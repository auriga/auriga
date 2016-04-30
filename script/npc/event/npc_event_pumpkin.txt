//カボチャ部屋の設定
//(本来はforce_1-1.gat しかし、アリーナクエストと重複するため、同MAP異名の2-1を使用)
//	→ 現在2-1も重複するのでこのスクリプトを利用したい場合は適切な場所に移動すること

force_2-1.gat,100,100,0,0	monster	ザック	1130,200,50000,25000
force_2-1.gat,100,100,0,0	monster	ブラッディナイト	1268,5,50000,25000
force_2-1.gat	mapflag	nosave	prontera.gat,156,191
force_2-1.gat	mapflag	nomemo	dummy
force_2-1.gat	mapflag	noteleport	dummy
force_2-1.gat	mapflag	pvp	dummy
//イベントホールの設定
pvp_2vs2.gat	mapflag	nosave	prontera.gat,156,191
pvp_2vs2.gat	mapflag	nomemo	dummy
pvp_2vs2.gat	mapflag	noteleport	dummy
pvp_2vs2.gat	mapflag	pvp	dummy


prt_monk.gat,225,180,0	script	助教	89,{
	mes "[玄武]";
	mes "作物が育つ様を見ていると";
	mes "神の寵愛を感じずにはいられない。";
	next;
	mes "[玄武]";
	mes "その作物を栽培する我らモンクの";
	mes "働きもまた美しい。";
	next;
	mes "[玄武]";
	mes "本当に農業はいい……";
	mes "貴様が普段口にする野菜もまた";
	mes "誰かの努力の結晶なのだ。";
	next;
	mes "[玄武]";
	mes "この地上に命をお与えになった神と";
	mes "作物を栽培する者すべてに";
	mes "いつも感謝の気持ちを持つのだ。";
	next;
	mes "[玄武]";
	mes "農業は国の基盤。";
	mes "何と良い言葉であろうか……";
	close;
}

gef_fild00.gat,77,212,4	script	生意気な子	716,{
	mes "[生意気な子]";
	mes "ちっ、あのピエロめ・・・";
	mes "僕のキャンディーを奪った上に、";
	mes "もっといい物持って来いだなんて！";
	mes "これだから大人はキライなんだよ。";
	mes "絶対いつか仕返ししてやる！！";
	close;
}

pvp_2vs2.gat,40,30,4	script	臆病者	67,{
	mes "[臆病者]";
	mes "おれを殴る気なのか？！";
	mes "く、くるな～～～！！";
	mes "おまえなんかどっかに飛んでいけ！";
	close2;
	warp "prt_monk.gat",95,212;
	end;
}

// ■ PUMP_EVE -> 0～2

xmas_in.gat,27,103,4	script	太っちょおばさん#pump	701,{
	if(PUMP_EVE != 1) {
		mes "[タシンチェ]";
		mes "メリークリスマスー";
		mes "ほっほほほ～";
		mes "シーズンがシーズンだから";
		mes "若者がたくさん見られるねぇ～。";
		mes "アタイも一緒に若くなったみたいね～。";
		mes "ほっほほほ～";
		next;
		mes "[タシンチェ]";
		mes "この村にはルティエダンジョンという";
		mes "おもちゃ工場みたいな";
		mes "ところがあるけど、";
		mes "まあ、他の人から聞いたら";
		mes "なんとなく分かると思うけどねー";
		mes "あ、それが…";
		next;
		mes "[タシンチェ]";
		mes "この前分かったことなんだけどね、";
		mes "あのダンジョンの中で住んでる";
		mes "モンスターの中には";
		mes "他所でも見られるのと";
		mes "似ている奴らもいるらしいの。";
		next;
		mes "[タシンチェ]";
		mes "見掛は同じだけどね、";
		mes "多分この地方は本当に寒いから";
		mes "その性格が変わってしまったり、";
		mes "色が変わってしまったりする";
		mes "みたいなのよ。アタイらも相当ここに";
		next;
		mes "[タシンチェ]";
		mes "適応しているんでしょうけど。";
		mes "ほっほほほ～";
		mes "それじゃ、そろそろアタイも";
		mes "キムチ作りの準備をしようか。";
		mes "ああ、何のキムチを作るかって？";
		mes "アタイは「チョコキムチ」だねぇ。";
		next;
		mes "[タシンチェ]";
		mes "白菜キムチと";
		mes "チョコレートを良く混ぜて";
		mes "作り出したアタイんちの傑作品!!";
		mes "ほっほほほ～";
		mes "一口食べると忘れられないのよ";
		mes "ほーほっほほほほ!!!!";
		close;
	}
	//pumpkin event
	mes "[タシンチェ]";
	mes "おや、魔法のカボチャじゃないか。";
	mes "え？料理して欲しいのかい？";
	mes "じゃあ腕を振るってあげようかね。";
	next;
	mes "[タシンチェ]";
	mes "何が食べたいんだい？";
	mes "おすすめはアイスと";
	mes "キャンディーだよ。";
	mes "アイスは普通っぽく";
	mes "なっちゃうけどね。";
	next;
	if(select("アイス","キャンディー")==1) {
		mes "[タシンチェ]";
		mes "よし、作るよ。";
		mes "さあ、キムチを混ぜて";
		next;
		mes "- ゴリゴリ ガンガン -";
		next;
		mes "- ・・・ Success !! -";
		next;
		mes "[タシンチェ]";
		mes "さあ、出来た！";
		getitem 536,1;
		set PUMP_EVE,0;
		next;
		mes "[タシンチェ]";
		mes "普通のアイスとは";
		mes "ほんのちょっとだけ";
		mes "一味違うんだよ。";
		mes "わかるかねぇ？";
	}
	else {
		mes "[タシンチェ]";
		mes "よし、作るよ。";
		mes "キムチ持っといで～";
		next;
		mes "- カキンカキン ジャージャー -";
		next;
		mes "- ・・・ Success !! -";
		next;
		mes "[タシンチェ]";
		mes "さあ、出来た！";
		mes "「パンプキンキャンディー」だよ。";
		mes "そこらのキャンディーとは";
		mes "一味も二味も違うんだよ。";
		mes "わかるかねぇ？";
		next;
		set PUMP_EVE,2;
		mes "- パンプキンキャンディー -";
		mes "- を手に入れた -";
	}
	close;
OnInit:
	disablenpc "太っちょおばさん#normal";
	end;
}

//--------------------------------------------------
prt_monk.gat,218,175,4	script	修道士	49,{
	if(PUMP_EVE == 0) {
		mes "[修道士]";
		mes "今年は何年かぶりに";
		mes "魔法のカボチャが取れました。";
		mes "私たちは食糧備蓄のために";
		mes "魔法のカボチャ1個と";
		mes "通常のカボチャ10個を";
		mes "交換しています。";
		next;
		mes "[修道士]";
		mes "あなたもいかがですか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[修道士]";
			mes "そうですか。残念です。";
			mes "とってもおいしいんですよ。";
			close;
		}
		if(countitem(535)<10) {
			mes "[修道士]";
			mes "カボチャを持って";
			mes "ないじゃないですか。";
			mes "10個と交換です。";
			close;
		}
		mes "- 魔法のカボチャを手に入れた -";
		delitem 535,10;
		set PUMP_EVE,1;
		next;
		mes "[修道士]";
		mes "ありがとう。";
		mes "魔法のカボチャは";
		mes "煮るだけでとってもおいしいですが";
		mes "変わった食べ方もあるようです。";
		next;
		mes "[修道士]";
		mes "詳しく知りたければ";
		mes "ルティエのタシンチェおばさんに";
		mes "聞いてみてください。";
		close;
	}
	mes "[修道士]";
	mes "魔法のカボチャは";
	mes "一度に一つの交換と";
	mes "させていただいてます。";
	mes "一度食べて";
	mes "そのおいしさを感じてから";
	mes "またきてください。";
	next;
	mes "[修道士]";
	mes "カボチャ料理について";
	mes "詳しく知りたければ";
	mes "ルティエのタシンチェおばさんに";
	mes "聞いてみてくださいね。";
	close;
}

prt_monk.gat,227,162,4	script	修行僧	753,{
	if(PUMP_EVE != 1) {
		mes "[修行僧]";
		mes "おう、あんたもう";
		mes "魔法のかぼちゃは貰ったかい？";
		mes "俺達はこの畑で育った栄養満点の";
		mes "カボチャを食って";
		mes "ここまで強くなったんだ！";
		next;
		mes "[修行僧]";
		mes "特に魔法のカボチャは格別だ。";
		mes "まだだったら一度食べてみるといいぜ。";
		close;
	}
	mes "[修行僧]";
	mes "おっあんたも魔法のカボチャを";
	mes "もらったか。";
	mes "ふむ、実は料理の上手いおばさんを";
	mes "知ってるんだが、そのカボチャも";
	mes "持って行けば料理してくれるかも";
	mes "しれん。行ってみるかい？";
	next;
	if(select("是非！","いや、結構です")==2) {
		mes "[修行僧]";
		mes "遠慮深いやつだ。";
		close;
	}
	mes "[修行僧]";
	mes "よしきた！";
	mes "近くまで連れて行ってやろう。";
	close2;
	warp "xmas_fild01.gat",150,150;
	end;
}

gef_fild00.gat,73,209,4	script	聖なるピエロ	715,{
	if(PUMP_EVE != 2) {
		if(countitem(536)<1 && countitem(530)<1) {
			mes "[聖なるピエロ]";
			mes "あああ・・・。";
			mes "僕の大好きなお菓子が";
			mes "無くなっちゃったよ。";
			mes "お菓子が食べたいなぁ・・・";
			next;
			mes "[聖なるピエロ]";
			mes "ねぇ、もしよかったら";
			mes "何かお菓子を持ってきてくれない？";
			next;
			switch (select("いいよ","いやだね","ごめんね、忙しくて…")) {
			case 1:
				mes "[聖なるピエロ]";
				mes "本当に!?";
				mes "ありがと～";
				mes "じゃ、待ってるよ！";
				close2;
				warp "xmas_dun01.gat",205,17;
				end;
			case 2:
				mes "[聖なるピエロ]";
				mes "む！";
				mes "ケチ！";
				close2;
				warp "prt_monk.gat",182,236;
				end;
			case 3:
				mes "[聖なるピエロ]";
				mes "そっか……";
				mes "まっ、しょうがないね……";
				close;
			}
		}
		mes "[聖なるピエロ]";
		mes "あっ！";
		mes "君の持っているお菓子を";
		mes "僕にくれないかな？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[聖なるピエロ]";
			mes "ちぇっ！";
			close;
		}
		//両方持ってたら両方とも取られる？
		if(countitem(536))
			delitem 536,1;
		if(countitem(530))
			delitem 530,1;
		mes "[聖なるピエロ]";
		mes "ペロペロ、ペロペロ";
		mes "ありがとう。";
		next;
		if(select("どういたしまして","お礼は？")==1) {
			mes "[聖なるピエロ]";
			mes "ペロペロ、ペロペロ";
			close;
		}
		mes "[聖なるピエロ]";
		mes "キャンディーくらいで";
		mes "ケチケチすんなよ！";
		mes "もっと変わったアメを";
		mes "持ってきなっ！";
		mes "ベロベロベ～";
		close2;
		warp "prt_monk.gat",95,212;
		end;
	}
	mes "[聖なるピエロ]";
	mes "あー！";
	mes "パンプキンキャンディー！！";
	mes "頂戴！";
	mes "それ食べさせてー！！";
	next;
	if(select("しょうがないなぁ","いやだね")==2) {
		mes "[聖なるピエロ]";
		mes "・・・";
		mes "ふん、じゃぁ勝手に";
		mes "もらうよっ！";
		mes "ベロベロベローン！";
		next;
		mes "- パンプキンキャンディー -";
		mes "- をとられた -";
		set PUMP_EVE,0;
		next;
		mes "[聖なるピエロ]";
		mes "あっちに行っちゃえ！";
		close2;
		warp "prt_monk.gat",95,212;
		end;
	}
	mes "[聖なるピエロ]";
	mes "やったー！！";
	mes "じゃあ、お礼に";
	mes "魔法をプレゼントだ。";
	mes "Trick or Treat？";
	next;
	if(select("Trick","Treat")==1) {	//Trick選択
		set PUMP_EVE,0;
		switch(rand(11)) {
		case 0:		//ゲフェンD(B4)
			mes "[聖なるピエロ]";
			mes "いってこーい！";
			warp "gef_dun03.gat",138,119;
			break;
		case 1:		//GH地下水路
			mes "[聖なるピエロ]";
			mes "下水が詰まってるらしいから";
			mes "掃除して来て～";
			warp "gl_sew04.gat",293,6;
			break;
		case 2:		//GH最下層地下洞窟
			mes "[聖なるピエロ]";
			mes "これより探検隊を派遣します！";
			warp "gl_dun02.gat",138,72;
			break;
		case 3:		//タートルアイランド久陽宮
			mes "[聖なるピエロ]";
			mes "君もこれで王様どぁぁぁぁ！！！";
			warp "tur_dun04.gat",100,111;
			break;
		case 4:		//イズルード海底神殿
			mes "[聖なるピエロ]";
			mes "本日開店！魚観覧所！！";
			warp "iz_dun04.gat",130,227;
			break;
		case 5:		//時計塔地上
			mes "[聖なるピエロ]";
			mes "今日から君もここの店長だ！";
			warp "c_tower4.gat",119,179;
			break;
		case 6:		//沈没船2F
			mes "[聖なるピエロ]";
			mes "船長ぉぉぉぉ！！！";
			warp "tresure02.gat",100,164;
			break;
		case 7:		//カボチャ部屋
			mes "[聖なるピエロ]";
			mes "お一人さまご案内～";
			warp "force_2-1.gat",100,100;
			break;
		case 8:		//ノーグロード2F
			mes "[聖なるピエロ]";
			mes "君の人生常に崖っぷち！";
			warp "mag_dun02.gat",212,169;
			break;
		case 9:		//PvPイベントホール
			mes "[聖なるピエロ]";
			mes "今日の運勢：待ち人来たらず。";
			warp "pvp_2vs2.gat",19,39;
			break;
		case 10:	//ジュノー
			mes "[聖なるピエロ]";
			mes "よし！着いたらポーズを決めるんだ！";
			warp "yuno.gat",210,310;
			break;
		}
		end;
	}
	else {	//確率は500回試行した確率(某サイトより参考)
		set PUMP_EVE,0;
		set '@rand,rand(100);
		if('@rand >= 0 && '@rand < 10) 	 getitem 536,1;		//アイスクリーム(12.4%)
		if('@rand >= 10 && '@rand < 20)  getitem 2262,1;		//ピエロの鼻(10.6%)
		if('@rand >= 20 && '@rand < 29)  getitem 715,2;		//イエロジェムストーン(9.6%)
		if('@rand >= 29 && '@rand < 38)  getitem 7126,1;		//でっかいゼロピー(9.4%)
		if('@rand >= 38 && '@rand < 47)  getitem 716,2;		//レッドジェムストーン(8.6%)
		if('@rand >= 47 && '@rand < 55)  getitem 717,2;		//ブルージェムストーン(8%)
		if('@rand >= 55 && '@rand < 63)  getitem 2209,1;		//リボン(8%)
		if('@rand >= 63 && '@rand < 69)  getitem 911,1;		//セルー(5.8%)
		if('@rand >= 69 && '@rand < 75)  getitem 713,1;		//空き瓶(5.4%)
		if('@rand >= 75 && '@rand < 81)  getitem 1093,1;		//空のポーション瓶(4.8%)
		if('@rand >= 81 && '@rand < 85)  getitem 1092,1;		//空の試験管(3.8%)
		if('@rand >= 85 && '@rand < 89)  getitem 909,1;		//ゼロピー(3.6%)
		if('@rand >= 89 && '@rand < 92)  getitem 741,1;		//ポリン人形(3.4%)
		if('@rand >= 92 && '@rand < 94)  getitem 546,1;		//イエロースリムポーション(2.2%)
		if('@rand >= 94 && '@rand < 96)  getitem 547,1;		//ホワイトスリムポーション(1.4%)
		if('@rand >= 96 && '@rand < 98)  getitem 545,1;		//レッドスリムポーション(1.2%)
		if('@rand >= 98 && '@rand < 100) getitem 644,1;		//プレゼントボックス(1.6%)
		mes "[聖なるピエロ]";
		mes "君にこれをあげよう！";
		next;
		mes "[聖なるピエロ]";
		mes "どう？";
		mes "ボクの魔法？";
		mes "気に入ってくれた？";
		mes "ベロベロ～ン！";
		close;
	}
}
