#!/usr/bin/perl

#=========================================================================
# serverstatus.cgi  ver.1.02  by 胡蝶蘭
#	checkversionをラップした、サーバー状態を表示するcgi
#
# ** 設定方法 **
#
# - 下の $checkv 変数に checkversion へのパスを設定すること。
#
# - perl にパスが通っていない場合は $perl を perl への正しいパスにすること。
#
# - %servers をそれぞれ正しく設定する。IP はホスト名可。
#
# - %servers で設定したキャッシュファイル(空のファイル)を作成する。
#   また、書き換え可能にすること。
#   例> touch ss_login.cache ; chmod 666 ss_login.cache
#
# - 必要ならキャッシュ間隔やタイトルを変更
#
# - 複数map鯖にしている場合は,%serversに行を加えることで対応可能だが、
#   @serverorderに%serversのキーを加えることを忘れないように。
#
# - @state1,@state2で表示を多少変更可能。
#
# - 他は普通のCGIと同じ。（実行権やcgi-binフォルダなど）
#
#
# ** その他 **
#
# - あくまで現在の状態表示でログはとっていないので過去のデータは参照できない
#
# - キャッシュ間隔を 0 にするとキャッシュしなくなるが、
#   負荷が非常に大きいので注意。
#
# - ping によるチェックはおまけ程度。デフォルトだとチェックしない。
#   tcp-ping は負荷が高い。icmp-ping は軽めだがroot権が必要なので実質無理。
#   Net::Ping 必須。ActivePerl などでは alarm が未実装で動かない可能性あり。
#   うまくいかないなら ping しないほうが負荷が低くなる。
#
#
# ** エラーへの対処 **
#
# - Can't execute checkversion
#   checkversion が無いか、パスが違う。もしくは perl のコマンド名が違う。
#
# - Cache file open error.
#   キャッシュファイルが開けない。ちゃんと作成して書き込み可能にすること。
#
# - flock error.
#   flock が未サポート。キャッシュしなければ一応動くが負荷が高い。
#   flock を呼んでいるところをコメント化すれば一応動くがキャッシュが
#   壊れやすい。
#
#-------------------------------------------------------------------------


my($checkv)="../checkversion";	# checkversion のパス(おそらく変更が必要)
my($perl)  ="perl";				# perl のコマンド名

my($checkping)="";			# NG のとき ping によるチェックを行うpingの種類
							# "tcp", "udp", "icmp"(root権必要), ""から選択
							# ""だと ping しない。
							# Net::Ping がない/実装されていないと無視

my($cacheperiod) = 120;		# キャッシュ間隔(秒数)

my($title) = "Auriga Server Status";	# ページタイトル

my(@serverorder) = (			# 表示順
	"login","char","map"
);
my(%servers) = (				# データ(ip,名前,キャッシュファイル名)
	"login"	=> {
					"ip"	=> "127.0.0.1:6900",
					"desc"	=> "Login Server",
					"cache"	=> "./ss_login.cache",
				},

	"char"	=> {
					"ip"	=> "127.0.0.1:6121",
					"desc"	=> "Character Server",
					"cache" => "./ss_char.cache",
				},

	"map"	=> {
					"ip"	=> "127.0.0.1:5121",
					"desc"	=> "Map Server",
					"cache"	=> "./ss_map.cache",
				},
);

my(@state1) = (					# 状態表示
	"Down",		# 接続できない
	"Good",		# 正常動作中
	"Error",	# %serversの設定がおかしい(ポート番号)
	"Closed",	# pingには応答
);
my(@state2) = (					# 色
	"#ffc0c0",	# 接続できない
	"#c0ffc0",	# 正常動作中
	"#c0c0ff",	# %serversの設定がおかしい(ポート番号)
	"#ffffc0",	# pingには応答
);

#--------------------------- 設定ここまで --------------------------------




use strict;
eval " use Net::Ping; ";


my($msg) = << "EOD";
<html>
<head><title>$title</title></head>
<body text="black" bgcolor="white" link="blue" vlink="blue" alink="blue">
<h1>$title</h1>
<table border=1>
<tr><th>Server</th><th>Address</th><th>Status</th><th>Version</th></tr>
EOD

my(%langconv) = (
);

my($i);
foreach $i (@serverorder){
	my( $state, $ver ) = CheckServer( $servers{$i} );

	$msg.= "<tr bgcolor=\"$state2[$state]\"><td>".$servers{$i}->{desc}.
		"</td><td>".$servers{$i}->{ip}."</td><td>$state1[$state]</td>".
		"<td>$ver</td></tr>\n";
}
$msg.="</table></body></html>\n";

print "Content-type: text/html\n\n$msg";

sub CheckServer
{
	my($server) = shift;
	my($state)  = 0;

	if($cacheperiod>0)
	{
		open FH, "+<".$server->{cache} or HttpError("Cache file open error.");
		flock FH,2 or HttpError("flock error");
		my(@cache) = split /,/, <FH>;
		if( time < $cache[0] + $cacheperiod )
		{
			close FH;
			return ( $cache[1], $cache[2] );
		}
	}

	open PIPE,"$perl $checkv $server->{ip} |"
		or HttpError("Can't execute checkversion.\n");
	my(@dat)=<PIPE>;
	close PIPE;

	if($dat[1]=~m/Auriga/ && $dat[2]=~/server/){
		if($dat[2]=~/$i/ ){
			$state=1;
		}else{
			$state=2;
		}
	}elsif($checkping){
		eval {
			my($p) = Net::Ping->new($checkping);
			my($addr)=$server->{ip};
			$addr=~s/\:\d+$//;
			$state=3 if $p->ping($addr);
			$p->close();
		};
	}

	if($cacheperiod>0)
	{
		seek FH,0,0;
		truncate FH,0;
		print FH join( ",", time, $state, $dat[1] );
		close FH;
	}

	return ($state, $dat[1]);
};

sub LangConv {
	my(@lst)= @_;
	my($a,$b,@out)=();
	foreach $a(@lst){
		foreach $b(keys %langconv){
			$a=~s/$b/$langconv{$b}/g;
			my($rep1)=$1;
			$a=~s/\$1/$rep1/g;
		}
		push @out,$a;
	}
	return @out;
}

sub HttpMsg {
	my($msg)=join("", LangConv(@_));
	$msg=~s/\n/<br>\n/g;
	print LangConv("Content-type: text/html\n\n"),$msg;
	exit;
}

sub HttpError {
	my($msg)=join("", LangConv(@_));
	$msg=~s/\n/<br>\n/g;
	print LangConv("Content-type: text/html\n\n"),$msg;
	exit;
}
