// バーターの定義例。使用する場合はmap設定でこのファイルを読み込んでください。
// 赤ポーション1個とゼロピー1個を交換（在庫無制限）。
prontera.gat,150,180,4	barter	アイテム交換例::BarterSample	87,501:0:909:1

// 蝶の羽1個と100Zeny＋ゼロピー2個を交換（在庫10個、精錬値不問）。
prontera.gat,152,180,4	exbarter	複数素材交換例::ExBarterSample	87,602:10:100:909:2:-1

// 配置しない店とコピー店の定義例。
-	barter	交換元::BarterSource	87,502:0:909:2
prontera.gat,154,180,4	substore(BarterSource)	交換例コピー::BarterCopy	87
