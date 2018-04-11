//====================================================================
//Ragnarok Online - Kagerou Oboro Jobchange Script	by refis
//
//　■ CHANGE_KO -> 0～11
//====================================================================

que_ng.gat,28,156,0	script	はじめ#ko	139,1,1,{
	if(Job == Job_Ninja && BaseLevel >= 99 && JobLevel >= 70 && CHANGE_KO == 0) {
		mes "‐どこかで聞いたことのある";
		mes "　声が聞こえてくる‐";
		next;
		mes "[謎の声A]";
		mes "やあ、久しぶりですね。";
		mes "私がここを離れてから";
		mes "一族に加わった若者達の様子は";
		mes "どうですか？";
		next;
		mes "[謎の声B]";
		mes "うむ。なかなか根性のある奴らが";
		mes "多く入ってくれた。";
		mes "お前の人を見る目も";
		mes "まだまだ捨てたものじゃないな……。";
		next;
		mes "[謎の声A]";
		mes "君にそう言ってもらえるとは";
		mes "光栄ですね。";
		mes "ただでさえ空気の悪い場所に飛ばされ";
		mes "ここが恋しくなっていましたが……";
		next;
		mes "[謎の声A]";
		mes "どうです、そろそろ交代しませんか？";
		next;
		mes "[謎の声B]";
		mes "未練を捨てきれていないようだな。";
		mes "あの方がお許しになると";
		mes "思っているのか？";
		next;
		mes "[謎の声A]";
		mes "冗談ですよ。";
		mes "ところで、新人達の中で";
		mes "^BD0408あの場所^000000を";
		mes "見つけた子はいるのですか？";
		next;
		mes "[謎の声B]";
		mes "いや、隠された場所を探すのもまた";
		mes "試練のひとつ……";
		next;
		mes "[謎の声A]";
		mes "相変わらず融通が効きませんね。";
		mes "あんな場所、ただの壁……";
		next;
		mes "[謎の声B]";
		mes "……まて、誰かに聞かれている！";
		mes "お前は今すぐ任地に復帰しろ！";
		next;
		mes "‐話し声が聞こえなくなった。";
		mes "　隠された場所、壁、試練……";
		mes "　いったい何の事だろうか？‐";
		setquest 5131;
		set CHANGE_KO,1;
		close;
	}
	end;
}

que_ng.gat,21,76,0	script	絵がかざってある壁#ko	844,{
	if(Job == Job_Kagerou || Job == Job_Oboro) {
		mes "‐もうここには用はない‐";
		close;
	}
	if(CHANGE_KO == 1) {
		mes "‐隠された場所と";
		mes "　思われるところを見つけた‐";
		next;
		mes "‐以前この部屋に来た時に";
		mes "　気づかなかったのは何故だろう‐";
		next;
		mes "‐ともかく、中に入るためには……‐";
		next;
		if(select("絵を引きちぎる","絵に手をかざす") == 1) {
			mes "‐他人のものを勝手に";
			mes "　傷つけるわけにはいかない‐";
			close;
		}
		mes "‐絵の前に手をかざすと";
		mes "　何かに強くひっぱられる感じがした‐";
		close2;
		warp "job_ko.gat",26,111;
		end;
	}
	if(CHANGE_KO >= 2) {
		mes "‐^25C18D忍者屋敷^000000の隠し部屋への入り口だ‐";
		next;
		if(select("入る","入らない") == 2) {
			mes "‐あなたは壁から離れた‐";
			close;
		}
		mes "‐絵の前に手をかざすと";
		mes "　何かに強くひっぱられる感じがした‐";
		close2;
		warp "job_ko.gat",26,111;
		end;
	}
	mes "‐きれいな絵がかざってある壁だ‐";
	close;
}

job_ko.gat,25,115,4	script	謎の老人#ko	588,{
	switch(CHANGE_KO) {
	case 1:
		cutin "job_ko03",2;
		mes "‐^1A95E6老人が静かに瞑想をしている^000000‐";
		next;
		if(select("無視する","話しかける") == 1) {
			cutin "job_ko03",255;
			mes "‐あなたは、そっとその場を離れた‐";
			close;
		}
		mes "‐^1A95E6老人に話しかけたが反応がない……";
		mes "　あなたは立ち去ろうとした^000000‐";
		next;
		mes "[謎の老人]";
		mes "ついに辿りついた者が現れたか。";
		mes "ふむ……生きた人間は";
		mes "ひさかたぶりじゃ。";
		next;
		menu "ここはいったい……？",-;
		mes "‐^1A95E6老人はあなたのことを無視して";
		mes "　話を続けた^000000‐";
		next;
		mes "[謎の老人]";
		mes "昔、アマツには密かに";
		mes "歴史の影に生きる一族がいた……";
		next;
		mes "[謎の老人]";
		mes "影の中に潜みながらも";
		mes "ヒマワリのように……";
		mes "そう、陽の光差す場所を望んだ一族……";
		next;
		mes "[謎の老人]";
		mes "ただ一人の主に忠誠を誓った一族……";
		next;
		mes "[謎の老人]";
		mes "頼もしく……";
		next;
		mes "[謎の老人]";
		mes "忠義にあふれ……";
		next;
		mes "[謎の老人]";
		mes "そして強い……";
		next;
		menu "その一族はどうなりましたか？ ",-;
		mes "‐^1A95E6老人は寂しそうな目を";
		mes "　あなたに向けた^000000‐";
		next;
		mes "[謎の老人]";
		mes "主に捨てられ、";
		mes "歴史からも捨てられた一族を ";
		mes "何故、知りたがる？ ";
		next;
		if(select("……忍者だからです","ただの好奇心") == 2) {
			mes "[謎の老人]";
			mes "……そうか。";
			mes "すまんが、帰ってくれ。";
			close2;
			warp "amatsu.gat",147,136;
			end;
		}
		cutin "job_ko02",2;
		mes "[謎の老人]";
		mes "忍者！";
		mes "たしかに、一族が忍者と";
		mes "呼ばれた時期もあった……。";
		next;
		set CHANGE_KO,2;
		chgquest 5131,5132;
		mes "[謎の老人]";
		mes "そなたに昔から伝わる話を話そう。";
		mes "忘れられた一族の話を……。";
		close2;
		cutin "job_ko03",255;
		end;
	case 2:
		cutin "job_ko01",2;
		mes "‐^1A95E6謎の老人は孫に昔話を聞かせるような";
		mes "　静かな声で語り始めた^000000‐";
		next;
		mes "[謎の老人]";
		mes "あまりにも長い間語られなかったため";
		mes "今のアマツに住まうものは";
		mes "誰も覚えていないじゃろう。";
		next;
		mes "[謎の老人]";
		mes "城主の影となって働き";
		mes "城主のために生きることを選んだ";
		mes "一族があったのじゃ。";
		next;
		mes "[謎の老人]";
		mes "主のためならば";
		mes "どんな困難なことでもなしとげる";
		mes "忠実なる一族……。";
		next;
		mes "[謎の老人]";
		mes "忍者や闇の一族とも呼ばれていたが";
		mes "決して一族が望んで";
		mes "呼ばれていたわけではなかった。";
		next;
		mes "[謎の老人]";
		mes "彼らは城主の手足とも";
		mes "いうべき存在だったが";
		mes "その能力の高さ故に";
		mes "問題が発生してしまった。";
		next;
		menu "問題とは？",-;
		mes "[謎の老人]";
		mes "主たる城主でさえ全体像を掴めない";
		mes "徹底した秘密組織。";
		next;
		mes "[謎の老人]";
		mes "一族の存在に気づいた者たちが";
		mes "執拗に調べたが、";
		mes "情報を得ることはできなかった。";
		next;
		mes "[謎の老人]";
		mes "やがて、主である城主にも";
		mes "恐れられるようになり";
		mes "しだいに遠ざけられてしまった……。";
		next;
		mes "[謎の老人]";
		mes "城主の側を離れることになっても";
		mes "一族は主を裏切ることはなかった……。";
		next;
		menu "忠義に厚い一族だったのですね",-;
		cutin "job_ko03",2;
		mes "[謎の老人]";
		mes "そう、忠義が厚過ぎる";
		mes "くらいじゃった……。";
		next;
		set CHANGE_KO,3;
		chgquest 5132,5133;
		mes "‐^1A95E6老人はいっそうさびしそうな";
		mes "　表情になってしまった。^000000";
		mes "　引き続き、話しかけよう‐";
		close2;
		cutin "job_ko02",255;
		end;
	case 3:
		cutin "job_ko03",2;
		mes "[謎の老人]";
		mes "一族はあまりにも長い時間";
		mes "影に隠れてしまっていた。";
		mes "今の城主は一族のことを";
		mes "知りもしないじゃろう。";
		next;
		menu "…………",-;
		cutin "job_ko01",2;
		mes "[謎の老人]";
		mes "わしは忍者、";
		mes "または闇の一族と呼ばれた一族の";
		mes "最後の導き手、ギオンというものじゃ。";
		next;
		if(select("もう休みなさい","さらなる極みに達したいです") == 1) {
			cutin "job_ko04",2;
			mes "[導き手 ギオン]";
			mes "……この老いぼれの命を欲する";
			mes "暗殺者だったのか？";
			next;
			mes "[導き手 ギオン]";
			mes "それで一族に関心を持ったのか……";
			mes "じゃが、簡単にくれてやる訳には";
			mes "いかぬな。";
			next;
			mes "[導き手 ギオン]";
			mes "命まで取るつもりはないが……";
			next;
			mes "‐^1A95E6大きな衝撃を受け";
			mes "　意識が遠のいてゆく……^000000‐";
			close2;
			percentheal -99,0;
			warp "amatsu.gat",147,136;
			end;
		}
		cutin "job_ko02",2;
		mes "[導き手 ギオン]";
		mes "極み……か。";
		mes "久しぶりに耳にした言葉じゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "そなたがここに現れたのも";
		mes "何かの導きかもしれぬ……。";
		next;
		mes "[導き手 ギオン]";
		mes "じゃが、すまないことに";
		mes "わしが教えられることは何もない。";
		next;
		mes "[導き手 ギオン]";
		mes "しかしそなたが歩むべき";
		mes "^33CC71" +(Sex? "影狼": "朧")+ "への道^000000に導くだけじゃ。";
		next;
		mes "‐^1A95E6意識が遠のき";
		mes "　ギオンの声が遠くから聞こえてくる^000000‐";
		next;
		set CHANGE_KO,4;
		chgquest 5133,5134;
		mes "[導き手 ギオン]";
		mes "導き手であるわしと共に";
		mes (Sex? "影狼": "朧")+ "への道を歩む準備ができたなら";
		mes "また会いに来るがよい。";
		close2;
		warp "amatsu.gat",147,136;
		end;
	case 4:
		cutin "job_ko02",2;
		mes "[導き手 ギオン]";
		mes "ふむ……少しじゃが";
		mes "^33CC71" +(Sex? "影狼": "朧")+ "への道^000000に恐れをなし";
		mes "来ないのではないかと思ったが……";
		mes "いらぬ心配だったようじゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "さらなる極みに歩みだすためには";
		mes "誘惑に負けない正しき心と";
		mes "未知の世界にもうろたえない";
		mes "強い精神が必要じゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "一族の先祖は4種の試練によって";
		mes "その精神を手に入れた。";
		next;
		menu "4種の試練？",-;
		cutin "job_ko01",2;
		mes "[導き手 ギオン]";
		mes "そうじゃ、";
		mes "先祖は^087FF8知識、生存、武器、戦闘^000000と";
		mes "4種の試練に挑み";
		mes "正しい心と精神を養った。";
		next;
		mes "[導き手 ギオン]";
		mes "試練がどんなものか";
		mes "知りたいようじゃな。";
		mes "説明してやってもよいぞ。";
		while(1) {
			next;
			switch(select("知識の試練","生存の試練","武器の試練","戦闘の試練")) {
			case 1:
				mes "[導き手 ギオン]";
				mes "城主の補佐をつとめるためには";
				mes "数多くの知識が必要じゃ。";
				mes "そのための試練じゃ。";
				next;
				mes "[導き手 ギオン]";
				mes "10問の問題に答え";
				mes "9問以上正解すれば";
				mes "試練を乗り越えられるのじゃ。";
				next;
				mes "[導き手 ギオン]";
				mes "普段から知識を積み重ねた者なら";
				mes "問題ないじゃろう。";
				set '@flag,'@flag|1;
				if('@flag == 15)
					break;
				mes "次はどの試練について話そうかのう？";
				continue;
			case 2:
				mes "[導き手 ギオン]";
				mes "任務が常に安全とは限らないのでな。";
				mes "生存は重要なのじゃ。";
				next;
				mes "[導き手 ギオン]";
				mes "この試練を先祖は";
				mes "スゴロクと呼んでおった。";
				mes "サイコロで出た目の数だけ";
				mes "進む試練じゃ。";
				next;
				mes "[導き手 ギオン]";
				mes "まあ、スゴロクと言った時点で";
				mes "すぐに想像がついたじゃろう。";
				next;
				mes "[導き手 ギオン]";
				mes "じゃが、試練と呼ばれるくらいじゃ。";
				mes "単なる娯楽とはひと味違うぞ。";
				next;
				mes "[導き手 ギオン]";
				mes "そなたを助けるマスもあれば";
				mes "邪魔をするマスもあるじゃろう。";
				next;
				mes "[導き手 ギオン]";
				mes "賢く対応すれば";
				mes "乗り越えられるじゃろう。";
				set '@flag,'@flag|2;
				if('@flag == 15)
					break;
				mes "次はどの試練について話そうかのう？";
				continue;
			case 3:
				mes "[導き手 ギオン]";
				mes "一族は独特の武器を使っていたのじゃ。";
				mes "そのほとんどは自分たちで";
				mes "作ったものじゃった。";
				next;
				mes "[導き手 ギオン]";
				mes "自分だけの武器を作り出した者は";
				mes "祝福されし者と呼ばれていたそうじゃ。";
				next;
				mes "[導き手 ギオン]";
				mes "自分が使う武器を作り";
				mes "その武器を強化することが";
				mes "この試練の目標じゃ。";
				next;
				mes "[導き手 ギオン]";
				mes "そなたが祝福されし者と";
				mes "呼ばれることを祈ろう。";
				set '@flag,'@flag|4;
				if('@flag == 15)
					break;
				mes "次はどの試練について話そうかのう？";
				continue;
			case 4:
				mes "[導き手 ギオン]";
				mes "任務は一人だけに与えられるとは";
				mes "限らない。";
				mes "一つの任務を何人かで遂行することも";
				mes "当たり前のようにある。";
				next;
				mes "[導き手 ギオン]";
				mes "戦闘の試練は知識、生存、武器の試練を";
				mes "全て乗り越えた者だけが挑戦できる。";
				mes "つまり最後の試練ということじゃ……。";
				next;
				mes "[導き手 ギオン]";
				mes "他の試練とは違い";
				mes "他人と競うことが要求される……。";
				next;
				mes "[導き手 ギオン]";
				mes "目標はただひとつ！";
				mes "最も早く目標を倒した一人だけが";
				mes "試練を乗り越えられるわけじゃ。";
				next;
				mes "[導き手 ギオン]";
				mes "まあ、そなたが試練を受ける時に";
				mes "競う者がいなければ";
				mes "それもまたそなたの運じゃ。";
				set '@flag,'@flag|8;
				if('@flag == 15)
					break;
				mes "次はどの試練について話そうかのう？";
				continue;
			}
			break;
		}
		next;
		cutin "job_ko02",2;
		mes "[導き手 ギオン]";
		mes "百聞は一見にしかず、とも言うしな。";
		mes "直接赴くのが一番効果的じゃろう。";
		next;
		set CHANGE_KO,5;
		chgquest 5134,5135;
		mes "[導き手 ギオン]";
		mes "試練を受ける準備ができたなら";
		mes "もう一度声をかけるがよい。";
		close2;
		cutin "job_ko02",255;
		end;
	case 5:
		cutin "job_ko03",2;
		mes "[導き手 ギオン]";
		mes "本当に久しぶりじゃ……";
		mes "このように心が躍るのは。";
		next;
		mes "[導き手 ギオン]";
		mes "新しき道に進み行く若者のおかげか";
		mes "年甲斐もなく興奮しておるわい。";
		next;
		mes "[導き手 ギオン]";
		mes "試練については、すでに説明したな。";
		mes "では、一族のことも少し教えよう。";
		next;
		cutin "job_ko01",2;
		mes "[導き手 ギオン]";
		mes "一族は二人の戦士から";
		mes "始まったのじゃ……。";
		next;
		mes "[導き手 ギオン]";
		mes "太陽にたとえられし";
		mes "影に潜む狼のごとき戦士";
		mes "影狼……。";
		next;
		mes "[導き手 ギオン]";
		mes "月にたとえられし";
		mes "淡き月光のごとき戦士";
		mes "朧……。";
		next;
		mes "[導き手 ギオン]";
		mes "太陽と月";
		mes "どちらも世界を照らすものだが";
		mes "二人の戦士は似て異なる存在じゃった。";
		next;
		mes "[導き手 ギオン]";
		mes "互いに反目していた時期もあった。";
		next;
		mes "[導き手 ギオン]";
		mes "だが同じ一族になるまでには";
		mes "それほど長くの時間は";
		mes "必要としていなかったのじゃ。";
		next;
		menu "いったい何があったのですか？",-;
		cutin "job_ko02",2;
		mes "[導き手 ギオン]";
		mes "ふぉふぉふぉ。";
		mes "話し続けたせいか少し疲れたわい。";
		mes "試練を乗り越えてきたら";
		mes "続きを聞かせよう。";
		next;
		mes "[導き手 ギオン]";
		mes "始めに選ぶ試練はどれじゃ？";
		next;
		switch(select("知識の試練","生存の試練","武器の試練")) {
		case 1:
			mes "[導き手 ギオン]";
			mes "^339CCC知識の試練^000000から始めるのか？";
			mes "ふぉふぉふぉ。";
			mes "そなたがこの道を選んだことを";
			mes "あやつが知った時の顔が";
			mes "楽しみじゃの。";
			next;
			menu "あやつ？",-;
			set CHANGE_KO,6;
			setquest 5136;
			mes "[導き手 ギオン]";
			mes "ふぉふぉふぉ。";
			mes "会ってからのお楽しみじゃ。";
			mes "知識の試練はこっちじゃ。";
			close2;
			warp "job_ko.gat",72,128;
			end;
		case 2:
			mes "[導き手 ギオン]";
			mes "^339CCC生存の試練^000000から始めるのか？";
			mes "孤独な試練となるかも知れぬが……。";
			next;
			set CHANGE_KO,6;
			setquest 5137;
			mes "[導き手 ギオン]";
			mes "そなたならいらぬ心配じゃろう。";
			mes "生存の試練はこっちじゃ。";
			close2;
			warp "job_ko.gat",62,16;
			end;
		case 3:
			mes "[導き手 ギオン]";
			mes "^339CCC武器の試練^000000から始めるのか？";
			mes "では試練の前に……。";
			next;
			set CHANGE_KO,6;
			setquest 5138;
			getitem 1002,5;
			getitem 1010,1;
			mes "‐鉄鉱石を5個";
			mes "　プラコンを1個受け取りました‐";
			next;
			mes "[導き手 ギオン]";
			mes "それが必要になるじゃろう。";
			mes "武器の試練はこっちじゃ。";
			close2;
			warp "job_ko.gat",121,129;
			end;
		}
	case 6:
		set '@test1,checkquest(5136);
		set '@test2,checkquest(5137);
		set '@test3,checkquest(5138);
		if('@test1) {
			set '@test$,"知識";
			if('@test1 & 0x1) {
				set '@x,72;
				set '@y,128;
			}
		}
		else if('@test2) {
			set '@test$,"生存";
			if('@test2 & 0x1) {
				set '@x,62;
				set '@y,16;
			}
		}
		else if('@test3) {
			set '@test$,"武器";
			if('@test3 & 0x1) {
				set '@x,121;
				set '@y,129;
			}
		}
		if('@x && '@y) {
			cutin "job_ko04",2;
			mes "[導き手 ギオン]";
			mes "^339CCC" +'@test$+ "の試練^000000を受けているのか。";
			mes "再び試練に向かうかね？";
			next;
			switch(select("試練の場へ向かう","街に戻ります")) {
			case 1:
				mes "[導き手 ギオン]";
				mes '@test$+ "の試練はこっちじゃ。";
				close2;
				warp "job_ko.gat",'@x,'@y;
				end;
			case 2:
				mes "[導き手 ギオン]";
				mes "街まで送ろう。";
				close2;
				warp "amatsu.gat",147,136;
				end;
			}
		}
		cutin "job_ko01",2;
		mes "[導き手 ギオン]";
		mes "^339CCC" +'@test$+ "の試練^000000を乗り越えて来たか。";
		next;
		mes "[導き手 ギオン]";
		mes "2人とも満足できるような";
		mes "結果が得られたかな？";
		next;
		menu "話の続きを……",-;
		cutin "job_ko02",2;
		mes "[導き手 ギオン]";
		mes "そう急かさなくても覚えておる。";
		mes "……どこまで話をしたかのう。";
		mes "……ああ、そうじゃったな。";
		next;
		mes "[導き手 ギオン]";
		mes "太陽にたとえられし";
		mes "影に潜む狼のごとき戦士";
		mes "影狼……。";
		next;
		mes "[導き手 ギオン]";
		mes "月にたとえられし";
		mes "淡き月光のごとき戦士";
		mes "朧……。";
		next;
		mes "[導き手 ギオン]";
		mes "もともと二人の仲は良くなかった。";
		mes "性格も考え方も、すべてが";
		mes "正反対じゃった……。";
		next;
		mes "[導き手 ギオン]";
		mes "二人が最初に出会ったのは";
		mes "戦場じゃった……。";
		mes "それも敵同士として相まみえたのじゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "そのような状況では";
		mes "互いに傷つけあい、";
		mes "憎みあうしかなかったのじゃ……。";
		next;
		mes "[導き手 ギオン]";
		mes "じゃが、それが戦争というものじゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "昨日までは隣で笑っていた仲間が";
		mes "今日はもういない……。";
		mes "そういう場所じゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "ましてや敵同士。";
		mes "仲間を奪ったものに対する憎悪は";
		mes "増してゆくばかりじゃ……。";
		next;
		mes "[導き手 ギオン]";
		mes "少し疲れた。";
		mes "続きはもう一つ試練を";
		mes "乗り越えた後にでも話そう。";
		next;
		mes "[導き手 ギオン]";
		mes "二つ目はどの試練かね？ ";
		if(!'@test1)
			set '@str1$,"知識の試練";
		if(!'@test2)
			set '@str2$,"生存の試練";
		if(!'@test3)
			set '@str3$,"武器の試練";
		next;
		switch(select('@str1$,'@str2$,'@str3$)) {
		case 1:
			mes "[導き手 ギオン]";
			mes "^339CCC知識の試練^000000か。";
			mes "ふぉふぉふぉ。";
			mes "そなたがこの道を選んだことを";
			mes "あやつが知った時の顔が";
			mes "楽しみじゃの。";
			next;
			menu "あやつ？",-;
			set CHANGE_KO,7;
			setquest 5136;
			mes "[導き手 ギオン]";
			mes "ふぉふぉふぉ。";
			mes "会ってからのお楽しみじゃ。";
			mes "知識の試練はこっちじゃ。";
			close2;
			warp "job_ko.gat",72,128;
			end;
		case 2:
			mes "[導き手 ギオン]";
			mes "^339CCC生存の試練^000000か。";
			mes "孤独な試練となるかも知れぬが……。";
			next;
			set CHANGE_KO,7;
			setquest 5137;
			mes "[導き手 ギオン]";
			mes "そなたならいらぬ心配じゃろう。";
			mes "生存の試練はこっちじゃ。";
			close2;
			warp "job_ko.gat",62,16;
			end;
		case 3:
			mes "[導き手 ギオン]";
			mes "^339CCC武器の試練^000000か。";
			mes "では試練の前に……。";
			next;
			set CHANGE_KO,7;
			setquest 5138;
			getitem 1002,5;
			getitem 1010,1;
			mes "‐鉄鉱石を5個";
			mes "　プラコンを1個受け取りました‐";
			next;
			mes "[導き手 ギオン]";
			mes "それが必要になるじゃろう。";
			mes "武器の試練はこっちじゃ。";
			close2;
			warp "job_ko.gat",121,129;
			end;
		}
	case 7:
		set '@test1,checkquest(5136);
		set '@test2,checkquest(5137);
		set '@test3,checkquest(5138);
		if('@test1 & 0x1) {
			set '@test$,"知識";
			set '@x,72;
			set '@y,128;
		}
		else if('@test2 & 0x1) {
			set '@test$,"生存";
			set '@x,62;
			set '@y,16;
		}
		else if('@test3 & 0x1) {
			set '@test$,"武器";
			set '@x,121;
			set '@y,129;
		}
		if('@x && '@y) {
			cutin "job_ko04",2;
			mes "[導き手 ギオン]";
			mes "^339CCC" +'@test$+ "の試練^000000を受けているのか。";
			mes "再び試練に向かうかね？";
			next;
			switch(select("試練の場へ向かう","街に戻ります")) {
			case 1:
				mes "[導き手 ギオン]";
				mes '@test$+ "の試練はこっちじゃ。";
				close2;
				warp "job_ko.gat",'@x,'@y;
				end;
			case 2:
				mes "[導き手 ギオン]";
				mes "街まで送ろう。";
				close2;
				warp "amatsu.gat",147,136;
				end;
			}
		}
		if('@test1 & 0x8 && '@test2 & 0x8) {
			set '@type,3;
			set '@str$,"知識、生存の試練";
		}
		else if('@test1 & 0x8 && '@test3 & 0x8) {
			set '@type,2;
			set '@str$,"知識、武器の試練";
		}
		else if('@test2 & 0x8 && '@test3 & 0x8) {
			set '@type,1;
			set '@str$,"生存、武器の試練";
		}
		cutin "job_ko04",2;
		mes "[導き手 ギオン]";
		mes "^339CCC" +'@str$+ "^000000を乗り越えたか。";
		next;
		mes "[導き手 ギオン]";
		mes "これで二つ……。";
		mes "何かしら得るものがあったかな？";
		next;
		cutin "job_ko01",2;
		mes "[導き手 ギオン]";
		mes "では、続きを話そう。";
		next;
		mes "[導き手 ギオン]";
		mes "太陽にたとえられし";
		mes "影に潜む狼のごとき戦士";
		mes "影狼……。";
		next;
		mes "[導き手 ギオン]";
		mes "月にたとえられし";
		mes "淡き月光のごとき戦士";
		mes "朧……。";
		next;
		mes "[導き手 ギオン]";
		mes "二人の戦士が戦場で敵として";
		mes "出会ったところまでは話したな。";
		next;
		mes "[導き手 ギオン]";
		mes "長きに渡る戦争も、ついに終わる時が来た。";
		mes "平和が訪れたわけじゃが";
		mes "生き残った者たちも";
		mes "傷つき疲れ果てていた……。";
		next;
		mes "[導き手 ギオン]";
		mes "二人の戦士もまた、戦いを止めた。";
		mes "お互いに命を狙うこともなくなったが";
		mes "この二人にも癒しの時間が必要だった。";
		next;
		mes "[導き手 ギオン]";
		mes "そんな二人の前に一人の男が現れた。";
		mes "詳しいことは伝えられていないが";
		mes "二人の戦士の忠誠を得たのは";
		mes "その男だったと言われておる。";
		next;
		menu "その男とは？",-;
		mes "[導き手 ギオン]";
		mes "その男に関して伝わっていることは";
		mes "ほとんどないのじゃ。";
		mes "ただ二人の忠誠を得たとだけ";
		mes "記録には残っている。";
		next;
		mes "[導き手 ギオン]";
		mes "おそらく、今のアマツ城主の";
		mes "先祖ではないかと";
		mes "ワシは考えておる。";
		next;
		mes "[導き手 ギオン]";
		mes "一族に関する話も";
		mes "残り少なくなってきたのう。";
		mes "三つ目の試練を乗り越えたなら";
		mes "また続きを話そう。";
		next;
		switch('@type) {
		case 1:
			mes "[導き手 ギオン]";
			mes "^339CCC知識の試練^000000か。";
			mes "ふぉふぉふぉ。";
			mes "そなたがこの道を選んだことを";
			mes "あやつが知った時の顔が";
			mes "楽しみじゃの。";
			next;
			menu "あやつ？",-;
			set CHANGE_KO,8;
			setquest 5136;
			mes "[導き手 ギオン]";
			mes "ふぉふぉふぉ。";
			mes "会ってからのお楽しみじゃ。";
			mes "知識の試練はこっちじゃ。";
			close2;
			warp "job_ko.gat",72,128;
			end;
		case 2:
			mes "[導き手 ギオン]";
			mes "^339CCC生存の試練^000000か。";
			mes "孤独な試練となるかも知れぬが……。";
			next;
			set CHANGE_KO,8;
			setquest 5137;
			mes "[導き手 ギオン]";
			mes "そなたならいらぬ心配じゃろう。";
			mes "生存の試練はこっちじゃ。";
			close2;
			warp "job_ko.gat",62,16;
			end;
		case 3:
			mes "[導き手 ギオン]";
			mes "^339CCC武器の試練^000000か。";
			mes "では試練の前に……。";
			next;
			set CHANGE_KO,8;
			setquest 5138;
			getitem 1002,5;
			getitem 1010,1;
			mes "‐鉄鉱石を5個";
			mes "　プラコンを1個受け取りました‐";
			next;
			mes "[導き手 ギオン]";
			mes "それが必要になるじゃろう。";
			mes "武器の試練はこっちじゃ。";
			close2;
			warp "job_ko.gat",121,129;
			end;
		}
	case 8:
		set '@test1,checkquest(5136);
		set '@test2,checkquest(5137);
		set '@test3,checkquest(5138);
		if('@test1 & 0x1) {
			set '@test$,"知識";
			set '@x,72;
			set '@y,128;
		}
		else if('@test2 & 0x1) {
			set '@test$,"生存";
			set '@x,62;
			set '@y,16;
		}
		else if('@test3 & 0x1) {
			set '@test$,"武器";
			set '@x,121;
			set '@y,129;
		}
		if('@x && '@y) {
			cutin "job_ko04",2;
			mes "[導き手 ギオン]";
			mes "^339CCC" +'@test$+ "の試練^000000を受けているのか。";
			mes "再び試練に向かうかね？";
			next;
			switch(select("試練の場へ向かう","街に戻ります")) {
			case 1:
				mes "[導き手 ギオン]";
				mes '@test$+ "の試練はこっちじゃ。";
				close2;
				warp "job_ko.gat",'@x,'@y;
				end;
			case 2:
				mes "[導き手 ギオン]";
				mes "街まで送ろう。";
				close2;
				warp "amatsu.gat",147,136;
				end;
			}
		}
		cutin "job_ko01",2;
		mes "[導き手 ギオン]";
		mes "残る試練もひとつだけとなったか。";
		next;
		mes "[導き手 ギオン]";
		mes "他の試練とは違い";
		mes "他人と競うことが要求される……";
		mes "そんな試練じゃ。";
		next;
		menu "あの……話の続きは？",-;
		cutin "job_ko02",2;
		mes "[導き手 ギオン]";
		mes "ふぉふぉふぉ、覚えていたか。";
		mes "では続きを話そう。";
		next;
		mes "[導き手 ギオン]";
		mes "太陽にたとえられし";
		mes "影に潜む狼のごとき戦士";
		mes "影狼……。";
		next;
		mes "[導き手 ギオン]";
		mes "月にたとえられし";
		mes "淡き月光のごとき戦士";
		mes "朧……。";
		next;
		mes "[導き手 ギオン]";
		mes "この二人の戦士の忠誠を得た男は";
		mes "少し変わった性格だったと";
		mes "伝えられておる。";
		next;
		mes "[導き手 ギオン]";
		mes "争いよりは話し合いを優先し";
		mes "冗談が大好きで";
		mes "女好きだったと";
		mes "伝えられておるのじゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "ふぉふぉ……";
		mes "なぜこんな小さなことが";
		mes "伝えられておるのかわからぬが……。";
		next;
		mes "[導き手 ギオン]";
		mes "男は二人の戦士の仲を取り持つことを";
		mes "望んだようじゃ。";
		mes "長い戦争で二人がそう簡単には";
		mes "打ち解けられなかったせいかも知れぬ。";
		next;
		mes "[導き手 ギオン]";
		mes "二人の戦士を任務で組ませたり";
		mes "密室に閉じ込めたりと";
		mes "二人きりにさせたそうじゃ。";
		next;
		menu "自分が楽しんだだけでは……",-;
		mes "[導き手 ギオン]";
		mes "ふぉふぉふぉ、そうかも知れんのう。";
		mes "まあ、おかげで二人の戦士は";
		mes "晴れて結ばれることとなった。";
		next;
		mes "[導き手 ギオン]";
		mes "一族の始まり、というわけじゃな。";
		next;
		menu "それからどうなりましたか？ ",-;
		mes "[導き手 ギオン]";
		mes "惜しいことにその後のことは";
		mes "何者かによって意図的に";
		mes "伝えられていないようなのじゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "過去にしばられることなく";
		mes "未来へと進んで欲しかったから";
		mes "と、わしは考えておる……。";
		next;
		mes "[導き手 ギオン]";
		mes "さあ、そろそろ最後の試練を";
		mes "始めようかの？";
		next;
		set CHANGE_KO,9;
		chgquest 5135,72900;
		mes "[導き手 ギオン]";
		mes "疲れているようなら";
		mes "しばし休むのも良いかもしれん。";
		mes "準備ができたら";
		mes "声をかけるのじゃ。";
		close2;
		cutin "job_ko01",255;
		end;
	case 9:
		cutin "job_ko01",2;
		mes "[導き手 ギオン]";
		mes "もう少し休んでいても";
		mes "良かったのじゃよ。";
		mes "それとも、急ぎの用でもあるのか？";
		next;
		input '@str$;
		cutin "job_ko03",2;
		mes "[導き手 ギオン]";
		mes "^B24E59" +'@str$+ "^000000か？";
		next;
		mes "[導き手 ギオン]";
		mes "若者の心情は理解しづらいな。";
		next;
		mes "[導き手 ギオン]";
		mes "まあ、ここまでやってきたそなたなら";
		mes "最後の試練も乗り越えられるじゃろう。";
		next;
		cutin "job_ko01",2;
		mes "[導き手 ギオン]";
		mes "さて！";
		mes "戦闘の試練について説明しよう。";
		next;
		mes "[導き手 ギオン]";
		mes "戦闘の試練の目標は";
		mes "^FF0000一族の過去^000000と呼ばれるモンスターじゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "試練の場には似ている姿、";
		mes "似ている名前のモンスターがいる。";
		mes "注意して戦うのじゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "もしかしたら、同じ目標を狙う者が";
		mes "いるかも知れん。";
		mes "目標を倒した者のみが";
		mes "試練を乗り越えられるのじゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "そなたに" +(Sex? "影狼": "朧")+ "様の";
		mes "ご加護があらんことを……。";
		next;
		set CHANGE_KO,10;
		chgquest 72900,5146;
		mes "[導き手 ギオン]";
		mes "では戦闘の試練の場に向かうとしよう。";
		close2;
		switch(rand(3)){
		case 0: warp "job_ko.gat",142,20; break;
		case 1: warp "job_ko.gat",141,80; break;
		}
		end;
	case 10:
	case 11:
		cutin "job_ko03",2;
		mes "[導き手 ギオン]";
		mes "むむ?!";
		mes "そなたは^339CCC戦闘の試練^000000を";
		mes "受けていたはずでは？ ";
		next;
		switch(select("試練の場に送ってもらう","街に戻ります")) {
		case 1:
			mes "[導き手 ギオン]";
			mes "試練の場はこっちじゃ。";
			close2;
			warp "job_ko.gat",141,80;
			end;
		case 2:
			mes "[導き手 ギオン]";
			mes "街まで送ろう。";
			close2;
			warp "amatsu.gat",147,136;
			end;
		}
	}
}

job_ko.gat,81,124,4	script	クウガ・カイ#ko	730,{
	if(checkquest(5136)) {
		if(checkquest(5136) & 0x8) {
			mes "[クウガ・カイ]";
			mes "さあ、外に出してやろう。";
			mes "ギオン様に結果を報告するように。";
			close2;
			warp "job_ko.gat",16,113;
			end;
		}
		if(!checkquest(5139)) {
			mes "[クウガ・カイ]";
			mes "久しぶりだな！";
			next;
			menu "あなたは……",-;
			mes "[クウガ・カイ]";
			mes "忍者への道を求めて";
			mes "俺のところへやって来たのが";
			mes "つい先日のことと思っていたが……。";
			next;
			mes "[クウガ・カイ]";
			mes "すでにここまで成長しているとは！";
			next;
			mes "[クウガ・カイ]";
			mes "ハッハッハッハッ！";
			mes "見込んだ通り根性があるな。";
			mes "気に入った！";
			next;
			mes "[クウガ・カイ]";
			mes "ここでは^339CCC知識の試練^000000を";
			mes "受けることができるぞ。";
			next;
			mes "[クウガ・カイ]";
			mes "ただ強くなっただけでなく";
			mes "知識も身につけているだろうな？";
			next;
			if(select("もちろんです","いいえ……") == 2) {
				setquest 5139;
				mes "[クウガ・カイ]";
				mes "根性だけでは乗り越えられぬぞ。";
				mes "準備ができたら";
				mes "また話しかけてくれ。";
				close;
			}
			setquest 5139;
		}
		mes "[クウガ・カイ]";
		mes "試練に挑む準備はいいか？";
		next;
		switch(select("はい","いいえ","外に出たい")) {
		case 1:
			break;
		case 2:
			mes "[クウガ・カイ]";
			mes "仕方ないな。";
			mes "もう少し待ってやろう。";
			close;
		case 3:
			mes "[クウガ・カイ]";
			mes "なんだと？";
			mes "試練を前にして引き返すなど";
			mes "言語道断！";
			next;
			mes "[クウガ・カイ]";
			mes "破門されても文句は言えぬところだが";
			mes "……まあ、今回だけは許そう。";
			mes "万全の準備をして、また来るがいい。";
			close2;
			warp "job_ko.gat",16,113;
			end;
		}
		mes "[クウガ・カイ]";
		mes "知識の試練のやり方は聞いているか？";
		next;
		mes "[クウガ・カイ]";
		mes "俺が出す問題を聞き";
		mes "正解と思うものを選べばいい。";
		mes "半端な正解数では";
		mes "試練は突破できんぞ。";
		next;
		mes "[クウガ・カイ]";
		mes "では試練をはじめるぞ！";
		next;
		for(set '@i,0; '@i<=47; set '@i,'@i+1)
			set '@list['@i],'@i;
		for(set '@i,1; '@i<=10; set '@i,'@i+1) {
			set '@r,rand(getarraysize('@list));
			set '@test,'@list['@r];
			deletearray '@list['@r],1;
			mes "[クウガ・カイ]";
			if('@i<10)
				mes "第" +'@i+ "問";
			else
				mes "最終問題";
			switch('@test) {
			case 0:
				mes "一閃スキルの攻撃力を高めるために";
				mes "最も影響のあるステータスを答えよ。";
				next;
				if(select("Vit","MaxHP","Int","MaxSP")==2)
					set '@m,'@m+1;
				break;
			case 1:
				mes "一閃スキルの攻撃力を高めるため";
				mes "靴に挿すカードとして";
				mes "次のうち最も効果的なカードを選べ。";
				next;
				if(select("ゴールドオシドスカード","マーターカード","タナトスの憎悪カード","エドガカード")==2)
					set '@m,'@m+1;
				break;
			case 2:
				mes "一閃を習得するために必要な";
				mes "投擲修練のレベルはいくつか？";
				next;
				if(select("5","7","6","8")==2)
					set '@m,'@m+1;
				break;
			case 3:
				mes "空蝉スキルの最大レベルを答えよ。";
				next;
				if(select("5","3","1","4")==1)
					set '@m,'@m+1;
				break;
			case 4:
				mes "火炎陣スキルがレベル10のとき、";
				mes "最大攻撃回数は？";
				next;
				if(select("7","8","9","10")==3)
					set '@m,'@m+1;
				break;
			case 5:
				mes "火炎陣スキルを使用するために必要な";
				mes "触媒を答えよ。";
				next;
				if(select("氷閃石","烈火石","風鈴石","影宝珠")==2)
					set '@m,'@m+1;
				break;
			case 6:
				mes "影跳びLv5の最大移動距離は何歩分か？";
				next;
				if(select("9歩","11歩","13歩","15歩")==1)
					set '@m,'@m+1;
				break;
			case 7:
				mes "影分身レベル10の回避回数と";
				mes "持続時間が正しいものはどれだ？";
				next;
				if(select("7回‐200秒","5回‐220秒","6回‐240秒","5回‐240秒")==4)
					set '@m,'@m+1;
				break;
			case 8:
				mes "霞斬りスキルがレベル4のときの";
				mes "攻撃力を答えよ。";
				next;
				if(select("140%","150%","160%","170%")==1)
					set '@m,'@m+1;
				break;
			case 9:
				mes "苦無投げ使用時";
				mes "打撃回数を答えよ。";
				next;
				if(select("2","3","4","5")==2)
					set '@m,'@m+1;
				break;
			case 10:
				mes "次の中から、朔風レベル4のとき";
				mes "Matkおよび射程距離が";
				mes "正しいものを選べ。";
				next;
				if(select("Matk400‐8歩","Matk500‐7歩","Matk500‐8歩","Matk400‐7歩")==3)
					set '@m,'@m+1;
				break;
			case 11:
				mes "手裏剣投げの基本攻撃距離は何歩分か？";
				next;
				if(select("7歩","8歩","9歩","10歩")==3)
					set '@m,'@m+1;
				break;
			case 12:
				mes "水遁スキルがレベル7のときの";
				mes "持続時間を答えよ。";
				next;
				if(select("40秒","45秒","50秒","55秒")==2)
					set '@m,'@m+1;
				break;
			case 13:
				mes "水遁スキルの効果でないものを";
				mes "次の中から選べ。";
				next;
				if(select("移動速度減少","ウォーターボール使用可能","アクアベネディクタ使用可能","Vit減少")==4)
					set '@m,'@m+1;
				break;
			case 14:
				mes "銭投げスキルを習得するために必要な";
				mes "投擲修練レベルを答えよ。";
				next;
				if(select("4","6","8","10")==4)
					set '@m,'@m+1;
				break;
			case 15:
				mes "銭投げがレベル6のとき";
				mes "スキル使用時に消費する金額を答えよ。";
				next;
				if(select("2000～8000Zeny","1000～6000Zeny","3000～8000Zeny","3000～6000Zeny")==4)
					set '@m,'@m+1;
				break;
			case 16:
				mes "銭投げスキルをマスターするために";
				mes "必要な総スキルポイント数を答えよ。";
				next;
				if(select("25","30","35","37")==3)
					set '@m,'@m+1;
				break;
			case 17:
				mes "畳返しスキルをマスターしたとき";
				mes "何歩先まで攻撃できるか答えよ。";
				next;
				if(select("5","7","3","1")==3)
					set '@m,'@m+1;
				break;
			case 18:
				mes "次のうち投擲修練スキルが";
				mes "レベル7のとき";
				mes "習得できないスキルを選べ。";
				next;
				if(select("苦無投げ","風魔手裏剣投げ","一閃","銭投げ")==4)
					set '@m,'@m+1;
				break;
			case 19:
				mes "投擲修練がレベル7のとき";
				mes "手裏剣投げに追加される";
				mes "攻撃力を答えよ。";
				next;
				if(select("18","21","27","30")==2)
					set '@m,'@m+1;
				break;
			case 20:
				mes "念スキルレベル5を使用したとき";
				mes "上昇するStrおよびIntの";
				mes "数値を答えよ。";
				next;
				if(select("4","5","6","7")==2)
					set '@m,'@m+1;
				break;
			case 21:
				mes "雷撃砕の属性で正しいものは？";
				next;
				if(select("火","水","地","風")==4)
					set '@m,'@m+1;
				break;
			case 22:
				mes "龍炎陣の攻撃範囲を答えよ。";
				next;
				if(select("3ｘ3","4ｘ4","5ｘ5","6ｘ6")==3)
					set '@m,'@m+1;
				break;
			case 23:
				mes "龍炎陣を習得するために必要な";
				mes "忍法修練のスキルレベルを答えよ。";
				next;
				if(select("10","9","8","1")==1)
					set '@m,'@m+1;
				break;
			case 24:
				mes "次のうち触媒を必要としない";
				mes "忍者スキルを答えよ。";
				next;
				if(select("火炎陣","水遁","紅炎華","氷柱落し")==3)
					set '@m,'@m+1;
				break;
			case 25:
				mes "次のうち地属性のモンスターに";
				mes "もっとも効果的なスキルを選べ。";
				next;
				if(select("朔風","龍炎陣","氷柱落し","風刃")==2)
					set '@m,'@m+1;
				break;
			case 26:
				mes "次のうち、スキルと属性の組み合わせで";
				mes "正しくないものを選べ。";
				next;
				if(select("紅炎華、火","氷柱落し、水","氷閃槍、地","雷撃砕、風")==3)
					set '@m,'@m+1;
				break;
			case 27:
				mes "モンスターポルセリオに対して";
				mes "もっとも大きなダメージを与えられる";
				mes "苦無を次の中から選べ。";
				next;
				if(select("烈火の苦無","氷柱の苦無","猛毒の苦無","狂風の苦無")==1)
					set '@m,'@m+1;
				break;
			case 28:
				mes "オークウォリアーと戦う際に";
				mes "一番効果的な苦無を";
				mes "次の中から選べ。";
				next;
				if(select("烈火の苦無","氷柱の苦無","猛毒の苦無","狂風の苦無")==1)
					set '@m,'@m+1;
				break;
			case 29:
				mes "村雨に宿る力で正しいものは？ ";
				next;
				if(select("人間形モンスターに攻撃力+10%","人間形モンスターにCri+10","悪魔形モンスターに攻撃力+10%","悪魔形モンスターにCri+10")==2)
					set '@m,'@m+1;
				break;
			case 30:
				mes "次のうち、風魔手裏剣・烈火に";
				mes "宿る力を選べ。";
				next;
				if(select("ファイアーボールLv5,Dex-2","ファイアーボールLv5,Dex-3","ファイアーボールLv3,Dex-2","ファイアーボールLv3,Dex-3")==1)
					set '@m,'@m+1;
				break;
			case 31:
				mes "氷柱の苦無10個を作るときに";
				mes "必要な材料を答えよ。";
				next;
				if(select("雨雲の手裏剣4個、氷閃石2個","雨雲の手裏剣8個、氷閃石2個","雨雲の手裏剣2個、氷閃石1個","雨雲の手裏剣1個、氷閃石2個")==2)
					set '@m,'@m+1;
				break;
			case 32:
				mes "次のうち、Strにポイントを";
				mes "割り振ったとき";
				mes "効果を得られないものを選べ。";
				next;
				if(select("近接攻撃力上昇","所持可能重量上昇","魔法攻撃力上昇","武器攻撃力上昇")==3)
					set '@m,'@m+1;
				break;
			case 33:
				mes "次のうち、Agiにポイントを";
				mes "割り振ったとき";
				mes "効果を得られないものを選べ。";
				next;
				if(select("命中率の上昇","回避率の上昇","攻撃速度の上昇","攻撃後ディレイの減少")==1)
					set '@m,'@m+1;
				break;
			case 34:
				mes "次のうち、Vitにポイントを";
				mes "割り振ったとき";
				mes "効果を得られないものを選べ。";
				next;
				if(select("物理防御力の上昇","MaxHPの増加","魔法防御力の上昇","魔法攻撃力の上昇")==4)
					set '@m,'@m+1;
				break;
			case 35:
				mes "次のうち、Intにポイントを";
				mes "割り振ったとき";
				mes "効果を得られないものを選べ。";
				next;
				if(select("MaxSPの上昇","Matkの上昇","SP回復量の上昇","杖の攻撃力上昇")==4)
					set '@m,'@m+1;
				break;
			case 36:
				mes "次のうち、Dexにポイントを";
				mes "割り振ったとき";
				mes "効果を得られないものを選べ。";
				next;
				if(select("詠唱時間の減少","回避率の上昇","命中率の上昇","遠距離攻撃力上昇")==2)
					set '@m,'@m+1;
				break;
			case 37:
				mes "次のうち、Lukにポイントを";
				mes "割り振ったとき";
				mes "効果を得られないものを選べ。";
				next;
				if(select("命中率の上昇","完全回避率の上昇","魔法攻撃力の減少","クリティカル発生率の上昇")==1)
					set '@m,'@m+1;
				break;
			case 38:
				mes "次のうち、大型モンスターに対して";
				mes "物理攻撃を行ったとき";
				mes "もっとも効果的な武器用カードを選べ。";
				next;
				if(select("ルナティックカード","ミノタウロスカード","スケルワーカーカード","デザートウルフカード")==2)
					set '@m,'@m+1;
				break;
			case 39:
				mes "次のうち、中型モンスターに対して";
				mes "物理攻撃を行ったとき";
				mes "もっとも効果的な武器用カードを選べ。";
				next;
				if(select("ルナティックカード","ミノタウロスカード","スケルワーカーカード","デザートウルフカード")==3)
					set '@m,'@m+1;
				break;
			case 40:
				mes "次のうち、小型モンスターに対して";
				mes "物理攻撃を行ったとき";
				mes "もっとも効果的な武器用カードを選べ。";
				next;
				if(select("ルナティックカード","ミノタウロスカード","スケルワーカーカード","デザートウルフカード")==4)
					set '@m,'@m+1;
				break;
			case 41:
				mes "カイバラが作れない武器を";
				mes "次の中から選べ。";
				next;
				if(select("黒鱗","村雨","白刃","風魔手裏剣・風鳥")==4)
					set '@m,'@m+1;
				break;
			case 42:
				mes "次のうち、忍者専用のアイテムを";
				mes "作ってくれる匠の名前ではない";
				mes "ものを選べ。";
				next;
				if(select("カイバラ","アイクゥ","テツ","トシュ")==2)
					set '@m,'@m+1;
				break;
			case 43:
				mes "忍者の最大JobLvはいくつだ？";
				next;
				if(select("70","50","99","100")==1)
					set '@m,'@m+1;
				break;
			case 44:
				mes "忍者屋敷がある街の名前を答えよ。";
				next;
				if(select("ルティエ","アマツ","デワタ","コモド")==2)
					set '@m,'@m+1;
				break;
			case 45:
				mes "忍者転職のときに";
				mes "俺が手紙を出した相手の";
				mes "名前を答えよ。";
				next;
				if(select("野良犬","野良猫","野羊","山羊")==3)
					set '@m,'@m+1;
				break;
			case 46:
				mes "初めて俺に会ったとき";
				mes "俺の隣に置いてあったものを答えよ。";
				next;
				if(select("座布団","掛け軸","植木鉢","火鉢")==4)
					set '@m,'@m+1;
				break;
			case 47:
				mes "忍者が転生をする時に";
				mes "会う必要がある人物を";
				mes "次の中から選べ。";
				next;
				if(select("ヴァルキリー","ランドグリス","無い","ヒョウ")==3)
					set '@m,'@m+1;
				break;
			case 48:
				mes "次のうち、転生を担当している";
				mes "NPCの名前で正しいものを選べ。";
				next;
				if(select("ヴァルキリー","バルキリー","ハラキリー","クウガ・カイ")==1)
					set '@m,'@m+1;
				break;
			case 49:
				mes "忍者JobLv70の時に";
				mes "加算されたDexとLukの合計値を答えよ。";
				next;
				if(select("8","10","12","14")==2)
					set '@m,'@m+1;
				break;
			}
		}
		mes "[クウガ・カイ]";
		mes "これで全問終了だ。";
		mes "採点するのでしばし待て。";
		next;
		mes "[クウガ・カイ]";
		mes "…………。";
		next;
		if('@m < 9) {
			mes "[クウガ・カイ]";
			mes "ふむ……";
			mes "期待していたほどではないな。";
			next;
			mes "[クウガ・カイ]";
			mes "さらなる極みに進むには";
			mes "まだまだだということだ。";
			next;
			mes "[クウガ・カイ]";
			mes "もう一度機会を与えてやる！";
			mes "出直してこい！";
			close;
		}
		mes "[クウガ・カイ]";
		mes '@m+ "0点か……。";
		mes "力ばかりを身につけたわけではないか。";
		mes "さすがだな。";
		next;
		mes "[クウガ・カイ]";
		mes "だが、この程度の試練を";
		mes "乗り越えたくらいでうぬぼれるなよ。";
		next;
		mes "[クウガ・カイ]";
		mes "まだまだ貴様が乗り越えるべき";
		mes "試練は残っているぞ。";
		next;
		mes "[クウガ・カイ]";
		mes "貴様の力で試練を乗り越えられるか";
		mes "見守らせてもらう。";
		next;
		compquest 5136;
		delquest 5139;
		mes "[クウガ・カイ]";
		mes "さあ、外に出してやろう。";
		mes "ギオン様に結果を報告するように。";
		close2;
		warp "job_ko.gat",16,113;
		end;
	}
}

function	script	jobchenge_ko_func	{
	set '@cost,getarg(0);
	set '@heal,getarg(1);
	setarray '@to_x,63,
				54,46,38,30,22,17,17,17,17,17,
				17,25,33,41,49,57,62,62,62,62,
				62,54,46,38,30,25,25,25,25,33,
				41,49,54,54,54,47,38,33,33,41;
	setarray '@to_y,16,
				16,16,16,16,16,19,27,35,43,51,
				60,60,60,60,60,60,56,48,40,32,
				23,23,23,23,23,28,35,43,52,52,
				52,52,48,40,31,31,31,35,44,44;
	mes "　保有LP：" +CHANGE_KO_LP;
	mes "　サイコロを振ると" +'@cost+ "^FD0260LP^000000を消費します‐";
	next;
	menu "サイコロを振る",-;
	set '@rand,rand(1,6);
	emotion 57+'@rand,"";
	mes "‐" +'@rand+ "が出ました。";
	mes "　" +'@rand+ "マス進みます‐";
	close2;
	set CHANGE_KO_LP,CHANGE_KO_LP - '@cost + '@heal;
	if(CHANGE_KO_LP > 100)
		set CHANGE_KO_LP,100;
	set CHANGE_KO_NOW,CHANGE_KO_NOW + '@rand;
	warp "job_ko.gat",'@to_x[CHANGE_KO_NOW],'@to_y[CHANGE_KO_NOW];
	end;
}

job_ko.gat,57,16,4	script	道標#ko_00	858,1,1,{
	mes "‐スタート地点";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	set CHANGE_KO_LP,100;
	set CHANGE_KO_NOW,0;
	if(!checkquest(5140)) {
		mes "‐小さく説明が書いてある‐";
		while(1) {
			next;
			if(select("説明を読む","試練を始める") == 1) {
				mes "‐生存の試練はスゴロク形式で";
				mes "　進行します。";
				mes "　開始時に100ポイントの";
				mes "　^FD0260生存の試練ポイント(LP)^000000が与えられ";
				mes "　1回サイコロを振るのに";
				mes "　1LPを消費します‐";
				next;
				mes "‐ゴールまで40マスあり";
				mes "　途中のコマで^FD0260LP^000000が増減する";
				mes "　イベントが発生します‐";
				next;
				mes "‐^FD0260LP^000000が0になるまでに";
				mes "　ゴールに到達してください‐";
				next;
				mes "‐なお、ゴール到着と同時に";
				mes "　^FD0260LP^000000が0になった場合は";
				mes "　ゴールを認めます‐";
				next;
				mes "‐生存の試練の説明は以上です‐";
				continue;
			}
			break;
		}
		setquest 5140;
		mes "‐生存の試練ポイント(LP)を";
		mes "　100獲得しました‐";
		next;
		mes "‐位置：スタート地点";
		callfunc "jobchenge_ko_func",1,0;
		end;
	}
	mes "‐スタート地点に戻ってきました。";
	mes "　LPが回復しました‐";
	while(1) {
		next;
		if(select("説明を読む","試練を始める") == 1) {
			mes "‐生存の試練はスゴロク形式で";
			mes "　進行します。";
			mes "　開始時に100ポイントの";
			mes "　^FD0260生存の試練ポイント(LP)^000000が与えられ";
			mes "　1回サイコロを振るのに";
			mes "　1LPを消費します‐";
			next;
			mes "‐ゴールまで40マスあり";
			mes "　途中のコマで^FD0260LP^000000が増減する";
			mes "　イベントが発生します‐";
			next;
			mes "‐^FD0260LP^000000が0になるまでに";
			mes "　ゴールに到達してください‐";
			next;
			mes "‐なお、ゴール到着と同時に";
			mes "　^FD0260LP^000000が0になった場合は";
			mes "　ゴールを認めます‐";
			next;
			mes "‐生存の試練の説明は以上です‐";
			continue;
		}
		break;
	}
	mes "‐位置：スタート地点";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,49,16,4	script	道標#ko_01	858,1,1,{
	mes "‐1番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐最初から1が出るとは";
	mes "　運がありませんね。";
	mes "　ここでは10^FD0260LP^000000を支払うことで";
	mes "　9番のマスに進むことができます‐";
	next;
	if(select("10LPを支払って9番に進む","支払わない")==1) {
		mes "‐10LP支払いました。";
		mes "　9番に進みます‐";
		close2;
		set CHANGE_KO_LP,CHANGE_KO_LP - 10;
		set CHANGE_KO_NOW,9;
		warp "job_ko.gat",17,43;
		end;
	}
	mes "‐位置：1番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,41,16,4	script	道標#ko_02	858,1,1,{
	mes "‐2番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐トラップが発動しました!!";
	mes "　スタート地点に戻ります‐";
	close2;
	warp "job_ko.gat",63,16;
	end;
}

job_ko.gat,33,16,4	script	道標#ko_03	858,1,1,{
	mes "‐3番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐先祖の呪いにかかった。";
	mes "　5^FD0260LP^000000を支払って";
	mes "　先祖の呪いをはらう必要があります‐";
	next;
	menu "5LPを支払う",-;
	mes "‐5LP支払った";
	mes "　サイコロを振ることができます‐";
	set CHANGE_KO_LP,CHANGE_KO_LP - 5;
	next;
	mes "‐位置：3番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,25,16,4	script	道標#ko_04	858,1,1,{
	mes "‐4番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さくラクガキが書いてある‐";
	next;
	mes "‐^0000FF" +'name$+ "^000000";
	mes "　生存の試練に挑む‐";
	next;
	mes "‐試練に挑む記念に";
	mes "　名前を残しますか？‐";
	next;
	if(select("5LP支払って名前を残す","支払わない") == 1) {
		mes "‐5LP支払った‐";
		set CHANGE_KO_LP,CHANGE_KO_LP - 5;
		set 'name$,strcharinfo(0);
		next;
		mes "‐" +strcharinfo(0);
		mes "　生存の試練に挑む。";
		mes "　名前を残しました。";
		mes "　サイコロを振ることができます‐";
		next;
	}
	mes "‐位置：4番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,17,16,4	script	道標#ko_05	858,1,1,{
	mes "‐5番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	if(checkquest(5141)) {
		if(!(checkquest(5141) & 0x2)) {
			mes "‐呪いのため、サイコロを";
			mes "　振ることができません‐";
			close;
		}
		mes "‐2分が経過し、呪いが解けました。";
		mes "　サイコロを振ることができます‐";
		next;
		delquest 5141;
		mes "‐位置：5番マス";
		callfunc "jobchenge_ko_func",1,0;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐5^FD0260LP^000000を支払わなければ";
	mes "　2分間サイコロを振ることができない";
	mes "　呪いにかかります‐";
	next;
	if(select("5LP支払う","支払わない") == 2) {
		setquest 5141;
		mes "‐2分間サイコロを振ることができない";
		mes "　呪いにかかりました‐";
		close;
	}
	mes "‐5LP支払いました。";
	mes "　サイコロを振ることができます‐";
	set CHANGE_KO_LP,CHANGE_KO_LP - 5;
	next;
	mes "‐位置：5番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,17,24,4	script	道標#ko_06	858,1,1,{
	mes "‐6番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐ラッキー！";
	mes "　次のマスに移動した時";
	mes "　生存の試練ポイントが7^FD0260LP^000000回復。";
	mes "　100^FD0260LP^000000を超えた分は回復しません‐";
	next;
	mes "‐位置：6番マス";
	callfunc "jobchenge_ko_func",1,7;
	end;
}

job_ko.gat,17,32,4	script	道標#ko_07	858,1,1,{
	mes "‐7番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐トラップが発動しました!!";
	mes "　5番に戻ります‐";
	close2;
	set CHANGE_KO_NOW,5;
	warp "job_ko.gat",22,16;
	end;
}

job_ko.gat,17,40,4	script	道標#ko_08	858,1,1,{
	mes "‐8番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐ジャンケンマシン";
	mes "　あなたが勝てば14番へ移動します。";
	mes "　引き分けたらサイコロを振ります。";
	mes "　負ければスタート地点へ戻ります‐";
	next;
	mes "ジャン！　ケン！　ポン！ ";
	next;
	set '@own,select("チョキを出す","グーを出す","パーを出す")-1;
	set '@enemy,rand(3);
	mes "――結果表示――";
	mes "マシン：" +(('@enemy==0)? "チョキ": (('@enemy==1)? "グー": "パー"));
	mes "あなた：" +(('@own==0)? "チョキ": (('@own==1)? "グー": "パー"));
	next;
	if('@own == '@enemy) {
		mes "‐Draw";
		mes "　引き分けです‐";
		next;
		mes "‐位置：8番マス";
		callfunc "jobchenge_ko_func",1,0;
		end;
	}
	if('@own != ('@enemy+1)%3) {
		mes "‐You Lose……";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐You Win !";
	mes "　14番に進みます‐";
	close2;
	set CHANGE_KO_NOW,14;
	warp "job_ko.gat",41,60;
	end;
}

job_ko.gat,17,48,4	script	道標#ko_09	858,1,1,{
	mes "‐9番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐さらに進んでください‐";
	next;
	mes "‐位置：9番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,17,56,4	script	道標#ko_10	858,1,1,{
	mes "‐10番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐やられる前にやれ‐";
	next;
	if('trap) {
		mes "‐設置されていたトラップが";
		mes "　発動しました！";
		mes "　スタートに戻ります‐";
		close2;
		set 'trap,0;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐現在トラップは設置されていません‐";
	next;
	mes "‐10^FD0260LP^000000支払うことで ";
	mes "　スタートに戻る";
	mes "　トラップを設置できます‐";
	next;
	if(select("トラップを設置する","設置せずサイコロを振る") == 1) {
		mes "‐10LP支払いました。";
		mes "　トラップを設置しました‐";
		set 'trap,1;
		set CHANGE_KO_LP,CHANGE_KO_LP - 10;
		next;
	}
	mes "‐位置：10番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,22,60,4	script	道標#ko_11	858,1,1,{
	mes "‐11番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐トラップが設置されています！ ";
	mes "　9番に戻ります‐";
	close2;
	set CHANGE_KO_NOW,9;
	warp "job_ko.gat",17,43;
	end;
}

job_ko.gat,30,60,4	script	道標#ko_12	858,1,1,{
	mes "‐12番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐ジャンケンマシン";
	mes "　あなたが勝てば20番へ移動します。";
	mes "　引き分けたらサイコロを振ります。";
	mes "　負ければ9番へ戻ります‐";
	next;
	mes "ジャン！　ケン！　ポン！";
	next;
	set '@own,select("チョキを出す","グーを出す","パーを出す")-1;
	set '@enemy,rand(3);
	mes "――結果表示――";
	mes "マシン：" +(('@enemy==0)? "チョキ": (('@enemy==1)? "グー": "パー"));
	mes "あなた：" +(('@own==0)? "チョキ": (('@own==1)? "グー": "パー"));
	next;
	if('@own == '@enemy) {
		mes "‐Draw";
		mes "　引き分けです‐";
		next;
		mes "‐位置：12番マス";
		callfunc "jobchenge_ko_func",1,0;
		end;
	}
	if('@own != ('@enemy+1)%3) {
		mes "‐You Lose……";
		mes "　9番に戻ります‐";
		close2;
		set CHANGE_KO_NOW,9;
		warp "job_ko.gat",17,43;
		end;
	}
	mes "‐You Win !";
	mes "　20番に進みます‐";
	close2;
	set CHANGE_KO_NOW,20;
	warp "job_ko.gat",62,32;
	end;
}

job_ko.gat,38,60,4	script	道標#ko_13	858,1,1,{
	mes "‐13番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐ラッキー！";
	mes "　次のマスに移動した時";
	mes "　生存の試練ポイントが7^FD0260LP^000000回復。";
	mes "　100^FD0260LP^000000を超えた分は回復しません‐";
	next;
	mes "‐位置：13番マス";
	callfunc "jobchenge_ko_func",1,7;
	end;
}

job_ko.gat,46,60,4	script	道標#ko_14	858,1,1,{
	mes "‐14番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	if(checkquest(5141)) {
		if(!(checkquest(5141) & 0x2)) {
			mes "‐呪いのため、サイコロを";
			mes "　振ることができません‐";
			close;
		}
		mes "‐2分が経過し、呪いが解けました。";
		mes "　サイコロを振ることができます‐";
		next;
		delquest 5141;
		mes "‐位置：14番マス";
		callfunc "jobchenge_ko_func",1,0;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐5^FD0260LP^000000を支払わなければ";
	mes "　2分間サイコロを振ることができない";
	mes "　呪いにかかります‐";
	next;
	if(select("5LP支払う","支払わない") == 2) {
		setquest 5141;
		mes "‐2分間サイコロを振ることができない";
		mes "　呪いにかかりました‐";
		close;
	}
	mes "‐5LP支払いました。";
	mes "　サイコロを振ることができます‐";
	set CHANGE_KO_LP,CHANGE_KO_LP - 5;
	next;
	mes "‐位置：14番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,54,60,4	script	道標#ko_15	858,1,1,{
	mes "‐15番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	if(checkquest(5141)) {
		if(!(checkquest(5141) & 0x2)) {
			mes "‐呪いのため進めません‐";
			close;
		}
		mes "‐2分が経過し、呪いが解けました。";
		mes "　サイコロを振ることができます‐";
		next;
		delquest 5141;
		mes "‐位置：15番マス";
		callfunc "jobchenge_ko_func",1,0;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐強力な呪いにかかり";
	mes "　2分間進めない状態に";
	mes "　なりました‐";
	setquest 5141;
	close;
}

job_ko.gat,62,60,4	script	道標#ko_16	858,1,1,{
	mes "‐16番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐2^FD0260LP^000000を消費しサイコロを2回振れ‐";
	next;
	mes "‐同じ目が出たら19番へ進む。";
	mes "　同じ目が出ない場合には、";
	mes "　同じ目が出るまで2^FD0260LP^000000を消費し";
	mes "　サイコロを2回振り続ける‐";
	while(1) {
		next;
		mes "‐位置：16番マス";
		mes "　保有LP：" +CHANGE_KO_LP;
		mes "　サイコロを振ると2^FD0260LP^000000を消費します‐";
		next;
		menu "1個目のサイコロを振る",-;
		mes "‐2LPを消費した‐";
		set CHANGE_KO_LP,CHANGE_KO_LP - 2;
		next;
		set '@dice1,rand(1,6);
		emotion 57+'@dice1,"";
		mes "‐" +'@dice1+ "が出ました。";
		mes "　2個目のサイコロを振ってください‐";
		next;
		menu "2個目のサイコロを振る",-;
		set '@dice2,rand(1,6);
		emotion 57+'@dice2,"";
		mes "‐" +'@dice2+ "が出ました。";
		if('@dice1 == '@dice2) {
			mes "　同じ目が出たため19番に進みます‐";
			close2;
			set CHANGE_KO_NOW,19;
			warp "job_ko.gat",62,40;
			end;
		}
		else {
			// 未調査
			mes "　同じ目が出なかったため";
			mes "　再度サイコロを振ります‐";
			continue;
		}
	}
}

job_ko.gat,62,51,4	script	道標#ko_17	858,1,1,{
	mes "‐17番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐呪いにかかってなんだか体が重い。";
	mes "　サイコロを振るために10^FD0260LP^000000消費します‐";
	next;
	mes "‐位置：17番マス";
	callfunc "jobchenge_ko_func",10,0;
	end;
}

job_ko.gat,62,43,4	script	道標#ko_18	858,1,1,{
	mes "‐18番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐2^FD0260LP^000000を消費しサイコロを2回振れ‐";
	next;
	mes "‐2回の合計が5未満ならば24番へ進む。";
	mes "　5以上ならば19番に進む‐";
	next;
	mes "‐位置：18番マス";
	mes "　保有LP：" +CHANGE_KO_LP;
	mes "　サイコロを振ると2^FD0260LP^000000を消費します‐";
	next;
	menu "1個目のサイコロを振る",-;
	mes "‐2LPを消費した‐";
	set CHANGE_KO_LP,CHANGE_KO_LP - 2;
	next;
	set '@dice1,rand(1,6);
	emotion 57+'@dice1,"";
	mes "‐" +'@dice1+ "が出ました。";
	mes "　2個目のサイコロを振ってください‐";
	next;
	menu "2個目のサイコロを振る",-;
	set '@dice2,rand(1,6);
	emotion 57+'@dice2,"";
	mes "‐" +'@dice2+ "が出ました。";
	next;
	if(('@dice1+'@dice2) >= 5) {
		mes '@dice1+ " + " +'@dice2+ " = " +('@dice1+'@dice2);
		mes "‐2個の合計が5以上でした。";
		mes "　19番に進みます‐";
		close2;
		set CHANGE_KO_NOW,19;
		warp "job_ko.gat",62,40;
		end;
	}
	else {
		// 未調査
		mes "‐2個の合計が5未満でした。";
		mes "　24番に進みます‐";
		close2;
		set CHANGE_KO_NOW,24;
		warp "job_ko.gat",38,23;
		end;
	}
}

job_ko.gat,62,35,4	script	道標#ko_19	858,1,1,{
	mes "‐19番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐さらに進んでください‐";
	next;
	mes "‐位置：19番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,62,27,4	script	道標#ko_20	858,1,1,{
	mes "‐20番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐ラッキー！";
	mes "　次のマスに移動した時";
	mes "　生存の試練ポイントが7^FD0260LP^000000回復。";
	mes "　100^FD0260LP^000000を超えた分は回復しません‐";
	next;
	mes "‐位置：20番マス";
	callfunc "jobchenge_ko_func",1,7;
	end;
}

job_ko.gat,57,23,4	script	道標#ko_21	858,1,1,{
	mes "‐21番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐呪いにかかってなんだか体が重い。";
	mes "　サイコロを振るために10^FD0260LP^000000消費します‐";
	next;
	mes "‐位置：21番マス";
	callfunc "jobchenge_ko_func",10,0;
	end;
}

job_ko.gat,49,23,4	script	道標#ko_22	858,1,1,{
	mes "‐22番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐残りの^FD0260LP^000000を全て寄付し";
	mes "　スタート地点に戻れば";
	mes "　次にここを踏む者は救われるだろう‐";
	next;
	if('trap) {
		mes "‐親切な誰かが自分の^FD0260LP^000000を";
		mes "　寄付していました。";
		mes "　ゴール地点まで進みます‐";
		close2;
		set 'trap,0;
		warp "job_ko.gat",41,44;
		end;
	}
	mes "‐^FD0260LP^000000を全て寄付すると";
	mes "　次にここに止まった人は";
	mes "　ゴール地点へ進めます。";
	mes "　^FD0260LP^000000を全て寄付しますか？‐";
	next;
	if(select("LPを全て寄付する","寄付しない") == 1) {
		mes "‐残りの^FD0260LP^000000を全て寄付しました。";
		mes "　スタート地点に戻ります‐";
		close2;
		set 'trap,1;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐位置：22番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,41,23,4	script	道標#ko_23	858,1,1,{
	mes "‐23番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐トラップが発動しました!!";
	mes "　17番に戻ります‐";
	close2;
	set CHANGE_KO_NOW,17;
	warp "job_ko.gat",62,55;
	end;
}

job_ko.gat,33,23,4	script	道標#ko_24	858,1,1,{
	mes "‐24番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐2^FD0260LP^000000を消費しサイコロを2回振れ‐";
	next;
	mes "‐2回の合計が9以上ならば";
	mes "　25番～30番の好きな場所に進む。";
	mes "　8以下ならば19番に戻る‐";
	next;
	mes "‐位置：24番マス";
	mes "　保有LP：" +CHANGE_KO_LP;
	mes "　サイコロを振ると2^FD0260LP^000000を消費します‐";
	next;
	menu "1個目のサイコロを振る",-;
	mes "‐2LPを消費した‐";
	set CHANGE_KO_LP,CHANGE_KO_LP - 2;
	next;
	set '@dice1,rand(1,6);
	emotion 57+'@dice1,"";
	mes "‐" +'@dice1+ "が出ました。";
	mes "　2個目のサイコロを振ってください‐";
	next;
	menu "2個目のサイコロを振る",-;
	set '@dice2,rand(1,6);
	emotion 57+'@dice2,"";
	mes "‐" +'@dice2+ "が出ました。";
	next;
	if(('@dice1+'@dice2) >= 9) {
		mes '@dice1+ " + " +'@dice2+ " = " +('@dice1+'@dice2);
		mes "‐2個の合計が9以上でした。";
		mes "　25番～30番の好きな場所に進みます‐";
		next;
		switch(select("25番へ","26番へ","27番へ","28番へ","29番へ","30番へ")) {
		case 1: set CHANGE_KO_NOW,25; warp "job_ko.gat",30,23; break;
		case 2: set CHANGE_KO_NOW,26; warp "job_ko.gat",25,28; break;
		case 3: set CHANGE_KO_NOW,27; warp "job_ko.gat",25,35; break;
		case 4: set CHANGE_KO_NOW,28; warp "job_ko.gat",25,43; break;
		case 5: set CHANGE_KO_NOW,29; warp "job_ko.gat",25,52; break;
		case 6: set CHANGE_KO_NOW,30; warp "job_ko.gat",33,52; break;
		}
		end;
	}
	else {
		mes "‐2個の合計が8以下でした。";
		mes "　19番に戻ります‐";
		close2;
		set CHANGE_KO_NOW,19;
		warp "job_ko.gat",62,40;
		end;
	}
}

job_ko.gat,25,23,4	script	道標#ko_25	858,1,1,{
	mes "‐25番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	if(checkquest(5141)) {
		if(!(checkquest(5141) & 0x2)) {
			mes "‐呪いのため進めません‐";
			close;
		}
		mes "‐2分が経過し、呪いが解けました。";
		mes "　サイコロを振ることができます‐";
		next;
		delquest 5141;
		mes "‐位置：25番マス";
		callfunc "jobchenge_ko_func",1,0;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐ここでは寒……";
	mes "　文字がかすれてよく見えない。";
	mes "　どうしようか？‐";
	next;
	if(select("何か芸をする","何もしない") == 1) {
		// スキルではなく寒いジョークを発言するだけ
		mes "‐プロンテラで流行している";
		mes "　寒いジョークを放った！‐";
		next;
		setquest 5141;
		mes "‐2分間進めない";
		mes "　呪いにかかってしまった……‐";
		close;
	}
	if(rand(6)) {
		mes "‐何も起こらない……";
		mes "　芸でもするべきだろうか？‐";
		close;
	}
	mes "‐何もしなかったのが";
	mes "　正しい選択だったようだ‐";
	next;
	mes "‐位置：25番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,25,32,4	script	道標#ko_26	858,1,1,{
	mes "‐26番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐トラップが発動しました!!";
	mes "　20番に戻ります‐";
	close2;
	set CHANGE_KO_NOW,20;
	warp "job_ko.gat",62,32;
	end;
}

job_ko.gat,25,40,4	script	道標#ko_27	858,1,1,{
	mes "‐27番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐ラッキー！";
	mes "　次のマスに移動した時";
	mes "　生存の試練ポイントが7^FD0260LP^000000回復。";
	mes "　100^FD0260LP^000000を超えた分は回復しません‐";
	next;
	mes "‐位置：27番マス";
	callfunc "jobchenge_ko_func",1,7;
	end;
}

job_ko.gat,25,48,4	script	道標#ko_28	858,1,1,{
	mes "‐28番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐やられる前にやれ‐";
	next;
	if('trap) {
		mes "‐設置されていたトラップが";
		mes "　発動しました！";
		mes "　スタートに戻ります‐";
		close2;
		set 'trap,0;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐現在トラップは設置されていません‐";
	next;
	mes "‐10^FD0260LP^000000支払うことで ";
	mes "　スタートに戻る";
	mes "　トラップを設置できます‐";
	next;
	if(select("トラップを設置する","設置せずサイコロを振る") == 1) {
		mes "‐10LP支払いました。";
		mes "　トラップを設置しました‐";
		set 'trap,1;
		set CHANGE_KO_LP,CHANGE_KO_LP - 10;
		next;
	}
	mes "‐位置：28番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,30,52,4	script	道標#ko_29	858,1,1,{
	mes "‐29番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐残り11マス。";
	mes "　前進せよ‐";
	next;
	mes "‐位置：29番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,38,52,4	script	道標#ko_30	858,1,1,{
	mes "‐30番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐トラップが発動しました!!";
	mes "　9番に戻ります‐";
	close2;
	set CHANGE_KO_NOW,9;
	warp "job_ko.gat",17,43;
	end;
}

job_ko.gat,46,52,4	script	道標#ko_31	858,1,1,{
	mes "‐31番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	if(checkquest(5141)) {
		if(!(checkquest(5141) & 0x2)) {
			mes "‐呪いのため、サイコロを";
			mes "　振ることができません‐";
			close;
		}
		mes "‐2分が経過し、呪いが解けました。";
		mes "　サイコロを振ることができます‐";
		next;
		delquest 5141;
		mes "‐位置：31番マス";
		callfunc "jobchenge_ko_func",1,0;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐5^FD0260LP^000000を支払わなければ";
	mes "　2分間サイコロを振ることができない";
	mes "　呪いにかかります‐";
	next;
	if(select("5LP支払う","支払わない") == 2) {
		setquest 5141;
		mes "‐2分間サイコロを振ることができない";
		mes "　呪いにかかりました‐";
		close;
	}
	mes "‐5LP支払いました。";
	mes "　サイコロを振ることができます‐";
	set CHANGE_KO_LP,CHANGE_KO_LP - 5;
	next;
	mes "‐位置：31番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,54,52,4	script	道標#ko_32	858,1,1,{
	mes "‐32番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐ジャンケンマシン";
	mes "　あなたが勝てば33番～38番の";
	mes "　好きな場所に進む。";
	mes "　負けまたは引き分けの場合";
	mes "　スタート地点へ戻ります‐";
	next;
	mes "ジャン！　ケン！　ポン！";
	next;
	set '@own,select("チョキを出す","グーを出す","パーを出す")-1;
	set '@enemy,rand(3);
	mes "――結果表示――";
	mes "マシン：" +(('@enemy==0)? "チョキ": (('@enemy==1)? "グー": "パー"));
	mes "あなた：" +(('@own==0)? "チョキ": (('@own==1)? "グー": "パー"));
	next;
	if('@own == '@enemy) {
		// 未調査
		mes "‐Draw";
		mes "　引き分けです";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	if('@own != ('@enemy+1)%3) {
		// 未調査
		mes "‐You Lose……";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐You Win !";
	mes "　33～38の進みたいマスを";
	mes "　選んでください‐";
	next;
	switch(select("33番へ","34番へ","35番へ","36番へ","37番へ","38番へ")) {
	case 1: set CHANGE_KO_NOW,33; warp "job_ko.gat",54,48; break;
	case 2: set CHANGE_KO_NOW,34; warp "job_ko.gat",54,40; break;
	case 3: set CHANGE_KO_NOW,35; warp "job_ko.gat",54,31; break;
	case 4: set CHANGE_KO_NOW,36; warp "job_ko.gat",47,31; break;
	case 5: set CHANGE_KO_NOW,37; warp "job_ko.gat",38,31; break;
	case 6: set CHANGE_KO_NOW,38; warp "job_ko.gat",33,35; break;
	}
	end;
}

job_ko.gat,54,43,4	script	道標#ko_33	858,1,1,{
	mes "‐33番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐最後のサイコロを振るための";
	mes "　1^FD0260LP^000000を除くポイントを";
	mes "　全て支払えば39番に進めます‐";
	next;
	if(select("支払う","支払わない") == 1) {
		mes "‐" +(CHANGE_KO_LP-1)+ "LP支払った";
		mes "　39番に進みます‐";
		close2;
		set CHANGE_KO_LP,1;
		set CHANGE_KO_NOW,39;
		warp "job_ko.gat",33,44;
		end;
	}
	mes "‐サイコロを振ってください‐";
	next;
	mes "‐位置：33番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,54,35,4	script	道標#ko_34	858,1,1,{
	mes "‐34番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐ラッキー！";
	mes "　次のマスに移動した時";
	mes "　生存の試練ポイントが7^FD0260LP^000000回復。";
	mes "　100^FD0260LP^000000を超えた分は回復しません‐";
	next;
	mes "‐位置：34番マス";
	callfunc "jobchenge_ko_func",1,7;
	end;
}

job_ko.gat,49,31,4	script	道標#ko_35	858,1,1,{
	mes "‐35番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐設置されていたトラップが";
	mes "　発動しました！";
	mes "　29番に戻ります‐";
	close2;
	set CHANGE_KO_NOW,29;
	warp "job_ko.gat",25,52;
	end;
}

job_ko.gat,41,31,4	script	道標#ko_36	858,1,1,{
	mes "‐36番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐残り4マス‐";
	next;
	mes "‐4以上の目が出ればゴール地点に";
	mes "　たどり着けるが";
	mes "　もうひとつのルールを選んでもよい‐";
	next;
	mes "‐もうひとつのルールは";
	mes "　1,2,3が出ればゴール地点に進み";
	mes "　4,5,6が出れば29番に戻る。";
	mes "　このルールを使用せず";
	mes "　普通にサイコロを振ってもよい‐";
	next;
	if(select("もうひとつのルールを使用する","普通にサイコロを振る") == 1) {
		mes "‐位置：36番マス";
		mes "　保有LP：" +CHANGE_KO_LP;
		mes "　サイコロを振ると1^FD0260LP^000000を消費します‐";
		next;
		menu "サイコロを振る",-;
		set '@dice,rand(1,6);
		emotion 57+'@dice,"";
		set CHANGE_KO_LP,CHANGE_KO_LP - 1;
		mes "‐" +'@dice+ "が出ました。";
		if('@dice <= 3) {
			mes "　ゴール地点に進みます‐";
			close2;
			warp "job_ko.gat",41,44;
			end;
		}
		else {
			mes "　29番に戻ります‐";
			close2;
			set CHANGE_KO_NOW,29;
			warp "job_ko.gat",25,52;
			end;
		}
	}
	mes "‐位置：36番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,33,31,4	script	道標#ko_37	858,1,1,{
	mes "‐37番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐残り3マス‐";
	next;
	mes "‐奇数が出ればゴール地点に進む。";
	mes "　しかし、偶数が出れば";
	mes "　スタート地点に戻る‐";
	next;
	mes "‐位置：37マス";
	mes "　保有LP：" +CHANGE_KO_LP;
	mes "　サイコロを振ると1^FD0260LP^000000を消費します‐";
	next;
	menu "サイコロを振る",-;
	set '@dice,rand(1,6);
	emotion 57+'@dice,"";
	set CHANGE_KO_LP,CHANGE_KO_LP - 1;
	mes "‐" +'@dice+ "が出ました。";
	if('@dice%2) {
		mes "　ゴール地点に進みます‐";
		close2;
		warp "job_ko.gat",41,44;
		end;
	}
	else {
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
}

job_ko.gat,33,40,4	script	道標#ko_38	858,1,1,{
	mes "‐38番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐1^FD0260LP^000000を残し、全ての^FD0260LP^000000を支払うことで";
	mes "　スタートに戻る";
	mes "　トラップを設置できます‐";
	next;
	if('trap) {
		mes "‐設置されていたトラップが";
		mes "　発動しました！";
		mes "　スタートに戻ります‐";
		close2;
		set 'trap,0;
		warp "job_ko.gat",63,16;
		end;
	}
	if(select("トラップを設置する","設置せずサイコロを振る") == 1) {
		mes "‐" +(CHANGE_KO_LP-1)+ "LP支払いました。";
		mes "　トラップを設置しました‐";
		set 'trap,1;
		set CHANGE_KO_LP,1;
		next;
	}
	mes "‐位置：38番マス";
	callfunc "jobchenge_ko_func",1,0;
	end;
}

job_ko.gat,38,44,4	script	道標#ko_39	858,1,1,{
	mes "‐39番マス";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	if(CHANGE_KO_LP <= 0) {
		mes "‐^FD0260LP^000000が足りません。";
		mes "　スタート地点に戻ります‐";
		close2;
		warp "job_ko.gat",63,16;
		end;
	}
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐残り1マス。";
	mes "　長い道のりだったことだろう‐";
	next;
	mes "‐だが簡単に通す訳にはいかない。";
	mes "　3が出たら3番に戻ってもらう‐";
	next;
	mes "‐位置：39番マス";
	mes "　保有LP：" +CHANGE_KO_LP;
	mes "　サイコロを振ると1^FD0260LP^000000を消費します‐";
	next;
	menu "サイコロを振る",-;
	set '@dice,rand(1,6);
	emotion 57+'@dice,"";
	set CHANGE_KO_LP,CHANGE_KO_LP - 1;
	mes "‐" +'@dice+ "が出ました。";
	if('@dice == 3) {
		mes "　3番に戻ります‐";
		close2;
		set CHANGE_KO_NOW,3;
		warp "job_ko.gat",38,16;
		end;
	}
	else {
		mes "　ゴール地点に進みます‐";
		close2;
		warp "job_ko.gat",41,44;
		end;
	}
}

job_ko.gat,46,41,4	script	道標#ko_40	858,1,1,{
	mes "‐ゴール";
	mes "　^1A95E6他の文字は小さくて見えない。";
	mes "　もっと近づいてみよう^000000‐";
	close;
OnTouch:
	mes "‐小さく説明が書いてある‐";
	next;
	mes "‐さらなる極みへ歩むものへ";
	mes "　勇気ある始まりの歩みを踏み出した";
	mes "　汝らに祝福を！‐";
	next;
	compquest 5137;
	delquest 5140;
	mes "‐生存の試練を達成した‐";
	close2;
	warp "job_ko.gat",35,113;
	end;
}

job_ko.gat,127,125,4	script	ヒョウ#ko	730,{
	if(checkquest(5138)) {
		if(checkquest(5138) & 0x8) {
			mes "[ヒョウ]";
			mes "そうそう";
			mes "ギオン様に報告するのを";
			mes "忘れないでくださいね。";
			close2;
			warp "job_ko.gat",26,104;
			end;
		}
		if(!checkquest(5142)) {
			mes "[ヒョウ]";
			mes "久しぶりですね。";
			next;
			menu "お久しぶりです",-;
			mes "[ヒョウ]";
			mes "すっかり忘れられたかと思いましたが";
			mes "その様子では、";
			mes "憶えていてくれたようですね。";
			next;
			mes "[ヒョウ]";
			mes "さて、積もる話もありますが……";
			mes "今はそのような悠長なことを";
			mes "話している場合では、";
			mes "ありませんでしたね。";
			next;
			mes "[ヒョウ]";
			mes "では、あらためて！";
			mes strcharinfo(0);
			mes "一族の武器工房へようこそ！";
			next;
			mes "[ヒョウ]";
			mes "昔から私たちの一族は";
			mes "隠密として任務を遂行するために";
			mes "自分たち独自の武器を作ってきました。";
			next;
			menu "それでアインブロックに？",-;
			mes "[ヒョウ]";
			mes "……ほう、まだ憶えていましたか。";
			next;
			mes "[ヒョウ]";
			mes "その通りです。";
			mes "鋼鉄の都市アインブロックは";
			mes "腕利きの匠が多いため";
			mes "新しい技術も頻繁に生まれます。";
			next;
			mes "[ヒョウ]";
			mes "私の任務は";
			mes "そういった新しい技術を習得、分析して";
			mes "一族に報告をすることでした。";
			next;
			mes "[ヒョウ]";
			mes "おっと……";
			mes "少し口が滑りました。";
			next;
			mes "[ヒョウ]";
			mes "それはさておき";
			mes "^6848B7鉄鉱石、鉄、鋼鉄、プラコン、";
			mes "エンベルタコン、オリデオコン原石、";
			mes "エルニウム原石^000000は";
			mes "十分持っていますか？";
			next;
			mes "[ヒョウ]";
			mes "さっそく新しい武器の";
			mes "試作品を作ってみましょう。";
			next;
			misceffect 191,"製作道具#ko_01";
			mes "[ヒョウ]";
			mes "製作道具はそこと……";
			next;
			misceffect 191,"製作道具#ko_02";
			mes "[ヒョウ]";
			mes "ここ……";
			next;
			misceffect 191,"製作道具#ko_03";
			setquest 5142;
			mes "[ヒョウ]";
			mes "それから、向こうにあるものを";
			mes "自由に使ってください。";
			next;
			mes "[ヒョウ]";
			mes "武器の作り方について";
			mes "説明を聞きたい場合には";
			mes "もう一度、私に話しかけてください。";
			mes "それでは、始めてください。";
			close;
		}
		if(checkquest(5145)) {
			mes "[ヒョウ]";
			mes "満足できる成果は得られましたか？";
			next;
			switch(select("まだです","できました","壊れてしまった")) {
			case 1:
				mes "[ヒョウ]";
				mes "満足できる成果は";
				mes "簡単には得られませんからね。";
				close;
			case 2:
				mes "[ヒョウ]";
				mes "いい結果が得られたみたいですね。";
				next;
				if(getequipid(4) != 13074 && getequipid(4) != 13312) {
					mes "[ヒョウ]";
					mes "おや……。";
					next;
					mes "[ヒョウ]";
					mes "すみません。";
					mes "あなたが鍛えた武器を";
					mes "装備していただけますか。";
					mes "確認しますので。";
					close;
				}
				mes "[ヒョウ]";
				mes "では確認させてもらいましょう。";
				next;
				mes "‐ヒョウは武器を手に取って";
				mes "　観察している‐";
				next;
				set '@ref,getequiprefinerycnt(4);
				if('@ref < 7) {
					mes "[ヒョウ]";
					mes "なるほど。";
					mes "良い感じですが、";
					mes "もう少し、鍛える必要がありますね。";
					mes "がんばってください。";
					close;
				}
				else if('@ref < 9) {
					mes "[ヒョウ]";
					mes "なかなかやりますね。";
					mes "これなら合格を出せそうです。";
					mes "とはいえ、まだ強化可能ですが";
					mes "これで完成でよいですか？";
					next;
					if(select("はい","いいえ") == 2) {
						mes "[ヒョウ]";
						mes "では、満足できる結果が得られたら";
						mes "また来てください。";
						close;
					}
				}
				else if('@ref == 9) {
					mes "[ヒョウ]";
					mes "素晴らしい……。";
					mes "文句なしの合格ですよ。";
					mes "ここまでの出来なら";
					mes "最高峰を目指していただきたい";
					mes "そんな欲が出てきた程です。";
					next;
					mes "[ヒョウ]";
					mes "どうでしょう？";
					mes "あなたがよいのでしたら";
					mes "是非、最高峰を目指して";
					mes "がんばっていただきたいのですが。";
					next;
					if(select("これくらいにします","まだまだ満足できません") == 2) {
						mes "[ヒョウ]";
						mes "あなたの腕前に";
						mes "期待させてもらいますよ。";
						close;
					}
				}
				else if('@ref >= 10) {
					// 未調査
					mes "[ヒョウ]";
					mes "素晴らしい！";
					mes "文句なしの合格です！";
					next;
				}
				mes "[ヒョウ]";
				mes "あなたの腕前に関しては十分";
				mes "確認できました。";
				mes "この武器の仕上げは私がやりましょう。";
				mes "いったん預かりますよ。";
				next;
				delequip 4;
				delquest 5145;
				compquest 5138;
				delquest 5142;
				if(checkquest(5143))
					compquest 5143;
				if(checkquest(5144))
					compquest 5144;
				mes "[ヒョウ]";
				mes strcharinfo(0)+ "の";
				mes "武器の試練を終了します！";
				close;
			case 3:
				mes "[ヒョウ]";
				mes "忠告したはずですが……";
				next;
				mes "[ヒョウ]";
				mes "仕方がありませんね。";
				mes "少し確認させてもらいますよ。";
				next;
				mes "‐装備が全て外れた！";
				mes "　ヒョウが何かをしたのだろうか？‐";
				next;
				unequip;
				if(countitem(13074) > 0 || countitem(13312) > 0) {
					mes "[ヒョウ]";
					mes "おや……？";
					mes "試作品を持っているじゃありませんか。";
					close;
				}
				mes "[ヒョウ]";
				mes "ふむ……";
				mes "本当になくしてしまったようですね。";
				next;
				setquest 5142;
				delquest 5143;
				delquest 5144;
				delquest 5145;
				mes "[ヒョウ]";
				mes "しかたありません。";
				mes "もう一度、試作品から作ってください。";
				close;
			}
		}
		mes "[ヒョウ]";
		mes "新しい武器の試作品は";
		mes "完成しましたか？";
		if(checkquest(5143) || checkquest(5144))
			set '@str$,"はい、完成しました";
		next;
		switch(select("製作道具について聞く","材料が足りない","作り方を聞く",'@str$)) {
		case 1:
			misceffect 191,"製作道具#ko_01";
			mes "[ヒョウ]";
			mes "これから示す場所に";
			mes "製作道具があります。";
			mes "まずはひとつ目。";
			next;
			misceffect 191,"製作道具#ko_02";
			mes "[ヒョウ]";
			mes "ふたつ目。";
			next;
			misceffect 191,"製作道具#ko_03";
			mes "[ヒョウ]";
			mes "最後にみっつ目。";
			mes "好きなところを使ってください。";
			close;
		case 2:
			mes "[ヒョウ]";
			mes "材料が足りないのですか？";
			next;
			misceffect 191,"タンス#ko";
			mes "[ヒョウ]";
			mes "街に戻る必要があるみたいですね。";
			mes "そこのタンスを調べてみてください。";
			close;
		case 3:
			mes "[ヒョウ]";
			mes "ふむ、やはり説明が必要ですかね？";
			next;
			mes "[ヒョウ]";
			mes "まずは鉱石を溶かします。";
			mes "純度が高い金属を作るためには";
			mes "同じ種類の鉱石を使うといいでしょう。";
			mes "途中で鉱石が足りなくなると";
			mes "やり直しになってしまうので";
			mes "十分な数の鉱石を用意してください。";
			next;
			mes "[ヒョウ]";
			mes "また、希少性の高い鉱石ほど";
			mes "少ない個数で純度の高い金属を";
			mes "作ることができます。";
			next;
			mes "[ヒョウ]";
			mes "そうですね……";
			mes "同じ鉱石を溶かし続けた場合、";
			mes "鉄鉱石やプラコンなら^FF000050^000000個";
			mes "鉄やエンベルタコンなら^FF000025^000000個";
			mes "鋼鉄やオリデオコン原石なら^FF000017^000000個";
			mes "あれば十分でしょう。";
			next;
			mes "[ヒョウ]";
			mes "ですが、これらの個数は";
			mes "あくまで目安です。";
			mes "溶かす鉱石の組み合わせ次第で";
			mes "必要になる個数は変わりますから";
			mes "注意してくださいね。";
			next;
			mes "[ヒョウ]";
			mes "また、鉱石の性質についても";
			mes "注意してください。";
			mes "たとえば鉄鉱石、鉄、鋼鉄は";
			mes "性質が似ているため";
			mes "混ぜ合わせて溶かしても";
			mes "純度の高い金属ができるでしょう。";
			next;
			mes "[ヒョウ]";
			mes "プラコン、エンベルタコン";
			mes "オリデオコン原石も";
			mes "それぞれ性質が似ていますので";
			mes "同じことが言えます。";
			next;
			mes "[ヒョウ]";
			mes "ただし！";
			mes "これらの性質は相反するので";
			mes "^FF0000異なる性質の鉱石を溶かすと";
			mes "高めた純度が落ちてしまいます^000000。";
			next;
			mes "[ヒョウ]";
			mes "なお、エルニウム原石は";
			mes "特殊な性質を持っていて";
			mes "どちらの性質の金属に溶かしても";
			mes "わずかながら純度を";
			mes "高めることができます。";
			next;
			mes "[ヒョウ]";
			mes "純度の高い金属を用意できたら";
			mes "鋳型に流しこんでください。";
			next;
			mes "[ヒョウ]";
			mes "そして、研磨と焼入れを";
			mes "繰り返して金属を強化し";
			mes "最後に仕上げをしてください。";
			next;
			mes "[ヒョウ]";
			mes "強化が不十分だと";
			mes "試作品が壊れやすくなります。";
			mes "研磨と焼入れを十分に行ってから";
			mes "仕上げに移ってください。";
			next;
			mes "[ヒョウ]";
			mes "参考までに、研磨と焼入れを";
			mes "交互に作業するのが";
			mes "良い武器を作る最適な方法です。";
			next;
			mes "[ヒョウ]";
			mes "ここまで説明すれば十分ですね？";
			mes "さあ、試作品を作ってみましょう！";
			close;
		case 4:
			if(checkquest(5143)) {
				mes "[ヒョウ]";
				mes "ほう……";
				mes "苦無をまねた短剣の類ですか？";
				next;
				mes "[ヒョウ]";
				mes "面白い発想ですね。";
			}
			else if(checkquest(5144)) {
				mes "[ヒョウ]";
				mes "これは風魔手裏剣……？";
				mes "いやいや……";
				next;
				mes "[ヒョウ]";
				mes "平凡な風魔手裏剣ではありませんね！";
			}
			mes "少し鍛え直さないと";
			mes "武器として使うのは厳しいですが";
			mes "いい武器になる可能性を感じますね。";
			next;
			mes "[ヒョウ]";
			mes "よし、これなら合格点を出せますね。";
			next;
			mes "[ヒョウ]";
			mes "次に、武器の強化ですね。";
			mes "私の下の方に精錬装置があります。";
			mes "^0000FF精錬値が+7^000000になったら";
			mes "持ってきてください。";
			next;
			mes "[ヒョウ]";
			mes "それ以上精錬しても構いませんが";
			mes "^FF0000特別な報酬などはありません^000000から";
			mes "注意してくださいね。";
			next;
			mes "[ヒョウ]";
			mes "そうそう、精錬は必ず";
			mes "^FF0000この部屋の精錬装置で";
			mes "行なって下さい。^000000";
			next;
			mes "[ヒョウ]";
			mes "なお、ここにある精錬装置ですが";
			mes "鋼鉄の都市アインブロックの";
			mes "腕利きの匠により";
			mes "製作された精錬装置ですので";
			next;
			mes "[ヒョウ]";
			mes "他の場所で精錬した場合と";
			mes "精錬の成功率が";
			mes "異なっているようです。";
			mes "注意してください。";
			next;
			mes "[ヒョウ]";
			mes "また、^0000FFこの部屋の精錬装置で";
			mes "精錬に失敗しても";
			mes "武器は壊れません^000000。";
			next;
			mes "[ヒョウ]";
			mes "ですが、他の人に頼んだり";
			mes "ここではない場所で精錬に失敗して";
			mes "^FF0000試作品を壊すとやり直し^000000になるので";
			mes "絶対壊さないようにね。";
			setquest 5145;
			close;
		}
	}
}

job_ko.gat,117,128,0	script	タンス#ko	844,{
	mes "‐見たところ";
	mes "　普通のタンスのようだが……‐";
	next;
	if(select("そっとしておく","引き出しを開ける") == 1) {
		mes "‐あなたは、その場を離れた‐";
		close;
	}
	mes "‐どこかで機械が動く音がする……‐";
	close2;
	warp "amatsu.gat",147,136;
	end;
}

job_ko.gat,131,124,0	script	製作道具#ko_01	844,{
	if(!(checkquest(5142) & 0x1)) {
		mes "‐製作道具だ。";
		mes "　今は使う必要がない‐";
		close;
	}
	mes "‐武器を製作するための道具だ‐";
	next;
	mes "‐まずは武器製作に使う金属を";
	mes "　溶かす必要があるようだ‐";
	setarray '@point,20,40,60,20,40,60,20;
	while(1) {
		next;
		set '@sel,select("鉄鉱石を溶かす","鉄を溶かす","鋼鉄を溶かす","プラコンを溶かす","エンベルタコンを溶かす","オリデオコン原石を溶かす","エルニウム原石を溶かす","やめる") - 1;
		switch('@sel) {
		case 0:	set '@itemid,1002;	break;
		case 1:	set '@itemid,998;	break;
		case 2:	set '@itemid,999;	break;
		case 3:	set '@itemid,1010;	break;
		case 4:	set '@itemid,1011;	break;
		case 5:	set '@itemid,756;	break;
		case 6:	set '@itemid,757;	break;
		case 7:
			mes "‐あなたは、その場を離れた‐";
			close;
		}
		if(countitem('@itemid) < '@iron['@sel]+1) {
			mes "‐しかし" +getitemname('@itemid)+ "を持っていない‐";
		}
		else {
			if('@cnt == 0)
				misceffect 302;
			mes "‐高熱を与え";
			mes "　" +getitemname('@itemid)+ "を";
			mes "　溶かした‐";
			set '@cnt,'@cnt + '@point['@sel];
			set '@iron['@sel],'@iron['@sel] + 1;
			next;
			if('@cnt < 200) {
				mes "‐まだまだ先は長そうだ‐";
			}
			else if('@cnt < 400) {
				mes "‐この調子で溶かしていこう‐";
			}
			else if('@cnt < 600) {
				mes "‐そろそろ半分くらいだろうか‐";
			}
			else if('@cnt < 800) {
				mes "‐だいぶ純度が高くなった気がする‐";
			}
			else if('@cnt < 1000) {
				mes "‐もう少しで出来上がりそうだ‐";
			}
			else {
				mes "‐武器を作るために十分な量の";
				mes "　溶けた金属の用意ができた‐";
				break;
			}
		}
		next;
		mes "‐現在、溶かした鉱石の個数は";
		mes "　以下の通りです‐";
		next;
		mes "‐鉄鉱石：^FF0000" +'@iron[0]+ "^000000個";
		mes "　鉄：^FF0000" +'@iron[1]+ "^000000個";
		mes "　鋼鉄：^FF0000" +'@iron[2]+ "^000000個";
		mes "　プラコン：^FF0000" +'@iron[3]+ "^000000個";
		mes "　エンベルタコン：^FF0000" +'@iron[4]+ "^000000個";
		mes "　オリデオコン原石：^FF0000" +'@iron[5]+ "^000000個";
		mes "　エルニウム原石：^FF0000" +'@iron[6]+ "^000000個‐";
		next;
		mes "‐次はどの金属を溶かそうか？‐";
		continue;
	}
	next;
	mes "‐次は鋳型に溶けた金属を入れよう。";
	mes "　どの鋳型を使おうか？‐";
	next;
	switch(select("短剣用の鋳型","風魔手裏剣用の鋳型")) {
	case 1:
		mes "‐短剣用の鋳型に";
		mes "　溶けた金属を流し込んだ‐";
		set '@type,1;
		break;
	case 2:
		mes "‐風魔手裏剣用の鋳型に";
		mes "　溶けた金属を流し込んだ‐";
		set '@type,2;
		break;
	}
	next;
	misceffect 101;
	mes "‐ある程度形は整ったようだ。";
	mes "　次はどんな作業をしようか？‐";
	next;
	switch(select("研磨作業をする","焼入れ作業をする")) {
	case 1:
		misceffect 21,"";
		set '@cnt,1;
		mes "‐研磨作業を行った‐";
		next;
		mes "‐まだまだ先は長そうだ。";
		mes "　次は焼き入れ作業をしよう‐";
		break;
	case 2:
		misceffect 101,"";
		set '@cnt,2;
		mes "‐焼入れ作業を行った‐";
		next;
		mes "‐まだまだ先は長そうだ。";
		mes "　次は焼き入れ作業をしよう‐";
		break;
	}
	while(1) {
		next;
		mes "‐次はどんな作業をしようか？‐";
		next;
		switch(select("研磨作業をする","焼入れ作業をする","仕上げ作業をする")) {
		case 1:
			misceffect 21,"";
			if('@cnt == 2) {
				set '@cnt2,'@cnt2 + 1;
			}
			set '@cnt,1;
			mes "‐研磨作業を行った‐";
			next;
			if('@cnt2 < 3)
				mes "‐まだまだ先は長そうだ。";
			else if('@cnt2 < 6)
				mes "‐もっと鍛える必要がありそうだ。";
			else if('@cnt2 < 9)
				mes "‐この調子で鍛えていこう。";
			else if('@cnt2 < 12)
				mes "‐だいぶ鍛えられてきた。";
			else if('@cnt2 < 15)
				mes "‐もう少しで出来上がりそうだ。";
			else {
				mes "‐そろそろ仕上げ作業をしよう‐";
				continue;
			}
			mes "　次は焼き入れ作業をしよう‐";
			continue;
		case 2:
			misceffect 101,"";
			if('@cnt == 1) {
				set '@cnt2,'@cnt2 + 1;
			}
			set '@cnt,2;
			mes "‐焼入れ作業を行った‐";
			next;
			if('@cnt2 < 3)
				mes "‐まだまだ先は長そうだ。";
			else if('@cnt2 < 6)
				mes "‐もっと鍛える必要がありそうだ。";
			else if('@cnt2 < 9)
				mes "‐この調子で鍛えていこう。";
			else if('@cnt2 < 12)
				mes "‐だいぶ鍛えられてきた。";
			else if('@cnt2 < 15)
				mes "‐もう少しで出来上がりそうだ。";
			else {
				mes "‐そろそろ仕上げ作業をしよう‐";
				continue;
			}
			mes "　次は研磨作業をしよう‐";
			continue;
		case 3:
			mes "‐仕上げ作業として";
			mes "　武器のつや消しを行った‐";
			next;
			misceffect 101;
			delitem 1002,'@iron[0];
			delitem 998,'@iron[1];
			delitem 999,'@iron[2];
			delitem 1010,'@iron[3];
			delitem 1011,'@iron[4];
			delitem 756,'@iron[5];
			delitem 757,'@iron[6];
			if('@cnt2 < 15) {
				misceffect 183,"";
				mes "‐仕上げ作業の途中で";
				mes "　試作品が壊れてしまった‐";
				next;
				mes "‐製作過程に問題が";
				mes "　あったのかもしれない……。";
				mes "　最初からやり直しだ‐";
				close;
			}
			misceffect 103,"";
			if('@type == 1) {
				compquest 5142;
				setquest 5143;
				getitem 13074,1;
			}
			else {
				compquest 5142;
				setquest 5144;
				getitem 13312,1;
			}
			mes "‐試作品が完成した‐";
			next;
			mes "‐ヒョウに完成品を見せよう‐";
			close;
		}
	}
}

job_ko.gat,129,129,0	duplicate(製作道具#ko_01)	製作道具#ko_02	844
job_ko.gat,116,124,0	duplicate(製作道具#ko_01)	製作道具#ko_03	844

job_ko.gat,121,121,0	script	精錬装置#ko_01	844,{
	if(!checkquest(5143) && !checkquest(5144)) {
		mes "‐精錬を自動で行ってくれる装置だ。";
		mes "　しかし今は使う必要がないだろう‐";
		close;
	}
	mes "‐精錬装置に電源を入れた。";
	mes "　静かな音とともに装置が動き出した‐";
	next;
	mes "‐装置の横に";
	mes "　オリデオコンが入った倉庫があり";
	mes "　すぐに精錬ができそうだ‐";
	next;
	if(select("精錬する","精錬しない") == 2) {
		mes "‐装置の電源を切った‐";
		close;
	}
	if(getequipisequiped(4)==0) {
		mes "‐ピーピーピー";
		mes "　装置から警告音が聞こえる‐";
		next;
		mes "[ヒョウ]";
		mes "精錬をしたいのなら";
		mes "武器を装備してくださいね。";
		close;
	}
	if(getequipid(4) != 13074 && getequipid(4) != 13312) {
		mes "[ヒョウ]";
		mes "おや？";
		mes "ここで作った武器ではありませんね。";
		next;
		mes "[ヒョウ]";
		mes "それを強化したいのなら";
		mes "街の鍛冶屋にでも頼んでください。";
		close;
	}
	mes "‐武器を分析しています‐";
	next;
	if(getequiprefinerycnt(4) >= 10) {
		// 未調査
		mes "‐この武器はこれ以上精錬できません‐";
		close;
	}
	if(getequippercentrefinery(4) < 100) {
		mes "‐この武器は何度か精錬されているため";
		mes "　精錬に失敗すると";
		mes "　精錬値がひとつ下がります‐";
		next;
		if(select("精錬する","精錬しない") == 2) {
			mes "‐装置の電源を切った‐";
			close;
		}
	}
	else {
		mes "‐精錬を始めます‐";
		next;
	}
	if(getequippercentrefinery(4) > rand(100)) {
		successrefitem 4;
		mes "‐精錬に成功しました‐";
		close;
	}
	else {
		downrefitem 4;
		mes "‐精錬に失敗しました。";
		mes "　精錬値がひとつ下がりました‐";
		close;
	}
}

job_ko.gat,127,121,0	duplicate(精錬装置#ko_01)	精錬装置#ko_02	844

job_ko.gat,148,46,4	script	導き手 ギオン#ko	588,{
	switch(CHANGE_KO) {
	case 10:
		cutin "job_ko01",2;
		mes "[導き手 ギオン]";
		mes "まだ目標を倒していないようじゃな。";
		next;
		mes "[導き手 ギオン]";
		mes "目標の名は^FF0000一族の過去^000000じゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "うまく仕留めたら";
		mes "また話しかけてくれ。";
		mes "それとも、外に出たいのか？";
		next;
		if(select("出ない","外に出る") == 1) {
			mes "[導き手 ギオン]";
			mes "似たような名前の敵が多いが";
			mes "そなたなら仕留められるじゃろう。";
			close2;
			cutin "job_ko01",255;
			end;
		}
		mes "[導き手 ギオン]";
		mes "本来なら試練の最中に";
		mes "抜け出すなど許されぬ事じゃが……";
		mes "今回だけじゃぞ。";
		close2;
		cutin "job_ko01",255;
		warp "amatsu.gat",147,136;
		end;
	case 11:
		cutin "job_ko02",2;
		mes "[導き手 ギオン]";
		mes "うまく目標を仕留めたようじゃな。";
		next;
		if(Weight) {
			mes "[導き手 ギオン]";
			mes "新たな道の第一歩に";
			mes "余計なものは不要じゃろう。";
			mes "所持品を預かってやるから、";
			mes "すべて預けてからまた話かけてくれ。";
			next;
			switch(select("^0000FF倉庫^000000を開く","やめる")) {
			case 1:
				mes "[導き手 ギオン]";
				mes "倉庫を開くぞ。";
				close2;
				openstorage;
				cutin "job_ko02",255;
				end;
			case 2:
				mes "[導き手 ギオン]";
				mes "なんじゃ、まだなにかあるのか？";
				close2;
				cutin "job_ko02",255;
				end;
			}
		}
		cutin "job_ko04",2;
		mapannounce "job_ko.gat","導き手 ギオン : 一族" +strcharinfo(0)+ "が" +(Sex? "影狼": "朧")+ "の道を進むこととなった。かの者に祝福あれ！",0;
		mes "[導き手 ギオン]";
		mes "一族" +strcharinfo(0)+ "が";
		mes (Sex? "影狼": "朧")+ "の道を進むこととなった。";
		mes "かの者に祝福あれ！";
		next;
		cutin "job_ko02",2;
		mes "[導き手 ギオン]";
		mes "更なる極みを求める若者が";
		mes "現れたことを歓迎しよう。";
		next;
		mes "[クウガ・カイ]";
		mes "ギオン様、しばしお待ちを。";
		next;
		cutin "job_ko04",2;
		mes "[導き手 ギオン]";
		mes "すまん、すまん。";
		mes "そなたらのことを忘れておった。";
		mes "何か" +strcharinfo(0)+ "に";
		mes "伝えることでもあるかの？";
		next;
		cutin "job_ko01",255;
		mes "[クウガ・カイ]";
		mes "それでは……";
		next;
		mes "[クウガ・カイ]";
		mes strcharinfo(0);
		mes "お前は誇るべき我等が一族の仲間だ。";
		mes "いかなる時も堂々と胸を張って生きろ。";
		next;
		mes "[クウガ・カイ]";
		mes "……初めて会ったとき";
		mes "いきなり攻撃して悪かった……";
		next;
		mes "[ヒョウ]";
		mes "ふふ……";
		mes "カイのやつは言葉だけですか。";
		mes "私は彼よりも";
		mes "役立つものを贈りましょう。";
		next;
		mes "[ヒョウ]";
		mes "君が作った試作品の";
		mes "手入れをしておきました。";
		next;
		mes "[ヒョウ]";
		if(checkquest(5143) & 0x8) {
			// 未調査
			mes "武器の名は「紅」。";
			mes "手入れをしているうちに";
			mes "鬼気が巻き込まれるような武器になりました。";
			set '@gain,13075;
		}
		else if(checkquest(5144) & 0x8) {
			mes "[ヒョウ]";
			mes "武器の名は「影」。";
			mes "手入れをしているうちに";
			mes "暗闇に溶け込むような武器になりました。";
			set '@gain,13311;
		}
		next;
		mes "[ヒョウ]";
		mes "きっと気に入ってもらえると";
		mes "思いますよ。";
		next;
		mes "[ヒョウ]";
		mes "ではギオン様、続きを……";
		next;
		cutin "job_ko01",2;
		mes "[導き手 ギオン]";
		mes "ふぉふぉふぉ……";
		mes "二人に台詞を取られてしまったな。";
		mes "わしから話すことは何もない。";
		next;
		mes "[導き手 ギオン]";
		mes "ただ、そなたのような若者に";
		mes "もっと良い環境を";
		mes "作ってやれなかったのが心残りじゃ。";
		next;
		mes "[導き手 ギオン]";
		mes "これからも前向きに歩んでくれ。";
		mes "そして……";
		next;
		if(sc_ison(SC_ALL_RIDING)) {
			// 未調査
			mes "[導き手 ギオン]";
			mes "む、新たな旅立ちの準備が";
			mes "できていないようじゃな。";
			mes "騎乗生物を";
			mes "降りて来るのじゃ。";
			close2;
			cutin "job_ko01",255;
			end;
		}
		if(SkillPoint) {
			mes "[導き手 ギオン]";
			mes "む、新たな旅立ちの準備が";
			mes "できていないようじゃな。";
			mes "スキルポイントを";
			mes "全て振って来るのじゃ。";
			close2;
			cutin "job_ko01",255;
			end;
		}
		resetstatus;
		resetskill;
		jobchange (Sex? Job_Kagerou: Job_Oboro);
		set CHANGE_KO,0;
		delquest 5136;
		delquest 5137;
		delquest 5138;
		delquest 5143;
		delquest 5144;
		delquest 72905;
		setquest 201655;
		getitem '@gain,1;
		mes "[導き手 ギオン]";
		mes "そなたの行く先に";
		mes "影狼様と朧様の祝福があらんことを！";
		close2;
		warp "que_ng.gat",22,69;
		end;
	default:
		mes "[導き手 ギオン]";
		mes "そなたの行く先に";
		mes "影狼様と朧様の祝福があらんことを！";
		close2;
		warp "que_ng.gat",22,69;
		end;
	}
}

job_ko.gat,151,47,4	script	クウガ・カイ#ko2	730,{
	mes "[クウガ・カイ]";
	mes "貴様もここまで来たか……";
	close;
}

job_ko.gat,145,47,6	script	ヒョウ#ko2	730,{
	mes "[ヒョウ]";
	mes "やあ、いよいよですね。";
	close;
}

job_ko.gat,0,0,0	script	ko_test_mon	139,{
OnTimer300000:
	initnpctimer;
	killmonster "job_ko.gat","ko_test_mon::OnKilled1";
	set '@r,rand(getarraysize('mobid));
	areamonster "job_ko.gat",128,26,168,66,"一族の過去",'mobid['@r],1,"ko_test_mon::OnKilled1";
	end;
OnInit:
	setarray 'mobid,1002,1010,1031,1049,1050,1063,1113;
	setarray 'mobname$,
		"一族のハズレ","一族の影狼","一族の朧","一族の加古","一族の遺産",
		"一族の加護","一族の過誤","一族の黒歴史","一族の始祖",
		"影狼の記憶","影狼の過去","影狼の想い出","影狼の歴史",
		"朧の記憶","朧の過去","朧の想い出","朧の歴史",
		"過誤の一族","忍者の一族","城主のバカ","親族の遺産","親族の過去";

	set '@r,rand(getarraysize('mobid));
	areamonster "job_ko.gat",128,26,168,66,"一族の過去",'mobid['@r],1,"ko_test_mon::OnKilled1";

	for(set '@i,110; '@i<=171; set '@i,'@i+1) {
		set '@r1,rand(getarraysize('mobid));
		set '@r2,rand(getarraysize('mobname$));
		monster "job_ko.gat",'@i,50,'mobname$['@r2],'mobid['@r1],1,"ko_test_mon::OnKilled2";
	}
	for(set '@i,31; '@i<=81; set '@i,'@i+1) {
		set '@r1,rand(getarraysize('mobid));
		set '@r2,rand(getarraysize('mobname$));
		monster "job_ko.gat",140,'@i,'mobname$['@r2],'mobid['@r1],1,"ko_test_mon::OnKilled2";
	}
	initnpctimer;
	end;
OnKilled1:
	if(CHANGE_KO == 10)
		set CHANGE_KO,11;
	end;
OnKilled2:
	if(rand(2)) {
		set '@x,rand(110,171);
		set '@y,50;
	}
	else {
		set '@x,140;
		set '@y,rand(31,81);
	}
	set '@r1,rand(getarraysize('mobid));
	set '@r2,rand(getarraysize('mobname$));
	monster "job_ko.gat",'@x,'@y,'mobname$['@r2],'mobid['@r1],1,"ko_test_mon::OnKilled2";
	if(!rand(3))
		warp "job_ko.gat",16,113;
	end;
}

que_ng.gat,75,23,3	script	鍛冶師 テーネ#ko	762,{
	mes "[鍛冶師 テーネ]";
	mes "ご機嫌麗しゅうございます。";
	mes "鍛冶師でもっとも礼儀正しいと";
	mes "言われているテーネでございます。";
	next;
	mes "[鍛冶師 テーネ]";
	mes "今日はいかがいたしましょうか。";
	next;
	switch(select("どんな仕事ができますか？","能力を追加してください","能力を削除してください")) {
	case 1:
		mes "[鍛冶師 テーネ]";
		mes "おっと！";
		mes "私めの自己紹介に不足がありましたね。";
		mes "申し訳ございません。";
		next;
		mes "[鍛冶師 テーネ]";
		mes "私は一部の装備品に";
		mes "能力を追加することができます。";
		mes "その際には多少の手数料を";
		mes "いただくことになっております。";
		next;
		mes "[鍛冶師 テーネ]";
		mes "なお、装備品の精錬値によって、";
		mes "付与される能力は変化いたします。";
		mes "また、^FF0000能力の付与に";
		mes "失敗することはありません。^000000";
		next;
		mes "[鍛冶師 テーネ]";
		mes "取り扱っている装備品のリストも";
		mes "ご覧になりますか？";
		next;
		switch(select("武器のリストを見る","防具のリストを見る")) {
		case 1:
			mes "[鍛冶師 テーネ]";
			mes "武器のリストはこちらです。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "私が取り扱っている武器は^FD3302";
			mes "羅刹剣";
			mes "三日月";
			mes "風魔手裏剣・乱華";
			mes "風魔手裏剣・乱雪";
			mes "風魔手裏剣・雷雨^000000です。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "以上です。";
			mes "さらに多くの武具を取り扱うには";
			mes "まだまだ私も修行を";
			mes "重ねなくてはいけません。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "お望みであれば";
			mes "3番と4番のスロットに";
			mes "能力を追加いたします。";
			close;
		case 2:
			mes "[鍛冶師 テーネ]";
			mes "防具のリストはこちらです。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "私が取り扱っている防具は^FD3302";
			mes "狼紋様の手甲";
			mes "三日月紋様の手甲";
			mes "円鱗の鎧";
			mes "霧中闇影";
			mes "特殊忍者スーツ[1]^000000です。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "以上です。";
			mes "さらに多くの武具を取り扱うには";
			mes "まだまだ私も修行を";
			mes "重ねなくてはいけません。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "お望みであれば";
			mes "3番と4番のスロットに";
			mes "能力を追加いたします。";
			close;
		}
	case 2:
		mes "[鍛冶師 テーネ]";
		mes "能力の追加でございますね。";
		mes "装備なさっている武具の";
		mes "4番スロット、3番スロットの順に";
		mes "能力を付与いたします。";
		next;
		mes "[鍛冶師 テーネ]";
		mes "私の独創的な技術により";
		mes "^FF0000精錬値^000000やすでに挿してある^FF0000カード^000000が";
		mes "失われることはございません。";
		mes "また、^FF0000能力の付与に";
		mes "失敗することもありません。^000000";
		next;
		mes "[鍛冶師 テーネ]";
		mes "ただ材料の値段が張りますので";
		mes "多少の^5565AA手数料^000000をいただいております。";
		next;
		mes "[鍛冶師 テーネ]";
		mes "おっと、説明が長くなってしまい";
		mes "申し訳ございません。";
		mes "どの装備に能力を付与しますか？";
		next;
		switch(select("武器","防具")) {
		case 1:
			mes "[鍛冶師 テーネ]";
			mes "武器への能力付与をお望みですね。";
			mes "武器に能力を付与する^E14A1E手数料は";
			mes "1回100,000Zeny^000000となっております。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "それと、あらかじめ^FF0000片手武器は右手に";
			mes "装備して^000000いただけますか。";
			mes "ご協力をお願いいたします。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "どの武器に能力を付与いたしますか？";
			next;
			switch(select("また今度","羅刹剣","三日月","風魔手裏剣・乱華","風魔手裏剣・乱雪","風魔手裏剣・雷雨")) {
			case 1:
				mes "[鍛冶師 テーネ]";
				mes "お考え直しの時間が必要でしょうか？";
				mes "またいつでもいらしてください。";
				close;
			case 2: set '@itemid,13076; set '@menu,4; break;
			case 3: set '@itemid,13078; set '@menu,4; break;
			case 4: set '@itemid,13313; set '@menu,4; break;
			case 5: set '@itemid,13314; set '@menu,4; break;
			case 6: set '@itemid,13315; set '@menu,4; break;
			}
			break;
		case 2:
			mes "[鍛冶師 テーネ]";
			mes "防具への能力付与をお望みですね。";
			mes "防具に能力を付与する^E14A1E手数料は";
			mes "1回100,000Zeny^000000となっております。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "どの防具に能力を付与しますか？";
			next;
			switch(select("また今度","狼紋様の手甲","三日月紋様の手甲","円鱗の鎧","霧中闇影","特殊忍者スーツ[1]")) {
			case 1:
				mes "[鍛冶師 テーネ]";
				mes "お考え直しの時間が必要でしょうか？";
				mes "またいつでもいらしてください。";
				close;
			case 2: set '@itemid,2172; set '@menu,3; break;
			case 3: set '@itemid,2173; set '@menu,3; break;
			case 4: set '@itemid,15054; set '@menu,2; break;
			case 5: set '@itemid,15055; set '@menu,2; break;
			case 6: set '@itemid,15056; set '@menu,2; break;
			}
			break;
		}
		break;
	case 3:
		mes "[鍛冶師 テーネ]";
		mes "すでに付与された能力の";
		mes "削除をお望みですか？";
		mes "付与された能力が";
		mes "お気に召さなかったようですね。";
		next;
		mes "[鍛冶師 テーネ]";
		mes "それでは、たびたび高い手数料を";
		mes "いただくこととなり";
		mes "申しわけありませんが……";
		next;
		mes "[鍛冶師 テーネ]";
		mes "^E14A1E能力削除手数料は100,000Zeny^000000です。";
		mes "どの装備の能力を削除しますか？ ";
		next;
		switch(select("また今度","羅刹剣","三日月","風魔手裏剣・乱華","風魔手裏剣・乱雪","風魔手裏剣・雷雨","狼紋様の手甲","三日月紋様の手甲","円鱗の鎧","霧中闇影","特殊忍者スーツ［1］")) {
		case 1:
			mes "[鍛冶師 テーネ]";
			mes "やはり手数料負担が大きいのですね？";
			mes "手数料をもう少し下げられるよう";
			mes "もっと努力を重ねます。";
			close;
		case 2: set '@itemid,13076; set '@menu,4; break;
		case 3: set '@itemid,13078; set '@menu,4; break;
		case 4: set '@itemid,13313; set '@menu,4; break;
		case 5: set '@itemid,13314; set '@menu,4; break;
		case 6: set '@itemid,13315; set '@menu,4; break;
		case 7: set '@itemid,2172; set '@menu,3; break;
		case 8: set '@itemid,2173; set '@menu,3; break;
		case 9: set '@itemid,15054; set '@menu,2; break;
		case 10:set '@itemid,15055; set '@menu,2; break;
		case 11:set '@itemid,15056; set '@menu,2; break;
		}
		mes "[鍛冶師 テーネ]";
		mes "^44B7BC" +getitemname('@itemid)+ "^000000の";
		mes "能力初期化をお望みですか？";
		next;
		mes "[鍛冶師 テーネ]";
		mes "手数料はそのままで、4番スロットの";
		mes "能力を残し、3番スロットの能力のみを";
		mes "削除するサービスも行っております。";
		mes "なお、4番スロットの能力のみを";
		mes "削除することはできません。";
		next;
		switch(select("3番スロットのみ初期化する","両方初期化する")) {
		case 1:
			mes "[鍛冶師 テーネ]";
			mes "承知いたしました。";
			mes "3番スロットのみ初期化いたします。";
			set '@type,1;
			break;
		case 2:
			mes "[鍛冶師 テーネ]";
			mes "承知いたしました。";
			mes "両方のスロットを初期化いたします。";
			set '@type,2;
			break;
		}
		next;
		if(getequipid('@menu) != '@itemid) {
			mes "[鍛冶師 テーネ]";
			mes "作業ご希望の装備品を";
			mes "装備されていないようです。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "ご希望の装備品を装備した状態で";
			mes "ご利用をお願いいたします。";
			close;
		}
		if(Zeny < 100000) {
			mes "[鍛冶師 テーネ]";
			mes "大変申し訳ございませんが";
			mes "手数料が足りないようです。";
			next;
			mes "[鍛冶師 テーネ]";
			mes "原材料がとても高価なため";
			mes "必要最低限の手数料を";
			mes "いただくことになっております。";
			close;
		}
		set '@refine,getequiprefinerycnt('@menu);
		set '@card1,getequipcardid('@menu,0);
		set '@card2,getequipcardid('@menu,1);
		set '@card3,getequipcardid('@menu,2);
		set '@card4,getequipcardid('@menu,3);
		if('@type == 1) {
			if('@card3 == 0) {
				mes "[鍛冶師 テーネ]";
				mes "3番には能力がありません。";
				mes "ご確認をお願いいたします。";
				close;
			}
			set '@card3,0;
		}
		else if('@type == 2) {
			if('@card3 == 0 && '@card4 == 0) {
				mes "[鍛冶師 テーネ]";
				mes "能力が付与されていない装備です。";
				mes "ご確認をお願いいたします。";
				close;
			}
			set '@card3,0;
			set '@card4,0;
		}
		set Zeny,Zeny-100000;
		delequip '@menu;
		getitem2 '@itemid,1,1,'@refine,0,'@card1,'@card2,'@card3,'@card4;
		mes "[鍛冶師 テーネ]";
		mes "初期化が無事完了いたしました。";
		close;
	}
	// 能力付与続き
	if(getequipid('@menu) != '@itemid) {
		mes "[鍛冶師 テーネ]";
		mes "作業ご希望の装備品を";
		mes "装備されていないようです。";
		next;
		mes "[鍛冶師 テーネ]";
		mes "ご希望の装備品を装備した状態で";
		mes "ご利用をお願いいたします。";
		close;
	}
	if(Zeny < 100000) {
		mes "[鍛冶師 テーネ]";
		mes "大変申し訳ございませんが";
		mes "手数料が足りないようです。";
		next;
		mes "[鍛冶師 テーネ]";
		mes "原材料がとても高価なため";
		mes "必要最低限の手数料を";
		mes "いただくことになっております。";
		close;
	}
	set '@refine,getequiprefinerycnt('@menu);
	set '@card1,getequipcardid('@menu,0);
	set '@card[1],'@card1;
	set '@card2,getequipcardid('@menu,1);
	set '@card[2],'@card2;
	set '@card3,getequipcardid('@menu,2);
	set '@card[3],'@card3;
	set '@card4,getequipcardid('@menu,3);
	set '@card[4],'@card4;
	if('@card4 == 0) {
		mes "[鍛冶師 テーネ]";
		mes "能力が付与されてない装備です。";
		mes "4番スロットに";
		mes "能力を付与いたしますか？";
		set '@slot,4;
	}
	else if('@card3 == 0) {
		mes "[鍛冶師 テーネ]";
		mes "すでに4番スロットに";
		mes "能力が付与された装備品です。";
		mes "3番スロットにも";
		mes "能力を付与いたしますか？";
		set '@slot,3;
	}
	else {
		mes "[鍛冶師 テーネ]";
		mes "私の力ではこれ以上の";
		mes "能力付与は難しいです。";
		next;
		mes "[鍛冶師 テーネ]";
		mes "もし付与された能力が";
		mes "お気に召さないのでしたら";
		mes "初期化を行ってみてはいかがでしょう？";
		close;
	}
	next;
	if(select("また今度にする","付与する") == 1) {
		mes "[鍛冶師 テーネ]";
		mes "承知いたしました。";
		mes "またいらしてください。";
		close;
	}
	mes "[鍛冶師 テーネ]";
	mes "それでは、" +'@slot+ "番スロットへの";
	mes "能力付与作業を行います。";
	next;
	misceffect 154;
	set Zeny,Zeny-100000;
	delequip '@menu;
	if('@refine <= 4) {
		set '@rand,rand(1,26);
		setarray '@rate[1],20,16,14,13,7,3,1,0;
		setarray '@tbl_enchant[1],4786,4787,4788,4789,4791,4792,4793,4794;
	}
	else if('@refine <= 7) {
		set '@rand,rand(1,44);
		setarray '@rate[1],41,38,35,32,29,26,20,16,14,13,7,3,1,0;
		setarray '@tbl_enchant[1],4700,4710,4720,4730,4740,4750,4786,4787,4788,4789,4791,4792,4793,4794;
	}
	else if('@refine <= 9) {
		set '@rand,rand(1,36);
		setarray '@rate[1],32,28,24,20,16,12,10,8,6,4,2,0;
		setarray '@tbl_enchant[1],4700,4701,4710,4711,4720,4721,4730,4731,4740,4741,4750,4751;
	}
	else {
		set '@rand,rand(1,46);
		setarray '@rate[1],42,38,36,35,33,32,28,24,20,16,12,10,8,6,4,2,0;
		setarray '@tbl_enchant[1],4795,4796,4797,4800,4801,4700,4701,4710,4711,4720,4721,4730,4731,4740,4741,4750,4751;
	}
	for(set '@j,1; '@j <= getarraysize('@rate); set '@j,'@j+1) {
		if ('@rand > '@rate['@j]) {
			set '@card['@slot],'@tbl_enchant['@j];
			break;
		}
	}
	getitem2 '@itemid,1,1,'@refine,0,'@card[1],'@card[2],'@card[3],'@card[4];
	mes "[鍛冶師 テーネ]";
	mes "^44B7BC" +getitemname('@itemid)+ "^000000";
	mes "に能力を付与いたしました。";
	close;
}

que_ng.gat,21,72,6	script	防具職人 ギヨ#kaboro	934,{
	mes "[ギヨ]";
	mes "勝利とは何だと考えている？";
	mes "敵を倒す事……";
	mes "確かにその通りだ。";
	mes "だが、それより重要な事がある。";
	mes "それは、";
	mes "決して倒れないことだ！";
	next;
	mes "[ギヨ]";
	mes "その為には身を守る必要がある。";
	mes "「自身」を守れない者に";
	mes "「他人」を守る事などできない。";
	next;
	if(select("防具を作成する","会話を終える") == 2) {
		mes "[ギヨ]";
		mes "慎重になることは";
		mes "戦闘でとても重要な要素だ。";
		close;
	}
	switch(select("狼紋様の手甲[1]","三日月紋様の手甲[1]","円鱗の鎧[1]","霧中闇影[1]","やめる")) {
	case 1:
		mes "[ギヨ]";
		mes "狼紋様の手甲[1]か。";
		mes "野性的なものを選んだな。";
		while(1) {
			next;
			switch(select("材料を見る","性能を見る","作成する","やめる")) {
			case 1:
				mes "[ギヨ]";
				mes "^ff0000狼紋様の手甲[1]は";
				mes "キツネ紋様の手甲[1]1個";
				mes "狼の血10個^000000";
				mes "が必要だ。";
				mes "感じられるだろ？";
				mes "熱く燃え上がっている狼の血が。";
				continue;
			case 2:
				mes "[狼紋様の手甲[1]]";
				mes "物理攻撃命中時、一定確率で";
				mes "5秒間、Atk + 100";
				mes "Flee - 50";
				next;
				mes "[狼紋様の手甲[1]]";
				mes "[円鱗の鎧]";
				mes "と共に装備時、追加で";
				mes "Str + 2";
				mes "物理攻撃で与えるダメージ + 10%";
				next;
				mes "[狼紋様の手甲[1]]";
				mes "系列 : 盾";
				mes "防御 : 70";
				mes "重量 : 25";
				mes "要求レベル : 100";
				mes "装備 : 影狼 朧";
				continue;
			case 3:
				set '@gain,2172;
				setarray '@need,2171,6252;
				setarray '@amount,1,10;
				break;
			case 4:
				mes "[ギヨ]";
				mes "よく、考えるといい。";
				close;
			}
			break;
		}
		break;
	case 2:
		mes "[ギヨ]";
		mes "三日月紋様の手甲[1]か。";
		mes "美しさ、強さどちらも備えた";
		mes "上等な一品だ。";
		while(1) {
			next;
			switch(select("材料を見る","性能を見る","作成する","やめる")) {
			case 1:
				mes "[ギヨ]";
				mes "^ff0000三日月紋様の手甲[1]は";
				mes "キツネ紋様の手甲[1]1個";
				mes "水晶のかけら100個^000000";
				mes "が必要になる。";
				mes "これにより、水晶のように透明で";
				mes "美しい三日月を刻むことになる。";
				continue;
			case 2:
				mes "[三日月紋様の手甲[1]]";
				mes "精錬値が1上がる度に、";
				mes "スキルディレイ - 2%";
				mes "[霧中闇影]";
				mes "と共に装備時、追加で";
				mes "Flee + 10";
				mes "完全回避 + 10";
				next;
				mes "[三日月紋様の手甲[1]]";
				mes "系列 : 盾";
				mes "防御 : 45";
				mes "重量 : 25";
				mes "要求レベル : 100";
				mes "装備 : 影狼 朧";
				continue;
			case 3:
				set '@gain,2173;
				setarray '@need,2171,7321;
				setarray '@amount,1,100;
				break;
			case 4:
				mes "[ギヨ]";
				mes "よく、考えるといい。";
				close;
			}
			break;
		}
		break;
	case 3:
		mes "[ギヨ]";
		mes "円鱗の鎧[1]か。";
		mes "これはかつて伝説となっていた";
		mes "忍者が身に着けていたものらしい。";
		while(1) {
			next;
			switch(select("材料を見る","性能を見る","作成する","やめる")) {
			case 1:
				mes "[ギヨ]";
				mes "^ff0000円鱗の鎧[1]は";
				mes "火竜の鱗30個、";
				mes "氷の鱗30個、";
				mes "鮮血の鱗30個^000000";
				mes "が必要になる。";
				continue;
			case 2:
				mes "[円鱗の鱗[1]]";
				mes "MaxHP + 15%";
				mes "MaxSP - 30%";
				next;
				mes "[円鱗の鱗[1]]";
				mes "[狼模様の手甲]";
				mes "と共に装備時、追加で";
				mes "Str + 2";
				mes "物理攻撃で与えるダメージ + 10%";
				next;
				mes "[円鱗の鱗[1]]";
				mes "系列 : 鎧";
				mes "防御 : 90";
				mes "重量 : 180";
				mes "要求レベル : 100";
				mes "装備 : 影狼 朧";
				continue;
			case 3:
				set '@gain,15054;
				setarray '@need,7451,7562,6091;
				setarray '@amount,30,30,30;
				break;
			case 4:
				mes "[ギヨ]";
				mes "よく、考えるといい。";
				close;
			}
			break;
		}
		break;
	case 4:
		mes "[ギヨ]";
		mes "霧中闇影[1]か……。";
		mes "これは霧に隠れ闇に紛れ、";
		mes "身を守る為に作られた物だ。";
		while(1) {
			next;
			switch(select("材料を見る","性能を見る","作成する","やめる")) {
			case 1:
				mes "[ギヨ]";
				mes "^ff0000霧中闇影[1]には";
				mes "特殊忍者スーツ[1]";
				mes "暗闇の破片10個^000000";
				mes "が必要になる。";
				continue;
			case 2:
				mes "[霧中闇影[1]]";
				mes "Agi + 1";
				mes "物理攻撃を受けた時、";
				mes "一定確率で自分にオートスペル";
				mes "[幻術-影武者-]Lv1発動";
				next;
				mes "[霧中闇影[1]]";
				mes "[三日月模様の手甲]";
				mes "と共に装備時、追加で";
				mes "完全回避 + 10";
				mes "Flee + 10";
				next;
				mes "[霧中闇影[1]]";
				mes "系列 : 鎧";
				mes "防御 : 60";
				mes "重量 : 150";
				mes "要求レベル : 100";
				mes "装備 : 影狼 朧";
				continue;
			case 3:
				set '@gain,15055;
				setarray '@need,15056,6089;
				setarray '@amount,1,10;
				break;
			case 4:
				mes "[ギヨ]";
				mes "よく、考えるといい。";
				close;
			}
			break;
		}
		break;
	}
	mes "[ギヨ]";
	mes "作成の際には注意点がある。";
	mes "作成に使用する材料装備を";
	mes "複数所持している場合、";
	mes "^ff0000どれを材料にするかは指定できない。^000000";
	mes "材料に使用するものだけ所持した状態で";
	mes "来るように気を付けてくれ。";
	next;
	mes "[ギヨ]";
	mes "後で後悔してもしらないからな。";
	mes "では、作成するがいいか？";
	next;
	if(select("作成する","やめる") == 2) {
		mes "[ギヨ]";
		mes "よく、考えるといい。";
		close;
	}
	for(set '@i,0; '@amount['@i]!=0; set '@i,'@i+1) {
		if(countitem('@need['@i]) < '@amount['@i]) {
			mes "[ギヨ]";
			mes "……。";
			mes "材料が不足しているようだな。";
			switch('@gain) {
			case 2172:
				mes "^ff0000狼紋様の手甲[1]は";
				mes "キツネ紋様の手甲[1]1個";
				mes "狼の血10個^000000";
				break;
			case 2173:
				mes "^ff0000三日月紋様の手甲[1]は";
				mes "キツネ紋様の手甲[1]1個";
				mes "水晶のかけら100個^000000";
				break;
			case 15054:
				mes "^ff0000円鱗の鎧[1]は";
				mes "火竜の鱗30個、氷の鱗30個、";
				mes "鮮血の鱗30個^000000";
				break;
			case 15055:
				mes "^ff0000霧中闇影[1]には";
				mes "特殊忍者スーツ[1]";
				mes "暗闇の破片10個^000000";
				break;
			}
			mes "が必要だ。";
			mes "よく探して見てくれ。";
			close;
		}
	}
	if(checkitemblank() == 0) {
		mes "[ギヨ]";
		mes "荷物が多すぎるようだ。";
		mes "荷を減らしてから";
		mes "また来てくれ。";
		close;
	}
	if(checkweight('@gain,1) == 0) {
		mes "[ギヨ]";
		mes "荷物が重すぎるようだ。";
		mes getitemid('@gain)+ "[1]は重量" +(getiteminfo('@gain,6)/10)+ "だ。";
		mes "荷を軽くしてから";
		mes "また来てくれ。";
		close;
	}
	for(set '@i,0; '@amount['@i]!=0; set '@i,'@i+1)
		delitem '@need['@i],'@amount['@i];
	getitem '@gain,1;
	mes "[ギヨ]";
	mes "うむ。出来たぞ。";
	mes "美しい……。";
	close;
}

que_ng.gat,23,70,3	script	武器職人 キー#kaboro	939,{
	mes "[キー]";
	mes "攻撃は最大の防御";
	mes "という言葉がある。";
	mes "強力な武器こそ、";
	mes "私を守ってくれる。";
	next;
	mes "[キー]";
	mes "必要な材料があれば、";
	mes "特別な品を提供しよう。";
	next;
	if(select("武器を作成する","会話を終える") == 2) {
		mes "[キー]";
		mes "慎重過ぎるのも問題だ。";
		close;
	}
	switch(select("羅刹剣[1]","三日月[1]","風魔手裏剣・乱華[2]","やめる")) {
	case 1:
		mes "[キー]";
		mes "羅刹剣[1]は";
		mes "ある程度修練を積んだ者しか";
		mes "扱えない難しい武器だ。";
		while(1) {
			next;
			switch(select("材料をみる","性能をみる","作成する","やめる")) {
			case 1:
				mes "[キー]";
				mes "^ff0000羅刹剣は村雨[2]1個";
				mes "ガーネット1個^000000";
				mes "が必要になる。";
				mes "ガーネットが羅刹剣特有の美しい色を";
				mes "演出してくれる。";
				continue;
			case 2:
				mes "[羅刹剣[1]]";
				mes "Int + 3";
				mes "Matk + 100";
				next;
				mes "[羅刹剣[1]]";
				mes "系列 : 短剣";
				mes "攻撃 : 120";
				mes "重量 : 60";
				mes "武器レベル : 3";
				mes "要求レベル : 110";
				mes "装備 : 影狼 朧";
				continue;
			case 3:
				set '@gain,13076;
				setarray '@need,13013,718;
				setarray '@amount,1,1;
				break;
			case 4:
				mes "[キー]";
				mes "よく、考えてみる事だ。";
				close;
			}
			break;
		}
		break;
	case 2:
		mes "[キー]";
		mes "三日月[1]か……。";
		mes "三日月のように曲がる美しい曲線。";
		mes "この仕上がりを出せる者は";
		mes "滅多にいない一品だ。";
		while(1) {
			next;
			switch(select("材料をみる","性能をみる","作成する","やめる")) {
			case 1:
				mes "[キー]";
				mes "^ff0000三日月[1]は白刃[1]1個";
				mes "オパール1個^000000";
				mes "が必要になる。";
				mes "オパールが三日月の光を";
				mes "さらに輝かせる。";
				continue;
			case 2:
				mes "[三日月[1]]";
				mes "Matk + 120、";
				mes "スキル使用時";
				mes "消費SP - 5%";
				mes "スキル使用時";
				mes "詠唱時間 - 5%";
				next;
				mes "[三日月[1]]";
				mes "系列 : 短剣";
				mes "攻撃 : 50";
				mes "重量 : 60";
				mes "武器レベル : 4";
				mes "要求レベル : 100";
				mes "装備 : 影狼 朧";
				continue;
			case 3:
				set '@gain,13078;
				setarray '@need,13015,727;
				setarray '@amount,1,1;
				break;
			case 4:
				mes "[キー]";
				mes "よく、考えてみる事だ。";
				close;
			}
			break;
		}
		break;
	case 3:
		mes "[キー]";
		mes "風魔手裏剣・乱華[2]か。";
		mes "これも本当に美しい。";
		mes "君は花びらが舞う姿を";
		mes "見たことがあるか？";
		while(1) {
			next;
			switch(select("材料をみる","性能をみる","作成する","やめる")) {
			case 1:
				mes "[キー]";
				mes "^ff0000風魔手裏剣・乱華[2]は";
				mes "風魔手裏剣・明浄[2]1個";
				mes "壊れた手裏剣100個^000000";
				mes "が必要になる。";
				mes "手裏剣が少し多めに必要だが、";
				mes "美しく舞うためだ。";
				continue;
			case 2:
				mes "[風魔手裏剣・乱華[2]]";
				mes "Matk + 50";
				mes "スキル [風魔手裏剣-乱華-]";
				mes "で与えるダメージ + 20%";
				next;
				mes "系列 : 風魔手裏剣";
				mes "攻撃 : 150";
				mes "重量 : 150";
				mes "武器レベル : 3";
				mes "要求レベル : 110";
				mes "装備 : 影狼 朧";
				continue;
			case 3:
				set '@gain,13313;
				setarray '@need,13304,7156;
				setarray '@amount,1,100;
				break;
			case 4:
				mes "[キー]";
				mes "よく、考えてみる事だ。";
				close;
			}
			break;
		}
		break;
	case 4:
		mes "[キー]";
		mes "よく、考えてみる事だ。";
		close;
	}
	mes "[キー]";
	mes "作成の際には注意点がある。";
	mes "作成に使用する材料装備を";
	mes "複数所持している場合、";
	mes "^ff0000どれを材料にするかは指定できない。^000000";
	mes "材料に使用するものだけ所持した状態で";
	mes "来るように気を付けてくれ。";
	next;
	mes "[キー]";
	mes "後で後悔してもしらないからな。";
	mes "では、作成するがいいか？";
	next;
	if(select("作成する","やめる") == 2) {
		mes "[キー]";
		mes "よく、考えてみる事だ。";
		close;
	}
	for(set '@i,0; '@amount['@i]!=0; set '@i,'@i+1) {
		if(countitem('@need['@i]) < '@amount['@i]) {
			mes "[キー]";
			mes "駄目だ。材料が足りない。";
			switch('@gain) {
			case 13076:
				mes "羅刹剣[1]に必要な材料は";
				mes "^ff0000羅刹剣は村雨[2]1個";
				mes "ガーネット1個^000000";
				break;
			case 13078:
				mes "三日月[1]に必要な材料は";
				mes "^ff0000白刃[1]1個";
				mes "オパール1個^000000";
				break;
			case 13313:
				mes "風魔手裏剣・乱華[2]に必要な材料は";
				mes "^ff0000風魔手裏剣・明浄[2]1個";
				mes "壊れた手裏剣100個^000000";
				break;
			}
			mes "以上だ。";
			mes "材料を装備していては駄目だぞ。";
			close;
		}
	}
	if(checkitemblank() == 0) {
		mes "[キー]";
		mes "荷物が多すぎるようだ。";
		mes "荷を減らしてから";
		mes "また来てくれ。";
		close;
	}
	if(checkweight('@gain,1) == 0) {
		mes "[キー]";
		mes "荷物が重すぎるようだ。";
		mes getitemid('@gain)+ "[" +getiteminfo('@gain,10)+ "]は重量" +(getiteminfo('@gain,6)/10)+ "だ。";
		mes "荷を軽くしてから";
		mes "また来てくれ。";
		close;
	}
	for(set '@i,0; '@amount['@i]!=0; set '@i,'@i+1)
		delitem '@need['@i],'@amount['@i];
	getitem '@gain,1;
	mes "[キー]";
	mes "うむ。出来たぞ。";
	mes "美しい……。";
	close;
}
