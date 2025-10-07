//====================================================================
//Ragnarok Online - 3rd Class Jobchange Script	by refis
//====================================================================

//============================================================
// Func_Job3rd：転職代行NPC
//  引数(0)	：対象の3次職番号(Job_RuneKnight～Job_ShadowChaser）
//  戻り値	：0) コール元のクエスト続行
//			  1) コール元で会話終了（中断・転職完了など）
//------------------------------------------------------------
function	script	Func_Job3rd	{
	set '@job,getarg(0);
	switch('@job) {
		case Job_RuneKnight:   set '@jobname$,"ルーンナイト";       set '@oldjobname$,"ナイト";         break;
		case Job_Warlock:      set '@jobname$,"ウォーロック";       set '@oldjobname$,"ウィザード";     break;
		case Job_Ranger:       set '@jobname$,"レンジャー";         set '@oldjobname$,"ハンター";       break;
		case Job_ArchBishop:   set '@jobname$,"アークビショップ";   set '@oldjobname$,"プリースト";     break;
		case Job_Mechanic:     set '@jobname$,"メカニック";         set '@oldjobname$,"ブラックスミス"; break;
		case Job_Guillotine:   set '@jobname$,"ギロチンクロス";     set '@oldjobname$,"アサシン";       break;
		case Job_RoyalGuard:   set '@jobname$,"ロイヤルガード";     set '@oldjobname$,"クルセイダー";   break;
		case Job_Sorcerer:     set '@jobname$,"ソーサラー";         set '@oldjobname$,"セージ";         break;
		case Job_Minstrel:     set '@jobname$,"ミンストレル";       set '@oldjobname$,"バード";         break;
		case Job_Wanderer:     set '@jobname$,"ワンダラー";         set '@oldjobname$,"ダンサー";       break;
		case Job_Shura:        set '@jobname$,"修羅";               set '@oldjobname$,"モンク";         break;
		case Job_Genetic:      set '@jobname$,"ジェネティック";     set '@oldjobname$,"アルケミスト";   break;
		case Job_ShadowChaser: set '@jobname$,"シャドウチェイサー"; set '@oldjobname$,"ローグ";         break;
	}
	mes "[転職代行係]";
	mes "お待ち下さい!!";
	next;
	mes "[転職代行係]";
	mes "突然ですが、";
	mes "私、転職代行係と申します。";
	mes "今まさに、";
	mes '@jobname$ + "転職クエストが";
	mes "開始されようとしています。";
	next;
	mes "[転職代行係]";
	mes "このクエストは";
	mes "特殊なクエストとなっております。";
	mes "今からご説明いたしますので";
	mes "少々お付き合いくださいね。";
	next;
	mes "[転職代行係]";
	mes '@jobname$ + "転職クエストは";
	mes '@oldjobname$ + "系の3次職である";
	mes '@jobname$ + "に転職するための";
	mes "クエストです。";
	next;
	mes "[転職代行係]";
	mes "このクエストを開始してクリアした場合、";
	mes "転職できるだけでなく";
	mes "クリア報酬として^FF0000一度だけ利用可能な";
	mes "ステータス・スキル一括リセット権^000000が";
	mes "付与されます。";
	next;
	mes "[転職代行係]";
	mes "また、このクエストは開始せずに";
	mes "体験した扱いにして";
	mes "今すぐ転職することもできます。";
	next;
	mes "[転職代行係]";
	mes "但し、その場合、それ以降は";
	mes "このクエストを体験することはできません。";
	mes "クリア報酬の";
	mes "ステータス・スキル一括リセット権も";
	mes "得ることが出来なくなります。";
	next;
	mes "[転職代行係]";
	mes "あと、少々特別なケースですが、";
	mes "クエストを開始した後、途中で";
	mes "通常と異なる方法で転職した場合、";
	mes "転職後もそのままクエストを";
	mes "体験することになります。";
	next;
	mes "[転職代行係]";
	mes "そういった場合でもクエストをクリアすれば";
	mes "クリア報酬として^FF0000一度だけ利用可能な";
	mes "ステータス・スキル一括リセット権^000000が";
	mes "付与されます。";
	next;
	mes "[転職代行係]";
	mes "また、クエストを体験している間、";
	mes "その時の職業とは違う扱いで";
	mes "話が進むことがあるかもしれません。";
	mes "そんな時は話を合わせて";
	mes "あげてくださいね。";
	next;
	mes "[転職代行係]";
	mes "どちらの選択も、一度行うと";
	mes "再度選びなおすことは出来ませんので";
	mes "慎重に選択してください。";
	next;
	while(1) {
		switch(select("一旦考える","クエストを開始せずに今すぐ転職","クエストを開始する","クエストのクリア報酬について聞く","この場を離れる")) {
		case 1:
			continue;
		case 2:
			mes "[転職代行係]";
			mes "「クエストを開始せずに今すぐ転職」が";
			mes "選択されました。";
			mes "今すぐに転職出来ますが、以降、";
			mes "クエストは体験したものとして扱われ、";
			mes "ステータス・スキル一括リセットの権利も";
			mes "得られません。よろしいですか？";
			next;
			if(select("はい","いいえ") == 2) {
				mes "‐この場を去った‐";
				close2;
				return 1;
			}
			mes "[転職代行係]";
			mes "では、クエストは体験したことにして";
			mes "転職しましょう！";
			next;
			if(SkillPoint) {
				mes "‐スキルポイントが余っているため";
				mes "　進行できません‐";
				close2;
				return 1;
			}
			if(Weight || checkitemblank() < 3 || checkcart() || checkfalcon() || checkriding() || checkdragon() || checkgear() || checkwolf() || sc_ison(SC_ALL_RIDING) || getpetinfo(0)) {
				mes "[転職代行係]";
				mes "あなたは準備しなければ";
				mes "ならないことがありますね。";
				mes "まずは、身を清める為に";
				mes "身のまわりのものを";
				mes "無にしてください。";
				next;
				mes "[転職代行係]";
				mes "アイテム等の荷物を持たない";
				mes "空の状態でなければなりません。";
				mes "旅を共にした動物達やカート、";
				mes "騎乗生物、ペットなども";
				mes "持って行くことはできません。";
				next;
				mes "[転職代行係]";
				mes "それでは……用意ができましたら";
				mes "お越しください。";
				close2;
				return 1;
			}
			if('@job == Job_RuneKnight) {
				mes "[転職代行係]";
				mes "転職する為の準備は万全のようですね。";
				mes "それでは、転職する前に、";
				mes "これからご紹介します装備のうち";
				mes "いずれか1つをお選びください。";
				while(1) {
					next;
					mes "[転職代行係]";
					mes "お選びになった装備が、";
					mes "転職の際に渡されます。";
					mes " ";
					mes "[<ITEM>エナジールーンガード[1]<INFO>2140</INFO></ITEM>]";
					mes "[<ITEM>魔力石の指輪[1]<INFO>2794</INFO></ITEM>]";
					mes "[<ITEM>ルーンプレート[1]<INFO>15002</INFO></ITEM>]";
					next;
					switch(select("エナジールーンガード[1]","魔力石の指輪[1]","ルーンプレート[1]")) {
					case 1:
						set '@item,2140;
						break;
					case 2:
						set '@item,2794;
						break;
					case 3:
						set '@item,15002;
						break;
					}
					mes "[転職代行係]";
					mes getitemname('@item) + "[1]ですね。";
					mes "本当にこちらでよろしいですか？";
					next;
					if(select("はい","いいえ") == 1) {
						break;
					}
					mes "[転職代行係]";
					mes "それでは再度、";
					mes "欲しい装備を";
					mes "お選び下さい。";
					continue;
				}
			}
			resetstatus;
			resetskill;
			setoption 0;
			jobchange '@job;
			switch('@job) {
			case Job_RuneKnight:
				setquest 201180;
				compquest 201180;
				getitem 5746,1;		// ルーンサークレット
				getitem 2795,1;		// 熟していないリンゴの指輪
				getitem '@item,1;	// 選択した装備
				break;
			case Job_Warlock:
				setquest 201185;
				compquest 201185;
				getitem 5753,1;		// 魔力石の帽子
				getitem 2795,1;		// 熟していないリンゴの指輪
				break;
			case Job_Ranger:
				setquest 201190;
				compquest 201190;
				getitem 5748,1;		// スナイパーゴーグル
				getitem 2795,1;		// 熟していないリンゴの指輪
				getitem 6124,1;		// 狼の笛
				break;
			case Job_ArchBishop:
				setquest 201195;
				compquest 201195;
				getitem 5747,1;		// ミトラ
				getitem 2795,1;		// 熟していないリンゴの指輪
				break;
			case Job_Mechanic:
				setquest 201205;
				compquest 201205;
				if(Sex)
					getitem 5749,1;	// ドライバーバンド(male)
				else
					getitem 5760,1;	// ドライバーバンド(female)
				getitem 2795,1;		// 熟していないリンゴの指輪
				break;
			case Job_Guillotine:
				setquest 201200;
				compquest 201200;
				getitem 12106,1;	// 宝石箱
				getitem 2795,1;		// 熟していないリンゴの指輪
				getitem 5755,1;		// 沈黙の執行者
				break;
			case Job_RoyalGuard:
				setquest 201210;
				compquest 201210;
				getitem 5757,1;		// シュミッツのヘルム
				getitem 2795,1;		// 熟していないリンゴの指輪
				break;
			case Job_Sorcerer:
				setquest 201215;
				compquest 201215;
				getitem 5756,1;		// 風のささやき
				getitem 2795,1;		// 熟していないリンゴの指輪
				break;
			case Job_Minstrel:
				setquest 201220;
				compquest 201220;
				getitem 5751,1;		// ミンストレルソングの帽子
				getitem 2795,1;		// 熟していないリンゴの指輪
				break;
			case Job_Wanderer:
				setquest 201225;
				compquest 201225;
				getitem 5758,1;		// バレリーナの髪飾り
				getitem 2795,1;		// 熟していないリンゴの指輪
				break;
			case Job_Shura:
				setquest 201230;
				compquest 201230;
				getitem 5754,1;		// ブレイジングソウル
				getitem 2795,1;		// 熟していないリンゴの指輪
				break;
			case Job_Genetic:
				setquest 201240;
				compquest 201240;
				getitem 5752,1;		// ミダスのささやき
				getitem 2795,1;		// 熟していないリンゴの指輪
				break;
			case Job_ShadowChaser:
				setquest 201235;
				compquest 201235;
				getitem 6121,1;		// フェイスペイントブラシ
				getitem 6122,1;		// ペイントブラシ
				getitem 2795,1;		// 熟していないリンゴの指輪
				getitem 5750,1;		// シャドウクラウン
				break;
			}
			mes "[転職代行係]";
			mes "さあ、これで貴方は";
			mes '@jobname$ + "となりました。";
			mes "見た目も気持ちも一新ですね！";
			close2;
			return 1;
		case 3:
			mes "[転職代行係]";
			mes "「クエストを開始する」が";
			mes "選択されました。";
			mes "クエスト開始後は";
			mes "開始せずに今すぐ転職する選択が";
			mes "出来なくなります。";
			mes "本当によろしいですか？";
			next;
			if(select("はい","やめる") == 2) {
				mes "‐この場を去った‐";
				close2;
				return 1;
			}
			mes "[転職代行係]";
			mes "わかりました。";
			mes "では、クエストを開始します。";
			next;
			return 0;
		case 4:
			mes "[転職代行係]";
			mes '@jobname$ + "転職クエストは";
			mes '@oldjobname$ + "系の3次職である";
			mes '@jobname$ + "に転職するための";
			mes "クエストです。";
			next;
			mes "[転職代行係]";
			mes "このクエストを開始してクリアした場合、";
			mes "転職できるだけでなく";
			mes "クリア報酬として^FF0000一度だけ利用可能な";
			mes "ステータス・スキル一括リセット権^000000が";
			mes "付与されます。";
			next;
			mes "[転職代行係]";
			mes "このサービスはイズルードに居る";
			mes "サンシイの元で受けることが出来ます。";
			next;
			mes "[転職代行係]";
			mes "ステータス・スキル一括リセットをすると、";
			mes "貴方がこれまで割り振った";
			mes "ステータス・スキルがリセットされ";
			mes "これまでに獲得してきた";
			mes "ステータス・スキルポイントが";
			mes "全て手元に戻ります。";
			next;
			mes "[転職代行係]";
			mes "ステータス・スキル一括リセットには";
			mes "いくつか制限があります。";
			mes "まず、所持アイテムの重量を";
			mes "^FF00000^000000にする必要があります。";
			mes "手持ちのアイテムは、";
			mes "倉庫に預けるなどしてください。";
			next;
			mes "[転職代行係]";
			mes "次に、^FF0000カート、ファルコン、";
			mes "ペコペコ、ドラゴン、グリフォン、";
			mes "ウォーグ、魔導ギア、騎乗生物^000000";
			mes "を利用していると";
			mes "サービスを受けられませんので";
			mes "これらは外してきてください。";
			next;
			mes "[転職代行係]";
			mes "ステータスをリセットすると、";
			mes "これまでに獲得してきた";
			mes "ステータスポイントが";
			mes "手元に戻ってきます。";
			next;
			mes "[転職代行係]";
			mes "次にスキルリセットの";
			mes "仕組みについてお話しましょう。";
			next;
			mes "[転職代行係]";
			mes "スキルリセットをすると";
			mes "これまでに獲得してきた";
			mes "1次職分と2次職分、3次職分を";
			mes "合計したスキルポイントが";
			mes "手元に戻ります。";
			next;
			mes "[転職代行係]";
			mes "1次職分に関しての具体例を";
			mes "挙げますと、2次職への転職が";
			mes "JobLv40だった方は39ポイント、";
			mes "JobLv50だった方は49ポイント";
			mes "となります。";
			next;
			mes "[転職代行係]";
			mes "そしてそこへ2次職、";
			mes "3次職で獲得したポイントが";
			mes "追加されます。";
			next;
			mes "[転職代行係]";
			mes "なお、ノービス時に獲得した";
			mes "基本スキルや、応急手当等";
			mes "クエストで習得した追加スキルに";
			mes "関しては、リセットされません。";
			next;
			mes "[転職代行係]";
			mes "それから、転生された方は転生1次職へ";
			mes "転職した後に獲得したスキルが";
			mes "リセットされます。";
			next;
			mes "[転職代行係]";
			mes "では、スキルリセット後の";
			mes "注意事項をお話しします。";
			mes "2次職・上位2次職の方は";
			mes "まず、^FF00001次職・転生1次職分の";
			mes "スキルポイントを割り振って下さい。^000000";
			next;
			mes "[転職代行係]";
			mes "例えば……";
			mes "2次職への転職がJobLv40だった方は";
			mes "1次職の39ポイントを先に";
			mes "1次職用スキルに割り振る形に";
			mes "なります。";
			next;
			mes "[転職代行係]";
			mes "^FF00001次職用のスキルポイントを";
			mes "全て消費しないと、2次職のスキルへ";
			mes "ポイントを割り振ることは";
			mes "できません。^000000";
			next;
			mes "[転職代行係]";
			mes "^FF0000もちろん3次職の方は";
			mes "1次職、2次職用のスキルポイントを";
			mes "全て消費しないと、3次職の";
			mes "スキルへポイントを割り振ることは";
			mes "できません^000000ので、ご注意ください。";
			next;
			mes "[転職代行係]";
			mes "3次職転職クエストのクリア報酬、";
			mes "ステータス・スキル一括リセットの説明は";
			mes "以上です。";
			close2;
			return 1;
		case 5:
			mes "‐この場を去った‐";
			close2;
			return 1;
		}
	}
}

//============================================================
// ステータス・スキル一括リセットNPC
//------------------------------------------------------------
izlude.gat,104,231,3	script	サンシイ	878,{
	mes "[サンシイ]";
	mes "いらっしゃ～い。私は";
	mes "3次職転職クエストのクリア報酬";
	mes "^FF0000ステータス＆スキル一括";
	mes "リセットサービス^000000を";
	mes "一任されているサンシイです。";
	next;
	mes "[サンシイ]";
	mes "権利をお持ちでしたら、";
	mes "^FF0000ステータスリセットと";
	mes "スキルリセットを一括して^000000";
	mes "行うことができますよ。";
	next;
	switch(select("^FF0000ステータス＆スキル一括リセットサービス^000000について教えて","^FF0000ステータス＆スキル一括リセットサービス^000000を利用したい","^FF0000ステータス＆スキル一括リセット権^000000の有無を確認したい","特に何もありません")) {
	case 1:
		mes "[サンシイ]";
		mes "^FF0000ステータス＆スキル一括リセット";
		mes "サービス^000000は";
		mes "^FF0000ステータスリセット^000000と";
		mes "^FF0000スキルリセット^000000を^FF0000一括で^000000";
		mes "行うことができるサービスです。";
		next;
		mes "[サンシイ]";
		mes "権利をお持ちであれば";
		mes "^FF0000ステータスリセット^000000と";
		mes "^FF0000スキルリセット^000000を";
		mes "同時に行うことができます。";
		mes "ただし、どちらか片方だけを";
		mes "行うことはできません。";
		next;
		mes "[サンシイ]";
		mes "また、ご利用の際、";
		mes "お持ちのアイテムは";
		mes "倉庫に預けるなどして";
		mes "所持アイテムの重量を";
		mes "^FF00000^000000にして下さい。";
		next;
		mes "[サンシイ]";
		mes "そして^FF0000カート、ファルコン、";
		mes "ペコペコ、ドラゴン、";
		mes "グリフォン、ウォーグ、魔導ギア、";
		mes "騎乗生物^000000のご利用中は、";
		mes "ステータス＆スキル一括リセット";
		mes "サービスを受けられません。";
		next;
		mes "[サンシイ]";
		mes "お手数ですがカート、ファルコン、";
		mes "ペコペコ、ドラゴン、";
		mes "グリフォン、ウォーグ、";
		mes "魔導ギア、騎乗生物は";
		mes "外してきて下さい。";
		next;
		mes "[サンシイ]";
		mes "では、ステータスリセットの";
		mes "仕組みについてお話ししましょう。";
		mes "ステータスリセットをすると";
		mes "これまでに獲得してきた";
		mes "ステータスポイントが";
		mes "手元に戻ります。";
		next;
		mes "[サンシイ]";
		mes "次にスキルリセットの";
		mes "仕組みについてお話しましょう。";
		next;
		mes "[サンシイ]";
		mes "スキルリセットをすると";
		mes "これまでに獲得してきた";
		mes "1次職分と2次職分、3次職分を";
		mes "合計したスキルポイントが";
		mes "手元に戻ります。";
		next;
		mes "[サンシイ]";
		mes "1次職分に関しての具体例を";
		mes "挙げますと、2次職への転職が";
		mes "JobLv40だった方は39ポイント、";
		mes "JobLv50だった方は49ポイント";
		mes "となります。";
		next;
		mes "[サンシイ]";
		mes "そしてそこへ2次職、";
		mes "3次職で獲得したポイントが";
		mes "追加されます。";
		next;
		mes "[サンシイ]";
		mes "なお、ノービス時に獲得した";
		mes "基本スキルや、応急手当等";
		mes "クエストで習得した追加スキルに";
		mes "関しては、リセットされません。";
		next;
		mes "[サンシイ]";
		mes "では、スキルリセット後の";
		mes "注意事項をお話します。";
		mes "まず、^FF00001次職・転生1次職分の";
		mes "スキルポイントを振って下さい。^000000";
		next;
		mes "[サンシイ]";
		mes "例えば……";
		mes "2次職への転職がJobLv40だった方は";
		mes "1次職用の39ポイントを先に";
		mes "1次職用スキルに割り振る形に";
		mes "なります。";
		next;
		mes "[サンシイ]";
		mes "^FF00001次職用のスキルポイントを";
		mes "全て消費しないと、2次職のスキルへ";
		mes "ポイントを割り振ることは";
		mes "できません。^000000";
		next;
		mes "[サンシイ]";
		mes "^FF0000同じように";
		mes "1次職、2次職用のスキルポイントを";
		mes "全て消費しないと、3次職の";
		mes "スキルへポイントを割り振ることは";
		mes "できません^000000ので、ご注意ください。";
		next;
		mes "[サンシイ]";
		mes "以上がスキルリセットサービスの";
		mes "内容となります。";
		next;
		mes "[サンシイ]";
		mes "最後に、転職クエスト以外で獲得した";
		mes "ステータスリセットや";
		mes "スキルリセットの権利をお持ちでも";
		mes "こちらではお取り扱いしておりません。";
		mes "悪しからずご了承ください。";
		close;
	case 2:
		if(checkquest(129700) == 0) {
			mes "[サンシイ]";
			mes "おや？";
			mes "貴方は権利をお持ちではないようですね。";
			mes "ステータス＆スキル一括リセット";
			mes "サービスは";
			mes "権利をお持ちの方のみ利用可能です。";
			mes "ご了承ください。";
			close;
		}
		if(Weight) {
			mes "[サンシイ]";
			mes "申し訳ございませんが";
			mes "重量が0でなければ、";
			mes "ステータス＆スキル一括リセット";
			mes "サービスを";
			mes "受ける事はできません。";
			next;
			mes "[サンシイ]";
			mes "お荷物を^FF0000倉庫^000000に預けてから";
			mes "お越し下さい。";
			close;
		}
		mes "[サンシイ]";
		mes "分かりました。";
		mes "では先にステータス＆スキル一括リセット";
		mes "サービスについて";
		mes "念のためご説明します。";
		next;
		mes "[サンシイ]";
		mes "ステータス＆スキル一括リセット";
		mes "サービスには、";
		mes "いくつかの制限があります。";
		next;
		mes "[サンシイ]";
		mes "それからお持ちのアイテムは";
		mes "倉庫に預けるなどして";
		mes "所持アイテムの重量を";
		mes "^FF00000^000000にして下さい。";
		next;
		mes "[サンシイ]";
		mes "そして^FF0000カート、ファルコン、";
		mes "ペコペコ、ドラゴン、";
		mes "グリフォン、ウォーグ、魔導ギア、";
		mes "騎乗生物^000000のご利用中は、";
		mes "ステータス＆スキル一括リセット";
		mes "サービスを受けられません。";
		next;
		mes "[サンシイ]";
		mes "お手数ですがカート、ファルコン、";
		mes "ペコペコ、ドラゴン、";
		mes "グリフォン、ウォーグ、";
		mes "魔導ギア、騎乗生物は";
		mes "外してきて下さい。";
		next;
		mes "[サンシイ]";
		mes "では、ステータスリセットの";
		mes "仕組みについてお話ししましょう。";
		mes "ステータスリセットをすると";
		mes "これまでに獲得してきた";
		mes "ステータスポイントが";
		mes "手元に戻ります。";
		next;
		mes "[サンシイ]";
		mes "次にスキルリセットの";
		mes "仕組みについてお話しましょう。";
		next;
		mes "[サンシイ]";
		mes "スキルリセットをすると";
		mes "これまでに獲得してきた";
		mes "1次職分と2次職分、3次職分を";
		mes "合計したスキルポイントが";
		mes "手元に戻ります。";
		next;
		mes "[サンシイ]";
		mes "1次職分に関しての具体例を";
		mes "挙げますと、2次職への転職が";
		mes "JobLv40だった方は39ポイント、";
		mes "JobLv50だった方は49ポイント";
		mes "となります。";
		next;
		mes "[サンシイ]";
		mes "そしてそこへ2次職、";
		mes "3次職で獲得したポイントが";
		mes "追加されます。";
		next;
		mes "[サンシイ]";
		mes "なお、ノービス時に獲得した";
		mes "基本スキルや、応急手当等";
		mes "クエストで習得した追加スキルに";
		mes "関しては、リセットされません。";
		next;
		mes "[サンシイ]";
		mes "では、スキルリセット後の";
		mes "注意事項をお話します。";
		mes "まず、^FF00001次職・転生1次職分の";
		mes "スキルポイントを振って下さい。^000000";
		next;
		mes "[サンシイ]";
		mes "例えば……";
		mes "2次職への転職がJobLv40だった方は";
		mes "1次職用の39ポイントを先に";
		mes "1次職用スキルに割り振る形に";
		mes "なります。";
		next;
		mes "[サンシイ]";
		mes "^FF00001次職用のスキルポイントを";
		mes "全て消費しないと、2次職のスキルへ";
		mes "ポイントを割り振ることは";
		mes "できません。^000000";
		next;
		mes "[サンシイ]";
		mes "^FF0000同じように";
		mes "1次職、2次職用のスキルポイントを";
		mes "全て消費しないと、3次職の";
		mes "スキルへポイントを割り振ることは";
		mes "できません^000000ので、ご注意ください。";
		next;
		mes "[サンシイ]";
		mes "なお、私のサービスは";
		mes "^FF0000ステータスリセットと";
		mes "スキルリセットを";
		mes "一括でのみ行うことができます。^000000";
		mes "それぞれ片方だけご利用になることは";
		mes "できませんので、ご注意下さい。";
		next;
		mes "[サンシイ]";
		mes "説明は以上です。";
		mes "ステータス＆スキル一括リセットを";
		mes "行いますか？";
		next;
		if(select("はい","いいえ") == 2) {
			mes "[サンシイ]";
			mes "そうですか……分かりました。";
			mes "またの機会をお待ちしております。";
			close;
		}
		mes "[サンシイ]";
		mes "準備はいいですね？";
		mes "それでは、";
		mes "イッチ、ニ……";
		next;
		if(checkcart() || checkfalcon() || checkriding() || checkdragon() || checkgear() || checkwolf() || sc_ison(SC_ALL_RIDING)) {
			mes "[サンシイ]";
			mes "申し訳ございませんが、";
			mes "カート、ファルコン、ペコペコ、";
			mes "ドラゴン、グリフォン、ウォーグ、";
			mes "魔導ギア、騎乗生物のご利用中には";
			mes "ステータス＆スキル一括リセット";
			mes "サービスを受けられません。";
			next;
			mes "[サンシイ]";
			mes "カート、ファルコン、";
			mes "ペコペコ、ドラゴン、";
			mes "グリフォン、ウォーグ、";
			mes "魔導ギア、騎乗生物を";
			mes "外して下さい。";
			close;
		}
		delquest 129700;
		resetstatus;
		resetskill;
		mes "[サンシイ]";
		mes "サン、シ♪";
		mes "ハイ！　もうリセットされましたよ。";
		mes "ご利用ありがとうございました。";
		close;
	case 3:
		mes "[サンシイ]";
		mes "分かりました。";
		mes "あなたの";
		mes "ステータス＆スキル一括リセット権の";
		mes "有無をお調べ致します。";
		next;
		mes "[サンシイ]";
		mes strcharinfo(0) + " 様のリセット権は次の通りです。";
		mes "　";
		mes "ステータス＆スキル一括リセット権";
		if(checkquest(129700))
			mes "^FF0000あり^000000";
		else
			mes "なし";
		close;
	case 4:
		mes "[サンシイ]";
		mes "そうですか……分かりました。";
		mes "またの機会をお待ちしております。";
		close;
	}
}

//==========================================
// （旧）転職代行NPC
//------------------------------------------

function	script	jobchenge3rd_func	{
	function	job_name	{
		switch(getarg(0)) {
		case Job_Knight:		return "ロードナイト";
		case Job_Priest:		return "ハイプリースト";
		case Job_Wizard:		return "ハイウィザード";
		case Job_Blacksmith:	return "ホワイトスミス";
		case Job_Hunter:		return "スナイパー";
		case Job_Assassin:		return "アサシンクロス";
		case Job_Crusader:		return "パラディン";
		case Job_Monk:			return "チャンピオン";
		case Job_Sage:			return "プロフェッサー";
		case Job_Rogue:			return "チェイサー";
		case Job_Alchemist:		return "クリエイター";
		case Job_Bard:			return "クラウン";
		case Job_Dancer:		return "ジプシー";
		case Job_RuneKnight:	return "ルーンナイト";
		case Job_Warlock:		return "ウォーロック";
		case Job_Ranger:		return "レンジャー";
		case Job_ArchBishop:	return "アークビショップ";
		case Job_Mechanic:		return "メカニック";
		case Job_Guillotine:	return "ギロチンクロス";
		case Job_RoyalGuard:	return "ロイヤルガード";
		case Job_Sorcerer:		return "ソーサラー";
		case Job_Minstrel:		return "ミンストレル";
		case Job_Wanderer:		return "ワンダラー";
		case Job_Shura:			return "修羅";
		case Job_Genetic:		return "ジェネティック";
		case Job_ShadowChaser:	return "シャドウチェイサー";
		}
	}

	set '@job,getarg(0);
	set '@3rdName$, job_name('@job);
	if(Job == '@job) {
		mes "[転職代行係]";
		mes "おお、貴方は";
		mes '@3rdName$ +"ですね。";
		mes "もう転職は完了していますよ。";
		close;
	}
	if(Job != getarg(1) || Upper == UPPER_NORMAL ||
	  (Upper == UPPER_HIGH && BaseLevel < 90) ||
	  (Upper == UPPER_BABY && (BaseLevel < 99 || JobLevel < 50)) ) {
		mes "[転職代行係]";
		mes "こんにちは。";
		mes "貴方の周りに、";
		mes '@3rdName$ +"への";
		mes "転職を望む者はいませんか？";
		next;
		mes "[転職代行係]";
		mes "もしいましたら、";
		mes "私のところへ来るように";
		mes "伝えてください。";
		mes "今なら条件さえ満たしていれば";
		mes "すぐ転職できますよ。";
		close;
	}
	if(SkillPoint) {
		mes "‐スキルポイントが余っているため";
		mes "　進行できません‐";
		close;
	}
	mes "[転職代行係]";
	mes "こんにちは。";
	if(Upper == UPPER_HIGH)
		mes "貴方は"+ job_name(Job) +"ですね。";
	mes '@3rdName$ +"への転職を";
	mes "望みますか？";
	next;
	mes "[転職代行係]";
	mes "なお、"+ '@3rdName$ +"へ転職すると";
	mes "ステータスとスキルが全て";
	mes "リセットされます。";
	next;
	if(select("転職しない","^0000FF転職する^000000")==1) {
		mes "[転職代行係]";
		mes "わかりました。";
		mes "それもひとつの道でしょう。";
		close;
	}
	if(Weight || SkillPoint || checkriding() || checkcart() || checkfalcon() || sc_ison(SC_ALL_RIDING)) {
		mes "[転職代行係]";
		mes "あなたは準備しなければ";
		mes "ならないことがありますね。";
		mes "まずは、身を清める為に";
		mes "身のまわりのものを";
		mes "無にしてください。";
		next;
		mes "[転職代行係]";
		mes "アイテムやスキルポイントなど";
		mes "何も持たない";
		mes "状態でなければなりません。";
		mes "旅を共にした動物達やカート、";
		mes "騎乗生物なども";
		mes "持って行くことはできません。";
		next;
		mes "[転職代行係]";
		mes "それでは……用意ができましたら";
		mes "お越しください。";
		close;
	}
	if('@job == Job_RuneKnight) {
		mes "[転職代行係]";
		mes "転職する為の準備は万全のようですね。";
		mes "それでは、転職する前に、";
		mes "これからご紹介します装備のうち";
		mes "いずれか1つをお選びください。";
		mes "お選びになった装備が、";
		mes "転職の際に渡されます。";
		next;
		mes "[転職代行係]";
		mes "まず、装備の詳細について";
		mes "ご説明しますので、";
		mes "詳細が知りたい装備を";
		mes "お選び下さい。";
		while(1) {
			next;
			switch(select("エナジールーンガード[1]","魔力石の指輪[1]","ルーンプレート[1]","説明は大丈夫です")) {
			case 1:
				mes "[転職代行係]";
				mes "エナジールーンガード[1]について";
				mes "説明させていただきます。";
				next;
				mes "[装備詳細]";
				mes "豪華な青色の光の";
				mes "エナジールーンが";
				mes "ちりばめられている";
				mes "羽模様の盾。";
				mes "清く清明な気が溢れて";
				mes "自身と精神を刺激する。";
				next;
				mes "[装備詳細]";
				mes "系列 : 盾";
				mes "防御 : 70";
				mes "重量 : 0";
				mes "要求レベル : 99";
				mes "装備 : ルーンナイト専用";
				mes "特殊効果： MaxSP + 2%";
				next;
				mes "[転職代行係]";
				mes "他に詳細の知りたい";
				mes "装備はございますか？";
				continue;
			case 2:
				mes "[転職代行係]";
				mes "魔力石の指輪[1]について";
				mes "説明させていただきます。";
				next;
				mes "[装備詳細]";
				mes "不思議なルーンが";
				mes "刻まれている";
				mes "青色のリング。";
				mes "輝くルーンから";
				mes "神秘な活力が感じ取れる。";
				next;
				mes "[装備詳細]";
				mes "系列 : アクセサリー";
				mes "防御 : 0";
				mes "重量 : 0";
				mes "要求レベル : 90";
				mes "装備 : ルーンナイト専用";
				mes "特殊効果： Str + 2";
				next;
				mes "[転職代行係]";
				mes "他に詳細の知りたい";
				mes "装備はございますか？";
				continue;
			case 3:
				mes "[転職代行係]";
				mes "ルーンプレート[1]について";
				mes "説明させていただきます。";
				next;
				mes "[装備詳細]";
				mes "ルーンと宝石で飾られた";
				mes "プレートアーマー。";
				mes "見た目より軽いが、";
				mes "魔力により防御力が";
				mes "強化されている。";
				next;
				mes "[装備詳細]";
				mes "系列 : 鎧";
				mes "防御 : 95";
				mes "重量 : 0";
				mes "要求レベル : 99";
				mes "装備 : ルーンナイト専用";
				mes "特殊効果：精錬不可、破壊不可。";
				next;
				mes "[転職代行係]";
				mes "他に詳細の知りたい";
				mes "装備はございますか？";
				continue;
			case 4:
				mes "[転職代行係]";
				mes "それでは、貴方が欲しい";
				mes "装備をお選び下さい。";
				while(1) {
					next;
					switch(select("エナジールーンガード[1]","魔力石の指輪[1]","ルーンプレート[1]")) {
					case 1:
						set '@gain,2140;
						break;
					case 2:
						set '@gain,2794;
						break;
					case 3:
						set '@gain,15002;
						break;
					}
					next;
					mes "[転職代行係]";
					mes getitemname('@gain) +"[1]ですね。";
					mes "本当にこちらでよろしいですか？";
					next;
					if(select("はい","いいえ")==2) {
						mes "[転職代行係]";
						mes "それでは再度、";
						mes "欲しい装備を";
						mes "お選び下さい。";
						continue;
					}
					break;
				}
			}
			break;
		}
	}
	resetstatus;
	resetskill;
	setoption 0;
	jobchange '@job;
	switch(Job) {
	case Job_RuneKnight:
		setquest 201180;
		getitem 5746,1;	//ルーンサークレット
		getitem '@gain,1;	//選択装備
		break;
	case Job_ArchBishop:
		setquest 201195;
		getitem 5747,1;	//ミトラ
		break;
	case Job_Warlock:
		setquest 201185;
		getitem 5753,1;	//魔力石の帽子
		break;
	case Job_Mechanic:
		setquest 201205;
		if(Sex)
			getitem 5749,1;	//ドライバーバンド(male)
		else
			getitem 5760,1;	//ドライバーバンド(female)
		break;
	case Job_Ranger:
		setquest 201190;
		getitem 6124,1;	//狼の笛
		getitem 5748,1;	//スナイパーゴーグル
		break;
	case Job_Guillotine:
		setquest 201200;
		getitem 5755,1;	//沈黙の執行者
		getitem 12106,1;	//宝石箱
		break;
	case Job_RoyalGuard:
		setquest 201210;
		getitem 5757,1;	//シュミッツのヘルム
		break;
	case Job_Shura:
		setquest 201230;
		getitem 5754,1;	//ブレイジングソウル
		break;
	case Job_Sorcerer:
		setquest 201215;
		getitem 5756,1;	//風のささやき
		break;
	case Job_ShadowChaser:
		setquest 201235;
		getitem 6121,1;	//フェイスペイントブラシ
		getitem 6122,1;	//ペイントブラシ
		getitem 5750,1;	//シャドウクラウン
		break;
	case Job_Genetic:
		setquest 201240;
		getitem 5752,1;	//ミダスのささやき
		break;
	case Job_Minstrel:
		setquest 201220;
		getitem 5751,1;	//ミンストレルソングの帽子
		break;
	case Job_Wanderer:
		setquest 201225;
		getitem 5758,1;	//バレリーナの髪飾り
		break;
	}
	getitem 2795,1;	//熟していないリンゴの指輪
	if(Upper == UPPER_BABY) {
		for(set '@i,22954;'@i<=22969;set '@i,'@i+1) {
			if(countitem('@i))
				delitem '@i,1;
		}
		if(countitem(25018)) delitem 25018,1;
		if(countitem(25019)) delitem 25019,1;
		if(countitem(25020)) delitem 25020,1;
		if(getequipid(14) == 20307) unequip 14;
		if(countitem(20307)) delitem 20307,1;
	}
	mes "[転職代行係]";
	mes "さあ、これで貴方は";
	mes '@3rdName$ +"となりました。";
	mes "見た目も気持ちも一新ですね！";
	close;
}

//prt_in.gat,162,24,3	script	転職代行係#runeknight	888,{ callfunc "jobchenge3rd_func",Job_RuneKnight,Job_Knight; }
//morocc.gat,94,141,3	script	転職代行係#warlock	888,{ callfunc "jobchenge3rd_func",Job_Warlock,Job_Wizard; }
alberta.gat,223,111,5	script	転職代行係#ranger	888,{ callfunc "jobchenge3rd_func",Job_Ranger,Job_Hunter; }
//prt_church.gat,103,88,3	script	転職代行係#arch	888,{ callfunc "jobchenge3rd_func",Job_ArchBishop,Job_Priest; }
//yuno.gat,129,156,3	script	転職代行係#mechanic	888,{ callfunc "jobchenge3rd_func",Job_Mechanic,Job_Blacksmith; }
que_job01.gat,75,96,3	script	転職代行係#guillotine	888,{ callfunc "jobchenge3rd_func",Job_Guillotine,Job_Assassin; }
prt_castle.gat,48,161,3	script	転職代行係#roya	888,{ callfunc "jobchenge3rd_func",Job_RoyalGuard,Job_Crusader; }
gef_tower.gat,102,34,3	script	転職代行係#sorc	888,{ callfunc "jobchenge3rd_func",Job_Sorcerer,Job_Sage; }
alberta.gat,196,133,3	script	転職代行係#mins	888,{ callfunc "jobchenge3rd_func",Job_Minstrel,Job_Bard; }
xmas.gat,162,209,3	script	転職代行係#wand	888,{ callfunc "jobchenge3rd_func",Job_Wanderer,Job_Dancer; }
ve_in.gat,237,125,3	script	転職代行係#sura	888,{ callfunc "jobchenge3rd_func",Job_Shura,Job_Monk; }
alde_alche.gat,35,186,3	script	転職代行係#gene	888,{ callfunc "jobchenge3rd_func",Job_Genetic,Job_Alchemist; }
morocc.gat,156,70,3	script	転職代行係#shad	888,{ callfunc "jobchenge3rd_func",Job_ShadowChaser,Job_Rogue; }


//==========================================
// グリフォンレンタル
//------------------------------------------

prontera.gat,125,208,5	script	グリフォン管理兵	105,{
	if(Job != Job_RoyalGuard) {
		mes "[グリフォン管理兵]";
		mes "何の御用ですか？";
		mes "グリフォンは、ロイヤルガード様専用";
		mes "となっております。";
		close;
	}
	//未調査
	mes "[グリフォン管理兵]";
	mes "いらっしゃいませ。";
	mes "グリフォンをご利用ですか？";
	next;
	if(select("利用する","やめる")==2) {
		mes "[グリフォン管理兵]";
		mes "そうですか。では……";
		close;
	}
	if(checkriding()) {
		close;
	}
	if(getskilllv(63) < 1) {
		mes "[グリフォン管理兵]";
		mes "……まだグリフォンには";
		mes "乗れないようですね。";
		mes "スキル「ライディング」を";
		mes "覚えてからお越しください。";
		close;
	}
	setriding;
	close;
}


//==========================================
// トラップ専門家 - レンジャー
//------------------------------------------

-	shop	AlloyTrapShopper	-1,7940,12341

prt_in.gat,109,68,4		substore(AlloyTrapShopper)	トラップ専門家	66
mid_camp.gat,129,284,4	substore(AlloyTrapShopper)	トラップ専門家	66
payon.gat,123,109,4		substore(AlloyTrapShopper)	トラップ専門家	66
ra_in.gat,263,281,4		substore(AlloyTrapShopper)	トラップ専門家	66
lighthalzen.gat,337,240,4	substore(AlloyTrapShopper)	トラップ専門家	66


//==========================================
// 毒製造キット販売員 - ギロチンクロス
//------------------------------------------

-	script	3rdPoisonShopper	-1,{
	mes "[毒製造キット販売員]";
	mes "毒製造キットはいりませんか～？";
	mes "　";
	mes "毒製造キットは１つ";
	mes "5000zenyですよ～";
	mes "　";
	mes "買いますか～？";
	next;
	if(select("はい","いいえ")==2) {
		mes "[毒製造キット販売員]";
		mes "そうですか～";
		mes "わかりました～";
		mes "また来てくださいね～";
		close;
	}
	if(Zeny < 5000) {
		mes "[毒製造キット販売員]";
		mes "あの～";
		mes "お客さん、お金が足りませんよ～";
		mes "お金を増やして、またきて下さ～い。";
		close;
	}
	if(checkitemblank()==0) {
		mes "[毒製造キット販売員]";
		mes "あの～";
		mes "お客さん、所持している荷物が";
		mes "多いですね～";
		mes "これでは毒製造キットを";
		mes "渡せませんよ～";
		mes "身を軽くしてからまたきて下さ～い。";
		close;
	}
	if(checkweight(7931,1)==0) {
		mes "[毒製造キット販売員]";
		mes "あの～";
		mes "お客さん、所持している荷物が";
		mes "重すぎですよ～";
		mes "これでは毒製造キットを";
		mes "渡せませんよ～";
		mes "身を軽くしてからまたきて下さ～い。";
		close;
	}
	set Zeny,Zeny - 5000;
	getitem 7931,1;
	mes "[毒製造キット販売員]";
	mes "お買い上げ～";
	mes "ありがとうございま～す。";
	mes "またお越しくださ～い。";
	close;
}

morocc.gat,185,95,4	duplicate(3rdPoisonShopper)	毒製造キット販売員#moc	877
lhz_in02.gat,16,205,4	duplicate(3rdPoisonShopper)	毒製造キット販売員#lhz	877


//==========================================
// 媒体販売 - ミンストレル、ワンダラー
//------------------------------------------

comodo.gat,196,162,3	shop	カリブ#comodo	479,11513,6144


//==========================================
// ポイント商人 - レンジャー、ソーサラー
//------------------------------------------

gef_tower.gat,105,172,5	script	ポイント商人	700,{
	mes "[ポイント商人]";
	mes "こんにちは。";
	mes "ここでは鉱石をさらに砕いた";
	mes "触媒として使用する";
	mes "^FF0000各種ポイント^000000を販売しています。";
	mes "何か必要ですか？";
	next;
	switch(select("スカーレットポイント(火) - 200z","ライムグリーンポイント(地) - 200z","インディゴポイント(水) - 200z","イエローウィッシュポイント(風) - 200z","会話を終える")) {
	case 1:
		set '@itemid,6360;
		set '@element$,"火属性";
		break;
	case 2:
		set '@itemid,6363;
		set '@element$,"地属性";
		break;
	case 3:
		set '@itemid,6361;
		set '@element$,"水属性";
		break;
	case 4:
		set '@itemid,6362;
		set '@element$,"風属性";
		break;
	case 5:
		mes "[ポイント商人]";
		mes "またのご利用をお待ちしています。";
		close;
	}
	mes "[ポイント商人]";
	mes "^ff0000" +getitemname('@itemid)+ "^000000ですね。";
	mes "こちらは^0000ff" +'@element$+ "^000000のポイントです。";
	mes "何個購入しますか？";
	mes "同時に1000個まで購入できます。";
	mes "キャンセルするには、";
	mes "0を入力してください。";
	next;
	input '@num;
	if('@num == 0) {
		mes "[ポイント商人]";
		mes "キャンセルしました。";
		mes "またのご利用をお待ちしています。";
		close;
	}
	if('@num < 0 || '@num > 1000) {
		mes "[ポイント商人]";
		mes "正しい数を入力してください。";
		mes "一度に購入できるのは";
		mes "1000個までとなります。";
		close;
	}
	mes "[ポイント商人]";
	mes "^ff0000" +getitemname('@itemid)+ "^000000を";
	mes "^0000ff" +'@num+ "個^000000で";
	mes "よろしいですか？";
	next;
	if(select("はい","いいえ") == 2) {
		mes "[ポイント商人]";
		mes "キャンセルしました。";
		mes "またのご利用をお待ちしています。";
		close;
	}
	if(200*'@num > Zeny) {
		mes "[ポイント商人]";
		mes "お客様、すみませんが、";
		mes "所持金が不足しています。";
		close;
	}
	if(checkweight('@itemid,'@num) == 0) {
		mes "[ポイント商人]";
		mes "おや、荷物が一杯のようです。";
		mes "少し数を減らしてから、";
		mes "ご利用ください。";
		close;
	}
	set Zeny,Zeny-200*'@num;
	getitem '@itemid,'@num;
	mes "[ポイント商人]";
	mes "ご利用ありがとうございます。";
	close;
}


//==========================================
// 製造本販売員 - ジェネティック
//------------------------------------------

comodo.gat,106,213,5	shop	南国の果物商人	724,6258

alde_alche.gat,31,186,3	script	製造本販売員#alde	883,{
	mes "[製造本販売員]";
	mes "こんにちは！";
	mes "私はジェネティックの";
	mes "^0000FF特別な製造本^000000を販売しています！";
	next;
	mes "[製造本販売員]";
	mes "知ってました？";
	mes "ジェネティックは製造本を";
	mes "所持していないと、";
	mes "使えない製造スキルが";
	mes "あるんですよ。";
	next;
	mes "[製造本販売員]";
	mes "所持している製造本の";
	mes "^FF0000種類^000000が多ければ多いほど、";
	mes "製造できるアイテムの種類も";
	mes "増えるんですよ。";
	next;
	mes "[製造本販売員]";
	mes "いや～、この本内容が難しいので、";
	mes "売れなくて困ってたんですよ。";
	mes "1冊あれば、製造の材料はわかるので、";
	mes "充分なんですけど、";
	mes "何冊でも売りますよ！";
	mes "製造本を購入しますか？";
	next;
	if(select("はい","いいえ")==2) {
		mes "[製造本販売員]";
		mes "では、また来てください。";
		mes "いつでも、お待ちしてますよ！";
		close;
	}
	if(checkitemblank()==0) {
		mes "[製造本販売員]";
		mes "持っている荷物の数が";
		mes "多すぎますね。";
		mes "これでは本を";
		mes "渡せませんよ。";
		mes "荷物を整理してから";
		mes "また来てください。";
		close;
	}
	if(Weight*100/MaxWeight >= 90) {
		mes "[製造本販売員]";
		mes "持っている荷物の重量が";
		mes "重すぎますね。";
		mes "これでは本を";
		mes "渡せませんよ。";
		mes "荷物を整理してから";
		mes "また来てください。";
		close;
	}
	mes "[製造本販売員]";
	mes "ほ、本当ですか～！";
	mes "ありがとうございます！";
	mes "それでは、製造本のリストを";
	mes "お見せしますね！";
	mes "できれば、いっぱい";
	mes "買っていってください！";
	while(1){
		next;
		switch(select(
			"[リンゴ爆弾製造本] 100,000 zeny",
			"[パイナップル爆弾製造本] 100,000 zeny",
			"[ココナッツ爆弾製造本] 100,000 zeny",
			"[メロン爆弾製造本] 100,000 zeny",
			"[バナナ爆弾製造本]100,000 zeny",
			"[遺伝子組み換え植物栽培法]100,000 zeny",
			"[上級ポーション製造マニュアル] 100,000 zeny",
			"[ミックスクッキング料理本] 100,000 zeny",
			"[スタミナ増進研究書] 100,000 zeny",
			"[活力ドリンク製造法]100,000 zeny",
			"購入を終了する。")) {
		case 1:		//リンゴ爆弾製造本
			set '@gain,6279;
			break;
		case 2:		//パイナップル爆弾製造本
			set '@gain,6280;
			break;
		case 3:		//ココナッツ爆弾製造本
			set '@gain,6281;
			break;
		case 4:		//メロン爆弾製造本
			set '@gain,6282;
			break;
		case 5:		//バナナ爆弾製造本
			set '@gain,6283;
			break;
		case 6:		//遺伝子組み換え植物栽培法
			set '@gain,6284;
			break;
		case 7:		//上級ポーション製造マニュアル
			set '@gain,6285;
			break;
		case 8:		//ミックスクッキング料理本
			set '@gain,11022;
			break;
		case 9:		//スタミナ増進研究書
			set '@gain,11023;
			break;
		case 10:	//活力ドリンク製造法
			set '@gain,11024;
			break;
		case 11:
			mes "[製造本販売員]";
			mes "そうですか。";
			mes "また来てくださいね！";
			close;
		}
		mes "[製造本販売員]";
		mes "^0000FF[" +getitemname('@gain)+ "]^000000は";
		mes "100,000 zenyです。";
		mes "何冊購入します？";
		mes "1冊でも充分ですけど、";
		mes "100冊とか買ってもらっても";
		mes "いいですよ！";
		next;
		input '@num;
		if('@num == 0) {
			mes "[製造本販売員]";
			mes "他の本はいかがですか。";
			continue;
		}
		if('@num < 1 || '@num > 100) {
			mes "[製造本販売員]";
			mes "う～ん、残念！";
			mes "1度に購入できるのは";
			mes "100冊までなんです。";
			continue;
		}
		mes "[製造本販売員]";
		mes "^0000FF[" +getitemname('@gain)+ "]^000000を";
		mes '@num+ " 冊購入ですね！";
		mes "　";
		mes "よろしいですか？";
		next;
		if(select("はい","いいえ")==2) {
			mes "[製造本販売員]";
			mes "そ、そうですか……";
			mes "製造本はいっぱいありますから、";
			mes "遠慮することはないですよ。";
			continue;
		}
		if(Zeny < 100000 * '@num){
			mes "[製造本販売員]";
			mes "あ～、ちょっとお金が";
			mes "足りないみたいですね。";
			mes "お金を用意して来てください。";
			close;
		}
		mes "[製造本販売員]";
		mes "ありがとうございます！";
		mes "他の本はいりませんか？";
		set Zeny,Zeny - 100000 * '@num;
		getitem '@gain,'@num;
		continue;
	}
}


//==========================================
// 影工房 - シャドウチェイサー
//------------------------------------------

-	shop	PaintingShopper	-1,6123,6120

s_atelier.gat,17,110,1	substore(PaintingShopper)	販売員#sc_prt	67
s_atelier.gat,137,60,3	substore(PaintingShopper)	販売員#sc_ra	70
s_atelier.gat,114,117,1	substore(PaintingShopper)	販売員#sc_yuno	92
s_atelier.gat,15,65,5	substore(PaintingShopper)	販売員#sc_lgt	89
