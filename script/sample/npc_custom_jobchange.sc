//-----------------------------------------------------------------------------
// 転職カプラ	<3次職対応版>
//-----------------------------------------------------------------------------
prontera.gat,161,192,5	script	転職カプラ	114,{
	cutin "kafra_04",2;
	mes "[転職カプラ]";
	mes "いらっしゃいませ。";
	mes "こちらでは、転職する事が出来ます。";
	mes "転職をご希望ですか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[転職カプラ]";
		mes "またご利用ください。";
		close2;
		cutin "kafra_04",255;
		end;
	}
	if(getskilllv(1) < 9) {
		mes "[転職カプラ]";
		mes "基本スキルが足りません。";
		mes "基本スキルレベルを上げてから";
		mes "またお越しください。";
		close2;
		cutin "kafra_04",255;
		end;
	}
	if(SkillPoint) {
		mes "[転職カプラ]";
		mes "スキルポイントが残っています。";
		mes "全て消費してきてから";
		mes "またお越しください。";
		close2;
		cutin "kafra_04",255;
		end;
	}
	// 職業IDセット
	set '@job_id,0;
	switch(Job) {
		case Job_Novice:
			setarray '@job_id,Job_Swordman,Job_Magician,Job_Archer,Job_Acolyte,Job_Merchant,Job_Thief;
			if(Upper != UPPER_HIGH) {
				set '@job_id[getarraysize('@job_id)],Job_SuperNovice;
			}
			if(Upper == UPPER_NORMAL) {
				setarray '@job_id[getarraysize('@job_id)],Job_Taekwon,Job_Gunslinger,Job_Ninja,Job_Gyangsy;
			}
			break;
		case Job_Swordman:
			if(Upper == UPPER_HIGH) {
				set '@job_id,OLD_CLASS;
			}
			else {
				setarray '@job_id,Job_Knight,Job_Crusader;
			}
			break;
		case Job_Magician:
			if(Upper == UPPER_HIGH) {
				set '@job_id,OLD_CLASS;
			}
			setarray '@job_id,Job_Wizard,Job_Sage;
			break;
		case Job_Archer:
			if(Upper == UPPER_HIGH) {
				set '@job_id,OLD_CLASS;
			}
			else if(Sex) {
				setarray '@job_id,Job_Hunter,Job_Bard;
			}
			else {
				setarray '@job_id,Job_Hunter,Job_Dancer;
			}
			break;
		case Job_Acolyte:
			if(Upper == UPPER_HIGH) {
				set '@job_id,OLD_CLASS;
			}
			setarray '@job_id,Job_Priest,Job_Monk;
			break;
		case Job_Merchant:
			if(Upper == UPPER_HIGH) {
				set '@job_id,OLD_CLASS;
			}
			setarray '@job_id,Job_Blacksmith,Job_Alchemist;
			break;
		case Job_Thief:
			if(Upper == UPPER_HIGH) {
				set '@job_id,OLD_CLASS;
			}
			setarray '@job_id,Job_Assassin,Job_Rogue;
			break;
		case Job_Taekwon:
			setarray '@job_id,Job_Star,Job_Linker;
			break;
		case Job_Gyangsy:
			setarray '@job_id,Job_DeathKnight,Job_DarkCollector;
			break;
		case Job_Knight:
			set '@job_id,Job_RuneKnight;
			break;
		case Job_Priest:
			set '@job_id,Job_ArchBishop;
			break;
		case Job_Wizard:
			set '@job_id,Job_Warlock;
			break;
		case Job_Blacksmith:
			set '@job_id,Job_Mechanic;
			break;
		case Job_Hunter:
			set '@job_id,Job_Ranger;
			break;
		case Job_Assassin:
			set '@job_id,Job_Guillotine;
			break;
		case Job_Crusader:
			set '@job_id,Job_RoyalGuard;
			break;
		case Job_Monk:
			set '@job_id,Job_Shura;
			break;
		case Job_Sage:
			set '@job_id,Job_Sorcerer;
			break;
		case Job_Rogue:
			set '@job_id,Job_ShadowChaser;
			break;
		case Job_Alchemist:
			set '@job_id,Job_Genetic;
			break;
		case Job_Bard:
			set '@job_id,Job_Minstrel;
			break;
		case Job_Dancer:
			set '@job_id,Job_Wanderer;
			break;
		case Job_SuperNovice:
			setarray '@job_id,Job_ExpandedSuperNovice;
			break;
		case Job_Ninja:
			if(Sex) {
				setarray '@job_id,Job_Kagerou;
			}
			else {
				setarray '@job_id,Job_Oboro;
			}
			break;
	}
	if('@job_id[0] == 0) {
		mes "[転職カプラ]";
		mes "残念ながら、あなたに";
		mes "ご案内できる職業がありません。";
		mes "またお越しください。";
		close2;
		cutin "kafra_04",255;
		end;
	}
	mes "[転職カプラ]";
	mes "あなたにご案内できる職業は";
	mes "次の通りです。";
	mes "どの職業に転職されますか？";
	next;
	// 職業名セット
	set '@job_name$,"";
	set '@max,getarraysize('@job_id);
	for(set '@i,0; '@i < '@max; set '@i,'@i + 1) {
		switch('@job_id['@i]) {
			case Job_Swordman:
				set '@job_name$['@i],"ソードマン";
				break;
			case Job_Magician:
				set '@job_name$['@i],"マジシャン";
				break;
			case Job_Archer:
				set '@job_name$['@i],"アーチャー";
				break;
			case Job_Acolyte:
				set '@job_name$['@i],"アコライト";
				break;
			case Job_Merchant:
				set '@job_name$['@i],"マーチャント";
				break;
			case Job_Thief:
				set '@job_name$['@i],"シーフ";
				break;
			case Job_Knight:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"ロードナイト";
				}
				else {
					set '@job_name$['@i],"ナイト";
				}
				break;
			case Job_Priest:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"ハイプリースト";
				}
				else {
					set '@job_name$['@i],"プリースト";
				}
				break;
			case Job_Wizard:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"ハイウィザード";
				}
				else {
					set '@job_name$['@i],"ウィザード";
				}
				break;
			case Job_Blacksmith:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"ホワイトスミス";
				}
				else {
					set '@job_name$['@i],"ブラックスミス";
				}
				break;
			case Job_Hunter:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"スナイパー";
				}
				else {
					set '@job_name$['@i],"ハンター";
				}
				break;
			case Job_Assassin:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"アサシンクロス";
				}
				else {
					set '@job_name$['@i],"アサシン";
				}
				break;
			case Job_Crusader:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"パラディン";
				}
				else {
					set '@job_name$['@i],"クルセイダー";
				}
				break;
			case Job_Monk:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"チャンピオン";
				}
				else {
					set '@job_name$['@i],"モンク";
				}
				break;
			case Job_Sage:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"プロフェッサー";
				}
				else {
					set '@job_name$['@i],"セージ";
				}
				break;
			case Job_Rogue:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"チェイサー";
				}
				else {
					set '@job_name$['@i],"ローグ";
				}
				break;
			case Job_Alchemist:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"クリエイター";
				}
				else {
					set '@job_name$['@i],"アルケミスト";
				}
				break;
			case Job_Bard:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"クラウン";
				}
				else {
					set '@job_name$['@i],"バード";
				}
				break;
			case Job_Dancer:
				if(Upper == UPPER_HIGH) {
					set '@job_name$['@i],"ジプシー";
				}
				else {
					set '@job_name$['@i],"ダンサー";
				}
				break;
			case Job_SuperNovice:
				set '@job_name$['@i],"スーパーノービス";
				break;
			case Job_Taekwon:
				set '@job_name$['@i],"テコンキッド";
				break;
			case Job_Star:
				set '@job_name$['@i],"拳聖";
				break;
			case Job_Linker:
				set '@job_name$['@i],"ソウルリンカー";
				break;
			case Job_Gunslinger:
				set '@job_name$['@i],"ガンスリンガー";
				break;
			case Job_Ninja:
				set '@job_name$['@i],"忍者";
				break;
			case Job_Gyangsy:
				if(Sex) {
					set '@job_name$['@i],"ボンゴン";
				}
				else {
					set '@job_name$['@i],"ムナック";
				}
				break;
			case Job_DeathKnight:
				set '@job_name$['@i],"デスナイト";
				break;
			case Job_DarkCollector:
				set '@job_name$['@i],"ダークコレクター";
				break;
			case Job_RuneKnight:
				set '@job_name$['@i],"ルーンナイト";
				break;
			case Job_Warlock:
				set '@job_name$['@i],"ウォーロック";
				break;
			case Job_Ranger:
				set '@job_name$['@i],"レンジャー";
				break;
			case Job_ArchBishop:
				set '@job_name$['@i],"アークビショップ";
				break;
			case Job_Mechanic:
				set '@job_name$['@i],"メカニック";
				break;
			case Job_Guillotine:
				set '@job_name$['@i],"ギロチンクロス";
				break;
			case Job_RoyalGuard:
				set '@job_name$['@i],"ロイヤルガード";
				break;
			case Job_Sorcerer:
				set '@job_name$['@i],"ソーサラー";
				break;
			case Job_Minstrel:
				set '@job_name$['@i],"ミンストレル";
				break;
			case Job_Wanderer:
				set '@job_name$['@i],"ワンダラー";
				break;
			case Job_Shura:
				set '@job_name$['@i],"修羅";
				break;
			case Job_Genetic:
				set '@job_name$['@i],"ジェネティック";
				break;
			case Job_ShadowChaser:
				set '@job_name$['@i],"シャドウチェイサー";
				break;
			case Job_ExpandedSuperNovice:
				set '@job_name$['@i],"拡張スーパーノービス";
				break;
			case Job_Kagerou:
				set '@job_name$['@i],"影狼";
				break;
			case Job_Oboro:
				set '@job_name$['@i],"朧";
				break;
		}
	}
	set '@job_name$['@max],"やめる";
	set @menu,select(printarray('@job_name$));
	if('@job_id[@menu - 1] == 0) {
		mes "[転職カプラ]";
		mes "またご利用ください。";
		close2;
		cutin "kafra_04",255;
		end;
	}
	set '@sel_job,'@job_id[@menu - 1];
	mes "[転職カプラ]";
	mes "^FF0000" +'@job_name$[@menu - 1]+ "^000000に";
	mes "転職されますか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[転職カプラ]";
		mes "またご利用ください。";
		close2;
		cutin "kafra_04",255;
		end;
	}
	// 転職チェック（直前）
	switch('@sel_job) {
		case Job_Swordman:
		case Job_Magician:
		case Job_Archer:
		case Job_Acolyte:
		case Job_Merchant:
		case Job_Thief:
		case Job_Taekwon:
		case Job_Gunslinger:
		case Job_Ninja:
		case Job_Gyangsy:
			if(getskilllv(1) < 9) {
				mes "[転職カプラ]";
				mes "基本スキルが足りません。";
				mes "基本スキルレベルを上げてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			if(JobLevel < 10) {
				mes "[転職カプラ]";
				mes "一次職に転職するには";
				mes "Jobレベルが10必要です。";
				mes "Jobレベルを上げてきてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			break;
		case Job_SuperNovice:
			if(getskilllv(1) < 9) {
				mes "[転職カプラ]";
				mes "基本スキルが足りません。";
				mes "基本スキルレベルを上げてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			if(JobLevel < 10) {
				mes "[転職カプラ]";
				mes "スーパーノービスに転職するには";
				mes "Jobレベルが40必要です。";
				mes "Jobレベルを上げてきてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			if(BaseLevel < 45) {
				mes "[転職カプラ]";
				mes "スーパーノービスに転職するには";
				mes "Baseレベルが45以上必要です。";
				mes "Baseレベルを上げてきてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			break;
		case Job_Knight:
		case Job_Priest:
		case Job_Wizard:
		case Job_Blacksmith:
		case Job_Hunter:
		case Job_Assassin:
		case Job_Crusader:
		case Job_Monk:
		case Job_Sage:
		case Job_Rogue:
		case Job_Alchemist:
		case Job_Bard:
		case Job_Dancer:
		case Job_Star:
		case Job_Linker:
		case Job_DeathKnight:
		case Job_DarkCollector:
			if(JobLevel < 40) {
				mes "[転職カプラ]";
				mes "二次職に転職するには";
				mes "Jobレベルが40以上必要です。";
				mes "Jobレベルを上げてきてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			break;
		case Job_RuneKnight:
		case Job_Warlock:
		case Job_Ranger:
		case Job_ArchBishop:
		case Job_Mechanic:
		case Job_Guillotine:
		case Job_RoyalGuard:
		case Job_Sorcerer:
		case Job_Minstrel:
		case Job_Wanderer:
		case Job_Shura:
		case Job_Genetic:
		case Job_ShadowChaser:
// 国内仕様
//			if(Upper != UPPER_HIGH) {
//				mes "[転職カプラ]";
//				mes "三次職に転職するには";
//				mes "転生されている必要があります。";
//				mes "またお越しください。";
//				close2;
//				cutin "kafra_04",255;
//				end;
//			}
//			if(BaseLevel < 90) {
//				mes "[転職カプラ]";
//				mes "三次職に転職するには";
//				mes "Baseレベルが90以上必要です。";
//				mes "Baseレベルを上げてきてから";
//				mes "またお越しください。";
//				close2;
//				cutin "kafra_04",255;
//				end;
//			}
// 海外仕様
			if(BaseLevel < 99) {
				mes "[転職カプラ]";
				mes "三次職に転職するには";
				mes "Baseレベルが99必要です。";
				mes "Baseレベルを上げてきてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			break;
		case Job_ExpandedSuperNovice:
			if(JobLevel < 99) {
				mes "[転職カプラ]";
				mes "拡張スーパーノービスに転職するには";
				mes "Jobレベルが99必要です。";
				mes "Jobレベルを上げてきてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			if(BaseLevel < 99) {
				mes "[転職カプラ]";
				mes "拡張スーパーノービスに転職するには";
				mes "Baseレベルが99必要です。";
				mes "Baseレベルを上げてきてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			break;
		case Job_Kagerou:
		case Job_Oboro:
			if(JobLevel < 70) {
				mes "[転職カプラ]";
				mes '@job_name$[0] + "に転職するには";
				mes "Jobレベルが70必要です。";
				mes "Jobレベルを上げてきてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			if(BaseLevel < 99) {
				mes "[転職カプラ]";
				mes '@job_name$[0] + "に転職するには";
				mes "Baseレベルが99必要です。";
				mes "Baseレベルを上げてきてから";
				mes "またお越しください。";
				close2;
				cutin "kafra_04",255;
				end;
			}
			break;
	}
	if(SkillPoint) {
		mes "[転職カプラ]";
		mes "スキルポイントが残っています。";
		mes "全て消費してきてから";
		mes "またお越しください。";
		close2;
		cutin "kafra_04",255;
		end;
	}
	unequip;
	jobchange '@sel_job;
	mes "[転職カプラ]";
	mes "転職おめでとうございます！";
	mes "貴方のご活躍に期待しています。";
	close2;
	cutin "kafra_04",255;
	end;
}
