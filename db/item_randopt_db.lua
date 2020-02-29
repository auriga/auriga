-- ID,MOB_ID,{Slot,OptID,{OptVal_min,OptVal_max},Rate}

ItemRandoptTBL = 
{
	{--ハロウィンジャック => カボチャヘッド
		ID = 19175,
		MOB_ID = 1722,
		Option = {{1,148,{7,35},5000},{1,152,{1,13},5000},{2,170,{1,10},10000},},
	},
};

function ItemRandoptInit()
	for k, v in pairs(ItemRandoptTBL) do
		result = InsertRandopt(v.ID,v.MOB_ID,v.Option)
		if not result == true then
			return false
		end
	end

	return true;
end

return ItemRandoptInit()
