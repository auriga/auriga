
// ペットスキル用	テストスクリプト

prontera.gat,160,180,1	script	ペットスキル	112,{
	mes "攻撃スキルを選択してください。";
	next;
	switch( select("なし", "バッシュ", "ファイアーボルト", "ストームガスト") ) {
	case 1: set @num, -1; break;
	case 2: set @num,  5; break;
	case 3: set @num, 19; break;
	case 4: set @num, 89; break;
	}
	petskillattack @num, 10, 50, 0; // 発動率50%

	mes "支援スキルを選択してください。";
	next;
	switch( select("なし", "ヒール", "ブレッシング", "サンクチュアリ") ) {
	case 1: set @num, -1; break;
	case 2: set @num, 28; break;
	case 3: set @num, 34; break;
	case 4: set @num, 70; break;
	}
	petskillsupport @num, 10, 30, 20, 100; // HP 20% 以下で発動
	close;
}

