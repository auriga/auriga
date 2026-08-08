# ビルド・CI

詳細は `doc/server_build.txt` を参照。

## Linux / macOS / MinGW / Cygwin（gcc/clang）

```bash
make          # ビルド
make clean    # クリーン後に再ビルド
```

ビルドオプションはルートの `Makefile` で定義する（`PACKETVER`、`TXT_ONLY`、`PRE_RENEWAL`、`LOCALZLIB` など）。

## Windows（MSVC）

```bat
vc_make.bat       # ビルド（VS2017 以降。VS2026 対応あり）
vc_clean.bat      # クリーン
```

または `Auriga.sln`（`vcproj/`、Platform Toolset v145、x64）を Visual Studio で開く。

## 起動

- Unix 系: `start` / `auriga-start`
- Windows (MSVC): `win32_start.bat`

## CI

GitHub Actions で次を検証している。

- Windows MSVC 2022 / 2026
- Linux GCC / Clang
- macOS Clang

`src/**/*.c`、`src/**/*.h`、`vc_make.bat` などを変更した場合は、関連ワークフローが通ることを意識する。
