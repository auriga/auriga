izlude.gat,125,65,4	script	バグりましたか？	825,{
	cutin "ein_soldier",2;
	mes "[バグりましたか？]";
	mes "ども、バグりましたか？";
	mes "ここではキャラクターのスキルについて";
	mes "救済措置となる初期化を行います。";
	mes "拡張１次職まで対応しています。";
	next;
	mes "[バグりましたか？]";
	mes "救済の事なら僕にお任せ下さい。";
	mes "プレイヤーのジョブレベル・職業を判別";
	mes "してスキルリセットを行い、ポイントを";
	mes "初期化して再配布しています。";
	next;
	mes "[バグりましたか？]";
	mes "また、不正チートの事も考えて";
	mes "転職NPCから離して設置しております。";
	next;
	if(select("また今度にします","了解です") == 1) {
		close2;
		cutin "ein_soldier",255;
		end;
	}
	mes "[バグりましたか？]";
	mes "職業判別";
	mes "1次職であれば9P+現在のJoblv-1P";
	mes "2次職または転生であれば";
	mes "9P+Job49P+現在のJoblv-1P";
	mes "という風に配布されます。";
	next;
	switch(Job) {
	case Job_Novice:
		mes "[バグりましたか？]";
		mes "ノビさんの初期化しますね。";
		next;
		resetskill;
		set SkillPoint,JobLevel-1;
		break;
	case Job_Swordman:
	case Job_Magician:
	case Job_Archer:
	case Job_Acolyte:
	case Job_Merchant:
	case Job_Thief:
	case Job_Taekwon:
	case Job_Gunslinger:
	case Job_Ninja:
	case Job_DeathKnight:
	case Job_DarkCollector:
		mes "[バグりましたか？]";
		mes "1次職さんの初期化しますね。";
		next;
		resetskill;
		set SkillPoint,9+JobLevel-1;	// ノビの9Point+今のJob-1
		break;
	default:
		mes "[バグりましたか？]";
		mes "2次職さんの初期化しますね。";
		next;
		resetskill;
		set SkillPoint,58+JobLevel-1;	// ノビの9Point+1次Job50(49P)+現在
		break;
	}
	mes "[バグりましたか？]";
	mes "初期化完了。";
	mes "キャラクターのスキルポイントが";
	mes "元通りになりました。";
	mes "またご利用下さい。";
	mes "ありがとうございました。";
	close2;
	cutin "ein_soldier",255;
	end;
}
