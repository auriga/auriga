// csv 関数	テストスクリプト

prontera.gat,156,178,1	script	ペット図鑑	112,{
	function pet_info;
	set @file$, "db/pet_db.txt";
	mes "ペット図鑑";
	next;
	while(1) {
		switch( select("ID検索", "名前検索", "順番表示", "キャンセル") ) {
		case 1: // ID検索
			input @pet_id;
			pet_info csvfind(@file$, 0, @pet_id); // IDは0列目
			break;
		case 2: // 名前検索
			input @pet_name$;
			pet_info csvfind(@file$, 2, @pet_name$); // 名前は2列目
			break;
		case 3: // 順番表示
			set @pet_line,  0;
			set @pet_count, csvgetrows( @file$ );
			for( set @i, 0; @i < @pet_count; set @i, @i + 1) {
				// csvread 関数は文字列で帰ってくるので、一端値を
				// 数値変数に代入して数値化している
				set @pet_id, csvread( @file$, @i, 0 );
				if( @pet_id == 0 ) continue;
				pet_info @i;
			}
			break;
		case 4:
			close;
		}
	}
	// pet_info( line_no ) : ペットの情報を表示する
	function pet_info {
		if( getarg(0) == -1 ) {
			mes "お探しのペットは存在しません。";
		} else {
			csvreadarray @file$, getarg(0), @mobinfo$;
			set @pet_id, @mobinfo$;
			if( @pet_id == 0 ) {
				mes "お探しのペットは存在しません。";
			} else {
				mes "ID "           + @mobinfo$[0];
				mes "Name "         + @mobinfo$[2];
				mes "捕獲アイテム " + getitemname(@mobinfo$[3]);
				mes "餌 "           + getitemname(@mobinfo$[6]);
			}
		}
		next;
	}
}
