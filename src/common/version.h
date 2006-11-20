#ifndef _VERSION_H_
#define _VERSION_H_

#define AURIGA_MAJOR_VERSION	0	// Major Version
#define AURIGA_MINOR_VERSION	0	// Minor Version
#define AURIGA_REVISION			15	// Revision

#define AURIGA_RELEASE_FLAG		1	// 1=Develop,0=Stable
#define AURIGA_OFFICIAL_FLAG	0	// 1=Mod,0=Official

#define AURIGA_SERVER_LOGIN		1	// login server
#define AURIGA_SERVER_CHAR		2	// char server
#define AURIGA_SERVER_INTER		4	// inter server
#define AURIGA_SERVER_MAP		8	// map server

// ATHENA_MOD_VERSIONはパッチ番号です。
// これは無理に変えなくても気が向いたら変える程度の扱いで。
// （毎回アップロードの度に変更するのも面倒と思われるし、そもそも
// 　この項目を参照する人がいるかどうかで疑問だから。）
// その程度の扱いなので、サーバーに問い合わせる側も、あくまで目安程度の扱いで
// あんまり信用しないこと。
// 鯖snapshotの時や、大きな変更があった場合は設定してほしいです。
// C言語の仕様上、最初に0を付けると8進数になるので間違えないで下さい。

// Aurigaでは未定義にする予定です
// Revision番号を更新してください
#define AURIGA_MOD_VERSION	0	// mod version (patch No.)

#endif
