//= Auriga Script ==============================================================
// Ragnarok Online Thanatos Tower Script	by refis
//==============================================================================
//赤のカギ
tha_t03.gat,67,70,0	script	機械の装置#tt1	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(countitem(7421) || countitem(7426)) {
		mes "‐珍しい模様の機械の装置が、";
		mes "小さな音を出しながら動いてる‐";
		close;
	}
	mes "‐強い力が機械の装置を覆っている‐";
	next;
	if(select("強い力を取り除く","立ち去る")==2) {
		mes "‐何か方法がないか、";
		mes "考えてみることにした‐";
		close;
	}
	if(getequipweaponlv(4) < 4) {
		mes "‐持っている武器を";
		mes "機械の装置に向かって、";
		mes "思いっきり振り下ろした‐";
		mes "‐しかし、空を切る音がしただけで、";
		mes "機械の装置を覆っている力を";
		mes "取り除くことはできなかった‐";
		next;
		mes "‐もっと強力な武器が必要なようだ‐";
		close;
	}
	mes "‐覆っている力に向かって、";
	mes "^nItemID^" +getequipid(4);
	mes "を思いっきり振り下ろした‐";
	next;
	mes "‐すると、^nItemID^" +getequipid(4);
	mes "と覆っていた力がぶつかり、";
	mes "バシッ!!っという音と共に";
	mes "光が消えた‐";
	next;
	if(select("機械の装置を調べる","立ち去る")==2) {
		mes "‐特に調査する必要はなさそうだ‐";
		close;
	}
	mes "‐機械の装置を調べていると、";
	mes "ピーーッ!!っという音と共に、";
	mes "画面が現われた‐";
	mes "‐恐らく、さっき何かに";
	mes "触れてしまったせいだろう‐";
	next;
	if(select("画面を見る","画面を無視する")==2) {
		mes "‐画面を無視し、";
		mes "機械の装置を調べてみると、";
		mes "端の方にしまわれていた";
		mes "鍵のような物を見つけた‐";
		mes "‐……単なる鍵ではなさそうだ‐";
		getitem 7421,1;
		close;
	}
	mes "ゲートの封印技術研究によって";
	mes "開発された技術を利用し、";
	mes "魔力石も別の場所に封印した。";
	next;
	mes "これでゲートと魔力石を封印した。";
	mes "だが、いつかは誰かに、この封印が";
	mes "解かれてしまうかもしれない。";
	next;
	mes "特に、彼らにとっては、";
	mes "そんなに難しい事では";
	mes "ないかもしれない。";
	mes "そこで、ゲートを封印する直前に、";
	mes "ゲートに繋がる座標を変更した。";
	next;
	mes "どこへ繋がったかは、";
	mes "正確には確認できなかった。";
	mes "しかし、そこから流れ出る空気は、";
	mes "魔界のものとは異なり、";
	mes "明るい感じがしたので、";
	mes "特に心配する必要はなさそうだ。";
	next;
	mes "‐画面に表示されている内容は以上だ‐";
	mes "‐これを見る限り、";
	mes "この前後の文章が存在すると思われる‐";
	next;
	if(select("もう少し調べてみる","調べるのをやめる")==2)
		close;
	mes "‐機械の装置を隅々まで調べてみると、";
	mes "端の方にしまわれていた";
	mes "鍵のような物を見つけた‐";
	mes "‐……単なる鍵ではなさそうだ‐";
	getitem 7421,1;
	close;
}

//黄のカギ
tha_t04.gat,195,195,0	script	機械の装置#tt2	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(countitem(7422) || countitem(7427)) {
		mes "‐機械の装置は、何の音もせずに";
		mes "停止している‐";
		close;
	}
	mes "‐機械の装置をよく見ると、";
	mes "ちょっとした大きさの";
	mes "画面の下に数字がある‐";
	mes "‐その数字に触れてみると、";
	mes "ピーーッ!!っという音と共に";
	mes "画面に文字が現われた‐";
	next;
	mes "[画面]";
	mes "三桁の数字を入力してください。";
	mes "「0」や重複する数字は";
	mes "使用できません。";
	mes "また、入力範囲を";
	mes "超えないようにしてください。";
	next;
	setarray '@list,1,2,3,4,5,6,7,8,9;
	for(set '@i,0; '@i < 3; set '@i,'@i+1) {
		set '@r,rand(getarraysize('@list));
		set '@ans['@i],'@list['@r];
		deletearray '@list['@r],1;
	}
	for(set '@cnt,0; '@cnt < 10; set '@cnt,'@cnt+1) {
		input '@temp;
		if('@temp < 100 || '@temp > 999) {
			mes "[画面]";
			mes "入力範囲超過!!";
			close;
		}
		setarray '@num,'@temp/100,'@temp%100/10,'@temp%100%10;
		if('@num[0] == 0 || '@num[1] == 0 || '@num[2] == 0 || '@num[0] == '@num[1] || '@num[1] == '@num[2] || '@num[0] == '@num[2]) {
			mes "[画面]";
			mes "入力値に「0」または重複数字あり!!";
			continue;
		}
		mes "[画面]";
		mes "入力数字：^0000ff" +'@num[0]+ "^000000,^0000ff" +'@num[1]+ "^000000,^0000ff" +'@num[2]+ "^000000";
		mes "……照合中……。";
		next;
		if('@num[0] == '@ans[0])
			set '@match,'@match+1;
		if('@num[0] == '@ans[1] || '@num[0] == '@ans[2])
			set '@shift,'@shift+1;
		if('@num[1] == '@ans[1])
			set '@match,'@match+1;
		if('@num[1] == '@ans[0] || '@num[1] == '@ans[2])
			set '@shift,'@shift+1;
		if('@num[2] == '@ans[2])
			set '@match,'@match+1;
		if('@num[2] == '@ans[0] || '@num[2] == '@ans[1])
			set '@shift,'@shift+1;
		if('@match == 3)
			break;
		mes "[画面]";
		mes "ピィーーッ!!";
		mes "間違っています!!";
		next;
		mes "[画面]";
		mes "桁内の数字が一致しているのは、^ff0000"+ '@match +"^000000個、";
		mes "数字だけ一致しているのは、^ff0000"+ '@shift +"^000000個です。";
		next;
		set '@match,0;
		set '@shift,0;
		continue;
	}
	if('@cnt == 10) {
		mes "[画面]";
		mes "承認番号：^ff0000" +'@ans[0]+ "^000000,^ff0000" +'@ans[1]+ "^000000,^ff0000" +'@ans[2]+ "^000000";
		mes "承認番号を変更します。";
		close;
	}
	mes "[画面]";
	mes "承認されました。";
	mes "接続を許可します。";
	next;
	mes "‐この文章が表示されて少しすると……";
	mes "また、新たな文章が表示された‐";
	mes "‐画面の下にあった数字が消え、";
	mes "そこに空洞ができた‐";
	next;
	switch(select("画面の文章を読む","空洞の中をのぞいてみる","特に何もしない")) {
	case 1:
		mes "つまり、彼女がこちらへ来たのには、";
		mes "ある目的があった。その目的とは、";
		mes "まさに、魔王モロクである。";
		next;
		mes "それから、こちらで大規模な";
		mes "争いの跡を見つけた。";
		mes "その跡は、巨大な一つの個体と";
		mes "人間の大きさの多くの個体の";
		mes "戦いによるものだと思われる。";
		next;
		mes "これらは、魔王モロクと";
		mes "彼女の仲間達と推定された。";
		mes "戦闘の結果、恐らく、魔王モロクは";
		mes "深刻な打撃を受け、ここから撤退し、";
		mes "南へ下ったようだった。";
		next;
		mes "そして、モロクと争った";
		mes "彼女の仲間達が、モロクを";
		mes "追いかけていった跡が残っていた。";
		next;
		mes "しかし、彼女の跡は、";
		mes "これに続いていなかった。";
		next;
		mes "数百年経た今もなお、";
		mes "他の跡は残っているにもかかわらず、";
		mes "彼女の跡だけ消えているという点に、";
		mes "疑問が残った……。";
		mes "だが、結局、";
		mes "これ以上のことは判らなかった。";
		next;
		mes "‐この後につながる文章はない‐";
		next;
		if(select("画面の下の空洞の中をのぞいてみる","特に何もしない")==2)
			close;
	case 2:
		break;
	case 3:
		close;
	}
	mes "‐中をのぞいてみると、";
	mes "その傍らに輝く物体があった‐";
	mes "‐その物体を取り出してみると、";
	mes "鍵のような形をしていた‐";
	mes "‐……単なる鍵ではなさそうだ‐";
	getitem 7422,1;
	close;
}

//青のカギ
tha_t05.gat,101,37,0	script	機械の装置#tt3	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(countitem(7423) || countitem(7428)) {
		mes "‐底の方に少し模様がある以外は、";
		mes "特に変わったところはない‐";
		close;
	}
	mes "‐機械の装置周辺に、";
	mes "妙な空気を感じた‐";
	mes "‐機械の装置をよく見てみたが、";
	mes "スイッチなどは一切見当たらない‐";
	next;
	mes "‐しかし、装置の真ん中に";
	mes "何も表示されていない";
	mes "緑色の画面がある‐";
	switch(getareausers("tha_t05.gat",101,37,106,42)) {
	case 0:
		mes "‐それ以外には、";
		mes "特に変わった点はない‐";
		close;
	case 1:
		mes "‐それ以外には、";
		mes "特に変わった点はない‐";
		next;
		mes "‐ふと、底を見てみると、";
		mes "ちょっとした模様があった‐";
		close;
	case 2:
		next;
		mes "‐その周辺をよく見てみると、";
		mes "装置の底の方から、";
		mes "立っている人に向かって";
		mes "微かな光が出ている‐";
		close;
	default:
		break;
	}
	mes "‐機械の装置に近付くと、";
	mes "装置の底のあたりから";
	mes "微かな光が出始めた‐";
	mes "‐すると、ピーーッという音と共に";
	mes "装置の前面にある画面に";
	mes "文字が表示された‐";
	next;
	mes "‐そして、その下に";
	mes "空洞が現われた‐";
	next;
	switch(select("画面を見る","空洞を調べる","何もしない")) {
	case 1:
		mes "その後、こちらを発とうと思ったが、";
		mes "ここで見つけたゲートの存在が";
		mes "気がかりであった。";
		mes "もし誰かが、塔とゲートを見つけ、";
		mes "それを悪用したら、";
		mes "大陸に甚大な被害をもたらすからだ。";
		next;
		mes "そこで私は、ゲートと塔を";
		mes "封印することにした。";
		next;
		mes "彼らに気づかれないように";
		mes "作業をしなければならなかったので、";
		mes "その進行速度はかなり遅かった。";
		mes "その為、ゲートの封印作業に";
		mes "かなりの年月を要した。";
		next;
		mes "封印作業を始める前に、";
		mes "まず、ゲートの調査をした。";
		mes "その過程で、強い力を持つ";
		mes "魔力石がいくつか発見された。";
		next;
		mes "調査の結果、";
		mes "これらはゲートを維持する";
		mes "力の源であることが判った。";
		mes "そこで、魔力石を別の場所に";
		mes "封印することにした。";
		next;
		mes "‐この後につながる文章はない‐";
		close;
	case 2:
		mes "‐空洞の内部をよく見てみると、";
		mes "その内側に輝く物体が見えた‐";
		mes "‐それを取り出してみると、";
		mes "鍵のような形をしていた‐";
		getitem 7423,1;
		close;
	case 3:
		close;
	}
}

//緑のカギ
tha_t06.gat,43,152,0	script	機械の装置#tt4	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(countitem(7424) || countitem(7429)) {
		mes "‐大きな歯車が停止している‐";
		close;
	}
	mes "‐大きな歯車が動いている";
	mes "機械の装置がある‐";
	mes "‐機械の一面には、";
	mes "何も表示されていない";
	mes "画面がある‐";
	next;
	if(select("もう少し調べる","気にしないことにする")==2) {
		mes "‐何かの装置のようだが、";
		mes "気にするようなことはなさそうだ‐";
		close;
	}
	if(countitem(7421) <= 0 && countitem(7422) <= 0 && countitem(7423) <= 0) {
		mes "‐歯車が微かな光を発しているが、";
		mes "単に動いているだけで、";
		mes "それ以外は何の変哲もない‐";
		close;
	}
	mes "‐歯車を調べてみると……";
	mes "持っていたカギと歯車が、";
	mes "微かな光とともに";
	mes "音を出し始めた‐";
	mes "‐しばらくすると、音が止んだ‐";
	next;
	switch(select("機械の本体を調べる","歯車を調べる","気にしないことにする")) {
	case 1:
		mes "‐機械の本体には、何も反応がない‐";
		mes "‐画面にも、何も反応がない‐";
		close;
	case 2:
		mes "‐歯車を調べるため、";
		mes "歯車に触れてみたところ、";
		mes "歯車を少し動かせることが判った‐";
		next;
		mes "‐歯車をもう少し調べてみた‐";
		next;
		mes "‐その結果、";
		mes "小さい歯車2個と大きい歯車3個の";
		mes "計5個の歯車を動かせることが判った‐";
		next;
		mes "‐小さい歯車は、上下へ動かすことや";
		mes "押すことができるようだ‐";
		mes "‐大きい歯車は、上下と垂直に";
		mes "動かすことができるようだ‐";
		next;
		while(1) {
			mes "‐歯車を動かしてみよう‐";
			switch(select("一番小さい歯車","二番目に小さい歯車","一番大きい歯車","二番目に大きい歯車","三番目に大きい歯車","現在の状態を見る","全て元通りにする")) {
			case 1:
				switch(select("上へ上げる","下へ下げる","押す")) {
				case 1:
					set '@wheels[0],2;
					if('@wheels[0] == 2 && '@wheels[1] == 2 && '@wheels[2] == 2 && '@wheels[3] == 2 && '@wheels[4] == 2)
						break;
					continue;
				case 2:
					set '@wheels[0],1;
					if('@wheels[0] == 1 && '@wheels[1] == 1 && '@wheels[2] == 1 && '@wheels[3] == 1 && '@wheels[4] == 1)
						break;
					continue;
				case 3:
					set '@wheels[0],3;
					if('@wheels[0] == 3 && '@wheels[1] == 3 && '@wheels[2] == 3 && '@wheels[3] == 3 && '@wheels[4] == 3)
						break;
					continue;
				}
				break;
			case 2:
				switch(select("上へ上げる","下へ下げる","押す")) {
				case 1:
					set '@wheels[1],3;
					if('@wheels[0] == 3 && '@wheels[1] == 3 && '@wheels[2] == 3 && '@wheels[3] == 3 && '@wheels[4] == 3)
						break;
					continue;
				case 2:
					set '@wheels[1],2;
					if('@wheels[0] == 2 && '@wheels[1] == 2 && '@wheels[2] == 2 && '@wheels[3] == 2 && '@wheels[4] == 2)
						break;
					continue;
				case 3:
					set '@wheels[1],1;
					if('@wheels[0] == 1 && '@wheels[1] == 1 && '@wheels[2] == 1 && '@wheels[3] == 1 && '@wheels[4] == 1)
						break;
					continue;
				}
				break;
			case 3:
				switch(select("上へ上げる","下へ下げる","垂直に動かす")) {
				case 1:
					set '@wheels[2],1;
					if('@wheels[0] == 1 && '@wheels[1] == 1 && '@wheels[2] == 1 && '@wheels[3] == 1 && '@wheels[4] == 1)
						break;
					continue;
				case 2:
					set '@wheels[2],3;
					if('@wheels[0] == 3 && '@wheels[1] == 3 && '@wheels[2] == 3 && '@wheels[3] == 3 && '@wheels[4] == 3)
						break;
					continue;
				case 3:
					set '@wheels[2],2;
					if('@wheels[0] == 2 && '@wheels[1] == 2 && '@wheels[2] == 2 && '@wheels[3] == 2 && '@wheels[4] == 2)
						break;
					continue;
				}
				break;
			case 4:
				switch(select("上へ上げる","下へ下げる","垂直に動かす")) {
				case 1:
					set '@wheels[3],2;
					if('@wheels[0] == 2 && '@wheels[1] == 2 && '@wheels[2] == 2 && '@wheels[3] == 2 && '@wheels[4] == 2)
						break;
					continue;
				case 2:
					set '@wheels[3],3;
					if('@wheels[0] == 3 && '@wheels[1] == 3 && '@wheels[2] == 3 && '@wheels[3] == 3 && '@wheels[4] == 3)
						break;
					continue;
				case 3:
					set '@wheels[3],1;
					if('@wheels[0] == 1 && '@wheels[1] == 1 && '@wheels[2] == 1 && '@wheels[3] == 1 && '@wheels[4] == 1)
						break;
					continue;
				}
				break;
			case 5:
				switch(select("上へ上げる","下へ下げる","垂直に動かす")) {
				case 1:
					set '@wheels[4],2;
					if('@wheels[0] == 2 && '@wheels[1] == 2 && '@wheels[2] == 2 && '@wheels[3] == 2 && '@wheels[4] == 2)
						break;
					continue;
				case 2:
					set '@wheels[4],1;
					if('@wheels[0] == 1 && '@wheels[1] == 1 && '@wheels[2] == 1 && '@wheels[3] == 1 && '@wheels[4] == 1)
						break;
					continue;
				case 3:
					set '@wheels[4],3;
					if('@wheels[0] == 3 && '@wheels[1] == 3 && '@wheels[2] == 3 && '@wheels[3] == 3 && '@wheels[4] == 3)
						break;
					continue;
				}
				break;
			case 6:
				if('@wheels[0] == 0)      mes "一番小さい歯車：そのまま";
				else if('@wheels[0] == 1) mes "一番小さい歯車：下へ";
				else if('@wheels[0] == 2) mes "一番小さい歯車：上へ";
				else if('@wheels[0] == 3) mes "一番小さい歯車：押す";

				if('@wheels[1] == 0)      mes "二番目に小さい歯車：そのまま";
				else if('@wheels[1] == 1) mes "二番目に小さい歯車：押す";
				else if('@wheels[1] == 2) mes "二番目に小さい歯車：下へ";
				else if('@wheels[1] == 3) mes "二番目に小さい歯車：上へ";

				if('@wheels[2] == 0)      mes "一番大きい歯車：そのまま";
				else if('@wheels[2] == 1) mes "一番大きい歯車：上へ";
				else if('@wheels[2] == 2) mes "一番大きい歯車：垂直に";
				else if('@wheels[2] == 3) mes "一番大きい歯車：下へ";

				if('@wheels[3] == 0)      mes "二番目に大きい歯車：そのまま";
				else if('@wheels[3] == 1) mes "二番目に大きい歯車：垂直に";
				else if('@wheels[3] == 2) mes "二番目に大きい歯車：上へ";
				else if('@wheels[3] == 3) mes "二番目に大きい歯車：下へ";

				if('@wheels[4] == 0)      mes "三番目に大きい歯車：そのまま";
				else if('@wheels[4] == 1) mes "三番目に大きい歯車：下へ";
				else if('@wheels[4] == 2) mes "三番目に大きい歯車：上へ";
				else if('@wheels[4] == 3) mes "三番目に大きい歯車：垂直に";
				continue;
			case 7:
				cleararray '@wheels,0,5;
				continue;
			}
			break;
		};
		break;
	case 3:
		mes "‐…………‐";
		mes "‐気にしない方がよさそうだ‐";
		close;
	}
	mes "‐動いていた歯車が、ギィィ～ッ!!";
	mes "という音と共に止まった‐";
	mes "‐そして、機械の本体にある";
	mes "画面に文字が現われ、";
	mes "その下に空洞が現われた‐";
	next;
	switch(select("画面をよく見る","下の空洞をよく見る","特に気にしない")) {
	case 1:
		mes "この塔を建てた存在は、";
		mes "人間や神々ではなく……";
		mes "魔族であった。";
		next;
		mes "この点に興味を抱いた私は、";
		mes "魔族がどのような目的で、";
		mes "この塔を建てたのかを";
		mes "明らかにするため、研究を始めた。";
		next;
		mes "そうして研究を続ける中、";
		mes "二つの興味深い事実を発見した。";
		next;
		mes "一つは、この塔が千年前の戦争時、";
		mes "魔族を呼び出すゲートの役割を";
		mes "していたということ。";
		next;
		mes "二つめは、私達がよく知る";
		mes "魔王モロクが、このゲートを通り、";
		mes "魔界からこのミッドガルド大陸へ";
		mes "やって来たということ。";
		next;
		mes "そして、魔王モロクにも";
		mes "興味を抱くようになった。";
		mes "その理由は、魔王モロクが";
		mes "出現した時期と彼女がこちらへ";
		mes "やって来た時期は、";
		mes "ほぼ一致していたからだ。";
		next;
		mes "‐この後につながる文章はない‐";
		close;
	case 2:
		mes "‐空洞の内部をよく見てみると、";
		mes "その内側に輝く物体が見えた‐";
		mes "‐それを取り出してみると、";
		mes "鍵のような形をしていた‐";
		getitem 7424,1;
		close;
	case 3:
		mes "‐特に気にする必要はなさそうだ‐";
		close;
	}
}

//黒のカギ
tha_t09.gat,19,158,0	script	機械の装置#tt5	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(countitem(7425) || countitem(7430)) {
		mes "‐稼動していない機械がある‐";
		close;
	}
	mes "‐微かな音と光を発する機械がある‐";
	mes "‐機械の前面にはちょっとした";
	mes "大きさの画面があり、";
	mes "その下には、何かを置くことが";
	mes "できそうな空間がある‐";
	next;
	mes "‐しかも、それぞれの場所の色は、";
	mes "異なっている‐";
	if(!((countitem(7421)) || (countitem(7426))) && ((countitem(7422)) || (countitem(7427))) && ((countitem(7423)) || (countitem(7428))) && ((countitem(7424)) || (countitem(7429)))) close;
	next;
	input '@word$;
	if('@word$ != "赤のカギ" && '@word$ != "黄のカギ" && '@word$ != "青のカギ" && '@word$ != "緑のカギ") {
		mes "‐"+'@word$+"を";
		mes "使ってみたが、何も反応はなかった‐";
		close;
	}
	mes "‐各色に該当するカギと魔力石を";
	mes "置くと、それぞれの場所で";
	mes "光を発し始めた‐";
	mes "‐画面に文字が表示され、";
	mes "その下に空洞が現われた‐";
	next;
	switch(select("文章を読む","下の空洞を調べる","気にしない")) {
	case 1:
		mes "彼女の跡は北の方に続いていたので、";
		mes "その跡を追って北の方へ向かった。";
		mes "だが、次第にその跡を追うことが";
		mes "困難になってきた。";
		next;
		mes "そんな中、立ち寄った村で、";
		mes "人を寄せ付けない塔の話を聞いた。";
		next;
		mes "その塔の話を聞いた瞬間、";
		mes "彼女の跡はこの塔に向かっていたことを";
		mes "直感的に悟った。";
		next;
		mes "塔に到着した私は、その塔の";
		mes "奇怪な姿に大きな衝撃を受けた。";
		mes "人間が創造した建築様式中、";
		mes "このような形態の建物は";
		mes "存在しなかったからだ。";
		next;
		mes "それに、現代の技術をもってしても、";
		mes "このような塔を建設することは";
		mes "至難の業であるからだ。";
		mes "そして、ここを調査するうちに";
		mes "興味深い事実を発見した。";
		next;
		mes "‐この後につながる文章はない‐";
		close;
	case 2:
		mes "‐下の空洞を調べると、";
		mes "鍵のような物を見つけた‐";
		mes "‐それを回収すると、";
		mes "機械から発していた光が消えた‐";
		mes "‐置いた魔力石とカギを全て回収した‐";
		getitem 7425,1;
		close;
	case 3:
		mes "‐置いた魔力石とカギを全て回収した‐";
		close;
	}
}

//赤魔力石
tha_t05.gat,218,116,0	script	封印#tt2	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(!countitem(7421)) {
		mes "‐手を封印に近付けようとしたら、";
		mes "バシンッ!!という音と共に、";
		mes "手が弾かれ、脂汗がにじんだ‐";
		percentheal -10,0;
		close;
	}
	mes "‐神秘的な力に覆われている‐";
	mes "‐手を封印に近付けようとしたら、";
	mes "バシンッ!!という音と共に弾かれた‐";
	next;
	if(select("もう少し調べてみる","特にすることはなさそうだ")==2) {
		mes "‐その場から離れた‐";
		close;
	}
	input '@word$;
	if('@word$ != "赤のカギ") {
		mes "‐結局、何も分からなかった‐";
		close;
	}
	mes "‐持っていた赤のカギを突きさすと、";
	mes "ジィィーッ!!という音と共に";
	mes "覆っていた力が消えた‐";
	next;
	mes "‐機械をよく見ると、";
	mes "鍵を差し込めそうな小さな穴がある‐";
	mes "‐鍵を差し込むと、";
	mes "封印が神秘的な光を発し始めた‐";
	next;
	mes "‐そして、その光は徐々に消えたが、";
	mes "代わりに、神秘的な光を放つ";
	mes "物体が置かれていた‐";
	next;
	mes "‐そこにあった魔力石をつかんだ瞬間、";
	mes "頭の中に誰かの記憶が入ってきた‐";
	next;
	mes "……そこで、";
	mes "アサシンクロス達を送りこみ、";
	mes "魔王を退けるつもりだ。";
	next;
	mes "勝算は？";
	mes "　";
	mes "……1割……。";
	mes "　";
	mes "……全くないわけではないか。";
	mes "　";
	mes "まあ、相手が魔王だからね。";
	next;
	mes "‐…………‐";
	mes "‐一瞬、映像が現われて、消えた‐";
	delitem 7421,1;
	getitem 7426,1;
	close;
}

//黄魔力石
tha_t07.gat,113,129,0	script	封印#tt4	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(!countitem(7422)) {
		mes "‐手を封印に近付けようとしたら、";
		mes "バシンッ!!という音と共に、";
		mes "手が弾かれ、脂汗がにじんだ‐";
		percentheal -10,0;
		close;
	}
	mes "‐神秘的な力に覆われている‐";
	mes "‐手を封印に近付けようとしたら、";
	mes "バシンッ!!という音と共に弾かれた‐";
	next;
	if(select("もう少し調べてみる","特にすることはなさそうだ")==2) {
		mes "‐その場から離れた‐";
		close;
	}
	input '@word$;
	if('@word$ != "黄のカギ") {
		mes "‐結局、何も分からなかった‐";
		close;
	}
	mes "‐持っていた黄のカギを突きさすと、";
	mes "ジィィーッ!!という音と共に";
	mes "覆っていた力が消えた‐";
	next;
	mes "‐機械をよく見ると、";
	mes "鍵を差し込めそうな小さな穴がある‐";
	mes "‐鍵を差し込むと、";
	mes "封印が神秘的な光を発し始めた‐";
	next;
	mes "‐そして、その光は徐々に消えたが、";
	mes "代わりに、神秘的な光を放つ";
	mes "物体が置かれていた‐";
	next;
	mes "‐そこにあった魔力石をつかんだ瞬間、";
	mes "頭の中に誰かの記憶が入ってきた‐";
	next;
	mes "ルシルです。";
	mes "少し遠い所の任務でしたので、";
	mes "遅れました。";
	mes "タナトスだ…………";
	mes "…………";
	next;
	mes "（彼女を見ていると、";
	mes "何か変な感じがする。";
	mes "まるで……私の一部のような……）";
	next;
	mes "‐…………‐";
	mes "‐一瞬、映像が現われて、消えた‐";
	delitem 7422,1;
	getitem 7427,1;
	close;
}

//青魔力石
tha_t04.gat,150,44,0	script	封印#tt1	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(!countitem(7423)) {
		mes "‐手を封印に近付けようとしたら、";
		mes "バシンッ!!という音と共に、";
		mes "手が弾かれ、脂汗がにじんだ‐";
		percentheal -10,0;
		close;
	}
	mes "‐神秘的な力に覆われている‐";
	mes "‐手を封印に近付けようとしたら、";
	mes "バシンッ!!という音と共に弾かれた‐";
	next;
	if(select("もう少し調べてみる","特にすることはなさそうだ")==2) {
		mes "‐その場から離れた‐";
		close;
	}
	input '@word$;
	if('@word$ != "青のカギ") {
		mes "‐結局、何も分からなかった‐";
		close;
	}
	mes "‐持っていた青のカギを突きさすと、";
	mes "ジィィーッ!!という音と共に";
	mes "覆っていた力が消えた‐";
	next;
	mes "‐機械をよく見ると、";
	mes "鍵を差し込めそうな小さな穴がある‐";
	mes "‐鍵を差し込むと、";
	mes "封印が神秘的な光を発し始めた‐";
	next;
	mes "‐そして、その光は徐々に消えたが、";
	mes "代わりに、神秘的な光を放つ";
	mes "物体が置かれていた‐";
	next;
	mes "‐そこにあった魔力石をつかんだ瞬間、";
	mes "頭の中に誰かの記憶が入ってきた‐";
	next;
	mes "タナトス!!";
	mes "ギルドから連絡が来ました！";
	mes "直ちに任務を全て中止し、即座に";
	mes "ギルドへ戻るようにとのことです！";
	mes "　";
	mes "……分かった。";
	next;
	mes "‐…………‐";
	mes "‐一瞬、映像が現われて、消えた‐";
	delitem 7423,1;
	getitem 7428,1;
	close;
}

//緑魔力石
tha_t10.gat,129,159,0	script	封印#tt5	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(!countitem(7424)) {
		mes "‐手を封印に近付けようとしたら、";
		mes "バシンッ!!という音と共に、";
		mes "手が弾かれ、脂汗がにじんだ‐";
		percentheal -10,0;
		close;
	}
	mes "‐神秘的な力に覆われている‐";
	mes "‐手を封印に近付けようとしたら、";
	mes "バシンッ!!という音と共に弾かれた‐";
	next;
	if(select("もう少し調べてみる","特にすることはなさそうだ")==2) {
		mes "‐その場から離れた‐";
		close;
	}
	input '@word$;
	if('@word$ != "緑のカギ") {
		mes "‐結局、何も分からなかった‐";
		close;
	}
	mes "‐持っていた緑のカギを突きさすと、";
	mes "ジィィーッ!!という音と共に";
	mes "覆っていた力が消えた‐";
	next;
	mes "‐機械をよく見ると、";
	mes "鍵を差し込めそうな小さな穴がある‐";
	mes "‐鍵を差し込むと、";
	mes "封印が神秘的な光を発し始めた‐";
	next;
	mes "‐そして、その光は徐々に消えたが、";
	mes "代わりに、神秘的な光を放つ";
	mes "物体が置かれていた‐";
	next;
	mes "‐そこにあった魔力石をつかんだ瞬間、";
	mes "頭の中に誰かの記憶が入ってきた‐";
	next;
	mes "……とうとう魔王だけが残ったな……。";
	mes "さあ、これで終わりだ……。";
	mes "…………グッ!!";
	mes "やはり、魔王だけなことはあるな……。";
	mes "グハッ……。";
	next;
	mes "こ、これは…………";
	mes "……………………";
	mes "………………";
	mes "……グアァァァァッ!!!!";
	mes "な、我が……この身が……";
	mes "人間どもなんかに……!!!!";
	next;
	mes "‐…………‐";
	mes "‐一瞬、映像が現われて、消えた‐";
	delitem 7424,1;
	getitem 7429,1;
	close;
}

//黒魔力石
tha_t06.gat,226,230,0	script	封印#tt3	111,{
	if(checkitemblank() == 0) {
		mes "‐所持アイテムの種類数が多いため";
		mes "アイテムを受けとることができません‐";
		mes "‐所持アイテムを減らしてから、再度";
		mes "話しかけてください‐";
		close;
	}
	if(!countitem(7425)) {
		mes "‐手を封印に近付けようとしたら、";
		mes "バシンッ!!という音と共に、";
		mes "手が弾かれ、脂汗がにじんだ‐";
		percentheal -10,0;
		close;
	}
	mes "‐神秘的な力に覆われている‐";
	mes "‐手を封印に近付けようとしたら、";
	mes "バシンッ!!という音と共に弾かれた‐";
	next;
	if(select("もう少し調べてみる","特にすることはなさそうだ")==2) {
		mes "‐その場から離れた‐";
		close;
	}
	input '@word$;
	if('@word$ != "黒のカギ") {
		mes "‐結局、何も分からなかった‐";
		close;
	}
	mes "‐持っていた黒のカギを突きさすと、";
	mes "ジィィーッ!!という音と共に";
	mes "覆っていた力が消えた‐";
	next;
	mes "‐機械をよく見ると、";
	mes "鍵を差し込めそうな小さな穴がある‐";
	mes "‐鍵を差し込むと、";
	mes "封印が神秘的な光を発し始めた‐";
	next;
	mes "‐そして、その光は徐々に消えたが、";
	mes "代わりに、神秘的な光を放つ";
	mes "物体が置かれていた‐";
	next;
	mes "‐そこにあった魔力石をつかんだ瞬間、";
	mes "頭の中に誰かの記憶が入ってきた‐";
	next;
	mes "ああ……あれが……";
	mes "魔王モロクが、";
	mes "手下を集めているという塔か……。";
	mes "ヒュ～……冗談じゃない。";
	mes "一体どれくらい集まっているんだろう。";
	mes "……二、三千はいるようだな。";
	next;
	mes "‐…………‐";
	mes "‐一瞬、映像が現われて、消えた‐";
	delitem 7425,1;
	getitem 7430,1;
	close;
}

//赤の石像
tha_t12.gat,96,58,0	script	石像#tt1	111,{
	if($@THA_1SEAL == 12) {
		mes "‐石像が、直視できない程、";
		mes "強烈な光を放っている上、";
		mes "手を触れることができない程、";
		mes "熱を帯びている‐";
		close;
	}
	if($@THA_1SEAL != 0) {
		mes "‐石像が神秘的な光を発している‐";
		mes "‐……不思議な力のせいで";
		mes "近づくことができない‐";
		close;
	}
	mes "‐平凡な石像がある‐";
	mes "‐そこには、何かを入れることが";
	mes "できそうな穴がある‐";
	if(countitem(7426) < 1)
		close;
	next;
	mes "‐石像に近付くと、";
	mes "持っていた魔力石が";
	mes "光を発し始めた‐";
	mes "‐そして、石像から";
	mes "赤い光がさしてきた‐";
	next;
	if(select("穴に魔力石を入れる","そのままにしておく")==2) {
		mes "‐もう少し様子を見ることにした‐";
		close;
	}
	mes "‐石像の穴に魔力石を入れると、";
	mes "石像が神秘的な光に包まれた‐";
	delitem 7426,1;
	misceffect 55;
	donpcevent "tteffect2::OnGlow";
	set $@THA_1SEAL,1;
	close;
}

//黄の石像
tha_t12.gat,161,58,0	script	石像#tt4	111,{
	if($@THA_1SEAL == 12) {
		mes "‐石像が、直視できない程、";
		mes "強烈な光を放っている上、";
		mes "手を触れることができない程、";
		mes "熱を帯びている‐";
		close;
	}
	if($@THA_1SEAL != 1) {
		mes "‐石像が神秘的な光を発している‐";
		mes "‐……不思議な力のせいで";
		mes "近づくことができない‐";
		close;
	}
	mes "‐平凡な石像がある‐";
	mes "‐そこには、何かを入れることが";
	mes "できそうな穴がある‐";
	if(countitem(7427) < 1)
		close;
	next;
	mes "‐石像に近付くと、";
	mes "持っていた黄魔力石が";
	mes "光を発し始めた‐";
	next;
	if(select("穴に魔力石を入れる","そのままにしておく")==2) {
		mes "‐もう少し様子を見ることにした‐";
		close;
	}
	mes "‐石像の穴に魔力石を入れると、";
	mes "石像が神秘的な光に包まれた‐";
	delitem 7427,1;
	misceffect 57;
	donpcevent "tteffect3::OnGlow";
	set $@THA_1SEAL,2;
	close;
}

//青の石像
tha_t12.gat,104,18,0	script	石像#tt2	111,{
	if($@THA_1SEAL == 12) {
		mes "‐石像が、直視できない程、";
		mes "強烈な光を放っている上、";
		mes "手を触れることができない程、";
		mes "熱を帯びている‐";
		close;
	}
	if($@THA_1SEAL != 2) {
		mes "‐石像が神秘的な光を発している‐";
		mes "‐……不思議な力のせいで";
		mes "近づくことができない‐";
		close;
	}
	mes "‐平凡な石像がある‐";
	mes "‐そこには、何かを入れることが";
	mes "できそうな穴がある‐";
	if(countitem(7428) < 1)
		close;
	next;
	mes "‐石像に近付くと、";
	mes "持っていた青魔力石が";
	mes "光を発し始めた‐";
	next;
	if(select("穴に魔力石を入れる","そのままにしておく")==2) {
		mes "‐もう少し様子を見ることにした‐";
		close;
	}
	mes "‐石像の穴に魔力石を入れると、";
	mes "石像が神秘的な光に包まれた‐";
	delitem 7428,1;
	misceffect 54;
	donpcevent "tteffect5::OnGlow";
	set $@THA_1SEAL,3;
	close;
}

//黒の石像
tha_t12.gat,128,86,0	script	石像#tt3	111,{
	if($@THA_1SEAL == 12) {
		mes "‐石像が、直視できない程、";
		mes "強烈な光を放っている上、";
		mes "手を触れることができない程、";
		mes "熱を帯びている‐";
		close;
	}
	if($@THA_1SEAL != 3) {
		mes "‐石像が神秘的な光を発している‐";
		mes "‐……不思議な力のせいで";
		mes "近づくことができない‐";
		close;
	}
	mes "‐平凡な石像がある‐";
	mes "‐そこには、何かを入れることが";
	mes "できそうな穴がある‐";
	if(countitem(7430) < 1)
		close;
	next;
	mes "‐石像に近付くと、";
	mes "持っていた黒魔力石が";
	mes "光を発し始めた‐";
	next;
	if(select("穴に魔力石を入れる","そのままにしておく")==2) {
		mes "‐もう少し様子を見ることにした‐";
		close;
	}
	mes "‐石像の穴に魔力石を入れると、";
	mes "石像が神秘的な光に包まれた‐";
	delitem 7430,1;
	misceffect 59;
	donpcevent "tteffect1::OnGlow";
	set $@THA_1SEAL,4;
	close;
}

//緑の石像
tha_t12.gat,154,18,0	script	石像#tt5	111,{
	if($@THA_1SEAL == 12) {
		mes "‐石像が、直視できない程、";
		mes "強烈な光を放っている上、";
		mes "手を触れることができない程、";
		mes "熱を帯びている‐";
		close;
	}
	if($@THA_1SEAL != 4) {
		mes "‐石像が神秘的な光を発している‐";
		mes "‐……不思議な力のせいで";
		mes "近づくことができない‐";
		close;
	}
	mes "‐平凡な石像がある‐";
	mes "‐そこには、何かを入れることが";
	mes "できそうな穴がある‐";
	if(countitem(7429) < 1)
		close;
	next;
	mes "‐石像に近付くと、";
	mes "持っていた緑魔力石が";
	mes "光を発し始めた‐";
	next;
	if(select("穴に魔力石を入れる","そのままにしておく")==2) {
		mes "‐もう少し様子を見ることにした‐";
		close;
	}
	mes "‐石像の穴に魔力石を入れると、";
	mes "石像が神秘的な光に包まれた‐";
	misceffect 56;
	next;
	mes "‐五つの石像全てが光に包まれ、";
	mes "石像たちの中心にある模様が";
	mes "奇妙な風と共に強い気を発し始めた‐";
	delitem 7429,1;
	donpcevent "tteffect4::OnGlow";
	donpcevent "WarpThana::OnStart";
	set $@THA_1SEAL,5;
	close;
}

tha_t12.gat,129,56,0	script	tteffect1	139,{
	end;
OnGlow:
	initnpctimer;
	end;
OnTimer500:
OnTimer1000:
OnTimer1500:
OnTimer2000:
OnTimer2500:
	misceffect 59;
	end;
OnTimer3000:
	misceffect 59;
	stopnpctimer;
	if($@THA_1SEAL >= 6)	end;
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
}

tha_t12.gat,125,52,0	script	tteffect2	139,{
	end;
OnGlow:
	initnpctimer;
	end;
OnTimer500:
OnTimer1000:
OnTimer1500:
OnTimer2000:
OnTimer2500:
	misceffect 55;
	end;
OnTimer3000:
	misceffect 55;
	stopnpctimer;
	if($@THA_1SEAL >= 6)	end;
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
}

tha_t12.gat,134,52,0	script	tteffect3	139,{
	end;
OnGlow:
	initnpctimer;
	end;
OnTimer500:
OnTimer1000:
OnTimer1500:
OnTimer2000:
OnTimer2500:
	misceffect 57;
	end;
OnTimer3000:
	misceffect 57;
	stopnpctimer;
	if($@THA_1SEAL >= 6)	end;
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
}

tha_t12.gat,132,47,0	script	tteffect4	139,{
	end;
OnGlow:
	initnpctimer;
	end;
OnTimer500:
OnTimer1000:
OnTimer1500:
OnTimer2000:
OnTimer2500:
	misceffect 56;
	end;
OnTimer3000:
	misceffect 56;
	stopnpctimer;
	if($@THA_1SEAL >= 6)	end;
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
}

tha_t12.gat,127,47,0	script	tteffect5	139,{
	end;
OnGlow:
	initnpctimer;
	end;
OnTimer500:
OnTimer1000:
OnTimer1500:
OnTimer2000:
OnTimer2500:
	misceffect 54;
	end;
OnTimer3000:
	misceffect 54;
	stopnpctimer;
	if($@THA_1SEAL >= 6)	end;
	initnpctimer;
	end;
OnStop:
	stopnpctimer;
	end;
}

tha_t12.gat,130,52,0	script	WarpThana	45,1,1,{
	end;
OnInit:
	disablenpc "WarpThana";
	end;
OnTouch:
	warp "thana_boss.gat",136,116;
	end;
OnStart:
	initnpctimer;
	enablenpc "WarpThana";
	end;
OnTimer10000:
	if($@THA_1SEAL >= 5 && $@THA_1SEAL <= 11) {
		initnpctimer;
	}
	else {
		stopnpctimer;
		donpcevent "tteffect1::OnStop";
		donpcevent "tteffect2::OnStop";
		donpcevent "tteffect3::OnStop";
		donpcevent "tteffect4::OnStop";
		donpcevent "tteffect5::OnStop";
		disablenpc "WarpThana";
		end;
	}
}

//苦悩の封印
thana_boss.gat,202,75,0	script	模様#tt2	111,3,3,{
	end;
OnTouch:
	if($@THA_2SEAL&0x1)
		end;
	mes "‐緑色の模様が乱雑に描かれている‐";
	mes "‐その中には、何かを入れることが";
	mes "できそうな穴がある‐";
	if(countitem(7436) < 1)
		close;
	next;
	input '@word$;
	if('@word$ != "苦悩の欠片") {
		mes "‐そんな物は持っていない‐";
		close;
	}
	if($@THA_2SEAL&0x1) {
		mes "‐何も起こらない‐";
		close;
	}
	mes "‐苦悩の欠片を";
	mes "その模様にはめた‐";
	mes "‐すると、模様が";
	mes "明るい光を発し始めた‐";
	set $@THA_2SEAL,$@THA_2SEAL|0x01;
	delitem 7436,1;
	monster "thana_boss.gat",202,75,"苦悩",1712,1,"#ttDeath::OnKilled1";
	close;
}

//悲しみの封印
thana_boss.gat,217,167,0	script	模様#tt1	111,3,3,{
	end;
OnTouch:
	if($@THA_2SEAL&0x2)
		end;
	mes "‐紫色の模様が乱雑に描かれている‐";
	mes "‐その中には、何かを入れることが";
	mes "できそうな穴がある‐";
	if(countitem(7437) < 1)
		close;
	next;
	input '@word$;
	if('@word$ != "悲しみの欠片") {
		mes "‐そんな物は持っていない‐";
		close;
	}
	if($@THA_2SEAL&0x2) {
		mes "‐何も起こらない‐";
		close;
	}
	mes "‐悲しみの欠片を";
	mes "その模様にはめた‐";
	mes "‐すると、模様が";
	mes "明るい光を発し始めた‐";
	set $@THA_2SEAL,$@THA_2SEAL|0x02;
	delitem 7437,1;
	monster "thana_boss.gat",217,167,"悲しみ",1711,1,"#ttDeath::OnKilled1";
	close;
}

//絶望の封印
thana_boss.gat,62,171,0	script	模様#tt4	111,3,3,{
	end;
OnTouch:
	if($@THA_2SEAL&0x4)
		end;
	mes "‐赤色の模様が乱雑に描かれている‐";
	mes "‐その中には、何かを入れることが";
	mes "できそうな穴がある‐";
	if(countitem(7439) < 1)
		close;
	next;
	input '@word$;
	if('@word$ != "絶望の欠片") {
		mes "‐そんな物は持っていない‐";
		close;
	}
	if($@THA_2SEAL&0x4) {
		mes "‐何も起こらない‐";
		close;
	}
	mes "‐絶望の欠片を";
	mes "その模様にはめた‐";
	mes "‐すると、模様が";
	mes "明るい光を発し始めた‐";
	set $@THA_2SEAL,$@THA_2SEAL|0x04;
	delitem 7439,1;
	monster "thana_boss.gat",62,171,"絶望",1710,1,"#ttDeath::OnKilled1";
	close;
}

//憎悪の封印
thana_boss.gat,80,76,0	script	模様#tt3	111,3,3,{
	end;
OnTouch:
	if($@THA_2SEAL&0x8)
		end;
	mes "‐青色の模様が乱雑に描かれている‐";
	mes "‐その中には、何かを入れることが";
	mes "できそうな穴がある‐";
	if(countitem(7438) < 1)
		close;
	next;
	input '@word$;
	if('@word$ != "憎悪の欠片") {
		mes "‐そんな物は持っていない‐";
		close;
	}
	if($@THA_2SEAL&0x8) {
		mes "‐何も起こらない‐";
		close;
	}
	mes "‐憎悪の欠片を";
	mes "その模様にはめた‐";
	mes "‐すると、模様が";
	mes "明るい光を発し始めた‐";
	set $@THA_2SEAL,$@THA_2SEAL|0x08;
	delitem 7438,1;
	monster "thana_boss.gat",80,76,"憎悪",1709,1,"#ttDeath::OnKilled1";
	close;
}

//タナトスの封印
thana_boss.gat,141,218,0	script	模様#tt5	111,3,3,{
	end;
OnTouch:
	if($@THA_1SEAL > 9)
		end;
	mes "‐黒色の模様が乱雑に描かれている‐";
	mes "‐模様から強い力を感じる‐";
	if($@THA_1SEAL < 9)
		close;
	mes "‐近くに行って、";
	mes "模様を観察してみると……";
	mes "神秘的な光が模様を包み始めた‐";
	mes "‐そして、模様が強烈な光を放った‐";
	set $@THA_1SEAL,10;
	monster "thana_boss.gat",139,215,"憎悪",1709,1,"#ttDeath::OnKilled2";
	monster "thana_boss.gat",139,220,"絶望",1710,1,"#ttDeath::OnKilled2";
	monster "thana_boss.gat",144,220,"悲しみ",1711,1,"#ttDeath::OnKilled2";
	monster "thana_boss.gat",144,215,"苦悩",1712,1,"#ttDeath::OnKilled2";
	close;
}

thana_boss.gat,1,1,0	script	#ttDeath	-1,{
	end;
OnKilled1:
	set $@THA_1SEAL,$@THA_1SEAL+1;
	end;
OnKilled2:
	set '@mob,getmapmobs("thana_boss.gat","#ttDeath::OnKilled2");
	if('@mob < 1) {
		set $@THA_1SEAL,11;
		monster "thana_boss.gat",135,129,"魔剣士タナトスの思念体",1708,1,"#ttDeath::OnThanaKilled";
	}
	end;
OnThanaKilled:
	initnpctimer;
	set $@THA_1SEAL,12;
	announce "グワァァァァァーーーッ!!!!",0x9,0xff0000;
	end;
OnTimer2000:
	announce "グウゥゥーーーーッ!!",0x9,0xff0000;
	end;
OnTimer4000:
	announce "グハッ……グハッ…………",0x9,0xff0000;
	end;
OnTimer6000:
	announce "ウウゥゥーッ……ハァハァッ……",0x9,0xff0000;
	end;
OnTimer8000:
	announce "バシッ……バシッ……。",0x9,0xff0000;
	end;
OnTimer60000:
	areawarp "thana_boss.gat",0,0,280,280,"tha_t12.gat",130,48;
	set $@THA_2SEAL,0;
	end;
OnTimer1800000:
	areawarp "thana_boss.gat",0,0,280,280,"tha_t12.gat",130,48;
	killmonsterall "thana_boss.gat";
	set $@THA_1SEAL,0;
	stopnpctimer;
	end;
}
