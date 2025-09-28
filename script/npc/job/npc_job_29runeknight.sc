//= Auriga Script ==============================================================
// Ragnarok Online RuneKnight Jobchange Script	by Blaze
//- Registry -------------------------------------------------------------------
// CHANGE_RK -> 0～16
// CHANGE_RK_RUNE -> 0～
//==============================================================================

//============================================================
// マップフラグ
//------------------------------------------------------------
job3_rune01.gat	mapflag	nomemo		dummy
job3_rune01.gat	mapflag	noteleport	dummy
job3_rune01.gat	mapflag	nosave		SavePoint
job3_rune01.gat	mapflag	nobranch	dummy
job3_rune01.gat	mapflag	nopenalty	dummy
job3_rune01.gat	mapflag	noicewall	dummy
job3_rune02.gat	mapflag	nomemo		dummy
job3_rune02.gat	mapflag	noteleport	dummy
job3_rune02.gat	mapflag	nosave		SavePoint
job3_rune02.gat	mapflag	nobranch	dummy
job3_rune02.gat	mapflag	nopenalty	dummy
job3_rune02.gat	mapflag	noicewall	dummy

//============================================================
// ワープポイント
//------------------------------------------------------------
job3_rune01.gat,79,72,0	warp	#gate_to_rune01	1,1,gl_knt02.gat,150,60

//============================================================
// 簡易倉庫（npc_misc_storage.scより）
//------------------------------------------------------------
job3_rune01.gat,92,62,4	script	倉庫管理人	80,{
	callfunc "Func_StorageManager",50,0;
	close;
}
job3_rune01.gat,89,60,6	script	メイン倉庫	464,{
	callfunc "Func_Storage",50,0;
	end;
}
job3_rune01.gat,91,60,4	script	サブ倉庫1	464,{
	callfunc "Func_Storage",50,1;
	end;
}
job3_rune01.gat,93,60,4	script	サブ倉庫2	464,{
	callfunc "Func_Storage",50,2;
	end;
}
job3_rune01.gat,95,60,4	script	サブ倉庫3	464,{
	callfunc "Func_Storage",50,3;
	end;
}

//============================================================
// 開始NPC
//------------------------------------------------------------
prt_in.gat,162,24,3	script	華麗なる騎士	470,{
	if(Job == Job_RuneKnight) {
		mes "[光輝のルーンナイト　マヌエル]";
		mes "いまや君も我らギルドの立派な一員だ。";
		mes "はじめて君に会った時の姿がまだ";
		mes "記憶に残っているというのに……。";
		next;
		mes "[光輝のルーンナイト　マヌエル]";
		mes "我らが向かっている広大な道が";
		mes "いつまでも平坦なわけではないが";
		mes "それこそが人生であり";
		mes "剣の道ではないか……。";
		next;
		mes "[光輝のルーンナイト　マヌエル]";
		mes "我らの輝かしい未来の為に、乾杯！";
		if(checkquest(129700)) {
			next;
			mes "[インフォメーション]";
			mes "あなたは転職試験の";
			mes "クリア報酬";
			mes "ステータス・スキル一括リセット権";
			mes "を所持しています。";
			next;
			mes "[インフォメーション]";
			mes "権利を利用する場合、";
			mes "イズルードにいる";
			mes "サンシイを訪ねてください。";
		}
		close;
	}
	if(Job != Job_Knight || Upper == UPPER_NORMAL) {
		mes "[華麗なる騎士]";
		mes "この世には様々な道がある……";
		mes "しかし、数え切れない道の中で";
		mes "自分が行くべき道を正しく選択できる";
		mes "人間は少ない。";
		next;
		mes "[華麗なる騎士]";
		mes "それはそれとして、ここの酒は";
		mes "本当に旨い。";
		mes "君も一杯どうだ？";
		next;
		if(select("いただきます","遠慮します") == 2) {
			mes "[華麗なる騎士]";
			mes "そうか……残念ながら君は";
			mes "風流が理解できないようだ。";
			close;
		}
		mes "[華麗なる騎士]";
		mes "全てにおいて、変化という風が";
		mes "良い結果をもたらすものではないと";
		mes "私は信じている。";
		next;
		mes "[華麗なる騎士]";
		mes "この酒みたいにな。";
		mes "この酒の味は、いつまでも";
		mes "守られていて欲しいと思う。";
		close;
	}
	switch(CHANGE_RK) {
	case 0:
		emotion 1,"";
		mes "‐男が酒をあおっている。";
		mes "　騎士だろうか？‐";
		next;
		if(select("話しかける","通り過ぎる") == 2) {
			mes "‐関わらない方が良さそうだ‐";
			close;
		}
		if((Upper == UPPER_HIGH && BaseLevel < 90) || (Upper == UPPER_BABY && (BaseLevel < 99 || JobLevel < 50))) {
			mes "[華麗なる騎士]";
			mes "君が今のままの道を歩み続けるのなら";
			mes "いつか、その限界を思い知るだろう。";
			mes "かつての私がそうであったように……。";
			next;
			mes "[華麗なる騎士]";
			if(Upper == UPPER_HIGH)
				mes  "^3377FFBaseLvが90以上^000000の時が";
			else
				mes  "^3377FFBaseLvが99、JobLvが50^000000の時が";		// 養子のとき未調査
			mes "その時となろう。";
			next;
			mes "[華麗なる騎士]";
			mes "その時が来たら、私が君を";
			mes "助けることができるはずだ。";
			mes "今は酒を酌み交わすことしか";
			mes "できないが……。";
			next;
			mes "[華麗なる騎士]";
			mes "いずれ来るその日の為に……乾杯！";
			close;
		}
		cloakoffnpc "転職代行係#RK";
		misceffect 78,"転職代行係#RK";
		if(callfunc("Func_Job3rd",Job_RuneKnight)) {
			cloakonnpc "転職代行係#RK";
			end;
		}
		cloakonnpc "転職代行係#RK";
		mes "[華麗なる騎士]";
		mes "この世には様々な道がある……";
		mes "しかし、数え切れない道の中で";
		mes "自分が行くべき道を正しく選択できる";
		mes "人間は少ない。";
		next;
		mes "[華麗なる騎士]";
		mes "それはそれとして、ここの酒は";
		mes "本当に旨い。";
		mes "君も一杯どうだ？";
		next;
		if(select("いただきます","遠慮します") == 2) {
			mes "[華麗なる騎士]";
			mes "そうか……残念ながら君は";
			mes "風流が理解できないようだ。";
			close;
		}
		mes "[華麗なる騎士]";
		mes "君も剣の道を歩む者なのか……";
		mes "ならば、話が通じるだろう。";
		mes "剣と生きる者同士で飲めば";
		mes "酒もいっそう旨くなるというもの。";
		next;
		mes "[華麗なる騎士]";
		mes "この酒は私のおごりだ。";
		mes "未来の親友になるかも知れない";
		mes "君の為に。";
		next;
		mes "[華麗なる騎士]";
		mes "ふむ、私が見るかぎり君は";
		mes "これから新しい道を見つけ";
		mes "旅立つ準備ができているようだ。";
		next;
		mes "[華麗なる騎士]";
		mes "剣の道を歩むということは";
		mes "苦しい修行の連続だ。";
		mes "これまで君が歩んできた日々より";
		mes "さらに険しい旅が待っているだろう。";
		next;
		mes "[華麗なる騎士]";
		mes "……君が限界を超えた先にある";
		mes "新しい道に進むことを願うのであれば";
		mes "私が手助けをしよう。";
		next;
		mes "[華麗なる騎士]";
		mes "剣の限界を破ることを渇望し";
		mes "調和と神秘を悟った真の剣士の道……";
		mes "それが^FF0000ルーンナイト^000000だ。";
		next;
		mes "[華麗なる騎士]";
		mes "我らと共に歩む同志になって欲しい。";
		mes "君なら我らの同志として充分な資格を";
		mes "備えているのだから。";
		next;
		mes "[華麗なる騎士]";
		mes "君が望むなら、ルーンナイトへの道を";
		mes "指し示す師匠達を紹介しよう。";
		next;
		if(select("少し時間をください","覚悟はできています") == 1) {
			mes "[華麗なる騎士]";
			mes "新しい挑戦には、常に準備が必要だ。";
			mes "分かった。君を待つことにしよう。";
			next;
			mes "[華麗なる騎士]";
			mes "新しく進む道の先に存在するのは";
			mes "必ずしも栄光だけではないからな。";
			close;
		}
		mes "[華麗なる騎士]";
		mes "そうか！　ならば、私が同志たちに";
		mes "君を推薦しよう。";
		next;
		mes "[華麗なる騎士]";
		mes "君は^0000FFグラストヘイム^000000を知っているか？";
		mes "^0000FFグラストヘイム^000000にて";
		mes "君を導いてくれるルーンナイトが";
		mes "待っているはずだ。";
		next;
		mes "[光輝のルーンナイト　マヌエル]";
		mes "私の名前はマヌエル。";
		mes "光輝のルーンナイトと呼ばれている。";
		mes "私から話を聞いて来たと伝えれば";
		mes "次の道筋を示してくれるだろう。";
		next;
		mes "[光輝のルーンナイト　マヌエル]";
		mes "君が我らの同志となり";
		mes "同じ道を歩むことができるその日を";
		mes "ここで待つとしよう。";
		set CHANGE_RK,1;
		setquest 3200;
		close;
	case 1:
		mes "[光輝のルーンナイト　マヌエル]";
		mes "^0000FFグラストヘイム^000000にて";
		mes "君を導いてくれるルーンナイトが";
		mes "待っているはずだ。";
		next;
		mes "[光輝のルーンナイト　マヌエル]";
		mes "私から話を聞いて来たと伝えれば";
		mes "次の道筋を示してくれるだろう。";
		next;
		mes "[光輝のルーンナイト　マヌエル]";
		mes "君が我らの同志となり";
		mes "同じ道を歩むことができるその日を";
		mes "ここで待つとしよう。";
		close;
	default:
		emotion 1;
		mes "[光輝のルーンナイト　マヌエル]";
		mes "君には今、進むべき道が";
		mes "示されているのではないか？";
		next;
		mes "[光輝のルーンナイト　マヌエル]";
		mes "私が間違っているのであれば";
		mes "気にしないでくれ。";
		mes "ふむ、変わらないのは";
		mes "この酒の香りだけか……。";
		close;
	}
}

prt_in.gat,164,26,3	script(CLOAKED)	転職代行係#RK	888,{
	cloakonnpc;
	end;
}

//============================================================
// 
//------------------------------------------------------------
glast_01.gat,44,363,3	script	ルーンの引導者	468,{
	if(Job == Job_RuneKnight) {
		mes "[ルーンの引導者　ユングベルグ]";
		mes "……我らの同志";
		mes strcharinfo(0) + "ではないか。";
		mes "よく来てくれた。";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "これから我らの志をこの世に広める";
		mes "人材として期待している。";
		close;
	}
	if(Job != Job_Knight) {
		mes "[ルーンの引導者　ユングベルグ]";
		mes "オレは、この呪われたグラストヘイムに";
		mes "宿ったソードマスター";
		mes "ベルゼブの遺志を受け継ぐ";
		mes "一人の騎士にすぎない。";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "剣の道とは別の道を歩む者に";
		mes "我々の志と義気は理解できないだろう。";
		mes "オレのことは気にせず、自らの道を";
		mes "進んだ方がいい。";
		close;
	}
	switch(CHANGE_RK) {
	case 0:
		mes "[ルーンの引導者　ユングベルグ]";
		mes "君はこのグラストヘイムの";
		mes "呪われた亡霊なのか？";
		mes "あるいは何も知らずに迷い込んだ";
		mes "冒険者なのか？";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "君息をする人間であるなら";
		mes "オレの話をよく聞いてくれ……。";
		mes "オレなら、こんな所をうろうろして";
		mes "命を危険にさらすような真似はしない。";
		next;
		switch(select("あなたは誰ですか？","何をしてるんですか？","会話をやめる")) {
		case 1:
			mes "[ルーンの引導者　ユングベルグ]";
			mes "オレは、この呪われたグラストヘイムに";
			mes "宿ったソードマスター　ベルゼブの";
			mes "遺志を受け継ぐ、一人の騎士にすぎない。";
			next;
			mes "[ルーンの引導者　ユングベルグ]";
			mes "君も剣の道を歩む者なら";
			mes "いつか我々と同じ道を";
			mes "歩むことになるかもしれないな。";
			close;
		case 2:
			mes "[ルーンの引導者　ユングベルグ]";
			mes "オレも君と同じく剣の道を歩む者だ。";
			mes "今は、君のような偉大なる";
			mes "ルーンミッドガッツ王国の";
			mes "騎士ではないが……。";
			next;
			mes "[ルーンの引導者　ユングベルグ]";
			mes "我々は虚飾に満ち、本質に至らない";
			mes "王国の騎士団ではなく、真の剣と";
			mes "武の道を歩む者たちの集まりだ。";
			next;
			mes "[ルーンの引導者　ユングベルグ]";
			mes "肉体の強さだけではなく";
			mes "真の力を正しい剣の道へと導く……。";
			mes "それが我ら、ルーンナイト。";
			next;
			mes "[ルーンの引導者　ユングベルグ]";
			mes "半世紀もの間、グラストヘイムの底で";
			mes "隠棲していたが、ついに我々の志を";
			mes "この世に知らせる時が来たのだ。";
			next;
			mes "[ルーンの引導者　ユングベルグ]";
			mes "我々と共に真の剣の道を歩む者を";
			mes "見つけるため、各地に引導者を";
			mes "派遣している。";
			next;
			mes "[ルーンの引導者　ユングベルグ]";
			mes "君も剣の騎士として、我々と同じ志を";
			mes "持っているならば、引導者の推薦を得て";
			mes "改めてここに来てくれ。";
			close;
		case 3:
			mes "[ルーンの引導者　ユングベルグ]";
			mes "早くこの場から去った方がいい。";
			close;
		}
	case 1:
		mes "[ルーンの引導者　ユングベルグ]";
		mes "君はこのグラストヘイムの";
		mes "呪われた亡霊なのか？";
		mes "あるいは何も知らずに迷い込んだ";
		mes "冒険者なのか？";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "君息をする人間であるなら";
		mes "オレの話をよく聞いてくれ……。";
		mes "オレなら、こんな所をうろうろして";
		mes "命を危険にさらすような真似はしない。";
		next;
		if(select("ルーンナイトになる為に来ました","会話をやめる") == 2) {
			mes "[ルーンの引導者　ユングベルグ]";
			mes "早くこの場から去った方がいい。";
			close;
		}
		emotion 1;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "君がマヌエルの推薦を受けた";
		mes "ルーンナイトの候補生だと言うのか？";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "名は" + strcharinfo(0) + "……というのか。";
		mes "確かに、我々の同志となれる素質を";
		mes "有する騎士だと推薦が来ている。";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "……よろしい。";
		mes "我々の血盟になる資格については";
		mes "改めて聞く必要はないだろう。";
		mes "これより君に、行くべき道を示す。";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "まずはグラストヘイムに存在する";
		mes "^FF0000ルーンナイト集結地^000000へ";
		mes "向かうのだ。";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "^0000FFグラストヘイム騎士団の2階には";
		mes "我々の集結地に繋がる場所がある。";
		mes "そこを見つけることから始めよう。^000000";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "その場所には、君を集結地に案内する";
		mes "人物が待機しているはずだ。";
		mes "さあ、行くがいい。";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "無論、グラストヘイムの亡霊達が";
		mes "襲い掛かってくるだろう。";
		mes "だが、その危険を突破する程度の力は";
		mes "持ち合わせていると信じているぞ。";
		set CHANGE_RK,2;
		chgquest 3200,3201;
		close;
	case 2:
	case 3:
		mes "[ルーンの引導者　ユングベルグ]";
		mes "まずはグラストヘイムに存在する";
		mes "^FF0000ルーンナイト集結地^000000へ";
		mes "向かうのだ。";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "^0000FFグラストヘイム騎士団の2階には";
		mes "我々の集結地に繋がる場所がある。";
		mes "そこを見つけることから始めよう。^000000";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "その場所には、君を集結地に案内する";
		mes "人物が待機しているはずだ。";
		mes "さあ、行くがいい。";
		next;
		mes "[ルーンの引導者　ユングベルグ]";
		mes "無論、グラストヘイムの亡霊達が";
		mes "襲い掛かってくるだろう。";
		mes "だが、その危険を突破する程度の力は";
		mes "持ち合わせていると信じているぞ。";
		close;
	default:
		mes "[ルーンの引導者　ユングベルグ]";
		mes "まだ試験中のようだな。";
		mes "見事、試練を突破することを祈る。";
		next;
		if(select("集結地に行きたいです","会話をやめる") == 2) {
			mes "[ルーンの引導者　ユングベルグ]";
			mes "どうした？";
			mes "試験を続けないのか？";
			close;
		}
		mes "[ルーンの引導者　ユングベルグ]";
		mes "よかろう、今すぐ送るとしよう。";
		mes "では、行くがいい。";
		close2;
		warp "job3_rune01.gat",80,65;
		end;
	}
}

gl_knt02.gat,150,55,3	script	ルーンナイトギルド要員	83,{
	if(Job == Job_RuneKnight || CHANGE_RK > 3) {
		mes "[ルーンナイトギルド要員]";
		mes "こんにちは。";
		mes strcharinfo(0) + "様。";
		mes "ルーンナイト集結地に行きますか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[ルーンナイトギルド要員]";
			mes "そうですか。では、ご武運を！";
			mes "私は任務に戻ります。";
			close;
		}
		mes "[ルーンナイトギルド要員]";
		mes "了解しました。ご案内いたします。";
		close2;
		warp "job3_rune01.gat",80,65;
		end;
	}
	switch(CHANGE_RK) {
	case 0:
		mes "[ルーンナイトギルド要員]";
		mes "失礼ですが、ここは立ち入り禁止です。";
		mes "周囲を歩き回るのは問題ありませんが";
		mes "邪魔はしないでください。";
		close;
	case 1:
		mes "[ルーンナイトギルド要員]";
		mes "失礼ですが、ここは立ち入り禁止です。";
		mes "周囲を歩き回るのは問題ありませんが";
		mes "邪魔はしないでください。";
		next;
		mes "[ルーンナイトギルド要員]";
		mes "ふむ。でもあなたはこれから我々と";
		mes "縁があるかも知れませんね。";
		mes "剣の道を歩む者よ。";
		next;
		mes "[ルーンナイトギルド要員]";
		mes "遠からず、また会えるでしょう。";
		mes "その時になれば……。";
		close;
	case 2:
	case 3:
		mes "[ルーンナイトギルド要員]";
		mes "ここをよく見つけましたね。";
		mes "ユングベルグ様から";
		mes "お話は伺っております。";
		mes "あなたを集結地へ案内いたします。";
		next;
		mes "[ルーンナイトギルド要員]";
		mes "集結地ではまず、マスターである";
		mes "^0000FFティグリース様^000000にお会いください。";
		mes "新しい同志が現れることを";
		mes "いつも待っておられますので。";
		next;
		mes "[ルーンナイトギルド要員]";
		mes "では、私について来てください。";
		if(CHANGE_RK == 2) {
			set CHANGE_RK,3;
			chgquest 3201,104452;
		}
		close2;
		warp "job3_rune01.gat",80,65;
		end;
	}
}

//============================================================
// マスター
//------------------------------------------------------------
job3_rune01.gat,80,60,3	script	ティグリース	470,{
	if(Job == Job_RuneKnight) {
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "よく来てくれた、";
		mes strcharinfo(0) + "。";
		mes "特に用事は無さそうだが";
		mes "遠慮せず、ゆっくりしていくといい。";
		close2;
		cutin "3rd_rune_knight",255;
		end;
	}
	switch(CHANGE_RK) {
	case 0:
	case 1:
	case 2:
		// 未調査
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "どうやってここに来たのか知らないが、";
		mes "君はここにいるべき者ではないようだね。";
		next;
		mes "[マスター　ティグリース]";
		mes "元の場所に戻るといい。";
		mes "さあ、送ってあげよう。";
		close2;
		cutin "3rd_rune_knight",255;
		warp "gl_knt02.gat",150,60;
		end;
	case 3:
		cutin "3rd_rune_knight",2;
		mes "‐美しい鎧をまとい";
		mes "　炎を宿したかのような瞳を持つ";
		mes "　雄々しい姿の男が立っている‐";
		next;
		mes "‐男は燃えるような視線で";
		mes "　こちらを眺めると";
		mes "　ほどなくして話しかけてきた‐";
		next;
		mes "[マスター　ティグリース]";
		mes "マヌエルが推薦した候補生というのは";
		mes "君のことか？";
		mes "オレはルーンナイトギルドのマスター";
		mes "ティグリースだ。";
		mes "君の名を教えてくれ。";
		next;
		mes "[マスター　ティグリース]";
		mes "……おっと、これは失礼！";
		mes "連絡が来ているのだった。";
		mes strcharinfo(0) + "……。";
		mes "君がここに来たことを歓迎しよう！";
		next;
		mes "[マスター　ティグリース]";
		mes "オレは正直、全員の試験を";
		mes "最初から最後まで見ることはできない。";
		mes "君には是非、上手く試験をパスして";
		mes "我らの同志となって欲しい。";
		next;
		mes "[マスター　ティグリース]";
		mes "どれどれ……基本的な確認は";
		mes "マヌエルとユングベルグが";
		mes "上手くやってくれたようだから";
		mes "直ちにテストに入るとしようか。";
		next;
		mes "[マスター　ティグリース]";
		mes "ルナリア！";
		mes "……始めの試験は君に任せる。";
		next;
		cutin "3rd_rune_knight",255;
		mes "[時空のルーンナイト　ルナリア]";
		mes "……（こくっ）。";
		next;
		mes "‐ルナリアと呼ばれた白い肌の女騎士が";
		mes "　静かに頷きながら、こちらを見た‐";
		next;
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "さあ、試験が始まるぞ。";
		mes "^0000FFまずはそちらの可憐なお嬢さんから";
		mes "試験の内容を聞くように。^000000";
		next;
		mes "[マスター　ティグリース]";
		mes "さて、オレはここで君からの";
		mes "結果報告を待つとしよう。";
		mes "頑張ってくれよ。";
		set CHANGE_RK,4;
		chgquest 104452,3202;
		close2;
		cutin "3rd_rune_knight",255;
		end;
	case 4:
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "さあ、試験が始まるぞ。";
		mes "^0000FFまずはそちらの可憐なお嬢さんから";
		mes "試験の内容を聞くように。^000000";
		next;
		mes "[マスター　ティグリース]";
		mes "さて、オレはここで君からの";
		mes "結果報告を待つとしよう。";
		mes "頑張ってくれよ。";
		close2;
		cutin "3rd_rune_knight",255;
		end;
	case 5:
	case 6:
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "君は今、テスト中じゃないのか？";
		mes "ルナリア、どういうことだ？";
		mes "テストは終わったのかい？";
		next;
		cutin "3rd_rune_knight",255;
		mes "[時空のルーンナイト　ルナリア]";
		mes "……（ギロリ）。";
		next;
		mes "‐彼女は、何も言わずに首を横に振り";
		mes "　こちらを睨みつけた。";
		mes "　鋭い視線が容赦なく突き刺さる‐";
		next;
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "了解だ、ルナリア！";
		mes "……オレの話をよく聞いてくれよ。";
		mes "ルナリアは、ちょっと無口で無愛想だが";
		mes "彼女を無視することは許されない。";
		next;
		emotion 56;
		mes "[マスター　ティグリース]";
		mes "このオレでさえ……";
		mes "いや、我々の中では誰ひとりとして";
		mes "怒った彼女に敵う者はいないんだ。";
		mes "ははは！";
		next;
		cutin "3rd_rune_knight",255;
		mes "[時空のルーンナイト　ルナリア]";
		mes "……（ギロリ）。";
		next;
		cutin "3rd_rune_knight",2;
		emotion 19;
		mes "[マスター　ティグリース]";
		mes "おっと、そんな目で見ないでくれ。";
		mes "分かったかい、候補生さん？";
		mes "ルナリアに従って試験を受けなさい。";
		mes "それが君とオレのためになるようだ。";
		close2;
		cutin "3rd_rune_knight",255;
		end;
	case 7:
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "ルナリアの試験は合格したようだね！";
		mes "これでもう基本は見なくていいわけだ。";
		mes "さて、ルナリアの試験に";
		mes "合格したということは……。";
		next;
		mes "[マスター　ティグリース]";
		mes "レノア！　久々に君の出番が";
		mes "回ってきたということだよ。";
		next;
		cutin "3rd_rune_knight",255;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "どうやら、そのようね。";
		mes "だけど、私の試験はルナリアとは";
		mes "質が違うわよ？　脳みそまで";
		mes "筋肉じゃないことを期待するわ。";
		next;
		cutin "3rd_rune_knight",2;
		emotion 56;
		mes "[マスター　ティグリース]";
		mes "ははは！　……聞いたよな？";
		mes "次も一筋縄ではいかないだろうが";
		mes "頑張ってくれ！";
		next;
		mes "[マスター　ティグリース]";
		mes "^0000FFさあ、隣の書庫に控えている";
		mes "炎のようなお嬢様の試験を受けるんだ。^000000";
		set CHANGE_RK,8;
		chgquest 3204,3205;
		close2;
		cutin "3rd_rune_knight",255;
		end;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "レノア！　久々に君の出番が";
		mes "回ってきたということだよ。";
		next;
		cutin "3rd_rune_knight",255;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "どうやら、そのようね。";
		mes "だけど、私の試験はルナリアとは";
		mes "質が違うわよ？　脳みそまで";
		mes "筋肉じゃないことを期待するわ。";
		next;
		cutin "3rd_rune_knight",2;
		emotion 56;
		mes "[マスター　ティグリース]";
		mes "ははは！　……聞いたよな？";
		mes "次も一筋縄ではいかないだろうが";
		mes "頑張ってくれ！";
		next;
		mes "[マスター　ティグリース]";
		mes "^0000FFさあ、隣の書庫に控えている";
		mes "炎のようなお嬢様の試験を受けるんだ。^000000";
		close2;
		cutin "3rd_rune_knight",255;
		end;
	case 14:
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "話は聞いた。数人しかパスできなかった";
		mes "レノアのテストに受かったそうだね。";
		next;
		mes "[マスター　ティグリース]";
		mes "聞いたかもしれないが";
		mes "レノアの試験中に挫折した候補生は";
		mes "数え切れないほどいる。";
		next;
		mes "[マスター　ティグリース]";
		mes "非常に難しい試験だったのだが";
		mes "よく合格してくれた。";
		next;
		mes "[マスター　ティグリース]";
		mes "では、最後の試験に挑んでもらおう。";
		mes "この試験をパスすれば、君も我々と同じ";
		mes "正式なルーンナイトとしての道を";
		mes "歩むことになる。";
		next;
		mes "[マスター　ティグリース]";
		mes "^0000FF最終試験は、隣の武器庫にいる";
		mes "漆黒のルーンナイト";
		mes "ベルフィーノから受けるんだ。^000000";
		next;
		mes "[マスター　ティグリース]";
		mes "冗談ではなく、我々は本当に";
		mes "君がルーンナイトとして";
		mes "飛び立つ瞬間を心待ちにしている。";
		mes "……最後まで頑張ってくれ。";
		set CHANGE_RK,15;
		chgquest 3215,3216;
		close2;
		cutin "3rd_rune_knight",255;
		end;
	case 15:
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "^0000FF最終試験は、隣の武器庫にいる";
		mes "漆黒のルーンナイト";
		mes "ベルフィーノから受けるんだ。^000000";
		next;
		mes "[マスター　ティグリース]";
		mes "冗談ではなく、我々は本当に";
		mes "君がルーンナイトとして";
		mes "飛び立つ瞬間を心待ちにしている。";
		mes "……最後まで頑張ってくれ。";
		close2;
		cutin "3rd_rune_knight",255;
		end;
	case 16:
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "おめでとう！　君は全ての試験に";
		mes "合格し、ルーンナイトとしての道を";
		mes "歩むことになった。";
		next;
		mes "[マスター　ティグリース]";
		mes "オレは本当に嬉しいんだ。";
		mes "ふふ……後輩が増える時の喜びを";
		mes "君はまだ知らないだろう。";
		next;
		mes "[マスター　ティグリース]";
		mes "これから君は、今までの殻を脱ぎ捨て";
		mes "誇らしき我らルーンナイトの一員に";
		mes "生まれ変わるんだ。";
		next;
		mes "[マスター　ティグリース]";
		mes "さて、転職前の準備の確認だ。";
		mes "今、君が装備しているものや所持品を";
		mes "転職の喜びのためにいったん";
		mes "所持しているものを全て";
		mes "預けてきてくれ。";
		next;
		mes "[マスター　ティグリース]";
		mes "すでに知っていると思うが";
		mes "そこの倉庫サービスのお嬢さんに頼めば";
		mes "何も問題は無いはずだ。";
		next;
		mes "[マスター　ティグリース]";
		mes "また、ペコペコに騎乗しているなら";
		mes "ペコペコも預けて来るように。";
		next;
		mes "[マスター　ティグリース]";
		mes "もう一つ。スキルポイントが";
		mes "余っていれば、全部消費するように。";
		mes "余っていると転職は出来ないぞ。";
		next;
		mes "[マスター　ティグリース]";
		mes "オレからの話は以上だ！";
		mes "さあ、ルーンナイトとしての";
		mes "新しい旅立ちの時だ！";
		next;
		if(select("準備はできています","考える準備をください") == 2) {
			mes "[マスター　ティグリース]";
			mes "そうか……。";
			mes "心の準備ができたら";
			mes "また話しかけてくれ。";
			close2;
			cutin "3rd_rune_knight",255;
			end;
		}
		mes "[マスター　ティグリース]";
		mes "そうだ、君に相応しい祝いの品を";
		mes "用意している。";
		next;
		mes "[マスター　ティグリース]";
		mes "次の3つの中から好きなものを選んでくれ。";
		mes "ルーンナイトとなった時に渡すとしよう。";
		while(1) {
			mes " ";
			mes "[<ITEM>エナジールーンガード[1]<INFO>2140</INFO></ITEM>]";
			mes "[<ITEM>魔力石の指輪[1]<INFO>2794</INFO></ITEM>]";
			mes "[<ITEM>ルーンプレート[1]<INFO>15002</INFO></ITEM>]";
			next;
			switch(select("エナジールーンガード[1]","魔力石の指輪[1]","ルーンプレート[1]","考える時間をください")) {
			case 1:
				mes "[マスター　ティグリース]";
				mes "<ITEM>エナジールーンガード[1]<INFO>2140</INFO></ITEM>だな。";
				mes "本当にこれでよいのか？";
				set '@item,2140;
				break;
			case 2:
				mes "[マスター　ティグリース]";
				mes "<ITEM>魔力石の指輪[1]<INFO>2794</INFO></ITEM>だな。";
				mes "本当にこちらでよいのか？";
				set '@item,2794;
				break;
			case 3:
				mes "[マスター　ティグリース]";
				mes "<ITEM>ルーンプレート[1]<INFO>15002</INFO></ITEM>だな。";
				mes "本当にこちらでよいのか？";
				set '@item,15002;
				break;
			case 4:
				mes "[マスター　ティグリース]";
				mes "わかった。";
				mes "ゆっくり考えてきてくれ。";
				close2;
				cutin "3rd_rune_knight",255;
				end;
			}
			next;
			if(select("はい","いいえ") == 2) {
				mes "[マスター　ティグリース]";
				mes "それでは再度、欲しい装備を";
				mes "選んでくれ。";
				continue;
			}
			mes "[マスター　ティグリース]";
			mes "よろしい。では、";
			mes "我々の師である偉大なるソードマスター";
			mes "ベルゼブよ……。";
			mes "そして、大賢者セルフィオネよ……。";
			next;
			mes "[マスター　ティグリース]";
			mes "ここに一人の騎士が、我々と共に";
			mes "ルーンナイトの道を歩むことを";
			mes "祝福したまえ……。";
			next;
			if(Weight || checkitemblank() < 3 || checkcart() || checkfalcon() || checkriding() || checkdragon() || checkgear() || checkwolf() || sc_ison(SC_ALL_RIDING) || getpetinfo(0)) {
				mes "[マスター　ティグリース]";
				mes "ん……？　君はオレの話を";
				mes "理解できなかったようだな。";
				next;
				mes "[マスター　ティグリース]";
				mes "今、";
				mes "君が引き連れているものは全て解放して";
				mes "重量がある物は一旦全て預けてきてくれ。";
				mes "ペコペコに騎乗しているなら";
				mes "解き放つ必要があるということだ。";
				next;
				mes "[マスター　ティグリース]";
				mes "ここにいる";
				mes "倉庫サービスのお嬢さんに頼めば";
				mes "何も問題は無いはずだ。";
				next;
				mes "[マスター　ティグリース]";
				mes "理解できたら、準備を終えてから";
				mes "声を掛けてくれ！";
				next;
				cutin "3rd_rune_knight",255;
				mes "[インフォメーション]";
				mes "お持ちのアイテムは";
				mes "倉庫に預けるなどして";
				mes "所持アイテムの重量を";
				mes "^FF00000^000000にして下さい。";
				mes "空き種類数にも";
				mes "ある程度の余裕を持たせてください。";
				next;
				mes "[インフォメーション]";
				mes "カート、ファルコン、";
				mes "ペコペコ、ドラゴン、";
				mes "グリフォン、ウォーグ、";
				mes "魔導ギア、騎乗生物、";
				mes "ペットは";
				mes "外してきて下さい。";
				close;
			}
			if(SkillPoint) {
				mes "[マスター　ティグリース]";
				mes "ん……？";
				mes "何か準備が足りないようだが？";
				next;
				cutin "3rd_rune_knight",255;
				mes "^FF0000‐スキルポイントが余っている場合は";
				mes "　全て消費してください‐^000000";
				close;
			}
			if(Job != Job_Knight || Upper == UPPER_NORMAL || (Upper == UPPER_HIGH && BaseLevel < 90) || (Upper == UPPER_BABY && (BaseLevel < 99 || JobLevel < 50))) {	// 念のため職チェック
				mes "[マスター　ティグリース]";
				mes "ん……？";
				mes "何か準備が足りないようだが？";
				close2;
				cutin "3rd_rune_knight",255;
				end;
			}
			set CHANGE_RK,0;
			chgquest 3219,201180;
			compquest 201180;
			resetstatus;
			resetskill;
			setoption 0;
			jobchange Job_RuneKnight;
			getitem 5746,1;		// ルーンサークレット
			getitem 2795,1;		// 熟していないリンゴの指輪
			getitem '@item,1;
			setquest 129700;	// ステータス＆スキル一括リセット権
			mes "[マスター　ティグリース]";
			mes "おめでとう。君がルーンナイトとなり";
			mes "我々の同志になったこの瞬間は";
			mes "永遠に記憶されるだろう。";
			next;
			mes "[マスター　ティグリース]";
			mes "新しい道を歩む者の為に";
			mes "王宮から特別に贈り物も届いている。";
			mes "受け取ってくれ。";
			next;
			cutin "3rd_rune_knight",255;
			mes "[インフォメーション]";
			mes "転職試験のクリア報酬";
			mes "ステータス・スキル一括リセット権が";
			mes "付与されました。";
			mes "クエストウィンドウで利用方法を";
			mes "確認できます。";
			close;
		}
	}
}

//============================================================
// 第1試験
//------------------------------------------------------------
job3_rune01.gat,90,50,3	script	ルナリア	469,{
	if(Job == Job_RuneKnight) {
		mes "‐彼女は静かに顔を上げ";
		mes "　こちらを見て軽く頷いた‐";
		next;
		emotion 9;
		mes "‐そして、すぐ視線を逸らすと";
		mes "　いつものように何かを考え始めた‐";
		close;
	}
	switch(CHANGE_RK) {
	case 0:
	case 1:
	case 2:
	case 3:
		emotion 9;
		mes "‐白い肌の女性騎士は周りを気にして";
		mes "　いる様子はない。";
		mes "　こちらの存在についても";
		mes "　興味が無さそうだ‐";
		close;
	case 4:
		mes "‐何も言わずこちらの顔を見ていた";
		mes "　女騎士は、ささやくように";
		mes "　小さい声で話し始めた‐";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "5分……。";
		mes "^0000FF5分間で……敵を……";
		mes "全部倒すことができれば成功……。^000000";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "……この試験は……あたしと";
		mes "ティグリースマスター……";
		mes "……それにレノアとベルフィーノも";
		mes "……一緒に参観するから。";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "^0000FF必要なら……あたし達の誰かに……";
		mes "助けを求めても……いい……。";
		mes "でも、いつも助けるわけじゃない……。^000000";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "試験だから……助けないで見守ることも";
		mes "……ある。";
		mes "助けを求めるのは……自由。";
		mes "自分の力だけで挑戦しても……いい。";
		next;
		break;
	case 5:
		if(checkquest(3203)) {
			chgquest 3203,104455;
		}
		mes "[時空のルーンナイト　ルナリア]";
		mes "失敗……なの……？";
		mes "でも……回数制限はない……。";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "また……受けたいなら……";
		mes "試験場に送ってあげる……。";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "5分……。";
		mes "^0000FF5分間で……敵を……";
		mes "全部倒すことができれば成功……。^000000";
		next;
		break;
	case 6:
		mes "[時空のルーンナイト　ルナリア]";
		mes "試験は……合格。";
		next;
		mes "‐彼女は小さく微笑みながら";
		mes "　こちらを見た‐";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "基本的な騎士としての身体能力は……";
		mes "……合格……そう判断する。";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "……あたしの試験は……これで終わり。";
		mes "^0000FFティグリースマスターに……";
		mes "報告して。^000000";
		set CHANGE_RK,7;
		chgquest 104460,3204;
		close;
	default:
		mes "[時空のルーンナイト　ルナリア]";
		mes "……あたしの試験は……これで終わり。";
		mes "^0000FFティグリースマスターに……";
		mes "報告して。^000000";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "……他のルーンナイト達の試験が";
		mes "……待ってるから。";
		close;
	}
	mes "[時空のルーンナイト　ルナリア]";
	mes "……試験場に移動する準備ができたら";
	mes "……あたしに話しかけて。";
	next;
	if(select("試験場に移動する","準備する時間をください") == 2) {
		mes "[時空のルーンナイト　ルナリア]";
		mes "……わかった。";
		mes "……早く準備して。";
		close;
	}
	mes "‐ルナリアは軽く頷きながら手を振り";
	mes "　何かを唱えた‐";
	next;
	if(checkquest(3220)) {
		if(checkquest(3220)&2 == 0) {
			mes "[時空のルーンナイト　ルナリア]";
			mes "……ちょっと待って。";
			mes "試験場に一度入ったら……";
			mes "……少しの間は再入場できない。";
			mes "……テストを受けるほかの候補生の為。";
			mes "……少し後にまた来て……。";
			close;
		}
		delquest 3220;
	}
	if(getnpctimer(1,"RKTestStart") || getnpctimer(1,"RKTestBattle1") || getnpctimer(1,"RKTestBattle2")) {
		emotion 9;
		mes "‐しかし、少し顔をしかめると";
		mes "　こちらを見て、口を開く‐";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "……あなた以外の候補生が今";
		mes "……試験場を利用しているみたい。";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "……少しだけ待って。";
		mes "……ルーンナイトの試験は1人ずつ。";
		mes "……それがあたし達の約束だから。";
		next;
		mes "[時空のルーンナイト　ルナリア]";
		mes "……しばらくしたら終わると思う。";
		mes "……もう少し時間をおいて、また来て。";
		close;
	}
	if(CHANGE_RK == 4) {
		set CHANGE_RK,5;
		chgquest 3202,3203;
	} else {
		chgquest 104455,3203;
	}
	setquest 3220;
	warp "job3_rune02.gat",38,40;
	end;
}

job3_rune02.gat,38,40,0	script	RKTestStart	139,15,15,{
OnTouch:
	if(CHANGE_RK != 5) {
		warp "job3_rune01.gat",90,47;
		end;
	}
	areasetcell "job3_rune02.gat",37,39,39,41,1;
	initnpctimer;
	hideonnpc;
	end;
OnTimer5000:
	announce "これよりルーンナイト候補生の第1試験を行います",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer8000:
	announce "試験内容は「5分以内に全てのモンスターを倒す」ことです",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer11000:
	announce "生き残れなかった場合や、時間を越えた場合は失敗となります",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer14000:
	announce "それでは試験を開始します",0x9,0xFFFF00,0x190,12,0,0;
	initnpctimer "RKTestBattle1";
	initnpctimer "RKTestHelper";
	areasetcell "job3_rune02.gat",37,39,39,41,0;
	stopnpctimer;
	end;
}

job3_rune02.gat,0,0,0	script	RKTestBattle1	-1,{
OnTimer5000:
	areamonster "job3_rune02.gat",0,0,0,0,"レイドリック",1467,1,"RKTestBattle1::OnKilled";
	areamonster "job3_rune02.gat",0,0,0,0,"レイドリックアーチャー",1453,2,"RKTestBattle1::OnKilled";
	end;
OnTimer50000:
OnTimer100000:
OnTimer150000:
	switch(rand(6)) {
	case 0:
		areamonster "job3_rune02.gat",0,0,0,0,"レイドリック",1467,1,"RKTestBattle1::OnKilled";
		areamonster "job3_rune02.gat",0,0,0,0,"レイドリックアーチャー",1453,2,"RKTestBattle1::OnKilled";
		break;
	case 1:
	case 2:
		areamonster "job3_rune02.gat",0,0,0,0,"ライドワード",1478,4,"RKTestBattle1::OnKilled";
		break;
	case 3:
	case 4:
		areamonster "job3_rune02.gat",0,0,0,0,"フェンダーク",1484,1,"RKTestBattle1::OnKilled";
		areamonster "job3_rune02.gat",0,0,0,0,"リビオ",1483,1,"RKTestBattle1::OnKilled";
		break;
	case 5:
		areamonster "job3_rune02.gat",0,0,0,0,"レイス",1475,4,"RKTestBattle1::OnKilled";
		break;
	}
	end;
OnTimer200000:
	killmonster "job3_rune02.gat","RKTestBattle1::OnKilled";
	donpcevent "RKTestBattle2::OnStart";
	end;
OnTimer60000:
	announce "‐1分経過しました‐",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer120000:
	announce "‐2分経過しました‐",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer180000:
	announce "‐3分経過しました‐",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer240000:
	announce "‐4分経過しました‐",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer300000:
	announce "‐制限時間を越えました。試験は失敗です‐",0x9,0xFFFF00,0x190,12,0,0;
	end;
OnTimer303000:
	mapwarp "job3_rune02.gat","job3_rune01.gat",90,47;
	killmonster "job3_rune02.gat","RKTestBattle1::OnKilled";
	killmonster "job3_rune02.gat","RKTestBattle2::OnKilled";
	stopnpctimer "RKTestHelper";
	stopnpctimer;
	hideonnpc "ティグリース#RKTest";
	hideonnpc "ルナリア#RKTest";
	hideonnpc "レノア#RKTest";
	hideonnpc "ベルフィーノ#RKTest";
	hideoffnpc "RKTestStart";
	end;
OnKilled:
	end;
}

job3_rune02.gat,0,0,0	script	RKTestBattle2	-1,{
OnStart:
	switch(rand(6)) {
	case 0:
		areamonster "job3_rune02.gat",0,0,0,0,"レイドリック",1467,1,"RKTestBattle2::OnKilled";
		areamonster "job3_rune02.gat",0,0,0,0,"レイドリックアーチャー",1453,2,"RKTestBattle2::OnKilled";
		break;
	case 1:
	case 2:
		areamonster "job3_rune02.gat",0,0,0,0,"ライドワード",1478,4,"RKTestBattle2::OnKilled";
		break;
	case 3:
	case 4:
		areamonster "job3_rune02.gat",0,0,0,0,"フェンダーク",1484,1,"RKTestBattle2::OnKilled";
		areamonster "job3_rune02.gat",0,0,0,0,"リビオ",1483,1,"RKTestBattle2::OnKilled";
		break;
	case 5:
		areamonster "job3_rune02.gat",0,0,0,0,"レイス",1475,4,"RKTestBattle2::OnKilled";
		break;
	}
	end;
OnKilled:
	if(getmapmobs("job3_rune02.gat","RKTestBattle2::OnKilled") < 1) {
		set CHANGE_RK,6;
		delquest 3220;
		chgquest 3203,104460;
		announce "試験を見事クリアしました！",0x9,0xFFFF00,0x190,12,0,0;
		initnpctimer;
	}
	end;
OnTimer3000:
	mapwarp "job3_rune02.gat","job3_rune01.gat",90,47;
	killmonster "job3_rune02.gat","RKTestBattle1::OnKilled";
	killmonster "job3_rune02.gat","RKTestBattle2::OnKilled";
	stopnpctimer "RKTestHelper";
	stopnpctimer "RKTestBattle1";
	stopnpctimer;
	hideonnpc "ティグリース#RKTest";
	hideonnpc "ルナリア#RKTest";
	hideonnpc "レノア#RKTest";
	hideonnpc "ベルフィーノ#RKTest";
	hideoffnpc "RKTestStart";
	end;
}

job3_rune02.gat,0,0,0	script	RKTestHelper	-1,{
OnTimer30000:
	announce "ティグリース : ルーンナイトの候補生よ。我らの力を借りたければ、誰か一人に話しかけてくれ！",0x9,0xFFFF00,0x190,12,0,0;
	hideoffnpc "ティグリース#RKTest";
	hideoffnpc "ルナリア#RKTest";
	hideoffnpc "レノア#RKTest";
	hideoffnpc "ベルフィーノ#RKTest";
	end;
OnTimer60000:
	announce "ティグリース : 我らの手は必要ないのだな……諸君、しばらく様子を見るとしよう。",0x9,0xFFFF00,0x190,12,0,0;
	hideonnpc "ティグリース#RKTest";
	hideonnpc "ルナリア#RKTest";
	hideonnpc "レノア#RKTest";
	hideonnpc "ベルフィーノ#RKTest";
	initnpctimer;
	end;
}

job3_rune02.gat,34,46,5	script	ティグリース#RKTest	470,{
	if(getnpctimer(1,"ティグリース#RKTest") == 0 && getnpctimer(1,"ルナリア#RKTest") == 0 && getnpctimer(1,"レノア#RKTest") == 0 && getnpctimer(1,"ベルフィーノ#RKTest") == 0) {
		if(strnpcinfo(1) == "ティグリース") {
			switch(rand(6)) {
			case 0:
				announce "ティグリース : 君に、ベルゼブの祝福を……！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 34,0;
				sc_start SC_BLESSING,240000,10;
				break;
			case 1:
			case 2:
				announce "ティグリース : 生命の炎よ……再び燃え上がれ！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 28,1224;
				heal 1224,0;
				break;
			case 3:
				announce "ティグリース : 醜悪な亡霊たちよ……墓に帰るがいい！",0x9,0xFFFF00,0x190,12,0,0;
				misceffect 92,"";
				killmonster "job3_rune02.gat","RKTestBattle1::OnKilled";
				break;
			case 4:
			case 5:
				announce "ティグリース : 候補生よ、修練が足りないぞ！",0x9,0xFFFF00,0x190,12,0,0;
				break;
			}
		}
		else if(strnpcinfo(1) == "ルナリア") {
			switch(rand(6)) {
			case 0:
				announce "ルナリア : もっと速く……もっと強く……敵の息の根を止めるの……！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 29,0;
				sc_start SC_INCREASEAGI,240000,10;
				break;
			case 1:
			case 2:
				announce "ルナリア : まだ終わっていない……もう少しあなたに力を……！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 28,1224;
				heal 1224,0;
				break;
			case 3:
				announce "ルナリア : 全ては原点に……還れ……！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 35,0;
				sc_end SC_SILENCE;
				sc_end SC_CONFUSION;
				sc_end SC_BLIND;
				break;
			case 4:
			case 5:
				announce "レノア : これくらいの試練は、大したことないわよね？",0x9,0xFFFF00,0x190,12,0,0;
				break;
			}
		}
		else if(strnpcinfo(1) == "レノア") {
			switch(rand(6)) {
			case 0:
				announce "レノア : 疾風のルーンよ！　あなたに力を！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 29,0;
				sc_start SC_INCREASEAGI,240000,10;
				break;
			case 1:
			case 2:
				announce "レノア : 生命のルーンよ！　生命の力を！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 28,1224;
				heal 1224,0;
				break;
			case 3:
				announce "レノア : 私は誰よりも速い……他とは違うわよ！",0x9,0xFFFF00,0x190,12,0,0;
				misceffect 148,"";
				killmonster "job3_rune02.gat","RKTestBattle1::OnKilled";
				break;
			case 4:
			case 5:
				announce "レノア : これくらいの試練は、大したことないわよね？",0x9,0xFFFF00,0x190,12,0,0;
				break;
			}
		}
		else if(strnpcinfo(1) == "ベルフィーノ") {
			switch(rand(6)) {
			case 0:
				announce "ベルフィーノ : お前は、こんな所で倒れる者ではない！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 28,1224;
				heal 1224,0;
				break;
			case 1:
			case 2:
				announce "ベルフィーノ : 行け！　邪魔するものは全て切り裂け！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 29,0;
				sc_start SC_INCREASEAGI,240000,10;
				break;
			case 3:
				announce "ベルフィーノ : お前は一人ではない。我らが見守っている！",0x9,0xFFFF00,0x190,12,0,0;
				npcskillsupport 34,0;
				sc_start SC_BLESSING,240000,10;
				break;
			case 4:
			case 5:
				announce "ベルフィーノ : 戦え！　そして、勝て！　この程度の試練に躊躇するな！",0x9,0xFFFF00,0x190,12,0,0;
				break;
			}
		}
		stopnpctimer "RKTestHelper";
		initnpctimer;
	}
	end;
OnTimer5000:
	announce "ティグリース : 諸君、これからしばらく様子を見るとしよう。",0x9,0xFFFF00,0x190,12,0,0;
	hideonnpc "ティグリース#RKTest";
	hideonnpc "ルナリア#RKTest";
	hideonnpc "レノア#RKTest";
	hideonnpc "ベルフィーノ#RKTest";
	stopnpctimer;
	initnpctimer "RKTestHelper";
OnInit:
	hideonnpc;
	end;
}

job3_rune02.gat,43,46,3	duplicate(ティグリース#RKTest)	ルナリア#RKTest	469
job3_rune02.gat,43,34,1	duplicate(ティグリース#RKTest)	レノア#RKTest	469
job3_rune02.gat,34,34,7	duplicate(ティグリース#RKTest)	ベルフィーノ#RKTest	468

//============================================================
// 第2試験
//------------------------------------------------------------
job3_rune01.gat,55,50,3	script	レノア#RK	469,{
	if(Job == Job_RuneKnight) {
		mes "[紅蓮のルーンナイト　レノア]";
		mes "我らの同志になったのね。おめでとう！";
		mes "ルーンナイト" + strcharinfo(0) + "。";
		mes "改めてよろしくね。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "これから……我らが行くべき道が";
		mes "はっきりと現れてくるはずよ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "それまでに、我らと共にする同志を";
		mes "一人でも多く、探してみるわ。";
		mes "あなたみたいな人をね……。";
		mes "ふふ……。";
		close;
	}
	switch(CHANGE_RK) {
	default:
		mes "[紅蓮のルーンナイト　レノア]";
		mes "ルーンナイト候補生か……。";
		mes "あなたで何人目だったかしら？";
		next;
		emotion 54;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "私の試練を受けられるほどの素質ある";
		mes "人間が少なくてね……。";
		mes "御覧のとおり、休ませてもらってるわ。";
		next;
		emotion 29;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "あなたも試練を受けているなら";
		mes "私の試験まで頑張って残ってよ。";
		mes "ルナリアのテストは、ハンパないから。";
		mes "ふふ……。";
		close;
	case 8:
		emotion 29;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "もう……遅い!!　やっと、私の出番ね？";
		mes "ふふ……嬉しいじゃない。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "ルナリアのテストを受けた候補生は";
		mes "何人だっけ……100人超えた後は";
		mes "数えるのも飽きちゃったわ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "私はレノア。ルーンナイトの候補生達に";
		mes "ルーンと魔法に関する指導と試験を";
		mes "行っているわ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "私無口なルナリアのテストを受けて";
		mes "疲れているかしら？　あの娘はちょっと";
		mes "変わった子だけど。";
		mes "さあ、こちらも始めるわよ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "まずは、^0000FFこの書庫内にある本を読む";
		mes "ことから始めましょう。^000000";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "そうね……^0000FF『ルーンとルーンナイト』^000000、";
		mes "^0000FF『ルーンの原理と種類』^000000、";
		mes "^0000FF『ルーンストーンの制作と使用』^000000、";
		mes "この3冊でいいかしら……。";
		next;
		emotion 29;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "本をじっくり読んだら、";
		mes "ちょうだい。今まで読書とか勉強とは";
		mes "縁がなかったとしたら、ルーンナイトに";
		mes "なるのは難しいかもね。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "だとしても、あなたにゲフェンや";
		mes "ジュノーの魔法使い達と等しい知識を";
		mes "要求してるわけじゃないから";
		mes "頑張ってみなさい。";
		set CHANGE_RK,9;
		chgquest 3205,3206;
		close;
	case 9:
		if(checkquest(104465) == 0 || checkquest(104470) == 0 || checkquest(104475) == 0) {
			mes "[紅蓮のルーンナイト　レノア]";
			mes "まずは、^0000FFこの書庫内にある本を読む";
			mes "ことから始めましょう。^000000";
			next;
			mes "[紅蓮のルーンナイト　レノア]";
			mes "そうね……^0000FF『ルーンとルーンナイト』^000000、";
			mes "^0000FF『ルーンの原理と種類』^000000、";
			mes "^0000FF『ルーンストーンの制作と使用』^000000、";
			mes "この3冊でいいかしら……。";
			next;
			emotion 29;
			mes "[紅蓮のルーンナイト　レノア]";
			mes "本をじっくり読んだら、";
			mes "ちょうだい。今まで読書とか勉強とは";
			mes "縁がなかったとしたら、ルーンナイトに";
			mes "なるのは難しいかもね。";
			next;
			mes "[紅蓮のルーンナイト　レノア]";
			mes "だとしても、あなたにゲフェンや";
			mes "ジュノーの魔法使い達と等しい知識を";
			mes "要求してるわけじゃないから";
			mes "頑張ってみなさい。";
			close;
		}
		mes "[紅蓮のルーンナイト　レノア]";
		mes "指定した本は全部読んだのかしら？";
		mes "慣れない読書だったかもしれないけど";
		mes "ルーンナイトになると決意したんだから";
		mes "この程度のことで弱音を吐かないでね。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "本を読んで分かったと思うけど";
		mes "魔法の力は自然と元素の力を引き出す";
		mes "訓練を積まないと使用するのは";
		mes "不可能に近いわ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "それでウィザードやセージという職業が";
		mes "あるわけなんだけど、魔法は彼らの";
		mes "領域になってしまっているのが現実ね。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "ところで、ルーンナイト達の指導者……";
		mes "ソードマスター　ベルゼブは";
		mes "魔王モロクによって異世界への扉が";
		mes "開かれる前に、すでに異世界の";
		mes "妖精たちに会っていたらしいの。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "妖精の魔法学者達から魔法の精髄を";
		mes "実体化し、納める技術を学んだ後";
		mes "彼らの協力を得てルーンを具現する";
		mes "研究を進めたのよ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "その結果、ルーンを利用して";
		mes "剣と魔法を行使できるようになったのが";
		mes "私たちルーンナイトというわけ。";
		next;
		emotion 9,"";
		mes "[紅蓮のルーンナイト　レノア]";
		mes "……本で読んだ内容を、なぜ繰り返して";
		mes "教えているのか理解できない……";
		mes "という顔をしてるわね。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "それで次は、^0000FFアッシュ・バキュームで";
		mes "ルーンナイトの誕生に";
		mes "協力してもらったラフィネ族の賢者に";
		mes "直接会ってもらうことにするわ。^000000";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "これから、ミッドガルド連合軍駐屯地に";
		mes "派遣されているルーンナイト達に協力し";
		mes "ルーンの研究をしている";
		mes "^0000FF賢者セルフィオネ^000000に会ってくるのよ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "もう長い時間を私達人間と共にしている";
		mes "賢者だから、言葉は通じるわ。";
		mes "その点は心配しないで。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "出発の準備ができたら^0000FFミッドガルド";
		mes "連合軍駐屯地^000000に転送してあげるわ。";
		mes "そこで賢者から教えを請いなさい。";
		set CHANGE_RK,10;
		chgquest 3206,3207;
		delquest 104465;
		delquest 104470;
		delquest 104475;
		close;
	case 10:
	case 11:
		mes "[紅蓮のルーンナイト　レノア]";
		mes "^0000FFミッドガルド連合軍駐屯地^000000に";
		mes "転送してあげるわ。準備はいい？";
		next;
		if(select("準備ができました","まだ、できていません") == 2) {
			mes "[紅蓮のルーンナイト　レノア]";
			mes "準備が終わったら、声を掛けてね。";
			mes "私はいつでも準備OKだから。";
			close;
		}
		mes "[紅蓮のルーンナイト　レノア]";
		mes "いいわ。なら、今すぐ転送してあげる。";
		mes "ああ、そうだ。一つ注意があるわ……。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "あなたがこれから行く場所は異世界よ。";
		mes "駐屯地に派遣されている人たちはみんな";
		mes "^FF0000各国の認証を貰った冒険者達と";
		mes "その管理者のみよ。^000000";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "各国の協定で、私たちルーンナイトの";
		mes "行動の自由は保証されているけど……";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "あなたが異世界で自由に行動する";
		mes "ためには、^FF0000私達と関係なく異世界に";
		mes "行く正式なルートを通さないとダメ。^000000";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "私ができるのは、異世界とこの場所を";
		mes "繋ぐことだけ……。";
		mes "この点だけは気をつけてね。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "それじゃあ、転送するわよ。";
		mes "いってらっしゃい！";
		close2;
		warp "mid_camp.gat",236,246;
		end;
	case 12:
		mes "[紅蓮のルーンナイト　レノア]";
		mes "お帰りなさい。";
		mes "異世界はどうだったかしら？";
		next;
		emotion 29;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "あなたほどの実力なら、異世界で存分に";
		mes "立ち回ってきたかもしれないわね……。";
		mes "ふふっ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "さて次は、ルーンナイトにふさわしい";
		mes "ルーンに関する試験を行うわよ。";
		mes "この試験のために、面倒くさいことを";
		mes "やってもらったのよ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "まだルーンナイトじゃないあなたに";
		mes "ルーンストーンを直接触ることができる";
		mes "機会を用意したわ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		//mes "^0000FF私の背後にある石造の足元に";	// 本鯖仕様
		mes "^0000FF私の背後にある石像の足元に";
		mes "ルーンストーンを生成するための";
		mes "炉があるわ。これを使ってあなたに";
		mes "ルーンストーンを作ってもらうわ。^000000";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "この書斎で読んだ本の内容を";
		mes "ちゃんと覚えているなら";
		mes "私が説明しなくてもルーンストーンを";
		mes "作れるはずよ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "ルーンストーンの作成を開始すると";
		mes "炉の中でルーンストーンが生成される";
		mes "様子を見ることができるわ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "あなたはその様子を見て";
		mes "^0000FF生成されるであろうルーンストーンの";
		mes "名前を頭の中で強くイメージするの。^000000";
		mes "簡単でしょ？";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "作成目標は^0000FFルーンストーン2個^000000よ。";
		mes "よく覚えておいてね。";
		set CHANGE_RK,13;
		chgquest 3213,3214;
		close;
	case 13:
		mes "[紅蓮のルーンナイト　レノア]";
		//mes "^0000FF私の背後にある石造の足元に";	// 本鯖仕様
		mes "^0000FF私の背後にある石像の足元に";
		mes "ルーンストーンを生成するための";
		mes "炉があるわ。これを使ってあなたに";
		mes "ルーンストーンを作ってもらうわ。^000000";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "この書斎で読んだ本の内容を";
		mes "ちゃんと覚えているなら";
		mes "私が説明しなくてもルーンストーンを";
		mes "作れるはずよ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "ルーンストーンの作成を開始すると";
		mes "炉の中でルーンストーンが生成される";
		mes "様子を見ることができるわ。";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "あなたはその様子を見て";
		mes "^0000FF生成されるであろうルーンストーンの";
		mes "名前を頭の中で強くイメージするの。^000000";
		mes "簡単でしょ？";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "作成目標は^0000FFルーンストーン2個^000000よ。";
		next;
		if(select("生成したルーンの数は？","2個作りました！") == 1) {
			mes "[紅蓮のルーンナイト　レノア]";
			mes "これまで生成されたルーンストーンは";
			mes CHANGE_RK_RUNE + "個ね……。";
			close;
		}
		if(CHANGE_RK_RUNE < 2) {
			emotion 6;
			mes "[紅蓮のルーンナイト　レノア]";
			mes "こら！　私は2個作るように";
			mes "言ったはずよ。";
			mes "これじゃあ、足りないわ。";
			close;
		}
		else if(CHANGE_RK_RUNE == 2) {
			emotion 33;
			mes "[紅蓮のルーンナイト　レノア]";
			mes "ふむ……よろしい。2個ちょうどね。";
			mes "作ってもらったルーンストーンは";
			mes "私からティグリースに渡しておくわ。";
			next;
		}
		else {
			mes "[紅蓮のルーンナイト　レノア]";
			mes "あら……2個を越えてルーンストーンを";
			mes "作ってしまったようね。";
			mes "超過して作ったことが、必ずしも";
			mes "いいことだとは言えないわ。";
			next;
			mes "[紅蓮のルーンナイト　レノア]";
			mes "これだけのルーンストーンを作る中で";
			mes "失敗して失われた魔力があったとしたら";
			mes "大きな損をしたことになるのよ？";
			mes "まあ、今回はいいけど……。";
			next;
		}
		mes "[紅蓮のルーンナイト　レノア]";
		mes "さ、私の試験はこれで終了よ。";
		mes "^0000FFマスターに伝えて、次の試験に";
		mes "進んでちょうだい。^000000";
		set CHANGE_RK,14;
		set CHANGE_RK_RUNE,0;
		chgquest 104485,3215;
		close;
	case 14:
	case 15:
		mes "[紅蓮のルーンナイト　レノア]";
		mes "さ、私の試験はこれで終了よ。";
		mes "^0000FFマスターに伝えて、次の試験に";
		mes "進んでちょうだい。^000000";
		next;
		mes "[紅蓮のルーンナイト　レノア]";
		mes "途中で気づいていたかもしれないけど";
		mes "最初から私の試験は合格と不合格がある";
		mes "試験ではなかったのよ。";
		mes "緊張してたら、もうリラックスしても";
		mes "大丈夫だから。";
		close;
	case 16:
		mes "[紅蓮のルーンナイト　レノア]";
		mes "ベルフィーノは素直じゃないから";
		mes "人によって答えの違う試験を出すのよ。";
		mes "でも、あなたは認められて";
		mes "合格できたようね。";
		mes "おめでとう！";
		close;
	}
}

job3_rune01.gat,40,54,0	script	厳然たる装丁の本	844,{
	if(Job != Job_RuneKnight && CHANGE_RK < 9) {
		mes "[紅蓮のルーンナイト　レノア]";
		mes "勝手に、ここの物に手を出すことは";
		mes "さておき……その内容があなたに";
		mes "理解できるのかしら？";
		next;
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "ははは！";
		mes "レノア、いい加減にしないか。";
		mes "君も勝手に、ここの物に触れるのは";
		mes "やめたほうがいいぞ";
		close2;
		cutin "3rd_rune_knight",255;
		end;
	}
	mes "‐手に取った本の表紙には";
	mes "　^0000FF『ルーンとルーンナイト』^000000と";
	mes "　記載されている‐";
	next;
	while(1) {
		switch(select("『ルーンナイトの誕生』","『ルーンと魔法エナジー』","本を元の場所に戻す")) {
		case 1:
			mes "^6A0000ルーンナイトとは";
			mes "ソードマスターであり";
			mes "龍飛流の始祖として知られる";
			mes "伝説の剣士ベルゼブが生み出した";
			mes "剣と魔法の調和を心得て進化した";
			mes "剣士達のことだ。^000000";
			next;
			mes "^6A0000魔力エナジーではなく、体内で直接";
			mes "生成されたルーンストーンという";
			mes "媒体を利用し、ルーン固有の魔力を";
			mes "駆使できることが一般的な剣士達と";
			mes "一番異なる部分である。^000000";
			next;
			mes "^6A0000知られた通り「魔法力は基本的に";
			mes "体内で魔力生成が可能な適性者達が";
			mes "長い期間の修練によって";
			mes "使えるようになる」という通説を";
			mes "破ったのが「ルーン魔力」であり";
			mes "その詳細は、未だに研究中である。^000000";
			next;
			mes "^6A0000ソードマスター　ベルゼブは";
			mes "自分自身の力の限界を感じ、";
			mes "人間界の物理的な制限を越える方法を";
			mes "発見した者として知られている。";
			mes "既に十数年前から異世界の存在達と";
			mes "接触していたようだ。^000000";
			next;
			mes "^6A0000魔王モロクによる次元崩壊の時から";
			mes "その存在が確認された";
			mes "異世界の妖精族「ラフィネ族」は";
			mes "ルーンナイトの誕生に";
			mes "深く関わっているという。^000000";
			next;
			mes "^6A0000人間系とは異なる自然的な";
			mes "魔力の生成が可能な";
			mes "異世界の生命体から魔力の源泉を";
			mes "溜められる媒体の研究によって";
			mes "適性者ではなくても魔力を";
			mes "使えるようになったのだ。^000000";
			next;
			mes "^6A0000この研究の成果物がルーン魔力と";
			mes "ルーンストーンである。";
			mes "剣の強さと魔力の調査を成し遂げ";
			mes "新しい力を手に入れた剣士と";
			mes "彼の弟子達がルーンナイトとして";
			mes "この世に現れることになった。^000000";
			set '@book,'@book|1;
			next;
			continue;
		case 2:
			mes "^6A0000ルーンストーンと呼ばれる宝石は";
			mes "実体化されてない魔力という無形の";
			mes "存在を込めて、その精髄を直接";
			mes "扱えるようにした媒体である。^000000";
			next;
			mes "^6A0000ラフィネ族の賢者セルフィオネが";
			mes "ルーンナイトの始祖であるベルゼブと";
			mes "共に研究したその結果が、今も研究が";
			mes "進んでいる無限のエナジー源でもある。^000000";
			next;
			mes "^6A0000人間系の生命体とは異なり";
			mes "我々が異世界と呼ぶ";
			mes "「アッシュ・バキューム」の";
			mes "生命体は、大きさはそれぞれ異なるが";
			mes "魔力の源泉を体内に持っているという";
			mes "点に注目し、考案されたエナジーの";
			mes "保存法だと知られている。^000000";
			next;
			mes "^6A0000魔力の源泉から引き出した魔力を";
			mes "ルーンに変える作業は";
			mes "ルーンマスタリーと呼ばれる高位の";
			mes "ルーン精錬術によって可能であり";
			mes "これはベルゼブと彼の弟子達である";
			mes "ルーンナイトの固有スキルとして";
			mes "伝承されている。^000000";
			set '@book,'@book|2;
			next;
			continue;
		case 3:
			if(CHANGE_RK == 9) {
				if(checkquest(104465)) {
					mes "‐この本はすでに読み終わって";
					mes "　いたはずだ‐";
					close;
				}
				else if('@book == 3) {
					misceffect 16,"";
					mes "‐本を読み終わった。";
					mes "　知識が身についたように思う‐";
					setquest 104465;
					close;
				}
			}
			mes "‐いったん本を元に戻した。";
			mes "　続きはまた後で読もう‐";
			close;
		}
	}
}

job3_rune01.gat,43,44,0	script	絢爛たる装丁の本	844,{
	if(Job != Job_RuneKnight && CHANGE_RK < 9) {
		mes "[紅蓮のルーンナイト　レノア]";
		mes "勝手に、ここの物に手を出すことは";
		mes "さておき……その内容があなたに";
		mes "理解できるのかしら？";
		next;
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "ははは！";
		mes "レノア、いい加減にしないか。";
		mes "君も勝手に、ここの物に触れるのは";
		mes "やめたほうがいいぞ";
		close2;
		cutin "3rd_rune_knight",255;
		end;
	}
	mes "‐手に取った本の表紙には";
	mes "　^0000FF『ルーンの原理と種類』^000000と";
	mes "　記載されている‐";
	next;
	while(1) {
		switch(select("『ルーンの原理』","『ルーンの種類』","本を元の場所に戻す")) {
		case 1:
			mes "^6A0000ルーンは一種の記号として";
			mes "ルーンミッドガッツ王国の";
			mes "誕生以前から密かに使われていた";
			mes "呪術的な意味が強い";
			mes "言語体系とも言える。^000000";
			next;
			mes "^6A0000ルーンの体系とその意味に関しては";
			mes "現在、直接言及された資料は";
			mes "ほとんど残っていないが";
			mes "ゲフェンとジュノーの学者達と";
			mes "アルナベルツの学者達によって";
			mes "研究されている。^000000";
			next;
			mes "^6A0000ルーンは記号体系としても";
			mes "利用されるが、";
			mes "口伝されている話によると、占いや";
			mes "人間の潜在意識を引き出す呪術に";
			mes "使用されてきたという説がある。^000000";
			next;
			mes "^6A0000ルーンは独自の体系と種類を持ち";
			mes "配列によって色んな力を";
			mes "引き出すこともできるという。";
			mes "その力については";
			mes "現在の技術では測定できない。^000000";
			next;
			mes "^6A0000ルーンナイト達の登場と共に";
			mes "歴史の舞台に登場した";
			mes "ルーンの可能性は";
			mes "肯定的な側面で注目されているが";
			mes "使用者によっては悪用される可能性も";
			mes "ありえるという点も指摘されている。^000000";
			set '@book,'@book|1;
			next;
			continue;
		case 2:
			mes "^6A0000ルーンは全部で25種の小さい石で";
			mes "構成されており、外部からの衝撃に";
			mes "脆弱な為、その保管と取り扱いには";
			mes "特別な注意を求められる。^000000";
			next;
			mes "^6A000025種のルーン達は各々の意味を持ち";
			mes "この中で14種は逆位置になった時";
			mes "本来の力とは違う意味を";
			mes "持つことになる。";
			mes "様々なパターンによる例外についての";
			mes "研究は必須と言えよう。^000000";
			next;
			mes "^6A0000他の11種のルーンは位置に関係なく";
			mes "一貫した力を持つため";
			mes "11個の正ルーンと14個の逆ルーンを";
			mes "合わせて、25種のルーンすべてを";
			mes "マスターしないと完全な力を";
			mes "引き出すことはできない。^000000";
			next;
			mes "^6A000011個の正ルーンの中で空白のルーンは";
			mes "例外ルーンとして扱う。^000000";
			next;
			mes "^6A000025種のルーンストーンの名前を";
			mes "次に列挙する。^000000";
			next;
			mes "^6A0000エイシル、オシラ、マンナズ、";
			mes "アンスール、ハガラズ、カノ、";
			mes "ライゾ、スリサズ、ダガズ、";
			mes "ソウィル、ラクス、イス、";
			mes "ペオース、ベルカナ、ゲーボ、";
			mes "アルジス、エイワズ、テイワズ、^000000";
			next;
			mes "^6A0000ウンジョー、ジュラ、ナウシズ、";
			mes "イングズ、フェオ、ウルズ、";
			mes "そして空白のルーンである、ウィアド。^000000";
			set '@book,'@book|2;
			next;
			continue;
		case 3:
			if(CHANGE_RK == 9) {
				if(checkquest(104470)) {
					mes "‐この本はすでに読み終わって";
					mes "　いたはずだ‐";
					close;
				}
				else if('@book == 3) {
					misceffect 16,"";
					mes "‐本を読み終わった。";
					mes "　知識が身についたように思う‐";
					setquest 104470;
					close;
				}
			}
			mes "‐いったん本を元に戻した。";
			mes "　続きはまた後で読もう‐";
			close;
		}
	}
}

job3_rune01.gat,50,36,0	script	清麗なる装丁の本	844,{
	if(Job != Job_RuneKnight && CHANGE_RK < 9) {
		mes "[紅蓮のルーンナイト　レノア]";
		mes "勝手に、ここの物に手を出すことは";
		mes "さておき……その内容があなたに";
		mes "理解できるのかしら？";
		next;
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "ははは！";
		mes "レノア、いい加減にしないか。";
		mes "君も勝手に、ここの物に触れるのは";
		mes "やめたほうがいいぞ";
		close2;
		cutin "3rd_rune_knight",255;
		end;
	}
	mes "‐手に取った本の表紙には";
	mes "　^0000FF『ルーンストーンの制作と使用』^000000と";
	mes "　記載されている‐";
	next;
	while(1) {
		switch(select("『ルーンストーンの制作』","『ルーンストーンの詳細』","本を元の場所に戻す")) {
		case 1:
			mes "^6A0000ルーンストーンはルーンナイトの";
			mes "ルーンマスタリーという";
			mes "固有スキルによって制作される。";
			mes "ルーンマスタリーはルーンナイトの";
			mes "標識として体内に入力された一種の";
			mes "固有パスワードと同一のものである。^000000";
			next;
			mes "^6A0000ルーンナイトでない人間も";
			mes "特別に制限された条件に従うことで";
			mes "ルーンの生成と使用が出来る。";
			mes "しかし、これはルーン加熱炉と";
			mes "呼ばれる固有の機器を必要とする。^000000";
			next;
			mes "^6A0000加熱炉を利用し、ルーンストーンを";
			mes "生成する場合は、ルーン加熱炉に";
			mes "入れた魔力エナジーによって";
			mes "生成されるルーンの種類が";
			mes "決定される。";
			mes "これは変更が不可能である。^000000";
			next;
			mes "^6A0000ルーンマスタリーを利用し";
			mes "ルーンストーンを生成する場合は";
			mes "使用者が求むルーンの性質を";
			mes "生成できるが、これはルーンナイト";
			mes "のみの固有能力として分類する。^000000";
			next;
			mes "^6A0000異世界の魔力エナジーを";
			mes "身に溜めた状態で、ルーン加熱炉を";
			mes "作動させると体内の魔力エナジーが";
			mes "ルーン加熱炉を通じ収束し、";
			mes "ルーンストーンとして変換される。^000000";
			next;
			set '@book,'@book|1;
			next;
			continue;
		case 2:
			switch(select("第1章","第2章","第3章","第4章","本を元の場所に戻す")) {
			case 1:
				mes "^6A0000‐エイシル‐";
				mes "このルーンは肯定的な力の増強を示し";
				mes "加熱炉では赤い螺旋形になる。^000000";
				next;
				mes "^6A0000‐オシラ‐";
				mes "このルーンは等価交換、即ち";
				mes "「一つを失い、一つを得る」を示し";
				mes "代価を必要とする力を意味する。";
				mes "加熱炉では紫色の円形になる。^000000";
				next;
				mes "^6A0000‐マンナズ‐";
				mes "このルーンは希望と";
				mes "新しい始まりを示し、";
				mes "絶望的な状況を逆転させる";
				mes "肯定的な力を意味する。";
				mes "加熱炉ではエメラルド色の菱形になる。^000000";
				next;
				mes "^6A0000‐アンスール‐";
				mes "このルーンは準備を示し、来る未来の";
				mes "不安を乗り越える力を意味する。";
				mes "加熱炉ではエメラルド色の円形になる。^000000";
				next;
				mes "^6A0000‐ハガラズ‐";
				mes "このルーンは自由を示し";
				mes "拘束に抵抗する力を意味する。";
				mes "加熱炉では空色の星形になる。^000000";
				next;
				mes "^6A0000‐カノ‐";
				mes "このルーンは炎と情熱を示し";
				mes "全てを終わらせる力を意味する。";
				mes "加熱炉では赤い菱形になる。^000000";
				next;
				break;
			case 2:
				mes "^6A0000‐ライゾ‐";
				mes "このルーンは結合と再結合を示し";
				mes "完全の力を意味する。";
				mes "加熱炉では空色の斜線形になる。^000000";
				next;
				mes "^6A0000‐スリサズ‐";
				mes "このルーンは警戒を示し";
				mes "制限の力を意味する。";
				mes "加熱炉では黄色い星形になる。^000000";
				next;
				mes "^6A0000‐ダガズ‐";
				mes "このルーンは再起を示し、";
				mes "逆境を乗り越える力を意味する。";
				mes "加熱炉ではエメラルド色の螺旋形になる。^000000";
				next;
				mes "^6A0000‐ソウィル‐";
				mes "このルーンは勝利と成功を示し";
				mes "整理と終息の力を意味する。";
				mes "加熱炉では空色の扇形になる。^000000";
				next;
				mes "^6A0000‐ラクス‐";
				mes "このルーンは否定を示し";
				mes "内面を護る力を意味する。";
				mes "加熱炉では黄色い菱形になる。^000000";
				next;
				mes "^6A0000‐イス‐";
				mes "このルーンは停止を示し";
				mes "全てを止める力を意味する。";
				mes "加熱炉では紫色の螺旋形になる。^000000";
				next;
				break;
			case 3:
				mes "^6A0000‐ペオース‐";
				mes "このルーンは啓示を示し";
				mes "機会の力を意味する。";
				mes "加熱炉では銀色の螺旋形になる。^000000";
				next;
				mes "^6A0000‐ベルカナ‐";
				mes "このルーンは豊かさと誕生を示し";
				mes "防御と防護の力を意味する。";
				mes "加熱炉では金色の星形になる。^000000";
				next;
				mes "^6A0000‐ゲーボ‐";
				mes "このルーンは協力を示し";
				mes "調和の力を意味する。";
				mes "加熱炉では黄色い円錐形になる。^000000";
				next;
				mes "^6A0000‐アルジス‐";
				mes "このルーンは機会と挑戦の力を";
				mes "意味する。";
				mes "加熱炉ではエメラルド色の斜線形になる。^000000";
				next;
				mes "^6A0000‐エイワズ‐";
				mes "このルーンは変化と激動を示し";
				mes "移動の力を意味する。";
				mes "加熱炉では灰色の菱形になる。^000000";
				next;
				mes "^6A0000‐テイワズ‐";
				mes "このルーンは完璧な勝利を示し";
				mes "絶対的な解決を意味する。";
				mes "加熱炉では金色の円形になる。^000000";
				next;
				break;
			case 4:
				mes "^6A0000‐ウンジョー‐";
				mes "このルーンは賢さを示し";
				mes "知恵の力を意味する。";
				mes "加熱炉ではエメラルド色の星形になる。^000000";
				next;
				mes "^6A0000‐ジュラ‐";
				mes "このルーンは気楽さを示し";
				mes "休息の力を意味する。";
				mes "加熱炉では黄色い円形になる。^000000";
				next;
				mes "^6A0000‐ナウシズ‐";
				mes "このルーンは衰弱を示し";
				mes "弱化の力を意味する。";
				mes "加熱炉では黄色い扇形になる。^000000";
				next;
				mes "^6A0000‐イングズ‐";
				mes "このルーンは分裂を示し";
				mes "分離の力を意味する。";
				mes "加熱炉では紫色の菱形になる。^000000";
				next;
				mes "^6A0000‐フェオ‐";
				mes "このルーンは実現を示し";
				mes "具現の力を意味する。";
				mes "加熱炉では銀色の円形になる。^000000";
				next;
				mes "^6A0000‐ウルズ‐";
				mes "このルーンは運命を示し";
				mes "拘束の力を意味する。";
				mes "加熱炉では紫色の斜線形になる。^000000";
				next;
				break;
			case 5:
				continue;
			}
			set '@book,'@book|2;
			continue;
		case 3:
			if(CHANGE_RK == 9) {
				if(checkquest(104475)) {
					mes "‐この本はすでに読み終わって";
					mes "　いたはずだ‐";
					close;
				}
				else if('@book == 3) {
					misceffect 16,"";
					mes "‐本を読み終わった。";
					mes "　知識が身についたように思う‐";
					setquest 104475;
					close;
				}
			}
			mes "‐いったん本を元に戻した。";
			mes "　続きはまた後で読もう‐";
			close;
		}
	}
}

mid_camp.gat,238,250,3	script	賢者の守護騎士	468,{
	if(Job == Job_RuneKnight) {
		mes "[賢者を守護するルーンナイト]";
		mes "賢者セルフィオネ様は、ルーンナイトと";
		mes "始終を共にしておられる方だ。";
		next;
		mes "[賢者を守護するルーンナイト]";
		mes "この方の御側に仕えることに";
		mes "オレはルーンナイトとしての";
		mes "誇りを強く感じている。";
		close;
	}
	if(CHANGE_RK == 0) {
		mes "[賢者を守護するルーンナイト]";
		mes "この方の周りを無闇にうろつくことを";
		mes "許すことはできない。";
		mes "大人しく下がる方が身のためだぞ。";
		close;
	}
	else if(CHANGE_RK < 10) {
		mes "[賢者を守護するルーンナイト]";
		mes "剣を使う者よ……。";
		mes "例え我々と似た道を歩む者だとしても";
		mes "この方の周りを無闇にうろつくことを";
		mes "許すことはできない。";
		close;
	}
	mes "[賢者を守護するルーンナイト]";
	mes "ルーンナイトの候補生に限り";
	mes "特別な許可がなくとも駐屯地に滞在する";
	mes "ことが許されている。";
	next;
	mes "[賢者を守護するルーンナイト]";
	mes "君がこの地で自由に行動したければ";
	mes "遠征隊に協力し、信任を得なければ";
	mes "ならないだろう。";
	close;
}

mid_camp.gat,235,250,3	script	賢者セルフィオネ	435,{
	if(Job == Job_RuneKnight) {
		mes "[賢者セルフィオネ]";
		mes "あなたも立派なルーンナイトの一員に";
		mes "なったのですね。";
		mes "あなたの未来に少しでも役に立つことが";
		mes "できて、とても嬉しく思います。";
		next;
		mes "[賢者セルフィオネ]";
		mes "ルーンの力は完璧ではありません。";
		mes "未だに解き明かされていない";
		mes "不完全な力ですが……その力を制御し";
		mes "発展させるのは、あなた達と私が";
		mes "担うことでしょう。";
		next;
		mes "[賢者セルフィオネ]";
		mes "どうかこれからも精進を怠らず";
		mes "あなたの望む悟りに至りますように。";
		close;
	}
	if(CHANGE_RK < 10) {
		mes "[賢者セルフィオネ]";
		mes "ラフィネ族の私が、あなた達人間の";
		mes "駐屯地にいることに疑問を抱いて";
		mes "おられるようですね。";
		next;
		mes "[賢者セルフィオネ]";
		mes "あなたが考えているずっと以前から";
		mes "私達は特殊な状況下において";
		mes "人間達と接触がありました。";
		next;
		mes "[賢者セルフィオネ]";
		mes "私もまた、一人の人間とお互いの為";
		mes "数年間、交流をしていました。";
		mes "そのため、あなたともこうして";
		mes "お話することができるのです。";
		next;
		mes "[賢者セルフィオネ]";
		mes "私以外のラフィネ族と会話するには";
		mes "私たちの言語を翻訳するための";
		mes "機械が必要となることでしょう。";
		next;
		mes "[賢者セルフィオネ]";
		mes "それ以上のことについては……";
		mes "私からは話すことはできません。";
		mes "ここでの行動の自由は認められて";
		mes "いますが、この世界に関する発言は";
		mes "制限されていますので……。";
		close;
	}
	switch(CHANGE_RK) {
	case 10:
		mes "[賢者セルフィオネ]";
		mes "ようこそ。";
		mes "ルーンナイトの候補生の方ですね？";
		mes "私がセルフィオネです。";
		next;
		mes "[賢者セルフィオネ]";
		mes "あなたの出会ったルーンナイト達は";
		mes "みんな、ベルゼブと私の師事を受けた";
		mes "弟子達です。";
		mes "あなたもその一人というわけです。";
		next;
		mes "[賢者セルフィオネ]";
		mes "レノアから、ルーンの基礎は教えて";
		mes "もらったと思いますが、今回は私が";
		mes "あなたをお手伝いします。";
		next;
		mes "[賢者セルフィオネ]";
		mes "ルーンナイトが使用する";
		mes "ルーンストーンの魔力は、基本的に";
		mes "人間界の魔力ではありません。";
		next;
		mes "[賢者セルフィオネ]";
		mes "それは、この世界……";
		mes "あなた達はアッシュ・バキュームと呼ぶ";
		mes "私達の世界……";
		mes "アールブヘイムで作られた魔力です。";
		next;
		mes "[賢者セルフィオネ]";
		mes "この地の生命は、人間世界の生命とは";
		mes "異なり、体内に魔力をエナジーの";
		mes "形にして保有しています。";
		next;
		mes "[賢者セルフィオネ]";
		mes "ルーンストーンの魔力というのは";
		mes "この世界の生命が保有する";
		mes "魔力エナジーをルーンという別の形に";
		mes "変えて使用できるようにしたもの。";
		next;
		mes "[賢者セルフィオネ]";
		mes "つまり、ルーンストーンを使用するには";
		mes "異世界の生命に対する理解が";
		mes "必要となるのです。";
		next;
		mes "[賢者セルフィオネ]";
		mes "しかし……この地の生命から";
		mes "魔力エナジーを集めるには";
		mes "今のあなたには少々重荷かと思います。";
		next;
		mes "[賢者セルフィオネ]";
		mes "そこで、これからあなたの体に";
		mes "生命からの魔力エナジーを収める魔法を";
		mes "かけてあげます。";
		next;
		misceffect 58,"";
		mes "‐セルフィオネは何かを唱えた。";
		mes "　不思議な光が体を包み込んだ‐";
		next;
		mes "[賢者セルフィオネ]";
		mes "あくまで一時的ではありますが";
		mes "人間界の思念体を倒すことで";
		mes "魔力エナジーを得ることができます。";
		mes "そのエナジーを、そのまま使うことは";
		mes "出来ないのですけど……。";
		next;
		mes "[賢者セルフィオネ]";
		mes "^0000FFでは、私が指定する人間世界の";
		mes "思念体を倒して、エナジーを";
		mes "集めてきてもらいます。^000000";
		next;
		mes "[賢者セルフィオネ]";
		mes "そうですね……あなた達の世界では";
		mes "死者が集まる^0000FFニブルヘイム^000000という";
		mes "場所があると聞きました。";
		mes "死後も彷徨う者達のエナジーは";
		mes "充分な魔力の源泉となります。";
		next;
		mes "[賢者セルフィオネ]";
		mes "^0000FFデュラハン2体^000000、";
		mes "^0000FFディスガイズ2体^000000、";
		mes "^0000FFキューブ2体^000000を倒し";
		mes "エナジーを集めて来て下さい。";
		next;
		mes "[賢者セルフィオネ]";
		mes "エナジーを集め終わったら";
		mes "レノアに頼めば、再び私の元へ";
		mes "転送してくれるでしょう。";
		next;
		mes "[賢者セルフィオネ]";
		mes "先にお伝えしますが、私はあなたの";
		mes "資格を判断することはしません。";
		mes "判断はあなたの先輩である他の";
		mes "ルーンナイト達がすることですから。";
		next;
		mes "[賢者セルフィオネ]";
		mes "それでは頑張ってください。";
		mes "何か聞きたいことがありましたら";
		mes "声を掛けて下さいね。";
		set CHANGE_RK,11;
		chgquest 3207,3208;
		setquest 3209;
		setquest 3210;
		setquest 3211;
		close;
	case 11:
		mes "[賢者セルフィオネ]";
		mes "魔力エナジーは集まりましたか？";
		mes "それとも聞きたいことでもありますか？";
		next;
		switch(select("魔力エナジーを集めました","倒すべき敵を教えて","ルーンナイト集結地に戻りたい","会話をやめる")) {
		case 1:
			mes "[賢者セルフィオネ]";
			mes "わかりました。";
			mes "それでは、確認しましょう。";
			next;
			if(checkquest(3209)&4 == 0 || checkquest(3210)&4 == 0 || checkquest(3211)&4 == 0) {
				emotion 9;
				mes "[賢者セルフィオネ]";
				mes "……まだ足りていないようです。";
				mes "次に進むために必要な魔力エナジーを";
				mes "集められていませんよ。";
				next;
				mes "[賢者セルフィオネ]";
				mes "頑張って目標を達成してから";
				mes "私のところに来て下さいね。";
				close;
			}
			emotion 33;
			mes "[賢者セルフィオネ]";
			mes "まあ、すばらしい！";
			mes "充分な量の魔力エナジーがあなたの体に";
			mes "蓄積されています。";
			next;
			mes "[賢者セルフィオネ]";
			mes "これだけあれば、^0000FFレノアが";
			mes "ルーンストーンの生成について";
			mes "教えてくれるはずです。^000000";
			next;
			mes "[賢者セルフィオネ]";
			mes "私の役割はこれで終わりです。";
			mes "ルーンナイトとして生まれ変わった";
			mes "あなたに再会できるよう";
			mes "祈っています。";
			next;
			mes "[賢者セルフィオネ]";
			mes "この地での用事が済んでいるのでしたら";
			mes "ルーンナイト集結地に送りましょう。";
			mes "準備ができたら、話しかけて下さいね。";
			set CHANGE_RK,12;
			chgquest 3208,3213;
			delquest 3209;
			delquest 3210;
			delquest 3211;
			close;
		case 2:
			mes "[賢者セルフィオネ]";
			mes "あなた達の世界では";
			mes "死者が集まる^0000FFニブルヘイム^000000という";
			mes "場所があると聞きました。";
			mes "死後も彷徨う者達のエナジーは";
			mes "充分な魔力の源泉となります。";
			next;
			mes "[賢者セルフィオネ]";
			mes "^0000FFデュラハン2体^000000、";
			mes "^0000FFディスガイズ2体^000000、";
			mes "^0000FFキューブ2体^000000を倒し";
			mes "エナジーを集めて来て下さい。";
			close;
		case 3:
			mes "[賢者セルフィオネ]";
			mes "お望みであれば、すぐにお送りします。";
			mes "しかし、試験を継続するためには";
			mes "再び私の所に来ていただく必要が";
			mes "ありますよ。";
			next;
			mes "[賢者セルフィオネ]";
			mes "今すぐルーンナイト集結地に";
			mes "戻りますか？";
			next;
			if(select("戻ります","まだ戻りません") == 2) {
				mes "[賢者セルフィオネ]";
				mes "準備ができたら話しかけてください。";
				close;
			}
			mes "[賢者セルフィオネ]";
			mes "それでは送ります。";
			close2;
			warp "job3_rune01.gat",80,65;
			end;
		case 4:
			mes "[賢者セルフィオネ]";
			mes "聞きたいことがありましたら";
			mes "いつでも来て下さいね。";
			close;
		}
	case 12:
		mes "[賢者セルフィオネ]";
		mes "ルーンナイト集結地に戻る";
		mes "準備はできましたか？";
		next;
		if(select("戻ります","まだ準備が出来ていません") == 2) {
			mes "[賢者セルフィオネ]";
			mes "準備ができたら話しかけてください。";
			close;
		}
		mes "[賢者セルフィオネ]";
		mes "それでは送ります。";
		close2;
		warp "job3_rune01.gat",80,65;
		end;
	default:
		mes "[賢者セルフィオネ]";
		mes "試験は順調ですか？";
		next;
		mes "[賢者セルフィオネ]";
		mes "もしかして、あなたは何か";
		mes "間違った状態で、ここに来たのでは";
		mes "ありませんか？";
		next;
		mes "[賢者セルフィオネ]";
		mes "あなたがいるべき場所……。";
		mes "ルーンナイト集結地に送りましょう。";
		next;
		if(select("今すぐ戻ります","まだ、ここに用があります") == 2) {
			mes "[賢者セルフィオネ]";
			mes "用が済んだら私に話しかけてください。";
			close;
		}
		mes "[賢者セルフィオネ]";
		mes "それでは送ります。";
		close2;
		warp "job3_rune01.gat",80,65;
		end;
	}
}


job3_rune01.gat,58,51,0	script	石像の謎の穴	844,{
	if(CHANGE_RK != 13) {
		mes "[紅蓮のルーンナイト　レノア]";
		mes "そこは勝手に触らないほうがいいわよ。";
		mes "……冗談じゃ済まないから。";
		close;
	}
	mes "‐レノアの後ろに立つ巨大な";
	mes "　ルーンナイト像の足元に";
	mes "　拳ほどの大きさの穴が見える。";
	mes "　確かこれは、本で読んだ";
	mes "　量産型ルーンストーンの加熱炉だ‐";
	next;
	if(select("ルーンストーンの生成を始める","何もしない") == 2) {
		mes "[紅蓮のルーンナイト　レノア]";
		mes "ルーンストーンを作る準備が出来たら";
		mes "その加熱炉を使いなさい。";
		close;
	}
	mes "‐ルーンの魔力が揺れ";
	mes "　加熱炉で徐々に形を成していく‐";
	next;
	switch(rand(24)) {
	case 0:  set '@rune$,"エイシル";   mes "‐赤い螺旋形で燃え盛る";           break;
	case 1:  set '@rune$,"オシラ";     mes "‐紫色の円形で燃え盛る";           break;
	case 2:  set '@rune$,"マンナズ";   mes "‐エメラルド色の菱形で燃え盛る";   break;
	case 3:  set '@rune$,"アンスール"; mes "‐エメラルド色の円形で燃え盛る";   break;
	case 4:  set '@rune$,"ハガラズ";   mes "‐空色の星形で燃え盛る";           break;
	case 5:  set '@rune$,"カノ";       mes "‐赤い菱形で燃え盛る";             break;
	case 6:  set '@rune$,"ライゾ";     mes "‐空色の斜線形で燃え盛る";         break;
	case 7:  set '@rune$,"スリサズ";   mes "‐黄色い星形で燃え盛る";           break;
	case 8:  set '@rune$,"ダガズ";     mes "‐エメラルド色の螺旋形で燃え盛る"; break;
	case 9:  set '@rune$,"ソウィル";   mes "‐空色の扇形で燃え盛る";           break;
	case 10: set '@rune$,"ラクス";     mes "‐黄色い菱形で燃え盛る";           break;
	case 11: set '@rune$,"イス";       mes "‐紫色の螺旋形で燃え盛る";         break;
	case 12: set '@rune$,"ペオース";   mes "‐銀色の螺旋形で燃え盛る";         break;
	case 13: set '@rune$,"ベルカナ";   mes "‐金色の星形で燃え盛る";           break;
	case 14: set '@rune$,"ゲーボ";     mes "‐黄色い円錐形で燃え盛る";         break;
	case 15: set '@rune$,"アルジス";   mes "‐エメラルド色の斜線形で燃え盛る"; break;
	case 16: set '@rune$,"エイワズ";   mes "‐灰色の菱形で燃え盛る";           break;
	case 17: set '@rune$,"テイワズ";   mes "‐金色の円形で燃え盛る";           break;
	case 18: set '@rune$,"ウンジョー"; mes "‐エメラルド色の星形で燃え盛る";   break;
	case 19: set '@rune$,"ジュラ";     mes "‐黄色い円形で燃え盛る";           break;
	case 20: set '@rune$,"ナウシズ";   mes "‐黄色い扇形で燃え盛る";           break;
	case 21: set '@rune$,"イングズ";   mes "‐紫色の菱形で燃え盛る";           break;
	case 22: set '@rune$,"フェオ";     mes "‐銀色の円形で燃え盛る";           break;
	case 23: set '@rune$,"ウルズ";     mes "‐紫色の斜線形で燃え盛る";         break;
	}
	mes "　このルーンストーンの名は確か……‐";
	next;
	input '@str$;
	if('@rune$ != '@str$) {
		if(rand(6)) {
			misceffect 306,"";
			mes "[紅蓮のルーンナイト　レノア]";
			mes "当然の結果よ。";
			mes "イメージしたルーンストーンと";
			mes "炉内のルーンストーンが異なれば";
			mes "成功する確率は極めて低くなる。";
			next;
			emotion 54,"レノア#RK";
			mes "[紅蓮のルーンナイト　レノア]";
			mes "ルーンストーンの生成は失敗よ。";
			mes "はい、もう一回やって。";
			close;
		}
		misceffect 305,"";
		mes "[紅蓮のルーンナイト　レノア]";
		mes "運がいいわね。";
		mes "イメージしたルーンストーンと";
		mes "炉内のルーンストーンが違うものだけど";
		mes "正常に生成されたわ。";
		mes "こんなケースは稀だけどね……。";
		next;
	}
	else {
		misceffect 305,"";
		mes "[紅蓮のルーンナイト　レノア]";
		mes "ふーん……素晴らしいわね。";
		mes "イメージしたルーンストーンと";
		mes "炉内のルーンストーンが一致したのね。";
		next;
	}
	emotion 33,"レノア#RK";
	mes "[紅蓮のルーンナイト　レノア]";
	mes "ルーンストーン　1個が";
	mes "正しく生成されたことを確認したわ。";
	set CHANGE_RK_RUNE,CHANGE_RK_RUNE + 1;
	if(CHANGE_RK_RUNE == 2) {
		mes " ";
		mes "‐ルーンストーンを2個生成した。";
		mes "　レノアに報告しよう‐";
		chgquest 3214,104485;
	}
	close;
}

//============================================================
// 最終試験
//------------------------------------------------------------
job3_rune01.gat,114,50,3	script	ベルフィーノ	468,{
	if(Job == Job_RuneKnight) {
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "オレからすれば、お前はまだまだ";
		mes "新米のルーンナイトだ。";
		mes "過信せず、その力を磨き続けろよ。";
		close;
	}
	switch(CHANGE_RK) {
	default:
		mes "‐頭の天辺から足の爪先まで黒一色の";
		mes "　冷たい気配を放つルーンナイトが";
		mes "　こちらの様子をうかがっている‐";
		next;
		mes "‐ルーンナイトというのは";
		mes "　口うるさくて性格が悪い者か";
		mes "　あるいは、無言で殺伐とした者しか";
		mes "　いないのかもしれない‐";
		next;
		cutin "3rd_rune_knight",2;
		mes "[マスター　ティグリース]";
		mes "お、おい……何か誤解していないか？";
		mes "オレは口うるさくもないし";
		mes "殺伐としているわけでもないだろ？";
		next;
		cutin "3rd_rune_knight",255;
		mes "‐空耳が聞こえたような気がする‐";
		close;
	case 15:
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "オレのところに来る候補生か……";
		mes "久々だな。";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "ここまでの試験を突破したことについて";
		mes "おめでとう、と言っておこう。";
		mes "これから最終試験を行うが";
		mes "お前はすでに基本を備えていると";
		mes "考えさせてもらうぞ。";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "といっても、最終試験は簡単だ。";
		mes "^0000FFこれから出す質問に答えてもらう。^000000";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "お前がルーンナイトになる目的はなんだ？";
		next;
		menu "武術を極める",-,"ドラゴンを操る",-,"ルーンを扱う",-,"仲間を守る",-;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "……";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "……ひとまず合格。";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "ルーンナイトになれば";
		mes "できる事の幅が広がる。";
		mes "それ故に皆、何かしらの目的を持って";
		mes "ルーンナイトになるものだ。";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "だが、もしいつか";
		mes "目的を見失ってしまうようなら";
		mes "お前とお前のルーンの輝きは";
		mes "失われてしまうだろう。";
		mes "試験に合格したことも、";
		mes "それまでの経験も全てが無に返すと思え。";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "初心をいつまでも忘れるな。";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "これで試験は全て終了だ。";
		mes "……なんだ、拍子抜けしているのか？";
		mes "^0000FFティグリースマスターに報告し^000000";
		mes "ルーンナイトとして新しく生まれ変わる";
		mes "感激を味わってくるといい。";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "本当におめでとう。";
		mes "それじゃあ、オレは他の候補性の為の";
		mes "仕事を再開するとしよう。";
		set CHANGE_RK,16;
		chgquest 3216,3219;
		close;
	case 16:
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "これで試験は全て終了だ。";
		mes "^0000FFティグリースマスターに報告し^000000";
		mes "ルーンナイトとして新しく生まれ変わる";
		mes "感激を味わってくるといい。";
		next;
		mes "[漆黒のルーンナイト　ベルフィーノ]";
		mes "本当におめでとう。";
		mes "それじゃあ、オレは他の候補性の為の";
		mes "仕事を再開するとしよう。";
		close;
	}
}

//============================================================
// ドラゴン管理兵
//------------------------------------------------------------
prontera.gat,129,212,5	script	ドラゴン管理兵	105,{
	if(Job != Job_RuneKnight && Job != Job_DragonKnight) {
		mes "[ドラゴン管理兵]";
		mes "何の御用ですか？";
		mes "あなたはドラゴンの利用を";
		mes "できない職業です。";
		close;
	}
	mes "[ドラゴン管理兵]";
	mes "いらっしゃいませ。";
	mes "ドラゴンをご利用ですか？";
	next;
	if(select("利用する","やめる") == 2) {
		mes "[ドラゴン管理兵]";
		mes "そうですか。では……";
		close;
	}
	if(checkdragon()) {
		mes "[ドラゴン管理兵]";
		mes "既にドラゴンに乗って";
		mes "いらっしゃいますね。";
		close;
	}
	if(sc_ison(SC_ALL_RIDING)) {
		mes "‐騎乗生物を利用した状態では";
		mes "　進行できません。";
		mes "　騎乗生物から降りてください‐";
		close;
	}
	if(getskilllv(63) < 1) {
		mes "[ドラゴン管理兵]";
		mes "……まだドラゴンには";
		mes "乗れないようですね。";
		mes "スキル「ライディング」を";
		mes "覚えてからお越しください。";
		close;
	}
	setdragon;
	close;
}

//============================================================
// ルーン原石販売員
//------------------------------------------------------------
prontera.gat,168,228,3	script	ルーン原石販売員#pro	853,{
	mes "[ルーン原石販売員]";
	mes "あなたはもしかして、";
	mes "ルーン原石をお求めですかな!?";
	mes "　";
	mes "今なら、いい原石をお売りしますよ。";
	next;
	switch(select("高級なルーン原石を買う","一般的なルーン原石を買う")) {
	case 1:
		mes "[ルーン原石販売員]";
		mes "ほほ～、これはお目が高い！";
		mes "高級なルーン原石ですな。";
		set '@price,2500;
		set '@gain,12734;
		break;
	case 2:
		mes "[ルーン原石販売員]";
		mes "お～、実に堅実な方ですな！";
		mes "一般的なルーン原石をお求めとは。";
		set '@price,1000;
		set '@gain,12737;
		break;
	}
	mes "この原石は1個 "+ '@price +"Zenyで";
	mes "お売りしましょう！";
	mes "2000個までなら、1度で渡しましょう。";
	mes "いくつ買いますかな？";
	next;
	input '@num;
	if('@num == 0) {
		mes "[ルーン原石販売員]";
		mes "おや、そうですか。";
		mes "残念ですな。";
		mes "買いたくなったら、";
		mes "またお越しください。";
		close;
	}
	if('@num < 1 || '@num > 2000) {
		mes "[ルーン原石販売員]";
		mes "お客さん、冗談でしょう。";
		mes "ちゃんと数を言ってもらわないと";
		mes "用意できませんよ。";
		mes "1度でお売りできるのは";
		mes "1～2000個ですからな。";
		close;
	}
	if(Zeny < '@price*'@num) {
		mes "[ルーン原石販売員]";
		mes "おやおや？";
		mes "お客さん、困りますな～";
		mes "Zenyが足りませんよ。";
		mes "しっかり払ってもらわないと";
		mes "商売あがったりですからな。";
		mes "お金を用意して、また来てください。";
		close;
	}
	if(checkitemblank() == 0) {
		mes "[ルーン原石販売員]";
		mes "おっと!?";
		mes "お客さん、ちょっと荷物が";
		mes "多すぎるようですな。";
		mes "これでは、購入数の";
		mes getitemname('@gain) +"を渡せそうにない。";
		mes "身軽にしてから、また来てください。";
		close;
	}
	if(checkweight('@gain,'@num) == 0) {
		mes "[ルーン原石販売員]";
		mes "おっと!?";
		mes "お客さん、ちょっと荷物が";
		mes "重過ぎるようですな。";
		mes "これでは、購入数の";
		mes getitemname('@gain)+ "を渡せそうにない。";
		mes "身軽にしてから、また来てください。";
		close;
	}
	set Zeny,Zeny - '@price * '@num;
	getitem '@gain,'@num;
	mes "[ルーン原石販売員]";
	mes "毎度ありがたいですな。";
	mes "またのご利用、";
	mes "お待ちしておりますよ。";
	close;
}
