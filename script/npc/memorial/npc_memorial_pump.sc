//= Auriga Script ==============================================================
// Ragnarok Online Malangdo Pump Script	by Blaze
//- Registry -------------------------------------------------------------------
// PUMP_1QUE -> 0～3
//==============================================================================

//============================================================
// NPC
//------------------------------------------------------------
mal_in01.gat,172,28,2	script	アルボ	561,{
	mes "[アルボ]";
	mes "我々はあそこに立っている";
	mes "ミシン様の部下だった。";
	mes "以前はこの保管庫の";
	mes "管理を行っていたのだ。";
	next;
	mes "[アルボ]";
	mes "だがある日、";
	mes "大きな揺れとともに浸水が始まった。";
	mes "保管庫は水浸しになり、";
	mes "保管してあった貴重品は";
	mes "すべて流れてしまったのだ！";
	next;
	mes "[アルボ]";
	mes "流れていった先は排水路になっている。";
	mes "浸水はそこに潜んでいる奴らの仕業に";
	mes "違いないのだ！";
	next;
	mes "[アルボ]";
	mes "さらに奴らは！";
	mes "浸水を防ごうとしている";
	mes "ミシン様の邪魔をし！";
	mes "あまつさえミシン様を冒涜したのだ!!";
	next;
	mes "[アルボ]";
	mes "我々は奴らを絶対に許さない！";
	mes "あのモンスターどもは、";
	mes "最後の一匹まで刺身にして";
	mes "ワサビをつけて食ってやる!!";
	next;
	mes "^0000ff-ニャーと言いながら全身の毛を立て、";
	mes "　地下排水路に向け";
	mes "　怒りを露わにしている-^000000";
	close;
}

mal_in01.gat,172,26,2	script	マデカ	544,{
	mes "[マデカ]";
	mes "ニャーニャー!!!!";
	mes "悪い海産物は";
	mes "茹でたり焼いたりして";
	mes "食べちゃうニャー！";
	close;
}

//============================================================
// ダンジョン生成NPC
//------------------------------------------------------------
mal_in01.gat,160,34,4	script	保管庫の管理人ミシン	545,{
	if(BaseLevel < 40) {
		mes "[保管庫の管理人ミシン]";
		mes "ニャー、";
		mes "何の用件かはわからないけど";
		mes "この先は行っちゃダメニャ。";
		mes "トーマス提督の命令ニャ。";
		next;
		mes "-このクエストを進行するには";
		mes "　レベルが満たないようです。";
		mes "　^ff0000Baseレベル40以上^000000になったら";
		mes "　再度話しかけてください-";
		close;
	}
	if(PUMP_1QUE == 0) {
		mes "[保管庫の管理人ミシン]";
		mes "ニャニャニャア……。";
		mes " ";
		mes "-ひどく疲れている猫がいる。";
		mes "　毛皮でわかりにくいが、";
		mes "　血色も良くないようだ-";
		next;
		if(select("ヒゲをひっぱる","どうしたのか聞く")==1) {
			mes "[保管庫の管理人ミシン]";
			mes "ニャーーー!!!?";
			mes " ";
			mes "-あなたがヒゲをひっぱると、";
			mes "　猫は垂直に飛び上がった-";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "な、何をするニャ!!";
			mes "ミシンは一所懸命^ff0000地下排水路^000000からの";
			mes "浸水を食い止めているニャ！";
			mes "地下排水路は危険なのニャ！";
			mes "邪魔するなニャ！";
			close;
		}
		emotion 54;
		mes "[保管庫の管理人ミシン]";
		mes "ついさっきまで";
		mes "^ff0000地下排水路^000000の掃除をしてたニャ。";
		mes "いつものことニャア。";
		mes " ";
		mes "-猫はため息をついた-";
		next;
		menu "地下排水路？",-;
		mes "[保管庫の管理人ミシン]";
		mes "ニャア。";
		mes "元々、ここは貴重品をしまう";
		mes "保管庫だったニャ。";
		next;
		emotion 28;
		mes "[保管庫の管理人ミシン]";
		mes "でも、ある日、";
		mes "島が大きく揺れたと思ったら";
		mes "地下排水路からの浸水がおきて、";
		mes "保管庫が水浸しになったニャ。";
		mes "水浸しじゃ物を保管できないニャ……。";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "でも、ミシンは保管庫の管理人ニャ！";
		mes "諦めないニャ！";
		mes "地下排水路からの浸水を防いで、";
		mes "保管庫を復活させるために、";
		mes "今も走り回っているニャ！";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "……でも困っていることがあるにゃ。";
		mes "地下排水路には";
		mes "ミシンをバカにするやつらが";
		mes "潜んでいるのニャア……。";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "ミシンはやつらと戦っているニャ！";
		mes "得意の猫キックに猫パンチ！";
		mes "ミシンは強いニャ負けないニャア！";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "……。";
		mes "でも正直、戦うのに疲れてきたニャ。";
		mes "1日に何回も何十回も戦ってきたけど";
		mes "もう疲れが限界だニャア……。";
		next;
		menu "やめればいいじゃない",-;
		mes "[保管庫の管理人ミシン]";
		mes "それはいやニャ。";
		mes "ミシンはやつらを追い出して、";
		mes "浸水を止めて、";
		mes "保管庫を復活させるんだニャア。";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "それに、たまに保管庫に入れてた";
		mes "宝物を発見できたりするニャ。";
		mes "おいしい缶詰をゲットできるニャー。";
		next;
		if(select("頑張ってください。ではさようなら","自分も手伝うよ") == 1) {
			mes "[保管庫の管理人ミシン]";
			mes "ニャニャ、がんばるニャア！";
			mes "ミシンは保管庫を復活させるニャ。";
			close;
		}
		mes "[保管庫の管理人ミシン]";
		mes "ホントニャ？";
		mes "ウソいつわりないニャ？";
		next;
		if(select("はい","ごめんなさい。実は嘘です") == 2) {
			emotion 6;
			mes "[保管庫の管理人ミシン]";
			mes "嘘ニャ？";
			mes "嘘つきはどこかへ行くニャ!!";
			close;
		}
		mes "[保管庫の管理人ミシン]";
		mes "うれしいニャ!!";
		mes "本当にありがとうニャ！";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "では、君には地下排水路での";
		mes "掃除を手伝ってもらうニャ。";
		mes "掃除の詳しいやり方は";
		mes "その時になったら教えるニャ。";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "あと、地下排水路は掃除中に";
		mes "ミシンをバカにするやつらが";
		mes "邪魔をしてくる危険な場所ニャ。";
		mes "入るときは^ff0000パーティーを組んで、^000000";
		mes "ミシンと入場手続きをするニャ。";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "暗号を教えるから、";
		mes "入場手続きをするときはミシンに";
		mes "パーティーのボスが";
		mes "^ff0000この暗号^000000を言うニャ。";
		mes " ";
		mes "^990000『缶詰食べ過ぎお腹が出るにゃ』^000000";
		next;
		menu "缶詰食べ過ぎお腹が出るにゃ",-;
		mes "[保管庫の管理人ミシン]";
		mes "これを約束してくれるなら、";
		mes "ミシンは^ff0000地下排水路^000000に";
		mes "案内するニャア。";
		set PUMP_1QUE,1;
		close;
	}
	if(getonlinepartymember() < 1) {
		mes "[保管庫の管理人ミシン]";
		mes "ニャニャ、";
		mes "パーティーを作るか";
		mes "加入してないと";
		mes "^ff0000地下排水路^000000には入れられないニャ！";
		close;
	}
	if(checkquest(12254) || checkquest(71495)) {
		if(checkquest(12254)&2 == 0 || checkquest(71495)&2 == 0) {
			mes "[保管庫の管理人ミシン]";
			mes "今はお掃除しなくても大丈夫ニャ～。";
			mes "入場してから次の";
			mes "^ff0000午前5時以降^000000になったら";
			mes "また来てほしいのニャ。";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "但し、最後の入場をしてから";
			mes "^ff00001時間^000000経過するまでは";
			mes "お掃除しなくても大丈夫ニャ。";
			mes "もし、その前に来ても";
			mes "中には入れないから注意するニャ。";
			close;
		}
		delquest 12254;
		delquest 71495;
	}
	mes "[保管庫の管理人ミシン]";
	mes "どうしたニャ？";
	mes "ミシンにご用事？";
	next;
	while(1) {
		if(getpartyleader(getcharid(1)) == strcharinfo(0))
			set '@str$,"缶詰食べ過ぎお腹が出るにゃ";
		switch(select("地下排水路の行き方を聞きたい",'@str$,"地下排水路に行く","なんでもありません")) {
		case 1:
			mes "[保管庫の管理人ミシン]";
			mes "地下排水路の行き方かニャ？";
			mes "地下排水路に行くにはパーティーを";
			mes "組んでいる必要があるニャ。";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "地下排水路の入口を開きたければ、";
			mes "パーティーのボスが";
			mes "ミシンに暗号を言うニャ。";
			mes "そうしたらミシンが";
			mes "地下排水路の入口を開くニャ。";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "あと、地下排水路は、";
			mes "入場してから1回目の";
			mes "^ff0000午前5時^000000を迎えると";
			mes "もう一度入場できるようになるニャ。";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "但し、最後の入場をしてから";
			mes "^ff00001時間^000000経過しないと";
			mes "入場できないのニャ。";
			mes " ";
			mes "働きすぎは体に良くないニャ。";
			mes "最低でも1時間はゆっくり休むニャ。";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "他になにかあるかニャ？";
			next;
			continue;
		case 2:
			if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
				mes "[保管庫の管理人ミシン]";
				mes "ミシンと話している間に";
				mes "パーティーのボスじゃ";
				mes "なくなったのかニャ？";
				mes "ボスじゃなきゃ";
				mes "地下排水路は開けないニャ！";
				close;
			}
			mdcreate "Pump";
			mes "[保管庫の管理人ミシン]";
			mes "パーティー名が";
			mes getpartyname(getcharid(1))+ "。";
			mes "パーティーリーダーが";
			mes getpartyleader(getcharid(1))+ "だニャ。";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "^ff0000地下排水路^000000への入り口を";
			mes "開放するニャ。";
			mes "確認したら、もう一度";
			mes "ミシンに話しかけてニャ。";
			close;
		case 3:
			mes "-地下排水路に入場します-";
			close2;
			switch(mdenter("Pump")) {
			case 0:	// エラーなし
				announce "メモリアルダンジョン[Pump]に入場しました　：　" +strcharinfo(1)+ "（" +strcharinfo(0)+ "）",0x9,0x00FF99;
				setquest 12254;
				setquest 71495;
				delquest 97100;
				set PUMP_1QUE,1;	// エキスパートの討伐フラグを戻す
				end;
			case 1:	// パーティー未加入
				mes "[保管庫の管理人ミシン]";
				mes "ニャニャ……";
				mes "今、入り口を開けたパーティーに";
				mes "加入してないニャ。";
				mes "^ff0000地下排水路^000000には";
				mes "入っちゃダメニャ。";
				close;
			case 2:	// ダンジョン未作成
				mes "[保管庫の管理人ミシン]";
				mes "ニャニャ……";
				mes "^ff0000地下排水路^000000の入り口が";
				mes "うまく開かなかったニャ。";
				mes "パーティーリーダーがまだ";
				mes "暗号を言っていないのニャ。";
				close;
			default:	// その他エラー
				mes "[保管庫の管理人ミシン]";
				mes "ニャニャ……";
				mes "^ff0000地下排水路^000000の入り口が";
				mes "うまく開かなかったニャ。";
				close;
			}
		case 4:
			mes "[保管庫の管理人ミシン]";
			mes "なんでもないニャ？";
			close;
		}
	}
OnInit:
	waitingroom "地下排水路",0;
	end;
}

//============================================================
// 地下排水路（お掃除ビギナー）
//------------------------------------------------------------
1@pump.gat,63,100,4	script	保管庫の管理人ミシン#Pump0	545,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[保管庫の管理人ミシン]";
		mes "君達のボスと話をしているから、";
		mes "ちょっと待ってニャ。";
		close;
	}
	mes "[保管庫の管理人ミシン]";
	mes "ここは仲間たちと一緒に";
	mes "掃除をする地下排水路ニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "ところで君……";
	mes "掃除は得意かニャ？";
	mes "掃除のエキスパートさんなら、";
	mes "奥の部屋の掃除が";
	mes "できるかもしれないニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "そこは強いモンスターも出てくるし、";
	mes "掃除する箇所も多くて";
	mes "ちょっと難しいニャ。";
	mes "君はどれくらいお掃除できるニャ？";
	next;
	if(select("お掃除ビギナー","お掃除エキスパート(BaseLv90から選択可能)") == 1) {
		mes "[保管庫の管理人ミシン]";
		mes "分かったニャ。";
		mes "それならいつも掃除をしている";
		mes "この排水路の掃除を任せるニャ！";
		next;
		if(select("ちょっと待って","わかった") == 1) {
			mes "[保管庫の管理人ミシン]";
			mes "ん？まだ準備ができてないのかニャ？";
			mes "準備ができたら";
			mes "もう一度話しかけてほしいニャ。";
			close;
		}
		mes "[保管庫の管理人ミシン]";
		mes "右端に行って準備をするから";
		mes "ついて来るニャ！";
		hideonnpc;
		hideoffnpc getmdnpcname("保管庫の管理人ミシン#Pump1-1");
		announce "ミシン : マップの3時方向に移動した後、ミシンに話しかけるニャ！",0x9,0x00FFCC,0x190,15,0,0;
		close;
	}
	if(BaseLevel < 90) {
		mes "[保管庫の管理人ミシン]";
		mes "ニャー……";
		mes "そこまで強そうには見えないニャ。";
		mes "無理しなくてもいいニャ？";
		next;
		mes "-この先に進むには";
		mes "　もっと強くなる必要がありそうだ。";
		mes "　^990000Baseレベルを90以上^000000にしてから";
		mes "　また来てみよう-";
		close;
	}
	mes "[保管庫の管理人ミシン]";
	mes "腕に自信があるニャ？";
	mes "ニャるほど、ニャるほど……。";
	mes "君は奥の部屋に興味はあるかニャ？";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "そこは本当に長い間、";
	mes "掃除をしていない場所だから";
	mes "どんな恐ろしいモンスターが";
	mes "潜んでいるかわからないニャ。";
	mes "行ってみるかニャ？";
	next;
	if(select("ごめんなさい。見栄を張ってました","行ってみよう") == 1) {
		mes "[保管庫の管理人ミシン]";
		mes "ニャんだ、そうニャのか。";
		mes "無理をする必要はニャいニャ。";
		close;
	}
	mes "-^FF0000Baseレベル90未満の";
	mes "　パーティーメンバーがいた場合、";
	mes "　そのメンバーは奥に進めません。";
	mes "　また、奥へと進む通路は";
	mes "　1分経過すると閉じ、";
	mes "　再度開くことはできません^000000-";
	next;
	mes "-奥に進みますか？-";
	next;
	if(select("いいえ","はい") == 1) {
		mes "[保管庫の管理人ミシン]";
		mes "ニャんだ、そうニャのか。";
		mes "無理をする必要はニャいニャ。";
		close;
	}
	mes "[保管庫の管理人 ミシン]";
	mes "わかったニャ！";
	mes "それじゃあ掃除を始めるのニャ。";
	mes "ミシンが先に入るから";
	mes "ついて来るニャ！";
	hideonnpc;
	enablenpc getmdnpcname("#PumpWarp1");
	initnpctimer getmdnpcname("#PumpWarp1");
	announce "ミシン : ミシンが先に入るからついて来るニャ！　3時の方向の出入り口を開いておくニャ！",0x9,0x00FFCC,0x190,15,0,0;
	areamonster getmdmapname("2@pump.gat"),0,0,0,0,"ヒドラ",1068,20;
	close;
}

1@pump.gat,83,105,4	script	保管庫の管理人ミシン#Pump1-1	545,{
	mes "[保管庫の管理人ミシン]";
	mes "掃除方法を簡単に教えてあげるニャ。";
	mes "周辺に排水路があるのが見えるかニャ？";
	next;
	if(select("排水路？","見えている") == 1) {
		mes "[保管庫の管理人ミシン]";
		mes "ん？　排水路は初めて見るニャ？";
		mes "この周辺には排水路と呼ばれる";
		mes "機械がいくつかあるニャ。";
		mes "一度見て来るといいニャ。";
		close;
	}
	mes "[保管庫の管理人ミシン]";
	mes "あの排水路が重要ニャ！";
	mes "6個ある排水路に、";
	mes "海藻が付かないよう";
	mes "一所懸命に掃除をするんだニャ！";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "掃除をしているとモンスターが";
	mes "邪魔をしてくるけど、";
	mes "排水路を掃除している人は";
	mes "動いたりスキルを使えないから、";
	mes "注意するニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "排水路は全部で10回開くニャ。";
	mes "その内、排水路を^ff0000全部で5か所";
	mes "掃除できたら終了ニャ！^000000";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "開いた排水路は、もたもたしてると";
	mes "海藻が詰まってしまうニャ。";
	mes "^ff0000掃除終了までに海藻が6個付いたら";
	mes "掃除は失敗ニャア。^000000";
	mes "失敗したら、";
	mes "ミシンが君達を呼び戻すニャ！";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "排水路の掃除は、失敗しても";
	mes "海藻が詰まってしまうニャ。";
	mes "^ff00002回まではやり直しができる^000000ニャ。";
	mes "それ以上は時間がかかりすぎると";
	mes "みんなが心配するから、";
	mes "今日のお掃除は諦めて引き上げるニャ。";
	next;
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[保管庫の管理人ミシン]";
		mes "君達のボスが準備を終えたら";
		mes "始めるから、心の準備をしているニャ！";
		close;
	}
	mes "[保管庫の管理人ミシン]";
	mes "掃除する準備はできたのかニャ？";
	next;
	if(select("ちょっと待って","準備できてるよ") == 1) {
		mes "[保管庫の管理人ミシン]";
		mes "まだ準備ができてないのかニャ？";
		mes "準備ができたら";
		mes "もう一度話しかけてほしいニャ。";
		close;
	}
	mes "[保管庫の管理人ミシン]";
	mes "わかったニャ！　では始めるニャ！";
	hideonnpc;
	donpcevent getmdnpcname("PumpControl1-1")+"::OnStart";
	set '@chid,getcharid(3);
	set '@map$,getmapname("");
	getpartymember getcharid(1);
	for(set '@i,0; '@i<$@partymembercount; set '@i,'@i+1) {
		if(attachrid(getcharid(3,$@partymembername$['@i]))){
			if('@map$ == getmapname("")) {
				viewpoint 1,58,101,0,0xFFFF00;
				viewpoint 1,68,124,1,0xFFFF00;
				viewpoint 1,80,114,2,0xFFFF00;
				viewpoint 1,75,80,3,0xFFFF00;
				viewpoint 1,40,80,4,0xFFFF00;
				viewpoint 1,36,111,5,0xFFFF00;
			}
			detachrid;
		}
	}
	if(!attachrid('@chid)) {
		end;
	}
	close;
OnInit:
	hideonnpc;
	end;
}

1@pump.gat,83,105,4	script	保管庫の管理人ミシン#Pump1-2	545,{
	if('retry < 3) {
		mes "[保管庫の管理人ミシン]";
		mes "失敗してしまったニャ……。";
		mes " ";
		mes "でもミシン達は諦めないニャ。";
		mes "頑張ろうニャ！";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "素早く作業をしないと";
		mes "海藻が巻き付いてしまうニャ。";
		mes "グズグズしていたらすべての";
		mes "排水路が海藻で詰まってしまうニャ！";
		next;
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[保管庫の管理人ミシン]";
			mes "君達のボスとどうするか";
			mes "相談してるニャ！";
			mes "もうちょっと待ってほしいニャ～。";
			close;
		}
		mes "[保管庫の管理人ミシン]";
		mes "元気が残っているニャら、";
		mes "もう一度挑戦するかニャ？";
		mes "^ff0000あと"+3-'retry+"回、挑戦することができる^000000ニャ。";
		next;
		switch(select("ちょっと待って","もう一度挑戦する","あきらめて帰る")) {
		case 1:
			mes "[保管庫の管理人ミシン]";
			mes "あまり迷っている時間はないニャ。";
			mes "準備ができたら声をかけてほしいニャ。";
			close;
		case 2:
			mes "[保管庫の管理人ミシン]";
			mes "わかったニャ。では始めるニャ！";
			hideonnpc;
			donpcevent getmdnpcname("PumpControl1-1")+"::OnStart";
			close;
		case 3:
			mes "[保管庫の管理人ミシン]";
			mes "ニャ!?";
			mes "あきらめて地上に帰りたいのかニャ？";
			next;
			if(select("まだ頑張る","あきらめて帰る") == 1) {
				mes "[保管庫の管理人ミシン]";
				mes "ほんとニャ？";
				mes "良かったニャ～！";
				close;
			}
			mes "[保管庫の管理人ミシン]";
			mes "残念だけど仕方ないニャ……。";
			mes "ここまで手伝ってくれて";
			mes "ありがとニャ。";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "帰りの出口は左のほうニャ。";
			mes "また良かったら手伝って欲しいニャ！";
			set 'retry,3;
			enablenpc getmdnpcname("#PumpExit1");
			close;
		}
	}
	mes "[保管庫の管理人ミシン]";
	mes "失敗してしまったニャ……。";
	mes "何度もあきらめずに";
	mes "挑戦してくれて嬉しいけど、";
	mes "そろそろ時間がマズいニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "残念だけど地上へ戻るニャ……。";
	mes "ここまで手伝ってくれて";
	mes "ありがとニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "帰りの出口は左のほうニャ。";
	mes "また良かったら手伝って欲しいニャ！";
	enablenpc getmdnpcname("#PumpExit1");
	close;
OnStart:
	hideoffnpc;
	set 'retry,'retry+1;
	end;
OnInit:
	hideonnpc;
	set 'retry,0;
	end;
}

1@pump.gat,83,105,4	script	保管庫の管理人ミシン#Pump1-3	545,{
	mes "[保管庫の管理人ミシン]";
	mes "はああ～びっくりしたニャー！";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "あんな変な貝は初めて見たニャ。";
	mes "黒くて、ザラザラしてて、";
	mes "不気味で怖かったニャ……。";
	mes "倒してくれてありがとニャ！";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "あとはミシンが処理をするから、";
	mes "君達は荷物を纏めて";
	mes "反対方向の出口から先に出ているニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "あ、それと……";
	mes "今日ここで見たことは";
	mes "秘密にしていてほしいニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "トーマス提督がここを閉鎖しちゃうと、";
	mes "ミシンも君達も";
	mes "仕事が無くなってしまうニャ。";
	if(checkquest(97100)) {
		if(checkquest(97100)&4) {
			next;
			if(checkitemblank() < 1) {
				mes "[保管庫の管理人ミシン]";
				mes "あ、荷物がいっぱいのようだニャ。";
				mes "荷物を整理して、";
				mes "もう一度声をかけてニャ。";
				close;
			}
			mes "[保管庫の管理人ミシン]";
			mes "あとこれは";
			mes "手伝ってくれたお礼だニャ。";
			mes "良かったらまた手伝って欲しいニャ。";
			getitem 12636,50;
			set '@base,50;
			set '@job,20;
			if(getonlinepartymember() > 1) {
				set '@base,'@base+25;
				set '@job,'@job+10;
			}
			for(set '@i,0; '@i < '@base; set '@i,'@i+1) {
				getexp 10000,0;
			}
			for(set '@i,0; '@i < '@job; set '@i,'@i+1) {
				getexp 0,10000;
			}
		}
		delquest 97100;
	}
	close;
OnInit:
	hideonnpc;
	end;
}

1@pump.gat,0,0,0	script	PumpControl1-1	-1,{
OnStart:
	set 'phase,0;
	set 'success,0;
	set 'fail,0;
	initnpctimer;
	announce "ミシン : 5秒後に最初の排水路が開くニャ！　開かれた排水路を探してクリックし掃除を始めるニャ!!",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnTimer5000:
	if('success < 5) {
		if('phase < 10) {
			set 'phase,'phase+1;
			set '@rand,rand(6);
			donpcevent getmdnpcname("#Pump1-"+'@rand)+"::OnStart";
			switch('@rand) {
			case 0:
				set '@pos$,"中央付近";
				set '@x1,54;
				set '@y1,97;
				set '@x2,62;
				set '@y2,105;
				break;
			case 1:
				set '@pos$,"1時方向";
				set '@x1,64;
				set '@y1,120;
				set '@x2,72;
				set '@y2,128;
				break;
			case 2:
				set '@pos$,"2時方向";
				set '@x1,76;
				set '@y1,110;
				set '@x2,84;
				set '@y2,118;
				break;
			case 3:
				set '@pos$,"5時方向";
				set '@x1,71;
				set '@y1,76;
				set '@x2,79;
				set '@y2,84;
				break;
			case 4:
				set '@pos$,"7時方向";
				set '@x1,36;
				set '@y1,76;
				set '@x2,44;
				set '@y2,84;
				break;
			case 5:
				set '@pos$,"10時方向";
				set '@x1,32;
				set '@y1,107;
				set '@x2,40;
				set '@y2,115;
				break;
			}
			announce "ミシン : "+'@pos$+"の排水路が開いたニャ！",0x9,0x00FFCC,0x190,15,0,0;
			if(rand(2)) {
				areamonster getmdmapname("1@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のバドン",2174,rand(2,3),getmdnpcname("PumpControl1-1")+"::OnKilled";
				areamonster getmdmapname("1@pump.gat"),'@x1,'@y1,'@x2,'@y2,"深海のカニ",2176,rand(2,3),getmdnpcname("PumpControl1-1")+"::OnKilled";
			}
			else {
				areamonster getmdmapname("1@pump.gat"),'@x1,'@y1,'@x2,'@y2,"深海のカナトウス",2177,rand(2,3),getmdnpcname("PumpControl1-1")+"::OnKilled";
				areamonster getmdmapname("1@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のククレ",2179,rand(2,3),getmdnpcname("PumpControl1-1")+"::OnKilled";
			}
		}
	}
	else {
		donpcevent getmdnpcname("PumpControl1-2")+"::OnStart";
		stopnpctimer;
	}
	end;
OnTimer50000:
	initnpctimer;
	end;
OnSuccess:
	set 'success,'success+1;
	announce "ミシン : "+'success+"個目の排水路の掃除が完了したニャ～！",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnFail:
	set 'fail,'fail+1;
	killmonster getmdmapname("1@pump.gat"),getmdnpcname("PumpControl1-1")+"::OnKilled";
	areamonster getmdmapname("1@pump.gat"),55,99,61,105,"巨大な海藻",2191,1,getmdnpcname("PumpControl1-1")+"::OnKilled2";
	announce "ミシン : 巨大な海藻が付いてしまったニャ！　今"+'fail+"茎だニャ！",0x9,0xFF3333,0x190,15,0,0;
	if('fail >= 6) {
		killmonster getmdmapname("1@pump.gat"),getmdnpcname("PumpControl1-1")+"::OnKilled2";
		announce "ミシン : 巨大な海藻が排水路を覆っているニャ！　掃除は失敗だニャ～。とりあえずミシンの所まで来てほしいニャ!!",0x9,0xFF88FF,0x190,15,0,0;
		donpcevent getmdnpcname("保管庫の管理人ミシン#Pump1-2")+"::OnStart";
		stopnpctimer;
	}
	end;
OnKilled:
OnKilled2:
	end;
}

1@pump.gat,0,0,0	script	PumpControl1-2	-1,{
OnStart:
	if(getvariableofnpc('fail,getmdnpcname("PumpControl1-1")) == 0) {
		announce "ミシン : 掃除終了ニャ！　完璧に掃除できたから、巨大な海藻は詰まらなかったニャ！",0x9,0x00FFCC,0x190,15,0,0;
	}
	else {
		announce "ミシン : 巨大な海藻は全部で"+getvariableofnpc('fail,getmdnpcname("PumpControl1-1"))+"茎ニャ。掃除終了ニャ！",0x9,0x00FFCC,0x190,15,0,0;
	}
	initnpctimer;
	end;
OnTimer5000:
	if(getvariableofnpc('fail,getmdnpcname("PumpControl1-1")) == 0) {
		announce "ミシン : うむ！　君達意外とやるニャ!!",0x9,0x00FFCC,0x190,15,0,0;
	}
	else {
		announce "ミシン : なかなか良い掃除だったニャ！",0x9,0x00FFCC,0x190,15,0,0;
	}
	end;
OnTimer10000:
	announce "ミシン : では荷物を纏めて上に……　ニャアアア!?",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnTimer15000:
	announce "ミシン : 何か変ニャ感じがする!!　バラバラだと危険ニャ！　真ん中に集まるニャ!!",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnTimer17000:
	mapwarp "this",getmdmapname("1@pump.gat"),61,96;
	hideoffnpc getmdnpcname("#PumpBoss1");
	end;
OnTimer22000:
	hideonnpc getmdnpcname("#PumpBoss1");
	announce "ミシン : 君達も緊張を解かニャいで、戦闘の準備をするニャ！",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnTimer24000:
	monster getmdmapname("1@pump.gat"),57,107,"深海のお化け貝",2178,1,getmdnpcname("PumpControl1-2")+"::OnKilled";
	announce "深淵の中から『深海のお化け貝』が出現！",0x9,0xFF88FF,0x190,40,0,0;
	stopnpctimer;
	end;
OnKilled:
	announce "排水路から現れた深海のお化け貝を倒しました。戦利品が周囲にばらまかれているので、地面をよく調べて見ましょう。",0x9,0xFFFF00,0x190,15,0,0;
	for(set '@i,0; '@i<10; set '@i,'@i+1) {
		if(rand(6400) < 6000) {
			dropitem "this",rand(40,77),rand(87,120),12636,1,0;		// マラン島特産缶詰
		}
		else {
			dropitem "this",rand(40,77),rand(87,120),12623,1,0;		//高級武器の箱
		}
	}
	hideoffnpc getmdnpcname("保管庫の管理人ミシン#Pump1-3");
	enablenpc getmdnpcname("#PumpExit1");
	end;
}

1@pump.gat,58,101,0	script	#Pump1-0	844,14,14,{
	if(getnpctimer(1)) {
		progressbar 5;
	}
	if(getnpctimer(1) == 0) {
		mes "-排水路は閉じている-";
		close;
	}
	misceffect 16;
	stopnpctimer;
	donpcevent getmdnpcname("PumpControl1-1")+"::OnSuccess";
	end;
OnStart:
	set 'count,50;
OnTimer1000:
	set 'count,'count-1;
	if('count == 10) {
		announce "ミシン : 10秒以内に"+getvariableofnpc('phase,getmdnpcname("PumpControl1-1"))+"個目の排水路の掃除を終わらせるニャ！　急ぐニャー!!",0x9,0x00FFCC,0x190,15,0,0;
	}
	if('count > 0) {
		misceffect 109;
		initnpctimer;
		end;
	}
	stopnpctimer;
	donpcevent getmdnpcname("PumpControl1-1")+"::OnFail";
	end;
OnTouch:
	if(getnpctimer(1)) {
		misceffect 247;
	}
	end;
}

1@pump.gat,68,124,0		duplicate(#Pump1-0)	#Pump1-1	844,14,14
1@pump.gat,80,114,0		duplicate(#Pump1-0)	#Pump1-2	844,14,14
1@pump.gat,75,80,0		duplicate(#Pump1-0)	#Pump1-3	844,14,14
1@pump.gat,40,80,0		duplicate(#Pump1-0)	#Pump1-4	844,14,14
1@pump.gat,36,111,0		duplicate(#Pump1-0)	#Pump1-5	844,14,14

1@pump.gat,61,95,0	script	#PumpBoss1	111,14,14,{
OnTouch:
	setquest 97100;
	end;
OnInit:
	hideonnpc;
	end;
}

1@pump.gat,32,100,0	script	#PumpExit1	45,3,3,{
OnTouch:
	if(checkquest(97100)) {
		mes "[保管庫の管理人ミシン]";
		mes "ニャニャ!?";
		mes "ちょっと待ってくれニャ。";
		mes "ミシンとお話して欲しいニャ！";
		close;
	}
	mes "-地下排水路から外に出ますか？-";
	next;
	if(select("外に出ない","外に出る") == 1) {
		mes "-あなたはその場から離れた-";
		close;
	}
	mes "-外へ出ます-";
	close2;
	warp "mal_in01.gat",161,32;
	end;
OnInit:
	disablenpc;
	end;
}

1@pump.gat,84,105,0	script	#PumpWarp1	45,3,3,{
OnTouch:
	if(getnpctimer(1)) {
		if(BaseLevel < 90) {
			mes "-Baseレベル90未満の場合、";
			mes "　奥に移動はできません-";
			close2;
			warp getmdmapname("1@pump.gat"),74,105;
			end;
		}
		warp getmdmapname("2@pump.gat"),38,88;
		end;
	}
	mes "-奥の方で騒がしい音がする";
	mes "　お掃除が既に始まっていて";
	mes "　今から合流するのは難しそうだ。";
	mes " ";
	mes "　外に出ますか？-";
	next;
	if(select("外に出る","外に出ない") == 2) {
		mes "-もう少しここにいる事にした-";
		close;
	}
	mes "-あなたは外に出た-";
	close2;
	warp "mal_in01.gat",161,32;
	end;
OnTimer2000:
	announce "ミシン : 奥の部屋には恐ろしいモンスターがいっぱいニャ！　1分したら出入口を閉めるから、早く移動して欲しいニャ!!",0x9,0x0FFCC,0x0190,15,0,0;
	end;
OnTimer60000:
	announce "ミシン : 奥の部屋への出入口を閉めるニャ～！",0x9,0x0FFCC,0x0190,15,0,0;
	stopnpctimer;
	end;
OnInit:
	disablenpc;
	end;
}

//============================================================
// 地下排水路 最奥部（お掃除エキスパート）
//------------------------------------------------------------
2@pump.gat,40,88,4	script	保管庫の管理人ミシン#Pump2	545,{
	if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
		mes "[保管庫の管理人ミシン]";
		mes "君達のボスが準備を終えたら";
		mes "始めるから、心の準備をしているニャ！";
		close;
	}
	switch(getvariableofnpc('level,getmdnpcname("PumpControl2-1"))) {
	case 0:
		mes "[保管庫の管理人ミシン]";
		mes "掃除方法を簡単に教えてあげるニャ。";
		mes "周辺に排水路があるのが見えるかニャ？";
		next;
		if(select("排水路？","見えている") == 1) {
			mes "[保管庫の管理人ミシン]";
			mes "ん？　排水路は初めて見るニャ？";
			mes "この周辺には排水路と呼ばれる";
			mes "機械がいくつかあるニャ。";
			mes "一度見て来るといいニャ。";
			close;
		}
		mes "[保管庫の管理人ミシン]";
		mes "あの排水路が重要ニャ！";
		mes "10個ある排水路に、";
		mes "海藻が付かないよう";
		mes "一所懸命に掃除をするんだニャ！";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "掃除をしているとモンスターが";
		mes "邪魔をしてくるけど、";
		mes "排水路を掃除している人は";
		mes "動いたりスキルを使えないから、";
		mes "注意するニャ。";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "排水路は全部で10回開くニャ。";
		mes "その内、排水路を^ff0000全部で5か所";
		mes "掃除できたら終了ニャ！^000000";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "開いた排水路は、もたもたしてると";
		mes "海藻が詰まってしまうニャ。";
		mes "^ff0000掃除終了までに海藻が6個付いたら";
		mes "掃除は失敗ニャア。^000000";
		mes "失敗したら、";
		mes "ミシンが君達を呼び戻すニャ！";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "排水路の掃除は、失敗しても";
		mes "海藻が詰まってしまうニャ。";
		mes "^ff00002回まではやり直しができる^000000ニャ。";
		mes "それ以上は時間がかかりすぎると";
		mes "みんなが心配するから、";
		mes "今日のお掃除は諦めて引き上げるニャ。";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "それと、";
		mes "お掃除エキスパートさんには";
		mes "難易度を選んで貰ってるニャ。";
		mes "どれにするニャ？";
		while(1) {
			next;
			switch(select("難易度：3点盛り","難易度：6点盛り","難易度：ギガミックス盛り")) {
			case 1:
				mes "[保管庫の管理人ミシン]";
				mes "^ff0000難易度：3点盛り^000000";
				mes "^0000ff水属性^000000の攻撃をしてくるモンスターが";
				mes "いる排水路を掃除するニャ。";
				mes "^0000ff水属性^000000に有利な装備で挑んでくれニャ。";
				mes " ";
				mes "これでいいかニャ？";
				set '@str$,"3点盛り";
				set '@level,1;
				break;
			case 2:
				mes "[保管庫の管理人ミシン]";
				mes "^ff0000難易度：6点盛り^000000";
				mes "^0000ff水属性^000000と^00ff00風属性^000000の";
				mes "攻撃をしてくるモンスターがいる";
				mes "排水路を掃除するニャ。";
				mes "^0000ff水属性^000000と^00ff00風属性^000000に有利な";
				mes "装備で挑んでくれニャ。";
				next;
				mes "[保管庫の管理人ミシン]";
				mes "^ff0000難易度：6点盛り^000000でいいかニャ？";
				set '@str$,"6点盛り";
				set '@level,2;
				break;
			case 3:
				mes "[保管庫の管理人ミシン]";
				mes "^ff0000難易度：ギガミックス盛り^000000";
				mes "^0000ff水属性^000000と^00ff00風属性^000000の";
				mes "攻撃をしてくるモンスターがいる";
				mes "排水路を掃除するニャ。";
				mes "ここの主の^ff0000シーラカンスも";
				mes "何匹か出てきそうな気がする^000000ニャ……。";
				next;
				mes "[保管庫の管理人ミシン]";
				mes "^0000ff水属性^000000と^00ff00風属性^000000に有利な";
				mes "装備で挑んでくれニャ。";
				mes "^ff0000難易度：ギガミックス盛り^000000";
				mes "でいいかニャ？";
				set '@str$,"ギガミックス盛り";
				set '@level,3;
				break;
			}
			next;
			if(select("いいえ","はい") == 1) {
				mes "[保管庫の管理人ミシン]";
				mes "ニャニャ？";
				mes "どれにするニャ？";
				continue;
			}
			break;
		}
		set getvariableofnpc('level,getmdnpcname("PumpControl2-1")),'@level;
		mes "[保管庫の管理人ミシン]";
		mes "分かったニャ！";
		mes "難易度は"+'@str$+"でいくニャ！";
		mes "何がどう"+'@str$+"なのかは、";
		mes "君たち自身の目で";
		mes "確かめて欲しいニャ！";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "さあ、そろそろお掃除の時間ニャ。";
		break;
	case 1:
		mes "[保管庫の管理人ミシン]";
		mes "選んだ難易度は";
		mes "3点盛りだニャ！";
		break;
	case 2:
		mes "[保管庫の管理人ミシン]";
		mes "選んだ難易度は";
		mes "6点盛りだニャ！";
		break;
	case 3:
		mes "[保管庫の管理人ミシン]";
		mes "選んだ難易度は";
		mes "ギガミックス盛りだニャ！";
		break;
	}
	mes "掃除する準備はできたのかニャ？";
	next;
	if(select("ちょっと待って","準備できてるよ") == 1) {
		mes "[保管庫の管理人ミシン]";
		mes "まだ準備ができてないのかニャ？";
		mes "準備ができたら";
		mes "もう一度話しかけてほしいニャ。";
		close;
	}
	mes "[保管庫の管理人ミシン]";
	mes "分かったニャ！　では始めるニャ！";
	hideonnpc;
	donpcevent getmdnpcname("PumpControl2-1")+"::OnStart";
	set '@chid,getcharid(3);
	set '@map$,getmapname("");
	getpartymember getcharid(1);
	for(set '@i,0; '@i<$@partymembercount; set '@i,'@i+1) {
		if(attachrid(getcharid(3,$@partymembername$['@i]))){
			if('@map$ == getmapname("")) {
				viewpoint 1,79,109,0,0xFFFF00;
				viewpoint 1,98,98,1,0xFFFF00;
				viewpoint 1,114,114,2,0xFFFF00;
				viewpoint 1,100,74,3,0xFFFF00;
				viewpoint 1,115,50,4,0xFFFF00;
				viewpoint 1,81,63,5,0xFFFF00;
				viewpoint 1,57,70,6,0xFFFF00;
				viewpoint 1,47,49,7,0xFFFF00;
				viewpoint 1,62,96,8,0xFFFF00;
				viewpoint 1,53,114,9,0xFFFF00;
			}
			detachrid;
		}
	}
	if(!attachrid('@chid)) {
		end;
	}
	close;
}

2@pump.gat,39,88,4	script	保管庫の管理人ミシン#Pump2-2	545,{
	if('retry < 3) {
		mes "[保管庫の管理人ミシン]";
		mes "失敗してしまったニャ……。";
		mes " ";
		mes "でもミシン達は諦めないニャ。";
		mes "頑張ろうニャ！";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "素早く作業をしないと";
		mes "海藻が巻き付いてしまうニャ。";
		mes "グズグズしていたらすべての";
		mes "排水路が海藻で詰まってしまうニャ！";
		next;
		if(getpartyleader(getcharid(1)) != strcharinfo(0)) {
			mes "[保管庫の管理人ミシン]";
			mes "君達のボスとどうするか";
			mes "相談してるニャ！";
			mes "もうちょっと待ってほしいニャ～。";
			close;
		}
		mes "[保管庫の管理人ミシン]";
		mes "元気が残っているニャら、";
		mes "もう一度挑戦するかニャ？";
		mes "^ff0000あと"+3-'retry+"回、挑戦することができる^000000ニャ。";
		next;
		switch(select("ちょっと待って","もう一度挑戦する","あきらめて帰る")) {
		case 1:
			mes "[保管庫の管理人ミシン]";
			mes "あまり迷っている時間はないニャ。";
			mes "準備ができたら声をかけてほしいニャ。";
			close;
		case 2:
			mes "[保管庫の管理人ミシン]";
			mes "そうくると思ったニャ！";
			mes "難易度はどれにするニャ？";
			while(1) {
				next;
				switch(select("難易度：3点盛り","難易度：6点盛り","難易度：ギガミックス盛り")) {
				case 1:
					mes "[保管庫の管理人ミシン]";
					mes "^ff0000難易度：3点盛り^000000";
					mes "^0000ff水属性^000000の攻撃をしてくるモンスターが";
					mes "いる排水路を掃除するニャ。";
					mes "^0000ff水属性^000000に有利な装備で挑んでくれニャ。";
					mes " ";
					mes "これでいいかニャ？";
					set '@str$,"3点盛り";
					set '@level,1;
					break;
				case 2:
					mes "[保管庫の管理人ミシン]";
					mes "^ff0000難易度：6点盛り^000000";
					mes "^0000ff水属性^000000と^00ff00風属性^000000の";
					mes "攻撃をしてくるモンスターがいる";
					mes "排水路を掃除するニャ。";
					mes "^0000ff水属性^000000と^00ff00風属性^000000に有利な";
					mes "装備で挑んでくれニャ。";
					next;
					mes "[保管庫の管理人ミシン]";
					mes "^ff0000難易度：6点盛り^000000でいいかニャ？";
					set '@str$,"6点盛り";
					set '@level,2;
					break;
				case 3:
					mes "[保管庫の管理人ミシン]";
					mes "^ff0000難易度：ギガミックス盛り^000000";
					mes "^0000ff水属性^000000と^00ff00風属性^000000の";
					mes "攻撃をしてくるモンスターがいる";
					mes "排水路を掃除するニャ。";
					mes "ここの主の^ff0000シーラカンスも";
					mes "何匹か出てきそうな気がする^000000ニャ……。";
					next;
					mes "[保管庫の管理人ミシン]";
					mes "^0000ff水属性^000000と^00ff00風属性^000000に有利な";
					mes "装備で挑んでくれニャ。";
					mes "^ff0000難易度：ギガミックス盛り^000000";
					mes "でいいかニャ？";
					set '@str$,"ギガミックス盛り";
					set '@level,3;
					break;
				}
				next;
				if(select("いいえ","はい") == 1) {
					mes "[保管庫の管理人ミシン]";
					mes "ニャニャ？";
					mes "どれにするニャ？";
					continue;
				}
				break;
			}
			set getvariableofnpc('level,getmdnpcname("PumpControl2-1")),'@level;
			mes "[保管庫の管理人ミシン]";
			mes "分かったニャ！";
			mes "難易度は"+'@str$+"でいくニャ！";
			mes "何がどう"+'@str$+"なのかは、";
			mes "君たち自身の目で";
			mes "確かめて欲しいニャ！";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "それじゃあ始めるニャ！";
			hideonnpc;
			donpcevent getmdnpcname("PumpControl2-1")+"::OnStart";
			close;
		case 3:
			mes "[保管庫の管理人ミシン]";
			mes "ニャ!?";
			mes "あきらめて地上に帰りたいのかニャ？";
			next;
			if(select("まだ頑張る","あきらめて帰る") == 1) {
				mes "[保管庫の管理人ミシン]";
				mes "ほんとニャ？";
				mes "良かったニャ～！";
				close;
			}
			mes "[保管庫の管理人ミシン]";
			mes "残念だけど仕方ないニャ……。";
			mes "ここまで手伝ってくれて";
			mes "ありがとニャ。";
			next;
			mes "[保管庫の管理人ミシン]";
			mes "帰りの出口は左のほうニャ。";
			mes "また良かったら手伝って欲しいニャ！";
			set 'retry,3;
			enablenpc getmdnpcname("#PumpExit2");
			close;
		}
	}
	mes "[保管庫の管理人ミシン]";
	mes "失敗してしまったニャ……。";
	mes "何度もあきらめずに";
	mes "挑戦してくれて嬉しいけど、";
	mes "そろそろ時間がマズいニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "残念だけど地上へ戻るニャ……。";
	mes "ここまで手伝ってくれて";
	mes "ありがとニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "帰りの出口は左のほうニャ。";
	mes "また良かったら手伝って欲しいニャ！";
	enablenpc getmdnpcname("#PumpExit2");
	close;
OnStart:
	hideoffnpc;
	set 'retry,'retry+1;
	end;
OnInit:
	hideonnpc;
	set 'retry,0;
	end;
}

2@pump.gat,41,88,4	script	保管庫の管理人ミシン#Pump2-3	545,{
	if(PUMP_1QUE != 2) {
		mes "[保管庫の管理人ミシン]";
		mes "ありがとうニャ。";
		mes "良かったらまた手伝って欲しいニャ。";
		close;
	}
	set '@kill,getvariableofnpc('kill,getmdnpcname("PumpControl2-2"));
	if('@kill == 0) {
		mes "[保管庫の管理人ミシン]";
		mes "君達が戦った奴はシーラカンスの中でも";
		mes "亜種として扱われている奴だニャ。";
		mes "これまで何度か挑戦していたけど、";
		mes "その度に失敗していたニャ。";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "とりあえず大人しく帰ってくれて";
		mes "良かったニャ。";
	}
	else {
		mes "[保管庫の管理人ミシン]";
		mes "すごい奴を倒したニャ！";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "君達が倒した奴はシーラカンスの中でも";
		mes "強くて凶暴な奴だニャ。";
		mes "これまで何度か挑戦していたけど、";
		mes "その度に失敗していたニャ。";
		next;
		emotion 21;
		mes "[保管庫の管理人ミシン]";
		mes "まさか"+('@kill == 0? "アイツを": '@kill == 4? "4匹とも": '@kill+"匹も")+"倒せるとは";
		mes "思ってなかったニャ。";
		mes "すごいニャ！　すごいニャ!!";
		next;
		mes "[保管庫の管理人ミシン]";
		mes "フー！";
		mes "フー!!";
		next;
		emotion 32;
		mes "[保管庫の管理人ミシン]";
		mes "ふー……";
		mes "久しぶりにエキサイトして";
		mes "しまったニャ。";
	}
	next;
	mes "[保管庫の管理人ミシン]";
	mes "あとはミシンが処理をするから、";
	mes "君達は荷物を纏めて";
	mes "反対方向の出口から先に出ているニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "あ、それと……";
	mes "今日ここで見たことは";
	mes "秘密にしていてほしいニャ。";
	next;
	mes "[保管庫の管理人ミシン]";
	mes "トーマス提督がここを閉鎖しちゃうと、";
	mes "ミシンも君達も";
	mes "仕事が無くなってしまうニャ。";
	next;
	if(checkitemblank() < 1) {
		mes "[保管庫の管理人ミシン]";
		mes "あ、荷物がいっぱいのようだニャ。";
		mes "荷物を整理して、";
		mes "もう一度声をかけてニャ。";
		close;
	}
	mes "[保管庫の管理人ミシン]";
	mes "あとこれは";
	mes "手伝ってくれたお礼だニャ。";
	mes "良かったらまた手伝って欲しいニャ。";
	switch(getvariableofnpc('level,getmdnpcname("PumpControl2-1"))) {
	case 1:		// 3点盛り
		getitem 6423,2;
		getexp 3000000, 0;
		getexp 0, 1500000;
		break;
	case 2:		// 6点盛り
		getitem 6423,5;
		if(BaseLevel < 100) {
			getexp 3000000,0;
			getexp 0,1500000;
		}
		else if(BaseLevel < 110) {
			getexp 4000000,0;
			getexp 0,2000000;
		}
		else if(BaseLevel < 120) {
			getexp 5000000,0;
			getexp 0,2500000;
		}
		else if(BaseLevel < 130) {
			getexp 7000000,0;
			getexp 0,3500000;
		}
		else {
			getexp 10000000,0;
			getexp 0,5000000;
		}
		break;
	case 3:		// ギガミックス盛り
		switch('@kill) {
		case 0:
			getitem 6423,3;
			if(BaseLevel < 100) {
				getexp 3000000,0;
				getexp 0,1500000;
			}
			else if(BaseLevel < 110) {
				getexp 3000000,0;
				getexp 0,1500000;
			}
			else if(BaseLevel < 120) {
				getexp 4000000,0;
				getexp 0,2000000;
			}
			else if(BaseLevel < 130) {
				getexp 5000000,0;
				getexp 0,2500000;
			}
			else {
				getexp 6000000,0;
				getexp 0,3000000;
			}
			break;
		case 1:
			getitem 6423,8;
			if(BaseLevel < 100) {
				getexp 3000000,0;
				getexp 0,1500000;
			}
			else if(BaseLevel < 110) {
				getexp 4000000,0;
				getexp 0,2000000;
			}
			else if(BaseLevel < 120) {
				getexp 5000000,0;
				getexp 0,2500000;
			}
			else if(BaseLevel < 130) {
				getexp 7000000,0;
				getexp 0,3500000;
			}
			else {
				getexp 10000000,0;
				getexp 0,5000000;
			}
			break;
		case 2:
			getitem 6423,12;
			if(BaseLevel < 100) {
				getexp 3000000,0;
				getexp 0,1500000;
			}
			else if(BaseLevel < 110) {
				getexp 4500000,0;
				getexp 0,2250000;
			}
			else if(BaseLevel < 120) {
				getexp 6000000,0;
				getexp 0,3000000;
			}
			else if(BaseLevel < 130) {
				getexp 9000000,0;
				getexp 0,4500000;
			}
			else {
				getexp 12000000,0;
				getexp 0,6000000;
			}
			break;
		case 3:
			getitem 6423,15;
			if(BaseLevel < 100) {
				getexp 3000000,0;
				getexp 0,1500000;
			}
			else if(BaseLevel < 110) {
				getexp 5000000,0;
				getexp 0,2500000;
			}
			else if(BaseLevel < 120) {
				getexp 7000000,0;
				getexp 0,3500000;
			}
			else if(BaseLevel < 130) {
				getexp 11000000,0;
				getexp 0,5500000;
			}
			else {
				getexp 15000000,0;
				getexp 0,7500000;
			}
			break;
		case 4:
			getitem 6423,15;
			if(BaseLevel < 100) {
				getexp 3000000,0;
				getexp 0,1500000;
			}
			else if(BaseLevel < 110) {
				getexp 6000000,0;
				getexp 0,3000000;
			}
			else if(BaseLevel < 120) {
				getexp 10000000,0;
				getexp 0,5000000;
			}
			else if(BaseLevel < 130) {
				getexp 16000000,0;
				getexp 0,8000000;
			}
			else {
				getexp 20000000,0;
				getexp 0,10000000;
			}
			break;
		}
		break;
	}
	set PUMP_1QUE,3;
	close;
OnInit:
	hideonnpc;
	end;
}

2@pump.gat,0,0,0	script	PumpControl2-1	-1,{
OnStart:
	set 'phase,0;
	set 'success,0;
	set 'fail,0;
	initnpctimer;
	announce "ミシン : 5秒後に最初の排水路が開くニャ！　開かれた排水路を探してクリックし掃除を始めるニャ!!",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnTimer5000:
	if('success < 5) {
		if('phase < 10) {
			set 'phase,'phase+1;
			set '@rand,rand(6);
			donpcevent getmdnpcname("#Pump2-"+'@rand)+"::OnStart";
			switch('@rand) {
			case 0:
				set '@pos$,"12時方向";
				set '@x1,75;
				set '@y1,105;
				set '@x2,83;
				set '@y2,113;
				break;
			case 1:
				set '@pos$,"2時方向";
				set '@x1,94;
				set '@y1,94;
				set '@x2,102;
				set '@y2,102;
				break;
			case 2:
				set '@pos$,"2時方向";
				set '@x1,110;
				set '@y1,110;
				set '@x2,118;
				set '@y2,118;
				break;
			case 3:
				set '@pos$,"5時方向";
				set '@x1,96;
				set '@y1,70;
				set '@x2,104;
				set '@y2,78;
				break;
			case 4:
				set '@pos$,"5時方向";
				set '@x1,111;
				set '@y1,46;
				set '@x2,119;
				set '@y2,54;
				break;
			case 5:
				set '@pos$,"6時方向";
				set '@x1,77;
				set '@y1,59;
				set '@x2,85;
				set '@y2,67;
				break;
			case 6:
				set '@pos$,"8時方向";
				set '@x1,53;
				set '@y1,66;
				set '@x2,61;
				set '@y2,74;
				break;
			case 7:
				set '@pos$,"8時方向";
				set '@x1,43;
				set '@y1,45;
				set '@x2,51;
				set '@y2,53;
				break;
			case 8:
				set '@pos$,"10時方向";
				set '@x1,58;
				set '@y1,92;
				set '@x2,66;
				set '@y2,100;
				break;
			case 9:
				set '@pos$,"10時方向";
				set '@x1,49;
				set '@y1,110;
				set '@x2,57;
				set '@y2,118;
				break;
			}
			announce "ミシン : "+'@pos$+"の排水路が開いたニャ！",0x9,0x00FFCC,0x190,15,0,0;
			switch('level) {
			case 1:
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のソードフィッシュ",2181,rand(1,2),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のマルク",2182,rand(2,3),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のオボンヌ",2184,rand(2,3),getmdnpcname("PumpControl2-1")+"::OnKilled";
				break;
			case 2:
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のソードフィッシュ",2181,rand(1,2),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のマルク",2182,rand(1,2),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のオボンヌ",2184,rand(1,2),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"変異のストラウフ",2180,rand(1,2),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"変異のアノリアン",2183,1,getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"変異の河童",2185,1,getmdnpcname("PumpControl2-1")+"::OnKilled";
				break;
			case 3:
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のソードフィッシュ",2181,rand(2,3),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のマルク",2182,rand(2,3),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"古代のオボンヌ",2184,rand(2,3),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"変異のストラウフ",2180,rand(2,3),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"変異のアノリアン",2183,rand(2,3),getmdnpcname("PumpControl2-1")+"::OnKilled";
				areamonster getmdmapname("2@pump.gat"),'@x1,'@y1,'@x2,'@y2,"変異の河童",2185,rand(2,3),getmdnpcname("PumpControl2-1")+"::OnKilled";
				break;
			}
		}
	}
	else {
		donpcevent getmdnpcname("PumpControl2-2")+"::OnStart";
		stopnpctimer;
	}
	end;
OnTimer40000:
	initnpctimer;
	end;
OnSuccess:
	set 'success,'success+1;
	announce "ミシン : "+'success+"個目の排水路の掃除が完了したニャ～！",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnFail:
	set 'fail,'fail+1;
	killmonster getmdmapname("2@pump.gat"),getmdnpcname("PumpControl2-1")+"::OnKilled";
	areamonster getmdmapname("2@pump.gat"),75,78,85,88,"巨大な海藻",2191,1,getmdnpcname("PumpControl2-1")+"::OnKilled2";
	announce "ミシン : 巨大な海藻が付いてしまったニャ！　今"+'fail+"茎だニャ！",0x9,0xFF3333,0x190,15,0,0;
	if('fail >= 6) {
		killmonster getmdmapname("2@pump.gat"),getmdnpcname("PumpControl2-1")+"::OnKilled2";
		announce "ミシン : 巨大な海藻が排水路を覆っているニャ！　掃除は失敗だニャ～。とりあえずミシンの所まで来てほしいニャ!!",0x9,0xFF88FF,0x190,15,0,0;
		donpcevent getmdnpcname("保管庫の管理人ミシン#Pump2-2")+"::OnStart";
		stopnpctimer;
	}
	end;
OnKilled:
OnKilled2:
	end;
}

2@pump.gat,0,0,0	script	PumpControl2-2	-1,{
OnStart:
	if(getvariableofnpc('fail,getmdnpcname("PumpControl2-1")) == 0) {
		announce "ミシン : 掃除終了ニャ！　完璧に掃除できたから、巨大な海藻は詰まらなかったニャ！",0x9,0x00FFCC,0x190,15,0,0;
	}
	else {
		announce "ミシン : 巨大な海藻は全部で"+getvariableofnpc('fail,getmdnpcname("PumpControl2-1"))+"茎ニャ。掃除終了ニャ！",0x9,0x00FFCC,0x190,15,0,0;
	}
	initnpctimer;
	end;
OnTimer5000:
	if(getvariableofnpc('fail,getmdnpcname("PumpControl2-1")) == 0) {
		announce "ミシン : うむ！　君達意外とやるニャ!!",0x9,0x00FFCC,0x190,15,0,0;
	}
	else {
		announce "ミシン : なかなか良い掃除だったニャ！",0x9,0x00FFCC,0x190,15,0,0;
	}
	end;
OnTimer10000:
	announce "ミシン : では荷物を纏めて上に……　ニャアアア!?",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnTimer15000:
	announce "ミシン : 何か変ニャ感じがする!!　バラバラだと危険ニャ！　真ん中に集まるニャ!!",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnTimer17000:
	mapwarp "this",getmdmapname("2@pump.gat"),74,88;
	hideoffnpc getmdnpcname("#PumpBoss2");
	end;
OnTimer22000:
	hideonnpc getmdnpcname("#PumpBoss2");
	announce "ミシン : 君達も緊張を解かニャいで、戦闘の準備をするニャ！",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnTimer24000:
	switch(getvariableofnpc('level,getmdnpcname("PumpControl2-1"))) {
	case 1:
		monster getmdmapname("2@pump.gat"),79,92,"暗黒のシーラカンス",2187,1,getmdnpcname("PumpControl2-2")+"::OnKilled";
		announce "排水路の奥底から『暗黒のシーラカンス』が出現！",0x9,0xFF88FF,0x190,40,0,0;
		break;
	case 2:
		monster getmdmapname("2@pump.gat"),79,92,"暴虐のシーラカンス",2190,1,getmdnpcname("PumpControl2-2")+"::OnKilled";
		announce "排水路の奥底から『暴虐のシーラカンス』が出現！",0x9,0xFF88FF,0x190,40,0,0;
		break;
	default:
		monster getmdmapname("2@pump.gat"),94,97,"暗黒のシーラカンス",2187,1,getmdnpcname("PumpControl2-2")+"::OnKilled";
		monster getmdmapname("2@pump.gat"),97,71,"異形のシーラカンス",2188,1,getmdnpcname("PumpControl2-2")+"::OnKilled";
		monster getmdmapname("2@pump.gat"),60,68,"暴虐のシーラカンス",2189,1,getmdnpcname("PumpControl2-2")+"::OnKilled";
		monster getmdmapname("2@pump.gat"),66,97,"変異のシーラカンス",2190,1,getmdnpcname("PumpControl2-2")+"::OnKilled";
		announce "排水路の奥底から4匹のシーラカンスが出現！",0x9,0xFF88FF,0x190,40,0,0;
		break;
	}
	end;
OnTimer27000:
	announce "ミシン : アイツはいつも掃除を邪魔する悪いヤツだニャ！",0x9,0x00FFCC,0x190,15,0,0;
	end;
OnTimer30000:
	if(getvariableofnpc('level,getmdnpcname("PumpControl2-1")) < 3) {
		announce "ミシン : でもなんだか様子がおかしいニャ。　弱ってるみたいだニャ……。",0x9,0x00FFCC,0x190,15,0,0;
	}
	else {
		announce "ミシン : アイツらは3分間ココを荒らしたら、元来た場所へ帰ってしまうニャ！",0x9,0x00FFCC,0x190,15,0,0;
	}
	end;
OnTimer33000:
	if(getvariableofnpc('level,getmdnpcname("PumpControl2-1")) < 3) {
		announce "ミシン : よ～し、いまのうちニャ！　あいつを追っぱらって欲しいニャ！",0x9,0x00FFCC,0x190,15,0,0;
		stopnpctimer;
	}
	else {
		announce "ミシン : 3分以内にアイツらをやっつけて欲しいニャ！　頼んだニャ！",0x9,0x00FFCC,0x190,15,0,0;
	}
	end;
OnTimer93000:
	announce "ミシン : 1分経過したニャ！　まだ少し時間はあるニャ！",0x9,0xFF88FF,0x190,15,0,0;
	end;
OnTimer153000:
	announce "ミシン : 2分経過したニャ！　残り1分、急ぐニャ!!",0x9,0xFF88FF,0x190,15,0,0;
	end;
OnTimer213000:
	killmonster getmdmapname("2@pump.gat"),getmdnpcname("PumpControl2-2")+"::OnKilled";
	hideoffnpc getmdnpcname("保管庫の管理人ミシン#Pump2-3");
	enablenpc getmdnpcname("#PumpExit2");
	announce "ミシン : シーラカンスたちが帰ってくニャ……。とりあえず一安心かニャ。",0x9,0xFF88FF,0x190,15,0,0;
	end;
OnTimer216000:
	announce "ミシン : さあ、今度こそ帰るニャ。その前にミシンに話かけて欲しいニャ！",0x9,0xFF88FF,0x190,15,0,0;
	stopnpctimer;
	end;
OnKilled:
	set 'kill,'kill+1;
	if(getmapmobs(getmdmapname("2@pump.gat"),getmdnpcname("PumpControl2-2")+"::OnKilled") > 0) {
		announce "まだモンスターが残っています。",0x9,0x00FF99,0x190,20,0,0;
		end;
	}
	stopnpctimer;
	announce "排水路から現れたシーラカンスを倒しました。戦利品が周囲にばらまかれているので、地面をよく調べて見ましょう。",0x9,0xFFFF00,0x190,15,0,0;
	for(set '@i,0; '@i<10; set '@i,'@i+1) {
		if(rand(4000) < 5000) {
			dropitem "this",rand(40,77),rand(87,120),12636,1,0;		// マラン島特産缶詰
		}
		else {
			dropitem "this",rand(40,77),rand(87,120),12623,1,0;		//高級武器の箱
		}
	}
	hideoffnpc getmdnpcname("保管庫の管理人ミシン#Pump2-3");
	enablenpc getmdnpcname("#PumpExit2");
	end;
}

2@pump.gat,79,109,0	script	#Pump2-0	844,14,14,{
	if(getnpctimer(1)) {
		progressbar 5;
	}
	if(getnpctimer(1) == 0) {
		mes "-排水路は閉じている-";
		close;
	}
	misceffect 16;
	stopnpctimer;
	donpcevent getmdnpcname("PumpControl2-1")+"::OnSuccess";
	end;
OnStart:
	set 'count,40;
OnTimer1000:
	set 'count,'count-1;
	if('count == 10) {
		announce "ミシン : 10秒以内に"+getvariableofnpc('phase,getmdnpcname("PumpControl2-1"))+"個目の排水路の掃除を終わらせるニャ！　急ぐニャー!!",0x9,0x00FFCC,0x190,15,0,0;
	}
	if('count > 0) {
		misceffect 109;
		initnpctimer;
		end;
	}
	stopnpctimer;
	donpcevent getmdnpcname("PumpControl2-1")+"::OnFail";
	end;
OnTouch:
	if(getnpctimer(1)) {
		misceffect 247;
	}
	end;
}

2@pump.gat,98,98,0		duplicate(#Pump2-0)	#Pump2-1	844,14,14
2@pump.gat,114,114,0	duplicate(#Pump2-0)	#Pump2-2	844,14,14
2@pump.gat,100,74,0		duplicate(#Pump2-0)	#Pump2-3	844,14,14
2@pump.gat,115,50,0		duplicate(#Pump2-0)	#Pump2-4	844,14,14
2@pump.gat,81,63,0		duplicate(#Pump2-0)	#Pump2-5	844,14,14
2@pump.gat,57,70,0		duplicate(#Pump2-0)	#Pump2-6	844,14,14
2@pump.gat,47,49,0		duplicate(#Pump2-0)	#Pump2-7	844,14,14
2@pump.gat,62,96,0		duplicate(#Pump2-0)	#Pump2-8	844,14,14
2@pump.gat,53,114,0		duplicate(#Pump2-0)	#Pump2-9	844,14,14

2@pump.gat,79,85,0	script	#PumpBoss2	111,14,14,{
OnTouch:
	set PUMP_1QUE,2;
	switch(getvariableofnpc('level,getmdnpcname("PumpControl2-1"))) {
	case 1:
		viewpoint 1,79,92,0,0x0000FF;
		break;
	case 2:
		viewpoint 1,79,92,0,0x00FF00;
		break;
	case 3:
		viewpoint 1,94,97,0,0x0000FF;
		viewpoint 1,97,71,1,0x0000FF;
		viewpoint 1,60,68,2,0x00FF00;
		viewpoint 1,66,97,3,0x00FF00;
		break;
	}
	end;
OnInit:
	hideonnpc;
	end;
}

2@pump.gat,38,100,0	script	#PumpExit2	45,3,3,{
OnTouch:
	if(PUMP_1QUE == 2) {
		mes "[保管庫の管理人ミシン]";
		mes "ニャニャ!?";
		mes "ちょっと待ってくれニャ。";
		mes "ミシンとお話して欲しいニャ！";
		close;
	}
	mes "-地下排水路から外に出ますか？-";
	next;
	if(select("外に出ない","外に出る") == 1) {
		mes "-あなたはその場から離れた-";
		close;
	}
	mes "-外へ出ます-";
	close2;
	warp "mal_in01.gat",161,32;
	end;
OnInit:
	disablenpc;
	end;
}
