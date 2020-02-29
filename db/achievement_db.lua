ACH_KILL_MOB	= 1
ACH_USE_ITEM	= 2
ACH_QUEST		= 3
ACH_LEVEL		= 4
ACH_STATUS		= 5
ACH_ACHIEVE		= 6
ACH_ACHIEVE_RANK= 7
ACH_ADVENTURE	= 8
ACH_TAMING		= 9
ACH_PET_FRIEND	= 10
ACH_ADD_FRIEND	= 11
ACH_SPEND_ZENY	= 12
ACH_GET_ZENY	= 13
ACH_JOBCHANGE	= 14

AchievementTBL = 
{
	[500000] = {
		Name = "ロックリッジ",
		Type = ACH_QUEST,
		Content = {
			[1] = {
				ID = 202040,			--ロックリッジ
			}
		},
		Reward = {
			Title = 2000
		},
		Score = 1,
	},
	[500001] = {
		Name = "住人たちの悩み～ロックリッジ～(1)",
		Type = ACH_QUEST,
		Content = {
			[1] = {
				ID = 1329,			--困りもののワンちゃん
			},
			[2] = {
				ID = 1332,			--愛犬の復讐
			},
			[3] = {
				ID = 16079,			--荒野の厄介者
			}
		},
		Reward = {},
		Score = 1,
	},
	[500002] = {
		Name = "住人たちの悩み～ロックリッジ～(2)",
		Type = ACH_QUEST,
		Content = {
			[1] = {
				ID = 12382,			--食材がない！
			},
			[2] = {
				ID = 12411,			--異国の商人
			},
			[3] = {
				ID = 12390,			--治安維持活動　初級
			},
			[4] = {
				ID = 9461,			--原住民の頼み
			}
		},
		Reward = {},
		Score = 1,
	},
	[500003] = {
		Name = "住人たちの悩み～ロックリッジ～(3)",
		Type = ACH_QUEST,
		Content = {
			[1] = {
				ID = 1299,			--ガスターアレルギー
			},
			[2] = {
				ID = 14673,			--花火大会の準備
			},
			[3] = {
				ID = 12398,			--治安維持活動　上級
			},
			[4] = {
				ID = 12404,			--配管整備作業
			},
			[5] = {
				ID = 9459,			--排水パイプ掃除
			}
		},
		Reward = {},
		Score = 1,
	},
	[500004] = {
		Name = "開拓地の何でも屋",
		Type = ACH_ACHIEVE,
		Content = {
			[1] = {
				ID = 500001,
			},
			[2] = {
				ID = 500002,
			},
			[3] = {
				ID = 500003,
			}
		},
		Reward = {
			Title = 2001,
			Script = "{ getitem 31141,1; }"
		},
		Score = 1,
	},
	[500005] = {
		Name = "牛賊団退治～初級～(1)",
		Type = ACH_KILL_MOB,
		Content = {
			[1] = {
				ID = 3736,				--ラウンドライダー
				Count = 100
			},
			[2] = {
				ID = 3737,				--サイドライダー
				Count = 100
			},
			[3] = {
				ID = 3738,				--ブレードライダー
				Count = 100
			}
		},
		Reward = {
			Title = 2002
		},
		Score = 1,
	},
	[500006] = {
		Name = "牛賊団退治～初級～(2)",
		Type = ACH_KILL_MOB,
		Content = {
			[1] = {
				ID = 3736,				--ラウンドライダー
				Count = 1000
			},
			[2] = {
				ID = 3737,				--サイドライダー
				Count = 1000
			},
			[3] = {
				ID = 3738,				--ブレードライダー
				Count = 1000
			}
		},
		Reward = {
			Title = 2003
		},
		Score = 1,
	},
	[500007] = {
		Name = "牛賊団退治～初級～(3)",
		Type = ACH_KILL_MOB,
		Content = {
			[1] = {
				ID = 3736,				--ラウンドライダー
				Count = 10000
			},
			[2] = {
				ID = 3737,				--サイドライダー
				Count = 10000
			},
			[3] = {
				ID = 3738,				--ブレードライダー
				Count = 10000
			}
		},
		Reward = {
			Title = 2004
		},
		Score = 1,
	},
	[500008] = {
		Name = "牛賊団退治～上級～(1)",
		Type = ACH_KILL_MOB,
		Content = {
			[1] = {
				ID = 3747,				--トップラウンドライダー
				Count = 100
			},
			[2] = {
				ID = 3748,				--トップサイドライダー
				Count = 100
			},
			[3] = {
				ID = 3749,				--トップブレードライダー
				Count = 100
			}
		},
		Reward = {
			Title = 2005
		},
		Score = 1,
	},
	[500009] = {
		Name = "牛賊団退治～上級～(2)",
		Type = ACH_KILL_MOB,
		Content = {
			[1] = {
				ID = 3747,				--トップラウンドライダー
				Count = 1000
			},
			[2] = {
				ID = 3748,				--トップサイドライダー
				Count = 1000
			},
			[3] = {
				ID = 3749,				--トップブレードライダー
				Count = 1000
			}
		},
		Reward = {
			Title = 2006
		},
		Score = 1,
	},
	[500010] = {
		Name = "牛賊団退治～上級～(3)",
		Type = ACH_KILL_MOB,
		Content = {
			[1] = {
				ID = 3747,				--トップラウンドライダー
				Count = 10000
			},
			[2] = {
				ID = 3748,				--トップサイドライダー
				Count = 10000
			},
			[3] = {
				ID = 3749,				--トップブレードライダー
				Count = 10000
			}
		},
		Reward = {
			Title = 2007
		},
		Score = 1,
	},
	[500011] = {
		Name = "地下街の治安維持(1)",
		Type = ACH_KILL_MOB,
		Content = {
			[1] = {
				ID = 3787,				--カニバラウス
				Count = 100
			},
			[2] = {
				ID = 3788,				--プラズマラット
				Count = 100
			}
		},
		Reward = {
			Title = 2008
		},
		Score = 1,
	},
	[500012] = {
		Name = "地下街の治安維持(2)",
		Type = ACH_KILL_MOB,
		Content = {
			[1] = {
				ID = 3787,				--カニバラウス
				Count = 1000
			},
			[2] = {
				ID = 3788,				--プラズマラット
				Count = 1000
			}
		},
		Reward = {
			Title = 2009
		},
		Score = 1,
	},
	[500013] = {
		Name = "地下街の治安維持(3)",
		Type = ACH_KILL_MOB,
		Content = {
			[1] = {
				ID = 3787,				--カニバラウス
				Count = 10000
			},
			[2] = {
				ID = 3788,				--プラズマラット
				Count = 10000
			}
		},
		Reward = {
			Title = 2010
		},
		Score = 1,
	},
	[500014] = {
		Name = "ロックリッジマスター",
		Type = ACH_ACHIEVE,
		Content = {
			[1] = {
				ID = 500004				--開拓地の何でも屋
			},
			[2] = {
				ID = 500007				--牛賊団退治～初級～(3)
			},
			[3] = {
				ID = 500010				--牛賊団退治～上級～(3)
			},
			[4] = {
				ID = 500013				--地下街の治安維持(3)
			}
		},
		Reward = {
			Title = 2011
		},
		Score = 1,
	},
	[500015] = {
		Name = "パワスポ",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2012
		},
		Score = 1,
	},

	[500016] = {
		Name = "天秤座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2013
		},
		Score = 1,
	},
	[500017] = {
		Name = "蠍座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2014
		},
		Score = 1,
	},
	--Missing
	[500020] = {
		Name = "牡羊座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2017
		},
		Score = 1,
	},
	[500021] = {
		Name = "山羊座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2018
		},
		Score = 1,
	},
	[500022] = {
		Name = "魚座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2019
		},
		Score = 1,
	},
	[500023] = {
		Name = "サモンビギナー",
		Type = ACH_USE_ITEM,
		Content = {
			[1] = {
				ID = 604,				--古木の枝
				Count = 1
			}
		},
		Reward = {
			Title = 2020
		},
		Score = 1,
	},
	[500024] = {
		Name = "サモンマスター",
		Type = ACH_USE_ITEM,
		Content = {
			[1] = {
				ID = 604,				--古木の枝
				Count = 100
			}
		},
		Reward = {
			Title = 2021
		},
		Score = 1,
	},
	[500025] = {
		Name = "乙女座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2022
		},
		Score = 1,
	},
	[500026] = {
		Name = "獅子座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2023
		},
		Score = 1,
	},
	[500027] = {
		Name = "蟹座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2024
		},
		Score = 1,
	},
	[500028] = {
		Name = "牡牛座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2025
		},
		Score = 1,
	},
	[500029] = {
		Name = "双子座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2026
		},
		Score = 1,
	},
	[500030] = {
		Name = "射手座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2027
		},
		Score = 1,
	},
	[500031] = {
		Name = "蛇遣座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2028
		},
		Score = 1,
	},
	[500032] = {
		Name = "水瓶座の煌めき",
		Type = ACH_ADVENTURE,
		Content = {
			[1] = {
				ID = 1
			}
		},
		Reward = {
			Title = 2029
		},
		Score = 1,
	},
	[500033] = {
		Name = "激情の星座たち",
		Type = ACH_ACHIEVE,
		Content = {
			[1] = {
				ID = 500020
			},
			[2] = {
				ID = 500027
			},
			[3] = {
				ID = 500016
			},
			[4] = {
				ID = 500021
			}
		},
		Reward = {
			Title = 2030
		},
		Score = 1,
	},
	[500034] = {
		Name = "堅牢たる星座たち",
		Type = ACH_ACHIEVE,
		Content = {
			[1] = {
				ID = 500028
			},
			[2] = {
				ID = 500026
			},
			[3] = {
				ID = 500017
			},
			[4] = {
				ID = 500032
			}
		},
		Reward = {
			Title = 2031
		},
		Score = 1,
	},
	[500035] = {
		Name = "うつろいし星座たち",
		Type = ACH_ACHIEVE,
		Content = {
			[1] = {
				ID = 500029
			},
			[2] = {
				ID = 500025
			},
			[3] = {
				ID = 500030
			},
			[4] = {
				ID = 500022
			}
		},
		Reward = {
			Title = 2032
		},
		Score = 1,
	},
	[500036] = {
		Name = "The Zodiac",
		Type = ACH_ACHIEVE,
		Content = {
			[1] = {
				ID = 500033
			},
			[2] = {
				ID = 500034
			},
			[3] = {
				ID = 500035
			},
			[4] = {
				ID = 500031
			}
		},
		Reward = {
			Title = 2033
		},
		Score = 1,
	},
	[500037] = {
		Name = "カボチャケーキを食べよう！",
		Type = ACH_USE_ITEM,
		Content = {
			[1] = {
				ID = 11550,				--カボチャケーキ
				Count = 100
			}
		},
		Reward = {
			Title = 2034
		},
		Score = 1,
	},
	[500038] = {
		Name = "スティックキャンディおいちい!!",
		Type = ACH_USE_ITEM,
		Content = {
			[1] = {
				ID = 530,				--スティックキャンディ
				Count = 10000
			}
		},
		Reward = {
			Title = 2035
		},
		Score = 1,
	},
	[500039] = {
		Name = "仲良しベアドール",
		Type = ACH_PET_FRIEND,
		Content = {
			[1] = {
				ID = 1622,				--ベアドール
				Count = 900
			}
		},
		Reward = {
			Title = 2036,
			Script = "{ getitem 31826,1; }"
		},
		Score = 1,
	},
	[500040] = {
		Name = "手作りチョコを食べよう！",
		Type = ACH_USE_ITEM,
		Content = {
			[1] = {
				ID = 559,				--手作りチョコ
				Count = 2140
			}
		},
		Reward = {
			Title = 2037
		},
		Score = 1,
	},
};

function AchievementInit()
	for achieveID, achieveInfo in pairs(AchievementTBL) do
		if nil == achieveInfo.Reward.Title then
			achieveInfo.Reward.Title = 0
		end
		if nil == achieveInfo.Reward.Script then
			achieveInfo.Reward.Script = "{}"
		end
		result = InsertAchieveInfo(achieveID, achieveInfo.Name, achieveInfo.Type, achieveInfo.Score, achieveInfo.Reward.Title, achieveInfo.Reward.Script)
		if not result == true then
			return false
		end
		for v, achieveContent in pairs(achieveInfo.Content) do
			if nil == achieveContent.ID then
				achieveContent.ID = 1
			end
			if nil == achieveContent.Count then
				achieveContent.Count = 1
			end
			result = InsertAchieveContent(achieveID, achieveContent.ID, achieveContent.Count)
			if not result == true then
				return false
			end
		end
	end

	InsertAchieveDBEnd()
	return true
end

return AchievementInit()
