//= Auriga Script ==============================================================
// Royal Banquet Quest Script
//==============================================================================

//============================================================
// WARP
//------------------------------------------------------------
prt_prison.gat,155,290,0	warp	prt_prison_OUT	1,1,prt_pri00.gat,50,120
prt_pri00.gat,54,139,0	warp	prt_pri_to_prt_cas	1,1,prt_cas.gat,182,258

prt_cas_q.gat,154,8,0	warp	qroom_L_to_way_way_to_q	1,1,prt_cas.gat,156,163

prt_cas.gat,278,163,0	script	way_to_qroom_R_qroom_R_	45,1,1,{
OnTouch:
	if(EP16_1QUE < 2) {
		unittalk getnpcid(0,"王室守護騎士#03"),"王室守護騎士 : その先は貴賓が滞在する離宮です。外部の方は出入りできません。",1;
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"王室守護騎士#03"),"王室守護騎士 : 招待を受けた方は、付き人の案内をお待ちください。",1;
		end;
	}
	warp "prt_cas_q.gat",135,119;
	end;
}

prt_cas_q.gat,132,119,0	warp	qroom_R_to_way_way_to_q	1,1,prt_cas.gat,274,163
prt_cas_q.gat,130,8,0	warp	qroom_vip_in_qroom_vip_	1,1,prt_cas_q.gat,30,28
prt_cas_q.gat,34,28,0	warp	qroom_vip_out_qroom_vip	1,1,prt_cas_q.gat,134,8
prt_cas_q.gat,130,32,0	script	qroom_heine_in_qroom_he	45,1,1,{
	if(EP16_1QUE > 7 && EP16_1QUE < 16) {
		mes "‐扉は閉じている‐";
		close;
	}
	warp "prt_cas_q.gat",30,78;
	end;
}

prt_cas_q.gat,34,78,0	warp	qroom_heine_out_qroom_h	1,1,prt_cas_q.gat,134,32
prt_cas_q.gat,130,56,0	script	qroom_nerius_in_qroom_n	45,1,1,{
	if(EP16_1QUE > 2 && EP16_1QUE < 7 || EP16_1QUE > 7 && EP16_1QUE < 15) {
		mes "‐扉は閉じている‐";
		close;
	}
	warp "prt_cas_q.gat",30,128;
	end;
}

prt_cas_q.gat,34,128,0	warp	qroom_nerius_out_qroom_	1,1,prt_cas_q.gat,134,56
prt_cas_q.gat,130,80,0	warp	qroom_valter_in_qroom_b	1,1,prt_cas_q.gat,30,178
prt_cas_q.gat,34,178,0	warp	qroom_balter_out_qroom_	1,1,prt_cas_q.gat,134,80
prt_cas_q.gat,153,119,0	warp	qroom_wigner_in_qroom_w	2,2,prt_cas_q.gat,78,21
prt_cas_q.gat,74,21,0	warp	qroom_wigner_out_qroom_	2,2,prt_cas_q.gat,149,119
prt_cas_q.gat,153,143,0	warp	qroom_richard_in_qroom_	2,2,prt_cas_q.gat,78,77
prt_cas_q.gat,74,77,0	warp	qroom_richard_out_qroom	2,2,prt_cas_q.gat,149,143
prt_cas_q.gat,153,167,0	warp	qroom_geob_in_qroom_geo	2,2,prt_cas_q.gat,78,131
prt_cas_q.gat,74,131,0	warp	qroom_geob_out_qroom_ge	2,2,prt_cas_q.gat,149,167
prt_cas_q.gat,153,191,0	warp	qroom_lugen_in_qroom_lu	2,2,prt_cas_q.gat,78,189
prt_cas_q.gat,74,189,0	warp	qroom_lugen_out_qroom_l	2,2,prt_cas_q.gat,149,191
prt_cas.gat,216,184,0	warp	mainhall_in_mainhall_ou	1,1,prt_cas.gat,93,212
prt_cas.gat,93,208,0	warp	mainhall_out_mainhall_i	1,1,prt_cas.gat,216,180
prt_cas.gat,197,148,0	warp	guestroom_l1_in_guestro	1,1,prt_cas.gat,31,117
prt_cas.gat,31,120,0	warp	guestroom_l1_guestroom_	1,1,prt_cas.gat,197,152
prt_cas.gat,178,148,0	warp	guestroom_l2_in_guestro	1,1,prt_cas.gat,27,43
prt_cas.gat,27,47,0		warp	guestroom_l2_guestroom_	1,1,prt_cas.gat,178,152
prt_cas.gat,235,148,0	warp	guestroom_r1_in_guestro	1,1,prt_cas.gat,174,104
prt_cas.gat,174,108,0	warp	guestroom_r1_guestroom_	1,1,prt_cas.gat,235,152
prt_cas.gat,253,148,0	warp	guestroom_r2_in_guestro	1,1,prt_cas.gat,174,37
prt_cas.gat,174,40,0	warp	guestroom_r2_guestroom_	1,1,prt_cas.gat,253,152
prt_cas.gat,130,218,0	warp	library_in_library_out	1,1,prt_cas.gat,303,48
prt_cas.gat,300,48,0	warp	library_out_library_in	1,1,prt_cas.gat,127,218
prt_cas.gat,174,234,0	warp	cruroom_in_cruroom_out	1,1,prt_cas.gat,247,107
prt_cas.gat,247,111,0	warp	cruroom_out_cruroom_in	1,1,prt_cas.gat,174,237
prt_cas.gat,41,275,0	warp	cuisine_in_cuisine_out	1,1,prt_cas.gat,320,182
prt_cas.gat,320,178,0	warp	cuisine_out_cuisine_in	1,1,prt_cas.gat,41,271
prt_cas.gat,54,217,0	warp	dining_in_dining_out	1,1,prt_cas.gat,388,137
prt_cas.gat,392,137,0	warp	dining_out_dining_in	1,1,prt_cas.gat,58,217
prt_cas.gat,216,142,0	warp	cas_out_prt_to_cas		1,1,prontera.gat,156,354
prt_lib_q.gat,9,25,0	warp	#lib_q_to_pprt			1,1,prt_q.gat,155,335

//============================================================
// クエストNPC
//------------------------------------------------------------
prontera.gat,121,72,3	script	王室急使#e16_prt	833,5,5,{
	if(ASH_1QUE < 100) {	//異世界クエスト未クリア
		mes "[急使]";
		mes "こんにちは。王宮では";
		mes "アッシュバキュームで活躍をした方々を";
		mes "招待して宴を開いています。";
		mes "もしあなたが知っている人の中に";
		mes "^4d4dff異世界遠征へ赴いた英雄^000000がいらしたら";
		mes "ぜひ、教えてください。";
		next;
		mes "[急使]";
		mes "軍の所属ではない冒険者様たちを";
		mes "見つけるのは難しくて、";
		mes "なかなか思うように進まないのです。";
		close;
	}
	if(EP16_1QUE == 0) {
		mes "[急使]";
		mes "お待ちください。";
		mes strcharinfo(0)+ "様ですね？";
		mes "えーと……";
		next;
		mes "[急使]";
		mes "ああ、よかった。";
		mes "間違いないですね。";
		mes "ギルドから配布された";
		mes "人相の絵と一致します。";
		next;
		mes "[急使]";
		mes "軍の所属ではない冒険者様たちを";
		mes "見つけるのはなかなか難しくて。";
		mes "都市の急使たちが皆、";
		mes "人相絵を持って";
		mes "あなた方を探しているのです。";
		next;
		menu "私になにか用ですか？",-;
		mes "[急使]";
		mes "はい。実は今、王宮では";
		mes "モロク討伐を祝う宴が";
		mes "王家主催で行われています。";
		next;
		mes "[急使]";
		if(checkquest(201730)) {	// 魔神殿攻略済み
			mes "その祝宴に";
			mes strcharinfo(0)+ "様を";
			mes "^4d4dff貴賓としてご招待^000000したいのです。";
			mes "なにしろ、あなたは";
			mes "あの、魔王モロクを討伐された";
			mes "当事者ですから！";
		}
		else {
			mes strcharinfo(0)+ "様は";
			mes "遠征と討伐に貢献した英雄ですので、";
			mes "その祝宴に^4d4dff貴賓としてご招待^000000したいのです。";
		}
		next;
		if(select("貴賓？","招待？","結構です") == 3) {
			mes "[急使]";
			mes "そ、そんなことをおっしゃらず";
			mes "……ハッ！";
			mes "もしかして、お受けするという意味の";
			mes "結構ですでしょうか？";
			mes "ありがとうございます。";
			next;
		}
		mes "[急使]";
		mes "はい。私はただの使いですので、";
		mes "詳細はわかりませんが、";
		mes "王宮で聞けると思います。";
		mes "この招待状をお持ちになってくだされば";
		mes "すぐに話は通りますから。";
		next;
		mes "[急使]";
		mes "さあ、王宮では多くの者が";
		mes "あなたの訪れを待っています。";
		mes "今すぐ王宮へ向かってください。";
		next;
		if(checkitemblank() == 0) {
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		mes "[急使]";
		mes "もし望むのであれば、";
		mes "すぐお送りさせていただきます。";
		getitem 6933,1;
		setquest 7681;
		set EP16_1QUE,1;
		next;
		if(select("送ってもらわない","送ってもらう") == 1) {
			mes "[急使]";
			mes strcharinfo(0)+ "様が";
			mes "直接向かってくださるのですね。";
			mes "ありがとうございます。";
			mes "^FF0000プロンテラ城^000000に到着しましたら、";
			mes "入り口にいる祝宴の会場案内人に";
			mes "この招待状をお見せください。";
			next;
			mes "[急使]";
			mes "それでは私は";
			mes "他の方にも招待状を";
			mes "届けなければなりませんので、";
			mes "これで失礼いたします。";
			mes "よい時間をお過ごしください。";
			close;
		}
		mes "[急使]";
		mes "わかりました。";
		mes "それではお送りします。";
		mes "お送りした先に祝宴の会場案内人が";
		mes "おりますのでお声をおかけください。";
		next;
		mes "[急使]";
		mes "それではいってらっしゃいませ。";
		mes "よい時間をお過ごしください。";
		close2;
		warp "prt_castle.gat",102,24;
		end;
	} else if(EP16_1QUE < 24) {
		mes "[急使]";
		mes "おや、" +strcharinfo(0)+ "様。";
		mes "どうされました？";
		next;
		if(select("祝宴場に送って欲しい","なんでもない") == 2) {
			mes "[急使]";
			mes "そうですか。失礼いたしました。";
			close;
		}
		mes "[急使]";
		mes "わかりました。";
		mes "それではお送りします。";
		mes "お送りした先に祝宴の会場案内人が";
		mes "おりますのでお声をおかけください。";
		next;
		mes "[急使]";
		mes "それではいってらっしゃいませ。";
		mes "よい時間をお過ごしください。";
		close2;
		warp "prt_castle.gat",102,24;
		end;
	} else {
		mes "[急使]";
		mes strcharinfo(0)+ "様。";
		mes "王宮にお送りしましょうか？";
		next;
		if(select("お願いします","けっこうです") == 2) {
			mes "[急使]";
			mes "わかりました。";
			close;
		}
		mes "[急使]";
		mes "それではお送りします。";
		close2;
		warp "prt_cas.gat",18,29;
		end;
	}
OnTouch:
	if(ASH_1QUE < 100)
		end;
	if(EP16_1QUE == 0)
		unittalk "王室急使 : お待ちください！　" +strcharinfo(0)+ "様ではありませんか？　お伝えしたいことがあります！",1;
	if(EP16_1QUE == 24 && EP162_1QUE == 0)
		unittalk "王室急使 : " +strcharinfo(0)+ "様！　ある方が貴賓室にてあなたをお待ちです！",1;
	end;
}

geffen.gat,123,68,3		duplicate(王室急使#e16_prt)	王室急使#e16_gef	833,5,5
payon.gat,121,72,3		duplicate(王室急使#e16_prt)	王室急使#e16_pay	833,5,5
morocc.gat,121,72,3		duplicate(王室急使#e16_prt)	王室急使#e16_moc	833,5,5
alberta.gat,121,72,3	duplicate(王室急使#e16_prt)	王室急使#e16_alb	833,5,5
aldebaran.gat,159,113,3	duplicate(王室急使#e16_prt)	王室急使#e16_alde	833,5,5
dali.gat,114,88,3		duplicate(王室急使#e16_prt)	王室急使#e16_dali	833,5,5

prt_castle.gat,106,27,4	script	祝宴の会場案内人#ep16	105,{
	mes "[衛兵]";
	mes "祝宴が行われている会場へ";
	mes "ご案内しております。";
	mes "なお、会場は宮殿内にありまして";
	mes "王族の方々もいらっしゃるので";
	mes "振る舞いには気をつけてください。";
	next;
	if(select("行きたいです","用はないです") == 2) {
		mes "[衛兵]";
		mes "わかりました。";
		close;
	}
	mes "[衛兵]";
	mes "それではご案内します。";
	close2;
	warp "prt_cas.gat",216,146;
	end;
}

prt_cas.gat,343,67,4	script	気難しい司書#ep16lug0	71,{
	switch(EP16_6QUE) {
	case 5:
		mes "[気難しい司書]";
		mes "ようこそ。";
		mes "本をお探しですか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[気難しい司書]";
			mes "ここは図書館です。";
			mes "まずは本を選んでください。";
			close;
		}
		mes "[気難しい司書]";
		mes "本のタイトルや内容はわかりますか？";
		next;
		menu "ルーンミッドガッツの歴史",-;
		mes "[気難しい司書]";
		mes "ルーンミッドガッツの歴史ですね。";
		mes "ここで読みますか？";
		mes "それとも貸し出しですか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "貸し出しでお願いします。";
		next;
		mes "[気難しい司書]";
		mes "それでは貸し出し証を";
		mes "提出してください。";
		next;
		emotion 23,"";
		mes "["+strcharinfo(0)+"]";
		mes "貸し出し証？";
		mes "持っていませんが……";
		next;
		mes "[気難しい司書]";
		mes "その場合は規定上、";
		mes "貸し出しができません。";
		next;
		emotion 4,"";
		mes "["+strcharinfo(0)+"]";
		mes "それでは貸し出し証は";
		mes "どうやって作ればいいですか？";
		next;
		mes "[気難しい司書]";
		mes "身分証をお持ちになれば";
		mes "簡単な確認後、すぐに発行可能です。";
		next;
		emotion 4,"";
		mes "["+strcharinfo(0)+"]";
		mes "えっと、身分証もないです。";
		mes "祝宴に参加中なので";
		mes "荷物は全部部屋に置いていて……";
		next;
		mes "[気難しい司書]";
		mes "祝宴ですか？";
		mes "もしかして祝宴に招待された冒険者様？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ええ、そうです。";
		next;
		mes "[気難しい司書]";
		mes "それでは王国が招待した";
		mes "冒険者様のリストにお名前があれば、";
		mes "そちらで貸し出しができます。";
		next;
		mes "[気難しい司書]";
		mes "王国では招待した";
		mes "冒険者様のリストを配布しており、";
		mes "何かあれば失礼の無いよう";
		mes "対応するように言われております。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "（よかったような、";
		mes "個人情報の安売りのような……）";
		next;
		mes "[気難しい司書]";
		mes "それではお名前をどうぞ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes strcharinfo(0)+"です。";
		next;
		mes "[気難しい司書]";
		mes "少々お待ちください。";
		mes strcharinfo(0)+"様ですね。";
		emotion 0;
		next;
		mes "[気難しい司書]";
		mes "それでは貸し出し書類を作る間に……";
		mes "私の個人的な質問ですが、";
		mes "教えていただけますか？";
		mes "外で何が起きているのか";
		mes "全くわからなくて。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "はい。";
		mes "知っている範囲のものでよければ。";
		while(1) {
			next;
			mes "[気難しい司書]";
			mes "王宮で開かれている祝宴は、";
			mes "王家の人や冒険者様まで集めて";
			mes "^0000cd一体何のために^000000開かれているんですか？";
			next;
			switch(select("王子の誕生","国王の誕生日","モロク退治を記念")) {
			case 1:
				mes "[気難しい司書]";
				mes "あれ、王子の誕生の祝は";
				mes "この時期ではないはずですが……";
				continue;
			case 2:
				mes "[気難しい司書]";
				mes "あれ、国王の誕生の祝は";
				mes "この時期ではないはずですが……";
				continue;
			case 3:
				mes "[気難しい司書]";
				mes "ああ、そうでしたか。";
				break;
			}
			break;
		}
		while(1) {
			next;
			mes "[気難しい司書]";
			mes "この祝宴は全ての王家が";
			mes "参加しているそうですね。";
			mes "^0000cd王家は全部でいくつ^000000なんですか？";
			next;
			if(select("六王家","七王家","八王家") != 2) {
				mes "["+strcharinfo(0)+"]";
				mes "すみません。";
				mes "ちょっと考え事をしていました。";
				mes "もう一度お願いします。";
				continue;
			}
			mes "[気難しい司書]";
			mes "それじゃ王宮は";
			mes "人で溢れかえっていそうですね。";
			mes "滅多にないことでしょうから。";
			break;
		}
		while(1) {
			next;
			mes "[気難しい司書]";
			mes "聞くところによると";
			mes "^0000cd王位継承権に参加しない王家^000000も";
			mes "あるそうですが、";
			mes "どの家門ですか？";
			next;
			if(select("ウィグナーとハイネン","レベンブルグとリハルト","ゲオルグとバルター") != 3) {
				mes "["+strcharinfo(0)+"]";
				mes "すみません。";
				mes "ちょっと考え事をしていました。";
				mes "もう一度お願いします。";
				continue;
			}
			mes "[気難しい司書]";
			mes "ゲオルグ家とバルター家……";
			mes "確かに、納得できますね。";
			break;
		}
		while(1) {
			next;
			mes "[気難しい司書]";
			mes "前国王陛下の家門も";
			mes "^0000cd古い呪い^000000のせいで";
			mes "そうなったと言われてますから。";
			next;
			if(select("ネリウス家ですか？","ゲオルグ家ですか？","リハルト家ですか？") != 2) {
				mes "["+strcharinfo(0)+"]";
				mes "すみません。";
				mes "ちょっと考え事をしていました。";
				mes "もう一度お願いします。";
				continue;
			}
			break;
		}
		mes "[気難しい司書]";
		mes "そうです。^0000cdゲオルグ家^000000ですね。";
		next;
		mes "[気難しい司書]";
		mes "最近は祝宴のためか、";
		mes "図書館に来る人もいないのですが、";
		mes "ここを離れることもできないので、";
		mes "話相手になってくださって";
		mes "嬉しかったです。";
		next;
		mes "[気難しい司書]";
		mes "手続きが完了しました。";
		mes "それではこちらが";
		mes "ルーンミッドガッツの歴史です。";
		next;
		mes "[気難しい司書]";
		mes "貸し出し期間は1週間です。";
		mes "延滞すれば延滞金がかかります。";
		mes "冒険者様からはいただきませんが、";
		mes "期限内のご返却をお願いいたします。";
		next;
		if(checkitemblank() == 0) {
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		mes "[気難しい司書]";
		mes "それでは。";
		delquest 14499;
		setquest 14500;
		set EP16_6QUE,6;
		getitem 6926,1;
		next;
		mes "‐プロンテラの空き地に";
		mes "　戻りますか？‐";
		next;
		if(select("移動する","移動しない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラの空き地に";
		mes "　向かった‐";
		close2;
		warp "prontera.gat",262,67;
		end;
	case 6:
		mes "[気難しい司書]";
		mes "本はもう全部読みましたか？";
		mes "どうやらまだのようですね。";
		next;
		mes "[気難しい司書]";
		mes "まずはゆっくりと";
		mes "気に入る本のタイトルから";
		mes "探してみてください。";
		mes "そして気になったものは";
		mes "ぜひ読んでみてください。";
		mes "本は心に潤いを与えるものですから。";
		next;
		mes "‐プロンテラの空き地に";
		mes "　戻りますか？‐";
		next;
		if(select("移動する","移動しない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラの空き地に";
		mes "　向かった‐";
		close2;
		warp "prontera.gat",262,67;
		end;
	default:
		mes "[気難しい司書]";
		mes "図書館にようこそ。";
		next;
		mes "[気難しい司書]";
		mes "まずはゆっくりと";
		mes "気に入る本のタイトルから";
		mes "探してみてください。";
		mes "そして気になったものは";
		mes "ぜひ読んでみてください。";
		mes "本は心に潤いを与えるものですから。";
		close;
	}
}

prt_cas.gat,364,69,3	script	緊張した男#ep16lug01	748,{
	mes "[緊張した男]";
	mes "うーん、ここにもない……";
	mes "いったいどこにあの本があるんだ。";
	next;
	mes "[からかう男]";
	mes "おいおい、そこまでして";
	mes "内容を調べる必要があるのか？";
	close;
}

prt_cas.gat,365,68,3	script	からかう男#ep16lug01	898,{
	mes "[緊張した男]";
	mes "うーん、ここにもない……";
	mes "いったいどこにあの本があるんだ。";
	next;
	mes "[からかう男]";
	mes "おいおい、そこまでして";
	mes "内容を調べる必要があるのか？";
	close;
}

prt_pri00.gat,51,116,8	script	エルロンド・ロレンス#EP	751,{
	if(BaseLevel < 150) {
		mes "[エルロンド・ロレンス]";
		mes "あなたは";
		mes "関係者ではありませんね？";
		mes "ここは関係者以外の";
		mes "出入りを禁止しています。";
		mes "ご協力をお願いします。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "……まあ、もう少し";
		mes "お強そうになったら";
		mes "問題なくなると思いますが。";
		next;
		mes "‐^ff0000BaseLvが150以上の場合";
		mes "　^ff0000プロンテラ地下監獄に";
		mes "　^ff0000進行することが出来ます^000000‐";
		close;
	}
	if(!(checkquest(5415) & 0x8)) {		// プロンテラ地下監獄入場許可
		mes "[エルロンド・ロレンス]";
		mes "こんにちは。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "失礼ですが……";
		mes "ここからは関係者以外の";
		mes "出入りを禁止しています。";
		mes "ご協力をお願いします。";
		next;
		emotion 0;
		mes "[エルロンド・ロレンス]";
		mes "……それにしても";
		mes "ここは誰でも出入りできる";
		mes "区域ではないのですが……";
		mes "……むむ。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "あの魔王モロクを倒されたという";
		mes "冒険者様が今、";
		mes "王宮の祝宴に招待されたという";
		mes "話を聞いております。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "その風貌、使い込まれた武具……";
		mes "もしかして……";
		next;
		emotion 23;
		mes "[エルロンド・ロレンス]";
		mes "招待された冒険者様は、";
		mes "あなたですか？";
		next;
		emotion 38;
		mes "[エルロンド・ロレンス]";
		mes "うおお……凄い！";
		mes "噂で聞いていました。";
		mes "私、あなたのファンです。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "祝宴が開かれる日に";
		mes "ここの警備になってしまって";
		mes "ちょっと憂鬱だったんですが、";
		mes "お会い出来て";
		mes "本当にうれしいです！";
		next;
		mes "[エルロンド・ロレンス]";
		mes "自己紹介させてください!!";
		mes "私は王室クルセイダーの";
		mes "エルロンド・ロレンスと申します。";
		mes "冒険者様の活躍を聞いて";
		mes "憧れておりました!!";
		next;
		mes "[エルロンド・ロレンス]";
		mes "あ！";
		mes "そうだ。";
		mes "サインをお願いしても";
		mes "いいでしょうか？";
		next;
		switch(select("サインしない","サインする")) {
		case 1:
			mes "[エルロンド・ロレンス]";
			mes "そうですか……";
			mes "残念ですが、仕方ないですね。";
			mes "気が向いたらお願いします。";
			break;
		case 2:
			input '@str$;
			emotion 14;
			mes "[エルロンド・ロレンス]";
			mes '@str$;
			next;
			mes "[エルロンド・ロレンス]";
			mes "……うわあ～！";
			mes "感謝します。";
			mes "同僚たちに自慢できる";
			mes "宝物ができました。";
			mes "感激です。";
			break;
		}
		next;
		mes "[エルロンド・ロレンス]";
		mes "あ！　あっ！";
		mes "そうだ。";
		mes "そう！";
		next;
		mes "[エルロンド・ロレンス]";
		mes "実は、王室クルセイダー内で";
		mes "地下監獄で発生した問題への対処を";
		mes "有名な冒険者様に";
		mes "お願いしてみようという話が";
		mes "あったんです。";
		next;
		menu "地下監獄で発生した問題？",-;
		mes "[エルロンド・ロレンス]";
		mes "お～！";
		mes "やはり冒険者様なら";
		mes "興味を持つと思いました。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "お名前と実力はすでに";
		mes "証明されたも同然ですし、";
		mes "詳しい状況をお話ししましょう。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "実はこれは";
		mes "長いこと解決されずにいる、";
		mes "とても頭を悩まされる";
		mes "問題なのです……";
		next;
		menu "ほう？",-,"そんなに……",-,"はい",-;
		mes "[エルロンド・ロレンス]";
		mes "私たちの警備するこの地下監獄に";
		mes "前はいなかったモンスターたちが";
		mes "出現しはじめたのです。";
		next;
		menu "……モンスターが",-,"警備してるんですよね？",-,"それは大変ですね",-;
		mes "[エルロンド・ロレンス]";
		mes "あっ！";
		mes "誤解されては困ります！";
		next;
		emotion 16;
		mes "[エルロンド・ロレンス]";
		mes "私たちクルセイダーたちは";
		mes "地下監獄に出現したモンスター退治に";
		mes "力を注いでいます。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "ですが、私たちの倒す数より";
		mes "増える方が早いのです。";
		mes "ついに手におえない状況まで";
		mes "きてしまいました。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "恥ずかしい話ですが";
		mes "モンスターがどこを通じて";
		mes "入ってきているかさえも";
		mes "把握出来ていないのです。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "あ、すいません。";
		mes "前置きが";
		mes "長かったですよね。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "冒険者様にお願いしたいのは、";
		mes "暇な時に地下監獄の";
		mes "モンスター退治をお願いしたいのです。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "もちろん、";
		mes "報告書を書いていただく";
		mes "必要はありませんよ。";
		mes "それは私が書きます。";
		next;
		mes "‐プロンテラ地下監獄に";
		mes "　進行できるようになった‐";
		setquest 5415;
		compquest 5415;
		close;
	}
	mes "[エルロンド・ロレンス]";
	mes "地下監獄に入りますか？";
	mes "それともなにか……";
	mes "気になることでも？";
	next;
	switch(select("地下監獄に行く","地下監獄について","囚人について","似たような奴らを見たような気がする")) {
	case 1:
		mes "[エルロンド・ロレンス]";
		mes "わかりました。";
		mes "どうかお気をつけて……！";
		close2;
		warp "prt_prison.gat",160,290;
		end;
	case 2:
		mes "[エルロンド・ロレンス]";
		mes "ほうほう！";
		mes "地下監獄が気になりますか？";
		next;
		mes "[エルロンド・ロレンス]";
		mes "大体の国には、罪を犯した者を";
		mes "収容する施設があるように、";
		mes "ルーンミッドガッツ王国の";
		mes "平和と安全を脅かす存在たちを";
		mes "閉じ込める為に作られたと";
		mes "聞いています。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "基本的に丈夫に";
		mes "建てられてはいますが……";
		next;
		mes "[エルロンド・ロレンス]";
		mes "とても古い施設なので";
		mes "あらゆる補修が必要な状態です。";
		mes "状況が状況なので";
		mes "修理ができていないまま";
		mes "なんですけどね。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "ですので、現状、";
		mes "あまり良い状態ではないので、";
		mes "地下監獄で怪我などしないように";
		mes "気を付けてください。";
		close;
	case 3:
		mes "[エルロンド・ロレンス]";
		mes "見てお分かりに";
		mes "なったと思いますが、";
		mes "監獄の中にいる存在たちは";
		mes "モンスターたちです。";
		mes "誰がどうみても";
		mes "モンスターですよね？";
		next;
		mes "[エルロンド・ロレンス]";
		mes "あまりにも古い施設でもあり、";
		mes "書類すら紛失していたりもして……";
		mes "ただ伝え聞いている内容に";
		mes "なりますが、お話しますね。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "確かなのは、彼らは過去";
		mes "ルーンミッドガッツ王国を";
		mes "混乱に陥れた存在だということ。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "残念ながら彼らの罪名も";
		mes "懲役も残っている";
		mes "文書はありません。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "あるクルセイダーが";
		mes "罪名と懲役が記されていた";
		mes "文書を無くしてしまったという";
		mes "ことが書かれた文書だけは";
		mes "伝わっているんですが……";
		next;
		mes "[エルロンド・ロレンス]";
		mes "まあ地下監獄にいる奴らも";
		mes "特に気にしていなさそうなので";
		mes "問題はなさそうです。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "気になるとすれば、";
		mes "懲役が終わったかも";
		mes "しれないにも関わらず、";
		mes "外に出れない奴らも";
		mes "いるということでしょうか。";
		close;
	case 4:
		mes "[エルロンド・ロレンス]";
		mes "あ！";
		mes "その話、私も聞いたことが";
		mes "あります。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "私達、王室クルセイダーも";
		mes "集団ですから";
		mes "冒険者の経歴を持つ者もいます。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "その彼が地下監獄に収容されている";
		mes "奴らにそっくりなモンスターが";
		mes "外を歩き回っているのを見たと";
		mes "言っていました。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "クルセイダーの間では";
		mes "冒険者出身だからきっと、";
		mes "嘘をついているに違いないと";
		mes "相手にはしなかったのですが……";
		next;
		emotion 23;
		mes "[エルロンド・ロレンス]";
		mes "あっ！";
		mes "冒険者様がそうだとは";
		mes "思っていませんよ!?";
		mes "ただ、そいつは普段から";
		mes "嘘や、妄想話が酷くて……";
		next;
		mes "[エルロンド・ロレンス]";
		mes "確信を持って言いますが、";
		mes "外を歩き回っているモンスターと";
		mes "地下監獄にいる奴らは";
		mes "違う存在です。";
		next;
		mes "[エルロンド・ロレンス]";
		mes "多分、それらの兄弟や";
		mes "遠い親戚みたいなものでは";
		mes "ないかと……";
		mes "モンスターに兄弟や親戚が";
		mes "いるのかは知りませんが。";
		close;
	}
}

prt_cas_q.gat,80,80,4	script	リハルト家執事#EP161GAM	57,{
	if(EP16_1QUE < 2) {
		mes "[執事]";
		mes "ここには建国初期から";
		mes "軍権を掌握してきた";
		mes "リハルト家が滞在しています。";
		close;
	}
	switch(EP16_5QUE) {
	case 0:
		mes "[執事]";
		mes "こんにちは。お待ちしていました。";
		mes "ここには建国初期から";
		mes "軍権を掌握してきた";
		mes "リハルト家が滞在しています。";
		next;
		mes "[執事]";
		if(checkquest(201730)) {	// 魔神殿攻略済み
			mes "あの魔王モロクを";
			mes "討伐されたという";
		}
		else
			mes "モロク討伐に貢献したという";
		mes strcharinfo(0)+ "様の名声は";
		mes "日々、耳にしております。";
		mes "お会いできて光栄です。";
		next;
		mes "[執事]";
		mes "部屋の中で我がリハルト家の";
		mes "ポー様がお待ちです。";
		next;
		setquest 5402;
		set EP16_5QUE,1;
		mes "[執事]";
		mes "それではご案内します。";
		close;
	case 1:
		mes "[執事]";
		mes "我がリハルト家の";
		mes "ポー様がお待ちです。";
		mes "どうぞお入りください。";
		close;
	case 2:
		mes "[執事]";
		mes "ポー様とお話はされましたか？";
		close;
	case 3:
	case 4:
		//if(!(checkquest(73125) & 0x8))
		//	setquest 73125;
		//compquest 73125;
		mes "[執事]";
		mes "戦闘訓練を行っていただけるのですね。";
		mes "協力に感謝します。";
		mes "西の離宮の前にある^ff0000冒険者歓迎室^000000に";
		mes "リハルト家の訓練官がいます。";
		mes "彼から戦闘訓練を受けてください。";
		next;
		mes "[執事]";
		mes "よろしければ、";
		mes "部屋までご案内いたしましょうか？";
		next;
		if(select("お願いする","自分の足で歩いていく") == 2) {
			mes "[執事]";
			mes "かしこまりました。";
			close;
		}
		mes "[執事]";
		mes "かしこまりました。";
		mes "ではこちらへどうぞ。";
		close2;
		warp "prt_cas.gat",15,30;
		end;
	}
	end;
}

prt_cas_q.gat,93,74,4	script	ポー・リハルト#EP161GAM	993,{
	switch(EP16_5QUE) {
	case 0:
		cutin "richard_po02.BMP",2;
		emotion 19,"ポー・リハルト#EP161GAM";
		mes "[ポー]";
		mes "やあ、キミは";
		mes "祝宴に招待された冒険者かな？";
		mes "……すまないが、";
		mes "私はいま疲れているので";
		mes "休みたいのだ。";
		next;
		mes "[ポー]";
		mes "部屋の前にいる執事に話して";
		mes "時間を決めてから";
		mes "また来るといい。";
		close2;
		cutin "richard_po01.BMP",255;
		end;
	case 1:
		cutin "richard_po02.BMP",2;
		emotion 52,"ポー・リハルト#EP161GAM";
		mes "[ポー]";
		if(checkquest(201730)) {	// 魔神殿攻略済み
			mes "やあ。キミが魔王モロクを";
			mes "討伐したという";
		}
		else {
			mes "やあ。キミが魔王モロクの";
			mes "討伐に貢献したという";
		}
		mes "冒険者なんだね？";
		mes "その名声は王室にも";
		mes "広く知られているよ。";
		next;
		menu "ご挨拶に伺いました",-;
		mes "[ポー]";
		mes "これはこれは。";
		mes "わざわざ恐縮だ。";
		mes "ようこそ、リハルト家へ。";
		next;
		mes "[ポー]";
		mes "祝宴を楽しんでいるか？";
		mes "それとも王位継承についての方が";
		mes "気になるか？";
		mes "ふふふ、";
		mes "この私が王位につくと思うか？";
		next;
		mes "[ポー]";
		mes "私は王位に興味がある。";
		mes "だが、最近は軍事面についてのほうが";
		mes "興味があるのだ。";
		next;
		mes "[ポー]";
		mes "王になってくれと";
		mes "他の王家の家門連中に";
		mes "土下座されたら考えてもいいがな。";
		next;
		mes "[ポー]";
		mes "正直、今は王位より";
		mes "キミのほうに興味がある。";
		next;
		menu "え！",-;
		mes "[ポー]";
		mes "……まあ、その話は後でよいか。";
		mes "挨拶回りがあるのだろう？";
		mes "祝宴を楽しんで行ってくれ。";
		next;
		cutin "richard_po02.BMP",255;
		delquest 5402;
		delquest 73053;
		set EP16_5QUE,2;
		if((checkquest(7683)&0x8) && !checkquest(73051) && !checkquest(73053) && !checkquest(73052) && !checkquest(73054) && !checkquest(73055) && !checkquest(73056)) {
			mes "‐^0000cd七王家すべてに挨拶をした。^000000";
			mes "　ベルのところに戻ろう‐";
		} else {
			mes "‐^0000cdリハルト家との挨拶を済ました。^000000";
			mes "　他の王家にも挨拶に行こう‐";
		}
		next;
		mes "‐立ち去ろうとすると";
		mes "　ポーが話しかけてきた‐";
		next;
		cutin "richard_po02.BMP",2;
		mes "[ポー]";
		mes "挨拶回りで忙しい中悪いが、";
		mes "よかったら私の話を聞いてほしい。";
		mes "前からキミに注目していたのだ。";
		mes "時間があるならば";
		mes "私に話しかけて欲しい。";
		close2;
		cutin "richard_po02.BMP",255;
		end;
	case 2:
		cutin "richard_po02.BMP",2;
		mes "[ポー]";
		mes "我がリハルト家が";
		mes "キミに注目している理由を";
		mes "話すことにしようか。";
		next;
		mes "‐ポー・リハルトが少し真面目な";
		mes "　顔つきになった‐";
		next;
		mes "[ポー]";
		mes "リハルト家は古くより、";
		mes "兵士を育成、強化して";
		mes "ルーンミッドガッツ王国の国防を";
		mes "担っている。";
		mes "まあ、戦争屋と呼ぶ者もいるがな。";
		next;
		mes "[ポー]";
		mes "優れた兵士。";
		mes "今、リハルト家が求める優れた兵士とは";
		mes "あらゆる戦局に対応できる兵士だ。";
		mes "そのために、兵士たちに";
		mes "リハルト家の戦略と戦術を";
		mes "叩き込んでいる。";
		next;
		mes "[ポー]";
		mes "どのような困難があろうとも、";
		mes "機略を駆使して突破する";
		mes "兵士の大量生産。";
		mes "それが今の私が一番望むものだ。";
		next;
		mes "[ポー]";
		mes "戦いは変化し、進化する。";
		mes "だからこそ、それに対応できる";
		mes "戦略と戦術が必要なのだ。";
		next;
		mes "[ポー]";
		mes "すなわち、";
		mes "多くの戦場の経験が必要になる。";
		mes "そこでキミへのお願いだ。";
		mes "是非、キミに";
		mes "私の指定する戦闘訓練を行ってもらい";
		mes "戦術データをとりたいのだ。";
		next;
		mes "[ポー]";
		mes "もちろん、協力してくれれば";
		mes "それに見合う報酬も支給する。";
		mes "どうだ？";
		mes "お互い悪い話ではないと思うが。";
		next;
		if(select("戦闘訓練に挑戦する","断る") == 2) {
			emotion 57,"ポー・リハルト#EP161GAM";
			mes "[ポー]";
			mes "そうか。残念だが仕方ないな。";
			mes "気が変わったら訪ねて来てくれ。";
			close2;
			cutin "richard_po02.BMP",255;
			end;
		}
		emotion 33,"ポー・リハルト#EP161GAM";
		mes "[ポー]";
		mes "そうか！　そうか！";
		mes "チャレンジ精神旺盛な者は";
		mes "とても好きだぞ！";
		mes "協力感謝する。";
		next;
		mes "[ポー]";
		mes "執事に手筈を整えておくよう伝える。";
		mes "キミは準備が整ったら";
		mes "彼に声をかけてくれ。";
		mes "結果を楽しみにしてるぞ！";
		next;
		mes "[ポー]";
		mes "国を守るためには";
		mes "どうしても兵力が必要なのだ。";
		next;
		mes "[ポー]";
		mes "この数年、時代は大きく変化した。";
		mes "魔王モロクの登場による";
		mes "異世界への進出。";
		mes "そして、異種族の技術が流入し、";
		mes "魔神となったモロクすら討伐できた。";
		next;
		mes "[ポー]";
		mes "……驚くべきことにね、";
		mes "時を戻ることも可能になり、";
		mes "過去の英雄や偉人にも";
		mes "会えるようになった。";
		next;
		mes "[ポー]";
		mes "この状況で私は";
		mes "考えなくてはいけないよ。";
		mes "……彼らが敵になった場合、";
		mes "どのように倒せばよいのだろうか、と。";
		next;
		mes "[ポー]";
		mes "ラフィネ族を倒すためには、";
		mes "サファ族を倒すためには、";
		mes "レシア族を倒すためには、";
		mes "過去の時代の兵士を倒すためには";
		next;
		mes "[ポー]";
		mes "どのような戦略と戦術が";
		mes "必要になるのか。";
		next;
		if(select("彼らは敵じゃないです！","そんなことを考えなければ……") == 1) {
			mes "[ポー]";
			mes "気を悪くしないでくれ。";
			mes "彼らを敵とは思ってはいない。";
			mes "ただ、リハルト家の長としては、";
			mes "考えなくてはいけないのだよ。";
			next;
			mes "[ポー]";
			mes "それでは戦闘訓練を頼むよ。";
			mes "詳しくは執事に聞いてくれ。";
			setquest 5403;
			set EP16_5QUE,3;
			close2;
			cutin "richard_po02.BMP",255;
			end;
		}
		mes "[ポー]";
		mes "……";
		mes "意外だな。";
		mes "大抵、";
		mes "このような考えをする私には";
		mes "嫌悪感を抱く者が多いのだが。";
		next;
		mes "[ポー]";
		mes "そういわれると悪い気はしない。";
		mes "フフフ、";
		mes "キミが気に入ったよ。";
		next;
		if(select("いえいえ","どれくらい気に入った？") == 1) {
			mes "[ポー]";
			mes "それでは戦闘訓練を頼むよ。";
			mes "詳しくは執事に聞いてくれ。";
			setquest 5403;
			set EP16_5QUE,3;
			close2;
			cutin "richard_po02.BMP",255;
			end;
		}
		mes "[ポー]";
		mes "どれくらいだって？";
		mes "ハッハッハッハ！";
		mes "キミは本当に面白いな！";
		next;
		mes "[ポー]";
		mes "……そうだな。";
		next;
		mes "[ポー]";
		mes "キミに、";
		mes "プロポーズをしたいくらいかな。";
		mes "　";
		mes "‐ポー・リハルトは笑いながら言った‐";
		next;
		if(select("面白いですね","はい、お受けします！") == 2) {
			if(Sex) {
				mes "[ポー]";
				mes "ハッハッハッハ！";
				mes "残念ながら我が国では";
				mes "同性婚を認めていないので";
				mes "お断りしよう。";
			} else {
				mes "[ポー]";
				mes "ハッハッハッハッ！";
				mes "そういってもらえると";
				mes "冗談でも嬉しいものだ。";
			}
			next;
		}
		mes "[ポー]";
		mes "それでは戦闘訓練を頼むよ。";
		mes "詳しくは執事に聞いてくれ。";
		close2;
		cutin "richard_po02.BMP",255;
		end;
	case 3:
	case 4:
		cutin "richard_po02.BMP",2;
		mes "[ポー]";
		mes "訓練の進捗はどうだ？";
		mes "簡単そうに見えるものでも";
		mes "あまり油断しない方がいいぞ。";
		close2;
		cutin "richard_po02.BMP",255;
		end;
	}
	end;
}

prt_cas.gat,218,182,3	script	王室守護騎士#01	751,{
	mes "[王室守護騎士]";
	mes "こちらは魔王モロク討伐を祝う";
	mes "宴の会場となります。";
	mes "入場されますか？";
	next;
	if(select("入場する","入場しない") == 2) {
		mes "[王室守護騎士]";
		mes "承知いたしました。";
		mes "入場の際は、私にお声掛けください。";
		close;
	}
	mes "[王室守護騎士]";
	mes "それでは";
	mes "中へご案内いたします。";
	close2;
	warp "prt_cas.gat",93,212;
	end;
}

prt_cas.gat,97,216,2	script	侍従#vip_alimi	968,{
	mes "[侍従]";
	mes "お楽しみいただけていますか？";
	mes "久しぶりの王室行事ですので";
	mes "はりきって準備をしました。";
	mes "お気に召すと良いのですが。";
	close;
}

prt_cas.gat,93,214,0	script	#vip_alimi	139,4,1,{
OnTouch:
	if(EP16_1QUE > 0) {
		switch(getbaseclass(Class,2)) {
		case CLASS_SM:
		case CLASS_KN:
		case CLASS_CR:
			unittalk getnpcid(0,"侍従#vip_alimi"),"侍従 : 強靭な守護の剣" +strcharinfo(0)+ "様です。",1;
			break;
		case CLASS_MG:
		case CLASS_WZ:
		case CLASS_SA:
			unittalk getnpcid(0,"侍従#vip_alimi"),"侍従 : 真実の探求者"+strcharinfo(0)+"様です。",1;
			break;
		case CLASS_AC:
		case CLASS_HT:
			unittalk getnpcid(0,"侍従#vip_alimi"),"侍従 : 風を切る矢"+strcharinfo(0)+"様です。",1;
			break;
		case CLASS_BA:
		case CLASS_DC:
			unittalk getnpcid(0,"侍従#vip_alimi"),"侍従 : 幸福の伝道師"+strcharinfo(0)+"様です。",1;
			break;
		case CLASS_AL:
		case CLASS_PR:
		case CLASS_MO:
			unittalk getnpcid(0,"侍従#vip_alimi"),"侍従 : 大いなる神の代理人" +strcharinfo(0)+ "様です。",1;
			break;
		case CLASS_MC:
		case CLASS_BS:
		case CLASS_AM:
			unittalk getnpcid(0,"侍従#vip_alimi"),"侍従 : 見えざる黄金の手" +strcharinfo(0)+ "様です。",1;
			break;
		case CLASS_TF:
		case CLASS_AS:
		case CLASS_RG:
			unittalk getnpcid(0,"侍従#vip_alimi"),"侍従 : 静かなる闇の支配者" +strcharinfo(0)+ "様です。",1;
			break;
		case CLASS_NV:
		case CLASS_SNV:
			unittalk getnpcid(0,"侍従#vip_alimi"),"侍従 : はじまりを記憶する者"+strcharinfo(0)+"様です。",1;
			break;
		default:
			unittalk getnpcid(0,"侍従#vip_alimi"),"侍従 : 揺るぎない信念のマスター" +strcharinfo(0)+ "様です。",1;
			break;
		}
	}
	end;
}

prt_cas.gat,161,168,5	script	王室守護騎士#02	751,{
	mes "[守護騎士]";
	mes "プロンテラ城内を";
	mes "ご案内します。";
	next;
	switch(select("離宮","祝宴場","大丈夫です")) {
	case 1:
		mes "[守護騎士]";
		mes "すぐ西側に見える扉が";
		mes "離宮への出入り口です。";
		mes "ハイネン、ネリウス、バルター家と";
		mes "貴賓用の客室があります。";
		close;
	case 2:
		mes "[守護騎士]";
		mes "祝宴場はここから東の通路の先、";
		mes "中央にある大きな入口から";
		mes "ご入場いただけます。";
		close;
	case 3:
		mes "[守護騎士]";
		mes "なにかございましたら";
		mes "お声掛けください。";
		close;
	}
}

prt_cas.gat,270,168,3	script	王室守護騎士#03	751,{
	mes "[守護騎士]";
	mes "プロンテラ城内を";
	mes "ご案内します。";
	next;
	switch(select("離宮","祝宴場","大丈夫です")) {
	case 1:
		mes "[守護騎士]";
		mes "すぐ東側に見える扉が";
		mes "離宮への出入り口です。";
		mes "ウィグナー、レベンブルグ、";
		mes "ゲオルグ、リハルト家の";
		mes "客室があります。";
		mes "ゲオルグ家は現王家です。";
		close;
	case 2:
		mes "[守護騎士]";
		mes "祝宴場はここから西の通路の先、";
		mes "中央にある大きな入口から";
		mes "ご入場いただけます。";
		close;
	case 3:
		mes "[守護騎士]";
		mes "なにかございましたら";
		mes "お声掛けください。";
		close;
	}
}

prt_pri00.gat,58,128,4	script	監視者テルケス#ep16	732,{
	if(EP16_1QUE == 13) {
		mes "[監視者テルケス]";
		mes "おや、驚いた。";
		mes "……王家の記憶の間から出て";
		mes "ここにいるということは、";
		mes "移動の許可を";
		mes "もらっているようですね。";
		next;
		mes "[監視者テルケス]";
		mes "外へ案内しましょう。";
		mes "階段に沿って進むと、";
		mes "クルセイダーの執務室へ出ますよ。";
		mes "一度貴賓室に戻り、";
		mes "侍従から話を聞くと良いでしょう。";
		mes "お気をつけて。";
		delquest 7695;
		setquest 7696;
		set EP16_1QUE,14;
		close2;
		warp "prt_pri00.gat",53,128;
		end;
	}
	if(EP16_1QUE > 13) {
		mes "[監視者テルケス]";
		mes "どうされましたか？";
		next;
		if(select("王家の記憶の間に行く","外に出る")==2) {
			mes "[監視者テルケス]";
			mes "外ですね。どうぞ。";
			close2;
			warp "prt_pri00.gat",53,128;
			end;
		}
		mes "[監視者テルケス]";
		mes "はい。お気をつけて。";
		mes "出入りを人に見られないように";
		mes "ご注意を。";
		close2;
		warp "prt_lib.gat",9,28;
		end;
	}
	mes "[監視者テルケス]";
	mes "修行の邪魔です。";
	mes "よそへ行ってください。";
	close;
OnInit:
	setcell "prt_pri00.gat",60,127,0;
	end;
}


prt_cas.gat,188,258,0	script	prt_cas_to_prt_pri00	45,1,1,{
OnTouch:
	if(EP16_1QUE < 2) {
		unittalk getnpcid(0,"守護騎士#ep16_prigate01"),"守護騎士 : この先には勝手に入らないでください。",1;
		if(!sleep2(3000)) end;
		warp "prt_cas.gat",182,258;
		end;
	}
	warp "prt_pri00.gat",54,134;
	end;
}

prt_cas.gat,180,264,3	script	守護騎士#ep16_prigate01	751,{
	unittalk "守護騎士 : クルセイダーの執務室は廊下の最奥にあります。",1;
	end;
}

prt_cas.gat,180,251,3	script	守護騎士#ep16_prigate02	751,{
	unittalk "守護騎士 : 勤務中、異常なし……",1;
	if(!sleep2(2000)) end;
	unittalk "守護騎士 : ああ、早く交替時間になって……",1;
	end;
}

prt_cas.gat,91,237,3	script	エキナシア#ep16_etc01	803,{
	if(ASH_5QUE < 31) {	// 魔王モロク追跡クエスト
		mes "[エキナシア]";
		mes "このような祝宴を";
		mes "設けてもらえるとは……";
		mes "異世界へ向かうと決めた時には";
		mes "予想しなかったことです。";
		next;
		mes "[エキナシア]";
		mes "とてもうれしいものですね。";
		close;
	}
	mes "[エキナシア]";
	mes "あなたも招待されていたのですね！";
	mes "お久しぶりです。";
	next;
	cutin "mocseal_rin01.bmp",2;
	mes "[リーン]";
	mes "あら、まだ生きていたのね。";
	mes "こんな場所で会えるとは。";
	mes "そういえばキドも一緒に来てるわよ。";
	mes "どこかへ行ってるけど。";
	next;
	cutin "mocseal_rin01.bmp",255;
	mes "[エキナシア]";
	mes "ギルドの人に会ったと言っていたので";
	mes "どこかで話しこんでるのでは";
	mes "ないでしょうか。";
	next;
	cutin "mocseal_rin01.bmp",2;
	mes "[リーン]";
	mes "そういえば。";
	mes "知り合いっぽい人に誘われて";
	mes "食堂に行くって言ってたわ。";
	mes strcharinfo(0)+ "も";
	mes "挨拶しに行ってあげてね。";
	next;
	cutin "mocseal_rin01.bmp",255;
	mes "[エキナシア]";
	mes "そうですね。";
	mes "久しぶりですし、";
	mes "会ってみたらいいですね。";
	mes "懐かしい仲間と祝宴を楽しみましょう。";
	close;
}

prt_cas.gat,89,238,5	script	リーン#ep16_etc02	885,{
	if(ASH_5QUE < 31) {	// 魔王モロク追跡クエスト
		cutin "mocseal_rin01.bmp",2;
		mes "[リーン]";
		mes "なるほど、裕福な人間は";
		mes "こうやって遊ぶのね。";
		mes "せっかくだから、";
		mes "綺麗なドレスでも";
		mes "見て楽しもうかしら。";
		close2;
		cutin "mocseal_rin01.bmp",255;
		end;
	}
	cutin "mocseal_rin01.bmp",2;
	mes "[リーン]";
	mes "なるほど、裕福な人間は";
	mes "こうやって遊ぶのね。";
	mes "あら、" +strcharinfo(0);
	mes "せっかくの機会だもの。";
	mes "楽しみましょう。";
	close2;
	cutin "mocseal_rin01.bmp",255;
	end;
}

prt_cas.gat,367,123,7	script	キド#ep16_etc04	884,{
	if(ASH_5QUE < 31) {	// 魔王モロク追跡クエスト
		mes "[キド]";
		mes "リーンも、エキナシアも";
		mes "一体どこに行ってしまったんだ。";
		mes "二人とも豪華な宴で";
		mes "浮かれすぎだろう。";
		cutin "mocseal_kid01.bmp",2;
		next;
		mes "[キド]";
		mes "まったく";
		mes "ここは豪華すぎて";
		mes "俺には釣り合わない場所だ。";
		mes "　";
		mes "まあ、たまには良いが。";
		close2;
		cutin "mocseal_kid01.bmp",255;
		end;
	}
	mes "[キド]";
	mes "久しぶりだな。";
	mes "もうリーンとエキナシアには会ったか？";
	cutin "mocseal_kid01.bmp",2;
	next;
	mes "[キド]";
	mes "二人とも豪華な宴で";
	mes "ずいぶん";
	mes "浮かれていただろう？";
	next;
	mes "[キド]";
	mes "……ここは豪華すぎて";
	mes "俺には釣り合わない。";
	mes "　";
	mes "まあ、たまになら良いが。";
	close2;
	cutin "mocseal_kid01.bmp",255;
	end;
}

prt_cas.gat,215,146,0	script	#ep16_evt_01_on	139,1,1,{
	end;
OnTouch:
	if(EP16_1QUE == 1) {
		cloakoffnpc "侍従ベル#ep16_01";
		unittalk getnpcid(0,"侍従ベル#ep16_01"),"侍従ベル : お待ちしていました。" +strcharinfo(0)+ " 様。",1;
	}
	end;
}

prt_cas.gat,217,150,3	script(CLOAKED)	侍従ベル#ep16_01	967,{
	if(EP16_1QUE == 1) {
		mes "[侍従ベル]";
		mes strcharinfo(0)+ "様";
		mes "お待ちしておりました。";
		mes "無事、祝宴の招待状を";
		mes "お届けできたようですね。";
		next;
		mes "[侍従ベル]";
		mes "ここでの生活に不便がないよう";
		mes "お世話させていただきます。";
		mes "ベル・トワイライトと申します。";
		mes "どうぞ、ベルとお呼びください。";
		next;
		mes "[侍従ベル]";
		mes strcharinfo(0)+ "様は";
		mes "特別な貴賓として";
		mes "招待されておりますので、";
		mes "お部屋の用意がございます。";
		next;
		mes "[侍従ベル]";
		mes "まっすぐ進んでいただいて";
		mes "廊下の十字路を、";
		mes "^4d4dff左に^000000進んでください。";
		next;
		mes "[侍従ベル]";
		mes "私は、先に行って";
		mes "入室の準備をさせていただきますので、";
		mes "ゆっくりとお越しください。";
		close2;
		cloakonnpc "侍従ベル#ep16_01";
	}
	end;
}

prt_cas.gat,163,163,0	script	#ep16_evt_02_on	139,3,3,{
OnTouch:
	if(EP16_1QUE == 1) {
		cloakoffnpc "侍従ベル#ep16_02";
		unittalk getnpcid(0,"侍従ベル#ep16_02"),"侍従ベル : こちらです。左側の廊下を進んでください。"+strcharinfo(0)+"様。",1;
	}
	end;
}

prt_cas.gat,155,165,4	script(CLOAKED)	侍従ベル#ep16_02	967,{
	if(EP16_1QUE == 1) {
		mes "[侍従ベル]";
		mes "貴賓用の客室は";
		mes "こちらに用意されています。";
		mes "入ってすぐに見える";
		mes "^4d4dff一番最初の部屋^000000です。";
		next;
		mes "[侍従ベル]";
		mes "特別な貴賓の説明については";
		mes "ご入室された後に";
		mes "説明させていただきますので";
		mes "こちらまでお越しください。";
		close2;
		cloakonnpc "侍従ベル#ep16_02";
	}
	end;
}

prt_cas_q.gat,146,8,0	script	#ep16_evt_03_on	139,1,1,{
	if(EP16_1QUE == 1) {
		cloakoffnpc "侍従ベル#ep16_03";
		unittalk getnpcid(0,"侍従ベル#ep16_03"),"侍従ベル : こちらのお部屋になります。"+strcharinfo(0)+"様。",1;
	}
	end;
}

prt_cas_q.gat,135,10,4	script(CLOAKED)	侍従ベル#ep16_03	967,{
	if(EP16_1QUE == 1) {
		mes "[侍従ベル]";
		mes "詳しい内容につきましては";
		mes "ご入室後に";
		mes "説明させていただきます。";
		mes "どうぞ、お入りください。";
		close2;
		cloakonnpc;
	}
	end;
}

prt_cas_q.gat,26,30,3	script	侍従ベル#ep16_main	967,{
	switch(EP16_1QUE) {
	case 0:
		end;
	case 1:
		if(countitem(6933) > 0)
			delitem 6933,1;
		mes "[侍従ベル]";
		mes "ご足労いただきまして";
		mes "ありがとうございます。";
		mes "貴賓でいらっしゃる";
		mes strcharinfo(0)+ "様には";
		mes "特別に離宮の部屋を";
		mes "割り当てられています。";
		next;
		mes "[侍従ベル]";
		mes "日程につきましては、";
		mes "私がご案内しますので、";
		mes "確認の際には";
		mes "お申し付けください。";
		next;
		if(select("貴賓について聞く","よろしくお願いします") == 2) {
			mes "[侍従ベル]";
			mes "ありがとうございます。";
			mes strcharinfo(0)+ "様には";
			mes "心地よい滞在になられますよう";
			mes "尽力させていただきます。";
			next;
			mes "[侍従ベル]";
			mes "それでは、さっそく";
			mes "特別な貴賓の意味について";
			mes "説明させていただきます。";
			next;
		}
		mes "[侍従ベル]";
		mes "現在、王城で開催している";
		mes "魔王モロク討伐の祝宴は、";
		mes "アッシュバキュームへの";
		mes "遠征隊帰還を祝い、";
		mes "労うためのものですが……";
		next;
		mes "[侍従ベル]";
		mes "同時に、とても重要な";
		mes "王位継承者決定のための";
		mes "席でもあるのです。";
		next;
		mes "[侍従ベル]";
		mes "各王家から排出された";
		mes "王位継承権を持った殿下たちが";
		mes "評価を受けて、";
		mes "この祝宴の最中に";
		mes "^FF0000次の王位継承者が決定^000000";
		mes "となる予定です。";
		next;
		mes "[侍従ベル]";
		mes "そして、正式な戴冠式が行われる前に";
		mes "執行される王家だけの儀式を";
		mes "通過すれば、";
		mes "ルーンミッドガッツ王国は";
		mes "新しい国王陛下を";
		mes "迎えることになるでしょう。";
		next;
		switch(select("それと自分になんの関係が？","王家だけで執行される儀式とは")) {
		case 1:
			mes "[侍従ベル]";
			mes strcharinfo(0)+ "様は";
			mes "その、王家だけで執行される、";
			mes "次期王位継承者が";
			mes "この地に住む者に認められるために";
			mes "必要な儀式への";
			mes "立会人として招待されたのです。";
			break;
		case 2:
			mes "[侍従ベル]";
			mes "七王家の限りない栄光のために、";
			mes "そして、次期国王に選定された者が";
			mes "この地の民に";
			mes "認められるために行う";
			mes "王室だけの秘密の儀式です。";
			next;
			mes "[侍従ベル]";
			mes  strcharinfo(0)+ "様は";
			mes "その儀式の立会人として";
			mes "招待されたのです。";
			break;
		}
		next;
		mes "[侍従ベル]";
		mes "儀式の立会人は、";
		mes "各ギルドで推薦された有能な人物、";
		mes "または異世界遠征で";
		mes "輝かしい功績を立てた英雄に";
		mes "その資格を与えることにしたそうです。";
		next;
		if(checkquest(201730)) {	// 魔神殿攻略済み
			mes "[侍従ベル]";
			mes "あなたは";
			mes "魔王モロクを討伐された英雄ですから";
			mes "選ばれないほうが";
			mes "間違っているでしょうね。";
		}
		else {
			mes "[侍従ベル]";
			mes "そしてその結果、";
			mes strcharinfo(0)+ "様が";
			mes "選定されたのです。";
		}
		next;
		menu "儀式はいつ行われるんですか？",-;
		mes "[侍従ベル]";
		mes "私が今、知る限りでは";
		mes "既に継承者決定の";
		mes "最終段階のようです。";
		next;
		mes "[侍従ベル]";
		mes "先の王様が病により退位されて、";
		mes "国も、王宮も、かなり";
		mes "混乱していましたが……";
		mes "幸いにしてルーンミッドガッツ王国は";
		mes "七王家が支えている場所。";
		next;
		mes "[侍従ベル]";
		mes "もう新しい国王陛下を迎える時です。";
		next;
		mes "[侍従ベル]";
		mes "それと、立会人として";
		mes "招待されておりますので、";
		mes "祝宴に参加する前に、";
		mes "各家門を訪問して";
		mes "挨拶をしていただく必要がございます。";
		next;
		mes "[侍従ベル]";
		mes "この離宮は、各家門が";
		mes "首都プロンテラに宿泊される際に";
		mes "ご利用になる場所。";
		mes "現在、この部屋を除くと";
		mes "全て他の家門の方が滞在されています。";
		next;
		mes "[侍従ベル]";
		mes "つい先ほど、各家門に";
		mes strcharinfo(0)+ "様が";
		mes "到着されたことを伝えましたので、";
		mes "まずは^4d4dffここから近い";
		mes "^4d4dffハイネン家から訪問^000000されては";
		mes "いかがでしょうか？";
		next;
		mes "[侍従ベル]";
		mes "離宮内の案内をさせていただきますと、";
		mes "この部屋があるのは^0000FF西の離宮^000000。";
		mes "ハイネン家、ネリウス家、";
		mes "バルター家の者の部屋がございます。";
		next;
		mes "[侍従ベル]";
		mes "廊下を出て、向かいになるのが";
		mes "^0000FF東の離宮^000000です。";
		mes "ウィグナー家、リハルト家、";
		mes "ゲオルグ家、レベンブルグ家の";
		mes "お部屋がございます。";
		next;
		mes "[侍従ベル]";
		mes "各家門の方たちへの";
		mes "挨拶を決してお忘れなく。";
		delquest 7681;
		setquest 7682;
		setquest 7683;
		setquest 73051;
		setquest 73052;
		setquest 73053;
		setquest 73054;
		setquest 73055;
		setquest 73056;
		set EP16_1QUE,2;
		close;
	case 2:
		if((checkquest(7683)&0x8) && !checkquest(73051) && !checkquest(73053) && !checkquest(73052) && !checkquest(73054) && !checkquest(73055) && !checkquest(73056)) {
			mes "[侍従ベル]";
			mes "おかえりなさいませ。";
			mes "王位継承者決定が";
			mes "予定より遅れておりまして、";
			mes "しばらく時間がかかるそうです。";
			next;
			mes "[侍従ベル]";
			mes "お時間まで少し余裕が";
			mes "出来ましたので";
			mes "祝宴を楽しんで来ては";
			mes "いかがでしょうか？";
			next;
			mes "[侍従ベル]";
			mes "儀式の開始時間には、";
			mes "案内役の宮廷マジシャンが";
			mes "訪問するという連絡がきていますから、";
			mes "それまで祝宴をお楽しみください。";
			next;
			mes "[侍従ベル]";
			mes "ちょうど^4d4dffネリウス家のご令嬢が";
			mes "^4d4dff祝宴場で会うことを望んでいる^000000";
			mes "という伝言もあります。";
			mes strcharinfo(0)+"様を";
			mes "かなり気に入られたようですね。";
			delquest 7685;
			delquest 7686;
			delquest 73065;
			setquest 7687;
			set EP16_1QUE,3;
			close;
		} else {
			mes "[侍従ベル]";
			mes "つい先ほど、各家門に";
			mes strcharinfo(0)+ "様が";
			mes "到着されたと";
			mes "連絡を入れています。";
			next;
			mes "[侍従ベル]";
			mes "皆様、お待ちになってますので";
			mes "お早めにご挨拶に向かってください。";
			next;
			mes "[侍従ベル]";
			mes "まだ訪問していない家門は……";
			next;
			mes "[侍従ベル]";
			mes ( (!(checkquest(7683)&0x8)) ? "ハイネン家": "");
			mes ( (checkquest(73051)) ? "ネリウス家": "");
			mes ( (checkquest(73053)) ? "リハルト家": "");
			mes ( (checkquest(73052)) ? "バルター家": "");
			mes ( (checkquest(73054)) ? "ウィグナー家": "");
			mes ( (checkquest(73055)) ? "レベンブルグ家": "");
			mes ( (checkquest(73056)) ? "ゲオルグ家": "")+"です。";
			close;
		}
	case 3:
	case 4:
	case 5:
	case 6:
		mes "[侍従ベル]";
		mes "儀式の開始時間には、";
		mes "案内役の宮廷マジシャンが";
		mes "訪問するという連絡がきていますから、";
		mes "それまで祝宴をお楽しみください。";
		next;
		mes "[侍従ベル]";
		mes "祝宴場では";
		mes "^4d4dffネリウス家^000000の方々が";
		mes "お待ちしているとのことです。";
		close;
	case 7:
		mes "[侍従ベル]";
		mes "祝宴はいかがでしたか？";
		mes "アッシュバキュームから";
		mes "帰還された英雄たちを";
		mes "歓迎する宴ですので、";
		mes "祝宴自体は長期に渡って";
		mes "開催されるそうですよ。";
		next;
		mes "[侍従ベル]";
		mes "そういえば、先ほど";
		mes "宮廷マジシャンの訪問がありました。";
		mes "他の家門をまわった後、";
		mes "再度、この部屋に訪問すると";
		mes "申していましたので";
		mes "じき来るかと思います。";
		if(!sleep2(500)) end;
		next;
		cloakoffnpc "マジシャン・ニルレム#ep16_wiz01";
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_wiz01"),"マジシャン・ニルレム : ふうう～天才マジシャン！　ニルレムのご到着だよ～！",1;
		mes "[侍従ベル]";
		mes "おや。";
		mes "ちょうど、来たようですね。";
		mes "詳しい内容はこちらの者に";
		mes "ご質問ください。";
		delquest 7691;
		setquest 7692;
		set EP16_1QUE,8;
		next;
		mes "[ニルレム]";
		mes "やあ！";
		mes "あなたが噂の";
		mes strcharinfo(0)+"様ですね。";
		mes "お会いできてうれしいですよ！";
		next;
		mes "[ニルレム]";
		mes "お話ししたいのは";
		mes "やまやまなんですが～、";
		mes "すぐ儀式がはじまっちゃうそうですので";
		mes "さっそく移動しましょう！";
		next;
		mes "[ニルレム]";
		mes "驚かないでくださいよ。";
		mes "カウントダウンスタ～ト！";
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_wiz01"),"マジシャン・ニルレム : ３！",1;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_wiz01"),"マジシャン・ニルレム : ２！",1;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_wiz01"),"マジシャン・ニルレム : １！",1;
		if(!sleep2(500)) end;
		close2;
		cloakonnpc "マジシャン・ニルレム#ep16_wiz01";
		warp "prt_lib.gat",89,44;
		end;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		mes "[侍従ベル]";
		mes "おかえりなさい。";
		mes strcharinfo(0)+"様。";
		mes "儀式はもう終わったのでしょうか。";
		next;
		cloakoffnpc "マジシャン・ニルレム#ep16_wiz01";
		mes "[ニルレム]";
		mes "なにを言ってるんですか！";
		mes "まだ儀式は終わってないですよ！";
		next;
		mes "[侍従ベル]";
		mes "うわあ!?";
		next;
		mes "[ニルレム]";
		mes "急いで戻りますよ。";
		mes "心の準備はよろしいですね？";
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_wiz01"),"マジシャン・ニルレム : ３！",1;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_wiz01"),"マジシャン・ニルレム : ２！",1;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"マジシャン・ニルレム#ep16_wiz01"),"マジシャン・ニルレム : １！",1;
		if(!sleep2(500)) end;
		close2;
		cloakonnpc "マジシャン・ニルレム#ep16_wiz01";
		warp "prt_lib.gat",89,44;
		end;
	case 14:
		mes "[侍従ベル]";
		mes "おかえりなさいませ。";
		mes strcharinfo(0)+"様が";
		mes "ご不在の間に伝言を";
		mes "預かっております。";
		next;
		mes "[侍従ベル]";
		mes "『重要な会議を行う、";
		mes "　それまで待機しているように。";
		mes "　全てが決定したら";
		mes "　早急に知らせる。";
		mes "　それまで祝宴を楽しみなさい』";
		mes "……とのことです。";
		next;
		mes "[侍従ベル]";
		mes "それとは、別件でしょうか？";
		mes "^4d4dffハイネン家^000000の部屋に";
		mes "医者と司祭の方たちが";
		mes "あわただしく出入りしているのを";
		mes "見てしまいました。";
		next;
		mes "[侍従ベル]";
		mes "なにかあったのでしょうか？";
		next;
		if(select("……","内緒です")==2) {
			mes "[侍従ベル]";
			mes "内緒……ですか。";
			next;
		}
		mes "[侍従ベル]";
		mes "ハッ！　失礼しました。";
		mes "差し出がましい質問でしたね。";
		mes "申し訳ありません。";
		next;
		mes "[侍従ベル]";
		mes "えっと……そうだ！";
		mes "もう一つ伝言を預かってました！";
		next;
		mes "[侍従ベル]";
		mes "^4d4dffネリウス家^000000のご令嬢から";
		mes "ティータイムの招待が来ています。";
		next;
		mes "[侍従ベル]";
		mes strcharinfo(0)+"様が";
		mes "お戻りになったら、";
		mes "連絡を入れてくれと";
		mes "承っております。";
		mes "直ちにお返事しましょうか？";
		next;
		if(select("すぐに訪問する","後で訪問する")==2) {
			mes "[侍従ベル]";
			mes "それでは訪問される時に";
			mes "お知らせください。";
			close;
		}
		mes "[侍従ベル]";
		mes "それでは今から向かうと";
		mes "お伝えしておきましょう。";
		mes "行っていらっしゃいませ。";
		delquest 7696;
		setquest 7697;
		set EP16_1QUE,15;
		close;
	case 15:
		mes "[侍従ベル]";
		mes "ネリウス家のお部屋は、";
		mes "この部屋から二つ隣りになります。";
		mes "ハイネン家のお隣りです。";
		next;
		mes "[侍従ベル]";
		mes strcharinfo(0)+"様の";
		mes "訪問を伝えてありますので";
		mes "いつでもお訪ねください。";
		close;
	case 16:
		mes "[侍従ベル]";
		mes "ハイネン家から";
		mes "面会の要請がありました。";
		mes "お戻りになったら、";
		mes "ハイネン家を訪ねてください。";
		mes "という連絡でした。";
		close;
	case 17:
		mes "[侍従ベル]";
		mes "おかえりなさいませ。";
		mes "お戻りになりましたので";
		mes "ニルレム様をお呼びします。";
		next;
		mes "[侍従ベル]";
		mes "それがですね……";
		mes "宮廷マジシャンのニルレム様が";
		mes "先ほど、この部屋に";
		mes "飛び込んできまして。";
		next;
		mes "[侍従ベル]";
		mes "すぐに「どこに行った!?」と";
		mes "部屋を去られたので、";
		mes strcharinfo(0)+"様を";
		mes "探していたのだと思います。";
		next;
		cloakoffnpc "マジシャン・ニルレム#ep16_wiz01";
		mes "[ニルレム]";
		mes "天才！　宮廷マジシャン";
		mes "ニルレム参上！";
		next;
		mes "[侍従ベル]";
		mes "……ちょ、ちょうど良い";
		mes "タイミングでしたね。";
		close;
	default:
		mes "[侍従ベル]";
		mes strcharinfo(0)+"様、";
		mes "このベルめに";
		mes "御用でしょうか？";
		next;
		if(select("ニルレムを呼ぶ","何でもないです")==2) {
			mes "[侍従ベル]";
			mes "わかりました。";
			close;
		}
		mes "[侍従ベル]";
		mes "宮廷マジシャン、ニルレム様を";
		mes "お呼びするのですね？";
		mes "少々お待ちください。";
		next;
		mes "[侍従ベル]";
		mes "今、お呼びしましたので";
		mes "すぐいらっしゃると思います。";
		next;
		cloakoffnpc "マジシャン・ニルレム#ep16_wiz01";
		mes "[ニルレム]";
		mes "天才！　宮廷マジシャン";
		mes "ニルレム参上！";
		mes "お呼び出しありがとうございます。";
		mes "そんなにも私に会いたかったんですね！";
		close;
	}
	end;
}

prt_cas_q.gat,28,28,3	script(CLOAKED)	マジシャン・ニルレム#ep16_wiz01	735,{
	if(EP16_1QUE == 17) {
		mes "[ニルレム]";
		mes "はぁい！";
		mes "ダーリンお待たせ～";
		next;
		menu "……",-;
		mes "[ニルレム]";
		mes "あれっはずしちゃった？";
		next;
		mes "[ニルレム]";
		mes "だって、ルーンミッドガッツ王国の";
		mes "しかも、王家の！";
		mes "秘密を調査するっていわれて";
		mes "興奮しないマジシャンが";
		mes "この世のどこにいるんですか？";
		mes "そうですよね？";
		next;
		mes "[ニルレム]";
		mes "冒険にもでない！";
		mes "書類仕事と社交戦争だらけ！";
		mes "貴族しかない退屈な宮廷！";
		next;
		mes "[ニルレム]";
		mes "だったけど、私は";
		mes "宮廷マジシャンになって";
		mes "本当に良かったと思ってます今！";
		mes "王室最高！";
		next;
		mes "[ニルレム]";
		mes "やー、宮廷マジシャンの職は";
		mes "安定していて、給料も低くなくて";
		mes "異世界への留学費も";
		mes "支援してもらえるんですよ。";
		mes "今の事態になるまで";
		mes "退屈な職場だったけど！";
		next;
		mes "[ニルレム]";
		mes "と、職業の話はここまでにして～";
		next;
		mes "[ニルレム]";
		mes "準備はすべて終わりましたよ。";
		mes "例の歪みは王家の記憶の間から";
		mes "現れたので";
		mes "ゲートもそっちに設置しました。";
		next;
		mes "[ニルレム]";
		mes "それと、今後は";
		mes "^4d4dff王家の記憶の間に直接向かわれるか^000000、";
		mes "この^4d4dffニルレム呼び出し券^000000を";
		mes "使ってください。";
		mes "これはサービスですからね！";
		next;
		menu "ニルレム呼び出し券？",-;
		mes "[ニルレム]";
		mes "はい、このニルレムに会いたい時は";
		mes "いつでもここの侍従を通じて";
		mes "呼び出してくださいという話です。";
		mes "すぐに来てあげますから！";
		set EP16_1QUE,18;
		next;
		mes "[ニルレム]";
		mes "さあ、それでは行きますか？";
		next;
		if(select("移動する","準備が必要だ")==2) {
			mes "[ニルレム]";
			mes "でしたら、準備が終わり次第";
			mes "お呼びくださ～い。";
			mes "もし私が現れなかったら、";
			mes "すぐ^4d4dff王家の記憶の間^000000に来てくださいね。";
			next;
			mes "[ニルレム]";
			mes "道は知ってますもんね。";
			mes "ははは。";
			close;
		}
		mes "[ニルレム]";
		mes "それじゃ目を瞑って～";
		mes "はい！";
		close2;
		warp "prt_lib.gat",89,44;
		end;
	} else if(EP16_1QUE > 17) {
		mes "[ニルレム]";
		mes "それじゃ";
		mes "王家の記憶の間に";
		mes "出発しますか？";
		next;
		if(select("王家の記憶の間に出発","必要ない！")==2) {
			mes "[ニルレム]";
			mes "道は知ってますもんね。";
			mes "ははは。";
			close;
		}
		mes "[ニルレム]";
		mes "それじゃ目を瞑って～";
		mes "はい！";
		close2;
		warp "prt_lib.gat",89,44;
		end;
	}
	end;
}

prt_cas.gat,197,164,0	script	#ep16_evt_7688	139,3,3,{
OnTouch:
	if(EP16_1QUE == 3) {
		mes "["+strcharinfo(0)+"]";
		mes "（誰かの話し声が聞こえる）";
		next;
		cloakoffnpc "怪しいお客#ep16_01";
		cloakoffnpc "侍従#ep16_01";
		mes "[怪しいお客]";
		mes "先ほどの話は確かだな？";
		next;
		mes "[侍従]";
		mes "もちろんです。";
		mes "お探しの条件に";
		mes "ぴったり当てはまるはずですよ。";
		next;
		mes "[怪しいお客]";
		mes "ふむ……";
		next;
		mes "[侍従]";
		mes "彼もまた王位継承権を持っているお方。";
		mes "求めている情報は";
		mes "十分得られます。";
		next;
		mes "[怪しいお客]";
		mes "準備は？";
		mes "進んでいるのか？";
		mes "……その男に怪しまれないよう";
		mes "呼び出さなければいかんぞ。";
		next;
		mes "[侍従]";
		mes "もちろんです。";
		mes "……しかし、詳細はまた後ほど。";
		next;
		mes "[侍従]";
		mes "そろそろ祝宴に参加しなければ";
		mes "いけませんから。";
		next;
		mes "[怪しいお客]";
		mes "そうだな。";
		mes "では、後で会おう。";
		mes "　";
		mes "私を失望させないでくれよ。";
		cloakonnpc "怪しいお客#ep16_01";
		next;
		mes "[侍従]";
		mes "……";
		mes "面倒くさい人だな……";
		cloakonnpc "侍従#ep16_01";
		next;
		mes "‐不本意ながら";
		mes "　おかしな話を聞いてしまったようだ‐";
		delquest 7687;
		setquest 7688;
		set EP16_1QUE,4;
		close;
	}
	end;
}

prt_cas.gat,197,155,6	script(CLOAKED)	怪しいお客#ep16_01	865,{}

prt_cas.gat,199,154,2	script(CLOAKED)	侍従#ep16_01	47,{}

prt_cas.gat,106,240,3	script	スピーカ・ネリウス#ep16_02	10115,{
	if(EP16_1QUE < 3) {
		unittalk "スピーカ : ……失礼。",1;
		end;
	} else if(EP16_1QUE == 3) {
		cutin "ep16_spica_nerius01.bmp",2;
		mes "[スピーカ]";
		mes "他の家門の方とは";
		mes "普段はお会いすることが";
		mes "なかなか難しいのです。";
		close2;
		cutin "ep16_spica_nerius01.bmp",255;
		end;
	} else if(EP16_1QUE == 4) {
		cloakoffnpc "スピーカ・ネリウス#ep16_02";
		cloakoffnpc "クルックス#ep16_02";
		mes "[スピーカ]";
		mes "お待ちしておりました。";
		mes strcharinfo(0)+"様。";
		mes "ことづてはうまく";
		mes "伝わったようですね。";
		cutin "ep16_spica_nerius01.bmp",2;
		next;
		mes "[スピーカ]";
		mes "魔王モロク討伐のために";
		mes "貢献した冒険者。";
		mes "凄まじい活躍だったと聞いています。";
		next;
		menu "いえいえ",-;
		mes "[スピーカ]";
		mes "ですが事実ではありませんか。";
		mes "この場は貴方のような";
		mes "英雄の為の祝宴です。";
		mes "自信をお持ちになってください。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "そうです！";
		mes "そして、私たちと一緒に";
		mes "居るからといって";
		mes "誰も文句を言えませんから";
		mes "いつでも訪問して下さい。";
		next;
		mes "[スキア]";
		mes "私たちだけなのも久しぶりなので";
		mes "もう少し羽を伸ばしたいですし。";
		next;
		cutin "ep16_spica_nerius07.bmp",2;
		mes "[スピーカ]";
		mes "……ふっふっふ";
		next;
		mes "[スピーカ]";
		mes "口止めは私に任せておけ。";
		mes "クルックス、聞いたか？";
		mes "私の半身が遊びたいと言っている。";
		next;
		cutin "ep16_crux_findel03.bmp",2;
		mes "[クルックス]";
		mes "いや、あのお嬢様達？";
		mes "私に何をどうしろと？";
		next;
		mes "[クルックス]";
		mes "私はどこまでもお嬢様達の";
		mes "味方なのはご存知ですよね？";
		next;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "面白い冗談だな。";
		mes "今回、貴様が私達の";
		mes "監視役として来たのは";
		mes "知っているぞ？";
		next;
		cutin "ep16_crux_findel03.bmp",2;
		mes "[クルックス]";
		mes "違います！";
		mes "違うんですよ！";
		mes "……あれ？　あちらに居るのは";
		mes "ハイネン様ではありませんか？";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "あっ、本当だ。";
		mes "ニーヒル！　こっちです！";
		next;
		cloakoffnpc "ニーヒル・ハイネン#ep16_02";
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "そんなに大きな声で";
		mes "呼ばなくてもいいよ、スキア。";
		mes strcharinfo(0)+"様も";
		mes "一緒でしたか。";
		next;
		mes "[ニーヒル]";
		mes "確かにネリウス家門なら";
		mes "一緒に居ても変な誤解を";
		mes "受けたりはしない。";
		mes "賢明な判断だ。";
		next;
		cutin "ep16_spica_nerius06.bmp",0;
		mes "[スピーカ]";
		mes "スキア。";
		mes "そしてハイネン家の方。";
		mes "いつから互いに名前を呼び合う";
		mes "仲になったんだ？";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "先ほど廊下で会った時に";
		mes "名前で呼び合うようにしましたよ。";
		mes "離宮でハイネン家とネリウス家は";
		mes "並んでいますから。";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "お蔭で気分転換も出来たし、";
		mes "君には感謝している。";
		mes "そして……";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes strcharinfo(0)+"様には";
		mes "謝罪をしなければと思い、";
		mes "部屋に訪ねてみたら";
		mes "すでに祝宴場に向かったと。";
		next;
		menu "謝罪？",-;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "先ほどは……";
		mes "感情を抑える事ができず、";
		mes "無礼を働いてしまいました。";
		mes "どうかお許しを。";
		next;
		cloakoffnpc "ビオルレター・ハイネン#ep16_02";
		cutin "ep16_nihi_miseria_heine01.bmp",255;
		mes "[酒に酔った女性]";
		mes "あは……ははは……！";
		mes "ニーヒル様、ああ可哀そうに";
		mes "なんとまあ王位継承者にも";
		mes "推されていたのに……";
		next;
		mes "[酒に酔った女性]";
		mes "あれ、これはこれは。";
		mes "著名な女系家門である";
		mes "ネリウスの御令嬢じゃな～い？";
		next;
		mes "[酒に酔った女性]";
		mes "ニーヒル様。";
		mes "ついに家門も見捨てて";
		mes "ネリウス家に行ってしまう";
		mes "つもりなのですか？";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",2;
		mes "[ニーヒル]";
		mes "ビオルレター、";
		mes "なんなんだ、その無礼は！";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",255;
		mes "[ビオルレター]";
		mes "間違った事は言っていませんよ。";
		mes "そうでしょう？";
		mes "家門の中での待遇は最悪。";
		mes "ここで令嬢を手籠めにすれば";
		mes "第２の人生到来！　な～んてね？";
		mes "きゃはははは～！";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",2;
		mes "[ニーヒル]";
		mes "いい加減にしろ！";
		mes "邪推にもほどがあるぞ。";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",255;
		mes "[ビオルレター]";
		mes "あらあら～ニーヒル様も";
		mes "怒ったりするのね？";
		mes "そうです。そうやって";
		mes "感情をもっと表現して……";
		next;
		cutin "ep16_crux_findel01.bmp",2;
		mes "[クルックス]";
		mes "どの家門の令嬢なのかは";
		mes "存じておりませんが、";
		mes "その辺にしていただけませんか？";
		mes "お嬢様にこれ以上、";
		mes "侮辱的な発言をするなら";
		mes "こちらにも考えがあります。";
		next;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "黙っていろ、クルックス。";
		mes "自分の行動の意味さえ解さぬ";
		mes "浅はかな者と私を";
		mes "同列にするつもりか？";
		mes "このような事でハイネン家の";
		mes "恨みを買うつもりはない。";
		next;
		cutin "ep16_spica_nerius07.bmp",2;
		mes "[スピーカ]";
		mes "そうだと思いませんか？";
		mes "ビオルレター・コラト・ハイネン様？";
		next;
		mes "[スピーカ]";
		mes "彼に対する貴方の気持ちは";
		mes "十分理解いたしました。";
		mes "しかし、ここで騒いだところで";
		mes "泥を塗られるのはハイネン家ですよ？";
		next;
		mes "[スピーカ]";
		mes "彼のスキャンダルをお望みなら";
		mes "どうぞ勝手になさってください。";
		mes "ただし、ネリウス家を";
		mes "巻き込まないでくださいね？";
		cutin "ep16_spica_nerius02.bmp",2;
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",2;
		mes "[ニーヒル]";
		mes "今回は見逃してやるから";
		mes "すぐに戻れ。";
		mes "さもないと傍系の人間とはいえ";
		mes "家門の名でお前を罰するしかない。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",255;
		mes "[ビオルレター]";
		mes "分かりました。戻りますよ。";
		mes "ネリウス家にでも何処でも";
		mes "好きに行って下さい！";
		next;
		cloakonnpc "ビオルレター・ハイネン#ep16_02";
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "いや……";
		mes "どうしてそんな話に……？";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "面目ありません。";
		mes "あの者の無礼については";
		mes "私が代わって謝罪致します。";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "先ほどから謝罪ばかりですね。";
		mes "ニーヒルは悪くないのに……";
		next;
		cutin "ep16_spica_nerius01.bmp",1;
		mes "[スピーカ]";
		mes "確かにニーヒル様は悪くない。";
		mes "だがな……";
		mes "望もうと望まざろうと";
		mes "家門の名を背負うのならば、";
		mes "全ての責任を負う事になる。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "その通りだ。";
		mes "私はハイネン家の名を";
		mes "背負って生きている。";
		mes "ハイネンの全てに対して";
		mes "責任を取らなければならない立場だ。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "スキア、君が影になる理由と同じだ。";
		cloakoffnpc "王宮侍従#ep16_02";
		unittalk getnpcid(0,"王宮侍従#ep16_02"),"王宮侍従 : 度数の低い葡萄酒です。いかがですか？",1;
		next;
		unittalk getnpcid(0,"ニーヒル・ハイネン#ep16_02"),"ニーヒル : 頂きましょう。",1;
		unittalk getnpcid(0,"スキア・ネリウス#ep16_02"),"スキア : 私も一杯下さい。",1;
		cutin "ep16_spica_nerius01.bmp",1;
		mes "[スピーカ]";
		mes "事件はどうあれ家門の方からも";
		mes "あのような仕打ちを受けているとは";
		mes "知らなった……";
		next;
		cloakonnpc "王宮侍従#ep16_02";
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "祝宴の良い雰囲気を";
		mes "私が全部壊してしまったようだ。";
		mes "私はこれで失礼します。";
		mes "いつか機会があれば";
		mes "また話をしましょう。";
		next;
		cutin "ep16_spica_nerius05.bmp",1;
		mes "[スピーカ]";
		mes "いえ。こちらこそ、";
		mes "次は正式に招待を致します。";
		mes "その時、断らないでください。";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "ネリウス家次期当主の招待を";
		mes "断るわけがありませんよ。";
		mes "それではまた。";
		next;
		cloakonnpc "ニーヒル・ハイネン#ep16_02";
		cutin "ep16_spica_nerius01.bmp",2;
		mes "[スピーカ]";
		mes "ふむ……";
		mes "うむ……";
		mes "スキア、その葡萄酒を";
		mes "ちょっと見せてくれ。";
		next;
		cutin "ep16_spica_nerius02.bmp",2;
		mes "[スピーカ]";
		mes "そして、クルックス。";
		mes "飲料を渡した侍従について";
		mes "隠密に調べてくれ。";
		mes "気取られるなよ。";
		unittalk getnpcid(0,"クルックス#ep16_02"),"クルックス : かしこまりました、お嬢様。",1;
		next;
		mes "[スピーカ]";
		mes "他の者の目は騙せても、";
		mes "私の目は騙せないさ。";
		mes strcharinfo(0)+"様も";
		mes "よく見てくれ。";
		mes "おかしいだろう？";
		next;
		menu "また、口調が変わりましたね",-;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "ん、この口調か？";
		mes "私は元々命令調で話す事に";
		mes "慣れている身だ。";
		mes "貴賓なので丁寧な言葉遣いを";
		mes "心がけてはいたのだが、";
		mes "不慣れゆえに辛くてな。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "た、大変！";
		mes "ニーヒルの様子が……！";
		mes "まるで泥酔しているみたいに！";
		next;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "彼が飲んだ葡萄酒、";
		mes "ジュースに間違うほどに";
		mes "度数が低いものだったが";
		mes "それだけで酔ったとは思えない。";
		mes "何かある気がするな……";
		next;
		cutin "ep16_spica_nerius05.bmp",2;
		mes "[スピーカ]";
		mes strcharinfo(0)+"。";
		mes "面白そうな事が起こると思わないか？";
		mes "ああ……怪しい。怪しい。";
		mes "怪しいから私たちはもうこれで";
		mes "戻る事にしよう。";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "ええ？　そのまま行っちゃうの？";
		mes "ニーヒルはどこか痛いんじゃ？";
		mes "途中で倒れたらどうするの？";
		next;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "そこまで気になるなら";
		mes "介抱しに行ってやればいい。";
		mes "私のことはクルックスが";
		mes "守ってくれるから大丈夫。";
		unittalk getnpcid(0,"スピーカ・ネリウス#ep16_02"),"スピーカ : クルックス、部屋に戻ろう。",1;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"クルックス#ep16_02"),"クルックス : はい、お嬢様。",1;
		next;
		cloakonnpc "スピーカ・ネリウス#ep16_02";
		cloakonnpc "クルックス#ep16_02";
		mes "[スキア]";
		mes "あの……冒険者様？";
		mes "冒険者様が先に行っては";
		mes "ダメですか？";
		mes "私がここで駆け寄っては";
		mes "みんな変な目で見ると思います。";
		cutin "ep16_skia_nerius01.bmp",0;
		next;
		mes "[スキア]";
		mes "私はバレないように";
		mes "ついて行ってみます。";
		mes "スピーカは何かに気づいて";
		mes "あんな事を言ったんだと思います。";
		mes "きっと何かあります。";
		next;
		if(select("仕方ないですね……","ニーヒルに近づくチャンスですよ") == 2) {
			mes "[スキア]";
			mes "に、ニーヒルに……！";
			mes "冒険者様っ、誤解しないでください！";
			mes "わ、私は心配なだけです！";
			cutin "ep16_skia_nerius02.bmp",0;
			next;
		}
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "ニーヒルは祝宴場の";
		mes "外に出たはずです。";
		mes "きっと離宮に向かったはずなので";
		mes "そっちに行ってみましょう！";
		delquest 7688;
		setquest 7689;
		set EP16_1QUE,5;
		close2;
		cutin "ep16_crux_findel03.bmp",255;
		end;
	} else if(EP16_1QUE == 5) {
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "ニーヒルは祝宴場の";
		mes "外に出たはずです。";
		mes "きっと離宮に向かったはずなので";
		mes "そっちに行ってみましょう！";
		close2;
		cutin "ep16_crux_findel03.bmp",255;
		end;
	} else {
		cutin "ep16_spica_nerius02.bmp",2;
		mes "[スピーカ]";
		mes "面白そうな事が起こると思わないか？";
		mes "ああ……怪しい。怪しい。";
		close2;
		cutin "ep16_spica_nerius02.bmp",255;
		end;
	}
}

prt_cas.gat,104,240,5	script	スキア・ネリウス#ep16_02	10116,{
	if(EP16_1QUE < 3) {
		unittalk "スキア : ……",1;
		end;
	} else if(EP16_1QUE == 3) {
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes strcharinfo(0)+"様";
		mes "祝宴はどうですか？";
		mes "私はこのような祝宴は初めてなので";
		mes "少し緊張してしまって……";
		next;
		mes "[スキア]";
		mes "あ、決して祝宴が初めて";
		mes "という意味ではなく……";
		mes "何と説明すればいいかな。";
		next;
		cutin "ep16_spica_nerius01.bmp",2;
		mes "[スピーカ]";
		mes "説明する必要はない。";
		mes "私たち家門内の事だ。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "そうですね。";
		mes "余計な事を言いました。";
		mes "大変失礼致しました。";
		close2;
		cutin "ep16_crux_findel03.bmp",255;
		end;
	} else if(EP16_1QUE == 4) {
		cloakoffnpc "スピーカ・ネリウス#ep16_02";
		cloakoffnpc "クルックス#ep16_02";
		mes "[スピーカ]";
		mes "お待ちしておりました。";
		mes strcharinfo(0)+"様。";
		mes "ことづてはうまく";
		mes "伝わったようですね。";
		cutin "ep16_spica_nerius01.bmp",2;
		next;
		mes "[スピーカ]";
		mes "魔王モロク討伐のために";
		mes "貢献した冒険者。";
		mes "凄まじい活躍だったと聞いています。";
		next;
		menu "いえいえ",-;
		mes "[スピーカ]";
		mes "ですが事実ではありませんか。";
		mes "この場は貴方のような";
		mes "英雄の為の祝宴です。";
		mes "自信をお持ちになってください。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "そうです！";
		mes "そして、私たちと一緒に";
		mes "居るからといって";
		mes "誰も文句を言えませんから";
		mes "いつでも訪問して下さい。";
		next;
		mes "[スキア]";
		mes "私たちだけなのも久しぶりなので";
		mes "もう少し羽を伸ばしたいですし。";
		next;
		cutin "ep16_spica_nerius07.bmp",2;
		mes "[スピーカ]";
		mes "……ふっふっふ";
		next;
		mes "[スピーカ]";
		mes "口止めは私に任せておけ。";
		mes "クルックス、聞いたか？";
		mes "私の半身が遊びたいと言っている。";
		next;
		cutin "ep16_crux_findel03.bmp",2;
		mes "[クルックス]";
		mes "いや、あのお嬢様達？";
		mes "私に何をどうしろと？";
		next;
		mes "[クルックス]";
		mes "私はどこまでもお嬢様達の";
		mes "味方なのはご存知ですよね？";
		next;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "面白い冗談だな。";
		mes "今回、貴様が私達の";
		mes "監視役として来たのは";
		mes "知っているぞ？";
		next;
		cutin "ep16_crux_findel03.bmp",2;
		mes "[クルックス]";
		mes "違います！";
		mes "違うんですよ！";
		mes "……あれ？　あちらに居るのは";
		mes "ハイネン様ではありませんか？";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "あっ、本当だ。";
		mes "ニーヒル！　こっちです！";
		next;
		cloakoffnpc "ニーヒル・ハイネン#ep16_02";
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "そんなに大きな声で";
		mes "呼ばなくてもいいよ、スキア。";
		mes strcharinfo(0)+"様も";
		mes "一緒でしたか。";
		next;
		mes "[ニーヒル]";
		mes "確かにネリウス家門なら";
		mes "一緒に居ても変な誤解を";
		mes "受けたりはしない。";
		mes "賢明な判断だ。";
		next;
		cutin "ep16_spica_nerius06.bmp",0;
		mes "[スピーカ]";
		mes "スキア。";
		mes "そしてハイネン家の方。";
		mes "いつから互いに名前を呼び合う";
		mes "仲になったんだ？";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "先ほど廊下で会った時に";
		mes "名前で呼び合うようにしましたよ。";
		mes "離宮でハイネン家とネリウス家は";
		mes "並んでいますから。";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "お蔭で気分転換も出来たし、";
		mes "君には感謝している。";
		mes "そして……";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes strcharinfo(0)+"様には";
		mes "謝罪をしなければと思い、";
		mes "部屋に訪ねてみたら";
		mes "すでに祝宴場に向かったと。";
		next;
		menu "謝罪？",-;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "先ほどは……";
		mes "感情を抑える事ができず、";
		mes "無礼を働いてしまいました。";
		mes "どうかお許しを。";
		next;
		cloakoffnpc "ビオルレター・ハイネン#ep16_02";
		cutin "ep16_nihi_miseria_heine01.bmp",255;
		mes "[酒に酔った女性]";
		mes "あは……ははは……！";
		mes "ニーヒル様、ああ可哀そうに";
		mes "なんとまあ王位継承者にも";
		mes "推されていたのに……";
		next;
		mes "[酒に酔った女性]";
		mes "あれ、これはこれは。";
		mes "著名な女系家門である";
		mes "ネリウスの御令嬢じゃな～い？";
		next;
		mes "[酒に酔った女性]";
		mes "ニーヒル様。";
		mes "ついに家門も見捨てて";
		mes "ネリウス家に行ってしまう";
		mes "つもりなのですか？";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",2;
		mes "[ニーヒル]";
		mes "ビオルレター、";
		mes "なんなんだ、その無礼は！";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",255;
		mes "[ビオルレター]";
		mes "間違った事は言っていませんよ。";
		mes "そうでしょう？";
		mes "家門の中での待遇は最悪。";
		mes "ここで令嬢を手籠めにすれば";
		mes "第２の人生到来！　な～んてね？";
		mes "きゃはははは～！";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",2;
		mes "[ニーヒル]";
		mes "いい加減にしろ！";
		mes "邪推にもほどがあるぞ。";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",255;
		mes "[ビオルレター]";
		mes "あらあら～ニーヒル様も";
		mes "怒ったりするのね？";
		mes "そうです。そうやって";
		mes "感情をもっと表現して……";
		next;
		cutin "ep16_crux_findel01.bmp",2;
		mes "[クルックス]";
		mes "どの家門の令嬢なのかは";
		mes "存じておりませんが、";
		mes "その辺にしていただけませんか？";
		mes "お嬢様にこれ以上、";
		mes "侮辱的な発言をするなら";
		mes "こちらにも考えがあります。";
		next;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "黙っていろ、クルックス。";
		mes "自分の行動の意味さえ解さぬ";
		mes "浅はかな者と私を";
		mes "同列にするつもりか？";
		mes "このような事でハイネン家の";
		mes "恨みを買うつもりはない。";
		next;
		cutin "ep16_spica_nerius07.bmp",2;
		mes "[スピーカ]";
		mes "そうだと思いませんか？";
		mes "ビオルレター・コラト・ハイネン様？";
		next;
		mes "[スピーカ]";
		mes "彼に対する貴方の気持ちは";
		mes "十分理解いたしました。";
		mes "しかし、ここで騒いだところで";
		mes "泥を塗られるのはハイネン家ですよ？";
		next;
		mes "[スピーカ]";
		mes "彼のスキャンダルをお望みなら";
		mes "どうぞ勝手になさってください。";
		mes "ただし、ネリウス家を";
		mes "巻き込まないでくださいね？";
		cutin "ep16_spica_nerius02.bmp",2;
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",2;
		mes "[ニーヒル]";
		mes "今回は見逃してやるから";
		mes "すぐに戻れ。";
		mes "さもないと傍系の人間とはいえ";
		mes "家門の名でお前を罰するしかない。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",255;
		mes "[ビオルレター]";
		mes "分かりました。戻りますよ。";
		mes "ネリウス家にでも何処でも";
		mes "好きに行って下さい！";
		next;
		cloakonnpc "ビオルレター・ハイネン#ep16_02";
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "いや……";
		mes "どうしてそんな話に……？";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "面目ありません。";
		mes "あの者の無礼については";
		mes "私が代わって謝罪致します。";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "先ほどから謝罪ばかりですね。";
		mes "ニーヒルは悪くないのに……";
		next;
		cutin "ep16_spica_nerius01.bmp",1;
		mes "[スピーカ]";
		mes "確かにニーヒル様は悪くない。";
		mes "だがな……";
		mes "望もうと望まざろうと";
		mes "家門の名を背負うのならば、";
		mes "全ての責任を負う事になる。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "その通りだ。";
		mes "私はハイネン家の名を";
		mes "背負って生きている。";
		mes "ハイネンの全てに対して";
		mes "責任を取らなければならない立場だ。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "スキア、君が影になる理由と同じだ。";
		cloakoffnpc "王宮侍従#ep16_02";
		unittalk getnpcid(0,"王宮侍従#ep16_02"),"王宮侍従 : 度数の低い葡萄酒です。いかがですか？",1;
		next;
		unittalk getnpcid(0,"ニーヒル・ハイネン#ep16_02"),"ニーヒル : 頂きましょう。",1;
		unittalk getnpcid(0,"スキア・ネリウス#ep16_02"),"スキア : 私も一杯下さい。",1;
		cutin "ep16_spica_nerius01.bmp",1;
		mes "[スピーカ]";
		mes "事件はどうあれ家門の方からも";
		mes "あのような仕打ちを受けているとは";
		mes "知らなった……";
		next;
		cloakonnpc "王宮侍従#ep16_02";
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "祝宴の良い雰囲気を";
		mes "私が全部壊してしまったようだ。";
		mes "私はこれで失礼します。";
		mes "いつか機会があれば";
		mes "また話をしましょう。";
		next;
		cutin "ep16_spica_nerius05.bmp",1;
		mes "[スピーカ]";
		mes "いえ。こちらこそ、";
		mes "次は正式に招待を致します。";
		mes "その時、断らないでください。";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "ネリウス家次期当主の招待を";
		mes "断るわけがありませんよ。";
		mes "それではまた。";
		next;
		cloakonnpc "ニーヒル・ハイネン#ep16_02";
		cutin "ep16_spica_nerius01.bmp",2;
		mes "[スピーカ]";
		mes "ふむ……";
		mes "うむ……";
		mes "スキア、その葡萄酒を";
		mes "ちょっと見せてくれ。";
		next;
		cutin "ep16_spica_nerius02.bmp",2;
		mes "[スピーカ]";
		mes "そして、クルックス。";
		mes "飲料を渡した侍従について";
		mes "隠密に調べてくれ。";
		mes "気取られるなよ。";
		unittalk getnpcid(0,"クルックス#ep16_02"),"クルックス : かしこまりました、お嬢様。",1;
		next;
		mes "[スピーカ]";
		mes "他の者の目は騙せても、";
		mes "私の目は騙せないさ。";
		mes strcharinfo(0)+"様も";
		mes "よく見てくれ。";
		mes "おかしいだろう？";
		next;
		menu "また、口調が変わりましたね",-;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "ん、この口調か？";
		mes "私は元々命令調で話す事に";
		mes "慣れている身だ。";
		mes "貴賓なので丁寧な言葉遣いを";
		mes "心がけてはいたのだが、";
		mes "不慣れゆえに辛くてな。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "た、大変！";
		mes "ニーヒルの様子が……！";
		mes "まるで泥酔しているみたいに！";
		next;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "彼が飲んだ葡萄酒、";
		mes "ジュースに間違うほどに";
		mes "度数が低いものだったが";
		mes "それだけで酔ったとは思えない。";
		mes "何かある気がするな……";
		next;
		cutin "ep16_spica_nerius05.bmp",2;
		mes "[スピーカ]";
		mes strcharinfo(0)+"。";
		mes "面白そうな事が起こると思わないか？";
		mes "ああ……怪しい。怪しい。";
		mes "怪しいから私たちはもうこれで";
		mes "戻る事にしよう。";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "ええ？　そのまま行っちゃうの？";
		mes "ニーヒルはどこか痛いんじゃ？";
		mes "途中で倒れたらどうするの？";
		next;
		cutin "ep16_spica_nerius06.bmp",2;
		mes "[スピーカ]";
		mes "そこまで気になるなら";
		mes "介抱しに行ってやればいい。";
		mes "私のことはクルックスが";
		mes "守ってくれるから大丈夫。";
		unittalk getnpcid(0,"スピーカ・ネリウス#ep16_02"),"スピーカ : クルックス、部屋に戻ろう。",1;
		unittalk getnpcid(0,"クルックス#ep16_02"),"クルックス : はい、お嬢様。",1;
		next;
		cloakonnpc "スピーカ・ネリウス#ep16_02";
		cloakonnpc "クルックス#ep16_02";
		mes "[スキア]";
		mes "あの……冒険者様？";
		mes "冒険者様が先に行っては";
		mes "ダメですか？";
		mes "私がここで駆け寄っては";
		mes "みんな変な目で見ると思います。";
		cutin "ep16_skia_nerius01.bmp",0;
		next;
		mes "[スキア]";
		mes "私はバレないように";
		mes "ついて行ってみます。";
		mes "スピーカは何かに気づいて";
		mes "あんな事を言ったんだと思います。";
		mes "きっと何かあります。";
		next;
		if(select("仕方ないですね……","ニーヒルに近づくチャンスですよ") == 2) {
			mes "[スキア]";
			mes "に、ニーヒルに……！";
			mes "冒険者様っ、誤解しないでください！";
			mes "わ、私は心配なだけです！";
			cutin "ep16_skia_nerius02.bmp",0;
			next;
		}
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "ニーヒルは祝宴場の";
		mes "外に出たはずです。";
		mes "きっと離宮に向かったはずなので";
		mes "そっちに行ってみましょう！";
		delquest 7688;
		setquest 7689;
		set EP16_1QUE,5;
		close2;
		cutin "ep16_crux_findel03.bmp",255;
		end;
	} else if(EP16_1QUE == 5) {
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "ニーヒルは祝宴場の";
		mes "外に出たはずです。";
		mes "きっと離宮に向かったはずなので";
		mes "そっちに行ってみましょう！";
		close2;
		cutin "ep16_crux_findel03.bmp",255;
		end;
	} else {
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "……胸騒ぎがします。";
		mes "悪いことが起こらなければ";
		mes "いいのですが。";
		close2;
		cutin "ep16_skia_nerius02.bmp",255;
		end;
	}
}

prt_cas.gat,108,240,3	script	クルックス#ep16_02	10118,{
	if(EP16_1QUE < 4) {
		cutin "ep16_crux_findel01.bmp",2;
		mes "[クルックス]";
		mes "私の事はお気になさらず。";
		mes "ただの護衛です。";
		close2;
		cutin "ep16_crux_findel03.bmp",255;
		end;
	} else if(EP16_1QUE == 4) {
		cutin "ep16_crux_findel01.bmp",2;
		mes "[クルックス]";
		mes "またお会いしましたね。";
		mes "お嬢様がお待ちです。";
		close2;
		cutin "ep16_crux_findel03.bmp",255;
		end;
	} else if(EP16_1QUE == 5) {
		cutin "ep16_crux_findel01.bmp",2;
		mes "[クルックス]";
		mes "またお会いしましたね。";
		mes "お嬢様がお待ちです。";
		close2;
		cutin "ep16_crux_findel03.bmp",255;
		end;
	} else {
		cutin "ep16_crux_findel01.bmp",2;
		mes "[クルックス]";
		mes "お嬢様の指示について思案中です。";
		mes "調査をする為にはお嬢様のそばを";
		mes "離れなければならないので……";
		close2;
		cutin "ep16_crux_findel03.bmp",255;
		end;
	}
}

prt_cas.gat,107,237,2	script(CLOAKED)	ニーヒル・ハイネン#ep16_02	10114,{}

prt_cas.gat,103,235,7	script(CLOAKED)	ビオルレター・ハイネン#ep16_02	959,{}

prt_cas.gat,108,235,2	script(CLOAKED)	王宮侍従#ep16_02	80,{}

prt_cas.gat,197,164,0	script	#ep16_evt_7689	139,2,3,{
OnTouch:
	if(EP16_1QUE == 5) {
		mes "‐前方から、誰かが";
		mes "　こちらへ来る気配がする‐";
		next;
		cloakoffnpc "怪しいお客#ep16_01";
		cloakoffnpc "侍従#ep16_01";
		mes "[侍従]";
		mes "いかがでしたか？";
		next;
		mes "[怪しいお客]";
		mes "うむ、悪くない。";
		mes "求めていたほどではないが";
		mes "なかなかの手がかりは得られたぞ。";
		next;
		mes "[侍従]";
		mes "薬がかなり効果的でした。";
		mes "……あの方は、";
		mes "耐性も持ちえなかったようですね。";
		next;
		mes "[怪しいお客]";
		mes "何も持たずに生まれてきたと";
		mes "名前をつけられただけはある。";
		mes "はははは！";
		next;
		mes "[侍従]";
		mes "ははは……";
		mes "これからどうなされますか？";
		mes "あの方はこのままで？";
		next;
		mes "[怪しいお客]";
		mes "うむ。放っておけ。";
		mes "あの様ならば、";
		mes "酔いに負けただけと";
		mes "思うだろう。";
		next;
		mes "[怪しいお客]";
		mes "我々は、そろそろ";
		mes "革命の準備をしようじゃないか。";
		cloakonnpc "怪しいお客#ep16_01";
		cloakonnpc "侍従#ep16_01";
		if(!sleep2(1000)) end;
		cloakoffnpc "スキア・ネリウス#ep16_7689";
		mes "‐怪しい二人は";
		mes "　そのまま歩き去って行った‐";
		next;
		mes "[スキア]";
		mes "あっ";
		mes strcharinfo(0)+"様！";
		mes "ニーヒルは見つかりましたか？";
		cutin "ep16_skia_nerius01.bmp",0;
		next;
		switch(select("見つからない","見つかった")) {
		case 1:
			mes "[スキア]";
			mes "そうですか……";
			mes "　";
			mes "ニーヒルはどこに";
			mes "行ってしまったんでしょう？";
			next;
			mes "[スキア]";
			mes "ちゃんと部屋に戻れたなら";
			mes "いいんです。";
			next;
			mes "[スキア]";
			mes "でも、離宮には";
			mes "大公がいらっしゃるから……";
			mes "あの状態では";
			mes "戻りたくないんじゃないかな。";
			cutin "ep16_skia_nerius02.bmp",0;
			next;
			mes "‐その時、怪しい二人が";
			mes "　来た方角にある一つの部屋から";
			mes "　うめき声が聞こえてきた‐";
			break;
		case 2:
			mes "[スキア]";
			mes "本当ですか！";
			mes "ニーヒルはどこに……";
			next;
			menu "適当な場所を言う",-,"怪しい二人が来た方向を指す",-;
			mes "[スキア]";
			mes "あの部屋ですか……？";
			mes "　";
			mes "‐その時、あなたが適当に";
			mes "　指を向けた部屋から";
			mes "　うめき声が響いてきた‐";
			break;
		}
		next;
		mes "[スキア]";
		mes strcharinfo(0)+"様";
		mes "行ってみましょう！";
		setquest 7690;
		delquest 7689;
		set EP16_1QUE,6;
		close2;
		cutin "ep16_skia_nerius02.bmp",255;
		cloakonnpc "スキア・ネリウス#ep16_7689";
		end;
	}
}

prt_cas.gat,202,163,3	script(CLOAKED)	スキア・ネリウス#ep16_7689	10116,{}

prt_cas.gat,31,116,0	script	#ep16_evt_7690	139,1,1,{
OnTouch:
	if(EP16_1QUE == 6) {
		cloakoffnpc "スキア・ネリウス#ep16_7690";
		cloakoffnpc "ニーヒル・ハイネン#ep16_7690";
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"ニーヒル・ハイネン#ep16_7690"),"ニーヒル : うう……",1;
		if(!sleep2(1000)) end;
		unittalk getnpcid(0,"スキア・ネリウス#ep16_7690"),"スキア : ニーヒル！",1;
		end;
	}
	end;
}

prt_cas.gat,31,116,3	script(CLOAKED)	ニーヒル・ハイネン#ep16_7690	10114,{
	if(EP16_1QUE == 6) {
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "……誰だ？";
		mes strcharinfo(0)+"？";
		mes "どうしてここに？";
		next;
		unittalk getnpcid(0,"ニーヒル・ハイネン#ep16_7690"),"ニーヒル : くっ……",1;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "私は……酔っているのか？";
		mes "頭痛がひどい。";
		mes "目まいがする……";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "ニーヒル、大丈夫ですか？";
		mes "あなたこそ";
		mes "どうしてこの部屋に？";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "酔いが回ってしまったみたい";
		mes "だったから……";
		mes "酒をくれた侍従に";
		mes "休める場所まで";
		mes "案内してくれとい……";
		mes "……くっ";
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "度数の低い葡萄酒だと……";
		mes "聞いたんだが……";
		next;
		switch(select("大丈夫？","酒に弱い？")) {
		case 1:
			cutin "ep16_nihi_miseria_heine01.bmp",2;
			mes "[ニーヒル]";
			mes "……すまない。";
			mes "なんとも……言えない。";
			next;
			mes "[ニーヒル]";
			mes "酒に強いわけではないが……";
			mes "　";
			mes "普段はここまでひどくは";
			mes "ならないんだが……";
			break;
		case 2:
			cutin "ep16_nihi_miseria_heine01.bmp",2;
			mes "[ニーヒル]";
			mes "いや、";
			mes "そんなことは……";
			mes "　";
			mes "決して強いわけでもないが……";
			next;
			mes "[ニーヒル]";
			mes "いつもなら、こんな風には……";
			break;
		}
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "……情けない。";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "そんなこと……";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "会場で倒れなくてよかったわ。";
		mes "今のニーヒルを見たのは";
		mes "私と冒険者様だけだもの。";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "ふふ、確かにそうだな。";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",2;
		mes "[ニーヒル]";
		mes "……そういえば、";
		mes "ここに来たのは二人だけか？";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "先客がいたような気が";
		mes "したんだが……";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "先客？";
		mes "この部屋には";
		mes "あなたしかいなかったけど……？";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "そうなのか？";
		next;
		mes "[ニーヒル]";
		mes "……";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "ニーヒル？";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "いや、なんでもない。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "そうだ。";
		mes "そろそろ儀式の手筈が";
		mes "整ってもおかしくない時間だ。";
		next;
		mes "[ニーヒル]";
		mes "出席するにせよしないにせよ";
		mes "大人しく戻るのが良さそうだ。";
		mes "幸いにも徐々に状態も";
		mes "良くなってきたしな。";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "ここで時間を無駄にしていたら、";
		mes "またなにか言われてしまう。";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "一人で戻れる？";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "ああ。探してくれてありがとう。";
		mes "スキア、";
		mes strcharinfo(0)+"様も。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "それでは失礼する。";
		mes "　";
		mes "‐ニーヒルはまだ少し";
		mes "　危なっかしい足取りで";
		mes "　部屋を出て行った‐";
		next;
		cloakonnpc "ニーヒル・ハイネン#ep16_7690";
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "……あれなら、大丈夫かな。";
		next;
		cutin "ep16_skia_nerius03.bmp",0;
		mes "[スキア]";
		mes "それでは";
		mes strcharinfo(0)+"様、";
		mes "私たちも戻りましょうか。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "今ごろ、宮廷魔術師が";
		mes strcharinfo(0)+"様の部屋に";
		mes "到着していると思います。";
		mes "儀式でまたお会いしましょう。";
		delquest 7690;
		setquest 7691;
		set EP16_1QUE,7;
		close2;
		cutin "ep16_skia_nerius01.bmp",255;
		end;
	}
}

prt_cas.gat,29,117,5	script(CLOAKED)	スキア・ネリウス#ep16_7690	10116,{
	if(EP16_1QUE == 6) {
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "……誰だ？";
		mes strcharinfo(0)+"？";
		mes "どうしてここに？";
		next;
		unittalk getnpcid(0,"ニーヒル・ハイネン#ep16_7690"),"ニーヒル : くっ……",1;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "私は……酔っているのか？";
		mes "頭痛がひどい。";
		mes "目まいがする……";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "ニーヒル、大丈夫ですか？";
		mes "あなたこそ";
		mes "どうしてこの部屋に？";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "酔いが回ってしまったみたい";
		mes "だったから……";
		mes "酒をくれた侍従に";
		mes "休める場所まで";
		mes "案内してくれとい……";
		mes "……くっ";
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "度数の低い葡萄酒だと……";
		mes "聞いたんだが……";
		next;
		switch(select("大丈夫？","酒に弱い？")) {
		case 1:
			cutin "ep16_nihi_miseria_heine01.bmp",2;
			mes "[ニーヒル]";
			mes "……すまない。";
			mes "なんとも……言えない。";
			next;
			mes "[ニーヒル]";
			mes "酒に強いわけではないが……";
			mes "　";
			mes "普段はここまでひどくは";
			mes "ならないんだが……";
			break;
		case 2:
			cutin "ep16_nihi_miseria_heine01.bmp",2;
			mes "[ニーヒル]";
			mes "いや、";
			mes "そんなことは……";
			mes "　";
			mes "決して強いわけでもないが……";
			next;
			mes "[ニーヒル]";
			mes "いつもなら、こんな風には……";
			break;
		}
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "……情けない。";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "そんなこと……";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "会場で倒れなくてよかったわ。";
		mes "今のニーヒルを見たのは";
		mes "私と冒険者様だけだもの。";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "ふふ、確かにそうだな。";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",2;
		mes "[ニーヒル]";
		mes "……そういえば、";
		mes "ここに来たのは二人だけか？";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "先客がいたような気が";
		mes "したんだが……";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "先客？";
		mes "この部屋には";
		mes "あなたしかいなかったけど……？";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "そうなのか？";
		next;
		mes "[ニーヒル]";
		mes "……";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "ニーヒル？";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "いや、なんでもない。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "そうだ。";
		mes "そろそろ儀式の手筈が";
		mes "整ってもおかしくない時間だ。";
		next;
		mes "[ニーヒル]";
		mes "出席するにせよしないにせよ";
		mes "大人しく戻るのが良さそうだ。";
		mes "幸いにも徐々に状態も";
		mes "良くなってきたしな。";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "ここで時間を無駄にしていたら、";
		mes "またなにか言われてしまう。";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "一人で戻れる？";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "ああ。探してくれてありがとう。";
		mes "スキア、";
		mes strcharinfo(0)+"様も。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "それでは失礼する。";
		mes "　";
		mes "‐ニーヒルはまだ少し";
		mes "　危なっかしい足取りで";
		mes "　部屋を出て行った‐";
		next;
		cloakonnpc "ニーヒル・ハイネン#ep16_7690";
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "……あれなら、大丈夫かな。";
		next;
		cutin "ep16_skia_nerius03.bmp",0;
		mes "[スキア]";
		mes "それでは";
		mes strcharinfo(0)+"様、";
		mes "私たちも戻りましょうか。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "今ごろ、宮廷魔術師が";
		mes strcharinfo(0)+"様の部屋に";
		mes "到着していると思います。";
		mes "儀式でまたお会いしましょう。";
		delquest 7690;
		setquest 7691;
		set EP16_1QUE,7;
		close2;
		cutin "ep16_skia_nerius01.bmp",255;
		end;
	} else if(EP16_1QUE == 7) {
		mes "[スキア]";
		mes strcharinfo(0)+"様。";
		mes "ニーヒルはもう大丈夫みたい。";
		mes "一緒に探してくれて";
		mes "ありがとうございました。";
		next;
		mes "[スキア]";
		mes "そろそろ宮廷魔術師が";
		mes strcharinfo(0)+"様の部屋に";
		mes "到着していると思います。";
		mes "儀式でまたお会いしましょう。";
		close2;
		cutin "ep16_skia_nerius01.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,19,85,4	script	クロネカー・ハイネン#ep16_01	10119,{
	switch(EP16_1QUE) {
	case 0:
	case 1:
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "君の訪問は許可していない。";
		mes "速やかに下がりなさい。";
		close2;
		cutin "ep16_kronecker_granz_heine.bmp",255;
		end;
	case 2:
		if(!checkquest(73065)) {
			mes "‐何か話しているようだ。";
			mes "　近づいてみよう‐";
			close;
		}
		if(checkquest(7683) & 0x1) {
			cutin "ep16_kronecker_granz_heine.bmp",2;
			mes "[クロネカー]";
			mes "お見苦しい姿をお見せした。";
			mes "ハイネン家を代表して謝罪する。";
			next;
			cutin "ep16_friedrich_stolz_heine.bmp",1;
			mes "[フリードリヒ]";
			mes "挨拶が遅れた。";
			mes "私がハイネン家の現当主である";
			mes "フリードリヒ・";
			mes "シュトルツ・ハイネンだ。";
			next;
			mes "[フリードリヒ]";
			mes "この方は先代当主で私の父である";
			mes "グランツ大公だ。";
			next;
			cutin "ep16_kronecker_granz_heine.bmp",2;
			mes "[クロネカー]";
			mes "クロネカー・グランツ・ハイネンだ。";
			next;
			cutin "ep16_friedrich_stolz_heine.bmp",1;
			mes "[フリードリヒ]";
			mes "そしてこちらにいるのが";
			mes "次期王位候補の";
			mes "ピーター・ハイネン。";
			next;
			cutin "ep16_petter_heine01.bmp",0;
			mes "[ピーター]";
			mes "歴戦の勇者様にお会い出来て";
			mes "とても光栄です。";
			next;
			cutin "ep16_friedrich_stolz_heine.bmp",1;
			mes "[フリードリヒ]";
			mes "そして先ほど出て行ったのが";
			mes "私の息子のニーヒルです。";
			next;
			mes "[フリードリヒ]";
			mes "ハイネン家の正統な直系だが、";
			mes "まだ幼いところがあってな。";
			mes "先ほどの件、改めて謝罪する。";
			next;
			cutin "ep16_kronecker_granz_heine.bmp",2;
			mes "[クロネカー]";
			mes "あいつは放っておけ。";
			mes "今は子どものわがままを";
			mes "聞いている時ではないのだ。";
			next;
			cutin "ep16_petter_heine01.bmp",0;
			mes "[ピーター]";
			mes "……大公殿下。";
			mes "ニーヒルに冷たくしすぎでは？";
			mes "王位継承権は本来、";
			mes "ニーヒルにあるべきはず。";
			next;
			mes "[ピーター]";
			mes "それを傍系である私が……";
			next;
			cutin "ep16_kronecker_granz_heine.bmp",2;
			mes "[クロネカー]";
			mes "そこまでにしなさい。";
			mes "ニーヒルには素質が無い。";
			next;
			mes "[クロネカー]";
			mes "家門の正統性に合致する要素が";
			mes "何一つ無いにも関わらず";
			mes "継承権については声をあげて主張する。";
			mes "権力に欲があったという";
			mes "証拠ではないか！";
			next;
			cutin "ep16_petter_heine01.bmp",0;
			mes "[ピーター]";
			mes "当たり前の権利を黙殺されて";
			mes "傷心しているといった様子ですよ。";
			next;
			cutin "ep16_kronecker_granz_heine.bmp",2;
			mes "[クロネカー]";
			mes "ハイネンの名で享受できる権利。";
			mes "その全てを持った者がニーヒルだ。";
			next;
			mes "[クロネカー]";
			mes "あいつはそれを真に理解しているのか。";
			mes "今のあいつでは客人の前に立たせて";
			mes "話をするのも恥ずかしい。";
			next;
			mes "[クロネカー]";
			mes "大変失礼した。";
			mes "どうしてあのような者が";
			mes "我が家門に生まれ、";
			mes "こんな問題を起こすのか。";
			next;
			mes "[クロネカー]";
			mes "君は儀式に参観すると聞いた。";
			mes "^0000ff次の王位は必ずハイネン家^000000に";
			mes "戻って来るだろう。";
			next;
			mes "[クロネカー]";
			mes "実は以前、候補者を集めて";
			mes "資質を試す王位継承を";
			mes "行ったのだ……";
			next;
			cutin "ep16_friedrich_stolz_heine.bmp",1;
			mes "[フリードリヒ]";
			mes "当時、最有力候補だった";
			mes "^0000ffバルター家のアイゼン・アルム^000000が";
			mes "突如として他の候補を脅し、";
			mes "^0000ffゲオルグ家のエルンスト^000000が";
			mes "彼を斬るという事件があったんだ。";
			next;
			mes "[フリードリヒ]";
			mes "それによってエルンストが";
			mes "次期王位に確定するかと思いきや、";
			mes "突然、^0000ff放棄の意思^000000を見せた。";
			mes "私には^0000ff王妃殿下の意思^000000が";
			mes "絡んでいるように思えるな。";
			next;
			mes "[フリードリヒ]";
			mes "……とにかくその事件をきっかけに";
			mes "王位継承者の選定については";
			mes "内部で再度行うことになった。";
			mes "ハイネン家では今回も";
			mes "^0000ffピーターが候補^000000になっている。";
			next;
			mes "[クロネカー]";
			mes "他の家門でも";
			mes "ピーターを支持する者も多いのだ。";
			mes "^ff0000ピーターこそが";
			mes "^ff0000七王家に利益をもたらす^000000ことが";
			mes "できると確信しておる。";
			cutin "ep16_kronecker_granz_heine.bmp",2;
			next;
			menu "七王家の利益……",-;
			mes "[クロネカー]";
			mes "そうじゃ。";
			mes "それをニーヒル……";
			mes "あいつが妬んでいる。";
			mes "みっともない男だ……";
			next;
			cutin "ep16_friedrich_stolz_heine.bmp",1;
			mes "[フリードリヒ]";
			mes "……";
			mes "ニーヒルは悪い奴ではない。";
			mes "ハイネン家の名に背く行動は";
			mes "一度も見せたことがないしな。";
			next;
			mes "[フリードリヒ]";
			mes "息子だから庇ってるわけじゃない。";
			mes "ただし、ニーヒル……";
			mes "あの子は……";
			next;
			mes "[クロネカー]";
			cutin "ep16_kronecker_granz_heine.bmp",2;
			mes "庇うんじゃない。無能こそ罪だ。";
			mes "ハイネン家は巨大な魔力を持って";
			mes "生まれる家系。";
			next;
			mes "[クロネカー]";
			mes "あいつの名……ミゼリアにも";
			mes "相応の理由があるのだ。";
			next;
			mes "[フリードリヒ]";
			cutin "ep16_kronecker_granz_heine.bmp",1;
			mes "これ以上は家門内のことだ。";
			mes "あまり気にしないでくれ。";
			mes "とにかく、後でまだ会おう。";
			next;
			compquest 7683;
			mes "[フリードリヒ]";
			mes "近いうちに王位継承は終わる。";
			mes "私たちはその準備をする故に";
			mes "時間を割けず申し訳ない。";
			next;
			mes "[フリードリヒ]";
			mes "君もまだ訪問していない";
			mes "家門があるなら";
			mes "訪問してみなさい。";
			next;
			if((checkquest(7683)&0x8) && !checkquest(73051) && !checkquest(73053) && !checkquest(73052) && !checkquest(73054) && !checkquest(73055) && !checkquest(73056)) {
				mes "‐^0000cd七王家すべてに挨拶をした。^000000";
				mes "　ベルのところに戻ろう‐";
			} else {
				mes "‐^0000cdハイネン家との挨拶を済ました。^000000";
				mes "　他の王家にも挨拶に行こう‐";
			}
			cutin "ep16_kronecker_granz_heine.bmp",255;
			close;
		} else {
			cutin "ep16_kronecker_granz_heine.bmp",1;
			mes "[フリードリヒ]";
			mes "君もまだ訪問していない";
			mes "家門があるなら";
			mes "訪問してみなさい。";
			close2;
			cutin "ep16_kronecker_granz_heine.bmp",255;
			end;
		}
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "もうじき王位継承が終わる。";
		mes "予想していた通り、";
		mes "ピーターが有力だろう。";
		next;
		mes "[クロネカー]";
		mes "君は祝宴を楽しんでいるか？";
		mes "王位継承が終わったら";
		mes "最後の儀式の為に";
		mes "移動をする予定だが……";
		next;
		mes "[クロネカー]";
		mes "君には特別に宮廷魔術師を";
		mes "派遣させよう。";
		mes "適当に祝宴を楽しんだ後、";
		mes "部屋に戻っていなさい。";
		close2;
		cutin "ep16_kronecker_granz_heine.bmp",255;
		end;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		end;
	case 16:
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "待っていたぞ。";
		mes "王家の恥部を晒すようで";
		mes "あまり気が進まないが。";
		next;
		mes "[クロネカー]";
		mes "参観の資格を与えたのは王室で、";
		mes "凶刃に立ち向かったのも君だ。";
		next;
		mes "[クロネカー]";
		mes "単刀直入に話そう。";
		mes "まず、その者たちは";
		mes "^4d4dffユミルの心臓の欠片^000000を";
		mes "狙っていた奴らのようだ。";
		next;
		mes "[クロネカー]";
		mes "儀式の部屋にあったのが";
		mes "まさか偽物だったとは";
		mes "夢にも思わなかった。";
		next;
		mes "[クロネカー]";
		mes "どうして偽物があったのか";
		mes "王家の記憶の間にある";
		mes "歴史書を調べてみたが";
		next;
		mes "[クロネカー]";
		mes "結局は探し出せなかった。";
		mes "ただし、不可解なものだけは発見した。";
		next;
		menu "^4d4dff真実を知る者？^000000",-;
		mes "[クロネカー]";
		mes "王家の記憶の間で";
		mes "それを見て来たのか。";
		mes "思いのほか利口なようだな。";
		next;
		mes "[クロネカー]";
		mes "真実を知らせる為には";
		mes "時間を遡らないとならない。";
		next;
		mes "[クロネカー]";
		mes "フリードリヒ。";
		mes "過去に行く話を頼む。";
		next;
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "時間移動に長けた宮廷魔術師がいる。";
		mes "その者の力を使い、";
		mes "過去に行って調査を行ってほしい。";
		next;
		menu "まさかニルレム？",-;
		mes "[フリードリヒ]";
		mes "知っているのか。";
		mes "ならば話がはやい。";
		mes "彼と一緒に過去に行ってほしいのだ。";
		next;
		menu "ユミルの心臓の行方ですね？",-;
		mes "[フリードリヒ]";
		mes "そうだ。";
		mes "そして王家の記憶の間という";
		mes "場所自体が一部の関連者以外は";
		mes "立ち入りが禁じられた場所。";
		next;
		mes "[フリードリヒ]";
		mes "秘密を厳守するためにも、";
		mes "これ以上、他人を巻き込むことは";
		mes "できないのだ。";
		mes "力を貸してほしい。";
		next;
		menu "わかりました",-;
		mes "[フリードリヒ]";
		mes "過去のプロンテラ城に行き、";
		mes "何があったのか調べてきてくれ。";
		next;
		mes "[フリードリヒ]";
		mes "……それと";
		mes strcharinfo(0)+"殿。";
		mes "君には礼を言う。";
		next;
		menu "どうしました？",-;
		mes "[フリードリヒ]";
		mes "ニーヒルの事だ。";
		mes "君に随分世話になっているようだ。";
		mes "ネリウス家のお嬢様たちにも。";
		next;
		mes "[フリードリヒ]";
		mes "実は、宮廷魔術師の力を使い、";
		mes "過去に調査に行くことを提案してきたのは";
		mes "ネリウス家のスピーカ殿だ。";
		next;
		mes "[フリードリヒ]";
		mes "父クロネカーはユミルの心臓の行方で";
		mes "頭がいっぱいだったから";
		mes "その提案に大喜びだった。";
		next;
		mes "[フリードリヒ]";
		mes "過去にいくことを提案したのも";
		mes "真実を突き止めることが";
		mes "ニーヒルの無実につながると";
		mes "考えたのかもしれない。";
		next;
		mes "[フリードリヒ]";
		mes "スピーカ殿は";
		mes "あの襲撃犯の行方を捜すそうだ。";
		mes "ニーヒルの疑いを晴らすために。";
		next;
		mes "[フリードリヒ]";
		mes "なによりもあの襲撃の時、";
		mes "ピーターが刺され、";
		mes "ユミルの心臓も王も偽物と言われ";
		mes "皆、動くことすらできなかった。";
		next;
		mes "[フリードリヒ]";
		mes "だが、ニーヒルは、";
		mes "ニーヒルは動いたのだ。";
		next;
		mes "[フリードリヒ]";
		mes "息子の成長を見るというのは、";
		mes "本当に嬉しいものなのだ。";
		next;
		mes "[フリードリヒ]";
		mes "そしてスピーカ殿と君のように";
		mes "息子に賛同する者がいる。";
		mes "新しい時代を感じるよ。";
		mes "……少し話がそれたな。";
		next;
		mes "[クロネカー]";
		mes "ニルレムは準備が出来次第";
		mes "君の部屋に行かせる。";
		mes "これからニルレムと一緒に";
		mes "行動をしなさい。";
		setquest 7699;
		delquest 7698;
		set EP16_1QUE,17;
		close2;
		cutin "ep16_kronecker_granz_heine.bmp",255;
		end;
	case 17:
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "ニルレムという魔術師が";
		mes "君の部屋を訪ねる。";
		mes "部屋で待機していてくれ。";
		close2;
		cutin "ep16_kronecker_granz_heine.bmp",255;
		end;
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "希望を捨てるにはまだ早い。";
		mes "私は君のことを信じている。";
		close2;
		cutin "ep16_kronecker_granz_heine.bmp",255;
		end;
	case 24:
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "君の尽力のおかげで";
		mes "我が家門にかけられた";
		mes "汚名を晴らすことができた。";
		next;
		mes "[クロネカー]";
		mes "後は寝込んでいるピーターさえ";
		mes "起きれば良いのだが。";
		close2;
		cutin "ep16_friedrich_stolz_heine.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,21,83,3	script	フリードリヒ・ハイネン#ep16_01	10120,{
	switch(EP16_1QUE) {
	case 0:
	case 1:
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "許可もなく出入りするとは。";
		mes "すぐに出て行きなさい。";
		close2;
		cutin "ep16_friedrich_stolz_heine.bmp",255;
		end;
	case 2:
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "こればかりはな……";
		mes "ニーヒルも落ち着いてくれると";
		mes "いいのだが……";
		close2;
		cutin "ep16_friedrich_stolz_heine.bmp",255;
		end;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "君も祝宴を楽しんだらどうだ？";
		mes "ニーヒルも祝宴場に向かったぞ。";
		next;
		mes "[フリードリヒ]";
		mes "第一印象は良くなかっただろうが";
		mes "ニーヒルは悪い子ではない。";
		mes "ただ……";
		next;
		mes "[フリードリヒ]";
		mes "いや、何でもない。";
		mes "忘れてくれ。";
		close2;
		cutin "ep16_friedrich_stolz_heine.bmp",255;
		end;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		end;
	case 16:
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "やっと来たか。";
		mes "大公が首を長くして待っている。";
		close2;
		cutin "ep16_friedrich_stolz_heine.bmp",255;
		end;
	case 17:
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "ニルレムは作業を終えた後、";
		mes "君の部屋に向かうと言っていたから";
		mes "しばらく待ってくれ。";
		mes "良い結果を期待しているぞ。";
		close2;
		cutin "ep16_friedrich_stolz_heine.bmp",255;
		end;
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
		mes "[フリードリヒ]";
		mes "……";
		next;
		mes "‐考え事をしているようだ。";
		mes "　今は話しかけるのをやめておこう‐";
		close2;
		cutin "ep16_friedrich_stolz_heine.bmp",255;
		end;
	case 23:
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "大公から話は聞いた。";
		mes "正式に許可を得て";
		mes "君が王家の記憶の間を自由に";
		mes "出入りできるようにしてある。";
		next;
		mes "[フリードリヒ]";
		mes "……しかし、大変なことになったな。";
		mes "だからこそ七王家が団結し、";
		mes "この国を守らなくてはいけない。";
		next;
		mes "[フリードリヒ]";
		mes "君には本当に感謝している。";
		mes "いつか君がハイネン家の力を";
		mes "必要とするならば";
		mes "君の力になる事を約束しよう。";
		next;
		mes "[フリードリヒ]";
		mes "君に渡せる報酬は";
		mes "この程度が精一杯なのだ。";
		mes "本当に申し訳ない。";
		mes "だが、宮殿の内部での生活においては";
		mes "不便がないように取り計らおう。";
		next;
		mes "[フリードリヒ]";
		mes "……並大抵の事では";
		mes "過去が変わらないと知っている。";
		mes "しかし、今の私たちには";
		mes "どうする事もできないのだ。";
		next;
		mes "[フリードリヒ]";
		mes "私たちに出来る事をやるしかない。";
		next;
		mes "[フリードリヒ]";
		mes "そこで……";
		mes "君の都合が良い時でかまわない。";
		mes "これからも過去に行き、";
		mes "ユミルの心臓を守って";
		mes "もらいたいのだ。";
		next;
		mes "[フリードリヒ]";
		mes "それがいかに困難で、";
		mes "危険を伴うことかということは";
		mes "重々承知している。";
		mes "だがこれは君にしか";
		mes "頼めないことなのだ。";
		next;
		menu "引き受ける",-;
		mes "[フリードリヒ]";
		mes "ありがとう。";
		mes "君ならそう言ってくれると";
		mes "思っていたよ。";
		next;
		mes "[フリードリヒ]";
		mes "君が頑張っている間、";
		mes "私たちも色々調査をしている。";
		next;
		mes "[フリードリヒ]";
		mes "あの時、侵入した者についても";
		mes "調査をしているところだ。";
		mes "必ず、解決してみせるぞ。";
		close2;
		if(checkitemblank() == 0) {	// 未調査
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		set EP16_1QUE,24;
		delquest 7704;
		setquest 7705;
		setquest 201875;
		getitem 6919,40;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		cutin "ep16_friedrich_stolz_heine.bmp",255;
		end;
	default:
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "……並大抵の事では";
		mes "過去が変わらないと知っている。";
		mes "しかし、今の私たちには";
		mes "どうする事もできないのだ。";
		next;
		mes "[フリードリヒ]";
		mes "私たちに出来る事をやるしかない。";
		next;
		mes "[フリードリヒ]";
		mes "君が頑張っている間、";
		mes "私たちも色々調査をしている。";
		next;
		mes "[フリードリヒ]";
		mes "あの時、侵入した者についても";
		mes "調査をしているところだ。";
		mes "各自、各々の仕事を頑張ろう。";
		close2;
		cutin "ep16_friedrich_stolz_heine.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,18,83,5	script	ピーター・ハイネン#ep16_01	987,{
	switch(EP16_1QUE) {
	case 0:
	case 1:
		cutin "ep16_petter_heine01.bmp",1;
		mes "[ピーター]";
		mes "祝宴に招待された英雄の方ですね。";
		mes "貴方達のための祝宴なのですから";
		mes "楽しんで下さい。";
		close2;
		cutin "ep16_petter_heine01.bmp",255;
		end;
	case 2:
		cutin "ep16_petter_heine01.bmp",1;
		mes "[ピーター]";
		mes "はは……";
		mes "大公はかなり怒っていますね。";
		close2;
		cutin "ep16_petter_heine01.bmp",255;
		end;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		cutin "ep16_petter_heine01.bmp",0;
		mes "[ピーター]";
		mes "王位継承に参加した";
		mes "当事者ではありますが、";
		mes "果たして私は正しいのか";
		mes "悩んでしまいます。";
		next;
		mes "[ピーター]";
		mes "みんなの為を思ってする事が";
		mes "むしろ苦めているのではないか……";
		next;
		mes "[ピーター]";
		mes "今の状況を見たとき、";
		mes "多くの方が私が有力だと";
		mes "言っているのですが、";
		mes "本当にそうなのか。";
		next;
		mes "[ピーター]";
		mes "どれほど大きな責任があるのか";
		mes "どれほど頑張らなければ";
		mes "ならないのか……";
		mes "考える事だけが増えています。";
		next;
		mes "[ピーター]";
		mes "だからといって";
		mes "逃げるわけにもいきません。";
		mes "私が頑張らないと。";
		close2;
		cutin "ep16_petter_heine01.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,19,85,0	script	#ep16_heine_evt01	139,12,12,{
OnTouch:
	if(EP16_1QUE == 2 && !(checkquest(73065) & 0x8)) {
		cloakoffnpc "ニーヒル・ハイネン#ep16_01";
		cloakoffnpc "ピーター・ハイネン#ep16_01";
		cloakonnpc "ピーター・ハイネン#ep16_02";
	} else if(EP16_1QUE < 10) {
		cloakonnpc "ピーター・ハイネン#ep16_02";
		cloakoffnpc "ピーター・ハイネン#ep16_01";
	} else if(EP16_1QUE > 9) {
		cloakonnpc "ピーター・ハイネン#ep16_01";
		cloakoffnpc "ピーター・ハイネン#ep16_02";
	}
	end;
}

prt_cas_q.gat,22,77,0	script	#ep16_heine_evt02	139,3,3,{
OnTouch:
	if(EP16_1QUE == 2 && !checkquest(73065)) {
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "お前は……";
		mes "自分が何をしたのか";
		mes "わかっているのか！";
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",0;
		mes "[ニーヒル]";
		mes "……";
		next;
		cutin "ep16_petter_heine01.bmp",1;
		mes "[ピーター]";
		mes "お、落ち着いてください。";
		mes "グランツ公……";
		next;
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "先刻、無礼を働いたのは";
		mes "己の一族の者だぞ！";
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",0;
		mes "[ニーヒル]";
		mes "……先に";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",0;
		mes "[ニーヒル]";
		mes "……先に";
		mes "無礼を働いたのは";
		mes "向こうのほうです！";
		next;
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "！";
		mes "　";
		mes "ニーヒル！";
		next;
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "馬鹿者!!";
		mes "先か後かの話ではない！";
		mes "お前は、仮にも";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",0;
		mes "[ニーヒル]";
		mes "本家に戻ります。";
		mes "許可をください。";
		next;
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "ニーヒル、それは……";
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",0;
		mes "[ニーヒル]";
		mes "父上。";
		mes "私がここにいる理由はありません。";
		next;
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "家門の一員として";
		mes "ここにいること、";
		mes "それがお前の義務だ！";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",0;
		mes "[ニーヒル]";
		mes "私が家門の一員？";
		mes "これまで";
		mes "一員として認めてくれたことなんか";
		mes "ありましたか!?";
		next;
		mes "[ニーヒル]";
		mes "先刻も、これまでも";
		mes "まともに相手をしてくれたことが！";
		next;
		cutin "ep16_petter_heine01.bmp",1;
		mes "[ピーター]";
		mes "……";
		mes "　";
		mes "いいえ、ニーヒル。";
		mes "あなたは……";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",0;
		mes "[ニーヒル]";
		mes "そもそも、その家門が";
		mes "私につけた名をお忘れですか！";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",0;
		mes "[ニーヒル]";
		mes "ニーヒル・ミゼリア！";
		mes "役立たずと判断して";
		mes "つけられた名を！";
		next;
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "そこまでにしておけ。";
		mes "ニーヒル。";
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",0;
		mes "[ニーヒル]";
		mes "……";
		next;
		cutin "ep16_nihi_miseria_heine03.bmp",0;
		mes "[ニーヒル]";
		mes "認めはせずに、";
		mes "責任だけを私に押し付けて";
		mes "……もうこれ以上は嫌です！";
		next;
		mes "‐ニーヒルと呼ばれた青年が";
		mes "　あなたのほうへ";
		mes "　向かってくる‐";
		next;
		switch(select("声をかけない","声をかける")) {
		case 1:
		cutin "ep16_nihi_miseria_heine04.bmp",0;
			mes "[ニーヒル]";
			mes "！";
			mes "　";
			mes "失礼。どいてください。";
			break;
		case 2:
			mes "[ニーヒル]";
			mes "……私などに声掛けは必要ありません。";
			mes "挨拶は部屋の奥にいる";
			mes "グランツ公にどうぞ。";
			break;
		}
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",255;
		mes "‐ニーヒルは不機嫌なまま";
		mes "　部屋を出て行ってしまった‐";
		next;
		cloakonnpc "ニーヒル・ハイネン#ep16_01";
		cutin "ep16_friedrich_stolz_heine.bmp",1;
		mes "[フリードリヒ]";
		mes "ニーヒル";
		mes "待ちなさい！";
		next;
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "追いかけるなフリードリヒ！";
		mes "ピーターもだ！";
		next;
		cutin "ep16_petter_heine01.bmp",1;
		mes "[ピーター]";
		mes "しかし……";
		next;
		cutin "ep16_kronecker_granz_heine.bmp",2;
		mes "[クロネカー]";
		mes "ふん、生意気を言いおって。";
		mes "いつまで子どものつもりでいるのか。";
		setquest 73065;
		compquest 73065;
		close2;
		cutin "ep16_kronecker_granz_heine.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,22,80,3	script(CLOAKED)	ニーヒル・ハイネン#ep16_01	10114,{}

prt_cas_q.gat,9,90,3	script(CLOAKED)	ピーター・ハイネン#ep16_02	10117,{
	mes "‐傷が痛むのか苦しそうだ。";
	mes "　会話ができる状態ではない‐";
	close;
}

prt_cas_q.gat,142,38,0	script	#ep16_evt_7686	139,5,5,{
	end;
OnTouch:
	if(EP16_1QUE == 2 && (checkquest(7683) & 0x8) && !checkquest(7686)) {
		cloakoffnpc "スキア#ep16_7686";
		cloakoffnpc "ニーヒル#ep16_7686";
		mes "‐ハイネン家の部屋を出て行った";
		mes "　青年と、一人の少女が向き合っていた‐";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "あなたは……";
		mes "あなたが噂のシャドウプリンセスですか？";
		next;
		mes "[ニーヒル]";
		mes "あなたも大変そうですね。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "……あ、";
		mes "ハイネン家の公子様でしたか。";
		next;
		mes "[スキア]";
		mes "私がシャドウなのは";
		mes "あっていますが、";
		mes "それが大変だと思ったことは";
		mes "一度もありません。";
		next;
		mes "[スキア]";
		mes "私は、私ができることを";
		mes "しているだけですから。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "しかし、あなた自身が望んで、";
		mes "そのように生まれたわけでは";
		mes "ないでしょう？";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "ええ。";
		mes "私はシャドウとして育ちました。";
		mes "もちろん、それに疑問を";
		mes "持ったことはありますけど……";
		next;
		mes "[スキア]";
		mes "少なくとも、今の私は";
		mes "自ら選択したものです。";
		mes "これが私の道です。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "……";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "そのように考えられるあなたが";
		mes "うらやましい。";
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "私は、自分につけられた";
		mes "ミゼリアという名を捨てたいと";
		mes "いつも思っています。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "ミゼリア……？";
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "不幸という意味です。";
		mes "ひどい名でしょう？";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "……";
		next;
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		mes "[ニーヒル]";
		mes "生まれた時から何も持たないと";
		mes "いわれ続けて生きると";
		mes "どうなるのか知っていますか？";
		next;
		mes "[ニーヒル]";
		mes "自分自身を失うのです。";
		mes "本当に、空っぽになったように。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "……";
		next;
		mes "[ニーヒル]";
		mes "私は何を言っているのでしょうか。";
		mes "すみません。";
		mes "あなたに言うことではなかった。";
		next;
		cutin "ep16_skia_nerius02.bmp",0;
		mes "[スキア]";
		mes "何もないということは！";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "……";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "何にでも、どんなものにも";
		mes "変わることができませんか？";
		mes "人に決められた未来はありません。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "……";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "……そう、ですね。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "そういえば、";
		mes "まだ挨拶もしていませんでしたね。";
		mes "ニーヒル・ミゼリア・ハイネンです。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "私はスキア。";
		mes "スキア・ネリウスです。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "呼び止めてしまって";
		mes "申し訳ない。";
		mes "シャドウプリンセスのあなたが";
		mes "一人で、廊下にいたのには";
		mes "理由があったのでしょう？";
		next;
		cutin "ep16_skia_nerius03.bmp",0;
		mes "[スキア]";
		mes "大丈夫ですよ！";
		mes "用事を終わらせた";
		mes "帰りでしたから。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "でも、そろそろスピーカのもとに";
		mes "帰らないと、遅いって";
		mes "言われちゃうかもしれません。";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "それは大変ですね。";
		mes "早く顔を見せてあげなくては。";
		next;
		cutin "ep16_skia_nerius01.bmp",0;
		mes "[スキア]";
		mes "ええ！";
		mes "それでは、失礼します。";
		cloakonnpc "スキア#ep16_7686";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "……";
		next;
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		mes "[ニーヒル]";
		mes "スキアか。";
		mes "ネリウス家には";
		mes "面白いお嬢さんがいるものだ。";
		close2;
		cloakonnpc "ニーヒル#ep16_7686";
		cutin "ep16_nihi_miseria_heine02.bmp",255;
		setquest 7686;
		compquest 7686;
		end;
	}
	end;
}

prt_cas_q.gat,141,39,5	script(CLOAKED)	スキア#ep16_7686	10116,{}

prt_cas_q.gat,144,38,3	script(CLOAKED)	ニーヒル#ep16_7686	10114,{}

prt_cas_q.gat,19,136,0	script	#ep16_evt_neriusroom	139,12,12,{
OnTouch:
	if(EP162_1QUE > 1) {
		cloakonnpc "護衛騎士クルックス#ep16_room01";
		cloakonnpc "スピーカ・ネリウス#ep16_room01";
		cloakonnpc "スキア・ネリウス#ep16_room01";
	} else if(EP16_1QUE > 14 && EP16_1QUE < 17) {
		cloakonnpc "護衛騎士クルックス#ep16_room01";
		cloakonnpc "スピーカ・ネリウス#ep16_room01";
		cloakonnpc "スキア・ネリウス#ep16_room01";
		cloakoffnpc "スピーカ・ネリウス#ep16_room02";
	} else if(EP16_1QUE > 2 && EP16_1QUE < 7) {
		cloakonnpc "護衛騎士クルックス#ep16_room01";
		cloakonnpc "スピーカ・ネリウス#ep16_room01";
		cloakonnpc "スキア・ネリウス#ep16_room01";
	} else if(EP16_1QUE > 17) {
		cloakonnpc "スキア・ネリウス#ep16_room01";
	}
	end;
}

prt_cas_q.gat,20,139,3	script	スピーカ・ネリウス#ep16_room01	10115,{
	switch(EP16_1QUE) {
	case 0:
	case 1:
		cutin "ep16_spica_nerius01.bmp",1;
		mes "[スピーカ]";
		mes "祝宴に招待された方ですか？";
		mes "ここは祝宴場ではありませんよ。";
		close2;
		cutin "ep16_spica_nerius01.bmp",255;
		end;
	case 2:
		if(checkquest(73051)) {
			mes "[スピーカ]";
			mes "あなたが噂の";
			mes strcharinfo(0)+"様ですね。";
			mes "ご足労、感謝致します。";
			mes "私はネリウス家の";
			mes "スピーカと申します。";
			cutin "ep16_spica_nerius01.bmp",1;
			next;
			mes "[スキア]";
			mes "スキアです。";
			mes "お会い出来て嬉しいです。";
			cutin "ep16_skia_nerius01.bmp",0;
			next;
			mes "[スピーカ]";
			mes "そして、こちらは私の専属護衛騎士の";
			mes "クルックスです。";
			cutin "ep16_spica_nerius01.bmp",1;
			next;
			mes "[クルックス]";
			mes "クルックス・ファインデルと申します。";
			mes "現在、ネリウス家で剣を学んでいます。";
			cutin "ep16_crux_findel01.bmp",2;
			next;
			mes "[スピーカ]";
			mes "本来なら当主である母が来るべきですが";
			mes "今回の祝宴には英雄をはじめ";
			mes "多くの来客があると聞きました。";
			cutin "ep16_spica_nerius01.bmp",1;
			next;
			mes "[スピーカ]";
			mes "社会勉強という事で";
			mes "私たち双子が母に代わり";
			mes "出席することになったのです。";
			next;
			menu "王位継承候補はどこに？",-;
			cutin "ep16_spica_nerius05.bmp",1;
			mes "[スピーカ]";
			mes "王子……";
			mes "エリヒを探しているのですか？";
			mes "エリヒの居場所は……";
			mes "えーっと……";
			unittalk getnpcid(0,"護衛騎士クルックス#ep16_room01"),"クルックス : ……",1;
			next;
			cutin "ep16_spica_nerius06.bmp",1;
			mes "[スピーカ]";
			mes "し、知らないわけではありません！";
			mes "エリヒの居場所ですよね？";
			mes "それは……えーっと……";
			unittalk getnpcid(0,"護衛騎士クルックス#ep16_room01"),"クルックス : 図書館にいるはずです。",1;
			next;
			cutin "ep16_spica_nerius01.bmp",1;
			mes "[スピーカ]";
			mes "そう！　図書館！";
			mes "エリヒなら王宮の図書館にいます。";
			mes "また何かに興味を持って";
			mes "調べものでもしているのでしょう！";
			next;
			cutin "ep16_spica_nerius02.bmp",1;
			mes "[スピーカ]";
			mes "ネリウスは王位に";
			mes "興味がありませんから。";
			mes "エリヒも無理に王位継承に";
			mes "出る必要はなかったのです。";
			next;
			cutin "ep16_spica_nerius01.bmp",1;
			mes "[スピーカ]";
			mes "形式上の候補だからか、";
			mes "今も好き勝手に動いているんです。";
			next;
			menu "王位に興味が無いのはなぜ？",-;
			cutin "ep16_spica_nerius05.bmp",1;
			mes "[スピーカ]";
			mes "それはネリウスの特徴のせいです。";
			mes "ネリウス家は先祖代々、";
			mes "女性が中心であるため、";
			mes "王妃が多く選出されています。";
			next;
			cutin "ep16_spica_nerius03.bmp",1;
			mes "[スピーカ]";
			mes "万が一エリヒが出なかったら、";
			mes "私とスキアのどちらかが";
			mes "王妃候補として";
			mes "名が挙がっていたでしょう。";
			next;
			cutin "ep16_spica_nerius02.bmp",1;
			mes "[スピーカ]";
			mes "母はそれを嫌がっておりまして。";
			mes "結果、出したカードがエリヒだった。";
			mes "と言うわけです。";
			next;
			cutin "ep16_spica_nerius01.bmp",1;
			mes "[スピーカ]";
			mes "さて、家門の話は";
			mes "このくらいにしましょう。";
			mes "他の家門と挨拶はしましたか？";
			next;
			mes "[スピーカ]";
			mes "私も久しぶりに得た自由です。";
			mes "羽を伸ばさせていただきます。";
			next;
			cutin "ep16_skia_nerius03.bmp",0;
			mes "[スキア]";
			mes "冒険者様も私たちと一緒に";
			mes "楽しみましょうよ！";
			mes "ハイネン家の公子様と";
			mes "話も合いそうですし。";
			next;
			cutin "ep16_spica_nerius06.bmp",1;
			mes "[スピーカ]";
			mes "スキア、愛する私の半身。";
			mes "お前はもう少し教養のある";
			mes "言葉遣いを覚えましょうね？";
			next;
			cutin "ep16_spica_nerius07.bmp",1;
			mes "[スピーカ]";
			mes "とにかく、我々ネリウス家は";
			mes "あなたをいつでも受け入れます。";
			mes "気にせず訪問してください。";
			next;
			//setquest 7684;
			//compquest 7684;
			delquest 73051;
			if((checkquest(7683)&0x8) && !checkquest(73051) && !checkquest(73053) && !checkquest(73052) && !checkquest(73054) && !checkquest(73055) && !checkquest(73056)) {
				mes "‐^0000cd七王家すべてに挨拶をした。^000000";
				mes "　ベルのところに戻ろう‐";
				next;
			}
			cutin "ep16_spica_nerius01.bmp",1;
			mes "[スピーカ]";
			mes "私たちは祝宴の準備があるので";
			mes "あまり時間はないのですが……";
			next;
			mes "[スピーカ]";
			mes "まだ訪問していない家門があるなら";
			mes "訪問してみてはどうですか？";
			close2;
			cutin "ep16_spica_nerius01.bmp",255;
			end;
		}
		mes "[スピーカ]";
		mes "まだ訪問していない家門があるなら";
		mes "訪問してみてはどうですか？";
		cutin "ep16_spica_nerius01.bmp",1;
		close2;
		cutin "ep16_spica_nerius01.bmp",255;
		end;
	case 3:
	case 4:
	case 5:
	case 6:
		end;
	case 7:
		mes "[スピーカ]";
		mes "スキアから大体の話は聞いた。";
		mes "ニーヒル公子様は";
		mes "意外と酒に弱かったようだな。";
		cutin "ep16_spica_nerius01.bmp",1;
		next;
		mes "[スピーカ]";
		mes "……";
		cutin "ep16_spica_nerius03.bmp",1;
		next;
		mes "[スピーカ]";
		mes "生憎と私の目は節穴ではない。";
		mes "何か隠し事があるんじゃないか？";
		next;
		switch(select("怪しい人をみた","ない")) {
		case 1:
			mes "[スピーカ]";
			mes "先ほど、スキアも";
			mes "似たような事を言っていた。";
			mes "クルックスに調べさせたが";
			mes "大した情報はなかったよ。";
			next;
			mes "[スピーカ]";
			mes "今回の祝宴は大規模故に";
			mes "人手不足になっていてな。";
			mes "臨時で雇用した者の中に";
			mes "不審人物が紛れ込んでいたのかも";
			mes "知れないな。";
			break;
		case 2:
			mes "[スピーカ]";
			mes "……そうか。";
			mes "私も一人の小娘に過ぎない。";
			mes "英雄である君が言うのなら";
			mes "そういう事にしておこう。";
			cutin "ep16_spica_nerius07.bmp",1;
			break;
		}
		next;
		mes "[スピーカ]";
		mes "とにかく私はこの事を";
		mes "七王家で議論をしたい。";
		cutin "ep16_spica_nerius02.bmp",1;
		next;
		mes "[スピーカ]";
		mes "老人たちがどこまで私の言葉に";
		mes "耳を傾けるのかは疑問だがな。";
		close2;
		cutin "ep16_spica_nerius01.bmp",255;
		end;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		end;
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		mes "[スピーカ]";
		mes "君も苦労が絶えないな。";
		mes "こうも様々な事に";
		mes "巻き込まれて……";
		cutin "ep16_spica_nerius01.bmp",1;
		next;
		mes "[スピーカ]";
		mes "私もあまり良い状態ではないが";
		mes "王室は例の不審人物の背後を";
		mes "探っているところだ。";
		next;
		mes "[スピーカ]";
		mes "……そうした所で、";
		mes "場内に潜んでいる末端を";
		mes "捕えるのが精々だろうが、";
		mes "やらないよりはマシだ。";
		next;
		menu "スキアは？",-;
		mes "[スピーカ]";
		mes "ニーヒル公子と";
		mes "遊びに行ってしまったよ。";
		mes "あんな男のどこが良いんだか。";
		mes "顔以外、これと言って……";
		cutin "ep16_spica_nerius03.bmp",1;
		next;
		mes "[スピーカ]";
		mes "まさか……";
		mes "まさか、それなのか？";
		mes "スキアは彼の外見に惚れたのか？";
		mes "クルックス、君の意見を述べろ！";
		cutin "ep16_spica_nerius05.bmp",1;
		next;
		cutin "ep16_crux_findel03.bmp",2;
		mes "[クルックス]";
		mes "スピーカ様、ニーヒル公子は";
		mes "現在、謹慎中と伺っています。";
		mes "外出など出来ないのでは？";
		next;
		mes "[スピーカ]";
		mes "そうだった……訂正する。";
		mes "スキアはニーヒルの謹慎先を";
		mes "訪ねていった……って。";
		mes "それも同じようなことじゃないか！";
		cutin "ep16_spica_nerius06.bmp",1;
		next;
		menu "クルックス、ご苦労様……",-;
		cutin "ep16_crux_findel03.bmp",2;
		mes "[クルックス]";
		mes "はい……";
		mes "もう行かれるのですか？";
		mes "確かにお嬢様がこれ以上暴走する前に";
		mes "戻った方が賢明かもしれません。";
		next;
		cutin "ep16_crux_findel02.bmp",2;
		mes "[クルックス]";
		mes "それでは、また。";
		close2;
		cutin "ep16_spica_nerius01.bmp",255;
		end;
	case 24:
		if(EP162_1QUE > 0) {
			cutin "ep16_spica_nerius01.bmp",1;
			mes "[スピーカ]";
			mes "やあ、"+strcharinfo(0)+"。";
			mes "ちょうど今、妹に逃げられて、";
			mes "手持ち無沙汰になっていたところだ。";
			next;
			cutin "ep16_spica_nerius05.bmp",1;
			mes "[スピーカ]";
			mes "今回の件は苦労をかけたな。";
			mes "一番の功労者は間違いなく";
			mes strcharinfo(0)+"だろう。";
			next;
			cutin "ep16_spica_nerius07.bmp",1;
			mes "[スピーカ]";
			mes "最初はちょっとした";
			mes "興味からだったが……。";
			mes "ふふふ……";
			mes "おかげで退屈することは";
			mes "なかったよ。";
			next;
			mes "[スピーカ]";
			mes "もし、何かあったらいつでも";
			mes "頼ってくれていいぞ。";
			mes "冒険者様の周りでは";
			mes "面白そうな事が多そうだしな。";
			close2;
			cutin "ep16_spica_nerius01.bmp",255;
			end;
		}
		mes "[スピーカ]";
		mes "君も苦労が絶えないな。";
		mes "こうも様々な事に";
		mes "巻き込まれて……";
		cutin "ep16_spica_nerius01.bmp",1;
		next;
		mes "[スピーカ]";
		mes "私もあまり良い状態ではないが";
		mes "王室は例の不審人物の背後を";
		mes "探っているところだ。";
		next;
		mes "[スピーカ]";
		mes "……そうした所で、";
		mes "場内に潜んでいる末端を";
		mes "捕えるのが精々だろうが、";
		mes "やらないよりはマシだ。";
		next;
		menu "スキアは？",-;
		mes "[スピーカ]";
		mes "ニーヒル公子と";
		mes "遊びに行ってしまったよ。";
		mes "あんな男のどこが良いんだか。";
		mes "顔以外、これと言って……";
		cutin "ep16_spica_nerius03.bmp",1;
		next;
		mes "[スピーカ]";
		mes "まさか……";
		mes "まさか、それなのか？";
		mes "スキアは彼の外見に惚れたのか？";
		mes "クルックス、君の意見を述べろ！";
		cutin "ep16_spica_nerius05.bmp",1;
		next;
		cutin "ep16_crux_findel03.bmp",2;
		mes "[クルックス]";
		mes "スピーカ様、ニーヒル公子は";
		mes "現在、謹慎中と伺っています。";
		mes "外出など出来ないのでは？";
		next;
		mes "[スピーカ]";
		mes "そうだった……訂正する。";
		mes "スキアはニーヒルの謹慎先を";
		mes "訪ねていった……って。";
		mes "それも同じようなことじゃないか！";
		cutin "ep16_spica_nerius06.bmp",1;
		next;
		menu "クルックス、ご苦労様……",-;
		cutin "ep16_crux_findel03.bmp",2;
		mes "[クルックス]";
		mes "はい……";
		mes "もう行かれるのですか？";
		mes "確かにお嬢様がこれ以上暴走する前に";
		mes "戻った方が賢明かもしれません。";
		next;
		cutin "ep16_crux_findel02.bmp",2;
		mes "[クルックス]";
		mes "それでは、また。";
		close2;
		cutin "ep16_spica_nerius01.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,18,136,5	script	スキア・ネリウス#ep16_room01	10116,{
	cutin "ep16_skia_nerius03.bmp",0;
	mes "[スキア]";
	mes "こんにちは！";
	mes "お会い出来て光栄です！";
	close2;
	cutin "ep16_skia_nerius03.bmp",255;
	end;
}

prt_cas_q.gat,21,140,3	script	護衛騎士クルックス#ep16_room01	10118,{
	cutin "ep16_crux_findel01.bmp",1;
	mes "[クルックス]";
	mes "私の事はお気になさらず。";
	close2;
	cutin "ep16_crux_findel01.bmp",255;
	end;
}

prt_cas_q.gat,18,136,5	script(CLOAKED)	スピーカ・ネリウス#ep16_room02	10115,{
	if(EP16_1QUE == 15) {
		mes "[スピーカ]";
		mes "遅かったな……";
		cutin "ep16_skia_shadow01.bmp",1;
		next;
		mes "[スピーカ]";
		mes "何、別に理由があって";
		mes "招待したわけではない。";
		mes "儀式中にあった事件のせいで";
		mes "みんな会議ばかりでな。";
		cloakoffnpc "ニーヒル・ハイネン#ep16_nroom01";
		next;
		mes "[スピーカ]";
		mes "これはこれは……";
		mes "ハイネン家の公子か。";
		mes "謹慎処分を受けた割には";
		mes "随分と自由に歩き回っているな。";
		next;
		mes "[ニーヒル]";
		mes "そうですね。";
		mes "不思議なことにゲオルグ家から";
		mes "私への擁護と陳情があったのです。";
		mes "おかげで、西の離宮内ならば";
		mes "自由に移動できる許可が出ました。";
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		next;
		mes "[スピーカ]";
		mes "ゲオルグ家のキャサリン様が？";
		mes "というよりエルンスト王子か。";
		mes "王位継承儀式の襲撃に";
		mes "勇気ある行動をとった者に";
		mes "心をうたれたのだろう。";
		mes "どちらにせよ感謝しかないな。";
		cutin "ep16_skia_shadow01.bmp",1;
		next;
		mes "[ニーヒル]";
		mes "勇気ではありません。";
		mes "私が行動しなくても";
		mes "誰かが同じ行動をとったでしょう。";
		mes "……それに";
		mes "私が招いた襲撃事件です。";
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		next;
		cutin "ep16_skia_shadow01.bmp",1;
		mes "[スピーカ]";
		mes "そんなことはない！";
		mes "私は心をうたれた！";
		next;
		mes "[スピーカ]";
		mes "……い、いやなんでもない。";
		cutin "ep16_skia_shadow05.bmp",0;
		next;
		mes "[ニーヒル]";
		mes "ここに来たのは、";
		mes strcharinfo(0)+"様に";
		mes "伝えたい事項があったからです。";
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		next;
		mes "[ニーヒル]";
		mes "それよりスキア。";
		mes "何をしているんですか？";
		next;
		mes "[スピーカ]";
		mes "ス、スキアだと？";
		mes "わ、私はスピーカだ！";
		mes "あの子はこの場には居ないぞ！";
		cutin "ep16_skia_shadow03.bmp",0;
		next;
		mes "[ニーヒル]";
		mes "……そういう事ですか。";
		mes "それではシャドウ。";
		mes "何かあったのですか？";
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		next;
		mes "[スキア]";
		mes "……ふう。";
		mes "どうして分かったんですか？";
		cutin "ep16_skia_shadow04.bmp",0;
		next;
		mes "[ニーヒル]";
		mes "双子だとしても、";
		mes "全てが同じという事はないでしょう？";
		mes "ただ互いの違う部分を";
		mes "見ただけですよ。";
		cutin "ep16_nihi_miseria_heine02.bmp",2;
		next;
		mes "[スキア]";
		mes "そうなんですか？";
		mes "それなら……嬉しいです。";
		mes "私を見てくれていて……";
		cutin "ep16_skia_shadow05.bmp",0;
		next;
		menu "どうしてそんな姿を？",-;
		mes "[スキア]";
		mes "それは、次期当主である";
		mes "スピーカを守る為です。";
		mes "私がスピーカとして";
		mes "表に出る事もあるんですよ。";
		cutin "ep16_skia_shadow01.bmp",0;
		next;
		mes "[スキア]";
		mes "スピーカは当主として";
		mes "必要な知識を学び、";
		mes "私はスピーカを守るために、";
		mes "気配の消し方や戦い方を習いました。";
		cutin "ep16_skia_shadow02.bmp",0;
		next;
		mes "[スキア]";
		mes "常に影からスピーカを守り";
		mes "時にはスピーカの影となりました。";
		next;
		mes "[スキア]";
		mes "そんな私を人々は";
		mes "シャドウプリンセスと呼びました。";
		mes "事実、公の場で、";
		mes "こんなにも自由に動くのは";
		mes "初めてなんですよ。";
		next;
		mes "[スキア]";
		mes "とにかく、今は席を外している";
		mes "スピーカの代わりをしているんです。";
		mes "祝宴で大人しくしているところを";
		mes "見せないといけませんから。";
		cutin "ep16_skia_shadow04.bmp",0;
		next;
		mes "[ニーヒル]";
		mes "スピーカ公女は";
		mes "いつ戻られますか？";
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		next;
		mes "[スキア]";
		mes "^0000ff大事な話^000000をしに、";
		mes "^0000ffある方に会いに行く^000000と";
		mes "言っていました。";
		cutin "ep16_skia_shadow01.bmp",0;
		next;
		menu "大事な話？",-;
		mes "[スキア]";
		mes "は、はい。";
		mes "大切な人を守る、大事な話です。";
		cutin "ep16_skia_shadow05.bmp",0;
		next;
		mes "[ニーヒル]";
		mes "ところで";
		mes strcharinfo(0)+"様に";
		mes "任せたい仕事があるので";
		mes "その話を伝えに来たのです。";
		mes "ハイネン家にいらしてほしいのです。";
		cutin "ep16_nihi_miseria_heine04.bmp",2;
		next;
		menu "わざわざ来てくれたの？",-;
		mes "[ニーヒル]";
		mes strcharinfo(0)+"様が";
		mes "ネリウス家を訪問していると聞いて、";
		mes "父が私に行くように言ったのです。";
		next;
		cutin "ep16_skia_shadow03.bmp",0;
		mes "[スキア]";
		mes "フリードリヒ様が？";
		mes "おそらく儀式で起きた事に";
		mes "ついての話ですよね。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "それは直接聞いてほしいです。";
		next;
		mes "[ニーヒル]";
		mes "話が長くなりましたが";
		mes "まずはお爺様とお父様に";
		mes "会って下さい。";
		next;
		cutin "ep16_skia_shadow04.bmp",0;
		mes "[スキア]";
		mes "……分かりました。";
		mes "詳しい事はスピーカが戻ったら";
		mes "直接聞いてみます。";
		next;
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "それでは行きましょう。";
		next;
		cutin "ep16_skia_shadow04.bmp",0;
		mes "[スキア]";
		mes strcharinfo(0)+"様、";
		mes "ニーヒル様";
		mes "また来てくださいね。";
		setquest 7698;
		delquest 7697;
		set EP16_1QUE,16;
		close2;
		cutin "ep16_nihi_miseria_heine01.bmp",255;
		end;
	} else if(EP16_1QUE == 16 || EP16_1QUE == 17) {
		mes "[スキア]";
		mes "私はスピーカが戻るまでは";
		mes "服を着替えられませんので";
		mes "この場を離れられません。";
		cutin "ep16_skia_shadow04.bmp",1;
		next;
		mes "[スキア]";
		mes "もし、スピーカと";
		mes "鉢合わせてしまったら";
		mes "大変な事になりますから。";
		close2;
		cutin "ep16_nihi_miseria_heine01.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,23,133,2	script(CLOAKED)	ニーヒル・ハイネン#ep16_nroom01	10114,{
	if(EP16_1QUE == 16) {
		cutin "ep16_nihi_miseria_heine01.bmp",2;
		mes "[ニーヒル]";
		mes "状況があまり良くありません。";
		mes "早く移動した方が良いでしょう。";
		close2;
		cutin "ep16_nihi_miseria_heine01.bmp",255;
		end;
	}
	end;
}

prt_cas.gat,321,25,1	script	エリヒ・ネリウス#ep16_erihi	881,{
	mes "[エリヒ]";
	mes "祝宴を開いてるだけあって、";
	mes "随分とにぎやかだね。";
	mes "でも、ここは図書館だから";
	mes "静かにしてくれるかな？";
	close;
}

prt_cas_q.gat,20,184,3	script	イアン・バルター#ep16wal	55,10,10,{
	if(EP16_1QUE < 2) {
		mes "[イアン]";
		mes "ここにどうやって";
		mes "入って来た？";
		mes "人を呼んで追い出す前に、";
		mes "出て行くがいい！";
		close;
	}
	if(EP16_3QUE == 0) {
		mes "[イアン]";
		mes "おや、貴方は？";
		next;
		menu "ご挨拶に伺いました",-;
		mes "[イアン]";
		mes "貴方が今回の祝宴に招待された";
		mes "冒険者様ですね。";
		mes "お招きしたのは、正確には";
		mes "王位継承の儀式のほうですが……";
		mes "異世界にて活躍された方と";
		mes "お会いできて光栄です。";
		next;
		mes "[イアン]";
		mes "おっと、失礼。";
		mes "私はバルター家の当主、";
		mes "^0000cdイアン・バルター^000000と申します。";
		next;
		mes "[イアン]";
		mes "バルター家は、";
		mes "騎士道を重んじる家門です。";
		mes "また、海上貿易も営んでおり";
		mes "国のために貢献しております。";
		next;
		mes "[イアン]";
		mes "ところで、我が^0000cdバルター家は";
		mes "王位継承には参加しません^000000が、";
		mes "七王家の中の一つとして";
		mes "儀式には参列させていただくことに";
		mes "なっております。";
		mes "よろしくお願いします。";
		next;
		mes "[イアン]";
		mes "……ご存じかもしれませんが、";
		mes "以前、各王家から継承候補者が";
		mes "一同に集まったことがありました。";
		mes "その時に、我が家門の候補者に";
		mes "^0000cd不幸な事故^000000が起きてしまったのです。";
		next;
		menu "不幸な事故？",-;
		mes "[イアン]";
		mes "左様。我が家門の王位候補者";
		mes "^0000cdアイゼン・アルム^000000が不祥事を起こし、";
		mes "^0000cdゲオルグ家の後継者によって";
		mes "^0000cd処断された^000000のです。";
		next;
		mes "[イアン]";
		mes "これを受けて、我が家門は";
		mes "自粛する意味として";
		mes "^0000cd今回の王位継承に";
		mes "^0000cd参加しないことに決定^000000しました。";
		next;
		mes "[イアン]";
		mes "……申し訳ない。";
		mes "このような祝いの場で";
		mes "不吉な話をしてしまいましたね。";
		next;
		mes "[アイゼン・アノ]";
		mes "……";
		next;
		mes "[イアン]";
		mes "アイゼン・アノ、";
		mes "こちらに来なさい。";
		mes "　";
		mes "‐バルター家当主の言葉に";
		mes "　一人の青年がこちらへ";
		mes "　近づいてきた‐";
		next;
		mes "[イアン]";
		mes "こちらは^0000cd私の甥である";
		mes "^0000cdアイゼン・アノ^000000です。";
		mes "今年の成人の儀を迎えれば";
		mes "家門の長になりバルター家を";
		mes "継ぐことになります。";
		next;
		mes "[アイゼン・アノ]";
		mes "初めまして。";
		mes "^0000cdアイゼン・アノ・バルター^000000です。";
		mes "お会いできて光栄です。";
		next;
		if(select("挨拶を返す","王位継承の話を振る") == 1) {
			mes "[アイゼン・アノ]";
			mes "まだまだ若輩の私に";
			mes "ありがとうございます。";
			mes "冒険者様は……";
			next;
		}
		mes "‐アイゼン・アノとの対話に";
		mes "　割り込むようにして、";
		mes "　当主イアンが声を上げた‐";
		next;
		mes "[イアン]";
		mes "冒険者様！";
		mes "そろそろ祝宴も盛り上がるころです。";
		mes "どうか、楽しんでください。";
		next;
		delquest 73052;
		//setquest 14469;
		//compquest 14469;
		setquest 73070;
		set EP16_3QUE,1;
		if((checkquest(7683)&0x8) && !checkquest(73051) && !checkquest(73053) && !checkquest(73052) && !checkquest(73054) && !checkquest(73055) && !checkquest(73056)) {
			mes "‐^0000cd七王家すべてに挨拶をした。^000000";
			mes "　ベルのところに戻ろう‐";
		} else {
			mes "‐^0000cdバルター家との挨拶を済ました。^000000";
			mes "　他の王家にも挨拶に行こう‐";
		}
		next;
		mes "‐その時、アイゼン・アノが";
		mes "　話しかけてきた‐";
		next;
		mes "[アイゼン・アノ]";
		mes "……";
		mes "少し、お話があります。";
		mes "よろしければ、";
		mes "私に話しかけてください。";
		close;
	}
	if(EP16_3QUE <= 1 && !(checkquest(14516) & 0x8)) {
		cloakoffnpc "怪しい人#ep16wal";
		mes "[リハルト家門の人間]";
		mes "お久しぶりです。";
		mes "イアン様。";
		next;
		mes "[イアン]";
		mes "何用だ!?";
		mes "^0000cd以前の王位継承以降^000000、";
		mes "接触することは";
		mes "今後一切しないと";
		mes "互いに結論付けたはず！";
		next;
		mes "[リハルト家門の人間]";
		mes "もちろん承知していますとも。";
		mes "ですが……";
		next;
		mes "[リハルト家門の人間]";
		mes "最近、そちらの後継者が";
		mes "方々を嗅ぎまわっているという話を";
		mes "小耳にはさみましてね。";
		next;
		mes "[リハルト家門の人間]";
		mes "まあ、唯一幸いなことに";
		mes "周囲の者は彼を";
		mes "相手にしていないようですが……";
		next;
		mes "[イアン]";
		mes "……その話か。";
		mes "すでに手は打った。";
		next;
		mes "[イアン]";
		mes "アイゼン・アノには、";
		mes "^0000cd兄のことは忘れろ^000000と";
		mes "言い含めておいてある。";
		next;
		mes "[リハルト家門の人間]";
		mes "それが最善でしょう。";
		next;
		mes "[リハルト家門の人間]";
		mes "万が一にでも、我々が";
		mes "^0000cdゲオルグ家の王位候補を";
		mes "^0000cd殺めようとしていた^000000と";
		mes "知られるわけにはいきませんからな。";
		next;
		mes "[イアン]";
		mes "……口にするんじゃない。";
		mes "どこで誰が聞いているかもわからんぞ。";
		next;
		mes "[リハルト家門の人間]";
		mes "おや、失礼。";
		mes "……まあ、計画は";
		mes "アイゼン・アルム様が暴走されたせいで";
		mes "^0000cdことを起こす前につぶれた^000000";
		mes "ものですし。";
		next;
		mes "[リハルト家門の人間]";
		mes "バルター家の後継者でもあった";
		mes "アイゼン・アルム様の件は";
		mes "誠に遺憾でしたよ。";
		next;
		mes "[イアン]";
		mes "……誰が後継者になろうと";
		mes "我が家門をうまく";
		mes "続けてくれるならば関係ない。";
		next;
		mes "[イアン]";
		mes "しかし、なぜ";
		mes "いつも正義のためと動いていた";
		mes "アイゼン・アルムが";
		mes "あのような行動を起こしたのか……";
		next;
		mes "[リハルト家門の人間]";
		mes "……それは気にはなります。";
		mes "かといって";
		mes "今更、追求することは叶いません。";
		next;
		mes "[イアン]";
		mes "ゲオルグ家の後継者も";
		mes "口を閉ざしているようじゃないか。";
		next;
		mes "[リハルト家門の人間]";
		mes "はい、そうだと聞いています。";
		next;
		mes "[リハルト家門の人間]";
		mes "どちらにせよ、アイゼン・アルム様が";
		mes "ゲオルグ家の後継者に";
		mes "殺されてしまったせいで、";
		mes "^0000cdバルター家は、此度の";
		mes "^0000cd王位継承に参加できなくなった^000000のは";
		mes "残念でした。";
		next;
		mes "[リハルト家門の人間]";
		mes "残されたバルターの後継者が、";
		mes "この件を追うことを止められぬなら、";
		mes "せめて注意と監視は";
		mes "怠らぬようにお願いいたします。";
		next;
		mes "[リハルト家門の人間]";
		mes "王位欲しさに当主が他の家門の";
		mes "王子を暗殺しようとした、";
		mes "などということが表沙汰になれば、";
		mes "一番困るのはイアン様では？";
		next;
		mes "[イアン]";
		mes "貴様、私を脅迫する気か!?";
		next;
		mes "[リハルト家門の人間]";
		mes "しっ！";
		mes "静かに。大声は出さないでください。";
		mes "バルターの後継者様に";
		mes "聞こえてしまいますよ。";
		next;
		mes "[リハルト家門の人間]";
		mes "私が話したいのは、ただ";
		mes "互いに気を付けましょう、と。";
		mes "それだけです。";
		next;
		mes "[イアン]";
		mes "……";
		next;
		mes "[リハルト家門の人間]";
		mes "おっと、そろそろ戻らねば。";
		mes "それでは失礼します。";
		mes "互いに良い祝宴を過ごしましょう。";
		next;
		cloakonnpc "怪しい人#ep16wal";
		mes "[イアン]";
		mes "クソッ生意気な！";
		mes "あんな奴とこれからも";
		mes "手を組まなければいけないのか！";
		next;
		mes "[イアン]";
		mes "……結局、残ったものが";
		mes "有能な甥の死だけ、とは……";
		mes "　";
		mes "とんだお笑い種だ。";
		setquest 14516;
		compquest 14516;
		close;
	}
	if(EP16_1QUE == 2) {
		mes "[イアン]";
		mes "そろそろ祝宴も盛り上がるころです。";
		mes "どうか、楽しんでください。";
		close;
	}
	mes "[イアン]";
	mes "祝宴は楽しんでいますか？";
	mes "貴方がたのための祝宴です。";
	mes "心行くまで楽しんでください。";
	close;
OnTouch:
	if(EP16_3QUE <= 1 && !(checkquest(14516) & 0x8)) {
		cloakoffnpc "怪しい人#ep16wal";
		mes "[リハルト家門の人間]";
		mes "お久しぶりです。";
		mes "イアン様。";
		next;
		mes "[イアン]";
		mes "何用だ!?";
		mes "^0000cd以前の王位継承以降^000000、";
		mes "接触することは";
		mes "今後一切しないと";
		mes "互いに結論付けたはず！";
		next;
		mes "[リハルト家門の人間]";
		mes "もちろん承知していますとも。";
		mes "ですが……";
		next;
		mes "[リハルト家門の人間]";
		mes "最近、そちらの後継者が";
		mes "方々を嗅ぎまわっているという話を";
		mes "小耳にはさみましてね。";
		next;
		mes "[リハルト家門の人間]";
		mes "まあ、唯一幸いなことに";
		mes "周囲の者は彼を";
		mes "相手にしていないようですが……";
		next;
		mes "[イアン]";
		mes "……その話か。";
		mes "すでに手は打った。";
		next;
		mes "[イアン]";
		mes "アイゼン・アノには、";
		mes "^0000cd兄のことは忘れろ^000000と";
		mes "言い含めておいてある。";
		next;
		mes "[リハルト家門の人間]";
		mes "それが最善でしょう。";
		next;
		mes "[リハルト家門の人間]";
		mes "万が一にでも、我々が";
		mes "^0000cdゲオルグ家の王位候補を";
		mes "^0000cd殺めようとしていた^000000と";
		mes "知られるわけにはいきませんからな。";
		next;
		mes "[イアン]";
		mes "……口にするんじゃない。";
		mes "どこで誰が聞いているかもわからんぞ。";
		next;
		mes "[リハルト家門の人間]";
		mes "おや、失礼。";
		mes "……まあ、計画は";
		mes "アイゼン・アルム様が暴走されたせいで";
		mes "^0000cdことを起こす前につぶれた^000000";
		mes "ものですし。";
		next;
		mes "[リハルト家門の人間]";
		mes "バルター家の後継者でもあった";
		mes "アイゼン・アルム様の件は";
		mes "誠に遺憾でしたよ。";
		next;
		mes "[イアン]";
		mes "……誰が後継者になろうと";
		mes "我が家門をうまく";
		mes "続けてくれるならば関係ない。";
		next;
		mes "[イアン]";
		mes "しかし、なぜ";
		mes "いつも正義のためと動いていた";
		mes "アイゼン・アルムが";
		mes "あのような行動を起こしたのか……";
		next;
		mes "[リハルト家門の人間]";
		mes "……それは気にはなります。";
		mes "かといって";
		mes "今更、追求することは叶いません。";
		next;
		mes "[イアン]";
		mes "ゲオルグ家の後継者も";
		mes "口を閉ざしているようじゃないか。";
		next;
		mes "[リハルト家門の人間]";
		mes "はい、そうだと聞いています。";
		next;
		mes "[リハルト家門の人間]";
		mes "どちらにせよ、アイゼン・アルム様が";
		mes "ゲオルグ家の後継者に";
		mes "殺されてしまったせいで、";
		mes "^0000cdバルター家は、此度の";
		mes "^0000cd王位継承に参加できなくなった^000000のは";
		mes "残念でした。";
		next;
		mes "[リハルト家門の人間]";
		mes "残されたバルターの後継者が、";
		mes "この件を追うことを止められぬなら、";
		mes "せめて注意と監視は";
		mes "怠らぬようにお願いいたします。";
		next;
		mes "[リハルト家門の人間]";
		mes "王位欲しさに当主が他の家門の";
		mes "王子を暗殺しようとした、";
		mes "などということが表沙汰になれば、";
		mes "一番困るのはイアン様では？";
		next;
		mes "[イアン]";
		mes "貴様、私を脅迫する気か!?";
		next;
		mes "[リハルト家門の人間]";
		mes "しっ！";
		mes "静かに。大声は出さないでください。";
		mes "バルターの後継者様に";
		mes "聞こえてしまいますよ。";
		next;
		mes "[リハルト家門の人間]";
		mes "私が話したいのは、ただ";
		mes "互いに気を付けましょう、と。";
		mes "それだけです。";
		next;
		mes "[イアン]";
		mes "……";
		next;
		mes "[リハルト家門の人間]";
		mes "おっと、そろそろ戻らねば。";
		mes "それでは失礼します。";
		mes "互いに良い祝宴を過ごしましょう。";
		next;
		cloakonnpc "怪しい人#ep16wal";
		mes "[イアン]";
		mes "クソッ生意気な！";
		mes "あんな奴とこれからも";
		mes "手を組まなければいけないのか！";
		next;
		mes "[イアン]";
		mes "……結局、残ったものが";
		mes "有能な甥の死だけ、とは……";
		mes "　";
		mes "とんだお笑い種だ。";
		setquest 14516;
		compquest 14516;
		close;
	}
	end;
}

prt_cas_q.gat,23,187,3	script(CLOAKED)	怪しい人#ep16wal	86,{}

prt_cas_q.gat,14,184,5	script	アイゼン・アノ#ep16wal	983,{
	switch(EP16_3QUE) {
	case 0:
		mes "[アイゼン・アノ]";
		mes "冒険者様ですね。";
		mes "こんな場所まで";
		mes "訪ねてくださるとは……";
		next;
		mes "[アイゼン・アノ]";
		mes "私たちの家門を";
		mes "代表する方はあちらにいます。";
		mes "ご挨拶されるなら、";
		mes "当主であるイアン様からどうぞ。";
		close;
	case 1:
		mes "[アイゼン・アノ]";
		mes "……話したいことがあります。";
		next;
		switch(select("ちゃんと話をしたかったです","アイゼン・アルムについて")) {
		case 1:
			mes "[アイゼン・アノ]";
			mes "兄さんが暴れ、殺された";
			mes "あの話について、ですか？";
			mes "あなたもあのありえない噂を";
			mes "本当に信じているのですか？";
			next;
			mes "[アイゼン・アノ]";
			mes "兄さんがあんな事件を……";
			mes "しかも、暴力をふるうなんて";
			mes "ありえません。";
			break;
		case 2:
			mes "[アイゼン・アノ]";
			mes "確かに。";
			mes "先ほどのイアン様は";
			mes "少々わざとらしかったですからね。";
			next;
			mes "[アイゼン・アノ]";
			mes "そうまでしてでも、私に";
			mes "自由を与えたくないようです。";
			next;
			mes "[アイゼン・アノ]";
			mes "……あなたもバルター家の噂は";
			mes "ご存じでしょう？";
			mes "アイゼン・アルム……兄さんが";
			mes "暴れ、殺されたあの話を。";
			next;
			mes "[アイゼン・アノ]";
			mes "いいえ、";
			mes "兄さんがあんな事件を……";
			mes "しかも、暴力をふるうなんてこと";
			mes "するはずがないんです。";
			break;
		}
		next;
		mes "[アイゼン・アノ]";
		mes "たとえ、それが本当だとしても";
		mes "……";
		next;
		mes "[アイゼン・アノ]";
		mes "兄さんは……兄さんには……！";
		mes "なにか理由があって";
		mes "そうしたはずです！";
		next;
		mes "[アイゼン・アノ]";
		mes "しかし真実は誰も知らず、";
		mes "噂だけをみんな信じています……";
		next;
		mes "[アイゼン・アノ]";
		mes "……";
		mes "あなたに話したかったのは、";
		mes "まさに兄さんのことなんです。";
		mes "兄さんの、あの事件……";
		mes "真実を知りたいのです。";
		next;
		switch(select("乱心したのでは？","あなたは何もしないんですか？")) {
		case 1:
			mes "[アイゼン・アノ]";
			mes "もちろん、調査はしています！";
			mes "だけど家門のお偉い方たちは";
			mes "私が過去を掘り返してまで";
			mes "^0000cd調査してまわっていることを";
			mes "^0000cdあまり好ましく考えてない^000000ようです。";
			next;
			mes "[アイゼン・アノ]";
			mes "あの^0000cdエルンスト・ゲオルグ^000000と";
			mes "面会することもできていないのです。";
			break;
		case 2:
			mes "[アイゼン・アノ]";
			mes "まさか！";
			mes "先ほども言ったように";
			mes "私は真実は別にあると思っています。";
			next;
			mes "[アイゼン・アノ]";
			mes "しかし、イアン様を見たでしょう？";
			mes "私が^0000cd調査していることを";
			mes "^0000cdバルター家の人間は";
			mes "^0000cdあまり好ましく考えてない^000000ようです。";
			next;
			mes "[アイゼン・アノ]";
			mes "ひどく妨害され、一番重要な";
			mes "^0000cdエルンスト・ゲオルグ^000000と";
			mes "面会さえできないのです。";
			break;
		}
		next;
		switch(select("エルンスト・ゲオルグ？","会えないのですか？")) {
		case 1:
			mes "[アイゼン・アノ]";
			mes "はい。";
			mes "家の者は、私が";
			mes "エルンストに会うことを";
			mes "一番許していないようです。";
			break;
		case 2:
			mes "[アイゼン・アノ]";
			mes "そうです。";
			mes "彼は現王家であるゲオルグ家から";
			mes "選出された王位継承候補者でした。";
			mes "兄さんと一番仲が良くて……";
			mes "そして、兄さんを処断したと";
			mes "言われている人物です。";
			next;
			mes "[アイゼン・アノ]";
			mes "事件後、彼は";
			mes "引きこもっているそうですが……";
			break;
		}
		next;
		mes "[アイゼン・アノ]";
		mes "しかし、事件の日を知っているのは";
		mes "兄さんのそばにいた^0000cd守護騎士^000000と";
		mes "兄さんを刺した^0000cdエルンスト・ゲオルグ^000000の";
		mes "はずなのです。";
		next;
		mes "[アイゼン・アノ]";
		mes "会うことが叶わない今、";
		mes "どこから調べればいいのか……";
		mes "どうか冒険者様の";
		mes "お力添えを頂けないでしょうか。";
		next;
		while(1) {
			switch(select("エルンスト・ゲオルグに会おう","守護騎士から聞こう","聞き込みから")) {
			case 1:
				mes "[アイゼン・アノ]";
				mes "いえ、だから";
				mes "彼には会えないんですって。";
				mes "私も色々試しましたが";
				mes "八方ふさがりの状態なんです。";
				mes "これ以上は無理です。";
				next;
				continue;
			case 2:
				break;
			case 3:
				mes "[アイゼン・アノ]";
				mes "状況を調べた結果、";
				mes "当日、兄さんのそばにいたのは";
				mes "^0000cd守護騎士^000000と";
				mes "^0000cdエルンスト・ゲオルグ^000000だと";
				mes "聞いています。";
				mes "……しかし、";
				next;
				continue;
			}
			break;
		}
		mes "[アイゼン・アノ]";
		mes "守護騎士から……？";
		next;
		menu "守護騎士はどこに？",-;
		mes "[アイゼン・アノ]";
		mes "……解雇しました。";
		next;
		mes "[アイゼン・アノ]";
		mes "私は兄さんの守護騎士が";
		mes "兄さんを見捨てて逃げたので、";
		mes "嫌になって、解雇したのです。";
		mes "もちろん自分の守護騎士も。";
		next;
		mes "[アイゼン・アノ]";
		mes "……今は";
		mes "守護騎士という言葉すら、";
		mes "口にしたくないですよ。";
		next;
		menu "守護騎士に会いましょう",-;
		mes "[アイゼン・アノ]";
		mes "しかし、守護騎士と言われながら";
		mes "忠誠を誓った主君を裏切って";
		mes "逃げた者を……！";
		next;
		mes "[アイゼン・アノ]";
		mes "……いえ、そうですね。";
		mes "エルンスト・ゲオルグから";
		mes "当たれないのなら、";
		mes "守護騎士から調べるのは";
		mes "当然の流れでしょう。";
		next;
		mes "[アイゼン・アノ]";
		mes "私の守護騎士だった者と";
		mes "兄さんの守護騎士は";
		mes "共に訓練をしていた仲と";
		mes "聞いています。";
		next;
		mes "[アイゼン・アノ]";
		mes "兄さんの守護騎士を探すなら、";
		mes "私の守護騎士を務めていた者を";
		mes "頼るといいでしょう。";
		next;
		mes "[アイゼン・アノ]";
		mes "……しかし、私は";
		mes "彼らを切り捨てた人間です。";
		mes "今更会わせる顔など……";
		next;
		mes "[アイゼン・アノ]";
		mes "いや、でも……";
		mes "私は兄さんになにがあったのか、";
		mes "真実を知りたいのです。";
		next;
		mes "[アイゼン・アノ]";
		mes "冒険者様。";
		mes "どうか、彼らを探しては";
		mes "もらえませんか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[アイゼン・アノ]";
			mes "……そうですか。";
			mes "そうですよね。";
			mes "どんなに私が知りたくとも";
			mes "貴方には関係のないことでした。";
			mes "ここまで聞いてもらえただけでも";
			mes "ありがたいと思わなければ。";
			next;
			mes "[アイゼン・アノ]";
			mes "しかし、もし";
			mes "気が変わって";
			mes "協力していただけるなら、";
			mes "その時は私を訪ねてください。";
			next;
			mes "[アイゼン・アノ]";
			mes "私はなんとか彼らに";
			mes "会いに行けるよう";
			mes "あがいてみましょう。";
			close;
		}
		mes "[アイゼン・アノ]";
		mes "ありがとうございます！";
		mes "私の守護騎士は……";
		mes "傍付きを拒否はしましたが";
		mes "バルター家の騎士としては";
		mes "在籍しているはずです。";
		next;
		mes "[アイゼン・アノ]";
		mes "^0000cdアルベルタの南側にある";
		mes "^0000cdバルター家の邸宅^000000にいると思います。";
		mes "名前は";
		mes "^0000cdサイマン・バルター・マーシャル^000000です。";
		mes "よろしくお願いします。";
		delquest 14516;
		delquest 73070;
		setquest 14470;
		set EP16_3QUE,2;
		next;
		mes "‐アルベルタの南側にある";
		mes "　バルター家の邸宅に向かおうかな？‐";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐バルター家の邸宅に向かった‐";
		close2;
		warp "alberta.gat",49,36;
		end;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		mes "[アイゼン・アノ]";
		mes "守護騎士だったサイマンには";
		mes "会えましたか？";
		mes "まだバルター家にいてくれたなら";
		mes "^0000cdアルベルタの南側にある";
		mes "^0000cdバルター家の邸宅^000000にいると思います。";
		next;
		mes "[アイゼン・アノ]";
		mes "……怒りにまかせて";
		mes "解雇してしまったことを";
		mes "今更ながらに後悔しています。";
		next;
		mes "[アイゼン・アノ]";
		mes "ちゃんと話をきいてやれたら";
		mes "なにか変わっていたでしょうか。";
		next;
		mes "‐アルベルタの南側にある";
		mes "　バルター家の邸宅に向かおうかな？‐";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐バルター家の邸宅に向かった‐";
		close2;
		warp "alberta.gat",49,36;
		end;
	case 7:
		mes "[アイゼン・アノ]";
		mes "戻りましたね。";
		mes "成果はありましたか？";
		next;
		mes "‐アイゼン・アルムの守護騎士と";
		mes "　出会えた経緯と、";
		mes "　会って話した内容を簡単に";
		mes "　聞かせた‐";
		next;
		mes "[アイゼン・アノ]";
		mes "これがその^0000cd手紙^000000ですか。";
		mes "……確かに";
		mes "うちの家門の紋章と";
		mes "兄さんの筆跡に間違いありません。";
		next;
		mes "[アイゼン・アノ]";
		mes "その守護騎士は噂のように";
		mes "兄さんを裏切って離れた";
		mes "わけではなさそうですね。";
		next;
		mes "[アイゼン・アノ]";
		mes "やはり兄さんは何の理由もなく、";
		mes "あのような行動を";
		mes "起こしたわけではなかった……";
		mes "何か、目的があったんですね。 ";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "私がやれるのは";
		mes "ここまでのようです。";
		next;
		mes "[アイゼン・アノ]";
		mes "はい。";
		mes "ここからは私の役目です。";
		mes "ここまでご協力いただき、";
		mes "ありがとうございます。";
		next;
		mes "[アイゼン・アノ]";
		mes "バルター家の力が必要な時は";
		mes "いつでも訪ねて来て下さい。";
		next;
		if(checkitemblank() == 0) {
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		mes "[アイゼン・アノ]";
		mes "冒険者様は今後、";
		mes "バルター家の大事な";
		mes "お客さまです。";
		mes "いつでも協力します。";
		delitem 6929,1;
		delquest 14474;
		setquest 201900;
		set EP16_3QUE,8;
		getitem 6919,30;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		close;
	case 8:
		mes "[アイゼン・アノ]";
		mes "冒険者様が知らせてくれた";
		mes "情報を元に、";
		mes "今は他の情報を集めています。";
		mes "まだ足りませんがいつかは";
		mes "真実を明かすことができると";
		mes "考えています。";
		next;
		mes "[アイゼン・アノ]";
		mes "アルベルタに行っている";
		mes "サイマンも呼びました。";
		mes "今は一人でも多くの力が";
		mes "必要とされる時ですから。";
		next;
		mes "[アイゼン・アノ]";
		mes "真実が明かされる日が来たら、";
		mes "冒険者様を再度お呼びします。";
		close;
	}
	end;
}

alberta.gat,48,33,7	script	バルター家の執事#ep16wal	109,{
	switch(EP16_3QUE) {
	case 2:
		mes "[バルター家の執事]";
		mes "今日も天気がいい！";
		mes "しかし……今は屋敷に";
		mes "誰も居ないのがなあ。";
		mes "寂しいものだ。";
		next;
		menu "すいません、バルター家の邸宅ですか？",-;
		mes "[バルター家の執事]";
		mes "そうですが……";
		mes "何か御用でしょうか？";
		mes "今は皆プロンテラに出払っており、";
		mes "残念ながら、お会いできるものが";
		mes "おりませんが……";
		next;
		menu "アイゼン・アノから頼まれて来ました",-;
		mes "[バルター家の執事]";
		mes "おお、そうなのですね！";
		mes "アイゼン・アノ様に呼ばれることを";
		mes "あれほど待っていた";
		mes "甲斐がありました。";
		next;
		mes "[バルター家の執事]";
		mes "アイゼン・アノ様の守護騎士、";
		mes "サイマンは^0000cdイズルード^000000に";
		mes "出発する船が停泊している";
		mes "^0000cd船着き場^000000の近くにいます。";
		next;
		mes "[バルター家の執事]";
		mes "いつでもアイゼン・アノ様の呼びかけがあれば、";
		mes "プロンテラに少しでも早く";
		mes "向かえるようにいつもあそこで";
		mes "待っています。";
		next;
		mes "[バルター家の執事]";
		mes "イズルード行きの船がある場所に";
		mes "行って見て下さい。";
		mes "そこにいると思います。";
		delquest 14470;
		setquest 73058;
		set EP16_3QUE,3;
		next;
		mes "‐イズルード行きの船がある場所に";
		mes "　向かおうかな？‐";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐イズルード行きの船がある場所に";
		mes "　向かった‐";
		close2;
		warp "alberta.gat",188,142;
		end;
	case 3:
		mes "[バルター家の執事]";
		mes "アイゼン・アノ様の守護騎士、";
		mes "サイマンは^0000cdイズルード^000000に";
		mes "出発する船が停泊している";
		mes "^0000cd船着き場^000000の近くにいます。";
		next;
		mes "[バルター家の執事]";
		mes "いつでもアイゼン・アノ様の呼びかけがあれば、";
		mes "プロンテラに少しでも早く";
		mes "向かえるようにいつもあそこで";
		mes "待っています。";
		next;
		mes "[バルター家の執事]";
		mes "イズルード行きの船がある場所に";
		mes "行って見て下さい。";
		mes "そこにいると思います。";
		next;
		mes "‐イズルード行きの船がある場所に";
		mes "　向かおうかな？‐";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐イズルード行きの船がある場所に";
		mes "　向かった‐";
		close2;
		warp "alberta.gat",188,142;
		end;
	case 4:
		mes "[バルター家の執事]";
		mes "今日も天気がいい！";
		mes "しかし……今は屋敷に";
		mes "誰も居ないのがなあ。";
		mes "寂しいものだ。";
		close;
	default:
		mes "[バルター家の執事]";
		mes "アルスキィ家の執事、";
		mes "マハト……";
		mes "黙っていたら調子に";
		mes "のりやがって……！";
		mes "もうこれ以上は許せん!!";
		next;
		mes "[バルター家の執事]";
		mes "たかが邸宅を一軒持ってるだけで、";
		mes "アルベルタ最高の家門？";
		mes "バルター家をなんだと";
		mes "思っているんだ!!";
		next;
		mes "[バルター家の執事]";
		mes "我々が目の前にいたら";
		mes "目も合わせられない";
		mes "小物の分際で……。";
		next;
		mes "[バルター家の執事]";
		mes "ご主人様は優しい方だから";
		mes "許しているが……";
		mes "これだから教養が無い";
		mes "輩は困る。";
		close;
	}
}

alberta.gat,187,147,7	script	守護騎士#ep16wal	470,{
	switch(EP16_3QUE) {
	case 3:
		mes "[サイマン]";
		mes "……";
		mes "風を感じる……";
		mes "何か事件が起きる気がします。";
		next;
		menu "アイゼン・アノの守護騎士ですか？",-;
		mes "[サイマン]";
		mes "私がアイゼン・アノ様の";
		mes "守護騎士ですが……";
		mes "何の御用でしょうか？";
		mes "まさか……";
		mes "アイゼン・アノ様の身に何か!?";
		emotion 0,"守護騎士#ep16wal";
		next;
		mes "[サイマン]";
		mes "やはりこのような場所で";
		mes "待っている場合ではなかった!!";
		mes "若旦那はご無事ですか!?";
		next;
		mes "[サイマン]";
		mes "誘拐？　傷害？　強盗？";
		mes "何が起きたんですか？";
		mes "ああ……！　今すぐにでも";
		mes "出発するべきか!?";
		next;
		menu "落ち着いてくださいな",-;
		mes "[サイマン]";
		mes "はあ……若旦那様が私を呼んだのでは";
		mes "ないんですね。";
		mes "それでも無事だと言うので";
		mes "良かったです。";
		next;
		mes "[サイマン]";
		mes "では、私に何の用が？";
		mes "いや、それよりあなたは";
		mes "どちら様でしょう。";
		next;
		mes "‐今までのことをサイマンに話した‐";
		next;
		mes "[サイマン]";
		mes "これは、失礼しました……";
		mes "私は^0000cdサイマン・バルター・マーシャル^000000です。";
		next;
		mes "[サイマン]";
		mes "申し訳ないのですが、私も";
		mes "アイゼン・アルム様の守護騎士だった";
		mes "^0000cdケイン・バルター・ウォーカー^000000の";
		mes "行方に関しては私も";
		mes "分からないのです。";
		next;
		menu "名前にすべてバルターが入りますね",-;
		mes "[サイマン]";
		mes "バルター家門に所属された以上、";
		mes "バルター家門の人たちに";
		mes "配属された騎士たちはすべて";
		mes "バルターという名前を貰う";
		mes "しきたりなんです。";
		next;
		mes "[サイマン]";
		mes "同じ名前を与えられてると、";
		mes "所属感が増します。";
		mes "またそれは優れた騎士として";
		mes "認定されたという大きな";
		mes "自負心でもあります。";
		next;
		menu "ケインの居場所を知っている人は？",-;
		mes "[サイマン]";
		mes "実は、アイゼン・アノ様を";
		mes "王宮までお送りした時、";
		mes "騎士団にちょっと寄ったのですが、";
		mes "その時に何人かの騎士たちから";
		mes "^0000cd怪しい噂^000000を聞いたことがあります。";
		next;
		mes "[サイマン]";
		mes "^0000cdプロンテラ監獄に入れられているスリ^000000が";
		mes "他の国で^0000cdバルター家の人を見た^000000と";
		mes "話しをしているのを聞いたらしいです。";
		next;
		mes "[サイマン]";
		mes "だけど最近は王宮で行わる祝宴のせいで";
		mes "国外に出られる方はいなかったので、";
		mes "怪しいと思いました。";
		mes "私の考えではたぶん彼が";
		mes "^0000cdケイン^000000のようです。";
		next;
		mes "[サイマン]";
		mes "かなり気になる内容でしたし、";
		mes "私の方で直接";
		mes "調べたかったのですが……";
		mes "アイゼン・アノ様からアルベルタに戻れと";
		mes "命じられてしまい、どうする事もできなくて";
		mes "ここに戻る事になってしまいました。";
		next;
		menu "プロンテラ監獄のスリ？",-;
		mes "[サイマン]";
		mes "はい。";
		mes "本名は分かりませんが、";
		mes "そっちの世界では";
		mes "^0000cdビッグフットマン^000000と";
		mes "呼ばれているみたいですよ。";
		next;
		mes "[サイマン]";
		mes "元々はスリ程度の比較的";
		mes "罪の軽い犯罪者は他の場所に監禁しますが、";
		mes "彼はアルナベルツ側でもスリをしていて";
		mes "つかまったらしいです。";
		next;
		mes "[サイマン]";
		mes "外交上の問題もあり、";
		mes "私たちの方で引き継いだ後、";
		mes "王宮の地下監獄に";
		mes "収容されたらしいです。";
		mes "ちなみにプロンテラ中央宮から";
		mes "地下監獄に行けますよ。";
		next;
		mes "[サイマン]";
		mes "その者は大陸のあらゆる所を";
		mes "旅しているせいか分かりませんが、";
		mes "色んな情報を持っているそうです。";
		next;
		mes "[サイマン]";
		mes "それでバルター家の人を";
		mes "目撃したのが事実じゃなくても、";
		mes "情報を得る事が出来るかもしれないと";
		mes "考えていましたが……";
		next;
		menu "情報ありがとうございます",-;
		mes "[サイマン]";
		mes "王宮に戻りましたら";
		mes "若旦那によろしくお伝えください。";
		mes "ここは私が確かに守っていると。";
		next;
		mes "[サイマン]";
		mes "そして私が必要な時は、";
		mes "いつでも向かうように";
		mes "準備はしていると";
		mes "伝えて下さい。";
		next;
		mes "[サイマン]";
		mes "では、お気をつけて。";
		delquest 73058;
		setquest 14471;
		set EP16_3QUE,4;
		next;
		mes "‐プロンテラ中央宮から";
		mes "　プロンテラ監獄に行けるらしい。";
		mes "　向かおうかな？‐";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐プロンテラ監獄に向かった‐";
		close2;
		warp "prt_pri00.gat",51,123;
		end;
	case 4:
		mes "[サイマン]";
		mes "監獄の方で何か情報は、";
		mes "つかめましたか？";
		mes "もしまだでしたら……";
		next;
		mes "[サイマン]";
		mes "^0000cd王宮の地下監獄^000000に監禁された";
		mes "^0000cdビッグフットマン^000000という人物を";
		mes "訪ねてみてください。";
		next;
		mes "[サイマン]";
		mes "それから……";
		mes "アイゼン・アルム様から他の話は";
		mes "聞いていませんか？";
		mes "もしプロンテラに行くことになったら";
		mes "アイゼン・アルム様に私の気持ちを";
		mes "必ずお伝え下さい。";
		next;
		mes "‐プロンテラ中央宮から";
		mes "　プロンテラ監獄に行けるらしい。";
		mes "　向かおうかな？‐";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐プロンテラ監獄に向かった‐";
		close2;
		warp "prt_pri00.gat",51,123;
		end;
	default:
		mes "[守護騎士]";
		mes "私がいない間に、";
		mes "もし若旦那様の身に、";
		mes "何か起きたら……";
		mes "今すぐにでもプロンテラに行こうか。";
		next;
		mes "[守護騎士]";
		mes "いや、きっと怒られる。";
		mes "もう少し待つことにしよう。";
		mes "そのうち呼んで頂けるはず……。";
		next;
		mes "[守護騎士]";
		mes "もう少しだけ……。";
		close;
	}
}

prt_pri00.gat,57,119,1	script	ビッグフットマン#ep16wal	54,{
	switch(EP16_3QUE) {
	case 4:
		mes "[ビッグフットマン]";
		mes "揚げた鳥、焼いたジャガイモ……";
		mes "新鮮なチーズ……";
		mes "はあ……こんな所に";
		mes "閉じ込められていると";
		mes "普通の食べ物が食べたくなるんだなあ。";
		next;
		mes "[ビッグフットマン]";
		mes "今、俺の口までこれらの";
		mes "食べ物を運んでくれる";
		mes "美女が居たら……";
		mes "今すぐにでも結婚するのに。";
		next;
		emotion 23;
		mes "[ビッグフットマン]";
		mes "うわ!?";
		mes "あれまた現れた!!!!";
		mes "怖い!!!!";
		mes "だけど俺がここに捕まっている間は";
		mes "安全だよな……";
		next;
		menu "ビッグフットマン？",-;
		emotion 6;
		mes "[ビッグフットマン]";
		mes "あっ！";
		mes "俺、もうそれは食べないぞ！";
		mes "こんな家畜のエサみたいな食べ物は";
		mes "食べない！";
		mes "俺は美食家ではないけど、";
		mes "味くらいわかる！";
		next;
		mes "[ビッグフットマン]";
		mes "俺に食事らしいものを";
		mes "持って来てくれ！";
		mes "いくら監獄だとしても食えそうなものを";
		mes "提供するのが当たり前じゃないか!?";
		next;
		menu "看守ではないです",-;
		mes "[ビッグフットマン]";
		mes "看守じゃないの？";
		mes "ならいいけど。";
		mes "ここの食べ物は最悪なんだ。";
		next;
		mes "[ビッグフットマン]";
		mes "だけどあんた誰？";
		mes "見た感じでは冒険者のように";
		mes "みえるけど。";
		next;
		mes "[ビッグフットマン]";
		mes "いや、そんなものは";
		mes "重要じゃないな……";
		mes "俺に聞きたい事があって来たと";
		mes "言ったな？";
		mes "世の中にタダという物はない、";
		mes "それは知っているよな？";
		next;
		emotion 4,"";
		menu "……何が望みですか？",-;
		mes "[ビッグフットマン]";
		mes "ここから出してくれ。";
		next;
		menu "それは私の権限外のことです",-;
		mes "[ビッグフットマン]";
		mes "なんだよ、つまんない奴だな。";
		mes "ここに入れるくらいなら";
		mes "ある程度地位が高い位置にある";
		mes "奴じゃないのか？";
		next;
		mes "[ビッグフットマン]";
		mes "わかった、認める。";
		mes "俺も無理な頼みだというくらいは";
		mes "分かっているしな。";
		next;
		mes "[ビッグフットマン]";
		mes "最初から期待もしていない。";
		mes "ただ言ってみただけだ。";
		next;
		mes "[ビッグフットマン]";
		mes "しかし断るのが早すぎだ。";
		mes "もう少し悩むふりくらいは";
		mes "してくれれば楽しかったのによ。";
		next;
		menu "本当に望んでいる事は何ですか？",-;
		mes "[ビッグフットマン]";
		mes "それはZenyに決まっているじゃないか。";
		mes "金額はあんたが欲しがる情報によって";
		mes "変わる。";
		next;
		mes "[ビッグフットマン]";
		mes "分割はダメ。現金のみの一括払い。";
		mes "２年以上過ぎているZenyのみ受け取る。";
		mes "いつかここから出た時に";
		mes "気持ち良く使ってやるから。";
		next;
		menu "いやです",-;
		emotion 32;
		mes "[ビッグフットマン]";
		mes "ああ、もう！　冗談だよ!";
		mes "冗談も区別できないんだな。";
		next;
		mes "[ビッグフットマン]";
		mes "それに若いくせに";
		mes "諦めるのがあまりにも早い。";
		next;
		mes "[ビッグフットマン]";
		mes "待った!!　あんたを見ていたら";
		mes "何か頼みたいことが浮かんだ！";
		next;
		mes "[ビッグフットマン]";
		mes "そう!!";
		mes "辛口焼餃子とグリーンサラダ!!";
		mes "それだ！";
		mes "それを持って来てくれ。";
		next;
		mes "[ビッグフットマン]";
		mes "ここの食べ物はあまりにもひどくて";
		mes "美味しく食べられないんだ。";
		mes "それでいつも食べ物のことばかり";
		mes "考えている。";
		next;
		mes "[ビッグフットマン]";
		mes "今一番食べたいものがそれなんだ。";
		mes "そのくらいは叶えられるよな？";
		mes "^0000cd辛口焼餃子1個と";
		mes "グリーンサラダ1皿！^000000";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "それくらいは出来ます。";
		mes "すこし待って下さい。 ";
		next;
		emotion 18;
		mes "[ビッグフットマン]";
		mes "待てと言わなくても";
		mes "どこにも行けないから安心しろ。";
		delquest 14471;
		setquest 14472;
		set EP16_3QUE,5;
		close;
	case 5:
		if(countitem(12055) < 1 || countitem(12065) < 1) {
			mes "[ビッグフットマン]";
			mes "待った!!　ちょっと待ってよ。";
			mes "餃子の油の匂いと";
			mes "サラダの新鮮な臭いがしないぞ？";
			next;
			mes "[ビッグフットマン]";
			mes "本当に食べ物を持って";
			mes "来たのか？";
			mes "^0000cd辛口焼餃子1個と";
			mes "グリーンサラダ1皿！^000000";
			next;
			mes "[ビッグフットマン]";
			mes "それを持って来るまでは俺は";
			mes "何も言わないぞ！";
			mes "頼んだのをちゃんと";
			mes "持って来ているか確認して";
			mes "再度持って来てくれ！";
			close;
		}
		mes "[ビッグフットマン]";
		mes "匂いがする。この匂いだ。";
		mes "持って来たものを出してみろ。";
		next;
		menu "ここにあります",-;
		mes "[ビッグフットマン]";
		mes "お……これこれ！";
		mes "少しずつ味わって食べるぜ。";
		mes "それで、聞きたい事を言ってみろ。";
		next;
		menu "他国でバルター家の人間を見た件",-;
		mes "[ビッグフットマン]";
		mes "ああ、それが気になっていたのか。";
		mes "あんたも知っての通り";
		mes "交易を行うバルター家は";
		mes "アルベルタとプロンテラを除外した";
		mes "ルーンミッドガッツでは";
		mes "見かける事が難しいだろ。";
		next;
		mes "[ビッグフットマン]";
		mes "広く知られている奴以外には、";
		mes "身元をうまく隠したりもしているし。";
		next;
		mes "[ビッグフットマン]";
		mes "しかし、あの家門の紋章が";
		mes "あまりにも変わっていてな。";
		mes "で……それを見たんだ。";
		mes "^0000cdベインス^000000で。";
		next;
		menu "バルター家の誰を見たのですか？",-;
		mes "[ビッグフットマン]";
		mes "誰なのか俺も知らない。";
		mes "俺はいつもと同じく";
		mes "仕事をしていたんだ。";
		mes "知っているよな？";
		mes "人が食べて行くには仕事を";
		mes "しないといけないだろ？";
		next;
		menu "スリですね！",-;
		emotion 6;
		mes "[ビッグフットマン]";
		mes "人聞きが悪い言い方はやめろ。";
		mes "俺の話が聞きたくないのか？";
		mes "とはいえ俺は義理を大事にする。";
		mes "餃子とサラダを持ってきてくれた";
		mes "約束分は守るぜ。";
		next;
		mes "[ビッグフットマン]";
		mes "とにかくえらく古びた格好をした男が";
		mes "無防備状態で市場に立っていたから";
		mes "近づいて仕事をしたよ。";
		mes "それで素早くその場を離れたんだ。";
		next;
		mes "[ビッグフットマン]";
		mes "市場の隅っこで確認してみたんだけど、";
		mes "とてつもない金額の金が";
		mes "入っていたんだ。";
		mes "そして ^0000cd古い手紙が一枚";
		mes "^000000一緒にあったんだ。";
		mes "^0000cd印章^000000が押されている手紙が。";
		next;
		menu "手紙だけでバルター家だと思ったのですか？",-;
		mes "[ビッグフットマン]";
		mes "まあ、急ぐな。";
		mes "だからその話を今からしようと";
		mes "したんじゃないか。";
		next;
		mes "[ビッグフットマン]";
		mes "その袋に入っていた金額を確認して、";
		mes "俺はその日の仕事を終えようと";
		mes "していたんだ。";
		mes "そのくらい、収穫が良かったからな。";
		next;
		mes "[ビッグフットマン]";
		mes "だけどすぐに、";
		mes "あの古びた格好をしていた奴が";
		mes "現れたんだよ。";
		next;
		mes "[ビッグフットマン]";
		mes "その後は言わなくてもわかるよな？";
		mes "3人くらいの男と戦ってるのかと";
		mes "思ったくらいに凄かった。";
		mes "あの凄い拳！";
		mes "ふう……あれを振り回す時！";
		mes "その時……俺は見たんだよ、あれを。";
		next;
		mes "[ビッグフットマン]";
		mes "大事に隠しておいた^0000cd刀^000000を。";
		mes "そしてその^0000cd刀にあった紋章^000000を。";
		mes "これで分かったか？　どうよ？";
		mes "このくらいなら信じるだろ？";
		next;
		menu "本当に見えたのですか？",-;
		emotion 6;
		mes "[ビッグフットマン]";
		mes "あ、疑い深いね。";
		mes "俺の職業が何か忘れた？";
		next;
		menu "スリです！",-;
		emotion 7;
		mes "[ビッグフットマン]";
		mes "あ、また言いやがった!!";
		mes "だからー！　直接的に言うな!?";
		next;
		mes "[ビッグフットマン]";
		mes "とにかく、俺の職業的に";
		mes "何でも瞬間的にキャッチする";
		mes "目が必要なの。";
		next;
		mes "[ビッグフットマン]";
		mes "人をパッと見た瞬間に、財布の位置と";
		mes "相手が持っている武器と様子、そして";
		mes "足の速さくらいを";
		mes "全部把握しなければならない";
		mes "高難易度技術を必要とする専門職なんだぜ。";
		next;
		mes "[ビッグフットマン]";
		mes "俺は信じられなくても";
		mes "俺の職業的な能力は信じろよ。";
		emotion 23,"";
		next;
		menu "信じてみます",-;
		mes "[ビッグフットマン]";
		mes "もっと必要な情報はない？";
		mes "今回はデザートが食べたくなった。";
		next;
		menu "食べすぎはよくないですよ！",-;
		mes "[ビッグフットマン]";
		mes "あ、デザート!!";
		mes "俺のデザートがあああ……";
		delitem 12055,1;
		delitem 12065,1;
		delquest 14472;
		setquest 14473;
		set EP16_3QUE,6;
		next;
		mes "‐ベインスに向かおうかな？‐";
		next;
		if(select("向かわない","向かう")==1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐ベインスに向かった‐";
		close2;
		warp "veins.gat",160,164;
		end;
	case 6:
		mes "[ビッグフットマン]";
		mes "何だ？　気が変わったのか？";
		mes "もっと得たい情報でもあるのか？";
		mes "なら、マステラ酒がちょっと";
		mes "飲みたいけど……";
		next;
		mes "[ビッグフットマン]";
		mes "もしやどこに行けば";
		mes "いいのか忘れたのか？";
		mes "^0000cdベインス^000000に行けと";
		mes "言っただろ。";
		next;
		mes "[ビッグフットマン]";
		mes "次にまた会う時は";
		mes "デザート持って来て！";
		next;
		mes "‐ベインスに向かおうかな？‐";
		next;
		if(select("向かわない","向かう")==1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐ベインスに向かった‐";
		close2;
		warp "veins.gat",160,164;
		end;
	default:
		mes "[ビッグフットマン]";
		mes "揚げた鳥、焼いたジャガイモ……";
		mes "新鮮なチーズ……";
		mes "はあ……こんな所に";
		mes "閉じ込められていると";
		mes "普通の食べ物が食べたくなるんだなあ。";
		next;
		mes "[ビッグフットマン]";
		mes "今、俺の口までこれらの";
		mes "食べ物を運んでくれる";
		mes "美女が居たら……";
		mes "今すぐにでも結婚するのに。";
		next;
		emotion 23;
		mes "[ビッグフットマン]";
		mes "うわ!?";
		mes "あれまた現れた!!!!";
		mes "怖い!!!!";
		mes "だけど俺がここに捕まっている間は";
		mes "安全だよな……";
		close;
	}
}

veins.gat,156,160,7	script	K#ep16wal	934,{
	switch(EP16_3QUE) {
	case 6:
		emotion 7;
		mes "[K]";
		mes "あんた、誰だ？";
		mes "さっきからなぜオレを見ているんだ？";
		mes "オレの財布を狙っているのか？";
		mes "それは残念だ。";
		mes "オレの財布を狙っていた奴を";
		mes "この前監獄に送ったばかりだぜ？";
		next;
		mes "[K]";
		mes "すり仲間からそんな情報は";
		mes "共有されないみたいだな？";
		mes "監獄に行きたくないなら";
		mes "速やかにここから消えろ。";
		next;
		menu "はじめまして、ケイン・バルター・ウォーカー",-;
		mes "[K]";
		mes "……知らない名前だ。";
		next;
		menu "主君を見捨てた裏切り者",-;
		mes "[K]";
		mes "お前……誰だ？";
		mes "どうしてオレの所に来て";
		mes "そんな話をする!!";
		next;
		menu "真実を知りたいのです",-;
		mes "[K]";
		mes "真実？";
		mes "何だ！";
		mes "何を知ろうとしているッ!?";
		next;
		menu "知っているのはあなたの方だ",-;
		mes "[K]";
		mes "……言ってみろ。";
		mes "お前は誰だ？";
		mes "アイゼン・アルム様の死に関して";
		mes "何か知っているのか？";
		next;
		mes "[K]";
		mes "答えによってはお前の命が";
		mes "かかっている……";
		mes "まずはオレの正体を知っている";
		mes "事自体が除去の理由だ。";
		next;
		mes "[K]";
		mes "さ、言ってみろ。";
		mes "お前は誰だ？";
		mes "どうやってオレを訪ねて来た？";
		mes "そしてアイゼン・アルム様の死に対して";
		mes "何を知っている？";
		next;
		menu "アイゼン・アノからの依頼で調べている",-;
		mes "[K]";
		mes "おお、なんということだ……";
		mes "アイゼン・アノ様……？";
		mes "あの方がついに？";
		mes "どれほど待ちわびたことか…";
		next;
		mes "[K]";
		mes "た、大変失礼しました！";
		mes "申し訳ありません！";
		mes "どうか私の無礼をお許しください!!";
		next;
		mes "[K]";
		mes "私はもうバルターという名前を";
		mes "使う事が出来ません……";
		mes "星が消えたなら、その星の衛星も";
		mes "名前も失わなければなりません。";
		mes "それに私はその星も守る事が";
		mes "出来なかった罪人です。";
		next;
		mes "[K]";
		mes "アイゼン・アノ様がアイゼン・アルム様の";
		mes "死に対して本格的に調査を";
		mes "始めたのですか？";
		mes "それなら私もあの方の側で";
		mes "全力を尽くし、協力します。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "そうではありません。";
		mes "アイゼン・アノ様も兄様の死に";
		mes "疑問を抱いていて、きちんと";
		mes "調べてみたいそうなのですが、";
		mes "いろいろと問題があり";
		mes "中々進んでいません。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "そのような理由があって";
		mes "比較的な動き回る事ができる私が";
		mes "代わりに調べるために動いています。";
		next;
		mes "[K]";
		mes "そうですか……";
		mes "それなら私はどのように";
		mes "協力すればよいでしょう？";
		mes "真実を明かすためなら";
		mes "何でも協力します。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ただアイゼン・アルム様との間にあったことさえ";
		mes "話して頂ければ大丈夫です。";
		mes "アイゼン・アルム様が";
		mes "亡くなる前に消えた理由と、";
		mes "どうしてここにいるのか、などです。";
		next;
		mes "[K]";
		mes "私も実はあの方が死んだ際、";
		mes "何が起きたのか、何も知りません。";
		mes "というのも、あの事件が起きる前、";
		mes "私は^0000cd任務を与えられてここに";
		mes "来ることになりました。^000000";
		next;
		mes "[K]";
		mes "そして任務を終えて戻ろうとした時、";
		mes "大量のZenyと一緒に^0000cd手紙が一枚";
		mes "^000000送られてきました。";
		mes "^0000cd絶対ルーンミッドガッツに";
		mes "戻って来ないように^000000という";
		mes "内容でした。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "それからは？";
		next;
		mes "[K]";
		mes "その後すぐに風の噂であの方が";
		mes "亡くなったことを知りました。";
		mes "急いでルーンミッドガッツに";
		mes "戻りたかったのですが、";
		next;
		mes "[K]";
		mes "手紙には ^0000cd決して何があっても";
		mes "戻って来るな^000000という指示が";
		mes "あったのでそうする事も";
		mes "できませんでした……。";
		next;
		mes "[K]";
		mes "しばらくしてある噂を聞きました。";
		mes "アイゼン・アルム様の乱暴な";
		mes "行動とそれに伴う死について、です。";
		next;
		mes "[K]";
		mes "無論……";
		mes "主君を裏切った守護騎士の話も……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "なるほど……アイゼン・アルム様は";
		mes "あなたが巻き込まれないように";
		mes "保護しようとしたんですね。";
		mes "身辺に問題があれば一番";
		mes "困るのはあなたなので。";
		next;
		mes "[K]";
		mes "なるほど……";
		mes "そのような意図があったのでしょうか。";
		mes "私はそこまでは考えられなくて……";
		mes "それでは、調査のために";
		mes "私がアイゼン・アルム様から頂いた";
		mes "^0000cd手紙と剣^000000を差し上げます。";
		next;
		mes "[K]";
		mes "アイゼン・アノ様にお渡しください。";
		mes "どうかこれらがあの方の名誉を";
		mes "回復するのに力になれば……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "剣は持っていて下さい。";
		mes "騎士にとって剣は命と一緒ですから。";
		mes "アイゼン・アルム様もそれを";
		mes "望んでいると思います。";
		next;
		if(checkitemblank() == 0) {
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		mes "[K]";
		mes "わかりました。";
		mes "それでは気を付けてお戻り下さい。";
		delquest 14473;
		setquest 14474;
		getitem 6929,1;
		set EP16_3QUE,7;
		next;
		mes "‐アイゼン・アノのいる場所に";
		mes "　向かおうかな？‐";
		next;
		if(select("向かわない","向かう")==1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐アイゼン・アノに会いに";
		mes "　向かった‐";
		close2;
		warp "prt_cas_q.gat",26,178;
		end;
	case 7:
		mes "[K]";
		mes "アイゼン・アノ様に手紙と";
		mes "例の話は伝えてくれましたか？";
		next;
		mes "[K]";
		mes "もし、わたしの力が必要なら";
		mes "いつでもこの身を捧げると";
		mes "伝えて下さい。";
		next;
		mes "‐アイゼン・アノのいる場所に";
		mes "　向かおうかな？‐";
		next;
		if(select("向かわない","向かう")==1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐アイゼン・アノに会いに";
		mes "　向かった‐";
		close2;
		warp "prt_cas_q.gat",26,178;
		end;
	default:
		mes "[K]";
		mes "戻りたい。";
		mes "またあの場所に……";
		close;
	}
}

prt_cas_q.gat,82,21,1	script	ルヴィエル・ウィグナー#ep16wig	10132,{
	if(EP16_1QUE < 2) {
		end;
	}
	switch(EP16_4QUE) {
	case 0:
		mes "[ルヴィエル]";
		mes "ようこそ、冒険者様。";
		mes "私はウィグナー家の";
		mes "^0000cdルヴィエル・ウィグナー^000000と申します。";
		next;
		menu "ご挨拶に伺いました",-;
		mes "[ルヴィエル]";
		mes "おお、これはこれは。";
		mes "ご挨拶いただけるとは光栄です。";
		next;
		mes "[ルヴィエル]";
		mes "今回の宴は祝いの意味もありますが";
		mes "王位継承の話も進行するようで。";
		mes "いや、ははは。";
		mes "冒険者様はすでにご存じでしょうな。";
		next;
		mes "[ルヴィエル]";
		mes "私の家門でも";
		mes "王位継承権を持つ候補がおりますので";
		mes "ぜひ、お会いになってください。";
		next;
		mes "[ルヴィエル]";
		mes "そしてこちらは我が妻";
		mes "^0000cdカタリナ・ウィグナー^000000です。";
		next;
		mes "[カタリナ]";
		mes "ごきげんよう。";
		mes "ウィグナー家にようこそ。";
		next;
		mes "[カタリナ]";
		mes "冒険者様の便宜を図るよう";
		mes "私たちは最大の支援をいたしますわ。";
		mes "どうぞごゆるりと";
		mes "旅の疲れを癒してくださいまし。";
		next;
		mes "[カタリナ]";
		mes "もしお時間が許されるなら";
		mes "今度はウィグナーの本家にも";
		mes "ご訪問くださいませ。";
		mes "いつでも冒険者様を歓迎しますわ。";
		next;
		mes "[カタリナ]";
		mes "……ところで、あなた？";
		mes "^0000cdユルゲン^000000はどこに行ったのかしら。";
		next;
		cloakoffnpc "ユルゲン・ウィグナー#ep16wig00";
		cloakonnpc "ユルゲン・ウィグナー#ep16wig";
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "お呼びですか？";
		next;
		cutin "16jur_nor.bmp",255;
		mes "[ルヴィエル]";
		mes "ユルゲン。ちょうどよいところに。";
		mes "冒険者様、";
		mes "我が^0000cdウィグナー家の後継者^000000にして";
		mes "^0000cd王位継承候補^000000のユルゲンです。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "紹介にあずかりました";
		mes "^0000cdユルゲン・ウィグナー^000000と申します。";
		mes "お会いできて光栄です。";
		next;
		mes "[ユルゲン]";
		mes "冒険者様、どうぞおくつろぎください。";
		mes "必要なものがあれば";
		mes "いつでもおっしゃってくださいね。";
		next;
		menu "ありがとうございます",-;
		mes "[ユルゲン]";
		mes "それでは私は失礼します。";
		next;
		cloakonnpc "ユルゲン・ウィグナー#ep16wig00";
		cloakoffnpc "ユルゲン・ウィグナー#ep16wig";
		cutin "16jur_nor.bmp",255;
		mes "[ルヴィエル]";
		mes "なんだ。もう行ってしまうのか。";
		next;
		mes "[ルヴィエル]";
		mes "……ふぅ、";
		mes "まったく社交性が無きに等しい。";
		mes "これから後継者として";
		mes "人に接することも多くなるだろうに。";
		mes "どうか息子の無礼をお許しください。";
		next;
		mes "[ルヴィエル]";
		mes "もしよろしければ";
		mes "ウィグナー家の他の子供たちにも";
		mes "お会いになってください。";
		mes "モロクを打ち倒した英雄が";
		mes "祝宴に参加すると聞いて";
		mes "みな楽しみにしております。";
		next;
		mes "[ルヴィエル]";
		mes "では、どうぞごゆっくりと";
		mes "おくつろぎください。";
		next;
		delquest 73054;
		//setquest 14475;
		//compquest 14475;
		setquest 73075;
		set EP16_4QUE,1;
		if((checkquest(7683)&0x8) && !checkquest(73051) && !checkquest(73053) && !checkquest(73052) && !checkquest(73054) && !checkquest(73055) && !checkquest(73056)) {
			mes "‐^0000cd七王家すべてに挨拶をした。^000000";
			mes "　ベルのところに戻ろう‐";
		} else {
			mes "‐^0000cdウィグナー家との挨拶を済ました。^000000";
			mes "　他の王家にも挨拶に行こう‐";
		}
		next;
		mes "‐その時、ユルゲンが";
		mes "　話しかけてきた‐";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "挨拶回り中、失礼します。";
		mes "もし時間があれば";
		mes "もう少しお話しません？";
		mes "よければ私に話しかけてくださいね。";
		close2;
		cutin "16jur_nor.bmp",255;
		end;
	case 1:
		mes "[ルヴィエル]";
		mes "冒険者様、ウィグナー家にようこそ。";
		next;
		mes "[ルヴィエル]";
		mes "もしよろしければ";
		mes "ウィグナー家の子供たちにも";
		mes "お会いになってください。";
		mes "冒険者様のお話を聞ければ";
		mes "さぞ喜ぶでしょう。";
		close;
	case 2:
		mes "[ルヴィエル]";
		mes "子供たちには";
		mes "お会いになりましたか？";
		mes "もしよろしければ";
		mes "ティータイムでもいかがですか？";
		next;
		mes "[ルヴィエル]";
		mes "私たち夫婦は";
		mes "冒険者様の話を聞ける事が";
		mes "とても嬉しいのです。";
		mes "経験談はお金で買えるものでは";
		mes "ありませんから。";
		next;
		mes "[カタリナ]";
		mes "そうそう。";
		mes "子供達に失礼はありませんでしたか？";
		mes "わがままを許してしまってきたので";
		mes "とても心配です。";
		next;
		mes "[カタリナ]";
		mes "最近は注意するようにしているのですが";
		mes "もし冒険者様に失礼な事を";
		mes "行なったようであれば";
		mes "代わりにお詫びいたします。";
		next;
		menu "大丈夫です",-;
		mes "[カタリナ]";
		mes "そうですか？";
		mes "それなら良いのですけれど……";
		mes "私たちが子供達のわがままを";
		mes "許しすぎた気がします。";
		next;
		mes "[カタリナ]";
		mes "前回の王位継承会議では";
		mes "準備も無く参加して";
		mes "恥を晒しましたし……";
		next;
		mes "[ルヴィエル]";
		mes "王位に就く事自体は";
		mes "それほど重要ではないよ。";
		mes "資質のあるものは";
		mes "なるべくして王になる。";
		mes "そんな事でユルゲンに";
		mes "ストレスを与えたくはない。";
		next;
		mes "[カタリナ]";
		mes "あなたは欲がなさすぎます。";
		mes "ウィグナー家から";
		mes "王が輩出されるとしたら";
		mes "どんなに光栄でしょう。";
		mes "七王家の中でも一際、";
		mes "格があがるというものですよ。";
		next;
		mes "[ルヴィエル]";
		mes "はんっ！";
		mes "そんなものただ面倒なだけだ。";
		mes "それに忘れたのか？";
		mes "いつか話した事があっただろう。";
		next;
		mes "[ルヴィエル]";
		mes "たとえ王になったところで";
		mes "利益を得ようと集まる";
		mes "ハエが増えるだけだ。";
		next;
		mes "[ルヴィエル]";
		mes "それに、王になるために";
		mes "どれだけの財産が必要か。";
		mes "以前、ウィグナー家が";
		mes "傾きかけた事もある。";
		next;
		mes "[カタリナ]";
		mes "あら。";
		mes "その反対になる可能性も";
		mes "あるじゃないですか。";
		mes "ウィグナー家の立場が";
		mes "確固たるものになるのでは？";
		next;
		mes "[カタリナ]";
		mes "今はユルゲンを支える";
		mes "カトリンとアイザックもいます。";
		next;
		mes "[ルヴィエル]";
		mes "ふふっ……アイザックか。";
		mes "そうだな。";
		mes "いや、我が子ながら頼もしい限りだ。";
		next;
		menu "アイザック様を信頼しているんですね",-;
		mes "[ルヴィエル]";
		mes "ああ、冒険者様、申し訳ありません。";
		mes "話がそれました。";
		next;
		menu "いいえ、お構いなく",-;
		mes "[ルヴィエル]";
		mes "話が出たついでですが、";
		mes "アイザックはどうでしたか。";
		mes "我が子達の中で";
		mes "もっともウィグナー家らしい子です。";
		next;
		mes "[ルヴィエル]";
		mes "ユルゲンはルックスに興味がありすぎて";
		mes "王位や財産に関心が無くて……";
		mes "もしもカトリンが男に生まれていたら";
		mes "全てを引き継がせても";
		mes "安心だったのですが……";
		next;
		mes "[ルヴィエル]";
		mes "そんな折、わがままだったアイザックが";
		mes "ウィグナー家に相応しい人物として";
		mes "育ってくれたので一安心しました。";
		next;
		mes "[ルヴィエル]";
		mes "ああ、もちろん他の子供達が";
		mes "相応しくないわけでは無いですよ。";
		next;
		menu "意味はわかります",-;
		mes "[カタリナ]";
		mes "子供達の前ではこの話は";
		mes "しないでくださいね。";
		mes "露骨に比較されるのは";
		mes "気持ちの良いものでは";
		mes "ないでしょうから……";
		next;
		mes "[ルヴィエル]";
		mes "何を言うか。";
		mes "ウィグナー家の人間であれば";
		mes "嫌な言葉も聞かなければならない。";
		mes "言葉を判断するのは自分自身だ。";
		mes "嫌な話を聞く事で";
		mes "学べる事もある。";
		next;
		mes "[カタリナ]";
		mes "いいえ、それでも子供達の前で";
		mes "そんな事は言わないでください。";
		next;
		mes "[ルヴィエル]";
		mes "私が子供達の前で";
		mes "そんな事を言った事があるか？";
		next;
		mes "[カタリナ]";
		mes "それは……";
		next;
		mes "[カタリナ]";
		mes "ところで最近、";
		mes "アイザックがどこかで何かを";
		mes "しているようなんですけど";
		mes "ご存知ですか？";
		next;
		mes "[ルヴィエル]";
		mes "レベンブルグ家の次男と";
		mes "事業を起こしているらしいな。";
		mes "まぁ、アイザックなら";
		mes "大丈夫であろう。";
		next;
		mes "[カトリン]";
		mes "キャーー!!";
		next;
		emotion 23,"ルヴィエル・ウィグナー#ep16wig";
		mes "[ルヴィエル]";
		mes "^0000cdカトリン?!^000000";
		next;
		emotion 23,"カタリナ・ウィグナー#ep16wig";
		mes "[カタリナ]";
		mes "^0000cdカトリン!!^000000";
		mes "いったい何があったのでしょう！";
		next;
		menu "お二人はここに！　状況を見てきます",-;
		mes "‐カトリンに何があったのだろうか!?";
		mes "　様子を見にいってみよう‐";
		cloakonnpc "アイザック・ウィグナー#ep16wig";
		chgquest 14476,14477;
		set EP16_4QUE,3;
		close;
	case 3:
		mes "[ルヴィエル]";
		mes "カトリンは大丈夫だろうか？";
		mes "やはり行ってみるべきか。";
		next;
		mes "‐カトリンに何があったのだろうか!?";
		mes "　様子を見にいってみよう‐";
		close;
	case 4:
		mes "[ルヴィエル]";
		mes "ああ、冒険者様。子供達に";
		mes "何が起きているのか";
		mes "聞いてみたのですが、";
		mes "教えてもらえませんでした。";
		next;
		mes "[カタリナ]";
		mes "何かご存知ないでしょうか……？";
		next;
		menu "今は言えませんが、安心してください",-;
		mes "[カタリナ]";
		mes "そうですか。";
		mes "子供達が黙っていろと……";
		mes "冒険者様は";
		mes "事情を知っているようですね。";
		mes "子供たちの事、";
		mes "何卒よろしくお願いします。";
		close;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "[ルヴィエル]";
		mes "子供達の事、";
		mes "どうかよろしくお願いします。";
		close;
	default:
		mes "[ルヴィエル]";
		mes "冒険者様、";
		mes "子供達に大体の話は聞きました。";
		mes "理由までは聞けませんでしたが";
		mes "冒険者様には助けられたとも";
		mes "申しておりました。";
		next;
		mes "[カタリナ]";
		mes "どうも以前より";
		mes "仲が良くなったようです。";
		mes "もちろん今までも良かったですが、";
		mes "もっと良くなりました。";
		mes "微笑ましいことです。";
		next;
		mes "[ルヴィエル]";
		mes "冒険者様は";
		mes "我々に幸運をもたらす方のようです。";
		mes "これからもウィグナー家と";
		mes "末永くお付き合いくださいませ。";
		next;
		mes "[カタリナ]";
		mes "祝宴が終わったらぜひ";
		mes "ウィグナー家にお越しください。";
		mes "冒険者様の訪問を";
		mes "お待ちしております。";
		close;
	}
}

prt_cas_q.gat,82,23,0	script	カタリナ・ウィグナー#ep16wig	71,{
	switch(EP16_4QUE) {
	case 0:
		mes "[カタリナ]";
		mes "ようこそ、冒険者様。";
		mes "歓迎いたします。";
		next;
		mes "[カタリナ]";
		mes "必要なものがあれば";
		mes "いつでもおっしゃってください。";
		mes "ウィグナー家の者として";
		mes "最善を尽くさせていただきます。";
		next;
		mes "[カタリナ]";
		mes "家門に関する話は";
		mes "ウィグナー家の主である";
		mes "ルヴィエル・ウィグナーと";
		mes "お話なさってください。";
		close;
	case 1:
	case 2:
		mes "[カタリナ]";
		mes "子供達にはお会いいただけましたか？";
		mes "冒険者様との会話は";
		mes "貴重な経験になるでしょう。";
		mes "事実、大きな困難に";
		mes "ぶつかったことがない";
		mes "子供たちなので経験が足りません。";
		next;
		mes "[カタリナ]";
		mes "建国英雄の家門に嫁いで以来、";
		mes "家柄にふさわしい子供たちに";
		mes "育て上げるつもりでしたが……";
		next;
		mes "[カタリナ]";
		mes "夫が名誉や権力に欲が無い人でして。";
		mes "私としては少し心残りです。";
		next;
		mes "[カタリナ]";
		mes "ただ、子供たちが望むものは";
		mes "できる限り叶えたいと思っています。";
		mes "そのせいで少し礼に欠ける所があって";
		mes "心配になることも多いのですが……";
		next;
		mes "[カタリナ]";
		mes "ですので、ぜひ冒険者様の";
		mes "話を聞きたいです。";
		mes "多くの経験を積んだ方の";
		mes "話を聞くのが大きな楽しみです。";
		close;
	case 3:
		mes "[カタリナ]";
		mes "カトリンに何があったのでしょうか!?";
		mes "こうしてはおれません。";
		mes "やはり行ってみるべきかしら。";
		next;
		menu "ここで待っていてください",-;
		mes "[カタリナ]";
		mes "ああ……";
		mes "何事もなければ良いのですが。";
		close;
	case 4:
		mes "[ルヴィエル]";
		mes "ああ、冒険者様。";
		mes "子供達に何が起きているのか";
		mes "聞いてみたのですが、";
		mes "教えて貰えませんでした。";
		next;
		mes "[カタリナ]";
		mes "何かご存知ないでしょうか……？";
		next;
		menu "今は言えませんが、安心してください",-;
		mes "[カタリナ]";
		mes "そうですか。";
		mes "子供達が黙っていろと……";
		mes "冒険者様は";
		mes "事情を知っているようですね。";
		mes "子供達の事、";
		mes "何卒よろしくお願いします。";
		close;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "[カタリナ]";
		mes "子供達の事、";
		mes "何卒よろしくお願いします。";
		close;
	default:
		mes "[カタリナ]";
		mes "子供達の仲が以前よりも";
		mes "よくなったように見えます。";
		mes "冒険者様のおかげです。";
		next;
		mes "[カタリナ]";
		mes "冒険者様は我々に";
		mes "幸運をもたらす方のようです。";
		mes "これからもウィグナー家と";
		mes "末永くお付き合いくださいませ。";
		close;
	}
}

prt_cas_q.gat,80,23,5	script(CLOAKED)	ユルゲン・ウィグナー#ep16wig00	989,{}

prt_cas_q.gat,95,9,5	script	ユルゲン・ウィグナー#ep16wig	989,{
	switch(EP16_4QUE) {
	case 0:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "私に会いに来る";
		mes "約束はありましたか？";
		mes "それでは外でお待ちください。";
		mes "先に来た方から順番に";
		mes "会う事になっておりますので。";
		mes "私は誰にでも公平なのですよ。";
		next;
		mes "[ユルゲン]";
		mes "もし私の両親に";
		mes "お会いになる約束でしたら";
		mes "あちらにおります。";
		mes "ところで扉の外には待っている人が";
		mes "どれほどいる事でしょう。";
		next;
		mes "[ユルゲン]";
		mes "今日も美しさで世界の平和を守ります。";
		mes "ああ、美しさは正義！";
		close2;
		cutin "16jur_nor.bmp",255;
		end;
	case 1:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様、よかった。";
		mes "時間があるようですね。";
		mes "先ほどは失礼しました。";
		next;
		mes "[ユルゲン]";
		mes "個人的にはもう少し";
		mes "お話をしたかったのですが";
		mes "母様は少しでも作法を間違えると";
		mes "すぐに怒るのでちょっと……";
		next;
		mes "[ユルゲン]";
		mes "まあ、人前で怒鳴るとは思えませんが、";
		mes "それでも面倒事は避けたかったので。";
		mes "本当に失礼しました。";
		next;
		mes "[ユルゲン]";
		mes "冒険者様、話は変わりますが";
		mes "私の家族を紹介いたします。";
		mes "こちらの優雅なレディーは";
		mes "私の姉、^0000cdカトリン・ウィグナー^000000です。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "こういう時は姉、ではなく";
		mes "ウィグナー家の長女と紹介する方が";
		mes "礼儀にかなうのよ。";
		next;
		mes "[カトリン]";
		mes "冒険者様、お初にお目にかかります。";
		mes "ウィグナー家へようこそ。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "そしてこちらは私の弟、";
		mes "^0000cdアイザック・ウィグナー^000000です。";
		next;
		mes "[ユルゲン]";
		mes "ウィグナー家の次男です。";
		mes "家業に関心がない私や姉と違い";
		mes "頭も手際も良いので";
		mes "いずれはウィグナー家を";
		mes "発展させる人物になるでしょう。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "これはどうも。";
		mes "アイザック・ウィグナーと申します。";
		mes "このつまらない家門にまで";
		mes "ご足労いただき光栄です。";
		mes "どうかお楽しみくださいますよう。";
		next;
		cutin "16kat_ang.bmp",2;
		mes "[カトリン]";
		mes "アイザック！";
		mes "そのような言葉遣いは";
		mes "控えるように注意したはずよ。";
		mes "あなたを紹介したユルゲンにも失礼よ。";
		mes "ウィグナー家の名に泥を塗るつもり？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "冗談ですよ、";
		mes "ジョ・ウ・ダ・ン。";
		mes "姉さんは本当に堅苦しいな。";
		mes "冒険者様にも癒しが必要でしょう？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "お客様に失礼になる言葉は";
		mes "冗談ではないのよ。";
		mes "それは侮辱と言うの。";
		mes "冒険者様、弟の無礼、";
		mes "どうかをお許しください。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "どうでもいいけど……";
		mes "私は家に帰りたいね。";
		mes "ここは狭いし窮屈だ。";
		mes "せめて祝宴場にでも出向きたい。";
		next;
		mes "[ユルゲン]";
		mes "ああ、私に会いたがっている人が";
		mes "どんなに多いことか！";
		mes "私はこの美しい顔を";
		mes "みなに披露する義務があるんだ！";
		next;
		mes "[ユルゲン]";
		mes "この堅苦しくも暗い王宮に";
		mes "一筋の光をもたらすようにね！";
		mes "人々に楽しみを与える必要があるんだ。";
		next;
		cutin "16kat_ang.bmp",2;
		mes "[カトリン]";
		mes "それは王位継承に対する侮辱よ。";
		mes "最善を尽くして臨みなさい。";
		mes "あなたが思っているほど";
		mes "軽々しいものではありません。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "あなたは七大建国王家とともに";
		mes "王国を導く王位継承者の一人である";
		mes "自覚を忘れてはならないの。";
		next;
		mes "[カトリン]";
		mes "もう子供ではいられないの。";
		mes "その責任と義務の重さを";
		mes "軽んじないよう教えたはずよ。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "もちろん！";
		mes "よく解っているさ。";
		mes "だから今日も鏡の前で服装を正し、";
		mes "ヘアスタイルも完璧にしたのさ。";
		mes "私の心の中の緊張の糸が";
		mes "切れないようにね。";
		next;
		mes "[ユルゲン]";
		mes "自分を完璧にすることで";
		mes "大局を見る目も";
		mes "養われるんじゃないかな。";
		mes "そして私は完璧に準備ができている。";
		next;
		mes "[ユルゲン]";
		mes "ほら、今日の新しいマントは";
		mes "私の瞳の色によく似合う。";
		mes "きっと王宮の雰囲気も";
		mes "明るくしてくれるさ。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "……またはじまった。";
		mes "そろそろお暇させてもらうよ。";
		mes "冒険者様、それではまた。";
		next;
		cloakonnpc "アイザック・ウィグナー#ep16wig";
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "……冒険者様、";
		mes "もしよろしければ";
		mes "^0000cd私たちの両親とティータイム^000000でも";
		mes "いかがですか？";
		next;
		mes "[カトリン]";
		mes "お二人とも冒険者様の話を聞くのを";
		mes "とても楽しみにされておりました。";
		chgquest 73075,14476;
		set EP16_4QUE,2;
		close2;
		cutin "16kat_nor.bmp",255;
		end;
	case 2:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "^0000cd父と母^000000はあちらにおります。";
		mes "冒険者様のお話を心待ちにしています。";
		mes "ところで扉の外に私を待っている人は";
		mes "どれくらいいますか？";
		next;
		mes "[ユルゲン]";
		mes "ああ、順番に会うので";
		mes "待たせてしまっています。";
		mes "美しさで世界の平和を守るのは";
		mes "辛いですね。";
		close2;
		cutin "16jur_nor.bmp",255;
		end;
	case 3:
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お姉さんがなにかをなくしたようですが、";
		mes "ひどく慌てていて、";
		mes "詳しいことがわからないのです。";
		mes "冒険者様になら落ち着いて";
		mes "話すのではないでしょうか。";
		close2;
		cutin "16jur_sim.bmp",255;
		end;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お姉さんが無くしたものが";
		mes "一体何なのかは";
		mes "わかりません。";
		next;
		mes "[ユルゲン]";
		mes "私を好きな人々に声をかけて";
		mes "探してもらえば、";
		mes "あーっ！";
		mes "という間に見つかるでしょう。";
		mes "しかし、それでは父が";
		mes "黙っていない理由があるのです。";
		next;
		mes "[ユルゲン]";
		mes "仕方ありません、";
		mes "冒険者様にお任せするのが";
		mes "最善かと思われます。";
		mes "冒険者様の手にかかってますよ！";
		close2;
		cutin "16jur_sim.bmp",255;
		end;
	case 11:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様、どうでしたか？";
		mes "何か成果は？";
		next;
		menu "今までのことを報告する",-;
		mes "[ユルゲン]";
		mes "なるほど……";
		mes "箱を持っていった人は";
		mes "確認できていませんか。";
		mes "箱はいつのまにか消えていた、";
		mes "ということになりますね。";
		next;
		menu "実はカトリンに対して偏見がある人がいる",-;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "それは一体？";
		next;
		menu "カトリンの自作自演が疑われています",-;
		mes "[ユルゲン]";
		mes "……！";
		mes "はあ、普段からコミュニケーションを";
		mes "もっととったほうがいいと";
		mes "言っていたのですが……";
		mes "怠っていたようですね。";
		next;
		cutin "16kat_nor.bmp",2;
		cloakoffnpc "カトリン・ウィグナー#ep16wig";
		mes "[カトリン]";
		mes "なぜ私を知らない人への";
		mes "評判のためにそんな事を";
		mes "する必要があるのかしら？";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "姉さん!?";
		mes "一体いつから？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "つい今ほどね。";
		mes "でもあなたが話した内容を";
		mes "聞くくらい前から。";
		mes "で、人々からの悪い評判は";
		mes "私のせいだと？";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "ある程度はあるのでは？";
		mes "ほら、私を見てよ。";
		mes "私はいつでもどんな人にでも";
		mes "最善を尽くして接しているから";
		mes "みんな私が好きなんだ。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "……人々があなたに好感を持つのが";
		mes "あなたの態度のおかげだと";
		mes "本気で思ってるの？";
		mes "呆れた……。";
		next;
		mes "[カトリン]";
		mes "本当に呆れた……。";
		next;
		mes "[カトリン]";
		mes "以前の王位継承の件で";
		mes "あなたの態度が問題になって";
		mes "家門にどれだけ迷惑をかけたのか";
		mes "もう忘れたのね。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "私のコミュニケーションに";
		mes "問題があるとでも？";
		mes "それじゃ一体どうして";
		mes "私が好かれるのさ？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "……そんな事も解らないのね。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "まさか私のルックスのおかげだと";
		mes "言いたいのかい？";
		next;
		cutin "16kat_ang.bmp",2;
		mes "[カトリン]";
		mes "そうよ。";
		mes "幼い頃から何もしなくても……";
		mes "いいえ、問題を起こしても";
		mes "周囲の人々はあなたに対して";
		mes "妙に優しかった。";
		next;
		mes "[カトリン]";
		mes "みんな笑っていた。";
		mes "みんなウィグナー家の後継者、";
		mes "次期王位候補のあなたに";
		mes "気に入られるために。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "それが外見のおかげだと？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "それはあなたも否定できないでしょ。";
		mes "外見だって才能の一部だから。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "例えルックスのおかげだとしても";
		mes "私が望んでそうなったわけでは";
		mes "ないだろう？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "美しいルックスの弟と";
		mes "黙っていても比較され、";
		mes "きな臭い噂話が立つのは";
		mes "私が望んでいるとでも？";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "だからお姉さんも";
		mes "もう少し他の人と話を……";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "人から誤解を受けない";
		mes "一番良い方法は「沈黙」なの。";
		mes "言葉にしなければ失敗もしないわ。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "必ずしもそうとは言えないよ。";
		mes "例えば今日聞いた話だけど、";
		mes "お姉さんが沈黙した結果……";
		next;
		cutin "16kat_ang.bmp",2;
		mes "[カトリン]";
		mes "私はもうベストを尽くしてるわよ!!";
		mes "知ってる？";
		mes "影は光があるから生まれるの。";
		mes "私だって頑張ってるの！";
		next;
		mes "[カトリン]";
		mes "でも結局人は上辺しか見ない！";
		mes "私は何をどうすればいいの？";
		next;
		menu "お二人とも、落ち着いてください",-;
		cloakoffnpc "アイザック・ウィグナー#ep16wig";
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "二人とも揉めすぎ！";
		mes "何が起きてるのかは";
		mes "知った事じゃないけど";
		mes "落ち着きなよ。";
		mes "二人の声が廊下の端まで";
		mes "響いてるぜ？";
		next;
		mes "[アイザック]";
		mes "このままじゃ、家のイメージが";
		mes "悪くなっちゃうよ。";
		next;
		mes "[アイザック]";
		mes "この前兄さんが地の底まで";
		mes "落としてくれた評判を";
		mes "やっと少し回復できたところなんだ。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "……";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "ところで^0000cdこの箱は姉さんの^000000だよね？";
		mes "人の出入りが多いところにあったから";
		mes "とりあえず持ってきたけど。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "これ、^0000cdお前が持っていたのか^0000cd？";
		next;
		cutin "16kat_ang.bmp",2;
		mes "[カトリン]";
		mes "持ち出したならちゃんと話しなさいよ。";
		mes "アイザック！";
		mes "あなたのせいでどんなに";
		mes "困っていたと思っているの？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "えええ……";
		mes "姉さんのためと思って";
		mes "預かっていただけなのに……";
		next;
		mes "[アイザック]";
		mes "どんなに小さな物でも";
		mes "家で物が無くなれば……";
		mes "わかるよね、";
		mes "父が何とおっしゃるか。";
		next;
		mes "[アイザック]";
		mes "「たとえ小物一つでも";
		mes "まともに管理できない者は";
		mes "ウィグナー家に必要なし。";
		mes "管理能力こそ最大の美徳である」";
		mes "でしょう。";
		next;
		emotion 3,"ユルゲン・ウィグナー#ep16wig";
		mes "[アイザック]";
		mes "うう……言っただけで";
		mes "頭が痛くなる。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "で、その中にはいったい";
		mes "何が入ってるの？";
		mes "あんな騒ぎまで起こして。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "この中に金銭的な価値を";
		mes "持つような物は無いわ。";
		mes "でも……私にとっては";
		mes "宝石よりも価値がある物よ。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "これは……";
		mes "ノート……？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "日記？";
		next;
		emotion 3,"ユルゲン・ウィグナー#ep16wig";
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "言葉は慎むほど良いの。";
		mes "こぼれた水は元に戻せないのと同じ。";
		mes "でも誰にだって";
		mes "正直になりたい瞬間はある。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "私が「私」になれる瞬間。";
		mes "それがこの日記帳だった。";
		next;
		mes "[カトリン]";
		mes "沈黙でも人々の誤解が生まれるなら";
		mes "言葉を慎むのが必ずしも";
		mes "良い事ではなかったという事ね。";
		mes "私は日記帳も見つかったし";
		mes "もう失礼するわ。";
		mes "冒険者様、それでは失礼いたします。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お姉さん、あの……";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "もういいの。";
		mes "気にしないで。";
		next;
		cloakonnpc "カトリン・ウィグナー#ep16wig";
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "話がまったく見えないんだけど。";
		mes "何があったの？";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お前が勝手にその箱を";
		mes "持ち出したから……";
		mes "はあ……とにかく、";
		mes "簡単に言うとお姉さん怒ってる。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "なんで姉さんが怒るのさ。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "話すと長くなるんだけど、";
		mes "お姉さんに関する悪い噂が";
		mes "出回っているらしいんだ。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "その噂なら聞いたことある。";
		mes "でもそれって兄さんが";
		mes "原因になっているから、";
		mes "そのうち兄さんが";
		mes "なんとかするだろうと";
		mes "思ってたけど……？";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "知っていたのか？";
		mes "なんで話してくれなかった？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "話したところで聞き流してただろう？";
		mes "天に授かった美しさを持つ兄さんは";
		mes "どうせ理解できないよ。";
		next;
		mes "[アイザック]";
		mes "おかげで周りのちやほやも";
		mes "当たり前だっただろう。";
		mes "両親も厳しかったわけではないしね。";
		mes "だから空気読めないんだよ。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お前……";
		mes "私を怒らせたいのか？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "まさか！";
		mes "いま話しているのは全て事実だよ。";
		mes "個人的な感情なんてないから";
		mes "最後まで聞いて欲しいんだ。";
		next;
		mes "[アイザック]";
		mes "兄さんは解らないだろうけど、";
		mes "その外見のおかげで";
		mes "知らないうちに私と姉さんは";
		mes "結構な被害にあったんだ。";
		next;
		mes "[アイザック]";
		mes "さっき姉さんが話してた";
		mes "影は光があるから";
		mes "生まれるってことだよ。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "よく解らないな。";
		mes "美しい外見が何故、";
		mes "被害を与えるんだ？";
		mes "みんな美しい物は好きだろう？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "見る人は、ね。";
		mes "でもその隣にいて";
		mes "常に比較される人にとっては違うのさ。";
		mes "特に姉さんはそのとばっちりを";
		mes "受けていたし。";
		next;
		mes "[アイザック]";
		mes "天使のような美しさを持つ人の隣に";
		mes "凡人が立っていると考えてみてよ。";
		mes "まったくもって普通なのに";
		mes "比較されるんだ。";
		next;
		mes "[アイザック]";
		mes "そして、隣にいる人物が";
		mes "美しければ美しいほど";
		mes "凡人は醜く見えてしまう。";
		mes "それが今までの私たちなんだ。";
		next;
		mes "[アイザック]";
		mes "姉さんが受けたストレスは";
		mes "特にひどかったろうね。";
		mes "どれだけ我慢し、慈しみの心で";
		mes "兄さんに接していたか。";
		mes "本当の天使は姉さんの方だよ。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "そんな……そのような……";
		mes "私はただ……";
		next;
		mes "[ユルゲン]";
		mes "どうすればいいんだ……";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "さあ？";
		mes "周囲の空気に気づけない";
		mes "兄さんにも原因はあるけど、";
		mes "元はと言えばそういう外見を与えた";
		mes "天が悪いんじゃないかな。";
		next;
		mes "[アイザック]";
		mes "とにかく、いま心配なのは姉さんだよ。";
		mes "今まで姉さんが怒ったの見たことある？";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "……一度だけ怒ったことがある。";
		mes "幼いころだけど。";
		mes "よくよく考えてみたら";
		mes "今と状況が似ていたような……";
		mes "比較……なんて言ってたっけ。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "私はもっと小さかったから";
		mes "記憶が曖昧だけど、";
		mes "兄さんと姉さんが言い争った後から";
		mes "話をしなくなったのは";
		mes "なんとなく覚えてるよ。";
		mes "やっぱり兄さんが原因じゃないか。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "今は誰が悪いのかを";
		mes "論じている場合ではないだろう。";
		mes "どうしましょうか、冒険者様？";
		next;
		menu "怒った人をなだめた経験は無いんですか？",-;
		mes "[ユルゲン]";
		mes "はい。私に怒る人なんて";
		mes "この世でおそらく";
		mes "お姉さん一人だけですから。";
		next;
		mes "[ユルゲン]";
		mes "冒険者様、とにかく私たちを";
		mes "助けてください。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "私は抜けるよ。";
		mes "別に私が姉さんを";
		mes "怒らせたわけじゃないし。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "待てよ、";
		mes "原因は姉さんの日記帳を";
		mes "勝手に持ち出したお前だろう。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "いや、私はただ持ち物が";
		mes "無くならないように……";
		mes "冒険者様、助けて！";
		next;
		menu "プレゼントとかどう？",-;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お姉さんが好きな物……";
		mes "アイザックは知ってるか？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "悪いけど、";
		mes "私は兄さんと同じ情報しか";
		mes "持ち合わせていないんだ。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "つまり、何も知らないって事か。";
		next;
		menu "大切な思い出がある物とかない？",-;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "そんなもの……あ？";
		mes "あるある！";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "へ？";
		mes "そんなのあったっけ？";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "まだ小さい時に";
		mes "家族でコモドビーチを";
		mes "訪れたことがあった。";
		mes "あの時の海岸と洞窟で";
		mes "綺麗な石を拾った覚えがある。";
		next;
		mes "[ユルゲン]";
		mes "姉さんが好きだった、";
		mes "透明な石の中に海水とサンゴが";
		mes "入っているような……";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "「海涙石」？";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "そう！　それだ！";
		mes "窓辺に吊るして太陽の光に煌めくのを";
		mes "ずっと見てたよな。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "ああ、思い出した。";
		mes "姉さんの部屋にあった";
		mes "あの綺麗な石！";
		mes "あれは海涙石だったのか。";
		next;
		menu "海涙石って何ですか？",-;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "コモドの特産品だったものです。";
		mes "海水のように透明な結晶の中に";
		mes "サンゴや砂が入っています。";
		mes "人魚が流した涙とも";
		mes "呼ばれてますね。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "ロマンチストな人は";
		mes "人魚の涙や人魚の贈り物とも";
		mes "呼びますが。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "コモドビーチの奥地で";
		mes "砂をあされば見つかるんです。";
		mes "みんなでワイワイ騒ぎながら";
		mes "探し回ったものです。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "最近はコモドビーチでは";
		mes "取れないらしいよ。";
		mes "理由はわからないけど";
		mes "^0000cdコモドダンジョン 01（西洞窟カル）";
		mes "^0000cdにいるメデューサ^000000から";
		mes "入手出来るようになったそうな。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "は？";
		mes "なんでモンスターがそんなものを";
		mes "持っているんだ？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "詳しくは知らないよ。";
		mes "人魚の贈り物というくらいだから";
		mes "半漁人がプレゼントでも";
		mes "したんじゃないの？";
		mes "子供の好きそうな話さ。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "あそこに半漁人は";
		mes "生息していないはずだが……";
		mes "それより、何でそんなことを";
		mes "知ってるんだ？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "いや、実は海涙石に関する";
		mes "事業を計画していたんだ。";
		mes "前はすぐに採取できてたから";
		mes "観光客や海に祈りを捧げる人が";
		mes "たまに探してたくらいだしね。";
		next;
		mes "[アイザック]";
		mes "ところがいつの間にか";
		mes "採れなくなって、";
		mes "赤字必至なんでやめたんだ。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "知らなかった……";
		mes "うーん、あとは石に飾られた花が";
		mes "なにかあったような……";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "そうだね。";
		mes "確かに花も飾られていた。";
		mes "しかも長い間枯れなかったよね。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様、枯れない花に";
		mes "なにか心当たりが？";
		next;
		menu "しおれないバラだと思う",-;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "そんなものがあるのですか？";
		mes "枯れてしまう前にまた新しい花を";
		mes "飾ればいいのでは？";
		next;
		menu "同じものを大切にしたいんだと思う",-;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "なるほど、同じもの。";
		mes "好きなものが長く続くことを";
		mes "望んでいるのか。";
		mes "枯れてしまって取り替えた花は";
		mes "もう「好きだった花」ではない、と。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "確かに……";
		mes "私が私でない誰かになるなんて";
		mes "想像するだけで寒気がする。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "で、持ってきてもらえますよね？";
		next;
		menu "え？",-;
		mes "[アイザック]";
		mes "まさか、私たちに集められるとでも";
		mes "思っておいでですか?!";
		next;
		mes "[アイザック]";
		mes "私は事業の準備がありますし、";
		mes "兄さんは外に出るだけで";
		mes "身動きも取れないほど";
		mes "人が集まってしまうので無理です。";
		next;
		mes "[アイザック]";
		mes "そして今の状況を知る人であり、";
		mes "信じられる人は……";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お願いします。";
		mes "ウィグナー家の平和は";
		mes "あなたの手にかかっています！";
		next;
		menu "わかりました……",-;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "そうですね。";
		mes "^0000cdしおれないバラは1個^000000あれば";
		mes "大丈夫そうです。";
		mes "^0000cd海涙石も1個^000000お願いします。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "よろしくお願いします。";
		delquest 14486;
		setquest 14487;
		set EP16_4QUE,12;
		next;
		cutin "16jur_nor.bmp",255;
		mes "‐^0000cdこのクエストを進行中のみ";
		mes "　^0000cdメデューサを討伐すると";
		mes "　^0000cd海涙石を入手できます^000000‐";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "海涙石を入手しに行くなら";
		mes "よろしければ、使いの者をだします。";
		mes "使いの者にコモドまで";
		mes "案内させますよ。";
		next;
		mes "[ユルゲン]";
		mes "しおれないバラは";
		mes "どこで入手できるか分からないので";
		mes "冒険者様自らの足で";
		mes "手に入れてきてください。";
		next;
		if(select("自力でいきます","お願いします") == 1) {
			mes "[ユルゲン]";
			mes "自力とはさすがですね。";
			mes "それではよろしくお願いします。";
			close2;
			cutin "16jur_nor.bmp",255;
			end;
		}
		mes "[ユルゲン]";
		mes "わかりました。";
		mes "それではお送りしましょう。";
		close2;
		warp "comodo.gat",34,215;
		end;
	case 12:
		cutin "16jur_sim.bmp",0;
		if(countitem(6927) < 1 || countitem(748) < 1) {
			mes "[ユルゲン]";
			mes "冒険者様、お願いしていた物は";
			mes "揃いましたか？";
			next;
			mes "[ユルゲン]";
			mes "あ、もしかして何をお願いしていたか";
			mes "お忘れですか？";
			next;
			mes "[ユルゲン]";
			mes "^0000cd海涙石が1個^000000。";
			mes "これはコモド西の洞窟にいる";
			mes "メデューサを倒せば";
			mes "手に入れることが出来るようです。";
			next;
			cutin "16jur_nor.bmp",255;
			mes "‐^0000cdこのクエストを進行中のみ";
			mes "　^0000cdメデューサを討伐すると";
			mes "　^0000cd海涙石を入手できます^000000‐";
			next;
			cutin "16jur_nor.bmp",0;
			mes "[ユルゲン]";
			mes "そして^0000cdしおれないバラ1個^000000です。";
			next;
			mes "[ユルゲン]";
			mes "困難な仕事かも知れませんが";
			mes "お姉さんを落ち着かせるために";
			mes "どうかお願いします。";
			next;
			mes "[ユルゲン]";
			mes "海涙石を入手しに行くなら";
			mes "よろしければ、使いの者をだします。";
			mes "使いの者にコモドまで";
			mes "案内させますよ。";
			next;
			mes "[ユルゲン]";
			mes "しおれないバラは";
			mes "どこで入手できるか分からないので";
			mes "冒険者様自らの足で";
			mes "手に入れてきてください。";
			next;
			if(select("自力でいきます","お願いします") == 1) {
				mes "[ユルゲン]";
				mes "自力とはさすがですね。";
				mes "それではよろしくお願いします。";
				close2;
				cutin "16jur_nor.bmp",255;
				end;
			}
			mes "[ユルゲン]";
			mes "わかりました。";
			mes "それではお送りしましょう。";
			close2;
			warp "comodo.gat",34,215;
			end;
		}
		mes "[ユルゲン]";
		mes "冒険者様、お願いしていたものは";
		mes "全て集まりましたか？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "そろそろ我慢の限界です……";
		mes "最近、姉さんが居ない時でも";
		mes "部屋中に冷ややかな雰囲気が";
		mes "漂っているようで……。";
		misceffect 89,"アイザック・ウィグナー#ep16wig";
		next;
		menu "どうぞ",-;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "おお！";
		mes "本当に全部集まったのですね！";
		mes "あなたは命の恩人です！";
		mes "それではお姉さんを呼ばないと……";
		mes "まだ怒ってるようですし";
		mes "どうやって呼び出そうか。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "姉さんなら呼んできたよ。";
		next;
		cloakoffnpc "カトリン・ウィグナー#ep16wig";
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "急に何の用なの？";
		mes "私の事なら怒ってないから";
		mes "放っておいて。";
		mes "本当に怒ってないから。";
		emotion 6,"カトリン・ウィグナー#ep16wig";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お姉さん、私たちが悪かった。";
		mes "だからもう怒らないで欲しい。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "……何が悪かったのかは";
		mes "解っているのよね？";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "姉さんの私物を勝手に";
		mes "持ち出した事……かな。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "私は……まあ、色々あるな。";
		mes "姉さんがどんな風に感じていたか";
		mes "全然知らなかった。";
		next;
		mes "[ユルゲン]";
		mes "でも家族だから、";
		mes "家族だからこそ";
		mes "話せなかったのかも知れないけど";
		mes "話して欲しかった。";
		next;
		mes "[ユルゲン]";
		mes "お互いの心に詰まった";
		mes "言葉を抱えたままだと";
		mes "今回のように誤解が生まれるのでは……";
		mes "そう思った。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "同感よ。";
		mes "確かに私も一人で考えてた。";
		mes "私にも非がある。";
		mes "もっと素直になるべきだった。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "まだ小さい時にだけど……";
		mes "あの時は何でも話せたよね。";
		mes "……これ、覚えてる？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "これは……いつの間に？";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様のおかげだよ。";
		mes "思い出して見たらあの幼い時が";
		mes "一番仲が良かった時かなって。";
		mes "ほら、この石。";
		mes "透明で中が透けて";
		mes "美しいサンゴが見えるよね。";
		next;
		mes "[ユルゲン]";
		mes "人間も一緒なんじゃないかな。";
		mes "全部見せる必要は";
		mes "無いかもしれないけど、";
		mes "少しは見せてみないと";
		mes "どんなに美しい物がそこにあるのか。";
		mes "解らないと思う。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "そうね。確かにそうだわ。";
		mes "私もこれからは努力する。";
		mes "誤解されないためにも。";
		next;
		mes "[カトリン]";
		mes "ところでそんな話……";
		mes "誰に習ったの？";
		mes "やっと人間らしい会話が";
		mes "できたわね。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "人間らしい会話って……";
		mes "まあ、いいや。";
		mes "これからはお互いに";
		mes "心をオープンにしていこうか。";
		next;
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "まあ、今日は兄弟が仲直りできた日だし";
		mes "もうケンカはやめよう。";
		mes "冒険者様もご苦労様でした。";
		mes "これは少ないですが";
		mes "私たちのために頑張っていただいた";
		mes "心ばかりのお礼です。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "恥ずかしい姿をお見せしてしまい、";
		mes "申し訳ありませんでした。";
		mes "またご訪問ください。";
		mes "改めて歓迎いたします。";
		next;
		if(checkitemblank() == 0) {	// 未調査
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様のおかげで";
		mes "気づいた事も多いです。";
		mes "冒険者様に助けが必要な時は";
		mes "力及ぶ限りお助けします。";
		mes "それでは！";
		delitem 6927,1;
		delitem 748,1;
		delquest 14487;
		set EP16_4QUE,13;
		setquest 201880;
		getitem 6919,30;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		next;
		cutin "16jur_nor.bmp",255;
		mes "‐ユルゲンにもう一度話しかけると";
		mes "　ウィグナー家の心の箱(おまけ)";
		mes "　クエストを開始できます‐";
		close;
	case 13:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "ああ、冒険者様。";
		mes "ようこそ。";
		mes "祝宴は楽しんでらっしゃいますか？";
		mes "何か必要な物でも？";
		next;
		menu "カトリンとの仲はどう？",-;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様のおかげで";
		mes "最近は会話も増えて、";
		mes "お互いに信頼しあえる";
		mes "仲になっています。";
		mes "それにですね……";
		next;
		cutin "16jur_nor.bmp",255;
		cloakoffnpc "メイド#ep16wig01";
		mes "[メイド]";
		mes "失礼します。";
		next;
		mes "[メイド]";
		mes "……！";
		mes "失礼致しました。";
		mes "御用中のようですので";
		mes "掃除は後に致します。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "いいえ、大丈夫ですよ。";
		mes "構わずにお仕事を";
		mes "なさってください。";
		next;
		cutin "16jur_nor.bmp",255;
		menu "お久しぶり",-;
		mes "[メイド]";
		mes "どこかでお会いしましたっけ？";
		mes "じゃなかった…";
		mes "ああ……はい……";
		mes "こんにちは……";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "もしかしてこの者が……？";
		mes "冒険者様が箱の行方を";
		mes "お聞きになったという……";
		next;
		menu "そうです",-;
		mes "[ユルゲン]";
		mes "あの時は失礼しました。";
		mes "事情が事情なだけに……";
		mes "改めてお詫びいたします。";
		next;
		cutin "16jur_nor.bmp",255;
		mes "[メイド]";
		mes "うーん。";
		mes "そうおっしゃっていただけると";
		mes "気が楽になります。";
		mes "ただ、もっと早く言ってもらえたら";
		mes "こんなことには……ブツブツ。";
		mes "おそすぎ……ブツブツ。";
		next;
		menu "どうしました？",-;
		mes "[メイド]";
		mes "あっ、いえ。";
		mes "なんでもありません！";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "あの、その……";
		next;
		cutin "16jur_nor.bmp",255;
		mes "[メイド]";
		mes "それでは失礼致します。";
		mes "原則として誰もいない時に";
		mes "清掃を行う決まりですので。";
		next;
		cloakonnpc "メイド#ep16wig01";
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "あ……ちょっと……";
		mes "まって……";
		next;
		mes "[ユルゲン]";
		mes "冒険者様……";
		next;
		menu "はい",-;
		cutin "16jur_sim.bmp",0;
		emotion 3;
		mes "[ユルゲン]";
		mes "^0000cd恋^000000みたいです。";
		next;
		menu "……はい？",-;
		emotion 23,"";
		cutin "16jur_nor.bmp",0;
		emotion 3;
		mes "[ユルゲン]";
		mes "なんでだろう。";
		mes "この心臓の鼓動……";
		mes "あの方が初めてです。";
		next;
		mes "[ユルゲン]";
		mes "何というか……";
		mes "胸の高鳴りが止まりません。";
		mes "凛と張った声に飾りのない行動。";
		mes "そして意志を貫く言動。";
		next;
		mes "[ユルゲン]";
		mes "今まで出会った女性も美しく、";
		mes "優雅な温室の花のようでしたが。";
		mes "彼女は広い草原に咲いた花のような";
		mes "清々しさがあります。";
		next;
		mes "[ユルゲン]";
		mes "今まで出会った女性にはない";
		mes "力強さを感じます。";
		next;
		mes "[ユルゲン]";
		mes "冒険者様！";
		mes "どのように心の内を伝えれば";
		mes "良いのでしょうか！";
		mes "手を取り、愛の言葉を囁けば";
		mes "良いのでしょうか？";
		next;
		menu "告白は初めて？",-;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "はい。そしてどうやら彼女が";
		mes "^0000cd私の初恋の相手^000000です。";
		mes "ああ、こんなに胸が高鳴る！";
		mes "私の人生はすばらしいものに";
		mes "なりました！";
		next;
		menu "アピールするの？",-;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "アピールですか……";
		mes "記憶に残るのは……ああ！";
		mes "警備網を潜り抜け";
		mes "私の部屋のカーテンの後ろに";
		mes "潜んでいた人がいました！";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "実物大の私の黄金像を";
		mes "送ってきた人もいました。";
		mes "私の方が美しいので";
		mes "送り返しましたが。";
		next;
		mes "[ユルゲン]";
		mes "そうですね、";
		mes "私と全く同じ黄金像を";
		mes "プレゼントするのは";
		mes "どうでしょうか！";
		next;
		menu "うーん…手紙とかどう？",-;
		mes "[ユルゲン]";
		mes "手紙！　いいですね！";
		mes "少々お待ちください！";
		next;
		menu "待つ？",-;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お忘れですか？";
		mes "私がここから出たら";
		mes "大混乱が起きます。";
		next;
		mes "[ユルゲン]";
		mes "そうなれば彼女……";
		mes "名前も聞いていませんでしたね。";
		mes "とにかく彼女にも迷惑になります。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "ふう……";
		mes "それではこの手紙を宝石が入った箱と";
		mes "一緒にお渡しください。";
		mes "私の心の声と共に。";
		next;
		if(select("わかりました","お断り！")==2) {
			cutin "16jur_sim.bmp",0;
			mes "[ユルゲン]";
			mes "やはり無理でしたか。";
			mes "それでは直接いきます。";
			next;
			mes "[ユルゲン]";
			mes "明日のルーンミッドガッツニュースの";
			mes "トップは";
			mes "「ウィグナー家の後継者、";
			mes "人波に飲まれ圧死」";
			mes "ですかね。";
			next;
			mes "[ユルゲン]";
			mes "それとも";
			mes "「王宮メイド、病院送り！　原因は？」";
			mes "なんてニュースになるかも";
			mes "知れませんね……";
			close2;
			cutin "16jur_nor.bmp",255;
			end;
		}
		mes "[ユルゲン]";
		mes "ありがとうございます！";
		mes "それではお願いします！";
		setquest 14488;
		set EP16_4QUE,14;
		close2;
		cutin "16jur_nor.bmp",255;
		end;
	case 14:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様！";
		mes "今か今かと待っていました！";
		mes "それで返事は？";
		close2;
		cutin "16jur_nor.bmp",255;
		end;
	case 15:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様！";
		mes "今か今かと待っていました！";
		mes "それで返事は？";
		mes "もちろん良い返事ですよね？";
		next;
		menu "お断りされました",-;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "断られ……た……？";
		mes "そんな！";
		mes "私は彼女の好みではない";
		mes "という事でしょうか！";
		mes "それともお送りした物が";
		next;
		menu "何か事情がありそう",-;
		mes "[ユルゲン]";
		mes "はっ！";
		mes "もしかして既に恋人がいるのでは？";
		mes "そうだよな……あんな魅力的な方が……";
		mes "一人なはずが……";
		mes "やはり私が好きになった方！";
		next;
		mes "[ユルゲン]";
		mes "ハア……";
		mes "^0000cd生まれて初めて切に願うもの^000000が";
		mes "こんなにも叶えづらいものとは！";
		mes "生きるって……胸が苦しい……";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "ですが父様はおっしゃいました！";
		mes "挑戦は少なくとも";
		mes "3回は続けられるべきだと！";
		next;
		mes "[ユルゲン]";
		mes "最初は一歩を踏み出すため、";
		mes "その次は確認のため、";
		mes "最後は今生の縁でないと";
		mes "諦めるため。";
		next;
		mes "[ユルゲン]";
		mes "ですから冒険者様、";
		mes "もう一度お願いします。";
		next;
		mes "[ユルゲン]";
		mes "特別な何か……";
		mes "私の心を伝えられる……";
		mes "そして花……";
		next;
		mes "[ユルゲン]";
		mes "海涙石！";
		mes "そしてしおれないバラ！";
		next;
		menu "うそだろユルゲン！",-;
		mes "[ユルゲン]";
		mes "彼女へのプレゼントです。";
		mes "^0000cd透き通る海のように";
		mes "私の胸のうちを見せたいという心^000000と";
		mes "彼女への^0000cd尽きない想いを表す心^000000として！";
		next;
		menu "さてと、そろそろ……",-;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お待ちください！";
		mes "冒険者様、どうかお願いします！";
		mes "私の恋の伝令になってください！";
		mes "彼女に私の透き通るような";
		mes "尽きない好意をお伝えください！";
		next;
		menu "わかりました……",-;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "私の手紙と^0000cd海涙石1個、";
		mes "しおれないバラ1個^000000を";
		mes "彼女にお伝えください。";
		mes "お願いします。";
		next;
		mes "[ユルゲン]";
		mes "海涙石はこの前と同じく";
		mes "メデューサを倒せば";
		mes "手に入るはずです。";
		next;
		mes "[ユルゲン]";
		mes "冒険者様、それではお願いします。";
		mes "ウィグナーはどんな借りでも";
		mes "必ず返します。";
		next;
		menu "了解",-;
		mes "[ユルゲン]";
		mes "ありがとう！";
		mes "ところで彼女の名前は……？";
		next;
		menu "メリー",-;
		mes "[ユルゲン]";
		mes "^0000cdメリー^000000……";
		mes "綺麗な名前ですね。";
		mes "私の心にその名を刺繍のごとく";
		mes "綴りましょう！";
		next;
		mes "[ユルゲン]";
		mes "冒険者様、どうか私の";
		mes "この燃えるような気持ちを";
		mes "メリー様にお伝えください！";
		set EP16_4QUE,16;
		delquest 14489;
		setquest 14490;
		next;
		mes "[ユルゲン]";
		mes "海涙石を入手しに行くなら";
		mes "よろしければ、使いの者をだします。";
		mes "使いの者にコモドまで";
		mes "案内させますよ。";
		next;
		mes "[ユルゲン]";
		mes "しおれないバラは";
		mes "どこで入手できるか分からないので";
		mes "冒険者様自らの足で";
		mes "手に入れてきてください。";
		next;
		if(select("自力でいきます","お願いします")==1) {
			mes "[ユルゲン]";
			mes "自力とはさすがですね。";
			mes "それではよろしくお願いします。";
			close2;
			cutin "16jur_nor.bmp",255;
			end;
		}
		mes "[ユルゲン]";
		mes "わかりました。";
		mes "それではお送りしましょう。";
		close2;
		cutin "16jur_nor.bmp",255;
		warp "comodo.gat",34,215;
		end;
	case 16:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "メリー様に私の心を伝えて……";
		mes "というにはあまりにも";
		mes "時間が経っていませんね。";
		next;
		mes "[ユルゲン]";
		mes "もしかして依頼の品を";
		mes "お忘れになりましたか？";
		next;
		mes "[ユルゲン]";
		mes "手紙はお持ちですね。";
		mes "後はメデューサを倒して得られる";
		mes "^0000cd海涙石1個と";
		mes "しおれないバラ1個^000000を";
		mes "お願いします。";
		next;
		mes "[ユルゲン]";
		mes "このような平凡なものでも";
		mes "私の心を伝えられるなら……";
		mes "それにメリー様も";
		mes "負担に感じないでしょう！";
		mes "さあ！　私のこの心を";
		mes "お伝えください！";
		next;
		mes "[ユルゲン]";
		mes "海涙石を入手しに行くなら";
		mes "よろしければ、使いの者をだします。";
		mes "使いの者にコモドまで";
		mes "案内させますよ。";
		next;
		mes "[ユルゲン]";
		mes "しおれないバラは";
		mes "どこで入手できるか分からないので";
		mes "冒険者様自らの足で";
		mes "手に入れてきてください。";
		next;
		if(select("自力でいきます","お願いします")==1) {
			mes "[ユルゲン]";
			mes "自力とはさすがですね。";
			mes "それではよろしくお願いします。";
			close2;
			cutin "16jur_nor.bmp",255;
			end;
		}
		mes "[ユルゲン]";
		mes "わかりました。";
		mes "それではお送りしましょう。";
		close2;
		cutin "16jur_nor.bmp",255;
		warp "comodo.gat",34,215;
		end;
	case 17:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様!　どうでしたか？";
		mes "私は冒険者様が";
		mes "この部屋を出た瞬間から";
		mes "メリー様に対する心を";
		mes "留める事ができませんでした！";
		next;
		emotion 3;
		mes "[ユルゲン]";
		mes "食事中も、鏡を見ても、";
		mes "他の人との会話の時も";
		mes "彼女の姿が目の前に揺らめいて……";
		mes "一日中メリー様の事ばかり";
		mes "考えてしまいます！";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "これが恋！私は今まで";
		mes "なんと多くの罪を犯したのでしょう！";
		mes "あまりにも多くの女性の恋を";
		mes "踏み躙ってきました。";
		mes "ですがその人たちにいまさら";
		mes "何かできるとは思えません。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "ところで冒険者様の表情を見ると";
		mes "どうやらメリー様が私の心を";
		mes "受け取ってくれたのでしょうか！";
		next;
		menu "もう少し時間が必要そう",-;
		mes "[ユルゲン]";
		mes "それでは私の心を";
		mes "全部受け止めていただいたわけでは";
		mes "ありませんね……";
		mes "それでもかまいません！";
		mes "完全に拒まれたわけでは";
		mes "ありませんから！";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "誰かを好きになる事が";
		mes "ここまで苦しいとは";
		mes "思いもしませんでした。";
		mes "言葉一つ、手の動き一つにも";
		mes "胸が締め付けられるようです。";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "これからは私の事を";
		mes "好きになってくれた全ての人々に";
		mes "親切にしなくては！";
		next;
		mes "[ユルゲン]";
		mes "決めました。";
		mes "時間が必要ならば、";
		mes "私はメリーに毎日想いを伝えましょう。";
		mes "時と運はつかむものですから！";
		mes "私の心を毎日、毎時！";
		next;
		menu "うーん……",-;
		emotion 3;
		mes "[ユルゲン]";
		mes "私の直感では冒険者様が";
		mes "仲を持っていただけたので";
		mes "全てが上手くいく気がするんです。";
		next;
		menu "そうですかね",-;
		if(checkitemblank() == 0) {	// 未調査
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "ああ、そうだ。";
		mes "すっかり忘れるところでした。";
		mes "つまらないものですが";
		mes "お礼の気持ちを準備しました。";
		mes "どうぞ受け取ってください。";
		delquest 14491;
		setquest 201881;
		set EP16_4QUE,18;
		getitem 6919,20;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		close2;
		cutin "16jur_nor.bmp",255;
		end;
	case 18:
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "これからは私の事を";
		mes "好きになってくれた全ての人々に";
		mes "親切にしなくては！";
		next;
		mes "[ユルゲン]";
		mes "決めました。";
		mes "時間が必要ならば、";
		mes "私はメリーに毎日想いを伝えましょう。";
		mes "時と運はつかむものですから！";
		mes "私の心を毎日、毎時！";
		next;
		mes "[ユルゲン]";
		mes "冒険者様！";
		mes "私に気付かせてくれて";
		mes "ありがとうございました！";
		close2;
		cutin "16jur_nor.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,96,7,1	script(CLOAKED)	カトリン・ウィグナー#ep16wig	10125,{
	switch(EP16_4QUE) {
	case 0:
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "……。";
		close2;
		cutin "16kat_nor.bmp",255;
		end;
	case 1:
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "冒険者様、";
		mes "ウィグナー家にご訪問いただき光栄です。";
		mes "ユルゲンには";
		mes "もうお会いになりましたか？";
		close2;
		cutin "16kat_nor.bmp",255;
		end;
	case 2:
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "父とお話をしてください。";
		close2;
		cutin "16kat_nor.bmp",255;
		end;
	case 3:
		cutin "16kat_ang.bmp",2;
		mes "[カトリン]";
		mes "私は破滅よ！";
		next;
		menu "どうしました？",-;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "お姉さん、まずは落ち着こう。";
		mes "ここに置いたのは確かなんだね？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "そう、ここ！";
		mes "ここに置いてあったの！";
		mes "先ほど冒険者様とお話をしてから";
		mes "ここに置いたのに……";
		mes "消えてしまったの！";
		next;
		menu "何を無くしたのですか？",-;
		mes "[カトリン]";
		mes "私の宝石箱が……いえ";
		mes "中身は宝石ではないのですが、";
		mes "とにかく大事なものが入った";
		mes "^0000cd小さな箱がなくなりました^000000。";
		next;
		mes "[カトリン]";
		mes "先ほどカバンから取り出して";
		mes "ここに置いたのですが……";
		mes "どうしましょう……";
		mes "もしも誰かにあれを";
		mes "見られでもしたら……っ!!";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "もしかしたら";
		mes "掃除に来た^0000cdメイド^000000が";
		mes "片付けてしまったのでは？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "ユルゲン、いけません！";
		mes "そのメイドが持っていくのを";
		mes "直接見たわけではないでしょう？";
		mes "状況だけで人を疑うのは";
		mes "良くない事です。";
		next;
		menu "話を聞くのは良い案だと思います",-;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "いいえ、その必要はありません。";
		mes "話を聞きにいけば、";
		mes "自分は疑われていると考えるでしょう。";
		mes "きっと気分を害する事になります。";
		next;
		cutin "16jur_sim.bmp",0;
		mes "[ユルゲン]";
		mes "でもそんなに不安になるほど、";
		mes "大事な物なんでしょう？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "それは……そうだけど……";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "絶対に見つけ出さないと";
		mes "駄目なんだよね？";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "そう……だけど……";
		next;
		menu "どうか安心してお待ちください",-;
		mes "[カトリン]";
		mes "……それが最善かは……";
		mes "わかりません。";
		mes "疑いをかけているようで……";
		next;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "冒険者様を信じてみよう。";
		mes "多くの経験を積んだ方だから";
		mes "きっと上手くいくよ。";
		next;
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "……そう。";
		mes "それではお願い致します。";
		mes "私は念のため";
		mes "他の場所を探してみます。";
		next;
		cloakonnpc;
		cutin "16jur_nor.bmp",0;
		mes "[ユルゲン]";
		mes "お願いします。";
		mes "^0000cdメイド達は台所にいる^000000と聞きました。";
		chgquest 14477,14478;
		set EP16_4QUE,4;
		close2;
		cutin "16jur_nor.bmp",255;
		end;
	case 11:
		mes "[ユルゲン]";
		mes "お姉さんが無くしたものが";
		mes "一体何なのかは";
		mes "わかりません。";
		next;
		mes "[ユルゲン]";
		mes "私を好きな人々に声をかけて";
		mes "探してもらえば、";
		mes "あーっ！";
		mes "という間に見つかるでしょう。";
		mes "しかし、それでは父が";
		mes "黙っていない理由があるのです。";
		next;
		mes "[ユルゲン]";
		mes "仕方ありません、";
		mes "冒険者様にお任せするのが";
		mes "最善かと思われます。";
		mes "冒険者様の手にかかってますよ！";
		close2;
		cutin "16jur_sim.bmp",255;
		end;
	default:
		cutin "16kat_nor.bmp",2;
		mes "[カトリン]";
		mes "冒険者様のおかげで";
		mes "以前よりも兄弟の仲が";
		mes "良くなったように感じます。";
		mes "これからは弟達にも";
		mes "胸の中にしまっていた話を";
		mes "しようと思います。";
		next;
		mes "[カトリン]";
		mes "今までは感情を押し殺し、";
		mes "言葉も声に出さないように";
		mes "していましたが";
		mes "それが良い事ではないと";
		mes "気づきました。";
		next;
		mes "[カトリン]";
		mes "これからは素直になって";
		mes "誤解を生まないように";
		mes "話をしていきたいと思います。";
		next;
		mes "[カトリン]";
		mes "冒険者様、";
		mes "本当にありがとうございました。";
		close2;
		cutin "16kat_nor.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,90,16,0	script	#ep16wig004	139,14,14,{
	end;
OnTouch:
	if(EP16_4QUE == 2 || EP16_4QUE == 3) {
		cloakoffnpc "カトリン・ウィグナー#ep16wig";
		if(EP16_6QUE == 2 || EP16_6QUE == 8)
			cloakoffnpc "アイザック・ウィグナー#ep16wig";
		else
			cloakonnpc "アイザック・ウィグナー#ep16wig";
	} else if(EP16_4QUE > 3 && EP16_4QUE < 12) {
		cloakonnpc "カトリン・ウィグナー#ep16wig";
		if(EP16_6QUE == 2 || EP16_6QUE == 8)
			cloakoffnpc "アイザック・ウィグナー#ep16wig";
		else
			cloakonnpc "アイザック・ウィグナー#ep16wig";
	} else if(EP16_4QUE == 12) {
		cloakonnpc "カトリン・ウィグナー#ep16wig";
		cloakoffnpc "アイザック・ウィグナー#ep16wig";
	} else {
		cloakoffnpc "カトリン・ウィグナー#ep16wig";
		cloakoffnpc "アイザック・ウィグナー#ep16wig";
	}

	switch(rand(3)) {
	case 1:
		if(!getnpctimer(1,"田舎者の男性#ep16wig01") && !getnpctimer(1,"一途な女性#ep16wig01")) {
			donpcevent "一途な女性#ep16wig01::OnStart";
			end;
		}
		break;
	case 2:
		if(!getnpctimer(1,"田舎者の男性#ep16wig01") && !getnpctimer(1,"一途な女性#ep16wig01")) {
			donpcevent "田舎者の男性#ep16wig01::OnStart";
			end;
		}
		break;
	}
	end;
}

prt_cas_q.gat,94,7,7	script(CLOAKED)	アイザック・ウィグナー#ep16wig	10126,{
	switch(EP16_6QUE) {
	case 2:
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "ああ、いらっしゃいましたか、";
		mes "兄さんならあちらに……";
		next;
		menu "あなたに用があります",-;
		mes "[アイザック]";
		mes "ヴォルフ様の事ですか？";
		next;
		menu "はい",-;
		mes "[アイザック]";
		mes "ヴォルフ様が約束の時間に";
		mes "遅れる事は今まで一度も";
		mes "ありませんでしたから。";
		mes "何かあったのでは、と。";
		next;
		mes "[アイザック]";
		mes "まあ、冒険者様が代わりに";
		mes "いらっしゃるのは想定外でしたが。";
		mes "それでは本日の会談は";
		mes "取り消しという事でしょうか。";
		next;
		menu "ある物を受け取りにきました",-;
		mes "[アイザック]";
		mes "あれ？……そうですか。";
		mes "どうやらヴォルフ様が";
		mes "冒険者様を信頼しているようですね。";
		next;
		menu "試されているのかも",-;
		mes "[アイザック]";
		mes "気を悪くしないでください。";
		mes "元々疑り深い性格でもありますし、";
		mes "こういう仕事をしている分には";
		mes "相手が信頼に値するのか";
		mes "確認が必要ですしね。";
		next;
		mes "[アイザック]";
		mes "これを……ヴォルフ様に";
		mes "お伝えください。";
		mes "取り扱いには注意してください。";
		next;
		mes "[アイザック]";
		mes "それともう一つお願いをしても";
		mes "よろしいでしょうか？";
		mes "最近プロンテラを中心として";
		mes "^0000cdとある噂^000000が広まっているそうです。";
		next;
		mes "[アイザック]";
		mes "^0000cdヘルムト・レベンブルグに関する噂^000000";
		mes "だそうです。";
		mes "とりあえず調査後に事実なのかの";
		mes "確認をしたいと思います。";
		next;
		if(checkitemblank() == 0) {	// 未調査
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		mes "[アイザック]";
		mes "評判も重要ですので";
		mes "何かある前に調べる必要があります。";
		mes "それではお願いします。";
		set EP16_6QUE,3;
		delquest 14496;
		setquest 14497;
		getitem 6930,1;
		next;
		mes "[アイザック]";
		mes "それでは私はこれで失礼します。";
		cloakonnpc;
		close2;
		cutin "16isa.bmp",255;
		end;
	case 8:
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "ああ、冒険者様。";
		mes "どうでしたか？";
		mes "例の物は伝えていただけたようですね。";
		mes "ところで噂に関しては……";
		next;
		menu "ヴォルフ・レベンブルグ直筆の書類を渡す",-;
		mes "[アイザック]";
		mes "確かに受け取りました。";
		mes "なるほど……";
		mes "そうだったのですね……";
		mes "というわけで新事業は";
		mes "期間未定で延期……";
		mes "事業方針を変更する、ですか。";
		next;
		mes "[アイザック]";
		mes "整理が付いたら直接伺います。";
		mes "との事ですね。";
		next;
		mes "[アイザック]";
		mes "という事は結局戦争は";
		mes "起こさないという事ですね。";
		mes "噂の威力が少なくなかったようですね。";
		next;
		mes "[アイザック]";
		mes "少し惜しいですね。";
		mes "私も家門内での立場を固める";
		mes "良い機会でしたのに。";
		next;
		mes "[アイザック]";
		mes "ですが、ヴォルフ様なら";
		mes "さらに良い案を出してくれるでしょう。";
		mes "ヴォルフ様には了解したと";
		mes "お伝えください。";
		mes "そして新しい事業方針にも";
		mes "期待していると。";
		next;
		menu "わかりました",-;
		mes "[アイザック]";
		mes "よろしくお願いします。";
		delitem 6931,1;
		delquest 14502;
		setquest 14503;
		set EP16_6QUE,9;
		next;
		mes "[アイザック]";
		mes "それでは私はこれで失礼します。";
		cloakonnpc "アイザック・ウィグナー#ep16wig";
		close2;
		cutin "16isa.bmp",255;
		end;
	default:
		break;
	}
	switch(EP16_4QUE) {
	case 0:
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "ウィグナー家には";
		mes "初めていらっしゃいましたか？";
		mes "それではあちらにおります";
		mes "私の^0000cd両親にお会いになって^000000ください。";
		close2;
		cutin "16isa.bmp",255;
		end;
	case 1:
	case 2:
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "冒険者様、まずはウィグナー家にいる";
		mes "他の家族にもあっていただけますか？";
		mes "父や母、王位継承候補の兄と";
		mes "長女の姉にも。";
		next;
		mes "[アイザック]";
		mes "良いお話が聞けると思います。";
		close2;
		cutin "16isa.bmp",255;
		end;
	case 12:
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "冒険者様、お願いしていた物は";
		mes "集まりましたか？";
		next;
		mes "[アイザック]";
		mes "私が直接集めてきた方が";
		mes "仲直りとしては良いでしょうが、";
		mes "身内の恥を外にさらけ出すような";
		mes "ものですので……";
		next;
		mes "[アイザック]";
		mes "お手数をお掛けしますが";
		mes "お願いします。";
		mes "ああ、念のため集める物は、";
		next;
		mes "[アイザック]";
		mes "^0000cd海涙石1個、しおれないバラ1個^000000です。";
		next;
		mes "[アイザック]";
		mes "冒険者様の手に";
		mes "我々姉弟の仲がかかっています。";
		next;
		mes "[アイザック]";
		mes "それではお願いします！";
		mes "できるだけ早く！";
		close2;
		cutin "16isa.bmp",255;
		end;
	case 13:
		cutin "16isa.bmp",1;
		mes "[アイザック]";
		mes "冒険者様のおかげで兄さんと姉さんの";
		mes "仲直りができました。";
		mes "まあ、私のおかげでもありますが。";
		next;
		mes "[アイザック]";
		mes "あはは、冗談ですよ！";
		mes "冒険者様、私はこれで失礼します。";
		close2;
		cutin "16isa.bmp",255;
		end;
	}
}

prt_cas_q.gat,93,10,4	script(CLOAKED)	メイド#ep16wig01	69,{}

prt_cas.gat,322,216,5	script	メイド#ep16wig02	69,{
	switch(EP16_4QUE) {
	case 4:
		mes "[メイド]";
		mes "今日もキツいと評判の";
		mes "キッチン掃除……";
		mes "何とか終わらせないと……";
		next;
		mes "[メイド]";
		mes "どこかにこんな私を";
		mes "助けてくれる人は";
		mes "いないかな……って";
		mes "何か御用でしょうか？";
		next;
		menu "ウィグナー家の掃除を担当している方？",-;
		mes "[メイド]";
		mes "あ、はい。私です。";
		mes "何か問題でも……？";
		next;
		menu "小さな箱を見ませんでしたか？カトリンの物です",-;
		mes "[メイド]";
		mes "あ、はい。たしかに見ました。";
		mes "単調ながら高級感溢れる箱でした。";
		mes "掃除の際には一度ずらしましたが、";
		mes "テーブルを拭き終えた後には";
		mes "ぴったりと元の位置に戻しました。";
		next;
		menu "状況をもっと詳しく",-;
		mes "[メイド]";
		mes "あの、すみません。";
		mes "これってもしかしなくても";
		mes "私疑われているんですよね。";
		next;
		emotion 6,"メイド#ep16wig02";
		mes "[メイド]";
		mes "貴族の部屋でなくなったものがあって、";
		mes "^0000cd掃除をしていたメイドが盗んだ^000000と……";
		next;
		menu "疑っているわけではないです",-;
		emotion 6,"メイド#ep16wig02";
		mes "[メイド]";
		mes "でも心の片隅では";
		mes "疑っておいででしょう。";
		mes "違いますか？";
		next;
		emotion 7,"メイド#ep16wig02";
		mes "[メイド]";
		mes "ふう……";
		mes "メイドという仕事をしていると";
		mes "こういう事も結構ありますので";
		mes "大丈夫です。";
		mes "疑われるのは慣れませんけど。";
		next;
		mes "[メイド]";
		mes "私は何も盗んでいません。";
		mes "でもそうですね……";
		mes "他に人は……";
		next;
		menu "あなたの他に人はいたのですか？",-;
		mes "[メイド]";
		mes "それが……いたような、";
		mes "いなかったような。";
		mes "^0000cdキッチンが綺麗になれば";
		mes "^0000cd思い出せそう^000000です。";
		mes "あまりに汚くて私の頭の中も";
		mes "混乱していまして……";
		next;
		emotion 45,"メイド#ep16wig02";
		mes "[メイド]";
		mes "あ～あ～！";
		mes "誰か私を手伝ってくれる";
		mes "優しい人はいないのかな～。";
		next;
		menu "手伝いましょう",-;
		emotion 18,"メイド#ep16wig02";
		mes "[メイド]";
		mes "あら！";
		mes "手伝ってくださるのですか！";
		mes "それじゃこの^0000cdポリンたわし^000000を";
		mes "お貸しします。";
		mes "隅々までちゃんと掃除してくださいね！";
		next;
		mes "[メイド]";
		mes "特殊な製法で製作された";
		mes "とても凄いたわしなので";
		mes "いろんな場所で使う事ができます。";
		mes "掃除の手順までコーチしてくれる";
		mes "優れ物ですよ。";
		next;
		mes "[メイド]";
		mes "初めて使う方は驚くかも知れませんが、";
		mes "人に害は及ぼしたりしないので";
		mes "安心してください。";
		mes "伝説的なとある方が";
		mes "作った物だそうです。";
		next;
		if(checkitemblank() == 0) {
			mes "[メイド]";
			mes "あら？";
			mes "荷物がいっぱいですね。";
			mes "荷物に1個以上の空きを作ってから";
			mes "また来てください。";
			close;
		}
		mes "[メイド]";
		mes "ああ、あと掃除にもちゃんと";
		mes "順番がありますからね。";
		mes "まずは壁のカビ取りから。";
		mes "粘ついた汚れを取ったら";
		mes "最後に床掃除です！";
		delquest 14478;
		setquest 14479;
		setquest 73062;
		getitem 6928,3;
		set EP16_4QUE,5;
		close;
	case 5:
	case 6:
	case 7:
		mes "[メイド]";
		mes "もう終わったのですか？";
		mes "あらあら、まだみたいですね。";
		next;
		mes "[メイド]";
		mes "先ほどお渡ししたたわしで";
		mes "ちゃんと掃除をしてくださいね。";
		close;
	case 8:
		emotion 21;
		mes "[メイド]";
		mes "うわあ～！";
		mes "本当にピカピカになりました！";
		mes "私の腕力じゃ";
		mes "ここまでの掃除は無理です。";
		mes "いっそキッチン専門の";
		mes "清掃員に転職しませんか？";
		next;
		mes "[メイド]";
		mes "あの部屋は臨時で";
		mes "使用するものとはいえ、";
		mes "ルーンミッドガッツ最高の富を誇る";
		mes "ウィグナー家が使用しました。";
		next;
		mes "[メイド]";
		mes "当然それに見合う家具や";
		mes "カーペットが絶え間なく運ばれ";
		mes "飾られていたのです。";
		mes "それに私、今まであのように";
		mes "優雅で豪華な虎の皮は";
		mes "初めて見ました。";
		next;
		menu "家具ではなく人の話をしたいです",-;
		mes "[メイド]";
		mes "はあ……";
		mes "ちょっとは空気を読んでください。";
		mes "腹黒い貴族を相手している方が";
		mes "こんなに鈍感とは……";
		next;
		mes "[メイド]";
		mes "はい、ここまで聞いたら";
		mes "わかりますよね。";
		mes "なぜ私が^0000cd家具の話^000000をしていたのか。";
		next;
		menu "まさか家具の配達人？",-;
		mes "[メイド]";
		mes "私は誰とは言ってませんけど";
		mes "他にも出入りする人を調べれば";
		mes "何か解るかもしれませんね。";
		mes "ところで……";
		mes "本当に箱を無くしたのですか？";
		next;
		mes "[メイド]";
		mes "王宮ではいろんな噂話を聞けますが、";
		mes "小耳に挟んだ話です。";
		mes "ウィグナー家の王子様は";
		mes "とてもお美しいではありませんか。";
		next;
		mes "[メイド]";
		mes "幼い頃から弟の王子様ばかり";
		mes "注目を浴びていたので";
		mes "ストレスがたまったお姫様のほうは";
		mes "人々の注目を集めようと必死だと。";
		next;
		mes "[メイド]";
		mes "そのような噂話があるのです。";
		next;
		mes "[メイド]";
		mes "まだ、一部の人の間で";
		mes "ささやかれているだけのようですが、";
		mes "本日のティータイムが終わる頃には";
		mes "王宮中に知れ渡るかも知れません。";
		next;
		menu "いやいや、まさか",-;
		emotion 6;
		mes "[メイド]";
		mes "だから「噂」なのです。";
		mes "私はただ聞いただけです。";
		mes "それじゃ私はこれで失礼します。";
		next;
		menu "配達人ってどこにいるの？",-;
		mes "[メイド]";
		mes "そうですね、プロンテラのどこか……";
		mes "とは思いますが。";
		mes "まずは^0000cdプロンテラ南西の";
		mes "^0000cd屋台が並んでいる辺り^000000に";
		mes "行ってみてください。";
		mes "お店はその近くですから。";
		next;
		mes "[メイド]";
		mes "あ、それと私は何も話していません。";
		mes "噂話は噂ですから。";
		delquest 14483;
		setquest 14484;
		set EP16_4QUE,9;
		next;
		mes "‐配達人のところに向かおうかな？‐";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐配達人のところに向かった‐";
		close2;
		warp "prontera.gat",46,94;
		end;
	case 9:
		mes "[メイド]";
		mes "冒険者様？";
		mes "家具配達員の方でしたら……";
		mes "^0000cd区役所の近く^000000だと思います。";
		mes "多分。";
		next;
		mes "[メイド]";
		mes "それじゃ私は掃除の続きをしますので。";
		mes "失礼いたします。";
		next;
		mes "‐配達人のところに向かおうかな？‐";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐配達人のところに向かった‐";
		close2;
		warp "prontera.gat",46,94;
		end;
	case 14:
		emotion 6;
		mes "[メイド]";
		mes "だーもう！";
		mes "なんて頑固な汚れなんだ……";
		mes "全然消えないな……";
		mes "何で僕がこんな事を……";
		next;
		menu "すいません",-;
		mes "[メイド]";
		mes "わ！急に話しかけないで！";
		mes "びっくり！";
		mes "あ、う……じゃなくてはい。";
		mes "えーと、初めて会うのかな？";
		mes "前にもあったことがあるのかな？";
		mes "冒険者の方、だよね？";
		next;
		menu "覚えてないの？",-;
		emotion 16;
		mes "[メイド]";
		mes "ああ、あああ。";
		mes "はい、そうでしたね。";
		mes "^0000cd顔を覚えるのが苦手で^000000……";
		mes "どのようなご用件でしょう？";
		next;
		menu "なんか感じが変わった？",-;
		mes "[メイド]";
		mes "ま、まさか！";
		mes "僕はいつもどおり……って";
		mes "僕、じゃなくてー、私！";
		mes "私はいつもどおりです";
		mes "アハハ。";
		next;
		menu "ユルゲンの手紙を渡す",-;
		mes "[メイド]";
		mes "これは……もしかして";
		mes "何かの請求書ですか？";
		mes "私何か大きな失敗でも？";
		next;
		menu "どうぞ読んでください",-;
		mes "[メイド]";
		mes "それでは……";
		mes "読んでみます。";
		next;
		emotion 14;
		mes "[メイド]";
		mes "「いきなりですがあなたが好きです。";
		mes "　ものすごく好きです。";
		mes "　デートしたいです。";
		mes "　　　　　　　　　　　ユルゲン」";
		mes "……はい……ええ？";
		mes "……うーん……はい。";
		next;
		mes "[メイド]";
		mes "えっと……";
		mes "つまりこれは……";
		mes "あれ……ですか？";
		next;
		menu "ラブレター",-;
		mes "[メイド]";
		mes "ふう……申し訳ありませんが";
		mes "お返しすると伝えてください。";
		mes "お心は……そう、";
		mes "ありがたいですけど……";
		next;
		menu "もしかして恋人がもういる？",-;
		mes "[メイド]";
		mes "いえ、そうではありませんが……";
		mes "とにかくお返しください。";
		mes "あまりにも突然ですし、";
		mes "身分も違いますし。";
		next;
		mes "[メイド]";
		mes "それに私は今、";
		mes "恋愛なんてできません。";
		mes "^0000cdちょっとした事情がありまして^000000。";
		next;
		menu "わかりました",-;
		mes "[メイド]";
		mes "はい、本当に申し訳ありません。";
		next;
		menu "名前だけでも聞いていいかな？",-;
		mes "[メイド]";
		mes "メド……";
		mes "いえ、^0000cdメリー^000000です。";
		set EP16_4QUE,15;
		delquest 14488;
		setquest 14489;
		close;
	case 15:
		mes "[メイド]";
		mes "ユルゲン様には";
		mes "お伝えいただけたでしょうか。";
		mes "気分を害さないようにお願いします。";
		close;
	case 16:
		if(countitem(6927) < 1 || countitem(748) < 1) {
			mes "[メイド]";
			mes "ユルゲン様には";
			mes "お伝えいただけたでしょうか。";
			mes "気分を害さないようにお願いします。";
			close;
		}
		emotion 7;
		mes "[メリー]";
		mes "だーもう！";
		mes "いつ終わるんだよ、これ！";
		mes "帰ってきたら";
		mes "タダじゃおかないぞマジで！";
		next;
		menu "どうしたの？",-;
		mes "[メリー]";
		mes "ああ！　いいえ！";
		mes "またいらしたんですね。";
		mes "ユルゲン様からの伝言ですか？";
		next;
		menu "ユルゲンの想いを伝えに来た",-;
		mes "[メリー]";
		mes "申し訳ありませんが";
		mes "お断りさせていただきます。";
		mes "でも本当に綺麗ですね。";
		mes "石の中に水がはいってるんですか？";
		next;
		menu "ユルゲンからの愛の表現",-;
		mes "[メリー]";
		mes "うーん。";
		mes "本当にダメなんですけどね。";
		mes "……うーん、話していいのかな。";
		mes "僕の秘密を……";
		next;
		menu "秘密？",-;
		mes "[メリー]";
		mes "秘密中の秘密です。";
		mes "絶対に知られたらダメなんです。";
		next;
		mes "[メリー]";
		mes "はあ、冒険者様だけには";
		mes "話しますけど、";
		mes "ここで働いていたメイドは";
		mes "^0000cd姉^000000です。";
		mes "多分、冒険者様が知っていた人は";
		mes "姉の方です。";
		next;
		menu "なるほど、姉妹だったのか",-;
		mes "[メリー]";
		mes "姉妹だったらいいんですけど。";
		mes "^0000cd僕は弟で男^000000なんです。";
		next;
		emotion 23,"";
		menu "弟？男？",-;
		mes "[メリー]";
		mes "はあ……";
		mes "これには深いわけがありまして……";
		mes "好きでこんな服を着ているのでは";
		mes "ないんです。";
		next;
		mes "[メリー]";
		mes "姉はこの前の事件で";
		mes "傷心してしまい";
		mes "もうこんな仕事はしたくないと";
		mes "夜逃げしてしまったのです。";
		next;
		emotion 54;
		mes "[メリー]";
		mes "仕方なく王宮のメイド長に";
		mes "連絡したのですが、";
		mes "契約の問題もあって";
		mes "^0000cd代わりに仕事をする人を連れてくれば^000000";
		mes "目を瞑ると言ったのです。";
		next;
		mes "[メリー]";
		mes "そうでないと、";
		mes "契約上に明記されている";
		mes "^0000cd契約不履行による賠償^000000を";
		mes "家族が払わなければならないと。";
		next;
		mes "[メリー]";
		mes "そこで僕が代わりに";
		mes "働くといったのですが、";
		mes "男の従士は多いので";
		mes "ダメだと言われました。";
		next;
		mes "[メリー]";
		mes "そこを何とかしてもらったのが";
		mes "キッチン手伝いと掃除をするために";
		mes "^0000cdメイドの人手が必要^000000";
		mes "と言われました。";
		next;
		mes "[メリー]";
		mes "必死にメイドの仕事をする人を";
		mes "探しました。";
		next;
		mes "[メリー]";
		mes "でも王宮での祝宴は人手不足だったので";
		mes "メイドの仕事を出来る方は";
		mes "既に王宮に雇われていて";
		mes "姉の代わりになってくれるような";
		mes "女性はいませんでした。";
		next;
		mes "[メリー]";
		mes "そして母と相談し、";
		mes "姉と顔も見分けがつかない僕が";
		mes "かつらをつけて";
		mes "^0000cd姉のふりをして働く事^000000になりました。";
		mes "キッチンの仕事ばかりだったので";
		mes "人目に付く事もありませんし。";
		next;
		menu "気付かなかった……",-;
		mes "[メリー]";
		mes "僕と^0000cd姉は双子でそっくり^000000なので。";
		mes "誰も気づきませんでした。";
		mes "冒険者様もそうでしょう？";
		next;
		menu "ユルゲンになんと言えば……",-;
		emotion 20;
		mes "[メリー]";
		mes "事情はともあれ……";
		mes "可哀そうですね。";
		mes "^0000cd生まれて初めて惚れたのが偽者^000000";
		mes "だなんて。";
		next;
		mes "[メリー]";
		mes "良い物ばかり見ていた人は";
		mes "それに見合った目線を持ってると";
		mes "思っていましたが、";
		mes "そうでもないようですね。";
		next;
		switch(select("恋は盲目ってことかな","男でもいいじゃない")) {
		case 1:
			mes "[メリー]";
			mes "うーん、まいりました。";
			next;
			break;
		case 2:
			mes "[メリー]";
			mes "うんうん、男同士でもいいですよね。";
			mes "僕もそう思います。";
			mes "ただし、僕以外でお願いします！";
			next;
			break;
		}
		menu "ユルゲンに全部伝えるしかないか",-;
		emotion 23;
		mes "[メリー]";
		mes "いや！　ダメですよ！";
		mes "知ってるのは冒険者様だけですから！";
		mes "今正体がばれてしまうと";
		mes "^0000cdいろいろとマズい^000000のです。";
		mes "僕には賠償金が払えません。";
		next;
		mes "[メリー]";
		mes "姉には何とか帰ってくるように";
		mes "連絡をしていますが、";
		mes "なかなか連絡が付かないようです。";
		mes "祝宴が終わるまでだけでも";
		mes "秘密にして貰えませんか？";
		next;
		menu "ユルゲンをだます事になる",-;
		mes "[メリー]";
		mes "それは本当に申し訳なく思います。";
		mes "ですがこの仕事には";
		mes "家族の生計がかかっているのです。";
		next;
		mes "[メリー]";
		mes "タダでさえこんな服を着て、";
		mes "こんな仕事までしているのです。";
		mes "可哀そうだと思いませんか……？";
		next;
		menu "返事を貰えなかったと伝える事にする",-;
		mes "[メリー]";
		mes "本当ですか？";
		mes "それじゃ、とりあえず";
		mes "プレゼントは受け取っておいて";
		mes "祝宴最後の日にお返しします。";
		next;
		mes "[メリー]";
		mes "受け取らないと";
		mes "また冒険者様を追い返す事に";
		mes "なりそうですから。";
		mes "そうですね、";
		mes "僕も掃除区域を変えてもらって";
		mes "出会わないように注意します。";
		next;
		menu "了解",-;
		mes "[メリー]";
		mes "ありがとうございます。";
		mes "それではお願いします。";
		delitem 6927,1;
		delitem 748,1;
		set EP16_4QUE,17;
		delquest 14490;
		setquest 14491;
		close;
	case 17:
		mes "[メリー]";
		mes "ユルゲン様には";
		mes "伝えていただけましたか？";
		mes "はあ……";
		mes "いつまで続くのでしょうか。";
		next;
		mes "[メリー]";
		mes "いっその事";
		mes "僕も夜逃げしようかな……";
		close;
	case 18:
		mes "[メリー]";
		mes "王子様には伝えていただけましたか？";
		mes "もう諦めていただけると";
		mes "いいんですが……";
		close;
	default:
		mes "[メイド]";
		mes "フフフ～ン♪";
		mes "お掃除、お掃除～♪";
		mes "めんどくさいね～♪";
		close;
	}
}

prt_cas.gat,339,212,5	script	暗く湿った壁#ep16wig	111,7,7,{
	if(EP16_4QUE == 5) {
		if(!checkquest(14481)) {
			mes "[ポリンたわし]";
			mes "汝、臭く汚い場所にて";
			mes "我を呼び覚ましたのは人間か？";
			mes "深き眠りより呼び覚ました罪は";
			mes "掃除で償うべし。";
			next;
			mes "[ポリンたわし]";
			mes "我はこのたわしに封印されし";
			mes "掃除の神なり。";
			mes "我に再度安息の眠りをもたらすため、";
			mes "この場所を清掃せよ。";
			next;
			mes "[ポリンたわし]";
			mes "この場所に戯れる汚物は";
			mes "^0000cdカビの群生^000000なり。";
			mes "その同族と神聖なる水にて";
			mes "清掃がなされるだろう。";
			next;
			mes "[ポリンたわし]";
			mes "まずは^0000cdカビの粉1個と聖水1個^000000を";
			mes "求めるべし。";
			setquest 14481;
			close;
		}
		if(countitem(7001) < 1 || countitem(523) < 1) {
			mes "[ポリンたわし]";
			mes "汝、人間よ。";
			mes "準備は徹底して行うべし。";
			mes "まずは^0000cdカビの粉1個と聖水1個^000000を";
			mes "求めるべし。";
			next;
			mes "[ポリンたわし]";
			mes "求める物集まらば、";
			mes "清掃の資格を持つ者と認めん。";
			mes "汝、人間よ。";
			mes "準備は徹底して行うべし。";
			close;
		}
		mes "[ポリンたわし]";
		mes "カビの粉と聖水を持つものよ、";
		mes "カビの群生を消し去らん。";
		next;
		mes "[ポリンたわし]";
		mes "カビの粉をカビの群生にふりかけ、";
		mes "たわしを回しながら";
		mes "押し付けるべし。";
		next;
		mes "[ポリンたわし]";
		mes "その後、聖水をふりかけ、";
		mes "たわしでこねるように";
		mes "混ぜるべし。";
		next;
		mes "[ポリンたわし]";
		mes "そして次のように清掃行うべし。";
		next;
		mes "[ポリンたわし]";
		mes "繊細に1回はたき、";
		mes "3回強く叩くべし。";
		mes "聖水とカビの粉が";
		mes "混ざるようにせよ。";
		next;
		mes "[ポリンたわし]";
		mes "次に10回押しこみ、";
		mes "5回時計回しに強くこするべし。";
		next;
		progressbar 3;
		misceffect 78;
		mes "[ポリンたわし]";
		mes "感心した。";
		mes "まれに見る清掃だった。";
		mes "ポリンたわし生、";
		mes "一点の曇りなし。";
		next;
		mes "[ポリンたわし]";
		mes "我の成すべき事";
		mes "成しとげ成仏せん。";
		mes "汝、人間よ。";
		mes "天晴れであった。";
		misceffect 66,"";
		delitem 6928,1;
		delitem 7001,1;
		delitem 523,1;
		delquest 14481;
		delquest 73062;
		setquest 73063;
		set EP16_4QUE,6;
		close;
	}
	if(EP16_4QUE >= 6) {
		mes "[綺麗になった壁]";
		mes "綺麗になった壁を見ると";
		mes "一緒に掃除をした";
		mes "むすっとしたポリンたわしを";
		mes "思い出す。";
		close;
	}
	end;
OnTouch:
	if(EP16_4QUE == 5) {
		if(!checkquest(14481)) {
			misceffect 58;
			mes "[ポリンたわし]";
			mes "汝、臭く汚い場所にて";
			mes "我を呼び覚ましたのは人間か？";
			mes "深き眠りより呼び覚ました罪は";
			mes "掃除で償うべし。";
			next;
			mes "[ポリンたわし]";
			mes "我はこのたわしに封印されし";
			mes "掃除の神なり。";
			mes "我に再度安息の眠りをもたらすため、";
			mes "この場所を清掃せよ。";
			next;
			mes "[ポリンたわし]";
			mes "この場所に戯れる汚物は";
			mes "^0000cdカビの群生^000000なり。";
			mes "その同族と神聖なる水にて";
			mes "清掃がなされるだろう。";
			next;
			mes "[ポリンたわし]";
			mes "まずは^0000cdカビの粉1個と聖水1個^000000を";
			mes "求めるべし。";
			setquest 14481;
			close;
		}
	}
	end;
}

prt_cas.gat,339,198,5	script	べとべとした壁#ep16wig	111,7,7,{
	if(EP16_4QUE == 6) {
		if(!checkquest(14480)) {
			mes "[ポリンたわし]";
			mes "うーん！　よく寝た！";
			mes "君があの^0000cdべとべとした油汚れ^000000に";
			mes "僕を案内したのかい？";
			next;
			mes "[ポリンたわし]";
			mes "始めまして！";
			mes "僕はこのたわしに住んでいる";
			mes "掃除の妖精さ！";
			mes "僕と一緒に掃除をしてくれる人を";
			mes "待っていたんだ！";
			next;
			mes "[ポリンたわし]";
			mes "やっと起きる事ができたよ！";
			mes "それじゃ僕と一緒に";
			mes "楽しく掃除をしよう！";
			next;
			mes "[ポリンたわし]";
			mes "油汚れは僕の得意分野さ！";
			mes "今日もはりきっちゃうよ！";
			next;
			mes "[ポリンたわし]";
			mes "この油汚れなら……";
			mes "^0000cdオレンジとアルコールを混ぜたもの^000000が";
			mes "効果があるよ！";
			mes "まずは^0000cdオレンジ1個とアルコール1個^000000を";
			mes "準備しよう！";
			setquest 14480;
			close;
		}
		if(countitem(582) < 1 || countitem(970) < 1) {
			mes "[ポリンたわし]";
			mes "まだ掃除に必要なものが";
			mes "揃ってないよ！";
			mes "まずは^0000cdオレンジ1個とアルコール1個^000000を";
			mes "準備しよう！";
			next;
			mes "[ポリンたわし]";
			mes "できるなら僕が準備したいけどさ、";
			mes "ほら。僕ってたわしでしょう？";
			mes "だからお願いね。";
			close;
		}
		mes "[ポリンたわし]";
		mes "どうやらオレンジとアルコールが";
		mes "準備できたようだね！";
		next;
		mes "[ポリンたわし]";
		mes "まずはその美味しそうな";
		mes "オレンジの皮を剥こう！";
		mes "そして皮はアルコールに";
		mes "漬けて置くんだ！";
		mes "オレンジの実は美味しくいただこうね！";
		next;
		mes "[ポリンたわし]";
		mes "さあ、もうそろそろ";
		mes "アルコールにオレンジの皮の";
		mes "成分が溶けたとはずさ！";
		mes "よく振って混ぜてみよう！";
		next;
		mes "[ポリンたわし]";
		mes "そしてそのアルコール混合物を";
		mes "油汚れに振りかけるんだ！";
		mes "パッパッとね。";
		next;
		mes "[ポリンたわし]";
		mes "最初はゆるーくたわしで";
		mes "回しながらこするんだ。";
		mes "ゆっくりね。";
		mes "だんだん強くこするんだ。";
		next;
		mes "[ポリンたわし]";
		mes "アルコール混合物を";
		mes "もう一度パッパッと振りかけてから";
		mes "腕が痛くない程度でこするんだ。";
		next;
		while(1) {
			progressbar 3;
			if(rand(5) != 0)	// 暫定
				break;
			mes "[ポリンたわし]";
			mes "うーん、ちょっとこするのが";
			mes "弱すぎたみたいだ。";
			mes "アルコール混合物を";
			mes "もう少し振りかけよう。";
			next;
			mes "[ポリンたわし]";
			mes "油汚れにアルコールが";
			mes "染み込むように最初は弱く";
			mes "そしてだんだん強くこすっていくんだ。";
			next;
			mes "[ポリンたわし]";
			mes "最初はゆるーくたわしで";
			mes "回しながらこするんだ。";
			mes "ゆっくりね。";
			mes "だんだん強くこするんだ。";
			next;
			mes "[ポリンたわし]";
			mes "アルコール混合物を";
			mes "もう一度パッパッと振りかけてから";
			mes "腕が痛くない程度でこするんだ。";
			next;
			continue;
		}
		misceffect 78;
		mes "[ポリンたわし]";
		mes "うわぁ！　本当に綺麗になったよ！";
		mes "それに爽やかなオレンジの香りが";
		mes "あたりに充満してるよ！";
		next;
		mes "[ポリンたわし]";
		mes "それじゃ名残惜しいけど";
		mes "これで僕の役目は終わりさ。";
		mes "掃除を終えた後に待つ運命だからね。";
		next;
		mes "[ポリンたわし]";
		mes "短い間だったけど、";
		mes "たわしの妖精としては充実できたよ！";
		mes "あーあ、今度は僕も君みたいな";
		mes "人間に生まれたい……な……ぁ……";
		misceffect 66,"";
		delitem 6928,1;
		delitem 582,1;
		delitem 970,1;
		delquest 14480;
		delquest 73063;
		setquest 73064;
		set EP16_4QUE,7;
		close;
	}
	if(EP16_4QUE >= 7) {
		mes "[綺麗になった壁]";
		mes "綺麗になった壁を見ると";
		mes "一緒に掃除をした";
		mes "優しかったポリンたわしを";
		mes "思い出す。";
		close;
	}
	end;
OnTouch:
	if(EP16_4QUE == 6) {
		if(!checkquest(14480)) {
			misceffect 58;
			mes "[ポリンたわし]";
			mes "うーん！　よく寝た！";
			mes "君があの^0000cdべとべとした油汚れ^000000に";
			mes "僕を案内したのかい？";
			next;
			mes "[ポリンたわし]";
			mes "始めまして！";
			mes "僕はこのたわしに住んでいる";
			mes "掃除の妖精さ！";
			mes "僕と一緒に掃除をしてくれる人を";
			mes "待っていたんだ！";
			next;
			mes "[ポリンたわし]";
			mes "やっと起きる事ができたよ！";
			mes "それじゃ僕と一緒に";
			mes "楽しく掃除をしよう！";
			next;
			mes "[ポリンたわし]";
			mes "油汚れは僕の得意分野さ！";
			mes "今日もはりきっちゃうよ！";
			next;
			mes "[ポリンたわし]";
			mes "この油汚れなら……";
			mes "^0000cdオレンジとアルコールを混ぜたもの^000000が";
			mes "効果があるよ！";
			mes "まずは^0000cdオレンジ1個とアルコール1個^000000を";
			mes "準備しよう！";
			setquest 14480;
			close;
		}
	}
	end;
}

prt_cas.gat,309,215,5	script	真っ黒な床#ep16wig	111,{
	if(EP16_4QUE == 7) {
		if(!checkquest(14482)) {
			mes "[ポリンたわし]";
			mes "あなたですか！";
			mes "今日の掃除担当は！";
			mes "お初にお目にかかります！";
			mes "自分はポリンたわしに封印された";
			mes "掃除担当曹長であります！";
			next;
			mes "[ポリンたわし]";
			mes "自分の指示に正しくついて";
			mes "これればどんなにキツイ汚れでも";
			mes "撃破する事ができるであります！";
			mes "心配無用であります！";
			next;
			mes "[ポリンたわし]";
			mes "本日の目標を確認したであります！";
			mes "床の上にこびりついた";
			mes "黒い物体であります！";
			mes "彼我戦力差は";
			mes "芳しくないのであります！";
			next;
			mes "[ポリンたわし]";
			mes "戦力差を埋めるために";
			mes "補給品が必要であります！";
			mes "目標殲滅のため、";
			mes "^0000cdきれいな砂1個とレモン1個^000000が";
			mes "必要であります！";
			next;
			mes "[ポリンたわし]";
			mes "掃除実施は補給品がそろい次第、";
			mes "実行するであります！";
			mes "補給品捜索を頼んだであります！";
			setquest 14482;
			close;
		}
		if(countitem(7043) < 1 || countitem(568) < 1) {
			mes "[ポリンたわし]";
			mes "補給品が";
			mes "まだ到着していないのであります！";
			mes "目標殲滅のため、";
			mes "^0000cdきれいな砂1個とレモン1個^000000が";
			mes "必要であります！";
			next;
			mes "[ポリンたわし]";
			mes "掃除実施は補給品がそろい次第、";
			mes "実行するであります！";
			mes "補給品の準備を頼んだであります！";
			close;
		}
		mes "[ポリンたわし]";
		mes "補給品の準備、よし！";
		mes "それでは清掃を開始するであります！";
		next;
		mes "[ポリンたわし]";
		mes "レモンを手でつぶすであります！";
		mes "レモン汁は床に振り撒くであります！";
		mes "きれいな砂はその上に";
		mes "振り掛けるであります！";
		mes "研磨作用が強くなるであります！";
		next;
		mes "[ポリンたわし]";
		mes "そして自分を力強く床に";
		mes "こすりつけるであります！";
		mes "床掃除は次のように";
		mes "こするのであります！";
		next;
		mes "[ポリンたわし]";
		mes "掃除は左から右へするのが";
		mes "定石であります！";
		mes "腕が棒になるくらいに";
		mes "強くこするのがコツであります！";
		next;
		while(1) {
			progressbar 3;
			if(rand(5) != 0)	// 暫定
				break;
			mes "[ポリンたわし]";
			mes "まだまだであります！";
			mes "そのような動きでは黒い物体は";
			mes "残滅できないのであります！";
			next;
			mes "[ポリンたわし]";
			mes "掃除は左から右へするのが";
			mes "定石であります！";
			mes "腕が棒になるくらいに";
			mes "強くこするのがコツであります！";
			next;
			continue;
		}
		misceffect 78;
		mes "[ポリンたわし]";
		mes "よろしい！";
		mes "最高であります！";
		mes "黒い物体の殲滅に成功したであります！";
		next;
		mes "[ポリンたわし]";
		mes "自分がいなくても";
		mes "もう大丈夫であります！";
		mes "そなたは立派な清掃兵であります！";
		next;
		mes "[ポリンたわし]";
		mes "これで自分も役目を果たしたので";
		mes "除隊できるであります！";
		mes "これにて解散！　であります！";
		misceffect 66,"";
		delitem 6928,1;
		delitem 7043,1;
		delitem 568,1;
		delquest 14482;
		delquest 14479;
		delquest 73064;
		setquest 14483;
		set EP16_4QUE,8;
		close;
	}
	if(EP16_4QUE >= 8) {
		mes "[輝く床]";
		mes "輝く床を見ていると";
		mes "軍人のようなポリンたわしを";
		mes "思い出す。";
		mes "メイドに掃除完了を知らせよう。";
		close;
	}
	end;
OnTouch:
	if(EP16_4QUE == 7) {
		if(!checkquest(14482)) {
			misceffect 58;
			mes "[ポリンたわし]";
			mes "あなたですか！";
			mes "今日の掃除担当は！";
			mes "お初にお目にかかります！";
			mes "自分はポリンたわしに封印された";
			mes "掃除担当曹長であります！";
			next;
			mes "[ポリンたわし]";
			mes "自分の指示に正しくついて";
			mes "これればどんなにキツイ汚れでも";
			mes "撃破する事ができるであります！";
			mes "心配無用であります！";
			next;
			mes "[ポリンたわし]";
			mes "本日の目標を確認したであります！";
			mes "床の上にこびりついた";
			mes "黒い物体であります！";
			mes "彼我戦力差は";
			mes "芳しくないのであります！";
			next;
			mes "[ポリンたわし]";
			mes "戦力差を埋めるために";
			mes "補給品が必要であります！";
			mes "目標殲滅のため、";
			mes "^0000cdきれいな砂1個とレモン1個^000000が";
			mes "必要であります！";
			next;
			mes "[ポリンたわし]";
			mes "掃除実施は補給品がそろい次第、";
			mes "実行するであります！";
			mes "補給品捜索を頼んだであります！";
			setquest 14482;
			close;
		}
	}
	end;
}

prontera.gat,52,88,5	script	家具配達員#ep16wig	52,{
	switch(EP16_4QUE) {
	case 9:
		mes "[家具配達員]";
		mes "ふう、今日も良く働いたぜ！";
		mes "さーて、夕飯は何かな～。";
		mes "確か温かいスープだったような……";
		next;
		menu "すいません",-;
		emotion 28;
		mes "[家具配達員]";
		mes "おっと！";
		mes "今日はもう店じまいですよ。";
		mes "急ぎの件でなければ";
		mes "明日また来て貰っても良いですか？";
		next;
		mes "[家具配達員]";
		mes "今日も良く働いて疲れてるんです。";
		mes "こういう日には";
		mes "ハーブの味つきカルビでも";
		mes "食いたいな……";
		next;
		menu "ウィグナー家の家具について",-;
		mes "[家具配達員]";
		mes "はい、どうしました？";
		mes "もしかして何か家具に問題でも？";
		mes "受け取り確認はしましたが……";
		next;
		mes "[家具配達員]";
		mes "もしかして追加の注文ですか？";
		mes "ウィグナー家はお得意さんなので";
		mes "何とかしたいのですが";
		mes "あの家具は特注でして";
		mes "すぐには配達できないんですよ。";
		emotion 54;
		next;
		menu "箱を見ませんでした？",-;
		mes "[家具配達員]";
		mes "家具配達時には特には……";
		mes "いや、ちょっと待てよ。";
		mes "確か……";
		next;
		mes "[家具配達員]";
		mes "ベッド近くのテーブルの上にあった";
		mes "^0000cd小さな箱^000000ですかね？";
		mes "特に派手な装飾はない箱。";
		next;
		menu "たぶん、そうです",-;
		mes "[家具配達員]";
		mes "思い出しました。";
		mes "飾り気はないので素朴な雰囲気ですが";
		mes "あれは巨匠の作品でしょう。";
		mes "使われた木材も高級なものでしたし、";
		mes "錠も気品が感じられるものでした。";
		next;
		mes "[家具配達員]";
		mes "いやー、あれはもう芸術品の域ですよ。";
		mes "家具を取り扱って結構経ちますが";
		mes "あれほどの物はそうそう";
		mes "見た事がないです。";
		next;
		menu "配達後も、箱はありましたか？",-;
		emotion 6;
		mes "[家具配達員]";
		mes "そりゃそうでしょう。";
		mes "箱が勝手に歩き回る訳でも……・";
		next;
		emotion 23;
		mes "[家具配達員]";
		mes "……もしかして私が疑われてます?!";
		mes "荷車にはそんな物は";
		mes "ありませんでしたよ！";
		next;
		menu "疑っているわけではありません",-;
		emotion 7;
		mes "[家具配達員]";
		mes "まあ、お偉いさんの事ですから";
		mes "何か無くなればとりあえず";
		mes "私のような下の者を疑うのでしょう。";
		mes "金が少ない物は貪欲で不道徳だと。";
		mes "偏見じゃないか。";
		next;
		emotion 7;
		mes "[家具配達員]";
		mes "はあ、";
		mes "そっちがそのつもりでなくても";
		mes "受け入れる側からは";
		mes "そうは聞こえないんですよ。";
		next;
		menu "あなただけではなくみんなに聞いている",-;
		emotion 32;
		mes "[家具配達員]";
		mes "ふう……";
		mes "あんたもお偉いさんの使いって事か。";
		mes "そうですね。それなら……";
		mes "(ギュルルルルル)";
		mes "うお、腹が減りすぎて……";
		mes "めまいが……";
		next;
		menu "食べ物はある？",-;
		mes "[家具配達員]";
		mes "そんなもので(ギュルルルル)";
		mes "私の気分が晴れる(グルルルルル)";
		mes "とでも(ギュルルルル)";
		mes "……ゴホン。";
		mes "それじゃ「ハーブの味つきカルビ」を。";
		next;
		menu "カルビはうまいですよね",-;
		mes "[家具配達員]";
		mes "そう、最高にうまい！";
		mes "^0000cdハーブの味つきカルビ1個^000000で";
		mes "手を打ちましょう！";
		emotion 29;
		delquest 14484;
		setquest 14485;
		set EP16_4QUE,10;
		close;
	case 10:
		if(countitem(12044) < 1) {
			mes "[家具配達員]";
			mes "持ってきましたか？";
			mes "（ギュルルルルルル）";
			mes "もう倒れそうです……";
			next;
			mes "[家具配達員]";
			mes "でもカルビの匂いがしませんね。";
			mes "^0000cdハーブの味つきカルビ1個^000000ですよ。";
			next;
			emotion 32;
			mes "[家具配達員]";
			mes "腹ペコで意識不明になる前に";
			mes "持ってきてください。";
			mes "（ギュルルルルル）";
			close;
		}
		mes "[家具配達員]";
		mes "もう来たんですか。";
		mes "（ギュルルル）";
		mes "腹が減って倒れる前に来たのは";
		mes "評価しますよ。";
		next;
		emotion 18;
		mes "[家具配達員]";
		mes "どれどれ、これはいい肉だ！";
		mes "早速焼かせて貰いましょう！";
		mes "なんて久しぶりなんだろ！";
		next;
		mes "[家具配達員]";
		mes "10年前に親父と食べた";
		mes "カルビを思い出す……";
		mes "親父ぃ……！";
		next;
		menu "箱の件",-;
		emotion 6;
		mes "[家具配達員]";
		mes "ああ、あの箱なら（もぐもぐ）";
		mes "城から出るときに（もぐもぐ）";
		mes "警備兵に荷車（もぐもぐ）……";
		next;
		mes "[家具配達員]";
		mes "げほげほ！";
		mes "ふー、喉に肉が詰まった。";
		mes "まあ、警備兵に荷車を";
		mes "確認して貰ったし";
		mes "警備兵に聞いてみてくれ。";
		next;
		mes "[家具配達員]";
		mes "ああ、そうだ。";
		mes "ところで（もぐもぐ）";
		next;
		mes "[家具配達員]";
		mes "城に出入りしているうちに";
		mes "小耳に挟んだのだが、";
		mes "ウィグナー家の長女に関して";
		mes "変な噂が立っているらしい。";
		next;
		menu "噂？",-;
		emotion 20;
		mes "[家具配達員]";
		mes "火の無いところに煙は立たぬ、";
		mes "とも言うじゃないか。";
		mes "何となく陰険な雰囲気で";
		mes "何かをたくらんでいそうだと。";
		next;
		mes "[家具配達員]";
		mes "下の者である私が";
		mes "こんな話を聞いたという事は";
		mes "秘密にしてくれよ。";
		next;
		menu "カトリンの自作自演だと？",-;
		mes "[家具配達員]";
		mes "だから噂話だよ。";
		mes "^0000cd気になるなら確認してみるといい。^000000";
		mes "とにかく、あの箱は";
		mes "私が部屋から出るまでは";
		mes "ずっとテーブルの上にあったよ。";
		delitem 12044,1;
		delquest 14485;
		setquest 14486;
		set EP16_4QUE,11;
		next;
		mes "‐メイドも配達人も";
		mes "　カトリンを疑っているようだ。";
		mes "　一度ユルゲンに報告しよう‐";
		next;
		mes "‐ユルゲンのところに向かおうかな？‐";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐ユルゲンに会いに向かった‐";
		close2;
		warp "prt_cas_q.gat",90,15;
		end;
	case 11:
		mes "[家具配達員]";
		mes "何か忘れ物ですか？";
		mes "城の警備兵には";
		mes "もう聞いてみましたか？";
		next;
		mes "[家具配達員]";
		mes "それともまたカルビを";
		mes "もらえるんですかね？";
		mes "あれは美味かった。";
		next;
		if(select("向かわない","向かう") == 1) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐ユルゲンに会いに向かった‐";
		close2;
		warp "prt_cas_q.gat",90,15;
		end;
	default:
		mes "[家具配達員]";
		mes "ふう、これで今日の仕事は終わりだ！";
		mes "明日の準備も今のうちにしておこう。";
		next;
		mes "[家具配達員]";
		mes "あと、腹も減ったし";
		mes "なにか食べるとするかな。";
		close;
	}
}

prt_cas_q.gat,150,122,4	script	恋する女性#ep16wig	71,{
	switch(rand(2)) {
	case 0:
		emotion 14;
		mes "[恋する女性]";
		mes "ユルゲン様はいつお出ましに";
		mes "なるのですか？";
		mes "ああ、待ち遠しいです！";
		next;
		mes "[お嬢様な女性]";
		mes "私は23番目……";
		next;
		mes "[一途な女性]";
		mes "今日中にはお会いできるかしら？";
		next;
		mes "[端整な女性]";
		mes "23番目なら今日中は";
		mes "難しいかもしれませんわ。";
		close;
	case 1:
		mes "[恋する女性]";
		mes "整理券はもらったものの……";
		mes "いつまで待てばいいのかしら。";
		next;
		mes "[お嬢様な女性]";
		mes "とりあえずティータイムはいかが？";
		next;
		mes "[一途な女性]";
		mes "少し休みますか？";
		next;
		mes "[端整な女性]";
		mes "ちょっと、中から何か聞こえません？";
		close;
	}
}

prt_cas_q.gat,148,122,4	script	一途な女性#ep16wig	68,{
	switch(rand(2)) {
	case 0:
		emotion 6,;
		mes "[一途な女性]";
		mes "ユルゲン様はみんなのものよ！";
		mes "誰かの独り占めになった";
		mes "ユルゲン様なんて見たくないの！";
		next;
		mes "[お嬢様な女性]";
		mes "そうよ！　みんなのものよ！";
		next;
		mes "[恋する女性]";
		mes "私も！　私も！";
		next;
		mes "[端整な女性]";
		mes "あら、私はそうは思いませんけど？";
		close;
	case 1:
		mes "[一途な女性]";
		mes "ユルゲン様を独り占めするのは";
		mes "天が許しても私が許しません！";
		next;
		mes "[お嬢様な女性]";
		mes "私も許さないわ！";
		next;
		mes "[恋する女性]";
		mes "正直になりなさい。";
		mes "それが私なら私は私を許しますわ。";
		next;
		mes "[端整な女性]";
		mes "天が許したなら";
		mes "いいんじゃなくて？";
		close;
	}
}

prt_cas_q.gat,148,117,7	script	お嬢様な女性#ep16wig	91,{
	switch(rand(2)) {
	case 0:
		mes "[お嬢様な女性]";
		mes "ユルゲン様はみんなに";
		mes "平等にしてくれるのだから、";
		mes "私たちもフェアに";
		mes "抜け駆けはしないと";
		mes "言ったでしょう！";
		mes "さあ、自首なさい！";
		next;
		mes "[一途な女性]";
		mes "それで自首するようなら";
		mes "初めから入ったりしないのでは？";
		next;
		mes "[恋する女性]";
		mes "ユルゲン様はなぜ";
		mes "一人を選んでは";
		mes "くださらないのかしら……";
		next;
		mes "[端整な女性]";
		mes "ところでユルゲン様は";
		mes "いついらっしゃるの？";
		close;
	case 1:
		emotion 7;
		mes "[お嬢様な女性]";
		mes "いったいどなた？";
		mes "昨日、カトリン様に媚を売ろうと";
		mes "うろついていたのは！";
		mes "抜け駆けはしない約束でしょう！";
		next;
		mes "[一途な女性]";
		mes "私じゃありません！";
		mes "そんな目で見ないでくださいな！";
		next;
		mes "[恋する女性]";
		mes "まあ！　いったい誰がそんな！";
		next;
		mes "[端整な女性]";
		mes "カトリン様が優しすぎるのに";
		mes "付け入ったのだわ。";
		close;
	}
}

prt_cas_q.gat,150,117,7	script	端整な女性#ep16wig	90,{
	switch(rand(2)) {
	case 0:
		mes "[端整な女性]";
		mes "そこのあなた！";
		mes "初めて来たならちょっとは";
		mes "周りの雰囲気を読みなさいよ！";
		next;
		mes "[お嬢様な女性]";
		mes "そうよ！";
		mes "迷惑だわ！";
		next;
		mes "[恋する女性]";
		mes "最初の3か月は";
		mes "遠くから見るだけという";
		mes "ルールを知りませんの？";
		next;
		mes "[一途な女性]";
		mes "ここで列を整理していた人は";
		mes "どこに行ったのかしらね。";
		close;
	case 1:
		emotion 7;
		mes "[端整な女性]";
		mes "ちょっと！　押さないでよ！";
		mes "順番を守りなさい！";
		next;
		mes "[お嬢様な女性]";
		mes "あら、";
		mes "初めての人は自己申告からよ。";
		next;
		mes "[恋する女性]";
		mes "列に並ぶのは";
		mes "基本中の基本ですわよ。";
		next;
		mes "[一途な女性]";
		mes "皆さん。";
		mes "お優しいのね。";
		close;
	}
}

prt_cas_q.gat,146,121,4	script	田舎者の男性#ep16wig	59,{
	emotion 28;
	mes "[田舎者の男性]";
	mes "ここの女性たちは怖いです……";
	mes "暴言は吐くし、列は乱すし……";
	next;
	switch(select("もう帰ったら？","がんばれ")) {
	case 1:
		emotion 7;
		mes "[田舎者の男性]";
		mes "もう整理券はもらってますし";
		mes "帰るに帰れませんよ。";
		mes "少なくともユルゲン様に会うまでは！";
		next;
		emotion 14;
		mes "[田舎者の男性]";
		mes "本物のユルゲン様を見るまでは";
		mes "帰りません！";
		mes "ええ！　帰りません！";
		mes "何のために田舎から";
		mes "出てきたと……";
		close;
	case 2:
		emotion 14;
		mes "[田舎者の男性]";
		mes "そうです！";
		mes "すべてはユルゲン様に";
		mes "お会いするため!!";
		mes "女性の怖さなんて";
		mes "なんぼでもないです！";
		close;
	}
}

prt_cas_q.gat,153,123,3	script	王宮警備兵#ep16wig01	105,{
	switch(rand(3)) {
	case 0:
		mes "[王宮警備兵]";
		mes "ご覧になればわかると思いますが、";
		mes "他の家門にはこうして";
		mes "王宮警備兵が目立つように";
		mes "配属されていません。";
		next;
		mes "[王宮警備兵]";
		mes "ウィグナー家の部屋には";
		mes "侵入する人が絶えませんので";
		mes "至急、手配されたのです。";
		close;
	case 1:
		emotion 25;
		mes "[王宮警備兵]";
		mes "そちらの方！";
		mes "押さないでください！";
		mes "整理券の番号順で";
		mes "お並びください！";
		next;
		mes "[王宮警備兵]";
		mes "昨日も押し合いで倒れた方が";
		mes "病院に搬送されました！";
		mes "事故を起こさないために";
		mes "ご協力をお願いします！";
		close;
	case 2:
		emotion 54;
		mes "[王宮警備兵]";
		mes "今日もきついのです。";
		mes "女性の力がこれほど強いとは";
		mes "思いませんでした。";
		next;
		mes "[王宮警備兵]";
		mes "昨日がこの場所での";
		mes "初勤務でしたが、";
		mes "なぜ先輩方が辞めたのか";
		mes "やっと解りました。";
		mes "綺麗な女性を見れると聞いて";
		mes "志願したのが運の尽きでした。";
		close;
	}
}

prt_cas_q.gat,153,116,1	script	王宮警備兵#ep16wig02	105,{
	switch(rand(3)) {
	case 0:
		emotion 7;
		mes "[王宮警備兵]";
		mes "うん？　ちょっとそこの君！";
		mes "この前、部屋に侵入した者だな！";
		mes "待て！";
		next;
		mes "[王宮警備兵]";
		mes "くーっ、また逃げられた。";
		mes "なんて逃げ足だ。";
		mes "妹はこんなところに";
		mes "来てないだろうな。";
		close;
	case 1:
		emotion 28;
		mes "[王宮警備兵]";
		mes "最初に王宮警備兵になった時は";
		mes "感動すらしましたが、";
		mes "今の仕事は列整理係なのか";
		mes "王宮警備なのかすらわかりません。";
		next;
		emotion 6;
		mes "[王宮警備兵]";
		mes "ちょっと！";
		mes "ちゃんと並んでください！";
		mes "通路は通れるように！";
		mes "整理券を持たない方は";
		mes "後ろに並んでください！";
		close;
	case 2:
		emotion 36;
		mes "[王宮警備兵]";
		mes "そこ！　静かにしてください！";
		mes "うるさくてユルゲン様が";
		mes "お休みになれないとのことです！";
		next;
		mes "[王宮警備兵]";
		mes "これは全てユルゲン様のためです！";
		mes "ユルゲン様が寝不足になったら";
		mes "ファンの皆さんも悲しいでしょう！";
		close;
	}
}

prt_cas_q.gat,95,11,4	script(HIDDEN)	一途な女性#ep16wig01	68,{
	mes "[一途な女性]";
	mes "ユルゲン様は私と";
	mes "一緒になるのよ……!!";
	close;
OnStart:
	initnpctimer;
	hideoffnpc "一途な女性#ep16wig01";
	unittalk "一途な女性 : キャー！　ユルゲン様!!　ユルゲン様!!　愛してます！　こっちを見て！　キャー!!";
	emotion 30,"一途な女性#ep16wig01";
	end;
OnTimer22000:
	unittalk getnpcid(0,"ユルゲン・ウィグナー#ep16wig"),"ユルゲン・ウィグナー : ああ、あなたはこの前の……なにか御用ですか？";
	end;
OnTimer24000:
	unittalk "一途な女性 : ユルゲン様！　私と一緒になりましょう！　永遠に!!";
	misceffect 343,"一途な女性#ep16wig01";
	end;
OnTimer26000:
	unittalk getnpcid(0,"ユルゲン・ウィグナー#ep16wig"),"ユルゲン・ウィグナー : うーん、それは困りますね。";
	end;
OnTimer28000:
	hideoffnpc "王宮警備兵#ep16wig03";
	hideoffnpc "王宮警備兵#ep16wig04";
	unittalk getnpcid(0,"王宮警備兵#ep16wig03"),"王宮警備兵 : ピーッ！　またこいつだ！　捕まえろ！";
	end;
OnTimer30000:
	unittalk getnpcid(0,"王宮警備兵#ep16wig04"),"王宮警備兵 : 毎回毎回、いったいどこから入ってくるんだ！";
	end;
OnTimer32000:
	unittalk getnpcid(0,"王宮警備兵#ep16wig03"),"王宮警備兵 : つまみ出せ！";
	end;
OnTimer34000:
	unittalk "一途な女性 : あぁんユルゲン様！　また来ます！";
	end;
OnTimer36000:
	hideonnpc "一途な女性#ep16wig01";
	hideonnpc "王宮警備兵#ep16wig03";
	hideonnpc "王宮警備兵#ep16wig04";
	end;
OnTimer200000:
	stopnpctimer;
	end;
}

prt_cas_q.gat,94,12,4	script(HIDDEN)	王宮警備兵#ep16wig03	105,{}

prt_cas_q.gat,95,12,4	script(HIDDEN)	王宮警備兵#ep16wig04	105,{}

prt_cas_q.gat,98,23,1	script(HIDDEN)	田舎者の男性#ep16wig01	59,{
	mes "[田舎者の男性]";
	mes "ユルゲン様と握手もできず……";
	mes "あちっ！";
	close;
OnStart:
	initnpctimer;
	hideoffnpc "田舎者の男性#ep16wig01";
	unittalk "田舎者の男性 : ユルゲ……あちーっ!!　あち!!";
	end;
OnTimer22000:
	unittalk "田舎者の男性 : なんでこんなところ出るんだ!?";
	end;
OnTimer24000:
	unittalk "田舎者の男性 : あの女！　変な場所を教えやがって！";
	end;
OnTimer26000:
	unittalk "田舎者の男性 : うあっちいい！";
	unittalk getnpcid(0,"ユルゲン・ウィグナー#ep16wig"),"ユルゲン・ウィグナー : 男性のファンの方なのはわかりますが、私に会うのにこのようなパフォーマンスは必要ありませんよ。でも、すごいですね。";
	end;
OnTimer28000:
	unittalk "田舎者の男性 : あっユルゲンさ……あち！　助け！　ユルゲン様！　握手！";
	end;
OnTimer31000:
	hideoffnpc "王宮警備兵#ep16wig05";
	hideoffnpc "王宮警備兵#ep16wig06";
	unittalk getnpcid(0,"王宮警備兵#ep16wig05"),"王宮警備兵 : なにごとですか！";
	end;
OnTimer33000:
	unittalk getnpcid(0,"王宮警備兵#ep16wig06"),"王宮警備兵 : んん？　なんでこんなところから人が……とりあえず確保！";
	end;
OnTimer35000:
	unittalk getnpcid(0,"王宮警備兵#ep16wig05"),"王宮警備兵 : まったく世の中には変な人が多い！";
	end;
OnTimer37000:
	unittalk getnpcid(0,"王宮警備兵#ep16wig06"),"王宮警備兵 : つまみ出せ！";
	end;
OnTimer39000:
	unittalk "田舎者の男性 : あああ！ ユルゲン様ぁ";
	end;
OnTimer41000:
	unittalk getnpcid(0,"ユルゲン・ウィグナー#ep16wig"),"ユルゲン・ウィグナー : 火傷はあとが残らないようしっかり冷やすんだよ～";
	end;
OnTimer43000:
	hideonnpc "田舎者の男性#ep16wig01";
	hideonnpc "王宮警備兵#ep16wig05";
	hideonnpc "王宮警備兵#ep16wig06";
	end;
OnTimer200000:
	stopnpctimer;
	end;
}

prt_cas_q.gat,98,20,7	script(HIDDEN)	王宮警備兵#ep16wig05	105,{}

prt_cas_q.gat,96,22,7	script(HIDDEN)	王宮警備兵#ep16wig06	105,{}

comodo.gat,36,210,5	script(CLOAKED)	ウィグナー家の使いの者#ep16wig	99,{
	mes "[ウィグナー家の使いの者]";
	mes "ユルゲン様のいる場所に";
	mes "戻られますか？";
	mes "ご案内いたしますよ。";
	next;
	if(select("向かわない","向かう")==1) {
		mes "[ウィグナー家の使いの者]";
		mes "わかりました。";
		close;
	}
	mes "[ウィグナー家の使いの者]";
	mes "ご案内いたします。";
	close2;
	warp "prt_cas_q.gat",90,15;
	end;
}

comodo.gat,36,210,0	script	#wig_warp	139,10,10,{
OnTouch:
	if(EP16_4QUE >= 12)
		cloakoffnpc "ウィグナー家の使いの者#ep16wig";
	end;
}

prt_cas.gat,107,225,5	script	アイザック・ウィグナー#ep16wig01	10126,3,3,{
	cutin "16isa.bmp",1;
	mes "[アイザック]";
	mes "あははは！";
	mes "その表情を見れなかったのは";
	mes "残念ですね！";
	mes "次もそのような場があれば";
	mes "ぜひ私もお招きください。";
	next;
	cutin "16isa.bmp",255;
	mes "[イザベラ]";
	mes "あら、アイザック様は";
	mes "いつもお忙しくて";
	mes "お招きしても";
	mes "いらっしゃることが";
	mes "できませんでしょう。";
	next;
	mes "[ベアトリス]";
	mes "そうですわ！";
	mes "今のプロンテラで、一番忙しい方の";
	mes "三本の指に入るでしょう。";
	next;
	mes "[ソフィア]";
	mes "ブライアンも";
	mes "アイザック様と一緒。";
	mes "帰ってくるのが";
	mes "いつも深夜ですの。";
	mes "憎らしいですわ。";
	next;
	mes "[ブライアン]";
	mes "いや、それは……";
	next;
	cutin "16isa.bmp",1;
	mes "[アイザック]";
	mes "おっと！　これはこれは";
	mes "不本意ながら";
	mes "ソフィア様の楽しい時間を";
	mes "奪ってしまってましたか！";
	mes "どうかお許しください。";
	next;
	mes "[アイザック]";
	mes "ですがもうしばらくだけ、";
	mes "ブライアン様をお貸しいただけますか？";
	mes "今の重要な案件が終わったら、";
	mes "すぐソフィア様のために";
	mes "全力を尽くすよう、";
	mes "ブライアン様にお願いしましょう！";
	next;
	cutin "16isa.bmp",255;
	mes "[ソフィア]";
	mes "あら、その約束、";
	mes "守っていただきますわよ！";
	next;
	cutin "16isa.bmp",1;
	mes "[アイザック]";
	mes "このアイザック・ウィグナーの";
	mes "名に懸けて。";
	next;
	mes "[イザベラ]";
	mes "その時は、私の招待も";
	mes "お受けになってくださいね。";
	mes "楽しみにしていますわ。";
	cutin "16isa.bmp",255;
	close;
OnTouch:
	unittalk "アイザック : あははは！　その表情を見れなかったのは残念ですね！",1;
	end;
}

prt_cas.gat,105,221,1	script	イザベラ#ep16wig	90,{
	mes "[イザベラ]";
	mes "私は祝宴が大好きです！";
	mes "特に王宮の祝宴は華やかで";
	mes "きらびやかで……！";
	close;
}

prt_cas.gat,105,224,4	script	ベアトリス#ep16wig	91,{
	mes "[ベアトリス]";
	mes "このような祝宴が開かれると";
	mes "女性はまず他の女性を";
	mes "鋭くチェックしますの。";
	next;
	mes "[ベアトリス]";
	mes "飾りや髪型、ドレスの色。";
	mes "宝石の大きさやカットの形。";
	mes "それこそ猛獣よりもぎらぎらとね。";
	close;
}

prt_cas.gat,107,222,1	script	ソフィア#ep16wig	71,{
	mes "[ソフィア]";
	mes "久しぶりの王宮はいいですわね。";
	mes "懐かしい顔もいっぱい。";
	mes "でも……";
	next;
	mes "[ソフィア]";
	mes "みなさん、綺麗に着飾っていて";
	mes "とても輝いていますの。";
	mes "　";
	mes "私はもう色あせたかしら……";
	next;
	mes "[ブライアン]";
	mes "そんなことない！";
	mes "君が一番綺麗だよ！";
	mes "だから僕の目には";
	mes "君しか映らないんだ。";
	next;
	mes "[ソフィア]";
	mes "あら、お上手だこと……";
	close;
}

prt_cas.gat,108,223,3	script	ブライアン#ep16wig	995,{
	mes "[ブライアン]";
	mes "今日はいきなり消えないでくれよ。";
	mes "とても不安になるんだ。";
	next;
	mes "[ソフィア]";
	mes "あら！　私も懐かしい方と";
	mes "お話をしたいですわ。";
	mes "あなたも知り合いの方と";
	mes "楽しんでらっしゃいな。";
	next;
	mes "[ブライアン]";
	mes "……はぁ、";
	mes "僕の知り合いは";
	mes "毎回仕事の話しかしないのだよ。";
	mes "こんな場所でまで";
	mes "したくないのに。";
	next;
	mes "[ソフィア]";
	mes "それじゃ私に";
	mes "ついていらっしゃいな。";
	next;
	mes "[ブライアン]";
	mes "……それもちょっと";
	mes "　";
	mes "女性が多い席は……";
	next;
	mes "[ソフィア]";
	mes "まあ！";
	mes "わがままね。";
	mes "私にだけなら許しますけど！";
	close;
}

prt_cas.gat,84,225,4	script	ルヴィエル・ウィグナー#ep16wig01	10132,{
	mes "[ルヴィエル]";
	mes "マクシーミリアン様、";
	mes "ご機嫌よろしゅうございますか？";
	mes "ヴォルフ様の話を";
	mes "我が息子、アイザックから";
	mes "度々聞いています。";
	next;
	mes "[マクシーミリアン]";
	mes "おかげさまで。";
	mes "どうぞ一度我が家に";
	mes "訪問してください。";
	mes "お待ちしていますよ。";
	close;
}

prt_cas.gat,85,225,4	script	カタリナ・ウィグナー#ep16wig01	71,{
	mes "[カタリナ]";
	mes "久しぶりの王宮です。";
	mes "色々と変わった気がします。";
	mes "たまには訪れたいのですが……";
	next;
	mes "[ルヴィエル]";
	mes "招待を受ければ";
	mes "良いではないか。";
	mes "訪問はそんなに難しくないよ？";
	next;
	mes "[カタリナ]";
	mes "……そういう話ではないのです。";
	close;
}

prt_cas_q.gat,88,184,0	script	#ep16lug004	139,14,14,{
OnTouch:
	if(EP16_6QUE == 3) {
		cloakoffnpc "マイアー・レベンブルグ#ep16lug";
	} else if(EP16_6QUE > 7) {
		cloakonnpc "ヘルムト・レベンブルグ#ep16lug";
		cloakonnpc "マイアー・レベンブルグ#ep16lug";
		cloakonnpc "カルベルン#ep16lug";
	}
	end;
}

prt_cas_q.gat,90,186,5	script	マクシーミリアン#ep16lug	10133,{
	if(EP16_1QUE < 2) {
		end;
	}
	switch(EP16_6QUE) {
	case 0:
		mes "[マクシーミリアン]";
		mes "ようこそ、冒険者様。";
		mes "^0000cdレベンブルグ^000000家に";
		mes "お越しいただき光栄です。";
		mes "私は^0000cdマクシーミリアン^000000と申します。";
		next;
		menu "ご挨拶に伺いました",-;
		mes "[マクシーミリアン]";
		mes "これはわざわざありがとうございます。";
		mes "我がレベンブルグ家は";
		mes "建国七家門の一つにして、";
		mes "古来、ルーンミッドガッツ王国のため";
		mes "力を注いでおります。";
		next;
		mes "[マクシーミリアン]";
		mes "今回の王位継承にも";
		mes "我が家門の後継者、";
		mes "^0000cdヘルムト・レベンブルグ^000000が";
		mes "王位継承候補として参加しますので";
		mes "私共々、お見知りおきいただければ";
		mes "幸いです。";
		next;
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "初めまして。紹介にあずかった";
		mes "^0000cdヘルムト・レベンブルグ^000000と申します。";
		next;
		menu "挨拶する",-;
		mes "[ヘルムト]";
		mes strcharinfo(0)+"殿。";
		mes "魔王モロク討伐に活躍した";
		mes "冒険者にお会いでき、大変光栄です。";
		next;
		cutin "16hel.bmp",255;
		mes "[マクシーミリアン]";
		mes "もしよろしければ";
		mes "私たち以外のレベンブルグ家の者にも";
		mes "会っていただけますでしょうか。";
		next;
		mes "[マクシーミリアン]";
		mes "本来であれば私がご案内するのが";
		mes "よろしいかとは思いますが、";
		mes "王位継承の儀式の準備が";
		mes "ありまして……";
		next;
		mes "[マクシーミリアン]";
		mes strcharinfo(0)+"様";
		mes "でしたら、";
		mes "ご自由にしていただいて";
		mes "問題ありません。";
		next;
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "……ぜひ、我が弟、";
		mes "^0000cdヴォルフ・レベンブルグ^000000にも";
		mes "会ってやってください。";
		next;
		mes "[マクシーミリアン]";
		mes "そうですな。";
		mes "次男のヴォルフは、";
		mes "国境警備の任で不在の多い";
		mes "ヘルムトに代わり、この家を";
		mes "預かっていますので、";
		mes "色々話を聞いていただくと良いかと。";
		cutin "16hel.bmp",255;
		setquest 14495;
		set EP16_6QUE,1;
		close;
	case 1:
		mes "[マクシーミリアン]";
		mes "もしよろしければ";
		mes "私たち以外のレベンブルグ家の者にも";
		mes "会っていただけますでしょうか。";
		next;
		mes "[マクシーミリアン]";
		mes "本来であれば私がご案内するのが";
		mes "よろしいかとは思いますが、";
		mes "王位継承の儀式の準備が";
		mes "ありまして……";
		next;
		mes "[マクシーミリアン]";
		mes strcharinfo(0)+"様";
		mes "でしたら、";
		mes "ご自由にしていただいて";
		mes "問題ありません。";
		next;
		mes "[マクシーミリアン]";
		mes "次男のヴォルフは、";
		mes "国境警備の任で不在の多い";
		mes "ヘルムトに代わり、この家を";
		mes "預かっていますので、";
		mes "色々話を聞いていただくと良いかと。";
		close;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		mes "[マクシーミリアン]";
		mes "我がレベンブルグ家は、";
		mes "建国の英雄ヴィルヘルムの子孫として";
		mes "ルーンミッドガッツ王国の建国と発展に";
		mes "貢献したと自負しております。";
		next;
		mes "[マクシーミリアン]";
		mes "それゆえ、子どもたちにも";
		mes "教育には気をつけたつもりでしたが";
		mes "作法を無視したり、";
		mes "わがままを言うこともありまして……";
		next;
		mes "[マクシーミリアン]";
		mes "レベンブルグ家の習わしから";
		mes "少しずつずれているようで心配です。";
		mes "はぁ……";
		next;
		mes "[マクシーミリアン]";
		mes strcharinfo(0)+"様に";
		mes "非礼を行ったのであれば、";
		mes "申し訳ありません。";
		mes "どうかお許しください。";
		next;
		mes "[マクシーミリアン]";
		mes "彼らは、";
		mes "将来、このレベンブルグ家の";
		mes "代表となる者なのですが……";
		next;
		mes "[マクシーミリアン]";
		mes "後継者の長男は毎日を戦場で過ごし、";
		mes "次男はこともあろうか";
		mes "家風をおろそかにし事業を開くと……";
		next;
		mes "[マクシーミリアン]";
		mes "三男は暇があれば家出し、";
		mes "裏路地にいり浸っている様子で……";
		mes "監視はつけていますが、";
		mes "その目が届かない時もあるようで。";
		next;
		mes "[マクシーミリアン]";
		mes "……";
		next;
		mes "[マクシーミリアン]";
		mes "不幸中の幸いか、";
		mes "末っ子のアグネスだけは";
		mes "良い子に育ってくれて、";
		mes "私も少しは安心しております。";
		next;
		mes "[マクシーミリアン]";
		mes "おっと";
		next;
		mes "[マクシーミリアン]";
		mes "……歳をとると";
		mes "どうも雑談が多くなるようで。";
		mes "失礼しました。";
		mes "どうか行き先短い老いぼれの戯言と";
		mes "聞き流してやってください。";
		close;
	case 8:
	case 9:
		mes "[マクシーミリアン]";
		mes "……子どもたちには";
		mes "好きにさせすぎました。";
		mes "いずれ自分たちで気づけるだろうと。";
		next;
		mes "[マクシーミリアン]";
		mes "王位に関しても、";
		mes "ヘルムトが選ばれる可能性は";
		mes "なきに等しいと思い、";
		mes "好きにさせていたのです。";
		mes "戦争にだけは反対しましたが。";
		next;
		mes "[マクシーミリアン]";
		mes "しかし、こうなれば";
		mes "今回を機に";
		mes "それぞれの位置で";
		mes "家を立て直す機会にしたいと思います。";
		mes "危険は機会なり、ともいいますからね。";
		close;
	case 10:
		mes "[マクシーミリアン]";
		mes "ヘルムトをつれてきてください。";
		mes "^0000cdシュバルツバルドの国境付近、";
		mes "国境検問所^000000にいるはずです。";
		mes "現地まで使いの者に案内させましょう。";
		mes "準備はよろしいですか？";
		next;
		if(select("送ってください","待ってください")==2) {
			mes "[マクシーミリアン]";
			mes "準備が出来次第、";
			mes "私に声をかけてください。";
			close;
		}
		mes "[マクシーミリアン]";
		mes "手数をおかけしますが、";
		mes "よろしくお願いします。";
		close2;
		warp "yuno_fild01.gat",242,165;
		end;
	case 11:
		cutin "16wol_nor.bmp",255;
		mes "[マクシーミリアン]";
		mes "おお、どうでしたか。";
		mes "その様子ですと、";
		mes "行ってきてくださったようですね。";
		next;
		mes "[マクシーミリアン]";
		mes "ですが……";
		mes "ヘルムトがいませんね……";
		mes "やはりここには来ないと？";
		next;
		mes "‐ヘルムトの意思と";
		mes "　後継者に関する話を";
		mes "　マクシーミリアンと";
		mes "　ヴォルフに伝えた‐";
		next;
		mes "[マクシーミリアン]";
		mes "ヘルムトが出て行ったと聞いた時、";
		mes "なんとなくそうだとは思いましたが、";
		mes "レベンブルグ家後継者の席まで";
		mes "放棄してしまうとは……";
		next;
		mes "[マクシーミリアン]";
		mes "……ですが、ヘルムトの意思を尊重し、";
		mes "受け入れましょう。";
		mes "時機をみて、公表したいと思います。";
		next;
		mes "[マクシーミリアン]";
		mes "そしてヴォルフ、";
		mes "これからはお前がレベンブルグ家を";
		mes "率いるのだ。";
		mes "……重荷になるかもしれんが";
		mes "尽力してくれ。";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "……";
		next;
		cutin "16wol_nor.bmp",255;
		mes "[マクシーミリアン]";
		mes "私のやり方で、子どもたちに";
		mes "挫折を与えてしまった過去があったので";
		mes "なるべく好きにさせていましたが、";
		mes "やっとわかった気がします。";
		next;
		mes "[マクシーミリアン]";
		mes "新しい時代は";
		mes "新しい世代に任せるべきだと。";
		mes "ここからは子どもたちの手で";
		mes "レベンブルグ家を";
		mes "率いてもらいましょう。";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "……今まで、";
		mes "兄や他の者には";
		mes "私のやり方を";
		mes "強要してしまっていました。";
		next;
		mes "[ヴォルフ]";
		mes "多くの影響を";
		mes "大陸の隅々まで与えるには";
		mes "戦争より良い方法があるはずです。";
		next;
		mes "[ヴォルフ]";
		mes "マイアーの言葉通り、";
		mes "方法を探してみます。";
		mes "そして必ず見つけます。";
		next;
		mes "[ヴォルフ]";
		mes "もしよろしければ、";
		mes "^0000cdマイアーにも私の意志を";
		mes "伝えていただけませんか。^000000";
		next;
		mes "[ヴォルフ]";
		mes "戦争はあきらめ、";
		mes "よりよい方法探していると。";
		mes "そして、また以前のように";
		mes "家にも顔を出して欲しいと。";
		next;
		menu "わかりました",-;
		mes "[ヴォルフ]";
		mes "よろしくお願いします。";
		delquest 14505;
		setquest 14506;
		set EP16_6QUE,12;
		next;
		cutin "16wol_nor.bmp",255;
		mes "‐マイアーを探しに行きますか？‐";
		next;
		if(select("探しに行く","探しに行かない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラに向かった‐";
		close2;
		warp "prontera.gat",262,67;
		end;
	case 12:
		mes "[マクシーミリアン]";
		mes "マイアーにヘルムトの話を";
		mes "伝えてください。";
		mes "プロンテラのどこかにいるはずです。";
		next;
		mes "‐マイアーを探しに行きますか？‐";
		next;
		if(select("探しに行く","探しに行かない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラに向かった‐";
		close2;
		warp "prontera.gat",262,67;
		end;
	case 13:
		mes "[マクシーミリアン]";
		mes "いらっしゃいませ、冒険者様。";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "マイアーに";
		mes "話は伝えていただけましたか？";
		mes "マイアーはなにか言っていましたか？";
		next;
		cutin "16wol_nor.bmp",255;
		mes "‐あなたは、マイアーの言葉を";
		mes "　マクシーミリアンに";
		mes "　報告した‐";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "そうですか。";
		mes "戦争をあきらめて良かった。";
		mes "私を信頼していると……";
		mes "……敵に回したら面倒なのは";
		mes "お互い様ですが。ふふ。";
		next;
		mes "[ヴォルフ]";
		mes "困ったときは手助け";
		mes "……というよりは";
		mes "もう少し家に戻ってきて";
		mes "欲しいのですがね。";
		next;
		mes "[ヴォルフ]";
		mes "まあ、以前よりは";
		mes "関係が改善されたようで、";
		mes "期待しますよ。";
		next;
		mes "[ヴォルフ]";
		mes "ひとまずは";
		mes "祝宴が落ち着いたら";
		mes "戻ってくるかな。";
		next;
		mes "[ヴォルフ]";
		mes "それまでに";
		mes "歓迎の準備をしなくては";
		mes "いけませんね。";
		next;
		cutin "16wol_nor.bmp",255;
		mes "[マクシーミリアン]";
		mes "よかったです。";
		mes "やっと……";
		mes "やっと、家族の絆を";
		mes "取り戻せたようです。";
		next;
		mes "[マクシーミリアン]";
		mes "あなた様のおかげです。";
		mes "これからはそれぞれの位置で";
		mes "家門と王国のために";
		mes "努力を惜しまないでしょう。";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "レベンブルグ家の危機を救ってくださり";
		mes "本当にありがとうございます。";
		mes "感謝の印としては";
		mes "少ないかもしれませんが……";
		next;
		mes "[ヴォルフ]";
		mes "こちらをどうか受け取ってください。";
		next;
		if(checkitemblank() == 0) {	// 未調査
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		cutin "16wol_nor.bmp",255;
		mes "[マクシーミリアン]";
		mes "レベンブルグ家の助けが必要でしたら";
		mes "いつでもいらしてください。";
		mes "我がレベンブルグ家の扉は";
		mes "いつでも開いております。";
		delquest 14507;
		setquest 201885;
		set EP16_6QUE,14;
		getitem 6919,30;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		close;
	case 14:
		mes "[マクシーミリアン]";
		mes strcharinfo(0)+"様には";
		mes "本当に感謝しております。";
		mes "あなたのおかげで、";
		mes "レベンブルグ家は";
		mes "安定を取り戻しつつあります。";
		next;
		mes "[マクシーミリアン]";
		mes "我がレベンブルグ家は、";
		mes "今まで互いに信じることもできず、";
		mes "刃を向け合っていました。";
		next;
		mes "[マクシーミリアン]";
		mes "……ですがもう大丈夫です。";
		mes "ありがとうございます。";
		close;
	}
}

prt_cas_q.gat,90,184,7	script	ヘルムト・レベンブルグ#ep16lug	10127,{
	switch(EP16_6QUE) {
	case 0:
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "どうも、";
		mes "ヘルムト・レベンブルグと申します。";
		next;
		mes "[ヘルムト]";
		mes "家のことなら私よりも、";
		mes "^0000cdあちらにいる私の祖父に";
		mes "^0000cd聞いてください。^000000";
		mes "私よりはまともな話が聞けるでしょう。";
		close2;
		cutin "16hel.bmp",255;
		end;
	case 1:
	case 2:
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "私の弟、^0000cdヴォルフ・レベンブルグ^000000には";
		mes "お会いになりましたか？";
		next;
		mes "[ヘルムト]";
		mes "私が戦場にこもっている間、";
		mes "弟にはレベンブルグ家の多くを";
		mes "任せていますので、";
		mes "色々聞いていただくと良いかと。";
		close2;
		cutin "16hel.bmp",255;
		end;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "久しぶりに家に戻りました。";
		mes "家族の顔も見れましたし、";
		mes "我が家というものは良いですね。";
		next;
		mes "[ヘルムト]";
		mes "……しかし、今この時も";
		mes "モンスターの危険に晒されている";
		mes "戦場の仲間のことを考えると、";
		mes "心はひどく重くなります。";
		next;
		mes "[ヘルムト]";
		mes "一刻も早く祝宴を終えて";
		mes "戦場に戻りたいですね。";
		mes "ここは私には少し窮屈です。";
		close2;
		cutin "16hel.bmp",255;
		end;
	}
}

prt_cas_q.gat,86,180,7	script	カルベルン#ep16lug	962,{
	if(EP16_6QUE < 8) {
		mes "[カルベルン]";
		mes "こんにちは。";
		mes "私はヘルムト様の付き人";
		mes "^0000cdカルベルン^000000と申します。";
		next;
		mes "[カルベルン]";
		mes "国境近くの戦場で";
		mes "ヘルムト様のお世話をしていたせいか、";
		mes "たまにプロンテラに来ると";
		mes "どうもなじめません。";
		next;
		mes "[カルベルン]";
		mes "王宮の貴族や王族の皆様の";
		mes "プレッシャーも感じますし……";
		next;
		mes "[カルベルン]";
		mes "ヘルムト様も、";
		mes "ここでは王族の一員として";
		mes "過ごされていて……";
		mes "いつもと違う姿で";
		mes "なんだか遠く感じます。";
		next;
		mes "[カルベルン]";
		mes "戦場では一兵士にも、召使いにも";
		mes "分け隔てなく接してくださる方で、";
		mes "皆、ヘルムト様が好きなんです。";
		next;
		mes "[カルベルン]";
		mes "私もモンスターの襲撃で";
		mes "両親を失って……ヘルムト様に";
		mes "引き取っていただいたのです。";
		next;
		mes "[カルベルン]";
		mes "その恩に報いるために、";
		mes "お世話をさせていただいております。";
		next;
		mes "[カルベルン]";
		mes "しかしここでは";
		mes "ヘルムト様が渇きを感じる前に";
		mes "飲み物を運ぶくらいしか";
		mes "やることがありません。";
		next;
		mes "[カルベルン]";
		mes "祝宴が早く終わってほしいですね……";
		next;
		mes "[カルベルン]";
		mes "ああ、決してヘルムト様が";
		mes "国王になってほしくない、とかでは";
		mes "ないのですよ。";
		mes "ただ、なんだかここは窮屈で……";
		close;
	}
}

prt_cas_q.gat,92,182,7	script(CLOAKED)	マイアー・レベンブルグ#ep16lug	10129,{
	cutin "16mye_nor.bmp",1;
	mes "[マイアー]";
	mes "久しぶりの我が家は安らぎますね。";
	mes "すこし窮屈ですが。";
	next;
	mes "[マイアー]";
	mes "俺がいなくても問題はないだろうから";
	mes "心配はしていなかったのですが、";
	mes "祖父ももう歳なのが";
	mes "少し気がかりで。";
	mes "まあ、皆元気そうで安心しましたよ。";
	next;
	mes "[マイアー]";
	mes "寂しい気も少しはしますがね。";
	mes "はは……。家を出て行った手前、";
	mes "言えた立場ではないのですが。";
	close2;
	cutin "16mye_nor.bmp",255;
	end;
}

prt_cas_q.gat,96,186,3	script	ヴォルフ・レベンブルグ#ep16lug	10128,{
	switch(EP16_6QUE) {
	case 0:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "レベンブルグ家にご訪問いただき";
		mes "ありがとうございます。";
		mes "レベンブルグ家の長であり、";
		mes "私の祖父の";
		mes "^0000cdマクシーミリアン^000000には";
		mes "会っていただけましたか？";
		next;
		mes "[ヴォルフ]";
		mes "まだでしたら、是非";
		mes "会っていただきたいです。";
		mes "祖父は冒険者様と話せることを";
		mes "とても楽しみにしております。";
		close2;
		cutin "16wol_nor.bmp",255;
		end;
	case 1:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "レベンブルグ家にご訪問いただき";
		mes "ありがとうございます。";
		mes "私はレベンブルグ家の次男、";
		mes "^0000cdヴォルフ・レベンブルグ^000000と申します。";
		next;
		mes "[ヴォルフ]";
		mes "我々レベンブルグ家は、建国の英雄";
		mes "ヴィルヘルム・レベンブルグの";
		mes "意志を継ぎ、";
		mes "名誉と正義と伝統の守護のため、";
		mes "邁進しております。";
		next;
		mes "[ヴォルフ]";
		mes "ルーンミッドガッツ建国以来、";
		mes "我が家門の多くの者たちが";
		mes "国のために尽力してきた歴史を";
		mes "私はとても誇らしく思いますよ。";
		next;
		mes "[ヴォルフ]";
		mes "そして今、私の兄の";
		mes "^0000cdヘルムト・レベンブルグ^000000が";
		mes "王位継承の候補として";
		mes "皆に期待されております。";
		mes "兄にはお会いになりましたか？";
		next;
		switch(select("はい","いいえ")) {
		case 1:
			mes "[ヴォルフ]";
			mes "結構なことです。";
			mes "きっと兄は、この国の王になれる人と";
			mes "理解いただけたことでしょう。";
			break;
		case 2:
			mes "[ヴォルフ]";
			mes "ふふ、とぼけるのが";
			mes "上手な方ですね。";
			mes "さきほどレベンブルグ家の当主と";
			mes "共に挨拶しているのを";
			mes "見ていますよ。";
			next;
			mes "[ヴォルフ]";
			mes "兄はきっと";
			mes "この国の王になれるでしょう。";
			break;
		}
		next;
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "冒険者様、お初にお目にかかります。";
		mes "わたくし、";
		mes "^0000cdアグネス・レベンブルグ^000000と申します。";
		mes "兄弟の中では一番末で、";
		mes "長女になります。";
		next;
		mes "[アグネス]";
		mes "話は変わりますが、冒険者様は";
		mes "祝宴のパートナーはお決まりですの？";
		mes "実はわたくし、まだパートナーが";
		mes "決まっておりませんの……";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "アグネス、今は";
		mes "そのような話をする場ではないのだ。";
		mes "私がレベンブルグ家についての";
		mes "説明を……";
		next;
		cloakoffnpc "マイアー・レベンブルグ#ep16lug";
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "それじゃ美しいお嬢さんは";
		mes "私と共に参りませんか？";
		next;
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "ああっ！　マイアー兄！";
		next;
		mes "[アグネス]";
		mes "帰ってきたのね！";
		mes "おかえりなさい！";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "ああ、ちょうどいいところに。";
		mes "彼は我が弟、三男の";
		mes "^0000cdマイアー・レベンブルグ^000000と申します。";
		next;
		mes "[ヴォルフ]";
		mes "長い間家を離れていましたが";
		mes "やっと帰ってきたようです。";
		mes "……帰ってきたんだよな？";
		next;
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "半分くらいは。";
		mes "プロンテラの路地裏にまで";
		mes "^0000cd戦争に狂った長兄と金に堕落した次兄が";
		mes "^0000cd王位継承のために手を組んだ^000000って";
		mes "話が伝わってきてね。";
		next;
		mes "[マイアー]";
		mes "だから帰ってきたのさ。";
		mes "普段は目も合わせない兄弟が";
		mes "いきなり仲良しごっこだ。";
		mes "俺も混ざらないわけには";
		mes "いかないだろう？";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "……言葉を慎め。";
		mes "^0000cd家を出て不良とつるんでいる^000000としても";
		mes "この場所まで薄汚い裏路地に";
		mes "染める必要はない。";
		mes "私がお前の行動を知らないとでも";
		mes "思っていたのか？";
		next;
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "へえ～？　それ本気で言ってる？";
		mes "じいさまやお前が送りこんだ";
		mes "監視役がいたのは、";
		mes "裏路地の子どもでも知ってるぜ。";
		next;
		mes "[マイアー]";
		mes "うちの高貴な兄には、";
		mes "俺の言葉遣いは";
		mes "薄汚いと感じるようだけど、";
		next;
		cutin "16mye_ang.bmp",1;
		mes "[マイアー]";
		mes "長兄と手を組んで";
		mes "^0000cdヘルムト兄が王になれば^000000、";
		mes "^0000cd王城以外、国中が^000000";
		mes "^0000cd裏路地と同じになる^000000だろうから、";
		mes "今から聞きなれた方が良いんじゃない？";
		next;
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "いや、うちの兄様がたには";
		mes "もう、戦争で得られる金を";
		mes "数える音しか聞こえないか～。";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "……場を弁えろ。";
		mes "それにお前呼ばわりはやめるんだ。";
		mes "もう良い大人だろう。";
		mes "そのような品のない";
		mes "言葉遣いはやめるんだ。";
		next;
		cutin "16agn_ang.bmp",2;
		mes "[アグネス]";
		mes "もうやめてよ！";
		mes "なんでケンカばかりするの!?";
		next;
		mes "[アグネス]";
		mes "それに今日は祝宴じゃなかったの？";
		mes "せっかく冒険者様も";
		mes "いらしてくださったのに！";
		mes "私たちを見てなんと思われてるかしら！";
		mes "気品の欠片もないわ!!";
		next;
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "ああ、そうだね。";
		mes "どうやら招かれざる客だった俺が";
		mes "ここから去る方がよさそうだ。";
		mes "アグネス、また後でな。";
		next;
		cloakonnpc "マイアー・レベンブルグ#ep16lug";
		cutin "16agn_ang.bmp",2;
		mes "[アグネス]";
		mes "……";
		next;
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "……私も、失礼しますわ。";
		mes "準備をして参ります……。";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "……見苦しいところをお見せしてしまい";
		mes "申し訳ありません。";
		mes "マイアーは家から長く離れていたので";
		mes "礼儀を忘れているようです。";
		next;
		mes "[ヴォルフ]";
		mes "後でお詫びに行くよう話しておきます。";
		mes "もともとあのような性格では";
		mes "ないのですが……どうかご容赦を。";
		next;
		menu "はい",-;
		mes "[ヴォルフ]";
		mes "そう言っていただけると助かります。";
		mes "ところでお時間があるようでしたら、";
		mes "一つ頼まれていただいても";
		mes "よろしいでしょうか。";
		next;
		menu "なんでしょう",-;
		mes "[ヴォルフ]";
		mes "ウィグナー家に訪問いただき、";
		mes "^0000cdアイザック・ウィグナー様^000000より";
		mes "ある品物を";
		mes "受け取っていただきたいのです。";
		next;
		mes "[ヴォルフ]";
		mes "本来なら、私が行く予定でしたが";
		mes "マイアーのことを";
		mes "祖父に伝えておく必要が";
		mes "あるようです。";
		mes "それも、できるだけ早く。";
		next;
		if(select("そうですね","なぜ？")==2) {
			cutin "16wol_ang.bmp",2;
			mes "[ヴォルフ]";
			mes "……他意はありませんよ。";
			mes "弟がここに顔を見せた理由が";
			mes "我が家の名に泥を塗るような";
			mes "ものですからね。";
			mes "祖父はこの家の当主。";
			mes "報告は当然でしょう？";
			next;
		}
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "冒険者様は、祝宴に";
		mes "招待されるだけの信頼に値する方。";
		mes "アイザック様も";
		mes "理解してもらえるでしょう。";
		next;
		menu "わかりました",-;
		mes "[ヴォルフ]";
		mes "ありがとうございます。";
		mes "アイザック・ウィグナー様は";
		mes "ウィグナー家が滞在している";
		mes "部屋にいらっしゃるようです。";
		mes "よろしくお願いします。";
		next;
		delquest 14495;
		setquest 14496;
		delquest 73055;
		delquest 7682;
		setquest 7685;
		set EP16_6QUE,2;
		if((checkquest(7683)&0x8) && !checkquest(73051) && !checkquest(73053) && !checkquest(73052) && !checkquest(73054) && !checkquest(73055) && !checkquest(73056)) {
			mes "‐^0000cd七王家すべてに挨拶をした。^000000";
			mes "　ベルのところに戻ろう‐";
		} else {
			mes "‐^0000cdレベンブルグ家との挨拶を済ました。^000000";
			mes "　他の王家にも挨拶に行こう‐";
		}
		next;
		mes "‐また、ヴォルフから";
		mes "　^0000FFレベンブルグ家の絆クエスト^000000";
		mes "　を受注した。このクエストを";
		mes "　進行するのもよいだろう‐";
		close2;
		cutin "16wol_nor.bmp",255;
		end;
	case 2:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "アイザック様より";
		mes "品物を受け取ってきてください。";
		mes "よろしくお願いします。";
		next;
		mes "[ヴォルフ]";
		mes "ウィグナー家が滞在されているのは";
		mes "^0000cd廊下に出て南、つきあたりの部屋^000000です。";
		close2;
		cutin "16wol_nor.bmp",255;
		end;
	case 3:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "冒険者様、";
		mes "お願いしていた品は……";
		mes "おお、これですね。";
		next;
		cutin "16wol_nor.bmp",255;
		mes "‐アイザック・ウィグナーから";
		mes "　預かった品物を";
		mes "　ヴォルフに渡した‐";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "おや、これは……";
		mes "箱に鍵がかけられているようですね。";
		mes "^0000cdパスワードの数字^000000を入力することで";
		mes "開くようです。";
		next;
		mes "[ヴォルフ]";
		mes "……ふむふむ、";
		mes "どうやら^0000cd黄金と数^000000を愛する";
		mes "ウィグナー家のウィットが";
		mes "含まれたものですね。";
		next;
		mes "[ヴォルフ]";
		mes "とすると……なるほど。";
		mes "これは^0000cd黄金比率^000000が答えです。";
		mes "一番最初の文字は「^0000cd1^000000」。";
		mes "冒険者様、";
		mes "続きはおわかりですか？";
		next;
		menu "えーと……",-;
		input '@str$;
		cutin "16wol_nor.bmp",255;
		if('@str$ == "1618") {
			mes "‐あなたは";
			mes "　「^0000cd1618^000000」と入力した。";
			mes "　カチリと小さな音が";
			mes "　二人の間に響く‐";
			next;
			cutin "16wol_nor.bmp",2;
			mes "[ヴォルフ]";
			mes "おお、開きましたね！";
			mes "さすが冒険者様。";
			mes "博識でいらっしゃるようだ。";
			next;
			mes "[ヴォルフ]";
			mes "そして中にあるのは……";
			mes "こちらです。";
		} else {
			mes "‐あなたは";
			mes "　「^0000cd"+ '@str$ +"^000000」と入力した。";
			mes "　箱はなんの反応も示さない‐";
			next;
			cutin "16wol_nor.bmp",2;
			mes "[ヴォルフ]";
			mes "ふふ、冒険者様にも";
			mes "わからないことがあるようだ。";
			mes "このパスワードの答えは「^0000cd1618^000000」ですよ。";
			mes "　";
			mes "‐ヴォルフが数字を入力すると";
			mes "　小さな音が二人の間に響いた‐";
			next;
			mes "[ヴォルフ]";
			mes "さあ、開きました。";
			mes "そして中にあるのは……";
			mes "こちらです。";
			next;
		}
		mes "‐ヴォルフは小瓶を取り出し";
		mes "　良く見えるよう、";
		mes "　少し高い位置へ掲げた‐";
		next;
		mes "[ヴォルフ]";
		mes "この小さな瓶に詰まったものは、";
		mes "これからの戦闘と";
		mes "戦争の図を変えてしまうでしょう。";
		mes "まだ試作品ですが。";
		next;
		mes "[ヴォルフ]";
		mes "冒険者様にお願いして正解でしたね。";
		mes "報酬は必ずや、お気に召すものを";
		mes "準備させていただきます。";
		next;
		menu "よろしく",-,"おかまいなく",-;
		mes "[ヴォルフ]";
		mes "それと……";
		mes "アイザック様はなにか";
		mes "おっしゃっていましたか？";
		next;
		menu "伝言を伝える",-;
		cutin "16wol_ang.bmp",2;
		mes "‐あなたは";
		mes "　アイザックの伝言を";
		mes "　ヴォルフに伝えた‐";
		next;
		mes "[ヴォルフ]";
		mes "兄さんに関する噂……ですか。";
		next;
		mes "[ヴォルフ]";
		mes "……";
		mes "マイアーが顔を見せた理由といい、";
		mes "一体なにが……";
		mes "これは確認する必要がありますね。";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "……その、";
		mes "冒険者様……";
		next;
		menu "はい",-;
		mes "[ヴォルフ]";
		mes "もう一度、お願いをしても";
		mes "よろしいでしょうか。";
		mes "今の噂について";
		mes "調べていただきたいのです。";
		next;
		mes "[ヴォルフ]";
		mes "いろいろな場所を訪れる冒険者様なら";
		mes "多くの情報を得ることが";
		mes "できるでしょうし、";
		mes "なにより私が信頼できる方ですので。";
		next;
		mes "[ヴォルフ]";
		mes "ただでさえ仕事が山積みなのに、";
		mes "愚弟も帰ってくるし……。";
		mes "お忙しいなら";
		mes "断っていただいても大丈夫です。";
		next;
		if(select("わかりました","嫌です") == 2) {
			mes "[ヴォルフ]";
			mes "そうですか。";
			mes "……いえ、断っていただいて良いと";
			mes "言ったのは私です。";
			mes "無理は言いません。";
			next;
			mes "[ヴォルフ]";
			mes "……ですが、もし";
			mes "お引き受けできるようでしたら";
			mes "私に教えてください。";
			close2;
			cutin "16wol_nor.bmp",255;
			end;
		}
		mes "[ヴォルフ]";
		mes "本当にありがとうございます。";
		mes "噂話なら……";
		mes "まずは子どもを調べると良いでしょう。";
		mes "^0000cdプロンテラの空き地^000000などで";
		mes "よく遊んでいるようですので";
		mes "寄ってみてください。";
		next;
		if(countitem(6930) > 0)
			delitem 6930,1;
		delquest 14497;
		setquest 14498;
		set EP16_6QUE,4;
		cutin "16wol_nor.bmp",255;
		mes "["+strcharinfo(0)+"]";
		mes "（プロンテラの空き地か……";
		mes "　たしかプロンテラの南東の方";
		mes "　だったかな？）";
		next;
		if(select("移動する","移動しない") == 2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラの空き地に";
		mes "　向かった‐";
		close2;
		warp "prontera.gat",262,67;
		end;
	case 4:
	case 5:
	case 6:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "プロンテラでささやかれている";
		mes "レベンブルグ家の噂は、";
		mes "どのようなものでしたか？";
		next;
		mes "[ヴォルフ]";
		mes "噂話なら……";
		mes "まずは子どもを調べると良いでしょう。";
		mes "^0000cdプロンテラの空き地^000000などで";
		mes "よく遊んでいるようですので";
		mes "寄ってみてください。";
		next;
		cutin "16wol_nor.bmp",255;
		mes "["+strcharinfo(0)+"]";
		mes "（プロンテラの空き地か……";
		mes "　たしかプロンテラの南東の方";
		mes "　だったかな？）";
		next;
		if(select("移動する","移動しない") == 2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラの空き地に";
		mes "　向かった‐";
		close2;
		warp "prontera.gat",262,67;
		end;
	case 7:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "お帰りなさい。";
		mes "どうやらお疲れのようですね。";
		mes "レベンブルグ家の噂について";
		mes "調べていただけましたか？";
		next;
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "噂話ですって？";
		mes "それはどのようなお話ですの？";
		next;
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "……ああ、";
		mes "先ほどお前に聞いた噂だな、ヴォルフ。";
		mes "プロンテラでささやかれているという。";
		next;
		cutin "16hel.bmp",255;
		mes "[マクシーミリアン]";
		mes "もうお調べになられたのですか？";
		mes strcharinfo(0)+"様。";
		next;
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "へえ、俺も興味があるな。";
		cloakoffnpc "マイアー・レベンブルグ#";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "マイアー。";
		next;
		cutin "16mye_ang.bmp",1;
		mes "[マイアー]";
		mes "なんだ？";
		mes "俺は、妹に会いにきたんだ。";
		mes "喧嘩したからといって";
		mes "それも駄目とは言わないよな。";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "……";
		mes "　";
		mes "‐ヴォルフはため息を";
		mes "　一つついた‐";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "冒険者様。";
		mes "調査の報告をしていただけますか？";
		next;
		if(select("わかりました","ここで話をしても？")==2) {
			cutin "16hel.bmp",0;
			mes "[ヘルムト]";
			mes "問題ありません。";
			mes "レベンブルグ家の話ですから、";
			mes "みな聞く必要があります。";
			next;
		}
		cutin "16wol_nor.bmp",255;
		mes "‐あなたは子ども達の話を";
		mes "　内容を少し和らげて伝えた‐";
		next;
		cutin "16agn_ang.bmp",2;
		mes "[アグネス]";
		mes "まあ、戦争なんて！";
		mes "そんなことをして";
		mes "誰が喜びますの？";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "……なるほど、";
		mes "ただの噂話にしては";
		mes "悪意が感じられるほどに具体的ですね。";
		next;
		mes "[ヴォルフ]";
		mes "しかし、";
		mes "噂を流したのは";
		mes "どうやら、レベンブルグ家を";
		mes "良く知っている者のようだ。";
		next;
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "ヴォルフ兄！";
		mes "何を言いますの？";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "もちろん、お前を";
		mes "疑ってはいないよ。";
		mes "アグネス。";
		mes "お前がそんなことをするとは思わない。";
		next;
		mes "[ヴォルフ]";
		mes "しかし……";
		mes "　";
		mes "‐ヴォルフは静かに";
		mes "　マイアーに視線を向けた‐";
		next;
		mes "[ヴォルフ]";
		mes "……^0000cdマイアー？";
		mes "どこまでレベンブルグの名に";
		mes "泥を塗りつけるつもりなんだ？^000000";
		next;
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "そうだね……";
		mes "必要な分だけ、かな？";
		next;
		emotion 23,"マクシーミリアン#ep16lug";
		emotion 23,"ヴォルフ・レベンブルグ#ep16lug";
		emotion 23,"アグネス・レベンブルグ#ep16lug";
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "マイアー、本当にお前が？";
		next;
		cutin "16agn_ang.bmp",2;
		mes "[アグネス]";
		mes "マイアー兄!?";
		next;
		cutin "16agn_ang.bmp",255;
		mes "[マクシーミリアン]";
		mes "マイアー……本当なのか……？";
		mes "お前がこの噂話を……";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "チンピラを集めて";
		mes "ボスにでもなったつもりか？";
		mes "さぞかし楽しかったのだろうな。";
		next;
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "そのチンピラがやらかしたことを";
		mes "ようやく目の当たりにしたのだろう？";
		mes "上流社会の人間だけが";
		mes "影響力を持っていると、";
		mes "いくら頭が腐ったからといって";
		mes "勘違いしてるわけはないよな。";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "……どこまでやるつもりだ。";
		next;
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "そうだね……";
		mes "聖堂の友達に頼んだのもあるし、";
		mes "商人仲間もいたな。";
		mes "ああ、もちろん裏路地の仲間もな。";
		next;
		mes "[マイアー]";
		mes "俺が助けが必要だといったら、";
		mes "みんな二つ返事で";
		mes "助け舟を出してくれたよ。";
		next;
		mes "[マイアー]";
		mes "果たしてお前が見えない者まで";
		mes "相手にできるか見ものだね！";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "……お前が何を考えて噂を……";
		mes "こんなことをしているのかが";
		mes "私にはわからん。";
		next;
		mes "[ヴォルフ]";
		mes "……いや、解っている。";
		mes "お前のその小さい同情心で";
		mes "私の計画を";
		mes "全てぶち壊すつもりなのだろう！";
		next;
		cutin "16mye_ang.bmp",1;
		mes "[マイアー]";
		mes "計画？　なんのことだ？";
		mes "もしかして戦争計画か？";
		mes "罪無き人々を戦場に赴かせることか？";
		mes "お前の野望を成就するために!?";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "……お前はまだまだ子どもだ。";
		mes "兄さんと私がどんな思いで";
		mes "この計画を実行しているのか";
		mes "全くわかっていない！";
		next;
		mes "[ヴォルフ]";
		mes "^0000cd14年前^000000、最高の家柄と謳われた";
		mes "我々が何もできなかった";
		mes "あの無力感を、お前は、";
		mes "お前は覚えていないのか!?";
		next;
		mes "[ヴォルフ]";
		mes "^0000cd名門の家柄という名前^000000だけだ。";
		mes "なのにお前はチンピラどもの";
		mes "ボス気取りで計画を台無しにしている！";
		next;
		cutin "16mye_ang.bmp",1;
		mes "[マイアー]";
		mes "そうして家を建て直したら大陸か？";
		mes "その後に残るものはなんだ？　復讐か?!";
		next;
		mes "[マイアー]";
		mes "お前も知っているだろう！";
		mes "それは新たな苦痛を呼ぶだけだって。";
		mes "親無しも当然に育った俺らは";
		mes "家門と残っていた財産で";
		mes "不自由はしなかった。";
		next;
		mes "[マイアー]";
		mes "それに^0000cd互いに支えあう兄弟^000000がいたよ。";
		mes "思い出せ、あの時の俺達を。";
		mes "でもな、この世の中には";
		mes "俺らのように運が良い人は";
		mes "そんなに多くないんだ!!";
		next;
		mes "[マイアー]";
		mes "親がいなくて身寄りもいない、";
		mes "横たわる場所一つもない、";
		mes "飢えた腹を満たす方法なんてない人々が";
		mes "溢れてるんだ!!";
		next;
		mes "[マイアー]";
		mes "ヘルムト兄さんとお前が";
		mes "夢見た世界なんて、";
		mes "^0000cd少数の恵まれた人間のため^000000の";
		mes "世界なんだよ！";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "お前は理想が先走りすぎた！";
		mes "大きな目標のためには";
		mes "時には犠牲にも目を瞑る必要がある！";
		next;
		cutin "16mye_ang.bmp",1;
		mes "[マイアー]";
		mes "目標のための犠牲?!";
		mes "俺が知らないとでも思ったのか？";
		mes "お前がなぜそんなに躍起になって";
		mes "ヘルムト兄さんを助けているのか！";
		next;
		mes "[マイアー]";
		mes "ヘルムト兄さんが";
		mes "王位継承者候補になった時は";
		mes "正直どうでもいいと思ったよ。";
		mes "ヘルムト兄さんは他人から";
		mes "好感や信頼を得ることなんて";
		mes "気にもしない人だから。";
		next;
		mes "[マイアー]";
		mes "ヘルムト兄さんが夢見たものは";
		mes "ただの夢物語として語られるぐらいだ。";
		mes "でもな、お前が野望のために";
		mes "兄さんと手を組んでからは";
		mes "話が変わった。";
		next;
		mes "[マイアー]";
		mes "上っ面では仲のよい兄弟に";
		mes "見せかけているかも知れないけど";
		mes "お前が戦争を利用して";
		mes "儲けを企んでることくらい";
		mes "見抜いてるさ。";
		next;
		cutin "16mye_ang.bmp",1;
		mes "[マイアー]";
		mes "それにヘルムト兄さんを";
		mes "木偶の王に仕立て上げ、";
		mes "^0000cd実質的に家と王国の権力を";
		mes "その手にする^000000のが目的だろう。違うか？";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "レベンブルグ家に今何が残っている？";
		mes "家柄？　名誉？　そんなもの、";
		mes "国から一歩でも出ればただのゴミだ！";
		mes "しかも歳月と共に他の家門より";
		mes "我が家は廃れてきている！";
		next;
		mes "[ヴォルフ]";
		mes "だがな、見ろよ。ウィグナー家を。";
		mes "彼等が何をしても";
		mes "彼等の財力の前に誰しもが";
		mes "その頭を垂れるのを！";
		next;
		mes "[ヴォルフ]";
		mes "それが誰であっても、だ！";
		mes "私が望んでいるのはそんな力だ。";
		mes "無力な名より^0000cd実質的な力が必要なのだ！^000000";
		next;
		cutin "16mye_ang.bmp",1;
		mes "[マイアー]";
		mes "そんなもの、お前のわがままだろうが！";
		mes "ヘルムト兄さんが王になれなかった";
		mes "ときのことは考えていたのか？";
		next;
		mes "[マイアー]";
		mes "レベンブルグ家の次男の位置では";
		mes "やりたい放題なんて無理だよな？";
		mes "その野望、潔くあきらめられるか？";
		next;
		mes "[マイアー]";
		mes "所詮、人間の短い人生なんだよ……";
		mes "人を動かすのは力じゃない、心だよ。";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "……心？";
		mes "^0000cdあいつら^000000にも通じたか？";
		next;
		cutin "16mye_ang.bmp",1;
		mes "[マイアー]";
		mes "……違う角度から";
		mes "近づくべきだったんだ。";
		next;
		cutin "16wol_ang.bmp",2;
		mes "[ヴォルフ]";
		mes "ふ……一丁前に口答えできるとは。";
		mes "もう泣くだけの";
		mes "子どもじゃないってことか。";
		mes "だが戯言はそこまでにしておけよ。";
		next;
		mes "[ヴォルフ]";
		mes "私の堪忍袋の緒が切れる前にな。";
		next;
		cutin "16mye_ang.bmp",1;
		mes "[マイアー]";
		mes "お前が何もしなければ";
		mes "俺だって何もしないさ。";
		mes "裏路地の^0000cd幸せのジョナダン^000000として";
		mes "生きただろう。";
		next;
		mes "[マイアー]";
		mes "だがお前はウィグナーと";
		mes "新事業という名目で";
		mes "殺傷武器を作っていた！";
		next;
		mes "[マイアー]";
		mes "家族の信頼さえ得られない者が";
		mes "もっと多くの民の信頼を";
		mes "得られるわけがないだろう？";
		mes "それに子ども扱いはもう飽き飽きだ。";
		next;
		cutin "16mye_ang.bmp",255;
		mes "[マクシーミリアン]";
		mes "……二人とも";
		next;
		cutin "16agn_ang.bmp",2;
		mes "[アグネス]";
		mes "みんなもうやめてッ!!!!";
		mes "何でみんな争うの？";
		mes "わたくし達、";
		mes "ただ幸せになりたかっただけでしょう？";
		next;
		mes "[アグネス]";
		mes "だからみんな自分の道を見つけようと！";
		mes "ヘルムト兄は戦場で、";
		mes "ヴォルフ兄は商売で、";
		mes "マイアー兄は裏路地で。";
		next;
		mes "[アグネス]";
		mes "それで良いではありませんの？";
		mes "もっと大きなものってなに？";
		mes "名分!?　復讐!?　戦争!?";
		mes "今この狭い場所での争いでさえ、";
		mes "大切なものがなくなっていくのに、";
		mes "これより大きな戦争になるの？";
		next;
		mes "[アグネス]";
		mes "わたくしたちが本当に望むものって何？";
		mes "戦って幸せが得られるのなら、";
		mes "それもいいかも知れないわ。";
		mes "でもそうじゃないでしょう？";
		mes "わたくしたちもう充分争いましたわ……";
		next;
		mes "[アグネス]";
		mes "そうでしょう??";
		mes "……ヘルムト兄、ヴォルフ兄、";
		mes "マイアー兄……";
		next;
		cutin "16agn_ang.bmp",255;
		mes "[マクシーミリアン]";
		mes "……とりあえずみんなそこまでだ。";
		mes "大声を出すのもここまでにしよう。";
		next;
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "アグネスが正しい。";
		mes "二人とももうやめておきなさい。";
		next;
		cutin "16mye_nor.bmp",1;
		mes "[マイアー]";
		mes "……俺は少し席をはずさせてもらうよ。";
		next;
		cloakonnpc "マイアー・レベンブルグ#";
		cutin "16agn_ang.bmp",2;
		mes "[アグネス]";
		mes "マイアー兄！　どこに行くの!?";
		mes "……またどこかに行ってしまうの？";
		next;
		cutin "16agn_ang.bmp",255;
		mes "[マクシーミリアン]";
		mes "……さあ、考えはまとめられるか？";
		mes "私はアグネスに同意するよ。";
		mes "私たちは長い間、争いすぎた。";
		next;
		mes "[マクシーミリアン]";
		mes "だがな力はもっと大きな力を、";
		mes "復讐は更に復讐を呼び込むという事実を";
		mes "私たちは覚えておく必要がある。";
		next;
		mes "[マクシーミリアン]";
		mes "なぜ私がたった一人の息子と";
		mes "義娘を失った時に沈黙していたか……";
		mes "解るか？";
		next;
		mes "[マクシーミリアン]";
		mes "復讐をしても何も変わらないからだ。";
		mes "復讐とは暴力で己の心をごまかし、";
		mes "偽りの慰安を得ているに";
		mes "過ぎないからだ……";
		next;
		mes "[マクシーミリアン]";
		mes "……死んだものは帰らない……";
		mes "お前達の両親も";
		mes "そんなことは望んでいないだろう。";
		next;
		mes "[マクシーミリアン]";
		mes "今まではお前達それぞれの好きに";
		mes "させてきたが今回だけは、";
		mes "アグネスの意見を尊重し、";
		mes "皆に従ってもらおう。";
		mes "……やはり戦争は避けたいのだ。";
		next;
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "…………";
		mes "……私も少し風に当たってきます。";
		next;
		cloakonnpc "ヘルムト・レベンブルグ#ep16lug";
		cutin "16hel.bmp",255;
		mes "[カルベルン]";
		mes "ヘルムト様！　お待ちください！";
		next;
		cloakonnpc "カルベルン#ep16lug";
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "…………";
		next;
		cutin "16wol_nor.bmp",255;
		mes "["+strcharinfo(0)+"]";
		mes "私は部外者ですが、";
		mes "多くの人は戦争を恐れています。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "小さい子ども達さえ。";
		mes "起きていない事実ですが、";
		mes "不安と恐怖が長引くことは";
		mes "よくありません。";
		next;
		mes "[マクシーミリアン]";
		mes "……冒険者様には不本意ながら";
		mes "醜い場面をお見せしてしまい";
		mes "申し訳ありません。";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "……厚かましいのは承知の上で";
		mes "もう一つ、お願いをしても";
		mes "よろしいでしょうか。";
		next;
		cutin "16wol_nor.bmp",255;
		mes "["+strcharinfo(0)+"]";
		mes "乗りかかった船です。";
		mes "お手伝いしますよ。";
		next;
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "何度もありがとうございます。";
		mes "この件について、";
		mes "^0000cdアイザック様にも噂について";
		mes "知らせる必要があります。^000000";
		mes "少々お待ちください。";
		next;
		cutin "16wol_nor.bmp",255;
		mes "‐ヴォルフはそう言うと";
		mes "　目にも止まらぬ速さで";
		mes "　手紙を書き上げ、封をした‐";
		next;
		if(checkitemblank() == 0) {	// 未調査
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "この書類をアイザック様に";
		mes "お渡しください。";
		mes "何度も申し訳ありませんが、";
		mes "よろしくお願いします。";
		delquest 14501;
		setquest 14502;
		set EP16_6QUE,8;
		getitem 6931,1;
		close2;
		cutin "16wol_nor.bmp",255;
		end;
	case 8:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "アイザック様に";
		mes "手紙は届けていただけましたか？";
		next;
		mes "[ヴォルフ]";
		mes "それでは冒険者様、";
		mes "よろしくお願いします。";
		close2;
		cutin "16wol_nor.bmp",255;
		end;
	case 9:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "冒険者様、お疲れ様でした。";
		mes "……アイザック様は";
		mes "気分を害されていましたか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "全て理解していると";
		mes "おっしゃっていました。";
		mes "また、ヴォルフ様が新しい商品を";
		mes "見つけてくださる事を";
		mes "信じている、とも。";
		next;
		mes "[ヴォルフ]";
		mes "それは良かった。私の意図を";
		mes "汲んでいただけたようですね。";
		mes "アイザック様を失望させないために、";
		mes "他の新しい事業の着手にも";
		mes "急がねばなりません。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "事業への熱意は変わらないのですね。";
		next;
		mes "[ヴォルフ]";
		mes "ははは……";
		mes "どうやら私の性に合うようでして。";
		mes "楽しいと思えますし、なにより";
		mes "レベンブルグの名ではなく、";
		mes "私自身の実力を見せる事が";
		mes "できますからね。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ところで他の方は";
		mes "いらっしゃらないようですね。";
		mes "マイアー様やヘルムト様まで……";
		next;
		cutin "16wol_nor.bmp",255;
		mes "[マクシーミリアン]";
		mes "ヘルムトは何も話さず";
		mes "戦場に戻りました。";
		mes "マイアーもまた家を出ました。";
		mes "アグネスの言葉に";
		mes "何かを感じたのでしょう。";
		next;
		mes "[マクシーミリアン]";
		mes "よろしければ……";
		mes "^0000cd噂になっているレベンブルグ家の";
		mes "誤解を解きたい^000000のですが、";
		mes "よろしいでしょうか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "はい、大丈夫です。";
		next;
		mes "[マクシーミリアン]";
		mes "実のところ、噂の内容の";
		mes "ある程度は「事実」です。";
		mes "戦争が起きるという部分以外は。";
		next;
		mes "[マクシーミリアン]";
		mes "……少し昔の話をしましょう。";
		mes "私の息子夫婦、子ども達の親は";
		mes "アグネスが生まれてから";
		mes "隣国にちょっとしたバカンスに";
		mes "行きました。";
		next;
		mes "[マクシーミリアン]";
		mes "ですが、そこで";
		mes "モンスターの襲撃があったのです。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "バカンスなら観光地に行ったのでは？";
		mes "そのような場所でも";
		mes "モンスターが現れたのですか？";
		next;
		mes "[マクシーミリアン]";
		mes "静養のために";
		mes "少し人里と離れた場所だったのです。";
		mes "とはいえ、比較的に安全な場所でした。";
		mes "しかし、なぜか";
		mes "モンスターが群れをなして";
		mes "襲ってきたのだそうです。";
		next;
		mes "[マクシーミリアン]";
		mes "明確な原因は未だにわかりませんが、";
		mes "討伐に耐えられず";
		mes "近くまで来てしまったのでは、と";
		mes "思われます。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "そうだったんですね……";
		next;
		mes "[マクシーミリアン]";
		mes "私が知らせを聞いて急いで向った時には";
		mes "既に地域が封鎖され、";
		mes "立ち入り禁止となっていました。";
		mes "息子夫婦はその地域に";
		mes "取り残されていたはずなのに……";
		next;
		mes "[マクシーミリアン]";
		mes "私たちは管理局に";
		mes "立ち入り禁止区域の捜索を";
		mes "願い出ました。";
		next;
		mes "[マクシーミリアン]";
		mes "しかし彼等は、外国から来た私たち";
		mes "……しかも武装した兵士を";
		mes "自分達の国へ入れる事は";
		mes "徹底して拒否しました。";
		next;
		mes "[マクシーミリアン]";
		mes "……理解はします。";
		mes "他国の武力勢力など";
		mes "信頼関係がない以上、";
		mes "入国を拒否するのが";
		mes "正しい判断でしょう。";
		next;
		mes "[マクシーミリアン]";
		mes "なんとか立ち入り禁止区域に入るため";
		mes "方法を探しましたが、";
		mes "その時点で";
		mes "かなりの時間が経っていました。";
		next;
		mes "[マクシーミリアン]";
		mes "結局なんとかして";
		mes "その地の傭兵を雇用し、";
		mes "立ち入り禁止区域へ赴かせましたが……";
		mes "息子夫婦は既に息絶えた後でした……";
		next;
		mes "[マクシーミリアン]";
		mes "息子夫婦は発見される少し前まで";
		mes "生きていたようです。";
		mes "最後まで戦い、戦闘の末、";
		mes "苦しみの中で息絶えたと思うと……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "…………";
		next;
		mes "[マクシーミリアン]";
		mes "子ども達には息子夫婦の詳細は";
		mes "できるだけ伏せましたが、";
		mes "息を引き取ってしまった事は";
		mes "言わざるを得ませんでした。";
		next;
		mes "[マクシーミリアン]";
		mes "親を亡くした孫達、";
		mes "息子夫婦を失った私は";
		mes "こうして";
		mes "一緒に暮らすようになりました。";
		next;
		mes "[マクシーミリアン]";
		mes "私はレベンブルグ家の名に";
		mes "相応しい人間になるよう、";
		mes "子どもたちを厳しく教育しました。";
		mes "……ですが子ども達に必要だったのは、";
		mes "厳しい躾ではなく";
		mes "暖かいふれあいだったのです。";
		next;
		mes "[マクシーミリアン]";
		mes "私はそんなことにも気付かず、";
		mes "厳しいルールを守るよう";
		mes "子どもたちに強制しました。";
		next;
		mes "[マクシーミリアン]";
		mes "子ども達には辛い日々だったのでしょう。";
		mes "いつだったか、子ども達は";
		mes "反抗するかのように";
		mes "皆で家出をしました。";
		next;
		mes "[マクシーミリアン]";
		mes "子ども達は今でも家出の話は";
		mes "あまりしたがりません。";
		mes "ですがその時に見て聞いたものは";
		mes "多くの影響を与えたようです。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……たとえば……？";
		next;
		mes "[マクシーミリアン]";
		mes "ヘルムトは自己鍛錬の日々を送り、";
		mes "機が熟すと国境の戦場に向いました。";
		mes "ヴォルフはいきなり";
		mes "商売をすると言い出しました。";
		next;
		mes "[マクシーミリアン]";
		mes "それまで我が家には";
		mes "商人はいませんでした。";
		mes "武門の誉れが高い";
		mes "レベンブルグの名のもとに";
		mes "商売は許されないと話しても、";
		mes "聞く耳を持ちませんでした。";
		next;
		mes "[マクシーミリアン]";
		mes "マイアーは家出から戻って暫くの間は";
		mes "家でじっとしていましたが、";
		mes "その後メモを残して出て行きました。";
		mes "アグネスだけは家出前と変わらず、";
		mes "その後も過ごしていました。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "それぞれが求めていたことに";
		mes "そんな事情があったのですね。";
		mes "噂ではその部分は";
		mes "語られませんでしたが。";
		next;
		mes "[マクシーミリアン]";
		mes "そうですね。";
		mes "噂の件は";
		mes "マイアーが責任を取ると";
		mes "言っていましたので、";
		mes "その内に収まるでしょう。";
		next;
		mes "[マクシーミリアン]";
		mes "ところで冒険者様、";
		mes "一つ頼まれていただけますか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "なんでしょう。";
		next;
		mes "[マクシーミリアン]";
		mes "^0000cdヘルムトが";
		mes "何も言わずに去ったのが気になります。^000000";
		next;
		mes "[マクシーミリアン]";
		mes "まだ宮殿にいて欲しかったのですが、";
		mes "勝手にいなくなってしまったので";
		mes "正直困ってます。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "それでは、ヘルムト様を";
		mes "ここへお連れしましょう。";
		next;
		mes "[マクシーミリアン]";
		mes "そうですね。恐らく、";
		mes "^0000cdシュバルツバルドとの国境付近にある";
		mes "国境検問所^000000にいるでしょう。";
		next;
		mes "[マクシーミリアン]";
		mes "準備が出来次第、";
		mes "私に声をかけてください。";
		mes "現地まで使いの者に案内させましょう。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "はい、それでは。";
		delquest 14503;
		setquest 14504;
		set EP16_6QUE,10;
		close;
	case 10:
	case 11:
	case 12:
	case 13:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "幼い頃には";
		mes "兄弟皆仲が良かったのです。";
		mes "ヘルムト兄さんとマイアーも。";
		next;
		mes "[ヴォルフ]";
		mes "アグネスは末っ子で";
		mes "たった一人の妹だったので、";
		mes "みんな可愛がりました。";
		next;
		mes "[ヴォルフ]";
		mes "いつからこうなってしまったのか……";
		mes "たまに考えます。";
		next;
		mes "[ヴォルフ]";
		mes "大人になるにつれて";
		mes "それぞれ望むものが違い、";
		mes "正しいと思うものが違った……";
		mes "そんなところでしょう。";
		mes "何となく解ります。";
		next;
		mes "[ヴォルフ]";
		mes "マイアーが家を出て行ってしまった時は";
		mes "やはりショックでしたね。";
		mes "一番近い家族が何も告げずに";
		mes "出て行ってしまったのですから。";
		next;
		mes "[ヴォルフ]";
		mes "その時からですね。私も";
		mes "自分ができることを探し始めたのは。";
		mes "私だけ置いてけぼりになるのは";
		mes "嫌でしたから。";
		next;
		mes "[ヴォルフ]";
		mes "人間は何か足りないものがあると";
		mes "本能的にそれを";
		mes "埋めようとする……";
		mes "そんなところでしょうか。";
		next;
		mes "[ヴォルフ]";
		mes "私はこれからも前に進んでいきます。";
		mes "私が求めるものを見つける為に。";
		close2;
		cutin "16wol_nor.bmp",255;
		end;
	case 14:
		cutin "16wol_nor.bmp",2;
		mes "[ヴォルフ]";
		mes "冒険者様のおかげで";
		mes "私たち兄弟の仲が";
		mes "少し昔のように近くなった気がします。";
		mes "今まではお互いに譲ることが出来ず、";
		mes "意地を張っていました。";
		next;
		mes "[ヴォルフ]";
		mes "兄弟とは互いにぶつかり、理解し、";
		mes "成長してゆくものなのでしょう。";
		mes "あまりにも長い間離れていたので";
		mes "当たり前の事さえ";
		mes "忘れてしまっていたようです。";
		next;
		mes "[ヴォルフ]";
		mes "これからは祖父を助け";
		mes "レベンブルグ家を立て直してみます。";
		mes "冒険者様も";
		mes "たまにはいらしてくださいね。";
		mes "いつでも歓迎しますよ。";
		close2;
		cutin "16wol_nor.bmp",255;
		end;
	}
	end;
}

prt_cas_q.gat,96,184,1	script	アグネス・レベンブルグ#ep16lug	10130,{
	switch(EP16_6QUE) {
	case 0:
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "あら、どのようなご用件でしょうか？";
		mes "おじい様にお会いになる方でしょうか。";
		next;
		mes "[アグネス]";
		mes "それでしたら、あちらです。";
		mes "どうぞ、楽しい時間を";
		mes "お過ごしくださいね。";
		close2;
		cutin "16agn_nor.bmp",255;
		end;
	case 1:
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "お兄様たちにはお会いになりましたか？";
		mes "まだならヴォルフ兄様とぜひお話を。";
		next;
		mes "[アグネス]";
		mes "最近はおじい様と二人で";
		mes "レベンブルグ家の多くを";
		mes "把握しておりますので、";
		mes "興味深い話も聞けると思います。";
		next;
		mes "[アグネス]";
		mes "……そのせいか、";
		mes "わたくしとお話してくださる時間は";
		mes "あまりないのですけども……";
		close2;
		cutin "16agn_nor.bmp",255;
		end;
	case 2:
	case 3:
	case 4:
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "祝宴はもう始まってしまったのに";
		mes "一緒に行く方が";
		mes "まだ決まっておりませんの！";
		next;
		mes "[アグネス]";
		mes "本当はヴォルフお兄様と";
		mes "ご一緒するはずでしたのに、";
		mes "お忙しくて";
		mes "ダメになってしまいましたわ。";
		next;
		mes "[アグネス]";
		mes "マイアー兄が";
		mes "一緒に行ってくださるそうですが、";
		mes "いつまた出て行ってしまうか";
		mes "とても心配ですの……";
		next;
		mes "[アグネス]";
		mes "わたくしが望んでいるのは";
		mes "ほんの小さな幸せですのに。";
		mes "幼い頃はお兄様方もみんな仲良く、";
		mes "わたくしと遊んでくださいましたわ。";
		mes "本もたくさん読んでいただいて";
		mes "とても楽しかった……";
		next;
		mes "[アグネス]";
		mes "わたくしは今でも";
		mes "お兄様方と読んだ本が大好きですの。";
		mes "本から出た王子様、お姫様、";
		mes "そして動物やたくさんの人々は";
		mes "わたくしの大切なお友達ですのよ。";
		next;
		mes "[アグネス]";
		mes "お姫様に誓いを立てる騎士の物語も";
		mes "読みましたわ。";
		mes "そのお話でお姫様が騎士に";
		mes "綺麗なハンカチを渡すシーンが";
		mes "ありましたの。";
		next;
		mes "[アグネス]";
		mes "そのシーンがとても素敵で、";
		mes "わたくしもこうやって";
		mes "ハンカチを持ち歩くように";
		mes "なりましたのよ。";
		next;
		mes "[アグネス]";
		mes "誓いの騎士様が現れてくだされば";
		mes "いつでもハンカチを手渡せるように。";
		mes "けれど、残念なことに";
		mes "まだ騎士様にお会いできていませんの。";
		close2;
		cutin "16agn_nor.bmp",255;
		end;
	case 5:
	case 6:
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "冒険者様もご覧になりましたか?!";
		mes "マイアー兄と一緒にいらした方！";
		next;
		mes "[アグネス]";
		mes "素敵な方……一体どなたかしら。";
		mes "すぐに去ってしまわれたので";
		mes "お話もできませんでしたわ……";
		close2;
		cutin "16agn_nor.bmp",255;
		end;
	case 7:
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "冒険者様？　冒険者様？";
		mes "ヴォルフお兄様が";
		mes "冒険者様を探しておりましたわ。";
		mes "お会いになる約束を";
		mes "されていたのですね。";
		next;
		mes "[アグネス]";
		mes "さあ、ヴォルフお兄様が";
		mes "お待ちしておりますわ。";
		mes "いらして欲しいと言っていましたわ。";
		close2;
		cutin "16agn_nor.bmp",255;
		end;
	case 8:
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "まったくもう！";
		mes "お兄様方ったら、本当に";
		mes "まだまだ子どもですのね。";
		next;
		mes "[アグネス]";
		mes "プロンテラの広場で遊んでいる";
		mes "ちいさな子ども達に聞いても";
		mes "答えられる問題ですのに！";
		next;
		mes "[アグネス]";
		mes "個人的な欲望に目がくらんで";
		mes "真意を見極められないようでは……";
		mes "わたくしだって、復讐したいと";
		mes "思った時もありましたが、";
		mes "それで解決する問題では";
		mes "ありませんから。";
		next;
		mes "[アグネス]";
		mes "王国市民のみなさんが";
		mes "日々幸せに送るにはどうすればいいか、";
		mes "少しでも考えたなら";
		mes "このような結論なんて";
		mes "最初から出るはずがありませんわ。";
		next;
		mes "[アグネス]";
		mes "……今は少し";
		mes "考えを改めておられるようですし、";
		mes "わたくしも見守ることにします……";
		close2;
		cutin "16agn_nor.bmp",255;
		end;
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		cutin "16agn_nor.bmp",2;
		mes "[アグネス]";
		mes "お兄様方とはお会いになりましたか？";
		next;
		mes "[アグネス]";
		mes "久しぶりに我が家に活気が戻って";
		mes "嬉しく思いますの。";
		mes "たとえ居場所が離れ離れでも、";
		mes "今後、お兄様方はお互いに";
		mes "刃を向けることは無さそうで";
		mes "ほっとしておりますわ。";
		close2;
		cutin "16agn_nor.bmp",255;
		end;
	case 14:
		if(checkquest(14509)) {
			if(checkquest(14509)&2) {
				cutin "16agn_ang.bmp",2;
				mes "[アグネス]";
				mes "冒険者様！　大変ですわ！";
				mes "除湿剤の効果が";
				mes "切れてしまいましたの！";
				next;
				mes "[アグネス]";
				mes "こうしている間にも";
				mes "刻一刻とカビが私のドレスを";
				mes "蝕んでいきますわ！";
				mes "早く^0000cd除湿剤^000000を用意しないと！";
				next;
				if(select("除湿剤を持って来る","今は忙しい")==2) {
					cutin "16agn_nor.bmp",2;
					mes "[アグネス]";
					mes "そうですか……";
					mes "仕方ありませんわ。";
					mes "ああ……";
					mes "どうすればいいんですの……。";
					close2;
					cutin "16agn_nor.bmp",255;
					end;
				}
				cutin "16agn_nor.bmp",2;
				mes "[アグネス]";
				mes "ああ……冒険者様は";
				mes "本当にお優しいのですね。";
				mes "今回もその優しさに";
				mes "甘えさせていただきますわ。";
				next;
				mes "[アグネス]";
				mes "それでは^0000cd除湿剤を2個^000000";
				mes "持って来ていただきたいですわ。";
				mes "それが無いと安心してドレスを";
				mes "しまうことができませんわ。";
				next;
				mes "[アグネス]";
				mes "それではお願いいたしますわ。";
				mes "お気をつけて！";
				delquest 14509;
				setquest 14508;
				close2;
				cutin "16agn_nor.bmp",255;
				end;
			} else {
				cutin "16agn_nor.bmp",2;
				mes "[アグネス]";
				mes "冒険者様、来てくださったのですね！";
				mes "おかげ様でいただいた除湿剤が";
				mes "グングン湿気を吸い取っていますわ！";
				next;
				mes "[アグネス]";
				mes "もし効果が無くなってしまったら";
				mes "また持って来てくださいますか？";
				mes "その時はまたいらしてくれると";
				mes "嬉しいですわ。";
				close2;
				cutin "16agn_nor.bmp",255;
				end;
			}
		}
		if(!checkquest(14508)) {
			cutin "16agn_ang.bmp",2;
			mes "[アグネス]";
			mes "冒険者様!!";
			mes "良いところにいらっしゃいました！";
			mes "大変ですの！";
			next;
			cutin "16agn_nor.bmp",255;
			mes "["+strcharinfo(0)+"]";
			mes "何事ですか？";
			mes "もしや侵入者!?";
			mes "それとも兄弟喧嘩の続きでも";
			mes "ありましたか!?";
			next;
			cutin "16agn_ang.bmp",2;
			mes "[アグネス]";
			mes "いいえ!!　そのような";
			mes "小さな事ではありませんの！";
			mes "冒険者様の助けが必要ですの！";
			next;
			cutin "16agn_ang.bmp",255;
			mes "["+strcharinfo(0)+"]";
			mes "!!";
			mes "何か大きな戦闘があるのですね！";
			mes "それでは準備をしてきますので";
			mes "少々お待ちください。";
			next;
			cutin "16agn_nor.bmp",2;
			mes "[アグネス]";
			mes "はい？";
			next;
			cutin "16agn_nor.bmp",255;
			mes "["+strcharinfo(0)+"]";
			mes "……はい？";
			next;
			cutin "16agn_nor.bmp",2;
			mes "[アグネス]";
			mes "なぜ戦闘の準備をなさいますの？";
			next;
			cutin "16agn_nor.bmp",255;
			mes "["+strcharinfo(0)+"]";
			mes "大変だとお話になったので……";
			mes "戦闘ではないのですか？";
			next;
			cutin "16agn_nor.bmp",2;
			mes "[アグネス]";
			mes "……えっと……ゴホン。";
			mes "人が生きる際にある大変なことは";
			mes "戦闘だけではありませんことよ。";
			next;
			cutin "16agn_nor.bmp",255;
			mes "["+strcharinfo(0)+"]";
			mes "……では一体何が？";
			next;
			cutin "16agn_nor.bmp",2;
			mes "[アグネス]";
			mes "実は祝宴に着ていくための";
			mes "ドレスをクローゼットに";
			mes "しまっていたんですの。";
			next;
			cutin "16agn_ang.bmp",2;
			mes "[アグネス]";
			mes "でも、気づいてしまいましたの。";
			mes "このクローゼットには^ff0000除湿剤^000000が";
			mes "置いて無かったんですの！";
			next;
			mes "[アグネス]";
			mes "このままではせっかく用意した";
			mes "ドレスがカビだらけに";
			mes "なってしまいますの。";
			mes "そんなことになったら";
			mes "祝宴に参加することが";
			mes "できなくなってしまいますわ。";
			next;
			cutin "16agn_nor.bmp",2;
			mes "[アグネス]";
			mes "そこで冒険者様にお願いが";
			mes "ございますの。";
			next;
			if(select("除湿剤を持って来ればいいんですね？","急用を思い出しました")==2) {
				cutin "16agn_nor.bmp",2;
				mes "[アグネス]";
				mes "そうですか……";
				mes "仕方ありませんわ。";
				mes "話を聞いてくださって";
				mes "ありがとうございます。";
				close2;
				cutin "16agn_nor.bmp",255;
				end;
			}
			cutin "16agn_nor.bmp",2;
			mes "[アグネス]";
			mes "まあ！";
			mes "私が言う前にお願いの内容を";
			mes "当ててしまうなんて、";
			mes "さすがは冒険者様ですの！";
			mes "すごいですわ！";
			next;
			mes "[アグネス]";
			mes "それでは^0000cd除湿剤を2個^000000";
			mes "持って来ていただきたいですわ。";
			mes "それが無いと安心してドレスを";
			mes "しまうことができませんわ。";
			next;
			mes "[アグネス]";
			mes "お願いを聞いてくれて";
			mes "ありがとうございます。";
			mes "では、よろしくお願いいたしますわ！";
			setquest 14508;
			close2;
			cutin "16agn_nor.bmp",255;
			end;
		} else {
			cutin "16agn_nor.bmp",2;
			if(countitem(6921) < 2) {
				mes "[アグネス]";
				mes "^0000cd除湿剤を2個^000000";
				mes "持って来ていただきたいですわ。";
				mes "それが無いと安心してドレスを";
				mes "しまうことができませんわ。";
				next;
				mes "[アグネス]";
				mes "それではお願いいたしますわ。";
				mes "お気をつけて！";
				close2;
				cutin "16agn_nor.bmp",255;
				end;
			}
			mes "[アグネス]";
			mes "ああ！";
			mes "持ってきてくださったんですね。";
			mes "ありがとうございます！";
			mes "やっぱり冒険者様はすごいですわ！";
			next;
			mes "[アグネス]";
			mes "これで安心してドレスを";
			mes "クローゼットにしまうことが";
			mes "できますわ！";
			mes "ありがとうございます！";
			next;
			mes "[アグネス]";
			mes "冒険者様、";
			mes "これはわたくしの感謝の印です。";
			mes "どうぞお受けとりくださいね。";
			next;
			if(checkitemblank() == 0) {	// 未調査
				mes "‐荷物をこれ以上持てません";
				mes "　荷物に1個以上の空きを";
				mes "　作ってください‐";
				close;
			}
			mes "[アグネス]";
			mes "それと……もしよければ、";
			mes "また除湿効果が無くなったら";
			mes "お願いしてもよろしいでしょうか？";
			mes "ここは湿気が強くて除湿剤が";
			mes "すぐに駄目になってしまいますの。";
			delitem 6921,2;
			delquest 14508;
			setquest 14509;
			getitem 6919,2;
			close2;
			cutin "16agn_nor.bmp",255;
			end;
		}
	}
}

prontera.gat,267,67,3	script	子ども#ep16lug01	975,{
	switch(EP16_6QUE) {
	case 0:
	case 1:
	case 2:
	case 3:
		mes "[エレン]";
		mes "汝、我らに用か？";
		mes "我らは資格なき者と話す口は持たぬ。";
		mes "立ち去るがよい。";
		close;
	case 4:
		mes "[エレン]";
		mes "……今日は風が冷たいな。";
		mes "……風に腐臭が混じっている……";
		mes "今日もどこかで争いの痕跡が";
		mes "鼻をくすぐるのか……";
		next;
		emotion 40,"子ども#ep16lug02";
		mes "[ジン]";
		mes "おっとごめん。";
		mes "その匂い僕だ。";
		next;
		mes "[エレン]";
		mes "……そうか……";
		mes "これもまた試練の一つか……";
		next;
		emotion 6,"子ども#ep16lug03";
		mes "[ヘリオット]";
		mes "……二人ともやめなよ。";
		mes "話を聞いていると頭が痛くなる。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "あのさ、";
		mes "ちょっと聞きたいことがあるんだけど。";
		mes "何か面白い噂話ってある？";
		next;
		mes "[エレン]";
		mes "……ふっ、依頼か。";
		next;
		mes "[ジン]";
		mes "面白い話？";
		next;
		mes "[ヘリオット]";
		mes "私！　あるある！";
		next;
		mes "[エレン]";
		mes "その依頼、受けよう。";
		mes "汝が求めるものとは何だ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "戦争の話とか、王家の話とかかな？";
		mes "噂になっているみたいだけど、";
		mes "ここに来て日が浅いから";
		mes "詳しくは知らないんだ。";
		next;
		mes "[ジン]";
		mes "あ、僕知ってます。";
		mes "っていうか、みんな知ってます。";
		next;
		mes "[ヘリオット]";
		mes "私が！　私が話す！";
		next;
		mes "[エレン]";
		mes "我も話なら知っている。";
		mes "だが、汝がその話を聞くに値するか";
		mes "我はその資格を問うているのだ。";
		mes "確信というなの資格をな。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "うん？　ああ、何か必要なの？";
		mes "……飴とか？";
		next;
		mes "[ジン]";
		mes "飴……ふう、相手が悪かったですね。";
		mes "僕たちを飴ごときで釣ろうとは。";
		next;
		mes "[ヘリオット]";
		mes "お母さんが知らない人から";
		mes "物を貰っちゃダメだって";
		mes "言ってたんだよ！";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "じゃあ、何だったらいいの？";
		next;
		mes "[エレン]";
		mes "我らに必要なものは代価ではない。";
		mes "この話を聞く資格が";
		mes "汝にあるのかが重要だ。";
		next;
		mes "[ヘリオット]";
		mes "しかく？　なにそれ？";
		mes "エレンってたまに難しい事言うよね。";
		next;
		mes "[ジン]";
		mes "僕としては代価が何かによりますね。";
		mes "何を聞きたいのか";
		mes "先に話してみてくださいよ。";
		mes "まずは提示、そして交渉でしょ？";
		next;
		emotion 4,"";
		mes "["+strcharinfo(0)+"]";
		mes "（子どもだと思って油断したけど、";
		mes "なかなか賢いな……。）";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "代価は何となくわかった。";
		mes "でも資格？　ただの噂話を聞くのに";
		mes "資格が必要なの？";
		next;
		mes "[エレン]";
		mes "それは噂話によるのだ。";
		mes "全ての物事はその身に";
		mes "危険を宿しているからな。";
		next;
		mes "[ヘリオット]";
		mes "その話ってそんなに危険？";
		mes "ジンは知ってた？";
		mes "私はぜんぜん解らないけど。";
		next;
		mes "[ジン]";
		mes "エレンの話ですよ？";
		mes "言ってる事の7割は嘘か、";
		mes "エレンの空想世界の設定です……";
		mes "エレンの言葉が全て真実なら";
		mes "この世はもう12回は滅びてますよ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "そうなんだ。";
		mes "じゃあどうすればその資格を";
		mes "認めてもらえるのかな？";
		mes "あと代価は？";
		next;
		emotion 18,"子ども#ep16lug02";
		mes "[ジン]";
		mes "やっと本論にたどり着きましたね。";
		mes "僕はとりあえずいいもの！";
		next;
		emotion 18,"子ども#ep16lug03";
		mes "[ヘリオット]";
		mes "私！　私はきれいなもの～！";
		next;
		emotion 0,"子ども#ep16lug01";
		mes "[エレン]";
		mes "資格の証明！";
		mes "資格の証明が必要なのだ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "そんな、3人分も用意できないよ。";
		mes "こっちの質問は一つなんだから、";
		mes "そっちも一つにしてくれないかな？";
		next;
		mes "[ジン]";
		mes "うーん、そう言われると";
		mes "反論できませんね。";
		mes "仕方ありません。";
		mes "ここはジャンケンで勝った人の";
		mes "お願いにしましょう。";
		next;
		mes "[ヘリオット]";
		mes "わかったわ！";
		next;
		mes "[エレン]";
		mes "我はパーを出す。";
		next;
		mes "[ジン]";
		mes "それじゃいきますよ。";
		mes "ジャ～ンケ～ン……";
		next;
		mes "[ジン]";
		mes "ポン！";
		emotion 12,"子ども#ep16lug02";
		mes "[ヘリオット]";
		mes "ポン！";
		emotion 11,"子ども#ep16lug03";
		mes "[エレン]";
		mes "グーだ！";
		emotion 11,"子ども#ep16lug01";
		next;
		mes "[ジン]";
		mes "やったー！";
		emotion 18,"子ども#ep16lug02";
		mes "[ヘリオット]";
		mes "えー！";
		emotion 23,"子ども#ep16lug03";
		mes "[エレン]";
		mes "ま、負けた……。";
		emotion 28,"子ども#ep16lug01";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "決まったかい？";
		mes "君は何が必要かな？";
		next;
		mes "[ジン]";
		mes "歴史書！";
		mes "ルーンミッドガッツの歴史が";
		mes "網羅された本だよ！";
		mes "王宮図書館にあるそうだけど、";
		mes "一度も見たことがないんだ。";
		next;
		mes "[ジン]";
		mes "周りには";
		mes "王宮に出入りできる人がいないし、";
		mes "書店ではあつかってないから";
		mes "実物を見たいんだ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……盗めと？";
		next;
		mes "[ジン]";
		mes "牢獄にでもぶち込まれたいんですか？";
		mes "貸し出しでお願いします。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "わかった。";
		mes "それじゃあ行ってくるよ。";
		next;
		mes "[ジン]";
		mes "出来るだけ早くお願いしますね。";
		set EP16_6QUE,5;
		delquest 14498;
		setquest 14499;
		next;
		mes "‐プロンテラ中央宮の";
		mes "　図書館に移動しますか？‐";
		next;
		switch(select("移動する","移動しない")) {
		case 1:
			mes "‐あなたはプロンテラ中央宮の";
			mes "　図書館に向かった‐";
			close2;
			warp "prt_cas.gat",343,63;
			end;
		case 2:
			mes "‐あなたはその場を離れた‐";
			close;
		}
		end;
	case 5:
		mes "[ジン]";
		mes "王宮図書館の";
		mes "^0000cdルーンミッドガッツの歴史^000000を";
		mes "借りて来てください。";
		next;
		mes "‐プロンテラ中央宮の";
		mes "　図書館に移動しますか？‐";
		next;
		if(select("移動する","移動しない") == 2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラ中央宮の";
		mes "　図書館に向かった‐";
		close2;
		warp "prt_cas.gat",343,63;
		end;
	case 6:
		mes "["+strcharinfo(0)+"]";
		mes "これでいいかな？";
		next;
		emotion 18,"子ども#ep16lug02";
		mes "[ジン]";
		mes "ありがとうございます。";
		mes "これでやっと読むことができます。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "それじゃこっちも";
		mes "約束を守ってもらうよ。";
		next;
		mes "[エレン]";
		mes "……戦争、王家、";
		mes "ヘルムト・レベンブルグ。";
		mes "かの者が王になれば、";
		mes "大陸は血の渦に飲み込まれるだろう。";
		next;
		mes "[エレン]";
		mes "暗闇が大陸を多い尽くし、";
		mes "力なき者たちの苦痛が";
		mes "大陸中に広がるだろう。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "それが噂話？";
		mes "でも内容がよく解らないな。";
		mes "わかる人いる？";
		next;
		mes "[ジン]";
		mes "僕が説明しましょう。";
		mes "ヘルムト・レベンブルグが王になれば";
		mes "戦争が起きるという事ですよ。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "それだとちょっと簡略すぎだね？";
		mes "追加で説明を頼んでもいいかな？";
		next;
		mes "[ヘリオット]";
		mes "はい！　私がやります！";
		mes "えっとね、噂話の内容は……";
		next;
		mes "[ヘリオット]";
		mes "ヘルムト・レベンブルグが";
		mes "王になれば……あ、そうだ。";
		mes "レベンブルグ家の噂は知ってる？";
		mes "^0000cd4兄弟の親が死んだ^000000って話。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "いや、初めて聞くね。";
		next;
		mes "[ヘリオット]";
		mes "これもただの噂話なのかも";
		mes "知れませんけど、";
		mes "なんか殺されたらしいの！";
		next;
		mes "[ヘリオット]";
		mes "えっと隣の国にいって？";
		mes "殺されて？";
		mes "だからヘルムト・レベンブルグは";
		mes "ショックを受けて、";
		mes "戦場を彷徨っているって。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "戦場にいたのは本当だけどね。";
		mes "今は王宮にいるそうだよ。";
		next;
		mes "[ヘリオット]";
		mes "王位けいしょう？だよね。";
		mes "噂になっている話もそれなの。";
		next;
		mes "[ヘリオット]";
		mes "^0000cdヘルムトが王になれば^000000、";
		mes "父と母が殺された国に復讐して";
		mes "^0000cd大陸を統一するための戦争^000000を";
		mes "起こすんだって。";
		next;
		mes "[ヘリオット]";
		mes "だからレベンブルグ家の^0000cd次男^000000が";
		mes "戦争に必要なお金を集めるために";
		mes "^0000cd事業^000000をしているんだって。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "結構詳しいんだ？";
		next;
		mes "[ヘリオット]";
		mes "こんなの誰でも知ってるよ！";
		mes "大人も同じことばかり話してるから。";
		next;
		mes "[ジン]";
		mes "僕の親は心配しています。";
		mes "ヘルムトが王になることで";
		mes "戦争が起こる事を。";
		mes "本当はみんな不安なんです。";
		mes "戦争なんて好きな人はいませんよ。";
		next;
		emotion 0,"子ども#ep16lug01";
		mes "[エレン]";
		mes "ふっ……";
		mes "戦場のかぐわしさを知らぬとは……";
		next;
		emotion 54,"子ども#ep16lug02";
		mes "[ジン]";
		mes "あ、こいつはなしで。";
		next;
		emotion 28,"子ども#ep16lug03";
		mes "[ヘリオット]";
		mes "私も戦争は嫌い。";
		mes "こわいもの……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "とにかく、ありがとう。";
		mes "良い話を聞けたよ。";
		next;
		mes "[ヘリオット]";
		mes "うん！　またね！";
		next;
		mes "[ジン]";
		mes "本、ありがとうございました。";
		next;
		mes "[エレン]";
		mes "……男の別れに見送りはいらぬ……";
		delitem 6926,1;
		delquest 14500;
		setquest 14501;
		set EP16_6QUE,7;
		next;
		mes "‐戻ってヴォルフに噂の内容を";
		mes "　伝えよう。";
		mes "　プロンテラ離宮に戻りますか？‐";
		next;
		if(select("戻る","戻らない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラ離宮に";
		mes "　向かった‐";
		close2;
		warp "prt_cas_q.gat",84,188;
		end;
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
		mes "[エレン]";
		mes "汝、資格を証明せし者よ。";
		mes "我の契約の預かり人となるのか？";
		next;
		mes "[エレン]";
		mes "忌むべきして血を呼び覚ます儀式！";
		mes "滅亡は暗黒の意志なりて……";
		next;
		mes "[ジン]";
		mes "また始まった。";
		next;
		mes "[ヘリオット]";
		mes "早く！";
		mes "ここは私たちがなんとかするから！";
		next;
		mes "‐戻ってヴォルフに噂の内容を";
		mes "　伝えよう。";
		mes "　プロンテラ離宮に戻りますか？‐";
		next;
		if(select("戻る","戻らない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラ離宮に";
		mes "　向かった‐";
		close2;
		warp "prt_cas_q.gat",84,188;
		end;
	case 12:
		mes "["+strcharinfo(0)+"]";
		mes "こんにちは～。";
		next;
		mes "[ジン]";
		mes "あれ？冒険者さんだ。";
		mes "ちょうどいいところに！";
		mes "本全部読みました、ありがとう！";
		mes "返しますね！";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ちょっと聞きたいことがあって……";
		mes "レベンブルグ家に関する";
		mes "噂話なんだけど。";
		next;
		mes "[エレン]";
		mes "かの家門にまつわる新しき話はない。";
		mes "無き話を求めることは死せる……";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ああ、新しい噂話じゃなくて、";
		mes "その話をした人を知っているか";
		mes "聞きたいんだ。";
		next;
		mes "[ジン]";
		mes "どうしてですか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "噂を広めた人が誰なのか、";
		mes "探しているんだ。";
		next;
		mes "[ヘリオット]";
		mes "ええ？";
		mes "探したら捕まえるの？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "いや、その人のおじいさんから";
		mes "伝言を頼まれたんだ。";
		next;
		mes "[ヘリオット]";
		mes "え？";
		mes "家族なのに会えないんですか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "うーん、家族だけどね。";
		mes "そうだね。ちょっと会えないかもね。";
		next;
		mes "[ジン]";
		mes "へんなの。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "うん、変だね。";
		mes "でも家族同士でも会うのが難しくて、";
		mes "他の人に頼む必要がある時もあるんだ。";
		next;
		mes "[エレン]";
		mes "そうか……";
		mes "ならば此度は更なる資格の証明がひ……";
		next;
		mes "[ヘリオット]";
		mes "あ！　ちょうど来たよ！";
		mes "ジョナダンおにいちゃん！";
		mes "お客様だよ！";
		next;
		cloakoffnpc "平凡な男#ep16lug02";
		mes "[マイアー]";
		mes "!!!?";
		mes "冒険者様、どうしてここに？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "噂を辿って探すつもりでしたが、";
		mes "ここで会えるとは思いませんでした。";
		next;
		mes "[マイアー]";
		mes "私に会いに？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "はい。";
		mes "マイアー様に伝言があって参りました。";
		next;
		emotion 1,"子ども#ep16lug01";
		mes "[エレン]";
		mes "マイアー?";
		next;
		emotion 1,"子ども#ep16lug02";
		mes "[ジン]";
		mes "マイアー?";
		next;
		emotion 1,"子ども#ep16lug03";
		mes "[ヘリオット]";
		mes "マイアーってだれ？";
		mes "^0000cdジョナダンおにいちゃんがマイアー^000000？";
		mes "ジョナダン？　マイアー？";
		mes "私たちにはジョナダンって言ったよね？";
		next;
		mes "[マイアー]";
		mes "……この子たちには";
		mes "以前にも会いましたね。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "はい、かわいいですよ。";
		mes "おかげさまで少し苦労しましたが。";
		next;
		mes "[ヘリオット]";
		mes "ジョナダン？　マイアー？";
		mes "……マイアー？　ジョナダン？";
		mes "どっちなの？";
		next;
		mes "[マイアー]";
		mes "さあ、冒険者様と私は";
		mes "大事な話があるんだ。";
		mes "少しだけ耳を塞いでくれるかい？";
		mes "少し場をはずしてくれると嬉しいな。";
		next;
		mes "[エレン]";
		mes "開いた耳はふさがらぬ。";
		next;
		mes "[ジン]";
		mes "大事な話なら僕も聞きます！";
		next;
		mes "[ヘリオット]";
		mes "ちょっと！";
		mes "大事な話って言ってるでしょ！";
		mes "はい！　耳塞いで！";
		next;
		mes "[マイアー]";
		mes "みんな良い子だね。";
		mes "話が終わったら";
		mes "甘いキャンディをあげよう。";
		next;
		mes "[エレン]";
		mes "俺の耳には風すら立ち入れぬ。";
		next;
		mes "[ジン]";
		mes "どうぞー。";
		next;
		mes "[ヘリオット]";
		mes "きゃー！　ふふふ、何も聞こえないー！";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……かわいいものですね。";
		mes "賢いし。";
		next;
		mes "[マイアー]";
		mes "そうです。";
		mes "この子達のように、";
		mes "私が導く必要がある人が";
		mes "ここには大勢います。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……簡単ではないですけど";
		mes "大事なことですね。";
		next;
		mes "[マイアー]";
		mes "私は私ができることを";
		mes "しているだけですよ。";
		mes "ところで伝言と言うのは……？";
		next;
		mes "‐マイアーに";
		mes "　ヘルムトの後継者の席譲渡と";
		mes "　二人の兄の戦争放棄に関する話を";
		mes "　伝えた‐";
		next;
		mes "[マイアー]";
		mes "それはよかった。";
		mes "やはり兄さん達は正しい選択を";
		mes "してくれたのですね。";
		next;
		mes "[マイアー]";
		mes "何より^0000cdヴォルフ兄さんが";
		mes "方向転換したのが一番^000000です。";
		mes "本気で闘うことになると";
		mes "かなり面倒ですから。";
		next;
		mes "[マイアー]";
		mes "ヴォルフ兄さんは一度やると言い出すと";
		mes "止まらないんですよ。";
		mes "まあ、そこが長所でもありますが。";
		next;
		mes "[マイアー]";
		mes "はは。信じられないかもしれませんが、";
		mes "私が家族の中で";
		mes "一番信頼を置いている人なんですよ。";
		next;
		mes "[マイアー]";
		mes "ああ、そういえば冒険者様には";
		mes "醜いところを見せてしまいましたね。";
		mes "ほんとうにすみません。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ただの兄弟ゲンカだったのですよね。";
		next;
		mes "[マイアー]";
		mes "そういっていただけると助かります。";
		next;
		mes "[マイアー]";
		mes "これからはちょくちょく帰りますよ。";
		mes "家は窮屈だとばかり思ってましたが、";
		mes "どうやらそうでもないようですしね。";
		mes "私に何かできることがあるなら";
		mes "協力したいと思います。";
		next;
		mes "[マイアー]";
		mes "祝宴が終わったら";
		mes "すぐにでもまた帰ると";
		mes "伝えていただけると助かります。";
		next;
		mes "[マイアー]";
		mes "ああ、そうだ。";
		mes "アグネスも祝宴に一緒に行けなくて";
		mes "申し訳ないと伝えていただけますか。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "はい、伝えます。";
		next;
		mes "[マイアー]";
		mes "冒険者様も何か助けが必要な時は";
		mes "私に言ってくださいね。";
		mes "できる限り助力します。";
		mes "それでは！";
		delquest 14506;
		setquest 14507;
		set EP16_6QUE,13;
		next;
		mes "‐マイアーの意志を伝えに";
		mes "　マクシーミリアンの元へ戻ろう‐";
		next;
		if(select("戻る","戻らない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラ離宮に";
		mes "　向かった‐";
		close2;
		warp "prt_cas_q.gat",84,188;
		end;
	case 13:
		mes "[エレン]";
		mes "戦争の危機が去った。";
		mes "闇から這い出る乱世の英雄の誕生も";
		mes "後世の歴史にのこ……";
		next;
		mes "[ジン]";
		mes "まただ！　また始まった！";
		next;
		mes "[ヘリオット]";
		mes "早く！";
		mes "ここは私たちがなんとかするから！";
		next;
		mes "‐マイアーの意志を伝えに";
		mes "　マクシーミリアンの元へ戻ろう‐";
		next;
		if(select("戻る","戻らない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラ離宮に";
		mes "　向かった‐";
		close2;
		warp "prt_cas_q.gat",84,188;
		end;
	case 14:
		mes "[エレン]";
		mes "戦争の危機が去った。";
		mes "闇から這い出る乱世の英雄の誕生も";
		mes "後世の歴史にのこ……";
		next;
		mes "[ジン]";
		mes "まただ！　また始まった！";
		next;
		mes "[ヘリオット]";
		mes "早く！";
		mes "ここは私たちがなんとかするから！";
		close;
	default:
		mes "‐子どもたちが遊んでいる‐";
		close;
	}
}

prontera.gat,270,68,1	script	子ども#ep16lug02	706,5,5,{
	mes "‐子どもたちが遊んでいる‐";
	close;
OnTouch:
	if(EP16_6QUE > 12) {
		cloakoffnpc "平凡な男#ep16lug02";
	}
	end;
}

prontera.gat,268,69,5	script	子ども#ep16lug03	703,{
	mes "‐子どもたちが遊んでいる‐";
	close;
}

prontera.gat,270,72,3	script(CLOAKED)	平凡な男#ep16lug02	86,{
	if(EP16_6QUE > 12) {
		mes "[マイアー]";
		mes "わざわざ遠い所まで";
		mes "ありがとうございました。";
		mes "冒険者様のおかげで";
		mes "私達兄弟の壁は薄くなった気がします。";
		next;
		mes "[マイアー]";
		mes "互いに争い、傷つけ、戦って……";
		mes "私もそんなものは望んでいません。";
		mes "やはり家族ですから、";
		mes "皆の事は心から大切に思っています。";
		next;
		mes "‐マイアーの意志を伝えに";
		mes "　マクシーミリアンの元へ戻ろう‐";
		next;
		if(select("戻る","戻らない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラ離宮に";
		mes "　向かった‐";
		close2;
		warp "prt_cas_q.gat",84,188;
		end;
	}
	end;
}

yuno_fild01.gat,239,173,7	script	国境守備隊#ep16lug01	734,{}
yuno_fild01.gat,241,173,7	script	国境守備隊#ep16lug02	469,{}
yuno_fild01.gat,243,173,1	script	国境守備隊#ep16lug03	469,{}
yuno_fild01.gat,245,173,1	script	国境守備隊#ep16lug04	734,{}
yuno_fild01.gat,239,171,7	script	国境守備隊#ep16lug05	875,{}
yuno_fild01.gat,241,171,7	script	国境守備隊#ep16lug06	735,{}
yuno_fild01.gat,243,171,1	script	国境守備隊#ep16lug07	735,{}
yuno_fild01.gat,245,171,1	script	国境守備隊#ep16lug08	875,{}

yuno_fild01.gat,242,175,5	script	ヘルムト・レベンブルグ#ep16lug02	10127,{
	switch(EP16_6QUE) {
	case 10:
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "冒険者様？";
		mes "どうしてここにへ？";
		mes "……ここは危険です。";
		next;
		cutin "16hel.bmp",255;
		mes "["+strcharinfo(0)+"]";
		mes "大丈夫です。";
		mes "モンスターとの闘いには慣れています。";
		next;
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "冒険者様が";
		mes "英雄と謳われるほどの戦士であることを";
		mes "失念しておりました。";
		mes "無礼をご容赦ください。";
		mes "ところで、なぜここに……？";
		next;
		cutin "16hel.bmp",255;
		mes "["+strcharinfo(0)+"]";
		mes "ヘルムト様を連れ戻しに来ました。";
		mes "マクシー様が心配しておりました。";
		mes "今は家にいるほうがいいと。";
		next;
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "……せっかく来ていただいたのに";
		mes "申し訳ありませんが、私は戻りません。";
		mes "私がいるべき場所はここです。";
		mes "祖父にはそう伝えてください。";
		next;
		cutin "16hel.bmp",255;
		mes "["+strcharinfo(0)+"]";
		mes "ですが、みなさん心配していますよ。";
		next;
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "……実は私は、幼い頃より死んだ両親を";
		mes "助けなかった人々を";
		mes "許すことができませんでした。";
		next;
		mes "[ヘルムト]";
		mes "その時決意したのです。";
		mes "全ての人が自分に従うよう、";
		mes "大きな力を手に入れようと。";
		mes "その一心で自身を鍛えました。";
		next;
		mes "[ヘルムト]";
		mes "……そしていつしか、";
		mes "大陸全てを統一することが";
		mes "必要だと考えるようになりました。";
		mes "武力による統一……戦争が必要だと。";
		next;
		mes "[ヘルムト]";
		mes "ですが、マイアーとアグネスの言葉で";
		mes "ようやく気づいたのです。";
		mes "私が求める道はまた、";
		mes "誰かの悲しみと憎悪の";
		mes "始まりになるかもしれないと。";
		next;
		mes "[ヘルムト]";
		mes "涙を流し、悲しみに暮れ、";
		mes "憎しみを抱えるのは";
		mes "巻き込まれた罪のない市民だと。";
		mes "それこそ、あの時の父や母、";
		mes "私たちのような人間だ。";
		next;
		mes "[ヘルムト]";
		mes "戦争でもたらす力など";
		mes "何の意味もないと、";
		mes "私はようやく気づきました。";
		next;
		mes "[ヘルムト]";
		mes "だからこそ、今、解ったのです。";
		mes "多くの人々を守るためには力が必要だ。";
		mes "私はこの力を人々の為に使いたい。";
		mes "戦争のためではなく、";
		mes "人々を守るために力を使いたいのです。";
		next;
		mes "[ヘルムト]";
		mes "だから私はここに残ります。";
		mes "遠いところまで足を運んでいただき、";
		mes "申し訳ありませんが、";
		mes "祖父にはそう伝えていただけると";
		mes "嬉しいです。";
		next;
		mes "[ヘルムト]";
		mes "王位継承の事など家の事については、";
		mes "どこにいても家族ですので、";
		mes "私にできる事があれば協力します。";
		next;
		mes "[ヘルムト]";
		mes "ですが、最終的に決断をするのは";
		mes "ヴォルフです。";
		mes "^0000cdレベンブルグ家の後継者の席は";
		mes "ヴォルフにゆだねる^000000と伝えてください。";
		next;
		mes "[ヘルムト]";
		mes "これからヴォルフには";
		mes "多くの力が必要となるでしょう。";
		mes "私はここを守り、";
		mes "そしてヴォルフの為にも";
		mes "尽力しましょう。";
		next;
		mes "[ヘルムト]";
		mes "そうすれば、";
		mes "ヴォルフも戦争に執着することなく、";
		mes "マイアーもアグネスも";
		mes "戦争に怯えず日々を過ごす事ができる。";
		mes "いつしか兄弟で協力し、";
		mes "支えあう日が来ることでしょう。";
		next;
		cutin "16hel.bmp",255;
		mes "["+strcharinfo(0)+"]";
		mes "……わかりました。";
		mes "マクシー様にお伝えします。";
		next;
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "ありがとうございます。";
		mes "お願いいたします。";
		delquest 14504;
		setquest 14505;
		set EP16_6QUE,11;
		next;
		cutin "16hel.bmp",255;
		mes "‐ヘルムトの意志を伝えに";
		mes "　マクシーミリアンの元へ戻ろう‐";
		next;
		if(select("戻る","戻らない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラ離宮に";
		mes "　向かった‐";
		close2;
		warp "prt_cas_q.gat",84,188;
		end;
	case 11:
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "私がいるべき場所はここです。";
		mes "^0000cdレベンブルグ家の後継者の席は";
		mes "ヴォルフにゆだねる^000000と伝えてください。";
		next;
		mes "[ヘルムト]";
		mes "そうすれば、";
		mes "ヴォルフも戦争に執着することなく、";
		mes "マイアーもアグネスも";
		mes "戦争に怯えず日々を過ごす事ができる。";
		mes "いつしか兄弟で協力し、";
		mes "支えあう日が来ることでしょう。";
		next;
		cutin "16hel.bmp",255;
		mes "‐ヘルムトの意志を伝えに";
		mes "　マクシーミリアンの元へ戻ろう‐";
		next;
		if(select("戻る","戻らない")==2) {
			mes "‐あなたはその場を離れた‐";
			close;
		}
		mes "‐あなたはプロンテラ離宮に";
		mes "　向かった‐";
		close2;
		warp "prt_cas_q.gat",84,188;
		end;
	default:
		cutin "16hel.bmp",0;
		mes "[ヘルムト]";
		mes "地鳴りがする……襲撃が近そうだ。";
		mes "全員戦闘準備を怠るな！";
		close2;
		cutin "16hel.bmp",255;
		end;
	}
}

yuno_fild01.gat,244,176,3	script	カルベルン#ep16lug02	962,{
	switch(EP16_6QUE) {
	case 10:
		mes "[カルベルン]";
		mes "ヘルムト様は";
		mes "戦争はなさらないと決めたそうです。";
		mes "本当によかったです。";
		mes "ヘルムト様の意思は尊重しますが、";
		mes "戦争は良いものではありませんから。";
		next;
		mes "[カルベルン]";
		mes "これからはここでヘルムト様を助け、";
		mes "人々の安全と平和を守るため、";
		mes "皆と尽力したいと思います。";
		close;
	case 11:
		mes "[カルベルン]";
		mes "やっと戦場に帰ってこれました。";
		mes "私がやるべき事があるこの場所へ。";
		next;
		mes "[カルベルン]";
		mes "ヘルムト様は";
		mes "戦争はなさらないと決めたそうです。";
		mes "本当によかったです。";
		mes "ヘルムト様の意思は尊重しますが、";
		mes "戦争は良いものではありませんから。";
		next;
		mes "[カルベルン]";
		mes "これからはここでヘルムト様を助け、";
		mes "人々の安全と平和を守るため、";
		mes "皆と尽力したいと思います。";
		close;
	default:
		mes "[カルベルン]";
		mes "ヘルムト様の";
		mes "お飲み物の準備をしなくては。";
		close;
	}
}

prt_cas.gat,85,223,1	script	マクシーミリアン#ep16wig01	10133,{
	mes "[マクシーミリアン]";
	mes "最近、我が家のヴォルフが";
	mes "ウィグナー様のお世話になっていると";
	mes "聞いていますよ。";
	next;
	mes "[ルヴィエル]";
	mes "そんなことは！";
	mes "我が家のアイザックのほうが、";
	mes "レベンブルグ家の聡明さを";
	mes "受け継いだヴォルフ様から";
	mes "色々と学んでいると聞きました。";
	mes "ははは！";
	next;
	mes "[カタリナ]";
	mes "どうかアイザックを";
	mes "よろしくお願いいたします。";
	close;
}

prt_cas.gat,104,231,3	script	祝宴場のお客様#ep16wig01	817,{
	mes "[祝宴場のお客様]";
	mes "祝宴に来るのは";
	mes "いつも楽しいです！";
	mes "他国の文化に触れ合う";
	mes "機会ですからね！";
	mes "しかも美味しい料理とお酒まで！";
	close;
}

prt_cas.gat,103,232,3	script	祝宴場のお客様#ep16wig0	824,{
	mes "[祝宴場のお客様]";
	mes "ふぅ……祝宴は疲れます。";
	mes "まだ旅の疲れも癒えてないのに。";
	mes "本当に人が多いですね。";
	close;
}

prt_cas.gat,81,235,3	script	祝宴場のお客様#ep16wig02	478,{
	mes "[祝宴場のお客様]";
	mes "ルーンミッドガッツ王国の城は";
	mes "大きく華やかですね。";
	mes "異国の情緒を感じられます。";
	mes "ここまで来るのは大変でしたが";
	mes "来てよかったですよ。";
	close;
}

prt_cas.gat,79,219,7	script	祝宴場のお客様#ep16wig03	583,{
	mes "[祝宴場のお客様]";
	mes "ああっ！　冒険者様じゃないですか！";
	mes "ポートマラヤにも来てくださいね！";
	mes "みんな歓迎しますよ！";
	close;
}

prt_cas.gat,88,246,7	script	祝宴場のお客様#ep16wig04	839,{
	mes "[祝宴場のお客様]";
	mes "ここの楽団の演奏は";
	mes "心に響きますね。";
	mes "遠くから来た甲斐があります。";
	close;
}

prt_cas.gat,114,226,5	script	祝宴場のお客様#ep16wig05	537,{
	mes "[祝宴場のお客様]";
	mes "ここの花ってみんな";
	mes "このように光るのですか？";
	mes "不思議ですね。";
	close;
}

prt_cas.gat,87,231,5	script	祝宴場のお客様#ep16wig06	778,{
	mes "[祝宴場のお客様]";
	mes "昔、一度だけ";
	mes "王宮に来たことがありますが……";
	mes "ずいぶんと変わりましたね。";
	mes "さらに大きく優雅になりました。";
	next;
	mes "[祝宴場のお客様]";
	mes "今は、国王が空位の状態だなんて";
	mes "言われても信じられませんよ。";
	close;
}

prt_cas.gat,86,251,5	script	祝宴場のお客様#ep16wig07	967,{
	mes "[祝宴場のお客様]";
	mes "ここは人が多いですね。";
	mes "あまりに多くてめまいがします。";
	mes "でもこういう活気はいいですね。";
	close;
}

prt_cas_q.gat,81,131,0	script	#ep16_1ゲオルグ	139,5,5,{
	end;
OnTouch:
	if(EP16_1QUE >= 2 && EP16_2QUE == 0) {
		mes "[マーティン]";
		mes "そこ！　止まりなさい！";
		unittalk getnpcid(0,"ゲオルグ家守護騎士#ep16_1_m"),"ゲオルグ家守護騎士 : そこ！　止まりなさい！",1;
		emotion 0,"ゲオルグ家守護騎士#ep16_1_m";
		emotion 0,"ゲオルグ家守護騎士#ep16_1_g";
		next;
		mes "[マーティン]";
		mes "王妃様に近づく者には";
		mes "先に身体検査を受けていただく！";
		mes "まずは身分を証明できるものと";
		mes "所持品をすべて";
		mes "このテーブルの上に乗せろ。";
		next;
		mes "[マーティン]";
		mes "それができたら、";
		mes "壁に手をつき……";
		next;
		mes "[ジェラード]";
		mes "マーティン！　やめろ！";
		mes "部屋を訪ねて来るお客様に";
		mes "無礼な態度をとるなと";
		mes "言っただろう!?";
		emotion 23,"ゲオルグ家守護騎士#ep16_1_g";
		next;
		mes "[マーティン]";
		mes "ふん、王妃様の安全のためだ。";
		next;
		mes "[ジェラード]";
		mes "確かに王妃様の安全を守るのが";
		mes "我らの仕事だ。";
		mes "だが、それはお客様に";
		mes "無礼な態度をとったり、";
		mes "追い出せということではないぞ。";
		emotion 7,"ゲオルグ家守護騎士#ep16_1_g";
		next;
		mes "[マーティン]";
		mes "そんな甘い考えで";
		mes "王妃様を守れるわけないだろう！";
		next;
		mes "[ジェラード]";
		mes "……確かに今、この城は";
		mes "王位継承で殺伐としている。";
		mes "だが、そんな状況でも";
		mes "俺たちに出来ることは";
		mes "限られているんだ。";
		next;
		mes "[マーティン]";
		mes "それに王妃様の";
		mes "ゲオルグ家は……";
		emotion 9,"ゲオルグ家守護騎士#ep16_1_m";
		next;
		mes "[王妃]";
		mes "なにを騒いでいらっしゃるの？";
		cutin "ep16gao_1.bmp",2;
		next;
		cutin "ep16gao_1.bmp",255;
		mes "[ジェラード]";
		mes "はっ！　王妃様！";
		mes "申し訳ございません。";
		mes "お客様がいらっしゃいました。";
		emotion 0,"ゲオルグ家守護騎士#ep16_1_g";
		setquest 11400;
		set EP16_2QUE,1;
		close;
	}
	end;
}

prt_cas_q.gat,93,129,3	script	王妃#ep16_1	10121,{
	switch(EP16_2QUE) {
	case 0:
		mes "[マーティン]";
		mes "そこ！　止まりなさい！";
		unittalk getnpcid(0,"ゲオルグ家守護騎士#ep16_1_m"),"ゲオルグ家守護騎士 : そこ！　止まりなさい！",1;
		emotion 0,"ゲオルグ家守護騎士#ep16_1_m";
		emotion 0,"ゲオルグ家守護騎士#ep16_1_g";
		next;
		mes "[マーティン]";
		mes "王妃様に近づく者には";
		mes "先に身体検査を受けていただく！";
		mes "まずは身分を証明できるものと";
		mes "所持品をすべて";
		mes "このテーブルの上に乗せろ。";
		next;
		mes "[マーティン]";
		mes "それができたら、";
		mes "壁に手をつき……";
		next;
		mes "[ジェラード]";
		mes "マーティン！　やめろ！";
		mes "部屋を訪ねて来るお客様に";
		mes "無礼な態度をとるなと";
		mes "言っただろう!?";
		emotion 23,"ゲオルグ家守護騎士#ep16_1_g";
		next;
		mes "[マーティン]";
		mes "ふん、王妃様の安全のためだ。";
		next;
		mes "[ジェラード]";
		mes "確かに王妃様の安全を守るのが";
		mes "我らの仕事だ。";
		mes "だが、それはお客様に";
		mes "無礼な態度をとったり、";
		mes "追い出せということではないぞ。";
		emotion 7,"ゲオルグ家守護騎士#ep16_1_g";
		next;
		mes "[マーティン]";
		mes "そんな甘い考えで";
		mes "王妃様を守れるわけないだろう！";
		next;
		mes "[ジェラード]";
		mes "……確かに今、この城は";
		mes "王位継承で殺伐としている。";
		mes "だが、そんな状況でも";
		mes "俺たちに出来ることは";
		mes "限られているんだ。";
		next;
		mes "[マーティン]";
		mes "それに王妃様の";
		mes "ゲオルグ家は……";
		emotion 9,"ゲオルグ家守護騎士#ep16_1_m";
		next;
		mes "[王妃]";
		mes "なにを騒いでいらっしゃるの？";
		cutin "ep16gao_1.bmp",2;
		next;
		cutin "ep16gao_1.bmp",255;
		mes "[ジェラード]";
		mes "はっ！　王妃様！";
		mes "申し訳ございません。";
		mes "お客様がいらっしゃいました。";
		emotion 0,"ゲオルグ家守護騎士#ep16_1_g";
		setquest 11400;
		set EP16_2QUE,1;
		close;
	case 1:
		mes "[キャサリン]";
		mes "ようこそいらっしゃいました。";
		mes "わたくしはこの国の王妃、";
		mes "キャサリン・ゲオルグ。";
		cutin "ep16gao_2.bmp",2;
		next;
		menu "ご挨拶に伺いました",-;
		mes "[キャサリン]";
		mes "騎士たちの無礼、";
		mes "お詫びしますわ。";
		mes "祝宴の開催に、王位継承と続いて";
		mes "皆も敏感になっているようです。";
		mes "どうか、ご理解くださいまし。";
		emotion 17,"王妃#ep16_1";
		cutin "ep16gao_1.bmp",2;
		next;
		menu "王位継承について聞く",-;
		cutin "ep16gao_1.bmp",2;
		mes "[キャサリン]";
		mes "ああ、そうでしたわね。";
		mes "遠征、魔王モロク討伐と";
		mes "多大な貢献をされたあなたに";
		mes "王位継承の儀式立ち合いを";
		mes "お願いしましたもの。";
		next;
		mes "[キャサリン]";
		mes "各家門に話を";
		mes "お聞きしたいことでしょう。";
		mes "わたくしはゲオルグ家について";
		mes "答えればよろしいかしら。";
		next;
		mes "[キャサリン]";
		mes "ゲオルグ家は";
		mes "建国の英雄トリスタン1世の子孫で、";
		mes "代々多くの王と騎士たちを世に出した";
		mes "現王家です。";
		next;
		mes "[キャサリン]";
		mes "以前行われた";
		mes "^0000ff次期国王選出の審査時^000000にも、";
		mes "ゲオルグ家からは";
		mes "^0000ff第四王子であるエルンスト^000000が";
		mes "候補として選ばれていましたわ。";
		next;
		mes "[キャサリン]";
		mes "今は、違いますけれど……";
		next;
		menu "違うとは？",-;
		mes "[キャサリン]";
		mes "……あらあら、";
		mes "わたくしとしたことが";
		mes "失言をしてしまいましたわね。";
		next;
		mes "[キャサリン]";
		mes "それについては";
		mes "お話しできませんの。";
		mes "聞かなかったことにしてくださいな。";
		cutin "ep16gao_3.bmp",2;
		next;
		mes "[キャサリン]";
		mes "ただ、今回の王位継承に";
		mes "^0000ffゲオルグ家は立候補^000000しませんと";
		mes "理解していただければ。";
		cutin "ep16gao_1.bmp",2;
		next;
		mes "[キャサリン]";
		mes "さて、そろそろ時間のようですわ。";
		mes "ここから先は、";
		mes "ジェラードとマーティンが";
		mes "答えましょう。";
		next;
		mes "[キャサリン]";
		mes "それと、もう祝宴場には";
		mes "顔をお出しになられました？";
		mes "自慢の料理や演奏を";
		mes "用意させましたの。";
		mes "儀式までの間、楽しんでくださると";
		mes "うれしいですわ。";
		cutin "ep16gao_2.bmp",2;
		next;
		mes "[キャサリン]";
		mes "それではわたくしは";
		mes "公務がありますのでこれで。";
		cutin "ep16gao_1.bmp",2;
		next;
		delquest 11400;
		setquest 11401;
		delquest 73056;
		set EP16_2QUE,2;
		if((checkquest(7683)&0x8) && !checkquest(73051) && !checkquest(73053) && !checkquest(73052) && !checkquest(73054) && !checkquest(73055) && !checkquest(73056)) {
			mes "‐^0000cd七王家すべてに挨拶をした。^000000";
			mes "　ベルのところに戻ろう‐";
		} else {
			mes "‐^0000cdゲオルグ家との挨拶を済ました。^000000";
			mes "　他の王家にも挨拶に行こう‐";
		}
		next;
		mes "‐その時、キャサリンが";
		mes "　話しかけてきた‐";
		next;
		cutin "ep16gao_1.bmp",2;
		mes "[キャサリン]";
		mes "そうそう、祝宴会場にも";
		mes "ゲオルグ家の者がおります。";
		mes "エルンストもいるかもしれません。";
		mes "よろしければ、";
		mes "お会いになってください。";
		next;
		mes "‐^0000cdエルンスト王子とゲオルグ家クエスト^000000を";
		mes "　受注した‐";
		close2;
		cutin "ep16gao_1.bmp",255;
		end;
	case 2:
		cutin "ep16gao_1.bmp",2;
		mes "[キャサリン]";
		mes "質問があるようでしたら";
		mes "ここにいるジェラードとマーティンが";
		mes "答えましょう。";
		next;
		mes "[キャサリン]";
		mes "それではわたくしは";
		mes "公務がありますのでこれで。";
		mes "またいつでもいらしてくださいな。";
		close2;
		cutin "ep16gao_1.bmp",255;
		end;
	case 3:
	case 4:
	case 5:
		switch(rand(3)) {
		case 0:
			mes "[キャサリン]";
			mes "モロクからの嘆願書？";
			cutin "ep16gao_1.bmp",2;
			next;
			mes "[キャサリン]";
			mes "……";
			next;
			mes "[キャサリン]";
			mes "すぐに使者を出しましょう。";
			mes "急いで処理をする必要が";
			mes "ありそうですわね。";
			close2;
			cutin "ep16gao_1.bmp",255;
			end;
		case 1:
			mes "[キャサリン]";
			mes "またわたくしのドレスの";
			mes "製作費申請ですの……？";
			mes "毎日違うドレスを着ても";
			mes "余ってしまうほどのドレスを";
			mes "どうしろと言うの……";
			cutin "ep16gao_3.bmp",2;
			next;
			mes "[キャサリン]";
			mes "不許可ですわね。";
			emotion 6;
			cutin "ep16gao_1.bmp",2;
			close2;
			cutin "ep16gao_1.bmp",255;
			end;
		case 2:
			mes "[キャサリン]";
			mes "王室議会で使用する";
			mes "最高級インク台……？";
			mes "使用者はどなたかしら。";
			cutin "ep16gao_1.bmp",2;
			next;
			mes "[キャサリン]";
			mes "……破損の記録もなし。";
			mes "記録を行う書記の備品でもない時点で";
			mes "不許可ですわね。";
			emotion 6;
			close2;
			cutin "ep16gao_1.bmp",255;
			end;
		}
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		mes "[キャサリン]";
		mes "エルンストのことですの？";
		mes "そうですわね……";
		cutin "ep16gao_1.bmp",2;
		next;
		mes "[キャサリン]";
		mes "毎日公務を手伝ってくれます。";
		mes "挨拶も忘れずしていますし、";
		mes "真面目なのでしょうね。";
		cutin "ep16gao_2.bmp",2;
		next;
		mes "[キャサリン]";
		mes "そういえば……";
		mes "祝宴がはじまってから";
		mes "仕事を持ってどこかに";
		mes "行ってしまったようですわね。";
		mes "まだ顔を見ていないわ。";
		cutin "ep16gao_1.bmp",2;
		close2;
		cutin "ep16gao_1.bmp",255;
		end;
	case 14:
		mes "[キャサリン]";
		mes "エルンストには";
		mes "出会えましたか？";
		cutin "ep16gao_1.bmp",2;
		next;
		switch(select("出会えた","出会えていない")) {
		case 1:
			mes "[キャサリン]";
			mes "そうですか……。";
			next;
			mes "[キャサリン]";
			mes "……あの子は何も";
			mes "話してはくれませんが";
			mes "いつか克服してくれると";
			mes "わたくしは信じております。";
			next;
			mes "[キャサリン]";
			mes "どうかわたくしと一緒に";
			mes "あの子の成長を";
			mes "見守ってあげてくださいな。";
			cutin "ep16gao_2.bmp",2;
			close2;
			cutin "ep16gao_2.bmp",255;
			end;
		case 2:
			mes "[キャサリン]";
			mes "そうですか……。";
			mes "つい先ほどまで";
			mes "この部屋におりましたのに……";
			cutin "ep16gao_1.bmp",2;
			next;
			mes "[キャサリン]";
			mes "家門の代表がこのように";
			mes "歩き回ってばかりでは";
			mes "困りますわ。";
			next;
			menu "エルンストの噂について聞く",-;
			mes "[キャサリン]";
			mes "……その話は";
			mes "お聞きにならないでくださいな。";
			cutin "ep16gao_3.bmp",2;
			next;
			mes "[キャサリン]";
			mes "それは、ゲオルグ家が";
			mes "自ら克服すべき問題ですわ。";
			close2;
			cutin "ep16gao_3.bmp",255;
			end;
		}
	}
	end;
}

prt_cas_q.gat,87,132,3	script	ゲオルグ家守護騎士#ep16_1_m	733,{
	switch(EP16_2QUE) {
	case 2:
		mes "[マーティン]";
		mes "俺はやることがある。";
		mes "用があるならジェラードに";
		mes "話してくれ。";
		close;
	case 3:
		mes "[マーティン]";
		mes "まだなにかあるのか？";
		close;
	case 4:
		mes "[マーティン]";
		mes "理由は知らないが、";
		mes "スカーレット様とリディオン様は";
		mes "昔から仲が悪い。";
		next;
		mes "[マーティン]";
		mes "年もお近いんだし、";
		mes "王妃様のためにも";
		mes "いがみ合わないでもらいたいものだが、";
		mes "……難しい話だ。";
		next;
		mes "[マーティン]";
		mes "険悪なのにも";
		mes "理由はないのかもしれない。";
		mes "お二方共、厳格な人だから。";
		close;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "[マーティン]";
		mes "何かようでもあるのか？";
		close;
	case 13:
		mes "[マーティン]";
		mes "エルンスト様なら祝宴場のほうに";
		mes "向かわれた。";
		mes "まだいらっしゃるかは";
		mes "俺の知るところではないがな。";
		close;
	case 14:
		mes "[マーティン]";
		mes "王妃様、";
		mes "おいたわしい……";
		close;
	default:
		mes "[マーティン]";
		mes "いいか？";
		mes "王妃様に失礼のないようにな。";
		close;
	}
}

prt_cas_q.gat,85,127,3	script	ゲオルグ家守護騎士#ep16_1_g	65,{
	switch(EP16_2QUE) {
	case 2:
		mes "[ジェラード]";
		mes "お客様、";
		mes "先ほどは失礼いたしました。";
		next;
		mes "[マーティン]";
		mes "所持品に不審な物は";
		mes "ありませんでしたので、";
		mes "お返しいたします。";
		emotion 0,"ゲオルグ家守護騎士#ep16_1_g";
		next;
		mes "[ジェラード]";
		mes "マーティン！";
		mes "何をしているのかと思ったら、";
		mes "勝手に荷物検査などしていたのか！";
		next;
		mes "[マーティン]";
		mes "これだけ大勢の人間が";
		mes "出入りしているんだ。";
		mes "用心するにこしたことはないだろう？";
		next;
		mes "[ジェラード]";
		mes "まったく……";
		mes "　";
		mes "お客様、";
		mes "重ね重ね、失礼いたしました。";
		next;
		switch(select("いいえ","本当ですよ")) {
		case 1:
			mes "[ジェラード]";
			mes "……ありがとうございます。";
			mes "ほら、マーティン";
			mes "お前も頭を下げろ！";
			break;
		case 2:
			mes "[ジェラード]";
			mes "本当に申し訳ありません！";
			mes "このようなことは";
			mes "もう起こらないようにしますので！";
			mes "ほら、マーティン";
			mes "お前も頭を下げろ！";
			break;
		}
		next;
		mes "‐マーティンと呼ばれる";
		mes "　守護騎士は、不服そうな表情を隠さずに";
		mes "　少しだけ頭を下げた‐";
		next;
		mes "[ジェラード]";
		mes "こら！";
		next;
		mes "[マーティン]";
		mes "……あの時のようなことは";
		mes "もう御免だ。";
		emotion 0,"ゲオルグ家守護騎士#ep16_1_g";
		next;
		menu "あの時？",-;
		mes "[ジェラード]";
		mes "そ、そうだ、お客様！";
		mes "もう祝宴場には向かわれましたか？";
		mes "よろしければ、会場にいる";
		mes "ゲオルグ家の方々にも";
		mes "お会いになってください。";
		next;
		mes "[ジェラード]";
		mes "王妃様の姉君である";
		mes "スカーレット・ザハー様も";
		mes "そちらにいらっしゃってますよ。";
		next;
		mes "[ジェラード]";
		mes "ゲオルグ家の人間ではないですが";
		mes "王妃様に関しては";
		mes "知らないことがない方です。";
		delquest 11401;
		setquest 11402;
		set EP16_2QUE,3;
		close;
	case 3:
		mes "[ジェラード]";
		mes "もう祝宴場には向かわれましたか？";
		mes "よろしければ、会場にいる";
		mes "ゲオルグ家の方々にも";
		mes "お会いになってください。";
		next;
		mes "[ジェラード]";
		mes "王妃様の姉君である";
		mes "スカーレット・ザハー様も";
		mes "そちらにいらっしゃってますよ。";
		next;
		mes "[ジェラード]";
		mes "ゲオルグ家の人間ではないですが";
		mes "王妃様に関しては";
		mes "知らないことがない方です。";
		close;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "[ジェラード]";
		mes "スカーレット様と王妃様は";
		mes "かなり御歳が離れているそうですが、";
		mes "見た目はとてもお若い方ですので";
		mes "王妃様と差があるようには";
		mes "見えません。";
		next;
		mes "[ジェラード]";
		mes "王妃様ご自身も";
		mes "かなり御歳を召されてますが";
		mes "あんなにお美しい方です。";
		mes "実際よりも若く見えるのが";
		mes "お二人の家門の特徴だそうですよ。";
		close;
	case 13:
		mes "[ジェラード]";
		mes "一人で国政を担うのも";
		mes "大変だというのに、";
		mes "祝宴に王位継承騒動まで……";
		mes "ここ数日間は、";
		mes "お休みになる時間もないようです。";
		next;
		mes "[ジェラード]";
		mes "王妃様もエルンスト様も";
		mes "お辛いことが多すぎました。";
		mes "もう少し楽になって欲しいです。";
		close;
	case 14:
		mes "[ジェラード]";
		mes "王位継承が終われば、";
		mes "王妃様は新しい王に国政を任せて";
		mes "スカーレット様の城に";
		mes "お戻りになるかもしれません。";
		next;
		mes "[ジェラード]";
		mes "一生を王室に仕えると決めて";
		mes "王妃様に仕えて来た私としては";
		mes "……少し心配です。";
		close;
	default:
		mes "[ジェラード]";
		mes "王妃様の御前です。";
		mes "どうか、失礼のないよう";
		mes "お気をつけてください。";
		close;
	}
}

prt_cas.gat,73,244,5	script	スカーレット・ザハー#ep16_1	71,{
	switch(EP16_2QUE) {
	case 3:
		mes "[スカーレット・ザハー]";
		mes "あらあら、まあまあ";
		mes "冒険様が、一貴族の私に";
		mes "なにかご用ですか？";
		emotion 18;
		next;
		switch(select("ゲオルグ家について聞く","挨拶をする","なんでもありません")) {
		case 1:
			mes "[スカーレット・ザハー]";
			mes "はあ……";
			mes "あなたですの？";
			next;
			mes "[スカーレット・ザハー]";
			mes "話しかけてくる方は";
			mes "みーんな、口を揃えて";
			mes "「ゲオルグ家ゲオルグ家」と";
			mes "ゲオルグ家のことばかり。";
			emotion 6;
			next;
			mes "[スカーレット・ザハー]";
			mes "私自身に興味を持っては";
			mes "いただけないのかしら？";
			next;
			switch(select("……","興味ありません","興味あります")) {
			case 1:
				mes "[スカーレット・ザハー]";
				mes "あらあら！";
				mes "慌てないでくださいな。";
				mes "ほんの冗談ですから。";
				mes "うふふ。";
				emotion 18;
				next;
				break;
			case 2:
				mes "[スカーレット・ザハー]";
				mes "あらあら！";
				mes "とても正直なお方ですのね。";
				mes "まあ、ほんの冗談でしたもの。";
				mes "気になさらないでね。うふふ。";
				emotion 18;
				next;
				break;
			case 3:
				mes "[スカーレット・ザハー]";
				mes "あらあら！";
				mes "お世辞かしら、うふふ。";
				mes "それとも私の年齢を";
				mes "ご存じないのかしらね。";
				next;
				mes "[スカーレット・ザハー]";
				mes "まあ、ほんの冗談でしたの。";
				mes "気になさらないで。";
				emotion 18;
				next;
				break;
			}
			mes "[スカーレット・ザハー]";
			mes "皆がご存知の通り、";
			mes "ゲオルグ家の祖先は";
			mes "ルーンミッドガッツ王国を";
			mes "建国した英雄なのですわ！";
			next;
			mes "[リディオン・ゲオルグ]";
			mes "……建国の英雄である";
			mes "トリスタン1世の子孫。";
			mes "そんな話は街にいる";
			mes "子供ですら知っているほど";
			mes "有名な話なんだがな？";
			mes "ザハー夫人。";
			next;
			mes "[スカーレット・ザハー]";
			mes "あらあらまあまあ！";
			mes "リディオン・ゲオルグ様！";
			mes "お体の調子が芳しくないと";
			mes "伺っておりましたが、";
			mes "お元気そうでなによりですわ。";
			emotion 6;
			next;
			mes "[リディオン・ゲオルグ]";
			mes "ははは。";
			mes "ゲオルグ家の人間でもない";
			mes "ザハー家の女性が、";
			mes "我がゲオルグ家門について、";
			mes "事実無根な話を口にされないか";
			mes "心配で休んでいられませんからな。";
			delquest 11402;
			setquest 11403;
			set EP16_2QUE,4;
			close;
		case 2:
			mes "[スカーレット・ザハー]";
			mes "あらあら！";
			mes "あなたのような冒険者に";
			mes "挨拶されてしまいましたわ！";
			mes "違う世界に生きてる者ですもの";
			mes "とても新鮮ですわね。";
			close;
		case 3:
			mes "[スカーレット・ザハー]";
			mes "そうですの？";
			mes "にぎやかな祝宴に浮かれて、";
			mes "思わず声をかけてしまわれたのかしら。";
			mes "うふふ。";
			close;
		}
		end;
	case 4:
		mes "[スカーレット・ザハー]";
		mes "あらあら、まあまあ。";
		mes "リディオン・ゲオルグ様！";
		mes "お体の調子があまり";
		mes "よくないと聞きましたが、";
		mes "休まなくて大丈夫ですの？";
		emotion 6;
		next;
		mes "[リディオン・ゲオルグ]";
		mes "問題ないですとも。";
		mes "ゲオルグ家の人間でもない";
		mes "ザハー家の女性が、";
		mes "我がゲオルグ家門について、";
		mes "事実無根な話を流してしまわないか";
		mes "心配で休んでいられませんからな。";
		close;
	case 5:
		mes "[スカーレット・ザハー]";
		mes "ふん、嫌な爺さんだわ！";
		mes "私よりも若いくせに";
		mes "いつも説教ばかり！";
		emotion 6;
		next;
		mes "[スカーレット・ザハー]";
		mes "あら！　おほほほほ。";
		mes "冒険者様いらっしゃったのね。";
		mes "ゲオルグ家は王位継承が終わり次第、";
		mes "王権を渡し、王宮を出て静かに";
		mes "過ごすという話をしていましたのよ。";
		next;
		mes "[スカーレット・ザハー]";
		mes "私もキャサリンには";
		mes "これ以上は悲しんで";
		mes "欲しくありませんから。";
		mes "今回の決定には";
		mes "賛成していますわ。";
		next;
		mes "[スカーレット・ザハー]";
		mes "ですが、肝心の当事者である";
		mes "エルンスト王子が";
		mes "いくら探しても見つかりませんの。";
		next;
		mes "[スカーレット・ザハー]";
		mes "この叔母である私が、";
		mes "傷ついた甥っ子を慰めるために";
		mes "遠くから来たというのに！";
		next;
		mes "[スカーレット・ザハー]";
		mes "病で引退を表明した先王に";
		mes "お見舞いもできず、";
		mes "妹には忙しいという理由で";
		mes "祝宴場に追い出され";
		mes "甥っ子の姿は見えないまま……";
		emotion 28;
		next;
		mes "[スカーレット・ザハー]";
		mes "もし祝宴場で";
		mes "エルンスト王子に会ったら、";
		mes "こちらに顔を出すように";
		mes "伝えてくださいな。";
		mes "必ずですわよ。";
		set EP16_2QUE,6;
		delquest 11404;
		setquest 11405;
		close;
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "[スカーレット・ザハー]";
		mes "当事者である";
		mes "エルンスト王子が";
		mes "いくら探しても見つかりませんの。";
		next;
		mes "[スカーレット・ザハー]";
		mes "この叔母である私が、";
		mes "傷ついた甥っ子を慰めるために";
		mes "遠くから来たというのに！";
		next;
		mes "[スカーレット・ザハー]";
		mes "病で引退を表明した先王に";
		mes "お見舞いもできず、";
		mes "妹には忙しいという理由で";
		mes "祝宴場に追い出され";
		mes "甥っ子の姿は見えないまま……";
		emotion 28;
		next;
		mes "[スカーレット・ザハー]";
		mes "もし祝宴場で";
		mes "エルンスト王子に会ったら、";
		mes "こちらに顔を出すように";
		mes "伝えてくださいな。";
		mes "必ずですわよ。";
		close;
	case 13:
		mes "[スカーレット・ザハー]";
		mes "あらあら。";
		mes "エルンスト王子は";
		mes "やはり見つからなかった";
		mes "みたいですわね？";
		mes "キャサリンに聞いたほうが";
		mes "よろしいかしら。";
		next;
		mes "[スカーレット・ザハー]";
		mes "……";
		next;
		mes "[スカーレット・ザハー]";
		mes "あなたの表情を見ればわかります。";
		mes "あの子の噂を";
		mes "聞いてしまったのですね。";
		next;
		mes "[スカーレット・ザハー]";
		mes "気分の良い話ではなかったと";
		mes "思いますけど、";
		mes "あまり気にしないでくださいな。";
		next;
		mes "[スカーレット・ザハー]";
		mes "エルンスト王子も";
		mes "そのような噂話に耐えられず、";
		mes "隠れてしまったのかもしれないわね。";
		next;
		mes "[スカーレット・ザハー]";
		mes "……まあ、";
		mes "あの子にもまだ";
		mes "休息が必要なのでしょう。";
		next;
		mes "[スカーレット・ザハー]";
		mes "冒険者様も、エルンスト王子を";
		mes "探すのはお休みになって、";
		mes "祝宴を楽しんでくださいな。";
		next;
		if(checkitemblank() == 0) {	// 未調査
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		mes "[スカーレット・ザハー]";
		mes "せっかくの楽しい祝宴が";
		mes "このまま終わってしまっては";
		mes "残念ではありませんか。";
		set EP16_2QUE,14;
		delquest 11412;
		setquest 201890;
		getitem 6919,25;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		close;
	case 14:
		mes "[スカーレット・ザハー]";
		mes "あらあら、まあまあ！";
		mes "楽しんでいらっしゃいますか？";
		next;
		mes "[スカーレット・ザハー]";
		mes "もしお時間があるなら";
		mes "武勇伝でも聞かせてくださいな。";
		mes "リディオン様の小言は";
		mes "飽きてしまいましたわ。";
		close;
	default:
		mes "[スカーレット・ザハー]";
		mes "あらあら、まあまあ";
		mes "エルンスト王子はどこかしら？";
		mes "姿が見えませんわ。";
		emotion 18;
		close;
	}
	end;
}

prt_cas.gat,82,240,3	script	リディオン・ゲオルグ#ep16_1	923,{
	switch(EP16_2QUE) {
	case 4:
		mes "[リディオン・ゲオルグ]";
		mes "私たちゲオルグ家は";
		mes "七王家の一つではあり、";
		mes "かつ、最も多くの王を排出してきた";
		mes "名家中の名家といえます。";
		next;
		mes "[リディオン・ゲオルグ]";
		mes "実際にルーンミッドガッツ王国の";
		mes "中心であるプロンテラに";
		mes "本拠地を置いており！";
		next;
		mes "[リディオン・ゲオルグ]";
		mes "国王であるトリスタン3世の";
		mes "突然の病による引退からはじまり、";
		mes "そして王子たちに相次ぐ";
		mes "不運な事件があったのにも";
		mes "かかわらず！";
		next;
		mes "[リディオン・ゲオルグ]";
		mes "エルンスト・ゲオルグ王子が";
		mes "先の王位継承で有力候補に";
		mes "選出されたことも";
		mes "ゲオルグ家の力を";
		mes "表しているといえますな！";
		next;
		mes "[スカーレット・ザハー]";
		mes "あらあら、まあまあ。";
		mes "ゲオルグ家のエルンスト王子は、";
		mes "王位継承を辞退されましたわよ？";
		next;
		mes "[リディオン・ゲオルグ]";
		mes "何……!?";
		unittalk getnpcid(0,"リディオン・ゲオルグ#ep16_1"),"リディオン・ゲオルグ : 何!?",1;
		next;
		mes "[スカーレット・ザハー]";
		mes "ですから、";
		mes "エルンスト王子は";
		mes "王位継承権を拒否なさったの。";
		next;
		mes "[リディオン・ゲオルグ]";
		mes "そんな……";
		next;
		mes "[リディオン・ゲオルグ]";
		mes "そんな……ありえない!!";
		next;
		mes "[スカーレット・ザハー]";
		mes "あらあら、まあまあ。";
		mes "名家中の名家様は、";
		mes "屋敷にこもって、療養なさってばかりで";
		mes "こんな大きいニュースも";
		mes "初耳のようですわねぇ？";
		next;
		mes "[リディオン・ゲオルグ]";
		mes "あ、ありえないいいいい!!";
		mes "エルンストは、あいつはどこだあああ!!";
		unittalk getnpcid(0,"リディオン・ゲオルグ#ep16_1"),"リディオン・ゲオルグ : うわあああああ!!　エルンストはどこだあああ!!",1;
		next;
		mes "[スカーレット・ザハー]";
		mes "あいつとは……";
		mes "王子に対して失礼ではなくて？";
		mes "それとも名家の出は";
		mes "言葉づかいも知らないのかしら。";
		next;
		mes "[リディオン・ゲオルグ]";
		mes "ありえないいいいいい!!";
		unittalk getnpcid(0,"リディオン・ゲオルグ#ep16_1"),"リディオン・ゲオルグ : ありえないいいいいい!!",1;
		set EP16_2QUE,5;
		delquest 11403;
		setquest 11404;
		close;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		mes "[リディオン・ゲオルグ]";
		mes "あ、ありえないいいいい!!";
		mes "王位継承権をあきらめたなど！";
		mes "エルンストは、あいつはどこだあああ!!";
		unittalk getnpcid(0,"リディオン・ゲオルグ#ep16_1"),"リディオン・ゲオルグ : うわあああああ!!　エルンストはどこだあああ!!",1;
		next;
		mes "[スカーレット・ザハー]";
		mes "あいつとは……";
		mes "王子に対して失礼ではなくて？";
		mes "それとも名家の出は";
		mes "言葉づかいも知らないのかしら。";
		next;
		mes "[リディオン・ゲオルグ]";
		mes "ありえないいいいいい!!";
		unittalk getnpcid(0,"リディオン・ゲオルグ#ep16_1"),"リディオン・ゲオルグ : ありえないいいいいい!!",1;
		close;
	default:
		mes "[リディオン・ゲオルグ]";
		mes "どこのペコペコの骨とも";
		mes "分からん奴らを";
		mes "出入りさせるから";
		mes "王室の品格が落ちるのだ！";
		close;
	}
}

prt_cas.gat,76,258,0	script	#ep16_1噂話1	139,3,3,{
OnTouch:
	if(EP16_2QUE == 6) {
		mes "[噂している声]";
		mes "ねぇ、聞きました？";
		mes "トリスタン3世陛下が";
		mes "白骨で発見されたんですって！";
		mes "こわいわねえ……";
		next;
		mes "[噂している声]";
		mes "うっそ～！";
		mes "本当に!?";
		next;
		mes "[噂している声]";
		mes "陛下は病のために";
		mes "隠居されたのではなくて？";
		next;
		mes "[噂している声]";
		mes "タイミングよく";
		mes "魔王モロクの件も重なって";
		mes "新しい時代のためにと";
		mes "退かれたのでは？";
		next;
		mes "[噂している声]";
		mes "わたくしもそう聞いていますわ。";
		next;
		mes "[噂している声]";
		mes "あら、でも";
		mes "信頼できる情報よ？";
		mes "内緒にしてちょうだいね。";
		set EP16_2QUE,7;
		delquest 11405;
		setquest 11406;
		close;
	}
	end;
}

prt_cas.gat,84,232,0	script	#ep16_1噂話2	139,3,3,{
OnTouch:
	if(EP16_2QUE == 7) {
		mes "[噂している声]";
		mes "……それで王子たちは";
		mes "結局毒殺だと……";
		next;
		mes "[噂している声]";
		mes "そんなことが……";
		mes "そういえば前回の";
		mes "王位継承の時も……";
		set EP16_2QUE,8;
		delquest 11406;
		setquest 11407;
		close;
	}
	end;
}

prt_cas.gat,110,242,0	script	#ep16_1噂話3	139,3,3,{
OnTouch:
	if(EP16_2QUE == 8) {
		mes "[噂している声]";
		mes "ふん！";
		mes "エルンストの小僧め";
		mes "勝手に王位を";
		mes "諦めやがって！";
		next;
		mes "[噂している声]";
		mes "あいつは、";
		mes "トリスタン3世陛下の";
		mes "最後の実子でも";
		mes "あるだろうに！";
		next;
		mes "[噂している声]";
		mes "しっ";
		mes "声が大きいですよ！";
		next;
		mes "[噂している声]";
		mes "いや～";
		mes "だってそうだろ？";
		mes "なにか間違ってるか？";
		next;
		mes "[噂している声]";
		mes "そんな重要なことを";
		mes "どうして自分勝手に";
		mes "決めてしまったんだ！";
		next;
		mes "[噂している声]";
		mes "家門のことは";
		mes "考えていないのか、まったく！";
		set EP16_2QUE,9;
		delquest 11407;
		setquest 11408;
		close;
	}
	end;
}

prt_cas.gat,111,218,0	script	#ep16_1噂話4	139,3,3,{
OnTouch:
	if(EP16_2QUE == 9) {
		mes "[噂している声]";
		mes "あんな三流家門出のやつと";
		mes "一緒にいた結果か……";
		next;
		mes "[噂している声]";
		mes "ははは……";
		mes "ひどい言い草だなあ";
		next;
		mes "[噂している声]";
		mes "まあ、でも";
		mes "その乱心した";
		mes "三流の家の候補者を";
		mes "粛清したんだろう？";
		next;
		mes "[噂している声]";
		mes "しかし、それで心を病んで";
		mes "王位継承権を辞退するなんて";
		mes "本末転倒じゃないか。";
		next;
		mes "[噂している声]";
		mes "聞くところによると";
		mes "部屋にひとり引きこもってるらしいぞ。";
		next;
		mes "[噂している声]";
		mes "なんて情けない！";
		set EP16_2QUE,10;
		delquest 11408;
		setquest 11409;
		close;
	}
	end;
}

prt_cas.gat,92,224,0	script	#ep16_1噂話5	139,3,3,{
OnTouch:
	if(EP16_2QUE == 10) {
		mes "[噂している声]";
		mes "あらそれじゃあ";
		mes "今、王宮の仕事はすべて";
		mes "王妃様が行って";
		mes "らっしゃるのですか？";
		next;
		mes "[噂している声]";
		mes "そうみたいですわ。";
		mes "陛下はご病気で";
		mes "ずっと動けないらしいですし、";
		mes "王子様たちはほら、ねえ？";
		next;
		mes "[噂している声]";
		mes "王妃様、なんておかわいそう……";
		next;
		mes "[噂している声]";
		mes "こうなるまでは";
		mes "ずっと表に姿をお見せに";
		mes "ならなかったのに……";
		mes "大変なことですわ。";
		set EP16_2QUE,11;
		delquest 11409;
		setquest 11410;
		close;
	}
	end;
}

prt_cas.gat,77,223,0	script	#ep16_1噂話6	139,3,3,{
OnTouch:
	if(EP16_2QUE == 11) {
		mes "[噂している声]";
		mes "そんなことで";
		mes "王位を諦めてしまうとは";
		mes "バカな奴……";
		next;
		mes "[噂している声]";
		mes "私ならそんな権力、";
		mes "絶対手離さないのに！";
		next;
		mes "[噂している声]";
		mes "おいおい、";
		mes "権力ってのは誰でも";
		mes "簡単に握れるものじゃないぞ。";
		next;
		mes "[噂している声]";
		mes "なんだと!?";
		mes "俺はそんな想像も";
		mes "しちゃいけないってのか！";
		next;
		mes "[噂している声]";
		mes "それに王位につくと";
		mes "呪いもついてくるらしい";
		mes "じゃないか。";
		mes "俺は嫌だね。";
		next;
		mes "[噂している声]";
		mes "……あれは家門のほうに";
		mes "ついてくるものじゃなかったか？";
		next;
		mes "[噂している声]";
		mes "いや、わからないよ～";
		mes "どちらにしろ不吉じゃないか。";
		set EP16_2QUE,12;
		delquest 11410;
		setquest 11411;
		close;
	}
	end;
}

prt_cas.gat,66,217,0	script	#ep16_1噂話7	139,3,3,{
	if(EP16_2QUE == 12) {
		mes "[噂している声]";
		mes "……";
		mes "繁栄を極めたゲオルグ家の";
		mes "エルンスト王子が逃げ出すなんて。";
		mes "やはりゲオルグ家は";
		mes "呪われてるいるんだわ……";
		next;
		mes "[噂している声]";
		mes "やめろ！";
		mes "誰かに聞かれたら";
		mes "大変なことになるぞ！";
		cloakoffnpc "謎の男#ep16_1";
		next;
		mes "[謎の男]";
		mes "ふふふ、";
		mes "エルンスト王子はよほど";
		mes "ひどい人物のようだね。";
		next;
		mes "‐男は影に隠れて顔が";
		mes "　よくわからない‐";
		next;
		menu "あなたは？",-;
		mes "[謎の男]";
		mes "僕のことはいい。";
		mes "あなたは冒険者だよね。";
		next;
		mes "[謎の男]";
		mes "冒険者たちはすばらしい。";
		mes "心から憧れるし尊敬する。";
		mes "自由で、自分の正義を貫けるから。";
		next;
		mes "[謎の男]";
		mes "冒険者さん。";
		mes "よかったらある王族の話を";
		mes "聞いてくれないかな？";
		next;
		menu "王族の話？",-;
		mes "[謎の男]";
		mes "昔、家門がちがえど";
		mes "とても^4d4dff仲の良い二人の王子^000000が";
		mes "いたそうだよ。";
		mes "それでね、";
		mes "こんな約束をしていたそうだ。";
		next;
		mes "[謎の男]";
		mes "^4d4dff二人で王を目指そう^000000、とね。";
		next;
		mes "[謎の男]";
		mes "どちらかが王になったら";
		mes "王になれなかった方が";
		mes "必ず王の腹心になり盛りたてる。";
		next;
		mes "[謎の男]";
		mes "そして、どちらかが";
		mes "道を外すようなことがあれば";
		mes "必ずその手で殺すと。";
		mes "この王国の光のためにね。";
		next;
		mes "[謎の男]";
		mes "……";
		mes "その二人は純粋だった。";
		mes "光が1つしかなく美しい物だと";
		mes "信じていた。";
		mes "光を目指せば必ず";
		mes "皆を幸せにできると思っていた。";
		next;
		mes "[謎の男]";
		mes "彼らは光には、";
		mes "醜い虫のようなものが";
		mes "群れをなすことを知らなかった。";
		mes "大量の虫が光を遮り、";
		mes "光そのものが消えてしまう";
		mes "ことがあるのを知らなかった。";
		next;
		mes "[謎の男]";
		mes "……";
		mes "悲劇がおきるんだ。";
		mes "一人の王子の家門が、";
		mes "もう一人の王子を、";
		mes "暗殺しようと、したらしい。";
		mes "王位を狙ってね。";
		next;
		menu "酷い",-;
		mes "[謎の男]";
		mes "それを知った王子は、";
		mes "暗殺をとめようと、";
		mes "最悪の選択をとってしまった！";
		next;
		mes "[謎の男]";
		mes "きっと、その王子は、";
		mes "こう思っていたんだ。";
		mes "自分がいなくなれば、";
		mes "自分の家門から王位はでない。";
		mes "だから、暗殺をとめられる、と……";
		next;
		mes "[謎の男]";
		mes "そして、その王子は";
		mes "自ら命を断ってしまった。";
		next;
		menu "そ、そんな！",-;
		mes "[謎の男]";
		mes "悲しい話ではないよ。";
		mes "怒りの話だよ。";
		mes "王子の自殺を防げなかった";
		mes "もう一人の王子の不甲斐なさにね。";
		next;
		menu "生き残った王子はどうなったの？",-;
		mes "[謎の男]";
		mes "情けない王子の方は……";
		mes "王位を諦めたそうだ。";
		mes "絶望してね。";
		mes "自分の不甲斐なさ、";
		mes "家門の背負う欲の汚さに。";
		next;
		menu "それで？",-;
		mes "[謎の男]";
		mes "それで、か。";
		mes "まあ、その王子には期待しないで";
		mes "聞いてほしい。";
		next;
		mes "[謎の男]";
		mes "その王子は、家門をこえた、";
		mes "この国を正しく導くことできる";
		mes "王の素質がある者が現れたら";
		mes "その王を守りたいと考えている。";
		next;
		mes "[謎の男]";
		mes "今度こそ、虫に";
		mes "光が消されないために。";
		mes "それが死んだ王子との";
		mes "約束だと思っているらしい。";
		next;
		switch(select("なるほど","君ならできるよ、エルンスト")) {
		case 1:
			mes "[謎の男]";
			mes "……";
			mes "聞いてくれてありがとう。";
			mes "それでは失礼する。";
			next;
			mes "[噂している声]";
			mes "……ヒソヒソ。";
			mes "あそこで話していたのは";
			mes "エルンスト王子ではないか？";
			next;
			mes "[噂している声]";
			mes "……本当だ。";
			mes "冒険者と何を話していたんだ？";
			delquest 11411;
			setquest 11412;
			set EP16_2QUE,13;
			close2;
			cloakonnpc "謎の男#ep16_1";
			end;
		case 2:
			mes "[エルンスト]";
			mes "ふふふ、";
			mes "僕の顔を覚えいてくれたんだね、";
			mes strcharinfo(0)+"。";
			mes "お久しぶり。";
			next;
			menu "王位を諦めるの？",-;
			mes "[エルンスト]";
			mes "そうだよ。";
			mes "僕は大切なものを守りたい。";
			mes "それは、アルム兄さんが守りたかった、";
			mes "本当の光。";
			mes "バルター家やゲオルグ家など";
			mes "家門は関係ないんだ。";
			next;
			mes "[エルンスト]";
			mes "兄さんが守ってくれたこの命、";
			mes "有用に使いたい。";
			mes "この国の光が消えないように";
			mes "^4d4dff光^000000が輝き続けるために。";
			next;
			mes "[エルンスト]";
			mes "……";
			mes "おっと、";
			mes "人が多くなってきたようだね。";
			mes "あまり目立ちたくない。";
			mes "それでは失礼するよ。";
			mes "僕がいたことは内緒にしておいて。";
			set EP16_2QUE,13;
			delquest 11411;
			setquest 11412;
			close2;
			cloakonnpc "謎の男#ep16_1";
			end;
		}
	}
	end;
}

prt_cas.gat,66,220,3	script(CLOAKED)	謎の男#ep16_1	985,{}

prt_cas.gat,78,250,5	script	王室料理人#ep16_1	46,{
	if(EP16_7QUE == 1) {
		mes "[王室料理人]";
		mes "急いで厨房に行ってくれ！";
		mes "料理長が暴れる寸前なんだ。";
		close;
	}
	if(EP16_7QUE == 22) {
		mes "[王室料理人]";
		mes "今は本当に忙しいんだ！";
		mes "あまりの忙しさに加えて";
		mes "多くの人たちを見たせいか、";
		mes "もう人の顔も見分けが……";
		next;
		mes "[王室料理人]";
		mes "なんであんな間違いを";
		mes "してしまったんだ……";
		mes "あの料理長に";
		mes "嫌になるほど怒られたよ……";
		mes "ふふふ。";
		emotion 19;
		close;
	}
	mes "[王室料理人]";
	mes "目が回るほど忙しいというが、";
	mes "今、あまりに忙しくて";
	mes "本当に目が回っているんだ！";
	close;
OnTouch:
	if(EP16_7QUE == 0 && EP16_1QUE >= 3) {
		mes "[王室料理人]";
		mes "こんな所に居たのか！";
		mes "何をしていたんだ？";
		emotion 0;
		next;
		mes "[王室料理人]";
		mes "急いで厨房に行ってくれ！";
		mes "料理長が暴れる寸前なんだ。";
		setquest 11394;
		set EP16_7QUE,1;
		close;
	}
	end;
}

prt_cas.gat,309,200,5	script	王室料理長#ep16_1	10122,{
	switch(EP16_7QUE) {
	case 0:
		mes "[料理長]";
		mes "もーーー!!";
		mes "一体いつになったら";
		mes "至極の料理人見習いは";
		mes "来るんですかーっ！";
		emotion 6;
		cutin "ep16cook_king_1.bmp",2;
		close2;
		cutin "ep16cook_king_1.bmp",255;
		end;
	case 1:
		mes "[料理長]";
		mes "もーーー!!";
		mes "一体いつになったら";
		mes "至極の料理人見習いは";
		mes "来るんですかーっ！";
		emotion 6;
		cutin "ep16cook_king_1.bmp",2;
		next;
		mes "[料理長]";
		mes "もちろん！";
		mes "私のつくるぅ～、祝宴料理に！";
		mes "不足はないけどもっ！";
		mes "不足はないけどもっ！";
		mes "自信があるから2回も言ったけども！";
		next;
		mes "[料理長]";
		mes "もっと！";
		mes "もっと！";
		mes "もっと!!";
		mes "もっと!!!!";
		mes "お客様たちを";
		mes "満足させなければ！";
		next;
		mes "[料理長]";
		mes "一生一代の大仕事を";
		mes "中途半端に終わらせることは";
		mes "出来ません！";
		mes "少なくとも超素晴らしく！";
		mes "いや、スーパーウルトラ素晴らしく！";
		next;
		mes "[料理長]";
		mes "超～ウルトラスーパー";
		mes "ミラコォー（いい発音）で";
		mes "ファンタスティックで";
		mes "モーマンタイ程度じゃないと";
		mes "満足することはできません！";
		emotion 6;
		next;
		cutin "ep16cook_king_1.bmp",255;
		mes "[王室見習い料理人]";
		mes "料理長、報告します！";
		next;
		mes "[王室見習い料理人]";
		mes "至極の料理人見習いの方が";
		mes "いらっしゃいました！";
		next;
		mes "[料理長]";
		mes "ユー、遅いです！";
		mes "調理場は戦場なんですよ！";
		mes "そして今は激戦の最中です！";
		mes "ポーション連打レベルですよ！";
		mes "1分1秒が命取りになるのに";
		mes "遅れてくるなんて!!";
		emotion 6;
		cutin "ep16cook_king_1.bmp",2;
		next;
		mes "[料理長]";
		mes "普段ならば";
		mes "料理長私刑法にのっとり";
		mes "「身を持って串焼き経験刑」など";
		mes "大変な罰を受けてもらいますが";
		mes "今日は特別な日なので";
		mes "後日にしてあげます！";
		next;
		switch(select("私、料理人じゃないです","状況について聞く","身を持って串焼き経験したいです")) {
		case 1:
			mes "[料理長]";
			mes "嘘おっしゃい！";
			mes "私にはわかります！";
			mes "あなたは凄腕の料理人です！";
			break;
		case 2:
			mes "[料理長]";
			mes "今はそんなこと";
			mes "どうでもいいです！";
			mes "お喋りはこの辺にして";
			mes "もっと素晴らしい";
			mes "祝宴をするために";
			mes "頑張りますよ!!";
			break;
		case 3:
			mes "[料理長]";
			mes "わかりました。";
			mes "ちょっと足を開いてください。";
			mes "この大きな串でブスッっとね、";
			mes "え～と、たれと塩、";
			mes "どっちを経験したい……";
			mes "ってバカ!!";
			next;
			mes "[料理長]";
			mes "本気にするって本当におバカよ！";
			mes "ジョークに決まってるでしょ！";
			mes "料理学校で習わなかったの!?";
			mes "料理人ジョーク！";
			mes "もう、時間がないの！";
			break;
		}
		next;
		mes "[料理長]";
		mes "早くその机の前の空いている";
		mes "場所に行ってそこで";
		mes "料理の準備をして下さい！";
		next;
		mes "[料理長]";
		mes "うまく整えてある";
		mes "グリフォン肉に……";
		mes "ソース……え？";
		mes "ソースを……あれ!?";
		emotion 0;
		next;
		mes "[料理長]";
		mes "そんな……！";
		mes "ソースがなくなっています！";
		mes "あのソースがなければ";
		mes "何もできませーん!!";
		next;
		mes "[料理長]";
		mes "至極の料理人見習い！";
		mes "早くソースの達人、";
		mes "オリエンタルオイシスター様から";
		mes "ソースをもらって来て下さい！";
		emotion 26;
		next;
		mes "[料理長]";
		mes "急いで！　早く！";
		mes "急いで下さい！";
		set EP16_7QUE,2;
		delquest 11394;
		setquest 11395;
		close2;
		cutin "ep16cook_king_1.bmp",255;
		end;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
		mes "[料理長]";
		mes "ソースはまだですかああああ!!";
		mes "早くソースの達人、";
		mes "オリエンタルオイシスター様から";
		mes "ソースをもらって来て下さい！";
		emotion 26;
		cutin "ep16cook_king_1.bmp",2;
		next;
		mes "[料理長]";
		mes "急いで！　早く！";
		mes "急いで下さい！";
		close2;
		cutin "ep16cook_king_1.bmp",255;
		end;
	case 12:
		mes "[料理長]";
		mes "おおお！";
		mes "やはり達人の腕！";
		mes "完璧です！";
		cutin "ep16cook_king_1.bmp",2;
		next;
		mes "[料理長]";
		mes "それではここから";
		mes "料理を作ってみます！";
		mes "早く空いている場所に行って";
		mes "準備をして下さい！";
		set EP16_7QUE,13;
		delquest 11397;
		setquest 11398;
		close2;
		cutin "ep16cook_king_1.bmp",255;
		end;
	case 13:
		mes "[料理長]";
		mes "それではここから";
		mes "料理を作ってみます！";
		mes "早く空いている場所に行って";
		mes "準備をして下さい！";
		cutin "ep16cook_king_1.bmp",2;
		close2;
		cutin "ep16cook_king_1.bmp",255;
		end;
	case 14:
		mes "[料理長]";
		mes "さて、これを食堂に";
		mes "持って行けば完璧です！";
		cutin "ep16cook_king_1.bmp",2;
		next;
		mes "[料理長]";
		mes "何をしていますか!!";
		mes "早く料理を持って";
		mes "食堂に走りなさい！";
		next;
		mes "[料理長]";
		mes "料理が無くなった皿に";
		mes "すばやく補充するのも";
		mes "王室料理人の能力です!!";
		close2;
		cutin "ep16cook_king_1.bmp",255;
		end;
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
		mes "[料理長]";
		mes "はああああああ！";
		mes "料理の心は！";
		mes "王妃様の心！";
		cutin "ep16cook_king_1.bmp",2;
		next;
		mes "[料理長]";
		mes "この魂を燃やして!!";
		mes "最高の料理を!!";
		close2;
		cutin "ep16cook_king_1.bmp",255;
		end;
	case 21:
		mes "[料理長]";
		mes "ぎゃあああああ!!";
		mes "申し訳ありませんでした！";
		emotion 17;
		cutin "ep16cook_king_1.bmp",2;
		next;
		mes "[料理長]";
		mes "新しく来ることになった";
		mes "見習い料理人と思い込み……";
		mes "無礼な物言いどころか";
		mes "お使いまで……";
		next;
		mes "[料理長]";
		mes "冒険者様を連れて来た者も";
		mes "処罰しておきましたので";
		mes "どうか許して下さい！";
		mes "身を持ってタンの盛り合わせの刑！";
		next;
		mes "[料理長]";
		mes "ですが冒険者様の料理の才能は";
		mes "本物だと思います!!";
		mes "グリフォン焼き！";
		mes "美味しかったです！";
		next;
		if(checkitemblank() < 1) {
			cutin "ep16cook_king_2.bmp",255;
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		mes "[料理長]";
		mes "また冒険者様と";
		mes "料理ができる日を";
		mes "楽しみにしています！";
		cutin "ep16cook_king_2.bmp",2;
		set EP16_7QUE,22;
		delquest 11420;
		setquest 201895;
		getitem 6919,25;
		getexp 500000,0,1;
		getexp 500000,0,1;
		getexp 0,100000,0;
		getexp 0,100000,0;
		getexp 0,100000,0;
		close2;
		cutin "ep16cook_king_2.bmp",255;
		end;
	case 22:
		cutin "ep16cook_king_1.bmp",2;
		mes "[料理長]";
		mes "また冒険者様と";
		mes "料理ができる日を";
		mes "楽しみにしています！";
		close2;
		cutin "ep16cook_king_2.bmp",255;
		end;
	}
}

prt_cas.gat,313,199,0	script	#ep16_ビン	139,4,4,{
OnTouch:
	switch(EP16_7QUE) {
	case 0:
		mes "[料理長]";
		mes "そこ！";
		mes "邪魔なので下がってなさい！";
		cutin "ep16cook_king_1.bmp",2;
		close2;
		cutin "ep16cook_king_1.bmp",255;
		end;
	case 13:
		mes "[料理長]";
		mes "さあ、では！";
		mes "今日のメイン料理は……";
		mes "カラッとした皮で中はしっとり。";
		mes "特性ソースでいただく";
		mes "グリフォンの丸焼きです！";
		cutin "ep16cook_king_1.bmp",2;
		next;
		mes "[料理長]";
		mes "祝宴に出される料理だけに！";
		mes "全ての皿が同じ味でなければ";
		mes "いけないことを忘れないように！";
		next;
		mes "[料理長]";
		mes "それでは私の作る手順を見て";
		mes "同じようにして下さい！";
		next;
		mes "[料理長]";
		mes "グリフォンのおにくを～";
		unittalk getnpcid(0,"料理人#ep16_1"),"料理人 : グリフォンのおにくを～",1;
		unittalk getnpcid(0,"料理人#ep16_2"),"料理人 : グリフォンのおにくを～",1;
		unittalk getnpcid(0,"料理人#ep16_3"),"料理人 : グリフォンのおにくを～",1;
		unittalk getnpcid(0,"料理人#ep16_4"),"料理人 : グリフォンのおにくを～",1;
		unittalk getnpcid(0,"料理人#ep16_5"),"料理人 : グリフォンのおにくを～",1;
		unittalk getnpcid(0,"料理人#ep16_6"),"料理人 : グリフォンのおにくを～",1;
		next;
		mes "[料理長]";
		mes "あぶっちゃう！あぶちゃう～～っ！";
		unittalk getnpcid(0,"料理人#ep16_1"),"料理人 : あぶっちゃう！あぶちゃう～～っ！",1;
		unittalk getnpcid(0,"料理人#ep16_2"),"料理人 : あぶっちゃう！あぶちゃう～～っ！",1;
		unittalk getnpcid(0,"料理人#ep16_3"),"料理人 : あぶっちゃう！あぶちゃう～～っ！",1;
		unittalk getnpcid(0,"料理人#ep16_4"),"料理人 : あぶっちゃう！あぶちゃう～～っ！",1;
		unittalk getnpcid(0,"料理人#ep16_5"),"料理人 : あぶっちゃう！あぶちゃう～～っ！",1;
		unittalk getnpcid(0,"料理人#ep16_6"),"料理人 : あぶっちゃう！あぶちゃう～～っ！",1;
		next;
		mes "[料理長]";
		mes "ホット！";
		unittalk getnpcid(0,"料理人#ep16_1"),"料理人 : ホット！",1;
		unittalk getnpcid(0,"料理人#ep16_2"),"料理人 : ホット！",1;
		unittalk getnpcid(0,"料理人#ep16_3"),"料理人 : ホット！",1;
		unittalk getnpcid(0,"料理人#ep16_4"),"料理人 : ホット！",1;
		unittalk getnpcid(0,"料理人#ep16_5"),"料理人 : ホット！",1;
		unittalk getnpcid(0,"料理人#ep16_6"),"料理人 : ホット！",1;
		next;
		mes "[料理長]";
		mes "グリフォンイズベリーホット！";
		unittalk getnpcid(0,"料理人#ep16_1"),"料理人 : グリフォンイズベリーホット！",1;
		unittalk getnpcid(0,"料理人#ep16_2"),"料理人 : グリフォンイズベリーホット！",1;
		unittalk getnpcid(0,"料理人#ep16_3"),"料理人 : グリフォンイズベリーホット！",1;
		unittalk getnpcid(0,"料理人#ep16_4"),"料理人 : グリフォンイズベリーホット！",1;
		unittalk getnpcid(0,"料理人#ep16_5"),"料理人 : グリフォンイズベリーホット！",1;
		unittalk getnpcid(0,"料理人#ep16_6"),"料理人 : グリフォンイズベリーホット！",1;
		next;
		mes "[料理長]";
		mes "ふふふふ！";
		mes "とても素晴らしい";
		mes "グリフォン焼きDXが";
		mes "上手に焼けました!!";
		unittalk getnpcid(0,"料理人#ep16_1"),"料理人 : ご苦労様でした！",1;
		unittalk getnpcid(0,"料理人#ep16_2"),"料理人 : ご苦労様でした！",1;
		unittalk getnpcid(0,"料理人#ep16_3"),"料理人 : ご苦労様でした！",1;
		unittalk getnpcid(0,"料理人#ep16_4"),"料理人 : ご苦労様でした！",1;
		unittalk getnpcid(0,"料理人#ep16_5"),"料理人 : ご苦労様でした！",1;
		unittalk getnpcid(0,"料理人#ep16_6"),"料理人 : ご苦労様でした！",1;
		next;
		mes "[料理長]";
		mes "これでこれを食堂に";
		mes "持って行けば完璧です！";
		next;
		mes "[料理長]";
		mes "何をしていますか!!";
		mes "早く料理を持って";
		mes "食堂に走りなさい！";
		next;
		mes "[料理長]";
		mes "料理が無くなった皿に";
		mes "すばやく補充するのも";
		mes "王室料理人の能力です!!";
		set EP16_7QUE,14;
		delquest 11398;
		setquest 11399;
		close2;
		cutin "ep16cook_king_1.bmp",255;
		end;
	}
	end;
}

prt_cas.gat,319,211,3	script	王室ソース造りの達人#ep16_1	749,{
	switch(EP16_7QUE) {
	case 0:
	case 1:
		mes "[オリエンタルオイシスター]";
		mes "うむ……この食欲そそる味！";
		mes "正確な配合というのは";
		mes "いつでも美しい……";
		close;
	case 2:
		mes "[オリエンタルオイシスター]";
		mes "おいしいソースをつくる達人、";
		mes "それはオリエンタルオイシスターの";
		mes "ことをいうんだぜ！";
		next;
		menu "料理長がソースがないと言ってました",-;
		mes "[オリエンタルオイシスター]";
		mes "なにぃ～～！";
		mes "ソースがなくなってしまっただと？";
		emotion 0;
		next;
		mes "[オリエンタルオイシスター]";
		mes "こいつは大変だぜ！";
		mes "あの料理長の性格……";
		mes "遅れてしまったら何をされるか……";
		next;
		mes "[オリエンタルオイシスター]";
		mes "先週、お皿を割って";
		mes "生きたままツルツルそばにされた";
		mes "皿洗いがいたと聞いたぜ！";
		next;
		mes "[オリエンタルオイシスター]";
		mes "うむ……";
		mes "急いでソースを完成させよう。";
		mes "君！";
		mes "少し手伝ってくれないか？";
		next;
		mes "[オリエンタルオイシスター]";
		mes "先ほど、弟子の奴が";
		mes "ソースに滑って";
		mes "お尻を強打してしまい";
		mes "医務室に運ばれてしまった。";
		emotion 28;
		next;
		mes "[オリエンタルオイシスター]";
		mes "是非、助手がほしいんだぜ！";
		mes "いっしょに";
		mes "最高のソースを作るんだ！";
		next;
		mes "[オリエンタルオイシスター]";
		switch(rand(4)) {
		case 0:
			mes "それではまず、さわやかな";
			mes "味を出せる材料を";
			mes "持って来てくれ。";
			set EP16_7QUE,4;
			delquest 11395;
			setquest 11396;
			setquest 11428;
			break;
		case 1:
			mes "それではグニャグニャする";
			mes "食感を生かす材料を";
			mes "持って来てくれ。";
			set EP16_7QUE,4;
			delquest 11395;
			setquest 11396;
			setquest 11429;
			break;
		case 2:
			mes "それでは華麗に光る材料を";
			mes "持って来てくれ。";
			set EP16_7QUE,4;
			delquest 11395;
			setquest 11396;
			setquest 11430;
			break;
		case 3:
			mes "それではやわらかい味を";
			mes "出してくれる材料を";
			mes "持って来てくれ。";
			set EP16_7QUE,4;
			delquest 11395;
			setquest 11396;
			setquest 11431;
			break;
		}
		close;
	case 3:
		mes "[オリエンタルオイシスター]";
		mes "やれやれ……";
		mes "ソースにとって材料とは";
		mes "命のような物なんだ。";
		mes "まちがったら、";
		mes "そこでソース終了だよ。";
		next;
		mes "[オリエンタルオイシスター]";
		mes "では最初から作り直してみよう！";
		next;
		mes "[オリエンタルオイシスター]";
		switch(rand(4)) {
		case 0:
			mes "それではまず、さわやかな";
			mes "味を出せる材料を";
			mes "持って来てくれ。";
			setquest 11428;
			break;
		case 1:
			mes "それではグニャグニャする";
			mes "食感を生かす材料を";
			mes "持って来てくれ。";
			setquest 11429;
			break;
		case 2:
			mes "それでは華麗に光る材料を";
			mes "持って来てくれ。";
			setquest 11430;
			break;
		case 3:
			mes "それではやわらかい味を";
			mes "出してくれる材料を";
			mes "持って来てくれ。";
			setquest 11431;
			break;
		}
		set EP16_7QUE,4;
		close;
	case 4:
		mes "[オリエンタルオイシスター]";
		mes "急いで材料を持って来てくれ！";
		close;
	case 5:
		mes "[オリエンタルオイシスター]";
		mes "うむ、素晴らしい！";
		next;
		mes "[オリエンタルオイシスター]";
		switch(rand(4)) {
		case 0:
			mes "次はさわやかな味を出せる";
			mes "材料を持って来てくれ。";
			setquest 11428;
			break;
		case 1:
			mes "次はグニャグニャする";
			mes "食感を生かす材料を";
			mes "持って来てくれ。";
			setquest 11429;
			break;
		case 2:
			mes "次は華麗に光る材料を";
			mes "持って来てくれ。";
			setquest 11430;
			break;
		case 3:
			mes "次はやわらかい味を";
			mes "出してくれる材料を";
			mes "持って来てくれ。";
			setquest 11431;
			break;
		}
		set EP16_7QUE,6;
		close;
	case 6:
		mes "[オリエンタルオイシスター]";
		mes "急いで材料を持って来てくれ！";
		close;
	case 7:
		mes "[オリエンタルオイシスター]";
		mes "うむ、素晴らしい！";
		next;
		mes "[オリエンタルオイシスター]";
		switch(rand(4)) {
		case 0:
			mes "次はさわやかな味を出せる";
			mes "材料を持って来てくれ。";
			setquest 11428;
			break;
		case 1:
			mes "次はグニャグニャする";
			mes "食感を生かす材料を";
			mes "持って来てくれ。";
			setquest 11429;
			break;
		case 2:
			mes "次は華麗に光る材料を";
			mes "持って来てくれ。";
			setquest 11430;
			break;
		case 3:
			mes "次はやわらかい味を";
			mes "出してくれる材料を";
			mes "持って来てくれ。";
			setquest 11431;
			break;
		}
		set EP16_7QUE,8;
		close;
	case 8:
		mes "[オリエンタルオイシスター]";
		mes "急いで材料を持って来てくれ！";
		close;
	case 9:
		mes "[オリエンタルオイシスター]";
		mes "うむ、素晴らしい！";
		next;
		mes "[オリエンタルオイシスター]";
		switch(rand(4)) {
		case 0:
			mes "次はさわやかな味を出せる";
			mes "材料を持って来てくれ。";
			setquest 11428;
			break;
		case 1:
			mes "次はグニャグニャする";
			mes "食感を生かす材料を";
			mes "持って来てくれ。";
			setquest 11429;
			break;
		case 2:
			mes "次は華麗に光る材料を";
			mes "持って来てくれ。";
			setquest 11430;
			break;
		case 3:
			mes "次はやわらかい味を";
			mes "出してくれる材料を";
			mes "持って来てくれ。";
			setquest 11431;
			break;
		}
		set EP16_7QUE,10;
		close;
	case 10:
		mes "[オリエンタルオイシスター]";
		mes "急いで材料を持って来てくれ！";
		close;
	case 11:
		mes "[オリエンタルオイシスター]";
		mes "おお、すばらしい！";
		mes "お蔭で完璧なソースが出来た！";
		mes "早く料理長に持って行きなさい！";
		next;
		mes "[オリエンタルオイシスター]";
		mes "それにしても";
		mes "君にはソースをつくる才能がある。";
		mes "私と一緒にソース道を";
		mes "歩んでみるのはどうだ？";
		set EP16_7QUE,12;
		delquest 11396;
		setquest 11397;
		close;
	default:
		mes "[オリエンタルオイシスター]";
		mes "君にはソースをつくる才能がある。";
		mes "私と一緒にソース道を";
		mes "歩んでみるのはどうだ？";
		close;
	}
}

prt_cas.gat,303,216,5	script	ムカージュース#ep16_1	10043,{
	switch(EP16_7QUE) {
	case 4:
	case 6:
	case 8:
	case 10:
		if(checkquest(11428)) {
			mes "[オリエンタルオイシスター]";
			mes "そう！　それだ！";
			mes "早くこっちに持って来てくれ！";
			emotion 0,"王室ソース造りの達人#ep16_1";
			set EP16_7QUE,EP16_7QUE+1;
			delquest 11428;
			close;
		}
		if(checkquest(11429) || checkquest(11430) || checkquest(11431)) {
			mes "[オリエンタルオイシスター]";
			mes "ひいいいいいいいいいっ!!";
			mes "ソースを完全にダメにしちまった!!";
			next;
			mes "[オリエンタルオイシスター]";
			mes "もうこのソースは使えない！";
			mes "最初から新しく作りなおさないと!!";
			set EP16_7QUE,3;
			if(checkquest(11429))
				delquest 11429;
			if(checkquest(11430))
				delquest 11430;
			if(checkquest(11431))
				delquest 11431;
			close;
		}
		break;
	}
	mes "‐みずみずしいムカーを";
	mes "　すりおろして作ったジュース。";
	mes "　爽やかな味がする‐";
	close;
}

prt_cas.gat,308,204,5	script	ポリンゼリー #ep16_1	10042,{
	switch(EP16_7QUE) {
	case 4:
	case 6:
	case 8:
	case 10:
		if(checkquest(11429)) {
			mes "[オリエンタルオイシスター]";
			mes "そう！　それだ！";
			mes "早くこっちに持って来てくれ！";
			emotion 0,"王室ソース造りの達人#ep16_1";
			set EP16_7QUE,EP16_7QUE+1;
			delquest 11429;
			close;
		}
		if(checkquest(11428) || checkquest(11430) || checkquest(11431)) {
			mes "[オリエンタルオイシスター]";
			mes "ひいいいいいいいいいっ!!";
			mes "ソースを完全にダメにしちまった!!";
			next;
			mes "[オリエンタルオイシスター]";
			mes "もうこのソースは使えない！";
			mes "最初から新しく作りなおさないと!!";
			set EP16_7QUE,3;
			if(checkquest(11428))
				delquest 11428;
			if(checkquest(11430))
				delquest 11430;
			if(checkquest(11431))
				delquest 11431;
			close;
		}
		break;
	}
	mes "‐やわらかいポリンで作ったゼリー。";
	mes "　グニャグニャする食感を";
	mes "　生かしている……‐";
	close;
}

prt_cas.gat,338,206,5	script	光る草#ep16_1	10046,{
	switch(EP16_7QUE) {
	case 4:
	case 6:
	case 8:
	case 10:
		if(checkquest(11430)) {
			mes "[オリエンタルオイシスター]";
			mes "そう！　それだ！";
			mes "早くこっちに持って来てくれ！";
			emotion 0,"王室ソース造りの達人#ep16_1";
			set EP16_7QUE,EP16_7QUE+1;
			delquest 11430;
			close;
		}
		if(checkquest(11428) || checkquest(11429) || checkquest(11431)) {
			mes "[オリエンタルオイシスター]";
			mes "ひいいいいいいいいいっ!!";
			mes "ソースを完全にダメにしちまった!!";
			next;
			mes "[オリエンタルオイシスター]";
			mes "もうこのソースは使えない！";
			mes "最初から新しく作りなおさないと!!";
			set EP16_7QUE,3;
			if(checkquest(11428))
				delquest 11428;
			if(checkquest(11429))
				delquest 11429;
			if(checkquest(11431))
				delquest 11431;
			close;
		}
		break;
	}
	mes "‐ピカピカと光る草を";
	mes "　すりおろして作った粉。";
	mes "　料理に華麗さをプラスしてくれる‐";
	close;
}

prt_cas.gat,330,211,5	script	ミノタウロスバター#ep16	10044,{
	switch(EP16_7QUE) {
	case 4:
	case 6:
	case 8:
	case 10:
		if(checkquest(11431)) {
			mes "[オリエンタルオイシスター]";
			mes "そう！　それだ！";
			mes "早くこっちに持って来てくれ！";
			emotion 0,"王室ソース造りの達人#ep16_1";
			set EP16_7QUE,EP16_7QUE+1;
			delquest 11431;
			close;
		}
		if(checkquest(11428) || checkquest(11429) || checkquest(11430)) {
			mes "[オリエンタルオイシスター]";
			mes "ひいいいいいいいいいっ!!";
			mes "ソースを完全にダメにしちまった!!";
			next;
			mes "[オリエンタルオイシスター]";
			mes "もうこのソースは使えない！";
			mes "最初から新しく作りなおさないと!!";
			set EP16_7QUE,3;
			if(checkquest(11428))
				delquest 11428;
			if(checkquest(11429))
				delquest 11429;
			if(checkquest(11430))
				delquest 11430;
			close;
		}
		break;
	}
	mes "‐ミノタウロスの";
	mes "　牛乳で作ったバター。";
	mes "　意外にとてもやわらかい";
	mes "　味がする‐";
	close;
}

prt_cas.gat,315,204,1	script	料理人#ep16_1	886,{
	mes "[料理人]";
	mes "私の料理に間違いはない！";
	close;
}

prt_cas.gat,313,204,3	script	料理人#ep16_2	886,{
	mes "[料理人]";
	mes "あの料理長と一緒に";
	mes "料理を作れるなんて";
	mes "夢のようです！";
	close;
}

prt_cas.gat,313,202,3	script	料理人#ep16_3	886,{
	mes "[料理人]";
	mes "おいちい!!";
	close;
}

prt_cas.gat,313,200,3	script	料理人#ep16_4	886,{
	mes "[料理人]";
	mes "私はどっちかといえば……";
	mes "砂糖よりは塩派です！";
	close;
}

prt_cas.gat,313,196,3	script	料理人#ep16_5	886,{
	mes "[料理人]";
	mes "チューニングの終わりは";
	mes "純正なり。";
	mes "料理の終わりは、";
	mes "結局原材料のそのままの";
	mes "味を楽しむこと……";
	close;
}

prt_cas.gat,313,194,3	script	料理人#ep16_6	886,{
	mes "[料理人]";
	mes "料理長と～結婚したい～♪";
	unittalk "料理人 : 料理長と～結婚したい～♪",1;
	close;
}

prt_cas.gat,302,205,5	script	皿洗い#ep16_1	883,{
	switch(EP16_7QUE) {
	case 20:
		if(countitem(6935) < 3) {
			mes "[皿洗い]";
			mes "拭いても……拭いても……";
			mes "終わりがない！";
			next;
			mes "[皿洗い]";
			mes "だけどこれが皿洗いの宿命！";
			next;
			mes "[皿洗い]";
			mes "それが私の宿命なら";
			mes "受け入れよう!!";
			next;
			mes "[皿洗い]";
			mes "早く皿を私に！";
			mes "皿をもっと！";
			next;
			mes "[皿洗い]";
			mes "私は耐えます！";
			mes "この宿命に!!!!";
			close;
		}
		mes "[皿洗い]";
		mes "ふふふ……";
		mes "皿の追加かい？";
		mes "俺の手にかかれば";
		mes "どんな皿でもピカピカさ。";
		next;
		mes "[皿洗い]";
		mes "……そういえば";
		mes "先ほどから料理長が探していたが。";
		mes "もしかして";
		mes "問題でも発生したのかい？";
		set EP16_7QUE,21;
		delitem 6935,3;
		delquest 11419;
		setquest 11420;
		close;
	case 21:
		mes "[皿洗い]";
		mes "……そういえば";
		mes "先ほどから料理長が探していたが。";
		mes "もしかして";
		mes "問題でも発生したのかい？";
		close;
	case 22:
		if(checkquest(11427)) {
			if(checkquest(11427) & 0x2) {	// TODO
				mes "[皿洗い]";
				mes "未調査";
				delquest 11427;
				close;
			}
			mes "[皿洗い]";
			mes "ちょっと無理してないかい？";
			mes "今日は少し休んで";
			mes "明日また来るのがいいかと……";
			close;
		}
		if(checkquest(11426)) {
			if(countitem(6935) < 2) {
				mes "[皿洗い]";
				mes "拭いても……拭いても……";
				mes "終わりがない！";
				next;
				mes "[皿洗い]";
				mes "だけどこれが皿洗いの宿命！";
				next;
				mes "[皿洗い]";
				mes "それが私の宿命なら";
				mes "受け入れよう!!";
				next;
				mes "[皿洗い]";
				mes "早く皿を私に！";
				mes "皿をもっと！";
				next;
				mes "[皿洗い]";
				mes "私は耐えます！";
				mes "この宿命に!!!!";
				close;
			}
			if(checkitemblank() < 1) {
				mes "‐荷物をこれ以上持てません";
				mes "　荷物に1個以上の空きを";
				mes "　作ってください‐";
				close;
			}
			mes "[皿洗い]";
			mes "ふふふ……";
			mes "皿の追加かい？";
			mes "俺の手にかかれば";
			mes "どんな皿でもピカピカさ。";
			delitem 6935,2;
			delquest 11426;
			setquest 11427;
			getitem 6919,1;
			close;
		}
		mes "[皿洗い]";
		mes "もしかして手伝いに";
		mes "来てくれたんですか？";
		mes "皿を綺麗にすると";
		mes "心もキレイになる";
		mes "気がする人なんです？";
		next;
		mes "[皿洗い]";
		mes "まあそんな気分に";
		mes "なるのは、普通のことです！";
		mes "というわけで";
		mes "皿を2枚持って来てください！";
		next;
		mes "[皿洗い]";
		mes "大事な皿なので気を付けて下さい！";
		setquest 11426;
		close;
	default:
		mes "[皿洗い]";
		mes "くっ……";
		mes "沈まれ、俺の左手の湿疹！";
		unittalk "皿洗い : 沈まれ、俺の左手の湿疹！",1;
		next;
		mes "[皿洗い]";
		mes "クリーム!!";
		mes "クリームを早く!!";
		unittalk "皿洗い : クリームを早く!!",1;
		close;
	}
}

prt_cas.gat,358,124,0	script	グリフォン焼き#ep16_1	10131,{
	if(EP16_7QUE == 14) {
		mes "‐あなたはグリフォン焼きを";
		mes "　テーブルに置いた‐";
		next;
		mes "[タマリン]";
		mes "……はあ、";
		mes "食べられないのが残念です。";
		mes "こんなにいいにおいを";
		mes "しているのに。";
		unittalk getnpcid(0,"タマリン#ep16_1"),"タマリン : ……はあ",1;
		cutin "tama_cook_4.bmp",2;
		set EP16_7QUE,15;
		delquest 11399;
		setquest 11413;
		close2;
		cutin "tama_cook_4.bmp",255;
		end;
	}
	mes "‐美味しそうな";
	mes "　グリフォン焼きがある‐";
	close;
}

prt_cas.gat,361,142,5	script	タマリン#ep16_1	10124,{
	switch(EP16_7QUE) {
	case 15:
		mes "[タマリン]";
		mes "……はあ、";
		mes "一体何なんだ……";
		emotion 32;
		unittalk "タマリン : ……はあ",1;
		cutin "tama_cook_4.bmp",2;
		next;
		mes "[タマリン]";
		mes "あっ！";
		mes strcharinfo(0) +"様";
		mes "ではありませんか？";
		emotion 0;
		cutin "tama_cook_2.bmp",2;
		next;
		mes "[タマリン]";
		mes "今回の祝宴には";
		mes "魔王モロク討伐に貢献した";
		mes "冒険者たちが集まると聞いていたので、";
		mes "噂に聞くあなたにも";
		mes "会えるのではと思っていました。";
		cutin "tama_cook_1.bmp",2;
		next;
		mes "[タマリン]";
		mes "祝宴は楽しんで……";
		next;
		mes "[タマリン]";
		mes "……って、その姿は";
		emotion 23;
		cutin "tama_cook_2.bmp",2;
		next;
		mes "[タマリン]";
		mes "まさか！";
		mes strcharinfo(0) +"様も";
		mes "やられましたか!?";
		next;
		mes "[タマリン]";
		mes "私は、仲間のテューリアンが";
		mes "食べ物が足りないと言うので";
		mes "周辺をうろうろしていたら、";
		mes "突然、料理長が探していると言われて";
		mes "連れてこられまして……";
		cutin "tama_cook_1.bmp",2;
		next;
		mes "[タマリン]";
		mes "断ろうとしたら";
		mes "生きたままジュースにして";
		mes "シロマアイスティーならぬ";
		mes "タマリンアイスティーにして";
		mes "チューチュー吸ったろか！";
		mes "と料理長に脅迫されて……";
		cutin "tama_cook_4.bmp",2;
		next;
		mes "[タマリン]";
		mes "祝宴の準備が忙しすぎて";
		mes "説明する機会もとれないまま、";
		mes "結局はこんな風に……";
		emotion 28;
		next;
		mes "[タマリン]";
		mes "みなさんとても忙しそうで、";
		mes "逃げ出すのも忍びないし……";
		cutin "tama_cook_1.bmp",2;
		next;
		mes "[タマリン]";
		mes "私はもうダメみたいです……";
		next;
		mes "[タマリン]";
		mes "もし祝宴場でテューリアンを";
		mes "見かけたら伝えてください。";
		mes "タマリンはもう戻れないと……";
		set EP16_7QUE,16;
		delquest 11413;
		setquest 11414;
		close2;
		cutin "tama_cook_1.bmp",255;
		end;
	case 16:
	case 17:
	case 18:
		mes "[タマリン]";
		mes "私はもうダメみたいです……";
		cutin "tama_cook_4.bmp",2;
		next;
		mes "[タマリン]";
		mes "もし祝宴場でテューリアンを";
		mes "見かけたら伝えてください。";
		mes "タマリンはもう戻れないと……";
		close2;
		cutin "tama_cook_4.bmp",255;
		end;
	case 19:
		mes "[タマリン]";
		mes "……ふう、";
		mes "なんて投げやりな「頑張れ」";
		mes "なんだ……。";
		mes "やっぱりからかったことを";
		mes "マークは根に持ってますね。";
		cutin "tama_cook_1.bmp",2;
		next;
		mes "[タマリン]";
		mes "仕方ありません。";
		mes "仕事を続けますか……。";
		mes "はぁ……";
		next;
		mes "[タマリン]";
		mes "実は、使用済みの皿を集めて";
		mes "厨房に持って行くように";
		mes "言われているんです。";
		next;
		mes "[タマリン]";
		mes "もし手が空いているのでしたら、";
		mes strcharinfo(0)+"様も";
		mes "一緒にお皿を集めてもらえませんか？";
		mes "二人でやれば";
		mes "きっとすぐ終わると思います。";
		next;
		mes "[タマリン]";
		mes "よろしくお願いします。";
		mes "早く終わらせて美味しい物を";
		mes "一緒に食べましょう！";
		cutin "tama_cook_3.bmp",2;
		set EP16_7QUE,20;
		delquest 11417;
		setquest 11419;
		close2;
		cutin "tama_cook_3.bmp",255;
		end;
	case 20:
		mes "[タマリン]";
		mes "よろしくお願いします。";
		mes "早く終わらせて美味しい物を";
		mes "一緒に食べましょう！";
		cutin "tama_cook_3.bmp",2;
		close2;
		cutin "tama_cook_3.bmp",255;
		end;
	case 21:
		mes "[タマリン]";
		mes "次にやるべき仕事が……";
		mes "どうしてこんなことに……";
		cutin "tama_cook_1.bmp",2;
		close2;
		cutin "tama_cook_1.bmp",255;
		end;
	case 22:
		mes "[タマリン]";
		mes "ふう……！";
		mes strcharinfo(0)+"様。";
		mes "ありがとうございます。";
		mes "お陰様で思ったより早く";
		mes "仕事が片付きました。";
		cutin "tama_cook_3.bmp",2;
		next;
		mes "[タマリン]";
		mes "それにしても、";
		mes "やっと解放されると";
		mes "期待していたのに……";
		next;
		mes "[タマリン]";
		mes "料理長に報告しようとした瞬間、";
		mes "今度はマークに捕まってしまい";
		mes "この仕事に戻ってしまいました……";
		cutin "tama_cook_1.bmp",2;
		next;
		mes "[タマリン]";
		mes "諦めが肝心といいますし、";
		mes "ここは諦めて働きます……";
		mes "きっとテューリアン達と";
		mes "出会った時から、";
		mes "私の運命は決められて";
		mes "いたのでしょう……";
		emotion 32;
		cutin "tama_cook_3.bmp",2;
		close2;
		cutin "tama_cook_3.bmp",255;
		end;
	default:
		mes "[タマリン]";
		mes "お皿を落としてしまった……";
		unittalk "タマリン : ……はあ",1;
		emotion 32;
		cutin "tama_cook_4.bmp",2;
		close2;
		cutin "tama_cook_4.bmp",255;
		end;
	}
}

prt_cas.gat,111,235,3	script	テューリアン#ep16_1	628,{
	switch(EP16_7QUE) {
	case 16:
		if(ECL_1QUE < 6) {
			mes "[テューリアン]";
			mes "お前もここに招待された";
			mes "冒険者だろ？";
			mes "俺もだ。";
			cutin "bu_du1.bmp",2;
			next;
			mes "[テューリアン]";
			mes "名前は……";
			mes strcharinfo(0)+"か！";
			mes "よろしくな！";
		} else {
			mes "[テューリアン]";
			mes "おお……!?";
			mes strcharinfo(0) +"!!";
			mes "俺だよ、俺!!";
			mes "久しぶりだなあ！";
			emotion 18;
			cutin "bu_du1.bmp",2;
		}
		next;
		mes "[テューリアン]";
		mes "それにしても";
		mes "すげぇ祝宴だな！";
		mes "料理も美味いんだぜ！";
		mes strcharinfo(0)+"も、";
		mes "グリフォン焼きは食べたか？";
		next;
		menu "タマリンからの伝言を伝える",-;
		mes "[テューリアン]";
		mes "へえ！";
		mes "だから戻ってこなかったのか。";
		mes "毎回よく居なくなるから、";
		mes "また迷子になってるのかと思って、";
		mes "心配はしてなかったけどな！";
		emotion 23;
		cutin "bu_du5.bmp",2;
		next;
		mes "[テューリアン]";
		mes "そういえば……";
		mes "マークもここで働いてるんだ！";
		cutin "bu_du3.bmp",2;
		next;
		mes "[テューリアン]";
		mes "マークは兄さんに頼まれて、";
		mes "無理やり働かされてる";
		mes "らしいけどな。";
		cutin "bu_du2.bmp",2;
		next;
		mes "[テューリアン]";
		mes "そういえば……";
		mes "さっきマークと会ったのは";
		mes "どこだったかな？";
		cutin "bu_du3.bmp",2;
		next;
		mes "[テューリアン]";
		mes "マギー！";
		mes "さっき、マークとどこで会ったか";
		mes "覚えてるかー？";
		set EP16_7QUE,17;
		delquest 11414;
		setquest 11415;
		close2;
		cutin "bu_du3.bmp",255;
		end;
	case 17:
		mes "[テューリアン]";
		mes "そういえば……";
		mes "マークもここで働いてるんだ！";
		cutin "bu_du3.bmp",2;
		next;
		mes "[テューリアン]";
		mes "マークは兄さんに頼まれて、";
		mes "無理やり働かされてる";
		mes "らしいけどな。";
		cutin "bu_du2.bmp",2;
		next;
		mes "[テューリアン]";
		mes "そういえば……";
		mes "さっきマークと会ったのは";
		mes "どこだったかな？";
		cutin "bu_du3.bmp",2;
		next;
		mes "[テューリアン]";
		mes "マギー！";
		mes "さっき、マークとどこで会ったか";
		mes "覚えてるかー？";
		close2;
		cutin "bu_du3.bmp",255;
		end;
	case 18:
		mes "[テューリアン]";
		mes "聞いたか？";
		mes "マークは階段の上にいるらしい。";
		mes "会いに行ってやれば、";
		mes "きっと喜ぶと思うぞ。";
		cutin "bu_du2.bmp",2;
		close2;
		cutin "bu_du2.bmp",255;
		end;
	case 19:
	case 20:
	case 21:
		mes "[テューリアン]";
		mes "さすが、マドリドだな！";
		mes "英雄のために祝宴にまで来て";
		mes "仕事をさせられるんだからな。";
		mes "わはははははははっ！";
		cutin "bu_du2.bmp",2;
		close2;
		cutin "bu_du2.bmp",255;
		end;
	default:
		if(ECL_1QUE < 6) {
			mes "[テューリアン]";
			mes "お前もここに招待された";
			mes "冒険者だろ？";
			mes "俺もだ。";
			cutin "bu_du1.bmp",2;
			next;
			mes "[テューリアン]";
			mes "名前は……";
			mes strcharinfo(0)+ "か！";
			mes "よろしくな！";
			next;
			mes "[テューリアン]";
			mes "それにしても";
			mes "すげぇ祝宴だな！";
			mes "料理も美味いんだぜ！";
			mes strcharinfo(0)+ "も、";
			mes "グリフォン焼きは食べたか？";
			next;
			mes "[テューリアン]";
			mes "このワザとらしい鶏肉味！";
			mes "グリフォンがこんなにも";
			mes "美味しいとは思わなかった！";
			mes "まだ食べてないなら、";
			mes "食べたほうがいいぞ！";
			cutin "bu_du2.bmp",2;
			close2;
			cutin "bu_du2.bmp",255;
			end;
		}
		mes "[テューリアン]";
		mes "おお……!?";
		mes strcharinfo(0)+ "!!";
		mes "俺だよ、俺!!";
		mes "久しぶりだなあ！";
		emotion 18;
		cutin "bu_du1.bmp",2;
		next;
		mes "[テューリアン]";
		mes "それにしても";
		mes "すげぇ祝宴だな！";
		mes "料理も美味いんだぜ！";
		mes strcharinfo(0)+ "も、";
		mes "グリフォン焼きは食べたか？";
		next;
		mes "[テューリアン]";
		mes "このワザとらしい鶏肉味！";
		mes "グリフォンがこんなにも";
		mes "美味しいとは思わなかった！";
		mes "まだ食べてないなら、";
		mes "食べたほうがいいぞ！";
		cutin "bu_du2.bmp",2;
		close2;
		cutin "bu_du2.bmp",255;
		end;
	}
}

prt_cas.gat,111,234,3	script	マギスティン#ep16_1	612,{
	switch(EP16_7QUE) {
	case 17:
		mes "[マギスティン]";
		mes "あ……";
		mes "マークさんなら……";
		cutin "bu_maggi1.bmp",2;
		next;
		mes "[マギスティン]";
		mes "あちらの階段の上で会いましたよ。";
		mes "忙しそうだったので、";
		mes "あまり話すことは";
		mes "出来ませんでしたけど……";
		cutin "bu_maggi3.bmp",2;
		next;
		mes "[マギスティン]";
		mes "マークさんの分の料理を";
		mes "残しておこうと思うのですが";
		mes "テューが片っ端から";
		mes "食べてしまうので、";
		mes "少し困っています……";
		emotion 16;
		cutin "bu_maggi2.bmp",2;
		set EP16_7QUE,18;
		delquest 11415;
		setquest 11416;
		close2;
		cutin "bu_maggi2.bmp",255;
		end;
	case 18:
		mes "[マギスティン]";
		mes "あ……";
		mes "マークさんなら……";
		cutin "bu_maggi1.bmp",2;
		next;
		mes "[マギスティン]";
		mes "あちらの階段の上で会いましたよ。";
		mes "忙しそうだったので、";
		mes "あまり話すことは";
		mes "出来ませんでしたけど……";
		cutin "bu_maggi3.bmp",2;
		close2;
		cutin "bu_maggi3.bmp",255;
		end;
	case 19:
	case 20:
	case 21:
		mes "[マギスティン]";
		mes "……グリフォン焼きは";
		mes "少し苦手です……";
		mes "テューは美味しいって";
		mes "凄い速さで食べていましたけど。";
		cutin "bu_maggi2.bmp",2;
		close2;
		cutin "bu_maggi2.bmp",255;
		end;
	default:
		mes "[マギスティン]";
		mes "あ……こんにちは。";
		cutin "bu_maggi2.bmp",2;
		close2;
		cutin "bu_maggi2.bmp",255;
		end;
	}
}

prt_cas.gat,82,268,5	script	マークイシャ#ep16_1	10123,{
	switch(EP16_7QUE) {
	case 18:
		mes "[マークイシャ]";
		mes "こんにちは。";
		mes strcharinfo(0)+"様。";
		mes "祝宴は楽しんでいますか？";
		mes "何か必要なものはありますか？";
		unittalk "マークイシャ : 祝宴は楽しんでいますか？",1;
		emotion 2;
		cutin "mark_wt_4.bmp",0;
		next;
		menu "タマリンのことを話す",-;
		mes "[マークイシャ]";
		mes "タマリンが？";
		mes "……そうですか。";
		mes "私が働いているのを";
		mes "からかっていたのに！";
		emotion 6;
		cutin "mark_wt_2.bmp",0;
		next;
		mes "[マークイシャ]";
		mes "フフフフフフ。";
		mes strcharinfo(0)+"様。";
		mes "タマリンにどうか、";
		mes "頑張れと伝えてください。";
		cutin "mark_wt_4.bmp",0;
		set EP16_7QUE,19;
		delquest 11416;
		setquest 11417;
		close2;
		cutin "mark_wt_4.bmp",255;
		end;
	case 19:
		mes "[マークイシャ]";
		mes strcharinfo(0)+"様。";
		mes "タマリンにどうか";
		mes "頑張れとお伝えください。";
		cutin "mark_wt_1.bmp",0;
		next;
		mes "[マークイシャ]";
		mes "祝宴準備から抜けだせるなら";
		mes "自分で言いたいのですが……";
		mes "ちょっと難しそうなので";
		mes "フフフ、残念です。";
		close2;
		cutin "mark_wt_1.bmp",255;
		end;
	default:
		mes "[マークイシャ]";
		mes "こんにちは。";
		mes "祝宴は楽しんでいますか？";
		mes "何か必要なものはありますか？";
		unittalk "マークイシャ : 祝宴は楽しんでいますか？",1;
		emotion 2;
		cutin "mark_wt_4.bmp",0;
		close2;
		cutin "mark_wt_4.bmp",255;
		end;
	}
}

prt_cas.gat,341,79,2	script	アルプオカート#ep16_1	615,{
	mes "[アルプオカート]";
	mes "!!!!";
	mes "この本はあの伝説の……";
	unittalk "アルプオカート : !!!!",1;
	cutin "bu_alp4.bmp",2;
	next;
	mes "[アルプオカート]";
	mes "王宮の祝宴だといわれて";
	mes "迷っていたんだが……";
	mes "……来て……よかった……";
	close2;
	cutin "bu_alp4.bmp",255;
	end;
}

prt_cas.gat,373,57,8	script	オリバー#ep16_1	626,{
	mes "[オリバー]";
	mes "わぁ！　これも！";
	mes "あれも！　それも！";
	mes "全部あるよ！";
	unittalk "オリバー : やっぱり、王宮だね！",1;
	cutin "bu_oliver4.bmp",0;
	next;
	mes "[オリバー]";
	mes "あ、この本は僕も";
	mes "持っていない物だ！";
	next;
	mes "[オリバー]";
	mes "やっぱり王宮は凄いなあ……";
	close2;
	cutin "bu_oliver4.bmp",255;
	end;
}

prt_cas.gat,76,236,3	script	バゼット#ep16_1	883,{
	mes "[バゼット]";
	mes "まだ研究しなければならないものが";
	mes "山のように残っているというのに";
	mes "こんな祝宴に連れてこられては困る！";
	next;
	mes "[バゼット]";
	mes "テオレは上手く出来ているのか……";
	mes "不安でしかない。";
	close;
}

prt_cas.gat,97,248,5	script	王宮演奏家#orint	741,{
	mes "[王宮演奏家オリント]";
	mes "業務中の私語は禁止です。";
	mes "演奏家の私に";
	mes "なにか御用でしょうか。";
	next;
	if(select("一曲お願いします","対話を終える") == 2) {
		mes "‐あなたは";
		mes "　演奏の邪魔になったことを";
		mes "　一言詫びて";
		mes "　彼から離れた‐";
		close;
	}
	misceffect 969,"王宮演奏家#3";
	mes "[王宮演奏家オリント]";
	switch(rand(14)) {
	case 0:  set '@title$,"<I miss you>";			set '@no$,"04";		break;
	case 1:  set '@title$,"<Marschmallow Waltz>";	set '@no$,"145";	break;
	case 2:  set '@title$,"<Splendide Dreams>";		set '@no$,"128";	break;
	case 3:  set '@title$,"<Jittering Nightmare>";	set '@no$,"160";	break;
	case 4:  set '@title$,"<Alpen Rose>";			set '@no$,"109";	break;
	case 5:  set '@title$,"<Tales of East>";		set '@no$,"115";	break;
	case 6:  set '@title$,"<Theme of Alberta>";		set '@no$,"15";		break;
	case 7:  set '@title$,"<Yuna Song>";			set '@no$,"33";		break;
	case 8:  set '@title$,"<Eclage>";				set '@no$,"155";	break;
	case 9:  set '@title$,"<Dazzling Snow>";		set '@no$,"137";	break;
	case 10: set '@title$,"<Dream of Whale>";		set '@no$,"117";	break;
	case 11: set '@title$,"<One Step Closer>";		set '@no$,"30";		break;
	case 12: set '@title$,"<Not so Far away>";		set '@no$,"74";		break;
	default:
		mes "準備していた曲ではありませんが、";
		mes "今回は私のお気に入りを";
		mes "聞いていただくのはいかがでしょう。";
		next;
		mes "[王宮演奏家オリント]";
		mes "ある島を表現した";
		mes "<Good Morning>を";
		mes "演奏させていただきます。";
		musiceffect "111";
		unittalk getnpcid(0,"祝宴場の貴族#4"),"祝宴場の貴族 : こ、この曲は最高だ!!体に力がみなぎる！",1;
		unittalk getnpcid(0,"祝宴場客#5"),"祝宴場客 : プロンテラ王家の繁栄を祝う曲だ、間違いない！",1;
		unittalk getnpcid(0,"祝宴場客#6"),"祝宴場客 : これを療養中のトリスタン3世様が聞けば病が治るだろう!!",1;
		close;
	}
	mes '@title$+ "を";
	mes "演奏させていただきます。";
	musiceffect '@no$;
	close;
}

prt_cas.gat,95,248,5	script	王宮演奏家#occi	485,{
	emotion 2;
	mes "[王宮演奏家オックシー]";
	mes "私とオリントはずっと昔から";
	mes "こういう素敵な場所で";
	mes "合奏するのが夢だったの。";
	mes "ね、オリント？";
	next;
	emotion 9,"王宮演奏家#orint";
	mes "[王宮演奏家オリント]";
	mes "業務中に私語は禁止だ。";
	next;
	emotion 32;
	mes "[王宮演奏家オックシー]";
	mes "んもう！　真面目なんだから。";
	mes "でも、そういう所が";
	mes "魅力的なのよね♪";
	close;
}

prt_cas.gat,93,248,5	script	王宮演奏家#3	485,{
	emotion 18;
	mes "[王宮演奏家エリー]";
	mes "ドウィット、見て。";
	mes "あの人たち、すごく綺麗……";
	next;
	emotion 33,"王宮演奏家#4";
	mes "[王宮演奏家ドウィット]";
	mes "確かに美しいご婦人達だ。";
	mes "……でも、この煌びやかな風景は";
	mes "君が一番似合うと思うよ。";
	next;
	mes "[王宮演奏家エリー]";
	mes "え……？";
	next;
	emotion 40;
	mes "[王宮演奏家ドウィット]";
	mes "エリー、君は美しい。";
	mes "君の踊りはそれこそ";
	mes "大自然に勝るほどに美しい。";
	next;
	mes "[王宮演奏家ドウィット]";
	mes "君が赤いドレスを身にまとえば";
	mes "大輪のバラよりも鮮烈で";
	mes "君が青いドレスを身にまとえば";
	mes "清流よりもたおやかだ。";
	next;
	mes "[王宮演奏家エリー]";
	mes "え……あの……";
	mes "あ、ありがとう……";
	next;
	emotion 2,"王宮演奏家#occi";
	mes "[王宮演奏家オックシー]";
	mes "あははは！";
	mes "エリーったら顔真っ赤！";
	mes "ところでドウィット、";
	mes "そのドレスを着るのが";
	mes "私だったらどうなの～？";
	next;
	mes "[王宮演奏家ドウィット]";
	mes "オックシー……";
	mes "いくら君達が双子とはいえ";
	mes "私に見分けがつかないとでも";
	mes "思っているのかい？";
	next;
	mes "[王宮演奏家ドウィット]";
	mes "足音はもちろん";
	mes "身のこなしや踊りのクセ、";
	mes "呼吸や鼓動のリズムに至るまで";
	mes "まったくの別物じゃないか。";
	emotion 32,"王宮演奏家#4";
	close;
}

prt_cas.gat,91,248,5	script	王宮演奏家#4	479,{
	mes "[王宮演奏家ドウィット]";
	mes "オリントと初めて会った時は";
	mes "禁欲的で、すべてのことに対して";
	mes "無関心なつまらない男だと";
	mes "思ったものだけれど、";
	mes "その後に素晴らしい集中力を";
	mes "持っていると気づいたんだ。";
	next;
	mes "[王宮演奏家ドウィット]";
	mes "常に努力を怠らず、";
	mes "ベストな状態を保っているからこそ";
	mes "あのような旋律を紡げるのだろう。";
	next;
	mes "[王宮演奏家ドウィット]";
	mes "周囲を顧みずに没頭するから";
	mes "それによって誤解を招くことも";
	mes "多いけれどね。";
	next;
	mes "[王宮演奏家ドウィット]";
	mes "とにかく、私たちがこんな場所で";
	mes "演奏することができたのも";
	mes "オリントのお蔭だと思っている。";
	mes "君も聞きたい曲があるなら";
	mes "オリントに頼んでみるといい。";
	close;
}

prt_cas.gat,113,243,3	script	祝宴場の貴族#1	90,{
	mes "[祝宴場の貴族]";
	mes "私は宴が好きなの。";
	mes "響き渡る音楽、人々が話す声、";
	mes "茶菓を運ぶ侍従たち。";
	mes "この光景を見るために";
	mes "貴族に生まれたようなものよ。";
	close;
}

prt_cas.gat,70,239,5	script	祝宴場の貴族#2	86,{
	mes "[祝宴場の貴族]";
	mes "宴の主役は別に居るが、";
	mes "私も貴族だ。";
	mes "この機会に良い相手と";
	mes "巡り会えるようにしなくては。";
	close;
}

prt_cas.gat,73,232,5	script	祝宴場の貴族#3	967,{
	mes "[祝宴場の貴族]";
	mes "君は宴は好きかい？";
	mes "……僕は嫌いだ。";
	mes "両親に連れてこられたけど";
	mes "早く家に帰って寝たいよ。";
	close;
}

prt_cas.gat,72,227,5	script	祝宴場客#1	766,{
	mes "[祝宴場客]";
	mes "プロンテラで大きな祝宴が";
	mes "開かれると言われてのう。";
	mes "はるばるアマツから来たんじゃ。";
	close;
}

prt_cas.gat,71,227,5	script	祝宴場客#2	763,{
	mes "[祝宴場客]";
	mes "お爺ちゃん、はしゃぎ過ぎて";
	mes "倒れないでね。";
	close;
}

prt_cas.gat,111,228,3	script	祝宴場客#3	421,{
	mes "[祝宴場客]";
	mes "ルーンミッドガッツ王国の";
	mes "商権を握っている貴族たちが";
	mes "一同に集まるこの機会を";
	mes "私たち猫の手が";
	mes "見落とせるはずがないにゃ！";
	next;
	mes "[祝宴場客]";
	mes "私の身長と同じくらい";
	mes "長い契約書を";
	mes "手に入れるのにゃ！";
	close;
}

prt_cas.gat,98,248,5	script	猫#ep16bgm	876,{
	mes "‐猫は演奏家の足にくっつき";
	mes "　まどろんでいる。";
	mes "　あなたには興味がなさそうだ‐";
	close;
}

prt_cas.gat,98,231,5	script	司令官アジフ#ep16	459,{
	cutin "ep13_captin_edq.bmp",2;
	mes "[司令官アジフ]";
	mes "ようやくアッシュ・バキュームでの";
	mes "残務が終わって帰ってきたと思ったら";
	mes "今度は宴会に出席させられるとは。";
	next;
	mes "[司令官アジフ]";
	mes "まったく……";
	mes "俺は家で昼寝でもしたいんだがな。";
	next;
	cutin "ep13_captin_edq.bmp",255;
	mes "[参謀アビダル]";
	mes "気持ちはわかりますが、";
	mes "私たちの功労を労う為の席です。";
	mes "笑顔は崩さないようにしてくださいね。";
	next;
	mes "[教官長イグリド]";
	mes "兄貴～、";
	mes "服も靴も窮屈で苦しいんだが、";
	mes "俺は客室で寝てちゃダメか？";
	next;
	cutin "ep13_captin_edq.bmp",2;
	mes "[司令官アジフ]";
	mes "諦めろ……";
	mes "ま、どうせ逃げられないなら";
	mes "精一杯楽しむとしよう。";
	close2;
	cutin "ep13_captin_edq.bmp",255;
	end;
}

prt_cas.gat,100,231,3	script	遠征隊参謀アビダル#ep16	755,{
	mes "[参謀アビダル]";
	mes "長い間、二つの種族が警戒しあう";
	mes "緊張の中を過ごしていたので";
	mes "こういった場所に来ると、";
	mes "まるで夢の中に居るようです。";
	mes "これが平和というものなのでしょうか？";
	close;
}

prt_cas.gat,97,229,7	script	教官長イグリド#ep16	751,{
	mes "[教官長イグリド]";
	mes "まったく……";
	mes "本当に俺たちのためだと言うなら";
	mes "ゆっくり休ませるべきだと思わないか？";
	next;
	mes "[教官長イグリド]";
	mes "こんな宴会を喜んでるのは";
	mes "現場を知らない連中だけさ。";
	mes "ま、いつものことだけどな。";
	close;
}

prt_cas.gat,165,245,0	script	調査団員リョースン#ep16	748,{
	emotion 28;
	mes "[リョースン]";
	mes "つ、ついに手に入れた！";
	mes "誰も手を付けていない";
	mes "イチゴのケーキ！";
	next;
	mes "[リョースン]";
	mes "遠征隊のキャンプでは";
	mes "ケーキを死守するために";
	mes "どれほどの妨害工作をしていたか……";
	mes "ああ、涙が出そうだ。";
	next;
	mes "[リョースン]";
	mes "イチゴ！　イチゴ！";
	mes "このイチゴのケーキは";
	mes "私のものです！";
	mes "誰にも渡しません！";
	close;
}

prt_cas.gat,99,247,3	script	祝宴場の貴族#4	573,{
	mes "[祝宴場の貴族]";
	mes "この楽団は実に素晴らしい。";
	mes "私の離宮にも一度招待して";
	mes "パーティーを開いてみよう。";
	close;
}

prt_cas.gat,89,250,5	script	祝宴場客#5	895,{
	mes "[祝宴場客]";
	mes "私は楽団のオリント様の";
	mes "古くからのファンです。";
	mes "この方の演奏を毎度聞くために";
	mes "どれほどの時間とお金をかけたか。";
	next;
	mes "[祝宴場客]";
	mes "この祝宴の招待状も";
	mes "どれだけ苦労して手に入れたのか";
	mes "知っていますか？";
	mes "数量限定だったので、";
	mes "本当に苦労しました！";
	close;
}

prt_cas.gat,89,244,7	script	祝宴場客#6	642,{
	mes "[祝宴場客]";
	mes "この楽団にいる双子の姉妹は";
	mes "性格こそ違うけれど、";
	mes "互いの真似をするのは";
	mes "本当に上手なんだ。";
	next;
	mes "[祝宴場客]";
	mes "二人で一人を演じるときは";
	mes "本当に分身したように";
	mes "錯覚してしまうんだよ。";
	close;
}

prt_cas.gat,152,163,0	script	way_to_qroom_L_qroom_L_	45,1,1,{
OnTouch:
	if(EP16_1QUE < 1) {
		unittalk getnpcid(0,"王室守護騎士#02"),"王室守護騎士 : その先は貴賓が滞在する離宮です。外部の方は出入りできません。",1;
		if(!sleep2(3000)) end;
		unittalk getnpcid(0,"王室守護騎士#02"),"王室守護騎士 : 招待を受けた方は、付き人の案内をお待ちください。",1;
		end;
	}
	warp "prt_cas_q.gat",150,8;
	end;
}


prt_cas.gat,9,23,4	script	歓迎室管理兵#ep16jp	105,{
	mes "[歓迎室管理兵]";
	mes "ご協力感謝いたします、冒険者様。";
	mes "この部屋より出られる場合は";
	mes "わたくしめにお申し付けください。";
	mes "ご案内いたします。";
	next;
	if(select("この場に留まる","「プロンテラの街」へ戻る") == 1) {
		mes "[歓迎室管理兵]";
		mes "承知いたしました。";
		mes "何かありましたら";
		mes "お声をお掛けください！";
		close;
	}
	mes "[歓迎室管理兵]";
	mes "承知いたしました。";
	mes "では「プロンテラの街」へと";
	mes "ご案内いたします。";
	close2;
	warp "prontera.gat",117,72;
	end;
}

prt_cas.gat,15,33,4	script	リハルト家訓練官#ep16jp	47,{
	if(EP16_5QUE < 3) {
		mes "[リハルト家訓練官]";
		mes "我が主「ポー・リハルト」様には";
		mes "もうお会いになられましたか？";
		next;
		mes "[リハルト家訓練官]";
		mes "主は多くの戦闘経験を持つ";
		mes "冒険者を探しておられます。";
		mes "もしご協力いただけるなら";
		mes "リハルト家の部屋を";
		mes "訪ねてください。";
		close;
	}
	if(EP16_5QUE < 4) {
		mes "[リハルト家訓練官]";
		mes "ようこそおいでくださいました。";
		mes "執事より話は承っております。";
		delquest 5403;
		while(1) {
			next;
			mes "[リハルト家訓練官]";
			mes "様々な戦闘データを得るため";
			mes "冒険者様には各地にいる";
			mes "^0000ff強者^000000と戦っていただきます。";
			next;
			mes "[リハルト家訓練官]";
			mes "見事強者を打ち倒し、";
			mes "私共に貴重なデータを";
			mes "提供してくださった暁には";
			mes "^0000ff王家貢献の証^000000を差し上げます。";
			next;
			mes "[リハルト家訓練官]";
			mes "^0000ff証^000000は隣の「^0000ffディラン^000000」にて";
			mes "王家御用達の品との";
			mes "^0000ff引き換え^000000ができますので、";
			mes "ぜひご利用ください。";
			next;
			mes "[リハルト家訓練官]";
			mes "現在リハルト家で調査中の";
			mes "強者は次の通りです。";
			next;
			mes "【討伐対象】";
			mes "== ^32cd32サラの記憶^000000 ==";
			mes "・^0000ff大長老アイリン　1体^000000";
			mes "王家貢献の証　5個";
			mes "　";
			mes "== ^32cd32フェイスワームの巣^000000 ==";
			mes "・^0000ffダークフェイスワーム　2体^000000";
			mes "王家貢献の証　10個";
			mes "・^0000ff女王フェイスワーム　1体^000000";
			mes "王家貢献の証　30個";
			mes "※何れかの属性で達成となります";
			mes "　";
			mes "== ^32cd32ゲフェン魔法大会^000000 ==";
			mes "・^0000ffブルート・ハゼ　1体^000000";
			mes "王家貢献の証　5個";
			mes "・^0000ffフェンリル　1体^000000";
			mes "王家貢献の証　5個";
			mes "　";
			mes "== ^32cd32魔神の塔^000000 ==";
			mes "・^0000ff魔神の巨影　1体^000000";
			mes "王家貢献の証　8個";
			mes "　";
			mes "== ^32cd32フェンリルとサラ^000000 ==";
			mes "・^0000ffサラの幻影　1体^000000";
			mes "王家貢献の証　5個";
			mes "　";
			mes "== ^32cd32飛行船襲撃^000000 ==";
			mes "・^0000ff怒りの船長ペルロック　1体^000000";
			mes "王家貢献の証　10個";
			mes "・^0000ff暴走した船長ペルロック　1体^000000";
			mes "王家貢献の証　20個";
			mes "　";
			mes "== ^32cd32呪いの剣士^000000 ==";
			mes "・^0000ff呪いの根源　1体^000000";
			mes "王家貢献の証　3個";
			mes "　";
			mes "== ^32cd32ビオスの島^000000 ==";
			mes "・^0000ff死神アンク　1体^000000";
			mes "王家貢献の証　5個";
			mes "　";
			mes "== ^32cd32モルスの洞窟^000000 ==";
			mes "・^0000ffモルス・ネクロマンサー　1体^000000";
			mes "王家貢献の証　5個";
			mes "　";
			mes "== ^32cd32魔神殿^000000 ==";
			mes "・^0000ffブリナラネア　1体^000000";
			mes "王家貢献の証　10個";
			mes "・^0000ffムスペルスコール　1体^000000";
			mes "王家貢献の証　10個";
			mes "・^0000ff絶望の神モロク　1体^000000";
			mes "王家貢献の証　20個";
			mes "　";
			mes "== ^32cd32侵攻されたプロンテラ^000000 ==";
			mes "・^0000ff不死の軍団兵士長　500体^000000";
			mes "王家貢献の証　5個";
			mes "・^0000ff不死の軍団兵士長　1000体^000000";
			mes "王家貢献の証　5個";
			mes "※各500匹討伐と同時に進行可能です";
			mes "　";
			mes "== ^32cd32プロンテラ地下監獄^000000 ==";
			mes "・^0000ffフローズンウルフ、タフィー　各50体^000000";
			mes "王家貢献の証　30個";
			mes "・^0000ffフローズンウルフ、タフィー　各100体^000000";
			mes "王家貢献の証　30個";
			mes "※各50匹討伐と同時に進行可能です";
			next;
			mes "[リハルト家訓練官]";
			mes "協力していただく際の注意点ですが、";
			mes "リハルト家の家訓として";
			mes "訓練後には十分な休息を";
			mes "しっかり取る事としています。";
			next;
			mes "^FF0000[INFORMATION]";
			mes "^FF0000討伐クエストは報告後、";
			mes "^FF0000一定時間は次の報告ができません。";
			mes "^FF0000また、クエストの受注は";
			mes "^FF0000報告時に自動的に行われます。^000000";
			next;
			mes "[リハルト家訓練官]";
			mes "説明は以上です。";
			mes "よろしいですか？";
			next;
			if(select("いいえ","はい") == 1) {
				mes "[リハルト家訓練官]";
				mes "それではもう一度";
				mes "ご説明いたします。";
				continue;
			}
			break;
		}
		for('@qid=97600; '@qid <= 97622; '@qid++) {
			setquest '@qid;
		}
		//setquest 73126;
		//compquest 73126;
		set EP16_5QUE,4;
		mes "[リハルト家訓練官]";
		mes "それではご武運を。";
		mes "お帰りをお待ちしています。";
		close;
	}
	mes "[リハルト家訓練官]";
	mes "お帰りなさいませ、";
	mes strcharinfo(0)+ "様。";
	mes "本日はどうされましたか？";
	next;
	switch(select("訓練の報告をする","訓練の説明","討伐状況の確認","訓練の受注","訓練の取消","やめる")) {
	case 1:
		setarray '@reward,5,10,30,30,30,30,30,5,5,8,5,10,20,3,5,5,10,10,20,5,5,30,30;
		setarray '@timeque,73100,73101,73102,73102,73102,73102,73102,73107,73108,73109,73110,73111,73112,73113,73114,73115,73116,73117,73118,73119,73120,73121,73122;
		set '@amount,0;
		for('@i=0; '@i <= getarraysize('@reward); '@i++) {
			if(checkquest('@timeque['@i]) & 0x2) {
				delquest '@timeque['@i];
			}
			if(checkquest('@timeque['@i]))
				continue;
			set '@quest_id,97600+'@i;
			if(checkquest('@quest_id) & 0x4) {
				delquest '@quest_id;
				setquest '@timeque['@i];
				setquest '@quest_id;
				set '@amount,'@amount+'@reward['@i];
			}
		}
		if('@amount > 0) {
			getitem 6919,'@amount;
			mes "[リハルト家訓練官]";
			mes "貴重な戦闘データを";
			mes "ありがとうございます。";
			mes "ポー様も大層お喜びになるでしょう。";
			close;
		}
		mes "[リハルト家訓練官]";
		mes "おや……？";
		mes "報告可能な課題がないようです。";
		mes "もう一度ご確認ください。";
		close;
	case 2:
		mes "[リハルト家訓練官]";
		mes "様々な戦闘データを得るため";
		mes "冒険者様には各地にいる";
		mes "^0000ff強者^000000と戦っていただきます。";
		next;
		mes "[リハルト家訓練官]";
		mes "見事強者を打ち倒し、";
		mes "私共に貴重なデータを";
		mes "提供してくださった暁には";
		mes "^0000ff王家貢献の証^000000を差し上げます。";
		next;
		mes "[リハルト家訓練官]";
		mes "^0000ff証^000000は隣の「^0000ffディラン^000000」にて";
		mes "王家御用達の品との";
		mes "^0000ff引き換え^000000ができますので、";
		mes "ぜひご利用ください。";
		next;
		mes "[リハルト家訓練官]";
		mes "現在リハルト家で調査中の";
		mes "強者は次の通りです。";
		next;
		mes "【討伐対象】";
		mes "== ^32cd32サラの記憶^000000 ==";
		mes "・^0000ff大長老アイリン　1体^000000";
		mes "王家貢献の証　5個";
		mes "　";
		mes "== ^32cd32フェイスワームの巣^000000 ==";
		mes "・^0000ffダークフェイスワーム　2体^000000";
		mes "王家貢献の証　10個";
		mes "・^0000ff女王フェイスワーム　1体^000000";
		mes "王家貢献の証　30個";
		mes "※何れかの属性で達成となります";
		mes "　";
		mes "== ^32cd32ゲフェン魔法大会^000000 ==";
		mes "・^0000ffブルート・ハゼ　1体^000000";
		mes "王家貢献の証　5個";
		mes "・^0000ffフェンリル　1体^000000";
		mes "王家貢献の証　5個";
		mes "　";
		mes "== ^32cd32魔神の塔^000000 ==";
		mes "・^0000ff魔神の巨影　1体^000000";
		mes "王家貢献の証　8個";
		mes "　";
		mes "== ^32cd32フェンリルとサラ^000000 ==";
		mes "・^0000ffサラの幻影　1体^000000";
		mes "王家貢献の証　5個";
		mes "　";
		mes "== ^32cd32飛行船襲撃^000000 ==";
		mes "・^0000ff怒りの船長ペルロック　1体^000000";
		mes "王家貢献の証　10個";
		mes "・^0000ff暴走した船長ペルロック　1体^000000";
		mes "王家貢献の証　20個";
		mes "　";
		mes "== ^32cd32呪いの剣士^000000 ==";
		mes "・^0000ff呪いの根源　1体^000000";
		mes "王家貢献の証　3個";
		mes "　";
		mes "== ^32cd32ビオスの島^000000 ==";
		mes "・^0000ff死神アンク　1体^000000";
		mes "王家貢献の証　5個";
		mes "　";
		mes "== ^32cd32モルスの洞窟^000000 ==";
		mes "・^0000ffモルス・ネクロマンサー　1体^000000";
		mes "王家貢献の証　5個";
		mes "　";
		mes "== ^32cd32魔神殿^000000 ==";
		mes "・^0000ffブリナラネア　1体^000000";
		mes "王家貢献の証　10個";
		mes "・^0000ffムスペルスコール　1体^000000";
		mes "王家貢献の証　10個";
		mes "・^0000ff絶望の神モロク　1体^000000";
		mes "王家貢献の証　20個";
		mes "　";
		mes "== ^32cd32侵攻されたプロンテラ^000000 ==";
		mes "・^0000ff不死の軍団兵士長　500体^000000";
		mes "王家貢献の証　5個";
		mes "・^0000ff不死の軍団兵士長　1000体^000000";
		mes "王家貢献の証　5個";
		mes "※各500匹討伐と同時に進行可能です";
		mes "　";
		mes "== ^32cd32プロンテラ地下監獄^000000 ==";
		mes "・^0000ffフローズンウルフ、タフィー　各50体^000000";
		mes "王家貢献の証　30個";
		mes "・^0000ffフローズンウルフ、タフィー　各100体^000000";
		mes "王家貢献の証　30個";
		mes "※各50匹討伐と同時に進行可能です";
		next;
		mes "[リハルト家訓練官]";
		mes "協力していただく際の注意点ですが、";
		mes "リハルト家の家訓として";
		mes "訓練後には十分な休息を";
		mes "しっかり取る事としています。";
		next;
		mes "^FF0000[INFORMATION]";
		mes "^FF0000討伐クエストは報告後、";
		mes "^FF0000一定時間は次の報告ができません。";
		mes "^FF0000また、クエストの受注は";
		mes "^FF0000報告時に自動的に行われます。^000000";
		next;
		mes "[リハルト家訓練官]";
		mes "説明は以上です。";
		close;
	case 3:
		for('@qid=0; '@qid <= 22; '@qid++) {
			if(checkquest(73100+'@qid) && !(checkquest(73100+'@qid) & 0x2))
				set '@data$['@qid],"^888888報告クールタイム中^000000";
			else if(checkquest(97600+'@qid) & 0x4)
				set '@data$['@qid],"^ff0000討伐済み^000000";
			else if(checkquest(97600+'@qid))
				set '@data$['@qid],"^0000ff挑戦中^000000";
			else
				set '@data$['@qid],"^888888未受注^000000";
		}
		mes "[リハルト家訓練官]";
		mes strcharinfo(0)+ "様の";
		mes "達成状況は次の通りです。";
		next;
		mes "【^ff0000討伐対象^000000】";
		mes "== ^32cd32サラの記憶^000000 ==";
		mes "・^0000ff大長老アイリン^000000";
		mes '@data$[0];
		mes "　";
		mes "== ^32cd32フェイスワームの巣^000000 ==";
		mes "・^0000ffダークフェイスワーム^000000";
		mes '@data$[1];
		mes "・^0000ff女王フェイスワーム^000000";
		mes '@data$[2];
		mes "　";
		mes "== ^32cd32ゲフェン魔法大会^000000 ==";
		mes "・^0000ffブルート・ハゼ^000000";
		mes '@data$[7];
		mes "・^0000ffフェンリル^000000";
		mes '@data$[8];
		mes "　";
		mes "== ^32cd32魔神の塔^000000 ==";
		mes "・^0000ff魔神の巨影^000000";
		mes '@data$[9];
		mes "　";
		mes "== ^32cd32フェンリルとサラ^000000 ==";
		mes "・^0000ffサラの幻影^000000";
		mes '@data$[10];
		mes "　";
		mes "== ^32cd32飛行船襲撃^000000 ==";
		mes "・^0000ff怒りの船長ペルロック^000000";
		mes '@data$[11];
		mes "・^0000ff暴走した船長ペルロック^000000";
		mes '@data$[12];
		mes "　";
		mes "== ^32cd32呪いの剣士^000000 ==";
		mes "・^0000ff呪いの根源^000000";
		mes '@data$[13];
		mes "　";
		mes "== ^32cd32ビオスの島^000000 ==";
		mes "・^0000ff死神アンク^000000";
		mes '@data$[14];
		mes "　";
		mes "== ^32cd32モルスの洞窟^000000 ==";
		mes "・^0000ffモルス・ネクロマンサー^000000";
		mes '@data$[15];
		mes "　";
		mes "== ^32cd32魔神殿^000000 ==";
		mes "・^0000ffブリナラネア^000000";
		mes '@data$[16];
		mes "・^0000ffムスペルスコール^000000";
		mes '@data$[17];
		mes "・^0000ff絶望の神モロク^000000";
		mes '@data$[18];
		mes "　";
		mes "== ^32cd32侵攻されたプロンテラ^000000 ==";
		mes "・^0000ff不死の軍団兵士長^000000";
		mes "　（各500匹討伐）";
		mes '@data$[19];
		mes "・^0000ff不死の軍団兵士長^000000";
		mes "　（各1000匹討伐）";
		mes '@data$[20];
		mes "　";
		mes "== ^32cd32プロンテラ地下監獄^000000 ==";
		mes "・^0000ffフローズンウルフ、タフィー^000000";
		mes "　（各50匹討伐）";
		mes '@data$[21];
		mes "・^0000ffフローズンウルフ、タフィー^000000";
		mes "　（各100匹討伐）";
		mes '@data$[22];
		close;
	case 4:
		for('@qid=97600; '@qid <= 97622; '@qid++) {
			if(!checkquest('@qid))
				break;
			if('@qid == 97622) {
				mes "[リハルト家訓練官]";
				mes strcharinfo(0)+ "様は既に";
				mes "全ての訓練を受注しております。";
				next;
				mes "[リハルト家訓練官]";
				mes "^ff0000ご報告いただいた訓練は^000000";
				mes "^ff0000私の方で報告と同時に受注の手続きを^000000";
				mes "^ff0000取らせていただきます。^000000";
				mes "そのため、受注の手続きは不要です。";
				next;
				mes "[リハルト家訓練官]";
				mes "「^0000ff訓練の受注^000000」は";
				mes "取り消した訓練を";
				mes "再度受注される際にご利用ください。";
				close;
			}
		}
		mes "[リハルト家訓練官]";
		mes "どの訓練を受注されますか？";
		next;
		setarray '@menu$,"全ての討伐クエストを受注する",
						(!checkquest(97600)? "^0000ff":"^888888")+ "大長老アイリン^000000",
						(!checkquest(97601)? "^0000ff":"^888888")+ "ダークフェイスワーム^000000",
						(!checkquest(97602)? "^0000ff":"^888888")+ "女王フェイスワーム^000000",
						(!checkquest(97607)? "^0000ff":"^888888")+ "ブルート・ハゼ^000000",
						(!checkquest(97608)? "^0000ff":"^888888")+ "フェンリル^000000",
						(!checkquest(97609)? "^0000ff":"^888888")+ "魔神の巨影^000000",
						(!checkquest(97610)? "^0000ff":"^888888")+ "サラの幻影^000000",
						(!checkquest(97611)? "^0000ff":"^888888")+ "怒りの船長ペルロック^000000",
						(!checkquest(97612)? "^0000ff":"^888888")+ "暴走した船長ペルロック^000000",
						(!checkquest(97613)? "^0000ff":"^888888")+ "呪いの根源^000000",
						(!checkquest(97614)? "^0000ff":"^888888")+ "死神アンク^000000",
						(!checkquest(97615)? "^0000ff":"^888888")+ "モルス・ネクロマンサー^000000",
						(!checkquest(97616)? "^0000ff":"^888888")+ "ブリナラネア^000000",
						(!checkquest(97617)? "^0000ff":"^888888")+ "ムスペルスコール^000000",
						(!checkquest(97618)? "^0000ff":"^888888")+ "絶望の神モロク^000000",
						(!checkquest(97619)? "^0000ff":"^888888")+ "不死の軍団兵士長(500体)^000000",
						(!checkquest(97620)? "^0000ff":"^888888")+ "不死の軍団兵士長(1000体)^000000",
						(!checkquest(97621)? "^0000ff":"^888888")+ "フローズンウルフ、タフィー(各50体)^000000",
						(!checkquest(97622)? "^0000ff":"^888888")+ "フローズンウルフ、タフィー(各100体)^000000",
						"やめる";
		set '@i,select(printarray('@menu$))-2;
		if('@i == -1) {	// 全ての討伐クエストを受注する
			for('@qid=97600; '@qid <= 97622; '@qid++) {
				if(!checkquest('@qid))
					setquest '@qid;
			}
			mes "[リハルト家訓練官]";
			mes "訓練の受注が";
			mes "完了いたしました。";
			close;
		}
		if('@i == getarraysize('@menu$) - 2) {
			mes "[リハルト家訓練官]";
			mes "そうですか。";
			mes "気が変わったらまた来てください。";
			close;
		}
		set '@qid,97600+'@i;
		if('@qid > 97602)
			set '@qid,'@qid+5;
		if(checkquest('@qid)) {
			mes "[リハルト家訓練官]";
			mes "その訓練は既に";
			mes "受注なさっています。";
			close;
		}
		if('@qid == 97602) {
			setquest 97602;
			setquest 97603;
			setquest 97604;
			setquest 97605;
			setquest 97606;
		} else {
			setquest '@qid;
		}
		mes "[リハルト家訓練官]";
		mes "訓練の受注が";
		mes "完了いたしました。";
		close;
	case 5:
		mes "[リハルト家訓練官]";
		mes "どの訓練を取消しますか？";
		next;
		setarray '@menu$,"全ての討伐クエストを取り消す",
						(checkquest(97600)? "^0000ff":"^888888")+ "大長老アイリン^000000",
						(checkquest(97601)? "^0000ff":"^888888")+ "ダークフェイスワーム^000000",
						(checkquest(97602)? "^0000ff":"^888888")+ "女王フェイスワーム^000000",
						(checkquest(97607)? "^0000ff":"^888888")+ "ブルート・ハゼ^000000",
						(checkquest(97608)? "^0000ff":"^888888")+ "フェンリル^000000",
						(checkquest(97609)? "^0000ff":"^888888")+ "魔神の巨影^000000",
						(checkquest(97610)? "^0000ff":"^888888")+ "サラの幻影^000000",
						(checkquest(97611)? "^0000ff":"^888888")+ "怒りの船長ペルロック^000000",
						(checkquest(97612)? "^0000ff":"^888888")+ "暴走した船長ペルロック^000000",
						(checkquest(97613)? "^0000ff":"^888888")+ "呪いの根源^000000",
						(checkquest(97614)? "^0000ff":"^888888")+ "死神アンク^000000",
						(checkquest(97615)? "^0000ff":"^888888")+ "モルス・ネクロマンサー^000000",
						(checkquest(97616)? "^0000ff":"^888888")+ "ブリナラネア^000000",
						(checkquest(97617)? "^0000ff":"^888888")+ "ムスペルスコール^000000",
						(checkquest(97618)? "^0000ff":"^888888")+ "絶望の神モロク^000000",
						(checkquest(97619)? "^0000ff":"^888888")+ "不死の軍団兵士長(500体)^000000",
						(checkquest(97620)? "^0000ff":"^888888")+ "不死の軍団兵士長(1000体)^000000",
						(checkquest(97621)? "^0000ff":"^888888")+ "フローズンウルフ、タフィー(各50体)^000000",
						(checkquest(97622)? "^0000ff":"^888888")+ "フローズンウルフ、タフィー(各100体)^000000",
						"やめる";
		set '@i,select(printarray('@menu$))-2;
		if(select("いいえ","はい") == 1) {
			mes "[リハルト家訓練官]";
			mes "そうですか。";
			mes "気が変わったらまた来てください。";
			close;
		}
		if('@i == -1) {	// 全ての討伐クエストを取り消す
			for('@qid=0; '@qid <= 22; '@qid++) delquest 97600+'@qid;
			mes "[リハルト家訓練官]";
			mes "訓練の取消しが";
			mes "完了いたしました。";
			close;
		}
		if('@i == getarraysize('@menu$) - 2) {
			mes "[リハルト家訓練官]";
			mes "そうですか。";
			mes "気が変わったらまた来てください。";
			close;
		}
		set '@qid,97600+'@i;
		if('@qid > 97602)
			set '@qid,'@qid+5;
		if(!checkquest('@qid)) {
			mes "[リハルト家訓練官]";
			mes "その訓練は";
			mes "受注しておりません。";
			close;
		}
		if('@qid == 97602) {
			delquest 97602;
			delquest 97603;
			delquest 97604;
			delquest 97605;
			delquest 97606;
		} else {
			delquest '@qid;
		}
		mes "[リハルト家訓練官]";
		mes "訓練の取消しが";
		mes "完了いたしました。";
		close;
	case 6:
		mes "[リハルト家訓練官]";
		mes "そうですか。";
		mes "気が変わったらまた来てください。";
		close;
	}
}

//============================================================
// ニーヴエンチャントNPC
//------------------------------------------------------------
prt_cas.gat,18,33,4	script	ディラン#ep16jp	734,{
	mes "[ディラン]";
	mes "ようこそお越しくださいました、";
	mes strcharinfo(0)+ "様。";
	mes "本日はどのようなご用件ですか？";
	next;
	switch(select("ニーヴエンチャント","エンチャントについて","王家貢献の証で交換","証の交換ラインナップを見る","立ち去る")) {
	case 1:
		mes "[ディラン]";
		mes "ニーヴエンチャントは";
		mes "[^0000ff金剛石の盾[0]^000000]";
		mes "[^0000ff栄光の証[0]^000000]、";
		mes "[^0000ff城下町の地図[0]^000000]、";
		mes "[^0000ff輝く聖水[0]^000000]、";
		mes "[^0000ff金剛石の靴[1]^000000]、";
		mes "[^0000ff帯状の暗器[0]^000000]、";
		mes "[^0000ff狙撃手の手袋[0]^000000]、";
		mes "[^0000ffニーヴクレイモア[1]^000000]、";
		mes "[^0000ffニーヴグレイヴ[1]^000000]、";
		mes "[^0000ffニーヴジャマダハル[1]^000000]、";
		mes "[^0000ffニーヴシーフボウ[1]^000000]、";
		mes "[^0000ffニーヴハンターボウ[1]^000000]、";
		mes "[^0000ffニーヴクロスボウ[1]^000000]、";
		mes "[^0000ffニーヴウィザードスタッフ[1]^000000]、";
		mes "[^0000ffニーヴアークワンド[1]^000000]、";
		mes "[^0000ffニーヴホーリーステッキ[1]^000000]、";
		mes "[^0000ffニーヴディバインクロス[1]^000000]、";
		mes "[^0000ffニーヴギロチン[1]^000000]、";
		mes "[^0000ffニーヴバスター[1]^000000]、";
		mes "[^0000ffニーヴ風魔手裏剣[1]^000000]、";
		mes "[^0000ffニーヴライフル[1]^000000]、";
		mes "[^0000ff金剛石のマント[1]^000000]に";
		mes "利用が可能です。";
		next;
		set '@i,select(
			(getequipid(3))? getequipname(3): "左手-装備していない",
			(getequipid(4))? getequipname(4): "右手-装備していない",
			(getequipid(5))? getequipname(5): "肩にかける物-装備していない",
			(getequipid(6))? getequipname(6): "靴-装備していない",
			(getequipid(7))? getequipname(7): "アクセサリー[1]-装備していない",
			(getequipid(8))? getequipname(8): "アクセサリー[2]-装備していない"
				)+2;
		if(getequipisequiped('@i)==0) {
			mes "[ディラン]";
			mes "エンチャントを行う場合は、";
			mes "対象のアイテムを";
			mes "装備しておいてください。";
			mes "お手数をおかけしますが、";
			mes "よろしくお願いします。";
			close;
		}
		switch(getequipid('@i)) {
		case 28920:		// 金剛石の盾[0]
			set '@type,0;
			break;
		case 28497:		// 城下町の地図[0]
		case 28498:		// 輝く聖水[0]
		case 28499:		// 栄光の証[0]
		case 28524:		// 帯状の暗器[0]
		case 28525:		// 狙撃手の手袋[0]
			set '@type,1;
			break;
		case 21031:		// ニーヴクレイモア[1]
		case 36008:		// ニーヴグレイヴ[1]
		case 38026:		// ニーヴジャマダハル[1]
		case 18153:		// ニーヴシーフボウ[1]
		case 18154:		// ニーヴハンターボウ[1]
		case 18155:		// ニーヴクロスボウ[1]
		case 2042:		// ニーヴウィザードスタッフ[1]
		case 2043:		// ニーヴアークワンド[1]
		case 2044:		// ニーヴホーリーステッキ[1]
		case 2045:		// ニーヴディバインクロス[1]
		case 38121:		// ニーヴギロチン[1]
		case 38122:		// ニーヴバスター[1]
		case 13339:		// ニーヴ風魔手裏剣[1]
		case 28235:		// ニーヴライフル[1]
			set '@type,2;
			break;
		case 20942:		// 金剛石のマント[1]
		case 22142:		// 金剛石の靴[1]
			set '@type,3;
			break;
		default:
			mes "[ディラン]";
			mes "エンチャントを行う場合は、";
			mes "対象のアイテムを";
			mes "装備しておいてください。";
			mes "ニーヴは繊細なので、";
			mes "他の物にはエンチャントが";
			mes "できません……。";
			close;
		}
		set '@card[1],getequipcardid('@i,1);
		set '@card[2],getequipcardid('@i,2);
		set '@card[3],getequipcardid('@i,3);
		if('@card[3] == 0)
			set '@pos,3;
		else if('@card[2] == 0)
			set '@pos,2;
		else if('@card[1] == 0)
			set '@pos,1;
		else {
			mes "[ディラン]";
			mes "既に限界まで";
			mes "強化されているようですね。";
			mes "申し訳ありませんが、";
			mes "ニーヴエンチャントは";
			mes "^0000ff最大三つ^000000までしかできません。";
			close;
		}
		mes "[ディラン]";
		mes "エンチャントするニーヴの種類を";
		mes "お選びください。";
		next;
		setarray '@menu$,"安息のニーヴ","永劫のニーヴ","傷のニーヴ","血のニーヴ","名誉のニーヴ","死のニーヴ","やめる";
		for('@j=1; '@j <= 3; '@j++) {
			if('@card['@j] >= 29249 && '@card['@j] <= 29252) {
				set '@menu$[0],"^888888【エンチャント済】"+'@menu$[0]+"^000000";
				set '@flag[0],1;
			}
			if('@card['@j] >= 29253 && '@card['@j] <= 29259) {
				set '@menu$[1],"^888888【エンチャント済】"+'@menu$[1]+"^000000";
				set '@flag[1],1;
			}
			if('@card['@j] >= 29260 && '@card['@j] <= 29269 || '@card['@j] == 29510) {
				set '@menu$[2],"^888888【エンチャント済】"+'@menu$[2]+"^000000";
				set '@flag[2],1;
			}
			if('@card['@j] >= 29270 && '@card['@j] <= 29275) {
				set '@menu$[3],"^888888【エンチャント済】"+'@menu$[3]+"^000000";
				set '@flag[3],1;
			}
			if('@card['@j] >= 29276 && '@card['@j] <= 29278 || '@card['@j] >= 29382 && '@card['@j] <= 29384) {
				set '@menu$[4],"^888888【エンチャント済】"+'@menu$[4]+"^000000";
				set '@flag[4],1;
			}
			if('@card['@j] >= 29279 && '@card['@j] <= 29282 || '@card['@j] >= 29385 && '@card['@j] <= 29386) {
				set '@menu$[5],"^888888【エンチャント済】"+'@menu$[5]+"^000000";
				set '@flag[5],1;
			}
		}
		switch('@type) {
		case 1:		// アクセサリー
			set '@menu$[1],"";
			set '@menu$[2],"";
			break;
		case 2:		// 武器
			set '@menu$[5],"";
			break;
		case 3:		// 肩にかけるもの・靴
			set '@menu$[2],"";
			break;
		}
		set '@j,select(printarray('@menu$)) - 1;
		if('@flag['@j] > 0) {
			mes "[ディラン]";
			mes "同じ種類のエンチャントは";
			mes "行う事が出来ません。";
			close;
		}
		if('@j > 5) {
			mes "[ディラン]";
			mes "ご利用ありがとうございました。";
			mes "またのお越しを";
			mes "お待ちしております。";
			close;
		}
		mes "[ディラン]";
		mes "どのニーヴを";
		mes "エンチャントいたしますか？";
		next;
		switch('@j) {
		case 0:		// 安息のニーヴ
			setarray '@gain,29249,29250,29251,29252;
			set '@n,select("安息のニーヴ(体力) -> 100","安息のニーヴ(精神) -> 100","安息のニーヴ(生命) -> 100","安息のニーヴ(知力) -> 100","やめる") - 1;
			if('@n >= getarraysize('@gain)) {
				mes "[ディラン]";
				mes "わかりました。";
				mes "必要になったらまた来てください。";
				close;
			}
			set '@nameid,'@gain['@n];
			set '@amount,100;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "エンチャントするニーヴは";
			mes "^0000ff"+ getitemname('@nameid) +"^000000で";
			mes "よろしいですか？";
			break;
		case 1:		// 永劫のニーヴ
			setarray '@gain,29253,29254,29255,29256,29257,29258,29259;
			set '@n,select("永劫のニーヴ(火) -> 100","永劫のニーヴ(水) -> 100","永劫のニーヴ(風) -> 100","永劫のニーヴ(地) -> 100","永劫のニーヴ(闇) -> 100","永劫のニーヴ(念) -> 100","永劫のニーヴ(毒) -> 100","やめる") - 1;
			if('@n >= getarraysize('@gain)) {
				mes "[ディラン]";
				mes "わかりました。";
				mes "必要になったらまた来てください。";
				close;
			}
			set '@nameid,'@gain['@n];
			set '@amount,100;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "エンチャントするニーヴは";
			mes "^0000ff"+ getitemname('@nameid) +"^000000で";
			mes "よろしいですか？";
			break;
		case 2:		// 傷のニーヴ
			setarray '@gain,29260,29261,29262,29263,29264,29265,29266,29267,29268,29269,29510;
			set '@n,select("傷のニーヴ(無形) -> 100","傷のニーヴ(不死形) -> 100","傷のニーヴ(動物形) -> 100","傷のニーヴ(植物形) -> 100","傷のニーヴ(昆虫形) -> 100","傷のニーヴ(魚貝形) -> 100","傷のニーヴ(悪魔形) -> 100","傷のニーヴ(人間形) -> 250","傷のニーヴ(天使形) -> 100","傷のニーヴ(竜形) -> 100","傷のニーヴ(プレイヤー) -> 250","やめる") - 1;
			if('@n >= getarraysize('@gain)) {
				mes "[ディラン]";
				mes "わかりました。";
				mes "必要になったらまた来てください。";
				close;
			}
			set '@nameid,'@gain['@n];
			if('@nameid == 29267 || '@nameid == 29510)
				set '@amount,250;
			else
				set '@amount,100;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "エンチャントするニーヴは";
			mes "^0000ff"+ getitemname('@nameid) +"^000000で";
			mes "よろしいですか？";
			break;
		case 3:		// 血のニーヴ
			setarray '@gain,29270,29271,29272,29273,29274,29275;
			set '@n,select("血のニーヴ(腕力) -> 100","血のニーヴ(迅速) -> 100","血のニーヴ(体力) -> 100","血のニーヴ(知力) -> 100","血のニーヴ(集中) -> 100","血のニーヴ(幸運) -> 100","やめる") - 1;
			if('@n >= getarraysize('@gain)) {
				mes "[ディラン]";
				mes "わかりました。";
				mes "必要になったらまた来てください。";
				close;
			}
			set '@nameid,'@gain['@n];
			set '@amount,100;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "エンチャントするニーヴは";
			mes "^0000ff"+ getitemname('@nameid) +"^000000で";
			mes "よろしいですか？";
			break;
		case 4:		// 名誉のニーヴ
			setarray '@gain,29276,29277,29278;
			set '@n,select("名誉のニーヴ(迅速) -> 300","名誉のニーヴ(集中) -> 300","名誉のニーヴ(熟練) -> 300","やめる") - 1;
			if('@n >= getarraysize('@gain)) {
				mes "[ディラン]";
				mes "わかりました。";
				mes "必要になったらまた来てください。";
				close;
			}
			set '@nameid,'@gain['@n];
			set '@amount,300;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "エンチャントするニーヴは";
			mes "^0000ff"+ getitemname('@nameid) +"^000000で";
			mes "よろしいですか？";
			break;
		case 5:		// 死のニーヴ
			setarray '@gain,29279,29280,29281,29282;
			set '@n,select("死のニーヴ(腕力) -> 200","死のニーヴ(知力) -> 200","死のニーヴ(体力) -> 200","死のニーヴ(魔防) -> 200","やめる") - 1;
			if('@n >= getarraysize('@gain)) {
				mes "[ディラン]";
				mes "わかりました。";
				mes "必要になったらまた来てください。";
				close;
			}
			set '@nameid,'@gain['@n];
			set '@amount,200;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "エンチャントするニーヴは";
			mes "^0000ff"+ getitemname('@nameid) +"^000000で";
			mes "よろしいですか？";
			break;
		default:
			mes "[ディラン]";
			mes "わかりました。";
			mes "必要になったらまた来てください。";
			close;
		}
		next;
		if(select("いいえ","はい") == 1) {
			mes "[ディラン]";
			mes "ご利用ありがとうございました。";
			mes "またのお越しを";
			mes "お待ちしております。";
			close;
		}
		delitem 6919,'@amount;
		setequipcardid '@i,'@pos,'@nameid,0x6;
		misceffect 182,"";
		misceffect 548,"";
		misceffect 338,"";
		emotion 15;
		mes "[ディラン]";
		mes "ご利用ありがとうございました。";
		mes "またのお越しを";
		mes "お待ちしております。";
		close;
	case 2:
		mes "[ディラン]";
		mes "ニーヴエンチャントは";
		mes "[^0000ff金剛石の盾[0]^000000]";
		mes "[^0000ff栄光の証[0]^000000]、";
		mes "[^0000ff城下町の地図[0]^000000]、";
		mes "[^0000ff輝く聖水[0]^000000]、";
		mes "[^0000ff金剛石の靴[1]^000000]、";
		mes "[^0000ff帯状の暗器[0]^000000]、";
		mes "[^0000ff狙撃手の手袋[0]^000000]、";
		mes "[^0000ffニーヴクレイモア[1]^000000]、";
		mes "[^0000ffニーヴグレイヴ[1]^000000]、";
		mes "[^0000ffニーヴジャマダハル[1]^000000]、";
		mes "[^0000ffニーヴシーフボウ[1]^000000]、";
		mes "[^0000ffニーヴハンターボウ[1]^000000]、";
		mes "[^0000ffニーヴクロスボウ[1]^000000]、";
		mes "[^0000ffニーヴウィザードスタッフ[1]^000000]、";
		mes "[^0000ffニーヴアークワンド[1]^000000]、";
		mes "[^0000ffニーヴホーリーステッキ[1]^000000]、";
		mes "[^0000ffニーヴディバインクロス[1]^000000]、";
		mes "[^0000ffニーヴギロチン[1]^000000]、";
		mes "[^0000ffニーヴバスター[1]^000000]、";
		mes "[^0000ffニーヴ風魔手裏剣[1]^000000]、";
		mes "[^0000ffニーヴライフル[1]^000000]、";
		mes "[^0000ff金剛石のマント[1]^000000]に";
		mes "エンチャントが可能です。";
		next;
		mes "[ディラン]";
		mes "また、エンチャントの際には";
		mes "ニーヴの種類に応じて、";
		mes "^0000ff王家貢献の証^000000が必要になります。";
		next;
		while(1) {
			switch(select("エンチャントの注意事項","エンチャントの種類","立ち去る")) {
			case 1:
				mes "[ディラン]";
				mes "エンチャントの注意事項について";
				mes "お伝えいたします。";
				next;
				mes "[ディラン]";
				mes "エンチャントを行うと";
				mes "装備の精錬値は^ff0000リセット^000000されます。";
				mes "精錬をする際は";
				mes "全てのエンチャントを済ませた状態で";
				mes "行う事をおすすめします。";
				next;
				mes "[ディラン]";
				mes "エンチャントするアイテムに";
				mes "ランダムオプションが";
				mes "付与されていた場合、";
				mes "^ff0000その効果は引き継がれる^000000ので";
				mes "ご安心ください。";
				next;
				mes "[ディラン]";
				mes "エンチャントは希望するアイテムを";
				mes "^ff0000装備した状態^000000でおこなってください。";
				next;
				mes "[ディラン]";
				mes "エンチャントは^ff0000100%成功します^000000。";
				mes "ただし、一度行ったエンチャントの";
				mes "^ff0000リセットは出来ません。^000000";
				next;
				mes "[ディラン]";
				mes "全てのエンチャントは";
				mes "^ff0000ダークハンド[1]と";
				mes "^ff0000共に装備する^000000事で";
				mes "力が増幅され、";
				mes "隠された能力が発動します。";
				next;
				mes "[ディラン]";
				mes "ただし、^0000ff同じ種類のエンチャントを";
				mes "^0000ff複数個付与したとしても";
				mes "^0000ffセット効果は1個分しか発動しません^000000。";
				mes "例えば、同じニーヴを盾に1つ、";
				mes "アクセサリーに1つ付与しても";
				mes "発動するセット効果は1回分のみです。";
				next;
				mes "[ディラン]";
				mes "最後に、1つのアイテムに";
				mes "ニーヴは最大3つまで";
				mes "付与できますが、";
				mes "同じ系列のニーヴは2つ以上";
				mes "エンチャントすることができません。";
				next;
				mes "[ディラン]";
				mes "例えば、死のニーヴ(腕力)を";
				mes "付与した場合、";
				mes "他の死のニーヴは付与できません。";
				next;
				continue;
			case 2:
				mes "[ディラン]";
				mes "ニーヴは大きく分けて";
				mes "以下、6つのタイプがあります。";
				next;
				mes "[ディラン]";
				mes "安息のニーヴ";
				mes "永劫のニーヴ";
				mes "傷のニーヴ";
				mes "血のニーヴ";
				mes "名誉のニーヴ";
				mes "死のニーヴ";
				next;
				mes "[ディラン]";
				mes "これらは全てエンチャント可能な部位と";
				mes "エンチャント可能な回数が";
				mes "決められています。";
				mes "どれについて確認しますか？";
				mes "‐^ff0000一部、確認に";
				mes "　^ff0000画面のスクロールが必要です^000000‐";
				next;
				while(1) {
					switch(select("安息のニーヴ　…　HPとSPの増強","永劫のニーヴ　…　属性耐性の増加","傷のニーヴ　…　種族耐性の増加","血のニーヴ　…　ステータスの上昇","名誉のニーヴ　…　命中と回避と動作速度の上昇","死のニーヴ　…　攻撃と防御の上昇","立ち去る")) {
					case 1:
						switch(select("安息のニーヴ(体力) -> 100","安息のニーヴ(精神) -> 100","安息のニーヴ(生命) -> 100","安息のニーヴ(知力) -> 100","戻る")) {
						case 1:
							mes "[安息のニーヴ(体力)]";
							mes "MaxHP + 200";
							mes "―――――――――――――";
							mes "精錬値が6以上の時、追加で";
							mes "MaxHP + 300";
							mes "―――――――――――――";
							mes "精錬値が8以上の時、追加で";
							mes "MaxHP + 500";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "MaxHP + 5000";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 2:
							mes "[安息のニーヴ(精神)]";
							mes "MaxSP + 10";
							mes "―――――――――――――";
							mes "精錬値が6以上の時、追加で";
							mes "MaxSP + 20";
							mes "―――――――――――――";
							mes "精錬値が8以上の時、追加で";
							mes "MaxSP + 50";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "MaxSP + 100";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 3:
							mes "[安息のニーヴ(生命)]";
							mes "5秒毎にHP + 50";
							mes "―――――――――――――";
							mes "精錬値が6以上の時、追加で";
							mes "5秒毎にHP + 50";
							mes "―――――――――――――";
							mes "精錬値が8以上の時、追加で";
							mes "5秒毎にHP + 150";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "5秒毎にHP + 1000";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 4:
							mes "[安息のニーヴ(知力)]";
							mes "5秒毎にSP + 1";
							mes "―――――――――――――";
							mes "精錬値が6以上の時、追加で";
							mes "5秒毎にSP + 1";
							mes "―――――――――――――";
							mes "精錬値が8以上の時、追加で";
							mes "5秒毎にSP + 3";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "5秒毎にSP + 25";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 5:
							continue;
						}
						break;
					case 2:
						switch(select("永劫のニーヴ(火) -> 100","永劫のニーヴ(水) -> 100","永劫のニーヴ(風) -> 100","永劫のニーヴ(地) -> 100","永劫のニーヴ(闇) -> 100","永劫のニーヴ(念) -> 100","永劫のニーヴ(毒) -> 100","戻る")) {
						case 1:
							mes "[永劫のニーヴ(火)]";
							mes "火属性攻撃で";
							mes "受けるダメージ - 20%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "火属性攻撃で";
							mes "受けるダメージ - 15%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "金剛石の靴[1]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 2:
							mes "[永劫のニーヴ(水)]";
							mes "水属性攻撃で";
							mes "受けるダメージ - 20%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "水属性攻撃で";
							mes "受けるダメージ - 15%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "金剛石の靴[1]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 3:
							mes "[永劫のニーヴ(風)]";
							mes "風属性攻撃で";
							mes "受けるダメージ - 20%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "風属性攻撃で";
							mes "受けるダメージ - 15%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "金剛石の靴[1]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 4:
							mes "[永劫のニーヴ(地)]";
							mes "地属性攻撃で";
							mes "受けるダメージ - 20%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "地属性攻撃で";
							mes "受けるダメージ - 15%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "金剛石の靴[1]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 5:
							mes "[永劫のニーヴ(闇)]";
							mes "闇属性攻撃で";
							mes "受けるダメージ - 20%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "闇属性攻撃で";
							mes "受けるダメージ - 15%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "金剛石の靴[1]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 6:
							mes "[永劫のニーヴ(念)]";
							mes "念属性攻撃で";
							mes "受けるダメージ - 20%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "念属性攻撃で";
							mes "受けるダメージ - 15%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "金剛石の靴[1]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 7:
							mes "[永劫のニーヴ(毒)]";
							mes "毒属性攻撃で";
							mes "受けるダメージ - 20%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "毒属性攻撃で";
							mes "受けるダメージ - 15%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "金剛石の靴[1]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 8:
							continue;
						}
						break;
					case 3:
						switch(select("傷のニーヴ(無形) -> 100","傷のニーヴ(不死形) -> 100","傷のニーヴ(動物形) -> 100","傷のニーヴ(植物形) -> 100","傷のニーヴ(昆虫形) -> 100","傷のニーヴ(魚貝形) -> 100","傷のニーヴ(悪魔形) -> 100","傷のニーヴ(人間形) -> 250","傷のニーヴ(天使形) -> 100","傷のニーヴ(竜形) -> 100","傷のニーヴ(プレイヤー) -> 250","戻る")) {
						case 1:
							mes "[傷のニーヴ(無形)]";
							mes "無形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "無形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 2:
							mes "[傷のニーヴ(不死形)]";
							mes "不死形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "不死形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 3:
							mes "[傷のニーヴ(動物形)]";
							mes "動物形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "動物形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 4:
							mes "[傷のニーヴ(植物形)]";
							mes "植物形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "植物形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 5:
							mes "[傷のニーヴ(昆虫形)]";
							mes "昆虫形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "昆虫形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 6:
							mes "[傷のニーヴ(魚貝形)]";
							mes "魚貝形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "魚貝形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 7:
							mes "[傷のニーヴ(悪魔形)]";
							mes "悪魔形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "悪魔形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 8:
							mes "[傷のニーヴ(人間形)]";
							mes "人間形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "人間形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 9:
							mes "[傷のニーヴ(天使形)]";
							mes "天使形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "天使形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 10:
							mes "[傷のニーヴ(竜形)]";
							mes "竜形モンスターから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "竜形モンスターから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 11:
							mes "[傷のニーヴ(プレイヤー)]";
							mes "プレイヤーから";
							mes "受けるダメージ - 30%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "プレイヤーから";
							mes "受けるダメージ - 5%";
							mes "ドラム形プレイヤーから";
							mes "受けるダメージ - 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 12:
							continue;
						}
						break;
					case 4:
						switch(select("血のニーヴ(腕力) -> 100","血のニーヴ(迅速) -> 100","血のニーヴ(体力) -> 100","血のニーヴ(知力) -> 100","血のニーヴ(集中) -> 100","血のニーヴ(幸運) -> 100","戻る")) {
						case 1:
							mes "[血のニーヴ(腕力)]";
							mes "Str + 3";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "Str + 2";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "Str + 2";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "Str + 5";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 2:
							mes "[血のニーヴ(迅速)]";
							mes "Agi + 3";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "Agi + 2";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "Agi + 2";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "Agi + 5";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 3:
							mes "[血のニーヴ(体力)]";
							mes "Vit + 3";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "Vit + 2";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "Vit + 2";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "Vit + 5";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 4:
							mes "[血のニーヴ(知力)]";
							mes "Int + 3";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "Int + 2";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "Int + 2";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "Int + 5";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 5:
							mes "[血のニーヴ(集中)]";
							mes "Dex + 3";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "Dex + 2";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "Dex + 2";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "Dex + 5";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 6:
							mes "[血のニーヴ(幸運)]";
							mes "Luk + 3";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "Luk + 2";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "Luk + 2";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "Luk + 5";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 7:
							continue;
						}
						break;
					case 5:
						switch(select("名誉のニーヴ(迅速) -> 300","名誉のニーヴ(集中) -> 300","名誉のニーヴ(熟練) -> 300","名誉のニーヴ(命中) -> --","名誉のニーヴ(回避) -> --","名誉のニーヴ(幸運) -> --","戻る")) {
						case 1:
							mes "[名誉のニーヴ(迅速)]";
							mes "攻撃速度 + 5%";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "攻撃速度 + 3%";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "攻撃速度 + 2%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "Aspd + 1";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 2:
							mes "[名誉のニーヴ(集中)]";
							mes "詠唱時間 - 5%";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "詠唱時間 - 5%";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "詠唱時間 - 5%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "詠唱時間 - 10%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 3:
							mes "[名誉のニーヴ(熟練)]";
							mes "スキルディレイ - 5%";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "スキルディレイ - 5%";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "スキルディレイ - 5%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "スキルディレイ - 10%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "ニーヴクレイモア[1]、";
							mes "ニーヴグレイヴ[1]、";
							mes "ニーヴジャマダハル[1]、";
							mes "ニーヴシーフボウ[1]、";
							mes "ニーヴハンターボウ[1]、";
							mes "ニーヴクロスボウ[1]、";
							mes "ニーヴウィザードスタッフ[1]、";
							mes "ニーヴアークワンド[1]、";
							mes "ニーヴホーリーステッキ[1]、";
							mes "ニーヴディバインクロス[1]、";
							mes "ニーヴギロチン[1]、";
							mes "ニーヴバスター[1]、";
							mes "ニーヴ風魔手裏剣[1]、";
							mes "ニーヴライフル[1]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 4:
							mes "[ディラン]";
							mes "すみません。";
							mes "^FF0000名誉のニーヴ(命中)^000000については";
							mes "私はよく知らないんです。";
							mes "詳しい事は^0000FFロブ^000000という";
							mes "ニーヴ研究仲間が知っています。";
							next;
							mes "[ディラン]";
							mes "最近会っていないですが、";
							mes "シュバルツバルド共和国で";
							mes "見た人がいるようです。";
							mes "出会ったら、聞いてみてください。";
							break;
						case 5:
							mes "[ディラン]";
							mes "すみません。";
							mes "^FF0000名誉のニーヴ(回避)^000000については";
							mes "私はよく知らないんです。";
							mes "詳しい事は^0000FFロブ^000000という";
							mes "ニーヴ研究仲間が知っています。";
							next;
							mes "[ディラン]";
							mes "最近会っていないですが、";
							mes "シュバルツバルド共和国で";
							mes "見た人がいるようです。";
							mes "出会ったら、聞いてみてください。";
							break;
						case 6:
							mes "[ディラン]";
							mes "すみません。";
							mes "^FF0000名誉のニーヴ(幸運)^000000については";
							mes "私はよく知らないんです。";
							mes "詳しい事は^0000FFロブ^000000という";
							mes "ニーヴ研究仲間が知っています。";
							next;
							mes "[ディラン]";
							mes "最近会っていないですが、";
							mes "シュバルツバルド共和国で";
							mes "見た人がいるようです。";
							mes "出会ったら、聞いてみてください。";
							break;
						case 7:
							continue;
						}
						break;
					case 6:
						switch(select("死のニーヴ(腕力) -> 200","死のニーヴ(知力) -> 200","死のニーヴ(体力) -> 200","死のニーヴ(魔防) -> 200","死のニーヴ(技巧) -> --","死のニーヴ(幸運) -> --","戻る")) {
						case 1:
							mes "[死のニーヴ(腕力)]";
							mes "物理攻撃で";
							mes "与えるダメージ + 3%";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "物理攻撃で";
							mes "与えるダメージ + 1%";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "物理攻撃で";
							mes "与えるダメージ + 1%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "物理攻撃で";
							mes "与えるダメージ + 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 2:
							mes "[死のニーヴ(知力)]";
							mes "魔法攻撃で";
							mes "与えるダメージ + 3%";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "魔法攻撃で";
							mes "与えるダメージ + 1%";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "魔法攻撃で";
							mes "与えるダメージ + 1%";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "魔法攻撃で";
							mes "与えるダメージ + 5%";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 3:
							mes "[死のニーヴ(体力)]";
							mes "Def + 10";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "Def + 15";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "Def + 25";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "Def + 500";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 4:
							mes "[死のニーヴ(魔防)]";
							mes "Mdef + 4";
							mes "―――――――――――――";
							mes "精錬値が7以上の時、追加で";
							mes "Mdef + 6";
							mes "―――――――――――――";
							mes "精錬値が9以上の時、追加で";
							mes "Mdef + 10";
							mes "―――――――――――――";
							mes "[ダークハンド]と";
							mes "共に装備時、追加で";
							mes "Mdef + 20";
							mes "―――――――――――――";
							mes "金剛石の盾[0]、";
							mes "栄光の証[0]、";
							mes "城下町の地図[0]、";
							mes "輝く聖水[0]、";
							mes "金剛石の靴[1]、";
							mes "帯状の暗器[0]、";
							mes "狙撃手の手袋[0]、";
							mes "金剛石のマント[1]に";
							mes "^ff00001回^000000利用可能";
							break;
						case 5:
							mes "[ディラン]";
							mes "すみません。";
							mes "^FF0000死のニーヴ(技巧)^000000については";
							mes "私はよく知らないんです。";
							mes "詳しい事は^0000FFロブ^000000という";
							mes "ニーヴ研究仲間が知っています。";
							next;
							mes "[ディラン]";
							mes "最近会っていないですが、";
							mes "シュバルツバルド共和国で";
							mes "見た人がいるようです。";
							mes "出会ったら、聞いてみてください。";
							break;
						case 6:
							mes "[ディラン]";
							mes "すみません。";
							mes "^FF0000死のニーヴ(幸運)^000000については";
							mes "私はよく知らないんです。";
							mes "詳しい事は^0000FFロブ^000000という";
							mes "ニーヴ研究仲間が知っています。";
							next;
							mes "[ディラン]";
							mes "最近会っていないですが、";
							mes "シュバルツバルド共和国で";
							mes "見た人がいるようです。";
							mes "出会ったら、聞いてみてください。";
							break;
						case 7:
							continue;
						}
						break;
					case 7:
						emotion 15;
						mes "[ディラン]";
						mes "ご利用ありがとうございました。";
						mes "またのお越しを";
						mes "お待ちしております。";
						close;
					}
					next;
					continue;
				}
			case 3:
				emotion 15;
				mes "[ディラン]";
				mes "ご利用ありがとうございました。";
				mes "またのお越しを";
				mes "お待ちしております。";
				close;
			}
		}
	case 3:
		mes "[ディラン]";
		mes "王家貢献の証で";
		mes "交換を希望されるのですね。";
		mes "どちらをご所望ですか？";
		next;
		setarray '@menu$,"金剛石の盾[0] -> 50","栄光の証[0] -> 500","城下町の地図[0] -> 500","輝く聖水[0] -> 500","^888888【選択不可】ドラゴンホーン^000000 -> 500","^888888【選択不可】コールオブネメシス^000000 -> 500","王家の青い箱 -> 5","やめる";
		if(Job == Job_RuneKnight || Job == Job_DragonKnight)
			set '@menu$[4],"ドラゴンホーン -> 500";
		if(Job == Job_RoyalGuard || Job == Job_ImperialGuard)
			set '@menu$[5],"コールオブネメシス -> 500";
		set '@i,select(printarray('@menu$)) - 1;
		switch('@i) {
		case 0:		// 金剛石の盾
			set '@gain,28920;
			set '@amount,50;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "交換を希望する品物は";
			mes "金剛石の盾[0]で";
			mes "よろしいですか？";
			break;
		case 1:		// 栄光の証[0]
			set '@gain,28499;
			set '@amount,500;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "交換を希望する品物は";
			mes "栄光の証[0]で";
			mes "よろしいですか？";
			break;
		case 2:		// 城下町の地図[0]
			set '@gain,28497;
			set '@amount,500;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "交換を希望する品物は";
			mes "城下町の地図[0]で";
			mes "よろしいですか？";
			break;
		case 3:		// 輝く聖水[0]
			set '@gain,28498;
			set '@amount,500;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "交換を希望する品物は";
			mes "輝く聖水[0]で";
			mes "よろしいですか？";
			break;
		case 4:		// ドラゴンホーン
			if(Job == Job_RuneKnight || Job == Job_DragonKnight) {
				set '@gain,23219;
				set '@amount,500;
				if(countitem(6919) < '@amount) {
					mes "[ディラン]";
					mes "お持ちの王家貢献の証が";
					mes "足りないようです。";
					mes "必要数をお確かめの上、";
					mes "もう一度お声かけください。";
					close;
				}
				mes "[ディラン]";
				mes "交換を希望する品物は";
				mes "ドラゴンホーンで";
				mes "よろしいですか？";
			} else {
				mes "[ディラン]";
				mes "申し訳ございません。";
				mes "ご所望のアイテムは";
				mes "ルーンナイトの方のみ";
				mes "使用できるアイテムのため、";
				mes "交換を受け付けておりません。";
				close;
			}
			break;
		case 5:		// コールオブネメシス
			if(Job == Job_RoyalGuard || Job == Job_ImperialGuard) {
				set '@gain,23220;
				set '@amount,500;
				if(countitem(6919) < '@amount) {
					mes "[ディラン]";
					mes "お持ちの王家貢献の証が";
					mes "足りないようです。";
					mes "必要数をお確かめの上、";
					mes "もう一度お声かけください。";
					close;
				}
				mes "[ディラン]";
				mes "交換を希望する品物は";
				mes "コールオブネメシスで";
				mes "よろしいですか？";
			} else {
				mes "[ディラン]";
				mes "申し訳ございません。";
				mes "ご所望のアイテムは";
				mes "ロイヤルガードの方のみ";
				mes "使用できるアイテムのため、";
				mes "交換を受け付けておりません。";
				close;
			} 
			break;
		case 6:		// 王家の青い箱
			set '@gain,22901;
			mes "[ディラン]";
			mes "王家の青い箱ですね。";
			mes "いくつ交換をご希望ですか？";
			mes "一度に最大100個まで";
			mes "交換をお受けいたします。";
			next;
			input '@num;
			if('@num <= 0) {
				mes "[ディラン]";
				mes "交換数が決まりましたら";
				mes "もう一度お声かけください。";
				close;
			}
			if('@num > 100) {
				mes "[ディラン]";
				mes "申し訳ございません。";
				mes "一度に交換できるのは";
				mes "100個までです。";
				mes "交換数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			set '@amount,5 * '@num;
			if(countitem(6919) < '@amount) {
				mes "[ディラン]";
				mes "お持ちの王家貢献の証が";
				mes "足りないようです。";
				mes "必要数をお確かめの上、";
				mes "もう一度お声かけください。";
				close;
			}
			mes "[ディラン]";
			mes "交換を希望する品物は";
			mes "王家の青い箱で";
			mes "よろしいですか？";
			mes "(交換数 : "+'@num+"個)";
			next;
			if(select("いいえ","はい") == 1) {
				mes "[ディラン]";
				mes "品物が決まりましたら";
				mes "もう一度お声かけください。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "[ディラン]";
				mes "アイテムの種類数が";
				mes "多すぎるようです。";
				mes "荷物を減らしていただけますか。";
				close;
			}
			if(checkweight('@gain,'@num) == 0) {
				mes "[ディラン]";
				mes "所持しているアイテムが";
				mes "重すぎるようです。";
				mes "荷物を軽くしていただけますか。";
				close;
			}
			delitem 6919,'@amount;
			getitem '@gain,'@num;
			emotion 15;
			mes "[ディラン]";
			mes "ご利用ありがとうございました。";
			mes "またのお越しを";
			mes "お待ちしております。";
			close;
		default:
			mes "[ディラン]";
			mes "ご利用ありがとうございました。";
			mes "またのお越しを";
			mes "お待ちしております。";
			close;
		}
		next;
		if(select("いいえ","はい") == 1) {
			mes "[ディラン]";
			mes "品物が決まりましたら";
			mes "もう一度お声かけください。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "[ディラン]";
			mes "アイテムの種類数が";
			mes "多すぎるようです。";
			mes "荷物を減らしていただけますか。";
			close;
		}
		if(checkweight('@gain,1) == 0) {
			mes "[ディラン]";
			mes "所持しているアイテムが";
			mes "重すぎるようです。";
			mes "荷物を軽くしていただけますか。";
			close;
		}
		delitem 6919,'@amount;
		getitem '@gain,1;
		emotion 15;
		mes "[ディラン]";
		mes "ご利用ありがとうございました。";
		mes "またのお越しを";
		mes "お待ちしております。";
		close;
	case 4:
		mes "[ディラン]";
		mes "王家貢献の証での";
		mes "交換ラインナップの確認ですね。";
		mes "どちらをご覧になりますか？";
		next;
		while(1) {
			switch(select("金剛石の盾[0] -> 50","栄光の証[0] -> 500","城下町の地図[0] -> 500","輝く聖水[0] -> 500","ドラゴンホーン -> 500","コールオブネメシス -> 500","王家の青い箱 -> 5","立ち去る")) {
			case 1:
				mes "[金剛石の盾[0]]";
				mes "BaseLv150以上の時、追加で";
				mes "Def + 100";
				mes "─────────────";
				mes "[金剛石の盾]の";
				mes "精錬値が3上がる度に追加で";
				mes "Def + 20";
				mes "─────────────";
				mes "[栄光の証]と";
				mes "共に装備時、追加で";
				mes "完全回避 + 10";
				mes "―――――――――――――";
				mes "系列 : ^777777盾^000000";
				mes "防御 : ^77777750^000000";
				mes "重量 : ^777777100^000000";
				mes "要求レベル : ^777777100^000000";
				mes "装備 : ^777777全ての職業^000000";
				break;
			case 2:
				mes "[栄光の証[0]]";
				mes "すべてのステータス + 1";
				mes "―――――――――――――";
				mes "物理・魔法攻撃で";
				mes "与えるダメージ + 2%";
				mes "─────────────";
				mes "BaseLv150以上の時、追加で";
				mes "すべてのステータス + 1";
				mes "物理・魔法攻撃で";
				mes "与えるダメージ + 2%";
				mes "─────────────";
				mes "[金剛石の盾]と";
				mes "共に装備時、追加で";
				mes "完全回避 + 10";
				mes "―――――――――――――";
				mes "系列 : ^777777アクセサリー^000000";
				mes "防御 : ^7777770^000000";
				mes "重量 : ^77777710^000000";
				mes "要求レベル : ^777777100^000000";
				mes "装備 : ^777777全ての職業^000000";
				break;
			case 3:
				mes "[城下町の地図[0]]";
				mes "物理攻撃で";
				mes "与えるダメージ + 2%";
				mes "―――――――――――――";
				mes "攻撃速度 + 3%";
				mes "―――――――――――――";
				mes "系列 : ^777777アクセサリー^000000";
				mes "防御 : ^7777770^000000";
				mes "重量 : ^77777710^000000";
				mes "要求レベル : ^777777100^000000";
				mes "装備 : ^777777全ての職業^000000";
				break;
			case 4:
				mes "[輝く聖水[0]]";
				mes "魔法攻撃で";
				mes "与えるダメージ + 2%";
				mes "―――――――――――――";
				mes "詠唱時間 - 5%";
				mes "―――――――――――――";
				mes "系列 : ^777777アクセサリー^000000";
				mes "防御 : ^7777770^000000";
				mes "重量 : ^77777710^000000";
				mes "要求レベル : ^777777100^000000";
				mes "装備 : ^777777全ての職業^000000";
				break;
			case 5:
				mes "[ドラゴンホーン]";
				mes "―――――――――――――";
				mes "^ff0000※ドラゴンホーンは^000000";
				mes "^ff0000ルーンナイトの方のみ^000000";
				mes "^ff0000交換可能です。^000000";
				mes "―――――――――――――";
				mes "[ドラゴンホーン]使用時、";
				mes "[ドラゴン";
				mes "トレーニング]Lv5を";
				mes "習得している場合、";
				mes "ドラゴンに";
				mes "騎乗することができる";
				mes "―――――――――――――";
				mes "再使用待機時間20秒";
				mes "―――――――――――――";
				mes "^FF0000[ドラゴンホーン]は";
				mes "攻城戦・新攻城戦の砦内・";
				mes "ターボトラックでは";
				mes "使用できません^000000";
				mes "―――――――――――――";
				mes "^FF0000[ドラゴンホーン]は";
				mes "NPC売却・倉庫への移動のみ";
				mes "可能です^000000";
				mes "―――――――――――――";
				mes "重量 : ^7777770^000000";
				break;
			case 6:
				mes "[コールオブネメシス]";
				mes "―――――――――――――";
				mes "^ff0000※コールオブネメシスは^000000";
				mes "^ff0000ロイヤルガードの方のみ^000000";
				mes "^ff0000交換可能です。^000000";
				mes "―――――――――――――";
				mes "ロイヤルガードが";
				mes "[コールオブネメシス]使用時";
				mes "[騎兵修練]Lv5を";
				mes "習得している場合、";
				mes "グリフォンに";
				mes "騎乗することができる";
				mes "―――――――――――――";
				mes "再使用待機時間20秒";
				mes "―――――――――――――";
				mes "^FF0000[コールオブネメシス]は";
				mes "攻城戦・新攻城戦の砦内・";
				mes "ターボトラックでは";
				mes "使用できません^000000";
				mes "―――――――――――――";
				mes "^FF0000[コールオブネメシス]は";
				mes "NPC売却・倉庫への移動のみ";
				mes "可能です^000000";
				mes "―――――――――――――";
				mes "重量 : ^7777770^000000";
				break;
			case 7:
				mes "[王家の青い箱]";
				mes "―――――――――――――";
				mes "^ff0000※王家の青い箱は使用すると^000000";
				mes "^ff0000ランダムでアイテムを1つ^000000";
				mes "^ff0000入手できます。^000000";
				mes "―――――――――――――";
				mes "知る人ぞ知っている";
				mes "あの箱とそっくり。";
				mes "だけど中身は";
				mes "確実に違うようだ。";
				mes "―――――――――――――";
				mes "重量 : ^77777720^000000";
				break;
			case 8:
				mes "[ディラン]";
				mes "わかりました。";
				mes "必要になったらまた来てください。";
				close;
			}
			next;
			continue;
		}
		close;
	case 5:
		mes "[ディラン]";
		mes "ご利用ありがとうございました。";
		mes "またのお越しを";
		mes "お待ちしております。";
		close;
	}
}

prt_cas.gat,21,33,4	script	ニルレムの助手#ep16jp	893,{
	mes "[ニルレムの助手]";
	mes "こちらでは、時魔術師のローブの";
	mes "時を戻したり、エンチャントを";
	mes "行う事ができます。";
	next;
	setarray '@menu$,"時魔術師のローブの交換","時魔術師のローブの時を戻す","超越者のローブエンチャント","時魔術師のローブについて聞く","超越者のローブについて聞く","やめる";
	if(countitem(6941) == 0)
		set '@menu$[0],"^888888"+'@menu$[0]+"^000000";
	if(getequiprefinerycnt(2) < 9 || getequipid(2) != 15193)
		set '@menu$[1],"^888888"+'@menu$[1]+"^000000";
	if(getequiprefinerycnt(2) < 9 || getequipid(2) != 15194 || getequipcardid(2,3) == 4876)
		set '@menu$[2],"^888888"+'@menu$[2]+"^000000";
	switch(select(printarray('@menu$))) {
	case 1:		// TODO
		mes "[ニルレムの助手]";
		mes "ニルレム様は魔力を多く含む";
		mes "アイテムを集めておられます。";
		next;
		mes "[ニルレムの助手]";
		mes "一説によると、過去に";
		mes "ヴァルキリーの力の破片と呼ばれる";
		mes "強大な魔力を持つ";
		mes "宝石があったそうです。";
		next;
		if(countitem(6941) == 0) {
			mes "[ニルレムの助手]";
			mes "もしそのようなアイテムを";
			mes "入手したら私のところまで";
			mes "持ってきてください。";
			mes "お礼は弾みますよ。";
			close;
		}
		mes "[ニルレムの助手]";
		mes "おぉ、それは";
		mes "ヴァルキリーの力の破片!!";
		next;
		mes "[ニルレムの助手]";
		mes "それを1個譲って頂けるなら";
		mes "お礼として偉大なマジシャン";
		mes "ニルレム様の愛用する";
		mes "ローブを一着お渡ししましょう。";
		next;
		if(select("いいえ","はい") == 1) {
			mes "[ニルレムの助手]";
			mes "残念です……。";
			mes "気が変わったら来てください。";
			mes "いつでもお待ちしています。";
			close;
		}
		if(checkitemblank() == 0) {
			mes "[ニルレムの助手]";
			mes "アイテムの種類数が多いです。";
			mes "荷物を減らしてください。";
			close;
		}
		delitem 6941,1;
		getitem 15193,1;
		emotion 15;
		mes "[ニルレムの助手]";
		mes "ありがとうございます。";
		mes "これでニルレム様も";
		mes "お喜びになります。";
		close;
	case 2:		// TODO
		mes "[ニルレムの助手]";
		mes "時魔術師のローブは";
		mes "一見古ぼけたローブですが、";
		mes "その昔はとても強力な";
		mes "魔力を放っていたと";
		mes "言い伝えられています。";
		next;
		mes "[ニルレムの助手]";
		mes "時を戻すことで";
		mes "失われた力を取り戻せますが、";
		mes "そのためにはローブを時間移動に";
		mes "耐えれる程度に";
		mes "鍛える必要があります。";
		next;
		if(getequiprefinerycnt(2) < 9 || getequipid(2) != 15193) {
			mes "[ニルレムの助手]";
			mes "時魔術師のローブを";
			mes "+9以上に鍛えたら";
			mes "持ってきてください。";
			close;
		}
		if(select("時を戻す","やめておく") == 2) {
			mes "[ニルレムの助手]";
			mes "そうですか。";
			close;
		}
		delequip 2;
		getitem 15194,1;
		emotion 21;
		misceffect 676,"";
		mes "[ニルレムの助手]";
		mes "どうぞ、お受け取り下さい。";
		close;
	case 3:		// TODO
		mes "[ニルレムの助手]";
		mes "超越者のローブは";
		mes "強大な力を持っていますが、";
		mes "エクラージュで会得した";
		mes "秘儀を使えばさらなる力を";
		mes "引き出せるかもしれません。";
		next;
		mes "[ニルレムの助手]";
		mes "力を引き出すためには";
		mes "事前に超越者のローブを";
		mes "ある程度鍛えておく必要があります。";
		next;
		if(getequiprefinerycnt(2) < 9 || getequipid(2) != 15194) {
			mes "[ニルレムの助手]";
			mes "超越者のローブを";
			mes "+9以上に鍛えたら";
			mes "持ってきてください。";
			close;
		}
		// エンチャント済み(仮)
		if(getequipcardid(2,3) == 4876) {
			mes "[ニルレムの助手]";
			mes "おや？";
			mes "その超越者のローブは";
			mes "すでにエンチャントされています。";
			close;
		}
		mes "[ニルレムの助手]";
		mes "エンチャントしますか？";
		next;
		if(select("エンチャントをする","やめておく") == 2) {
			mes "[ニルレムの助手]";
			mes "そうですか。";
			close;
		}
		set '@refine,getequiprefinerycnt(2);
		set '@card[0],getequipcardid(2,0);
		set '@card[1],getequipcardid(2,1);
		set '@card[2],getequipcardid(2,2);
		set '@card[3],4876;		// 暴走した魔力
		delequip 2;
		getitem2 15194,1,1,'@refine,0,'@card[0],'@card[1],'@card[2],'@card[3];
		mes "[ニルレムの助手]";
		mes "エンチャントは終了しました。";
		mes "どうぞ、お受け取り下さい。";
		close;
	case 4:
		mes "[ニルレムの助手]";
		mes "こちらでは、";
		mes "ヴァルキリーの力の破片を";
		mes "1個譲っていただくと";
		mes "お礼に時魔術師のローブを";
		mes "1個お渡ししています。";
		next;
		mes "[ニルレムの助手]";
		mes "時魔術師のローブの性能は";
		mes "以下の通りです。";
		next;
		mes "[時魔術師のローブ]";
		mes "Matk + 30";
		mes "─────────────";
		mes "詠唱時間 - 5%";
		mes "─────────────";
		mes "魔法攻撃命中時、";
		mes "一定確率で10秒間、";
		mes "[時魔術師のローブ]の";
		mes "精錬値が1上がる度に追加で";
		mes "Int + 3";
		mes "─────────────";
		mes "[力の時空ブーツ]、";
		mes "[俊敏の時空ブーツ]、";
		mes "[体力の時空ブーツ]、";
		mes "[知力の時空ブーツ]、";
		mes "[技巧の時空ブーツ]、";
		mes "[幸運の時空ブーツ]の";
		mes "いずれかと共に装備時、";
		mes "追加で";
		mes "MaxHP + 20%";
		mes "―――――――――――――";
		mes "系列 : ^777777鎧^000000";
		mes "防御 : ^77777735^000000";
		mes "重量 : ^77777780^000000";
		mes "要求レベル : ^777777100^000000";
		mes "装備 : ^777777ノービス系を除く全ての職業^000000";
		next;
		mes "[ニルレムの助手]";
		mes "また、精錬値が+9以上の";
		mes "時魔術師のローブを持って来て頂ければ";
		mes "失われた力を取り戻した";
		mes "超越者のローブにして差し上げることが";
		mes "可能です。";
		close;
	case 5:
		mes "[ニルレムの助手]";
		mes "こちらでは、精錬値が+9以上の";
		mes "時魔術師のローブの時を戻し、";
		mes "失われた力を取り戻した";
		mes "超越者のローブにして差し上げることが";
		mes "可能です。";
		next;
		mes "[ニルレムの助手]";
		mes "超越者のローブの性能は";
		mes "以下の通りです。";
		next;
		mes "[超越者のローブ]";
		mes "Matk + 60";
		mes "─────────────";
		mes "詠唱時間 - 5%";
		mes "─────────────";
		mes "詠唱が中断されない";
		mes "─────────────";
		mes "[超越者のローブ]の";
		mes "精錬値が1上がる度に追加で";
		mes "Int + 3";
		mes "念属性魔法攻撃で";
		mes "与えるダメージ + 2%";
		mes "─────────────";
		mes "[ニーズヘッグの影カード]と";
		mes "共に装備時、追加で";
		mes "絶対に凍結状態にならない";
		mes "魔法攻撃で";
		mes "モンスターを倒した時、";
		mes "HP + 200 ,SP + 20";
		mes "─────────────";
		mes "[力の時空ブーツ]、";
		mes "[俊敏の時空ブーツ]、";
		mes "[体力の時空ブーツ]、";
		mes "[知力の時空ブーツ]、";
		mes "[技巧の時空ブーツ]、";
		mes "[幸運の時空ブーツ]の";
		mes "いずれかと共に装備時、";
		mes "追加で";
		mes "MaxHP + 20%";
		mes "―――――――――――――";
		mes "系列 : ^777777鎧^000000";
		mes "防御 : ^77777735^000000";
		mes "重量 : ^77777780^000000";
		mes "要求レベル : ^777777100^000000";
		mes "装備 : ^777777ノービス系を除く全ての職業^000000";
		next;
		mes "[ニルレムの助手]";
		mes "また、超越者のローブの";
		mes "精錬値を+9以上にすると";
		mes "特別なエンチャントを";
		mes "超越者のローブに";
		mes "施して差し上げます。";
		next;
		mes "[ニルレムの助手]";
		mes "なんと！";
		mes "精錬値やカードはそのままに";
		mes "暴走した魔力という能力を";
		mes "超越者のローブの第4スロットに";
		mes "エンチャントできるのです。";
		next;
		mes "[ニルレムの助手]";
		mes "^ff0000ただし、すでに第4スロットが";
		mes "^ff0000エンチャント済みの場合、";
		mes "^ff0000エンチャントが上書きされます。^000000";
		next;
		mes "[ニルレムの助手]";
		mes "暴走した魔力の能力は";
		mes "以下の通りです。";
		next;
		mes "[暴走した魔力]";
		mes "魔法攻撃命中時、";
		mes "一定確率で10秒間、";
		mes "[暴走した魔力]発動";
		mes "―――――――――――――";
		mes "[暴走した魔力]発動時、";
		mes "Int + 200";
		mes "1秒毎にSP - 200";
		mes "―――――――――――――";
		mes "[カルデュイの耳]、";
		mes "[ラフィネシールド]と";
		mes "共に装備時、";
		mes "[コメット]の";
		mes "再使用待機時間減少効果が";
		mes "発動しない";
		mes "―――――――――――――";
		mes "[堕ちた大神官ヒバムカード]";
		mes "と共に装備時、";
		mes "[堕ちた大神官ヒバムカード]";
		mes "の効果が発動しない";
		next;
		mes "[ニルレムの助手]";
		mes "とても魅力的だと思いますので";
		mes "時魔術師のローブをお持ちなら";
		mes "ぜひ、エンチャントなどを";
		mes "ご依頼ください。";
		close;
	case 6:
		mes "[ニルレムの助手]";
		mes "気が変わったら来てください。";
		mes "いつでもお待ちしています。";
		close;
	}
}

//============================================================
// パワフルカード交換NPC
//------------------------------------------------------------
prt_cas.gat,27,16,4	script	モンスター研究家#ep16jp	866,{
	if(!(checkquest(73130) & 0x8)) {
		mes "[モンスター研究家]";
		mes "私は^0000ffパワフルモンスター^000000と呼ばれる";
		mes "^0000ff希少種^000000の研究をしている者です。";
		next;
		mes "[モンスター研究家]";
		mes "パワフルモンスターは";
		mes "通常のモンスターと";
		mes "色や大きさが異なり、";
		mes "強力な力を持っています。";
		next;
		mes "[モンスター研究家]";
		mes "王国内ではスケルトンや";
		mes "アーチャースケルトンなどの";
		mes "希少種が確認されており、";
		mes "何れも通常のそれに比べて";
		mes "強いモンスターでした。";
		next;
		mes "[モンスター研究家]";
		mes "パワフルモンスターは";
		mes "その力だけでなく、";
		mes "^0000ffカードもより強力な^000000";
		mes "^0000ff効果を持つといいます。^000000";
		next;
		mes "[モンスター研究家]";
		mes "しかし、パワフルモンスターは";
		mes "希少種のため滅多に";
		mes "出会うことが出来ません。";
		mes "そのためカードの入手は";
		mes "困難を極めます。";
		next;
		mes "[モンスター研究家]";
		mes "しかし、私は長年の研究の末、";
		mes "ついにパワフルモンスターの";
		mes "カードを作りだすことに";
		mes "成功したのです。";
		next;
		mes "[モンスター研究家]";
		mes "パワフルモンスターのカードは";
		mes "^0000ff通常のモンスターのカードを^000000";
		mes "^0000ff複数枚重ね、ルーンの力で^000000";
		mes "^0000ff圧縮することによって生成できます。^000000";
		next;
		mes "[モンスター研究家]";
		mes "もし興味があれば";
		mes "私のところにカードと";
		mes "「^0000ffルーン魔法の粉^000000」を";
		mes "持ってきてください。";
		mes "例え装着済みでも";
		mes "圧縮してあげますよ。";
		setquest 73130;
		compquest 73130;
		close;
	}
	mes "[モンスター研究家]";
	mes "ようこそいらっしゃいました。";
	mes "本日はどのようなご用件ですか？";
	next;
	switch(select("パワフルカードの生成","装着済みのカードのアップグレード","パワフルカードの性能を見る","やめる")) {
	case 1:
		mes "[モンスター研究家]";
		mes "どのモンスターの";
		mes "カードの生成をご希望ですか？";
		next;
		switch(select("パワフルAスケルトン","パワフルスケルトン","パワフルSスケルトン","パワフルアムダライス","やめる")) {
		case 1:	// パワフルAスケルトンカード
			set '@gain,27037;
			setarray '@nameid,4094,6920;
			setarray '@amount,4,5;
			break;
		case 2:	// パワフルスケルトンカード
			set '@gain,27036;
			setarray '@nameid,4025,6920;
			setarray '@amount,7,5;
			break;
		case 3:	// パワフルSスケルトンカード
			set '@gain,27038;
			setarray '@nameid,4086,6920;
			setarray '@amount,5,5;
			break;
		case 4:	// パワフルアムダライスカード
			set '@gain,27039;
			setarray '@nameid,4601,6920;
			setarray '@amount,2,20;
			break;
		case 5:
			mes "[モンスター研究家]";
			mes "わかりました。";
			mes "必要になったらまた来てください。";
			close;
		}
		mes "[モンスター研究家]";
		mes "^0000ff" +getitemname('@gain)+ "^000000";
		mes "ですね。";
		mes getitemname('@nameid[0])+ " " +'@amount[0]+ "個";
		mes getitemname('@nameid[1])+ " " +'@amount[1]+ "個";
		mes "でお作りしましょう。";
		next;
		if(select("いいえ","はい") == 1) {
			mes "[モンスター研究家]";
			mes "わかりました。";
			mes "必要になったらまた来てください。";
			close;
		}
		if(countitem('@nameid[0]) < '@amount[0] || countitem('@nameid[1]) < '@amount[1]) {
			mes "[モンスター研究家]";
			mes "むむっ";
			mes "材料が足りないようですね。";
			mes "もう一度ご確認いただけますか？";
			close;
		}
		if(checkitemblank() == 0) {
			// 未調査
			mes "‐荷物をこれ以上持てません";
			mes "　荷物に1個以上の空きを";
			mes "　作ってください‐";
			close;
		}
		delitem '@nameid[0],'@amount[0];
		delitem '@nameid[1],'@amount[1];
		getitem '@gain,1;
		misceffect 102,"";
		misceffect 107,"";
		misceffect 135,"";
		mes "[モンスター研究家]";
		mes "ふぅ、無事にできたようです。";
		mes "大事にしてくださいね。";
		close;
	case 2:
		mes "[モンスター研究家]";
		mes "既に装備に装着されている";
		mes "カードのアップグレードを";
		mes "ご希望ですね。";
		mes "装備の精錬値、他の装着済みのカード、";
		mes "エンチャント、ランダムオプションを";
		mes "維持したままアップグレードできます。";
		next;
		mes "[モンスター研究家]";
		mes "アップグレードに必要な";
		mes "元となるカードの枚数は、";
		mes "通常のパワフルカード生成の時よりも";
		mes "1枚分少なくなります。";
		mes "装着済みのカードを1枚分の材料として";
		mes "使用できるからです。";
		next;
		mes "[モンスター研究家]";
		mes "アップグレードの際の注意点ですが、";
		mes "まず、対象となるカードが装着された";
		mes "装備を身に付けてください。";
		mes "また、武器カードの";
		mes "アップグレードの場合は必ず^0000ff右手^000000に";
		mes "装備するようにしてください。";
		next;
		mes "[モンスター研究家]";
		mes "^0000ff1つの装備に同じカードが複数^000000";
		mes "^0000ff装着されている場合、^000000";
		mes "^0000ff若いスロット番号のカードから先に^000000";
		mes "^0000ffアップグレードが行われます。^000000";
		mes "^0000ffスロットの左の方にあるカードが^000000";
		mes "^0000ff優先的に対象になる、ということです。^000000";
		next;
		mes "[モンスター研究家]";
		mes "どのモンスターのカードへの";
		mes "アップグレードをご希望ですか？";
		next;
		switch(select("パワフルAスケルトン","パワフルスケルトン","パワフルSスケルトン","パワフルアムダライス","やめる")) {
		case 1:	// パワフルAスケルトンカード
			set '@pos,4;
			set '@gain,27037;
			setarray '@nameid,4094,6920;
			setarray '@amount,3,5;
			break;
		case 2:	// パワフルスケルトンカード
			set '@pos,4;
			set '@gain,27036;
			setarray '@nameid,4025,6920;
			setarray '@amount,6,5;
			break;
		case 3:	// パワフルSスケルトンカード
			set '@pos,4;
			set '@gain,27038;
			setarray '@nameid,4086,6920;
			setarray '@amount,4,5;
			break;
		case 4:	// パワフルアムダライスカード
			set '@pos,2;
			set '@gain,27039;
			setarray '@nameid,4601,6920;
			setarray '@amount,1,20;
			break;
		case 5:
			mes "[モンスター研究家]";
			mes "わかりました。";
			mes "必要になったらまた来てください。";
			close;
		}
		mes "[モンスター研究家]";
		mes "装備に装着されている";
		mes "^ff0000" +getitemname('@nameid[0])+ "^000000を";
		mes "^0000ff" +getitemname('@gain)+ "^000000";
		mes "にアップグレードするのですね。";
		mes getitemname('@nameid[0])+ " " +'@amount[0]+ "個";
		mes getitemname('@nameid[1])+ " " +'@amount[1]+ "個 が必要です。";
		next;
		if(select("いいえ","はい") == 1) {
			mes "[モンスター研究家]";
			mes "わかりました。";
			mes "必要になったらまた来てください。";
			close;
		}
		if(getequipisequiped('@pos)==0) {
			mes "[モンスター研究家]";
			mes "むむっ";
			mes "カードに対応した部位に";
			mes "何も装備されていないようです。";
			mes "もう一度ご確認いただけますか？";
			close;
		}
		for(set '@i,0; '@i < 4; set '@i,'@i+1) {
			if(getequipcardid('@pos,'@i) == '@nameid[0])
				break;
		}
		if('@i == 4) {
			mes "[モンスター研究家]";
			mes "むむっ";
			mes "その装備には";
			mes "^0000ff元となるカード^000000が";
			mes "装着されていないようです。";
			mes "もう一度ご確認いただけますか？";
			close;
		}
		// 未調査
		if(countitem('@nameid[0]) < '@amount[0] || countitem('@nameid[1]) < '@amount[1]) {
			mes "[モンスター研究家]";
			mes "むむっ";
			mes "材料が足りないようですね。";
			mes "もう一度ご確認いただけますか？";
			close;
		}
		delitem '@nameid[0],'@amount[0];
		delitem '@nameid[1],'@amount[1];
		setequipcardid '@pos,'@i,'@gain,0x2;
		misceffect 102,"";
		misceffect 107,"";
		misceffect 135,"";
		mes "[モンスター研究家]";
		mes "ふぅ、無事にできたようです。";
		mes "大事にしてくださいね。";
		close;
	case 3:
		mes "[モンスター研究家]";
		mes "どのパワフルカードを";
		mes "ご覧になりますか？";
		while(1) {
			next;
			switch(select("パワフルAスケルトンカード","パワフルスケルトンカード","パワフルSスケルトンカード","パワフルアムダライスカード","立ち去る")) {
			case 1:
				mes "[パワフルAスケルトンカード]";
				mes "遠距離物理攻撃で";
				mes "与えるダメージ + 5%";
				mes "―――――――――――――";
				mes "BaseLvが20上がる度に追加で";
				mes "遠距離物理攻撃で";
				mes "与えるダメージ + 1%";
				mes "―――――――――――――";
				mes "系列 : ^777777カード^000000";
				mes "装備 : ^777777武器^000000";
				mes "重量 : ^7777771^000000";
				continue;
			case 2:
				mes "[パワフルスケルトンカード]";
				mes "Atk + 5";
				mes "―――――――――――――";
				mes "物理攻撃命中時、";
				mes "一定確率で敵を";
				mes "スタン状態にする";
				mes "―――――――――――――";
				mes "BaseLvが20上がる度に追加で";
				mes "Atk + 3";
				mes "敵をスタン状態にする";
				mes "確率が上昇";
				mes "―――――――――――――";
				mes "系列 : ^777777カード^000000";
				mes "装備 : ^777777武器^000000";
				mes "重量 : ^7777771^000000";
				continue;
			case 3:
				mes "[パワフルSスケルトンカード]";
				mes "Cri + 5";
				mes "―――――――――――――";
				mes "BaseLvが20上がる度に追加で";
				mes "Atk + 5 , Cri + 1";
				mes "―――――――――――――";
				mes "系列 : ^777777カード^000000";
				mes "装備 : ^777777武器^000000";
				mes "重量 : ^7777771^000000";
				continue;
			case 4:
				mes "[パワフルアムダライスカード]";
				mes "物理・魔法攻撃で";
				mes "与えるダメージ + 12%";
				mes "―――――――――――――";
				mes "BaseLvが20上がる度に追加で";
				mes "物理・魔法攻撃で";
				mes "与えるダメージ + 1%";
				mes "―――――――――――――";
				mes "2秒毎にHP - 666 , SP - 66";
				mes "―――――――――――――";
				mes "装備解除時、";
				mes "HP - 6666 , SP - 666";
				mes "―――――――――――――";
				mes "系列 : ^777777カード^000000";
				mes "装備 : ^777777鎧^000000";
				mes "重量 : ^7777771^000000";
				continue;
			case 5:
				mes "[モンスター研究家]";
				mes "わかりました。";
				mes "必要になったらまた来てください。";
				close;
			}
		}	// end while
	case 4:
		mes "[モンスター研究家]";
		mes "わかりました。";
		mes "必要になったらまた来てください。";
		close;
	}
}

prt_cas.gat,27,24,3	script(CLOAKED)	マジシャン・ニルレム#ep16_wiz02	735,{}

prt_cas.gat,27,27,3	script	グラハム#ep16jp	86,{
	if(EP16_1QUE < 1) {
		mes "[グラハム]";
		mes "冒険者歓迎室は";
		mes "各街に居る^0000ff王室急使^000000によって";
		mes "招かれた方へのサービスを";
		mes "行う部屋です。";
		next;
		mes "[グラハム]";
		mes "魔王モロクの遠征と討伐に";
		mes "貢献した英雄の方は";
		mes "王室急使に申し出ていただければ";
		mes "祝宴に^4d4dff貴賓としてご招待^000000";
		mes "いたします。";
		close;
	}
	if(!(checkquest(73131) & 0x8)) {
		mes "[グラハム]";
		mes strcharinfo(0)+ "様。";
		mes "お待ちしておりました。";
		next;
		mes "[グラハム]";
		mes "冒険者歓迎室では";
		mes "ここでの生活に不便がないよう";
		mes "傷の治療や倉庫の管理などの";
		mes "お世話をさせていただきますので、";
		mes "何なりとお申し付けください。";
		close2;
		setquest 73131;
		compquest 73131;
		end;
	}
	mes "[グラハム]";
	mes "ようこそお越しくださいました、";
	mes strcharinfo(0)+ "様。";
	mes "本日はいかがいたしましょう？";
	next;
	setarray '@menu$,"位置セーブサービス","倉庫サービス -> 50zeny","傷の治療 -> 5000zeny","転送サービス -> 無料","カートサービス -> 800zeny","終了";
	if(EP16_1QUE < 18)
		set '@menu$[3],"^888888転送サービス -> 無料^000000";
	set '@i,select(printarray('@menu$));
	switch('@i) {
	case 1:
		savepoint "prt_cas.gat",9,15;
		mes "[グラハム]";
		mes "保存されました。";
		mes "ご利用ありがとうございます。";
		close;
	case 2:
		if(Zeny < 50) {
			mes "[グラハム]";
			mes "お金が足りません。";
			close;
		}
		mes "[グラハム]";
		mes "倉庫を開きます。";
		set Zeny,Zeny-50;
		openstorage;
		close;
	case 3:
		mes "[グラハム]";
		mes "傷の治療には";
		mes "^0000ff5000 Zeny^000000かかりますが";
		mes "よろしいですか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[グラハム]";
			mes "ご利用ありがとうございました。";
			mes "またのお越しを";
			mes "お待ちしております。";
			close;
		}
		if(Zeny < 5000) {
			mes "[グラハム]";
			mes "お金が足りません。";
			close;
		}
		npcskillsupport 28,9999;
		percentheal 100,100;
		set Zeny,Zeny -5000;
		mes "[グラハム]";
		mes "傷の治療が完了しました。";
		mes "またのお越しを";
		mes "お待ちしております。";
		close;
	case 4:
		if(EP16_1QUE < 18) {
			mes "[グラハム]";
			mes "転送サービスには宮廷マジシャンを";
			mes "呼び出す権利が必要です。";
			mes "権利を獲得しましたら";
			mes "再度お声かけください。";
			close;
		}
		mes "[グラハム]";
		mes "宮廷マジシャン、ニルレム様を";
		mes "お呼びするので、";
		mes "少々お待ちください。";
		next;
		cloakoffnpc "マジシャン・ニルレム#ep16_wiz02";
		mes "[ニルレム]";
		mes "天才！　宮廷マジシャン";
		mes "ニルレム参上！";
		mes "お呼び出しありがとうございます。";
		mes "そんなにも私に会いたかったんですね！";
		mes "　";
		mes "さあ、それではどこへ行きますか？";
		next;
		setarray '@menu$,"時の通路","[MD] 空中要塞","[MD] 過去の儀式の間","侵攻されたプロンテラ","侵攻されたプロンテラ(避難地)","プロンテラ地下監獄","[デイリー] タマリンとお皿","[デイリー] アグネスのドレス","立ち去る";
		if(EP16_7QUE < 22)
			set '@menu$[6],"^888888[デイリー] タマリンとお皿^000000";
		if(EP16_6QUE < 14)
			set '@menu$[7],"^888888[デイリー] アグネスのドレス^000000";
		set '@i,select(printarray('@menu$)) - 1;
		switch('@i) {
		case 0:
			set '@map$,"dali.gat";
			set '@x,109;
			set '@y,86;
			break;
		case 1:
			set '@map$,"prt_q.gat";
			set '@x,250;
			set '@y,67;
			break;
		case 2:
			set '@map$,"prt_lib_q.gat";
			set '@x,89;
			set '@y,80;
			break;
		case 3:
			set '@map$,"prt_q_jp.gat";
			set '@x,153;
			set '@y,324;
			break;
		case 4:
			set '@map$,"prt_q.gat";
			set '@x,156;
			set '@y,328;
			break;
		case 5:
			set '@map$,"prt_pri00.gat";
			set '@x,51;
			set '@y,120;
			break;
		case 6:
			if(EP16_7QUE < 22) {
				mes "[ニルレム]";
				mes "偉大なマジシャンの私でも";
				mes "^0000ff依頼を受ける資格がない^000000所には";
				mes "案内してあげられません……。";
				close2;
				cloakonnpc "マジシャン・ニルレム#ep16_wiz02";
				end;
			}
			set '@map$,"prt_cas_q.gat";
			set '@x,302;
			set '@y,202;
			break;
		case 7:
			if(EP16_6QUE < 14) {
				mes "[ニルレム]";
				mes "偉大なマジシャンの私でも";
				mes "^0000ff依頼を受ける資格がない^000000所には";
				mes "案内してあげられません……。";
				close2;
				cloakonnpc "マジシャン・ニルレム#ep16_wiz02";
				end;
			}
			set '@map$,"prt_cas_q.gat";
			set '@x,79;
			set '@y,189;
			break;
		default:
			mes "[グラハム]";
			mes "ご利用ありがとうございました。";
			mes "またのお越しを";
			mes "お待ちしております。";
			close2;
			cloakonnpc "マジシャン・ニルレム#ep16_wiz02";
			end;
		}
		mes "[ニルレム]";
		mes "それじゃ目を瞑って～";
		mes "はい！";
		close2;
		cloakonnpc "マジシャン・ニルレム#ep16_wiz02";
		warp '@map$,'@x,'@y;
		end;
	case 5:
		mes "[グラハム]";
		mes "お客様、大変申し訳ございませんが、";
		mes "カートサービスは、商人と";
		mes "その上位職及びスーパーノービス";
		mes "専用のサービスとなっております。";
		close;
	case 6:
		mes "[グラハム]";
		mes "ご利用ありがとうございました。";
		mes "またのお越しを";
		mes "お待ちしております。";
		close;
	}
}

prt_lib_q.gat,110,58,4	script	文書#EP161DBOOK	844,{
	mes "‐内容の半分以上が";
	mes "　黒く塗りつぶされた文書がある‐";
	next;
	if(select("読む","読まない")==2) {
		mes "‐読むのをやめた‐";
		close;
	}
	mes "‐被害者供述調書";
	mes "　加害者：■■■(囚人番号: 243AD265)";
	mes "　上記のモンスターによる";
	mes "　^2EA4FF贈収賄、";
	mes "　横領、暴力^000000事件に関して";
	mes "　■■■■■日‐";
	next;
	mes "‐王室クルセイダー執務室にて";
	mes "　パラディン■■■は、";
	mes "　クルセイダー■■■を";
	mes "　呼び出し、被害者に";
	mes "　陳述拒否権があることを説明後、";
	mes "　被害者を審問した所、";
	mes "　下記のように陳述した‐";
	next;
	mes "‐幾つかの言葉以外は";
	mes "　すべて黒く塗られていて";
	mes "　読むことが出来ない‐";
	next;
	if(select("続けて読む","読まない")==2) {
		mes "‐読むのをやめた‐";
		close;
	}
	mes "‐被害者供述調書";
	mes "　加害者: ■■■";
	mes "　(囚人番号: 267BD184)";
	mes "　上記のモンスターによる";
	mes "　^2EA4FF結婚詐欺^000000事件に関して";
	mes "　■■■■■日、";
	mes "　王室クルセイダー執務室にて‐";
	next;
	mes "‐パラディン■■■は、";
	mes "　クルセイダー■■■を呼び出し、";
	mes "　陳述拒否権があることを";
	mes "　説明後、被害者を";
	mes "　審問した所、";
	mes "　下記のように陳述した‐";
	next;
	mes "‐幾つかの言葉以外は";
	mes "　すべて黒く塗られていて";
	mes "　読むことが出来ない‐";
	next;
	if(select("続けて読む","読まない")==2) {
		mes "‐読むのをやめた‐";
		close;
	}
	mes "‐被害者供述調書";
	mes "　加害者: ■■■";
	mes "　(囚人番号: 265CM154)";
	mes "　上記モンスターによる";
	mes "　^2EA4FF詐欺罪^000000 被害事件に関して‐";
	mes "■■■■■日‐";
	next;
	mes "‐王室クルセイダー執務室にて";
	mes "　パラディン■■■は、";
	mes "　クルセイダー■■■を";
	mes "　呼び出して";
	mes "　陳述拒否権があることを知らせた後、";
	mes "　被害者を審問した所、";
	mes "　下記のように陳述した‐";
	next;
	mes "‐幾つかの言葉以外は";
	mes "　すべて黒く塗られていて";
	mes "　読むことが出来ない‐";
	next;
	if(select("続けて読む","読まない")==2) {
		mes "‐読むのをやめた‐";
		close;
	}
	mes "‐被害者供述調書";
	mes "　加害者: ■■■";
	mes "　(囚人番号: 243DV17)";
	mes "　上記モンスターによる";
	mes "　^2EA4FF自由に対する罪^000000事件に関して";
	mes "　■■■■■日‐";
	next;
	mes "‐王室クルセイダー執務室にて";
	mes "　パラディン■■■は、";
	mes "　クルセイダー■■■を";
	mes "　呼び出して";
	mes "　陳述拒否権があることを知らせた後、";
	mes "　被害者を審問した所、";
	mes "　下記のように陳述した‐";
	next;
	mes "‐幾つかの言葉以外は";
	mes "　すべて黒く塗られていて";
	mes "　読むことが出来ない‐";
	next;
	if(select("続けて読む","読まない")==2) {
		mes "‐読むのをやめた‐";
		close;
	}
	mes "‐被害者供述調書";
	mes "　加害者: ■■■";
	mes "　(囚人番号: 95EB72)";
	mes "　上記モンスターによる";
	mes "　^2EA4FF器物破損、街侵攻^000000事件に関して";
	mes "　■■■■■日‐";
	next;
	mes "‐王室クルセイダー執務室にて";
	mes "　パラディン■■■は、";
	mes "　クルセイダー■■■を";
	mes "　呼び出して";
	mes "　陳述拒否権があることを知らせた後、";
	mes "　被害者を審問した所、";
	mes "　下記のように陳述した‐";
	next;
	mes "‐幾つかの言葉以外は";
	mes "　すべて黒く塗られていて";
	mes "　読むことが出来ない‐";
	next;
	if(select("続けて読む","読まない")==2) {
		mes "‐読むのをやめた‐";
		close;
	}
	mes "‐被害者供述調書";
	mes "　加害者: ■■■";
	mes "　(囚人番号: 117FM188)";
	mes "　上記モンスターによる";
	mes "　^2EA4FFヒステリー爆発^000000事件に関して";
	mes "　■■■■■日‐";
	next;
	mes "‐王室クルセイダー執務室にて";
	mes "　パラディン■■■は、";
	mes "　クルセイダー■■■を";
	mes "　呼び出して";
	mes "　陳述拒否権があることを知らせた後、";
	mes "　被害者を審問した所、";
	mes "　下記のように陳述した‐";
	next;
	mes "‐幾つかの言葉以外は";
	mes "　すべて黒く塗られていて";
	mes "　読むことが出来ない‐";
	next;
	if(select("続けて読む","読まない")==2) {
		mes "‐読むのをやめた‐";
		close;
	}
	mes "‐被害者供述調書";
	mes "　加害者: ■■■";
	mes "　(囚人番号: 103GD214)";
	mes "　上記モンスターによる";
	mes "　^2EA4FF器物破損、街侵攻^000000事件に関して";
	mes "　■■■■■日‐";
	next;
	mes "‐王室クルセイダー執務室にて";
	mes "　パラディン■■■は、";
	mes "　クルセイダー■■■を";
	mes "　呼び出して";
	mes "　陳述拒否権があることを知らせた後、";
	mes "　被害者を審問した所、";
	mes "　下記のように陳述した‐";
	next;
	mes "‐幾つかの言葉以外は";
	mes "　すべて黒く塗られていて";
	mes "　読むことが出来ない‐";
	next;
	if(select("続けて読む","読まない")==2) {
		mes "‐読むのをやめた‐";
		close;
	}
	mes "‐被害者供述調書";
	mes "　加害者: ■■■";
	mes "　(囚人番号: 55HK115)";
	mes "　上記モンスターによる";
	mes "　^2EA4FF経歴偽造、詐欺^000000事件に関して";
	mes "　■■■■■日‐";
	next;
	mes "‐王室クルセイダー執務室にて";
	mes "　パラディン■■■は、";
	mes "　クルセイダー■■■を";
	mes "　呼び出して";
	mes "　陳述拒否権を知らせた後、";
	mes "　被害者を審問した所、";
	mes "　下記のように陳述した‐";
	next;
	mes "‐幾つかの言葉以外は";
	mes "　すべて黒く塗られていて";
	mes "　読むことが出来ない‐";
	next;
	if(select("続けて読む","読まない")==2) {
		mes "‐読むのをやめた‐";
		close;
	}
	mes "‐これ以上はない‐";
	close;
}

prt_lib_q.gat,88,54,0	script	#effect1	139,4,4,{
OnTouch:
	if(EP16_1QUE < 20) {
		misceffect 522,"";
		soundeffect "rsx_0806_die.wav",0,0;
		unittalk getcharid(3),strcharinfo(0)+" : うわっ！",1;
	}
	end;
}

prt_lib_q.gat,88,74,0	script	#effect2	139,4,4,{
OnTouch:
	if(EP16_1QUE < 20) {
		misceffect 522,"";
		soundeffect "rsx_0806_die.wav",0,0;
		unittalk getcharid(3),strcharinfo(0)+" : 揺れている!!",1;
	}
	end;
}

prt_lib_q.gat,91,85,3	script	マジシャン・ニルレム#ep16_lib_q	735,{
	switch(EP16_1QUE) {
	case 19:
		mes "[ニルレム]";
		mes "準備は出来ましたか？";
		mes "準備が出来たら";
		mes "揺れる空間に触れてくださいね。";
		close;
	case 20:
		mes "[ニルレム]";
		mes "危ないところでしたね！";
		mes "ヒヤヒヤしましたよ！";
		mes "ユミルの心臓はあいつらが";
		mes "盗んでいたようですね。";
		mes "ところであいつは";
		mes "誰だったんですか？";
		next;
		menu "それよりプロンテラが襲撃されているらしい!!",-;
		mes "[ニルレム]";
		mes "プロンテラが襲撃？";
		mes "そんな馬鹿な。";
		mes "そんな歴史は";
		mes "聞いたことがありませんよ～。";
		next;
		menu "空中要塞、アンデッド軍団が!!",-;
		mes "[ニルレム]";
		mes "空中要塞、アンデッド軍団……？";
		mes "またまたそんなことを。";
		mes "……";
		next;
		mes "[ニルレム]";
		mes "でも、まってください。";
		mes "ユミルの心臓を狙っていたのは";
		mes "まさにアンデッド軍団。";
		mes "まさか、本当に…!?";
		mes "　";
		mes "‐ニルレムの顔が青ざめる‐";
		next;
		mes "‐過去のプロンテラが";
		mes "　襲撃を受けている!!‐";
		musiceffect "166";
		next;
		menu "行ってみよう!!",-;
		mes "[ニルレム]";
		mes "やっぱり！";
		mes "そう言うと思ってました！";
		mes "早く行きましょう！";
		mes "南西の方角から外に出られるはずです。";
		delquest 7701;
		setquest 7702;
		set EP16_1QUE,21;
		close;
	case 21:
	case 22:
	case 23:
		mes "[ニルレム]";
		mes "早く外に出てみましょう！";
		mes "南西の方角から外に出られるはずです。";
		close;
	case 24:
		if(checkquest(7705) && checkquest(7705) & 0x4) {
			mes "[ニルレム]";
			mes "はい！　フリードリヒ様から";
			mes "お預かりした報酬です！";
			mes "お仕事お疲れ様でした！";
			next;
			if(checkitemblank() < 1) {
				mes "‐荷物をこれ以上持てません";
				mes "　荷物に1個以上の空きを";
				mes "　作ってください‐";
				close;
			}
			delquest 7705;
			getitem 6919,10;
			mes "[ニルレム]";
			mes "私も少し頑張り過ぎたかも";
			mes "しれません。";
			mes "本当に大変でした……。";
			close;
		}
		mes "[ニルレム]";
		mes "ふふふ、私はだんだん";
		mes "ここが好きになり始めています。";
		mes "私に何かご用ですか？";
		next;
		if(select("儀式の部屋に繋ぐ","帰還")==2) {
			mes "[ニルレム]";
			mes "願いを叶えましょう！";
			close2;
			warp "prt_lib.gat",89,43;
			end;
		}
		if(checkquest(7706)) {
			if(checkquest(7706) & 0x2) {
				delquest 7706;
			} else {
				mes "[ニルレム]";
				mes "それはちょっと無理です。";
				mes "私がいくら天才マジシャンと言えど";
				mes "私も人間なんで限界……";
				next;
				mes "[ニルレム]";
				mes "多重次元の接続というのは";
				mes "とても難しい事なのです。";
				mes "申し訳ありません。";
				next;
				mes "[ニルレム]";
				mes "周辺で暴走している魔力が";
				mes "ある程度安定したら";
				mes "その時やって差し上げますね。";
				close;
			}
		}
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[ニルレム]";
			mes "あれ？　あなたこのパーティーの";
			mes "リーダーじゃないですね？";
			mes "パーティーリーダーに";
			mes "代わってもらえますか？";
			close;
		}
		mes "[ニルレム]";
		mes "それじゃ儀式の部屋で";
		mes "いったい何が起きていたのか";
		mes "見に行きましょう！";
		next;
		mes "[ニルレム]";
		mes "一度ねじった時空間を";
		mes "再度強制的に繋げるので";
		mes "私はこれを維持する事に";
		mes "集中しなければいけません！";
		next;
		mes "[ニルレム]";
		mes "私は一緒にはいけませんが";
		mes "必ず生きて帰って来て下さい。";
		next;
		if(select("今すぐ繋げてもらう","行かない")==2) {
			mes "[ニルレム]";
			mes "ははは……";
			mes "あまり遅れないでくださいね。";
			close;
		}
		mes "[ニルレム]";
		mes "次の地域に行けるゲートが";
		mes "活性化されました！";
		mes "さあ、入場して下さい！";
		close2;
		mdcreate "ritual_room";
		end;
	}
}

prt_lib_q.gat,88,90,1	script	揺れる空間#evt_gate02	10042,{
	if(checkquest(7706)) {
		mes "[ニルレム]";
		mes "それはちょっと無理です。";
		mes "私がいくら天才マジシャンと言えど";
		mes "私も人間なんで限界……";
		next;
		mes "[ニルレム]";
		mes "多重次元の接続というのは";
		mes "とても難しい事なのです。";
		mes "申し訳ありません。";
		next;
		mes "[ニルレム]";
		mes "周辺で暴走している魔力が";
		mes "ある程度安定したら";
		mes "その時やって差し上げますね。";
		close;
	}
	if(EP16_1QUE == 19) {
		mes "‐過去のユミルの心臓がある";
		mes "　継承の儀式の場所へ移動が可能です‐";
		next;
		if(select("入る","やめる")==2) {
			mes "‐今はやめておこう‐";
			close;
		}
		mes "‐先に進んだ‐";
		close2;
		warp "mir_q.gat",101,10;
		end;
	}
	if(EP16_1QUE >= 24) {
		mes "‐かつてユミルの心臓があった";
		mes "　過去の儀式の間へ移動が可能です‐";
		next;
		if(select("入る","やめる")==2) {
			mes "[ニルレム]";
			mes "これはただ空間を引き裂き";
			mes "強制的に繋げたものにすぎません。";
			mes "それも私が天才マジシャンだから";
			mes "可能なことなんですよ！";
			close;
		}
		if(getonlinepartymember() < 1) {
			mes "‐^4d4dffこのイベントは";
			mes "　メモリアルダンジョンで進行します。";
			mes "　パーティーを結成した後、";
			mes "　もう一度試して下さい‐^000000";
			close;
		}
		switch(mdenter("ritual_room")) {
		case 0:	// エラーなし
			announce "メモリアルダンジョン[ritual_room] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99;
			setquest 7705;
			setquest 7706;
			donpcevent getmdnpcname("Mir_Contorl")+"::OnStart";
			close;
		case 1:	// パーティー未加入
			mes "‐メモリアルダンジョンを";
			mes "　生成したパーティーのメンバーのみ、";
			mes "　メモリアルダンジョンに入れます‐";
			close;
		case 2:	// ダンジョン未作成
			mes "[ニルレム]";
			mes "やっぱり強制的に繋ぐのは";
			mes "無理なのかな？";
			mes "少し待って下さい。";
			close;
		default:	// その他エラー
			close;
		}
	}
	mes "‐空間が揺らいでいる‐";
	close;
}

mir_q.gat,101,90,3	script	ビジョウ#01	10143,{
	if(EP16_1QUE == 19) {
		cutin "bijou_01.bmp",2;
		mes "[ビジョウ]";
		mes "人間か……";
		mes "結界を張ったから";
		mes "外からは入れないはずだが……";
		mes "どうやって中に入ってきた？";
		mes "貴様もユミルの心臓が目的か？";
		next;
		mes "‐凄まじい悪意を感じる。";
		mes "　そして、恐ろしいほどの";
		mes "　魔力を感じる……";
		next;
		menu "誰？",-;
		mes "[ビジョウ]";
		mes "愚問。";
		mes "私が誰だと？";
		mes "^ff0000プロンテラがアンデッド軍団に";
		mes "^ff0000蹂躙、破壊^000000されているを";
		mes "見てこなかったのか？";
		next;
		menu "プロンテラがアンデッド軍団に襲撃!?",-;
		mes "[ビジョウ]";
		mes "私をからかっているのか？";
		mes "気付かないわけがないだろう。";
		mes "空に浮かぶ偉大な";
		mes "^0000ff空中要塞^000000に。";
		mes "^0000ff空中要塞によって";
		mes "^0000ffプロンテラはいまや壊滅目前だ。^000000";
		next;
		menu "空中要塞!?",-;
		mes "[ビジョウ]";
		mes "……";
		mes "お前は何か違うな。";
		mes "この世界の人間と違うようだ。";
		next;
		mes "[ビジョウ]";
		mes "……";
		mes "ユミルの心臓を手に入れてから";
		mes "お前を殺そうと思ったけど、";
		mes "気が変わった。";
		next;
		mes "‐ビジョウから";
		mes "　凄まじい殺意が放たれる‐";
		next;
		mes "[ビジョウ]";
		mes "今、お前を殺す。";
		next;
		mes "[ビジョウ]";
		mes "ヒメルメズ様の祝福を受けた";
		mes "不死の軍団よ！";
		mes "今、この冒険者を食らえ!!";
		next;
		menu "戦う！",-,"逃げよう！",-;
		mes "[ニルレム]";
		mes "うわわわ!!";
		next;
		mes "[ニルレム]";
		mes "これはやばいです!!";
		mes "逃げましょう!!";
		mes "撤退しましょう!!";
		mes "僕に話しかけてください!!";
		cutin "bijou_01.bmp",255;
		cloakoffnpc "マジシャン・ニルレム#01";
		close;
	}
}

mir_q.gat,105,80,3	script(CLOAKED)	マジシャン・ニルレム#01	735,{
	if(EP16_1QUE == 19) {
		mes "[ニルレム]";
		mes "これ以上ここに留まるのは危険です！";
		mes "本当に殺されてしまいますよ！";
		next;
		mes "[ニルレム]";
		mes "脱出しましょう！";
		close2;
		set EP16_1QUE,20;
		setquest 7701;
		delquest 7700;
		warp "prt_lib_q.gat",88,83;
		end;
	}
	cloakonnpc;
	end;
}
mir_q.gat,92,96,3	script	パワフルスケルトン#01	3446,{}
mir_q.gat,91,91,3	script	パワフルスケルトン#02	3446,{}
mir_q.gat,96,85,3	script	パワフルスケルトン#03	3446,{}
mir_q.gat,101,82,3	script	パワフルスケルトン#04	3446,{}
mir_q.gat,111,96,3	script	パワフルスケルトン#05	3446,{}
mir_q.gat,112,91,3	script	パワフルスケルトン#06	3446,{}
mir_q.gat,107,85,3	script	パワフルスケルトン#07	3446,{}

prt_q.gat,157,334,3	script	ニルレム#ep16_pprt01	735,{
	if(EP16_1QUE == 21) {
		mes "[ニルレム]";
		mes "あわわわ、";
		mes "本当にプロンテラが襲撃されている!!";
		mes "な、南西の方に、";
		mes "要塞が攻めてきてます!!";
		next;
		mes "[ニルレム]";
		mes "どうしますか？";
		mes "このまま調査しますか？";
		mes "きっと戦闘になりますよ。";
		mes "それとも、戻って報告しますか？";
		next;
		menu "ここから戻れる？",-;
		mes "[ニルレム]";
		mes "はい、任せてください！";
		mes "時間移動は得意です。";
		mes "エクラージュに留学もしたんです。";
		next;
		mes "[ニルレム]";
		mes "それと猫の手職員からも";
		mes "あらゆることも習いました。";
		mes "少なくても次元の狭間に関して";
		mes "人間の中では一番詳しいと";
		mes "自負しています！";
		next;
		mes "[ニルレム]";
		mes "次元の狭間上にある場所なら";
		mes "元の場所に戻るくらいは簡単です。";
		next;
		mes "[ニルレム]";
		mes "私たちはこの時間に属している";
		mes "存在ではないですから、";
		mes "入って来るよりは出て行く方が";
		mes "百万倍簡単です。";
		next;
		mes "[ニルレム]";
		mes "それでどうします？";
		next;
		menu "状況整理だ！",-;
		mes "[ニルレム]";
		mes "わかりました。";
		mes "私たちの状況を";
		mes "ちょっと整理しましょう。";
		next;
		mes "[ニルレム]";
		mes "儀式の間にあった秘宝は、";
		mes "^4d4dffプロンテラを襲撃したアンデッド軍団^000000の";
		mes "一味に^4d4dff奪取 ^000000された。";
		mes "合っていますか？";
		next;
		menu "合っている",-;
		mes "[ニルレム]";
		mes "しかも恐ろしい強さのようです。";
		mes "異世界でもあんな禍々しい";
		mes "魔力を持つ者は見たことは";
		mes "なかったです！";
		next;
		mes "[ニルレム]";
		mes "そういえば、";
		mes "ヒメルメズ様とか言ってましたね！";
		mes "彼女の名前は知っています！";
		next;
		mes "[ニルレム]";
		mes "たしか、はるか昔、";
		mes "グラストヘイム城を襲って";
		mes "廃墟にしたという";
		mes "古の12ヴァルキリーの一人です！";
		next;
		mes "[ニルレム]";
		mes "もう何が何だか！";
		mes "理解がおいつきません！";
		next;
		mes "[ニルレム]";
		mes "さらにいえば";
		mes "プロンテラがこんな大襲撃を";
		mes "受けたのに歴史に";
		mes "残されていないなんて。";
		next;
		menu "意図的に隠されたようだ",-;
		mes "[ニルレム]";
		mes "そうですね。";
		mes "秘宝が盗まれたのを隠すため？";
		mes "それとも他の理由？";
		mes "想像すらできません。";
		next;
		mes "[ニルレム]";
		mes "……「^4d4dff真実を知る者^000000」。";
		mes "王家の記憶の間で見た";
		mes "文書の封印された部分にあった……";
		next;
		menu "「真実を知る者」がどうしたの？",-;
		mes "[ニルレム]";
		mes "封印された歴史を知る者、";
		mes "それこそが「真実を知る者」。";
		mes "それは";
		mes strcharinfo(0)+"様";
		mes "ですよ！";
		next;
		mes "[ニルレム]";
		mes "秘宝は守る事も奪う事も";
		mes "出来なかったけど";
		mes "少なくとも真実を知ることが";
		mes "できました。";
		next;
		mes "[ニルレム]";
		mes "これから王家と過去の秘密が明かされ、";
		mes "欠けていたパズルが";
		mes "埋まっていくことになるでしょう。";
		next;
		mes "[ニルレム]";
		mes "ふふふ……";
		mes "その中心には";
		mes strcharinfo(0)+"様が";
		mes "立つ事になりますよ。";
		setquest 7703;
		delquest 7702;
		set EP16_1QUE,22;
		next;
		mes "[ニルレム]";
		mes "これからどうします？";
		mes "元の時間に戻りますか？";
		mes "それとも、ここを調査しますか？";
		next;
		if(select("戻る","調査する")==2) {
			mes "[ニルレム]";
			mes "わかりました。";
			mes "戻りたくなったら";
			mes "話しかけてください。";
			close;
		}
		mes "[ニルレム]";
		mes "それでは戻りましょうか。";
		mes "私たちの任務は";
		mes "ここで一段落ですね！";
		next;
		mes "[ニルレム]";
		mes "では行きましょう。";
		mes "元々私たちの時間でもない場所に";
		mes "長くいても良い事なんか";
		mes "ひとつもありません。";
		next;
		mes "[ニルレム]";
		mes "それでは行きますよ。";
		mes "３……";
		if(!sleep2(2000)) end;
		mes "２……";
		if(!sleep2(1000)) end;
		mes "１！";
		close2;
		warp "prt_lib.gat",88,80;
		end;
	}
	mes "[ニルレム]";
	mes "ははは！";
	mes "ここはいつ来ても本当に";
	mes "……嫌ですね。";
	next;
	if(select("元の時代に戻ろう","見回って来る")==2) {
		mes "[ニルレム]";
		mes "いってらっしゃい！";
		close;
	}
	mes "[ニルレム]";
	mes "そうしましょう！";
	next;
	mes "[ニルレム]";
	mes "それでは行きますよ。";
	close2;
	warp "prt_lib.gat",89,43;
	end;
}

//============================================================
// 侵略されたプロンテラNPC
//------------------------------------------------------------
prt_q.gat,156,324,6	script	警備隊長シュピーゲル#01	10134,{
	if(!(checkquest(5448) & 0x8)) {
		mes "[警備隊長シュピーゲル]";
		mes "そこ！";
		mes "間隔が開いているぞ！";
		mes "ちゃんと整列するんだ！";
		next;
		mes "[警備隊長シュピーゲル]";
		mes "負傷したものは後方にさがれ！";
		mes "軽傷の者は治療が終わり次第";
		mes "持ち場へ戻るんだ！";
		next;
		mes "[警備隊長シュピーゲル]";
		mes "うん？";
		mes "冒険者がなぜこんなところに？";
		mes "危険だから早く建物の中に";
		mes "入りなさい！";
		next;
		menu "話を聞く",-;
		mes "[警備隊長シュピーゲル]";
		mes "今、街はアンデッドの";
		mes "侵攻を受けています。";
		mes "奴らは街の南東に着陸した";
		mes "巨大な要塞の中から";
		mes "次々と押し寄せているのです。";
		next;
		mes "[警備隊長シュピーゲル]";
		mes "我々は街を守りながら";
		mes "増え続けるアンデッドの";
		mes "元となる要塞内にも";
		mes "兵を派遣していますが……";
		mes "今のところ奴らの勢いが";
		mes "衰える様子はありません。";
		next;
		menu "協力を申し出る",-;
		if(BaseLevel < 100) {
			mes "[警備隊長シュピーゲル]";
			mes "申し出はありがたいのですが、";
			mes "敵の力は強力です。";
			mes "少なくとも";
			mes "^ff0000BaseLv100以上^000000でないと";
			mes "太刀打ちできないでしょう。";
			close;
		}
		mes "[警備隊長シュピーゲル]";
		mes "そうですか。";
		mes "今は少しでも多くの戦力がほしい。";
		mes "是非とも貴方の申し出を";
		mes "受けさせてもらいましょう。";
		mes "貴方の勇気に感謝します。";
		setquest 5448;
		compquest 5448;
	} else {
		mes "[警備隊長シュピーゲル]";
		mes "よく来てくれました。";
		mes "奴らは依然として";
		mes "街中に溢れ返っています。";
	}
	next;
	switch(select("街のアンデッドを殲滅する","巨大要塞に乗り込む","準備をしなおす")) {
	case 1:
		mes "[警備隊長シュピーゲル]";
		mes "では貴方は街を徘徊する";
		mes "アンデッドの殲滅に";
		mes "努めてください。";
		mes "冒険者の貴方は組織的な防御より";
		mes "遊撃に徹した方が良いでしょう。";
		next;
		if(select("出発する","準備をしなおす")==2) {
			mes "[警備隊長シュピーゲル]";
			mes "奴らは非常に危険です。";
			mes "万全の準備を整えてから";
			mes "挑んでください。";
			close;
		}
		mes "[警備隊長シュピーゲル]";
		mes "くれぐれも気をつけて。";
		mes "生き残ることを";
		mes "最優先に考えてください。";
		close2;
		warp "prt_q_jp.gat",153,324;
		end;
	case 2:
		mes "[警備隊長シュピーゲル]";
		mes "要塞は街の南東に着陸しています。";
		mes "近くに待機している兵士が";
		mes "要塞への侵入経路を";
		mes "案内してくれるでしょう。";
		mes "増え続けるアンデッドの大元を";
		mes "叩いてください。";
		next;
		mes "[警備隊長シュピーゲル]";
		mes "よければ要塞付近まで";
		mes "兵士に送らせますが、";
		mes "どうしますか？";
		next;
		if(select("送ってもらう","自分で歩いて行く")==2) {
			mes "[警備隊長シュピーゲル]";
			mes "そうですか。";
			mes "道中のアンデッドには";
			mes "注意してください。";
			viewpoint 1,259,57,1,0xFF0000;
			close;
		}
		mes "[警備隊長シュピーゲル]";
		mes "くれぐれも気をつけて。";
		mes "生き残ることを";
		mes "最優先に考えてください。";
		close2;
		warp "prt_q.gat",249,64;
		end;
	case 3:
		mes "[警備隊長シュピーゲル]";
		mes "奴らは非常に危険です。";
		mes "万全の準備を整えてから";
		mes "挑んでください。";
		close;
	}
}

prt_q.gat,165,326,6	script	兵士#EP162PS01	105,{
	emotion 6;
	mes "[兵士]";
	mes "くそっ……アンデッドどもめ！";
	close;
}

prt_q.gat,167,324,6	script	兵士#EP162PS02	105,{
	emotion 28;
	mes "[兵士]";
	mes "つい今まで一緒に戦ってた仲間が……！";
	mes "ううっ……";
	close;
}

prt_q.gat,165,322,6	script	兵士#EP162PS03	105,{
	mes "[兵士]";
	mes "お願いですから";
	mes "無理はしないでください。";
	close;
}

prt_q.gat,167,320,6	script	兵士#EP162PS04	105,{
	emotion 53;
	mes "[兵士]";
	mes "落ちて来た物は";
	mes "一体なんだったのでしょう？";
	mes "アンデッドと";
	mes "関係があるのでしょうか？";
	close;
}

prt_q.gat,165,318,6	script	兵士#EP162PS05	105,{
	emotion 36;
	mes "[兵士]";
	mes "ここは死守します！";
	close;
}

prt_q.gat,146,326,2	script	兵士#EP162PS06	105,{
	emotion 57;
	mes "[兵士]";
	mes "倒しても倒しても";
	mes "きりが無いなんて……。";
	close;
}

prt_q.gat,144,324,2	script	兵士#EP162PS07	105,{
	mes "[兵士]";
	mes "不死の兵は強いですね。";
	mes "気をつけてください。";
	close;
}

prt_q.gat,146,322,2	script	兵士#EP162PS08	105,{
	emotion 19;
	mes "[兵士]";
	mes "ああ、アンデッドどもめ……！";
	close;
}

prt_q.gat,144,320,2	script	兵士#EP162PS09	105,{
	mes "[兵士]";
	mes "変な科学者が";
	mes "空から落ちて来た物体を";
	mes "研究するために";
	mes "兵士を募っていましたが、";
	mes "音沙汰がないですね……。";
	close;
}

prt_q.gat,146,318,2	script	兵士#EP162PS10	105,{
	mes "[兵士]";
	mes "博士は大丈夫でしょうか。";
	mes "変人なだけに";
	mes "誰も止められませんでしたが。";
	close;
}

prt_q.gat,149,316,4	script	兵士#EP162PS11	105,{
	emotion 11;
	mes "[兵士]";
	mes "プロンテラは我々が守ります！";
	close;
}

prt_q.gat,151,314,4	script	兵士#EP162PS12	105,{
	emotion 54;
	mes "[兵士]";
	mes "家族が無事か心配です。";
	close;
}

prt_q.gat,153,316,4	script	兵士#EP162PS13	105,{
	emotion 55;
	mes "[兵士]";
	mes "どうやらここには";
	mes "アンデッドがあまり来てないようです。";
	close;
}

prt_q.gat,158,316,4	script	兵士#EP162PS14	105,{
	mes "[兵士]";
	mes "私の仲間が博士についていきました。";
	mes "心配です。";
	mes "無茶をしてなきゃいいのですが……。";
	close;
}

prt_q.gat,160,314,4	script	兵士#EP162PS15	105,{
	emotion 54;
	mes "[兵士]";
	mes "わははは！";
	mes "本当なら今日が初デートだったのに！";
	mes "はははは！";
	close;
}

prt_q.gat,162,316,4	script	兵士#EP162PS16	105,{
	emotion 19;
	mes "[兵士]";
	mes "うおおお！　全部かかって来い！";
	close;
}

prt_q.gat,160,327,5	script	負傷兵#EP161PS17	105,{
	emotion 36;
	mes "[兵士]";
	mes "くそ……まだ戦える！";
	close;
}

prt_q.gat,159,328,6	script	衛生兵#EP162PS18	641,{
	misceffect 320,"負傷兵#EP161PS17";
	mes "[兵士]";
	mes "まだ治療が終わってません！";
	close;
}

-	script	死亡した住民#base	-1,{
	mes "‐既に息絶えている‐";
	close;
OnTouch:
	set '@dummy,getmapxy('@map$,'@x,'@y,1);
	if(strnpcinfo(2) == "EP161DIE06")
		set '@message$,"カエリ……タイ……";
	else if(strnpcinfo(2) == "EP161DIE07")
		set '@message$,"ヒメルメズ……タメニ……";
	else if(strnpcinfo(2) == "EP161DIE08")
		set '@message$,"ニクイ……ニクイ……";
	else if(strnpcinfo(2) == "EP161DIE09")
		set '@message$,"グォォォ！";
	else if(strnpcinfo(2) == "EP161DIE10")
		set '@message$,"デートモ……デキズニ……";
	else if(strnpcinfo(2) == "EP161DIE11")
		set '@message$,"カエリタイ……";
	else if(strnpcinfo(2) == "EP161DIE12")
		set '@message$,"ダイジョウブダ……";
	else if(strnpcinfo(2) == "EP161DIE13")
		set '@message$,"モウスグ……ムスメガ……";
	else if(strnpcinfo(2) == "EP161DIE14")
		set '@message$,"ワタシノイヌガ……";
	else if(strnpcinfo(2) == "EP161DIE15")
		set '@message$,"サイゴニ……タベタカッタ……";
	else if(strnpcinfo(2) == "EP161DIE16")
		set '@message$,"コウウンノオマモリガ……";
	else if(strnpcinfo(2) == "EP161DIE17")
		set '@message$,"ハハハハハハ……";
	else if(strnpcinfo(2) == "EP161DIE18")
		set '@message$,"ニンゲ……ォイシ……？";
	else if(strnpcinfo(2) == "EP161DIE19")
		set '@message$,"タ……タスケテ……";
	else if(strnpcinfo(2) == "EP161DIE20")
		set '@message$,"ツカレタ……";
	else
		set '@message$,"グオォォォ……";
	unittalk "死亡した住民 : "+ '@message$,1;
	unittalk getcharid(3),strcharinfo(0)+" : ?",1;
	if(!sleep2(1000)) end;
	initnpctimer;
	misceffect 772;
	monster '@map$,'@x,'@y,"ゾンビ",1015,1;
	monster '@map$,'@x,'@y,"アクラウス",1194,1;
	monster '@map$,'@x,'@y,"ハンターフライ",1035,1;
	hideonnpc;
	end;
OnTimer300000:
	hideoffnpc;
	end;
}

prt_q.gat,213,90,2	duplicate(死亡した住民#base)	死亡した住民#EP161DIE01	457,2,2
prt_q.gat,214,85,6	duplicate(死亡した住民#base)	死亡した住民#EP161DIE02	887,2,2
prt_q.gat,222,87,8	duplicate(死亡した住民#base)	死亡した住民#EP161DIE03	849,2,2
prt_q.gat,149,188,2	duplicate(死亡した住民#base)	死亡した住民#EP161DIE04	887,2,2
prt_q.gat,188,207,6	duplicate(死亡した住民#base)	死亡した住民#EP161DIE05	849,2,2
prt_q.gat,109,94,8	duplicate(死亡した住民#base)	死亡した住民#EP161DIE06	457,2,2
prt_q.gat,88,279,2	duplicate(死亡した住民#base)	死亡した住民#EP161DIE07	887,2,2
prt_q.gat,89,207,6	duplicate(死亡した住民#base)	死亡した住民#EP161DIE08	849,2,2
prt_q.gat,265,300,8	duplicate(死亡した住民#base)	死亡した住民#EP161DIE09	457,2,2
prt_q.gat,88,350,2	duplicate(死亡した住民#base)	死亡した住民#EP161DIE10	887,2,2
prt_q.gat,156,275,6	duplicate(死亡した住民#base)	死亡した住民#EP161DIE11	457,2,2
prt_q.gat,104,114,8	duplicate(死亡した住民#base)	死亡した住民#EP161DIE12	849,2,2
prt_q.gat,108,318,2	duplicate(死亡した住民#base)	死亡した住民#EP161DIE13	887,2,2
prt_q.gat,238,129,6	duplicate(死亡した住民#base)	死亡した住民#EP161DIE14	849,2,2
prt_q.gat,200,139,8	duplicate(死亡した住民#base)	死亡した住民#EP161DIE15	849,2,2
prt_q.gat,74,227,2	duplicate(死亡した住民#base)	死亡した住民#EP161DIE16	457,2,2
prt_q.gat,220,350,6	duplicate(死亡した住民#base)	死亡した住民#EP161DIE17	849,2,2
prt_q.gat,45,146,8	duplicate(死亡した住民#base)	死亡した住民#EP161DIE18	849,2,2
prt_q.gat,227,219,2	duplicate(死亡した住民#base)	死亡した住民#EP161DIE19	457,2,2
prt_q.gat,146,252,6	duplicate(死亡した住民#base)	死亡した住民#EP161DIE20	887,2,2

prt_q.gat,47,339,5	script	兵士#EP161ETC01	105,{
	emotion 19;
	mes "[兵士]";
	mes "ここは";
	mes "プロンテラ第2避難所の騎士団です。";
	close;
}

prt_q.gat,52,344,5	script	兵士#EP161ETC02	105,{
	emotion 19;
	mes "[兵士]";
	mes "ここは";
	mes "プロンテラ第2避難所の騎士団です。";
	close;
}

prt_q.gat,249,74,2	script	プロンテラ兵士#a2	105,{
	mes "[兵士]";
	mes "モンスターの侵攻は一時的に";
	mes "鎮静化しているようです。";
	next;
	mes "[兵士]";
	mes "私の家族、私の友達……。";
	mes "彼らを傍で守りたいけど、";
	mes "それよりもっと重要な事が";
	mes "ここにはあります。";
	next;
	mes "[兵士]";
	mes "倒しても倒しても、";
	mes "モンスターの進軍は止まらない。";
	mes "要塞という根源を封じなくては……。";
	close;

}

prt_q.gat,252,73,4	script	プロンテラ兵士#a3	105,{
	mes "[兵士]";
	mes "私が愛する人はみんな……";
	mes "……あいつらに……!!";
	next;
	mes "‐兵士はそう言うと";
	mes "　黙ってしまった‐";
	close;
}

prt_q.gat,235,63,2	script	プロンテラ兵士#a4	105,5,5,{
	end;
OnTouchNPC:
	unittalk "兵士 : ここは通さん！";
	misceffect 438;
	warp "prt_q.gat",-1,-1;
	end;
}

prt_q.gat,236,81,1	script	プロンテラ兵士#a5	105,10,10,{
	end;
OnTouchNPC:
	unittalk "兵士 : アンデッドめ！";
	misceffect 438;
	warp "prt_q.gat",-1,-1;
	end;
}

prt_q.gat,267,82,8	script	プロンテラ兵士#a6	105,5,5,{
	end;
OnTouchNPC:
	unittalk "兵士 : くらえ！";
	misceffect 438;
	warp "prt_q.gat",-1,-1;
	end;
}

prt_q.gat,256,71,0	script	プロンテラ兵士#ep16jp	105,{
	mes "[プロンテラ兵士]";
	mes "ご協力ありがとうございます。";
	mes "　";
	mes "シュピーゲル隊長の";
	mes "元まで戻られますか？";
	next;
	if(select("送ってもらう","やめる")==2) {
		mes "[プロンテラ兵士]";
		mes "そうですか。";
		mes "何かありましたら";
		mes "お声をお掛けください。";
		close;
	}
	mes "[プロンテラ兵士]";
	mes "承知いたしました。";
	mes "シュピーゲル隊長の元へ";
	mes "ご案内いたします。";
	close2;
	warp "prt_q.gat",156,328;
	end;
}

prt_q.gat,249,71,4	script	科学者サウス#a1	573,{
	mes "[科学者サウス]";
	mes "私はプロンテラで子供たちに";
	mes "科学を教えている者だ。";
	mes "個人的な研究もしている。";
	next;
	mes "[科学者サウス]";
	mes "日々平凡に暮らしてきたが……";
	mes "まさかプロンテラがこんな事態に";
	mes "陥る日がくるとは……。";
	close;
}

prt_q_jp.gat,156,324,6	script	警備隊長シュピーゲル#02	10134,{
	mes "[警備隊長シュピーゲル]";
	mes "おお、無事でしたか。";
	mes "少し休みますか？";
	next;
	if(select("少し休む","まだ続ける")==2) {
		mes "[警備隊長シュピーゲル]";
		mes "そうですか。";
		mes "くれぐれも無理は";
		mes "しないでください。";
		close;
	}
	mes "[警備隊長シュピーゲル]";
	mes "わかりました。";
	mes "ではこちらへ。";
	close2;
	warp "prt_q.gat",156,328;
	end;
}

//============================================================
// プロンテラ地下監獄NPC
//------------------------------------------------------------
prt_prison.gat,159,206,0	script	jump_A1		45,1,1,{
OnTouch:
	if(readparam(0) > 200)
		showmessage "移動速度を上げなければ、飛び越えられそうにない。","";
	else
		warp "prt_prison.gat",159,195;
	end;
}

prt_prison.gat,159,198,0	script	jump_A2		45,1,1,{
OnTouch:
	if(readparam(0) > 200)
		showmessage "移動速度を上げなければ、飛び越えられそうにない。","";
	else
		warp "prt_prison.gat",159,208;
	end;
}

prt_prison.gat,87,254,0		warp	secret_A1		1,1,prt_prison.gat,88,207
prt_prison.gat,85,202,0		script	jump_A_02		45,1,1,{
OnTouch:
	if(readparam(0) > 200)
		showmessage "移動速度を上げなければ、飛び越えられそうにない。","";
	else
		warp "prt_prison.gat",90,254;
	end;
}

prt_prison.gat,115,78,0		script	jump_B2	45,1,1,{
OnTouch:
	if(readparam(0) > 200)
		showmessage "移動速度を上げなければ、飛び越えられそうにない。","";
	else
		warp "prt_prison.gat",115,87;
	end;
}

prt_prison.gat,115,85,0		script	jump_B1	45,1,1,{
OnTouch:
	if(readparam(0) > 200)
		showmessage "移動速度を上げなければ、飛び越えられそうにない。","";
	else
		warp "prt_prison.gat",115,76;
	end;
}

prt_prison.gat,267,143,0	warp	secret_D1	1,1,prt_prison.gat,238,90
prt_prison.gat,248,90,0		warp	secret_D2	1,1,prt_prison.gat,265,143

prt_prison.gat,265,154,4	script	囚人 265CM154#EP161C	10135,{
	switch(rand(3)) {
	case 0:
		mes "[囚人 265CM154]";
		mes "人間さんは汚す醍醐味を";
		mes "知らないん？";
		mes "掃除するのと同じくらいに";
		mes "汚すのもかなり楽しいよ。";
		next;
		emotion 12;
		mes "[囚人 265CM154]";
		mes "今日のお掃除は";
		mes "お休み～お休み～♪";
		close;
	case 1:
		mes "[囚人 265CM154]";
		mes "あ～あ、";
		mes "汚い、汚い～！";
		mes "檻の外も";
		mes "お掃除しようよ～！";
		next;
		mes "[囚人 265CM154]";
		mes "代わりに誰か掃除してくれれば";
		mes "いいのに～";
		close;
	case 2:
		mes "[囚人 265CM154]";
		mes "さあ！　人間さん！";
		mes "監獄も汚れるだけ";
		mes "汚れてしまったから";
		mes "いよいよ掃除をする時に";
		mes "なったみたいだよ。";
		next;
		emotion 12;
		mes "[囚人 265CM154]";
		mes "今日も気持ちよく";
		mes "掃除～掃除～♪";
		mes "あちしは檻の中だけ～♪";
		close;
	}
}

prt_prison.gat,95,72,6	script	囚人 95EB72#EP161E	736,{
	switch(rand(2)) {
	case 0:
		emotion 43;
		mes "[囚人 95EB72]";
		mes "ぐうう、この臭いは……";
		mes "そう人間……";
		mes "人間の匂いだ。";
		next;
		emotion 29;
		mes "[囚人 95EB72]";
		mes "ククク、この暗い地下監獄で";
		mes "人間の匂いを嗅ぐのは";
		mes "どれほど久しいか。";
		mes "人間、近くまで来てみろ……";
		mes "安心しろ。久しぶりに見た";
		mes "人間だから、特別に殺しはしない。";
		next;
		if(select("近づく","近づかない") == 2) {
			unittalk "‐ビクビク‐",1;
			mes "[囚人 95EB72]";
			mes "くはははは……!!";
			mes "　";
			mes "‐檻の中の囚人は";
			mes "　すごくびくびくしているように見えた‐";
			close;
		}
		emotion 4;
		mes "[囚人 95EB72]";
		mes "くはははは……!!";
		mes "勇敢な人間だな。";
		mes "もしこの私が嘘をついて";
		mes "貴様の首をはねていたら";
		mes "どうするつもりだ？";
		mes "ここは監獄だぞ？";
		next;
		unittalk "‐ビクビク‐",1;
		mes "[囚人 95EB72]";
		mes "怖がりの人間によって";
		mes "このような暗く湿った場所に";
		mes "拘束されているが……";
		mes "ククク、私がここから";
		mes "脱出した暁には、";
		mes "人間、お前たちを許さん！";
		next;
		mes "‐檻の中の囚人は";
		mes "　すごくびくびくしているように見える‐";
		next;
		menu "……",-;
		mes "[囚人 95EB72]";
		mes "くはははは……!!";
		mes "私がびくびくしているように";
		mes "見えるのか！";
		mes "しかし、これは、そう！";
		mes "武者震いというやつだ。";
		next;
		mes "[囚人 95EB72]";
		mes "はじめて見たんだろう？";
		mes "檻の外にいるくせに無知だな。";
		mes "さすが人間だ。";
		mes "くはははは……!!";
		close;
	case 1:
		misceffect 197;
		mes "[囚人 95EB72]";
		mes "ぐうう……zZz……";
		mes "むにゃむにゃ……zZz……";
		mes "ぐうう……zZz……";
		next;
		mes "‐どうやらこの囚人は";
		mes "　寝ているようだ‐";
		close;
	}
}

prt_prison.gat,117,188,4	script	囚人 117FM188#EP161F	10136,{
	switch(rand(3)) {
	case 0:
		mes "[囚人 117FM188]";
		mes "監獄でも快適な環境は";
		mes "とても重要なんだぞ。";
		mes "君も監獄に";
		mes "行くことになったら";
		mes "これだけは覚えておくんだ。";
		close;
	case 1:
		mes "[囚人 117FM188]";
		mes "ううむ……";
		mes "空気が湿っている。";
		mes "わらわは大変不快だぞ……";
		close;
	case 2:
		mes "[囚人 117FM188]";
		mes "おい、そこの人間。";
		mes "気になることがある！";
		mes "人間の囚人たちも";
		mes "みんなこんな厳しい環境で";
		mes "暮らすのか？";
		next;
		mes "[囚人 117FM188]";
		mes "いくら囚人だとしても";
		mes "こんなに汚く湿った場所に";
		mes "閉じ込めるとは……";
		mes "正直、すべてのことに対して";
		mes "気に入らない！";
		next;
		emotion 6;
		mes "[囚人 117FM188]";
		mes "今すぐに監獄の管理人を";
		mes "呼んできなさい。";
		mes "文句を言ってやる！";
		next;
		if(select("無理です","嫌です") == 1) {
			mes "[囚人 117FM188]";
			mes "なんだと？";
			mes "　";
			mes "……そうか、君は";
			mes "ここの管理人に会える権限を";
			mes "持たないのか。";
			mes "知らなかったな。";
			next;
		} else {
			mes "[囚人 117FM188]";
			mes "なんだと？";
			mes "人間族とは気がきかないのだな。";
			mes "わらわの部下ならこの程度のこと";
			mes "喜んで聞き入れるものだが……";
			next;
		}
		mes "[囚人 117FM188]";
		mes "わらわが直接会いに行くことも";
		mes "出来ないし、";
		mes "君が管理人と会うことは";
		mes "不可能なのだから";
		mes "代案を見つけなければ。";
		next;
		mes "‐囚人は自分の思考に";
		mes "　没頭しているようだ‐";
		close;
	}
}

prt_prison.gat,103,214,4	script	囚人 103GD214#EP161G	737,{
	switch(rand(2)) {
	case 0:
		mes "[囚人 103GD214]";
		mes "ククク……クッフ……";
		mes "人間たちが私に恐れを抱いて";
		mes "この暗き地に";
		mes "我が身を縛り付けたところで、";
		mes "意志も抑制できるなどと";
		mes "思わないことだ。";
		next;
		mes "[囚人 103GD214]";
		mes "この暗闇の地で退屈にも飽き、";
		mes "永き眠りを求めた結果、";
		mes "私の中の闇はこの地の";
		mes "多くを変えてしまった……";
		next;
		emotion 56;
		misceffect 772;
		mes "[囚人 103GD214]";
		mes "ハハハハハ！";
		mes "認めたくはないが、";
		mes "私の支配下にある闇が";
		mes "暴れだそうとしている……！";
		mes "誰にこの闇を鎮められるものか！";
		close;
	case 1:
		emotion 56;
		mes "[囚人 103GD214]";
		mes "ククク……クッフ……";
		mes "クハハハハ……クッ……!!";
		mes "　";
		mes "‐檻の中の囚人はひとり、";
		mes "　苦しんでいたり";
		mes "　笑っていたりを繰り返している‐";
		close;
	}
}

prt_prison.gat,243,17,4	script	囚人 243DV17#EP161D	909,{
	emotion 29;
	mes "[囚人 243DV17]";
	mes "ククク。";
	mes "ゼロピーを1個くれたら";
	mes "行きたい区域に";
	mes "送ってやるぞ。";
	next;
	switch(select("監獄入口","A区域","B区域","C区域","D区域","E区域","F区域","G区域","H区域","丁重に断る")) {
	default:
		mes "[囚人 243DV17]";
		mes "なんだ？";
		mes "ポリンには無理な芸当ってか？";
		mes "もういい。あっち行け。";
		close;
	}
	close;
}

prt_prison.gat,55,115,2	script	囚人 55HK115#EP161H	10138,{
	switch(rand(3)) {
	case 0:
		mes "[囚人 55HK115]";
		mes "こんな場所では満足に";
		mes "角の手入れもできない。";
		mes "ああ……";
		mes "角を磨くにふさわしいものが必要だ。";
		close;
	case 1:
		mes "[囚人 55HK115]";
		mes "おい、支配人～！";
		mes "支配人はいないのか？";
		next;
		mes "‐この中の囚人はここを";
		mes "　ホテルか何かだと";
		mes "　勘違いしているのだろうか？";
		mes "　支配人を探している……";
		mes "　とりあえずスルーしよう‐";
		close;
	case 2:
		mes "[囚人 55HK115]";
		mes "最高に美しいと称賛された";
		mes "ぼくの角を";
		mes "これ以上損なう訳には……";
		next;
		mes "[囚人 55HK115]";
		mes "……あそこをうろついている";
		mes "下等種族の皮が良さそうなんだよな。";
		close;
	}
}

prt_prison.gat,243,265,6	script	囚人 243AD265#EP161A	969,{
	switch(rand(4)) {
	case 0:
		mes "[囚人 243AD265]";
		mes "死をもって自由になった";
		mes "同胞たちは今";
		mes "どこにいるのか……";
		next;
		emotion 56;
		mes "‐檻の中の囚人は";
		mes "　ボロボロに朽ちた紙を広げ、";
		mes "　己の拳を左の胸に";
		mes "　何度も叩きつけていた‐";
		close;
	case 1:
		emotion 56;
		mes "[囚人 243AD265]";
		mes "誰だ!?　私を呼ぶのは!!";
		mes "共に海を旅した仲間たちなのか！";
		mes "そうなのか！";
		next;
		mes "[囚人 243AD265]";
		mes "なぜ今頃になって呼ぶのだ";
		mes "私はそこへ行けないというのに!!";
		mes "　";
		mes "‐監獄の中にいる囚人が";
		mes "　泣き叫んでいる‐";
		close;
	case 2:
		mes "[囚人 243AD265]";
		mes "海は遠く、人だったころから";
		mes "どれだけの時間が経過しただろう……";
		next;
		mes "[囚人 243AD265]";
		mes "しかし、私は忘れないのだ。";
		mes "海で共に生きた仲間たちのことは";
		mes "絶対に……";
		mes "胸に刻んだ記憶を";
		mes "何度でもこの拳で";
		mes "思い起こそう……";
		next;
		emotion 56;
		mes "‐檻の中の囚人は";
		mes "　己の拳で左の胸を";
		mes "　パンパンと叩いている‐";
		close;
	case 3:
		emotion 52;
		mes "[囚人 243AD265]";
		mes "……おや";
		mes "久しぶりに会う人間だ。";
		mes "懐かしいものだな。";
		next;
		if(select("挨拶する","このまま去る") == 2) {
			mes "[囚人 243AD265]";
			mes "……まあ、";
			mes "相手にされぬのも仕方がない。";
			mes "私が人だったのも";
			mes "遠い昔のことだ。";
			close;
		}
		mes "[囚人 243AD265]";
		mes "ははは……ありがとう。";
		close;
	}
}

prt_prison.gat,267,184,8	script	囚人 267BD184#EP161B	10137,{
	switch(rand(3)) {
	case 0:
		emotion 38;
		mes "[囚人 267BD184]";
		mes "ほほう……？";
		mes "お前の目はなかなか";
		mes "美しい色をしているな。";
		mes "私の好みだ。";
		next;
		mes "[囚人 267BD184]";
		mes "物は相談だが……";
		mes "その目をひとつだけ";
		mes "私にくれないか？";
		mes "大事に保管する。";
		next;
		menu "それはちょっと",-,"嫌です",-;
		emotion 28;
		mes "[囚人 267BD184]";
		mes "何？";
		mes "本当に欲しかったのだが……";
		mes "そんな綺麗にピカピカ光る目を";
		mes "ふたつも持っているのに";
		mes "譲ることができないとはな。";
		next;
		emotion 32;
		mes "[囚人 267BD184]";
		mes "致し方ない。";
		mes "諦めるとしよう。";
		mes "その代わり、";
		mes "会いに来ておくれ。";
		close;
	case 1:
		mes "‐檻の中の囚人は";
		mes "　とても穏やかな表情をしている。";
		mes "　話しかけられたら、";
		mes "　ついつい相手をしてしまいそうな";
		mes "　雰囲気だ‐";
		next;
		if(select("どうしてここに？","立ち去る") == 1) {
			mes "[囚人 267BD184]";
			mes "……今のは、";
			mes "私に話しかけたのか？";
			mes "ふふ。";
			next;
			mes "[囚人 267BD184]";
			mes "お前の目はなかなかに好みだ。";
			mes "答えてあげようか。";
			mes "……結婚詐欺だ。";
			next;
			mes "[囚人 267BD184]";
			mes "そう、結婚詐欺！";
			mes "本当にありえないな！";
			mes "お前の目には私が";
			mes "結婚詐欺などという";
			mes "愛憎に満ちた事件を";
			mes "起こすような顔に見えるか？";
			next;
			emotion 38;
			mes "[囚人 267BD184]";
			mes "私はただ綺麗な目を持った";
			mes "女性に興味があっただけだ。";
			mes "それなのに、私の純粋な愛を";
			mes "誤解するとは。";
			next;
			mes "[囚人 267BD184]";
			mes "まったく人間には";
			mes "困ったものだね。";
			next;
		}
		mes "["+strcharinfo(0)+"]";
		mes "（こういう相手は危険だ。";
		mes "早くここから離れよう）";
		mes "　";
		mes "‐あなたはその檻に背を向けた‐";
		close;
	case 2:
		mes "[囚人 267BD184]";
		mes "……うん。";
		mes "私には時間がたっぷりとあるが、";
		mes "お前とはまだ遊んであげられないな。";
		next;
		if(select("なぜ？","自分もです") == 2) {
			emotion 6;
			mes "[囚人 267BD184]";
			mes "では、早急に立ち去るといい。";
			close;
		}
		mes "[囚人 267BD184]";
		mes "ふふ。";
		mes "まだ私好みの目ではないからね。";
		mes "次に会う時までに";
		mes "綺麗に磨いてくれたまえ。";
		close;
	}
}
