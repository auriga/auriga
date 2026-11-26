-- キャッシュショップの商品定義
-- Tab: 0 新着 / 1 人気 / 2 期間限定 / 3 レンタル / 4 装備 / 5 強化 / 6 回復 / 7 その他 / 8 セール
-- Price: PC_SHOP_POINTの消費量
-- StartDate / EndDate: YYYYMMDD。0は制限なし。終了日当日まで購入可能。
-- 同じTabとItemIDの重複は登録不可。

local TAB_NEW = 0 -- 新着
local TAB_POPULAR = 1 -- 人気
local TAB_LIMITED = 2 -- 期間限定
local TAB_RENTAL = 3 -- レンタル
local TAB_EQUIPMENT = 4 -- 装備
local TAB_ENHANCEMENT = 5 -- 強化
local TAB_RECOVERY = 6 -- 回復
local TAB_OTHER = 7 -- その他
local TAB_SALE = 8 -- セール

CashshopTBL = {
	-- 新着
	-- { Tab = TAB_NEW, ItemID = 17159, Price = 5000, StartDate = 0, EndDate = 0 },
	-- { Tab = TAB_NEW, ItemID = 201145, Price = 5000, StartDate = 0, EndDate = 0 },
	-- 人気
	{ Tab = TAB_POPULAR, ItemID = 12920, Price = 10000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_POPULAR, ItemID = 14904, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_POPULAR, ItemID = 14905, Price = 15000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_POPULAR, ItemID = 17289, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_POPULAR, ItemID = 16653, Price = 10000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_POPULAR, ItemID = 12922, Price = 7500, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_POPULAR, ItemID = 14289, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_POPULAR, ItemID = 13990, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_POPULAR, ItemID = 17634, Price = 5000, StartDate = 0, EndDate = 0 },
	-- 強化
	{ Tab = TAB_ENHANCEMENT, ItemID = 16653, Price = 10000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12900, Price = 7500, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 13990, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 13500, Price = 12000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12901, Price = 7000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 17290, Price = 9000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12913, Price = 1000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12914, Price = 1000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12927, Price = 1500, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12917, Price = 1000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12918, Price = 1000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12903, Price = 3000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12904, Price = 3000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12908, Price = 3000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12905, Price = 3000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12906, Price = 3000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_ENHANCEMENT, ItemID = 12907, Price = 3000, StartDate = 0, EndDate = 0 },
	-- その他
	{ Tab = TAB_OTHER, ItemID = 12920, Price = 10000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 12921, Price = 7000, StartDate = 0, EndDate = 0 },
	-- { Tab = TAB_OTHER, ItemID = 200456, Price = 10000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 14905, Price = 15000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 14904, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 16682, Price = 12000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 17634, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 14289, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 14290, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 17219, Price = 20000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 12911, Price = 15000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 12922, Price = 7500, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 16674, Price = 7500, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 17289, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 12910, Price = 500, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 200488, Price = 5000, StartDate = 0, EndDate = 0 },
	{ Tab = TAB_OTHER, ItemID = 200513, Price = 5000, StartDate = 0, EndDate = 0 },
	-- { Tab = TAB_OTHER, ItemID = 17159, Price = 5000, StartDate = 0, EndDate = 0 },
	-- { Tab = TAB_OTHER, ItemID = 201145, Price = 5000, StartDate = 0, EndDate = 0 },
}

ClearCashshop()
for _, v in ipairs(CashshopTBL) do
	if not InsertCashshopItem(v.Tab, v.ItemID, v.Price, v.StartDate or 0, v.EndDate or 0) then
		error(string.format("cashshop.lua: invalid entry Tab=%d ItemID=%d", v.Tab, v.ItemID))
	end
end
return true
