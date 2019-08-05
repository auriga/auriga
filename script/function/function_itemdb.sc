//==============================================================================
// Ragnarok Online Itemdb Functions
//==============================================================================

//============================================================
// 巨大なハエの羽
//------------------------------------------------------------
function	script	ItemdbPartyCall	{
	warp "Random",0,0;
	set '@name$,strcharinfo(0);
	if('@name$ == getpartyleader(getcharid(1)) && !getmapxy('@map$,'@x,'@y,0)) {
		getpartymember getcharid(1);
		for(set '@i,0; '@i < $@partymembercount; set '@i,'@i+1) {
			if($@partymembername$['@i] == '@name$)			// 自分は除外
				continue;
			if(getmapname($@partymembername$['@i]) != '@map$)	// MAPが違う
				continue;
			if(attachrid(getcharid(3,$@partymembername$['@i]))) {
				if(!checkdead()) {
					// 死亡してないならリーダーの元へワープ
					warp '@map$,'@x,'@y;
				}
				detachrid;
			}
		}
	}
	return;
}

//============================================================
// キラキラスティック
//------------------------------------------------------------
function	script	ItemdbResetSkill	{
	if(Weight || checkcart() || checkfalcon() || checkriding())
		return;
	set '@lv,getskilllv(1);	// 基本スキル
	resetskill 0;		// クエストスキルはリセットしない
	if('@lv > 0) {
		skill 1,'@lv,0;
		set SkillPoint,SkillPoint - '@lv;
	}
	return;
}

//============================================================
// ヒール系効果向上総合
//------------------------------------------------------------
function	script	ItemdbAlmightyHeal	{
	set '@flag,getarg(0);
	set '@val,getarg(1);
	if('@flag&1) {
		bonus2 bAddSkillHealRate,28,'@val;	/* ヒール */
		bonus2 bAddSkillDamageRate,28,'@val;
	}
	if('@flag&2) {
		bonus2 bAddSkillHealRate,70,'@val;	/* サンクチュアリ */
		bonus2 bAddSkillDamageRate,70,'@val;
	}
	if('@flag&4)
		bonus2 bAddSkillHealRate,231,'@val;	/* ポーションピッチャー */
	if('@flag&8)
		bonus2 bAddSkillHealRate,478,'@val;	/* スリムポーションピッチャー */
	if('@flag&16)
		bonus2 bAddSkillHealRate,322,'@val;	/* イドゥンの林檎 */
	if('@flag&32) {
		bonus2 bAddSkillHealRate,2043,'@val;	/* コルセオヒール */
		bonus2 bAddSkillDamageRate,2043,'@val;
	}
	if('@flag&64) {
		bonus2 bAddSkillHealRate,2051,'@val;	/* ハイネスヒール */
		bonus2 bAddSkillDamageRate,2051,'@val;
	}
	return;
}

//============================================================
// 被ヒール系効果向上総合
//------------------------------------------------------------
function	script	ItemdbAlmightySubHeal	{
	set '@flag,getarg(0);
	set '@val,getarg(1);
	if('@flag&1)
		bonus2 bAddSkillSubHealRate,28,'@val;	/* ヒール */
	if('@flag&2)
		bonus2 bAddSkillSubHealRate,70,'@val;	/* サンクチュアリ */
	if('@flag&4)
		bonus2 bAddSkillSubHealRate,231,'@val;	/* ポーションピッチャー */
	if('@flag&8)
		bonus2 bAddSkillSubHealRate,478,'@val;	/* スリムポーションピッチャー */
	if('@flag&16)
		bonus2 bAddSkillSubHealRate,322,'@val;	/* イドゥンの林檎 */
	if('@flag&32)
		bonus2 bAddSkillSubHealRate,2043,'@val;	/* コルセオヒール */
	if('@flag&64)
		bonus2 bAddSkillSubHealRate,2051,'@val;	/* ハイネスヒール */
	return;
}
