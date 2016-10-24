/*=========================================================================
 * 汎用文字列処理ユーザー定義関数スクリプトライブラリ
 *				created by Rayce (rewritten Auriga068)
 *
 * ■ substr関数を利用することで文字列処理用のライブラリ関数を作成する
 *    ことができます。
 *    本来ならば使いたい関数をscript.cに直接追加するところですが
 *    全てのライブラリ関数を追加していくのはソースコードに無駄が生じます
 *    （しかも文字列処理を行わない人ならば全く必要ない）。
 *    substr関数はPerlライクな仕様になっているため、任意の文字列を柔軟に
 *    取り出すことが可能です。
 *    getstrlen関数と組み合わせることでかなりの範囲の文字列処理が実現できます。
 *    ここでは頻繁に使いそうなfunctionの例をライブラリとして用意しておきます。
 *
 * ■ C言語とは違いポインタの概念はありませんので、文字列検索系の
 *    関数では何番目に一致したかを返り値とします。
 *-------------------------------------------------------------------------
 */

//===============================================
// 左側空白除去
//	callfunc("StrTrim","<string>")
//-----------------------------------------------
function	script	StrTrim	{
	set '@dup$,getarg(0);
	while(1) {	// 前方検索
		set '@buf$,substr('@dup$,'@i,1);
		if('@buf$ == "" || '@buf$ != " ")
			break;
		set '@i,'@i+1;
	}
	return substr('@dup$,'@i);
}

//===============================================
// 右側空白除去
//	callfunc("StrRTrim","<string>")
//-----------------------------------------------
function	script	StrRTrim	{
	set '@dup$,getarg(0);
	while(1) {	// 後方検索
		set '@i,'@i-1;
		set '@buf$,substr('@dup$,'@i,1);
		if('@buf$ == "" || '@buf$ != " ")
			break;
	}
	return ('@i == -1)? substr('@dup$,0): substr('@dup$,0,'@i+1);
}

//===============================================
// 指定文字列が最も先頭に出現する位置を返す
//	callfunc("StrIndex","<str1>","<str2>")
//-----------------------------------------------
function	script	StrIndex	{
	set '@src$,getarg(0);
	set '@dst$,getarg(1);
	set '@len,getstrlen('@dst$);
	set '@max,getstrlen('@src$) - '@len;

	for(set '@i,0; '@i <= '@max; set '@i,'@i+1) {
		if( substr('@src$,'@i,'@len) == '@dst$ )
			return '@i;
	}
	return -1;
}

//===============================================
// 指定文字列が最も末尾に出現する位置を返す
//	callfunc("StrRIndex","<str1>","<str2>")
//-----------------------------------------------
function	script	StrRIndex	{
	set '@src$,getarg(0);
	set '@dst$,getarg(1);
	set '@len,getstrlen('@dst$);
	set '@max,getstrlen('@src$) - '@len;

	for(set '@i,'@max; '@i >= 0; set '@i,'@i-1) {
		if( substr('@src$,'@i,'@len) == '@dst$ )
			return '@i;
	}
	return -1;
}

//===============================================
// 指定文字列のいずれかの文字を探索
// 動作が保証されるのは１バイト文字のみ
//	callfunc("StrCSpn","<str1>","<str2>")
//-----------------------------------------------
function	script	StrCSpn	{
	set '@src$,getarg(0);
	set '@dst$,getarg(1);
	set '@max,getstrlen('@src$);
	set '@len,getstrlen('@dst$);

	for(set '@i,0; '@i < '@max; set '@i,'@i+1) {		// <str1>の走査
		for(set '@j,0; '@j < '@len; set '@j,'@j+1) {	// <str2>の走査
			if( substr('@src$,'@i,1) == substr('@dst$,'@j,1) )
				return '@i;
		}
	}
	return -1;
}

//===============================================
// 指定文字列のいずれかの文字列を探索
// ２バイト単位で検索する
//	callfunc("StrWCSpn","<str1>","<str2>")
//-----------------------------------------------
function	script	StrWCSpn	{
	set '@src$,getarg(0);
	set '@dst$,getarg(1);
	set '@max,getstrlen('@src$);
	set '@len,getstrlen('@dst$);

	for(set '@i,0; '@i < '@max; set '@i,'@i+2) {		// <str1>の走査
		for(set '@j,0; '@j < '@len; set '@j,'@j+2) {	// <str2>の走査
			if( substr('@src$,'@i,2) == substr('@dst$,'@j,2) )
				return '@i;
		}
	}
	return -1;
}

//===============================================
// <n>番目を１バイト削る
//	callfunc("StrDelete","<string>",<n>)
//-----------------------------------------------
function	script	StrDelete	{
	set '@n,getarg(1);
	if('@n < 0)
		return "";

	set '@buf$,getarg(0);
	return substr('@buf$,0,'@n) + substr('@buf$,'@n+1);
}

//===============================================
// <n>番目以降の文字列を左に<len>バイトずらす
//	callfunc("StrShift","<string>",<n>,<len>)
//-----------------------------------------------
function	script	StrShift	{
	set '@buf$,getarg(0);
	set '@n,getarg(1);
	set '@len,getarg(2);
	if('@n < 0 || '@len < 0 || '@n > getstrlen('@buf$))
		return "";

	if('@len == 0)		// ずらせないので何もしない
		return '@buf$;

	if('@len > '@n)		// 指定位置よりもshift値が大きいならshift値を位置にする
		set '@n,'@len;

	return substr('@buf$,0,'@n - '@len) + substr('@buf$,'@n);
}

//===============================================
// <n>番目以降の文字列を右にずらして
// 指定文字列を挿入する
//	callfunc("StrInsert","<str1>",<n>,"<str2>")
//-----------------------------------------------
function	script	StrInsert	{
	set '@n,getarg(1);
	if('@n < 0)
		return "";

	set '@buf$,getarg(0);
	return substr('@buf$,0,'@n) + getarg(2) + substr('@buf$,'@n);
}

//===============================================
// <str1>に含まれる<str2>を<str3>に置換
//	callfunc("StrReplace","<str1>","<str2>","<str3>")
//-----------------------------------------------
function	script	StrReplace	{
	set '@buf$,getarg(0);
	set '@n,callfunc("StrIndex",'@buf$,getarg(1));
	if('@n < 0)
		return '@buf$;	// 何もしない

	return substr('@buf$,0,'@n) + getarg(2) + substr('@buf$,'@n + getstrlen(getarg(1)));
}

//===============================================
// 先頭から順に<str1>に含まれる<str2>を
// <str3>に全部置換する
//	callfunc("StrAReplace","<str1>","<str2>","<str3>")
//-----------------------------------------------
function	script	StrAReplace	{
	// StrIndexを展開して利用する
	set '@src$,getarg(0);
	set '@dst$,getarg(1);
	set '@len,getstrlen('@dst$);
	set '@max,getstrlen('@src$) - '@len;

	for(set '@i,0; '@i <= '@max; set '@i,'@i+1) {
		if( substr('@src$,'@i,'@len) == '@dst$ ) {
			set '@ret$,'@ret$ + substr('@src$,'@pos,'@i - '@pos) + getarg(2);
			set '@pos,'@i + '@len;	// 次の検索開始位置を保存
			set '@i,'@pos-1;	// 次の検索位置まで飛ばす
		}
	}
	return '@ret$ + substr('@src$,'@pos);	// 残りを末尾まで繋いで終了
}

//===============================================
// 文字列の並びを逆にする
// 動作が保証されるのは１バイト文字のみ
//	callfunc("StrReverse","<string>")
//-----------------------------------------------
function	script	StrReverse	{
	set '@buf$,getarg(0);
	set '@len,getstrlen('@buf$);

	for(set '@i,'@len-1; '@i >= 0; set '@i,'@i-1) {
		set '@ret$,'@ret$ + substr('@buf$,'@i,1);
	}
	return '@ret$;
}

//===============================================
// 文字列の並びを逆にする
// ２バイト単位で並び替える
//	callfunc("StrWReverse","<string>")
//-----------------------------------------------
function	script	StrWReverse	{
	set '@buf$,getarg(0);
	set '@len,getstrlen('@buf$);

	for(set '@i,'@len-2; '@i >= 0; set '@i,'@i-2) {
		set '@ret$,'@ret$ + substr('@buf$,'@i,2);
	}
	if('@i != 0)	// 文字列長が奇数のときは余った先頭1バイトを足す
		set '@ret$,'@ret$ + substr('@buf$,0,1);
	return '@ret$;
}

//===============================================
// 文字列の並びをシャッフルする
// 動作が保証されるのは１バイト文字のみ
//	callfunc("StrShuffle","<string>")
//-----------------------------------------------
function	script	StrShuffle	{
	set '@dup$,getarg(0);
	set '@len,getstrlen('@dup$);

	for(set '@i,'@len-1; '@i >= 0; set '@i,'@i-1) {
		if('@i == 0) {
			set '@ret$,'@ret$ + '@dup$;			// 最後は乱数使わずそのまま結合
		} else {
			set '@rand,rand('@i);
			set '@ret$,'@ret$ + substr('@dup$,'@rand,1);
			set '@dup$,callfunc("StrDelete",'@dup$,'@rand);	// 選んだ文字は削る
		}
	}
	return '@ret$;
}

//===============================================
// <n>番目から１バイトずつ分解して配列に格納
// ただし配列上限の128byteまで
//	callfunc("StrArray","<string>",<n>,<variable>)
//-----------------------------------------------
function	script	StrArray	{
	set '@buf$,getarg(0);
	set '@n,getarg(1);
	set '@max,('@n < 0)? 0: getstrlen('@buf$) - '@n;

	for(set '@i,0; '@i < '@max && '@i < 128; set '@i,'@i+1) {
		set getelementofarray(getarg(2),'@i),substr('@buf$,'@n+'@i,1);
	}
	return '@i;	// 格納した個数を返す
}

//===============================================
// セパレータによる文字列分割
//	callfunc("StrSplit","<string>","<sep>",<variable>")
//-----------------------------------------------
function	script	StrSplit	{
	// StrIndexを展開して利用する
	set '@src$,getarg(0);
	set '@dst$,getarg(1);
	set '@len,getstrlen('@dst$);
	set '@max,getstrlen('@src$) - '@len;

	for(set '@i,0; '@i <= '@max; set '@i,'@i+1) {
		if( substr('@src$,'@i,'@len) == '@dst$ ) {
			set getelementofarray(getarg(2),'@idx),substr('@src$,'@pos,'@i - '@pos);
			set '@idx,'@idx+1;
			set '@pos,'@i + '@len;	// 次の検索開始位置を保存
			set '@i,'@pos-1;	// 次の検索位置まで飛ばす
		}
	}
	set getelementofarray(getarg(2),'@idx),substr('@src$,'@pos);	// 残りを末尾まで繋ぐ
	return '@idx+1;	// 格納した個数を返す
}


//===============================================
// substr関数の仕様
//-----------------------------------------------
prontera.gat,157,191,4	script	文字列抽出テスト	112,{
	set '@buf$,"ABCDEFGH";
	mes "[offsetの確認]";
	mes "正のoffset →";
	mes "　  0   1   2   3   4   5   6   7";
	mes "　  A   B   C   D   E   F   G   H";
	mes "　 -8  -7  -6  -5  -4  -3  -2  -1";
	mes "負のoffset ←";
	next;
	mes "[負のlength]";
	mes "　  0   1   2   3   4   5   6   7";
	mes "　  A   B   C   D   E   F   G   H";
	mes " ";
	mes "-1: A   B   C   D   E   F   G   -";
	mes "-3: A   B   C   D   E   -   -   -";
	next;
	mes "01 : " + substr('@buf$,2);		// CDEFGH
	mes "02 : " + substr('@buf$,1,4);	// BCDE
	mes "03 : " + substr('@buf$,3,8);	// DEFGH
	mes "04 : " + substr('@buf$,-3);	// FGH
	mes "05 : " + substr('@buf$,-5,4);	// DEFG
	mes "06 : " + substr('@buf$,1,-3);	// BCDE
	mes "07 : " + substr('@buf$,-5,-2);	// DEF
	mes "08 : " + substr('@buf$,-1,1);	// H
	mes "09 : " + substr('@buf$,-4,5);	// EFGH
	mes "10 : " + substr('@buf$,0,0);	// [nothing]
	mes "11 : " + substr('@buf$,4,0);	// [nothing]
	mes "12 : " + substr('@buf$,-9);
	mes "13 : " + substr('@buf$,10);
	mes "14 : " + substr('@buf$,1,-12);
	mes "15 : " + substr('@buf$,6,-3);
	mes "16 : " + substr('@buf$,-3,-4);
	mes "17 : " + substr('@buf$,6,-2);
	next;
	mes "[テスト]";
	mes "文字列を入力";
	next;
	input '@str$;
	mes "開始位置を入力";
	next;
	input '@offset;
	mes "取得個数を入力";
	next;
	input '@count;
	mes "substr(\"" +'@str$+ "\"," +'@offset+ "," +'@count+ ")";
	mes "  -> " + substr('@str$,'@offset,'@count);
	close;
}

//===============================================
// 文字列処理使用例
//-----------------------------------------------
prontera.gat,159,191,4	script	文字列処理テスト	113,{
	mes "StrTrim : "     + callfunc("StrTrim","   ABC");				// ABC
	mes "StrRTrim : "    + callfunc("StrRTrim","ABC   ");				// ABC
	mes "StrIndex : "    + callfunc("StrIndex","ABCDEF","CDE");			// 2
	mes "StrRIndex : "   + callfunc("StrRIndex","ABCDEF-ABCDEF","CDE");		// 9
	mes "StrCSpn : "     + callfunc("StrCSpn","ABCDEF","XYFDZ");			// 3
	mes "StrWCSpn : "    + callfunc("StrWCSpn","あいうえお","んえい");		// 2
	mes "StrDelete : "   + callfunc("StrDelete","ABCDEF",4);			// ABCDF
	mes "StrShift : "    + callfunc("StrShift","ABCDEF",3,2);			// ADEF
	mes "StrInsert : "   + callfunc("StrInsert","ABCDEF",3,"XYZ");			// ABCXYZDEF
	mes "StrReplace : "  + callfunc("StrReplace","ABCDEF-ABCDEF","CD","XYZ");	// ABXYZDEF-ABCDEF
	mes "StrAReplace : " + callfunc("StrAReplace","ABCDEF-ABCDEF","CD","XYZ");	// ABXYZDEF-ABXYZDEF
	mes "StrReverse : "  + callfunc("StrReverse","ABCDEF");				// FEDCBA
	mes "StrWReverse : " + callfunc("StrWReverse","あいうえお");			// おえういあ
	mes "StrShuffle : "  + callfunc("StrShuffle","ABCDEF");				// [random]
	next;
	mes "StrArray :";
	set '@c,callfunc("StrArray","ABCDEF",2,'@buf$);		// 4
	for(set '@i,0; '@i < '@c; set '@i,'@i+1) {
		mes "　" + '@i + " -> " + '@buf$['@i];		// 順にC,D,E,F
	}
	next;
	mes "StrSplit :";
	set '@c,callfunc("StrSplit","ABC#DE#F","#",'@buf$);	// 3
	for(set '@i,0; '@i < '@c; set '@i,'@i+1) {
		mes "　" + '@i + " -> " + '@buf$['@i];		// 順にABC,DE,F
	}
	close;
}
