//==============================================================================
// Ragnarok Online Job Group Functions
//==============================================================================
//	Grp_Novice  ：　　ノービス系列（ノービス、スーパーノービス）
//	Grp_Swordman：　ソードマン系列（ソードマン、ナイト、クルセイダー）
//	Grp_Magician：　マジシャン系列（マジシャン、ウィザード、セージ）
//	Grp_Archer  ：　アーチャー系列（アチャ、ハンタ、バード、ダンサー）
//	Grp_Acolyte ：　アコライト系列（アコライト、プリースト、モンク）k
//	Grp_Merchant：マーチャント系列（マーチャント、ブラックスミス、アルケミスト）
//	Grp_Thief   ：　　　シーフ系列（シーフ、アサシン、ローグ）
//	Grp_TaeKwon ：　　　テコン系列（テコンキッド、拳聖、ソウルリンカー）
//------------------------------------------------------------------------------
function	script	JobGroup	{
	set '@cnt, 0;
	while(getargcount() > '@cnt) {
		switch(getarg('@cnt)) {
		case Grp_Novice:
			if(Class == Job_Novice || Class == Job_SuperNovice)
				return 1;
			break;
		case Grp_Swordman:
			if(Class == Job_Swordman || Class == Job_Knight || Class == Job_Crusader)
				return 1;
			break;
		case Grp_Magician:
			if(Class == Job_Magician || Class == Job_Wizard || Class == Job_Sage)
				return 1;
			break;
		case Grp_Archer:
			if(Class == Job_Archer || Class == Job_Hunter || Class == Job_Bard || Class == Dancer)
				return 1;
			break;
		case Grp_Acolyte:
			if(Class == Job_Acolyte || Class == Job_Priest || Class == Job_Monk)
				return 1;
			break;
		case Grp_Merchant:
			if(Class == Job_Merchant || Class == Job_Blacksmith || Class == Job_Alchemist)
				return 1;
			break;
		case Grp_Thief:
			if(Class == Job_Thief || Class == Job_Assassin || Class == Job_Rogue)
				return 1;
			break;
		case Grp_TaeKwon:
			if(Class == Job_TaeKwon || Class == Job_StarGladiator || Class == Job_SoulLinker)
				return 1;
			break;
		}
		set '@cnt, '@cnt + 1;
	}
	return 0;
}
