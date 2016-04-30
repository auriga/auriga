//商人
-	script	NoviceExchange	-1,{
	if(Weight*100/MaxWeight >= 90) {
		mes "[商人]";
		mes "おいおい！";
		mes "怪力じゃないくせに";
		mes "何でそんなに持ち歩いてるんだ？";
		mes "カプラの倉庫にでも預けてこい。";
		close;
	}
	set '@code,strnpcinfo(5);	//識別子の#以降の文字列を参照して数値に変換
	switch('@code) {
		case 0:	//prontera
			setarray '@need,935,914,909;	//かたい皮、綿毛、ゼロピー
			setarray '@amount,5,10,10;	
			break;
		case 1:	//geffen
			setarray '@need,935,915,909;	//かたい皮、さなぎの皮、ゼロピー
			setarray '@amount,5,6,10;
			break;
		case 2:	//morocc
			setarray '@need,935,916,909;	//かたい皮、鳥の羽毛、ゼロピー
			setarray '@amount,5,7,10;
			break;
		case 3:	//aldebaran
			setarray '@need,955,916,909;	//蟲の皮、鳥の羽毛、ゼロピー
			setarray '@amount,1,7,10;
			break;
		case 4:	//payon
			setarray '@need,902,909;	//木の根、ゼロピー、0
			setarray '@amount,6,10;
			break;
	}
	mes "[商人]";
	mes "こんにちは！";
	mes "あのさ「" +getitemname('@need[0])+ "」や「" +getitemname('@need[1])+ "」";
	mes "というアイテムを持ってないか？";
	if('@code < 4)
		mes "あ、「ゼロピー」でもいいぞ。";
	mes "もし持ってたら、俺に少し";
	mes "分けてくれないか。";
	next;
	mes "[商人]";
	mes "もちろん、ただでもらおうなんて";
	mes "わけじゃない。そうだな……";
	mes "「" +getitemname('@need[0]) + '@amount[0]+ "個」か「" +getitemname('@need[1]) + '@amount[1]+ "個」";
	if('@code < 4)
		mes "または「ゼロピー10個」と";
	mes "「赤ポーション1個」を";
	mes "交換するのはどうだ？";
	next;
	switch (select("いいですよ！","何か損してる気が……","嫌です！")) {
	case 1:
		mes "[商人]";
		mes "「" +getitemname('@need[0])+ "」か「" +getitemname('@need[1])+ "」";
		if('@code < 4)
			mes "もしくは「ゼロピー」。";
		mes "さあ、どれと交換するんだ？";
		next;
		if('@code<4)
			set '@talk$,"「ゼロピー」を「赤ポーション」に";
		//payonの時は3番目の選択肢出ない
		set '@i,select("「"+getitemname('@need[0])+"」を「赤ポーション」に","「"+getitemname('@need[1])+"」を「赤ポーション」に",'@talk$,"やめておきます")-1;
		if('@i==3) {
			mes "[商人]";
			mes "そうか……";
			mes "まあ、気が向いたらまた来な。";
			close;
		}
		set '@have,countitem('@need['@i]);	//交換アイテム所持数
		if('@have < '@amount['@i]) {
			mes "[商人]";
			if('@code < 4 || '@i > 0)		//フェイヨンで木の根を選んだ場合は表示されない。(他の地域は未調査)
				mes "おい！";
			mes getitemname('@need['@i])+ "はどこにあるんだ？";
			mes "いくらなんでも" +getitemname('@need['@i])+ "が" +'@amount['@i]+ "個ないと";
			mes "赤ポーションは渡せないぞ。";
			close;
		}
		mes "[商人]";
		mes "ありがてぇ！";
		mes "それじゃ、何個交換しようか？";
		mes "ちょいと見せてみな。";
		next;
		set '@max,'@have / '@amount['@i];	//交換可能数
		mes "[商人]";
		mes getitemname('@need['@i])+ "は" +'@have+ "個";
		mes "あるのか……そうすると";
		mes "赤ポーションは" +'@max+ "個まで";
		mes "交換できるぞ。";
		next;
		mes "[商人]";
		mes getitemname('@need['@i])+ "を赤ポーションと交換するか？";
		next;
		if(select("交換します","やっぱりやめておきます")==2) {
			mes "[商人]";
			mes "……仕方ねぇな。";
			mes "また、気が向いたら来てくれよ。";
			close;
		}
		mes "[商人]";
		mes "赤ポーションは最大何個もらえるかは";
		mes "さっき教えたから、わかってるな？";
		next;
		mes "[商人]";
		mes "一度に交換できる赤ポーションの数は";
		mes "最小は1個、最大は100個だ。";
		mes "もし交換する気がないなら「0」と";
		mes "言ってくれ。";
		while(1) {
			next;
			input '@val;
			if('@val<0 || '@val>100) {
				mes "[商人]";
				mes "一度に交換できるのは";
				mes "100個までだって言っただろ！";
				mes "仕方ねぇな、もう一回聞いてやる。";
				mes "何個にするんだ？";
				continue;
			}
			break;
		}
		if('@val == 0) {
			mes "[商人]";
			mes "おいおい、そりゃないだろ。";
			mes "期待させるだけさせておいて……";
			mes "仕方ねぇな。気が向いたら";
			mes "また来てくれよ。";
			close;
		}
		if('@val > '@max) {
			mes "[商人]";
			mes "おい！それじゃあ、" +getitemname('@need['@i])+ "が";
			mes "足りないだろ？赤ポーションが";
			mes "何個まで交換できるか、きちんと";
			mes "確認してから来いよ。";
			close;
		}
		delitem '@need['@i],'@amount['@i]*'@val;
		getitem 501,'@val;
		mes "[商人]";
		mes "おし！これが赤ポーションだ。";
		mes "確認してくれ。ありがとよ。";
		mes "がははー！";
		close;
	case 2:
		mes "[商人]";
		mes "損してるかもだって？がははー。";
		mes "全然そんなことはないはずだぞ。";
		mes "どちらかと言えば、俺の方が";
		mes "損になる。まぁ、俺の条件が";
		mes "気にくわないなら仕方ないが。";
		close;
	case 3:
		mes "[商人]";
		mes "……チッ。仕方ねぇな。";
		mes "また気が向いたら来てくれよ。";
		close;
	}
}

prontera.gat,123,102,5	duplicate(NoviceExchange)	商人::NoviceExchange#0	85
geffen.gat,173,88,5	duplicate(NoviceExchange)	商人::NoviceExchange#1	85
morocc.gat,180,259,3	duplicate(NoviceExchange)	商人::NoviceExchange#2	85
aldebaran.gat,152,63,5	duplicate(NoviceExchange)	商人::NoviceExchange#3	85
payon.gat,200,134,5	duplicate(NoviceExchange)	商人::NoviceExchange#4	85


//ペリックス
//  ■ @change_jellopy

alberta.gat,190,173,3	script	ペリックス	85,{
	if(@change_jellopy == 0) {
		mes "[ペリックス]";
		mes "なんだ、俺に何か用か？";
		mes "いくら物欲しそうな顔したって";
		mes "何もやらんぞ。";
		next;
		mes "[ペリックス]";
		mes "何か欲しいなら仕事をしろ、仕事を！";
		mes "ん？仕事がないだって？";
		mes "仕方ねぇな……";
		next;
		mes "[ペリックス]";
		mes "じゃあ、ゼロピーを10個集めてこい。";
		mes "きちんと集めてきたらその報酬として";
		mes "赤ポーションをやろう。";
		next;
		mes "[ペリックス]";
		mes "10個がきついなら、3個でもいいぞ。";
		mes "ゼロピーを3個集めてきたら";
		mes "いもをやろう。";
		next;
		mes "[ペリックス]";
		mes "ゼロピーを手に入れたら";
		mes "またここに来な。";
		if(countitem(909))
			set @change_jellopy,1;
		close;
	}
	mes "[ペリックス]";
	mes "おお、ゼロピーを集めてきたのか。";
	mes "よし！赤ポーションかいも";
	mes "どっちと交換するんだ？";
	next;
	switch (select("赤ポーションをください","いもをください")) {
		case 1:
			set '@amount,10;
			set '@gain,501;
			break;
		case 2:
			set '@amount,3;
			set '@gain,516;
			break;
	}
	mes "[ペリックス]";
	mes "わかった。じゃあ、持ってきた物を";
	mes "見せてくれ。";
	next;
	if(countitem(909) < '@amount) {
		mes "[ペリックス]";
		mes "おい！" +getitemname('@gain)+ "が欲しかったら";
		mes "ゼロピーを" +'@amount+ "個集めてこいと";
		mes "言っただろ？";
		close;
	}
	set '@max,countitem(909) / '@amount;	//交換可能数
	mes "[ペリックス]";
	mes "よし、" +getitemname('@gain)+ "と交換してやろう。";
	mes getitemname('@gain)+ "はいくつ欲しいんだ？";
	next;
	switch (select("できる限り欲しいです","数を指定したいです","やっぱりやめておきます")) {
	case 1:
		set '@val,'@max;
		break;
	case 2:
		mes "[ペリックス]";
		mes "なら100個以下にしてくれ。";
		mes "もしやめるなら「0」と言えばいい。";
		mes "お前の持ってる数だと……";
		mes "最大" +'@max+ "個まで";
		mes getitemname('@gain)+ "をあげられるぞ。";
		while(1) {
			next;
			input '@val;
			if('@val < 0 || '@val > 100) {
				mes "[ペリックス]";
				mes "100個より多いと渡せないだろ。";
				mes "もう一度考えてくれ。";
				continue;
			}
			break;
		}
		if('@val == 0) {
			mes "[ペリックス]";
			mes "そうか。";
			mes "じゃあ、また気が向いたら来な。";
			close;
		}
		if('@val > '@max) {
			mes "[ペリックス]";
			mes "おや？それだとゼロピーが足りないぞ。";
			mes "もう少し集めてから来るんだな。";
			close;
		}
		break;
	case 3:
		mes "[ペリックス]";
		mes "じゃあ、また今度な。";
		close;
	}
	delitem 909,'@amount*'@val;
	getitem '@gain,'@val;
	mes "[ペリックス]";
	mes "ほらよ！";
	mes "約束の" +getitemname('@gain)+ "だ。";
	mes "大事に使うんだぞ。";
	close;
}
