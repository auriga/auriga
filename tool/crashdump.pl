#!/bin/perl

# 基準ディレクトリ
$base_dir = "../";

# サーバーのファイル名
@server_name = ("login-server", "char-server", "map-server");

# リンクマップからシンボル名を読み込む
foreach $server( 0.. $#server_name ) {
	push @symbols, symbol_read("$base_dir$server_name[$server].map");
}

# クラッシュダンプのファイルを開く
open A, "<${base_dir}crashdump.log"         or die "Can't read  crashdump.log";
open B, ">${base_dir}crashdump_report.log" or die "Can't write crashdump_report.log";

$server = 0;
while( <A> ) {
	if( /^\t(0x\w+)/ ) {
		# 関数のアドレスなので、シンボル名を求める
		printf B "$1 : %s\n", sybmol_getname( $symbols[ $server ], hex($1) );
	} elsif( /^\t/ ) {
		# サーバー名が含まれている可能性があるので調べる
		my $a;
		foreach $a( 0 .. $#server_name ) {
			if( index($_, $server_name[$a] ) >= 0 ) {
				$server = $a; last;
			}
		}
		print B $_;
	} else {
		# それ以外なのでそのまま出力
		print B $_;
	}
}

close A;
close B;

# シンボルを読み込む
sub symbol_read {
	my $file = shift;
	my @func, @addr, @base;
	open(A, $file) or die "Can't open $file\n";
	while(<A>) {
		if( /(\d+):(\w+)\s+(\w+)H / ) {
			# 有効なアドレスの範囲
			$base[ $1 ] = hex($2);
			if( $base[ $1 ] > 0 ) {
				push @addr, [ hex($2), hex($2) + hex($3) ];
			}
		} elsif( /(\d+):(\w+)\s+(\w+)\s+(\w+)/ ) {
			# 関数名とそのアドレス(VC)
			push @func, [ hex($4), $3, $1];
		} elsif( /(\d+):(\w+)\s+(\w+)/ ) {
			# 関数名とそのアドレス
			if( $base[ $1 ] > 0 ) {
				push @func, [ $base[$1] + hex($2), $3, $1 ];
			}
		}
	}
	close A;
	# アドレスを元に大きい順に並び替える
	@func = sort { $b->[0] <=> $a->[0] } @func;
	return [ \@func, \@addr ];
}

# アドレスから関数名を返す
sub sybmol_getname {
	my $symbol      = shift;
	my $addr        = shift;
	my $symbol_func = $symbol->[0];
	my $symbol_addr = $symbol->[1];
	my $flag = 0;

	# 無効なアドレス判定
	foreach( @{ $symbol_addr } ) {
		if( $addr >= $_->[0] && $addr <= $_->[1] ) {
			$flag = 1;
		}
	}
	if( !$flag ) {
		# 無効なアドレスだった
		return "unknown (invalid address)";
	}
	foreach ( @{ $symbol_func } ) {
		if( $addr >= $_->[0] && $_->[1] =~ /^_[^_]/) {
			if( $_->[2] == 1 ) {
				return sprintf "%s + 0x%x", $_->[1], $addr - $_->[0];
			} else {
				return "unknown (invalid type)";
			}
		}
	}
	return "unknown (internal error)";
}
