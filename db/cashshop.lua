-- キャッシュショップの商品定義
-- Tab: 0 新着 / 1 人気 / 2 期間限定 / 3 レンタル / 4 装備 / 5 強化 / 6 回復 / 7 その他 / 8 セール
-- Price: PC_SHOP_POINTの消費量
-- StartDate / EndDate: YYYYMMDD。0は制限なし。終了日当日まで購入可能。
-- 同じTabとItemIDの重複は登録不可。

CashshopTBL = {
	{ Tab = 0, ItemID = 501, Price = 10, StartDate = 0, EndDate = 0 },
	{ Tab = 0, ItemID = 502, Price = 10, StartDate = 0, EndDate = 0 },
	{ Tab = 0, ItemID = 503, Price = 10, StartDate = 0, EndDate = 0 },
	{ Tab = 1, ItemID = 504, Price = 20, StartDate = 0, EndDate = 0 },
	{ Tab = 1, ItemID = 505, Price = 20, StartDate = 0, EndDate = 0 },
	{ Tab = 6, ItemID = 506, Price = 5, StartDate = 0, EndDate = 0 },
	{ Tab = 6, ItemID = 507, Price = 5, StartDate = 0, EndDate = 0 },
	{ Tab = 7, ItemID = 645, Price = 50, StartDate = 0, EndDate = 0 },
}

ClearCashshop()
for _, v in ipairs(CashshopTBL) do
	if not InsertCashshopItem(v.Tab, v.ItemID, v.Price, v.StartDate or 0, v.EndDate or 0) then
		error(string.format("cashshop.lua: invalid entry Tab=%d ItemID=%d", v.Tab, v.ItemID))
	end
end
return true
