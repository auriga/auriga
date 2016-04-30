// 配列のテスト
prontera.gat,164,190,1	script	配列テスト	112,{
	set @hoge[0],1;
	set @hoge[1],5;
	mes "hoge[2]を入力してください";
	next;
	input @hoge[2];
	mes "hoge   => " + @hoge;
	mes "hoge[0]=> " + @hoge[0];
	mes "hoge[1]=> " + @hoge[1];
	mes "hoge[2]=> " + @hoge[2];
	next;
	setarray @hoge[1],2,3,4,5;
	mes "true: 5,1,2,3,4";
	mes "hoge size = "+ getarraysize(@hoge);
	mes "hoge[0]=> " + @hoge[0];
	mes "hoge[1]=> " + @hoge[1];
	mes "hoge[2]=> " + @hoge[2];
	mes "hoge[3]=> " + @hoge[3];
	next;
	copyarray @fuga[0],@hoge[2],2;
	mes "true: 3,4,0";
	mes "fuga[0]=> " + @fuga[0];
	mes "fuga[1]=> " + @fuga[1];
	mes "fuga[2]=> " + @fuga[2];
	next;
	deletearray @hoge[1],2;
	mes "true: 1,4,5,0";
	mes "hoge[0]=> " + @hoge[0];
	mes "hoge[1]=> " + @hoge[1];
	mes "hoge[2]=> " + @hoge[2];
	mes "hoge[3]=> " + @hoge[3];
	next;

	// 要素の小さい方からコピー
	setarray @hoge,0,1,2,3;
	copyarray @hoge[0],@hoge[1],3;
	mes "true: 1,2,3,3";
	mes @hoge[0];
	mes @hoge[1];
	mes @hoge[2];
	mes @hoge[3];
	next;

	// 要素の大きい方からコピー
	setarray @hoge,1,2,3,0;
	copyarray @hoge[1],@hoge[0],3;
	mes "true: 1,1,2,3";
	mes @hoge[0];
	mes @hoge[1];
	mes @hoge[2];
	mes @hoge[3];
	close;
}
