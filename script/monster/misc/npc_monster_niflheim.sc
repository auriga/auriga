//= Auriga Script ==============================================================
// Ragnarok Online Niflheim Monster Spawn Script　　Ep 15.2
//==============================================================================

//============================================================
// 死者の街ニブルヘイム - niflheim.gat
//------------------------------------------------------------
niflheim.gat,0,0,0,0	monster	キューブ	1508,75,5000,0,0
niflheim.gat,0,0,0,0	monster	ルード	1509,75,5000,0,0

niflheim.gat,0,0,0	script	#NifMVP	-1,{
OnInit:
	initnpctimer;
	end;
OnTimer7980000:
	switch(rand(7)) {
	case 0:
		monster "niflheim.gat",327,193,"ロードオブデス",1373,1,"#NifMVP::OnKilled1";
		monster "niflheim.gat",330,193,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",324,193,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",327,196,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",327,190,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",324,190,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",330,190,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",324,196,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",330,196,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		break;
	case 1:
		monster "niflheim.gat",337,252,"ロードオブデス",1373,1,"#NifMVP::OnKilled1";
		monster "niflheim.gat",337,255,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",337,249,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",334,252,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",340,252,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",334,249,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",340,255,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",340,249,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",334,255,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		break;
	case 2:
		monster "niflheim.gat",190,185,"ロードオブデス",1373,1,"#NifMVP::OnKilled1";
		monster "niflheim.gat",190,188,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",190,182,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",193,185,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",187,185,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",187,182,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",193,182,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",193,188,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",187,188,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		break;
	case 3:
		monster "niflheim.gat",131,138,"ロードオブデス",1373,1,"#NifMVP::OnKilled1";
		monster "niflheim.gat",131,141,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",131,135,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",128,138,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",134,138,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",134,141,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",128,141,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",134,135,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",128,135,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		break;
	case 4:
		monster "niflheim.gat",311,64,"ロードオブデス",1373,1,"#NifMVP::OnKilled1";
		monster "niflheim.gat",311,67,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",311,61,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",308,64,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",314,64,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",314,61,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",314,67,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",308,67,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",308,61,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		break;
	case 5:
		monster "niflheim.gat",238,131,"ロードオブデス",1373,1,"#NifMVP::OnKilled1";
		monster "niflheim.gat",238,134,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",238,128,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",235,131,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",241,131,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",235,128,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",235,134,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",241,128,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",241,134,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		break;
	case 6:
		monster "niflheim.gat",86,219,"ロードオブデス",1373,1,"#NifMVP::OnKilled1";
		monster "niflheim.gat",86,222,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",86,216,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",89,219,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",83,219,"ブラッディマーダー",1507,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",89,222,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",89,216,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",83,222,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		monster "niflheim.gat",83,216,"ロリルリ",1505,1,"#NifMVP::OnKilled2";
		break;
	}
	monster "niflheim.gat",154,95,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",115,65,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",330,195,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",151,83,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",285,245,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",235,135,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",265,48,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",186,139,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",166,267,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",82,202,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",219,44,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",287,44,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",275,165,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",138,204,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",299,39,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",31,154,"ディスガイズ",1506,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",154,96,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",116,65,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",151,84,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",286,245,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",330,196,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",236,135,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",165,49,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",167,267,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",82,203,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",220,44,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",287,45,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",287,44,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",276,166,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",139,205,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",300,39,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	monster "niflheim.gat",31,155,"デュラハン",1504,1,"#NifMVP::OnKilled2";
	stopnpctimer;
	end;
OnKilled1:
	killmonster "niflheim.gat","#NifMVP::OnKilled2";
	initnpctimer;
	end;
OnKilled2:
	end;	//ダミーイベント
}
