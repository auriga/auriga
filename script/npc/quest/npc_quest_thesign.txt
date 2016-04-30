//==============================================================================
// Ragnarok Online The Sign Script     by AthenaDev
//
//　■ SIGN_QUE -> 0～144,198～203
//==============================================================================

//============================================================
// Warp
//------------------------------------------------------------
//メッツの家
prontera.gat,263,279,0	warp	signwarp1001	1,1,prt_in.gat,227,18
prt_in.gat,227,15,0	warp	signwarp1002	1,1,prontera.gat,263,275
//ダンス試験場
cmd_in01.gat,17,34,0	warp	signwarp1003	1,1,comodo.gat,187,164
//ハワードの家
geffen.gat,140,99,0	warp	signwarp1004	1,1,geffen_in.gat,166,50
geffen_in.gat,166,54,0	warp	signwarp1005	1,1,geffen.gat,137,102
//サイオンの家
um_dun01.gat,132,91,0	warp	signwarp1006	1,1,um_in.gat,15,20
um_in.gat,11,18,0	warp	signwarp1007	1,1,um_dun01.gat,129,90
um_in.gat,33,18,0	warp	signwarp1008	1,1,um_in.gat,89,11
um_in.gat,89,9,0	warp	signwarp1009	1,1,um_in.gat,33,16
//ヴァルキリー神殿（ヒミン）
himinn.gat,49,67,0	warp	signwarp1010	1,1,himinn.gat,49,75
himinn.gat,49,72,0	warp	signwarp1011	1,1,himinn.gat,49,63
himinn.gat,49,6,0	warp	signwarp1012	1,1,gef_fild07.gat,179,241
//ヘルの館
que_sign01.gat,113,132,0	warp	signwarp1013	1,1,nif_in.gat,117,173
que_sign01.gat,179,169,0	warp	signwarp1014	1,1,niflheim.gat,30,156
que_sign01.gat,179,19,0	warp	signwarp1014	1,1,niflheim.gat,30,156
que_sign01.gat,45,15,0	warp	signwarp1014	1,1,niflheim.gat,146,245
//ヘルの庭
que_sign02.gat,22,313,0	warp	signwarp1014	1,1,niflheim.gat,30,156

//============================================================
// Monster
//------------------------------------------------------------
que_sign02.gat,0,0,0,0	monster	エンシェントマミー	1522,8,0,0,0
que_sign02.gat,0,0,0,0	monster	イビルドルイド		1435,8,0,0,0
que_sign02.gat,0,0,0,0	monster	グール			1423,20,0,0,0
que_sign02.gat,0,0,0,0	monster	インキュバス		1580,8,0,0,0
que_sign02.gat,0,0,0,0	monster	インジャスティス	1446,8,0,0,0
que_sign02.gat,0,0,0,0	monster	スケルプリズナー	1479,15,0,0,0
que_sign02.gat,0,0,0,0	monster	ゾンビプリズナー	1480,15,0,0,0
que_sign02.gat,0,0,0,0	monster	レイス			1475,15,0,0,0
que_sign02.gat,0,0,0,0	monster	デッドリーレイス	1566,8,0,0,0

//============================================================
// 第1部
//------------------------------------------------------------
-	script	張り紙#sign	111,{
	cutin "sign_01",4;
	mes "次へ";
	next;
	cutin "sign_02",4;
	mes "次へ";
	next;
	cutin "sign_03",4;
	mes "次へ";
	next;
	cutin "sign_04",4;
	mes "終わり";
	if(SIGN_QUE == 0)
		set SIGN_QUE,1;
	close2;
	cutin "sign_04",255;
	end;
}
prontera.gat,147,305,0	duplicate(張り紙#sign)	張り紙	111
geffen.gat,168,175,0	duplicate(張り紙#sign)	張り紙	111
morocc.gat,168,265,0	duplicate(張り紙#sign)	張り紙	111
payon.gat,160,183,0	duplicate(張り紙#sign)	張り紙	111
aldebaran.gat,54,223,0	duplicate(張り紙#sign)	張り紙	111
alberta.gat,35,241,0	duplicate(張り紙#sign)	張り紙	111

prt_in.gat,227,45,0	script	考古学者	804,{
	cutin "mets_alpha",2;
	switch(SIGN_QUE) {
	case 0:
		mes "[メッツ]";
		mes "発掘、そして探検には努力と粘りが";
		mes "大事です。";
		mes "もちろん、その前に十分な";
		mes "研究や調査が必要ですがね。";
		break;
	case 1:
		mes "[メッツ]";
		mes "おや、何かご用ですかな？";
		next;
		if(select("張り紙を見て来ました","単なる通りすがりです")==2) {
			mes "[メッツ]";
			mes "世の中には色々な人がいます。";
			mes "機会に巡り合えても、それを";
			mes "なかなか活かすことができない人。";
			mes "あなたにも、いささかそんな";
			mes "印象を受けました……";
			mes "いや、失礼。";
			break;
		}
		mes "[メッツ]";
		mes "おやおや、そうですか。";
		mes "よく来てくれました。";
		next;
		if(BaseLevel < 50) {
			mes "[メッツ]";
			mes "しかし、残念ながら";
			mes "あなたにこの仕事を任せる";
			mes "ことはできません。熱意や";
			mes "意気込みだけでは、出来ないことも";
			mes "あるのです。もっと経験を積んでから";
			mes "いらしてください。";
			break;
		}
		mes "[メッツ]";
		mes "う～ん、良いでしょう。";
		mes "あなたは十分強そうです。";
		mes "もう少し準備がありますので、";
		mes "しばらく時間をくださいますか。";
		next;
		mes "[メッツ]";
		mes "あ～、ところであなたのお名前は……";
		mes "^FF0000" +strcharinfo(0)+ "^000000ですか。";
		mes "はい、ありがとうございます。";
		mes "では、また後ほど。";
		set SIGN_QUE,2;
		break;
	case 2:
		mes "[メッツ]";
		mes "待たせてしまいましたか？";
		mes "思っていたより準備に手間取って";
		mes "しまいまして。";
		mes "申し訳ございません。";
		next;
		mes "[メッツ]";
		mes "うーん……そうですね。";
		mes "私がどうしてあんな張り紙を";
		mes "出したか、分かりますかな？";
		mes "それだけ私にとって、大切な";
		mes "ことなのです。そしてその為に、";
		mes "まず簡単な試練を受けてください。";
		next;
		mes "[メッツ]";
		mes "合格しましたら、詳細をお話ししたいと";
		mes "思います。私の目的は、とても危険を";
		mes "伴うことかもしれないので、誰にでも";
		mes "任せられる話ではないのです。";
		next;
		mes "[メッツ]";
		mes "うーん……そうですね～。";
		mes "まず、^FF0000モロク^000000へ行き、";
		mes "^FF0000アーリア^000000を探してください。";
		mes "彼が最初の試練について教えて";
		mes "くれます。";
		next;
		mes "[メッツ]";
		mes "それでは、全ての試練が終わったら、";
		mes "再び私のもとへいらしてください。";
		mes "その時、詳細をお話しします。";
		next;
		mes "[メッツ]";
		mes "あ～……アーリアですか。";
		mes "え～とですね、その方は私からの";
		mes "連絡無しでは、何も話して";
		mes "くれないかと。もし、すでに会って";
		mes "いらして、不愉快な思いをしたなら";
		mes "かわりにお詫びします。";
		set SIGN_QUE,3;
		break;
	case 3:
		mes "[メッツ]";
		mes "う～ん？";
		mes "まだ出発なさっていなかったのですか？";
		mes "もうアーリアには連絡しましたから。";
		mes "心配せずにお出かけください。";
		break;
	case 53:
		mes "[メッツ]";
		mes "おぉ……見事です。";
		mes "いやいや、やはり私の目に";
		mes "狂いはなかったですな。";
		next;
		mes "[メッツ]";
		mes "ここまで試練に打ち勝ってきたのなら、";
		mes "スタージュエルのかけらを6つ";
		mes "持っておられるはずです。";
		mes "早速、それについて説明しましょう。";
		next;
		mes "[メッツ]";
		mes "あれは夏も終わりに近い頃……";
		mes "北ミョルニール山脈を調査していた時に";
		mes "発見したものなのです。";
		mes "発見した時は一つだったのですが、";
		mes "空気に触れたとたん、このように";
		mes "割れてしまったのです。";
		next;
		mes "[メッツ]";
		mes "そして私は、これを元通りにしたい。";
		mes "それには、自分だけの力では無理だと";
		mes "感じ、このような形で、協力いただける";
		mes "方を探すことにしたのです。";
		next;
		mes "[メッツ]";
		mes "この、スタージュエルのかけらですが";
		mes "まったく正体がつかめていません。";
		mes "このかけら、割れた表面を見ると、";
		mes "紋様が見えますでしょう。";
		next;
		mes "[メッツ]";
		mes "特定のパターンであることも含め、";
		mes "私はこれが文字ではないかと";
		mes "予想しております。この文字を解読し、";
		mes "何が書かれているか知りたいのです。";
		next;
		mes "[メッツ]";
		mes "あ、そのかけらをこちらに";
		mes "お渡しいただけませんか。";
		mes "面白いものを見せましょう。";
		next;
		misceffect 304;
		mes "^3355FFメッツはスタージュエルのかけらを";
		mes "受け取ると、懐から、もう一つかけらを";
		mes "取り出し、一つの形に合わせた。";
		mes "すると、一つに合わされたかけらが、";
		mes "神秘的な輝きを放ち始めた-^000000";
		next;
		mes "[メッツ]";
		mes "いかがです？";
		mes "このようになっていても、";
		mes "このかけら達は壊れたわけでは";
		mes "ないのです。";
		mes "きっと、優れた鍛冶師ならこれを";
		mes "一つに戻すこともできるでしょう。";
		next;
		mes "[メッツ]";
		mes "私は引き続きそのような鍛冶師を";
		mes "探すとします。";
		mes "見つかればすぐにでも";
		mes "ご連絡を差し上げますので、";
		mes "朗報をお待ちください。";
		next;
		mes "[メッツ]";
		mes "では、最後のかけらも";
		mes strcharinfo(0)+ "様に";
		mes "お預けしましょう。";
		mes "では、連絡をお待ちください。";
		set SIGN_QUE,54;
		getitem 7177,1;
		break;
	case 54:
		if(rand(5)) {
			mes "[メッツ]";
			mes "今、少しずつ情報が入ってきています。";
			mes "もうすぐ、スタージュエルのかけらを";
			mes "一つに戻せる鍛冶師が見つかりますぞ。";
			mes "もうしばらく、お待ちを。";
			break;
		}
		mes "[メッツ]";
		mes "おー、よくぞいらっしゃいました！";
		mes "実は、スタージュエルのかけらを";
		mes "一つに戻せそうな方が、先ほど";
		mes "見つかったのです！　大陸最高の";
		mes "鍛冶師と呼ばれる、";
		mes "^FF0000エンゲル・ハワード^000000という方です。";
		next;
		mes "[メッツ]";
		mes "ところが……";
		mes "現在、彼は行方不明とのこと。";
		mes "彼の家族は、ゲフェンにいるという";
		mes "情報まではつかめました。";
		mes "このまますぐに行って、";
		mes "調べてはもらえませんか。";
		next;
		mes "[メッツ]";
		mes "それでは、お願いしますぞ。";
		break;
	case 71:
	case 72:
		mes "[メッツ]";
		mes "おお、お疲れ様でした。";
		mes "これが、修復された";
		mes "スタージュエルのかけらですか。";
		mes "宝石としても、十分に高値が";
		mes "つくでしょうな。しかし、そこで";
		mes "止めるわけにはいきません。";
		next;
		mes "[メッツ]";
		mes "これはきっと、あなたを古代の力へ";
		mes "導いてくれるはずです。それを";
		mes "証明するのは……スタージュエルに";
		mes "ついて書かれている本です。";
		next;
		mes "[メッツ]";
		mes "その本に関しては、^FF0000ゲフェンタワーの";
		mes "ウィザード^000000を訪ねればいいでしょう。";
		set SIGN_QUE,72;
		break;
	case 73:
	case 74:
	case 75:
		mes "[メッツ]";
		mes "そうですか。その方はゲフェンに";
		mes "いなかったのですか。私のほうも、";
		mes "引き続き情報を集めてみましょう。";
		break;
	case 76:
		mes "[メッツ]";
		mes "おかえりなさい。";
		mes "おお、そうですか。わかりました。";
		mes "では、古代言語文を見せて";
		mes "いただけますかね？";
		next;
		mes "[メッツ]";
		mes "うん、やはり……予想通りですね。";
		mes "この文を解読できる方は、今はもう";
		mes "ほとんどいないでしょう。";
		next;
		mes "[メッツ]";
		mes "幸いにも、私はこの言語を";
		mes "解読できる方に心当たりがあります。";
		mes "その方が解読できなければ、";
		mes "おそらく……諦めるしかないでしょう。";
		next;
		mes "[メッツ]";
		mes "これを持って、フランクという方を";
		mes "訪ねてください。その方なら必ず、";
		mes "この文を解読できるでしょう。";
		while(1) {
			next;
			switch(select("フランクってどなたですか？","その方はどこに？","分かりました、では。")) {
			case 1:
				mes "[メッツ]";
				mes "本名はフランク・フランクリンと";
				mes "言います。隠居生活に入っていて、";
				mes "ほとんど人との接触がありませんが";
				mes "古代に関する知識は、誰よりも";
				mes "豊富です。";
				next;
				mes "[メッツ]";
				mes "しかし、とても気難しくて、かく言う";
				mes "私も会えたことがありません。";
				mes "でも、あなたなら何とかすることが";
				mes "できるような予感がしますよ。";
				break;
			case 2:
				mes "[メッツ]";
				mes "その方は今、^FF0000沈没船^000000の";
				mes "研究に取り組んでいると聞きました。";
				mes "海を観察するため、家に帰らない日も";
				mes "多いとか。";
				set SIGN_QUE,77;
				break;
			case 3:
				mes "[メッツ]";
				mes "幸運を祈っていますよ。";
				close2;
				cutin "mets_alpha",255;
				end;
			}
		}
	case 77:
	case 78:
	case 79:
		mes "[メッツ]";
		mes "本名はフランク・フランクリンと";
		mes "言います。隠居生活に入っていて、";
		mes "ほとんど人との接触がありませんが";
		mes "古代に関する知識は、誰よりも";
		mes "豊富です。";
		next;
		mes "[メッツ]";
		mes "しかし、とても気難しくて、かく言う";
		mes "私も会えたことがありません。";
		mes "でも、あなたなら何とかすることが";
		mes "できるような予感がしますよ。";
		break;
		next;
		mes "[メッツ]";
		mes "その方は今、^FF0000沈没船^000000の";
		mes "研究に取り組んでいると聞きました。";
		mes "海を観察するため、家に帰らない日も";
		mes "多いとか。";
		break;
	case 80:
	case 81:
		mes "[メッツ]";
		mes "おかえりなさい。どうでした？";
		mes "ほう、これですか……私が思うに、";
		mes "この内容は特定の場所を指して";
		mes "いるようですな。そして鍵は……";
		mes "何かのアイテムですかな。";
		next;
		mes "[メッツ]";
		mes "詳しい事は、こちらでも調査して";
		mes "見ますが……";
		mes strcharinfo(0)+ "様も、";
		mes "引き続き頑張ってくだされ。";
		break;
	case 82:
		mes "[メッツ]";
		mes "なるほど!!";
		mes "「天に届く塔」とは";
		mes "ゲフェンタワーのことでしたか。";
		next;
		mes "[メッツ]";
		mes "ううん……「選ばれなかった者が";
		mes "自らを隠し生きる者の場所」";
		mes "ですか……うーん……";
		mes "まだまだ謎が多いですな。";
		break;
	case 137:
		mes "[メッツ]";
		mes "おお、それは！";
		mes "それこそ、私が求めていたもの！";
		next;
		mes "[メッツ]";
		mes "すぐに研究を始めるとします。";
		mes "解明まで時間がかかりますので、";
		mes "時間をください。";
		mes "では、預かりましょう。";
		delitem 7314,1;
		set SIGN_QUE,138;
		set SIGN_SUBQUE,gettime(3)/2+1;
		break;
	case 138:
		if((SIGN_SUBQUE*2+2)%24 != gettime(3) && (SIGN_SUBQUE*2+3)%24 != gettime(3)) {
			mes "[メッツ]";
			mes "まだ研究中です。";
			mes "もう少し時間をくださいませんか。";
			break;
		}
		mes "[メッツ]";
		mes "これは凄いですね。";
		mes "まず、これはこの世界に存在しない";
		mes "材質で作られています。";
		mes "そして、この青いレンズこそ";
		mes "探していた強大な力の正体です。";
		next;
		mes "[メッツ]";
		mes "この周辺にあしらわれている古代文字が";
		mes "封印の役割をしているようですな。";
		mes "どうやら、ゲフェンタワーと噴水台の";
		mes "力の源でもあったらしい。";
		next;
		mes "[メッツ]";
		mes "だがそれも、あなたがこれの所有者と";
		mes "なったため、タワーと噴水台の力は";
		mes "今はこの古代文字に宿っている模様。";
		mes "この封印が解けたら、一大事ですな……";
		next;
		mes "[メッツ]";
		mes "この力は、あなたがヴァルハラに";
		mes "出入りするために必要なエネルギーを";
		mes "提供する役割もあるようです。";
		next;
		mes "[メッツ]";
		mes "そのような品に敢えて手を出すのなら";
		mes "やはり、並大抵の人間では扱えない";
		mes "でしょう。";
		next;
		mes "[メッツ]";
		mes "大陸最高の鍛冶屋、";
		mes "エンゲル・ハワードの";
		mes "出番再び、ですな。";
		set SIGN_QUE,139;
		set SIGN_SUBQUE,0;
		getitem 7314,1;
		break;
	case 139:
	case 140:
		mes "[メッツ]";
		mes "エンゲル・ハワードには会って";
		mes "みましたかな？　彼なら、これを";
		mes "扱うことができるでしょう。";
		break;
	case 141:
		if(countitem(2644) < 1) {
			mes "[メッツ]";
			mes "エンゲル・ハワードには会って";
			mes "みましたかな？　彼なら、これを";
			mes "扱うことができるでしょう。";
			break;
		}
		mes "[メッツ]";
		mes "おお、おかえりなさい。";
		mes "待っていましたよ。";
		next;
		mes "[メッツ]";
		mes "やはり……";
		mes "凄い力ですな。";
		mes "…………ありがとうございます。";
		mes "私は、十分満足しました。";
		next;
		mes "[メッツ]";
		mes "この力の事を、ここまで確認出来て";
		mes "本当に良かった。";
		mes "ここまで私に付き合ってくれて";
		mes "ありがとう。";
		mes "そして、お疲れさまでした。";
		set SIGN_QUE,142;
		if(checkre())
			getexp 200000,0;
		else
			getexp 2000000,0;
		break;
	case 201:
		mes "[メッツ]";
		mes "失敗したのですか。";
		mes "う～ん、残念ですが……";
		mes "お疲れ様でしたな。";
		next;
		mes "[メッツ]";
		mes "私が見てみたかった物は手に";
		mes "入りませんでしたが、おかげで、";
		mes "色々な経験が出来ました。";
		next;
		mes "[メッツ]";
		mes "少ないですが、報酬を差し上げたいと";
		mes "思います。";
		mes "わずかですが、どうかお役立て";
		mes "ください。";
		next;
		mes "[メッツ]";
		mes "そして、スタージュエルは返して";
		mes "いただきますよ。";
		delitem 7178,1;
		set SIGN_QUE,202;
		if(checkre())
			getexp 10000,0;
		else
			getexp 100000,0;
		getitem 617,1;
		break;
	default:
		if(SIGN_QUE < 13) {
			mes "[メッツ]";
			mes "アーリアに会ってください。";
			mes "あまり遅いようでしたら、他の方に";
			mes "頼みたいと思っております。";
			mes "どうか、早く発ってください。";
			next;
			mes "[メッツ]";
			mes "うーん……";
			mes "アーリアを見かけだけで判断しては";
			mes "だめですよ……";
			break;
		}
		else if(SIGN_QUE < 15) {
			mes "[メッツ]";
			mes "あ～！";
			mes "アーリアの承諾を得られましたね。";
			mes "今度は、ダイウですね。";
			mes "ダイウは……";
			mes "え～と……面白い方です。";
			break;
		}
		else if(SIGN_QUE < 20) {
			mes "[メッツ]";
			mes "ダイウの試練もクリアされましたか。";
			mes "次はヨルニムです。";
			mes "彼はとても研究熱心ですので、";
			mes "時間を選んで訪問した方が";
			mes "よさそうです。";
			break;
		}
		else if(SIGN_QUE < 25) {
			mes "[メッツ]";
			mes "ジスクリエは……まだ若いですしね。";
			mes "少し、自分が見えていないところも";
			mes "ありますが、優れた方ですよ。";
			break;
		}
		else if(SIGN_QUE < 35) {
			mes "[メッツ]";
			mes "ディアリースですか……";
			mes "うーん……なにか、行方のヒントでも";
			mes "あれば良いのですが……";
			break;
		}
		else if(SIGN_QUE < 53) {
			mes "[メッツ]";
			mes "いよいよ、ベーカーですか。";
			mes "彼は最近、とても忙しいらしいですな。";
			break;
		}
		else if(SIGN_QUE < 71) {
			mes "[メッツ]";
			mes "あなたにばかり動いて";
			mes "いただいてしまっているようで、";
			mes "申し訳ない。";
			next;
			mes "[メッツ]";
			mes "私は、スタージュエルのかけらに";
			mes "ついて引き続き情報を集めています。";
			mes "修復後も、きっと役に立つでしょう。";
			break;
		}
		else if(SIGN_QUE < 98) {
			mes "[メッツ]";
			mes "自分を隠したまま生きている";
			mes "者達の村ですか。";
			mes "もしかしたら、その村がその者達の";
			mes "姿を隠しているのかもしれませんね。";
			break;
		}
		else if(SIGN_QUE < 137) {
			mes "[メッツ]";
			mes "もう少しです。頑張ってください。";
			break;
		}
		else if(SIGN_QUE > 201) {
			mes "[メッツ]";
			mes "いや、残念でなりません。";
			mes "もう少しで、スタージュエルの";
			mes "事がわかったのに……";
			break;
		}
		mes "[メッツ]";
		mes "あなたのおかげで、長年の夢が";
		mes "適いました。もし、また何かあったら";
		mes "お願いしていいですかな？";
		break;
	}
	close2;
	cutin "mets_alpha",255;
	end;
}

prt_in.gat,228,26,3	script	執事	55,{
	if(SIGN_QUE < 3) {
		mes "[ハデス]";
		mes "いらっしゃいませ。";
		mes "どのようなご用件で";
		mes "いらしたのでしょうか。";
		next;
		switch(select("用なんてないです","メッツさんに会いに","お金ちょうだい")) {
		case 1:
			mes "[ハデス]";
			mes "用がないなら、お帰りください。";
			close;
		case 2:
			mes "[ハデス]";
			mes "ご主人様は書斎にいらっしゃいます。";
			mes "取り次ぎますので少々お待ちください。";
			close;
		case 3:
			mes "[ハデス]";
			mes "……";
			mes "無礼な方ですね。";
			mes "ただちにお帰りください！";
			close2;
			percentheal -30,0;
			warp "prontera.gat",150,150;
			end;
		}
	}
	else if(SIGN_QUE < 14) {
		mes "[ハデス]";
		mes "いらっしゃいませ、";
		mes strcharinfo(0)+ "様。";
		mes "どんなご用でしょうか？";
		next;
		switch(select("アーリアはどんな方ですか？","メッツさんの仕事って何ですか？","イルシはどんな方ですか？")) {
		case 1:
			mes "[ハデス]";
			mes "彼は……とても無口な方だと";
			mes "聞いております。また、少しばかり";
			mes "気が荒いと。お会いになられるなら、";
			mes "言葉には気をつけた方がよろしいかと";
			mes "存じます。";
			close;
		case 2:
			mes "[ハデス]";
			mes "それは……";
			mes "その点に関しては何も";
			mes "申し上げるわけには参りません。";
			close;
		case 3:
			mes "[ハデス]";
			mes "イルシは……";
			mes "幼い頃からここで働いております。";
			mes "私には孫娘みたいな子でして。";
			mes "とても、良い子です……";
			close;
		}
	}
	else if(SIGN_QUE < 15) {
		mes "[ハデス]";
		mes "あぁ、イルシも恋人がいて";
		mes "おかしくない年齢ですね。あの子は";
		mes "プロンテラでも話題の美女でして。";
		next;
		mes "[ハデス]";
		mes "かなりたくさんの男性から求愛を";
		mes "受けていると聞いておりますが、";
		mes "あの子は全て断っているそうです。";
		mes "何か理由でもあるのか……";
		close;
	}
	else if(SIGN_QUE < 20) {
		mes "[ハデス]";
		mes "そう言えばこの頃、張り紙の件で";
		mes "ご主人様に会いに来られる方が";
		mes "増えました。";
		mes "ううん……";
		next;
		mes "[ハデス]";
		mes "かなりたくさんの方がご主人様を";
		mes "訪ねていらしてますので、あまり";
		mes "ゆっくり構えていると、機会を逃して";
		mes "しまうかもしれません。どうか";
		mes "諦めないようご忠告させて";
		mes "いただきます。";
		close;
	}
	else if(SIGN_QUE < 25) {
		mes "[ハデス]";
		mes "ジスクリエ様は確かに素晴らしい";
		mes "お方ですが、仕事柄の性質か、";
		mes "どうしても自尊心が高くなると";
		mes "言いますか……";
		next;
		mes "[ハデス]";
		mes "もう少し、控えめにされるほうが";
		mes "好ましいと思いますが、性格や性質は";
		mes "そう簡単に変えられるものでも";
		mes "ございませんので……";
		close;
	}
	else if(SIGN_QUE < 35) {
		mes "[ハデス]";
		mes "人の欲求には終わりがありません。";
		mes "特に、賭博は人の欲求そのものを";
		mes "見るようです。";
		next;
		mes "[ハデス]";
		mes "当たっている時は運が良いと賭けを続け";
		mes "損をしたら、負けを取り返すように";
		mes "賭けを続け、結果として何も残らない。";
		close;
	}
	else if(SIGN_QUE < 54) {
		mes "[ハデス]";
		mes "ベーカー様は凄い方です。";
		mes "若いのに、彼ほど成功した方を";
		mes "私は知りません。先代から受け継いだ";
		mes "事業を維持していくだけでも、とても";
		mes "大変なことかと存じます。";
		next;
		mes "[ハデス]";
		mes "しかも、ただ維持するのではなく";
		mes "事業を拡大しておられます。";
		mes "その能力は賞賛に値します。";
		close;
	}
	else if(SIGN_QUE == 54) {
		mes "[ハデス]";
		mes "お疲れさまでした。";
		mes "試練を無事に終了されたと聞きました。";
		mes "実は、あの試練ですが、かなりの方が";
		mes "途中で挫折されております。";
		next;
		mes "[ハデス]";
		mes "次の段階に向け、ご主人様は情報収集に";
		mes "力を注いでおります。";
		mes "新しい進展がございますまで、しばらく";
		mes "休まれたらいかがですか？";
		close;
	}
	mes "[ハデス]";
	mes "大事なものこそ、熟考を重ねると";
	mes "よろしいかと存じます。";
	close;
}

prt_in.gat,248,23,2	script	メイド	1275,{}
prt_in.gat,248,23,0	script	メイド	111,{
	if(SIGN_QUE < 3) {
		mes "[イルシ]";
		mes "……";
		mes "何かご用ですか？";
		mes "ここはご主人さまのお部屋です。";
		mes "出て行ってください。";
		close;
	}
	else if(SIGN_QUE < 14) {
		mes "[イルシ]";
		mes "あら、";
		mes strcharinfo(0)+ "様。";
		mes "何かご用でしょうか？";
		next;
		set '@str$,(Sex? "イルシちゃん、時間ある？": "イルシって綺麗～");
		if(select('@str$,"メッツさんってどんな方でしょう？")==2) {
			mes "[イルシ]";
			mes "うーん……";
			mes "難しい質問です、ご主人さまは……";
			next;
			mes "[イルシ]";
			mes "いいえ。";
			mes "雇われの身で、雇い主様を評価する";
			mes "わけにはまいりません。";
			close;
		}
		if(Sex) {
			mes "[イルシ]";
			mes "え？";
			mes "……それはデートのお申し込みですか？";
			mes "…………";
			next;
			mes "[イルシ]";
			mes "「時間ある？」はないでしょう？";
			mes "うーん、むしろそれは……";
			mes strcharinfo(0)+ "様次第です。";
			mes "フフ……。";
			close;
		}
		else {
			mes "[イルシ]";
			mes "あ、どうも……ありがとうございます。";
			mes "あの、私の仕事はあまり外に";
			mes "出ませんから、色白に見えるだけ";
			mes "なのかもしれませんが……";
			mes "あの、" +strcharinfo(0)+ "様も";
			mes "とてもステキです。";
			close;
		}
	}
	else if(SIGN_QUE < 15) {
		mes "[イルシ]";
		mes "最近の男性は情けないです。";
		mes "興味をあからさまに表すか";
		mes "影でコソコソしてるか。";
		next;
		emotion 32;
		mes "[イルシ]";
		mes "ただ大人しいだけかもしれませんが";
		mes "最近の男性には真心を感じません。";
		close;
	}
	else if(SIGN_QUE < 20) {
		mes "[イルシ]";
		mes "今日は少し疲れています。";
		mes "時々、こういう日もありますよね。";
		mes "仕事が多かったわけでもないのに……";
		next;
		mes "[イルシ]";
		mes "こんな日は、部屋でぐっすり";
		mes "休みたいですが、仕事がありますもの。";
		mes "薬を飲んで、がんばらなきゃ。";
		close;
	}
	else if(SIGN_QUE < 25) {
		mes "[イルシ]";
		mes "ジスクリエさん？";
		mes "あの……とても美しい方です。";
		mes "それに、才能もある方で、私なんか";
		mes "比較にならないくらいです。";
		next;
		emotion 9;
		mes "[イルシ]";
		mes "とても羨ましいですが、あの方と私の";
		mes "差を埋めることなんて、毎日どれだけ";
		mes "努力しても無理ですもの。";
		close;
	}
	else if(SIGN_QUE < 35) {
		mes "[イルシ]";
		mes "コモドに行かれたことありますか？";
		mes "私、前に1回だけ行ったことがあるの";
		mes "ですが、とっても素敵な場所でした！";
		mes "コモドのカジノ……";
		mes "面白かったんですが……";
		next;
		mes "[イルシ]";
		mes "あそこに住みたいとは思いません。";
		mes "だって、なんか誘惑に負けそう";
		mes "ですもの……";
		close;
	}
	else if(SIGN_QUE < 54) {
		mes "[イルシ]";
		mes "ベーカー様のお屋敷に、サイリンと言う";
		mes "メイドがいます。ミッドガッツ出身では";
		mes "ないらしいのですが、それではどこの";
		mes "出身なんでしょう？";
		next;
		mes "[イルシ]";
		mes "この前、ここにいらした時に";
		mes "会ったことがあります。";
		mes "そうですね……異国的な美しさとでも";
		mes "言うのでしょうか……";
		mes "ジスクリエさんとはまた違った";
		mes "美しさでした。";
		close;
	}
	else if(SIGN_QUE == 54) {
		emotion 2;
		mes "[イルシ]";
		mes "こんにちは。お久しぶりです。";
		mes "ラララ～♪";
		next;
		if(select("何か良い事でも？","何かあったの？")==1) {
			mes "[イルシ]";
			mes "え？　あの、実は";
			mes "ボーイフレンドが出来たんです。";
			next;
			mes "[イルシ]";
			mes "とても嬉しくて♪";
			mes "あの、彼って背が高くて、ハンサムで";
			mes "いつも綺麗な服で、それで……";
			mes "ぺちゃくちゃぺちゃ……";
			next;
			mes "^3355FFあなたはこっそりと席を立った。";
			mes "これ以上聞いていると、腹が立って";
			mes "きそうだ。^000000";
			close;
		}
		mes "[イルシ]";
		mes "うーん……";
		mes "あった事はありましたが……";
		mes "ふふ、ひ・み・つ・です。";
		mes "ラララ～♪";
		close;
	}
	emotion 32;
	mes "[イルシ]";
	mes "あらあらあら、大変大変！";
	mes "最近、お客様がいっぱい！";
	close;
}

//============================================================
// 第1部 - アーリアの試練
//------------------------------------------------------------
morocc_in.gat,115,154,5	script	ローグ	810,{
	if(SIGN_QUE < 3) {
		emotion 9;
		end;
	}
	switch(SIGN_QUE) {
	case 3:
		mes "[アーリア]";
		mes "…………";
		mes "誰だ？";
		next;
		switch(select("メッツさんの所から来ました","^0000FF" +strcharinfo(0)+ "^000000です","そう言うあなたは？")) {
		case 1:
			mes "[アーリア]";
			mes "ふん。";
			mes "信じられるか。消えろ。";
			close2;
			warp "morocc.gat",279,173;
			end;
		case 2:
			mes "[アーリア]";
			mes "…………";
			mes "ああ……";
			mes "^0000FF" +strcharinfo(0)+ "^000000か。";
			mes "メッツから聞いている。";
			next;
			mes "[アーリア]";
			mes "最初の試練は簡単だ。";
			mes "私がこれから教える品を";
			mes "集めてくればいい。";
			next;
			mes "[アーリア]";
			mes "ただし、私が教えた順番通りに";
			mes "持って来い。他のものを同時に";
			mes "持って来たら没収する。";
			next;
			mes "[アーリア]";
			mes "まずは、^FF0000綿毛 100個^000000持ってこい。";
			if(countitem(914) >= 100)
				delitem 914,countitem(914);
			set SIGN_QUE,4;
			close;
		case 3:
			misceffect 49;
			percentheal -50,0;
			mes "[アーリア]";
			mes "…………";
			mes "消えろ。";
			close;
		}
	case 4:
		setarray '@need,914,7033;
		setarray '@amount,100,50;
		break;
	case 5:
		setarray '@need,7033,904;
		setarray '@amount,50,30;
		break;
	case 6:
		setarray '@need,904,930;
		setarray '@amount,30,20;
		break;
	case 7:
		setarray '@need,930,1038;
		setarray '@amount,20,15;
		break;
	case 8:
		setarray '@need,1038,7013;
		setarray '@amount,15,10;
		break;
	case 9:
		set '@need,7013;
		set '@amount,10;
		break;
	case 10:
		mes "[アーリア]";
		mes "…………";
		mes "そこにいる奴と話せ。";
		set SIGN_QUE,11;
		close;
	case 11:
		mes "[アーリア]";
		mes "…………";
		mes "面倒をかけるな。";
		close;
	case 12:
		mes "[アーリア]";
		mes "足りない。";
		mes "もう一回、そこの奴と話して来い。";
		set SIGN_QUE,11;
		close;
	case 13:
		mes "[アーリア]";
		mes "…………";
		mes "いいか……";
		mes "フェイヨンのダイウに会いに行け。";
		if(checkre()) {
			if(BaseLevel >= 90) getexp 1800,0;
			else if(BaseLevel >= 80) getexp 1300,0;
			else if(BaseLevel >= 70) getexp 1000,0;
			else if(BaseLevel >= 60) getexp 750,0;
			else getexp 300,0;
		} else {
			if(BaseLevel >= 90) getexp 18000,0;
			else if(BaseLevel >= 80) getexp 13000,0;
			else if(BaseLevel >= 70) getexp 10000,0;
			else if(BaseLevel >= 60) getexp 7500,0;
			else getexp 3000,0;
		}
		getitem 7177,1;
		set SIGN_QUE,14;
		close;
	case 14:
		mes "[アーリア]";
		mes "…………";
		mes "フェイヨンに行け。";
		close;
	default:
		emotion 9;
		mes "[アーリア]";
		mes "…………";
		mes "面倒をかけるな。";
		close;
	}
	//4～9の続き
	mes "[アーリア]";
	mes "…………";
	if(countitem('@need[0]) < '@amount[0]) {
		mes "^FF0000" +getitemname('@need[0])+ " " +'@amount[0]+ "個^000000だ。";
		close;
	}
	delitem '@need[0],'@amount[0];
	if('@need[1] > 0) {
		if(countitem('@need[1]) >= '@amount[1])
			delitem '@need[1],countitem('@need[1]);
		mes "次は^FF0000" +getitemname('@need[1])+ " " +'@amount[1]+ "^000000だ。";
	}
	else {
		mes "これで全部だ。";
		mes "また後で来い。";
	}
	set SIGN_QUE,SIGN_QUE+1;
	close;
}

morocc_in.gat,114,162,4	script	青年	118,{
	if(SIGN_QUE < 11) {
		emotion 19;
		mes "[ガーナ]";
		mes "最近、暑いよなー！";
		mes "この街は暑くて暑くて大変だよ。";
		mes "暑い以外は良い街なんだけどなー！";
		close;
	}
	if(SIGN_QUE == 12 || SIGN_QUE == 13) {
		mes "[ガーナ]";
		mes "質問は終わりました。";
		mes "結果はお師匠様から聞いてください。";
		close;
	}
	if(SIGN_QUE >= 14) {
		mes "[ガーナ]";
		mes "うーん、もうちょっと";
		mes "涼しかったらいいのになー！";
		mes "我慢するしかないかな～。";
		close;
	}
	mes "[ガーナ]";
	mes "お？　師匠が僕に話せって？";
	mes "どうぞどうぞ！";
	mes "ゆっくりしてって下さい。";
	mes "僕ができることなら、なんでも";
	mes "しますからー！";
	next;
	mes "[ガーナ]";
	mes "えっとですね、これからいくつか";
	mes "質問します。良ーく考えて、答えて";
	mes "くださいね。";
	next;
	mes "[ガーナ]";
	mes "こほん、さて、最初の問題です。";
	mes "…………";
	mes "無人島にたった一人で流れ着きました。";
	mes "一番最初に何をしますか？";
	next;
	switch(select("水を探す","船を待つ","食べ物を探す","島を探検する")) {
		case 1: set '@point,'@point+7; break;
		case 2: set '@point,'@point+1; break;
		case 3: set '@point,'@point+4; break;
		case 4: set '@point,'@point+10; break;
	}
	mes "[ガーナ]";
	mes "二番目の質問です。";
	mes "…………";
	mes "大きい建物が急に崩れて、とても狭い";
	mes "場所に閉じ込められてしまいました。";
	mes "そんな時、なにをしますか？";
	next;
	switch(select("大声で助けてーと叫ぶ","じっとしている","死を覚悟する","外に出る方法を探す")) {
		case 1: set '@point,'@point+3; break;
		case 2: set '@point,'@point+7; break;
		case 3: set '@point,'@point+1; break;
		case 4: set '@point,'@point+7; break;
	}
	mes "[ガーナ]";
	mes "三番目の質問です。";
	mes "…………";
	mes "あなたはダンジョンで、仲間とはぐれて";
	mes "迷子になってしまいました。";
	mes "さぁ、どうします？";
	next;
	switch(select("仲間を探し回る","外に出る方法を探す","じっとしている","一人でダンジョンを回る")) {
		case 1: set '@point,'@point+0; break;
		case 2: set '@point,'@point+5; break;
		case 3: set '@point,'@point+10; break;
		case 4: set '@point,'@point+1; break;
	}
	mes "[ガーナ]";
	mes "四番目の質問です。";
	mes "…………";
	mes "あなたは、外と連絡が取れない状況で、";
	mes "ある館に仲間と閉じ込められて";
	mes "しまいました。そんな中、殺人事件が！";
	mes "どうしますか？";
	next;
	switch(select("事件が解決されるのを待つ","仲間が全員いるか確かめる","外と連絡を取る方法を探す","自ら事件を解決する","自分が殺される前にいっそ仲間を……")) {
		case 1: set '@point,'@point+7; break;
		case 2: set '@point,'@point+5; break;
		case 3: set '@point,'@point+3; break;
		case 4: set '@point,'@point+1; break;
		case 5: set '@point,'@point+1; break;
	}
	mes "[ガーナ]";
	mes "五番目の質問です。";
	mes "…………";
	mes "一週間後に、世界が滅亡するとします。";
	mes "それまでの一週間、何をしますか？";
	next;
	switch(select("大人しく滅亡を待つ","木をいっぱい植える","他の世界へ移住する方法を考える","残った時間で世界を探検する","悪いことをしてみる")) {
		case 1: set '@point,'@point+5; break;
		case 2: set '@point,'@point+3; break;
		case 3: set '@point,'@point+7; break;
		case 4: set '@point,'@point+10; break;
		case 5: set '@point,'@point+1; break;
	}
	mes "[ガーナ]";
	mes "ふむふむ、ちょっと失礼……";
	mes "おし、これでOK。";
	mes "結果は師匠に聞いてください。";
	mes "ではー！";
	if('@point > 33)
		set SIGN_QUE,13;
	else
		set SIGN_QUE,12;
	close;
}

//============================================================
// 第1部 - ダイウの試練
//------------------------------------------------------------
payon_in03.gat,11,31,4	script	ダイウ	808,{
	mes "[ダイウ]";
	mes "わっはっはっはーっ!!";
	mes "肉を持ってこい！";
	mes "楽を奏でろ!!";
	mes "フハハハハハッハッハッ!!";
	next;
	mes "[ダイウ]";
	mes "世界中の珍味！";
	mes "世界中の美女!!";
	mes "世界を手に入れたも同然!!!!";
	mes "ハハハハハハ！";
	next;
	if(SIGN_QUE == 15) {
		mes "[ダイウ]";
		mes "こんな所で何をしている？";
		mes "ん、行き先を忘れたか？";
		mes "何を聞いていたんだ、お前は。";
		mes "アルデバランの^CE0000ヨルニム^000000だ。";
		mes "さぁ、走れ！";
		next;
		mes "[ダイウ]";
		mes "肝っ玉の小さい奴だから、きっと";
		mes "人気の少ない場所でひっそりと";
		mes "暮らしてるだろうさ。";
		close;
	}
	if(SIGN_QUE > 15) {
		mes "[ダイウ]";
		mes "ああ、食った食った……";
		mes "これだけ食べたら、さすがに";
		mes "眠くなってきたぞ。";
		next;
		mes "[ダイウ]";
		mes "ゴートが一匹、ゴートが……";
		mes "……z……zz……ZZ";
		close;
	}
	mes "[ダイウ]";
	mes "何だ、若造。";
	mes "羨ましいか？";
	mes "羨ましいなら、偉くなってみろ！";
	mes "ハーッハッハハハハ！";
	if(SIGN_QUE < 14)
		close;
	next;
	mes "[ダイウ]";
	mes "あぁん？";
	mes "何か言いたいことでもあるのか？";
	mes "ないなら、とっとと消えな。";
	if(Sex) {
		mes "男が俺の前でふらふらするな。";
		mes "気持ち悪い。";
	}
	else {
		mes "それとも、お前もここに来て";
		mes "一緒に一杯やるか？";
	}
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "いえ、これを見てくれませんか？";
	next;
	mes "^3355FF-あなたは懐から、";
	mes "清らかな光を発する";
	mes "小さな宝石を取り出した-^000000";
	next;
	emotion 0;
	mes "[ダイウ]";
	mes "なんだと？";
	mes "そ、それは……";
	next;
	mes "[ダイウ]";
	mes "それは、アーリアの！";
	mes "そんなことなら、早く言え！";
	mes "お前も、『ダイウ様ダイウ様";
	mes "サインください～』と追い回す、";
	mes "俺の追っかけかと思って、";
	mes "追い出すところだったじゃないか！";
	next;
	mes "[ダイウ]";
	mes "お前、それがなんだか知っているのか？";
	next;
	switch(select("はい、知っています","それが私と関係あるんですか？","わからないので教えてくれませんか？")) {
	case 1:
		mes "[ダイウ]";
		mes "ほう、思ったより博識だな。";
		mes "そうか。では、それは何だ？";
		next;
		if(select("……とても良い物です","実はわからないんです。てへ。")==1) {
			emotion 9;
			mes "[ダイウ]";
			mes "なんだ、その適当な返事は！";
			mes "俺はそういう、曖昧にごまかそうとする";
			mes "奴は大嫌いだ！";
			set '@point,'@point+2;
		}
		else {
			emotion 32;
			mes "[ダイウ]";
			mes "……";
			mes "頭が痛い……";
			set '@point,'@point+4;
		}
		break;
	case 2:
		emotion 9;
		mes "[ダイウ]";
		mes "…………";
		next;
		mes "[ダイウ]";
		mes "お前は、どうしてこんな苦労をしてまで";
		mes "試練を受けなければならないか、";
		mes "理解していないようだな。";
		break;
	case 3:
		mes "[ダイウ]";
		mes "アーリアは説明しなかったのか？";
		mes "まあいい。俺が説明してやる。";
		mes "下手に知ったかぶりするより、";
		mes "知らないなら知らないと言う奴のほうが";
		mes "素直でいいわい！";
		if(checkre())
			getexp 0,0;
		else
			getexp 5,0;
		set '@point,'@point+5;
		break;
	}
	next;
	mes "[ダイウ]";
	mes "お前が持っているそれは、";
	mes "^31009Cスタージュエルのかけら^000000と言う。";
	mes "それは、普通の品物じゃない。";
	mes "新しい力を秘めた、かなりいわくつきの";
	mes "もんだ。";
	next;
	mes "[ダイウ]";
	mes "メッツが偶然手に入れたもんだが、";
	mes "それ以外は知らん。";
	next;
	mes "[ダイウ]";
	mes "メッツは仲間に、その新しい力に";
	mes "相応しい人物を探してくれと頼んだ。";
	mes "そう、旅と試練に立派に耐えられる";
	mes "人物をな。";
	next;
	mes "[ダイウ]";
	mes "それで俺達はそれぞれ、世界中に";
	mes "散らばり、メッツの紹介で来た奴等を";
	mes "試すことにしたのさ。";
	next;
	switch(select("私がズバリ！適任者です","よろしくお願いします！","はぁ……","そうですか")) {
	case 1:
		mes "[ダイウ]";
		mes "あー？";
		mes "その自信はどこから出てるんだ。";
		mes "ま、俺のように旅で疲れた仲間を癒せる";
		mes "才色兼備のダンディーな男には";
		mes "及ばないが、お前も悪くはないな。";
		set '@point,'@point+5;
		break;
	case 2:
		emotion 33;
		mes "[ダイウ]";
		mes "おう！　いいね、その心意気!!";
		mes "そういう心こそ、大事なんだ。";
		mes "可愛いじゃねぇか、こいつ……";
		mes "よし、俺が" +(Sex? "綺麗な嫁さんでも": "ピッタリの旦那を");
		mes "見つけてやるか！";
		set '@point,'@point+7;
		break;
	case 3:
		emotion 6;
		mes "[ダイウ]";
		mes "「はぁ……」だとっ?!";
		next;
		emotion 7;
		mes "[ダイウ]";
		mes "そんなたるんだ精神で何ができる！";
		mes "このバカやろう！";
		percentheal -10,0;
		set '@point,'@point+2;
		break;
	case 4:
		emotion 9;
		mes "[ダイウ]";
		mes "…………";
		next;
		mes "[ダイウ]";
		mes "……アーリアみたいに無気力で";
		mes "美しくないヤロウだな。";
		mes "俺は夢のない奴は嫌いだね。";
		set '@point,'@point+4;
		break;
	}
	next;
	mes "[ダイウ]";
	mes "……お前とはもうちょっと話し合う";
	mes "必要があるな。";
	mes "いいか、コミュニケーションってのは";
	mes "大事なんだぜ。";
	next;
	emotion 20;
	mes "[ダイウ]";
	mes "メッツから、シビアな質問も";
	mes "しといてくれって頼まれてるし……";
	mes "ま、悪く思うな。";
	next;
	mes "[ダイウ]";
	mes "友達はいるか？";
	mes "一緒によくパーティーを";
	mes "組んだりする友達だ。";
	next;
	switch(select("はい","1人でいる時が好きです","友達なんていません")) {
	case 1:
		emotion 23;
		mes "[ダイウ]";
		mes "この、幸せモン！";
		mes "人ってのはな、母ちゃんの腹の中に";
		mes "いる時が一番幸せなんだとよ。";
		mes "その後は、出会う人次第ってな。";
		next;
		mes "[ダイウ]";
		mes "肉体的とか、精神的とかじゃねぇ。";
		mes "^3355FF仲間^000000は大きな力だって忘れるなよ！";
		set '@point,'@point+5;
		break;
	case 2:
		mes "[ダイウ]";
		mes "まぁな～。1人になりたい時だって";
		mes "あるさ……。でもな、孤独ってのは";
		mes "苦しいもんさ。そういう時に、";
		mes "自分自身と戦い、勝ち、旅立つのも";
		mes "重要だがな。";
		next;
		mes "[ダイウ]";
		mes "ただ、自分に縛られるなよ。";
		mes "普段自分だけを見て、他人を";
		mes "軽視する奴は捨てられるもんだぜ。";
		mes "もっと色んな人と会ってみな。";
		mes "どんな平凡な経験だって、自分の";
		mes "肥やしになるんだぜ。";
		set '@point,'@point+4;
		break;
	case 3:
		mes "[ダイウ]";
		mes "……その年で友達が1人も";
		mes "いないってのか？";
		mes "どんな生活してきたんだ……ブツブツ。";
		mes "もう一度、人生振り返ってみたら";
		mes "どうよ？　俺みたいに堂々とした奴の";
		mes "周りには、自然と人が集まるもんさ。";
		set '@point,'@point+3;
		break;
	}
	next;
	mes "[ダイウ]";
	mes "最近人々の中で話題になっている";
	mes "のは、ある人物がたくさんの";
	mes "モンスターを引き連れて色んな";
	mes "場所に出没するっていう事件に";
	mes "ついてだ。";
	mes "お前はどう思う？";
	next;
	switch(select("本当に怖いですよね！","我慢できません！","そんなこともあるでしょう。")) {
	case 1:
		emotion 9;
		mes "[ダイウ]";
		mes "…………";
		next;
		emotion 9;
		mes "[ダイウ]";
		mes "…………";
		next;
		emotion 6;
		mes "[ダイウ]";
		mes "性根が腐ってやがるな。";
		next;
		emotion 6;
		mes "[ダイウ]";
		mes "大変だとわめいて";
		mes "怖がっているばかりか！";
		next;
		emotion 6;
		mes "[ダイウ]";
		mes "お前が生きていく道ってのは";
		mes "そんなものなのか？";
		next;
		emotion 6;
		mes "[ダイウ]";
		mes "人々が後ろであざけり";
		mes "笑う様が目に浮かぶぞ……。";
		next;
		mes "[ダイウ]";
		mes "くっ……";
		break;
	case 2:
		mes "[ダイウ]";
		mes "おう！　俺もそう思う!!";
		next;
		mes "[ダイウ]";
		mes "不届きなやつらめ……";
		mes "中にはそれが自慢だと";
		mes "気取っているやつらもいる。";
		mes "根性から腐ってやがる！";
		next;
		emotion 6;
		mes "[ダイウ]";
		mes "ウォー!!!";
		next;
		mes "[ダイウ]";
		mes "ちょっと興奮してしまった……";
		next;
		emotion 21;
		mes "[ダイウ]";
		mes "お前もこれから難しい出来事に";
		mes "出会っても、その心に信念を";
		mes "持ち続けることを";
		mes "決して忘れないでほしい。";
		set '@point,'@point+5;
		break;
	case 3:
		mes "[ダイウ]";
		mes "こいつ！";
		mes "信念も何も無いのか！";
		mes "生きて……成長していくのが";
		mes "生易しいことじゃないこと";
		mes "くらいはわかるだろう？";
		next;
		mes "[ダイウ]";
		mes "大変な人生だからこそ、";
		mes "価値があり、そして輝くって";
		mes "ものなんだ。";
		next;
		mes "[ダイウ]";
		mes "大変でもじっと耐えて";
		mes "生きていくうちに、";
		mes "強く成長している自分に";
		mes "気づくこともあるだろう。";
		next;
		mes "[ダイウ]";
		mes "二度とそんな適当なことを";
		mes "言わないでくれよな？";
		set '@point,'@point+3;
		break;
	}
	next;
	mes "[ダイウ]";
	mes "最近、攻城戦が盛んらしいな。";
	next;
	mes "[ダイウ]";
	mes "緊迫した状況で、一緒に汗を流し、";
	mes "同じ空気を吸う!!";
	next;
	mes "[ダイウ]";
	mes "鋭い金属音が響き、魔法が風を揺さぶり";
	mes "麗しいプリーストの姉ちゃん達が……";
	mes "ご、ごほ、ごほ、あ、いや、何……";
	next;
	emotion 9;
	mes "[ダイウ]";
	mes "とにかく、男のロマンがある……";
	mes "ふっ……";
	next;
	mes "[ダイウ]";
	mes "では質問だ!!";
	mes "攻城戦の心臓とも言えるエンペリウムが";
	mes "今のような形ではなく、麗しい女性の";
	mes "聖像だったら、お前はどうする!!";
	next;
	switch(select("どんな形だろうと壊す","絶対に壊せない","目をつぶって壊す")) {
	case 1:
		mes "[ダイウ]";
		mes "ほう、強いな。";
		if(Sex) {
			mes "男が女をイジメるのは";
			mes "好きじゃないがな。";
		}
		else
			mes "あ、女にする質問じゃなかったか。";
		set '@point,'@point+3;
		break;
	case 2:
		mes "[ダイウ]";
		mes "ハッハッハ!!　やはりそうか。";
		mes "正しい者は、美しいものを";
		mes "守らねばならない!!";
		next;
		mes "[ダイウ]";
		mes "美しいものを、どうして自ら";
		mes "壊せようか～！";
		set '@point,'@point+5;
		break;
	case 3:
		mes "[ダイウ]";
		mes "何かを得るために、何かを";
		mes "犠牲にする……か。";
		mes "いいね。";
		set '@point,'@point+6;
		break;
	}
	next;
	mes "[ダイウ]";
	mes "俺なら、時間切れになるまで、";
	mes "そのエンペリウムを守りぬいただろう！";
	mes "ウハハハハハハ!!!!";
	next;
	mes "[ダイウ]";
	mes "今度はギルドに関する質問だ。";
	next;
	mes "[ダイウ]";
	mes "例えば、お前が誰もが知っている";
	mes "有名ギルドに入ったとしよう。";
	next;
	mes "[ダイウ]";
	mes "そして、そのギルドには、";
	mes "これまた有名な敵対ギルドがいる。";
	mes "この二つのギルドの動向は、けっこう";
	mes "注目されていると、付け加えておこう。";
	next;
	mes "[ダイウ]";
	mes "さて。お前がいつものように狩りを";
	mes "していると、ある人物と偶然出会った。";
	mes "そいつは、敵対ギルドの中心人物だ。";
	next;
	mes "[ダイウ]";
	mes "周りには、お前とそいつ以外誰も";
	mes "いない。そして、相手は何かとても";
	mes "困っているらしく、助けてくれないかと";
	mes "言ってきた。";
	next;
	mes "[ダイウ]";
	mes "さぁ、お前はどうする？";
	next;
	switch(select("手伝う","無視する","逃げる")) {
	case 1:
		mes "[ダイウ]";
		mes "敵でも手伝うか。わっはっは!!";
		mes "まぁ、助けあったりすると、";
		mes "ギスギスした関係が良くなったりも";
		mes "するしな。";
		mes "お前の考えはわかって来たぜ。";
		set '@point,'@point+6;
		break;
	case 2:
		mes "[ダイウ]";
		mes "まぁ確かに、手伝う必要があるかどうか";
		mes "判らんからな。敵対関係ってのもあるし";
		mes "ま、仕方ないって面もあるか。";
		mes "お前の考えはわかって来たぜ。";
		set '@point,'@point+5;
		break;
	case 3:
		mes "[ダイウ]";
		mes "……情けねぇな。";
		mes "そういう行動のせいで、敵対関係が";
		mes "より一層激しくなるってことも";
		mes "あるんだぜ。";
		mes "お前の考えはわかって来たぜ。";
		set '@point,'@point+4;
		break;
	}
	next;
	mes "[ダイウ]";
	mes "さて、最後の質問だ。";
	next;
	mes "[ダイウ]";
	mes "今の生活、楽しいか？";
	next;
	if(select("はい","いいえ")==1) {
		mes "[ダイウ]";
		mes "そうか、よかったな。";
		mes "日常ってのは、繰り返しのほうが多いし";
		mes "気がつけば同じ場所を回っているような";
		mes "空しさを感じる時だってある。";
		next;
		mes "[ダイウ]";
		mes "いつでも余裕を忘れず、楽しい心で";
		mes "暮らせよ。俺は綺麗な女と肉があれば";
		mes "言うことねぇ!!　最高の人生だ!!";
		mes "わーっはっはっはっは!!!!";
	}
	else {
		mes "[ダイウ]";
		mes "そうなのか……";
		mes "まぁ、腹が立ったりもするし、毎日";
		mes "同じようなことを繰り返してりゃ、";
		mes "空しく感じる時だってあるだろうな。";
		next;
		mes "[ダイウ]";
		mes "なんでも最初は楽しくても、";
		mes "徐々に気持ちなんてのは変わってく。";
		next;
		mes "[ダイウ]";
		mes "だがな！";
		mes "初心忘れるべからずだ！";
		mes "初心、すなわち「初めの心」!!";
		mes "俺は、その言葉は大事だと思う!!";
		next;
		mes "[ダイウ]";
		mes "初心を忘れれば、人は変わる。";
		mes "今まで一生懸命、人生って道を";
		mes "走って来たのはわかるさ。";
		next;
		mes "[ダイウ]";
		mes "だがな、ちょっと立ち止まって、";
		mes "自分が走ってきた道を見直してみたら";
		mes "どうだい？　自分が忘れちまったものが";
		mes "何か、見えてくるかも知れないぜ。";
		next;
		emotion 21;
		mes "[ダイウ]";
		mes "おっと、俺らしくねぇ。";
		mes "俺のモットーは才色兼備な";
		mes "おしゃれ男なのによ。フッ……。";
	}
	next;
	mes "[ダイウ]";
	mes "おし、じゃあ俺から見た";
	mes "お前の評価だ。";
	next;
	mes "[ダイウ]";
	mes "……………………";
	next;
	if('@point < 20) {
		mes "[ダイウ]";
		mes "うん、残念だ。";
		mes "どうしてもお前は気に食わん。";
		mes "自分に足りないものはなんなのか、";
		mes "良く考え直してみることだな。";
		close;
	}
	if('@point < 27) {
		mes "[ダイウ]";
		mes "うーん……";
		mes "何かが足りない！";
		mes "そんな奴は追試だ!!!";
		close;
	}
	set SIGN_QUE,15;
	getitem 7177,1;
	if(checkre()) {
		if(BaseLevel >= 90) getexp 1800,0;
		else if(BaseLevel >= 80) getexp 1300,0;
		else if(BaseLevel >= 70) getexp 1000,0;
		else if(BaseLevel >= 60) getexp 700,0;
		else getexp 300,0;
	}
	else {
		if(BaseLevel >= 90) getexp 18000,0;
		else if(BaseLevel >= 80) getexp 13000,0;
		else if(BaseLevel >= 70) getexp 10000,0;
		else if(BaseLevel >= 60) getexp 7000,0;
		else getexp 3000,0;
	}
	if('@point < 30) {
		mes "[ダイウ]";
		mes "ふむ、まぁ悪くはないか。";
		mes "合格としよう。";
	}
	else {
		emotion 18;
		mes "[ダイウ]";
		mes "おめでとう！";
		mes "俺はお前が気に入った!!";
		mes "お前、本当に俺と似てるな。";
		mes "ハハハ、光栄だろう！";
		next;
		mes "[ダイウ]";
		mes "残りのテストも、頑張れよ。";
		mes "なに、お前ならきっとできるさ。";
	}
	next;
	mes "[ダイウ]";
	mes "次はアルデバランの";
	mes "^CE0000ヨルニム^000000を訪ねるといい。";
	mes "ちょっとひ弱だが、良い奴だ。";
	mes "特に、研究に対する心は熱い！";
	next;
	mes "[ダイウ]";
	mes "じゃあ、がんばれよー！";
	next;
	mes "[ダイウ]";
	mes "………";
	next;
	emotion 3;
	mes "[ダイウ]";
	mes "よし、カプラサービスに連絡だ。";
	close;
}

payon.gat,154,170,3	script	ハシン	78,{
	mes "[ハシン]";
	mes "あ～ん♪　彼ってばなんて";
	mes "おしゃれなのかしら～。";
	next;
	mes "[ハシン]";
	mes "小さい頃はあんなにワンパクだったのに";
	mes "いつの間に、あ～んなに素敵になって。";
	next;
	mes "[ハシン]";
	mes "ルックスなんて抜群で、性格も";
	mes "ウフ♪だから、あんなにたくさんの";
	mes "女性が彼のもとに集まるのは";
	mes "当たり前だと思わない？";
	next;
	mes "[ハシン]";
	mes "あ～あ～、幼馴染みのこの私も";
	mes "誘惑してくれないかしら、はぁ……";
	next;
	if(select("そのハンサムさんはどこですか？","美しさは罪だね～")==2) {
		emotion 6;
		mes "[ハシン]";
		mes "あらやだ～。";
		mes "私だって若い時は凄かったのよ。";
		mes "もう、何言わせるのよー！";
		close;
	}
	mes "[ハシン]";
	mes "フェイヨン一、ハンサムなダイウ様？";
	next;
	mes "[ハシン]";
	mes "ダイウ様は、ちょうど声変わりする前";
	mes "だったかしら。強くなってくると";
	mes "町を去ったんだけど、あんなに壮健で";
	mes "素敵になって帰ってくるなんて……";
	next;
	menu "ダイウ様はどこですか？",-;
	mes "[ハシン]";
	mes "えっと……";
	if(Sex) {
		mes "そうね。あなたもダイウ様に会って、";
		mes "真の男ってものを学ぶといいわ。";
	}
	else {
		mes "あなたも、私達のダイウ様の";
		mes "噂を聞いてきたのね～。";
		next;
		mes "[ハシン]";
		mes "人気がありすぎて困っちゃう～。";
	}
	next;
	mes "[ハシン]";
	mes "ダイウ様は、この町の北にあるお屋敷に";
	mes "いらっしゃるわ。";
	close;
}

payon_in03.gat,13,31,4	script	下女	1416,{}
payon_in03.gat,13,31,0	script	下女	111,{
	mes "[下女]";
	mes "ダイウ様、こちらも是非召し上がって";
	mes "くださいませ。これは、体に良い";
	mes "九つの薬草と虎の足の裏を煎じ、";
	mes "5時間じっくり煮込んだもので";
	mes "ございます。";
	next;
	mes "[下女]";
	mes "長旅の疲れが吹き飛び、さらに、";
	mes "風邪の予防、そして弱い骨を";
	mes "強くしてくれますわ。";
	mes "はい、あ～ん。";
	close;
}

payon_in03.gat,8,31,4	script	下女	1416,{}
payon_in03.gat,8,31,0	script	下女	111,{
	mes "[下女]";
	mes "この離宮の下女達が、どこかで";
	mes "見たことがある姿でも、弓や刀で";
	mes "傷つけようとしてはなりません。";
	next;
	mes "[下女]";
	mes "私達は、ダイウ様の趣向により、";
	mes "このような衣装に身を包んでいるだけで";
	mes "ございます。ですので、どうか武器は";
	mes "お納めください。";
	close;
}

payon_in03.gat,81,22,4	script	下女	1170,{}
payon_in03.gat,81,22,0	script	下女#sign	111,{
	mes "[下女]";
	mes "いらっしゃいませ、";
	mes "ここはダイウ様がお暮らしの";
	mes "フェイヨン離宮です。";
	close;
}
payon_in03.gat,81,15,0	script	下女	1170,{}
payon_in03.gat,81,15,0	duplicate(下女#sign)	下女	111
payon_in03.gat,79,22,4	script	下女	1404,{}
payon_in03.gat,79,22,0	duplicate(下女#sign)	下女	111
payon_in03.gat,79,15,0	script	下女	1404,{}
payon_in03.gat,79,15,0	duplicate(下女#sign)	下女	111

//============================================================
// 第1部 - ヨルニムの試練
//------------------------------------------------------------
aldeba_in.gat,155,101,3	script	ヨルニム	805,7,7,{
	if(gettime(3) >= 6) && (gettime(3) < 17) {
		mes "^0063FF-雑に本が散らばっている中、";
		mes "男が1人、手に試験管を持ったまま";
		mes "苦難の表情を浮かべている-";
		mes "-どうしよう？-^000000";
		next;
		if(select("声をかけてみる","放っておく")==1) {
			mes "[" +strcharinfo(0)+ "]";
			mes "あの…………";
			next;
			mes "[ヨルニム]";
			mes "………………";
			next;
			mes "^0063FF-自分の実験に集中するあまり";
			mes "こちらの声が聞こえていないようだ-^000000";
			next;
			if(select("もう一度声をかけてみる","放っておく")==1) {
				mes "[" +strcharinfo(0)+ "]";
				mes "失礼しまーーーす!!";
				next;
				mes "[ヨルニム]";
				mes "……!!";
				mes "あ……こんにちは……";
				mes "……申し訳ありませんが、今はちょっと";
				mes "手が放せないので……午後5時以降に、";
				mes "また来てください……";
				next;
				mes "[ヨルニム]";
				mes "……こうだから……これを……よし。";
				mes "……これでもないか……";
				mes "それでは、またもう一度……";
				close;
			}
		}
		mes "^0063FF-一瞬、声をかけようと思ったが";
		mes "また出直すことにした-";
		mes "-部屋の中で、彼が低くつぶやく声と";
		mes "試験管が軽くぶつかる音が響いた-^000000";
		close;
	}
	if(gettime(3) < 6) || (gettime(3) >= 22) {
		mes "[ヨルニム]";
		mes "……z……zz……Z";
		close;
	}
	if(SIGN_QUE < 15) {
		mes "[ヨルニム]";
		mes "ああ…………";
		mes "神は本当に素晴らしい。";
		mes "無から有を作り出す……";
		mes "生命誕生と、その奥深さ……";
		mes "まさに神秘だ……";
		next;
		mes "[ヨルニム]";
		mes "私は単なる学者にすぎませんが、";
		mes "うーん…………";
		mes "努力あるのみです……";
		mes "神への領域に挑戦……";
		mes "……罰を受けてしまうでしょうか？";
		next;
		mes "[ヨルニム]";
		mes "自信は……ありません……";
		mes "でも、私は信じています。";
		mes "この世の全てが、特定の条件によって、";
		mes "その形態を成しているのだと……";
		next;
		mes "[ヨルニム]";
		mes "生命の誕生も同じ……";
		mes "いつかはその秘密が…………";
		mes "必ず明かされるのです。";
		mes "その時……人はもっと偉い種族と";
		mes "なれるのでしょうか？";
		close;
	}
	switch(SIGN_QUE) {
	case 15:
		mes "[" +strcharinfo(0)+ "]";
		mes "あ……";
		next;
		emotion 23;
		mes "^313FFF-ガチャン-^000000";
		next;
		mes "[ヨルニム]";
		mes "……………………";
		next;
		emotion 19;
		mes "[ヨルニム]";
		mes "……………………";
		next;
		emotion 28;
		mes "[ヨルニム]";
		mes "ああ…………";
		mes "5時間かけて増やしたのに、";
		mes "こんなことに……";
		mes "しくしく……";
		next;
		emotion 28;
		mes "[ヨルニム]";
		mes "しくしく……何か用ですか……";
		mes "静かに研究できると思って、ここに";
		mes "研究所を作ったのに……ああ……";
		next;
		if(select("ダイウさんの紹介で来ました","申し訳ありません……")==2) {
			emotion 28;
			mes "[ヨルニム]";
			mes "しくしく…………";
			mes "また5時間……";
			close;
		}
		emotion 4;
		mes "[ヨルニム]";
		mes "あ……";
		mes "そうなんですか……！";
		mes "そういえばそんな頼みを";
		mes "受けましたっけ……";
		next;
		emotion 19;
		mes "[ヨルニム]";
		mes "ああっ、それで……お名前は……？";
		next;
		menu strcharinfo(0)+ "と言います",-;
		mes "[ヨルニム]";
		mes "あ……";
		mes strcharinfo(0);
		mes "さんですか。";
		mes "私はヨルニムです……";
		mes "研究が好きな平凡な学者です……";
		next;
		mes "[ヨルニム]";
		mes "メッツさんの頼みも断ろうと";
		mes "思ったんですが……";
		mes "その、ようこそ。";
		next;
		mes "[ヨルニム]";
		mes "あ……" +strcharinfo(0)+ "さんが";
		mes "いらしたと言うことは";
		mes "これからはもっと沢山の人が、ここに";
		mes "来るようになるという事ですね。";
		next;
		mes "[ヨルニム]";
		mes "ああ……";
		mes "私の研究は……しくしく……";
		mes "メッツさん……";
		next;
		mes "[ヨルニム]";
		mes "うう……";
		mes "約束ですから仕方ないです……";
		mes "先ほど、あなたが急に";
		mes "声をかけたせいで、私の重要な";
		mes "研究サンプルが割れてしまいました。";
		mes "まずは、その弁償からお願いします。";
		next;
		mes "[ヨルニム]";
		mes "そ……そんなに睨まないでくださいよ！";
		mes "あれはとっても大事なサンプル";
		mes "だったんです！";
		next;
		mes "[ヨルニム]";
		mes "そ、それでですね……";
		mes "空の試験管 10個";
		mes "イグドラシルの葉 2個";
		mes "緑ハーブ 10個";
		mes "簡単でしょ……ハハ……";
		next;
		mes "[ヨルニム]";
		mes "最近、生命工学の研究をしてまして。";
		mes "神のように、無から有を創造……";
		mes "不思議な性能を発揮する";
		mes "イグドラシルの葉に、その秘密が";
		mes "隠されていないかと思って……";
		next;
		emotion 4;
		mes "[ヨルニム]";
		mes "それではお願いいたします……";
		mes "あ、そうだ……あの、実は……";
		mes "私……夜10時になると、プツリと";
		mes "電池が切れたみたいに";
		mes "眠っちゃうんです……なので、";
		mes "10時前にいらしてください……";
		set SIGN_QUE,16;
		close;
	case 16:
		if(countitem(1092) < 10 || countitem(610) < 2 || countitem(511) < 10) {
			mes "[ヨルニム]";
			mes "……また教えるんですか？";
			mes "空の試験管 10個";
			mes "イグドラシルの葉 2個";
			mes "緑ハーブ 10個です……";
			mes "そ、そんな怖い顔しないでも……";
			mes "頼みます……ウウ……";
			close;
		}
		delitem 1092,10;
		delitem 610,2;
		delitem 511,10;
		emotion 15;
		mes "[ヨルニム]";
		mes "あああああ、ありがとうございます……";
		mes "これでまた研究を続けられます";
		next;
		mes "[ヨルニム]";
		mes "そ……それでは試練の方を……";
		next;
		mes "[ヨルニム]";
		mes strcharinfo(0)+ "さんは、";
		mes "^CE3131賢者の石^000000をご存知ですか？";
		next;
		mes "[ヨルニム]";
		mes "私達研究者の間で、こと秘密裏に";
		mes "語られている石です。実際、その";
		mes "存在可否については、誰も詳しいことは";
		mes "知りません……";
		next;
		mes "[ヨルニム]";
		mes "^CE3131賢者の石^000000が何かは、";
		mes "私もよく知りません……";
		mes "ただ、本能的に感じるのです……";
		mes "それさえあれば、停滞している";
		mes "この実験も……なにか、こう光を";
		mes "見ることができるのではないかと……";
		next;
		mes "[ヨルニム]";
		mes "そこで……！";
		mes "^CE3131賢者の石^000000について";
		mes "調査をお願いします！";
		next;
		mes "[ヨルニム]";
		mes "噂によると、過去に名を馳せた";
		mes "あるアルケミストの女性が何か";
		mes "知っているとのこと。ただ、その方は";
		mes "ある日、地位と名声を捨て、";
		mes "迷宮のような深い森に";
		mes "消えてしまったと言われています。";
		next;
		mes "[ヨルニム]";
		mes "その女性に会うことができれば、";
		mes "賢者の石について何らかの";
		mes "情報を得られるはずです。";
		mes "彼女を探してください。";
		mes "それでは、お願いしましたよ。";
		set SIGN_QUE,17;
		close;
	case 17:
	case 18:
		mes "[ヨルニム]";
		mes "賢者の石に関する情報はまだですか？";
		close;
	case 19:
		mes "[ヨルニム]";
		mes "ああ……おかえりなさい！";
		mes "それで、賢者の石について、";
		mes "何かわかりましたか？";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "それが、ほとんど何もわかりません";
		mes "でした。ただ、賢者の石は赤い色を";
		mes "しているとか、不老不死の薬だという";
		mes "話を聞きました。";
		mes "つまり、強い魔力を持つ石なんだと";
		mes "思います。";
		next;
		mes "[ヨルニム]";
		mes "やはり、ただの噂に過ぎなかったと";
		mes "いうことでしょうか……。";
		mes "でも、今の話だと、賢者の石に";
		mes "近い存在が、身近にあったような……";
		mes "なんだったっけ……";
		mes "あなた、何か心当たりはありませんか？";
		next;
		input '@word$;
		if('@word$ != "イエロージェムストーン" && '@word$ != "レッドジェムストーン" && '@sign_word$ != "ブルージェムストーン") {
			mes "[ヨルニム]";
			mes "うーん、違うと思いますよ……";
			close;
		}
		mes "[ヨルニム]";
		mes "……ああ、そうですね。";
		mes "確かに、近い存在かもしれません……";
		mes "確信はありませんが……";
		next;
		mes "[ヨルニム]";
		mes "はい、よくわかりました……";
		mes "賢者の石については、このまま忘れて、";
		mes "自分の研究に専念したいと思います……";
		mes "噂に頼ろうとしていた自分が、";
		mes "今となっては恥ずかしくて……";
		mes "しくしく……";
		next;
		set SIGN_QUE,20;
		getitem 7177,1;
		mes "[ヨルニム]";
		mes "お疲れ様です……";
		mes "では、これを差し上げます。";
		mes "私はまた研究に戻るとします……";
		mes "アア……これで訪ねてくる人が";
		mes "減ってくれればいいのにな……";
		next;
		mes "[ヨルニム]";
		mes "次は、魔法の都市にいらっしゃる";
		mes "^0063FFジスクリエ^000000様を";
		mes "訪ねてください……";
		next;
		mes "[ヨルニム]";
		mes "彼女は1ヶ所にとどまる性格では";
		mes "ないし、友人が多そうなので、";
		mes "旅館のような場所に厄介になっていると";
		mes "思います。それでは……";
		close;
	case 20:
		mes "[ヨルニム]";
		mes "次は、魔法の都市にいらっしゃる";
		mes "^0063FFジスクリエ^000000様を";
		mes "訪ねてください……";
		close;
	default:
		mes "[ヨルニム]";
		mes "ああ……こうでもないし……";
		mes "こうすると……あああ!!";
		mes "こっちでもなかった……";
		mes "しくしく……どうしよう……";
		close;
	}
OnTouch:
	if(rand(2)) {
		emotion 5;
		misceffect 305;
	}
	else {
		emotion 23;
		misceffect 306;
	}
	end;
}

aldeba_in.gat,156,118,4	script	ピルピル	102,{
	if(gettime(3) >= 6 && gettime(3) < 12) {
		mes "[ピルピル]";
		mes "今日も頑張って研究研究～";
		mes "朝から熱心に実験実験～";
		next;
		mes "[ピルピル]";
		mes "この研究室には、僕とお師匠様しか";
		mes "いませんが、健康維持のため、";
		mes "絶対に守っている規則があります。";
		next;
		mes "[ピルピル]";
		mes "午前10時から、午後5時まで";
		mes "研究に専念。";
		mes "自由時間は5時以降です。";
		mes "お師匠様は、夜10時まで研究して、";
		mes "そのまま寝てしまいますけどね。";
		next;
		mes "[ピルピル]";
		mes "だから、研究以外の用でしたら";
		mes "5時を過ぎてから訪ねてきてください。";
		close;
	}
	if(gettime(3) < 6) {
		mes "[ピルピル]";
		mes "……クウ……グウ……";
		mes "フニャ……ムニャ……";
		next;
		if(select("起こす","やめる")==2) {
			mes "[ピルピル]";
			mes "ムニャ……グー……";
			close;
		}
		mes "[ピルピル]";
		mes "…………";
		mes "疲れてるんだー！";
		mes "10時まで寝かせろー！";
		mes "ワァー!!!　キャアアアアッ!!!!";
		close;
	}
	emotion 28;
	mes "[ピルピル]";
	mes "あああ、眠い!!　寝たい!!";
	mes "でも、がんばらないと卒業が……";
	mes "つらいな～……しくしく……";
	mes "お師匠様～、今日はここまでじゃ";
	mes "だめですか～？";
	next;
	switch(select("ここは何をする所ですか？",(SIGN_QUE == 17)? "消えたアルケミストについて": "",(SIGN_QUE == 17)? "賢者の石ってなんですか？": "")) {
	case 1:
		mes "[ピルピル]";
		mes "ここは私のお師匠様、ヨルニム様の";
		mes "研究室です。";
		mes "お師匠様は最近、人工的に生命を";
		mes "生み出すことができるかの研究を";
		mes "なさっております。";
		next;
		mes "[ピルピル]";
		mes "もちろん、たやすいことでは";
		mes "ありません。";
		mes "ですので、お師匠様は最近ずっと";
		mes "その研究に没頭していらして……";
		mes "誰とも会っていないし、心配です。";
		close;
	case 2:
		mes "[ピルピル]";
		mes "消えたアルケミストですか？";
		mes "そのご婦人は、生命工学の分野で";
		mes "とっても有名な人だったと";
		mes "聞いています。";
		next;
		mes "[ピルピル]";
		mes "ある日、特定の材料を組み合わせて";
		mes "モンスターを召喚する方法を発表し、";
		mes "世界に一大センセーションを";
		mes "巻き起こした直後に、";
		mes "こつぜんと姿を消したそうです。";
		next;
		mes "[ピルピル]";
		mes "ここまでは誰でも知ってるお話です。";
		mes "実は、そのアルケミストさん、";
		mes "私の友達だったのです！";
		mes "とっても優秀な子だったんですよ。";
		next;
		mes "[ピルピル]";
		mes "彼女と彼女のお父さんは、生活や友達、";
		mes "全てを犠牲にして、実験に明け暮れ";
		mes "ました。そして、モンスター召喚術を";
		mes "発見したんです。";
		next;
		mes "[ピルピル]";
		mes "しかし、あまりにも実験でエネルギーを";
		mes "使いすぎた結果、あの研究の完成後、";
		mes "実験に嫌気がさしたと言って……";
		mes "お父さんと一緒に荷物をまとめて、";
		mes "^CE3131南にある森^000000に入って行って";
		mes "しまいました。";
		next;
		mes "[ピルピル]";
		mes "わざわざ、あんな危ない場所を選ぶ";
		mes "必要があったかどうか疑問です。";
		mes "でも、それだけ、何もかも忘れて静かに";
		mes "暮らしたかったのかもしれません。";
		mes "あの頃は、毎日毎日、誰かしら彼女を";
		mes "訪れていましたしね。";
		next;
		mes "[ピルピル]";
		mes "かなりストレスも溜まっていた";
		mes "みたいですし……。";
		mes "僕とお師匠様の研究が完成したら、";
		mes "彼女達みたいに世を捨てるように";
		mes "なるのかな……？";
		close;
	case 3:
		mes "[ピルピル]";
		mes "それは、僕もわかりません。";
		mes "毎日ここで生活しているというか、";
		mes "外にあんまり出てないから、噂とか";
		mes "全然わからないんです。";
		close;
	}
}

aldeba_in.gat,139,103,0	script	ノート	111,{
	mes "[ヨルニム]";
	mes "アアッ、触らないでください！";
	mes "私の研究日誌を、もとの場所に";
	mes "戻してください！";
	mes "はやく!!";
	close;
}

prt_maze02.gat,58,150,0	script	prtmazemove	139,5,5,{
OnTouch:
	mes "^3355FF深い森の中、あなたは木々の";
	mes "間に消える少女の後ろ姿を見つけ";
	mes "急いでその後を追った-^000000";
	close2;
	switch(rand(10)) {
		default: warp "prt_maze02.gat",11,146; break;
		case 4: 
		case 5: 
		case 6: warp "prt_maze03.gat",55,8; break;
		case 7: 
		case 8: 
		case 9: warp "prt_maze01.gat",62,129; break;
	}
	end;
}
prt_maze02.gat,57,151,1	duplicate(prtmazemove)	プルレ	91

prt_maze02.gat,18,126,0	script	prtmazewarp	139,3,3,{
	warp "prt_maze02.gat",90,170;
	end;
}

prt_maze02.gat,25,161,0	script	prtmazemusic	139,7,7,{
	soundeffect "assassin_of_sunset.wav",0;
	end;
}

prt_maze02.gat,14,183,4	script	タッタ	51,{
	if(SIGN_QUE > 18) {
		mes "[タッタ]";
		mes "星明かりはささやく～";
		mes "どんなに偉い学者でも～♪";
		mes "星がなんで美しく輝くか～";
		mes "どんな研究でもわからない～♪";
		mes "ラララ～♪";
		next;
		emotion 18;
		emotion 4,"プルレ#sign";
		mes "[プルレ]";
		mes "お父さん……";
		mes "[タッタ]";
		mes "ハハハッ、ちょっとクサかったかな？";
		close;
	}
	if(SIGN_QUE < 18) {
		emotion 2;
		mes "[タッタ]";
		mes "プルレ、今日は何をして";
		mes "遊んできたんだい？";
		next;
		emotion 2,"プルレ#sign";
		mes "[プルレ]";
		mes "今日は、青熊さんと白熊さんと";
		mes "鬼ごっこして遊んだの。";
		next;
		emotion 2;
		mes "[タッタ]";
		mes "近くには恐ろしい魔物が住んでいる。";
		mes "道に迷わないよう、気を付けるんだよ。";
		mes "いいね？";
		next;
		emotion 18,"プルレ#sign";
		mes "[プルレ]";
		mes "はーい、お父さん。";
		mes "でも、もうこの迷宮は、";
		mes "目を閉じていたって通れるわ。";
		next;
		mes "[タッタ]";
		mes "ふふ、この森に来てからかなり";
		mes "経ってしまったね。";
		mes "父のわがままで";
		mes "お前の人生が犠牲にならないか、";
		mes "心配だったとはいえ……";
		next;
		emotion 31,"プルレ#sign";
		mes "[プルレ]";
		mes "父さん、私達はやるべきことは";
		mes "全てやったでしょ？";
		mes "だから、休む時になっただけよ。";
		mes "ここに来てから、心がだいぶ";
		mes "落ち着いたもの。";
		next;
		emotion 28;
		mes "[タッタ]";
		mes "そうか。";
		mes "そうだったら、お父さんも嬉しいよ……";
		next;
		emotion 2;
		mes "[タッタ]";
		mes "私達は迷宮の親子～";
		mes "静かで深いさびしい森の中～";
		mes "しかし私たちは幸せで～～";
		if(SIGN_QUE != 17)
			close;
		next;
		if(select("うわー!!!!","失礼します")==1) {
			set SIGN_QUE,18;
			monster "prt_maze02.gat",14,177,"フローラ",1118,1;
			monster "prt_maze02.gat",17,171,"フローラ",1118,1;
			monster "prt_maze02.gat",24,173,"フローラ",1118,1;
			monster "prt_maze02.gat",17,175,"マリンスフィアー",1142,1;
			monster "prt_maze02.gat",17,168,"マリンスフィアー",1142,1;
			emotion 23,"プルレ#sign";
			emotion 23;
			mes "[プルレ]";
			mes "ヤーッ!!";
			mes "バイオプラント!!";
			mes "[タッタ]";
			mes "はっ!!";
			mes "スフィアーマイン!!";
			close;
		}
		emotion 0,"プルレ#sign";
		emotion 0;
		mes "[タッタ]";
		mes "何故……人がこのような場所に？";
		mes "いったい、どのようなご用件で？";
	}
	if(SIGN_QUE == 18) {
		emotion 32;
		mes "[プルレ]";
		mes "何者だ!!";
	}
	next;
	mes "[" +strcharinfo(0)+ "]";
	mes "実はお聞きしたいことがあって、";
	mes "お二人を探していました。";
	mes "会えて嬉しいです。";
	next;
	mes "[タッタ]";
	mes "それは、どうも……";
	mes "こんな所までやってくるとは、";
	mes "一体、何を聞きたいのでしょう？";
	next;
	switch(select("賢者の石について","アルケミストの研究について","やっぱりなんでもないです")) {
	case 1:
		mes "[タッタ]";
		mes "……実は私達にも";
		mes "よくわからないのです。";
		next;
		mes "[タッタ]";
		mes "たぶん、賢者の石とは、誰も";
		mes "理解してはいけないものなのです。";
		mes "時々、噂になったりならなかったり……";
		mes "誰かが作り出した話なのかも";
		mes "しれません。";
		next;
		mes "[タッタ]";
		mes "こんな所まで訪ねてきてくださったのに";
		mes "お力になれず申し訳ございません。";
		next;
		mes "[タッタ]";
		mes "噂話程度でよければ……";
		mes "賢者の石は、どんな物質も金に";
		mes "換えることができる、触媒のような";
		mes "ものだと言われています。";
		next;
		mes "[タッタ]";
		mes "錬金術を研究する者が、";
		mes "だれもが目指す究極の存在です。";
		next;
		mes "[タッタ]";
		mes "聞いたところ、物を金に変える以外に";
		mes "不死の名薬とも言われています。";
		mes "その色は深紅だそうです……";
		mes "どこでこんな噂がたったか、ですか？";
		next;
		mes "[タッタ]";
		mes "何人かの学者は、賢者の石を";
		mes "探すのではなく、賢者の石を作ろうと";
		mes "しました。そして、賢者の石そのものは";
		mes "無理でしたが、それに近い魔力の高い";
		mes "石を作るのには成功したと聞いて";
		mes "います。";
		next;
		mes "[プルレ]";
		mes "私達が知っているのは、この程度です。";
		mes "せっかくここまでいらしたのに、";
		mes "申し訳ございません。";
		next;
		mes "[タッタ]";
		mes "それでは、帰り道は私達が";
		mes "案内しましょう。";
		mes "ここは危険ですから。";
		next;
		mes "[タッタ][プルレ]";
		mes "ごきげんよう、旅人さん。";
		close2;
		set SIGN_QUE,19;
		warp "mjolnir_12.gat",44,23;
		end;
	case 2:
		mes "[プルレ]";
		mes "私とお父さんは、とっても長い間";
		mes "研究を続けてきました。そして、";
		mes "成功してしまったんです。";
		next;
		mes "[プルレ]";
		mes "入手可能な特定の材料を組み合わせ、";
		mes "まったく別の力を発揮する";
		mes "調合液です。";
		next;
		mes "[プルレ]";
		mes "それを使うと、特定のモンスターを";
		mes "召喚したり、爆発させたり出来ます。";
		mes "研究成果を発表した時は、本当に";
		mes "大変でした……世界中のアルケミストが";
		mes "集まったかと思うほど、毎日人が";
		mes "訪れてきました！";
		next;
		mes "[タッタ]";
		mes "研究で疲れていた上、研究後の注目で";
		mes "娘は心身共にやられてしまいました。";
		mes "それで、人に見つからないような";
		mes "この森に住むことにしたのです。";
		next;
		mes "[タッタ]";
		mes "調合液について聞きたいなら、";
		mes "錬金術師ギルドの人や、";
		mes "街のアルケミストに";
		mes "聞けばよろしいでしょう。";
		next;
		mes "[タッタ]";
		mes "私達は、もうこれ以上、";
		mes "それについて";
		mes "話したくないのです。";
		close;
	case 3:
		mes "[タッタ]";
		mes "ハハハ、おもしろいお方だ。";
		close;
	}
}

prt_maze02.gat,16,183,3	script	プルレ#sign	91,{
	if(SIGN_QUE < 19) {
		mes "[プルレ]";
		mes "ララル～";
		mes "ララリ～";
		close;
	}
	mes "[プルレ]";
	mes "賢者の石……";
	close;
}

//============================================================
// 第1部 - ジスクリエの試練
//------------------------------------------------------------
geffen_in.gat,59,74,4	script	ジスクリエ#sign	803,{
	if(SIGN_QUE < 20) {
		mes "[ジスクリエ]";
		mes "マスタ～～";
		mes "もう一杯～";
		close;
	}
	switch(SIGN_QUE) {
	case 20:
		mes "[ジスクリエ]";
		mes "マスタ～～";
		mes "もう一杯～";
		next;
		mes "[ジスクリエ]";
		mes "ふぅ……";
		mes "あら";
		mes (Sex? "素敵なお兄さん、": "可愛いお嬢さん")+ "、こんにちは。";
		mes "私はジスクリエ。";
		mes "聞いたことあるでしょ？";
		mes "フフ、驚いた？";
		next;
		if(select("初耳です……","聞いたことあります！")==1) {
			emotion 4;
			mes "[ジスクリエ]";
			mes "クスクス、冗談……";
			mes "実は知っているんでしょう？";
			next;
			if(select("はい","全然知りません")==2) {
				emotion 9;
				mes "[ジスクリエ]";
				mes "……";
				next;
				mes "[ジスクリエ]";
				mes "そう……";
				mes "関心がない方のようね。";
				next;
			}
		}
		else
			set @menu,1;
		if(@menu==1) {
			emotion 32;
			mes "[ジスクリエ]";
			mes "ホホホ、そうでしょう。";
			mes "でも、私は美しいだけじゃないのよ！";
			mes "私は好奇心が強くて、何事も試さないと";
			mes "気が収まらないし、他人が知っている";
			mes "ことも全て知りたい。";
			mes "厄介な性格よね、ヒック。";
			next;
			mes "[ジスクリエ]";
			mes "でもね、おかげで私が知らないことは";
			mes "何一つないの。フフ……";
			mes "あん、もう空？";
			mes "お姉さん～、もう一杯～！";
			next;
		}
		mes "[ジスクリエ]";
		mes "私はね、博識で輝いている自分が好き。";
		next;
		mes "[ジスクリエ]";
		mes "特に、私を仰いで見る人々の視線!!";
		mes "ゾッとするような、ピリっとするような";
		mes "あの視線……フフッ。";
		next;
		mes "[ジスクリエ]";
		mes "その為に、学ぶことに狂ったように";
		mes "執着して……";
		next;
		mes "[ジスクリエ]";
		mes "ウィザード試験はもちろん、";
		mes "水準以上の知識を身に付けなければ";
		mes "難関と言われるセージ試験も！";
		next;
		mes "[ジスクリエ]";
		mes "数学的計算能力と専門知識が必要な";
		mes "アルケミスト試験も、優秀な成績で";
		mes "合格した、優秀な学徒であると同時に";
		mes "有能な学者……それが私。";
		next;
		mes "[ジスクリエ]";
		mes "ホホホ、自分で言うのもなんだけど、";
		mes "私より博識な人はこの世にいないわ。";
		mes "ホホホ、ホホホホホ。";
		next;
		if(select("自惚れているね","ほどほどにしてください……")==2) {
			mes "[ジスクリエ]";
			mes "フーン……";
			mes "飲んだらいけない？";
			mes "私はお酒が大好きなの♪";
			mes "ヒック。";
			next;
			mes "[ジスクリエ]";
			mes "曇った世の中が、私の目には";
			mes "美しく見えるのよ、わからなくて～？";
			close;
		}
		mes "[ジスクリエ]";
		mes "あら……";
		mes "私が自惚れている？";
		next;
		emotion 6;
		mes "[ジスクリエ]";
		mes "こんなに優秀な私が？";
		mes "………ふーん。";
		next;
		emotion 7;
		mes "[ジスクリエ]";
		mes "今まで誰も、そんなことをこの私に";
		mes "言った人はいなかったわ……";
		mes "だって、私は事実凄いのですもの!!!";
		next;
		mes "[ジスクリエ]";
		mes "わかったわ!!!!";
		mes "あなたが私より頭が良いなら";
		mes "さっきの生意気な言葉も忘れて、";
		mes "私は自分が自惚れていると";
		mes "認めましょう！";
		next;
		mes "[ジスクリエ]";
		mes "でも、あなたが私より劣るなら、";
		mes "私の自尊心を傷つけた代償を";
		mes "それ相応に支払ってもらうわ!!";
		next;
		mes "[ジスクリエ]";
		mes "話は簡単。";
		mes "ここにいるアロンが出すテストを";
		mes "二人で受けるだけ。選択問題だから";
		mes "慌てることはないわ。";
		next;
		mes "[ジスクリエ]";
		mes "公平かどうかは、心配しても";
		mes "始まらないわよ。";
		mes "私は何もかも学んだ";
		mes "才女なんだから。フフ。";
		next;
		emotion 29;
		mes "[ジスクリエ]";
		mes "こういうのって、博識な私がどうしても";
		mes "有利になってしまうんだけど、これも、";
		mes "私をバカにした代価よ。オホホホホ。";
		next;
		mes "[ジスクリエ]";
		mes "じゃ、お願い。";
		mes "アロン？";
		set SIGN_QUE,21;
		close;
	case 21:
	case 22:
		mes "[ジスクリエ]";
		mes "余所見してる余裕があって？";
		mes "さぁ、始めましょうか！";
		close;
	case 23:
		mes "[ジスクリエ]";
		mes "ふ、ふふふ……";
		mes "私の勝ちね!!";
		next;
		emotion 6;
		mes "[ジスクリエ]";
		mes "考え付くかぎり最悪の方法で、";
		mes "あなたに恥をかかせてやりたいけど";
		mes "私は有能で理性的な知識人。";
		next;
		mes "[ジスクリエ]";
		mes "ま、ちょっとお酒入ってたし……";
		next;
		mes "[ジスクリエ]";
		mes "とにかく！";
		mes "私の心を傷つけたことは";
		mes "忘れてあげるわ。";
		next;
		mes "[ジスクリエ]";
		mes "でも、今後私の近くに現われたら、";
		mes "ナパームバルカンで遠くまで";
		mes "飛ばしてさしあげてよ。";
		next;
		emotion 29;
		mes "[ジスクリエ]";
		mes "じゃあ、もう消えてくれる？";
		next;
		if(select("このまま退くことはできません！","あの、いえ、実は……")==2) {
			mes "[ジスクリエ]";
			mes "ん？　まさか!!";
			mes "女だから手加減したとか";
			mes "言わないわよね？";
			mes "次から、良く相手を見定めてから";
			mes "勝負なさい！";
			close;
		}
		mes "[ジスクリエ]";
		mes "あー、もう！";
		mes "本当に疲れる人ね……";
		next;
		mes "[ジスクリエ]";
		mes "フン、まぁいいわ。";
		mes "少し可哀想ですものね。";
		mes "今度も私は勝つわ!!";
		set SIGN_QUE,22;
		close;
	case 24:
		mes "[ジスクリエ]";
		mes "ああ、もう！";
		mes "まったくもう!!";
		next;
		mes "[ジスクリエ]";
		mes "……………………";
		mes "ふふ……………………";
		mes "そうよ、私の負けよ。";
		mes "私、まだまだ修行不足なのね。";
		next;
		mes "[ジスクリエ]";
		mes "いいわ。認めます。";
		mes "私も、こんなことが判らないほど";
		mes "わからず屋じゃないし。";
		mes "自分が自惚れていたって、認めるわ。";
		next;
		mes "[ジスクリエ]";
		mes "ふふっ、もうちょっと飲んで";
		mes "また前みたいに旅に出ようかしら。";
		next;
		mes "[ジスクリエ]";
		mes "あ、ところであなた。名前は？";
		mes "私を倒した相手だもの。";
		mes "名前、知りたいわ。";
		next;
		input 'name$;
		mes "[ジスクリエ]";
		mes "へ～、";
		mes 'name$+ "ね……";
		mes "永遠に忘れないわ、その名前。";
		next;
		set SIGN_QUE,25;
		getitem 7177,1;
		mes "[ジスクリエ]";
		mes "これはプレゼントよ。";
		mes "私の友達、メッツが適当な人に";
		mes "渡せばいいってくれたんだけど。";
		mes "私が持ってるつもりだったけど、";
		mes "あなたのほうが相応しいような";
		mes "気がするわ。";
		next;
		mes "[ジスクリエ]";
		mes "これについて興味あるなら、";
		mes "^3131CEディアリース^000000を";
		mes "訪ねなさい。";
		next;
		mes "[ジスクリエ]";
		mes "賭け事が好きで、私と同じで";
		mes "一ヶ所に落ち着かない人だから……";
		mes "今、どこにいるか知らないわ。";
		next;
		mes "[ジスクリエ]";
		mes "後は自分で探してみて。";
		mes "私は一杯飲んで、このほろ苦い気持ちを";
		mes "和らげるとするから。";
		mes "じゃ、バイバイ。";
		close;
	case 25:
		set '@rand,rand(3);
		mes "[ジスクリエ]";
		mes "あたた……頭が……";
		mes "あぁ、" +('name$ != ""? 'name$: "エンゲル・ハワード")+ "ね。";
		mes "ディアリースは見つかった？";
		next;
		mes "[ジスクリエ]";
		mes "彼は、賭け事が三度のご飯より";
		mes "好きだから、そういう場所に行けば";
		mes "会えるかもね。";
		close;
	default:
		mes "[ジスクリエ]";
		mes "あ～、ヒック……";
		mes "飲み過ぎたかしら？";
		close;
	}
}

geffen_in.gat,61,72,7	script	アロン	754,{
	switch(SIGN_QUE) {
	case 21:
		emotion 9;
		mes "[アロン]";
		mes "……………………";
		next;
		emotion 9;
		mes "[アロン]";
		mes "……z……Z……";
		next;
		emotion 6,"ジスクリエ#sign";
		mes "[ジスクリエ]";
		mes "アロン!!";
		next;
		emotion 23;
		mes "[アロン]";
		mes "はっ!!";
		mes "うたた寝してましたか……";
		mes "お酒に弱くて、はは。";
		next;
		emotion 19;
		mes "[アロン]";
		mes "すみません。";
		mes "おほん、それでは私が裁判……";
		mes "じゃなくて、試験出題兼監督官を";
		mes "務めれば良いのですね？";
		mes "あぁ～、お酒を飲みにきたのに……";
		next;
		mes "[アロン]";
		mes "それでは、準備っと……";
		mes "急に頼むんだから……";
		mes "仕方ない、この前、学生達に出した";
		mes "問題を……";
		set SIGN_QUE,22;
		close;
	case 22:
		break;
	default:
		emotion 23;
		mes "[アロン]";
		mes "うおおおおおおー!!";
		mes "今すぐ、私と一緒にプロンテラ大聖堂に";
		mes "行きましょう!!!";
		mes "結婚しましょう!!!";
		next;
		emotion 21;
		mes "[アロン]";
		mes "その顔！　その脚線美!!";
		mes "すべてが私の好みです!!!!";
		mes "私と結婚して、この世に愛を";
		mes "振り撒きましょう!!";
		next;
		emotion 14;
		mes "[アロン]";
		mes "私がきっと貴方を幸せに……";
		mes "あ……";
		mes "ヒック！　そこのきれいなお姉さん!!";
		mes "私と結婚しましょう!!!";
		next;
		mes "-冷たい視線-";
		next;
		emotion 28;
		mes "[アロン]";
		mes "…………";
		close;
	}
	//22の続き
	emotion 0;
	mes "[アロン]";
	mes "では始めます。";
	mes "問題は10問です。";
	next;
	while(1) {
		switch('@c) {
		case 0:
			switch(rand(3)) {
			case 0:
				mes "[アロン]";
				mes "1】ブラックスミス転職と";
				mes "関係ない人は？";
				next;
				if(select("バイス","ヒュッケ","バルカデー","グロン")==3)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "1】中和剤を作る時、必要のない";
				mes "材料は？";
				next;
				if(select("カルボーディル","ディトリミン","アルコール")==1)
					set '@m,'@m+1;
				break;
			case 2:
				mes "[アロン]";
				mes "1】次の中で大きさの違う";
				mes "モンスターは？";
				next;
				if(select("巨大ウィスパー","マーリン","カナトウス","コボルドアーチャー")==2)
					set '@m,'@m+1;
				break;
			}
			set '@r,8;
			break;
		case 1:
			switch(rand(3)) {
			case 0:
				mes "[アロン]";
				mes "2】プリーストのスキル、聖体降福と";
				mes "関連あるスキルは？";
				next;
				if(select("レックスディビーナ","グロリア","リカバリー","サンクチュアリ")==2)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "2】ホワイトスリムポーションを";
				mes "作るのに必要のない材料は？";
				next;
				if(select("乳鉢","魔女の星の粉","空の試験管","空のポーション瓶")==4)
					set '@m,'@m+1;
				break;
			case 2:
				mes "[アロン]";
				mes "2】ブラックスミスがグラディウスを";
				mes "作るのに必要な材料は？";
				next;
				if(select("サファイア","ジルコン","トパーズ","呪われたルビー")==1)
					set '@m,'@m+1;
				break;
			}
			set '@r,7;
			break;
		case 2:
			switch(rand(3)) {
			case 0:
				mes "[アロン]";
				mes "3】ボルト系魔法の属性の中で、";
				mes "マジシャンが習得できない";
				mes "属性は何か？";
				next;
				if(select("水","地","火","風")==2)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "3】ウサギのヘアバンドの";
				mes "防御力と能力値は？";
				next;
				if(select("1/LUK+2","1/LUK+5","2/LUK+2","2/LUK+5")==3)
					set '@m,'@m+1;
				break;
			case 2:
				mes "[アロン]";
				mes "3】次の中で、カードの装着後名称が";
				mes "間違っているのは？";
				next;
				if(select("ホーネットカード→マーター","レクイエムカード→カオス","ワームテールカード→クレバー","ゴーレムカード→イモータル")==4)
					set '@m,'@m+1;
				break;
			}
			set '@r,7;
			break;
		case 3:
			mes "[アロン]";
			mes "では次の問題です。";
			next;
			switch(rand(2)) {
			case 0:
				mes "[アロン]";
				mes "4】ミッドガッツ王国、";
				mes "国王の名前は？";
				next;
				if(select("トリストン3世","トリスタン3世","トライスター3世","トラスト3世")==2)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "4】次の中で、種族が違う";
				mes "モンスターは？";
				next;
				if(select("ペノメナ","ハティー","ペスト","エクスプロージョン")==1)
					set '@m,'@m+1;
				break;
			}
			set '@r,7;
			break;
		case 4:
			switch(rand(3)) {
			case 0:
				mes "[アロン]";
				mes "5】次の中で、イグドラシルの葉を";
				mes "ドロップしないモンスターは？";
				next;
				if(select("マルドゥーク","バフォメットJr.","エンジェリング","彷徨う者")==1)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "5】シルクローブを着ることが";
				mes "できない職業は？";
				next;
				if(select("ソードマン","マーチャント","ハンター","マジシャン")==3)
					set '@m,'@m+1;
				break;
			case 2:
				mes "[アロン]";
				mes "5】PVP室に入場できるようになる";
				mes "レベルは？";
				next;
				if(select("30","31","32","33")==2)
					set '@m,'@m+1;
				break;
			}
			set '@r,8;
			break;
		case 5:
			switch(rand(3)) {
			case 0:
				mes "[アロン]";
				mes "6】空きビンの重量は？";
				next;
				if(select("1","2","3")==2)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "6】インディアンのヘアバンドの";
				mes "防御値は？";
				next;
				if(select("0","1","2","3")==4)
					set '@m,'@m+1;
				break;
			case 2:
				mes "[アロン]";
				mes "6】タートルアイランドが";
				mes "一番近い都市は？";
				next;
				if(select("アルデバラン","アルベルタ","コモド","イズルード")==2)
					set '@m,'@m+1;
				break;
			}
			set '@r,8;
			break;
		case 6:
			switch(rand(3)) {
			case 0:
				mes "[アロン]";
				mes "7】(((51×15)／3)＋5)＝？";
				next;
				if(select("250","255","260","265")==3)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "7】(((4560／4)／2)＋3)＝？";
				next;
				if(select("573","574","575","576")==1)
					set '@m,'@m+1;
				break;
			case 2:
				mes "[アロン]";
				mes "7】(3102＋500＋4)／6＝？";
				next;
				if(select("600","601","602")==2)
					set '@m,'@m+1;
				break;
			}
			set '@r,8;
			break;
		case 7:
			switch(rand(2)) {
			case 0:
				mes "[アロン]";
				mes "8】ジュノーの精錬所に";
				mes "一番近いのは？";
				next;
				if(select("セージキャッスル","モンスター博物館","道具店","武器防具店")==4)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "8】次のハンターのトラップスキルで";
				mes "ダメージを与えないものは？";
				next;
				if(select("クレイモアトラップ","フリージングトラップ","ショックウェーブトラップ","ランドマイン")==3)
					set '@m,'@m+1;
				break;
			}
			set '@r,8;
			break;
		case 8:
			switch(rand(2)) {
			case 0:
				mes "[アロン]";
				mes "9】火属性の武器が一番有効な";
				mes "モンスターは？";
				next;
				if(select("ゴブリン長男","ゴブリン次男","ゴブリン三男","ゴブリン四男")==4)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "9】ストーンカースが通じない";
				mes "モンスターは？";
				next;
				if(select("エルダーウィロー","イビルドルイド","白蓮玉","マルク")==2)
					set '@m,'@m+1;
				break;
			}
			set '@r,8;
			break;
		case 9:
			switch(rand(2)) {
			case 0:
				mes "[アロン]";
				mes "10】次の中で同じ外見じゃないのは？";
				next;
				if(select("プロンテラのホルグレン","プロンテラの人形商人","イズルードの肉商人","モロクの肉商人")==3)
					set '@m,'@m+1;
				break;
			case 1:
				mes "[アロン]";
				mes "10】次の中でノービスが";
				mes "装備できないのは？";
				next;
				if(select("葬式用の帽子","足鎖","ウドゥンメイル","ブリーフ")==3)
					set '@m,'@m+1;
				break;
			}
			set '@r,8;
			break;
		case 10:
			mes "[アロン]";
			mes "はい、ここまで。";
			mes "テスト結果を見ましょう。";
			next;
			mes "[アロン]";
			mes strcharinfo(0)+ "さんの";
			mes "成績は……";
			mes '@m+ "点ですね。";
			next;
			mes "[アロン]";
			mes "そして、ジスクリエの成績は";
			mes '@e+ "点です。";
			next;
			if('@m > '@e) {
				set SIGN_QUE,24;
				mes "[ジスクリエ]";
				mes "ま、まさか……";
			}
			if('@m < '@e) {
				set SIGN_QUE,23;
				emotion 29,"ジスクリエ#sign";
				mes "[ジスクリエ]";
				mes "ほほほ、やっぱり！";
				mes "褒めて褒めて!!!";
				mes "オホホホホ!!";
			}
			if('@m == '@e) {
				set SIGN_QUE,24;
				mes "[ジスクリエ]";
				mes "クッ、思ったよりやるわね……";
			}
			next;
			mes "[アロン]";
			mes "これでよろしいですか？";
			mes "うーん、もうちょっと飲みたかった";
			mes "けど……。あとはお二人で話し合って";
			mes "くださいね。";
			close;
		}
		if(rand(10) < '@r) {
			emotion 2,"ジスクリエ#sign";
			mes "[ジスクリエ]";
			mes "ふふ、簡単ね。";
			set '@e,'@e+1;
		}
		else {
			emotion 23,"ジスクリエ#sign";
			mes "[ジスクリエ]";
			mes "クッ、この私がこんなミスを";
			mes "するなんて……";
		}
		if('@c >= 2) {
			next;
			mes "[ジスクリエ]";
			mes "えっと、いまのところ点数は……";
			next;
			if('@m > '@e) {
				mes "[ジスクリエ]";
				mes "ハッ!!　このままじゃ負けちゃう！";
				mes "早く次!!";
			}
			if('@m < '@e) {
				mes "[ジスクリエ]";
				mes "ふふ、それっぽっち？";
				mes "もうちょっと脳みそを";
				mes "転がしてみたらどう？";
			}
			if('@m == '@e) {
				mes "[ジスクリエ]";
				mes "あら、思ったよりやるわね。";
				mes "油断ならないわ。";
			}
		}
		set '@c,'@c+1;
		next;
		continue;
	}
}

//==============================================================
// 第1部 - ディアリースの試練
//==============================================================
cmd_in02.gat,88,51,4	script	変な男	806,{
	if(SIGN_QUE < 25) {
		mes "[ディアリース]";
		mes "あたー、また外したか……";
		mes "ちぇっ……";
		mes "うん？　なんだお前？";
		next;
		if(Zeny < 10000) {
			emotion 32;
			mes "[ディアリース]";
			mes "お、金持ってるようだな。";
			mes "何、乞食じゃねぇよ。";
			mes "ジロジロ見てんじゃねぇ！";
			mes "一発食らいてぇのか?!";
			percentheal -10,0;
			close;
		}
		misceffect 10;
		mes "[ディアリース]";
		mes "お、金持ってるようだな。";
		mes "フッ";
		mes "ちょっとばかし借りるよ。";
		mes "ククク……";
		set Zeny,Zeny-10000;
		close;
	}
	switch(SIGN_QUE) {
	case 25:
		mes "[ディアリース]";
		mes "あ、くそ！";
		mes "また外しやがった";
		mes "ふぅ……";
		next;
		if(select("あの……","見ていないふりをして通り過ぎる")==2) {
			mes "[ディアリース]";
			mes "あー、もう財布も空だな……";
			close;
		}
		mes "[ディアリース]";
		mes "何だ？";
		mes "俺は今、イライラしてんだ。";
		mes "冷やかしなら、覚悟しろよ、";
		mes "てめぇ！";
		next;
		if(select("ご、ごめんなさい","メッツさんの紹介で来ました")==1) {
			mes "[ディアリース]";
			mes "何だと！　この俺をからかうとは";
			mes "いい度胸じゃねぇか！";
			mes "覚悟しな……クク……";
			close2;
			heal -(Hp-1),0;
			soundeffect "sign_noise.wav",0;
			warp "comodo.gat",122,100;
			end;
		}
		mes "[ディアリース]";
		mes "ちぇっ、なんだ。";
		mes "メッツが送ったヤロウか。";
		mes "ってことは、あれだろ、あれ。";
		mes "クク……";
		next;
		mes "[ディアリース]";
		mes "俺のテストが受けたかったら、";
		mes "30,000zeny持ってきな。";
		mes "びた一文まけねぇぜ。";
		set SIGN_QUE,26;
		close;
	case 26:
		mes "[ディアリース]";
		mes "金は持ってきたか？";
		mes "クク……";
		next;
		if(select("持ってきました","まだです")==2) {
			mes "[ディアリース]";
			mes "何だって!?";
			mes "クク……早くしたほうがいいぜ。";
			mes "俺の気分が変わらないうちによ……";
			mes "クク……";
			close;
		}
		mes "[ディアリース]";
		mes "ほう……？";
		if(Zeny < 30000) {
			mes "あ……？";
			mes "てめぇ俺をからかってるのか？";
			mes "出直しやがれ！";
			close;
		}
		set Zeny,Zeny-30000;
		mes "クク……";
		mes "よし、また明日の夕方に来い。";
		set SIGN_QUE,27;
		close;
	case 27:
		if(gettime(3) < 18 || gettime(3) >= 23) {
			mes "[ディアリース]";
			mes "夕方に来いって言っただろ。";
			mes "てめぇは時間もわからねぇのか？";
			close;
		}
		mes "[ディアリース]";
		mes "おう、時間ピッタリだな。";
		mes "あんまり時間にうるさいヤロウは";
		mes "好きじゃねぇが。";
		next;
		mes "[ディアリース]";
		mes "約束は約束だ。テストをしてやっか。";
		mes "難しいからって、さぼるんじゃねぇぜ。";
		mes "クク……";
		set SIGN_QUE,28;
		close;
	case 28:
		mes "[ディアリース]";
		mes "よし、テストその1だ。";
		mes "俺好みの";
		mes "^FF0000工芸品をできるだけ集めて来い^000000。";
		mes "鑑定眼ってやつを見てやる。";
		next;
		mes "[ディアリース]";
		mes "ある程度のものじゃなければ";
		mes "合格じゃねぇ。わかったな。";
		mes "クク……";
		set SIGN_QUE,29;
		close;
	case 29:
		mes "[ディアリース]";
		mes "持ってきたか？";
		mes "どれ、見せてみろ。";
		next;
		if(countitem(734)) set '@point,'@point+1; //赤い額縁
		if(countitem(735)) set '@point,'@point+1; //青い陶磁器
		if(countitem(736)) set '@point,'@point+1; //白い皿
		if(countitem(7149)) set '@point,'@point+1; //黄色い皿
		if(countitem(747)) set '@point,'@point+2; //水晶鏡
		if(countitem(749)) set '@point,'@point+4; //氷バラ
		if(countitem(740)) set '@point,'@point+1; //ぬいぐるみ
		if(countitem(741)) set '@point,'@point+1; //ポリン人形
		if(countitem(742)) set '@point,'@point+2; //チョンチョン人形
		if(countitem(743)) set '@point,'@point+3; //スポア人形
		if(countitem(752)) set '@point,'@point+3; //バッタ人形
		if(countitem(753)) set '@point,'@point+4; //サル人形
		if(countitem(754)) set '@point,'@point+4; //タヌキ人形
		if(countitem(750)) set '@point,'@point+7; //バフォメット人形
		if(countitem(751)) set '@point,'@point+7; //オシリス人形
		if('@point == 0) {
			mes "[ディアリース]";
			mes "……";
			mes "おい。何もないじゃねぇか。";
			mes "早く俺を満足させる品を持って来い。";
			mes "怠けるな！";
			close;
		}
		if('@point <= 10) {
			mes "[ディアリース]";
			mes "う～ん……";
			mes "ちょっと足りねぇな。";
			mes "この程度じゃ、俺は満足しないぜ。";
			close;
		}
		mes "[ディアリース]";
		mes "ほう、悪くねぇな。";
		mes "これは、ほ～……";
		next;
		mes "[ディアリース]";
		mes "よしよし、いいだろう。";
		mes "じゃあ次のテストをする試験場に";
		mes "送ってやる。";
		next;
		mes "[ディアリース]";
		mes "あっちに、ラディマンって奴がいる。";
		mes "詳しくは奴に聞きな。";
		delitem 734,1;
		delitem 735,1;
		delitem 736,1;
		delitem 7149,1;
		delitem 747,1;
		delitem 749,1;
		delitem 740,1;
		delitem 741,1;
		delitem 742,1;
		delitem 743,1;
		delitem 752,1;
		delitem 753,1;
		delitem 754,1;
		delitem 750,1;
		delitem 751,1;
		set SIGN_QUE,30;
		if(checkre()) {
			if(BaseLevel >= 90) getexp 1300,0;
			else if(BaseLevel >= 80) getexp 1000,0;
			else if(BaseLevel >= 70) getexp 800,0;
			else if(BaseLevel >= 60) getexp 500,0;
			else getexp 300,0;
		}
		else {
			if(BaseLevel >= 90) getexp 13000,0;
			else if(BaseLevel >= 80) getexp 10000,0;
			else if(BaseLevel >= 70) getexp 8000,0;
			else if(BaseLevel >= 60) getexp 5000,0;
			else getexp 3000,0;
		}
		close2;
		warp "cmd_in01.gat",33,29;
		end;
	case 30:
	case 31:
		mes "[ディアリース]";
		mes "なんだてめぇ……";
		mes "まだテストに受かってないのか。";
		mes "また向こうに送ってやるから、";
		mes "せいぜい頑張りな……クク……";
		close2;
		warp "cmd_in01.gat",33,29;
		end;
	case 32:
		mes "[ディアリース]";
		mes "不合格か。";
		mes "ま、諦めるのも人生ってな。";
		mes "どうする？";
		next;
		if(select("もう1回","また後で")==2) {
			mes "[ディアリース]";
			mes "クク……せいぜい無駄な練習でも";
			mes "して来るんだな。";
			close;
		}
		mes "[ディアリース]";
		mes "クク……せいぜい頑張りな……";
		mes "その程度じゃ合格は遠いんじゃねぇ？";
		mes "ククク……";
		close2;
		warp "cmd_in01.gat",33,29;
		end;
	case 33:
		mes "[ディアリース]";
		mes "一応合格ってか。";
		mes "俺的には、まだまだなんだが、";
		mes "約束だから、パスってことにしてやる。";
		next;
		mes "[ディアリース]";
		mes "そしたらな……";
		mes "アルベルタのベーカーって奴を";
		mes "訪ねろ。";
		set SIGN_QUE,35;
		getitem 7177,1;
		if(checkre()) {
			if(BaseLevel >= 90) getexp 1700,0;
			else if(BaseLevel >= 80) getexp 1200,0;
			else if(BaseLevel >= 70) getexp 900,0;
			else if(BaseLevel >= 60) getexp 700,0;
			else getexp 300,0;
		}
		else {
			if(BaseLevel >= 90) getexp 17000,0;
			else if(BaseLevel >= 80) getexp 12000,0;
			else if(BaseLevel >= 70) getexp 9000,0;
			else if(BaseLevel >= 60) getexp 7000,0;
			else getexp 3000,0;
		}
		next;
		mes "[ディアリース]";
		mes "俺の役はここまでだ。";
		mes "二度と来るなよ。";
		close;
	case 34:
		mes "[ディアリース]";
		mes "ふん、思ってたより上手かったじゃ";
		mes "ねぇか。";
		next;
		mes "[ディアリース]";
		mes "それじゃぁな……";
		mes "アルベルタのベーカーって奴を";
		mes "訪ねろ。";
		set SIGN_QUE,35;
		getitem 7177,1;
		set Zeny,Zeny+20000;
		if(checkre()) {
			if(BaseLevel >= 90) getexp 1900,0;
			else if(BaseLevel >= 80) getexp 1400,0;
			else if(BaseLevel >= 70) getexp 1000,0;
			else if(BaseLevel >= 60) getexp 700,0;
			else getexp 300,0;
		}
		else {
			if(BaseLevel >= 90) getexp 19000,0;
			else if(BaseLevel >= 80) getexp 14000,0;
			else if(BaseLevel >= 70) getexp 10000,0;
			else if(BaseLevel >= 60) getexp 7000,0;
			else getexp 3000,0;
		}
		next;
		mes "[ディアリース]";
		mes "これは、貴様が最初に持ってきた金で";
		mes "稼いだ分さ。持っていけ。";
		mes "……";
		mes "俺の役はここまでだ。";
		mes "二度と来るなよ。";
		close;
	default:
		emotion 29;
		mes "[ディアリース]";
		mes "おいおい、二度と来るなって";
		mes "言ったよな。";
		next;
		if(select("さようなら","またテストを受けたいです")==1) {
			emotion 32;
			mes "[ディアリース]";
			mes "用もなく来るんじゃねぇよ。";
			mes "とっとと失せな。";
			close;
		}
		emotion 29;
		mes "[ディアリース]";
		mes "物好きだな……";
		mes "はいはい、送ってやるよ。";
		next;
		warp "cmd_in01.gat",33,29;
		end;
	}
}

cmd_in01.gat,33,25,5	script	試験官	724,{
	switch(SIGN_QUE) {
	case 30:
	case 31:
		mes "[ラマディン]";
		mes "こちらのチャットルームが控室と";
		mes "なっております。控室でお待ち";
		mes "ください～。チャットルームを";
		mes "クリックすることで、控室に入ることが";
		mes "できます。テストの内容は";
		mes "リズム感を見るものです。";
		next;
		mes "[ラマディン]";
		mes "順番になると特設ルームに移動します。";
		mes "床に「×」型のパネルがあります。";
		mes "左上[|＼]、右上[／|]、";
		mes "左下[|／]、右下[＼|]の四箇所を";
		mes "流れる音楽にあわせて踏んでください。";
		next;
		mes "[ラマディン]";
		mes "音楽の指示通りにパネルを踏むと点が";
		mes "加算されます。ちゃんと音楽にあわせて";
		mes "踏まないと駄目ですよ～。";
		next;
		mes "[ラマディン]";
		mes "音楽が終わったら、私が合計点を";
		mes "計算します。点数によって、";
		mes "合格・不合格がありますから";
		mes "気をつけてくださいね。";
		next;
		mes "[ラマディン]";
		mes "テストが終わりましたら、私のもとに";
		mes "点数確認にいらしてください。";
		mes "では、頑張ってください～。";
		close;
	case 32:
		mes "[ラマディン]";
		mes "はい、";
		mes strcharinfo(0)+ "様ですね。";
		mes "えっと……";
		next;
		mes "[ラマディン]";
		mes "あらあら。不合格です～。";
		mes "ちゃんと合格点数じゃなければ";
		mes "駄目です。";
		next;
		mes "[ラマディン]";
		mes "また再挑戦してくださいませ。";
		mes "ありがとうございました～。";
		set SIGN_QUE,30;
		close;
	case 33:
		mes "[ラマディン]";
		mes "はい、";
		mes strcharinfo(0)+ "様ですね。";
		mes "えっと……";
		next;
		mes "[ラマディン]";
		mes "おめでとうございます！　合格です！";
		mes "ディアリースさんには、連絡して";
		mes "おきますね。では、彼のほうを";
		mes "お訪ねください。";
		mes "お疲れさまでした～！";
		close;
	case 34:
		mes "[ラマディン]";
		mes "はい、";
		mes strcharinfo(0)+ "様ですね。";
		mes "えっと……";
		next;
		mes "[ラマディン]";
		mes "すごい～～～～～!!";
		mes "おめでとうございます!!!!";
		mes "満点です!!!!";
		mes "それでは、ディアリースさんに";
		mes "連絡しますね。";
		next;
		mes "[ラマディン]";
		mes "こんな良い点数ですもの。";
		mes "ディアリースさんがお祝いしてくれると";
		mes "いいですね。";
		mes "では、お疲れさまでした～！";
		close;
	default:
		mes "[ラマディン]";
		mes "なにかご用ですか？";
		mes "ここはディアリース様の私有地です。";
		mes "むやみに入ってこないで下さい。";
		next;
		warp "comodo.gat",187,164;
		end;
	}
}

cmd_in01.gat,33,33,1	script	控室#sign	66,{
	end;
OnInit:
	waitingroom "DANCE　DANCE!!",20,"控室#sign::OnStart",1;
	end;
OnStart:
	disablewaitingroomevent;
	getwaitingpcid '@accid;
	if(attachrid('@accid)) {
		set getvariableofnpc('charid,"SignDance"),getcharid(3);
		hideonnpc "SignDanceStep#1";
		hideonnpc "SignDanceStep#2";
		hideonnpc "SignDanceStep#3";
		hideonnpc "SignDanceStep#4";
		hideonnpc "SignDanceStep#5";
		donpcevent "SignDance::OnStart";
		set @sign_dance,0;
		warp "cmd_in01.gat",16,15;
	}
	else
		enablewaitingroomevent;
	end;
}

cmd_in01.gat,0,0,0	script	SignDance	-1,{
	function StepReset {
		for(set '@i,1; '@i <= 5; set '@i,'@i+1) {
			if('@i != getarg(0))
				hideonnpc "SignDanceStep#" +'@i;
		}
		if(getarg(0))	//0以外は指定タイル出現
			hideoffnpc "SignDanceStep#" +getarg(0);
		return;
	}
	end;
OnStart:
	initnpctimer;
	end;
OnTimer2000:
	announce "ではテストを始めます。頑張って！",9;
	end;
OnTimer4000:
	announce " 左上～♪ : |＼",9;
	set 'count,1;
	StepReset 4;
	end;
OnTimer6000:
	announce " 右下～♪ : ＼|",9;
	set 'count,2;
	StepReset 2;
	end;
OnTimer8000:
	announce " 左下から右上へ～♪ : |／　／|",9;
	set 'count,3;
	StepReset 5;
	end;
OnTimer11000:
	announce " そのまま下へ～♪ : ＼|",9;
	set 'count,5;
	StepReset 2;
	end;
OnTimer13000:
	announce " 左下、右上、左上、真ん中でクルリン♪ : |／　／|　|＼　◎",9;
	set 'count,6;
	StepReset 5;
	end;
OnTimer18000:
	announce " 左下、右下、また左下～♪ : |／　＼|　|／",9;
	set 'count,10;
	StepReset 5;
	end;
OnTimer21000:
	announce " 右下、中央、右下～♪ : ＼|　◎　＼|",9;
	set 'count,13;
	StepReset 2;
	end;
OnTimer24000:
	announce " 左下、左上、右上、右下、真ん中～♪ : |／　|＼　／|　＼|　◎",9;
	set 'count,16;
	StepReset 5;
	end;
OnTimer30000:
	announce " 左下、右上、左上、右下～♪ : |／　／|　|＼　＼|",9;
	set 'count,21;
	StepReset 5;
	end;
OnTimer34000:
	announce " 右上、右下、はいリピート～♪ : ／|　＼|　／|　＼|",9;
	set 'count,25;
	StepReset 3;
	end;
OnTimer38000:
	announce " 左上、右上、真ん中、右上、左下、右下で決め♪ : |＼　／|　◎　／|　|／　＼|",9;
	set 'count,29;
	StepReset 4;
	end;
OnTimer44000:
	StepReset 0;
	announce "お疲れさまでした～♪",9;
	end;
OnTimer46000:
	stopnpctimer;
	if(attachrid('charid)) {
		if(SIGN_QUE == 30) {
			if(@sign_dance < 30)
				set SIGN_QUE,32;
			else if(@sign_dance < 34)
				set SIGN_QUE,33;
			else
				set SIGN_QUE,34;
		}
		set @sign_dance,0;
	}
	areawarp "cmd_in01.gat",12,12,20,20,"cmd_in01.gat",29,33;
	set 'charid,0;
	set 'count,0;
	hideoffnpc "SignDanceStep#1";
	hideoffnpc "SignDanceStep#2";
	hideoffnpc "SignDanceStep#3";
	hideoffnpc "SignDanceStep#4";
	hideoffnpc "SignDanceStep#5";
	enablewaitingroomevent "控室#sign";
	end;
}

cmd_in01.gat,16,16,0	script	SignDanceStep#1	139,1,1,{
	end;
OnTouch:
	if(getvariableofnpc('charid,"SignDance") != getcharid(3)) {
		warp "cmd_in01.gat",29,33;
		end;
	}
	set '@num,strnpcinfo(2);
	switch('@num) {
		case 1: soundeffect "effect\\sign_center.wav",0; break;
		case 2: soundeffect "effect\\sign_down.wav",0; break;
		case 3: soundeffect "effect\\sign_right.wav",0; break;
		case 4: soundeffect "effect\\sign_up.wav",0; break;
		case 5: soundeffect "effect\\sign_left.wav",0; break;
	}
	set @sign_dance,@sign_dance+1;
	hideonnpc;
	switch(getvariableofnpc('count,"SignDance")) {
	case 8:
	case 13:
	case 19:
	case 30:
		hideoffnpc "SignDanceStep#1";
		break;
	case 10:
	case 14:
	case 18:
	case 23:
	case 25:
	case 27:
	case 33:
		hideoffnpc "SignDanceStep#2";
		break;
	case 3:
	case 6:
	case 17:
	case 21:
	case 26:
	case 29:
	case 31:
		hideoffnpc "SignDanceStep#3";
		break;
	case 7:
	case 16:
	case 22:
		hideoffnpc "SignDanceStep#4";
		break;
	case 11:
	case 32:
		hideoffnpc "SignDanceStep#5";
		break;
	default:
		break;
	}
	set getvariableofnpc('count,"SignDance"),getvariableofnpc('count,"SignDance")+1;
	end;
}
cmd_in01.gat,16,11,0	duplicate(SignDanceStep#1)	SignDanceStep#2	139,1,3
cmd_in01.gat,21,16,0	duplicate(SignDanceStep#1)	SignDanceStep#3	139,3,1
cmd_in01.gat,16,21,0	duplicate(SignDanceStep#1)	SignDanceStep#4	139,1,3
cmd_in01.gat,11,16,0	duplicate(SignDanceStep#1)	SignDanceStep#5	139,3,1

//==============================================================
// 第1部 - ベーカーの試練
//==============================================================
alberta_in.gat,125,101,5	script	太っちょな商人	807,{
	if(SIGN_QUE < 35) {
		mes "[ベーカー]";
		mes "うーん、こうだから、プロンテラは";
		mes "こんな感じで、ジュノーは……";
		mes "ううん、頭が痛い……";
		mes "ブツブツ……";
		close;
	}
	switch(SIGN_QUE) {
	case 35:
		mes "[ベーカー]";
		mes "うーん、本当に困ったな……";
		mes "うん？　なんだお前。";
		next;
		if(select("あ、なんでもないです","メッツさんの事で来たんですが")==1) {
			mes "[ベーカー]";
			mes "今は忙しいんだ。";
			mes "職探しなら、執事に相談して。";
			close;
		}
		mes "[ベーカー]";
		mes "ああ、そうなのか。";
		mes "今、少しばかり忙しいので、";
		mes "また後で来てくれるかい？";
		set SIGN_QUE,36;
		close;
	case 36:
		mes "[ベーカー]";
		mes "ふむふむ、そうかそうか。";
		mes "ディアリースのテストも";
		mes "クリアしたんだ。";
		mes "その証拠、見せてくれるかい？";
		next;
		if(select("少々お待ちください","これを……")==1) {
			mes "[ベーカー]";
			mes "早くね。僕は他の人達みたいに";
			mes "暇じゃないんだ。";
			close;
		}
		mes "[ベーカー]";
		mes "ちょっと拝見……";
		next;
		mes "[ベーカー]";
		mes "お、ぴったりだ。";
		mes "おし、それじゃあね……";
		mes "これから品物を一つ君に預けるから";
		mes "それを配達してきて。";
		next;
		mes "[ベーカー]";
		mes "かなり貴重な品物だから、";
		mes "気をつけて扱ってよ。";
		mes "失くしたりしたら、試練は不合格。";
		mes "やり直しは無しだからね。";
		mes "詳しいことは執事に聞いてくれるかい。";
		set SIGN_QUE,37;
		close;
	case 37:
	case 38:
	case 39:
		mes "[ベーカー]";
		mes "ああ、この仕事は、この人に……";
		mes "うーん……ちょっと難しいかな……";
		mes "あ、仕事については執事に聞いて。";
		close;
	case 40:
		mes "[ベーカー]";
		mes "ああ、配達は終わったかい？";
		mes "もう一つ、仕事があるんだ。";
		mes "また執事に説明してあるから、";
		mes "お願いね。";
		set SIGN_QUE,41;
		close;
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:
	case 50:
	case 51:
		mes "[ベーカー]";
		mes "引き受けた仕事を終わらせてから";
		mes "来てくれるかい。";
		mes "ちょっと今、忙しくてね。";
		close;
	case 52:
		mes "[ベーカー]";
		mes "ああ、おかえり！";
		mes "連絡は受けてるよ。";
		mes "見ず知らずの人を、これだけ親身に";
		mes "手伝えるなんて、メッツ爺さんの目に";
		mes "間違いはなかったって事かな。";
		next;
		mes "[ベーカー]";
		mes "できることなら、僕が試練を";
		mes "受けたかったくらいなんだけどね。";
		mes "最近はアマツやコンロンとの交易も";
		mes "増えてて、どうしても無理があって。";
		next;
		mes "[ベーカー]";
		mes "サイリンも、アマツで縁があって";
		mes "雇った子でね。彼女の兄もプロンテラで";
		mes "雇ってもらえたことだし、僕の事の";
		mes "ように嬉しくって。";
		next;
		mes "[ベーカー]";
		mes "さぁ、これをどうぞ。";
		mes "僕が最後です。";
		mes "これを持って、メッツ爺さんに";
		mes "報告するといいよ。そこから先は";
		mes "メッツ爺さんと君次第かな。";
		set SIGN_QUE,53;
		getitem 7177,1;
		if(checkre()) {
			if(BaseLevel >= 90) getexp 2000,0;
			else if(BaseLevel >= 80) getexp 1500,0;
			else if(BaseLevel >= 70) getexp 1100,0;
			else if(BaseLevel >= 60) getexp 800,0;
			else getexp 500,0;
		}
		else {
			if(BaseLevel >= 90) getexp 20000,0;
			else if(BaseLevel >= 80) getexp 15000,0;
			else if(BaseLevel >= 70) getexp 11000,0;
			else if(BaseLevel >= 60) getexp 8000,0;
			else getexp 5000,0;
		}
		close;
	default:
		mes "[ベーカー]";
		mes "やぁ、最近どう？";
		mes "できることなら、僕が試練を";
		mes "受けたかったくらいなんだけどね。";
		mes "僕だって、あれがいったいなんなのか";
		mes "知りたいさ！";
		close;
	}
}

alberta_in.gat,114,178,5	script	変わっている執事	109,{
	if(SIGN_QUE < 37) {
		mes "[マハト]";
		mes "ワッハッハ、";
		mes "ようこそいらっしゃいました。";
		mes "こちらはアルベルタ一の貿易商、";
		mes "アルスキィ家の邸宅です。";
		next;
		mes "[マハト]";
		mes "私は、こちらの執事をしている";
		mes "マハトと申します。";
		mes "何かご用があるなら、遠慮なく";
		mes "言ってください。手伝えることなら";
		mes "なんでもいたしましょう。";
		mes "ワッハッハ～。";
		close;
	}
	switch(SIGN_QUE) {
	case 37:
		mes "[マハト]";
		mes "おお、ご主人様からお話は";
		mes "伺っております。とても急を要する";
		mes "お仕事ですので、手短に。";
		mes "これから渡す品物を";
		mes "^FF0000リービッヒ^000000様に";
		mes "お届けください。";
		next;
		mes "[マハト]";
		mes "リービッヒ様は一つの土地に";
		mes "定住されない方ですので、";
		mes "まずは彼を探すところから";
		mes "始めていただかなければなりません。";
		mes "そういえば以前、他国におられると";
		mes "耳にしました。";
		next;
		mes "[マハト]";
		mes "そして、この品はくれぐれも";
		mes "無くさないようお願いいたします。";
		next;
		mes "-あなたは珍しい石を受け取った-";
		mes "-見た目は普通の石だが、この石には";
		mes "あなたの名前が刻まれている-";
		set SIGN_QUE,38;
		getitem2 7049,1,1,0,0,254,0,getcharid(0),(getcharid(0)>>16)&0xffff;
		close;
	case 38:
		mes "[マハト]";
		mes "リービッヒ様はまだ見つかりませんか？";
		mes "お預けした品は、代用品が";
		mes "ございませんので、無くさないよう";
		mes "お気をつけください。";
		next;
		mes "[マハト]";
		mes "それでは、お気をつけて。";
		close;
	case 39:
		mes "[マハト]";
		mes "お帰りなさいませ。";
		mes "おお、リービッヒ様が";
		mes "見つかりましたか。";
		mes "それでは、ご主人様に連絡して";
		mes "おきますので、そちらにも";
		mes "顔を出してあげてくださいませ。";
		delitem 7181,1;
		set SIGN_QUE,40;
		close;
	case 40:
		mes "[マハト]";
		mes "いや、いつもは私がしていた仕事でね。";
		mes "今回は助かりました。";
		close;
	case 41:
		mes "[マハト]";
		mes "うん？　ご用ですかな？";
		next;
		if(select("何でもないです","もう一つ仕事があると……")==1) {
			mes "[マハト]";
			mes "ワッハッハ、そうですか。";
			mes "ではまた。";
			close;
		}
		mes "[マハト]";
		mes "ほう、そうですか。";
		mes "ふむふむ、そうですね……";
		next;
		mes "[マハト]";
		mes "うーん、そうだ。";
		mes "最近、^FF0000サイリン^000000が困っている";
		mes "様子なのです。彼女の相談に";
		mes "のってあげてくれますか？";
		set SIGN_QUE,42;
		close;
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:
	case 50:
		mes "[マハト]";
		mes "それでは、頼みましたよ。";
		mes "人を助ける！";
		mes "良いことではありませんか。";
		mes "ホッホ。";
		mes "それに、サイリンはかわいいと";
		mes "思いませんか？ホッホッホ。";
		close;
	case 51:
		mes "[マハト]";
		mes "どうでした、サイリンは？";
		mes "ふむふむ……おおう、そうでしたか。";
		mes "ありがとうございます。";
		mes "ご主人様には、私からご報告して";
		mes "おきましょう。";
		next;
		mes "[マハト]";
		mes "それでは幸運をお祈りいたします。";
		set SIGN_QUE,52;
		close;
	default:
		mes "[マハト]";
		mes "まったく、ご主人様には困った……";
		mes "あれだけ仕事の最中だけでも服装は";
		mes "整えてくださいと言っても、聞いて";
		mes "くれません。身なりくらい、もっと";
		mes "シャンとしてもらいたいものです。";
		close;
	}
}

yuno.gat,330,100,4	script	騎士	734,{
	if(SIGN_QUE < 38) {
		mes "[リービッヒ]";
		mes "私は珍しい品を集めるのが趣味です。";
		mes "それで、この付近では入手困難な物を";
		mes "探したりもしますが……";
		next;
		mes "[リービッヒ]";
		mes "そういう品が欲しい時は、アルベルタの";
		mes "アルスキィ氏を頼ったりします。";
		mes "少々値は張りますが、確実に手に";
		mes "入れてくれますからね。";
		close;
	}
	if(SIGN_QUE > 38) {
		mes "[リービッヒ]";
		mes "この前はありがとうございました。";
		mes "おかげで、コレクションがまた";
		mes "増えましたよ。";
		close;
	}
	mes "[リービッヒ]";
	mes "おや、もしかしてアルスキィ氏の所から";
	mes "いらしたのですか？";
	mes "では、頼んでいた品は持ってきて";
	mes "いただけましたか？";
	next;
	switch(select("いいえ、違います","他の事で忙しいです","はい、そうです")) {
	case 1:
		mes "[リービッヒ]";
		mes "おや、申し訳ありません。";
		close;
	case 2:
		mes "[リービッヒ]";
		mes "そうですか……";
		mes "ここからアルベルタまでは、";
		mes "遠いですしね……勘違いして";
		mes "申し訳ありません。注文していた品の";
		mes "到着が遅いので、少し冷静さを欠いて";
		mes "いるようです。";
		close;
	case 3:
		if(countitem(7049)) {
			mes "[リービッヒ]";
			mes "これがそうですか？";
			mes "うーん、確かに！";
			next;
			mes "[リービッヒ]";
			mes "届けてくださって、本当に";
			mes "ありがとうございます。";
			mes "アルベルタからここまで";
			mes "大変だったでしょう。";
			next;
			mes "[リービッヒ]";
			mes "それでは、この領収書を";
			mes "ベーカーさんに届けてください。";
			mes "ありがとうございました。";
			delitem 7049,1;
			set SIGN_QUE,39;
			getitem 7181,1;
			if(checkre()) {
				if(BaseLevel >= 90) getexp 1100,0;
				else if(BaseLevel >= 80) getexp 700,0;
				else if(BaseLevel >= 70) getexp 400,0;
				else if(BaseLevel >= 60) getexp 200,0;
				else getexp 100,0;
			}
			else {
				if(BaseLevel >= 90) getexp 11000,0;
				else if(BaseLevel >= 80) getexp 7000,0;
				else if(BaseLevel >= 70) getexp 4000,0;
				else if(BaseLevel >= 60) getexp 2000,0;
				else getexp 1000,0;
			}
			close;
		}
		mes "[リービッヒ]";
		mes "おぉ、そうですか。";
		mes "ところで、品物は？";
		next;
		if(select("安全な場所に保管してあります","無くしました")==1) {
			mes "[リービッヒ]";
			mes "そうなのですか。ハハハ。";
			mes "では、待っていますから、";
			mes "ここに持ってきていただけませんか？";
			close;
		}
		mes "[リービッヒ]";
		mes "え？";
		mes "……………………";
		mes "本当ですか？";
		next;
		if(select("はい","冗談です")==1) {
			mes "[リービッヒ]";
			mes "………………";
			mes "………………はぁ";
			mes "そうですか……わかりました";
			mes "ベーカーさんには、そのように";
			mes "お伝えしておきます。";
			mes "それでは。";
			close;
		}
		mes "[リービッヒ]";
		mes "アハハ……いやはや、";
		mes "びっくりしたじゃないですか。";
		mes "ハハハ。では、待っていますから、";
		mes "ここに持ってきていただけませんか？";
		close;
	}
}

alberta_in.gat,154,171,5	script	メイド	758,{
	if(SIGN_QUE < 38) {
		mes "[サイリン]";
		mes "あ、すみません。今掃除中ですので、";
		mes "そこ、どいていただけますか？";
		mes "あの、それと家に入ってくるときは";
		mes "履き物を綺麗に拭いてから";
		mes "上がっていただけないでしょうか？";
		close;
	}
	switch(SIGN_QUE) {
	case 38:
		mes "[サイリン]";
		mes "リービッヒさんですか？";
		mes "度々、変わった注文をされる方です。";
		mes "最後の注文は……ミョルニール山脈の";
		mes "方だったと思います。";
		next;
		mes "[サイリン]";
		mes "今はどこにいらっしゃるのか、";
		mes "わかりません。うーん……この間が";
		mes "ミョルニール山脈で、その前が確か";
		mes "あそこだったから……今度は";
		mes "シュバルツバルド共和国の方へ";
		mes "行ったかもしれません。";
		close;
	case 39:
	case 40:
	case 41:
	case 42:
		mes "[サイリン]";
		mes "ああ、どうしよう……";
		mes "はぁ……";
		mes "…………";
		mes "あ?!";
		mes "どうして人の話をこっそり";
		mes "聞いているのですか?!";
		next;
		mes "[サイリン]";
		mes "忙しいんです。";
		mes "出て行ってください！";
		if(SIGN_QUE == 42)
			set SIGN_QUE,43;
		close;
	case 43:
		mes "[サイリン]";
		mes "はぁ……どうしよう……";
		next;
		if(select("通りすぎる","あの、マハトさんから言われて……")==1) {
			mes "[サイリン]";
			mes "うん、1人で悩んでてもしかたない。";
			mes "仕事しよう……";
			close;
		}
		mes "[サイリン]";
		mes "え、執事のマハトさまが？";
		mes "いったい、何故？";
		next;
		menu "何か悩んでいるのかと心配していました",-;
		emotion 15;
		mes "[サイリン]";
		mes "あら……";
		mes "あの、では……ちょっと手伝って";
		mes "いただけないでしょうか？";
		mes "よろしくお願いします。";
		next;
		mes "[サイリン]";
		mes "あの、実はもうすぐ私の兄の";
		mes "誕生日なんです。でも、仕事が";
		mes "忙しくって、時間がなくて……";
		mes "それで悩んでいました。";
		next;
		mes "[サイリン]";
		mes "前に兄に会った時、元気が";
		mes "なかったんです。なので、元気がでる";
		mes "^FF0000精力剤^000000というお薬を";
		mes "プレゼントしようかなと";
		mes "思っているのですが……";
		next;
		mes "[サイリン]";
		mes "あの、もし良かったら、私の代わりに";
		mes "手に入れてきてくれないでしょうか？";
		mes "あの、嫌でしたら、無理にとは……";
		next;
		switch(select("面倒だな","ちょっと考えさせて","喜んで手伝うよ",)) {
		case 1:
			mes "[サイリン]";
			mes "そうですか。";
			mes "あの、もし考えが変わりましたら";
			mes "お願いできますか？";
			mes "それでは、御機嫌よう。";
			set SIGN_QUE,44;
			close;
		case 2:
			mes "[サイリン]";
			mes "はい、構いません。";
			mes "お待ちしてますね。";
			set SIGN_QUE,45;
			close;
		case 3:
			break;
		}
		break;
	case 44:
		mes "[サイリン]";
		mes "あ、考えなおしていただけましたか？";
		mes "手伝っていただけますか？";
		mes "あの、お手伝いしていただけるなら";
		mes "わずかですが、お礼もしますし……";
		next;
		if(select("どうしよう","手伝うよ")==2)
			break;
		mes "[サイリン]";
		mes "そうですか。";
		mes "あの、もし考えが変わりましたら";
		mes "お願いできますか？";
		mes "それでは、ごきげんよう。";
		close2;
		emotion 9;
		end;
	case 45:
		mes "[サイリン]";
		mes "あ、どうでしょう？";
		mes "手伝っていただけますか？";
		mes "あの、お手伝いしていただけるなら";
		mes "わずかですが、お礼もしますし……";
		next;
		if(select("まだ悩んでる","手伝います")==2)
			break;
		mes "[サイリン]";
		mes "そう……ですか";
		mes "あの、あまり時間がないんです……";
		mes "考え直すなら、お早めに……";
		close;
	case 46:
	case 47:
		mes "[サイリン]";
		mes "無理なことを頼んでいるのは";
		mes "承知しています。";
		mes "でも、どうかお願いします。";
		close;
	case 48:
		if(countitem(7044) < 1) {
			mes "[サイリン]";
			mes "あ、どうでした？";
			mes "なにかわかりましたか？";
			close;
		}
		mes "[サイリン]";
		mes "お待ちしていましたー。";
		mes "うわ、本当にありがとうございます。";
		next;
		mes "[サイリン]";
		mes "あの、これをプロンテラ城に勤めている";
		mes "兄に持っていっていただけませんか？";
		mes "兄の名前は^FF0000ルーイン^000000です。";
		next;
		mes "[サイリン]";
		mes "あ、それと……";
		mes "これも一緒にお願いします。";
		set SIGN_QUE,49;
		getitem 7183,1;
		close;
	case 49:
		mes "[サイリン]";
		mes "兄はプロンテラ城に勤めております。";
		mes "あの、あまり時間がないので……";
		mes "どうかお願いします。";
		close;
	case 50:
		mes "[サイリン]";
		mes "ああ、ありがとうございます！";
		next;
		mes "[サイリン]";
		mes "あの、これ少ないですが……";
		mes "ほんの気持ちです。";
		set SIGN_QUE,51;
		getitem 525,3;
		next;
		emotion 31;
		close;
	default:
		mes "[サイリン]";
		mes "ご主人さまは、お部屋を汚すことは";
		mes "ないのですが、書類がとにかく多くて。";
		mes "この書類の管理だけでも一苦労です。";
		close;
	}
	//43～45の続き
	mes "[サイリン]";
	mes "え？　本当ですか？";
	mes "えへ……";
	mes "ありがとうございます。";
	mes "本当は、とっても心配だったんです。";
	next;
	mes "[サイリン]";
	mes "えっと、そのお薬ですが、";
	mes "アルデバランの錬金術ギルドと";
	mes "関係あると聞いています。ただ、私も";
	mes "それ以上はわからなくて……";
	next;
	mes "[サイリン]";
	mes "お願いする立場なのに、これしか";
	mes "情報がなくて申し訳ありません。";
	mes "あの、それでもよろしくお願いします。";
	set SIGN_QUE,46;
	close;
}

alde_alche.gat,169,162,7	script	アルケミスト	749,{
	if(SIGN_QUE < 46) {
		mes "[メルカ]";
		mes "錬金術の究極の形は";
		mes "賢者の石だというが、アルケミスト";
		mes "全員が、それを目指している";
		mes "わけじゃない。";
		mes "私のように、他の研究をしている者も";
		mes "いっぱいいるさ。";
		next;
		if(select("……","どんな研究ですか？")==1) {
			mes "[メルカ]";
			mes "色んな意味で、賢者の石は幻想に";
			mes "過ぎないかもしれないからね。";
			mes "今まで数多くのアルケミストが、";
			mes "それを目標にしてきたけど、";
			mes "未だに現実のものになって";
			mes "いないしさ。";
			close;
		}
		mes "[メルカ]";
		mes "フフ、私の研究は一味違うぞ。";
		next;
		mes "[メルカ]";
		mes "詳しい事は秘密。";
		mes "いやー、最近秘密を知りたがる人が";
		mes "多くて困っているんだ。";
		close;
	}
	switch(SIGN_QUE) {
	case 46:
		mes "[メルカ]";
		mes "うん、なんか用かい？";
		mes "用がないなら、出ていって";
		mes "くれないかな。";
		next;
		if(select("精力剤を作れる人を探しているのですが","あ、ごめんなさい")==2) {
			mes "[メルカ]";
			mes "謝ることができる、その心がけは";
			mes "良いと思うよ。";
			mes "じゃ、できるだけ静かに";
			mes "出て行ってもらえるかな。";
			close;
		}
		mes "[メルカ]";
		mes "なに？　君、どうしてそれを?!";
		mes "そのことを知っている人は、";
		mes "そう多くないはずなのに……";
		mes "ううん……それで？";
		next;
		if(select("ちょっと聞いてみたかっただけです","精力剤を作ってもらえませんか？")==1) {
			mes "[メルカ]";
			mes "……";
			mes "大人をからかうのは関心しないな。";
			mes "さっさと帰りなさい。";
			close;
		}
		mes "[メルカ]";
		mes "ううん……ここまで訪ねてきたって";
		mes "ことは、ある程度確信を持っている";
		mes "ということかな。";
		next;
		mes "[メルカ]";
		mes "よし、作ってあげよう。";
		mes "ただし、材料は君が集めてくるんだよ。";
		next;
		mes "[メルカ]";
		mes "それで、材料だ。";
		mes "ちゃんとメモでも取るんだよ。";
		next;
		mes "[メルカ]";
		mes "^FF0000ローヤルゼリー 10個";
		mes "ハチ蜜 20個";
		mes "くまの足の裏 30個";
		mes "ヒナレの葉 1個";
		mes "メント 1個";
		mes "空きビン 1個^000000";
		next;
		mes "[メルカ]";
		mes "いいかい？　もう一回言うよ。";
		next;
		mes "[メルカ]";
		mes "^FF0000ローヤルゼリー 10個";
		mes "ハチ蜜 20個";
		mes "くまの足の裏 30個";
		mes "ヒナレの葉 1個";
		mes "メント 1個";
		mes "空きビン 1個^000000";
		next;
		mes "[メルカ]";
		mes "それじゃ、頼んだよ。";
		set SIGN_QUE,47;
		close;
	case 47:
		mes "[メルカ]";
		mes "材料、集めてきたかい？";
		next;
		if(select("まだです","持ってきました")==1) {
			mes "[メルカ]";
			mes "私は作るだけだからね。";
			mes "材料はしっかり、君が集めてきなよ。";
			close;
		}
		mes "[メルカ]";
		mes "そうか。";
		mes "じゃあ、見せてくれるかい？";
		next;
		if(countitem(526) < 10 || countitem(518) < 20 || countitem(948) < 30 || countitem(520) < 1 || countitem(708) < 1 || countitem(713) < 1) {
			mes "[メルカ]";
			mes "おや、足りないよ。";
			mes "もう一度、材料を教えるからね。";
			mes "きちんと数をそろえてくるように。";
			next;
			mes "[メルカ]";
			mes "^FF0000ローヤルゼリー 10個";
			mes "ハチ蜜 20個";
			mes "くまの足の裏 30個";
			mes "ヒナレの葉 1個";
			mes "メント 1個";
			mes "空きビン 1個^000000";
			close;
		}
		mes "[メルカ]";
		mes "ふむふむ……";
		mes "よし、全部揃ってるね。";
		mes "じゃあ、作ってあげよう……";
		mes "と言いたいところだけど、条件がある！";
		next;
		mes "[メルカ]";
		mes "これを作るのは今回だけ。";
		mes "どんなに頭を下げても、";
		mes "2度目はないからね。";
		mes "あと、若干手数料をもらうよ。";
		next;
		if(Zeny < 10000) {
			mes "[メルカ]";
			mes "手数料は10,000zeny。";
			mes "それだけ持ってきてくれたら、";
			mes "作ってあげるよ。";
			close;
		}
		mes "[メルカ]";
		mes "手数料は10,000zeny。";
		mes "そんな大金ってわけじゃないだろう？";
		mes "よし、じゃあちょっと待ってな。";
		next;
		mes "-メルカはてきぱきと材料を";
		mes "試験管で交ぜたり熱したりし始めた-";
		next;
		mes "……";
		next;
		mes "……";
		mes "…………";
		next;
		mes "……";
		mes "…………";
		mes "………………";
		next;
		mes "……";
		mes "…………";
		mes "………………";
		mes "……………………";
		next;
		if(rand(50) == 0) {
			delitem 526,10;
			delitem 518,20;
			delitem 948,30;
			delitem 520,1;
			delitem 708,1;
			delitem 713,1;
			misceffect 306;
			mes "[メルカ]";
			mes "…………………………";
			mes "あ……";
			mes "しまった……";
			mes "失敗してしまったみたいだ。";
			mes "悪いけど、また材料を集めてきて";
			mes "もらえるかい？";
			close;
		}
		misceffect 305;
		mes "[メルカ]";
		mes "よし、成功！";
		mes "これを持っていきなさい。";
		mes "あ、でもこれだけは注意して。";
		mes "これは短時間に多用してはいけないよ。";
		mes "いいね。";
		next;
		mes "[メルカ]";
		mes "一度にたくさん飲む必要もないよ。";
		mes "血圧が高くなりすぎて、";
		mes "倒れてしまうからね。";
		set Zeny,Zeny-10000;
		delitem 526,10;
		delitem 518,20;
		delitem 948,30;
		delitem 520,1;
		delitem 708,1;
		delitem 713,1;
		set SIGN_QUE,48;
		getitem 7044,1;
		close;
	default:
		mes "[メルカ]";
		mes "精力剤は、使う人によって薬にも";
		mes "毒にもなるんだ。";
		mes "だから、気をつけるんだよ。";
		close;
	}
}

prt_castle.gat,107,58,5	script	兵士	105,{
	if(SIGN_QUE == 49 && countitem(7044) && countitem(7183)) {
		mes "[ルーイン]";
		mes "え？";
		mes "妹から？";
		mes "何でしょうか……？";
		mes "ま、まさか、妹になにか?!";
		next;
		menu "妹さんから誕生日プレゼントです",-;
		mes "[ルーイン]";
		mes "え？";
		mes "あ、そういえばもうすぐ";
		mes "私の誕生日でした！";
		mes "あはは、すっかり忘れてました。";
		next;
		emotion 0;
		mes "[ルーイン]";
		mes "ありがとうございます。";
		mes "わざわざ、こんなところまで";
		mes "何をくれたんだろう……";
		next;
		mes "[ルーイン]";
		mes "あ、これは……";
		mes "前に言ってたの、覚えてたんだ……";
		next;
		mes "[ルーイン]";
		mes "あの、ありがとうございます。";
		mes "お礼をしたいのですが、";
		mes "勤務中なので……";
		next;
		mes "[ルーイン]";
		mes "あ、そうだ。";
		mes "少し休んでいったらいかがでしょう？";
		mes "なに、ここはいっぱい人が";
		mes "出入りしますから、少しくらい";
		mes "バレませんよ。";
		delitem 7044,1;
		delitem 7183,1;
		set SIGN_QUE,50;
		percentheal 100,100;
		next;
		mes "[ルーイン]";
		mes "妹には、私からも連絡しておきます。";
		mes "これ以上、お手数をおかけするわけには";
		mes "いきませんし、今日は本当に";
		mes "ありがとうございました。";
		close;
	}
	if(SIGN_QUE > 49) {
		mes "[ルーイン]";
		mes "あ、ようこそ。";
		mes "先日はありがとうございました。";
		mes "あれは、ありがたく使わせて";
		mes "いただきましたよ。";
		mes "え、何に使ったって？";
		mes "あはは、それは秘密です。";
		close;
	}
	mes "[ルーイン]";
	mes "ようこそ、おいでくださいました。";
	mes "城内は迷うことがありますから、";
	mes "気をつけてください。";
	close;
}

alberta.gat,98,202,5	script	警備兵	105,{
	if(SIGN_QUE > 51) {
		mes "[フルブ]";
		mes "いらっしゃいませ！";
		mes "この間から、ベーカー様のお顔が";
		mes "とても明るいのです。";
		mes "なんだか、大きな肩の荷が下りたと";
		mes "おっしゃってました。";
		close;
	}
	mes "[フルブ]";
	mes "こちらはアルスキィ家の邸宅です。";
	mes "ご用件は、まず私を通していただくよう";
	mes "お願いします。";
	if(SIGN_QUE < 35)
		close;
	next;
	if(select("ベーカーさんはいらっしゃいますか？","失礼しました")==1) {
		mes "[フルブ]";
		mes "ベーカー様は、つい先日旅行から";
		mes "戻られたところです。";
		close;
	}
	mes "[フルブ]";
	mes "そうですか。";
	mes "それでは、こちらも失礼します。";
	close;
}

alberta.gat,43,49,5	script	貧しそうな商人	89,{
	if(SIGN_QUE < 35) {
		mes "[マチェン]";
		mes "あぁ、どうしよう……";
		mes "私の家はどうなっちゃうんだろう……";
		next;
		mes "[マチェン]";
		mes "アルスキィ家が来て以来、もう";
		mes "にっちもさっちも";
		mes "いかなくなっちゃった……";
		mes "ご先祖様に合わせる顔がないよ……";
		close;
	}
	if(SIGN_QUE < 52) {
		mes "[マチェン]";
		mes "ベーカーさんは、いったいどうやって";
		mes "財産を増やしているんだろう……";
		next;
		if(select("ベーカーさん？","ベーカーさんを知っていますか？")==1) {
			mes "[マチェン]";
			mes "ああ……ベーカーさんについてなら";
			mes "私に聞かないほうがいいですよ。";
			mes "私の家は、アルスキィ家が来る前は";
			mes "アルベルタ一の商家だったんですよ。";
			next;
			mes "[マチェン]";
			mes "アルスキィ家がアルベルタに来たのは";
			mes "50年くらい前だったかな。";
			next;
			mes "[マチェン]";
			mes "最初はそうでもなかったんだけど、";
			mes "前の当主になってから、急に財産が";
			mes "増えだしたんだ。";
			next;
			mes "[マチェン]";
			mes "そして、今の当主になって、更に";
			mes "財産を増やし、今では";
			mes "ミッドガッツでも有数の金持ちに";
			mes "なったのさ。なんか、凄い複雑だよ……";
			close;
		}
		mes "[マチェン]";
		mes "ベーカーさん？";
		mes "ああ、神様の家にでも";
		mes "でかけてるんじゃないの？";
		next;
		menu "…………",-;
		mes "[マチェン]";
		mes "ハハハ、冗談だよ。";
		mes "北の方に大きい屋敷がある。";
		mes "それがこのアルベルタで一番裕福で";
		mes "大きな商家、アルスキィ家の屋敷さ。";
		mes "ベーカーさんは、そこの現当主だよ。";
		next;
		mes "[マチェン]";
		mes "外出してる時もあるけど、";
		mes "この間見たばっかりだから";
		mes "自宅にいるんじゃないかな。";
		close;
	}
	mes "[マチェン]";
	mes "アルスキィ家が単なる守銭奴だったら";
	mes "ここまで大きくはならなかっただろう。";
	mes "きっと、周りの商人達と一緒に";
	mes "頑張ったから、ここまで大きく";
	mes "なったんだ。";
	next;
	mes "[マチェン]";
	mes "とは言え、あまりにも手際が良くて";
	mes "こっちにはにっちもさっちもいかないよ。";
	mes "とほほ……";
	close;
}

//============================================================
// 第2部
//------------------------------------------------------------
geffen_in.gat,159,48,4	script	寂しそうな女性	711,{
	if(SIGN_QUE < 54) {
		mes "[ブレンダ]";
		mes "今日の夕飯は何がいいかしら？";
		mes "うーん……この間教えてもらったのに";
		mes "しようかしら？";
		mes "せっかく教えてもらったのに、";
		mes "まだ一度も作っていないし……";
		close;
	}
	switch(SIGN_QUE) {
	case 54:
		mes "[ブレンダ]";
		mes "何か用ですか？";
		mes "今、ちょうど夕飯の準備で";
		mes "忙しいのですが。";
		mes "それに、知らない人の家に";
		mes "勝手に上がるのはよくないですよ。";
		next;
		input '@str$;
		if('@str$ != "エンゲル・ハワード") {
			emotion 2;
			mes "[ブレンダ]";
			mes "……もう、いったい何のご用ですか？";
			mes "よし、美味しく出来た。";
			mes "さて、ご飯にしようかしら。";
			close;
		}
		mes "[ブレンダ]";
		mes "主人を訪ねていらしたのですね。";
		mes "私達一家は、主人の仕事のため、";
		mes "プロンテラからゲフェンに";
		mes "引っ越してきました。";
		next;
		mes "[ブレンダ]";
		mes "この街を選んだのは、あそこから";
		mes "一番近い街がここだったからです。";
		mes "なのに、もう何日も帰ってこないし、";
		mes "連絡の一言も……";
		next;
		mes "[ブレンダ]";
		mes "彼は、家族のことも忘れて";
		mes "仕事ばっかり……";
		mes "まぁ、有名な鍛冶師ということも";
		mes "あるのでしょうけど……";
		next;
		mes "[ブレンダ]";
		mes "主人を探すのなら、その前に";
		mes "一度娘に会ってくださいませんか。";
		mes "パパにあげたいものがあると";
		mes "言っていましたので……";
		set SIGN_QUE,55;
		close;
	case 55:
	case 56:
		mes "[ブレンダ]";
		mes "ルンルン～。";
		mes "うん、美味しく出来た。";
		mes "この間作ってあげたら、娘がとても";
		mes "気に入ってしまい、また食べたいって";
		mes "言うんです。";
		close;
	case 57:
		mes "[ブレンダ]";
		mes "主人には会えました？";
		mes "あの、病気とかしていませんでしたか？";
		mes "ちゃんとご飯は食べていたでしょうか？";
		next;
		emotion 9;
		mes "[ブレンダ]";
		mes "ああ、私ったら何を……";
		mes "でも、元気なら良かった……";
		mes "ゆっくり、連絡を待つとします。";
		close;
	case 58:
	case 59:
	case 60:
	case 61:
		if(countitem(7278) < 1) {
			mes "[ブレンダ]";
			mes "連絡するだなんて……";
			mes "………………";
			close2;
			emotion 9;
			end;
		}
		mes "[ブレンダ]";
		mes "ありがとうございます……";
		mes "彼も相変わらずなのね。";
		mes "家事が出来なくて心配だけど、";
		mes "私はそんな彼を愛しているのです。";
		next;
		mes "[ブレンダ]";
		mes "私も、何かできることを";
		mes "やってみようと思います。";
		mes "ありがとうございました。";
		mes "……あ、娘がお話ししたいと";
		mes "言っていました。";
		mes "少しだけ相手してくださいませんか？";
		delitem 7278,1;
		set SIGN_QUE,SIGN_QUE+4;
		close;
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:
	case 68:
	case 69:
		mes "[ブレンダ]";
		mes "あの、私が言うのもなんですが、";
		mes "主人はホルグレンさんや";
		mes "アラガムさんにも教えていたほどの";
		mes "腕を持っています。";
		mes "信じていいと思いますよ。";
		close;
	default:
		mes "[ブレンダ]";
		mes "私は、娘と一緒に主人を待つことに";
		mes "します。家族として、主人の仕事を";
		mes "理解しているつもりですから。";
		mes "でも、感情がついていかない時も";
		mes "あります。そんなものですよ……";
		mes "あなたも良い旅を。";
		close;
	}
}

geffen_in.gat,171,42,3	script	かわいい子供	703,{
	if(SIGN_QUE < 54) {
		emotion 28;
		mes "[リア]";
		mes "ぐすん、パパに会いたいなぁ。";
		mes "いつ会えるかなぁ、ぐすん。";
		close;
	}
	switch(SIGN_QUE) {
	case 54:
		mes "[リア]";
		mes "ママが美味しいもの、作って";
		mes "くれてるんだもん。";
		mes "元気ださなきゃ。";
		next;
		emotion 18;
		mes "[リア]";
		mes "うん、あのね、ママの料理は";
		mes "とっても美味しいんだー。";
		mes "へへッ。";
		close;
	case 55:
		mes "[リア]";
		mes "私のパパは、世界で一番の";
		mes "鍛冶屋さんなんだって。";
		mes "今は、弟子に仕事を任せて";
		mes "世界を旅しながら、めずらしい";
		mes "コウセキをさがしてるんだって。";
		mes "すごいでしょー！";
		next;
		if(select("あれ、それは？","弟子？")==1) {
			mes "[リア]";
			mes "これ？";
			mes "あのね、パパにおてがみ書いてるの。";
			mes "ママがね、パパを探してくれる";
			mes "お" +(Sex? "兄": "姉")+ "さんがいるって教えてくれたの。";
			mes "だからね、パパにね、おてがみ";
			mes "わたしてもらうんだぁ。えへへッ。";
			close;
		}
		mes "[リア]";
		mes "んとね、ホルグレンおじちゃんとか、";
		mes "アラガムおじちゃんがよく遊んで";
		mes "くれるの。";
		mes "でもね、パパと遊ぶほうがずっと";
		mes "おもしろいの。でもね、でもね、";
		mes "パパ帰ってこないの……ぐすん。";
		next;
		if(select("パパに会いたい？","パパだって会いたいって思ってるさ")==1) {
			mes "[リア]";
			mes "会いたい。";
			mes "でもね、パパはお仕事なの。";
			mes "忙しいの。";
			close;
		}
		emotion 9;
		mes "[リア]";
		mes "うんうん、だって、リアのパパだもん。";
		mes "でも、パパ忙しいの。";
		next;
		mes "[リア]";
		mes "それでね、だからね、";
		mes "おてがみ書いたの。";
		mes "パパにあげたいんだけどね、";
		mes "どこにいるかわからないの。";
		next;
		if(select("…………","よし、届けてあげる")==2) {
			mes "[リア]";
			mes "お" +(Sex? "兄": "姉")+ "ちゃん、誰？";
			mes "知らない人にたのんじゃ";
			mes "いけないってママが言ってたの。";
			close;
		}
		mes "[ブレンダ]";
		mes "リア、そのお" +(Sex? "兄": "姉")+ "ちゃんに頼んでみたら？";
		mes "そのお" +(Sex? "兄": "姉")+ "ちゃん、パパを";
		mes "探してるんだって。";
		next;
		mes "[リア]";
		mes "ほんと、ほんとう!?";
		mes "わーい!!";
		next;
		mes "[リア]";
		mes "えっとね、じゃあね。";
		mes "これ、おねがいします。";
		mes "きっとパパにとどけてね。";
		mes "ぜったいだよ！";
		set SIGN_QUE,56;
		getitem 7276,1;
		close;
	case 56:
	case 57:
	case 58:
	case 59:
	case 60:
	case 61:
		if(rand(2)) {
			mes "[リア]";
			mes "あのね、パパはね、お客さんのものを";
			mes "こわしたことがないんだよ。";
			mes "ホルグレンおじちゃんとか、";
			mes "パパみたいになりたいって";
			mes "がんばってるんだって。";
			close;
		}
		mes "[リア]";
		mes "あのね、お手紙、ちゃんとパパに";
		mes "とどけてね。";
		close;
	case 62:
	case 63:
	case 64:
	case 65:
		mes "[リア]";
		mes "わー、お手紙とどけてくれて";
		mes "ありがとう！";
		mes "お礼に、私のたからものあげるね。";
		mes "お" +(Sex? "兄": "姉")+ "ちゃん、ありがとう！";
		set SIGN_QUE,SIGN_QUE+4;
		getitem 529,10;
		close;
	default:
		mes "[リア]";
		mes "あのね、パパはぶきやぼうぐを絶対に";
		mes "こわしたりしないんだよ。";
		mes "すごいんだよ、とくべつなの。";
		close;
	}
}

mjo_dun02.gat,88,295,4	script	魂を燃やす男	85,{
	if(SIGN_QUE > 1 && SIGN_QUE < 54) {
		if(countitem(1002) < 1) {
			emotion 32;
			mes "[エンゲル・ハワード]";
			mes "何だ、おまえ？";
			mes "ここは私の作業部屋なんだ。";
			mes "出て行ってくれないか。";
			mes "今大事なところなんだ。";
			close2;
			warp "mjo_dun02.gat",372,346;
			end;
		}
		mes "[エンゲル・ハワード]";
		mes "ううん、やはり少し足りないな。";
		mes "どうしようか……";
		next;
		mes "[エンゲル・ハワード]";
		mes "あ、お前。鉄鉱石を持ってるな。";
		mes "すまん、急いでるんだ。";
		mes "1個もらえないか？";
		next;
		if(select("いいですよ","嫌です")==1) {
			mes "[エンゲル・ハワード]";
			mes "お、助かる。ありがとう。";
			mes "いつか必ず、この恩は返すよ。";
			delitem 1002,1;
			getexp 10,0;
			close;
		}
		mes "[エンゲル・ハワード]";
		mes "そうか。だったら悪いが";
		mes "出て行ってくれないか。";
		mes "ここは私の作業部屋なんだ。";
		close2;
		emotion 32;
		end;
	}
	switch(SIGN_QUE) {
	case 0:
	case 1:
	case 54:
	case 55:
		mes "[エンゲル・ハワード]";
		mes "邪魔しないでくれ。";
		mes "今大事なところなんだ。";
		close2;
		emotion 32;
		end;
	case 56:
		mes "[エンゲル・ハワード]";
		mes "家族に最後に連絡してから、";
		mes "だいぶ経ったな……";
		mes "そろそろ連絡しないと";
		mes "まずいだろうな……";
		next;
		mes "[エンゲル・ハワード]";
		mes "うん？　私に何か？";
		mes "用がないなら、邪魔しないで欲しいな。";
		if(countitem(7276) < 1)
			close;
		next;
		switch(select("あの、お願いがあって……","リアちゃんの手紙を持ってきました","ごめんなさい")) {
		case 1:
			mes "[エンゲル・ハワード]";
			mes "今は忙しいんだ。";
			mes "他人の頼みを聞く余裕はないね。";
			mes "他をあたってくれ。";
			close;
		case 2:
			break;
		case 3:
			mes "[エンゲル・ハワード]";
			mes "わかればいい。";
			mes "じゃあな。";
			close;
		}
		mes "[エンゲル・ハワード]";
		mes "娘から？";
		mes "なに、本当か？";
		mes "早く見せてくれ！";
		next;
		mes "[エンゲル・ハワード]";
		mes "ほうー……うんうん……";
		mes "ハハッ、そうか";
		mes "やつが、ハハハッ。";
		mes "ほー……";
		next;
		mes "[エンゲル・ハワード]";
		mes "元気が出てきたよ。ありがとう。";
		mes "ところで、これだけの為に、わざわざ";
		mes "訪ねてきたんじゃないだろう？";
		mes "頼みでもあるのかな？";
		mes "できることなら聞いてやろう。";
		next;
		menu "実は……",-;
		mes "[エンゲル・ハワード]";
		mes "うん？";
		mes "それは……";
		mes "うん、そうか……";
		next;
		mes "[エンゲル・ハワード]";
		mes "前に、お師匠から聞いたことがある。";
		mes "この世には、大地から生まれるのでは";
		mes "なく、空から生れ落ちてくる鉱物が";
		mes "あるそうだ。そんな空の鉱物の中には";
		mes "とても美しいものがあると言っていた。";
		next;
		mes "[エンゲル・ハワード]";
		mes "中でも一番美しく、涙のような石があり";
		mes "人々はそれを神の涙と呼んだと言う。";
		next;
		mes "[エンゲル・ハワード]";
		mes "でもこれは……";
		mes "この紋様は……それに、この断面は……";
		next;
		mes "[エンゲル・ハワード]";
		mes "これは、外部からの力によって";
		mes "割れたのではなく、内部から";
		mes "なんらかの力が加わって割れたようだ。";
		mes "ふむ……";
		next;
		mes "[エンゲル・ハワード]";
		mes "つまり、私にこれを修復して";
		mes "欲しいんだね？";
		mes "いいだろう。このような機会は、";
		mes "一生に一度あるかないかだ。";
		next;
		mes "[エンゲル・ハワード]";
		mes "だが、これは生半可な材料では";
		mes "修復できない。必要なものは、ほとんど";
		mes "手元にあるが、それでも足りないものが";
		mes "いくつかある。それを集めてきて";
		mes "くれないか。";
		next;
		mes "[エンゲル・ハワード]";
		mes "いいかい。";
		mes "^FF0000携帯用溶鉱炉5個^000000、";
		mes "^FF0000オリデオコンの金槌2個^000000、";
		mes "そして^FF0000金敷^000000だ。";
		mes "金敷は高級なものほど良い。";
		mes "成功しやすくなるからね。";
		next;
		mes "[エンゲル・ハワード]";
		mes "本当は、エンペリウムの金敷が";
		mes "一番良いんだが、今ちょうど手元に";
		mes "なくってね。それに、そう簡単に手に";
		mes "入るものでもないし。あ、かけらは";
		mes "私が預かっておこう。";
		mes "修復の準備を始めておく。";
		next;
		mes "[エンゲル・ハワード]";
		mes "入口まで戻るのは大変だろう。";
		mes "近道から帰るといい。";
		delitem 7276,1;
		delitem 7177,7;
		set SIGN_QUE,57;
		close2;
		warp "mjo_dun02.gat",371,344;
		end;
	case 57:
		mes "[エンゲル・ハワード]";
		mes "成功率は金敷に左右される。";
		mes "それじゃあ、何を持って来たか";
		mes "見せてもらえるかな。";
		next;
		if(countitem(612) < 5 || countitem(615) < 2 || (countitem(986) < 1 && countitem(987) < 1 && countitem(988) < 1 && countitem(989) < 1)) {
			if(rand(6)) {
				mes "[エンゲル・ハワード]";
				mes "ちゃんと覚えたね？";
				mes "それほど珍しいものでもないし、";
				mes "今度は忘れないようにね。";
				close;
			}
			mes "[エンゲル・ハワード]";
			mes "頼んだものは持ってきてくれたかな？";
			mes "何、まだ？";
			next;
			mes "[エンゲル・ハワード]";
			mes "え、必要なものを忘れた？";
			mes "うーん、あんな簡単なことも";
			mes "覚えられないのか……。もう1回";
			mes "教えてあげるから、今度は頼んだよ。";
			next;
			mes "[エンゲル・ハワード]";
			mes "いいかい。";
			mes "^FF0000携帯用溶鉱炉5個^000000、";
			mes "^FF0000オリデオコンの金槌2個^000000、";
			mes "そして^FF0000金敷^000000だ。";
			mes "金敷は高級なものほど良い。";
			mes "成功率が上がるからね。";
			close;
		}
		if(countitem(986)) {
			mes "[エンゲル・ハワード]";
			mes "金敷か。";
			mes "かなり心細いが、いいだろう。";
			mes "それじゃあ、修復作業に入るぞ。";
			set '@anvil,0;
		}
		else if(countitem(987)) {
			mes "[エンゲル・ハワード]";
			mes "オリデオコンの金敷か。";
			mes "少し心細いが、いいだろう。";
			mes "それじゃあ、修復作業に入るか。";
			set '@anvil,1;
		}
		else if(countitem(988)) {
			mes "[エンゲル・ハワード]";
			mes "黄金の金敷か。";
			mes "うん、これならやれるだろう。";
			mes "それじゃあ、修復作業に入るか。";
			set '@anvil,2;
		}
		else if(countitem(989)) {
			mes "[エンゲル・ハワード]";
			mes "これはエンペリウムの金敷じゃ";
			mes "ないか！　ハハッ、よし！";
			mes "これならよっぽど運に見放されない限り";
			mes "修復は成功するだろう。";
			mes "それじゃあ、修復作業に入るか。";
			set '@anvil,3;
		}
		next;
		mes "[エンゲル・ハワード]";
		mes "かなり時間がかかるから、その間、";
		mes "この手紙を家族に持って行って";
		mes "くれないか？";
		mes "迷惑をかけて悪いけど、";
		mes "修復の代金だとでも思って";
		mes "頼まれてくれないか。";
		delitem 612,5;
		delitem 615,2;
		delitem 986+'@anvil,1;
		set SIGN_QUE,58+'@anvil;
		getitem 7278,1;
		close;
	case 58:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
		mes "[エンゲル・ハワード]";
		mes "ん、まだ作業中だ。";
		mes "まだかなりかかるから、その間に";
		mes "手紙を頼んだよ。";
		close;
	case 66: //金敷
		set '@result,63;
		break;
	case 67: //オリデオコンの金敷
		set '@result,33;
		break;
	case 68: //黄金の金敷
		set '@result,10;
		break;
	case 69: //エンペリウムの金敷
		set '@result,0;
		break;
	case 70:
		if(countitem(612) < 5 || countitem(615) < 2 || (countitem(986) < 1 && countitem(987) < 1 && countitem(988) < 1 && countitem(989) < 1)) {
			if(rand(6)) {
				mes "[エンゲル・ハワード]";
				mes "ちゃんと覚えたね？";
				mes "それほど珍しいものでもないし、";
				mes "今度は忘れないようにね。";
				close;
			}
			mes "[エンゲル・ハワード]";
			mes "頼んだものは持ってきてくれたかな？";
			mes "何、まだ？";
			next;
			mes "[エンゲル・ハワード]";
			mes "え、必要なものを忘れた？";
			mes "うーん、あんな簡単なことも";
			mes "覚えられないのか……。もう1回";
			mes "教えてあげるから、今度は頼んだよ。";
			next;
			mes "[エンゲル・ハワード]";
			mes "いいかい。";
			mes "^FF0000携帯用溶鉱炉5個^000000、";
			mes "^FF0000オリデオコンの金槌2個^000000、";
			mes "そして^FF0000金敷^000000だ。";
			mes "エンペリウムの金敷が一番いいけど、";
			mes "入手が難しいから、黄金でいいよ。";
			close;
		}
		if(countitem(986) || countitem(987)) {
			mes "[エンゲル・ハワード]";
			mes "金敷やオリデオコンの金敷だと";
			mes "どうしても成功率が下がってしまうよ。";
			mes "いいのかい？";
			next;
			mes "[エンゲル・ハワード]";
			mes "うーん……やはり心配だ。";
			mes "悪いけど、黄金の金敷を持ってきて";
			mes "くれないかな。頼んだよ。";
			close;
		}
		else if(countitem(988)) {
			mes "[エンゲル・ハワード]";
			mes "ありがとう、黄金の金敷だね。";
			set '@anvil,988;
		}
		else if(countitem(989)) {
			mes "[エンゲル・ハワード]";
			mes "これはエンペリウムの金敷じゃないか！";
			set '@anvil,989;
		}
		mes "よし、準備は出来てるんだ。";
		mes "すぐに取り掛かろう。";
		mes "モンスターが来たら、そっちは";
		mes "頼んだよ。";
		next;
		mes "ゴシゴシ、カンカン";
		mes "トンカン、トンカン、トンカン";
		mes "ザザ、ザッ、ザ、ゴシゴシ……";
		next;
		misceffect 101;
		next;
		mes "カンカン、トントン、ガンガン";
		mes "スチャ、スチャ、チャンチャン";
		next;
		misceffect 101;
		next;
		mes "ドンダン、ドンガン";
		mes "ポンポン、トントン";
		mes "チャッチャッチャッ";
		next;
		misceffect 101;
		next;
		mes "ウィィィィィィィィン";
		mes "ギュィィィィィィィン";
		next;
		misceffect 101;
		next;
		mes "[エンゲル・ハワード]";
		mes "ふぅ……";
		mes "もう少しだ。";
		next;
		misceffect 101;
		next;
		mes "カンカン、カンカンカン";
		next;
		misceffect 101;
		next;
		misceffect 99;
		next;
		mes "[エンゲル・ハワード]";
		mes "ホッ、終わった……";
		mes "稀に見る難しさだったよ。";
		mes "でも、見てくれ。この幻想的な光を。";
		mes "かけらだけでも美しかったが、";
		mes "やはりこのほうが数倍美しい。";
		mes "いや、引き受けてよかったよ。";
		next;
		mes "[エンゲル・ハワード]";
		mes "私が魂を込めて修復したんだ。";
		mes "大切にしてくれよ。";
		delitem 612,5;
		delitem 615,2;
		delitem '@anvil,1;
		set SIGN_QUE,71;
		getitem 7178,1;
		misceffect 94,"";
		close;
	case 139:
		mes "[エンゲル・ハワード]";
		mes "はは、そっちはうまくやったようだね。";
		mes "目を見ればわかるよ。";
		mes "ところで、また何か用かい？";
		next;
		menu "はい、お願いがあって来ました",-;
		mes "[エンゲル・ハワード]";
		mes "そうなのか。";
		mes "今度はどんな厄介な品を持って";
		mes "来たのかな？";
		next;
		menu "これです。",-;
		mes "[エンゲル・ハワード]";
		mes "これは……！";
		mes "こうして見ているだけでも、";
		mes "凄い力を感じるよ。";
		mes "よくこんな品を";
		mes "次々と見つけてくるね。";
		next;
		mes "[エンゲル・ハワード]";
		mes "こんな品、一生に1回出会えれば";
		mes "ラッキーってなもんなのに、2回も";
		mes "触れることができるなんてね。";
		next;
		mes "[エンゲル・ハワード]";
		mes "こいつはかなり時間がかかりそうだ……";
		mes "どれくらい時間がかかるか、予想も";
		mes "できないよ。";
		delitem 7314,1;
		set SIGN_QUE,140;
		set SIGN_SUBQUE,gettime(3)/2+1;
		close;
	case 140:
		if((SIGN_SUBQUE*2+2)%24 != gettime(3) && (SIGN_SUBQUE*2+3)%24 != gettime(3)) {
			mes "[エンゲル・ハワード]";
			mes "まだ終わってないんだ。";
			mes "心配なのはわかるけど、もう少し";
			mes "かかりそうだよ。";
			close;
		}
		mes "[エンゲル・ハワード]";
		mes "お、ちょうど良かった。";
		mes "今、仕事が終わったところだよ。";
		mes "いやいや、大変だったけど、";
		mes "こんな機会、一生に一度あるか";
		mes "ないかだし、頑張らせてもらったよ。";
		next;
		mes "[エンゲル・ハワード]";
		mes "ほら、これだ。";
		mes "おかげで、なんか自分がまた";
		mes "一回り大きくなれた気がするよ。";
		mes "ハハッ";
		set SIGN_QUE,141;
		set SIGN_SUBQUE,0;
		getitem 2644,1;
		close;
	default:
		if(SIGN_QUE < 139) {
			mes "[エンゲル・ハワード]";
			mes "そっちはうまくやってるかい？";
			mes "助けが必要になったら、遠慮なく";
			mes "おいでよ。";
			close;
		}
		mes "[エンゲル・ハワード]";
		mes "旅も悪くないけど、家族がいるなら";
		mes "ちゃんと連絡は取ったほうがいいぞ。";
		mes "自分が帰る所は、家族のもとなんだ。";
		close2;
		emotion 9;
		end;
	}
	//66～69の続き
	if(rand(100) < '@result) {
		emotion 19;
		mes "[エンゲル・ハワード]";
		mes "ああ、おかえり……";
		mes "実は、言いにくいんだが……";
		next;
		mes "[エンゲル・ハワード]";
		if(SIGN_QUE < 68)
			mes "やはり、この金敷では難しかった。";
		else {
			mes "作業中に、モンスターに襲われてね。";
			mes "作業に夢中で、モンスターが";
			mes "現われたのに気がつかなかったのも";
			mes "あるんだけど、失敗してしまったんだ。";
		}
		next;
		mes "[エンゲル・ハワード]";
		mes "あ、そんなに落ち込まないでくれ。";
		mes "スタージュエルのかけらは無事だ。";
		mes "ただ、他の材料が全部だめに";
		mes "なってしまった。悪いが、もう1度";
		mes "材料を集めてきてもらえるかい。";
		next;
		mes "[エンゲル・ハワード]";
		mes "^FF0000携帯用溶鉱炉5個^000000、";
		mes "^FF0000オリデオコンの金槌2個^000000、";
		mes "そして^FF0000金敷^000000だ。";
		if(SIGN_QUE < 68) {
			mes "エンペリウムの金敷とは言わないけど";
			mes "できれば黄金の金敷を持ってきて";
			mes "もらえないかな。";
		}
		else
			mes "もう一回、黄金の金敷を頼むよ。";
		set SIGN_QUE,70;
		close;
	}
	mes "[エンゲル・ハワード]";
	mes "おかえり。手紙は渡してくれたかい？";
	mes "仕事に熱中していると、どうしても";
	mes "家族が後回しになってしまってね……";
	next;
	mes "[エンゲル・ハワード]";
	mes "君は結婚したら、ちゃんと家族を";
	mes "大事にしてあげることだ。";
	mes "男だろうと、女だろうと、家族の中に";
	mes "ちゃんと役割ってもんがあるんだ。";
	next;
	mes "[エンゲル・ハワード]";
	mes "よし、修復できた。";
	mes "ほら、これだ。";
	next;
	set SIGN_QUE,71;
	getitem 7178,1;
	misceffect 94,"";
	next;
	mes "[エンゲル・ハワード]";
	mes "稀に見る難しさだったよ。";
	mes "でも、見てくれ。この幻想的な光を。";
	mes "かけらだけでも美しかったが、";
	mes "やはりこのほうが数倍美しい。";
	mes "いや、引き受けてよかったよ。";
	next;
	mes "[エンゲル・ハワード]";
	mes "私が魂を込めて修復したんだ。";
	mes "大切にしてくれよ。";
	close;
}

gef_tower.gat,118,36,4	script	怒っているウィザード	64,{
	if(SIGN_QUE != 72) {
		emotion 32;
		mes "[ドータ]";
		mes "ぶつぶつ、ぶつぶつぶつ……";
		mes "ぶつぶつ……";
		mes "あのやろ～～～～～～～!!!!";
		close;
	}
	emotion 32;
	mes "[ドータ]";
	mes "ふん、魔法を使えない奴が、";
	mes "どうしてこんな所に来た？";
	next;
	input '@str$;
	if('@str$ != "メッツ" && '@str$ != "スタージュエル") {
		mes "[ドータ]";
		mes "はぁ？";
		mes "なんのことかわからないな。";
		mes "ほら、ふざけてないで、とっとと帰れ。";
		close;
	}
	mes "[ドータ]";
	mes "うん？";
	if('@str$ == "スタージュエル")
		mes "スタージュエル？";
	mes "メッツさんのことで来たのか。";
	mes "……………";
	next;
	emotion 9;
	next;
	emotion 9;
	next;
	emotion 7;
	mes "だぁーーーーーっ!!!!";
	next;
	emotion 32;
	mes "[ドータ]";
	mes "くそ、また思い出してしまったじゃ";
	mes "ないか！　ぶつぶつ…………";
	mes "探してる奴なら、^FF0000コモドの方で";
	mes "新しい部族^000000が発見されたとかで";
	mes "そっちに行ってしまったよ！";
	set SIGN_QUE,73;
	close;
}

umbala.gat,163,256,3	script	原住民	781,{
	if(UM_1QUE < 3) {
		mes "[？？？？]";
		mes "ウムバウムバ？";
		mes "ウムバ、ウムバ～!!";
		mes "ウムバババ、ウムバ～";
		mes "バババ!!!!";
		close;
	}
	if(SIGN_QUE < 73) {
		emotion 2;
		mes "[ラウタン]";
		mes "スマイルマスク～、スマイルマスク～";
		mes "スマイルマスク～、お面、面めん～";
		mes "お肉も好き好き、お肉にっく～";
		close;
	}
	if(SIGN_QUE > 73) {
		mes "[ラウタン]";
		mes "お面、お面～";
		mes "スマイルマスク～";
		mes "スマイル、スマイル～";
		close;
	}
	mes "[ラウタン]";
	mes "最近、村に来た人？";
	mes "うんとね、知ってるけど……";
	mes "スマイルマスク～、スマイルマスク～。";
	next;
	if(countitem(2278) < 1) {
		mes "[ラウタン]";
		mes "あのね、私、スマイルマスクが";
		mes "好きなの。";
		mes "くれたら教えてあげる。";
		close;
	}
	mes "[ラウタン]";
	mes "あ、スマイルマスクだ～!!";
	mes "お面、お面、お面！";
	mes "ね、ね、ちょうだい！";
	next;
	if(select("はい、あげる","あげない")==2) {
		mes "[ラウタン]";
		mes "ブウ～、嫌い嫌い！";
		mes "スマイルマスク、";
		mes "ちょうだいちょうだい！";
		close;
	}
	mes "[ラウタン]";
	mes "うわーい、ありがとう、ありがとう！";
	next;
	mes "[ラウタン]";
	mes "あのね、この間、変な服を着た人が";
	mes "あそこの大きな木の中に入ってったのを";
	mes "見たの。でもね、出てくるのは";
	mes "見てないの。";
	delitem 2278,1;
	set SIGN_QUE,74;
	close;
}

um_in.gat,152,125,5	script	気難しそうな男	121,{
	if(SIGN_QUE < 74) {
		emotion 29;
		mes "[サイオン]";
		mes "ククク、これをこのようにして……";
		mes "あれをああすれば……";
		mes "ククク……";
		next;
		emotion 6;
		mes "[サイオン]";
		mes "うん、誰だお前？";
		mes "どうやってここに入ってきた。";
		mes "すぐ出てけ。";
		close2;
		warp "umbala.gat",125,151;
		end;
	}
	switch(SIGN_QUE) {
	case 74:
		emotion 29;
		mes "[サイオン]";
		mes "ククク、これをこのようにして……";
		mes "あれをああすれば……";
		mes "ククク……";
		next;
		emotion 6;
		mes "[サイオン]";
		mes "うん、誰だお前？";
		mes "どうやってここに入ってきた。";
		mes "さぁ、とっとと消えたまえ。";
		next;
		switch(select("メッツさんの用件で……","申し訳ありません","あのこれを……","…………")) {
		case 1:
			mes "[サイオン]";
			mes "何、メッツ？";
			mes "だったら、メッツの使いという";
			mes "証拠を見せたまえ。";
			close;
		case 2:
			emotion 32;
			mes "[サイオン]";
			mes "口だけじゃなくて、態度で示さんかい。";
			mes "ここは一般人が気軽に来る";
			mes "場所ではない。";
			mes "さぁ、とっとと消えたまえ。";
			close;
		case 3:
			break;
		case 4:
			misceffect 124;
			mes "[サイオン]";
			mes "お前は、他人の家に無断で";
			mes "上がりこんで来て、喋りもせんのか。";
			mes "ここはお前の家か?!　わがままで";
			mes "失礼で情けない奴め！　出て行け！";
			mes "カァーッ!!!!";
			close2;
			misceffect 17,"";
			percentheal -30,0;
			end;
		}
		mes "[サイオン]";
		mes "ほう、それは……";
		next;
		emotion 23;
		next;
		mes "[サイオン]";
		mes "おう、それは!!!";
		mes "神の涙ではないか。";
		mes "いよいよ完成したか。";
		next;
		mes "[サイオン]";
		mes "ククク……となると";
		mes "私も約束を守らねばな。";
		mes "神の涙……俗にスタージュエルと";
		mes "呼ばれておる。";
		next;
		mes "[サイオン]";
		mes "うすうす感じておるかもしれんが、";
		mes "このスタージュエルの内部には";
		mes "人間の視力では見ることの出来ない";
		mes "文字が存在する。文字だということは";
		mes "判っておるが、内容や意味に関しては";
		mes "通常の方法では解読不可能だ。";
		next;
		mes "[サイオン]";
		mes "しかし、このスタージュエル、実は";
		mes "特殊な紙に反応する。";
		mes "その紙とは、古い本に使われている";
		mes "ような紙だ。";
		next;
		mes "[サイオン]";
		mes "いいか、古い紙だぞ。";
		mes "このスタージュエルの内容を";
		mes "読めるようにするには、";
		mes "10枚程いるかな。";
		mes "いいか、10枚程集めてから";
		mes "出直してくるがいい。";
		set SIGN_QUE,75;
		close;
	case 75:
		mes "[サイオン]";
		mes "集めて来たか？";
		mes "見せなさい。";
		next;
		if(countitem(1097) < 1) {
			mes "[サイオン]";
			mes "こらっ!!!!";
			mes "古い紙を持って来いと言っただろうが！";
			next;
			mes "[サイオン]";
			mes "さっさと持ってこんか！";
			mes "カァーッ!!";
			next;
			misceffect 17,"";
			percentheal -30,0;
			next;
			warp "umbala.gat",125,151;
			end;
		}
		mes "[サイオン]";
		mes "よし、これなら使えそうだ。";
		mes "この^FF0000古い本のページ^000000なら";
		mes "スタージュエルも反応するだろう。";
		next;
		if(countitem(1097) < 7) {
			mes "[サイオン]";
			mes "……ん？";
			mes "枚数が足りないな。";
			mes "反応はあるが、文字が浮かび上がるには";
			mes "まだ足りない。もっと集めて来なさい。";
			close;
		}
		mes "[サイオン]";
		mes "よし、ちょっと待て。";
		mes "ウムウム……こうして、";
		mes "ああしてと……";
		mes "ゴシゴシ、ゴシゴシ。";
		next;
		misceffect 72;
		next;
		mes "[サイオン]";
		mes "よし、予想通りだ！";
		mes "古い本のページに反応して、";
		mes "スタージュエルに文字が";
		mes "浮かび上がったぞ！";
		mes "ククク……";
		next;
		mes "[サイオン]";
		mes "これでメッツとの約束は守った。";
		mes "あいつに、これ以上私に迷惑を";
		mes "かけるのは止めろと伝えてくれたまえ。";
		mes "これ以上迷惑をかけるようなら……";
		mes "ククク……";
		delitem 1097,7;
		set SIGN_QUE,76;
		getitem 7275,1;
		close;
	case 76:
		mes "[サイオン]";
		mes "さっさとメッツに伝えるがいい。";
		mes "これ以上迷惑をかけるなとな。";
		close;
	default:
		mes "[サイオン]";
		mes "勝手に他人の家に入ってくるな。";
		mes "カァーッ!!!!";
		close;
	}
}

alberta.gat,165,83,4	script	気難しそうなお爺さん	755,{
	if(SIGN_QUE < 77) {
		mes "[フランク]";
		mes "雨が降るかいな……";
		mes "ああ、いかん。最近、目がどうもなぁ。";
		mes "このまま老いて、いずれ死なねば";
		mes "ならないのか……";
		close;
	}
	switch(SIGN_QUE) {
	case 77:
	case 78:
		if(SIGN_QUE < 78 || countitem(2203) < 1 || countitem(7275) < 1) {
			mes "[フランク]";
			mes "最近、目が本当にいかんわい。";
			mes "老いには勝てんか。";
			mes "ん、なんだ？";
			mes "立ち聞きとは失礼な！";
			mes "ほれほれ、さっさと立ち去らんかい!!";
			set SIGN_QUE,78;
			close;
		}
		mes "[フランク]";
		mes "なんじゃい……ん？";
		mes "これをわしに？";
		mes "ふはは、最近の若者にしては";
		mes "気が利いてるじゃないか。";
		next;
		mes "[フランク]";
		mes "うん、ぴったしじゃ。";
		mes "そうじゃ、この眼鏡の礼をさせて";
		mes "くれんかな？";
		while(1) {
			next;
			switch(select("ゲフェンの隠された力って？","スタージュエルについて","古代言語文の解読を")) {
			case 1:
				mes "[フランク]";
				mes "ゲフェンに存在する強大な力か。";
				mes "わしも詳しくは知らないが、";
				mes "ゲフェンタワーは確かに単純な";
				mes "建築物ではない。";
				mes "これは予想じゃが、何かを封じるために";
				mes "作られたのではないだろうか。";
				next;
				mes "[フランク]";
				mes "タワー前の噴水も、何かの役割を";
				mes "担っていると感じるんじゃが。";
				mes "ただ、あまり興味がなくてな。";
				mes "詳しく調査したことはないんじゃ。";
				next;
				mes "[フランク]";
				mes "しかし、あのゲフェンタワーの";
				mes "存在だけでも、あの場所になにか";
				mes "あるのは確かじゃろうて。";
				break;
			case 2:
				mes "[フランク]";
				mes "スタージュエルとな……";
				mes "そう、神の涙とも呼ばれるそれじゃ。";
				mes "神の涙は単なる宝石にあらず。";
				next;
				mes "[フランク]";
				mes "もちろん、本当に神が流した涙という";
				mes "わけではない。そのような意志を秘めた";
				mes "存在だと伝えられておるが、誰もそれを";
				mes "見たことがない。そもそも、";
				mes "スタージュエルさえ実在するかどうか";
				mes "怪しいしな。";
				break;
			case 3:
				mes "[フランク]";
				mes "うん、これは？";
				mes "この古代言語を解読してくれと";
				mes "いうことか。ほほう、これは。";
				mes "ほっほっ、久しぶりに面白そうな";
				mes "相手じゃわい。まぁ、わし以外に";
				mes "これの解読は無理じゃろうて。";
				next;
				mes "[フランク]";
				mes "これはまさしく、古代の神が";
				mes "使ったとされる上級言語じゃ。";
				mes "読むだけでも非常に困難じゃが、";
				mes "そのあとの解読にも時間が";
				mes "かかりそうじゃ。";
				next;
				mes "[フランク]";
				mes "よし！";
				mes "さっそく、お前がくれたこの眼鏡で";
				mes "読んでみるとしよう。";
				mes "また後で来るがいい。";
				delitem 2203,1;
				delitem 7275,1;
				set SIGN_QUE,79;
				close;
			}
		}
	case 79:
		if(rand(50)) {
			mes "[フランク]";
			mes "ん……おおう、お前か。";
			mes "この古代言語、資料が少ないのもあって";
			mes "解読にはまだ時間がかかりそうじゃ。";
			mes "もう少し時間をくれんか。";
			close;
		}
		mes "[フランク]";
		mes "おう、ちょうど解読が終わったぞ。";
		mes "かなり難しい単語が多くてな、";
		mes "こんなに時間がかかってしまった。";
		mes "しかも、この内容は象徴的すぎて、";
		mes "どういう意味か理解できないかも";
		mes "知れんぞ。";
		next;
		mes "[フランク]";
		mes "さぁ、翻訳文はこれじゃ。";
		mes "久しぶりに見た古代言語だったが";
		mes "楽しませてもらったぞ。";
		mes "ホッホッ。";
		set SIGN_QUE,80;
		getitem 7274,1;
		close;
	default:
		mes "[フランク]";
		mes "この世には、まだ発見されていない";
		mes "遺跡や不思議な力が眠っておる。";
		mes "そして、それらがある限り、";
		mes "そういうものを追い求める人が";
		mes "いるもんじゃ。";
		close;
	}
}

gef_fild07.gat,182,241,0	script	#himinnwarp	111,1,1,{
	if(SIGN_QUE != 80 || countitem(907) < 4 || countitem(953) < 12 || countitem(7013) < 365)
		end;
	mes "^6B8E23あなたの懐にある";
	mes "スタージュエルが微かに輝き始めた。";
	mes "ここが門だろうか？";
	mes "近付いてみよう。^000000";
	close;
OnTouch:
	if(SIGN_QUE == 203) {
		mes "何も起こらない……";
		close;
	}
	if(SIGN_QUE > 80) {
		warp "himinn.gat",49,10;
		end;
	}
	if(SIGN_QUE != 80 || countitem(907) < 4 || countitem(953) < 12 || countitem(7013) < 365)
		end;
	misceffect 58,"";
	mes "突然、あなたの懐にある";
	mes "スタージュエルと古木の露、岩の心臓";
	mes "サンゴが強く輝き出した！";
	next;
	misceffect 9,"";
	mes "そして、あなたの体が";
	mes "神秘的な光に包まれた。";
	next;
	misceffect 99,"";
	mes "瞬間、眩い光が一面に広がり";
	mes "あなたは気を失った……";
	next;
	delitem 907,4;
	delitem 953,12;
	delitem 7013,365;
	set SIGN_QUE,81;
	warp "himinn.gat",49,10;
	end;
}

himinn.gat,48,86,5	script	ヴァルキリー	811,{
	if(SIGN_QUE < 81) {

	}
	switch(SIGN_QUE) {
	case 81:
		mes "[ヴァルキリー]";
		mes "ようこそ、聖地へ。";
		mes "あなたこそ、自分の勇気を試すため";
		mes "数多い試練を受ける者……";
		mes "その試練の鍵、スタージュエルを";
		mes "持つ者……";
		next;
		mes "[ヴァルキリー]";
		mes "しかし、勇気を示すには、まだ数多くの";
		mes "難関が待っています。";
		mes "貴方は、これから更に過酷な試練に";
		mes "耐えなければなりません。";
		next;
		mes "[ヴァルキリー]";
		mes "あの御方に選ばれるため、あなたは";
		mes "まだ多くの勇気を示さねばなりません。";
		mes "今まで、数多くの者がそうし、そして";
		mes "そのために倒れてゆきましたが……";
		next;
		mes "[ヴァルキリー]";
		mes "彼らが皆、あの御方に選ばれ、";
		mes "祝福を受けながら生きたくとも……";
		mes "^FF0000重々しく立ちはだかる死を";
		mes "無視し、祝福だけを受けることは";
		mes "できないのです。^000000";
		next;
		mes "[ヴァルキリー]";
		mes "^FF0000自らを隠し生きる者の場所^000000を";
		mes "訪れなさい。";
		mes "彼らは、自分達に成せなかった夢に";
		mes "向かって歩んでいる貴方を見て、";
		mes "妬み怨むでしょう。";
		next;
		mes "[ヴァルキリー]";
		mes "それに打ち勝つことができれば、";
		mes "さらなる試練への扉が開くはずです。";
		mes "そこで証明してください。";
		mes "貴方の力を、貴方の勇気を。";
		next;
		mes "[ヴァルキリー]";
		mes "善悪を見極めるのは、";
		mes "貴方自身です。";
		set SIGN_QUE,82;
		percentheal 100,100;
		if(checkre()) {
			if(BaseLevel > 90) getexp 35000,0;
			else if(BaseLevel > 85) getexp 21000,0;
			else if(BaseLevel > 80) getexp 16000,0;
			else if(BaseLevel > 75) getexp 12000,0;
			else if(BaseLevel > 70) getexp 7000,0;
			else if(BaseLevel > 65) getexp 3500,0;
			else if(BaseLevel > 60) getexp 2000,0;
			else if(BaseLevel > 55) getexp 1200,0;
			else getexp 900,0;
		}
		else {
			if(BaseLevel > 90) getexp 350000,0;
			else if(BaseLevel > 85) getexp 210000,0;
			else if(BaseLevel > 80) getexp 160000,0;
			else if(BaseLevel > 75) getexp 120000,0;
			else if(BaseLevel > 70) getexp 70000,0;
			else if(BaseLevel > 65) getexp 35000,0;
			else if(BaseLevel > 60) getexp 20000,0;
			else if(BaseLevel > 55) getexp 12000,0;
			else getexp 9000,0;
		}
		close2;
		warp "geffen.gat",120,100;
		end;
	case 95:
		mes "[ヴァルキリー]";
		mes "私ができることは、神々の祝福が";
		mes "いつも貴方と共にあるよう、祈るだけ。";
		next;
		mes "[ヴァルキリー]";
		mes "貴方が自分の信念を持ち、目標に";
		mes "向かう為に、私はもちろん、神も";
		mes "貴方に干渉することは出来ません。";
		next;
		mes "[ヴァルキリー]";
		mes "神が望んでいるのは盲目的な";
		mes "追従ではなく、自分で考え、信じる事。";
		next;
		mes "[ヴァルキリー]";
		mes "どうか、歩き続けてください。";
		mes "それを願うこと、それが私が唯一";
		mes "できる事……";
		set SIGN_QUE,96;
		close;
	case 129:
	case 130:
		mes "[ヴァルキリー]";
		mes "貴方は試練に立ち向かい、";
		mes "見事その試練に打ち勝ちました。";
		mes "神々の跡を追いながら、闇に沈む";
		mes "死者の世界で、その光を失うこと無く";
		mes "異世界の侵略から自分の世界を";
		mes "守り抜きました。";
		next;
		mes "[ヴァルキリー]";
		mes "神は、貴方の意志と勇気を見守り、";
		mes "結果、ヴァルハラへ入ることを";
		mes "許されました。しかし、貴方はまだ";
		mes "ミッドガルドに必要な存在。";
		next;
		mes "[ヴァルキリー]";
		mes "よって、貴方にThe Signを授けます。";
		mes "これは、あなたが選ばれた勇者であり、";
		mes "その勇気を示したことの証です。";
		next;
		mes "[ヴァルキリー]";
		mes "貴方が、ミッドガルドを去る日、";
		mes "The Signにより、ヴァルハラへ";
		mes "入ることができるでしょう。";
		set SIGN_QUE,137;
		getitem 7314,1;
		close;
	case 200:
	case 201:
		mes "[ヴァルキリー]";
		mes "貴方の勇気を示しなさい。";
		mes "それが達成されれば、貴方は";
		mes "選ばれし者となるでしょう。";
		close;
	case 202:
		mes "[ヴァルキリー]";
		mes "神々は貴方の意志、選択、そして";
		mes "勇気を見守り、失望しました。";
		mes "貴方に、我等が聖地ヴァルハラに";
		mes "入る資格はありません。";
		next;
		mes "[ヴァルキリー]";
		mes "これ以上、ここを訪れることも";
		mes "許しません。";
		next;
		mes "[ヴァルキリー]";
		mes "それでは……";
		set SIGN_QUE,203;
		close;
	default:
		if(SIGN_QUE < 95) {
			mes "[ヴァルキリー]";
			mes "その後はいかがですか？";
			mes "死者の暮らす場所を旅するのは、";
			mes "生者にとって大変でしょう。";
			close;
		}
		if(SIGN_QUE < 150) {
			mes "[ヴァルキリー]";
			mes "神々があなたを見守っております。";
			mes "貴方の勇気を示してください。";
			mes "それが達成されれば、貴方は";
			mes "選ばれし者となるでしょう。";
			close;
		}
		mes "[ヴァルキリー]";
		mes "ここは運命に導かれた者のみ、";
		mes "入ることが許される場所。";
		mes "いかなる方法で";
		mes "入ったかわかりませんが、";
		mes "すぐに立ち去るが良いでしょう。";
		close2;
		warp "gef_fild07.gat",180,242;
		end;
	}
}

//============================================================
// 第3部
//------------------------------------------------------------
niflheim.gat,313,70,4	script	物静かな女性	90,{
	if(SIGN_QUE < 82) {
		mes "[セリン]";
		mes "あなたは、私が探している";
		mes "人じゃない……";
		mes "ごめんなさい……";
		close;
	}
	switch(SIGN_QUE) {
	case 82:
		mes "[セリン]";
		mes "そこを行く御方、どうか私の話を";
		mes "聞いてください。私は、あなたの";
		mes "ような御方をずっと探していました。";
		mes "あなたのような、自分の勇気を";
		mes "試すために旅を重ねている方を……";
		next;
		mes "[セリン]";
		mes "この死と言う名の、息が詰まりそうな";
		mes "暗闇の中、あなたの姿は強い信念に";
		mes "あふれ明るく輝いています。";
		mes "どうか、私の話を聞いてください。";
		next;
		if(select("私にはやるべきことがあります","ええ、聞きましょう")==1) {
			mes "[セリン]";
			mes "ああ、同情でもいい……";
			mes "私を哀れに思い、ほんのわずかでも";
			mes "時間をいただければと……";
			mes "でも、栄光に向かおうとする";
			mes "その固い意志を、私のような者の為に";
			mes "煩わせることはできませんね……";
			next;
			mes "[セリン]";
			mes "どうか……";
			mes "いつか、時間が出来ましたら……";
			mes "その時にでも私の話を聞いてください。";
			mes "お願いします……";
			close;
		}
		mes "[セリン]";
		mes "ああ、ありがとうございます。";
		next;
		mes "[セリン]";
		mes "私という存在は、この場所に";
		mes "なじめないでいます。そんな私の望みは";
		mes "あなたと一緒にヴァルキリーの試練を";
		mes "受け、ここから出ることです……";
		next;
		if(select("悪いけど……","分かりました、手伝いましょう")==1) {
			mes "[セリン]";
			mes "ああ、同情でもいい……";
			mes "私を哀れに思い、ほんのわずかでも";
			mes "時間をいただければと……";
			mes "でも、栄光に向かおうとする";
			mes "その固い意志を、私のような者の為に";
			mes "煩わせることはできませんね……";
			next;
			mes "[セリン]";
			mes "どうか……";
			mes "いつか、時間が出来ましたら……";
			mes "その時にでも私の話を聞いてください。";
			mes "お願いします……";
			close;
		}
		mes "[セリン]";
		mes "ああ、ありがとうございます。";
		mes "ただ、ここにはあまりにも、私と";
		mes "同じような方が多い……その方も";
		mes "助けていただけないでしょうか？";
		next;
		if(select("分かりました","どうして？")==1) {
			mes "[セリン]";
			mes "ああ、ありがとうございます。";
			mes "きっと彼らは、助けてあげれば";
			mes "深い感謝の気持ちと共に眠りに";
			mes "つくことができるでしょう。";
			next;
			mes "[セリン]";
			mes "本当に感謝します……";
			mes "あなたはなんと心優しいのでしょう。……";
			mes "どうか、彼らにもお言葉をかけて";
			mes "あげてください。";
			mes "私にしてくださったように、どうか。";
			set SIGN_QUE,83;
			close;
		}
		mes "[セリン]";
		mes "ああ、ごめんなさい……";
		mes "私を手伝ってくださるだけでも";
		mes "寛大であるのに、それ以上を";
		mes "お願いするのは、欲深いという";
		mes "ものですね……";
		mes "それでも、感謝します……";
		set SIGN_QUE,84;
		close;
	case 83:
		if(SIGN_SUBQUE < 8) {
			mes "[セリン]";
			mes "どうか、彼らにもお言葉をかけて";
			mes "あげてください。";
			mes "私にしてくださったように、どうか。";
			close;
		}
		mes "[セリン]";
		mes "手伝っていただいて、本当に";
		mes "ありがとうございます。";
		mes "お礼に、この指輪を差し上げます。";
		next;
		mes "[セリン]";
		mes "これは、私に残された最後の宝物……";
		mes "あなたにとっては価値のないものかも";
		mes "しれませんが、どうか、受け取って";
		mes "ください。";
		next;
		mes "[セリン]";
		mes "この指輪は、あなたの目的が";
		mes "達成されるまでは、その指に";
		mes "はめずに大切に持っていて";
		mes "ください。何かの役に立つかも";
		mes "しれません……";
		set SIGN_QUE,85;
		set SIGN_SUBQUE,0;
		getitem 2642,1;
		close;
	case 84:
		mes "[セリン]";
		mes "ここには、他の方々と違う雰囲気の";
		mes "方がいます。その方と話してみて";
		mes "ください。";
		set SIGN_QUE,87;
		close;
	case 85:
		mes "[セリン]";
		mes "村に、吟遊詩人がいます。";
		mes "彼の歌声は甘美で寂しいのです。";
		mes "彼は、あなたのような別の場所から来た";
		mes "人の事を謡います。";
		next;
		mes "[セリン]";
		mes "きっと、彼はあなたの役に立つことを";
		mes "知っています。";
		set SIGN_QUE,86;
		close;
	case 86:
	case 87:
	case 88:
	case 89:
	case 90:
	case 91:
		mes "[セリン]";
		mes "ここに随分長くいらっしゃいますが";
		mes "志は無事成し遂げられましたか？";
		close;
	case 92:
		mes "[セリン]";
		mes "ここに随分長くいらっしゃいますが";
		mes "志は無事成し遂げられましたか？";
		next;
		mes "[セリン]";
		if(countitem(2642)) {
			mes "苦痛の中でうめいていた魂を";
			mes "助けてくださって感謝しています。";
		}
		mes "ところで……なにか私に用が";
		mes "あるようですね。";
		next;
		if(select("いいえ","死者の主について知りたい")==1) {
			mes "[セリン]";
			mes "なにか聞きたいことでも出来たら";
			mes "是非いらしてください。";
			mes "あなたのお役に立ちたいのです。";
			close;
		}
		mes "[セリン]";
		mes "死者の主は、ニブルヘイムと";
		mes "死者の砦を治める偉大な方です。";
		next;
		mes "[セリン]";
		mes "彼女は、ロキと巨人アングルボダの間に";
		mes "産まれた末っ子で、オーディンの命で";
		mes "ここで死者を治めるようになりました。";
		next;
		mes "[セリン]";
		mes "時々、彼女は死者の砦から出てきて";
		mes "ニブルヘイムを見回っています。";
		mes "私が知っているのは、それくらい";
		mes "ですが……";
		next;
		menu "印について知りませんか",-;
		mes "[セリン]";
		mes "それは、九つの世界の象徴と";
		mes "呼ばれていて、死者の主が身から";
		mes "離さず持っているそうです。";
		mes "オーディンから受けた、死者を治める";
		mes "象徴でもありますから。";
		next;
		mes "[セリン]";
		mes "しかし、その印は死者を治める象徴";
		mes "以外にも、ある意味を持っているとの";
		mes "噂があります。それが何なのかは";
		mes "分かりませんけど……";
		next;
		menu "アングルボダについては？",-;
		mes "[セリン]";
		mes "アングルボダは死者の主の母です。";
		mes "彼女が神々により捕らわれた後、";
		mes "彼女と彼女が産んだ3人の子供は";
		mes "神により拉致されました。";
		next;
		mes "[セリン]";
		mes "しかしその後、彼女がどうなったか";
		mes "誰も知りません……";
		next;
		menu "魔女については？",-;
		mes "[セリン]";
		mes "魔女は、私をとても";
		mes "憎んでいらっしゃるようです。";
		next;
		mes "[セリン]";
		mes "私が、ここに適応できずにいるから";
		mes "死者として、ここに居る資格がないと";
		mes "思っているのでしょうか……";
		next;
		emotion 9;
		mes "[セリン]";
		mes "なので、いつも私を";
		mes "見張っているようなのです。";
		mes "でも、仕方ないです。";
		mes "自分でも、私はここに";
		mes "似つかわしくないと思っていますから。";
		set SIGN_QUE,93;
		close;
	case 93:
		mes "[セリン]";
		mes "あ、すみません。";
		mes "話が飛んでしまいましたね。";
		mes "残念ながら、これ以上役に立ちそうな";
		mes "お話は知らないんです。";
		next;
		mes "[セリン]";
		mes "一つだけ言えるのは、死者の主が";
		mes "彼女の母を探しているというのなら";
		mes "アングルボダは、まだ死んで";
		mes "いないのでしょう。";
		next;
		emotion 9;
		mes "[セリン]";
		mes "もしくは、なんらかの理由で";
		mes "魂がニブルヘイムに来れずにいるか……";
		mes "どちらにしろ、死者の主にとって";
		mes "望ましいことではありませんね……";
		set SIGN_QUE,94;
		close;
	case 94:
		mes "[セリン]";
		mes "私が知っていることは、もう全て";
		mes "お話ししました。ごめんなさい……";
		mes "あまりお役に立てなかったようですね。";
		next;
		mes "[セリン]";
		mes "あの、アングルボダに関しては";
		mes "彼女を捕らえた神に近い存在から";
		mes "聞くことができるのでは";
		mes "ないでしょうか。";
		next;
		mes "[セリン]";
		mes "ヴァルキリーとか";
		mes "アスガルドの方とか……";
		next;
		mes "[セリン]";
		mes "あの、差し出がましいかもしれませんが";
		mes "九つの世界の象徴が欲しい理由を";
		mes "教えてもらえないのでしょうか？";
		next;
		mes "[セリン]";
		mes "九つの世界の象徴は、とても";
		mes "危険な品です。";
		mes "それを得るとして、それを何に";
		mes "使うのでしょう。";
		next;
		mes "[セリン]";
		mes "もしあれが、悪い意図を持った人の手に";
		mes "渡ったら……";
		next;
		if(select("渡ったら？","自分でなんとかします")==2) {
			mes "[セリン]";
			mes "あ、ごめんなさい。";
			mes "私がでしゃばることでは";
			mes "ありませんでしたね……";
			set SIGN_QUE,95;
			close;
		}
		mes "[セリン]";
		mes "ニブルヘイムでは、死の苦痛に";
		mes "苦しんだあげく、良くない事を";
		mes "考える方も多くいます。";
		next;
		mes "[セリン]";
		mes "そんな方が九つの世界の象徴を";
		mes "手に入れたら何が起こるか";
		mes "わかりません……";
		next;
		if(select("それでは、どうすれば……","忠告は感謝しますが……")==2) {
			mes "[セリン]";
			mes "そうですか……";
			set SIGN_QUE,95;
			close;
		}
		mes "[セリン]";
		mes "九つの世界の象徴を手に入れたら";
		mes "まっさきに私に会いに来てください。";
		next;
		mes "[セリン]";
		mes "私ができる精一杯のことを";
		mes "してさしあげたいと思います。";
		next;
		menu "考えてみます",-;
		mes "[セリン]";
		mes "それでは、お待ちしてます。";
		set SIGN_QUE,95;
		close;
	case 118:
		mes "[セリン]";
		mes "これが、九つの世界の象徴……";
		mes "ヘル様からこれをいただけたなんて、";
		mes "本当に凄い方です。";
		next;
		mes "[セリン]";
		mes "でも、これは1回しか";
		mes "使えないのですね……";
		next;
		mes "[セリン]";
		mes "それでは、これからあなたが";
		mes "何をすべきかお話ししましょう。";
		next;
		menu "聞かせてください",-;
		mes "[セリン]";
		mes "あなたは、選ばれし者となるため";
		mes "勇気を示すべく、ヴァルキリーの";
		mes "言葉により、ここへいらっしゃい";
		mes "ました。";
		next;
		mes "[セリン]";
		mes "そして、魔女の依頼を受けて";
		mes "この印を得た……";
		mes "私の考えを言います。";
		next;
		mes "[セリン]";
		mes "その、メッツさんの意図がまず";
		mes "おかしくはないでしょうか？";
		mes "このような強大な力を渡したとして、";
		mes "調査するだけで満足するでしょうか？";
		next;
		mes "[セリン]";
		mes "彼は、あなたを利用しているのでは";
		mes "ないですか？";
		next;
		mes "[セリン]";
		mes "魔女もそうです。";
		mes "彼女は、なぜこれが必要なのか";
		mes "説明しなかったのでしょう。";
		next;
		mes "[セリン]";
		mes "この印は、この死者の世界の";
		mes "住人にとって絶対的な力です。";
		mes "魔女は何かを企んで、これを";
		mes "手に入れて欲しいと頼んだのかも";
		mes "知れません。";
		next;
		if(select("では、どうすればいい？","信じられません")==2) {
			mes "[セリン]";
			mes "そうですね……";
			mes "これは、私の予想に過ぎませんし……";
			next;
			mes "[セリン]";
			mes "でも私は、あなたが心配なんです。";
			mes "どうか、お許しください。";
			close;
		}
		mes "[セリン]";
		mes "これを、魔女に持っていっては";
		mes "なりません。。";
		mes "彼女が、これを何に利用するか";
		mes "わからないなら、絶対に渡しては";
		mes "いけません。";
		next;
		mes "[セリン]";
		mes "あの話だって、単なる噂かも";
		mes "しれませんし……";
		set SIGN_QUE,131;
		close;
	case 129:
		mes "[セリン]";
		mes "………………";
		next;
		mes "[セリン]";
		mes "………………";
		next;
		mes "[セリン]";
		mes "………………";
		next;
		mes "[セリン]";
		mes "………………";
		next;
		mes "[セリン]";
		mes "………………";
		next;
		mes "[セリン]";
		mes "………………";
		next;
		mes "[セリン]";
		mes "………………";
		next;
		if(countitem(2643) < 1) {
			emotion 28;
			close;
		}
		if(select("指輪、返しに来たよ","……")==2) {
			emotion 28;
			close;
		}
		mes "[セリン]";
		mes "………………";
		mes "………………";
		mes "………………";
		next;
		mes "[セリン]";
		mes "………………";
		mes strcharinfo(0)+ "さん……";
		mes "忘れ……なかった……";
		mes "あなただけは……";
		next;
		mes "[セリン]";
		mes "生に対する執着も……";
		mes "その思い出も……";
		mes "全部忘れたけど……";
		next;
		mes "[セリン]";
		mes "あなただけは……";
		mes "忘れない……";
		next;
		mes "[セリン]";
		mes "………………";
		mes "………………";
		mes "………………";
		next;
		mes "[セリン]";
		mes "私に……残ったもの……";
		mes "あなたと……あなたの思い出が……";
		mes "詰まっている指輪……";
		mes "大事に……してね……";
		mes "……ありがとう……";
		next;
		mes "[セリン]";
		mes "本当にありがとう……";
		mes "………………";
		mes "…………";
		mes "……";
		next;
		mes "彼女の目は、何も宿さず";
		mes "ただ空虚な闇を見つめている……";
		next;
		mes "しかし、彼女は以前のように";
		mes "寂しげに、悲しげに見えない。";
		mes "彼女の頬を、一筋の細い光が";
		mes "流れた……";
		next;
		mes "彼女の唇は、小さくはにかむように";
		mes "微笑んでいる。";
		mes "あなたとの思い出が";
		mes "手に輝く指輪と一緒にある限り……";
		delitem 2643,1;
		if(checkre())
			getexp 50000,0;
		else
			getexp 500000,0;
		close;
	case 130:
		emotion 28;
		mes "[セリン]";
		mes "…………";
		next;
		emotion 9;
		mes "[セリン]";
		mes "…………";
		next;
		emotion 9;
		mes "[セリン]";
		mes "…………";
		next;
		emotion 28;
		mes "[セリン]";
		mes "…………";
		close;
	case 131:
		mes "[セリン]";
		mes "…………";
		next;
		menu "あの、噂って？",-;
		mes "[セリン]";
		mes "魔女は最近、自分が与えた試練を";
		mes "通過した者を選んで会っています。";
		next;
		mes "[セリン]";
		mes "噂では、彼女は強大な力を";
		mes "手に入れるため、ある準備を";
		mes "しているらしいのです。";
		mes "そう、魔界の王ダークロードを";
		mes "召喚するための準備を……";
		next;
		menu "詳しく聞かせてください",-;
		mes "[セリン]";
		mes "ダークロードは異界の魔王。";
		mes "その力は、とても強大で、";
		mes "とても恐ろしいものです。";
		next;
		mes "[セリン]";
		mes "しかし、彼が異界を越えて来るためには";
		mes "その強大な力のほとんどを";
		mes "使わなければならない上、";
		mes "たくさんの命が宿るミッドガルドは、";
		mes "彼にとって最悪の環境です。";
		next;
		mes "[セリン]";
		mes "なので、越えて来たとしても、";
		mes "ダークロードはその力の半分も";
		mes "発揮することが出来ません。";
		mes "それでも、彼はずっとミッドガルドを";
		mes "狙っているのです。";
		next;
		mes "[セリン]";
		mes "そんなダークロードにとって、";
		mes "ニブルヘイムは最適の場所です。";
		mes "ここは死者の世界なので、";
		mes "彼の世界に近いものがあります。";
		next;
		mes "[セリン]";
		mes "つまり、ダークロード本来の力を";
		mes "発揮しやすい環境なのです。";
		next;
		mes "[セリン]";
		mes "もし、彼がここニブルヘイムに";
		mes "現われてしまったら……彼はきっと";
		mes "ミッドガルドを目指すでしょう。";
		mes "そして彼の力によって、ミッドガルドは";
		mes "死の世界になってしまう……";
		next;
		menu "ヘルは？",-;
		mes "[セリン]";
		mes "ヘル様も、分かっていると思うのです。";
		mes "でも、ダークロードがミッドガルドで";
		mes "多くの命を奪ったとしても、それは";
		mes "ニブルヘイムの住人、すなわち、";
		mes "ヘル様の民が増えることになります。";
		next;
		mes "[セリン]";
		mes "だから、見逃しているのでは";
		mes "ないでしょうか。";
		next;
		mes "[セリン]";
		mes "それに、ダークロードが狙っているのは";
		mes "ミッドガルド。";
		mes "ニブルヘイムではありません……";
		next;
		menu "どうすればいい？",-;
		mes "[セリン]";
		mes "魔女の計画を止めなければなりません。";
		mes "彼女がダークロードを召喚したら";
		mes "ミッドガルドは滅亡してしまいます。";
		next;
		mes "[セリン]";
		mes "彼女の狙いは、ダークロードを";
		mes "こちらに召喚し、代わりに何か願いを";
		mes "かなえてもらうことです。";
		mes "そしてそのためには、";
		mes "召喚用の魔方陣が必要です。";
		next;
		mes "[セリン]";
		mes "それは、きっとニブルヘイムの";
		mes "どこかにあります。";
		next;
		menu "どこ？",-;
		mes "[セリン]";
		mes "私は、生前はウィザードでした。";
		mes "なので、魔方陣について詳しく";
		mes "知っています。";
		next;
		mes "[セリン]";
		mes "ギョル渓谷は、ダークロードを";
		mes "召喚できるほど強大な魔方陣を";
		mes "描ける空間がありません。";
		mes "ニブルヘイムの街では、人目が";
		mes "多すぎます。";
		next;
		mes "[セリン]";
		mes "他人の目を避け、強大な魔方陣を";
		mes "準備できる場所……心当たりが";
		mes "あります。";
		mes "そこへ、一緒に行ってください。";
		set SIGN_QUE,132;
		close;
	case 132:
		if(getnpctimer(1,"SignTimer#serin")) {
			mes "[セリン]";
			mes "もう少し準備する時間をください。";
			close;
		}
		mes "[セリン]";
		mes "それでは出発しましょうか？";
		next;
		if(select("はい","もうちょっと待って")==2)
			close;
		mes "[セリン]";
		mes "では、行きましょう。";
		close2;
		initnpctimer "SignTimer#serin";
		warp "que_sign01.gat",199,36;
		end;
	case 133:
	case 134:
	case 199:
		mes "セリンの痕跡が残っている。";
		if(getnpctimer(1,"SignTimer#serin")) {
			close;
		}
		next;
		if(select("痕跡を追う","無視する")==2)
			close;
		close2;
		set SIGN_QUE,199;
		initnpctimer "SignTimer#serin";
		warp "que_sign01.gat",199,36;
		end;
	case 135:
	case 136:
		emotion 9;
		mes "[セリン]";
		mes "………………";
		mes "……………";
		mes "誰……";
		mes "……………";
		close;
	default:
		if(SIGN_QUE < 118) {
			mes "[セリン]";
			mes "それを手に入れたら、必ず私に会いに";
			mes "来てください。心良くない者にそれが";
			mes "渡ってしまっては、大変なことに";
			mes "なります。";
			next;
			mes "[セリン]";
			mes "どうか、お願いします……";
			close;
		}
		if(SIGN_QUE < 129) {
			mes "セリンの残された邪念が";
			mes "彼女の形を形成している。";
			close;
		}
		if(SIGN_QUE > 199) {
			mes "彼女の痕跡だけが残っている。";
			mes "……………";
			mes "彼女はどうなっただろう……";
			mes "……………";
			if(countitem(2642)) {
				next;
				mes "あなたが持っている";
				mes "セリンの指輪が、";
				mes "光と共に消えた……";
				delitem 2642,1;
			}
			close;
		}
		if(countitem(2642) < 1) {
			emotion 9;
			mes "[セリン]";
			mes "………………";
			mes "………………";
			close;
		}
		emotion 28;
		mes "[セリン]";
		mes "ありがとう……";
		delitem 2642,1;
		next;
		mes "セリンは自分の指輪を持ち";
		mes "去った……";
		close;
	}
}

niflheim.gat,350,258,1	script	#呪われた魂	844,3,3,{
OnTouch:
	if((SIGN_QUE != 83 && SIGN_QUE != 90) || SIGN_SUBQUE != 0)
		end;
	killmonster "niflheim.gat","nif_soul";
	mes "[アッシュブルース]";
	mes "お主には強い呪いを感じる!!!!";
	mes "わしはお主の存在を拒否する!!!!";
	mes "もし退かぬのなら、死を与えよう!!";
	mes "わしの大事な本たちに";
	mes "触れるんじゃない!!!!";
	next;
	switch(select("1番目の本を取ってみる","2番目の本を取ってみる","3番目の本を取ってみる","おとなしく退く")) {
	case 1:
		monster "niflheim.gat",349,259,"ライドワード",1478,1,"nif_soul";
		mes "[アッシュブルース]";
		mes "ぐはははは!!";
		mes "むやみにわしの本を触れるからだ!!";
		mes "噛み切られ、引き裂かれるがよい!!";
		mes "永遠の呪いに囚われるのだ!!";
		close;
	case 2:
		mes "[アッシュブルース]";
		mes "わしの本たちに触れるとは……";
		mes "早々に消えろ!!わしの休息の";
		mes "邪魔をするんじゃない!!";
		close2;
		warp "niflheim.gat",34,162;
		end;
	case 3:
		mes "[アッシュブルース]";
		mes "ぬうう……お主。";
		mes "結構、度胸があるようだな。";
		mes "…………!!!!";
		mes "ならば……一度呪文を";
		mes "唱えてみるがよい……!!";
		next;
		if(select("クローバ","クルラト","クレイトス")==2)
			set '@nif_soul,'@nif_soul+1;
		if(select("ベリト","ベリタス","ベラタ")==3)
			set '@nif_soul,'@nif_soul+1;
		if(select("ネクタイ","ネックレス","ネロ","^FFFFFFニックト^000000")==4)
			set '@nif_soul,'@nif_soul+1;
		if('@nif_soul < 3) {
			monster "niflheim.gat",345,259,"オークスケルトン",1462,1,"nif_soul";
			monster "niflheim.gat",347,261,"オークスケルトン",1462,1,"nif_soul";
			monster "niflheim.gat",344,253,"オークスケルトン",1462,1,"nif_soul";
			monster "niflheim.gat",346,251,"オークスケルトン",1462,1,"nif_soul";
			monster "niflheim.gat",349,249,"オークスケルトン",1462,1,"nif_soul";
			monster "niflheim.gat",350,260,"オークスケルトン",1462,1,"nif_soul";
			monster "niflheim.gat",353,256,"オークスケルトン",1462,1,"nif_soul";
			mes "[アッシュブルース]";
			mes "ぐはははは!!!!";
			mes "お主、呪文が間違っているぞ!!";
			mes "お主に必要なのは死のようだな。";
			mes "一生、呪われ続けるがよい……!!";
			close;
		}
		if(rand(5) == 0) {
			mes "[アッシュブルース]";
			mes "呪文は確かに正しい……だが、";
			mes "お主の呪いは解けないのだ……";
			mes "ぐはははは……!!!!";
			close;
		}
		mes "[アッシュブルース]";
		mes "ぬあああああ!!";
		mes "全ての呪いが解けていく!!";
		mes "ぐああああ……!!!!";
		next;
		mes "[アッシュブルース]";
		mes "ぬあああああ!!";
		mes "全ての呪いが解けていく!!";
		mes "これをやるからとっとと立ち去れ!!";
		mes "ぐああああ……!!!!";
		if(SIGN_QUE == 83)
			set SIGN_SUBQUE,1;
		if(SIGN_QUE == 90)
			set SIGN_QUE,91;
		getitem 7304,1;
		close;
	case 4:
		mes "[アッシュブルース]";
		mes "ぶははは!!";
		mes "よく考えたようだな……";
		mes "お主が無事に生きて帰れることを";
		mes "わしも祈ってやろう。";
		close;
	}
}

nif_in.gat,156,93,0	script	#少女	844,2,2,{
OnTouch:
	if(SIGN_QUE != 83) {
		emotion 28;
		mes "[アラキナ]";
		mes "しくしく、うわ～ん。";
		mes "お家に帰りたいよ……";
		mes "しくしく……";
		close;
	}
	switch(SIGN_SUBQUE) {
	case 0:
	case 2:
		emotion 28;
		mes "[アラキナ]";
		mes "うわ～ん。";
		mes "お家に帰りたいよ……";
		close;
	case 1:
		mes "[アラキナ]";
		mes "お" +(Sex? "兄": "姉")+ "ちゃん……";
		mes "ここはどこ……？";
		mes "私、目が覚めたらここにいたの……";
		mes "ママ……ねぇ、ママを見なかった？";
		mes "……うわ～ん。お家に帰りたいよ～。";
		next;
		if(select("どうすれば帰れるの？","帰れないから諦めなさい")==2) {
			mes "[アラキナ]";
			mes "しくしく、うわ～ん。";
			mes "お家に帰りたいよ……";
			mes "しくしく……";
			close2;
			emotion 28;
			end;
		}
		mes "[アラキナ]";
		mes "わからない……";
		mes "時々訪ねてくる吟遊詩人のおじちゃんは";
		mes "帰りたいなら魔女に会いなさいって";
		mes "言ってたけど、外を1人で歩くのは、";
		mes "とても怖いの……";
		set SIGN_SUBQUE,2;
		close;
	case 3:
	case 4:
		if(countitem(7309) < 1) {
			emotion 28;
			mes "[アラキナ]";
			mes "うわ～ん。";
			mes "お家に帰りたいよ……";
			mes "でも、魔女は怖いよ～、しくしく。";
			close;
		}
		mes "[アラキナ]";
		mes "これを使えば帰れるの？";
		mes "ありがとう!!";
		delitem 7309,countitem(7309);
		set SIGN_SUBQUE,5;
		close;
	case 5:
		emotion 28;
		mes "[アラキナ]";
		mes "うそつき……";
		mes "何も起きない～。";
		mes "しくしく、うわ～ん。";
		mes "お家に帰りたいよ……";
		set SIGN_SUBQUE,6;
		close;
	default:
		emotion 28;
		mes "[アラキナ]";
		mes "嘘つき……";
		mes "何も起きない～。";
		mes "しくしく、うわ～ん。";
		mes "お家に帰りたいよ……";
		close;
	}
}

nif_in.gat,188,168,0	script	#魔女	844,2,2,{
OnTouch:
	switch(SIGN_QUE) {
	default:
		if(SIGN_QUE < 88) {
			mes "[キルケラ]";
			mes "自分の器を量れない者は";
			mes "冒険にその身を投じることも";
			mes "あります……";
			close;
		}
		end;
	case 83:	//サブクエスト中
		break;
	case 88:
		if(countitem(2642) < 1) {
			mes "[キルケラ]";
			mes "助け？";
			mes "なぜ私があなたを助けなければ";
			mes "いけないのでしょう。";
			next;
			if(select("ご、ごめんなさい","こちらも、何かお手伝いしますから")==1) {
				emotion 32;
				mes "[キルケラ]";
				mes "……";
				close;
			}
			mes "[キルケラ]";
			mes "そう、そこまで言うのなら……";
			mes "実は以前、魔女の呪文書を";
			mes "誰かが盗み出してしまったのです。";
			mes "その呪文書を取り返して";
			mes "もらえないでしょうか。";
			next;
			mes "[キルケラ]";
			mes "どこの誰が盗んだかは、";
			mes "わかりません……。";
			mes "それと、次に来る時は、";
			mes "2階の肖像画の右にある";
			mes "飾りから来てください。";
			set SIGN_QUE,90;
			close;
		}
		mes "[キルケラ]";
		mes "やはり、単純な理由でここを";
		mes "訪れたのではなかったのですね。";
		mes "ここがどんな場所かは、";
		mes "もうわかったと思います。";
		next;
		mes "[キルケラ]";
		mes "ここは、あなたと同じように、";
		mes "勇気を証明し、";
		mes "選ばれし者になろうとして";
		mes "失敗した者達が眠る場所。";
		mes "苦痛と言う名の墓場。";
		next;
		mes "[キルケラ]";
		mes "そして、この街には、全ての死者を";
		mes "統治する死者の主がいます。";
		next;
		mes "[キルケラ]";
		mes "彼女は鎧で全身を隠し、時折り、";
		mes "見回りのために姿を現すのです。";
		mes "その強さは他に類を見ません。";
		next;
		mes "[キルケラ]";
		mes "あなたは……";
		next;
		mes "[キルケラ]";
		mes "……彼女から印を得なければ";
		mes "なりません。";
		next;
		menu "印とはなんですか？",-;
		mes "[キルケラ]";
		mes "それは……";
		mes "あらゆる死者の主である象徴。";
		next;
		menu "どうしてそれが必要なの？",-;
		mes "[キルケラ]";
		mes "それは、まだ教えるわけには";
		mes "いきません。その印を持ち帰ってきた";
		mes "時に教えましょう……";
		next;
		mes "[キルケラ]";
		mes "印のことは、絶対に秘密にして";
		mes "ください。";
		mes "その印は誰にも渡しては";
		mes "ならないものですから。";
		next;
		if(select("どうして？","印を得る方法は？")==1) {
			mes "[キルケラ]";
			mes "それは、まだ教えるわけには";
			mes "いきません。";
			next;
			menu "印を得る方法は？",-;
		}
		mes "[キルケラ]";
		mes "一番簡単なのは、力で死者の主から";
		mes "その印を奪うことです。";
		mes "もしくは、ある物を提供し、";
		mes "取り引きをすることです。";
		next;
		if(select("分かりました","なにを提供すればいい？")==1) {
			set SIGN_QUE,89;
			close;
		}
		mes "[キルケラ]";
		mes "彼女には、神々により監禁された";
		mes "母がいるといいます。";
		next;
		mes "[キルケラ]";
		mes "そして死者の主は……";
		mes "母、アングルボダを";
		mes "探し続けています。";
		next;
		mes "[キルケラ]";
		mes "……次に来る時は、2階の肖像画の";
		mes "右にある飾りから来てください。";
		set SIGN_QUE,92;
		close;
	case 89:
		mes "[キルケラ]";
		mes "…………";
		next;
		menu "なにを提供すればいい？",-;
		mes "[キルケラ]";
		mes "彼女には、神々により監禁された";
		mes "母がいるといいます。";
		mes "そして死者の主は……";
		mes "母、アングルボダを";
		mes "探し続けています。";
		next;
		mes "[キルケラ]";
		mes "……次に来る時は、";
		mes "2階の肖像画の右にある";
		mes "飾りから来てください。";
		set SIGN_QUE,92;
		close;
	}
	switch(SIGN_SUBQUE) {
	default:
		mes "[キルケラ]";
		mes "何か理由がないのであれば";
		mes "生きている方は、その世界へ";
		mes "帰るべきです。";
		close;
	case 2:
		if(countitem(7304) < 1) {
			mes "[キルケラ]";
			mes "あなた、生きているじゃ";
			mes "ありませんか。";
			mes "ここまで来るのは";
			mes "大変だったでしょう……";
			mes "理由はどうあれ、ここは生きている方が";
			mes "来るところではありません。";
			next;
			mes "[キルケラ]";
			mes "私の力で外へ出してあげますから、";
			mes "もう二度と来てはいけません。";
			close2;
			warp "umbala.gat",132,203;
			end;
		}
		mes "[キルケラ]";
		mes "どうしてあなたが";
		mes "私の無くした呪文書を";
		mes "持っているのですか？";
		next;
		menu "呪われた魂から貰いました",-;
		mes "[キルケラ]";
		mes "そう……";
		mes "その魂は私の呪文書を盗み";
		mes "勝手に呪文を使っていたようですね。";
		mes "でも、呪文書が戻ってきて";
		mes "よかったです。";
		next;
		mes "[キルケラ]";
		mes "さて、あなたはどんな理由で";
		mes "私を訪ねてきたのですか？";
		next;
		if(select("帰りたいんです","アラキナを帰してあげたいです")==1) {
			mes "[キルケラ]";
			mes "そうですか。";
			mes "では私の力で";
			mes "送り帰してあげましょう。";
			close2;
			warp "umbala.gat",132,203;
			end;
		}
		mes "[キルケラ]";
		mes "帰してあげたいのですか？";
		mes "それなら、これを持っていくと";
		mes "良いです。";
		mes "これは、生きている者を";
		mes "その故郷へ帰す力を持っています。";
		delitem 7304,1;
		set SIGN_SUBQUE,3;
		getitem 7309,1;
		close;
	case 3:
		if(countitem(7309)) {
			mes "[キルケラ]";
			mes "早く行ってください。";
			close;
		}
		mes "[キルケラ]";
		mes "羽を失くしてしまったのですか？";
		mes "仕方ありませんね、この最後の";
		mes "羽をお使いください。";
		mes "早くその子を助けてあげるのです！";
		set SIGN_SUBQUE,4;
		getitem 7309,1;
		close;
	case 6:
		mes "[キルケラ]";
		mes "あの品は、生きている人を";
		mes "その故郷に帰すものだと";
		mes "教えませんでしたか？";
		set SIGN_SUBQUE,7;
		close;
	case 7:
		mes "[キルケラ]";
		mes "その少女は、自分が死んだと知らず、";
		mes "認めず、生への未練と執着が、";
		mes "彼女をあの場所に捕らえて";
		mes "いるのです……。";
		set SIGN_SUBQUE,8;
		close;
	case 8:
		mes "[キルケラ]";
		mes "自分の器を量れない者は";
		mes "冒険にその身を投じることも";
		mes "あります……";
		close;
	}
}

nif_in.gat,105,81,0	script	#クレユ	844,2,2,{
OnTouch:
	switch(SIGN_QUE) {
	default:
		end;
	case 75:
	case 76:
	case 77:
	case 78:
	case 79:
	case 80:
	case 81:
		mes "[クレユ]";
		mes "陽が傾き西の山にかかりし時";
		mes "空が紫の夕暮れに染まる頃";
		mes "美しき旋律に実を委ねれば";
		mes "主なる者を助ける鍵を得ようぞ";
		close;
	case 86:
		mes "[クレユ]";
		mes "陽が傾き西の山にかかりし時";
		mes "空が紫の夕暮れに染まる頃";
		mes "美しき旋律に実を委ねれば";
		mes "主なる者を助ける鍵を得ようぞ";
		next;
		mes "[クレユ]";
		mes "あなたはセリンをどう思う？";
		next;
		menu "彼女は良い人",-,"彼女は悪い人",-,"まだ何とも言えない",-;
		mes "[クレユ]";
		mes "そのように思う理由は？";
		next;
		if(select("そう感じたから","客観的に判断して")==1) {
			if(SIGN_SUBQUE > 1)
				set SIGN_SUBQUE,0;
			else
				set SIGN_SUBQUE,SIGN_SUBQUE+1;
		}
		mes "[クレユ]";
		mes "君の考えは良く分かった。";
		mes "では、君の望みは？";
		next;
		if(select("ニブルヘイムはどんな所ですか？","選ばれし者になるにはどうすれば？")==1) {
			mes "[クレユ]";
			mes "ニブルヘイムは、君も知っている通り";
			mes "死者の街。ただそれだけの存在。";
			mes "ヴァルハラを夢見ながら死んだ";
			mes "数多くの英雄達の、苦痛という名の";
			mes "墓場さ。";
			close;
		}
		mes "[" +strcharinfo(0)+ "]";
		mes "選ばれる為に、私がすべきことは";
		mes "何ですか？";
		next;
		mes "[クレユ]";
		mes "選ばれし者になるためには、";
		mes "君の勇気を示さねばならない。";
		mes "どう示すかは君次第。";
		mes "あの御方は、それを見守るだけ……";
		next;
		mes "[クレユ]";
		mes "もっと知りたければ";
		mes "^FF0000オゼ^000000を訪ねなさい。";
		set SIGN_QUE,87;
		close;
	case 87:
		mes "[クレユ]";
		mes "もっと知りたければ";
		mes "^FF0000オゼ^000000を訪ねなさい。";
		close;
	}
}

niflheim.gat,146,241,0	script	陰気な男	735,{
	if(SIGN_QUE < 80) {
		mes "[？？]";
		mes "邪魔するな!!";
		close;
	}
	switch(SIGN_QUE) {
	case 80:
	case 81:
	case 82:
	case 83:
	case 84:
	case 85:
	case 86:
		mes "[？？]";
		mes "人の外見は、所詮皮一枚。";
		mes "内面を見なければ、その人の本質は";
		mes "分からない。";
		close;
	case 87:
		if(countitem(2642) < 1) {
			mes "[オゼ]";
			mes "審判を受けるために";
			mes "この死の街を尋ねて来たか。";
			next;
			mes "[オゼ]";
			mes "私も、お前のように選ばれし者と";
			mes "なるべく、ここに訪れた一人。";
			mes "しかし、失敗した。その代償として、";
			mes "肉体を失い、死者の街を彷徨う";
			mes "魂となった。";
			next;
			mes "[オゼ]";
			mes "警告しよう……慎重になるがいい。";
			mes "この試練の代償は、あまりに大きい。";
			next;
			mes "[オゼ]";
			mes "貪欲な考えを「勇気」などという言葉で";
			mes "一括りにしてしまっては、";
			mes "見えなくなってしまう物もある……";
			next;
			mes "[オゼ]";
			mes "ああ、すまん。気を害したか？";
			mes "だが忘れるな。あの御方はいつも";
			mes "お前を見ている。選ばれし者となる";
			mes "資格があるか調べるためにな。";
			next;
			mes "[オゼ]";
			mes "話が長くなったな。";
			mes "魔女を訪ねるといい。";
			mes "彼女なら、お前が何をすればいいか";
			mes "良く知っている。";
			set SIGN_QUE,88;
			close;
		}
		mes "[オゼ]";
		mes "何を探している？";
		mes "おおかた、クレユが";
		mes "よこしたのだろう。";
		mes "さっさと本筋に入ろうか。";
		next;
		mes "[オゼ]";
		mes "お前、何故、選ばれし者に";
		mes "なりたい。";
		next;
		if(select("自分の勇気を証明したい","自分の名誉のため","たくさんの人の役に立ちたい")==1) {
			if(SIGN_SUBQUE > 2)
				set SIGN_SUBQUE,0;
			else
				set SIGN_SUBQUE,SIGN_SUBQUE+1;
		}
		mes "[オゼ]";
		mes "私がどうしてここに居るか、";
		mes "クレユに聞いたか？";
		next;
		if(select("はい","いいえ")==1) {
			mes "[オゼ]";
			mes "そうか。";
			mes "それなら魔女を訪ねるがいい。";
			next;
			mes "[オゼ]";
			mes "だが、気をつけるがいい。";
			mes "彼女は魔女なのだからな……";
			set SIGN_QUE,88;
			close;
		}
		mes "[オゼ]";
		mes "私も、お前のように選ばれし者と";
		mes "なるべく、ここに訪れた一人。";
		mes "しかし、失敗した。その代償として、";
		mes "肉体を失い、死者の街を彷徨う";
		mes "魂となった。";
		next;
		mes "[オゼ]";
		mes "警告しよう……慎重になるがいい。";
		mes "この試練の代償は、あまりに大きい。";
		next;
		mes "[オゼ]";
		mes "貪欲な考えを「勇気」などという言葉で";
		mes "一括りにしてしまっては、";
		mes "見えなくなってしまう物もある……";
		next;
		mes "[オゼ]";
		mes "ああ、すまん。気を害したか？";
		mes "だが忘れるな。あの御方はいつも";
		mes "お前を見ている。選ばれし者となる";
		mes "資格があるか調べるためにな。";
		next;
		mes "[オゼ]";
		mes "話が長くなったな。";
		mes "魔女を訪ねるといい。";
		mes "彼女なら、お前が何をすればいいか";
		mes "良く知っている。";
		next;
		mes "[オゼ]";
		mes "だが、気をつけるがいい。";
		mes "彼女は魔女なのだからな……";
		next;
		mes "[オゼ]";
		mes "ん？　ああ、これはセリンの言葉だ。";
		mes "彼女は優しい。";
		mes "ニブルヘイムには";
		mes "似つかわしくない存在だ。";
		next;
		mes "[オゼ]";
		mes "セリンは生きていた頃、";
		mes "立派なウィザードだったそうだ。";
		set SIGN_QUE,88;
		close;
	case 117:
		mes "[オゼ]";
		mes "よく来たな。";
		mes "ヘルを探しているそうじゃないか。";
		next;
		mes "[オゼ]";
		mes "もう隠す必要もないな。";
		mes "私の本当の名前はガングルラティ。";
		mes "死者の主であるヘル様の僕。";
		next;
		mes "[オゼ]";
		mes "それではヘル様のもとへ送ろう。";
		mes "準備はいいか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[オゼ]";
			mes "準備が出来たら、再び";
			mes "訪ねてくるがいい。";
			mes "しかし、急ぐがいい。";
			mes "ヘル様がお待ちかねだ。";
			close;
		}
		mes "[オゼ]";
		mes "ヘル様の前では礼儀を守ることだ。";
		mes "礼儀を守ることが出来ねば、";
		mes "惨事となると心得よ。";
		close2;
		warp "que_sign01.gat",45,20;
		end;
	case 118:
		mes "[オゼ]";
		mes "ほう、九つの世界の象徴か。";
		mes "1回とは言え、よくヘル様が";
		mes "許したものだ。";
		next;
		mes "[オゼ]";
		mes "もう一度言う。";
		mes "「彼女」には気をつけるがいい。";
		mes "彼女は既に、おまえがヘル様から";
		mes "象徴を授かったのを知っている。";
		next;
		mes "[オゼ]";
		mes "いいか、事の本質を見極めるがいい……";
		close;
	default:
		if(SIGN_QUE < 117) {
			mes "[オゼ]";
			mes "お前、なにかを探しているようだな。";
			mes "それも、そうとう危険な物を。";
			mes "気をつけろよ。";
			next;
			mes "[オゼ]";
			mes "強くて危険な存在が、お前を";
			mes "狙ってくることだろう……";
			close;
		}
		if(SIGN_QUE < 129) {
			mes "[オゼ]";
			mes "急がなければ、ミッドガルドも";
			mes "ニブルヘイムも、滅ぼされて";
			mes "しまうだろう……";
			next;
			mes "[オゼ]";
			mes "ヘル様は、いったい何を";
			mes "お考えなのか……";
			close;
		}
		if(SIGN_QUE > 200) {
			mes "[オゼ]";
			mes "彼女を止めることは出来なかった";
			mes "ようだな。おまえならできるだろうと";
			mes "少しは期待していたのだが……";
			next;
			mes "[オゼ]";
			mes "……期待はずれだったな。";
			mes "さぁ、帰るがよい。";
			close;
		}
		mes "[オゼ]";
		mes "よくぞ彼女を止めてくれた。";
		mes "感謝しよう。";
		next;
		mes "[オゼ]";
		mes "全て終わったなら、もう一度";
		mes "訪ねるようにとの、ヘル様の";
		mes "お言葉だ。参られるか？";
		next;
		if(select("また後で","行きます")==1) {
			mes "[オゼ]";
			mes "そうか。";
			close;
		}
		mes "[オゼ]";
		mes "では送ろう。";
		mes "いいか、ヘル様の前では";
		mes "礼を守るのだぞ。";
		close2;
		warp "que_sign01.gat",45,20;
		end;
	}
}

nif_in.gat,140,177,0	script	#スイッチ	111,{
	if(countitem(7313) == 1) {
		warp "que_sign01.gat",115,135;
		end;
	}
	if(SIGN_QUE > 89) {
		if(SIGN_QUE == 126)
			set SIGN_QUE,198;
		warp "que_sign01.gat",115,135;
		end;
	}
}

que_sign01.gat,122,141,4	script	魔女	792,{
	if(countitem(7313) == 1 && (SIGN_QUE < 124 || SIGN_QUE > 126)) {
		mes "[キルケラ]";
		mes "行きますか？";
		next;
		if(select("行きます","まだ……")==2) {
			mes "[キルケラ]";
			mes "急いで……";
			close;
		}
		set @menu,select("セリンの近くへ","セリンを探しに");
		mes "[キルケラ]";
		mes "頼みます……";
		close2;
		if(@menu == 1) warp "que_sign01.gat",195,189;
		else warp "que_sign02.gat",35,313;
		end;
	}
	switch(SIGN_QUE) {
	case 90:
		if(countitem(2642) < 1) {
			mes "[キルケラ]";
			mes "まず、やるべきことをしなさい。";
			close;
		}
		mes "[キルケラ]";
		mes "呪文書はもう一つあります。";
		mes "そちらも取り返して来てください。";
		set SIGN_SUBQUE,0;
		close;
	case 91:
		if(countitem(7304) < 1) {
			emotion 32;
			mes "[キルケラ]";
			mes "まず、やるべきことをしなさい。";
			close;
		}
		mes "[キルケラ]";
		mes "あの魂は私の呪文書を盗み";
		mes "勝手に呪文を使っていたようです。";
		mes "でも、呪文書が戻ってきてよかった。";
		next;
		mes "[キルケラ]";
		mes "さて、あなたはどんな理由で";
		mes "私を訪ねてきたのですか？";
		next;
		menu "クレユさんに教わって来ました",-;
		mes "[キルケラ]";
		mes "やはり、単純な理由でここを";
		mes "訪れたのではなかったのですね。";
		mes "ここがどんな場所かは、";
		mes "もうわかったと思います。";
		next;
		mes "[キルケラ]";
		mes "ここは、あなたと同じように、";
		mes "勇気を証明し、";
		mes "選ばれし者になろうとして";
		mes "失敗した者達が眠る場所。";
		mes "苦痛と言う名の墓場。";
		next;
		mes "[キルケラ]";
		mes "そして、この街には、全ての死者を";
		mes "統治する死者の主がいます。";
		next;
		mes "[キルケラ]";
		mes "彼女は鎧で全身を隠し、時折り、";
		mes "見回りのために姿を現すのです。";
		mes "その強さは他に類を見ません。";
		next;
		mes "[キルケラ]";
		mes "あなたは……";
		next;
		mes "[キルケラ]";
		mes "……彼女から印を得なければ";
		mes "なりません。";
		next;
		menu "印とはなんですか？",-;
		mes "[キルケラ]";
		mes "それは……";
		mes "あらゆる死者の主である象徴。";
		next;
		menu "どうしてそれが必要なの？",-;
		mes "[キルケラ]";
		mes "それは、まだ教えるわけには";
		mes "いきません。その印を持ち帰ってきた";
		mes "時に教えましょう……";
		next;
		mes "[キルケラ]";
		mes "印のことは、絶対に秘密にして";
		mes "ください。";
		mes "その印は誰にも渡しては";
		mes "ならないものですから。";
		next;
		if(select("どうして？","印を得る方法は？")==1) {
			mes "[キルケラ]";
			mes "それは、まだ教えるわけには";
			mes "いきません。";
			next;
			menu "印を得る方法は？",-;
		}
		mes "[キルケラ]";
		mes "一番簡単なのは、力で死者の主から";
		mes "その印を奪うことです。";
		mes "もしくは、ある物を提供し、";
		mes "取り引きをすることです。";
		next;
		if(select("分かりました","なにを提供すればいい？")==1) {
			set SIGN_QUE,92;
			close;
		}
		mes "[キルケラ]";
		mes "彼女には、神々により監禁された";
		mes "母がいるといいます。";
		next;
		mes "[キルケラ]";
		mes "死者の主は、母、アングルボダを";
		mes "探し続けています。";
		delitem 7304,1;
		set SIGN_QUE,92;
		close;
	case 92:
		if(rand(10) < 8) {
			mes "[キルケラ]";
			mes "死者の主は、自分が母を";
			mes "探しているという情報を流し、";
			mes "アングルボダに関する噂や話が";
			mes "集まってくるのを待っています。";
			next;
			mes "[キルケラ]";
			mes "いいですか。絶対誰にも";
			mes "あなたが印を欲していると";
			mes "教えてはいけません。";
			next;
			mes "[キルケラ]";
			mes "特にセリンには気をつけなさい。";
			mes "あの人は、必ず止めなければいけない";
			mes "存在。絶対、気付かれては";
			mes "ならないのです、絶対に。";
			close;
		}
		mes "[キルケラ]";
		mes "アングルボダについては、";
		mes "セリンと言う女が知っているかも";
		mes "しれません。";
		mes "でも、気をつけてください。";
		next;
		mes "[キルケラ]";
		mes "あの人は、必ず止めなければいけない";
		mes "存在。絶対、気付かれては";
		mes "ならないのです、絶対に。";
		close;
	case 118:
		mes "[キルケラ]";
		mes "よくそれを持ってきてくれました。";
		mes "誰も探すことが出来なかった";
		mes "アングルボダを探し出すことが";
		mes "出来たのですね。";
		mes "では、その印を私に……";
		next;
		if(select("渡す","渡さない")==2) {
			emotion 9;
			mes "[キルケラ]";
			mes "セリンに何か言われましたか？";
			mes "無理に奪おうとはしません。ですが、";
			mes "良く考えてください。";
			close;
		}
		mes "[キルケラ]";
		mes "では、お話しましょう。";
		mes "これから、あなたが成さねばならない";
		mes "重要なことを教えます。";
		next;
		mes "[キルケラ]";
		mes "今から、この印であることをします。";
		mes "そして、そのためにもう一つ、";
		mes "どうしても必要な物があります。";
		mes "なんでもいいので、セリンが身に";
		mes "着けていた物が要るのです。";
		next;
		mes "[キルケラ]";
		mes "彼女はもうすでに、その身を";
		mes "隠してしまいました。";
		mes "難しいでしょうが、どうか";
		mes "お願いします。";
		delitem 7305,1;
		set SIGN_QUE,119;
		close;
	case 119:
		if(countitem(2642)) {
			mes "[キルケラ]";
			mes "そう、彼女の指輪を持って";
			mes "いたのですか。助かりました。";
			mes "これで、彼女がどこに隠れたか";
			mes "探し出すことが出来ます。";
			delitem 2642,1;
			set SIGN_QUE,120;
			close;
		}
		mes "[キルケラ]";
		mes "こうしていても埒があきませんね。";
		mes "セリンは既に身を隠してしまったし、";
		mes "このような状態で彼女を探すのは";
		mes "不可能に近い……";
		mes "私がなんとかしてみましょう。";
		set SIGN_QUE,121;
		close;
	case 120:
	case 121:
		mes "[キルケラ]";
		mes "薬が完成する間に、";
		mes "お話しましょう。";
		next;
		mes "[キルケラ]";
		mes "印が必要な理由を言わなかったのは";
		mes "あなたを通じ、セリンが私の意図に";
		mes "気付く可能性があったからです。";
		mes "気を悪くしたでしょう？";
		mes "でも、万が一を考えると、慎重に事を";
		mes "運ばざるをえなかったのです。";
		next;
		mes "[キルケラ]";
		mes "セリンは、死者であるにも関わらず、";
		mes "生に執着するあまり、自分の死を";
		mes "受け入れることが出来ずにいます。";
		next;
		mes "[キルケラ]";
		mes "もちろん、そんな者はいくらでも";
		mes "います。普通は絶望と苦痛の中、";
		mes "うめきながら希望という光を";
		mes "忘れていきます。";
		next;
		mes "[キルケラ]";
		mes "しかし、彼女は違う。";
		next;
		mes "[キルケラ]";
		mes "彼女は信念を持ち、希望を捨てずに";
		mes "生への執着を保ってきた。";
		mes "だからこそ、彼女がひと際、ここで";
		mes "異質に見えるのでしょう。";
		next;
		mes "[キルケラ]";
		mes "希望という光を心に持っているだけで";
		mes "ここでは明るすぎる存在となる。";
		next;
		mes "[キルケラ]";
		mes "しかし、彼女は道を間違えた。";
		mes "だから、止めなければならない……";
		while('@talk < 0x7) {
			next;
			switch(select("彼女の願いって？","彼女は何をしようとしている？","私がすべきことは？")) {
			case 1:
				mes "[キルケラ]";
				mes "彼女は九つ世界の象徴を欲しています。";
				mes "全ての死者を支配するヘル様の印を";
				mes "得られれば、ニブルヘイムを出ることが";
				mes "できるからです。";
				next;
				mes "[キルケラ]";
				mes "しかし、あなたが持って来た物では";
				mes "彼女の願いを叶えることが出来ません。";
				mes "生を取り戻す手続きは複雑だから、";
				mes "1回だけの権利では、生まれ変わるのは";
				mes "到底、不可能なのです。";
				set '@talk,'@talk|0x1;
				break;
			case 2:
				mes "[キルケラ]";
				mes "生前、彼女はとても優れた";
				mes "ウィザードでした。彼女は、その知識を";
				mes "使い、九つの世界の象徴を利用し、";
				mes "ある存在をここに呼び出そうと";
				mes "企んでいます。";
				next;
				mes "[キルケラ]";
				mes "悪魔の王、ダークロードを……";
				next;
				mes "[キルケラ]";
				mes "あなたの世界ミッドガルドは、生で";
				mes "満ちている世界。そんな世界に";
				mes "具現するには、ダークロードとて負担が";
				mes "大きすぎるのです。";
				next;
				mes "[キルケラ]";
				mes "それ故、ミッドガルドでは、自分の力を";
				mes "まともに発揮することが出来ずに";
				mes "退いたりしていますが……";
				mes "ここは違います。";
				mes "ここは生ではなく、死が満ちて";
				mes "いますから。";
				next;
				mes "[キルケラ]";
				mes "ダークロードにとって、ニブルヘイムは";
				mes "ミッドガルドより自分の世界に近い。";
				mes "その分、本来の力を使えるでしょう。";
				next;
				mes "[キルケラ]";
				mes "ダークロードがニブルヘイムに姿を";
				mes "現せば、あなたの世界は彼の強大な";
				mes "力によって滅亡します。";
				next;
				mes "[キルケラ]";
				mes "ダークロードを召喚したら、セリンは";
				mes "きっと、こう言います。";
				mes "自分を生き返らせてくれと……";
				mes "もちろんダークロードなら、";
				mes "その願いを叶えられます。";
				next;
				mes "[キルケラ]";
				mes "そして、ヘル様にとって";
				mes "ミッドガルドは関係のない世界。";
				mes "いえ、むしろダークロードにより";
				mes "数多くの死者が生まれ、自分の民が";
				mes "増えると喜ぶかもしれない……";
				next;
				mes "[キルケラ]";
				mes "だから、ヘル様はセリンの行為を";
				mes "知っていながら、何も手を打とうと";
				mes "していないのかも知れない。";
				set '@talk,'@talk|0x2;
				break;
			case 3:
				mes "[キルケラ]";
				mes "あなたがすべきことは、";
				mes "この薬を持ってセリンを探すこと。";
				next;
				mes "[キルケラ]";
				mes "この薬は印の力を使い、";
				mes "印の死者を従わせる力と";
				mes "彼女の記憶を完全に封じる、";
				mes "二つの力を持っています。";
				next;
				mes "[キルケラ]";
				mes "彼女の記憶を封印する薬は";
				mes "以前から準備していました。しかし、";
				mes "絶対的な命令を下せねば、彼女は薬を";
				mes "飲もうとしないでしょう。";
				next;
				mes "[キルケラ]";
				mes "だから、あなたに印を得るよう";
				mes "頼んだのです。";
				set '@talk,'@talk|0x4;
				break;
			}
		}
		set SIGN_QUE,SIGN_QUE+2;
		close;
	case 122:
		mes "[キルケラ]";
		mes "薬が完成しました。";
		mes "これを持ってセリンを";
		mes "追ってください。";
		next;
		mes "[キルケラ]";
		mes "幸い、あなたが持っていた指輪の";
		mes "おかげで彼女の隠れ場所が";
		mes "分かりました。これから、";
		mes "その場所に送りましょう。";
		next;
		mes "[キルケラ]";
		mes "それと、これを持っていきなさい。";
		mes "あなたと共に、セリンに立ち向かって";
		mes "くれる仲間に渡しなさい。";
		next;
		mes "[キルケラ]";
		mes "指輪は、あなたの目的が";
		mes "達成されるまでは指にはめずに";
		mes "大事に持っていなさいね。";
		next;
		mes "[キルケラ]";
		mes "では、全て終わったら、またここに";
		mes "戻ってきてください。";
		set SIGN_QUE,124;
		getitem 7308,1;
		getitem 2643,1;
		getitem 7313,5;
		close;
	case 123:
		mes "[キルケラ]";
		mes "薬が完成しました。";
		mes "これを持ってセリンを";
		mes "追ってください。";
		next;
		mes "[キルケラ]";
		mes "セリンの隠れていると";
		mes "思われる場所を見つけました。";
		mes "今から、そこへ送りましょう。";
		mes "必ず、彼女を見つけ";
		mes "そして止めてください。";
		next;
		mes "[キルケラ]";
		mes "それと、これを持っていきなさい。";
		mes "あなたと共に、セリンに立ち向かって";
		mes "くれる仲間に渡しなさい。";
		set SIGN_QUE,124;
		getitem 7308,1;
		getitem 7313,5;
		close;
	case 124:
	case 125:
	case 198:
		if(getnpctimer(1,"SignTimer#witch")) {
			mes "[キルケラ]";
			mes "もう少し待ってください。";
			close;
		}
		mes "[キルケラ]";
		mes "早く彼女を止めなければ。";
		mes "準備はいいですか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[キルケラ]";
			mes "あまり時間はありません……";
			close;
		}
		close2;
		if(countitem(2643)) {
			initnpctimer "SignTimer#witch";
			warp "que_sign01.gat",195,189;
		}
		else
			warp "que_sign02.gat",35,313;
		end;
	case 127:
	case 128:
		if(countitem(7313) < 5) {
			mes "[キルケラ]";
			mes "魔女の印はどうしました？";
			mes "全部持ってきてください。";
			close;
		}
		mes "[キルケラ]";
		mes "……お疲れさまでした。";
		mes "あなたならきっとできると思って";
		mes "いました。彼女もこれで、全てを忘れ";
		mes "ここで生きて行けるでしょう。";
		next;
		mes "[キルケラ]";
		mes "生への執着も、";
		mes "ミッドガルドへの執着も、";
		mes "あなたの記憶も全て……";
		next;
		if(countitem(2643)) {
			mes "[キルケラ]";
			mes "生まれ変わることが出来ずとも、";
			mes "彼女は幸せだったでしょう。";
			mes "あなたと出会えましたから。";
			next;
			mes "[キルケラ]";
			mes "生とは、呼吸し、心臓が鳴る肉体を";
			mes "持つことではありません。";
			mes "自分以外の存在と調和し、共存する中で";
			mes "自分をみつけることです。";
			next;
			mes "[キルケラ]";
			mes "彼女は、ニブルヘイムの住人。";
			mes "ここで存在していかなければならない。";
		}
		else {
			mes "[キルケラ]";
			mes "結局、彼女の生に対する執着は悲劇に";
			mes "終わってしまいました。あまり、後味の";
			mes "良いものではありませんね……";
			next;
			mes "[キルケラ]";
			mes "でも、彼女はニブルヘイムの";
			mes "住人だから、ここで存在して";
			mes "いかなければなりません。";
		}
		next;
		mes "[キルケラ]";
		mes "とにかく、ありがとう。";
		mes "あなたは見事、自分のやるべきことを";
		mes "成し遂げました。";
		next;
		mes "[キルケラ]";
		mes "さぁ、行きなさい。";
		mes "そして、全てが終わったら、また";
		mes "ヘル様を訪ねるといいでしょう。";
		delitem 7313,5;
		if(countitem(2643)) {
			set SIGN_QUE,129;
			if(checkre())
				getexp 50000,0;
			else
				getexp 500000,0;
		}
		else {
			set SIGN_QUE,130;
			if(checkre())
				getexp 30000,0;
			else
				getexp 300000,0;
		}
		close;
	case 131:
	case 132:
	case 133:
	case 134:
		mes "[キルケラ]";
		mes "彼女を止めなければ。";
		mes "早く！";
		close;
	case 135:
	case 136:
		mes "[キルケラ]";
		mes "……お疲れさまでした。";
		mes "あなたならきっとできると思って";
		mes "いました。彼女もこれで、全てを忘れ";
		mes "ここで生きて行けるでしょう。";
		next;
		mes "[キルケラ]";
		mes "生への執着も、";
		mes "ミッドガルドへの執着も、";
		mes "あなたの記憶も全て……";
		next;
		mes "[キルケラ]";
		mes "結局、彼女の生に対する執着は悲劇に";
		mes "終わってしまいました。あまり、後味の";
		mes "良いものではありませんね……";
		next;
		mes "[キルケラ]";
		mes "でも、彼女はニブルヘイムの";
		mes "住人だから、ここで存在して";
		mes "いかなければなりません。";
		next;
		mes "[キルケラ]";
		mes "とにかく、ありがとう。";
		mes "あなたは見事、自分のやるべきことを";
		mes "成し遂げました。";
		next;
		mes "[キルケラ]";
		mes "さぁ、行きなさい。";
		mes "そして、全てが終わったら、また";
		mes "ヘル様を訪ねるといいでしょう。";
		if(countitem(2643))
			set SIGN_QUE,129;
		else
			set SIGN_QUE,130;
		if(checkre())
			getexp 30000,0;
		else
			getexp 300000,0;
		close;
	case 200:
		mes "[キルケラ]";
		mes "あなたに任せたのが間違いでした。";
		mes "セリンはダークロードの召喚を";
		mes "試みましたが、幸いにも、別の方により";
		mes "阻止されました。";
		next;
		mes "[キルケラ]";
		mes "それが誰かですか？";
		mes "分かりませんか？　あなたと同じように";
		mes "選ばれし者の試練で、ここに来ている";
		mes "方の1人です。";
		next;
		mes "[キルケラ]";
		mes "セリンを無事止めることが出来た者は";
		mes "神に選ばれ、ヴァルハラへ昇る";
		mes "許可を得るでしょう。";
		next;
		mes "[キルケラ]";
		mes "あなたは失敗したのです。";
		mes "やり直しもできません。";
		mes "これで終わりです。";
		next;
		mes "[キルケラ]";
		mes "セリンが、最後の優しさであなたを";
		mes "ミッドガルドに送らなければ、あなたは";
		mes "他の失敗した者と同じく、";
		mes "ニブルヘイムを救われない魂として";
		mes "彷徨うことになっていたでしょう。";
		next;
		mes "[キルケラ]";
		mes "彼女に感謝することですね。";
		delitem 7308,countitem(7308);
		delitem 2642,countitem(2642);
		set SIGN_QUE,201;
		if(checkre())
			getexp 20000,0;
		else
			getexp 200000,0;
		close;
	default:
		if(SIGN_QUE < 118) {
			mes "[キルケラ]";
			mes "印を得るのは、とても難しい";
			mes "ことでしょう。しかし、必ず";
			mes "手に入れなければならないのです。";
			mes "それは私だけではなく、あなたにも";
			mes "必要な品なのです。";
			close;
		}
		if(SIGN_QUE > 200) {
			mes "[キルケラ]";
			mes "これ以上言うことはありません。";
			close;
		}
		mes "[キルケラ]";
		mes "まだ何か？";
		mes "生きている者は、生きる者の世界へ";
		mes "帰るべきです。";
		close;
	}
}

niflheim.gat,102,54,4	script	威圧感のある男	739,{
	if(SIGN_QUE < 82) {
		mes "[レイキン]";
		mes "なに？　どこかで見たことあるって？";
		mes "世の中には自分とそっくりな人物が";
		mes "3人いると言うだろう。そうだな、";
		mes "人に限らずモンスターも数えたら";
		mes "3体以上いるかもな。";
		close;
	}
	if(SIGN_QUE < 96) {
		mes "[レイキン]";
		mes "ここも悪くはない。";
		mes "神々が暮らすアスガルドの";
		mes "圧迫感に比べれば、";
		mes "ニブルヘイムはずっと自由だ。";
		next;
		mes "[レイキン]";
		mes "神々に追放されてここに来たが、";
		mes "むしろ感謝したいくらいだ。";
		close;
	}
	switch(SIGN_QUE) {
	case 96:
		mes "[レイキン]";
		mes "アングルボダ？";
		mes "あぁ、巨人族の女か。";
		mes "神々によって捕らわれた後、";
		mes "魂を5つにわけられて、ミッドガルドの";
		mes "一番深い場所に封印されたんだ。";
		next;
		mes "[レイキン]";
		mes "神々の災いとなる、ロキ等3人の子を";
		mes "産んだからとは言え、過酷な処分だ。";
		mes "死んでも安息が得られないんだからな。";
		next;
		menu "ミッドガルドで一番深い場所？",-;
		mes "[レイキン]";
		mes "そう、一番深く、危険な場所だ。";
		mes "凶悪なモンスターが、";
		mes "うじゃうじゃいるって話だ。";
		next;
		mes "[レイキン]";
		mes "どこか分からない？";
		mes "くすくす、知りたいか？";
		next;
		mes "[レイキン]";
		mes "もっと詳しく聞きたければ……";
		mes "そうだな、40,000zenyくれ。";
		next;
		if(select("あげる","あげない")==2) {
			mes "[レイキン]";
			mes "ま、頑張れや。";
			close;
		}
		if(Zeny < 40000) {
			emotion 32;
			mes "[レイキン]";
			mes "金、ないじゃないか。";
			mes "冷やかしか？";
			close;
		}
		mes "[レイキン]";
		mes "よし、教えてやろう。";
		mes "それはグラストヘイムの最下層。";
		mes "そこで……";
		next;
		set '@rand,rand(1,4);
		mes "[レイキン]";
		switch('@rand) {
		case 1:
			mes "^0000FF「大きな1時」「大きな5時」";
			mes "「大きな7時」「小さな6時」^000000を";
			break;
		case 2:
			mes "^0000FF「大きな4時」「大きな10時」";
			mes "「小さな6時」「とても小さな11時」^000000を";
			break;
		case 3:
			mes "^0000FF「大きな5時」「小さな11時」";
			mes "「小さな6時」「とても小さな11時」^000000を";
			break;
		case 4:
			mes "^0000FF「大きな4時」「大きな5時」";
			mes "「大きな10時」「小さな11時」^000000を";
			break;
		}
		mes "探してみな。";
		next;
		mes "[レイキン]";
		mes "今教えた場所に、なんらかの痕跡が";
		mes "残されているはずだ。";
		next;
		mes "[レイキン]";
		mes "いいか、他人には絶対に教えるなよ。";
		next;
		if(select("分かりました","大きな、小さなってどういう意味？")==1) {
			mes "[レイキン]";
			mes "よし……";
			set Zeny,Zeny-40000;
			set SIGN_QUE,SIGN_QUE+'@rand;
			close;
		}
		mes "[レイキン]";
		mes "世の中、ただより高いもんはない。";
		mes "そうだな、あと20,000zenyくれたら";
		mes "教えてやろう。";
		next;
		if(select("あげない","あげる")==1) {
			emotion 32;
			mes "[レイキン]";
			mes "そうか。";
			set Zeny,Zeny-40000;
			set SIGN_QUE,SIGN_QUE+'@rand;
			close;
		}
		if(Zeny < 40000) {
			emotion 32;
			mes "[レイキン]";
			mes "金、ないじゃないか。";
			mes "冷やかしか？";
			close;
		}
		mes "[レイキン]";
		mes "「大きな」「小さな」は中央からの";
		mes "距離を指している。";
		next;
		mes "[レイキン]";
		mes "「大きな」は一番外側、";
		mes "「小さな」は外側よりちょっと内側、";
		mes "「とても小さな」は中央に近い内側だと";
		mes "思ってくれ。わかったな。";
		set Zeny,Zeny-60000;
		set SIGN_QUE,SIGN_QUE+'@rand+4;
		close;
	case 97:
	case 98:
	case 99:
	case 100:
		mes "[レイキン]";
		mes "まだ分からないことがある？";
		mes "20,000zenyくれるなら教えてやろう。";
		next;
		if(select("あげない","あげる")==1) {
			emotion 32;
			mes "[レイキン]";
			mes "あっ、そう。";
			close;
		}
		if(Zeny < 40000) {
			mes "[レイキン]";
			mes "金、ないじゃないか。";
			mes "冷やかしか？";
			close;
		}
		mes "[レイキン]";
		mes "「大きな」「小さな」は中央からの";
		mes "距離を指している。";
		next;
		mes "[レイキン]";
		mes "「大きな」は一番外側、";
		mes "「小さな」は外側よりちょっと内側、";
		mes "「とても小さな」は中央に近い内側だと";
		mes "思ってくれ。わかったな。";
		set Zeny,Zeny-20000;
		set SIGN_QUE,SIGN_QUE+4;
		close;
	case 101:
	case 102:
	case 103:
	case 104:
		mes "[レイキン]";
		mes "よし、ボーナス情報だ。";
		mes "その封印というのは、もちろん";
		mes "神が作った。";
		mes "だから、生半可な力では";
		mes "決して破ることが出来ない。";
		next;
		mes "[レイキン]";
		mes "堅くて重い、そして大きな力を持った";
		mes "武器だけが封印を破ることができる。";
		next;
		mes "[レイキン]";
		mes "だがな……";
		mes "神が作った封印を破るというのが、";
		mes "どういう意味か良く考えることだ。";
		next;
		mes "[レイキン]";
		mes "そして、封印には";
		mes "^FF0000特定の法則^000000があると";
		mes "覚えておくといい。";
		close;
	default:
		if(SIGN_QUE < 150) {
			mes "[レイキン]";
			mes "ここも悪くはない。";
			mes "神々が暮らすアスガルドの";
			mes "圧迫感に比べれば、";
			mes "百倍も千倍もマシだ。";
			close;
		}
		mes "[レイキン]";
		mes "………………";
		mes "あ……";
		mes "………………";
		mes "…………";
		close;
	}
}

gl_dun02.gat,262,265,0	script	神秘的な気配#1	111,{
	set '@num,strnpcinfo(2);
	switch('@num) {
		case 1: set '@flag,101; break;
		case 2: setarray '@flag,102,104; break;
		case 3: setarray '@flag,103,105,108; break;
		case 4: set '@flag,109; break;
		case 5: setarray '@flag,106,112; break;
		case 6: setarray '@flag,107,116; break;
		case 7: setarray '@flag,110,111,113; break;
		case 8: setarray '@flag,114,115; break;
	}
	set '@len,getarraysize('@flag);
	for(set '@i,0; '@i<'@len; set '@i,'@i+1) {
		if(SIGN_QUE == '@flag['@i])
			break;
	}
	if('@i == '@len) {
		mes "神秘的な気配を感じる。";
		mes "しかし同時に陰鬱な気配も感じられる。";
		close;
	}
	if(countitem(1530)) set '@power,50;
	else if(countitem(1363)) set '@power,66;
	else if(countitem(1722) || countitem(1471)) set '@power,68;
	else if(countitem(1369) || countitem(1470)) set '@power,70;
	else if(countitem(1367) || countitem(1368) || countitem(1466) || countitem(1469)) set '@power,72;
	else if(countitem(1365) || countitem(1366) || countitem(1473)) set '@power,74;
	else if(countitem(1170) || countitem(1468) || countitem(1168) || countitem(1169)) set '@power,76;
	else if(countitem(1364) || countitem(1913)) set '@power,78;
	else if(countitem(1261) || countitem(1528) || countitem(1167)) set '@power,80;
	else if(countitem(1305) || countitem(1720) || countitem(1136) || countitem(1137) || countitem(1166)) set '@power,82;
	else if(countitem(1164) || countitem(1165) || countitem(1467) || countitem(1138) || countitem(1139) || countitem(1224) || countitem(1225) || countitem(1416) || countitem(1526)) set '@power,84;
	else if(countitem(1135) || countitem(1140) || countitem(1141) || countitem(1527)) set '@power,86;
	else if(countitem(1237) || countitem(1524) || countitem(1525) || countitem(1557) || countitem(1415) || countitem(1964)) set '@power,88;
	else if(countitem(1132) || countitem(1134) || countitem(1233) || countitem(1234) || countitem(1235) || countitem(1414) || countitem(1523) || countitem(1236)) set '@power,90;
	else if(countitem(1131) || countitem(1230) || countitem(1232)) set '@power,92;
	else if(countitem(1719) || countitem(1130) || countitem(1133) || countitem(1223) || countitem(1229) || countitem(1231) || countitem(1413) || countitem(1814) || countitem(1242)) set '@power,94;
	else if(countitem(1227) || countitem(1228) || countitem(1240) || countitem(1241) || countitem(1962) || countitem(1813)) set '@power,96;
	else if(countitem(1558) || countitem(1963)) set '@power,98;
	else {
		mes "-現在アイテムウィンドウに";
		mes "所持している武器では";
		mes "封印を解くことはできません-";
		close;
	}
	if(rand(100) < '@power) {
		mes "-封印を勢いよく叩いてみたが、";
		mes "まったく反応がない-";
		mes "-もっと強い衝撃を与えなければ";
		mes "ならないようだ-";
		close;
	}
	if((SIGN_QUE == 116 && '@num == 6) || (SIGN_QUE == 113 && '@num == 7) || '@num == 8) {
		mes "最後の魂のかけらを得た瞬間、";
		mes "4つのかけらが宙に浮かび上がり、";
		mes "徐々に光を含んだ、一つの透明な";
		mes "宝石となった。";
		next;
		mes "静かにあなたの手に落ちた";
		mes "その宝石が、あなたの頭の中に";
		mes "直接話しかけてきた。";
		next;
		mes "私の魂を君に預けよう。";
		mes "私を死者の主に導いてくれ……";
		delitem 7306,3;
		set SIGN_QUE,117;
		getitem 7307,1;
		close;
	}
	mes "-武器を振り下ろした瞬間、";
	mes "封印が解け、神秘的な光が流れ出した-";
	mes "-神秘的な光を発している何かを";
	mes "見つけた！-";
	next;
	mes "-魂のかけらをみつけた-";
	set SIGN_QUE,SIGN_QUE+4;
	getitem 7306,1;
	close;
}

gl_dun02.gat,271,100,0	duplicate(神秘的な気配#1)	神秘的な気配#2	111
gl_dun02.gat,268,32,0	duplicate(神秘的な気配#1)	神秘的な気配#3	111
gl_dun02.gat,16,26,0	duplicate(神秘的な気配#1)	神秘的な気配#4	111
gl_dun02.gat,42,251,0	duplicate(神秘的な気配#1)	神秘的な気配#5	111
gl_dun02.gat,123,234,0	duplicate(神秘的な気配#1)	神秘的な気配#6	111
gl_dun02.gat,140,72,0	duplicate(神秘的な気配#1)	神秘的な気配#7	111
gl_dun02.gat,119,182,0	duplicate(神秘的な気配#1)	神秘的な気配#8	111

que_sign01.gat,45,227,4	script	死者の主	856,{
	if(SIGN_QUE < 117) {
		mes "[ヘル]";
		mes "ぬしは招待されていない身で";
		mes "この我と会いに来たと申すのか？";
		mes "無礼者め！";
		mes "ぬしの世界へ帰るがよい！";
		close2;
		percentheal -100,0;
		end;
	}
	switch(SIGN_QUE) {
	case 117:
		mes "[ヘル]";
		mes "死者達から歓迎されぬが故、ここに";
		mes "来るまで、手数をかけてしまったな。";
		mes "ガングルラティから、ぬしが";
		mes "アングルボダの魂を持ってきたと";
		mes "聞いた。";
		next;
		mes "[ヘル]";
		mes "我は長い間、アングルボダを";
		mes "探していた。礼を言わねばなるまい。";
		mes "何か願いがあるなら、言ってみよ。";
		next;
		menu "あなたの印をください",-;
		mes "[ヘル]";
		mes "印を得たいと？";
		mes "まさに、我の全権威を寄こせと";
		mes "言っているようなもの。";
		next;
		mes "[ヘル]";
		mes "アングルボダの魂を取り戻して";
		mes "くれた事は感謝する。";
		mes "しかし、それでそんな無理な要求が";
		mes "通ると思うか。";
		next;
		menu "では、どうすれば印を得られますか？",-;
		mes "[ヘル]";
		mes "そこまで願うのなら、1回だけ、";
		mes "印の権威を使うことを許そう。";
		next;
		mes "[ヘル]";
		mes "全ての死者を治め、支配する資格として";
		mes "どんな命令でも下すことができる。";
		mes "しかし、肝に銘じるがよい。";
		mes "1回だけだとな。";
		next;
		mes "-^FF0000九つの世界の象徴^000000を獲得した-";
		delitem 7307,1;
		set SIGN_QUE,118;
		getitem 7305,1;
		close;
	case 142:
		mes "[ヘル]";
		mes "ああ、来たか……";
		next;
		mes "[ヘル]";
		mes "やはり、ぬしから不思議な気配が";
		mes "感じられる。我に近いような……";
		mes "そんな気配がな。";
		next;
		mes "[ヘル]";
		mes "ぬし、何か珍しい気配のする品を";
		mes "手にしたことはないか？";
		next;
		if(select("The Sign","スタージュエル")==1) {
			mes "[ヘル]";
			mes "いや、それではない……";
			mes "気配の感じからして、もっと前に";
			mes "触れておるはず。";
			close;
		}
		mes "[ヘル]";
		mes "そうか……";
		mes "まさか、それを持っておるとはな……";
		next;
		mes "[ヘル]";
		mes "しばらく私に貸してはくれんか。";
		mes "面白いものを見せてやろう。";
		next;
		if(select("はい","いいえ")==2) {
			mes "[ヘル]";
			mes "はは、面白い。";
			mes "この我の頼みを真っ向から";
			mes "断るとはな。";
			next;
			mes "[ヘル]";
			mes "良い、今回だけは特別に許そう。";
			mes "しかし、次は考え直すが良い。";
			close2;
			warp "niflheim.gat",29,154;
			end;
		}
		mes "[ヘル]";
		mes "では、こちらへ。";
		mes "何、すぐ終わる";
		delitem 7178,1;
		set SIGN_QUE,143;
		close;
	case 143:
		mes "[ヘル]";
		mes "…………";
		next;
		misceffect 13;
		next;
		misceffect 32;
		next;
		misceffect 183;
		next;
		misceffect 90;
		next;
		mes "[ヘル]";
		mes "思っておったより手こずったか。";
		mes "ほれ、手を出せ。";
		next;
		set SIGN_QUE,144;
		getitem 7025,1;
		mes "[ヘル]";
		mes "ん、これは何かとな？";
		mes "これこそ、神の涙と呼ばれていた";
		mes "ものの本来の姿。";
		next;
		mes "[ヘル]";
		mes "ぬし等が知っていると思っている";
		mes "過去や史実は、実際には違うことも";
		mes "あるのだと、忘れるでない。真実は、";
		mes "ほんのひとかけらしかない。";
		next;
		mes "[ヘル]";
		mes "興味があるなら、神々の役目、";
		mes "魔王の役目とは何か、";
		mes "調べてみるといい。";
		next;
		mes "[ヘル]";
		mes "我が教えられるのはここまで。";
		mes "あとは、自分で調べるがいい。";
		close;
	default:
		if(SIGN_QUE < 142) {
			mes "[ヘル]";
			mes "ぬしがそれを、どのように使おうが";
			mes "自由。しかし、その結果は自ら責任を";
			mes "負うがよい。";
			close;
		}
		mes "[ヘル]";
		mes "まだ何か用か？";
		close;
	}
}

que_sign01.gat,46,56,0	script	噴水台	111,{
	if(SIGN_QUE < 118) {
		mes "噴水だ。";
		mes "あふれ出している水は";
		mes "とてもきれいに見える。";
		next;
		if(select("水を飲んでみる","水を飲まない")==2) {
			mes "…………";
			close;
		}
		mes "………………";
		close2;
		percentheal -100,0;
		end;
	}
	mes "噴水だ。";
	mes "水を空きビンに入れようか？";
	next;
	if(select("入れる","入れない")==2) {
		mes "…………";
		close;
	}
	if(countitem(713) < 1) {
		mes "空きビンがない。";
		close;
	}
	delitem 713,1;
	getitem 12020,1;
	close;
}

que_sign02.gat,378,235,0	script	signwarp	45,1,1,{
	if(countitem(7313) == 1 && (SIGN_QUE < 124 || SIGN_QUE > 126)) {
		warp "que_sign01.gat",197,190;
		end;
	}
	if(getnpctimer(1,"SignTimer#witch")) {
		mes "何かが進入を阻んでいる。";
		close;
	}
	initnpctimer "SignTimer#witch";
	warp "que_sign01.gat",197,190;
	end;
}

que_sign01.gat,0,0,0	script	SignTimer#witch	-1,{
OnTimer600000:
	areawarp "que_sign01.gat",166,162,229,227,"niflheim.gat",30,156;
	end;
OnTimer620000:
	killmonster "que_sign01.gat","SignTimer#witch::OnKilled";
	hideoffnpc "セリン#witch";
	set 'mob,0;
	stopnpctimer;
	end;
OnKilled:
	set 'mob,'mob-1;
	if('mob < 1)
		hideoffnpc "セリン#witch";
	end;
}

que_sign01.gat,197,195,4	script	セリン#witch	90,{
	if(SIGN_QUE < 124) {
		emotion 9;
		mes "[セリン]";
		mes "…………";
		close;
	}
	switch(SIGN_QUE) {
	case 124:
		mes "[セリン]";
		mes "とうとうここまでいらして";
		mes "しまったのですね。";
		mes "私が何をしようとしていたか、";
		mes "魔女から聞いたのでしょう。";
		next;
		mes "[セリン]";
		mes "彼女は、私が何を考えていたのか";
		mes "知ってしまった。";
		mes "だから、私を監視していたのです。";
		next;
		menu "どうしてこんな事を……",-;
		mes "[セリン]";
		mes "魔女から聞いて知っていると思いますが";
		mes "私は人間になりたいのです。";
		next;
		mes "[セリン]";
		mes "ニブルヘイムに留まり、死という名の";
		mes "空気を呼吸し、絶望という名の食物を";
		mes "食べて暮らし続けたくないのです。";
		next;
		menu "それでダークロードを……",-;
		mes "[セリン]";
		mes "あなたがヘル様からいただいた権利は";
		mes "1回しか使えません。";
		mes "それでは、私を生の世界、";
		mes "ミッドガルドに導くのは不可能です。";
		next;
		mes "[セリン]";
		mes "そうなると、";
		mes "私の願いをかなえられるのは";
		mes "ダークロードだけ。";
		next;
		menu "ダークロードが召喚されたら！",-;
		mes "[セリン]";
		mes "もちろん、ダークロードがこの世界に";
		mes "現われれば、どうなってしまうか";
		mes "分かっています。";
		mes "ダークロードはミッドガルドを破壊し、";
		mes "幾多の死をもたらすでしょう。";
		next;
		menu "それじゃあ、生まれ変わっても！",-;
		mes "[セリン]";
		mes "………………";
		mes "あなたの言葉どおり、破壊された";
		mes "ミッドガルドに生き返っても意味は";
		mes "ないのでしょう……";
		next;
		mes "[セリン]";
		mes "でも、ニブルヘイムでの苦痛と滲めさに";
		mes "じっと耐えているより、ずっといい。";
		next;
		mes "[セリン]";
		mes "私の願いは「生」。";
		mes "ただ、それだけ。";
		mes "生きているというその証拠を";
		mes "感じたいんです。";
		next;
		mes "[セリン]";
		mes "だから、世界がどうなるかは";
		mes "関係ありません。";
		next;
		mes "[セリン]";
		mes "甘い空気を吸いたい。";
		mes "心臓がドキドキするのを感じたい。";
		mes "体温を持った肉体が欲しい……";
		next;
		mes "[セリン]";
		mes "こんな私を哀れに思うなら";
		mes "見逃してください……";
		mes "お願い……";
		mes "どうか、邪魔しないで……";
		next;
		if(select("彼女を止める","彼女を見逃す")==1) {
			set SIGN_QUE,125;
			close;
		}
		mes "[セリン]";
		mes "……ありがとうございます。";
		mes "しかし、あなたは神の試練を";
		mes "パスできなくなるかもしれません。";
		next;
		mes "[セリン]";
		mes "いえ、きっと神は許さないでしょう。";
		mes "あなたは、勇気を示すために、ここまで";
		mes "苦しい道を歩いてきました。";
		mes "それを全て投げ出すのですよ。";
		next;
		mes "[セリン]";
		mes "本当に……良いのですか？";
		next;
		if(select("やはりミッドガルドのため……","うん……")==1) {
			set SIGN_QUE,125;
			close;
		}
		mes "[セリン]";
		mes "……最後の力で、あなたを";
		mes "ミッドガルドに送りましょう。";
		next;
		mes "[セリン]";
		mes "ありがとう……";
		set SIGN_QUE,200;
		if(checkre())
			getexp 20000,0;
		else
			getexp 200000,0;
		stopnpctimer "SignTimer#witch";
		close2;
		warp "umbala.gat",132,203;
		end;
	case 125:
		mes "[セリン]";
		mes "……ダークロードを召喚できない以上";
		mes "あなたに抵抗するのは無駄でしょう。";
		mes "でも…………";
		next;
		mes "[セリン]";
		mes "私は万が一のため、召喚に必要な力、";
		mes "すなわち、たくさんの死者の絶望を";
		mes "集めてきました。";
		next;
		if(countitem(2643)) {
			mes "[セリン]";
			mes "私の頼みで、あなたが手伝ってくれた";
			mes "魂たちのこと……";
			mes "結果はどうでした？";
			mes "結局、救済されたはずの魂も、";
			mes "絶望から脱することができずにいる。";
			next;
			mes "[セリン]";
			mes "ニブルヘイムに居るアラキナは、";
			mes "自分が死んだことを知らない。";
			mes "家へ帰れるという希望を抱いたのに";
			mes "結局は帰れず、さらに大きな絶望を";
			mes "味わった。";
		}
		else {
			mes "[セリン]";
			mes "私の最初の頼みを断ったことで、";
			mes "助けを得られなかった魂は絶望に";
			mes "捕らわれ、ニブルヘイムに留まって";
			mes "います。";
		}
		next;
		mes "[セリン]";
		mes "あなたがしたことは、結果として";
		mes "苦痛にしか呼ばなかった。";
		mes "そう、私は最初からそうなると思い";
		mes "あなたにあのようなお願いを";
		mes "したのです。";
		next;
		if(countitem(2643)) {
			mes "[セリン]";
			mes "そして、実際その通りになった。";
			mes "あなたのおかげで、彼女の絶望は増し";
			mes "その絶望は私の力となった……";
			next;
		}
		mes "[セリン]";
		mes "ダークロードに売る私の魂は、";
		mes "そんな力を少しずつためていた……";
		mes "彼を召喚するために……";
		next;
		mes "[セリン]";
		mes "本当は、あなたと争いたくない……";
		next;
		mes "[セリン]";
		mes "しかし、それしか方法がないなら……";
		mes "私が生まれ変わるには";
		mes "それしかないなら……";
		mes "私は負けない、絶対に負けない！";
		mes "戦います、あなたと！";
		close2;
		set SIGN_QUE,126;
		set getvariableofnpc('mob,"SignTimer#witch"),10;
		monster "que_sign01.gat",196,195,"ダークロードの分身",1605,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",180,180,"エンシェントマミー",1522,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",210,210,"エンシェントマミー",1522,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",200,200,"エンシェントレイス",1475,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",200,180,"エンシェントレイス",1475,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",180,200,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",205,205,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",190,190,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",205,190,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",190,205,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		hideonnpc;
		end;
	case 126:
		mes "[セリン]";
		mes "……これが、私のしようと";
		mes "していた事に対する答えなのですね。";
		next;
		mes "[セリン]";
		mes "もう私には、全ての記憶を失い、";
		mes "ニブルヘイムという名の死の中で";
		mes "生きていくしか、選択は";
		mes "ないのですね……";
		next;
		mes "[セリン]";
		mes "1つだけ、聞いても良いですか？";
		mes "どうして、あなたは印を持っていながら";
		mes "その薬を飲めと、命令しなかったの";
		mes "ですか？";
		next;
		mes "[セリン]";
		mes "その印を使えば……私を含む";
		mes "あらゆる死者に、どんな命令でも";
		mes "下すことが出来たのに……";
		next;
		mes "[セリン]";
		mes "………………";
		next;
		mes "[セリン]";
		mes "そうですね……";
		mes "あなたの目を見れば、";
		mes "分かる気がします。";
		next;
		mes "[セリン]";
		mes "最後の最後まで私に、機会を";
		mes "与えてくれていたのですね……";
		mes "そして、それを投げ捨てたのは、";
		mes "私自身……";
		next;
		mes "[セリン]";
		mes "ありがとう……";
		next;
		mes "[セリン]";
		mes "空虚な魂だけの私だけど、";
		mes "あなたのような人に会えてよかった。";
		next;
		mes "[セリン]";
		mes "まるで命を得たような……";
		mes "大切で……";
		mes "暖かい……";
		mes "そんな出会いをくれて、";
		mes "本当にありがとう……";
		next;
		mes "[セリン]";
		mes "すべての記憶を失っても、";
		mes "出来れば……あなたに関する記憶は";
		mes "失いたくない……";
		next;
		mes "[セリン]";
		mes "いいえ、きっと忘れません。";
		mes "やっと出会えた、命の温もりだから……";
		next;
		mes "[セリン]";
		mes "ありがとう……";
		mes "あなたの未来に幸あらんことを……";
		delitem 7308,1;
		set SIGN_QUE,127;
		close;
	case 127:
		mes "-あなたは倒れたセリンを抱きかかえ";
		mes "ニブルヘイムへと帰って行った-";
		close2;
		set SIGN_QUE,128;
		stopnpctimer "SignTimer#witch";
		warp "que_sign01.gat",117,137;
		close;
	case 198:
		mes "[セリン]";
		mes "まだ諦められないのですか？";
		mes "………………";
		mes "お願い、これ以上、私の邪魔を";
		mes "しないで！";
		close2;
		set SIGN_QUE,126;
		set getvariableofnpc('mob,"SignTimer#witch"),10;
		monster "que_sign01.gat",196,195,"ダークロードの分身",1605,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",180,180,"エンシェントマミー",1522,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",210,210,"エンシェントマミー",1522,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",200,200,"エンシェントレイス",1475,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",200,180,"エンシェントレイス",1475,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",180,200,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",205,205,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",190,190,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",205,190,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		monster "que_sign01.gat",190,205,"腐った死体",1423,1,"SignTimer#witch::OnKilled";
		hideonnpc;
		end;
	case 200:
		mes "[セリン]";
		mes "……最後の力で、あなたを";
		mes "ミッドガルドに送りましょう。";
		close2;
		stopnpctimer "SignTimer#witch";
		warp "umbala.gat",132,203;
		end;
	default:
		mes "[セリン]";
		mes "………………";
		close;
	}
}

que_sign01.gat,0,0,0	script	SignTimer#serin	-1,{
OnTimer600000:
	areawarp "que_sign01.gat",166,12,229,77,"niflheim.gat",30,156;
	end;
OnTimer620000:
	killmonster "que_sign01.gat","SignTimer#serin::OnKilled";
	hideoffnpc "セリン#serin";
	hideonnpc "セリン#dummy";
	hideonnpc "ダークロード#serin";
	stopnpctimer;
	end;
OnKilled:
	hideoffnpc "セリン#serin";
	end;
}

que_sign01.gat,196,39,4	script	セリン#serin	90,{
	if(SIGN_QUE < 132) {
		mes "[セリン]";
		mes "……？";
		close;
	}
	switch(SIGN_QUE) {
	case 132:
		mes "[セリン]";
		mes "この魔力は……どうやら、";
		mes "魔方陣は完成しているようです。";
		mes "たぶんその印が、最後に必要な";
		mes "材料なのでしょう。";
		next;
		mes "[セリン]";
		mes "魔方陣を破壊しましょう。";
		mes "あの、その印を私にくれませんか？";
		mes "この魔方陣を完全に消し去るため、";
		mes "どうしても必要なのです。";
		next;
		menu "渡す",-;
		mes "[セリン]";
		mes "危ないから離れてください！";
		delitem 7305,1;
		set SIGN_QUE,133;
		hideoffnpc "セリン#dummy";
		initnpctimer "セリン#dummy";
		hideonnpc;
		close;
	case 133:
		mes "[セリン]";
		mes "……ごめんなさい。";
		mes "ダークロードを召喚するには、";
		mes "この方法しかなかったんです。";
		next;
		menu "……どうして?!",-;
		mes "[セリン]";
		mes "…………";
		mes "ダークロードを召喚する代わりに";
		mes "願いをかなえて欲しかったのは、";
		mes "魔女ではありません。";
		mes "私です……";
		next;
		menu "なぜ……",-;
		mes "[セリン]";
		mes "……私は、人間になりたいのです。";
		mes "ニブルヘイムに留まり、";
		mes "死という名の空気を呼吸し、";
		mes "絶望という名の食物を食べて";
		mes "暮らし続けたくないのです。";
		next;
		menu "それでダークロードを……",-;
		mes "[セリン]";
		mes "あなたがヘル様からいただいた権利は";
		mes "1回しか使えません。";
		mes "それでは、私を生の世界、";
		mes "ミッドガルドに導くのは不可能です。";
		next;
		mes "[セリン]";
		mes "そうなると、";
		mes "私の願いをかなえられるのは";
		mes "ダークロードだけ。";
		next;
		menu "ダークロードが召喚されたら！",-;
		mes "[セリン]";
		mes "もちろん、ダークロードがこの世界に";
		mes "現われれば、どうなってしまうか";
		mes "分かっています。ダークロードは、";
		mes "ミッドガルドを破壊し、幾多の死を";
		mes "もたらすでしょう。";
		next;
		menu "それじゃあ、生まれ変わっても！",-;
		mes "[セリン]";
		mes "………………";
		mes "あなたの言葉どおり、荒野となった";
		mes "ミッドガルドに生き返っても意味は";
		mes "ないのでしょう……";
		mes "でも、ニブルヘイムでの苦痛と惨めさに";
		mes "じっと耐えているより、ずっといい。";
		next;
		mes "[セリン]";
		mes "私の願いは「生」。";
		mes "ただ、それだけ。";
		mes "生きているというその証を";
		mes "感じたいんです。";
		next;
		mes "[セリン]";
		mes "だから、世界がどうなるかは";
		mes "関係ありません。";
		next;
		mes "[セリン]";
		mes "甘い空気を吸いたい。";
		mes "心臓がドキドキするのを感じたい。";
		mes "体温を持った肉体が欲しい……";
		next;
		mes "[セリン]";
		mes "こんな私を哀れに思うなら";
		mes "見逃してください……";
		mes "お願い……";
		mes "どうか、邪魔しないで……";
		next;
		if(select("彼女を見逃す","彼女を止める")==1) {
			mes "[セリン]";
			mes "……ありがとうございます。";
			mes "しかし、あなたは神の試練を";
			mes "パスできなくなるかもしれません。";
			next;
			mes "[セリン]";
			mes "いえ、きっと神は許さないでしょう。";
			mes "あなたは、勇気を示すために、ここまで";
			mes "苦しい道を歩いてきました。";
			mes "それを全て投げ出すのですよ。";
			next;
			mes "[セリン]";
			mes "本当に……良いのですか？";
			next;
			if(select("やはりミッドガルドのため……","うん……")==2) {
				mes "[セリン]";
				mes "……最後の力で、あなたを";
				mes "ミッドガルドに送りましょう。";
				next;
				mes "[セリン]";
				mes "ありがとう……";
				set SIGN_QUE,200;
				if(checkre())
					getexp 20000,0;
				else
					getexp 200000,0;
				stopnpctimer "SignTimer#serin";
				close2;
				warp "umbala.gat",132,203;
				end;
			}
		}
		mes "[セリン]";
		mes "本当は、あなたと争いたくない……";
		mes "しかし、それしか方法がないなら……";
		mes "私が生まれ変わるには";
		mes "それしかないなら……";
		mes "私は負けない、絶対に負けない！";
		mes "戦います、あなたと！";
		next;
		emotion 29,"ダークロード#serin";
		mes "[ダークロード]";
		mes "私に立ち向かうと言うのか。";
		mes "たかが人間のくせに、生意気な。";
		mes "それなら、まずお前から";
		mes "血祭りに上げてくれよう！";
		close2;
		set SIGN_QUE,134;
		hideonnpc;
		hideonnpc "ダークロード#serin";
		monster "que_sign01.gat",196,44,"ダークロードの分身",1605,1,"SignTimer#serin::OnKilled";
		end;
	case 134:
		mes "[セリン]";
		mes "……これが、私のしようと";
		mes "していた事に対する答えなのですね。";
		next;
		mes "[セリン]";
		mes "もう私には、全ての記憶を失い、";
		mes "ニブルヘイムという名の死の中で";
		mes "生きていくしか、選択は";
		mes "ないのですね……";
		next;
		mes "[セリン]";
		mes "1つだけ、聞いても良いですか？";
		mes "どうして、あなたは印を持っていながら";
		mes "私に止めろと命令しなかったの";
		mes "ですか？";
		next;
		mes "[セリン]";
		mes "その印を使えば……私を含む";
		mes "あらゆる死者に、どんな命令でも";
		mes "下すことが出来たのに……";
		next;
		mes "[セリン]";
		mes "………………";
		next;
		mes "[セリン]";
		mes "そうですね……";
		mes "あなたの目を見れば、";
		mes "分かる気がします。";
		next;
		mes "[セリン]";
		mes "最後の最後まで私に、機会を";
		mes "与えてくれていたのですね……";
		mes "そして、それを投げ捨てたのは、";
		mes "私自身……";
		next;
		mes "[セリン]";
		mes "ありがとう……";
		next;
		mes "[セリン]";
		mes "空虚な魂だけの私だけど、";
		mes "あなたのような人に会えてよかった。";
		next;
		mes "[セリン]";
		mes "まるで命を得たような……";
		mes "大切で……";
		mes "暖かい……";
		mes "そんな出会いをくれて、";
		mes "本当にありがとう……";
		next;
		mes "[セリン]";
		mes "すべての記憶を失っても、";
		mes "出来れば……あなたに関する記憶は";
		mes "失いたくない……";
		next;
		mes "[セリン]";
		mes "いいえ、きっと忘れません。";
		mes "やっと出会えた、命の温もりだから……";
		next;
		mes "[セリン]";
		mes "ありがとう……";
		mes "あなたの未来に幸あらんことを……";
		set SIGN_QUE,135;
		close;
	case 135:
		mes "-あなたは倒れたセリンを抱きかかえ";
		mes "ニブルヘイムへと帰って行った-";
		close2;
		set SIGN_QUE,136;
		stopnpctimer "SignTimer#serin";
		warp "que_sign01.gat",117,137;
		close;
	case 199:
		mes "[セリン]";
		mes "まだ諦められないのですか？";
		mes "………………";
		mes "お願い、これ以上、私の邪魔を";
		mes "しないで！";
		close2;
		set SIGN_QUE,134;
		hideonnpc;
		hideonnpc "ダークロード#serin";
		monster "que_sign01.gat",196,44,"ダークロードの分身",1605,1,"SignTimer#serin::OnKilled";
		end;
	case 200:
		mes "[セリン]";
		mes "……最後の力で、あなたを";
		mes "ミッドガルドに送りましょう。";
		close2;
		stopnpctimer "SignTimer#serin";
		warp "umbala.gat",132,203;
		end;
	default:
		mes "[セリン]";
		mes "………………";
		close;
	}
}

que_sign01.gat,196,39,4	script	セリン#dummy	90,{
	end;
OnInit:
	hideonnpc;
	end;
OnTimer3000:
	misceffect 13;
	end;
OnTimer6000:
	misceffect 8;
	end;
OnTimer9000:
	misceffect 90;
	end;
OnTimer13000:
	hideonnpc;
	hideoffnpc "ダークロード#serin";
	hideoffnpc "セリン#serin";
	stopnpctimer;
	end;
}

que_sign01.gat,196,44,4	script	ダークロード#serin	737,{
	end;
OnInit:
	hideonnpc;
	end;
}

geffen.gat,119,48,0	script	噴水台	111,{
	if(countitem(7025) < 1) {
		mes "噴水台がある。";
		close;
	}
	mes "「魔王の嘆き」が不思議な光を";
	mes "放ち始めた。噴水台の一部が、";
	mes "その光に呼応するように";
	mes "光を放っている。";
	misceffect 200;
	misceffect 200,"";
	next;
	if(select("魔王の嘆きをかざす","無視する")==2) {
		mes "…………";
		close;
	}
	announce "光と共にゲフェニアへの門が開かれた",9,0x9CFF00;
	mes "魔王の涙を噴水台の光へかざすと";
	mes "噴水台が更に光り、見たことのない";
	mes "門が開いた。";
	misceffect 247;
	donpcevent "GefeniaWarp::OnStart";
	close;
}

geffen.gat,119,55,0	script	GefeniaWarp	45,1,1,{
OnTouch:
	//switch(rand(4)) { //旧仕様
	switch('rand) {
		case 0: warp "gefenia01.gat",58,169; break;
		case 1: warp "gefenia02.gat",116,115; break;
		case 2: warp "gefenia03.gat",130,206; break;
		case 3: warp "gefenia04.gat",133,88; break;
	}
	end;
OnInit:
	hideonnpc;
	end;
OnStart:
	set 'rand,rand(4);
	hideoffnpc;
	initnpctimer;
OnTimer10000:
OnTimer20000:
OnTimer30000:
OnTimer40000:
	misceffect 247;
	end;
OnTimer45000:
	hideonnpc;
	announce "ゲフェニアへの門が閉まります",9,0x9CFF00;
	stopnpctimer;
	end;
}
