//= Auriga Script ==============================================================
// Ragnarok Online RoyalGuard Jobchange Script	by Blaze
//- Registry -------------------------------------------------------------------
// CHANGE_AB -> 0～11
//==============================================================================

//============================================================
// マップフラグ
//------------------------------------------------------------
job3_arch01.gat	mapflag	nomemo		dummy
job3_arch01.gat	mapflag	noteleport	dummy
job3_arch01.gat	mapflag	nosave		SavePoint
job3_arch01.gat	mapflag	nobranch	dummy
job3_arch01.gat	mapflag	nopenalty	dummy
job3_arch01.gat	mapflag	noicewall	dummy
job3_arch02.gat	mapflag	nomemo		dummy
job3_arch02.gat	mapflag	noteleport	dummy
job3_arch02.gat	mapflag	nosave		SavePoint
job3_arch02.gat	mapflag	nobranch	dummy
job3_arch02.gat	mapflag	nopenalty	dummy
job3_arch02.gat	mapflag	noicewall	dummy

//============================================================
// モンスター
//------------------------------------------------------------
job3_arch02.gat,0,0,0,0	monster	ナイトメア				1427,2,5000,0,0
job3_arch02.gat,0,0,0,0	monster	レイドリックアーチャー	1453,2,5000,0,0
job3_arch02.gat,0,0,0,0	monster	ゾンビ					1394,5,5000,0,0
job3_arch02.gat,0,0,0,0	monster	ゾンビプリズナー		1480,3,5000,0,0

//============================================================
// 開始NPC
//------------------------------------------------------------
prt_church.gat,103,88,3	script	祈る聖職者	60,{
	if(Job == Job_ArchBishop) {
		emotion 0;
		mes "[祈る聖職者]";
		mes "おお、貴方からは以前よりも";
		mes "気高く高貴なオーラを感じます。";
		next;
		mes "[祈る聖職者]";
		mes "聖地巡礼の中で自分を磨いて";
		mes "来られたのですね。";
		mes "本当に素晴らしい……。";
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
	if(Job != Job_Priest || Upper == UPPER_NORMAL) {
		mes "[祈る聖職者]";
		mes "全能の神、オーディンの前に";
		mes "彼より聡慧な者はいないし";
		mes "彼より慈悲深い者もいない。";
		next;
		mes "[祈る聖職者]";
		mes "聖職者はいつも全ての仕事に";
		mes "真面目に取り組むべきです。";
		mes "神に仕え、彼のあとを踏むことを";
		mes "怠けてはいけません。";
		next;
		mes "[祈る聖職者]";
		mes "最近、聖職者達が世俗にまみれ";
		mes "本来の義務を忘却し";
		mes "形だけ飾ることに夢中になっている";
		mes "という話を聞きます。";
		next;
		mes "[祈る聖職者]";
		mes "もし、そんな聖職者を見たら";
		mes "プロンテラ聖堂まで訪ねて来るよう";
		mes "伝えてくれませんか？";
		next;
		mes "[祈る聖職者]";
		mes "私は彼らを、オーディンに仕える";
		mes "清くて品位がある聖職者として";
		mes "生まれ変われるようにするつもりです。";
		close;
	}
	switch(CHANGE_AB) {
	case 0:
		mes "‐穏やかそうな男性が";
		mes "　祈りを捧げている‐";
		next;
		if(select("話しかける","通り過ぎる") == 2) {
			mes "‐邪魔はしないでおこう‐";
			close;
		}
		if((Upper == UPPER_HIGH && BaseLevel < 90) || (Upper == UPPER_BABY && (BaseLevel < 99 || JobLevel < 50))) {
			mes "[祈る聖職者]";
			mes "全能の神、オーディンの前に";
			mes "彼より聡慧な者はいないし";
			mes "彼より慈悲深い者もいない。";
			next;
			mes "[祈る聖職者]";
			mes "聖職者はいつも全ての仕事に";
			mes "真面目に取り組むべきです。";
			mes "神に仕え、彼のあとを踏むことを";
			mes "怠けてはいけません。";
			next;
			mes "[祈る聖職者]";
			mes "貴方は経験が不足していますが";
			if(Upper == UPPER_HIGH)
				mes  "^3377FFBaseLvが90以上^000000なら";
			else
				mes  "^3377FFBaseLvが99、JobLvが50^000000なら";		// 養子のとき未調査
			mes "より清く、品位がある聖職者として";
			mes "生まれ変わる方法を教えましょう。";
			close;
		}
		cloakoffnpc "転職代行係#AB";
		misceffect 78,"転職代行係#AB";
		if(callfunc("Func_Job3rd",Job_ArchBishop)) {
			cloakonnpc "転職代行係#AB";
			end;
		}
		cloakonnpc "転職代行係#AB";
		mes "[祈る聖職者]";
		mes "全能の神、オーディンの前に";
		mes "彼より聡慧な者はいないし";
		mes "彼より慈悲深い者もいない。";
		next;
		mes "[祈る聖職者]";
		mes "聖職者はいつも全ての仕事に";
		mes "真面目に取り組むべきです。";
		mes "神に仕え、彼のあとを踏むことを";
		mes "怠けてはいけません。";
		next;
		mes "[祈る聖職者]";
		mes (Sex? "兄弟": "姉妹") + "殿、貴方はどれぐらい";
		mes "他人に対して誠実に";
		mes "生きてきたのですか？";
		mes "あらゆる心を受け止め";
		mes "彼らに奉仕したのですか？";
		next;
		mes "[祈る聖職者]";
		mes "我々は神に仕える者です。";
		mes "我々の行動は神の姿として";
		mes "人々の目に映ることもあります。";
		mes "だから、いつも立ち居ふるまいには";
		mes "気をつけるべきです。";
		next;
		mes "[祈る聖職者]";
		mes "聖職者は真実だけを言い";
		mes "偽りを口にしてはいけません。";
		mes "我々はロキの誘惑に応じることなく";
		mes "正義と真実に向かい合う敬虔な心を";
		mes "持っているはずです。";
		next;
		mes "[祈る聖職者]";
		mes (Sex? "兄弟": "姉妹") + "殿。";
		mes "我々は神に仕える者ですが";
		mes "本当は平凡な人間にすぎません。";
		next;
		mes "[祈る聖職者]";
		mes "知らない内に闇に魅入られ";
		mes "堕落してしまう可能性があります。";
		mes "それに気付けないこともあるでしょう。";
		next;
		mes "[祈る聖職者]";
		mes "我々はいつも初心を忘れず";
		mes "敬虔な心を維持し";
		mes "人々に善行を施し、神の規律と知恵を";
		mes "広く知らせる努力を行うべきです。";
		next;
		menu "どうすれば、それができますか？",-;
		mes "[祈る聖職者]";
		mes "いい質問です。";
		mes "幾つか方法があります。";
		next;
		mes "[祈る聖職者]";
		mes "^3131FF聖地巡礼^000000は、ご存知ですか？";
		mes "神の加護と恩寵を求め";
		mes "神聖な場所で、祈りを捧げる行為です。";
		next;
		mes "[祈る聖職者]";
		mes "聖地巡礼を行えば";
		mes "^3131FFより高貴で品位がある存在^000000として";
		mes "生まれ変わることができるでしょう。";
		next;
		mes "[祈る聖職者]";
		mes "いかがですか？";
		mes "よろしければ、私が聖地巡礼に適した";
		mes "場所をお教えしますよ。";
		next;
		if(select("聖地巡礼を行います","考えさせてください") == 2) {
			mes "[祈る聖職者]";
			mes "聖地巡礼は忌避するほど";
			mes "過酷なものではありません。";
			mes "清い心で祈るだけのことです。";
			next;
			mes "[祈る聖職者]";
			mes "気が向いたら、いつでも来てください。";
			mes "私はいつまでも、ここで貴方を";
			mes "お待ちしていますから。";
			close;
		}
		emotion 33;
		mes "[祈る聖職者]";
		mes "すばらしい心構えです。";
		mes "聖職者としての道に回帰し";
		mes "これまでの罪を告解して";
		mes "新しい身と心に備えてください。";
		next;
		mes "[祈る聖職者]";
		mes "それではまず、^0000FFウンバラ^000000という";
		mes "小さな村に向ってください。";
		mes "文明とは無縁の";
		mes "自然と共生する人々の村です。";
		next;
		mes "[祈る聖職者]";
		mes "そこで、^0000FFデイヤン神父^000000を";
		mes "探してください。";
		next;
		mes "[祈る聖職者]";
		mes "デイヤン神父を見つけたら";
		mes "^3131FFプロンテラから聖地巡礼に来ました。^000000";
		mes "と伝えるのです。";
		next;
		mes "[祈る聖職者]";
		mes "デイヤン神父は耳があまり";
		mes "よくありませんので";
		mes "大きい声ではっきり言わなければ";
		mes "なりません。";
		next;
		mes "[祈る聖職者]";
		mes "分かりましたか？";
		mes "では、知恵に富むオーディンが";
		mes "貴方に聖なる光の道標を";
		mes "与えてくださるように……。";
		set CHANGE_AB,1;
		setquest 2187;
		close;
	default:
		mes "[祈る聖職者]";
		mes "聖地巡礼は順調ですか？";
		mes "^0000FFウンバラのデイヤン神父^000000とは";
		mes "もう会われましたか？";
		next;
		mes "[祈る聖職者]";
		mes "デイヤン神父を見つけたら";
		mes "^3131FFプロンテラから聖地巡礼に来ました。^000000";
		mes "と伝えるのですよ。";
		close;
	}
}

prt_church.gat,103,90,3	script(CLOAKED)	転職代行係#AB	888,{
	cloakonnpc;
	end;
}

//============================================================
// 聖地巡礼
//------------------------------------------------------------
umbala.gat,137,227,5	script	ウンバラ族の子供	787,{
	mes "[ウンバラ族の子供]";
	mes "…………。";
	close;
}

umbala.gat,139,227,3	script	デイヤン神父	60,{
	if(Job == Job_ArchBishop) {
		mes "[デイヤン神父]";
		mes "よく来てくださいました。";
		mes "友が訪ねてきてくれることは";
		mes "とても嬉しいことです。";
		next;
		mes "[デイヤン神父]";
		mes "貴方の立派な姿を見ることができて";
		mes "私も嬉しく思いますよ。";
		mes "ほっほっほ。";
		close;
	}
	switch(CHANGE_AB) {
	case 0:
		mes "[デイヤン神父]";
		mes "ウン……バ……ウンバ？";
		close;
	case 1:
		mes "[デイヤン神父]";
		mes "ウン……バ……ウンバ？";
		next;
		mes "[ウンバラ族の子供]";
		mes "………………。";
		next;
		emotion 19;
		mes "[デイヤン神父]";
		mes "これじゃ……ないのか？";
		mes "ふむ……だったら……";
		mes "ウム……マ？　ウ……マウ……マ？";
		next;
		mes "[ウンバラ族の子供]";
		mes "………………。";
		next;
		mes "[デイヤン神父]";
		mes "これは、なんとも";
		mes "もどかしいのう……ほほほほほっ。";
		next;
		mes "[デイヤン神父]";
		mes "ほほほほほほっ。";
		mes "おほほほほっ。ふむふむ。";
		next;
		menu "デイヤン神父ですか？",-;
		emotion 1;
		mes "[デイヤン神父]";
		mes "……はい？";
		next;
		menu "デイヤン神父ではありませんか？",-;
		mes "[デイヤン神父]";
		mes "ジェ……ウニャムニャ……ル？";
		next;
		menu "デイヤン神父ですよね！",-;
		emotion 5;
		mes "[デイヤン神父]";
		mes "あ～、はいはい。";
		mes "そうです。";
		mes "私がデイヤンです。";
		mes "はじめまして、" + (Sex? "兄弟": "姉妹") + "殿。";
		next;
		mes "‐白髪混じりの老人は";
		mes "　微笑んでそう答えた‐";
		next;
		mes "[デイヤン神父]";
		mes "補聴器を忘れてしまいました。";
		mes "ほほほっ。";
		mes "私に何か御用ですか？";
		next;
		menu "プロンテラから聖地巡礼に来ました。",-;
		emotion 1;
		mes "[デイヤン神父]";
		mes "…………？";
		next;
		mes "‐話を聞くために";
		mes "　デイヤン神父が耳を近づけてきた‐";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "……ふう～。";
		mes "^FF0000プロンテラから聖地巡礼に来ました！";
		mes "プロンテラから聖地巡礼に来ました！";
		mes "プロンテラから聖地巡礼に来ました！";
		mes "プロンテラから聖地巡礼に来ました！^000000";
		next;
		emotion 5;
		mes "[デイヤン神父]";
		mes "ほお……そうですか！";
		mes "聖地巡礼でしたか。";
		mes "巡礼者が来るのは久しぶりです。";
		mes "歓迎します。" + (Sex? "兄弟": "姉妹") + "殿。";
		next;
		mes "‐神父は慈愛に満ちた微笑を見せる‐";
		next;
		mes "[デイヤン神父]";
		mes "この深い緑に包まれた村を";
		mes "よく見てください。";
		mes "向こうに巨大な樹が見えるはずです。";
		next;
		mes "[デイヤン神父]";
		mes "あの大きな樹は";
		mes "^3131FFイグドラシル^000000と言います。";
		mes "オーディンが世界を創造した後に";
		mes "植えたと言われています。";
		next;
		mes "[デイヤン神父]";
		mes "イグドラシルの根は";
		mes "3つの世界にまたがり";
		mes "3つの泉へ伸びています。";
		next;
		mes "[デイヤン神父]";
		mes "ニブルヘイムに張った根には";
		mes "フベルゲルミルの泉が。";
		mes "ミッドガルドにはミーミルの泉が。";
		next;
		mes "[デイヤン神父]";
		mes "神たちの世界、アスガルドには";
		mes "ウルドの泉があります。";
		next;
		mes "[デイヤン神父]";
		mes "特にミーミルの泉は";
		mes "世界のあらゆる知識の収蔵庫。";
		mes "我らがオーディンも片目を捧げ";
		mes "その知識を得たという話です。";
		next;
		mes "[デイヤン神父]";
		mes (Sex? "兄弟": "姉妹") + "殿。";
		mes "我々は聖なる場所で神を礼賛し";
		mes "自分の人生を振りかえることで";
		mes "世俗にまみれた体と心を";
		mes "清めることができます。";
		next;
		mes "[デイヤン神父]";
		mes "さあ、これから^0000FFフベルゲルミルの泉^000000に";
		mes "向かってください。";
		mes "場所は後で説明する時に";
		mes "地図に記しましょう。";
		next;
		mes "[デイヤン神父]";
		mes "^0000FF幹を辿り、枝の先端が泉へと延びる";
		mes "できる限り静かな場所^000000を";
		mes "探してください。";
		next;
		mes "[デイヤン神父]";
		mes "あまり先に行き過ぎてはいけません。";
		mes "行き過ぎると、違う世界へと";
		mes "迷い込んでしまいますから。";
		next;
		mes "[デイヤン神父]";
		mes "静かな枝の先についたら";
		mes "敬虔な心で、過去の罪を悔い改め";
		mes "誠実な生活を約束する祈りを";
		mes "捧げましょう。";
		next;
		mes "[デイヤン神父]";
		mes "神の恵みを礼賛し";
		mes "神の知恵を借りて正しい道を";
		mes "進めるように祈るのです。";
		next;
		mes "[デイヤン神父]";
		mes "祈りの手順は、少し複雑ですから";
		mes "後で説明しましょう。";
		mes "^3131FFもう一度、私に話しかけて";
		mes "ください。^000000";
		set CHANGE_AB,2;
		chgquest 2187,2188;
		close;
	case 2:
	case 3:
		mes "[デイヤン神父]";
		mes "この世界で一番聖なる場所の一つ。";
		mes "フベルゲルミルの泉に行って";
		mes "神に祈って下さい。";
		next;
		viewpoint 1,110,283,1,0xFF9900;
		mes "[デイヤン神父]";
		mes "この神聖な儀式が貴方の魂を";
		mes "とても美しく、明るく照らして";
		mes "くれるでしょう。";
		next;
		if(select("祈りの手順について聞く","会話をやめる") == 2) {
			mes "[デイヤン神父]";
			mes "私の祈りが貴方の人生の苦しみを";
			mes "少しでも減らせるように……";
			close;
		}
		mes "[デイヤン神父]";
		mes "祈りの際、全部で4つの道を";
		mes "歩くことになります。";
		mes "これから私が言うことを";
		mes "よく覚えて下さい。";
		next;
		mes "[デイヤン神父]";
		mes "一つ目は^3131FF瞑想の道^000000。";
		mes "体と心を敬虔にし";
		mes "祈りの準備を行います。";
		next;
		mes "[デイヤン神父]";
		mes "全ての祈りの始まりになる";
		mes "祝福と共に";
		mes "頭を下げ、目を閉じ";
		mes "心を無心にするのです。";
		next;
		mes "[デイヤン神父]";
		mes "二つ目は^3131FF苦しみの道^000000。";
		mes "今までの罪を告白し";
		mes "神への赦しを請います。";
		next;
		mes "[デイヤン神父]";
		mes "苦しみを恐れないで下さい。";
		mes "それは必要なものなのです。";
		mes "闇と傷を克服することで罪を清算し";
		mes "真実の道に入る最初の一歩に";
		mes "なるのですから。";
		next;
		mes "[デイヤン神父]";
		mes "三つ目は^3131FF歓喜の道^000000。";
		mes "全ての生命が自らの罪に苦しむ者を";
		mes "慰めてくれます。";
		next;
		mes "[デイヤン神父]";
		mes "また試練を克服した存在には";
		mes "祝福を与えてくれるでしょう。";
		mes "これを洗礼儀式と言います。";
		next;
		mes "[デイヤン神父]";
		mes "貴方は洗礼に感謝し";
		mes "聖水を飲みます。";
		mes "^0000FF聖水^000000を^FF00001個^000000、持参してください。";
		next;
		mes "[デイヤン神父]";
		mes "最後は^3131FF光の道^000000。";
		mes "この世のすべての生命から";
		mes "祝福された貴方は";
		mes "全ての罪から解放された";
		mes "自由な身となるでしょう。";
		next;
		mes "[デイヤン神父]";
		mes "解放された者は全ての生命と共に";
		mes "嬉しさの賛歌を歌います。";
		next;
		mes "[デイヤン神父]";
		mes "祈りが全部終わったら";
		mes "静かにその場から立ち去りましょう。";
		next;
		mes "[デイヤン神父]";
		mes "さあ、心の準備ができましたか？";
		mes "祈りが終わったら";
		mes "温かいお茶でも飲みながら";
		mes "楽しい話をしましょう。";
		if(CHANGE_AB == 2) {
			set CHANGE_AB,3;
			chgquest 2188,104260;
		}
		close;
	case 4:
		mes "[デイヤン神父]";
		mes "おかえりなさい。";
		mes "とても素晴らしい祈りを";
		mes "捧げたようですね。";
		next;
		menu "祈りの感想を伝える",-;
		mes "[デイヤン神父]";
		mes "ほほほっ。";
		mes "祈りは自分自身に対し";
		mes "信頼と勇気を与えてくれます。";
		next;
		mes "[デイヤン神父]";
		mes "平穏な心から生み出される微笑みは";
		mes "他人の警戒心を解き、会話も導いて";
		mes "くれることでしょう。";
		mes "できる限り、大勢の人を励まし";
		mes "愛を分けてあげることが大切です。";
		next;
		menu "ありがとうございました",-;
		mes "[デイヤン神父]";
		mes (Sex? "兄弟": "姉妹") + "殿。";
		mes "貴方に1つお願いがあります。";
		next;
		mes "[デイヤン神父]";
		mes "シュバルツバルドの";
		mes "^0000FFフィゲル^000000という村に";
		mes "^0000FFシスター・アンジェ^000000という";
		mes "聖職者がいます。";
		next;
		mes "[デイヤン神父]";
		mes "彼女はいつも、この世で苦しんでいる";
		mes "人々の為に祈りを捧げている";
		mes "素晴らしい聖職者です。";
		next;
		mes "[デイヤン神父]";
		mes "ですが、フィゲルで最後に会った時";
		mes "どこか疲れたような、悲しい顔を";
		mes "していました。";
		next;
		mes "[デイヤン神父]";
		mes "彼女に、イグドラシルへの巡礼を";
		mes "進めてもらえませんか？";
		mes "長時間の祈りによって";
		mes "体調を崩しているのではないかと";
		mes "心配しているのです。";
		next;
		mes "[デイヤン神父]";
		mes "イグドラシルの澄んだ空気が";
		mes "彼女を癒やしてくれるでしょう。";
		next;
		menu "わかりました",-;
		mes "[デイヤン神父]";
		mes "本当にありがとうございます。";
		mes (Sex? "兄弟": "姉妹") + "殿もお祈りが必要になった時は";
		mes "いつでもここにいらしてください。";
		next;
		mes "[デイヤン神父]";
		mes "友が訪ねてきてくれることは";
		mes "とても楽しいことですから。";
		set CHANGE_AB,5;
		chgquest 104265,2189;
		close;
	default:
		mes "[デイヤン神父]";
		mes "^0000FFフィゲルのシスター・アンジェ^000000は";
		mes "元気でしたか？";
		close;
	}
}

yggdrasil01.gat,226,48,0	script	#聖地巡礼yggdrasil01	844,14,14,{
	switch(CHANGE_AB) {
	default:
		mes "‐静かな場所だ。";
		mes "　心が洗われるような気持ちになる‐";
		next;
		mes "‐思わず何かに対して";
		mes "　祈りを捧げたくなった‐";
		close;
	case 3:
		misceffect 231;
		mes "‐静かに生命力が溢れており";
		mes "　神聖さを感じる。";
		mes "　ここなら祈りを捧げるのに";
		mes "　ちょうど良さそうだ‐";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "まずは、ひざまずいて……";
		mes "祈りを始めよう……";
		next;
		mes "‐デイヤン神父から教えられた";
		mes "　手順を思い出してみよう‐";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "一つ目は、何の道だっけ？";
		next;
		if(select("沈黙の道","苦痛の道","瞑想の道") != 3) {
			emotion 20,"";
			mes "[" + strcharinfo(0) + "]";
			mes (@menu == 1? "沈黙の道": "苦痛の道") + "……？";
			mes "これではなかった気がする……。";
			close;
		}
		mes "[" + strcharinfo(0) + "]";
		mes "たしか瞑想の道だったはず。";
		next;
		mes "^3131FF[デイヤン神父]";
		mes "一つ目は瞑想の道。";
		mes "体と心を敬虔にし";
		mes "祈りの準備を行います。^000000";
		next;
		mes "^3131FF[デイヤン神父]";
		mes "全ての祈りの始まりになる";
		mes "祝福と共に";
		mes "頭を下げ、目を閉じ";
		mes "心を無心にするのです。^000000";
		next;
		misceffect 42,"";
		mes "‐貴方は深呼吸をすると";
		mes "　ゆっくり目を閉じた‐";
		next;
		mes "‐静寂の中で聞こえてくる祝福の音で";
		mes "　心が穏やかになるのを感じた。";
		mes "　雑念を振り落とし、できるかぎり";
		mes "　静寂を維持する‐";
		next;
		mes "…………";
		next;
		mes "…………";
		mes "………";
		next;
		mes "…………";
		mes "………";
		mes "……";
		next;
		mes "…………";
		mes "………";
		mes "……";
		mes "…";
		next;
		mes "^3131FF[デイヤン神父]";
		mes "二つ目は苦しみの道。";
		mes "今までの罪を告白し";
		mes "神への赦しを請います。^000000";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "今までの生きてきた中で";
		mes "どのような過ちを犯しただろう？";
		mes "告解を通じて、神に赦しを";
		mes "請うとしよう。";
		next;
		input '@str$;
		mes "[" + strcharinfo(0) + "]";
		mes "全知全能の神、オーディンに";
		mes "私の罪を告白します。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "^3131FF" + '@str$ + "^000000";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "慈悲深いオーディンよ。";
		mes "聖職者の任務をないがしろにした";
		mes "罪深い私をどうかお赦しください。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "神の英知で、この愚かな聖職者を";
		mes "正しい道へ導いてください。";
		next;
		mes "‐告解を繰り返し";
		mes "　静かに祈りを続けた‐";
		next;
		mes "…………";
		next;
		mes "…………";
		mes "………";
		next;
		mes "…………";
		mes "………";
		mes "……";
		next;
		mes "…………";
		mes "………";
		mes "……";
		mes "…";
		next;
		mes "^3131FF[デイヤン神父]";
		mes "三つ目は歓喜の道。";
		mes "全ての生命が自らの罪に苦しむ者を";
		mes "慰めてくれます。^000000";
		next;
		mes "^3131FF[デイヤン神父]";
		mes "また試練を克服した存在には";
		mes "祝福を与えてくれるでしょう。";
		mes "これを洗礼儀式と言います。^000000";
		next;
		mes "^3131FF[デイヤン神父]";
		mes "貴方は洗礼に感謝し";
		mes "聖水を飲みます。^000000";
		next;
		if(countitem(523) < 1) {
			emotion 0,"";
			mes "[" + strcharinfo(0) + "]";
			mes "あっ、聖水を持って来ていない！";
			close;
		}
		misceffect 86,"";
		mes "‐ゆっくりと聖水に口を付けた‐";
		next;
		misceffect 78,"";
		mes "…………";
		next;
		mes "…………";
		mes "………";
		next;
		mes "…………";
		mes "………";
		mes "……";
		next;
		mes "…………";
		mes "………";
		mes "……";
		mes "…";
		next;
		mes "^3131FF[デイヤン神父]";
		mes "最後は光の道。";
		mes "この世のすべての生命から";
		mes "祝福された貴方は";
		mes "全ての罪から解放された";
		mes "自由な身となるでしょう。^000000";
		next;
		mes "^3131FF[デイヤン神父]";
		mes "解放された者は全ての生命と共に";
		mes "嬉しさの賛歌を歌います。^000000";
		next;
		mes "‐ゆっくり深呼吸すると";
		mes "　高らかに賛歌を歌い始めた‐";
		next;
		mes "‐澄んだ泉に聖なる和音が響き";
		mes "　更に涼しい滝の音が合唱に加わる‐";
		next;
		misceffect 75,"";
		mes "[" + strcharinfo(0) + "]";
		mes "ヘイムダルの子孫達はみな";
		mes "大きい樹の下で集まった。";
		next;
		misceffect 75,"";
		mes "[" + strcharinfo(0) + "]";
		mes "木の上の大きい鳥が";
		mes "私に世界の知恵を教えてくれた。";
		mes "木の下の大きい狼は";
		mes "私を世界の脅威から譲ってくれた。";
		next;
		misceffect 75,"";
		mes "[" + strcharinfo(0) + "]";
		mes "ヴァルハラの主は立ち上がり";
		mes "世界が嬉しい歓声をあげる。";
		next;
		misceffect 75,"";
		mes "[" + strcharinfo(0) + "]";
		mes "光の父、知恵の詩人よ";
		mes "私の為に歌いたまえ。";
		mes "輝く黄金の杯の主よ";
		mes "私の為に聖なる予言を与えたまえ。";
		next;
		misceffect 42,"";
		misceffect 77,"";
		mes "‐歌い終えると信仰心が満ち";
		mes "　何かに守られているような";
		mes "　心強い気持ちになった‐";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "さて……祈りも済んだから";
		mes "デイヤン神父の元に戻ろう。";
		set CHANGE_AB,4;
		chgquest 104260,104265;
		close2;
		warp "umbala.gat",138,219;
		end;
	case 4:
		mes "[" + strcharinfo(0) + "]";
		mes "さて……祈りも済んだから";
		mes "デイヤン神父の元に戻ろう。";
		close2;
		warp "umbala.gat",138,219;
		end;
	}
OnTouch:
	if(CHANGE_AB == 3 || CHANGE_AB == 4) {
		misceffect 231;
	}
	end;
}

//============================================================
// ヴァルキリーの悪夢
//------------------------------------------------------------
hu_in01.gat,205,204,7	script	祈るシスター	79,{
	if(CHANGE_AB == 5) {
		mes "[祈るシスター]";
		mes "シスター・アンジェをお探しですか？";
		mes "彼女なら^0000FF教会の隣にある船着場^000000で";
		mes "祈っていると思いますわ。";
		close;
	}
	mes "‐静かな教会の中に佇む";
	mes "　シスターが見える。";
	mes "　目を閉じて祈っているようだ‐";
	next;
	mes "‐邪魔をしないように";
	mes "　静かにその場から立ち去った‐";
	close;
}

hugel.gat,193,103,3	script	シスター・アンジェ	79,{
	if(Job == Job_ArchBishop) {
		mes "[シスター・アンジェ]";
		mes "とても晴れやかな心地です。";
		mes "貴方が悪魔たちからヴァルキリーを";
		mes "救い出してくれたのですね？";
		next;
		mes "[シスター・アンジェ]";
		mes "これで私も悪夢に悩まされることは";
		mes "なさそうです。";
		mes "本当にありがとうございます！";
		close;
	}
	switch(CHANGE_AB) {
	default:
		mes "[シスター・アンジェ]";
		mes "オーディン神殿に向かわれるのでしたら";
		mes "十分に注意してください。";
		mes "悪魔たちによって";
		mes "神殿は占拠されている状態です。";
		next;
		mes "[シスター・アンジェ]";
		mes "できることなら悪魔たちを";
		mes "追い払いたいのに……。";
		mes "私にできることは";
		mes "ここからオーディンの神殿に向って";
		mes "祈ることだけ……。";
		close;
	case 5:
		mes "[" + strcharinfo(0) + "]";
		mes "あの……すみません。";
		mes "シスター・アンジェですか？";
		next;
		emotion 1;
		mes "[シスター・アンジェ]";
		mes "はい、私がアンジェですが……";
		mes "私に何か御用でしょうか？";
		next;
		mes "‐ウンバラのデイヤン神父から";
		mes "　頼まれて来たことを伝えた‐";
		next;
		emotion 0;
		mes "[シスター・アンジェ]";
		mes "あら、デイヤン神父から……。";
		mes "デイヤン神父はお元気でしたか？";
		next;
		mes "[シスター・アンジェ]";
		mes "もうお歳ですのに";
		mes "子供みたいに純真な方ですよね。";
		mes "ふふっ。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "デイヤン神父は貴方のことを";
		mes "心配していましたよ。";
		next;
		mes "[シスター・アンジェ]";
		mes "あら、まあ……。";
		mes "本当に親切な方ですね。";
		mes "デイヤン神父も、" + (Sex? "兄弟": "姉妹") + "殿も。";
		next;
		mes "[シスター・アンジェ]";
		mes "ただ、ご心配には及びません。";
		mes "悪い夢にうなされて";
		mes "少しばかり疲れただけですわ。";
		next;
		menu "悪い夢？",-;
		emotion 54;
		mes "[シスター・アンジェ]";
		mes "それが……。";
		mes "実は、私がここに赴任したその日から";
		mes "悪い夢を見始めたのです。";
		next;
		mes "[シスター・アンジェ]";
		mes "最初の頃は、ヴァルキリーが";
		mes "暗闇の中で悲しんでいる夢でした。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "ヴァルキリー？";
		next;
		mes "[シスター・アンジェ]";
		mes "はい。";
		mes "彼女は暗い闇の中で座り込み";
		mes "涙を流していました。";
		mes "まるで、羽を切り落とされた";
		mes "鳥のように……。";
		next;
		mes "[シスター・アンジェ]";
		mes "しかし、時間が経つにつれ";
		mes "夢は酷くなっていったのです。";
		mes "今ではヴァルキリーが太い鎖に縛られ";
		mes "最後には、悪魔たちにバラバラに";
		mes "されてしまうのです。";
		next;
		mes "[シスター・アンジェ]";
		mes "あまりに酷い夢で……";
		mes "私は息すらまともにできず";
		mes "うなされた挙句に目が覚めます。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "ヴァルキリーの死を見つめるなんて";
		mes "とてもつらい夢ですね。";
		next;
		mes "[シスター・アンジェ]";
		mes "ただの悪夢なのでしょうか？";
		mes "もしかしたら、何かを暗示している";
		mes "のではないかと思うのです。";
		next;
		mes "[シスター・アンジェ]";
		mes "私は心を静める為に";
		mes "オーディン神殿に行き";
		mes "ミサを捧げようとしたのですが……";
		next;
		mes "[シスター・アンジェ]";
		mes "神殿はすでに悪魔の巣窟に";
		mes "なってしまっていて";
		mes "引き返すしかありませんでした。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "……夢はオーディン神殿の悪魔達と";
		mes "関係があるのではないでしょうか？";
		next;
		mes "[シスター・アンジェ]";
		mes "……そうかもしれません。";
		mes "しかし、私にできることは";
		mes "ここからオーディンの神殿に向って";
		mes "祈ることだけ……。";
		next;
		if(select("私が調べてみましょう","一緒に祈りを捧げましょう") == 2) {
			mes "[シスター・アンジェ]";
			mes "ありがとうございます。";
			mes "私も悪夢に負けないよう";
			mes "今以上に頑張って";
			mes "祈りを捧げることにします。";
			close;
		}
		emotion 0;
		mes "[シスター・アンジェ]";
		mes "ええっ？";
		mes "ですが、神殿は本当に危険なのです！";
		next;
		menu "私を信じてください",-;
		mes "[シスター・アンジェ]";
		mes "なんという心強いお言葉。";
		mes "貴方を引き止めることは";
		mes "できないようですね……。";
		next;
		mes "[シスター・アンジェ]";
		mes "でしたら私が";
		mes "教会の所有する船を使って";
		mes "オーディン神殿までご案内いたします。";
		next;
		mes "[シスター・アンジェ]";
		mes "きっと貴方を神殿に案内することが";
		mes "私に課せられた使命なのでしょう。";
		next;
		mes "[シスター・アンジェ]";
		mes "さあ、準備ができましたら";
		mes "^0000FF私に声を掛けてください。^000000";
		mes "オーディン神殿までに向かいましょう。";
		set CHANGE_AB,6;
		chgquest 2189,2190;
		close;
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		mes "[シスター・アンジェ]";
		mes "オーディン神殿に向かう";
		mes "準備はできましたか？";
		next;
		if(countitem(523) < 1) {
			mes "[シスター・アンジェ]";
			mes "神殿には悪魔が徘徊していて危険です。";
			mes "^FF0000必ず聖水を持って行ってください。^000000";
			next;
		}
		if(select("準備はできています","ちょっと待ってください") == 2) {
			mes "[シスター・アンジェ]";
			mes "準備ができましたら";
			mes "声を掛けてください。";
			close;
		}
		mes "[シスター・アンジェ]";
		mes "わかりました。";
		if(CHANGE_AB > 6) {
			mes "前回はオーディン神殿に向かう途中";
			mes "貴方の姿が船から消えてしまい";
			mes "心配しておりましたが、";
			mes "ご無事なようで安心しました。";
			next;
			mes "[シスター・アンジェ]";
		}
		mes "さあ、参りましょう。";
		next;
		mes "‐シスター・アンジェと共に船に乗り";
		mes "　オーディン神殿に向かう途中";
		mes "　突然、頭の中に声が聞こえてきた‐";
		next;
		mes "‐声に集中しようとした瞬間";
		mes "　視界が真っ白になり";
		mes "　意識を失ってしまった‐";
		close2;
		warp "job3_arch01.gat",29,29;
		end;
	case 11:
		mes "[シスター・アンジェ]";
		mes "とても晴れやかな心地です。";
		mes "貴方が悪魔たちからヴァルキリーを";
		mes "救い出してくれたのですね？";
		next;
		mes "[シスター・アンジェ]";
		mes "これで私も悪夢に悩まされることは";
		mes "なさそうです。";
		mes "本当にありがとうございます！";
		next;
		if(select("ヴァルキリーのもとへ向かう","会話をやめる") == 2) {
			mes "[シスター・アンジェ]";
			mes "ヴァルキリーのもとに向かう際は";
			mes "私に声をかけてくださいね。";
			close;
		}
		mes "[シスター・アンジェ]";
		mes "わかりました。";
		mes "さあ、参りましょう。";
		close2;
		warp "job3_arch02.gat",278,235;
		end;
	}
}

job3_arch01.gat,29,34,3	script	ヴァルキリー	403,{
	switch(CHANGE_AB) {
	default:	// 未調査
		warp "hugel.gat",191,103;
		end;
	case 6:
		cutin "3rd_ab_anghilde01",1;
		mes "[ヴァルキリー]";
		mes "天上には勝利の角笛が";
		mes "鳴り響いているのに";
		mes "飛ばない鳥は大地を這い";
		mes "ついに滅びてしまうのか……。";
		mes "ああ、痛恨の極みだ！";
		next;
		emotion 0;
		mes "‐ヴァルキリーは、こちらに気づくと";
		mes "　怒りの形相で睨みつけてきた‐";
		next;
		cutin "3rd_ab_anghilde03",1;
		mes "[ヴァルキリー]";
		mes "必滅の苦痛の中で生きている";
		mes "ヘイムダルの子孫ではないか。";
		mes "こんなところに何の用だ？";
		next;
		mes "[ヴァルキリー]";
		mes "このアングヒルデの";
		mes "悲惨な運命をあざける為に来たのか？";
		next;
		cutin "3rd_ab_anghilde01",255;
		mes "[" + strcharinfo(0) + "]";
		mes "まさか！";
		mes "私は貴方を探していたのです。";
		next;
		cutin "3rd_ab_anghilde01",1;
		emotion 1;
		mes "[アングヒルデ]";
		mes "……私を探していただと？";
		mes "私がミッドガルドに留まっている";
		mes "ことは事実だが";
		mes "人間とは交わることのない運命だ。";
		next;
		mes "[アングヒルデ]";
		mes "そうか、貴様の狙いは";
		mes "ヴァルハラへ辿り着くことなのだな？";
		mes "しかし、それは叶わぬ望みだ。";
		next;
		mes "[アングヒルデ]";
		mes "私はアスガルドにて重罰を受け";
		mes "追放された身。";
		next;
		mes "[アングヒルデ]";
		mes "私の今の任務は、この小さな島を";
		mes "護ることであり";
		mes "あの方の元に人間を";
		mes "導くことではない。";
		next;
		cutin "3rd_ab_anghilde01",255;
		mes "[" + strcharinfo(0) + "]";
		mes "そうではありません。";
		mes "貴方を助けるために";
		mes "私はここに来たのです。";
		next;
		cutin "3rd_ab_anghilde01",1;
		mes "[アングヒルデ]";
		mes "ははっ！";
		mes "人間ごときが、この私を助けるだと？";
		next;
		mes "[アングヒルデ]";
		mes "…………………………";
		next;
		mes "‐ヴァルキリーは急に黙ると";
		mes "　静かにこちらの様子を見ている‐";
		next;
		mes "[アングヒルデ]";
		mes "人間よ、答えろ。";
		mes "本当に私を助ける為に";
		mes "ここに来たと言うのか？";
		next;
		if(select("はい","いいえ") == 2) {
			cutin "3rd_ab_anghilde03",1;
			mes "[ヴァルキリー]";
			mes "私は子供の悪戯を許すほど";
			mes "寛大ではないぞ！";
			close2;
			cutin "3rd_ab_anghilde01",255;
			warp "hugel.gat",191,103;
			end;
		}
		mes "[アングヒルデ]";
		mes "……そうか。";
		mes "これ以上身を引く場所も無く";
		mes "立ち向かう力もない以上";
		mes "貴様に頼るのも悪くない。";
		next;
		mes "[アングヒルデ]";
		mes "私は本来、オーディン様の命令に従い";
		mes "ヴァルハラに引導する戦士達を";
		mes "見守るヴァルキリーだった。";
		next;
		mes "[アングヒルデ]";
		mes "しかし、些少な過ちで";
		mes "オーディン様の狼である";
		mes "フレキを興奮させてしまった。";
		next;
		mes "[アングヒルデ]";
		mes "その罰として、アスガルドを";
		mes "追放され、この島を護るという";
		mes "命令を受けたのだ。";
		next;
		mes "[アングヒルデ]";
		mes "不本意ではあったが";
		mes "この島はオーディン様や他の神々の";
		mes "伝説が残る貴重な場所。";
		next;
		mes "[アングヒルデ]";
		mes "私は遺跡を護りつつ";
		mes "聖地としての価値を高めることに";
		mes "尽力した。";
		next;
		cutin "3rd_ab_anghilde03",1;
		mes "[ヴァルキリー]";
		mes "……だが、ある日";
		mes "この島に悪魔達が現れた。";
		next;
		mes "[アングヒルデ]";
		mes "私は全力で悪魔達に戦いを挑んだが";
		mes "次々と現れる悪魔の軍勢に敗れ";
		mes "この場所に封印されてしまったのだ。";
		next;
		mes "[アングヒルデ]";
		mes "次第に、聖なる神殿は悪魔達によって";
		mes "汚されていくのだろう。";
		mes "ああ……私はいつまでこんな";
		mes "不名誉な運命に翻弄されるのか！";
		next;
		cutin "3rd_ab_anghilde01",1;
		mes "[アングヒルデ]";
		mes "……ヘイムダルの子孫よ。";
		mes "貴様の名前はなんと言うのか？";
		next;
		cutin "3rd_ab_anghilde01",255;
		mes "[" + strcharinfo(0) + "]";
		mes strcharinfo(0) + " です。";
		next;
		cutin "3rd_ab_anghilde01",1;
		mes "[アングヒルデ]";
		mes strcharinfo(0) + "よ。";
		mes "ヴァルキリーとしての恥を忍んで";
		mes "助けを求める。";
		next;
		mes "[アングヒルデ]";
		mes "私が力を封印されている以上";
		mes "天上にこの状態を報告し";
		mes "援軍を要請しなければならない。";
		next;
		menu "どうすればいいのですか？",-;
		mes "[アングヒルデ]";
		mes "^0000FF神殿の一番高い所で";
		mes "黄金の角笛を吹けば^000000";
		mes "天上のヴァルキリー達と連絡が取れる。";
		next;
		mes "[アングヒルデ]";
		mes "しかし、角笛も2つに破壊されて";
		mes "どこかに破棄されてしまった。";
		next;
		mes "[アングヒルデ]";
		mes "これから、お前を神殿に送る。";
		mes "まずは、^FF0000壊れた角笛の欠片^000000を";
		mes "見つけるのだ。";
		next;
		mes "[アングヒルデ]";
		mes "2つの欠片を見つけたら";
		mes "神殿の一番高い場所に行け。";
		mes "その後のことは、私に任せろ。";
		next;
		mes "[アングヒルデ]";
		mes "準備ができたら";
		mes "再度、話し掛けてくれ。";
		set CHANGE_AB,7;
		chgquest 2190,104270;
		close2;
		cutin "3rd_ab_anghilde01",255;
		end;
	case 7:
		cutin "3rd_ab_anghilde01",1;
		mes "[アングヒルデ]";
		mes strcharinfo(0) + "よ。";
		mes "これより神殿に送るが";
		mes "準備はできているか？";
		next;
		if(select("準備はできています","まだ待ってください") == 2) {
			mes "[アングヒルデ]";
			mes "準備ができたら";
			mes "再度、話し掛けてくれ。";
			close2;
			cutin "3rd_ab_anghilde01",255;
			end;
		}
		mes "[アングヒルデ]";
		mes "では、頼んだぞ！";
		set CHANGE_AB,8;
		chgquest 104270,2191;
		close2;
		cutin "3rd_ab_anghilde01",255;
		warp "job3_arch02.gat",121,50;
		end;
	case 8:
	case 9:
	case 10:
		cutin "3rd_ab_anghilde01",1;
		mes "[アングヒルデ]";
		mes "大丈夫か、人間よ。";
		mes "予想どおり、簡単ではないが";
		mes "再挑戦するか？";
		next;
		switch(select("再挑戦します","まだ待ってください","フィゲルに戻りたい")) {
		case 1:
			mes "[アングヒルデ]";
			mes "では、頼んだぞ！";
			set CHANGE_AB,8;
			close2;
			cutin "3rd_ab_anghilde01",255;
			warp "job3_arch02.gat",121,50;
			end;
		case 2:
			mes "[アングヒルデ]";
			mes "準備ができたら";
			mes "再度、話し掛けてくれ。";
			close2;
			cutin "3rd_ab_anghilde01",255;
			end;
		case 3:
			mes "[アングヒルデ]";
			mes "準備に戻るのか？";
			mes "それなら私は待っていよう。";
			close2;
			cutin "3rd_ab_anghilde01",255;
			warp "hugel.gat",191,103;
			end;
		}
	}
}

job3_arch02.gat,122,48,0	script	#arch02out	45,1,1,{
	if(CHANGE_AB >= 8 && CHANGE_AB < 11) {
		warp "job3_arch01.gat",29,29;
		end;
	}
	warp "hugel.gat",191,103;
	end;
}

job3_arch02.gat,121,50,0	script	#コンパス_1_job3_arch02	139,1,1,{
OnTouch:
	switch(CHANGE_AB) {
	case 8:
		viewpoint 1,113,327,0,0xFF0000;
		viewpoint 1,273,235,1,0x00FFFF;
		break;
	case 9:
		viewpoint 1,244,46,0,0xFF0000;
		viewpoint 1,273,235,1,0x00FFFF;
		break;
	case 10:
		viewpoint 1,273,235,1,0x00FFFF;
		break;
	}
	end;
}

job3_arch02.gat,113,327,5	script	ヴァルキリーの悪夢	403,{
	switch(CHANGE_AB) {
	default:
		mes "‐目の前に苦悶の表情を浮かべ";
		mes "　武器を構えるヴァルキリーの";
		mes "　姿が見える‐";
		next;
		cutin "3rd_ab_anghilde03",1;
		mes "[ヴァルキリーの悪夢]";
		mes "今すぐここから立ち去れ！";
		mes "汚らわしい悪魔どもめ！";
		mes "私の刃で、その身をバラバラに";
		mes "切り裂かれたいのか！";
		next;
		cutin "3rd_ab_anghilde03",255;
		mes "‐こちらの姿が見えていないらしい。";
		mes "　どうやら正気を失っているようだ‐";
		close;
	case 8:
		mes "‐目の前に苦悶の表情を浮かべ";
		mes "　武器を構えるヴァルキリーの";
		mes "　姿が見える‐";
		next;
		cutin "3rd_ab_anghilde03",1;
		mes "[ヴァルキリーの悪夢]";
		mes "今すぐここから立ち去れ！";
		mes "汚らわしい悪魔どもめ！";
		mes "私の刃で、その身をバラバラに";
		mes "切り裂かれたいのか！";
		next;
		mes "‐こちらの姿が見えていないらしい。";
		mes "　どうやら正気を失っているようだ‐";
		next;
		mes "‐なんとかなだめて";
		mes "　話を聞きたいところだが……‐";
		next;
		if(select("静かに名乗る","荒々しく名乗る") == 2) {
			cutin "3rd_ab_anghilde03",255;
			mes "‐荒々しく自らの名前を名乗った‐";
			next;
			cutin "3rd_ab_anghilde03",1;
			emotion 6;
			mes "[ヴァルキリーの悪夢]";
			mes "黙れ、悪魔め！";
			mes "貴様の名前など知ったことか！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　武器を振り回して暴れ始めた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐話を聞いてもらうのは難しそうだ。";
			mes "　しばらくしてから";
			mes "　もう一度話し掛けてみよう‐";
			close;
		}
		mes "‐静かに自らの名前を名乗った‐";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes strcharinfo(0) + "だと……。";
		mes "その名前はどこかで聞いたことが……。";
		mes "ぐっ……思い出せん……。";
		next;
		if(select("今すぐ使命を思い出してください","まずは落ち着いてください") == 1) {
			cutin "3rd_ab_anghilde01",1;
			emotion 0;
			mes "[ヴァルキリーの悪夢]";
			mes "そうだ！";
			mes "私の使命は、聖域を汚す悪魔どもを";
			mes "排除することだ！";
			next;
			cutin "3rd_ab_anghilde03",1;
			mes "[ヴァルキリーの悪夢]";
			mes "まずは貴様から排除してやろう！";
			mes "この聖域に侵入したことを";
			mes "後悔するがいい！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　武器を振り回して暴れ始めた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐話を聞いてもらうのは難しそうだ。";
			mes "　しばらくしてから";
			mes "　もう一度話し掛けてみよう‐";
			close;
		}
		cutin "3rd_ab_anghilde01",1;
		mes "[ヴァルキリーの悪夢]";
		mes "私は、この聖域を守護する者……。";
		mes "オーディン様の命を受けた";
		mes "栄光あるヴァルキリー……。";
		next;
		mes "‐ヴァルキリーは";
		mes "　少し落ち着いたように見える‐";
		next;
		if(select("素早く一気に近づく","ゆっくりと一歩近づく") == 1) {
			cutin "3rd_ab_anghilde03",1;
			emotion 0;
			mes "[ヴァルキリーの悪夢]";
			mes "近づくな！";
			mes "私を油断させようとしたのか！";
			mes "残念だが、そんな手は通用しないぞ！";
			next;
			mes "[ヴァルキリーの悪夢]";
			mes "さあ、近づいてみろ！";
			mes "その身を真っ二つにしてくれる！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　武器を振り回して暴れ始めた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐話を聞いてもらうのは難しそうだ。";
			mes "　しばらくしてから";
			mes "　もう一度話し掛けてみよう‐";
			close;
		}
		mes "[ヴァルキリーの悪夢]";
		mes "おお……!?";
		mes "その姿は、悪魔ではないのか？";
		mes "いや、人間に化けた悪魔かもしれん！";
		next;
		if(select("穏やかに賛美歌を歌う","厳しく諭す") == 2) {
			mes "‐ヴァルキリーを厳しく諭した‐";
			next;
			cutin "3rd_ab_anghilde03",1;
			emotion 0;
			mes "[ヴァルキリーの悪夢]";
			mes "貴様は何様のつもりだ！";
			mes "私の苦悩を知らずに";
			mes "説教するつもりか！";
			next;
			mes "[ヴァルキリーの悪夢]";
			mes "私を惑わす悪魔め！";
			mes "今すぐに、私の前から消え失せろ！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　武器を振り回して暴れ始めた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐話を聞いてもらうのは難しそうだ。";
			mes "　しばらくしてから";
			mes "　もう一度話し掛けてみよう‐";
			close;
		}
		cutin "3rd_ab_anghilde01",255;
		misceffect 75,"";
		mes "‐穏やかに賛美歌を歌い上げた‐";
		next;
		cutin "3rd_ab_anghilde02",1;
		mes "[ヴァルキリーの悪夢]";
		mes "おお……。";
		mes "これは、神を讃える歌！";
		mes "なんと心地よい響きなのだ！";
		next;
		misceffect 77;
		mes "[ヴァルキリーの悪夢]";
		mes "ああ……。";
		mes "聖なる歌声によって";
		mes "私の苦悩が消えていくようだ……。";
		next;
		cutin "3rd_ab_anghilde01",1;
		mes "[ヴァルキリーの悪夢]";
		mes "……人間よ、貴様のおかげで";
		mes "苦悩から開放され";
		mes "正気を取り戻すことができた。";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes "しかし、それも一時的なことだ……。";
		mes "すぐにまた、私は苦悩に囚われて";
		mes "しまうだろう……くっ……！";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes "私が正気を保っている間に";
		mes "これを渡しておく。";
		mes "壊れた角笛の欠片だ……。";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes "これだけでは、役に立たない。";
		mes "もう^FF00001つの欠片^000000を探すのだ……。";
		mes "私を正気に戻してくれた貴様なら";
		mes "探し出すことができるはず。";
		next;
		if(checkitemblank() < 1) {
			mes "[ヴァルキリーの悪夢]";
			mes "荷物が多くて";
			mes "壊れた角笛の欠片を持てないようだな。";
			mes "所持品の種類数を減らしてから";
			mes "また来てくれ。";
			close2;
			cutin "3rd_ab_anghilde01",255;
			end;
		}
		mes "[ヴァルキリーの悪夢]";
		mes "頼んだぞ……。";
		mes "さあ、もう行ってくれ……。";
		mes "今更だが、このような情けない姿を";
		mes "人に見られたくはない……。";
		set CHANGE_AB,9;
		chgquest 2191,104275;
		getitem 6154,1;		// 壊れた角笛の欠片
		viewpoint 1,244,46,0,0xFF0000;
		close2;
		cutin "3rd_ab_anghilde01",255;
		end;
	case 9:
	case 10:
	case 11:
		cutin "3rd_ab_anghilde01",1;
		mes "[ヴァルキリーの悪夢]";
		mes "壊れた角笛の欠片を";
		mes "もう1つ探すのだ……。";
		mes "私を正気に戻してくれた貴様なら";
		mes "探し出すことができるはず。";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes "頼んだぞ……。";
		mes "さあ、もう行ってくれ……。";
		mes "今更だが、このような情けない姿を";
		mes "人に見られたくはない……。";
		close2;
		cutin "3rd_ab_anghilde01",255;
		end;
	}
}

job3_arch02.gat,244,46,5	script	ヴァルキリーの悪夢	403,{
	switch(CHANGE_AB) {
	default:
		mes "‐武器を振り回し暴れている";
		mes "　ヴァルキリーがいる‐";
		next;
		cutin "3rd_ab_anghilde03",1;
		mes "[ヴァルキリーの悪夢]";
		mes "グゥゥ！";
		mes "聖域を汚す悪魔どもめ！";
		mes "私が怒りの鉄槌で";
		mes "全て打ち砕いてやる！";
		next;
		cutin "3rd_ab_anghilde03",255;
		mes "‐怒りの形相でこちらを";
		mes "　睨みつけている。";
		mes "　完全に正気を失っているようだ‐";
		close;
	case 8:
		mes "‐武器を振り回し暴れている";
		mes "　ヴァルキリーがいる‐";
		next;
		mes "‐声をかけようとするが";
		mes "　まったく近づくことができない‐";
		next;
		mes "‐いったん別の場所を探索した方が";
		mes "　良さそうだ‐";
		close;
	case 9:
		mes "‐武器を振り回し暴れている";
		mes "　ヴァルキリーがいる‐";
		next;
		cutin "3rd_ab_anghilde03",1;
		mes "[ヴァルキリーの悪夢]";
		mes "グゥゥ！";
		mes "聖域を汚す悪魔どもめ！";
		mes "私が怒りの鉄槌で";
		mes "全て打ち砕いてやる！";
		next;
		mes "‐怒りの形相でこちらを";
		mes "　睨みつけている。";
		mes "　完全に正気を失っているようだ‐";
		next;
		switch(select("鋭く睨み返す","強い語気で告解を促す","目を閉じて瞑想する")) {
		case 1:
			emotion 0;
			mes "[ヴァルキリーの悪夢]";
			mes "ほう、私と刃を交えるつもりか！";
			mes "良かろう、我が必殺の一撃を";
			mes "食らうがいい！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　こちらに向って斬りかかってきた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐その場から慌てて逃げ出した。";
			mes "　しばらくしてから";
			mes "　話し掛けたほうが良さそうだ‐";
			close;
		case 2:
			emotion 0;
			mes "[ヴァルキリーの悪夢]";
			mes "話し合いの時間は";
			mes "すでに過ぎ去っている！";
			mes "今は互いの剣で決着をつける時だ！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　こちらに向って斬りかかってきた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐その場から慌てて逃げ出した。";
			mes "　しばらくしてから";
			mes "　話し掛けたほうが良さそうだ‐";
			close;
		case 3:
			break;
		}
		cutin "3rd_ab_anghilde01",1;
		mes "[ヴァルキリーの悪夢]";
		mes "貴様、何のつもりだ？";
		mes "敵を目の前にして目を閉じるなど！";
		mes "死の覚悟ができたということか！";
		next;
		switch(select("急いで弁解する","静かに瞑想を続ける","大声で賛美歌を歌う")) {
		case 1:
			cutin "3rd_ab_anghilde03",1;
			emotion 6;
			mes "[ヴァルキリーの悪夢]";
			mes "誰が貴様のような者の話に";
			mes "耳を傾けるものか！";
			mes "今すぐ、私が成敗してくれるわ！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　こちらに向って斬りかかってきた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐その場から慌てて逃げ出した。";
			mes "　しばらくしてから";
			mes "　話し掛けたほうが良さそうだ‐";
			close;
		case 2:
			break;
		case 3:
			cutin "3rd_ab_anghilde01",255;
			misceffect 75,"";
			mes "‐賛美歌を高らかに歌い上げる‐";
			next;
			cutin "3rd_ab_anghilde03",1;
			emotion 6;
			mes "[ヴァルキリーの悪夢]";
			mes "私は歌など聴きたくはない！";
			mes "その口を閉じろ！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　こちらに向って斬りかかってきた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐その場から慌てて逃げ出した。";
			mes "　しばらくしてから";
			mes "　話し掛けたほうが良さそうだ‐";
			close;
		}
		mes "[ヴァルキリーの悪夢]";
		mes "……私と戦う気は無いと言うことか？";
		mes "お前は一体何者だ。";
		mes "なぜ、私の前に立つのだ？";
		next;
		mes "‐ヴァルキリーは";
		mes "　少し落ち着いたように見える";
		next;
		switch(select("瞑想を続ける","はっきりと告解を促す","大声で賛美歌を歌う")) {
		case 1:
			cutin "3rd_ab_anghilde03",1;
			emotion 6;
			mes "[ヴァルキリーの悪夢]";
			mes "質問に答える気は無いのだな？";
			mes "貴様のような者には興味は無い。";
			mes "今すぐ私の前から失せろ！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　こちらに向って斬りかかってきた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐その場から慌てて逃げ出した。";
			mes "　しばらくしてから";
			mes "　話し掛けたほうが良さそうだ‐";
			close;
		case 2:
			break;
		case 3:
			cutin "3rd_ab_anghilde01",255;
			misceffect 75,"";
			mes "‐賛美歌を高らかに歌い上げる‐";
			next;
			cutin "3rd_ab_anghilde03",1;
			emotion 6;
			mes "[ヴァルキリーの悪夢]";
			mes "私は歌など聴きたくはない！";
			mes "その口を閉じろ！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　こちらに向って斬りかかってきた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐その場から慌てて逃げ出した。";
			mes "　しばらくしてから";
			mes "　話し掛けたほうが良さそうだ‐";
			close;
		}
		emotion 1;
		mes "[ヴァルキリーの悪夢]";
		mes "私に罪を告白しろと言うのか？";
		mes "栄光あるヴァルキリーに";
		mes "告解する罪など……";
		next;
		cutin "3rd_ab_anghilde01",255;
		mes "[" + strcharinfo(0) + "]";
		mes "自らの罪を告解することは";
		mes "苦しい道ですが";
		mes "神は必ず貴方の罪を";
		mes "赦してくださいます。";
		next;
		mes "[" + strcharinfo(0) + "]";
		mes "貴方の苦しみは";
		mes "やがて歓喜に至るでしょう。";
		mes "さあ、貴方の罪を告白し";
		mes "神に赦しを請うのです。";
		next;
		cutin "3rd_ab_anghilde02",1;
		mes "[ヴァルキリーの悪夢]";
		mes "ああ……";
		mes "もしそれが叶うとすれば";
		mes "どれだけ喜ばしいことか……。";
		next;
		cutin "3rd_ab_anghilde01",1;
		mes "[ヴァルキリーの悪夢]";
		mes "私は自らの不注意で";
		mes "オーディン様の狼である";
		mes "フレキを傷つけてしまった。";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes "そして今は、悪魔どもに追いやられ";
		mes "この神殿を守るという使命さえも";
		mes "守れずにいる！";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes "この不甲斐無い私を";
		mes "神は赦してくださるというのか！";
		next;
		if(select("ヴァルキリーに聖水を振りかける","自分で聖水を飲む") == 2) {
			cutin "3rd_ab_anghilde01",255;
			if(countitem(523) < 1) {
				mes "‐聖水を飲もうとしたが";
				mes "　聖水を持っていなかった‐";
				next;
				mes "‐聖水を手に入れてから";
				mes "　話し掛けたほうが良さそうだ‐";
				close;
			}
			mes "‐聖水にゆっくりと口をつけた。";
			mes "　しかし、何も起きる気配はない‐";
			next;
			cutin "3rd_ab_anghilde03",1;
			emotion 6;
			mes "[ヴァルキリーの悪夢]";
			mes "やはり私の罪は赦されないのか！";
			mes "ならば、侵入者をこの聖域から";
			mes "追い出し、恥をすすぐしか無い！";
			next;
			mes "‐ヴァルキリーはそう言うと";
			mes "　こちらに向って斬りかかってきた‐";
			next;
			cutin "3rd_ab_anghilde03",255;
			emotion 19,"";
			mes "‐その場から慌てて逃げ出した。";
			mes "　しばらくしてから";
			mes "　話し掛けたほうが良さそうだ‐";
			close;
		}
		cutin "3rd_ab_anghilde01",255;
		if(countitem(523) < 1) {
			mes "‐ヴァルキリーに聖水を";
			mes "　振りかけようとしたが";
			mes "　聖水を持っていなかった‐";
			next;
			mes "‐聖水を手に入れてから";
			mes "　話し掛けたほうが良さそうだ‐";
			close;
		}
		mes "‐ヴァルキリーに持っていた聖水を";
		mes "　振りかけた‐";
		next;
		misceffect 78;
		cutin "3rd_ab_anghilde02",1;
		mes "[ヴァルキリーの悪夢]";
		mes "おお、なんとも清清しい心地だ。";
		mes "私のこれまでの苦悩が";
		mes "失せていくようだ……";
		next;
		mes "‐ヴァルキリーは武器を収めると";
		mes "　天を仰いで祈りだした‐";
		next;
		mes "‐最後に行うのは、もちろん……‐";
		next;
		if(select("賛美歌を歌い祝福する","静かに立ち去る") == 2) {
			cutin "3rd_ab_anghilde01",255;
			mes "‐ヴァルキリーの祈りを";
			mes "　邪魔しないように";
			mes "　その場から静かに立ち去った‐";
			next;
			mes "‐しかし、何も進展していないことに";
			mes "　気がついた‐";
			next;
			mes "‐しばらくしてから";
			mes "　ヴァルキリーに再度";
			mes "　話し掛けたほうが良さそうだ‐";
			close;
		}
		cutin "3rd_ab_anghilde01",255;
		misceffect 75,"";
		mes "‐賛美歌を歌い";
		mes "　ヴァルキリーを祝福する‐";
		next;
		misceffect 77;
		cutin "3rd_ab_anghilde01",1;
		mes "[ヴァルキリーの悪夢]";
		mes "おお……私はこれまで";
		mes "悪夢に蝕まれ、自分自身を失くして";
		mes "いたようだ……。";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes "だが、貴様の祈りの儀式によって";
		mes "ようやく自分自身を";
		mes "取り戻すことができた。";
		mes "感謝するぞ、人間。";
		next;
		cutin "3rd_ab_anghilde01",255;
		mes "‐黄金の角笛について尋ねた‐";
		next;
		cutin "3rd_ab_anghilde01",1;
		mes "[ヴァルキリーの悪夢]";
		mes "黄金の角笛か……。";
		mes "残念だが、私が持っているのは";
		mes "割れた角笛の片割れのみ……。";
		next;
		emotion 0;
		mes "[ヴァルキリーの悪夢]";
		mes "なんと！　すでにもう片方の";
		mes "欠片を手に入れていたのか。";
		mes "ならば、これも持って行くがいい。";
		mes "これで角笛を復元できるだろう！";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes "だが、まだ終わってはいないぞ。";
		mes "島の一番高いところにある";
		mes "^0000FF崩壊した神殿^000000に向かうのだ。";
		next;
		if(checkitemblank() < 1) {
			mes "[ヴァルキリーの悪夢]";
			mes "む、荷物が多くて";
			mes "欠片が持てないようだな。";
			mes "所持品の種類数を減らしてから";
			mes "また来てくれ。";
			close2;
			cutin "3rd_ab_anghilde01",255;
			end;
		}
		mes "[ヴァルキリーの悪夢]";
		mes "そこで角笛を使用すれば";
		mes "全てが終わるだろう。";
		mes "最後まで気を抜くなよ。";
		set CHANGE_AB,10;
		chgquest 104275,104280;
		getitem 6154,1;		// 壊れた角笛の欠片
		viewpoint 2,1,1,0,0xFFFFFF;
		close2;
		cutin "3rd_ab_anghilde01",255;
		end;
	case 10:
	case 11:
		cutin "3rd_ab_anghilde01",1;
		mes "[ヴァルキリーの悪夢]";
		mes "まだ終わってはいないぞ。";
		mes "島の一番高いところにある";
		mes "^0000FF崩壊した神殿^000000に向かうのだ。";
		next;
		mes "[ヴァルキリーの悪夢]";
		mes "そこで角笛を使用すれば";
		mes "全てが終わるだろう。";
		mes "最後まで気を抜くな。";
		close2;
		cutin "3rd_ab_anghilde01",255;
		end;
	}
}

job3_arch02.gat,273,235,5	script	ヴァルキリーの幻影	811,{
	switch(CHANGE_AB) {
	default:
		cutin "3rd_ab_valkyrie",1;
		mes "[ヴァルキリーの幻影]";
		mes "いつまでも貴方が";
		mes "気高き聖職者でありますように！";
		mes "いつかまたヴァルハラで";
		mes "会いましょう……";
		close2;
		cutin "3rd_ab_valkyrie",255;
		warp "hugel.gat",191,103;
		end;
	case 8:
		cutin "3rd_ab_valkyrie",1;
		mes "[ヴァルキリーの幻影]";
		mes "ここは神殿の中でも一番高い場所。";
		mes "もっとも天に近い場所です。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "黄金の角笛をここで使えば";
		mes "ヴァルキリーの援軍を呼ぶことが";
		mes "できるでしょう。";
		next;
		switch(select("黄金の角笛について聞く","ここから出たいのですが","会話をやめる")) {
		case 1:
			mes "[ヴァルキリーの幻影]";
			mes "黄金の角笛は、天上への連絡手段。";
			mes "その音が鳴り響けば";
			mes "ヴァルキリーたちが";
			mes "この地に集結するでしょう。";
			next;
			mes "[ヴァルキリーの幻影]";
			mes "しかし、アングヒルデが";
			mes "悪魔に敗れた際";
			mes "角笛も2つに割られてしまいました。";
			next;
			mes "[ヴァルキリーの幻影]";
			mes "^FF00002つ^000000に割られた角笛を探すのです。";
			mes "この神殿のどこかにあるはずです。";
			next;
			mes "[ヴァルキリーの幻影]";
			mes "^FF0000焦ることなく慎重に事を進めれば^000000";
			mes "必ず手に入れることが";
			mes "できるはずです。";
			close2;
			cutin "3rd_ab_valkyrie",255;
			end;
		case 2:
			mes "[ヴァルキリーの幻影]";
			mes "わかりました。";
			mes "アングヒルデの元に";
			mes "戻してあげましょう。";
			close2;
			cutin "3rd_ab_valkyrie",255;
			warp "job3_arch01.gat",29,29;
			end;
		case 3:
			mes "[ヴァルキリーの幻影]";
			mes "無理をしてはいけません。";
			mes "必要なのは、焦らずに";
			mes "事を進める忍耐力です。";
			close2;
			cutin "3rd_ab_valkyrie",255;
			end;
		}
	case 9:
		cutin "3rd_ab_valkyrie",1;
		mes "[ヴァルキリーの幻影]";
		mes "ここは神殿の中でも一番高い場所。";
		mes "もっとも天に近い場所です。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "壊れた角笛の欠片を1つ";
		mes "手に入れたのですね。";
		mes "もう1つの欠片があれば";
		mes "角笛を元に戻すことができます。";
		next;
		switch(select("黄金の角笛について聞く","ここから出たいのですが","会話をやめる")) {
		case 1:
			mes "[ヴァルキリーの幻影]";
			mes "もう1つの壊れた角笛の欠片を";
			mes "手に入れる必要があります。";
			next;
			mes "[ヴァルキリーの幻影]";
			mes "そのためには、^FF0000聖地巡礼の道のり^000000を";
			mes "思い出す必要が";
			mes "あるかもしれません。";
			next;
			mes "[ヴァルキリーの幻影]";
			mes "苦悩する者に必要なのは";
			mes "敬虔なる^FF0000祈りの儀式^000000です。";
			mes "貴方もフベルゲルミルの泉にて";
			mes "経験しているはずですよ。";
			close2;
			cutin "3rd_ab_valkyrie",255;
			end;
		case 2:
			mes "[ヴァルキリーの幻影]";
			mes "わかりました。";
			mes "アングヒルデの元に";
			mes "戻してあげましょう。";
			close2;
			cutin "3rd_ab_valkyrie",255;
			warp "job3_arch01.gat",29,29;
			end;
		case 3:
			mes "[ヴァルキリーの幻影]";
			mes "無理をしてはいけません。";
			mes "必要なのは、焦らずに";
			mes "事を進める忍耐力です。";
			close2;
			cutin "3rd_ab_valkyrie",255;
			end;
		}
	case 10:
		cutin "3rd_ab_valkyrie",1;
		mes "[ヴァルキリーの幻影]";
		mes "角笛の欠片が集まりましたね。";
		mes "さあ、それを修復してあげましょう。";
		next;
		cutin "3rd_ab_valkyrie",255;
		misceffect 82,"";
		mes "‐2つの欠片が1つになり";
		mes "　黄金の角笛として修復された‐";
		next;
		cutin "3rd_ab_valkyrie",1;
		mes "[ヴァルキリーの幻影]";
		mes "さあ、その角笛を吹き鳴らすのです。";
		mes "天上まで、その音色が届くように！";
		next;
		cutin "3rd_ab_valkyrie",255;
		mes "‐空に向かって思い切り角笛を";
		mes "　吹き鳴らした‐";
		next;
		mes "ブゥォォォォ……";
		mes "ブゥゥォォオ………";
		next;
		cutin "3rd_ab_anghilde01",1;
		mes "[アングヒルデの声]";
		mes "遂にこの時が来たのだな！";
		mes "角笛の音が天上まで届く時が！";
		next;
		mes "[アングヒルデの声]";
		mes "オーディン様のしもべ！";
		mes "ヴァルハラの戦乙女たちよ！";
		mes "神の聖域が闇に汚されています！";
		next;
		mes "[アングヒルデの声]";
		mes "どうか力を貸してください！";
		mes "力を失くした私に代わり";
		mes "闇を打ち払ってください！";
		next;
		cutin "3rd_ab_valkyrie",1;
		mes "[天上の声]";
		mes "安心しなさい、アングヒルデよ。";
		mes "貴方の願いは角笛の音色と共に";
		mes "ヴァルハラに届きました。";
		next;
		mes "[天上の声]";
		mes "貴方の願いは";
		mes "すぐに叶えられることでしょう。";
		mes "悪魔達は他のヴァルキリー達によって";
		mes "すべて処断されるのです。";
		next;
		cutin "3rd_ab_anghilde01",1;
		mes "[アングヒルデの声]";
		mes "姉妹達が来てくれるのですね！";
		mes "ならば、ここはもう安全なのですか？";
		next;
		cutin "3rd_ab_valkyrie",1;
		mes "[天上の声]";
		mes "そうです、アングヒルデ。";
		next;
		mes "[天上の声]";
		mes "そして貴方がアスガルドから";
		mes "追放された後も、一人でこの聖地を";
		mes "守ろうとした功績が認められました。";
		next;
		mes "[天上の声]";
		mes "すぐにでも貴方の追放は赦され";
		mes "天上に戻れるようになるでしょう。";
		next;
		cutin "3rd_ab_anghilde02",1;
		mes "[アングヒルデの声]";
		mes "ああ！　アスガルドに戻れるなんて！";
		next;
		mes "[アングヒルデの声]";
		mes "オーディン様に栄光あれ！";
		mes "恩恵を賜り、嬉しさで心が満ちる。";
		mes "明るくて……暖かい……光が！";
		next;
		mes "‐アングヒルデの歓喜の歌が";
		mes "　響き渡る‐";
		next;
		cutin "3rd_ab_anghilde02",255;
		emotion 1,"";
		mes "‐しかし、その歌声は突然";
		mes "　聞こえなくなった‐";
		next;
		mes "‐不思議に思っていると";
		mes "　目の前のヴァルキリーが";
		mes "　語りかけてきた‐";
		next;
		cutin "3rd_ab_valkyrie",1;
		mes "[ヴァルキリーの幻影]";
		mes "心配する事はありません。";
		mes "彼女は本来いるべき場所に";
		mes "戻ったのです。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "……アングヒルデは既に死んだ";
		mes "ヴァルキリーだったのです。";
		next;
		emotion 0,"";
		mes "[ヴァルキリーの幻影]";
		mes "ここは現実を認められない";
		mes "アングヒルデの歪んだ幻想……";
		mes "悪夢が生み出した空間。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "彼女の魂は死後";
		mes "この悪夢の中に閉じ込められ";
		mes "ずっと苦しんでいたのです。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "しかし、貴方のおかげで";
		mes "アングヒルデは救われました。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "現実世界の神殿では";
		mes "悪魔が徘徊したままですが";
		mes "彼女の魂は安息を得たのです。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "貴方は、姉妹を救ってくれました。";
		mes "本当に感謝いたします。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "ぜひお礼をしたいのですが";
		mes "私の勝手でヴァルハラに";
		mes "招待することはできません。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "代わりにオーディン様から";
		mes "与えられた力で";
		mes "貴方に新しい力を授けましょう。";
		delitem 6154,countitem(6154);		// 壊れた角笛の欠片
		set CHANGE_AB,11;
		chgquest 104280,104285;
		next;
		mes "[ヴァルキリーの幻影]";
		mes "そのためには準備が必要です。";
		mes "装備や所持品を預け、";
		mes "スキルポイントを";
		mes "すべて消費してきてください。";
		next;
		mes "[ヴァルキリーの幻影]";
		mes "準備ができたら声を掛けてください。";
		mes "私はここでお待ちしております。";
		close2;
		cutin "3rd_ab_valkyrie",255;
		end;
	case 11:
		cutin "3rd_ab_valkyrie",1;
		mes "[ヴァルキリーの幻影]";
		mes "新しい力を授かる準備は";
		mes "できたのですか？";
		next;
		switch(select("準備はできています","まだ待ってください","外に戻りたいです")) {
		case 1:
			mes "[ヴァルキリーの幻影]";
			mes "それでは、貴方に聖なる力を";
			mes "授けましょう！";
			next;
			if(Weight || checkitemblank() < 2 || checkcart() || checkfalcon() || checkriding() || checkdragon() || checkgear() || checkwolf() || sc_ison(SC_ALL_RIDING) || getpetinfo(0)) {
				mes "[ヴァルキリーの幻影]";
				mes "……おや？";
				mes "転職の準備が済んでいませんよ。";
				mes "引き連れているものは全て解放し、";
				mes "重量がある物は持たないで来るのです。";
				next;
				cutin "3rd_ab_valkyrie",255;
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
				mes "[ヴァルキリーの幻影]";
				mes "転職の準備ができていませんよ。";
				mes "もう一度、確認してみてください。";
				next;
				cutin "3rd_ab_valkyrie",255;
				mes "^FF0000‐スキルポイントが余っている場合は";
				mes "　全て消費してください‐^000000";
				close;
			}
			if(Job != Job_Priest || Upper == UPPER_NORMAL || (Upper == UPPER_HIGH && BaseLevel < 90) || (Upper == UPPER_BABY && (BaseLevel < 99 || JobLevel < 50))) {	// 念のため職チェック
				mes "[ヴァルキリーの幻影]";
				mes "転職の準備ができていませんよ。";
				mes "もう一度、確認してみてください。";
				close2;
				cutin "3rd_ab_valkyrie",255;
				end;
			}
			set CHANGE_AB,0;
			chgquest 104285,201195;
			compquest 201195;
			resetstatus;
			resetskill;
			setoption 0;
			jobchange Job_ArchBishop;
			getitem 5747,1;		// ミトラ
			getitem 2795,1;		// 熟していないリンゴの指輪
			setquest 129700;	// ステータス＆スキル一括リセット権
			mes "[ヴァルキリーの幻影]";
			mes "貴方にはこれもお渡しします。";
			mes "遠慮せず受け取ってください。";
			next;
			mes "[ヴァルキリーの幻影]";
			mes "いつまでも貴方が";
			mes "気高き聖職者でありますように！";
			mes "いつかまたヴァルハラで";
			mes "会いましょう……";
			next;
			cutin "3rd_ab_valkyrie",255;
			mes "[インフォメーション]";
			mes "転職試験のクリア報酬";
			mes "ステータス・スキル一括リセット権が";
			mes "付与されました。";
			mes "クエストウィンドウで利用方法を";
			mes "確認できます。";
			close2;
			warp "hugel.gat",191,103;
			end;
		case 2:
			mes "[ヴァルキリーの幻影]";
			mes "準備ができたら声を掛けてください。";
			mes "私はここでお待ちしております。";
			close2;
			cutin "3rd_ab_valkyrie",255;
			end;
		case 3:
			mes "[ヴァルキリーの幻影]";
			mes "わかりました。";
			mes "それでは一度フィゲルに送ります。";
			next;
			mes "[ヴァルキリーの幻影]";
			mes "ここに来る際は";
			mes "^0000FFシスター・アンジェに案内して";
			mes "もらってくださいね。^000000";
			close2;
			cutin "3rd_ab_valkyrie",255;
			warp "hugel.gat",191,103;
			end;
		}
	}
}
