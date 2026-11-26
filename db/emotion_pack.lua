-- キャッシュ・エモーションパック・カタログ
--
-- Id:        エモーションパックID。0は基本エモーション。
-- Price:     価格
-- ItemID:    交換ItemID。ItemID0でPriceを設定するとPC_SHOP_POINTによる購入として扱われます。
-- StartDate / EndDate: 販売期間。YYYYMMDD形式(0は無期限)。
-- Duration:  購入後のレンタル期間。単位は秒(0は無期限)。
--
-- 購入パックはアカウント変数 EMOTION_PACKSで管理され、レンタル期間有はEMO_P<id>です。

EmotionPackTBL =
{
	-- Client pack IDs: 1 = 21st Anniversary, 2 = 2023 Chuseok, 3 = 2023 Thanksgiving.
	-- Prices below are server settings (Emotion Coin 1001874).
	{ Id = 1, Price = 0, ItemID = 1001874, StartDate = 0, EndDate = 0, Duration = 0 },
	{ Id = 2, Price = 1, ItemID = 1001874, StartDate = 0, EndDate = 0, Duration = 0 },
	{ Id = 3, Price = 1, ItemID = 1001874, StartDate = 0, EndDate = 0, Duration = 0 },
}

local function yyyymmdd_today()
	return tonumber(os.date("%Y%m%d"))
end

function EmotionPackInit()
	ClearEmotionPack()
	local today = yyyymmdd_today()
	local ok, warn, skip = 0, 0, 0

	for _, v in ipairs(EmotionPackTBL) do
		local id = v.Id or 0
		local price = v.Price or 0
		local item = v.ItemID or 0
		local start_date = v.StartDate or 0
		local end_date = v.EndDate or 0
		local duration = v.Duration or 0

		if id <= 0 or price < 0 then
			print(string.format("emotion_pack.lua: skip invalid Id=%s Price=%s", tostring(v.Id), tostring(v.Price)))
			skip = skip + 1
		elseif start_date > 0 and end_date > 0 and start_date > end_date then
			print(string.format("emotion_pack.lua: DATE AUDIT fail Id=%d Start>%d End (skipped)", id, start_date))
			skip = skip + 1
		else
			if end_date > 0 and end_date < today then
				print(string.format("emotion_pack.lua: DATE AUDIT expired Id=%d EndDate=%d", id, end_date))
				warn = warn + 1
			elseif start_date > 0 and start_date > today then
				print(string.format("emotion_pack.lua: DATE AUDIT upcoming Id=%d StartDate=%d", id, start_date))
				warn = warn + 1
			end
			if InsertEmotionPack(id, price, item, start_date, end_date, duration) == true then
				ok = ok + 1
			else
				print(string.format("emotion_pack.lua: InsertEmotionPack failed Id=%d", id))
				skip = skip + 1
			end
		end
	end

	print(string.format("emotion_pack.lua: loaded=%d warn=%d skip=%d (today=%d)", ok, warn, skip, today))
	return true
end

return EmotionPackInit()
