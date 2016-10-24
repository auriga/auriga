// カプラギルド倉庫サービス	テストスクリプト
prontera.gat,165,188,4	script	ギルド倉庫カプラ	112,{
	cutin "kafra_06",2;
	mes "[ギルド倉庫カプラ]";
	mes "カプラギルド倉庫サービスです。";
	mes "毎度ご利用ありがとうございます♪";
	mes "テスト用なので金は貰いません。";
	next;
	if(select("ギルド倉庫を利用する","やっぱやめる") == 1) {
		set '@flag,guildopenstorage();
		switch('@flag) {
		case 0:
			break;	// 成功
		case 1:
			mes "[ギルド倉庫カプラ]";
			mes "ギルドメンバーが倉庫を使用中です。";
			mes "しばらく待ってから利用してください。";
			break;
		case 2:
			mes "[ギルド倉庫カプラ]";
			mes "ギルドに所属してない方は利用する";
			mes "ことができません。";
			break;
		case 3:
			mes "[ギルド倉庫カプラ]";
			mes "お客様の倉庫を開く準備をしています。";
			mes "しばらく待ってから利用してください。";
			break;
		}
	}
	else {
		mes "[ギルド倉庫カプラ]";
		mes "またのご利用をお待ちしています♪";
	}
	close2;
	cutin "kafra_06",255;
	end;
}
