//= Auriga Script ==============================================================
// Ragnarok Online Eclage Town Script	by refis
//==============================================================================

//============================================================
// Shop
//------------------------------------------------------------
-	shop	ecl_callshop	-1,519
ecl_in01.gat,65,85,5	script	牛乳商人#ecl	559,{
	callshop "ecl_callshop";
	end;
OnInit:
	waitingroom "おいしい牛乳販売中ニャ！",0;
	end;
}

ecl_in01.gat,66,95,3	script	防具商人ナパラ	436,{
	mes "[防具商人]";
	mes "こんにちは。";
	mes "高級品を厳選して扱う防具屋です。";
	mes "何か必要ですか？";
	next;
	set '@menu,select("力のグローブ[0]","知力のグローブ[0]","敏捷のグローブ[0]","体力のグローブ[0]","器用さのグローブ[0]","幸運のグローブ[0]")-1;
	switch('@menu) {
	case 0:
		mes "[防具商人]";
		mes "^3131FF力のグローブ[0]^000000、";
		mes "ですね。";
		mes "性能は以下です。";
		next;
		mes "[力のグローブ[0]]";
		mes "^3131FFMaxHP+100 ,MaxSP+20^000000";
		mes "^3131FF純粋なStr+10ごとにAtk+1^000000";
		mes "^3131FF純粋なStrが110以上の時、追加で^000000";
		mes "^3131FF物理攻撃で与えるダメージ+1%^000000";
		mes "^3131FFスロット数:0^000000";
		next;
		mes "[力のグローブ[0]]";
		mes "^3131FF系列:アクセサリ^000000";
		mes "^3131FF防御:0^000000";
		mes "^3131FF重量:10^000000";
		mes "^3131FF要求レベル:100^000000";
		mes "^3131FF全ての職業^000000";
		break;
	case 1:
		mes "[防具商人]";
		mes "^3131FF知力のグローブ[0]^000000、";
		mes "ですね。";
		mes "性能は以下です。";
		next;
		mes "[知力のグローブ[0]]";
		mes "^3131FFMaxHP+100 , MaxSP+20^000000";
		mes "^3131FF純粋なInt+10ごとにMatk+1^000000";
		mes "^3131FF純粋なIntが110以上の時^000000";
		mes "^3131FF追加でMatk+1%^000000";
		mes "^3131FFスロット数:0^000000";
		next;
		mes "[知力のグローブ[0]]";
		mes "^3131FF系列:アクセサリ^000000";
		mes "^3131FF防御:0^000000";
		mes "^3131FF重量:10^000000";
		mes "^3131FF要求レベル:100^000000";
		mes "^3131FF全ての職業^000000";
		break;
	case 2:
		mes "[防具商人]";
		mes "^3131FF敏捷のグローブ[0]^000000、";
		mes "ですね。";
		mes "性能は以下です。";
		next;
		mes "[敏捷のグローブ[0]]";
		mes "^3131FFMaxHP+100 , MaxSP+20^000000";
		mes "^3131FF純粋なAgi+10ごとにFlee+1^000000";
		mes "^3131FF純粋なAgiが110以上の時^000000";
		mes "^3131FF追加で完全回避+1^000000";
		mes "^3131FFスロット数:0^000000";
		next;
		mes "[敏捷のグローブ[0]]";
		mes "^3131FF系列:アクセサリ^000000";
		mes "^3131FF防御:0^000000";
		mes "^3131FF重量:10^000000";
		mes "^3131FF要求レベル:100^000000";
		mes "^3131FF全ての職業^000000";
		break;
	case 3:
		mes "[防具商人]";
		mes "^3131FF体力のグローブ[0]^000000、";
		mes "ですね。";
		mes "性能は以下です。";
		next;
		mes "[体力のグローブ[0]]";
		mes "^3131FFMaxHP+100 , MaxSP+20^000000";
		mes "^3131FF純粋なVit+10ごとにMaxHP+50^000000";
		mes "^3131FF純粋なVitが110以上の時^000000";
		mes "^3131FF追加でMaxHP+1%^000000";
		mes "^3131FFスロット数:0^000000";
		next;
		mes "[体力のグローブ[0]]";
		mes "^3131FF系列:アクセサリ^000000";
		mes "^3131FF防御:0^000000";
		mes "^3131FF重量:10^000000";
		mes "^3131FF要求レベル:100^000000";
		mes "^3131FF全ての職業^000000";
		break;
	case 4:
		mes "[防具商人]";
		mes "^3131FF器用さのグローブ[0]^000000、";
		mes "ですね。";
		mes "性能は以下です。";
		next;
		mes "[器用さのグローブ[0]]";
		mes "^3131FFMaxHP+100 , MaxSP+20^000000";
		mes "^3131FF純粋なDex+10ごとにHit+1^000000";
		mes "^3131FF純粋なDexが110以上の時、追加で^000000";
		mes "^3131FF遠距離物理攻撃で与えるダメージ+1%^000000";
		mes "^3131FFスロット数:0^000000";
		next;
		mes "[器用さのグローブ[0]]";
		mes "^3131FF系列:アクセサリ^000000";
		mes "^3131FF防御:0^000000";
		mes "^3131FF重量:10^000000";
		mes "^3131FF要求レベル:100^000000";
		mes "^3131FF全ての職業^000000";
		break;
	case 5:
		mes "[防具商人]";
		mes "^3131FF幸運のグローブ[0]^000000、";
		mes "ですね。";
		mes "性能は以下です。";
		next;
		mes "[幸運のグローブ[0]]";
		mes "^3131FFMaxHP+100 , MaxSP+20^000000";
		mes "^3131FF純粋なLuk+10ごとにCri+1^000000";
		mes "^3131FF純粋なLukが110以上の時、追加で^000000";
		mes "^3131FFクリティカル攻撃で与えるダメージ+1%^000000";
		mes "^3131FFスロット数:0^000000";
		next;
		mes "[幸運のグローブ[0]]";
		mes "^3131FF系列:アクセサリ^000000";
		mes "^3131FF防御:0^000000";
		mes "^3131FF重量:10^000000";
		mes "^3131FF要求レベル:100^000000";
		mes "^3131FF全ての職業^000000";
		break;
	}
	next;
	mes "[防具商人]";
	mes "購入には";
	mes "スプレンディッドコイン10個";
	mes "必要です。買いますか？";
	next;
	if(select("買う","買わない") == 2) {
		mes "[防具商人]";
		mes "そうですか。";
		mes "ご用がありましたら、";
		mes "またお越しください。";
		close;
	}
	if(countitem(6081) < 10) {
		mes "[防具商人]";
		mes "コインが足りません。";
		close;
	}
	if(checkweight(2917,1) == 0) {
		mes "[防具商人]";
		mes "おっと、荷物がいっぱいのようです。";
		mes "所持品を減らしてから";
		mes "またお越しください。";
		close;
	}
	mes "[防具商人]";
	mes "毎度、ありがとうございます。";
	delitem 6081,10;
	getitem 2917+'@menu,1;
	close;
OnInit:
	waitingroom "防具屋",0;
	end;
}

ecl_in01.gat,64,97,5	script	スロット専門家ナトゥロ	436,{
	mes "[スロット専門家]";
	mes "私はナトゥロ。";
	mes "スロットの専門家です。";
	mes "スプレンディッドコイン5個で";
	mes "妹のナパラが売る品物に";
	mes "スロットを1個開けますわ。";
	next;
	if(select("スロットを活性化する","やめる") == 2) {
		mes "[スロット専門家]";
		mes "やめるのですね。";
		mes "またのお越しを";
		mes "お待ちしておりますわ。";
		close;
	}
	mes "[スロット専門家]";
	mes "スロットの活性化は";
	mes "非常に難しい作業なのです。";
	mes "目を凝らしながら慎重に作業しても";
	mes "簡単に失敗する場合がありますわ。";
	next;
	mes "[スロット専門家]";
	mes "失敗した場合、使用したコインや";
	mes "アイテムは無くなってしまいます。";
	mes "それでもよろしいですか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[スロット専門家]";
		mes "やめるのですね。";
		mes "またのお越しを";
		mes "お待ちしておりますわ。";
		close;
	}
	mes "[スロット専門家]";
	mes "どのアイテムのスロットを";
	mes "活性化しますか？";
	next;
	set '@menu,select("力のグローブ[0]","知力のグローブ[0]","敏捷のグローブ[0]","体力のグローブ[0]","器用さのグローブ[0]","幸運のグローブ[0]")-1;
	mes "[スロット専門家]";
	mes "それでは、確認いたします。";
	mes "あなたが選択した装備は ";
	mes getitemname(2917+'@menu)+ "[0]";
	mes "でよろしいですか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[スロット専門家]";
		mes "確認後にまたお声かけください。";
		close;
	}
	progressbar 3000;
	if(countitem(2917+'@menu) < 1) {
		mes "[スロット専門家]";
		mes "アイテムをお持ちでないようですわ。";
		mes "所持品を確認してくださいませ。";
		close;
	}
	if(countitem(6081) < 5) {
		mes "[スロット専門家]";
		mes "スプレンディッドコインが足りないわ。";
		mes "スロット活性化には5枚、必要です。";
		close;
	}
	set '@rand,rand(100);
	if('@rand >= 51 && '@rand < 60) {
		emotion 21;
		delitem 6081,5;
		delitem 2917+'@menu,1;
		getitem 2923+'@menu,1;
		mes "[スロット専門家]";
		mes "あああ、なんということでしょう！";
		mes "成功しました！";
		mes "おめでとうございます！";
		mes "スロットが活性化されましたわ。";
		close;
	}
	else {
		emotion 9;
		delitem 6081,5;
		delitem 2917+'@menu,1;
		mes "[スロット専門家]";
		mes "ああ、なんということでしょう。";
		mes "失敗してしまいました……。";
		mes "次はきっと成功します！";
		mes "次こそは……。";
		close;
	}
}

ecl_in01.gat,33,98,5	script	薬草商人フライフィーナ	443,{
	mes "[薬草商人]";
	mes "いらっしゃいませ～っす！";
	mes "新鮮な生薬草だけ扱っている";
	mes "フライフィーナの薬草商店～っす！";
	mes "何かお探しっすか？";
	next;
	switch(select("スノーフリップ","ピオニーマミー","ぴしゃりハーブ","世界樹のほこり","話を終える")) {
	case 1:
		mes "[薬草商人]";
		mes "スノーフリップっすね。";
		mes "この商品ははんぱねえっす。";
		mes "こんな効果があります。";
		next;
		mes "[スノーフリップ]";
		mes "^3131FF発火、出血、深い眠り、";
		mes "睡眠^000000を治療する。";
		mes "再使用待機時間5秒。";
		mes "重量:1";
		next;
		mes "[薬草商人]";
		mes "スプレンディッドコイン 5個で1個";
		mes "購入が出来まっす。";
		mes "これ、買いますか？";
		set '@gain,12812;
		set '@cost,5;
		break;
	case 2:
		mes "[薬草商人]";
		mes "ピオニーマミーっすね。";
		mes "これもやべえっすよ！";
		mes "こんな効果があります。";
		next;
		mes "[ピオニーマミー]";
		mes "^3131FF凍結、冷凍、氷結^000000を";
		mes "治療する。";
		mes "再使用待機時間5秒。";
		mes "重量:1";
		next;
		mes "[薬草商人]";
		mes "スプレンディッドコイン5個で1個";
		mes "購入が出来るっす。";
		mes "これ、買いますか？";
		set '@gain,12813;
		set '@cost,5;
		break;
	case 3:
		mes "[薬草商人]";
		mes "ぴしゃりハーブっすね。";
		mes "さすがお客様、しびれるぅっす！";
		mes "こんな効果があります。";
		next;
		mes "[ぴしゃりハーブ]";
		mes "^3131FFスタン、恐怖、混乱、幻覚^000000を";
		mes "治療する。";
		mes "再使用待機時間5秒。";
		mes "重量:1";
		next;
		mes "[薬草商人]";
		mes "スプレンディッドコイン1個で1個";
		mes "購入出来るっす。";
		mes "これ、買いますか？";
		set '@gain,12814;
		set '@cost,1;
		break;
	case 4:
		mes "[薬草商人]";
		mes "世界樹のほこりっすね。";
		mes "お客様、おめめが高いっす！";
		mes "こちらはこんな効果があります。";
		next;
		mes "[世界樹のほこり]";
		mes "^3131FF石化、暗黒、呪い、毒、速度減少";
		mes "リバースオーキッシュ^000000を";
		mes "治療する。";
		mes "再使用待機時間5秒。";
		mes "重量:1";
		next;
		mes "[薬草商人]";
		mes "スプレンディッドコイン1個で1個";
		mes "購入が出来ます。";
		mes "これ、買いますか？";
		set '@gain,12815;
		set '@cost,1;
		break;
	case 5:
		mes "[薬草商人]";
		mes "またのお越しをお待ちしてまっす！";
		close;
	}
	next;
	switch(select("1個購入","10個購入","購入しない")) {
	case 1:
		set '@num,1;
		break;
	case 2:
		set '@num,10;
		break;
	case 3:
		mes "[薬草商人]";
		mes "やめるっすか？";
		mes "では、またのお越しを";
		mes "お待ちしておりまっす！";
		close;
	}
	mes "[薬草商人]";
	mes getitemname('@gain)+ "を" +'@num+ "個購入しますか？";
	next;
	if(select("購入する","やめる") == 2) {
		mes "[薬草商人]";
		mes "やめるっすか？";
		mes "では、またのお越しを";
		mes "お待ちしておりまっす！";
		close;
	}
	if(countitem(6081) < '@cost*'@num) {
		mes "[薬草商人]";
		mes "コインが足りないっす。";
		close;
	}
	if(checkweight('@gain,'@num) == 0) {
		mes "[薬草商人]";
		mes "おっと、荷物がいっぱいです！";
		mes "荷物を整理してから";
		mes "また来てくださいっす。";
		close;
	}
	mes "[薬草商人]";
	mes "毎度、ありがとうございまっす！";
	delitem 6081,'@cost*'@num;
	getitem '@gain,'@num;
	close;
OnInit:
	waitingroom "薬草商人",0;
	end;
}

ecl_in01.gat,67,39,4	script	複製の専門家パルツ	445,{
	emotion 3;
	mes "[パルツ]";
	mes "いらっしゃいませ。お客様。";
	mes "ふふっ。";
	mes "何か御用ですか？";
	next;
	switch(select("用は無い","話を聞く","頭装備の複製をお願いする")) {
	case 1:
		mes "[パルツ]";
		mes "ふっ。";
		mes "私はいつでもここにいます。";
		mes "また訪れてください。";
		close;
	case 2:
		mes "[パルツ]";
		mes "ふっふっふ。";
		mes "私が何をしているかって？";
		mes "エクラージュで私ほど魔力制御に";
		mes "長けている人はいないでしょうね。";
		next;
		mes "[パルツ]";
		mes "魔力制御を試みる人は大勢いますが、";
		mes "私ほど的確かつ高度に";
		mes "能力を使いこなす人はいないですよ。";
		mes "ふふふ。";
		next;
		menu "で、何をしているんですか？",-;
		emotion 21;
		mes "[パルツ]";
		mes "ん、長くなりましたか。";
		mes "なかなか、ストレートな性格ですね。";
		if(Sex)
			mes "ふふ。お兄さん、気に入りましたよ。";	// 未調査
		else
			mes "ふふ。お姉さん、気に入りましたよ。";
		next;
		mes "[パルツ]";
		mes "私は最近新しい技術を確立しました。";
		mes "頭につける色々な装備。";
		mes "おしゃれな帽子、素敵な仮面";
		mes "可愛い花飾り、あれ等々……。";
		mes "あなたもたくさんお持ちでしょう。";
		next;
		emotion 1;
		mes "[パルツ]";
		mes "ただ、おしゃれで素敵な装備も";
		mes "能力の関係で使われることなく";
		mes "倉庫に眠ったまま……なんて経験";
		mes "ふっ……。";
		mes "あなたも一度くらいは";
		mes "あるんじゃないですか？ どうです？";
		next;
		menu "はい",-,"いいえ",-;
		emotion 18;
		mes "[パルツ]";
		mes "間違いなくあるはずです。";
		mes "私がそうだと思ったのだから";
		mes "そうに決まっていますよ。ふふ。";
		next;
		mes "[パルツ]";
		mes "そこで私は考えたのです。";
		mes "そういった装備の能力を";
		mes "私の持つ魔力制御の力で抑える事で";
		mes "見た目だけを楽しめるような";
		mes "装備を複製する事が";
		mes "出来るんじゃないかとね。";
		next;
		mes "[パルツ]";
		mes "いや、ふふ。さすが私の能力。";
		mes "^0571B0衣装装備^000000と呼ばれる";
		mes "見た目だけを変更するアイテムを";
		mes "複製する事が出来ましたよ。";
		mes "どうです。欲しいでしょう？";
		next;
		menu "作成には何が必要なの？",-;
		mes "[パルツ]";
		mes "良い質問です。必要な材料は";
		mes "ふっ。以下です。";
		next;
		mes "[パルツ]";
		mes "見た目を複製する元の^0571B0頭装備^000000";
		mes "^E1281E水晶鏡4つ、妖精の魔法の粉1個^000000";
		mes "^0000FFエメラルド、ルビー、サファイア";
		mes "トパーズ、ジルコン　各10個ずつ^000000";
		mes "スプレンディッドコイン 50個";
		next;
		emotion 22;
		mes "[パルツ]";
		mes "どうですか。";
		mes "必要な材料が多いですか？";
		mes "逆にこれだけの材料を使用してなお、";
		mes "魔力制御をおこなう事の出来る私が";
		mes "いかに優れているか、という事です。";
		mes "ふーっふっふ。ふふーっふっふ。";
		next;
		menu "で、複製可能な頭装備は？",-;
		mes "[パルツ]";
		mes "ふーふっ……っ……ゲフッゲフッ。";
		mes "おっと、忘れていました。";
		mes "あなた先ほどから中々鋭いですね。";
		mes "わかりました。お教えしましょう。";
		mes "私が複製可能な装備は現在、";
		mes "以下の8種類です。";
		next;
		mes "[パルツ]";
		mes "^0571B0花びら、マジェスティックゴート[0]";
		mes "ほお紅、ヴァルキリーヘルム[1]";
		mes "アサシンマスク、妖精の耳";
		mes "老人の仮面、学生帽[0]^000000";
		next;
		mes "[パルツ]";
		mes "さて、どうしますか？";
		mes "材料さえあれば";
		mes "いつでも作ってさしあげますよ。";
		next;
		if(select("必要ない","頭装備の複製をお願いする") == 1) {
			mes "[パルツ]";
			mes "ふっ……。";
			mes "いつでも私はここにいます。";
			mes "気が向いたらまたお越しください。";
			close;
		}
	case 3:
		break;
	}
	while(1) {
		mes "[パルツ]";
		mes "わかりました。では、複製の前に";
		mes "注意事項をお伝えします。ふふっ。";
		mes "少し長くなりますが、";
		mes "大事なのでよく聞いてください。";
		next;
		mes "[パルツ]";
		mes "^FF0000まず、複製を行うと、";
		mes "複製に使用した元の頭装備は";
		mes "無くなります。その為、";
		mes "精錬値、カード、エンチャントといった";
		mes "複製元に適用されていたものは";
		mes "全て消えますので注意してください。^000000";
		next;
		mes "[パルツ]";
		mes "^FF0000次に、同種の複製元の頭装備を";
		mes "複数、所持品に持たないでください。^000000";
		mes "複数同じ装備を所持している場合";
		mes "複製元に使用する頭装備を";
		mes "ご自身では選択できませんので、";
		mes "注意してください。";
		next;
		mes "[パルツ]";
		mes "わかりづらいですか？";
		mes "そうですね。例えばあなたが";
		mes "ヴァルキリーヘルム[1]と";
		mes "ヴァルキリーヘルムオブリロード[1]";
		mes "の２つを持っていたとしましょう。";
		mes "ふふ。例えばの話ですよ。";
		next;
		mes "[パルツ]";
		mes "この状態で、複製元に使う頭装備が";
		mes "ヴァルキリーヘルムオブリロード[1]";
		mes "になってしまったら、大惨事でしょう。";
		mes "ですから、使う予定の頭装備だけ";
		mes "持ってくるようにしてください。";
		next;
		mes "[パルツ]";
		mes "また、^FF0000複製元に使う頭装備は";
		mes "装備せず、所持品に持った状態で";
		mes "声をかけてください。^000000";
		mes "ふふ。";
		mes "焦らなくても、材料が揃えば";
		mes "すぐにお作りしますから。";
		next;
		mes "[パルツ]";
		mes "最後に、私がおこなう頭装備の複製は、";
		mes "100％成功します。";
		mes "ふふ。尊敬しましたか？";
		mes "そうです。必ず成功するんです。";
		mes "安心してお任せください。";
		next;
		mes "[パルツ]";
		mes "注意点は以上です。";
		mes "完璧ですね。どうです。";
		mes "大丈夫そうですか？";
		next;
		if(select("わかった","もう一度注意事項を聞く") == 1)
			break;
	}
	mes "[パルツ]";
	mes "さて、ではどの頭装備を";
	mes "複製しますか？";
	next;
	setarray '@reqlist$,"花びら(^777777材料不足^000000)","マジェスティックゴート[0](^777777材料不足^000000)","ほお紅(^777777材料不足^000000)","ヴァルキリーヘルム[1](^777777材料不足^000000)","アサシンマスク(^777777材料不足^000000)","妖精の耳(^777777材料不足^000000)","老人の仮面(^777777材料不足^000000)","学生帽[0](^777777材料不足^000000)";
	if(countitem(6081) >= 50 && countitem(747) >= 4 && countitem(6395) >= 1 && countitem(721) >= 10 && countitem(723) >= 10 && countitem(726) >= 10 && countitem(728) >= 10 && countitem(729) >= 10) {
		setarray '@equiplist,2269,2256,5040,5171,5054,2286,5176,5016;
		for(set '@i,0; '@i<getarraysize('@equiplist); set '@i,'@i+1) {
			if(countitem('@equiplist['@i]) >= 1) {
				set '@reqlist$['@i],getitemname('@equiplist['@i]) + "(^2502FD複製可能^000000)";
				set '@material['@i],1;
			}
		}
	}
	setarray '@itemlist,19552,19549,19550,19546,19553,19551,19554,19545;
	set '@menu,select(printarray('@reqlist$))-1;
	mes "[パルツ]";
	mes "^0571B0" +getitemname('@itemlist['@menu])+ "^000000ですね？";
	next;
	if('@material['@i] == 0 || countitem('@equiplist['@menu]) < 1) {
		emotion 28;
		mes "[パルツ]";
		mes "おや……アイテムが足りないようです。";
		next;
		mes "[パルツ]";
		mes "^0571B0" +getitemname('@equiplist['@menu])+ "^000000と";
		mes "^E1281Eスプレンディッドコイン50個";
		mes "水晶鏡4個、妖精の魔法の粉1個^000000";
		mes "^0000FFエメラルド、ルビー、サファイア";
		mes "トパーズ、ジルコン10個ずつ^000000";
		mes "持って来てください。";
		close;
	}
	emotion 1;
	mes "[パルツ]";
	mes "ふむ。材料は足りているようです。";
	mes "ふふふ。";
	mes "では、複製しますよ？";
	next;
	if(select("はい","いいえ") == 2) {
		emotion 23;
		mes "[パルツ]";
		mes "あれ？　あれあれ!?";
		mes "やめてしまうんですか……。";
		mes "ふっ。まぁいいでしょう。";
		mes "欲しくなったらまた来てください。";
		close;
	}
	emotion 29;
	mes "[パルツ]";
	mes "わかりました。";
	mes "久しぶりに";
	mes "実力を発揮する時が来ましたね。";
	mes "ふふっ。ふふふふふ！";
	next;
	emotion 9;
	mes "[パルツ]";
	mes "ふぅ。";
	mes "……";
	mes "…………";
	mes "では……";
	next;
	emotion 9;
	mes "[パルツ]";
	mes "ハアァァアア";
	mes "……";
	mes "フゥゥゥ";
	mes "………";
	mes "……まだだ………";
	mes "ハァァア！";
	next;
	mes "[パルツ]";
	mes "フゥゥゥゥォォオオ";
	mes "……";
	mes "……！　……今だ!!";
	mes "パァアルッツ!!";
	mes "パパパパァアルッツ!!";
	mes "アイムパァルッツ！";
	misceffect 12;
	progressbar 1;
	misceffect 54;
	progressbar 1;
	misceffect 55;
	progressbar 1;
	misceffect 56;
	progressbar 1;
	misceffect 68;
	next;
	delitem 6081,50;
	delitem 747,4;
	delitem 6395,1;
	delitem 721,10;
	delitem 723,10;
	delitem 726,10;
	delitem 728,10;
	delitem 729,10;
	delitem '@equiplist['@menu],1;
	getitem '@itemlist['@menu],1;
	mes "[パルツ]";
	mes "ふっ。完成です。";
	mes "満足な結果が出ましたね。";
	mes "また複製してほしかったら";
	mes "いつでも訪ねてください。";
	mes "私はいつでもここにいます。ふふ。";
	close;
OnInit:
	waitingroom "衣装装備作成",0;
	end;
}

//============================================================
// 猫の手職員転送
//------------------------------------------------------------
-	script	猫の手職員#eclage	-1,{
	mes "[猫の手職員]";
	mes "良い日ですにゃ～お客さん。";
	mes "お金を出す人の機嫌を取るためなら";
	mes "床に這いつくばる事も躊躇わない。";
	mes "過激な猫の手空間移動サービスに";
	mes "ようこそですにゃ～。";
	next;
	mes "[猫の手職員]";
	mes "我が猫の手空間移動サービスは";
	mes "これまで蓄積して来た";
	mes "異世界の情報を元に";
	mes "区間別移動サービスを";
	mes "行っていますにゃ。";
	next;
	mes "[猫の手職員]";
	mes "料金はマラン島特産缶詰や";
	mes "Zenyで受け付けているから";
	mes "ぜひご利用くださいにゃ～。";
	next;
	set '@menu$[0],"やめる";
	switch(strnpcinfo(2)) {
	case 1:	// エクラージュ
		setarray '@menu$[1],"モーラ(缶詰3個)","モーラ(3,000Zeny)";
		set '@map$,"mora.gat";
		set '@x,130;
		set '@y,75;
		set '@cost,3;
		break;
	case 2:	// スプレンディッド
		setarray '@menu$[1],"モーラ(缶詰20個)","モーラ(20,000Zeny)","ミッドガルド連合駐屯地(缶詰2個)","ミッドガルド連合駐屯地(2,000Zeny)";
		setarray '@map$,"mora.gat","mid_camp.gat";
		setarray '@x,130,207;
		setarray '@y,75,227;
		setarray '@cost,20,2;
		break;
	case 3:	// モーラ
		setarray '@menu$[1],"エクラージュ(缶詰3個)","エクラージュ(3,000Zeny)","スプレンディッド(無料)";
		setarray '@map$,"eclage.gat","splendide.gat";
		setarray '@x,109,365;
		setarray '@y,37,244;
		setarray '@cost,3,0;
		break;
	case 4:	// ミッドガルド連合駐屯地
		setarray '@menu$[1],"スプレンディッド(缶詰2個)","スプレンディッド(2,000Zeny)","マヌク(缶詰3個)","マヌク(3,000Zeny)";
		setarray '@map$,"splendide.gat","manuk.gat";
		setarray '@x,365,110;
		setarray '@y,244,342;
		setarray '@cost,2,3;
		break;
	case 5:	// マヌク
		setarray '@menu$[1],"ミッドガルド連合駐屯地(缶詰3個)","ミッドガルド連合駐屯地(3,000Zeny)","エルディカスティス(缶詰20個)","エルディカスティス(20,000Zeny)";
		setarray '@map$,"mid_camp.gat","dicastes01.gat";
		setarray '@x,207,189;
		setarray '@y,227,67;
		setarray '@cost,3,20;
		break;
	case 6:	// エルディカスティス
		setarray '@menu$[1],"マヌク(缶詰3個)","マヌク(3,000Zeny)";
		set '@map$,"manuk.gat";
		set '@x,110;
		set '@y,342;
		set '@cost,3;
		break;
	}
	set '@i,printarray('@menu$)-2;
	if('@i == -1) {
		mes "[猫の手職員]";
		mes "にゃにゃ～";
		mes "またのおこしをお待ちしてますにゃ～。";
		close;
	}
	if('@i%2) {
		set '@price,'@cost*1000;
		if(Zeny < '@price) {
			// 未調査
			mes "[猫の手職員]";
			mes "にゃにゃ？";
			mes "Zenyが足りないにゃ～。";
			mes "申し訳ありませんが";
			mes "無料では困りますにゃ～。";
			close;
		}
		mes "[猫の手職員]";
		mes "いってらっしゃいにゃ～。";
		close2;
		set Zeny,Zeny-'@price;
	}
	else {
		if(countitem(12636) < '@cost) {
			mes "[猫の手職員]";
			mes "にゃにゃ？";
			mes "缶詰の数が足りないにゃ～。";
			mes "申し訳ありませんが";
			mes "無料では困りますにゃ～。";
			close;
		}
		mes "[猫の手職員]";
		mes "いってらっしゃいにゃ～。";
		close2;
		delitem 12636,'@cost;
	}
	warp '@map$['@i/2],'@x['@i/2],'@y['@i/2];
	end;
OnInit:
	set '@dummy,getmapxy('@map$,'@dummy,'@dummy,1);		//'@map$以外はダミー
	if('@map$ == "-")					//duplicate元は何もしない
		end;
	waitingroom "猫の手空間移動サービス",0;
	end;
}

eclage.gat,117,40,4		duplicate(猫の手職員#eclage)	猫の手職員#1	421
splendide.gat,373,240,4	duplicate(猫の手職員#eclage)	猫の手職員#2	421
mora.gat,136,76,4		duplicate(猫の手職員#eclage)	猫の手職員#3	421
mid_camp.gat,207,234,4	duplicate(猫の手職員#eclage)	猫の手職員#4	421
manuk.gat,108,350,4		duplicate(猫の手職員#eclage)	猫の手職員#5	421
dicastes01.gat,189,68,4	duplicate(猫の手職員#eclage)	猫の手職員#6	421

eclage.gat,98,26,0	script	出口#eclage	45,1,1,{
	if(ASH_1QUE < 100) {	//異世界クエスト未クリア
		mes "["+strcharinfo(0)+"]";
		mes "（なぜか外への道が";
		mes "遮断されていて、";
		mes "外に出ることが出来ない……）";
		next;
		mes "‐^FF0000異世界クエスト^000000をクリアしないと";
		mes "　エクラージュの外へ";
		mes "　出ることができません‐";
		next;
		mes "[謎の妖精]";
		mes "そこのあなた。";
		mes "　";
		mes "‐誰かが話しかけてきた。";
		mes "　振り向くと一匹の妖精がいる‐";
		next;
		mes "[謎の妖精]";
		mes "道に迷いましたか？";
		mes "よろしければ、私がプロンテラに";
		mes "お送りしましょう。";
		next;
		if(select("お願いします！","けっこうです") == 2) {
			mes "[謎の妖精]";
			mes "そうですか。";
			mes "余計なお世話でしたね。";
			close;
		}
		mes "[謎の妖精]";
		mes "それではお送りします。";
		close2;
		warp "prontera.gat",116,72;
		end;
	}
	warp "ecl_fild01.gat",99,317;
	end;
}

//============================================================
// 案内員
//------------------------------------------------------------
eclage.gat,177,56,3	script	エクラージュ案内員#01	462,{
	mes "[エクラージュ案内員]";
	mes "こんにちは冒険者さん。";
	mes "ラフィネ族の町は他の種族の方には";
	mes "少し歩きにくいでしょう。";
	mes "良かったら私が行先を案内しますよ。";
	mes "どこか行きたい場所はありますか？";
	next;
	set '@type,strnpcinfo(2);
	if('@type != 1)	viewpoint 1,177,56,0,0xFF0000;
	if('@type != 2)	viewpoint 1,302,256,1,0xFF8000;
	if('@type != 3)	viewpoint 1,267,155,2,0x000000;
	if('@type != 4)	viewpoint 1,184,191,3,0x32CD32;
	if('@type != 5)	viewpoint 1,288,288,4,0xFF00EE;
	if('@type != 6)	viewpoint 1,184,123,5,0x0000FF;
	if('@type != 7)	viewpoint 1,96,70,6,0xC000C0;
	setarray '@str$,"南部^FF0000(177,56)^000000",
			"北部^FF8000(302,256)^000000",
			"東部^000000(267,155)^000000",
			"中央部^32cd32(184,191)^000000",
			"ホームツリー前^ff00ee(288,288)^000000",
			"ヒエールの研究室付近^0000FF(184,123)^000000",
			"出口付近^C000C0(96,70)^000000",
			"やめる";
	set '@str$['@type-1],"";
	switch(select(printarray('@str$))) {
	case 1:
		set '@x,175;
		set '@y,54;
		break;
	case 2:
		set '@x,302;
		set '@y,253;
		break;
	case 3:
		set '@x,268;
		set '@y,158;
		break;
	case 4:
		set '@x,182;
		set '@y,189;
		break;
	case 5:
		set '@x,285;
		set '@y,287;
		break;
	case 6:
		set '@x,182;
		set '@y,121;
		break;
	case 7:
		set '@x,96;
		set '@y,67;
		break;
	case 8:
		mes "[エクラージュ案内員]";
		mes "わかりました。";
		mes "案内が必要になったら";
		mes "気軽に話しかけてください。";
		close2;
		viewpoint 2,1,1,0,0xFFFFFF;
		viewpoint 2,1,1,1,0xFFFFFF;
		viewpoint 2,1,1,2,0xFFFFFF;
		viewpoint 2,1,1,3,0xFFFFFF;
		viewpoint 2,1,1,4,0xFFFFFF;
		viewpoint 2,1,1,5,0xFFFFFF;
		viewpoint 2,1,1,6,0xFFFFFF;
		end;
	}
	mes "[エクラージュ案内員]";
	mes "それではこちらへどうぞ。";
	close2;
	warp "eclage.gat",'@x,'@y;
	end;
OnInit:
	waitingroom "エクラージュ案内",0;
	end;
}

eclage.gat,302,256,3	duplicate(エクラージュ案内員#01)	エクラージュ案内員#02	462
eclage.gat,267,155,3	duplicate(エクラージュ案内員#01)	エクラージュ案内員#03	462
eclage.gat,184,191,3	duplicate(エクラージュ案内員#01)	エクラージュ案内員#04	462
eclage.gat,288,288,3	duplicate(エクラージュ案内員#01)	エクラージュ案内員#05	462
eclage.gat,184,123,3	duplicate(エクラージュ案内員#01)	エクラージュ案内員#06	462
eclage.gat,96,70,3		duplicate(エクラージュ案内員#01)	エクラージュ案内員#07	462

ecl_in01.gat,48,60,5	script	エクラージュガード	447,{
	mes "[エクラージュガード]";
	mes "冒険者よ、歓迎します。";
	mes "ここは偉大で神聖な木";
	mes "ホームツリーの内部にある広場です。";
	mes "何について知りたいですか？";
	next;
	switch(select("王宮","オーブ","商店","監獄","治療所","一般住居","会話をやめる")) {
	case 1:
		mes "[エクラージュガード]";
		mes "私たちの偉大な王を含めて勇猛な将校";
		mes "偉い学者達は皆、王宮の中に";
		mes "いらっしゃいます。";
		next;
		mes "[エクラージュガード]";
		mes "王宮はホームツリーの上層にあります。";
		mes "私たちはそのまま飛べば良いのですが";
		mes "あなたは羽がないので、右側の道から";
		mes "上層へ登ってください。";
		close;
	case 2:
		mes "[エクラージュガード]";
		mes "私の裏手にあるオーブは";
		mes "私たちラフィネ族の象徴と同じです。";
		mes "神秘で力強い魔力を持っています。";
		mes "ラフィネ族は皆このオーブを見守って";
		mes "大切に保護しています。";
		close;
	case 3:
		mes "[エクラージュガード]";
		mes "ここはホームツリーの広場です。";
		mes "必要なものがありましたら、";
		mes "この周辺で入手可能でしょう。";
		close;
	case 4:
		mes "[エクラージュガード]";
		mes "監獄は罪を犯した人々を";
		mes "閉じこめるための場所です。";
		mes "ただの冒険者であるあなたが";
		mes "そんな場所に何の用事が";
		mes "あるのですか？";
		next;
		mes "[エクラージュガード]";
		mes "疑問が残りますが";
		mes "一応位置はお知らせいたします。";
		mes "左側の道を降りて行けばあります。";
		mes "しかし、中に入ることは簡単では";
		mes "ないでしょう。";
		close;
	case 5:
		mes "[エクラージュガード]";
		mes "自然に優しく包まれるその中では";
		mes "すべての疲れも痛みも";
		mes "消えてしまいます。";
		next;
		mes "[エクラージュガード]";
		mes "治療所であなたの疲れた心身を";
		mes "治療してみたいなら";
		mes "左側の道を降りてください。";
		close;
	case 6:
		mes "[エクラージュガード]";
		mes "ここに来る間にラフィネ族が構えた";
		mes "美しいヤイを見ませんでしたか？";
		mes "ホームツリーの外に出てみてください。";
		mes "そこに私達の住居があります。";
		close;
	case 7:
		mes "[エクラージュガード]";
		mes "困ったことがあったら";
		mes "いつでも聞いてください。";
		mes "それでは、良い旅を。";
		close;
	}
}

//============================================================
// クエスト案内員
//------------------------------------------------------------
eclage.gat,279,293,3	script	不思議な上級ラフィネ	435,{
	mes "[不思議な上級ラフィネ]";
	mes "……不思議な風が吹いています。";
	mes "どうやらあなたが";
	mes "風を吹かせようとしているようですね。";
	mes "いや、イグドラシルがあなたを";
	mes "導いているのかもしれません。";
	next;
	mes "[不思議な上級ラフィネ]";
	mes "あなたがこのエクラージュで";
	mes "何がおこせるのか、";
	mes "お教えしましょう。";
	mes "イグドラシルの加護を……。";
	setarray '@str$,"(^ff0000進行不可^000000)","(^0000ff進行可能^000000)","(^008000進行中^000000)","(^808080クリア済^000000)";
	set '@story[0],ECL_1QUE==3?  3: (ECL_1QUE>0? 2: 1);
	set '@story[1],ECL_2QUE==28? 3: (ECL_2QUE>0? 2: (ECL_1QUE<3 || BaseLevel<99? 0: 1));
	set '@story[2],ECL_3QUE==33? 3: (ECL_3QUE>0? 2: (BaseLevel<99? 0: 1));
	set '@story[3],ECL_4QUE==24? 3: (ECL_4QUE>0? 2: (BaseLevel<99? 0: 1));
	set '@story[4],ECL_5QUE==23? 3: (ECL_5QUE>0? 2: (BaseLevel<99? 0: 1));
	set '@story[5],ECL_6QUE==41? 3: (ECL_6QUE>0? 2: (ECL_3QUE<5 || BaseLevel<99? 0: 1));
	set '@story[6],ECL_7QUE==8?  3: (ECL_7QUE>0? 2: (BaseLevel<99? 0: 1));
	set '@story[7],ECL_8QUE>=3?  3: (ECL_8QUE>0? 2: (ECL_2QUE<2 || BaseLevel<99? 0: 1));
	set '@story[8],ECL_8QUE>=5?  3: (ECL_8QUE>2? 2: (ECL_8QUE<3 || BaseLevel<99? 0: 1));
	set '@story[9],ECL_8QUE>=10? 3: (ECL_8QUE>4? 2: (ECL_8QUE<5 || BaseLevel<99? 0: 1));
	set '@story[10],ECL_9QUE==10?3: (ECL_9QUE>0? 2: (BaseLevel<99? 0: 1));
	while(1) {
		next;
		set '@menu,select(
			"冒険者達との出会い　" +'@str$['@story[0]],
			"夢見る作家　" +'@str$['@story[1]],
			"エクラージュの王　" +'@str$['@story[2]],
			"美しさの代償　" +'@str$['@story[3]],
			"妖精たちの事件簿　" +'@str$['@story[4]],
			"悠久なる絆　" +'@str$['@story[5]],
			"エクラージュの悪戯キッズ　" +'@str$['@story[6]],
			"ラフィネ流ガーデニング　" +'@str$['@story[7]],
			"塔に挑んだ冒険者達　" +'@str$['@story[8]],
			"塔の中の冒険者　" +'@str$['@story[9]],
			"プロフェッサーワームの記憶　" +'@str$['@story[10]],
			"やめる")-1;
		if('@menu == 11) {
			mes "[不思議な上級ラフィネ]";
			mes "イグドラシルの加護を……。";
			close;
		}
		switch('@story['@menu]){
		case 0:
			mes "[不思議な上級ラフィネ]";
			mes "風が……起きない……。";
			mes "今のあなたには";
			mes "まだ足りないものがあるようです。";
			mes "　";
			mes "^0000ff‐条件が満たない為、";
			mes "　現在このクエストは出来ません‐^000000";
			break;
		case 1:
			mes "[不思議な上級ラフィネ]";
			mes "……見えます。";
			mes "あなたが……起こす風が……。";
			next;
			mes "[不思議な上級ラフィネ]";
			mes "ご希望でしたらその場所まで";
			mes "お送りしましょう。";
			next;
			if(select("送ってもらう","やめておく") == 2)
				break;
			mes "[不思議な上級ラフィネ]";
			mes "それではお送りしましょう。";
			mes "　";
			mes "あなたにイグドラシルの加護を。";
			close2;
			switch('@menu) {
			case 0: warp "ecl_fild01.gat",94,320; break;	// 冒険者達との出会い
			case 1: warp "eclage.gat",102,30; break;		// 夢見る作家
			case 2: warp "ecl_in01.gat",32,49; break;		// エクラージュの王
			case 3: warp "eclage.gat",282,254; break;		// 美しさの代償
			case 4: warp "eclage.gat",156,53; break;		// 妖精たちの事件簿
			case 5: warp "ecl_in02.gat",133,114; break;		// 悠久なる絆
			case 6: warp "ecl_in01.gat",26,87; break;		// エクラージュの悪戯キッズ
			case 7: warp "ecl_fild01.gat",190,92; break;	// ラフィネ流ガーデニング
			case 8: warp "ecl_fild01.gat",190,92; break;	// 塔に挑んだ冒険者達
			case 9: warp "ecl_fild01.gat",190,92; break;	// 塔の中の冒険者
			case 10: warp "ecl_tdun04.gat",26,38; break;	// プロフェッサーワームの記憶
			}
			end;
		case 2:
			mes "[不思議な上級ラフィネ]";
			mes "風が……吹いている。";
			mes "今……あなたは……";
			mes "その中心にいる……。";
			next;
			mes "^0000ff‐進行中のクエストは";
			mes "　クエストリストから確認する事が";
			mes "　可能です‐^000000";
			break;
		case 3:
			mes "[不思議な上級ラフィネ]";
			mes "……静寂が……";
			mes "訪れています……。";
			mes "　";
			mes "^ff0000‐クリア済のクエストです‐^000000";
			break;
		}
		next;
		mes "[不思議な上級ラフィネ]";
		mes "他も確認しますか？";
	}
OnInit:
	waitingroom "クエスト案内",0;
	end;
}

//============================================================
// 住民
//------------------------------------------------------------
ecl_fild01.gat,92,316,5	script	旅行者	545,{
	mes "[旅行者]";
	mes "こんなにいっぱい待っているとは……。";
	mes "私はいつになったら入れるかな？";
	emotion 28;
	close;
}

ecl_fild01.gat,106,312,5	script	旅行者	525,{
	mes "[旅行者]";
	mes "私はもう書類を提出したけど";
	mes "ここの花畑がとても気に入って";
	mes "ここに居続けています。";
	emotion 14;
	next;
	mes "[旅行者]";
	mes "夜は寝袋で耐えられます！";
	mes "警備兵の嫌がっている";
	mes "視線以外は……。";
	emotion 4,"警備兵#ep14_2";
	emotion 4,"警備兵#ep14_2_2";
	close;
}

ecl_fild01.gat,108,320,7	script	旅行者	941,{
	mes "[旅行者]";
	mes "エクラージュはどれほど美しい";
	mes "都市なのでしょうか？";
	mes "考えるだけでドキドキします。";
	emotion 3;
	close;
}

ecl_fild01.gat,105,320,2	script	旅行者	436,{
	mes "[旅行者]";
	mes "違う、私は旅行者ではなく";
	mes "エクラージュの住民なんだよ！";
	emotion 6;
	next;
	mes "[旅行者]";
	mes "旅行者たちが多くて";
	mes "私も中に入れないというのは何だ！";
	emotion 23;
	close;
}

ecl_fild01.gat,103,319,5	script	旅行者	900,{
	mes "[旅行者]";
	mes "ここのドングリは甘くて美味しい。";
	next;
	mes "[旅行者]";
	mes "このドングリならこの世で一番";
	mes "おいしい料理を作れるかもしれない。";
	emotion 21;
	close;
}

ecl_fild01.gat,110,316,3	script	旅行者	896,{
	mes "[旅行者]";
	mes "旅行をする時は荷物を";
	mes "少なめにした方がいいです。";
	next;
	mes "[旅行者]";
	mes "旅行をすると荷物が少しずつ増えて";
	mes "重くなりますから。";
	next;
	mes "[旅行者]";
	mes "それが人生の重量なのですかね？";
	emotion 38;
	close;
}

ecl_fild01.gat,92,318,5	script	旅行者	517,{
	mes "[旅行者]";
	mes "うう……。";
	close;
}

ecl_fild01.gat,93,318,5	script	旅行者	107,{
	mes "[旅行者]";
	mes "うう……うう……。";
	next;
	mes "[旅行者]";
	mes "まだなのか……長すぎる……";
	mes "もう空腹で限界だ……";
	close;
}

ecl_fild01.gat,94,313,5	script	旅行者	715,{
	mes "[旅行者]";
	mes "ん！　君もミッドガルド出身なのか？";
	next;
	mes "[旅行者]";
	mes "最近になってミッドガルド出身の人が";
	mes "多く見られて嬉しいよ。";
	emotion 44;
	close;
}

ecl_fild01.gat,101,320,5	script	旅行者	522,{
	mes "[旅行者]";
	mes "はあ……足が痛い。";
	mes "やっとビフロストを渡って来たのに";
	mes "また待てと！";
	emotion 6;
	close;
}

ecl_fild01.gat,88,315,5	script	旅行者	98,{
	mes "[旅行者]";
	mes "ああ……";
	mes "どうしてこんなに人が多いんだ……。";
	next;
	mes "[旅行者]";
	mes "ひとりになりたい……。";
	emotion 57;
	close;
}

ecl_in01.gat,54,91,3	script	ダンディ#ecl	443,{
	mes "[ダンディ]";
	mes "この素晴らしい私を見てみな！";
	mes "どうだ？ かっこいいだろう？";
	next;
	mes "[ダンディ]";
	mes "ラフィネなら誰でも自由自在に服を";
	mes "変化できるけど、誰でもこんなに";
	mes "かっこいいわけではないんだ！";
	next;
	emotion 32,"ラフィキ#ecl";
	mes "[ラフィキ]";
	mes "君は何を言っているんだ？";
	mes "誰が見てもこの区域で一番の";
	mes "オシャレさんは私なんだ！";
	close;
}

ecl_in01.gat,53,92,4	script	ラフィキ#ecl	444,{
	mes "[ラフィキ]";
	mes "今日も私のセンスは素晴らしい。";
	next;
	emotion 14;
	mes "[ラフィキ]";
	mes "こんにちは～。";
	mes "私の素晴らしい体ちゃん～。";
	mes "髪の毛ひとつひとつまで美しいね！";
	next;
	emotion 29,"ダンディ#ecl";
	mes "[ダンディ]";
	mes "よお、ダサイ君。";
	mes "今日はいっそうダサいな！";
	close;
}

eclage.gat,101,130,5	script	ウタポア	435,{
	mes "[ウタポア]";
	mes "私は親と一緒に住んでいたけど、";
	mes "最近一人暮らしを始めたのです!!";
	mes "自分のヤイを持つようになって";
	mes "本当にうれしいです！";
	next;
	mes "[ウタポア]";
	mes "エクラージュで一番華麗で";
	mes "美しいヤイにするつもりです！";
	next;
	emotion 18;
	mes "[ウタポア]";
	mes "ああ、うれしいなぁ！";
	mes "うれしいなぁ!!";
	close;
}

ecl_in01.gat,55,25,3	script	ミザニ	520,{
	mes "[ミザニ]";
	mes "異界から来た方ですね？";
	mes "歓迎します。";
	next;
	mes "[ミザニ]";
	mes "ただし、あなたがエクラージュを";
	mes "混乱させなければの話ですが。";
	close;
}

eclage.gat,106,61,4	script	マコサ	444,{
	mes "[マコサ]";
	mes "私も異界に行って見たいです。";
	next;
	mes "[マコサ]";
	mes "けど、異界の人たちはこんなカワイイ";
	mes "私を見て見ぬふりができますかね？";
	next;
	emotion 32;
	mes "[マコサ]";
	mes "はああ、何処に行っても";
	mes "可愛くて困るんだよな……。";
	close;
}

ecl_in02.gat,168,41,3	script	パムボ	438,{
	mes "[パムボ]";
	mes "光るものは好きですか？";
	next;
	emotion 14;
	mes "[パムボ]";
	mes "私はとても好きだけど！";
	next;
	mes "[パムボ]";
	mes "ピカピカ～ピカピカ～♪";
	next;
	mes "[パムボ]";
	mes "ピカピカ～ピカピカ～♪";
	mes "ピカピカ～ピカピカ～♪";
	next;
	mes "[パムボ]";
	mes "ピカピカ～ピカピカ～♪";
	mes "ピカピカ～ピカピカ～♪";
	mes "うははは～ははは～ひひ～♪";
	mes "へへへ～ふふひ～ほほ～♪";
	mes "くわああ～へれれ～ぷぷ～♪";
	next;
	emotion 28;
	mes "[パムボ]";
	mes "……。";
	mes "だけど、ここには光る物が";
	mes "ありません……。";
	close;
}

ecl_fild01.gat,134,109,6	script	ワラオ	446,{
	mes "[ワラオ]";
	mes "あ～、お腹が空いたけど、";
	mes "今日は何を食べようかな？";
	next;
	mes "[ワラオ]";
	mes "そういえば異界の人は何の味が";
	mes "するのか気になるな？";
	next;
	emotion 29;
	mes "[ワラオ]";
	mes "あはは、";
	mes "冗談ですよ、もちろん！";
	close;
}

ecl_in01.gat,38,37,4	script	ひざまずいた少年	441,{
	mes "[ひざまずいた少年]";
	mes "どうしてこんな風にして";
	mes "いるのか気になるんですか？";
	next;
	mes "[ひざまずいた少年]";
	mes "最初はただ普通に";
	mes "座っていたのです。";
	mes "しかし、長時間座っていたら";
	mes "膝をのばすことができなく";
	mes "なってしまいました。";
	next;
	emotion 28;
	mes "[ひざまずいた少年]";
	mes "のばそうとしても足がとても痺れて!!";
	mes "このままひざまずいた状態で";
	mes "生きなければならないんでしょうか？";
	close;
}

ecl_fild01.gat,183,190,4	script	ケイタリン	447,{
	emotion 18;
	mes "[ケイタリン]";
	mes "わははは！ こんにちわ！";
	mes "遠足に行くには丁度いい日ですよね？";
	next;
	emotion 16;
	mes "[ケイタリン]";
	mes "遠足に行きたいけど、お弁当を作って";
	mes "持って行くのが面倒くさいですか？";
	next;
	emotion 21;
	mes "[ケイタリン]";
	mes "もう心配しないで大丈夫です！";
	next;
	emotion 0;
	mes "[ケイタリン]";
	mes "エクラージュのリスたちが";
	mes "汗をかきながら集めた";
	mes "ドングリで作った";
	mes "美味しい組み合わせ！";
	next;
	emotion 8;
	mes "[ケイタリン]";
	mes "豪華なお弁当セットがなんと";
	mes "2,999コイン!!";
	next;
	emotion 23;
	mes "[ケイタリン]";
	mes "本当に破格的な価格！";
	next;
	emotion 3;
	mes "[ケイタリン]";
	mes "今、注文して頂くと百回使用しても";
	mes "いつも新品のような使い捨てフォークも";
	mes "差し上げます！";
	next;
	mes "[ケイタリン]";
	mes "え？ 異界の方は";
	mes "そんなにドングリを";
	mes "食べないんですか？";
	next;
	mes "[ケイタリン]";
	mes "知りませんでした……。";
	close;
}

ecl_in01.gat,41,103,1	script	バルグレ少女	439,{
	mes "[バルグレ少女]";
	mes "この上にあるバルコニーが";
	mes "見えますか？";
	mes "そこでは重要な行事が行われる度に";
	mes "マヨル・ジュン様が現れるんです！";
	next;
	emotion 14;
	mes "[バルグレ少女]";
	mes "本当にかっこいいです!!";
	mes "きゃああああ～♪";
	close;
}

ecl_in01.gat,52,102,4	script	合唱団団長	442,{
	mes "[合唱団団長]";
	mes "私たちはエクラージュ木の羽合唱団～♪";
	mes "天上のハーモニーを聞かせましょう～♪";
	next;
	mes "[合唱団団長]";
	mes "異界の人よ、あなたにも～♪";
	next;
	emotion 2;
	mes "[合唱団]";
	mes "あ～♪";
	next;
	emotion 2,"合唱団団員#ecl01";
	mes "[合唱団]";
	mes "あ～～♪";
	mes "あ～♪";
	next;
	emotion 2,"合唱団団員#ecl02";
	mes "[合唱団]";
	mes "あ～～～♪";
	mes "あ～～♪";
	mes "あ～♪";
	next;
	emotion 2,"合唱団団員#ecl03";
	mes "[合唱団]";
	mes "あ～～～～♪";
	mes "あ～～～♪";
	mes "あ～～♪";
	mes "あ～♪";
	next;
	emotion 2,"合唱団団員#ecl04";
	mes "[合唱団]";
	mes "あ～～～～～♪";
	mes "あ～～～～♪";
	mes "あ～～～♪";
	mes "あ～～♪";
	mes "あ～♪";
	next;
	emotion 2,"合唱団団員#ecl05";
	mes "[合唱団]";
	mes "あ～～～～～～♪";
	mes "あ～～～～～♪";
	mes "あ～～～～♪";
	mes "あ～～～♪";
	mes "あ～～♪";
	mes "あ～♪";
	next;
	emotion 2;
	emotion 2,"合唱団団員#ecl01";
	emotion 2,"合唱団団員#ecl02";
	emotion 2,"合唱団団員#ecl03";
	emotion 2,"合唱団団員#ecl04";
	emotion 2,"合唱団団員#ecl05";
	mes "[合唱団]";
	mes "らららら～♪";
	mes "感じて見ましょう～";
	mes "流れるようなメロディを～♪";
	next;
	mes "[合唱団団員]";
	mes "どうですか!!";
	mes "私たちのハーモニー!!";
	close;
}

ecl_in01.gat,51,103,4	script	合唱団団員#ecl01	442,{
	emotion 2;
	mes "[合唱団団員]";
	if(strnpcinfo(2) == "ecl05")
		mes "あん～♪";
	else
		mes "あ～♪";
	close;
}
ecl_in01.gat,53,103,4	duplicate(合唱団団員#ecl01)	合唱団団員#ecl02	442
ecl_in01.gat,50,104,4	duplicate(合唱団団員#ecl01)	合唱団団員#ecl03	442
ecl_in01.gat,52,104,4	duplicate(合唱団団員#ecl01)	合唱団団員#ecl04	442
ecl_in01.gat,54,104,4	duplicate(合唱団団員#ecl01)	合唱団団員#ecl05	442

ecl_tdun03.gat,50,47,4	script	看板	837,{
	mes "‐4階への入口が壊れているため、";
	mes "　ここからは上がれません。";
	mes "　用がある方は塔の入口にいる";
	mes "　案内人に話しかけてください‐";
	close;
}

ecl_in02.gat,96,22,3	script	立て札	835,{
	mes "[北] 監獄";
	mes "[西] 治療所";
	close;
}

ecl_in01.gat,8,71,5	script	エクラージュガード	447,{
	mes "[エクラージュガード]";
	mes "こちらはホームツリーの下層へ";
	mes "降りる道に繋がっています。";
	mes "また、監獄と治療所があります。";
	close;
}

ecl_in01.gat,76,89,4	script	倉庫番ラフィネ	437,{
	mes "[倉庫番ラフィネ]";
	mes "倉庫使いますか～？";
	mes "1回^FF0000 100 Zeny^000000になります～。";
	next;
	if(select("使う","使わない") == 2) {
		mes "[倉庫番ラフィネ]";
		mes "使うときは遠慮なく";
		mes "言ってください～。";
		close;
	}
	if(Zeny < 100) {
		mes "[倉庫番ラフィネ]";
		mes "どうやらお金が足りないようです。";
		close;
	}
	mes "[倉庫番ラフィネ]";
	mes "倉庫を開きます。";
	close2;
	set Zeny,Zeny-100;
	openstorage;
	end;
OnInit:
	waitingroom "倉庫",0;
	end;
}

ecl_in02.gat,164,56,3	script	治療所受付員	437,{
	mes "[治療所受付員]";
	mes "こんにちは。";
	mes "ここはエクラージュ治療所です。";
	next;
	switch(select("位置セーブ","休む","会話をやめる")) {
	case 1:
		mes "[治療所受付員]";
		mes "セーブしました。";
		mes "ですが、治療所でセーブを";
		mes "したからといって";
		mes "あまり怪我をしないでくださいね。";
		savepoint "ecl_in02.gat",163,49;
		close;
	case 2:
		mes "[治療所受付員]";
		mes "ホームツリーの清らかなエネルギーで";
		mes "一杯な治療所で疲れた心身を";
		mes "回復してみませんか？";
		mes "本来はスプレンディッドコインを";
		mes "1個頂きますが、 お客様に限って";
		mes "5,000Zenyにサービスしてあげますよ。";
		next;
		switch(select("スプレンディッドコインを使用","Zenyを使用","やめる")) {
		case 1:
			if(countitem(6081) < 1) {
				mes "[治療所受付員]";
				mes "スプレンディッドコインを";
				mes "持っていないみたいです。";
				mes "よく確認してください。";
				close;
			}
			mes "[治療所受付員]";
			mes "ゆっくり休んでください。";
			close2;
			delitem 6081,1;
			percentheal 100,100;
			warp "ecl_in02.gat",167,49;
			end;
		case 2:
			if(Zeny < 5000) {
				mes "[治療所受付員]";
				mes "所持金が足りないようです。";
				mes "よく確認してください。";
				close;
			}
			mes "[治療所受付員]";
			mes "ゆっくり休んでください。";
			close2;
			set Zeny,Zeny-5000;
			percentheal 100,100;
			warp "ecl_in02.gat",167,49;
			end;
		case 3:
			mes "[治療所受付員]";
			mes "疲れた時はいつでもご利用ください。";
			mes "またのお越しをお待ちしています。";
			close;
		}
	case 3:
		mes "[治療所受付員]";
		mes "疲れた時はいつでもご利用ください。";
		mes "またのお越しをお待ちしています。";
		close;
	}
}

ecl_in02.gat,135,45,5	script	傷ついたラフィネ	441,{
	mes "[傷ついたラフィネ]";
	mes "うう……。";
	mes "ここは……どこですか……?";
	next;
	mes "[治療所ラフィネ]";
	mes "治療所ですから安心してください。";
	mes "止血剤も使いましたし";
	mes "治癒魔法も施しました。";
	mes "出血がひどくて大変な事に";
	mes "なるところだったんですよ。";
	next;
	mes "[傷ついたラフィネ]";
	mes "……。";
	mes "あの、記憶が全然ないのですが……。";
	mes "私はどうしたのですか？";
	next;
	mes "[治療所ラフィネ]";
	mes "……矢の当たりどころが悪くて。";
	next;
	mes "[傷ついたラフィネ]";
	mes "……何の話ですか？";
	next;
	mes "[治療所ラフィネ]";
	mes "元気になったら申し上げようと";
	mes "思っていたのですが……。";
	mes "よく聞いてください。";
	next;
	mes "[治療所ラフィネ]";
	mes "あなたはこれから";
	mes "ヤイを飾ることができません。";
	mes "羽に怪我をしてしまったのです。";
	mes "羽の一番重要な部分を";
	mes "矢が貫通してしまって……。";
	next;
	mes "[傷ついたラフィネ]";
	mes "そんな……。";
	mes "ごめんなさい……。";
	mes "ごめんなさい……あなた……。";
	mes "うわああーん!!";
	close;
}

ecl_in02.gat,137,44,3	script	治療所ラフィネ	442,{
	mes "[傷ついたラフィネ]";
	mes "うう……。";
	mes "ここは……どこですか……?";
	next;
	mes "[治療所ラフィネ]";
	mes "治療所ですから安心してください。";
	mes "止血剤も使いましたし";
	mes "治癒魔法も施しました。";
	mes "出血がひどくて大変な事に";
	mes "なるところだったんですよ。";
	next;
	mes "[傷ついたラフィネ]";
	mes "……。";
	mes "あの、記憶が全然ないのですが……。";
	mes "私はどうしたのですか？";
	next;
	mes "[治療所ラフィネ]";
	mes "……矢の当たりどころが悪くて。";
	next;
	mes "[傷ついたラフィネ]";
	mes "……何の話ですか？";
	next;
	mes "[治療所ラフィネ]";
	mes "元気になったら申し上げようと";
	mes "思っていたのですが……。";
	mes "よく聞いてください。";
	next;
	mes "[治療所ラフィネ]";
	mes "あなたはこれから";
	mes "ヤイを飾ることができません。";
	mes "羽に怪我をしてしまったのです。";
	mes "羽の一番重要な部分を";
	mes "矢が貫通してしまって……。";
	next;
	mes "[傷ついたラフィネ]";
	mes "そんな……。";
	mes "ごめんなさい……。";
	mes "ごめんなさい……あなた……。";
	mes "うわああーん!!";
	close;
}

//============================================================
// 冒険者達との出会いクエスト
//- Registry -------------------------------------------------
// ECL_1QUE -> 0～3
//------------------------------------------------------------
ecl_fild01.gat,97,322,0	script	#ep14_2入り口	45,3,3,{
	if(ECL_1QUE < 3) {
		mes "[警備兵]";
		mes "お待ちください。";
		mes "初めてエクラージュを訪れる方は";
		mes "入場するための書類を";
		mes "記入してください。";
		close;
	}
	warp "eclage.gat",100,28;
	end;
}

ecl_fild01.gat,94,322,5	script	警備兵#ep14_2	447,{
	switch(ECL_1QUE) {
	case 0:
		mes "[警備兵]";
		mes "初めてエクラージュを訪れる方は";
		mes "入場するための書類を";
		mes "記入してください。";
		next;
		mes "[警備兵]";
		mes "最近、ビフロストを通じて";
		mes "ミッドガルド大陸から訪れる人が";
		mes "多くなってしまい、";
		mes "このような手続きをとるように";
		mes "なりました。";
		next;
		mes "[警備兵]";
		mes "もちろん、記入していただいた書類は";
		mes "エクラージュの出入統計に使用された後";
		mes "厳重に保管いたしますので";
		mes "ご安心ください。";
		next;
		if(select("書類を作成する","やめる") == 2) {
			mes "[警備兵]";
			mes "書類に記入しないとエクラージュに";
			mes "入場することができないので";
			mes "注意してください。";
			close;
		}
		mes "[警備兵]";
		mes "では、この書類に";
		mes "名前と職業を書いてください。";
		next;
		mes "‐手渡された書類に";
		mes "　必要事項を記入した‐";
		next;
		mes "[警備兵]";
		mes "書類の記入が完了しましたら";
		mes "あそこにいる出入国管理者に";
		mes "提出してください。";
		set ECL_1QUE,1;
		setquest 11310;
		close;
	case 1:
		mes "[警備兵]";
		mes "書類に名前と職業、レベルを書いた後";
		mes "あそこにいる出入国管理者に";
		mes "提出してください。";
		close;
	case 2:
		mes "[警備兵]";
		mes "書類の作成が完了したようですね。";
		mes "ラフィネの首都エクラージュに";
		mes "ようこそ！";
		next;
		mes "[警備兵]";
		mes "エクラージュはビフロストの";
		mes "影響圏にあるので";
		mes "種族間での自由な意思疎通が";
		mes "可能です。";
		next;
		mes "[警備兵]";
		mes "ですから、別途の通訳機が必要なく";
		mes "歩行種族のための橋も";
		mes "十分に整備されているので";
		mes "楽しい時を過ごせるでしょう。";
		next;
		mes "[警備兵]";
		mes "また、エクラージュの奥には";
		mes "偉大で神聖な木";
		mes "^FF0000ホームツリー^000000があります。";
		mes "内部にも入る事ができますので";
		mes "ぜひ、お立ち寄りください。";
		set ECL_1QUE,3;
		chgquest 11311,201565;
		close2;
		warp "eclage.gat",100,28;
		end;
	default:
		mes "[警備兵]";
		mes "ラフィネの首都エクラージュに";
		mes "ようこそ！";
		next;
		mes "[警備兵]";
		mes "エクラージュはビフロストの";
		mes "影響圏にあるので";
		mes "種族間での自由な意思疎通が";
		mes "可能です。";
		next;
		mes "[警備兵]";
		mes "ですから、別途の通訳機が必要なく";
		mes "歩行種族のための橋も";
		mes "十分に整備されているので";
		mes "楽しい時を過ごせるでしょう。";
		next;
		mes "[警備兵]";
		mes "また、エクラージュの奥には";
		mes "偉大で神聖な木";
		mes "^FF0000ホームツリー^000000があります。";
		mes "内部にも入る事ができますので";
		mes "ぜひ、お立ち寄りください。";
		close;
	}
OnInit:
	if(strnpcinfo(2) == "ep14_2_2")
		waitingroom "エクラージュ入場",0;
	end;
}
ecl_fild01.gat,100,323,3	duplicate(警備兵#ep14_2)	警備兵#ep14_2_2	447

ecl_fild01.gat,111,320,3	script	出入国管理者	445,{
	switch(ECL_1QUE) {
	case 0:
		mes "[出入国管理者]";
		mes "何の用ですか？";
		mes "見ての通り、私は今とても忙しいので";
		mes "急ぎの用件でないなら";
		mes "ジャマをしないで頂けますか？";
		emotion 6;
		close;
	case 1:
		mes "[出入国管理者]";
		mes "ふう……お待たせして";
		mes "申し訳ありません。";
		mes "最近、旅行者が多くて……。";
		emotion 16;
		next;
		mes "[出入国管理者]";
		mes "それでは記入した書類をこちらに。";
		next;
		mes "[？？？]";
		mes "おい！　書類全部書いたぞ！";
		mes "これで間違いないよな？";
		mes "早く中に入れてくれよ！";
		cutin "bu_du1",2;
		emotion 23,"";
		next;
		cutin "bu_du1",255;
		mes "[出入国管理者]";
		mes "あの……お客様、順番に書類を";
		mes "処理していますので";
		mes "しばらくお待ちください。";
		emotion 4;
		next;
		mes "[？？？]";
		mes "何を言ってるんだ！";
		mes "俺がこいつらより先に来たんだ！";
		cutin "bu_du3",2;
		next;
		cutin "bu_du3",255;
		mes "[出入国管理者]";
		mes "お客様が書類を記入している間に";
		mes "他の方が書類を提出しましたので";
		mes "お客様の順番が後ろに下がって";
		mes "しまったのです。";
		emotion 7;
		next;
		mes "[？？？]";
		mes "何!?　先に来た順番で処理してくれると";
		mes "言ったじゃないか!!";
		cutin "bu_du5",2;
		next;
		cutin "bu_du5",255;
		mes "[出入国管理者]";
		mes "それはそうですが……。";
		next;
		mes "‐はああ！‐";
		next;
		mes "[？？？]";
		mes "痛っ！　なんで殴るんだよ！";
		cutin "bu_du4",2;
		next;
		mes "[？？？]";
		mes "すみません。";
		mes "うちのバカが迷惑をかけました。";
		cutin "bu_mark3",0;
		next;
		mes "[？？？]";
		mes "誰がバカだよ！";
		cutin "bu_du5",2;
		next;
		mes "[？？？]";
		mes "最初にお前が名前を間違って";
		mes "書いたからじゃないか。";
		mes "そんなバカなことをしなければ";
		mes "ここまで待たされなかったはずだろ！";
		cutin "bu_mark3",0;
		next;
		mes "[？？？]";
		mes "マークイシャもマドリドも同じだろ！";
		cutin "bu_du3",2;
		next;
		mes "[マークイシャ]";
		mes "全然違う！";
		mes "どうして15年も一緒にいる";
		mes "友達の名前を間違えるんだ！";
		cutin "bu_mark4",0;
		next;
		mes "[？？？]";
		mes "間違えたんじゃない！";
		mes "わざとやったんだ！";
		mes "マドリドで十分だろ！";
		mes "マドリドで！";
		cutin "bu_du3",2;
		next;
		cutin "bu_du3",255;
		mes "[マークイシャ]";
		mes "ふぅ……バカな友人ですみません。";
		mes "私たちのことは気にしないで";
		mes "お仕事を続けてください。";
		cutin "bu_mark3",0;
		next;
		mes "[？？？]";
		mes "うわああああ！";
		mes "俺を入れろ！";
		mes "いったいいつまで待てばいいんだ！";
		cutin "bu_du5",2;
		next;
		mes "[マークイシャ]";
		mes "静かにしろ!!";
		mes "すみません、すみません。";
		cutin "bu_mark3",0;
		next;
		cutin "bu_mark3",255;
		mes "[出入国管理者]";
		mes "はあ……疲れますね。";
		mes strcharinfo(0)+ "様の";
		mes "一行の書類処理が完了しました。";
		mes "警備兵に話かけると";
		mes "都市に入ることができます。";
		emotion 27;
		next;
		mes "[？？？]";
		mes "……";
		cutin "bu_oliver0",0;
		next;
		cutin "bu_oliver0",255;
		mes "["+strcharinfo(0)+"]";
		mes "(今、誰かいたような……？)";
		next;
		mes "[出入国管理者]";
		mes "そして、テューリアン様の一行が";
		mes "うるさいので早く中に連れて";
		mes "入ってください。";
		emotion 6;
		next;
		mes "[テューリアン]";
		mes "うははは!!";
		mes "見たか!!";
		mes "結局は俺のおかげで早く入ることが";
		mes "できただろ！";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "お前のせいで入るのが遅れたよ……。";
		cutin "bu_mark4",0;
		next;
		mes "[テューリアン]";
		mes "真の男とは過去の事を";
		mes "振り返らないことだ！";
		mes "書類受付は俺が遅れたけど！";
		mes "エクラージュ入場は負けられない！";
		mes "うはははは!!";
		cutin "bu_du2",2;
		next;
		mes "[マークイシャ]";
		mes "……はあ。";
		mes "本当に申し訳ありません。";
		cutin "bu_mark2",0;
		next;
		mes "[？？？]";
		mes "あの……マークさん。";
		mes "テューがもうみえません。";
		cutin "bu_maggi3",2;
		next;
		mes "[マークイシャ]";
		mes "あ……。";
		cutin "bu_mark3",0;
		next;
		mes "[マークイシャ]";
		mes "頭が痛い……。";
		emotion 19,"";
		set ECL_1QUE,2;
		chgquest 11310,11311;
		close2;
		cutin "bu_mark3",255;
		end;
	case 2:
		mes "[出入国管理者]";
		mes "はあ～疲れます。";
		mes strcharinfo(0)+ "様の";
		mes "一行の書類処理が完了しました。";
		mes "警備兵に話かけると";
		mes "都市に入ることができます。";
		emotion 27;
		close;
	default:
		mes "[出入国管理者]";
		mes "はあ……疲れます。";
		mes strcharinfo(0)+ "様の";
		mes "一行の書類処理が完了しました。";
		mes "警備兵に話かけると";
		mes "都市に入ることができます。";
		emotion 27;
		close;
	}
OnInit:
	waitingroom "出入国管理者",0;
	end;
}

//============================================================
// 夢見る作家クエスト
//- Registry -------------------------------------------------
// ECL_2QUE -> 0～28
//------------------------------------------------------------
eclage.gat,101,29,0	script	#ep14_2橋	139,5,5,{
	if(ECL_1QUE == 3 && ECL_2QUE == 0) {
		mes "‐街の奥へと視線を向けると";
		mes "　巨大な木が見えた。";
		mes "　あれが^FF0000ホームツリー^000000のようだ‐";
		next;
		mes "[妖精大工]";
		mes "あ！";
		mes "そこ気を付けてください！";
		emotion 23,"妖精大工#ep14_2";
		set ECL_2QUE,1;
		//setquest 72600;
		//compquest 72600;
		close;
	}
	if(ECL_2QUE == 4) {
		mes "‐橋が壊れていて、とても危険だ。";
		mes "　早く直した方が良いだろう‐";
		set ECL_2QUE,5;
		//setquest 72605;
		//compquest 72605;
		close;
	}
	end;
}

eclage.gat,102,32,4	script	妖精大工#ep14_2	443,{
	switch(ECL_2QUE) {
	case 0:
	case 1:
		mes "[妖精大工]";
		mes "橋の一部が壊れているので";
		mes "気を付けてください。";
		mes "下に落ちてしまいますよ。";
		next;
		switch(select("仕事の内容","橋が壊れた理由","やめる")) {
		case 1:
			mes "[妖精大工]";
			mes "見ての通り大工の仕事をしています。";
			mes "最近はエクラージュに旅行者が増えて";
			mes "以前より橋を作ることに";
			mes "力を入れています。";
			next;
			mes "[妖精大工]";
			mes "ラフィネは飛べるから橋を置く";
			mes "必要はありませんが";
			mes "木に登ったりして落ちる旅行者たちが";
			mes "多くて橋を作っています。";
			close;
		case 2:
			mes "[妖精大工]";
			mes "さきほど、人間が橋の上で";
			mes "走っている途中、バランスを崩して";
			mes "落ちてしまったのですが";
			mes "その時に橋の茎を切って";
			mes "しまったようです。";
			emotion 6;
			next;
			mes "[？？？]";
			mes "おーい！　助けてくれー！";
			next;
			mes "[妖精大工]";
			mes "ここからでは遠すぎて";
			mes "引き上げられません！";
			mes "橋を直すまで待っていてください！";
			next;
			mes "[？？？]";
			mes "お前らは空を飛べるだろう。";
			mes "飛んできて俺を引き上げてくれ！";
			next;
			mes "[妖精大工]";
			mes "無理ですよ。";
			mes "飛んで助けに行こうにも";
			mes "体の大きさが違い過ぎて";
			mes "持ち上げられません！";
			next;
			mes "[？？？]";
			mes "なんだと!?";
			mes "わかった、早く橋を直して";
			mes "助けてくれ！";
			next;
			mes "[妖精大工]";
			mes "はぁ……";
			mes "運悪く入り口の近くなので";
			mes "早く修理をしないと。";
			next;
			mes "[妖精大工]";
			mes "今すぐ、危険だと知らせる標識を";
			mes "設置して、橋を直す材料を受け取って";
			mes "同僚を呼びに行って……。";
			mes "ああ、何を優先しよう……。";
			next;
			if(select("手伝う","やめる") == 2) {
				mes "[妖精大工]";
				mes "橋を修理するまでは危険なので";
				mes "注意して渡ってください。";
				close;
			}
			mes "[妖精大工]";
			mes "本当ですか！";
			mes "手伝ってくれるんですか？";
			mes "……や……優しい……。";
			emotion 23;
			next;
			mes "[妖精大工]";
			mes "まだこの世の中にこんなに優しい方が";
			mes "残っているとは……目から汗が……。";
			emotion 28;
			next;
			mes "[妖精大工]";
			mes "では、わたしの代わりに修理に使う";
			mes "新しい橋の材料を";
			mes "持って来てくれませんか？";
			mes "他の方たちが橋から落ちて";
			mes "怪我でもしたら大変なので";
			mes "今は魔法使って橋を維持させています！";
			next;
			mes "[妖精大工]";
			mes "あと、修理に必要な橋の材料の";
			mes "数を計算しますので、";
			mes "もう一度話しかけてもらっても";
			mes "いいですか？";
			emotion 27;
			set ECL_2QUE,2;
			setquest 11312;
			close;
		case 3:
			mes "[妖精大工]";
			mes "橋を修理するまでは危険なので";
			mes "注意して渡ってください。";
			close;
		}
	case 2:
		mes "[妖精大工]";
		mes "ごめんなさい。";
		mes "今、急いで修理しますので、";
		mes "橋の修理が完了するまで";
		mes "少しお待ちください。";
		next;
		menu "魔法で修理したら？",-;
		mes "[妖精大工]";
		mes "ええ、修理は不可能ではないですが";
		mes "生命創造に関連する魔法は魔力を";
		mes "消耗しちゃうので勝手に使用しては";
		mes "いけないんです。";
		next;
		mes "[妖精大工]";
		mes "以前は橋の材料を必要な分だけ";
		mes "注文すればよかったけど";
		mes "最近は大量生産している";
		mes "既製品を使用しているんです。";
		next;
		mes "[妖精大工]";
		mes "橋の耐久度のためには橋の材料を";
		mes "切断したり、複数の材料を";
		mes "繋げない方がいいけど、";
		mes "既製品は大きさが決まっているので";
		mes "仕方ないですね。";
		next;
		mes "[妖精大工]";
		mes "壊れた橋が……ここからあそこまで";
		mes "19メートルくらいなんです。";
		mes "橋の材料は……";
		emotion 19;
		next;
		mes "[妖精大工]";
		mes "うん……。";
		emotion 19;
		next;
		mes "[妖精大工]";
		mes "それでは、橋の材料を2本";
		mes "貰ってきてください。";
		emotion 5;
		next;
		mes "[妖精大工]";
		mes "都市の外側のタワー近くで";
		mes "働いている^0000FFゴルリ^000000に話をすると";
		mes "新しい橋の材料をくれるはずです。";
		set ECL_2QUE,3;
		chgquest 11312,11313;
		close;
	case 3:
		mes "[妖精大工]";
		mes "都市の外側のタワー近くで";
		mes "働いている［ゴルリ］に話をすると";
		mes "新しい橋の材料をくれるはずです。";
		close;
	case 4:
	case 5:
		mes "[大工フォン]";
		mes "本当にいまだにそんなことで";
		mes "悩んでいるんですか。";
		mes "本当に真面目ですね……。";
		next;
		mes "[大工フォン]";
		mes "あ！　こんなことをしている";
		mes "場合じゃなかった、";
		mes "急いで橋を修理して下に落ちた人も";
		mes "引き揚げないと。";
		next;
		mes "[？？？]";
		mes "おーい！　早くしてくれ！";
		next;
		mes "[テューリアン]";
		mes "ふう！";
		mes "助かった！";
		emotion 23,"";
		emotion 23;
		cutin "bu_du2",2;
		next;
		mes "[テューリアン]";
		mes "木の枝に引っかからなきゃ";
		mes "ヤバかったな。";
		next;
		mes "[マークイシャ]";
		mes "だから、私が気を付けろと";
		mes "言ったじゃないか！";
		mes "いったいどれほどの迷惑が";
		mes "かかったと思っているんだ？";
		cutin "bu_mark3",0;
		next;
		cutin "bu_mark3",255;
		mes "[大工フォン]";
		mes "……";
		emotion 4;
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……";
		emotion 4,"";
		next;
		mes "[テューリアン]";
		mes "あれ！";
		mes "さっきのあいつらじゃないか！";
		mes "お前らが橋を直すのを手伝ったのか？";
		mes "なかなかやるじゃないか！";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "すみません。";
		mes "先ほどから続けてみっともない";
		mes "姿ばかり見せてしまって。";
		cutin "bu_mark1",0;
		next;
		cutin "bu_mark1",255;
		mes "[大工フォン]";
		mes "今回は見なかったことに";
		mes "しますけど";
		mes "次に橋を壊したら";
		mes "監獄に入れますからね！";
		mes "私も暇ではないのですから。";
		emotion 6;
		next;
		mes "[マークイシャ]";
		mes "すみません。";
		mes "私の方から十分に注意をしておくので";
		mes "心配しないでください。";
		cutin "bu_mark1",0;
		next;
		mes "[テューリアン]";
		mes "だけど、少し走っただけなのに";
		mes "橋が壊れるなんて……";
		mes "耐久度に問題があるんじゃないか？";
		mes "これじゃあ巨人たちはエクラージュに";
		mes "来ることが……。";
		cutin "bu_du3",2;
		next;
		cutin "bu_du3",255;
		mes "‐テューリアンが橋の手すりに";
		mes "　手を置いた瞬間。";
		mes "　手すりが真っ二つに";
		mes "　引きちぎれてしまった‐";
		emotion 23;
		emotion 23,"";
		next;
		mes "[大工フォン]";
		mes "……";
		emotion 57;
		next;
		mes "[マークイシャ]";
		mes "あ……。";
		cutin "bu_mark4",0;
		next;
		mes "[？？？]";
		mes "あ……。";
		cutin "bu_maggi3",2;
		next;
		mes "[テューリアン]";
		mes "はあ……。";
		cutin "bu_du1",2;
		next;
		mes "[テューリアン]";
		mes "違う！　今回は本当に誤解だ！";
		mes "これを見ろ！";
		mes "ここの案内にも橋の上では危ないから";
		mes "手すりにつかまってくださいと";
		mes "書いてあるじゃないか。";
		cutin "bu_du5",2;
		next;
		mes "[テューリアン]";
		mes "俺は軽く手を置いただけなんだよ！";
		mes "俺は悪くない！";
		next;
		cutin "bu_du5",255;
		mes "[大工フォン]";
		mes "……";
		emotion 9;
		next;
		mes "[大工フォン]";
		mes "あ……";
		emotion 6;
		next;
		mes "[大工フォン]";
		mes "うああああ……";
		mes "……。";
		emotion 23;
		next;
		mes "[大工フォン]";
		mes "早く行けこのトラブルメーカー！";
		emotion 23;
		next;
		mes "[マークイシャ]";
		mes "本当にすみません。";
		mes "この後にこいつを何処かにおいてから";
		mes "仕事を手伝いに来ます。";
		cutin "bu_mark1",0;
		next;
		cutin "bu_mark3",255;
		mes "[大工フォン]";
		mes "来るな！";
		mes "もう二度と来るな！";
		emotion 23;
		next;
		mes "[大工フォン]";
		mes "あ～あ……";
		mes "今日こそ仕事を終わらせて友達に";
		mes "会いに行こうと思ってたのに……。";
		mes "今日も徹夜確定じゃないか";
		emotion 57;
		next;
		mes "[大工フォン]";
		mes "酷く壊れてはないから";
		mes "何とか修理は出来るけど……。";
		mes "はあ……。";
		emotion 28;
		next;
		mes "[大工フォン]";
		mes strcharinfo(0)+ "様は";
		mes "もう^FF0000ホームツリー^000000に行ってください。";
		mes "この道をまっすぐ都市の方に";
		mes "向かって北東側に行けば着きます。";
		emotion 54;
		next;
		mes "[大工フォン]";
		mes "ホームツリーに入るとすぐ目の前に";
		mes "広場がでるけど、そこには人々が";
		mes "いっぱい集まっているので";
		mes "情報を得るにはいいと思います。";
		next;
		mes "[大工フォン]";
		mes "そして、ホームツリーの入口にいる";
		mes "友達のグラシスに今日はいけないと";
		mes "伝えてくれませんか？";
		next;
		mes "[大工フォン]";
		mes "もうすぐ友達の誕生日なので";
		mes "みんなで集まることに";
		mes "なっていたのですが";
		mes "友達を待たせるわけには";
		mes "いきませんから……";
		mes "お願いします。";
		emotion 17;
		delitem 6553,2;
		viewpoint 1,283,275,0,0xFF0000;
		set ECL_2QUE,6;
		chgquest 11314,11315;
		close;
	case 6:
		mes "[大工フォン]";
		mes "ホームツリーの入口にいる";
		mes "友達のグラシスに今日はいけないと";
		mes "伝えてくれませんか？";
		next;
		mes "[大工フォン]";
		mes "もうすぐ友達の誕生日なので";
		mes "みんなで集まることに";
		mes "なっていたのですが";
		mes "友達を待たせるわけには";
		mes "いかないのでお願いします。";
		viewpoint 1,283,275,0,0xFF0000;
		emotion 17;
		close;
	default:
		mes "[大工フォン]";
		mes "早く友達に会いたいです。";
		emotion 28;
		close;
	}
OnInit:
	waitingroom "夢見る作家",0;
	end;
}

ecl_fild01.gat,201,91,4	script	ゴルリ	442,{
	switch(ECL_2QUE) {
	case 3:
		mes "[ゴルリ]";
		mes "生命は自然が作り出した";
		mes "最も美しい発明であり、";
		mes "死は、より多くの生命を";
		mes "得るためのものだという。";
		next;
		mes "[ゴルリ]";
		mes "魔法で栽培されたこの種に";
		mes "生命はあるのだろうか。";
		mes "魔法で育てた橋が壊れても";
		mes "死と呼べるのだろうか。";
		next;
		mes "[ゴルリ]";
		mes "長い時間をかけて種を育て";
		mes "橋を作って来たが";
		mes "簡単に作られ簡単に壊れる";
		mes "今の橋の姿は私を悩ませる。";
		next;
		mes "[ゴルリ]";
		mes "これもまた時代の流れなのか……。";
		mes "なぜ私はこのような運命を持った物を";
		mes "作り出したのだろう。";
		next;
		mes "[ゴルリ]";
		mes "この種は私の名前をとって";
		mes "［ゴルリアット]と呼んでいる。";
		next;
		mes "[ゴルリ]";
		mes "土に植えると二つの茎に";
		mes "ひとつの葉っぱが出るという";
		mes "不思議な姿で成長するから";
		mes "橋の材料として利用している";
		mes "植物なのだ。";
		next;
		mes "[ゴルリ]";
		mes "ゴルリアットのお蔭で橋の材料が";
		mes "足りない問題は解決されたが";
		mes "自然の力を無視してしまった。";
		mes "この魔法がいつか恐ろしい結果を";
		mes "招くのではないかと心配している。";
		next;
		mes "[ゴルリ]";
		mes "最近はフィリー様の仕事を手伝いながら";
		mes "少しずつ元気を取り戻してはいるが";
		mes "いつかはこの間違いを";
		mes "正していくつもりなんだ。";
		next;
		mes "[ゴルリ]";
		mes "君も心身が疲れている時は";
		mes "フィリー様と話をしてみるがいい";
		mes "新しい何かを得ることになるから。";
		mes "そして……うむ……。";
		mes "ちょっと話している間に";
		mes "橋の材料が完成したようだ。";
		next;
		mes "[ゴルリ]";
		mes "では、この橋の材料を";
		mes "フォンに渡してやってくれ。";
		mes "あと、大変なのは分かるけど";
		mes "もう少し橋を大事にしてくれと";
		mes "伝えてくれないか？";
		next;
		if(checkitemblank() == 0) {
			mes "[ゴルリ]";
			mes "おや、ずいぶんと荷物が多いな。";
			mes "まずは荷物を減らしてきて";
			mes "くれないか？";
			close;
		}
		mes "[ゴルリ]";
		mes "私もフィリー様の仕事を";
		mes "お手伝いしているので";
		mes "頻繁に橋が壊れると体が持たないよ。";
		getitem 6553,2;
		set ECL_2QUE,4;
		chgquest 11313,11314;
		close;
	case 4:
	case 5:
		mes "[ゴルリ]";
		mes "では、この橋の材料を";
		mes "フォンに渡してやってくれ。";
		mes "あと、大変なのは分かるけど";
		mes "もう少し橋を大事にしてくれと";
		mes "伝えてくれないか？";
		next;
		mes "[ゴルリ]";
		mes "私もフィリー様の仕事を";
		mes "お手伝いしているので";
		mes "頻繁に橋が壊れると体が持たなくなる。";
		close;
	default:
		mes "[ゴルリ]";
		mes "一本のエルダーウィローを育てるために";
		mes "春からペコペコは泣いたようだ。";
		next;
		mes "[ゴルリ]";
		mes "一本のエルダーウィローを育てるために";
		mes "アラームは時計塔の中で泣いたようだ。";
		next;
		mes "[ゴルリ]";
		mes "ミッドガルドから来たバードが";
		mes "聞かせてくれた歌なんだよ。";
		next;
		mes "[ゴルリ]";
		mes "もし、君も知っている歌があるなら";
		mes "ぜひ聞いて見たい。";
		close;
	}
}

eclage.gat,283,275,4	script	グラシス	438,{
	switch(ECL_2QUE) {
	case 6:
		mes "[グラシス]";
		mes "う～ん……。";
		mes "みんな遅いな。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "あのすみません……。";
		next;
		mes "[グラシス]";
		mes "はい？";
		next;
		mes "[グラシス]";
		mes "はぁ～……";
		next;
		mes "[グラシス]";
		mes "あの……";
		mes "そういうのは困ります……。";
		emotion 16,"";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "違います。そうじゃなくて……。";
		emotion 4,"";
		next;
		mes "[グラシス]";
		mes "はあ……。";
		mes "私にはお付き合いしてる方が";
		mes "いますから……。";
		next;
		mes "[グラシス]";
		mes "こうして外に出れば";
		mes "いつも私の美貌の虜になった男が";
		mes "寄ってくるのよね……。";
		mes "だから外に出るのは嫌なのに……。";
		mes "美しすぎるって罪なのね。";
		mes "ああ、なんて可哀そうな私……。";
		emotion 6;
		emotion 19,"";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "そうじゃなくて……。";
		mes "フォンさんが徹夜で来れないと思うので";
		mes "それを伝えてくれと……。";
		next;
		mes "[グラシス]";
		mes "……";
		emotion 9;
		next;
		mes "[グラシス]";
		mes "あ、はい……。";
		next;
		mes "[グラシス]";
		mes "穴があったら入りたい……。";
		emotion 9;
		next;
		mes "[グラシス]";
		mes "……えっと";
		mes "それは本当ですか？";
		mes "フォンが来れないんですか？";
		emotion 23;
		next;
		mes "[グラシス]";
		mes "モレンの誕生日がもうすぐなのに";
		mes "こんなにみんなが集まらないと";
		mes "本当に最悪の誕生日パーティに";
		mes "なるかもしれません。";
		next;
		mes "[グラシス]";
		mes "モレンの誕生日だからと";
		mes "スプレンディッドから飛んできた";
		mes "ユッブもいるのに……。";
		mes "あれ、そういえばユッブは";
		mes "何処に行ったのかしら。";
		emotion 23;
		next;
		mes "[グラシス]";
		mes "自分の家の前で集まろうと";
		mes "言っていたのに！";
		mes "せめて、いなくなる前に家の扉は";
		mes "開けていってくれないと！";
		emotion 23;
		next;
		mes "[グラシス]";
		mes "他の友達が来るかも知れませんから";
		mes "私はここを動けません。";
		mes "もし冒険者様がミカンのへたのような";
		mes "頭をしている妖精を見かけたら";
		mes "グラシスが探していると";
		mes "伝えてください。";
		next;
		mes "[グラシス]";
		mes "そして、早く扉を開けてくれないと";
		mes "へたを取ってしまうと伝えてください。";
		next;
		mes "[テューリアン]";
		mes "わかった！";
		mes "その頼み！";
		mes "俺が力になってやる！";
		emotion 23;
		emotion 23,"";
		cutin "bu_du1",2;
		next;
		cutin "bu_du1",255;
		mes "["+strcharinfo(0)+"]";
		mes "？？？";
		next;
		mes "[マークイシャ]";
		mes "おい！　他人の話に";
		mes "勝手に割り込むなと言っただろ！";
		cutin "bu_mark3",0;
		next;
		mes "[テューリアン]";
		mes "何を言っているんだ！";
		mes "助けが必要なら場所を選ばずに";
		mes "飛んで行くのが勇者の仕事だ！";
		cutin "bu_du2",2;
		next;
		mes "[テューリアン]";
		mes "そして、お前！";
		mes "さっきからよく会うけど";
		mes "何かの縁を感じるな！";
		cutin "bu_du1",2;
		next;
		mes "[テューリアン]";
		mes "よし！　決めた！ ";
		cutin "bu_du2",2;
		next;
		mes "[テューリアン]";
		mes "普段は簡単に認めたりしないんだけど";
		mes "お前は俺のライバルとして認めてやる！";
		mes "今回の勝負は！";
		mes "ここにいるチビ妖精のグラツスを";
		mes "手伝うのだ！";
		next;
		cutin "bu_du2",255;
		mes "[グラシス]";
		mes "誰がチビですか……。";
		mes "それに名前も";
		mes "間違ってるじゃない……。";
		emotion 6;
		next;
		mes "[テューリアン]";
		mes "とにかく！";
		mes "先にユッブとかいうのを";
		mes "連れてきた方が勝ちだ！";
		mes "わかったな！";
		cutin "bu_du2",2;
		next;
		mes "[テューリアン]";
		mes "では！";
		mes "ミカンのへたを探しに出発だ！";
		mes "みんな、行くぞ！";
		next;
		mes "[？？？]";
		mes "……（こくっ）";
		cutin "bu_alp1",0;
		next;
		mes "[？？？]";
		mes "いきなり人の話に割り込むのは";
		mes "どうかと思いますけど……";
		mes "人助けになるなら賛成です！";
		cutin "bu_maggi2",2;
		next;
		mes "[マークイシャ]";
		mes "まったく……";
		mes "お前なんで人の話を";
		mes "聞こうとしないんだ。";
		cutin "bu_mark4",0;
		next;
		mes "[？？？]";
		mes "あの、マークさん。";
		mes "テューが先に行っちゃいました……。";
		cutin "bu_maggi3",2;
		next;
		mes "[マークイシャ]";
		mes "あいつ……。";
		mes "仕方ない、早く追いかけるぞ！";
		cutin "bu_mark3",0;
		next;
		cutin "bu_mark3",255;
		mes "[グラシス]";
		mes "……行ってしまいましたね。";
		mes "まあ、いいです。";
		mes "早くユッブを連れてきて下さいね。";
		viewpoint 2,283,275,0,0xFF0000;
		viewpoint 1,191,200,0,0xFF0000;
		set ECL_2QUE,7;
		chgquest 11315,11316;
		close;
	case 7:
		mes "[グラシス]";
		mes "他の友達が来るかも知れませんから";
		mes "私はここを動けません。";
		mes "もし冒険者様がミカンのへたのような";
		mes "頭をしている妖精を見かけたら";
		mes "グラシスが探していると";
		mes "伝えてください。";
		next;
		mes "[グラシス]";
		mes "そして、早く扉を開けてくれないと";
		mes "へたを取ってしまうと伝えてください。";
		emotion 23;
		viewpoint 1,191,200,0,0xFF0000;
		close;
	case 8:
		mes "[グラシス]";
		mes "ん……";
		mes "モレンの歳ですか？";
		next;
		mes "[グラシス]";
		mes "う～ん、私と30歳くらい";
		mes "差があったと思うけど……。";
		emotion 20;
		next;
		menu "では、グラシスの歳は？",-;
		mes "[グラシス]";
		mes "女性に歳を聞くのは失礼です！";
		mes "ミュラーならモレンの歳が";
		mes "わかるかもしれませんから";
		mes "ミュラーに聞いてください。";
		emotion 23;
		next;
		mes "[グラシス]";
		mes "ミュラーはエクラージュの広場にいます。";
		viewpoint 2,283,275,0,0xFF0000;
		viewpoint 1,299,309,0,0xFF0000;
		set ECL_2QUE,9;
		chgquest 11317,11318;
		close;
	case 9:
		mes "[グラシス]";
		mes "女性に歳を聞くのは失礼です！";
		mes "ミュラーならモレンの歳が";
		mes "わかるかもしれませんから";
		mes "ミュラーに聞いてください。";
		emotion 23;
		next;
		mes "[グラシス]";
		mes "ミュラーはエクラージュの広場にいます。";
		viewpoint 1,299,309,0,0xFF0000;
		close;
	case 10:
		mes "[グラシス]";
		mes "シュルは街の東の方に住んでいます。";
		mes "たぶん、家の近くにいるはずです。";
		viewpoint 1,265,166,0,0xFF0000;
		close;
	case 11:
		mes "[グラシス]";
		mes "タトは街の西にいます。";
		viewpoint 1,137,169,0,0xFF0000;
		close;
	case 12:
		mes "[グラシス]";
		mes "エクラージュには王様が住んでいます。";
		mes "本当にかっこいいんですよ。";
		mes "ふふふ";
		emotion 40;
		close;
	case 13:
		mes "[グラシス]";
		mes "そういえばフォンとゴルリの所に";
		mes "行って見ないといけないなのに……。";
		mes "後で行ってみます。";
		close;
	case 14:
		mes "[グラシス]";
		mes "あ！";
		mes "このロウソクを全て挿すためには";
		mes "とても大きなケーキが必要ですね……。";
		emotion 23;
		next;
		mes "[グラシス]";
		mes "う～ん……";
		mes "では、みんな忙しそうなので";
		mes "みんなを集めるのは諦めて";
		mes "私はロウソクにあいそうな";
		mes "ケーキでも焼きにいきます。";
		next;
		mes "[グラシス]";
		mes "この道を下ると";
		mes "モレンの家があるので";
		mes "何かほしい物があるか";
		mes "聞いてきてください。";
		next;
		mes "[？？？]";
		mes "おーい！";
		next;
		mes "[グラシス]";
		mes "あれ、誰かがこっちに向かって";
		mes "走ってきますね。";
		next;
		mes "[グラシス]";
		mes "あ！　あの人たちは……。";
		next;
		mes "[テューリアン]";
		mes "チビお嬢さん！";
		mes "俺がユッブという奴を持って来た！";
		emotion 23;
		emotion 23,"";
		cutin "bu_du2",2;
		next;
		mes "[？？？]";
		mes "はぁはぁ……";
		mes "テュー、走るの速いよ……。";
		cutin "bu_maggi4",0;
		next;
		mes "[？？？]";
		mes "……";
		cutin "bu_alp2",2;
		next;
		mes "[マークイシャ]";
		mes "はぁ……";
		mes "まさかユッブさんを見つけた瞬間";
		mes "ユッブさんを抱えて";
		mes "走りだすなんて……。";
		cutin "bu_mark3",0;
		next;
		cutin "bu_mark3",255;
		mes "[グラシス]";
		mes "……";
		emotion 9;
		next;
		mes "["+strcharinfo(0)+"]";
		mes "……";
		emotion 9,"";
		next;
		mes "[ユッブ]";
		mes "何だ、このバカは！";
		mes "早くオレをおろせ！";
		cutin "war_y1",2;
		next;
		cutin "war_y1",255;
		mes "[グラシス]";
		mes "私の友達を荷物扱いしないでくれる？";
		mes "それに、もう遅いです！";
		emotion 6;
		next;
		mes "[テューリアン]";
		mes "何!?";
		mes "あっちは二人じゃないか！";
		mes "俺の方が不利だ！";
		cutin "bu_du3",2;
		next;
		mes "[マークイシャ]";
		mes "私たちは四人だぞ……。";
		cutin "bu_mark2",0;
		next;
		cutin "bu_mark2",255;
		mes "["+strcharinfo(0)+"]";
		mes "二人？";
		emotion 1,"";
		next;
		mes "[テューリアン]";
		mes "何を言っているんだ。";
		mes "都市の入口からあのチビを";
		mes "連れていただろ。";
		cutin "bu_du1",2;
		next;
		cutin "bu_du1",255;
		mes "["+strcharinfo(0)+"]";
		mes "え!?";
		emotion 1,"";
		next;
		mes "[テューリアン]";
		mes "少し可愛いけど俺たちには";
		mes "マギがいるから負けない！";
		mes "マギは凄く可愛いからな！";
		cutin "bu_du3",2;
		next;
		mes "[マギスティン]";
		mes "……";
		cutin "bu_maggi1",2;
		next;
		cutin "bu_maggi1",255;
		mes "[？？？]";
		mes "……";
		cutin "bu_oliver0",0;
		next;
		mes "[？？？]";
		mes "僕が見える？";
		emotion 23,"";
		cutin "bu_oliver3",0;
		next;
		mes "[テューリアン]";
		mes "何を言っているんだ！";
		mes "そんなに目立つ服を着ているくせに。";
		mes "どこで買った！";
		cutin "bu_du1",2;
		next;
		mes "[？？？]";
		mes "え……。";
		mes "僕は見えないと思ったのに";
		mes "違ったのかな？";
		cutin "bu_oliver2",0;
		next;
		mes "[テューリアン]";
		mes "見えないわけないだろ。";
		mes "うちのアルプ見たいに";
		mes "クローキングでも使うなら別だけど！";
		mes "ギロチンクロスだか何だか知らないけど";
		mes "アルプはスキルを使っていなくても";
		mes "本当に見えないような気がするんだ！";
		cutin "bu_du2",2;
		next;
		cutin "bu_du2",255;
		mes "[グラシス]";
		mes "ただ存在感がないだけじゃない？";
		emotion 9;
		next;
		mes "[アルプオカート]";
		mes "……";
		cutin "bu_alp3",2;
		next;
		mes "[アルプオカート]";
		mes "そういえば何処かで";
		mes "見た事がある……。";
		mes "何処だったか……。";
		cutin "bu_alp1",2;
		next;
		mes "[？？？]";
		mes "凄い……";
		mes "こんなにリアルな夢は始めてだ……。";
		cutin "bu_oliver2",0;
		next;
		mes "[テューリアン]";
		mes "わははははは！";
		mes "夢だってさ！";
		mes "こいつ、まだ夢から";
		mes "さめてないみたいだぞ！";
		mes "本当に可愛いな！";
		mes "俺たちが連れて歩いたらダメか？";
		cutin "bu_du2",2;
		next;
		mes "[マークイシャ]";
		mes "何を言っているんだ！";
		mes "勝手に触るな！";
		cutin "bu_mark3",0;
		next;
		mes "[オリバー]";
		mes "うえ～嫌だ～。";
		mes "それに僕はチビでもない！";
		mes "オリバーという立派な名前がある！";
		cutin "bu_oliver5",0;
		next;
		mes "[テューリアン]";
		mes "あっさり断られた……。";
		mes "マギと一緒にいれば";
		mes "より一層可愛いはずなのに。";
		cutin "bu_du5",2;
		next;
		mes "[テューリアン]";
		mes "仕方ない。";
		mes "モレンを探しに行くぞ！";
		mes "今度こそ負けないからな！";
		mes "出発！";
		delitem 6555,128;
		set ECL_2QUE,15;
		chgquest 11323,11324;
		next;
		cutin "bu_du5",255;
		mes "[グラシス]";
		mes "何なのかしらあの人たち……。";
		mes "ユッブもそのまま連れて行って";
		mes "しまってるじゃない……。";
		emotion 4;
		next;
		mes "[グラシス]";
		mes "まあ……それはユッブが";
		mes "何とかするでしょうけど。";
		mes "とにかく……この道を下ると";
		mes "モレンの家があるので";
		mes "何かほしい物があるか";
		mes "聞いてきてくれませんか？";
		viewpoint 2,283,275,0,0xFF0000;
		viewpoint 1,266,216,0,0xFF0000;
		close;
	case 15:
		mes "[グラシス]";
		mes "何なのかしらあの人たち……。";
		mes "ユッブもそのまま連れて行って";
		mes "しまってるじゃない……。";
		emotion 4;
		next;
		mes "[グラシス]";
		mes "まあ……それはユッブが";
		mes "何とかするだろうけど。";
		mes "とにかく……この道を下ると";
		mes "モレンの家があるので";
		mes "何かほしい物があるか";
		mes "聞いてきてくれませんか？";
		close;
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
		mes "[グラシス]";
		mes "う～ん、クリームはチョコがいいかな？";
		mes "生クリームがいいかな？";
		emotion 40;
		next;
		mes "‐ケーキ作りに夢中になっている。";
		mes "　ジャマはしないようにしよう‐";
		close;
	case 21:
		mes "[グラシス]";
		mes "う～ん、クリームはチョコがいいかな？";
		mes "生クリームがいいかな？";
		emotion 40;
		next;
		mes "[グラシス]";
		mes "あら、お帰りなさい。";
		mes "モレンが何を欲しがっているのか";
		mes "わかりましたか？";
		next;
		mes "[グラシス]";
		mes "……";
		emotion 9;
		next;
		mes "[グラシス]";
		mes "えええ!?";
		mes "巨大な鳥の伝説!?";
		mes "モレンと知り合って100年近いけど";
		mes "そんな話は聞いたことないよ！";
		emotion 23;
		next;
		mes "[グラシス]";
		mes "出発前に送別パーティも";
		mes "しないといけないし……。";
		mes "すぐにでも出発するなら";
		mes "早く止めないと！";
		next;
		mes "[グラシス]";
		mes "こんな急に……";
		mes "私はモレンの話を少し聞いてみるので";
		mes "ユッブにも相談してみてくれませんか？";
		mes "何か探すものがあると言って";
		mes "家に入っていったので";
		mes "まだ中にいるはずです。";
		emotion 19;
		viewpoint 2,283,275,0,0xFF0000;
		viewpoint 1,292,265,0,0xFF0000;
		set ECL_2QUE,22;
		chgquest 11330,11331;
		close;
	case 22:
		mes "[グラシス]";
		mes "出発前に送別パーティも";
		mes "しないといけないし……。";
		mes "すぐにでも出発するなら";
		mes "早く止めないと！";
		next;
		mes "[グラシス]";
		mes "こんな急に…";
		mes "私はモレンの話を少し聞いてみるので";
		mes "ユッブにも相談してみてくれませんか？";
		mes "何か探すものがあると言って";
		mes "家に入っていたので";
		mes "まだ中にいるはずです。";
		emotion 19;
		close;
	case 23:
		mes "[グラシス]";
		mes "モレンがミッドガルドに行くので";
		mes "凄く寂しいです……。";
		mes "ユッブがスプレンディッド部隊に";
		mes "行く時もこんな気分だったのに……。";
		next;
		mes "[グラシス]";
		mes "まずはお土産に";
		mes "何を買ってきて貰うか";
		mes "決めようと思います！";
		emotion 21;
		close;
	default:
		mes "[グラシス]";
		mes "う～ん……。";
		mes "みんな遅いな。";
		mes "最近、エクラージュに入って来る";
		mes "人の人数だけみても";
		mes "忙しいのは予想できるけど……。";
		next;
		mes "[グラシス]";
		mes "私はなんで暇なんだろ……。";
		mes "どうして私だけ？";
		emotion 23;
		close;
	}
}

eclage.gat,191,200,4	script	ユッブ	446,{
	switch(ECL_2QUE) {
	case 7:
		mes "‐コソコソ‐";
		next;
		mes "‐グラシスが話していた妖精のようだ‐";
		next;
		mes "[ユッブ]";
		mes "ん？　誰だ！";
		emotion 23;
		cutin "war_y1",2;
		next;
		menu "グラシスの話を伝える。",-;
		mes "[ユッブ]";
		mes "誕生日のロウソクを作る材料を";
		mes "見つけに行くと言ったのに";
		mes "やはり聞いてなかったようだな。";
		mes "あいつは鏡を見ていると";
		mes "何も聞かなくなるからな。";
		emotion 54;
		cutin "war_y3",2;
		next;
		mes "[ユッブ]";
		mes "そういえばモレンは何歳だったかな。";
		mes "オレが132歳だから";
		mes "オレよりは若かったと思うけど";
		mes "思い出せない……。";
		next;
		mes "[ユッブ]";
		mes "おい、グラシスの所に戻って";
		mes "扉を開けてやるついでに";
		mes "モレンの歳も聞いてきてくれないか？";
		viewpoint 2,191,200,0,0xFF0000;
		viewpoint 1,283,275,0,0xFF0000;
		set ECL_2QUE,8;
		chgquest 11316,11317;
		close2;
		cutin "war_y3",255;
		end;
	case 8:
		mes "[ユッブ]";
		mes "そういえばモレンは何歳だったかな。";
		mes "オレが132歳だから";
		mes "オレよりは若かったと思うけど";
		mes "思い出せない……。";
		next;
		mes "[ユッブ]";
		mes "おい、グラシスの所に戻って";
		mes "扉を開けてやるついでに";
		mes "モレンの歳も聞いてきてくれないか？";
		cutin "war_y3",2;
		viewpoint 2,191,200,0,0xFF0000;
		viewpoint 1,283,275,0,0xFF0000;
		close2;
		cutin "war_y3",255;
		end;
	case 9:
		mes "[ユッブ]";
		mes "ミュラー？";
		mes "ミュラーはエクラージュの広場に";
		mes "いるはずだ。";
		cutin "war_y4",2;
		viewpoint 1,299,309,0,0xFF0000;
		close2;
		cutin "war_y4",255;
		end;
	case 10:
		mes "[ユッブ]";
		mes "シュル？";
		mes "シュルは街の東側にいるはずだ。";
		cutin "war_y4",2;
		viewpoint 1,265,166,0,0xFF0000;
		close2;
		cutin "war_y4",255;
		end;
	case 11:
		mes "[ユッブ]";
		mes "タト？";
		mes "タトは街の西側にいるはずだ。";
		cutin "war_y4",2;
		viewpoint 1,137,169,0,0xFF0000;
		close2;
		cutin "war_y4",255;
		end;
	case 12:
		mes "[ユッブ]";
		mes "はあ!?";
		mes "みんなモレンが何歳なのか";
		mes "知らないのか!?";
		emotion 23;
		cutin "war_y3",2;
		next;
		mes "[ユッブ]";
		mes "う～ん、それでもみんなから";
		mes "聞いた話をまとめて見ると……。";
		next;
		mes "[ユッブ]";
		mes "132歳のオレより年下で";
		mes "98歳のミュラーより年上。";
		mes "グラシスとは30歳違って、";
		mes "グラシスはシュルの2歳年下。";
		mes "シュルはタトより14歳年上で";
		mes "タトが146歳だということだな？";
		emotion 9;
		emotion 9,"";
		cutin "war_y2",2;
		next;
		mes "[ユッブ]";
		mes "132 > モレン";
		mes "モレン > 98";
		mes " |モレン - グラシス| = 30";
		mes "グラシス = シュル - 2";
		mes "シュル = タト + 14";
		mes "タト = 146";
		next;
		mes "[ユッブ]";
		mes "ってことだよな？";
		mes "それだと何歳になるんだ？";
		emotion 1;
		cutin "war_y3",2;
		next;
		input '@str$;
		if('@str$ != "128") {
			mes "[ユッブ]";
			mes "ん～違うんじゃないか？";
			mes "もっと良く考えて見ろ。";
			cutin "war_y2",2;
			close2;
			cutin "war_y2",255;
			end;
		}
		mes "[ユッブ]";
		mes "そう！";
		mes "それだ！";
		mes "今、思い出した！";
		mes "そうだったような気がする。";
		emotion 5;
		cutin "war_y4",2;
		next;
		mes "[ユッブ]";
		mes "つまりロウソクを100個以上";
		mes "作らないといけないのか……。";
		emotion 16;
		cutin "war_y3",2;
		next;
		mes "[ユッブ]";
		mes "お前、暇ならロウソク作りに使う";
		mes "ほこりの塊を少し集めて来てくれよ。";
		mes "今持っているほこりの塊だけじゃ";
		mes "足りないんだ。";
		mes "そうだな……^FF00008個^000000あれば";
		mes "足りるかな。";
		next;
		mes "[ユッブ]";
		mes "ほこりの塊はビフロストタワーの中にいる";
		mes "^FF0000チェネレ^000000を倒すと手に入るからな。";
		mes "よろしく頼んだぞ。";
		set ECL_2QUE,13;
		chgquest 11321,11322;
		close2;
		cutin "war_y3",255;
		end;
	case 13:
		if(countitem(6561) < 8) {
			mes "[ユッブ]";
			mes "お前、暇ならロウソク作りに使う";
			mes "ほこりの塊を少し集めて来てくれよ。";
			mes "今持っているほこりの塊だけじゃ";
			mes "足りないんだ。";
			mes "そうだな……^FF00008個^000000あれば";
			mes "足りるかな。";
			cutin "war_y3",2;
			next;
			mes "[ユッブ]";
			mes "ほこりの塊はビフロストタワーの中にいる";
			mes "^FF0000チェネレ^000000を倒すと手に入るからな。";
			mes "よろしく頼んだぞ。";
			close2;
			cutin "war_y3",255;
			end;
		}
		mes "[ユッブ]";
		mes "へー！";
		mes "もう全部集めて来たのか。";
		mes "オレもロウソクの芯を";
		mes "全部作り終わったところだ！";
		emotion 2;
		cutin "war_y4",2;
		next;
		if(checkitemblank() == 0) {
			mes "[ユッブ]";
			mes "ずいぶんと荷物が多いな。";
			mes "少し荷物を減らしてから";
			mes "また来いよ。";
			close2;
			cutin "war_y4",255;
			end;
		}
		delitem 6561,8;
		getitem 6555,128;
		set ECL_2QUE,14;
		chgquest 11322,11323;
		mes "[ユッブ]";
		mes "ほこりの塊をこうして芯を刺すと！";
		mes "出来上がり！";
		next;
		mes "[ユッブ]";
		mes "これで全部完成だ！";
		mes "これをグラシスに渡してくれ。";
		next;
		mes "[ユッブ]";
		mes "あと……";
		mes "手伝ってくれた礼に";
		mes "オレの家を貸してやるよ！";
		mes "エクラージュにいる間は";
		mes "好きなだけ使ってもいいぞ。 ";
		emotion 21;
		next;
		mes "[ユッブ]";
		mes "オレはスプレンディッドで";
		mes "仕事をしているから";
		mes "エクラージュに戻って来ることも";
		mes "少ないしな。";
		next;
		mes "[ユッブ]";
		mes "確か、今は鍵がかかっているはずだから";
		mes "お前がグラシスと話している間に";
		mes "鍵を開けておいてやるよ。";
		mes "じゃあ、頼んだぞ。";
		viewpoint 2,191,200,0,0xFF0000;
		viewpoint 1,283,275,0,0xFF0000;
		viewpoint 1,292,265,1,0x00FF00;
		close2;
		cutin "war_y4",255;
		end;
	case 14:
		mes "[ユッブ]";
		mes "どうしたんだ?!";
		mes "早くそのロウソクを";
		mes "グラシスに渡してくれ。";
		viewpoint 1,283,275,0,0xFF0000;
		close2;
		cutin "war_y4",255;
		end;
	case 15:
	case 16:
	case 17:
		mes "[ユッブ]";
		mes "ヨトゥンヘイムに行って見たか？";
		mes "そこはとても大きな巨人たちが";
		mes "住んでいるんだ。";
		cutin "war_y4",2;
		close2;
		cutin "war_y4",255;
		end;
	default:
		mes "‐コソコソ‐";
		next;
		mes "‐何かをしている。";
		mes "　ジャマしないようにしよう‐";
		close;
	}
}

ecl_in01.gat,73,51,4	script	ミュラー	442,{
	switch(ECL_2QUE) {
	case 9:
		mes "[ミュラー]";
		mes "モレンの歳ですか？";
		mes "正確には分かりませんが……。";
		mes "私よりは年上ですよ。";
		next;
		mes "[ミュラー]";
		mes "私の歳ですか？";
		mes "私は98歳です。";
		next;
		mes "[ミュラー]";
		mes "そうだ！　シュルに聞いてみたら";
		mes "分かるかもしれません。";
		next;
		mes "[ミュラー]";
		mes "シュルの家は街の東側の奥にあります。";
		emotion 52;
		set ECL_2QUE,10;
		chgquest 11318,11319;
		close;
	case 10:
		mes "[ミュラー]";
		mes "シュルの家は街の東側の奥にあります。";
		emotion 52;
		close;
	default:
		mes "[ミュラー]";
		mes "う～ん……何をプレゼントすれば";
		mes "凄いと噂されるかな？";
		emotion 52;
		close;
	}
}

eclage.gat,265,166,4	script	シュル	443,{
	switch(ECL_2QUE) {
	case 10:
		mes "[シュル]";
		mes "モレンの歳？";
		mes "う～ん、何歳だっただろう。";
		mes "歳は数えなくなって";
		mes "かなり時間が経っているから。";
		mes "グラシスが私より2歳";
		mes "若かったのは覚えているよ。";
		emotion 20;
		next;
		mes "[シュル]";
		mes "もしかしたら……";
		mes "タトなら覚えているんじゃないかな？";
		next;
		mes "[シュル]";
		mes "タトは街の西に住んでいるから";
		mes "行って聞いて見て。";
		viewpoint 1,137,169,0,0xFF0000;
		set ECL_2QUE,11;
		chgquest 11319,11320;
		close;
	case 11:
		mes "[シュル]";
		mes "タトは街の西に住んでいるから";
		mes "行って聞いて見て。";
		viewpoint 1,137,169,0,0xFF0000;
		close;
	default:
		mes "[シュル]";
		mes "ラフィネは美しいヤイを建てることに";
		mes "自分の命をかけるくらいに大事だと";
		mes "考えている。";
		mes "私もラフィネだけど";
		mes "理解しにくい部分なんだ。";
		close;
	}
}

eclage.gat,137,169,4	script	タト	439,{
	switch(ECL_2QUE) {
	case 11:
		mes "[タト]";
		mes "モレンさんの歳ですか？";
		mes "私はモレンさんと仲良くなったのが";
		mes "最近なのでよく知りません。";
		next;
		mes "[タト]";
		mes "でも、シュルの歳ならわかります！";
		mes "私より14歳上なんですよ！";
		emotion 23;
		next;
		menu "タトの歳は？",-;
		mes "[タト]";
		mes "私は146歳です。";
		emotion 23,"";
		next;
		mes "‐モレンの歳に対する確実な情報は";
		mes "　得る事はできなかったけど";
		mes "　まずはユッブの所に戻ろう‐";
		viewpoint 2,137,169,0,0xFF0000;
		viewpoint 1,191,200,0,0xFF0000;
		set ECL_2QUE,12;
		chgquest 11320,11321;
		close;
	case 12:
		mes "‐モレンの歳に対する確実な情報は";
		mes "　得る事はできなかったけど";
		mes "　まずはユッブの所に戻ろう‐";
		viewpoint 1,191,200,0,0xFF0000;
		close;
	default:
		mes "[タト]";
		mes "友達がスプレンディッド部隊に";
		mes "志願したと言っていました。";
		mes "ヨトゥンヘイムはとても寒い場所だと";
		mes "聞いているので";
		mes "元気にしているか心配です。";
		close;
	}
}

eclage.gat,266,216,4	script	モレン	444,{
	switch(ECL_2QUE) {
	case 15:
		mes "[モレン]";
		mes "エクラージュは本当に住み易い場所だ。";
		mes "いつも花が咲いているし";
		mes "気候も暖かいから。";
		next;
		mes "[モレン]";
		mes "そこに美しく飾られた";
		mes "私だけのヤイがあれば";
		mes "それこそ本当のパラダイス！";
		emotion 40;
		next;
		mes "[オリバー]";
		mes "あの丸い家をヤイっていうのか。";
		cutin "bu_oliver2",0;
		next;
		cutin "bu_oliver2",255;
		mes "[モレン]";
		mes "ヤイは卵という意味を持っている。";
		mes "それにラフィネにとって";
		mes "ヤイは家以上の意味を";
		mes "持っていたりもする…";
		next;
		mes "[モレン]";
		mes "だけど、私の人生をかけても良いほどの";
		mes "多くの時間と努力を注ぎ込んだヤイは";
		mes "結局偽物に過ぎない。";
		emotion 6;
		next;
		mes "[モレン]";
		mes "卵という名前を持って";
		mes "卵のような姿をしているけど";
		mes "これは卵じゃないんだ！";
		mes "これはただの卵のような";
		mes "何かに過ぎない！";
		emotion 23;
		next;
		mes "[モレン]";
		mes "そして、よく見ると君！";
		mes "もしかしてミッドガルドから";
		mes "来たのか!?";
		next;
		if(select("そうだ","違う") == 2) {
			mes "[モレン]";
			mes "そうか……。";
			mes "ミッドガルドから来た";
			mes "人間のように見えたけど";
			mes "見間違えたようだ。";
			close;
		}
		mes "[モレン]";
		mes "やはりそうなのか！";
		mes "そうするとミッドガルドに";
		mes "住んでいるという伝説の鳥に関して";
		mes "知っているか？";
		next;
		mes "[モレン]";
		mes "良かったら話を聞かせてくれないか？";
		mes "時間のある時で構わないから";
		mes "もう一度、私に話しかけてくれ！";
		set ECL_2QUE,16;
		chgquest 11324,11325;
		close;
	case 16:
		mes "[モレン]";
		mes "そこら辺の冒険者から";
		mes "少しずつ聞いた話だけど。";
		mes "噂によるとミッドガルドには";
		mes "家くらいの卵を産めるほどに";
		mes "巨大な鳥の伝説があると聞いたんだ。";
		next;
		mes "[モレン]";
		mes "その伝説を初めて聞いた時は";
		mes "寝る事もできないほど";
		mes "興奮していたよ。";
		next;
		mes "[モレン]";
		mes "だけど、時間が経って歳を重ねると";
		mes "そんなことは徐々に忘れてしまったよ。";
		mes "幼いころの夢なんてそんなものだろ？ ";
		emotion 28;
		next;
		mes "[モレン]";
		mes "しかし、ミッドガルドから";
		mes "来たとみられる冒険者が巨大な羽を";
		mes "持っていたという話を";
		mes "広場で会った人に聞いたんだ。";
		next;
		mes "[モレン]";
		mes "その話を聞いた後から";
		mes "仕事が手につかないんだよ。";
		mes "やはり、その伝説は本当だったのかな？";
		emotion 54;
		next;
		mes "[モレン]";
		mes "実を言うとその話を聞いて";
		mes "すぐに街を回ってみたけど";
		mes "巨大な羽を持った人は";
		mes "見つけることはできなかった……。";
		next;
		mes "[モレン]";
		mes "君は確か、私のほしい物を";
		mes "聞きに来たんだったね。";
		mes "もうすぐ私の誕生日だからな。";
		mes "おそらく友人の誰かに頼まれて";
		mes "聞きに来たのだろうが……。";
		next;
		mes "[モレン]";
		mes "せっかくのところ残念だけど、";
		mes "今の私は存在するかもわからない";
		mes "伝説の鳥の卵にしか興味がないんだ。";
		next;
		mes "[モレン]";
		mes "そして、それはプレゼントではなく";
		mes "自分の力で手に入れたいと思っている。";
		mes "もし、伝説が本当ならば";
		mes "今すぐにでもミッドガルド大陸へ";
		mes "旅立つつもりだ。";
		next;
		mes "[モレン]";
		mes "だから、友人たちには";
		mes "旅立つ時に応援してくれれば";
		mes "それで十分だと伝えてくれないか。";
		next;
		mes "[モレン]";
		mes "けど、情けないことに";
		mes "真実を知るのが少し怖い。";
		mes "聞いた話が嘘だったらと思うと";
		mes "旅立つ決心がつかないんだ。";
		emotion 16;
		next;
		mes "[？？？]";
		mes "うははは！";
		mes "話は聞かせて貰った！";
		next;
		mes "‐声のする方へ振り返ると";
		mes "　テューリアン達の姿が見えた‐";
		next;
		mes "[テューリアン]";
		mes "いいか、ちっこいの！";
		mes "男なら迷うな！";
		mes "堂々と立ち向かって！";
		mes "そして戦うんだ！";
		emotion 23;
		emotion 23,"";
		cutin "bu_du2",2;
		next;
		cutin "bu_du2",255;
		mes "[モレン]";
		mes "戦う……。";
		emotion 9;
		next;
		mes "[テューリアン]";
		mes "もし、本当の事を知るのが怖いなら";
		mes "俺がその広場にいるやつに";
		mes "話を聞いてから知らせてやる！";
		mes "もちろん、その伝説が嘘だったら";
		mes "言わないから心配するな！";
		cutin "bu_du2",2;
		next;
		mes "[マークイシャ]";
		mes "なあ、頼むから";
		mes "何にでも首を突っ込むのは";
		mes "控えてくれないか……。";
		cutin "bu_mark3",0;
		next;
		mes "[マークイシャ]";
		mes "しかし、私もそのような伝説は";
		mes "聞いたことはないですね。";
		mes "確かに普通のラフィネなら";
		mes "私たちのような大したことない物でも";
		mes "巨大に感じるかもしれませんが……。";
		cutin "bu_mark1",0;
		next;
		mes "[マギスティン]";
		mes "私も聞いたことないです。";
		mes "そんなに巨大な鳥なんて";
		mes "本当にいるんでしょうか？";
		cutin "bu_maggi1",2;
		next;
		mes "[アルプオカート]";
		mes "……だが、ミッドガルド大陸は広い。";
		mes "俺たちが聞いたことない伝説が";
		mes "あるのかもしれん……。";
		cutin "bu_alp3",2;
		next;
		mes "[テューリアン]";
		mes "やはり広場で話を";
		mes "聞いてみるしかないな！";
		cutin "bu_du1",2;
		next;
		mes "[テューリアン]";
		mes "よし、それじゃあ";
		mes "勝負……";
		cutin "bu_du2",2;
		next;
		mes "[マークイシャ]";
		mes "……";
		cutin "bu_mark3",0;
		next;
		mes "[テューリアン]";
		mes "……と思ったけど";
		mes strcharinfo(0)+ "！";
		mes "今回はお前についていくぜ！";
		mes "お前の実力を確かめてやる！";
		cutin "bu_du5",2;
		next;
		mes "[マークイシャ]";
		mes "いつも強引ですいません。";
		mes "邪魔はしないようにしますので";
		mes "よろしくお願いします。";
		cutin "bu_mark1",0;
		next;
		mes "[マギスティン]";
		mes strcharinfo(0)+ "さん";
		mes "まずは広場に行って";
		mes "話を聞いてみましょう。";
		cutin "bu_maggi2",2;
		next;
		mes "[モレン]";
		mes "話を聞かせてくれた人は";
		mes "いつも広場にあるオーブの近くで";
		mes "思い出にふけっているから";
		mes "すぐにわかると思うよ。";
		cutin "bu_maggi2",255;
		viewpoint 2,266,216,0,0xFF0000;
		viewpoint 1,299,309,0,0xFF0000;
		set ECL_2QUE,17;
		chgquest 11325,11326;
		close;
	case 17:
		mes "[モレン]";
		mes "私が聞いた話は嘘だったのかな";
		mes "ただ忘れられた伝説だと思っていたけど";
		mes "今は事実なのか嘘なのか";
		mes "真実を知るのが少し怖い。";
		next;
		mes "[テューリアン]";
		mes "早く広場に行って";
		mes "俺たちも話を聞いてみようぜ！";
		cutin "bu_du1",2;
		viewpoint 1,299,309,0,0xFF0000;
		close2;
		cutin "bu_du1",255;
		end;
	case 18:
	case 19:
		mes "[モレン]";
		mes "私が聞いた話は嘘だったのかな";
		mes "ただ忘れられた伝説だと思っていたけど";
		mes "今は事実なのか嘘なのか";
		mes "真実を知るのが少し怖い。";
		close;
	case 20:
		mes "[モレン]";
		mes "それは本当なのか？";
		mes "巨大な鳥の伝説が真実だったとは……。";
		next;
		mes "[モレン]";
		mes "……";
		mes "このままではダメだ。";
		mes "早く荷物を準備して";
		mes "ミッドガルドへ旅に出る！";
		next;
		mes "‐モレンがすぐにでも旅に出る気だ";
		mes "　グラシスに知らせてあげたほうが";
		mes "　良さそうだ‐";
		viewpoint 1,283,275,0,0xFF0000;
		set ECL_2QUE,21;
		chgquest 11329,11330;
		close;
	case 21:
		mes "[モレン]";
		mes "それは本当なのか？";
		mes "巨大な鳥の伝説が真実だったとは……。";
		emotion 38;
		next;
		mes "[モレン]";
		mes "……";
		mes "このままではダメだ。";
		mes "早く荷物を準備して";
		mes "ミッドガルドへ旅に出る！";
		emotion 23;
		emotion 23,"";
		next;
		mes "‐モレンがすぐにでも旅に出る気だ";
		mes "　グラシスに知らせてあげたほうが";
		mes "　良さそうだ‐";
		viewpoint 1,283,275,0,0xFF0000;
		close;
	case 22:
	case 23:
		mes "[モレン]";
		mes "友達と誕生日パーティと";
		mes "送別会を終えた後に";
		mes "ミッドガルドに旅立つつもりだ。";
		next;
		mes "[モレン]";
		mes "友達に会いたいから";
		mes "なるべく早く戻って来るよ。";
		close;
	default:
		mes "[モレン]";
		mes "エクラージュは本当に住み易い場所だ。";
		mes "いつも花が咲いているし";
		mes "気候も暖かいから。";
		next;
		mes "[モレン]";
		mes "そこに美しく飾られた";
		mes "私だけのヤイがあれば";
		mes "それこそ本当のパラダイス！";
		next;
		mes "[モレン]";
		mes "ヤイは卵という意味を持っている。";
		mes "それにラフィネにとって";
		mes "ヤイは家以上の意味を";
		mes "持っていたりもする……";
		emotion 40;
		close;
	}
}

ecl_in01.gat,60,71,4	script	思い出にふけるラフィネ	443,{
	switch(ECL_2QUE) {
	case 17:
		mes "[思い出にふけるラフィネ]";
		mes "ふふふ";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "最近は変わったお客さんが";
		mes "増えたな……。";
		mes "昔は異世界に行くためには";
		mes "命をかけなければならなかったのに。";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "今は次元の狭間というもので";
		mes "本当に楽になっている。";
		mes "それに転送というのを使って";
		mes "飛んで行く冒険に";
		mes "何のロマンがあるんだ……。";
		emotion 32;
		next;
		mes "[思い出にふけるラフィネ]";
		mes "最近の冒険者はかえるの卵が";
		mes "どんな味かもわからないだろう。";
		emotion 32;
		next;
		mes "[思い出にふけるラフィネ]";
		mes "ゼロピーを集めてツルギを";
		mes "買っていたのが昨日のようだ。";
		mes "あんなに大事にしていたツルギも";
		mes "今は使われることもなく";
		mes "倉庫にしまわれている。";
		emotion 28;
		next;
		mes "[思い出にふけるラフィネ]";
		mes "時間は本当にはかない物だな……。";
		mes "こんなにはかないとわかっていたら";
		mes "あの時にもう少し……。";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "そこの君……。";
		mes "ライトステンダードという";
		mes "英雄を知っているか？";
		next;
		switch(select("分からない","知っている")) {
		case 1:
			mes "[思い出にふけるラフィネ]";
			mes "ふふふふ……。";
			mes "最近の冒険者が知るわけないか";
			mes "かなり昔の英雄だからな……。";
			mes "今はほとんど忘れられているのかもな。";
			break;
		case 2:
			mes "[思い出にふけるラフィネ]";
			mes "ふふふふ……。";
			mes "最近の冒険者が彼を知っているとは";
			mes "不思議だな……";
			mes "今はほとんど忘れられていると";
			mes "思っていたが。";
			break;
		}
		next;
		mes "[思い出にふけるラフィネ]";
		mes "彼は上級ラフィネでもなく";
		mes "小さな体でとても大きな怪物たちと";
		mes "戦って勝利した。";
		mes "伝説とは彼のためにある";
		mes "言葉のようだった。";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "彼の武勇伝は小さな子供たちまで";
		mes "歌にしてしまうほど有名だった。";
		mes "だが、ラグナロクが過ぎて";
		mes "平和が来ると彼は";
		mes "突然引退してしまったよ。";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "そして、瞬く間に人々から";
		mes "忘れられてしまった……。";
		mes "彼は強力な力と素晴らしい知識を";
		mes "持っていた。";
		mes "だが、彼には足りない物があった。";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "彼に足りなかった物が";
		mes "何かわかるかね？";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "私のような友達だよ……。";
		mes "彼のそばに私のような";
		mes "信じられる友がいたなら……。";
		next;
		mes "[テューリアン]";
		mes "ところで、あんたは";
		mes "ミッドガルドに生息しているという";
		mes "大きな鳥の伝説を知らないか？";
		emotion 23,"";
		cutin "bu_du1",2;
		next;
		cutin "bu_du1",255;
		mes "‐テューリアンのしわがない脳を";
		mes "　初めてありがたく感じた‐";
		emotion 40,"";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "ほう、それは";
		mes "ミッドガルド大陸の巨大鳥に";
		mes "関する伝説のことか？";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "それならこのエクラージュの中で";
		mes "私より詳しい者はいないだろう。";
		emotion 52;
		next;
		mes "[思い出にふけるラフィネ]";
		mes "ライトステンダードが";
		mes "ミッドガルド大陸に到着して";
		mes "間もない頃の話だ。";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "彼はミッドガルド大陸に行く前にも";
		mes "長い間冒険をしていたが、";
		mes "あれほどの大きな鳥は";
		mes "初めてみたと言っていた。";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "実は私もそこまで巨大な鳥が";
		mes "いるとは考えられなかった。";
		mes "町の外に散策に行った時に";
		mes "町の入口でとても大きな羽を";
		mes "持っている旅人を見るまでは……。";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "その羽を見た時";
		mes "ライトステンダードが話していた話が";
		mes "全て本当だったと。";
		next;
		mes "[テューリアン]";
		mes "う～ん……。";
		mes "さっきモレンが街の中では";
		mes "見なかったと言っていたから、";
		mes "まだ外にいるのか？";
		cutin "bu_du1",2;
		next;
		mes "[テューリアン]";
		mes "急いで行ってみよう！";
		cutin "bu_du2",2;
		next;
		cutin "bu_du2",255;
		mes "[思い出にふけるラフィネ]";
		mes "もう行くのか！";
		mes "まだミッドガルドで出会った";
		mes "どんな金属も壊す怪人に関する";
		mes "話もしてないのに！";
		emotion 23;
		next;
		mes "[テューリアン]";
		mes "それはまた後で聞きに来るよ！";
		cutin "bu_du2",2;
		set ECL_2QUE,18;
		chgquest 11326,11327;
		close2;
		cutin "bu_du2",255;
		end;
	case 18:
		mes "[思い出にふけるラフィネ]";
		mes "ほう、考えが変わったのか？";
		mes "では、ライトステンダードが";
		mes "私にだけ話してくれた、";
		mes "ミッドガルドの深い森の中で出会った";
		mes "宝石を食べる怪物について";
		mes "話してやる！";
		next;
		mes "[マギスティン]";
		mes "あの……";
		mes "テューが先に走って";
		mes "行っちゃいましたよ。";
		mes "一人で行かせるとまた何か";
		mes "問題を起こすかも……。";
		cutin "bu_maggi3",2;
		next;
		mes "[マギスティン]";
		mes "町の入口に向かうなら";
		mes "テューが壊した橋を通らないと";
		mes "いけないけど……";
		mes "もう直ってるかなぁ？";
		close2;
		cutin "bu_maggi3",255;
		end;
	default:
		mes "[思い出にふけるラフィネ]";
		mes "ほほほ";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "最近は変わったお客さんが";
		mes "増えたな……。";
		mes "昔は異世界に行くためには";
		mes "命をかけなければならなかったのに。";
		next;
		mes "[思い出にふけるラフィネ]";
		mes "今は次元の狭間というもので";
		mes "本当に楽になっている。";
		mes "それに転送というのを使って";
		mes "飛んで行く冒険に";
		mes "何のロマンがあるんだ……。";
		emotion 32;
		next;
		mes "[思い出にふけるラフィネ]";
		mes "最近の冒険者はかえるの卵が";
		mes "どんな味かもわからないだろう。";
		emotion 32;
		next;
		mes "[思い出にふけるラフィネ]";
		mes "ゼロピーを集めてツルギを";
		mes "買っていたのが昨日のようだ。";
		mes "あんなに大事にしていたツルギも";
		mes "今は使われることもなく";
		mes "倉庫にしまわれている。";
		emotion 28;
		close;
	}
}

ecl_fild01.gat,97,315,4	script	旅人	732,{
	switch(ECL_2QUE) {
	case 18:
		mes "[旅人]";
		mes "誰だ？";
		mes "初めてみる顔だけど";
		next;
		mes "[旅人]";
		mes "もしかしてまた、羽について";
		mes "聞きに来たのか？";
		mes "ただの装飾品なんだが";
		mes "みんなどうしたんだ？";
		emotion 52;
		next;
		mes "[旅人]";
		mes "売ってもらうつもりなら";
		mes "やめといた方がいいよ。";
		mes "いくら頼まれても売る気はないから。";
		next;
		mes "[旅人]";
		mes "この羽は、君らが思っているような";
		mes "普通の羽ではない。";
		next;
		mes "[旅人]";
		mes "くくく……。";
		mes "まあ、自慢するほどの";
		mes "ことじゃないんだが……。";
		next;
		mes "[旅人]";
		mes "このアールブヘイムに来て間もない頃に";
		mes "あんな凄い奴と出会ったのも";
		mes "運だったんだろうな。";
		next;
		mes "[旅人]";
		mes "あいつは本当に凄かった。";
		mes "その巨大な身体を動かすだけの";
		mes "羽を持っていたのだから。";
		next;
		mes "[旅人]";
		mes "だが、その程度で諦める私ではない！";
		mes "思えば本当に長い戦闘だったよ。";
		emotion 40;
		next;
		mes "[テューリアン]";
		mes "おかしいな、俺たちの聞いた話では";
		mes "ミッドガルド大陸で見たと";
		mes "言ってたけど？";
		emotion 23;
		cutin "bu_du1",2;
		next;
		cutin "bu_du1",255;
		mes "[旅人]";
		mes "はぁ!?";
		mes "そ、そんなはずは……";
		mes "私は確かにアールブヘイムで見た。";
		emotion 19;
		next;
		mes "[旅人]";
		mes "こんなものまで見せようとは";
		mes "考えていなかったけど、";
		mes "この怪我がその証拠だ。";
		mes "本当に生死をかけての";
		mes "戦闘だったぞ。";
		next;
		mes "[マークイシャ]";
		mes "ん……。";
		mes "ここ最近の戦闘での怪我としては";
		mes "かなり古いものに見えますね。";
		mes "それに怪我を見ると";
		mes "魔法で治療したものにも";
		mes "見えないし……。";
		emotion 23;
		cutin "bu_mark4",0;
		next;
		cutin "bu_mark4",255;
		mes "[旅人]";
		mes "そうだ！";
		mes "か、考えて見たら最近ではなく";
		mes "かなり前のことだったような。";
		mes "戦利品があまりにも多くて";
		mes "全部覚えるのも難しいからな！";
		emotion 19;
		next;
		mes "[オリバー]";
		mes "だけど、まだエクラージュにも入れずに";
		mes "ここに居る君たちがどうして";
		mes "他の地域に行ったの？";
		emotion 23;
		cutin "bu_oliver2",0;
		next;
		mes "[マギスティン]";
		mes "この近くに現れていたなら";
		mes "ここの人たちが見て無い";
		mes "わけがないじゃない……。";
		emotion 23;
		cutin "bu_maggi1",2;
		next;
		cutin "bu_maggi1",255;
		mes "[旅人]";
		mes "そう！　その通りだ！";
		emotion 19;
		next;
		mes "[旅人]";
		mes "私が異世界に来たのは";
		mes "今回が初めてではない。";
		mes "以前、狭間の調査が進んでいる時に";
		mes "たまたま他の地域にいったことがある。";
		next;
		mes "[アルプオカート]";
		mes "……だがこの羽。";
		mes "よく見ると何か怪しいな。";
		emotion 23;
		cutin "bu_alp3",2;
		next;
		mes "[アルプオカート]";
		mes "何か作り物のような気がしないか？";
		emotion 23;
		cutin "bu_alp4",2;
		next;
		cutin "bu_alp4",255;
		mes "[旅人]";
		mes "何だと!?";
		mes "何処だ！　見せて見ろ！";
		mes "うわ、本当だ！";
		mes "あの猫……";
		mes "私に偽物を売りやがったな!?";
		emotion 23;
		next;
		mes "[テューリアン]";
		mes "あ……買ったんだな？";
		emotion 9,"";
		cutin "bu_du2",2;
		next;
		mes "[オリバー]";
		mes "買ったね？";
		cutin "bu_oliver5",0;
		next;
		mes "[アルプオカート]";
		mes "……そうだとしても";
		mes "素晴らしい腕だな。";
		mes "ここまで本物らしく作るとは。";
		cutin "bu_alp1",2;
		next;
		cutin "bu_alp1",255;
		mes "[旅人]";
		mes "……";
		mes "こっちは高い金を出して";
		mes "買ったのに！";
		emotion 23;
		next;
		mes "[旅人]";
		mes "おい、君たちは";
		mes "エクラージュに入れるよな？";
		mes "私にこれを売った猫商人が";
		mes "広場で商売をしている。";
		next;
		mes "[旅人]";
		mes "あいつが私の金を持って逃げる……";
		mes "いや……。";
		mes "他の被害者が出る前に";
		mes "捕まえてくれ！";
		next;
		mes "[旅人]";
		mes "この私がエクラージュに入るまで！";
		mes "頼む！";
		mes "お願いだ！";
		emotion 28;
		set ECL_2QUE,19;
		chgquest 11327,11328;
		close;
	case 19:
		mes "[旅人]";
		mes "おい、君たちは";
		mes "エクラージュに入れるよな？";
		mes "私にこれを売った猫商人が";
		mes "広場で商売をしている。";
		next;
		mes "[旅人]";
		mes "あいつが私の金を持って逃げる……";
		mes "いや……。";
		mes "他の被害者が出る前に";
		mes "捕まえてくれ！";
		next;
		mes "[旅人]";
		mes "この私がエクラージュに入るまで！";
		mes "頼む！";
		mes "お願いだ！";
		emotion 28;
		close;
	case 20:
		mes "[旅人]";
		mes "うう、私の金……。";
		mes "偽物だったとは……。";
		mes "うう……。";
		emotion 28;
		close;
	default:
		mes "[旅人]";
		mes "誰だ？";
		mes "初めてみる顔だけど";
		next;
		mes "[旅人]";
		mes "もしかしてまた、羽について";
		mes "聞きに来たのか？";
		mes "ただの装飾品なんだが";
		mes "みんなどうしたんだ？";
		next;
		mes "[旅人]";
		mes "売ってもらうつもりなら";
		mes "やめといた方がいいよ。";
		mes "いくら頼まれても売る気はないから。";
		next;
		mes "[旅人]";
		mes "この羽は、君らが思っているような";
		mes "普通の羽ではない。";
		close;
	}
}

ecl_in01.gat,70,88,4	script	行商人	495,{
	switch(ECL_2QUE) {
	case 19:
		mes "[行商人]";
		mes "にゃん？";
		mes "こんにちにゃ～ん";
		mes "遠い～国の宝あるにゃん。";
		mes "見てみるにゃん。";
		mes "安くするにゃ～ん";
		next;
		menu "羽について話す",-;
		mes "[行商人]";
		mes "にゃにゃ!?";
		mes "羽が作り物にゃ!?";
		mes "そんなことないにゃん！";
		mes "本当だにゃん！";
		emotion 23;
		next;
		mes "[行商人]";
		mes "それは確かにミッドガルドで";
		mes "手に入れた物だにゃん。";
		next;
		mes "[アルプオカート]";
		mes "そのわりにはこの部分が……。";
		cutin "bu_alp1",2;
		next;
		cutin "bu_alp1",255;
		mes "[行商人]";
		mes "にゃにゃん！";
		mes "そ……そこに気が付くとはにゃん……。";
		emotion 23;
		next;
		mes "[行商人]";
		mes "実は……。";
		mes "その羽が鳥の羽なのは本当にゃん。";
		mes "だけど私が少し直したにゃん……。";
		next;
		mes "[行商人]";
		mes "あまりにも大きくて持ち歩けないから";
		mes "小さく切ったにゃん。";
		mes "そうすればたくさんの人に売れて";
		mes "お得だと考えたにゃん！";
		mes "だけど、形がおかしくなったから";
		mes "少し手をいれたにゃん。";
		next;
		mes "[マギスティン]";
		mes "切った？";
		mes "なら、元はどのくらい";
		mes "大きい羽だったの？";
		cutin "bu_maggi2",2;
		next;
		cutin "bu_maggi2",255;
		mes "[行商人]";
		mes "ん……。";
		mes "ここからあそこまでの";
		mes "長さだったにゃん。";
		next;
		mes "[行商人]";
		mes "それを持ち歩くのは";
		mes "無理にゃん……。";
		next;
		mes "[テューリアン]";
		mes "おお！";
		mes "そのくらいなら１個の卵で";
		mes "凄い卵焼きを作れるな！";
		cutin "bu_du2",2;
		next;
		mes "[マークイシャ]";
		mes "それは無理だと思うけど……";
		mes "とにかくいい情報を手に入れたから";
		mes "モレンさんに知らせてあげた方が";
		mes "よさそうだね。";
		cutin "bu_mark1",0;
		set ECL_2QUE,20;
		chgquest 11328,11329;
		close2;
		cutin "bu_mark1",255;
		end;
	case 20:
		mes "[マークイシャ]";
		mes "とにかくいい情報を手に入れたから";
		mes "モレンさんに知らせてあげた方が";
		mes "よさそうだね。";
		cutin "bu_mark1",0;
		close2;
		cutin "bu_mark1",255;
		end;
	default:
		mes "[行商人]";
		mes "にゃん？";
		mes "こんにちにゃ～ん";
		mes "遠い～国の宝あるにゃん。";
		mes "見てみるにゃん。";
		mes "安くするにゃ～ん";
		close;
	}
}

eclage.gat,292,266,4	script	#ユッブの家	844,{
	if(ECL_2QUE < 15) {
		mes "‐扉が閉まっているようだ‐";
		close;
	}
	mes "‐ユッブの家だ‐";
	next;
	if(select("ユッブの家に入らない","ユッブの家に入る") == 1) {
		mes "‐あなたはユッブの家を後にした‐";
		close;
	}
	mes "‐ユッブの家に入ります‐";
	close2;
	if(ECL_2QUE < 27)
		warp "ecl_in04.gat",180,226;
	else
		warp "ecl_in04.gat",226,232;
	end;
OnInit:
	waitingroom "ユッブの家",0;
	end;
}

ecl_in04.gat,181,222,4	script	ユッブの家出口	844,{
	mes "‐ユッブの家の玄関だ‐";
	next;
	if(select("ユッブの家から出ない","ユッブの家から出る") == 1) {
		mes "‐もう少しここにいることにした‐";
		close;
	}
	mes "‐外に出ます‐";
	close2;
	warp "eclage.gat",289,260;
	end;
}

ecl_in04.gat,222,232,4	script	ユッブの家出口	844,{
	mes "‐ユッブの家の玄関だ‐";
	next;
	if(select("ユッブの家から出ない","ユッブの家から出る") == 1) {
		mes "‐もう少しここにいることにした‐";
		close;
	}
	mes "‐外に出ます‐";
	close2;
	warp "eclage.gat",289,260;
	end;
}

ecl_in04.gat,182,224,4	script	ユッブ	446,{
	switch(ECL_2QUE) {
	case 22:
		mes "[ユッブ]";
		mes "巨大な鳥の伝説？";
		mes "そんなことを話していたような";
		mes "気がする……。";
		mes "オレは伝説を信じていないから";
		mes "聞き流したけどな。";
		emotion 55;
		cutin "war_y3",2;
		next;
		mes "[ユッブ]";
		mes "グラシスには話してないのか？";
		next;
		mes "[ユッブ]";
		mes "まあ、グラシスのヤイは……。";
		mes "オレは亀裂を初めて見たときに";
		mes "グラシスのヤイを思い出したよ。";
		emotion 53;
		cutin "war_y2",2;
		next;
		mes "[ユッブ]";
		mes "とにかく巨大な鳥の卵は";
		mes "プレゼントで渡されるより";
		mes "直接探しに行きたいんだろ？";
		cutin "war_y3",2;
		next;
		mes "[ユッブ]";
		mes "じゃあ、パーティの準備を";
		mes "急がなきゃな。";
		mes "まずはスプレンディッドに";
		mes "荷物を送ってから……。";
		next;
		mes "[ユッブ]";
		mes "種を箱に入れるのは";
		mes "いつも緊張するな……。";
		mes "一瞬のミスで";
		mes "とんでもない事になる。";
		emotion 52;
		cutin "war_y2",2;
		next;
		mes "[ユッブ]";
		mes "ああ、これか？";
		mes "スプレンディッドにいるマスターから";
		mes "送るように頼まれている物資なんだ。";
		next;
		mes "[ユッブ]";
		mes "本当に大事な作業だから";
		mes "少し待ってろ。";
		set ECL_2QUE,23;
		chgquest 11331,11332;
		close2;
		cutin "war_y2",255;
		end;
	case 23:
		mes "[ユッブ]";
		mes "ふう";
		mes "全部終わった……。";
		mes "この前送った物は";
		mes "ミスってすべて使えなく";
		mes "なってしまって怒られたから……。";
		emotion 28;
		cutin "war_y3",2;
		next;
		mes "[ユッブ]";
		mes "じゃあ、これを広場にいる配達員に";
		mes "渡して来てくれ。";
		mes "配達員から送るようにと";
		mes "マスターから言われたからな。";
		next;
		mes "[ユッブ]";
		mes "すぐに送らないと";
		mes "怒られる……。";
		emotion 9;
		cutin "war_y2",2;
		set ECL_2QUE,24;
		chgquest 11332,11333;
		close2;
		cutin "war_y2",255;
		end;
	case 24:
		mes "[ユッブ]";
		mes "ふう";
		mes "全部終わった……。";
		mes "この前送った物は";
		mes "ミスってすべて使えなく";
		mes "なってしまって怒られたから……。";
		emotion 28;
		cutin "war_y3",2;
		next;
		mes "[ユッブ]";
		mes "じゃあ、これを広場にいる配達員に";
		mes "渡して来てくれ。";
		mes "配達員から送るようにと";
		mes "マスターから言われたからな。";
		next;
		mes "[ユッブ]";
		mes "すぐに送らないと";
		mes "怒られる……。";
		emotion 9;
		cutin "war_y2",2;
		close2;
		cutin "war_y2",255;
		end;
	case 25:
		mes "[ユッブ]";
		mes "やっとマスターから";
		mes "頼まれたことも終わったし";
		mes "そろそろパーティの準備でも";
		mes "手伝うことにするか。";
		cutin "war_y4",2;
		next;
		mes "[ユッブ]";
		mes "オレは少し出かけてくるから";
		mes "休んでな。";
		emotion 18;
		next;
		mes "[マギスティン]";
		mes "気を付けて行ってきてね。";
		cutin "bu_maggi2",2;
		next;
		mes "[テューリアン]";
		mes "だけど、今から何をするんだ？";
		mes "マークちゃんよ、何かないか？";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "そんなに歩き回って疲れてないか？";
		mes "少し休むことにしよう。";
		cutin "bu_mark4",0;
		next;
		mes "[オリバー]";
		mes "うん……。";
		mes "僕、お腹空いた。";
		cutin "bu_oliver3",0;
		next;
		mes "[オリバー]";
		mes "ドングリ！";
		mes "街の外にドングリが";
		mes "たくさんあったのを見た！";
		mes "食べたい！";
		cutin "bu_oliver4",0;
		next;
		mes "[テューリアン]";
		mes "ドングリ？";
		mes "それ美味しいのか？";
		cutin "bu_du1",2;
		next;
		mes "[テューリアン]";
		mes "それじゃドングリでも";
		mes "獲りに行って見ようか！";
		mes "俺が持ってくる！";
		cutin "bu_du2",2;
		next;
		mes "[オリバー]";
		mes "痛い！";
		mes "ほっぺを引っ張らないで！";
		cutin "bu_oliver7",2;
		next;
		mes "[マークイシャ]";
		mes "疲れを知らないな……。";
		mes "では、私はみんなと休んでいるから";
		mes "行って来るといい。";
		cutin "bu_mark2",0;
		next;
		mes "[マークイシャ]";
		mes "そうそう。";
		mes "大量のどんぐりは、エクラージュの";
		mes "入口付近に生息している^FF0000ペタル^000000という";
		mes "モンスターを倒すと手に入るらしい。";
		next;
		mes "[テューリアン]";
		mes "入り口付近にいる^FF0000ペタル^000000だな！";
		mes "わかった、行こう！";
		mes strcharinfo(0)+ "!";
		cutin "bu_du2",2;
		close2;
		cutin "bu_du2",255;
		set ECL_2QUE,26;
		chgquest 11334,11335;
		end;
	case 26:
		mes "[ユッブ]";
		mes "やっとマスターから";
		mes "頼まれたことも終わったし";
		mes "そろそろパーティの準備でも";
		mes "手伝うことにするか。";
		cutin "war_y4",2;
		next;
		mes "[ユッブ]";
		mes "オレは少し出かけてくるから";
		mes "休んでな。";
		emotion 18;
		next;
		mes "[マギスティン]";
		mes "気を付けて行ってきてね。";
		cutin "bu_maggi2",2;
		next;
		mes "[テューリアン]";
		mes "だけど、今から何をするんだ？";
		mes "マークちゃんよ、何かないか？";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "そんなに歩き回って疲れてないか？";
		mes "少し休もう。";
		cutin "bu_mark4",0;
		next;
		mes "[オリバー]";
		mes "うん……。";
		mes "僕、お腹空いた。";
		emotion 37,"オリバー#ep14_2";
		cutin "bu_oliver3",0;
		next;
		mes "[オリバー]";
		mes "ドングリ！";
		mes "街の外にドングリが";
		mes "凄くたくさんあったのを見た！";
		mes "食べたい！";
		emotion 43,"オリバー#ep14_2";
		cutin "bu_oliver4",0;
		next;
		mes "[テューリアン]";
		mes "ドングリ？";
		mes "それ美味しいのか？";
		cutin "bu_du1",2;
		next;
		mes "[テューリアン]";
		mes "それじゃドングリでも";
		mes "採りに行って見ようか！";
		mes "俺が持ってくる！";
		cutin "bu_du2",2;
		next;
		mes "[オリバー]";
		mes "痛い！ ";
		mes "ほっぺを引っ張らないで！";
		emotion 6,"オリバー#ep14_2";
		cutin "bu_oliver7",0;
		next;
		mes "[マークイシャ]";
		mes "疲れるということを知らないな……。";
		mes "では、私はみんなと休んでいるから";
		mes "行って来るといい。";
		cutin "bu_mark2",0;
		next;
		mes "[マークイシャ]";
		mes "そうそう。";
		mes "大量のどんぐりは、エクラージュの";
		mes "入口付近に生息している^FF0000ペタル^000000という";
		mes "モンスターを倒すと手に入るらしい。";
		next;
		mes "[テューリアン]";
		mes "入り口付近にいる^FF0000ペタル^000000だな！";
		mes "わかった、行こう！";
		mes strcharinfo(0)+ "!";
		cutin "bu_du2",2;
		close2;
		cutin "bu_du2",255;
		end;
	default:
		mes "[ユッブ]";
		mes "自分の家だと思って";
		mes "ゆっくりしていけよ。";
		cutin "war_y4",2;
		close2;
		cutin "war_y4",255;
		end;
	}
}

ecl_in04.gat,179,226,4	script	オリバー#ep14_2	626,{
	switch(ECL_2QUE) {
	case 26:
		if(countitem(6558) < 1) {
			mes "[オリバー]";
			mes "ドングリ～～！";
			mes "ドングリをいっぱい";
			mes "持って来るって言ったのに～！";
			emotion 28;
			cutin "bu_oliver7",0;
			next;
			mes "[テューリアン]";
			mes "行こう！　" +strcharinfo(0)+ "!";
			cutin "bu_du2",2;
			close2;
			cutin "bu_du2",255;
			end;
		}
		mes "[オリバー]";
		mes "うわああ、";
		mes "美味しそうなドングリだ！";
		mes "ありがとう、美味しく食べるよ！";
		emotion 43;
		cutin "bu_oliver4",0;
		next;
		mes "[オリバー]";
		mes "美味しい！";
		mes "マギは？";
		next;
		mes "[マギスティン]";
		mes "美味しい……！";
		cutin "bu_maggi2",2;
		next;
		mes "[オリバー]";
		mes "あー！　美味しかった！";
		mes "お腹いっぱいだ。";
		mes "ふう……。";
		emotion 30;
		cutin "bu_oliver81",0;
		next;
		mes "[テューリアン]";
		mes "オリバー、もっと食べて。";
		mes "いっぱい食べないと";
		mes "大きくならないんだぞ！";
		cutin "bu_du1",2;
		next;
		mes "[オリバー]";
		mes "ふあああ……";
		mes "お腹いっぱい……。";
		mes "眠い……。";
		emotion 45;
		cutin "bu_oliver82",0;
		next;
		mes "[テューリアン]";
		mes "オリバー、食べてすぐ横になると";
		mes "太るぞ……。";
		cutin "bu_du2",2;
		next;
		mes "[オリバー]";
		mes "だけど、とても眠い。";
		cutin "bu_oliver83",0;
		next;
		mes "[オリバー]";
		mes "僕はこれが夢だと思ったけど";
		mes "こんなに眠いなんて";
		mes "夢じゃないみたいだね。";
		cutin "bu_oliver84",0;
		next;
		mes "[オリバー]";
		mes "ドングリも美味しいし……。";
		mes "…";
		cutin "bu_oliver85",0;
		next;
		mes "[オリバー]";
		mes "……";
		emotion 9,"";
		cutin "bu_oliver86",0;
		next;
		mes "[テューリアン]";
		mes "……";
		cutin "bu_du1",2;
		next;
		mes "[アルプオカート]";
		mes "……";
		cutin "bu_alp2",2;
		next;
		mes "[テューリアン]";
		mes "き、消えた……";
		mes "うわああああ！ ";
		emotion 23,"";
		cutin "bu_du5",2;
		delitem 6558,1;
		set ECL_2QUE,27;
		chgquest 11335,11336;
		close2;
		cutin "bu_du5",255;
		warp "eclage.gat",289,260;
		end;
	default:
		mes "[オリバー]";
		mes "眠い……。";
		mes "僕は少し寝るから";
		mes "出るときに起こして……。";
		mes "僕だけおいて行っちゃ";
		mes "ダメだからね～";
		emotion 45;
		cutin "bu_oliver6",0;
		close2;
		cutin "bu_oliver6",255;
		end;
	}
}

ecl_in01.gat,44,53,4	script	配達員	513,{
	switch(ECL_2QUE) {
	case 24:
		mes "[配達員]";
		mes "これが荷物ですか？";
		mes "安全に配送するので";
		mes "ご安心ください。";
		next;
		mes "[配達員]";
		mes "スプレンディッドから";
		mes "エクラージュに来る道は";
		mes "とても険しいのですが、";
		mes "今の時期はエクラージュに";
		mes "来る方がいいです。";
		next;
		mes "[配達員]";
		mes "ポリンの漬け物なんて";
		mes "自分で少しずつ作って食べればいいのに";
		mes "どうして私が配達をするんだ……。";
		mes "ああ、気持ち悪い。";
		emotion 28;
		set ECL_2QUE,25;
		chgquest 11333,11334;
		close;
	default:
		mes "[配達員]";
		mes "ふう……。";
		mes "決まった時間までに到着するためには";
		mes "早く出発しないとな。";
		next;
		mes "[配達員]";
		mes "いや……";
		mes "逆に遅く行った方がいいかも……";
		mes "倉庫に配達しなければならない";
		mes "ポリン漬けの箱が";
		mes "かなりあったような気が……。";
		emotion 28;
		close;
	}
}

ecl_in04.gat,226,231,4	script	テューリアン#ep14_2in2	628,{
	if(ECL_2QUE == 27) {
		mes "[テューリアン]";
		mes "ど、どこに消えたんだろ……。";
		mes "まさか幽霊!?";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[マギスティン]";
		mes "魔法を使ったような気配も";
		mes "感じられなかったけど……。";
		cutin "bu_maggi3",2;
		next;
		mes "[マギスティン]";
		mes "あ、ここの床にオリバーが";
		mes "被っていたフードが……。";
		emotion 23,"マギスティン#ep14_2in2";
		cutin "bu_maggi4",2;
		next;
		mes "[マギスティン]";
		mes "うぅ……怖いよぉ……嫌だよぉ……";
		emotion 28,"マギスティン#ep14_2in2";
		cutin "bu_maggi4",2;
		next;
		mes "[アルプオカート]";
		mes "思い出した……。";
		mes "オリバー……。";
		emotion 52,"アルプオカート#ep14_2in";
		cutin "bu_alp2",2;
		next;
		mes "[アルプオカート]";
		mes "……";
		mes "オリバーヒルベルト……。";
		mes "夢みる小説家とも呼ばれる";
		mes "有名な小説家だ……。";
		emotion 9,"アルプオカート#ep14_2in";
		cutin "bu_alp3",2;
		next;
		mes "[アルプオカート]";
		mes "それにこの本……。";
		mes "どうしてオリバーがいる時には";
		mes "思い出せなかったんだろ……。";
		cutin "bu_alp5",2;
		next;
		mes "[テューリアン]";
		mes "おい……";
		mes "お前、今その本をふところから";
		mes "出したか？";
		emotion 9,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[アルプオカート]";
		mes "ファンだから……。";
		emotion 40,"アルプオカート#ep14_2in";
		cutin "bu_alp4",2;
		next;
		mes "[テューリアン]";
		mes "ふところに入れて持ち歩くほどなのに";
		mes "なんで覚えていないんだ……。";
		mes "その前にいくらファンでも";
		mes "普通にふところに入れてまで";
		mes "持ち歩くのか？";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[アルプオカート]";
		mes "……";
		emotion 40,"アルプオカート#ep14_2in";
		cutin "bu_alp4",2;
		next;
		mes "[テューリアン]";
		mes "おい、お前な……。";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "それより……この本のタイトルが……";
		mes "［妖精の都市］だけど？";
		emotion 23,"マークイシャ#ep14_2in2";
		cutin "bu_mark4",0;
		next;
		mes "[マークイシャ]";
		mes "それに……";
		mes "発行されて何年も経った本だぞ……。";
		emotion 23,"マークイシャ#ep14_2in2";
		next;
		mes "[テューリアン]";
		mes "……どういうことだ？";
		mes "オリバーは幽霊じゃないのか？";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "オリバーは最初に言っていただろう。";
		mes "自分の姿が見えるはずがない。";
		mes "こんなリアルな夢は初めてだと。";
		cutin "bu_mark1",0;
		next;
		mes "[マークイシャ]";
		mes "もしかしたら、オリバーにとって";
		mes "ここは夢の世界だったのかも知れない。";
		next;
		mes "[マギスティン]";
		mes "つまり、オリバーにとって";
		mes "ここでの出来事は夢で、";
		mes "本当の身体の目が覚めたから";
		mes "こちらのオリバーの姿が";
		mes "消えてしまったんですか？";
		cutin "bu_maggi1",2;
		next;
		mes "[テューリアン]";
		mes "おいおい、そんなこと";
		mes "ありえるのか？";
		mes "第一、俺たちは夢じゃなくて";
		mes "実在するじゃないか。";
		cutin "bu_du1",2;
		next;
		mes "[アルプオカート]";
		mes "しかし、それなら辻褄があう。";
		mes "オリバーの事を忘れていた事も";
		mes "不思議な力が働いていたとしか";
		mes "思えないし……。";
		cutin "bu_alp1",2;
		next;
		mes "[アルプオカート]";
		mes "俺たちが実在するというのも";
		mes "オリバーがここを夢だと";
		mes "思い込んでいただけにすぎない。";
		next;
		mes "[テューリアン]";
		mes "なるほどな……。";
		mes "真実はわからないけど";
		mes "オリバーが無事ならそれでいいさ。";
		mes "あいつ、可愛かったしな！";
		mes "良い思い出が出来た！";
		cutin "bu_du2",2;
		next;
		mes "[アルプオカート]";
		mes "憧れの小説家に会えて感激だ……。";
		cutin "bu_alp4",2;
		next;
		mes "[マギスティン]";
		mes "一緒に食べたどんぐり。";
		mes "美味しかったです。";
		cutin "bu_maggi2",2;
		next;
		mes "[マークイシャ]";
		mes "大変なこともあったが……。";
		mes "仲間が増えたみたいで楽しかったよ。";
		cutin "bu_mark2",0;
		next;
		mes "[テューリアン]";
		mes strcharinfo(0)+ "も";
		mes "いろいろ助かったぜ！";
		mes "ひとまずはここでお別れだ。";
		mes "ありがとうな！";
		cutin "bu_du1",2;
		next;
		if(checkitemblank() == 0) {
			mes "[テューリアン]";
			mes "このオリバーの被っていたフード……";
			mes "お前に持っていて貰おうかと思ったけど";
			mes "荷物が多そうだな。";
			mes "少し荷物を減らしてから";
			mes "また来てくれないか。";
			close2;
			cutin "bu_du1",255;
			end;
		}
		getitem 19543,1;
		getexp 5000000,0;
		getexp 0,2500000;
		set ECL_2QUE,28;
		chgquest 11337,201570;
		close2;
		cutin "bu_du1",255;
		end;
	}
	mes "[テューリアン]";
	mes "ところで、これ1巻じゃないか";
	mes "他にもあるのかな？";
	emotion 9,"テューリアン#ep14_2in2";
	cutin "bu_du1",2;
	next;
	mes "[アルプオカート]";
	mes "3巻で完結なんだ。";
	emotion 21,"アルプオカート#ep14_2in";
	cutin "bu_alp1",2;
	next;
	mes "[テューリアン]";
	mes "どうしてふところから";
	mes "何冊もでるんだ……";
	mes "というか、なんで";
	mes "全巻持ち歩いてるんだよ……。";
	emotion 23,"テューリアン#ep14_2in2";
	cutin "bu_du5",2;
	close2;
	cutin "bu_du5",255;
	end;
}

ecl_in04.gat,224,234,4	script	マークイシャ#ep14_2in2	616,{
	if(ECL_2QUE == 27) {
		mes "[テューリアン]";
		mes "ど、どこに消えたんだろ……。";
		mes "まさか幽霊!?";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[マギスティン]";
		mes "魔法を使ったような気配も";
		mes "感じられなかったけど……。";
		cutin "bu_maggi3",2;
		next;
		mes "[マギスティン]";
		mes "あ、ここの床にオリバーが";
		mes "被っていたフードが……。";
		emotion 23,"マギスティン#ep14_2in2";
		cutin "bu_maggi4",2;
		next;
		mes "[マギスティン]";
		mes "うぅ……怖いよぉ……嫌だよぉ……";
		emotion 28,"マギスティン#ep14_2in2";
		cutin "bu_maggi4",2;
		next;
		mes "[アルプオカート]";
		mes "思い出した……。";
		mes "オリバー……。";
		emotion 52,"アルプオカート#ep14_2in";
		cutin "bu_alp2",2;
		next;
		mes "[アルプオカート]";
		mes "……";
		mes "オリバーヒルベルト……。";
		mes "夢みる小説家とも呼ばれる";
		mes "有名な小説家だ……。";
		emotion 9,"アルプオカート#ep14_2in";
		cutin "bu_alp3",2;
		next;
		mes "[アルプオカート]";
		mes "それにこの本……。";
		mes "どうしてオリバーがいる時には";
		mes "思い出せなかったんだろ……。";
		cutin "bu_alp5",2;
		next;
		mes "[テューリアン]";
		mes "おい……";
		mes "お前、今その本をふところから";
		mes "出したか？";
		emotion 9,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[アルプオカート]";
		mes "ファンだから……。";
		emotion 40,"アルプオカート#ep14_2in";
		cutin "bu_alp4",2;
		next;
		mes "[テューリアン]";
		mes "ふところに入れて持ち歩くほどなのに";
		mes "なんで覚えていないんだ……。";
		mes "その前にいくらファンでも";
		mes "普通にふところに入れてまで";
		mes "持ち歩くのか？";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[アルプオカート]";
		mes "……";
		emotion 40,"アルプオカート#ep14_2in";
		cutin "bu_alp4",2;
		next;
		mes "[テューリアン]";
		mes "おい、お前な……。";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "それより……この本のタイトルが……";
		mes "［妖精の都市］だけど？";
		emotion 23,"マークイシャ#ep14_2in2";
		cutin "bu_mark4",0;
		next;
		mes "[マークイシャ]";
		mes "それに……";
		mes "発行されて何年も経った本だぞ……。";
		emotion 23,"マークイシャ#ep14_2in2";
		next;
		mes "[テューリアン]";
		mes "……どういうことだ？";
		mes "オリバーは幽霊じゃないのか？";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "オリバーは最初に言っていただろう。";
		mes "自分の姿が見えるはずがない。";
		mes "こんなリアルな夢は初めてだと。";
		cutin "bu_mark1",0;
		next;
		mes "[マークイシャ]";
		mes "もしかしたら、オリバーにとって";
		mes "ここは夢の世界だったのかも知れない。";
		next;
		mes "[マギスティン]";
		mes "つまり、オリバーにとって";
		mes "ここでの出来事は夢で、";
		mes "本当の身体の目が覚めたから";
		mes "こちらのオリバーの姿が";
		mes "消えてしまったんですか？";
		cutin "bu_maggi1",2;
		next;
		mes "[テューリアン]";
		mes "おいおい、そんなこと";
		mes "ありえるのか？";
		mes "第一、俺たちは夢じゃなくて";
		mes "実在するじゃないか。";
		cutin "bu_du1",2;
		next;
		mes "[アルプオカート]";
		mes "しかし、それなら辻褄があう。";
		mes "オリバーの事を忘れていた事も";
		mes "不思議な力が働いていたとしか";
		mes "思えないし……。";
		cutin "bu_alp1",2;
		next;
		mes "[アルプオカート]";
		mes "俺たちが実在するというのも";
		mes "オリバーがここを夢だと";
		mes "思い込んでいただけにすぎない。";
		next;
		mes "[テューリアン]";
		mes "なるほどな……。";
		mes "真実はわからないけど";
		mes "オリバーが無事ならそれでいいさ。";
		mes "あいつ、可愛かったしな！";
		mes "良い思い出が出来た！";
		cutin "bu_du2",2;
		next;
		mes "[アルプオカート]";
		mes "憧れの小説家に会えて感激だ……。";
		cutin "bu_alp4",2;
		next;
		mes "[マギスティン]";
		mes "一緒に食べたどんぐり。";
		mes "美味しかったです。";
		cutin "bu_maggi2",2;
		next;
		mes "[マークイシャ]";
		mes "大変なこともあったが……。";
		mes "仲間が増えたみたいで楽しかったよ。";
		cutin "bu_mark2",0;
		next;
		mes "[テューリアン]";
		mes strcharinfo(0)+ "も";
		mes "いろいろ助かったぜ！";
		mes "ひとまずはここでお別れだ。";
		mes "ありがとうな！";
		cutin "bu_du1",2;
		next;
		if(checkitemblank() == 0) {
			mes "[テューリアン]";
			mes "このオリバーの被っていたフード……";
			mes "お前に持っていて貰おうかと思ったけど";
			mes "荷物が多そうだな。";
			mes "少し荷物を減らしてから";
			mes "また来てくれないか。";
			close2;
			cutin "bu_du1",255;
			end;
		}
		getitem 19543,1;
		getexp 5000000,0;
		getexp 0,2500000;
		set ECL_2QUE,28;
		chgquest 11337,201570;
		close2;
		cutin "bu_du1",255;
		end;
	}
	mes "[マークイシャ]";
	mes "しかし、不思議な事もあるものだ。";
	mes "もしかしたら、夢を見ているのは";
	mes "私たちの方だったりしてな。";
	emotion 23,"テューリアン#ep14_2in2";
	cutin "bu_mark1",0;
	next;
	mes "[テューリアン]";
	mes "痛っ！";
	mes "どうして俺を殴るんだよ！";
	mes "痛いだろう！";
	emotion 19,"テューリアン#ep14_2in2";
	cutin "bu_du4",2;
	next;
	mes "[マークイシャ]";
	mes "ああ、どうやら夢じゃないらしい。";
	emotion 6,"テューリアン#ep14_2in2";
	cutin "bu_mark2",0;
	close2;
	cutin "bu_mark2",255;
	end;
}

ecl_in04.gat,223,234,4	script	マギスティン#ep14_2in2	612,{
	if(ECL_2QUE == 27) {
		mes "[テューリアン]";
		mes "ど、どこに消えたんだろ……。";
		mes "まさか幽霊!?";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[マギスティン]";
		mes "魔法を使ったような気配も";
		mes "感じられなかったけど……。";
		cutin "bu_maggi3",2;
		next;
		mes "[マギスティン]";
		mes "あ、ここの床にオリバーが";
		mes "被っていたフードが……。";
		emotion 23,"マギスティン#ep14_2in2";
		cutin "bu_maggi4",2;
		next;
		mes "[マギスティン]";
		mes "うぅ……怖いよぉ……嫌だよぉ……";
		emotion 28,"マギスティン#ep14_2in2";
		cutin "bu_maggi4",2;
		next;
		mes "[アルプオカート]";
		mes "思い出した……。";
		mes "オリバー……。";
		emotion 52,"アルプオカート#ep14_2in";
		cutin "bu_alp2",2;
		next;
		mes "[アルプオカート]";
		mes "……";
		mes "オリバーヒルベルト……。";
		mes "夢みる小説家とも呼ばれる";
		mes "有名な小説家だ……。";
		emotion 9,"アルプオカート#ep14_2in";
		cutin "bu_alp3",2;
		next;
		mes "[アルプオカート]";
		mes "それにこの本……。";
		mes "どうしてオリバーがいる時には";
		mes "思い出せなかったんだろ……。";
		cutin "bu_alp5",2;
		next;
		mes "[テューリアン]";
		mes "おい……";
		mes "お前、今その本をふところから";
		mes "出したか？";
		emotion 9,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[アルプオカート]";
		mes "ファンだから……。";
		emotion 40,"アルプオカート#ep14_2in";
		cutin "bu_alp4",2;
		next;
		mes "[テューリアン]";
		mes "ふところに入れて持ち歩くほどなのに";
		mes "なんで覚えていないんだ……。";
		mes "その前にいくらファンでも";
		mes "普通にふところに入れてまで";
		mes "持ち歩くのか？";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[アルプオカート]";
		mes "……";
		emotion 40,"アルプオカート#ep14_2in";
		cutin "bu_alp4",2;
		next;
		mes "[テューリアン]";
		mes "おい、お前な……。";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "それより……この本のタイトルが……";
		mes "［妖精の都市］だけど？";
		emotion 23,"マークイシャ#ep14_2in2";
		cutin "bu_mark4",0;
		next;
		mes "[マークイシャ]";
		mes "それに……";
		mes "発行されて何年も経った本だぞ……。";
		emotion 23,"マークイシャ#ep14_2in2";
		next;
		mes "[テューリアン]";
		mes "……どういうことだ？";
		mes "オリバーは幽霊じゃないのか？";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "オリバーは最初に言っていただろう。";
		mes "自分の姿が見えるはずがない。";
		mes "こんなリアルな夢は初めてだと。";
		cutin "bu_mark1",0;
		next;
		mes "[マークイシャ]";
		mes "もしかしたら、オリバーにとって";
		mes "ここは夢の世界だったのかも知れない。";
		next;
		mes "[マギスティン]";
		mes "つまり、オリバーにとって";
		mes "ここでの出来事は夢で、";
		mes "本当の身体の目が覚めたから";
		mes "こちらのオリバーの姿が";
		mes "消えてしまったんですか？";
		cutin "bu_maggi1",2;
		next;
		mes "[テューリアン]";
		mes "おいおい、そんなこと";
		mes "ありえるのか？";
		mes "第一、俺たちは夢じゃなくて";
		mes "実在するじゃないか。";
		cutin "bu_du1",2;
		next;
		mes "[アルプオカート]";
		mes "しかし、それなら辻褄があう。";
		mes "オリバーの事を忘れていた事も";
		mes "不思議な力が働いていたとしか";
		mes "思えないし……。";
		cutin "bu_alp1",2;
		next;
		mes "[アルプオカート]";
		mes "俺たちが実在するというのも";
		mes "オリバーがここを夢だと";
		mes "思い込んでいただけにすぎない。";
		next;
		mes "[テューリアン]";
		mes "なるほどな……。";
		mes "真実はわからないけど";
		mes "オリバーが無事ならそれでいいさ。";
		mes "あいつ、可愛かったしな！";
		mes "良い思い出が出来た！";
		cutin "bu_du2",2;
		next;
		mes "[アルプオカート]";
		mes "憧れの小説家に会えて感激だ……。";
		cutin "bu_alp4",2;
		next;
		mes "[マギスティン]";
		mes "一緒に食べたどんぐり。";
		mes "美味しかったです。";
		cutin "bu_maggi2",2;
		next;
		mes "[マークイシャ]";
		mes "大変なこともあったが……。";
		mes "仲間が増えたみたいで楽しかったよ。";
		cutin "bu_mark2",0;
		next;
		mes "[テューリアン]";
		mes strcharinfo(0)+ "も";
		mes "いろいろ助かったぜ！";
		mes "ひとまずはここでお別れだ。";
		mes "ありがとうな！";
		cutin "bu_du1",2;
		next;
		if(checkitemblank() == 0) {
			mes "[テューリアン]";
			mes "このオリバーの被っていたフード……";
			mes "お前に持っていて貰おうかと思ったけど";
			mes "荷物が多そうだな。";
			mes "少し荷物を減らしてから";
			mes "また来てくれないか。";
			close2;
			cutin "bu_du1",255;
			end;
		}
		getitem 19543,1;
		getexp 5000000,0;
		getexp 0,2500000;
		set ECL_2QUE,28;
		chgquest 11337,201570;
		close2;
		cutin "bu_du1",255;
		end;
	}
	mes "[マギスティン]";
	mes "オリバー……";
	emotion 28,"マギスティン#ep14_2in2";
	cutin "bu_maggi4",2;
	next;
	mes "[テューリアン]";
	mes "マギ、大丈夫か？";
	emotion 19,"テューリアン#ep14_2in2";
	cutin "bu_du1",2;
	close2;
	cutin "bu_du1",255;
	end;
}

ecl_in04.gat,223,230,4	script	アルプオカート#ep14_2in	615,{
	if(ECL_2QUE == 27) {
		mes "[テューリアン]";
		mes "ど、どこに消えたんだろ……。";
		mes "まさか幽霊!?";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[マギスティン]";
		mes "魔法を使ったような気配も";
		mes "感じられなかったけど……。";
		cutin "bu_maggi3",2;
		next;
		mes "[マギスティン]";
		mes "あ、ここの床にオリバーが";
		mes "被っていたフードが……。";
		emotion 23,"マギスティン#ep14_2in2";
		cutin "bu_maggi4",2;
		next;
		mes "[マギスティン]";
		mes "うぅ……怖いよぉ……嫌だよぉ……";
		emotion 28,"マギスティン#ep14_2in2";
		cutin "bu_maggi4",2;
		next;
		mes "[アルプオカート]";
		mes "思い出した……。";
		mes "オリバー……。";
		emotion 52,"アルプオカート#ep14_2in";
		cutin "bu_alp2",2;
		next;
		mes "[アルプオカート]";
		mes "……";
		mes "オリバーヒルベルト……。";
		mes "夢みる小説家とも呼ばれる";
		mes "有名な小説家だ……。";
		emotion 9,"アルプオカート#ep14_2in";
		cutin "bu_alp3",2;
		next;
		mes "[アルプオカート]";
		mes "それにこの本……。";
		mes "どうしてオリバーがいる時には";
		mes "思い出せなかったんだろ……。";
		cutin "bu_alp5",2;
		next;
		mes "[テューリアン]";
		mes "おい……";
		mes "お前、今その本をふところから";
		mes "出したか？";
		emotion 9,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[アルプオカート]";
		mes "ファンだから……。";
		emotion 40,"アルプオカート#ep14_2in";
		cutin "bu_alp4",2;
		next;
		mes "[テューリアン]";
		mes "ふところに入れて持ち歩くほどなのに";
		mes "なんで覚えていないんだ……。";
		mes "その前にいくらファンでも";
		mes "普通にふところに入れてまで";
		mes "持ち歩くのか？";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du5",2;
		next;
		mes "[アルプオカート]";
		mes "……";
		emotion 40,"アルプオカート#ep14_2in";
		cutin "bu_alp4",2;
		next;
		mes "[テューリアン]";
		mes "おい、お前な……。";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "それより……この本のタイトルが……";
		mes "［妖精の都市］だけど？";
		emotion 23,"マークイシャ#ep14_2in2";
		cutin "bu_mark4",0;
		next;
		mes "[マークイシャ]";
		mes "それに……";
		mes "発行されて何年も経った本だぞ……。";
		emotion 23,"マークイシャ#ep14_2in2";
		next;
		mes "[テューリアン]";
		mes "……どういうことだ？";
		mes "オリバーは幽霊じゃないのか？";
		emotion 23,"テューリアン#ep14_2in2";
		cutin "bu_du1",2;
		next;
		mes "[マークイシャ]";
		mes "オリバーは最初に言っていただろう。";
		mes "自分の姿が見えるはずがない。";
		mes "こんなリアルな夢は初めてだと。";
		cutin "bu_mark1",0;
		next;
		mes "[マークイシャ]";
		mes "もしかしたら、オリバーにとって";
		mes "ここは夢の世界だったのかも知れない。";
		next;
		mes "[マギスティン]";
		mes "つまり、オリバーにとって";
		mes "ここでの出来事は夢で、";
		mes "本当の身体の目が覚めたから";
		mes "こちらのオリバーの姿が";
		mes "消えてしまったんですか？";
		cutin "bu_maggi1",2;
		next;
		mes "[テューリアン]";
		mes "おいおい、そんなこと";
		mes "ありえるのか？";
		mes "第一、俺たちは夢じゃなくて";
		mes "実在するじゃないか。";
		cutin "bu_du1",2;
		next;
		mes "[アルプオカート]";
		mes "しかし、それなら辻褄があう。";
		mes "オリバーの事を忘れていた事も";
		mes "不思議な力が働いていたとしか";
		mes "思えないし……。";
		cutin "bu_alp1",2;
		next;
		mes "[アルプオカート]";
		mes "俺たちが実在するというのも";
		mes "オリバーがここを夢だと";
		mes "思い込んでいただけにすぎない。";
		next;
		mes "[テューリアン]";
		mes "なるほどな……。";
		mes "真実はわからないけど";
		mes "オリバーが無事ならそれでいいさ。";
		mes "あいつ、可愛かったしな！";
		mes "良い思い出が出来た！";
		cutin "bu_du2",2;
		next;
		mes "[アルプオカート]";
		mes "憧れの小説家に会えて感激だ……。";
		cutin "bu_alp4",2;
		next;
		mes "[マギスティン]";
		mes "一緒に食べたどんぐり。";
		mes "美味しかったです。";
		cutin "bu_maggi2",2;
		next;
		mes "[マークイシャ]";
		mes "大変なこともあったが……。";
		mes "仲間が増えたみたいで楽しかったよ。";
		cutin "bu_mark2",0;
		next;
		mes "[テューリアン]";
		mes strcharinfo(0)+ "も";
		mes "いろいろ助かったぜ！";
		mes "ひとまずはここでお別れだ。";
		mes "ありがとうな！";
		cutin "bu_du1",2;
		next;
		if(checkitemblank() == 0) {
			mes "[テューリアン]";
			mes "このオリバーの被っていたフード……";
			mes "お前に持っていて貰おうかと思ったけど";
			mes "荷物が多そうだな。";
			mes "少し荷物を減らしてから";
			mes "また来てくれないか。";
			close2;
			cutin "bu_du1",255;
			end;
		}
		getitem 19543,1;
		getexp 5000000,0;
		getexp 0,2500000;
		set ECL_2QUE,28;
		chgquest 11337,201570;
		close2;
		cutin "bu_du1",255;
		end;
	}
	mes "[アルプオカート]";
	mes "こ、こんなことが……。";
	mes "どうして思い出せなかったんだ……。";
	emotion 23,"アルプオカート#ep14_2in";
	cutin "bu_alp5",2;
	next;
	mes "[アルプオカート]";
	mes "サインを……";
	mes "サインを貰わないといけないのに！";
	emotion 23,"アルプオカート#ep14_2in";
	close2;
	cutin "bu_alp5",255;
	end;
}

//============================================================
// エクラージュの王クエスト
//- Registry -------------------------------------------------
// ECL_3QUE -> 0～
//------------------------------------------------------------
ecl_hub01.gat,98,32,3	script	エクラージュガード	461,{
	if(ECL_3QUE < 5) {
		mes "[エクラージュガード]";
		mes "王のために働く者ではありませんね。";
		mes "恐れ入ります。この先は";
		mes "関係者以外の方は入場できません。";
		next;
		mes "‐エクラージュの王のために働く者";
		mes "　でないと、この先に進めないようだ‐";
		next;
		mes "^FF0000‐この先に進むには";
		mes "　クエスト「エクラージュの王」を";
		mes "　進める必要があります‐^000000";
		close;
	}
	mes "[エクラージュガード]";
	mes "王のために働く者……ですね。";
	mes "執政官の通知がありましたので";
	mes "出入りを許可します。";
	mes "こちらへどうぞ。";
	close2;
	warp "ecl_in02.gat",126,115;
	end;
}

eclage.gat,112,40,3	script	エクラージュガード	461,{
	switch(ECL_3QUE) {
	case 5:
		if(ECL_3QUE_sub & 0x1) {
			mes "[レオ]";
			mes "果実ジャムとハチ蜜は";
			mes "本当に素晴らしい味でした！";
			mes "前線基地のやつら、";
			mes "こんなに美味しい物を";
			mes "食べていたんですね!!";
			next;
			mes "[レオ]";
			mes "あなたにお手伝いいただいたことは";
			mes "上層部に伝えておきました！";
			mes "またお会いしましょう!!";
			close;
		}
		if(checkquest(7420)) {
			if(countitem(12344) < 3 || countitem(12345) < 3) {
				mes "[レオ]";
				mes "^FF0000ピンギキュラの果実ジャム3個^000000と";
				mes "^FF0000ルシオラヴェスパのハチ蜜3個^000000です。";
				mes "スプレンディッド前線基地の";
				mes "特産品です。";
				mes "お願いします！";
				close;
			}
			mes "[レオ]";
			mes "おおおおお、その手にある物は!!";
			mes "ピンギキュラの果実ジャムと!!!";
			mes "ルシオラヴェスパのハチ蜜!!!";
			mes "助かりました!!!";
			next;
			mes "[レオ]";
			mes "マヨル・ジュン様は";
			mes "やっぱり人を見る目がありますね。";
			next;
			delitem 12344,3;
			delitem 12345,3;
			set ECL_3QUE_sub,ECL_3QUE_sub|1;
			delquest 7420;
			getexp 200000,0;
			getexp 0,200000;
			if(ECL_3QUE_sub & 0x7 == 0x7) {
				mes "[エクラージュガード]";
				mes "ここにいましたか。";
				mes "マヨル・ジュンから、あなたを探すよう";
				mes "指示されました。";
				mes "レオの頼みも聞いてくれたんですか？";
				cutin "minuel01",4;
				next;
				mes "[エクラージュガード]";
				mes "そうですか。";
				mes "では、あの方からの伝言を";
				mes "お伝えします。";
				next;
				mes "[エクラージュガード]";
				mes "あなたはエクラージュのために";
				mes "たくさんの仕事をしてくれた。";
				mes "もう十分やってくれたと思っている。";
				next;
				mes "[エクラージュガード]";
				mes "とのことです。";
				mes "このように伝えれば分かるはずだと。";
				mes "それでは私はこれで失礼します。";
				set ECL_3QUE,6;
				set ECL_3QUE_sub,0;
				chgquest 7417,7421;
				next;
				cutin "minuel01",255;
				mes "[レオ]";
				mes "どういうことでしょうね。";
				mes "仕事を依頼した立場でこんなことを";
				mes "言うのもあれなんですが、";
				mes "私はマヨル・ジュンがどうして";
				mes "あなたにこんなことをさせているのか";
				mes "理解できません。";
				next;
				mes "[レオ]";
				mes "……マヨル・ジュンは";
				mes "いったい何を考えているのか……";
				next;
				mes "[レオ]";
				mes "ま、とにかく！";
				mes "あなたにお手伝いいただいたことは";
				mes "上層部にしっかりと伝達して";
				mes "おきますね！";
				next;
				mes "‐マヨル・ジュン　カルデュイが";
				mes "　呼んでいるらしい。";
				mes "　王宮にいるカルデュイに会いに";
				mes "　行こう‐";
				close;
			}
			mes "[レオ]";
			mes "あなたにお手伝いいただいたことは";
			mes "上層部にしっかりと伝達して";
			mes "おきますね！";
			close;
		}
		mes "[レオ]";
		mes "こんにちは！";
		emotion 0,"エクラージュガード#reo";
		next;
		mes "[レオ]";
		mes "本当にこんにちは！";
		next;
		mes "[レオ]";
		mes "……";
		next;
		if(select("なんですか？","変な妖精だ") == 2) {
			mes "[レオ]";
			mes "ちょ！　違います。";
			mes "私は変なラフィネではありません。";
			mes "誤解ですよ、誤解……";
			close;
		}
		mes "[レオ]";
		mes "マヨル・ジュンが、あなたは";
		mes "ラフィネとエクラージュのために";
		mes "どんなこともしてくれるはずだと";
		mes "言っていました。";
		next;
		mes "[レオ]";
		mes "それで今一番に処理しなければ";
		mes "ならない案件を処理してもらおうと……";
		next;
		if(select("何をすればいい？","断る！") == 2) {
			mes "[レオ]";
			mes "あなたの意思に任せなさいと";
			mes "言われたけど、やはりこのように";
			mes "なってしまうんですね……。";
			mes "悲しいです。";
			close;
		}
		mes "[レオ]";
		mes "頼みたいのは";
		mes "スプレンディッド前線基地で作られる";
		mes "ピンギキュラの果実ジャムと";
		mes "ルシオラヴェスパのハチ蜜を少し";
		mes "用意してほしいんです。";
		next;
		mes "[レオ]";
		mes "霧の森という壁をどうしても";
		mes "越えられなくて……";
		next;
		menu "至急な案件ではないの？",-;
		mes "[レオ]";
		mes "私が！";
		mes "それを食べないと死にそうなんですよ!!";
		mes "至急なんです!!!!";
		next;
		mes "[レオ]";
		mes "スプレンディッドを行き来して";
		mes "いるんじゃないんですか？";
		mes "来るときにちょこっと持って来て";
		mes "くれれば、私は助かるんです！";
		mes "二度と同じお願いはしませんから。";
		next;
		mes "[レオ]";
		mes "ではお願いしますね！";
		mes "^FF0000ピンギキュラの果実ジャム3個^000000と";
		mes "^FF0000ルシオラヴェスパのハチ蜜3個^000000です～";
		mes "スプレンディッド前線基地で";
		mes "販売しています。";
		next;
		mes "[レオ]";
		mes "この2つを手に入れるためには";
		mes "スプレンディッドコインが";
		mes "必要になるはずです。";
		mes "コインはスプレンディッドで";
		mes "少し働くと稼げますよ！";
		next;
		mes "[レオ]";
		mes "スプレンディッドの仕事を";
		mes "手伝うということは、";
		mes "エクラージュのためでもあります。";
		mes "さあ、頑張ってください！";
		setquest 7420;
		close;
	case 6:
	case 7:
		mes "[レオ]";
		mes "果実ジャムとハチ蜜は";
		mes "本当に素晴らしい味でした！";
		mes "前線基地のやつら、";
		mes "こんなに美味しい物を";
		mes "食べていたんですね!!";
		next;
		mes "[レオ]";
		mes "あなたにお手伝いいただいたことは";
		mes "上層部に伝えておきました！";
		mes "またお会いしましょう!!";
		close;
	case 8:
		if(checkquest(7423)) {
			mes "‐レオは、自分たちの王である";
			mes "　カルデュイを、それほど信頼して";
			mes "　いないようだ。";
			mes "　他のラフィネからも話を";
			mes "　聞いてみよう‐";
			close;
		}
		mes "[レオ]";
		mes "仕事を依頼した立場でこんなことを";
		mes "言うのもあれなんですが、";
		mes "私はマヨル・ジュンがどうして";
		mes "あなたにラフィネの手伝いを";
		mes "させたのか、理解できません。";
		next;
		mes "[レオ]";
		mes "……マヨル・ジュンは";
		mes "いったい何を考えているのか……";
		next;
		menu "王が嫌いなの？",-;
		emotion 9,"エクラージュガード#reo";
		mes "[レオ]";
		mes "いいえ！　まさか！";
		mes "ただ……そうですね……";
		mes "近づきにくい、信じられない……";
		mes "まあ、そんな感じです。";
		next;
		mes "[レオ]";
		mes "何も悪いことをしていないので";
		mes "警戒する必要も本来なら";
		mes "ないんですけど……";
		next;
		mes "[レオ]";
		mes "前例がないわけではありませんが、";
		mes "かなり特別な王ですので……";
		mes "色々と気になるんですよね。";
		next;
		mes "[レオ]";
		mes "おっと！";
		mes "外部の人であるあなたに";
		mes "ちょっと話し過ぎてしまいました。";
		mes "今の話は、どうか！";
		mes "どうか忘れてください！";
		next;
		setquest 7423;
		if(checkquest(7423) && checkquest(7424) && checkquest(7425) && checkquest(7426)) {
			// 未調査
			mes "‐理由については、";
			mes "　カルデュイに直接聞いて";
			mes "　みるのが早そうだ‐";
			set ECL_3QUE,9;
			setquest 7427;
			delquest 7423;
			delquest 7424;
			delquest 7425;
			delquest 7426;
			delquest 72253;
			close;
		}
		mes "‐レオは、自分たちの王である";
		mes "　カルデュイを、それほど信頼して";
		mes "　いないようだ。";
		mes "　他のラフィネからも話を";
		mes "　聞いてみよう‐";
		close;
	case 9:
		mes "[レオ]";
		mes "マヨル・ジュンについての話は";
		mes "もうやめましょう。";
		mes "あなたは今の仕事だけに";
		mes "集中してください！";
		next;
		mes "‐今まで聞いた話から、";
		mes "　カルデュイについてラフィネは";
		mes "　対外的には好意を示しているが、";
		mes "　それとはまったく逆の";
		mes "　不安や不信を強く抱いているようだ‐";
		next;
		mes "‐理由については、";
		mes "　カルデュイに直接聞いて";
		mes "　みるのが早そうだ‐";
		close;
	case 10:
		if(checkquest(7433)) {
			if(checkquest(7433) & 0x2) {
				delquest 7433;
				mes "[レオ]";
				mes "モンスターが減る気配はないけど";
				mes "パトロールをすることで、";
				mes "旅人たちからのクレームは";
				mes "少し減ります。";
				next;
				mes "[レオ]";
				mes "時間に余裕があれば、";
				mes "またパトロールにいきましょう。";
				close;
			}
			mes "[レオ]";
			mes "モンスターは疲れを知らないのか……";
			mes "旅人たちから、周辺の安全について";
			mes "クレームが続出しています。";
			mes "本当に……困った奴らです。";
			next;
			mes "[レオ]";
			mes "次のパトロールの時も";
			mes "是非お願いします。";
			mes "はああ……";
			close;
		}
		if(checkquest(7432)) {
			if(checkquest(7432) & 0x4) {
				mes "[レオ]";
				mes "今回も良い成果です！";
				mes "さあ、今回の仕事に対する";
				mes "報酬です。";
				next;
				if(checkitemblank() == 0) {
					mes "[レオ]";
					mes "むむ！";
					mes "お礼をお渡ししようと思いましたが";
					mes "持ち物が多すぎるようです。";
					mes "持ち物を整理してから、";
					mes "もう一度話しかけてください。";
					close;
				}
				mes "[レオ]";
				mes "またパトロールを手伝ってくれる";
				mes "のであれば、明日来てください！";
				mes "あなたの分の枠は、";
				mes "私の方で用意しておきます。";
				mes "ははは！";
				chgquest 7432,7433;
				getitem 6081,1;
				close;
			}
			mes "[レオ]";
			mes "メンブリッツとペタルを各5体ずつ。";
			mes "よろしくお願いします！";
			next;
			mes "[レオ]";
			mes "しかし、正直なところ、";
			mes "メンブリッツって綺麗ですよね？";
			mes "それなのにどうしてあのように";
			mes "なってしまったのか……。";
			next;
			mes "[レオ]";
			mes "同じラフィネ？";
			mes "いや、あれはラフィネでは";
			mes "ありません。";
			next;
			mes "[レオ]";
			mes "ペタルもなぁ……";
			mes "ペタルも本当にかわいいです。";
			mes "ヤイに1匹おいて";
			mes "飼いたいくらいです。";
			mes "だけど……";
			next;
			mes "[レオ]";
			mes "あいつらは花壇を壊します！";
			mes "なので、飼うことはできないし";
			mes "放置しておくことも";
			mes "できないんです……。";
			close;
		}
		mes "[レオ]";
		mes "こんにちは！";
		mes "いいところに来ました。";
		mes "花が咲いた大地のメンブリッツと";
		mes "ペタルを退治しに行きましょう！";
		next;
		mes "[レオ]";
		mes "旅人から、あいつらに迷惑を";
		mes "かけられているというクレームが";
		mes "いっぱい入って来ています。";
		mes "一緒にやってみませんか？";
		next;
		switch(select("行く！　やる！　やっつける！","今日はダメ！","果実ジャムとハチ蜜は必要ないの？")) {
		case 1:
			mes "[レオ]";
			mes "戦意を燃やしていますね！";
			mes "いいですね、行きましょう！";
			mes "もちろん！　あなただけ！";
			mes "旅人たちをイジメたり、";
			mes "花壇を壊しているメンブリッツと";
			mes "ペタルを懲らしめに。";
			next;
			mes "[レオ]";
			mes "メンブリッツ、ペタルを各5匹";
			mes "退治してきてください。";
			mes "エクラージュ前、";
			mes "ビフロストタワーのある";
			mes "花が咲いた大地に";
			mes "集まっているはずです。";
			setquest 7432;
			close;
		case 2:
			mes "[レオ]";
			mes "なんだ……やらないんですか……。";
			mes "じゃあ、ひとりでやろ。";
			mes "ひとり寂しく……";
			close;
		case 3:
			mes "[レオ]";
			mes "ああ、果実ジャムとハチ蜜……。";
			mes "それは当分食べないことにしました。";
			mes "好きなだけ食べていたら、";
			mes "お腹を壊してしまいまして。";
			mes "……悲しい話です。";
			close;
		}
	default:
		mes "[レオ]";
		mes "アールブヘイムの関門である、";
		mes "ラフィネの首都エクラージュに";
		mes "ようこそ！";
		mes "旅を楽しんでください！";
		close;
	}
}

ecl_tdun04.gat,32,35,3	script	ヒシエ#tlord	623,{
	switch(ECL_3QUE) {
	case 12:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "旅人よ、何の用だ？";
		next;
		mes "‐目の前に立っているラフィネは";
		mes "　大きな背に濃い色の皮膚、";
		mes "　小さな羽を持っている。";
		mes "　まるで上級ラフィネ・ドナと";
		mes "　下級ラフィネ・パパンを";
		mes "　うまく混ぜ合わせたようだ‐";
		next;
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "何をじろじろ見ている？";
		mes "私の姿に対して品評するのが";
		mes "目的なのか？";
		mes "君はいったい誰だ？";
		next;
		menu "カルデュイの兄を知りませんか？",-;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "ふむ……カルはあまり詳しく";
		mes "私のことを話さなかったようだな。";
		mes "名前や容姿も聞かずに、";
		mes "ただ「はい」と言って来たのか？";
		next;
		mes "[ヒシエ]";
		mes "私がカルの兄のヒシエだ。";
		mes "カルとは双子だが……";
		mes "まあ、肌の色やら何やら、";
		mes "いろいろ違うから、戸惑うのもわかる。";
		next;
		mes "[ヒシエ]";
		mes "その手に持っている手紙を";
		mes "渡しに来たのだろう？";
		next;
		mes "[ヒシエ]";
		mes "以前もらった手紙に客が訪れるかもと";
		mes "書いてあったが、このことだったのか。";
		mes "手紙を読むから少し待ってくれ。";
		next;
		mes "‐カルデュイの兄、ヒシエに";
		mes "　カルデュイからの手紙を渡した。";
		mes "　もう一度ヒシエに話しかけよう‐";
		set ECL_3QUE,13;
		chgquest 7434,7435;
		close2;
		cutin "hisie01",255;
		end;
	case 13:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "待たせて悪かった。";
		mes "手紙は全部読んだ。";
		mes "友達のことが書かれていたが、";
		mes "それが君なのか。";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "君に私のことを";
		mes "詳しく伝えなかったのは、";
		mes "わざと驚かせるためだったようだ。";
		mes "相変わらずのようだな。";
		next;
		mes "[ヒシエ]";
		mes "私の姿が変わっているのは";
		mes "すでにわかっているとは思うが、";
		mes "ドナとパパンの混血だからだ。";
		next;
		mes "[ヒシエ]";
		mes "話すと複雑だが、君も知っておく";
		mes "必要がありそうだ。";
		mes "手紙には君の紹介のほかに、";
		mes "もうひとつ書かれていた。";
		next;
		mes "[ヒシエ]";
		mes "しかし……";
		mes "今になってエイヴァントを";
		mes "探している理由は何だ……？";
		next;
		if(select("エイヴァント？","もうひとつ？") == 2) {
			mes "[ヒシエ]";
			mes "エイヴァントを探してほしいそうだ。";
			mes "君が大きな力になってくれるらしいぞ？";
			next;
		}
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "エイヴァントは魔学者であり……";
		mes "そして……私とカルの父親だ。";
		mes "けどどうして君に頼んだんだ？";
		mes "他の人に話しづらいなら、";
		mes "私に頼んでもいいだろうに。";
		next;
		mes "[ヒシエ]";
		mes "まあとにかく、エイヴァントが";
		mes "今どこにいるのかは私も知らない。";
		mes "あまり知りたくもないし、";
		mes "正直に言うとカルが探しているのも";
		mes "止めたいが……";
		next;
		menu "お父さんでしょう？",-;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "ただ生物学的に父親だということだ。";
		mes "実際には私たちは彼の実験体に";
		mes "過ぎない。";
		mes "私たちは彼の仮説を証明するために";
		mes "作られた存在だから。";
		next;
		mes "[ヒシエ]";
		mes "だから父子間の情みたいものはない。";
		mes "カルはエイヴァントを消すために";
		mes "探しているのかもしれない……。";
		next;
		menu "実験？　仮説？",-,"作られた存在？",-;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "混血ながらマヨルになった";
		mes "セネスについては知っているか？";
		mes "エイヴァントは純粋ではない";
		mes "混血のドナでも、マヨルに選ばれる";
		mes "ことがあるということに興味が";
		mes "あったらしい。";
		next;
		mes "[ヒシエ]";
		mes "そしていくつかの仮説を立てて";
		mes "それを証明するために実験を行った。";
		mes "カルは徹底的に計算され作られた";
		mes "エイヴァントの作品だ。";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "私は実験に伴う予想外の事故で";
		mes "生まれた……。";
		mes "とにかくカルは王になったが";
		mes "自身の人生は失ってしまった。";
		mes "エイヴァントに対する憎しみは";
		mes "変わっていないだろう。";
		next;
		mes "[ヒシエ]";
		mes "そのカルがエイヴァントを";
		mes "探している……？";
		mes "何か心境に変化があったか、";
		mes "あるいは、何か考えがあるんだな。";
		mes "マヨルになっていつの間にか、";
		mes "あの泣き虫が大きくなったようだ。";
		next;
		menu "泣き虫？",-;
		mes "[ヒシエ]";
		mes "冗談だと思うか？";
		mes "君の知っているカルデュイは";
		mes "自信にあふれているからか？";
		next;
		cutin "hisie04",0;
		mes "[ヒシエ]";
		mes "まあ、そうだろな。";
		mes "マヨルになってから";
		mes "カルの性格は大きく変わったようだ。";
		mes "それを実際に一度見てみたかったが。";
		next;
		menu "直接会いに行けば？",-;
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "私がエクラージュに入ったら";
		mes "小さなラフィネたちがビックリする。";
		mes "私はドナでもパパンでもない。";
		mes "どちらにも属していない。";
		next;
		mes "[ヒシエ]";
		mes "その昔にプロレンスがしようとした";
		mes "血統を汚すこと。";
		mes "彼が求めていたのが私のような";
		mes "者なのではないか……。";
		next;
		menu "プロレンス？",-;
		mes "[ヒシエ]";
		mes "暴君と名高い混血王セネス。";
		mes "その父親がプロレンスだ……。";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "とにかくエイヴァントを探さないと。";
		mes "あのふざけた実験が元老会にばれて";
		mes "姿を隠したのも数十年前だ。";
		mes "きっとどこかで自身の実験が成功したと";
		mes "喜んでいるんだろう。";
		mes "彼はそのような人物だ。";
		next;
		mes "[ヒシエ]";
		mes "私はエクラージュに入れないから、";
		mes "エクラージュ内部の探索は君に任す。";
		mes "カル以外に、誰か情報が集まりそうな";
		mes "地位にいる知り合いはいないか？";
		mes "もしいるなら、話を聞いてみてくれ。";
		next;
		mes "[ヒシエ]";
		mes "私は私なりにエクラージュの外を";
		mes "調べてみる。";
		mes "痕跡でも残っていればいいが……。";
		mes "さあ、探しに行こう！";
		next;
		cutin "hisie01",255;
		mes "‐情報が集まりそうな地位にいる";
		mes "　人物から話を聞いてくるように";
		mes "　言われた。";
		mes "　軍参謀シナイムはそれに";
		mes "　当てはまりそうだ‐";
		next;
		mes "‐軍参謀シナイムから";
		mes "　話を聞いてみよう‐";
		set ECL_3QUE,14;
		chgquest 7435,7436;
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "良かったらエクラージュの入口まで";
		mes "送ろうか？";
		next;
		if(select("お願いする","断る") == 2) {
			mes "[ヒシエ]";
			mes "そうか。わかった。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "それじゃ行こうか。";
		close2;
		warp "ecl_fild01.gat",101,315;
		end;
	case 14:
	case 15:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "エクラージュ内部の捜索を頼む。";
		mes "カル以外に、誰か情報が集まりそうな";
		mes "地位にいる知り合いはいないか？";
		mes "もしいるなら、話を聞いてみてくれ。";
		next;
		cutin "hisie01",255;
		mes "‐情報が集まりそうな地位にいる";
		mes "　人物から話を聞いてくるように";
		mes "　言われた。";
		mes "　軍参謀シナイムはそれに";
		mes "　当てはまりそうだ‐";
		next;
		mes "‐軍参謀シナイムから";
		mes "　話を聞いてみよう‐";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "良かったらエクラージュの入口まで";
		mes "送ろうか？";
		next;
		if(select("お願いする","断る") == 2) {
			mes "[ヒシエ]";
			mes "そうか。わかった。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "それじゃ行こうか。";
		close2;
		warp "ecl_fild01.gat",101,315;
		end;
	case 16:
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "軍参謀が魔学者の支援をしていたのか？";
		mes "……怪しいな。";
		mes "素晴らしい研究成果を出してから発表し";
		mes "みんなを驚かせたいというならわかるが";
		mes "シナイムはそのような性格ではない。";
		mes "そうだろう？";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "それに、真理の扉の変わり者たちは";
		mes "自身の研究にプライドを持っている。";
		mes "だから、「何についての研究なのか」を";
		mes "隠すのは好まない傾向がある。";
		next;
		mes "[ヒシエ]";
		mes "その魔学者は何かあるな。";
		mes "調べて見た方がいい。";
		mes "魔学者が誰なのか分からないなら、";
		mes "シナイムの動きを調べてみるんだ。";
		next;
		mes "[ヒシエ]";
		mes "そこら辺は君に任せたよ。";
		mes "私も気になっていることがあってな。";
		mes "それを確認して来る。";
		mes "では、よい知らせを待っているぞ。";
		next;
		cutin "hisie03",255;
		mes "‐軍参謀シナイムをもっと調べる";
		mes "　必要がある。";
		mes "　いつも王宮周辺を見ている人物……";
		mes "　エクラージュガード・ミニュエルなら";
		mes "　何か知っているかもしれない‐";
		set ECL_3QUE,17;
		chgquest 7438,7439;
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "良かったらエクラージュの入口まで";
		mes "送ろうか？";
		next;
		if(select("お願いする","断る") == 2) {
			mes "[ヒシエ]";
			mes "そうか。わかった。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "それじゃ行こうか。";
		close2;
		warp "ecl_fild01.gat",101,315;
		end;
	case 17:
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "軍参謀が魔学者の支援をしていたのか？";
		mes "……怪しいな。";
		mes "素晴らしい研究成果を出してから発表し";
		mes "みんなを驚かせたいというならわかるが";
		mes "シナイムはそのような性格ではない。";
		mes "そうだろう？";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "それに、真理の扉の変わり者たちは";
		mes "自身の研究にプライドを持っている。";
		mes "だから、「何についての研究なのか」を";
		mes "隠すのは好まない傾向がある。";
		next;
		mes "[ヒシエ]";
		mes "その魔学者は何かあるな。";
		mes "調べて見た方がいい。";
		mes "魔学者が誰なのか分からないなら、";
		mes "シナイムの動きを調べてみるんだ。";
		next;
		mes "[ヒシエ]";
		mes "そこら辺は君に任せたよ。";
		mes "私も気になっていることがあってな。";
		mes "それを確認して来る。";
		mes "では、よい知らせを待っているぞ。";
		next;
		cutin "hisie03",255;
		mes "‐軍参謀シナイムをもっと調べる";
		mes "　必要がある。";
		mes "　いつも王宮周辺を見ている人物……";
		mes "　エクラージュガード・ミニュエルなら";
		mes "　何か知っているかもしれない‐";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "良かったらエクラージュの入口まで";
		mes "送ろうか？";
		next;
		if(select("お願いする","断る") == 2) {
			mes "[ヒシエ]";
			mes "そうか。わかった。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "それじゃ行こうか。";
		close2;
		warp "ecl_fild01.gat",101,315;
		end;
	case 18:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "成果はあったのか？";
		next;
		mes "‐ミニュエルから得た情報を伝えた‐";
		next;
		mes "[ヒシエ]";
		mes "ふむ……";
		mes "シナイムが支援する魔学者が誰なのか";
		mes "直接行って確認するしかないな。";
		next;
		mes "[ヒシエ]";
		mes "今の話と関係あるかわからないが、";
		mes "東にある洞窟で研究用のヤイを";
		mes "1つ発見したんだ。";
		next;
		mes "[ヒシエ]";
		mes "普通のヤイではなく、";
		mes "簡単な研究用の建物として、";
		mes "解放されているヤイだ。";
		mes "秘密研究をしたり、";
		mes "エイヴァントが隠れたり";
		mes "できる場所ではなさそうだが……。";
		next;
		mes "[ヒシエ]";
		mes "それでも、他に手掛りもないしな。";
		mes "まずはそこを訪ねてみて";
		mes "誰がいるのか直接確認してみよう。";
		next;
		mes "[ヒシエ]";
		mes "そうだな……";
		mes "よし、この計画で行こう。";
		next;
		mes "[ヒシエ]";
		mes "君がほこりの塊と落ち葉のしおりを";
		mes "シナイムに頼まれたとおり10個持って";
		mes "シナイムに配達を頼まれた風に";
		mes "装ってヤイに接近するんだ。";
		next;
		mes "[ヒシエ]";
		mes "私は少し離れたところに隠れて";
		mes "ヤイから出てくるのが";
		mes "エイヴァントなのか確認する。";
		mes "まあ、誰も出てこない可能性も";
		mes "あるが……";
		mes "とにかくやってみよう。";
		next;
		mes "[ヒシエ]";
		mes "私は目立たないように";
		mes "エクラージュに侵入するつもりだ。";
		next;
		mes "[ヒシエ]";
		mes "エクラージュの広場に入る";
		mes "手前の道で会おう。";
		mes "実験材料は忘れずに";
		mes "持って来るようにな。";
		next;
		cutin "hisie03",255;
		mes "‐ヒシエが東の方角で発見したヤイが、";
		mes "　シナイムの支援する魔学者が研究を";
		mes "　行っているヤイの可能性がある‐";
		next;
		mes "‐シナイムに配達を頼まれたように";
		mes "　装ってヤイを訪ね、ヤイにいる人物を";
		mes "　確認することにした‐";
		next;
		mes "‐まずはほこりの塊と落ち葉のしおりを";
		mes "　10個持って、ヒシエと落ち合う予定の";
		mes "　エクラージュ広場前に行こう‐";
		set ECL_3QUE,19;
		chgquest 7440,7441;
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "とりあえずエクラージュの入口まで";
		mes "一緒にいこうか？";
		next;
		if(select("お願いする","まだやることがあるので断る") == 2) {
			mes "[ヒシエ]";
			mes "そうか。わかった。";
			mes "できるだけ早く済ませてくれよ。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "それじゃ行こうか。";
		close2;
		warp "ecl_fild01.gat",101,315;
		end;
	case 19:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "自然に接近するためには、";
		mes "実験材料が必要になる。";
		mes "実験材料を手に入れて";
		mes "シナイムに配達を頼まれたように";
		mes "装って接近するんだ。";
		next;
		mes "[ヒシエ]";
		mes "たしかほこりの塊と";
		mes "落ち葉のしおり10個ずつ";
		mes "だったよな？";
		next;
		cutin "hisie03",255;
		mes "‐ほこりの塊と落ち葉のしおりを";
		mes "　10個持って、ヒシエと落ち合う予定の";
		mes "　エクラージュ広場前に行こう‐";
		close;
	case 20:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "髪の毛の色が変わっていたが、";
		mes "確かにエイヴァントだった。";
		mes "あんな所にいたとは……";
		next;
		mes "[ヒシエ]";
		mes "カルにこの事実を知らせなければ。 ";
		mes "急げ！";
		next;
		cutin "hisie01",255;
		mes "‐軍参謀シナイムが支援していた";
		mes "　魔学者は、エイヴァントだった。";
		mes "　急いでカルデュイに報告に行こう‐";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "良かったらエクラージュの入口まで";
		mes "送ろうか？";
		next;
		if(select("お願いする","断る") == 2) {
			mes "[ヒシエ]";
			mes "そうか。わかった。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "それじゃ行こうか。";
		close2;
		warp "ecl_fild01.gat",101,315;
		end;
	case 21:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "エイヴァントが何を研究しているのか";
		mes "確かめてみよう。";
		mes "急ごう！";
		next;
		cutin "hisie01",255;
		mes "‐エイヴァントが何の研究をしていたか";
		mes "　確認するため、エイヴァントのヤイを";
		mes "　再度調べに行こう‐";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "良かったらエクラージュの入口まで";
		mes "送ろうか？";
		next;
		if(select("お願いする","断る") == 2) {
			mes "[ヒシエ]";
			mes "そうか。わかった。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "それじゃ行こうか。";
		close2;
		warp "ecl_fild01.gat",101,315;
		end;
	case 22:
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "エイヴァントの研究資料を";
		mes "早くカルに持って行くんだ！";
		next;
		cutin "hisie01",255;
		mes "‐エイヴァントの研究資料を";
		mes "　カルデュイに届けよう‐";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "良かったらエクラージュの入口まで";
		mes "送ろうか？";
		next;
		if(select("お願いする","断る") == 2) {
			mes "[ヒシエ]";
			mes "そうか。わかった。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "それじゃ行こうか。";
		close2;
		warp "ecl_fild01.gat",101,315;
		end;
	case 23:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "オーブに対する警戒を";
		mes "強化するのは当然だとして……";
		mes "何か忘れているような気が……";
		next;
		switch(select("エイヴァントについて","軍参謀シナイムについて")) {
		case 1:
			mes "[ヒシエ]";
			mes "奴はただへらへら笑いながら";
			mes "黙秘している。";
			mes "今自分がおかれている状況も";
			mes "楽しんでいるのかもしれない。";
			next;
			mes "[ヒシエ]";
			mes "頭のおかしな奴とは思っていたが……";
			mes "あいつの性格を久しぶりに";
			mes "再確認しただけでイライラする。";
			next;
			cutin "hisie03",0;
			mes "[ヒシエ]";
			mes "それに今になってまた";
			mes "私の体に興味が湧いたようで、";
			mes "対面するたびに反対に";
			mes "いろいろ質問されて嫌になる。";
			next;
			mes "[ヒシエ]";
			mes "混血者がここまで大きく成長したことに";
			mes "興味が出たんだろう。";
			mes "私はあのような者が";
			mes "父親だということを死ぬまで認めない。";
			close2;
			cutin "hisie03",255;
			end;
		case 2:
			cutin "hisie03",0;
			mes "[ヒシエ]";
			mes "……！";
			mes "そうだ！　シナイム！";
			mes "どうしてそれを忘れていたんだ？";
			mes "あまりにもエイヴァントばかりに";
			mes "気を取られていて、忘れていたよ。";
			next;
			cutin "hisie01",0;
			mes "[ヒシエ]";
			mes "シナイムは私たちがエイヴァントを";
			mes "捕えたことをまだ知らない。";
			mes "彼女がエイヴァントの支援者";
			mes "であるなら、今頃不安になって";
			mes "いることだろう……";
			next;
			menu "行って調べてみましょうか？",-;
			mes "[ヒシエ]";
			mes "本当か？";
			mes "そうしてくれるのであれば助かる。";
			mes "私やカルが直接出るのは";
			mes "今は避けたほうが良さそうだからな。";
			next;
			cutin "hisie02",0;
			mes "[ヒシエ]";
			mes "特にカルは変な誤解をされやすい。";
			mes "先入観というのはとても怖いから。";
			next;
			mes "[ヒシエ]";
			mes "それじゃ、よろしく頼む。";
			mes "くれぐれも気をつけてな。";
			next;
			cutin "hisie03",255;
			mes "‐軍参謀シナイムから";
			mes "　話を聞いて来よう‐";
			set ECL_3QUE,24;
			chgquest 72268,7445;
			next;
			cutin "hisie01",0;
			mes "[ヒシエ]";
			mes "良かったらエクラージュの入口まで";
			mes "送ろうか？";
			next;
			if(select("お願いする","断る") == 2) {
				mes "[ヒシエ]";
				mes "そうか。わかった。";
				close2;
				cutin "hisie01",255;
				end;
			}
			mes "[ヒシエ]";
			mes "それじゃ行こうか。";
			close2;
			warp "ecl_fild01.gat",101,315;
			end;
		}
	case 24:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "君はシナイムと何度か接しているから";
		mes "接近するのは難しくないはず。";
		mes "カルは確かにマヨルではあるが、";
		mes "たぶん歴代のマヨルの中で";
		mes "一番権力を持っていないマヨルだから。";
		next;
		mes "[ヒシエ]";
		mes "大半のラフィネはカルが歴代マヨルの";
		mes "情報をただそのまま保管して";
		mes "静かに次に譲ることを願っている。";
		mes "何かをしようとすると";
		mes "反発が酷いらしい。";
		next;
		mes "[ヒシエ]";
		mes "カルには味方が少ない。";
		mes "だから君が力になってほしい。";
		mes "シナイムについては君に任せる。";
		next;
		mes "[ヒシエ]";
		mes "何かわかったら、カルの所に";
		mes "行ってくれ。";
		next;
		mes "[ヒシエ]";
		mes "良かったらエクラージュの入口まで";
		mes "送ろうか？";
		next;
		if(select("お願いする","断る") == 2) {
			mes "[ヒシエ]";
			mes "そうか。わかった。";
			close2;
			cutin "hisie01",255;
			end;
		}
		mes "[ヒシエ]";
		mes "それじゃ行こうか。";
		close2;
		warp "ecl_fild01.gat",101,315;
		end;
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "エクラージュに行こう。";
		mes "カルも含めて話をする";
		mes "必要がありそうだ。";
		close2;
		cutin "hisie01",255;
		end;
	case 33:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "最近はここより宮殿に";
		mes "長くいるようになった。";
		mes "消えたオーブ内の核に代わって";
		mes "魔力を送っているから……";
		next;
		cutin "hisie04",0;
		mes "[ヒシエ]";
		mes "君には感謝している。";
		mes "すべてのことが終わった時、";
		mes "話せなかったことを話せたらいいなと";
		mes "思っている。";
		close2;
		cutin "hisie01",255;
		end;
	default:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "好奇心でここまで登って来たなら、";
		mes "もう降りた方がいいぞ。";
		mes "最近プロフェッサーの調子が";
		mes "イマイチだからな。";
		close2;
		cutin "hisie01",255;
		end;
	}
}

mora.gat,103,74,5	script	遠征隊員#tl01	946,{
	mes "[遠征隊員]";
	mes "エクラージュに一度行ってみたくて、";
	mes "連合軍の駐屯地から霧の森を通って";
	mes "ここまで来たけど……";
	mes "霧の森は敵が強いから、";
	mes "もう二度と入りたくない！";
	next;
	mes "[遠征隊員]";
	mes "ああ……";
	mes "エクラージュに行った後、";
	mes "どうやって駐屯地に";
	mes "戻ればいいんだ……";
	next;
	switch(select("エクラージュ？","不思議な種について教える","頑張って")) {
	case 1:
		mes "[遠征隊員]";
		mes "おや？　まだ知らないのか？";
		mes "エクラージュはラフィネの首都だ。";
		mes "物資の運送などでエクラージュから";
		mes "モーラに来るラフィネと旅人たちが";
		mes "多いけど……";
		next;
		mes "[遠征隊員]";
		mes "君もここまで来たなら";
		mes "一度訪問して見なさい。";
		mes "まあ、観光だよ、観光！";
		mes "ビフロストから北に";
		mes "まっすぐ進めばいい。";
		close;
	case 2:
		mes "[遠征隊員]";
		mes "うむ？";
		mes "霧の森で採取した不思議な種を";
		mes "使って飛んで行けば……";
		mes "スプレンディッドの近くまで";
		mes "行けるのか？";
		next;
		mes "[遠征隊員]";
		mes "そのような方法あったとは。";
		mes "はは。ありがとう。";
		close;
	case 3:
		mes "[遠征隊員]";
		mes "私を励ましてくれてるのか？";
		mes "優しいんだね……。";
		close;
	}
}

ecl_in01.gat,32,52,5	script	旅人ポメ#tl01	515,3,3,{
	if(ECL_3QUE == 1 || ECL_3QUE == 2) {
		mes "[ポメ]";
		mes "エクラージュガードがあなたを";
		mes "探していましたよ。";
		mes "東側の出入り口にいるようですが、";
		mes "行かないのですか？";
		next;
		mes "[ポメ]";
		mes "丁寧な頼み方で悪い気分には";
		mes "ならなかったんじゃないですか？";
		mes "そうです！";
		mes "エクラージュのラフィネたちは";
		mes "旅人にいつも優しいんです。";
		close;
	}
	if(ECL_3QUE == 8) {
		if(checkquest(7424)) {
			mes "[ポメ]";
			mes "きっと何かがあります。";
			mes "私が観察してみた結果としては、";
			mes "彼らは王の誕生を喜びながらも";
			mes "不安を抱いていました。";
			close;
		}
		mes "[ポメ]";
		mes "今までラフィネの王様のために";
		mes "働いていたのですか?!";
		mes "どうして私に一言も";
		mes "言ってくれなかったんですか？";
		mes "ポメも王様にまた会いたいです。";
		next;
		mes "[ポメ]";
		mes "祝いの場で一度挨拶しただけ";
		mes "だったので、あまり話をすることも";
		mes "できませんでした……。";
		mes "本当に美しい方だったとしか";
		mes "覚えていません。";
		next;
		mes "[ポメ]";
		mes "けれど、ラフィネたちは";
		mes "自分たちの王をあまり喜んで";
		mes "受け入れてはいないようです。";
		mes "どうしてでしょうか？";
		mes "もしかして何か知っているんですか？";
		next;
		mes "[ポメ]";
		mes "無理に聞いちゃうと";
		mes "ラフィネたちの自尊心を";
		mes "刺激してしまいそうで聞けません。";
		next;
		setquest 7424;
		if(checkquest(7423) && checkquest(7424) && checkquest(7425) && checkquest(7426)) {
			mes "‐今まで聞いた話から、";
			mes "　カルデュイについてラフィネは";
			mes "　対外的には好意を示しているが、";
			mes "　それとはまったく逆の";
			mes "　不安や不信を強く抱いているようだ‐";
			next;
			mes "‐理由については、";
			mes "　カルデュイに直接聞いて";
			mes "　みるのが早そうだ‐";
			set ECL_3QUE,9;
			setquest 7427;
			delquest 7423;
			delquest 7424;
			delquest 7425;
			delquest 7426;
			delquest 72253;
			close;
		}
		mes "‐ポメの話を興味深く聞いた。 ";
		mes "　信頼されていない王……";
		mes "　他のラフィネたちから";
		mes "　もっと話を聞いて見よう‐";
		close;
	}
	if(ECL_3QUE == 9) {
		mes "[ポメ]";
		mes "そろそろ次の地域まで移動する";
		mes "計画をたてます。";
		mes "このまま戻るか、そうでなければ";
		mes "モーラまで行くか……悩みますね。";
		close;
	}
	if(ECL_3QUE >= 3) {
		mes "[ポメ]";
		mes "あなたは忙しそうですね。";
		mes "あなたの名前をあちこちで";
		mes "いっぱい聞きました。";
		mes "もうラフィネたちと";
		mes "友達になりましたね！";
		close;
	}
	if(checkquest(7411) && checkquest(7412) && checkquest(7413)) {
		doevent "エクラージュガード#tl01::OnStart";
	}
	mes "[ポメ]";
	mes "あなた、ミッドガルドの方ですよね?!";
	mes "あなたの姿、それにその服装！";
	mes "エクラージュの近くには、";
	mes "あなたのような格好の人たちは";
	mes "住んでいません。";
	next;
	mes "[ポメ]";
	mes "私はアールブヘイムの中部から来た";
	mes "ポメと言います。";
	mes "本当……エクラージュに来て";
	mes "よかった……。";
	mes "ここでミッドガルドの人と";
	mes "出会えるとは。";
	next;
	mes "[ポメ]";
	mes "エクラージュには旅人が";
	mes "いっぱい集まるけど、最近までは";
	mes "アールブヘイム出身が大半でしたから、";
	mes "とても嬉しいです。";
	next;
	switch(select("旅人が多い理由","エクラージュの名所は？")) {
	case 1:
		mes "[ポメ]";
		mes "旅人が多い理由……";
		mes "一つ目の理由は、ここでは誰でも";
		mes "簡単にコミュニケーションが";
		mes "とれるからでしょう。";
		next;
		mes "[ポメ]";
		mes "エクラージュはビフロストと共にあり、";
		mes "ビフロストの意思ですべての人種との";
		mes "言葉の壁がなくなっています。";
		mes "今の私とあなたのように。";
		next;
		mes "[ポメ]";
		mes "二つ目の理由は、エクラージュが";
		mes "アールブヘイムの終わりで始まりの";
		mes "関門……ヨトゥンヘイムに行ける";
		mes "唯一の通路だからです。";
		next;
		mes "[ポメ]";
		mes "そしてエクラージュに旅人が";
		mes "集まる一番の大きな理由は!!!";
		next;
		menu "理由は?!",-;
		emotion 56;
		mes "[ポメ]";
		mes "最近ここに新しい";
		mes "^0000FFマヨル・ジュン^000000が誕生したからです!!!!";
		next;
		menu "マヨマヨ？",-;
		mes "[ポメ]";
		mes "いいえ、^0000FFマヨル・ジュン^000000です。";
		mes "ラフィネで最も位の高い者……";
		mes "「王」です。";
		mes "王様です！　王様が誕生したんです!!";
		next;
		mes "[ポメ]";
		mes "今回の王様はとても幼いのに";
		mes "マヨル・ジュンになったのです。";
		mes "ラフィネの王様らしく、";
		mes "とても美しいです。";
		next;
		menu "それはいつの話ですか？",-;
		mes "[ポメ]";
		mes "10年くらい前かな……？";
		mes "いや、5年？　15年……？";
		mes "　";
		mes "……とにかく、100年前では";
		mes "なかったと思います。";
		next;
		setquest 7411;
		if(checkquest(7411) && checkquest(7412) && checkquest(7413)) {
			doevent "エクラージュガード#tl01::OnStart";
		}
		mes "‐ポメという旅人はラフィネ王について";
		mes "　終わりなく喋り続けている。";
		mes "　他の人は気にしないで自分だけの";
		mes "　世界に入り込んでいて、";
		mes "　何を話しているのか分からない。";
		mes "　他の旅人と話してみよう‐";
		close;
	case 2:
		mes "[ポメ]";
		mes "エクラージュの名所ですか？";
		mes "それは勿論、ビフロストタワーです！";
		mes "厳密に言うとエクラージュ内部の";
		mes "名所ではありませんけど！";
		mes "あはははは";
		next;
		mes "[ポメ]";
		mes "だけど、私はまだ、";
		mes "見に行っていません……。";
		mes "ふうう、怖くて。";
		next;
		mes "[ポメ]";
		mes "ビフロストタワーは……";
		mes "あ、そうだ。";
		mes "リトリップさんは";
		mes "行って来ましたよね？";
		mes "リトリップさんから話してください！";
		next;
		mes "‐ビフロストタワーについては";
		mes "　リトリップという旅人が";
		mes "　よく知っているようだ‐";
		close;
	}
OnTouch:
	if(ECL_3QUE == 0 && BaseLevel >= 99) {
		mes "‐ラフィネではない複数の";
		mes "　アールブヘイムの旅人が";
		mes "　会話をしている‐";
		emotion 56,"旅人ポメ#tl01";
		emotion 56,"旅人リトリップ#tl02";
		emotion 56,"旅人チーバー#tl03";
		next;
		if(select("場所を変える","話しの輪に入ってみる") == 1) {
			mes "‐旅人達は";
			mes "　あまり気にしていないようだ‐";
			close;
		}
		mes "‐さりげなく近寄ったら";
		mes "　会話を止めた後、席を譲ってくれた。";
		mes "　話かけてみよう‐";
		//set ECL_3QUE,1;
		close;
	}
	end;
OnInit:
	waitingroom "エクラージュの王",0;
	end;
}

ecl_in01.gat,32,51,7	script	旅人リトリップ#tl02	513,{
	if(ECL_3QUE == 1) {
		mes "[リトリップ]";
		mes "見たところ、ラフィネたちは";
		mes "君に用があるようだな。";
		mes "東側の出入り口まで来てくれと";
		mes "言っていたぞ。";
		mes "行ってみなさい。";
		close;
	}
	if(ECL_3QUE == 2) {
		mes "[リトリップ]";
		mes "おや？";
		mes "君は東側の出入り口で";
		mes "誰かと会う約束をしていなかったか？";
		close;
	}
	if(ECL_3QUE == 8) {
		mes "[リトリップ]";
		mes "新しい王が誕生し盛り上がっていた";
		mes "雰囲気も落ち着いたようだ。";
		mes "だけど、なぜか人々の雰囲気が";
		mes "少し変だな……。";
		next;
		mes "[リトリップ]";
		mes "なぜだろう？";
		mes "気のせいならいいが……";
		close;
	}
	if(ECL_3QUE == 9) {
		mes "[リトリップ]";
		mes "私はチーバー君ともう一度";
		mes "タワーに挑戦してみるつもりだ。";
		mes "展望もいいらしいじゃないか。";
		mes "運が良ければモーラまで見えるだろ。";
		close;
	}
	if(ECL_3QUE >= 3) {
		mes "[リトリップ]";
		mes "この前、あのガードに呼ばれた後、";
		mes "あらゆるところで君の話を";
		mes "聞くようになったよ。";
		mes "重要な何かにかかわっているのか？";
		mes "君の認知度はかなりのものだよ。";
		close;
	}
	if(checkquest(7411) && checkquest(7412) && checkquest(7413)) {
		doevent "エクラージュガード#tl01::OnStart";
	}
	if(checkquest(7412)) {
		mes "[リトリップ]";
		mes "私の話だけでは面白くないだろ。";
		mes "ポメちゃんとチーバー君からも";
		mes "話を聞いてみなさい。";
		next;
		mes "[リトリップ]";
		mes "そして、ビフロストタワーの秘密を";
		mes "解いたら私にも教えてくれ。";
		mes "君には期待しているよ、ははは。";
		next;
		mes "‐他の旅人とも話をしてみよう‐";
		close;
	}
	mes "[リトリップ]";
	mes "ほおお、これはまた珍しい旅人ですな。";
	mes "こっちにいらっしゃい。";
	mes "私の名前はリトリップだ。";
	next;
	mes "[リトリップ]";
	mes "君はモーラから来たんだね？";
	mes "なら、来る途中に";
	mes "ビフロストタワーも見ただろ？";
	next;
	switch(select("外から見ただけです","中に入ってみた")) {
	case 1:
		mes "[リトリップ]";
		mes "そうか？　残念だな。";
		mes "まあ、あのタワーの中には";
		mes "恐ろしいモンスターたちがいるからな。";
		mes "無駄に挑戦して命を失うよりはいい。";
		break;
	case 2:
		mes "[リトリップ]";
		mes "そうか、凄かっただろ？";
		mes "あれでも遠い昔は";
		mes "とてもかっこいい展望台として";
		mes "使われたタワーなんだ。";
		next;
		mes "[リトリップ]";
		mes "今は恐ろしいモンスターたちの";
		mes "住み家になっているけどな。";
		mes "あのタワーに入って無事に";
		mes "出てきたところを見ると、";
		mes "君は相当な実力を持っているようだね。";
		break;
	}
	next;
	mes "[リトリップ]";
	mes "タワーの一番上には^0000FF怪しい錬金術師^000000が";
	mes "いるという噂がある。";
	mes "なぜそこにいるのかは分からないが、";
	mes "かなり昔からいるらしい。";
	next;
	mes "[リトリップ]";
	mes "もしその錬金術師が";
	mes "今も生きているのであれば、";
	mes "彼はその存在だけで";
	mes "生きた歴史と呼べるだろう。";
	next;
	mes "[リトリップ]";
	mes "その錬金術師とタワーとビフロストは";
	mes "エクラージュが作られる前から";
	mes "存在していたらしいからな。";
	next;
	mes "[リトリップ]";
	mes "今も多くの人たちが";
	mes "ビフロストの伝説を知る為に";
	mes "タワーに挑戦しているが、";
	mes "まだこの噂の真実を解き明かした";
	mes "者はいない。";
	next;
	menu "ラフィネたちは？",-;
	mes "[リトリップ]";
	mes "ん、ラフィネたち？";
	mes "彼らはなぜか分からないが、";
	mes "ビフロストタワー自体に";
	mes "あまり興味を示していない。";
	mes "ただの自然物のひとつとして";
	mes "認識しているようなんだ。";
	next;
	mes "[リトリップ]";
	mes "実を言うと彼らの能力であれば、";
	mes "十分に秘密を解くことが";
	mes "できるのだろうが……";
	mes "ビフロストタワー自体を";
	mes "尊重しているような感じがする。";
	next;
	mes "[リトリップ]";
	mes "だが、タワーに挑戦している者を";
	mes "止めたりしていないのを見ると、";
	mes "何も考えてはいないのかもな？";
	mes "君も気になるなら挑戦して";
	mes "タワーの秘密を解いてみなさい。";
	next;
	setquest 7412;
	if(checkquest(7411) && checkquest(7412) && checkquest(7413)) {
		doevent "エクラージュガード#tl01::OnStart";
	}
	mes "[リトリップ]";
	mes "そしてもし、君がビフロストタワーの";
	mes "秘密を解くことができたら、";
	mes "私に教えてくれ。";
	mes "君は十分に強いからタワーを";
	mes "探検できるだろ。";
	mes "私には1階が限界だったよ、ははは。";
	next;
	mes "[リトリップ]";
	mes "そうだ、他の友達とも話してみたか？";
	mes "ポメちゃんとチーバー君も";
	mes "それなりの情報を";
	mes "持っているはずだから";
	mes "聞いて見なさい。";
	mes "やはり旅人に重要なのは情報だぞ！";
	next;
	mes "‐他の旅人とも話をしてみよう‐";
	close;
}

ecl_in01.gat,35,51,3	script	旅人チーバー#tl03	514,{
	if(ECL_3QUE == 1) {
		mes "[チーバー]";
		mes "今、エクラージュガードが";
		mes "君を探していただろ？";
		mes "問題を起こしたくなければ、";
		mes "最大限ラフィネたちを";
		mes "尊重するのがいいだろう。";
		mes "それも旅の基本だから。";
		close;
	}
	if(ECL_3QUE == 2) {
		mes "[チーバー]";
		mes "エクラージュガードと";
		mes "何処かに行ったんじゃなかったっけ？";
		mes "途中で道に迷ったのであれば";
		mes "東側の出入り口にいるガードと";
		mes "話してみなよ。";
		mes "案内してくれるはずだ。";
		close;
	}
	if(ECL_3QUE >= 8) {
		mes "[チーバー]";
		mes "むう……霧の森に挑戦してみようかな？";
		mes "無理かな？　無理だろうな……";
		mes "ふむ、じゃあリトリップさんと";
		mes "タワーでも行って来ることにしよう。";
		close;
	}
	if(ECL_3QUE >= 3) {
		mes "[チーバー]";
		mes "君は普通の旅人では";
		mes "なかったみたいだな！";
		close;
	}
	if(checkquest(7411) && checkquest(7412) && checkquest(7413)) {
		doevent "エクラージュガード#tl01::OnStart";
	}
	if(checkquest(7413)) {
		mes "[チーバー]";
		mes "ラフィネの王位継承について";
		mes "何か巨大な儀式が必要なのは";
		mes "知っているけど……";
		mes "具体的にどのような儀式なのかは";
		mes "私も良く知らないんだ。";
		next;
		mes "[チーバー]";
		mes "もっと早く来ていれば王位継承という";
		mes "歴史的な瞬間に立ち会えたかも";
		mes "知れないけど、";
		mes "私は一足遅かったんだ……。";
		next;
		mes "[チーバー]";
		mes "マヨル・ジュンの寿命は";
		mes "かなり長いから、";
		mes "もう接する機会はないだろうな。";
		mes "ははは……";
		next;
		mes "‐他の旅人とも話をしてみよう‐";
		close;
	}
	mes "[チーバー]";
	mes "ミッドガルドの人間だね。";
	mes "チーバーです。";
	mes "見ての通り私もあなたと同じ";
	mes "旅人なんだ。";
	next;
	mes "[チーバー]";
	mes "旅をする際に一番重要なのは、";
	mes "やはり現地の情報だと考えている。";
	mes "あなたもそう思うだろう？";
	next;
	if(NYD_1QUE >= 131) {
		mes "[チーバー]";
		mes "聞いた話ではヨトゥンヘイムへの道を";
		mes "妨げている亀裂やらという物を避けて";
		mes "通る道ができたらしいけど……";
		mes "本当にあの霧の森を通っているのかな？";
		next;
		switch(select("そうです","魔法で来ました")) {
		case 1:
			mes "[チーバー]";
			mes "なるほど、ミッドガルドの";
			mes "人間は強いんだな。";
			mes "モーラで聞いた話では";
			mes "霧の森はモンスターが強く";
			mes "失踪者が多いと聞いたが……";
			break;
		case 2:
			mes "[チーバー]";
			mes "なるほど……";
			mes "先にモーラに到着した";
			mes "ミッドガルドの人たちが";
			mes "魔法で支援するということか？";
			mes "いい方法だ。";
			break;
		}
		next;
		mes "[チーバー]";
		mes "教えてくれてありがとう。";
		mes "お礼に興味深い話を";
		mes "教えてあげよう。";
		mes "アールブヘイムでは";
		mes "誰でも知っているけど、";
		mes "君たちは知らないはずだ。";
	}
	else {
		mes "[チーバー]";
		mes "サファ族とラフィネ族の戦争については";
		mes "あなたも知っているね？";
		next;
		mes "[チーバー]";
		mes "サファ族の行うブラディウム採掘が、";
		mes "ラフィネ族の守護するイグドラシルを";
		mes "衰えさせているという理由で、";
		mes "ラフィネ族から仕掛けられた戦争だ。";
		next;
		mes "[チーバー]";
		mes "しかし……私は信じられない話を";
		mes "聞いたんだ。";
		next;
		mes "‐チーバーは、声をひそめて続けた‐";
		next;
		mes "[チーバー]";
		mes "実は、サファ族の採掘がイグドラシルを";
		mes "衰えさせているというのは、";
		mes "ラフィネ族の勘違いだった……。";
		mes "サファ族とラフィネ族の戦争は、";
		mes "ラフィネ族の勘違いで";
		mes "始まったらしいんだ。";
		emotion 0,"";
		next;
		mes "[チーバー]";
		mes "その反応をみると……";
		mes "何もご存じないようだね。";
		mes "真実を探り当てたのがミッドガルドの";
		mes "人間だと聞いていたので、";
		mes "何か知っているのでは、";
		mes "と思ったのだが……。";
		next;
		mes "[チーバー]";
		mes "まあ、いい。";
		mes "私の聞いた内容をお話ししよう。";
		next;
		mes "[チーバー]";
		mes "イグドラシルにはニーズヘッグという";
		mes "守護者がいるのだが、";
		mes "どうもそのニーズヘッグに異変が";
		mes "あったらしいんだ。";
		next;
		mes "[チーバー]";
		mes "イグドラシルの衰えは、";
		mes "サファ族の採掘が原因ではなく、";
		mes "守護者ニーズヘッグの異変が";
		mes "原因だった……。";
		next;
		mes "[チーバー]";
		mes "それをミッドガルドの人間が突き止め、";
		mes "サファ族とラフィネ族のそれなりの";
		mes "地位の者に伝えたらしいのだが……";
		mes "今のところ、戦争が終結する様子は";
		mes "ないんだよな……。";
		next;
		mes "[チーバー]";
		mes "引くに引けなくなっているのか、";
		mes "あるいは真実を聞いた者が";
		mes "その重大さに圧倒されて、真実を";
		mes "握りつぶす選択をしてしまったのか、";
		mes "それはわからない。";
		next;
		menu "今の話は本当ですか？",-;
		mes "[チーバー]";
		mes "私があなたにお伝えしたのは、";
		mes "「情報」だ。";
		mes "その「情報」を信じるか信じないか、";
		mes "今後の行動に活かすべきか";
		mes "それとも影響されないべきか、";
		mes "それを決めるのはあなた自身だ。";
		next;
		mes "[チーバー]";
		mes "もし今のあなたに、それを決める";
		mes "材料がないというのなら、";
		mes "その材料を集めるというのも、";
		mes "情報の有効な使い方だと思うぞ。";
		next;
		mes "[チーバー]";
		mes "かくいう私も、エクラージュであれば";
		mes "もっと確かな情報が得られるのでは";
		mes "ないかと思って、訪れたのだが、";
		mes "今のところは収穫なしだよ。";
		mes "ははは……";
		next;
		mes "[チーバー]";
		mes "そうだ。";
		mes "あなたはここに来たばかりだろう？";
		mes "ラフィネ族について、";
		mes "もっと基本的な情報を";
		mes "お教えしよう。";
		next;
		mes "[チーバー]";
		mes "アールブヘイムでは";
		mes "誰でも知っているけど、";
		mes "君たちは知らないはずだ。";
	}
	next;
	mes "[チーバー]";
	mes "ラフィネたちの中で、特に背が大きく、";
	mes "明るい皮膚の色をしていて、";
	mes "大きく派手な羽を持っている";
	mes "ラフィネたちをみたことがあるだろ？";
	next;
	mes "[チーバー]";
	mes "彼らは^0000FF「ドナ」^000000というんだ。";
	mes "一般的な小さな体のラフィネは";
	mes "彼らの言葉で^0000FF「パパン」^000000という。";
	mes "……何か変な名称だけど";
	mes "尊重してやろうじゃないか。";
	next;
	mes "[チーバー]";
	mes "ドナたちは大きく華麗な上に、";
	mes "大抵、魔力が強くて寿命も長い。";
	mes "そのため、個体数は少ないが、";
	mes "ほとんどが要職で働いている。";
	next;
	mes "[チーバー]";
	mes "さらに、ドナたちには";
	mes "大きな役割がある。";
	mes "それは、エクラージュにとって";
	mes "もっとも重要なこと……";
	mes "彼らはすべて、マヨルの候補、";
	mes "即ち王の候補なんだ。";
	next;
	mes "[チーバー]";
	mes "普通、王といえば、親から子へ";
	mes "継承されるものだが、";
	mes "ラフィネの王は違う。";
	mes "マヨル・ジュンは^0000FFドナの中から、";
	mes "血統にかかわらず現れる。^000000";
	next;
	mes "[チーバー]";
	mes "先代の王が後任に";
	mes "王位を譲る形式ではない。";
	mes "興味深い話だろ？";
	next;
	mes "[チーバー]";
	mes "単純にドナが上級で、パパンが下級と";
	mes "いうだけの分類ではない。";
	mes "任された役割で、はっきりと";
	mes "区別されているんだ。";
	next;
	mes "[チーバー]";
	mes "ただ、ラフィネの王位継承について";
	mes "何か巨大な儀式が必要なのは";
	mes "知っているが……";
	mes "具体的にどのような儀式なのかは";
	mes "私も良く知らないんだ。";
	next;
	mes "[チーバー]";
	mes "もっと早く来ていれば、ラフィネの";
	mes "王位継承という歴史的な瞬間に";
	mes "立ち会えたかも知れないが、";
	mes "私は一足遅かったんだ……。";
	next;
	mes "[チーバー]";
	mes "マヨル・ジュンの寿命は";
	mes "かなり長いから、";
	mes "もう接する機会はないだろうな。";
	mes "ははは……";
	next;
	setquest 7413;
	if(checkquest(7411) && checkquest(7412) && checkquest(7413)) {
		doevent "エクラージュガード#tl01::OnStart";
	}
	mes "‐チーバーから";
	mes "　ラフィネに関する情報を得た。";
	mes "　他の旅人とも話をしてみよう‐";
	close;
}

ecl_in01.gat,31,49,7	script	エクラージュガード#tl01	447,{
	mes "[エクラージュガード]";
	mes "あ、急いで元の場所に戻らないと";
	mes "失礼します。";
	close2;
	hideonnpc "エクラージュガード#tl01";
	end;
OnStart:
	hideoffnpc "エクラージュガード#tl01";
	cutin "minuel01",4;
	mes "[エクラージュガード]";
	mes "ちょっと、失礼します。";
	mes "みなさんの中にミッドガルドから";
	mes "来た方はいませんか？";
	next;
	menu "私ですが？",-;
	mes "[エクラージュガード]";
	mes "おお、あなたですか！";
	mes "あなたにお会いしたいという方が";
	mes "おりますので、少しお時間を";
	mes "いただけませんか？";
	next;
	mes "[エクラージュガード]";
	mes "怪しい方ではありませんし、";
	mes "危害を加えることもありません。";
	mes "お話を聞きたいだけですので";
	mes "宜しくお願いします。";
	next;
	mes "[エクラージュガード]";
	mes "よろしければ";
	mes "私がご案内いたしますよ。";
	next;
	if(select("分かりました","今はそんな余裕がない") == 2) {
		mes "[エクラージュガード]";
		mes "あ、そうですか？";
		mes "仕方ないですね。";
		mes "いつでも構いませんので";
		mes "時間がある時に";
		mes "私を訪ねて来てください。";
		next;
		mes "[エクラージュガード]";
		mes "広場の東側にある出入り口にいます。";
		mes "必ず訪ねて来てください。";
		mes "お願いします。";
		next;
		mes "‐自分に会いたいと言っている";
		mes "　人物がいるらしい。";
		mes "　エクラージュガードが案内を";
		mes "　してくれるらしいので、";
		mes "　エクラージュガードのところに";
		mes "　行ってみよう‐";
		set ECL_3QUE,1;
		delquest 7411;
		delquest 7412;
		delquest 7413;
		setquest 7414;
		close2;
		hideonnpc "エクラージュガード#tl01";
		cutin "minuel01",255;
		end;
	}
	mes "[エクラージュガード]";
	mes "では、行きましょう。";
	close;
	set ECL_3QUE,2;
	delquest 7411;
	delquest 7412;
	delquest 7413;
	setquest 7415;
	hideonnpc "エクラージュガード#tl01";
	warp "ecl_in03.gat",244,89;
	end;
OnInit:
	hideonnpc "エクラージュガード#tl01";
	end;
}

ecl_in01.gat,82,70,3	script	エクラージュガード#tl02	447,{
	switch(ECL_3QUE) {
	case 0:
		cutin "minuel01",2;
		mes "[エクラージュガード]";
		mes "ようこそ、エクラージュへ。";
		mes "観光を楽しんでください。";
		close2;
		cutin "minuel01",255;
		end;
	case 1:
		cutin "minuel01",2;
		mes "[エクラージュガード]";
		mes "あ、来ましたね。";
		mes "あなたにお会いしたいという方の所に";
		mes "案内してもいいですか？";
		next;
		if(select("行きましょう","今はそんな余裕がない")) {
			mes "[エクラージュガード]";
			mes "そ……そうですか？";
			mes "では、もう少しお待ちします。";
			next;
			cutin "minuel02",2;
			mes "[エクラージュガード]";
			mes "私のことは気にしないでください。";
			mes "千年でも一万年でもここで";
			mes "お待ちしておりますので。";
			mes "それが仕事なのです。";
			close2;
			cutin "minuel01",255;
			end;
		}
		mes "[エクラージュガード]";
		mes "では、行きましょう。";
		close2;
		set ECL_3QUE,2;
		chgquest 7414,7415;
		warp "ecl_in03.gat",244,89;
		end;
	case 2:
		cutin "minuel01",2;
		mes "[エクラージュガード]";
		mes "まだ用事が終わっていませんよね？";
		mes "もう一度ご案内しましょうか？";
		next;
		if(select("お願いします","必要ありません") == 2) {
			mes "[エクラージュガード]";
			mes "そうですか？";
			mes "分かりました、必要であれば";
			mes "いつでも訪ねて来てください。";
			close2;
			cutin "minuel02",255;
			end;
		}
		mes "[エクラージュガード]";
		mes "では、行きましょう。";
		close2;
		warp "ecl_in03.gat",244,89;
		end;
	case 3:
		cutin "minuel01",2;
		mes "[エクラージュガード]";
		mes "良くお会いしますね。";
		mes "軍参謀がお会いするための";
		mes "申請をしておいたのは、";
		mes "すでに通知を受けて知っています。";
		next;
		mes "[エクラージュガード]";
		mes "もうご案内しても";
		mes "大丈夫な時間のようです。";
		mes "今すぐご案内しましょうか？";
		next;
		if(select("お願いします","また来ます") == 2) {
			mes "[エクラージュガード]";
			mes "お好きなようにしてください。";
			mes "でも、あまりにも待たせると";
			mes "マヨル・ジュンが";
			mes "怒るかもしれませんが……";
			close2;
			cutin "minuel02",255;
			end;
		}
		mes "[エクラージュガード]";
		mes "では、ご案内します。";
		set ECL_3QUE,4;
		chgquest 7416,72280;
		close2;
		warp "ecl_in03.gat",54,83;
		end;
	case 4:
		cutin "minuel01",2;
		mes "[エクラージュガード]";
		mes "ミーティングルームに";
		mes "ご案内しましょうか？";
		next;
		if(select("お願いします","大丈夫です") == 2) {
			mes "[エクラージュガード]";
			mes "ありがとうございます。";
			mes "あまりにも頻繁にいらっしゃるので、";
			mes "私のことを空間転送担当と";
			mes "間違っているのかと思いました。";
			close2;
			cutin "minuel02",255;
			end;
		}
		mes "[エクラージュガード]";
		mes "では、ご案内します。";
		close2;
		warp "ecl_in03.gat",54,83;
		end;
	case 5:
		if(ECL_3QUE_sub & 0x2) {
			cutin "minuel01",2;
			mes "[ミニュエル]";
			mes "ヤイをモンスター素材で飾ったら、";
			mes "周辺の反応が凄かったんです！";
			mes "もしかしたら、これが流行を";
			mes "巻き起こすかもしれません。";
			close2;
			cutin "minuel01",255;
			end;
		}
		if(checkquest(7418)) {
			if(countitem(6032) < 5 || countitem(6023) < 5 || countitem(944) < 5) {
				cutin "minuel01",2;
				mes "[ミニュエル]";
				mes "ヒルスリオンの角、魔力の角、";
				mes "馬のひづめを各5個ずつお願いします。";
				mes "魔力の角はスプレンディッドの";
				mes "近辺にいるコルヌスから";
				mes "入手することができます。";
				next;
				mes "‐ヒルスリオンの角、魔力の角、";
				mes "　馬のひづめを各5個ずつ集め、";
				mes "　ミニュエルに届けよう‐";
				close2;
				cutin "minuel01",255;
				end;
			}
			cutin "minuel01",2;
			mes "[ミニュエル]";
			mes "もうお戻りになりましたか？";
			mes "品物を確認いたします。";
			mes "えーと……";
			next;
			mes "[ミニュエル]";
			mes "ある程度キズがあるのは";
			mes "その分、野性味が出ますね。";
			mes "素晴らしいです、ご苦労様でした。";
			cutin "minuel02",2;
			next;
			delitem 6032,5;
			delitem 6023,5;
			delitem 944,5;
			set ECL_3QUE_sub,ECL_3QUE_sub|2;
			delquest 7418;
			getexp 200000,0;
			getexp 0,200000;
			if(ECL_3QUE_sub & 0x7 == 0x7) {
				mes "[ミニュエル]";
				mes "そういえば、私以外の";
				mes "ラフィネたちから頼まれた仕事も、";
				mes "見事にこなしたそうですね。";
				mes "私ももう大丈夫なので、";
				mes "マヨル・ジュンの所に";
				mes "行ってください。";
				cutin "minuel01",2;
				next;
				mes "[ミニュエル]";
				mes "良いタイミングであの方の意思を";
				mes "伝えるのが私の仕事。";
				mes "私はそれが今だと考えております。";
				set ECL_3QUE,6;
				set ECL_3QUE_sub,0;
				chgquest 7417,7421;
				next;
				mes "[ミニュエル]";
				mes "それにしても、あまりにも頻繁に";
				mes "お会いしたので、情が移った";
				mes "というか何というか……";
				mes "まあ、それだけのことですが。";
				close2;
				cutin "minuel01",255;
				end;
			}
			mes "[ミニュエル]";
			mes "そのうち良い知らせがあると思います。";
			mes "期待していてもいいですよ。";
			close2;
			cutin "minuel01",255;
			end;
		}
		cutin "minuel01",2;
		mes "[エクラージュガード]";
		mes "あ、またお会いしましたね。";
		mes "このように頻繁にお会いすると";
		mes "わかっていたら、";
		mes "始めからきちんと挨拶を";
		mes "して置けばよかったです。";
		next;
		mes "[ミニュエル]";
		mes "私はミニュエルと言います。";
		mes "よくある名前です。";
		mes "何の意味があるのかはわかりません。";
		mes "たぶん、両親が呼びやすい名前を";
		mes "つけたんだと思います。";
		next;
		mes "[ミニュエル]";
		mes "そういえば、噂を聞きました。";
		mes "エクラージュで働くようになったと……";
		cutin "minuel02",2;
		next;
		if(select("デタラメだ","頼みたいことはある？") == 1) {
			mes "[ミニュエル]";
			mes "え？　そうなんですか？";
			mes "あなたにピッタリの仕事が";
			mes "あったのに残念ですね。";
			mes "わ、分かりました。";
			close2;
			cutin "minuel01",255;
			end;
		}
		mes "[ミニュエル]";
		mes "実を言うと私は常にここにいるので";
		mes "個人的な時間が少し不足しています。";
		mes "私だけではなく、この関連の仕事を";
		mes "しているラフィネたちはみんな";
		mes "そうだと思いますけど……。";
		cutin "minuel01",2;
		next;
		mes "[ミニュエル]";
		mes "なので、ヤイを飾るための材料を";
		mes "集める時間がないのです。";
		mes "こだわりぬいたデコレーションを";
		mes "施したいと思っているのに……";
		next;
		mes "[ミニュエル]";
		mes "そこで、お礼を差し上げますので";
		mes "ヤイをデコレーションする";
		mes "材料を集めてくれませんか？";
		next;
		if(select("わかった","いやだ") == 2) {
			mes "[ミニュエル]";
			mes "うう、断るんですか？";
			mes "でもきっと、あなたはいつか";
			mes "私を助けに来てくれるはずです。";
			mes "それまでお待ちしています。";
			cutin "minuel02",2;
			close2;
			cutin "minuel02",255;
			end;
		}
		mes "[ミニュエル]";
		mes "ありがとうございます。";
		mes "必要な材料は、";
		mes "^0000ffヒルスリオンの角、魔力の角、";
		mes "馬のひづめを各5個ずつ^000000です。";
		next;
		mes "[ミニュエル]";
		mes "材料は私が行くことのできない";
		mes "スプレンディッドの近くにいる";
		mes "モンスターを狩ることで";
		mes "入手できる物の中から決めました。";
		next;
		mes "[ミニュエル]";
		mes "この材料を使ってヤイを、";
		mes "野性味の中にも美しさが";
		mes "溢れるように飾ってみたいです。";
		next;
		mes "[ミニュエル]";
		mes "ヒルスリオンは噂で聞いたんですが、";
		mes "ビフロスト北部や";
		mes "サファの領域で見かけることが";
		mes "できるそうです。";
		mes "その角と、草原のコルヌスの魔力の角。";
		mes "そして馬のひづめという物。";
		next;
		mes "[ミニュエル]";
		mes "馬のひづめに関しては";
		mes "私よりあなたが詳しいと思います。";
		mes "では、宜しくお願いします。";
		next;
		mes "‐ヒルスリオンの角、魔力の角、";
		mes "　馬のひづめを各5個ずつ集め、";
		mes "　ミニュエルに届けよう‐";
		setquest 7418;
		close2;
		cutin "minuel02",255;
		end;
	case 6:
		cutin "minuel01",2;
		mes "[ミニュエル]";
		mes "マヨル・ジュンがお呼びです。";
		mes "今はそこまで案内してあげられる";
		mes "余裕がないので、今回は口頭で";
		mes "ご説明いたします。";
		next;
		mes "[ミニュエル]";
		mes "この出口から出て行って散策道を";
		mes "進んで2階上にあがると";
		mes "ミーティングルームの入口です。";
		mes "そちらに行ってみてください。";
		close2;
		cutin "minuel01",255;
		end;
	case 7:
		cutin "minuel01",2;
		mes "[ミニュエル]";
		mes "またお会いしましたね。";
		mes "参謀ですか？";
		next;
		mes "[ミニュエル]";
		mes "まず、散策道を通じて上の階に";
		mes "行きます。";
		mes "王室内部の右手に会議場が";
		mes "ありますので、";
		mes "そこにいらっしゃいます。";
		close2;
		cutin "minuel01",255;
		end;
	case 16:
	case 17:
		cutin "minuel01",2;
		mes "[ミニュエル]";
		mes "今日も王宮に寄って来たんですか？";
		next;
		menu "シナイムが支援している魔学者について聞く",-;
		mes "[ミニュエル]";
		mes "軍参謀が魔学者を";
		mes "支援していたのですか？";
		mes "まったく知りませんでした……";
		mes "……いや、そういえば……";
		mes "あ……それで……";
		next;
		menu "心当たりを聞く",-;
		mes "[ミニュエル]";
		mes "帰宅の際に、";
		mes "東の方向によく行かれていました。";
		mes "軍参謀のヤイは反対方向なのに。";
		next;
		mes "[ミニュエル]";
		mes "それで、誰かと会っているのかなと";
		mes "思っていました。";
		mes "今の話を聞いた上で考えると、";
		mes "それがたぶん、支援しているという";
		mes "魔学者では？";
		next;
		mes "[ミニュエル]";
		mes "もちろん、推測ですが……";
		mes "ま、このようなことでも";
		mes "力になれるのであれば";
		mes "嬉しいです。";
		next;
		mes "‐軍参謀シナイムは、";
		mes "　自身のヤイがあるのとは反対方向の";
		mes "　東の方角に、よく行っているらしい。";
		mes "　一度ヒシエに報告をしよう‐";
		cutin "minuel02",2;
		set ECL_3QUE,18;
		chgquest 7439,7440;
		close2;
		cutin "minuel02",255;
		end;
	default:
		if(checkquest(7428)) {
			cutin "minuel01",2;
			mes "[ミニュエル]";
			mes "用意して来てほしいのは";
			mes "ヒルスリオンの角、魔力の角、";
			mes "馬のひづめを各10個ずつ";
			mes "お願いします。";
			next;
			mes "‐ヒルスリオンの角、魔力の角、";
			mes "　馬のひづめを各10個ずつ集め、";
			mes "　ミニュエルに届けよう‐";
			close2;
			cutin "minuel02",255;
			end;
		}
		cutin "minuel01",2;
		mes "[ミニュエル]";
		mes "少しお時間ありますか？";
		mes "この前入手していただいた";
		mes "モンスターの材料が友達の間で";
		mes "流行ってしまいまして……";
		mes "もう少し手に入れてほしいんですが、";
		mes "お願いできますか？";
		next;
		if(select("引き受ける","断る") == 2) {
			mes "[ミニュエル]";
			mes "残念ですね……";
			mes "また今度お願いします。";
			close2;
			cutin "minuel02",255;
			end;
		}
		mes "[ミニュエル]";
		mes "ありがとうございます。";
		mes "この前用意してくれた";
		mes "ヒルスリオンの角、魔力の角、";
		mes "馬のひづめを各10個ずつ";
		mes "お願いします。";
		next;
		mes "[ミニュエル]";
		mes "友達の間でもワイルドな飾りが";
		mes "流行ってしまいました。";
		mes "ははは……";
		mes "では、私はここでお待ちします。";
		next;
		mes "‐ヒルスリオンの角、魔力の角、";
		mes "　馬のひづめを各10個ずつ集め、";
		mes "　ミニュエルに届けよう‐";
		setquest 7428;
		close2;
		cutin "minuel02",255;
		end;
	}
}

ecl_in03.gat,245,93,5	script	軍参謀	435,{
	switch(ECL_3QUE) {
	case 2:
		mes "[軍参謀]";
		mes "エクラージュにようこそ。";
		mes "歓迎します。";
		mes "私があなたをお呼びしました。";
		next;
		mes "[シナイム]";
		mes "スプレンディッド前線基地に送られる";
		mes "すべての軍需品を担当しています。";
		mes "シナイムと申します。";
		next;
		mes "[シナイム]";
		mes "モーラに送った私たちの補給品を……";
		mes "うむ……つぅ……";
		mes "すみません。";
		mes "最近、頭痛が頻繁に起きていて……";
		next;
		mes "[シナイム]";
		mes "続けましょう。";
		mes "モーラから補給品を霧の森を通過して";
		mes "スプレンディッドまで代わりに";
		mes "配達してくれている者たちがいると";
		mes "聞きました。";
		next;
		if(BIF_1QUE >= 181) {	// ビフロストクエスト達成済み? 未確認
			mes "[シナイム]";
			mes "このように直接お会いできて";
			mes "嬉しいです。";
			mes "あなた以外にも、配達を手伝ってくれた";
			mes "方々が一足先にエクラージュに";
			mes "いらしていて、同じようにお招き";
			mes "しました。";
		}
		else {
			mes "[シナイム]";
			mes "それはミッドガルドから来た";
			mes "人間たちとのこと。";
			mes "それで、エクラージュを訪れた";
			mes "ミッドガルドの方たちを、";
			mes "このようにお招きして";
			mes "お話を伺っております。";
		}
		next;
		mes "[シナイム]";
		mes "……う、うむむ……";
		next;
		mes "[シナイム]";
		mes "……あ、今私が変な表情をしたのは";
		mes "頭痛のせいです。";
		mes "誤解しないでください。";
		mes "と、とにかく話を続けます……";
		next;
		mes "[シナイム]";
		mes "そろそろ本題に入ります。";
		mes "私があなたに会いたかった理由です。";
		next;
		mes "[シナイム]";
		mes "すでにご存じのとおり、";
		mes "ビフロストに発生した";
		mes "巨大な亀裂のせいで、";
		mes "スプレンディッドとの交流が";
		mes "途絶えています。";
		next;
		if(NYD_1QUE >= 131) {
			mes "[シナイム]";
			mes "スプレンディッドは、";
			mes "イグドラシルを守るため、";
			mes "我々がヨトゥンヘイムに作った";
			mes "前線基地です。";
			mes "サファ族に対抗するために非常に";
			mes "重要な場所です。";
			next;
			mes "[シナイム]";
			mes "しかし、ビフロストに発生した";
			mes "亀裂により、スプレンディッドの";
			mes "状況を確認することができなくなって";
			mes "しまったのです。";
			next;
			mes "[シナイム]";
			mes "そこで、ミッドガルドの";
			mes "旅人をお呼びして、";
			mes "最近のスプレンディッドと";
			mes "ヨトゥンヘイムの状況について";
			mes "お話を聞いております。";
			next;
			mes "[シナイム]";
			mes "何かスプレンディッド近辺での";
			mes "サファ族との対立について、";
			mes "見聞きしたこと、知っていることは";
			mes "ありませんか？";
			next;
			mes "‐ニーズヘッグの巣での";
			mes "　出来事を思い出していた。";
			mes "　イグドラシルの衰えは、";
			mes "　サファ族の採掘が原因ではなく、";
			mes "　守護者ニーズヘッグの異変が";
			mes "　原因だった‐";
			next;
			mes "‐軍参謀シナイムに、そのことは";
			mes "　伝わっているのだろうか。";
			mes "　確認してみるのが良さそうだ‐";
		}
		else {
			mes "[シナイム]";
			mes "ラフィネは霧の森とビフロストの";
			mes "意思には逆らえません。";
			mes "これはアールブヘイムのすべての妖精に";
			mes "共通する話です。";
			mes "そのため、我々ではスプレンディッドの";
			mes "状況を確認することができず……。";
			next;
			mes "[シナイム]";
			mes "そこで、あなた方ミッドガルドの";
			mes "旅人から、最近のスプレンディッドと";
			mes "ヨトゥンヘイムの状況について";
			mes "お話を聞いております。";
			next;
			mes "[シナイム]";
			mes "聞いた話だと、現在はサファ族との";
			mes "対立状況は、休戦に近い";
			mes "小康状態らいしいですが……";
			mes "これは我々の物資の支給が難しいために";
			mes "そのようになったのでしょうか？";
			next;
			mes "‐シナイムの質問に対し、";
			mes "　記憶している限りの";
			mes "　今現在の状態を説明した‐";
			next;
			mes "[シナイム]";
			mes "なるほど……";
			next;
			mes "‐ラフィネ族とサファ族との";
			mes "　対立について、旅人チーバーから";
			mes "　聞いた話を思い出した。";
			mes "　軍参謀シナイムは、その内容を";
			mes "　知っているのだろうか。";
			mes "　確認してみるのが良さそうだ‐";
		}
		next;
		menu "そういえば……",-;
		mes "[シナイム]";
		mes "はい。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "あなたたちとサファ族との戦争の原因は";
		mes "サファ族がイグドラシルを衰えさせた";
		mes "ことが引き金となって起きた";
		mes "イグドラシル守護戦争だと";
		mes "言われています。";
		next;
		mes "[シナイム]";
		mes "その通りです。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "しかし、私が知っている真実は";
		mes "それとはちょっと違います。";
		next;
		mes "‐シナイムの表情がわずかに";
		mes "　歪んだ。";
		mes "　それは頭痛によるものでは";
		mes "　なさそうだ‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "表面的な原因は確かにサファ族の";
		mes "採掘によるイグドラシルの";
		mes "損傷ですが……";
		next;
		mes "[シナイム]";
		mes "お待ちください。";
		next;
		mes "‐シナイムに、強い調子で";
		mes "　言葉を遮られた‐";
		next;
		menu "どうしました？",-;
		mes "[シナイム]";
		mes "この戦争は聖戦です。";
		mes "イグドラシルを守るという";
		mes "我々の使命をかけた聖戦……";
		mes "私たちが私たちのプライドを";
		mes "かけて行っている戦争なのです。";
		next;
		mes "[シナイム]";
		mes "あなたが言おうとしていること、";
		mes "それによって引き起こる波紋。";
		mes "あなたはその責任を取ることが";
		mes "できますか？";
		next;
		mes "[シナイム]";
		mes "もし責任を取ることができないなら";
		mes "何も話さないでください。";
		next;
		menu "真実を隠しているのですか？",-;
		mes "[シナイム]";
		mes "…………。";
		next;
		mes "‐シナイムは眉間にしわを寄せ、";
		mes "　深く考え込んでいる‐";
		next;
		menu "シナイムさん？",-;
		mes "[シナイム]";
		mes "……あなたの言わんとしていること、";
		mes "それは世界樹イグドラシルと";
		mes "守護者の問題です。";
		next;
		mes "[シナイム]";
		mes "私が言えるのはここまでです。";
		mes "あなたが持っている疑問には、";
		mes "私はお答えする事ができません。";
		next;
		mes "[シナイム]";
		mes "あなたの話を聞くのは私ではなく";
		mes "我々の王マヨル・ジュンでなくては";
		mes "なりません。";
		next;
		mes "[シナイム]";
		mes "マヨル・ジュンにお会いできる場を";
		mes "用意しましょう。";
		next;
		mes "‐シナイムは会話の途中に";
		mes "　再度頭痛が始まったようで";
		mes "　顔をしかめた。";
		mes "　頭痛が収まったようで表情が";
		mes "　元に戻った後、話を続けた‐";
		next;
		mes "[シナイム]";
		mes "もちろんあなたが信じている";
		mes "その真実は、話せる時間が来るまで";
		mes "誰にも話さないと約束してください。";
		next;
		if(select("約束する","断る") == 2) {
			while(1) {
				mes "[シナイム]";
				mes "困りましたね。";
				mes "あなたが火種になることを";
				mes "望んでいません。";
				next;
				mes "[シナイム]";
				mes "マヨル・ジュンと話し合う前に";
				mes "言わないというのがそれほど";
				mes "難しいですか？";
				next;
				if(select("言わない様にする","難しい") == 1) {
					mes "[シナイム]";
					mes "そうですか。";
					next;
					break;
				}
				mes "[シナイム]";
				mes "むう……";
				mes "それではあなた自身の立場が";
				mes "悪くなるだけですよ……";
				next;
			}
		}
		mes "[シナイム]";
		mes "あなたのことを";
		mes "マヨル・ジュンに伝え、";
		mes "会う場所を用意しておきます。";
		next;
		mes "[シナイム]";
		mes "あなたをここまで案内したガードに";
		mes "伝えておきます。";
		mes "彼にあなたを案内させましょう。";
		next;
		mes "[シナイム]";
		mes "では、エクラージュを";
		mes "楽しんでください。";
		mes "広場まで送って差しあげます。";
		mes "そうだ、あなたを案内するガードは";
		mes "広場の東の出口にいます。";
		mes "忘れないでください。";
		next;
		mes "‐シナイムはラフィネ族の王";
		mes "　マヨル・ジュンと話せるよう";
		mes "　手配してくれるらしい。";
		mes "　エクラージュ広場の東側出口にいる";
		mes "　エクラージュガードに案内して";
		mes "　もらおう‐";
		set ECL_3QUE,3;
		chgquest 7415,7416;
		close2;
		warp "ecl_in01.gat",47,28;
		end;
	case 3:
		mes "[シナイム]";
		mes "案内はガードに任せています。";
		mes "すみませんが、今の私は";
		mes "席を外すことができません。";
		next;
		mes "[シナイム]";
		mes "エクラージュ広場の東側の出入口に";
		mes "ガードがいます。";
		mes "彼に話をしておきましたので";
		mes "案内してもらってください。";
		close;
	case 4:
		mes "[シナイム]";
		mes "あなたの考えをマヨル・ジュンに";
		mes "伝えることはできましたか？";
		mes "決定はあの方がするでしょう。";
		next;
		mes "[シナイム]";
		mes "おや……？";
		mes "まだのようですね。";
		mes "ガードに案内をしてもらってください。";
		close;
	case 5:
		mes "[シナイム]";
		mes "あなたについての話は聞きました。";
		mes "エクラージュのために働くことに";
		mes "したようですね？";
		next;
		mes "[シナイム]";
		mes "ビフロストへの入口に";
		mes "ロイという伝令が待っているはずです。";
		next;
		mes "[シナイム]";
		mes "スプレンディッドと定期的な連絡を";
		mes "するために送った伝令なんですが、";
		mes "まだ彼では無理だったようです。";
		next;
		mes "[シナイム]";
		mes "協力してくれたら、";
		mes "多くのラフィネたちが";
		mes "あなたのことを認めると思います。";
		close;
	case 6:
		mes "‐シナイムは頭が痛そうに";
		mes "　片手でこめかみを押さえている‐";
		next;
		mes "[シナイム]";
		mes "最近になって頭痛がさらに";
		mes "酷くなりました。";
		mes "……今日は何のご用ですか？";
		mes "あなたのことをマヨル・ジュンが";
		mes "呼んでいたと思いますが。";
		mes "あの方の所に行ってみてください。";
		close;
	case 7:
		mes "[シナイム]";
		mes "ようこそ。";
		mes "マヨル・ジュンに認められた";
		mes "異邦人よ。";
		next;
		menu "何か受け取って行くようにと言われたけど……",-;
		mes "[シナイム]";
		mes "はい、マヨル・ジュンから";
		mes "あなたへの贈り物を預かっています。";
		next;
		mes "[シナイム]";
		mes "そんなに大した物ではありませんが、";
		mes "誰にでも使う事が許可されている";
		mes "物ではありません。";
		mes "軽く振ると、いつでもエクラージュに";
		mes "来ることができます。";
		next;
		mes "[シナイム]";
		mes "王のために働く者、";
		mes "あなたにふさわしい物です。";
		next;
		if(checkitemblank() == 0) {
			mes "[シナイム]";
			mes "おや……";
			mes "持ち物が多すぎるようです。";
			mes "持ち物を整理してから、";
			mes "もう一度話しかけてください。";
			close;
		}
		mes "‐贈り物を受け取ったが、";
		mes "　まだカルデュイが何を考えて";
		mes "　いるのか、測りかねる部分がある。";
		mes "　すぐ近くにいる休憩中のラフィネや";
		mes "　旅人ポメ、町にいる話中のラフィネ、";
		mes "　エクラージュガード・レオから、";
		mes "　王についての情報を集めてみよう‐";
		set ECL_3QUE,8;
		chgquest 7422,72253;
		getitem 2916,1;
		close;
	case 8:
	case 9:
	case 10:
	case 11://?
	case 12://?
	case 13://?
		mes "[シナイム]";
		mes "最近、色んな仕事を";
		mes "手伝っているみたいですね？";
		mes "大変ですね。";
		close;
	case 14:
		mes "[シナイム]";
		mes "あぁ、ようやく見つけた。";
		mes "最近、ビフロストタワーに";
		mes "行っているらしいですね？";
		mes "そこで、ひとつお願いしたい";
		mes "ことがあります。";
		next;
		mes "[シナイム]";
		mes "私が支援している魔学者がいるのですが";
		mes "実験材料としていくつか足りない物が";
		mes "あるらしく。";
		mes "それをビフロストタワーで手に入れて";
		mes "ほしいんです。";
		next;
		mes "[シナイム]";
		mes "お願いしてもいいですか？";
		mes "もちろん、それなりのお礼は";
		mes "用意いたします。";
		next;
		if(select("分かりました","断ります") == 2) {
			mes "[シナイム]";
			mes "急なお願いでしたからね。";
			mes "まあ、仕方がないですね。";
			mes "他の方に頼んでみます。";
			close;
		}
		mes "[シナイム]";
		mes "急なお願いで引き受けてもらえるか";
		mes "不安だったのですが、快く引き受けて";
		mes "いただき、ありがとうございます。";
		mes "では、これから言う物を";
		mes "集めてください。";
		next;
		mes "[シナイム]";
		mes "^0000ffほこりの塊、落ち葉のしおり^000000です。";
		mes "ビフロストタワーで入手できます。";
		mes "^0000ffそれぞれ10個ずつ^000000お願いします。";
		next;
		mes "‐ビフロストタワーで、ほこりの塊、";
		mes "　落ち葉のしおりを10個ずつ集め、";
		mes "　シナイムに届けよう‐";
		set ECL_3QUE,15;
		chgquest 7436,7437;
		close;
	case 15:
		if(countitem(6560) < 10 || countitem(6561) < 10) {
			mes "[シナイム]";
			mes "^0000ffほこりの塊、落ち葉のしおりを";
			mes "各10個すつ^000000です。";
			mes "ビフロストタワーで入手できます。";
			next;
			mes "‐ビフロストタワーで、ほこりの塊、";
			mes "　落ち葉のしおりを10個ずつ集め、";
			mes "　シナイムに届けよう‐";
			close;
		}
		mes "[シナイム]";
		mes "手に入れて来ましたね！";
		mes "ありがとうございます。";
		mes "このくらいあれば当分は";
		mes "問題ないと思います。";
		next;
		menu "支援している魔学者について聞く",-;
		mes "[シナイム]";
		mes "ただ個人的に支援しているだけです。";
		mes "真理の扉に属した学者や錬金術師たちは";
		mes "研究以外をおろそかにしがちです。";
		mes "基本的な生活力など……";
		mes "私が支援している魔学者も、";
		mes "そのような方なのです。";
		next;
		menu "会ってみたいです",-;
		mes "[シナイム]";
		mes "それは困ります。";
		mes "とても警戒心が強いので、";
		mes "外部の人と接触するのを好みません。";
		next;
		mes "[シナイム]";
		mes "それに、私が彼の個人的なことを";
		mes "あなたに教える義務などはありません。";
		mes "そうでしょう？";
		mes "ですので、これ以上詮索するのは";
		mes "やめてください。";
		next;
		menu "エイヴァントについて",-;
		mes "[シナイム]";
		mes "エイヴァント？";
		mes "聞いたことがあるような……。";
		mes "魔学者なんですか？";
		mes "しかし私が知っている魔学者の中に";
		mes "そのような名前の方はいませんよ。";
		next;
		mes "‐シナイムは、支援している";
		mes "　魔学者について、何も話して";
		mes "　くれなかった。";
		mes "　もっと情報を集める必要がある‐";
		next;
		mes "‐いつも王宮周辺を見ている人物……";
		mes "　エクラージュガード・ミニュエルから";
		mes "　話しを聞いてみよう‐";
		delitem 6561,10;
		delitem 6560,10;
		set ECL_3QUE,16;
		chgquest 7437,7438;
		getexp 150000,0;
		getexp 0,150000;
		close;
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
		mes "[シナイム]";
		mes "エイヴァント……";
		mes "思い出しました。";
		mes "数十年前までは天才魔学者だったが、";
		mes "不適切な実験をして行方をくらませた";
		mes "人物ではありませんか？";
		next;
		mes "[シナイム]";
		mes "どこであの者の情報を得たかは";
		mes "知りませんが、諦めた方がいい。";
		mes "見つけるのは無理ですよ。";
		close;
	case 22:
		mes "[シナイム]";
		mes "未だに私が支援している学者が";
		mes "気になるんですか？";
		mes "残念ですが、その学者は";
		mes "急に姿を消しました。";
		next;
		mes "[シナイム]";
		mes "彼が人間であるあなたに興味を";
		mes "示していたので、二人を合わせて";
		mes "みようと考えていたのですが。";
		mes "どうして急にいなくなったのか……";
		close;
	case 23:
		mes "[シナイム]";
		mes "オーブの警戒を強化しろと";
		mes "マヨル・ジュンの指示がありました。";
		mes "理由は分かりませんが、";
		mes "あなたも注意してください。";
		mes "王のために働いている者でしょう？";
		next;
		mes "[シナイム]";
		mes "それとも、未だに私が支援している";
		mes "魔学者が気になるんですか？";
		next;
		menu "彼が行っていた研究について知っているのか",-;
		mes "[シナイム]";
		mes "知りません。";
		mes "自分を支援してくれれば";
		mes "望んでいることを叶えてくれると";
		mes "言っていました。";
		next;
		mes "[シナイム]";
		mes "これ以上お話しできることは";
		mes "ありません。";
		mes "彼が急にいなくなり私も機嫌が";
		mes "あまりよくありません。";
		close;
	case 24:
		mes "[シナイム]";
		mes "はあ……頭が痛くなってきた。";
		mes "マヨル様も何の理由か説明しないで";
		mes "オーブを守る人員を増やせと";
		mes "言っているし……";
		next;
		mes "[シナイム]";
		mes "魔学者は消えてしまったし……。";
		mes "まさか……";
		mes "これが話で聞いた食い逃げ!?";
		next;
		menu "落ち着いてください",-;
		mes "[シナイム]";
		mes "落ち着けませんよ";
		mes "はああ……私は詐欺にあったのでは";
		mes "ないかと思っています。";
		mes "自分を一定期間支援してくれたら";
		mes "私が求めている研究をしてくれると";
		mes "約束していました。";
		next;
		switch(select("どんな支援をしていたんですか？","何の研究を要請したかったんですか？")) {
		case 1:
			mes "[シナイム]";
			mes "彼の要求は単純でした。";
			mes "寝食および研究ができる場所の提供。";
			mes "私が依頼する研究についての";
			mes "材料費のすべてを提供。";
			next;
			mes "[シナイム]";
			mes "食事を提供したし、";
			mes "材料も与えたのに";
			mes "今になってどうして";
			mes "逃げたのでしょうか？";
			mes "私もびっくりしています。";
			next;
			mes "[シナイム]";
			mes "……考えてみると、このことに";
			mes "ついて、話せる相手もいなかった。";
			mes "最初は特に秘密にしたかったわけでは";
			mes "なかったのに……";
			next;
			mes "[シナイム]";
			mes "行方を探してみようとしたら、";
			mes "真理の扉の学者たちも";
			mes "知らないと言うし……";
			next;
			mes "[シナイム]";
			mes "今後、霧の森についての研究を";
			mes "任せようと思っていたのに……";
			mes "他の学者を見つけてみます。";
			break;
		case 2:
			mes "[シナイム]";
			mes "ビフロストタワーについて";
			mes "研究をしてくれと要請しました。";
			next;
			mes "[シナイム]";
			mes "私が指示したのはそれだけです、";
			mes "それ以外は知りません。";
			mes "その件が終わったら、その次は";
			mes "霧の森についてを依頼しようと";
			mes "思ってました。";
			next;
			mes "[シナイム]";
			mes "だけど、こんな自分勝手な人だとは。";
			mes "騙されましたよ、私は……！";
			next;
			mes "[シナイム]";
			mes "他に条件が良い学者を探して";
			mes "依頼することにします。";
			break;
		}
		next;
		mes "[シナイム]";
		mes "まあ、とにかくこれは、";
		mes "私の個人的な事情。";
		mes "それより王のために働く者よ。";
		mes "最近、マヨル・ジュンが";
		mes "何を考えているのか";
		mes "知っていますか？";
		next;
		mes "[シナイム]";
		mes "マヨル・ジュンはその存在自体が";
		mes "ラフィネ一族と共になくては";
		mes "なりません。";
		mes "個人的に何かをしようとするのは、";
		mes "許されることではありません。";
		next;
		menu "そんなことはない",-,"何が気になるんですか？",-;
		mes "[シナイム]";
		mes "……オーブについて。";
		mes "オーブを守る人員を";
		mes "増やせと言われました。";
		next;
		mes "[シナイム]";
		mes "なんの説明も無しに突然です。";
		mes "あなたは理由を知っていますか？";
		next;
		switch(select("理由を話してやる","私も知らない")) {
		case 1:
			mes "‐どこまで話そう？‐";
			next;
			switch(select("全部教える","適当に話す")) {
			case 1:
				mes "[シナイム]";
				mes "何ですって？";
				mes "私が支援していた魔学者が";
				mes "あのエイヴァントだったと";
				mes "言うんですか？";
				mes "本当ですか!?";
				next;
				menu "支援していた者の名前も知らなったんですか？",-;
				mes "[シナイム]";
				mes "……そ……んなはずは……";
				mes "私には違う名前を";
				mes "名乗ってましたし……。";
				next;
				mes "[シナイム]";
				mes "……あなたの話が本当なら大変です。";
				mes "もし悪用されたら……";
				next;
				mes "[シナイム]";
				mes "しかし、私が見ていた限りでは、";
				mes "他の者と会っているようなことは";
				mes "なさそうでした。";
				next;
				mes "[シナイム]";
				mes "彼の性格からして、";
				mes "何かに使用する目的ではなく、";
				mes "単に好奇心から研究していた";
				mes "可能性が高いです。";
				mes "いや……そうであることを";
				mes "願うしかありません。";
				next;
				mes "[シナイム]";
				mes "スプレンディッドのことだけでも";
				mes "頭が痛いのに……";
				mes "問題が増えて大変です。";
				next;
				mes "[シナイム]";
				mes "……あなたは異邦人だが、";
				mes "オーブを守らなければならない";
				mes "義務があります。";
				mes "ことのすべてを知ってしまった";
				mes "のですから。";
				next;
				mes "[シナイム]";
				mes "もしもの時は……";
				mes "どうか力になってください。";
				next;
				mes "[シナイム]";
				mes "私は兵力の配置に";
				mes "もう少し気を使うようにいたします。";
				next;
				mes "‐シナイムは、支援していた魔学者が";
				mes "　エイヴァントであると知らなかった";
				mes "　ようだ。";
				mes "　カルデュイに報告に行こう‐";
				set ECL_3QUE,25;
				chgquest 7445,7446;
				close;
			case 2:
				mes "[シナイム]";
				mes "むう……";
				mes "単にマヨル・ジュンが";
				mes "オーブの警備に不安を感じたので、";
				mes "それで警戒の強化を指示した？";
				next;
				mes "[シナイム]";
				mes "……まあ、承知しました。";
				mes "指示されたのでやります。";
				mes "マヨル・ジュンが正常的な思考で";
				mes "下した命令だと信じます。";
				break;
			}
			break;
		case 2:
			mes "[シナイム]";
			mes "意外ですね。";
			mes "マヨル・ジュンが一番信頼しているのは";
			mes "あなただと思っていました。";
			next;
			mes "[シナイム]";
			mes "理由はともかく、マヨル・ジュンが";
			mes "正常的な思考で下した命令だと";
			mes "信じるしかありません。";
			break;
		}
		next;
		menu "従いたくないんですか？",-;
		mes "[シナイム]";
		mes "そんなことありません。";
		mes "ただ濁った血がマヨル・ジュンの";
		mes "判断力まで濁すのではないかと";
		mes "心配しているだけです。";
		next;
		mes "[シナイム]";
		mes "……私たちは、今のマヨル・ジュンは";
		mes "ただ通り過ぎる風のようなもので";
		mes "あってほしいと祈っています。";
		mes "強風は一度で十分ですから。";
		next;
		mes "[シナイム]";
		mes "あなたはマヨル・ジュンを";
		mes "かなり信じているようですね。";
		mes "私たちが持っている";
		mes "不安感とは違って。";
		next;
		mes "[シナイム]";
		mes "マヨル・ジュンがオーブに執着している";
		mes "理由は分かりませんが、";
		mes "あなたが訪れた後に決定したのを";
		mes "見ると、あなたも大きな影響を";
		mes "与えたのではないですか？";
		next;
		mes "[シナイム]";
		mes "これは勘の域を出ない考えですが……";
		mes "私はあなたが、私たち一族の";
		mes "未来にかかわる決定に";
		mes "関与しているのではないかと";
		mes "思っています。";
		next;
		mes "[シナイム]";
		mes "もしそうであるなら……";
		mes "我々の未来がどうなるのか。";
		mes "私たちラフィネの誇りであり、";
		mes "根源であるオーブがどうなるのか。";
		mes "どうか目をそらさず、最後まで";
		mes "見届けてください。";
		next;
		mes "‐シナイムは、支援していた魔学者が";
		mes "　何の研究をしていたか、";
		mes "　知らなかったようだ。";
		mes "　カルデュイに報告に行こう‐";
		set ECL_3QUE,25;
		chgquest 7445,7447;
		close;
	case 25:
		mes "[シナイム]";
		mes "ここまで知ってしまったからには、";
		mes "あなたには今回の件に対して";
		mes "最後まで付き合う責任があります。";
		next;
		mes "[シナイム]";
		mes "あなたも自分が信じるマヨル・ジュンが";
		mes "正しい判断を下したのか、";
		mes "最後まで見届けたいでしょう？";
		next;
		menu "あの方は正常です",-;
		mes "[シナイム]";
		mes "正常でないとこちらも困ります。";
		mes "しかし、セネスのようにいつ";
		mes "個人的な野望を持つやもしれぬので";
		mes "警戒は必要です。";
		next;
		mes "[シナイム]";
		mes "マヨル・ジュンという存在は";
		mes "その存在だけで、敬意を払わねば";
		mes "ならないもの。";
		mes "ですので、私たちは";
		mes "あの方の判断に従いつつ、";
		mes "疑わなければなりません。";
		next;
		mes "[シナイム]";
		mes "これは万が一のためです。";
		mes "私が望んでいるのはただひとつ。";
		next;
		mes "[シナイム]";
		mes "オーブをめぐって起きている";
		mes "マヨル・ジュンの一連の指示が、";
		mes "本当にオーブとラフィネの";
		mes "ためであること。";
		next;
		mes "[シナイム]";
		mes "私の心配が杞憂であったと";
		mes "証明してほしいだけです。";
		close;
	case 26:
		mes "[シナイム]";
		mes "あなたはオーブについて";
		mes "どれほどご存じですか？";
		next;
		mes "[シナイム]";
		mes "魔力が凝集された結晶、";
		mes "すべてのラフィネの誇り……";
		mes "そういった抽象的なものではなく、";
		mes "オーブがどのように管理されているか";
		mes "その構造的なものを言っています。";
		next;
		mes "[シナイム]";
		mes "オーブが飾ってある広場の天井を";
		mes "見上げたことはありますか？";
		next;
		mes "[シナイム]";
		mes "ないでしょう。";
		mes "実は、見上げたとしても";
		mes "まぶしい光で何も見えないんです。";
		next;
		menu "どうしてそんなことを話すんですか？",-;
		mes "‐シナイムは小さく笑っただけで、";
		mes "　質問には答えず、続けた‐";
		next;
		mes "[シナイム]";
		mes "オーブは常に広場に置かれ、";
		mes "誰にでも見れるよう、";
		mes "露出されています。";
		next;
		mes "[シナイム]";
		mes "そして、天井にはオーブを";
		mes "目立たせるための照明が";
		mes "設置されています。";
		next;
		mes "[シナイム]";
		mes "ただ、それは表向きの理由で、";
		mes "本当は警備の状況が外部に漏れないよう";
		mes "目くらましの役割を担っています。";
		next;
		mes "[シナイム]";
		mes "オーブを守る兵士たちは、";
		mes "その照明が設置された天井から";
		mes "見下ろし、警備を行って";
		mes "いるのです。";
		next;
		mes "[シナイム]";
		mes "下からでは照明がまぶしくて、";
		mes "警備の人数や配置が把握できません。";
		mes "万が一オーブに危機が迫った場合でも、";
		mes "有利に警備することができます。";
		next;
		mes "[シナイム]";
		mes "逆に言えば、";
		mes "その天井の警備を無力化させると";
		mes "オーブに害を与えやすくなると";
		mes "いうことです。";
		next;
		mes "[シナイム]";
		mes "どういう状態か把握するためにも";
		mes "一度、行ってみませんか？";
		mes "あなたなら大丈夫でしょう。";
		mes "あなたは王が間違った判断を";
		mes "下したのかそうではないのかを";
		mes "見守る義務を持った人間ですから。";
		next;
		mes "[シナイム]";
		mes "案内します。";
		mes "私の手を握ってください。";
		next;
		mes "‐どうしよう？‐";
		next;
		switch(select("カルデュイに先に知らせる","手を握る")) {
		case 1:
			mes "[シナイム]";
			mes "時間がほしいのですか？";
			mes "異種族に対してこのような";
			mes "好意も珍しいのに。";
			mes "まあ分かりました。";
			mes "心の整理ができたら";
			mes "来てください。";
			next;
			mes "‐いったんカルデュイに";
			mes "　報告に行こう‐";
			set ECL_3QUE,27;
			chgquest 7448,7449;
			close;
		case 2:
			mes "‐シナイムの手を掴むと、";
			mes "　一瞬チクッとする痛みが走った。";
			mes "　急いで手を放したが、";
			mes "　何の異常もない‐";
			next;
			menu "気のせいか……？",-;
			mes "[シナイム]";
			mes "どうしました？";
			mes "それでは行きますよ。";
			set ECL_3QUE,29;
			chgquest 7448,7450;
			close2;
			warp "ecl_hub01.gat",129,12;
			end;
		}
	case 27:
	case 28:
	case 29:
		mes "‐シナイムが謎の微笑みを見せながら";
		mes "　手を伸ばしてきた‐";
		next;
		if(select("まだ準備ができていない","手を握る") == 1) {
			mes "[シナイム]";
			mes "異種族に対してこのような";
			mes "好意も珍しいのに。";
			mes "まあ分かりました。";
			mes "心の整理ができたら";
			mes "来てください。";
			close;
		}
		mes "‐シナイムの手を掴むと、";
		mes "　一瞬チクッとする痛みが走った。";
		mes "　急いで手を放したが、";
		mes "　何の異常もない‐";
		next;
		menu "気のせいか……？",-;
		mes "[シナイム]";
		mes "どうしました？";
		mes "それでは行きますよ。";
		close2;
		set ECL_3QUE,29;
		warp "ecl_hub01.gat",129,12;
		end;
	case 30:
	case 31:
	case 32:
	case 33:
		mes "[見知らぬラフィネ]";
		mes "どうした？　シナイム？";
		mes "残念だが、彼女は急にいなくなって";
		mes "私が新しく任命された。";
		mes "業務中なので、用件がないなら";
		mes "ジャマをしないでほしい。";
		close;
	default:
		mes "[軍参謀]";
		mes "申し訳ございませんが、";
		mes "関係者以外出入することはできません。";
		close;
	}
}

ecl_in03.gat,41,90,5	script	カルデュイ	624,{
	switch(ECL_3QUE) {
	case 4:
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "エクラージュに来たことを歓迎する。";
		mes "異邦人よ。";
		next;
		mes "[カルデュイ]";
		mes "遠くから来た異邦人。";
		mes "そなたが私に伝えようとしている";
		mes "真実があると聞いたが……";
		next;
		mes "[カルデュイ]";
		mes "それが本当なら……";
		mes "これからそなたは、";
		mes "とても忙しくなるだろう。";
		next;
		menu "どういう意味ですか？",-;
		mes "[カルデュイ]";
		mes "そなたの知っている真実で";
		mes "私と元老会、そして数多くの";
		mes "ラフィネを説得するというのなら……";
		mes "我々の信頼を得るため、";
		mes "相応の努力が必要だ。";
		next;
		mes "[カルデュイ]";
		mes "もちろん、私はそなたの言葉を受けて、";
		mes "行動を起こす事もできる。";
		next;
		mes "[カルデュイ]";
		mes "しかし、だ……。";
		mes "異邦人の一言で動く王を、";
		mes "他のラフィネたちが受け入れて";
		mes "くれると思うか？";
		next;
		cutin "kardui03",1;
		mes "[カルデュイ]";
		mes "特にそれが私となれば……";
		next;
		mes "[カルデュイ]";
		mes "…………。";
		next;
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "ふん……まあ、いい。";
		mes "私の言いたいことはわかったか？";
		mes "そなたはこのエクラージュに";
		mes "もう少しその名を刻む必要が";
		mes "あるということだ。";
		next;
		if(select("功を立てろと？","イグドラシルに関する話ですが") == 1) {
			cutin "kardui01",1;
			mes "[カルデュイ]";
			mes "ふふ……";
			mes "ちゃんと理解したようだな。";
			next;
			menu "イグドラシルに関する話ですが",-;
		}
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "うむ……";
		mes "分かっている。";
		mes "そなたに言われるまでもなく、な。";
		next;
		mes "[カルデュイ]";
		mes "そこまで驚かなくてもいい。";
		mes "こう見えてもこの私は";
		mes "ラフィネの歴史であり精神、";
		mes "そしてイグドラシルの";
		mes "また異なる守護者。";
		next;
		mes "[カルデュイ]";
		mes "イグドラシルの意思を継承した私が";
		mes "何も知らないと思っていたのか？";
		mes "ラフィネの王を見くびるでない。";
		next;
		mes "[カルデュイ]";
		mes "まあ、そなたはまだ、この地について";
		mes "詳しく知らないのだろう。";
		mes "これ以上は問わないようにしよう。";
		next;
		mes "[カルデュイ]";
		mes "……ヨトゥンヘイムの戦争は";
		mes "遠くないうちに終結するはずだ。";
		mes "誰も納得しないような";
		mes "無理やり行う終結ではなく、";
		mes "皆の望むとおりの終結だ。";
		next;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "だから異邦人よ。";
		mes "戦争のことは気にするな。";
		mes "それより、エクラージュのために";
		mes "仕事をしてみないか？";
		next;
		menu "なぜ真実と向き合わないんですか？",-;
		cutin "kardui02",1;
		mes "[カルデュイ]";
		mes "うむ……";
		mes "その話を続けるのであれば、";
		mes "なおさらエクラージュのために";
		mes "働いてもらわねばならないな。";
		next;
		mes "[カルデュイ]";
		mes "言ったであろう？";
		mes "ラフィネの王、マヨル・ジュンたる私に";
		mes "意見するのであれば、";
		mes "まずは我々の信頼を得るための";
		mes "努力が必要だ。";
		next;
		mes "[カルデュイ]";
		mes "考えてみたまえ。";
		mes "このような重要な話を、";
		mes "今日初めて会ったばかりの";
		mes "そなたに話す義務はない。";
		mes "そうだろう？";
		next;
		menu "…………",-;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "そなたについては執政官と元老会、";
		mes "そしてすべてのガードに話しておく。";
		mes "これから、このエクラージュで";
		mes "王のために働く者と";
		mes "同じ権利を得ることになる。";
		next;
		mes "[カルデュイ]";
		mes "一族の王である私と親密になれるのだ。";
		mes "もしそれが嫌だというのなら……";
		mes "それならば私たちの仲が";
		mes "そのくらいでしかないと";
		mes "いうことだ。";
		next;
		menu "私たちはどんな仲なんですか？",-;
		mes "[カルデュイ]";
		mes "私たちの仲か？";
		mes "ふむ、そうだな……";
		mes "これからお互いに秘密を共有する仲、";
		mes "といったところか？";
		next;
		mes "[カルデュイ]";
		mes "……はは……面白くないか？";
		mes "簡単に言えば、私の友になれ、";
		mes "ということだ。";
		mes "ラフィネの王と友になれるのだ。";
		mes "喜ぶがよい。";
		next;
		mes "[カルデュイ]";
		mes "まあ、とにかくそなたの訪問は";
		mes "いつでも許可する。";
		next;
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "だが、私を満足させることが";
		mes "できなければ何も得ることは";
		mes "できないだろう。";
		mes "次に会う事を楽しみにしている。";
		mes "異邦人でありながら友になる者よ。";
		next;
		cutin "kardui04",255;
		mes "‐マヨル・ジュン　カルデュイと";
		mes "　これ以上踏み込んだ話をするには、";
		mes "　エクラージュで困っている人を助け、";
		mes "　信頼を得るほかないようだ‐";
		set ECL_3QUE,5;
		chgquest 72280,7417;
		close;
	case 5:
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "さあ、王のために働く者！";
		mes "私のために一生懸命働いてみろ！";
		next;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "……というのは冗談で。";
		next;
		mes "[カルデュイ]";
		mes "エクラージュで有名になるのは";
		mes "大変だろうが、";
		mes "いつかそなたの名を記憶している者が";
		mes "そなたを助ける日が来るはずだ……";
		next;
		cutin "kardui01",255;
		mes "‐マヨル・ジュン　カルデュイと";
		mes "　踏み込んだ話をするには、";
		mes "　エクラージュで困っている人を助け、";
		mes "　信頼を得るほかないようだ‐";
		close;
	case 6:
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "元気だったようだな。";
		next;
		menu "おかげ様で",-;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "ラフィネのために、";
		mes "よく働いてくれたそうだな。";
		mes "話は聞いているぞ。";
		next;
		mes "[カルデュイ]";
		mes "私がわざとそなたに面倒なことを";
		mes "させたと考えているんだな？";
		mes "ふふふ……まあ遠からず……";
		mes "しかし、結果として、我々の";
		mes "信頼は得られた。";
		mes "そうだろう？";
		next;
		mes "[カルデュイ]";
		mes "ふふ……さて……";
		mes "今日そなたをここに呼び出したのは";
		mes "以前、すべて話せなかったことを";
		mes "話すためだ。";
		mes "我が一族のために働いてくれた";
		mes "そなたへの礼だ。";
		next;
		menu "話せなかったこと？",-;
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "そなたは以前、私にイグドラシルを";
		mes "めぐる対立について話そうとしていた。";
		mes "今度は私がそのことをどうやって";
		mes "知っていたのかを答えよう。";
		next;
		mes "[カルデュイ]";
		mes "イグドラシルの守護者たる";
		mes "ラフィネの王マヨル・ジュンは";
		mes "イグドラシルと繋がっていて、";
		mes "ある程度の疎通が可能だ。";
		next;
		mes "[カルデュイ]";
		mes "イグドラシルに発生した異常現象は、";
		mes "サファ族の採掘が原因ではない、";
		mes "ということを……";
		mes "私はイグドラシルを通じて知っている。";
		next;
		menu "なのにどうして？",-;
		mes "[カルデュイ]";
		mes "疑問に思うのも当然だな。";
		mes "しかし、イグドラシルに異常現象が";
		mes "発生した時、理由は分からないが";
		mes "イグドラシルと疎通することが";
		mes "できなくなったのだ。";
		next;
		mes "[カルデュイ]";
		mes "それで、異常現象を調べるため";
		mes "調査団を送った。";
		next;
		mes "[カルデュイ]";
		mes "調査団の調査結果は、";
		mes "サファ族による無理な採掘に";
		mes "よるものだという報告があった。";
		mes "……その後はそなたも知って";
		mes "おるだろう。";
		next;
		menu "今はイグドラシルとの疎通は？",-;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "問題なく疎通できている。";
		mes "私がこの場所に座って、";
		mes "すべての真実を見抜いている。";
		next;
		mes "[カルデュイ]";
		mes "戦争が始まり、後戻りできない状態に";
		mes "なってから、再度イグドラシルと";
		mes "繋がることができるようになった。";
		next;
		cutin "kardui02",1;
		mes "[カルデュイ]";
		mes "それまで……イグドラシルとの疎通が";
		mes "再度行えるようになるまで、";
		mes "今まで感じた事のない";
		mes "とても凶悪な気を感じた。";
		next;
		mes "[カルデュイ]";
		mes "そんなときに、他の守護者、";
		mes "ニーズヘッグが、";
		mes "自身の義務を投げ捨てた。";
		mes "その当時は何が起きていたのか";
		mes "知る事ができなかったが。";
		next;
		mes "[カルデュイ]";
		mes "当時、イグドラシルと繋がりが";
		mes "切れた時のマヨル・ジュンは、";
		mes "その後、凶悪な気に耐える事が";
		mes "出来ないまま王位継承された。";
		next;
		mes "[カルデュイ]";
		mes "それで誕生したのが、";
		mes "現在のマヨル・ジュンである私だ。";
		next;
		cutin "kardui03",1;
		mes "[カルデュイ]";
		mes "覚醒した後、私は複雑になってしまった";
		mes "真実をどのように解けばいいのか、";
		mes "とても……とても長い間、悩んだ。";
		mes "まあ、それ以外にも個人的な問題が";
		mes "あってな……。";
		next;
		mes "[カルデュイ]";
		mes "…………。";
		next;
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "守護者の巣と関連した封印と浄化に";
		mes "参加した者たちには会ってみたか？";
		mes "数少ない真実を知っている者たちだ。";
		next;
		mes "[カルデュイ]";
		mes "だが、彼らも言っていた。";
		mes "戦争を止めるのは、すでに遅いと。";
		mes "この戦争はとても長い間";
		mes "続いてしまって、両方とも譲るには";
		mes "プライドが許さないと。";
		next;
		mes "[カルデュイ]";
		mes "しかし、考えもしなかった第3の勢力が";
		mes "入って来るようになった。";
		mes "それがそなたたち人間だ。";
		next;
		mes "[カルデュイ]";
		mes "そなたたちの登場でサファとラフィネ";
		mes "両側の視線がそなたたちに向いた。";
		mes "私はそれを機に、少しずつラフィネの";
		mes "考えを変えていこうとしているのだ。";
		next;
		mes "[カルデュイ]";
		mes "ヨトゥンヘイムの巨人、";
		mes "サファたちもすでに知っている。";
		mes "私たちはお互い敵ではないことを。";
		next;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "だから、そこまで心配しなくても";
		mes "大丈夫だ。";
		mes "それにこれはマヨル・ジュンになった";
		mes "私が解かなければならない問題。";
		mes "王として必ず解決すると約束しよう。";
		next;
		mes "[カルデュイ]";
		mes "これで少しは安心できたか？";
		mes "それとも、相変わらず心配か？";
		mes "しかし、そなたの考えはともかく";
		mes "疑問はある程度解消しただろう？";
		next;
		mes "[カルデュイ]";
		mes "まあ、疑問がなくなっても";
		mes "時々ここまで足を運んでくれ。";
		mes "マヨル・ジュンというのは忙しそうに";
		mes "見えるだろうが、実は割と暇なんだ。";
		mes "ははははは……";
		next;
		mes "[カルデュイ]";
		mes "そうだ、軍参謀に渡しておいた物が";
		mes "あるから、必ず受け取るように。";
		mes "いいな？";
		next;
		cutin "kardui01",255;
		mes "‐軍参謀のシナイムから";
		mes "　何かもらえるらしい。";
		mes "　受け取りに行こう‐";
		set ECL_3QUE,7;
		delquest 7421;
		getexp 200000,0;
		getexp 0,200000;
		setquest 7422;
		close;
	case 7:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "そなたに渡すプレゼントを";
		mes "用意しておいたから、";
		mes "軍参謀から貰ってくれ。";
		mes "これからそなたの役に立つだろう。";
		next;
		cutin "kardui01",255;
		mes "‐軍参謀のシナイムから";
		mes "　何かもらえるらしい。";
		mes "　受け取りに行こう‐";
		close;
	case 8:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "そのブローチ、とても可愛いだろう？";
		mes "使用すればいつでもエクラージュに";
		mes "戻ることができる。";
		mes "今はそなたに渡せるのは";
		mes "そのくらいしかないな。";
		close2;
		cutin "kardui01",255;
		end;
	case 9:
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "久しぶりだな。";
		mes "私に何か用でもあるのか？";
		next;
		switch(select("アレとは何ですか？","暴君らしいですね？","不幸の種！")) {
		case 1:
			cutin "kardui02",1;
			mes "[カルデュイ]";
			mes "アレ？　何のことだ？";
			mes "いきなり主語が抜かれている質問では、";
			mes "いくら私でも分からないぞ……。";
			break;
		case 2:
			cutin "kardui01",1;
			mes "[カルデュイ]";
			mes "この私が暴君？";
			mes "わはははははは！";
			mes "最高の冗談だ。";
			mes "私は今まで暴政を行ったことも、";
			mes "強制執行したこともないぞ。";
			break;
		case 3:
			cutin "kardui02",1;
			mes "[カルデュイ]";
			mes "不幸？　不幸の種……";
			mes "私に言っているのか？";
			break;
		}
		next;
		menu "噂について話す",-;
		cutin "kardui02",1;
		mes "[カルデュイ]";
		mes "そなたの話では、一族たちが私のことを";
		mes "あまり信じておらず、不安に思っている";
		mes "ということだな？";
		next;
		mes "[カルデュイ]";
		mes "ははは……";
		mes "すでに分かっていたことだが……";
		mes "うむ、わざわざ私のために、";
		mes "伝えに来てくれたことは感謝するよ。";
		next;
		mes "[カルデュイ]";
		mes "しかし、次からは話に来る前に";
		mes "一度考えてみたほうがいいぞ。";
		mes "そのような話し出しでは、";
		mes "ちょっと間違えば、お互いの関係に";
		mes "水を差しかねない。";
		next;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "いずれにしても、そなたの心の中で私は";
		mes "すでに友達になっているようだな。";
		mes "そうだろう？";
		mes "友達でなければ、そのような噂で";
		mes "心配するはずがない。";
		next;
		mes "[カルデュイ]";
		mes "…………。";
		next;
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "以前、私が話したことを覚えているか？";
		mes "私たちはこれから秘密を共有するように";
		mes "なる仲だと言ったことを。";
		mes "友達になった記念としてこの私が";
		mes "秘密をひとつ話してやろう。";
		next;
		mes "[カルデュイ]";
		mes "マヨル・ジュンとは、歴代すべての";
		mes "王の記憶が継承された者だ。";
		mes "初代マヨル・ジュンから、";
		mes "少し前の先代マヨル・ジュンまでの";
		mes "すべての記憶。";
		next;
		mes "[カルデュイ]";
		mes "それは巨大な情報の集合体で、";
		mes "あらゆる感情の集まりでもある。";
		mes "また、ラフィネにとってのドナの";
		mes "存在理由でもある。";
		mes "ドナは準備された器のような物だ。";
		next;
		mes "[カルデュイ]";
		mes "万が一、私に何かがあって";
		mes "急に死んでしまったとしよう。";
		mes "そうすると、ドナたちの中のひとりに";
		mes "すべての記憶が継承され、";
		mes "その者が新しいマヨル・ジュン、";
		mes "つまり、王になる。";
		next;
		menu "すごい話だけど、それが何の関係が？",-;
		mes "[カルデュイ]";
		mes "私はな。";
		mes "ドナとパパンの混血なんだ。";
		mes "マヨル・ジュンの器である";
		mes "ドナの血が汚れること、";
		mes "ラフィネの一族はそれを恐れている。";
		next;
		mes "[カルデュイ]";
		mes "実を言うと混血の王というのは";
		mes "私が初めてではない。";
		mes "その先例というのが、最初の混血王で";
		mes "そして……相当な暴君だったんだ。";
		next;
		cutin "kardui02",1;
		mes "[カルデュイ]";
		mes "混血というだけでも問題なのに、";
		mes "混血王の乱暴な気質を";
		mes "受け継ぐかもしれない……。";
		mes "一族が感じている不安は理解できる。";
		next;
		mes "[カルデュイ]";
		mes "先の混血王の名はセネスといった。";
		mes "セネスの記憶を受け継いだ時、";
		mes "私は悲しくて、辛かった。";
		mes "マヨルになると忘却という機能を";
		mes "失ってしまうから、";
		mes "忘れることもできない。";
		next;
		mes "[カルデュイ]";
		mes "混血王セネスは、";
		mes "自身が混血だとういう事実を";
		mes "呪いながら、狂い、破滅していった。";
		next;
		mes "[カルデュイ]";
		mes "今、一族たちが心配している状況は";
		mes "それなんだ。";
		mes "マヨル・ジュンが義務を果たさず";
		mes "狂ってしまうこと……";
		next;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "ははは……";
		mes "まあ、みんなが不安になっているのなら";
		mes "私はさらに一所懸命がんばるしかない。";
		next;
		mes "[カルデュイ]";
		mes "私が批判される混血だとしても、";
		mes "私は私がやらなければならない";
		mes "義務を果たす。";
		mes "そして……セネスのように";
		mes "運命から逃げたりもしない。";
		mes "だから、心配しなくても大丈夫だ。";
		next;
		cutin "kardui02",1;
		mes "[カルデュイ]";
		mes "……ただ、そうだな……";
		mes "そなたが、それでも私の";
		mes "心配をしてくれるというのなら……";
		next;
		mes "[カルデュイ]";
		mes "私の本当の友になってほしい……。";
		next;
		mes "[カルデュイ]";
		mes "…………。";
		next;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "話が長くなってしまったな。";
		mes "このようなことを話せる相手が";
		mes "いることは、嬉しいことだ。";
		mes "今までは、ただ耐えてきたからな。";
		next;
		mes "[カルデュイ]";
		mes "そういえばそなたの疑問に";
		mes "ふたつも答えてしまったな。";
		mes "次はこの借りを返せるような";
		mes "チャンスを与えてやるから、";
		mes "期待しているがよい。";
		next;
		cutin "kardui01",255;
		mes "‐カルデュイは、ラフィネの一族から";
		mes "　自分がどのように思われているのか";
		mes "　すでに知っていた。";
		mes "　そしてそれを乗り越え、王としての";
		mes "　役目を果たそうとしている‐";
		next;
		mes "‐しかし、友になってほしいと言う";
		mes "　カルデュイの表情には、";
		mes "　重圧に苦しむ彼の素顔が";
		mes "　にじんでいた‐";
		next;
		mes "‐もう一度、カルデュイに";
		mes "　話しかけてみよう‐";
		set ECL_3QUE,10;
		chgquest 7427,72258;
		getexp 200000,0;
		getexp 0,1000000;
		getexp 0,1000000;
		getexp 0,1000000;
		getexp 0,1000000;
		getexp 0,400000;
		close;
	case 10:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "エクラージュの生活はどうだ？";
		mes "君らのために道を作ってはいたが、";
		mes "君らは羽を持っていないから……";
		next;
		mes "[カルデュイ]";
		mes "あ、そうだ。";
		mes "実は君に対して偉そうに";
		mes "話すのはやめようと考えている。";
		mes "マヨルにはなったが、たまには";
		mes "私の年齢に合うような行動も";
		mes "してみたいのでな。";
		next;
		mes "[カルデュイ]";
		mes "マヨルというのは終わりなく続く";
		mes "前世の歯車のような物。";
		mes "継承された記憶だけで、";
		mes "数百回の人生を生きたのと同じなんだ。";
		next;
		mes "[カルデュイ]";
		mes "……この記憶に巻き込まれて、";
		mes "いつの間にか私は、数千年を生きてきた";
		mes "年寄りのようになってしまっていた。";
		next;
		mes "[カルデュイ]";
		mes "たまにはマヨル・ジュンの";
		mes "カルデュイではなく、";
		mes "普通のカルデュイでいても";
		mes "いいんじゃないかなと……思ったんだ。";
		mes "もちろん、実践に移すのは初めてだ。";
		next;
		cutin "kardui02",1;
		mes "[カルデュイ]";
		mes "それに……";
		next;
		mes "[カルデュイ]";
		mes "……セネスにも心から話せるような";
		mes "相手がいたなら、";
		mes "未来は変わっていたのではと……";
		mes "そのようなことを、たまに考える。";
		next;
		mes "[カルデュイ]";
		mes "…………。";
		next;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "ま、そういうわけだから！";
		mes "これから私たちの仲を";
		mes "さらに親密にして行こうではないか。";
		next;
		cutin "kardui01",255;
		mes "‐偉そうに話すのはやめると";
		mes "　言いながらも、王としての話し方が";
		mes "　染みついてしまっているのか、";
		mes "　その口調はどこかぎこちない‐";
		next;
		mes "‐もう一度カルデュイから";
		mes "　話を聞こう‐";
		set ECL_3QUE,11;
		chgquest 72258,72263;
		close;
	case 11:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "ビフロストタワーには";
		mes "行ってみたか？";
		next;
		if(select("行ってみた","行ってみる予定だ","まったく考えていない") == 3) {
			mes "[カルデュイ]";
			mes "それは残念だな。";
			mes "エクラージュの名所の中の";
			mes "ひとつなのに……";
			close2;
			cutin "kardui01",255;
			end;
		}
		mes "[カルデュイ]";
		mes "では安心して仕事を頼むことができる。";
		mes "　";
		mes "王からの命令だ！";
		mes "ビフロストタワーにいるある人物に";
		mes "この手紙を渡してこい！";
		next;
		menu "……",-;
		mes "[カルデュイ]";
		mes "…………。";
		next;
		mes "[カルデュイ]";
		mes "ふふ、冗談だ。";
		mes "手紙を渡したい相手は私の兄でな。";
		mes "個人的なことだから";
		mes "友達に頼むことにしたんだ。";
		mes "やってくれるよな？";
		mes "この機会に貸しを返してくれよ。";
		next;
		mes "[カルデュイ]";
		mes "ビフロストタワーの最上階に";
		mes "行くと会える。";
		mes "兄さんはそこで暮らしている。";
		mes "これを渡してくれ。";
		next;
		cutin "kardui01",255;
		mes "‐カルデュイから手紙を受け取った。";
		mes "　ビフロストタワー最上階にいるという";
		mes "　カルデュイの兄に渡しに行こう‐";
		set ECL_3QUE,12;
		chgquest 72263,7434;
		close;
	case 12:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "ビフロストタワーの最上階に行って";
		mes "私の兄さんにその手紙を渡してくれ。";
		mes "まあ、行ってみればわかる。";
		next;
		mes "‐カルデュイからの手紙を";
		mes "　ビフロストタワー最上階にいるという";
		mes "　カルデュイの兄に渡しに行こう‐";
		close2;
		cutin "kardui01",255;
		end;
	case 13:
	case 14:
	case 15:
	case 16:
	case 17://?
	case 18://?
	case 19://?
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "素晴らしい兄さんだっただろ？";
		mes "この世の中で唯一私の考えを";
		mes "分かってくれている人なんだ。";
		mes "私を慰めてくれたのも、";
		mes "私の憎悪を抑えてくれたのも";
		mes "すべて兄さんだ。";
		next;
		mes "[カルデュイ]";
		mes "もし兄さんがいなかったら、";
		mes "私もセネスのようになっていたかも";
		mes "しれない……。";
		next;
		mes "[カルデュイ]";
		mes "さあ、私のもう一つの頼みを";
		mes "兄さんから聞いただろ？";
		mes "それもとても重要なんだ。";
		mes "よろしく頼むよ。";
		close2;
		cutin "kardui01",255;
		end;
	case 20:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "何か成果はあったか？";
		mes "……？";
		mes "あれっ？";
		mes "兄さん!?";
		next;
		cutin "hisie04",0;
		mes "[ヒシエ]";
		mes "こうやって直接会って話すのは";
		mes "久しぶりだな。";
		next;
		menu "どうやって入って来たんですか？",-;
		mes "[ヒシエ]";
		mes "以前より警備が";
		mes "緩んでいるんじゃないか？";
		mes "簡単に入って来ることができたぞ。";
		next;
		cutin "kardui05",2;
		mes "[カルデュイ]";
		mes "夢のようです。";
		mes "警備が薄ければ";
		mes "兄さんにいつでも会えるの？";
		mes "それならば、これからは";
		mes "この状態を維持しないと。";
		next;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "いいえ、兄さん！";
		mes "ここで暮らしてください。";
		mes "タワーに戻らないで……";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "そうしてやりたいが、";
		mes "それではお前が困ってしまう。";
		mes "代わりに頻繁に来るようにする。";
		mes "それでいいだろ？";
		next;
		cutin "kardui02",2;
		mes "[カルデュイ]";
		mes "そう……ですね……";
		next;
		cutin "kardui01",255;
		menu "そろそろ本題に入ろう",-;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "……ん？";
		mes "ああ、悪かった！";
		mes "君がいるのを忘れていたよ。";
		mes "久しぶりの再会で、";
		mes "気分が高ぶってしまったんだ。";
		next;
		cutin "kardui04",2;
		mes "[カルデュイ]";
		mes "そうだな……";
		mes "王たる者、兄とはいえ、";
		mes "招かれざる客の来訪を";
		mes "喜んではいけない……";
		next;
		mes "[カルデュイ]";
		mes "君の言いたいことはよくわかった。";
		mes "二度とこんなことがないように、";
		mes "もう兄さんとは会わない。";
		mes "それでいいんだろう？";
		next;
		menu "そんな意味ではありません！",-;
		cutin "kardui05",2;
		mes "[カルデュイ]";
		mes "ふふふ……。";
		mes "冗談だ、怒るな。";
		mes "しかし、その真っ赤な顔……";
		mes "ふふふ……あははははは！";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "……。";
		mes "お前にはどのように";
		mes "聞こえるかわからないが……";
		next;
		mes "[ヒシエ]";
		mes "私はお前がマヨルになって";
		mes "良かったと思っているよ。";
		next;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "え？";
		mes "兄さん、それはどういう意味ですか？";
		mes "冗談でも……";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "今のように、明るく前向きになった";
		mes "お前の姿を見ることができて";
		mes "嬉しいということだよ。";
		next;
		mes "[ヒシエ]";
		mes "自分の存在を呪い、";
		mes "一族を恨んでやいないかと";
		mes "ずっと心配だった……。";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "おっと、これ以上話を続けると、";
		mes "お前の友人にまた怒られてしまう。";
		next;
		mes "[ヒシエ]";
		mes "それで本題だが……。";
		mes "エイヴァントの居場所を見つけた。";
		mes "エクラージュで暮らしている。";
		mes "それと何かの研究をしているようだ。";
		next;
		cutin "kardui04",2;
		mes "[カルデュイ]";
		mes "まさか、また変なものを";
		mes "研究しているのでは？";
		mes "いや……そうでなかったとしても";
		mes "邪魔をしてやりたくなる。";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "同感だ。";
		mes "いずれにしろ、あいつの研究が何なのか";
		mes "把握しておく必要はあるだろう。";
		next;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "エイヴァントは計画外のことが";
		mes "発生することを、とても嫌って";
		mes "いましたよね？";
		mes "ならば、いっぱいプレゼントして";
		mes "あげてください。";
		mes "その計画外の状況を。";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "うむ。";
		mes "カルの友人よ。";
		mes "急いで準備してくれ。";
		next;
		cutin "hisie01",255;
		mes "‐エイヴァントの研究内容を";
		mes "　調べるため、彼のヤイに向かおう‐";
		set ECL_3QUE,21;
		chgquest 7442,7443;
		close;
	case 21:
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "エイヴァントの研究室に行き、";
		mes "彼が何を研究しているのか";
		mes "調べてきてほしい。";
		mes "ついでに研究の邪魔を";
		mes "してくるのもいい。";
		next;
		mes "[カルデュイ]";
		mes "ふふふ……";
		mes "想像するだけで気分が良くなる。";
		mes "しっかり兄さんをサポートするように。";
		next;
		cutin "kardui01",255;
		mes "‐エイヴァントの研究内容を";
		mes "　調べるため、彼のヤイに向かおう‐";
		close;
	case 22:
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "調査は無事終了したようだね。";
		next;
		cutin "kardui05",2;
		mes "[カルデュイ]";
		mes "君の話は兄さんから聞いたよ。";
		mes "あのエイヴァントを";
		mes "倒したそうじゃないか？";
		mes "ふふふふ……";
		next;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "しかし、隠れて何をしているのかと";
		mes "思っていたが、こんな物を";
		mes "研究していたとは。";
		next;
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "オーブの魔力を強制的に";
		mes "抽出するための研究のようだな。";
		mes "奴の頭がおかしいのは、";
		mes "今も昔も変わらないようだ。";
		next;
		cutin "kardui03",2;
		mes "[カルデュイ]";
		mes "まあ……そのおかげで、";
		mes "私たち兄弟がいるんですが。";
		mes "あぁ、イライラする。";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "ああ……そうだな。";
		mes "とにかく今回の研究はやり過ぎだ。";
		mes "突然エイヴァントを探せと";
		mes "言ってきたのは、これを予想して";
		mes "いたからなのか？";
		next;
		cutin "kardui02",2;
		mes "[カルデュイ]";
		mes "そうです。";
		mes "イグドラシルから何か不気味な……";
		mes "不安のようなものを感じたので。";
		mes "明確に何かは分からなかったけど、";
		mes "頭の中に浮かんだのが";
		mes "エイヴァントだった……";
		next;
		menu "オーブとは？",-;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "オーブは私たち一族、ラフィネの";
		mes "すべての魔力。";
		mes "とてつもない魔力が集まっている。";
		next;
		mes "[カルデュイ]";
		mes "万が一エイヴァントの研究通りに";
		mes "オーブの魔力を強制的に抽出して";
		mes "使用することができたなら……";
		mes "恐ろしく強大な力を得ることになる。";
		next;
		cutin "kardui04",2;
		mes "[カルデュイ]";
		mes "たとえば誰かが悪い意図で";
		mes "オーブの魔力を盗んで、";
		mes "その力をふるい始めたら……";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "とんでもない災難だ。";
		mes "研究の進行結果を見ると";
		mes "ほぼ最後の段階まで来ている。";
		mes "この研究結果を私たちだけが";
		mes "知っているなら良いが……";
		next;
		cutin "kardui04",2;
		mes "[カルデュイ]";
		mes "万が一他の者がこのことを";
		mes "知っていたらオーブが危険です。";
		mes "オーブの警戒を強化します。";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "では私はエイヴァントを";
		mes "もう少し追及してみよう。";
		next;
		cutin "kardui05",2;
		mes "[カルデュイ]";
		mes "兄さん、ありがとう。";
		mes "オーブのことは私に任せて。";
		next;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes strcharinfo(0)+ "、";
		mes "これは君へのプレゼントだ。";
		mes "私の魔力が君の成長の";
		mes "大きな力になればと";
		mes "思っている。";
		misceffect 83,"";
		delitem 6541,1;
		getexp 400000,0;
		getexp 0,300000;
		set ECL_3QUE,23;
		chgquest 7444,72268;
		next;
		cutin "kardui01",255;
		mes "‐ヒシエはエイヴァントについて";
		mes "　引き続き調べるらしい。";
		mes "　ビフロストタワー最上階に行き、";
		mes "　ヒシエから話を聞いてみよう‐";
		close;
	case 23:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "オーブの警戒を強化するように";
		mes "指示してある。";
		mes "急な警戒強化だったから";
		mes "みんな驚いていたようだが……";
		next;
		mes "[カルデュイ]";
		mes "オーブはとても大切なものだ。";
		mes "それを守ることなんだから";
		mes "従うだろう。";
		next;
		cutin "kardui01",255;
		mes "‐ビフロストタワー最上階に行き、";
		mes "　エイヴァントについて引き続き";
		mes "　調べているヒシエから";
		mes "　話を聞いてみよう‐";
		close;
	case 24:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "シナイムについて、";
		mes "兄さんとそのような話をしたのか。";
		mes "そういえば確かにエイヴァントを";
		mes "支援していたよな。";
		next;
		mes "[カルデュイ]";
		mes "いや、正確に話すと、";
		mes "彼女は自分が支援していたのが";
		mes "魔学者のエイヴァントだったことを";
		mes "知らなかったのだ。";
		mes "個人的な支援まで私が口だしすることは";
		mes "できない。";
		next;
		mes "[カルデュイ]";
		mes "兄さんが話していたように";
		mes "君が協力してくれるなら、";
		mes "私としても歓迎する。";
		mes "よろしく頼む。";
		close2;
		cutin "kardui01",255;
		end;
	case 25:
		mes "[カルデュイ]";
		mes "兄さんからも話を聞いたよ。";
		mes "エイヴァントに気を取られ過ぎて、";
		mes "シナイムのことを綺麗に忘れていた。";
		cutin "kardui01",1;
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "何か成果でもあったのか？";
		mes "これまでの印象だと、";
		mes "シナイムが裏で糸を引いていたとは";
		mes "考えづらい。";
		next;
		mes "[ヒシエ]";
		mes "支援していた魔学者とも、";
		mes "偶然出会ったようだしな。";
		next;
		if(checkquest(7446)) {
			menu "シナイムにすべて伝えた",-;
			mes "[カルデュイ]";
			mes "魔学者がエイヴァントだったのを";
			mes "話したのか？";
			mes "彼が研究していた内容についても？";
			cutin "kardui01",2;
			next;
			cutin "hisie01",0;
			mes "[ヒシエ]";
			mes "しかし結局はシナイムも";
			mes "自身が後押ししていた魔学者の";
			mes "正体や個人研究については";
			mes "知らなかったということだな？";
			next;
			cutin "hisie02",0;
			mes "[ヒシエ]";
			mes "だが、それは知らないふりを";
			mes "しているだけの可能性もある。";
			mes "やはり、考えなしに接触するだけでは、";
			mes "すべてを知ることはできないか……。";
			next;
		}
		mes "[ヒシエ]";
		mes "他には何か言っていたか？";
		next;
		menu "シナイムとの会話内容を伝える",-;
		cutin "hisie02",255;
		mes "‐シナイムもほかのラフィネと同様に、";
		mes "　カルデュイに不安を抱いている";
		mes "　ことなど、会話の内容を全て伝えた‐";
		next;
		cutin "kardui02",2;
		mes "[カルデュイ]";
		mes "シナイム……";
		mes "他の官僚たちとは違って";
		mes "偏見なしで接してくれていると";
		mes "信じていたのに……";
		mes "それが嘘だったとは……";
		next;
		mes "[カルデュイ]";
		mes "私なりに努力はしたつもりだったけど、";
		mes "不信感をなくすには至らないのか……。";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "気にするな。";
		mes "どう思われていようが、";
		mes "お前はお前の信念通りの";
		mes "ことをすればいい。";
		next;
		mes "[ヒシエ]";
		mes "大丈夫だ。";
		mes "いつかみんながお前のことを";
		mes "認めてくれる日がくる。";
		mes "じっと息をひそめて過ぎ去るのを";
		mes "待つ対象ではなく、";
		mes "真のマヨルであるということを。";
		next;
		mes "[カルデュイ]";
		mes "そう……ですね。";
		mes "一時の感情に惑わされたのでは";
		mes "セネスと変わらないですよね？";
		cutin "kardui01",2;
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "それよりシナイムだ……。";
		mes "エイヴァントの研究に関わっていた者は";
		mes "やはりシナイムしか見つからないんだ。";
		mes "あいつはきっと何かを隠している。";
		next;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes strcharinfo(0)+ "、";
		mes "君にはいつもこんなことしか";
		mes "言えないが……。";
		mes "今回も私の力になってくれ。";
		next;
		menu "わかりました",-;
		mes "[カルデュイ]";
		mes "シナイムがなぜ、エイヴァントの";
		mes "研究に関わっていたのか……。";
		mes "きっと何か理由があるはず。";
		next;
		mes "[カルデュイ]";
		mes "不安感が絶え間なく襲ってくる。";
		mes "これはイグドラシルが送っている";
		mes "警告のメッセージなのだろうか？";
		next;
		mes "[カルデュイ]";
		mes "……大きなカギといえる君が";
		mes "私の味方で助かったよ。";
		mes "シナイムの真意はわからないが";
		mes "もう少しあの者について";
		mes "調べてみてくれ。";
		next;
		mes "[カルデュイ]";
		mes "頼む。";
		cutin "kardui04",2;
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "私も当分の間はここに居る予定だ。";
		mes "何かわかったらここまで来てくれ。";
		mes "頼むぞ。";
		set ECL_3QUE,26;
		chgquest 7446,7448;
		chgquest 7447,7448;
		close2;
		cutin "hisie01",255;
		end;
	case 26:
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "不安感が絶え間なく襲ってくる。";
		mes "この不安の正体が何なのか知りたい。";
		mes "これはイグドラシルが送っている";
		mes "警告のメッセージなのだろうか？";
		next;
		mes "[カルデュイ]";
		mes "シナイムのことは君に任せる。";
		mes "私は権力を持たないマヨルだ。";
		mes "君の力になることはできない。";
		mes "悪いな、毎回頼んでばかりで。";
		cutin "kardui02",2;
		close2;
		cutin "kardui02",255;
		end;
	case 27:
		mes "[カルデュイ]";
		mes "興味深くなって来たな！";
		mes "いったいどうしてだ？";
		mes "天井にある照明装置は";
		mes "ラフィネならみんなが知っている。";
		cutin "kardui04",2;
		next;
		mes "[カルデュイ]";
		mes "しかし、知っているのとわざと";
		mes "知らせるのでは、大きな違いがある。";
		mes "いったいなぜ、わざわざ君に";
		mes "オーブの警備について話したんだ？";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "焦らなくていい。";
		mes "まだ何かが起きたわけではない。";
		mes "シナイムがどうしてあのような";
		mes "態度に出ているか調べて";
		mes "これからのことを";
		mes "考えないといけないだろ？";
		next;
		menu "ヒシエの言う通りだ。",-;
		cutin "kardui04",2;
		mes "[カルデュイ]";
		mes "……今、できること……";
		mes strcharinfo(0)+ "、";
		mes "君がシナイムの言う通りに動いて";
		mes "真相を調べること……くらいか？";
		next;
		cutin "kardui03",2;
		mes "[カルデュイ]";
		mes "わかった。";
		mes "万が一のために追加兵力を";
		mes "送るよう手配する。";
		mes "君はシナイムが求めている通りに";
		mes "動いてみろ。";
		next;
		mes "[カルデュイ]";
		mes "今はただシナイムが";
		mes "本当に純粋な意図でそうしたと……";
		mes "信じるしかない。";
		next;
		mes "‐軍参謀シナイムのところに行き、";
		mes "　照明室に案内してもらおう‐";
		set ECL_3QUE,28;
		chgquest 7449,7450;
		close2;
		cutin "kardui03",255;
		end;
	case 28:
	case 29:
		cutin "kardui04",2;
		mes "[カルデュイ]";
		mes "シナイムが君をオーブと照明室に";
		mes "導こうとする理由を";
		mes "明かさなければならない。";
		next;
		mes "[カルデュイ]";
		mes "……今、できること……";
		mes strcharinfo(0)+ "、";
		mes "君がシナイムの言う通りに動いて";
		mes "真相を調べること……くらいか？";
		next;
		cutin "kardui03",2;
		mes "[カルデュイ]";
		mes "わかった。";
		mes "万が一のために追加兵力を";
		mes "送るよう手配する。";
		mes "君はシナイムが求めている通りに";
		mes "動いてみろ。";
		next;
		mes "[カルデュイ]";
		mes "今はただシナイムが";
		mes "本当に純粋な意図でそうしたと……";
		mes "信じるしかない。";
		next;
		mes "‐軍参謀シナイムのところに行き、";
		mes "　照明室に案内してもらおう‐";
		close2;
		cutin "kardui03",255;
		end;
	case 30:
		cutin "kardui02",2;
		mes "[カルデュイ]";
		mes "私に力がないばかりに……";
		mes "苦労をさせてしまった。";
		mes "すまない……。";
		next;
		menu "オーブの核が奪われたと聞きました",-;
		mes "[カルデュイ]";
		mes "うむ……";
		mes "今は一族に気づかれないよう、";
		mes "私と兄さんの魔力を集めて";
		mes "持続的にオーブに供給している。";
		next;
		cutin "kardui04",2;
		mes "[カルデュイ]";
		mes "目くらまし程度だが……";
		mes "私たち兄弟は魔力が強いから";
		mes "幸いまだ気づかれていない。";
		mes "はは……これはエイヴァントに";
		mes "感謝したらいいのか？";
		next;
		mes "[カルデュイ]";
		mes "ただいつもより2、3倍疲れる。";
		mes "魔力が抜けていく感じは";
		mes "いい気分ではないな。";
		mes "この溢れる魔力を集めて";
		mes "再度オーブの核を埋めることが";
		mes "できるかな？";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "……無理するな。";
		mes "いくら私が協力していると";
		mes "いっても魔力の限界はある。";
		next;
		cutin "kardui04",2;
		mes "[カルデュイ]";
		mes "そのことはその時が来たら";
		mes "考えるようにしましょうよ。";
		next;
		mes "[カルデュイ]";
		mes "それより……";
		mes "ニーズヘッグ様から聞いた。";
		mes "シナイムは、モロクの手下に";
		mes "操られていたらしいじゃないか？";
		next;
		cutin "kardui02",2;
		mes "[カルデュイ]";
		mes "どうして気づかなかったんだろう。";
		mes "……本当に私は……";
		mes "人形のようなマヨルだ……";
		next;
		mes "[カルデュイ]";
		mes "しかし、オーブやシナイムのことも";
		mes "大事だが、今一番の問題は";
		mes strcharinfo(0)+ "のことだ。";
		cutin "kardui01",2;
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "そうだな。";
		mes "元老会のラフィネたちが";
		mes "照明室での暴行の主犯として";
		mes "君に注目している状態だ。";
		next;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "元老たちには私から";
		mes "オーブは無事だと話してある。";
		mes "彼らが気にしているのは";
		mes "兵士たちの怪我と";
		mes "シナイムの行方だ。";
		next;
		menu "エイヴァントについて話す。",-;
		mes "[カルデュイ]";
		mes "そうだった、君がいた監獄には";
		mes "エイヴァントもいたな。";
		mes "すべてのことの元凶を";
		mes "忘れるところだった。";
		next;
		mes "‐監獄でエイヴァントと";
		mes "　交わした会話について話した‐";
		next;
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "……。";
		mes "結局はエイヴァント、私、シナイム、";
		mes "君も魔王に利用されていたのか。";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "再度話を戻して";
		mes strcharinfo(0)+ "の問題だが……。";
		mes "君が協力していたラフィネたちが";
		mes "君の味方になってくれるようだ。";
		next;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "それは助かりますね。";
		mes "けれど正当防衛を認めても";
		mes "表面的なだけで内心では……";
		next;
		menu "シナイムを追跡します！",-;
		mes "["+strcharinfo(0)+"]";
		mes "正当防衛だとしても私が";
		mes "兵士たちを怪我させたのは事実です。";
		mes "私に責任をとるチャンスをください。";
		mes "すべての元凶であるシナイムを";
		mes "探します。";
		mes "ついでにオーブも探しますよ！";
		next;
		mes "[カルデュイ]";
		mes "……そのように考えているなら君に、";
		mes "今回の事件の責任を取るために";
		mes "シナイムを探せ、と命を下そう。";
		next;
		mes "[カルデュイ]";
		mes "オーブも探せたらいいが、";
		mes "万が一のための準備をしておく";
		mes "必要がありそうだな。";
		mes "エイヴァントと話をしてみる。";
		next;
		cutin "kardui04",2;
		mes "[カルデュイ]";
		mes "……殺せる良いチャンスだったのに。";
		mes "残念だ。";
		mes "今回はこちらから頼むしかない。";
		next;
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "カル、すべてうまくいくはずだ。";
		mes "焦る必要はない。";
		mes "守護者たちが集まったんだろ。";
		mes "きっとうまくいく。";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "では、表面的なことはカルが行い、";
		mes "シナイムの追跡は";
		mes strcharinfo(0)+ "に任せる。";
		mes "私もオーブに魔力を注がなければ";
		mes "ならないのでカルのそばに残る。";
		next;
		cutin "kardui01",2;
		mes "[カルデュイ]";
		mes "ありがとうございます、兄さん。";
		next;
		mes "[カルデュイ]";
		mes "では、君の行動の自由は";
		mes "私が何とかするから、";
		mes "シナイムのことは頼んだぞ。";
		mes "兄さんの話では^4d4dffビフロストの";
		mes "何処かで手がかりをみつけることが";
		mes "できるはず^000000とのことだ。";
		set ECL_3QUE,31;
		chgquest 7451,7452;
		close2;
		cutin "kardui01",255;
		end;
	case 31:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "照明室であった乱闘は";
		mes "正当防衛だと立証された。";
		mes "行動に制約がかかったりすることは";
		mes "なくなっている。";
		next;
		mes "[カルデュイ]";
		mes "シナイムのことは頼んだぞ。";
		mes "兄さんの話では^4d4dffビフロストの";
		mes "何処かで手がかりをみつけることが";
		mes "できるはず^000000とのことだ。";
		close2;
		cutin "kardui01",255;
		end;
	case 32:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "穴の開いた死体か……";
		mes "軍参謀である彼女も";
		mes "利用されていたんだな。";
		next;
		cutin "kardui02",1;
		mes "[カルデュイ]";
		mes "どうして誰も気づかなかったの";
		mes "だろう……。";
		mes "油断や怠惰が呼び寄せたことなのか？";
		next;
		mes "[カルデュイ]";
		mes "いや、イグドラシルと疎通できる";
		mes "私が気づいてやるべき";
		mes "だったのだ……。";
		next;
		mes "[カルデュイ]";
		mes "…………。";
		next;
		cutin "kardui04",1;
		mes "[カルデュイ]";
		mes "まずは私がしっかりしなくては";
		mes "いけないな。";
		mes "シナイムの死は、私の意志を";
		mes "貫くための力になるだろう。";
		next;
		mes "[カルデュイ]";
		mes "これからは魔王を";
		mes "相手にするための準備をする。";
		mes "それが今の私ができる";
		mes "最善のことだから。";
		next;
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "君にはこれまで本当に世話になったな。";
		mes "これからも友として力を貸してほしい。";
		next;
		mes "[カルデュイ]";
		mes "イグドラシルの祝福が君のそばに……";
		misceffect 83,"";
		set ECL_3QUE,33;
		chgquest 7453,201615;
		getitem 6081,75;
		getexp 8450000,0;
		getexp 0,400000;
		close2;
		cutin "kardui01",255;
		end;
	case 33:
		switch(rand(3)) {
		case 0:
			cutin "kardui01",1;
			mes "[カルデュイ]";
			mes "頭の中がかなり混沌としている。";
			mes "元々いくつもの意識が混ざり合った";
			mes "ようなものがマヨルの頭の中だが……";
			mes "これはそれを超える。";
			next;
			mes "[カルデュイ]";
			mes "ああ、だだをこねたいのに";
			mes "兄さんは何処に行ったんだ？";
			mes "ふふ、このような私の姿を";
			mes "他のラフィネたちが見たら";
			mes "驚くんだろうな？";
			next;
			cutin "kardui05",1;
			mes "[カルデュイ]";
			mes "あははははは";
			mes "千年の知識も一万年の知識も";
			mes "全部いらない気がする。";
			next;
			cutin "kardui03",1;
			mes "[カルデュイ]";
			mes "先代のマヨルの記憶から情報を";
			mes "探っているのだけれど、";
			mes "魔王に対抗する方法などはない……。";
			next;
			cutin "kardui01",1;
			mes "[カルデュイ]";
			mes "やはりこの部分は専門家に";
			mes "任せるしかないようだな……。";
			close2;
			cutin "kardui01",255;
			end;
		case 1:
			cutin "kardui03",1;
			mes "[カルデュイ]";
			mes "全身から血を抜かれる気分というのは";
			mes "こんな感じなのかな？";
			mes "魔力が抜けていく気分は……";
			mes "ごめん、少し疲れた……";
			close2;
			cutin "kardui03",255;
			end;
		case 2:
			cutin "hisie02",0;
			mes "[ヒシエ]";
			mes "そのままにしておいてやれ……";
			mes "今さっき寝たところだ。";
			mes "オーブの消えた魔力を補充するのに";
			mes "相当疲れたようだ。";
			next;
			mes "[ヒシエ]";
			mes "気に入らないが、エイヴァントが";
			mes "オーブ内の核の代わりになるような";
			mes "新しい物を作っている最中だ。";
			mes "完成すれば、私やカルが魔力を";
			mes "供給する必要もなくなるだろう。";
			next;
			mes "[ヒシエ]";
			mes "本当……あいつに頭を";
			mes "下げることになるとはな。";
			mes "…………。";
			close2;
			cutin "hisie02",255;
			end;
		}
	default:
		cutin "kardui01",1;
		mes "[カルデュイ]";
		mes "うむ……";
		mes "どこの誰かは知らないが、";
		mes "私は呼んでないぞ？";
		close2;
		cutin "kardui01",255;
		end;
	}
}

ecl_fild01.gat,205,86,3	script	エクラージュ伝令ロイ	461,{
	switch(ECL_3QUE) {
	case 5:
		if(ECL_3QUE_sub & 0x4) {
			mes "[ロイ]";
			mes "私は郵便物を届けに行きますので。";
			mes "ありがとう、ご苦労様でした。";
			close;
		}
		if(checkquest(7419)) {
			if(countitem(6552) < 1) {
				mes "[ロイ]";
				mes "もう一度説明します。";
				mes "スプレンディッド前線基地に行って、";
				mes "定期連絡担当と会って！";
				next;
				mes "[ロイ]";
				mes "重要でもなんでもない、";
				mes "誰かのラブレターかも知れない！";
				mes "郵便物を受け取って、";
				mes "私の所まで持ってきてください。";
				close;
			}
			mes "[ロイ]";
			mes "この箱で間違いありません。";
			mes "ちゃんと受け取って来ましたね。";
			next;
			mes "[ロイ]";
			mes "それにしても……見てください。";
			mes "大した内容もないものばかり。";
			mes "個人的な挨拶程度の手紙が";
			mes "大半ですね。";
			next;
			delitem 6552,1;
			set ECL_3QUE_sub,ECL_3QUE_sub|4;
			delquest 7419;
			getexp 200000,0;
			getexp 0,200000;
			if(ECL_3QUE_sub & 0x7 == 0x7) {	// 未調査
				mes "[エクラージュガード]";
				mes "ここにいましたか。";
				mes "マヨル・ジュンから、あなたを探すよう";
				mes "指示されました。";
				mes "ロイの頼みも聞いてくれたんですか？";
				cutin "minuel01",4;
				next;
				mes "[エクラージュガード]";
				mes "そうですか。";
				mes "では、あの方からの伝言を";
				mes "お伝えします。";
				next;
				mes "[エクラージュガード]";
				mes "あなたはエクラージュのために";
				mes "たくさんの仕事をしてくれた。";
				mes "もう十分やってくれたと思っている。";
				next;
				mes "[エクラージュガード]";
				mes "とのことです。";
				mes "このように伝えれば分かるはずだと。";
				mes "それでは私はこれで失礼します。";
				set ECL_3QUE,6;
				set ECL_3QUE_sub,0;
				chgquest 7417,7421;
				next;
				cutin "minuel01",255;
				mes "‐マヨル・ジュン　カルデュイが";
				mes "　呼んでいるらしい。";
				mes "　王宮にいるカルデュイに会いに";
				mes "　行こう‐";
				close;
			}
			mes "[ロイ]";
			mes "私はこの郵便物を届けに行きますので。";
			mes "ありがとう、ご苦労様でした。";
			close;
		}
		mes "[ロイ]";
		mes "困りました。";
		mes "本っ当に困りました……。";
		next;
		mes "[ロイ]";
		mes "考えれば考えるほど、";
		mes "これはシナイムの嫌がらせだとしか";
		mes "思えないです。";
		emotion 0;
		next;
		mes "[ロイ]";
		mes "こんな絶妙なタイミングで";
		mes "現れたあなた。";
		mes "霧の森を通って来たあなたは";
		mes "神の祝福でも受けているんですか？";
		next;
		mes "[ロイ]";
		mes "プライドを無くしたら";
		mes "死んだも同然と思っている";
		mes "ラフィネですが、仕方がない。";
		mes "私は私の命が大事なので。";
		next;
		mes "[ロイ]";
		mes "申し訳ありませんが、";
		mes "ひとつお願いします。";
		next;
		if(select("何を？","断る") == 2) {
			mes "[ロイ]";
			mes "あ……";
			mes "考えもしないで拒否するなんて。";
			mes "ううぅ……";
			next;
			mes "[ロイ]";
			mes "私は今の記憶を抹消します！";
			mes "そうすれば再度お願いすることが";
			mes "できますから！";
			mes "あはははは！";
			mes "はは……はあ……";
			close;
		}
		mes "[ロイ]";
		mes "私たちラフィネには難しいが、";
		mes "あなたたちには簡単なことです。";
		mes "スプレンディッドから手紙を";
		mes "貰ってきてほしいんです！";
		next;
		mes "[ロイ]";
		mes "本当は私が指示された";
		mes "仕事なのですが……";
		mes "私は魔力が強い方ではないので。";
		next;
		mes "[ロイ]";
		mes "スプレンディッド前線基地の";
		mes "定期連絡担当官から郵便物を";
		mes "貰ってくるだけです。";
		next;
		mes "[ロイ]";
		mes "特に極秘文書でもないので";
		mes "あなたにも頼めます。";
		mes "郵便物ひとつ持ってくることくらい";
		mes "あなたには簡単でしょう？";
		next;
		if(select("私に任せて","いやです") == 2) {
			mes "[ロイ]";
			mes "うわあ、事情を聞いといて断るとは。";
			mes "……まあ、そうは言っても……";
			mes "どうせあなたはまた来るはず！";
			next;
			mes "[ロイ]";
			mes "ふふふ、私は知っています。";
			mes "こんな無理難題に";
			mes "私が選ばれたのは、";
			mes "目に見えない大きな力の";
			mes "影響だということを!!!";
			close;
		}
		mes "[ロイ]";
		mes "ありがとうございます！";
		mes "スプレンディッド前線基地に行って、";
		mes "定期連絡担当と会って！";
		next;
		mes "[ロイ]";
		mes "その重要でもなんでもない、";
		mes "誰かのラブレターかも知れない！";
		mes "郵便物を受け取って、";
		mes "私の所まで持ってきてください。";
		setquest 7419;
		next;
		mes "[ロイ]";
		mes "私はここであなたがその郵便物を";
		mes "持って戻るのを、じっと待ち続けます。";
		close;
	case 6:
		mes "[ロイ]";
		mes "エクラージュガードの話だと";
		mes "マヨル・ジュンがあなたに会いたがって";
		mes "いるようですけど？";
		mes "ここにいても大丈夫ですか？";
		close;
	case 7:
		mes "[ロイ]";
		mes "結局は私がやる仕事は伝令ではなく、";
		mes "郵便配達です。";
		mes "……そんなものですよ。";
		close;
	default:
		if(ECL_3QUE >= 8) {
			if(checkquest(7431)) {
				if(checkquest(7431) & 0x2) {
					mes "[ロイ]";
					mes "そろそろ郵便箱が";
					mes "いっぱいになる頃かな。";
					delquest 7431;
					close;
				}
				mes "[ロイ]";
				mes "なぜあんなに無駄な手紙が多いのか。";
				mes "そして遠距離ラブレターの割合の高さ！";
				mes "どうして伝令の私が";
				mes "他人の恋愛に協力してあげなければ";
				mes "いけないんでしょうか？";
				next;
				mes "[ロイ]";
				mes "立派な軍人になろうと";
				mes "思っていたのに……";
				mes "前線基地を志願したのに";
				mes "伝令担当になって、";
				mes "そして今は……";
				next;
				mes "[ロイ]";
				mes "あ、そういえば、";
				mes "また時間が経てば";
				mes "ラブレターがたまるはずです。";
				next;
				mes "[ロイ]";
				mes "それを持って来るのはあなた、";
				mes "それを配るのは私。";
				mes "私たちもカップルですね！";
				mes "ラブレター配達カップル！";
				next;
				mes "‐ロイの表情が寂しく見える‐";
				close;
			}
			if(checkquest(7430)) {
				if(countitem(6552) < 1) {
					mes "[ロイ]";
					mes "スプレンディッド前線基地にいる";
					mes "定期連絡官から郵便物を";
					mes "受け取ってきてください。";
					mes "簡単でしょう？";
					close;
				}
				mes "[ロイ]";
				mes "うむ……相変わらずどうでもいい手紙に";
				mes "獣の角のような物が入っていますね。";
				mes "ご苦労様でした。";
				next;
				mes "[ロイ]";
				mes "こうなってしまった以上は";
				mes "私がエクラージュの配達員になるか。";
				mes "……定期的に一緒に働きましょう。";
				mes "どうですか？";
				next;
				if(checkitemblank() == 0) {
					mes "[ロイ]";
					mes "あれ？";
					mes "私の誠意を示そうと思いましたが";
					mes "持ち物が多すぎるようです。";
					mes "持ち物を整理してから、";
					mes "もう一度話しかけてください。";
					close;
				}
				mes "[ロイ]";
				mes "お願いです、ぜひ次も私と一緒に";
				mes "働くと言ってください。";
				mes "これは私からの小さな誠意です。";
				mes "では、お待ちしております！";
				delitem 6552,1;
				chgquest 7430,7431;
				getitem 6081,1;
				close;
			}
			mes "[ロイ]";
			mes "あの、すみませんが今日も";
			mes "行って来ていただけますか？";
			mes "スプレンディッドに、";
			mes "郵便物を取りに……";
			next;
			if(select("わかった","今日は無理") == 2) {
				mes "[ロイ]";
				mes "はあぁ……";
				mes "そこまで簡単に断られるとは";
				mes "思ってもいませんでした……。";
				close;
			}
			mes "[ロイ]";
			mes "では、よろしくお願いします。";
			mes "定期連絡官から郵便物を";
			mes "受け取ってきてください。";
			next;
			mes "[ロイ]";
			mes "エクラージュから送る郵便物は、";
			mes "補給物資と一緒に届けています。";
			mes "ただ、向こうからこちらに";
			mes "送るのが難しかくて……。";
			next;
			mes "[ロイ]";
			mes "定期的にやらなければならないので、";
			mes "あなたが協力してくれて";
			mes "大変助かっています。";
			mes "では、私はここで待っていますね。";
			setquest 7430;
			close;
		}
		mes "[ロイ]";
		mes "モーラまでは行ける。";
		mes "だけど、霧の森はどうすればいい？";
		mes "私ひとりで……";
		next;
		mes "[ロイ]";
		mes "あっ……すみません。";
		mes "ただの一人言です。";
		mes "気にしないでください。";
		close;
	}
}

splendide.gat,267,368,3	script	定期連絡官	446,{
	if(ECL_3QUE >= 6) {
		if(countitem(6552) > 0) {
			mes "[定期連絡官]";
			mes "では、今回もよろしくお願いします。";
			mes "ロイに渡してください。";
			close;
		}
		if(checkquest(7430)) {
			mes "[定期連絡官]";
			mes "今日も郵便物を取りに来たんですか？";
			mes "ちょうどひと箱分集まったところ";
			mes "なんですよ。";
			next;
			if(select("郵便物を受け取る","受け取らない") == 2) {
				mes "[定期連絡官]";
				mes "あ……そうですか。";
				mes "残念ですね。";
				mes "まあ……しょうがないですね。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "[定期連絡官]";
				mes "おや？";
				mes "アイテムの種類数が多すぎる";
				mes "ようですよ。";
				mes "種類数を減らしてから";
				mes "もう一度話しかけてください。";
				close;
			}
			mes "[定期連絡官]";
			mes "では受け取ってください。";
			mes "基地内のみんながとても喜んでいます。";
			getitem 6552,1;
			next;
			mes "[定期連絡官]";
			mes "途中で重いからといって、";
			mes "捨てたりしないでくださいね！";
			close;
		}
		mes "[定期連絡官]";
		mes "エクラージュからこちらに来る";
		mes "郵便物は、補給物資と一緒に";
		mes "届いています。";
		mes "ただ、ここから向こうに送ることが";
		mes "難しかったんです。";
		next;
		mes "[定期連絡官]";
		mes "重要なものはもちろん優先的に";
		mes "届けられるのですが、私的なものは";
		mes "ないがしろにされがちで……";
		mes "あなたのおかげで";
		mes "それが解決できて助かっています。";
		close;
	}
	if(ECL_3QUE_sub & 0x4) {
		mes "[定期連絡官]";
		mes "私たちは霧の森を通れなくて……";
		mes "亀裂のせいで道は途絶えていますし、";
		mes "本当に大変です。";
		close;
	}
	if(countitem(6552) > 0) {
		mes "[定期連絡官]";
		mes "その箱はロイに渡してください。";
		mes "よろしくお願いします。";
		close;
	}
	mes "[定期連絡官]";
	mes "おや、こんにちは。";
	mes "ふふふ……どうです、上手いでしょう？";
	mes "最近人間の方と会う機会が増えたので、";
	mes "頑張って言葉を覚えたんですよ。";
	mes "言葉が通じないと不便ですからね。";
	next;
	if(checkquest(7419)) {
		mes "[定期連絡官]";
		mes "あ、エクラージュから来たのですか？";
		mes "ん？　ロイ？";
		mes "ああ、そういうことですか。";
		mes "待っていましたよ。";
		next;
		if(checkitemblank() == 0) {
			mes "[定期連絡官]";
			mes "おや？";
			mes "アイテムの種類数が多すぎる";
			mes "ようですよ。";
			mes "種類数を減らしてから";
			mes "もう一度話しかけてください。";
			close;
		}
		mes "[定期連絡官]";
		mes "ここに来るのは難しいだろうなと";
		mes "思っていたんですよ。";
		mes "あなたが代わりに来てくれて";
		mes "助かりました。";
		mes "ロイにこの箱を渡してください。";
		getitem 6552,1;
		next;
		mes "[定期連絡官]";
		mes "まあ、個人的な手紙が大半ですが。";
		mes "よろしくお願いします。";
		close;
	}
	mes "[定期連絡官]";
	mes "エクラージュには行ってみましたか？";
	mes "モーラまで行ったならエクラージュも";
	mes "訪問してみてください。";
	mes "本当に美しいところです。";
	close;
}

eclage.gat,274,294,5	script	話中のラフィネ#tl01	436,3,3,{
	if(ECL_3QUE >= 9) {
		mes "[ラフィネ女性]";
		mes "あああ、私は何も話していないよ！";
		mes "確かに私はお喋りだけど、";
		mes "何でも話すわけではないの。";
		next;
		mes "[ラフィネ女性]";
		mes "だから私から何かを聞き出そうとは";
		mes "思わないでよ、異邦人！";
		close;
	}
	mes "‐ラフィネの男女が何か話している。";
	mes "　しかし、こちらを意識しているようで";
	mes "　すぐに口を閉じた。";
	mes "　会話のジャマをしたようだ‐";
	close;
OnTouch:
	if(ECL_3QUE == 8 && !checkquest(7426)) {
		mes "‐ラフィネの男女が話している。";
		mes "　声をひそめてはいるが、";
		mes "　感情が高ぶっているためか、";
		mes "　話している内容が聞こえてくる‐";
		next;
		emotion 6,"話中のラフィネ#tl01";
		mes "[ラフィネ女性]";
		mes "どうしてそんな、落ち着いて";
		mes "いられるのよ！";
		mes "私たちはもっと、神経質なくらい、";
		mes "今のマヨルに注意を払わなくては";
		mes "いけないはずよ！";
		next;
		mes "‐ラフィネの男女は、";
		mes "　カルデュイについて";
		mes "　話しているようだ‐";
		next;
		mes "[ラフィネ男性]";
		mes "だーかーらー！";
		mes "王が変わってから今まで、";
		mes "何ともなかっただろ？";
		mes "それなのに、なんで急にそんなに";
		mes "不安になっているのかが";
		mes "わからないって言ってるんだよ。";
		next;
		mes "[ラフィネ女性]";
		mes "最近、異邦人と頻繁に会っている";
		mes "らしいじゃない?!";
		mes "きっと何か企んでいるのよ……";
		next;
		emotion 54,"エクラージュ住民#tl02";
		mes "[ラフィネ男性]";
		mes "はぁ……思い込みが激しすぎ……";
		mes "異種族との接見なんて、";
		mes "今までのマヨル様だって";
		mes "してきたじゃないか。";
		next;
		emotion 7,"話中のラフィネ#tl01";
		mes "[ラフィネ女性]";
		mes "あなたって、本当にバカね。";
		mes "アールブヘイムの別種族と会うのと、";
		mes "ミッドガルドの種族と会うのとでは、";
		mes "わけが違うでしょ?!";
		next;
		mes "[ラフィネ男性]";
		mes "そんなもんかねぇ。";
		next;
		emotion 6,"話中のラフィネ#tl01";
		mes "[ラフィネ女性]";
		mes "そんなもんなの！";
		mes "ああ、暴君の再来よ……";
		next;
		mes "[ラフィネ男性]";
		mes "……セネスのように";
		mes "暴政しているわけでもないのに……";
		next;
		mes "[ラフィネ女性]";
		mes "してからじゃ遅いでしょ！";
		mes "かなり昔のこととはいえ、";
		mes "また同じことにならないとは";
		mes "言い切れないじゃない！";
		next;
		mes "[ラフィネ男性]";
		mes "それはそうだけど……";
		next;
		mes "[ラフィネ女性]";
		mes "セネスの暴政は……";
		mes "実際に私が経験したわけじゃないけど、";
		mes "話で聞くだけで恐ろしくて……";
		next;
		mes "[ラフィネ女性]";
		mes "その時代に私がいなかったのが";
		mes "良かったと思うほどだもの。";
		mes "やっぱりマヨルは……";
		mes "完璧じゃないとね？";
		next;
		mes "[ラフィネ男性]";
		mes "それでもやっぱり、";
		mes "新しいマヨルがそうなると";
		mes "決まったわけじゃない。";
		mes "それに君も、新しいマヨルが誕生して";
		mes "良かったと思っているんだろう？";
		next;
		mes "[ラフィネ女性]";
		mes "まあ、そう……だけど……";
		mes "どうしてもアレが……";
		mes "アレさえなければ、特に気にすることも";
		mes "ないのに……";
		next;
		mes "‐興味深く聞いていたことが";
		mes "　ラフィネの男性に気づかれた‐";
		next;
		mes "[ラフィネ男性]";
		mes "……そのくらいにしなよ。";
		mes "異邦人に聞こえるよ。";
		next;
		if(select("すでに聞こえたけど、もう少し詳しく教えて","何の話だった？") == 1) {
			emotion 4,"エクラージュ住民#tl02";
			mes "[ラフィネ男性]";
			mes "いや、それは困ります。 ";
			mes "ははは……";
			mes "これは私たち種族の問題です。";
			next;
		}
		mes "[ラフィネ女性]";
		mes "異種族の人が知る必要のない話なの。";
		mes "人の話なんかに興味を持たずに";
		mes "自分のことを気にしなさい。";
		next;
		mes "‐マヨルと暴君？";
		mes "　セネスとは何だ？";
		mes "　とにかく現在のマヨルである";
		mes "　カルデュイについて、とても";
		mes "　不安に思っているようだ‐";
		next;
		setquest 7425;
		if(checkquest(7423) && checkquest(7424) && checkquest(7425) && checkquest(7426)) {
			mes "‐理由については、";
			mes "　カルデュイに直接聞いて";
			mes "　みるのが早そうだ‐";
			set ECL_3QUE,9;
			setquest 7427;
			delquest 7423;
			delquest 7424;
			delquest 7425;
			delquest 7426;
			delquest 72253;
			close;
		}
		mes "‐他の人たちからもっと話を";
		mes "　聞いて見よう‐";
		close;
	}
	end;
}

eclage.gat,275,294,3	script	エクラージュ住民#tl02	445,{
	switch(ECL_3QUE) {
	case 8:
		if(checkquest(7426)) {
			mes "[ラフィネ男性]";
			mes "異種族のことに";
			mes "あまり関与しないことです。";
			mes "国家に関する事柄なら特に。";
			next;
			mes "‐他の人たちからもっと話を";
			mes "　聞いて見よう‐";
			close;
		}
		mes "‐ラフィネの男女が話している。";
		mes "　声をひそめてはいるが、";
		mes "　感情が高ぶっているためか、";
		mes "　話している内容が聞こえてくる‐";
		next;
		emotion 6,"話中のラフィネ#tl01";
		mes "[ラフィネ女性]";
		mes "どうしてそんな、落ち着いて";
		mes "いられるのよ！";
		mes "私たちはもっと、神経質なくらい、";
		mes "今のマヨルに注意を払わなくては";
		mes "いけないはずよ！";
		next;
		mes "‐ラフィネの男女は、";
		mes "　カルデュイについて";
		mes "　話しているようだ‐";
		next;
		mes "[ラフィネ男性]";
		mes "だーかーらー！";
		mes "王が変わってから今まで、";
		mes "何ともなかっただろ？";
		mes "それなのに、なんで急にそんなに";
		mes "不安になっているのかが";
		mes "わからないって言ってるんだよ。";
		next;
		mes "[ラフィネ女性]";
		mes "最近、異邦人と頻繁に会っている";
		mes "らしいじゃない?!";
		mes "きっと何か企んでいるのよ……";
		next;
		emotion 54,"エクラージュ住民#tl02";
		mes "[ラフィネ男性]";
		mes "はぁ……思い込みが激しすぎ……";
		mes "異種族との接見なんて、";
		mes "今までのマヨル様だって";
		mes "してきたじゃないか。";
		next;
		emotion 7,"話中のラフィネ#tl01";
		mes "[ラフィネ女性]";
		mes "あなたって、本当にバカね。";
		mes "アールブヘイムの別種族と会うのと、";
		mes "ミッドガルドの種族と会うのとでは、";
		mes "わけが違うでしょ?!";
		next;
		mes "[ラフィネ男性]";
		mes "そんなもんかねぇ。";
		next;
		emotion 6,"話中のラフィネ#tl01";
		mes "[ラフィネ女性]";
		mes "そんなもんなの！";
		mes "ああ、暴君の再来よ……";
		next;
		mes "[ラフィネ男性]";
		mes "……セネスのように";
		mes "暴政しているわけでもないのに……";
		next;
		mes "[ラフィネ女性]";
		mes "してからじゃ遅いでしょ！";
		mes "かなり昔のこととはいえ、";
		mes "また同じことにならないとは";
		mes "言い切れないじゃない！";
		next;
		mes "[ラフィネ男性]";
		mes "それはそうだけど……";
		next;
		mes "[ラフィネ女性]";
		mes "セネスの暴政は……";
		mes "実際に私が経験したわけじゃないけど、";
		mes "話で聞くだけで恐ろしくて……";
		next;
		mes "[ラフィネ女性]";
		mes "その時代に私がいなかったのが";
		mes "良かったと思うほどだもの。";
		mes "やっぱりマヨルは……";
		mes "完璧じゃないとね？";
		next;
		mes "[ラフィネ男性]";
		mes "それでもやっぱり、";
		mes "新しいマヨルがそうなると";
		mes "決まったわけじゃない。";
		mes "それに君も、新しいマヨルが誕生して";
		mes "良かったと思っているんだろう？";
		next;
		mes "[ラフィネ女性]";
		mes "まあ、そう……だけど……";
		mes "どうしてもアレが……";
		mes "アレさえなければ、特に気にすることも";
		mes "ないのに……";
		next;
		mes "‐興味深く聞いていたことが";
		mes "　ラフィネの男性に気づかれた‐";
		next;
		mes "[ラフィネ男性]";
		mes "……そのくらいにしなよ。";
		mes "異邦人に聞こえるよ。";
		next;
		if(select("すでに聞こえたけど、もう少し詳しく教えて","何の話だった？") == 1) {
			emotion 4,"エクラージュ住民#tl02";
			mes "[ラフィネ男性]";
			mes "いや、それは困ります。 ";
			mes "ははは……";
			mes "これは私たち種族の問題です。";
			next;
		}
		mes "[ラフィネ女性]";
		mes "異種族の人が知る必要のない話なの。";
		mes "人の話なんかに興味を持たずに";
		mes "自分のことを気にしなさい。";
		next;
		mes "‐マヨルと暴君？";
		mes "　セネスとは何だ？";
		mes "　とにかく現在のマヨルである";
		mes "　カルデュイについて、とても";
		mes "　不安に思っているようだ‐";
		next;
		setquest 7425;
		if(checkquest(7423) && checkquest(7424) && checkquest(7425) && checkquest(7426)) {
			mes "‐理由については、";
			mes "　カルデュイに直接聞いて";
			mes "　みるのが早そうだ‐";
			set ECL_3QUE,9;
			setquest 7427;
			delquest 7423;
			delquest 7424;
			delquest 7425;
			delquest 7426;
			delquest 72253;
			close;
		}
		mes "‐他の人たちからもっと話を";
		mes "　聞いて見よう‐";
		close;
	case 9:
		mes "[ラフィネ男性]";
		mes "異種族のことに";
		mes "あまり関与しないことです。";
		mes "国家に関する事柄なら特に。";
		close;
	default:
		mes "[ラフィネ男性]";
		mes "エクラージュを訪れたお客様ですね。";
		mes "エクラージュを楽しんでくださいね。";
		close;
	}
}

ecl_in03.gat,244,57,5	script	休憩中のラフィネ	440,3,3,{
	if(ECL_3QUE >= 9) {
		mes "[休憩中のラフィネ]";
		mes "異種族の内政に、";
		mes "あまりにも興味を持ち過ぎでは";
		mes "ありませんか。";
		close;
	}
	mes "‐ラフィネ2人が";
	mes "　何かを話している。";
	mes "　1人は仕事をしているようだ。";
	mes "　話しかけられるのを";
	mes "　相当嫌がっている‐";
	next;
	mes "‐こちらに気づくと";
	mes "　あっちに行けと";
	mes "　視線で指示された‐";
	close;
OnTouch:
	if(ECL_3QUE == 8 && !checkquest(7426)) {
		mes "[休憩中のラフィネ]";
		mes "どうしてこんなに悪いことが";
		mes "立て続けに起きるのかな……。";
		next;
		mes "[休憩中のラフィネ]";
		mes "マヨルはイグドラシルとの疎通が";
		mes "切れてしまって、そのせいで";
		mes "継承することになった。";
		mes "スプレンディッドへの道には";
		mes "亀裂ができてしまったし……。";
		next;
		mes "[休憩中のラフィネ]";
		mes "話によると、亀裂は魔王が";
		mes "作った物なんだって？";
		mes "サファも頭を悩ませているらしいね。";
		mes "それに新しく継承されたマヨルは";
		mes "何と言っても……アレだしな……";
		next;
		mes "‐アレ？";
		mes "　アレとは何だろう？‐";
		next;
		mes "[休憩中のラフィネ]";
		mes "これはもしかして世界が滅びる";
		mes "前触れではないのか？";
		mes "それとも、以前にもこんなこと";
		mes "あったのか？";
		mes "君はどう思う？";
		next;
		mes "[公務中のラフィネ]";
		mes "……仕事しているんだから";
		mes "ジャマするなよ。";
		mes "ただでさえ亀裂のせいで";
		mes "スプレンディッドへの補給に";
		mes "問題が発生していて頭が痛いんだよ。";
		next;
		mes "[休憩中のラフィネ]";
		mes "あ、そういえばミッドガルドから";
		mes "来たという人間のことなんだけど。";
		mes "マヨルは何を考えているか";
		mes "分からないけど、その人間を呼んで";
		mes "色々とやらせているらしいよ。";
		next;
		mes "[休憩中のラフィネ]";
		mes "今回のマヨルは例外的に若く、";
		mes "そして……アレだし……";
		mes "ああ、どうして異邦人と頻繁に";
		mes "会っているんだろう……";
		mes "何を考えているのかな？";
		next;
		mes "[公務中のラフィネ]";
		mes "その異邦人とは、今私たちの話を";
		mes "立ち聞きしているあいつのことだな。";
		mes "マヨルが最近頻繁に会っている人物だ。";
		next;
		mes "[休憩中のラフィネ]";
		mes "うわっ!?";
		mes "いつからここにいたんですか!!";
		mes "ここは外部の人が歩き回っては";
		mes "いけない場所です!!";
		next;
		menu "アレというのは何ですか？",-;
		mes "[公務中のラフィネ]";
		mes "あなたが知る必要はありません。";
		mes "どうでもいい話なので";
		mes "気にしないでください。";
		mes "さあ、お客様はそろそろ";
		mes "ここから出てください。";
		next;
		setquest 7426;
		if(checkquest(7423) && checkquest(7424) && checkquest(7425) && checkquest(7426)) {
			// 未調査
			mes "‐理由については、";
			mes "　カルデュイに直接聞いて";
			mes "　みるのが早そうだ‐";
			set ECL_3QUE,9;
			setquest 7427;
			delquest 7423;
			delquest 7424;
			delquest 7425;
			delquest 7426;
			delquest 72253;
			close;
		}
		mes "‐ラフィネの話を興味深く聞いた。";
		mes "　アレとは何なのか……";
		mes "　他のラフィネたちから";
		mes "　もっと話を聞いて見よう‐";
		close;
	}
	end;
}

ecl_in03.gat,245,54,2	script	公務中のラフィネ	439,{
	switch(ECL_3QUE) {
	case 8:
		if(!checkquest(7426)) {
			mes "[休憩中のラフィネ]";
			mes "どうしてこんなに悪いことが";
			mes "立て続けに起きるのかな……。";
			next;
			mes "[休憩中のラフィネ]";
			mes "マヨルはイグドラシルとの疎通が";
			mes "切れてしまって、そのせいで";
			mes "継承することになった。";
			mes "スプレンディッドへの道には";
			mes "亀裂ができてしまったし……。";
			next;
			mes "[休憩中のラフィネ]";
			mes "話によると、亀裂は魔王が";
			mes "作った物なんだって？";
			mes "サファも頭を悩ませているらしいね。";
			mes "それに新しく継承されたマヨルは";
			mes "何と言っても……アレだしな……";
			next;
			mes "‐アレ？";
			mes "　アレとは何だろう？‐";
			next;
			mes "[休憩中のラフィネ]";
			mes "これはもしかして世界が滅びる";
			mes "前触れではないのか？";
			mes "それとも、以前にもこんなこと";
			mes "あったのか？";
			mes "君はどう思う？";
			next;
			mes "[公務中のラフィネ]";
			mes "……仕事しているんだから";
			mes "ジャマするなよ。";
			mes "ただでさえ亀裂のせいで";
			mes "スプレンディッドへの補給に";
			mes "問題が発生していて頭が痛いんだよ。";
			next;
			mes "[休憩中のラフィネ]";
			mes "あ、そういえばミッドガルドから";
			mes "来たという人間のことなんだけど。";
			mes "マヨルは何を考えているか";
			mes "分からないけど、その人間を呼んで";
			mes "色々とやらせているらしいよ。";
			next;
			mes "[休憩中のラフィネ]";
			mes "今回のマヨルは例外的に若く、";
			mes "そして……アレだし……";
			mes "ああ、どうして異邦人と頻繁に";
			mes "会っているんだろう……";
			mes "何を考えているのかな？";
			next;
			mes "[公務中のラフィネ]";
			mes "その異邦人とは、今私たちの話を";
			mes "立ち聞きしているあいつのことだな。";
			mes "マヨルが最近頻繁に会っている人物だ。";
			next;
			mes "[休憩中のラフィネ]";
			mes "うわっ!?";
			mes "いつからここにいたんですか!!";
			mes "ここは外部の人が歩き回っては";
			mes "いけない場所です!!";
			next;
			menu "アレというのは何ですか？",-;
			mes "[公務中のラフィネ]";
			mes "あなたが知る必要はありません。";
			mes "どうでもいい話なので";
			mes "気にしないでください。";
			mes "さあ、お客様はそろそろ";
			mes "ここから出てください。";
			next;
			setquest 7426;
			if(checkquest(7423) && checkquest(7424) && checkquest(7425) && checkquest(7426)) {
				// 未調査
				mes "‐理由については、";
				mes "　カルデュイに直接聞いて";
				mes "　みるのが早そうだ‐";
				set ECL_3QUE,9;
				setquest 7427;
				delquest 7423;
				delquest 7424;
				delquest 7425;
				delquest 7426;
				delquest 72253;
				close;
			}
			mes "‐ラフィネの話を興味深く聞いた。";
			mes "　アレとは何なのか……";
			mes "　他のラフィネたちから";
			mes "　もっと話を聞いて見よう‐";
			close;
		}
		end;
	case 9:
		mes "[勤務中のラフィネ]";
		mes "私たちの王について知りたいんですか？";
		mes "けれど人間の王と私たちのマヨルは";
		mes "比較が不可能です。";
		mes "人間側の概念を適用して";
		mes "考えないでください。";
		next;
		mes "[勤務中のラフィネ]";
		mes "それから……これ以上";
		mes "異種族の内政に好奇心を";
		mes "持たないでほしいです。";
		mes "何が言いたいか分かりましたか？";
		close;
	default:
		mes "[勤務中のラフィネ]";
		mes "ここは公務をするための場所です。";
		mes "出入を控えてください。";
		close;
	}
}

eclage.gat,280,290,0	script	#ヒシエ01	139,3,3,{
	if(ECL_3QUE == 19) {
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "目的地はこの近くだ。";
		mes "研究用のヤイがある場所を、";
		mes "君の持っている地図にも";
		mes "記してやる。";
		viewpoint 1,307,237,0,0x0A82FF;
		next;
		mes "[ヒシエ]";
		mes "実験材料は持って来たか？";
		mes "シナイムに頼まれた風に、";
		mes "自然に接近するのが大事だ。";
		mes "さあ、行こう！";
		close2;
		cutin "hisie01",255;
		end;
	}
	end;
}

eclage.gat,307,237,0	script	研究用のヤイ#tllb	844,{
	if(ECL_3QUE == 19) {
		if(countitem(6560) < 10 || countitem(6561) < 10) {
			cutin "hisie01",0;
			mes "[ヒシエ]";
			mes "ほこりの塊と落ち葉のしおりの";
			mes "数が足りないんじゃないか？";
			mes "早く準備しろ。";
			mes "それがあれば怪しまれなく済む。";
			close2;
			cutin "hisie01",255;
			end;
		}
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "このヤイだ。";
		mes "うまくやってくれよ。";
		mes "建物の外に出るように";
		mes "自然に誘導するんだ。";
		next;
		cutin "avn_labo",4;
		mes "‐ヒシエが身を隠したのを確認し";
		mes "　ヤイの扉を叩いた‐";
		next;
		mes "‐数回叩くと、扉の向こう側に";
		mes "　人の気配がし、";
		mes "　扉に設置されたのぞき窓が開いた‐";
		next;
		cutin "avn_labo",255;
		mes "[中から聞こえる声]";
		mes "……誰だ？";
		mes "人間？　なのか？";
		mes "ほほう、珍しい。";
		next;
		cutin "avant01",1;
		mes "‐ヤイの扉が開き、中から金髪の";
		mes "　上級ラフィネが出てきた。";
		mes "　彼は興味深げにこちらの全身を";
		mes "　眺め始めた‐";
		next;
		mes "[金髪の魔学者]";
		mes "ふん、人間……";
		mes "やはり大したことのない種族だな。";
		mes "しかしなぜ人間が訪ねてきた？";
		mes "つまらないことで来たのであれば";
		mes "覚悟した方がいいぞ。";
		next;
		menu "宅配を……",-,"シナイムの依頼で……",-;
		mes "[金髪の魔学者]";
		mes "何？　シナイムに頼まれたのか？";
		mes "ほこりの塊と落ち葉のしおりか。";
		mes "自分で持ってこないとは、";
		mes "回りくどいことを……";
		next;
		mes "[金髪の魔学者]";
		mes "おい、人間。";
		mes "こんなものより、";
		mes "お前のほうに興味がある。";
		mes "どうだ？";
		mes "私の実験材料にならないか？";
		next;
		cutin "avant02",1;
		mes "[金髪の魔学者]";
		mes "報酬は苦痛のない安息だ。";
		mes "良い条件だろ？";
		mes "……ククク";
		next;
		mes "[金髪の魔学者]";
		mes "いい表情だな";
		mes "実験体になる気がないなら";
		mes "二度とここには近寄るな。";
		next;
		cutin "avant01",255;
		mes "‐魔学者はあざ笑うような表情で";
		mes "　実験材料を奪ってヤイの中に";
		mes "　戻ってしまった。";
		mes "　彼がヤイの中に入った後、";
		mes "　木の後ろからヒシエが姿を現した‐";
		next;
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "間違いない……";
		mes "あいつはエイヴァントだ。";
		mes "髪の毛の色は変わっていたが、";
		mes "あの憎たらしい話し方は";
		mes "変わっていなかった。";
		next;
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "シナイムはあいつのことを";
		mes "知っていて支援しているのか？";
		mes "とにかく、まずはやつの居場所を";
		mes "カルに知らせることにしよう。";
		next;
		cutin "hisie01",255;
		mes "‐研究用のヤイにいたのは、";
		mes "　魔学者エイヴァントだった。";
		mes "　カルデュイに報告しよう‐";
		set ECL_3QUE,20;
		delitem 6561,10;
		delitem 6560,10;
		chgquest 7441,7442;
		close;
	}
	if(ECL_3QUE == 20) {
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "奴が気づく前に";
		mes "急いでこの場から離れよう。";
		mes "カルにこの事実を知らせるのが先だ。";
		next;
		cutin "hisie01",255;
		mes "‐研究用のヤイにいたのは、";
		mes "　魔学者エイヴァントだった。";
		mes "　カルデュイに報告しよう‐";
		close;
	}
	if(ECL_3QUE == 21) {
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "エイヴァントのヤイだから";
		mes "何か仕掛けが施されているかも";
		mes "しれない。";
		mes "様子をみてから入ることにしよう。";
		next;
		if(select("今すぐ入る","もう少し周囲の様子をみる。") == 2) {
			cutin "hisie03",0;
			mes "[ヒシエ]";
			mes "何か魔法的な仕掛けを感じるな……";
			mes "やはり、研究が行われているのは";
			mes "このヤイではなさそうだ。";
			mes "たぶん、このヤイから別の空間に";
			mes "繋がっているのだろう。";
			next;
			cutin "hisie01",0;
			mes "[ヒシエ]";
			mes "慎重に進もう。";
			close2;
			cutin "hisie01",255;
			end;
		}
		if(getnpctimer(1,"#tltimer")) {
			cutin "hisie01",0;
			mes "[ヒシエ]";
			mes "静かに。";
			mes "中から人の気配が感じられる。";
			mes "もう少し待って、";
			mes "奴が席をはずした時に入ろう。";
			next;
			mes "‐他のプレイヤーが使用中です。";
			mes "　しばらくまってから";
			mes "　お試しください‐";
			close2;
			cutin "hisie01",255;
			end;
		}
		cutin "hisie01",255;
		warp "que_avan01.gat",26,26;
		end;
	}
	if(ECL_3QUE >= 22) {
		cutin "avn_labo",4;
		mes "‐魔学者の秘密研究施設に";
		mes "　繋がっているヤイだ。";
		mes "　魔学者エイヴァントは";
		mes "　連行されてここにはいない‐";
		close2;
		cutin "avn_labo",255;
		end;
	}
	cutin "avn_labo",4;
	mes "‐ラフィネたちが";
	mes "　住んでいるヤイだ。";
	mes "　扉が閉まっていて";
	mes "　入ることができない‐";
	close2;
	cutin "avn_labo",255;
	end;
OnInit:
	waitingroom "研究用のヤイ",0;
	end;
}

que_avan01.gat,26,26,0	script	#tltimer	139,1,1,{
	mes "‐確かに小さなヤイに入ったのに、";
	mes "　目まいの後に気が付くと";
	mes "　大きな空間が現れた‐";
	hideonnpc "#tltimer";
	hideonnpc "ヒシエ#tlhunt";
	hideonnpc "魔学者エイヴァント#tlac";
	hideonnpc "エイヴァントの召喚物#01";
	hideonnpc "エイヴァントの召喚物#02";
	hideonnpc "エイヴァントの召喚物#03";
	hideonnpc "エイヴァントの召喚物#04";
	initnpctimer;
	next;
	cutin "hisie01",0;
	mes "[ヒシエ]";
	mes "平凡なヤイを秘密研究室と";
	mes "繋げていたようだ。";
	mes "うまく作ってあるな……。";
	mes "とにかく調べてみよう。";
	hideoffnpc "ヒシエ#tlspt";
	close2;
	cutin "hisie01",255;
	end;
OnTimer5000:
	announce "お帰りなさい、エイヴァント様……使用者認証待機時間5分です。",0x9,0xa8a8a8;
	end;
OnTimer300000:
	announce "警告 : 長時間認証を行っていなかったので関係者以外の出入禁止魔法が自動で発動します。",0x9,0xa8a8a8;
	end;
OnTimer303000:
	announce "研究所内部に空間の歪みが発生しました。",0x9,0x7b68ee;
	end;
OnTimer306000:
	stopnpctimer;
	mapwarp "que_avan01.gat","eclage.gat",265,275;
	end;
}

que_avan01.gat,18,38,0	script	デスク#tl01	844,{
	if(ECL_3QUE == 22) {
		mes "‐エイヴァントの研究資料は";
		mes "　すでに手に入れた。";
		mes "　デスクにこれ以上の用はない‐";
		close;
	}
	if(!checkquest(72278)) {
		mes "‐各種実験道具と資料が";
		mes "　置かれているデスクだ。";
		mes "　どうする？‐";
		cutin "avn_desk01",4;
		next;
		if(select("デスクを調べる","無視する") == 2) {
			mes "‐他の場所を調べることにした‐";
			close2;
			cutin "avn_desk03",255;
			end;
		}
		mes "‐デスク上に広がっていたものを";
		mes "　大体整理した‐";
		cutin "avn_desk02",4;
		set '@flag,checkquest(72273);
		next;
		while(1) {
			if(!'@flag)
				cutin "avn_desk02",4;
			else
				cutin "avn_desk04",4;
			mes "‐何を調べる？‐";
			next;
			switch(select("置いてあった書類を調べる","デスク上の装置を調べる","本棚の本を調べる","試薬を食べてみる","照明装置を調べる")) {
			case 1:
				mes "‐何が書かれているのか、";
				mes "　まったく分からない。";
				mes "　ヒシエに見せよう‐";
				next;
				cutin "hisie01",0;
				mes "[ヒシエ]";
				mes "真理の扉定期発売……";
				mes "……いらないな。";
				next;
				cutin "hisie01",255;
				continue;
			case 2:
				if(!'@flag) {
					mes "‐整理されたデスクの上に";
					mes "　装置らしきものが見える。";
					mes "　装置を操作できるヒントが";
					mes "　何処かにあるはずだ‐";
					next;
					continue;
				}
				mes "‐整理されたデスクの上に";
				mes "　装置らしきものが見える。";
				mes "　中央には小さな数字が";
				mes "　書かれた板がある。";
				mes "　5桁まで入力できるようだ‐";
				next;
				if(select("数字を入力する","他の部分を調べてみる") == 2) {
					mes "‐他の部分を調べてみることにした‐";
					next;
					continue;
				}
				input '@num;
				if('@num != 31425) {
					mes "‐数字が間違ったようだ‐";
					next;
					continue;
				}
				mes "‐数字を入力すると謎の音がした。";
				mes "　開くことができそうだ‐";
				chgquest 72273,72278;
				next;
				break;
			case 3:
				if('@flag) {
					mes "‐本を配置すると、背表紙の紋様が";
					mes "　ひとつの絵になった。";
					mes "　本は左から";
					mes "　^0000FF3巻、1巻、4巻、2巻、5巻^000000";
					mes "　の順番に並んでいる。";
					mes "　何か特別な意味があるのか……？‐";
					cutin "avn_book01",4;
					next;
					continue;
				}
				mes "‐5冊の本が並んでいる。";
				mes "　変わった紋様が気になる‐";
				cutin "avn_book02",4;
				next;
				switch(select("本の配列を変えてみる","考える","やめる")) {
				case 1:
					set '@book,0;
					setarray '@books$,"1番目","2番目","3番目","4番目","5番目";
					for(set '@i,1; '@i<5; set '@i,'@i+1){
						if('@i<=1)
							mes "‐1巻を何番目に配置する？‐";
						else
							mes "‐" +'@i+ "巻は何番目に配置する？‐";
						next;
						set '@menu,select(printarray('@books$))-1;
						if('@i<=3) {
							mes '@i+ "巻を" +'@books$['@menu]+ "に配置した。";
							set '@books$['@menu],"";
						}
						else {
							mes "4巻を" +'@books$['@menu]+ "番目に、";
							set '@books$['@menu],"";
							mes "5巻を" +printarray('@books$)+ "番目に配置した。";
						}
						if(('@i==1 && '@menu==2) || ('@i==2 && '@menu==0) || ('@i==3 && '@menu==3) || ('@i==4 && '@menu==1)) {
							set '@book,'@book+10;
						}
						next;
					}
					if('@book < 40) {
						mes "‐本の配置を変えてみたが、";
						mes "　何の成果もなかった‐";
						cutin "avn_desk02",4;
					} else {
						mes "‐本を配置すると、背表紙の紋様が";
						mes "　ひとつの絵になった。";
						mes "　本は左から";
						mes "　^0000FF3巻、1巻、4巻、2巻、5巻^000000";
						mes "　の順番に並んでいる。";
						mes "　何か特別な意味があるのだろうか？‐";
						setquest 72273;
						set '@flag,1;
						cutin "avn_book01",4;
					}
					next;
					continue;
				case 2:
					mes "‐本をよく観察すると";
					mes "　背表紙の文様が不揃いな事に";
					mes "　気づいた。";
					mes "　背表紙の文様にあわせて";
					mes "　並び替えろという事だろうか‐";
					next;
					switch(rand(1,5)) {
					case 1:
						mes "‐どうやら^FF00001巻は2番目^000000に";
						mes "　配置すると良さそうだ‐";
						break;
					case 2:
						mes "‐どうやら^FF00002巻は4番目^000000に";
						mes "　配置すると良さそうだ‐";
						break;
					case 3:
						mes "‐どうやら^FF00003巻は1番目^000000に";
						mes "　配置すると良さそうだ‐";
						break;
					case 4:
						mes "‐どうやら^FF00004巻は3番目^000000に";
						mes "　配置すると良さそうだ‐";
						break;
					case 5:
						mes "‐どうやら^FF00005巻は5番目^000000に";
						mes "　配置すると良さそうだ‐";
						break;
					}
					next;
					continue;
				case 3:
					mes "‐他の部分を調べてみることにした‐";
					next;
					continue;
				}
			case 4:
				mes "‐机の上に流れている試薬を";
				mes "　指ですくって味を見た。";
				mes "　強烈な痛みが体を襲った‐";
				percentheal -50,0;
				next;
				continue;
			case 5:
				mes "‐平凡な円形の照明装置である。";
				mes "　特別な機能や装置はない‐";
				next;
				continue;
			}
			break;
		}
	}
	mes "‐机の中の秘密空間には";
	mes "　研究資料の一部が入っていた。";
	mes "　内容がわからない。";
	mes "　ヒシエに見せることにした‐";
	cutin "avn_desk03",4;
	next;
	mes "[ヒシエ]";
	mes "何か発見したのか？";
	mes "ん？　これは……";
	mes "母さんの写真だな。";
	mes "奴がどうしてこれを";
	mes "持っているんだ？";
	cutin "hisie01",0;
	next;
	switch(select("美人ですね","この文書を見てください！")) {
	case 1:
		cutin "hisie02",0;
		mes "[ヒシエ]";
		mes "私とカルの髪の毛は";
		mes "母さんから受け継いだんだ。";
		mes "カルにとっては、";
		mes "唯一残っている母さんの";
		mes "痕跡でもある……";
		next;
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "それより隣にあるこの文書は……";
		mes "これが奴の研究資料なのか。";
		mes "どれどれ……";
		mes "む、これは……";
		mes "まさか……信じられない！";
		break;
	case 2:
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "あ、ああ。そうだったな。";
		mes "どれどれ……";
		mes "む、これは……";
		mes "まさか……信じられない！";
		break;
	}
	next;
	mes "[ヒシエ]";
	mes "エイヴァントはこんなものを";
	mes "研究していたのか!?";
	mes "こんなのを何に使うんだ？";
	next;
	menu "何ですか？",-;
	cutin "hisie01",0;
	mes "[ヒシエ]";
	mes "これはオーブについての研究資料だ。";
	mes "エクラージュの象徴であり、";
	mes "一族の魔力が集まっているオーブ！ ";
	mes "オーブの魔力をどうするつもりなんだ？";
	next;
	mes "[ヒシエ]";
	mes "この研究は危険だ。";
	mes "シナイムはこの研究内容を知っていて";
	mes "支援しているのか？";
	mes "早くカルに知らせないと！";
	next;
	cutin "avant01",1;
	mes "[魔学者エイヴァント]";
	mes "いや、それは困る。";
	mes "無礼な奴らだな。";
	mes "身勝手な行動はそこまでだ！";
	hideoffnpc "魔学者エイヴァント#tlac";
	hideoffnpc "エイヴァントの召喚物#01";
	hideoffnpc "エイヴァントの召喚物#02";
	hideoffnpc "エイヴァントの召喚物#03";
	hideoffnpc "エイヴァントの召喚物#04";
	next;
	cutin "hisie01",0;
	mes "[ヒシエ]";
	mes "この研究資料を頼む。";
	mes "エイヴァントは私が捕まえる。";
	next;
	switch(select("いや、ここは私が","ヒシエに任せる")) {
	case 1:
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "……分かった。";
		mes "エイヴァントが呼び出した";
		mes "奴らさえ倒せばいいはずだ。";
		mes "私は後ろから援護する。";
		mes "助けが必要な時は";
		mes "私の近くまで下がるんだ。";
		if(checkitemblank() == 0) {
			next;
			mes "[ヒシエ]";
			mes "ん?!";
			mes "荷物が多すぎて、";
			mes "エイヴァントの研究資料を";
			mes "持てないぞ！";
			mes "持ち物を減らして";
			mes "もう一度話しかけてくれ！";
			close;
			close2;
			cutin "hisie01",255;
			warp "eclage.gat",265,275;
			end;
		}
		getitem 6541,1;
		set ECL_3QUE,22;
		delquest 7443;
		delquest 72278;
		setquest 7444;
		close2;
		donpcevent "#avt管理者::OnStart1";
		cutin "hisie01",255;
		end;
	case 2:
		cutin "hisie04",0;
		mes "[ヒシエ]";
		mes "後から私も行く。";
		mes "資料をカルに渡してくれ！";
		if(checkitemblank() == 0) {
			next;
			mes "[ヒシエ]";
			mes "ん?!";
			mes "荷物が多すぎて、";
			mes "エイヴァントの研究資料を";
			mes "持てないぞ！";
			mes "持ち物を減らして";
			mes "もう一度話しかけてくれ！";
			close2;
			cutin "hisie01",255;
			warp "eclage.gat",265,275;
			end;
		}
		set ECL_3QUE,22;
		delquest 7443;
		delquest 72278;
		setquest 7444;
		getitem 6541,1;
		close2;
		warp "eclage.gat",294,240;
		end;
	}
}

que_avan01.gat,1,1,0	script	#avt管理者	844,{
OnStart1:
	hideonnpc "エイヴァントの召喚物#01";
	hideonnpc "エイヴァントの召喚物#02";
	hideonnpc "エイヴァントの召喚物#03";
	hideonnpc "エイヴァントの召喚物#04";
	monster "que_avan01.gat",22,40,"エイヴァントの召喚物",1198,1,"#avt管理者::OnKilled1";
	monster "que_avan01.gat",29,40,"エイヴァントの召喚物",1198,1,"#avt管理者::OnKilled1";
	monster "que_avan01.gat",16,40,"エイヴァントの召喚物",1198,1,"#avt管理者::OnKilled1";
	monster "que_avan01.gat",29,36,"エイヴァントの召喚物",1198,1,"#avt管理者::OnKilled1";
	monster "que_avan01.gat",29,32,"エイヴァントの召喚物",1198,1,"#avt管理者::OnKilled1";
	end;
OnStart2:
	initnpctimer;
	end;
OnTimer1000:
	misceffect 55,"魔学者エイヴァント#tlac";
	end;
OnTimer2000:
	monster "que_avan01.gat",26,38," ",2337,1,"#avt管理者::OnKilled2";
	end;
OnTimer4000:
	announce "ヒシエ : やばい！",0x9,0x7b68ee;
	end;
OnTimer8000:
	stopnpctimer;
	killmonster "que_avan01.gat","#avt管理者::OnKilled2";
	end;
OnKilled1:
	set '@count,getmapmobs("que_avan01.gat","#avt管理者::OnKilled1");
	if('@count <= 0) {
		announce "ヒシエ : ここまでだ！　エイヴァント！",0x9,0x7b68ee;
		hideonnpc "ヒシエ#tlspt";
		hideoffnpc "ヒシエ#tlhunt";
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "暴れない方がいいぞ。";
		mes "余計なことはするなよ。";
		next;
		cutin "avant02",2;
		mes "[エイヴァント]";
		mes "無断侵入に飽き足らず、";
		mes "今度は拉致か？";
		mes "若い奴らはこれだから……";
		mes "まあ、好きにしろ。";
		next;
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "……何を企んでいる？";
		mes "こんなあっさりと捕まる奴では";
		mes "ないだろう？";
		next;
		cutin "avant02",2;
		mes "[エイヴァント]";
		mes "ククク……";
		mes "久しぶりに息子が";
		mes "会いに来たのが嬉しくてな。";
		next;
		cutin "hisie03",0;
		mes "[ヒシエ]";
		mes "ふざけるな……";
		mes strcharinfo(0)+ "！";
		mes "こいつとこれ以上話す必要は";
		mes "ないだろう？";
		mes "ここからは私が処理するから、";
		mes "君は先に出発してくれ。";
		close2;
		cutin "hisie01",255;
		warp "eclage.gat",294,240;
		end;
	}
	end;
OnKilled2:
	end;
}

que_avan01.gat,26,41,3	script	魔学者エイヴァント#tlac	618,{
	cutin "avant02",1;
	mes "[エイヴァント]";
	mes "私のからだに手をつけるとは";
	mes "死にたくて頭がおかしく";
	mes "なったんだな、若造！";
	mes "願い通りにしてやる!!";
	close2;
	cutin "avant01",255;
	donpcevent "#avt管理者::OnStart2";
	end;
}

que_avan01.gat,22,40,3	script	エイヴァントの召喚物#01	1198,{}
que_avan01.gat,29,40,3	script	エイヴァントの召喚物#02	1198,{}
que_avan01.gat,29,36,3	script	エイヴァントの召喚物#03	1198,{}
que_avan01.gat,29,32,3	script	エイヴァントの召喚物#04	1198,{}

que_avan01.gat,23,34,2	script	ヒシエ#tlspt	623,3,3,{
	if(ECL_3QUE == 22) {
		cutin "hisie01",0;
		mes "[ヒシエ]";
		mes "隠れてこんなものを";
		mes "研究していたとは……";
		close2;
		cutin "hisie01",255;
		end;
	}
	cutin "hisie01",0;
	mes "[ヒシエ]";
	mes "どこかに重要な";
	mes "研究資料があるはずだ。";
	close2;
	cutin "hisie01",255;
	end;
OnTouch:
	if(ECL_3QUE == 22) {
		switch(rand(4)) {
		case 0:
			npcskillsupport 28,1672;
			heal 1672,0;
			break;
		case 1:
			npcskillsupport 28,9999;
			heal 9999,0;
			npcskillsupport 34,0;
			sc_start 10,240000,10;	//SC_BLESSING
			npcskillsupport 29,0;
			sc_start 12,240000,10;	//SC_INCREASEAGI
			break;
		case 2:
			npcskillsupport 34,0;
			sc_start 10,240000,10;	//SC_BLESSING
			break;
		case 3:
			npcskillsupport 29,0;
			sc_start 12,240000,10;	//SC_INCREASEAGI
			break;
		}
	}
	end;
}

que_avan01.gat,25,41,5	script	ヒシエ#tlhunt	623,{}

bif_fild02.gat,311,91,3	script	巨大な花のつぼみ	613,{
	if(ECL_3QUE == 31) {
		mes "‐ラフィネの死体だ。";
		mes "　姿をみると、死亡してから";
		mes "　あまり時間が経っていないようだ‐";
		next;
		mes "‐詳しく調べてみると、";
		mes "　その死体は消えたシナイムだ！";
		mes "　頭と思われる部分に穴が開いている‐";
		next;
		mes "‐穴から流れた血痕が";
		mes "　南の方向に向いている。";
		mes "　何か長い虫のような物が";
		mes "　通ったような跡だ‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ここから南の方向といえば……";
		mes "亀裂だな。";
		mes "……亀裂に逃げたのか。";
		next;
		mes "‐シナイムにとりついていた存在は";
		mes "　亀裂に逃げたようだ‐";
		next;
		mes "‐これ以上得られる情報はない。";
		mes "　この事実を急いでカルデュイに";
		mes "　知らせた方が良さそうだ‐";
		set ECL_3QUE,32;
		chgquest 7452,7453;
		close;
	}
	if(ECL_3QUE == 32) {
		mes "‐軍参謀シナイムの死体だ。";
		mes "　シナイムを支配していた本体は";
		mes "　すでに抜け出している‐";
		close;
	}
	mes "‐巨大な花のつぼみのような";
	mes "　形をしている正体不明の";
	mes "　物体がある‐";
	close;
}

//============================================================
// 美しさの代償クエスト
//- Registry -------------------------------------------------
// ECL_4QUE -> 0～24
//------------------------------------------------------------
eclage.gat,282,255,4	script	ウハリ	620,{
	switch(ECL_4QUE) {
	case 0:
		mes "[ウハリ]";
		mes "…………。";
		next;
		mes "[ウハリ]";
		mes "初めて見る姿……。";
		mes "あなた、この世界の住人では";
		mes "ありませんね？";
		next;
		mes "[ウハリ]";
		mes "……う～ん！";
		mes "見知らぬ世界にまで一人で";
		mes "来ることができる勇気と知識！";
		mes "それをお持ちのあなたなら、";
		mes "きっと経験も豊富なのでしょう。";
		next;
		mes "[ウハリ]";
		mes "私はウハリ。";
		mes "学者をしております。";
		mes "熟練の冒険者様、あなたの";
		mes "お名前をお聞かせください！";
		next;
		menu "名乗る",-;
		emotion 3;
		emotion 40,"";
		mes "[ウハリ]";
		mes "わあ！";
		mes "いいお名前ですね、";
		mes "かっこいいです！";
		mes "さぞかし色んな修羅場を";
		mes "経験して来たのでしょう？";
		next;
		mes "[ウハリ]";
		mes "…………。";
		mes strcharinfo(0)+ "様……。";
		mes "頼もしいあなたに、";
		mes "1つお願いがあります。";
		mes "聞いていただけませんか？";
		next;
		if(select("話しを聞く","今は忙しい") == 2) {
			mes "[ウハリ]";
			mes "そうですか。";
			mes "残念です……。";
			next;
			emotion 28;
			mes "[ウハリ]";
			mes "ジャマをしてすみませんでした。";
			close;
		}
		emotion 18;
		mes "[ウハリ]";
		mes "ありがとうございます!!!";
		next;
		mes "[ウハリ]";
		mes "私には^0000cd兄^000000が一人います。";
		next;
		mes "[ウハリ]";
		mes "私も、兄も……。";
		mes "少しは名の知られた学者です。";
		mes "兄は、ここ何年か家に閉じこもって";
		mes "いたので、世間からも忘れられて";
		mes "しまいましたが……。";
		next;
		mes "[ウハリ]";
		mes "私はいろんなところへ";
		mes "研究の手伝いや講演などで";
		mes "出かけています。";
		next;
		mes "[ウハリ]";
		mes "自慢ではありませんが、";
		mes "私も割と頭がよくて色んな所から";
		mes "呼ばれるんです。へへへ。";
		next;
		mes "[ウハリ]";
		mes "それで、最近長期間、家を離れて";
		mes "いたのですが、その間に兄が";
		mes "姿を消してしまったのです。";
		next;
		mes "[ウハリ]";
		mes "家を空けている間も、兄とは手紙で";
		mes "連絡をしていたのですが、急に連絡が";
		mes "途絶えて……。";
		next;
		mes "[ウハリ]";
		mes "心配になって急いで会いに来たら";
		mes "^0000cd兄が監獄に連れて行かれた^000000";
		mes "というじゃありませんか！";
		next;
		mes "[ウハリ]";
		mes "手紙で、最近何やら実験を行っている";
		mes "ようなことを言っていましたが、";
		mes "詳しい話は知りません。";
		mes "ただ、監獄に連れて行かれるような";
		mes "ことを兄がするなんて信じられなくて。";
		next;
		mes "[ウハリ]";
		mes "直接聞きたいけど、私の身分では";
		mes "監獄に行くことができないので……。";
		next;
		mes "[ウハリ]";
		mes strcharinfo(0)+ "様が";
		mes "^0000cd私の代わりに監獄にいる兄に会って^000000";
		mes "何があったのか、話を聞いてきて";
		mes "くれませんか？";
		next;
		if(select("引き受ける","監獄になんて行きたくない") == 2) {
			mes "[ウハリ]";
			mes "そう……ですよね……。";
			mes strcharinfo(0)+ "様の";
			mes "おっしゃることもよくわかります。";
			mes "忙しいのに無理な頼みを言って";
			mes "すみませんでした……。";
			set ECL_4QUE,1;
			close;
		}
		emotion 3;
		mes "[ウハリ]";
		mes "本当ですか!?";
		mes "ありがとうございます！";
		mes "やはり、熟練の冒険者様は";
		mes "優れた人格もお持ちだ……。";
		next;
		mes "[ウハリ]";
		mes "兄の名前はウフルといいます。";
		mes "それでは冒険者様が兄と面会すると、";
		mes "エクラージュガードに伝えておきます。";
		next;
		mes "[ウハリ]";
		mes "ただ監獄には、^FF0000王のために働く者^000000";
		mes "でなければ入れないそうです。";
		mes "また連れて行かれた監獄は、";
		mes "ホームツリーの中にありますが、";
		mes "具体的な場所は";
		mes "私にはわかりません……。";
		next;
		mes "[ウハリ]";
		mes "そうそう！　兄は";
		mes "^0000cd知らない人から話しかけられても、";
		mes "無視してしまう^000000ことが多くて……。";
		mes "直したほうがいいといつも言っている";
		mes "のですが、何しろもともとがとても";
		mes "人見知りする性格なもので……。";
		next;
		mes "[ウハリ]";
		mes "なので、ちゃんと話を聞いてくれるまで";
		mes "根気が必要になると思います。";
		mes "兄に会えたらこの^0000cd手紙^000000を";
		mes "必ず渡してください。";
		next;
		emotion 27;
		mes "[ウハリ]";
		mes "それでは、よろしくお願いします！";
		mes "何とか探し出してください！";
		next;
		if(checkitemblank() == 0) {
			mes "[ウハリ]";
			mes "荷物が多くて渡せませんね。";
			mes "種類数を減らしてきてもらえますか？";
			close;
		}
		mes "‐ホームツリーの監獄に連れて";
		mes "　行かれたウフルに会いに行こう‐";
		set ECL_4QUE,2;
		setquest 14118;
		getitem 6546,1;
		close;
	case 1:
		mes "[ウハリ]";
		mes strcharinfo(0)+ "様、";
		mes "どうしましたか？";
		mes "先ほどは忙しいと……。";
		next;
		if(select("手伝いに来た","特に用はない") == 2) {
			mes "[ウハリ]";
			mes "そうですか……。";
			mes "私の力ではどうすることも";
			mes "できなくて……私では……。";
			close;
		}
		emotion 18;
		mes "[ウハリ]";
		mes "では、兄に会いに行って";
		mes "くれるんですか？";
		mes "ありがとうございます！";
		next;
		mes "[ウハリ]";
		mes "兄の名前はウフルといいます。";
		mes "それでは冒険者様が兄と面会すると、";
		mes "エクラージュガードに伝えておきます。";
		next;
		mes "[ウハリ]";
		mes "ただ監獄には、^FF0000王のために働く者^000000";
		mes "でなければ入れないそうです。";
		mes "また連れて行かれた監獄は、";
		mes "ホームツリーの中にありますが、";
		mes "具体的な場所は";
		mes "私にはわかりません……。";
		next;
		mes "[ウハリ]";
		mes "そうそう！　兄は";
		mes "^0000cd知らない人から話しかけられても、";
		mes "無視してしまう^000000ことが多くて……。";
		mes "直したほうがいいといつも言っている";
		mes "のですが、何しろもともとがとても";
		mes "人見知りする性格なもので……。";
		next;
		mes "[ウハリ]";
		mes "なので、ちゃんと話を聞いてくれるまで";
		mes "根気が必要になると思います。";
		mes "兄に会えたらこの^0000cd手紙^000000を";
		mes "必ず渡してください。";
		next;
		emotion 27;
		mes "[ウハリ]";
		mes "それでは、よろしくお願いします！";
		mes "何とか探し出してください！";
		next;
		if(checkitemblank() == 0) {
			mes "[ウハリ]";
			mes "荷物が多くて渡せませんね。";
			mes "種類数を減らしてきてもらえますか？";
			close;
		}
		mes "‐ホームツリーの監獄に連れて";
		mes "　行かれたウフルに会いに行こう‐";
		set ECL_4QUE,2;
		setquest 14118;
		getitem 6546,1;
		close;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		mes "[ウハリ]";
		mes "兄に会えましたか？";
		next;
		if(select("手紙を忘れた","まだ会えていない") == 2) {
			mes "[ウハリ]";
			mes "そうですか……。";
			mes "兄が今どんな状況かわからず、";
			mes "不安でいっぱいです。";
			next;
			mes "[ウハリ]";
			mes "お願いする立場でこんなことを";
			mes "言ってはいけないのでしょうが、";
			mes "急いでいただけないでしょうか？";
			next;
			mes "[ウハリ]";
			mes "兄が本当に心配なんです……。";
			close;
		}
		if(countitem(6546) < 1) {
			if(checkitemblank() == 0) {
				mes "[ウハリ]";
				mes "荷物が多くて渡せませんね。";
				mes "種類数を減らしてきてもらえますか？";
				close;
			}
			mes "[ウハリ]";
			mes "それならいくらでも書きますよ！";
			mes strcharinfo(0)+ "様の苦労に";
			mes "比べたらこんなことは";
			mes "なんでもありません！";
			getitem 6546,1;
			close;
		}
		mes "[ウハリ]";
		mes "あの……" +strcharinfo(0)+ "様、";
		mes "そこにお持ちなのは、私が渡した";
		mes "手紙のように見えますけど……？";
		close;
	case 7:
		mes "[ウハリ]";
		mes "あ、" +strcharinfo(0)+ "様！";
		mes "兄に会うことはできましたか？";
		mes "話しは聞けましたか？";
		next;
		menu "ウフルの話を伝える",-;
		mes "[ウハリ]";
		mes "……。";
		next;
		mes "[ウハリ]";
		mes "どうしてそんな無謀なことを……。";
		next;
		menu "あなたは体の小ささに不満はありませんか？",-;
		mes "[ウハリ]";
		mes "はい、私は特に不満は持っていません。";
		next;
		mes "[ウハリ]";
		mes "兄は、身体条件が不利なら";
		mes "頭でも良くなければならないと言って、";
		mes "幼い頃から私に色々と";
		mes "教えてくれました。";
		next;
		mes "[ウハリ]";
		mes "そのおかげで、";
		mes "学者としてご飯を食べていける、";
		mes "今の私があるのです。";
		next;
		mes "[ウハリ]";
		mes "それに……。";
		mes "体が小さいから";
		mes "大人になっても町の人たちが";
		mes "かわいがってくれたりします。";
		next;
		emotion 18;
		mes "[ウハリ]";
		mes "そのせいで美味しいものを";
		mes "いっぱいいただきました。";
		mes "へへへ。";
		next;
		mes "[ウハリ]";
		mes "……。";
		next;
		mes "[ウハリ]";
		mes "ただ……そうですね……。";
		mes "たしかに、兄は生まれつきの";
		mes "体の小ささに劣等感を抱いていました。";
		mes "大きくて美しくなれるなら、";
		mes "なんでもやるとさえ……。";
		next;
		mes "[ウハリ]";
		mes "……兄の体を戻す方法を";
		mes "必ず見つけ出さないと！";
		mes "体を戻して、監獄からも";
		mes "出してあげないといけません。";
		next;
		mes "[ウハリ]";
		mes "そこで、なんですが……。";
		mes "^0000cd頼みたいこと^000000があります。";
		next;
		mes "[ウハリ]";
		mes "兄の体を元に戻すために、";
		mes "まず、監獄に連れて行かれた時の";
		mes "状況を正確に知りたいんです。";
		next;
		mes "[ウハリ]";
		mes "兄が研究していたものが";
		mes "何か残されていれば";
		mes "いいのですが……。";
		mes "兄の話を聞いても、具体的には";
		mes "よく分からないですし……。";
		next;
		if(select("引き受ける","断る") == 2) {
			mes "[ウハリ]";
			mes "やはり、忙しいですよね。";
			mes "すみません。";
			mes "兄に会ってくれたことだけでも";
			mes "本当にありがとうございます。";
			set ECL_4QUE,8;
			chgquest 14123,14124;
			close;
		}
		mes "[ウハリ]";
		mes "本当にありがとうございます！";
		next;
		mes "[ウハリ]";
		mes "それでは、^0000cdその当時のことを";
		mes "よく知っていそうな方たち^000000に";
		mes "話しを聞いてきてください！";
		next;
		mes "[ウハリ]";
		mes "まずはマシオネさんに聞いて";
		mes "見るのがいいと思います。";
		next;
		mes "[ウハリ]";
		mes "お願いします。";
		mes "私は今まで兄が話していたことを";
		mes "もう一度考えてみます。";
		viewpoint 1,200,272,0,0xFF0000;
		set ECL_4QUE,9;
		chgquest 14123,14125;
		close;
	case 8:
		mes "[ウハリ]";
		mes "ああ、兄さん……。";
		mes "これからどうすればいいんだろう……。";
		next;
		if(select("力になる","知らないふりをする") == 2) {
			mes "[ウハリ]";
			mes "はああ～。";
			mes "誰か力になってくれないかな～～。";
			close;
		}
		mes "[ウハリ]";
		mes "本当ですか!?";
		mes "ありがとうございます！";
		next;
		mes "[ウハリ]";
		mes "それでは、^0000cdその当時のことを";
		mes "よく知っていそうな方たち^000000に";
		mes "話しを聞いてきてください！";
		next;
		mes "[ウハリ]";
		mes "まずはマシオネさんに聞いて";
		mes "見るのがいいと思います。";
		next;
		mes "[ウハリ]";
		mes "お願いします。";
		mes "私は今まで兄が話していたことを";
		mes "もう一度考えてみます。";
		viewpoint 1,200,272,0,0xFF0000;
		set ECL_4QUE,9;
		chgquest 14124,14125;
		close;
	case 9:
	case 10:
	case 11:
		mes "[ウハリ]";
		mes "^0000cdその当時のことを";
		mes "よく知っていそうな方たち^000000に";
		mes "話しを聞いてきてください！";
		next;
		mes "[ウハリ]";
		mes "お願いします。";
		mes "私は今まで兄が話していたことを";
		mes "もう一度考えてみます。";
		close;
	case 12:
		viewpoint 2,1,1,0,0xFFFFFF;
		mes "[ウハリ]";
		mes "どうでしたか？";
		mes "何か聞きだす事ができましたか？";
		next;
		menu "スベリから受け取った紙を渡す",-;
		mes "[ウハリ]";
		mes "ん……？";
		next;
		if(countitem(6547) < 1) {
			mes "[ウハリ]";
			mes "あの……何を持って来たと";
			mes "言うんですか……？";
			next;
			mes "‐スベリから受け取った紙がない。";
			mes "　なくしてしまった場合、";
			mes "　もう一度スベリのところに行こう‐";
			close;
		}
		mes "[ウハリ]";
		mes "これは……^0000cd研究書^000000？";
		mes "兄はこれを見て……。";
		next;
		mes "[ウハリ]";
		mes "しかし……これは……。";
		mes "どうやら研究書の一部のみのようです。";
		mes "他の文書はありませんでしたか？";
		next;
		menu "ありませんでした",-;
		mes "[ウハリ]";
		mes "……そうですか。";
		mes "では、これを一度分析してみます。";
		mes "少し^0000cd時間^000000をください。";
		next;
		mes "‐ウハリが分析を始めたようだ。";
		mes "　もう一度話しかけみよう‐";
		delitem 6547,1;
		set ECL_4QUE,13;
		chgquest 14128,14131;
		close;
	case 13:
		mes "[ウハリ]";
		mes "おお、お待たせしました。";
		next;
		mes "[ウハリ]";
		mes "研究書ですが、一通り目を通し、";
		mes "書いてあることは理解しました。";
		mes "しかし、手元にあるのが研究書の";
		mes "一部だけですので、やはり研究の";
		mes "全容を把握するまでには至らず……。";
		next;
		mes "[ウハリ]";
		mes "研究に用いる材料が書いて";
		mes "あるのですが、用意するのが";
		mes "難しいものが多くて……。";
		mes "それに、調合の際の割合や順序にも";
		mes "理解できない部分があります……。";
		next;
		mes "[ウハリ]";
		mes "う～ん……。";
		mes "そもそも、上級ラフィネの羽の欠片と";
		mes "サファ族の髪の毛はどうして";
		mes "使われているんだろう？";
		next;
		mes "[ウハリ]";
		mes strcharinfo(0)+ "様の話では";
		mes "兄の姿は、サファ族のように";
		mes "青い光を放ち、体格が大きく、";
		mes "羽も普通の上級ラフィネのモノより";
		mes "大きいサイズだったのですよね？";
		next;
		mes "[ウハリ]";
		mes "そうなると、研究の内容は……。";
		mes "^0000cd2つの種族の特徴を融合する方法^000000";
		mes "……なのか？";
		next;
		mes "[ウハリ]";
		mes "しかし、上級ラフィネの羽の欠片と";
		mes "サファ族の髪の毛は、どうやって";
		mes "用意したのだろう？";
		next;
		mes "[ウハリ]";
		mes "兄が実験をした時も誰かの羽と";
		mes "髪の毛が使われたはずだけど……。";
		mes "兄がまさか……。";
		next;
		menu "実験の材料は依頼者が用意していた",-;
		mes "[ウハリ]";
		mes "兄がそう言っていたのですか？";
		mes "そうですか……。";
		next;
		mes "[ウハリ]";
		mes "しかし、見れば見るほどこの研究は";
		mes "とても……身の毛がよだちます。";
		mes "このようなことを思いついたこと";
		mes "自体が……。";
		next;
		mes "[ウハリ]";
		mes "だけど兄の体を戻すためには、";
		mes "私もまた、同じ研究をしなければ";
		mes "なりません。";
		next;
		mes "[ウハリ]";
		mes "あぁ……もう少し詳細な内容が";
		mes "書かれてあれば良かったのに。";
		next;
		menu "もう一度ウフルに聞いて来ようか？",-;
		mes "[ウハリ]";
		mes "それは……無駄だと思います。";
		mes "兄もこの研究書を元に実験をし、";
		mes "そして失敗した。";
		mes "だからあなたがおっしゃるような";
		mes "姿になってしまったのでしょう。";
		next;
		mes "[ウハリ]";
		mes "それよりも、研究書内容を正確に";
		mes "把握するなら^0000cdこの方法を教えた";
		mes "ラフィネを探したほうが良さそう^000000です。";
		next;
		if(select("ラフィネを探してみます","それは無理だ") == 2) {
			mes "[ウハリ]";
			mes "私も難しいことはわかっています。";
			mes "よくわかっているから";
			mes strcharinfo(0)+ "様に";
			mes "頼んでいるのです。";
			next;
			mes "[ウハリ]";
			mes strcharinfo(0)+ "様は";
			mes "経験も多くて実力もある方ですから。";
			next;
			mes "[ウハリ]";
			mes "でも、やはり無理ですよね？";
			mes "そうですよね……。";
			emotion 28;
			set ECL_4QUE,14;
			chgquest 14131,14132;
			close;
		}
		mes "[ウハリ]";
		mes "私が依頼したかったのがそれです!!";
		mes "さすが～やはり経験豊富な冒険者様は";
		mes "何でもお見通しですね!!";
		next;
		mes "[ウハリ]";
		mes "では、申し訳ありませんが";
		mes "お願いします！";
		next;
		mes "[ウハリ]";
		mes "そのラフィネを探して体を戻す方法が";
		mes "何か聞いて見てください。";
		mes "そして何の意図でこのようなモノを";
		mes "兄に渡したのかも。";
		next;
		mes "[ウハリ]";
		mes "実際にその上級ラフィネを見た人も";
		mes "いるようですから、^0000cd町の方たちに^000000";
		mes "聞いて見るのが早そうです。";
		next;
		mes "‐スベリから、ウフルと一緒にいた";
		mes "　ラフィネの話を聞こう‐";
		viewpoint 1,170,195,0,0xFF0000;
		set ECL_4QUE,15;
		chgquest 14131,14133;
		close;
	case 14:
		mes "[ウハリ]";
		mes strcharinfo(0)+ "様、";
		mes "力を貸してくれるんですか？";
		next;
		if(select("お互いに助け合わないと","ただここを通っただけです") == 2) {
			mes "[ウハリ]";
			mes "そうですか？";
			mes "すみませんが今は少し忙しいです。";
			close;
		}
		mes "[ウハリ]";
		mes "本当にありがとうございます!!";
		mes "やはり、神様は兄のことを";
		mes "見捨てていなかった……。";
		next;
		mes "[ウハリ]";
		mes "では、申し訳ありませんが";
		mes "お願いします！";
		next;
		mes "[ウハリ]";
		mes "兄に研究書を渡したラフィネを";
		mes "探して、体を戻す方法を聞き出して";
		mes "ください。";
		mes "そして何の意図でこのようなモノを";
		mes "兄に渡したのかも。";
		next;
		mes "[ウハリ]";
		mes "実際にその上級ラフィネを見た人も";
		mes "いるようですから、^0000cd町の方たちに^000000";
		mes "聞いて見るのが早そうです。";
		next;
		mes "‐スベリから、ウフルと一緒にいた";
		mes "　ラフィネの話を聞こう‐";
		set ECL_4QUE,15;
		chgquest 14132,14133;
		close;
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
		mes "[ウハリ]";
		mes "兄に研究書を渡した";
		mes "上級ラフィネは";
		mes "見つかりましたか？";
		close;
	case 22:
		mes "[ウハリ]";
		mes "兄に研究書を渡した";
		mes "上級ラフィネは";
		mes "見つかりましたか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "それが……そのラフィネは";
		mes "^0000cdすでに死んでいました。^000000";
		next;
		mes "[ウハリ]";
		mes "はい？";
		mes "死んでいる？";
		next;
		mes "‐ウフルの話はしない方が良さそうだ‐";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "最後に目撃された草原に";
		mes "行ってみたらすでに死んでいました。";
		mes "危険な研究に気づいた上層部が";
		mes "兵士を送ったのでないでしょうか？";
		next;
		mes "[ウハリ]";
		mes "…………。";
		next;
		mes "[ウハリ]";
		mes "だけどどうしてうちの兄に";
		mes "その研究を任せたのでしょう？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "小さな体に劣等感を持っている";
		mes "部分をついて、ウフルさんの頭脳を";
		mes "利用しようとしたのでは";
		mes "ないでしょうか。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "研究が成功していたら、";
		mes "他の下級ラフィネに対して";
		mes "悪用されていたかもしれません。";
		next;
		mes "[ウハリ]";
		mes "ああ、本当に恐ろしい話です。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ウフルさんの研究が失敗して";
		mes "良かったのかもしれません。";
		mes "ウフルさんには悪いですが……。";
		next;
		mes "[ウハリ]";
		mes "…………。";
		next;
		mes "[ウハリ]";
		mes "それでも何か方法があるはずです。";
		mes "私ひとりででも何とかして";
		mes "兄の体を元の姿に戻します。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "私が手伝えることはありますか？";
		next;
		mes "[ウハリ]";
		mes "ありがとうございます。";
		mes "多分これが最後の頼みだと思います。";
		next;
		mes "[ウハリ]";
		mes "この研究書に書かれた^0000cd材料たち^000000は";
		mes "私の力では手に入れることが";
		mes "難しい物なので";
		mes strcharinfo(0)+ "様の";
		mes "手を借りたいです。";
		next;
		mes "[ウハリ]";
		mes "必要な材料は^0000cdラフィネの羽の一部、";
		mes "堅い髪の毛、カルボーディル、";
		mes "精製されたブラディウム、";
		mes "闇のルーン、真っ赤なルーンを";
		mes "各1個ずつ^000000です。";
		mes "これらを集めて来てください。";
		next;
		mes "[ウハリ]";
		mes "今、私が信じられるのは";
		mes strcharinfo(0)+ "様だけです。";
		mes "お願いします。";
		next;
		mes "‐^0000cdラフィネの羽の一部^000000はジラニに";
		mes "　事情を話して渡してもらおう。";
		mes "　^0000cd堅い髪の毛^000000はムワディリカの遺体の";
		mes "　近くを探してみよう‐";
		set ECL_4QUE,23;
		chgquest 14140,14141;
		close;
	case 23:
		mes "[ウハリ]";
		mes "材料はすべて集まりましたか？";
		next;
		if(select("すべて集めました","材料をもう一度教えて下さい") == 2) {
			mes "[ウハリ]";
			mes "必要な材料は^0000cdラフィネの羽の一部、";
			mes "堅い髪の毛、カルボーディル、";
			mes "精製されたブラディウム、";
			mes "闇のルーン、真っ赤なルーンを";
			mes "各1個ずつ^000000です。";
			next;
			mes "‐^0000cdラフィネの羽の一部^000000はジラニに";
			mes "　事情を話して渡してもらおう。";
			mes "　^0000cd堅い髪の毛^000000はムワディリカの遺体の";
			mes "　近くを探してみよう‐";
			close;
		}
		if(countitem(6548) < 1 || countitem(6545) < 1 || countitem(972) < 1 ||
			countitem(6090) < 1 || countitem(7511) < 1 || countitem(7563) < 1) {
			mes "[ウハリ]";
			mes "あの……" +strcharinfo(0)+ "様？";
			mes "アイテムは何処にあるんですか？";
			mes "これじゃ困ります。";
			close;
		}
		mes "[ウハリ]";
		mes "用意するのは大変だったでしょう？";
		mes "本当にありがとうございます！";
		next;
		mes "[ウハリ]";
		mes "これでどうにか研究を進めてみます。";
		next;
		mes "[ウハリ]";
		mes "今までいろいろと力になってくれて";
		mes "ありがとうございます。";
		next;
		mes "[ウハリ]";
		mes "これは私からの気持ちです。";
		next;
		if(checkitemblank() == 0) {
			mes "[ウハリ]";
			mes "荷物が多くて渡せませんね。";
			mes "種類数を減らしてきてもらえますか？";
			close;
		}
		mes "[ウハリ]";
		mes strcharinfo(0)+ "様に";
		mes "この先、幸運が訪れんことを";
		mes "願っています。";
		delitem 6548,1;
		delitem 6545,1;
		delitem 972,1;
		delitem 6090,1;
		delitem 7511,1;
		delitem 7563,1;
		set ECL_4QUE,24;
		chgquest 14141,201595;
		getexp 5000000,0;
		getitem 6081,25;
		close;
	case 24:
		mes "[ウハリ]";
		mes "研究はまだ進行中です。";
		mes "少しでも希望があるのなら、";
		mes "私は死ぬ気で頑張ります";
		close;
	}
OnInit:
	waitingroom "美しさの代償",0;
	end;
}

ecl_in02.gat,149,117,4	script	ウフル	619,{
	switch(ECL_4QUE) {
	case 0:
	case 1:
		mes "[謎の男]";
		mes "……。";
		close;
	case 2:
		mes "[謎の男]";
		mes "……。";
		next;
		mes "‐話しかけても、まったく反応がない。";
		mes "　根気強く話しかける必要が";
		mes "　ありそうだ‐";
		set ECL_4QUE,3;
		setquest 14119;
		close;
	case 3:
		mes "[謎の男]";
		mes "……。";
		next;
		mes "‐謎の男は、こちらの話に答える気が";
		mes "　なさそうに見える。";
		mes "　気を引く物を見せる必要が";
		mes "　ありそうだ‐";
		set ECL_4QUE,4;
		chgquest 14119,14120;
		close;
	case 4:
		mes "[謎の男]";
		mes "……。";
		next;
		menu "ウハリからの手紙を見せる",-;
		if(countitem(6546) < 1) {
			mes "[謎の男]";
			mes "何が……あると言うんですか？";
			next;
			mes "‐ウハリから受け取った手紙が";
			mes "　どこにも見当たらない。";
			mes "　なくしてしまった場合、ウハリに";
			mes "　もう一度手紙を書いて貰おう‐";
			close;
		}
		mes "[謎の男]";
		mes "これ……は……？";
		next;
		mes "‐謎の男が、初めてこちらの話に";
		mes "　反応を示した。";
		mes "　手紙について説明をしよう‐";
		set ECL_4QUE,5;
		chgquest 14120,14121;
		close;
	case 5:
		if(countitem(6546) < 1) {
			mes "[謎の男]";
			mes "何が……あると言うんですか？";
			next;
			mes "‐ウハリから受け取った手紙が";
			mes "　どこにも見当たらない。";
			mes "　なくしてしまった場合、ウハリに";
			mes "　もう一度手紙を書いて貰おう‐";
			close;
		}
		mes "[謎の男]";
		mes "手……紙……？";
		next;
		menu "あなたがウフルさんですね？",-;
		mes "[ウフル]";
		mes "そう……ですけど……？";
		next;
		menu "ウハリさんからあなたへの手紙です",-;
		mes "[ウフル]";
		mes "……弟から？";
		mes "ありがとうございます……。";
		next;
		mes "‐ウフルにウハリからの手紙を";
		mes "　渡した。";
		mes "　もう一度話しかけてみよう‐";
		delitem 6546,1;
		set ECL_4QUE,6;
		setquest 14122;
		delquest 14118;
		delquest 14121;
		close;
	case 6:
		mes "‐ウフルは手紙を";
		mes "　読み終えたようだ‐";
		next;
		mes "[ウフル]";
		mes "……手紙を届けてくれて、";
		mes "ありがとうございます。";
		mes "ウハリは元気に過ごしているんですか？";
		next;
		menu "あなたの心配をしていました",-;
		mes "[ウフル]";
		mes "そうですか……。";
		next;
		mes "[ウフル]";
		mes "ああ、私はいったい何てことを";
		mes "してしまったんだ……。";
		next;
		mes "‐ウフルは、頭を抱えて";
		mes "　苦悩している‐";
		next;
		menu "何があったのですか？",-;
		mes "[ウフル]";
		mes "……あなたに手紙を託したと";
		mes "いうことは、弟はあなたを";
		mes "信用したということでしょうね。";
		mes "あいつは人を見る目があるから……。";
		mes "わかりました。お話します。";
		next;
		mes "[ウフル]";
		mes "ウハリを見たら分かると思いますが、";
		mes "私は元々はこんな姿では";
		mes "ありませんでした。";
		mes "私と弟は下級ラフィネの中でも";
		mes "^0000cd特に体が小さかったのです。^000000";
		next;
		mes "[ウフル]";
		mes "美しさを重視するラフィネの中では";
		mes "私たちは常に疎外感を感じていました。";
		next;
		mes "[ウフル]";
		mes "しかし、身体的な特徴はどうしようも";
		mes "ないこと……。";
		mes "私たちは劣っている部分を補うため、";
		mes "必死に勉強をし、おかげで人よりも";
		mes "賢くなることができました。";
		next;
		mes "[ウフル]";
		mes "学問で成功し、名も知られ始めた";
		mes "私のところに、ある日";
		mes "^0000cdムワディリカ^000000という一人の";
		mes "上級ラフィネが私を訪ねて来ました。";
		next;
		mes "[ウフル]";
		mes "ムワディリカは、ある研究所に所属する";
		mes "研究員で、その研究所が秘密裏に";
		mes "行っている研究を、私に手伝って";
		mes "ほしいと言いました。";
		next;
		mes "[ウフル]";
		mes "その研究とは、^0000cdラフィネ一族が";
		mes "さらに強く美しくなれるように";
		mes "身体を強化させる研究^000000";
		mes "だったのです。";
		next;
		mes "[ウフル]";
		mes "私は喜んで引き受けました。";
		mes "私の学者としての能力を認めてくれた";
		mes "ことがうれしかった。";
		mes "それに体が大きくなれるなら……。";
		next;
		mes "[ウフル]";
		mes "ムワディリカから、";
		mes "研究内容は誰にも話さないようにと";
		mes "言われてましたので、私がもっとも";
		mes "信頼している弟のウハリにも、";
		mes "詳しい話はしませんでした。";
		next;
		mes "[ウフル]";
		mes "私は家に引きこもり、";
		mes "研究に没頭しました。";
		mes "実験に必要なものは";
		mes "ムワディリカが用意してくれました。";
		next;
		mes "[ウフル]";
		mes "そしてその研究の末に、";
		mes "完成まであと一歩というところまで";
		mes "辿り着きました。";
		next;
		mes "[ウフル]";
		mes "しかし、その最後の一歩が、";
		mes "問題でした。";
		mes "最後の一歩……それはつまり、";
		mes "実際にラフィネの体を使った、";
		mes "人体実験です。";
		next;
		mes "[ウフル]";
		mes "どのような効果が表れるかわからない";
		mes "実験に、無関係の人を巻き込む";
		mes "わけにはいかない……。";
		mes "それで私は私自身を実験対象と";
		mes "する決心をしました。";
		next;
		mes "[ウフル]";
		mes "結果は見ての通り……。";
		next;
		mes "[ウフル]";
		mes "ムワディリカは実験が失敗すると";
		mes "どこかへと逃げてしまいました。";
		mes "それで私は一人で何とかしようと";
		mes "したのですが……。";
		mes "こんなところに連れて来られて";
		mes "しまって……。";
		next;
		mes "[ウフル]";
		mes "……このような姿になって、";
		mes "以前の小さかった体が";
		mes "とても懐かしく思えます。";
		mes "あの小さかった頃の体に";
		mes "戻りたい……。";
		next;
		mes "[ウフル]";
		mes "今の私は怪物だ……。";
		next;
		mes "[ウフル]";
		mes "こんなモノを望んだわけでは";
		mes "なかったのに……。";
		mes "欲張り過ぎたのでしょうね。";
		next;
		mes "[ウフル]";
		mes "すみません、話が長すぎましたね。";
		mes "まあ、私はここから出る事は";
		mes "難しそうです。";
		next;
		mes "[ウフル]";
		mes "もし、あなたがここから出る事が";
		mes "出来るなら、ウハリに元の姿に";
		mes "戻る方法を必ず見つけてくれと";
		mes "伝えてください。";
		mes "お願いします。";
		next;
		mes "‐ウハリのところに戻り、";
		mes "　ウフルの状況を伝えよう‐";
		set ECL_4QUE,7;
		chgquest 14122,14123;
		close;
	case 7:
	case 8:
		mes "[ウフル]";
		mes "本当にお願いします。";
		next;
		mes "‐ウハリのところに戻り、";
		mes "　ウフルの状況を伝えよう‐";
		close;
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
		mes "[ウフル]";
		mes "ウハリに会えましたか？";
		mes "良かったです。";
		mes "これで牢獄の生活でも";
		mes "少し安心できました。";
		next;
		mes "[ウフル]";
		mes "今日は監獄がとても暖かく";
		mes "感じられます。";
		close;
	case 21:
		mes "[ウフル]";
		mes "どうしました？";
		mes "何か良い知らせでもありますか？";
		next;
		menu "草原でラフィネの死体を見ました",-;
		mes "[ウフル]";
		mes "……ラフィネの死体ですか？";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "^0000cd上級ラフィネの死体です。^000000";
		mes "あなたに研究を依頼していた";
		mes "ムワディリカのようでした。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "それから、あなたが捕まる前に、";
		mes "草原で大きな体をしたラフィネが";
		mes "上級ラフィネを追う姿を";
		mes "見た者もいます。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "そして彼は殺害されました。";
		next;
		mes "[ウフル]";
		mes "何が言いたいんですか？";
		mes "殺害したのが私だと言いたいんですか？";
		next;
		menu "怒りを抑えられなかったのですか？",-;
		mes "[ウフル]";
		mes "…………。";
		mes "私が殺したと明かしたら……。";
		mes "何か変わるのですか。";
		next;
		mes "[ウフル]";
		mes "そんなことをしても";
		mes "私の体はこのままです……。";
		next;
		mes "[ウフル]";
		mes "あいつは私を騙したのです!!!";
		next;
		mes "[ウフル]";
		mes "私にはすべてのラフィネ族が";
		mes "さらに美しく強くなるのが";
		mes "研究の目的だと言って、";
		mes "私を実験対象にまでさせておいて！";
		next;
		mes "[ウフル]";
		mes "実験の危険性や材料の検証などは";
		mes "していませんでした。";
		mes "そして実験に失敗した途端、";
		mes "あいつは逃げ出したのです!!!";
		next;
		mes "[ウフル]";
		mes "……ムワディリカは死ぬ前に";
		mes "本当の研究の目的を話しました。";
		next;
		mes "[ウフル]";
		mes "自分を認めてくれなかった上層部に";
		mes "^0000cd自分の能力を証明することが";
		mes "本当の目的^000000だったと！";
		mes "たったそれだけのために……。";
		mes "たったそれだけの……。";
		next;
		mes "[ウフル]";
		mes "…………。";
		next;
		mes "[ウフル]";
		mes "上層部があいつの実験内容を知り、";
		mes "調査をして、一緒に実験に参加した";
		mes "私を捕まえました。";
		next;
		mes "[ウフル]";
		mes "私が犯した罪は何ですか？";
		next;
		mes "[ウフル]";
		mes "私はただ、あいつの欲望に利用された";
		mes "道具にすぎません。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "ムワディリカが研究をし始めた理由も";
		mes "あなたが研究の提案に流された理由と";
		mes "同じような気がします。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "いくら被害者だとしてもあなたが";
		mes "犯した罪を正当化させることは";
		mes "できません……。";
		mes "ただ、今ここに閉じ込められたあなたの";
		mes "姿を見ると、すでに罪の対価を";
		mes "支払っているようにみえます。";
		next;
		mes "[ウフル]";
		mes "…………。";
		next;
		mes "[ウフル]";
		mes "ウハリには……話さないでください。";
		mes "お願いします。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "私はここには来なかったことにします。";
		next;
		mes "[ウフル]";
		mes "ありがとうございます……。";
		mes "最後まで世話になりますね……。";
		next;
		mes "‐ウハリと話をしよう‐";
		set ECL_4QUE,22;
		chgquest 14139,14140;
		close;
	case 22:
		mes "[ウフル]";
		mes "…………。";
		close;
	}
}

eclage.gat,200,272,4	script	マシオネ	437,{
	if(ECL_4QUE == 9) {
		viewpoint 2,1,1,0,0xFFFFFF;
		emotion 23;
		mes "[マシオネ]";
		mes "あら！　びっくりした！";
		mes "ななな、なんですか？";
		mes "いきなり現れて！";
		mes "私に何をしようと！";
		next;
		menu "ウフルについて聞きたい",-;
		mes "[マシオネ]";
		mes "何だ、ウハリに言われてきたのね？";
		mes "ウフルについて、ねぇ……。";
		mes "う～ん、私も何かが起きたらしい";
		mes "ってことしか知らなくて……。";
		next;
		mes "[マシオネ]";
		mes "いつもは居るのか居ないのか";
		mes "分からないくらいにおとなしい人が";
		mes "どうして監獄に連れて行かれたのか。";
		next;
		mes "[マシオネ]";
		mes "あ、そういえばウフルが";
		mes "連れて行かれた日に";
		mes "^0000cdとても大きな悲鳴^000000を聞いたわ。";
		mes "すっごく驚いて、怖くて……。";
		next;
		mes "[マシオネ]";
		mes "そのちょっと後だったわね。";
		mes "たくさんの人が突然集まってきて、";
		mes "ウフルを捕まえて行ったの。";
		next;
		mes "[マシオネ]";
		mes "連れて行かれる時に、数日ぶりに";
		mes "家の外に出たウフルを見たわ。";
		mes "その時の、ウフルの姿が……。";
		mes "姿が……。";
		next;
		mes "[マシオネ]";
		mes "……その時^0000cdゴティ^000000も一緒に";
		mes "見ていたの。";
		mes "私より真剣に見ていたから他に何かを";
		mes "覚えているかもしれないわ。";
		mes "一度話しを聞いてみるといいわよ。";
		viewpoint 1,163,228,0,0xFF0000;
		set ECL_4QUE,10;
		chgquest 14125,14126;
		close;
	}
	emotion 23;
	mes "[マシオネ]";
	mes "あら！　びっくりした！";
	mes "ななな、なんですか!?";
	mes "いきなり現れないでくれませんか？";
	next;
	mes "[マシオネ]";
	mes "私は驚きやすい体質なんですよ！";
	close;
}

eclage.gat,163,228,4	script	ゴティ	438,{
	if(ECL_4QUE == 10) {
		viewpoint 2,1,1,0,0xFFFFFF;
		mes "[ゴティ]";
		mes "どうしました？";
		next;
		menu "マシオネさんの紹介で……",-;
		mes "[ゴティ]";
		mes "マシオネに言われて来たんですか？";
		mes "何の用です？";
		next;
		menu "ウフルについて聞く",-;
		mes "[ゴティ]";
		mes "ウフルのことですか？";
		mes "私もそれほど知っているわけでは";
		mes "ありませんが……。";
		next;
		mes "[ゴティ]";
		mes "そうですね……。";
		mes "監獄に連れて行かれた時より";
		mes "ずいぶん前になりますが、";
		mes "ウフルが^0000cd見知らぬ人と一緒に^000000";
		mes "いるのを見ました。";
		next;
		mes "[ゴティ]";
		mes "ウフルのことは昔から知っていますが、";
		mes "あのように明るい顔で笑うのは";
		mes "初めて見ましたね。";
		next;
		mes "[ゴティ]";
		mes "何かいい事でもあったのかと聞いたら、";
		mes "持っていた^0000cd紙^000000を振りながら";
		mes "「これで自分もりっぱな姿になれる」";
		mes "と……。";
		next;
		mes "[ゴティ]";
		mes "一緒にいた人は、言っちゃだめだ";
		mes "見たいな感じのジェスチャーを";
		mes "していました。";
		next;
		mes "[ゴティ]";
		mes "私は少し不安だったけど、";
		mes "ウフルが喜んでいる姿を見て、";
		mes "何も言えなかったんです。";
		next;
		menu "ウフルの持っていた紙について聞く",-;
		mes "[ゴティ]";
		mes "紙ですか？";
		mes "そうですね……。";
		mes "うーん、私は遠くにいたから";
		mes "よく見えませんでした……。";
		next;
		mes "[ゴティ]";
		mes "そうだ、うちの^0000cd旦那のスベリ^000000に";
		mes "聞いてみてください。";
		mes "ウフルと仲良くしていたので";
		mes "何か知っているかもしれません。";
		viewpoint 1,170,195,0,0xFF0000;
		set ECL_4QUE,11;
		chgquest 14126,14127;
		close;
	}
	if(ECL_4QUE == 16) {
		mes "[ゴティ]";
		mes "上級ラフィネ……？";
		mes "あ～、覚えていますよ。";
		next;
		mes "[ゴティ]";
		mes "この前あなたにお話しした、";
		mes "ウフルと一緒にいた人、";
		mes "その人が上級ラフィネでした。";
		mes "その人のことを言っているんですか？";
		next;
		mes "[ゴティ]";
		mes "そのラフィネならウフルと";
		mes "少し一緒にいた後、";
		mes "どこかへと行ってしまいました。";
		next;
		mes "[ゴティ]";
		mes "けど、そのラフィネ、";
		mes "^0000cd羽が大きく美しかったので";
		mes "上級という印象はあったんですが、";
		mes "目が鋭くて、どこか怪しい^000000";
		mes "感じがしました。";
		next;
		menu "他に何か覚えていませんか？",-;
		mes "[ゴティ]";
		mes "あ～、そういえば^0000cdポンペさんが";
		mes "花の咲いた大地で上級ラフィネが";
		mes "何かから逃げているのを";
		mes "目撃した^000000と話してました。";
		next;
		mes "[ゴティ]";
		mes "そのラフィネも^0000cd羽が大きくて";
		mes "美しかったらしい^000000です。";
		next;
		mes "[ゴティ]";
		mes "詳しく知りたいなら、";
		mes "ポンペさんを訪ねてみてください。";
		viewpoint 1,126,151,0,0xFF0000;
		set ECL_4QUE,17;
		chgquest 14134,14135;
		close;
	}
	mes "[ゴティ]";
	mes "もしかしてホームツリーに";
	mes "行ってみました？";
	mes "私たちのヤイとは比較できないくらい";
	mes "美しいらしいけど……。";
	next;
	mes "[ゴティ]";
	mes "やはり私たちのような下級の";
	mes "ラフィネは、夢を見るしか";
	mes "できないんでしょうねぇ。";
	close;
}

eclage.gat,170,195,4	script	スベリ	443,{
	if(ECL_4QUE == 11) {
		viewpoint 2,1,1,0,0xFFFFFF;
		mes "[スベリ]";
		mes "俺に何か用でもあるのか？";
		next;
		menu "ウフルが持っていた紙について",-;
		mes "[スベリ]";
		mes "ああ～、";
		mes "俺も女房から、ウフルがそのような物を";
		mes "持っていたと聞いたけど……。";
		mes "俺もそれが何なのか良く知らないよ？";
		next;
		mes "[スベリ]";
		mes "それに、君はいったい誰なんだ？";
		next;
		menu "ウハリに頼まれたことを話す",-;
		mes "[スベリ]";
		mes "ほう、ウハリに？";
		mes "ウハリ……。";
		mes "あっ！　しまった、忘れてた！";
		next;
		mes "[スベリ]";
		mes "ウフルが書いた^0000cd手紙^000000が";
		mes "ウチの窓に刺さっていたんだ！";
		mes "監獄に連れていかれる直前に";
		mes "書いたものだろう。";
		next;
		mes "[スベリ]";
		mes "手紙には、同封された^0000cd文書^000000を";
		mes "弟に必ず渡してくれと";
		mes "書かれていたんだ。";
		next;
		mes "[スベリ]";
		mes "だけど!!!";
		next;
		mes "[スベリ]";
		mes "その、なんだ……。";
		mes "忙しくて、ウハリに渡す";
		mes "タイミングが、な！";
		mes "ははは……。";
		next;
		mes "[スベリ]";
		mes "その、同封された文書がもしかして";
		mes "ウチの女房が話していた紙なのかな？";
		mes "あれは……どこにやったっけ……。";
		next;
		mes "[スベリ]";
		mes "ああ、あったあった！";
		mes "これをウハリに渡してやってくれ。";
		next;
		mes "[スベリ]";
		mes "可哀そうなあいつらを";
		mes "よろしく頼むよ。";
		next;
		mes "[スベリ]";
		mes "真面目な子たちが";
		mes "どうしてこんなことに";
		mes "なっちまったのかね……。";
		next;
		if(checkitemblank() == 0) {
			mes "[スベリ]";
			mes "荷物が多くて渡せないな。";
			mes "種類数を減らしてきてくれるかい？";
			close;
		}
		mes "‐スベリから汚れた研究書を";
		mes "　預かった。ウハリに渡そう‐";
		viewpoint 1,282,255,0,0xFF0000;
		getitem 6547,1;
		set ECL_4QUE,12;
		chgquest 14127,14128;
		close;
	}
	if(ECL_4QUE == 12 && countitem(6547) < 1) {
		mes "[スベリ]";
		mes "俺はどうして君がここに";
		mes "来たかを分かっている!!";
		next;
		mes "[スベリ]";
		mes "これを落として行ったな？";
		next;
		if(checkitemblank() == 0) {
			mes "[スベリ]";
			mes "おっと、荷物が多くて渡せないな。";
			mes "種類数を減らしてきてくれるかい？";
			close;
		}
		mes "[スベリ]";
		mes "若いんだから、";
		mes "もう少ししっかりしなさい。";
		getitem 6547,1;
		close;
	}
	if(ECL_4QUE == 15) {
		viewpoint 2,1,1,0,0xFFFFFF;
		mes "[スベリ]";
		mes "ん？　なんだ？";
		mes "他にも俺に用があるのか？";
		next;
		menu "ウフルと一緒にいた上級ラフィネは誰ですか？",-;
		mes "[スベリ]";
		mes "上級ラフィネ？";
		mes "う～ん、それがなぁ……。";
		mes "俺にも誰なのかよく分からないんだよ。";
		next;
		mes "[スベリ]";
		mes "俺も初めて見るラフィネだった。";
		mes "そして、その時以降、";
		mes "一度もその姿を見ていないんだ。";
		next;
		mes "[スベリ]";
		mes "そうだなぁ。";
		mes "俺の女房の所に行って見な？";
		mes "一緒に見てたから。";
		next;
		mes "[スベリ]";
		mes "俺の女房は記憶力がいいから";
		mes "何かの力になるかもな。";
		next;
		mes "‐スベリの奥さん、ゴティに";
		mes "　上級ラフィネについて聞いてみよう‐";
		viewpoint 1,163,228,0,0xFF0000;
		set ECL_4QUE,16;
		chgquest 14133,14134;
		close;
	}
	mes "[スベリ]";
	mes "俺の女房の夢はホームツリーに";
	mes "行くことなんだ。";
	next;
	mes "[スベリ]";
	mes "俺もなんとかしてやりたいけど、";
	mes "俺じゃ無理だからな。";
	mes "俺たちの身分では……。";
	close;
}

eclage.gat,126,151,4	script	ポンペ	444,{
	if(ECL_4QUE == 17) {
		viewpoint 2,1,1,0,0xFFFFFF;
		mes "[ポンペ]";
		mes "うおっ！ びっくりした！";
		mes "ん？ あんた誰？";
		next;
		menu "ゴティに紹介されたことを伝える",-;
		mes "[ポンペ]";
		mes "む……。";
		mes "草原で見た、";
		mes "上級ラフィネのことか……。";
		next;
		mes "[ポンペ]";
		mes "俺はあの夜、草原で、その……";
		mes "もよおしてしまってな。";
		mes "用を足せる場所を探していたんだ。";
		next;
		mes "[ポンペ]";
		mes "で、まあ、うろうろしていたら、";
		mes "いきなり黒い影が2体現れたんだ。";
		next;
		mes "[ポンペ]";
		mes "最初に現れたのは^0000cd上級ラフィネ^000000だった。";
		mes "凄い速さであっちの方に";
		mes "消えて行ったんだ。";
		mes "^0000cd羽が大きくて綺麗だった^000000なぁ。";
		mes "うん……。";
		next;
		mes "[ポンペ]";
		mes "で！　その後、すぐだ!!";
		mes "何かが現れて!!!";
		next;
		mes "[ポンペ]";
		mes "最初は大きな塊に見えたが……。";
		mes "そいつもラフィネだった。";
		mes "^0000cd体がとても大きなラフィネ^000000が";
		mes "上級ラフィネを追っていたんだ。";
		next;
		mes "[ポンペ]";
		mes "日も暮れていたからな。";
		mes "真っ暗で誰だったのかは";
		mes "わからなかった。";
		next;
		mes "[ポンペ]";
		mes "向こうも、俺には気づかなかった";
		mes "ようだな。";
		mes "ちょっと用足しのために、";
		mes "茂みの中にいたからな。";
		next;
		mes "[ポンペ]";
		mes "その後、俺は家に帰ったんだけど、";
		mes "まさに家に入ろうとしたその時、";
		mes "草原を揺さぶるほどの大きな悲鳴が";
		mes "聞こえたんだ。";
		mes "本当に恐ろしい悲鳴だった。";
		next;
		mes "[ポンペ]";
		mes "それからしばらくは、怖くて草原に";
		mes "近づくこともできずにいたよ。";
		next;
		mes "[ポンペ]";
		mes "数日前に、やっと草原に";
		mes "行くことが出来たんだが、";
		mes "あっちの方に大きな^0000cd死体^000000が";
		mes "あったんだ！";
		mes "周辺には^0000cd怪しい木の枝^000000も";
		mes "沢山落ちていた！";
		next;
		mes "[ポンペ]";
		mes "ま、まあ、怖くて近くまでは";
		mes "行ってないけどな……。";
		next;
		menu "死体？",-;
		mes "[ポンペ]";
		mes "そう！　死体だ！";
		mes "どうしてかはわからんが、";
		mes "^0000cd大きな羽が破かれていた。";
		mes "俺が追われているのを見た、";
		mes "上級ラフィネの死体^000000だと思うよ。";
		next;
		mes "[ポンペ]";
		mes "はぁ……。";
		mes "どうしてこんなことが……。";
		next;
		mes "[ポンペ]";
		mes "上級ラフィネなら魔力も強いはずだが、";
		mes "あのように簡単に殺されたのを見ると";
		mes "大きいラフィネはそれ以上の力を";
		mes "持っているんだろうな……。";
		next;
		mes "[ポンペ]";
		mes "ああ……。";
		mes "草原を歩き回っていて、";
		mes "あの大きな体をしたラフィネに";
		mes "襲われたらどうしよう!?";
		next;
		mes "[ポンペ]";
		mes "家の子供たちはまだ小さいのに";
		mes "父親の俺が何かされたら困るだろ!?";
		next;
		mes "[ポンペ]";
		mes "それで、草原に行くのが怖いんだよ。";
		mes "あんたも気をつけた方がいいぞ！";
		next;
		mes "[ポンペ]";
		mes "そういえば最近、人を探しに";
		mes "草原へ行ったラフィネが";
		mes "いたんだよ。";
		mes "たしかジラニという名前だったかな。";
		next;
		mes "[ポンペ]";
		mes "あんたが探してるラフィネと";
		mes "何か関係があるのかもしれないが、";
		mes "もし草原で彼女を見かけたら、";
		mes "危ないと注意してやってくれないか？";
		next;
		mes "‐ジラニというラフィネが";
		mes "　花が咲き始めた大地に行ったようだ。";
		mes "　会って話を聞いてみよう‐";
		set ECL_4QUE,18;
		chgquest 14135,14136;
		close;
	}
	mes "[ポンペ]";
	mes "うう……。";
	mes "草原に行くのは怖いなぁ……。";
	close;
}

ecl_fild01.gat,70,285,4	script	ジラニ	611,{
	switch(ECL_4QUE) {
	case 18:
		mes "[ジラニ]";
		mes "あの！　すみません！";
		mes "お忙しいところすみません！";
		mes "少しお話しできますか？";
		next;
		mes "[ジラニ]";
		mes "先ほどから見ていると何かを";
		mes "探しているようですね！";
		mes "違いますか？";
		mes "そうでしょう？";
		next;
		mes "[ジラニ]";
		mes "そこで！";
		mes "ひとつ^0000cd提案^000000があります！";
		next;
		menu "聞くだけなら",-;
		mes "[ジラニ]";
		mes "悪い話ではありません！";
		mes "実は私もこの近くで";
		mes "^0000cd探している人^000000がいます。";
		next;
		mes "[ジラニ]";
		mes "探しているのは、私の父です。";
		mes "少し前から家に帰らなくてですね。";
		mes "それで父の仕事場に";
		mes "行ってみたのですが、";
		mes "「ここ最近は来ていない」";
		mes "な～んて言われまして。";
		next;
		mes "[ジラニ]";
		mes "何も言わずにいなくなる人では";
		mes "ないので、なんかあったのかなーと";
		mes "思って、あっちこっち聞いて";
		mes "まわったんです。";
		next;
		mes "[ジラニ]";
		mes "そうしたら、この辺で父を";
		mes "目撃したという話を耳にして。";
		mes "それで、数日前からこの周辺を";
		mes "探しているんですが、";
		mes "何も見つからなくて……。";
		next;
		menu "捜査を依頼した方がいいのでは？",-;
		mes "[ジラニ]";
		mes "それは、すでにしました！";
		mes "だけど、何の成果もなし、でして。";
		next;
		mes "[ジラニ]";
		mes "そうなるともう、";
		mes "父の身に何かあったのでは！";
		mes "と、心配で心配で。";
		mes "いてもたってもいられず、";
		mes "私が直接探しにここまで";
		mes "来たわけです。";
		next;
		mes "[ジラニ]";
		mes "どうでしょう!?";
		mes "私は父を探すついでに";
		mes "あなたが探すものも探す！";
		mes "同じように、あなたは私が";
		mes "探すものもついでに探す！";
		next;
		mes "[ジラニ]";
		mes "ね？ いい案でしょ？";
		mes "一人で探すより二人で探した方が";
		mes "効率的に決まってます！";
		next;
		menu "どんな感じのお父さんですか？",-;
		mes "[ジラニ]";
		mes "そうですねぇ。";
		mes "父は私と似ている、かな？";
		mes "^0000cd羽が大きくて全体的に";
		mes "赤い色をしています。^000000";
		next;
		mes "[ジラニ]";
		mes "名前は^0000cdムワディリカ^000000と言います。";
		next;
		menu "ムワディリカ？",-;
		mes "[ジラニ]";
		mes "？";
		mes "どうかしましたか？";
		mes "ひょっとして、何かご存じで!?";
		next;
		menu "私が探している人と同じです",-;
		mes "[ジラニ]";
		mes "なんと～!!";
		mes "え、え？　本当に？";
		mes "うわ～、こんな偶然ってあるんだぁ！";
		next;
		mes "[ジラニ]";
		mes "まあ、";
		mes "お父さんの足取りをたどると";
		mes "ここに行きつくから、";
		mes "ありえない話じゃないか！";
		next;
		mes "[ジラニ]";
		mes "でも、";
		mes "あなたはどうしてお父さんを";
		mes "探しているの？";
		next;
		mes "[ジラニ]";
		mes "ううん！ この話は後でにしよう！";
		mes "あなたもお父さんを";
		mes "探しているのなら、";
		mes "話しが早いわね！";
		mes "一緒にお父さんを探そ～!!";
		next;
		mes "[ジラニ]";
		mes "じゃ、何か見つけたら";
		mes "ここに集合ね！";
		next;
		mes "[ジラニ]";
		mes "がんばろ～！";
		mes "えいえいおー!!";
		next;
		mes "‐花が咲き始めた大地で";
		mes "　ムワディリカを探そう‐";
		set ECL_4QUE,19;
		chgquest 14136,14137;
		close;
	case 19:
		mes "[ジラニ]";
		mes "何か見つかったかな？";
		mes "何か見つけたら";
		mes "ここに集合しましょ！";
		next;
		mes "[ジラニ]";
		mes "がんばろ～！";
		mes "えいえいおー!!";
		close;
	case 20:
		mes "[ジラニ]";
		mes "何か見つかったかな？";
		next;
		mes "[ジラニ]";
		mes "こっちは何も……。";
		mes "うぅ、役に立たなくて";
		mes "ごめんなさい……。";
		next;
		if(countitem(6548) < 1) {
			mes "[ジラニ]";
			mes "ん？";
			mes "どうしました？";
			next;
			mes "["+strcharinfo(0)+"]";
			mes "あれ？ どこにあるんだ？";
			mes "落としたのかな？";
			close;
		}
		mes "‐草原で見た死体のことを伝え、";
		mes "　拾って来たラフィネの羽の欠片を";
		mes "　見せた‐";
		next;
		mes "[ジラニ]";
		mes "……え？";
		mes "あ、あ……これは……。";
		next;
		mes "[ジラニ]";
		mes "これは……たしかにお父さんの……。";
		mes "どうして……どういうことなの……？";
		next;
		menu "一緒にお父さんのところに行こうか？",-;
		mes "‐混乱した様子のジラニが、";
		mes "　一つ大きな深呼吸をした‐";
		next;
		mes "[ジラニ]";
		mes "………。";
		next;
		mes "[ジラニ]";
		mes "ありがとう。";
		mes "でも、大丈夫です。";
		mes "私ひとりで行きます。";
		next;
		mes "[ジラニ]";
		mes "その前に、聞いてもいいですか？";
		mes "あなたはどうして私の父を";
		mes "探していたのですか？";
		next;
		mes "‐ウフルの研究の話を";
		mes "　教えてあげた‐";
		next;
		mes "[ジラニ]";
		mes "お父さんがそんな研究を……？";
		mes "最近何か一所懸命に研究を";
		mes "していたことは知っていたけど……。";
		next;
		mes "[ジラニ]";
		mes "ああ！　いったいどうして！";
		mes "誰が……そのようなことを……。";
		mes "あの優しいお父さんを……。";
		next;
		mes "‐ジラニは懸命に";
		mes "　涙をこらえている‐";
		next;
		mes "[ジラニ]";
		mes "ウフル様に会って";
		mes "父のことを伝えてください。";
		next;
		mes "[ジラニ]";
		mes "父と一緒に研究をしていた方、";
		mes "そして父の研究の犠牲になって";
		mes "しまった方……。";
		mes "父のことを知らせてあげないと";
		mes "いけません。";
		next;
		if(checkitemblank() == 0) {
			mes "[ジラニ]";
			mes "お父さんを見つけてくれた";
			mes "お礼をしたいのですが、";
			mes "荷物の種類が多いようです。";
			mes "種類数を減らしてきてもらえますか？";
			close;
		}
		mes "[ジラニ]";
		mes "お父さんを見つけてくれて";
		mes "ありがとうございました……。";
		mes "お礼というほどの物ではありませんが、";
		mes "受け取ってください。";
		delitem 6548,1;
		set ECL_4QUE,21;
		chgquest 14138,14139;
		getexp 100000,0;
		getitem 617,1;
		close;
	case 21:
	case 22:
		mes "[ジラニ]";
		mes "お父さん……。";
		close;
	case 23:
		mes "[ジラニ]";
		mes "何かご用ですか？";
		next;
		menu "お父さんの羽の欠片が必要です。",-;
		if(countitem(6548) > 0) {
			mes "[ジラニ]";
			mes "手に持っているのが";
			mes "お父さんの羽の欠片では";
			mes "ありませんか？";
			close;
		}
		mes "[ジラニ]";
		mes "お父さんの羽の欠片をどうして……。";
		next;
		mes "‐ウフルの話を少し聞かせてやる‐";
		next;
		mes "[ジラニ]";
		mes "そうですか……。";
		mes "お父さんとの研究で……。";
		next;
		mes "[ジラニ]";
		mes "では、差し上げます。";
		mes "多分、お父さんもそれを";
		mes "望んでいるでしょう。";
		next;
		if(checkitemblank() == 0) {
			mes "[ジラニ]";
			mes "お父さんの羽の欠片を";
			mes "差し上げたいのですが、";
			mes "荷物の種類が多いようです。";
			mes "種類数を減らしてきてもらえますか？";
			close;
		}
		mes "[ジラニ]";
		mes "成功することを願うと";
		mes "伝えて下さい。";
		getitem 6548,1;
		close;
	case 24:
		mes "[ジラニ]";
		mes "お父さんに会って来ました。";
		next;
		mes "[ジラニ]";
		mes "私はここでお父さんと";
		mes "もう少し一緒にいます。";
		close;
	default:
		mes "[ジラニ]";
		mes "どこにいるんだろう。";
		mes "この辺だと思うんだけど……。";
		close;
	}
}

ecl_fild01.gat,269,165,4	script	巨大な花のつぼみ	613,{
	if(ECL_4QUE == 19) {
		mes "‐ポンペが話していた";
		mes "　ラフィネの死体のようだ‐";
		next;
		mes "‐羽の形を見ると^0000cdウフルとジラニが";
		mes "　話していた、上級ラフィネの";
		mes "　ムワディリカと姿が一致^000000する‐";
		next;
		mes "‐体のあらゆる所にあるキズを見ると";
		mes "　抵抗の末に^0000cd殺害されたように^000000見える‐";
		next;
		mes "‐体の大きな上級ラフィネが";
		mes "　力で押し切られている。";
		mes "　上級ラフィネより^0000cdさらに体が大きい";
		mes "　人物にやられた^000000ようだ‐";
		next;
		if(checkitemblank() == 0) {
			mes "‐ばらまかれた羽の欠片を";
			mes "　持っていこうとしたが、";
			mes "　アイテムの種類数が多くて";
			mes "　持つことができない。";
			mes "　種類数を減らしてから受け取ろう‐";
			close;
		}
		mes "‐ばらまかれた羽の欠片を集めて";
		mes "　ジラニに報告しよう‐";
		set ECL_4QUE,20;
		chgquest 14137,14138;
		getitem 6548,1;
		close;
	}
	if(ECL_4QUE == 20) {
		if(countitem(6548) < 1) {
			if(checkitemblank() == 0) {
				mes "‐ばらまかれた羽の欠片を";
				mes "　持っていこうとしたが、";
				mes "　アイテムの種類数が多くて";
				mes "　持つことができない。";
				mes "　種類数を減らしてから受け取ろう‐";
				close;
			}
			mes "‐ばらまかれていたラフィネの";
			mes "　羽の欠片を集めた‐";
			getitem 6548,1;
			close;
		}
		mes "‐上級ラフィネの死体だ‐";
		close;
	}
	if(ECL_4QUE == 23) {
		mes "‐死体の周辺に木の枝のように見える、";
		mes "　サファ族の髪の毛がある‐";
		next;
		if(countitem(6545) < 1) {
			if(checkitemblank() == 0) {
				mes "‐サファ族の髪の毛を";
				mes "　持っていこうとしたが、";
				mes "　アイテムの種類数が多くて";
				mes "　持つことができない。";
				mes "　種類数を減らしてから受け取ろう‐";
				close;
			}
			mes "‐研究材料らしいから";
			mes "　少し持って行こう‐";
			getitem 6545,1;
			close;
		}
		mes "‐上級ラフィネの死体だ‐";
		close;
	}
	mes "‐巨大な花のつぼみのような";
	mes "　形をしている正体不明の";
	mes "　物体がある‐";
	close;
}

eclage.gat,156,51,0	script	#hidden_eclage	139,{}

//============================================================
// 妖精たちの事件簿クエスト
//- Registry -------------------------------------------------
// ECL_5QUE -> 0～
//------------------------------------------------------------
ecl_in04.gat,81,106,0	script	#hidden2_eclage	139,2,2,{
	if(ECL_5QUE == 1) {
		mes "[ルーエン]";
		mes "これはいったい";
		mes "何があったの……？";
		next;
		mes "[デイムス]";
		mes "家の中が滅茶苦茶じゃないか……。";
		mes "泥棒が入ったのか？";
		next;
		mes "[ロサ]";
		mes "ネックレス……。";
		mes "私の大事なネックレスがないわ！";
		mes "盗まれたに違いないわ!!";
		next;
		mes "[ポピ]";
		mes "ワンワン!!　ワンワン!!";
		mes "ワン！　ワン！";
		next;
		mes "[ルーエン]";
		mes "ポピ、大人しくして！";
		mes "この人は悪い人じゃないから";
		mes "吠えないでいいのよ。";
		next;
		mes "[ロサ]";
		mes "だから、戸締りの確認をしようと";
		mes "何度も言ったじゃない!!";
		mes "これは家のことを気にしない";
		mes "あなたの責任よ。";
		next;
		mes "[デイムス]";
		mes "おい……。";
		mes "私が悪いっていうのかい？";
		mes "家族全員が無事だっただけでも";
		mes "良かったじゃないか!?";
		next;
		mes "[ロサ]";
		mes "何を言っているのよ？";
		mes "本当にあなたはもう!!";
		next;
		mes "[ルーエン]";
		mes "あ……。";
		mes "あの人、起きたみたい！";
		mes "あの、大丈夫ですか？";
		sc_end SC_BLIND;
		next;
		menu "頭がとても痛いです……",-;
		mes "[ロサ]";
		mes "起きたのなら、さっさと帰って！";
		mes "家に泥棒が入って大変なのに";
		mes "あなたの面倒みている余裕はないわ！";
		next;
		mes "[ルーエン]";
		mes "お母さん、この人だって";
		mes "怪我をしているのに……。";
		next;
		mes "[ルーエン]";
		mes "すみません。";
		mes "あなたが家の前で倒れていたので";
		mes "この部屋に運んだのです。";
		mes "でも、どうしてあんなところに？";
		next;
		menu "何者かに頭を殴られたと答える",-;
		mes "[ルーエン]";
		mes "……そんなことが！";
		mes "あなたを襲った人が";
		mes "泥棒だったのかもしれませんね。";
		next;
		mes "[ロサ]";
		mes "待ちなさい！";
		mes "自分で盗んでおいて";
		mes "嘘をついているかもしれないわ。";
		mes "この人の持ち物を調べてみて！";
		next;
		mes "[デイムス]";
		mes "落ち着くんだ。";
		mes "さっきは追い出そうとして";
		mes "今度は持ち物を調べるなんて";
		mes "さすがに失礼じゃないか。";
		mes "それに、泥棒なら家の前で";
		mes "倒れているなんておかしいだろう？";
		next;
		mes "[ロサ]";
		mes "そういうふうに思わせて";
		mes "私たちを騙しているかもしれないわ。";
		mes "無実だというなら、真犯人を";
		mes "連れて来てごらんなさい！";
		next;
		mes "[ルーエン]";
		mes "……すみません。";
		mes "母は動揺しているみたいなので";
		mes "気にしないでください。";
		next;
		switch(select("真犯人を捜して無実を証明する","ネックレスを探すのを手伝う")) {
		case 1:
			mes "[ルーエン]";
			mes "母の言うことなら";
			mes "気にしないでください。";
			mes "私は、あなたが犯人だとは";
			mes "思っていませんから……。";
			next;
			mes "[ルーエン]";
			mes "もちろん、犯人を捜してくれるなら";
			mes "助かりますけど……。";
			break;
		case 2:
			mes "[ルーエン]";
			mes "そう言ってもらえると、助かります。";
			mes "でも、あまり危険なことは";
			mes "しないでくださいね。";
			mes "また怪我をされても困りますから。";
			break;
		}
		next;
		menu "さっそく捜査を開始する",-,"捜査への協力を求める",-;
		mes "[ルーエン]";
		mes "……そうですか。";
		mes "わかりました。";
		next;
		mes "[ロサ]";
		mes "信用できないわ……。";
		next;
		mes "[デイムス]";
		mes "泥棒を捕まえましょう。";
		next;
		mes "[ルーエン]";
		mes "まずは、何からお話ししましょうか？";
		mes "私でわかることなら";
		mes "お答えしますけど？";
		set ECL_5QUE,2;
		chgquest 9225,9226;
		close;
	}
	end;
}

ecl_in04.gat,78,108,5	script	ルーエン	437,{
	switch(ECL_5QUE) {
	case 1:
		mes "[ルーエン]";
		mes "これはいったい";
		mes "何があったの……？";
		next;
		mes "[デイムス]";
		mes "家の中が滅茶苦茶じゃないか……。";
		mes "泥棒が入ったのか？";
		next;
		mes "[ロサ]";
		mes "ネックレス……。";
		mes "私の大事なネックレスがないわ！";
		mes "盗まれたに違いないわ!!";
		next;
		mes "[ポピ]";
		mes "ワンワン!!　ワンワン!!";
		mes "ワン！　ワン！";
		next;
		mes "[ルーエン]";
		mes "ポピ、大人しくして！";
		mes "この人は悪い人じゃないから";
		mes "吠えないでいいのよ。";
		next;
		mes "[ロサ]";
		mes "だから、戸締りの確認をしようと";
		mes "何度も言ったじゃない!!";
		mes "これは家のことを気にしない";
		mes "あなたの責任よ。";
		next;
		mes "[デイムス]";
		mes "おい……。";
		mes "私が悪いっていうのかい？";
		mes "家族全員が無事だっただけでも";
		mes "良かったじゃないか!?";
		next;
		mes "[ロサ]";
		mes "何を言っているのよ？";
		mes "本当にあなたはもう!!";
		next;
		mes "[ルーエン]";
		mes "あ……。";
		mes "あの人、起きたみたい！";
		mes "あの、大丈夫ですか？";
		next;
		menu "頭がとても痛いです……",-;
		mes "[ロサ]";
		mes "起きたのなら、さっさと帰って！";
		mes "家に泥棒が入って大変なのに";
		mes "あなたの面倒みている余裕はないわ！";
		next;
		mes "[ルーエン]";
		mes "お母さん、この人だって";
		mes "怪我をしているのに……。";
		next;
		mes "[ルーエン]";
		mes "すみません。";
		mes "あなたが家の前で倒れていたので";
		mes "この部屋に運んだのです。";
		mes "でも、どうしてあんなところに？";
		next;
		menu "何者かに頭を殴られたと答える",-;
		mes "[ルーエン]";
		mes "……そんなことが！";
		mes "あなたを襲った人が";
		mes "泥棒だったのかもしれませんね。";
		next;
		mes "[ロサ]";
		mes "待ちなさい！";
		mes "自分で盗んでおいて";
		mes "嘘をついているかもしれないわ。";
		mes "この人の持ち物を調べてみて！";
		next;
		mes "[デイムス]";
		mes "落ち着くんだ。";
		mes "さっきは追い出そうとして";
		mes "今度は持ち物を調べるなんて";
		mes "さすがに失礼じゃないか。";
		mes "それに、泥棒なら家の前で";
		mes "倒れているなんておかしいだろう？";
		next;
		mes "[ロサ]";
		mes "そういうふうに思わせて";
		mes "私たちを騙しているかもしれないわ。";
		mes "無実だというなら、真犯人を";
		mes "連れて来てごらんなさい！";
		next;
		mes "[ルーエン]";
		mes "……すみません。";
		mes "母は動揺しているみたいなので";
		mes "気にしないでください。";
		next;
		switch(select("真犯人を捜して無実を証明する","ネックレスを探すのを手伝う")) {
		case 1:
			mes "[ルーエン]";
			mes "母の言うことなら";
			mes "気にしないでください。";
			mes "私は、あなたが犯人だとは";
			mes "思っていませんから……。";
			next;
			mes "[ルーエン]";
			mes "もちろん、犯人を捜してくれるなら";
			mes "助かりますけど……。";
			break;
		case 2:
			mes "[ルーエン]";
			mes "そう言ってもらえると、助かります。";
			mes "でも、あまり危険なことは";
			mes "しないでくださいね。";
			mes "また怪我をされても困りますから。";
			break;
		}
		next;
		menu "さっそく捜査を開始する",-,"捜査への協力を求める",-;
		mes "[ルーエン]";
		mes "……そうですか。";
		mes "わかりました。";
		next;
		mes "[ロサ]";
		mes "信用できないわ……。";
		next;
		mes "[デイムス]";
		mes "泥棒を捕まえましょう。";
		next;
		mes "[ルーエン]";
		mes "まずは、何からお話ししましょうか？";
		mes "私でわかることなら";
		mes "お答えしますけど？";
		set ECL_5QUE,2;
		chgquest 9225,9226;
		close;
	case 2:
		mes "[ルーエン]";
		mes "何からお話ししましょうか？";
		mes "私でわかることなら";
		mes "お答えします。";
		next;
		menu "事件の前に何をしていたのか聞く",-;
		mes "[ルーエン]";
		mes "私は花が咲き始めた大地で";
		mes "散策をしていました。";
		mes "風を感じながら読書をしたり……。";
		next;
		mes "[ルーエン]";
		mes "風が吹いている場所にいると";
		mes "気分が良くなって";
		mes "家のこととか";
		mes "悩み事から解放されるんです。";
		next;
		menu "怪しい人を見ていないか聞く",-;
		mes "[ルーエン]";
		mes "怪しい人ですか？";
		next;
		mes "[ルーエン]";
		mes "……そういえば！";
		mes "赤くて短い髪の人が";
		mes "早足で歩いているのを見ました。";
		mes "何を急いでいるのかなーって";
		mes "考えていたのを覚えてます。";
		next;
		mes "[ルーエン]";
		mes "あまり見かけない髪の色だったので";
		mes "いったい誰なんだろうって";
		mes "しばらく見ていました。";
		next;
		switch(select("その人について詳しく聞く","知り合いに赤くて短い髪の人がいるか聞く")) {
		case 1:
			mes "[ルーエン]";
			mes "それ以上は……。";
			mes "ちょっとわかりません。";
			mes "男の人だったのか";
			mes "それとも女だったのか……？";
			next;
			mes "[ルーエン]";
			mes "体格は男の人のように";
			mes "見えましたけど……。";
			mes "髪型は女の人のようにも";
			mes "見えましたし……。";
			next;
			mes "[ルーエン]";
			mes "ただ、なんとなく";
			mes "どこかで見たことがあるような";
			mes "気がしました。";
			mes "……記憶違いかもしれませんけど。";
			break;
		case 2:
			mes "[ルーエン]";
			mes "いえ……。";
			mes "あの髪の色、髪型……。";
			mes "見たことがないです。";
			next;
			mes "[ルーエン]";
			mes "少なくとも、私の知人には";
			mes "絶対にいません。";
			mes "これだけは自信をもって断言できます！";
			break;
		}
		next;
		switch(select("倒れている自分を発見したのは誰か聞く","その後、その人を見たか聞く")) {
		case 1:
			mes "[ルーエン]";
			mes "私が帰ってきたとき";
			mes "あなたは家の前に倒れていました。";
			next;
			mes "[ルーエン]";
			mes "死んでいるのかと思って";
			mes "とても驚きましたけれど";
			mes "呼吸してたのに気づいたんです。";
			next;
			mes "[ルーエン]";
			mes "その後、とにかく治療のために";
			mes "家に入れようと思ったのですが";
			mes "家の中が荒らされていて";
			mes "また驚きました……。";
			next;
			mes "[ルーエン]";
			mes "家の中にはお母さんがいたんです。";
			mes "家に戻っていたなら";
			mes "家の前に人が倒れているのを";
			mes "見ているはずですけど……。";
			mes "どうして何もしなかったのかしら？";
			next;
			mes "[ルーエン]";
			mes "たぶん、倒れているあなたを";
			mes "最初に見つけたのは";
			mes "お母さんのはずです。";
			break;
		case 2:
			mes "[ルーエン]";
			mes "いいえ、見たのはその時だけです。";
			mes "帰ってくるときに";
			mes "お父さんの友達のバルミンが";
			mes "家の前を歩いているのを";
			mes "見かけました。";
			next;
			mes "[ルーエン]";
			mes "遠くからだったので";
			mes "よく見えませんでしたけど";
			mes "急いでいる様子でした。";
			next;
			mes "[ルーエン]";
			mes "家の前を通ったなら";
			mes "倒れているあなたを";
			mes "見ているはずですけど";
			mes "そのまま通り過ぎてしまったのかしら？";
			break;
		}
		next;
		menu "ルーエンへの聞き込みを終える",-;
		mes "[ルーエン]";
		mes "どうしてこんなことに……。";
		mes "すみません、少し混乱してしまって";
		mes "細かなことまでは覚えていません。";
		next;
		mes "[ルーエン]";
		mes "お父さん……デイムスにも";
		mes "話を聞いてみてください。";
		set ECL_5QUE,3;
		chgquest 9226,9227;
		setquest 9240;
		close;
	case 3:
		mes "[ルーエン]";
		mes "お父さん……デイムスにも";
		mes "話を聞いてみてください。";
		close;
	case 4:
		mes "[ルーエン]";
		mes "お母さん……ロサにも";
		mes "話を聞いてみてください。";
		close;
	case 5:
		mes "[ルーエン]";
		mes "もう、お話しできることは";
		mes "だいたいお伝えしたと思います。";
		next;
		mes "‐家族への聞き込みは";
		mes "　終わった‐";
		next;
		mes "‐情報を整理してみよう。";
		mes "　まずは……‐";
		next;
		mes "‐ルーエンが赤くて短い髪の人を";
		mes "　見たという。";
		mes "　男か女かもわからないが";
		mes "　見たことがある気がすると";
		mes "　言っていた‐";
		next;
		mes "‐ルーエンは家の前に";
		mes "　人が倒れているのに気づいたが";
		mes "　先に家の中にはロサが";
		mes "　帰ってきていた。";
		mes "　そして……‐";
		next;
		mes "‐デイムスは友達のバルミンに";
		mes "　会いに行っていた。";
		mes "　デイムスはバルミンからの";
		mes "　借金の申し入れを断っていた‐";
		next;
		mes "‐盗まれたネックレスは";
		mes "　デイムスがプレゼントしたもので";
		mes "　ロサはもうひとつ";
		mes "　ネックレスを欲しがっていた‐";
		next;
		mes "‐デイムスはロサが";
		mes "　犯人ではないかと疑っているようだ。";
		mes "　そして……‐";
		next;
		mes "‐ロサは買い物に出かけていた。";
		mes "　家は荒らされていたが";
		mes "　ネックレスが無くなった以外に";
		mes "　変わったところはなかった‐";
		next;
		mes "‐家の中に高価なものはなかった。";
		mes "　盗まれたネックレスは";
		mes "　とても大切にしていたようだが";
		mes "　盗むほどの価値はなかったようだ‐";
		next;
		mes "‐どうして犯人は";
		mes "　高価でもないネックレスを";
		mes "　盗んだのか？‐";
		next;
		mes "‐まだわからないことが多い。";
		mes "　もっと情報を集めよう‐";
		next;
		mes "‐次は、家の中を調べてみよう。";
		mes "　まずは犬のポピからだ‐";
		set ECL_5QUE,6;
		chgquest 9229,9230;
		close;
	case 6:
		mes "[ルーエン]";
		mes "現場検証ですか？ ";
		mes "まずは……そうですね。";
		mes "犬のポピがずっと留守番を";
		mes "していたはずです。";
		close;
	case 7:
		mes "[ルーエン]";
		mes "現場検証ですか？ ";
		mes "次は……そうですね。";
		mes "本棚が荒らされていますね……。";
		close;
	case 8:
		mes "[ルーエン]";
		mes "現場検証ですか？ ";
		mes "次は……そうですね。";
		mes "本棚の横の机の本が";
		mes "破られていますね……。";
		close;
	case 9:
		mes "[ルーエン]";
		mes "現場検証ですか？ ";
		mes "次は……そうですね。";
		mes "ドリンク箱が本棚の脇に";
		mes "ありますけど……。";
		close;
	case 10:
		mes "[ルーエン]";
		mes "現場検証ですか？ ";
		mes "次は……そうですね。";
		mes "荒らされたテーブルに";
		mes "何かあるかもしれませんね。";
		close;
	case 11:
		mes "[ルーエン]";
		mes "現場検証ですか？ ";
		mes "後は……そうですね。";
		mes "犬の収集物くらいでしょうか……。";
		close;
	case 12:
		mes "[ルーエン]";
		mes "家の中の調査が終わったんですね。";
		mes "何かわかりましたか？";
		next;
		mes "[ルーエン]";
		mes "あの……。";
		mes "ネックレスは盗まれたのではなく";
		mes "どこかに落ちていたとか";
		mes "そういうことはないでしょうか？";
		next;
		if(select("鋭い指摘だ","必ず犯人は存在する") == 1) {
			mes "‐確かにネックレスは見つけたけれど";
			mes "　犯人がわかるまでは";
			mes "　秘密にしておこう‐";
			next;
		}
		mes "[ルーエン]";
		mes "……そうですか。";
		mes "ここまで調べていただいて";
		mes "もう十分です。";
		mes "ありがとうございました。";
		next;
		mes "[ロサ]";
		mes "何を言っているの？";
		mes "必ず犯人を捕まえて";
		mes "私のネックレスを";
		mes "取り戻すのよ！";
		next;
		mes "‐パタパタ‐";
		next;
		mes "‐誰かが家に入って来たのか";
		mes "　室内に羽音が響く‐";
		next;
		mes "[クルイアン]";
		mes "お母様～！　お父様～！";
		mes "私です！　クルイアンです！";
		mes "……あっ!!";
		mes "家の中が滅茶苦茶に……？";
		mes "泥棒に入られたんですか!?";
		hideoffnpc "クルイアン#event";
		next;
		mes "[ロサ]";
		mes "あなたにお母様などと";
		mes "呼ばれるいわれはありません！";
		mes "娘に近づくなと";
		mes "何度も言ったわよね？";
		mes "早く家から出て行きなさい！";
		next;
		mes "[クルイアン]";
		mes "お母様!!";
		mes "盗まれたものなら";
		mes "必ず私が探し出します！";
		mes "私を信じてください！";
		next;
		mes "[ロサ]";
		mes "もういいから";
		mes "早く家から出て行きなさい！";
		hideonnpc "クルイアン#event";
		next;
		mes "‐今のがルーエンの恋人だろうか？";
		mes "　ロサには信用されていないみたいだ‐";
		next;
		mes "[ルーエン]";
		mes "クルイアンですか？";
		mes "ええ、お付き合いしています。";
		mes "……彼は、本当はいい人なんです。";
		mes "いつもは、この家を出て";
		mes "少し北西のあたりにいます。";
		next;
		mes "‐これまでの調査で";
		mes "　何人か話を聞いてみたい";
		mes "　人物がでてきた。";
		mes "　まずは、クルイアンに";
		mes "　話を聞きに行こう‐";
		set ECL_5QUE,13;
		delquest 9252;
		delquest 9253;
		delquest 9254;
		delquest 9255;
		delquest 9256;
		delquest 9257;
		delquest 9230;
		setquest 9231;
		setquest 9258;
		close;
	case 13:
		mes "[ルーエン]";
		mes "聞き込みですか？ ";
		mes "クルイアンなら";
		mes "この家を出て少し北西に進んだあたりに";
		mes "いつもいるので";
		mes "話を聞いてあげてください。";
		close;
	case 14:
		mes "[ルーエン]";
		mes "聞き込みですか？ ";
		mes "バルミンさんなら";
		mes "花が咲き始めた大地に";
		mes "いると思います。";
		close;
	case 15:
		mes "[ルーエン]";
		mes "聞き込みですか？ ";
		mes "スピードアップポーションを";
		mes "取り扱っている商人ですか？";
		mes "うーん、商売をするなら";
		mes "街の中だと思いますけど……。";
		close;
	case 16:
		mes "[ルーエン]";
		mes "聞き込みは終わったんですね。";
		mes "何かわかりましたか？";
		next;
		if(select("これから推理します","少し情報を整理します") == 2) {
			mes "[ルーエン]";
			mes "……そうですか。";
			next;
			mes "‐ひと通り関係者に話は聞いた。";
			mes "　準備できたらルーエンに";
			mes "　推理を話そう‐";
			close;
		}
		mes "[ルーエン]";
		mes "えっ……！";
		mes "犯人がわかったのですか？";
		next;
		mes "[ロサ]";
		mes "まあ、本当なの!?";
		next;
		mes "[デイムス]";
		mes "なんと！";
		mes "こんなに早く見つけるとは……。";
		mes "さっそく関係者を集めます。";
		close2;
		set ECL_5QUE,17;
		chgquest 9234,9235;
		warp "ecl_in04.gat",206,195;
		end;
	case 17:
		mes "[ルーエン]";
		mes "みなさんがお待ちです。";
		next;
		if(select("これから推理します","少し情報を整理します") == 2) {
			mes "[ルーエン]";
			mes "……そうですか。";
			next;
			mes "‐ひと通り関係者に話は聞いた。";
			mes "　準備できたらルーエンに";
			mes "　話しかけよう‐";
			close;
		}
		mes "[ルーエン]";
		mes "では、こちらへどうぞ。";
		close2;
		warp "ecl_in04.gat",206,195;
		end;
	case 18:
		mes "[ルーエン]";
		mes "あなたには迷惑をかけてしまって";
		mes "すみませんでした。";
		next;
		mes "[ルーエン]";
		mes "クルイアンがしたことは";
		mes "悪いことですけれど";
		mes "本人も反省しているので、";
		mes "これからは二人で力を合わせて";
		mes "いこうと思います。";
		next;
		mes "[ルーエン]";
		mes "本当に、ありがとうございました。";
		if(checkitemblank() < 3) {
			next;
			mes "[ルーエン]";
			mes "お礼をしようと思ったのですけれど";
			mes "それ以上持てないみたいですね。";
			mes "アイテムの種類数を減らしてから";
			mes "もう一度話しかけてください。";
			close;
		}
		set ECL_5QUE,19;
		chgquest 9236,9237;
		getitem 6081,1;
		getexp 300000,0;
		getexp 0,150000;
		next;
		mes "[ルーエン]";
		mes "お父さん、デイムスも";
		mes "お礼を言いたいそうなので";
		mes "話しかけてあげてください。";
		close;
	case 19:
	case 20:
	case 21:
		mes "[ルーエン]";
		mes "ありがとうございました。";
		mes "お母さんにクルイアンとの交際を";
		mes "認めてもらえるよう";
		mes "二人で力を合わせて";
		mes "いこうと思います。";
		close;
	}
}

ecl_in04.gat,85,110,3	script	デイムス	447,{
	switch(ECL_5QUE) {
	case 2:
		mes "[デイムス]";
		mes "泥棒を捕まえるためなら";
		mes "協力は惜しみませんよ。";
		mes "準備しておきますので";
		mes "先に娘から話を聞いてください。";
		close;
	case 3:
		mes "[デイムス]";
		mes "泥棒を捕まえるためなら";
		mes "協力は惜しみませんよ。";
		next;
		menu "事件の前に何をしていたのか聞く",-;
		mes "[デイムス]";
		mes "私は友人と会っていました。";
		mes "バルミンという名前です。";
		next;
		mes "[デイムス]";
		mes "娘の話……。";
		mes "妻の話や……。";
		mes "世間話もして……。";
		next;
		mes "[デイムス]";
		mes "帰ってきた時には";
		mes "家の中はめちゃくちゃで、";
		mes "妻と娘は呆然としていたし";
		mes "あなたは倒れていました……。";
		next;
		switch(select("友達について聞く","友達とトラブルがなかったか聞く")) {
		case 1:
			mes "[デイムス]";
			mes "特に悪いことをするような";
			mes "人ではありません。";
			next;
			mes "[デイムス]";
			mes "まあ、歳を取っても";
			mes "少し子供のような……。";
			mes "悪く言うのなら、まだ大人に";
			mes "なりきっていない人です。";
			break;
		case 2:
			mes "[デイムス]";
			mes "実は……。";
			mes "その友人が私に";
			mes "お金を貸してほしいと";
			mes "言ってきたことがありました。";
			next;
			mes "[デイムス]";
			mes "貸せるようなお金もありませんでしたし";
			mes "友達同士でお金の貸し借りは";
			mes "良くないと思ったので";
			mes "断ったのですが……。";
			next;
			mes "[デイムス]";
			mes "それ以外には";
			mes "怪しいこともないし";
			mes "悪さをするような人でもありません。";
			break;
		}
		next;
		switch(select("事件について思い当たることを聞く","ネックレスについて聞く")) {
		case 1:
			mes "[デイムス]";
			mes "あまり考えたくはないのですが……。";
			mes "私は妻が怪しいと思っています。";
			mes "最近、不満を溜めこんでいたようなので";
			next;
			mes "[デイムス]";
			mes "何を話しても";
			mes "ダメだ、いやだなどと";
			mes "ちゃんとした理由もなく";
			mes "私に反対すること自体が";
			mes "目的になっているようでした……。";
			next;
			mes "[デイムス]";
			mes "最近はあれこれ買ってくれと";
			mes "言ってくることも増えたし";
			mes "すねたり、怒ったりすることも多くて";
			mes "まったく……疲れます……。";
			break;
		case 2:
			mes "[デイムス]";
			mes "盗まれたのは";
			mes "妻のネックレスですね……。";
			mes "若い頃、私が買って";
			mes "プレゼントしたものです。";
			next;
			mes "[デイムス]";
			mes "泥棒に入られたと聞いた時は";
			mes "大変だと思いましたが、";
			mes "ネックレスが盗まれたと聞いて";
			mes "以前に妻と話したことを";
			mes "思い出しました。";
			next;
			mes "[デイムス]";
			mes "ネックレスをもうひとつ";
			mes "買ってほしいと言われたのです。";
			mes "妻の次の誕生日に買うと";
			mes "約束したのですが";
			mes "妻は不満そうでした。";
			next;
			mes "[デイムス]";
			mes "まさかとは思いますが";
			mes "ネックレスを盗られたことにすれば";
			mes "新しいものを私が買い与えると";
			mes "考えたのではないかと……。";
			mes "私の考えすぎでしょうか？";
			break;
		}
		next;
		menu "デイムスへの聞き込みを終える",-;
		mes "[デイムス]";
		mes "もし、家族のせいで";
		mes "あなたが怪我をしたのなら";
		mes "本当に申し訳ありません。";
		next;
		mes "[デイムス]";
		mes "妻のロサにも聞いてみてください。";
		mes "……ただ、思い込みで";
		mes "変なことを言ったり";
		mes "嘘をついたりするかもしれません。";
		set ECL_5QUE,4;
		chgquest 9227,9228;
		setquest 9247;
		close;
	case 4:
		mes "[デイムス]";
		mes "妻のロサにも聞いてみてください。";
		mes "……ただ、思い込みで";
		mes "変なことを言ったり";
		mes "嘘をついたりするかもしれません。";
		close;
	case 5:
		mes "[デイムス]";
		mes "もう家族全員の話は";
		mes "聞き終わりましたか？";
		close;
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "[デイムス]";
		mes "現場検証というわけですか。";
		mes "すっかり犯人に荒らされてしまって";
		mes "困ったものです。";
		close;
	case 13:
		mes "[デイムス]";
		mes "クルイアンですか？";
		mes "娘との交際のことで";
		mes "妻に反対されていますね。";
		mes "たぶん、街にいると思いますよ。";
		close;
	case 14:
		mes "[デイムス]";
		mes "バルミンですか？";
		mes "花が咲き始めた大地で";
		mes "狩りをしているはずです。";
		close;
	case 15:
		mes "[デイムス]";
		mes "スピードアップポーションを";
		mes "扱っている商人ですか？";
		mes "さあ……とりあえず";
		mes "街の中を探してみては？";
		close;
	case 16:
	case 17:
		mes "[デイムス]";
		mes "何かわかりましたか？";
		close;
	case 18:
		mes "[デイムス]";
		mes "ルーエンが感謝していました。";
		mes "話しかけてあげてください。";
		close;
	case 19:
		mes "[デイムス]";
		mes "事件の真相を知って";
		mes "少し複雑な気分です。";
		next;
		mes "[デイムス]";
		mes "これからのことは";
		mes "家族で話し合って";
		mes "決めようと思います。";
		next;
		mes "[デイムス]";
		mes "あなたには感謝しています。";
		mes "ありがとうございました。";
		if(checkitemblank() < 3) {
			next;
			mes "[デイムス]";
			mes "お礼をしようと思いましたが";
			mes "それ以上持てないようですね。";
			mes "アイテムの種類数を減らしてから";
			mes "もう一度話しかけてください。";
			close;
		}
		set ECL_5QUE,20;
		chgquest 9237,9238;
		getitem 607,1;
		getexp 300000,0;
		getexp 0,150000;
		next;
		mes "[デイムス]";
		mes "そうそう。";
		mes "ロサも何か用意していたみたいです。";
		mes "話しかけてやってください。";
		close;
	case 20:
	case 21:
		mes "[デイムス]";
		mes "お世話になりました。";
		mes "これからのことは";
		mes "家族で話し合って";
		mes "決めようと思います。";
		close;
	default:
		mes "[デイムス]";
		mes "家に泥棒が入るのは";
		mes "初めてのことだ……。";
		close;
	}
}

ecl_in04.gat,77,104,5	script	ロサ	520,{
	switch(ECL_5QUE) {
	case 2:
	case 3:
		mes "[ロサ]";
		mes "あなたが犯人ではないというの？";
		mes "……わかったわ。";
		mes "協力してもいいけど";
		mes "少し落ち着くまで待って。";
		mes "先に娘と主人に話を聞いておいて。";
		close;
	case 4:
		mes "[ロサ]";
		mes "ネックレスのために";
		mes "私でわかることなら話します。";
		mes "あなたのことを";
		mes "信用したわけではないわよ！";
		next;
		menu "事件の前に何をしていたのか聞く",-;
		mes "[ロサ]";
		mes "近くのお店へ";
		mes "買い物に行っていたわ。";
		next;
		mes "[ロサ]";
		mes "特にいいものはなくて";
		mes "そのまま家に帰って来たけど……。";
		mes "それだけよ。";
		next;
		switch(select("家の前で倒れていた人を無視した理由を聞く","家の中で気づいたことについて聞く")) {
		case 1:
			mes "[ロサ]";
			mes "家の前であなたが倒れているのを見て";
			mes "とても驚いたわ。";
			mes "助けようと思ったけど";
			mes "慌ててしまって";
			mes "私ひとりではどうしていいか";
			mes "わからなかったの！";
			next;
			mes "[ロサ]";
			mes "それで、主人か娘が帰っていないかと";
			mes "家の中に入ってみたら";
			mes "部屋が荒らされていて……。";
			next;
			mes "[ロサ]";
			mes "家の前には倒れている人！";
			mes "家の中は荒れ放題！";
			mes "私は恐怖で気が動転して";
			mes "立ち尽くすことしかできなかったわ！";
			set '@str$,"ネックレス以外に無くなったものがないか聞く";
			break;
		case 2:
			mes "[ロサ]";
			mes "泥棒に荒らされたせいで";
			mes "散らかっていたけど";
			mes "ネックレス以外に";
			mes "なくなった物はないみたい……。";
			next;
			mes "[ロサ]";
			mes "どうして私の大切な";
			mes "ネックレスを……？";
			mes "役に立たないあの犬でも";
			mes "連れて行けばいいのに！";
			next;
			mes "[ロサ]";
			mes "……。";
			mes "…………。";
			mes "ごめんなさい。";
			mes "無関係なあなたに";
			mes "怒ってしまって……。";
			next;
			mes "[ロサ]";
			mes "そうね……。";
			mes "やっぱり、他に変わったところは";
			mes "なかったわ。";
			set '@str$,"本当に他に無くなったものがないか聞く";
			break;
		}
		next;
		switch(select("犯人の心当たりを聞く",'@str$)) {
		case 1:
			mes "[ロサ]";
			mes "心当たりと言われても……。";
			mes "主人はあまり気が利かないけど";
			mes "悪い人ではないのよ。";
			mes "娘は恋人と別れるように言っても";
			mes "聞かないけど、優しい子だわ……。";
			next;
			mes "[ロサ]";
			mes "この家に高価なものが";
			mes "あるわけでもないし……。";
			mes "唯一、私が大切にしていた";
			mes "ネックレスを……！";
			next;
			mes "[ロサ]";
			mes "家族なら、私がどれだけ";
			mes "ネックレスを大事にしていたか";
			mes "わかっているはず！";
			mes "だから、家族以外の誰かが";
			mes "盗んだに違いないわ!!";
			break;
		case 2:
			mes "[ロサ]";
			mes "散らかっていてよくわからないけれど";
			mes "他に盗られて困るような";
			mes "金目のものはないわ。";
			next;
			mes "[ロサ]";
			mes "あのネックレスも";
			mes "それほど高価なものではないの。";
			mes "でも、私にとっては";
			mes "とても大切なものなの……。";
			next;
			mes "[ロサ]";
			mes "見た目も地味だし";
			mes "どうして、盗まれたのかしら……？";
			mes "まったくわからないわ。";
			break;
		}
		next;
		menu "ロサへの聞き込みを終える",-;
		mes "[ロサ]";
		mes "私のネックレス……。";
		mes "主人に買ってもらった";
		mes "大切なものなの……。";
		next;
		mes "‐家族への聞き込みは";
		mes "　ひと通り行った。";
		mes "　一度情報を整理しよう‐";
		set ECL_5QUE,5;
		chgquest 9228,9229;
		setquest 9251;
		close;
	case 5:
		mes "[ロサ]";
		mes "私の知っていることは";
		mes "お話ししましたわ。";
		close;
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "[ロサ]";
		mes "こんなに散らかされて";
		mes "片付けるのが大変だわ！";
		close;
	case 13:
		mes "[ロサ]";
		mes "クルイアンですか？";
		mes "娘との交際を認めるつもりは";
		mes "ありません！";
		close;
	case 14:
		mes "[ロサ]";
		mes "バルミンさんですか？";
		mes "主人の友人ですわね。";
		close;
	case 15:
		mes "[ロサ]";
		mes "スピードアップポーションを";
		mes "扱っている商人ですか？";
		mes "……私が行くお店では";
		mes "売っていませんわね。";
		close;
	case 16:
	case 17:
		mes "[ロサ]";
		mes "ネックレスは見つかったのかしら？";
		close;
	case 18:
		mes "[ロサ]";
		mes "ネックレスを見つけてくれて";
		mes "ありがとう！";
		mes "まずはルーエンに話しかけて。";
		close;
	case 19:
		mes "[ロサ]";
		mes "ネックレスを見つけてくれて";
		mes "ありがとう！";
		mes "デイムスがお礼を言いたいそうよ。";
		mes "主人と話している間に";
		mes "私も何か用意するわ。";
		mes "後でまた来てちょうだい。";
		close;
	case 20:
		mes "[ロサ]";
		mes "クルイアンのことは第一印象から";
		mes "好きになれなくて……。";
		mes "今回の事件のことで";
		mes "思った通りだったって……。";
		next;
		mes "[ロサ]";
		mes "それに、娘に裏切られたような";
		mes "気分にもなって、とても辛かったわ。";
		next;
		mes "[ロサ]";
		mes "……でも、クルイアンが";
		mes "お酒も遊びもやめて";
		mes "まじめになった時に";
		mes "もう少しちゃんと";
		mes "話を聞いてあげていれば……。";
		next;
		mes "[ロサ]";
		mes "こんなことにはならなかったかも";
		mes "しれないと";
		mes "……そんな気もするの。";
		next;
		mes "[ロサ]";
		mes "あなたにも、最初に酷いことを言って";
		mes "ごめんなさいね。";
		mes "そして、ネックレスを見つけてくれて";
		mes "ありがとう。";
		if(checkitemblank() < 3) {
			next;
			mes "[ロサ]";
			mes "お礼をしようと思ったけど";
			mes "それ以上持てないようね。";
			mes "アイテムの種類数を減らしてから";
			mes "もう一度話しかけてね。";
			close;
		}
		set ECL_5QUE,21;
		chgquest 9238,9239;
		getitem 6081,1;
		getitem 607,1;
		getexp 300000,0;
		getexp 0,150000;
		next;
		mes "[ロサ]";
		mes "クルイアンも反省したみたいね。";
		mes "あなたにお礼が言いたいそうよ。";
		mes "会いに行ってあげなさい。";
		mes "……だからといって、";
		mes "娘との交際を認めるわけでは";
		mes "ありませんけどね。";
		close;
	case 21:
		mes "[ロサ]";
		mes "ネックレスを見つけてくれて";
		mes "ありがとう。";
		close;
	default:
		mes "[ロサ]";
		mes "家の中に泥棒が入るなんて";
		mes "想像もしていなかったわ!!";
		close;
	}
}

ecl_in04.gat,80,103,3	script	クルイアン#event	442,{
	mes "[クルイアン]";
	mes "これはいったい……？";
	close;
OnInit:
	hideonnpc "クルイアン#event";
	end;
}

eclage.gat,164,102,3	script	クルイアン	442,{
	switch(ECL_5QUE) {
	case 0:
		mes "[クルイアン]";
		mes "ルーエン……。";
		mes "もうすぐ、認めてもらうよ。";
		close;
	case 1:
	case 2:
	case 3:
	case 4:
		mes "[クルイアン]";
		mes "どうしよう……。";
		mes "こんなつもりじゃなかったのに。";
		close;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "[クルイアン]";
		mes "お母様のネックレスは";
		mes "必ず私が見つけてみせる！";
		close;
	case 13:
		mes "[クルイアン]";
		mes "あなたは……？";
		mes "ああ、ルーエンの家にいた";
		mes "人間ですね。";
		next;
		mes "[クルイアン]";
		mes "ネックレスなら";
		mes "必ず私が見つけてみせます！";
		next;
		switch(select("ルーエンのことについて聞く","ネックレスのことをどこで知ったか聞く")) {
		case 1:
			mes "[クルイアン]";
			mes "ルーエンのことは";
			mes "とても大切にしています。";
			mes "お母様に交際を反対されていますけど";
			mes "必ず、認めてもらうつもりです！";
			next;
			mes "[クルイアン]";
			mes "たしかに、ルーエンと出会ったころ";
			mes "私はお酒や遊びが好きな";
			mes "不まじめな男に見えたかもしれません。";
			next;
			mes "[クルイアン]";
			mes "でも、交際を認めてもらうために";
			mes "最近はまじめにしています。";
			break;
		case 2:
			mes "[クルイアン]";
			mes "ん？";
			mes "ルーエンの家に行ったときですよ。";
			mes "あなたもその場にいたはずです。";
			next;
			mes "[クルイアン]";
			mes "ネックレスの話は出なかったって？";
			mes "そんなことはないと思いますけど……。";
			next;
			mes "[クルイアン]";
			mes "……細かな会話の内容まで";
			mes "覚えてはいませんけど、";
			mes "たしかに、その時聞いたはずです。";
			break;
		}
		next;
		menu "事件の前に何をしていたのか聞く",-;
		mes "[クルイアン]";
		mes "アリバイ調査というやつですか？";
		mes "いいですよ。";
		next;
		mes "[クルイアン]";
		mes "今日は花が咲き始めた大地で";
		mes "モンスターを倒していました。";
		mes "いい運動になりますし";
		mes "モンスターが増えて困っている";
		mes "ところでしたし。";
		next;
		mes "[クルイアン]";
		mes "帰ってくるときに";
		mes "お父様の友人のバルミンを見ました。";
		mes "そういえば、";
		mes "なにか急いでいる様子だったかな……？";
		next;
		mes "[クルイアン]";
		mes "その後、ルーエンに会おうと思って";
		mes "彼女の家に行ったんです。";
		mes "……あんなことになっていて";
		mes "驚きましたけど……。";
		next;
		mes "[クルイアン]";
		mes "そうそう。";
		mes "これはモンスターを倒している時に";
		mes "手に入れた戦利品です。";
		mes "よかったら、ひとつどうぞ。";
		if(checkitemblank() < 3) {
			next;
			mes "[クルイアン]";
			mes "……と思ったら";
			mes "それ以上持てないみたいですね。";
			mes "荷物の種類数を減らしてから";
			mes "また来てください。";
			close;
		}
		getitem 645,1;
		set ECL_5QUE,14;
		chgquest 9231,9232;
		setquest 9259;
		next;
		mes "[クルイアン]";
		mes "そのスピードアップポーションが";
		mes "私のアリバイを証明してくれます。";
		mes "……これでいいでしょう？";
		next;
		mes "‐念のため、クルイアンの";
		mes "　アリバイが正しいか";
		mes "　花が咲き始めた大地で";
		mes "　モンスターを倒して";
		mes "　スピードアップポーションを";
		mes "　入手できるか確かめよう‐";
		next;
		mes "‐メンブリッツを5体と";
		mes "　ペタルを30体ほど倒せばいいだろう‐";
		next;
		mes "‐花が咲き始めた大地には";
		mes "　デイムスの友人のバルミンも";
		mes "　いるはずだ。";
		mes "　もしかしたら";
		mes "　クルイアンについて";
		mes "　何か聞けるかもしれない‐";
		next;
		mes "‐モンスターを討伐したら";
		mes "　花が咲き始めた大地にいる";
		mes "　バルミンを探して話しかけよう‐";
		close;
	case 14:
		mes "[クルイアン]";
		mes "そのスピードアップポーションが";
		mes "私のアリバイを証明してくれます。";
		next;
		mes "‐念のため、クルイアンの";
		mes "　アリバイが正しいか";
		mes "　花が咲き始めた大地で";
		mes "　モンスターを倒して";
		mes "　スピードアップポーションを";
		mes "　入手できるか確かめよう‐";
		next;
		mes "‐メンブリッツを5体と";
		mes "　ペタルを30体ほど倒せばいいだろう‐";
		next;
		mes "‐花が咲き始めた大地には";
		mes "　デイムスの友人のバルミンも";
		mes "　いるはずだ。";
		mes "　もしかしたら";
		mes "　クルイアンについて";
		mes "　何か聞けるかもしれない‐";
		next;
		mes "‐モンスターを討伐したら";
		mes "　花が咲き始めた大地にいる";
		mes "　バルミンを探して話しかけよう‐";
		close;
	case 15:
	case 16:
		mes "[クルイアン]";
		mes "お母様のネックレスは";
		mes "必ず私が見つけてみせる！";
		next;
		mes "‐犯人がわかるまでの間は";
		mes "　ネックレスが見つかったことは";
		mes "　伏せておこう‐";
		close;
	case 17:
		mes "[クルイアン]";
		mes "何かわかりましたか？";
		mes "もし、あなたが解決できなくても";
		mes "お母様のネックレスは";
		mes "私が探し出します！";
		next;
		mes "‐犯人がわかるまでの間は";
		mes "　ネックレスが見つかったことは";
		mes "　伏せておこう‐";
		close;
	case 18:
	case 19:
	case 20:
		mes "[クルイアン]";
		mes "あなたにはご迷惑をおかけしました。";
		mes "それはそうと";
		mes "ルーエンの家に行かなくて";
		mes "いいのですか？";
		close;
	case 21:
		mes "[クルイアン]";
		mes "あなたさえいなければ";
		mes "何もかもうまくいったのに……。";
		next;
		mes "[クルイアン]";
		mes "……というのは嘘です。";
		mes "自分がどれだけ愚かなことを";
		mes "したのか、わかっています。";
		next;
		mes "[クルイアン]";
		mes "幸い、ルーエンには";
		mes "縁を切られないようなので";
		mes "今度こそ彼女を幸せにできるよう";
		mes "がんばるつもりです。";
		next;
		mes "[クルイアン]";
		mes "あなたにはご迷惑をおかけしました。";
		mes "あと、ネックレスを";
		mes "見つけていただいて";
		mes "ありがとうございます。";
		if(checkitemblank() < 3) {
			next;
			mes "[クルイアン]";
			mes "お礼をしようと思ったのですが";
			mes "それ以上持てないようですね。";
			mes "アイテムの種類数を減らしてから";
			mes "もう一度話しかけてください。";
			close;
		}
		set ECL_5QUE,22;
		chgquest 9239,9262;
		getitem 608,1;
		getexp 300000,0;
		getexp 0,150000;
		next;
		mes "[クルイアン]";
		mes "動転してたとはいえ、バルミンさんに";
		mes "疑いの目を向けるようなことまで";
		mes "言ってしまって、恥ずかしいです。";
		mes "バルミンさんに";
		mes "今度クルイアンがお詫びに行くと";
		mes "伝えてください。";
		close;
	case 22:
		mes "[クルイアン]";
		mes "動転してたとはいえ、バルミンさんに";
		mes "疑いの目を向けるようなことまで";
		mes "言ってしまって、恥ずかしい限りです。";
		mes "もしバルミンさんのところに行ったら";
		mes "今度クルイアンがお詫びに行くと";
		mes "伝えてください。";
		close;
	case 23:
		mes "[クルイアン]";
		mes "今度こそルーエンを幸せにできるよう";
		mes "がんばるつもりです。";
		close;
	}
}

ecl_fild01.gat,98,299,5	script	バルミン	461,{
	switch(ECL_5QUE) {
	case 14:
		if(!(checkquest(9259) & 0x4)) {
			mes "[バルミン]";
			mes "何か用かね？";
			mes "すまないが、今はちょっと忙しい。";
			mes "モンスターを狩っているんだ。";
			mes "君も狩りの途中のようだけど……。";
			mes "狩りが終わってから";
			mes "もう一度来てくれ。";
			close;
		}
		mes "‐この人は、デイムスの友達の";
		mes "　バルミンかな？";
		mes "　ルーエンとクルイアンが";
		mes "　街で見かけたと言っていた‐";
		next;
		mes "[バルミン]";
		mes "おや、あなたは？";
		mes "……なんと、デイムスの家で";
		mes "事件ですと！";
		next;
		menu "事件の前に何をしていたのか聞く",-;
		mes "[バルミン]";
		mes "今日は朝からここにいました。";
		mes "モンスターを倒して";
		mes "戦利品をお金に換えるんです。";
		next;
		mes "[バルミン]";
		mes "一度デイムスがやって来て";
		mes "世間話をしました。";
		mes "その時は特に変わった様子は";
		mes "なかったのですが……。";
		mes "家に帰って驚いたでしょうね……。";
		next;
		switch(select("デイムスの家に行ったか聞く","クルイアンと会ったか聞く")) {
		case 1:
			mes "[バルミン]";
			mes "いや、さっきも言った通り";
			mes "今日はずっとここにいましたよ。";
			next;
			mes "‐たしかルーエンが";
			mes "　家の前を通るバルミンを";
			mes "　遠目に見たと言っていたはずだ。";
			mes "　見間違いか、それともどちらかが";
			mes "　嘘をついているのだろうか？‐";
			break;
		case 2:
			mes "[バルミン]";
			mes "いえ、デイムスがやって来た以外には";
			mes "誰も見かけていませんな。";
			next;
			mes "‐クルイアンは狩りの帰りに";
			mes "　バルミンを見たと言っていた。";
			mes "　気づかなかっただけか、";
			mes "　それとも、どちらかが";
			mes "　嘘をついているのだろうか？‐";
			break;
		}
		next;
		mes "‐この付近での狩りの戦利品として";
		mes "　スピードアップポーションが";
		mes "　入手できたと";
		mes "　クルイアンは言っていた‐";
		next;
		menu "スピードアップポーションについて聞く",-;
		mes "[バルミン]";
		mes "スピードアップポーション……？";
		mes "ここのモンスターは";
		mes "そんなものは持ってないぞ。";
		mes "君もさっきまで狩りをしていたなら";
		mes "わかるだろう？";
		next;
		mes "[バルミン]";
		mes "もし手に入れるとしたら";
		mes "商人から買うとか？";
		mes "……だけど、このあたりで";
		mes "スピードアップポーションを";
		mes "扱っている商人なんていたかな？";
		next;
		mes "[バルミン]";
		mes "少しはお役にたてましたかな？";
		mes "とにかく、友人のために";
		mes "必ず泥棒を捕まえてください。";
		next;
		mes "‐バルミンの供述は";
		mes "　クルイアンの言っていたことと";
		mes "　矛盾している‐";
		next;
		switch(select("バルミンが嘘をついている","クルイアンが嘘をついている")) {
		case 1:
			mes "‐クルイアンが言ったように";
			mes "　この付近での狩りの戦利品として";
			mes "　スピードアップポーションが";
			mes "　入手できるなら、バルミンが";
			mes "　嘘をついているということになる‐";
			next;
			mes "‐ただ、実際にモンスターを倒しても";
			mes "　スピードアップポーションは";
			mes "　入手できなかった……‐";
			break;
		case 2:
			mes "‐このあたりのモンスターから";
			mes "　スピードアップポーションを";
			mes "　入手することはできなかった‐";
			break;
		}
		next;
		mes "‐スピードアップポーションを";
		mes "　取り扱っている商人がいないか";
		mes "　探してみよう‐";
		set ECL_5QUE,15;
		delquest 9232;
		delquest 9259;
		setquest 9233;
		close;
	case 15:
		mes "[バルミン]";
		mes "このあたりで";
		mes "スピードアップポーションを";
		mes "扱っている商人なんていたかな……？";
		next;
		mes "‐スピードアップポーションを";
		mes "　取り扱っている商人がいないか";
		mes "　探してみよう‐";
		close;
	case 16:
	case 17:
		mes "[バルミン]";
		mes "友人のためにも";
		mes "早く事件を解決してください。";
		close;
	case 18:
	case 19:
	case 20:
		mes "[バルミン]";
		mes "おや、あなたですか。";
		mes "デイムス達のところにいなくて";
		mes "いいのですか？";
		close;
	case 21:
		mes "[バルミン]";
		mes "おや、あなたですか。";
		mes "クルイアンは若いので";
		mes "まだまだやり直せるでしょう。";
		mes "彼なら、街にいると思いますよ。";
		close;
	case 22:
		mes "[バルミン]";
		mes "人間の探偵さんではありませんか。";
		mes "クルイアンは若いので";
		mes "まだまだやり直せるでしょう。";
		next;
		mes "[バルミン]";
		mes "友人の問題を解決してくれて";
		mes "ありがとうございました。";
		next;
		mes "[バルミン]";
		mes "狩りをした戦利品くらいしか";
		mes "持っていませんが";
		mes "受け取ってください。";
		if(checkitemblank() < 3) {
			next;
			mes "[バルミン]";
			mes "……と思ったのですが";
			mes "それ以上持てないようですね。";
			mes "アイテムの種類数を減らしてから";
			mes "もう一度話しかけてください。";
			close;
		}
		set ECL_5QUE,23;
		chgquest 9262,201610;
		getitem 6558,20;
		getitem 6081,25;
		getexp 3800000,0;
		getexp 0,1900000;
		next;
		mes "[バルミン]";
		mes "それにしても";
		mes "みごとな推理でしたな。";
		mes "これからの冒険に";
		mes "幸運があるように";
		mes "祈っておりますよ。";
		close;
	case 23:
		mes "[バルミン]";
		mes "これからの冒険に";
		mes "幸運があるように";
		mes "祈っておりますよ。";
		close;
	default:
		mes "[バルミン]";
		mes "すまないが、今はちょっと忙しい。";
		mes "モンスターを狩っているんだ。";
		close;
	}
}

eclage.gat,222,131,3	script	放浪商人	807,{
	switch(ECL_5QUE) {
	case 15:
		mes "‐人間の商人だ。";
		mes "　昼間から酒を飲んでいるのか";
		mes "　少し匂う……‐";
		next;
		mes "[放浪商人]";
		mes "やあ、いらっしゃい～。";
		mes "いい商品が入荷してるよ～。";
		next;
		switch(select("赤い髪の男だ","ドリンク箱の酒瓶がなくなっていた")) {
		case 1:
			mes "‐そういえば、ルーエンが";
			mes "　赤い髪の人物を見たと";
			mes "　言っていた……‐";
			break;
		case 2:
			mes "‐そういえば、家の中の";
			mes "　酒瓶が入った箱が";
			mes "　荒らされていた……‐";
			break;
		}
		next;
		mes "‐念のため";
		mes "　話を聞いてみよう‐";
		next;
		mes "[放浪商人]";
		mes "うん？　何をしているかって？";
		mes "もちろん～。";
		mes "商売をしているんだよ～。";
		next;
		mes "[放浪商人]";
		mes "今なら1回10000Zenyで";
		mes "スピードアップポーションが";
		mes "当たるくじを販売しているよ～！";
		next;
		mes "[放浪商人]";
		mes "運が良ければ、1回で2個の";
		mes "スピードアップポーションが";
		mes "当たるかもしれないよ～。";
		next;
		switch(select("値段が高すぎる","くじを引いてみる(10,000Zeny)")) {
		case 1:
			mes "[放浪商人]";
			mes "やっぱりそうかな～？";
			mes "たまにしか売れないんだよ～。";
			break;
		case 2:
			mes "‐スピードアップポーションは";
			mes "　もっと安く入手できたような";
			mes "　気がする。";
			mes "　それでも、くじを引きますか？‐";
			next;
			if(select("やっぱりやめる","それでもくじを引く(10,000Zeny)") == 1) {
				mes "[放浪商人]";
				mes "そうですか～。";
				mes "また今度来てくださいね～。";
				break;
			}
			while(1) {
				mes "[放浪商人]";
				mes "よし！";
				mes "何が出るかな～？";
				next;
				if(Zeny < 10000) {
					mes "[放浪商人]";
					mes "おや？";
					mes "お金が足りないみたいだね～。";
					close;
				}
				if(checkitemblank() < 3) {
					mes "[放浪商人]";
					mes "おや？";
					mes "それ以上持てないみたいだね～。";
					mes "アイテムの種類数を減らしてから";
					mes "また来てね～。";
					close;
				}
				set '@rand,rand(1,2);
				misceffect 9,"";
				set Zeny,Zeny -10000;
				getitem 645,'@rand;
				mes "[放浪商人]";
				mes "結果は……";
				mes "^006400スピードアップポーション^000000" +'@rand+ "個です～。";
				mes "1回で" +'@rand+ "個出ましたね。";
				next;
				mes "[放浪商人]";
				mes "もう一度、やってみないかい？";
				mes "今度はもっといいものが";
				mes "出るかもしれないよ～。";
				next;
				if(select("もう引かない","もう1回くじを引いてみる(10,000Zeny)") == 1) {
					mes "[放浪商人]";
					mes "そうですか～。";
					mes "また今度来てくださいね～。";
					break;
				}
			}
		}
		next;
		mes "[放浪商人]";
		mes "え……窃盗事件？";
		mes "違うよ、このお酒はラフィネから";
		mes "買ったんだよ～。";
		next;
		mes "‐この商人から";
		mes "　スピードアップポーションを";
		mes "　入手できるようだ‐";
		next;
		mes "‐これだけわかればいいだろう。";
		mes "　ルーエンのところに戻ろう‐";
		set ECL_5QUE,16;
		delquest 9233;
		setquest 9234;
		setquest 9260;
		close;
	case 16:
	case 17:
		mes "[放浪商人]";
		mes "もう一度、くじを引いてみるかい？";
		next;
		mes "‐この商人から";
		mes "　スピードアップポーションを";
		mes "　入手できるようだ‐";
		next;
		mes "‐これだけわかればいいだろう。";
		mes "　ルーエンのところに戻ろう‐";
		close;
	case 18:
		mes "[放浪商人]";
		mes "いや～。";
		mes "なかなか見事な推理だったね～。";
		mes "あの家の人たちも";
		mes "これで安心だね～。";
		close;
	default:
		mes "[放浪商人]";
		mes "うーん、お酒が欲しい。";
		mes "飲みたいよ～。";
		close;
	}
}

ecl_in04.gat,85,104,3	script	ポピ	81,{
	switch(ECL_5QUE) {
	case 6:
		mes "‐この犬は、事件発生時間に";
		mes "　家にいたはずだ‐";
		next;
		switch(select("この犬が犯人ということもあり得る","この犬が犯人を目撃しているかもしれない")) {
		case 1:
			mes "‐よくしつけられた犬でも";
			mes "　時には家を散らかすことだって";
			mes "　ないとはいえない。";
			mes "　ついでにネックレスを";
			mes "　どこかに持って行ったかもしれない‐";
			next;
			mes "‐……だからといって";
			mes "　物音を聞いてやってきた人間を";
			mes "　気づかれずに昏倒させることが";
			mes "　できるだろうか？‐";
			next;
			mes "‐さすがに、ちょっと";
			mes "　無理があるような気がする‐";
			next;
			mes "‐犯人を目撃している可能性なら";
			mes "　十分にありそうだけど……‐";
			next;
		case 2:
			break;
		}
		mes "‐この犬が犯人を目撃していたとして";
		mes "　犯人の手掛かりを聞いても";
		mes "　答えてくれるわけでもないし……‐";
		next;
		if(select("犬を観察してみる","やめる") == 2) {
			mes "‐今にも吠えかかってきそうだ。";
			mes "　後でまた観察しよう‐";
			close;
		}
		mes "[ポピ]";
		mes "ウウウウ……ワンワン!!";
		mes "グルルル！";
		next;
		mes "‐危うく噛みつかれるところだった。";
		mes "　人見知りする犬なのかもしれない‐";
		next;
		mes "‐これだけ元気な犬なら";
		mes "　犯人を目撃していたら";
		mes "　吠えかかったり";
		mes "　しそうなものだけど……？‐";
		next;
		switch(select("犯人は犬を手なずけるのが上手い？","犯人は普段から家によく来る人物？")) {
		case 1:
			mes "‐犯人は犬を手なずけるのが";
			mes "　上手い人物か、";
			mes "　普段からこの家によく来る人物";
			mes "　という可能性がある‐";
			break;
		case 2:
			mes "‐犯人は普段からこの家に";
			mes "　よく来る人物か、";
			mes "　犬を手なずけるのが上手い人物";
			mes "　という可能性がある‐";
			break;
		}
		next;
		mes "‐とはいえ、決定的な証拠ではない。";
		mes "　次は本棚を調べてみよう‐";
		set ECL_5QUE,7;
		setquest 9252;
		close;
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "‐これだけ元気な犬なら";
		mes "　犯人を目撃していたら";
		mes "　吠えかかったり";
		mes "　しそうなものだけど……？‐";
		next;
		mes "‐犯人は犬を手なずけるのが";
		mes "　上手い人物か、";
		mes "　普段からこの家によく来る人物";
		mes "　という可能性がある‐";
		close;
	default:
		if(ECL_5QUE >= 18) {
			mes "[ポピ]";
			mes "ワン～！";
			close;
		}
		mes "[ポピ]";
		mes "ウウウウ……ワンワン!!";
		mes "グルル！";
		close;
	}
}

ecl_in04.gat,80,112,3	script	荒らされた本棚	111,{
	if(ECL_5QUE >= 18)
		end;
	switch(ECL_5QUE) {
	case 6:
		mes "‐棚の本が倒れたり";
		mes "　本が床に落ちたりしている‐";
		next;
		mes "‐まずは犬を観察してみよう‐";
		break;
	case 7:
		mes "‐棚の本が倒れたり";
		mes "　本が床に落ちたりしている‐";
		next;
		if(select("調べてみる","やめる") == 2) {
			mes "‐後でまた調べてみよう‐";
			close;
		}
		mes "‐物理の本……科学の本……";
		mes "　小説……‐";
		next;
		mes "‐週刊大人のラフィネ……";
		mes "　これはお父さんのかな？‐";
		next;
		mes "‐日記帳……";
		mes "　こっちは娘さんのものか……‐";
		next;
		mes "‐人の日記帳を見るのは";
		mes "　少し気が引けるけど";
		mes "　何か事件の手掛かりが";
		mes "　あるかもしれない。";
		mes "　……おや、これは？‐";
		next;
		mes "‐お母さんが彼との交際を";
		mes "　認めてくれない。";
		mes "　彼がお母さんに信頼される";
		mes "　よい方法はないかな……‐";
		next;
		switch(select("ルーエンは悩みを抱えていた？","ルーエンは母親に反感を持っていた？")) {
		case 1:
			mes "‐……ルーエンは";
			mes "　こんな悩みを抱えていたのか‐";
			break;
		case 2:
			mes "‐恋人のことで";
			mes "　ルーエンと母親との間に";
			mes "　対立があったのかもしれない‐";
			break;
		}
		next;
		mes "‐ネックレスの件には";
		mes "　関係ないかもしれないけれど";
		mes "　念のため、覚えておこう。";
		mes "　次は破られた本を調べてみよう‐";
		set ECL_5QUE,8;
		setquest 9253;
		close;
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mes "‐ルーエンは、恋人との交際を";
		mes "　母親に認めてもらえなかったようだ‐";
		next;
		mes "‐ネックレスの件には";
		mes "　関係ないかもしれないけれど";
		mes "　念のため、覚えておこう‐";
		close;
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		mes "‐ルーエンは、恋人との交際を";
		mes "　母親に認めてもらえなかったようだ‐";
		close;
	default:
		mes "‐棚の本が倒れたり";
		mes "　本が床に落ちたりしている‐";
		close;
	}
}

ecl_in04.gat,78,111,3	script	破られた本	111,{
	if(ECL_5QUE >= 18)
		end;
	mes "‐机の上の本が";
	mes "　ビリビリに引き裂かれている‐";
	switch(ECL_5QUE) {
	case 6:
		next;
		mes "‐まずは犬を観察してみよう‐";
		break;
	case 7:
		next;
		mes "‐先に本棚を調べてみよう‐";
		break;
	case 8:
		next;
		if(select("調べてみる","やめる") == 2) {
			mes "‐後でまた調べてみよう‐";
			close;
		}
		mes "‐娯楽小説だろうか……？";
		mes "　特に価値のあるような";
		mes "　希少本というわけではなさそうだ‐";
		next;
		mes "‐破損部分を見ると";
		mes "　物がぶつかったというより";
		mes "　人為的に引き裂かれたように";
		mes "　見える‐";
		next;
		mes "‐わざわざ本を破る理由とは……？‐";
		next;
		switch(select("泥棒が入ったように思わせたかった？","ネックレスが目的と気づかれないように？")) {
		case 1:
			mes "‐いかにも泥棒が侵入して";
			mes "　家を荒らしたように見えるけど";
			mes "　それは犯人の正体を隠すための";
			mes "　偽装工作かもしれない‐";
			break;
		case 2:
			mes "‐いかにも金目のものなら";
			mes "　なんでもいいから探し回ったように";
			mes "　見えるけれど";
			mes "　ネックレスを狙っていたと";
			mes "　思われないための";
			mes "　偽装工作かもしれない‐";
			break;
		}
		next;
		mes "‐もし、そうだとしたら";
		mes "　犯人は家族か、家族と身近な";
		mes "　人物という可能性もある‐";
		next;
		mes "‐……いや、まだ何の証拠もない。";
		mes "　思い込みは間違いのもとだ。";
		mes "　でも、可能性の一つとして";
		mes "　今のことは心に留めておこう。";
		mes "　次はドリンク箱を調べてみよう‐";
		set ECL_5QUE,9;
		setquest 9254;
		close;
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		mes "‐机の上の本は人為的に";
		mes "　引き裂かれたように見える‐";
		next;
		mes "‐いかにも泥棒が侵入して";
		mes "　家を荒らしたように見えるけど";
		mes "　それは犯人の偽装工作かもしれない‐";
		close;
	}
	close;
}

ecl_in04.gat,83,111,3	script	ドリンク箱	111,{
	if(ECL_5QUE >= 18)
		end;
	switch(ECL_5QUE) {
	case 6:
		mes "‐飲み物の瓶が入っている";
		mes "　ここも散らかっているようだ‐";
		next;
		mes "‐まずは犬を観察してみよう‐";
		close;
	case 7:
		mes "‐飲み物の瓶が入っている";
		mes "　ここも散らかっているようだ‐";
		next;
		mes "‐先に本棚を調べてみよう‐";
		close;
	case 8:
		mes "‐飲み物の瓶が入っている";
		mes "　ここも散らかっているようだ‐";
		next;
		mes "‐先に机の上の本を調べてみよう‐";
		close;
	case 9:
		mes "‐飲み物の瓶が入っている";
		mes "　ここも散らかっているようだ‐";
		next;
		if(select("調べてみる","やめる") == 2) {
			mes "‐後でまた調べてみよう‐";
			close;
		}
		mes "‐この飲み物は何だろう？‐";
		next;
		mes "[デイムス]";
		mes "ああ、それはお酒です。";
		mes "ラフィネ族のお酒としては";
		mes "一般的なものです。";
		mes "高級品じゃないですよ。";
		next;
		mes "[デイムス]";
		mes "まだ15本ほど";
		mes "箱にあったと思います。";
		next;
		mes "‐念のため、数えてみると";
		mes "　お酒の瓶は13本だった‐";
		next;
		switch(select("犯人が盗んだ？","デイムスの記憶違い？","瓶は武器にもなる？")) {
		case 1:
			mes "‐高級でもないお酒を盗むなんて";
			mes "　犯人はお酒が好きなのだろうか？‐";
			next;
			mes "‐瓶を持って逃げるのは目立つから";
			mes "　盗んだお金で酒屋に行った方が";
			mes "　良さそうな気がするけれど……‐";
			break;
		case 2:
			mes "‐これだけ数があったら";
			mes "　正確な本数を覚えていなくても";
			mes "　おかしくはない‐";
			next;
			mes "‐わざわざ嘘をつくようなこととも";
			mes "　思えないけれど";
			mes "　デイムスの記憶違いかもしれない‐";
			break;
		case 3:
			mes "‐この瓶で人を殴ったら";
			mes "　殴られた方は";
			mes "　無事では済まないだろう‐";
			next;
			mes "‐瓶の方も割れてしまうかも";
			mes "　しれないが……どうやら";
			mes "　破片などは見当たらないようだ。";
			mes "　凶器として使用されたかどうかは";
			mes "　わからない‐";
			break;
		}
		next;
		mes "‐ともかく、ドリンク箱の";
		mes "　瓶も散らかっていることは";
		mes "　念のために覚えておこう‐";
		next;
		mes "‐次はテーブルを調べてみよう‐";
		set ECL_5QUE,10;
		setquest 9255;
		close;
	case 10:
	case 11:
	case 12:
		mes "‐お酒の瓶が入っている";
		mes "　ここも散らかっているようだ‐";
		next;
		mes "‐犯人が瓶を盗んだのか";
		mes "　それとも、深い意味などないのか？‐";
		close;
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		mes "‐お酒の瓶が入っている";
		mes "　ここも散らかっているようだ‐";
		close;
	default:
		mes "‐飲み物の入った瓶が入っている";
		mes "　ここも散らかっているようだ‐";
		close;
	}
}

ecl_in04.gat,76,107,3	script	荒らされたテーブル	111,{
	if(ECL_5QUE >= 18)
		end;
	mes "‐テーブルの上も荒らされている‐";
	switch(ECL_5QUE) {
	case 6:
		next;
		mes "‐まずは犬を観察してみよう‐";
		break;
	case 7:
		next;
		mes "‐先に本棚を調べてみよう‐";
		break;
	case 8:
		next;
		mes "‐先に机の上の本を調べてみよう‐";
		break;
	case 9:
		next;
		mes "‐先にドリンク箱を調べてみよう‐";
		break;
	case 10:
		next;
		if(select("調べてみる","やめる") == 2) {
			mes "‐後でまた調べてみよう‐";
			close;
		}
		mes "‐散らかったテーブルの上を";
		mes "　観察すると、綺麗な小箱があった‐";
		next;
		mes "[ロサ]";
		mes "それは宝石箱だわ。";
		mes "盗まれたネックレスも";
		mes "その中に入れてあったの。";
		next;
		mes "[ロサ]";
		mes "それも高価なものじゃないけど";
		mes "宝石箱としては、いい物よ。";
		mes "ネックレスと同じくらいには";
		mes "価値があるんじゃないかしら？";
		next;
		mes "‐なぜ、犯人はネックレスを";
		mes "　盗んだとき、宝石箱ごと";
		mes "　持っていかなかったのだろう？‐";
		next;
		mes "‐金目のものが欲しいのなら";
		mes "　ネックレスだけでなく";
		mes "　宝石箱も持っていくはずだ‐";
		next;
		mes "‐ネックレス自体も";
		mes "　それほど高価なものではない‐";
		next;
		menu "犯人の目的はお金ではない？",-,"ネックレスの持ち主に対するメッセージ？",-;
		mes "‐ロサが大切にしていたという";
		mes "　ネックレス……‐";
		next;
		mes "‐それを盗むことに";
		mes "　どんな意味があるのだろう……？‐";
		next;
		mes "‐次は犬の収集物を";
		mes "　調べてみよう‐";
		set ECL_5QUE,11;
		setquest 9256;
		close;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		mes "‐テーブルの上には";
		mes "　ネックレスを入れていた";
		mes "　宝石箱が残っている‐";
		next;
		mes "‐宝石箱も価値があるようだが";
		mes "　なぜ中に入っていたネックレスだけが";
		mes "　盗まれたのだろう？‐";
		close;
	}
	close;
}

ecl_in04.gat,80,105,3	script	犬の収集物	557,{
	if(ECL_5QUE >= 18)
		end;
	switch(ECL_5QUE) {
	case 6:
		mes "‐犬の収集物だろうか？";
		mes "　雑多な物が重ねられている‐";
		next;
		mes "‐まずは犬を観察してみよう‐";
		close;
	case 7:
		mes "‐犬の収集物だろうか？";
		mes "　雑多な物が重ねられている‐";
		next;
		mes "‐先に本棚を調べてみよう‐";
		close;
	case 8:
		mes "‐犬の収集物だろうか？";
		mes "　雑多な物が重ねられている‐";
		next;
		mes "‐先に机の上の本を調べてみよう‐";
		close;
	case 9:
		mes "‐犬の収集物だろうか？";
		mes "　雑多な物が重ねられている‐";
		next;
		mes "‐先にドリンク箱を調べてみよう‐";
		close;
	case 10:
		mes "‐犬の収集物だろうか？";
		mes "　雑多な物が重ねられている‐";
		next;
		mes "‐先に荒らされたテーブルを";
		mes "　調べてみよう‐";
		close;
	case 11:
		mes "‐犬の収集物だろうか？";
		mes "　雑多な物が重ねられている。";
		mes "　何か事件の手掛かりが";
		mes "　あるだろうか？‐";
		next;
		if(select("調べてみる","やめる") == 2) {
			mes "‐後でまた調べてみよう‐";
			close;
		}
		mes "‐サンダル、定規、バケツ……";
		mes "　ガラクタのようなものが";
		mes "　積み重なっている‐";
		next;
		mes "‐……おや？";
		mes "　これは……‐";
		next;
		mes "‐まさか、盗まれたはずの";
		mes "　ネックレス？‐";
		next;
		mes "‐どうしてこんなところに？";
		mes "　まさか、犬が真犯人なのか？‐";
		next;
		menu "犯人は犬ではない",-,"まだ調べることがある",-;
		mes "‐いや、自分を襲ったのは";
		mes "　あの騒がしい犬とは思えない。";
		mes "　それに、破られた本の裂け目は";
		mes "　人為的なものだった‐";
		next;
		mes "‐もしかしたら、ネックレスを";
		mes "　ここに隠したのは犬かもしれない。";
		mes "　でも、家を荒らした人物が";
		mes "　他にいるはずだ‐";
		next;
		mes "‐近くに犯人がいるかもしれないので";
		mes "　ネックレスを見つけたことは";
		mes "　犯人がわかるまでの間は";
		mes "　伏せておこう‐";
		next;
		mes "‐家の中はひと通り調べた。";
		mes "　一度ルーエンと話してみよう‐";
		set ECL_5QUE,12;
		setquest 9257;
		close;
	case 12:
		mes "‐もしかしたら、ネックレスを";
		mes "　ここに隠したのは犬かもしれない。";
		mes "　でも、家を荒らした人物が";
		mes "　他にいるはずだ‐";
		next;
		mes "‐家の中はひと通り調べた。";
		mes "　一度ルーエンと話してみよう‐";
		close;
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		mes "‐もしかしたら、ネックレスを";
		mes "　ここに隠したのは犬かもしれない。";
		mes "　でも、家を荒らした人物が";
		mes "　他にいるはずだ‐";
		next;
		mes "‐ここにネックレスがあることは";
		mes "　犯人がわかるまでの間は";
		mes "　伏せておこう‐";
		close;
	default:
		mes "‐犬の収集物だろうか？";
		mes "　雑多な物が重ねられている‐";
		close;
	}
}

ecl_in04.gat,209,200,3	script	放浪商人	807,{
	if(ECL_5QUE >= 18) {
		mes "[放浪商人]";
		mes "う～ん……。";
		mes "まさか、私の商品がアリバイに";
		mes "利用されているとはね～。";
		close;
	}
	mes "[放浪商人]";
	mes "急に呼ばれたけど";
	mes "何が始まるのかな～？";
	close;
}

ecl_in04.gat,203,199,5	script	バルミン	461,{
	if(ECL_5QUE >= 18) {
		mes "[バルミン]";
		mes "なるほど、そういうことだったのか。";
		mes "早く解決して良かった。";
		next;
		mes "[バルミン]";
		mes "なかなか見事な推理でした。";
		mes "帰る前に花が咲き始めた大地に";
		mes "来てください。";
		close;
	}
	mes "[バルミン]";
	mes "ふむ……。";
	mes "事件のことで何かわかったのかな？";
	close;
}

ecl_in04.gat,205,198,5	script	クルイアン	442,{
	if(ECL_5QUE >= 18) {
		mes "[クルイアン]";
		mes "ルーエンは悪くありません。";
		mes "すべて私が悪いのです……。";
		next;
		mes "[クルイアン]";
		mes "……後で、私のところに";
		mes "来てください。";
		mes "前に会った場所で待っています。";
		close;
	}
	mes "[クルイアン]";
	mes "お母様のネックレスは";
	mes "私が見つけてみせます！";
	close;
}

ecl_in04.gat,210,197,3	script	ロサ	520,{
	if(ECL_5QUE >= 18) {
		mes "[ロサ]";
		mes "まさか……。";
		mes "こんなことって……。";
		close;
	}
	mes "[ロサ]";
	mes "私のネックレスは見つかったの？";
	mes "早く教えてちょうだい！";
	close;
}

ecl_in04.gat,203,196,5	script	デイムス	447,{
	if(ECL_5QUE >= 18) {
		mes "[デイムス]";
		mes "うーん、まさかそんなことで……。";
		mes "なんにせよ、解決していただき";
		mes "ありがとうございました。";
		next;
		mes "[デイムス]";
		mes "後でお礼をしますので";
		mes "部屋を出たら";
		mes "家族に話しかけてください。";
		close;
	}
	mes "[デイムス]";
	mes "さあ、早く事件を解決してください。";
	close;
}

ecl_in04.gat,208,194,3	script	ルーエン	437,{
	if(ECL_5QUE != 17) {
		mes "[ルーエン]";
		mes "色々とありがとうございました。";
		mes "後は私とクルイアンで";
		mes "何とかします。";
		next;
		if(select("部屋から出る","もう少しここにいる") == 2) {
			mes "[ルーエン]";
			mes "外に出る時は";
			mes "声をかけてください。";
			close;
		}
		mes "‐部屋から出ます‐";
		close2;
		warp "ecl_in04.gat",77,107;
		end;
	}
	mes "[ルーエン]";
	mes "どうしますか？";
	next;
	switch(select("推理する","もう少し考える","いったん外に出る")) {
	case 1:
		break;
	case 2:
		mes "‐考えがまとまったら";
		mes "　もう一度ルーエンに";
		mes "　話しかけよう‐";
		close;
	case 3:
		mes "‐部屋から出ます‐";
		close2;
		warp "ecl_in04.gat",77,107;
		end;
	}
	mes "‐今回の事件。";
	mes "　家の中で物音がして";
	mes "　中の様子を見ようとしたら";
	mes "　背後から衝撃を受けて";
	mes "　昏倒させられた‐";
	next;
	mes "‐気が付くと、住人に介抱されていて";
	mes "　家の中は荒らされ";
	mes "　奥さんが大事にしている";
	mes "　ネックレスが無くなっていた‐";
	next;
	mes "‐事件に関係する人物は6名。";
	mes "　この家の主人デイムス";
	mes "　妻のロサ";
	mes "　娘のルーエン";
	mes "　デイムスの友人バルミン";
	mes "　ルーエンの恋人クルイアン";
	mes "　赤い髪の放浪商人‐";
	next;
	mes "‐まず、犯人の目的から";
	mes "　整理してみよう‐";
	while(1) {
		next;
		switch('@succsess) {
		case 0:
			switch(select("金目のものが欲しかった","ロサのネックレスが目当てだった")) {
			case 1:
				mes "‐犯人は金目のものが欲しくて";
				mes "　家に侵入し、ロサのネックレスを";
				mes "　盗んだ‐";
				next;
				mes "‐……でも、ネックレスと同じくらい";
				mes "　価値のあった宝石箱は";
				mes "　盗まれていなかった。";
				mes "　金目のものが目当てなら";
				mes "　わざわざ宝石箱からネックレスだけ";
				mes "　抜き取るのはおかしい‐";
				next;
				mes "‐もう一度考えてみよう‐";
				continue;
			case 2:
				mes "‐犯人は金目のものなら";
				mes "　なんでもいいというわけではなく";
				mes "　ロサのネックレスを";
				mes "　盗み出す必要があった‐";
				next;
				mes "‐家の中の本が引き裂かれていたり";
				mes "　宝石箱が盗まれていなかったことを";
				mes "　考えても、わざわざ";
				mes "　泥棒が入ったように見せて";
				mes "　本来の目的を偽装していた‐";
				next;
				mes "‐しかし、実際には";
				mes "　ネックレスは犬の収集物の中に";
				mes "　紛れ込んでいた‐";
				set '@succsess,'@succsess + 1;
				continue;
			}
		case 1:
			switch(select("ネックレスを盗む際にトラブルがあった","実は犬が犯人だった")) {
			case 1:
				mes "‐犯人が宝石箱からネックレスを";
				mes "　取り出した時に";
				mes "　何らかのトラブルがあって";
				mes "　盗みに失敗したのかもしれない‐";
				break;
			case 2:
				mes "‐ネックレスを隠したのは";
				mes "　犬かもしれないが";
				mes "　宝石箱からネックレスを";
				mes "　盗み出した人物がいるはずだ‐";
				break;
			}
			next;
			mes "‐以上の情報から";
			mes "　犯人について";
			mes "　推理できることは？‐";
			set '@succsess,'@succsess + 1;
			continue;
		case 2:
			switch(select("犯人はこの家の家族かその知人","犯人はロサに恨みがある")) {
			case 1:
				mes "‐泥棒が入ったように";
				mes "　偽装するということは";
				mes "　犯人には別の目的があったと";
				mes "　推測できる‐";
				next;
				mes "‐ということは";
				break;
			case 2:
				mes "‐ロサの大事にしている";
				mes "　ネックレスが狙われたということは";
				mes "　犯人がロサに恨みを持っていた";
				mes "　可能性がある‐";
				next;
				mes "‐しかし、別の理由でネックレスが";
				mes "　必要と犯人が考えた可能性も";
				mes "　否定できない‐";
				next;
				mes "‐いずれにしても";
				break;
			}
			mes "　ネックレスの持ち主であるロサや";
			mes "　その家族に何らかの形で";
			mes "　関連している人物が";
			mes "　事件に深くかかわっている";
			mes "　可能性が高い‐";
			next;
			mes "‐つまり……";
			mes "　犯人は、この中にいる‐";
			next;
			mes "‐次は、この6人について";
			mes "　整理してみよう‐";
			next;
			mes "‐6人に話を聞いたとき";
			mes "　互いに矛盾した供述をしていた";
			mes "　人物がいる‐";
			set '@succsess,'@succsess + 1;
			continue;
		case 3:
			switch(select("デイムスとロサ","ルーエンと放浪商人","バルミンとクルイアン")) {
			case 1:
				mes "‐デイムスはロサが犯人だと";
				mes "　疑っていた。";
				mes "　一方で、ロサは家族以外の誰かが";
				mes "　犯人に違いないと言っていた‐";
				next;
				mes "‐とはいえ、これは2人とも";
				mes "　確かな証拠もなく";
				mes "　推測で言っていただけだ‐";
				next;
				mes "‐もう一度考えてみよう‐";
				continue;
			case 2:
				mes "‐ルーエンは赤くて短い髪の人物を";
				mes "　見かけたと言っていた。";
				mes "　放浪商人はルーエンのことを";
				mes "　見たような様子はなかったが……‐";
				next;
				mes "‐これは、単純にルーエンが";
				mes "　一方的に放浪商人を";
				mes "　見かけただけかもしれないし";
				mes "　もしかしたら";
				mes "　別の人物だったのかもしれない‐";
				next;
				mes "‐もう一度考えてみよう‐";
				continue;
			case 3:
				mes "‐バルミンは花が咲き始めた大地の";
				mes "　モンスターから";
				mes "　スピードアップポーションは";
				mes "　得られないと言っていたが";
				mes "　クルイアンは";
				mes "　スピードアップポーションを";
				mes "　入手していた‐";
				next;
				mes "‐この2人の供述は矛盾している。";
				mes "　他の人の供述で、どちらが正しいか";
				mes "　わかるものがあったはずだ‐";
				set '@succsess,'@succsess + 1;
				continue;
			}
		case 4:
			switch(select("ルーエンの供述","デイムスの供述","放浪商人の供述")) {
			case 1:
				mes "‐ルーエンは帰ってきたときに";
				mes "　家の前を通るバルミンを見たと";
				mes "　言っていた。";
				mes "　その時間、バルミンは";
				mes "　花が咲き始めた大地で";
				mes "　モンスターを狩っていた‐";
				next;
				mes "‐バルミンの供述は";
				mes "　ルーエンとクルイアンの";
				mes "　2人の供述と矛盾する‐";
				next;
				mes "‐バルミンが嘘をついている";
				mes "　証拠にはならないが";
				mes "　このことは覚えておこう‐";
				continue;
			case 2:
				mes "‐デイムスはバルミンに";
				mes "　借金を頼まれたことがあった。";
				mes "　その時は断ったそうだが";
				mes "　バルミンにネックレスを狙う";
				mes "　動機があったと考えられる‐";
				next;
				mes "‐しかし、バルミンはモンスターを";
				mes "　倒してまじめに働いていたし";
				mes "　なにより、先ほど犯人の目的は";
				mes "　金目の物ではないと";
				mes "　推理したばかりだ‐";
				next;
				mes "‐もう一度考えてみよう‐";
				continue;
			case 3:
				mes "‐放浪商人の販売していたくじから";
				mes "　スピードアップポーションを";
				mes "　入手することができた‐";
				next;
				mes "‐しかも、実際に";
				mes "　花が咲き始めた大地で";
				mes "　モンスターを倒しても";
				mes "　スピードアップポーションは";
				mes "　手に入らなかった‐";
				next;
				mes "‐つまり、犯行時刻に";
				mes "　花が咲き始めた大地にいたという";
				mes "　人物の供述は嘘ではないだろうか？‐";
				next;
				mes "‐情報の整理はこんなものだろうか。";
				mes "　決定的な証拠はないが";
				mes "　明らかに怪しい人物が一人いる‐";
				set '@succsess,'@succsess + 1;
				continue;
			}
		case 5:
			switch(select("デイムス","ロサ","ルーエン","バルミン","クルイアン","放浪商人","もう一度始めから考える")) {
			case 1:
				mes "[デイムス]";
				mes "えっ？";
				mes "私ですか……？";
				mes "どうして、私がネックレスを";
				mes "盗まなければいけないのですか？";
				next;
				switch(select("間違えた","ロサに不満があったことを指摘する")) {
				case 1:
					mes "[デイムス]";
					mes "驚かさないでください。";
					continue;
				case 2:
					mes "[デイムス]";
					mes "……たしかに、多少は";
					mes "妻とうまくいかないこともありました。";
					mes "でも、それで私が犯人というのは";
					mes "あまりにも短絡的です。";
					next;
					mes "[デイムス]";
					mes "だいたい、私が犯人だったら";
					mes "妻に対する不満があっても";
					mes "そのことを隠して";
					mes "疑われないようにしますよ！";
					next;
					mes "‐デイムスが犯人という推理は";
					mes "　無理があるようだ。";
					mes "　もう一度考えてみよう‐";
					continue;
				}
			case 2:
				mes "[ロサ]";
				mes "なんですって！";
				mes "私が犯人だと言うの!?";
				mes "ふざけないでちょうだい！";
				next;
				switch(select("間違えた","新しいネックレスを欲しがっていたことを指摘する")) {
				case 1:
					mes "[ロサ]";
					mes "当然よっ！";
					mes "私が犯人のわけがないわ。";
					continue;
				case 2:
					mes "[ロサ]";
					mes "新しいネックレスを";
					mes "買ってもらうために";
					mes "大事にしていたネックレスを";
					mes "隠したとでもいうの!?";
					next;
					mes "[ロサ]";
					mes "あのネックレスは主人にもらった";
					mes "思い出の品物なのよ。";
					mes "新しいものが欲しいと言ったのも";
					mes "着飾って人に見せつけたいとか";
					mes "そういうことではないわ！";
					next;
					mes "[ロサ]";
					mes "ただ、最近主人が";
					mes "私に無関心な様子だったから";
					mes "少し不安だっただけよ！";
					next;
					mes "‐ロサが犯人という推理は";
					mes "　無理があるようだ。";
					mes "　もう一度考えてみよう‐";
					continue;
				}
			case 3:
				mes "[ルーエン]";
				mes "ええっ！";
				mes "わ、私ですか……？";
				next;
				switch(select("間違えた","バルミンを見かけたという供述について指摘する")) {
				case 1:
					mes "[ルーエン]";
					mes "そうですか……。";
					mes "びっくりしました。";
					continue;
				case 2:
					mes "[ルーエン]";
					mes "えっ？　バルミンさんは";
					mes "ずっと花が咲き始めた大地に";
					mes "いたのですか？";
					next;
					mes "[ルーエン]";
					mes "……家の前でバルミンさんを";
					mes "見かけたというのは";
					mes "たぶん、私の記憶違いです。";
					mes "花が咲き始めた大地で";
					mes "見かけたか、もしかしたら";
					mes "別の人と間違えたのかもしれません。";
					next;
					mes "[ルーエン]";
					mes "でも、私は犯人じゃありません！";
					mes "母のネックレスを盗む理由なんて";
					mes "ありませんから。";
					next;
					mes "‐ルーエンが犯人でないと";
					mes "　証明できる材料はない。";
					mes "　しかし、今はもっと怪しい人物が";
					mes "　いるはずだ。";
					mes "　もう一度考えてみよう‐";
					continue;
				}
			case 4:
				mes "[バルミン]";
				mes "私が泥棒だと言うのかね？";
				next;
				switch(select("間違えた","供述の矛盾を指摘する")) {
				case 1:
					mes "[バルミン]";
					mes "うむ。";
					mes "わかってくれれば、いいのだ。";
					continue;
				case 2:
					mes "[バルミン]";
					mes "クルイアンの供述と矛盾するだと？";
					mes "他の人が何を言ったか知らないが";
					mes "私は自分が見たままを";
					mes "供述したつもりだ。";
					next;
					mes "[バルミン]";
					mes "もしかして、クルイアンの方が";
					mes "嘘をついているということは";
					mes "ないのかね？";
					next;
					mes "‐バルミンの供述は嘘ではなかった。";
					mes "　疑うべき人物は他にいるはずだ。";
					mes "　もう一度考えてみよう‐";
					continue;
				}
			case 5:
				mes "[クルイアン]";
				mes "私が犯人だというのですか？";
				mes "でも、私にはアリバイがあると";
				mes "言いましたよね？";
				next;
				switch(select("間違えた","供述の嘘を指摘する")) {
				case 1:
					mes "[クルイアン]";
					mes "そうですよね。";
					mes "私にはアリバイがありますから。";
					continue;
				case 2:
					mes "[クルイアン]";
					mes "えっ？";
					mes "スピードアップポーションは";
					mes "花が咲き始めた大地の";
					mes "モンスターからは";
					mes "入手できないって？";
					next;
					mes "[クルイアン]";
					mes "……たしかに";
					mes "スピードアップポーションは";
					mes "そこにいる放浪商人のくじで";
					mes "入手しました。";
					next;
					mes "[クルイアン]";
					mes "でも、それは私が";
					mes "花が咲き始めた大地に";
					mes "いなかったというだけで";
					mes "私が犯人だという証拠では";
					mes "ありませんよね？";
					next;
					mes "[クルイアン]";
					mes "もし私が犯人だというなら";
					mes "そのことを証明するような何かを";
					mes "示してください！";
					set '@succsess,'@succsess + 1;
					continue;
				}
			case 6:
				mes "[放浪商人]";
				mes "私が犯人だって？";
				mes "ちょっと待ってくれよ！";
				next;
				switch(select("間違えた","酒瓶が無くなっていたことを指摘する")) {
				case 1:
					mes "[放浪商人]";
					mes "そうだよな。";
					mes "私が犯人のわけがない！";
					continue;
				case 2:
					mes "[放浪商人]";
					mes "今日はお酒を飲んでいたけれど";
					mes "あれは自分で稼いだお金で買った";
					mes "ものだよ。";
					next;
					mes "[放浪商人]";
					mes "え？";
					mes "仕事中にお酒を飲むのは";
					mes "良くないって……？";
					mes "大きなお世話だよ。";
					next;
					mes "‐放浪商人の発言も気になるが";
					mes "　とりあえず、今はもっと";
					mes "　怪しい人物がいるはずだ。";
					mes "　もう一度考えてみよう‐";
					continue;
				}
			case 7:
				mes "‐あなたは、もう一度";
				mes "　始めから考えることにした‐";
				close;
			}
		case 6:
			switch(select("犯行時刻何をしていたか聞く","ネックレスのあった場所を明かす","ネックレスを探すと意気込んでいたことを指摘する","ルーエンとの交際を否定されていたことを指摘する")) {
			case 1:
				mes "[クルイアン]";
				mes "街にいましたよ。";
				mes "証明できる人はいませんが。";
				next;
				mes "‐クルイアンは開き直って";
				mes "　嘘をついているように";
				mes "　見えるが、本当のことは";
				mes "　聞き出せそうにない。";
				mes "　もう一度考えてみよう‐";
				continue;
			case 2:
				mes "[クルイアン]";
				mes "ネックレスは犬の収集物の中に";
				mes "あったんですか。";
				mes "まさか、そんなところにあるとは";
				mes "驚きました。";
				next;
				mes "[クルイアン]";
				mes "ということは";
				mes "私が犯人という証拠には";
				mes "なりませんよね？";
				next;
				mes "‐クルイアンの言う通りだ。";
				mes "　もう一度考えてみよう‐";
				continue;
			case 3:
				mes "[クルイアン]";
				mes "ええ、犯人が盗んだネックレスを";
				mes "取り返そうと思ったんです。";
				mes "私が犯人なら、そんなことは";
				mes "考えないでしょう？";
				next;
				menu "ネックレスが盗まれたことをどこで知ったか聞く",-;
				mes "[クルイアン]";
				mes "ルーエンに聞いたのです。";
				mes "お母様が困っていると思って";
				mes "急いで駆け付けたのです！";
				next;
				menu "クルイアンが来るまでルーエンは家を出ていない",-;
				mes "[クルイアン]";
				mes "えっ？";
				mes "そ、それは……。";
				next;
				mes "[クルイアン]";
				mes "たぶん、私の勘違いです。";
				mes "ルーエン以外の誰かに";
				mes "聞いたのだと思います。";
				next;
				mes "[ルーエン]";
				mes "……クルイアン。";
				mes "もう、やめようよ。";
				next;
				mes "[クルイアン]";
				mes "ルーエン！";
				mes "何を言ってるんだ？";
				next;
				mes "[ルーエン]";
				mes "ネックレスが盗まれたことを";
				mes "知っていたのは、私と両親と";
				mes "人間の探偵さんと……。";
				mes "あとは、盗もうとした本人だけ。";
				next;
				mes "[ルーエン]";
				mes "私にだって、そのくらいのことは";
				mes "わかるわ。";
				mes "……もう、ごまかしきれないよ。";
				next;
				mes "[クルイアン]";
				mes "……ルーエン……。";
				next;
				mes "[クルイアン]";
				mes "……そうです。";
				mes "私がネックレスを";
				mes "盗もうとしました。";
				next;
				mes "[ロサ]";
				mes "やっぱり、あなただったのね！";
				mes "お酒や遊びだけでなく";
				mes "盗みまで働くなんて！";
				next;
				mes "[クルイアン]";
				mes "そのことについては";
				mes "申し訳なく思っています。";
				mes "……お母様を困らせるつもりは";
				mes "なかったのです。";
				next;
				mes "[ロサ]";
				mes "何を言っているの!?";
				mes "大切にしているものを盗まれたら";
				mes "困るに決まっているじゃない！";
				mes "それと、私のことを";
				mes "お母様と呼ぶのは止めなさい！";
				next;
				mes "[ルーエン]";
				mes "待って！";
				mes "クルイアンに悪気はなかったの。";
				mes "せめて、話を聞いてあげて。";
				next;
				mes "[クルイアン]";
				mes "……少し前まで";
				mes "私はお酒やギャンブルが好きで";
				mes "毎日、遊びまわっていました。";
				next;
				mes "[クルイアン]";
				mes "ルーエンと出会って";
				mes "これからはまじめになろうと";
				mes "生活を変えたのです。";
				next;
				mes "[クルイアン]";
				mes "でも、お母様に交際を認めてもらえず";
				mes "とても悩みました。";
				next;
				mes "[デイムス]";
				mes "ふむ……たしかに妻には";
				mes "頑固なところがある。";
				mes "だからといって、ネックレスを";
				mes "盗むことはないだろう。";
				next;
				mes "[クルイアン]";
				mes "いえ、そうではないのです。";
				mes "……私は、なんとかして";
				mes "お母様の信頼を勝ち取ろうと";
				mes "その方法について";
				mes "いろいろ考えました。";
				next;
				mes "[クルイアン]";
				mes "そして……わざと";
				mes "お母様のネックレスを盗んで";
				mes "それを私が見つけたことにすれば";
				mes "お母様も認めてくださるのではないかと";
				mes "思ったのです。";
				next;
				mes "[クルイアン]";
				mes "……もちろん";
				mes "今となっては、バカな考えだったと";
				mes "反省しています。";
				next;
				mes "[クルイアン]";
				mes "ネックレスを取り出すところを";
				mes "ルーエンに見つかって";
				mes "止めようとする彼女と";
				mes "ぶつかった時にネックレスは";
				mes "どこかに落として";
				mes "見つからなくなってしまうし……。";
				next;
				mes "[クルイアン]";
				mes "家の入り口で";
				mes "見知らぬ人を殴ってしまい";
				mes "怖くなって逃げ出すことしか";
				mes "できませんでした……。";
				next;
				mes "[ルーエン]";
				mes "私も、怖くなって";
				mes "逃げ出してしまったのは同じです。";
				next;
				mes "[ルーエン]";
				mes "それどころか";
				mes "本当のことを言い出せず";
				mes "クルイアンを庇うために";
				mes "嘘をついてしまって……。";
				mes "本当にごめんなさい。";
				next;
				mes "[クルイアン]";
				mes "いや、ルーエンは悪くない！";
				mes "全て私が悪いのです。";
				next;
				mes "[クルイアン]";
				mes "ほんとうに申し訳ありませんでした。";
				next;
				mes "‐事件の犯人はクルイアンだった。";
				mes "　本人も反省しているようなので";
				mes "　もう新たな被害が";
				mes "　出ることはないだろう‐";
				next;
				mes "[ルーエン]";
				mes "人間の探偵さん、";
				mes "怪我をさせてしまってごめんなさい。";
				mes "私たちがしたことは";
				mes "良くないことですけど、";
				mes "反省して、やり直そうと思います。";
				next;
				mes "[ルーエン]";
				mes "あなたが事件を";
				mes "解決してくれなかったら";
				mes "後ろめたい気持ちのまま";
				mes "だったと思います。";
				next;
				mes "[ルーエン]";
				mes "ほんとうに、ありがとうございました。";
				mes "お礼をしたいので";
				mes "部屋を出たらもう一度";
				mes "話しかけてくださいね。";
				set ECL_5QUE,18;
				delquest 9240;
				delquest 9244;
				delquest 9247;
				delquest 9248;
				delquest 9251;
				delquest 9258;
				delquest 9260;
				delquest 9235;
				setquest 9236;
				close2;
				warp "ecl_in04.gat",77,107;
				end;
			case 4:
				mes "[クルイアン]";
				mes "たしかに、お母様には";
				mes "交際に反対されていました。";
				next;
				mes "[クルイアン]";
				mes "だからといって";
				mes "お母様が大事にしている";
				mes "ネックレスを盗んでも";
				mes "交際を認められるわけでは";
				mes "ないでしょう？";
				next;
				mes "‐クルイアンの言う通りだ。";
				mes "　もう一度考えてみよう‐";
				continue;
			}
		}
	}
	next;
	close;
}

eclage.gat,156,56,3	script	民家入り口#eclage	844,3,3,{
	switch(ECL_5QUE) {
	case 0:
		mes "‐民家がある。";
		mes "　扉は閉まっているようだ‐";
		close;
	default:
		mes "‐盗難事件のあった民家だ‐";
		next;
		if(select("民家に入らない","民家に入る") == 1) {
			mes "‐あなたは民家を後にした‐";
			close;
		}
		mes "‐民家に入ります‐";
		close2;
		warp "ecl_in04.gat",77,107;
		end;
	}
OnTouch:
	if(ECL_5QUE == 0) {
		mes "‐カサカサ……カサカサ……";
		mes "　ドンドンドカンドカン……";
		mes "　カンカン!!　カン！‐";
		next;
		mes "‐家の中から物音がする‐";
		next;
		if(select("気にせず通り過ぎる","声をかけてみる") == 1) {
			mes "‐物音を気にせず、";
			mes "　あなたは先を急ぐことにした‐";
			close;
		}
		mes "["+strcharinfo(0)+"]";
		mes "中に誰かいますか？";
		mes "大丈夫ですか？";
		next;
		mes "‐不意に視界が揺れた。";
		mes "　どうやら後頭部に";
		mes "　衝撃を受けたようだ。";
		mes "　力が抜け、視界がかすんできた‐";
		misceffect 0,"";
		sc_start3 SC_BLIND,0,0,0,0,60000,10;
		next;
		mes "‐いったい、何が……？";
		mes "　……誰かに殴られた？";
		mes "　ああ、だめだ……‐";
		close2;
		set ECL_5QUE,1;
		setquest 9225;
		warp "ecl_in04.gat",80,108;
		end;
	}
	end;
OnInit:
	waitingroom "民家入り口",0;
	end;
}

ecl_in04.gat,81,102,3	script	民家出口#eclage	844,{
	mes "‐民家の玄関だ‐";
	next;
	if(select("民家から出ない","民家から出る") == 1) {
		mes "‐もう少しここにいることにした‐";
		close;
	}
	mes "‐外に出ます‐";
	close2;
	warp "eclage.gat",156,53;
	end;
}

//============================================================
// 悠久なる絆クエスト
//- Registry -------------------------------------------------
// ECL_6QUE -> 0～
//------------------------------------------------------------
ecl_in02.gat,133,115,0	script	#pa0829看守自動	139,3,3,{
	if(ECL_6QUE > 0)
		end;
	mes "[クレヴァー]";
	mes "おーい、看守～。おーい。";
	mes "ちょっと乾燥しすぎてるよ。";
	mes "肌がカサカサになっちゃうよ～。";
	mes "あ～あ！";
	mes "困っちゃうな～。あーあ！";
	mes "おい、看守～？聞いているのか？";
	next;
	mes "[看守]";
	mes "……";
	next;
	mes "^000099‐看守は疲れきった面持ちで";
	mes "　監獄の中にいる囚人を見つめている‐^000000";
	next;
	mes "[看守]";
	mes "クレヴァー様、一言だけいいます。";
	mes "今のあなたはここでは囚人の身です。";
	mes "反省の時間を持つよう";
	mes "命令されている状態です。";
	next;
	mes "[クレヴァー]";
	mes "うん、そうそう。それは分かった。";
	mes "だから急いでここの湿度を";
	mes "何とかしてくれないか。";
	mes "乾燥しすぎてカサカサするんだよ。";
	next;
	mes "[看守]";
	mes "まだ、私の言葉の意味を";
	mes "理解していませんか？";
	mes "そういった事に気を使っていちいち";
	mes "配慮してあげるわけには";
	mes "いかないんですよ。";
	next;
	mes "[クレヴァー]";
	mes "ちぇっ";
	mes "けちだな……。";
	next;
	mes "[看守]";
	mes "まったく。";
	mes "はぁ……。";
	next;
	mes "^000099‐看守は何か言いかけたが、";
	mes "　そのまま席に戻った。";
	mes "　あの人は何故、";
	mes "　捕まっているのだろうか。";
	mes "　看守に話しかけてみよう‐^000000";
	set ECL_6QUE,1;
	setquest 12280;
	close;
}

ecl_in02.gat,146,114,4	script	クレヴァー	622,{
	switch(ECL_6QUE) {
	case 0:
	case 1:
		mes "[クレヴァー]";
		mes "ん、何だ、君は。";
		mes "看守に許可を貰ったか？";
		mes "許可を貰わずに話すと怒られるんだ。";
		mes "面会は看守を通してくれ。";
		close;
	case 2:
		mes "[クレヴァー]";
		mes "お、来たか。";
		mes "ただ……。";
		mes "私は君とは初めて会う気がするな。";
		mes "何の用で面会しに来た？";
		next;
		if(select("特に用はありません","何故ここに？") == 1) {
			mes "[クレヴァー]";
			mes "何しにきたんだ君は……。";
			close;
		}
		mes "[クレヴァー]";
		mes "ん。";
		mes "私が何の罪で捕らえられたのか、";
		mes "気になるって？";
		mes "そんな話を聞いてどうするんだ？";
		next;
		mes "[クレヴァー]";
		mes "見たことも無い人が私に";
		mes "面会要請をしていたから、";
		mes "何か特別な事があると思ったのに、";
		mes "君にはがっかりだよ。";
		mes "あ～もう看守いじめに歌でも歌うか～。";
		mes "あ゛～あ゛～～！";
		next;
		mes "^000099‐クレヴァーが歌い始めた時、";
		mes "　看守の絶望と恐怖のすれ違う表情が";
		mes "　横目に映りこんだ‐^000000";
		next;
		mes "[看守]";
		mes "お願いします。";
		mes "何とかクレヴァー様を";
		mes "黙らせて下さい……。";
		mes "もう1年も聴いていて";
		mes "精神的に限界なんです……。";
		mes "殴るわけにもいかないし。";
		set ECL_6QUE,3;
		setquest 72552;
		delquest 72550;
		close;
	case 3:
		mes "[クレヴァー]";
		mes "そこの君～、るるる～";
		mes "よそ見するな～";
		mes "他の囚人は見るな～";
		mes "私、私だけを見ていろ～ろろ～";
		mes "ずっと見ていろ～ざまあみろ～";
		next;
		menu "ちょっと待ってください！",-;
		mes "[クレヴァー]";
		mes "ん？　なんだ？";
		mes "なんか面白い話でもあるのか？";
		while(1) {
			next;
			if(select("じゃれてみる","旅の話をする","ミッドガルド大陸の話をする","食べたい物を聞いてみる") == 4)
				break;
			mes "[クレヴァー]";
			mes "ふむ……";
			mes "（少し考えている）";
			next;
			mes "[クレヴァー]";
			mes "うむ。";
			next;
			mes "[クレヴァー]";
			mes "すまないな。";
			mes "やっぱり歌を歌う方が楽しいわ！";
			next;
			mes "‐うまくいかなかった。";
			mes "　どうしよう？‐";
		}
		mes "[クレヴァー]";
		mes "うん。食べたい物？";
		mes "うむ……言われてみれば……";
		mes "ずっと同じ食事だから、";
		mes "食べたい物はいっぱいあるな。";
		mes "そうだ、ぜひ食べたい物があった。";
		next;
		mes "[クレヴァー]";
		mes "いつだったか人間の旅人が";
		mes "プレゼントだと言いながら、";
		mes "^000099ブドウ果汁入りハーブティー^000000という";
		mes "飲み物をくれたんだ。";
		mes "頭がすっきりしてとてもおいしかった。";
		mes "もう一度あれを飲んでみたいな。";
		next;
		mes "[クレヴァー]";
		mes "君が私のために";
		mes "^000099ブドウ果汁入りハーブティー^000000を1杯";
		mes "持って来てくれたら、";
		mes "私はお礼として昔話をしてやろう。";
		next;
		if(select("持ってくる","持ってこない") == 2) {
			mes "[クレヴァー]";
			mes "そうか。それならいいんだ。";
			mes "私は歌でも歌うことにするよ。";
			close;
		}
		mes "[クレヴァー]";
		mes "ほおお～そうか。";
		mes "では、私はそれまで";
		mes "昼寝でもしてるとするよ。";
		mes "じゃあ頼んだよ。";
		set ECL_6QUE,4;
		delquest 72552;
		setquest 12281;
		close;
	case 4:
		if(countitem(12046) < 1) {
			mes "[クレヴァー]";
			mes "ぐううう……";
			mes "すやすや……。";
			next;
			mes "^000099‐ブドウ果汁入りハーブティーを";
			mes "　用意して来るまでは";
			mes "　寝ているようだ‐^000000";
			close;
		}
		mes "[クレヴァー]";
		mes "おや、本当に持って来たのか。";
		mes "それより君、ここに入る時に";
		mes "面会申請はしたか？";
		mes "おい～看守！　看守～～！";
		mes "この人の面会申請が済んでいるか";
		mes "確認しなくてもいいのか？";
		next;
		mes "[看守]";
		mes "いいです！　大丈夫です！";
		mes "問題ないです！";
		next;
		mes "^000099‐看守がイラついた声で";
		mes "　遠くから叫んでいる‐^000000";
		next;
		mes "[クレヴァー]";
		mes "ふぅん……。面会は問題ないってさ。";
		mes "いや、一応確認を取らないとね。";
		mes "後で何を言われるかわからないからさ。";
		mes "よし。それじゃぁまずは";
		mes "持ってきてくれたジュースを";
		mes "ありがたく頂くとしよう。";
		next;
		mes "[クレヴァー]";
		mes "見てわかると思うけど、私は囚人だ。";
		mes "特にあげられる物がない。";
		mes "その代わり、君に祝福があるよう";
		mes "祈ってあげよう。";
		delitem 12046,1;
		set ECL_6QUE,5;
		delquest 12281;
		setquest 12282;
		getexp 120000,0;
		getexp 0,80000;
		close;
	case 5:
		mes "[クレヴァー]";
		mes "ふう～。おいしかった。";
		mes "いやーありがとう。";
		mes "ここに閉じ込められた1年の間に";
		mes "訪ねて来た面会客の中で";
		mes "一番気に入ったよ。";
		next;
		menu "エクラージュの昔話を聞く",-;
		mes "[クレヴァー]";
		mes "ああ、そうだな。";
		mes "確かにそのような約束をしたな。";
		mes "よし。じゃあ話すとしよう。";
		next;
		mes "[クレヴァー]";
		mes "そうだな……何から話そうか。";
		mes "セネス王のこと？";
		mes "それとも軍参謀のことか、";
		mes "……他には次元の狭間とか";
		mes "色々あるから、";
		mes "聞きたいものを言ってくれ。";
		while(1) {
			next;
			switch(select("セネス王の父","セネス王","軍参謀シナイム","次元の狭間")) {
			case 1:
				mes "[クレヴァー]";
				mes "これは昔のある王と関連した噂話だ。";
				mes "昔、プロレンスという";
				mes "1級犯罪者がいた。";
				mes "彼は1級犯罪者でありながら、";
				mes "セネスというエクラージュのマヨル、";
				mes "いわゆる王様だな、の父だったんだ。";
				next;
				mes "[クレヴァー]";
				mes "何の罪を犯したかって？";
				mes "ははは、それは誰も知らないんだ。";
				mes "だけどこのエクラージュで、";
				mes "プロレンスという名前を口にするのは";
				mes "^000099事実上禁止^000000されている。";
				next;
				mes "[クレヴァー]";
				mes "君も気を付ける事だな。";
				mes "うっかり口にすると、";
				mes "私の隣に来る事になるかもしれない。";
				mes "ははは。";
				break;
			case 2:
				mes "[クレヴァー]";
				mes "プロレンスの子である";
				mes "セネス王に関する話もある。";
				mes "犯罪者の父を持った王様";
				mes "という事もあったせいか、";
				mes "過激な政治傾向を見せていた。";
				next;
				mes "[クレヴァー]";
				mes "実は精神病だったという噂もある。";
				mes "セネス王が自らイグドラシルの茎を";
				mes "噛み砕いて食べたこともあるらしい。";
				next;
				mes "[クレヴァー]";
				mes "君、想像できるか？";
				mes "マヨルがイグドラシルに";
				mes "害を及ぼす行為が";
				mes "どんな意味を持つのかを。";
				next;
				mes "[クレヴァー]";
				mes "結局はそうした行為によって";
				mes "イグドラシルとの繋がりは";
				mes "途切れてしまったんだ……。";
				next;
				mes "[クレヴァー]";
				mes "彼は徐々に病んでいきながら、";
				mes "最終的には自らの体に火を付けて";
				mes "自決したという噂だ。";
				next;
				mes "[クレヴァー]";
				mes "もちろん、この話は昔の噂話だ。";
				mes "真偽の程は何ともいえない。";
				mes "ただ、一つ確かなのは、セネス王が";
				mes "^000099イグドラシルとの関係を切った";
				mes "最初のマヨル^000000";
				mes "であったことは確かだ。";
				next;
				mes "[クレヴァー]";
				mes "この事によってエクラージュには";
				mes "大変な危機が訪れる。";
				mes "ただし、";
				mes "それはまた別の話だ。";
				break;
			case 3:
				mes "[クレヴァー]";
				mes "ふふ。これも突拍子も無い噂話だよ。";
				mes "エクラージュに住む殆どのラフィネが";
				mes "わかっていない話だ。";
				mes "軍参謀のシナイムの本名は";
				mes "シナイムではないんだ。";
				next;
				mes "[クレヴァー]";
				mes "だけど、彼女の本名が何だったのかは";
				mes "だれも覚えていない。私も同じだ。";
				mes "まるで巨大な消しゴムで";
				mes "全員の記憶の一部を消したようにね。";
				next;
				mes "[クレヴァー]";
				mes "確かなのは彼女の本名が";
				mes "絶対シナイムではないという事だけだ。";
				mes "そこで私は面白い仮説を立てた。";
				mes "君は集団群衆制御という話を";
				mes "聞いたことがないかね？";
				next;
				mes "[クレヴァー]";
				mes "強力な群衆制御能力を持ってすれば";
				mes "自身の本名、元の顔、声さえも";
				mes "元の自分ではなく、今の自分が本当だと";
				mes "信じさせることができる、らしい。";
				next;
				mes "[クレヴァー]";
				mes "シナイムはそのような力を";
				mes "持っていたのか。";
				mes "あるいは……そのような力で";
				mes "他の誰かにそうさせられたのか……。";
				next;
				mes "[クレヴァー]";
				mes "まぁ……";
				mes "噂だよ。噂。";
				break;
			case 4:
				mes "[クレヴァー]";
				mes "囚われの身であれなんだが……";
				mes "実は元々私は歴史学者なのだよ。";
				mes "このアールブヘイムの";
				mes "過去から現在までの地理、生物、考古学";
				mes "そういったものを一緒に研究していた。";
				mes "勿論、今もしているよ。";
				next;
				mes "[クレヴァー]";
				mes "それで、最近の話になるんだがね。";
				mes "この付近で亀裂が発見されたんだ。";
				mes "当然、今の私の状況では";
				mes "現地に見に行く事は出来なかったが、";
				mes "わたしの同僚が調査団として参加し";
				mes "何かを得て戻って来たようなんだ。";
				next;
				menu "何か？",-;
				mes "[クレヴァー]";
				mes "そうだ。狭間の鉱石を持って来た。";
				mes "君は知っているか？";
				mes "次元の狭間を利用すると";
				mes "時空や次元の壁を越えて";
				mes "移動する事が可能なんだ。";
				next;
				mes "[クレヴァー]";
				mes "あ～そうか、忘れていたよ。";
				mes "君はミッドガルド大陸から";
				mes "飛んで来た旅人だったな。";
				mes "狭間の存在は知っていて当然か。";
				next;
				mes "[クレヴァー]";
				mes "まぁとにかく、技術者や科学者達が";
				mes "仕組みや謎の解明に向け";
				mes "色々研究を重ねている所だろう。";
				next;
				mes "[クレヴァー]";
				mes "うむ。しかし楽しみだな。";
				mes "過去との連絡が可能になる";
				mes "こんなことがもし実現するとしたら";
				mes "君なら何をするかね？";
				mes "ふふ。";
				next;
				mes "[クレヴァー]";
				mes "さて、少ししゃべり過ぎたようだ。";
				mes "ハーブティー一杯の対価としては";
				mes "充分だったんじゃないかな。";
				mes "私は少し休むことにするよ。";
				next;
				mes "[クレヴァー]";
				mes "あ、そうそう。";
				mes "先ほどの狭間の鉱石の話だが";
				mes "詳しく知りたいのであれば、";
				mes "私の友人^000099ヒエール^000000を";
				mes "訪ねて見るといい。";
				next;
				mes "[クレヴァー]";
				mes "彼の家は、街の南の方にある。";
				mes "私と似ているが、悪い奴ではない。";
				mes "まさに研究者の中の研究者だよ。";
				next;
				mes "[クレヴァー]";
				mes "久々に実のある話が出来て楽しかった。";
				mes "普段は看守相手にふざけた歌を";
				mes "歌ってるばかりだからな。はは……。";
				mes "今日はありがとう。";
				mes "もう休む事にする。";
				next;
				set ECL_6QUE,6;
				delquest 12282;
				setquest 12283;
				mes "‐クレヴァーは深い眠りについた。";
				mes "　まずは看守に面会終了を";
				mes "　報告しよう‐";
				close;
			}
			next;
			mes "[クレヴァー]";
			mes "他にもあるぞ。";
		}
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		mes "^000099‐クレヴァーはぐっすり寝ている。";
		mes "　起こさない様に気を付けよう‐^000000";
		close;
	case 18:
		mes "[クレヴァー]";
		mes "る～るるる～。";
		mes "よく寝たから気分がいいな～。";
		mes "ふんふんふん～。ふふふ～。";
		next;
		mes "[クレヴァー]";
		mes "おや、君は確か、";
		mes "ブドウ果汁入りハーブティーを";
		mes "くれた人じゃないか。";
		mes "ははは。どうしたんだい。";
		next;
		if(select("反応しました","通り過ぎる") == 2) {
			mes "[クレヴァー]";
			mes "なんだ？　無視するのか？";
			mes "寂しいもんだな。";
			close;
		}
		mes "[クレヴァー]";
		mes "ん？　なんだって！";
		mes "待ってくれ……。";
		mes "小さな声でもう一度言ってくれ";
		next;
		menu "狭間の鉱石の反応に成功しました",-;
		mes "[クレヴァー]";
		mes "信じられない。君が協力したのか？";
		mes "いや、それはいいか。";
		mes "一体どうやって可能にしたんだ!?";
		next;
		mes "[クレヴァー]";
		mes "狭間の鉱石が反応するとき";
		mes "触媒の周りには反作用で";
		mes "常識を超える力が放出される。";
		mes "よく知られている事だ。";
		mes "それをどう処理したというんだ？";
		next;
		menu "経緯を話す",-;
		mes "[クレヴァー]";
		mes "そうか、必要な材料を君が集めて";
		mes "技術的な問題は";
		mes "ヒエールが何とかしたという事か。";
		mes "では、反応後に何か特別な事が";
		mes "起きただろう？";
		next;
		mes "[クレヴァー]";
		mes "私の見立てでは過去との通信が";
		mes "可能になるはずなんだ！";
		mes "何が起きた？";
		mes "君が何を見たのか教えてくれ。";
		next;
		menu "ここまでの出来事を話す",-;
		mes "[クレヴァー]";
		mes "なに？　ホームツリーの話をしていた";
		mes "二人のラフィネが出てきた？";
		mes "ということは、";
		mes "過去との通信に成功したのか!?";
		mes "何という事だ！　ついにやったか！";
		mes "しかし二人……？　ホームツリー？";
		next;
		mes "[クレヴァー]";
		mes "ふむ……";
		mes "ちょっと待ってくれ。";
		mes "思い当たる節がある。";
		mes "過去の文献を探してくるから";
		mes "ここで待っていてくれ。";
		next;
		mes "‐クレヴァーが歴史書を探している。";
		mes "　もう一度話しかけてみよう‐";
		set ECL_6QUE,19;
		delquest 12289;
		setquest 12290;
		close;
	case 19:
		mes "[クレヴァー]";
		mes "あったぞ。私が投獄される前に";
		mes "関心を持っていた分野がこれだ。";
		mes "エクラージュの誕生に関する歴史。";
		mes "公認の歴史書には";
		mes "記録されていない内容も含めた";
		mes "完全版の歴史だ。";
		next;
		menu "完全版？",-;
		mes "[クレヴァー]";
		mes "大きな業績があったにもかかわらず";
		mes "公式の歴史書には含まれない物がある。";
		next;
		mes "[クレヴァー]";
		mes "^000099ドナ間の勢力争い^000000";
		mes "^000099ドナ間の殺し合い^000000";
		mes "例えばこういったものは";
		mes "公式の歴史書には載らない。";
		next;
		menu "ドナ？",-;
		mes "[クレヴァー]";
		mes "ドナは上級のラフィネ達の事だ。";
		mes "貴族というのかね。";
		mes "パパンと呼ばれる一般層の上位さ。";
		mes "マヨル、つまり王様はこのドナから";
		mes "一人選ばれているんだよ。";
		next;
		menu "なるほど",-;
		mes "[クレヴァー]";
		mes "うむ。だから彼らには";
		mes "広まると都合の悪い話というのは";
		mes "いくらでもある。";
		mes "そうした内容は、公式の歴史書には";
		mes "残らないんだよ。";
		next;
		menu "闇に葬り去られる？",-;
		mes "[クレヴァー]";
		mes "いや、歴史は歴史だからな。";
		mes "例え公式には残されなくても";
		mes "私のような学者達が";
		mes "続けて記録を伝承している";
		mes "非公式の歴史書がある。";
		next;
		mes "[クレヴァー]";
		mes "もちろん、ドナ勢力の中でも";
		mes "特に上級の者達にとっては";
		mes "都合の悪い内容だ。";
		mes "政治的な目的で歪曲されたものも多い。";
		mes "見つかれば命の危険すらあるだろう。";
		next;
		mes "[クレヴァー]";
		mes "先人の学者達は代々";
		mes "そうした危険を顧みずに";
		mes "嘘偽りない真の歴史書を";
		mes "受け継いできてくれたわけだ。";
		next;
		mes "[クレヴァー]";
		mes "私はその意志を引き継ぎ、";
		mes "隠された真実を暴き、";
		mes "嘘偽りない歴史を";
		mes "繋いで行く事を天職としている。";
		next;
		menu "つまり今、監獄にいる理由は……",-;
		mes "[クレヴァー]";
		mes "いや。";
		mes "私は落書きをして捕まっただけさ。";
		next;
		menu "…………",-;
		mes "[クレヴァー]";
		mes "ふふ。話を戻そう。";
		mes "今、君が聞いたというエクラージュの";
		mes "ホームツリーに関する話だが、";
		mes "我々の持つ歴史書には";
		mes "非公式の歴史として残っている。";
		next;
		mes "[クレヴァー]";
		mes "君が見た髪が短かったという者。";
		mes "それは恐らく^ff0000エスラン^000000という名前の";
		mes "ドナだと思う。";
		mes "エクラージュのために、";
		mes "ビフロストの回復を最優先に";
		mes "主張した者だ。";
		next;
		mes "[クレヴァー]";
		mes "そして長髪の者は^ff0000ロベル^000000という名前の";
		mes "ドナに間違いないだろう。";
		mes "ビフロストの回復を保留にし、";
		mes "ホームツリーの創造を最優先する事を";
		mes "主張した勢力のリーダーだ。";
		next;
		mes "[クレヴァー]";
		mes "非公式の歴史書によると";
		mes "彼等二人の対立が根深いという理由で";
		mes "エクラージュの誕生に";
		mes "大きな貢献をしたにも関わらず、";
		mes "公式の記録には";
		mes "残らなかったようだ。";
		next;
		mes "[クレヴァー]";
		mes "しかし……";
		mes "その時見た、聞いた内容は";
		mes "君の眼にはどのように映った？";
		mes "今のこのエクラージュはとても平和だ。";
		mes "上級職のドナたちの争いが";
		mes "あったにしては平和すぎる。";
		next;
		switch(select("平和にはみえない","平和にみえる")) {
		case 1:
			mes "[クレヴァー]";
			mes "そうか？　ただ、少なくとも";
			mes "ここのホームツリーはどうだ？";
			mes "問題なく生きている！";
			mes "そしてあのビフロストの植物たちも";
			mes "何も問題なく生きている……！";
			break;
		case 2:
			mes "[クレヴァー]";
			mes "そう、君の言う通りだ。";
			mes "ここのホームツリーは生きている。";
			mes "そしてあのビフロストの植物たちも";
			mes "何も問題なく生きている。";
			break;
		}
		next;
		mes "[クレヴァー]";
		mes "本当に争いがあったのか？";
		mes "公式の歴史書に記録されない程の";
		mes "大きな対立がもしあったのならば、";
		mes "このエクラージュとビフロストは";
		mes "絶対に今のような平和な姿に";
		mes "なっているはずはないと思うんだ。";
		next;
		mes "[クレヴァー]";
		mes "駄目だ。ここにある物だけでは";
		mes "どうにも説明しきれん。";
		mes "少し待ってくれ。";
		mes "推薦したい書籍がある。";
		mes "紙に場所を書くから、";
		mes "直接行って確かめてみてくれ。";
		next;
		mes "‐クレヴァーの書いてくれた";
		mes "　メモを見ると";
		mes "　ホームツリーの図書館に";
		mes "　行く必要があるようだ‐";
		set ECL_6QUE,20;
		delquest 12290;
		setquest 12291;
		close;
	case 20:
	case 21:
		mes "[クレヴァー]";
		mes "紙に書いた場所に行って、";
		mes "直接確かめてみてくれ。";
		close;
	case 22:
		mes "[クレヴァー]";
		mes "お、戻ったか。";
		next;
		menu "読んできました",-;
		mes "[クレヴァー]";
		mes "そうか。雑誌はどうだった？";
		mes "3流雑誌だと言われているけど、";
		mes "実は歴史書よりも詳しい内容が";
		mes "正確に書かれてあるんだ。";
		next;
		mes "[クレヴァー]";
		mes "3流として烙印されているからな。";
		mes "検閲もないし、そうそう信じないし";
		mes "ちょうどいいんだ。";
		mes "で、何か見つけたか？";
		while(1) {
			next;
			if(select("特にない","質問がある") == 2)
				break;
			mes "[クレヴァー]";
			mes "そうか。";
			mes "目の利く旅人だと思っていたが、";
			mes "私の間違いか。";
		}
		mes "[クレヴァー]";
		mes "ほう。何でも聞いてくれ。";
		while(1) {
			next;
			switch(select("パパンについて","元老会について","エスランとロベルについて","マヨル・ジュンについて")) {
			case 1:
				mes "[クレヴァー]";
				mes "パパンは一般のラフィネ達の事だ。";
				mes "全体の90%がこのパパンだ。";
				mes "ドナは上流階級の貴族だ。";
				mes "お互いに尊重しあっていて、";
				mes "対立などがあった歴史は";
				mes "基本的には無い。";
				next;
				mes "[クレヴァー]";
				mes "パパンは数が多いので";
				mes "いくつもの集団がある。";
				mes "そうした集団の長達は";
				mes "定期的に集まって集会をしている。";
				mes "文献で元老会と対立していたのは";
				mes "恐らくこうした集団の事だろう。";
				continue;
			case 2:
				mes "[クレヴァー]";
				mes "元老会か。";
				mes "高齢のドナ達で構成された、";
				mes "集まりの事だ。";
				mes "ラフィネの伝統や血統の伝承を";
				mes "管理したり、守る事を目的として";
				mes "最初は結成されたようだ。";
				next;
				mes "[クレヴァー]";
				mes "しかし、時間が経つにつれ";
				mes "あらゆる政治的問題に";
				mes "幅をきかせるようになっていった。";
				next;
				mes "[クレヴァー]";
				mes "しきたりを管理したり、";
				mes "伝統の保護を続けるうちに";
				mes "少しずつ影響力が増したんだろう。";
				mes "ラフィネは寿命が長いからな。";
				continue;
			case 3:
				mes "[クレヴァー]";
				mes "エスランとロベルの話を読んだか。";
				mes "実を言うと大半のラフィネ達は";
				mes "この地が当時の貴族勢力である";
				mes "元老会のおかげで成り立っていると";
				mes "思っている。";
				next;
				mes "[クレヴァー]";
				mes "しかし、実際の歴史は";
				mes "若いラフィネたちの犠牲で";
				mes "成り立っている。";
				mes "初めは歴史学者である私も";
				mes "にわかには信じられなかった。";
				next;
				mes "[クレヴァー]";
				mes "続けて発見される非公式の資料に";
				mes "若き二人のラフィネに関する記述が";
				mes "非常に具体的に書かれている。";
				mes "どうやって正統歴史書を本当だと";
				mes "受け入れることができるんだ？";
				next;
				mes "[クレヴァー]";
				mes "だから私は関連する論文を書いて";
				mes "一度発表してみたんだよ。";
				mes "結果は……";
				mes "認めてもらえなかった。";
				next;
				mes "[クレヴァー]";
				mes "若い学者が歴史の真実を訴えても";
				mes "誰も振り向いてくれなかったよ。";
				next;
				mes "[クレヴァー]";
				mes "それで私は論文の発表後に";
				mes "エクラージュにある壁面のそこらに";
				mes "「くたばれ元老会の嘘つき共！」";
				mes "とスプレーをしていたら";
				mes "捕まってしまったんだ。";
				mes "上手くいきそうだったんだがな。";
				next;
				set ECL_6QUE,23;
				delquest 12292;
				setquest 72566;
				mes "[クレヴァー]";
				mes "ちょっと待った！";
				mes "看守がここを気にしているようだ。";
				mes "少し話題を変えよう。";
				close;
			case 4:
				mes "[クレヴァー]";
				mes "マヨル・ジュン？";
				mes "言い易い様に王様と呼んでいる。";
				mes "私達の間ではアイドルのような存在だ。";
				next;
				mes "[クレヴァー]";
				mes "もちろん、私とヒエールのような";
				mes "学者は特に興味はない。";
				mes "私は現実の世界に";
				mes "興味を持っていないからな。";
				continue;
			}
		}
	case 23:
		mes "[クレヴァー]";
		mes "看守がここを気にしているようだ。";
		mes "少し話題を変えよう。";
		close;
	case 24:
		mes "[クレヴァー]";
		mes "ん？　何でもなかったか。";
		mes "私はてっきり";
		mes "君との会話が長引いているのを";
		mes "看守が嫌がっているのかと……。";
		next;
		mes "^000099‐正反対だ‐^000000";
		next;
		mes "[クレヴァー]";
		mes "それで何だが……";
		mes "ここからの内容は";
		mes "これまで誰にも話していない";
		mes "秘密が含まれてくる。";
		next;
		mes "[クレヴァー]";
		mes "万が一これから私が話す内容を";
		mes "聞きたくないのであれば、";
		mes "今までの話はなかったことにしてくれ。";
		next;
		mes "[クレヴァー]";
		mes "ただ、もし今回の話に興味があり、";
		mes "今後協力してくれるというのであれば、";
		mes "これから聞く話は全て秘匿し";
		mes "絶対に他言しないようにしてほしい。";
		next;
		mes "[クレヴァー]";
		mes "どうだろう？　約束できるか？";
		next;
		if(select("約束する","約束出来ない") == 2) {
			mes "[クレヴァー]";
			mes "残念だ。";
			mes "ここまで私の話を聞いてくれた旅人は";
			mes "君が初めてだったのに。";
			mes "まあ、考えが変わったら";
			mes "いつでも私を訪ねて来てくれ。";
			close;
		}
		mes "[クレヴァー]";
		mes "素晴らしい。ありがとう。";
		mes "では取引成立だな。";
		mes "まずは君の好意に感謝し、";
		mes "ホームツリーに加護を祈るとする。";
		set ECL_6QUE,25;
		delquest 72568;
		setquest 72570;
		getexp 120000,0;
		getexp 0,80000;
		close;
	case 25:
		mes "[クレヴァー]";
		mes "よし。では続きを話そう。";
		mes "ただ秘密と言っても実はな、";
		mes "君は既に一度";
		mes "見ているはずなんだ。";
		next;
		mes "[クレヴァー]";
		mes "ヒエールが狭間の鉱石の研究を";
		mes "していただろう。";
		mes "彼も私と同じ目的で";
		mes "研究をしていたんだ。";
		next;
		mes "[クレヴァー]";
		mes "^000099空間を超越し過去のラフィネとの";
		mes "交信を行う^000000という事だ。";
		next;
		mes "[クレヴァー]";
		mes "私は歴史の事実を知る為に、";
		mes "ヒエールはホームツリーの内部設計を";
		mes "知るために。";
		next;
		menu "なるほど",-;
		mes "[クレヴァー]";
		mes "うむ。そして今回、";
		mes "君が交信に必要な材料を";
		mes "用意してくれた事によって";
		mes "とうとう実験が成功したわけだ。";
		next;
		mes "[クレヴァー]";
		mes "恐らく、私とこうして話している間にも";
		mes "ヒエールは狭間の作動方法など";
		mes "実用化に向けて調整しているはずだ。";
		next;
		mes "[クレヴァー]";
		mes "もしかすると既に";
		mes "過去のラフィネ達との交信が";
		mes "安定して出来るかもしれない。";
		mes "それですまないんだが……";
		next;
		mes "[クレヴァー]";
		mes "ヒエールに会って、過去のエスラン達と";
		mes "通信を試みてきてくれないか。";
		mes "本当は私が行きたいんだが……。";
		next;
		mes "[クレヴァー]";
		mes "そしてなんでもいいから";
		mes "彼らの話を全て記録して";
		mes "私に知らせてくれ。お願いだ。";
		mes "頼んだぞ！";
		set ECL_6QUE,26;
		delquest 72570;
		setquest 12293;
		close;
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
		mes "[クレヴァー]";
		mes "ヒエールに会って、過去のエスラン達と";
		mes "通信を試みてきてくれないか。";
		next;
		mes "[クレヴァー]";
		mes "そしてなんでもいいから";
		mes "彼らの話を全て記録して";
		mes "私に知らせてくれ。お願いだ。";
		mes "頼んだぞ！";
		close;
	case 38:
		mes "[クレヴァー]";
		mes "おお。戻ったか。";
		next;
		mes "[クレヴァー]";
		mes "それで、どうだった？";
		mes "ヒエールの研究は";
		mes "実を結んだか？";
		next;
		menu "これまでの話を伝える",-;
		mes "[クレヴァー]";
		mes "そうかー。そうだったか。";
		mes "やはり、エスランとロベル、";
		mes "若い二人のドナの犠牲によって";
		mes "エクラージュは成り立っていたんだな。";
		mes "公式歴史書の内容は間違いだった。";
		next;
		mes "[クレヴァー]";
		mes "本当にご苦労だった。";
		mes "ありがとう、" +strcharinfo(0)+ "";
		mes "君がいなかったら、";
		mes "監獄で閉じ込められた身のまま、";
		mes "何一つ進まなかっただろう。";
		next;
		mes "[クレヴァー]";
		mes "しかし……二人の覚悟は凄いな。";
		mes "う～む。";
		mes "なぁ、君はどう思う？";
		mes "あの二人は再び、";
		mes "会う事ができたと思うか？";
		next;
		switch(select("会えなかった","会えた","どこかできっと")) {
		case 1:
			mes "[クレヴァー]";
			mes "……君の答えはそうか。";
			mes "でも確かに、";
			mes "その可能性が一番高そうだ。";
			mes "少し、残念な気もするが……。";
			break;
		case 2:
			mes "[クレヴァー]";
			mes "なぜだろうな。君がそういってくれて";
			mes "安堵している自分がいるんだ。";
			mes "長年の疑問が解決した反動で";
			mes "気持ちが少し、";
			mes "緩んだのかもしれないな……。";
			break;
		case 3:
			mes "[クレヴァー]";
			mes "……どこかできっと、か。";
			mes "君は意外とロマンチストだな。";
			mes "そのどこかが是非";
			mes "この地、エクラージュであることを";
			mes "願うばかりだ。";
			break;
		}
		next;
		mes "[クレヴァー]";
		mes "どちらにしろ……。";
		mes "私たちが、知る由もない話だ。";
		next;
		mes "[クレヴァー]";
		mes "なにはともあれ、";
		mes "今回は久々に満足いく結果が出た！";
		mes "よかった。よかった。";
		next;
		cutin "EP14_etran1",1;
		mes "^000099‐笑っているクレヴァーの顔に";
		mes "　エスランの影が重ねて見えた‐^000000";
		next;
		cutin "EP14_etran1",255;
		mes "[クレヴァー]";
		mes "おや、その手に持っている";
		mes "首飾りはなんだ？";
		next;
		menu "エスランから貰いました",-;
		mes "[クレヴァー]";
		mes "なんだって？";
		mes "ちょっと見せてくれないか。";
		mes "どれどれ……。";
		next;
		mes "[クレヴァー]";
		mes "おお。これは、すごい。";
		mes "秘められた能力があるようだな。";
		mes "ヒエールのもとに持っていけば";
		mes "その力を解放できると思うぞ。";
		mes "一度訪れてみるといい。";
		next;
		mes "[クレヴァー]";
		mes "しかし君には";
		mes "本当に世話になった。";
		mes "長い間ありがとう。";
		mes "おかげで出所後に書く歴史書に";
		mes "執筆すべき内容が一気に増えたよ。";
		next;
		mes "[クレヴァー]";
		mes "最後に君の歩む道に祝福があるよう、";
		mes "祈らせてもらうとするよ。";
		mes "元気でな！";
		mes "私は早速執筆作業に入らせてもらうよ。";
		next;
		mes "[クレヴァー]";
		mes "それと、これはささやかなお礼だ。";
		mes "受け取ってくれ。";
		next;
		if(checkitemblank() == 0) {
			mes "[クレヴァー]";
			mes "と思ったけど、荷物が多くて";
			mes "それ以上持てないようだな。";
			mes "アイテムの種類数を減らしてから";
			mes "また来てくれ。";
			close;
		}
		mes "‐クレヴァーは執筆を始めた。";
		mes "　このことをヒエールに伝えよう‐";
		set ECL_6QUE,39;
		delquest 72578;
		setquest 72580;
		getexp 4060000,0;
		getexp 0,1880000;
		getitem 6081,50;
		close;
	case 39:
	case 40:
	case 41:
		mes "^000099‐黙々と筆記用具で何かを";
		mes "　一所懸命に書いている。";
		mes "　早速執筆しているようだ‐^000000";
		close;
	}
}

ecl_in04.gat,109,215,3	script	ヒエール	621,{
	switch(ECL_6QUE) {
	case 7:
		mes "[ヒエール]";
		mes "ふーむ……。";
		mes "ここの数式が違うのかな。";
		mes "ん、待てよ。";
		mes "中心極限定理によればここは……";
		next;
		menu "こんにちは",-;
		mes "[ヒエール]";
		mes "ん？　何の用件ですか？";
		mes "ここは勝手に入って来ちゃいけません。";
		next;
		menu "紹介を受けて来ました。",-;
		mes "[ヒエール]";
		mes "紹介？　どこの誰からの紹介ですか。";
		mes "教えてください。";
		next;
		input '@str$;
		if('@str$ != "クレヴァー") {
			mes "[ヒエール]";
			mes '@str$+ "だと？";
			mes "私はそのような人は知らない！";
			mes "怪しい奴だな。出て行け！";
			close2;
			warp "eclage.gat",152,91;
			end;
		}
		mes "["+strcharinfo(0)+"]";
		mes "クレヴァーさんの紹介で来た";
		mes strcharinfo(0)+ "といいます。";
		next;
		mes "[ヒエール]";
		mes "おお、クレヴァーの紹介ですか。";
		mes "それはそれは。わかりました。";
		mes "途中だった作業を終わらせるので";
		mes "少し待っててください。";
		next;
		mes "‐途中の作業を片付けてくれるようだ。";
		mes "　もう一度、話しかけよう‐";
		set ECL_6QUE,8;
		delquest 72554;
		setquest 72556;
		close;
	case 8:
		mes "[ヒエール]";
		mes "お待たせしました。";
		mes "しかし変わり者のあのクレヴァーと";
		mes "よく普通に会話が出来ましたね。";
		mes "よっぽど好かれたのか、";
		mes "あなたも変わり者なのか。はは。";
		mes "いや、失礼。それであいつは何て？";
		while(1) {
			next;
			switch(select("会話をやめる","セネス王の父について","セネス王について","軍参謀シナイムについて","次元の狭間について")) {
			case 1:
				mes "[ヒエール]";
				mes "え、はい？　わざわざ訪ねてきたのに？";
				mes "やはりあいつと同じで";
				mes "とんだ変わり者ですね。";
				mes "私は忙しいんです。";
				mes "用件が無いなら帰って下さい。";
				close;
			case 2:
				mes "[ヒエール]";
				mes "私はここの王族に関する噂は";
				mes "興味がありません。";
				continue;
			case 3:
				mes "[ヒエール]";
				mes "どうでもいい話ですね。";
				continue;
			case 4:
				mes "[ヒエール]";
				mes "今の名前が本名じゃない？";
				mes "だからどうしたんですか？";
				continue;
			case 5:
				break;
			}
			break;
		}
		mes "[ヒエール]";
		mes "お～。その話を聞いたんですか。";
		mes "あなたは見る目があるようですね。";
		mes "クレヴァーが言っていたと思いますが、";
		mes "私の部屋には狭間から持って来た";
		mes "狭間の鉱石があります。内緒ですよ。";
		mes "これはね……";
		next;
		mes "^000099‐そういうとヒエールは嬉しそうに";
		mes "　狭間の鉱石が入った箱を見せながら、";
		mes "　約30分間、休まずに話を続けた‐^000000";
		next;
		mes "^000099‐これは……クレヴァーとは違う意味で";
		mes "　疲れるタイプのようだ。";
		mes "　なんとか話を切らないと……";
		mes "　何かこちらから話を振ろう‐^000000";
		while(1) {
			next;
			switch(select("狭間の鉱石の用途を聞く","狭間の鉱石の入手方法を聞く","狭間の鉱石の実用化について聞く")) {
			case 1:
				mes "[ヒエール]";
				mes "はい。まさにその点を研究中です。";
				mes "この狭間の鉱石を使うと、";
				mes "過去と未来の空間概念を超えて";
				mes "次元間の壁を壊してくれるということは";
				mes "分かっています。";
				next;
				mes "[ヒエール]";
				mes "つまりどういう事かというと、";
				mes "狭間の鉱石を上手く利用すると、";
				mes "^000099過去の人物に会う事^000000が";
				mes "出来るようになる可能性があるんです。";
				continue;
			case 2:
				mes "[ヒエール]";
				mes "最近、ここの近くに";
				mes "巨大な亀裂が出来ました。";
				mes "今はラフィネの兵士たちの監視により";
				mes "入場禁止になっていますが、";
				mes "発見当初は調査のために、";
				mes "私たちのような研究者が入れたんです。";
				next;
				mes "[ヒエール]";
				mes "その時にひとつ持って来ています。";
				mes "もちろん見つかれば";
				mes "私は監獄行きです。";
				mes "絶対に他言はしないで下さい。";
				mes "クレヴァーの紹介のあなただからこそ";
				mes "信用してお話しています。";
				continue;
			case 3:
				break;
			}
			break;
		}
		mes "[ヒエール]";
		mes "実用化……ですか。";
		mes "……。";
		next;
		menu "どうしました？",-;
		mes "[ヒエール]";
		mes "実は、色々な手段を使っているんですが";
		mes "はは……。";
		mes "この狭間の鉱石がね……なかなか。";
		next;
		mes "[ヒエール]";
		mes "言う事を聞いてくれないんです。";
		mes "正直、";
		mes "反応さえもありません。";
		mes "はぁ……。";
		next;
		mes "[ヒエール]";
		mes "私はね、物質としてのルールを無視した";
		mes "反物質とも呼べるこの鉱石が、";
		mes "一体どんな反応をみせるのか";
		mes "そして、その時何が起こるのか……";
		mes "必ず！　必ずや！";
		next;
		mes "[ヒエール]";
		mes "この目で確かめてみたいんですよ。";
		mes "ただ、見たいんです。";
		mes "それだけです。";
		next;
		mes "[ヒエール]";
		mes "けど、特別な支援があるわけでもなく、";
		mes "手がかりがあるわけでもない。";
		mes "手詰まりの状態ですよ。はは。";
		next;
		mes "[ヒエール]";
		mes "ん。そういえば……";
		mes "あなたのいた世界では、";
		mes "すでに狭間の鉱石と反応する物質の";
		mes "調合に成功したと聞いたけど、";
		mes "あの猫の話は本当だったのかな。";
		next;
		menu "猫？",-;
		mes "[ヒエール]";
		mes "実は猫の手サービスの出身だという猫が";
		mes "ミッドガルド大陸、いわゆる人間界で";
		mes "書かれたという本を";
		mes "販売しに来たことがあるんです。";
		next;
		mes "[ヒエール]";
		mes "その時に猫はこう言いました。";
		mes "私が研究している内容に関して";
		mes "有意義な内容が書かれた本もある、と。";
		mes "研究内容を知っているはずはないし、";
		mes "あまりに突拍子も無い話だったので";
		mes "追い出してしまったのです。";
		next;
		menu "猫は金が関わる話には誠実です",-;
		mes "[ヒエール]";
		mes "そうだったんですね。";
		mes "そうすると本当だったのか。";
		mes "しかし何故私の研究を……。";
		mes "まぁその事はいいとしましょう。";
		mes "それよりです。";
		next;
		mes "[ヒエール]";
		mes "このようなことを頼むのは";
		mes "申し訳ないのですが、";
		mes "改めてその猫たちから";
		mes "狭間の鉱石に関する情報を";
		mes "調べて来てもらえませんか？";
		next;
		mes "[ヒエール]";
		mes "私が直接行けばいいのでしょうが、";
		mes "見ての通り研究を続けなくては";
		mes "いけないものですから……。";
		mes "お願いします。どうでしょうか？";
		next;
		if(select("手伝う","断る") == 2) {
			mes "[ヒエール]";
			mes "そうですか……。";
			mes "やっぱり、無理ですか。";
			mes "それならしょうがないですね。";
			set ECL_6QUE,9;
			close;
		}
		mes "[ヒエール]";
		mes "おお！　本当にありがとうございます！";
		mes "この恩は研究結果が出た場合に";
		mes "必ずお返しします！";
		mes "ではその間、私は物質調合の";
		mes "準備をしておきます。";
		next;
		mes "[ヒエール]";
		mes "ミッドガルド連合軍駐屯地に";
		mes "シエルビーという猫がいるはずです。";
		mes "お願いします。";
		set ECL_6QUE,10;
		delquest 72556;
		setquest 12284;
		close;
	case 9:
		mes "[ヒエール]";
		mes "おや、私の頼みを聞いてくれますか？";
		mes "猫から狭間の鉱石に関する情報を";
		mes "調べて来てもらえますか？";
		next;
		if(select("手伝う","断る") == 2) {
			mes "[ヒエール]";
			mes "そうですか……。";
			mes "やっぱり、無理ですか。";
			mes "そんなわざわざ話に来て、";
			mes "また断らなくても……。";
			close;
		}
		mes "[ヒエール]";
		mes "おお！　ありがとうございます！";
		mes "この恩は研究結果が出た場合に";
		mes "必ずお返しします！";
		mes "ではその間、私は物質調合の";
		mes "準備をしておきます。";
		next;
		mes "[ヒエール]";
		mes "ミッドガルド連合軍駐屯地に";
		mes "シエルビーという猫がいるはずです。";
		mes "お願いします。";
		set ECL_6QUE,10;
		delquest 72556;
		setquest 12284;
		close;
	case 10:
	case 11:
	case 12:
		mes "[ヒエール]";
		mes "猫の手サービスは、";
		mes "モーラからエルディカスティスの間まで";
		mes "色々な場所にいます。";
		mes "恐らくはミッドガルド連合軍駐屯地に";
		mes "いるはずですが……。";
		close;
	case 13:
		mes "[ヒエール]";
		mes "おお、どうでしたか。";
		mes "何か成果がありましたか？";
		next;
		menu "猫から聞いた話を伝える",-;
		mes "[ヒエール]";
		mes "そうでしたか。";
		mes "闇の破片にジェムストーン、か。";
		mes "どちらも初めて聞く名前です。";
		mes "ここには無い物なんでしょう。";
		mes "私が行おうとした研究は";
		mes "不可能に近い事だったのか……。";
		next;
		if(countitem(7798) > 0 && countitem(715) > 1 && countitem(716) > 1 && countitem(717) > 1) {
			set '@flag,1;
		}
		switch(select("諦めましょう",'@flag? "必要な物を集めてきた": "必要な物を集めてみる")) {
		case 1:
			mes "[ヒエール]";
			mes "やはり物理の原則に反する行動は";
			mes "不可能だよな……。";
			close;
		case 2:
			if(!'@flag) {
				mes "[ヒエール]";
				mes "本当ですか？　是非お願いします。";
				mes "すごく助かります！";
				mes "私はここで待っています。";
				close;
			}
			break;
		}
		mes "[ヒエール]";
		mes "おお、これがその例の、";
		mes "闇の破片とジェムストーンですか。";
		mes "これさえあれば実験を";
		mes "続けることができます。";
		mes "本当にありがとうございます！";
		next;
		if(select("用意した物を渡す","用意はしたが渡すとは言ってない") == 2) {
			mes "[ヒエール]";
			mes "えええ！　準備してくれたのに";
			mes "渡してくれないんですか……。";
			mes "そんな。";
			close;
		}
		mes "[ヒエール]";
		mes "ありがとうございます。";
		mes "私の研究が成功すれば、";
		mes "ラフィネ科学史に";
		mes "大きな貢献をするでしょう。";
		mes "あなたのおかげです。";
		mes "ホームツリーの祝福がありますように。";
		delitem 7798,1;
		delitem 715,2;
		delitem 716,2;
		delitem 717,2;
		set ECL_6QUE,14;
		delquest 12286;
		setquest 12287;
		getexp 120000,0;
		getexp 0,80000;
		close;
	case 14:
		mes "[ヒエール]";
		mes "さて、それじゃあ実際にこれを使って";
		mes "ここに置いてこうして、と……。";
		mes "おや……変だな？";
		mes "確かに本に書かれてある通りの";
		mes "配列になっているはずなんだが。";
		mes "どうして反応しないんだ。";
		next;
		mes "[ヒエール]";
		mes "う～む";
		mes "こうすればいいのかな？";
		mes "いや、違うな。";
		mes "こっちか！";
		mes "あれ、こうか？";
		mes "…………";
		next;
		mes "[ヒエール]";
		mes "どうしてダメなんだよ！";
		mes "言う事を聞けよ!!";
		mes "このように配列したら";
		mes "こういう反応が返ってくるべきだろう！";
		mes "何故なんだ！";
		next;
		mes "^000099‐思い通り進まず、暴れるヒエール。";
		mes "　拍子に手から闇の破片が転げ落ちた。";
		mes "　このままでは闇の破片が……！‐^000000";
		next;
		menu "手を伸ばし闇の破片を掴む",-;
		mes "^000099‐床に落ちそうな闇の破片を";
		mes "　すんでの所で掴み取り、";
		mes "　ヒエールがのべていた配列の中に";
		mes "　そっと戻した‐^000000";
		next;
		mes "‐その瞬間！‐";
		next;
		sc_start3 SC_BLIND,0,0,0,0,60000,10;
		mes "^000099‐目の前が暗くなり";
		mes "　何処からか声が聞こえてきた‐^000000";
		next;
		cutin "EP14_etran0",1;
		mes "[？？？？]";
		mes "例えば、君が話していた通り";
		mes "ホームツリーを";
		mes "先に完成させたとしよう。";
		mes "だが、その後はどうする？";
		mes "奴が吸い込む巨大なエネルギーは";
		mes "どうしろというんだ？";
		next;
		cutin "EP14_robert0",1;
		mes "[？？？？]";
		mes "確かにその通りだ。";
		mes "ホームツリーを生き返らせるには、";
		mes "想像をはるかに超える生命力が必要だ。";
		mes "ただ、それでもホームツリーは";
		mes "生き返らせないと駄目だ。";
		mes "必ず必要だ。";
		next;
		cutin "EP14_etran0",1;
		mes "[？？？？]";
		mes "その間に死んでいく";
		mes "他の生命体たちはどうする。";
		mes "ホームツリーの完成のために";
		mes "何十年、何百年間という期間、";
		mes "ホームツリー界隈は";
		mes "不毛の地になるかも知れないんだぞ！";
		next;
		mes "[？？？？]";
		mes "いや、間違いなくなる！";
		mes "ホームツリー以外の生命は全滅だ。";
		mes "ホームツリーは命を助ける為の物だ！";
		mes "これじゃあ本末転倒じゃないか?!";
		next;
		cutin "EP14_robert0",1;
		mes "[？？？？]";
		mes "ホームツリー無しに生命を維持しても、";
		mes "どうせ長くは持たないんだ。";
		mes "ある程度の犠牲は覚悟しないと駄目だ。";
		mes "それは誰よりもお前が";
		mes "知っているだろう！";
		next;
		cutin "EP14_etran0",1;
		mes "[？？？？]";
		mes "やはりホームツリーを完成させつつ";
		mes "その力を利用する事で並行して";
		mes "大地を生き返らせる、という方法が";
		mes "一番早いし、シンプルだろう。";
		next;
		mes "[？？？？]";
		mes "ただ、いずれにせよこの決断で";
		mes "我々の命運を大きく左右するのは";
		mes "間違いない事だ……。";
		mes "果たしてそんな権限が我々に";
		mes "あるんだろうか……！";
		next;
		mes "[？？？？]";
		mes "ホームツリーを生かす事が";
		mes "本当に正しい事なのか？";
		mes "命を左右するような権限など";
		mes "誰も持つべきではないんじゃないか？";
		next;
		cutin "EP14_robert0",1;
		mes "[？？？？]";
		mes "ふふ。良い夢を見ているな、エスラン。";
		mes "必ず選択は必要だ。";
		mes "それが生きるという事だ。";
		mes "誰かが決めなければいけない。";
		next;
		mes "[？？？？]";
		mes "まぁ、私たち二人だけで話しても";
		mes "埒が開かないだろう。";
		mes "私は元老会の決定に従うことにするよ。";
		set ECL_6QUE,15;
		delquest 12287;
		setquest 72560;
		close2;
		cutin "EP14_robert0",255;
		sc_end SC_BLIND;
		end;
	case 15:
		mes "[ヒエール]";
		mes "い、今の！　き、聞こえました？";
		mes "怪しい声が！";
		mes "一体どういう事だ！";
		mes "実験に成功したのか？";
		next;
		menu "聞こえた内容を伝える",-;
		mes "[ヒエール]";
		mes "私と同じ内容ですね。";
		mes "何の話だったんだろう。";
		mes "ホームツリーの創造？";
		mes "そんな話は聞いたことがない。";
		next;
		mes "[ヒエール]";
		mes "同じ話を聞いたという事は";
		mes "この装置の仕業か……。";
		mes "幽霊でないのなら、";
		mes "もう一度会えるかもしれない。";
		mes "ちょっと確認をしてみます。";
		next;
		mes "^000099‐そういうとヒエールは、";
		mes "　再び懸命に配列を動かし始めた‐^000000";
		next;
		mes "^000099‐しかし一向に狭間の鉱石は";
		mes "　反応を示さない‐^000000";
		next;
		mes "[ヒエール]";
		mes "ふぅ。駄目だ。";
		mes "私が何をしても反応しないです。";
		mes "一度やってみますか？";
		set ECL_6QUE,16;
		delquest 72560;
		setquest 12288;
		close;
	case 16:
		mes "[ヒエール]";
		mes "私が何をしても反応しないです。";
		mes "一度やってみますか？";
		close;
	case 17:
		mes "[ヒエール]";
		mes "やはりこれは霊的な内容ではなく、";
		mes "実在した状況を映しているようですね。";
		mes "過去におこった出来事でしょう。";
		next;
		mes "[ヒエール]";
		mes "歴史の一部を見ているのか……";
		mes "これは凄い事だぞ。";
		next;
		menu "先ほどの声は誰ですか？",-;
		mes "[ヒエール]";
		mes "すみません。";
		mes "私は歴史には詳しくありません。";
		mes "ただ、その方面なら一人";
		mes "本当に最高という人材がいます。";
		mes "あなたもよくご存じの方ですよ。";
		next;
		menu "もしかして、クレヴァー？",-;
		mes "[ヒエール]";
		mes "ご名答！";
		mes "確かに相当な変わり者ですが、";
		mes "考古学や歴史に関する知識は";
		mes "間違いありません。";
		next;
		mes "[ヒエール]";
		mes "先ほどの会話を調べるのであれば";
		mes "クレヴァーを訪ねてみてください。";
		mes "私はこいつの配列をもう少し、";
		mes "詳しく研究して見ることにします。";
		set ECL_6QUE,18;
		delquest 72562;
		setquest 12289;
		close;
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
		mes "[ヒエール]";
		mes "先ほどの会話を調べるのであれば";
		mes "クレヴァーを訪ねてみてください。";
		mes "私はこいつの配列をもう少し、";
		mes "詳しく研究して見ることにします。";
		close;
	case 26:
		mes "[ヒエール]";
		mes "おお、こんにちは。いいところに。";
		mes "実はあなたがいない間に";
		mes "持ち運び可能な携帯用次元通信機を";
		mes "作ってみたんですが……";
		mes "少し問題がありまして……。";
		next;
		menu "問題？",-;
		cutin "EP14_robert5",1;
		mes "[？？？？]";
		mes "君は誰だ！";
		mes "どうして私と同じ姿をしている？";
		mes "答えろ！　元老会の差し金か!?";
		next;
		cutin "EP14_robert5",255;
		mes "[ヒエール]";
		mes "落ち着いて私の話を聞いて下さい。";
		mes "私はヒエールといいます。";
		next;
		mes "[ヒエール]";
		mes "少し、複雑な事情が色々重なっていて、";
		mes "その、何と言えばいいのか……。";
		next;
		mes "^000099‐ヒエールととても似たドナが";
		mes "　ヒエールを睨んでいる。";
		mes "　あのドナは何だろう？‐^000000";
		next;
		menu "名前を聞く",-;
		cutin "EP14_robert5",1;
		mes "[？？？？]";
		mes "私か？　私の名前は^000099ロベル^000000。";
		mes "上級生命術師だ。";
		mes "目の前にいる私そっくりな奴と";
		mes "君はどういう関係なんだ？";
		next;
		mes "^000099‐彼がどうやらロベルのようだ‐^000000";
		next;
		menu "今までの状況を説明する",-;
		cutin "EP14_robert1",1;
		mes "[ロベル]";
		mes "なんだと！";
		mes "つまり今話している君達は";
		mes "未来に住む者だということなのか？";
		mes "そんな事が可能なのか!?";
		next;
		mes "[ロベル]";
		mes "にわかには納得できない話だな。";
		mes "……";
		mes "……頭が痛くなってきた。";
		next;
		cutin "EP14_robert1",255;
		mes "["+strcharinfo(0)+"]";
		mes "この装置はそこにいる";
		mes "ヒエールが用意したものです。";
		next;
		cutin "EP14_robert1",1;
		mes "[ロベル]";
		mes "なるほど。";
		next;
		cutin "EP14_robert1",255;
		mes "[ヒエール]";
		mes "はい。まずは今の状況を説明致します。";
		next;
		mes "^000099‐ヒエールは今までの実験内容を";
		mes "　追加で説明し始めた。";
		mes "　ロベルはヒエールの話に耳を傾け";
		mes "　何度もうなずいていた‐^000000";
		next;
		mes "[ヒエール]";
		mes "事情はだいたいこんな所です。";
		mes "すみません、とても興奮していて";
		mes "心を落ち着かせることが難しいです。";
		mes "ロベル様が本当に存在していたとは。";
		next;
		mes "[ヒエール]";
		mes "ロベル様は私たち研究者にとっては";
		mes "伝説のような方です。";
		mes "実在していた事が信じられない程です。";
		next;
		mes "[ヒエール]";
		mes "この巨大なホームツリーという生命体を";
		mes "大地、居住地と融合させて構築する";
		mes "この発想と手法は";
		mes "とても素晴らしい事です。";
		next;
		cutin "EP14_robert3",1;
		mes "[ロベル]";
		mes "ホームツリー。";
		mes "うまく育ったのか……。";
		mes "正直可能性は薄いと考えていたんだが、";
		mes "こんな未来にまで役に立っているとは。";
		mes "そうか。";
		next;
		mes "[ロベル]";
		mes "しかし本当なのか？";
		next;
		menu "事実です",-;
		cutin "EP14_robert1",1;
		mes "[ロベル]";
		mes "不可能だと思っていた。";
		mes "諦めなくてよかったが……";
		mes "どうも実感が湧かん。";
		mes "ちょっとすまないが、今すぐ私を";
		mes "ホームツリーの前まで案内してくれ！";
		mes "嘘じゃない事を見せてくれ！";
		set ECL_6QUE,27;
		delquest 12293;
		setquest 12294;
		close2;
		cutin "EP14_robert1",255;
		end;
	case 27:
		mes "[ヒエール]";
		mes "ホームツリーは中央広場にあります。";
		close;
	case 28:
		mes "[ヒエール]";
		mes "うーむ……やはりここか。";
		mes "出力が足りないんだな。";
		mes "となると……あれを……";
		next;
		mes "[ヒエール]";
		mes "お、ロベル様はどうでしたか。";
		mes "ホームツリーを見て";
		mes "何か言っていましたか。";
		next;
		menu "途中で消えてしまいました",-;
		mes "[ヒエール]";
		mes "そうでしたか……。";
		mes "この携帯用次元通信機は";
		mes "まだ出力がよくないんです。";
		mes "つまり使える範囲が狭いんです。";
		next;
		mes "[ヒエール]";
		mes "ロベル様との交信を行うために";
		mes "この機械の年代記周波数は";
		mes "先ほど発見した時期で固定しました。";
		mes "恐らくこれで同じ時代の";
		mes "ロベル様に繰り返し会えるはずです。";
		next;
		mes "[ヒエール]";
		mes "ただ……特定の場所のみでしか";
		mes "会えないという問題があります。";
		next;
		menu "場所を変えれば色々会える？",-;
		mes "[ヒエール]";
		mes "確かではありませんが、";
		mes "私の予想ではそうなります。";
		mes "生命を持った存在の場合、";
		mes "通信機の範囲から離れると";
		mes "こちらとの交信が断絶されるようです。";
		next;
		mes "[ヒエール]";
		mes "^000099（とても古いペンを見ながら）^000000";
		mes "ロベル様との連絡は途切れましたが、";
		mes "あの方が持っていたペンは";
		mes "ほら。残っているでしょう。";
		next;
		menu "エスランにも会う事ができる？",-;
		mes "[ヒエール]";
		mes "理論上はそうですね。";
		mes "しかし、エスラン様に会うには";
		mes "エスラン様に会える場所を探して";
		mes "そこに行かなければなりません。";
		next;
		mes "[ヒエール]";
		mes "出力を大幅に広げて";
		mes "反応範囲を広げれば";
		mes "可能かも知れませんが、";
		mes "まだ不安定なので……。";
		next;
		menu "私にその通信機を貸してください",-;
		mes "[ヒエール]";
		mes "まさかこれを持って";
		mes "周辺を探索する気ですか？";
		mes "無理ですよ！　外は危険です！";
		while(1) {
			next;
			if(select("私は大丈夫です","あなたの理論を確かめたいでしょう") == 1)
				break;
			mes "[ヒエール]";
			mes "いやいや、";
			mes "あなたの心配はしていません。";
			mes "この大事な通信機が";
			mes "壊れるのが心配なんです。";
		}
		mes "[ヒエール]";
		mes "う……";
		next;
		mes "[ヒエール]";
		mes "うううう……";
		next;
		mes "‐ヒエールはすごく悩んでいる‐";
		next;
		mes "[ヒエール]";
		mes "うぅ……確かに。";
		mes "危険はかなりありますが";
		mes "あなたの言うとおりです。";
		mes "確かめたい！　結果を知りたい！";
		mes "科学者としての性か……。";
		next;
		mes "[ヒエール]";
		mes "……しょうがない。";
		mes "絶対に壊さないで下さい！";
		mes "もう一つ予備の通信機は作りましたが";
		mes "調整が済んでいるのはそれだけです。";
		mes "絶対に無くさないでくださいよ!!!";
		next;
		mes "^000099‐ヒエールから";
		mes "　次元通信機を借りた。";
		mes "　通信機から出ているエネルギーが";
		mes "　祝福の力となって体に入ってきた‐";
		set ECL_6QUE,29;
		delquest 12295;
		setquest 12296;
		getexp 120000,0;
		getexp 0,80000;
		next;
		mes "[ヒエール]";
		mes "エスラン様の居場所で一番有力な場所は";
		mes "ビフロストタワーです。";
		mes "ビフロストタワーは街の外、";
		mes "花が咲き始めた大地の南にあります。";
		mes "くれぐれも、気を付けてください。";
		close;
	case 29:
	case 30:
	case 31:
		mes "[ヒエール]";
		mes "気をつけて使用して下さい。";
		mes "今すぐ稼働が可能なのは";
		mes "それ一台しかないんです。";
		close;
	case 32:
		mes "[ヒエール]";
		mes "お帰りなさい。ふふっ";
		mes strcharinfo(0)+ "さんがいない間に";
		mes "通信機に色々な機能を";
		mes "追加しておきましたよ。";
		next;
		mes "[ヒエール]";
		mes "これでかなり広範囲で";
		mes "狭間に反応する事が可能になりました。";
		mes "さて……これの名前は何にするか。";
		next;
		menu "ホームツリーの葉が欲しいんですが",-;
		mes "[ヒエール]";
		mes "えっ？　急に何を言うんですか。";
		mes "次元通信機の性能がいくらよくても";
		mes "ホームツリーまで創造することは";
		mes "出来ませんよ。これは交信機なんです。";
		next;
		menu "エスランとの約束を説明する",-;
		mes "[ヒエール]";
		mes "なるほど。";
		mes "そういう事ですか。";
		mes "ただ……";
		next;
		mes "[ヒエール]";
		mes "難しいですね。";
		mes "ホームツリーを勝手に損傷する行為は、";
		mes "エクラージュでは不法行為です。";
		mes "即追放されます。";
		next;
		mes "[ヒエール]";
		mes "また、枯れたホームツリーの葉は";
		mes "地面に落ちないんです。";
		mes "ゆっくりと生命エネルギーに変わり";
		mes "そのまま樹に吸収されます。";
		mes "落ち葉として拾う事も不可能なんです。";
		next;
		mes "[ヒエール]";
		mes "うーん……何か方法がないかな。";
		next;
		mes "[ヒエール]";
		mes "うーむ……ん……？";
		next;
		mes "[ヒエール]";
		mes "万が一……";
		mes "万が一ですよ。";
		next;
		mes "[ヒエール]";
		mes "ホームツリーの創造主が";
		mes "ホームツリーの葉を";
		mes "渡してくれるとしたら";
		mes "それは不法行為ではないと思います。";
		next;
		menu "ロベル？",-;
		mes "[ヒエール]";
		mes "そうです。";
		mes "そうだよ。それが一番いい！";
		mes "ロベル様が渡してくれれば、";
		mes "受け取ることができます。";
		next;
		mes "[ヒエール]";
		mes "急いでロベル様と交信してみましょう。";
		next;
		mes "[ヒエール]";
		mes "そうと決まれば早速、";
		mes "交信を始めましょうか。";
		mes "通信機に手を置いて下さい。";
		set ECL_6QUE,33;
		delquest 12298;
		setquest 12299;
		close;
	case 33:
		mes "[ヒエール]";
		mes "次元通信機に集中して下さい。";
		close;
	case 34:
		mes "[ヒエール]";
		mes "ロベル様……";
		mes "本当に自分にそっくりだな。";
		next;
		menu "（性格はまるで似ていないが……）",-;
		mes "[ヒエール]";
		mes "まだ二度しか会っていないけど、";
		mes "とても親近感が湧きます。";
		mes "この感じ、何と説明すればいいのか。";
		next;
		mes "[ヒエール]";
		mes "あっと。";
		mes "通信機から目を離さないで下さい。";
		mes "交信が繋がっている状態です。";
		set ECL_6QUE,35;
		delquest 72574;
		setquest 72576;
		close;
	case 35:
		mes "[ヒエール]";
		mes "まだ交信が繋がっている状態です。";
		mes "通信機を確認してみてください。";
		close;
	case 36:
		mes "[ヒエール]";
		mes "通信は終わりましたか。";
		mes "どうでしたか。";
		next;
		mes "[ヒエール]";
		mes "おお……これが……。";
		mes "最初に作られた";
		mes "ホームツリーの葉ですか。";
		mes "う～ん、輝きがすごい。";
		next;
		mes "[ヒエール]";
		mes "これをエスラン様に届けるんですね。";
		mes "私も欲しいところですが……";
		mes "我慢我慢。";
		mes "さあ、早く届けてきてください。";
		close;
	case 37:
		mes "[ヒエール]";
		mes "おー、お帰りなさい。";
		mes "こちらの改良もほぼ出来ましたよ。";
		next;
		mes "[ヒエール]";
		mes "通信機の範囲が";
		mes "このエクラージュを超えて";
		mes "ビフロスト全地域まで";
		mes "動作できるようになりました。";
		next;
		mes "[ヒエール]";
		mes "もう少し手を加えれば";
		mes "年代記まで自由自在に";
		mes "選択可能になりそうです。";
		next;
		menu "エスランの言葉を伝える",-;
		mes "[ヒエール]";
		mes "おお、本当ですか？　それは良かった。";
		mes "いつか……私もエスラン様とロベル様が";
		mes "この通信機を通じて";
		mes "もう一度再会できるように";
		mes "力になる事が出来れば……。";
		next;
		cutin "EP14_robert1",1;
		mes "^000099‐一瞬、ヒエールの笑顔から";
		mes "　ロベルの姿が重なって見えた‐^000000";
		next;
		cutin "EP14_robert1",255;
		mes "[ヒエール]";
		mes "そうだ。最後にクレヴァーにも";
		mes "成り行きを報告してあげたら";
		mes "どうですか？";
		mes "聞きたがると思いますよ。";
		set ECL_6QUE,38;
		delquest 12301;
		setquest 72578;
		close;
	case 38:
		mes "[ヒエール]";
		mes "クレヴァーにも";
		mes "成り行きを報告してあげたら";
		mes "どうですか？";
		mes "聞きたがると思いますよ。";
		close;
	case 39:
		mes "[ヒエール]";
		mes "そうですか、クレヴァーは";
		mes "あんなところでも執筆を始めましたか。";
		mes "あいつらしいですね。";
		next;
		mes "[ヒエール]";
		mes "出所してからもいろいろと";
		mes "問題を起こしてくれそうです。";
		next;
		mes "‐ヒエールはやれやれといった感じで";
		mes "　苦笑した‐";
		next;
		mes "[ヒエール]";
		mes "ところで次元通信機ですが、";
		mes "さらに改良してみました。";
		mes "チャンネルを色々いじってみたので";
		mes "何が出るかは私も知りませんが、";
		mes "良かったら使ってみてください。";
		next;
		mes "‐ヒエールは次元通信機を";
		mes "　さらに改良したらしい。";
		mes "　次元通信機を調べてみよう‐";
		set ECL_6QUE,40;
		delquest 72580;
		setquest 72582;
		close;
	case 40:
		mes "[ヒエール]";
		mes "そうですか、クレヴァーは";
		mes "あんなところでも執筆を始めましたか。";
		mes "あいつらしいですね。";
		next;
		mes "[ヒエール]";
		mes "出所してからもいろいろと";
		mes "問題を起こしてくれそうです。";
		next;
		mes "‐ヒエールはやれやれといった感じで";
		mes "　苦笑した‐";
		next;
		mes "[ヒエール]";
		mes "ところで次元通信機ですが、";
		mes "さらに改良してみました。";
		mes "チャンネルを色々いじってみたので";
		mes "何が出るかは私も知りませんが、";
		mes "良かったら使ってみてください。";
		next;
		mes "‐ヒエールは次元通信機を";
		mes "　さらに改良したらしい。";
		mes "　次元通信機を調べてみよう‐";
		close;
	case 41:
		mes "[ヒエール]";
		mes "あれから色々とやる事が多くて、";
		mes "今日も相変わらず忙しいです。";
		next;
		if(select("雑談をする","エスランの首飾りについて聞く") == 1) {
			mes "[ヒエール]";
			mes "次元通信機ですか？";
			mes "今の所、一通りの改良は終わりました。";
			mes strcharinfo(0)+ "様には";
			mes "色々とお世話になりましたから";
			mes "好きなだけ使用できるように";
			mes "してありますよ。";
			next;
			mes "[ヒエール]";
			mes "いつでも好きな時に来て";
			mes "使ってみて下さい。";
			mes "チャンネルを色々いじってみたので";
			mes "何が出るかは私も知りません。";
			close;
		}
		mes "[ヒエール]";
		mes "エスラン様の首飾りですか？";
		mes "特殊な魔力石で効果を";
		mes "付与する事ができます。";
		mes "ただし魔力石の作成費用として";
		mes "スプレンディッドコインが10個";
		mes "必要です。";
		next;
		mes "^ff0000‐エスランの首飾りを複数所持している";
		mes "　場合、どの首飾りに効果を付与するか";
		mes "　選ぶことはできませんので、";
		mes "　ご注意ください。";
		mes "　効果を付与したい首飾りのみを";
		mes "　所持した状態で話しかけてください‐^000000";
		while(1) {
			next;
			switch(select("今回はやめておく","効果内容を聞く","効果を付与して貰う")) {
			case 1:
				mes "[ヒエール]";
				mes "はい、今度コインが用意できたら";
				mes "また訪ねて来て下さい。";
				close;
			case 2:
				mes "[ヒエール]";
				mes "付与される効果は4種類の中から";
				mes "自由に選択する事が出来ます。";
				mes "必ず成功するので安心してください。";
				mes "既につけた能力を変更したい場合は";
				mes "上書きする形で変更が可能です。";
				mes "効果の詳細を聞きますか？";
				while(1) {
					next;
					switch(select("物理能力付与について","魔法能力付与について","遠距離能力付与について","回復能力付与について","やめる")) {
					case 1:
						mes "[ヒエール]";
						mes "物理能力を付与すると、";
						mes "以下の能力がつきます。";
						next;
						mes "[先鋭1]";
						mes "Cri + 6";
						mes "Hit + 2";
						next;
						mes "[Atk2]";
						mes "物理攻撃で";
						mes "与えるダメージ + 2%";
						next;
						mes "[ヒエール]";
						mes "他も聞きますか？";
						continue;
					case 2:
						mes "[ヒエール]";
						mes "魔法能力を付与すると、";
						mes "以下の能力がつきます。";
						next;
						mes "[魔力3]";
						mes "Matk + 12";
						mes "詠唱時間 - 8%";
						next;
						mes "[Matk1]";
						mes "Matk + 1%";
						mes "固定詠唱時間 - 1%";
						next;
						mes "[ヒエール]";
						mes "他も聞きますか？";
						continue;
					case 3:
						mes "[ヒエール]";
						mes "遠距離能力を付与すると、";
						mes "以下の能力がつきます。";
						next;
						mes "[先鋭1]";
						mes "Cri + 6";
						mes "Hit + 2";
						next;
						mes "[名弓1]";
						mes "遠距離物理攻撃で";
						mes "与えるダメージ + 2%";
						next;
						mes "[ヒエール]";
						mes "他も聞きますか？";
						continue;
					case 4:
						mes "[ヒエール]";
						mes "回復能力を付与すると、";
						mes "以下の能力がつきます。";
						next;
						mes "[ダブル大司教1]";
						mes "[ヒール]";
						mes "[サンクチュアリ]";
						mes "[ポーションピッチャー]";
						mes "[ハイネスヒール]";
						mes "[コルセオヒール]";
						mes "使用時、HP回復量 + 6%";
						next;
						mes "[ヒエール]";
						mes "他も聞きますか？";
						continue;
					case 5:
						break;
					}
					break;
				}
				mes "[ヒエール]";
				mes "わかりました。";
				mes "他に何かありますか？";
				continue;
			case 3:
				break;
			}
			break;
		}
		mes "[ヒエール]";
		mes "わかりました。";
		mes "専門分野ではないので";
		mes "少し緊張しますね……。";
		mes "どの能力を付与しますか？";
		next;
		switch(select("物理能力付与","魔法能力付与","遠距離能力付与","回復能力付与","やっぱりやめる")) {
		case 1:
			set '@slot[3],4818;
			set '@slot[4],4766;
			break;
		case 2:
			set '@slot[3],4813;
			set '@slot[4],4760;
			break;
		case 3:
			set '@slot[3],4818;
			set '@slot[4],4832;
			break;
		case 4:
			set '@slot[3],4805;
			set '@slot[4],4805;
			break;
		case 5:
			mes "[ヒエール]";
			mes "わかりました。";
			mes "効果を付与したくなったら";
			mes "また来てください。";
			close;
		}
		if(countitem(6081) < 10) {
			mes "[ヒエール]";
			mes "スプレンディッドコインが";
			mes "不足しているようです。";
			mes "1回で10枚、必要です。";
			mes "用意出来たらまた来てください。";
			close;
		}
		delitem 2915,1;
		delitem 6081,10;
		getitem2 2915,1,1,0,0,0,0,'@slot[3],'@slot[4];
		mes "[ヒエール]";
		mes "ふう。";
		mes "うまく効果が付与されました。";
		close;
	default:
		mes "[ヒエール]";
		mes "木の葉一枚の長さがX、";
		mes "平均値がM、中央値がN";
		mes "で……と、";
		mes "分散がLである正規分布Pの……";
		mes "ふむふむ、なるほど。";
		mes "ということは……";
		next;
		mes "^0000ff‐難しそうな計算をしている‐^000000";
		close;
	}
}

mid_camp.gat,173,257,5	script	シエルビー	545,{
	switch(ECL_6QUE) {
	case 10:
		mes "[シエルビー]";
		mes "ふん。";
		mes "猫の手サービスを受けたいのなら、";
		mes "私ではなく、猫の手職員を";
		mes "訪ねた方がいいよ。";
		next;
		menu "ご機嫌斜めですね",-;
		mes "[シエルビー]";
		mes "なんだ？";
		mes "元気な猫や親切な猫を見てきたせいで";
		mes "私が変に見えるか？";
		next;
		mes "[シエルビー]";
		mes "にゃ～、どうしたにゃん～？";
		mes "私、本当に猫缶詰大好きだにゃん～！";
		mes "……";
		mes "こんな反応を望んでいたか？";
		next;
		mes "[シエルビー]";
		mes "猫が誰でもそんな";
		mes "単純な奴ばかりだと思わんで欲しいな。";
		mes "それに私は今とても機嫌が悪いんだ。";
		mes "何か用があるなら、";
		mes "他の猫を探して見たらどうだね。";
		next;
		menu "次元の狭間について聞いてみる",-;
		mes "[シエルビー]";
		mes "はは、猫にそんなことを聞くか。";
		mes "私たちにとって、科学という分野は";
		mes "まるで重要ではないんだよ。";
		mes "興味も無い。";
		mes "大事なのは商業と漁業の2つだけだ。";
		mes "ただ……";
		next;
		mes "[シエルビー]";
		mes "商売として扱えるネタなんかは";
		mes "勉強したり仕入れたりもする。";
		mes "次元の狭間？";
		mes "確かに情報が無いわけではない。";
		mes "だけど今は機嫌が悪いんだ。";
		mes "そこにいるそのポードのせいでね！";
		next;
		mes "[シエルビー]";
		mes "まったく、あいつは食べる事しか";
		mes "頭に無いのか……。";
		mes "ちょっと報酬が遅れた程度で";
		mes "ぶつぶつぶつぶつ、いつまでも……";
		mes "あーうるさい奴め！";
		mes "私だって貰ってないんだよ、まだ！";
		next;
		mes "[シエルビー]";
		mes "というわけでね。";
		mes "残念だけど、";
		mes "他の奴でも探してみたらどうだ？";
		set ECL_6QUE,11;
		delquest 12284;
		setquest 72558;
		close;
	case 11:
		mes "[シエルビー]";
		mes "残念だけど、";
		mes "他の奴でも探してみたらどうだ？";
		close;
	case 12:
		if(countitem(12636) < 10 && countitem(6049) < 2 && countitem(6039) < 10) {
			mes "^000099‐シエルビーは争いに夢中です。";
			mes "　なんとかして止めないと……‐^000000";
			next;
			mes "^000099‐マラン島特産缶詰10個か";
			mes "　まかじき2個か";
			mes "　魚のはしくれ10個の";
			mes "　どれかを渡せば";
			mes "　落ち着きそうだ‐^000000";
			close;
		}
		mes "^000099‐争いに夢中なシエルビーに";
		mes "　用意した食料を見せた‐^000000";
		next;
		mes "[シエルビー]";
		mes "あ？　それは……？";
		mes "君の手にあるその食べ物は";
		mes "どうしたんだ？";
		next;
		if(select("自分で食べる分です","あなた達に渡すために持ってきました") == 1) {
			mes "[シエルビー]";
			mes "はぁ？　人間なのに？";
			mes "猫用の食料を？";
			mes "それをわざわざ言いに来たのか。";
			mes "まったく人間ってのは……";
			next;
			mes "[ポード]";
			mes "シエルビーがよそみしてる！";
			mes "ポードはチャンス逃さない！";
			mes "　";
			mes "ボッカーン";
			next;
			mes "[シエルビー]";
			mes "いてててっ！";
			mes "…………";
			mes "こんのバカ猫め！";
			mes "もう許さん！　もう許さんぞ!!!";
			next;
			mes "^000099‐争いはますます激しくなった‐^000000";
			close;
		}
		mes "[シエルビー]";
		mes "ふん。";
		mes "本当か……？";
		mes "本当にもらっていいのか？";
		next;
		if(select("嫌なら持って帰ります","どうぞあげますよ") == 1) {
			mes "[シエルビー]";
			mes "いやいや。待ってくれ！";
			mes "欲しい！　確かに欲しい！";
			next;
		}
		mes "[シエルビー]";
		mes "では、ありがたく。";
		mes "ふん。そうすると対価が必要だな。";
		mes "何が欲しいんだ？";
		mes "やはり、以前話していた";
		mes "次元の狭間に関する内容か？";
		next;
		menu "はい、聞かせてください",-;
		mes "[シエルビー]";
		mes "ふん。やはり、その件か。";
		mes "以前、エクラージュでこの件を";
		mes "研究してる者がいるという情報を";
		mes "聞きつけて苦労して入手したんだ。";
		mes "その時は徒労に終わったが……";
		mes "こんな形で役に立つとはな。";
		next;
		mes "[シエルビー]";
		mes "ミッドガルドの学者たちも";
		mes "表に情報を公開していなくてね。";
		mes "まぁ我々の情報網を駆使すれば";
		mes "どうとでもなるんだけどな。";
		next;
		mes "[シエルビー]";
		mes "では教えよう。";
		next;
		mes "[シエルビー]";
		mes "次元の狭間の鉱石を活性化させるには";
		mes "触媒になる^000099闇の破片^000000が1個";
		mes "必要となる。";
		next;
		mes "[シエルビー]";
		mes "狭間はモロクの体に";
		mes "反応するようでね。";
		mes "触媒も類似する物が必要らしい。";
		next;
		mes "[シエルビー]";
		mes "闇の結晶体があれば、";
		mes "より強力な効果を発揮するらしいが、";
		mes "残念ながらその調合方法は";
		mes "入手できなかった。";
		next;
		mes "[シエルビー]";
		mes "さらに闇の破片に加えて";
		mes "ブルー、イエロー、レッド、";
		mes "各ジェムストーンが2個ずつ必要だ。";
		next;
		menu "ジェムストーン？",-;
		mes "[シエルビー]";
		mes "闇の破片が触媒になって";
		mes "狭間の鉱石と反応する時、";
		mes "周辺にはとても大きなひずみが出来る。";
		mes "次元の扉が開く力の反作用のようだ。";
		mes "その時、反作用を相殺する力が無いと";
		mes "どうなる？";
		next;
		mes "[シエルビー]";
		mes "君も見た事があるんじゃないか。";
		mes "モロクで発生した次元の狭間のように";
		mes "その周辺は崩れてしまう。";
		mes "それを防ぐ為に必要なものが";
		mes "ジェムストーン、という事らしい。";
		next;
		mes "[シエルビー]";
		mes "これで説明は概ね終わりだ。";
		mes "必要な物をもう一度言うと";
		mes "^000099闇の破片^000000が1個";
		mes "^000099各ジェムストーン^000000が2個ずつ";
		mes "以上だ。";
		next;
		mes "[シエルビー]";
		mes "しかし、狭間の鉱石のような物を";
		mes "活性化してどうするんだ？";
		mes "何か恐ろしい事でも企んでいるのか。";
		mes "ふん。まぁ猫には関係ない事だ。";
		next;
		switch(select(
			((countitem(12636) >= 10)? "礼を言い、缶詰を渡す": ""),
			((countitem(6049)  >=  2)? "礼を言い、まかじきを渡す": ""),
			((countitem(6039)  >= 10)? "礼を言い、魚のはしくれを渡す": "")
		)) {
		case 1:
			set '@itemid,12636;
			set '@num,10;
			break;
		case 2:
			set '@itemid,6049;
			set '@num,2;
			break;
		case 3:
			set '@itemid,6039;
			set '@num,10;
			break;
		}
		mes "[シエルビー]";
		mes "ありがたい。ふん。";
		mes "これで食事の心配はなくなった。";
		mes "君が進む道に猫の神から";
		mes "祝福があることを祈ってやる。";
		delitem '@itemid,'@num;
		set ECL_6QUE,13;
		delquest 12285;
		setquest 12286;
		getexp 120000,0;
		getexp 0,80000;
		next;
		mes "‐シエルビーから情報を入手した。";
		mes "　ヒエールのところへ戻ろう‐";
		close;
	derfault:
		if(ECL_6QUE < 13) {
			mes "[シエルビー]";
			mes "ふん。";
			mes "猫の手サービスを受けたいのなら、";
			mes "私ではなく、猫の手職員を";
			mes "訪ねた方がいいよ。";
			close;
		}
		mes "[シエルビー]";
		mes "活性化に必要な材料は";
		mes "^000099闇の破片^000000が1個";
		mes "^000099各ジェムストーン^000000が2個ずつ";
		mes "だからな。忘れるなよ。";
		close;
	}
}

mid_camp.gat,179,258,4	script	ポード	544,{
	switch(ECL_6QUE) {
	case 11:
		mes "[ポード]";
		mes "給料として支給されるはずの";
		mes "^000099マラン島特産缶詰^000000を";
		mes "まだもらっていない！";
		mes "ポード、悲しい。お腹すいた……。";
		mes "あっちにいる^000099シエルビー^000000も";
		mes "不機嫌だし……。";
		next;
		mes "[ポード]";
		mes "先月も少し足りなかった！";
		mes "だから、今回は";
		mes "^000099マラン島特産缶詰^000000を10個";
		mes "貰えるって言っていたのに……！";
		mes "全然来ない。お腹すいた。";
		mes "悲しい。";
		next;
		mes "[シエルビー]";
		mes "いい加減にしろ、ポード！";
		mes "ここに物資が来るまでは";
		mes "時間がかかると何度も言ってるだろう！";
		next;
		menu "あの、次元の狭間について……",-;
		mes "[ポード]";
		mes "え？　なに??";
		mes "ポードは難しいことは知らない。";
		mes "ポード、イワシの事はよく知っている！";
		mes "サバもよく知っている！";
		mes "次元……何とかは";
		mes "シエルビーがよく知っている！";
		next;
		mes "[ポード]";
		mes "だけど……";
		mes "シエルビーが不機嫌だし、";
		mes "^000099マラン島特産缶詰^000000ももらえないし、";
		mes "お腹も減ったし……！";
		mes "もう知らない！";
		mes "仕事しない！　仕事しない！";
		next;
		mes "[シエルビー]";
		mes "おい、ポード！";
		mes "いい加減にしろと言ってるだろ！";
		mes "このやろう！";
		next;
		mes "^000099‐2匹の猫が壮絶な争いを始めた。";
		mes "　このままでは話を聞けそうにない。";
		mes "　給料のマラン島特産缶詰の事で";
		mes "　もめているようだ‐^000000";
		set ECL_6QUE,12;
		delquest 72558;
		setquest 12285;
		close;
	case 12:
		mes "^000099‐ポードは争いに夢中です。";
		mes "　なんとかして止めないと……‐^000000";
		close;
	derfault:
		if(ECL_6QUE < 13) {
			mes "[ポード]";
			mes "支給されるはずの";
			mes "^000099マラン島特産缶詰^000000を";
			mes "まだもらっていない！";
			mes "ポード、悲しい。お腹すいた……。";
			mes "あっちにいる^000099シエルビー^000000も";
			mes "不機嫌だし……。";
			close;
		}
		mes "[ポード]";
		mes "私たちにプレゼントくれた！";
		mes "ありがとう！　いい人！";
		mes "シエルビーも喜んでいる！";
		mes "これで食べ物に困らなくなった！";
		close;
	}
}

ecl_in02.gat,133,115,7	script	看守#pa0829	461,3,3,{
	switch(ECL_6QUE) {
	case 0:
		mes "[看守]";
		mes "こんにちは。";
		mes "おや、この時間は面会帳に";
		mes "特に予定は無いようですね。";
		mes "誰かとの面会をご希望ですか？";
		next;
		if(select("中を見て回りたい","外に出して下さい") == 1) {
			mes "[看守]";
			mes "わかりました。";
			mes "お帰りの際はお声掛けください。";
			close;
		}
		mes "[看守]";
		mes "わかりました。";
		mes "気を付けてお帰りください。";
		close2;
		warp "ecl_in02.gat",98,29;
		end;
	case 1:
		mes "[看守]";
		mes "こんにちは。";
		mes "おや、この時間は面会帳に";
		mes "特に予定は無いようですね。";
		mes "誰かとの面会をご希望ですか？";
		next;
		if(select("クレヴァー","外に出して下さい") == 2) {
			mes "[看守]";
			mes "わかりました。";
			mes "気を付けてお帰りください。";
			close2;
			warp "ecl_in02.gat",98,29;
			end;
		}
		mes "[看守]";
		mes "クレヴァー様ですか!?";
		mes "それは……";
		next;
		mes "[クレヴァー]";
		mes "あ？　何だ？　私に面会か？";
		mes "やった～！　面会だ！　面会！　面会！";
		mes "嬉しい～。";
		next;
		mes "[看守]";
		mes "ああ……。";
		next;
		mes "^000099‐看守の顔色が変わっていく。";
		mes "　クレヴァーという囚人に";
		mes "　よほど嫌な目にあっているようだ‐^000000";
		next;
		mes "[看守]";
		mes "うーん……。";
		mes "面会予定名簿に、";
		mes "予定は入っていないのですが……。";
		next;
		mes "[クレヴァー]";
		mes "お～い。看守～！　何をしているんだ？";
		mes "早く扉を開けろよ！　面会なんだよ！";
		mes "私の面会を邪魔すると";
		mes "お前の勤務時間に歌を歌うぞ！";
		mes "いいのか？　ん？　ん？";
		next;
		mes "[クレヴァー]";
		mes "そうだ、どうせなら";
		mes "今すぐ歌うのも悪くないな。";
		mes "あー！　んっ！　あ゛あ゛～～！";
		mes "ようし。歌っちゃおうかな～。";
		next;
		mes "^000099‐看守の顔色がさらに悪くなる。";
		mes "　看守は何かを決心したような顔つきで";
		mes "　こちらに向きなおった‐^000000";
		next;
		mes "[看守]";
		mes "うん。名簿にはないけれど、";
		mes "これは何かの間違いでしょう。";
		mes "きっと手違いで名簿に記載が";
		mes "無いだけだと思いますので";
		mes "面会を許可します。";
		mes "時間は、そうですね……。";
		next;
		mes "[看守]";
		mes "お好きなだけ使って構いません。";
		mes "では、どうぞごゆっくり。";
		set ECL_6QUE,2;
		setquest 72550;
		delquest 12280;
		close;
	case 3:
		mes "[看守]";
		mes "お願いします。";
		mes "あのクレヴァー様のうるさい口を";
		mes "何とかして下さい……！";
		mes "この１年間ずっとこんな調子で、";
		mes "頭がおかしくなりそうです。";
		next;
		if(select("中を見て回りたい","外に出して下さい") == 1) {
			mes "[看守]";
			mes "わかりました。";
			mes "お帰りの際はお声掛けください。";
			close;
		}
		mes "[看守]";
		mes "わかりました。";
		mes "気を付けてお帰りください。";
		close2;
		warp "ecl_in02.gat",98,29;
		end;
	case 6:
		mes "[看守]";
		mes "なんてことだ！　あなたのおかげです！";
		mes "クレヴァー様が寝るという事は";
		mes "これから数日のあいだ";
		mes "平和な時間が訪れるという事です！";
		mes "一度眠るとしばらく起きないんです。";
		next;
		mes "[看守]";
		mes "このような時間を";
		mes "再び持てるようになるとは！";
		mes "どうかあなたに";
		mes "ホームツリーの祝福が";
		mes "ありますように。";
		set ECL_6QUE,7;
		delquest 12283;
		setquest 72554;
		getexp 100000,0;
		getexp 0,60000;
		next;
		mes "‐看守に感謝された。";
		mes "　次はヒエールに会いに行こう。";
		mes "　クレヴァーによると";
		mes "　ヒエールの家は";
		mes "　街の南の方にあるようだ‐";
		close;
	case 23:
		mes "[看守]";
		mes "あっ" +strcharinfo(0)+ "様！";
		mes "もうお帰りですか？";
		mes "うわあ～やっと静かになったのに！";
		next;
		menu "そろそろ時間なのかなと",-;
		mes "[看守]";
		mes "何をおっしゃるんですか？";
		mes "あんなものは飾りですよ。";
		mes "いいですか？　ここに帳簿があります。";
		mes "1の右にまるを書いてこうして、と。";
		mes "はい。6時間延長しました！";
		next;
		mes "^000099‐手際よく改ざんしている。";
		mes "　本当に看守なんだろうか……。";
		mes "　ただ、クレヴァーの事は平気そうだ。";
		mes "　クレヴァーの元に戻ろう‐^000000";
		set ECL_6QUE,24;
		delquest 72566;
		setquest 72568;
		close;
	default:
		mes "[看守]";
		mes "他にも用件があります？";
		next;
		if(select("中を見て回りたい","外に出して下さい") == 1) {
			mes "[看守]";
			mes "わかりました。";
			mes "お帰りの際はお声掛けください。";
			close;
		}
		mes "[看守]";
		mes "わかりました。";
		mes "気を付けてお帰りください。";
		close2;
		warp "ecl_in02.gat",98,29;
		end;
	}
OnTouch:
	if(ECL_6QUE == 0) {
		mes "[クレヴァー]";
		mes "おーい、看守～。おーい。";
		mes "ちょっと乾燥しすぎてるよ。";
		mes "肌がカサカサになっちゃうよ～。";
		mes "あ～あ！";
		mes "困っちゃうな～。あーあ！";
		mes "おい、看守～？聞いているのか？";
		next;
		mes "[看守]";
		mes "……";
		next;
		mes "^000099‐看守は疲れきった面持ちで";
		mes "　監獄の中にいる囚人を見つめている‐^000000";
		next;
		mes "[看守]";
		mes "クレヴァー様、一言だけいいます。";
		mes "今のあなたはここでは囚人の身です。";
		mes "反省の時間を持つよう";
		mes "命令されている状態です。";
		next;
		mes "[クレヴァー]";
		mes "うん、そうそう。それは分かった。";
		mes "だから急いでここの湿度を";
		mes "何とかしてくれないか。";
		mes "乾燥しすぎてカサカサするんだよ。";
		next;
		mes "[看守]";
		mes "まだ、私の言葉の意味を";
		mes "理解していませんか？";
		mes "そういった事に気を使っていちいち";
		mes "配慮してあげるわけには";
		mes "いかないんですよ。";
		next;
		mes "[クレヴァー]";
		mes "ちぇっ";
		mes "けちだな……。";
		next;
		mes "[看守]";
		mes "まったく。";
		mes "はぁ……。";
		next;
		mes "^000099‐看守は何か言いかけたが、";
		mes "　そのまま席に戻った。";
		mes "　あの人は何故、";
		mes "　捕まっているのだろうか。";
		mes "　看守に話しかけてみよう‐^000000";
		set ECL_6QUE,1;
		setquest 12280;
		close;
	} else if(ECL_6QUE == 18) {
		mes "[看守]";
		mes "あ！　あなたはあの時の！";
		mes "よく来てくれました！";
		mes "また助けてくれませんか……。";
		mes "私にはとても手が負えません。";
		next;
		mes "[クレヴァー]";
		mes "そこの君、よそ見するな～";
		mes "他の囚人は見るな～";
		mes "私、私だけを見ていろ～";
		mes "私がそばに居るうちに～るる～";
		next;
		mes "^000099‐クレヴァーがまた大声で歌っている";
		mes "　看守が切実なまなざしで、";
		mes "　訴えかけてくる‐^000000";
		next;
		menu "面会の事前申請をしていないのですが……",-;
		mes "[看守]";
		mes "面会の事前申請記録ですか？";
		mes "いいえ、そんなものは必要ありません。";
		mes "クレヴァー様の面会ですね。";
		mes "ほら、ここにちょちょいと……。";
		mes "見て下さい。名簿にありました。";
		mes "どうぞお入りください。";
		next;
		mes "^000099‐目の前で名簿に名前を書いてくれた‐^000000";
		close;
	} else if(ECL_6QUE == 22) {
		mes "[看守]";
		mes "あっ、こんにちは。";
		mes "いつもありがとうございます。";
		mes "しかしすごいですね。";
		mes strcharinfo(0)+ "様がどんな手を";
		mes "使ったのか想像がつきませんが、";
		mes "クレヴァー様が静かになりました。";
		next;
		menu "面会をしたいのですが予約が……",-;
		mes "[看守]";
		mes "何をおっしゃるんですか!!";
		mes strcharinfo(0)+ "様の面談でしたら";
		mes "いつでも歓迎です。";
		mes "特にクレヴァー様の面談なら";
		mes "私がいくらでも名簿を改ざんします！";
		next;
		mes "^000099‐看守に面会の許可を貰った‐^000000";
		close;
	} else if(ECL_6QUE == 23) {
		mes "[看守]";
		mes "あっ" +strcharinfo(0)+ "様！";
		mes "もうお帰りですか？";
		mes "うわあ～やっと静かになったのに！";
		next;
		menu "そろそろ時間なのかなと",-;
		mes "[看守]";
		mes "何をおっしゃるんですか？";
		mes "あんなものは飾りですよ。";
		mes "いいですか？　ここに帳簿があります。";
		mes "1の右にまるを書いてこうして、と。";
		mes "はい。6時間延長しました！";
		next;
		mes "^000099‐手際よく改ざんしている。";
		mes "　本当に看守なんだろうか……。";
		mes "　ただ、クレヴァーの事は平気そうだ。";
		mes "　クレヴァーの元に戻ろう‐^000000";
		set ECL_6QUE,24;
		delquest 72566;
		setquest 72568;
		close;
	} else if(ECL_6QUE == 38) {
		mes "[看守]";
		mes "ああ～～来ましたか!!";
		mes "待っていました！";
		next;
		menu "こんにちは",-;
		mes "[看守]";
		mes "実はクレヴァー様が、変な呪文を";
		mes "唱えながらぶつぶつ言っているんです。";
		mes "完全に嫌がらせです。お願いします！";
		mes "なんとか助けてください。";
		next;
		mes "[看守]";
		mes "まずはいらっしゃったので";
		mes "面会名簿に予約を記録しておきますね。";
		next;
		mes "^000099‐看守はまた何事もなかったように";
		mes "　予約名簿を改ざんしてくれた。";
		mes "　もはや予約制の必要を感じない……‐^000000";
		close;
	}
	end;
OnInit:
	waitingroom "悠久なる絆",0;
	end;
}

ecl_in01.gat,82,80,4	script	月刊エクラージュ	111,{
	if(ECL_6QUE >= 20) {
		mes "^990000―――月刊エクラージュ―――^000000";
		mes "^999900衝撃！　エクラージュ誕生秘話特集^000000";
		next;
		mes "^000099‐クレヴァーが知らせてくれた本だ。";
		mes "　歴史書には見えないが……";
		mes "　本の目次を読んでみる‐^000000";
		next;
		switch(select("本を閉じる","絶望の大地――――7P","元老会の陰謀――――48P","永遠の別れ――――132P","（古くなって見えない部分）")) {
		case 1:
			mes "^000099‐本を閉じた‐^000000";
			close;
		case 2:
			mes "^000099第1節。絶望の大地^000000";
			mes "　";
			mes "イグドラシルに異常があるのだろうか。";
			mes "平和に過ごしていたこの地に";
			mes "死の気配が現れ始めた。";
			next;
			mes "汚染された水源、枯れた大地、";
			mes "突然変異した生物たちの攻撃。";
			mes "ラフィネたちの生活は";
			mes "日に日に変化を余儀なくされた。";
			next;
			mes "^000099‐一部黒く塗られていて読めない‐^000000";
			next;
			mes "パパンの長達は";
			mes "このエクラージュという場所が";
			mes "イグドラシルを守護するために";
			mes "最適であることは疑問視していない。";
			mes "その考えは今でも変化が無いようだ。";
			next;
			mes "しかし、度重なる元老会の圧力と";
			mes "日々広がる被害により、";
			mes "パパン、一般市民たちの";
			mes "統制が次第に難しくなってきている。";
			next;
			mes "具体的な対策も未だ決まらない。";
			mes "これといった成果がないまま、";
			mes "病気や変異生物からの攻撃を受け、";
			mes "仲間や家族が亡くなっていく。";
			mes "どうすれば。一体どうすれば……。";
			next;
			mes "^000099‐ここから先は汚れていて読めない‐^000000";
			close;
		case 3:
			mes "^000099第2節。元老会の陰謀^000000";
			mes "　";
			mes "元老会は長く続く被害の責任を";
			mes "パパンの長達のせいにしてきた。";
			mes "元々、居住する地域の選定が";
			mes "間違っていたという話だ。";
			next;
			mes "彼らはより南側の森の中に";
			mes "首都を移転する計画を";
			mes "元老会内部で決定のうえ";
			mes "パパンの長達に通告してきた。";
			next;
			mes "^000099‐破れたページは飛ばした‐^000000";
			next;
			mes "南の方に偵察に向かった";
			mes "調査隊の状況は深刻だった。";
			mes "巨大な迷宮のような森。";
			mes "安全な場所はどこにもない。";
			mes "殆どは迷宮の中で出会った何かに";
			mes "壊滅させられてしまった。";
			next;
			mes "それでも、元老会は強行し続けた。";
			mes "解決すべき最優先事項という理由を盾に";
			mes "さらなる調査隊の派遣を要求した。";
			mes "無謀としか言いようがないが、";
			mes "他に解決策を持たない一般市民達は";
			mes "この指示に従わざるを得なかった。";
			next;
			mes "パパンの長達としては";
			mes "元老会の無謀な要求を跳ね除ける";
			mes "根本的な打開策が必要だった。";
			mes "このまま元老会の方針に従っていては";
			mes "大地によって滅ぶのと大差が無い。";
			next;
			mes "そんな折、二人の若きドナが";
			mes "一つの案を元老会に提出した。";
			next;
			mes "^000099エスラン、ロベル^000000";
			mes "生命に関する研究者兼技術者で";
			mes "ラフィネの中でも最高の頭脳を持つ";
			mes "若きエースだ。";
			mes "彼らが大規模大地蘇生に関する";
			mes "報告書を提出したのである。";
			next;
			mes "若い二人のドナの提案は単純だった。";
			mes "^000099イグドラシルと直接共感する";
			mes "巨大なホームツリーを創造し、";
			mes "大地を蘇らせる^000000";
			mes "という内容だ。";
			next;
			mes "ホームツリーを創造する事により、";
			mes "自然が持つ治癒力を極度に活性化し";
			mes "安定した地に変えると同時に、";
			mes "イグドラシルの保護もおこなうという";
			mes "考えである。";
			next;
			mes "ただし、この提案には問題もあった。";
			mes "^000099ホームツリーが育つ為には";
			mes "大地の生命力を吸収する必要が";
			mes "あったからだ。^000000";
			mes "最初に充分な量の栄養を確保しないと";
			mes "力を発揮できないのである。";
			next;
			mes "元老会は彼ら二人の提案を黙殺した。";
			mes "ホームツリーの創造に";
			mes "大地の栄養を必要とするなら";
			mes "大地の再生とホームツリーの創造は";
			mes "同時に出来るわけが無い、";
			mes "というのが表向きの理由だ。";
			next;
			mes "こうして若き二人の報告は、";
			mes "ろくに議論されることなく、";
			mes "幕を閉じた。";
			mes "元老会は変わらず、";
			mes "南への移転を主張し続けた。";
			next;
			mes "最初から彼らの目標は";
			mes "南への移転にあったのだ。";
			mes "それは、";
			next;
			mes "^000099‐この先のページは破られている‐^000000";
			if(ECL_6QUE == 20) {
				set ECL_6QUE,21;
				chgquest 12291,72564;
			}
			close;
		case 4:
			mes "^000099‐すべてのページに";
			mes "　意図的に汚したインクの後がある‐^000000";
			close;
		case 5:
			mes "^000099‐すべてのページに";
			mes "　意図的に汚したインクの後がある‐^000000";
			if(ECL_6QUE == 20) {
				close;
			}
			next;
			menu "折れている部分が見える",-;
			mes "^000099‐うまく広げると";
			mes "　折ってあった部分の内容を";
			mes "　読む事ができそうだ‐^000000";
			next;
			menu "広げて読んでみる",-;
			mes "^000099‐本を読んだラフィネ達の";
			mes "　感想が書かれている‐^000000";
			next;
			mes "^990000RE:^000000";
			mes "誰がこんなことをしたんだ！";
			mes "この一冊が最後なのに汚れて読めない！";
			mes "―――――――――";
			mes "^990000RE-RE:^000000";
			mes "あの、複写版を持っているので、";
			mes "よかったら連絡残して下さい。";
			next;
			mes "^990000RE:^000000";
			mes "おい、お前らこれどういうことだ？";
			mes "ここには元老会はホームツリー創造に";
			mes "反対したと書かれている。";
			mes "しかし、正式の歴史書には元老会が";
			mes "ホームツリーを創造したと書いてある。";
			mes "どっちが正しいんだ？";
			next;
			mes "^990000RE:^000000";
			mes "羽の長さ180以上のラフィネと";
			mes "一度付き合って見たいです。";
			mes "―――――――――";
			mes "わたし、アナイス様が好きです。";
			mes "―――――――――";
			next;
			mes "^990000RE:^000000";
			mes "両親から聞いたんだけど、";
			mes "エスランとロベルの二人が";
			mes "元老会の移転案を止めようとして";
			mes "^000099仕組んで元老会の前で争ったらしいけど^000000";
			mes "それって本当なの？";
			next;
			mes "^990000RE-RE:^000000";
			mes "俺もその話聞いた。";
			mes "ばれないように二人で^990000何日も前から、";
			mes "いがみ合う振りをしていたらしいぞ^000000。";
			mes "まぁこの辺は歴史記録者の間で一番、";
			mes "解釈上の論争が多かったらしいが。";
			next;
			mes "^990000RE:^000000";
			mes "おいおい、";
			mes "こんなの信じている奴いるのか。";
			mes "この月刊エクラージュは";
			mes "ゴシップ専門誌だぞ。";
			mes "歴史書じゃぁないんだから。";
			mes "見極めろよその辺は。";
			next;
			mes "^990000RE-RE:^000000";
			mes "そうですか。";
			if(ECL_6QUE == 21) {
				next;
				set ECL_6QUE,22;
				chgquest 72564,12292;
				mes "^000099‐エスランとロベル、";
				mes "　二人のドナに関する話を読んだ。";
				mes "　クレヴァーの元に戻ろう‐^000000";
			}
			close;
		}
	}
	mes "^000099‐普通の雑誌にみえる。";
	mes "　ゴシップを主に載せているようだ‐^000000";
	close;
}

ecl_tdun01.gat,60,56,4	script	#pa0829エスラン室内	111,{
	if(ECL_6QUE == 29 || ECL_6QUE == 30 || ECL_6QUE == 36) {
		mes "‐何かの反応があった！‐";
		close2;
		warp "ecl_tdun01a.gat",60,51;
		end;
	}
	if(ECL_6QUE == 31) {
		mes "^000099‐特に新しい反応はない‐^000000";
		close;
	}
	if(ECL_6QUE == 37) {
		mes "^000099‐エスランと交信できた場所だ‐^000000";
		close;
	}
	mes "^000099‐タワーに似合わない墓地がある。";
	mes "　墓石が古くて誰の物かは判らない‐^000000";
	close;
}

ecl_tdun01.gat,60,56,0	script	#pa0829エスラン室内タッ	139,5,5,{
	if(ECL_6QUE == 29) {
		mes "‐何かの反応があった！‐";
		close2;
		warp "ecl_tdun01a.gat",60,51;
		end;
	}
	end;
}

ecl_tdun01a.gat,60,56,4	script	#pa0829エスラン室内copy	111,{
	if(ECL_6QUE == 30) {
		cutin "EP14_etran01",1;
		mes "[？？？？]";
		mes "ん？　これは何だ？";
		mes "夢でもみているのか？";
		next;
		menu "エスランですか？",-;
		cutin "EP14_etran3",1;
		mes "[エスラン]";
		mes "何故私の名前を？";
		mes "誰だ？";
		next;
		menu "事情を説明する",-;
		cutin "EP14_etran5",1;
		mes "[エスラン]";
		mes "なんだって？";
		mes "遥か先の未来から来た？";
		mes "何を言っているんだい君は？";
		next;
		menu "通信機の説明をする",-;
		cutin "EP14_etran5",255;
		mes "["+strcharinfo(0)+"]";
		mes "未来から来たのではなく、";
		mes "少しの間だけ過去と未来の交信が";
		mes "可能になった状態です。";
		mes "お聞きしたい事があります。";
		next;
		cutin "EP14_etran4",1;
		mes "^000099‐驚いた事に";
		mes "　エスランはクレヴァーとそっくりだ。";
		mes "　クレヴァーとヒエールは";
		mes "　エスランとロベルの";
		mes "　生まれ変わり……？‐^000000";
		next;
		while(1) {
			switch(select("元老会について","ロベルとの言い争いについて","大地復活作業の進捗について")) {
			case 1:
				cutin "EP14_etran8",1;
				mes "[エスラン]";
				mes "元老会か……本当に腐った組織だ。";
				mes "化石のような存在だよ。";
				next;
				mes "[エスラン]";
				mes "軍の統率、政治、文化にまで";
				mes "すべて、干渉しようとしている。";
				mes "さらには私たちの生死に関わる";
				mes "首都再建にも首を突っ込んでいる。";
				next;
				mes "[エスラン]";
				mes "この地域で首都を復興しようとする";
				mes "若いラフィネたちの合理的な選択を";
				mes "彼らは無視しようとしている。";
				mes "首都再建は自分たち中心で進まないと";
				mes "気が済まないらしい。";
				next;
				mes "[エスラン]";
				mes "それで無理をしてでも";
				mes "南側の森の方を駐屯地にするという";
				mes "ふざけた計画を進めていやがる。";
				next;
				cutin "EP14_etran4",1;
				mes "[エスラン]";
				mes "若いラフィネたちは";
				mes "絶対にそれを許す事ができない。";
				mes "それで私とロベルは";
				mes "ここを再建する事が可能と伝え、";
				mes "南の方に移転するのをとどめている。";
				mes "しかし……";
				next;
				mes "[エスラン]";
				mes "いや、方法は勿論考えてあるんだ。";
				mes "ただ、成功した場合の話だ。";
				mes "私たちが失敗すると、";
				mes "さらに多くのラフィネ達が";
				mes "南側に向かわされるだろう。";
				next;
				mes "[エスラン]";
				mes "これ以上、元老会の手によって";
				mes "若いラフィネ達の";
				mes "犠牲を増やす事はできない。";
				next;
				cutin "EP14_etran4",255;
				continue;
			case 2:
				cutin "EP14_etran5",1;
				mes "[エスラン]";
				mes "ああ、私たち二人が";
				mes "元老会の前で争っていた事か。";
				mes "しかし……よく知っているな。";
				mes "私のいる世界から遥か先の";
				mes "未来なんだろうここは？";
				next;
				mes "[エスラン]";
				mes "あの時、私たちは元老会の介入を";
				mes "どうやって防ぐか考えていた。";
				mes "奴らは南の森への移転を";
				mes "必ず持ち出してくるだろうからな。";
				mes "そこで我々はわざと対立したんだ。";
				next;
				mes "[エスラン]";
				mes "ホームツリーの創造を優先するか。";
				mes "大地の復活を優先するか。";
				mes "この案に話が集中すれば、";
				mes "どちらが選択されたとしても";
				mes "よかったんだ。";
				next;
				mes "[エスラン]";
				mes "話を出した段階で既に";
				mes "私とロベルで並行して作業を進める事を";
				mes "覚悟していたからな。";
				mes "第3の案、というのを潰したかったから";
				mes "ああいう方法をとったんだよ。";
				next;
				cutin "EP14_etran4",1;
				mes "[エスラン]";
				mes "結果的には思い通りになった。";
				mes "もっとも、南の森に移転するという";
				mes "元老会の計画は";
				mes "あの時多くの若いラフィネ達の";
				mes "犠牲があった事もあって";
				mes "言及されることはなかった。";
				next;
				mes "[エスラン]";
				mes "もしロベルにもう一度会えるなら";
				mes "その時の話をしたいなぁ。";
				next;
				cutin "EP14_etran4",255;
				continue;
			case 3:
				cutin "EP14_bif01",3;
				mes "[エスラン]";
				mes "進捗か……。";
				mes "正直言って、自信がないな。";
				mes "今のこのビフロストは";
				mes "あまりにも崩壊し過ぎている。";
				mes "いくら生命力を注いでもきりがない。";
				next;
				mes "[エスラン]";
				mes "大地とは別の問題もある。";
				mes "ホームツリーが当初想定していたより";
				mes "エネルギーをかなり食う。";
				mes "吸収する領域も広く速度も早いんだ。";
				next;
				mes "[エスラン]";
				mes "まぁ、この点は";
				mes "ロベルが努力してくれているだろう。";
				mes "一度、世界樹に繋がったホームツリーは";
				mes "育ちきるまで周辺を壊滅状態にさせる。";
				mes "恐らく今頃、暴走を最小限に抑える為";
				mes "命を懸けているだろう。";
				next;
				cutin "EP14_etran5",1;
				mes "[エスラン]";
				mes "状況が把握できたかい？";
				mes "今、私たちの任務は分かれている。";
				mes "ビフロストで大地に命を吹き込む私。";
				mes "ホームツリーの暴走を止めるロベル。";
				mes "一度始めたらこの作業は";
				mes "二度と離れる事が出来ない。";
				next;
				mes "[エスラン]";
				mes "もし、どちらかが離れてしまったら";
				mes "互いの均衡が崩れ、";
				mes "ビフロストもホームツリーも";
				mes "共倒れしてしまう。";
				next;
				mes "[エスラン]";
				mes "相手がロベルだからこそ……";
				mes "信頼している親友だからこそ";
				mes "できる作業なんだ。";
				next;
				mes "[エスラン]";
				mes "しかし、今の状況が本当に";
				mes "正しい方向に進んでいるのか、";
				mes "見当がつかないんだよ全く。";
				mes "不安にもなるさ……。";
				mes "まぁ、向こうを信じて";
				mes "作業を続けるしかないけどな。";
				next;
				menu "必ずうまくいきます",-;
				cutin "EP14_etran5",255;
				mes "["+strcharinfo(0)+"]";
				mes "あなたのいた時代から遥か未来の今、";
				mes "ビフロストは木、花、草";
				mes "生命が溢れる大地になっています。";
				next;
				cutin "EP14_etran3",1;
				mes "[エスラン]";
				mes "なに……？　ということは……";
				mes "成功、成功するのか!?";
				mes "成功しているというのか未来で？";
				next;
				menu "一緒に外に出てみませんか？",-;
				mes "[エスラン]";
				mes "よ、よし。　わかった。";
				mes "目で確認しよう。ついて行く。";
				set ECL_6QUE,31;
				chgquest 12297,72572;
				close2;
				cutin "EP14_etran3",255;
				warp "ecl_fild01.gat",183,92;
				end;
			}
		}
	}
	if(ECL_6QUE == 36) {
		cutin "EP14_etran01",1;
		mes "[エスラン]";
		mes "む？　この感じは。";
		mes "もしかして以前、";
		mes "その未来から来た旅人か？";
		next;
		cutin "EP14_etran1",1;
		mes "[エスラン]";
		mes "おお、来てくれたのか！";
		next;
		mes "[エスラン]";
		mes "いや、君が訪ねて来てからは";
		mes "仕事が苦にならなくなったよ。";
		mes "この先に正しい道があるとわかると";
		mes "こんなにも違うものなんだな。";
		mes "生命力を調節するのも、";
		mes "楽しくやれている。";
		next;
		cutin "EP14_etran3",1;
		mes "[エスラン]";
		mes "そうだ。それより、";
		mes "ロベルに首飾りは";
		mes "渡してくれたか？";
		mes "葉はどうした？";
		mes "ホームツリーの葉は？";
		next;
		menu "首飾りとホームツリーの葉を渡す",-;
		if(countitem(6539) < 1 || countitem(6540) < 1) {
			cutin "EP14_etran3",1;
			mes "[エスラン]";
			mes "ん？";
			mes "何かロベルから受け取ったのかい？";
			mes "もう一度確認した方が";
			mes "いいんじゃないか？";
			close;
			cutin "EP14_etran01",255;
			warp "ecl_tdun01.gat",60,51;
			end;
		}
		cutin "EP14_etran1",1;
		mes "[エスラン]";
		mes "ホームツリーが育ったという事は";
		mes "事実だったか！";
		mes "よかった、本当に良かったよ！";
		next;
		cutin "EP14_etran6",1;
		mes "[エスラン]";
		mes "しかし、首飾りは";
		mes "受けとってくれなかったか……";
		next;
		menu "ロベルの言葉を伝える",-;
		cutin "EP14_etran1",1;
		mes "[エスラン]";
		mes "やはり、ロベルは";
		mes "私と違って強いな。";
		mes "まぁそれがロベルの長所なんだ。";
		next;
		mes "[エスラン]";
		mes "ふふ。いつもあいつはそうだ。";
		mes "弱音を吐く事も無い。";
		mes "あいつは強いな……。";
		next;
		cutin "EP14_etran1",255;
		mes "["+strcharinfo(0)+"]";
		mes "ロベルは最後に";
		mes "この言葉も伝えてくれと";
		mes "言っていました。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "「私と共に歩んでくれて";
		mes "　ありがとう。";
		mes "　もう二度と会う事は";
		mes "　叶わないかも知れないが、";
		mes "　心はいつも共にある。」";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "「お前が私を信じているくらい";
		mes "　^000099私もお前を信頼している^000000。」";
		next;
		cutin "EP14_etran3",1;
		mes "[エスラン]";
		mes "なんだって！　ロベルが？";
		mes "そう話していたのか？";
		mes "本当に？";
		next;
		cutin "EP14_etran6",1;
		mes "[エスラン]";
		mes "長く共に仕事をしていたが、";
		mes "初めて聞いたよそんな言葉は。";
		mes "信頼してくれていたのか！　そうか……";
		mes "はは……嬉しいな。";
		mes "そうか！　あいつが……。";
		next;
		mes "^000099‐弱々しく肩を震わせている‐^000000";
		next;
		cutin "EP14_etran4",1;
		mes "[エスラン]";
		mes "うん。いや、";
		mes "色々本当にありがとう。";
		mes "未来から来た人。";
		next;
		cutin "EP14_etran1",1;
		mes "[エスラン]";
		mes "君がいなかったら";
		mes "不安を抱えたまま作業を続け";
		mes "心が折れてしまっていただろう。";
		next;
		mes "[エスラン]";
		mes "そして、何より";
		mes "ロベルの想いを確かめられた。";
		mes "とても礼になるとは思えないが。";
		mes "この首飾りを受け取ってくれないか。";
		next;
		cutin "EP14_etran01",1;
		mes "[エスラン]";
		mes "では、私はこれで失礼する。";
		mes "それとこの不思議な機械を";
		mes "作った人にも伝えてほしい。";
		mes "ありがとう、と。";
		next;
		if(checkitemblank() < 3) {
			mes "[エスラン]";
			mes "……と思ったけど、";
			mes "それ以上、持てないみたいね。";
			mes "アイテムの種類数を減らしてから";
			mes "また来てくれ。";
			close2;
			cutin "EP14_etran01",255;
			warp "ecl_tdun01.gat",60,51;
			end;
		}
		cutin "EP14_etran01",255;
		delitem 6540,1;
		delitem 6539,1;
		set ECL_6QUE,37;
		chgquest 12300,12301;
		getitem 2915,1;
		mes "‐エスランの首飾りを手に入れた。";
		mes "　少し輝いている部分がある。";
		mes "　^ff0000隠された力があるのだろうか。^000000";
		mes "　まずはヒエールの元に戻ろう‐";
		close2;
		warp "ecl_tdun01.gat",60,51;
		end;
	}
	if(ECL_6QUE == 37) {
		mes "^000099‐エスランと交信できた場所だ‐^000000";
		close2;
		warp "ecl_tdun01.gat",60,51;
		end;
	}
	// 未調査
	mes "^000099‐特に新しい反応はない‐^000000";
	close2;
	warp "ecl_tdun01.gat",60,51;
	end;
}

ecl_tdun01a.gat,60,56,0	script	#pa0829エスラン室内タッ	139,5,5,{
	if(ECL_6QUE == 29) {
		cutin "EP14_etran0",1;
		mes "[？？？？]";
		mes "大変だ。";
		mes "ホームツリーが吸い込むエネルギーが";
		mes "思ったより大きいぞ。";
		mes "ロベルの奴がある程度は";
		mes "調整してくれるだろうが……";
		mes "やはり無理だったのか!?";
		next;
		mes "^000099‐エスランらしき反応が来た！";
		mes "　もう少し近くに行ってみよう‐^000000";
		set ECL_6QUE,30;
		chgquest 12296,12297;
		close2;
		cutin "EP14_etran0",255;
		end;
	}
	end;
}

ecl_fild01.gat,183,94,0	script	#pa0829エスラン室外タッ	139,3,3,{
	if(ECL_6QUE == 31) {
		cutin "EP14_etran1",1;
		mes "[エスラン]";
		mes "ああ……これが！";
		next;
		cutin "EP14_bif02",3;
		mes "[エスラン]";
		mes "これが……";
		mes "本当に夢ではないんだな？";
		next;
		menu "はい",-;
		mes "["+strcharinfo(0)+"]";
		mes "今、あなたが見ているここが、";
		mes "数千、数万のラフィネ達が生きる";
		mes "生命の地、ビフロストです。";
		next;
		cutin "EP14_etran7",1;
		mes "[エスラン]";
		mes "あぁ、ああ……本当に、";
		mes "本当に良かった。";
		mes "私は間違ってなかった。";
		mes "間違っていなかったんだ私は！";
		next;
		mes "^000099‐エスランは顔を崩しながら、";
		mes "　彼の苦労の結果を見つめていた。";
		mes "　そして何かを思い出したように";
		mes "　質問をしてきた‐^000000";
		next;
		cutin "EP14_etran5",1;
		mes "[エスラン]";
		mes "ロベルは？";
		mes "ホームツリーはどうした？";
		next;
		menu "ホームツリーも成功しています",-;
		cutin "EP14_etran1",1;
		mes "[エスラン]";
		mes "うおお！　おおおお！";
		mes "そうか。そうか！";
		mes "あいつの苦労も報われたか。";
		mes "良かった。";
		mes "間違っていなかったんだな……。";
		next;
		mes "[エスラン]";
		mes "是非ホームツリーも見てみたいな。";
		mes "ホームツリーのある場所に";
		mes "連れて行ってくれないか？";
		next;
		menu "それは無理です……",-;
		cutin "EP14_etran1",255;
		mes "["+strcharinfo(0)+"]";
		mes "通信機の可動範囲の関係で、";
		mes "そこまで案内する事は";
		mes "出来ないんです。";
		next;
		cutin "EP14_etran6",1;
		mes "[エスラン]";
		mes "くっ……そうか。しかし、";
		mes "本当にロベルも成功したのか？";
		mes "私のために嘘をついているんじゃ";
		mes "ないだろうな？";
		next;
		menu "ホームツリーの葉を持ってきます",-;
		cutin "EP14_etran1",1;
		mes "[エスラン]";
		mes "おお、ホームツリーの葉か。";
		mes "確かにそうだ。";
		mes "ホームツリーが正しく育ったのなら、";
		mes "きっとその葉も見事なものだろう。";
		mes "他の植物では見る事ができない、";
		mes "特別な輝きがあるはずだ。";
		next;
		cutin "EP14_etran1",255;
		mes "["+strcharinfo(0)+"]";
		mes "どんな形をしているんですか？";
		next;
		cutin "EP14_etran3",1;
		mes "[エスラン]";
		mes "私も見たことはないからな。";
		mes "ただ、理論上でいくと、";
		mes "生命力が豊富になったホームツリーは";
		mes "黄金のような光を放つはずなんだ。";
		next;
		mes "[エスラン]";
		mes "それ以外に知っている事実はない。";
		mes "ただ、本当のホームツリーの葉なら";
		mes "必ず一目見ればわかるはずだ。";
		mes "ホームツリーの葉から出る";
		mes "生命反応はとても凄いからな。";
		next;
		cutin "EP14_etran4",1;
		mes "[エスラン]";
		mes "もし、君が成長したホームツリーの葉を";
		mes "持って来てくれるなら、";
		mes "私は絶対あきらめない。";
		mes "ロベルの成功を";
		mes "無駄にはできないからな！";
		next;
		mes "[エスラン]";
		mes "そうだ。ロベルの所にいくのなら";
		mes "もう一つ頼みたいことがある。";
		next;
		mes "‐そう言うとエスランは";
		mes "　頭を下げながら首の後ろに両手を回し";
		mes "　付けていたアクセサリーを取った‐";
		next;
		cutin "EP14_bif03",3;
		mes "[エスラン]";
		mes "この首飾りを……";
		mes "ロベルに渡してくれ。";
		mes "私は絶対諦めないと。";
		mes "もう二度と会えないかもしれないが";
		mes "目的を果たすまで……";
		next;
		cutin "EP14_etran01",1;
		mes "^000099‐エスランの姿がぼやけ始める。";
		mes "　通信機の力が弱くなったようだ‐^000000";
		next;
		cutin "EP14_etran0",1;
		mes "^000099‐エスランの姿が消えると、";
		mes "　首飾りは茂みに落ちた‐^000000";
		next;
		if(checkitemblank() < 3) {
			mes "‐アイテムがいっぱいのようだ。";
			mes "　アイテムの種類数を減らしてから";
			mes "　もう一度来よう‐";
			cutin "EP14_bif03",255;
			close;
		}
		cutin "EP14_bif03",3;
		mes "^000099‐古いラフィネの首飾りを";
		mes "　手に入れた‐^000000";
		set ECL_6QUE,32;
		chgquest 72572,12298;
		getitem 6539,1;
		getexp 120000,0;
		getexp 0,80000;
		next;
		mes "^000099‐エネルギーが体に満ちてくる。";
		mes "　ヒエールのところへ戻ろう‐^000000";
		cutin "EP14_bif03",255;
		close;
	}
	end;
}

eclage.gat,291,301,0	script	#pa0829ロベル室外タッチ	139,3,3,{
	if(ECL_6QUE == 27) {
		cutin "EP14_robert1",1;
		mes "[ロベル]";
		mes "こ……これが。";
		next;
		menu "これがホームツリーです",-;
		cutin "EP14_robert3",1;
		mes "[ロベル]";
		mes "ここまで立派に……。";
		mes "……";
		next;
		mes "[ロベル]";
		mes "無理だと思っていた。";
		mes "エスランとの約束だけが";
		mes "心の支えだった。";
		mes "しかし、こんなにも。";
		mes "ああ……。";
		next;
		mes "^000099‐ロベルは、嬉しそうに";
		mes "　ホームツリーを眺めながら";
		mes "　涙を流した。";
		mes "　その時、";
		mes "　ロベルの体がぼやけ始めた‐^000000";
		next;
		cutin "EP14_robert01",1;
		mes "[ロベル]";
		mes "ん？　何だ？";
		mes "何が起きている？";
		next;
		cutin "EP14_robert0",1;
		mes "[ロベル]";
		mes "おい、私の声が聞こえるか？";
		mes "おい" +strcharinfo(0)+ "！";
		mes "いないのか?!";
		mes "何だ……！　やはり夢なのか？";
		next;
		cutin "EP14_robert0",255;
		mes "^000099‐数分もせずに";
		mes "　ロベルの姿が消えてしまった。";
		mes "　まずはヒエールの所に戻って";
		mes "　状況を把握する必要がありそうだ‐^000000";
		set ECL_6QUE,28;
		chgquest 12294,12295;
		close;
	}
	end;
}

ecl_fild01.gat,110,240,0	script	#pa0829反応機1	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？？]";
			mes "うわあ～緑の化け物だ！　逃げろ！";
			break;
		case 1:
			mes "[？？？？]";
			mes "うわああああ!!";
			mes "だから言ったじゃないか!!";
			break;
		case 2:
			mes "[？？？？]";
			mes "肉はまだ焼けていないのか？";
			mes "私は早く食べたい……。";
			break;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

ecl_fild01.gat,110,198,0	script	#pa0829反応機2	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？？]";
			mes "私は……私はやってしまった。";
			mes "禁止された領域！";
			mes "そして、奴らに奪われてしまった。";
			mes "私の300グラム。";
			next;
			mes "[？？？？]";
			mes "オーブンの前での";
			mes "私語は禁止ですよ。";
			mes "オルレアン学生。";
			break;
		case 1:
			mes "[？？？？]";
			mes "こ……この者は";
			mes "本当に正気なんですか？";
			break;
		case 2:
			mes "[？？？？]";
			mes "うちのお父さんは";
			mes "精錬関連の品物を横流しなんて";
			mes "していないよ！";
			next;
			mes "[？？？？]";
			mes "うるさい！";
			mes "誰が何と言っても君のお父さんは";
			mes "精錬関連の品物を横流しした";
			mes "卑怯者だ。";
			mes "悔しかったらいつでも訪ねて来い。";
			next;
			mes "[？？？？]";
			mes "くそ……いつか";
			mes "お前の頭を精錬してやる。";
			break;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

ecl_fild01.gat,165,158,0	script	#pa0829反応機3	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？？]";
			mes "ねえ、あなた。";
			mes "私がどうして怒っているのか";
			mes "本当にわかってるの？　ねえ？";
			next;
			mes "[？？？？]";
			mes "悪かった、悪かったよ。";
			next;
			mes "[？？？？]";
			mes "何が？";
			break;
		case 1:
			mes "[？？？？]";
			mes "美味しそう！";
			mes "美味しそうな焼き鳥!!";
			break;
		case 2:
			mes "[？？？？]";
			mes "息子よ、何をしているんだ？";
			next;
			mes "[？？？？]";
			mes "防具の手入れ中です。お父さん。";
			break;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

ecl_fild01.gat,237,166,0	script	#pa0829反応機4	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？]";
			mes "1……2……3……4……5……6……";
			mes "多い……。";
			mes "おかしい……。";
			mes "1個多い……。";
			mes "この唐揚げ、1個多い！";
			break;
		case 1:
			mes "[？？？]";
			mes "私はおかしくなり始めている。";
			mes "このヘッドフォンに";
			mes "私の全てを傾けるぅぅぅ！";
			next;
			mes "[？？？]";
			mes "音楽だけがこの国で";
			mes "唯一認められている麻薬だから……。";
			break;
		case 2:
			mes "[？？？]";
			mes "もう寝る事にしよう。";
			mes "明日、起きたら";
			mes "すべてが終わっていて";
			mes "何も無い日常が";
			mes "平和に訪れるはずだ。";
			mes "メリークリスマス。";
			next;
			mes "^000099‐通信機が動作した。";
			mes "　なぜか悲しい気持ちになった‐^000000";
			close;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

ecl_fild01.gat,230,206,0	script	#pa0829反応機5	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？]";
			mes "1……2……3……4……5……6……";
			mes "多い……。";
			mes "おかしい……。";
			mes "1個多い……。";
			mes "この唐揚げ、1個多い！";
			break;
		case 1:
			mes "[？？？？]";
			mes "ねえ、あなた。";
			mes "私がどうして怒っているのか";
			mes "本当にわかってるの？　ねえ？";
			next;
			mes "[？？？？]";
			mes "悪かった、悪かったよ。";
			next;
			mes "[？？？？]";
			mes "何が？";
			break;
		case 2:
			mes "[？？？]";
			mes "ちょっと右に回って下さい～。";
			mes "もうちょっと左に～。はい。";
			mes "息を吸って～、はい！我慢して～！";
			mes "カシャッ！";
			mes "はい、息を吐いて下さい～。";
			break;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

ecl_fild01.gat,234,266,0	script	#pa0829反応機6	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？？]";
			mes "うわあ～緑の化け物だ！　逃げろ！";
			break;
		case 1:
			mes "[？？？？]";
			mes "うわああああ!!";
			mes "だから言ったじゃないか!!";
			break;
		case 2:
			mes "[？？？？]";
			mes "肉はまだ焼けていないのか？";
			mes "私は早く食べたい……。";
			break;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

ecl_fild01.gat,179,125,0	script	#pa0829反応機7	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？？]";
			mes "私は……私はやってしまった。";
			mes "禁止された領域！";
			mes "そして、奴らに奪われてしまった。";
			mes "私の300グラム。";
			next;
			mes "[？？？？]";
			mes "オーブンの前での";
			mes "私語は禁止ですよ。";
			mes "オルレアン学生。";
			break;
		case 1:
			mes "[？？？？]";
			mes "こ……この者は";
			mes "本当に正気なんですか？";
			break;
		case 2:
			mes "[？？？？]";
			mes "うちのお父さんは";
			mes "精錬関連の品物を横流しなんて";
			mes "していないよ！";
			next;
			mes "[？？？？]";
			mes "うるさい！";
			mes "誰が何と言っても君のお父さんは";
			mes "精錬関連の品物を横流しした";
			mes "卑怯者だ。";
			mes "悔しかったらいつでも訪ねて来い。";
			next;
			mes "[？？？？]";
			mes "くそ……いつか";
			mes "お前の頭を精錬してやる。";
			break;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

ecl_fild01.gat,179,179,0	script	#pa0829反応機8	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？？]";
			mes "ねえ、あなた。";
			mes "私がどうして怒っているのか";
			mes "本当にわかってるの？　ねえ？";
			next;
			mes "[？？？？]";
			mes "悪かった、悪かったよ。";
			next;
			mes "[？？？？]";
			mes "何が？";
			break;
		case 1:
			mes "[？？？？]";
			mes "美味しそう！";
			mes "美味しそうな焼き鳥!!";
			break;
		case 2:
			mes "[？？？？]";
			mes "息子よ、何をしているんだ？";
			next;
			mes "[？？？？]";
			mes "防具の手入れ中です。お父さん。";
			break;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

ecl_fild01.gat,187,243,0	script	#pa0829反応機9	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？]";
			mes "1……2……3……4……5……6……";
			mes "多い……。";
			mes "おかしい……。";
			mes "1個多い……。";
			mes "この唐揚げ、1個多い！";
			break;
		case 1:
			mes "[？？？]";
			mes "私はおかしくなり始めている。";
			mes "このヘッドフォンに";
			mes "私の全てを傾けるぅぅぅ！";
			next;
			mes "[？？？]";
			mes "音楽だけがこの国で";
			mes "唯一認められている麻薬だから……。";
			break;
		case 2:
			mes "[？？？]";
			mes "もう寝る事にしよう。";
			mes "明日、起きたら";
			mes "すべてが終わっていて";
			mes "何も無い日常が";
			mes "平和に訪れるはずだ。";
			mes "メリークリスマス。";
			next;
			mes "^000099‐通信機が動作した。";
			mes "　なぜか悲しい気持ちになった‐^000000";
			close;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

ecl_fild01.gat,159,278,0	script	#pa0829反応機10	139,3,3,{
	if(ECL_6QUE == 29) {
		switch(rand(3)) {
		case 0:
			mes "[？？？]";
			mes "1……2……3……4……5……6……";
			mes "多い……。";
			mes "おかしい……。";
			mes "1個多い……。";
			mes "この唐揚げ、1個多い！";
			break;
		case 1:
			mes "[？？？？]";
			mes "ねえ、あなた。";
			mes "私がどうして怒っているのか";
			mes "本当にわかってるの？　ねえ？";
			next;
			mes "[？？？？]";
			mes "悪かった、悪かったよ。";
			next;
			mes "[？？？？]";
			mes "何が？";
			break;
		case 2:
			mes "[？？？]";
			mes "ちょっと右に回って下さい～。";
			mes "もうちょっと左に～。はい。";
			mes "息を吸って～、はい！我慢して～！";
			mes "カシャッ！";
			mes "はい、息を吐いて下さい～。";
			break;
		}
		next;
		mes "^000099‐通信機は動作したが、";
		mes "　エスランとは関係なさそうだ‐^000000";
		close;
	}
	end;
}

eclage.gat,155,91,4	script	#pa0829ヒエール扉10	836,{
	mes "[掲示板]";
	mes "ヒエールの研究室。";
	mes "許可の無い";
	mes "パパン、動物、サファ族の";
	mes "出入を禁止します。";
	next;
	if(select("立ち去る","中に入る") == 1)
		close;
	warp "ecl_in04.gat",107,213;
	end;
OnInit:
	waitingroom "ヒエールの研究室",0;
	end;
}

ecl_in04.gat,109,212,0	warp	ecl_in04_exit	1,1,eclage.gat,152,91

ecl_in04.gat,105,216,4	script	ヒエールの作業台	111,{
	switch(ECL_6QUE) {
	case 14:
		// 未調査
		mes "[ヒエール]";
		mes "さて、それじゃあ実際にこれを使って";
		mes "ここに置いてこうして、と……。";
		mes "おや……変だな？";
		mes "確かに本に書かれてある通りの";
		mes "配列になっているはずなんだが。";
		mes "どうして反応しないんだ。";
		next;
		mes "[ヒエール]";
		mes "う～む";
		mes "こうすればいいのかな？";
		mes "いや、違うな。";
		mes "こっちか！";
		mes "あれ、こうか？";
		mes "…………";
		next;
		mes "[ヒエール]";
		mes "どうしてダメなんだよ！";
		mes "言う事を聞けよ!!";
		mes "このように配列したら";
		mes "こういう反応が返ってくるべきだろう！";
		mes "何故なんだ！";
		next;
		mes "^000099‐思い通り進まず、暴れるヒエール。";
		mes "　拍子に手から闇の破片が転げ落ちた。";
		mes "　このままでは闇の破片が……！‐^000000";
		next;
		menu "手を伸ばし闇の破片を掴む",-;
		mes "^000099‐床に落ちそうな闇の破片を";
		mes "　すんでの所で掴み取り、";
		mes "　ヒエールがのべていた配列の中に";
		mes "　そっと戻した‐^000000";
		next;
		mes "‐その瞬間！‐";
		next;
		sc_start3 SC_BLIND,0,0,0,0,60000,10;
		mes "^000099‐目の前が暗くなり";
		mes "　何処からか声が聞こえてきた‐^000000";
		next;
		cutin "EP14_etran0",1;
		mes "[？？？？]";
		mes "例えば、君が話していた通り";
		mes "ホームツリーを";
		mes "先に完成させたとしよう。";
		mes "だが、その後はどうする？";
		mes "奴が吸い込む巨大なエネルギーは";
		mes "どうしろというんだ？";
		next;
		cutin "EP14_robert0",1;
		mes "[？？？？]";
		mes "確かにその通りだ。";
		mes "ホームツリーを生き返らせるには、";
		mes "想像をはるかに超える生命力が必要だ。";
		mes "ただ、それでもホームツリーは";
		mes "生き返らせないと駄目だ。";
		mes "必ず必要だ。";
		next;
		cutin "EP14_etran0",1;
		mes "[？？？？]";
		mes "その間に死んでいく";
		mes "他の生命体たちはどうする。";
		mes "ホームツリーの完成のために";
		mes "何十年、何百年間という期間、";
		mes "ホームツリー界隈は";
		mes "不毛の地になるかも知れないんだぞ！";
		next;
		mes "[？？？？]";
		mes "いや、間違いなくなる！";
		mes "ホームツリー以外の生命は全滅だ。";
		mes "ホームツリーは命を助ける為の物だ！";
		mes "これじゃあ本末転倒じゃないか?!";
		next;
		cutin "EP14_robert0",1;
		mes "[？？？？]";
		mes "ホームツリー無しに生命を維持しても、";
		mes "どうせ長くは持たないんだ。";
		mes "ある程度の犠牲は覚悟しないと駄目だ。";
		mes "それは誰よりもお前が";
		mes "知っているだろう！";
		next;
		cutin "EP14_etran0",1;
		mes "[？？？？]";
		mes "やはりホームツリーを完成させつつ";
		mes "その力を利用する事で並行して";
		mes "大地を生き返らせる、という方法が";
		mes "一番早いし、シンプルだろう。";
		next;
		mes "[？？？？]";
		mes "ただ、いずれにせよこの決断で";
		mes "我々の命運を大きく左右するのは";
		mes "間違いない事だ……。";
		mes "果たしてそんな権限が我々に";
		mes "あるんだろうか……！";
		next;
		mes "[？？？？]";
		mes "ホームツリーを生かす事が";
		mes "本当に正しい事なのか？";
		mes "命を左右するような権限など";
		mes "誰も持つべきではないんじゃないか？";
		next;
		cutin "EP14_robert0",1;
		mes "[？？？？]";
		mes "ふふ。良い夢を見ているな、エスラン。";
		mes "必ず選択は必要だ。";
		mes "それが生きるという事だ。";
		mes "誰かが決めなければいけない。";
		next;
		mes "[？？？？]";
		mes "まぁ、私たち二人だけで話しても";
		mes "埒が開かないだろう。";
		mes "私は元老会の決定に従うことにするよ。";
		set ECL_6QUE,15;
		chgquest 12287,72560;
		close2;
		cutin "EP14_robert0",255;
		sc_end SC_BLIND;
		end;
	case 15:
		mes "^000099‐ヒエールが作ってくれた";
		mes "　次元通信機の初号機がある。";
		mes "　触ると作動しそうな感じがする‐^000000";
		close;
	case 16:
		sc_start3 SC_BLIND,0,0,0,0,60000,10;
		mes "^000099‐ヒエールが並べている配列の中央に";
		mes "　闇の破片を置いた瞬間、";
		mes "　目の前が暗くなり、";
		mes "　声が聞こえてきた‐^000000";
		next;
		cutin "EP14_robert0",1;
		mes "[？？？？]";
		mes "報告します。調査によると";
		mes "ホームツリーの創造にかかる時間は";
		mes "少なくとも200年。";
		mes "その間、この大地に生きる生命体の";
		mes "約80%が絶滅します。";
		next;
		mes "[？？？？]";
		mes "ホームツリーを生き返らせない場合";
		mes "生命源の供給が徐々に減って行く為、";
		mes "約400年で生命体は全て絶滅します。";
		next;
		mes "[？？？？]";
		mes "200年の間に多数の犠牲を覚悟し、";
		mes "根本を立て直し、長い平和を楽しむか。";
		mes "400年間、少しずづ財産を減らしながら";
		mes "死んでいくのか。";
		mes "二つに一つです。";
		next;
		mes "[？？？？]";
		mes "どうか、元老会の賢明な判断を";
		mes "お願いします。";
		mes "以上です。";
		next;
		cutin "EP14_robert0",255;
		mes "[低い声]";
		mes "うむ。ありがとう。";
		mes "報告書は受け取らせていただく。";
		next;
		mes "[低い声]";
		mes "では、発表する。";
		mes "我々、元老会の決定は……";
		next;
		mes "^000099‐声にノイズが入りながら、";
		mes "　元の世界に戻った‐^000000";
		set ECL_6QUE,17;
		chgquest 12288,72562;
		sc_end SC_BLIND;
		close;
	case 17:
		mes "^000099‐ヒエールが作ってくれた";
		mes "　次元通信機の初号機がある。";
		mes "　今は触っても動かない‐^000000";
		close;
	case 33:
		cutin "EP14_robert01",1;
		mes "[ロベル]";
		mes "ん？";
		mes "これは……？";
		mes "この前のあいつらか？";
		mes "やはり夢ではなかったのか。";
		next;
		cutin "EP14_robert5",1;
		mes "[ロベル]";
		mes "おい、" +strcharinfo(0)+ "！";
		mes "こないだは急にいなくなったな。";
		mes "あの時の出来事は";
		mes "夢だと思っていたよ。";
		next;
		mes "^000099‐ロベルが鮮明な姿で登場した‐";
		next;
		menu "経緯を説明する",-;
		cutin "EP14_robert1",1;
		mes "[ロベル]";
		mes "なるほど。";
		mes "まだ機械の調子が良くなかったのか。";
		mes "しかし……";
		mes "技術の進歩というのは";
		mes "驚きが絶えないな。";
		next;
		mes "[ロベル]";
		mes "ん？　君の右手にある";
		mes "その首飾りはなんだ？";
		while(1) {
			next;
			if(select("市場で買いました","盗みました","エスランと会って来ました") == 3)
				break;
			cutin "EP14_robert5",1;
			mes "[ロベル]";
			mes "おいおい。";
			mes "私を騙すことはできないぞ、";
			mes "正直に話してくれ。";
			mes "その首飾りはどこで手に入れた？";
		}
		cutin "EP14_robert5",255;
		mes "["+strcharinfo(0)+"]";
		mes "エスランの首飾りです。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "エスランは、";
		mes "かなり疲れているように見えました。";
		mes "そこでビフロストの現在の姿を";
		mes "見てもらいました。";
		next;
		cutin "EP14_robert3",1;
		mes "[ロベル]";
		mes "ふむ。";
		next;
		cutin "EP14_robert3",255;
		mes "["+strcharinfo(0)+"]";
		mes "ビフロストの大地が";
		mes "生命を取り戻した姿をみて、";
		mes "エスランも喜んでいました。";
		next;
		cutin "EP14_robert3",1;
		mes "[ロベル]";
		mes "そうか！";
		mes "無理をして倒れていないか";
		mes "心配していたのだが";
		mes "元気を取り戻したようで";
		mes "安心したよ。";
		next;
		mes "[ロベル]";
		mes "エスランも、自分の努力が";
		mes "報われた姿を見て";
		mes "さぞ、嬉しかっただろう。";
		mes "私からも礼を言う。";
		next;
		cutin "EP14_robert3",255;
		mes "["+strcharinfo(0)+"]";
		mes "エスランは、この首飾りを";
		mes "あなたに渡してくれと。";
		mes "自身の目で見た未来のビフロストの為に";
		mes "絶対にあきらめないで努力すると。";
		next;
		mes "["+strcharinfo(0)+"]";
		mes "エスランはあなたが";
		mes "勇気を失うのを心配していました。";
		mes "あなたのホームツリーが";
		mes "うまく育ったのか";
		mes "直接確認できない状況だったので。";
		next;
		cutin "EP14_robert3",1;
		mes "[ロベル]";
		mes "それはしょうがない。";
		mes "そもそも、大地に生命を付与する間、";
		mes "術師は絶対に離れられないからな。";
		mes "しかし、なんとかしてエスランにも";
		mes "この景色を見せたかったものだが……。";
		next;
		menu "ホームツリーの葉が欲しい",-;
		cutin "EP14_robert4",1;
		mes "[ロベル]";
		mes "ああ、なるほど！";
		mes "エスランにホームツリーの葉を";
		mes "見せようという事だな。";
		next;
		cutin "EP14_robert2",1;
		mes "[ロベル]";
		mes "ちょうど私のホームツリーが";
		mes "初めての葉を生成した状態だ。";
		mes "少し待ってくれ。";
		cutin "EP14_robert2",255;
		set ECL_6QUE,34;
		chgquest 12299,72574;
		close;
	case 34:
		mes "^000099‐まだロベルの反応がない。";
		mes "　葉を採収しているようだ‐^000000";
		close;
	case 35:
		cutin "EP14_robert2",1;
		mes "[ロベル]";
		mes "待たせたな。";
		next;
		mes "[ロベル]";
		mes "これがホームツリーの葉だ。";
		mes "受け取ってくれ。";
		next;
		cutin "EP14_robert4",1;
		mes "[ロベル]";
		mes "あ、それと先ほど君が渡してくれた";
		mes "首飾りだが、";
		mes "エスランに返してやってくれ。";
		next;
		mes "[ロベル]";
		mes "あいつの所持品を";
		mes "肌身離さず持っておくなんて";
		mes "気味が悪い。はは。";
		next;
		cutin "EP14_robert2",1;
		mes "[ロベル]";
		mes "ただ、最後に1つ";
		mes "あいつに一言";
		mes "伝言をお願いしたい。";
		next;
		cutin "EP14_robert01",1;
		mes "[ロベル]";
		mes "私と共に歩んでくれて";
		mes "ありがとう。";
		mes "もう二度と会う事は";
		mes "叶わないかも知れないが";
		mes "心はいつも共にあると。";
		next;
		mes "[ロベル]";
		mes "そして……";
		mes "お前が私を信じているくらい";
		mes "^000099私もお前を信頼している^000000と。";
		next;
		if(checkitemblank() < 3) {
			mes "[ロベル]";
			mes "荷物がいっぱいのようだな。";
			mes "アイテムの種類数を減らしてから";
			mes "もう一度来てくれ。";
			close2;
			cutin "EP14_robert01",255;
			end;
		}
		cutin "EP14_robert01",255;
		mes "^000099‐ロベルはその言葉を残し、";
		mes "　通信機の中に姿を消した。";
		mes "　手にはロベルが渡してくれた";
		mes "　ホームツリーの葉と";
		mes "　エスランの首飾りが残った‐^000000";
		set ECL_6QUE,36;
		chgquest 72576,12300;
		getitem 6540,1;
		getexp 120000,0;
		getexp 0,80000;
		close;
	case 36:
		if(countitem(6540) < 1 || countitem(6539) < 1) {
			cutin "EP14_robert2",1;
			mes "[ロベル]";
			mes "ホームツリーの葉と首飾りを";
			mes "エスランに渡してくれ。";
			if(checkitemblank() < 3) {
				next;
				mes "[ロベル]";
				mes "荷物がいっぱいのようだな。";
				mes "アイテムの種類数を減らしてから";
				mes "もう一度来てくれ。";
				close2;
				cutin "EP14_robert01",255;
				end;
			}
			if(countitem(6540) < 1)
				getitem 6540,1;
			if(countitem(6539) < 1)
				getitem 6539,1;
			close;
		}
		mes "^000099‐次元通信機が置かれてある。";
		mes "　今すぐ使う事はなさそうだ‐^000000";
		close;
	case 37:
	case 38:
		mes "^000099‐次元通信機が置かれてある。";
		mes "　今すぐ使う事はなさそうだ‐^000000";
		close;
	case 39:
		mes "^000099‐最新の次元通信機だ。";
		mes "　これを利用する事で過去や未来、";
		mes "　また、他の次元の映像を";
		mes "　覗き込むことができそうだ。";
		mes "　気になる時に使って見よう‐^000000";
		set ECL_6QUE,41;
		chgquest 72580,201575;
		close;
	case 40:
		mes "^000099‐最新の次元通信機だ。";
		mes "　これを利用する事で過去や未来、";
		mes "　また、他の次元の映像を";
		mes "　覗き込むことができそうだ。";
		mes "　気になる時に使って見よう‐^000000";
		set ECL_6QUE,41;
		chgquest 72582,201575;
		close;
	case 41:
		switch(rand(3)) {
		case 0:
			mes "^000099‐悠久なる絆‐^000000";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "お～い、ロベル～！";
			mes "ロベル～！";
			mes "荷物はこんなもので大丈夫かな？";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "おいおい、お前の荷物はわからんよ。";
			mes "多めに用意しておけよ。";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "はは。それもそうか。";
			next;
			cutin "EP14_etran4",1;
			mes "[エスラン]";
			mes "……";
			next;
			mes "[エスラン]";
			mes "いよいよだな、ロベル。";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "そうだな。";
			next;
			cutin "EP14_etran4",1;
			mes "[エスラン]";
			mes "うまく……";
			mes "いくといいな。";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "そうだな。";
			next;
			mes "[ロベル]";
			mes "理論上エネルギーは足りている。";
			mes "ホームツリーの創造中に発生する";
			mes "大地の腐敗を";
			mes "ある程度抑える事さえできれば";
			mes "ホームツリーは完成するはずだ。";
			next;
			cutin "EP14_robert2",1;
			mes "[ロベル]";
			mes "つまりはお前次第という事だ。";
			next;
			cutin "EP14_etran3",1;
			mes "[エスラン]";
			mes "またそうやって！";
			mes "もちろん、全力は尽くすさ。";
			next;
			cutin "EP14_etran5",1;
			mes "[エスラン]";
			mes "でもやっぱり不安で……。";
			mes "　";
			mes "……";
			mes "ロベルは変わらないよな～本当に。";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "そうでもないさ。";
			mes "お前も随分強くなったんじゃないか。";
			next;
			cutin "EP14_etran5",1;
			mes "[エスラン]";
			mes "そうかなぁ。";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "そろそろ出発の時間だ。";
			next;
			cutin "EP14_etran4",1;
			mes "[エスラン]";
			mes "もうそんな時間か。";
			next;
			mes "[エスラン]";
			mes "なぁ、ロベル。";
			mes "また、会えるといいな。";
			next;
			cutin "EP14_robert2",1;
			mes "[ロベル]";
			mes "その時は、お前の好きな";
			mes "ブルーベリーパイを";
			mes "たくさん作ってやろう。";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "本当に！　やった！";
			mes "絶対だぞ。";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "まぁ、お互いの状況はきっと";
			mes "このエクラージュの大地が";
			mes "教えてくれるだろう。";
			mes "無理せず慎重に進めよう。";
			next;
			mes "[ロベル]";
			mes "さて……";
			mes "行くか。";
			next;
			cutin "EP14_etran6",1;
			mes "[エスラン]";
			mes "ロベル～。";
			next;
			cutin "EP14_etran4",1;
			mes "[エスラン]";
			mes "頑張ろうな！";
			next;
			cutin "EP14_robert2",1;
			mes "[ロベル]";
			mes "ああ。";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "それじゃ！";
			next;
			cutin "EP14_robert4",1;
			mes "[ロベル]";
			mes "ああ。";
			close2;
			cutin "EP14_robert4",255;
			end;
		case 1:
			mes "^000099‐料理を作るロベル‐^000000";
			next;
			cutin "EP14_robert2",1;
			mes "[ロベル]";
			mes "うん、いい匂いだ。";
			next;
			cutin "EP14_robert2",1;
			mes "[ロベル]";
			mes "エスランがもうすぐ戻る頃だな。";
			mes "あいつが戻る頃には";
			mes "いい感じに出来上がっているだろう。";
			next;
			cutin "EP14_robert4",1;
			mes "[ロベル]";
			mes "よ～し。うまく焼けた。";
			mes "このかりっとするパイ生地。";
			mes "匂いも良い。";
			mes "うん。我ながら良くできたな。";
			mes "さて……ちょっと食べてみるかな。";
			next;
			cutin "EP14_robert2",1;
			mes "[ロベル]";
			mes "ふむ……いや。";
			mes "エスランが家に戻っている頃か。";
			mes "持って行って一緒に食べるかな。";
			next;
			cutin "EP14_robert2",255;
			mes "^000099‐パイを持ってエスランの家を";
			mes "　訪ねるロベル。‐^000000";
			next;
			cutin "EP14_etran2",1;
			mes "[エスランの案内板]";
			mes "ここは私、エスランの家です！";
			mes "今日、私はビフロストに行っています！";
			mes "帰りは遅くなりそうです。";
			mes "プレゼントは玄関に置いて下さい。";
			next;
			cutin "EP14_etran2",1;
			mes "[エスランの案内板]";
			mes "あ、でも……良く考えたら";
			mes "プレゼントなんて持って来てくれる人";
			mes "いないか！";
			mes "まさかロベルがパイを焼いて";
			mes "きてくれるはずもないし。";
			mes "はははは！";
			next;
			cutin "EP14_robert5",1;
			mes "[ロベル]";
			mes "持って来ていない！";
			mes "パイなんて焼いて持って来ていない！";
			mes "二度と持ってくるものか！";
			close2;
			cutin "EP14_robert5",255;
			end;
		case 2:
			mes "^000099‐エスランとロベルの幼少時代１‐^000000";
			next;
			cutin "EP14_robert4",1;
			mes "[ロベル]";
			mes "どうした？　なぜ泣いている？";
			next;
			cutin "EP14_etran7",1;
			mes "[エスラン]";
			mes "ううう。私の事を背が小さくて";
			mes "みっともないと同じクラスの奴らが";
			mes "いじめてくる……。";
			next;
			cutin "EP14_robert4",1;
			mes "[ロベル]";
			mes "なんだ。";
			mes "そんなことで泣いているのか。";
			mes "だからと言ってお前の背が";
			mes "急に高くなるわけではないだろう。";
			next;
			mes "[ロベル]";
			mes "いいか、そいつらは";
			mes "お前が泣いている姿を見る為に";
			mes "わざといじめているんだ。";
			mes "いつまでも泣いていたら";
			mes "相手の思うままだろう。";
			mes "もう泣くのはやめろ。";
			next;
			cutin "EP14_etran7",1;
			mes "[エスラン]";
			mes "ぐすん。";
			next;
			cutin "EP14_robert3",1;
			mes "[ロベル]";
			mes "やれやれ……。";
			mes "本当に泣き虫だな。";
			next;
			cutin "EP14_etran5",1;
			mes "[エスラン]";
			mes "いいよなロベルは背も高いし……。";
			mes "私もロベルのように";
			mes "クールになりたい。";
			next;
			cutin "EP14_robert4",1;
			mes "[ロベル]";
			mes "……";
			next;
			cutin "EP14_robert4",255;
			mes "^000099‐数時間後‐^000000";
			next;
			cutin "EP14_robert3",1;
			mes "[ロベル]";
			mes "^FF0000この辺りか。^000000";
			next;
			cutin "EP14_robert3",255;
			mes "^000099‐エスランをいじめていた";
			mes "　ラフィネたちはその夜、";
			mes "　全治数週間の怪我を負った。‐^000000";
			close2;
			cutin "EP14_etran1",255;
			end;
		case 3:
			mes "^000099‐エスランとロベルの幼少時代２‐^000000";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "お～い、ロベル～！";
			mes "ロベル～！";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "なんだ。エスラン。";
			mes "随分元気じゃないか";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "ふふふ。実は";
			mes "この間私をいじめてきてた奴らが";
			mes "仲直りしてくれって言ってきたんだ！";
			mes "ごめんなさいって謝りながら！";
			next;
			cutin "EP14_robert2",1;
			mes "[ロベル]";
			mes "そうか。よかったじゃないか。";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "そうなんだよ。ふふ。";
			mes "だからね、こう言ってやったんだ！";
			next;
			cutin "EP14_etran2",1;
			mes "[エスラン]";
			mes "うるさい!!";
			mes "お前たちみたいに";
			mes "平気で人の悪口を言う奴と";
			mes "友達になる気は無い！";
			mes "ってね！";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "いやーその後すごい殴られたよ！";
			mes "でもさ。";
			mes "なんか彼らも怪我をしていて";
			mes "おあいこだったんだ。";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "どうだいロベル！";
			mes "少しは男らしくなっただろう私も！";
			next;
			cutin "EP14_robert4",1;
			mes "[ロベル]";
			mes "はは。";
			mes "はははは！";
			mes "エスラン。";
			mes "お前は面白いなやはり。";
			close2;
			cutin "EP14_robert4",255;
			end;
		case 4:
			mes "^000099‐エスランの苦悩‐^000000";
			next;
			cutin "EP14_etran4",1;
			mes "[エスラン]";
			mes "うおっ！";
			mes "またか。";
			mes "急に大地の破壊速度が……。";
			next;
			mes "[エスラン]";
			mes "はぁ～。";
			mes "ロベルは大地を通じて";
			mes "お互いの状況を確認出来るって";
			mes "言っていたけど……。";
			next;
			cutin "EP14_etran5",1;
			mes "[エスラン]";
			mes "自分の力が弱くなっているのか";
			mes "大地の力が強くなっているのか";
			mes "毎日同じ作業をしていると";
			mes "全然わからなくなってくるよ……。";
			next;
			mes "[エスラン]";
			mes "本当に上手くいってるのかなこれ……。";
			close2;
			cutin "EP14_etran5",255;
			end;
		case 5:
			mes "^000099‐もしもエスランとロベルが";
			mes "　囚人と看守だったら？‐^000000";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "看守～ここは乾燥しすぎているよ。";
			mes "これでは私の皮膚が全部";
			mes "カサカサになってしまうよ～。";
			mes "それでもいいというのか？　ん？";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "顔を洗え。";
			next;
			cutin "EP14_etran5",1;
			mes "[エスラン]";
			mes "あっ、はい……。";
			close2;
			cutin "EP14_etran5",255;
			end;
		case 6:
			mes "^000099‐料理の鉄人ロベル‐^000000";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "今からパイを作る。";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "本当！　本当に!?";
			mes "もしかしてブルーベリーも入れる？";
			mes "おおぉ！　大好きなんだよ！";
			next;
			cutin "EP14_robert4",1;
			mes "[ロベル]";
			mes "もちろん、入れる。";
			mes "そして、今日の朝一で手に入れた";
			mes "大きなイチゴも乗せる。";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "な、なんだって？";
			mes "イ、イチゴまで!?";
			mes "何という事だ！";
			mes "こんな事があっていいのか！";
			mes "考えるだけで頭がおかしくなる！";
			next;
			mes "[エスラン]";
			mes "そ、それでいったい";
			mes "いくつ焼くつもりなんだい？";
			mes "2つ？　いや、待てよ……";
			mes "2つでは足りなくない？";
			next;
			cutin "EP14_robert4",1;
			mes "[ロベル]";
			mes "1つ焼く。";
			mes "君のはない。";
			next;
			cutin "EP14_etran6",1;
			mes "[エスラン]";
			mes "えええええええええええええ！";
			mes "いじわるしないでよ！";
			mes "私が何をしたっていうんだよ！";
			close2;
			cutin "EP14_etran6",255;
			end;
		case 7:
			mes "^000099‐ホームツリー‐^000000";
			next;
			cutin "EP14_robert2",1;
			mes "[ロベル]";
			mes "うむ。";
			mes "順調だな。";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "ただ……";
			mes "思ったより成長が早い。";
			next;
			mes "[ロベル]";
			mes "予定より良いペースで";
			mes "成長してくれそうだが、";
			mes "上手くコントロールしないと";
			mes "大地の方が……。";
			mes "後はエスランか。";
			next;
			mes "[ロベル]";
			mes "上手く持ちこたえてくれると";
			mes "いいんだが……。";
			close2;
			cutin "EP14_robert1",255;
			end;
		case 8:
			mes "^000099‐決断‐^000000";
			next;
			cutin "EP14_etran8",1;
			mes "[エスラン]";
			mes "くそっ！";
			mes "なんなんだよ元老会の奴ら！";
			mes "なんであいつら頑なに";
			mes "ビフロストへの移住を進めるんだ。";
			mes "もう無理だってわかるだろう！";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "威信を保とうと必死なんだろう。";
			mes "遠征が失敗しているのは間違いない。";
			mes "今後うまくいく見込みも少ない。";
			next;
			mes "[ロベル]";
			mes "ただ、遠征を決定した段階では";
			mes "選択肢として妥当だったのも事実だ。";
			next;
			cutin "EP14_etran8",1;
			mes "[エスラン]";
			mes "それはそうだけど。でもさ!!";
			mes "このままじゃ被害が増えるだけだよ。";
			mes "何より私たちが計画している";
			mes "ホームツリーの創造にも";
			mes "影響が出てしまう。";
			next;
			cutin "EP14_robert1",1;
			mes "[ロベル]";
			mes "そうだな……。";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "そうだ。ロベル！";
			mes "良い事を考えたぞ。";
			mes "あれをこうしてさ……";
			mes "ごにょごにょ……";
			next;
			cutin "EP14_robert3",1;
			mes "[ロベル]";
			mes "なるほど。";
			mes "くだらない……が、案外そうだな。";
			mes "うまくいくかもしれん。";
			next;
			cutin "EP14_etran1",1;
			mes "[エスラン]";
			mes "でしょ！";
			mes "上手くいくと思うな。";
			next;
			cutin "EP14_robert3",1;
			mes "[ロベル]";
			mes "いいのか？";
			mes "うまくいったら";
			mes "本当に後戻りはできないぞ。";
			next;
			cutin "EP14_etran4",1;
			mes "[エスラン]";
			mes "……";
			mes "…………";
			next;
			mes "[エスラン]";
			mes "うん。";
			next;
			mes "[エスラン]";
			mes "何もしないと";
			mes "結局駄目になってしまうんだろう。";
			mes "覚悟は決めるさ！";
			mes "ロベルこそ平気なのか!?";
			next;
			cutin "EP14_robert4",1;
			mes "[ロベル]";
			mes "ふふ。";
			mes "そうか。私は平気だよ。";
			mes "お前が心配だっただけだ。";
			next;
			cutin "EP14_etran5",1;
			mes "[エスラン]";
			mes "ちぇっ";
			mes "またそうやって。";
			mes "　";
			mes "じゃあさ、次の……";
			mes "　";
			mes "‐通信はここで途切れた‐";
			close2;
			cutin "EP14_etran5",255;
			end;
		case 9:
			mes "[？？？]";
			mes "ピーーーAND!?";
			mes "～～ピーピー～";
			mes "OH　MY　SHOULDER!!";
			next;
			mes "^000099‐そっと閉じた‐^000000";
			close;
		case 10:
			mes "[？？？]";
			mes "後1回。後1回成功すれば";
			mes "これまでの負けがチャラになる。";
			mes "これはチャンスなんだ！";
			mes "そう。ここが勝負所だ！";
			next;
			mes "[？？？]";
			mes "頼む！";
			next;
			mes "‐音声が途切れた‐";
			close;
		case 11:
			mes "[？？？]";
			mes "愛の偉大さを知らないあなたは";
			mes "かわいそうです!!";
			next;
			mes "[？？？]";
			mes "……";
			close;
		case 12:
			mes "^000099‐ノイズが発生しているようだ。";
			mes "　周波数を調節して";
			mes "　もう一度利用してみよう‐^000000";
			close;
		}
	default:
		if(ECL_6QUE >= 18 && ECL_6QUE <= 32) {
			mes "^000099‐ヒエールが懸命に改良している。";
			mes "　勝手にさわらないでおこう‐^000000";
			close;
		}
		mes "^000099‐色んなガラクタが乗っている。";
		mes "　何かの作業台のようだ‐^000000";
		close;
	}
}

//============================================================
// エクラージュの悪戯キッズクエスト
//- Registry -------------------------------------------------
// ECL_7QUE -> 0～
//------------------------------------------------------------
ecl_in02.gat,160,36,4	script	アイリン#nk	441,{
	switch(ECL_7QUE) {
	case 4:
		if(checkquest(4258)) {
			mes "[アイリン]";
			mes "え？　最近本を読んだかって？";
			mes "本は大好きだよ。いつも読んでるよ。";
			mes "治療所で暇なんだもん。";
			next;
			mes "[アイリン]";
			mes "あ、そういえば最近本を一冊借りたよ。";
			mes "ミッドガルツ？　ミッドカット？";
			mes "あれ……ミッドガルド？　忘れた！";
			mes "あなたが来た場所の本よ。";
			mes "面白かったなー。";
			mes "だけどそれがどうしたの？";
			next;
			mes "[アイリン]";
			mes "セシリアったら";
			mes "いきなりどうしたのかな。";
			mes "私が本を好きなことは";
			mes "すでに分かっているはずなのにー。";
			mes "とにかくそのように伝えてね。";
			delquest 4258;
			close;
		}
		mes "[アイリン]";
		mes "セシリアったら";
		mes "いきなりどうしたのかな。";
		mes "私が本を好きなことは";
		mes "すでに分かっているはずなのにー。";
		next;
		mes "[アイリン]";
		mes "もし、他の話があったら";
		mes "また教えてね。";
		mes "どうしてそんなことを聞くのかも";
		mes "聞いて見て。";
		close;
	case 5:
	case 6:
		mes "[アイリン]";
		mes "セシリアが何かを調査している？";
		mes "そうなの？　うん？　うん？";
		mes "それでそれで？　うん？";
		mes "まだ調べてるの？　うん？";
		mes "気になる！　早く調べて！";
		close;
	case 7:
		switch(ECL_7QUE1) {
		case 0:
			mes "[アイリン]";
			mes "え！　うん、うん？";
			mes "えええ！　そういう事だったの！";
			mes "ドミニクのいたずらのせいで";
			mes "最近ずっとおなかが痛かったのね！";
			mes "ゆ、許せない！";
			next;
			mes "[アイリン]";
			mes "よぉし。仕返ししてやる！";
			mes "羽には羽を触角には触角をよ！";
			mes "ふざけた事にはふざけた事で返すのが";
			mes "私たちのルールなんだから。";
			next;
			mes "[アイリン]";
			mes "どうしよう。何したらいいかな。";
			mes "ドミニクは本を守っているんだよね。";
			mes "そしたら本棚を散らかしたら";
			mes "嫌がるかな？";
			next;
			mes "[アイリン]";
			mes "よーし！　そうしよう！";
			mes "わたしの魔法の力で";
			mes "本棚を散らかしてやる！";
			next;
			mes "[アイリン]";
			mes "ねえ、お願い。";
			mes "^FF0000植物の茎と緑ハーブを1個ずつ^000000";
			mes "持って来てくれる？";
			mes "わたし、魔法の準備するから。";
			next;
			if(select("手伝う","断る") == 2) {
				mes "[アイリン]";
				mes "えー！　そっか……。";
				mes "つめたい人だね。";
				close;
			}
			mes "[アイリン]";
			mes "ありがと！";
			mes "1個ずつだし簡単だよね。";
			mes "私はここで準備をしているから";
			mes "早くお願いね。";
			set ECL_7QUE1,1;
			setquest 4261;
			delquest 72515;
			close;
		case 1:
			if(countitem(511) < 1 || countitem(905) < 1) {
				mes "[アイリン]";
				mes "ねえ、まだ～？";
				mes "はぁ、待つの疲れた～。";
				mes "もう少し、急いでくれないかな。";
				mes "いたずらはすぐやらないと！";
				mes "^FF0000植物の茎と緑ハーブ1個ずつ^000000";
				mes "早く持ってきて～。";
				close;
			}
			if(checkitemblank() == 0) {
				mes "[アイリン]";
				mes "持ってきてくれたの？　ありがと！";
				mes "でも……";
				mes "荷物がいっぱいみたい。";
				mes "少し整理して来て！";
				close;
			}
			mes "[アイリン]";
			mes "持ってきてくれたの？　ありがと！";
			mes "こっちも準備は完了したよ。";
			mes "よーしじゃあ作るぞー。";
			mes "ふふっ。これをこうして……";
			mes "ここに緑ハーブをうまく混ぜて……";
			mes "これでよしっと！";
			delitem 511,1;
			delitem 905,1;
			set ECL_7QUE1,2;
			chgquest 4261,4262;
			getitem 6563,1;
			misceffect 305;
			next;
			mes "[アイリン]";
			mes "じゃ～ん！　出来上がり～。";
			mes "誰でも使える召喚道具！";
			mes "その名も～";
			next;
			mes "[アイリン]";
			mes "^ff0000雑草！^000000";
			next;
			mes "[アイリン]";
			mes "完成でーす！";
			next;
			menu "……雑草？",-;
			mes "[アイリン]";
			mes "そうだよ。雑草だよ！";
			mes "これを持って";
			mes "ドミニクが大事に守っている";
			mes "本棚の周辺にこっそり埋めて来て。";
			next;
			mes "[アイリン]";
			mes "毎日掃除で大変なのに";
			mes "急に本棚の隣に草が生えてきたら……";
			mes "ふふふっ！　きゃはは！";
			mes "絶対いやだよね？　ね？";
			next;
			mes "[アイリン]";
			mes "さあ、早く行ってきて！";
			mes "こういう事はすぐやらないと！";
			close;
		case 2:
			mes "[アイリン]";
			mes "ふっふー楽しみ～。";
			mes "さあ、早くドミニクの本棚に行って";
			mes "こっそり埋めて来て。";
			close;
		case 3:
			mes "[アイリン]";
			mes "あ、行ってきてくれたのね。";
			mes "ねえねえ、どうだった？";
			mes "おこってた？　やっぱりおこってた？";
			next;
			mes "[アイリン]";
			mes "あ～、勿体ないなぁ";
			mes "その場面を直接見たかったな。";
			mes "今度、私ももう一度やってみよう。";
			next;
			mes "‐…………";
			mes "　まるで効果が無かったことは";
			mes "　言わないでおこう‐";
			close;
		}
	case 8:
		mes "[アイリン]";
		mes "あ、行ってきてくれたのね。";
		mes "ねえねえ、どうだった？";
		mes "おこってた？　やっぱりおこってた？";
		next;
		mes "[アイリン]";
		mes "あ～、勿体ないなぁ";
		mes "その場面を直接見たかったな。";
		mes "今度、私ももう一度やってみよう。";
		next;
		mes "‐…………";
		mes "　まるで効果が無かったことは";
		mes "　言わないでおこう‐";
		close;
	default:
		switch(ECL_7QUE1) {
		case 0:
			if(!checkquest(72500))
				setquest 72500;
			mes "[アイリン]";
			mes "うう、うううう……";
			mes "おなかがとても痛い。";
			mes "ん。なぁに？";
			mes "じろじろ見ないで。";
			next;
			mes "[アイリン]";
			mes "うぅ……";
			mes "別に変ったものなんて";
			mes "食べていないのに";
			mes "どうしてこんなに";
			mes "おなかが痛くなるんだろう……。";
			next;
			mes "[アイリン]";
			mes "なぁに、まだそこにいるの？";
			mes "あ。そうだ！";
			mes "ちょっとお願いしてもいいかな？";
			next;
			mes "[アイリン]";
			mes "あのね。おなかに良くきくお薬を";
			mes "作ろうとしたんだけど、";
			mes "それに必要な材料がひとつ";
			mes "倉庫になかったの……。";
			next;
			mes "[アイリン]";
			mes "いっぱい買っておいたから";
			mes "まだあると思ったのに。";
			mes "だからね、緑ハーブを10個";
			mes "持ってきてくれない？";
			next;
			if(select("わかった","私がどうして？") == 2) {
				mes "[アイリン]";
				mes "じゃあなんで話かけてくるの。";
				mes "意味わかんない……。";
				close;
			}
			mes "[アイリン]";
			mes "やった！　ありがとう。";
			mes "^ff0000緑ハーブ10個^000000ね。";
			mes "う……おなかがまた……うぅ。";
			mes "あぁ……ん……あーー！　いたい！";
			mes "ねえ、エクラージュが私の声で";
			mes "いっぱいになる前にお願い！";
			set ECL_7QUE1,1;
			setquest 4254;
			close;
		case 1:
			mes "[アイリン]";
			mes "うううう、おなかが痛いよ。";
			mes "どうしてこんなタイミングで";
			mes "緑ハーブの在庫がないの……。";
			mes "絶対私買っておいたはずなのに。";
			mes "うう……うぅ……。";
			next;
			if(select("ハーブを渡す","その場を去る") == 2)
				close;
			if(countitem(511) < 10) {
				mes "[アイリン]";
				mes "ハーブ……。";
				mes "足りないよ？　10個だよ。";
				close;
			}
			mes "[アイリン]";
			mes "あ！　緑ハーブだ！";
			mes "持って来てくれてありがとう。";
			mes "じゃあわたしは";
			mes "お薬を作って飲む事にするね。";
			mes "これでおなかがよくなるといいな。";
			next;
			mes "[アイリン]";
			mes "そうそう、お薬箱を探していたらね";
			mes "わたしとは関係のないお薬が";
			mes "少し見つかったの。";
			mes "それをお礼にあげるよー。";
			next;
			delitem 511,10;
			set ECL_7QUE1,2;
			delquest 4254;
			getexp 100000,0;
			getitem 12812,1;
			getitem 12813,1;
			getitem 12814,1;
			getitem 12815,1;
			mes "[アイリン]";
			mes "この辺でとれる材料で";
			mes "作ったやつなんだって。";
			mes "すごくいいみたい。";
			mes "他の冒険家たちは喜んでいたよー。";
			close;
		case 2:
			mes "[アイリン]";
			mes "うう……ううぅ……。";
			mes "お薬を飲んだにもかかわらず";
			mes "おなかがまだ痛い……気がする……。";
			mes "これは単純な痛みではないのかな。";
			mes "もしかするとこれが……";
			next;
			mes "[アイリン]";
			mes "恋の病？";
			emotion 1;
			close;
		}
	}
OnInit:
	waitingroom "エクラージュの悪戯キッズ",0;
	end;
}

ecl_in03.gat,175,69,4	script	バルボン#nk	444,{
	switch(ECL_7QUE) {
	case 4:
		if(checkquest(4259)) {
			mes "[バルボン]";
			mes "え、何だよ突然？　本？";
			mes "本は読むよ。とても好きだ。";
			mes "特に絵の多い本が良いね。";
			mes "最近はミッドガルドに関連する本が";
			mes "大量に入って来たから読んでいたよ。";
			next;
			mes "[バルボン]";
			mes "ここエクラージュにも";
			mes "ミッドガルドから来る人が";
			mes "増えたからね。";
			next;
			mes "[バルボン]";
			mes "いやーミッドガルドも";
			mes "なかなか面白そうな場所だねえ。";
			mes "ちょっと住んでみたくはないけど、";
			mes "遊びに行きたくなったよ。";
			delquest 4259;
			close;
		}
		mes "[バルボン]";
		mes "最近エクラージュにも";
		mes "ミッドガルドから来る人が";
		mes "増えたからね。";
		next;
		mes "[バルボン]";
		mes "それで興味を惹かれたんで";
		mes "ミッドガルド関係の本は";
		mes "何冊か借りて読んだよ。";
		mes "新しい本でも出ていないかな。";
		mes "また見にいってみるかー。";
		close;
	case 5:
	case 6:
		mes "[バルボン]";
		mes "なになに？　え！　まじで？";
		mes "ということは……どういうことだ？";
		mes "謎が深まってきたね。";
		close;
	case 7:
		switch(ECL_7QUE2) {
		case 0:
			mes "[バルボン]";
			mes "な、なにぃ！　ドミニクの仕業？";
			mes "と、ということはやはり";
			mes "ドミニクとメンブリッツの";
			mes "複数犯だったという事か～。";
			next;
			menu "違います",-;
			mes "[バルボン]";
			mes "ゆ、許せないな！";
			mes "よぅし。こうなったら俺も本気を";
			mes "出すしかないようだな。";
			mes "とうとう本気を出す時が";
			mes "来てしまったようだな！";
			next;
			mes "[バルボン]";
			mes "よぉぅし。ドミニクのやつが";
			mes "一番嫌いなことを考えてみよう……。";
			mes "俺の名はバルボン";
			mes "生まれながらの天才イタズラBoy。";
			mes "なめるなよ！";
			next;
			mes "[バルボン]";
			mes "そう……そうだ！　たしかあいつは";
			mes "小さくて素早くて、カサカサしている";
			mes "茶色くて、暗いところに潜むやつが";
			mes "大嫌いと言っていたな。";
			mes "どう考えて見てもこれは……";
			next;
			mes "[バルボン]";
			mes "ネズミ……だよな？";
			next;
			menu "違うと思います",-;
			mes "[バルボン]";
			mes "いや、ネズミしか考えられないわ！";
			mes "ネズミにしよう。決定！";
			mes "だってネズミしか変換できないし。";
			mes "よぅし。ネズミを用意して";
			mes "あいつのいる場所に放ってやろう。";
			mes "ふっふっふ、名案すぎる。";
			next;
			mes "[バルボン]";
			mes "そうと決まればネズミが必要だな。";
			mes "ここにはいないんだ。取ってこないと。";
			mes "俺は準備が必要だから……";
			mes "手伝ってくれる人が……いるね、うん。";
			next;
			if(select("手伝う","断る") == 2) {
				mes "[バルボン]";
				mes "どうしてだ？　ほわーい？";
				mes "君には聞こえないかい？";
				mes "俺の心がドラムのように";
				mes "ドンドンと鳴り響いているのが。";
				mes "頼むよ！　君が必要なんだ！";
				close;
			}
			mes "[バルボン]";
			mes "そうか！　ありがとう！";
			mes "君にも俺と同じ";
			mes "イタズラの血が流れているんだね。";
			mes "血統だよ。素晴らしい。";
			next;
			mes "[バルボン]";
			mes "よし！　詳しい話はあとだ。";
			mes "^ff0000ねずみの尻尾^000000を2個";
			mes "用意して持ってきて欲しい。";
			mes "ただ、この辺りにはいないからな。";
			mes "色々あたって探してきてくれ。";
			next;
			mes "[バルボン]";
			mes "俺はその間に精神集中するから";
			mes "用意が終わるまでは、";
			mes "あまり話しかけないでくれよな！";
			mes "よろしく頼んだよ！";
			set ECL_7QUE2,1;
			chgquest 72520,4263;
			close;
		case 1:
			if(countitem(1016) < 2) {
				mes "[バルボン]";
				mes "うおぉぉ、血が、血が騒ぐ。";
				mes "イタズラの気が全身に";
				mes "湧き乱れてとまらない！";
				mes "乱れ咲くイタズラエナジー！　フォォ！";
				mes "ふぅ……まだだ……今は準備の刻。";
				mes "鎮まれ……俺のハート……。";
				next;
				menu "……",-;
				mes "[バルボン]";
				mes "あれ！　いたの君？　言ってよ～。";
				mes "今、集中してるんだよ。";
				mes "え？　かっこよかったって？";
				mes "はは。照れるな。それより……";
				mes "ねずみの尻尾まだ？";
				mes "2個だよ。宜しく頼むよ！";
				close;
			}
			mes "[バルボン]";
			mes "おお、待っていたよ！";
			mes "こっちもちょうど準備が";
			mes "すべて終わったんだ！";
			mes "さあ、早速尻尾をくれ。";
			next;
			mes "[バルボン]";
			mes "さあ、じゃあ始めよう。";
			mes "……ブツブツ……";
			next;
			mes "[バルボン]";
			mes "全知全能の小さな尻尾よ……";
			mes "お前の終わりは壮大で針小なれど";
			mes "ねずみとしての生を全うしたはずの";
			mes "神秘的な力を俺のこの右肩に献上し";
			mes "ありとあらゆる生命の力を宿して";
			next;
			mes "‐良くわからない呪文が続いている‐";
			next;
			mes "[バルボン]";
			mes "^ff0000最終的にホイ！^000000";
			misceffect 12;
			next;
			if(checkitemblank() == 0) {
				mes "[バルボン]";
				mes "よぉぅし、ってあれ？";
				mes "荷物がいっぱいだよ君！";
				mes "台無しだよ！　頼むよ！";
				mes "荷物を整理してから来てくれ。";
				close;
			}
			delitem 1016,2;
			set ECL_7QUE2,2;
			chgquest 4263,4264;
			getitem 6562,1;
			misceffect 21;
			mes "[バルボン]";
			mes "よし、できた。全部できたぜ。";
			mes "一部呪文を間違えてひやっとしたが";
			mes "最終的にうまくいったよ。";
			next;
			mes "[バルボン]";
			mes "さぁ、これを君に渡すよ。";
			mes "これをドミニクの隣に投げると";
			mes "ねずみに化けて";
			mes "やつの周りを走るだろう。";
			mes "これでイタズラは完・成！";
			mes "さっ、行った行った！";
			next;
			menu "えっ？",-;
			mes "[バルボン]";
			mes "おいおいおーい、頼むよ～！";
			mes "俺は作るのが役目だよ？";
			mes "投げるのは君の役目だろう？";
			mes "どうしたんだ急に！";
			next;
			mes "[バルボン]";
			mes "ふふ。あー楽しみだなとても！";
			mes "何しているんだい？";
			mes "早くっ！　頼むよ！";
			mes "タイムイズゼニーだよ！";
			next;
			mes "‐バルボンから無理やりいたずらの";
			mes "　手伝いを頼まれた。";
			mes "　ドミニクの元へ行ってみよう‐";
			close;
		case 2:
			mes "[バルボン]";
			mes "さあ、早くそれをもって";
			mes "ドミニクに投げつけてきてくれ。";
			mes "投げるとねずみに化けて";
			mes "奴の周辺を走りまわるはずだぜ。";
			next;
			mes "[バルボン]";
			mes "ふふふ……";
			mes "楽しみだわー！";
			mes "何してるの？　早く！　すばやく！";
			close;
		case 3:
			mes "[バルボン]";
			mes "おお、行ってきた？　どうだった？";
			mes "うまくねずみは変身したか？";
			mes "いやードミニク慌てただろうなぁ。";
			mes "あーはっは。";
			next;
			mes "[バルボン]";
			mes "手も足も出なかったでしょ。";
			mes "大嫌いって言ってたからね！";
			mes "お見通しなんだよ!!　ははっ！";
			next;
			mes "[バルボン]";
			mes "イタズラならこっちが上だという事を";
			mes "きっちりわからせないとね。";
			mes "あーすっきりした。";
			mes "愉快愉快！　ありがとな！";
			next;
			mes "‐効果が無かったことは";
			mes "　言わないでおこう……‐";
			close;
		}
	case 8:
		mes "[バルボン]";
		mes "おお、行ってきた？　どうだった？";
		mes "うまくねずみは変身したか？";
		mes "いやードミニク慌てただろうなぁ。";
		mes "あーはっは。";
		next;
		mes "[バルボン]";
		mes "手も足も出なかったでしょ。";
		mes "大嫌いって言ってたからね！";
		mes "お見通しなんだよ!!　ははっ！";
		next;
		mes "[バルボン]";
		mes "イタズラならこっちが上だという事を";
		mes "きっちりわからせないとね。";
		mes "あーすっきりした。";
		mes "愉快愉快！　ありがとな！";
		next;
		mes "‐効果が無かったことは";
		mes "　言わないでおこう……‐";
		close;
	default:
		switch(ECL_7QUE2) {
		case 0:
			if(!checkquest(72500))
				setquest 72500;
			mes "[バルボン]";
			mes "おっかしいなー。";
			next;
			menu "どうしました？",-;
			mes "[バルボン]";
			mes "いや、なんかさ";
			mes "最近なぜかわからないけど";
			mes "物がよく無くなるんだよ……。";
			mes "ポケットにあった物も";
			mes "ちゃんと整理して置いた物も。";
			next;
			mes "[バルボン]";
			mes "あっ！　もしや……。";
			mes "そういう事か！";
			mes "はいはい。";
			mes "おっけーおっけー。";
			mes "そういう事ね。";
			next;
			menu "なんですか",-;
			mes "[バルボン]";
			mes "これはきっと外にいる";
			mes "イタズラ大好きなやつらの";
			mes "仕業だよ。";
			mes "俺が外に出た時にあいつらが";
			mes "俺の物を持っていった。";
			mes "そうに違いない！";
			next;
			mes "[バルボン]";
			mes "くっそーあいつらめ。";
			mes "懲らしめてやりたいけど";
			mes "仕事中だしなぁ。";
			next;
			mes "[バルボン]";
			mes "ちょっと君さ、悪いんだけどさ";
			mes "俺のかわりに";
			mes "外にいるあいつらを";
			mes "懲らしめてくれない？";
			next;
			if(select("私がどうして？","手伝う") == 1) {
				mes "[バルボン]";
				mes "うーん、まぁそりゃそうか。";
				mes "他に暇な人を探してみるか……。";
				close;
			}
			mes "[バルボン]";
			mes "おお、本当？　ありがとう。";
			mes "じゃぁお願いするわ。";
			mes "外に出てメンブリッツを20匹";
			mes "やっつけてきてくれ。";
			mes "そうすれば奴らも懲りるだろう。";
			next;
			menu "本当にそいつらの仕業なんですか？",-;
			mes "[バルボン]";
			mes "え？　本当にあいつらかって？";
			mes "間違いないよ！　多分。";
			mes "俺の勘はたまにあたるんだ。";
			next;
			mes "[バルボン]";
			mes "メンブリッツは外に出れば";
			mes "すぐに見つかると思うから";
			mes "よろしく頼んだよ～！";
			set ECL_7QUE2,1;
			setquest 4255;
			close;
		case 1:
			if(checkquest(4255) & 0x4) {
				mes "[バルボン]";
				mes "おお、懲らしめてきてくれたか。";
				mes "よーしよし！　ありがとう！";
				mes "いやー助かったよ。";
				mes "……と言いたい所だけど";
				next;
				mes "[バルボン]";
				mes "実は解決してないんだよね。";
				mes "君がメンブリッツを";
				mes "倒しに行っている間にも";
				mes "俺が良く使っていたペンが";
				mes "無くなっちゃったんだ……。";
				next;
				menu "やっぱり違う人が犯人だったのでは",-;
				mes "[バルボン]";
				mes "これはもしかすると……";
				mes "犯人は……";
				mes "複数いる？";
				next;
				menu "いや、ただ犯人が違うだけでは……",-;
				mes "[バルボン]";
				mes "ぷっはー！　難しい！";
				mes "さすがに複数人相手は難しい！";
				mes "犯人も手がこんでるなーしかし。";
				mes "　";
				mes "おっとそうだ。お礼をしないとな。";
				next;
				mes "[バルボン]";
				mes "よし、これをあげよう。";
				mes "使ってくれ！";
				delquest 4255;
				getexp 100000,0;
				getitem 6081,2;
				set ECL_7QUE2,2;
				set ECL_7QUE3,3;
				chgquest 72500,72505;
				next;
				mes "‐3人の悩みを解決した。";
				mes "　セシリアのところへ行こう‐";
				close;
			}
			mes "[バルボン]";
			mes "メンブリッツを20匹、";
			mes "やっつけてきてね！";
			mes "メンブリッツは外に出れば";
			mes "すぐに見つかると思うから";
			mes "よろしく頼んだよ～！";
			close;
		case 2:
			mes "[バルボン]";
			mes "おかしいな……。";
			mes "やはり犯人は……複数いる？";
			mes "メンブリッツを懲らしめている間にも、";
			mes "俺が良く使っていたペンが";
			mes "無くなってしまった。";
			mes "難しい……この問題は難しい。";
			close;
		}
	}
OnInit:
	waitingroom "エクラージュの悪戯キッズ",0;
	end;
}

ecl_in01.gat,26,88,5	script	セシリア#nk	440,{
	switch(ECL_7QUE) {
	case 0:
		if(!checkquest(72500))
			setquest 72500;
		mes "[セシリア]";
		mes "うーん……どうしようかしら。";
		next;
		mes "[セシリア]";
		mes "何度見比べてみても";
		mes "やはり、数が合わないわ。";
		mes "しかも、ちょっとずつだけ足りない。";
		mes "最近、ここを訪れるものが";
		mes "増えていると聞くから、";
		mes "そいつらの仕業なのか……。";
		next;
		emotion 0;
		mes "[セシリア]";
		mes "ん？　あら！";
		mes "ちょっと～、ちょっとそこ！";
		mes "そこのあなた！　あなたよ。";
		mes "何を盗み聞きしているの？";
		mes "私が話したこと";
		mes "全部聞いていたでしょう？";
		next;
		switch(select("はい","いいえ")) {
		case 1:
			mes "[セシリア]";
			mes "素直でよろしいわ。";
			break;
		case 2:
			mes "[セシリア]";
			mes "嘘をつくんじゃない！";
			break;
		}
		next;
		mes "[セシリア]";
		mes "実はね、私が管理していた補給品が";
		mes "ちょっとずつなくなっているのよ。";
		mes "今までこんなことは無かったのに。";
		mes "どう考えても";
		mes "これは外部から来た人の仕業だ。";
		mes "そう思わない？";
		next;
		mes "[セシリア]";
		mes "いや、それでね。";
		mes "まぁ犯人が誰かはいいのよ。";
		mes "そんな事は重要ではないの。";
		next;
		menu "なるほど",-;
		mes "[セシリア]";
		mes "補給品が無くなったという事実を";
		mes "誰が知っているか、という事なのよ。";
		mes "意味わかる？　私と犯人と";
		mes "あなた。そう、あなただよね。";
		next;
		mes "[セシリア]";
		mes "だから、あなたが泥棒です！";
		mes "もうそういう事になります。";
		mes "泥棒として認定！";
		mes "はい泥棒！　この泥棒やろう！";
		next;
		mes "[セシリア]";
		mes "どろぼおおおおお!!";
		emotion 26;
		misceffect 458,"";
		next;
		menu "え？",-;
		mes "[セシリア]";
		mes "あなたは泥棒なので犯罪者です。";
		mes "あなたは法廷代理人を立てることができ";
		mes "あなたには黙秘権があります。";
		mes "また、あなたは……";
		next;
		mes "[セシリア]";
		mes "ん……まぁ、細かい事はいいか。";
		mes "つい専門用語が出てしまうのよ。";
		mes "ごめんなさいね。";
		next;
		mes "[セシリア]";
		mes "さあ、今からあなた泥棒ですけど";
		mes "今、どんなお気持ち？";
		next;
		switch(select("いきなりどうしたんですか？","……")) {
		case 1:
			mes "[セシリア]";
			mes "人生は長いでしょう。";
			mes "だから突然、身に覚えのない";
			mes "災難にみまわれたりするものです。";
			mes "あなたにとっては";
			mes "今日がその日のようね。";
			next;
			mes "[セシリア]";
			mes "さぁ、最後のチャンスだよ！";
			mes "私も鬼じゃない。";
			mes "お互いが幸せになるいい方法を";
			mes "考えてあるのよ。";
			mes "どう、一度聞いてみる？";
			break;
		case 2:
			mes "[セシリア]";
			mes "ほぉ、早速黙秘権ってやつ。";
			mes "素人じゃあないわね。";
			mes "ただ、残念だけど私もプロなの。";
			mes "お互いが幸せになるいい方法を";
			mes "用意してあるわけ。";
			mes "どう、ちょっと聞いてみる？";
			break;
		}
		next;
		if(select("いやだ！","わかった") == 1) {
			mes "[セシリア]";
			mes "なら、しょうがない。";
			mes "あなたを犯人に仕立て上げて";
			mes "私は無実っていうことにするわ！";
			mes "妖精をなめちゃいけないわよ。";
			mes "証拠なんて作ればいいし。";
			next;
			mes "[セシリア]";
			mes "さあ、証拠はゆっくり作ろ。";
			mes "3人くらい妖精がいれば";
			mes "イグドラシルでも作れるんだよ。";
			mes "観念する事だね！";
			next;
			mes "‐突然妖精に泥棒扱いされた。";
			mes "　ひとまずこの場を離れよう‐";
			close2;
			warp "eclage.gat",296,306;
			end;
		}
		mes "[セシリア]";
		mes "素晴らしい決断ね。";
		mes "話は極めてシンプルよ。";
		mes "それは……";
		next;
		mes "[セシリア]";
		mes "無くなった補給品を";
		mes "あなたが集めてくるという事。";
		mes "私は倉庫を守っているから";
		mes "勝手に動くことができないし。";
		next;
		mes "[セシリア]";
		mes "どうかしら？";
		mes "泥棒の濡れ衣をかぶるよりは";
		mes "いいんじゃないと思うけど？";
		next;
		menu "無くした品を集めればいいのですね",-;
		mes "[セシリア]";
		mes "そうそう、そうな……違うわよ！";
		mes "なくしてないし。盗まれたの！";
		mes "しかも泥棒はあなたなんですけど。";
		mes "さっき決まったでしょ？";
		mes "私はあなたの濡れ衣を晴らそうと";
		mes "親切で言ってるのよ。大体……";
		next;
		menu "品物を教えてください",-;
		mes "[セシリア]";
		mes "あっ……えっと……必要な品物は、";
		mes "^FF0000大量のどんぐり10個";
		mes "古い本のページ10個";
		mes "最後にカビの粉10個^000000";
		mes "3種類、10個ずつよ。";
		set ECL_7QUE,1;
		setquest 4256;
		next;
		mes "[セシリア]";
		mes "さて、これで私とあなたは";
		mes "同じ船に乗ったようなものね。";
		mes "これを専門用語で【共犯】っていうの。";
		next;
		mes "[セシリア]";
		mes "ちょっと難しかったかしら？";
		mes "ふふ。何でも知ってるのよ私は。";
		next;
		mes "[セシリア]";
		mes "さぁ！　気を付けて行って来て。";
		mes "3つともこの辺で入手できるはずよ。";
		close;
	case 1:
		mes "[セシリア]";
		mes "しーっ！";
		mes "誰かに見られてない？";
		mes "では、持って来た物をみせて。";
		next;
		if(countitem(6558) < 10 || countitem(1097) < 10 || countitem(7001) < 10) {
			mes "[セシリア]";
			mes "ふーよかった。これで帳尻が";
			mes "合わない……足りない……。";
			mes "足りてないわよ！　この泥棒やろう！";
			next;
			mes "[セシリア]";
			mes "必要な品物は、";
			mes "^FF0000大量のどんぐり10個";
			mes "古い本のページ10個";
			mes "最後にカビの粉10個^000000よ。";
			mes "2度と間違えないで。急いで！";
			close;
		}
		mes "[セシリア]";
		mes "ふーよかった。これで帳尻があうわ。";
		mes "思ったより優秀なのね。";
		mes "お蔭で私もあなたも助かったわ。";
		next;
		mes "[セシリア]";
		mes "まぁ、共犯だったし";
		mes "お礼は言わなくてもいいわよね。";
		next;
		mes "[セシリア]";
		mes "ありがとう。";
		next;
		mes "[セシリア]";
		mes "私はまた無くなった物がないか";
		mes "確認をしてみるわ。";
		next;
		mes "[セシリア]";
		mes "ちょうど10個ずつ消えるって";
		mes "泥棒にしろ無くしたにしろ";
		mes "ちょっとおかしいし。";
		mes "何かあったらまた手伝って。";
		delitem 6558,10;
		delitem 1097,10;
		delitem 7001,10;
		set ECL_7QUE,2;
		delquest 4256;
		getexp 300000,0;
		next;
		mes "[セシリア]";
		mes "そういえば……";
		mes "アイリンとバルボンも";
		mes "最近困ったことがあるって";
		mes "言っていたわね。";
		mes "よかったら話を聞いてあげて。";
		close;
	case 2:
		mes "[セシリア]";
		mes "おかしいな……";
		mes "しっかり整理しておいたのに、";
		mes "なぜ、散らかっているの。";
		mes "もしかして私、";
		mes "誰かに嫌われているのかな。";
		mes "普段の行いはすごい良いのに……。";
		emotion 4,"";
		next;
		mes "[セシリア]";
		mes "あら。どうしたの泥棒さん。";
		mes "アイリンとバルボンの所には";
		mes "行ってみたかしら？";
		mes "よかったら話を聞いてあげて。";
		close;
	case 3:
		mes "[セシリア]";
		mes "あら、あなた。";
		mes "アイリンとバルボンの2人に";
		mes "会ってくれたらしいじゃない。";
		next;
		mes "[セシリア]";
		mes "アイリンはお腹を痛めていた所を、";
		mes "バルボンは所持品がなくなって";
		mes "困っていた所を";
		mes "どちらも助けてくれたと聞いたけど。";
		next;
		mes "[セシリア]";
		mes "それにしてもこうも立て続けに";
		mes "些細なトラブルが起こるなんて……";
		next;
		mes "‐何かを考え込んでいるセシリア‐";
		next;
		mes "[セシリア]";
		mes "おかしい……";
		mes "根拠は無いけど……";
		mes "なにかおかしい。";
		next;
		mes "[セシリア]";
		mes "以前なかったことが起きるのは";
		mes "新しい何かがあるはずだわ。";
		next;
		mes "[セシリア]";
		mes "何か共通項……あったかな。";
		mes "あなたも考えてくれない？";
		mes "ミッドガルドから来たのよね。";
		mes "向こうの知識で……ん？";
		next;
		mes "[セシリア]";
		mes "ミッドガルド！　そうだ！";
		mes "本！　最近本を借りたわ。";
		next;
		mes "[セシリア]";
		mes "あの2人も確か本が好きだったし";
		mes "これは考えられるわ！";
		mes "ちょっとあなた。";
		mes "お願い！";
		next;
		mes "[セシリア]";
		mes "アイリンとバルボンに会って";
		mes "最近、ミッドガルド関係の本を";
		mes "借りたり読んだりしていないか";
		mes "聞いて来てみて。";
		set ECL_7QUE,4;
		set ECL_7QUE1,0;
		set ECL_7QUE2,0;
		delquest 72505;
		setquest 4257;
		setquest 4258;
		setquest 4259;
		close;
	case 4:
		if(checkquest(4258) || checkquest(4259)) {
			mes "[セシリア]";
			mes "アイリンとバルボンに会って";
			mes "最近、ミッドガルド関係の本を";
			mes "借りたり読んだりしていないか";
			mes "聞いて来てみて。";
			close;
		}
		mes "‐アイリン、バルボンと話した内容を";
		mes "　セシリアに伝えた‐";
		next;
		mes "[セシリア]";
		mes "やっぱり！";
		next;
		mes "[セシリア]";
		mes "その2人も本を借りて読んでいたのね。";
		mes "訪問者が増えたから、";
		mes "私もミッドガルドの事が知りたくて、";
		mes "ついこないだ本を借りたの。";
		next;
		mes "[セシリア]";
		mes "アイリン、バルボンと私は";
		mes "最近、本を読んだという";
		mes "共通点を持っている。";
		mes "ということは……";
		next;
		mes "[セシリア]";
		mes "やっぱり本棚を管理している";
		mes "ドミニクが怪しい！";
		mes "何かを知っているか、もしくは……。";
		mes "ちょっとドミニクの所に行って";
		mes "話を聞いてきて！";
		set ECL_7QUE,5;
		chgquest 4257,72510;
		getexp 50000,0;
		close;
	case 5:
		mes "[セシリア]";
		mes "アイリン、バルボンと私は";
		mes "最近、本を読んだという";
		mes "共通点を持っている。";
		mes "ということは……";
		next;
		mes "[セシリア]";
		mes "やっぱり本棚を管理している";
		mes "ドミニクが怪しい！";
		mes "何かを知っているか、もしくは……。";
		close;
	case 6:
		mes "[セシリア]";
		mes "あ、ドミニクの所に";
		mes "行って来てくれたの？";
		mes "どう考えても本棚を管理している";
		mes "あいつが怪しいと思うんだけど……";
		next;
		menu "ドミニクの話を伝える",-;
		mes "[セシリア]";
		mes "……";
		next;
		mes "[セシリア]";
		mes "やっぱりそう。";
		mes "あいつの仕業だったのね。";
		mes "ドミニクの奴、以前から";
		mes "怪しいなぁと思っていたのよ。";
		next;
		mes "[セシリア]";
		mes "誤解しないで。";
		mes "エクラージュの住民の大半は、";
		mes "いや、ほぼ全ての住民は";
		mes "外部からの人を差別したりはしないわ。";
		next;
		menu "泥棒扱いされました……",-;
		mes "[セシリア]";
		mes "そう……";
		mes "そんなことがあったの。";
		next;
		mes "[セシリア]";
		mes "ちょっと今大事な話をしてるから";
		mes "黙ってて！";
		emotion 23,"";
		next;
		mes "[セシリア]";
		mes "いい？";
		mes "みんな良い人たちばかりなのよ。";
		mes "ドミニクのやつが特別に";
		mes "おかしいだけなの。";
		mes "変な偏見は持たないで。お願い。";
		next;
		mes "[セシリア]";
		mes "それはそうと……";
		mes "あっちがそういう事をしてくるなら";
		mes "こっちも反撃を考える必要があるわね。";
		next;
		mes "[セシリア]";
		mes "何か計画してみようかな。";
		mes "アイリンとバルボンには";
		mes "私から連絡しておくわ。";
		mes "2人の所に一度行ってみて。";
		set ECL_7QUE,7;
		delquest 4260;
		setquest 72515;
		setquest 72520;
		getexp 100000,0;
		close;
	case 7:
		if(ECL_7QUE1 < 3 || ECL_7QUE2 < 3) {
			mes "[セシリア]";
			mes "あっちがそういう事をしてくるなら";
			mes "こっちも反撃を考える必要があるわね。";
			next;
			mes "[セシリア]";
			mes "アイリンとバルボンの計画は";
			mes "進んでいるかしら？";
			mes "もし、まだ2人に聞いてないなら";
			mes "一度行ってみて。";
			close;
		}
		mes "[セシリア]";
		mes "あなたには色々助けてもらったわね。";
		mes "何かお礼をしないと……。";
		mes "そうだ！　これまでのお礼に";
		mes "書庫の本を閲覧可能にしておくわ。";
		next;
		menu "本？",-;
		mes "[セシリア]";
		mes "そうよ。私が直接、";
		mes "上層部に許可をとっておくわ。";
		mes "ドミニクが管理する書庫の本を";
		mes "好きなだけ見る事が出来るわよ。";
		mes "どう。嬉しいでしょ？";
		next;
		if(select("嬉しい","嬉しくない") == 2) {
			mes "[セシリア]";
			mes "えっ？　嬉しすぎて怖い？";
			next;
		}
		mes "[セシリア]";
		mes "ふふ。いいのよ遠慮しないで！";
		mes "今、書庫で人気が高いのは、";
		mes "あなたが住んでいる場所、";
		mes "ミッドガルドに関する本よ。";
		next;
		mes "[セシリア]";
		mes "読んでみると面白いと思うわ。";
		mes "視線が変わると評価も変わるから。";
		mes "私たちが見ている視線で";
		mes "ミッドガルドを探訪してみて。";
		next;
		if(checkitemblank() == 0) {
			mes "[セシリア]";
			mes "お礼をしようと思ったけど";
			mes "荷物がいっぱいね。";
			mes "少し整理してから来なさい。";
			close;
		}
		mes "[セシリア]";
		mes "それと、これもあげるわ。";
		mes "嬉しいでしょ？";
		set ECL_7QUE,8;
		set ECL_7QUE1,0;
		set ECL_7QUE2,0;
		delquest 72525;
		//setquest 4265;
		//compquest 4265;
		setquest 201600;
		getitem 6081,20;
		close;
	case 8:
		mes "[セシリア]";
		mes "これからは広場の本棚にある";
		mes "本を好きなだけ見れるわよ。";
		mes "楽しい時間をエクラージュで";
		mes "過ごせると思う。";
		next;
		mes "[セシリア]";
		mes "なんだか、世話になっちゃったわね。";
		mes "色々と……本当にありがとう。";
		mes "あのね……。";
		next;
		mes "[セシリア]";
		mes "私……初めてあなたに会ったとき";
		mes "その……あなたを、";
		mes "泥棒よばわりしてしまったけど……";
		mes "正直……";
		next;
		emotion 21;
		mes "[セシリア]";
		mes "すごく、いい選択だったと思う。";
		mes "お蔭で色々助けてもらえたし。";
		next;
		emotion 9,"";
		menu "………",-;
		mes "[セシリア]";
		mes "さすが、私って感じよね。";
		mes "ありがとう泥棒さん！";
		mes "あと……ごめんね。";
		next;
		mes "[セシリア]";
		mes "さてっと！";
		mes "それじゃあ私は仕事があるから";
		mes "これ以上話しかけないでね！";
		close;
	}
OnInit:
	waitingroom "エクラージュの悪戯キッズ",0;
	end;
}

ecl_in01.gat,80,77,5	script	ドミニク#nk	445,3,3,{
	switch(ECL_7QUE) {
	case 5:
		mes "[ドミニク]";
		mes "ん。何の用です？";
		mes "エクラージュを歩き回るのを ";
		mes "止めたりはしませんが、";
		mes "私の邪魔はしないでいただけますか。";
		next;
		menu "セシリアから聞いた話をする",-;
		mes "[ドミニク]";
		mes "いたずら？　あぁ。";
		mes "くくっ。気づきましたか。";
		mes "なかなかやるじゃないですか。";
		mes "ばれてしまっちゃあしょうがない。";
		next;
		mes "[ドミニク]";
		mes "確かに、ここエクラージュの住民は";
		mes "見知らぬ者に対して偏見を持ちません。";
		mes "原則と言えるでしょう。";
		mes "いい事です。";
		mes "私だっていつも意地の悪い事を";
		mes "しているわけではありません。";
		next;
		mes "[ドミニク]";
		mes "ただし！";
		mes "今回は話が別です。";
		next;
		mes "[ドミニク]";
		mes "私はね。ミッドガルドの話が";
		mes "ここエクラージュで話題になるのが";
		mes "とても嫌なんです。不安なんですよ。";
		mes "わかりますか？";
		next;
		mes "[ドミニク]";
		mes "エクラージュはとても平和です。";
		mes "日々何不自由なく暮らしています。";
		next;
		mes "[ドミニク]";
		mes "にも関わらず、いや";
		mes "だからこそなのかもしれませんね。";
		mes "エクラージュの住民は皆、";
		mes "異国の地に興味を示しはじめている。";
		next;
		mes "[ドミニク]";
		mes "勿論、最初のうちはいいでしょう。";
		mes "こうしてあなたが訪れているように";
		mes "交流も徐々に進んでいくわけです。";
		mes "するとどうなりますか。";
		next;
		mes "[ドミニク]";
		mes "良い事ばかりではないでしょう。";
		mes "必ず、どこかで";
		mes "そう遠くない時期に";
		mes "争いの種は生まれるでしょう。";
		next;
		mes "[ドミニク]";
		mes "だから私はそんな事になる前に";
		mes "エクラージュの住民の興味を";
		mes "他に移したいと考えたんですよ。";
		next;
		mes "[ドミニク]";
		mes "そういうわけで";
		mes "ミッドガルド関連の本を借りる人に";
		mes "いたずらをしたんです。";
		mes "呪われた本なんていう噂が広まれば";
		mes "大成功だったんですけどね。";
		next;
		mes "[ドミニク]";
		mes "まぁ、どうぞ。";
		mes "話すなら話してください。";
		mes "ひとつも怖くありません。";
		mes "私は私の信じる道を歩むだけです。";
		next;
		mes "‐最近起きていたたトラブルは";
		mes "　ドミニクの仕業だったようだ。";
		mes "　セシリアに話を伝えに行こう‐";
		set ECL_7QUE,6;
		chgquest 72510,4260;
		close;
	case 6:
		mes "[ドミニク]";
		mes "どうぞ。";
		mes "話すなら話してください。";
		mes "私は私の信じる道を歩むだけです。";
		close;
	case 7:
	case 8:
		mes "[ドミニク]";
		mes "ふむ。何か胸騒ぎがするな。";
		close;
	default:
		mes "[ドミニク]";
		mes "ん。何の用です？";
		mes "エクラージュを歩き回るのを ";
		mes "止めたりはしませんが、";
		mes "私の邪魔はしないでいただけますか。";
		close;
	}
OnTouch:
	if(ECL_7QUE == 7 && ECL_7QUE2 == 2) {
		mes "‐ドミニクのそばまで来た。";
		mes "　この辺なら気づかれないだろう。";
		mes "　ねずみの尻尾を投げますか？‐";
		next;
		if(select("投げない","投げる") == 1)
			close;
		mes "‐ねずみの尻尾を投げた。";
		mes "　ボワンッ！";
		mes "　投げた瞬間、尻尾はねずみに化けた‐";
		delitem 6562,1;
		set ECL_7QUE2,3;
		chgquest 4264,72525;
		initnpctimer;
		monster "ecl_in01.gat",80,77,"ねずみ",1175,1,"ドミニク#nk::OnKilled";
		getexp 300000,0;
		next;
		mes "[ドミニク]";
		mes "おや……おぉ、これはもしや";
		mes "これがねずみという奴か。";
		mes "エクラージュにはいないはずなのに。";
		mes "来訪者の荷物にでも紛れていたのかな。";
		mes "不潔なところを好むと";
		mes "聞きましたが……。";
		next;
		mes "[ドミニク]";
		mes "ふむふむ。思ったより可愛いな。";
		mes "汚らしいかさかさした虫とは";
		mes "大違いだ。";
		mes "う～ん、珍しい物が見れたな。";
		next;
		mes "‐珍しい物が見れたと";
		mes "　喜んでいる……‐";
		close;
	}
	end;
OnKilled:
	end;
OnTimer15000:
	stopnpctimer;
	killmonster "ecl_in01.gat","ドミニク#nk::OnKilled";
	end;
}

ecl_in01.gat,79,84,0	script	#ecl_kusa	139,3,3,{
	if(ECL_7QUE == 7 && ECL_7QUE1 == 2) {
		mes "‐この辺りが草を植えるには";
		mes "　ちょうどよさそうだ‐";
		next;
		if(select("やらない","やってみる") == 1)
			close;
		mes "‐ドミニクに見つからぬように";
		mes "　用意した雑草を撒いた‐";
		delitem 6563,1;
		set ECL_7QUE1,3;
		delquest 4262;
		initnpctimer;
		monster "ecl_in01.gat",79,84,"雑草",1080,1,"#ecl_kusa::OnKilled";
		getexp 300000,0;
		next;
		mes "[ドミニク]";
		mes "ちょっと！　あなた！";
		mes "そこで何をしているんです？";
		next;
		mes "[ドミニク]";
		mes "ん？　何ですかこれは。";
		mes "草？　雑草か。";
		mes "どうしてこんなところに？";
		next;
		mes "[ドミニク]";
		mes "まあ、いいでしょう。";
		mes "元々緑の多い場所ですし、";
		mes "本に影響はないですね。";
		mes "ただ、あなた。許可も無くあまり";
		mes "うろうろしないようにお願いしますよ。";
		next;
		mes "‐雑草はきちんと芽吹いたが";
		mes "　ドミニクは気にしてないようだ‐";
		close;
	}
OnKilled:
	end;
OnTimer15000:
	stopnpctimer;
	killmonster "ecl_in01.gat","#ecl_kusa::OnKilled";
	end;
}

ecl_in01.gat,80,86,4	script	ミッドガルド探検史#book	111,{
	if(ECL_7QUE < 8) {
		mes "‐読めそうな本がある。";
		mes "　ミッドガルドに関する内容のようだ。";
		mes "　棚に手をのばしてみた‐";
		next;
		mes "[ドミニク]";
		mes "ちょっと、あなた！";
		mes "勝手に持っていかないでください！";
		mes "申し訳ないですが、ここの本は";
		mes "エクラージュ住民の方以外は";
		mes "貸し出しできませんよ。";
		close;
	}
	mes "‐読めそうな本がある。";
	mes "　ミッドガルドに関する内容のようだ。";
	mes "　棚に手をのばしてみた‐";
	next;
	mes "‐ミッドガルド探検史その1‐";
	while(1) {
		next;
		if(select("本を読む","読むのをやめる") == 2) {
			mes "‐手に取った本を本棚に戻した‐";
			close;
		}
		switch(rand(10)) {
		case 0:
			mes "モロクは魔王モロクが";
			mes "寝ていると伝えられている場所だ。";
			next;
			mes "何もない砂漠に水路、湖を作るとは";
			mes "人間らしくないセンスだ。";
			next;
			mes "かつての指導者が眠っている建物から";
			mes "モンスターが出るようになる前は";
			mes "平和な場所だったんだろう。";
			continue;
		case 1:
			mes "アルベルタはルーンミッドガッツの";
			mes "人々が、他国に旅立つために";
			mes "よく訪ねる場所だ。";
			next;
			mes "そこには多くの船が準備されていて";
			mes "これで旅行をするようだ。";
			next;
			mes "本当に人間たちの能力とは……";
			mes "失望してしまう。";
			mes "なぜワープポータルを使わないのか。";
			continue;
		case 2:
			mes "森の中にはフェイヨンという街がある。";
			mes "宮殿と呼ばれている場所らしいが";
			mes "用途はよくわからない。";
			next;
			mes "ルーンミッドガッツの首都が";
			mes "プロンテラになる前に";
			mes "使用されていた場所なのだろうか……。";
			continue;
		case 3:
			mes "ここには多くの戦士たちが";
			mes "お互いに競いあいながら";
			mes "一所懸命に走ったり、";
			mes "相撲のようなことをする場所もある。";
			next;
			mes "戦いの勝者は賞品が貰えるようだが、";
			mes "最近はあまり流行っていないらしい。";
			continue;
		case 4:
			mes "人間たちもやはり居住地の境界線には";
			mes "国境町を建てていた。";
			mes "この辺はどこも変わらないらしい。";
			mes "それがこの街、アルデバランだ。";
			next;
			mes "街の中央にある時計塔には";
			mes "時計の姿をしているモンスターが";
			mes "出没していた。";
			mes "何故、街の中にある塔で";
			mes "モンスターが出現するのかは";
			mes "調査不足で不明である。";
			next;
			mes "ただ、時計塔という名前の割には";
			mes "時計にちなんだモンスターは少ない。";
			mes "この塔について冒険者に話を聞くと";
			mes "圧倒的に砂を持った老女の話が";
			mes "多かった。「婆」というらしい。";
			continue;
		case 5:
			mes "衛星都市イズルード。";
			mes "プロンテラの玄関口のような場所だ。";
			mes "人間は空を飛べないので";
			mes "大きな箱、船と呼ばれる物で移動する。";
			next;
			mes "船と呼ばれる大きな箱が";
			mes "彼らの文明発展に大きな貢献を";
			mes "果たしているようだ。";
			mes "真偽のほどは定かではない。";
			continue;
		case 6:
			mes "マジシャンの集う街、ゲフェン";
			mes "中央にある塔が特徴的だ。";
			next;
			mes "街の中央にシンボルを建てるのが";
			mes "流行っているのだろうか……。";
			mes "プロンテラには噴水が、";
			mes "アルデバランには時計塔が、";
			mes "ゲフェンにはタワーがある。";
			next;
			mes "やはり人間たちの都市計画には";
			mes "センスが不足していると考えられる。";
			continue;
		case 7:
			mes "ルーンミッドガッツの首都プロンテラ";
			mes "ここは綿密な計画で建てられた";
			mes "綺麗な建物がたくさんある。";
			next;
			mes "ここには彼らが「王」と呼んでいる";
			mes "指導者が住んでいるようだ。";
			continue;
		case 8:
			mes "プロンテラには超人的な力を";
			mes "持った人が住んでいるようだ";
			mes "特別な注意が必要らしい。";
			next;
			mes "彼は、ただ一本のハンマーを使用して";
			mes "どんな武器、防具でも数回叩くだけで";
			mes "破壊してしまうとの事だ。";
			mes "恐ろしい力の持ち主である。";
			next;
			mes "それでも冒険家たちは";
			mes "自身の装備を持って";
			mes "彼のもとを訪れるらしい。";
			mes "信じられないことである。";
			continue;
		case 9:
			mes "ルーンミッドガッツは";
			mes "東に海、南に砂漠、中央に森、北に山";
			mes "が、それぞれある。";
			next;
			mes "正確な表現ではないが、";
			mes "おそらく子供が絵を描けば";
			mes "おおむねこう描くだろう。";
			next;
			mes "一見非常にバランスのいい感じはあるが";
			mes "大陸として住みやすいかというと";
			mes "どうもそのようには感じられない。";
			mes "住み慣れた故郷と";
			mes "比べてしまうからだろうか。";
			continue;
		}
	}
}

ecl_in01.gat,82,84,4	script	ミッドガルド探検史#book	111,{
	if(ECL_7QUE < 8) {
		mes "‐読めそうな本がある。";
		mes "　ミッドガルドに関する内容のようだ。";
		mes "　棚に手をのばしてみた‐";
		next;
		mes "[ドミニク]";
		mes "ちょっと、あなた！";
		mes "勝手に持っていかないでください！";
		mes "申し訳ないですが、ここの本は";
		mes "エクラージュ住民の方以外は";
		mes "貸し出しできませんよ。";
		close;
	}
	mes "‐読めそうな本がある。";
	mes "　ミッドガルドに関する内容のようだ。";
	mes "　棚に手をのばしてみた‐";
	next;
	mes "‐ミッドガルド探検史その2‐";
	while(1) {
		next;
		if(select("本を読む","読むのをやめる") == 2) {
			mes "‐手に取った本を本棚に戻した‐";
			close;
		}
		switch(rand(10)) {
		case 0:
			mes "人間は、不確定な未来に身を委ね";
			mes "結果に一喜一憂しながらも";
			mes "その事に対して";
			mes "喜びを感じる場合があるらしい。";
			next;
			mes "そんな人が集まる場所がここ";
			mes "コモドである。";
			continue;
		case 1:
			mes "長い歴史でいくつもの文明を";
			mes "築きあげてきた人間たち。";
			mes "ところが、彼らの知識は";
			mes "積もるものではなく、";
			mes "興味が移るだけのようだ。";
			next;
			mes "彼らは既に、それぞれの木、草を";
			mes "見分けられなくなっている。";
			next;
			mes "そうでなければ、普通の森を";
			mes "迷宮の森などと呼ぶわけがない！";
			mes "自分たちが迷うからといって";
			mes "森に変な名前を付けるとは！";
			continue;
		case 2:
			mes "私たち妖精がミッドガルドに来る事で";
			mes "言語を扱えるのは人間に限らない事を";
			mes "伝えられると思っていた。";
			mes "また、この事実は大変な驚きと衝撃を";
			mes "もたらすだろうとも考えていた。";
			next;
			mes "ところがである。";
			mes "既に2本足で立つわけのわからない猫が";
			mes "人間社会にうまく馴染んで";
			mes "生活をしている。";
			mes "そればかりか逞しくもその猫達は";
			mes "商売まで営んでいる。なんという事だ。";
			next;
			mes "私の知らない何かがある……。";
			continue;
		case 3:
			mes "ここミッドガルド大陸の南方には";
			mes "コモド以外に町はない。";
			mes "いったい、何のために";
			mes "ファロス燈台島は";
			mes "存在しているのだろう？";
			next;
			mes "訪れてみたものの";
			mes "普通の船員がいるだけで、";
			mes "政治組織や反社会集団などが";
			mes "存在する情報は入手できなかった。";
			mes "ただ、何かありそうな気がする。";
			mes "追って詳しく調査をしてみたい。";
			continue;
		case 4:
			mes "まずは人間のチャレンジ精神に";
			mes "敬意を表して、この町の記録を書く。";
			next;
			mes "巨大な木がひとつの町になったウンバラ";
			mes "ここには、様々な理由で";
			mes "高い木から飛び降りる人がいる。";
			mes "しかも信じられないことに";
			mes "何回も何回も飛び降りるのである。";
			next;
			mes "いったいどういうことだろうか。";
			mes "木から飛び降りる行為は";
			mes "男性にとって成人の証明であると";
			mes "聞いていたのだが……。";
			mes "他の理由があるのだろうか。";
			continue;
		case 5:
			mes "プロンテラのような大都市では";
			mes "資源の確保が重要だ。";
			next;
			mes "人間は水が無いと3日ともたないという";
			mes "弱い存在のため、特に水源の確保は";
			mes "重要視されているようである。";
			next;
			mes "そこで上下水道施設として、";
			mes "巨大な建築物を建てたようなのだが……";
			next;
			mes "何故入り口が都市内部にないんだ？";
			mes "面倒くさいだけじゃないのか……？";
			mes "建築構造上の問題なのか、";
			mes "保安上の意図でこのようになったのか、";
			mes "人間の行動は理解しづらいものが多い。";
			continue;
		case 6:
			mes "コモドは歓楽と海岸の都市、";
			mes "色んな遊びがある場所だというが……";
			mes "今はあまりそういう雰囲気はない。";
			next;
			mes "この町には人々から崇められる";
			mes "女性も存在するようだ。";
			next;
			mes "人々は彼女に";
			mes "ダイヤモンドという宝石を捧げる。";
			mes "女性はお礼として";
			mes "神からのプレゼントを与える。";
			mes "ただし、本当に欲しい";
			mes "プレゼントを貰えるのは";
			mes "運に恵まれた人のみのようだ。";
			continue;
		case 7:
			mes "私は今日、衝撃的な事実を目撃した。";
			mes "こんな事が許されるのだろうか。";
			next;
			mes "プロンテラからほどない場所にある";
			mes "修道院。神の道に進もうとする";
			mes "若者たちが訪れる地である";
			next;
			mes "なんとここでは、";
			mes "神道を目指す若者を騙して";
			mes "延々とキノコ採取をさせたり、";
			mes "走らせたりしているようだ……。";
			mes "信じられない事である。";
			continue;
		case 8:
			mes "巨大な城の遺跡、グラストヘイム。";
			next;
			mes "ここがどうしてこのようになったか、";
			mes "何の事情があったのかは";
			mes "まだ明らかになっていない。";
			next;
			mes "現在では10種類を超える数多くの";
			mes "モンスターの棲み処となっている。";
			mes "それより……";
			next;
			mes "今、自分はどの辺りにいるのか";
			mes "誰か教えてくれないものか……。";
			continue;
		case 9:
			mes "イズルードから船に乗った先、";
			mes "バイラン島の地下には洞窟が存在する。";
			next;
			mes "島の地下に";
			mes "あのように長い洞窟が存在するのは";
			mes "神秘としか言いようがない。";
			mes "洞窟の先には神殿や都市などが";
			mes "現在も発見され続けているという。";
			mes "古代の文明か何かだろうか。";
			continue;
		}
	}
}

ecl_in01.gat,83,84,4	script	ミッドガルド探検史#book	111,{
	if(ECL_7QUE < 8) {
		mes "‐読めそうな本がある。";
		mes "　ミッドガルドに関する内容のようだ。";
		mes "　棚に手をのばしてみた‐";
		next;
		mes "[ドミニク]";
		mes "ちょっと、あなた！";
		mes "勝手に持っていかないでください！";
		mes "申し訳ないですが、ここの本は";
		mes "エクラージュ住民の方以外は";
		mes "貸し出しできませんよ。";
		close;
	}
	mes "‐読めそうな本がある。";
	mes "　ミッドガルドに関する内容のようだ。";
	mes "　棚に手をのばしてみた‐";
	next;
	mes "‐ミッドガルド探検史その3‐";
	while(1) {
		next;
		if(select("本を読む","読むのをやめる") == 2) {
			mes "‐手に取った本を本棚に戻した‐";
			close;
		}
		switch(rand(10)) {
		case 0:
			mes "坂に作られた町、ベインスは";
			mes "かなりうまく設計されている。";
			next;
			mes "入り乱れる高低差を巧みに利用して";
			mes "生活空間を確保しているようだ。";
			next;
			mes "ただ、行きたい場所に";
			mes "思うように行けないのは";
			mes "非常にいらいらする。";
			continue;
		case 1:
			mes "田園都市であるフィゲルは";
			mes "まるで南部地域のコモドのようだ。";
			next;
			mes "数多くのミニゲームがありながら、";
			mes "町の風景が牧歌的で癒される。";
			next;
			mes "ただ、あのような娯楽施設は";
			mes "国の中心にあるべきだと思うが……。";
			continue;
		case 2:
			mes "アインブロックは";
			mes "機械がメインになっている都市だ。 ";
			next;
			mes "立ち並ぶ工場でいったい何が";
			mes "生産されているのだろう。";
			mes "そして何のために人々は";
			mes "働いているのだろう。";
			next;
			mes "文明の発展は必ずしも";
			mes "豊かな人生には繋がらない。";
			mes "足るを知る。という言葉を";
			mes "彼らに捧げたい。";
			continue;
		case 3:
			mes "アルナベルツ地域の";
			mes "何処かにとても暑い場所が";
			mes "あるらしい……。";
			next;
			mes "内部の熱気で私の羽が";
			mes "全部燃やされそうだ。";
			mes "しかもそこの住民は";
			mes "友好的ではないらしい。";
			next;
			mes "以上の理由で";
			mes "この地の探査は中断するしかなかった。";
			mes "これを読んでいるあなたたちも";
			mes "近づかないよう注意されたし。";
			next;
			mes "ガーディアンが怖いわけでは";
			mes "ない。";
			continue;
		case 4:
			mes "アルナベルツの首都、ラヘルには";
			mes "小さくて白い姿をしていて";
			mes "プニョプニョしてカワイイ生物がいる。";
			next;
			mes "シロマを想像したあなたは間違ってる。";
			mes "マーリンでもない。";
			next;
			mes "正解は指導者と祭司の女の子だ。";
			continue;
		case 5:
			mes "アインブロックで列車に乗ると";
			mes "アインベフという町へ行ける。";
			next;
			mes "私にとって列車は";
			mes "最も嫌いな交通手段だが";
			mes "低価格の為、人間には便利そうだ。";
			next;
			mes "ただ……空気が悪すぎる。";
			mes "生き物の住む場所ではない……。";
			continue;
		case 6:
			mes "リヒタルゼンには研究者たちが建てた";
			mes "巨大な建物がある。";
			mes "その中で何をしているかは";
			mes "外からはうかがい知れないが、";
			mes "どうも良くない噂もあるようだ。";
			next;
			mes "この街ではとても";
			mes "貧富の差が激しいように見える。";
			mes "そのあたりに何か、問題の原因が";
			mes "潜んでいたりするのだろうか……。";
			continue;
		case 7:
			mes "ジュノーという都市は空に浮いている。";
			mes "素晴らしい力ではないか。";
			next;
			mes "そしてここでは迷路を脱出できた人に";
			mes "新しい力を提供する場所があるようだ。";
			next;
			mes "人間たちの力は本当に未知数だ。";
			mes "空に大地を浮かす力があると思えば";
			mes "新しい力の解放に";
			mes "わけのわからない迷路が必要となる。";
			continue;
		case 8:
			mes "いよいよ人間たちは";
			mes "船を水上で使う事に飽き足らず";
			mes "空の上での利用も開始したようだ。";
			next;
			mes "いったい次は何処にいくんだ？";
			mes "地面の下？　時間と空間を超越？";
			next;
			mes "いずれ過去に旅行して来るなんて事が";
			mes "当たり前になるのかもしれない。";
			mes "人類の技術発展には注意が必要だ。";
			continue;
		case 9:
			mes "アウドムラ草原には";
			mes "多くの食虫植物と小動物が住んでいる。";
			next;
			mes "人を見かけると襲ってくるので";
			mes "小動物だと油断しないほうがいい。";
			next;
			mes "万が一彼らが肉食だとしたら";
			mes "何を食べて生きているんだろう？";
			continue;
		}
	}
}

ecl_in01.gat,83,81,4	script	ミッドガルド探検史#book	111,{
	if(ECL_7QUE < 8) {
		mes "‐読めそうな本がある。";
		mes "　ミッドガルドに関する内容のようだ。";
		mes "　棚に手をのばしてみた‐";
		next;
		mes "[ドミニク]";
		mes "ちょっと、あなた！";
		mes "勝手に持っていかないでください！";
		mes "申し訳ないですが、ここの本は";
		mes "エクラージュ住民の方以外は";
		mes "貸し出しできませんよ。";
		close;
	}
	mes "‐読めそうな本がある。";
	mes "　ミッドガルドに関する内容のようだ。";
	mes "　棚に手をのばしてみた‐";
	next;
	mes "‐ミッドガルド探検史その4‐";
	while(1) {
		next;
		if(select("本を読む","読むのをやめる") == 2) {
			mes "‐手に取った本を本棚に戻した‐";
			close;
		}
		switch(rand(8)) {
		case 0:
			mes "アルベルタからは";
			mes "以下のような場所に行く事が出来た。";
			next;
			mes "神の国アマツ、楽園のようなコンロン、";
			mes "武術の達人がいるという龍ノ城、";
			mes "大きな彫刻があるアユタヤなどなど。";
			next;
			mes "現在も絶え間なく各国から";
			mes "外交員が連絡を取りに来ているらしい。";
			mes "これからもっと多くの地域に";
			mes "行けるようになっていくのだろう。";
			continue;
		case 1:
			mes "この大陸で信じる神のうち";
			mes "最も有名なのはオーディンのようだ。";
			mes "オーディンを崇めている";
			mes "神殿が存在する。";
			next;
			mes "せっかくなので私も訪れてみたが、";
			mes "とても冷たく扱われた。";
			mes "かなしい。";
			continue;
		case 2:
			mes "アルベルタから船に乗ると";
			mes "色んな場所に辿り着くことができる。";
			next;
			mes "もう少し分散してもいいと思うのだが";
			mes "利便性を考えての事かもしれない。";
			mes "おかげで便利に使う事が出来る。";
			continue;
		case 3:
			mes "ベインスの下方に渡し場がある。";
			mes "最初私は、ここにある船が";
			mes "どこに向かうのか分からなかった。";
			next;
			mes "そこで隠れて様子を見ていたところ";
			mes "衝撃的なものを目撃してしまった……。";
			next;
			mes "政治的な問題に";
			mes "巻き込まれる可能性があるので、";
			mes "話はこれで終わらせたいと思う。";
			continue;
		case 4:
			mes "アルベルタから行ける場所の中には";
			mes "難破船まである。";
			next;
			mes "すでにあの船は怪しい者達に";
			mes "占領されている。";
			continue;
		case 5:
			mes "時計塔のある街で";
			mes "1年中、赤く分厚い服を着ている";
			mes "ヒゲの長いお爺さんがいる。";
			mes "彼に頼むと年中雪の降り積もる街に";
			mes "行くことが出来る。";
			next;
			mes "ここは雰囲気が最高によかった。";
			mes "何故、白という色は";
			mes "あんなにも美しいのだろう。";
			mes "全てを呑み込むようでいて";
			mes "他の全てを強調する。";
			next;
			mes "この日記も続けていると飽きてくる。";
			mes "たまには美しい白いページがあっても";
			mes "いいんじゃないだろうか。";
			continue;
		case 6:
			mes "船に乗って行ける場所の中で、";
			mes "有名なバカンス地があるようだ。";
			next;
			mes "ただ、一人では行かないほうが";
			mes "いいらしい。酒場のマスターが";
			mes "泣きながら教えてくれた。";
			continue;
		case 7:
			mes "アルベルタから行ける場所の中に";
			mes "カメが大量に出没するという島がある。";
			next;
			mes "定期船があるわけではないが、";
			mes "あきらめない調査の末、";
			mes "そこに送ってくれる船長がいる事実を";
			mes "知る事ができた。";
			next;
			mes "実際に行って見ると";
			mes "冷たいカメ、熱いカメ、忍者カメなど";
			mes "見たこともないカメがたくさんいた。";
			mes "そもそも亀ははじめてみた。";
			continue;
		}
	}
}

ecl_in01.gat,82,78,4	script	雑誌#01	111,{
	if(ECL_7QUE < 8) {
		mes "‐読めそうな本がある。";
		mes "　ミッドガルドに関する内容のようだ。";
		mes "　棚に手をのばしてみた‐";
		next;
		mes "[ドミニク]";
		mes "ちょっと、あなた！";
		mes "勝手に持っていかないでください！";
		mes "申し訳ないですが、ここの本は";
		mes "エクラージュ住民の方以外は";
		mes "貸し出しできませんよ。";
		close;
	}
	mes "月刊ルーンミッドガッツ10月号";
	next;
	mes "特集！　プロンテラの有名人！";
	mes "独占インタビューに成功!!";
	next;
	if(select("続けて読む","読むのをやめる") == 2)
		close;
	mes "[記者]";
	mes "みなさん、こんにちは。";
	mes "今日のインタビューは";
	mes "10年という長い期間、";
	mes "冒険者の装備を精錬し続け、";
	mes "現在もなお現役である精錬の達人";
	mes "ホルグレン先生です！";
	next;
	mes "[記者]";
	mes "いや、楽しみですね～。";
	mes "よろしくお願いします。";
	mes "こんにちは！　ホルグレン先生！";
	next;
	mes "[ホルグレン]";
	mes "はい、こんにちは。";
	next;
	mes "[記者]";
	mes "では、さっそくの質問です。";
	mes "10年以上の間、";
	mes "精錬を続けてきている先生ですが、";
	mes "精錬を始めた理由は何ですか？";
	next;
	mes "[ホルグレン]";
	mes "うん。小さい頃プールに行った時だ。";
	mes "泳ぎ方もまだよくわからないのに";
	mes "水に良く浮いたんだよ。";
	mes "その時だね。あ、これは才能あるなと。";
	next;
	mes "[ホルグレン]";
	mes "それがきっかけで、";
	mes "精錬をするようになったんだ。";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "[記者]";
	mes "ん……？ええと、";
	mes "水に良く浮いたから？";
	mes "えっ!???";
	mes "水に浮くのは普通ですし、";
	mes "それに、今聞いているのは";
	mes "精錬を始めた理由ですよ？";
	next;
	mes "[ホルグレン]";
	mes "あなたは水の中で精錬をしたことが";
	mes "ありますか？";
	mes "したことないなら分からないだろう。";
	mes "まったく……！";
	next;
	mes "[記者]";
	mes "えええ？　いや……は、はい。";
	next;
	mes "[記者]";
	mes "確かに精錬はした事がありませんし";
	mes "水の中ならなおさらです。";
	next;
	mes "[記者]";
	mes "そうですか……。";
	mes "何か先生にしかわからない";
	mes "天啓があった、と";
	mes "いう事なんでしょうかね……。";
	next;
	mes "[記者]";
	mes "う、う～ん。、";
	mes "常人離れした感覚が窺えます。";
	mes "と、とりあえず、";
	mes "次の質問に移りましょう。";
	next;
	mes "[記者]";
	mes "噂では凄い特技を";
	mes "持っていると聞いたのですが、";
	mes "それはなにか教えてもらえますか？";
	next;
	mes "[ホルグレン]";
	mes "うん。";
	mes "私は目を閉じて精錬ができるんだ。";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "[記者]";
	mes "はい？";
	mes "いやいやいや！";
	mes "だから壊れるのではありませんか？";
	mes "何してるんですか？";
	next;
	mes "[ホルグレン]";
	mes "うるさい！";
	mes "あなたは、目を閉じて精錬をしたことが";
	mes "ありますか？";
	mes "したことないなら分からないだろう。";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "[記者]";
	mes "えええ！　ちょっと！";
	mes "いや、した事はないですけど……。";
	mes "ううん。特技……特技ですか。";
	mes "はぁ。";
	next;
	mes "[記者]";
	mes "先生のもとへ希望を抱いて訪れる";
	mes "冒険者の皆さんに";
	mes "このような内容をお送りして";
	mes "いいものか……疑問が残りますが、";
	next;
	mes "[記者]";
	mes "時間もありますので";
	mes "この辺で一度、実際に精錬を、";
	mes "見せていただきたいと思います。";
	mes "お願いします。";
	next;
	mes "[記者]";
	mes "それでは先生、まず最初は";
	mes "こちらのナイフからいきますか？";
	next;
	mes "[ホルグレン]";
	mes "ナイフか……。";
	mes "今日は駄目だ。";
	mes "せっかくのインタビューだろう。";
	mes "最低でもレベル4武器じゃないと。";
	next;
	mes "[記者]";
	mes "えっ、先生？　どうしたんですか。";
	mes "お願いします。";
	mes "冗談ですよね？";
	next;
	mes "[ホルグレン]";
	mes "私は冗談が嫌いだ！";
	mes "おい、なんだ！";
	mes "+9錐を持っているじゃないか。";
	mes "良い武器じゃないか。";
	mes "よし。+10にしてやろう。";
	mes "さぁ、渡してみな。";
	next;
	mes "[記者]";
	mes "いやいや、先生これは……あ！";
	mes "ちょっと！　ちょっと待ってください。";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "‐カン！　カン！　カン!!‐";
	mes "[ホルグレン]";
	mes "クホホホホ……";
	next;
	mes "[記者]";
	mes "ああああ！";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "[ホルグレン]";
	mes "はははは、今日は調子が悪いのかな。";
	mes "そうか！　今日は日曜日だよな？";
	mes "日曜日は武器精錬が";
	mes "うまくいかない日だという事を";
	mes "すっかり忘れていたよ。";
	mes "防具だ。防具なら大丈夫。";
	next;
	mes "‐記者の鎧を脱がすホルグレン‐";
	next;
	mes "[ホルグレン]";
	mes "中々よい防具じゃないか。";
	mes "+6ハイリスクヴァルキリーアーマーか";
	mes "ただ、+7の方が縁起が良いな。";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "‐カン！　カン！　カン!!‐";
	mes "[ホルグレン]";
	mes "クホホホホ……";
	next;
	mes "[記者]";
	mes "ああ！　何してるんですか！";
	mes "あああ。大切な……鎧が……。";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "[ホルグレン]";
	mes "なんだ。今日は偶数の日か。";
	mes "そういう事か。おかしいと思ったよ。";
	mes "今日みたいな日は鎧は駄目なんだ。";
	mes "そう、こういう日は靴がいいんだ。";
	mes "靴。くっくだよ。";
	mes "君、早く脱ぎなさい。";
	next;
	mes "[記者]";
	mes "あっ……ちょっと！";
	next;
	mes "‐強引に記者の靴を脱がす、";
	mes "　ホルグレン‐";
	next;
	mes "[ホルグレン]";
	mes "よしっと。";
	mes "ん？";
	mes "おいおいおい。";
	mes "+8鈍化の黒革のブーツとはなんだ。";
	mes "何故+8なんだ？　意味が分からん。";
	mes "仕方ない。ちょっと待っていろ。";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "‐カン！　カン！　カン!!‐";
	mes "[ホルグレン]";
	mes "さあ、出来上がったよ！";
	mes "久々に良い物ができた。";
	mes "武具が強くなって君も嬉しいだろ？";
	next;
	mes "[記者]";
	mes "おお！";
	mes "おお！　まさか成功するとは！";
	mes "それじゃ早速……";
	next;
	mes "[ホルグレン]";
	mes "何を言ってるんだ？";
	mes "まだ後1回残っているだろう。";
	mes "何故妥協するんだ！";
	mes "+9鈍化の黒革のブーツなんて";
	mes "既にいくつもあるだろう!!";
	mes "一番を目指せよ！　諦めるなよ！";
	next;
	mes "[記者]";
	mes "いえ、もう充分です。";
	mes "充分ですって！　ああ！";
	mes "待って!!!!!";
	mes "おい、ホルグレン！";
	mes "待てこら！　待って！　お願い！";
	mes "おい!!!!!!!!　ああああ！";
	next;
	mes "[ホルグレン]";
	mes "クホホホホ……";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "[記者]";
	mes "ああ……ああ……";
	mes "装備が……装備が……";
	next;
	mes "[ホルグレン]";
	mes "はは。はは……そうだな……。";
	mes "そうだ……あれ？　そうだ！";
	mes "今日は大事な約束があったよ。";
	mes "今日は大事な約束が";
	mes "あったよ！";
	next;
	mes "[ホルグレン]";
	mes "いや、急にすまないね。";
	mes "インタビューはここまでにしよう。";
	next;
	if(select("続けて読む","やめる") == 2)
		close;
	mes "　事情により";
	mes "　インタビューが中断致しましたこと";
	mes "　お詫び申し上げます。";
	mes "　‐編集部一同‐";
	close;
}

//============================================================
// ラフィネ流ガーデニングクエスト
//- Registry -------------------------------------------------
// ECL_8QUE -> 0～
//------------------------------------------------------------
ecl_fild01.gat,190,93,5	script	フィリー	617,{
	switch(ECL_8QUE) {
	case 0:
		if(ECL_2QUE < 2) {	// 夢見る作家クエスト非受託
			mes "[フィリー]";
			mes "この美しい草原を見てくれ。";
			mes "小さい葉、木の枝ひとつひとつが";
			mes "歌っているのが聞こえないか。";
			close;
		}
		mes "[フィリー]";
		mes "この美しい草原を見てくれ。";
		mes "小さい葉、木の枝ひとつひとつが";
		mes "息をしているんだ。";
		next;
		mes "[フィリー]";
		mes "ただ、どういうわけか";
		mes "最近、元気がないみたいなんだ。";
		mes "そこで小さなラフィネたちを集めて";
		mes "大地に歌を聞かせたり";
		mes "水を撒いたりしているんだ。";
		next;
		mes "[フィリー]";
		mes "ラフィネの仕事に興味があるなら";
		mes "もう一度話しかけてくれ。";
		set ECL_8QUE,1;
		setquest 72450;
		close;
	case 1:
		mes "[フィリー]";
		mes "私はラフィネのフィリーという。";
		mes "エクラージュで働いているんだ。";
		mes "……キミは、冒険者のようだね。";
		next;
		mes "[フィリー]";
		mes "ラフィネの仕事に興味があるのかい？";
		mes "もしよければ、私たちの仕事を";
		mes "手伝ってくれないか？";
		next;
		if(select("引き受ける","断る") == 2) {
			mes "[フィリー]";
			mes "そうなのか……残念だ。";
			mes "気が変わったら、また来てくれ。";
			close;
		}
		mes "[フィリー]";
		mes "キミに頼みたいのは";
		mes "とても簡単なことさ。";
		mes "草原にいるラフィネたちに";
		mes "今日の作業を始めるように";
		mes "伝えてくれ。";
		next;
		mes "[フィリー]";
		mes "この草原では、ラフィネたちが";
		mes "歌い、踊り、水をやり、";
		mes "独自の方法で木と草と風";
		mes "そして土に力を与えているんだ。";
		next;
		mes "[フィリー]";
		mes "元々は私ひとりでやっていた";
		mes "仕事なのだが、";
		mes "肩を怪我してしまって";
		mes "今は他のラフィネたちに";
		mes "やってもらっているんだ。";
		next;
		mes "[フィリー]";
		mes "4人のラフィネが";
		mes "草原にいるはずだ。";
		mes "地図に印をつけておくから、";
		mes "そこに行ってくれ。";
		mes "それでは、頼んだよ。";
		set ECL_8QUE,2;
		delquest 72450;
		setquest 72465;
		setquest 13051;
		setquest 13052;
		setquest 13053;
		setquest 13054;
		viewpoint 1,222,290,0,0xFF0000;
		viewpoint 1,83,263,1,0xFF0000;
		viewpoint 1,163,196,2,0xFF0000;
		viewpoint 1,237,181,3,0xFF0000;
		close;
	case 2:
		if(checkquest(13051) || checkquest(13052) || checkquest(13053) || checkquest(13054)) {
			mes "[フィリー]";
			mes "作業を行うラフィネは4名いる。";
			mes "全員に作業を始めるよう";
			mes "伝えてくれ。";
			next;
			mes "[フィリー]";
			mes "みんな草原のどこかで";
			mes "準備しているはずさ。";
			viewpoint 1,222,290,0,0xFF0000;
			viewpoint 1,83,263,1,0xFF0000;
			viewpoint 1,163,196,2,0xFF0000;
			viewpoint 1,237,181,3,0xFF0000;
			close;
		}
		mes "[フィリー]";
		mes "どうやら、みんな作業を";
		mes "始めたようだね。";
		mes "草原が息を吹き返しているよ。";
		mes "この草原にはたくさんの";
		mes "物語があるんだ。";
		next;
		mes "[フィリー]";
		mes "花と木とラフィネを";
		mes "愛する心があるなら、";
		mes "どこかで話を聞けるかもしれないよ。";
		next;
		if(checkitemblank() == 0) {
			mes "[フィリー]";
			mes "お礼をしようと思ったけど";
			mes "それ以上持てないようだね。";
			mes "アイテムの種類数を減らしてから";
			mes "また来てくれ。";
			close;
		}
		mes "[フィリー]";
		mes "今日の作業は終了だな。";
		mes "ありがとう！";
		mes "……もしよければ、";
		mes "^FF0000もうひとつ、手伝ってもらいたい";
		mes "作業があるから、";
		mes "もう一度、話しかけてくれないか？^000000";
		set ECL_8QUE,3;
		delquest 72465;
		setquest 72490;
		setquest 201580;
		getitem 6081,1;
		getexp 300000,0;
		getexp 0,300000;
		close;
	case 3:
		mes "[フィリー]";
		mes "このビフロストタワーは";
		mes "遥かな昔からあったという。";
		next;
		mes "[フィリー]";
		mes "いつからかモンスターが棲みつき";
		mes "出入りを禁じたのだが……";
		next;
		mes "[フィリー]";
		mes "旅人たちは危険だと聞くと";
		mes "余計に入りたがるようだ。";
		emotion 54;
		next;
		mes "[フィリー]";
		mes "この前も^FF00003名の冒険者^000000が";
		mes "ビフロストタワーに入っていった。";
		mes "いつまで経っても";
		mes "出てくる気配がないのだ……。";
		next;
		mes "[フィリー]";
		mes "強く引き留めなかったことを";
		mes "悔やんでいる……。";
		mes "彼らが無事なのか、";
		mes "見に行ってくれないか？";
		next;
		if(select("任せてください！","今は無理です") == 2) {
			mes "[フィリー]";
			mes "そうか。";
			mes "もし気が変わったら";
			mes "また来てくれ。";
			close;
		}
		mes "[フィリー]";
		mes "頼もしいね。";
		mes "ビフロストタワーに入った";
		mes "冒険者は3名いる。";
		next;
		mes "[フィリー]";
		mes "1人は少し前に入ったばかりだ。";
		mes "まだあまり遠くまで";
		mes "行ってないと思う。";
		next;
		mes "[フィリー]";
		mes "2人目の冒険者は";
		mes "真面目そうなお嬢さんだった。";
		mes "無事かどうか気になっている。";
		next;
		mes "[フィリー]";
		mes "3人目の冒険者が問題だ。";
		mes "……何をしているのかわからないが";
		mes "中に入って1か月ほど経っているんだ。";
		next;
		mes "[フィリー]";
		mes "楽器を持って一曲作ってくると";
		mes "言っていたのだが……";
		mes "頼む、探してくれ。";
		set ECL_8QUE,4;
		delquest 72490;
		setquest 72470;
		setquest 13056;
		setquest 13057;
		setquest 13058;
		close;
	case 4:
		if(!checkquest(72455)) {
			mes "[フィリー]";
			mes "ビフロストタワーから";
			mes "出てこない冒険者が3人いる。";
			mes "全員の安否を確認してくれ。";
			close;
		}
		mes "[フィリー]";
		mes "全員が無事で安心したよ。";
		mes "しかし、いつになったら";
		mes "出てくるつもりなんだ……？";
		mes "何か言ってなかったかい？";
		next;
		menu "具体的には何も……",-;
		mes "[フィリー]";
		mes "……そうか。";
		mes "困ったね。";
		mes "私にできることがあれば";
		mes "いいのだが……。";
		emotion 9;
		next;
		menu "中にいる冒険者がお腹を空かせています",-;
		mes "[フィリー]";
		mes "そんなことなら";
		mes "早く出てくればいいのに。";
		mes "……すまないが";
		mes "もし食べ物があれば、その冒険者に";
		mes "少し分けてやってくれないか？";
		next;
		mes "[フィリー]";
		mes "……私も今はこれしか持ってないが";
		mes "もし、また冒険者の様子を";
		mes "見に行くなら";
		mes "持って行ってくれ。";
		next;
		mes "[フィリー]";
		mes "これからは定期的に";
		mes "冒険者たちの無事を確認しよう。";
		mes "よかったら明日もまた来てくれ。";
		if(checkitemblank() < 2) {
			next;
			mes "[フィリー]";
			mes "お礼をしようと思ったけど";
			mes "それ以上持てないようだね。";
			mes "アイテムの種類数を減らしてから";
			mes "また来てくれ。";
			close;
		}
		set ECL_8QUE,5;
		delquest 72470;
		delquest 72455;
		setquest 13059;
		setquest 13060;
		setquest 72460;
		setquest 201585;
		getexp 300000,0;
		getexp 0,300000;
		getitem 517,10;
		getitem 6081,1;
		close;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		mes "[フィリー]";
		mes "いつみても美しい草原だね。";
		mes "花が咲きはじめた大地という名が";
		mes "本当に似合うよ。";
		emotion 2;
		next;
		switch(select("会話する","大地の様子を聞く","冒険者たちの安否")) {
		case 1:
			switch(rand(3)) {
			case 0:
				mes "[フィリー]";
				mes "花と大地を愛する心を持っていれば";
				mes "お互いに争ったりすることも";
				mes "ないはずなのに。";
				close;
			case 1:
				mes "[フィリー]";
				mes "ビフロストタワーは危険なので";
				mes "用がないなら入らないでくれ。";
				mes "すでに入ってしまった冒険者たちは";
				mes "どうすることもできないよ。";
				close;
			case 2:
				mes "[フィリー]";
				mes "エクラージュはどうだい？";
				mes "本当に素晴らしい場所だろう。";
				close;
			}
		case 2:
			if(checkquest(13059) & 0x2) {
				mes "[フィリー]";
				mes "よく来てくれたね。";
				mes "作業の時間だ。";
				mes "手伝ってくれるかい？";
				next;
				if(select("私に任せて！","すみません、また後で") == 2) {
					mes "[フィリー]";
					mes "徐々に小さくなっていく";
					mes "大地の声が聞こえるかい？";
					mes "今日は気分がよくないみたいだ。";
					next;
					mes "[フィリー]";
					mes "こんな時こそ、大地のために";
					mes "働く必要があるんだ！";
					close;
				}
				mes "[フィリー]";
				mes "本当にありがとう！";
				mes "ラフィネ達に作業開始を";
				mes "伝えてくれ！";
				delquest 13059;
				setquest 13050;
				setquest 13051;
				setquest 13052;
				setquest 13053;
				setquest 13054;
				viewpoint 1,222,290,0,0xFF0000;
				viewpoint 1,83,263,1,0xFF0000;
				viewpoint 1,163,196,2,0xFF0000;
				viewpoint 1,237,181,3,0xFF0000;
				close;
			}
			if(checkquest(13050)) {
				if(checkquest(13051) || checkquest(13052) || checkquest(13053) || checkquest(13054)) {
					mes "[フィリー]";
					mes "作業を行うラフィネは4人だ。";
					mes "みんなに作業開始するよう";
					mes "伝えてくれ。";
					viewpoint 1,222,290,0,0xFF0000;
					viewpoint 1,83,263,1,0xFF0000;
					viewpoint 1,163,196,2,0xFF0000;
					viewpoint 1,237,181,3,0xFF0000;
					close;
				}
				mes "[フィリー]";
				mes "大地の歌声が聞こえるよ。";
				mes "みんなに伝えてくれたんだね。";
				mes "ありがとう。";
				next;
				mes "[フィリー]";
				mes "風が吹いて花と木が踊る音……";
				mes "いつか、キミにも聞こえるだろう。";
				emotion 3;
				if(checkitemblank() < 2) {
					next;
					mes "[フィリー]";
					mes "お礼をしようと思ったけど";
					mes "それ以上持てないようだね。";
					mes "アイテムの種類数を減らしてから";
					mes "また来てくれ。";
					close;
				}
				delquest 13050;
				setquest 13059;
				getitem 6081,1;
				close;
			}
			mes "[フィリー]";
			mes "今は大地の機嫌が";
			mes "少し良いみたいだね。";
			mes "休んでいても大丈夫そうだよ。";
			close;
		case 3:
			if(checkquest(13060) & 0x2) {
				mes "[フィリー]";
				mes "まだ冒険者たちは出て来ないんだ。";
				mes "彼らが無事かどうか";
				mes "今日も見に行ってくれないか？";
				next;
				mes "[フィリー]";
				mes "わざわざ他の世界から来てくれた";
				mes "冒険者たちが怪我でもしたら";
				mes "大地が悲しむよ……。";
				next;
				if(select("手伝います！","今日は疲れているから、ごめんなさい") == 2) {
					mes "[フィリー]";
					mes "そうか。";
					mes "……心配だよ。";
					mes "特に歌を歌っていた冒険者が……。";
					close;
				}
				mes "[フィリー]";
				mes "ありがとう。";
				mes "3人の冒険者が無事か";
				mes "見て来てくれ！";
				delquest 13060;
				setquest 13055;
				setquest 13056;
				setquest 13057;
				setquest 13058;
				close;
			}
			if(checkquest(13055)) {
				if(!checkquest(72475)) {
					mes "[フィリー]";
					mes "3人の冒険者が";
					mes "まだビフロストタワーから";
					mes "出て来ないんだ。";
					mes "それぞれ事情はあるだろうけど";
					mes "心配だよ。";
					next;
					mes "[フィリー]";
					mes "冒険者たちが無事なのか";
					mes "見に行ってくれ。";
					close;
				}
				mes "[フィリー]";
				mes "全員無事だったのか。";
				mes "……早く出てくればいいのに。";
				mes "とにかく助かったよ！";
				emotion 54;
				if(checkitemblank() < 2) {
					next;
					mes "[フィリー]";
					mes "お礼をしようと思ったけど";
					mes "それ以上持てないようだね。";
					mes "アイテムの種類数を減らしてから";
					mes "また来てくれ。";
					close;
				}
				delquest 13055;
				delquest 72475;
				setquest 13060;
				getitem 6081,1;
				close;
			}
			mes "[フィリー]";
			mes "一応みんな無事で";
			mes "よかったと言うべきかな……。";
			emotion 9;
			close;
		}
	}
OnInit:
	waitingroom "ラフィネ流ガーデニング",0;
	end;
}

ecl_fild01.gat,222,290,5	script	歌うラフィネ	436,{
	if(ECL_8QUE == 2) {
		if(checkquest(13051)) {
			mes "[歌うラフィネ]";
			mes "フィリー様のお遣いですか？";
			mes "では、歌いますね！";
			next;
			mes "[歌うラフィネ]";
			mes "何故歌うのかって？";
			mes "私の歌はこの大地に";
			mes "安らぎを与えることができるんですよ。";
			next;
			mes "‐ラフィネの歌が始まった。";
			mes "　心が暖まるような歌だ‐";
			emotion 2;
			delquest 13051;
			close;
		}
		mes "[歌うラフィネ]";
		mes "私は大地と花のために歌っています。";
		close;
	}
	if(ECL_8QUE == 3) {
		mes "[歌うラフィネ]";
		mes "大地のために歌うことは";
		mes "とてもいいことだと思います。";
		close;
	}
	if(ECL_8QUE >= 5) {
		if(!checkquest(13059)) {
			if(checkquest(13051)) {
				mes "[歌うラフィネ]";
				mes "作業開始の時間ですね！";
				mes "心配しないでください。";
				mes "私の声は必ず大地に届きますから。";
				emotion 2;
				next;
				mes "‐ラフィネの歌が始まった。";
				mes "　心が暖まるような歌だ‐";
				emotion 2;
				delquest 13051;
				close;
			}
			mes "[歌うラフィネ]";
			mes "私は大地と花のために歌っています。";
			close;
		}
		mes "[歌うラフィネ]";
		mes "歌い過ぎたみたいで";
		mes "のどが渇きました。";
		mes "こんな時には冷たい飲み物が";
		mes "欲しくなります。";
		emotion 53;
		close;
	}
	mes "[歌うラフィネ]";
	mes "大地の声が聞こえますか？";
	mes "今は悲しんでるみたいなんです……。";
	close;
}

ecl_fild01.gat,83,263,5	script	水を与えているラフィネ	444,{
	if(ECL_8QUE == 2) {
		if(checkquest(13052)) {
			mes "[水を与えているラフィネ]";
			mes "作業が始まっているんですか？";
			mes "では、私は大地に水を与えます。";
			delquest 13052;
			close;
		}
		mes "[水を与えているラフィネ]";
		mes "草と花びらが生き返る音が";
		mes "聞こえますか？";
		mes "私が毎日";
		mes "水を与えているからなんですよ！";
		mes "へへっ！";
		close;
	}
	if(ECL_8QUE == 3) {
		mes "[水を与えているラフィネ]";
		mes "大地に水を与えるのが";
		mes "私の仕事です。";
		close;
	}
	if(ECL_8QUE >= 5) {
		if(!checkquest(13059)) {
			if(checkquest(13052)) {
				mes "[水を与えているラフィネ]";
				mes "今日もたくさん水を与えます。";
				mes "そうすれば、枯れた花と草が";
				mes "生き返りますから！";
				mes "へへっ！";
				delquest 13052;
				close;
			}
			mes "[水を与えているラフィネ]";
			mes "あっちこっちに水を与えています。";
			mes "あなたも元気がない時は";
			mes "水を飲むといいですよ～。";
			close;
		}
		mes "[水を与えているラフィネ]";
		mes "今日の水遣りはこのくらいにします。 ";
		mes "水が多すぎても良くないですし";
		mes "明日の水の用意もしないと";
		mes "いけないので。";
		close;
	}
	mes "[水を与えているラフィネ]";
	mes "大地の元気がない……";
	mes "枯れていくように見えます。";
	close;
}

ecl_fild01.gat,163,196,5	script	踊るラフィネ	438,{
	if(ECL_8QUE == 2) {
		if(checkquest(13053)) {
			mes "[踊るラフィネ]";
			mes "フィリー様が作業を始めなさいと";
			mes "言ったんですか？";
			mes "でも、どうしてあなたがそのことを？";
			next;
			mes "[踊るラフィネ]";
			mes "フィリー様に新しい踊りを";
			mes "見せる機会だったのに！";
			next;
			mes "[踊るラフィネ]";
			mes "今日は前に踊っていた踊りにします。";
			mes "新しい踊りはフィリー様に";
			mes "一番最初に見せるつもりですから。";
			next;
			menu "踊る？",-;
			mes "[踊るラフィネ]";
			mes "この地に住んでいるラフィネたちは";
			mes "この大地と生命体たちの気持ちを";
			mes "感じ取ることができます。";
			next;
			mes "[踊るラフィネ]";
			mes "私が躍っていると";
			mes "大地が元気になるのが";
			mes "わかったんですよ。";
			mes "だから、私は毎日踊っています。";
			next;
			mes "[踊るラフィネ]";
			mes "あなたも冒険をしているうちに";
			mes "大地の気持ちがわかるように";
			mes "なるかもしれないわ。";
			mes "さあ、始めますよ。";
			delquest 13053;
			close;
		}
		mes "[踊るラフィネ]";
		mes "明日はフィリー様が";
		mes "来てくれたらいいな。";
		close;
	}
	if(ECL_8QUE == 3) {
		mes "[踊るラフィネ]";
		mes "風に揺られている草を見ていると";
		mes "まるで踊っているみたいだと";
		mes "思いませんか？";
		close;
	}
	if(ECL_8QUE >= 5) {
		if(!checkquest(13059)) {
			if(checkquest(13051)) {
				mes "[踊るラフィネ]";
				mes "今日もあなたですか……。";
				mes "私が作業をがんばっていると";
				mes "フィリー様に伝えてくださいね！";
				mes "さあ、早く！";
				emotion 32;
				delquest 13053;
				close;
			}
			mes "[踊るラフィネ]";
			mes "さぼったりしないので";
			mes "心配しないでください。";
			close;
		}
		mes "[踊るラフィネ]";
		mes "次はフィリー様が";
		mes "来てくれたらいいな……";
		close;
	}
	mes "[踊るラフィネ]";
	mes "いち、に、さん、し……";
	mes "踊る前に体をほぐすことが重要です。";
	mes "こんな感じにね！";
	close;
}

ecl_fild01.gat,237,181,5	script	カワイイラフィネ	446,{
	if(ECL_8QUE == 2) {
		if(checkquest(13054)) {
			mes "[カワイイラフィネ]";
			mes "何か用ですか？";
			next;
			menu "フィリーの頼みで来た",-;
			mes "[カワイイラフィネ]";
			mes "作業の開始時間を知らせに来たの？";
			mes "じゃあ、新人さんね！";
			next;
			menu "違う",-;
			mes "[カワイイラフィネ]";
			mes "あ、恥ずかしがらないでいいよ。";
			mes "私も最近作業を始めたばかりだし。";
			mes "けど、私が先輩だからね！";
			next;
			menu "……",-;
			mes "[カワイイラフィネ]";
			mes "みんないろいろな方法で";
			mes "大地を愛する気持ちを";
			mes "表現するんだけど、";
			mes "君は何ができるの？";
			next;
			mes "[カワイイラフィネ]";
			mes "見た感じでは……";
			mes "ちょっとわからないんだけど？";
			next;
			menu "君は何を？",-;
			mes "[カワイイラフィネ]";
			mes "見てわからないかな～。";
			mes "私ってオシャレでカワイイでしょう？";
			next;
			mes "[カワイイラフィネ]";
			mes "私は大地に微笑みを";
			mes "分けてあげる仕事をしているの。";
			mes "こんな風に大地に向けて微笑むと";
			mes "きっと大地も気分が良くなるはずよ！";
			next;
			menu "……",-;
			mes "[カワイイラフィネ]";
			mes "とにかく、君も大地のために";
			mes "できる仕事を、早く見つけてね！";
			mes "じゃあ、私は作業を始めるから。";
			next;
			mes "‐カワイイラフィネは微笑み始めた‐";
			emotion 18;
			delquest 13054;
			close;
		}
		mes "[カワイイラフィネ]";
		mes "変に見えるかもしれないけど";
		mes "常に大地に微笑むことは";
		mes "けっこう大変なの。";
		close;
	}
	if(ECL_8QUE == 3) {
		mes "[カワイイラフィネ]";
		mes "楽しかった事を思い出しながら";
		mes "軽く微笑んでみるの。";
		close;
	}
	if(ECL_8QUE >= 5) {
		if(!checkquest(13059)) {
			if(checkquest(13051)) {
				mes "[カワイイラフィネ]";
				mes "新人さんね。";
				mes "作業を始めるわ。";
				emotion 18;
				delquest 13054;
				close;
			}
			mes "[カワイイラフィネ]";
			mes "変に見えるかもしれないけど";
			mes "常に大地に微笑むことは";
			mes "けっこう大変なの。";
			emotion 18;
			close;
		}
		mes "[カワイイラフィネ]";
		mes "大地に微笑みを与えるために";
		mes "私も日々自分を磨いています。";
		mes "きっとカワイイ方が大地も";
		mes "嬉しいに違いないですから！";
		close;
	}
	mes "[カワイイラフィネ]";
	mes "花咲く大地に来たのは初めて？";
	mes "美しい草原でしょ！";
	close;
}

ecl_fild01.gat,98,47,5	script	ロシ#0番	893,{
	mes "‐真面目そうな女性がいる‐";
	close2;
	warp "ecl_tdun01a.gat",98,44;
	end;
}

ecl_tdun01a.gat,98,47,5	script	ロシ#1番	893,{
	if(ECL_8QUE == 4) {
		if(checkquest(13057)) {
			mes "[ロシ]";
			mes "あら、びっくりした！";
			mes "あなたは……？";
			next;
			menu "状況を説明する",-;
			mes "[ロシ]";
			mes "そうですか……。";
			mes "心配されているとは知りませんでした。";
			mes "だけど、まだ戻る事はできません。";
			mes "私は記者です。";
			next;
			mes "[ロシ]";
			mes "月刊ブリガンという雑誌に";
			mes "冒険者向けの記事を書いています。";
			next;
			mes "[ロシ]";
			mes "やっとここまで来たけど";
			mes "まだ特ダネが見つからないんです。";
			mes "ここに何かあると記者の勘が";
			mes "告げているのに！";
			next;
			mes "[ロシ]";
			mes "とにかく私は無事なので";
			mes "心配の必要はないと伝えてください。";
			next;
			if(checkquest(13056) || checkquest(13058)) {
				mes "‐ロシは無事なようだ。";
				mes "　他の冒険者の安否も確認しよう‐";
				delquest 13057;
				close2;
				warp "ecl_tdun01.gat",98,44;
				end;
			}
			mes "‐3人とも無事のようだ。";
			mes "　フィリーに報告しよう‐";
			setquest 72455;
			delquest 13057;
			close2;
			warp "ecl_tdun01.gat",98,44;
			end;
		}
		mes "[ロシ]";
		mes "大丈夫です。";
		mes "きっと特ダネを見つけますから！";
		close2;
		warp "ecl_tdun01.gat",98,44;
		end;
	}
	if(ECL_8QUE >= 5) {
		if(checkquest(13057)) {
			mes "[ロシ]";
			mes "また、あなたね。";
			mes "前にも言ったけど";
			mes "特ダネを見つけるまで";
			mes "私はここから出ませんから！";
			next;
			if(checkquest(13056) || checkquest(13058)) {
				mes "‐ロシは無事なようだ。";
				mes "　他の冒険者の安否も確認しよう‐";
				delquest 13057;
				close2;
				warp "ecl_tdun01.gat",98,44;
				end;
			}
			mes "‐3人とも無事のようだ。";
			mes "　フィリーに報告しよう‐";
			setquest 72475;
			delquest 13057;
			close2;
			warp "ecl_tdun01.gat",98,44;
			end;
		}
		mes "[ロシ]";
		mes "心配しないでください。";
		mes "自分の身は自分で守れますから！";
		close2;
		warp "ecl_tdun01.gat",98,44;
		end;
	}
	mes "[ロシ]";
	mes "特ダネが必要です！";
	mes "冒険者たちの心を";
	mes "掴むことができるようなものが。";
	close2;
	warp "ecl_tdun01.gat",98,44;
	end;
}

ecl_tdun01.gat,11,62,5	script	ウンチョウ#0番	896,{
	mes "‐若い冒険者風の男性がいる‐";
	close2;
	warp "ecl_tdun01a.gat",13,61;
	end;
}

ecl_tdun01a.gat,11,62,5	script	ウンチョウ#1番	896,{
	if(ECL_8QUE == 4) {
		if(checkquest(13056)) {
			mes "[ウンチョウ]";
			mes "あなたも冒険者ですか？";
			mes "ここは私が調べているので";
			mes "もし調べたいなら";
			mes "私の後にしてください。";
			next;
			menu "状況を説明する",-;
			mes "[ウンチョウ]";
			mes "冒険者の安否を心配するとは";
			mes "暇なラフィネですね。";
			mes "まして、いつかは冒険王になる男に";
			mes "心配など無用です。";
			next;
			menu "冒険王？",-;
			mes "[ウンチョウ]";
			mes "そう……あらゆる場所を探検し";
			mes "見つけた宝をどこかに隠すつもりです。";
			mes "やがて冒険者たちが";
			mes "私の足跡を追うことになるでしょう。";
			next;
			mes "[ウンチョウ]";
			mes "サインしてあげましょうか？";
			mes "いずれ、一生食べるのに困らない";
			mes "大金になるかもしれませんよ。";
			next;
			menu "遠慮する",-;
			mes "[ウンチョウ]";
			mes "……人を見る目がないですね。";
			mes "私はまだここを調べるので";
			mes "ラフィネには大丈夫だと";
			mes "伝えておいてください。";
			next;
			if(checkquest(13057) || checkquest(13058)) {
				mes "‐ウンチョウは無事なようだ。";
				mes "　他の冒険者の安否も確認しよう‐";
				delquest 13056;
				close2;
				warp "ecl_tdun01.gat",13,61;
				end;
			}
			mes "‐3人とも無事のようだ。";
			mes "　フィリーに報告しよう‐";
			setquest 72475;
			delquest 13056;
			close2;
			warp "ecl_tdun01.gat",13,61;
			end;
		}
		mes "[ウンチョウ]";
		mes "大丈夫です。";
		mes "私は冒険王になる男ですから。";
		close2;
		warp "ecl_tdun01.gat",13,61;
		end;
	}
	if(ECL_8QUE >= 5) {
		if(checkquest(13056)) {
			mes "[ウンチョウ]";
			mes "心配無用です。";
			mes "探索が終われば出て行くので";
			mes "ラフィネには無事だと伝えてください。";
			next;
			mes "[ウンチョウ]";
			mes "別の場所を調べに行きますので";
			mes "これで失礼。";
			next;
			if(checkquest(13057) || checkquest(13058)) {
				mes "‐ウンチョウは無事なようだ。";
				mes "　他の冒険者の安否も確認しよう‐";
				delquest 13056;
				close2;
				warp "ecl_tdun01.gat",13,61;
				end;
			}
			mes "‐3人とも無事のようだ。";
			mes "　フィリーに報告しよう‐";
			setquest 72475;
			delquest 13056;
			close2;
			warp "ecl_tdun01.gat",13,61;
			end;
		}
		mes "[ウンチョウ]";
		mes "私のサインが欲しいのですか？";
		mes "そうでないなら";
		mes "邪魔をしないでください。";
		close2;
		warp "ecl_tdun01.gat",13,61;
		end;
	}
	mes "[ウンチョウ]";
	mes "塔の隅々まで探索しています。";
	mes "回顧録を書くときに困らないように。";
	close2;
	warp "ecl_tdun01.gat",13,61;
	end;
}

ecl_tdun01.gat,51,103,3	script	ニュオーズ#0	625,{
	mes "‐派手な格好をした男性がいる‐";
	close2;
	warp "ecl_tdun01a.gat",53,103;
	end;
}

ecl_tdun01a.gat,51,103,3	script	ニュオーズ#1	625,{
	if(ECL_8QUE == 4) {
		if(checkquest(13058)) {
			cutin "nines04",2;
			mes "[ニュオーズ]";
			mes "もしかして……人間なのか？";
			next;
			menu "安否を確認しに来た",-;
			mes "[ニュオーズ]";
			mes "無事だと言えるのかな……？";
			mes "無事じゃないかもしれない。";
			next;
			mes "[ニュオーズ]";
			mes "もう何日も食べてないんだ……。";
			mes "今にも倒れそうだよ。";
			next;
			mes "[ニュオーズ]";
			mes "とりあえず^FF0000今は^000000生きている……。";
			mes "けど、いつまで保つか……。";
			mes "ああ、眠くなってきた……。";
			next;
			mes "[ニュオーズ]";
			mes "外にいる……。";
			mes "筋肉ラフィネだったかな？";
			mes "食べ物を分けてくれと伝えてくれ。";
			mes "私が飢え死ぬ前に。";
			next;
			if(checkquest(13056) || checkquest(13057)) {
				mes "‐ニュオーズは無事なようだ。";
				mes "　他の冒険者の安否も確認しよう‐";
				delquest 13058;
				close2;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			mes "‐3人とも無事のようだ。";
			mes "　フィリーに報告しよう‐";
			setquest 72455;
			delquest 13058;
			close2;
			warp "ecl_tdun01.gat",53,103;
			end;
		}
		cutin "nines04",2;
		mes "[ニュオーズ]";
		mes "味までは望まない。";
		mes "お願いだから何か食べ物を……。";
		mes "力が入らなくて、もう歩けない。";
		close2;
		warp "ecl_tdun01.gat",53,103;
		end;
	}
	if(ECL_8QUE == 5) {
		cutin "nines04",2;
		mes "[ニュオーズ]";
		mes "もう本当に終わりのようだ……。";
		mes "それでも私の人生楽しかったな……。";
		next;
		mes "[ニュオーズ]";
		mes "お腹が減って死ぬのか。";
		mes "少し恥ずかしいけど……。";
		mes "今までありがとう。";
		mes "愛する私のギルド員たちよ。";
		next;
		menu "フィリーからにくを貰って来たよ！",-;
		mes "[ニュオーズ]";
		mes "私、にく大好きだよ！";
		mes "でも野菜はないのか？";
		next;
		mes "[ニュオーズ]";
		mes "野菜じゃなくても、にくと一緒に";
		mes "食べられるような物だよ。";
		mes "にくだけをそんなにいっぱい";
		mes "食べられないよ。";
		next;
		mes "[ニュオーズ]";
		mes "そうだな……にくだけじゃなくて、";
		mes "塔の外にいるペタルが持っている";
		mes "^FF0000大量のどんぐり^000000も";
		mes "10個持ってきてくれないかい？";
		mes "頼んだよ。";
		set ECL_8QUE,6;
		setquest 13061;
		delquest 72460;
		close2;
		warp "ecl_tdun01.gat",53,103;
		end;
	}
	if(ECL_8QUE == 6) {
		if(countitem(517) < 10 || countitem(6558) < 10) {
			cutin "nines04",2;
			mes "[ニュオーズ]";
			mes "これが走馬灯というものなのか……。";
			mes "むかしの思い出が……";
			mes "プロンテラ南の門近くでの";
			mes "楽しいひととき……。";
			close2;
			warp "ecl_tdun01.gat",53,103;
			end;
		}
		cutin "nines02",2;
		mes "[ニュオーズ]";
		mes "にくだ、おにく！";
		mes "私が大好きなおにく！";
		next;
		mes "[ニュオーズ]";
		mes "うううう、美味しい。";
		next;
		mes "[ニュオーズ]";
		mes "そうだよ、この味だよ。";
		next;
		mes "[ニュオーズ]";
		mes "ああ、美味しい！";
		mes "これこそがおにくの味。";
		next;
		mes "[ニュオーズ]";
		mes "外に出たら筋肉ラフィネに";
		mes "歌のひとつも作ってあげないと。";
		next;
		mes "[ニュオーズ]";
		mes "いつ……出られるか";
		mes "わからないけど……。";
		next;
		menu "ここにいる理由を聞く",-;
		mes "[ニュオーズ]";
		mes "うーん、なんと言えばいいか……。";
		mes "気がついたらこの塔に入って";
		mes "道に迷っていたんだ。";
		next;
		mes "[ニュオーズ]";
		mes "実は2年前に";
		mes "道に迷ったことがあって";
		mes "それ以降は気が向くままに";
		mes "旅行しているんだ。";
		next;
		mes "[ニュオーズ]";
		mes "この塔がおもしろそうだから";
		mes "入ってみたんだけど、";
		mes "出られなくて困ってしまったんだ。";
		next;
		if(checkitemblank() == 0) {
			mes "[ニュオーズ]";
			mes "お礼をしようと思ったけど";
			mes "これ以上持てないみたいだね。";
			mes "アイテムの種類数を減らしてから";
			mes "また来てくれ。";
			close2;
			cutin "nines04",255;
			warp "ecl_tdun01.gat",53,103;
			end;
		}
		mes "[ニュオーズ]";
		mes "ともかく、これで助かったよ。";
		mes "ありがとう。";
		mes "すまないが、もうひとつ";
		mes "助けてくれないか？";
		mes "よかったら、もう一度話しかけてくれ。";
		delitem 517,10;
		delitem 6558,10;
		set ECL_8QUE,7;
		delquest 13061;
		getexp 300000,0;
		getexp 0,300000;
		getitem 6081,1;
		setquest 72480;
		close2;
		cutin "nines02",255;
		end;
	}
	if(ECL_8QUE == 7) {
		if(checkquest(13063)) {
			if(!(checkquest(13063) & 0x4)) {
				cutin "nines03",2;
				mes "[ニュオーズ]";
				mes "まだ処理できないのかい？";
				mes "もう外に出たいから";
				mes "急いでくれると助かる。";
				mes "作詞でもしながら待たせてもらうよ。";
				close2;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			cutin "nines02",2;
			mes "[ニュオーズ]";
			mes "終わったんだね！";
			mes "これでもう少し探検を楽しんで";
			mes "……違う！";
			mes "そろそろ外に出てみようかな。";
			next;
			mes "[ニュオーズ]";
			mes "……と思ったけど、";
			mes "せっかくここまで来たから";
			mes "何か記念になるものでもないと";
			mes "旅行に来た意味がないよね？";
			next;
			mes "[ニュオーズ]";
			mes "実は……。";
			mes "お土産がないと";
			mes "友達が怒るんじゃないかと。";
			next;
			mes "[ニュオーズ]";
			mes "友達が怒らないで喜びそうな";
			mes "記念品にいい物がないかな？";
			emotion 1;
			next;
			switch(select("ゼロピー","幸運の卵","周辺モンスターの戦利品")) {
			case 1:
				mes "[ニュオーズ]";
				mes "ゼロピーもいいけど……。";
				mes "あまりにも珍しくないし……。";
				mes "他に何かないかな？";
				next;
				if(select("バフォメットカード","周辺モンスターの戦利品") == 2)
					break;
				cutin "nines04",2;
				mes "[ニュオーズ]";
				mes "お、おい……。";
				mes "そんな物はここで";
				mes "手に入れられないよ。";
				emotion 19;
				next;
				menu "周辺モンスターの戦利品 ",-;
				break;
			case 2:
				mes "[ニュオーズ]";
				mes "ん？　それは何に使う物なんだ？";
				mes "旅行をしている間に";
				mes "何か新しい物が出たようだね。";
				emotion 1;
				next;
				mes "[ニュオーズ]";
				mes "何かわからないけど、他にないかな？";
				next;
				if(select("古いカード帖","周辺モンスターの戦利品") == 2)
					break;
				mes "[ニュオーズ]";
				mes "古いカード帖か……。";
				mes "ハズレになるかもしれない物を";
				mes "友達に渡すことはできないよ。";
				mes "他にないかな？";
				next;
				menu "周辺モンスターの戦利品",-;
				break;
			case 3:
				break;
			}
			cutin "nines01",2;
			mes "[ニュオーズ]";
			mes "周辺モンスターの戦利品か……。";
			mes "それいいね！";
			emotion 0;
			next;
			mes "[ニュオーズ]";
			mes "きっと友達も";
			mes "ここまでは来たことはないだろうし";
			mes "ここでしか手に入らないものなら";
			mes "不思議に見えるだろうね。";
			next;
			mes "[ニュオーズ]";
			mes "私が旅行していた場所を";
			mes "伝えるのにも役立つだろう。";
			next;
			if(checkitemblank() == 0) {
				mes "[ニュオーズ]";
				mes "お礼をしようと思ったけど";
				mes "これ以上持てないみたいだね。";
				mes "アイテムの種類数を減らしてから";
				mes "また来てくれ。";
				close2;
				cutin "nines04",255;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			mes "[ニュオーズ]";
			mes "いい考えだ。";
			mes "では、何を集めるか考えてみるから";
			mes "もう一度話しかけてくれ。";
			set ECL_8QUE,8;
			delquest 13063;
			setquest 72485;
			getexp 300000,0;
			getexp 0,300000;
			getitem 6081,1;
			close2;
			warp "ecl_tdun01.gat",53,103;
			end;
		}
		cutin "nines01",2;
		mes "[ニュオーズ]";
		mes "私を助けてくれるんだね、ありがとう。";
		mes "私が彷徨っているのは、";
		mes "もちろん方向音痴というのもあるけど";
		mes "他にも理由がある。";
		next;
		cutin "nines04",2;
		mes "[ニュオーズ]";
		mes "あそこにいるやつらが見えるか？";
		mes "やつらがここから出るのを";
		mes "邪魔しているようなのだよ。";
		next;
		menu "何も見えない",-;
		mes "[ニュオーズ]";
		mes "しっかり見てくれ。";
		mes "あっちにいるホコリみたいな奴らが";
		mes "私の視野をジャマしている。";
		mes "視野がぼやけて来ると眠くなるし";
		mes "お腹も減ってくる……。";
		emotion 16;
		next;
		menu "気のせいだよ",-;
		cutin "nines03",2;
		mes "[ニュオーズ]";
		mes "そんなことはない。";
		mes "やつらを20匹ほど倒してくれれば";
		mes "ここから出られそうなんだ。";
		mes "お願いだよ。";
		next;
		mes "‐ニュオーズを助けるために、";
		mes "　^FF0000チェネレを20匹^000000倒そう‐";
		delquest 72480;
		setquest 13063;
		close2;
		warp "ecl_tdun01.gat",53,103;
		end;
	}
	if(ECL_8QUE == 8) {
		cutin "nines02",2;
		mes "[ニュオーズ]";
		mes "考えてみたけど！";
		mes "^FF0000落ち葉のしおり^000000なら";
		mes "友達も喜ぶと思うよ！";
		next;
		mes "[ニュオーズ]";
		mes "この塔で見かける古書の間に";
		mes "しおりが挟まっていたよ。";
		mes "誰かが読みかけなのかもしれないけど";
		mes "いいお土産になるよ。";
		emotion 52;
		next;
		mes "[ニュオーズ]";
		mes "ちょうど^FF0000いいメロディ^000000が浮かんだから";
		mes "私は歌を作るよ。";
		mes "君はお土産を集めてきてくれ。";
		next;
		mes "‐ニュオーズのお土産に";
		mes "　^FF0000落ち葉のしおりを10個^000000集めよう。";
		mes "　落ち葉のしおりはこの塔にいる";
		mes "　毀損された古書が持っているようだ‐";
		set ECL_8QUE,9;
		delquest 72485;
		setquest 13065;
		close2;
		warp "ecl_tdun01.gat",53,103;
		end;
	}
	if(ECL_8QUE == 9) {
		if(countitem(6560) < 10) {
			cutin "nines03",2;
			mes "[ニュオーズ]";
			mes "心配しなくていいよ。";
			mes "歌の方もうまく進んでいる。";
			next;
			mes "[ニュオーズ]";
			mes "^FF0000記念品を集めて来る頃^000000には";
			mes "多分完成していると思うよ。";
			close2;
			cutin "nines04",255;
			warp "ecl_tdun01.gat",53,103;
			end;
		}
		cutin "nines02",2;
		mes "[ニュオーズ]";
		mes "落ち葉のしおりを集めたんだね!?";
		mes "思った通りの記念品だよ。";
		mes "みんな喜ぶよ。";
		next;
		mes "[ニュオーズ]";
		mes "ちょうど歌も完成したんだ。";
		mes "一度聞いてみる？";
		next;
		mes "[ニュオーズ]";
		mes "^D96E26また、その道と出会った～";
		mes "彷徨い続けて～^000000";
		next;
		mes "[ニュオーズ]";
		mes "^D96E26馴染んだダンジョン～";
		mes "モンスターでいっぱい～";
		mes "迷路と私の空腹～^000000";
		next;
		mes "[ニュオーズ]";
		mes "^D96E26抜け出そうとした道に～";
		mes "モンスターはいなくて良かったけど～^000000";
		next;
		mes "[ニュオーズ]";
		mes "^D96E26少し歩いただけで～";
		mes "目まいが～";
		mes "お腹が空いて倒れた";
		mes "その時のその場所^000000";
		next;
		mes "[ニュオーズ]";
		mes "ここまでだけど、どう？";
		mes "いけるでしょう？";
		next;
		switch(select("名曲だね","他の曲を真似したような気がするけど？")) {
		case 1:
			mes "[ニュオーズ]";
			mes "ありがとう！";
			mes "いつかチャンスがあれば";
			mes "君に助けてもらったことも";
			mes "歌にするよ！";
			break;
		case 2:
			cutin "nines04",2;
			mes "[ニュオーズ]";
			mes "あはははは……。";
			mes "やっぱりそうだよね？";
			mes "実際歌ってみたら";
			mes "そんな感じもするし……。";
			mes "また今度作り直すよ。";
			break;
		}
		next;
		cutin "nines01",2;
		mes "[ニュオーズ]";
		mes "探検もほぼ終わったし";
		mes "満腹になったし……。";
		mes "そろそろ塔から出ないとね。";
		next;
		if(checkitemblank() == 0) {
			mes "[ニュオーズ]";
			mes "お礼をしようと思ったけど";
			mes "これ以上持てないみたいだね。";
			mes "アイテムの種類数を減らしてから";
			mes "また来てくれ。";
			close2;
			cutin "nines01",255;
			warp "ecl_tdun01.gat",53,103;
			end;
		}
		cutin "nines02",2;
		mes "[ニュオーズ]";
		mes "本当にありがとう！";
		mes "どこかでまた会えることを願うよ。";
		delitem 6560,10;
		set ECL_8QUE,10;
		delquest 13065;
		setquest 13062;
		setquest 13064;
		setquest 13066;
		setquest 201590;
		getexp 300000,0;
		getexp 0,300000;
		getitem 6081,1;
		close2;
		cutin "nines01",255;
		warp "ecl_tdun01.gat",53,103;
		end;
	}
	if(ECL_8QUE == 10) {
		if((checkquest(13062) && checkquest(13062) & 0x2 == 0) && (checkquest(13064) && checkquest(13064) & 0x2 == 0) && (checkquest(13066) && checkquest(13066) & 0x2 == 0)) {
			cutin "nines02",2;
			mes "[ニュオーズ]";
			mes "心配しなくていいよ！";
			mes "^FF0000今度は必ず外に出るから！^000000";
			mes "いままでありがとう！";
			mes "次に会ったら美味しいものでも";
			mes "ごちそうするよ。";
			emotion 15;
			close2;
			cutin "nines02",255;
			warp "ecl_tdun01.gat",53,103;
			end;
		}
		cutin "nines01",2;
		mes "[ニュオーズ]";
		mes "また、会ったね！";
		next;
		switch(select("生存を確認しに来た","食料補給","ホコリ除去","友達へのお土産")) {
		case 1:
			mes "[ニュオーズ]";
			mes "筋肉ラフィネに言われて";
			mes "来たんだね？";
			mes "心優しいラフィネだよね。";
			mes "心配ないと伝えてくれ。";
			if((!checkquest(13061) && !checkquest(13062)) || checkquest(13062) & 0x2) {
				next;
				cutin "nines04",2;
				mes "[ニュオーズ]";
				mes "ところで……。";
				mes "空腹で動けないんだ。";
				mes "助けてくれないかな？";
				emotion 16;
			}
			else if((!checkquest(13063) && !checkquest(13064)) || checkquest(13064) & 0x2) {
				next;
				mes "[ニュオーズ]";
				mes "私の前をジャマするホコリを";
				mes "何とかすれば大丈夫そうだな……。";
			}
			else if((!checkquest(13065) && !checkquest(13066)) || checkquest(13066) & 0x2) {
				next;
				mes "[ニュオーズ]";
				mes "お腹も満たしたし";
				mes "塔から出るのは難しくないね。";
				mes "あとはお土産さえ用意すれば……。";
			}
			if(checkquest(13055)) {
				next;
				if(checkquest(13056) || checkquest(13057)) {
					mes "‐ニュオーズは無事なようだ。";
					mes "　他の冒険者の安否も確認しよう‐";
					delquest 13058;
					close2;
					warp "ecl_tdun01.gat",53,103;
					end;
				}
				mes "‐3人とも無事のようだ。";
				mes "　フィリーに報告しよう‐";
				setquest 72475;
				delquest 13058;
				close2;
				cutin "nines01",255;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			close2;
			cutin "nines01",255;
			warp "ecl_tdun01.gat",53,103;
			end;
		case 2:
			if(checkquest(13062)) {
				if(checkquest(13062) & 0x2 == 0) {
					cutin "nines02",2;
					mes "[ニュオーズ]";
					mes "君が用意してくれたにくは";
					mes "本当に美味しかったよ。";
					mes "味付けが少し薄かったけど……。";
					close2;
					cutin "nines01",255;
					warp "ecl_tdun01.gat",53,103;
					end;
				}
			}
			if(checkquest(13061)) {
				if(countitem(517) < 10 || countitem(6558) < 10) {
					cutin "nines04",2;
					mes "[ニュオーズ]";
					mes "食べ物……食べ物が必要だよ……。";
					mes "目まいがする……。";
					next;
					mes "[ニュオーズ]";
					mes "に……にく。おにく……にく……。";
					next;
					mes "‐どうやら空腹で動けないようだ";
					mes "　にくと大量のどんぐりを10個ずつ";
					mes "　持ってきてあげよう‐";
					close2;
					cutin "nines01",255;
					warp "ecl_tdun01.gat",53,103;
					end;
				}
				cutin "nines02",2;
				mes "[ニュオーズ]";
				mes "久しぶりの食事だよ！";
				mes "にくだ！　にく！";
				mes "少し冷めているけどにくだよ！";
				emotion 15;
				next;
				mes "[ニュオーズ]";
				mes "うわあ、本当にありがとう！";
				mes "君は本当にいい人だね。";
				emotion 21;
				next;
				if(checkitemblank() == 0) {
					mes "[ニュオーズ]";
					mes "お礼をしようと思ったけど";
					mes "これ以上持てないみたいだね。";
					mes "アイテムの種類数を減らしてから";
					mes "また来てくれ。";
					close2;
					cutin "nines02",255;
					warp "ecl_tdun01.gat",53,103;
					end;
				}
				mes "[ニュオーズ]";
				mes "これで出口を探しに行けるよ。";
				mes "今回は外に出る事ができそうだ！";
				delitem 517,10;
				delitem 6558,10;
				delquest 13061;
				setquest 13062;
				getitem 6081,1;
				close2;
				cutin "nines01",255;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			cutin "nines02",2;
			mes "[ニュオーズ]";
			mes "ああ……助かったよ……";
			mes "また君に会えて。";
			next;
			mes "[ニュオーズ]";
			mes "もうちょっとで塔から";
			mes "出ることができると思ったのに";
			mes "いつの間にか同じ場所に";
			mes "戻ってしまうんだ……";
			next;
			mes "[ニュオーズ]";
			mes "もしかしたら、この塔には";
			mes "呪いのようなものが";
			mes "かかっているかもしれない。";
			next;
			menu "あなたが道を間違えただけでは？",-;
			cutin "nines04",2;
			mes "[ニュオーズ]";
			mes "……そうかもしれない。";
			mes "ともかく、歩き回って空腹なんだ。";
			mes "すまないが食べ物を";
			mes "持ってきてくれないか？";
			next;
			if(select("引き受ける","断る") == 2) {
				mes "[ニュオーズ]";
				mes "そうか……わかった。";
				mes "外の筋肉ラフィネには";
				mes "私のことは諦めてくれと";
				mes "伝えてくれ……。";
				emotion 16;
				close2;
				cutin "nines04",255;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			mes "[ニュオーズ]";
			mes "ありがとう。";
			mes "できれば、にくがいいな。";
			mes "あと大量のどんぐりが";
			mes "にくと合うと思うけど……。";
			next;
			menu "まずは何でもいいから食べた方が……",-;
			mes "[ニュオーズ]";
			mes "そうなんだけど、";
			mes "せっかく食べるなら";
			mes "美味しいものがいいじゃない？";
			mes "悪いけど頼むよ。";
			emotion 43;
			delquest 13062;
			setquest 13061;
			close2;
			cutin "nines04",255;
			warp "ecl_tdun01.gat",53,103;
			end;
		case 3:
			if(checkquest(13064)) {
				if(checkquest(13064) & 0x2 == 0) {
					cutin "nines02", 2;
					mes "[ニュオーズ]";
					mes "今は大丈夫だよ。";
					mes "このくらいなら問題ないからね。";
					close2;
					cutin "nines02",255;
					warp "ecl_tdun01.gat",53,103;
					end;
				}
			}
			if(checkquest(13063)) {
				if(checkquest(13063) & 0x4 == 0) {
					mes "[ニュオーズ]";
					mes "やっかいなやつらだ。";
					mes "あ……私がやりたくないから";
					mes "頼んでいるわけではないよ。";
					mes "ははは……。";
					emotion 22;
					close2;
					cutin "nines01",255;
					warp "ecl_tdun01.gat",53,103;
					end;
				}
				cutin "nines02",2;
				mes "[ニュオーズ]";
				mes "もう掃除したのかい？";
				mes "君はなかなか優秀だね。";
				mes "気に入ったよ。";
				emotion 52;
				next;
				if(checkitemblank() == 0) {
					mes "[ニュオーズ]";
					mes "お礼をしようと思ったけど";
					mes "これ以上持てないみたいだね。";
					mes "アイテムの種類数を減らしてから";
					mes "また来てくれ。";
					close2;
					cutin "nines02",255;
					warp "ecl_tdun01.gat",53,103;
					end;
				}
				mes "[ニュオーズ]";
				mes "後は私ひとりでなんとかするよ。";
				mes "助けられてばかりというのも";
				mes "悪いしね。";
				delquest 13063;
				setquest 13064;
				getitem 6081,1;
				close2;
				cutin "nines02",255;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			cutin "nines03",2;
			mes "[ニュオーズ]";
			mes "あああ！";
			mes "ひとりで塔から出ようとしたけど";
			mes "ちょっと景色に気を取られていたら";
			mes "またやつらが……。";
			next;
			cutin "nines04",2;
			mes "[ニュオーズ]";
			mes "私も埃を除去するが";
			mes "あまり動くとまた空腹になるし……。";
			emotion 9;
			next;
			if(select("ホコリの除去を手伝う","手伝わない") == 2) {
				mes "[ニュオーズ]";
				mes "そうか……。";
				mes "わたしひとりでやってみよう。";
				mes "もしかしたら、";
				mes "倒れてしまうかもしれないが……";
				close2;
				cutin "nines04",255;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			cutin "nines02",2;
			mes "[ニュオーズ]";
			mes "察しがいいね。さすがだ！";
			mes "今度、私のギルドに";
			mes "入れるようにしてあげるよ！";
			emotion 33;
			next;
			mes "[ニュオーズ]";
			mes "では、チェネレを20匹倒してくれ。";
			mes "いっぱい倒す必要はないよ。";
			mes "私もやるから。";
			delquest 13064;
			setquest 13063;
			close2;
			cutin "nines04",255;
			warp "ecl_tdun01.gat",53,103;
			end;
		case 4:
			if(checkquest(13066)) {
				if(checkquest(13066) & 0x2 == 0) {
					// 未調査
				}
				close2;
				cutin "nines04",255;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			if(checkquest(13065)) {
				if(countitem(6560) < 10) {
					cutin "nines01",2;
					mes "[ニュオーズ]";
					mes "多くはいらない。";
					mes "でも、もう少し欲しいな。";
					close2;
					cutin "nines01",255;
					warp "ecl_tdun01.gat",53,103;
					end;
				}
				cutin "nines02", 2;
				mes "[ニュオーズ]";
				mes "ありがとう！";
				mes "本当に君は素晴らしい！";
				next;
				mes "[ニュオーズ]";
				mes "ミッドガルド大陸でまた会おう！";
				mes "一緒に冒険もしたいし。";
				next;
				if(checkitemblank() == 0) {
					mes "[ニュオーズ]";
					mes "お礼をしようと思ったけど";
					mes "これ以上持てないみたいだね。";
					mes "アイテムの種類数を減らしてから";
					mes "また来てくれ。";
					close2;
					cutin "nines01",255;
					warp "ecl_tdun01.gat",53,103;
					end;
				}
				mes "[ニュオーズ]";
				mes "友達にお土産を渡すときに";
				mes "君のことも話しておくよ。";
				emotion 15;
				delitem 6560,10;
				delquest 13065;
				setquest 13066;
				getitem 6081,1;
				cutin "nines02",255;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			cutin "nines03",2;
			mes "[ニュオーズ]";
			mes "いつの間にか、集めてくれたお土産が";
			mes "なくなっていたんだ。";
			mes "ちゃんと荷物に入れておいたのに……。";
			next;
			mes "[ニュオーズ]";
			mes "申し訳ないけど";
			mes "もう一度助けてくれないか？";
			mes "友達に会わせる顔がないよ。";
			next;
			if(select("手伝う","手伝わない") == 2) {
				cutin "nines04",2;
				mes "[ニュオーズ]";
				mes "そうか……しかたない。";
				mes "ひとりで探してみるよ。";
				mes "いつまでかかるかわからないけど";
				mes "自分のミスだからね……。";
				close2;
				cutin "nines04",255;
				warp "ecl_tdun01.gat",53,103;
				end;
			}
			mes "[ニュオーズ]";
			mes "落ち葉でできたしおり。";
			mes "どこか懐かしい感じがするよ。";
			mes "きっと友達も喜んでくれるはず……。";
			delquest 13066;
			setquest 13065;
			close2;
			cutin "nines03",255;
			warp "ecl_tdun01.gat",53,103;
			end;
		}
	}
	cutin "nines04",2;
	mes "[ニュオーズ]";
	mes "朝に発泡一杯～";
	mes "お昼に発泡一杯～";
	mes "もうあなたに夢中……";
	mes "お腹が空きすぎて";
	mes "これ以上歌えない……。";
	close2;
	cutin "nines04",255;
	warp "ecl_tdun01.gat",53,103;
	end;
}

//============================================================
// プロフェッサーワームの記憶クエスト
//- Registry -------------------------------------------------
// ECL_9QUE -> 0～
//------------------------------------------------------------
ecl_fild01.gat,196,93,5	script	塔の案内人#biftower	443,{
	mes "[塔の案内人]";
	mes "今、3階から4階は通行止めでね。";
	mes "だから、この塔の4階に行きたいなら";
	mes "ボクの転送装置を利用しないと";
	mes "^ff00004階には行けない^000000から注意してね。";
	mes "転送装置で4階に行くかい?";
	next;
	if(select("転送装置を使う","転送は必要ない") == 2) {
		mes "[塔の案内人]";
		mes "わかったよ。";
		mes "3階から4階の階段は今";
		mes "壊れていて通行できないうえに";
		mes "3階はモンスターが多いから";
		mes "行くなら気をつけてね。";
		close;
	}
	mes "[塔の案内人]";
	mes "ボクが4階以外は用事がないし";
	mes "モンスターが多くて危険なんだよね。";
	mes "それじゃ転送するね。";
	close2;
	warp "ecl_tdun04.gat",26,24;
	end;
OnInit:
	waitingroom "4階転送",0;
	end;
}

ecl_tdun04.gat,23,27,5	script	出口案内人#biftower	443,{
	mes "[出口案内人]";
	mes "残念だけど、ここから";
	mes "3階には降りられないよ。";
	mes "もしこの塔から出たいなら";
	mes "オレが転送装置で";
	mes "塔の外に直接送るよ。";
	next;
	if(select("塔から出たい","理由を聞く") == 2) {
		mes "[出口案内人]";
		mes "出入口をモンスターが壊してね。";
		mes "修理しても修理しても壊すから";
		mes "今は放置状態なんだ。";
		mes "もしこの塔から出たいなら";
		mes "再度、オレに声をかけてね。";
		close;
	}
	mes "[出口案内人]";
	mes "それじゃ、塔の外に移動するよ。";
	mes "塔の外だから、襲われても";
	mes "文句は言わないでくれよ。";
	close2;
	warp "ecl_fild01.gat",182,92;
	end;
OnInit:
	waitingroom "入口転送",0;
	end;
}

ecl_tdun04.gat,26,39,1	script	プロフェッサーワーム	627,{
	switch(ECL_9QUE) {
	case 0:
		mes "[プロフェッサーワーム]";
		mes "忙しい、忙しいよ！　あー忙しい。";
		mes "モンスターを、";
		mes "モンスターを作らないと！";
		mes "危険だ、いつここを";
		mes "襲撃して来るか分からない！";
		mes "わああああ！";
		next;
		switch(select("挨拶をする","何をしているか聞く","ビフロストについて聞く")) {
		case 1:
			break;
		case 2:
			mes "[プロフェッサーワーム]";
			mes "難しい質問だ。";
			mes "やらなければいけない事があるのは";
			mes "覚えているんだが、";
			mes "何をやらなければいけないか";
			mes "思い出せないんだ。";
			next;
			mes "[プロフェッサーワーム]";
			mes "ひとまずは今やっていることを";
			mes "続けるしかない。";
			mes "モンスターを作って置くことだ。";
			close;
		case 3:
			mes "[プロフェッサーワーム]";
			mes "ビフロスト？　眠っているよ。";
			mes "ぐっすり眠っている。";
			next;
			mes "[プロフェッサーワーム]";
			mes "……";
			next;
			mes "[プロフェッサーワーム]";
			mes "ああ……次は私の番になるのか！";
			mes "だめだ！";
			mes "このままやられるわけにはいかない。";
			mes "モンスターを";
			mes "モンスターをもっと作らないと！";
			close;
		}
		mes "[プロフェッサーワーム]";
		mes "きゃああ！　だ、だ、誰だ！";
		mes "ここまでどうやって登って来た!?";
		mes "タワーには多くのモンスターを";
		mes "配置しておいたのに！";
		next;
		mes "[プロフェッサーワーム]";
		mes "侵入者が入って来ることは";
		mes "ありえないはずだが！";
		mes "やはり、き……君は！";
		next;
		mes "[プロフェッサーワーム]";
		mes "私が作ったモンスターだな？";
		mes "やはり、そうか！";
		next;
		if(select("このタワーはなんですか","あなたも虫に見えます") == 1) {
			mes "[プロフェッサーワーム]";
			mes "タワーだと！　ん、タワー？";
			mes "何だタワーって？";
			mes "なぜ、私がタワーの中にいるんだ？";
			mes "おかしい、何も思い出せん……。";
			mes "どうやってここに来たのだ私は。";
			close;
		}
		mes "[プロフェッサーワーム]";
		mes "虫？　何を言っているんだ。";
		mes "なぜ、私が虫なんだ！";
		mes "お前こそモンスターのくせに！";
		mes "私が適当に作ったせいで";
		mes "頭の方も適当なようだな!!";
		mes "まったく、困ったもんだ……。";
		next;
		mes "‐呆れ顔で頬を撫でる";
		mes "　プロフェッサーワーム‐";
		next;
		mes "[プロフェッサーワーム]";
		mes "……";
		next;
		mes "[プロフェッサーワーム]";
		mes "……";
		mes "…………";
		next;
		mes "[プロフェッサーワーム]";
		mes "……な、なんだこれは。";
		mes "なんということだ……。";
		mes "二枚目だった私の顔がいつの間に";
		mes "こんな風に……";
		mes "私の名前、私の名前は……";
		next;
		menu "プロフェッサーワーム？",-;
		mes "[プロフェッサーワーム]";
		mes "そうだ！　そうだ……いや";
		mes "そうだけど、そうじゃないんだ……。";
		mes "違う名前があったはずなんだ。";
		mes "なんだったかな……";
		mes "あれ、名前が出てこない！";
		mes "くそっ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "それよりも顔だ！　顔！";
		mes "なぜこんな虫みたいな顔に";
		mes "なってしまったというんだ……。";
		mes "何が起きているんだいったい……";
		next;
		emotion 1;
		mes "[プロフェッサーワーム]";
		mes "そうだ！　肖像画だ。";
		mes "以前、有名な画家に書いてもらった";
		mes "肖像画がどこかにあったはずだ。";
		mes "それがあれば昔の顔が";
		mes "わかるな、うん。よーーし。";
		next;
		mes "[プロフェッサーワーム]";
		mes "おい、君っ！";
		mes "何をぼーっと立っているんだ！";
		mes "今の話聞いていただろう。";
		mes "とりあえず早急に";
		mes "私の肖像画を探してきてくれよ！";
		next;
		if(select("手伝う","断る") == 2) {
			mes "[プロフェッサーワーム]";
			mes "おい、君！";
			mes "暇だからここまで";
			mes "登って来たんだろう！";
			mes "何を言っているんだ！";
			close;
		}
		mes "[プロフェッサーワーム]";
		mes "よし。いい子だ。";
		mes "何か聞きたい事があるんだろう。";
		mes "肖像画を見れば";
		mes "何か過去の記憶を";
		mes "思い出すかもしれない。";
		next;
		mes "[プロフェッサーワーム]";
		mes "この部屋の本棚にある本のどこかに";
		mes "私の肖像画が挟まっているはずだ。";
		mes "頼んだぞ！";
		set ECL_9QUE,1;
		setquest 1214;
		close;
	case 1:
		mes "[プロフェッサーワーム]";
		mes "この部屋の本棚にある本のどこかに";
		mes "私の肖像画が挟まっているはずだ。";
		mes "頼んだぞ！";
		close;
	case 2:
		mes "[プロフェッサーワーム]";
		mes "おお、持ってきてくれたか。";
		mes "ありがとう。";
		mes "どれどれ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "……";
		cutin "ep14_pro_worm",3;
		next;
		mes "[プロフェッサーワーム]";
		mes "これか……私の元の姿。";
		mes "……";
		mes "たしかに、私だ。";
		mes "しかし、どうしてここまで";
		mes "変わってしまったんだ？";
		mes "ん……";
		next;
		mes "[プロフェッサーワーム]";
		mes "うっすら何かが、";
		mes "浮かんで……きたような……";
		mes "その時の天気、そして風景……";
		mes "そう、花が咲き始めた大地で……";
		mes "何かを集めていた……。";
		next;
		mes "[プロフェッサーワーム]";
		mes "そう……";
		mes "そうだ！";
		mes "^FF0000星模様キノコ^000000を集めていたんだ！";
		cutin "ep14_pro_worm",255;
		next;
		mes "[プロフェッサーワーム]";
		mes "何故キノコを集めていたんだろう……。";
		mes "おい、君。";
		mes "ちょっと花が咲き始めた大地に行って";
		mes "^FF0000星模様キノコ^000000を集めて来てくれないか。";
		next;
		mes "[プロフェッサーワーム]";
		mes "星模様キノコを見れば、";
		mes "記憶が戻る気がするんだ！";
		next;
		if(select("わかった","いやだ") == 2) {
			mes "[プロフェッサーワーム]";
			mes "私は名前さえ忘れているんだぞ！";
			mes "なんとか手伝おうとは思わんのか！";
			close;
		}
		mes "[プロフェッサーワーム]";
		mes "花が咲き始めた大地で";
		mes "^FF0000星模様キノコ^000000を20個集めて来るんだ。";
		mes "たくさんあった方がいい。";
		mes "^FF0000星模様キノコ^000000は";
		mes "ペタルが持っているはずだ。";
		mes "頼んだぞ！";
		next;
		mes "^FF0000‐星模様キノコは、このクエストを";
		mes "　受けている状態で対象モンスターを";
		mes "　討伐することで自動的に入手します。";
		mes "　所持アイテムの重量と種類数に";
		mes "　十分な余裕をもって";
		mes "　討伐してください‐^000000";
		next;
		mes "^FF0000‐また、パーティーメンバーが";
		mes "　対象モンスターを討伐した場合でも";
		mes "　星模様キノコを入手することが";
		mes "　できます‐^000000";
		set ECL_9QUE,3;
		chgquest 1215,1216;
		close;
	case 3:
		if(countitem(6542) < 20) {
			mes "[プロフェッサーワーム]";
			mes "^FF0000星模様キノコ^000000が足りないぞ！";
			mes "その時、私は何かをするために";
			mes "20個を集めていた。";
			mes "個数が足りないと、";
			mes "浮かんでくる内容も";
			mes "漠然としてしまうんだ！";
			next;
			mes "[プロフェッサーワーム]";
			mes "^FF0000星模様キノコ^000000は";
			mes "花が咲き始めた大地にうろついている";
			mes "ペタルから手に入れることが";
			mes "できるからな。";
			close;
		}
		mes "[プロフェッサーワーム]";
		mes "おお、^FF0000星模様キノコ^000000を20個";
		mes "集めて来てくれたか。ありがたい。";
		next;
		misceffect 72;
		mes "[プロフェッサーワーム]";
		mes "おお……記憶が";
		mes "戻って来る……来ている！";
		mes "……";
		mes "これを材料にして……";
		mes "そう……";
		mes "そうだ！　薬を作っていたんだ！";
		next;
		mes "[プロフェッサーワーム]";
		mes "ただ、良いことのために";
		mes "作っていたわけでは";
		mes "なかった気がするな。";
		mes "後は……";
		mes "何か、他にも材料があったな。";
		next;
		mes "[プロフェッサーワーム]";
		mes "よし！";
		mes "忘れる前にメモを取ろう。";
		mes "メモがあれば忘れないぞ。";
		mes "そうだな。壁にでも……";
		mes "ん？";
		next;
		mes "[プロフェッサーワーム]";
		mes "なんだこれは!!!";
		mes "落書きだらけじゃないか。";
		mes "誰がこんなにも落書きを";
		mes "したっていうんだ！";
		mes "え？";
		next;
		mes "[プロフェッサーワーム]";
		mes "おまえか!?　モンスター顔の";
		mes "おまえが書いたのか！？";
		next;
		menu "あなたの名前がありますよ……",-;
		emotion 23;
		mes "[プロフェッサーワーム]";
		mes "ああ！";
		mes "私の文字かこれは！";
		mes "そうか。過去の私が同じように";
		mes "メモを取っていたのか。";
		next;
		mes "[プロフェッサーワーム]";
		mes "ははっ。ははは……";
		mes "壁の落書きを見ても";
		mes "メモを取っていたことすら";
		mes "思い出せないとは……。";
		next;
		mes "[プロフェッサーワーム]";
		mes "すまんが君、";
		mes "壁に書かれている内容を読んで";
		mes "私に教えてくれないか。";
		mes "こんな状態では、";
		mes "うまく頭に入ってこない。";
		next;
		mes "‐壁のあらゆる場所に";
		mes "　プロフェッサーワームの落書きが";
		mes "　残されている。";
		mes "　これらを調べれば";
		mes "　タワーやビフロストに関する情報を";
		mes "　得る事ができそうだ‐";
		next;
		mes "‐^FF0000壁に書かれた落書きを全て調べよう。";
		mes "　全部で5つあるようだ^000000‐";
		delitem 6542,20;
		set ECL_9QUE,4;
		chgquest 1216,1217;
		close;
	case 4:
		if(ECL_9QUE_sub & 0x1F == 0x1F) {
			mes "[プロフェッサーワーム]";
			mes "落書きの内容を全て調査したのか？";
			next;
			mes "‐プロフェッサーワームに";
			mes "　調査した内容を報告した‐";
			next;
			mes "[プロフェッサーワーム]";
			mes "そうか、私が薬を製造して";
			mes "ビフロストを眠らせたのか。";
			mes "そして姿が虫に変わり、";
			mes "どんどん記憶力が失われつつあると。";
			mes "ふむ。";
			next;
			mes "[プロフェッサーワーム]";
			mes "ありがとう。";
			mes "しかし……うーむ。";
			mes "少し考える時間をくれないか。";
			next;
			mes "‐何か考えているようだ。";
			mes "　もう一度話しかけてみよう‐";
			set ECL_9QUE,5;
			set ECL_9QUE_sub,0;
			close;
		}
		mes "[プロフェッサーワーム]";
		mes "壁の色んな所に落書きがある。";
		mes "どうやら全て私が書いたようだ。";
		mes "壁を5か所ほど調査して";
		mes "落書きの内容を私に報告してくれ。";
		mes "気になる、とても気になって記憶が";
		mes "全部ぶっ飛びそうだよ。";
		close;
	case 5:
		mes "[プロフェッサーワーム]";
		mes "いやしかし";
		mes "さすが私の作ったモンスターだな。";
		mes "モンスターよ、君のお蔭で";
		mes "記憶が少しずつではあるが";
		mes "戻って来ているように感じるよ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "ただ、まだまだ謎は多い。";
		mes "何故私は、";
		mes "タワーに閉じこめられたままなんだ？";
		mes "何故私は、";
		mes "ビフロストを眠らせたんだ？";
		mes "何故なんだ？　ん？";
		next;
		menu "それを聞きたいんです！",-;
		mes "[プロフェッサーワーム]";
		mes "うるさい！　うるさいうるさい！";
		mes "ああ……ああ……";
		mes "頭が破裂しそうだ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "そうだ、今覚えていることを";
		mes "壁に書き残しておこう。";
		mes "うん……ん？　あれ……";
		next;
		menu "…………",-;
		mes "[プロフェッサーワーム]";
		mes "あ、ああ、そうだそうだ。";
		mes "今それを君に調べてもらったんだな。";
		mes "大丈夫だ。";
		emotion 4,"";
		next;
		mes "[プロフェッサーワーム]";
		mes "それならば後は……";
		mes "日記、か。";
		mes "そうだ！";
		mes "私が書いた日記があった！";
		next;
		mes "[プロフェッサーワーム]";
		mes "しかしあれは……";
		next;
		menu "見せてください",-;
		mes "[プロフェッサーワーム]";
		mes "それが……一般のノートではなく";
		mes "^0000FF日記カエル^000000という録音用のカエルを";
		mes "通じて録音していたんだよ。";
		mes "ただちょっとな……";
		next;
		mes "[プロフェッサーワーム]";
		mes "いや、実はイライラするたびに";
		mes "ぽんぽん投げ飛ばしていたせいで、";
		mes "色々な場所に散り散りに";
		mes "なってしまっているんだ……。";
		next;
		menu "……",-;
		mes "[プロフェッサーワーム]";
		mes "いや、カエルには悪い事をしたが、";
		mes "しょうがなかったんだ。";
		mes "ストレス発散だよ！";
		mes "もしも君が私の立場なら";
		mes "カエルだけではなく、すべてを";
		mes "投げ出していただろうよ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "ということでひとまずそのカエルを";
		mes "探してきて欲しいのだが、";
		mes "何も考えず投げつけていたからな……。";
		mes "カエル自身も動き回るだろうし。";
		mes "ふーむ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "そうだ、1階に";
		mes "日記カエルを最近投げたな。";
		mes "2匹くらい投げた気がするが……";
		mes "すまない。あまり覚えていない。";
		mes "まずはそいつを探してきてくれないか。";
		next;
		mes "[プロフェッサーワーム]";
		mes "君が見つけて来る間に";
		mes "私は他のカエルをどこに投げたか";
		mes "思い出すことにするよ。";
		mes "すまないがよろしく頼んだよ。";
		set ECL_9QUE,6;
		chgquest 1217,1223;
		close;
	case 6:
	case 7:
		mes "[プロフェッサーワーム]";
		mes "1階に日記カエルを";
		mes "何匹だったかな……2匹くらい";
		mes "投げつけた記憶がある。";
		next;
		mes "[プロフェッサーワーム]";
		mes "いやーあれはすごかった。";
		mes "ころころと";
		mes "よく転がっていたよ。";
		close;
	case 8:
		mes "[プロフェッサーワーム]";
		mes "おお、2匹見つかったか。";
		mes "すまないな。";
		next;
		mes "[プロフェッサーワーム]";
		mes "確かもう1つ……";
		mes "力いっぱい投げた日記カエルが";
		mes "大きく飛んでタワーの外に";
		mes "消えていった気がする。";
		mes "多分、タワーの周辺にいるはずだ。";
		close;
	case 9:
		mes "[プロフェッサーワーム]";
		mes "おぉ、戻ったか。ありがとう。";
		mes "うむ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "思い出せるのはここまでだ。";
		mes "後は思い出せそうにない。";
		next;
		mes "[プロフェッサーワーム]";
		mes "よし。";
		mes "ここまで集まった情報を整理するか。";
		mes "どれどれ……";
		next;
		mes "[プロフェッサーワーム]";
		mes "……";
		next;
		mes "[プロフェッサーワーム]";
		mes "あの方はビフロストの大地の持つ力を";
		mes "恐れていた。";
		mes "そこで私に命令して";
		mes "ビフロストを眠らせる事にした。";
		next;
		mes "[プロフェッサーワーム]";
		mes "私は命令に従って星模様キノコなどの";
		mes "材料を集めて薬を作り、";
		mes "ビフロストを眠らせる事に成功した。";
		next;
		mes "[プロフェッサーワーム]";
		mes "そしてしばらくの間、";
		mes "この地ビフロストタワーで";
		mes "様子を見守る事にした。";
		next;
		mes "[プロフェッサーワーム]";
		mes "色々不可解な事が起きたのは";
		mes "その時からだ。";
		mes "今では私の姿は虫のようになり";
		mes "自分が何者なのか、";
		mes "思い出すのもおぼつかない。";
		next;
		mes "[プロフェッサーワーム]";
		mes "……";
		next;
		mes "[プロフェッサーワーム]";
		mes "……";
		mes "…………";
		next;
		mes "[プロフェッサーワーム]";
		mes "……";
		mes "あの方……か。";
		next;
		mes "[プロフェッサーワーム]";
		mes "ああああ、駄目だ!!!";
		mes "駄目だ駄目だ駄目だ駄目だ！";
		next;
		mes "[プロフェッサーワーム]";
		mes "全く思いだせん！";
		mes "頭脳には自信があったんだが、";
		mes "何か強力な力に阻まれている気分だ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "くそっ、くそっ。";
		mes "絶対にあきらめないぞ。";
		mes "こうなったらとことん勝負してやる。";
		mes "かつて天才と呼ばれた私の";
		mes "底力を見せてやる!!!!";
		next;
		mes "[プロフェッサーワーム]";
		mes "君、ここまで本当に";
		mes "すまなかったな。";
		mes "解決こそしなかったが、";
		mes "少し正気を取り戻すことが出来た。";
		next;
		mes "[プロフェッサーワーム]";
		mes "これからは色々対策を取る事にする。";
		mes "忘れてしまう事が問題なら";
		mes "初めて聞いてもわかるように";
		mes "一からメモを取るようにするさ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "必ず解決するつもりだ。";
		mes "進展があった場合は";
		mes "また力を借りるかもしれない。";
		mes "その時は是非頼むよ。";
		next;
		mes "[プロフェッサーワーム]";
		mes "話が長くなってしまったな。";
		mes "少しばかりだがお礼をあげよう。";
		mes "ありがとう。";
		if(checkitemblank() == 0) {
			next;
			mes "[プロフェッサーワーム]";
			mes "おっと、荷物がいっぱいだな。";
			mes "少し荷物を整理してから、";
			mes "また話しかけてくれ。";
			close;
		}
		set ECL_9QUE,10;
		chgquest 1228,201605;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 1000000,0;
		getexp 0,1000000;
		getexp 0,1000000;
		getexp 0,1000000;
		getexp 0,1000000;
		getexp 0,1000000;
		getitem 6081,25;
		close;
	case 10:
		mes "[プロフェッサーワーム]";
		mes "記憶を戻す機会を見つけたら";
		mes "またお願いする事もあるだろうから";
		mes "その時にまた力になってくれ。";
		close;
	}
OnInit:
	waitingroom "プロフェッサーワームの記憶",0;
	end;
}

ecl_tdun04.gat,21,41,0	script	#pf	139,2,2,{
	if(ECL_9QUE == 1) {
		mes "‐肖像画を見つけた！‐";
		next;
		cutin "ep14_pro_worm",3;
		mes "‐今とはまったく違う姿だ。";
		mes "　肩に力が入っている。";
		mes "　自信に溢れるマジシャンのようだ。";
		mes "　紙が古過ぎるせいで";
		mes "　名前は消えている‐";
		next;
		mes "‐プロフェッサーワームに見せよう‐";
		cutin "ep14_pro_worm",255;
		set ECL_9QUE,2;
		chgquest 1214,1215;
		close;
	}
	if(ECL_9QUE == 2) {
		cutin "ep14_pro_worm",3;
		mes "‐プロフェッサーワームの肖像画を";
		mes "　見つけた場所だ‐";
		next;
		mes "‐早くプロフェッサーワームに";
		mes "　見せにいこう‐";
		cutin "ep14_pro_worm",255;
		close;
	}
	end;
}

ecl_tdun04.gat,37,21,0	duplicate(#pf)	#pf3	139,2,2

ecl_tdun04.gat,39,23,4	script	壁に書かれたメモ#1	844,{
	if(ECL_9QUE == 4) {
		if(ECL_9QUE_sub & 0x1F == 0x1F) {
			mes "‐全ての壁をチェックした。";
			mes "　プロフェッサーワームの元に戻ろう‐";
			close;
		}
		if(ECL_9QUE_sub & 0x1) {
			mes "‐この壁の殴り書きは一度読んだ。";
			mes "　後、4個、残っている‐";
			next;
			mes "　もう一度読んでみようか‐";
			next;
			if(select("読まない","もう一度読んでみる") == 1) {
				mes "‐その場を後にした‐";
				close;
			}
			mes "[壁の記録1]";
			mes "ビフロストを寝かせることに成功した。";
			mes "私の腕はやはり素晴らしい！";
			mes "だけど、なぜ私までもここに";
			mes "残らなければいけないんだ？";
			close;
		}
		mes "‐壁が殴り書きで埋め尽くされている。";
		mes "　一部内容が読み取れそうだ‐";
		next;
		if(select("読む","読まない") == 2) {
			mes "‐読まずにその場を後にした‐";
			close;
		}
		mes "‐殴り書きを読んでみた‐";
		next;
		mes "[壁の記録1]";
		mes "ビフロストを寝かせることに成功した。";
		mes "私の腕はやはり素晴らしい！";
		mes "だけど、なぜ私までもここに";
		mes "残らなければいけないんだ？";
		set ECL_9QUE_sub,ECL_9QUE_sub | 0x1;
		//setquest 1218;
		//compquest 1218;
		close;
	}
	if(ECL_9QUE == 5) {
		mes "‐この壁の殴り書きは一度読んだ。";
		mes "　もう一度読んでみようか‐";
		next;
		if(select("読まない","もう一度読んでみる") == 1) {
			mes "‐その場を後にした‐";
			close;
		}
		mes "[壁の記録1]";
		mes "ビフロストを寝かせることに成功した。";
		mes "私の腕はやはり素晴らしい！";
		mes "だけど、なぜ私までもここに";
		mes "残らなければいけないんだ？";
		close;
	}
	mes "‐壁に落書きが書いてある‐";
	close;
}

ecl_tdun04.gat,35,31,4	script	壁に書かれたメモ#2	844,{
	if(ECL_9QUE == 4) {
		if(ECL_9QUE_sub & 0x1F == 0x1F) {
			mes "‐全ての壁をチェックした。";
			mes "　プロフェッサーワームの元に戻ろう‐";
			close;
		}
		if(ECL_9QUE_sub & 0x2) {
			mes "‐この壁の殴り書きは一度読んだ。";
			mes "　後、4個、残っている‐";
			next;
			mes "　もう一度読んでみようか‐";
			next;
			if(select("読まない","もう一度読んでみる") == 1) {
				mes "‐その場を後にした‐";
				close;
			}
			mes "[壁の記録2]";
			mes "タワーに閉じ込もってから";
			mes "まだそれほど経過していないというのに";
			mes "どんどん昔の事を忘れている……。";
			mes "きっと眠りを拒否するビフロストの";
			mes "強い意志が";
			mes "私に影響を与えているんだろう。";
			next;
			mes "[壁の記録2]";
			mes "このままでは自分の名前まで";
			mes "忘れてしまうのでは無いかと";
			mes "不安になる……。";
			close;
		}
		mes "‐壁が殴り書きで埋め尽くされている。";
		mes "　一部内容が読み取れそうだ‐";
		next;
		if(select("読む","読まない") == 2) {
			mes "‐読まずにその場を後にした‐";
			close;
		}
		mes "‐殴り書きを読んでみた‐";
		next;
		mes "[壁の記録2]";
		mes "タワーに閉じ込もってから";
		mes "まだそれほど経過していないというのに";
		mes "どんどん昔の事を忘れている……。";
		mes "きっと眠りを拒否するビフロストの";
		mes "強い意志が";
		mes "私に影響を与えているんだろう。";
		next;
		mes "[壁の記録2]";
		mes "このままでは自分の名前まで";
		mes "忘れてしまうのでは無いかと";
		mes "不安になる……。";
		set ECL_9QUE_sub,ECL_9QUE_sub | 0x2;
		//setquest 1219;
		//compquest 1219;
		close;
	}
	if(ECL_9QUE == 5) {
		mes "‐この壁の殴り書きは一度読んだ。";
		mes "　もう一度読んでみようか‐";
		next;
		if(select("読まない","もう一度読んでみる") == 1) {
			mes "‐その場を後にした‐";
			close;
		}
		mes "[壁の記録2]";
		mes "タワーに閉じ込もってから";
		mes "まだそれほど経過していないというのに";
		mes "どんどん昔の事を忘れている……。";
		mes "きっと眠りを拒否するビフロストの";
		mes "強い意志が";
		mes "私に影響を与えているんだろう。";
		next;
		mes "[壁の記録2]";
		mes "このままでは自分の名前まで";
		mes "忘れてしまうのでは無いかと";
		mes "不安になる……。";
		close;
	}
	mes "‐壁に落書きが書いてある‐";
	close;
}

ecl_tdun04.gat,28,43,4	script	壁に書かれたメモ#3	844,{
	if(ECL_9QUE == 4) {
		if(ECL_9QUE_sub & 0x1F == 0x1F) {
			mes "‐全ての壁をチェックした。";
			mes "　プロフェッサーワームの元に戻ろう‐";
			close;
		}
		if(ECL_9QUE_sub & 0x4) {
			mes "‐この壁の殴り書きは一度読んだ。";
			mes "　後、4個、残っている‐";
			next;
			mes "　もう一度読んでみようか‐";
			next;
			if(select("読まない","もう一度読んでみる") == 1) {
				mes "‐その場を後にした‐";
				close;
			}
			mes "‐殴り書きを読んでみた‐";
			next;
			mes "[壁の記録3]";
			mes "私の姿が変化している！";
			mes "手も！　皮膚も！　ああ……！";
			mes "これは間違いない、虫の姿だ！";
			mes "私が虫に変わってしまうとは、";
			mes "どうしてこんなことが。";
			next;
			mes "[壁の記録3]";
			mes "これもビフロストのせいなのか？";
			mes "眠らせた報復として私に";
			mes "このような呪いをかけたのか？";
			mes "深い眠りに落ちたまま？";
			mes "そんなことはありえない……。";
			mes "まさかこんなことが！";
			close;
		}
		mes "‐壁が殴り書きで埋め尽くされている。";
		mes "　一部内容が読み取れそうだ‐";
		next;
		if(select("読む","読まない") == 2) {
			mes "‐読まずにその場を後にした‐";
			close;
		}
		mes "‐殴り書きを読んでみた‐";
		next;
		mes "[壁の記録3]";
		mes "私の姿が変化している！";
		mes "手も！　皮膚も！　ああ……！";
		mes "これは間違いない、虫の姿だ！";
		mes "私が虫に変わってしまうとは、";
		mes "どうしてこんなことが。";
		next;
		mes "[壁の記録3]";
		mes "これもビフロストのせいなのか？";
		mes "眠らせた報復として私に";
		mes "このような呪いをかけたのか？";
		mes "深い眠りに落ちたまま？";
		mes "そんなことはありえない……。";
		mes "まさかこんなことが！";
		set ECL_9QUE_sub,ECL_9QUE_sub | 0x4;
		//setquest 1220;
		//compquest 1220;
		close;
	}
	if(ECL_9QUE == 5) {
		mes "‐この壁の殴り書きは一度読んだ。";
		mes "　もう一度読んでみようか‐";
		next;
		if(select("読まない","もう一度読んでみる") == 1) {
			mes "‐その場を後にした‐";
			close;
		}
		mes "[壁の記録3]";
		mes "私の姿が変化している！";
		mes "手も！　皮膚も！　ああ……！";
		mes "これは間違いない、虫の姿だ！";
		mes "私が虫に変わってしまうとは、";
		mes "どうしてこんなことが。";
		next;
		mes "[壁の記録3]";
		mes "これもビフロストのせいなのか？";
		mes "眠らせた報復として私に";
		mes "このような呪いをかけたのか？";
		mes "深い眠りに落ちたまま？";
		mes "そんなことはありえない……。";
		mes "まさかこんなことが！";
		close;
	}
	mes "‐壁に落書きが書いてある‐";
	close;
}

ecl_tdun04.gat,38,37,4	script	壁に書かれたメモ#4	844,{
	if(ECL_9QUE == 4) {
		if(ECL_9QUE_sub & 0x1F == 0x1F) {
			mes "‐全ての壁をチェックした。";
			mes "　プロフェッサーワームの元に戻ろう‐";
			close;
		}
		if(ECL_9QUE_sub & 0x8) {
			mes "‐この壁の殴り書きは一度読んだ。";
			mes "　後、4個、残っている‐";
			next;
			mes "　もう一度読んでみようか‐";
			next;
			if(select("読まない","もう一度読んでみる") == 1) {
				mes "‐その場を後にした‐";
				close;
			}
			mes "[壁の記録4]";
			mes "ビフロストの頭が伸び続けている。";
			mes "バカな！　こんなことはありえん……。";
			mes "もうタワーの高さを超えている！";
			mes "どういうことなんだ。";
			next;
			mes "[壁の記録4]";
			mes "眠りにつけなかった彼女の";
			mes "何かのメッセージなのだろうか。";
			mes "また一つ謎が増えた。";
			close;
		}
		mes "‐壁が殴り書きで埋め尽くされている。";
		mes "　一部内容が読み取れそうだ‐";
		next;
		if(select("読む","読まない") == 2) {
			mes "‐読まずにその場を後にした‐";
			close;
		}
		mes "‐殴り書きを読んでみた‐";
		next;
		mes "[壁の記録4]";
		mes "ビフロストの頭が伸び続けている。";
		mes "バカな！　こんなことはありえん……。";
		mes "もうタワーの高さを超えている！";
		mes "どういうことなんだ。";
		next;
		mes "[壁の記録4]";
		mes "眠りにつけなかった彼女の";
		mes "何かのメッセージなのだろうか。";
		mes "また一つ謎が増えた。";
		set ECL_9QUE_sub,ECL_9QUE_sub | 0x8;
		//setquest 1221;
		//compquest 1221;
		close;
	}
	if(ECL_9QUE == 5) {
		mes "‐この壁の殴り書きは一度読んだ。";
		mes "　もう一度読んでみようか‐";
		next;
		if(select("読まない","もう一度読んでみる") == 1) {
			mes "‐その場を後にした‐";
			close;
		}
		mes "[壁の記録4]";
		mes "ビフロストの頭が伸び続けている。";
		mes "バカな！　こんなことはありえん……。";
		mes "もうタワーの高さを超えている！";
		mes "どういうことなんだ。";
		next;
		mes "[壁の記録4]";
		mes "眠りにつけなかった彼女の";
		mes "何かのメッセージなのだろうか。";
		mes "また一つ謎が増えた。";
		close;
	}
	mes "‐壁に落書きが書いてある‐";
	close;
}

ecl_tdun04.gat,24,31,4	script	壁に書かれたメモ#5	844,{
	if(ECL_9QUE == 4) {
		if(ECL_9QUE_sub & 0x1F == 0x1F) {
			mes "‐全ての壁をチェックした。";
			mes "　プロフェッサーワームの元に戻ろう‐";
			close;
		}
		if(ECL_9QUE_sub & 0x10) {
			mes "‐この壁の殴り書きは一度読んだ。";
			mes "　後、4個、残っている‐";
			next;
			mes "　もう一度読んでみようか‐";
			next;
			if(select("読まない","もう一度読んでみる") == 1) {
				mes "‐その場を後にした‐";
				close;
			}
			mes "[壁の記録5]";
			mes "駄目だ……。";
			mes "次に被害を受けるのは";
			mes "私以外考えられない……。";
			mes "いつもどこかで誰かに";
			mes "見られている気がする。";
			next;
			mes "[壁の記録5]";
			mes "このまま黙って";
			mes "やられるわけにはいかない。";
			mes "モンスターを……。";
			mes "私を守ってくれるモンスターを";
			mes "作らなければ。";
			mes "もっと、もっと。一匹でも多く！";
			close;
		}
		mes "プロフェッサーワームの記録が壁を";
		mes "うめている。";
		mes "一部内容を読み取れそうだ。";
		next;
		if(select("読む","読まない") == 2) {
			mes "‐読まずにその場を後にした‐";
			close;
		}
		mes "記録を読むことにする。";
		next;
		mes "[壁の記録5]";
		mes "駄目だ……。";
		mes "次に被害を受けるのは";
		mes "私以外考えられない……。";
		mes "いつもどこかで誰かに";
		mes "見られている気がする。";
		next;
		mes "[壁の記録5]";
		mes "このまま黙って";
		mes "やられるわけにはいかない。";
		mes "モンスターを……。";
		mes "私を守ってくれるモンスターを";
		mes "作らなければ。";
		mes "もっと、もっと。一匹でも多く！";
		set ECL_9QUE_sub,ECL_9QUE_sub | 0x10;
		//setquest 1222;
		//compquest 1222;
		close;
	}
	if(ECL_9QUE == 5) {
		mes "‐この壁の殴り書きは一度読んだ。";
		mes "　もう一度読んでみようか‐";
		next;
		if(select("読まない","もう一度読んでみる") == 1) {
			mes "‐その場を後にした‐";
			close;
		}
		mes "[壁の記録5]";
		mes "駄目だ……。";
		mes "次に被害を受けるのは";
		mes "私以外考えられない……。";
		mes "いつもどこかで誰かに";
		mes "見られている気がする。";
		next;
		mes "[壁の記録5]";
		mes "このまま黙って";
		mes "やられるわけにはいかない。";
		mes "モンスターを……。";
		mes "私を守ってくれるモンスターを";
		mes "作らなければ。";
		mes "もっと、もっと。一匹でも多く！";
		close;
	}
	mes "‐壁に落書きが書いてある‐";
	close;
}

ecl_tdun01.gat,27,80,5	script	日記カエル3号#worm	614,{
	if(ECL_9QUE == 6) {
		mes "‐カエルがいる。";
		mes "　プロフェッサーワームの投げた";
		mes "　カエルのようだ。";
		mes "　話を聞いてみよう‐";
		close2;
		warp "ecl_tdun01a.gat",29,80;
		end;
	}
	if(ECL_9QUE >= 7) {
		mes "‐もう一度";
		mes "　カエルの話を聞きますか？‐";
		next;
		if(select("はい","いいえ") == 2) {
			mes "‐やめておこう‐";
			close;
		}
		mes "‐話を聞くことにした‐";
		close2;
		warp "ecl_tdun01a.gat",29,80;
		end;
	}
	mes "[日記カエル3号]";
	mes "プロフェッサーワームが";
	mes "私をここに投げました。";
	mes "機嫌が悪いと私たちを";
	mes "放り投げるんです。";
	close;
}

ecl_tdun01a.gat,27,80,5	script	日記カエル3号#copyworm	614,{
	if(ECL_9QUE == 6) {
		mes "[日記カエル3号]";
		mes "プロフェッサーワームが";
		mes "私をここに投げました。";
		mes "機嫌が悪いと私たちを";
		mes "放り投げるんです。";
		next;
		menu "日記カエルですか？",-;
		mes "[日記カエル3号]";
		mes "木で作られた録音用のカエルです。";
		mes "プロフェッサーワームの作品です。";
		mes "極限の寂しさがこのような発明品を";
		mes "誕生させたんです。";
		mes "意外な才能です。";
		next;
		menu "録音内容を聞かせてください",-;
		mes "[日記カエル3号]";
		mes "わかりました。聞かせてあげますね。";
		mes "プロフェッサーワームの声を";
		mes "真似しないといけないから";
		mes "まずはのどを調整しないと……";
		mes "アー、アー……あー。";
		next;
		mes "[3号が聞かせてくれる日記内容]";
		mes "……あの方は、あの方は";
		mes "ビフロストを恐れていたんだ！";
		mes "いつかは自身を威嚇するはずだと";
		mes "除去しないといけないと言っていたよ！";
		next;
		mes "[3号が聞かせてくれる日記内容]";
		mes "あの方が、あの方が！あああ～。";
		mes "ただ……あの方が思い出せない……";
		next;
		mes "[日記カエル3号]";
		mes "保存された記録はここまでです。";
		set ECL_9QUE,7;
		chgquest 1223,1224;
		close2;
		warp "ecl_tdun01.gat",29,80;
		end;
	}
	if(ECL_9QUE >= 7) {
		mes "[日記カエル3号]";
		mes "日記内容が気になりますか。";
		mes "もう一度聞きますか？";
		while(1) {
			next;
			switch(select("他の日記カエルの事を聞く","日記内容をもう一度聞く","他の内容が無いか聞く","もう用は無い")) {
			case 1:
				mes "[日記カエル3号]";
				mes "そこの日記カエル6号は";
				mes "私が投げられた後に";
				mes "ここに投げられてきました。";
				break;
			case 2:
				mes "[日記カエル3号]";
				mes "わかりました。聞かせてあげますね。";
				mes "プロフェッサーワームの声を";
				mes "真似しないといけないから";
				mes "まずはのどを調整しないと……";
				mes "アー、アー……あー。";
				next;
				mes "[3号が聞かせてくれる日記内容]";
				mes "……あの方は、あの方は";
				mes "ビフロストを恐れていたんだ！";
				mes "いつかは自身を威嚇するはずだと";
				mes "除去しないといけないと言っていたよ！";
				next;
				mes "[3号が聞かせてくれる日記内容]";
				mes "あの方が、あの方が！あああ～。";
				mes "ただ……あの方が思い出せない……";
				next;
				mes "[日記カエル3号]";
				mes "保存された記録はここまでです。";
				break;
			case 3:
				mes "[日記カエル3号]";
				mes "本当はもっとありました。";
				mes "ただ、記憶は私の燃料に保存される為";
				mes "他の情報はお腹の中に消えました。";
				mes "生きて行くためなので";
				mes "どうすることもできません。";
				emotion 19,"";
				break;
			case 4:
				mes "[日記カエル3号]";
				mes "そうですか。";
				close2;
				warp "ecl_tdun01.gat",29,80;
				end;
			}
		}
	}
}

ecl_tdun01.gat,23,79,4	script	日記カエル6号#worm	614,{
	if(ECL_9QUE == 7) {
		mes "‐カエルがいる。";
		mes "　プロフェッサーワームの投げた";
		mes "　カエルのようだ。";
		mes "　話を聞いてみよう‐";
		close2;
		warp "ecl_tdun01a.gat",29,80;
		end;
	}
	if(ECL_9QUE >= 8) {
		mes "‐もう一度";
		mes "　カエルの話を聞きますか？‐";
		next;
		if(select("はい","いいえ") == 2) {
			mes "‐やめておこう‐";
			close;
		}
		mes "‐話を聞くことにした‐";
		close2;
		warp "ecl_tdun01a.gat",29,80;
		end;
	}
	mes "[日記カエル6号]";
	mes "プロフェッサーワームが";
	mes "私をここに投げつけやがった！";
	mes "モンスターがいるこんな場所に！";
	close;
}

ecl_tdun01a.gat,23,79,4	script	日記カエル6号#copyworm	614,{
	if(ECL_9QUE == 7) {
		if(checkquest(1225)) {
			if(checkquest(1225) & 0x4) {
				mes "[日記カエル6号]";
				mes "おお。";
				mes "^FF0000ヴァッサー・リヒテルン^000000を15匹";
				mes "退治してきてくれたか。";
				mes "これでやっと安心できる。";
				mes "約束した通り日記を聞かせてやろう！";
				next;
				mes "[日記カエル6号]";
				mes "プロフェッサーワームの声を";
				mes "真似しないといけないから";
				mes "まずはのどを調整しないと……";
				mes "ふん……ふんふん！";
				next;
				mes "[6号が聞かせてくれる日記内容]";
				mes "あの方はこう仰られた。";
				mes "ビフロストを寝かした後は";
				mes "ここに残りその様子を見張りなさいと。";
				mes "決して起きてしまわぬよう監視しろと。";
				mes "途中で起きたら私の責任だと。";
				next;
				mes "[6号が聞かせてくれる日記内容]";
				mes "その言葉を言いつかってから";
				mes "もうすでに数十年、";
				mes "経ってしまった……。";
				next;
				mes "[6号が聞かせてくれる日記内容]";
				mes "……。";
				mes "…………。";
				mes "あああ、怒りが湧いてくる！";
				mes "イライラする!!!";
				mes "何故私だけがこんな事を";
				mes "続けていないといけないんだ！";
				next;
				mes "[6号が聞かせてくれる日記内容]";
				mes "ああ！　起こしてやりたい！";
				mes "あああ……！　頭が…割れる!!";
				mes "起こしてやる……起こして……";
				mes "ん……起こしてどうするんだ？";
				mes "ん、そもそも誰を起こすんだ？";
				next;
				mes "[6号が聞かせてくれる日記内容]";
				mes "何だこれは。カエル……";
				mes "こいつを起こすのか？　いや……";
				mes "ああ……頭が……！";
				mes "もういい!!!";
				mes "とりあえずこのカエルを";
				mes "どこか遠くに投げつけてやる！";
				next;
				mes "[日記カエル6号]";
				mes "日記はここまでだ。";
				mes "そして、俺をここまで";
				mes "投げ飛ばしてしまったんだ。";
				next;
				mes "[日記カエル6号]";
				mes "他の日記カエルはおそらく";
				mes "タワーの外側のどこかにいるだろう。";
				mes "誰かが持っていったりしていなければ";
				mes "すぐ見つける事ができるだろう。";
				set ECL_9QUE,8;
				chgquest 1225,1226;
				close2;
				warp "ecl_tdun01.gat",29,80;
				end;
			}
			mes "[日記カエル6号]";
			mes "^FF0000ヴァッサー・リヒテルン^000000を15匹";
			mes "退治して来たら、";
			mes "プロフェッサーワームの日記を";
			mes "聞かせてやるよ。";
			close2;
			warp "ecl_tdun01.gat",29,80;
			end;
		}
		mes "[日記カエル6号]";
		mes "何だお前は。何の用だ。";
		next;
		mes "[日記カエル6号]";
		mes "なんだと？";
		mes "プロフェッサーワームが";
		mes "私を探していた？　ばかな。";
		mes "必要なくなったから捨てたんだろう！";
		mes "おもいっきり投げ飛ばしたよ私を！";
		next;
		menu "怪我は無さそうですね",-;
		mes "[日記カエル6号]";
		mes "怪我の問題じゃないよ!!!";
		mes "君も捨てられると";
		mes "私の気持ちを理解できるだろうね！";
		mes "で、何の用なんだい？";
		next;
		menu "日記の内容を聞かせて欲しい",-;
		mes "[日記カエル6号]";
		mes "あぁん？";
		mes "他人の日記になぜ興味があるんだ？";
		next;
		mes "[日記カエル6号]";
		mes "そうだ。こうしよう。";
		mes "俺の頼みを聞いてくれたら";
		mes "日記を聞かせてあげるぜ。";
		next;
		mes "[日記カエル6号]";
		mes "実は一つ困っている事がある。";
		mes "これもまたあいつのせいなんだが、";
		mes "プロフェッサーワームがばらまいた";
		mes "モンスターたちが";
		mes "俺に噛みついてくるんだ。";
		next;
		mes "[日記カエル6号]";
		mes "中でも^FF0000ヴァッサー・リヒテルン^000000という";
		mes "モンスターが";
		mes "よく寄ってきて困ってるんだよ。";
		next;
		mes "[日記カエル6号]";
		mes "頼みはわかるな？";
		mes "そいつらを退治してきてほしいんだ。";
		mes "^FF0000ヴァッサー・リヒテルン^000000を15匹";
		mes "退治して来てくれたら";
		mes "気持ちよく日記を聞かせてやるよ。";
		next;
		if(select("退治を手伝う","断る") == 1) {
			mes "[日記カエル6号]";
			mes "ふん。そうかい。";
			mes "それなら、俺も日記に関しては";
			mes "一言も言わない様にさせてもらう。";
			close2;
			warp "ecl_tdun01.gat",29,80;
			end;
		}
		mes "[日記カエル6号]";
		mes "よおし、じゃあ早く行って来てくれ。";
		mes "分かっているよね？";
		mes "記憶は私の燃料に";
		mes "保存されているという事を。";
		mes "さぁ！　急いで退治してきてくれ！";
		chgquest 1224,1225;
		close2;
		warp "ecl_tdun01.gat",29,80;
		end;
	}
	if(ECL_9QUE >= 8) {
		mes "[日記カエル6号]";
		mes "日記の内容をまた聞きたいか？";
		mes "モンスターを退治してくれたからな！";
		mes "いくらでも聞かせてやるよ。";
		next;
		switch(select("他の日記カエルの事を聞く","日記内容をもう一度聞く")) {
		case 1:
			mes "[日記カエル6号]";
			mes "他の日記カエルはおそらく";
			mes "タワーの外側のどこかにいるだろう。";
			mes "誰かが持っていったりしていなければ、";
			mes "すぐ見つける事ができるだろう。";
			close;
		case 2:
			mes "[日記カエル6号]";
			mes "よぉし、任せておけ。";
			mes "プロフェッサーワームの声を";
			mes "真似しないといけないから";
			mes "まずはのどを調整しないと……";
			mes "ふん……ふんふん！";
			next;
			mes "[6号が聞かせてくれる日記内容]";
			mes "あの方はこう仰られた。";
			mes "ビフロストを寝かした後は";
			mes "ここに残りその様子を見張りなさいと。";
			mes "決して起きてしまわぬよう監視しろと。";
			mes "途中で起きたら私の責任だと。";
			next;
			mes "[6号が聞かせてくれる日記内容]";
			mes "その言葉を言いつかってから";
			mes "もうすでに数十年、";
			mes "経ってしまった……。";
			next;
			mes "[6号が聞かせてくれる日記内容]";
			mes "……。";
			mes "…………。";
			mes "あああ、怒りが湧いてくる！";
			mes "イライラする!!!";
			mes "何故私だけがこんな事を";
			mes "続けていないといけないんだ！";
			next;
			mes "[6号が聞かせてくれる日記内容]";
			mes "ああ！起こしてやりたい！";
			mes "あああ……！　頭が…割れる!!";
			mes "起こしてやる……起こして……";
			mes "ん……起こしてどうするんだ？";
			mes "ん、そもそも誰を起こすんだ？";
			next;
			mes "[6号が聞かせてくれる日記内容]";
			mes "何だこれは。カエル……";
			mes "こいつを起こすのか？いや……";
			mes "ああ……頭が……！";
			mes "もういい!!!";
			mes "とりあえずこのカエルを";
			mes "どこか遠くに投げつけてやる！";
			next;
			mes "[日記カエル6号]";
			mes "日記はここまでだ。";
			mes "そして、俺をここまで";
			mes "投げとばしてしまったんだ。";
			close2;
			warp "ecl_tdun01.gat",29,80;
			end;
		}
	}
	mes "[日記カエル6号]";
	mes "何だお前は。何の用だ。";
	mes "私は今傷ついているんだ。";
	mes "帰れ帰れ。";
	close2;
	warp "ecl_tdun01.gat",29,80;
	end;
}

ecl_fild01.gat,173,95,7	script	日記カエル30号#worm	614,{
	if(ECL_9QUE == 8) {
		if(checkquest(1227)) {
			if(countitem(6542) < 10) {
				mes "[日記カエル30号]";
				mes "^FF0000星模様キノコ^000000を10個";
				mes "集めてきてください。";
				mes "花が咲き始めた大地にいる";
				mes "ペタルから";
				mes "手に入れることができます。";
				close;
			}
			mes "[日記カエル30号]";
			mes "^FF0000星模様キノコ^000000を10個";
			mes "集めてくれたんですね。";
			mes "ありがとうございます。";
			mes "まずは治療を行いますので";
			mes "このまま、少し待って下さい。";
			next;
			mes "[日記カエル30号]";
			mes "‐もみもみ";
			mes "　べたべた‐";
			next;
			mes "[日記カエル30号]";
			mes "ああ、体の調子がよくなりました。";
			mes "完全によくなりました。";
			mes "全部なおりました。";
			mes "怪我などしていなかったかのようです。";
			mes "いいえ、";
			next;
			mes "[日記カエル30号]";
			mes "怪我などしていませんでした。";
			next;
			mes "[日記カエル30号]";
			mes "もともと怪我などしていなかったので";
			mes "治療もしていませんね。";
			mes "星模様キノコなんて貰っていません。";
			next;
			mes "[日記カエル30号]";
			mes "なーんだ、全部悪い夢だったのか。";
			mes "ああ、よかったよかった。";
			mes "解決しました。";
			next;
			menu "鷲掴みにして放り投げる",-,"思いっきり蹴り飛ばす",-;
			mes "[日記カエル30号]";
			mes "ああ、待ってください。";
			mes "冗談です、冗談です。";
			mes "そんなに怒らないでください。";
			mes "すぐに日記の内容を再生しますので";
			mes "ちょっとおまちください。";
			next;
			mes "[日記カエル30号]";
			mes "プロフェッサーワームの声を";
			mes "真似しないといけないので、";
			mes "まずはのどを調整しないと……";
			mes "んっ……んっー……んがっ！";
			next;
			mes "[30号が聞かせてくれる日記内容]";
			mes "すごい！　すごいぞ!!!";
			mes "この塔には凄い秘密が隠されていた！";
			mes "ああ、驚いた。本当に驚いた！";
			mes "数百年にかけて守られていた秘密を";
			mes "私は解いてしまった！";
			mes "分かってしまった！";
			next;
			mes "[30号が聞かせてくれる日記内容]";
			mes "ただ、あまりにも衝撃的な内容で";
			mes "全部真っ白に忘れてしまった！";
			next;
			mes "[30号が聞かせてくれる日記内容]";
			mes "このカエル！";
			mes "イライラして来たから";
			mes "また投げちゃう！　えいっ";
			next;
			mes "‐これ以上の日記集めは";
			mes "　意味がなさそうだ。";
			mes "　プロフェッサーワームに";
			mes "　報告にいこう‐";
			delitem 6542,10;
			set ECL_9QUE,9;
			chgquest 1227,1228;
			close;
		}
		mes "[日記カエル30号]";
		mes "見ての通り私は";
		mes "壊れた日記カエルです。";
		mes "プロフェッサーワームが";
		mes "私をここまで投げました。";
		mes "特に悪いこともしていないのに！";
		next;
		menu "大丈夫ですか",-;
		mes "[日記カエル30号]";
		mes "大丈夫じゃないです。";
		mes "もう何もかもやる気がでません。";
		mes "ここで燃料が尽きるのを待つだけです。";
		next;
		menu "そういわず日記の内容を聞かせて下さい",-;
		mes "[日記カエル30号]";
		mes "投げ出された時に怪我をしました。";
		mes "もう無理です。";
		mes "日記を読む力が出せません。";
		mes "どうしようもありません。";
		next;
		mes "[日記カエル30号]";
		mes "ただ、もしもあなたが";
		mes "治療のために花が咲き始めた大地で";
		mes "^FF0000星模様キノコ^000000を10個";
		mes "集めて来てくれるのであれば";
		mes "元気になるかもしれません。";
		next;
		if(select("集めてくる","いいから日記内容を聞かせてくれ") == 2) {
			mes "[日記カエル30号]";
			mes "そうですか……。";
			mes "それでは私があなたに";
			mes "聞かせてあげられるのは";
			mes "叫び声しかなさそうですね。";
			next;
			mes "[日記カエル30号]";
			mes "うわああああああ";
			mes "あああああああ";
			mes "あああああ";
			mes "ああああ";
			mes "あああ";
			close;
		}
		mes "[日記カエル30号]";
		mes "^FF0000星模様キノコ^000000は";
		mes "花が咲き始めた大地にいる";
		mes "ペタルから手に入れることができます。";
		next;
		mes "[日記カエル30号]";
		mes "分かっていますよね？";
		mes "私の燃料は記憶だということ。";
		mes "戻りが遅いと私の泣き声しか";
		mes "聞けなくなりますよ。";
		next;
		mes "^FF0000‐星模様キノコは、このクエストを";
		mes "　受けている状態で対象モンスターを";
		mes "　討伐することで自動的に入手します。";
		mes "　所持アイテムの重量と種類数に";
		mes "　十分な余裕をもって";
		mes "　討伐してください‐^000000";
		next;
		mes "^FF0000‐また、パーティーメンバーが";
		mes "　対象モンスターを討伐した場合でも";
		mes "　星模様キノコを入手することが";
		mes "　できます‐^000000";
		chgquest 1226,1227;
		close;
	}
	if(ECL_9QUE >= 9) {
		mes "[日記カエル30号]";
		mes "また来たのですか。";
		mes "もう一度日記の内容を聞きますか？";
		next;
		switch(select("他の日記カエルの事を聞く","日記内容をもう一度聞く")) {
		case 1:
			mes "[日記カエル30号]";
			mes "これ以上残っているカエルは";
			mes "いないと思います。";
			mes "モンスターに食べられたか、";
			mes "投げられた時に壊れてしまいました。";
			close;
		case 2:
			mes "[日記カエル30号]";
			mes "すぐに日記の内容を再生しますので";
			mes "ちょっとおまちください。";
			next;
			mes "[日記カエル30号]";
			mes "プロフェッサーワームの声を";
			mes "真似しないといけないので、";
			mes "まずはのどを調整しないと……";
			mes "んっ……んっー……んがっ！";
			next;
			mes "[30号が聞かせてくれる日記内容]";
			mes "すごい！　すごいぞ!!!";
			mes "この塔には凄い秘密が隠されていた！";
			mes "ああ、驚いた。本当に驚いた！";
			mes "数百年にかけて守られていた秘密を";
			mes "私は解いてしまった！";
			mes "分かってしまった！";
			next;
			mes "[30号が聞かせてくれる日記内容]";
			mes "ただ、あまりにも衝撃的な内容で";
			mes "全部真っ白に忘れてしまった！";
			next;
			mes "[30号が聞かせてくれる日記内容]";
			mes "このカエル！";
			mes "イライラして来たから";
			mes "また投げちゃう！　えいっ";
			next;
			mes "‐これ以上の日記集めは";
			mes "　意味がなさそうだ。";
			mes "　プロフェッサーワームに";
			mes "　報告にいこう‐";
			close;
		}
	}
	mes "[日記カエル30号]";
	mes "見ての通り私は";
	mes "壊れた日記カエルです。";
	mes "プロフェッサーワームが";
	mes "私をここまで投げました。";
	mes "特に悪いこともしていないのに！";
	close;
}
