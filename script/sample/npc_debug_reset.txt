prontera.gat,152,192,4	script	リセット職員	117,{
	cutin "kafra_01",2;
	mes "[リセット職員]";
	mes "いらっしゃいませ";
	mes "こちらではステータス、スキルの";
	mes "リセットを行えます。";
	next;
	mes "[リセット職員]";
	mes "リセット料金は300Zenyです。";
	next;
	set @menu,select("ステータスリセット","スキルリセット","終了");
	if(@menu < 3) {
		if(Zeny < 300) {
			mes "[カプラ職員]";
			mes "お客様、お金が足りません。";
			mes "所持金をお確かめください。";
		}
		else {
			set Zeny,Zeny-300;
			if(@menu == 1)
				resetstatus;
			else
				resetskill;
			mes "[リセット職員]";
			mes "リセット完了しました。";
			mes "利用してくださってありがとうございます。";
		}
	}
	close2;
	cutin "kafra_01",255;
	end;
}
