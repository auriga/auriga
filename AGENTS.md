# AGENTS.md — Auriga 向け AI エージェント指針

このファイルは、AI コーディングエージェントが本リポジトリで作業するときの入口です。  
詳細ルールは `.agents/` に分割してあります。作業前に関連ファイルを読んでください。

Claude Code 向けの `CLAUDE.md` は本ファイルへのリンクです。内容の編集は **AGENTS.md** と **`.agents/`** で行ってください。

## ルール一覧

| ファイル | 内容 |
|----------|------|
| [`.agents/project.md`](.agents/project.md) | プロジェクト概要・ディレクトリ構成・主要ドキュメント・ライセンス |
| [`.agents/coding.md`](.agents/coding.md) | コーディング規約・設定/DB/スクリプト変更・CHANGELOG |
| [`.agents/build.md`](.agents/build.md) | ビルド・起動・CI |
| [`.agents/git.md`](.agents/git.md) | Git / ブランチ / コミット / PR の運用 |
| [`.agents/workflow.md`](.agents/workflow.md) | エージェントの作業境界（してよいこと / 確認すること / 禁止） |

## 最短サマリ

- 言語は **C11**。login / char / map の3サーバー構成。
- ビルド: Unix 系は `make`、Windows は `vc_make.bat` または `Auriga.sln`。
- 仕様はまず `doc/` を見る。重要な挙動変更は `CHANGELOG.md` に追記。
- **コミット・push・PR はユーザーが明示したときだけ。**
- 依頼範囲外の変更、秘密情報のコミット、不要なリファクタはしない。
