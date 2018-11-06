//= Auriga Script ==============================================================
// Ragnarok Online Toy Factory in Nightmare Script	by refis
//==============================================================================

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
xmas.gat,237,303,3	script	キャサリンゼータ	10032,{
	if(BaseLevel < 110) {
		mes "[キャサリンゼータ]";
		mes "あ！　あの、待って下さい！";
		mes "ここはあなたのように";
		mes "経験が浅い方が挑戦するには";
		mes "危険な場所なのです。";
		next;
		mes "[キャサリンゼータ]";
		mes "中に入りたいのであれば、";
		mes "もう少し強くなってからが";
		mes "良いかと思います……。";
		mes "そ……そうですね、";
		mes "だいたい^ff0000BaseLv110^000000くらいあれば";
		mes "大丈夫かなっと……。";
		close;
	}
	if(checkquest(12330) == 0) {
		mes "[キャサリンゼータ]";
		mes "そ……そんなに見ないでください。";
		mes "今はこんな顔ですけど";
		mes "元々は違うんです……。";
		mes "ちゃんと、目とかも";
		mes "あったんですよ……。";
		next;
		mes "^0000ff‐目の前にいる少女は、";
		mes "　今にも泣きだしそうな声で";
		mes "　そういいながら、";
		mes "　本来は瞳があったであろう";
		mes "　空洞があなたを見つめてる‐^000000";
		next;
		menu "どうしてそんな顔になったんですか？",-;
		mes "[キャサリンゼータ]";
		mes "話すと少し長くなりますけど……";
		mes "大丈夫……でしょうか？";
		next;
		menu "話を続けて下さい",-;
		mes "[キャサリンゼータ]";
		mes "ど……何処から話せばいいのかな。";
		mes "街の話から始めた方がいいのかな……。";
		next;
		mes "^0000ff‐一度ため息を吐き出した少女は";
		mes "　昔話を話す詩人のような声で話始めた‐^000000";
		next;
		mes "[キャサリンゼータ]";
		mes "この街にはおもちゃ工場が";
		mes "ありますけど……実はその工場の中に、";
		mes "作業員しか知らない別の工場が";
		mes "あるんです。";
		mes "そして……私もそこに勤める";
		mes "職員の一人でした。";
		next;
		mes "[キャサリンゼータ]";
		mes "はじめは幸せでした。";
		mes "仕事が終われば街にみんな集まって、";
		mes "お菓子と温かい紅茶を飲みながら";
		mes "おしゃべりをしたり。";
		mes "毎日、充実していました。";
		next;
		menu "今の雰囲気はそうでもないようだけど……",-;
		mes "[キャサリンゼータ]";
		mes "はい……。";
		mes "いつまでもおもちゃを包装するだけで、";
		mes "生活を維持することはできません。";
		mes "結局、作業員は少しずつ";
		mes "工場からいなくなってしまい、";
		mes "工場の経営は厳しくなっていきました。";
		next;
		mes "[キャサリンゼータ]";
		mes "結局、最後まで残ったのは";
		mes "人形職人のお爺さんと、";
		mes "彼のもとで、弟子として";
		mes "人形作りを手伝いつつ";
		mes "働いていた、私だけに";
		mes "なりました……。";
		next;
		mes "^0000ff‐彼女の感情の微妙な震えで";
		mes "　白い顎が揺れているのが感じられる‐^000000";
		next;
		menu "続けて話を聞く",-;
		mes "[キャサリンゼータ]";
		mes "工場の閉鎖が決定した日。";
		mes "人形職人は最後に作った人形に";
		mes "服を着せながら涙を流していました。";
		next;
		mes "[キャサリンゼータ]";
		mes "もうこれで人形を作ることは";
		mes "永遠にないと思っていたようです。";
		mes "……いまでも昨日のことみたいに";
		mes "思い出すことができます……。";
		next;
		mes "[キャサリンゼータ]";
		mes "その最後の人形に^0000ffセリーヌ・キミ^000000という";
		mes "名前を付けて、人形職人は";
		mes "工場のすべての作業場を";
		mes "止めました……。";
		next;
		menu "人形に名前を？",-;
		mes "[キャサリンゼータ]";
		mes "人形職人にとって人形は";
		mes "ある意味、子供のようなもの。";
		mes "命を吹き込むつもりで真剣に";
		mes "取り組み、作品を生み出します。";
		mes "その中でも、最高傑作が";
		mes "キミです……。";
		next;
		mes "[キャサリンゼータ]";
		mes "あ、すいません。";
		mes "セリーヌ・キミでは長いので";
		mes "親しみをこめ、^0000ffキミ^000000と";
		mes "みんな、呼んでいるんです。";
		next;
		mes "[キャサリンゼータ]";
		mes "人形職人は昔を懐かしみつつ";
		mes "キミを作りあげていきました。";
		mes "できれば以前のように、";
		mes "この工場に人が戻ってほしい……。";
		mes "人形職人のそんな気持ちが、キミに";
		mes "生命を吹き込んだのかもしれません。";
		next;
		menu "人形が生きていたんですか？",-;
		mes "[キャサリンゼータ]";
		mes "はい。^0000ff彼女^000000は生命がある存在に";
		mes "なりました。";
		mes "ところが……。";
		mes "どうしてなのかは分からないのですが";
		mes "私がキミを見かけた時、彼女は";
		mes "怒りと憎悪に囚われており、";
		next;
		mes "[キャサリンゼータ]";
		mes "とても私の声など聞く耳を";
		mes "もたないという感じで";
		mes "無人のおもちゃ工場をただ一人";
		mes "歩き回っていたのです。";
		next;
		mes "[キャサリンゼータ]";
		mes "そんなキミを見ておかしいなと";
		mes "こっそり後をつけたのですが……";
		mes "その時、人形職人のお爺さんが";
		mes "座っているのを見つけたのです。";
		next;
		mes "[キャサリンゼータ]";
		mes "私はお爺さんに駆け寄り、";
		mes "声をかけましたが反応はなく";
		mes "体もすっかり冷たくなっていて";
		mes "事切れていました……。";
		next;
		mes "[キャサリンゼータ]";
		mes "そして……。";
		mes "驚いて動けない私の視界に";
		mes "キミの姿が映りました……。";
		mes "お爺さんの亡骸の背後に立ち、";
		mes "その表情はなにも語らず、";
		mes "ただじっとそこに居ました。";
		next;
		mes "[キャサリンゼータ]";
		mes "私はその姿を見て……";
		mes "なぜか恐怖を感じてしまい……";
		mes "そこで私は気を失いました。";
		mes "どれくらいそうしていたのか、";
		mes "目が覚めると工場の外にいて、";
		mes "私の顔はこんな風になっていました。";
		next;
		mes "^0000ff‐目の前にいる少女の顔は、";
		mes "　明らかに皮膚などがなく";
		mes "　例えるなら顔だけが白骨化";
		mes "　してしまったように見える‐^000000";
		next;
		menu "その顔は、キミという人形が原因？",-;
		mes "[キャサリンゼータ]";
		mes "それが……私にも分からないのです。";
		mes "キミの可能性もありますし、";
		mes "他に原因があるのかもしれません。";
		mes "ただハッキリしていることは";
		mes "気を失ったときに何かがあった。";
		mes "それだけなのです……。";
		next;
		menu "キミが犯人だと思いますか？",-;
		mes "[キャサリンゼータ]";
		mes "……正直に言えば、分からないのです。";
		mes "キミではない気もしますし、";
		mes "そうなると他に誰が？と考えると";
		mes "思い当たる人物はいません……。";
		mes "かと言って、キミだと決め付けるのは";
		mes "早計な気もするのです。";
		next;
		mes "[キャサリンゼータ]";
		mes "だから、真実を知りたいと";
		mes "思ってはいるのですが……。";
		mes "……。";
		next;
		mes "^0000ff‐彼女はそういいながら";
		mes "　自分の身体を抱きしめた‐^000000";
		next;
		mes "[キャサリンゼータ]";
		mes "怖いんです……。";
		mes "行きたくないんです……。";
		mes "またあの工場に行けば、";
		mes "今以上に恐ろしいことが";
		mes "起きるかもしれない……。";
		next;
		mes "[キャサリンゼータ]";
		mes "でも、真実を知りたい……。";
		mes "この顔も、可能なら戻したい。";
		mes "お爺さんの亡骸も、ここではなく";
		mes "きちんと埋葬してあげたい。";
		mes "でも一人では怖くて……！";
		mes "……。";
		next;
		mes "[キャサリンゼータ]";
		mes "……冒険者さん。";
		mes "無理を承知で、言います……。";
		mes "私と一緒に、この工場に入って";
		mes "キミを探していただけませんか!?";
		next;
		menu "協力すると申し出る",-;
		mes "[キャサリンゼータ]";
		mes "そう……ですよね。";
		mes "無理に決ま……えっ!?";
		mes "一緒に行ってくれるのですか!?";
		mes "ああ……まさかそんな人が";
		mes "現れてくれるなんて！";
		next;
		menu "一緒にあの工場にいきましょう",-;
		mes "[キャサリンゼータ]";
		mes "ただ、先ほどもいいましたが";
		mes "おもちゃ工場は危険な状態です。";
		mes "私は全く戦えないし……。";
		mes "道案内程度しか役にたてそうに";
		mes "ありません……。";
		next;
		mes "^0000ff‐彼女は大きく開いたまま";
		mes "　今は閉じることすら叶わない";
		mes "　虚空のくぼみがある顔を";
		mes "　少し伏せたかと思うと";
		mes "　まっすぐにこちらを見て";
		mes "　こう告げた‐^000000";
		next;
		mes "[キャサリンゼータ]";
		mes "それでも私は知りたいのです。";
		mes "本当のことを……。";
		mes "このままでは何も問題は";
		mes "解決しませんし……。";
		mes "なので、宜しくお願いします。";
		next;
		mes "[キャサリンゼータ]";
		mes "そうと決まれば……";
		mes "準備をするので、少し待って下さい。";
		mes "冒険者様も準備ができたら";
		mes "私に声をかけてください。";
		setquest 12330;
		close;
	}
	if(checkquest(12330) != 0x8) {
		mes "[キャサリンゼータ]";
		mes "お待たせしました。";
		mes "準備ができました。";
		mes "冒険者様もよろしいでしょうか？";
		mes "今からあの転送装置に";
		mes "冒険者様の情報を登録し";
		mes "入場申請を行います。";
		compquest 12330;
		if(getonlinepartymember() < 1) {
			//
			next;
			mes "[キャサリンゼータ]";
			mes "この先は危険です。";
			mes "パーティーを組んでから";
			mes "きていただけますか。";
			close;
		}
	}
	else {
		mes "[キャサリンゼータ]";
		mes "残念ですが、キミの魂はいまだに";
		mes "苦しんでいるようです。";
		mes "お爺さんもこのままじゃ";
		mes "安心できないだろうし……。";
		mes "お暇なときにまた、お願いします。";
		if(getonlinepartymember() < 1) {
			next;
			mes "[キャサリンゼータ]";
			mes "この先は危険です。";
			mes "パーティーを組んでから";
			mes "きていただけますか。";
			close;
		}
		if(checkquest(12331)) {
			next;
			if(checkquest(12331) & 0x2) {
				mes "^0000ff‐おもちゃ工場が";
				mes "　稼働する時間になりました‐^000000";
				delquest 12331;
				close;
			}
			mes "[キャサリンゼータ]";
			mes "せっかく来ていただきましたが";
			mes "工場がまだ稼働時間では";
			mes "ないようですね……。";
			mes "ここで働いているのは";
			mes "おもちゃばかりなので";
			mes "時間に融通がきかなくて……。";
			next;
			mes "[キャサリンゼータ]";
			mes "なのでごめんなさい。";
			mes "工場が稼働するまで";
			mes "中に入ることはできません。";
			mes "せっかく来て頂きましたが";
			mes "時間をおいてから再度、";
			mes "声をかけてもらえると嬉しいです。";
			close;
		}
	}
	if(HORROR_1QUE >= 0)
		set '@str$[0],"この工場について";
	if(HORROR_1QUE >= 1)
		set '@str$[1],"ヒット商品について";
	if(HORROR_1QUE >= 3)
		set '@str$[2],"キャサリンゼータについて";
	if(HORROR_1QUE >= 5)
		set '@str$[3],"人形職人の死因について";
	if(HORROR_1QUE >= 7)
		set '@str$[4],"工場が稼働している理由";
	if(HORROR_1QUE >= 9)
		set '@str$[5],"キミについて";
	if(HORROR_1QUE >= 11)
		set '@str$[6],"キミの付属品について";
	if(HORROR_1QUE >= 13)
		set '@str$[7],"今後について";
	next;
	switch(select("^0000ffおもちゃ工場の鍵を開ける^000000","^ff0000やめる^000000",
		'@str$[0],'@str$[1],'@str$[2],'@str$[3],'@str$[4],'@str$[5],'@str$[6],'@str$[7])) {
	case 1:
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[キャサリンゼータ]";
			mes "ご、ごめんなさい。";
			mes "あなたのパーティーのリーダーと";
			mes "話をさせてもらえますか？";
			mes "一気に声をかけられると";
			mes "混乱してしまうのです……。";
			close;
		}
		mdcreate "Horror of Toy";
		mes "[キャサリンゼータ]";
		mes "以下の内容で手続きしますね。";
		mes "パーティー名が";
		mes "^0000FF" +strcharinfo(1)+ "^000000で";
		mes "パーティーリーダーは";
		mes "^0000FF" +strcharinfo(0)+ "^000000";
		mes "っと……。";
		next;
		mes "[キャサリンゼータ]";
		mes "まもなく転送装置が動くと思います。";
		close;
	case 2:
		mes "[キャサリンゼータ]";
		mes "……あら。";
		mes "やっぱりやめておきますか？";
		mes "今ならまだ間に合いますし……。";
		close;
	case 3:
		mes "[キャサリンゼータ]";
		mes "この街は一年中、雪が降る";
		mes "寒冷な気候と、物資の運輸が";
		mes "困難という地勢的特徴があって";
		mes "あらゆる産業が定着しなくて……。";
		next;
		mes "[キャサリンゼータ]";
		mes "それをこの工場の創業者であり";
		mes "腕利きの人形職人であるお爺さんが";
		mes "工場を設立、数多くのヒット商品を";
		mes "世に送り出したおかげで、";
		mes "一時期この工場だって、とても";
		mes "活気あふれる場所だったんです。";
		next;
		mes "[キャサリンゼータ]";
		mes "ただ、とある時期を境に";
		mes "それまで売れていた商品が";
		mes "なぜかわかりませんが売れなくなり";
		mes "現在のような状態になりました。";
		next;
		mes "[キャサリンゼータ]";
		mes "商品の人気は確かに、波がありますが";
		mes "本当に急に売れなくなったので";
		mes "もしかしたら、誰かが";
		mes "お爺さんを陥れるために";
		mes "仕組んだ罠だったりして……。";
		mes "なんて、考えすぎですね。";
		close;
	case 4:
		mes "[キャサリンゼータ]";
		mes "工場のヒット商品について";
		mes "知りたいのですか？";
		mes "冒険者様は好奇心が";
		mes "とても強いんですね！";
		mes "私がわかる範囲で";
		mes "お答えしますね。";
		next;
		mes "[キャサリンゼータ]";
		mes "一つ目は^FF0000「動く球体関節人形」^000000です。";
		mes "手足がわりと柔軟に動くため";
		mes "壊れにくくて、丈夫でした。";
		mes "クオリティにも拘って作られ";
		mes "特に、小さい女の子たちに";
		mes "大人気でした……。";
		next;
		mes "[キャサリンゼータ]";
		mes "次に、「動く球体関節人形」や";
		mes "プレゼントを入れるための箱、";
		mes "^FF0000「プレゼントボックス」^000000です。";
		mes "シンプルだけど扱いやすく";
		mes "デザインにも拘ったボックスです！";
		next;
		mes "[キャサリンゼータ]";
		mes "あとは、そうですね。";
		mes "^FF0000「アニバーサリークッキー」^000000と";
		mes "^FF0000「アニバーサリージュース」^000000かな。";
		mes "記念日に大事な人や家族と飲んで食べて";
		mes "幸せな気分になれるようにと";
		mes "作られたんですよ。";
		next;
		mes "[キャサリンゼータ]";
		mes "他にもあるのですが、";
		mes "有名なヒット商品は";
		mes "それくらいでしょうか。";
		mes "特にクッキーとジュースは";
		mes "個人的におすすめです。";
		close;
	case 5:
		mes "[キャサリンゼータ]";
		mes "え!?";
		mes "私について、ですか……。";
		mes "私のことを聞いてもあまり";
		mes "面白くないと思いますが……。";
		next;
		mes "[キャサリンゼータ]";
		mes "私がここを離れられない理由は";
		mes "確かに、この顔のせいもありますが";
		mes "何より、お世話になった";
		mes "人形職人のお爺さんに";
		mes "生前、なにもできなかったからが";
		mes "大きかったりします……。";
		next;
		mes "[キャサリンゼータ]";
		mes "この工場の関係者で、";
		mes "お爺さんにお世話にならなかった";
		mes "人間はいないといっても";
		mes "過言ではないと思います。";
		next;
		mes "[キャサリンゼータ]";
		mes "そのくらいこの工場にとって";
		mes "お爺さんは、大きな存在だったんです。";
		mes "それは私だけでなく";
		mes "お爺さんに作られたおもちゃ達も";
		mes "同様に……。";
		next;
		mes "[キャサリンゼータ]";
		mes "だから私、助けたいんです。";
		mes "お爺さんの忘れ形見である";
		mes "キミのことを……。";
		mes "だからもしまたよければ";
		mes "ぜひ、力を貸して";
		mes "くださいね。";
		close;
	case 6:
		mes "[キャサリンゼータ]";
		mes "……お爺さん。";
		mes "……。";
		next;
		mes "[キャサリンゼータ]";
		mes "……すいません。";
		mes "あの時のことを思い出しちゃって。";
		mes "この工場の創業者であり";
		mes "凄腕の人形職人であることは";
		mes "すでにお話してありますよね。";
		next;
		mes "[キャサリンゼータ]";
		mes "お爺さんの死因は、";
		mes "作業員の一人が心臓発作だと";
		mes "話していましたが、実際は";
		mes "はっきりした死因が";
		mes "わかっていないんです。";
		next;
		mes "[キャサリンゼータ]";
		mes "あと一つ気になるのが、";
		mes "お爺さんが生前";
		mes "心臓が悪いという話を";
		mes "聞いた記憶が";
		mes "ないんですよね……。";
		next;
		mes "[キャサリンゼータ]";
		mes "それに心臓病なら";
		mes "私が見たあれは……。";
		mes "……。";
		next;
		mes "[キャサリンゼータ]";
		mes "……ううーん。";
		mes "記憶がはっきりしません。";
		mes "多分、私の勘違いか";
		mes "見間違いだと思いますし";
		next;
		mes "[キャサリンゼータ]";
		mes "そんなことより今は、";
		mes "お爺さんの死因が";
		mes "はっきりしないせいで";
		mes "キミが工場長を殺したんじゃないか";
		mes "といった根も葉もない噂が";
		mes "広がっている方が問題です。";
		next;
		mes "[キャサリンゼータ]";
		mes "せめて、キミが";
		mes "お爺さんを殺していない";
		mes "証拠が見つかればいいんだけど……。";
		mes "時間が経過しているだけに";
		mes "難しそうですね。";
		close;
	case 7:
		mes "[キャサリンゼータ]";
		mes "工場長のお爺さんがいないのに";
		mes "今もこの工場は稼働していますね。";
		next;
		mes "[キャサリンゼータ]";
		mes "私はてっきり、キミが";
		mes "お爺さんの意思をついで、";
		mes "工場を稼働させているのだと";
		mes "思っていました……。";
		mes "でもキミのあの感じだと";
		mes "その可能性は低いようです。";
		next;
		mes "[キャサリンゼータ]";
		mes "そういえば作業員たちも";
		mes "産みの親である人形職人の";
		mes "お爺さんのことを";
		mes "なぜか忘れていましたね。";
		next;
		mes "[キャサリンゼータ]";
		mes "いくらキミでも";
		mes "お爺さんの記憶だけ忘れさせるなんて";
		mes "できると思わないですし、これは";
		mes "^FF0000キミ以外の誰か^000000の";
		mes "仕業のような気がします……。";
		next;
		mes "[キャサリンゼータ]";
		mes "だって、キミならきっと";
		mes "お爺さんのことを忘れてほしいなんて";
		mes "絶対に思わないはずです。";
		mes "キミは誰よりも、孤独の寂しさを";
		mes "知っているのですから……。";
		next;
		mes "[キャサリンゼータ]";
		mes "そう考えると私には";
		mes "そんなことをできるような";
		mes "人に心当たりがないので、";
		mes "この件については";
		mes "いくら考えても答えは";
		mes "でなさそうです……。";
		close;
	case 8:
		mes "[キャサリンゼータ]";
		mes "本当に、びっくりです……。";
		mes "キミと最後に会った時から";
		mes "随分、印象が違いましたから。";
		next;
		mes "[キャサリンゼータ]";
		mes "うまく説明できないんですが";
		mes "怖い顔になっているというか……";
		mes "なんだか前にみたときよりも";
		mes "寂しそうな感じがしました……。";
		next;
		mes "[キャサリンゼータ]";
		mes "あと、キミは自分のせいで";
		mes "お爺さんが死んだと、";
		mes "思い込んでいるようです。";
		mes "困ったなあ……。";
		next;
		mes "[キャサリンゼータ]";
		mes "私たちが何を言っても";
		mes "もう一人のキミらしき声が";
		mes "すぐに、こちらのいうことを";
		mes "捻じ曲げてしまうし……。";
		mes "あっ、そのもう一人の";
		mes "キミについてなのですが";
		next;
		mes "[キャサリンゼータ]";
		mes "お爺さんが生きていたときには";
		mes "居なかったと記憶しています。";
		mes "そうなると、あのもう一人のキミが";
		mes "工場の謎の稼動と何か";
		mes "関係があるのでしょうか……？";
		next;
		mes "[キャサリンゼータ]";
		mes "もう一人のキミを";
		mes "なんとかできれば、キミの件だけでも";
		mes "解決するのに……";
		mes "良い方法がないんですよね。";
		mes "うーん、まだまだ先は";
		mes "長そうです……。";
		close;
	case 9:
		mes "[キャサリンゼータ]";
		mes "冒険者様。";
		mes "私そういえば、お爺さんに";
		mes "簡単なキミの資料について";
		mes "いただいていたのを";
		mes "思い出したんです。";
		next;
		mes "[キャサリンゼータ]";
		mes "どうもこの工場で入手できる";
		mes "一部のアイテムはキミに付属する";
		mes "予定だったアイテムがいくつか";
		mes "紛れ込んでいるみたいですね。";
		next;
		mes "[キャサリンゼータ]";
		mes "ただ、そのアイテムの種類が";
		mes "書かれたページについては";
		mes "残念ながら、見つかりませんでした。";
		mes "なので、はっきりと、";
		mes "どのアイテムが……とは";
		mes "言えないのですが。";
		next;
		mes "[キャサリンゼータ]";
		mes "多分、セリーヌのリボンとか";
		mes "ノーブルクロスあたりが";
		mes "その付属する予定の";
		mes "アイテムだった気がします。";
		mes "他に、洋傘もそれっぽいですよね。";
		next;
		mes "[キャサリンゼータ]";
		mes "そう考えると、キミは";
		mes "お爺さんにとって本当に";
		mes "娘のような存在だったんですね。";
		mes "キミがもっと可愛く、";
		mes "愛されるように願って";
		mes "作られたものでしょうし……。";
		close;
	case 10:
		mes "[キャサリンゼータ]";
		mes "冒険者様とこんなにも";
		mes "長い付き合いになるなんて";
		mes "思ってもみなかったです。";
		next;
		mes "[キャサリンゼータ]";
		mes "いまだにキミの説得はうまく";
		mes "できていない状態ですが、";
		mes "こればかりは根気よく";
		mes "気長に進めるしかないですよね。";
		next;
		mes "[キャサリンゼータ]";
		mes "まだわからないことも多いし";
		mes "大変ですけど……";
		mes "私はまだ、諦めません。";
		next;
		menu "最初のころとかわりましたね",-;
		mes "[キャサリンゼータ]";
		mes "はい、それも冒険者様が";
		mes "私とキミのためにこうして";
		mes "力添えしてくれたお陰です。";
		mes "本当に感謝しています。";
		next;
		mes "[キャサリンゼータ]";
		mes "だからこそ、";
		mes "冒険者様にはもっと";
		mes "この工場のことや、キミのこと";
		mes "お爺さんのことを知ってほしいのに";
		next;
		mes "[キャサリンゼータ]";
		mes "これ以上のことは分からないというか";
		mes "思い出せないというか……。";
		mes "とりあえず今のところ";
		mes "私のほうからこれ以上、";
		mes "お話できる内容はありません……。";
		mes "ごめんなさい……。";
		next;
		mes "[キャサリンゼータ]";
		mes "あ、でも一つだけ。";
		mes "私、まだ冒険者様に伝えていない";
		mes "情報がありました。";
		next;
		menu "伝えていない情報？",-;
		mes "[キャサリンゼータ]";
		mes "はい。";
		mes "キミが何度退けても";
		mes "この工場に戻ってくるように";
		mes "私も、諦めが悪いということです！";
		mes "なので、冒険者様。";
		mes "これからも、よろしくお願いします。";
		next;
		mes "^0000ff‐そういって頭を下げる";
		mes "　彼女の顔にほんの一瞬";
		mes "　笑顔の少女が重なって";
		mes "　見えた気がした‐^000000";
		next;
		mes "[キャサリンゼータ]";
		mes "それでは、";
		mes "また何か冒険者様に";
		mes "お話できることを思い出したり";
		mes "情報を手に入れた際には";
		mes "お話しますので、";
		mes "楽しみにしててください。";
		next;
		mes "^0000ff‐キャサリンゼータから";
		mes "　聞ける話をすべて聞くことが";
		mes "　できたようだ。";
		mes "　これ以上の話は聞けないようなので";
		mes "　憶えておこう‐^000000";
		close;
	}
}

//============================================================
// ダンジョン入場NPC
//------------------------------------------------------------
xmas.gat,233,305,4	script	転送装置	10007,{
	if(BaseLevel < 110) {
		mes "[転送装置]";
		mes "転送に必要な能力が足りません。";
		mes "BaseLv110以上にしてください。";
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "[転送装置]";
		mes "この先に行くには";
		mes "パーティーを組む必要が";
		mes "あります。";
		mes "パーティーを結成して下さい。";
		close;
	}
	if(checkquest(12331)) {
		if(checkquest(12331) & 0x2) {
			mes "[転送装置]";
			mes "^0000ff転送の痕跡が消えました。";
			mes "転送装置の利用が";
			mes "可能になりました。^000000";
			delquest 12331;
			close;
		}
		mes "[転送装置]";
		mes "転送を行った痕跡が残っています。";
		mes "しばらく時間をおいてください。";
		close;
	}
	mes "[転送装置]";
	mes "システムチェック中……。";
	next;
	mes "‐転送装置は正常に起動しています‐";
	next;
	if(select("入る","入らない") == 2) {
		mes "‐あなたは転送装置から離れた‐";
		close;
	}
	switch(mdenter("Horror of Toy")) {
	case 0:	// エラーなし
		announce "メモリアルダンジョン[Horror of Toy] に入場しました　：　" +strcharinfo(1)+ " (" +strcharinfo(0)+ ")",0x9,0x00ff99;
		donpcevent getmdnpcname("キャサリンゼータ#0") +"::OnMDInit";
		if(checkquest(96400))
			delquest 96400;
		if(checkquest(96405))
			delquest 96405;
		setquest 12331;
		//setquest 118903;
		setquest 96400;
		//warp "1@xm_d.gat",111,22;
		close;
	case 1:	// パーティー未加入
		mes "[転送装置]";
		mes "パーティーが解体されています。";
		mes "再度パーティーを組み直してから";
		mes "入場受付を行ってください。";
		close;
	case 2:	// ダンジョン未作成
		mes "[転送装置]";
		mes "工場稼働時間ではないため";
		mes "移動することができません。";
		mes "　";
		mes "‐入場受付が必要なようだ‐";
		close;
	default:	// その他エラー
		close;
	}
}

//============================================================
// ホラーおもちゃ工場
//------------------------------------------------------------
1@xm_d.gat,112,20,6	script	キャサリンゼータ#0	10032,{
	if(sc_onparam(SC_MONSTER_TRANSFORM,1)) {
		// 未調査
	}
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "[キャサリンゼータ]";
		mes "なんとか工場に潜り込めましたね。";
		mes "ここについて詳しい説明を";
		mes "私からした方がよいですか？";
		unittalk "キャサリンゼータ : なんとか工場に潜り込めましたね。ここについて詳しい説明を私からした方がよいですか？";
		next;
		switch(select("話を終える","話を聞く","説明は必要ないので進む")) {
		case 1:
			mes "[キャサリンゼータ]";
			mes "心の準備が出来たら声をかけて下さい。";
			close;
		case 2:
			donpcevent getmdnpcname("キャサリンゼータ#0") +"::OnStart";
			close;
		case 3:
			donpcevent getmdnpcname("キャサリンゼータ#0") +"::OnStart2";
			close;
		}
	}
	else {
		mes "[キャサリンゼータ]";
		mes "ご、ごめんなさい……。";
		mes "あまり沢山の人に一気に";
		mes "話しかけられると私、混乱するんです。";
		mes "だから申し訳ないのですが";
		mes "あなたのパーティーのリーダーとのみ";
		mes "話をさせてください。";
		close;
	}
OnMDInit:
	if('flag)
		end;
	set 'flag,1;
	hideonnpc getmdnpcname("#bgm01");
	hideonnpc getmdnpcname("#bgm02");
	hideonnpc getmdnpcname("#bgm03");
	hideonnpc getmdnpcname("#bgm04");
	hideonnpc getmdnpcname("#bgm05");
	hideonnpc getmdnpcname("#bgm06");
	hideonnpc getmdnpcname("キャサリンゼータ#01");
	hideonnpc getmdnpcname("キャサリンゼータ#21");
	hideonnpc getmdnpcname("キャサリンゼータ#6");
	hideonnpc getmdnpcname("セリーヌ・キミ#2");
	hideonnpc getmdnpcname("囚われたサンタ#3");
	hideonnpc getmdnpcname("囚われたサンタ#4");
	hideonnpc getmdnpcname("職員用の衣服ボックス#1");
	hideonnpc getmdnpcname("職員用の衣服ボックス#2");
	hideonnpc getmdnpcname("職員用の衣服ボックス#3");
	hideonnpc getmdnpcname("職員用の衣服ボックス#4");
	hideonnpc getmdnpcname("#fac1bs");
	hideonnpc getmdnpcname("#pck1");
	hideonnpc getmdnpcname("#kimion1");
	hideonnpc getmdnpcname("#fac3wp");
	hideonnpc getmdnpcname("#fac3wp2");
	hideonnpc getmdnpcname("#fac4wp");
	hideonnpc getmdnpcname("#fac4wp2");
	hideonnpc getmdnpcname("#fac5wp");
	hideonnpc getmdnpcname("#fac5wp2");
	hideonnpc getmdnpcname("#fac6wp");
	hideonnpc getmdnpcname("#jeton2");
	hideonnpc getmdnpcname("非常口#exwp1");
	for(set '@i,1;'@i<=10; set '@i,'@i+1)
		hideonnpc getmdnpcname("作業員#xm_d"+'@i);
	hideonnpc getmdnpcname("包装されたプレゼント#00");
	for(set '@i,1;'@i<=12; set '@i,'@i+1)
		hideonnpc getmdnpcname("包装されたプレゼント#"+'@i);
	for(set '@i,1;'@i<=9; set '@i,'@i+1)
		hideonnpc getmdnpcname("xm_d#eff_f0"+'@i);
	donpcevent getmdnpcname("xm_d#Barricade00")+"::OnStart";
	end;
OnStart:
	initnpctimer;
	hideoffnpc getmdnpcname("#bgm01");
	hideoffnpc getmdnpcname("キャサリンゼータ#01");
	hideonnpc getmdnpcname("キャサリンゼータ#0");
	end;
OnTimer1000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk1";
	end;
OnTimer6000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk2";
	end;
OnTimer11000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk3";
	donpcevent getmdnpcname("#fac1ct") + "::OnStart";
	end;
OnTimer14000:
	announce "工場案内放送 : おもちゃ工場の家族のみなさ～ん。起きて下さ～い。楽しい労働時間がやって来ましたよ～。",0x9,0x00ff44;
	end;
OnTimer19000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk4";
	end;
OnTimer24000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk5";
	end;
OnTimer27000:
	announce "工場案内放送 : 工場内のゴミや有害なものを片付けて、いつものように安全に作業を行って下さい。",0x9,0x00ff44;
	end;
OnTimer30000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk6";
	end;
OnTimer33000:
	announce "工場案内放送 : 今日も一所懸命、子供たちの夢と希望の為にプレゼントを作りましょう。",0x9,0x00ff44;
	end;
OnTimer36000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk7";
	end;
OnTimer37000:
	announce "工場案内放送 : 第1ライン作業をはじめて下さい。安全ヘルメットを着用しましょう。",0x9,0x00ff44;
	end;
OnTimer40000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk8";
	end;
OnTimer46000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk9";
	end;
OnTimer48000:
	announce "工場案内放送 : 工場内では作業員証明書や作業服は必ず着用しましょう。そうしないと警備の方たちに怒られますよ～。",0x9,0x00ff44;
	end;
OnTimer53000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk10";
	hideoffnpc getmdnpcname("職員用の衣服ボックス#1");
	hideoffnpc getmdnpcname("職員用の衣服ボックス#2");
	hideoffnpc getmdnpcname("職員用の衣服ボックス#3");
	misceffect 247,getmdnpcname("職員用の衣服ボックス#1");
	misceffect 247,getmdnpcname("職員用の衣服ボックス#2");
	misceffect 247,getmdnpcname("職員用の衣服ボックス#3");
	end;
OnTimer59000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk11";
	end;
OnTimer64000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk12";
	end;
OnTimer69000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk13";
	end;
OnTimer74000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk14";
	end;
OnTimer78000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk15";
	end;
OnTimer84000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk16";
	announce "‐動いている人形たちと動くおもちゃボックスを停止させるため、アナウンスが流れるまで倒してください‐",0x9,0xffffff;
	end;
OnTimer90000:
	stopnpctimer;
	hideonnpc getmdnpcname("キャサリンゼータ#01");
	hideonnpc getmdnpcname("#bgm01");
	end;

OnStart2:
	initnpctimer;
	setnpctimer 100000;
	hideoffnpc getmdnpcname("#bgm01");
	hideoffnpc getmdnpcname("キャサリンゼータ#01");
	hideonnpc getmdnpcname("キャサリンゼータ#0");
	end;
OnTimer103000:
	donpcevent getmdnpcname("キャサリンゼータ#01")+"::OnTalk17";
	end;
OnTimer109000:
	hideonnpc getmdnpcname("キャサリンゼータ#01");
	announce "工場案内放送 : おもちゃ工場の家族のみなさ～ん。みんな起きて下さい。楽しい労働時間がやって来ましたよ～。",0x9,0x00ff44;
	hideoffnpc getmdnpcname("職員用の衣服ボックス#1");
	hideoffnpc getmdnpcname("職員用の衣服ボックス#2");
	hideoffnpc getmdnpcname("職員用の衣服ボックス#3");
	misceffect 247,getmdnpcname("職員用の衣服ボックス#1");
	misceffect 247,getmdnpcname("職員用の衣服ボックス#2");
	misceffect 247,getmdnpcname("職員用の衣服ボックス#3");
	end;
OnTimer115000:
	announce "工場案内放送 : 工場内のゴミや有害なものを片付けて、いつものように安全に作業を行って下さい。",0x9,0x00ff44;
	end;
OnTimer121000:
	stopnpctimer;
	announce "工場案内放送 : 今日も一所懸命、子供たちの夢と希望の為にプレゼントを作りましょう。",0x9,0x00ff44;
	hideonnpc getmdnpcname("#bgm01");
	donpcevent getmdnpcname("#fac1ct")+ "::OnStart";
	end;
}

1@xm_d.gat,112,20,0	script	#bgm01	139,10,10,{
	musiceffect "99";
	end;
}

1@xm_d.gat,112,20,1	script	キャサリンゼータ#01	10032,{
	end;
OnTalk1:
	unittalk "キャサリンゼータ : ここは第1工場ですね。主にプレゼントとして渡す前のおもちゃや人形たちを集めておいてあった場所です。";
	end;
OnTalk2:
	unittalk "キャサリンゼータ : ああ、色々と思い出してきました。作業服を着ないでうろうろしていたら、警備兵のおじさんたちが走って来てよく怒られました……。";
	end;
OnTalk3:
	unittalk "キャサリンゼータ : それなのに……あ……。";
	end;
OnTalk4:
	unittalk "キャサリンゼータ : こ……これはいったい？　人の代わりにおもちゃや人形たちが歩き回っています。まるで作業員のように……。";
	end;
OnTalk5:
	unittalk "キャサリンゼータ : どうやら長い間、誰もいなかった工場を誰かが、稼動させているようですね……。";
	end;
OnTalk6:
	unittalk "キャサリンゼータ : まるで閉鎖される前に働いていた人たちに似せた……いえ、何もかもが以前と同じようです。すごい……。一体誰が……？";
	end;
OnTalk7:
	unittalk "キャサリンゼータ : だけど、喜んでいる場合ではなさそうです。キミがいた区域に行くためには、まずここの生産作業をすべて停止させなければなりません。";
	end;
OnTalk8:
	unittalk "キャサリンゼータ : そのためにも、あの人形たちと動くおもちゃボックスを一時的に、働けなくする必要があると思います。";
	end;
OnTalk9:
	unittalk "キャサリンゼータ : え？　働けなくする方法ですか？　……そうですね。行動の制御回路を止めてしまえば大丈夫だと思います。";
	end;
OnTalk10:
	unittalk "キャサリンゼータ : あ、警備兵の役もおもちゃたちがやっているのかな……。面倒なことになりそうですから作業服に着替えたほうがよいかもしれませんね。以前はここの何処かに作業服に着替えるボックスがあったのに……。";
	end;
OnTalk11:
	unittalk "キャサリンゼータ : 私の後ろにありましたね。あの職員用の衣服ボックスがそうです。何かあった時の為に、作業員服に必ず着替えて下さい。私はまだ自分の作業員証明証をもっていますから着替える必要はないので……。";
	end;
OnTalk12:
	unittalk "キャサリンゼータ : 第1工場の仕事が終わらないと、第2工場が動きません。とりあえず作業服に着替えたら、活動している人形たちと動くおもちゃボックスの活動を止めてください。";
	end;
OnTalk13:
	unittalk "キャサリンゼータ : 話しても無駄だと思いますし、行動の制御回路はわかりにくい場所にあるのでここは戦って、止めてしまいましょう。";
	end;
OnTalk14:
	unittalk "キャサリンゼータ : おもちゃですからすぐに修復可能ですし、ちょっと乱暴に扱われたくらいではそうそう壊れないので遠慮はいりません。";
	end;
OnTalk15:
	unittalk "キャサリンゼータ : 一定のおもちゃの活動が停止すれば、アナウンスが流れ、第2工場へ行く道が開くかもしれませんし。";
	end;
OnTalk16:
	unittalk "キャサリンゼータ : 私は手がかりがないか調べてきます。ここにいる人形と動くおもちゃボックスを停止させ、もし第2工場への道が開いたら、向こうで合流しましょう。頑張って下さい。";
	end;
OnTalk17:
	unittalk "キャサリンゼータ : では、第2工場への道が開いたら、向こう側で合流することにしましょう。頑張って下さい。";
	end;
}

1@xm_d.gat,13,105,6	script	職員用の衣服ボックス#1	10033,{
	progressbar 1;
	sc_end SC_MONSTER_TRANSFORM;
	musiceffect "52";
	sc_start SC_MONSTER_TRANSFORM,180000,1246;
	mes "^0000ff‐作業服に着替え終わりました。";
	mes "　作業中に変身が必要な場合はここで";
	mes "　いつでも変身することが出来ます‐^000000";
	close;
}

1@xm_d.gat,116,16,6	script	職員用の衣服ボックス#2	10033,{
	progressbar 1;
	sc_end SC_MONSTER_TRANSFORM;
	musiceffect "52";
	sc_start SC_MONSTER_TRANSFORM,180000,1246;
	mes "^0000ff‐作業服に着替え終わりました。";
	mes "　作業中に変身が必要な場合はここで";
	mes "　いつでも変身することが出来ます‐^000000";
	close;
}

1@xm_d.gat,10,20,6	script	職員用の衣服ボックス#3	10033,{
	progressbar 1;
	sc_end SC_MONSTER_TRANSFORM;
	musiceffect "52";
	sc_start SC_MONSTER_TRANSFORM,180000,1246;
	mes "^0000ff‐作業服に着替え終わりました。";
	mes "　作業中に変身が必要な場合はここで";
	mes "　いつでも変身することが出来ます‐^000000";
	close;
}

1@xm_d.gat,1,5,3	script	#fac1ct	844,{
OnStart:
	areamonster getmdmapname("1@xm_d.gat"),10,20,116,105,"プレゼント包装担当者",2989,31,getmdnpcname("#fac1ct")+ "::OnKilled";
	areamonster getmdmapname("1@xm_d.gat"),10,20,116,105,"包装されたボックス",2991,36,getmdnpcname("#fac1ct")+ "::OnKilled";
	end;
OnKilled:
	set '@count,getmapmobs(getmdmapname("1@xm_d.gat"),getmdnpcname("#fac1ct")+ "::OnKilled");
	if('@count < 28) {
		initnpctimer;
		viewpoint 1,71,129,1,0xFF8000;
		killmonster getmdmapname("1@xm_d.gat"),getmdnpcname("#fac1ct")+"::OnKilled";
		announce "作業班長案内放送 : あれ？　みんなどこに行ってしまったんだ!?",0x9,0xff8800;
	}
	end;
OnTimer3000:
	announce "作業班長案内放送 : 包装済みのボックスを第2工場へ運ぶのに人手が足りないんだ！",0x9,0xff8800;
	end;
OnTimer5000:
	stopnpctimer;
	announce "作業班長案内放送 : 手が空いているやつは北西にあるレールのところまで来てくれ！",0x9,0xff8800;
	hideoffnpc getmdnpcname("#fac1bs");
	for(set '@i,61; '@i<=89; set '@i,'@i+1)
		hideonnpc getmdnpcname("alert#"+ '@i);
	end;
}

1@xm_d.gat,71,129,3	script	#fac1bs	10020,{
	if(sc_onparam(SC_MONSTER_TRANSFORM,1) == 1249) {
		mes "[作業班長]";
		mes "何をグズグズしているんだ。";
		mes "ここにある包装済みのボックスを";
		mes "持ってからそっちに行くんだ！";
		close;
	}
	if(sc_onparam(SC_MONSTER_TRANSFORM,1) != 1246) {
		mes "[作業班長]";
		mes "なんだ!?　人間じゃないか!!";
		mes "どうして人間が!?";
		mes "ここは関係者以外立ち入り禁止だ！";
		mes "警備兵ー！　人間だー！";
		unittalk "作業班長 : 警備兵！　警備兵はどこにいるんだ！　ここに人間たちが来ている！";
		donpcevent getmdnpcname("#alert1") +"::OnStart";
		close;
	}
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		mes "[作業班長]";
		mes "作業員がいなくなって心配していたぞ。";
		mes "まったく……他の奴らはどこいったんだ？";
		mes "ああっと、しまった！";
		mes "こんなことをしている場合じゃない、";
		mes "子供達がプレゼントを待ってるんだ。";
		next;
		mes "[作業班長]";
		mes "急いで^ff0000ここにある";
		mes "包装済みのボックス^000000";
		mes "を持ってレールの東にある";
		mes "第2工場に移動してくれ。";
		mes "大きいから気をつけて運ぶんだぞ。";
		unittalk "作業班長 : 急いでここにある包装済みのボックスを持ってレールの東にある第2工場に移動してくれ。大きいから気をつけて運ぶんだぞ。";
		hideoffnpc getmdnpcname("#pck1");
		misceffect 247,getmdnpcname("#pck1");
		close;
	}
	else {
		mes "[作業班長]";
		mes "お前の班のリーダーは誰だ？";
		mes "時間がないんだ。";
		mes "リーダーと話をさせてくれ。";
		close;
	}
OnStart:
	hideoffnpc getmdnpcname("#fac1bs");
	unittalk "作業班長 : 人間たちは全部排除されたみたいだな……？　最近こんなことが頻繁に起きている。嫌な世の中になったものだ……。おっと、仕事仕事っと。";
	end;
}

1@xm_d.gat,65,127,6	script	#pck1	10033,{
	progressbar 1;
	if(sc_onparam(SC_MONSTER_TRANSFORM,1) == 1249) {
		mes "^009900‐既に包装済みのボックスを";
		mes "　持ち上げています。";
		mes "　一度に2個以上は持ち上げることは";
		mes "　できません‐^000000";
		close;
	}
	if(sc_onparam(SC_MONSTER_TRANSFORM,1) != 1246) {
		mes "^ff0000‐作業員の姿ではないので、";
		mes "　包装済みのボックスを";
		mes "　持ち上げることができません。";
		mes "　着替えた状態で";
		mes "　作業服に着替えた状態で";
		mes "　試してみましょう‐^000000";
		close;
	}
	sc_end SC_MONSTER_TRANSFORM;
	sc_start SC_MONSTER_TRANSFORM,180000,1249;
	mes "^0000ff‐包装済みのボックスを";
	mes "　持ち上げました。";
	mes "　あまりにも巨大で";
	mes "　前がちゃんと見えません‐^000000";
	viewpoint 2,1,1,1,0xFFFFFF;
	viewpoint 1,76,129,2,0xFF8000;
	close;
}

1@xm_d.gat,76,129,0	script	#fac1wp	45,2,2,{
	set '@map$,getmdmapname("1@xm_d.gat");
	set '@label$,getmdnpcname("#fac1ct")+"::OnKilled";
	if(getmapmobs('@map$,'@label$)){
		mes "^ff0000‐まだ多くのおもちゃが動いている。";
		mes "　もっと活動しているおもちゃを";
		mes "　停止させる必要がありそうだ‐^000000";
		close;
	}
	if(sc_onparam(SC_MONSTER_TRANSFORM,1) != 1249) {
		mes "[作業班長]";
		mes "何をグズグズしているんだ。";
		mes "ここにある包装済みのボックスを";
		mes "持ってからそっちに行くんだ！";
		close;
	}
	warp '@map$,88,129;
	end;
}

1@xm_d.gat,79,129,0	script	#fac1wp2	45,2,2,{
	mes "‐作業班長が人手がこなくて";
	mes "　苛立っている様子が見える。";
	mes "　戻るとまた、作業を任されそうだ。";
	mes "　用事がない以上は戻らない方が";
	mes "　良いかもしれない……‐";
	next;
	if(select("第1工場に戻らない","第1工場に戻る") == 1)
		close;
	warp getmdmapname("1@xm_d.gat"),73,129;
	end;
}

1@xm_d.gat,179,129,0	script	#fac2wp	45,2,2,{
	if(sc_onparam(SC_MONSTER_TRANSFORM,1) != 1249) {
		mes "‐包装済みのボックスを";
		mes "　持ち上げていないせいか";
		mes "　レールが動作しない。";
		mes "　再度、包装済みのボックスを";
		mes "　持って来よう‐";
		close;
	}
	warp getmdmapname("1@xm_d.gat"),183,100;
	end;
}
1@xm_d.gat,184,109,0	warp	#fac2wp2	2,2,1@xm_d.gat,170,129

1@xm_d.gat,130,135,4	script	道標#1	858,{
	mes "‐^ff0000↑休憩室^000000";
	mes "　※休憩室の利用可能時間は";
	mes "　アナウンスにて案内※";
	mes "　";
	mes "　^ff0000→第2工場^000000";
	mes "　※レールに沿ってまっすぐ※‐";
	close;
}

1@xm_d.gat,1,5,3		script	#alert1	844,{
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	hideonnpc getmdnpcname("#fac1bs");
	end;
OnTimer2000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer3000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer4000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer5000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer6000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer7000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer8000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer9000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer10000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer11000:
	areamonster getmdmapname("1@xm_d.gat"),61,118,71,128,"おもちゃ工場警備兵",2990,1,getmdnpcname("#alert1")+ "::OnKilled";
	end;
OnTimer60000:
	killmonster getmdmapname("1@xm_d.gat"),getmdnpcname("#alert1")+"::OnKilled";
	donpcevent getmdnpcname("#fac1bs")+"OnStart";
	end;
OnKilled:
	end;
}

1@xm_d.gat,185,100,6	script	キャサリンゼータ#2	10032,{
	mes "[キャサリンゼータ]";
	mes "無事に合流できましたね、";
	mes "良かった……。";
	mes "怪我とか、ありませんか？";
	mes "休憩をかねて、";
	mes "少し状況を整理しましょうか？";
	unittalk "キャサリンゼータ : 無事に合流できましたね、良かった……。怪我とか、ありませんか？　休憩をかねて、少し状況を整理しましょうか？";
	next;
	switch(select("話をやめる","第2工場の情報を聞く","説明は不要なので進もうという")) {
	case 1:
		mes "[キャサリンゼータ]";
		mes "準備が出来たら声をかけて下さい。";
		close;
	case 2:
		viewpoint 1,155,98,1,0xFF8000;
		viewpoint 1,130,72,2,0xFF8000;
		viewpoint 1,134,34,3,0xFF8000;
		viewpoint 1,195,28,4,0xFF8000;
		viewpoint 1,228,30,5,0xFF8000;
		viewpoint 1,203,55,6,0xFF8000;
		viewpoint 1,132,52,7,0xFFF8000;
		viewpoint 1,162,52,8,0xFF8000;
		viewpoint 1,242,17,9,0xFF8000;
		viewpoint 1,209,15,10,0xFF8000;
		donpcevent getmdnpcname("キャサリンゼータ#2") +"::OnStart";
		close;
	case 3:
		viewpoint 1,155,98,1,0xFF8000;
		viewpoint 1,130,72,2,0xFF8000;
		viewpoint 1,134,34,3,0xFF8000;
		viewpoint 1,195,28,4,0xFF8000;
		viewpoint 1,228,30,5,0xFF8000;
		viewpoint 1,203,55,6,0xFF8000;
		viewpoint 1,132,52,7,0xFF8000;
		viewpoint 1,162,52,8,0xFF8000;
		viewpoint 1,242,17,9,0xFF8000;
		viewpoint 1,209,15,10,0xFF8000;
		donpcevent getmdnpcname("キャサリンゼータ#2") +"::OnStart2";
		close;
	}
OnStart:
	initnpctimer;
	hideoffnpc getmdnpcname("#bgm06");
	hideoffnpc getmdnpcname("キャサリンゼータ#21");
	hideonnpc getmdnpcname("キャサリンゼータ#2");
	end;
OnTimer1000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk1";
	end;
OnTimer6000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk2";
	end;
OnTimer11000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk3";
	end;
OnTimer16000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk4";
	end;
OnTimer21000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk5";
	end;
OnTimer26000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk6";
	end;
OnTimer31000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk7";
	end;
OnTimer36000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk8";
	end;
OnTimer41000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk9";
	end;
OnTimer46000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk10";
	announce "‐作業服に着替えた後、「作業員」を見かけたら、人形職人の話を聞いてみよう‐",0x9,0xffffff;
	end;
OnTimer52000:
	stopnpctimer;
	hideonnpc getmdnpcname("キャサリンゼータ#21");
	hideonnpc getmdnpcname("#bgm06");
	hideoffnpc getmdnpcname("職員用の衣服ボックス#4");
	misceffect 247,getmdnpcname("職員用の衣服ボックス#4");
	for(set '@i,1; '@i<=10; set '@i,'@i+1)
		hideoffnpc getmdnpcname("作業員#xm_d"+ '@i);
	donpcevent getmdnpcname("#fac2ct")+ "::OnStart";
	donpcevent getmdnpcname("#fac2wpc")+ "::OnStart";
	end;

OnStart2:
	initnpctimer;
	setnpctimer 100000;
	hideoffnpc getmdnpcname("#bgm06");
	hideoffnpc getmdnpcname("キャサリンゼータ#21");
	hideonnpc getmdnpcname("キャサリンゼータ#2");
	end;
OnTimer103000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk8";
	end;
OnTimer107000:
	donpcevent getmdnpcname("キャサリンゼータ#21")+"::OnTalk9";
	announce "‐作業服に着替えた後、「作業員」を見かけたら、人形職人の話を聞いてみよう‐",0x9,0xffffff;
	end;
OnTimer112000:
	stopnpctimer;
	hideonnpc getmdnpcname("キャサリンゼータ#21");
	hideonnpc getmdnpcname("#bgm06");
	hideoffnpc getmdnpcname("職員用の衣服ボックス#4");
	misceffect 247,getmdnpcname("職員用の衣服ボックス#4");
	for(set '@i,1; '@i<=10; set '@i,'@i+1)
		hideoffnpc getmdnpcname("作業員#xm_d"+ '@i);
	donpcevent getmdnpcname("#fac2ct")+ "::OnStart";
	donpcevent getmdnpcname("#fac2wpc")+ "::OnStart";
	end;
}

1@xm_d.gat,185,100,0	script	#bgm06	139,10,10,{
	musiceffect "99";
	end;
}

1@xm_d.gat,185,100,6	script	キャサリンゼータ#21	10032,{
	end;
OnTalk1:
	unittalk "キャサリンゼータ : ここは作業員たちがプレゼントを包装して集める第2工場でした。";
	end;
OnTalk2:
	unittalk "キャサリンゼータ : 以前は工場のあらゆる場所が人々で賑わっていたのに、今はそうでもないようですね……。";
	end;
OnTalk3:
	unittalk "キャサリンゼータ : あ、そうだ！　来る途中に分かったことですけど、ここにはおもちゃではない子供たちも徘徊しています。";
	end;
OnTalk4:
	unittalk "キャサリンゼータ : なんというか……とても怖い姿で。とても悲しそうな感じの霊魂たちが多かったんです。";
	end;
OnTalk5:
	unittalk "キャサリンゼータ : その子たちが襲ってきたら……残念ですが冒険者様の手で休ませてあげて下さい……。それしか、あの子達をここから救う手段はないのです……。なぜか私には襲いかかってきませんでしたが……。";
	end;
OnTalk6:
	unittalk "キャサリンゼータ : あとは、探索している途中に作業中のおもちゃを見かけたら、人形職人の話を聞いてもらってもいいですか？　どうも人形職人の記憶がすっかり消えているようなのです……。";
	end;
OnTalk7:
	unittalk "キャサリンゼータ : もし人形職人への記憶を思い出したら、彼らも旅立つことができるかもしれません。それが唯一の希望のような気がします……。";
	end;
OnTalk8:
	unittalk "キャサリンゼータ : 何かあったら、ご連絡します。それでは、私は何か手がかりがないか、ほかの場所をあたってみますね。";
	end;
OnTalk9:
	unittalk "キャサリンゼータ : あ、あと……包装済みのボックスはもう必要ないはずです。そのままでは怪しまれるので、この後忘れずに作業服に着替えておいてください。";
	end;
OnTalk10:
	unittalk "キャサリンゼータ : 頼ってばかりで……本当にすみません。では後程お会いしましょう。";
	end;
}

1@xm_d.gat,185,94,6		script	職員用の衣服ボックス#4	10033,5,5,{
	progressbar 1;
	sc_end SC_MONSTER_TRANSFORM;
	musiceffect "128";
	sc_start SC_MONSTER_TRANSFORM,300000,1246;
	mes "^0000ff‐作業服に着替え終わりました。";
	mes "　作業中に変身が必要な場合はここで";
	mes "　いつでも変身することが出来ます‐^000000";
	close;
OnTouch:
	for(set '@i,1; '@i<=10; set '@i,'@i+1)
		doevent getmdnpcname("作業員#xm_d"+'@i)+ "::OnCheck";
	end;
}

1@xm_d.gat,1,5,3		script	#fac2ct	844,{
OnStart:
	areamonster getmdmapname("1@xm_d.gat"),143,36,240,120,"包装されたボックス",2991,16,getmdnpcname("#fac2ct")+ "::OnKilled";
	areamonster getmdmapname("1@xm_d.gat"),143,36,240,120,"工場警備員の魂",2992,16,getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),155,98,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),155,98,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),130,72,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),130,72,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),134,34,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),134,34,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),195,28,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),195,28,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),228,30,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),228,30,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),203,55,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),203,55,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),132,52,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),132,52,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),162,52,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),162,52,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	//monster getmdmapname("1@xm_d.gat"),242,17,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	//monster getmdmapname("1@xm_d.gat"),242,17,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),209,15,"捨てられたクマ人形",2995,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	monster getmdmapname("1@xm_d.gat"),209,15,"プレゼントがない幽霊",2993,rand(1,3),getmdnpcname("#fac2ct")+ "::OnKilled";
	end;
OnKilled:
	end;
}

1@xm_d.gat,130,178,0	warp	#fac3wp		2,2,1@xm_d.gat,130,193
1@xm_d.gat,130,184,0	warp	#fac3wp2	2,2,1@xm_d.gat,129,173

1@xm_d.gat,1,2,3		script	#fac2wpc	844,{
OnStart:
	set 'count,10;
	end;
OnCount:
	set 'count,'count-1;
	if('count)
		announce "工場案内放送 : 勤務人数を確認中です。今現在包装ラインにて" +'count+ "名が作業中です。ミスのないよう、頑張って下さい。",0x9,0x00ff44;
	else {
		announce "工場案内放送 : 配送分類作業場の作業員全員が家に戻りました。作業場の電源を遮断して作業員休憩室の扉を開きます。",0x9,0x00ff44;
		announce "‐通れなかった休憩室の扉が開いたようだ。包装済みのボックスを移動するために使ったレールを北に上がった場所に休憩室があったはず。行ってみよう‐",0x9,0xffffff;
		for(set '@i,90; '@i<=100; set '@i,'@i+1)
			hideonnpc getmdnpcname("alert#"+ '@i);
		killmonster getmdmapname("1@xm_d.gat"),getmdnpcname("#fac2ct")+"::OnKilled";
		hideoffnpc getmdnpcname("#fac3wp");
		hideoffnpc getmdnpcname("#fac3wp2");
	}
	end;
OnCheck:
	for(set '@i,1; '@i<=10; set '@i,'@i+1)
		doevent getmdnpcname("作業員#xm_d"+'@i)+ "::OnCheck";
	end;
}

1@xm_d.gat,155,98,3		script	作業員#xm_d1	10020,{
	mes "[作業員]";
	mes "ふむ？　新入りかい？";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "仕事で忙しいんだ。";
		mes "雑談はあとにしてくれ。";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : 人形職人……？　あ！　あの爺さんか！　この工場の創業者で人形職人だったな。";
	end;
OnTimer4000:
	unittalk "作業員 : ここにいるおもちゃはみんな、あの爺さんの手で生み出されたといっても過言じゃない。無論、俺もね。";
	end;
OnTimer7000:
	unittalk "作業員 : 中でも、キミちゃんはあの人の最高傑作ともいえるできらしい。爺さんがそう手紙に書いてたのみたよ。";
	end;
OnTimer10000:
	unittalk "作業員 : というかあの爺さんのこと忘れてた……？　あれ……？";
	end;
OnTimer13000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d1");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,1,0xFFFFFF;
	end;
}

1@xm_d.gat,130,72,3		script	作業員#xm_d2	10020,{
	mes "[作業員]";
	mes "ふえ？";
	mes "あなた見かけない顔ね。";
	mes "最近、稼働開始したの？";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "仕事は今日もいっぱいいっぱい。";
		mes "わたしは今日も明日も、仕事よ。";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : 職人のお爺ちゃんをキミちゃんが殺したって噂があるの？　それについてはまったくの出鱈目よ。";
	end;
OnTimer4000:
	unittalk "作業員 : 職人のお爺ちゃんは、わたし達の生みの親だもの。殺すなんてありえないわ。";
	end;
OnTimer7000:
	unittalk "作業員 : ……キミちゃん、もしかしたらその嘘を真にうけたりしてないかな。あの子、純粋だから……。";
	end;
OnTimer10000:
	unittalk "作業員 : あ、こうしちゃいられない。私も職人のお爺ちゃんに会いに行こう。";
	end;
OnTimer13000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d2");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,2,0xFFFFFF;
	end;
}

1@xm_d.gat,134,34,1		script	作業員#xm_d3	10020,{
	mes "[作業員]";
	mes "おい！　いま忙しいんだ。";
	mes "用事があるなら、手短にしてくれ。";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "そっちは仕事ないのか？";
		mes "雑談する暇があるなら働けよ……。";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : 人形職人の爺さんは、この工場の創業者でもあり、腕利きの人形職人でねえ。";
	end;
OnTimer4000:
	unittalk "作業員 : 中でも作品のうちの一つである、動く球体関節人形は大人気だった。";
	end;
OnTimer7000:
	unittalk "作業員 : そういやあ、自分も稼働するのやめたはずなのに。ボケたかなあ……。";
	end;
OnTimer10000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d3");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,3,0xFFFFFF;
	end;
}

1@xm_d.gat,195,28,3		script	作業員#xm_d4	10020,{
	mes "[作業員]";
	mes "……。";
	mes "あら、何か用なのかな？";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "今日も仕事。明日も仕事。";
		mes "仕事しない悪い人形は怒られるよ？";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : キミと人形職人のお爺さんを私が最後に見たのは、休憩室だったかな。";
	end;
OnTimer4000:
	unittalk "作業員 : そういえば最近、休憩室から誰かと誰かの話し声が聞こえるのよね。";
	end;
OnTimer7000:
	unittalk "作業員 : 人形職人のお爺さんはいないのに、誰なんだか。";
	end;
OnTimer10000:
	unittalk "作業員 : ……あれ？　人形職人のお爺さんのこと忘れてた！　いけない！";
	end;
OnTimer13000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d4");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,4,0xFFFFFF;
	end;
}

1@xm_d.gat,228,30,1		script	作業員#xm_d5	10020,{
	mes "[作業員]";
	mes "うーん。";
	mes "うーん。";
	mes "……なんだかメモリの調子が悪い。";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "働けど働けど。";
		mes "我の暮らし、楽にならず……。";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : うーん、記憶が定かじゃないんだけど……。";
	end;
OnTimer4000:
	unittalk "作業員 : 誰かにお爺さんについて、記憶のメモリーを改竄された可能性があるんだ。";
	end;
OnTimer7000:
	unittalk "作業員 : 人間……なんだろうか？　変な笑い声が印象に残ってるけど、よくおぼえてないや。";
	end;
OnTimer10000:
	unittalk "作業員 : でもおかげで、あのお爺さんを思い出せてよかった。ありがとう。";
	end;
OnTimer13000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d5");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,5,0xFFFFFF;
	end;
}

1@xm_d.gat,203,55,3		script	作業員#xm_d6	10020,{
	mes "[作業員]";
	mes "あ～調子悪い。";
	mes "動力源の不調なのかね。";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "仕事でへとへとでね……。";
		mes "雑談したい気分じゃないんだよ。";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : 以前は、観光客が大勢訪れる街だったんだ。爺さんも、嬉しそうだったな。";
	end;
OnTimer4000:
	unittalk "作業員 : ところがある日を境に、詳しい理由はわからないんだけど、観光客も少なくなっていき、この有様だよ。";
	end;
OnTimer7000:
	unittalk "作業員 : さて、爺さんもいないし、このままだと寂しいから、いくとしようかな。";
	end;
OnTimer10000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d6");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,6,0xFFFFFF;
	end;
}

1@xm_d.gat,132,52,1		script	作業員#xm_d7	10020,{
	mes "[作業員]";
	mes "やあ。";
	mes "僕になにか用かな。";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "仕事で忙しいんだ。";
		mes "雑談はやめてくれる？";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : 爺ちゃんが生きてたころ、たまに赤い服の人間を見かけたなあ。";
	end;
OnTimer4000:
	unittalk "作業員 : 爺ちゃんの知り合いなのか、詳細までは知らないんだけどね。";
	end;
OnTimer7000:
	unittalk "作業員 : 後はよく手紙を書いてたよ。誰に書いてたかは知らないけど。";
	end;
OnTimer10000:
	unittalk "作業員 : 手紙かあ。……僕も爺ちゃんに、手紙を書こうかな。";
	end;
OnTimer13000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d7");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,7,0xFFFFFF;
	end;
}

1@xm_d.gat,162,52,1		script	作業員#xm_d8	10020,{
	mes "[作業員]";
	mes "何？";
	mes "私に用ある？";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "私忙しい！　私仕事する!!";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : キミ、見なくなった。あの変な人間、キミと話してるのみたの最後。";
	end;
OnTimer4000:
	unittalk "作業員 : おもちゃもいた。でもおもちゃの様子変だった。なにかあった？　おじいさん、なんでいない？";
	end;
OnTimer7000:
	unittalk "作業員 : 私、おじいさん探してくる。いってくる。";
	end;
OnTimer10000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d8");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,8,0xFFFFFF;
	end;
}

1@xm_d.gat,242,17,5	script	作業員#xm_d9	10020,{
	mes "[作業員]";
	mes "ららら～♪";
	mes "！？";
	mes "今の、き、きいてました!?";
	mes "歌いながら仕事すると効率いいの。";
	mes "でも、今のは忘れてください！";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "……あら、なにもないなら";
		mes "仕事に集中させてほしいわ。";
		mes "仕事してればなにも考えないで";
		mes "すむから……。";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : お爺様のことですか……？　キミが完成し、目を開けた瞬間、心臓病によって天に召されたようです。";
	end;
OnTimer4000:
	unittalk "作業員 : キミはどうも、自分の顔を見てお爺様は亡くなったものと思っているようですが……。";
	end;
OnTimer7000:
	unittalk "作業員 : ただ、どういう結果であれ、キミは最後にお爺様と会えたのですから。";
	end;
OnTimer10000:
	unittalk "作業員 : え？　今からでも遅くない……ですか。……会えるでしょうか。私も……。";
	end;
OnTimer13000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d9");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,9,0xFFFFFF;
	end;
}

1@xm_d.gat,209,15,3	script	作業員#xm_d10	10020,{
	mes "[作業員]";
	mes "ふぁーあ……。";
	mes "むにゃ、なにか用？";
	mes "眠いんだけど……。";
	next;
	if(select("人形職人について尋ねる","何でもない") == 2) {
		mes "[作業員]";
		mes "仕事中の私語は控えろって";
		mes "いわれなかったのー？";
		close;
	}
	initnpctimer;
	set 'flag,1;
	doevent getmdnpcname("#fac2wpc")+ "::OnCheck";
	close;
OnTimer1000:
	unittalk "作業員 : 人間はキミのことを怖がるけれど、キミちゃんは私たちの面倒をよくみてくれるよー。まるで生前のお爺さんみたいに。";
	end;
OnTimer4000:
	unittalk "作業員 : よくキミちゃんに、お爺さんに作ってもらったってアクセサリーのリボンや傘を見せてもらったよー。";
	end;
OnTimer7000:
	unittalk "作業員 : ところでお爺さん、どこにいるのかなー……。";
	end;
OnTimer10000:
	donpcevent getmdnpcname("#fac2wpc")+ "::OnCount";
	hideonnpc getmdnpcname("作業員#xm_d10");
	end;
OnCheck:
	if('flag)
		viewpoint 2,1,1,10,0xFFFFFF;
	end;
}

1@xm_d.gat,131,208,0	script	#bgm04	139,{
	musiceffect "54";
	end;
}

1@xm_d.gat,131,208,0	script	#bgm05	139,{
	musiceffect "105";
	end;
}

1@xm_d.gat,113,207,5	script	道標#2	858,{
	mes "‐^ff0000第3工場はこちら！^000000";
	mes "　第3工場は配送の準備が";
	mes "　完了するまで立ち入ることが";
	mes "　できません。";
	mes "　注意しましょう‐";
	close;
}

1@xm_d.gat,131,208,8	script	囚われたサンタ#2	718,10,10,{
	if(getpartyleader(getcharid(1)) == strcharinfo(0)) {
		if(sc_onparam(SC_MONSTER_TRANSFORM,1)) {
			mes "‐サンタらしき男が";
			mes "　あなたを一瞬みると";
			mes "　小声で話しかけてきた‐";
			next;
			mes "[囚われたサンタ]";
			mes "モンスターの格好をしているが";
			mes "以前、会ったことがあるね。";
		}
		else {
			mes "[囚われたサンタ]";
			mes "……!?";
			mes "また君に会うとは思わなかったよ。";
		}
		mes "君、私を縛っているこの縄を";
		mes "また解いてくれないだろうか……。";
		mes "アンソニにまた今回も";
		mes "幽閉されてしまってね……。";
		next;
		if(select("会話を飛ばす","話を続ける") == 1) {
			mes "‐あなたは縄を解き";
			mes "　ひとしきり話に耳を傾けた‐";
			close2;
			donpcevent getmdnpcname("囚われたサンタ#3")+ "::OnStart2";
			end;
		}
		mes "[囚われたサンタ]";
		mes "頼む……！";
		mes "このままでは、子供たちやあの子に";
		mes "夢や希望を配ることができず";
		mes "悲しい思いをさせてしまうだろう。";
		mes "どうかお願いだ。";
		mes "この縄を解いてくれ……！";
		next;
		if(select("話をやめる","縄を解く") == 1) {
			mes "[囚われたサンタ]";
			mes "そうか……。";
			mes "以前は解いてくれたのに";
			mes "今回は解いてくれないのか。";
			mes "仕方がないとはいえ、";
			mes "淋しいものだな……。";
			close;
		}
		donpcevent getmdnpcname("囚われたサンタ#3")+ "::OnStart";
		close;
	}
	else {
		mes "[囚われたサンタ]";
		mes "君たちのリーダーは誰だい？";
		mes "リーダーの人間に";
		mes "話したいことがあるんだ。";
		close;
	}
OnTouch:
	initnpctimer;
	end;
OnTimer1000:
	stopnpctimer;
	unittalk "囚われたサンタ : アンソニ、目を覚ませ！　そして、早くこの縄を解け！　今ならまだ、お前の罪も軽いはずだ！";
	end;
}

1@xm_d.gat,131,208,8	script	囚われたサンタ#3	718,{
	mes "[囚われたサンタ]";
	mes "いくら今はこの工場に";
	mes "主がいないからといって";
	mes "こんな風にこの場所を荒らし";
	mes "好き勝手に物を盗んで";
	mes "許されるわけがない！";
	close;
OnStart:
	initnpctimer;
	hideonnpc getmdnpcname("囚われたサンタ#2");
	hideoffnpc getmdnpcname("囚われたサンタ#3");
	hideoffnpc getmdnpcname("#bgm04");
	end;
OnStart2:
	unittalk "囚われたサンタ : アンソニは第3工場のどこかにいると思う。すまないが、子供たちやこの工場の未来を頼む……！";
	hideonnpc getmdnpcname("アンソニ#1");
	hideonnpc getmdnpcname("囚われたサンタ#2");
	hideoffnpc getmdnpcname("囚われたサンタ#3");
	hideonnpc getmdnpcname("#bgm04");
	hideoffnpc getmdnpcname("#fac4wp");
	hideoffnpc getmdnpcname("#fac4wp2");
	hideoffnpc getmdnpcname("#bgm05");
	donpcevent getmdnpcname("#fac3ct")+ "::OnStart";
	donpcevent getmdnpcname("#fac3ct2")+ "::OnStart";
	donpcevent getmdnpcname("#fac3ct3")+ "::OnStart";
	end;
OnTimer2000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk1";
	end;
OnTimer4000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk2";
	end;
OnTimer6000:
	unittalk "囚われたサンタ : 主にプレゼントの配給を断られた腹いせとはいえ、おかしいと思わないのか？　主がいない状態で、なぜこの工場が動いているのか！。";
	end;
OnTimer9000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk3";
	end;
OnTimer12000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk4";
	end;
OnTimer16000:
	unittalk "囚われたサンタ : それはお前の都合だろう！　それに子供たちがそんなプレゼントを受け取った時の気持ちを考えてみろ！";
	end;
OnTimer20000:
	unittalk "囚われたサンタ : 正規の依頼で作られなかったおもちゃを配られたと知れば、子供たちの気持ちはどうなる!?";
	end;
OnTimer24000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk5";
	end;
OnTimer27000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk6";
	end;
OnTimer30000:
	unittalk "囚われたサンタ : お前のへりくつは聞いていない！　今すぐにでもこの工場から出て行くんだ！　アンソニ！";
	end;
OnTimer34000:
	announce "工場案内放送 : 第3工場にて発送準備が終わりました。",0x9,0x00ff44;
	end;
OnTimer38000:
	announce "工場案内放送 : 配送部の職員たちは準備をして下さい。",0x9,0x00ff44;
	end;
OnTimer41000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk7";
	end;
OnTimer45000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk8";
	end;
OnTimer49000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk9";
	end;
OnTimer53000:
	donpcevent getmdnpcname("アンソニ#1")+"::OnTalk10";
	end;
OnTimer58000:
	hideonnpc getmdnpcname("アンソニ#1");
	end;
OnTimer60000:
	unittalk "囚われたサンタ : ああ……サンタクロースは……子供たちの未来は……どうなってしまうのだ……。";
	end;
OnTimer64000:
	unittalk "囚われたサンタ : 君がなぜここにいるのかわからないが……あのアンソニという奴を、実力行使で工場から追い出してくれないだろうか。";
	end;
OnTimer68000:
	unittalk "囚われたサンタ : 私たちはこの工場の人形職人からプレゼントの配送を頼まれていたのだが、あのアンソニは人形職人に嫌われ、仕事を干されたんだ。";
	end;
OnTimer72000:
	unittalk "囚われたサンタ : それなのにあいつはそれを逆恨みして、なぜか主がいないのに稼動していたこの工場に目を付け、今じゃ我が物顔で闊歩しているんだ。";
	end;
OnTimer76000:
	unittalk "囚われたサンタ : しかもあいつを止めにきた私を縛ったあげく、人形職人の娘ともいえる人形も得意の舌先三寸で東の部屋から出てこないように仕向けたようだ。";
	end;
OnTimer80000:
	unittalk "囚われたサンタ : 私がなんとかできれば良いのだが、サンタクロース同士は契約の関係上、手を出せないんだ……。";
	end;
OnTimer84000:
	unittalk "囚われたサンタ : アンソニは第3工場のどこかにいると思う。すまないが、子供たちやこの工場の未来を頼む……！";
	hideonnpc getmdnpcname("#bgm04");
	hideoffnpc getmdnpcname("#fac4wp");
	hideoffnpc getmdnpcname("#fac4wp2");
	hideoffnpc getmdnpcname("#bgm05");
	donpcevent getmdnpcname("#fac3ct")+ "::OnStart";
	donpcevent getmdnpcname("#fac3ct2")+ "::OnStart";
	donpcevent getmdnpcname("#fac3ct3")+ "::OnStart";
	end;
}

1@xm_d.gat,131,213,4	script	アンソニ#1	10019,{
	mes "[アンソニ]";
	mes "おいおい。";
	mes "それじゃあまるで俺様が";
	mes "全部悪いみたいじゃないか。";
	mes "使われなくなった工場をせっかく";
	mes "有効利用してるだけなのに。";
	mes "ククク……。";
	close;
OnTalk1:
	unittalk "アンソニ : よく聞けよ爺さん。俺はこの工場が気に入っているんだ。";
	end;
OnTalk2:
	unittalk "アンソニ : この工場の主はもうとっくにくたばっているし、俺様のために働いてくれるようにお願いしてもいいんじゃね～？。";
	end;
OnTalk3:
	unittalk "アンソニ : よくいうぜ。主がいないってことは誰のものでもないってことだろ？　大体、主がいないのになんで稼動してるのかなんて俺様は知らないし、興味もねーよ。";
	end;
OnTalk4:
	unittalk "アンソニ : 要は中を覗いたら、この工場が稼動してた。だからそれを俺様が有効に利用しているだけで、爺さんにとやかく言う権利はないはずだぜ？";
	end;
OnTalk5:
	unittalk "アンソニ : へ……？　子供たちの気持ちだって？";
	end;
OnTalk6:
	unittalk "アンソニ : 別にいいんじゃない？　結果的にはプレゼントじゃないか。ほれ、タンの盛り合わせもバッタの炒め物も、腹に入れば同じだろ？　ククク……。";
	end;
OnTalk7:
	unittalk "アンソニ : お？　プレゼントたちが今日もた～くさん溜まっているな。さて、今日はどんなプレゼントが集まってるかな!?";
	end;
OnTalk8:
	unittalk "アンソニ : おっと、そこの人間。配送用のおもちゃに手を出さなければ、俺様は人間でも邪険にしないぜ。誰かと違って、心が広いからな。";
	end;
OnTalk9:
	unittalk "アンソニ : ここにいるおもちゃや、あの女の人形が手を出さないかどうかまでは保証はできないけどな。ククク……。";
	end;
OnTalk10:
	unittalk "アンソニ : さーて、第3工場の様子でも見てきますかね。";
	end;
}

1@xm_d.gat,143,209,4	script	囚われたサンタ#4	718,5,5,{
	if(checkquest(96405)) {
		mes "[囚われたサンタ]";
		mes "いやはや、世話になったね。";
		mes "なんとお礼を言えばよいか。";
		mes "彼女は、この奥の部屋に";
		mes "今もいるようだ。";
		mes "どうか、彼女も助けてやってくれ。";
		close;
	}
	mes "[囚われたサンタ]";
	mes "これでしばらく、アンソニも";
	mes "この工場には近づかないだろう。";
	mes "あいつの取り柄は";
	mes "体の丈夫さと諦めの悪さだから";
	mes "気に病む必要はない。";
	next;
	mes "[囚われたサンタ]";
	mes "あと、すまないが、";
	mes "あの少女の人形にも迷惑をかけたことを";
	mes "謝っておいてほしい。";
	next;
	mes "[囚われたサンタ]";
	mes "君には本当に世話になったね。";
	if(checkitemblank() == 0) {
		next;
		mes "[囚われたサンタ]";
		mes "おや？　ずいぶんと荷物が多そうだね。";
		mes "少し荷物を減らしてから";
		mes "また来るといい。";
		close;
	}
	set '@flag,checkquest(96400);
	delquest 96400;
	if('@flag & 0x4) {
		set '@user,getmapusers("this");
		if('@user < 12)
			set '@exp,(3500000+500000*'@user) / 7;
		else
			set '@exp,10000000 / 7;
		for(set '@i,0; '@i<7; set '@i,'@i+1)
			getexp '@exp,0;
		mes "ささやかだが、これはお礼だ。";
		mes "受け取ってくれ。";
		getitem 7642,10;
	}
	setquest 96405;
	close;
OnTouch:
	mes "[囚われたサンタ]";
	mes "おお！";
	mes "アンソニを追い出してくれたか！";
	mes "ぜひ、もっと近くに来て";
	mes "話を聞かせてくれないか！";
	close;
}

1@xm_d.gat,107,208,0	warp	#fac4wp	2,2,1@xm_d.gat,87,208
1@xm_d.gat,95,208,0		warp	#fac4wp2	2,2,1@xm_d.gat,115,208

1@xm_d.gat,1,5,3		script	#fac3ct	844,{
OnStart:
	monster getmdmapname("1@xm_d.gat"),229,234,"アンソニ",2988,1,getmdnpcname("#fac3ct")+ "::OnKilled";
	end;
OnKilled:
	killmonster getmdmapname("1@xm_d.gat"),getmdnpcname("#fac3ct2")+"::OnKilled";
	killmonster getmdmapname("1@xm_d.gat"),getmdnpcname("#fac3ct3")+"::OnKilled";
	donpcevent getmdnpcname("#finalbs")+"::OnStart";
	hideonnpc getmdnpcname("囚われたサンタ#3");
	hideoffnpc getmdnpcname("囚われたサンタ#4");
	hideonnpc getmdnpcname("#fac3wp");
	hideonnpc getmdnpcname("#fac3wp2");
	end;
}

1@xm_d.gat,1,5,3		script	#fac3ct2	844,{
OnStart:
	areamonster getmdmapname("1@xm_d.gat"),10,140,90,250,"工場警備員の魂",2992,25,getmdnpcname("#fac3ct2")+ "::OnKilled";
	areamonster getmdmapname("1@xm_d.gat"),10,140,90,250,"捨てられたクマ人形",2995,30,getmdnpcname("#fac3ct2")+ "::OnKilled";
	areamonster getmdmapname("1@xm_d.gat"),10,140,90,250,"怪奇な装飾ツリー",2987,30,getmdnpcname("#fac3ct2")+ "::OnKilled";
	areamonster getmdmapname("1@xm_d.gat"),10,140,90,250,"プレゼントがない幽霊",2993,30,getmdnpcname("#fac3ct2")+ "::OnKilled";
	areamonster getmdmapname("1@xm_d.gat"),10,140,90,250,"包装されなかった人形",2994,30,getmdnpcname("#fac3ct2")+ "::OnKilled";
	end;
OnKilled:
	end;
}

1@xm_d.gat,1,5,3		script	#fac3ct3	844,{
OnStart:
	areamonster getmdmapname("1@xm_d.gat"),165,218,253,250,"工場警備員の魂",2992,10,getmdnpcname("#fac3ct3")+ "::OnKilled";
	areamonster getmdmapname("1@xm_d.gat"),165,218,253,250,"捨てられたクマ人形",2995,15,getmdnpcname("#fac3ct3")+ "::OnKilled";
	areamonster getmdmapname("1@xm_d.gat"),165,218,253,250,"怪奇な装飾ツリー",2987,15,getmdnpcname("#fac3ct3")+ "::OnKilled";
	areamonster getmdmapname("1@xm_d.gat"),165,218,253,250,"プレゼントがない幽霊",2993,15,getmdnpcname("#fac3ct3")+ "::OnKilled";
	end;
OnKilled:
	end;
}

1@xm_d.gat,1,5,3		script	#finalbs	844,{
OnStart:
	initnpctimer;
	end;
OnTimer1000:
	announce "アンソニ : と、とりあえず今回は、人間に免じて出て行ってやるよ！　あばよ！　……イデデデデ。",0x9,0x00ff44;
	end;
OnTimer4000:
	stopnpctimer;
	hideoffnpc getmdnpcname("#fac5wp");
	hideoffnpc getmdnpcname("#fac5wp2");
	announce "キャサリンゼータ : た、大変です！　キ、キミがいたんです！　休憩室にある「関係者以外立ち入り禁止！」と書かれた看板の、後ろにある部屋です！　は、早く来てください!!",0x9,0xff6666;
	end;
}

1@xm_d.gat,144,207,2	script	道標#3	858,{
	mes "‐^ff0000関係者以外立ち入り禁止！^000000";
	mes "　この先の部屋、俺様の許可なく";
	mes "　立ち入ることは禁止だぜ～？";
	mes "　BY　アンソニ‐";
	close;
}

1@xm_d.gat,152,208,0	warp	#fac5wp	2,2,1@xm_d.gat,167,208
1@xm_d.gat,160,208,0	warp	#fac5wp2	2,2,1@xm_d.gat,145,208

1@xm_d.gat,233,183,3	script	セリーヌ・キミ#0	10034,{
	mes "[セリーヌ・キミ]";
	mes "あなたも以前来た人間のように";
	mes "ここを荒らしに来たの……？";
	mes "ねえ、あなたたちはどうして";
	mes "破壊したがるの？";
	close;
OnTalk1:
	unittalk "セリーヌ・キミ : 話……？　……こんな恐ろしい外見をしているわたしの話なんて、誰も聞きいてくれない！　おじいちゃんも……おもちゃたちも……！";
	end;
OnTalk2:
	unittalk "セリーヌ・キミ : ひどいことをする子じゃない……？　じゃあ、おじいちゃんはどうして、もう一度目を開けて、わたしをみてくれなかったの!?";
	end;
OnTalk3:
	unittalk "セリーヌ・キミ : おじいちゃん、わたしの顔を見てびっくりしたあと、わたしから遠ざかって動かなくなった……。わたしがいくら体を揺すっても、名前をよんでも答えてくれなかった……。";
	end;
OnTalk4:
	unittalk "セリーヌ・キミ : おじいちゃん……病気……だったの……？";
	end;
OnTalk5:
	unittalk "セリーヌ・キミ : わたし……が……わたしの顔がこんなだから……おじいちゃん、びっくりして心臓がとまっちゃったの……？";
	end;
OnTalk6:
	unittalk "セリーヌ・キミ : え……？　……わたし、誤解していたの……？　わたしがおじいちゃんを殺したわけじゃないの……？　嫌われたわけじゃないの？";
	end;
OnTalk7:
	unittalk "セリーヌ・キミ : わ……わたし……これが……わたし……。醜い……怖い……わたしの醜い心そのまま……！　こんなのじゃ、みんな、みんな……わたしを……";
	end;
OnTalk8:
	unittalk "セリーヌ・キミ : わたしがこの部屋にいる理由……醜いわたしがうろうろしたら、みんな怖がる……逃げるって……言われた……。だからわたし、ここに……。";
	end;
OnTalk9:
	unittalk "セリーヌ・キミ : おじいちゃんも……わたしなんか愛してなかった……！　赤い服のお姉ちゃんも、わたしを騙して……わたしを笑いものにするつもりだったんでしょ……！";
	end;
}

1@xm_d.gat,222,183,0	script	#jeton1	139,7,7,{
OnTouch:
	mes "‐キミがまた暴走を始めそうだ‐";
	mes "　";
	mes "‐キャサリンゼータの話を";
	mes "　聞きますか？‐";
	next;
	switch(select("聞かずに進める","話を聞く")) {
	case 1:
		hideonnpc getmdnpcname("#jeton1");
		hideoffnpc getmdnpcname("#bgm03");
		donpcevent getmdnpcname("#finalbs2")+"::OnStart2";
		close;
	case 2:
		hideonnpc getmdnpcname("#jeton1");
		hideoffnpc getmdnpcname("#bgm02");
		donpcevent getmdnpcname("#finalbs2")+"::OnStart";
		close;
	}
}

1@xm_d.gat,222,183,0	script	#bgm02	139,7,7,{
	musiceffect "101";
	end;
}

1@xm_d.gat,222,183,6	script	キャサリンゼータ#5	10032,{
	mes "[キャサリンゼータ]";
	mes "き……気を付けて下さい！";
	mes "キミは普通の状態じゃなさそうです。";
	mes "声をかけているのですが";
	mes "どうも様子がおかしくて……。";
	mes "一緒に声をかけてください！";
	close;
OnTalk1:
	unittalk "キャサリンゼータ : キミ！　私の話を聞いて。私とこの人は、ここを荒らすために来たわけではない！　あなたと話がしたいの。";
	end;
OnTalk2:
	unittalk "キャサリンゼータ : 私は……あなたがひどいことをする子じゃないって信じてる。　だから教えて、キミ。何があったの？　私のこの顔はあなたのせいなの？";
	end;
OnTalk3:
	unittalk "キャサリンゼータ : !?　一体、誰が喋ってるの……。キミ以外に声が……。";
	end;
OnTalk4:
	unittalk "キャサリンゼータ : キミ……！　その声に耳を傾けないで！　お爺さんはあなたの名前を呼ぶ前に、病気のせいで……";
	end;
OnTalk5:
	unittalk "キャサリンゼータ : そう！　病気だよ！　命を吹き込まれたあなたが動いたその瞬間、お爺さんはあまりの喜びに……。";
	end;
OnTalk6:
	unittalk "キャサリンゼータ : キミ、それは違う！　あなたはお爺さんを殺してなんかいない！　お爺さんも、あなたに殺されたなんて思っていない!!";
	end;
OnTalk7:
	unittalk "キャサリンゼータ : ち、違う！　……駄目だわ。キミの自我が分裂しています！　このままにしておくと危険です……！　仕方ありません……あの子を、止めてください！";
	end;
OnTalk8:
	unittalk "キャサリンゼータ : 力づくで構いません。キミが壊れたら……私が……私がなんとかしてみせます。なので、冒険者様は自分の安全を優先してください！";
	end;
OnTalk9:
	unittalk "キャサリンゼータ : 工場の空気もおかしい……。冒険者様！　私はキミを止めるための手がかりがないか探してきます！";
	end;
OnTalk10:
	unittalk "キャサリンゼータ : キミの自我が分裂しています！　このままにしておくと危険です……！　あの子を、止めてください！";
	end;
}

1@xm_d.gat,216,193,3	script	xm_d#eff_f01	844,{
OnStart:
	misceffect 343;
	end;
}
1@xm_d.gat,226,193,3	duplicate(xm_d#eff_f01)	xm_d#eff_f02	844
1@xm_d.gat,236,193,3	duplicate(xm_d#eff_f01)	xm_d#eff_f03	844
1@xm_d.gat,216,183,3	duplicate(xm_d#eff_f01)	xm_d#eff_f04	844
1@xm_d.gat,226,183,3	duplicate(xm_d#eff_f01)	xm_d#eff_f05	844
1@xm_d.gat,236,183,3	duplicate(xm_d#eff_f01)	xm_d#eff_f06	844
1@xm_d.gat,216,173,3	duplicate(xm_d#eff_f01)	xm_d#eff_f07	844
1@xm_d.gat,226,173,3	duplicate(xm_d#eff_f01)	xm_d#eff_f08	844
1@xm_d.gat,236,173,3	duplicate(xm_d#eff_f01)	xm_d#eff_f09	844

1@xm_d.gat,2,2,3		script	#bear	844,{
	end;
OnStart:
	if(rand(5))
		end;
	if(getmapmobs(getmdmapname("1@xm_d.gat"),getmdnpcname("#bear")+ "::OnKilled") >= 10)
		end;
	set '@user,getmapusers("this");
	if('@user >= 6)
		set '@num,3;
	else if('@user >= 3)
		set '@num,2;
	else
		set '@num,1;
	areamonster getmdmapname("1@xm_d.gat"),213,173,243,193,"捨てられたクマ人形",2995,'@num,getmdnpcname("#bear")+ "::OnKilled";
	end;
OnKilled:
	// dummy
	end;
}

1@xm_d.gat,233,183,0	script	#kimion1	139,7,7,{
OnTouch:
	initnpctimer;
	hideonnpc getmdnpcname("#kimion1");
	end;
OnTimer5000:
	donpcevent getmdnpcname("セリーヌ・キミ#2")+"::OnTalk";
	misceffect 247,getmdnpcname("セリーヌ・キミ#2");
	end;
OnTimer10000:
	stopnpctimer;
	hideonnpc getmdnpcname("セリーヌ・キミ#2");
	hideoffnpc getmdnpcname("#bgm03");
	hideonnpc getmdnpcname("セリーヌ・キミ#0");
	hideonnpc getmdnpcname("キャサリンゼータ#5");
	donpcevent getmdnpcname("xm_d#heal_c")+"::OnStart";
	end;
}

1@xm_d.gat,233,183,3	script	セリーヌ・キミ#2	10034,{
	mes "[セリーヌ・キミ]";
	mes "……わたしは醜い。";
	mes "……わたしは怖い。";
	mes "……みんな本当はわたしを嫌ってる。";
	mes "……おじいちゃんも、おもちゃも。";
	mes "……あなたも、そうでしょ？";
	close;
OnTalk:
	unittalk "セリーヌ・キミ :  あなたも……わたしを殺しに来たの？　あなたも……わたしを笑いに来たの？　あなたも……わたしを醜いって思うの？あなたも……わたしを嫌いって言うの？";
	end;
}

1@xm_d.gat,228,183,0	script	#bgm03	139,7,7,{
	musiceffect "101";
	end;
}

1@xm_d.gat,1,5,3		script	#finalbs2	844,{
OnStart:
	initnpctimer;
	end;
OnTimer2000:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk1";
	end;
OnTimer5000:
	donpcevent getmdnpcname("セリーヌ・キミ#0")+"::OnTalk1";
	end;
OnTimer7000:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk2";
	end;
OnTimer12000:
	announce "キミの幻影 : 信じる？　……ウソだ！",0x9,0xff8800;
	end;
OnTimer13000:
	donpcevent getmdnpcname("セリーヌ・キミ#0")+"::OnTalk2";
	end;
OnTimer18000:
	donpcevent getmdnpcname("セリーヌ・キミ#0")+"::OnTalk3";
	end;
OnTimer20000:
	announce "キミの幻影 : ソウダヨ、キミ！　あの人はアナタのことを見て驚いていたヨ！　アナタを恐れていたんダヨ……。カワイソウなキミ……。",0x9,0xff8800;
	end;
OnTimer23000:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk3";
	end;
OnTimer26000:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk4";
	end;
OnTimer29000:
	donpcevent getmdnpcname("セリーヌ・キミ#0")+"::OnTalk4";
	end;
OnTimer32000:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk5";
	end;
OnTimer34000:
	announce "キミの幻影 : ソウ！　驚愕ダよ！　命ヲ吹き込まれたアナタが動いたその瞬間、オ爺さんはあまりの醜さニ……驚いて、心臓がトマッテ死んじゃっタの。",0x9,0xff8800;
	end;
OnTimer37000:
	donpcevent getmdnpcname("セリーヌ・キミ#0")+"::OnTalk5";
	end;
OnTimer39000:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk6";
	end;
OnTimer42000:
	donpcevent getmdnpcname("セリーヌ・キミ#0")+"::OnTalk6";
	end;
OnTimer44000:
	announce "キミの幻影 : 忘れたノ？　キミ。あの人ガ見せてくれタ自身ノ姿を、再度見てみなさイ。鏡を見テ、ドウ？",0x9,0xff8800;
	end;
OnTimer47000:
	donpcevent getmdnpcname("セリーヌ・キミ#0")+"::OnTalk7";
	end;
OnTimer49000:
	announce "キミの幻影 : ねエ、キミ。大体お爺さんがキミを愛してたナラ、なんデ、こんな醜い顔にしたの？　お人形は顔が命なのに。クスクス……。",0x9,0xff8800;
	end;
OnTimer52000:
	donpcevent getmdnpcname("セリーヌ・キミ#0")+"::OnTalk8";
	end;
OnTimer55000:
	donpcevent getmdnpcname("セリーヌ・キミ#0")+"::OnTalk9";
	end;
OnTimer56000:
	misceffect 247,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer57000:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk7";
	end;
OnTimer60000:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk8";
	end;
OnTimer61000:
	misceffect 247,getmdnpcname("セリーヌ・キミ#0");
	misceffect 72,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer63000:
	announce "キミの幻影 : 怒りなサイ。悲しみなサイ。ダレもキミの味方なんていないんダヨ。クスクスクスクス……。",0x9,0xff8800;
	misceffect 72,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer64000:
	misceffect 72,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer66000:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk9";
	misceffect 72,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer67000:
	hideonnpc getmdnpcname("キャサリンゼータ#5");
	misceffect 72,getmdnpcname("セリーヌ・キミ#0");
	misceffect 30,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer68000:
	misceffect 72,getmdnpcname("セリーヌ・キミ#0");
	misceffect 30,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer69000:
	announce "キミの幻影 : かわいそう！　カワイソウな醜いキミ！",0x9,0xff8800;
	misceffect 30,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer70000:
	misceffect 30,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer72000:
	misceffect 90,getmdnpcname("セリーヌ・キミ#0");
	end;
OnTimer75000:
	stopnpctimer;
	hideonnpc getmdnpcname("セリーヌ・キミ#0");
	hideonnpc getmdnpcname("#bgm02");
	hideoffnpc getmdnpcname("#bgm03");
	hideonnpc getmdnpcname("セリーヌ・キミ#0");
	hideonnpc getmdnpcname("キャサリンゼータ#5");
	donpcevent getmdnpcname("xm_d#heal_c")+"::OnStart";
	end;
OnStart2:
	donpcevent getmdnpcname("キャサリンゼータ#5")+"::OnTalk10";
	hideonnpc getmdnpcname("セリーヌ・キミ#0");
	hideonnpc getmdnpcname("キャサリンゼータ#5");
	donpcevent getmdnpcname("xm_d#heal_c")+"::OnStart";
	end;
}

1@xm_d.gat,1,5,3		script	xm_d#heal_c	844,{
OnStart:
	initnpctimer;
	set 'mob1,callmonster(getmdmapname("1@xm_d.gat"),232,180,"セリーヌ・キミ",2996,getmdnpcname("xm_d#heal_c")+"::OnKilled1");
	set 'mob2,callmonster(getmdmapname("1@xm_d.gat"),226,190,"キミの幻影",2997,getmdnpcname("xm_d#heal_c")+"::OnKilled2");
	end;
OnTimer5000:
	donpcevent getmdnpcname("#bear")+"::OnStart";
	end;
OnCheck:
OnTimer10000:
	if('mob1) {
		set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob1);
		if('@x < 212 || '@y > 201 || '@y < 166) {
			stopnpctimer;
			announce "セリーヌ・キミ : ダメ！　この場所から離れちゃダメッ！",0x9,0xff6666;
			set 'mob1,0;
			killmonster getmdmapname("1@xm_d.gat"),getmdnpcname("xm_d#heal_c")+"::OnKilled1";
			set 'mob2,0;
			killmonster getmdmapname("1@xm_d.gat"),getmdnpcname("xm_d#heal_c")+"::OnKilled2";
			hideoffnpc getmdnpcname("#kimion1");
			hideoffnpc getmdnpcname("セリーヌ・キミ#2");
			end;
		}
	}
	if('mob1 && 'mob2) {
		set 'mob1hp,getmobhp('mob1);
		set 'mob2hp,getmobhp('mob2);
		if('mob1hp - 'mob2hp > 100000) {
			unittalk 'mob1,"セリーヌ・キミ : わたしとあなたは表裏一体。わたしがあなたを回復するの……。";
			set '@diff,'mob1hp - 'mob2hp;
		} else if('mob2hp - 'mob1hp > 100000) {
			unittalk 'mob2,"キミの幻影 : ワタシがキミを回復させル……。";
			set '@diff,'mob2hp - 'mob1hp;
		} else {
			switch(rand(10)) {
			case 0: unittalk 'mob1,"セリーヌ・キミ : わたしにとっての居場所はここしかないのに……なぜ、放っておいてくれないの……。"; break;
			case 1: unittalk 'mob1,"セリーヌ・キミ : 愛なんていらない……必要ない……。わたしには必要ない……。"; break;
			case 2: unittalk 'mob1,"セリーヌ・キミ : わたしは1人でいなきゃいけない……。可愛くないお人形は、誰にも必要とされない……。"; break;
			case 3: unittalk 'mob1,"セリーヌ・キミ : わたしと同じ、醜い顔になろうよ……。……仲間になろうよ。"; break;
			case 4: unittalk 'mob1,"セリーヌ・キミ : 死んじゃえ……。"; break;
			case 5: unittalk 'mob1,"セリーヌ・キミ : やだよ……怖いよ……おじいちゃん……。なんで、ここに居てくれないの……！"; break;
			case 6: unittalk 'mob1,"セリーヌ・キミ : 嫌い。嫌い……！　あっちにいって！"; break;
			default: break;
			}
			initnpctimer;
			end;
		}
		set 'healhp,('mob1hp+'mob2hp)/2 + '@diff;
		setmobhp 'mob1,'healhp;
		setmobhp 'mob2,'healhp;
		set 'healhp,getmobhp('mob1);
		for(set '@i,1;'@i<=9;set '@i,'@i+1)
			misceffect 343,getmdnpcname("xm_d#eff_f0"+'@i);
	}
	else
		initnpctimer;
	end;
OnTimer11000:
	announce "キャサリンゼータ : セリーヌ・キミとキミの幻影の体力が治癒によって" +'healhp+ " になりました！　気をつけてください！",0x9,0xff6666;
	end;
OnTimer15000:
	announce "キャサリンゼータ : 冒険者様！　私には分かるのですが、セリーヌ・キミと幻影の体力に大きく差があると、さっきよりも生命維持装置の活動が活発になっているようです。……なるべく均一に攻撃した方がいいかもしれません！",0x9,0xff6666;
	end;
OnTimer21000:
	initnpctimer;
	donpcevent getmdnpcname("xm_d#heal_c")+"::OnCheck";
	end;
OnKilled1:
	set 'mob1,0;
	if('mob2 == 0) {
		donpcevent getmdnpcname("#finalbs_e")+"::OnStart";
	}
	end;
OnKilled2:
	set 'mob2,0;
	if('mob1 == 0) {
		donpcevent getmdnpcname("#finalbs_e")+"::OnStart";
	}
	end;
}

1@xm_d.gat,1,5,3		script	#finalbs_e	844,{
OnStart:
	announce "セリーヌ・キミ : わたしを倒しても無駄だよ……。またわたしはこの工場にもどってくるんだから……。",0x9,0xff6666,0x190,15;
	set '@user,getmapusers("this");
	hideoffnpc getmdnpcname("#fac6wp");
	hideoffnpc getmdnpcname("#jeton2");
	hideoffnpc getmdnpcname("キャサリンゼータ#6");
	hideoffnpc getmdnpcname("包装されたプレゼント#00");
	killmonster getmdmapname("1@xm_d.gat"),getmdnpcname("#bear")+"::OnKilled";
	donpcevent getmdnpcname("包装されたプレゼント#00")+"::OnStart";
	setarray '@box,0,7,10,4,9,5,1,12,2,8,6,11,3;
	for(set '@i,1;'@i<='@user; set '@i,'@i+1) {
		hideoffnpc getmdnpcname("包装されたプレゼント#"+'@box['@i]);
	}
	sleep 6000;
	announce "キャサリンゼータ : !?　キミを退けたんですか!?　凄い……。とりあえず、その部屋の南西にある通路から、私がいる場所へきてください！",0x9,0xffff00,0x190,12;
	end;
}

1@xm_d.gat,205,159,0	warp	#fac6wp	2,2,1@xm_d.gat,205,147

1@xm_d.gat,218,145,0	script	#jeton2	139,5,5,{
	initnpctimer;
	hideonnpc getmdnpcname("#jeton2");
	end;
OnTimer1000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk1";
	end;
OnTimer4000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk2";
	end;
OnTimer6000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk3";
	end;
OnTimer9000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk4";
	end;
OnTimer12000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk5";
	end;
OnTimer16000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk6";
	end;
OnTimer22000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk7";
	end;
OnTimer27000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk8";
	end;
OnTimer32000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk9";
	end;
OnTimer37000:
	donpcevent getmdnpcname("キャサリンゼータ#6")+"::OnTalk10";
	end;
OnTimer40000:
	stopnpctimer;
	hideonnpc getmdnpcname("キャサリンゼータ#6");
	hideoffnpc getmdnpcname("非常口#exwp1");
	announce "キャサリンゼータ : 非常口を開放しました。お礼も置いておきましたので、非常口から外に出て下さいね。",0x9,0xffff00;
	end;
}

1@xm_d.gat,218,150,5	script	非常口#exwp1	10007,{
	mes "‐非常口から工場の外に出ますか？‐";
	next;
	if(select("もう少し見回ってみる","外に出る") == 1) {
		mes "‐非常口の作動を中止します‐";
		close;
	}
	if(checkitemblank() == 0) {
		mes "‐アイテムの種類数が多くて";
		mes "　報酬を持つことができない。";
		mes "　種類数を減らしてから";
		mes "　外に出よう‐";
		close;
	}
	if(checkquest(96405) & 0x4) {
		delquest 96405;
		getitem 7642,30;
	}
	if(HORROR_1QUE < 13)
		set HORROR_1QUE,HORROR_1QUE + 1;
	warp "xmas.gat",233,300;
	end;
}

1@xm_d.gat,218,145,5	script	キャサリンゼータ#6	10032,{
	end;
OnTalk1:
	unittalk "キャサリンゼータ : ……ここまでくれば大丈夫なはずです。";
	end;
OnTalk2:
	unittalk "キャサリンゼータ : 結局、手がかりも見つからず、危険な目にあわせてすいません……。";
	end;
OnTalk3:
	unittalk "キャサリンゼータ : でも、最後に少しは私の人形職人見習いとしての目が役にたったみたいで、良かったです。";
	end;
OnTalk4:
	unittalk "キャサリンゼータ : それにしても、幻影の声というものの正体は何だったんですかね？　どうしてキミにあんな酷いことを……。";
	end;
OnTalk5:
	unittalk "キャサリンゼータ : きっと私の顔の呪いもその正体不明の声が犯人ではないかと思っています。確証はないのですが……。";
	end;
OnTalk6:
	unittalk "キャサリンゼータ : 結局、お爺さんの気持ちはきちんとキミに届いていなかったのですね……。残念です……。";
	end;
OnTalk7:
	unittalk "キャサリンゼータ : 何にしろ、キミの魂がまた戻って来てもいいように、ここはしっかり管理しておいた方が良さそうです。";
	end;
OnTalk8:
	unittalk "キャサリンゼータ : でも私はまだ、あきらめていません。真実もまだはっきりしていないし。だからまた良ければ、力を貸してください。";
	end;
OnTalk9:
	unittalk "キャサリンゼータ : 外に出る出口は開けておきます。私が先に行くのでついてきてください。";
	end;
OnTalk10:
	unittalk "キャサリンゼータ : ……いつかキミにも、お爺さんやみんなの気持ちをちゃんと届けられたらいいな。";
	end;
}

1@xm_d.gat,148,218,5	script	脱出口#001	10007,{
	mes "‐どうやら緊急用の脱出口が";
	mes "　何かの拍子で作動したようです。";
	mes "　この脱出口から";
	mes "　街に戻れるようですが";
	mes "　まだ工場に用事があるなら";
	mes "　出ない方が良いでしょう‐";
	next;
	if(select("まだ出ない","外に出る") == 1) {
		mes "‐あなたはその場を離れた‐";
		close;
	}
	warp "xmas.gat",233,300;
	end;
}

1@xm_d.gat,1,1,0		script	xm_d#Barricade00	139,{
OnStart:
	areasetcell getmdmapname("1@xm_d.gat"),218,154,220,165,1;
	areasetcell getmdmapname("1@xm_d.gat"),218,202,220,213,1;
	end;
}
1@xm_d.gat,218,154,1	script	#Barricade1	1905,{}
1@xm_d.gat,218,155,1	script	#Barricade2	1905,{}
1@xm_d.gat,218,156,1	script	#Barricade3	1905,{}
1@xm_d.gat,218,157,1	script	#Barricade4	1905,{}
1@xm_d.gat,218,158,1	script	#Barricade5	1905,{}
1@xm_d.gat,218,159,1	script	#Barricade6	1905,{}
1@xm_d.gat,218,160,1	script	#Barricade7	1905,{}
1@xm_d.gat,218,161,1	script	#Barricade8	1905,{}
1@xm_d.gat,218,162,1	script	#Barricade9	1905,{}
1@xm_d.gat,218,163,1	script	#Barricade10	1905,{}
1@xm_d.gat,218,164,1	script	#Barricade11	1905,{}
1@xm_d.gat,218,165,1	script	#Barricade12	1905,{}
1@xm_d.gat,218,202,1	script	#Barricade13	1905,{}
1@xm_d.gat,218,203,1	script	#Barricade14	1905,{}
1@xm_d.gat,218,204,1	script	#Barricade15	1905,{}
1@xm_d.gat,218,205,1	script	#Barricade16	1905,{}
1@xm_d.gat,218,206,1	script	#Barricade17	1905,{}
1@xm_d.gat,218,207,1	script	#Barricade18	1905,{}
1@xm_d.gat,218,208,1	script	#Barricade19	1905,{}
1@xm_d.gat,218,209,1	script	#Barricade20	1905,{}
1@xm_d.gat,218,210,1	script	#Barricade21	1905,{}
1@xm_d.gat,218,211,1	script	#Barricade22	1905,{}
1@xm_d.gat,218,212,1	script	#Barricade23	1905,{}
1@xm_d.gat,218,213,1	script	#Barricade24	1905,{}

1@xm_d.gat,10,24,0	script	alert#61	139,10,10,{
OnTouch:
	if(sc_onparam(SC_MONSTER_TRANSFORM,1) != 1246) {
		initnpctimer;
		musiceffect "125";
		misceffect 124;
		hideonnpc;
		set '@dummy,getmapxy('@map$,'@x,'@y,1,getmdnpcname(strnpcinfo(0)));
		areamonster '@map$,'@x-5,'@y-5,'@x+5,'@y+5,"おもちゃ工場警備兵",2990,6,getmdnpcname(strnpcinfo(0))+"::OnKilled";
	}
	end;
OnTimer1000:
	switch(rand(10)) {
	default:announce "工場案内放送 : 警備兵の出動が必要です。ただちに外部の者を制圧して下さい。",0x9,0x00ffff; break;
	case 1:announce "工場案内放送 : 侵入者が人間でないことを祈ります。もし万が一人間だった場合はただちに排除して下さい。",0x9,0x00ffff; break;
	case 2:announce "警備隊放送 : 作業員ではない外部の者はただちに工場の外に出て下さい。",0x9,0xffff00; break;
	case 3:announce "工場案内放送 : あまり嬉しくないお知らせです。外部の生命体が感知されました。ただちに警備隊は出動して下さい。",0x9,0x00ff88; break;
	case 4:announce "警報 : 工場長様が視察に参ります。外部の者を早く処理するようにしましょう。",0x9,0xff4444; break;
	case 5:announce "工場案内放送 : 侵入者の存在が識別されました。判定コードAX0829。形態、人間、排除をお願いします。",0x9,0x00ffff; break;
	case 6:announce "警備隊放送 : 侵入者を発見した！　人間だと思われる！　直ちに排除する！",0x9,0xffff00; break;
	case 7:announce "工場案内放送 : 外部の者は今すぐ両手を上げて投降して下さい。従わない場合は発砲します。",0x9,0x00ffff; break;
	}
	end;
OnTimer4000:
	announce "キャサリンゼータ : その恰好ではばれてしまいます！　早く作業服に着替えてください！",0x9,0xff6666;
	end;
OnTimer60000:
	hideoffnpc;
	stopnpctimer;
	killmonster getmdmapname("1@xm_d.gat"),getmdnpcname(strnpcinfo(0))+"::OnKilled";
	end;
OnKilled:
	end;
}
1@xm_d.gat,30,24,0	duplicate(alert#61)	alert#62	139,10,10
1@xm_d.gat,50,24,0	duplicate(alert#61)	alert#63	139,10,10
1@xm_d.gat,70,24,0	duplicate(alert#61)	alert#64	139,10,10
1@xm_d.gat,90,24,0	duplicate(alert#61)	alert#65	139,10,10
1@xm_d.gat,10,44,0	duplicate(alert#61)	alert#66	139,10,10
1@xm_d.gat,30,44,0	duplicate(alert#61)	alert#67	139,10,10
1@xm_d.gat,50,44,0	duplicate(alert#61)	alert#68	139,10,10
1@xm_d.gat,70,44,0	duplicate(alert#61)	alert#69	139,10,10
1@xm_d.gat,90,44,0	duplicate(alert#61)	alert#70	139,10,10
1@xm_d.gat,110,44,0	duplicate(alert#61)	alert#71	139,10,10
1@xm_d.gat,10,64,0	duplicate(alert#61)	alert#72	139,10,10
1@xm_d.gat,30,64,0	duplicate(alert#61)	alert#73	139,10,10
1@xm_d.gat,50,64,0	duplicate(alert#61)	alert#74	139,10,10
1@xm_d.gat,70,64,0	duplicate(alert#61)	alert#75	139,10,10
1@xm_d.gat,90,64,0	duplicate(alert#61)	alert#76	139,10,10
1@xm_d.gat,110,64,0	duplicate(alert#61)	alert#77	139,10,10
1@xm_d.gat,10,84,0	duplicate(alert#61)	alert#78	139,10,10
1@xm_d.gat,30,84,0	duplicate(alert#61)	alert#79	139,10,10
1@xm_d.gat,50,84,0	duplicate(alert#61)	alert#80	139,10,10
1@xm_d.gat,70,84,0	duplicate(alert#61)	alert#81	139,10,10
1@xm_d.gat,90,84,0	duplicate(alert#61)	alert#82	139,10,10
1@xm_d.gat,110,84,0	duplicate(alert#61)	alert#83	139,10,10
1@xm_d.gat,10,104,0	duplicate(alert#61)	alert#84	139,10,10
1@xm_d.gat,30,104,0	duplicate(alert#61)	alert#85	139,10,10
1@xm_d.gat,50,104,0	duplicate(alert#61)	alert#86	139,10,10
1@xm_d.gat,70,104,0	duplicate(alert#61)	alert#87	139,10,10
1@xm_d.gat,90,104,0	duplicate(alert#61)	alert#88	139,10,10
1@xm_d.gat,110,104,0	duplicate(alert#61)	alert#89	139,10,10
1@xm_d.gat,155,20,0		duplicate(alert#61)	alert#90	139,10,10
1@xm_d.gat,180,50,0		duplicate(alert#61)	alert#91	139,10,10
1@xm_d.gat,205,80,0		duplicate(alert#61)	alert#92	139,10,10
1@xm_d.gat,230,110,0	duplicate(alert#61)	alert#93	139,10,10
1@xm_d.gat,180,20,0		duplicate(alert#61)	alert#94	139,10,10
1@xm_d.gat,180,50,0		duplicate(alert#61)	alert#95	139,10,10
1@xm_d.gat,180,80,0		duplicate(alert#61)	alert#96	139,10,10
1@xm_d.gat,205,20,0		duplicate(alert#61)	alert#97	139,10,10
1@xm_d.gat,205,50,0		duplicate(alert#61)	alert#98	139,10,10
1@xm_d.gat,205,80,0		duplicate(alert#61)	alert#99	139,10,10
1@xm_d.gat,205,110,0	duplicate(alert#61)	alert#100	139,10,10
1@xm_d.gat,230,20,0		duplicate(alert#61)	alert#101	139,10,10
1@xm_d.gat,230,50,0		duplicate(alert#61)	alert#102	139,10,10
1@xm_d.gat,230,80,0		duplicate(alert#61)	alert#103	139,10,10
1@xm_d.gat,230,110,0	duplicate(alert#61)	alert#104	139,10,10

1@xm_d.gat,217,140,3	script	包装されたプレゼント#1	10005,{
	// ダイヤモンド１カラット、ダイヤモンド２カラット、ダイヤモンド３カラット、金塊、銀塊、白金の塊、血塗られた古木の枝
	setarray '@gain,730,730,730,730,731,731,732,732,7228,7229,7230,12103;
	setarray '@rate,800,500,300,300,500,200,300,100, 250, 250, 250,   10;
	set '@dummy,getmapxy('@map$,'@x,'@y,1,getmdnpcname(strnpcinfo(0)));
	misceffect 10;
	hideonnpc;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@xs,'@x+rand(5)-2;
		set '@ys,'@y+rand(5)-2;
		if(rand(1000) < '@rate['@i])
			dropitem getmdmapname("1@xm_d.gat"),'@xs,'@ys,'@gain['@i],1,0;
	}
	end;
}
1@xm_d.gat,220,143,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#2	10005
1@xm_d.gat,225,144,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#3	10005
1@xm_d.gat,227,139,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#4	10005
1@xm_d.gat,226,135,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#5	10005
1@xm_d.gat,223,132,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#6	10005
1@xm_d.gat,217,128,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#7	10005
1@xm_d.gat,211,132,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#8	10005
1@xm_d.gat,208,135,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#9	10005
1@xm_d.gat,207,139,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#10	10005
1@xm_d.gat,209,144,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#11	10005
1@xm_d.gat,214,143,3	duplicate(包装されたプレゼント#1)	包装されたプレゼント#12	10005

1@xm_d.gat,217,135,3	script	包装されたプレゼント#00	10005,{
	// 血塗られたコイン、閉ざされた心の箱
	// 血塗られた古木の枝、古い洋傘、瑞々しいバラ、シャドウウォーカー[1]、赤いランタン、傷ついた心、優しい心
	setarray '@gain,12103,13442,18848,2486,2976,2977,2978;
	setarray '@rate,   10,   15,   25,  25,  10,   5,   5;
	stopnpctimer;
	misceffect 10;
	hideonnpc;
	if(rand(100) < 50)
		set '@gain2,7642;
	else
		set '@gain2,22534;
	dropitem getmdmapname("1@xm_d.gat"),217+rand(5)-2,135+rand(5)-2,'@gain2,1,0;
	for(set '@i,0; '@i<getarraysize('@gain); set '@i,'@i+1) {
		set '@x,217+rand(5)-2;
		set '@y,135+rand(5)-2;
		if(rand(1000) < '@rate['@i])
			dropitem getmdmapname("1@xm_d.gat"),'@x,'@y,'@gain['@i],1,0;
	}
	end;
OnStart:
OnTimer3000:
	initnpctimer;
	misceffect 100;
	end;
}
