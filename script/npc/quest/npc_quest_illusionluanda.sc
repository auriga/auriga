//= Auriga Script ==============================================================
// Ragnarok Online Illusion of Luanda Quest Script	by refis
//= Registry ===================================================================
// IL_LUANDA_QUE -> 0～23
//==============================================================================

beach_dun2.gat,248,254,4	script	トーテム#ILU_001	10043,{
	mes "‐部族のシンボルだろうか？";
	mes "　微かに青く光っている‐";
	next;
	if(select("触ってみる","そのままにしておく") == 2) {
		mes "‐その場を去った‐";
		close;
	}
	if(BaseLevel < 170) {
		mes "^ff0000【インフォメーション】";
		mes "クエスト「ルワンダに伝える話」は";
		mes "BaseLv170以上で進行可能です。^000000";
		close;
	}
	if(IL_LUANDA_QUE == 0) {
		setquest 5847;
		set IL_LUANDA_QUE,1;
	}
	mes "‐青い光に吸い込まれるようだ‐";
	close2;
	if(IL_LUANDA_QUE < 23)
		warp "com_d02_i_q.gat", 246, 248;
	else
		warp "com_d02_i.gat", 246, 248;
	end;
}

com_d02_i_q.gat,254,243,0	warp	ILU_Luanda#ILU_003	1,1,beach_dun2.gat,249,243

com_d02_i_q.gat,241,255,4	script	守護者ルワンダ#ILU_005	843,13,13,{
	switch(IL_LUANDA_QUE) {
	case 1:
		emotion 1;
		mes "[ルワンダ]";
		mes "あなたは？";
		next;
		menu "名乗る",-;
		mes "[ルワンダ]";
		mes "あ、そういえば。";
		mes "モンスターの侵略を防ぐため";
		mes "村で冒険者を雇った";
		mes "と聞いています。";
		mes "それがあなたですね？";
		next;
		mes "[ルワンダ]";
		mes "それにしても、";
		mes "どこかでお会いしたような……？";
		mes "見覚えがあるように";
		mes "感じるのは何故でしょう。";
		next;
		mes "[ルワンダ]";
		mes "いや、私が他人の顔のことを言える";
		mes "立場ではありません……。";
		mes "なにせ三つ子ですので、ハハ。";
		mes "きっと、勘違いでしょう。";
		next;
		mes "[ルワンダ]";
		mes "……改めてご挨拶を。";
		mes "私はルワンダ。";
		mes "この洞窟に留まり、近くの村の";
		mes "警護をしている者です。";
		next;
		mes "[ルワンダ]";
		mes "村の依頼はそこに設置してある";
		mes "掲示板で管理しています。";
		next;
		mes "[ルワンダ]";
		mes "早速、依頼を……";
		mes "と言いたいところですが、";
		mes "今はモンスターの";
		mes "活動が大人しく、幸い";
		mes "手は足りているのです。";
		next;
		mes "[ルワンダ]";
		mes "なので、冒険者さまには";
		mes "警護の一環ということで";
		mes "洞窟の見回りを";
		mes "していただけないでしょうか？";
		next;
		emotion 29;
		mes "[ルワンダ]";
		mes "変化の無い";
		mes "退屈な洞窟ですが、";
		mes "幽霊でも見つけたら";
		mes "知らせてください。";
		set IL_LUANDA_QUE,2;
		viewpoint 1, 153, 33, 1, 0xFF0000;
		viewpoint 1, 118, 100, 2, 0xFF0000;
		viewpoint 1, 193, 267, 3, 0xFF0000;
		viewpoint 1, 228, 91, 4, 0xFF0000;
		viewpoint 1, 208, 130, 5, 0xFF0000;
		viewpoint 1, 42, 215, 6, 0xFF0000;
		viewpoint 1, 263, 72, 7, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 193, 265;
		end;
	case 3:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐目撃した現象について、";
		mes "　ルワンダに話した‐";
		next;
		emotion 20;
		mes "[ルワンダ]";
		mes "確かに奇怪な現象です。";
		next;
		mes "[ルワンダ]";
		mes "村で長く過ごしてきた私ですら";
		mes "初めて聞きます。";
		mes "誰かが目撃したのなら";
		mes "村で噂でも流れていそうなものです。";
		next;
		mes "[ルワンダ]";
		mes "これは私の推測に過ぎませんが、";
		mes "最近発生し始めたものなのでは";
		mes "ないでしょうか。";
		next;
		mes "[ルワンダ]";
		mes "危険な現象かもしれませんので";
		mes "これから見回りで発見しても";
		mes "冒険者さまは";
		mes "絶対に近づかないでくださいね。";
		set IL_LUANDA_QUE,4;
		viewpoint 1, 153, 33, 1, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 153, 35;
		end;
	case 6:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐ルワンダによく似た青年達に";
		mes "　出会った話をした‐";
		next;
		emotion 0;
		mes "[ルワンダ]";
		mes "……えっ！？";
		mes "私の兄弟に会ったのですか！？";
		next;
		mes "[ルワンダ]";
		mes "ですが、まるでその場に";
		mes "私までいたかのような話です。";
		mes "私はしばらくここに居ましたし、";
		mes "幻想の出来事を";
		mes "見てきたかのような話です……。";
		next;
		mes "[ルワンダ]";
		mes "幻想……？いや、";
		mes "月日が流れたとはいえ、";
		mes "旅の方に会うことは稀です。";
		mes "少しずつ";
		mes "思い出してきました。";
		next;
		mes "[ルワンダ]";
		mes "記憶力の良い弟のマオと違って";
		mes "私は記憶するのは苦手ですが、";
		mes "確かに以前、";
		mes "狩りに出かける前、";
		mes "出会った旅の方に";
		mes "忠告した記憶があります。";
		next;
		mes "[ルワンダ]";
		mes "初めて出会った時、";
		mes "冒険者さまに";
		mes "見覚えがあると言いましたが、";
		mes "あれはやはり";
		mes "気のせいではなかったのか……。";
		next;
		mes "[ルワンダ]";
		mes "しかし、不思議ですね。";
		mes "あの旅の方が";
		mes "冒険者さまだというのなら、";
		mes "過去の私と話をしてきた";
		mes "ということになります。";
		next;
		mes "[ルワンダ]";
		mes "これからも";
		mes "似たような現象が起こり得る、";
		mes "ということでしょうか？";
		next;
		emotion 17;
		mes "[ルワンダ]";
		mes "ごめんなさい。";
		mes "あの時は急いでいたので";
		mes "忠告するのが精一杯でした。";
		mes "突然言われて信じられなくても";
		mes "無理はありません。";
		next;
		mes "[ルワンダ]";
		mes "結局、モンスターは";
		mes "襲ってくるどころか";
		mes "妙が付くほど大人しいです。";
		mes "このまま何も起こらなければ";
		mes "良いのですが。";
		next;
		mes "‐ルワンダはそう言うが";
		mes "　不安そうな顔をしている。";
		mes "　見回りを続ければ";
		mes "　新たな現象に";
		mes "　遭遇するかもしれない‐";
		set IL_LUANDA_QUE,7;
		viewpoint 1, 118, 100, 1, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 118, 102;
		end;
	case 8:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐カルとアスデンの話をした‐";
		next;
		emotion 18;
		mes "[ルワンダ]";
		mes "あっはは！";
		mes "デート中の";
		mes "カル兄と義姉さんに";
		mes "出くわしたようですね。";
		next;
		emotion 18;
		mes "[ルワンダ]";
		mes "しかも、";
		mes "誰も知らないデートスポット";
		mes "だなんて！あはははは！";
		mes "腹が痛い……。";
		next;
		mes "[ルワンダ]";
		mes "カル兄は";
		mes "デートにうってつけの";
		mes "場所を見つけた！";
		mes "とか言って、自分しか知らない";
		mes "秘密の場所だと";
		mes "思っていたようですが……、";
		next;
		mes "[ルワンダ]";
		mes "小さな村です。";
		mes "恋人達の間では、";
		mes "有名な場所なんですよ。";
		mes "ふふ……";
		mes "ばつの悪そうなカル兄の姿が";
		mes "目に浮かぶようです。";
		next;
		mes "[ルワンダ]";
		mes "最近、心配事が多くて";
		mes "心から笑える機会が";
		mes "ありませんでしたが、";
		mes "お蔭様で大笑いできました。";
		next;
		mes "[ルワンダ]";
		mes "次の話も待ち遠しいですが……";
		mes "冒険者さま、モンスターは一向に";
		mes "現れないし、見回りはもう大丈夫です。";
		mes "そろそろこの地を離れ、";
		mes "旅路に戻られた方が良いでしょう。";
		mes "報酬を用意しておきますね。";
		next;
		mes "‐ルワンダはそう言うが";
		mes "　心配事というのが気にかかる。";
		mes "　見回りを続ければ";
		mes "　原因が分かるかもしれない‐";
		set IL_LUANDA_QUE,9;
		viewpoint 1, 193, 267, 1, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 193, 265;
		end;
	case 10:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐洞窟で壁画を描いていた";
		mes "　ルワンダについて話した‐";
		next;
		mes "[ルワンダ]";
		mes "私が壁画を描いている時、";
		mes "冒険者さまに出会ったことは";
		mes "無かったはずです。";
		mes "うーん……。";
		next;
		mes "[ルワンダ]";
		mes "最近描き始めたので";
		mes "会っていたら今度は";
		mes "確実に覚えているはずです。";
		mes "あぁ、なぜ壁画を描いているのかだったら";
		mes "お話出来ますよ。";
		next;
		mes "[ルワンダ]";
		mes "村では公然の秘密ですが、";
		mes "私たち兄弟の目には";
		mes "神秘の力が宿っています。";
		next;
		mes "[ルワンダ]";
		mes "カル兄は";
		mes "遥か遠くまで";
		mes "高速なものでも正確に見通せる";
		mes "動体視力。";
		next;
		mes "[ルワンダ]";
		mes "末っ子のマオは、";
		mes "一度見たものを忘れない";
		mes "瞬間記憶能力。それに、";
		mes "目を合わせた相手の思考が";
		mes "流れてくるように";
		mes "読み取れる読心術。";
		next;
		mes "[ルワンダ]";
		mes "そして私には予知能力があります。";
		mes "……と言っても、";
		mes "制御はできず、不完全です。";
		mes "獲物の動きが少し予測できたり、";
		mes "見た夢が現実になったり。";
		next;
		mes "[ルワンダ]";
		mes "あ！能力と言えばもう一つ、";
		mes "善悪の気を感じ取れるんです。";
		next;
		mes "[ルワンダ]";
		mes "冒険者さまからは";
		mes "善の気しか感じられなかったので";
		mes "初対面でも警戒を解いて";
		mes "話しかけることが出来ました。";
		mes "警護には向いている能力でしょ？";
		next;
		mes "[ルワンダ]";
		mes "……話を戻します。";
		mes "私が壁画を描く理由ですが、";
		mes "ある日、私は村が燃える悪夢を";
		mes "見ました。";
		next;
		mes "[ルワンダ]";
		mes "数多のモンスターが村を襲い、";
		mes "悲鳴を上げる村のみんなの姿……。";
		mes "そして、草の根残らず村は壊滅。";
		next;
		mes "[ルワンダ]";
		mes "地獄のような夢を見た後、";
		mes "その出来事を私が洞窟で壁画として";
		mes "記録している夢も見ました。";
		next;
		mes "[ルワンダ]";
		mes "何故そんな夢を見たのか？";
		mes "今だって信じられません。";
		mes "ですが、私の能力は……";
		mes "夢が現実になります。";
		next;
		mes "[ルワンダ]";
		mes "それなら、村が襲われる前に";
		mes "悪夢の内容を";
		mes "何か別の現実にすることで";
		mes "村が襲われる未来が";
		mes "来なくなるかもしれないと";
		mes "考えたんです。";
		next;
		mes "[ルワンダ]";
		mes "……バカな話ですよね？";
		mes "自分でも分かっています。";
		next;
		mes "[ルワンダ]";
		mes "あぁ、でも心配しないでください。";
		mes "今のところ悪夢で見た出来事は";
		mes "起きていません。";
		next;
		mes "[ルワンダ]";
		mes "それにしても、";
		mes "壁画は完成していたのですか？";
		mes "それだと、";
		mes "今度はまるで未来の出来事を";
		mes "見てきたかのようです。";
		next;
		mes "[ルワンダ]";
		mes "今まで冒険者さまが";
		mes "予知に出てきたことはありませんが、";
		mes "その冒険者さまが";
		mes "今、私を助けていることを考えれば、";
		mes "何が起こっても";
		mes "不思議ではないのかも……。";
		next;
		mes "‐ルワンダは考え込んでしまった。";
		mes "　見回りを続ければ";
		mes "　新たな現象に";
		mes "　遭遇するかもしれない‐";
		set IL_LUANDA_QUE,11;
		viewpoint 1, 228, 91, 1, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 228, 89;
		end;
	case 12:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐一人で修行をしていた";
		mes "　マオについて話した‐";
		next;
		mes "[ルワンダ]";
		mes "マオのやつ……。";
		mes "色々と気を使っていたようです。";
		next;
		mes "[ルワンダ]";
		mes "カル兄は義姉さんと";
		mes "暮らしているから、";
		mes "気付かないのも無理はありません。";
		mes "ですが、私は一緒に住んでいるのに";
		mes "マオの様子に";
		mes "全く気付きませんでした。";
		next;
		mes "[ルワンダ]";
		mes "悪夢を見た後の";
		mes "私の不安な感情も";
		mes "マオにすっかり";
		mes "見透かされていたようです。";
		next;
		mes "[ルワンダ]";
		mes "マオの方こそ、";
		mes "他人の感情に振り回されて";
		mes "苦労が絶えないはずなのに……。";
		next;
		mes "[ルワンダ]";
		mes "それに、マオは昔から努力家で、";
		mes "戦闘だって";
		mes "能力に頼らずとも十分強いのです。";
		mes "それなのに、";
		mes "更に強くなるために修行だなんて。";
		next;
		emotion 15;
		mes "[ルワンダ]";
		mes "マオは人知れず";
		mes "自分を変える努力を";
		mes "続けていたのですね。";
		mes "私も見習わなければ。";
		next;
		mes "‐見回りを続ければ";
		mes "　新たな現象に";
		mes "　遭遇するかもしれない‐";
		set IL_LUANDA_QUE,13;
		viewpoint 1, 208, 130, 1, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 206, 130;
		end;
	case 14:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐洞窟で何か準備をする";
		mes "　ルワンダについて話した‐";
		next;
		mes "[ルワンダ]";
		mes "村が襲撃された時を考え、";
		mes "村長に言って洞窟に退避出来る";
		mes "手はずを整えました。";
		next;
		mes "[ルワンダ]";
		mes "洞窟の数ヶ所に";
		mes "非常用品の準備を";
		mes "しているところに";
		mes "出会ったようですね。";
		next;
		mes "[ルワンダ]";
		mes "マオに見習って";
		mes "私にだって";
		mes "出来ることをしようと";
		mes "思いまして。";
		next;
		mes "[ルワンダ]";
		mes "もちろん、使われないのが";
		mes "一番良いのですが……。";
		mes "すみません。";
		mes "なんだかすっかり";
		mes "冒険者さまを巻き込んで";
		mes "しまっていますね。";
		next;
		mes "‐見回りを続ければ";
		mes "　新たな現象に";
		mes "　遭遇するかもしれない‐";
		set IL_LUANDA_QUE,15;
		viewpoint 1, 153, 33, 1, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 153, 35;
		end;
	case 16:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐村の住民と村長に会った話をした‐";
		next;
		mes "[ルワンダ]";
		mes "……。";
		mes "襲撃される村の様子を";
		mes "目撃したようですね。";
		mes "悪夢程ではないにせよ、";
		mes "相当な被害で……。";
		next;
		mes "[ルワンダ]";
		mes "悪夢を思い出すたび、";
		mes "胸が痛みます。";
		mes "よりによって";
		mes "私達、兄弟が離れている隙に……。";
		next;
		mes "[ルワンダ]";
		mes "考えてみると、悪夢よりは被害が";
		mes "少ないことも不思議です。";
		mes "村長が落ち着いて";
		mes "避難させていたためでしょうか。";
		mes "私の予知は不完全とはいえ……。";
		next;
		mes "‐見回りを続ければ";
		mes "　新たな現象に";
		mes "　遭遇するかもしれない‐";
		set IL_LUANDA_QUE,17;
		viewpoint 1, 42, 215, 1, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 42, 217;
		end;
	case 18:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐帰路を急ぐ3人の話をした‐";
		next;
		mes "[ルワンダ]";
		mes "きっと、村が襲撃された後、";
		mes "私達が狩りから帰る様子を";
		mes "目撃したということ";
		mes "でしょうね……。";
		next;
		mes "[ルワンダ]";
		mes "急いで帰った所で";
		mes "村は襲撃された後。";
		mes "義姉さんだってモンスターに";
		mes "連れ去られて";
		mes "いることでしょう……。";
		next;
		mes "[ルワンダ]";
		mes "……私達が村を離れてさえ";
		mes "いなかったら、";
		mes "連れて行かれはしなかった";
		mes "はずなのに！！一体何故！？";
		next;
		menu "気をしっかり",-;
		mes "[ルワンダ]";
		mes "解ってます。";
		mes "解ってますとも……。";
		next;
		mes "[ルワンダ]";
		mes "でも、なぜ？";
		mes "私達兄弟が";
		mes "離れている時を";
		mes "狙われさえしなければ";
		mes "きっと撃退できるはずなのに……。";
		next;
		mes "[ルワンダ]";
		mes "運命からは逃れられない。";
		mes "ということでしょうか？";
		next;
		menu "まず、落ち着いた方がよさそうです",-;
		mes "[ルワンダ]";
		mes "……冒険者さまの前で";
		mes "取り乱してしまいました。";
		mes "ただ、経験した話を";
		mes "伝えてくださった";
		mes "だけなのに……。";
		next;
		mes "‐見回りを続ければ";
		mes "　新たな現象に";
		mes "　遭遇するかもしれない‐";
		set IL_LUANDA_QUE,19;
		viewpoint 1, 118, 100, 1, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 118, 102;
		end;
	case 20:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐カルとアスデンの話をした‐";
		next;
		mes "[ルワンダ]";
		mes "カ……";
		next;
		mes "[ルワンダ]";
		mes "カル兄……。";
		mes "カル兄の心の中は";
		mes "義姉さんが全てです。";
		next;
		mes "[ルワンダ]";
		mes "だから、義姉さんが";
		mes "呪いを受けた時の";
		mes "カル兄の悲しみは、";
		mes "私では想像できそうにも";
		mes "ありません……。";
		next;
		mes "[ルワンダ]";
		mes "私ですらこんなに悲しいのに、";
		mes "能力を持つマオが知ったら";
		mes "どうにかなってしまうでしょう。";
		next;
		mes "[ルワンダ]";
		mes "予知だけ出来ても、";
		mes "結局、村を護れないのでは……。";
		mes "自分が悔しくて";
		mes "仕方ありません……。";
		next;
		mes "‐見回りを続ければ";
		mes "　新たな現象に";
		mes "　遭遇するかもしれない‐";
		set IL_LUANDA_QUE,21;
		viewpoint 1, 263, 72, 1, 0xFF0000;
		next;
		mes "‐急いで見回りに行きますか？‐";
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", 261, 72;
		end;
	case 22:
		mes "[ルワンダ]";
		mes "冒険者さま、";
		mes "どうなさいましたか？";
		next;
		mes "‐何者かの不穏な会話を伝えた‐";
		next;
		mes "[ルワンダ]";
		mes "状況からして";
		mes "村を狙うウータン族や";
		mes "巨石族の会話に";
		mes "遭遇したようですね。";
		next;
		mes "[ルワンダ]";
		mes "それに、英雄を得たと？";
		mes "最近、奴らが妙に";
		mes "大人しかった理由は";
		mes "そこにあるのかもしれません。";
		next;
		mes "[ルワンダ]";
		mes "つまり、奴らの中に";
		mes "統率力のある英雄が現れたと。";
		mes "そして、力を蓄え";
		mes "攻め入る隙を伺っていた……？";
		next;
		mes "[ルワンダ]";
		mes "もし、そうなら、";
		mes "私達が狩りに出た隙に";
		mes "村を狙うことだって";
		mes "可能でしょうね。";
		next;
		mes "[ルワンダ]";
		mes "でも、困りました。";
		mes "私達が狩りに行かなければ";
		mes "村の暮らしが成り立ちません。";
		mes "しかし、今も戦闘となれば";
		mes "防ぐのがやっとの状態。";
		mes "統制をとって襲われたらやはり……。";
		next;
		mes "[ルワンダ]";
		mes "……悲観している場合では";
		mes "ありませんね。";
		mes "防御施設を増やし、";
		mes "徹底的に対策しなくては。";
		next;
		mes "[ルワンダ]";
		mes "それに、強大な力、";
		mes "というのも初耳です。";
		next;
		mes "[ルワンダ]";
		mes "モンスターが";
		mes "村を襲撃する目的でしょうか？";
		mes "ともかく、村長に伝えて";
		mes "調査しましょう。";
		next;
		mes "[ルワンダ]";
		mes "今まで";
		mes "ありがとうございました。";
		mes "冒険者さま。";
		mes "報酬をお渡ししなければ。";
		next;
		mes "[ルワンダ]";
		mes "これまで伝えてくださった話は";
		mes "ただの幻想に";
		mes "過ぎないのかもしれません。";
		mes "未来は決定している";
		mes "のかもしれません。";
		next;
		mes "[ルワンダ]";
		mes "ですが、あきらめて";
		mes "ただ何もしないより、";
		mes "その時出来る限りのことを";
		mes "した方が、";
		mes "未来は少しだけ良い方に";
		mes "変わるかもしれません。";
		next;
		mes "[ルワンダ]";
		mes "……変わらない、";
		mes "のかもしれません。";
		mes "……だとしても……";
		next;
		emotion 15;
		mes "[ルワンダ]";
		mes "絶望的な未来が待っていても、";
		mes "わずかでも可能性が";
		mes "残っているのなら、";
		mes "私はそれを信じて";
		mes "全身全霊で村を守護することに";
		mes "決めました。";
		next;
		if(checkitemblank() == 0) {
			mes "^ff0000【インフォメーション】";
			mes "これ以上多くの種類の";
			mes "荷物を持つことが出来ません。";
			mes "1個以上の空きを作ってください。^000000";
			close;
		}
		set IL_LUANDA_QUE,23;
		setquest 202115;
		delquest 5847;
		getitem 25271,10;
		getexp 300000000,0,1;
		getexp 0,60000000,0;
		mes "[ルワンダ]";
		mes "冒険者さまは";
		mes "私にゆるぎない";
		mes "希望を与えてくれました。";
		mes "この希望は";
		mes "決して幻想ではありません。";
		next;
		mes "‐ルワンダの話が終わると";
		mes "　辺りが青い光に包まれた‐";
		close2;
		warp "beach_dun2.gat", 249, 243;
		end;
	case 23:
		warp "beach_dun2.gat", 249, 243;
		end;
	}
	mes "[ルワンダ]";
	mes "冒険者さま、";
	mes "どうなさいましたか？";
	next;
	switch(select("周辺を見回る","掲示板とは？","この洞窟は一体なんですか？","モンスターが侵略する理由とは？","この場を去る")) {
	case 1:
		mes "‐急いで見回りに行きますか？‐";
		switch(IL_LUANDA_QUE) {
		case 2:
			viewpoint 1, 153, 33, 1, 0xFF0000;
			viewpoint 1, 118, 100, 2, 0xFF0000;
			viewpoint 1, 193, 267, 3, 0xFF0000;
			viewpoint 1, 228, 91, 4, 0xFF0000;
			viewpoint 1, 208, 130, 5, 0xFF0000;
			viewpoint 1, 42, 215, 6, 0xFF0000;
			viewpoint 1, 263, 72, 7, 0xFF0000;
			set '@x,193; set '@y,265;
			break;
		case 4: case 5: case 15:
			viewpoint 1, 153, 33, 1, 0xFF0000;
			set '@x,153; set '@y,35;
			break;
		case 7: case 19:
			viewpoint 1, 118, 100, 1, 0xFF0000;
			set '@x,118; set '@y,102;
			break;
		case 9:
			viewpoint 1, 193, 267, 1, 0xFF0000;
			set '@x,193; set '@y,265;
			break;
		case 11:
			viewpoint 1, 228, 91, 1, 0xFF0000;
			set '@x,228; set '@y,89;
			break;
		case 13:
			viewpoint 1, 208, 130, 1, 0xFF0000;
			set '@x,206; set '@y,130;
			break;
		case 17:
			viewpoint 1, 42, 215, 1, 0xFF0000;
			set '@x,42; set '@y,217;
			break;
		case 21:
			viewpoint 1, 263, 72, 1, 0xFF0000;
			set '@x,261; set '@y,72;
			break;
		}
		next;
		if(select("急いで見回る(ショートカット)","歩いて見回る") == 2) {
			mes "‐歩いて見回ることにした‐";
			close;
		}
		warp "com_d02_i_q.gat", '@x, '@y;
		end;
	case 2:
		mes "[ルワンダ]";
		mes "村で募集中の依頼は";
		mes "掲示板で";
		mes "お願いすることになります。";
		next;
		mes "[ルワンダ]";
		mes "今はモンスターが大人しいので";
		mes "依頼はありません。";
		mes "ですが、いつ暴れるか";
		mes "分からないので";
		mes "見回りをお願いします。";
		next;
		mes "[ルワンダ]";
		mes "あ！忘れていました。";
		mes "ここは戦場の真ん中になるので、";
		mes "安全の問題で掲示板は";
		mes "隅っこに設置されてます。";
		close;
	case 3:
		mes "[ルワンダ]";
		mes "このルワンダ洞窟は";
		mes "戦略的にみると、";
		mes "村の北側に通じる唯一の道です。";
		next;
		mes "[ルワンダ]";
		mes "だからこそ、";
		mes "私達はここで";
		mes "モンスターの侵略を";
		mes "防いでいるのです。";
		next;
		menu "ルワンダ洞窟？ルワンダ？",-;
		mes "[ルワンダ]";
		mes "あ、気付きましたね？";
		mes "そうです。";
		mes "私の名前もルワンダです。";
		next;
		mes "[ルワンダ]";
		mes "村のじいさま達の話によると……";
		mes "兄弟の名前も";
		mes "村の洞窟の名にちなんで、";
		mes "カル、マオと名付けたそうです。";
		next;
		mes "[ルワンダ]";
		mes "幼い頃、村の幼馴染に";
		mes "時々からかわれましたが、";
		mes "名前に不満はありませんでした。";
		next;
		mes "[ルワンダ]";
		mes "村に伝わる守護神達の名が";
		mes "由来と聞きますから、";
		mes "むしろ誇らしいです。";
		close;
	case 4:
		mes "[ルワンダ]";
		mes "私たちもそこが";
		mes "よく分かりません。";
		mes "理由が分かれば対処のしようも";
		mes "あると思うのですが。";
		next;
		mes "[ルワンダ]";
		mes "ここは食糧が豊富な村でもないし、";
		mes "モンスターが狙う理由など";
		mes "ないはずなのです。";
		next;
		mes "[ルワンダ]";
		mes "状況が変わらないとしても";
		mes "私達はここに";
		mes "住み続けるつもりです。";
		close;
	case 5:
		mes "[ルワンダ]";
		mes "ではご苦労さまです。";
		mes "冒険者さま。";
		close;
	}
OnTouch:
	if(IL_LUANDA_QUE == 1) {
		unittalk "ルワンダ : 私はルワンダ。そこに居るのはどなたですか？";
		mes "[ルワンダ]";
		mes "私はルワンダ。";
		mes "そこに居るのはどなたですか？";
		next;
		mes "‐ルワンダと名乗る男に";
		mes "　声をかけられた。";
		mes "　会話してみよう‐";
		close;
	}
	end;
}

com_d02_i_q.gat,249,250,4	script	掲示板	857,{
	mes "‐近くの村が立てた掲示板のようだ‐";
	close;
}

com_d02_i_q.gat,153,33,1	script	ゆらぎ#ILU_1	723,1,1,{
	misceffect 589;
	set '@id,substr(strnpcinfo(2),4);
	switch(IL_LUANDA_QUE) {
	case 2:
		mes "‐吸い込まれそうな、";
		mes "　奇怪な現象だ‐";
		next;
		mes "‐見過ごせない現象と思われる。";
		mes "　ルワンダに伝えよう‐";
		set IL_LUANDA_QUE,3;
		viewpoint 2, 153, 33, 1, 0xFF0000;
		viewpoint 2, 118, 100, 2, 0xFF0000;
		viewpoint 2, 193, 267, 3, 0xFF0000;
		viewpoint 2, 228, 91, 4, 0xFF0000;
		viewpoint 2, 208, 130, 5, 0xFF0000;
		viewpoint 2, 42, 215, 6, 0xFF0000;
		viewpoint 2, 263, 72, 7, 0xFF0000;
		next;
		mes "‐ルワンダのところへ戻りますか？‐";
		next;
		if(select("戻る","まだここに居る") == 2) {
			mes "‐あなたはその場に留まった‐";
			close;
		}
		warp "com_d02_i_q.gat", 241, 248;
		end;
	case 4:
		if('@id == 1) {
			cloakoffnpc "余裕な顔つきの青年#ILU_015";
			cloakoffnpc "ルワンダと呼ばれた青年#ILU_016";
			cloakoffnpc "澄んだ目の青年#ILU_017";
			unittalk getnpcid(0,"余裕な顔つきの青年#ILU_015"),"余裕な顔つきの青年 : 狩りは退屈だな。ルワンダ。";
			unittalk getnpcid(0,"澄んだ目の青年#ILU_017"),"澄んだ目の青年 : 準備できたよ。ルワンダ兄。";
			end;
		}
		break;
	case 5:
		if('@id == 1) {
			cloakoffnpc "ルワンダと呼ばれた青年#ILU_016";
			end;
		}
		break;
	case 7:
		if('@id == 2) {
			cloakoffnpc "カル#ILU_018";
			cloakoffnpc "アスデン#ILU_019";
			end;
		}
		break;
	case 9:
		if('@id == 3) {
			cloakoffnpc "壁画を描くルワンダ#ILU_020";
			end;
		}
		break;
	case 11:
		if('@id == 4) {
			cloakoffnpc "マオ#ILU_021";
			end;
		}
		break;
	case 13:
		if('@id == 5) {
			cloakoffnpc "準備をするルワンダ#ILU_022";
			end;
		}
		break;
	case 15:
		if('@id == 1) {
			cloakoffnpc "村長#ILU_023";
			cloakoffnpc "村人#ILU_024";
			cloakoffnpc "村人#ILU_025";
			cloakoffnpc "村人#ILU_026";
			unittalk getnpcid(0,"村長#ILU_023"),"村長 : 皆、落ち着け！";
			unittalk getnpcid(0,"村人#ILU_024"),"村人 : どうすれば……。";
			unittalk getnpcid(0,"村人#ILU_025"),"村人 : 三つ子はまだか！";
			unittalk getnpcid(0,"村人#ILU_026"),"村人 : 早く逃げないと！";
			end;
		}
		break;
	case 17:
		if('@id == 6) {
			cloakoffnpc "カル#ILU_027";
			cloakoffnpc "呆然とするルワンダ#ILU_";
			cloakoffnpc "マオ#ILU_029";
			unittalk getnpcid(0,"カル#ILU_027"),"カル : ようやく帰れそうだな。マオ。";
			end;
		}
		break;
	case 19:
		if('@id == 2) {
			cloakoffnpc "カル#ILU_030";
			cloakoffnpc "アスデン#ILU_031";
			cloakonnpc "アスデン#ILU_032";
			end;
		}
		break;
	case 21:
		if('@id == 7) {
			cloakoffnpc "シルエット#ILU_033";
			cloakoffnpc "シルエット#ILU_034";
			end;
		}
		break;
	default:
		mes "‐ルワンダのところへ戻りますか？‐";
		next;
		if(select("戻る","まだここに居る") == 2) {
			mes "‐あなたはその場に留まった‐";
			close;
		}
		warp "com_d02_i_q.gat", 241, 248;
		end;
	}
	mes "‐特に何も起こらない。";
	mes "　他の場所を探しに行きますか？‐";
	next;
	if(select("はい","いいえ") == 2) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	switch(IL_LUANDA_QUE) {
	case 4: case 5: case 15:
		set '@x,153; set '@y,35;
		break;
	case 7: case 19:
		set '@x,118; set '@y,102;
		break;
	case 9:
		set '@x,193; set '@y,265;
		break;
	case 11:
		set '@x,228; set '@y,89;
		break;
	case 13:
		set '@x,206; set '@y,130;
		break;
	case 17:
		set '@x,42; set '@y,217;
		break;
	case 21:
		set '@x,261; set '@y,72;
		break;
	}
	warp "com_d02_i_q.gat", '@x, '@y;
	end;
OnTouch:
	misceffect 589;
	set '@id,substr(strnpcinfo(2),4);
	switch(IL_LUANDA_QUE) {
	case 4:
		if('@id == 1) {
			cloakoffnpc "余裕な顔つきの青年#ILU_015";
			cloakoffnpc "ルワンダと呼ばれた青年#ILU_016";
			cloakoffnpc "澄んだ目の青年#ILU_017";
			unittalk getnpcid(0,"余裕な顔つきの青年#ILU_015"),"余裕な顔つきの青年 : 狩りは退屈だな。ルワンダ。";
			unittalk getnpcid(0,"澄んだ目の青年#ILU_017"),"澄んだ目の青年 : 準備できたよ。ルワンダ兄。";
		}
		break;
	case 5:
		if('@id == 1) {
			cloakoffnpc "ルワンダと呼ばれた青年#ILU_016";
		}
		break;
	case 7:
		if('@id == 2) {
			cloakoffnpc "カル#ILU_018";
			cloakoffnpc "アスデン#ILU_019";
		}
		break;
	case 9:
		if('@id == 3) {
			cloakoffnpc "壁画を描くルワンダ#ILU_020";
		}
		break;
	case 11:
		if('@id == 4) {
			cloakoffnpc "マオ#ILU_021";
		}
		break;
	case 13:
		if('@id == 5) {
			cloakoffnpc "準備をするルワンダ#ILU_022";
		}
		break;
	case 15:
		if('@id == 1) {
			cloakoffnpc "村長#ILU_023";
			cloakoffnpc "村人#ILU_024";
			cloakoffnpc "村人#ILU_025";
			cloakoffnpc "村人#ILU_026";
			unittalk getnpcid(0,"村長#ILU_023"),"村長 : 皆、落ち着け！";
			unittalk getnpcid(0,"村人#ILU_024"),"村人 : どうすれば……。";
			unittalk getnpcid(0,"村人#ILU_025"),"村人 : 三つ子はまだか！";
			unittalk getnpcid(0,"村人#ILU_026"),"村人 : 早く逃げないと！";
		}
		break;
	case 17:
		if('@id == 6) {
			cloakoffnpc "カル#ILU_027";
			cloakoffnpc "呆然とするルワンダ#ILU_";
			cloakoffnpc "マオ#ILU_029";
			unittalk getnpcid(0,"カル#ILU_027"),"カル : ようやく帰れそうだな。マオ。";
		}
		break;
	case 19:
		if('@id == 2) {
			cloakoffnpc "カル#ILU_030";
			cloakoffnpc "アスデン#ILU_031";
			cloakonnpc "アスデン#ILU_032";
		}
		break;
	case 21:
		if('@id == 7) {
			cloakoffnpc "シルエット#ILU_033";
			cloakoffnpc "シルエット#ILU_034";
		}
		break;
	}
	end;
}
com_d02_i_q.gat,118,100,1	duplicate(ゆらぎ#ILU_1)	ゆらぎ#ILU_2	723,1,1
com_d02_i_q.gat,193,267,1	duplicate(ゆらぎ#ILU_1)	ゆらぎ#ILU_3	723,1,1
com_d02_i_q.gat,228,91,1	duplicate(ゆらぎ#ILU_1)	ゆらぎ#ILU_4	723,1,1
com_d02_i_q.gat,208,130,1	duplicate(ゆらぎ#ILU_1)	ゆらぎ#ILU_5	723,1,1
com_d02_i_q.gat,42,215,1	duplicate(ゆらぎ#ILU_1)	ゆらぎ#ILU_6	723,1,1
com_d02_i_q.gat,263,72,1	duplicate(ゆらぎ#ILU_1)	ゆらぎ#ILU_7	723,1,1

com_d02_i_q.gat,154,41,4	script(CLOAKED)	余裕な顔つきの青年#ILU_015	843,{
	unittalk "余裕な顔つきの青年 : 狩りは退屈だな。ルワンダ。";
	end;
}

com_d02_i_q.gat,152,40,6	script(CLOAKED)	ルワンダと呼ばれた青年#ILU_016	843,{
	switch(IL_LUANDA_QUE) {
	case 4:
		cloakoffnpc "余裕な顔つきの青年#ILU_015";
		cloakoffnpc "澄んだ目の青年#ILU_017";
		unittalk "ルワンダと呼ばれた青年 : カル兄、準備は済みましたか？そろそろ出発しましょう。大分時間が経ちました。";
		mes "[ルワンダと呼ばれた青年]";
		mes "カル兄、準備は済みましたか？";
		mes "そろそろ出発しましょう。";
		mes "大分時間が経ちました。";
		next;
		unittalk getnpcid(0,"余裕な顔つきの青年#ILU_015"),"カル : そうだな。ルワンダの言う通り、すぐに出発しようか。妙な気配も感じる……。どう思う？　マオ。";
		mes "[カル]";
		mes "そうだな。ルワンダの言う通り、";
		mes "すぐに出発しようか。";
		mes "妙な気配も感じる……。";
		mes "どう思う？マオ。";
		next;
		unittalk getnpcid(0,"澄んだ目の青年#ILU_017"),"マオ : はっ！　アニキ達も大げさな。たったの一日、大変なことが起きる訳ない。……ん？";
		mes "[マオ]";
		mes "はっ！アニキ達も大げさな。";
		mes "たったの一日、";
		mes "大変なことが起きる訳ない。";
		mes "……ん？";
		next;
		unittalk getnpcid(0,"澄んだ目の青年#ILU_017"),"マオ : アニキ達、あそこに誰かいる。異邦人？";
		mes "[マオ]";
		mes "アニキ達、";
		mes "あそこに誰かいる。";
		mes "異邦人？";
		next;
		unittalk getnpcid(0,"澄んだ目の青年#ILU_017"),"マオ : ……異邦人みたいだ。オレの記憶が正しければ、この辺じゃ見かけない顔だな。";
		mes "[マオ]";
		mes "……異邦人みたいだ。";
		mes "オレの記憶が正しければ、";
		mes "この辺じゃ見かけない顔だな。";
		next;
		unittalk getnpcid(0,"余裕な顔つきの青年#ILU_015"),"カル : マオの記憶力なら間違いない。異邦人なんて珍しいな。";
		mes "[カル]";
		mes "マオの記憶力なら";
		mes "間違いない。";
		mes "異邦人なんて珍しいな。";
		next;
		unittalk "ルワンダと呼ばれた青年 : カル兄、あの様子なら危険な奴ではありません。ですが、もたもたしてもいられませんし、気にせず出発しましょう。";
		mes "[ルワンダと呼ばれた青年]";
		mes "カル兄、あの様子なら";
		mes "危険な奴ではありません。";
		mes "ですが、";
		mes "もたもたしてもいられませんし、";
		mes "気にせず出発しましょう。";
		next;
		unittalk getnpcid(0,"澄んだ目の青年#ILU_017"),"マオ : オレもすぐ行くよ。";
		mes "[マオ]";
		mes "オレもすぐ行くよ。";
		next;
		unittalk getnpcid(0,"余裕な顔つきの青年#ILU_015"),"カル : ふむ……。だが、ルワンダ。お前の顔、あの異邦人に何か言いたげだな？　マオ、ボク達だけ先に出発しようか。";
		mes "[カル]";
		mes "ふむ……。";
		mes "だが、ルワンダ。";
		mes "お前の顔、あの異邦人に";
		mes "何か言いたげだな？";
		mes "マオ、ボク達だけ先に出発しようか。";
		next;
		unittalk getnpcid(0,"余裕な顔つきの青年#ILU_015"),"カル : ルワンダ！　終わったら来い。あまり遅れないようになー。";
		mes "[カル]";
		mes "ルワンダ！終わったら来い。";
		mes "あまり遅れないようになー。";
		next;
		unittalk "ルワンダと呼ばれた青年 : はい、カル兄。";
		mes "[ルワンダと呼ばれた青年]";
		mes "はい、カル兄。";
		if(!sleep2(2000)) end;
		set IL_LUANDA_QUE,5;
		cloakonnpc "余裕な顔つきの青年#ILU_015";
		cloakoffnpc;
		cloakonnpc "澄んだ目の青年#ILU_017";
		next;
		unittalk "ルワンダと呼ばれた青年 : ……旅の方。ちょっと話があります。";
		mes "[ルワンダと呼ばれた青年]";
		mes "……旅の方。";
		mes "ちょっと話があります。";
		close;
	case 5:
		unittalk "ルワンダと呼ばれた青年 : ……あなたからは善の気しか感じられない。いったい何者です？";
		mes "[ルワンダと呼ばれた青年]";
		mes "……あなたからは";
		mes "善の気しか感じられない。";
		mes "いったい何者です？";
		next;
		menu "ルワンダ？",-;
		unittalk "ルワンダと呼ばれた青年 : 簡潔に話します。私には特別な力があるんです。でも……いつも都合よく感じ取れるわけではありません。";
		mes "[ルワンダと呼ばれた青年]";
		mes "簡潔に話します。";
		mes "私には特別な力があるんです。";
		mes "でも……いつも都合よく";
		mes "感じ取れるわけではありません。";
		next;
		unittalk "ルワンダと呼ばれた青年 : 悪い人ではないようだから忠告します。今すぐこの地から離れて。";
		mes "[ルワンダと呼ばれた青年]";
		mes "悪い人ではないようだから";
		mes "忠告します。";
		mes "今すぐこの地から離れて。";
		next;
		unittalk "ルワンダと呼ばれた青年 : こんな話、信じないだろうし、信じたくもないから今まで誰にも話したことはなかったけど……。";
		mes "[ルワンダと呼ばれた青年]";
		mes "こんな話、";
		mes "信じないだろうし、";
		mes "信じたくもないから";
		mes "今まで誰にも話したことは";
		mes "なかったけど……。";
		next;
		unittalk "ルワンダと呼ばれた青年 : いずれこの村は数多のモンスターに襲撃されます。無駄死にしたくないならこの地から早く離れてください。";
		mes "[ルワンダと呼ばれた青年]";
		mes "いずれこの村は";
		mes "数多のモンスターに";
		mes "襲撃されます。";
		mes "無駄死にしたくないなら";
		mes "この地から早く離れてください。";
		if(!sleep2(2000)) end;
		set IL_LUANDA_QUE,6;
		cloakonnpc "余裕な顔つきの青年#ILU_015";
		cloakonnpc;
		cloakonnpc "澄んだ目の青年#ILU_017";
		next;
		mes "‐そう言うと、青年は2人を追って消えた。";
		mes "　ルワンダとそっくりだが、";
		mes "　初対面のような口調だった。";
		mes "　ルワンダが居るはずの場所に戻り、";
		mes "　今経験したことを、";
		mes "　ルワンダに伝えよう‐";
		next;
		mes "‐ルワンダのところへ戻りますか？‐";
		next;
		if(select("戻る","まだここに居る") == 2) {
			mes "‐あなたはその場に留まった‐";
			close;
		}
		warp "com_d02_i_q.gat", 241, 248;
		end;
	}
	end;
}

com_d02_i_q.gat,156,39,4	script(CLOAKED)	澄んだ目の青年#ILU_017	843,{
	unittalk "澄んだ目の青年 : 準備できたよ。ルワンダ兄。";
	end;
}

com_d02_i_q.gat,121,95,4	script(CLOAKED)	カル#ILU_018	843,{
	unittalk getnpcid(0,"アスデン#ILU_019"),"アスデン : カル……今日の狩りはいかがでした？";
	mes "[アスデン]";
	mes "カル……";
	mes "今日の狩りはいかがでした？";
	next;
	unittalk "カル : ハハッ、アスデン。ボクの腕を信じられないのかい？　今日もいつも通り、ボクの戦果が一番だったさ！";
	mes "[カル]";
	mes "ハハッ、アスデン。";
	mes "ボクの腕を信じられないのかい？";
	mes "今日もいつも通り、";
	mes "ボクの戦果が一番だったさ！";
	next;
	unittalk getnpcid(0,"アスデン#ILU_019"),"アスデン : もぅ！　……嘘つき。マオちゃんからさっき全部聞いています。";
	mes "[アスデン]";
	mes "もぅ！……嘘つき。";
	mes "マオちゃんから";
	mes "さっき全部聞いています。";
	next;
	unittalk getnpcid(0,"アスデン#ILU_019"),"アスデン : 今日もルワンダ君とマオちゃんだけが、汗水流して狩りをしたんですって？　あなたは木の上に寝そべって声だけで仕事をして。";
	mes "[アスデン]";
	mes "今日もルワンダ君と";
	mes "マオちゃんだけが、";
	mes "汗水流して";
	mes "狩りをしたんですって？";
	mes "あなたは木の上に寝そべって";
	mes "声だけで仕事をして。";
	next;
	unittalk "カル : あらら……あいつら余計なこと言いやがったか……。";
	mes "[カル]";
	mes "あらら……";
	mes "あいつら余計なこと";
	mes "言いやがったか……。";
	next;
	unittalk getnpcid(0,"アスデン#ILU_019"),"アスデン : 本当……呆れた！　兄弟で1番の腕前なのに、1番やる気がないのよね。";
	mes "[アスデン]";
	mes "本当……呆れた！";
	mes "兄弟で1番の腕前なのに、";
	mes "1番やる気がないのよね。";
	next;
	unittalk "カル : なぁに、ボクの目は本当に必要な時にさえ役に立てばいい。後は弟達に任せて、サボっていて良いのさ。";
	mes "[カル]";
	mes "なぁに、ボクの目は";
	mes "本当に必要な時にさえ";
	mes "役に立てばいい。";
	mes "後は弟達に任せて、";
	mes "サボっていて良いのさ。";
	next;
	unittalk getnpcid(0,"アスデン#ILU_019"),"アスデン : またそんなこと言って……。あら？　あそこに誰か……。旅の方かしら？";
	mes "[アスデン]";
	mes "またそんなこと言って……。";
	mes "あら？あそこに誰か……。";
	mes "旅の方かしら？";
	next;
	unittalk "カル : なんだって！？　こんな、隠れたデートスポットに誰か来るなんて……。あぁ……本当にツいていない。絶好のデート日和だったのに。くぅー。";
	mes "[カル]";
	mes "なんだって！？こんな、";
	mes "隠れたデートスポットに";
	mes "誰か来るなんて……。";
	mes "あぁ……本当にツいていない。";
	mes "絶好のデート日和だったのに。";
	mes "くぅー。";
	next;
	unittalk getnpcid(0,"アスデン#ILU_019"),"アスデン : くすくす。わたしは別にどこで話をしたってかまわないよ？";
	mes "[アスデン]";
	mes "くすくす。わたしは別に";
	mes "どこで話をしたって";
	mes "かまわないよ？";
	next;
	unittalk "カル : いや、これじゃあムードも何もない。……だが、まだだ！　アスデン。次のデートスポットへエスコートしよう。そこの人、ボク達の分までゆっくりしていけよなー！";
	mes "[カル]";
	mes "いや、これじゃあムードも何もない。";
	mes "……だが、まだだ！アスデン。";
	mes "次のデートスポットへ";
	mes "エスコートしよう。";
	mes "そこの人、ボク達の分まで";
	mes "ゆっくりしていけよなー！";
	if(!sleep2(2000)) end;
	set IL_LUANDA_QUE,8;
	cloakonnpc;
	cloakonnpc "アスデン#ILU_019";
	next;
	mes "‐デートの邪魔をしたようで";
	mes "　申し訳なくなった。";
	mes "　経験した話を";
	mes "　ルワンダに伝えよう‐";
	next;
	mes "‐ルワンダのところへ戻りますか？‐";
	next;
	if(select("戻る","まだここに居る") == 2) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	warp "com_d02_i_q.gat", 241, 248;
	end;
}

com_d02_i_q.gat,120,95,6	script(CLOAKED)	アスデン#ILU_019	90,{
	unittalk "アスデン : 素敵なところよね……。";
	end;
}

com_d02_i_q.gat,191,271,8	script(CLOAKED)	壁画を描くルワンダ#ILU_020	843,{
	unittalk "壁画を描くルワンダ : うん……酷い出来だけど……私の腕にしては立派な壁画だよな。";
	mes "[壁画を描くルワンダ]";
	mes "うん……酷い出来だけど……";
	mes "私の腕にしては";
	mes "立派な壁画だよな。";
	next;
	unittalk "壁画を描くルワンダ : 悪夢で見た通りに出来たけど、どうせ未来は変わらない。";
	mes "[壁画を描くルワンダ]";
	mes "悪夢で見た通りに出来たけど、";
	mes "どうせ未来は変わらない。";
	next;
	unittalk "壁画を描くルワンダ : 悪夢は壁画の中の光景。ただの空夢。……そうであって欲しいけど、結局村は……。";
	mes "[壁画を描くルワンダ]";
	mes "悪夢は壁画の中の光景。";
	mes "ただの空夢。";
	mes "……そうであって欲しいけど、";
	mes "結局村は……。";
	next;
	unittalk "壁画を描くルワンダ : 未来は変わらない。分かっているはずなのになぜ、私はこんなことをしているんだろう……。";
	mes "[壁画を描くルワンダ]";
	mes "未来は変わらない。";
	mes "分かっているはずなのになぜ、";
	mes "私はこんなことを";
	mes "しているんだろう……。";
	next;
	unittalk "壁画を描くルワンダ : あれ？　あなたは……";
	mes "[壁画を描くルワンダ]";
	mes "あれ？";
	mes "あなたは……";
	next;
	menu "名乗る",-;
	unittalk "壁画を描くルワンダ : あ！　あなたは！　冒険者さま！！　なぜ、まだこの地にいらっしゃるのですか！？　もう旅路に戻ったと……";
	mes "[壁画を描くルワンダ]";
	mes "あ！あなたは！";
	mes "冒険者さま！！";
	mes "なぜ、まだこの地に";
	mes "いらっしゃるのですか！？";
	mes "もう旅路に戻ったと……";
	if(!sleep2(2000)) end;
	set IL_LUANDA_QUE,10;
	cloakonnpc;
	next;
	mes "‐壁画を描くルワンダは";
	mes "　会話の途中で消え去った。";
	mes "　経験した話を";
	mes "　ルワンダに伝えよう‐";
	next;
	mes "‐ルワンダのところへ戻りますか？‐";
	next;
	if(select("戻る","まだここに居る") == 2) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	warp "com_d02_i_q.gat", 241, 248;
	end;
}

com_d02_i_q.gat,228,95,4	script(CLOAKED)	マオ#ILU_021	843,{
	unittalk "マオ : チクショウ！　何でオレはこんなに弱いんだ！　アニキ達と違って戦闘で役立たずの能力なんて……。";
	mes "[マオ]";
	mes "チクショウ！";
	mes "何でオレはこんなに弱いんだ！";
	mes "アニキ達と違って";
	mes "戦闘で役立たずの";
	mes "能力なんて……。";
	next;
	unittalk "マオ : ん？　オ、オマエは！　狩りに向かう時、ルワンダ兄から忠告を受けた異邦人！";
	mes "[マオ]";
	mes "ん？オ、オマエは！";
	mes "狩りに向かう時、";
	mes "ルワンダ兄から";
	mes "忠告を受けた";
	mes "異邦人！";
	next;
	unittalk "マオ : そういえばあの時だったな。ルワンダ兄が悪夢を見たって知ったのは。ふーん……、そうか。オマエ、随分お節介みたいだな？";
	mes "[マオ]";
	mes "そういえばあの時だったな。";
	mes "ルワンダ兄が";
	mes "悪夢を見たって知ったのは。";
	mes "ふーん……、そうか。";
	mes "オマエ、";
	mes "随分お節介みたいだな？";
	next;
	unittalk "マオ : まあ、これも何かの縁だ。自己紹介しよう。オレはマオ。ルワンダ兄の弟。";
	mes "[マオ]";
	mes "まあ、これも何かの縁だ。";
	mes "自己紹介しよう。";
	mes "オレはマオ。";
	mes "ルワンダ兄の弟。";
	next;
	menu "名乗る",-;
	unittalk "マオ : ははは、会えて嬉しいぜ。気付いたかもしれないけど、オレ達兄弟は三つ子だ。";
	mes "[マオ]";
	mes "ははは、会えて嬉しいぜ。";
	mes "気付いたかもしれないけど、";
	mes "オレ達兄弟は三つ子だ。";
	next;
	unittalk "マオ : 赤ん坊の頃、村の中央で捨てられていたところをみんなが拾って育ててくれた。";
	mes "[マオ]";
	mes "赤ん坊の頃、";
	mes "村の中央で捨てられていたところを";
	mes "みんなが拾って";
	mes "育ててくれた。";
	next;
	unittalk "マオ : 村の周辺の洞窟の名にちなんで、カル、ルワンダ、マオと名付けてくれてさ。オレは末っ子のマオだ。";
	mes "[マオ]";
	mes "村の周辺の洞窟の名にちなんで、";
	mes "カル、ルワンダ、マオと";
	mes "名付けてくれてさ。";
	mes "オレは末っ子のマオだ。";
	next;
	unittalk "マオ : 昔、村を守ったといわれる守護神達の名前なんだぜ。";
	mes "[マオ]";
	mes "昔、村を守ったといわれる";
	mes "守護神達の名前なんだぜ。";
	next;
	unittalk "マオ : 今はさ、アニキ達に少しでも心配かけないように修行をしてて……。";
	mes "[マオ]";
	mes "今はさ、";
	mes "アニキ達に少しでも";
	mes "心配かけないように";
	mes "修行をしてて……。";
	next;
	unittalk "マオ : は……！！　オレがどうしてこんな話を！？";
	mes "[マオ]";
	mes "は……！！";
	mes "オレがどうしてこんな話を！？";
	next;
	unittalk "マオ : はぁ……。修業が上手く行かなくて気が緩んだかな。あっ！？　オマエ、まさかアニキ達に頼ま……。";
	mes "[マオ]";
	mes "はぁ……。";
	mes "修業が上手く行かなくて";
	mes "気が緩んだかな。";
	mes "あっ！？";
	mes "オマエ、まさかアニキ達に頼ま……。";
	if(!sleep2(2000)) end;
	set IL_LUANDA_QUE,12;
	cloakonnpc;
	next;
	mes "‐会話中にマオは";
	mes "　消え去ってしまった。";
	mes "　経験した話を";
	mes "　ルワンダに伝えよう‐";
	next;
	mes "‐ルワンダのところへ戻りますか？‐";
	next;
	if(select("戻る","まだここに居る") == 2) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	warp "com_d02_i_q.gat", 241, 248;
	end;
}

com_d02_i_q.gat,210,134,6	script(CLOAKED)	準備をするルワンダ#ILU_022	843,{
	unittalk "準備をするルワンダ : 飲み水はこれぐらいで大丈夫かな……。";
	mes "[準備をするルワンダ]";
	mes "飲み水はこれぐらいで";
	mes "大丈夫かな……。";
	next;
	unittalk "準備をするルワンダ : これらを使わないで済むのならそれに越したことはないのだけど……。";
	mes "[準備をするルワンダ]";
	mes "これらを使わないで";
	mes "済むのなら";
	mes "それに越したことは";
	mes "ないのだけど……。";
	next;
	unittalk "準備をするルワンダ : おや！？　冒険者さま、こんなところで会いましたね。この前は話している最中に……";
	mes "[準備をするルワンダ]";
	mes "おや！？";
	mes "冒険者さま、";
	mes "こんなところで会いましたね。";
	mes "この前は話している最中に……";
	next;
	unittalk "準備をするルワンダ : いきなり去ってしまうから……話が……。";
	mes "[準備をするルワンダ]";
	mes "いきなり去ってしまうから……";
	mes "話が……。";
	if(!sleep2(2000)) end;
	set IL_LUANDA_QUE,14;
	cloakonnpc;
	next;
	mes "‐準備をするルワンダは";
	mes "　消えてしまった。";
	mes "　経験した話を";
	mes "　ルワンダに伝えよう‐";
	next;
	mes "‐ルワンダのところへ戻りますか？‐";
	next;
	if(select("戻る","まだここに居る") == 2) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	warp "com_d02_i_q.gat", 241, 248;
	end;
}

com_d02_i_q.gat,157,28,4	script(CLOAKED)	村長#ILU_023	765,{
	unittalk getnpcid(0,"村人#ILU_024"),"村人 : なんて数だ！！　モンスターが押し寄せてくる！！";
	mes "[村人]";
	mes "なんて数だ！！";
	mes "モンスターが";
	mes "押し寄せてくる！！";
	next;
	unittalk getnpcid(0,"村人#ILU_025"),"村人 : み……三つ子はまだ戻らないのか？　一体、なんで襲って来るんだ！　あいつらが居ない時に限って……。";
	mes "[村人]";
	mes "み……三つ子は";
	mes "まだ戻らないのか？";
	mes "一体、なんで襲って来るんだ！";
	mes "あいつらが居ない時に";
	mes "限って……。";
	next;
	unittalk "村長 : 信じよう。三つ子達はきっと戻ってくる……。";
	mes "[村長]";
	mes "信じよう。";
	mes "三つ子達はきっと";
	mes "戻ってくる……。";
	next;
	unittalk getnpcid(0,"村人#ILU_026"),"村人 : ですが、村長、既にモンスターたちに連れて行かれた者も居ます！　彼らはもう……。";
	mes "[村人]";
	mes "ですが、村長、";
	mes "既にモンスターたちに";
	mes "連れて行かれた";
	mes "者も居ます！";
	mes "彼らはもう……。";
	next;
	unittalk "村長 : 不吉なことを言うな。信じるんだ。生きているはずだ。生きているとも……。";
	mes "[村長]";
	mes "不吉なことを言うな。";
	mes "信じるんだ。";
	mes "生きているはずだ。";
	mes "生きているとも……。";
	next;
	unittalk getnpcid(0,"村人#ILU_026"),"村人 : し……しかし、村長……。";
	mes "[村人]";
	mes "し……しかし、";
	mes "村長……。";
	next;
	unittalk "村長 : うむ……。ルワンダの忠告通り、避難できる者は避難した……。もう、出来るだけのことはやった。後は、三つ子達の帰りを諦めずに待とう。";
	mes "[村長]";
	mes "うむ……。";
	mes "ルワンダの忠告通り、";
	mes "避難できる者は避難した……。";
	mes "もう、出来るだけのことはやった。";
	mes "後は、三つ子達の帰りを";
	mes "諦めずに待とう。";
	next;
	unittalk "村長 : おや？　君は知らぬ顔だな？　何？　ルワンダの？　それはそれは、三つ子達が出払っているところに運が悪かったの……。";
	mes "[村長]";
	mes "おや？君は知らぬ顔だな？";
	mes "何？ルワンダの？";
	mes "それはそれは、三つ子達が";
	mes "出払っているところに";
	mes "運が悪かったの……。";
	next;
	unittalk "村長 : 助けたいのはやまやまだが、今は誰かを助けられる立場になくてな……。すまんの。我々は三つ子達を信じて待つ以外……。";
	mes "[村長]";
	mes "助けたいのはやまやまだが、";
	mes "今は誰かを助けられる";
	mes "立場になくてな……。";
	mes "すまんの。";
	mes "我々は三つ子達を";
	mes "信じて待つ以外……。";
	if(!sleep2(2000)) end;
	set IL_LUANDA_QUE,16;
	cloakonnpc;
	cloakonnpc "村人#ILU_024";
	cloakonnpc "村人#ILU_025";
	cloakonnpc "村人#ILU_026";
	next;
	mes "‐心配する村長は";
	mes "　消え去った。";
	mes "　経験した話を";
	mes "　ルワンダに伝えよう‐";
	next;
	mes "‐ルワンダのところへ戻りますか？‐";
	next;
	if(select("戻る","まだここに居る") == 2) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	warp "com_d02_i_q.gat", 241, 248;
	end;
}

com_d02_i_q.gat,155,29,6	script(CLOAKED)	村人#ILU_024	748,{
	unittalk "村人 : どうすれば……。";
	end;
}

com_d02_i_q.gat,153,28,6	script(CLOAKED)	村人#ILU_025	85,{
	unittalk "村人 : 三つ子はまだか！";
	end;
}

com_d02_i_q.gat,154,26,6	script(CLOAKED)	村人#ILU_026	84,{
	unittalk "村人 : 早く逃げないと！";
	end;
}

com_d02_i_q.gat,39,219,6	script(CLOAKED)	カル#ILU_027	843,{
	unittalk "カル : ようやく帰れそうだな。マオ。";
	end;
}

com_d02_i_q.gat,41,220,4	script(CLOAKED)	呆然とするルワンダ#ILU_028	843,{
	unittalk "呆然とするルワンダ : ……。";
	end;
}

com_d02_i_q.gat,43,219,4	script(CLOAKED)	マオ#ILU_029	843,{
	unittalk "マオ : 今回の狩りの結果も悪くなかったと思う。";
	mes "[マオ]";
	mes "今回の狩りの結果も";
	mes "悪くなかったと思う。";
	next;
	unittalk getnpcid(0,"カル#ILU_027"),"カル : そうだな。ちょっと不吉な出来事はあったけど、今回も良い金になりそうだぞ。な？　ルワンダ。";
	mes "[カル]";
	mes "そうだな。";
	mes "ちょっと不吉な出来事は";
	mes "あったけど、";
	mes "今回も良い金になりそうだぞ。";
	mes "な？ルワンダ。";
	next;
	unittalk "マオ : あれ？ルワンダ兄、あそこ……この前見かけた異邦人です。";
	mes "[マオ]";
	mes "あれ？ルワンダ兄、";
	mes "あそこ……";
	mes "この前見かけた異邦人です。";
	next;
	unittalk getnpcid(0,"カル#ILU_027"),"カル : おや？　そうだね。ボクも覚えているよ。";
	mes "[カル]";
	mes "おや？そうだね。";
	mes "ボクも覚えているよ。";
	next;
	unittalk getnpcid(0,"カル#ILU_027"),"カル : ハハッ。強面のルワンダが忠告したというのに、怖いもの知らずだな。";
	mes "[カル]";
	mes "ハハッ。";
	mes "強面のルワンダが";
	mes "忠告したというのに、";
	mes "怖いもの知らずだな。";
	next;
	unittalk "マオ : オレ達、みんな同じ顔だっての……。まったく、ルワンダ兄も何か言ってくれよ。";
	mes "[マオ]";
	mes "オレ達、";
	mes "みんな同じ顔だっての……。";
	mes "まったく、";
	mes "ルワンダ兄も何か言ってくれよ。";
	next;
	unittalk getnpcid(0,"呆然とするルワンダ#ILU_028"),"呆然とするルワンダ : ……カル兄！　大変だ！　村の方から猛烈な悪の気を感じる！　こんなに離れていてもはっきり分かる！！";
	mes "[呆然とするルワンダ]";
	mes "……カル兄！大変だ！";
	mes "村の方から";
	mes "猛烈な悪の気を感じる！";
	mes "こんなに離れていても";
	mes "はっきり分かる！！";
	next;
	unittalk getnpcid(0,"カル#ILU_027"),"カル : ふむ？　悪意？　村の方だと？　まさか……？　二人とも急ぐぞ！　村で何が起こっている？";
	mes "[カル]";
	mes "ふむ？悪意？";
	mes "村の方だと？まさか……？";
	mes "二人とも急ぐぞ！";
	mes "村で何が起こっている？";
	if(!sleep2(2000)) end;
	set IL_LUANDA_QUE,18;
	cloakonnpc "カル#ILU_027";
	cloakonnpc "呆然とするルワンダ#ILU_028";
	cloakonnpc;
	next;
	mes "‐3人は急いで去って行った。";
	mes "　今経験したことを";
	mes "　ルワンダに伝えよう‐";
	next;
	mes "‐ルワンダのところへ戻りますか？‐";
	next;
	if(select("戻る","まだここに居る") == 2) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	warp "com_d02_i_q.gat", 241, 248;
	end;
}

com_d02_i_q.gat,116,94,6	script(CLOAKED)	カル#ILU_030	843,{
	unittalk "カル : アスデン！　どうして？　なぜ君がこんな目に会わなければならない？　ボ……ボクが君をどんな想いで探したか……。";
	mes "[カル]";
	mes "アスデン！どうして？";
	mes "なぜ君がこんな目に";
	mes "会わなければならない？";
	mes "ボ……ボクが君を";
	mes "どんな想いで探したか……。";
	next;
	unittalk getnpcid(0,"アスデン#ILU_031"),"アスデン : カ……カル……。";
	mes "[アスデン]";
	mes "カ……カル……。";
	next;
	unittalk "カル : あぁ……アスデン……。ボクの特別な力を持つ目は、本当に力を発揮すべき時、何の役にも立たなかった……！";
	mes "[カル]";
	mes "あぁ……";
	mes "アスデン……。";
	mes "ボクの特別な力を持つ目は、";
	mes "本当に力を発揮すべき時、";
	mes "何の役にも立たなかった……！";
	next;
	unittalk getnpcid(0,"アスデン#ILU_031"),"アスデン : カル、悲しまないで……。カルは今、その目で私をどうにか見つけ出してくれたの……。";
	mes "[アスデン]";
	mes "カル、悲しまないで……。";
	mes "カルは今、";
	mes "その目で私をどうにか";
	mes "見つけ出してくれたの……。";
	next;
	unittalk getnpcid(0,"アスデン#ILU_031"),"アスデン : わたしは……嬉しいよ。";
	mes "[アスデン]";
	mes "わたしは……嬉しいよ。";
	next;
	misceffect 244,"アスデン#ILU_031";
	if(!sleep2(1000)) end;
	unittalk "カル : こ……これは……？　死よりも恐ろしい巨石族の呪い……か？　アスデンに……！？";
	mes "[カル]";
	mes "こ……これは……？";
	mes "死よりも恐ろしい";
	mes "巨石族の呪い……か？";
	mes "アスデンに……！？";
	next;
	unittalk "カル : ア……アスデン！　ボクはいつどこに居たって君をこの目で見つけ出す！　だから……、だから……！！";
	mes "[カル]";
	mes "ア……アスデン！";
	mes "ボクはいつどこに居たって";
	mes "君をこの目で見つけ出す！";
	mes "だから……、だから……！！";
	next;
	unittalk getnpcid(0,"アスデン#ILU_031"),"アスデン : あ……カル……。私の特別な人……！愛し……て……";
	mes "[アスデン]";
	mes "あ……カル……。";
	mes "私の特別な人……！";
	mes "愛し……て……";
	if(!sleep2(1000)) end;
	misceffect 244,"アスデン#ILU_031";
	if(!sleep2(1000)) end;
	misceffect 181,"アスデン#ILU_031";
	if(!sleep2(1000)) end;
	misceffect 924,"アスデン#ILU_031";
	cloakonnpc "アスデン#ILU_031";
	cloakoffnpc "アスデン#ILU_032";
	if(!sleep2(2000)) end;
	misceffect 34,"アスデン#ILU_032";
	cloakonnpc "アスデン#ILU_032";
	next;
	unittalk "カル : 置いて行かないでくれ……！！　アスデン！！！！";
	mes "[カル]";
	mes "置いて行かないでくれ……！！";
	mes "アスデン！！！！";
	if(!sleep2(2000)) end;
	set IL_LUANDA_QUE,20;
	cloakonnpc;
	cloakonnpc "アスデン#ILU_031";
	cloakonnpc "アスデン#ILU_032";
	next;
	mes "‐アスデンを追って";
	mes "　カルは消えた。";
	mes "　今経験したことを";
	mes "　ルワンダに伝えよう‐";
	next;
	mes "‐ルワンダのところへ戻りますか？‐";
	next;
	if(select("戻る","まだここに居る") == 2) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	warp "com_d02_i_q.gat", 241, 248;
	end;
}

com_d02_i_q.gat,117,94,4	script(CLOAKED)	アスデン#ILU_031	90,{}
com_d02_i_q.gat,117,94,4	script(CLOAKED)	アスデン#ILU_032	1148,{}

com_d02_i_q.gat,268,75,4	script(CLOAKED)	シルエット#ILU_033	10029,{
	unittalk "？？？？ : ククク、ニンゲンドモヲオイダシ、カノチヲテニスルノダ。";
	mes "[？？？？]";
	mes "ククク、";
	mes "ニンゲンドモヲ";
	mes "オイダシ、";
	mes "カノチヲテニスルノダ。";
	next;
	unittalk getnpcid(0,"シルエット#ILU_034"),"？？？？ : フシシ、エイユウヲエタワレラハ、イママデトハチガウ。";
	mes "[？？？？]";
	mes "フシシ、";
	mes "エイユウヲエタ";
	mes "ワレラハ、";
	mes "イママデトハ";
	mes "チガウ。";
	next;
	unittalk "？？？？ : トウソツヲエタノダカラナ、ククク。";
	mes "[？？？？]";
	mes "トウソツヲ";
	mes "エタノダカラナ、";
	mes "ククク。";
	next;
	unittalk getnpcid(0,"シルエット#ILU_034"),"？？？？ : チカラヲタクワエ、スキヲツキ、カノチヲエレバ、キョウダイナチカラハワレラガモノ。";
	mes "[？？？？]";
	mes "チカラヲ";
	mes "タクワエ、";
	mes "スキヲツキ、";
	mes "カノチヲエレバ、";
	mes "キョウダイナチカラハ";
	mes "ワレラガモノ。";
	next;
	unittalk "？？？？ : ……クンクン。ナニモノダ！？　ハナシヲキカレタカラニハ、ニンゲンドモニキヅカレルマエニウゴクカ。";
	mes "[？？？？]";
	mes "……クンクン。";
	mes "ナニモノダ！？";
	mes "ハナシヲキカレタカラニハ、";
	mes "ニンゲンドモニ";
	mes "キヅカレルマエニ";
	mes "ウゴクカ。";
	next;
	unittalk getnpcid(0,"シルエット#ILU_034"),"？？？？ : マア、モクロミガバレタトテ、セメイルコトニカワリナイ。カクゴシテイロ、ニンゲン。";
	mes "[？？？？]";
	mes "マア、モクロミガ";
	mes "バレタトテ、";
	mes "セメイルコトニ";
	mes "カワリナイ。";
	mes "カクゴシテイロ、ニンゲン。";
	if(!sleep2(2000)) end;
	set IL_LUANDA_QUE,22;
	cloakonnpc;
	cloakonnpc "シルエット#ILU_034";
	next;
	mes "‐ルワンダのところへ戻りますか？‐";
	next;
	if(select("戻る","まだここに居る") == 2) {
		mes "‐あなたはその場に留まった‐";
		close;
	}
	warp "com_d02_i_q.gat", 241, 248;
	end;
}

com_d02_i_q.gat,266,76,6	script(CLOAKED)	シルエット#ILU_034	10029,{}

com_d02_i.gat,254,243,0	warp	ILU_Luanda#ILU_002	1,1,beach_dun2.gat,249,243

com_d02_i.gat,241,255,4	script	守護者ルワンダ#ILU_004	843,{
	switch(rand(5)) {
	case 0:
		unittalk "守護者ルワンダ : 冒険者さま！　依頼はそこの掲示板をご覧ください！";
		break;
	case 1:
		unittalk "守護者ルワンダ : 巨石族め！　なぜ襲ってくるんだ！";
		break;
	case 2:
		unittalk "守護者ルワンダ : ウータン族め！　なぜ襲ってくるんだ！";
		break;
	case 3:
		unittalk "守護者ルワンダ : カル兄はきっと大丈夫だ……！";
		break;
	case 4:
		unittalk "守護者ルワンダ : マオだってきっと無事だ……！";
		break;
	}
	end;
}

com_d02_i.gat,249,250,4	script	掲示板#ILU_006	857,{
	if(checkquest(5849) & 0x2)
		delquest 5849;
	mes "‐村の掲示板だ。";
	mes "　依頼の状況が記入されている‐";
	mes "　";
	mes "[掲示板]";
	mes "【^ff0000ルワンダの依頼 状況^000000】";
	if(checkquest(5849))
		mes "^888888報告クールタイム中^000000";
	else if(checkquest(5852) & 0x4 || checkquest(5854) & 0x4)
		mes "^ff0000報告可能^000000";
	else if(checkquest(5848))
		mes "^0000ff挑戦中^000000";
	else
		mes "^888888未受注^000000";
	next;
	switch(select("依頼を受注/報告する","依頼の説明","討伐対象の変更","何もしない")) {
	case 1:
		if(checkquest(5848)) {
			if(checkquest(5849)) {
				if(!(checkquest(5849) & 0x2)) {
					mes "‐前回報告してから";
					mes "　まだ時間が経っていないため";
					mes "　報告できないようだ‐";
					close;
				}
			}
			if(checkquest(5852) & 0x4) {
				delquest 5852;
				setquest 5849;
				getitem 25271,2;
				getexp 100000000,0,1;
				getexp 0,20000000,0;
				setquest 5852;
				mes "‐報酬を手に入れた！";
				mes "　^0000ff古のメガリス　20体^000000討伐を再受注し";
				mes "　依頼の状況を掲示板に記入した‐";
				mes "　";
				mes "[掲示板]";
				mes "【^ff0000ルワンダの依頼 状況^000000】";
				mes "^888888報告クールタイム中^000000";
				close;
			}
			else if(checkquest(5854) & 0x4) {
				delquest 5854;
				setquest 5849;
				getitem 25271,2;
				getexp 100000000,0,1;
				getexp 0,20000000,0;
				setquest 5854;
				mes "‐報酬を手に入れた！";
				mes "　^0000ff古のフレイムシューター　20体^000000討伐を再受注し";
				mes "　依頼の状況を掲示板に記入した‐";
				mes "　";
				mes "[掲示板]";
				mes "【^ff0000ルワンダの依頼 状況^000000】";
				mes "^888888報告クールタイム中^000000";
				close;
			}
			mes "‐まだ依頼を達成していない。";
			mes "　達成してから報告しよう‐";
			close;
		}
		mes "[掲示板]";
		mes "モンスターの侵略を阻止してください！";
		mes "^ff0000どちらか^000000の討伐をお願いします！";
		mes "・^0000ff古のメガリス　20体^000000";
		mes "・^0000ff古のフレイムシューター　20体^000000";
		mes "　※討伐対象は受注後でも変更できます。";
		mes "　　報酬 : 洞窟で見つけた^0000ff幻想の石^000000 2個";
		next;
		switch(select("古のメガリス討伐　受注","古のフレイムシューター討伐　受注","依頼を受けない")) {
		case 1:
			setquest 5852;
			setquest 5848;
			mes "‐^0000ff古のメガリス　20体^000000討伐を受注し";
			break;
		case 2:
			setquest 5854;
			setquest 5848;
			mes "‐^0000ff古のフレイムシューター　20体^000000討伐を受注し";
			break;
		case 3:
			mes "‐その場を去った‐";
			close;
		}
		mes "　依頼の状況を掲示板に記入した‐";
		mes "　";
		mes "[掲示板]";
		mes "【^ff0000ルワンダの依頼 状況^000000】";
		mes "^0000ff挑戦中^000000";
		close;
	case 2:
		mes "[掲示板]";
		mes "モンスターの侵略を阻止してください！";
		mes "^ff0000どちらか^000000の討伐をお願いします！";
		mes "・^0000ff古のメガリス　20体^000000";
		mes "・^0000ff古のフレイムシューター　20体^000000";
		mes "　※討伐対象は受注後でも変更できます。";
		mes "　　報酬 : 洞窟で見つけた^0000ff幻想の石^000000 2個";
		next;
		mes "^ff0000【インフォメーション】";
		mes "討伐クエストは報告後、";
		mes "次の午前5時まで";
		mes "再度報告することができません。";
		mes "また、クエストの受注は";
		mes "報告時に自動的に行われます。^000000";
		close;
	case 3:
		if(!checkquest(5848)) {
			mes "‐今は依頼を受けていない‐";
			close;
		}
		mes "^ff0000【インフォメーション】";
		mes "受注している討伐対象の変更や";
		mes "キャンセルができます。^000000";
		mes "　";
		if(checkquest(5852))
			mes "^0000ff古のメガリス　20体^000000";
		else
			mes "^0000ff古のフレイムシューター　20体^000000";
		mes "^0000ff討伐受注中^000000";
		next;
		switch(select("今のまま討伐を続ける","討伐対象の変更","討伐依頼のキャンセル")) {
		case 1:
			mes "‐討伐を続けることにした‐";
			close;
		case 2:
			mes "^ff0000【インフォメーション】";
			mes "討伐対象を変更すると";
			mes "変更前の討伐は破棄されます。^000000";
			mes "　";
			if(checkquest(5852)) {
				mes "^0000ff古のメガリス　20体^000000";
				set '@target$,"古のフレイムシューター";
				set '@old_id,5852;
				set '@new_id,5854;
			}
			else {
				mes "^0000ff古のフレイムシューター　20体^000000";
				set '@target$,"古のメガリス";
				set '@old_id,5854;
				set '@new_id,5852;
			}
			mes "^0000ff討伐受注中^000000";
			next;
			if(select("今のまま討伐を続ける","対象を^0000ff" +'@target$+ "　20体^000000に変更する") == 1) {
				mes "‐討伐を続けることにした‐";
				close;
			}
			delquest 5848;
			delquest '@old_id;
			setquest '@new_id;
			setquest 5848;
			mes "‐討伐する対象を";
			mes "　^0000ff" +'@target$+ "　20体^000000に変更し、";
			mes "　依頼の状況を掲示板に記入した‐";
			mes "　";
			mes "[掲示板]";
			mes "【^ff0000討伐状況^000000】";
			mes "^0000ff挑戦中^000000";
			close;
		case 3:
			mes "^ff0000【インフォメーション】";
			mes "討伐をキャンセルをすると";
			mes "受注中の討伐は破棄されます。^000000";
			mes "　";
			if(checkquest(5852))
				mes "^0000ff古のメガリス　20体^000000";
			else
				mes "^0000ff古のフレイムシューター　20体^000000";
			mes "^0000ff討伐受注中^000000";
			next;
			if(select("今のまま討伐を続ける","討伐をキャンセルする") == 1) {
				mes "‐討伐を続けることにした‐";
				close;
			}
			delquest 5848;
			if(checkquest(5852))
				delquest 5852;
			else
				delquest 5854;
			mes "‐討伐をキャンセルし、";
			mes "　依頼の状況を掲示板に記入した‐";
			mes "　";
			mes "[掲示板]";
			mes "【^ff0000討伐状況^000000】";
			mes "^888888未受注^000000";
			close;
		}
	case 4:
		mes "‐その場を去った‐";
		close;
	}
}

com_d02_i.gat,0,0,0,0			monster	古のウータンファイター	20276,10,5000,0,#IllLuanda::OnSummon
com_d02_i.gat,140,210,110,60	monster	古のウータンファイター	20276,35,5000,0,#IllLuanda::OnSummon
com_d02_i.gat,0,0,0,0			monster	古のフレイムシューター	20274,10,5000,0,#IllLuanda::OnSummon
com_d02_i.gat,140,210,110,60	monster	古のフレイムシューター	20274,35,5000,0,#IllLuanda::OnSummon

com_d02_i.gat,0,0,0	script	#IllLuanda	-1,{
OnKilled:
	initnpctimer;
	end;
OnSummon:
	if('mob == 0) {
		set 'count,'count+1;
		if('count >= 1000 && rand(10) == 0) {
			set 'mob,areacallmonster("com_d02_i.gat",30,150,250,270,"古のウータンガード",20277,strnpcinfo(0)+"::OnKilled");
			set '@dummy,getmapxy('@map$,'@x,'@y,3,'mob);
			mobuseskillpos 'mob,21,10,'@x,'@y,0,0;	// サンダーストーム
			mobuseskill 'mob,730,1,0,0,-1,0,0;	// M呪縛陣
			unittalk 'mob,"古のウータンガード : 全く役に立たない奴らだ、結局俺の出番なのか。";
		}
	}
	end;
OnTimer7200000:
	stopnpctimer;
	set 'mob,0;
	set 'count,0;
	end;
}
