//====================================================================
//Ragnarok Online Rogue jobchange script
//
//　■ CHANGE_RG
//	1	面接試験
//	2	面接試験クリア
//	3	アイテム収集１
//	4	アイテム収集２
//	5	アイテム収集３
//	6	アイテム収集４
//	7	アイテム収集クリア
//	8	アントニオJr.
//	9	ヘルマンソンJr.		//未実装
//	10	アラガムJr.		//未実装
//	11	ホルグレンJr.		//未実装
//	12	アントニオJr.再試験
//	13	ヘルマンソンJr.再試験	//未実装
//	14	アラガムJr.再試験	//未実装
//	15	ホルグレンJr.再試験	//未実装
//	16	最終試験クリア
//====================================================================

//==========================================
// 試験申請および転職
//------------------------------------------

in_rogue.gat,363,122,4	script	ローグギルド員	747,{
	if(Upper == UPPER_HIGH) {
		mes "[マキ]";
		mes "あら？あんた、";
		mes "昔に私と会ったこと無いかい？";
		next;
		mes "[マキ]";
		mes "……";
		mes "そうかい、見間違えたみたいだね。";
		mes "変だね……";
		next;
		mes "[マキ]";
		mes "あたいが間違えるなんてめったに";
		mes "無いんだけどね……";
		mes "ま、気をつけて帰りな。";
		close;
	}
	if(Job == Job_Rogue) {
		mes "[マキ]";
		mes "おや、久しぶり～";
		mes "ギルドからの仕事は今は無いよ。";
		next;
		mes "[マキ]";
		mes "元気でやってるかい？";
		mes "何かあったら言ってくれよ。";
		next;
		mes "[マキ]";
		mes "ああそうそう、";
		mes "上納忘れないでよ～？";
		mes "ふふっ";
		close;
	}
	if(Job != Job_Thief) {
		mes "[マキ]";
		mes "ん？";
		mes "何の用？";
		mes "見る物なんてここにはないよ～";
		close;
	}
	if(JobLevel < 40) {
		mes "[マキ]";
		mes "ローグはシーフのJobLvが";
		mes "40以上のヤツだけがなれるんだ。";
		mes "あんたのようなひよっこには";
		mes "まだ早いよ。";
		mes "もう少し鍛えておいで。";
		close;
	}
	if(SkillPoint) {
		mes "[ローグギルド員]";
		mes "スキルポイントが残っていたら";
		mes "転職できないねぇ。";
		mes "全部消費してらっしゃい。";
		close;
	}
	switch(CHANGE_RG) {
	case 0:
		mes "[ローグギルド員]";
		mes "なに？こんなところまで";
		mes "何の用事で来たのさ。";
		mes "ローグになりたいっていう" +(Sex? "兄": "姉")+ "さんか。";
		next;
		mes "[ローグギルド員]";
		mes "会えてうれしいわ。";
		mes "あたいはローグギルドの";
		mes "「マキ」ってんだ。";
		mes "あんた名前は？";
		next;
		mes "[マキ]";
		mes "うん？" +strcharinfo(0)+ "だと？";
		mes "いい名前じゃないか。";
		next;
		mes "[マキ]";
		mes "ところで、またなんでこんな";
		mes "ところに来たのかい？";
		mes "さっきから正直に答えてくれてる";
		mes "からイイヤツみたいだけど。";
		next;
		mes "[マキ]";
		mes "でも、他でもそんなふうに";
		mes "なんでもかんでも教えてやっちゃ";
		mes "あぶないよ。";
		mes "ローグギルドの外では身の安全に";
		mes "注意しな。";
		next;
		mes "[マキ]";
		mes "さて、あんたみどころありそうだし";
		mes "あたいらんとこに入るテストでも";
		mes "受けてもらおうか。";
		next;
		mes "[マキ]";
		mes "あん、そんなに緊張しないで。";
		mes "手続き取ってる間にいくつか";
		mes "試すだけだからさ。";
		set CHANGE_RG,1;
		break;
	case 1:
		mes "[マキ]";
		mes "また来たね。";
		mes "緊張しないでもう一度やってみて。";
		mes "さぁ、はじめるよ。";
		break;
	case 2:
		mes "[マキ]";
		mes "「スミスラト」のとこに行きな。";
		mes "奴のテストはちょっと厄介だ……";
		mes "集金担当だからさ……";
		mes "性格がしつっこくてね……(ひそひそ)";
		next;
		mes "[マキ]";
		mes "間違えると大変だよ。";
		mes "とにかくがんばって！";
		close;
	default:	//3～15のとき
		mes "[マキ]";
		mes "がんばって！";
		mes "(何か機嫌がいい)";
		next;
		mes "[マキ]";
		mes "フフ……これでまた儲けやすく……";
		mes "あ……ああなんでもないよ！";
		mes "アハハ……アハハ……ハ……";
		close;
	case 16:
		set '@itemid,(JobLevel >= 50)? 1220: 1219;
		mes "[マキ]";
		mes "おっがんばったじゃないか！";
		mes "苦労しただろう～";
		mes "じゃ転職させてやるよ。";
		next;
		unequip;
		jobchange Job_Rogue;
		set CHANGE_RG,0;
		mes "[マキ]";
		mes "おめでとう！";
		mes "がんばったねぇ";
		mes "これからは自由に生きるんだよ！";
		mes "ふふ……";
		next;
		mes "[マキ]";
		mes "あ、でも一つ言っておくよ。";
		mes "自分の自由を大事に思うなら、";
		mes "人の自由も尊重してやらなきゃ";
		mes "ならないってことよ。";
		mes "それじゃ～ね～～";
		getitem '@itemid,1;
		close;
	}
	//面接ここから
	next;
	if(select("わかった","ちょっとまってくれ")==2) {
		mes "[マキ]";
		mes "そう、じゃ準備してらっしゃい。";
		close;
	}
	mes "[マキ]";
	mes "うん、それじゃはじめましょ。";
	next;
	mes "[マキ]";
	mes "これから問題を出すから";
	mes "よく聴いて正しいものを選んでね。";
	next;
	switch(rand(3)) {
	case 0:
		mes "[マキ]";
		mes "1.";
		mes "ローグのスキル「トンネルドライブ」";
		mes "を覚えるために必要なスキルは？";
		next;
		if(select("ハイディング","スティール","回避率向上","バッシュ")==1)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "2.";
		mes "ローグのスキル";
		mes "「コンパルションディスカウント」";
		mes "の割引率は、商人の「ディスカウント」";
		mes "Lv10より何%高いか。";
		next;
		if(select("3 %","2 %","1 %","0 %")==3)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "3.";
		mes "スキル「スティールコイン」の能力は？";
		next;
		if(select("プレイヤーからアイテムを盗む","モンスターからアイテムを盗む","モンスターからZenyを盗む","プレイヤーからZenyを盗む")==3)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "4.";
		mes "シーフ系で習得できるスキルで、";
		mes "素早く後ろに後退するスキルは";
		mes "何というか。";
		next;
		if(select("バックダッシュ","緊急回避","バックスタブ","バックステップ")==4)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "5.";
		mes "スキル「ストリップヘルム」Lv5";
		mes "を習得することで新たに出現する";
		mes "スキルは？";
		next;
		if(select("インベナム","トンネルドライブ","ベノムスプラッシャー","ストリップシールド")==4)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "6.";
		mes "次の中で、周囲の目を盗んで";
		mes "移動するスキルは？";
		next;
		if(select("ハイディング","バックステップ","トンネルドライブ","砂まき")==3)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "7.";
		mes "次の中で、物理攻撃の命中率を";
		mes "上げてくれるカードは？";
		next;
		if(select("アンドレ","ファミリアーカード","マミーカード","マリナカード")==3)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "8.";
		mes "次の中で、バドンカード";
		mes "(火属性に20%追加ダメージ)";
		mes "を刺した武器で攻撃するのに";
		mes "適しているモンスターは？";
		next;
		if(select("バドン","デビルチ","エルダーウィロー","バフォメット")==3)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "9.";
		mes "短剣でダブルアタックが";
		mes "発動した場合のSP消費量は？";
		next;
		if(select("15","パッシブなので 0","パッシブなので 10で固定","54")==2)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "10.";
		mes "イズルードダンジョンで効果を";
		mes "発揮する武器は次のうちどれか。";
		next;
		if(select("ウインド マインゴーシュ","アイス マインゴーシュ","アース マインゴーシュ","ファイア マインゴーシュ")==1)
			set '@point,'@point+10;
		break;
	case 1:
		mes "[マキ]";
		mes "1.";
		mes "スロットの多いグラディウスを落とす";
		mes "モンスターは次のうちどれか。";
		next;
		if(select("盗蟲","ペコペコ","デザートウルフ","コボルド")==4)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "2.";
		mes "ソケットのあるマインゴーシュは";
		mes "どのモンスターから得られるか。";
		next;
		if(select("ホーネット","デザートウルフ","マリオネット","ミスト")==1)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "3.";
		mes "ポーションを製造することができる";
		mes "職業は？";
		next;
		if(select("商人","アルケミスト","ブラックスミス","プリースト")==2)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "4.";
		mes "次の中でローグが使うことが";
		mes "できない武器は？";
		next;
		if(select("角弓","クロスボウ","グラディウス","カタール")==4)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "5.";
		mes "ホードの属性は何か。";
		next;
		if(select("水属性","火属性","風属性","地属性")==4)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "6.";
		mes "次の中で、ペットにすることが";
		mes "できないモンスターは？";
		next;
		if(select("ポポリン","クリーミー","オークウォリアー","ポイズンスポア")==2)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "7.";
		mes "火属性短剣が一番効果的な";
		mes "モンスターを選びなさい。";
		next;
		if(select("短剣ゴブリン","メイスゴブリン","フレイルゴブリン","ハンマーゴブリン")==4)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "8.";
		mes "次の中で、ギルド砦の無い街は？";
		next;
		if(select("プロンテラ","アルデバラン","アルベルタ","フェイヨン")==3)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "9.";
		mes "次の中で、青ハーブを落とす";
		mes "モンスターを選べ。";
		next;
		if(select("緑色草","黄色草","青い草","輝く草")==3)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "10.";
		mes "次の中で、アンデッドではない";
		mes "モンスターを選べ。";
		next;
		if(select("ゾンビ","メガロドン","ファミリアー","カーリッツバーグ")==3)
			set '@point,'@point+10;
		break;
	case 2:
		mes "[マキ]";
		mes "1.";
		mes "シーフの「回避率向上」スキル";
		mes "をマスターした時上昇するFLEEは？";
		next;
		if(select("30","40","160","20")==1)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "2.";
		mes "次の中で、ハイディングや";
		mes "クローキングを見破るモンスターは？";
		next;
		if(select("ワームテール","アルゴス","マミー","ソルジャースケルトン")==2)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "3.";
		mes "次の中で、ローグギルドがある";
		mes "所の地名を答えろ。";
		next;
		if(select("コモド","ココモビーチ","ファロス燈台島","モロク")==3)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "4.";
		mes "シーフギルドがある街は？";
		next;
		if(select("コモド","ルティエ","アルベルタ","モロク")==4)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "5.";
		mes "DEXと関係ないカードは？";
		next;
		if(select("ロッカーカード","マミーカード","ゼロムカード","ドロップスカード")==2)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "6.";
		mes "ローグの特徴を答えろ。";
		next;
		if(select("すぐれた身のこなし","すぐれた洞察力","すぐれたずうずうしさ","すぐれた攻撃力"))	//どれも正解
			set '@point,'@point+10;
		mes "[マキ]";
		mes "7.";
		mes "シーフからローグになるための";
		mes "JobLv最低値はいくつか。";
		next;
		if(select("30","41","40","50")==3)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "8.";
		mes "髪を染めるにはどこに行けば良いか。";
		next;
		if(select("モロク 7時方向建物の内","プロンテラ 7時方向建物の内","モロク 5時方向建物の内","プロンテラ 1時方向建物の内")==2)
			set '@point,'@point+10;
		mes "[マキ]";
		mes "9.";
		mes "ノービスがシーフになる場合";
		mes "必要になるきのこの名前は？";
		next;
		if(select("紅の毛ベトベトキノコ","赤毛ベトベトキノコ","紅の毛網キノコ","紅シイタケ")) {	//正解が2つなので特殊処理
			if(@menu == 1 || @menu == 3)
				set '@point,'@point+10;
		}
		mes "[マキ]";
		mes "10.";
		mes "比較的ローグと関係の無いカードは？";
		next;
		if(select("ウィスパーカード","エルダーウィローカード","ゼロムカード","マーターカード")==2)
			set '@point,'@point+10;
		break;
	}
	mes "[マキ]";
	mes "ふぅ……";
	mes "おつかれさん。";
	next;
	mes "[マキ]";
	mes "ん……点数は……";
	mes '@point+ "点か。";
	if('@point < 90) {
		mes "だめだ。";
		mes "そんなんじゃローグとして";
		mes "やっていけないよ。";
		mes "もう少し情報を集めてから来な。";
		close;
	}
	mes "へ～";
	mes "なかなかみどころが";
	mes "あるじゃないー。";
	next;
	mes "[マキ]";
	mes "さて、これからが本番よ。";
	mes "「スミスラト」が次のテストの";
	mes "担当だ。";
	mes "気をつけな、奴は集金担当だから";
	mes "かなり気難しいよ……";
	set CHANGE_RG,2;
	close;
}


//==========================================
// 一次試験（金品強奪）
//------------------------------------------

in_rogue.gat,376,23,2	script	スミスラト	57,{
	switch(CHANGE_RG) {
	case 0:
	case 1:
		mes "[スミスラト]";
		mes "ひぃふぅみぃ……………";
		mes "取引先が……";
		mes "モロク……ゲフェン……コモド……";
		next;
		mes "[スミスラト]";
		mes "頭が痛い……";
		next;
		mes "[スミスラト]";
		mes "うん？お前はなんだ？";
		mes "転職したいなら他のヤツに言え！";
		next;
		mes "[スミスラト]";
		mes "……ったく……";
		close;
	case 2:
		mes "[スミスラト]";
		mes "ローグギルドに来たことを";
		mes "歓迎する。";
		mes "今から、ローグになるための";
		mes "基本的なテストをやる。";
		next;
		mes "[スミスラト]";
		mes "ただ、テストの前に用意して";
		mes "もらいたいものがある。";
		next;
		mes "[スミスラト]";
		mes "授業料があるから少し金を";
		mes "用意するんだ。";
		mes "オレ達ローグギルドも資本金から";
		mes "仕事を始めて収益を出さなければ";
		mes "ならない。";
		mes "では次の物を持って来い。";
		next;
		mes "[スミスラト]";
		mes "まず、ギルド登録料^FF333310000Zeny^000000と";
		switch(rand(4)) {
			case 0:
				set CHANGE_RG,3;
				mes "スケルボーン 10個";
				mes "青ハーブ 6個";
				next;
				mes "[スミスラト]";
				mes "亡者の爪 10個";
				mes "亡者の牙 10個";
				break;
			case 1:
				set CHANGE_RG,4;
				mes "緑ハーブ 10個";
				mes "かにのこうら 10個";
				next;
				mes "[スミスラト]";
				mes "蛇の鱗 10個";
				mes "ガレット 10個";
				break;
			case 2:
				set CHANGE_RG,5;
				mes "黄ハーブ 10個";
				mes "かたい皮 10個";
				next;
				mes "[スミスラト]";
				mes "バッタの足 10個";
				mes "くまの足の裏 10個";
				break;
			case 4:		//台詞未調査
				set CHANGE_RG,6;
				mes "さなぎの皮 5個";
				mes "空きビン 5個";
				mes "鉄鉱石 5個";
				mes "岩の心臓 5個";
				mes "赤ハーブ 5個";
				next;
				mes "[スミスラト]";
				mes "獣の皮 5個";
				mes "イエロージェムストーン 5個";
				mes "こうもりの牙 5個";
				mes "サソリの尻尾 5個";
				mes "サルのしっぽ 5個";
				mes "化け物のエサ 5個";
				mes "それから……";
				next;
				mes "[スミスラト]";
				mes "綿毛 5個";
				mes "クローバー 5個";
				mes "鳥の羽毛 5個";
				mes "鳥のつめ 5個";
				mes "かえるの卵 5個";
				mes "タヌキ木の葉 5個";
				break;
		}
		mes "うん……あと……";
		next;
		mes "[スミスラト]";
		mes "これくらいにしておこう。";
		if(CHANGE_RG == 6) {	//台詞未調査
			mes "ん？数が多いって？";
			mes "…気にするな。";
		}
		mes "では全部揃えてからまた来い。";
		close;
	case 3:
	case 4:
	case 5:
	case 6:
		switch(CHANGE_RG) {
			case 3:
				setarray '@need,932,510,957,958;
				setarray '@amount,10,6,10,10;
				break;
			case 4:
				setarray '@need,511,964,926,910;
				cleararray '@amount,10,4;
				break;
			case 5:
				setarray '@need,508,935,940,948;
				cleararray '@amount,10,4;
				break;
			case 6:
				setarray '@need,915,713,1002,953,507,919,715,913,904,942,528,914,705,916,917,908,845;
				cleararray '@amount,5,17;
				break;
		}
		for(set '@i,0; '@i<getarraysize('@need); set '@i,'@i+1) {
			if(countitem('@need['@i]) < '@amount['@i] || Zeny < 10000)
				break;
		}
		if('@i < getarraysize('@need)) {
			mes "[スミスラト]";
			mes "ん……足りない物がある。";
			mes "何を頼んだかもう一度言う。";
			next;
			mes "[スミスラト]";
			mes "ギルド登録料^FF333310000Zeny^000000";
			next;
			mes "[スミスラト]";
			if(CHANGE_RG < 6) {
				for(set '@i,0; '@i<4; set '@i,'@i+1)
					mes getitemname('@need['@i])+ " " +'@amount['@i]+ "個";
			}
			else {
				mes "さなぎの皮 5個";
				mes "空きビン 5個";
				mes "鉄鉱石 5個";
				mes "岩の心臓 5個";
				mes "赤ハーブ 5個";
				next;
				mes "獣の皮 5個";
				mes "イエロージェムストーン 5個";
				mes "こうもりの牙 5個";
				mes "サソリの尻尾 5個";
				mes "サルのしっぽ 5個";
				mes "化け物のエサ 5個";
				next;
				mes "綿毛 5個";
				mes "クローバー 5個";
				mes "鳥の羽毛 5個";
				mes "鳥のつめ 5個";
				mes "かえるの卵 5個";
				mes "タヌキ木の葉 5個";
			}
			mes "だ。それでは待っている。";
			close;
		}
		mes "[スミスラト]";
		mes "まず、ギルド登録料^FF333310000Zeny^000000と";
		set Zeny,Zeny-10000;
		for(set '@i,0; '@i<getarraysize('@need); set '@i,'@i+1)
			delitem '@need['@i],'@amount['@i];
		switch(CHANGE_RG) {
			case 3:
				mes "スケルボーン 10個";
				mes "青ハーブ 6個";
				mes "よしよし……";
				next;
				mes "亡者の爪 10個";
				mes "亡者の牙 10個";
				mes "ふむ……完璧だ。";
				break;
			case 4:
				mes "緑ハーブ 10個";
				mes "かにのこうら 10個";
				next;
				mes "蛇の鱗 10個";
				mes "ガレット 10個";
				mes "よし、全部あるな。";
				break;
			case 5:
				mes "黄ハーブ 10個";
				mes "かたい皮 10個";
				next;
				mes "バッタの足 10個";
				mes "くまの足の裏 10個";
				mes "よし、全部あるな。";
				break;
			case 6:
				mes "さなぎの皮 5個";
				mes "空きビン 5個";
				mes "鉄鉱石 5個";
				mes "岩の心臓 5個";
				mes "赤ハーブ 5個";
				next;
				mes "獣の皮 5個";
				mes "イエロージェムストーン 5個";
				mes "こうもりの牙 5個";
				mes "サソリの尻尾 5個";
				mes "サルのしっぽ 5個";
				mes "化け物のエサ 5個";
				next;
				mes "綿毛 5個";
				mes "クローバー 5個";
				mes "鳥の羽毛 5個";
				mes "鳥のつめ 5個";
				mes "かえるの卵 5個";
				mes "タヌキ木の葉 5個";
				mes "……";
				//台詞未調査
				next;
				mes "[スミスラト]";
				mes "よくこれだけの物を";
				mes "集めて来られたな。";
				mes "これは褒美だ。とっておきなさい。";
				getitem 1097,1;
				break;
		}
		set CHANGE_RG,7;
		next;
		mes "[スミスラト]";
		mes "よし、ちょっと準備するから";
		mes "待っていろ。";
		mes "また話しかけてくれ。";
		mes "次のテストは……と……";
		close;
	case 7:
		mes "[スミスラト]";
		mes "次のテストの担当は……";
		mes "誰がいいか……";
		next;
		mes "[スミスラト]";
		mes "ああ……ヤツがいたな。";
		next;
		switch(rand(1)) {
			case 0:		//アントニオJr
				set CHANGE_RG,8;
				mes "[スミスラト]";
				mes "アントニオJr.がいい。";
				mes "アントニオさんの息子だ。";
				mes "もしや知っているか？";
				mes "親父さんが何の失敗をしたか";
				mes "知らないが、なんでも命を狙われて";
				mes "いるらしい……";
				next;
				mes "[スミスラト]";
				mes "東方のフェイヨン出身だが";
				mes "ココモビーチの空き家を使って";
				mes "暮らしている。";
				mes "たまに外で騒ぐヤツが居ると";
				mes "出て行って暴れるらしい……";
				next;
				mes "[スミスラト]";
				mes "神経が研ぎ澄まされていて";
				mes "近づくヤツには容赦なくナイフを";
				mes "投げるらしい……";
				mes "オレたちのギルドマスターも";
				mes "辛うじて説得に成功して";
				mes "ローグギルドに入れたらしい。";
				next;
				mes "[スミスラト]";
				mes "そんなヤツだが、腕前は良くて";
				mes "仕事は早い。特に足技が";
				mes "得意だったな……";
				next;
				mes "[スミスラト]";
				mes "また、賭博が好きだから";
				mes "その話で気に入られれば";
				mes "色々教えてもらえると思う。";
				next;
				mes "[スミスラト]";
				mes "あ、一応ヤツに近づく合言葉を";
				mes "教えておく。";
				mes "^3333FFアントニオは精錬品を壊すのが^000000";
				mes "^3333FF好きではない^000000";
				mes "だ。気をつけろ。";
				close;
			case 1:		//ヘルマンソンJr
				set CHANGE_RG,9;
				//未調査
				close;
			case 2:		//アラガムJr
				set CHANGE_RG,10;
				//未調査
				close;
			case 3:		//ホルグレンJr
				set CHANGE_RG,11;
				//未調査
				close;
		}
	case 8:
		mes "[スミスラト]";
		mes "なんだ、場所でも忘れたか？";
		mes "今度はしっかりメモしておくんだ。";
		next;
		mes "[スミスラト]";
		mes "ここからコモドの方の砂浜、";
		mes "ココモビーチにある建物。";
		mes "アントニオJr.に会え。";
		mes "合言葉は";
		mes "^3333FFアントニオは精錬品を壊すのが^000000";
		mes "^3333FF好きではない^000000";
		close;
	case 9:
		//未調査
		close;
	case 10:
		//未調査
		close;
	case 11:
		//未調査
		close;
	case 12:
		mes "[スミスラト]";
		mes "ここにはもう用は無いだろう？";
		close;
	}
}


//==========================================
// 二次試験（ローグ訪問）
//------------------------------------------

cmd_fild04.gat,304,180,0	script	roguewarp0401	45,1,1,{
	mes "[　]";
	mes "誰だ!?";
	mes "ここに何のようだ！";
	next;
	for(set '@i,0; '@i<4; set '@i,'@i+1) {
		switch('@i) {
			case 0: setarray '@word$,"アンティオニオは","アラガムは","アントニオは","ホルグレンは"; 			break;
			case 1: setarray '@word$,"精錬物品を","精錬品を","精錬物品は","精錬品"; 					break;
			case 2: setarray '@word$,"壊すことを","壊すのが","直すことを","直すのを"; 					break;
			case 3: setarray '@word$,"好むようだ","好きかもしれない","好きではない","好きである","好きだ","好まない"; 	break;
		}
		set '@ret['@i],select('@word$[0],'@word$[1],'@word$[2],'@word$[3],'@word$[4],'@word$[5]);
		if('@i == 0)
			mes "["+strcharinfo(0)+"]";
		mes '@word$['@ret['@i]-1];	//選択した項目をメッセージとして出す
	}
	next;
	if('@ret[0] == 3 && '@ret[1] == 2 && '@ret[2] == 2 && '@ret[3] == 3) {
		mes "--カチャリ--";
		mes "カギが開いた。";
		close2;
		warp "in_rogue.gat",164,106;
		end;
	}
	mes "[　]";
	mes "あっちにいけ！";
	close;
}

cmd_fild07.gat,355,286,0	warp	roguewarp0402	1,1,in_rogue.gat,247,126

cmd_fild09.gat,106,195,0	script	roguewarp0403	45,1,1,{
	mes "[　]";
	mes "誰だ!?";
	mes "ここに何のようだ！";
	next;
	for(set '@i,0; '@i<4; set '@i,'@i+1) {
		switch('@i) {
			case 0: setarray '@word$,"うちの父は","アラガムは","アラゴンは","レゴールラスは"; 	break;
			case 1: setarray '@word$,"精錬物品を","精錬武器を","精錬用品を","精錬品物を"; 		break;
			case 2: setarray '@word$,"直して","横領して","ぶん取って","叩いて","抜き取って"; 	break;
			case 3: setarray '@word$,"いない","座った","抱いた","なかった",""; 			break;
		}
		set '@ret['@i],select('@word$[0],'@word$[1],'@word$[2],'@word$[3],'@word$[4]);
		if('@i == 0)
			mes "["+strcharinfo(0)+"]";
		mes '@word$['@ret['@i]-1];	//選択した項目をメッセージとして出す
	}
	next;
	if('@ret[0] == 2 && '@ret[1] == 3 && '@ret[2] == 2 && '@ret[3] == 1) {
		mes "--カチャリ--";
		mes "カギが開いた。";
		close2;
		warp "in_rogue.gat",244,25;
		end;
	}
	mes "[　]";
	mes "あっちにいけ！";
	close;
}

cmd_fild09.gat,335,143,0	script	roguewarp0404	45,1,1,{
	mes "[　]";
	mes "誰だ!?";
	mes "ここに何のようだ！";
	next;
	for(set '@i,0; '@i<4; set '@i,'@i+1) {
		switch('@i) {
			case 0: setarray '@word$,"うちの父は","アラガムは","アラゴンは","レゴールラスは"; 	break;
			case 1: setarray '@word$,"精錬物品を","精錬武器を","精錬用品を","精錬品物を"; 		break;
			case 2: setarray '@word$,"修理して","精錬して","壊して","盗んで","横領して"; 		break;
			case 3: setarray '@word$,"いない","座った","抱いた","なかった",""; 			break;
		}
		set '@ret['@i],select('@word$[0],'@word$[1],'@word$[2],'@word$[3],'@word$[4]);
		if('@i == 0)
			mes "["+strcharinfo(0)+"]";
		mes '@word$['@ret['@i]-1];	//選択した項目をメッセージとして出す
	}
	next;
	if('@ret[0] == 1 && '@ret[1] == 3 && '@ret[2] == 5 && '@ret[3] == 1) {
		mes "--カチャリ--";
		mes "カギが開いた。";
		close2;
		warp "in_rogue.gat",169,34;
		end;
	}
	mes "[　]";
	mes "あっちにいけ！";
	close;
}

in_rogue.gat,161,103,0		warp	roguewarp0501	1,1,cmd_fild04.gat,302,177
in_rogue.gat,247,122,0		warp	roguewarp0502	1,1,cmd_fild07.gat,349,285
in_rogue.gat,244,21,0		warp	roguewarp0503	1,1,cmd_fild09.gat,106,191
in_rogue.gat,172,34,0		warp	roguewarp0504	1,1,cmd_fild09.gat,341,143

in_rogue.gat,270,130,0		script	roguewarp6001	45,1,1,{
	mes "カギがかかっている。";
	mes "数字を合わせるところが";
	mes "あるようだ。";
	next;
	input '@val;
	if('@val == 3019) {
		mes "[ヘルマンソンJr.]";
		mes "パスワード変えたよ。";
	}
	else if('@val != 0)
		mes "何も起こらない";
	close;
}

//==============================================================
in_rogue.gat,177,109,2	script	アントニオ Jr	88,{
	if(Job == Job_Rogue) {
		mes "[アントニオJr.]";
		mes "ここまで何しに？";
		mes "せっかくだから休んでいきな。";
		close;
	}
	switch(CHANGE_RG) {
	default:
		mes "[アントニオJr.]";
		mes "なに！";
		mes "ローグギルドから来たんじゃ";
		mes "ないのか！";
		mes "だめだ……";
		mes "来るな！……来るな！";
		next;
		mes "[アントニオJr.]";
		mes "お前も我が一族に恨みが";
		mes "ある奴だろう！";
		mes "オレは死ぬわけにはいかない。";
		mes "ここから消えなければ";
		mes "オレがお前を！";
		close;
	case 8:
	case 9:		//アントニオ以外未実装なのでとりあえず9～11も許可しておく
	case 10:
	case 11:
		mes "[アントニオJr.]";
		mes "ローグギルドから来た人か。";
		next;
		mes "[アントニオJr.]";
		mes "ローグになりたくて来たのかい？";
		mes "それなら教えてあげるよ。";
		next;
		mes "[アントニオJr.]";
		mes "オレ達ローグは^3333FF強者は避け";
		mes "弱者にあたる^000000ことが大事だ。";
		mes "よってモンスターと対峙する時も";
		mes "それなりの身のこなし方がある。";
		next;
		mes "[アントニオJr.]";
		mes "モンスターでもやはり";
		mes "弱いものには積極的に攻め";
		mes "強いものからは逃げるというのが";
		mes "原則だ。";
		next;
		mes "[アントニオJr.]";
		mes "さぁ、この原則にしたがって";
		mes "^3333FFローグギルドまで通じている地下水路^000000";
		mes "を通り、無事にたどりついてみろ。";
		mes "お前の持つスキルでうまくこなすんだ。";
		next;
		if(select("出発する","やめる")==2) {
			mes "[アントニオJr.]";
			mes "オレは忙しい。";
			mes "お前の冗談に付き合ってる";
			mes "ヒマはないんだ。";
			close;
		}
		mes "[アントニオJr.]";
		mes "失敗を繰り返して";
		mes "ギルドの足を引っ張るなよ？";
		close2;
		set CHANGE_RG,12;
		warp "in_rogue.gat",15,105;
		end;
	case 12:
	case 13:	//アントニオ以外未実装なのでとりあえず13～15も許可しておく
	case 14:
	case 15:
		mes "[アントニオJr.]";
		mes "うん……残念だ。";
		mes "だけどオレは何も言わない。";
		mes "自分で理解しろ。";
		next;
		if(select("出発する","やめる")==2) {
			mes "[アントニオJr.]";
			mes "オレは忙しい。";
			mes "お前は転職するつもりが";
			mes "あるのか？";
			close;
		}
		mes "[アントニオJr.]";
		mes "では送ろう、健闘を祈る。";
		close2;
		warp "in_rogue.gat",15,105;
		end;
	}
}

//==============================================================
in_rogue.gat,272,135,2	script	ヘルマンソン Jr	85,{
	if(Job == Job_Rogue) {
		//未調査
		close;
	}
	switch(CHANGE_RG) {
	default:
		mes "[ヘルマンソンJr.]";
		mes "うん？何の用だ！";
		mes "ローグギルドから来た奴じゃ";
		mes "ないな！";
		mes "ほら、出て行け……";
		next;
		mes "[ヘルマンソンJr.]";
		mes "お前……お前も我が一族を";
		mes "憎む輩か！";
		mes "まってくれ……死にたくない！";
		mes "どっか行け！";
		mes "行かないとオレがお前を!!!!";
		close;
	case 9:
		//未調査
		set CHANGE_RG,13;
		close;
	case 13:
		//未調査
		close;
	}
}

//==============================================================
in_rogue.gat,244,39,5	script	アラガム Jr	99,{
	if(Job == Job_Rogue) {
		mes "[アラガムJr.]";
		mes "うん？何の用か？";
		mes "せっかくだから休んでいきなさい。";
		close;
	}
	switch(CHANGE_RG) {
	default:
		mes "[アラガムJr.]";
		mes "な……なに！";
		mes "あなたはローグギルドから";
		mes "来た者ではないな！";
		mes "あっちに行け!!";
		next;
		mes "[アラガムJr.]";
		mes "あなたも我が一族に恨みを持つ";
		mes "者か……！";
		mes "私はまだ死ぬわけにいかない。";
		mes "どこかに行かないのならば";
		mes "私があなたを！";
		close;
	case 10:
		//未調査
		set CHANGE_RG,14;
		close;
	case 14:
		//未調査
		close;
	}
}

//==============================================================
in_rogue.gat,160,34,2	script	ホルグレン Jr	85,{
	if(Job == Job_Rogue) {
		mes "[アントニオJr.]";
		mes "よう、何の用だい？";
		mes "せっかくだから休んでいきなよ。";
		close;
	}
	switch(CHANGE_RG) {
	default:
		mes "[ホルグレンJr.]";
		mes "！";
		mes "お前は……なんだ！";
		mes "ローグギルドから来た奴じゃ";
		mes "ないな！";
		next;
		mes "[ホルグレンJr.]";
		mes "ぐおおお！";
		next;
		mes "[ホルグレンJr.]";
		mes "すぐに出て行け！";
		next;
		mes "[ホルグレンJr.]";
		mes "お前もうちの一族に恨みを持つ";
		mes "奴か？";
		mes "くそっオレはここで死ぬわけには";
		mes "いかない。";
		mes "出て行け！さもないと";
		mes "オレがお前を！";
		close;
	case 11:
		//未調査
		set CHANGE_RG,15;
		close;
	case 15:
		//未調査
		close;
	}
}


//==========================================
// 三次試験（帰還）
//------------------------------------------

in_rogue.gat,15,185,0	script	#RG_Test01	139,8,0,{
	if(CHANGE_RG != 12)
		end;
	if(getnpctimer(1,"RG_Timer") == 0)	//タイマーが停止してたら始動
		initnpctimer "RG_Timer";
	monster "in_rogue.gat",13,188,"--ja--",1394,1;
	monster "in_rogue.gat",14,189,"--ja--",1394,1;
	monster "in_rogue.gat",15,190,"--ja--",1394,1;
	monster "in_rogue.gat",16,188,"--ja--",1394,1;
	monster "in_rogue.gat",17,189,"--ja--",1394,1;
	monster "in_rogue.gat",18,190,"--ja--",1394,1;
	end;
}

in_rogue.gat,15,245,0	script	#RG_Test02	139,8,0,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",13,248,"--ja--",1393,1;
	monster "in_rogue.gat",15,248,"--ja--",1393,1;
	monster "in_rogue.gat",17,248,"--ja--",1393,1;
	end;
}

in_rogue.gat,15,333,0	script	#RG_Test03	139,8,0,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",15,336,"--ja--",1394,3;
	end;
}

in_rogue.gat,35,342,0	script	#RG_Test04	139,0,8,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",38,340,"--ja--",1393,1;
	monster "in_rogue.gat",37,342,"--ja--",1893,1;
	monster "in_rogue.gat",39,342,"--ja--",1423,1;
	monster "in_rogue.gat",38,344,"--ja--",1393,1;
	end;
}

in_rogue.gat,57,306,0	script	#RG_Test05	139,4,0,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",59,301,"--ja--",1438,1;
	end;
}

in_rogue.gat,96,333,0	script	#RG_Test06	139,0,4,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",92,325,"--ja--",1438,1;
	end;
}

in_rogue.gat,139,313,0	script	#RG_Test07	139,4,0,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",139,309,"--ja--",1893,1;
	end;
}

in_rogue.gat,135,246,0	script	#RG_Test08	139,0,4,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",140,246,"--ja--",1394,1;
	monster "in_rogue.gat",141,246,"--ja--",1394,1;
	monster "in_rogue.gat",142,246,"--ja--",1394,1;
	monster "in_rogue.gat",148,246,"--ja--",1394,1;
	monster "in_rogue.gat",149,246,"--ja--",1394,1;
	monster "in_rogue.gat",150,246,"--ja--",1394,1;
	end;
}

in_rogue.gat,199,218,0	script	#RG_Test09	139,0,8,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",157,218,"--ja--",1394,10;
	monster "in_rogue.gat",157,218,"--ja--",1893,1;
	monster "in_rogue.gat",157,218,"--ja--",1423,1;
	monster "in_rogue.gat",157,218,"--ja--",1420,1;
	end;
}

in_rogue.gat,86,187,0	script	#RG_Test10	139,0,8,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",88,190,"--ja--",1393,1;
	monster "in_rogue.gat",88,187,"--ja--",1393,1;
	monster "in_rogue.gat",88,184,"--ja--",1393,1;
	end;
}

in_rogue.gat,225,187,0	script	#RG_Test11	139,0,8,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",232,191,"--ja--",1893,1;
	monster "in_rogue.gat",233,190,"--ja--",1893,1;
	monster "in_rogue.gat",234,189,"--ja--",1893,1;
	end;
}

in_rogue.gat,252,320,0	script	#RG_Test12	139,0,8,{
	if(CHANGE_RG != 12)
		end;
	monster "in_rogue.gat",252,319,"--ja--",1393,1;
	monster "in_rogue.gat",252,321,"--ja--",1393,1;
	monster "in_rogue.gat",252,319,"--ja--",1423,1;
	monster "in_rogue.gat",252,321,"--ja--",1423,1;
	monster "in_rogue.gat",257,320,"--ja--",1420,1;
	monster "in_rogue.gat",248,320,"--ja--",1420,1;
	end;
}

//==============================================================
in_rogue.gat,0,0,0	script	RG_Timer	-1,{
	end;
OnTimer30000:
	killmonster "in_rogue.gat","All";
	//試験エリア内に誰も居ないならタイマー止める
	if(getareausers("this",8,98,23,349) + getareausers("this",24,180,241,349) + getareausers("this",242,312,373,327) == 0)
		stopnpctimer;
	else
		initnpctimer;
	end;
}

//==============================================================
in_rogue.gat,370,320,0	script	roguewarp6002	45,1,1,{
	set CHANGE_RG,16;
	warp "in_rogue.gat",378,113;
	end;
}
