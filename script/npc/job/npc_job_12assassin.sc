//====================================================================
//Ragnarok Online Assassin jobchange script
//
//　■ CHANGE_AS
//	1	筆記試験
//	2	筆記試験クリア
//	3	実技試験１
//	4	実技試験２
//	5	最終試験クリア
//
//　■ $@as_tester$ -> 実技挑戦者のキャラ名
//     @as_step     -> ギルドマスター部屋用
//====================================================================

//==========================================
// 試験受付および転職
//------------------------------------------

in_moc_16.gat,19,33,4	script	ギルド員	55,{
	if(Upper == UPPER_HIGH) {
		mes "[殺気を放つ者]";
		mes "ほう……貴様は……";
		mes "ただならぬ気配を持っているな。";
		next;
		mes "[殺気を放つ者]";
		mes "しかし私を圧するその気配……";
		mes "気に食わんな。";
		mes "帰れ！";
		close;
	}
	if(Job == Job_Thief && SkillPoint) {
		mes "[殺気を放つ者]";
		mes "スキルポイントが残っていては";
		mes "転職はできない。";
		mes "皆消費して来るように。";
		close;
	}
	mes "[殺気を放つ者]";
	mes "ん…";
	mes "何をしに来た？";
	mes "……";
	next;
	if(Job == Job_Novice) {
		mes "[殺気を放つ者]";
		mes "おい…ノービス。";
		mes "ここは貴様のような者が来て良い";
		mes "場所ではない。立ち去れ…";
		close;
	}
	if(getbaseclass(Class) == CLASS_AL) {
		mes "[殺気を放つ者]";
		mes "神に仕える者が何をしに来た？";
		mes "ここには貴様らが求める神はいない。";
		mes "帰るがいい…";
		close;
	}
	if(Job == Job_Assassin) {
		mes "[ベテランアサシン・ヒュイ]";
		mes "うん…";
		mes "たしか " +strcharinfo(0)+ " だったか…";
		next;
		mes "[ベテランアサシン・ヒュイ]";
		mes "せっかくだが、今はギルドからの";
		mes "仕事の要請は無い。";
		mes "修練を積んでいてくれ。さらばだ。";
		close;
	}
	if(Job != Job_Thief) {
		mes "[殺気を放つ者]";
		mes "何か仕事でも持ってきたのか？";
		mes "そうでなければ早々に立ち去れ…";
		close;
	}
	if(JobLevel < 40) {
		mes "[殺気を放つ者]";
		mes "うん…貴様はまだ修練不足だな。";
		mes "アサシンになりたいのなら、少なくとも";
		mes "シーフとしての修練をある程度積ま";
		mes "なければならない。";
		next;
		mes "[殺気を放つ者]";
		mes "それではさらなる修練を積んで";
		mes "から戻ってくるのだ…";
		mes "正確な転職条件は、JobLv40以上";
		mes "であること。";
		close;
	}
	switch(CHANGE_AS) {
	default:
		mes "[殺気を放つ者]";
		mes "うん…シーフか…";
		mes "シーフとして相当の修練を積んだな。";
		mes "どうだ？アサシンに転職するつもりは";
		mes "ないか？";
		next;
		switch (select("そのために来た","転職条件は？","遠慮する")) {
			case 1:
				mes "[殺気を放つ者]";
				mes "うむ…久しぶりの客だ。";
				mes "よし、受付に送ってやろう。";
				hideoffnpc "ギルド関係者#assassin1";
				hideonnpc "ギルド関係者#assassin2";
				close2;
				savepoint "in_moc_16.gat",15,12;
				warp "in_moc_16.gat",19,76;
				end;
			case 2:
				mes "[殺気を放つ者]";
				mes "転職条件は…";
				mes "一．シーフであること";
				mes "二．JobLvが40以上であること";
				mes "三．ギルドからのテストにパスすること";
				mes "の三つだ。";
				next;
				mes "[殺気を放つ者]";
				mes "シーフである水準以上の修練を";
				mes "積んだ者なら、テストを簡単に";
				mes "クリアすることも可能だ。";
				close;
			case 3:
				mes "[殺気を放つ者]";
				mes "そうか…仕方ない…";
				close;
		}
	case 4:
		mes "[殺気を放つ者]";
		mes "気を失ったか…";
		mes "HPとSPを回復してやる。";
		mes "力を出してもう一度挑戦しろ。";
		percentheal 100,100;
		next;
		mes "[殺気を放つ者]";
		mes "ところで…気絶するほどのものか？";
		mes "次の挑戦でもどうか…";
		mes "まだ無理ではないか？";
		next;
		if(select("大丈夫だ","無理だ…次の機会にする")==1) {
			mes "[殺気を放つ者]";
			mes "ふむ…そうか…";
			mes "頑張ってみろ。";
			close2;
			warp "in_moc_16.gat",19,76;
		}
		else {
			mes "[殺気を放つ者]";
			mes "そうか…いつでも待っている。";
			next;
			mes "[殺気を放つ者]";
			mes "ああ…街に戻ったらセーブを";
			mes "忘れないように。";
			mes "じゃ……";
			close2;
		}
		set CHANGE_AS,2;
		end;
	case 5:
		if(countitem(1008) < 1) {
			mes "[ベテランアサシン・ヒュイ]";
			mes "む……何を聞き間違ったか";
			mes "「非情な心」を持っていないな。";
			next;
			mes "[ベテランアサシン・ヒュイ]";
			mes "どこかで落としでもしたか…？";
			next;
			mes "[ベテランアサシン・ヒュイ]";
			mes "ギルドマスターが気づかないうちに";
			mes "早く見つけてこい！";
			next;
			mes "[ベテランアサシン・ヒュイ]";
			mes "見つかったらすぐに戻ってこいよ！";
			close;
		}
		if(SkillPoint) {
			mes "[殺気を放つ者]";
			mes "スキルポイントが残っていては";
			mes "転職はできない。";
			mes "皆消費して来るように。";
			close;
		}
		mes "[ベテランアサシン・ヒュイ]";
		mes "…おめでとう。いよいよ転職だ。";
		mes "その前に…ギルドマスターが";
		mes "求めたものを見てみようか…";
		next;
		mes "[ベテランアサシン・ヒュイ]";
		mes "………";
		mes "……";
		mes "…";
		next;
		delitem 1008,1;
		mes "[ベテランアサシン・ヒュイ]";
		mes "うむ、良いな。";
		next;
		unequip;
		jobchange Job_Assassin;
		set CHANGE_AS,0;
		mes "[ベテランアサシン・ヒュイ]";
		mes "よし！アサシンとしての道を歩んで";
		mes "いけ！常に自分の信念を貫き";
		mes "生くのだぞ。";
		mes "たまには遊びにこい。転職を祝おう。";
		close;
	}
}


//==========================================
// 一次試験（筆記試験）
//------------------------------------------

in_moc_16.gat,21,91,2	script	ギルド関係者#assassin1	730,1,1,{
	end;
OnTouch:
	mes "[アサシン・カイ]";
	mes "うん…？";
	close2;
	misceffect 16;
	hideonnpc;
	hideoffnpc "ギルド関係者#assassin2";
	end;
}

in_moc_16.gat,25,90,2	script	ギルド関係者#assassin2	730,2,2,{
	mes "[アサシン・カイ]";
	mes "まあ近くに来い。俺は人の顔を見て";
	mes "話すようにしている。";
	mes "俺は顔の見えないところで話を";
	mes "されるのが苦手でね…";
	mes "特に後ろから話しかけられるのは";
	mes "嫌いだ…";
	close;
OnTouch:
	if(CHANGE_AS != 1) {
		mes "[アサシン・カイ]";
		mes "何だ…転職しに来た奴か…";
		mes "誰かが近づくと避けるのが習慣に";
		mes "なっていてね…";
		mes "ふむ…ここまでご苦労だったな。";
		next;
		mes "[アサシン・カイ]";
		mes "アサシンへの転職について";
		mes "聞きたいのか？";
		next;
		if(select("そうだ","いや")==1) {
			mes "[アサシン・カイ]";
			mes "よし、すぐに転職申込書を作ろうか。";
			mes "そこの用紙に名前とJobLvを";
			mes "書くように。";
		}
		else {
			mes "[アサシン・カイ]";
			mes "ふむ…";
			mes "……";
			next;
			mes "[アサシン・カイ]";
			mes "本当に？";
			mes "……";
			next;
			if(select("はい","いや、転職したい")==1) {
				mes "[アサシン・カイ]";
				mes "なら出て行くんだ。";
				close2;
				warp "moc_fild16.gat",206,229;
				end;
			}
			mes "[アサシン・カイ]";
			mes "……";
			mes "……冷やかしか!?";
			mes "とにかく…転職するんだな？";
			next;
			mes "[アサシン・カイ]";
			mes "そこの転職申込書に";
			mes "名前とJobLvを書いてくれ。";
		}
		next;
		mes "[アサシン・カイ]";
		mes "どれ… " +strcharinfo(0)+ " と…";
		mes "JobLvは " +JobLevel+ " …";
		next;
		if(JobLevel >= 50) {
			mes "[アサシン・カイ]";
			mes "なに！ 50 だと！";
			mes "お前…相当な修練を積んだな！";
			mes "久々に使える奴が入って来たと";
			mes "上層部が喜ぶだろう…";
			mes "あ、独り言だ。早く書くように。";
		}
		else {
			mes "[アサシン・カイ]";
			mes "ふむ…賢明だな。";
			mes "最近皆根性が無くてね…";
			mes "あ、独り言だ。忘れてくれ。";
		}
		next;
		mes "[アサシン・カイ]";
		mes "……";
		next;
		mes "[アサシン・カイ]";
		mes "申込書への作成が終わったか。";
		mes "ではそれを私に。";
		next;
		mes "[アサシン・カイ]";
		mes "よし、行け。幸運を祈る。";
		close2;
		warp "in_moc_16.gat",19,144;
		misceffect 16;
		hideonnpc;
		hideoffnpc "ギルド関係者#assassin1";
		end;
	}
	mes "[アサシン・カイ]";
	mes "おう…試験は終わったか？";
	next;
	mes "[アサシン・カイ]";
	mes "ん…筆記で落ちたって？";
	mes "ぷっ…くくく…はははは！";
	next;
	mes "[アサシン・カイ]";
	mes "いや…久しぶりに面白い" +(Sex? "奴": "姉さん");
	mes "だと思ってさ…";
	mes "アサシンになりたいなら、あれくらい";
	mes "知ってて当然だろう？くくく…";
	next;
	mes "[アサシン・カイ]";
	mes "…ははは腹が痛い…";
	next;
	mes "[アサシン・カイ]";
	mes "くく…笑ってる場合じゃないな。";
	mes "ふふ…ヒントでもあげようか？";
	next;
	switch (select("はい","笑ってないでヒントをくれ","ヒントなどいらない")) {
	case 1:
		mes "[アサシン・カイ]";
		mes "ぷ…ははははは！";
		mes "これはお笑いだ…";
		mes "腹が痛い…あまり笑わせないでくれ！";
		next;
		mes "[名も無き者]";
		mes "…くくく";
		next;
		mes "[アサシン・カイ]";
		mes "ははは…名も知らない者が";
		mes "ずいぶんと図々しいね…";
		next;
		mes "[名も無き者]";
		mes "……";
		next;
		mes "[アサシン・カイ]";
		mes "ヒントか…";
		next;
		mes "[アサシン・カイ]";
		mes "…";
		next;
		mes "[アサシン・カイ]";
		mes "……";
		next;
		mes "[アサシン・カイ]";
		mes "…………";
		next;
		mes "[アサシン・カイ]";
		mes "………………";
		next;
		mes "[アサシン・カイ]";
		mes "……………………";
		next;
		mes "[アサシン・カイ]";
		mes "やだね。";
		next;
		mes "[アサシン・カイ]";
		mes "くくく…「はい」だって…";
		close;
	case 2:
		mes "[アサシン・カイ]";
		mes "ふむ…なりふり構っていられないか…";
		mes "まあ…たしかに誰でも過ちはおかす。";
		mes "笑ってすまん。";
		mes "だがプライドは捨てるなよ。";
		next;
		mes "[アサシン・カイ]";
		mes "ヒントは少しだ。";
		mes "アサシンについて、一言二言話す。";
		next;
		mes "[アサシン・カイ]";
		mes "何より俺達は、プライドを守らな";
		mes "ければならない。";
		mes "「砂漠の牙」アサシンだというな。";
		mes "いつかは俺達の出番が来る…";
		mes "今はその時を待つだけだ。";
		next;
		mes "[アサシン・カイ]";
		mes "そして…中には近くに親しい人間を";
		mes "持つ者もいるが、俺達は仕事柄たいてい";
		mes "孤独で生きる。";
		mes "もし、君の恋人や友達がひどい目に";
		mes "遭い、血を見ることになったら…";
		next;
		mes "[アサシン・カイ]";
		mes "決して忘れることはできないだろう。";
		mes "その重みを一生負い生きなければ";
		mes "ならない…";
		next;
		mes "[アサシン・カイ]";
		mes "少し寂しいが、己の道を歩むのだから";
		mes "これもしかたないだろう…";
		mes "文字通り「己の道」なんだ。";
		next;
		mes "[アサシン・カイ]";
		mes "俺が言えることはこれくらいか…";
		close;
	case 3:
		mes "[アサシン・カイ]";
		mes "うむ…";
		next;
		mes "[アサシン・カイ]";
		mes "その精神だ。プライドを捨てるような";
		mes "ことをしてはならない。";
		mes "俺達は誰がなんと言おうと、";
		mes "「砂漠の牙」としてのプライドがある。";
		mes "笑ってすまない…正式に詫びよう…";
		next;
		mes "[アサシン・カイ]";
		mes "最近はあまりにも腐った輩が";
		mes "多くてね…自分の仕事に関する知識は";
		mes "置いておくとしても、アサシンとしての";
		mes "プライドや、今まで辛い時に努力した";
		mes "記憶はどこへいってしまったのか…";
		next;
		mes "[アサシン・カイ]";
		mes "まったく…";
		next;
		mes "[アサシン・カイ]";
		mes "是非たのむ。アサシンになっても";
		mes "プライドは絶対に捨てるなよ！";
		next;
		if(select("…分かった","…嫌だ")==2) {
			mes "[アサシン・カイ]";
			mes "…これだけ言ってもわからないか？";
			next;
			mes "[アサシン・カイ]";
			mes "プライドを守ることがそんなに";
			mes "難しいことなのか？";
			next;
			mes "[アサシン・カイ]";
			mes "他人の靴をなめる犬になるというのか！";
			next;
			mes "[アサシン・カイ]";
			mes "出て行け！今すぐにだ！";
			mes "お前のような奴はアサシンになる";
			mes "資格などない！";
			next;
			mes "[アサシン・カイ]";
			mes "くわっ!!!!!";
			close2;
			warp "c_tower4.gat",64,76;
			end;
		}
		mes "[アサシン・カイ]";
		mes "うむ。その静かな返事に、決意が";
		mes "込められているな。";
		mes "それではいくつかのヒントを与える。";
		break;
	}
	next;
	switch(rand(3)) {
		case 0:
			mes "[アサシン・カイ]";
			mes "エルダーウィローカードを拾ったら、";
			mes "直ちに魔術師らに売れ。";
			mes "奴らは俺達には用の無いそのカードを";
			mes "欲しがるだろう。たしかINTを上げる";
			mes "効果を持っていたか…";
			next;
			mes "[アサシン・カイ]";
			mes "俺達は、防御より回避を鍛えるべきだ。";
			mes "たまに、頭にも重い装備をして、視界も";
			mes "良くないだろうにそのまま修練をする";
			mes "奴がいる…。心眼でも使っていると";
			mes "いうのか…。とにかくヘルムみたいな";
			mes "重い装備はだめだ。";
			next;
			mes "[アサシン・カイ]";
			mes "回避率増加スキルを習得すると、";
			mes "一段階上がるごとに回避率が３";
			mes "上昇する。";
			next;
			mes "[アサシン・カイ]";
			mes "念のため言うが…カタール系列武器";
			mes "(ジャマダハル/ジュル/カタール)は";
			mes "両手装備の武器だ。";
			next;
			mes "[アサシン・カイ]";
			mes "砂漠の街…懐かしいね…";
			mes "俺も故郷のモロクに行かなくなって";
			mes "ずいぶん経ったよ…";
			mes "シーフだったのがつい昨日のようだが、";
			mes "気がついたらかなりの年月が過ぎて";
			mes "いたんだな…";
			next;
			mes "[アサシン・カイ]";
			mes "懐かしいと言えば、シーフの転職試験";
			mes "の時農場の忍び込み、紅の毛網キノコ";
			mes "と紅の毛ベトベトキノコを盗んだ時…";
			mes "あれはわくわくしたな…";
			next;
			mes "[アサシン・カイ]";
			mes "昆虫はハイディングやクローキングを";
			mes "見破ってくる。きっとあの触覚で";
			mes "こちらの居場所を知るんだろうな。";
			next;
			mes "[アサシン・カイ]";
			mes "バフォメットジュニア…奴のカード";
			mes "効果はAGI+3にCRI+1のはずだ。";
			next;
			mes "[アサシン・カイ]";
			mes "俺達アサシンはAGIが一番優れていて、";
			mes "マスターすればJob加重値で10も";
			mes "プラスされる。これだけ増えれば";
			mes "大したものだろう。";
			break;
		case 1:
			mes "[アサシン・カイ]";
			mes "鋭く削ったグールの脚の骨は、";
			mes "グールの属性・すなわちアンデッド";
			mes "属性をそのまま持つ。";
			next;
			mes "[アサシン・カイ]";
			mes "今まで使ってきた武器は何なのか…";
			mes "ダマスカスか？スティレットか？";
			mes "マインゴーシュか？…";
			mes "分からなければ自分の手をよく見る";
			mes "ことだ…";
			next;
			mes "[アサシン・カイ]";
			mes "スロットの多いカタールは、";
			mes "デザートウルフが持っている。";
			mes "よく覚えておけ。";
			next;
			mes "[アサシン・カイ]";
			mes "スロットの多いジュルは、";
			mes "土の中にトンネルを掘るモンスターが";
			mes "持っている。";
			next;
			mes "[アサシン・カイ]";
			mes "俺は蛙が苦手だ。";
			next;
			mes "[アサシン・カイ]";
			mes "ハンマーを持つゴブリンは、たしか";
			mes "地属性だったはずだ…。";
			mes "地属性は火属性に弱い。";
			next;
			mes "[アサシン・カイ]";
			mes "作られた武器には、鍛冶屋の名前が";
			mes "入っている。";
			break;
		case 2:
			mes "[アサシン・カイ]";
			mes "まず、グリムトゥースはカタールを";
			mes "装備した時のみに使えるスキルだ。";
			next;
			mes "[アサシン・カイ]";
			mes "ポイズンという言葉は「毒」の意味だ。";
			next;
			mes "[アサシン・カイ]";
			mes "ダブルアタックは、一回の攻撃で";
			mes "二度切るスキルだ。";
			next;
			mes "[アサシン・カイ]";
			mes "レッドブラッドは火属性で、";
			mes "ブルージェムストーンはアサシンには";
			mes "関係のない石だ。";
			next;
			mes "[アサシン・カイ]";
			mes "エルダーウィローは魔術師のやつらが";
			mes "コールドボルトで倒している。";
			mes "つまり水属性は火属性に強い。";
			mes "逆に風属性には弱い。";
			next;
			mes "[アサシン・カイ]";
			mes "クローキングは壁際…つまり１セル";
			mes "離れなければ人目を盗むことが可能だ。";
			mes "あるスキルさえ使われなければな。";
			break;
	}
	next;
	mes "[アサシン・カイ]";
	mes "ふぅ…それなりに大変だな…";
	mes "これも…";
	next;
	mes "[アサシン・カイ]";
	mes "俺から言えるようなヒントは";
	mes "こんなところだ。";
	mes "ほとんど全ての問題について話したが、";
	mes "残りはごく基本的なものだから";
	mes "大丈夫だろう。では、";
	mes "「名も無き者」の試験を受けてこい。";
	close2;
	warp "in_moc_16.gat",19,144;
	hideonnpc;
	hideoffnpc "ギルド関係者#assassin1";
	end;
OnInit:
	hideonnpc;
	end;
}

//==============================================================
in_moc_16.gat,19,154,0	script	名も無き者	139,8,2,{
	switch(CHANGE_AS) {
	case 0:
		mes "[名も無き者]";
		mes "ん…お客さんか。";
		mes "クスクス…探しても無駄だよ。";
		mes "ボクは完全に姿を隠しているからね。";
		mes "この程度は基本だよ？";
		mes "クク…";
		next;
		mes "[名も無き者]";
		mes "うん、何故名前が無いかというとね…";
		mes "…キャハハ！キミ、余裕だねー。";
		mes "姿の見えないボクが怖くないのかい？";
		mes "どこで刃がキミの背中を狙っているか";
		mes "わからないってのに。";
		next;
		if(select("恐ろしい…","その位の殺気なら平気だね")==1) {
			mes "[名も無き者]";
			mes "ふん、キミもつまらない奴だな…";
			next;
			mes "[名も無き者]";
			mes "つまらない奴とは話したくないな。";
		}
		else {
			mes "[名も無き者]";
			mes "ふん…そっか。";
			next;
			mes "[名も無き者]";
			mes "……";
			next;
			mes "[名も無き者]";
			mes "いいね、話を続けようか。";
			next;
			mes "[名も無き者]";
			mes "ボクは今まで殺戮を繰り返してきた。";
			mes "手は完全に血塗られている…";
			next;
			mes "[名も無き者]";
			mes "ボクはギルドの剣として存在する身。";
			mes "殺戮をするのはボクだけど、命令を下す";
			mes "のはギルド。";
			mes "ボクはただの道具にすぎない。";
			mes "だから名前なんて要らないだろう？";
			next;
			mes "[名も無き者]";
			mes "クックック…";
			mes "とにかく、実力の無い奴がアサシンに";
			mes "なるってことが気に食わないんだ。";
			mes "だからボクに認められるくらい";
			mes "問題にしっかり答えなければだめだよ。";
			next;
			mes "[名も無き者]";
			mes "ふふ…それでは問題を出す前に";
			mes "質問があったら受けようか。";
			mes "知りたいことを聞いてみな？";
		}
		while(1) {
			next;
			switch (select("スキルについて","ステータスについて","もう十分だ")) {
			case 1:
				mes "[名も無き者]";
				mes "うん…スキルか…";
				mes "スキルの効果は世界の流れに";
				mes "よって少しずつ変わることがあるが";
				mes "基本的な構造というものが存在する";
				mes "から教えてあげようか。";
				next;
				mes "[名も無き者]";
				mes "先ず「カタール修練」";
				mes "文字通り暗殺用武器のカタールを";
				mes "使用する時の攻撃力が上がる。";
				mes "また、修練度を上げるとその攻撃力も";
				mes "上がっていく。";
				next;
				mes "[名も無き者]";
				mes "「左手修練」「右手修練」";
				mes "アサシンは、各手に一つづつ、";
				mes "合わせて二本の武器を装備";
				mes "することができる。";
				mes "しかし、片手の時より扱いが";
				mes "難しくなり、攻撃力が低下する。";
				next;
				mes "[名も無き者]";
				mes "このスキルはそんな欠点を";
				mes "修練によって補うためのものだ。";
				mes "「左手修練」は、「右手修練」を";
				mes "２レベルまで習得すれば覚えられる";
				mes "ようになる。";
				next;
				mes "[名も無き者]";
				mes "「ソニックブロー」";
				mes "素早く８連撃する攻撃だ。";
				mes "相当な技術を要し、カタールを装備";
				mes "した場合のみできる。";
				mes "これは「カタール修練」を4段階まで";
				mes "修練すれば覚えられるだろう。";
				next;
				mes "[名も無き者]";
				mes "「グリムトゥース」";
				mes "見えない敵に攻撃されたらどうか？";
				mes "この技はシーフで習得できる「ハイ";
				mes "ディング」を利用し、姿を隠した状態で";
				mes "敵を攻撃することができる。";
				next;
				mes "[名も無き者]";
				mes "修練度が高いほど遠くの敵に攻撃";
				mes "することが可能だ。";
				mes "多少範囲効果もあり、多数の敵を";
				mes "相手にしなければならない時に";
				mes "使う。あくまでも「やむをえず」";
				mes "だけどな。";
				next;
				mes "[名も無き者]";
				mes "アサシンにおいての基本は「暗殺」";
				mes "であって、グリムトゥースは姿を";
				mes "消すことが前提となる技なだけに";
				mes "少なくとも「クローキング」修練が";
				mes "２必要だ。";
				next;
				mes "[名も無き者]";
				mes "「クローキング」";
				mes "ハイディングのレベルが２以上で";
				mes "これを習得可能になる。";
				mes "今ボクがやっているように、姿を";
				mes "隠したまま移動もできるのさ。";
				mes "常に壁の側に居なければならないがね。";
				next;
				mes "[名も無き者]";
				mes "「エンチャントポイズン」";
				mes "武器に毒を塗りこむ技術だ。";
				mes "毒を塗った武器は当然「毒属性」";
				mes "を持ち、その状態で攻撃した場合";
				mes "一定確率で相手は毒に侵される。";
				next;
				mes "[名も無き者]";
				mes "さらに「ベナムスプラッシャー」を";
				mes "習得すれば、さらに被害を与える";
				mes "ことができるだろう。";
				mes "パーティーの武器にも毒を塗る";
				mes "ことができるよ。";
				mes "有効に使ってくれ。";
				next;
				mes "[名も無き者]";
				mes "「ポイズンリアクト」";
				mes "毒属性攻撃に対して、一度だけ";
				mes "自動的に反撃するスキルだ。";
				mes "自分にだけではなく、他人にも";
				mes "使用することができる。";
				next;
				mes "[名も無き者]";
				mes "「エンチャントポイズン」修練が";
				mes "３以上になれば習得可能だ。";
				next;
				mes "[名も無き者]";
				mes "「ベナムダスト」";
				mes "レッドジェムストーンを消費して";
				mes "指定一定地帯に毒を散布する";
				mes "技術だ。修練度が高いほど、";
				mes "汚染時間が長くなる。";
				next;
				mes "[名も無き者]";
				mes "「エンチャントポイズン」修練５";
				mes "レベルが必要だ。";
				next;
				mes "[名も無き者]";
				mes "「ベナムスプラッシャー」";
				mes "敵が毒状態になっていて、かつ";
				mes "HPが全快状態から三分の二";
				mes "以下に減っている時に使用でき、";
				mes "使用すると一定時間で対象が";
				mes "爆発する。";
				next;
				mes "[名も無き者]";
				mes "その時、周辺にも毒を撒き散らし、";
				mes "近くに居るものはダメージを受ける。";
				mes "習得が難しく、";
				mes "「ポイズンリアクト」５以上、";
				mes "「ベナムダスト」５以上の";
				mes "習得が必要となる。";
				next;
				mes "[名も無き者]";
				mes "以上がアサシンスキルの全てだ。";
				continue;
			case 2:
				mes "[名も無き者]";
				mes "うん…ステータスね…";
				mes "アサシンにとって一番重要な能力は";
				mes "なんと言っても俊敏性…";
				mes "すなわちAGIだろう…";
				next;
				mes "[名も無き者]";
				mes "暗殺時に敵に大きな被害を与えるには";
				mes "「力」 - STRも無視することは";
				mes "できないだろう。";
				next;
				mes "[名も無き者]";
				mes "急所を確実に突き、最も効率的に";
				mes "敵を仕留めるには「クリティカル」を";
				mes "決めることだが、「運」すなわち";
				mes "LUKに左右されることが大きい。";
				next;
				mes "[名も無き者]";
				mes "一概にどんな値が強いとは言えないが";
				mes "少しは参照になったかい？";
				mes "あとは自分の身を以って学んでくれ。";
				continue;
			case 3:
				mes "[名も無き者]";
				mes "じゃあテストを始めるよ。";
				mes "選択問題だ。";
				next;
				mes "[名も無き者]";
				mes "10問中 9問以上正解すれば合格。";
				mes "でも、どこで間違ったかは教えない。";
				next;
				mes "[名も無き者]";
				mes "ふふ…始めるよ…";
				set CHANGE_AS,1;
			}
			break;	//while文抜ける
		}
		break;	//最初のswitch文抜ける
	case 1:
		mes "[名も無き者]";
		mes "ふふ…まだ未練があったのかい？";
		next;
		mes "[名も無き者]";
		mes "よほど平和で安定した暮らしが";
		mes "嫌なようだね…";
		next;
		mes "[名も無き者]";
		mes "次も合格できないようなら、";
		mes "アサシンになるのなんて";
		mes "やめちゃいな！";
		next;
		if(select("平凡な泥棒で生きてゆく","転職テストを続けてくれ")==1) {
			mes "[名も無き者]";
			mes "ふ…そうだね。";
			mes "アサシンなど夢見ちゃだめだ。";
			mes "常に孤独な世界を味わうことに";
			mes "なるからね。";
			next;
			mes "[名も無き者]";
			mes "さ、外にでよう。";
			mes "そして砂嵐に負けず歩いて";
			mes "帰ってね…";
			close2;
			warp "moc_fild16.gat",206,241;
			end;
		}
		mes "[名も無き者]";
		mes "ククク…";
		mes "その孤独な旅、ボクがいつも側で";
		mes "見ているよ。地に横たわる時までね。";
		next;
		mes "[名も無き者]";
		mes "じゃあテストを始めるよ。";
		mes "選択問題だ。";
		next;
		mes "[名も無き者]";
		mes "10問中 9問以上正解すれば合格。";
		mes "でも、どこで間違ったかは教えない。";
		next;
		mes "[名も無き者]";
		mes "今度こそ合格するように。";
		break;
	default:
		mes "[名も無き者]";
		mes "クックック…";
		close;
	}
	//筆記試験ここから
	next;
	switch(rand(3)) {
	case 0:
		mes "[名も無き者]";
		mes "1. シーフの回避率増加スキルを";
		mes "最大まで修練した時の増加数値は？";
		next;
		if(select("30","40","160","20")==1)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "2. 次の中で、ハイディングを";
		mes "見破るモンスターは？";
		next;
		if(select("ワームテール","アンドレ","マミー","ソルジャースケルトン")==2)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "3. アサシンの二刀流で";
		mes "装備することができない組み合わせは？";
		next;
		if(select("マインゴーシュ + グラディウス","スティレット + マインゴーシュ","カタール + マインゴーシュ","ダマスカス + スティレット")==3)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "4. シーフ転職所に一番近い街は？";
		next;
		if(select("プロンテラ","ルティエ","アルベルタ","モロク")==4)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "5. AGIと関係ないカードは？";
		next;
		if(select("バフォメットジュニアカード","ウィスパーカード","雌盗蟲カード","雄盗蟲カード")==2)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "6. アサシンが他の職業より";
		mes "長けている点を述べろ。";
		next;
		if(select("すぐれた歌唱力","すぐれた演技力","すぐれたダンス力","すぐれた回避力")==4)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "7. JobLv50の時、アサシンが";
		mes "得るAGI加重値は？";
		next;
		if(select("7","8","9","10")==4)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "8. アサシンが装備できない";
		mes "アイテムは？";
		next;
		if(select("シルクローブ","ヘルム","ブーツ","ブローチ")==2)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "9. ノービスがシーフに";
		mes "転職する際必要なきのこは？";
		next;
		if(select("紅の毛ベトベトキノコ","赤毛ベトベトキノコ","紅の毛網キノコ","朱毛シイタケ")==3)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "10. 比較的アサシンには";
		mes "関係のないカードは？";
		next;
		if(select("ウィスパーカード","エルダーウィローカード","ソルジャースケルトンカード","コボルドカード")==2)
			set '@point,'@point+10;
		break;
	case 1:
		mes "[名も無き者]";
		mes "1. スロットの多いカタールは";
		mes "どのモンスターから手に入るか。";
		next;
		if(select("盗蟲","ペコペコ","デザートウルフ","鈍器コボルド")==3)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "2. スロットの多いジュルは";
		mes "どのモンスターから手に入るか。";
		next;
		if(select("マーティン","デザートウルフ","マリオネット","ミスト")==1)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "3. 属性武器を製造することが";
		mes "できる職業は？";
		next;
		if(select("商人","ブラックスミス","シーフ","プリースト")==2)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "4. 次の中でカタール系ではない";
		mes "武器は？";
		next;
		if(select("ジャマダハル","ジュル","カタール","グラディウス")==4)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "5. イズルードダンジョンの";
		mes "大部分のモンスターの属性は？";
		next;
		if(select("水属性","火属性","風属性","地属性")==1)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "6. 次の中でキューペットにする";
		mes "ことができないモンスターは？";
		next;
		if(select("ポポリン","ロッダフロッグ","スモーキー","ポイズンスポア")==2)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "7. 火属性短剣が最も効果的な";
		mes "モンスターを選べ。";
		next;
		if(select("短剣ゴブリン","メイスゴブリン","斧ゴブリン","ハンマーゴブリン")==4)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "8. 次の中で無属性の";
		mes "カタールを選びなさい。";
		next;
		if(select("爆炎のカタール","尖ってるいばらのカタール","デスナイフ","裏切り者")==4)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "9. 種族の違うモンスターを選べ。";
		next;
		if(select("ポリン","マスターリング","ゴーストリング","スポア")==3)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "10. 次の中でアンデッドではない";
		mes "モンスターはどれか。";
		next;
		if(select("ドレイク","メガロドン","スポア","カーリッツバーグ")==3)
			set '@point,'@point+10;
		break;
	case 2:
		mes "[名も無き者]";
		mes "1. グリムトゥースを習得するのに";
		mes "必要でないスキルは？";
		next;
		if(select("クローキング Lv 2","ソニックブロー Lv 5","カタール修練 Lv 4","右手修練 Lv 2")==4)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "2. エンチャントポイズンは、武器に";
		mes "属性を加えるスキルだ。";
		mes "次の中からその属性を選べ。";
		next;
		if(select("毒属性","地属性","闇属性","風属性")==1)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "3. 右手修練Lv4の効果は？";
		next;
		if(select("下降した攻撃力を 80% 回復","下降した攻撃力を 90% 回復","攻撃力を 90% 増加","攻撃力を 108% 増加")==2)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "4. ベナムダストに必要な";
		mes "アイテムは？";
		next;
		if(select("レッドブラッド","ブルージェムストーン","イエロージェムストーン","レッドジェムストーン")==4)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "5. エンチャントポイズンLv5まで";
		mes "修練すると習得が可能になるスキルは？";
		next;
		if(select("インベナム","ソニックブロー","ベナムスプラッシャー","ベナムダスト")==4)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "6. 次の中で人の目を盗んで";
		mes "移動することができるスキルは？";
		next;
		if(select("ハイディング","バックステップ","クローキング","砂まき")==3)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "7. ベナムスプラッシャーの";
		mes "使用条件でないものは？";
		next;
		if(select("対象が毒にかかっていること","レッドジェムストーン","対象のHPが全体の1/3以下")==1)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "8. 次の中で、バドンカード";
		mes "(火属性対象に20%追加ダメージ)";
		mes "を刺した武器で攻撃する時、一番";
		mes "効果を発揮するモンスターを選べ。";
		next;
		if(select("スチールチョンチョン","デビルチ","エルダーウィロー","バフォメット")==3)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "9. 短剣でダブルアタックが発動";
		mes "する時消費するSP量は？";
		next;
		if(select("15","0","10","54")==2)
			set '@point,'@point+10;
		mes "[名も無き者]";
		mes "10. イズルードダンジョンで";
		mes "効果的な武器は次のうちどれか。";
		next;
		if(select("ウィンドマインゴーシュ","アイスマインゴーシュ","アースマインゴーシュ","ファイアマインゴーシュ")==1)
			set '@point,'@point+10;
		break;
	}
	mes "[名も無き者]";
	mes "どうだった？問題は。";
	next;
	mes "[名も無き者]";
	mes "さて…点数は…";
	mes '@point+ "点…";
	if('@point < 90) {
		mes "不合格。勉強が足りないね。";
		next;
		mes "[名も無き者]";
		mes "そんなもんでアサシンになろうと";
		mes "思ったのかい？";
		mes "出直しておいで。";
		next;
		mes "[名も無き者]";
		mes "転職申込書の作成を担当する";
		mes "「カイ」に教わるとかね。";
		close2;
		warp "in_moc_16.gat",19,76;
		end;
	}
	mes "テストは合格だ。";
	next;
	mes "[名も無き者]";
	mes "まだ安心するな。";
	mes "テストはまだあるからね。";
	mes "奥に入れば次のテストが";
	mes "待っている。";
	set CHANGE_AS,2;
	close;
}


//==========================================
// 二次試験（実技１）
//------------------------------------------

in_moc_16.gat,19,162,0	script	バルカデー	139,3,1,{
	switch(CHANGE_AS) {
	case 0:
	case 1:
		mes "[バルカデー]";
		mes "テストを受けてきなさい。";
		mes "基本的な知識を無視するとは…";
		close2;
		warp "in_moc_16.gat",19,76;
		end;
	case 2:
		mes "[バルカデー]";
		mes strcharinfo(0)+ "…";
		mes "筆記試験はよくパスした…";
		next;
		mes "[バルカデー]";
		mes "うん…そのまま転職させてあげたい";
		mes "ところだが、基本を知らずに生きている";
		mes "人間があまりにも多くてね…";
		next;
		mes "[バルカデー]";
		mes "何より私達は自尊心を守らねば";
		mes "ならない。「砂漠の牙」である";
		mes "アサシンだというね…";
		mes "いつか私達の時代が来る。";
		mes "それまではひたすら待ち続けるんだ…";
		next;
		mes "[バルカデー]";
		mes "最近あまりにも精神の腐った奴が";
		mes "多い。";
		next;
		mes "[バルカデー]";
		mes "アサシンとしての自尊心や、";
		mes "昔してきただろう苦労はどこへ";
		mes "忘れたのか…";
		next;
		mes "[バルカデー]";
		mes "困ったものだ……";
		next;
		mes "[バルカデー]";
		mes "もし転職したら、アサシンとしての";
		mes "自尊心を忘れてはならない。";
		mes "キミの手にした武器に誓ってね…";
		next;
		mes "[バルカデー]";
		mes "それでは試験の説明を始める。";
		mes "暗殺の基本は迅速な判断。";
		next;
		mes "[バルカデー]";
		mes "すなわち、敵と味方を即座に判別";
		mes "しなければならない。";
		mes "よって…";
		next;
		mes "[バルカデー]";
		mes "試験の内容は多くの敵の中に";
		mes "紛れている";
		mes "「転職試験用見本」";
		mes "というやつを選んで倒せ。";
		next;
		mes "[バルカデー]";
		mes "「転職試験用見本」の数は６体。";
		mes "似た姿の奴が多いから";
		mes "気をつけるんだな。";
		mes "ミスをおかしたらまた初めからだ。";
		next;
		mes "[バルカデー]";
		mes "控え室で待機していれば、";
		mes "試験場に送ってあげるよ。";
		next;
		mes "[バルカデー]";
		mes "試験は一人ずつ受けるのが原則。";
		mes "先に入った者がいる場合は、";
		mes "その者の試験が終わるまで待機";
		mes "してもらう。いいね。";
		close;
	default:
		mes "[バルカデー]";
		mes "失敗しても諦めるな。";
		mes "まあ……引き返すのは自由だが。";
		mes "どうする？";
		next;
		if(select("まだこれからだ","転職をあきらめる")==1) {
			mes "[バルカデー]";
			mes "ふふ……";
			mes "もう一度言うが";
			mes "「転職試験用見本」";
			mes "を６体倒さなければならない。";
			mes "それでは健闘を祈る。";
			close;
		}
		mes "[バルカデー]";
		mes "そうか。";
		mes "よく休んでから来な。";
		close2;
		warp "in_moc_16.gat",19,13;
		end;
	}
}

//==============================================================
in_moc_16.gat,21,165,2	script	転職試験案内員::AS_ChatRoom	725,{
	end;
OnInit:
	waitingroom "転職試験場控室",10,"AS_ChatRoom::OnStart",1;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid '@accid;
	if(attachrid('@accid)) {
		set $@as_tester$,strcharinfo(0);	//挑戦者の名前
		set CHANGE_AS,3;
		warp "in_moc_16.gat",66,151;
		donpcevent "AS_Test2nd::OnStart";
	}
	else
		enablewaitingroomevent;
	end;
}

//==============================================================
in_moc_16.gat,0,0,0	script	AS_Test2nd	-1,{
OnStart:
	set 'count,6;
	disablenpc "#AS_Warp";
	monster "in_moc_16.gat",62,161,"転職試験用見本",1002,1,"AS_Test2nd::OnKillOK"; 
	monster "in_moc_16.gat",85,169,"転職試験用見本",1063,1,"AS_Test2nd::OnKillOK";
	monster "in_moc_16.gat",88,152,"転職試験用見本",1002,1,"AS_Test2nd::OnKillOK";
	monster "in_moc_16.gat",90,143,"転職試験用見本",1113,1,"AS_Test2nd::OnKillOK";
	monster "in_moc_16.gat",74,167,"転職試験用見本",1031,1,"AS_Test2nd::OnKillOK";
	monster "in_moc_16.gat",77,173,"転職試験用見本",1002,1,"AS_Test2nd::OnKillOK";
	monster "in_moc_16.gat",62,161,"転職試験用モンスター",1063,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",85,169,"転職試験用モンスター",1031,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",79,174,"実技試験用見本",1113,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",85,156,"転職試験用モンスター",1063,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",74,171,"転職試験モンスター",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",68,173,"転職試験用ダミー",1113,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",65,158,"戦闘試験用見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",60,158,"転職実験用見本",1113,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",64,169,"転職試験の時の見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",71,173,"転職試験見本",1063,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",77,172,"実技試験用見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",76,172,"転職試験用サンプル",1063,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",75,172,"転職試験用モンスター",1113,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",67,167,"実技試験用見本",1063,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",86,170,"転職実験用見本",1031,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",86,171,"転職見本用試験",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",86,173,"実技試験用見本",1063,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",85,170,"戦闘試験モンスター",1031,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",89,156,"見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",89,156,"殉職試験用見本",1113,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",89,156,"戦闘試験用見本",1063,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",89,156,"試験見本勇者職",1113,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",89,156,"転職試験見本",1031,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",83,169,"イビルドルイド",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",63,158,"ドッペルゲンガー",1063,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",63,157,"転職試験見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",64,159,"戦闘準備用見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",63,159,"転職準備用見本",1063,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",63,159,"弓手転職用見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",63,159,"剣士転職用見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",83,148,"泥棒転職用見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",82,148,"アコライト転職用見本",1002,1,"AS_Test2nd::OnKillNG";
	monster "in_moc_16.gat",84,148,"商人転職用見本",1002,1,"AS_Test2nd::OnKillNG";
	initnpctimer;
	end;
OnKillOK:
	set 'count,'count-1;
	if('count) {
		announce "監視者: まだだ…頑張れ…",9;
		end;
	}
	stopnpctimer;
	announce "監視者: よし、よくやった…合格だ！",9;
	announce "門番: 座標 87 137 次の転職場への扉が開きました",9;
	killmonster "in_moc_16.gat","All";
	enablenpc "#AS_Warp";
	initnpctimer "AS_Test3rd";	//三次試験用タイマー始動
	end;
OnKillNG:
	stopnpctimer;
	announce "監視者: " +$@as_tester$+ " !! ミスをしたな、戻ってこい。",9;
	areawarp "in_moc_16.gat",60,136,93,177,"in_moc_16.gat",19,161;
	killmonster "in_moc_16.gat","All";
	enablewaitingroomevent "AS_ChatRoom";
	end;
OnTimer1000:
	announce "監視者: 試験開始だ",9;
	end;
OnTimer2000:
	announce "監視者: 言ったとおり、モンスターの名前が「転職試験用見本」という奴だけを倒せ！",9;
	end;
OnTimer3000:
	announce "監視者: 試験の目的は、より迅速正確に対象を判別することだ。",9;
	end;
OnTimer4000:
	announce "監視者: それでは、持ち時間を３分与える。時間の経過は１分ごとに伝える。",9;
	end;
OnTimer5000:
	announce "監視者: よし…スタートだ。残り３分！",9;
	end;
OnTimer65000:
	announce "監視者: ２分だ。「転職試験用見本」を倒せ！",9;
	end;
OnTimer125000:
	announce "監視者: 残り１分！",9;
	end;
OnTimer180000:
	announce "監視者: 試験終了 5 秒前",9;
	end;
OnTimer181000:
	announce "監視者: 試験終了 4 秒前",9;
	end;
OnTimer182000:
	announce "監視者: - 3 -",9;
	end;
OnTimer183000:
	announce "監視者: - 2 -",9;
	end;
OnTimer184000:
	announce "監視者: - 1 -",9;
	end;
OnTimer185000:
	announce "監視者: 終了",9;
	end;
OnTimer186000:
	announce "監視者: 時間になったがクリアできなかったか…。また次頑張れ。",9;
	areawarp "in_moc_16.gat",60,136,93,177,"in_moc_16.gat",19,161;
	end;
OnTimer189000:
	stopnpctimer;
	killmonster "in_moc_16.gat","All";
	enablewaitingroomevent "AS_ChatRoom";
	end;
}

//==============================================================
in_moc_16.gat,87,137,0	script	#AS_Warp	45,2,1,{
	stopnpctimer "AS_Test2nd";
	warp "in_moc_16.gat",87,102;
	killmonster "in_moc_16.gat","All";
	enablewaitingroomevent "AS_ChatRoom";
	end;
}

//==============================================================
in_moc_16.gat,68,158,0	script	#AS_Abyss	139,0,0,{
	announce "監視者: " +$@as_tester$+ "様、落とし穴に落ちました。",9;
	warp "in_moc_16.gat",19,161;
	stopnpctimer "AS_Test2nd";
	killmonster "in_moc_16.gat","All";
	enablewaitingroomevent "AS_ChatRoom";
	end;
}

in_moc_16.gat,68,159,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,69,158,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,69,159,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,64,162,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,64,163,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,65,162,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,65,163,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,62,168,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,62,169,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,63,168,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,63,169,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,66,170,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,66,171,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,67,170,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,67,171,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,64,174,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,64,175,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,65,174,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,65,175,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,72,174,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,72,175,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,73,174,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,73,175,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,72,167,0		duplicate(#AS_Abyss)	落とし穴	139,0,1
in_moc_16.gat,73,167,0		duplicate(#AS_Abyss)	落とし穴	139,0,1
in_moc_16.gat,72,169,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,73,169,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,78,168,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,78,169,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,79,168,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,79,169,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,81,172,0		duplicate(#AS_Abyss)	落とし穴	139,1,0
in_moc_16.gat,81,173,0		duplicate(#AS_Abyss)	落とし穴	139,1,0
in_moc_16.gat,83,172,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,83,173,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,88,174,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,88,175,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,89,174,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,89,175,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,86,166,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,86,167,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,87,166,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,87,167,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,90,164,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,90,165,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,91,164,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,91,165,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,86,160,0		duplicate(#AS_Abyss)	落とし穴	139,2,0
in_moc_16.gat,86,161,0		duplicate(#AS_Abyss)	落とし穴	139,2,0
in_moc_16.gat,89,160,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,89,161,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,86,154,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,86,155,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,87,154,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,87,155,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,84,150,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,84,151,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,85,150,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,85,151,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,90,150,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,90,151,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,91,150,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,91,151,0		duplicate(#AS_Abyss)	落とし穴	139,0,0

in_moc_16.gat,86,146,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,86,147,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,87,146,0		duplicate(#AS_Abyss)	落とし穴	139,0,0
in_moc_16.gat,87,147,0		duplicate(#AS_Abyss)	落とし穴	139,0,0


//==========================================
// 三次試験（実技２）
//------------------------------------------

in_moc_16.gat,89,98,2	script	ダンテ	118,5,1,{
	end;
OnTouch:
	if(CHANGE_AS != 4) {
		mes "[ダンテ]";
		mes "私はこの試験を見ている";
		mes "「ダンテ」という。";
		mes "この試験で見るのは、お前の";
		mes "回避能力だ。";
		next;
		mes "[ダンテ]";
		mes "ハイディングを適度に使う";
		mes "ことも許されている。";
		next;
		mes "[ダンテ]";
		mes "目的は反対側の入口の「バルカデー」";
		mes "のところに行くこと。";
		mes "多くのモンスターの間を抜けて、";
		mes "向こう側まで行くんだ。";
		mes "倒さずにな。";
		next;
		mes "[ダンテ]";
		mes "途中で気を失ったり、逃げ出した場合は";
		mes "ここへ戻ってくることになる。";
		mes "それでは開始だ。健闘を祈る。";
		set CHANGE_AS,4;
		donpcevent "AS_Test3rd::OnStart";
		close;
	}
	mes "[ダンテ]";
	mes "うん…気を失ったみたいだな。";
	mes "よし、回復してやる。";
	percentheal 100,100;
	next;
	mes "[ダンテ]";
	mes "しかし、気を失うほどのものか？";
	mes "また転職を試みるのはいいが、";
	mes "無理なようなら今のうちに言ってくれ。";
	next;
	if(select("再挑戦だ","まだ無理なようだ…")==1) {
		mes "[ダンテ]";
		mes "そうか頑張ってくれ。";
		mes "バルカデーは近くにいるはずだ。";
		close;
	}
	mes "[ダンテ]";
	mes "そうか…それではまた次の機会に。";
	next;
	mes "[ダンテ]";
	mes "街に帰ったら記録するのを";
	mes "忘れないように。";
	close2;
	stopnpctimer "AS_Test3rd";
	set CHANGE_AS,2;
	announce "ダンテ: " +$@as_tester$+ "が転職をあきらめた。次の者入りなさい。",9;
	warp "in_moc_16.gat",18,14;
	killmonster "in_moc_16.gat","All";
	enablewaitingroomevent "AS_ChatRoom";
	end;
}

//==============================================================
in_moc_16.gat,0,0,0	script	AS_Test3rd	-1,{
OnStart:
	monster "in_moc_16.gat",81,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",82,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",83,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",84,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",85,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",86,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",87,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",88,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",89,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",90,77,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",75,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",77,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",79,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",81,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",83,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",85,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",90,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",92,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",94,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",96,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",98,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",100,56,"マミー",1041,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",76,62,"ヒドラ",1068,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",76,65,"ヒドラ",1068,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",79,62,"ヒドラ",1068,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",79,65,"ヒドラ",1068,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",96,62,"ヒドラ",1068,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",96,65,"ヒドラ",1068,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",99,62,"ヒドラ",1068,1,"AS_Test3rd::OnKilled";
	monster "in_moc_16.gat",99,65,"ヒドラ",1068,1,"AS_Test3rd::OnKilled";
	end;
OnKilled:
	announce "ダンテ: モンスターを倒してしまったら",9;
	announce "ダンテ: 最初からやり直しだ。",9;
	areawarp "in_moc_16.gat",64,46,111,105,"in_moc_16.gat",87,102;
	killmonster "in_moc_16.gat","All";
	enablewaitingroomevent "AS_ChatRoom";
	end;
OnTimer240000:
	stopnpctimer;
	areawarp "in_moc_16.gat",60,136,93,177,"in_moc_16.gat",19,161;
	areawarp "in_moc_16.gat",64,46,111,105,"in_moc_16.gat",19,161;
	killmonster "in_moc_16.gat","All";
	enablewaitingroomevent "AS_ChatRoom";
	end;
}

//==============================================================
in_moc_16.gat,87,48,1	script	バルカデー	725,2,2,{
	end;
OnTouch:
	killmonster "in_moc_16.gat","All";
	mes "[バルカデー]";
	mes "よし、来たな！";
	mes "いよいよ最終試験だ。";
	close2;
	stopnpctimer "AS_Test3rd";
	set @as_step,0;
	warp "in_moc_16.gat",181,183;
	enablewaitingroomevent "AS_ChatRoom";
	end;
}


//==========================================
// 最終試験
//------------------------------------------

in_moc_16.gat,182,169,0	script	#門番	45,1,1,{
	if(@as_step < 2) {
		set @as_step,@as_step+1;
		warp "in_moc_16.gat",181,183;
		end;
	}
	announce "門番: " +strcharinfo(0)+ "様がギルドマスターの部屋に入りました",9;
	hideonnpc "ヒュイ#AS";
	hideonnpc "カイ#AS";
	hideonnpc "名も無き者#AS";
	hideonnpc "バルカデー#AS";
	hideonnpc "監視者#AS";
	hideonnpc "ダンテ#AS";
	hideonnpc "補佐官マロビッツ#AS";
	savepoint "in_moc_16.gat",167,110;
	warp "SavePoint",0,0;
	end;
}

//==============================================================
in_moc_16.gat,167,110,0	script	アサシン迷宮案内	139,3,1,{
	mes "[ギルドマスター]";
	mes "ふむ…よく来たな。";
	mes "ここは「ギルドマスターの部屋」";
	mes "アサシンギルドの最深部だ。";
	next;
	mes "[ギルドマスター]";
	mes "私の居場所がわからないように迷宮に";
	mes "なっている。";
	mes "そして試験についてだが…";
	mes "私の所まで来てほしい。";
	mes "たまに侵入者があるためこのような";
	mes "造りにした。";
	next;
	mes "[ギルドマスター]";
	mes "それではまた後で会おう…";
	close;
}

in_moc_16.gat,170,90,0	script	アサシン迷宮案内#AS	139,1,1,{
	mes "[ギルドマスター]";
	mes "そこは入り組んだ道だ…";
	mes "他を進むように。";
	close;
}

in_moc_16.gat,160,85,0	duplicate(アサシン迷宮案内#AS)	アサシン迷宮案内	139,1,1

in_moc_16.gat,180,101,0	script	アサシン迷宮案内	139,1,1,{
	mes "[ギルドマスター]";
	mes "そっちではないと思うが…";
	close;
}

in_moc_16.gat,186,107,0	script	アサシン迷宮案内	139,1,1,{
	mes "[ギルドマスター]";
	mes "そっちではないと思うが…";
	close;
}

in_moc_16.gat,149,95,0	script	アサシン迷宮案内	139,1,1,{
	mes "[ギルドマスター]";
	mes "うむ、だいたいの道筋を";
	mes "理解したようだな。";
	close;
}

in_moc_16.gat,149,95,0	script	アサシン迷宮案内	139,0,0,{
	mes "[ギルドマスター]";
	mes "だいぶ近づいたな。";
	mes "お前の気配が感じられるぞ。";
	close;
}

in_moc_16.gat,175,89,0	script	アサシン迷宮案内	139,1,1,{
	mes "[ギルドマスター]";
	mes "そこは補佐官の所に通じる。";
	mes "何か補佐官に用でもあるのか？";
	close;
}

in_moc_16.gat,153,85,0	script	アサシン迷宮案内	139,1,1,{
	mes "[ギルドマスター]";
	mes "そこは入り組んだ道だ…";
	mes "少し戻れば良い。";
	mes "柱で邪魔された道だから、";
	mes "回りこんで進むように。";
	close;
}

//==============================================================
in_moc_16.gat,186,81,0	script	ギルドマスター補佐官	55,{
	mes "[補佐官マロビッツ]";
	mes "私は転職試験には関わりが";
	mes "ありません。";
	mes "転職についてはあちらにいらっしゃる";
	mes "ギルドマスター様にご依頼ください。";
	close;
}

//==============================================================
in_moc_16.gat,149,80,4	script	ギルドマスター	106,1,1,{
	end;
OnTouch:
	mes "[ギルドマスター]";
	mes "良く来た。道が複雑で苦労をかけたな。";
	mes "先ほど報告書が上がってきたが、";
	mes "なかなか見所があるシーフだそうだな。";
	mes "お前のように鍛え抜かれた奴は";
	mes "将来が楽しみだ。";
	next;
	mes "[ギルドマスター]";
	mes "さて、これからいくつか質問をするが";
	mes "お前が普段考えているように答えて";
	mes "くれれば良いから、楽にしてくれ。";
	next;
	mes "[ギルドマスター]";
	mes "まず…アサシンに重要なことは何か？";
	next;
	switch (select("より強い力","プライド(自尊心)","絶え間無い修練")) {
	case 1:
		mes "[ギルドマスター]";
		mes "より強い力といえば…確かに";
		mes "シーフに比べアサシンは強いと言える。";
		next;
		mes "[ギルドマスター]";
		mes "しかし、その強さは何のために";
		mes "必要なのだ？例えば復讐のためか…";
		mes "それとも他の何かのためか？";
		next;
		mes "[ギルドマスター]";
		mes "アサシンの力を手に入れたら";
		mes "どんな利があるだろうか？";
		next;
		switch (select("復讐を果たせる","金儲けがしやすくなる","より多くの場所に行ける")) {
			case 1:
				mes "[ギルドマスター]";
				mes "復讐か…";
				mes "そう…我々のたいていは恨み";
				mes "というものを持っている。";
				next;
				mes "[ギルドマスター]";
				mes "しかし我々は感情に左右されることなく";
				mes "自分に課せられた任務を忠実に遂行";
				mes "しなければならない。";
				next;
				mes "[ギルドマスター]";
				mes "アサシンになりたくば感情を消すことだ。";
				break;
			case 2:
				mes "[ギルドマスター]";
				mes "…たしかに生きていくには金が必要";
				mes "だが…それはアサシンとしての";
				mes "生き方に望むべきものではない。";
				break;
			case 3:
				mes "[ギルドマスター]";
				mes "良い考えだ。色々な場所を覚え、";
				mes "観察することは任務の成功をより";
				mes "高めることになる。";
				next;
				mes "[ギルドマスター]";
				mes "しかし、いくら仲間達ととはいえ、";
				mes "大勢で旅をするようなことは控えて";
				mes "ほしい。目立つことは避けなければ";
				mes "ならないからだ…";
				break;
		}
		break;
	case 2:
		mes "[ギルドマスター]";
		mes "プライドか…";
		mes "うちの者がそう言っていたか？";
		next;
		mes "[ギルドマスター]";
		mes "ふん…それはどういう根拠があってか？";
		mes "お前がアサシンの何に惹かれたかは";
		mes "知らないが…";
		next;
		mes "[ギルドマスター]";
		mes "奴らの大部分は、ある時期に";
		mes "大きな苦労を共にしてきた。";
		mes "だからよくわかる。";
		mes "では、お前にはなぜプライドが";
		mes "必要なのだ？";
		next;
		switch (select("一人で生きるには必要","金儲けのために必要","見た目が良いから")) {
			case 1:
				mes "[ギルドマスター]";
				mes "そう…我々は孤独な存在…";
				mes "どこに在っても常に一人だ。";
				next;
				mes "[ギルドマスター]";
				mes "しかし、我々にも仲間というものが";
				mes "ある。あまり深く入れ込み過ぎると";
				mes "危険もまとわりつくが、良きパートナー";
				mes "が居れば目的の達成もよりたやすく";
				mes "なるだろう…";
				break;
			case 2:
				mes "[ギルドマスター]";
				mes "…たしかに生きていくには金が必要";
				mes "だが…それはアサシンとしての";
				mes "生き方に望むべきものではない。";
				break;
			case 3:
				mes "[ギルドマスター]";
				mes "見かけにこだわるあまりものの";
				mes "本質を見逃すか…";
				mes "そんな精神の弱い者はアサシン";
				mes "としてふさわしくない。";
				break;
		}
		break;
	case 3:
		mes "[ギルドマスター]";
		mes "修練か…";
		mes "お前はすでに立派なシーフに";
		mes "見えるが、尚もって修練を積む理由は";
		mes "何か？";
		next;
		mes "[ギルドマスター]";
		mes "シーフならいざしらず、アサシンは";
		mes "己を律して時に慎んだ行動を取らねば";
		mes "ならない。たまに、力に対する欲望に";
		mes "負け、自分を制御できなくなる若者も";
		mes "いるのだ…";
		next;
		mes "[ギルドマスター]";
		mes "それでは今の何に満足できずに";
		mes "修練を積むというのだ？";
		next;
		switch (select("技術","目標","精神")) {
			case 1:
				mes "[ギルドマスター]";
				mes "技術はアサシンになればある程度";
				mes "身につくものだ。それ自体に";
				mes "最高の価値があるわけではない。";
				mes "アサシンになっても満足できるか";
				mes "わからぬぞ。";
				break;
			case 2:
				mes "[ギルドマスター]";
				mes "そうか…絶えず新たな目標を掲げる";
				mes "のは良いことだ…しかし…";
				mes "今はアサシンになることで一杯だが、";
				mes "いつかは変わるかもしれないぞ。";
				break;
			case 3:
				mes "[ギルドマスター]";
				mes "そうだな。常に強固な精神を持つのは";
				mes "重要なことだ。身体と共に精神面も鍛え";
				mes "ながら、なかなか精神面を強めるのは";
				mes "難しいのだ。";
				next;
				mes "[ギルドマスター]";
				mes "アサシンという職業は、技だけではなく";
				mes "精神も一定に保たねばならない。";
				mes "それでこそ体得した技術を余すことなく";
				mes "発揮できるからな。";
				break;
		}
		break;
	}
	next;
	mes "[ギルドマスター]";
	mes "お前はよく考えているな。";
	mes "中には何も考えずにアサシンに";
	mes "なろうという奴も居るんでな…";
	next;
	mes "[ギルドマスター]";
	mes "そういった奴らが問題を起こし";
	mes "我々ギルドの顔に泥を塗る。";
	next;
	mes "[ギルドマスター]";
	mes "これはお前も言えることだが、";
	mes "一度アサシンになったら二度と";
	mes "シーフに戻ることはできない。";
	mes "アサシンとしての義務と責任は";
	mes "この後ずっと負ってもらうことになる。";
	next;
	mes "[ギルドマスター]";
	mes "これからアサシンになったら";
	mes "まず何をするか？";
	next;
	switch (select("すぐに戦闘をする","私を待つ人々のところへ","アサシンについて調べる")) {
	case 1:
		mes "[ギルドマスター]";
		mes "戦闘だと？それで？";
		next;
		switch (select("早く成長したい","アサシンとしての自分の技を試す","シーフでは行きにくい場所に行く")) {
			case 1:
				mes "[ギルドマスター]";
				mes "あまり成長を焦ると基礎が緩み、";
				mes "特に精神面の修練が疎かになる";
				mes "だろう。基礎ができていないと咄嗟の";
				mes "事態に反応が遅れることがある。";
				mes "一瞬の判断が命取りになるアサシン";
				mes "こそ基礎を固めるべきだ。";
				break;
			case 2:
				mes "[ギルドマスター]";
				mes "自分を試すのは良いことだ。";
				mes "進化した自分の能力を試すのは";
				mes "良いことだが、アサシンとしての";
				mes "心構えは忘れるなよ。";
				break;
			case 3:
				mes "[ギルドマスター]";
				mes "良いことだ。新たな地へ赴けば";
				mes "また新たな発見があるだろう。";
				mes "しかし、アサシンになってもその";
				mes "人間の本質が変わるとは限らない。";
				next;
				mes "[ギルドマスター]";
				mes "初めはあまり無理をせず、少しずつ";
				mes "行動範囲を広げるのが良いだろう。";
				break;
		}
		break;
	case 2:
		mes "[ギルドマスター]";
		mes "誰が待っているのだ？";
		next;
		switch (select("仲間達だ","ギルド員達だ","恋人だ")) {
			case 1:
				mes "[ギルドマスター]";
				mes "そうか。彼らもお前のことを";
				mes "我が事のように喜ぶだろう。";
				mes "孤独の中でも仲間を思う心は";
				mes "忘れるなよ。";
				break;
			case 2:
				mes "[ギルドマスター]";
				mes "生死を共にする仲間か…良いな。";
				mes "アサシンとして、仲間の影となり";
				mes "よく助けてやることだ。";
				break;
			case 3:
				mes "[ギルドマスター]";
				mes "愛する人のためだと？";
				mes (Sex? "彼": "彼女")+ "の影となり、常に見守るというのか…";
				next;
				mes "[ギルドマスター]";
				mes "大事にすることだ…";
				mes "だがしかし、その甘さが我々の";
				mes "ような職には命取りとなる。";
				mes "お前の人生だ。悔いの無いようにな…";
				break;
		}
		break;
	case 3:
		mes "[ギルドマスター]";
		mes "良い姿勢だ。";
		mes "どんなことを調べる？";
		next;
		switch (select("アサシンに向いている場所を","ギルドの成長について","アサシンで収入を上げる方法を")) {
			case 1:
				mes "[ギルドマスター]";
				mes "この世で楽な場所・辛い場所は";
				mes "たしかに存在する。";
				mes "しかしアサシンというのはどんな";
				mes "環境下でも任務を遂行するために";
				mes "柔軟に対応できなければならない。";
				break;
			case 2:
				mes "[ギルドマスター]";
				mes "外には多くの我々の仲間がいる。";
				mes "奴らから学ぶことがあるはずだ。";
				next;
				mes "[ギルドマスター]";
				mes "そしてそこで得る知識と経験を";
				mes "元に土台を創り上げ、ギルドの";
				mes "発展に寄付してほしい。";
				mes "そしてお前もある程度の域に";
				mes "達すれば、逆に下の者の面倒を";
				mes "見る機会が来るはずだ。";
				break;
			case 3:
				mes "[ギルドマスター]";
				mes "…アサシンは金のために";
				mes "存在するのではない…";
				mes "もう少しアサシンの責務という";
				mes "ものを良く考えるべきだ。";
				break;
		}
		break;
	}
	next;
	mes "[ギルドマスター]";
	mes "お前との会話はなかなか楽しかった。";
	mes "私も昔を思い出したよ…";
	next;
	mes "[ギルドマスター]";
	mes "ふむ…それでは奴らを収集するか。";
	next;
	announce "ギルドマスター: " +strcharinfo(0)+ "のアサシン転職試験に関わった者は私の元集結せよ",9;
	mes "[ギルドマスター]";
	mes strcharinfo(0)+ "の";
	mes "アサシン転職試験に関わった者は";
	mes "私の元集結せよ";
	next;
	mes "[ギルドマスター]";
	mes "すぐに来い！";
	next;
	hideoffnpc "ヒュイ#AS";
	hideoffnpc "カイ#AS";
	hideoffnpc "名も無き者#AS";
	hideoffnpc "バルカデー#AS";
	hideoffnpc "監視者#AS";
	hideoffnpc "ダンテ#AS";
	hideoffnpc "補佐官マロビッツ#AS";
	mes "[名も無き者]";
	mes "お呼びですか？";
	next;
	mes "[ギルドマスター]";
	mes strcharinfo(0)+ "の転職試験を";
	mes "担当した者の意見を聞きたくてな……";
	mes "どうか？";
	next;
	mes "[名も無き者]";
	mes "あいつなら良いね。ククク…";
	next;
	mes "[ギルドマスター]";
	mes "「名も無き者」お前は賛成だな。";
	mes "ヒュイは？";
	next;
	if(JobLevel >= 50) {
		mes "[ヒュイ]";
		mes "最近見た中で一番根性がある";
		mes "シーフでした。";
		next;
		mes "[ヒュイ]";
		mes "賛成です。";
		mes "それでは私はお先に失礼します。";
		mes "席に戻らなければなりませんので…";
		mes "あ、マスター…私の代わりに何か";
		mes "プレゼントでも与えてやってください。";
		next;
		mes "[ギルドマスター]";
		mes "うむ。約束しよう。";
	}
	else {
		mes "[ヒュイ]";
		mes "まぁ基本はできてますよ。";
		mes "賛成です。";
		mes "それではお先に失礼します。";
		mes "席に戻らなければなりませんので…";
		next;
		mes "[ギルドマスター]";
		mes "うむ、そうしてくれ。";
	}
	next;
	mes "[ギルドマスター]";
	mes "では「監視者」お前はどうか？";
	next;
	hideonnpc "ヒュイ#AS";
	mes "[監視者]";
	mes "一応通過したので合格扱いです。";
	next;
	mes "[ギルドマスター]";
	mes "うむ、皆賛成のようだな。";
	mes "私もこの者については気に入った。";
	next;
	mes "[ギルドマスター]";
	mes "そう…アサシンには孤独という";
	mes "訓練が一生課せられる。";
	mes "強い己を持ち、生きてゆけ。";
	next;
	mes "[ギルドマスター]";
	mes "ん…話が長くなったな。";
	if(JobLevel >= 50) {
		mes "ここに以下の武器がある。";
		mes "ジュル カタール";
		mes "マインゴーシュ グラディウス";
		mes "以上全て私が愛用した武器だ。";
		next;
		switch(select("ジュル","カタール","マインゴーシュ","グラディウス")) {
			case 0: getitem 1251,1; break;
			case 1: getitem 1253,1; break;
			case 2: getitem 1208,1; break;
			case 3: getitem 1220,1; break;
		}
		mes "[ギルドマスター]";
		mes "これ一つあれば十分という";
		mes "時代もあったな…";

	}
	else {
		mes "まずはこれを受け取れ。";
		next;
		switch(rand(4)) {
			case 0: getitem 1207,1; break;
			case 1: getitem 1219,1; break;
			case 2: getitem 1250,1; break;
			case 3: getitem 1252,1; break;
		}
	}
	set CHANGE_AS,5;
	next;
	savepoint "morocc.gat",100,101;
	getitem 1008,1;
	mes "[ギルドマスター]";
	mes "では、合格の印を与えるから";
	mes "入口のベテランアサシン・ヒュイの";
	mes "所まで戻れ。";
	mes "ヒュイが実際に転職をさせてくれる";
	mes "だろう。";
	next;
	mes "[ギルドマスター]";
	mes "ここに " +strcharinfo(0)+ " …";
	mes "暗殺者としての道を歩まんとす…";
	mes "その先寂しく孤独な道になろうとも";
	mes "己の意志だけは忘れぬよう…";
	next;
	mes "[ギルドマスター]";
	mes "よし、皆戻ってよし！";
	mes "お前も入り口まで戻してやる。";
	hideonnpc "カイ#AS";
	hideonnpc "名も無き者#AS";
	hideonnpc "バルカデー#AS";
	hideonnpc "監視者#AS";
	hideonnpc "ダンテ#AS";
	hideonnpc "補佐官マロビッツ#AS";
	close2;
	warp "in_moc_16.gat",17,19;
	end;
}

in_moc_16.gat,156,87,2	script	ヒュイ#AS		55,{}
in_moc_16.gat,156,85,2	script	カイ#AS			730,{}
in_moc_16.gat,156,83,2	script	名も無き者#AS		106,{}
in_moc_16.gat,156,81,2	script	バルカデー#AS		725,{}
in_moc_16.gat,156,79,2	script	監視者#AS		118,{}
in_moc_16.gat,156,77,2	script	ダンテ#AS		118,{}
in_moc_16.gat,156,75,2	script	補佐官マロビッツ#AS	55,{}
