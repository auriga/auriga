//==============================================================================
// Ragnarok Online Global Functions
//==============================================================================

//==============================================================================
// アイテム買取・交換用ファンクション
// 　プレイヤーの所持品およびZenyを調べて、目的アイテムの取得可能最大数を返す
//　（比較対象が3つ以上ある場合に利用すること）
//	callfunc "MathMax",ItemID-Array,Amount-Array,Zeny;
//
// ■ 引数の詳細
//	ItemID-Array 	-> 必要アイテムIDを格納した配列
//	Amount-Array 	-> 必要アイテム個数を格納した配列
//	Zeny		-> 必要Zeny（配列ではない）、判定しない場合は0を入れる
//
// ■ 使用例
//	setarray '@itemid,512,602,1010;
//	setarray '@amount,3,1,5;
//	callfunc "MathMax",'@itemid,'@amount,300;
//
//		-> りんご3個、蝶の羽1個、ブラコン5個、300zで目的アイテム1個取得
//------------------------------------------------------------------------------

function	script	MathMax	{
	set '@size,getarraysize(getarg(0));
	//'@max配列に各アイテムにおける最大数を入れる
	for(set '@i,0; '@i<'@size; set '@i,'@i+1) {
		set '@max['@i],countitem(getelementofarray(getarg(0),'@i)) / getelementofarray(getarg(1),'@i);
	}
	if(getarg(2))
		set '@max['@i],Zeny / getarg(2);	//末尾にZenyによる最大数を入れる
	else
		set '@size,'@size-1;			//Zeny判定しないときはサイズを1つ減らす
	for(set '@i,0; '@i<'@size; set '@i,'@i+1) {
		if('@max[0] > '@max[1])			//要素0と1の値を比較し、大きい方をdeleteして詰める
			deletearray '@max[0],1;
		else
			deletearray '@max[1],1;
	}
	return '@max;	//最後に残ったものが取得可能最大数
}
