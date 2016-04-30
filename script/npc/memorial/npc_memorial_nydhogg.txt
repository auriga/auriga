//= Auriga Script ==============================================================
// Ragnarok Online Nydhogg's Nest Script	by refis
//- Registry -------------------------------------------------------------------
// NYD_2QUE -> 0～2
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
nyd_dun02.gat,100,201,3	script	守護者の門	111,8,8,{
	switch(NYD_1QUE) {
	case 0:
		mes "‐あなたを見下ろすように";
		mes "　龍の彫刻があり、";
		mes "　さらにその下には";
		mes "　二つの彫刻があった‐";
		next;
		if(select("調べる","特に何もしない") == 2) {
			mes "‐あなたは";
			mes "　この場を立ち去った‐";
			close;
		}
		if(ASH_6QUE == 14 || ASH_6QUE == 15) {
			misceffect 152,"";
			pushpc 7,3;
			mes "‐あなたが門に近づくと";
			mes "　押し返されてしまった。";
			mes "　どうやら、門には侵入者を拒む";
			mes "　何らかの^FF0000力^000000が放たれているようだ‐";
			next;
			mes "‐あなたはこの門の向こう側に";
			mes "　想像をこえる大きな^FF0000秘密^000000が";
			mes "　隠されているように感じた‐";
			next;
			mes "‐ミッドガルド連合軍の司令官に";
			mes "　報告する必要があるだろう‐";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（一度、ミッドガルド連合軍駐屯地の";
			mes "司令官アジフに報告しよう）";
			set NYD_1QUE,1;
			delquest 70374;
			setquest 70850;
			close;
		} else {
			misceffect 152,"";
			pushpc 7,3;
			mes "‐あなたが門に近づくと";
			mes "　押し返されてしまった。";
			mes "　どうやら、門には侵入者を拒む";
			mes "　何らかの^FF0000力^000000が放たれているようだ‐";
			next;
			mes "‐この門の向こう側には";
			mes "　想像をこえる大きな^FF0000秘密^000000が";
			mes "　隠されているに違いない。";
			mes "　あなたはミッドガルド連合軍駐屯地の";
			mes "　上層部に報告しようと考えた‐";
			next;
			mes "‐しかし、あなたは上層部と";
			mes "　まだ信頼関係が築けていない‐";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（ミッドガルド連合軍駐屯地の";
			mes "　^FF0000司令官からの依頼を達成する^000000など";
			mes "　信頼関係を築いてから";
			mes "　司令官に報告しよう）";
			close;
		}
	case 1:
		if(ASH_6QUE == 14 || ASH_6QUE == 15) {
			misceffect 152,"";
			pushpc 7,3;
			mes "‐あなたが門に近づくと";
			mes "　押し返されてしまった。";
			mes "　どうやら、門には侵入者を拒む";
			mes "　何らかの^FF0000力^000000が放たれているようだ‐";
			next;
			mes "‐あなたはこの門の向こう側に";
			mes "　想像をこえる大きな^FF0000秘密^000000が";
			mes "　隠されているように感じた‐";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（一度、ミッドガルド連合軍駐屯地の";
			mes "司令官アジフに報告しよう）";
			set ASH_6QUE,15;
			close;
		} else {
			misceffect 152,"";
			pushpc 7,3;
			mes "‐あなたが門に近づくと";
			mes "　押し返されてしまった。";
			mes "　どうやら、門には侵入者を拒む";
			mes "　何らかの^FF0000力^000000が放たれているようだ‐";
			next;
			mes "‐この門の向こう側には";
			mes "　想像をこえる大きな^FF0000秘密^000000が";
			mes "　隠されているに違いない。";
			mes "　あなたはミッドガルド連合軍駐屯地の";
			mes "　上層部に報告しようと考えた‐";
			next;
			mes "‐しかし、あなたは上層部と";
			mes "　まだ信頼関係が築けていない‐";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "（ミッドガルド連合軍駐屯地の";
			mes "　^FF0000司令官からの依頼を達成する^000000など";
			mes "　信頼関係を築いてから";
			mes "　司令官に報告しよう）";
			close;
		}
	case 111:
	case 112:
		misceffect 174,"";
		mes "‐拒むようにあなたを";
		mes "　押し返していた力がなくなり、";
		mes "　暖かくて穏やかな力が感じられる‐";
		next;
		mes "‐門に触れると、";
		mes "　どこからか声が聞こえてくる‐";
		next;
		mes "[声]";
		mes "^FF0000約束の言葉^000000を……";
		next;
		if(select("呪文を唱える","後でまた来ます") == 2) {
			mes "[声]";
			mes "……";
			close;
		}
		mes "[声]";
		mes "約束の言葉……";
		mes "守護者の呪文……";
		mes "存在が確認できた。";
		next;
		mes "[守護者の門]";
		mes "私はこの守護者の門を通じて";
		mes "あなたに話しかける。";
		mes "私は守護者の大侍従";
		mes "イグドラシルリアド。";
		next;
		mes "‐穏やかな光に包まれたような感覚が";
		mes "　心の中に広がっていき、";
		mes "　頭に直接声が聞こえてきた‐";
		next;
		mes "[イグドラシルリアド]";
		mes "今はこの世界樹イグドラシルの";
		mes "力が弱まっている時。";
		mes "ゆえに守護者ニーズヘッグが";
		mes "この門に近づくことを望んでいない。";
		next;
		menu "門の中に入りたいのですが",-;
		mes "[イグドラシルリアド]";
		mes "それは適わないこと……";
		mes "今は……";
		mes "……立ち去り";
		next;
		mes "[イグドラシルリアド]";
		mes "…早く…";
		mes "…逃……";
		next;
		mes "‐イグドラシルリアドの";
		mes "　様子がおかしい‐";
		next;
		mes "[イグドラシルリアド]";
		mes "……";
		mes "ああ、早く逃げるのだ……";
		next;
		menu "え!?",-;
		mes "[イグドラシルリアド]";
		mes "やっと……";
		mes "外部と……話すことができた……";
		next;
		menu "どうしたのですか？",-;
		mes "[イグドラシルリアド]";
		mes "ここに……";
		mes "ニーズヘッグは……";
		mes "もう……いない……";
		mes "残されたのは";
		mes "邪悪な竜……影……";
		next;
		mes "[イグドラシルリアド]";
		mes "私も……";
		mes "……肉体を消されて……";
		mes "とらわれている……";
		next;
		mes "[イグドラシルリアド]";
		mes "……";
		next;
		mes "‐イグドラシルリアドの声が";
		mes "　聞こえなくなった。";
		mes "　この門の中で";
		mes "　大変なことがおきているらしい‐";
		next;
		mes "‐あなたは何とかこの";
		mes "　門の中に入る手段がないか";
		mes "　思考した時、";
		mes "　それに反応するように";
		mes "　頭の中に門への入り方の";
		mes "　イメージが伝わってきた‐";
		next;
		mes "‐今、イグドラシルリアドと";
		mes "　^FF0000交信したことによって";
		mes "　この守護者の門が開錠出来る状態^000000";
		mes "　になったようだ。";
		mes "　そして、この先に進むには";
		mes "　^FF0000パーティーを組むことが必要だ^000000‐";
		next;
		mes "‐パーティーリーダーが";
		mes "　鍵の作成をし、作成後、";
		mes "　the Nest of Nidhogに入ろう‐";
		misceffect 174,"";
		if(NYD_1QUE == 111) {
			set NYD_1QUE,200;
			setquest 70900;
			delquest 70893;
		} else if(NYD_1QUE == 112) {
			set NYD_1QUE,201;
			setquest 70900;
			delquest 70898;
		}
		close;
	case 121:
	case 122:
	case 131:
	case 132:
	case 200:
	case 201:
	case 202:
	case 203:
		if(checkquest(3135)) {
			if(checkquest(3135) & 0x2) {
				mes "[守護者の門]";
				mes "イグドラシルの力が安定した。";
				mes "再びこの門を通過したければ";
				mes "もう一度話しかけるがいい。";
				delquest 3135;
				close;
			}
			mes "[守護者の門]";
			mes "イグドラシルの力が弱まり";
			mes "不安定になっている。";
			mes "力が安定するまで";
			mes "この門を通すことができない。";
			next;
			mes "[守護者の門]";
			mes "前回この門を通過してから";
			mes "^FF000072時間^000000ほど経過すれば、";
			mes "力が安定し、再びこの門を";
			mes "通過できるようになるだろう。";
			close;
		}
		else {
			if(getonlinepartymember() < 1) {
				mes "[守護者の門]";
				mes "1人以上のパーティーを組んでから";
				mes "再試行せよ。";
				close;
			}
			mes "‐門に触れると、";
			mes "　どこからか声が聞こえてくる‐";
			next;
			if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
				mes "[守護者の門]";
				mes "この門を通過することが";
				mes "許された者達の代表者よ。";
				mes "ここに入る鍵を作成し、";
				mes "この門を開錠するか？";
				set '@str1$,"the Nest of Nidhog鍵の作成";
				set '@str2$,"the Nest of Nidhogに入る";
			}
			else {
				mes "[守護者の門]";
				mes "守護者の門を通過することが";
				mes "許された者よ。";
				mes "この門を通過するか？";
				set '@str2$,"the Nest of Nidhogに入る";
			}
		}
		next;
		switch(select('@str1$,'@str2$,"キャンセル")) {
		case 1:
			if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
				mes "[守護者の門]";
				mes "汝は代表ではなくなっている。";
				mes "この門を通りたければ";
				mes "再び代表となりこの門に触れるがよい。";
				close;
			}
			mdcreate "the Nest of Nidhog";
			mes "[守護者の門]";
			mes "■パーティー名";
			mes "^0000FF" +strcharinfo(1)+ "^000000";
			mes "■パーティーリーダー";
			mes "^0000FF" +strcharinfo(0)+ "^000000";
			mes "^006400the Nest of Nidhog^000000の鍵の作成試行中。";
			next;
			mes "[守護者の門]";
			mes "作成に成功した場合は";
			mes "再び門に触れるがよい。";
			mes "^FF0000the Nest of Nidhogに入る^000000";
			mes "事を望めばこの門は開かれる。";
			close;
		case 2:
			switch(mdenter("the Nest of Nidhog")) {
			case 0:	// エラーなし
				announce "[" +strcharinfo(1)+ "] パーティーの [" +strcharinfo(0)+ "] が [the Nest of Nidhog] に入場します",0x9,0x00FF99;
				set NYD_2QUE,0;
				setquest 3135;
				donpcevent getmdnpcname("NydControl")+ "::OnStart";
				close;
			case 1:	// パーティー未加入
				mes "[守護者の門]";
				mes "汝、守護者の門を通るために必要な";
				mes "パーティーが解体されている。";
				mes "再試行せよ。";
				close;
			case 2:	// ダンジョン未作成
				if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
					mes "[守護者の門]";
					mes "the Nest of Nidhog の鍵が";
					mes "存在しない。";
					mes "代表であるパーティーリーダーが";
					mes "鍵を作成し終わっていないため、";
					mes "門を開錠することはできない。";
					close;
				}
				else {
					mes "[守護者の門]";
					mes "the Nest of Nidhog の鍵が";
					mes "存在しない。";
					mes "汝の代表であるパーティーリーダーが";
					mes "鍵を作成し終わっていないため、";
					mes "門を開錠することはできない。";
					close;
				}
			default:	// その他エラー
				mes "[守護者の門]";
				mes "不明なエラーが発生。";
				close;
			}
		case 3:
			mes "‐あなたは立ち去った‐";
			close;
		}
	}
	end;
OnTouch:
	if(!NYD_1QUE) {
		misceffect 174,"";
		misceffect 174;
		end;
	}
	end;
}

//============================================================
// ニーズヘッグの巣1F
//------------------------------------------------------------
1@nyd.gat,0,0,0	script	NydControl	-1,{
OnStart:
	if('active > 0)
		end;
	set 'active,1;
	donpcevent getmdnpcname("nyd_call_mon_1")+ "::OnStart";
	donpcevent getmdnpcname("nyd_boss_enter_call")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_red")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_white")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_yellow")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_green")+ "::OnClose";
	hideonnpc getmdnpcname("nyd_to2f_warp");
	hideonnpc getmdnpcname("イグドラシルリアド#");
	end;
}
1@nyd.gat,213,277,5	script	イグドラシルリアド	437,5,5,{
	switch(NYD_2QUE) {
	case 0:
		if(NYD_1QUE == 200 || NYD_1QUE == 201) {
			mes "‐穏やかな光に包まれたような感覚が";
			mes "　心の中に広がっていき、";
			mes "　頭に直接声が聞こえてきた‐";
			next;
			mes "[イグドラシルリアド]";
			mes "私は守護者に仕える";
			mes "イグドラシルリアド……";
			next;
			mes "[イグドラシルリアド]";
			mes "ここは危険だ……";
			mes "もう少しで全てが終わってしまう……";
			next;
			menu "あなたは？",-;
			mes "[イグドラシルリアド]";
			mes "私は守護者ニーズヘッグの";
			mes "大侍従イグドラシルリアドを";
			mes "任された者……";
			next;
			mes "[イグドラシルリアド]";
			mes "私はいまや肉体を失い、";
			mes "魂だけがここに";
			mes "とらわれている存在……";
			next;
			mes "[イグドラシルリアド]";
			mes "そうか、おまえ達は";
			mes "このヨトゥンヘイムでも、";
			mes "アールブヘイムの者でもないのか……";
			next;
			mes "[イグドラシルリアド]";
			mes "だから^FF0000ニーズヘッグの影^000000の力の";
			mes "干渉を受けずに";
			mes "私の声が聞こえたのだな……";
			next;
			menu "どういうことですか？",-;
			mes "[イグドラシルリアド]";
			mes "ニーズヘッグの影は";
			mes "自分の暴虐を隠すために";
			mes "ラフィネ族の侍従がここに来ても";
			mes "私があたかも無事かのように見せる";
			mes "呪いをかけたのだ。";
			next;
			mes "[イグドラシルリアド]";
			mes "しかしその呪いの効果は";
			mes "ラフィネ族の侍従のみに";
			mes "有効だったようだな。";
			next;
			mes "[イグドラシルリアド]";
			mes "さすがに奴もラフィネ族以外、";
			mes "まさか異世界の者がここに来ることは";
			mes "考えていなかったようだ。";
			next;
			menu "ニーズヘッグの影とは？",-;
			mes "[イグドラシルリアド]";
			mes "守護者ニーズヘッグの";
			mes "邪悪な意思のみが具現化した者。";
			mes "全ての生命を";
			mes "飲み込もうとしている……";
			mes "^FF0000本体のニーズヘッグは";
			mes "どこかに消えてしまった^000000……";
			next;
			mes "[イグドラシルリアド]";
			mes "^FF0000イグドラシルが衰弱している原因は";
			mes "ニーズヘッグの影なのだ^000000。";
			mes "イグドラシルの力を、生命を";
			mes "飲み込んでいるのだ。";
			next;
			menu "ニーズヘッグの影が原因？",-;
			mes "[イグドラシルリアド]";
			mes "そうだ。";
			mes "今、ラフィネ族はサファ族が";
			mes "イグドラシルの力を弱めていると";
			mes "戦争を行っているが";
			mes "サファ族が原因ではないのだ。";
			next;
			menu "早く教えないと！",-;
			mes "[イグドラシルリアド]";
			mes "いや、もう遅い……";
			mes "戦争を止めようが";
			mes "ニーズヘッグの影の力は";
			mes "あまりに巨大だ……";
			next;
			menu "ニーズヘッグを倒します",-;
			mes "[イグドラシルリアド]";
			mes "何……？";
			mes "本気か？";
			next;
			menu "はい",-;
			mes "[イグドラシルリアド]";
			mes "異世界の者よ……";
			next;
			mes "[イグドラシルリアド]";
			mes "わかった。";
			next;
			mes "[イグドラシルリアド]";
			mes "では私の力で";
			mes "守護者の関門を開けよう。";
			mes "その先にニーズヘッグの巣があり";
			mes "ニーズヘッグの影がいるのだ。";
			setpartyinmap NYD_2QUE,1;
			donpcevent getmdnpcname("ins_nyd_1f_timer")+ "::OnStart";
			donpcevent getmdnpcname("nyd_call_mon_1")+ "::OnStart2";
			next;
			mes "[イグドラシルリアド]";
			mes "しかし関門を開けることで";
			mes "ニーズヘッグの護衛兵が";
			mes "やってくるはずだ。";
			mes "護衛兵を倒さなくては";
			mes "関門を通ることはできない。";
			next;
			mes "[イグドラシルリアド]";
			mes "私の力で関門を開けるのは";
			mes "30分が限界だ！";
			mes "その間に護衛兵を倒してくれ!!";
			close;
		} else {
			mes "‐穏やかな光に包まれたような感覚が";
			mes "　心の中に広がっていき、";
			mes "　頭に直接声が聞こえてきた‐";
			next;
			mes "[イグドラシルリアド]";
			mes "また来てくれたのだな。";
			mes "礼を言うぞ。";
			next;
			mes "[イグドラシルリアド]";
			mes "ニーズヘッグの影が";
			mes "また力を蓄え始めたのだ。";
			next;
			mes "[イグドラシルリアド]";
			mes "今のうちに";
			mes "奴の力を抑えなくては";
			mes "大変なことになる。";
			next;
			mes "[イグドラシルリアド]";
			mes "では私の力で";
			mes "守護者の関門を開けよう。";
			mes "その先にニーズヘッグの巣があり";
			mes "ニーズヘッグの影がいるのだ。";
			next;
			mes "[イグドラシルリアド]";
			mes "しかし関門を開けることで";
			mes "ニーズヘッグの護衛兵が";
			mes "やってくるはずだ。";
			mes "護衛兵を倒さなくては";
			mes "関門を通ることはできない。";
			next;
			mes "[イグドラシルリアド]";
			mes "私の力で関門を開けるのは";
			mes "30分が限界だ！";
			mes "その間に護衛兵を倒してくれ!!";
			setpartyinmap NYD_2QUE,1;
			donpcevent getmdnpcname("ins_nyd_1f_timer")+ "::OnStart";
			donpcevent getmdnpcname("nyd_call_mon_1")+ "::OnStart2";
			close;
		}
	case 1:
		mes "[イグドラシルリアド]";
		mes "ニーズヘッグの影がいる";
		mes "ニーズヘッグの巣は";
		mes "ここから北にある。";
		next;
		mes "[イグドラシルリアド]";
		mes "ニーズヘッグの護衛兵を全て倒せば、";
		mes "関門が開かれるだろう。";
		mes "12体の護衛兵を全て倒すのだ！";
		close;
	case 2:
		mes "[イグドラシルリアド]";
		mes "私にできることはここまでか……";
		mes "ここから北にある関門から";
		mes "ニーズヘッグの巣に行くのだ。";
		next;
		mes "[イグドラシルリアド]";
		mes "先に私はニーズヘッグの巣で";
		mes "待っている！";
		hideonnpc;
		close;
	default:
		warp "mid_camp.gat",100,100;
		end;
	}
}

1@nyd.gat,1,1,0	script	nyd_call_mon_1	139,{
OnStart:
	set '@mdmap$,getmdmapname("1@nyd.gat");
	set '@mdnpc$,getmdnpcname("nyd_call_mon_1");
	areamonster '@mdmap$,0,0,0,0,"エンシェントツリー",2019,20,'@mdnpc$+ "::OnKilled1";
	areamonster '@mdmap$,0,0,0,0,"リンコ",2020,15,'@mdnpc$+ "::OnKilled2";
	areamonster '@mdmap$,0,0,0,0,"フィラ",2021,15,'@mdnpc$+ "::OnKilled3";
	areamonster '@mdmap$,0,0,0,0,"アクアエレメンタル",2016,15,'@mdnpc$+ "::OnKilled4";
	areamonster '@mdmap$,0,0,0,0,"ダークピンギキュラ",2015,15,'@mdnpc$+ "::OnKilled5";
	end;
OnStart2:
	if('flag) end;
	set 'flag,1;
	set '@mdmap$,getmdmapname("1@nyd.gat");
	set '@mdnpc$,getmdnpcname("nyd_call_mon_1");
	monster '@mdmap$,220,250,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,220,252,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,240,270,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,240,272,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,200,200,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,210,210,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,225,265,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,225,270,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,245,235,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,255,255,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,225,245,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,230,280,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	announce "ニーズヘッグの護衛兵 : 守護者の聖所を守れ！ 進入者を排除せよ！",0x9,0x00FF99;
	end;
OnKilled:
	set 'mob,getmapmobs(getmdmapname("1@nyd.gat"),getmdnpcname("nyd_call_mon_1")+ "::OnKilled");
	if('mob <= 0) {
		announce "ニーズヘッグの護衛兵を全て倒した！",0x9,0x00FF99;
		hideoffnpc getmdnpcname("nyd_to2f_warp");
		setpartyinmap NYD_2QUE,2;
	} else
		announce "残り [" +'mob+ "]体",0x9,0x00FF99;
	end;
OnKilled1:
	areamonster getmdmapname("1@nyd.gat"),0,0,0,0,"エンシェントツリー",2019,1,getmdnpcname("nyd_call_mon_1")+ "::OnKilled1";
	end;
OnKilled2:
	areamonster getmdmapname("1@nyd.gat"),0,0,0,0,"リンコ",2020,1,getmdnpcname("nyd_call_mon_1")+ "::OnKilled2";
	end;
OnKilled3:
	areamonster getmdmapname("1@nyd.gat"),0,0,0,0,"フィラ",2021,1,getmdnpcname("nyd_call_mon_1")+ "::OnKilled3";
	end;
OnKilled4:
	areamonster getmdmapname("1@nyd.gat"),0,0,0,0,"アクアエレメンタル",2016,1,getmdnpcname("nyd_call_mon_1")+ "::OnKilled4";
	end;
OnKilled5:
	areamonster getmdmapname("1@nyd.gat"),0,0,0,0,"ダークピンギキュラ",2015,1,getmdnpcname("nyd_call_mon_1")+ "::OnKilled5";
	end;
}

1@nyd.gat,1,2,0	script	ins_nyd_1f_timer	139,{
OnStart:
	initnpctimer;
	end;
OnTimer900000:
	announce "イグドラシルリアド : 時間があまり残っていない！　急ぐのだ！",0x9,0xFFFF00;
	end;
OnTimer1200000:
	announce "イグドラシルリアド : 私の力はもう持たない！　急ぐのだ！",0x9,0xFFFF00;
	end;
OnTimer1500000:
	announce "イグドラシルリアド : もうそろそろ限界だ……",0x9,0xFFFF00;
	end;
OnTimer1800000:
	announce "イグドラシルリアド : 駄目だ、門が閉じてしまった…… 失敗だ……",0x9,0xFFFF00;
	end;
OnTimer1830000:
	announce "イグドラシルリアド : 私の最後の力であなた達を脱出させよう……",0x9,0xFFFF00;
	end;
OnTimer1850000:
	killmonster getmdmapname("1@nyd.gat"),getmdnpcname("nyd_call_mon_1")+ "::OnKilled";
	mapwarp getmdmapname("1@nyd.gat"),"mid_camp.gat",310,150;
	stopnpctimer;
	end;
}

1@nyd.gat,195,320,0	warp	nyd_to2f_warp	5,5,2@nyd.gat,200,10

//============================================================
// ニーズヘッグの巣2F
//------------------------------------------------------------
2@nyd.gat,200,14,0	script	nyd_2f_enter	139,6,6,{
	donpcevent getmdnpcname("nyd_2f_enter_broad")+ "::OnStart";
	hideonnpc getmdnpcname("nyd_2f_enter");
	end;
}

2@nyd.gat,1,1,0	script	nyd_2f_enter_broad	139,{
OnStart:
	initnpctimer;
	end;
OnTimer12000:
	announce "ニーズヘッグの影 : 足りぬ…… 全然足りぬ…… 全然力が足りぬぞ!!",0x9,0xFFFF00;
	end;
OnTimer15000:
	announce "ニーズヘッグの影 : 世界樹…… もっとイグドラシルの生命が必要だ……",0x9,0xFFFF00;
	end;
OnTimer18000:
	announce "ニーズヘッグの影 : イグドラシルの生命を全て吸い尽くし…… そして破壊する…… 全てをだ……",0x9,0xFFFF00;
	stopnpctimer;
	end;
}

2@nyd.gat,199,178,0	script	nyd_ddr_control	139,6,6,{
	misceffect 152,"";
	mes "‐派手な色調の床から";
	mes "　正体不明の力が体内に";
	mes "　流れ込んでくる‐";
	next;
	mes "‐未知なる力はあなたの体を";
	mes "　他の場所へ転送させた‐";
	close2;
	warp getmdmapname("2@nyd.gat"),199,255;
	end;
}

2@nyd.gat,199,268,0	script	nyd_2f_boss_enter	139,8,8,{
	donpcevent getmdnpcname("nyd_boss_enter_call")+ "::OnStart2";
	hideonnpc getmdnpcname("nyd_2f_boss_enter");
	end;
}

2@nyd.gat,2,2,0	script	nyd_boss_enter_call	139,{
OnStart:
	set '@mdmap$,getmdmapname("2@nyd.gat");
	set '@mdnpc$,getmdnpcname("nyd_call_mon_1");
	areamonster '@mdmap$,20,12,380,172,"リンコ",2020,20,'@mdnpc$+ "::OnKilled1";
	areamonster '@mdmap$,20,12,380,172,"フィラ",2021,20,'@mdnpc$+ "::OnKilled2";
	areamonster '@mdmap$,20,12,380,172,"ダークシャドウ",2023,20,'@mdnpc$+ "::OnKilled3";
	areamonster '@mdmap$,20,12,380,172,"ダークピンギキュラ",2015,20,'@mdnpc$+ "::OnKilled4";
	end;
OnStart2:
	monster getmdmapname("2@nyd.gat"),199,327,"ニーズヘッグの影",2022,1,getmdnpcname("nyd_boss_enter_call")+ "::OnKilled";
	announce "ニーズヘッグの影 : この世界樹の生命を全て飲み込むより先に、貴様らを飲み込んでくれるわ!!",0x9,0x00FF00;
	initnpctimer;
	end;
OnReset:
	initnpctimer;
	end;
OnTimer180000:
	setnpctimer 0;
	switch(rand(4)) {
	case 0:
		announce "ニーズヘッグの影 : その部屋を貴様の鮮血でもっと赤く染めるがいい！",0x9,0xFFFF00;
		donpcevent getmdnpcname("nyd_crystal_white")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_yellow")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_green")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_red")+ "::OnStart";
		mapwarp getmdmapname("2@nyd.gat"),getmdmapname("2@nyd.gat"),115,278;
		end;
	case 1:
		announce "ニーズヘッグの影 : その青き水晶の前で凍え、朽ち果てるがいい！",0x9,0xFFFF00;
		donpcevent getmdnpcname("nyd_crystal_red")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_yellow")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_green")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_white")+ "::OnStart";
		mapwarp getmdmapname("2@nyd.gat"),getmdmapname("2@nyd.gat"),115,373;
		end;
	case 2:
		announce "ニーズヘッグの影 : その部屋で我に立ち向かった愚かさを悔いるがいい！",0x9,0xFFFF00;
		donpcevent getmdnpcname("nyd_crystal_red")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_white")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_green")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_yellow")+ "::OnStart";
		mapwarp getmdmapname("2@nyd.gat"),getmdmapname("2@nyd.gat"),284,278;
		end;
	case 3:
		announce "ニーズヘッグの影 : その部屋で朽ち果て、永遠に眠るがいい！",0x9,0xFFFF00;
		donpcevent getmdnpcname("nyd_crystal_red")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_white")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_yellow")+ "::OnClose";
		donpcevent getmdnpcname("nyd_crystal_green")+ "::OnStart";
		mapwarp getmdmapname("2@nyd.gat"),getmdmapname("2@nyd.gat"),284,374;
		end;
	}
	stopnpctimer;
	end;
OnKilled:
	announce "ニーズヘッグの影 : き、貴様ぁぁぁ…… お、俺のち、力がなくなっていく……",0x9,0x00FF99;
	donpcevent getmdnpcname("イグドラシルリアド#")+ "::OnStart";
	stopnpctimer;
	donpcevent getmdnpcname("nyd_crystal_red")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_white")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_yellow")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_green")+ "::OnClose";
	end;
OnKilled1:
	areamonster getmdmapname("2@nyd.gat"),20,12,380,172,"リンコ",2020,1,getmdnpcname("nyd_call_mon_1")+ "::OnKilled1";
	end;
OnKilled2:
	areamonster getmdmapname("2@nyd.gat"),20,12,380,172,"フィラ",2021,1,getmdnpcname("nyd_call_mon_1")+ "::OnKilled2";
	end;
OnKilled3:
	areamonster getmdmapname("2@nyd.gat"),20,12,380,172,"ダークシャドウ",2023,1,getmdnpcname("nyd_call_mon_1")+ "::OnKilled3";
	end;
OnKilled4:
	areamonster getmdmapname("2@nyd.gat"),20,12,380,172,"ダークピンギキュラ",2015,1,getmdnpcname("nyd_call_mon_1")+ "::OnKilled4";
	end;
}

2@nyd.gat,202,324,5	script	イグドラシルリアド#	437,{
	if(NYD_1QUE == 200 || NYD_1QUE == 201) {
		mes "[イグドラシルリアド]";
		mes "ありがとう。";
		mes "あなたはイグドラシルを、";
		mes "いや世界を救ったのだ。";
		next;
		mes "[イグドラシルリアド]";
		mes "邪悪なニーズヘッグの影は";
		mes "いなくなった。";
		mes "……それは完全な消滅ではなく、";
		mes "力を失い一時的に";
		mes "眠りについただけにすぎない。";
		next;
		mes "[イグドラシルリアド]";
		mes "だが、いかに強大な力を持つ";
		mes "ニーズヘッグの影といえど";
		mes "力を取り戻すのに";
		mes "多くの時間を要するであろう。";
		next;
		mes "[イグドラシルリアド]";
		mes "それにしても";
		mes "あなたはすごい力を持っている……";
		mes "あなたを正式な";
		mes "^FF0000侍従^000000として認めよう。";
		next;
		misceffect 152,"";
		mes "[イグドラシルリアド]";
		mes "これでニーズヘッグの巣に";
		mes "何度でも入れるようになった。";
		next;
		mes "[イグドラシルリアド]";
		mes "ただし、イグドラシルの力が";
		mes "不安定になっている今、";
		mes "再び入るには";
		mes "少しばかり時間が必要だがな。";
		next;
		mes "[イグドラシルリアド]";
		mes "そしてあなたにお願いがある。";
		mes "影が力を取り戻す前に";
		mes "スプレンディッドとマヌクの長に";
		mes "この事態を伝えて欲しいのだ。";
		next;
		mes "[イグドラシルリアド]";
		mes "世界樹イグドラシルの衰弱は";
		mes "サファ族のせいではない。";
		next;
		mes "[イグドラシルリアド]";
		mes "犯人は守護者、";
		mes "ニーズヘッグの影なのだ！";
		mes "手遅れになる前に";
		mes "急いでこの事実を皆に知らせるのだ！";
		next;
		menu "わかりました",-;
		mes "[イグドラシルリアド]";
		mes "それでは私の力であなたを";
		mes "この地から出そうではないか。";
		mes "準備はいいか？";
		next;
		if(NYD_1QUE == 200) {
			mes "‐あなたはラフィネ族と";
			mes "　手を結んでいる。";
			mes "　ラフィネ族の司令官";
			mes "　レビオルディルに報告しよう‐";
			set NYD_1QUE,202;
			setquest 70905;
			delquest 70900;
		}
		else if(NYD_1QUE == 201) {
			mes "‐あなたはサファ族と手を結んでいる。";
			mes "　サファ族の首長エトルに報告しよう‐";
			set NYD_1QUE,203;
			setquest 70907;
			delquest 70900;
		}
	} else {
		mes "[イグドラシルリアド]";
		mes "ありがとう。";
		mes "これでしばらくは";
		mes "ニーズヘッグの影も力を失うだろう。";
		next;
		mes "[イグドラシルリアド]";
		mes "それにしてもすごい力だ……";
		mes "ニーズヘッグの影を";
		mes "こうも倒すとは……";
		next;
		mes "[イグドラシルリアド]";
		mes "しかしこれは奴が一時的な";
		mes "眠りについただけに過ぎない。";
		mes "奴は力を蓄え再び現れるだろう。";
		next;
		mes "[イグドラシルリアド]";
		mes "それでは私の力であなたを";
		mes "この地から出そうではないか。";
		mes "準備はいいか？";
	}
	next;
	if(select("今すぐお願いします","少し時間をください") == 2) {
		mes "[イグドラシルリアド]";
		mes "では準備ができたら";
		mes "いつでも話しかけてくれ。";
		close;
	}
	warp "nyd_dun02.gat",97,196;
	end;
OnStart:
	hideoffnpc getmdnpcname("イグドラシルリアド#");
	announce "イグドラシルリアド : よく影を倒してくれた！ 全員、中央の魔法陣に集まるのだ。",0x9,0x00FF99;
	end;
}

2@nyd.gat,115,278,0	script	nyd_crystal_red	139,5,5,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_red");
	donpcevent getmdnpcname("nyd_crystal_red1")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_red2")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_red3")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_red_c")+ "::OnStart";
	initnpctimer;
	end;
OnClose:
	donpcevent getmdnpcname("nyd_crystal_red1")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_red2")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_red3")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_red_c")+ "::OnClose";
	hideonnpc getmdnpcname("nyd_crystal_red");
	end;
OnTouch:
	percentheal -50,0;
	percentheal -30,0;
	sc_start SC_BLEED,60000,5;
	end;
OnTimer10000:
	hideonnpc getmdnpcname("nyd_crystal_red");
	stopnpctimer;
	end;
}

2@nyd.gat,6,6,0	script	nyd_crystal_red_c	139,{
OnStart:
	killmonster getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_red_c")+ "::OnKilled";
	set '@mdmap$,getmdmapname("2@nyd.gat");
	set '@mdnpc$,getmdnpcname("nyd_crystal_red_c");
	monster '@mdmap$,120,285,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,119,286,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,120,270,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,119,269,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,118,270,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	end;
OnClose:
	killmonster getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_red_c")+ "::OnKilled";
	end;
OnKilled:
	set 'mob,getmapmobs(getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_red_c")+ "::OnKilled");
	if('mob <= 0) {
		announce "ニーズヘッグの影 : ほう、なかなかやるな…… では今度はこの俺が相手だっ！",0x9,0x00FF00;
		donpcevent getmdnpcname("nyd_crystal_red")+ "::OnClose";
		donpcevent getmdnpcname("nyd_boss_enter_call")+ "::OnReset";
	}
	end;
}

2@nyd.gat,130,298,0	script	nyd_crystal_red1	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_red1");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_red1");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,278;
	end;
}

2@nyd.gat,142,296,0	script	nyd_crystal_red2	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_red2");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_red2");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,278;
	end;
}

2@nyd.gat,145,283,0	script	nyd_crystal_red3	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_red3");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_red3");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,278;
	end;
}

2@nyd.gat,115,373,0	script	nyd_crystal_white	139,5,5,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_white");
	donpcevent getmdnpcname("nyd_crystal_white1")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_white2")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_white3")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_white_c")+ "::OnStart";
	initnpctimer;
	end;
OnClose:
	donpcevent getmdnpcname("nyd_crystal_white1")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_white2")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_white3")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_white_c")+ "::OnClose";
	hideonnpc getmdnpcname("nyd_crystal_white");
	end;
OnTouch:
	percentheal -50,0;
	sc_start SC_FREEZE,20000,5;
	end;
OnTimer10000:
	hideonnpc getmdnpcname("nyd_crystal_white");
	stopnpctimer;
	end;
}

2@nyd.gat,6,7,0	script	nyd_crystal_white_c	139,{
OnStart:
	killmonster getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_white_c")+ "::OnKilled";
	set '@mdmap$,getmdmapname("2@nyd.gat");
	set '@mdnpc$,getmdnpcname("nyd_crystal_white_c");
	monster '@mdmap$,120,380,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,119,381,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,120,367,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,119,366,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,118,365,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	end;
OnClose:
	killmonster getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_white_c")+ "::OnKilled";
	end;
OnKilled:
	set 'mob,getmapmobs(getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_white_c")+ "::OnKilled");
	if('mob <= 0) {
		announce "ニーズヘッグの影 : 突破したか！ ならばこの俺が相手してやろう！ ここまで来るがいい！",0x9,0x00FF00;
		donpcevent getmdnpcname("nyd_crystal_white")+ "::OnClose";
		donpcevent getmdnpcname("nyd_boss_enter_call")+ "::OnReset";
	}
	end;
}

2@nyd.gat,127,354,0	script	nyd_crystal_white1	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_white1");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_white1");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,373;
	end;
}

2@nyd.gat,140,357,0	script	nyd_crystal_white2	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_white2");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_white2");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,373;
	end;
}

2@nyd.gat,145,367,0	script	nyd_crystal_white3	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_white3");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_white3");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,373;
	end;
}

2@nyd.gat,284,278,0	script	nyd_crystal_yellow	139,5,5,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_yellow");
	donpcevent getmdnpcname("nyd_crystal_yellow1")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_yellow2")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_yellow3")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_yellow_")+ "::OnStart";
	initnpctimer;
	end;
OnClose:
	donpcevent getmdnpcname("nyd_crystal_yellow1")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_yellow2")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_yellow3")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_yellow_")+ "::OnClose";
	hideonnpc getmdnpcname("nyd_crystal_yellow");
	end;
OnTouch:
	percentheal 0,-50;
	sc_start SC_SLEEP,20000,5;
	sc_start SC_CONFUSION,60000,5;
	end;
OnTimer10000:
	hideonnpc getmdnpcname("nyd_crystal_yellow");
	stopnpctimer;
	end;
}

2@nyd.gat,6,8,0	script	nyd_crystal_yellow_	139,{
OnStart:
	killmonster getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_yellow_")+ "::OnKilled";
	set '@mdmap$,getmdmapname("2@nyd.gat");
	set '@mdnpc$,getmdnpcname("nyd_crystal_yellow_");
	monster '@mdmap$,282,284,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,283,283,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,280,275,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,281,276,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,281,277,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	end;
OnClose:
	killmonster getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_yellow_")+ "::OnKilled";
	end;
OnKilled:
	set 'mob,getmapmobs(getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_yellow_")+ "::OnKilled");
	if('mob <= 0) {
		announce "ニーズヘッグの影 : ほう、なかなかやるな……よかろう。この俺自ら葬ってやろう！",0x9,0x00FF00;
		donpcevent getmdnpcname("nyd_crystal_yellow")+ "::OnClose";
		donpcevent getmdnpcname("nyd_boss_enter_call")+ "::OnReset";
	}
	end;
}

2@nyd.gat,255,285,0	script	nyd_crystal_yellow1	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_yellow1");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_yellow1");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,278;
	end;
}

2@nyd.gat,257,296,0	script	nyd_crystal_yellow2	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_yellow2");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_yellow2");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,278;
	end;
}

2@nyd.gat,268,300,0	script	nyd_crystal_yellow3	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_yellow3");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_yellow3");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,278;
	end;
}

2@nyd.gat,284,374,0	script	nyd_crystal_green	139,5,5,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_green");
	donpcevent getmdnpcname("nyd_crystal_green1")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_green2")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_green3")+ "::OnStart";
	donpcevent getmdnpcname("nyd_crystal_green_c")+ "::OnStart";
	initnpctimer;
	end;
OnClose:
	donpcevent getmdnpcname("nyd_crystal_green1")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_green2")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_green3")+ "::OnClose";
	donpcevent getmdnpcname("nyd_crystal_green_c")+ "::OnClose";
	hideonnpc getmdnpcname("nyd_crystal_green");
	end;
OnTouch:
	percentheal -50,-50;
	sc_start SC_POISON,60000,5;
	end;
OnTimer10000:
	hideonnpc getmdnpcname("nyd_crystal_green");
	stopnpctimer;
	end;
}

2@nyd.gat,6,9,0	script	nyd_crystal_green_c	139,{
OnStart:
	killmonster getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_green_c")+ "::OnKilled";
	set '@mdmap$,getmdmapname("2@nyd.gat");
	set '@mdnpc$,getmdnpcname("nyd_crystal_green_c");
	monster '@mdmap$,282,378,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,283,377,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,280,368,"ニーズヘッグの護衛兵",2020,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,281,368,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	monster '@mdmap$,281,367,"ニーズヘッグの護衛兵",2021,1,'@mdnpc$+ "::OnKilled";
	end;
OnClose:
	killmonster getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_green_c")+ "::OnKilled";
	end;
OnKilled:
	set 'mob,getmapmobs(getmdmapname("2@nyd.gat"),getmdnpcname("nyd_crystal_green_c")+ "::OnKilled");
	if('mob <= 0) {
		announce "ニーズヘッグの影 : 突破したか…… そんなにこの俺の手で葬って欲しいのか？ いいだろう、ここまで来るがいい！",0x9,0x00FF00;
		donpcevent getmdnpcname("nyd_crystal_green")+ "::OnClose";
		donpcevent getmdnpcname("nyd_boss_enter_call")+ "::OnReset";
	}
	end;
}

2@nyd.gat,274,356,0	script	nyd_crystal_green1	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_green1");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_green1");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,278;
	end;
}

2@nyd.gat,260,356,0	script	nyd_crystal_green2	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_green2");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_green2");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,278;
	end;
}

2@nyd.gat,258,368,0	script	nyd_crystal_green3	139,6,6,{
OnStart:
	hideoffnpc getmdnpcname("nyd_crystal_green3");
	end;
OnClose:
	hideonnpc getmdnpcname("nyd_crystal_green3");
	end;
OnTouch:
	warp getmdmapname("2@nyd.gat"),115,278;
	end;
}
