//= Auriga Script ==============================================================
// Ragnarok Online God SE Festival Script	by refis
//==============================================================================

//============================================================
// ルミィ・ラビセフ
//------------------------------------------------------------
yuno.gat,118,192,6	script	ルミィ・ラビセフ#god_se	891,{
	if(countitem(7840) < 1) {
		mes "[ルミィ・ラビセフ]";
		mes "…………？";
		mes "仕事中です。";
		close;
	}
	mes "[ルミィ・ラビセフ]";
	mes "その花は……";
	mes "……………………";
	next;
	mes "[ルミィ・ラビセフ]";
	mes "……失礼ですが、";
	mes "貴方の資格を確認します。";
	next;
	if(strcharinfo(0) != getguildmaster(getcharid(2))) {
		mes "[ルミィ・ラビセフ]";
		mes "あなたには資格がありません。";
		next;
		mes "[ルミィ・ラビセフ]";
		mes "あなたがその花をどうやって";
		mes "手に入れたのかは分かりませんが、";
		mes "誰かを導けるくらいの資質がなければ";
		mes "これを使う事はできません。";
		next;
		mes "[ルミィ・ラビセフ]";
		mes "冷たいと思うでしょうけど、";
		mes "仕方ないのです。仕事ですから。";
		close;
	}
	mes "[ルミィ・ラビセフ]";
	mes "……確認できました。";
	mes "貴方はその花を使う資格がある……";
	next;
	mes "[ルミィ・ラビセフ]";
	mes "その花の使い道について";
	mes "もう知っているかも知れませんが、";
	mes "とりあえず説明をしましょう。";
	next;
	mes "[ルミィ・ラビセフ]";
	mes "ヴァルキリー、ウィッシュメイデン様が";
	mes "下賜してくださった恵み深い聖なる花。";
	mes "その花は特定の召喚師を通じて";
	mes "その場所に特定のモンスターを";
	mes "召喚させる事ができる能力を";
	mes "持っています。";
	next;
	mes "[ルミィ・ラビセフ]";
	mes "その花を利用する事ができる召喚師は";
	mes "この世にただ二人しかいません。";
	mes "……私と、私の双子の妹のルフィです。";
	mes "あまり似ていない双子の姉妹ですが、";
	mes "力は同じですからご心配なく。";
	next;
	mes "[ルミィ・ラビセフ]";
	mes "では……";
	mes "召喚の儀式を行ってよろしいですか？";
	next;
	if(select("^ff0000また今度^000000","^0000ff儀式を行う^000000") == 1) {
		mes "[ルミィ・ラビセフ]";
		mes "……そうですか。";
		mes "用事が無いときはあまり";
		mes "声をかけないでくださいね。";
		next;
		mes "[ルミィ・ラビセフ]";
		mes "まあ、こうして人の相手をするのも、";
		mes "仕事の内ではあるのですけどね。";
		mes "ふぅ。";
		close;
	}
	mes "[ルミィ・ラビセフ]";
	mes "では、少し";
	mes "召喚儀式について説明します。";
	next;
	mes "[ルミィ・ラビセフ]";
	mes "この花を利用した召喚儀式とは、";
	mes "現在我々がいるこのジュノーに";
	mes "『^0000ffヴァルキリーの祝福^000000』と";
	mes "『^0000ffヴァルキリーの贈り物^000000』を";
	mes "召喚する事でして、";
	mes "その効果は^00ff00約1時間^000000持続します。";
	next;
	mes "[ルミィ・ラビセフ]";
	mes "召喚儀式をしている間、";
	mes "全世界に声が届きます。";
	mes "世界中の冒険者達が一緒に";
	mes "楽しめるお祭りになるようにとの";
	mes "ヴァルキリー、ウィッシュメイデン様の";
	mes "ご配慮です。";
	next;
	mes "[ルミィ・ラビセフ]";
	mes "では、";
	mes "準備はよろしいですか？";
	next;
	if(select("^ff0000まだです^000000","^0000ffはい^000000") == 1) {
		mes "[ルミィ・ラビセフ]";
		mes "……ここまで言わせておいて";
		mes "まだ準備ができてないのですか？";
		next;
		mes "[ルミィ・ラビセフ]";
		mes "まあ、準備できてないと言われたら";
		mes "待つしかないのですが……";
		mes "これも仕事の内ですから……";
		mes "ふぅ……";
		close;
	}
	mes "[ルミィ・ラビセフ]";
	mes "では時間の確認をします。";
	mes "……………………";
	next;
	if($@gqse_festival != 0) {
		mes "[ルミィ・ラビセフ]";
		mes "あらっ、もうどこかで";
		mes "ヴァルキリー、ウィッシュメイデン様の";
		mes "召喚儀式が行われているようですね。";
		next;
		mes "[ルミィ・ラビセフ]";
		mes "もう少ししてから来てください。";
		close;
	}
	mes "[ルミィ・ラビセフ]";
	mes "良いでしょう。";
	mes "それでは、召喚儀式を始めます。";
	next;
	mes "[ルミィ・ラビセフ]";
	mes "楽しい時間を！";
	delitem 7840,1;
	donpcevent "ルミィ・ラビセフ#god_se::OnStart";
	announce "[" +strcharinfo(2)+ "]ギルドの[" +strcharinfo(0)+ "]様により、[ジュノー]に『ヴァルキリーの贈り物』召喚儀式が始まります。",8;
	close;
OnCall:
	set '@count,getmapmobs("yuno.gat","ルミィ・ラビセフ#god_se::OnKilled");
	if('@count < 31) {
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの祝福",1083,100,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1951,25,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1952,25,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1953,25,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1954,25,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの悪戯",1002,10,"ルミィ・ラビセフ#god_se::OnKilled";
	}
	else if('@count > 149) {
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの祝福",1083,1,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1951,1,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1952,1,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1953,1,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1954,1,"ルミィ・ラビセフ#god_se::OnKilled";
	}
	else {
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの祝福",1083,50,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1951,10,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1952,10,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1953,10,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの贈り物",1954,10,"ルミィ・ラビセフ#god_se::OnKilled";
		areamonster "yuno.gat",0,0,0,0,"ヴァルキリーの悪戯",1002,5,"ルミィ・ラビセフ#god_se::OnKilled";
	}
	end;
OnStart:
	initnpctimer;
	set $@gqse_festival,1;
	end;
OnStop:
	killmonster "yuno.gat","ルミィ・ラビセフ#god_se::OnKilled";
	set $@gqse_festival,0;
	stopnpctimer;
	end;
OnTimer10000:
	announce "約5分後、[ジュノー]にヴァルキリー・ウィッシュメイデンの『ヴァルキリーの贈り物』が召喚される予定です。",8;
	end;
OnTimer120000:
	announce "約3分後、[ジュノー]にヴァルキリー・ウィッシュメイデンの『ヴァルキリーの贈り物』が召喚される予定です。",8;
	end;
OnTimer240000:
	announce "約1分後、[ジュノー]にヴァルキリー・ウィッシュメイデンの『ヴァルキリーの贈り物』が召喚される予定です。",8;
	end;
OnTimer300000: OnTimer600000: OnTimer900000: OnTimer1200000:
OnTimer1500000:OnTimer1800000:OnTimer2100000:OnTimer2400000:
OnTimer2700000:OnTimer3000000:OnTimer3300000:OnTimer3600000:
	announce "只今、[ジュノー]にヴァルキリー・ウィッシュメイデンの第" +$@gqse_festival+ "次『ヴァルキリーの贈り物』が召喚されました。",8;
	set $@gqse_festival,$@gqse_festival + 1;
	donpcevent "ルミィ・ラビセフ#god_se::OnCall";
	end;
OnTimer303000: OnTimer603000: OnTimer903000: OnTimer1203000:
OnTimer1503000:OnTimer1803000:OnTimer2103000:OnTimer2403000:
OnTimer2703000:OnTimer3003000:OnTimer3303000:
	announce "『ヴァルキリーの贈り物』は約5分おきに連続召喚され、召喚儀式は全12回、約1時間持続する予定です。",8;
	end;
OnTimer13000:  OnTimer123000: OnTimer243000:
OnTimer308000: OnTimer608000: OnTimer908000: OnTimer1208000:
OnTimer1508000:OnTimer1808000:OnTimer2108000:OnTimer2408000:
OnTimer2708000:OnTimer3008000:OnTimer3308000:
	announce "召喚の瞬間を共に楽しみたい方々は、今すぐ[ジュノー]へお越しください。",8;
	end;
OnTimer3900000:
	announce "ヴァルキリー・ウィッシュメイデンの『ヴァルキリーの贈り物』召喚儀式は全て終了しました。",8;
	donpcevent "ルミィ・ラビセフ#god_se::OnStop";
	end;
}

//============================================================
// ルフィ・ラビセフ
//------------------------------------------------------------
rachel.gat,132,117,3	script	ルフィ・ラビセフ#god_se	891,{
	if(countitem(7840) < 1) {
		mes "[ルフィ・ラビセフ]";
		mes "仕事中ですから";
		mes "話しかけないでください！";
		close;
	}
	mes "[ルフィ・ラビセフ]";
	mes "花を持っていますね！";
	mes "ではでは～、あなたの資格を";
	mes "確認します！";
	next;
	if(strcharinfo(0) != getguildmaster(getcharid(2))) {
		mes "[ルフィ・ラビセフ]";
		mes "うーん、あなたには資格は";
		mes "なさそうですね。";
		next;
		mes "[ルフィ・ラビセフ]";
		mes "あなたがその花をどうやって";
		mes "手に入れたのかは分かりませんが、";
		mes "誰かを導けるくらいの資質がなければ";
		mes "これを使う事はできませんよ。";
		next;
		mes "[ルフィ・ラビセフ]";
		mes "冷たいと思うでしょうけど、";
		mes "仕方ないのです。仕事ですから。";
		close;
	}
	mes "[ルフィ・ラビセフ]";
	mes "へぇ～～～";
	mes "そんな眠そうな顔して";
	mes "ギルドマスターだなんて、";
	mes "ギルドメンバーに散々";
	mes "こき使われてるでしょう？";
	mes "ま、とりあえず資格はありっと……";
	next;
	mes "[ルフィ・ラビセフ]";
	mes "その花の使い道について";
	mes "もう知っているかも知れないけど、";
	mes "ちょっとだけ説明してあげますね！";
	next;
	mes "[ルフィ・ラビセフ]";
	mes "ヴァルキリー、ウィッシュメイデン様が";
	mes "下賜してくださった恵み深い聖なる花！";
	mes "その花は特定の召喚師を通じて";
	mes "その場所に特定のモンスターを";
	mes "召喚させる事ができる能力を";
	mes "持っているのです！";
	next;
	mes "[ルフィ・ラビセフ]";
	mes "その花を利用する事ができる召喚師は";
	mes "この世にただ二人だけ！";
	mes "私と、私の双子の姉のルミィです。";
	mes "あんまり似ていない双子だけど、";
	mes "力は同じだから心配無用ですよ！";
	next;
	mes "[ルフィ・ラビセフ]";
	mes "じゃあ……";
	mes "召喚の儀式を行っていいですか？";
	next;
	if(select("召喚しない","召喚する") == 1) {
		mes "[ルフィ・ラビセフ]";
		mes "むぅ……";
		next;
		mes "[ルフィ・ラビセフ]";
		mes "用がないのであれば、";
		mes "声をかけないでくださいよ。";
		mes "もし私がお姉さんだったら、";
		mes "ただでは済まなかったはずですよ？";
		close;
	}
	mes "[ルフィ・ラビセフ]";
	mes "じゃあ、ちょっとだけ";
	mes "召喚儀式について説明しますね。";
	next;
	mes "[ルフィ・ラビセフ]";
	mes "この花を利用した召喚儀式とは、";
	mes "今私たちがいるこのラヘルに";
	mes "『^0000ffヴァルキリーの祝福^000000』と";
	mes "『^0000ffヴァルキリーの贈り物^000000』を";
	mes "召喚する事で、";
	mes "効果は^00ff00約1時間^000000持続します。";
	next;
	mes "[ルフィ・ラビセフ]";
	mes "召喚儀式をしている間、";
	mes "全世界に声が届きます。";
	mes "世界中の冒険者達が一緒に";
	mes "楽しめるお祭りになるようにとの";
	mes "ヴァルキリー、ウィッシュメイデン様の";
	mes "ご配慮なのです。";
	next;
	mes "[ルフィ・ラビセフ]";
	mes "では、";
	mes "準備はいいですか？";
	next;
	if(select("^ff0000まだです^000000","^0000ffはい^000000") == 1) {
		mes "[ルフィ・ラビセフ]";
		mes "……ここまで言わせておいて";
		mes "まだ準備ができてないの？";
		next;
		mes "[ルフィ・ラビセフ]";
		mes "まあ、準備できてないと言われたら";
		mes "待ちますけどね。";
		mes "これも仕事の内だしね。";
		close;
	}
	mes "[ルフィ・ラビセフ]";
	mes "じゃあ召喚儀式が出来るか";
	mes "ちょっと時間を確認しますね。";
	next;
	if($@gqse_festival != 0) {
		mes "[ルフィ・ラビセフ]";
		mes "あれれ、もうどこかで";
		mes "ヴァルキリー、ウィッシュメイデン様の";
		mes "召喚儀式が行われているみたいです。";
		next;
		mes "[ルフィ・ラビセフ]";
		mes "もう少ししてから来てください！";
		close;
	}
	mes "[ルフィ・ラビセフ]";
	mes "大丈夫みたいですね。";
	mes "それじゃあ、召喚儀式を始めますね。";
	next;
	mes "[ルフィ・ラビセフ]";
	mes "楽しい時間を！";
	delitem 7840,1;
	donpcevent "ルフィ・ラビセフ#god_se::OnStart";
	announce "[" +strcharinfo(2)+ "]ギルドの[" +strcharinfo(0)+ "]様により、[ラヘル]に『ヴァルキリーの贈り物』召喚儀式が始まります。",8;
	close;
OnCall:
	set '@count,getmapmobs("rachel.gat","ルフィ・ラビセフ#god_se::OnKilled");
	if('@count < 31) {
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの祝福",1083,100,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1951,25,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1952,25,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1953,25,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1954,25,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの悪戯",1002,10,"ルフィ・ラビセフ#god_se::OnKilled";
	}
	else if('@count > 149) {
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの祝福",1083,1,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1951,1,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1952,1,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1953,1,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1954,1,"ルフィ・ラビセフ#god_se::OnKilled";
	}
	else {
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの祝福",1083,50,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1951,10,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1952,10,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1953,10,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの贈り物",1954,10,"ルフィ・ラビセフ#god_se::OnKilled";
		areamonster "rachel.gat",0,0,0,0,"ヴァルキリーの悪戯",1002,5,"ルフィ・ラビセフ#god_se::OnKilled";
	}
	end;
OnStart:
	initnpctimer;
	set $@gqse_festival,1;
	end;
OnStop:
	killmonster "rachel.gat","ルフィ・ラビセフ#god_se::OnKilled";
	set $@gqse_festival,0;
	stopnpctimer;
	end;
OnTimer10000:
	announce "約5分後、[ラヘル]にヴァルキリー・ウィッシュメイデンの『ヴァルキリーの贈り物』が召喚される予定です。",8;
	end;
OnTimer120000:
	announce "約3分後、[ラヘル]にヴァルキリー・ウィッシュメイデンの『ヴァルキリーの贈り物』が召喚される予定です。",8;
	end;
OnTimer240000:
	announce "約1分後、[ラヘル]にヴァルキリー・ウィッシュメイデンの『ヴァルキリーの贈り物』が召喚される予定です。",8;
	end;
OnTimer300000: OnTimer600000: OnTimer900000: OnTimer1200000:
OnTimer1500000:OnTimer1800000:OnTimer2100000:OnTimer2400000:
OnTimer2700000:OnTimer3000000:OnTimer3300000:OnTimer3600000:
	announce "只今、[ラヘル]にヴァルキリー・ウィッシュメイデンの第" +$@gqse_festival+ "次『ヴァルキリーの贈り物』が召喚されました。",8;
	set $@gqse_festival,$@gqse_festival + 1;
	donpcevent "ルフィ・ラビセフ#god_se::OnCall";
	end;
OnTimer303000: OnTimer603000: OnTimer903000: OnTimer1203000:
OnTimer1503000:OnTimer1803000:OnTimer2103000:OnTimer2403000:
OnTimer2703000:OnTimer3003000:OnTimer3303000:
	announce "『ヴァルキリーの贈り物』は約5分おきに連続召喚され、召喚儀式は全12回、約1時間持続する予定です。",8;
	end;
OnTimer13000:  OnTimer123000: OnTimer243000:
OnTimer308000: OnTimer608000: OnTimer908000: OnTimer1208000:
OnTimer1508000:OnTimer1808000:OnTimer2108000:OnTimer2408000:
OnTimer2708000:OnTimer3008000:OnTimer3308000:
	announce "召喚の瞬間を共に楽しみたい方々は、今すぐ[ラヘル]へお越しください。",8;
	end;
OnTimer3900000:
	announce "ヴァルキリー・ウィッシュメイデンの『ヴァルキリーの贈り物』召喚儀式は全て終了しました。",8;
	donpcevent "ルフィ・ラビセフ#god_se::OnStop";
	end;
}
