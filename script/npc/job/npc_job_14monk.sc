//===============================================================================================
//Ragnarok Online Monk jobchange script
//
//　■ CHANGE_MO -> 0～20
//     @monk_test -> 0～10、マラソン周回数
//===============================================================================================

//==========================================
// 転職案内
//------------------------------------------

prt_monk.gat,59,247,4	script	修行僧	120,6,2,{
	if(Job == Job_Monk) {
		mes "[都護府員]";
		mes "聖カピートリナ修道院にいらした";
		mes "ことを歓迎します。";
		mes "なにとぞ修行中のモンクの邪魔は";
		mes "なさらないでください。";
		mes "たとえあなたがモンクだとしても……";
		close;
	}
	switch(CHANGE_MO) {
	case 0:
		mes "[都護府員]";
		mes "ん……私に何の用ですか？";
		mes "神聖な修練場に入りたくば";
		mes "私に名前とJobLvを提示してから";
		mes "入っていただきます。";
		next;
		if(Upper == UPPER_HIGH) {
			mes "[都護府員]";
			mes "あ……";
			mes "申し訳ございません！";
			mes "見間違えました……";
			next;
			mes "[都護府員]";
			mes "……";
			mes "…………";
			next;
			mes "[都護府員]";
			mes "私が間違えるのもめずらしい……";
			mes "……良い一日を過ごしてください。";
			close;
		}
		mes "[都護府員]";
		mes "さあ、名前とJobLvを。";
		next;
		if(select("無視する","教える")==1) {
			mes "[都護府員]";
			mes "無礼者！出て行きなさい！";
			close2;
			warp "prt_fild03.gat",357,256;
			end;
		}
		mes "[都護府員]";
		mes "うん……" +strcharinfo(0);
		mes "ですね……。";
		mes "JobLvは" +JobLevel+ "ですか。";
		next;
		mes "[都護府員]";
		mes "さて、何の用で訪ねてきましたか？";
		mes strcharinfo(0)+ "よ……";
		setarray '@word$,"モンク達の修行姿を見ようと","モンクになろうと","修練場で休みに";
		break;
	case 1:
		if(Job == Job_Acolyte && JobLevel >= 40) {
			mes "[都護府員]";
			mes "どうですか？";
			mes "何か考えが変わりましたか？";
			setarray '@word$,"いいえ","モンクになりたいです！","もう少し休みます";
			break;
		}
		mes "[都護府員]";
		mes "ゆっくり見ていきなさい。";
		mes "何か得るものがあるかもしれません。";
		close;
	case 2:
		mes "[都護府員]";
		mes "無涯長老にお会いなさい。";
		mes "長老はここから南東の方角、";
		mes "修道院内部にいらっしゃるはずです。";
		close;
	default:
		mes "[都護府員]";
		mes "うん……厳しい修行を乗り越え";
		mes "良いモンクになってください。";
		close;
	}
	//メニュー部分
	next;
	switch(select('@word$[0],'@word$[1],'@word$[2])) {
	case 1:
		mes "[都護府員]";
		mes "うん、そうですか……";
		mes "分かりました。";
		mes "私たちモンクの修行する姿が";
		mes "何かの役に立つよう";
		mes "願っています。";
		set CHANGE_MO,1;
		close;
	case 2:
		if(Job != Job_Acolyte) {
			mes "[都護府員]";
			mes "はは、おもしろい冗談を言いますね。";
			close;
		}
		if(JobLevel < 40) {
			mes "[都護府員]";
			mes "うん……あなたにはまだ";
			mes "その資格が無いようです。";
			mes "我々は、アコライトJobLvが";
			mes "40以上の人だけに試練を受ける";
			mes "資格を与えているのです。";
			next;
			mes "[都護府員]";
			mes "ま、せっかく遠路いらした";
			mes "のですから、モンク達の修行姿を";
			mes "観察していくと良いでしょう。";
			next;
			mes "[都護府員]";
			mes "我々モンクの修行する姿が";
			mes "何かの役に立つよう";
			mes "願っています。";
			set CHANGE_MO,1;
			close;
		}
		mes "[都護府員]";
		mes "うん、JobLvもある程度まで";
		mes "達している様子。";
		mes "よし、中に入って無涯長老に";
		mes "お会いなさい。その方が";
		mes "あなたを導いてくださるでしょう。";
		set CHANGE_MO,2;
		close;
	case 3:
		mes "[都護府員]";
		mes "そうですか……長旅でお疲れの様子";
		mes "たまには休むことも大切です。";
		mes "こちらのモンク修練場で休んで";
		mes "いくと良いでしょう。";
		next;
		mes "[都護府員]";
		mes "いつも神に近づこうと努力する";
		mes "私達モンクの姿が、あなたの";
		mes "修行にも役立つことを願います。";
		set CHANGE_MO,1;
		close;
	}
OnTouch:
	if(Job == Job_Monk)
		end;
	switch(CHANGE_MO) {
	case 0:
		mes "[都護府員]";
		mes "何者！";
		mes "拙僧の許可なくこの神聖な";
		mes "修練場に立ち入ることは";
		mes "許されません！";
		next;
		mes "[都護府員]";
		mes "早々に立ち去りなさい！";
		close;
	case 1:
		mes "[都護府員]";
		mes "ゆっくり見ていきなさい。";
		mes "何か得るものがあるかもしれません。";
		close;
	case 2:
		mes "[都護府員]";
		mes "無涯長老にお会いなさい。";
		mes "長老はここから南東の方角、";
		mes "修道院内部にいらっしゃるはずです。";
		close;
	default:
		mes "[都護府員]";
		mes "うん……厳しい修行を乗り越え";
		mes "良いモンクになってください。";
		close;
	}
}

//==========================================
// 試験申請および転職
//------------------------------------------

monk_in.gat,99,58,4	script	長老	60,{
	mes "[無涯長老]";
	mes "大地と気の力が皆に";
	mes "幸運をもたらさんことを……";
	mes "ふむ、何用でわしを訪ねた？";
	next;
	if(SkillPoint) {
		mes "[無涯長老]";
		mes "スキルポイントが残っていては";
		mes "転職はかなわぬ！";
		mes "皆消費して来なさい。";
		close;
	}
	if(Job == Job_Monk) {
		mes "[無涯長老]";
		mes "修行は続けているか？";
		mes "常に精進を心がけるように。";
		next;
		mes "[無涯長老]";
		mes "我々は肉体を鍛え、強き精神を保たねば";
		mes "邪悪なる者がその肉体を狙いに来る。";
		next;
		mes "[無涯長老]";
		mes "いつも我々は神罰の代行者";
		mes "神の代理たることを忘れてはならぬ。";
		mes "邪悪な意志につけ込まれぬよう";
		mes "気をつけるのじゃ。";
		close;
	}
	if(Job != Job_Acolyte) {
		mes "[無涯長老]";
		mes "相談があるなら、プロンテラ大聖堂へ";
		mes "行くがよい。ここは相談所ではない。";
		mes "ましておぬしのように他の職業に就く";
		mes "者に述べることはない。";
		close;
	}
	switch(CHANGE_MO) {
	case 0:
	case 1:
		mes "[無涯長老]";
		mes "おぬしはアコライトだな。";
		mes "相談があるなら、プロンテラ大聖堂へ";
		mes "行ってみよ。ここは相談所ではない。";
		mes "モンクになるつもりがなければ、";
		mes "他の場所へ行くように。";
		close;
	case 2:
		mes "[無涯長老]";
		mes "モンクになりたいという";
		mes "若者のようだが……？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[無涯長老]";
			mes "ふむ……";
			mes "わしの勘も衰えたもんじゃ……";
			close;
		}
		mes "[無涯長老]";
		mes "ふむ……こんな時代にも";
		mes "まだ我々モンクの存在を";
		mes "忘れぬ者が居るとはな……";
		mes "よく参ったな、" +(Sex? "青年": "娘")+ "よ。";
		next;
		mes "[無涯長老]";
		mes "モンク志望生か……";
		mes "嬉しいのう。";
		mes "一応、モンクになる前に";
		mes "知っておかねばならぬことがある。";
		next;
		mes "[無涯長老]";
		mes "我らモンクは神に仕えながらも";
		mes "己の肉体を極限にまで鍛え、";
		mes "この世に信仰を伝える者である。";
		next;
		mes "[無涯長老]";
		mes "肉体を鍛えることは、信仰に仇なす";
		mes "モノを退け、自然の全ての事物と";
		mes "調和し、その恩恵を己身で受ける";
		mes "ためじゃ。";
		next;
		mes "[無涯長老]";
		mes "勿論、精神を鍛え、";
		mes "邪念を退けることも大事だぞ。";
		next;
		mes "[無涯長老]";
		mes "これらの修行過程は非常に";
		mes "厳しく、大きな苦を伴うかもしれん。";
		mes "が、これに耐えられるかどうかが";
		mes "モンクになれるかどうかの分かれ目と";
		mes "なる。";
		next;
		mes "[無涯長老]";
		mes "さて、ではおぬしがモンクとなり";
		mes "神に仕える確固たる意志があるか";
		mes "どうかを試したいと思う。";
		next;
		mes "[無涯長老]";
		mes "まず、その心構えができているか";
		mes "見るから、以下のものを集めて";
		mes "きなさい。";
		next;
		set CHANGE_MO,rand(3,9);
		switch(CHANGE_MO) {
		case 3:	//べとべとする液体5、ミミズの皮10、緑ハーブ20
			setarray '@need,938,1055,511;
			setarray '@amount,5,10,20;
			break;
		case 4:	//サルのしっぽ20、鉄鉱石5、青ハーブ3
			setarray '@need,942,1002,510;
			setarray '@amount,20,5,3;
			break;
		case 5:	//植物の茎30、ゼロピー5、蟲の皮10
			setarray '@need,905,909,955;
			setarray '@amount,30,5,10;
			break;
		case 6:	//けっこうかたい皮5、かたい皮20、ジャルゴン5
			setarray '@need,943,935,912;
			setarray '@amount,5,20,5;
			break;
		case 7:	//サイファー5、白ハーブ10、黄ハーブ10
			setarray '@need,7053,509,508;
			setarray '@amount,5,10,10;
			break;
		case 8:	//こうもりの牙10、くまの足の裏5、毒キノコの胞子20
			setarray '@need,913,948,7033;
			setarray '@amount,10,5,20;
			break;
		case 9:	//ハリネズミの針5、くもの糸20、短い足10
			setarray '@need,1027,1025,1042;
			setarray '@amount,5,20,10;
			break;
		}
		mes "[無涯長老]";
		for(set '@i,0; '@i<3; set '@i,'@i+1)
			mes getitemname('@need['@i])+ " " +'@amount['@i]+ "個";
		mes "を集めてくるように。";
		next;
		mes "[無涯長老]";
		mes "おぬし自身を試すのだから、";
		mes "自分の手で直接集めてくるように。";
		next;
		mes "[無涯長老]";
		mes "では揃ったらまた来なさい。";
		mes "さぁ出発じゃ！";
		mes "神のご加護があるよう祈っている。";
		close;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		mes "[無涯長老]";
		mes "ふむう……";
		next;
		switch(CHANGE_MO) {
		case 3:	//べとべとする液体5、ミミズの皮10、緑ハーブ20
			setarray '@need,938,1055,511;
			setarray '@amount,5,10,20;
			break;
		case 4:	//サルのしっぽ20、鉄鉱石5、青ハーブ3
			setarray '@need,942,1002,510;
			setarray '@amount,20,5,3;
			break;
		case 5:	//植物の茎30、ゼロピー5、蟲の皮10
			setarray '@need,905,909,955;
			setarray '@amount,30,5,10;
			break;
		case 6:	//けっこうかたい皮5、かたい皮20、ジャルゴン5
			setarray '@need,943,935,912;
			setarray '@amount,5,20,5;
			break;
		case 7:	//サイファー5、白ハーブ10、黄ハーブ10
			setarray '@need,7053,509,508;
			setarray '@amount,5,10,10;
			break;
		case 8:	//こうもりの牙10、くまの足の裏5、毒キノコの胞子20
			setarray '@need,913,948,7033;
			setarray '@amount,10,5,20;
			break;
		case 9:	//ハリネズミの針5、くもの糸20、短い足10
			setarray '@need,1027,1025,1042;
			setarray '@amount,5,20,10;
			break;
		}
		for(set '@i,0; '@i<3; set '@i,'@i+1) {
			if(countitem('@need['@i]) < '@amount['@i]) {
				mes "[無涯長老]";
				mes "まだ準備ができていない。";
				mes "集めるのは以下のものじゃ。";
				for(set '@i,0; '@i<3; set '@i,'@i+1)
					mes getitemname('@need['@i])+ " " +'@amount['@i]+ "個";
				mes "を集めてくるように。";
				close;
			}
		}
		for(set '@i,0; '@i<3; set '@i,'@i+1)
			delitem '@need['@i],'@amount['@i];
		set CHANGE_MO,10;
		mes "[無涯長老]";
		mes "うむ！全て手に入れてきたな！";
		mes "苦労したな！";
		mes "だがおぬしの意志は必ず神に";
		mes "伝わったことじゃろう。";
		next;
		mes "[無涯長老]";
		mes "よし、それでは先の修行に";
		mes "進んでもらおう。";
		mes "「童巴」に会うように。";
		mes "奴はここから北の";
		mes "墓地にいるはずじゃ。";
		close;
	case 10:
		mes "[無涯長老]";
		mes "次の修行に進んでもらう。";
		mes "「童巴」のところに行きなさい。";
		mes "奴はここから北の";
		mes "墓地にいるはずじゃ。";
		close;
	default:	//11～19の場合
		mes "[無涯長老]";
		mes "うむ、修行中じゃな。";
		mes "努力するように。";
		close;
	case 20:
		if(countitem(506)) {
			mes "[無涯長老]";
			mes "うん？まだ霊薬を飲んでいないな。";
			mes "その緑ポーションに似ている薬を";
			mes "飲みなさい。";
			mes "その薬を飲まなくてはモンクとして";
			mes "身体を整えることができんぞ。";
			close;
		}
		mes "[無涯長老]";
		mes "全ての修行を終えたな。";
		mes "もうおぬしはモンクになる資格が";
		mes "十分整った。";
		mes "今飲んだ霊薬によって身体も";
		mes "整えられたじゃろう。";
		next;
		mes "[無涯長老]";
		mes "まさか貴重な薬を捨ててはいまいな？";
		mes "では、モンクとして生きるための";
		mes "誓約を唱えれば転職完了とする。";
		next;
		mes "[無涯長老]";
		mes "おぬしは残った生の全てを";
		mes "神のために捧げるか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[無涯長老]";
			mes "……";
			mes "まだモンクになるための";
			mes "心ができていないと言うのか？";
			mes "もう少し修行をしてきなさい。";
			mes "悪に染まる者をモンクにする";
			mes "わけにはいかぬ。";
			close;
		}
		mes "[無涯長老]";
		mes "おぬしは手に入れた能力を";
		mes "己のためだけに行使するか？";
		next;
		if(select("はい","いいえ")==1) {
			mes "[無涯長老]";
			mes "ならぬ。我々モンクの力は";
			mes "己のためだけに使うのではない。";
			mes "神の代行者・神罰の執行者たる";
			mes "自覚を持ち生きなければならない。";
			mes "それを己のために行使するとは！";
			next;
			mes "[無涯長老]";
			mes "モンクとはどんな存在なのかを";
			mes "もう一度よく考えてくるのだ。";
			mes "そんな心構えでは世俗の欲心に";
			mes "染まり、しだいに能力も失うだろう。";
			close;
		}
		mes "[無涯長老]";
		mes "おぬしは神を汚す者に";
		mes "正義の審判を下すことを";
		mes "ためらわないか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[無涯長老]";
			mes "我々モンクを何と心得る。";
			mes "何人たりとも神を汚す者は";
			mes "世にあってはならぬ。";
			next;
			mes "[無涯長老]";
			mes "もう少しアコライトで";
			mes "修行を積んできなさい。";
			close;
		}
		mes "[無涯長老]";
		mes "おぬしは正義の審判を下す時、";
		mes "己の犠牲を省みずやれるか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[無涯長老]";
			mes "そんな覚悟ではならぬ。";
			mes "己を犠牲にしても正義を貫くことは";
			mes "立派なことじゃ。";
			next;
			mes "[無涯長老]";
			mes "犠牲というのはどういう意味かを";
			mes "よく考えてきなさい。";
			mes "決して易しいものではない……";
			close;
		}
		mes "[無涯長老]";
		mes "おぬしは多くのモンスターを";
		mes "引き連れることになろうとも";
		mes "他人の戦闘を助けるか？";
		next;
		if(select("はい","いいえ")==1) {
			mes "[無涯長老]";
			mes "それはならぬ。";
			mes "幾多のモンスターを引き連れる";
			mes "ことは、より犠牲を増やす種と";
			mes "なろう。そういう行動は慎まねば";
			mes "ならんのだ。";
			next;
			mes "[無涯長老]";
			mes "我々の強靭な精神と肉体を以ったと";
			mes "しても、完璧はない。";
			next;
			mes "[無涯長老]";
			mes "それが他人を助けているつもりでも、";
			mes "結果的にそれ以上の悪い事態をもたらす";
			mes "原因になりかねん。";
			mes "モンクのすべきことが何なのか";
			mes "もう一度考えてきなさい。";
			close;
		}
		mes "[無涯長老]";
		mes "おぬしは街や村で、同じ言葉を";
		mes "発しながら歩くことをするか？";
		next;
		if(select("はい","いいえ")==1) {
			mes "[無涯長老]";
			mes "いかん。";
			mes "これはモンクだけにではなく、";
			mes "全ての人間に言えることじゃ。";
			mes "うるさく叫んだところで相手に";
			mes "されんじゃろうしな。";
			next;
			mes "[無涯長老]";
			mes "説法を行うときでも同じだ。";
			mes "己の行動を今一度振り返るのじゃ。";
			close;
		}
		mes "[無涯長老]";
		mes "おぬしは自分が神の代行者で";
		mes "あることを自覚し、神のために";
		mes "身を捧げることができるか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[無涯長老]";
			mes "そんな心得ではモンクに";
			mes "なることはかなわぬ。";
			mes "我々の死と共に神に反する";
			mes "者を一つでも減らすことが";
			mes "できれば、それは意味を成す";
			mes "のじゃ。";
			close;
		}
		mes "[無涯長老]";
		mes "最後に、今まで述べたことを";
		mes "全て守ると誓いなさい。";
		next;
		if(select("誓います","無理です")==2) {
			mes "[無涯長老]";
			mes "……";
			next;
			mes "[無涯長老]";
			mes "まだ修行が足りないようだ。";
			mes (Sex? "青年": "娘")+ "よ、まだモンクに認める";
			mes "ことはできぬ。";
			next;
			mes "[無涯長老]";
			mes "再び始めから修行を行った";
			mes "ほうが良いが……";
			mes "心を鎮めてまた参れ。";
			next;
			mes "[無涯長老]";
			mes (Sex? "青年": "娘")+ "に信義が伝わるように……";
			close;
		}
		mes "[無涯長老]";
		mes "それでは、これにて誓約の儀を";
		mes "終わる。";
		mes "我々の" +(Sex? "兄弟": "姉妹")+ "、今ここに生まれる！";
		next;
		mes "[無涯長老]";
		mes (Sex? "青年": "娘")+ "の誓約は私の胸と君の胸、";
		mes "我々を見守る神に伝わった。";
		next;
		mes "[無涯長老]";
		mes "それではこれから";
		mes "おぬしの経絡を突く。";
		next;
		mes "[無涯長老]";
		mes "さぁ……これから365個の経絡を";
		mes "突くぞ。動くなよ！";
		next;
		mes "[無涯長老]";
		mes "カーーーーッ";
		next;
		mes "[無涯長老]";
		mes "フゥゥゥゥーー";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "- 師匠は深呼吸をした後 -";
		next;
		mes "[" +strcharinfo(0)+ "]";
		mes "- 私の経絡を突き始めた -";
		next;
		mes "[無涯長老]";
		mes "ヌオリャ！！";
		next;
		mes "[無涯長老]";
		mes "アタタタタタタ";
		next;
		mes "[無涯長老]";
		mes "セイッ！";
		next;
		mes "[無涯長老]";
		mes "チョイヤー！";
		next;
		mes "[無涯長老]";
		mes "フゥゥゥゥゥー";
		next;
		mes "[無涯長老]";
		mes "オワタァ！";
		next;
		set '@itemid,(JobLevel >= 50)? 1804: 1801;
		unequip;
		jobchange job_Monk;
		set CHANGE_MO,0;
		mes "[無涯長老]";
		mes "転職完了だ。";
		next;
		mes "[無涯長老]";
		mes "クッ……";
		next;
		mes "[無涯長老]";
		mes "やはり……老いには勝てぬ……";
		next;
		mes "[無涯長老]";
		mes "さぁ、おぬしもモンクだ。";
		mes "同志になったことを祝おう。";
		next;
		mes "[無涯長老]";
		mes "先ほどの誓約を忘れるでないぞ。";
		next;
		mes "[無涯長老]";
		mes "ゆるぎない信仰のもと、";
		mes "己の修行を忘れるなよ。";
		next;
		mes "[無涯長老]";
		mes "これは君に与える祝いの品だ。";
		mes "役立てるがよい。";
		getitem '@itemid,1;
		close;
	}
}

//==========================================
// 一次試験（心得暗唱）
//------------------------------------------

prt_monk.gat,251,255,4	script	童巴	79,{
	switch(CHANGE_MO) {
	default:
		mes "[童巴]";
		mes "私たちモンクは、";
		mes "神の代弁者です……";
		mes "そして神罰の代行者！";
		next;
		mes "[童巴]";
		mes "私たちの道を遮ることは";
		mes "すなわち神に反すること！";
		next;
		mes "[童巴]";
		mes "よって……";
		mes "あなたも敵ですか!?";
		mes "私の前を塞いだから……";
		next;
		mes "[童巴]";
		mes "私の前を阻むことは……";
		mes "……";
		mes "キィェェェェェェィ！";
		next;
		mes "[童巴]";
		mes "ハッハッハ……";
		next;
		mes "[童巴]";
		mes "驚きましたか？";
		mes "なに、素振りです。";
		close;
	case 10:
		mes "[童巴]";
		mes "何の用ですか？";
		mes "神に関する話をしたいのですか？";
		next;
		mes "[童巴]";
		mes "あなたはモンクへの修行を";
		mes "続ける身。あなたの気の流れは";
		mes "だいぶモンクのそれに近い。";
		next;
		mes "[童巴]";
		mes "気脈が開かれていることを悟ったら";
		mes "無涯長老様のところへ行くと";
		mes "良いでしょう。";
		next;
		mes "[童巴]";
		mes "私は、モンクになる者ならば";
		mes "かならず知っていなければならない";
		mes "知識について教えています。";
		mes "私からの教えを理解した後、";
		mes "身体の鍛錬を行います。";
		next;
		mes "[童巴]";
		mes "私がこれから述べることを覚え、";
		mes "後で暗唱してくだされば結構です。";
		mes "さぁ、精神集中はできていますか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[童巴]";
			mes "準備ができたらまた来てください。";
			close;
		}
		mes "[童巴]";
		mes "それでは……";
		next;
		mes "[童巴]";
		mes "よく聴いて心で覚えてください。";
		set CHANGE_MO,rand(11,13);
		break;
	case 11:
	case 12:
	case 13:
		mes "[童巴]";
		mes "よろしい、もう一度唱えましょう。";
		break;
	case 14:
		mes "[童巴]";
		mes "うん……？";
		mes "誰の元へ行くかはすでに";
		mes "教えたはず……";
		next;
		mes "[童巴]";
		mes "もしや……";
		next;
		mes "[童巴]";
		mes "私の忍耐力を試しているとか……？";
		next;
		mes "[童巴]";
		mes "よろしい。";
		mes "もう一度申し上げますが";
		mes "富年様にお会いください。";
		close;
	case 15:
		mes "[童巴]";
		mes "残った修行も完遂してください。";
		close;
	}
	next;
	switch(CHANGE_MO) {
	case 11:
		setarray '@list$,"神に仇名す者に審判を！","神に仇名す者に天罰を！","神に仇名す者に終焉を！","私たちモンクは","神の意志を地上に伝える","神の代弁者であり","神罰の代行者である","この身切り裂かれ焼かれようと","すべては神のために","神に仇名す者を裁くために";
		break;
	case 12:
		setarray '@list$,"神の代弁者であり","神罰の代行者である","モンク","私たちの使命は","私たちに与えられた肉体で","神に仇名す","愚かなる者等を","徘徊する邪悪な者等を","最後まで追い詰め","消滅させること";
		break;
	case 13:
		setarray '@list$,"神の声を世に伝えるべく","与えられた肉体を持つ","私たちモンクは","神罰の代行者であり","神の代弁者である","私たちの使命は","神に仇名す","死ぬことさえできぬ者","愚かな者等を","消滅させること";
		break;
	}
	for(set '@i,0; '@i<10; set '@i,'@i+1) {
		mes "[童巴]";
		mes '@list$['@i];
		next;
	}
	mes "[童巴]";
	mes "はい、ここまでです。";
	mes strcharinfo(0)+ "、あなたの番です。";
	next;
	function Shuffle;
	for(set '@c,0; '@c<10; set '@c,'@c+1) {
		Shuffle '@list$;
		set '@ret,select(	@monk_word$[0],@monk_word$[1],@monk_word$[2],@monk_word$[3],@monk_word$[4],
					@monk_word$[5],@monk_word$[6],@monk_word$[7],@monk_word$[8],@monk_word$[9])-1;
		if('@c == 0)
			mes "["+strcharinfo(0)+"]";
		mes @monk_word$['@ret];
		if(@monk_word$['@ret] == '@list$['@c])
			set '@point,'@point+1;
	}
	cleararray @monk_word$,"",10;	//もう使わないので消去
	next;
	mes "[童巴]";
	mes "ふぅ……";
	mes "お疲れさまでした。";
	next;
	mes "[童巴]";
	mes "さて……";
	next;
	if('@point == 10) {
		mes "[童巴]";
		mes "立派ですね、完璧でした。";
		next;
		mes "[童巴]";
		mes "しかし油断は禁物。";
		mes "モンクへの道はまだまだ";
		mes "険しい……";
		next;
		mes "[童巴]";
		mes "タァッ！";
		next;
		mes "セイッ！";
		next;
		mes "ハァッ！";
		next;
		mes "イヤァッ！";
		next;
		mes "[童巴]";
		mes "あなたの血脈はひとつ";
		mes "モンクのそれに近づいたようです。";
		next;
		mes "[童巴]";
		mes "では、富年様のところへ";
		mes "行って見なさい。";
		set CHANGE_MO,14;
		close;
	}
	mes "[童巴]";
	mes "ん……この程度も覚えられないとは……";
	next;
	mes "[童巴]";
	mes "さきほども申し上げましたが";
	mes "ただ覚えるのではなく、";
	mes "心で理解するのです。";
	next;
	mes "[童巴]";
	mes "さぁ、もう一度試みましょう。";
	next;
	mes "[童巴]";
	mes "一応申し上げておきますが、";
	mes "これを終えなければ";
	mes "先に進むことはできません。";
	close;

	//'@list$の文字列をシャッフルして@monk_word$に格納する
	function Shuffle {
		setarray '@num,0,1,2,3,4,5,6,7,8,9;
		for(set '@i,10; '@i>0; set '@i,'@i-1) {
			set '@r,rand('@i);
			set @monk_word$[10-'@i],getelementofarray(getarg(0),'@num['@r]);	//グローバル変数として扱う
			deletearray '@num['@r],1;						//選択された番号は削る
		}
		return;
	}
}

//==========================================
// ニ次試験（課題試験）
//------------------------------------------

prt_monk.gat,57,179,0	script	富年	110,{
	switch(CHANGE_MO) {
	default:
		mes "[富年]";
		mes "ハァァァァ！";
		next;
		mes "- 瞑想に耽っているようだ -";
		close;
	case 14:
		mes "[富年]";
		mes "……";
		next;
		mes "[富年]";
		mes "…………";
		next;
		mes "[富年]";
		mes "………………";
		next;
		mes "[富年]";
		mes "……………………";
		next;
		menu "あの……",-;
		mes "[富年]";
		mes "何だ……";
		mes "神との対話を邪魔するからには";
		mes "相応の訳あってのことだろうな？";
		next;
		mes "[富年]";
		mes "……";
		mes "まずその命、預かろう。";
		next;
		mes "[富年]";
		mes "さぁ、何用で来たか";
		mes "説明するように。";
		next;
		if(select("童巴様の紹介で来ました","何でもないです")==2) {
			mes "[富年]";
			mes "……";
			mes "ふむ……無事で帰れると";
			mes "思うなよ？";
			close;
		}
		mes "[富年]";
		mes "うん？そうか……";
		mes "どれ……";
		next;
		mes "[富年]";
		mes "ふむ……";
		mes "血脈が……";
		mes "そうか、よし……";
		next;
		mes "[富年]";
		mes "ところで、童巴と";
		mes "何をしたのだ？";
		next;
		if(select("あ……えっと……","文を暗唱しました","血脈診断をしてもらいました")!=2) {
			mes "[富年]";
			mes "たわけが！";
			mes "邪魔するでない！";
			close;
		}
		mes "[富年]";
		mes "ふむ、して……";
		mes "その結果は？";
		next;
		switch(select("あ……何だっけ……","体を鍛えました","モンクへの初歩を教えていただきました","モンクの血脈に近づけていただきました")) {
			default:
				mes "[富年]";
				mes "たわけが！";
				mes "邪魔するでない！";
				close;
			case 3:
				mes "[富年]";
				mes "正しく聞こえるが……";
				mes "正確な答えではない。";
				close;
			case 4:
				mes "[富年]";
				mes "そう、自分の体の中で";
				mes "何が変わったか自覚したな。";
				mes "よし、次の修行へ移るか。";
				next;
				mes "[富年]";
				mes "よし、私はお前に修行について";
				mes "選択の余地を与えてやる。";
				mes "次からいずれかを選んで";
				mes "修行を行うがよい。";
				next;
				if(select("キノコ採集","マラソン")==1) {
					mes "[富年]";
					mes "ふむ、キノコ採集ということは";
					mes "忍耐力を鍛えようというのか。";
					mes "わかった。準備を終えてから";
					mes "また話しかけるがよい。";
					set CHANGE_MO,15;
				}
				else {
					mes "[富年]";
					mes "ふむ、体力の限界を見極めつつ";
					mes "強靭な肉体を得るというのだな。";
					mes "よし、準備を終えてから";
					mes "また話しかけるがよい。";
					set CHANGE_MO,16;
				}
				close;
		}
	case 15:
		mes "[富年]";
		mes "準備はできたか。";
		next;
		mes "[富年]";
		mes "お前が選んだキノコ採集は";
		mes "たとえるなら忍耐力の試験だ。";
		next;
		mes "[富年]";
		mes "ここの修道院の中で";
		mes "お前と志を共にする者と";
		mes "一緒に試験を受けてもらう。";
		next;
		mes "[富年]";
		mes "同時に受ける者が多ければ";
		mes "それだけキノコを探すのが";
		mes "困難になるが、同じ道を歩もうと";
		mes "する仲間だ。争うでないぞ。";
		close;
	case 16:
		mes "[富年]";
		mes "準備はできたか。";
		next;
		mes "[富年]";
		mes "お前が選んだマラソンは";
		mes "たとえるなら自分との戦いだ。";
		next;
		mes "[富年]";
		mes "ここの修道院の中へ入るが良い。";
		next;
		mes "[富年]";
		mes "あるコースを指定回数まわる試験だ。";
		mes "では行ってこい。";
		close;
	}
}

prt_monk.gat,199,169,3	script	守門将	746,{
	mes "[守門将張力]";
	mes "こちらは";
	mes "モンク転職試験場です。";
	next;
	switch(CHANGE_MO) {
	default:
		mes "[守門将張力]";
		mes "中では静かに！";
		close;
	case 14:
		mes "[守門将張力]";
		mes "富年様ですか……？";
		next;
		mes "[守門将張力]";
		mes "富年様は静かな場所を";
		mes "好まれます。";
		mes "隅の方とかですね……";
		close;
	case 15:
	case 16:
		mes "[守門将張力]";
		mes strcharinfo(0)+ "……ですか？";
		next;
		if(select("はい！","いいえ")==1) {
			mes "[守門将張力]";
			mes "よし、良い返事です！";
			mes "試験があなたを待っていますよ！";
			mes "中へどうぞ。";
			close;
		}
		mes "[守門将張力]";
		mes "違うわけはない！";
		mes "さぁ中に入るのです！";
		close;
	}
}

monk_test.gat,329,61,3	script	助教	753,{
	switch(CHANGE_MO) {
	default:
		mes "[馬周]";
		mes "こんにちは、こちらはモンク修練場、";
		mes "聖カピトーリナ修道院です。";
		mes "中には斗門様がいらっしゃいます。";
		next;
		mes "[馬周]";
		mes "あちこち置いてある物を";
		mes "触ったり、騒いだりすること";
		mes "だけは遠慮してください。";
		close;
	case 15:
	case 16:
		mes "[馬周]";
		mes "どの試験場に移動しますか？";
		next;
		mes "[馬周]";
		mes "一応、私が聞いたところによると";
		mes ((CHANGE_MO==15)? "キノコ採集": "マラソン")+"試験でしたが……";
		mes "選択は自由です。";
		next;
		if(select("忍耐-キノコ採集","自分との戦い-マラソン試験")==1) {
			mes "忍耐-キノコ採集試験を";
			mes "選択しました。";
			set CHANGE_MO,15;
			close2;
			warp "job_monk.gat",226,175;
		}
		else {
			mes "自分への挑戦-マラソンを";
			mes "選択しました。";
			set CHANGE_MO,16;
			close2;
			warp "monk_test.gat",386,387;
		}
		end;
	}
}

//==========================================
// 課題試験（キノコ採集）
//------------------------------------------

job_monk.gat,225,180,0	script	助教	89,{
	if(countitem(1069)) {	//紅の毛ベトベトキノコだけでは無反応
		if(countitem(1069) >=30 || countitem(1070) >=30) {
			mes "[玄武]";
			mes "うむ！上等だ！";
			mes "先に進んでよろしい。";
			next;
			mes "[玄武]";
			mes "次は「斗門」様に";
			mes "会ってみなさい。";
			mes "斗門様は修道院建物内の";
			mes "一番奥にいらっしゃるはずだ。";
			delitem 1069,countitem(1069);
			delitem 1070,countitem(1070);
			set CHANGE_MO,17;
			close2;
			warp "prt_monk.gat",194,168;
			end;
		}
		mes "[玄武]";
		mes "むう……まだ少ないな。";
		next;
		mes "[玄武]";
		mes "あきらめるか？";
		next;
		if(select("キノコをもっと探す","あきらめる")==1) {
			mes "[玄武]";
			mes "頑張れぃ！";
			close;
		}
	}
	else {
		mes "[玄武]";
		mes "よし、私はこのキノコ採集試験を";
		mes "担当している「玄武」と言う。";
		next;
		mes "[玄武]";
		mes "貴様が今から体験する苦難は";
		mes "いわば試練と思うように。";
		next;
		mes "[玄武]";
		mes "我らは精神修行の一環として";
		mes "簡単な作物を栽培している。";
		mes "しかし最近、その作物のまわりに";
		mes "ひどい臭いを放つキノコができて";
		mes "しまってな……";
		next;
		mes "[玄武]";
		mes "そのキノコを撲滅するのを";
		mes "手伝ってもらう。";
		mes "ある程度伐採できたら";
		mes "その証拠を持ってくれば良い。";
		next;
		mes "[玄武]";
		mes "証拠とは、";
		mes "「紅の毛網キノコ」と";
		mes "「紅の毛ベトベトキノコ」";
		mes "である。";
		next;
		mes "[玄武]";
		mes "早くモンクになりたくば、";
		mes "さっさとこれらを集めることだ。";
		mes "いくつ集めよとは言わぬが、";
		mes "ある程度集めたら見せにくるように。";
		next;
		mes "[玄武]";
		mes "では始めるか？";
		next;
		if(select("キノコを狩る","あきらめる")==1) {
			mes "[玄武]";
			mes "では頑張ってくれ！";
			close;
		}
	}
	announce "助教: " +strcharinfo(0)+ "、転職試験 -キノコ採集- を断念",9;
	mes "[玄武]";
	mes "貴様も根性が無いな……";
	close2;
	warp "prt_monk.gat",194,168;
	end;
}

//==========================================
// 課題試験（マラソン）
//------------------------------------------

monk_test.gat,386,388,4	script	助教	110,{
	mes "[見習いモンク]";
	mes "よくいらっしゃいました。";
	mes "ここは自分を試す試練の場。";
	next;
	mes "[見習いモンク]";
	mes "と言ってもただ走るだけです。";
	mes "とにかくひたすら走るのです。";
	next;
	mes "[見習いモンク]";
	mes "途中で投げ出したりしてはなりません。";
	next;
	if(select("無理です","とにかく走る")==2) {
		mes "[見習いモンク]";
		mes "そうです、走り続けるのです！";
		close;
	}
	announce "助教: " +strcharinfo(0)+ "、転職試験を放棄！",9;
	mes "[見習いモンク]";
	mes strcharinfo(0)+ "、転職試験を放棄！";
	set @monk_test,0;
	close2;
	warp "prt_monk.gat",194,168;
	end;
}

monk_test.gat,387,350,0	script	#MO_Goal	45,2,2,{
	set @monk_test,@monk_test+1;
	if(@monk_test == 9) {
		warp "monk_test.gat",385,388;
		sleep 500;
		announce "監督: よし、最後の周回だ。これを終えれば試験終了だ。",9;
		end;
	}
	if(@monk_test == 10) {
		announce "監督: 頑張ったな、" +strcharinfo(0)+ "!! 完走だ！",9;
		mes "[試験監督]";
		mes "よし、「斗門」様のところに";
		mes "行きなさい。";
		mes "斗門様は修道院内部の";
		mes "一番奥にいらっしゃる。";
		set CHANGE_MO,17;
		close2;
		warp "prt_monk.gat",194,168;
		end;
	}
	warp "monk_test.gat",385,388;
	end;
}

monk_test.gat,82,384,0	script	#MO_Abyss	139,0,0,{
	announce "落とし穴: " +strcharinfo(0)+ "、コースから外れた。元の位置から開始だ。",9;
	warp "monk_test.gat",387,387;
	end;
}

monk_test.gat,82,385,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,83,384,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,83,385,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,82,390,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,82,391,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,83,390,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,83,391,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,38,387,0	duplicate(#MO_Abyss)	落とし穴	139,0,1
monk_test.gat,38,389,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,39,387,0	duplicate(#MO_Abyss)	落とし穴	139,0,1
monk_test.gat,39,389,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,11,158,0	duplicate(#MO_Abyss)	落とし穴	139,1,0
monk_test.gat,13,158,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,11,159,0	duplicate(#MO_Abyss)	落とし穴	139,1,0
monk_test.gat,13,159,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,11,30,0	duplicate(#MO_Abyss)	落とし穴	139,3,0
monk_test.gat,15,30,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,11,31,0	duplicate(#MO_Abyss)	落とし穴	139,3,0
monk_test.gat,15,31,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,70,11,0	duplicate(#MO_Abyss)	落とし穴	139,0,1
monk_test.gat,70,13,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,71,11,0	duplicate(#MO_Abyss)	落とし穴	139,0,1
monk_test.gat,71,13,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,186,11,0	duplicate(#MO_Abyss)	落とし穴	139,2,3
monk_test.gat,189,11,0	duplicate(#MO_Abyss)	落とし穴	139,0,3
monk_test.gat,387,42,0	duplicate(#MO_Abyss)	落とし穴	139,1,0
monk_test.gat,387,43,0	duplicate(#MO_Abyss)	落とし穴	139,1,0
monk_test.gat,389,42,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,389,43,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,387,164,0	duplicate(#MO_Abyss)	落とし穴	139,1,0
monk_test.gat,387,165,0	duplicate(#MO_Abyss)	落とし穴	139,1,0
monk_test.gat,389,164,0	duplicate(#MO_Abyss)	落とし穴	139,0,0
monk_test.gat,389,165,0	duplicate(#MO_Abyss)	落とし穴	139,0,0

//==========================================
// 三次試験（駆魔修行）
//------------------------------------------

monk_test.gat,319,139,4	script	斗門	52,{
	switch(CHANGE_MO) {
	default:
		mes "[斗門]";
		mes "静かにしなさい……";
		mes "フゥゥゥゥ……";
		next;
		mes "[斗門]";
		mes "ここ聖カピトーリナ修道院には";
		mes "先代方の残された偉業が";
		mes "眠っている。";
		next;
		mes "[斗門]";
		mes "あの裏に封印された我らの宿敵の";
		mes "眠りを解いてはならぬ……";
		close;
	case 17:
		mes "[斗門]";
		mes "よくぞここまで努力した！";
		mes "私は最後の試験、駆魔修行を";
		mes "担当している「斗門」と言う。";
		next;
		mes "[斗門]";
		mes "さぁ、言葉は必要ない！";
		mes "行動あるのみだ。";
		next;
		mes "[斗門]";
		mes "迷路の中に現れる全ての「魔」を";
		mes "お前の手でこの世から消し去るのだ。";
		next;
		mes "[斗門]";
		mes "ひ弱なプリーストと一緒になるなよ。";
		mes "我らには鍛えられた強靭な肉体がある。";
		next;
		mes "[斗門]";
		mes "さぁ、拳を握り、立ち上がるのだ！";
		next;
		mes "[斗門]";
		mes "思い切り実力を発揮してみよ！";
		set CHANGE_MO,18;
		close2;
		warp "monk_test.gat",88,74;
		end;
	case 18:
		mes "[斗門]";
		mes "うむ……";
		mes "失敗は成功の母と言う。";
		mes "さぁ、力を出して行くのだ！";
		close2;
		warp "monk_test.gat",88,74;
		end;
	case 19:
		mes "[斗門]";
		mes "よくできた！";
		mes "私の目に狂いはなかったな。";
		mes "よし、お前の内功を高めてやろう。";
		next;
		mes "[斗門]";
		mes "それを飲めば、お前の内功が";
		mes "高まり、モンクたる資格を得る";
		mes "ことができるはずだ。";
		mes "あとは「無涯」長老の元へ行け！";
		getitem 506,1;
		set CHANGE_MO,20;
		close;
	case 20:
		mes "[斗門]";
		mes "無涯長老の元へ行け！";
		close;
	}
}

monk_test.gat,88,91,4	script	試験監督#MO_Test	52,{
	mes "[斗門]";
	mes "さて、駆魔修行の準備は";
	mes "整ったかな？";
	next;
	switch(select("はい","いいえ","注意事項を聞く")) {
	case 1:
		mes "[斗門]";
		mes "それでは健闘を祈る。";
		mes "迷路に迷い、帰れなくなったら";
		mes "一度終了するといい……";
		mes "しかしその場合は最後に記録";
		mes "した場所に戻されるがな。";
		close2;
		if(strnpcinfo(2) == "MO_Test")
			warp "monk_test.gat",125,177;
		else if(strnpcinfo(2) == "MO_Test1")
			warp "monk_test.gat",125,277;
		else
			warp "monk_test.gat",229,277;
		if(getnpctimer(1,"MO_Timer") == 0)	//タイマーが停止してたら始動
			initnpctimer "MO_Timer";
		end;
	case 2:
		mes "[斗門]";
		mes "用意ができたら話しかけてくれ。";
		close;
	case 3:
		mes "[斗門]";
		mes "試験場内部には、目に見えない";
		mes "壁がある。";
		mes "修行のため、簡単に移動できぬ";
		mes "よう結界をはったのだ。";
		next;
		mes "[斗門]";
		mes "開始位置から反対側まで";
		mes "辿り着けば出口がある。";
		next;
		mes "[斗門]";
		mes "修行場内部には";
		mes "邪悪なる者が徘徊している。";
		mes "行く手を阻まれたら迷わず";
		mes "打ち倒すのだ。";
		mes "それでは健闘を祈る。";
		close;
	}
}

monk_test.gat,82,85,1	duplicate(試験監督#MO_Test)	試験監督#MO_Test1	95
monk_test.gat,95,85,4	duplicate(試験監督#MO_Test)	試験監督#MO_Test2	79

//==============================================================
monk_test.gat,140,181,0	script	#MO_Test1-1	139,1,1,{
	monster "monk_test.gat",140,181,"ゾンビ",1015,4;
	end;
}

monk_test.gat,150,164,0	script	#MO_Test1-2	139,1,1,{
	monster "monk_test.gat",150,164,"ゾンビ",1015,4;
	end;
}

monk_test.gat,158,192,0	script	#MO_Test1-3	139,1,1,{
	monster "monk_test.gat",158,192,"マミー",1041,1;
	end;
}

monk_test.gat,134,291,0	script	#MO_Test2-1	139,1,1,{
	monster "monk_test.gat",134,291,"ゾンビ",1015,4;
	end;
}

monk_test.gat,144,277,0	script	#MO_Test2-2	139,1,1,{
	monster "monk_test.gat",144,277,"ゾンビ",1015,4;
	end;
}

monk_test.gat,149,268,0	script	#MO_Test2-3	139,1,1,{
	monster "monk_test.gat",149,268,"ゾンビ",1015,5;
	end;
}

monk_test.gat,249,277,0	script	#MO_Test3-1	139,1,1,{
	monster "monk_test.gat",249,277,"ゾンビ",1015,4;
	end;
}

monk_test.gat,252,284,0	script	#MO_Test3-2	139,1,1,{
	monster "monk_test.gat",252,284,"マミー",1041,1;
	end;
}

monk_test.gat,264,292,0	script	#MO_Test3-3	139,1,1,{
	monster "monk_test.gat",264,292,"マミー",1041,1;
	end;
}

//==============================================================
monk_test.gat,0,0,0	script	MO_Timer	-1,{
	end;
OnTimer100000:
	killmonster "monk_test.gat","All";
	//試験エリア内に誰も居ないならタイマー止める
	if(getareausers("this",124,158,167,197) + getareausers("this",124,259,167,296) + getareausers("this",228,258,271,297) == 0)
		stopnpctimer;
	else
		initnpctimer;
	end;
}

//==============================================================

monk_test.gat,166,178,0	script	#MO_Goal_	45,1,1,{
	mes "[試験監督]";
	mes "よし、頑張ったな。";
	mes "斗門様の元へ戻れ。";
	set CHANGE_MO,19;
	close2;
	warp "prt_monk.gat",196,168;
	end;
}

monk_test.gat,166,278,0	duplicate(#MO_Goal_)	#MO_Goal	45,1,1
monk_test.gat,270,278,0	duplicate(#MO_Goal_)	#MO_Goal	45,1,1
