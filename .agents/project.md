# プロジェクト概要

Auriga は、プライベートサーバーエミュレータです。  
Athena 系を基にした **C11** のサーバー実装で、主に日本語コミュニティ向けに開発されています。

## サーバー構成

| バイナリ | 役割 | 主なソース |
|----------|------|------------|
| `login-server` | アカウント認証 | `src/login/` |
| `char-server` | キャラクター・インターサーバ | `src/char/` |
| `map-server` | マップ・戦闘・NPC・スクリプト | `src/map/` |

共有コードは `src/common/`（ソケット、タイマー、DB、Lua、zlib など）にあります。

## ディレクトリ構成

```
src/          C ソース（login / char / map / common / converter）
conf/         サーバー設定（*_auriga.conf）。運用差分は conf/import/ を優先
db/           アイテム・Mob・スキル等のデータ定義
script/       NPC / ワープ / モンスター配置などのスクリプト（.sc 等）
sql-files/    MySQL スキーマ・マイグレーション（*_changetable.sql）
doc/          設計・参照ドキュメント（日本語）
vcproj/       Visual Studio プロジェクト（Auriga.sln）
.github/      CI ワークフロー
.agents/      AI エージェント向けルール（本ディレクトリ）
```

## よく使うドキュメント

| ファイル | 内容 |
|----------|------|
| `doc/server_build.txt` | 構築・ビルドオプション |
| `doc/conf_ref.txt` | 設定ファイル |
| `doc/db_ref.txt` | DB 定義 |
| `doc/script_ref.txt` | スクリプト命令 |
| `doc/item_bonus.txt` | アイテムボーナス |
| `doc/client_packet.txt` | クライアントパケット |
| `doc/inter_server_packet.txt` | サーバー間パケット |
| `doc/sqllogin.txt` | MySQL ログイン周り |
| `doc/lua_ref.txt` | Lua 連携 |
| `doc/httpd.txt` | 内蔵 httpd / CGI |

## ライセンス

`COPYING` / `COPYING_JA` を確認すること。派生物・再配布の扱いに注意する。
