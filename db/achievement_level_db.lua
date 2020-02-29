AchievementLevelTBL = 
{
	[1] = 18,
	[2] = 49,
	[3] = 98,
	[4] = 171,
	[5] = 306,
	[6] = 410,
	[7] = 550,
	[8] = 728,
	[9] = 942,
	[10] = 1247,
	[11] = 1504,
	[12] = 1804,
	[13] = 2152,
	[14] = 2550,
	[15] = 3070,
	[16] = 3522,
	[17] = 4030,
	[18] = 4592,
	[19] = 5210,
	[20] = 5980,
};

function AchievementLevelInit()
	for achieveLv, achieveExp in pairs(AchievementLevelTBL) do
		result = InsertAchieveLevelDB(achieveLv, achieveExp)
		if not result == true then
			return false
		end
	end

	return true
end

return AchievementLevelInit()
