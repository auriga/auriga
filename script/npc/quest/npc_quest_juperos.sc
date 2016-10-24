//= Athena Script ==============================================================
// Ragnarok Online Juperos Script     by Blaze
//==============================================================================

//============================================================
// Warp
//------------------------------------------------------------
yuno_fild07.gat,208,175,0	script	juperoswarp0401		139,2,2{ warp "jupe_cave.gat",143,52; end; }
jupe_cave.gat,147,52,0		script	juperoswarp0501		139,2,2{ warp "yuno_fild07.gat",212,175; end; }
jupe_cave.gat,29,52,0		warp	juperoswarp4001		3,3,juperos_01.gat,54,246
juperos_01.gat,51,249,0		warp	juperoswarp4002		3,3,jupe_cave.gat,36,51
juperos_01.gat,100,91,0		script	juperoswarp4003		139,2,2{
	initnpctimer;
	mes "^797979["+strcharinfo(0)+"]^000000";
	mes "暖かい光に包まれている。";
	mes "まるで、体が宙に";
	mes "浮かんでいるかのようだ……。";
	mes "ああ……。";
	next;
	if(select("もう少しの間、この光に包まれていたい……","あっ！　そんなこと考えてる場合じゃない！")==1) {
		misceffect 348,"";
		mes "^797979["+strcharinfo(0)+"]^000000";
		mes "ああ……。";
		mes "体が軽くなっていく気がする……。";
		next;
		warp "juperos_02.gat",128,278;
		end;
	}
	mes "^797979["+strcharinfo(0)+"]^000000";
	mes "この光はどこから来ているんだ?!";
	mes "すぐに、ここから離れなきゃ……。";
	next;
	warp "juperos_01.gat",96,91;
	end;
OnTimer10000:
	areawarp "juperos_01.gat",98,89,102,93,"juperos_02",128,278;
	stopnpctimer;
	end;
}
juperos_02.gat,33,59,0		script	juperoswarp4004		45,2,2{
	switch(rand(4)) {
	case 0: warp "juperos_01.gat",79,72; end;
	case 1: warp "juperos_01.gat",79,112; end;
	case 2: warp "juperos_01.gat",120,72; end;
	case 3: warp "juperos_01.gat",120,112; end;
	}
}
juperos_02.gat,130,149,0	script	juperoswarp4005		139,2,2{ warp "jupe_gate.gat",50,167; end; }
jupe_gate.gat,50,171,0		script	juperoswarp4006		139,4,0{
	initnpctimer;
	mes "^797979["+strcharinfo(0)+"]^000000";
	mes "上の層に戻ることができる";
	mes "ワープのようだ。";
	next;
	if(select("ワープに身を任せる","ワープから離れる")==1) {
		misceffect 348,"";
		mes "^797979["+strcharinfo(0)+"]^000000";
		mes "体が軽くなったような感じがする……。";
		next;
		warp "juperos_02.gat",130,142;
		end;
	}
	mes "^797979["+strcharinfo(0)+"]^000000";
	mes "まだ上の層には戻らない！";
	next;
	warp "jupe_gate.gat",50,168;
	end;
OnTimer10000:
	areawarp "jupe_gate.gat",46,171,53,171,"juperos_02",130,142;
	stopnpctimer;
	end;
}
jupe_gate.gat,28,145,0		warp	juperoswarp4007		1,1,jupe_area1.gat,101,222
jupe_area1.gat,103,222,0	warp	juperoswarp4008		1,1,jupe_gate.gat,30,145
jupe_gate.gat,71,145,0		warp	juperoswarp4009		1,1,jupe_area2.gat,63,222
jupe_area2.gat,60,222,0		warp	juperoswarp4010		1,1,jupe_gate.gat,69,145
jupe_gate.gat,49,55,0		warp	juperoswarp4011		1,1,jupe_ele_r.gat,49,29
jupe_ele_r.gat,49,27,0		warp	juperoswarp4012		1,1,jupe_gate.gat,49,53
jupe_ele.gat,41,33,0		warp	juperoswarp4013		4,4,jupe_core.gat,150,286

//============================================================
// ゲート制御装置
//------------------------------------------------------------
juperos_02.gat,0,0,0	script	ゲート制御装置#juperos	-1,{
OnInit:
	hideonnpc "juperoswarp4005";
	set 'jupe_gate,3;
	monster "juperos_02.gat",24,275,"第1ゲート制御装置",1674,1,"ゲート制御装置#juperos::OnKilled";
	monster "juperos_02.gat",240,29,"第2ゲート制御装置",1674,1,"ゲート制御装置#juperos::OnKilled";
	monster "juperos_02.gat",282,183,"第3ゲート制御装置",1674,1,"ゲート制御装置#juperos::OnKilled";
	end;
OnKilled:
	set 'jupe_gate,'jupe_gate-1;
	switch('jupe_gate) {
	case 2: announce "誰かね？　ここへ来たのは……。",9,0xFF0000; break;
	case 1: announce "残念だが、ここはかつてのジュピロスではないがな……。",9,0xFF0000; break;
	default:
		announce "時間を与えよう！　我に会いたければ、探し出すがよい！",9,0xFF0000;
		areamisceffect "juperos_02.gat",0,0,300,300,563;
		areasoundeffect "juperos_02.gat",0,0,300,300,"earth_quake.wav",0;
		sleep 5000;
		announce "ウィイイーーンッ！　ウィイイーーンッ！",9,0xE55AA4;
		areasoundeffect "juperos_02.gat",0,0,300,300,"jupe_warning.wav",0;
		sleep 2000;
		announce "訪問者に告げます。",9,0xE55AA4;
		sleep 2000;
		announce "少しの間、次の区域への立ち入りを許可します。ゲートへお入りください。",9,0xE55AA4;
		hideoffnpc "juperoswarp4005";
		misceffect 561,"juperoswarp4005";
		set 't,26;
		initnpctimer;
	}
	end;
OnTimer23000:
	set 't,'t-1;
	misceffect 561,"juperoswarp4005";
	if('t == 2) {
		sleep 4000;
		announce "訪問者に告げます。まもなく、次の区域へ通じるゲートが閉じます。",9,0xE55AA4;
		sleep 5000;
		announce "ゲートが閉じるまで、あと約1分です。",9,0xE55AA4;
	}
	if('t == 0) {
		sleep 2000;
		hideonnpc "juperoswarp4005";
		announce "ゲートが閉じました。",9,0xE55AA4;
		sleep 3000;
		announce "制御装置は再稼動準備に入ります。",9,0xE55AA4;
		end;
	}
	initnpctimer;
	end;
OnTimer602000:
	stopnpctimer;
	donpcevent "ゲート制御装置#juperos::OnInit";
	end;
}

//============================================================
// 保安区域
//------------------------------------------------------------
jupe_area1.gat,0,0,0	script	jupe_area1	-1,{
OnSummon1:
	set 'flag,1;
	initnpctimer;
	sleep 1000;
	announce "ここまで辿り着いた者らよ……。",9,0xFF0000;
	sleep 2000;
	announce "我はお前らを阻もうと考えてはおらぬ。",9,0xFF0000;
	areasoundeffect "this",0,0,164,300,"jupe_warning.wav",0;
	sleep 2000;
	announce "しかし、この閉鎖された地に敢えて来たからには",9,0xFF0000;
	set 'mob,8;
	monster "jupe_area1.gat",30,263,"保安要員",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",30,262,"保安要員",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",30,261,"保安要員",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",30,260,"保安要員",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",30,259,"保安要員",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",30,258,"保安要員",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",30,257,"保安要員",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",30,256,"保安要員",1669,1,"jupe_area1::OnKilled";
	sleep 2000;
	announce "覚悟はできているだろうな？",9,0xFF0000;
	sleep 1000;
	areasoundeffect "this",0,0,164,300,"jupe_warning.wav",0;
	end;
OnSummon2:
	announce "さて、今度はどうかな？",9,0xFF0000;
	areasoundeffect "this",0,0,164,300,"jupe_warning.wav",0;
	sleep 2000;
	announce "もう一度……",9,0xFF0000;
	sleep 2000;
	announce "実力を見せるがよい！",9,0xFF0000;
	areasoundeffect "this",0,0,164,300,"jupe_warning.wav",0;
	set 'mob,8;
	monster "jupe_area1.gat",30,238,"保安要員",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",31,238,"保安要員",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",32,238,"保安要員",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",33,238,"保安要員",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",34,238,"保安要員",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",35,238,"保安要員",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",36,238,"保安要員",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",37,238,"保安要員",1669,1,"jupe_area1::OnKilled";
	end;
OnSummon3:
	set 'flag,4;
	initnpctimer;
	sleep 2000;
	announce "まだまだまだ……。",9,0xFF0000;
	sleep 2000;
	announce "さあ、来るがよい、我の所まで！",9,0xFF0000;
	set 'mob,8;
	monster "jupe_area1.gat",30,176,"上級警備兵",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",31,176,"上級警備兵",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",32,176,"上級警備兵",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",33,176,"上級警備兵",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",34,176,"上級警備兵",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",35,176,"上級警備兵",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",36,176,"上級警備兵",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",37,176,"上級警備兵",1675,1,"jupe_area1::OnKilled";
	sleep 2000;
	announce "我が誰なのか、知りたいかね？",9,0xFF0000;
	sleep 2000;
	announce "では、こいつらに勝ったら教えてやろう！",9,0xFF0000;
	end;
OnSummon4:
	announce "我は、この地下研究所の所長、",9,0xFF0000;
	sleep 2000;
	announce "いや、所長だった……",9,0xFF0000;
	sleep 2000;
	announce "ヴェスパー・ニュトーン。人は、物狂いヴェスパーと呼んだがな。",9,0xFF0000;
	set 'mob,13;
	monster "jupe_area1.gat",30,152,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",31,152,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",32,152,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",33,152,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",34,152,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",35,152,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",36,152,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",37,152,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",30,150,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",31,150,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",32,150,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",33,150,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",34,150,"ガードマン",1669,1,"jupe_area1::OnKilled";
	end;
OnSummon5:
	set 'flag,7;
	initnpctimer;
	sleep 2000;
	announce "我は、ここへの立ち入りを阻むために",9,0xFF0000;
	sleep 2000;
	announce "警備システムを作ったのではない。",9,0xFF0000;
	set 'mob,8;
	monster "jupe_area1.gat",30,89,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",31,89,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",32,89,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",33,89,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",34,89,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",35,89,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",36,89,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",37,89,"ガードマン",1669,1,"jupe_area1::OnKilled";
	sleep 2000;
	announce "では、何のためにかと……？　フッ、余興だよ。",9,0xFF0000;
	sleep 2000;
	announce "永遠に死ぬことができぬ、我のためにな!!",9,0xFF0000;
	end;
OnSummon6:
	announce "ここまで何しに来たんだ？",9,0xFF0000;
	sleep 2000;
	announce "この下に何かあると思っているのかね？",9,0xFF0000;
	sleep 2000;
	announce "言っておくが、この下は地獄だぞ！",9,0xFF0000;
	set 'mob,15;
	monster "jupe_area1.gat",42,64,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",43,64,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",44,64,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",45,64,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",46,64,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",47,64,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",48,64,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",49,64,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",42,62,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",43,62,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",44,62,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",45,62,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",46,62,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",47,62,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",48,62,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",49,62,"ガードマン",1675,1,"jupe_area1::OnKilled";
	end;
OnSummon7:
	set 'flag,10;
	initnpctimer;
	sleep 2000;
	announce "我に勝つ者を探していた。",9,0xFF0000;
	sleep 2000;
	announce "この言葉を聞いている者が、その者なのだろうか？",9,0xFF0000;
	set 'mob,8;
	monster "jupe_area1.gat",92,154,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",96,154,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",100,154,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",104,154,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",92,161,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",96,161,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",100,161,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",104,161,"ガードマン",1675,1,"jupe_area1::OnKilled";
	sleep 2000;
	announce "……変わり果てた我が肉体は、",9,0xFF0000;
	sleep 2000;
	announce "この下のどこかにあるであろう。",9,0xFF0000;
	end;
OnSummon8:
	announce "我は死ぬことができぬ！",9,0xFF0000;
	sleep 2000;
	announce "ならば我は、ここで強き者を待とう。",9,0xFF0000;
	sleep 2000;
	announce "永遠に、未来永劫にな！",9,0xFF0000;
	set 'mob,10;
	monster "jupe_area1.gat",104,161,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",108,161,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",111,161,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",112,161,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",115,161,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",104,154,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",108,154,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",111,154,"ガードマン",1669,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",112,154,"ガードマン",1675,1,"jupe_area1::OnKilled";
	monster "jupe_area1.gat",115,154,"ガードマン",1669,1,"jupe_area1::OnKilled";
	end;
OnKilled:
	set 'mob,'mob-1;
	if('mob == 0) {
		sleep 2000;
		switch('flag) {
		case 1: donpcevent "jupe_area1::OnSummon2"; break;
		case 2: announce "チック、チック、チック……。",9,0xFF0000; break;
		case 4: donpcevent "jupe_area1::OnSummon4"; break;
		case 5: announce "……まだまだだ。",9,0xFF0000; break;
		case 7: donpcevent "jupe_area1::OnSummon6"; break;
		case 8: announce "それでもというのなら、行くがよい！",9,0xFF0000; break;
		case 10: donpcevent "jupe_area1::OnSummon8"; break;
		case 11: announce "楽しめたかね？",9,0xFF0000; break;
		}
		set 'flag,'flag+1;
	}
	end;
OnTimer600000:
	if(rand(2))
		announce "逃げたのか……。",9,0xFF0000;
	else
		announce "ケッ……腰抜けめ……。",9,0xFF0000;
	sleep 2000;
	stopnpctimer;
	areawarp "this",0,0,70,300,"jupe_gate.gat",49,138;
	areawarp "this",70,0,164,200,"jupe_gate.gat",49,138;
	killmonster "this","All";
	set 'mob,0;
	set 'flag,0;
	end;
}

jupe_area1.gat,88,224,0	script	#jupe_area1-1	844,{
	set '@id,substr(strnpcinfo(2),11,1);
	cutin '@id,2;
	if(getvariableofnpc('flag,"jupe_area1") != ('@id-1)*3) {
		mes "-ある模様が描かれた穴がある。";
		mes "何かを入れることができそうだ-";
		mes "-向こう側へ渡るための装置のようだ-";
		close2;
		cutin '@id,255;
		end;
	}
	mes "-どこかで見たような穴がある。";
	mes "何かを入れることができそうだ-";
	mes "-向こう側へ渡るための";
	mes "装置かもしれない……-";
	next;
	if(select("紋章の欠片をはめてみる","何もしない")==1) {
		if(countitem(7355+'@id)) {
			cutin '@id+"-1",2;
			misceffect 159;
			mes "-持っていた紋章の欠片が";
			mes "ぴったりはまった-";
			next;
			mes "-紋章の欠片をはめた穴が動き、";
			mes "地面から小さな震動を感じた-";
			mes "-向こう側へ行くための";
			mes "ワープが作動したようだ-";
			mes "-紋章の欠片を回収した-";
			hideonnpc;
			hideoffnpc "juperoswarp" + '@id + "#jupe_area1";
			misceffect 561,"juperoswarp" + '@id + "#jupe_area1";
			soundeffect "jupe_warp.wav",0;
			initnpctimer;
		}
		else {
			mes "-穴に入るような物を";
			mes "持っていない-";
		}
	}
	else {
		mes "[" +strcharinfo(0)+ "]";
		mes "こんなものに構っている暇はない……。";
	}
	close2;
	cutin '@id,255;
	end;
OnTimer22000:
	stopnpctimer;
	hideonnpc "juperoswarp" +substr(strnpcinfo(2),11,1)+ "#jupe_area1";
	hideoffnpc;
	end;
}
jupe_area1.gat,25,238,0	duplicate(#jupe_area1-1)	#jupe_area1-2	844
jupe_area1.gat,36,146,0	duplicate(#jupe_area1-1)	#jupe_area1-3	844
jupe_area1.gat,50,49,0	duplicate(#jupe_area1-1)	#jupe_area1-4	844

jupe_area1.gat,112,162,0	script	レバー#jupe_area1	844,{
	mes "[わからない装置]";
	mes "レバーがある。";
	if(getvariableofnpc('flag,"jupe_area1") != 12)
		close;
	mes "引くことができそうだ。";
	next;
	if(select("レバーを引く","やめる")==1) {
		hideonnpc;
		hideoffnpc "juperoswarp5#jupe_area1";
		misceffect 561,"juperoswarp5#jupe_area1";
		soundeffect "jupe_warp.wav",0;
		initnpctimer;
		close;
	}
	mes "[" +strcharinfo(0)+ "]";
	mes "こんなものに構っている暇はない……。";
	close;
OnTimer22000:
	stopnpctimer;
	hideonnpc "juperoswarp5#jupe_area1";
	hideoffnpc;
	end;
}

jupe_area1.gat,83,221,0	script	juperoswarp1#jupe_area1	139,2,2{
	set '@n,substr(strnpcinfo(1),11,1);
	switch('@n) {
	case 1: warp "jupe_area1.gat",47,259; break;
	case 2: warp "jupe_area1.gat",21,191; break;
	case 3: warp "jupe_area1.gat",33,105; break;
	case 4: warp "jupe_area1.gat",83,157; break;
	}
	if(getvariableofnpc('flag,"jupe_area1") == ('@n-1)*3)
		donpcevent "jupe_area1::OnSummon"+('@n*2-1)+"";
	end;
OnInit:
	hideonnpc;
	end;
}
jupe_area1.gat,21,225,0	duplicate(juperoswarp1#jupe_area1)	juperoswarp2#jupe_area1	139,2,2
jupe_area1.gat,33,137,0	duplicate(juperoswarp1#jupe_area1)	juperoswarp3#jupe_area1	139,2,2
jupe_area1.gat,57,53,0	duplicate(juperoswarp1#jupe_area1)	juperoswarp4#jupe_area1	139,2,2
jupe_area1.gat,117,157,0	script	juperoswarp5#jupe_area1	139,2,2,{
	warp "jupe_gate.gat",28,29;
	end;
OnInit:
	hideonnpc;
	end;
}

//============================================================
// エレベーター
//------------------------------------------------------------
jupe_ele_r.gat,51,98,0	script	スイッチ進行中#jupe_ele	844,{
	mes "-この機械は、";
	mes "誰かが使用しているようだ-";
	close;
OnInit:
	hideonnpc;
	end;
OnKilled:
	set 'mob,'mob-1;
	if('mob == 0) {
		stopnpctimer "スイッチ#jupe_ele";
		sleep 5000;
		announce "幻影を破りし者らよ、更に奥へ進んでみないか？",9,0x66FF00;
		areasoundeffect "jupe_ele_r.gat",0,0,100,160,"earth_quake.wav",0;
		sleep 4000;
		disablenpc "juperoswarp4013";
		areawarp "jupe_ele_r.gat",0,0,100,160,"jupe_ele.gat",42,47;
		donpcevent "jupe_ele::OnSummon1";
		initnpctimer "jupe_ele";
		end;
	}
	end;
}

jupe_ele_r.gat,51,98,0	script	スイッチ#jupe_ele	844,{
	cutin "5",2;
	mes "-何かを作動させることが";
	mes "できそうなレバーと、";
	mes "用途不明な4個の穴がある-";
	next;
	if(select("レバーを引いてみる","触らない")==2) {
		mes "-得体の知れない物には";
		mes "触らない方がいい……-";
		close2;
		cutin "5",255;
		end;
	}
	mes "-^797979カチャ、カチャ^000000-";
	next;
	mes "-^797979レバーを引いてみたが、";
	mes "何も反応がない^000000-";
	mes "-レバーの横にある穴に";
	mes "何かを入れると作動するようだ-";
	if(countitem(7356) < 1 && countitem(7357) < 1 && countitem(7358) < 1 && countitem(7359) < 1) {
		close2;
		cutin "5",255;
		end;
	}
	next;
	menu "紋章の欠片をはめてみる",-;
	if(countitem(7356) < 1 || countitem(7357) < 1 || countitem(7358) < 1 || countitem(7359) < 1) {
		mes "-紋章の欠片が足りないようだ-";
		mes "-どうやら、全ての紋章の欠片を";
		mes "一緒にはめなければならないようだ-";
		close2;
		cutin "5",255;
		end;
	}
	initnpctimer;
	hideonnpc;
	hideoffnpc "スイッチ進行中#jupe_ele";
	misceffect 72;
	areamisceffect "jupe_ele_r.gat",0,0,100,160,563;
	delitem 7356,1;
	delitem 7357,1;
	delitem 7358,1;
	delitem 7359,1;
	cutin "5-1",2;
	mes "-この部屋を覆っていたたくさんの";
	mes "紋章の欠片が降ってきた-";
	mes "-これでは、もう回収することが";
	mes "できない-";
	close2;
	cutin "5",255;
	end;
OnTimer2000:
	announce "……後世の子孫たちよ……。",9,0x66FF00;
	sleep 3000;
	announce "何故、この都市が地に埋もれたか、知りたいか……？",9,0x66FF00;
	sleep 4000;
	announce "ならば、進むがよい。",9,0x66FF00;
	sleep 3000;
	announce "お前らが望むものを見せてあげよう。",9,0x66FF00;
	sleep 7000;
	announce "但し、全ての幻影と……",9,0xFF9900;
	sleep 3000;
	announce "全ての偽りを乗り越えればな……。",9,0xFF0000;
	sleep 3000;
	announce "20分の時を与えよう",9,0xFF0000;
	sleep 1000;
	set getvariableofnpc('mob,"スイッチ進行中#jupe_ele"),9;
	monster "jupe_ele_r.gat",44,99,"警備兵",1669,1,"スイッチ進行中#jupe_ele::OnKilled";
	sleep 200;
	monster "jupe_ele_r.gat",55,99,"警備兵",1675,1,"スイッチ進行中#jupe_ele::OnKilled";
	sleep 200;
	monster "jupe_ele_r.gat",45,84,"警備兵",1683,1,"スイッチ進行中#jupe_ele::OnKilled";
	sleep 200;
	monster "jupe_ele_r.gat",54,84,"警備兵",1675,1,"スイッチ進行中#jupe_ele::OnKilled";
	sleep 200;
	monster "jupe_ele_r.gat",45,99,"警備兵",1669,1,"スイッチ進行中#jupe_ele::OnKilled";
	sleep 200;
	monster "jupe_ele_r.gat",54,99,"警備兵",1683,1,"スイッチ進行中#jupe_ele::OnKilled";
	sleep 200;
	monster "jupe_ele_r.gat",48,84,"警備兵",1669,1,"スイッチ進行中#jupe_ele::OnKilled";
	sleep 200;
	monster "jupe_ele_r.gat",52,84,"警備兵",1683,1,"スイッチ進行中#jupe_ele::OnKilled";
	sleep 200;
	monster "jupe_ele_r.gat",50,84,"警備隊長",1684,1,"スイッチ進行中#jupe_ele::OnKilled";
	announce "我はしばしの間、幻影と共にいよう。",9,0xFF0000;
	end;
OnTimer144000:
	stopnpctimer;
	announce "期待外れだったか……。",9,0x66FF00;
	sleep 2000;
	areawarp "jupe_ele_r.gat",0,0,100,160,"jupe_gate.gat",49,138;
	killmonster "this","All";
	hideonnpc "スイッチ進行中#jupe_ele";
	hideoffnpc "スイッチ#jupe_ele";
	end;
}

jupe_ele.gat,0,0,0	script	jupe_ele	-1,{
OnSummon1:
	sleep 2000;
	announce "ここまで辿り着いたお前らの根性に、敬意を表する。",9,0xFF0000;
	sleep 3000;
	announce "さて……このあらゆるものは落とし穴なのか、もしくは侵入者をあぶり出すためのまやかしなのか、",9,0xFF0000;
	sleep 3000;
	announce "試してみるかね……。",9,0xFF0000;
	sleep 4000;
	set 'mob,8;
	monster "jupe_ele.gat",48,44,"警備兵",1675,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",45,42,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",38,42,"警備兵",1675,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",35,44,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",35,51,"警備兵",1675,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",38,53,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",45,53,"警備兵",1675,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",48,51,"警備兵",1669,1,"jupe_ele::OnKilled";
	end;
OnSummon2:
	sleep 2000;
	announce "ここは元々、お前らが思うような",9,0xFF0000;
	sleep 3000;
	announce "成熟し繁栄を極めた文化都市ではなかった。",9,0xFF0000;
	sleep 3000;
	announce "人間の真の恐ろしさを全て融合させ……",9,0xFF0000;
	sleep 3000;
	announce "遥かに人間の想像を超えた場所。",9,0xFF0000;
	sleep 1000;
	set 'mob,8;
	monster "jupe_ele.gat",48,44,"警備兵",1683,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",45,42,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",38,42,"警備兵",1683,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",35,44,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",35,51,"警備兵",1683,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",38,53,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",45,53,"警備兵",1683,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",48,51,"警備兵",1669,1,"jupe_ele::OnKilled";
	end;
OnSummon3:
	sleep 2000;
	announce "お前らの目に、ここにあるものはどう見えている？",9,0xFF0000;
	sleep 3000;
	announce "それは、本当に見えているのか？",9,0xFF0000;
	sleep 3000;
	announce "それとも……そう見えると信じているだけではないのか？",9,0xFF0000;
	sleep 4000;
	set 'mob,8;
	monster "jupe_ele.gat",48,44,"警備兵",1675,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",45,42,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",38,42,"警備兵",1683,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",35,44,"警備兵",1675,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",35,51,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",38,53,"警備兵",1683,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",45,53,"警備兵",1675,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",48,51,"警備兵",1669,1,"jupe_ele::OnKilled";
	end;
OnSummon4:
	sleep 2000;
	announce "忘れるでないぞ……いつかお前らの首をしめるのは……",9,0xFF0000;
	sleep 3000;
	announce "紛れもなく、お前ら自身だぞ。",9,0xFF0000;
	sleep 3000;
	set 'mob,8;
	monster "jupe_ele.gat",48,44,"警備兵",1684,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",45,42,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",38,42,"警備兵",1684,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",35,44,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",35,51,"警備兵",1675,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",38,53,"警備兵",1669,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",45,53,"警備兵",1683,1,"jupe_ele::OnKilled";
	monster "jupe_ele.gat",48,51,"警備兵",1675,1,"jupe_ele::OnKilled";
	end;
OnClear:
	sleep 2000;
	announce "我は何も言ってはおらぬ。",9,0x66FF00;
	sleep 3000;
	announce "これをお前らが聞く頃には、恐らく……我らの都市はこの世から消えているであろう。",9,0x66FF00;
	sleep 3000;
	announce "全てのことが間違いであった。我らは、ここにいてはならぬ存在であった。",9,0x66FF00;
	sleep 3000;
	announce "人間は、ここにいてもよいのだろうか？",9,0x66FF00;
	sleep 1000;
	announce "……願うならば、更に奥へ進むがよい。",9,0x66FF00;
	enablenpc "juperoswarp4013";
	end;
OnKilled:
	set 'mob,'mob-1;
	if('mob == 0) {
		sleep 2000;
		switch('flag) {
		case 0: donpcevent "jupe_ele::OnSummon2"; break;
		case 1: donpcevent "jupe_ele::OnSummon3"; break;
		case 2: donpcevent "jupe_ele::OnSummon4"; break;
		case 3: donpcevent "jupe_ele::OnClear"; break;
		}
		set 'flag,'flag+1;
	}
	end;
OnTimer144000:
	stopnpctimer;
	announce "期待外れだったか……。",9,0x66FF00;
	sleep 2000;
	areawarp "jupe_ele.gat",0,0,100,124,"jupe_gate.gat",49,138;
	killmonster "this","All";
	set 'flag,0;
	hideonnpc "スイッチ進行中#jupe_ele";
	hideoffnpc "スイッチ#jupe_ele";
	end;
}
