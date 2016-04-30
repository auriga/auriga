// 委託販売(プロの噴水上に４体ほど設置）
//
// クローンの設置を容易にするために、getelementofarray + getarg という
// 複雑な処理を多用しているので、読んでる途中で混乱してくるかもしれません。
// 今のAthenaのスクリプトでは、これくらい高性能なＮＰＣも作れるので、
// 「委託販売が作れるのなら他のＮＰＣも作ってみたい！」と思う人が
// 出てきてほしいなぁ、という希望を持ちながら公開することにしました。
// 何か良いアイディアがあれば、是非とも挑戦してみてください。
// 
// ※copyarrayにバグがあったので、mod1116より下のバージョンでは、
//   正しく動きません。
//   さらに、deletearrayにもバグがあったので、mod1127より下のバージョンでは、
//   アイテムがロストするバグが発生します。
// 
// v1 05/02/05 : 初公開
// v2 05/02/12 : アイテムがソートして配置されないバグを修正
// v3 05/02/13 : deletearray のバグを明記、typo２箇所(動作には影響なし)修正

prontera.gat,148,214,1	script	委託販売員1	112,{
	callfunc
		"seller",
		$s1_item_count,		// 0 アイテムリストの個数
		$s1_item_itemid,	// 1 アイテムリスト : アイテムID
		$s1_item_amount,	// 2 アイテムリスト : 販売個数
		$s1_item_zeny,		// 3 アイテムリスト : 販売金額
		$s1_item_account,	// 4 アイテムリスト : 出品者ID
		$s1_account_id,		// 5 出品者リスト : ID
		$s1_account_zeny;	// 6 出品者リスト : 総計Zeny
}

prontera.gat,153,214,1	script	委託販売員2	112,{
	callfunc
		"seller",
		$s2_item_count,$s2_item_itemid,$s2_item_amount,$s2_item_zeny,$s2_item_account,
		$s2_account_id,$s2_account_zeny;
}

prontera.gat,158,214,1	script	委託販売員3	112,{
	callfunc
		"seller",
		$s3_item_count,$s3_item_itemid,$s3_item_amount,$s3_item_zeny,$s3_item_account,
		$s3_account_id,$s3_account_zeny;
}

prontera.gat,163,214,1	script	委託販売員4	112,{
	callfunc
		"seller",
		$s4_item_count,$s4_item_itemid,$s4_item_amount,$s4_item_zeny,$s4_item_account,
		$s4_account_id,$s4_account_zeny;
}

function	script	seller	{
	function seller_clean;
	function seller_prevpage;
	function seller_nextpage;
	function seller_select;
	function seller_select_sub;
	function seller_pc_addzeny;
	function seller_pc_find;

	mes "[カプラ委託販売員]";
	mes "私達（株）カプラサービスでは";
	mes "取引市場を活性化するために";
	mes "皆様の要望にお答えして";
	mes "委託販売サービスを始めました。";
	next;
	while(1) {
		set @sel, select("委託販売とは？","購入する","出品する","販売代金を受け取る","やめる");
		if(@sel == 5) {
			// やめる
			break;
		}
		switch(@sel) {
		case 1: // 委託販売とは？
			mes "[カプラ委託販売員]";
			mes "委託販売とはお客様より商品を";
			mes "受け取り、指定価格で代売する";
			mes "新サービスです。";
			next;
			mes "[カプラ委託販売員]";
			mes "代金は後日私達委託販売員より";
			mes "受け取ることができます。";
			next;
			mes "[カプラ委託販売員]";
			mes "注意する点として、出品する場合";
			mes "10%の手数料を取らせて戴きます。";
			mes "又、一度に販売できるアイテムは";
			mes "100種類となっています。";
			next;
			break;
		case 2: // 購入する
			while(1) {
				if(getarg(0) == 0) {
					mes "[カプラ委託販売員]";
					mes "販売中のアイテムはありません。";
					next;
					break;
				}
				mes "[カプラ委託販売員]";
				mes "購入するアイテムを選んでください。";
				next;
				// アイテムの選択
				set @sel, seller_select(getarg(0),1,getarg(1),getarg(2),getarg(3));
				if(@sel == -1) {
					// キャンセル
					break;
				}
				// 個数の入力
				if(getelementofarray(getarg(2),@sel) == 1) {
					// １つしか無いものは個数を聞かない
					set @amount, 1;
				} else {
					mes "[カプラ委託販売員]";
					mes "購入する個数を入力してください。";
					next;
					input @amount;
					if( (@amount > getelementofarray(getarg(2),@sel)) || (@amount <= 0)) {
						mes "[カプラ委託販売員]";
						mes "在庫が不足しています。";
						next;
						break;
					}
				}
				// 各種チェック
				set @zeny , getelementofarray(getarg(3),@sel) * @amount;
				if(@zeny > Zeny) {
					mes "[カプラ委託販売員]";
					mes "Zeny が足りません。";
					next;
					break;
				} else if(checkweight(getelementofarray(getarg(1),@sel),@amount) == 0) {
					mes "[カプラ委託販売員]";
					mes "質量オーバーです。";
					next;
					break;
				}
				// 最終確認
				mes "[カプラ委託販売員]";
				mes getitemname(getelementofarray(getarg(1),@sel)) + " " + @amount + "個を";
				mes getelementofarray(getarg(3),@sel) + "Zeny で購入します。";
				mes "よろしいですか？";
				set @item_id,     getelementofarray(getarg(1),@sel);
				set @item_zeny,   getelementofarray(getarg(3),@sel);
				set @item_amount, getelementofarray(getarg(2),@sel);
				next;
				if(
					(select("はい","いいえ") != 1) ||
					(@zeny > Zeny) ||
					(checkweight(getelementofarray(getarg(1),@sel),@amount) == 0)
				) {
					// ここでのチェックを忘れると不正につながる恐れがある
					break;
				} else if(
					(@item_id     != getelementofarray(getarg(1),@sel)) ||
					(@item_zeny   != getelementofarray(getarg(3),@sel)) ||
					(@item_amount != getelementofarray(getarg(2),@sel))
				) {
					mes "[カプラ委託販売員]";
					mes "取引が同時に起こったため、";
					mes "先ほどのアイテムの販売を";
					mes "中断させて頂きました。";
					mes "再度購入をしてください。";
					break;
				}
				set Zeny , Zeny - @zeny;
				getitem getelementofarray(getarg(1),@sel),@amount;
				set @dummy , seller_pc_addzeny(getarg(5),getelementofarray(getarg(4),@sel),getarg(6),@zeny);
				if(@amount == getelementofarray(getarg(2),@sel)) {
					// 全部購入された -> 配列を削除
					deletearray getelementofarray(getarg(1),@sel),1;
					deletearray getelementofarray(getarg(2),@sel),1;
					deletearray getelementofarray(getarg(3),@sel),1;
					deletearray getelementofarray(getarg(4),@sel),1;
					set getarg(0) , getarg(0) - 1;
				} else {
					// 一部のみ購入 -> 個数を減らすだけ
					set getelementofarray(getarg(2),@sel), getelementofarray(getarg(2),@sel) - @amount;
				}
			}
			break;
		case 3: // 出品する
			while(1) {
				getinventorylist;
				if(@inventorylist_count == 0) {
					mes "[カプラ委託販売員]";
					mes "アイテムがありません。";
					next;
					break;
				} else if(@inventorylist_count > 100) {
					// 表示するのは先頭１００個までのアイテム
					set @inventorylist_count, 100;
				}
				if(getarg(0) >= 100) {
					mes "[カプラ委託販売員]";
					mes "現在最大まで出品されています。";
					next;
					break;
				}
				mes "[カプラ委託販売員]";
				mes "出品したいアイテムを選んでください。";
				next;
				// アイテムを選択させる
				set @sel, seller_select(@inventorylist_count,0,-1,-1,-1);
				if(@sel == -1) {
					// キャンセル
					break;
				} else if(@inventorylist_equip[@sel]) {
					// 装備フラグ
					mes "[カプラ委託販売員]";
					mes "装備している商品は出品できません。";
					next;
					break;
				} else if(!@inventorylist_identify[@sel]) {
					// 鑑定済みフラグ
					mes "[カプラ委託販売員]";
					mes "未鑑定の商品は出品できません。";
					next;
					break;
				} else if(@inventorylist_attribute[@sel]) {
					// 破損チェック
					mes "[カプラ委託販売員]";
					mes "破損した商品は出品できません。";
					next;
					break;
				} else if(
					@inventorylist_card1[@sel] || @inventorylist_card2[@sel] ||
					@inventorylist_card3[@sel] || @inventorylist_card4[@sel]
				) {
					// 製造チェック
					mes "[カプラ委託販売員]";
					mes "製造品、カードを差した商品は出品はできません。";
					next;
					break;
				} else if(@inventorylist_refine[@sel]) {
					// 精錬チェック
					mes "[カプラ委託販売員]";
					mes "精錬した商品は出品はできません。";
					next;
					break;
				} else if((@inventorylist_id[@sel] == 2634) || (@inventorylist_id[@sel] == 2635)) { 
					// 結婚指輪チェック
					mes "[カプラ委託販売員]";
					mes "結婚指輪は出品はできません。";
					next;
					break;
				}
				// 販売個数の入力
				if(@inventorylist_amount[@sel] == 1) {
					// 個数が１つしか無い時は聞かない
					set @amount, 1;
				} else {
					mes "[カプラ委託販売員]";
					mes "出品する個数を入力してください。";
					next;
					input @amount;
					if( (@amount > @inventorylist_amount[@sel]) || (@amount <= 0)) {
						mes "[カプラ委託販売員]";
						mes "所持個数を超えています。";
						next;
						break;
					}
				}
				mes "[カプラ委託販売員]";
				mes "出品する価格を入力してください。";
				next;
				input @money;
				if( @money <= 0) {
					mes "[カプラ委託販売員]";
					mes "0Zenyでの販売は出来ません。";
					next;
					break;
				}
				// 最終確認
				mes "[カプラ委託販売員]";
				mes getitemname(@inventorylist_id[@sel]) + " " + @amount + "個を";
				mes @money + "Zeny で出品します。";
				mes "よろしいですか？";
				next;
				if(
					(select("はい","いいえ") != 1) ||
					(countitem(@inventorylist_id[@sel]) < @amount) ||
					(getarg(0) >= 100)) {
					// ここでのチェックを忘れると不正につながる恐れがある
					break;
				}
				// 出品者リストに空きがあるか確かめる
				if(seller_pc_addzeny(getarg(5),getcharid(3),getarg(6),0) == 0) {
					mes "[カプラ委託販売員]";
					mes "申し訳ありませんが";
					mes "出品者リストが一杯です。";
					mes "他の委託販売員に尋ねるか";
					mes "日を改めてご利用ください。";
					next;
					break;
				}
				// 出品開始
				
				// アイテムIDごとにソートする
				for(set @pos , 0; @pos < getarg(0) ; set @pos, @pos + 1) {
					if(getelementofarray(getarg(1),@pos) > @inventorylist_id[@sel]) {
						break;
					}
				}
				if(@pos != getarg(0)) {
					copyarray getelementofarray(getarg(1),@pos+1),getelementofarray(getarg(1),@pos),getarg(0) - @pos;
					copyarray getelementofarray(getarg(2),@pos+1),getelementofarray(getarg(2),@pos),getarg(0) - @pos;
					copyarray getelementofarray(getarg(3),@pos+1),getelementofarray(getarg(3),@pos),getarg(0) - @pos;
					copyarray getelementofarray(getarg(4),@pos+1),getelementofarray(getarg(4),@pos),getarg(0) - @pos;
				}
				set getelementofarray(getarg(1),@pos) , @inventorylist_id[@sel];
				set getelementofarray(getarg(2),@pos) , @amount;
				set getelementofarray(getarg(3),@pos) , @money;
				set getelementofarray(getarg(4),@pos) , getcharid(3);
				set getarg(0) , getarg(0) + 1;
				delitem @inventorylist_id[@sel], @amount;
				mes "[カプラ委託販売員]";
				mes "出品できました。";
				next;
			};
			seller_clean;
			break;
		case 4: // 販売代金を受け取る
			//debug
			//mes "debug";
			//for(set @i , 0; @i < 100 ; set @i, @i + 1) {
			//	if(getelementofarray(getarg(5),@i)) {
			//		mes getelementofarray(getarg(5),@i) + " : " + getelementofarray(getarg(6),@i);
			//	}
			//}
			//next;
			set @pos, seller_pc_find(getarg(5),getcharid(3));
			if(@pos == -1) {
				mes "[カプラ委託販売員]";
				mes "預かっているZenyはありません。";
				next;
			} else if(getelementofarray(getarg(6),@pos) == 0) {
				mes "[カプラ委託販売員]";
				mes "預かっているZenyはありません。";
				next;
			} else {
				set @zeny , getelementofarray(getarg(6),@pos);
				mes "[カプラ委託販売員]";
				mes @zeny + "Zeny の売り上げの内、";
				mes "10%の手数料を頂いた残り";
				set @zeny, @zeny - @zeny / 10;
				mes @zeny + "Zeny の返金になります。";
				set Zeny, Zeny + @zeny;
				set getelementofarray(getarg(6),@pos) , 0;
				// 商品一覧にリストが無ければ、出品者リストから消去
				for(set @i , 0; @i < getarg(0) ; set @i,@i + 1) {
					if(getelementofarray(getarg(4),@i) == getcharid(3)) {
						break;
					}
				}
				if(@i == getarg(0)) {
					deletearray getelementofarray(getarg(5),@pos),1;
					deletearray getelementofarray(getarg(6),@pos),1;
				}
				next;
			}
			break;
		}
	}
	mes "[カプラ委託販売員]";
	mes "我々カプラサービスは、より完璧な";
	mes "サービスと管理業務を目指し";
	mes "お客様が安心してご利用いただけるよう";
	mes "いつも最善を尽くしています。";
	mes "（株）カプラサービスをご利用いただき";
	mes "ありがとうございました。";
	close;

	// seller_pc_addzeny(account_id , target , account_zeny , zeny)
	//     出品者リストの指定するIDにzenyZを加算する
	//
	//     account_id   : 出品者ID
	//     target       : 検索対象のID
	//     account_zeny : 出品者IDの所持Zeny
	//     zeny         : 加算するZeny
	function seller_pc_addzeny {
		set @__pos , seller_pc_find(getarg(0),getarg(1));
		if(@__pos != -1) {
			// 既に登録されていれば加算してtrue を返す
			set getelementofarray(getarg(2), @__pos) , getelementofarray(getarg(2), @__pos) + getarg(3);
			// 1Gz 制限
			if(getelementofarray(getarg(2), @__pos) > 1000*1000*1000) {
				set getelementofarray(getarg(2), @__pos) , 1000*1000*1000;
			}
			return 1;
		} else {
			// 登録されていなければ空きを探す
			for(set @__i , 0; @__i < 100 ; set @__i, @__i + 1) {
				if(getelementofarray(getarg(0), @__i) == 0) {
					// 空きを見つけたので追加
					set getelementofarray(getarg(0), @__i) , getarg(1);
					set getelementofarray(getarg(2), @__i) , getarg(3);
					return 1;
				}
			}
		}
		return 0;
	}

	// seller_pc_find( account_id , target)
	//     出品者リストから指定したIDを探し出す
	//     見つからなければ -1 を返す
	function seller_pc_find {
		for(set @__i , 0 ; @__i < 100 ; set @__i, @__i + 1) {
			if(getelementofarray(getarg(0), @__i) == getarg(1)) {
				return @__i;
			}
		}
		return -1;
	}

	// seller_select(limit , array , data1 , data2 , data3)
	//     array (要素数limit) の中からプレイヤーに１つを選択させる
	//     戻り値 -1 : キャンセル それ以外 : 選択された場所
	//
	//     data1, data2 , data3 はseller_select_sub にそのまま渡される
	function seller_select {
		set @__base,0;
		while(1) {
			set @__sel , select(
				"やっぱりやめる",
				seller_select_sub(getarg(0),@__base + 0,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_select_sub(getarg(0),@__base + 1,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_select_sub(getarg(0),@__base + 2,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_select_sub(getarg(0),@__base + 3,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_select_sub(getarg(0),@__base + 4,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_select_sub(getarg(0),@__base + 5,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_select_sub(getarg(0),@__base + 6,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_select_sub(getarg(0),@__base + 7,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_select_sub(getarg(0),@__base + 8,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_select_sub(getarg(0),@__base + 9,getarg(1),getarg(2),getarg(3),getarg(4)),
				seller_prevpage(@__base > 0),
				seller_nextpage(@__base + 10 < getarg(0))
			);
			if(@__sel == 1) {
				// やっぱりやめる
				return -1;
			} else if( (@__base + @__sel - 2 < getarg(0)) && (@__sel != 12) && (@__sel != 13) ) {
				set @index , @__base + @__sel - 2;
				return @index;
			} else if( (@__base + @__sel - 2 == getarg(0)) || (@__sel == 12)) {
				if(@__base > 0) {
					set @__base, @__base - 10;
				} else {
					set @__base, @__base + 10;
				}
			} else {
				// prev, next が表示されている
				set @__base, @__base + 10;
			}
		}
	}

	//                    0       1       2      3       4       5
	// seller_select_sub( limit , index , type , data1 , data2 , data3)
	function seller_select_sub {
		if(getarg(0) > getarg(1)) {
			switch(getarg(2)){
			case 0:
				if(!@inventorylist_identify[getarg(1)]) {
					return "????(未鑑定)";
				} else {
					return getitemname(@inventorylist_id[getarg(1)]) + " " + @inventorylist_amount[getarg(1)] + "個";
				}
				break;
			case 1:
				return
					getitemname(getelementofarray(getarg(3),getarg(1))) + " " + 
					getelementofarray(getarg(4),getarg(1)) + "個" + 
					getelementofarray(getarg(5),getarg(1)) + "Zeny";
				break;
			default:
				return getarg(1);
				break;
			}
		} else {
			return ;
		}
	}

	// 無駄変数を消去する
	function seller_clean {
		cleararray @inventorylist_id        , 0 , @inventorylist_count;
		cleararray @inventorylist_amount    , 0 , @inventorylist_count;
		cleararray @inventorylist_equip     , 0 , @inventorylist_count;
		cleararray @inventorylist_refine    , 0 , @inventorylist_count;
		cleararray @inventorylist_identify  , 0 , @inventorylist_count;
		cleararray @inventorylist_attribute , 0 , @inventorylist_count;
		cleararray @inventorylist_card1     , 0 , @inventorylist_count;
		cleararray @inventorylist_card2     , 0 , @inventorylist_count;
		cleararray @inventorylist_card3     , 0 , @inventorylist_count;
		cleararray @inventorylist_card4     , 0 , @inventorylist_count;
		set @inventorylist_count, 0;
	}

	function seller_prevpage {
		if(getarg(0)) {
			return "←前へ";
		} else {
			return ;
		}
	}
	function seller_nextpage {
		if(getarg(0)) {
			return "→次へ";
		} else {
			return ;
		}
	}
}
