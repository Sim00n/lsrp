public OnPlayerUseItem(playerid, itemid)
(
	if(Offer(playerid)(oType) == OFFER_ITEM)
	(
		if(Offer(playerid)(oValue) == itemid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ przedmiotu, ktÛry oferujesz., OK, )
			return 0
		)
	)

	string(256)
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøywaÊ przedmiotÛw podczas stanu nieprzytomnoúci., OK, )
		return 1
	)

	if(ItemInfo(itemid)(iPlace) != PLACE_PLAYER || ItemInfo(itemid)(iOwner) != PlayerCache(playerid)(pUID))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Wystπpi≥ b≥πd podczas prÛby uøycia przedmiotu.\nSprÛbuj ponownie., OK, )
		return 1
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_WATCH)
	(
		hour, minute, second
		gettime(hour, minute, second)

		format(string, sizeof(string), ~w~Godzina:~w~ ~y~%02d:%02d:%02d~y~~w~., hour, minute, second)
		GameTextForPlayer(playerid, string, 5000, 1)

		format(string, sizeof(string), * %s spoglπda na zegarek., PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)

		ApplyAnimation(playerid,COP_AMBIENT,Coplook_watch,4.1,0,0,0,0,0,1)
  		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_FOOD)
	(
		if(PlayerCache(playerid)(pFed) ( 80)
		(
			if(PlayerCache(playerid)(pFed) + ItemInfo(itemid)(iValue1) (= 80)
			(
	  			PlayerCache(playerid)(pFed) += ItemInfo(itemid)(iValue1)
			)
			else
			(
				PlayerCache(playerid)(pFed) = 80
				
				TextDrawSetString(Text:TextDrawMainInfo(playerid), Twoja postac jest ~y~najedzona~w~.)
				TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
				
				PlayerCache(playerid)(pShowInfoText) = 5
			)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Spoøy≥eú jedzenie. TwÛj pasek HP bÍdzie z minuty na minutÍ zwiÍksza≥ siÍ., OK, )
						
			format(string, sizeof(string), * %s spoøywa\%s\., PlayerName(playerid), ItemInfo(itemid)(iName))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
			
			DeleteItem(ItemInfo(itemid)(iUID))
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Twoja postaÊ jest w pe≥ni najedzona, nie moøe wiÍc nic wiÍcej przegryüÊ., OK, )
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_CIGGY)
	(
  		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY)
  		
  		ItemInfo(itemid)(iValue1) --
		PlayerCache(playerid)(pDrugLevel) += 5
  		
  		if(ItemInfo(itemid)(iValue1) (= 0)
		(
			DeleteItem(ItemInfo(itemid)(iUID))
			return 1
		)
		
		mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
   		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_CUBE)
	(
		rand = 1 + random(6)

		format(string, sizeof(string), * %s wyrzuci≥ %d oczek na 6., PlayerName(playerid), rand)
		ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_CLOTH)
	(
		if(!ItemInfo(itemid)(iValue1))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ tego przedmiotu., OK, )
			return 1
		)
		hrp_SetPlayerSkin(playerid, ItemInfo(itemid)(iValue1))
   		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_PAINT)
	(
		type = ItemInfo(itemid)(iValue1),
			ammo = ItemInfo(itemid)(iValue2)
	
 		if(IsPlayerInAnyVehicle(playerid) && !ItemInfo(itemid)(iUsed))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz wyjπÊ broni w pojeüdzie., OK, )
	 		return 0
		)
		if(ItemInfo(itemid)(iValue2) (= 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Amunicja w tej broni jest kompletnie wyczerpana., OK, )
	 		return 0
		)
		if(!strfind(ItemInfo(itemid)(iName), (F), true))
		(
			if(!IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI) && !IsPlayerInGroupType(playerid, GROUP_ARMY))
			(
   				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta broÒ jest oflagowana, uøywaÊ jej mogπ tylko i wy≥πcznie organizacje porzπdkowe., OK, )
				return 0
			)
		)
		if(!strfind(ItemInfo(itemid)(iName), (G), true))
		(
			if(!IsPlayerInGroupType(playerid, GROUP_CRIMINAL) && !IsPlayerInGroupType(playerid, GROUP_MAFIA) && !IsPlayerInGroupType(playerid, GROUP_CARTEL) && !IsPlayerInGroupType(playerid, GROUP_DEALERS) && !IsPlayerInGroupType(playerid, GROUP_PRISON) && !IsPlayerInGroupType(playerid, GROUP_RACERS))
			(
   				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta broÒ jest oflagowana, uøywaÊ jej mogπ tylko i wy≥πcznie organizacje porzπdkowe., OK, )
				return 0
			)
		)
		
		if(!ItemInfo(itemid)(iUsed))
		(
			ItemInfo(itemid)(iUsed) = 1
			mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))

			WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) = ItemInfo(itemid)(iUID)				
			WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) = type
			WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo) = ammo
			WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo)
			
			GivePlayerWeapon(playerid, type, ammo)
			
			WeaponCache(playerid)(WEAPON_FUNC)(pEquipped) = true
		)
		else
		(
			if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
			(
				ItemInfo(itemid)(iUsed) = 0
				ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo)
				
				mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
			
				SetPlayerAmmo(playerid, WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID), 0)
			
				WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) = 0
				WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) = 0
				WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo) = 0
				WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = 0
				WeaponCache(playerid)(WEAPON_FUNC)(pShot) = false
				
				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_FUNC))
				(
					RemovePlayerAttachedObject(playerid, SLOT_WEAPON_FUNC)
				)
			)
			else
			(
				ItemInfo(itemid)(iUsed) = 0
				mysql_query_format(UPDATE hrp_items SET item_used = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUID))
			)
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_WEAPON)
	(
		type = ItemInfo(itemid)(iValue1),
			ammo = ItemInfo(itemid)(iValue2)
		
		if(PlayerCache(playerid)(pGamePoints) ( 100 && PlayerCache(playerid)(pPremiumTime) ( gettime())
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta postaÊ nie ma jeszcze 100GS i dlatego nie pozwalamy jej uøywaÊ broni.\nNie martw siÍ, TwÛja giwera dalej naleøy do Ciebie i bÍdziesz mÛg≥ jπ uøywaÊ po przegraniu 5 godzin., OK, )
			return 0
		)
		if(PlayerCache(playerid)(pWeaponCheckFreeze))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz teraz wyjπc ani schowaÊ broni., OK, )
	 		return 0
		)
		
		if(IsPlayerInAnyVehicle(playerid) && !ItemInfo(itemid)(iUsed))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz wyjπÊ broni w pojeüdzie., OK, )
	 		return 0
		)
		
		// Sprawdzanie wyczerpanej amunicji
		if(type ) 15 && type ( 44)
		(
			if(ammo (= 0 )
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Amunicja w tej broni jest kompletnie wyczerpana., OK, )
				return 0
			)
		)
		
		// Sprawdzanie oflagowania broni
		if(!strfind(ItemInfo(itemid)(iName), (D), true))
		(
			//jest to flaga ktÛra po zescrollowaniu broni jest niewidoczna
			if(!IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI) && !IsPlayerInGroupType(playerid, GROUP_ARMY))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta broÒ jest oflagowana, uøywaÊ jej mogπ tylko i wy≥πcznie organizacje porzπdkowe., OK, )
				return 0
			)
		)
		if(!strfind(ItemInfo(itemid)(iName), (W), true))
		(
			if(!IsPlayerInGroupType(playerid, GROUP_ARMY))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta broÒ jest oflagowana, uøywaÊ jej mogπ tylko i wy≥πcznie øo≥nierze., OK, )
				return 0
			)
		)
		if(!strfind(ItemInfo(itemid)(iName), (H), true))
		(
			//flaga dla grupy hardcore
			if(!IsPlayerInGroupType(playerid, GROUP_HARDCORE))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta broÒ jest oflagowana, uøywaÊ jej mogπ tylko i wy≥πcznie organizacje typu hardcore., OK, )
				return 0
			)
		)
		if(!strfind(ItemInfo(itemid)(iName), (F), true))
		(
			if(!IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI) && !IsPlayerInGroupType(playerid, GROUP_ARMY))
			(
   				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta broÒ jest oflagowana, uøywaÊ jej mogπ tylko i wy≥πcznie organizacje porzπdkowe., OK, )
				return 0
			)
		)
		if(!strfind(ItemInfo(itemid)(iName), (G), true))
		(
			if(!IsPlayerInGroupType(playerid, GROUP_CRIMINAL) && !IsPlayerInGroupType(playerid, GROUP_MAFIA) && !IsPlayerInGroupType(playerid, GROUP_CARTEL) && !IsPlayerInGroupType(playerid, GROUP_DEALERS) && !IsPlayerInGroupType(playerid, GROUP_PRISON) && !IsPlayerInGroupType(playerid, GROUP_RACERS))
			(
   				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta broÒ jest oflagowana, uøywaÊ jej mogπ tylko i wy≥πcznie organizacje porzπdkowe., OK, )
				return 0
			)
		)
		if(!strfind(ItemInfo(itemid)(iName), (PB), true))
		(
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID || !DoorData(doorid)(dPaintball))
			(
   				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta broÒ to karabin paintballowy, uøywaÊ jej mogπ tylko i wy≥πcznie osoby na hali do paintballa., OK, )
				return 0
			)
		)
		if(strfind(ItemInfo(itemid)(iName), (PB), true))
		(
			doorid = GetPlayerDoorID(playerid)
			if(doorid != INVALID_DOOR_ID && DoorData(doorid)(dPaintball))
			(
   				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Jesteú na hali do paintballa, nie moøesz uøyÊ broni z normalnπ amunicjπ., OK, )
				return 0
			)
		)
		// Rozbicie na typy broni
		if((type ) 0 && type ( 19) || type ) 38)
		(
			// BroÒ funkcjonalna
			if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
			(
				if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) != ItemInfo(itemid)(iUID))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Najpierw schowaj obecnπ broÒ, aby mÛc wyjπÊ drugπ., OK, )
					return 0	
				)
			)
			
			if(!ItemInfo(itemid)(iUsed))
			(
				ItemInfo(itemid)(iUsed) = 1
				mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))

				WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) = ItemInfo(itemid)(iUID)				
				WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) = type
				WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo) = ammo
				WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo)
				
				GivePlayerWeapon(playerid, type, ammo)
				
				WeaponCache(playerid)(WEAPON_FUNC)(pEquipped) = true
			)
			else
			(
				if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
				(
					ItemInfo(itemid)(iUsed) = 0
					ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo)
					
					mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
				
					//SetPlayerAmmo(playerid, GetPlayerWeaponSlot(playerid, WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID)), 0)
					//SetPlayerAmmo(playerid, WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID), 0)
					
					ResetPlayerWeapons(playerid)
					GivePlayerWeapon(playerid, WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID), WeaponCache(playerid)(WEAPON_MAIN)(pLastAmmo)) 
					GivePlayerWeapon(playerid, WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID), WeaponCache(playerid)(WEAPON_SIDE)(pLastAmmo))
				
					WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) = 0
					WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) = 0
					WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo) = 0
					WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = 0
					
					if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_FUNC))
					(
						RemovePlayerAttachedObject(playerid, SLOT_WEAPON_FUNC)
					)
				)
				else
				(
					ItemInfo(itemid)(iUsed) = 0
					mysql_query_format(UPDATE hrp_items SET item_used = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUID))
				)
			)			
		)
		else if((type )= 22 && type (= 24) || type == 28 || type == 32)
		(
			// BroÒ poboczna
			if(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
			(
				if(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID) != ItemInfo(itemid)(iUID))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Najpierw schowaj obecnπ broÒ, aby mÛc wyjπÊ drugπ., OK, )
					return 0	
				)
			)
			
			if(!ItemInfo(itemid)(iUsed))
			(
				ItemInfo(itemid)(iUsed) = 1
				mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))

				WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID) = ItemInfo(itemid)(iUID)				
				WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID) = type
				WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo) = ammo
				WeaponCache(playerid)(WEAPON_SIDE)(pLastAmmo) = WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo)
				
				GivePlayerWeapon(playerid, type, ammo)
				
				WeaponCache(playerid)(WEAPON_SIDE)(pEquipped) = true
			)
			else
			(
				if(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
				(
					ItemInfo(itemid)(iUsed) = 0
					ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo)
					
					mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
				
					//SetPlayerAmmo(playerid, GetPlayerWeaponSlot(playerid, WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID)), 0)
					SetPlayerAmmo(playerid, WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID), 0)
				
					WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID) = 0
					WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID) = 0
					WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo) = 0
					WeaponCache(playerid)(WEAPON_SIDE)(pLastAmmo) = 0
					WeaponCache(playerid)(WEAPON_SIDE)(pShot) = false
					
					if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_SIDE))
					(
						RemovePlayerAttachedObject(playerid, SLOT_WEAPON_SIDE)
					)
				)
				else
				(
					ItemInfo(itemid)(iUsed) = 0
					mysql_query_format(UPDATE hrp_items SET item_used = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUID))
				)
			)
			
		) else (
			// BroÒ g≥Ûwna
			if(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
			(
				if(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID) != ItemInfo(itemid)(iUID))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Najpierw schowaj obecnπ broÒ, aby mÛc wyjπÊ drugπ., OK, )
					return 0	
				)
			)
			
			if(!ItemInfo(itemid)(iUsed))
			(
				ItemInfo(itemid)(iUsed) = 1
				mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))

				WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID) = ItemInfo(itemid)(iUID)				
				WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID) = type
				WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo) = ammo
				WeaponCache(playerid)(WEAPON_MAIN)(pLastAmmo) = WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo)
				
				GivePlayerWeapon(playerid, type, ammo)
				
				WeaponCache(playerid)(WEAPON_MAIN)(pEquipped) = true
			)
			else
			(
				if(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
				(
					ItemInfo(itemid)(iUsed) = 0
					ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo)
					
					mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
				
					//SetPlayerAmmo(playerid, GetPlayerWeaponSlot(playerid, WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID)), 0)
					SetPlayerAmmo(playerid, WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID), 0)
				
					WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID) = 0
					WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID) = 0
					WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo) = 0
					WeaponCache(playerid)(WEAPON_MAIN)(pLastAmmo) = 0
					WeaponCache(playerid)(WEAPON_MAIN)(pShot) = false
					
					if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_MAIN))
					(
						RemovePlayerAttachedObject(playerid, SLOT_WEAPON_MAIN)
					)
				)
				else
				(
					ItemInfo(itemid)(iUsed) = 0
					mysql_query_format(UPDATE hrp_items SET item_used = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUID))
				)
			)
		)
		
		print(============= Equip info =============)
		printf(Player: %s (%d), PlayerName(playerid), playerid)
		print(Przedmiot:)
		printf(Uid: %d, val1: %d, val2: %d, used: %d, owner: %d, place: %d, name: %s, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iOwner), ItemInfo(itemid)(iPlace), ItemInfo(itemid)(iName))
		print(============= ============= =============)
		
		// Dodaj odciski palcÛw
		if(!PlayerCache(playerid)(pGloves))
		(
			mysql_query_format(INSERT INTO hrp_fingerprints VALUES(NULL, %d, %d, %d), ItemInfo(itemid)(iUID), PlayerCache(playerid)(pUID), gettime())
		)
		
		return 1
	)	
	if(ItemInfo(itemid)(iType) == ITEM_AMMO)
	(
		if(!ItemInfo(itemid)(iValue1))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ tego przedmiotu., OK, )
			return 1
		)
		
		if(!strfind(ItemInfo(itemid)(iName), (F), true))
		(
			if(!IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI) && !IsPlayerInGroupType(playerid, GROUP_ARMY))
			(
   				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ten magazynek jest oflagowany, uøywaÊ go mogπ tylko i wy≥πcznie organizacje porzπdkowe., OK, )
				return 1
			)
		)
		
		if(!strfind(ItemInfo(itemid)(iName), (W), true))
		(
			if(!IsPlayerInGroupType(playerid, GROUP_ARMY))
			(
   				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ten magazynek jest oflagowany, uøywaÊ go mogπ tylko i wy≥πcznie wojsko, OK, )
				return 1
			)
		)
		
		data(64), list_items(256),
			item_uid, item_name(32), item_value1, item_value2

		mysql_query_format(SELECT item_uid, item_name, item_value1, item_value2 FROM hrp_items WHERE item_place = %d AND item_owner = %d AND item_type = %d AND item_value1 = %d, PLACE_PLAYER, PlayerCache(playerid)(pUID), ITEM_WEAPON, ItemInfo(itemid)(iValue1))

		mysql_store_result()
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)ds(32)dd, item_uid, item_name, item_value1, item_value2)
			format(list_items, sizeof(list_items), %s\n%d\t%d\t%d\t%s, list_items, item_uid, item_value1, item_value2, item_name)
		)
		mysql_free_result()
		if(strlen(list_items))
		(
			PlayerCache(playerid)(pManageItem) = itemid
			ShowPlayerDialog(playerid, D_ITEM_USE_AMMO, DIALOG_STYLE_LIST, DostÍpne bronie, list_items, Prze≥aduj, Anuluj)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie posiadasz øadnej broni, do ktÛrej mÛg≥byú uøyÊ tej amunicji., OK, )
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_PHONE)
	(
		if(ItemInfo(itemid)(iUsed))
		(
			PlayerCache(playerid)(pManageItem) = itemid
			cmd_tel(playerid, )
		)
		else
		(
			if(PlayerCache(playerid)(pPhoneNumber) != 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Moøesz mieÊ w≥πczony tylko jeden telefon!, OK, )
				return 1
			)
			ItemInfo(itemid)(iUsed) = 1
			
			PlayerCache(playerid)(pPhoneNumber) = ItemInfo(itemid)(iValue1)
			GameTextForPlayer(playerid, ~w~Telefon ~g~wlaczony, 4000, 6)
			
			// Skoro juø w≥πczy≥ to SMS-ki niech pobierze jeszcze - a nuø ktoú pisa≥.
			getPlayerOfflineMessages(playerid)
			
			
			mysql_query_format(UPDATE hrp_items SET item_used = 1 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUID))
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_CANISTER)
	(
		object_id = GetClosestObject(playerid)
		if(object_id != INVALID_OBJECT_ID && GetObjectModel(object_id) == OBJECT_FUELING)
		(
			price, value = 20, bens_type = ItemInfo(itemid)(iValue2)
			if(bens_type == TYPE_BENS) 			price = floatround(value * 3.5)
			else if(bens_type == TYPE_GAS) 		price = floatround(value * 1.0)
			else if(bens_type == TYPE_DIESEL) 	price = floatround(value * 2.0)
			else if(bens_type == TYPE_AIRFUEL)	price = floatround(value * 8.0)
			
			if(PlayerCache(playerid)(pCash) ( price)
			(
				format(string, sizeof(string), Nie posiadasz $%d aby zatankowaÊ kanister., price)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, string, OK, )
				return 1
			)
			
			hrp_GivePlayerMoney(playerid, -price)
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			ItemInfo(itemid)(iValue1) = value
			mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
		
			format(string, sizeof(string), * %s tankuje kanister., PlayerName(playerid))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE, true)

			ApplyAnimation(playerid,INT_HOUSE,wash_up,4.1,0,0,0,0,0,1)
		)
		else
		(
			vehid = GetClosestVehicle(playerid)
			if(vehid == INVALID_VEHICLE_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znaleziono øadnego pojazdu w pobliøu., OK, )
				return 1
			)
			max_fuel = GetVehicleMaxFuel(CarInfo(vehid)(cModel))
			if(floatround(CarInfo(vehid)(cFuel)) == max_fuel)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ten pojazd ma pe≥ny bak paliwa., OK, )
				return 1
			)
			if(CarInfo(vehid)(cFuelType) != ItemInfo(itemid)(iValue2))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Rodzaj paliwa w kanistrze nie pasuje do tego w pojeüdzie., OK, )
				return 1
			)
			if(!ItemInfo(itemid)(iValue1))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Kanister jest ca≥kowicie pusty., OK, )
				return 1
			)
			if(CarInfo(vehid)(cFuel) + ItemInfo(itemid)(iValue1) (= max_fuel)
			(
				item_fuel = ItemInfo(itemid)(iValue1), Float:Refuel = floatround(CarInfo(vehid)(cFuel)) + item_fuel
				CarInfo(vehid)(cFuel) = Refuel
				
				ItemInfo(itemid)(iValue1) = 0
				mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))

				format(string, sizeof(string), Pojazd %s zosta≥ pomyúlnie zatankowany.\nZatankowano %d litrÛw paliwa., CarInfo(vehid)(cName), item_fuel)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
			)
			else
			(
				needfuel = max_fuel - floatround(CarInfo(vehid)(cFuel))
				
				Float:Refuel = floatround(CarInfo(vehid)(cFuel)) + needfuel
				CarInfo(vehid)(cFuel) = Refuel
				
				ItemInfo(itemid)(iValue1) = ItemInfo(itemid)(iValue1) - needfuel				
				mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
				
				format(string, sizeof(string), Pojazd %s zosta≥ pomyúlnie zatankowany.\nZatankowano %d litrÛw paliwa., CarInfo(vehid)(cName), needfuel)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
			)
			format(string, sizeof(string), * %s tankuje pojazd %s kanistrem., PlayerName(playerid), CarInfo(vehid)(cName))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE, true)

			ApplyAnimation(playerid,INT_HOUSE,wash_up,4.1,0,0,0,0,0,1)

			SaveVehicle(vehid, SAVE_VEH_COUNT)
		)
		
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_MASK)
	(
		name(MAX_PLAYER_NAME)
		if(!ItemInfo(itemid)(iUsed))
		(
			ItemInfo(itemid)(iUsed) = 1
			PlayerCache(playerid)(pMaskUID) = ItemInfo(itemid)(iUID)
			
	 		format(string, sizeof(string), * %s zak≥ada przedmiot %s na twarz., PlayerName(playerid), ItemInfo(itemid)(iName))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE, true)

			format(name, sizeof(name), Nieznajomy_%s, CharCode(playerid))
			strmid(PlayerCache(playerid)(pName), name, 0, strlen(name), 32)
			
			format(string, sizeof(string), %s%s, PlayerName(playerid), GetPlayerStatusInfo(playerid))
			Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
		)
		else
		(
			ItemInfo(itemid)(iUsed) = 0
			PlayerCache(playerid)(pMaskUID) = 0
			
			format(string, sizeof(string), * %s zdejmuje z twarzy przedmiot %s., PlayerName(playerid), ItemInfo(itemid)(iName))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE, true)

			GetPlayerName(playerid, name, sizeof(name))
			strmid(PlayerCache(playerid)(pName), name, 0, strlen(name), 32)

			format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
			Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_HANDCUFFS)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Aby uøyÊ tego przedmiotu, skorzystaj z komendy /skuj., OK, )
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_MEGAPHONE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Aby uøyÊ tego przedmiotu, skorzystaj z komendy /m., OK, )
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_LINE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Aby uøyÊ tego przedmiotu, zaoferuj komuú holowanie., OK, )
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_BEDBUG)
	(
		
	)
	if(ItemInfo(itemid)(iType) == ITEM_NOTEBOOK)
	(
		if(ItemInfo(itemid)(iValue1) ) 0)
		(
			PlayerCache(playerid)(pManageItem) = itemid
			ShowPlayerDialog(playerid, D_ADD_CHIT, DIALOG_STYLE_INPUT, Karteczka, Wpisz treúÊ, ktÛra bÍdzie widnieÊ na karteczce.\nWpisanπ treúÊ bÍdzie mÛg≥ ujrzeÊ kaødy kto uøyje karteczki., OK, Anuluj)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, W tym notesie brakuje kartek., OK, )
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_CHIT)
	(
		data(256),
			chit_uid, chit_desc(128), chit_writer(24), chit_datetime(24)
			
		mysql_query_format(SELECT * FROM hrp_chits WHERE chit_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1))
		
		mysql_store_result()
		if(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)ds(128)s(24)s(24), chit_uid, chit_desc, chit_writer, chit_datetime)
			
			format(string, sizeof(string), %s\n\n%s,\n%s, DescWrap(chit_desc), chit_writer, chit_datetime)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, ItemInfo(itemid)(iName), string, OK, )
		)
		mysql_free_result()
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_CHECKBOOK)
	(
		if(PlayerCache(playerid)(pGamePoints) ( 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz wypisaÊ czeku, dopÛki nie zdobedziesz 100GS., OK, )
			return 1
		)
		if(ItemInfo(itemid)(iValue1) ) 0)
		(
			PlayerCache(playerid)(pManageItem) = itemid
			ShowPlayerDialog(playerid, D_WRITE_A_CHECK, DIALOG_STYLE_INPUT, Wypisz czek, Wprowadü kwotÍ jakπ chcesz wypisaÊ na czeku.\nKwota jakπ wpiszesz, zostanie pobrana z Twojego konta bankowego., Wypisz, Anuluj)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Wszystkie czeki zosta≥y wykorzystane., OK, )
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_CHECK)
	(
		if(PlayerCache(playerid)(pAdmin) == 0)
		(
			GuiMsg(playerid, Ten typ przedmiotu nie jest juø uøywany., 1)
			return 1
		)
		
		if(PlayerCache(playerid)(pGamePoints) ( 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz zrealizowaÊ czeku, dopÛki nie bedziesz mial 100GS., OK, )
			return 1
		)
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znajdujesz siÍ w banku., OK, )
			return 1
		)
	 	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
	  	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znajdujesz siÍ w banku., OK, )
	   		return 1
	   	)
	   	group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
	   	if(GroupData(group_id_fix)(gType) != GROUP_BANK)
	   	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znajdujesz siÍ w banku., OK, )
	   		return 1
	   	)
		if(!PlayerCache(playerid)(pBankNumber))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie posiadasz konta bankowego, za≥Ûø je., OK, )
			return 1
		)
		PlayerCache(playerid)(pBankCash) += ItemInfo(itemid)(iValue1)
		SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
		
		format(string, sizeof(string), * %s realizuje czek na $%d., PlayerName(playerid), ItemInfo(itemid)(iValue1))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE, false)
		
		format(string, sizeof(string), Czek zosta≥ pomyúlnie zrealizowany.\nNa Twoje konto bankowe przelano $%d.\n\nAktualny stan konta: $%d, ItemInfo(itemid)(iValue1), PlayerCache(playerid)(pBankCash))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		DeleteItem(ItemInfo(itemid)(iUID))
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_FISHING)
	(
		if(PlayerCache(playerid)(pDailyIncome) ) MAX_DAILY_INCOME && !IsPlayerInGroupType(playerid, GROUP_FISHING))
		(
			GuiMsg(playerid, Wyczerpa≥eú dzisiejszy limit dochodu z prac dorywczych.\nWrÛÊ jutro., 1)
			return 1
		)
		
		// Dodaj wyjπtek jeúli jest na ≥odzi
		bool:canUse = false
		cvehID = GetClosestVehicle(playerid, 10.0)
		
		if(IsVehicleBoat(cvehID))
			canUse = true
		
		if(!canUse)
		(
			if(!IsPlayerInRangeOfPoint(playerid, 15.0, 380.1618, -2096.8606, 7.8359) && 
			!IsPlayerInRangeOfPoint(playerid, 15.0, 526.4686,-1938.0804,2.4405) &&
			!IsPlayerInRangeOfPoint(playerid, 15.0, 561.6442,-1936.8746,2.4405) &&
			!IsPlayerInRangeOfPoint(playerid, 15.0, 544.5582,-1948.4175,3.2605))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znajdujesz siÍ na miejscu ≥owieckim., OK, )
				return 1
			)
		)
		
		if(!ItemInfo(itemid)(iUsed))
		(
			ItemInfo(itemid)(iUsed) = 1
			PlayerCache(playerid)(pFishingRodUID) = ItemInfo(itemid)(iUID)

			PlayerCache(playerid)(pFish) = true
			
   			if(!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_FISHING_ROD))
			(
				SetPlayerAttachedObject(playerid, SLOT_FISHING_ROD, 18632, 6, 0.079376, 0.037070, 0.007706, 181.482910, 0.0, 0.0, 1.0, 1.0, 1.0)
			)
			ApplyAnimation(playerid, CAMERA, camstnd_lkabt, 4.1, 0, 0, 0, 1, 0, 1)
			
			TextDrawSetString(Text:TextDrawMainInfo(playerid), Proces polowu ~b~~h~ryb ~w~w toku.~n~Odczekaj kilka chwil na zdobycz.)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
		)
		else
		(
  			ItemInfo(itemid)(iUsed) = 0
			PlayerCache(playerid)(pFishingRodUID) = 0

			PlayerCache(playerid)(pFish) = false
			
   			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_FISHING_ROD))
			(
				RemovePlayerAttachedObject(playerid, SLOT_FISHING_ROD)
			)
			ApplyAnimation(playerid, CARRY, crry_prtial, 4.1, 0, 0, 0, 0, 0)
			TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_BAG)
	(
 		data(32), list_items(256),
 			item_uid, item_name(32)

		mysql_query_format(SELECT item_uid, item_name FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_BAG, ItemInfo(itemid)(iUID))

		mysql_store_result()
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)ds(32), item_uid, item_name)
			format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, item_uid, item_name)
		)
		mysql_free_result()
		if(strlen(list_items))
		(
			ShowPlayerDialog(playerid, D_REMOVE_ITEM_BAG, DIALOG_STYLE_LIST, Znaleziono przedmioty:, list_items, Wyjmij, Anuluj)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znaleziono øadnych przedmiotÛw., OK, )
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_DRINK)
	(
		SetPlayerSpecialAction(playerid, ItemInfo(itemid)(iValue1))
		DeleteItem(ItemInfo(itemid)(iUID))
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_DRUG)
	(
		list_items(256), Float:health
		GetPlayerHealth(playerid, health)
		
		if(PlayerCache(playerid)(pRage))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Jesteú juø pod wp≥ywem jednego narkotyku. Kolejny da Ci FCK - chcesz tego ?, OK, )
			return 1
		)
		if(PlayerCache(playerid)(pWounded))
		(		
			DeleteItem(ItemInfo(itemid)(iUID))
			
			if(PlayerCache(playerid)(pArrest))
			(
				PlayerCache(playerid)(pBW) = 15 * 60
			)
			else
			(
				PlayerCache(playerid)(pBW) = 30 * 60
			)

			GetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

			PlayerCache(playerid)(pInt) = GetPlayerInterior(playerid)
			PlayerCache(playerid)(pVW) = GetPlayerVirtualWorld(playerid)
			
			SetPlayerCameraPos(playerid, PlayerCache(playerid)(pPosX) + 3, PlayerCache(playerid)(pPosY) + 4, PlayerCache(playerid)(pPosZ) + 7)
			SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

			hrp_TogglePlayerControllable(playerid, 0)

			SavePlayerStats(playerid, SAVE_PLAYER_POS)
		
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Upssss, Zaøy≥eú narkotyku w stanie tragicznego os≥abienia organizmu. èle siÍ to skoÒczy≥o., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pGymType) != TRAIN_NONE)
		(
			OnPlayerGymTrainStopped(playerid)
		)
		
		MainPlayerTable(playerid) = itemid
		switch(ItemInfo(itemid)(iValue1))
		(
			case DRUG_MARIHUANA:
			(
				foreach(Items, i)
				(
					if(ItemInfo(i)(iUID))
					(
						if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
						(
							if(ItemInfo(i)(iType) == ITEM_BLET || ItemInfo(i)(iType) == ITEM_BONGOS)
							(
								format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, ItemInfo(i)(iUID), ItemInfo(i)(iName))
							)
						)
					)
				)
				if(strlen(list_items))
				(
					ShowPlayerDialog(playerid, D_SELECT_DRUG_USE, DIALOG_STYLE_LIST, Wybierz uøywkÍ:, list_items, Wybierz, Anuluj)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znaleziono øadnych przedmiotÛw, ktÛrych moøesz uøyÊ., OK, )
				)
				
			)
			case DRUG_COCAINE:
			(
				ShowPlayerDialog(playerid, D_TYPE_COCAINE_USE, DIALOG_STYLE_LIST, Wybierz formÍ zaøycia narkotyku:, 1 - Wcieraj w dziπs≥a\n2 - Wziewnie do nosa\n3 - Øucie, Wybierz, Anuluj)
			)
			case DRUG_HEROIN:
			(
				ShowPlayerDialog(playerid, D_TYPE_HEROIN_USE, DIALOG_STYLE_LIST, Wybierz formÍ zaøycia narkotyku:, 1 - Wciπganie\n2 - Palenie\n3 - Doøylnie, Wybierz, Anuluj)
			)
			case DRUG_AMPHETAMINE:
			(
				ShowPlayerDialog(playerid, D_TYPE_AMPHETAMINE_USE, DIALOG_STYLE_LIST, Wybierz formÍ zaøycia narkotyku:, 1 - Palenie\n2 - Wziewnie do nosa\n3 - Doøylnie, Wybierz, Anuluj)
			)
			case DRUG_CRACK:
			(				
				DeleteItem(ItemInfo(itemid)(iUID))
				
				PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_SMOKE
				PlayerCache(playerid)(pRageStrength) = PlayerCache(playerid)(pStrength)
				PlayerCache(playerid)(pRageDrug) = DRUG_CRACK
				PlayerCache(playerid)(pDrugLevel) += 200

				PlayerCache(playerid)(pRage) = true
				PlayerCache(playerid)(pRageTime) = 900
				PlayerCache(playerid)(pStrength) += 35.0
				
				if(PlayerCache(playerid)(pDependence) ( 500)
				(
					PlayerCache(playerid)(pDependence) += 32.3
				)
				else
				(
					PlayerCache(playerid)(pDependence) += 17.3
				)

				format(string, sizeof(string), * %s zaøywa %s., PlayerName(playerid), ItemInfo(itemid)(iName))
				FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postaÊ czuje siÍ bardziej pobudzona.\n\nPrzez jakiú czas bÍdziesz zadawaÊ wiÍksze obraøenia., OK, )
			)
			case DRUG_LSD:
			(
				ShowPlayerDialog(playerid, D_TYPE_LSD_USE, DIALOG_STYLE_LIST, Wybierz formÍ zaøycia narkotyku:, 1 - Papierek pod jÍzyk\n2 - RoztwÛr, Wybierz, Anuluj)
			)
			case DRUG_SHROOMS:
			(
				DeleteItem(ItemInfo(itemid)(iUID))

				PlayerCache(playerid)(pRage) = true
				PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_GUMS
				PlayerCache(playerid)(pRageStrength) = PlayerCache(playerid)(pStrength)
				PlayerCache(playerid)(pRageDrug) = DRUG_SHROOMS
				PlayerCache(playerid)(pDrugLevel) += 100

				PlayerCache(playerid)(pRageTime) = 900
				
				SetPlayerWeather(playerid, -66)

				format(string, sizeof(string), * %s zaøywa %s., PlayerName(playerid), ItemInfo(itemid)(iName))
				FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postaÊ zaczyna czuÊ efekty dzia≥ania narkotyku.\nInformacje o dzia≥aniu konkretnego narkotyku znajdziesz na naszym forum., OK, )
			)
			case DRUG_MDMA:
			(				
				DeleteItem(ItemInfo(itemid)(iUID))
				
				PlayerCache(playerid)(pRage) = true
				PlayerCache(playerid)(pRageDrugUse) = DRUG_USE_GUMS
				PlayerCache(playerid)(pRageStrength) = PlayerCache(playerid)(pStrength)
				PlayerCache(playerid)(pRageDrug) = DRUG_MDMA
				PlayerCache(playerid)(pDrugLevel) += 100

				PlayerCache(playerid)(pRageTime) = 900

				format(string, sizeof(string), * %s zaøywa %s., PlayerName(playerid), ItemInfo(itemid)(iName))
				FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postaÊ czuje siÍ bardziej pobudzona., OK, )
			)
			case DRUG_METAAMP:
			(
				ShowPlayerDialog(playerid, D_TYPE_METAAMP_USE, DIALOG_STYLE_LIST, Wybierz formÍ zaøycia narkotyku:, 1 - Palenie\n2 - Wziewnie do nosa\n3 - Doøylnie, Wybierz, Anuluj)
			)
		)
		
		// Zabierz przytomnoúÊ od przedawkowania
		if(PlayerCache(playerid)(pDrugLevel) )= 900)
		(
			if(PlayerCache(playerid)(pArrest))
			(
				PlayerCache(playerid)(pBW) = 10 * 60
			) else (
				PlayerCache(playerid)(pBW) = 20 * 60
			)
			GetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

			PlayerCache(playerid)(pInt) = GetPlayerInterior(playerid)
			PlayerCache(playerid)(pVW) = GetPlayerVirtualWorld(playerid)

			SetPlayerCameraPos(playerid, PlayerCache(playerid)(pPosX) + 3, PlayerCache(playerid)(pPosY) + 4, PlayerCache(playerid)(pPosZ) + 7)
			SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

			hrp_TogglePlayerControllable(playerid, 0)
			SavePlayerStats(playerid, SAVE_PLAYER_POS)

			TextDrawSetString(Text:TextDrawMainInfo(playerid), Na wskutek ~r~przedawkowania ~w~narkotyku utraciles przytomnosc.)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

			PlayerCache(playerid)(pShowInfoText) = 5
		)

		PlayerCache(playerid)(pInt) = GetPlayerInterior(playerid)
		PlayerCache(playerid)(pVW) = GetPlayerVirtualWorld(playerid)
		GetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))
			
		
		
		/*
		case DRUG_MEDICINE:
		(
			if(PlayerCache(playerid)(pHealth) + ItemInfo(itemid)(iValue2) (= 100)
			(
				Float:health
				GetPlayerHealth(playerid, health)
				hrp_SetPlayerHealth(playerid, health + ItemInfo(itemid)(iValue2))
			)
			else
			(
				hrp_SetPlayerHealth(playerid, 100)
			)

			format(string, sizeof(string), * %s zaøywa \%s\., PlayerName(playerid), ItemInfo(itemid)(iName))
			ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)

			DeleteItem(ItemInfo(itemid)(iUID))
		)*/

		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_JOINT || ItemInfo(itemid)(iType) == ITEM_BONGOS)
	(
		PlayerCache(playerid)(pRage) = true
		PlayerCache(playerid)(pRageTime) = 600
		PlayerCache(playerid)(pRageStrength) = PlayerCache(playerid)(pStrength)
		PlayerCache(playerid)(pRageDrug) = DRUG_MARIHUANA
	
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY)
		
		if(ItemInfo(itemid)(iType) == ITEM_BONGOS)
		(
			ItemInfo(itemid)(iValue1)--
		)
		else
		(
			DeleteItem(ItemInfo(itemid)(iUID))
		)
		
		PlayerCache(playerid)(pSmokeJoint) = true
		PlayerCache(playerid)(pSmokeReps) = 25
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_ATTACH)
	(
		// sprawdzenie czy fryzura i przerywanie jeúli jest fryzurπ a nie jest u fryzjera
		if(isItemIsHaircut(itemid))
		(
			if( GetPlayerVirtualWorld(playerid) == 0)
			(
				GuiMsg(playerid, Musisz znajdowaÊ siÍ w budynku fryzjera, by edytowaÊ ten przedmiot., 1)
				return 1
			)
			
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Musisz znajdowaÊ siÍ w budynku fryzjera., OK, )
				return 1
			)
			
			if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Musisz znajdowaÊ siÍ w budynku fryzjera., OK, )
				return 1
			)
			
			group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
			if(GroupData(group_id_fix)(gType) != GROUP_CLOTHES)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Musisz znajdowaÊ siÍ w budynku fryzjera., OK, )
				return 1
			)
		)
		
		
		if(!ItemInfo(itemid)(iUsed))
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_TRYING))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ tego przedmiotu w tym momencie., OK, )
				return 1
			)
			if(!PlayerCache(playerid)(pPremium))
			(
				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_ONE))
				(
					if(PlayerCache(playerid)(pAASlot))
					(
						if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_FOUR))
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Masz juø zape≥nione wszystkie sloty udostÍpnione na akcesoria., OK, )
							return 1
						)
					) else (
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Masz juø zape≥nione wszystkie sloty udostÍpnione na akcesoria., OK, )
						return 1
					)
				)
			)
			else
			(
				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_ONE) && IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_TWO) && IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_THREE))
				(
					if(PlayerCache(playerid)(pAASlot))
					(
						if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_FOUR))
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Masz juø zape≥nione wszystkie sloty udostÍpnione na akcesoria., OK, )
							return 1
						)
					) else (
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Masz juø zape≥nione wszystkie sloty udostÍpnione na akcesoria., OK, )
						return 1
					)
				)
			)
			
			if(!strfind(ItemInfo(itemid)(iName), (B), true))
			(
				name(32)
				
				PlayerCache(playerid)(pMaskUID) = ItemInfo(itemid)(iUID)
				
				format(name, sizeof(name), Nieznajomy_%s, CharCode(playerid))
				strmid(PlayerCache(playerid)(pName), name, 0, strlen(name), 32)
				
				format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
				Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
			)
			
			PlayerCache(playerid)(pManageItem) = itemid
			ShowPlayerDialog(playerid, D_ACCESS_APPLY, DIALOG_STYLE_MSGBOX, Akcesorie, Wybierz poniøej, jak chcia≥byú zastosowaÊ przedmiot:, Za≥Ûø, Edytuj)
			return 1
		)
		else
		(
			ItemInfo(itemid)(iUsed) = 0
			
			if(!strfind(ItemInfo(itemid)(iName), (B), true))
			(
				name(32)
				PlayerCache(playerid)(pMaskUID) = 0
				GetPlayerName(playerid, name, sizeof(name))
				strmid(PlayerCache(playerid)(pName), name, 0, strlen(name), 32)
				
				format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
				Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
			)
			
			RemovePlayerAttachedObject(playerid, SLOT_ACCESS_ONE)
			RemovePlayerAttachedObject(playerid, SLOT_ACCESS_TWO)
			
			if(PlayerCache(playerid)(pPremium))
			(
				RemovePlayerAttachedObject(playerid, SLOT_ACCESS_THREE)
			)

			if(PlayerCache(playerid)(pAASlot)) (
				RemovePlayerAttachedObject(playerid, SLOT_ACCESS_FOUR)
			)

			mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
			LoadPlayerAccess(playerid)
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_PLATE)
	(
		if(ItemInfo(itemid)(iValue1))
		(
			if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			(
				vehid = GetPlayerVehicleID(playerid)
				if(!(CarInfo(vehid)(cAccess) & VEH_ACCESS_AUDIO))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, W tym pojeüdzie nie ma zamontowanego sprzÍtu audio., OK, )
					return 1
				)
				
				data(128), audio_url(128)
				mysql_query_format(SELECT audio_url FROM hrp_audiourls WHERE audio_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1))
				
				mysql_store_result()
				if(mysql_fetch_row(data, |))
				(
					sscanf(data, p(|)s(128), audio_url)
					strmid(CarInfo(vehid)(cAudioURL), audio_url, 0, strlen(audio_url), 64)
					
					// Za≥πcz muzÍ u wszystkich, nie tylko u siebie
					foreach(Player, i)
					(
						if(Logged(i) && Spawned(i))
						(
							if(IsPlayerInAnyVehicle(i))
							(
								if(GetPlayerVehicleID(i) == vehid)
								(
									if(PlayerCache(i)(pAudioHandle))
									(
										//Audio_Stop(i, PlayerCache(i)(pAudioHandle))
										PlayerCache(i)(pAudioHandle) = 0
										StopAudioStreamForPlayer(i)
									)
									//Audio_StopRadio(i)
									//PlayerCache(i)(pAudioHandle) = Audio_PlayStreamed(i, CarInfo(vehid)(cAudioURL))
									PlayerCache(i)(pAudioHandle) = 1
									PlayAudioStreamForPlayer(i, CarInfo(vehid)(cAudioURL))
								)
							)
						)
					)
				)
				mysql_free_result()
				
				format(string, sizeof(string), * %s umieszcza p≥ytÍ w radiu., PlayerName(playerid))
				FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
				
				//format(string, sizeof(string), ((PamiÍtaj, øe aby s≥yszeÊ muzykÍ poza pojazdem, klapa bagaønika musi byÊ otwarta a pojazd zapalony.)))
				//SendClientMessage(playerid, COLOR_GREY, string)
				
   				TextDrawSetString(Text:TextDrawMainInfo(playerid), ~y~Plyta ~w~zostala umieszczona w ~r~radiu ~w~samochodowym pomyslnie.)
				TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

				PlayerCache(playerid)(pShowInfoText) = 5
			   	return 1
			)
			else
			(
				data(64), item_uid, item_name(32),
					list_items(256)
					
				PlayerCache(playerid)(pManageItem) = itemid

				mysql_query_format(SELECT item_uid, item_name FROM hrp_items WHERE item_place = %d AND item_owner = %d AND item_type = %d, PLACE_PLAYER, PlayerCache(playerid)(pUID), ITEM_PLAYER)
				
				mysql_store_result()
				while(mysql_fetch_row(data, |))
				(
					sscanf(data, p(|)ds(32), item_uid, item_name)
					format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, item_uid, item_name)
				)
				mysql_free_result()
				
				if(strlen(list_items))
				(
					ShowPlayerDialog(playerid, D_INSERT_DISC, DIALOG_STYLE_LIST, Wybierz odtwarzacz, list_items, Wybierz, Anuluj)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie posiadasz øadnych odtwarzaczy w ekwipunku., OK, )
					PlayerCache(playerid)(pManageItem) = 0
				)
			)
		)
		else
		(
			PlayerCache(playerid)(pManageItem) = itemid
			printf((debug) PlayerCache(playerid)(pManageItem) = %d, PlayerCache(playerid)(pManageItem))
			ShowPlayerDialog(playerid, D_RECORD_DISC, DIALOG_STYLE_INPUT, Nagrywanie p≥yty, To jest czysta p≥yta, na ktÛrej moøesz nagraÊ dowolny kawa≥ek.\nWklej w pole tekstowe poniøej link do muzyki, ktÛra ma byÊ odtwarzana poprzez urzπdzenia.\n\nUpewnij siÍ, øe link jest poprawny w innym wypadku muzyka moøe nie byÊ s≥yszalna.\n\nD≥ugoúÊ linku nie moøe przekroczyÊ 64 znakÛw., Nagraj, Anuluj)
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_PLAYER)
	(
		if(!ItemInfo(itemid)(iValue1))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, W tym odtwarzaczu nie ma øadnej p≥yty., OK, )
			return 1
		)
		if(IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz siedzieÊ w pojeüdzie., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pMusicPlayerUID))
		(
			if(PlayerCache(playerid)(pMusicPlayerUID) != ItemInfo(itemid)(iUID))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Uøywasz juø jakiegoú odtwarzacza., OK, )
				return 1
			)
		)
		if(ItemInfo(itemid)(iUsed))
		(
			if(PlayerCache(playerid)(pAudioHandle))
			(
				//Audio_Stop(playerid, PlayerCache(playerid)(pAudioHandle))
				PlayerCache(playerid)(pAudioHandle) = 0
				StopAudioStreamForPlayer(playerid)
			)
			PlayerCache(playerid)(pMusicPlayerUID) = 0
			ItemInfo(itemid)(iUsed) = 0
			
			TextDrawSetString(Text:TextDrawMainInfo(playerid), ~y~Odtwarzanie ~w~muzyki zostalo pomyslnie ~r~zakonczone~w~.)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

			PlayerCache(playerid)(pShowInfoText) = 5
		)
		else
		(
			if(PlayerCache(playerid)(pAudioHandle))
			(
				PlayerCache(playerid)(pAudioHandle) = 0
				StopAudioStreamForPlayer(playerid)
			)
			PlayerCache(playerid)(pMusicPlayerUID) = ItemInfo(itemid)(iUID)
			ItemInfo(itemid)(iUsed) = 1
			
   			data(128), audio_url(128)
			mysql_query_format(SELECT audio_url FROM hrp_audiourls WHERE audio_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1))

			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
   				sscanf(data, p(|)s(128), audio_url)
				//PlayerCache(playerid)(pAudioHandle) = Audio_PlayStreamed(playerid, audio_url)
				PlayerCache(playerid)(pAudioHandle) = 1
				PlayAudioStreamForPlayer(playerid, audio_url)
			)
			mysql_free_result()
			
   			TextDrawSetString(Text:TextDrawMainInfo(playerid), ~y~Odtwarzanie ~w~muzyki zostalo pomyslnie ~g~rozpoczete~w~.)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

			PlayerCache(playerid)(pShowInfoText) = 5
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_ARMOUR)
	(
		if(!strfind(ItemInfo(itemid)(iName), (W), true))
		(
			if(!IsPlayerInGroupType(playerid, GROUP_ARMY))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ tego przedmiotu., OK, )
				return 1
			)
		)
		
		if(!strfind(ItemInfo(itemid)(iName), (C), true))
		(
			//nie sprawdzaj nic, bo to cywilna
		)
		else
		(
			if(!IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI) && !IsPlayerInGroupType(playerid, GROUP_ARMY) && !IsPlayerInGroupType(playerid, GROUP_MEDICAL) && !IsPlayerInGroupType(playerid, GROUP_FIREDEPT))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ tego przedmiotu., OK, )
				return 1
			)
		)
		if(!ItemInfo(itemid)(iValue1))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ta kamizelka jest ca≥kowicie uszkodzona, nie moøesz jej uøyÊ., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pArmour) && !ItemInfo(itemid)(iUsed))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Obecnie masz juø na sobie jednπ kamizelkÍ kuloodpornπ., OK, )
			return 1
		)
		if(!ItemInfo(itemid)(iUsed))
		(
			PlayerCache(playerid)(pArmour) = ItemInfo(itemid)(iValue1)
			PlayerCache(playerid)(pArmourDelay) = 15
			SetPlayerArmour(playerid, ItemInfo(itemid)(iValue1))
			
			// Status, poprawki
			if(ItemInfo(itemid)(iValue1) ( 100.0)
			(
				PlayerCache(playerid)(pArmorDisplay) = true
			)
			else
			(
				PlayerCache(playerid)(pArmorDisplay) = false
			)
			
			ItemInfo(itemid)(iUsed) = 1

			format(string, sizeof(string), * %s zak≥ada kamizelkÍ kuloodpornπ., PlayerName(playerid), ItemInfo(itemid)(iName))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		)
		else
		(
			ItemInfo(itemid)(iValue1) = floatround(PlayerCache(playerid)(pArmour))
			ItemInfo(itemid)(iUsed) = 0
		
			PlayerCache(playerid)(pArmour) = 0
			SetPlayerArmour(playerid, 0)
			
			// widok kamizelki
			PlayerCache(playerid)(pArmorDisplay) = false
			
   			format(string, sizeof(string), * %s zdejmuje kamizelkÍ kuloodpornπ., PlayerName(playerid), ItemInfo(itemid)(iName))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		)
		mysql_query_format(UPDATE hrp_items SET item_value1 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_GLOVES)
	(
		if(PlayerCache(playerid)(pGloves) && !ItemInfo(itemid)(iUsed))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Obecnie masz juø za≥oøone jakieú rÍkawiczki., OK, )
			return 1
		)
		if(!ItemInfo(itemid)(iUsed))
		(
			ItemInfo(itemid)(iUsed) = 1
			PlayerCache(playerid)(pGloves) = true
			
			format(string, sizeof(string), * %s zak≥ada %s na d≥onie., PlayerName(playerid), ItemInfo(itemid)(iName))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		)
		else
		(
  			ItemInfo(itemid)(iUsed) = 0
			PlayerCache(playerid)(pGloves) = false
			
			format(string, sizeof(string), * %s zdejmuje %s z d≥oni., PlayerName(playerid), ItemInfo(itemid)(iName))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		)
		mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_CORPSE)
	(
		if(!PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Aby uøyÊ tego przedmiotu, musisz byÊ na s≥uøbie grupy., OK, )
			return 1
		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_CORONER && GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_MEDICAL && GroupData(group_id_fix)(gType) != GROUP_FBI)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie posiadasz odpowiedniego doúwiadczenia, by mÛc zidentyfikowaÊ zw≥oki., OK, )
			return 1
		)
 		if(!ItemInfo(itemid)(iValue1))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Po g≥Íbszej identyfikacji cia≥a wynika, øe zosta≥o pope≥nione samobÛjstwo lub zabÛjca dobrze ukry≥ dowody zbrodni (mia≥ rÍkawiczki)., OK, )
			return 1
		)
		data(64), killer_name(32), killer_weapon(32), corpsedesc(512)
		mysql_query_format(SELECT char_name, item_name FROM hrp_characters, hrp_items WHERE char_uid = %d AND item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iValue2))
		
		mysql_store_result()
		if(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)s(32)s(32), killer_name, killer_weapon)
		)
		mysql_free_result()
		
		pos = strfind(killer_name, _, true)
		if(pos != -1)	killer_name(pos) =  
		
		if(GroupData(group_id_fix)(gType) == GROUP_FBI || GroupData(group_id_fix)(gType) == GROUP_POLICE)
		(
			format(corpsedesc, sizeof(corpsedesc), Zbierajπc dowody z cia≥a moøna stwierdziÊ, øe zabÛjcπ jest %s., killer_name)
			
			if(ItemInfo(itemid)(iValue2))
			(
				format(corpsedesc, sizeof(corpsedesc), %s\nPo g≥Íbszych badaniach cia≥a moøna wywnioskowaÊ, øe ofiara zosta≥a zabita broniπ %s (UID: %d)., corpsedesc, killer_weapon, ItemInfo(itemid)(iValue2))
			)
			else
			(
				format(corpsedesc, sizeof(corpsedesc), %s\nPo g≥Íbszych badaniach cia≥a moøna wywnioskowaÊ, øe ofiara zosta≥a zabita rÍkami., corpsedesc, killer_weapon)
			)
		)
		else if(GroupData(group_id_fix)(gType) == GROUP_MEDICAL)
		(
			if(ItemInfo(itemid)(iValue2))
			(
				format(string, sizeof(string), Po g≥Íbszych badaniach cia≥a moøna wywnioskowaÊ, øe ofiara zosta≥a zabita broniπ %s (UID: %d)., killer_weapon, ItemInfo(itemid)(iValue2))
			)
			else
			(
				format(string, sizeof(string), Po g≥Íbszych badaniach cia≥a moøna wywnioskowaÊ, øe ofiara zosta≥a zabita rÍkami., killer_weapon)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, corpsedesc, OK, )
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_ROLL)
	(
		if(!ItemInfo(itemid)(iUsed))
		(
			if(IsPlayerInAnyVehicle(playerid))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ tego przedmiotu w pojeüdzie., OK, )
				return 1
			)
			if(PlayerCache(playerid)(pRoll))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Masz juø obecnie jakieú rolki w uøyciu., OK, )
				return 1
			)
			if(GetPlayerDoorID(playerid) != INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz jeüdziÊ na rolkach wewnπtrz budynku., OK, )
				return 1
			)
			ItemInfo(itemid)(iUsed) = 1
			PlayerCache(playerid)(pRoll) = true
			
			TextDrawSetString(Text:TextDrawMainInfo(playerid), Aby rozpoczac jazde na ~b~rolkach~w~, zacznij ~g~sprintowac~w~.)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			
			PlayerCache(playerid)(pShowInfoText) = 5
		)
		else
		(
	 		ItemInfo(itemid)(iUsed) = 0
			PlayerCache(playerid)(pRoll) = false
			
			ClearAnimations(playerid, 1)
		)
		mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_PBENTRY)
	(
		if(!ItemInfo(itemid)(iUsed))
		(
			if(PlayerCache(playerid)(pWounded))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz strzelaÊ w trakcie os≥abienia organizmu., OK, )
				return 1
			)
			if(PlayerCache(playerid)(pPaintballTime))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, W chwili obecnej korzystasz juø z paintballa., OK, )
				return 1
			)
			ItemInfo(itemid)(iUsed) = 1
			
			PlayerCache(playerid)(pPaintballPass) = itemid
			PlayerCache(playerid)(pPaintballTime) = ItemInfo(itemid)(iValue1) * 60

			TextDrawSetString(Text:TextDrawMainInfo(playerid), Uzyles ~y~wejsciowki ~w~mozesz wejsc na hale do ~r~paintballa~w~.)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

			PlayerCache(playerid)(pShowInfoText) = 5
		)
		else
		(
			doorid = GetPlayerDoorID(playerid)
			if(DoorData(doorid)(dPaintball))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz przestaÊ uøywaÊ wejúciÛwki wewnπtrz hali., OK, )
				return 1
			)
			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iValue1) = PlayerCache(playerid)(pPaintballTime) / 60

			PlayerCache(playerid)(pPaintballPass) = 0
			PlayerCache(playerid)(pPaintballTime) = 0
		)
		mysql_query_format(UPDATE hrp_items SET item_used = %d, item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_PASS)
	(
		if(!ItemInfo(itemid)(iUsed))
		(
			if(PlayerCache(playerid)(pWounded))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz trenowaÊ w trakcie os≥abienia organizmu., OK, )
				return 1
			)
			if(PlayerCache(playerid)(pTrainTime))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, W chwili obecnej korzystasz juø z si≥owni., OK, )
				return 1
			)
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Musisz znajdowaÊ siÍ w budynku si≥owni, do ktÛrej naleøy karnet., OK, )
				return 1
			)
			if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Musisz znajdowaÊ siÍ w budynku si≥owni, do ktÛrej naleøy karnet., OK, )
				return 1
			)
			group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
			if(GroupData(group_id_fix)(gType) != GROUP_GYM || DoorData(doorid)(dOwner) != ItemInfo(itemid)(iValue2))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Musisz znajdowaÊ siÍ w budynku si≥owni, do ktÛrej naleøy karnet., OK, )
				return 1
			)
			ItemInfo(itemid)(iUsed) = 1
			
			PlayerCache(playerid)(pGymPass) = itemid
			PlayerCache(playerid)(pTrainTime) = ItemInfo(itemid)(iValue1) * 60

			TextDrawSetString(Text:TextDrawMainInfo(playerid), Uzyles ~y~karnetu ~w~mozesz rozpoczac ~r~trening~w~. Uzyj komendy ~g~/trenuj ~w~przy dowolnym obiekcie.)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

			PlayerCache(playerid)(pShowInfoText) = 5
		)
		else
		(
			if(PlayerCache(playerid)(pGymType) != TRAIN_NONE)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz przestaÊ uøywaÊ karnetu podczas korzystania z obiektu sportowego., OK, )
				return 1
			)
			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iValue1) = PlayerCache(playerid)(pTrainTime) / 60

			PlayerCache(playerid)(pGymPass) = 0
			PlayerCache(playerid)(pTrainTime) = 0
		)
		mysql_query_format(UPDATE hrp_items SET item_used = %d, item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_MOLOTOV)
	(
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Aby mÛc uøyÊ tego przedmiotu, musisz znajdowaÊ siÍ w budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dBurnTime))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ten budynek juø p≥onie!, OK, )
			return 1
		)
  		foreach(Doors, d)
		(
	 		if(DoorData(d)(dUID))
	   		(
		 		if(DoorData(d)(dBurnTime))
		   		(
			 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie mozesz uøyÊ tego przedmiotu teraz., OK, )
			   		return 1
				)
			)
		)
	   	firefighter_count, group_id_fix
		foreach(Player, i)
		(
	 		if(Logged(i) && Spawned(i))
	   		(
		 		if(PlayerCache(i)(pGroupDuty))
		   		(
		   			group_id_fix = GetPlayerDutyGroupID(i)
			 		if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
			   		(
				 		firefighter_count ++
				   		if(firefighter_count )= 5)
						(
							break
						)
					)
		  		)
	   		)
		)
		if(firefighter_count ( 5)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie mozesz uøyÊ tego przedmiotu teraz., OK, )
   			return 1
 		)
		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)

		DoorData(doorid)(dFireObject) = CreateDynamicObject(18690, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ) - 2.0, 0.0, 0.0, 0.0, DoorData(doorid)(dEnterVW), DoorData(doorid)(dEnterInt), -1, 100.0)
		DoorData(doorid)(dFireLabels) = CreateDynamic3DTextLabel(Ten budynek stanπ≥ w p≥omieniach!\nProcent zniszczeÒ: 0%, 0x33AA33FF, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ) + 0.3, 10.0)

		foreach(Player, i)
		(
  			if(Logged(i) && Spawned(i))
   			(
	 			if(GetPlayerDoorID(i) == doorid)
				(
		  			SendClientMessage(i, COLOR_DO, ** W tym budynku z niewiadomych przyczyn wybucha poøar. Wszyscy powinni zaczπÊ siÍ ewakuowaÊ. **)
				)
			)
		)

		// Podpal wnÍtrze!
		for(fire = 0 fire (= 20 fire++)
		(
  			if(fire (= 10)
			(
				CreateDynamicObject(18694, PosX + random(15), PosY + random(15), PosZ, random(360), random(360), random(360), DoorData(doorid)(dExitVW), DoorData(doorid)(dExitInt), -1, 100.0)
			)
			else
			(
   				CreateDynamicObject(18694, PosX - random(15), PosY - random(15), PosZ, random(360), random(360), random(360), DoorData(doorid)(dExitVW), DoorData(doorid)(dExitInt), -1, 100.0)
			)
		)
		GetXYInFrontOfPlayer(playerid, PosX, PosY, 8.0)
		CreateExplosion(PosX, PosY, PosZ, 12, 5.0)
			
		DoorData(doorid)(dBurnTime) = 1
		SaveDoor(doorid, SAVE_DOOR_THINGS)

		DeleteItem(ItemInfo(itemid)(iUID))
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_PICKLOCK)
	(
 		if(ItemInfo(itemid)(iValue1) ) 100)
 		(
   			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ten przedmiot ma ustalonπ nieprawid≥owπ wartoúÊ pierwszπ (maksymalne 100)., OK, )
			return 1
	  	)
		foreach(Doors, doorid)
		(
			if(DoorData(doorid)(dUID))
			(
				if(IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)) && GetPlayerInterior(playerid) == DoorData(doorid)(dEnterInt) && GetPlayerVirtualWorld(playerid) == DoorData(doorid)(dEnterVW))
				(
					if(!DoorData(doorid)(dLocked))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Te drzwi sπ otwarte., OK, )
						return 1
					)
					rand_value = random(101 - ItemInfo(itemid)(iValue1))
					if(!rand_value)
					(
						DoorData(doorid)(dLocked) = 0
						SaveDoor(doorid, SAVE_DOOR_LOCK)
					
   						TextDrawSetString(Text:TextDrawMainInfo(playerid), Wytrych spowodowal, ~g~otwarcie ~w~drzwi przy ktorych stoisz.)
						TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

						PlayerCache(playerid)(pShowInfoText) = 5
					)
					else
					(
						TextDrawSetString(Text:TextDrawMainInfo(playerid), Wytrych ulegl ~r~zniszczeniu ~w~przy probie otwarcia drzwi.)
						TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

						PlayerCache(playerid)(pShowInfoText) = 5
					)
					format(string, sizeof(string), * %s prÛbuje otworzyÊ drzwi wytrychem., PlayerName(playerid))
					ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
					
					DeleteItem(ItemInfo(itemid)(iUID))
					return 1
				)
			)
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_OPTIWAND)
	(
		if(ItemInfo(itemid)(iUsed))
		(
			if(!PlayerCache(playerid)(pUsingOptiwand))
			(
				return 1
			)
			hrp_SetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))
			
			SetPlayerInterior(playerid, PlayerCache(playerid)(pInt))
			SetPlayerVirtualWorld(playerid, PlayerCache(playerid)(pVW))
			
			SetCameraBehindPlayer(playerid)
			ItemInfo(itemid)(iUsed) = 0
			
			PlayerCache(playerid)(pUsingOptiwand) = false
			hrp_TogglePlayerControllable(playerid, true)
			return 1
		)
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ teraz tego przedmiotu., OK, )
			return 1
		)
		foreach(Doors, doorid)
		(
  			if(DoorData(doorid)(dUID))
			(
				if(IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)) && GetPlayerInterior(playerid) == DoorData(doorid)(dEnterInt) && GetPlayerVirtualWorld(playerid) == DoorData(doorid)(dEnterVW))
				(
					Float:CameraLookAtX, Float:CameraLookAtY, Float:CameraLookAtZ = DoorData(doorid)(dExitZ) + 1.5
					GetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

					PlayerCache(playerid)(pInt) = GetPlayerInterior(playerid)
					PlayerCache(playerid)(pVW) = GetPlayerVirtualWorld(playerid)
					
					SetPlayerCameraPos(playerid, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ) + 1.5)

					SetPlayerInterior(playerid, DoorData(doorid)(dExitInt))
					SetPlayerVirtualWorld(playerid, DoorData(doorid)(dExitVW))

				 	CameraLookAtX += (5.0 * floatsin(-DoorData(doorid)(dExitAng), degrees))
				 	CameraLookAtY += (5.0 * floatcos(-DoorData(doorid)(dExitAng), degrees))
				 	
				 	SetPlayerCameraLookAt(playerid, CameraLookAtX, CameraLookAtY, CameraLookAtZ)
					hrp_SetPlayerPos(playerid, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ) - 40.0)
				 	
					TextDrawSetString(Text:TextDrawMainInfo(playerid), Korzystasz z ~b~optiwandu~w~, aby go ~r~wylaczyc ~w~uzyj przedmiotu ponownie.)
					TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

					PlayerCache(playerid)(pShowInfoText) = 5
					ItemInfo(itemid)(iUsed) = 1
					
					PlayerCache(playerid)(pUsingOptiwand) = true
					hrp_TogglePlayerControllable(playerid, false)
					return 1
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znajdujesz siÍ przy wejúciu øadnych drzwi., OK, )
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_FLASHBANG)
	(
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ teraz tego przedmiotu., OK, )
			return 1
		)
		foreach(Doors, doorid)
		(
			if(DoorData(doorid)(dUID))
			(
				if(IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)) && GetPlayerInterior(playerid) == DoorData(doorid)(dEnterInt) && GetPlayerVirtualWorld(playerid) == DoorData(doorid)(dEnterVW))
				(
					if(DoorData(doorid)(dExitVW) != 0)
					(
						foreach(Player, i)
						(
							des_player_vw = GetPlayerVirtualWorld(i)
							if(des_player_vw == DoorData(doorid)(dExitVW))
							(
								Float:PosX, Float:PosY, Float:PosZ
								GetPlayerPos(i, PosX, PosY, PosZ)

								TextDrawShowForPlayer(i, Text:TextDrawFlashbang(i))
								PlayerCache(i)(pFlashed) = gettime()

								//audio = Audio_Play(i, AUDIO_FLASHBANG)
								//Audio_Set3DPosition(i, audio, PosX, PosY, PosZ, 10.0)
								
								SetPlayerDrunkLevel(i, 6000)
								
								TextDrawSetString(Text:TextDrawMainInfo(i), Zostales oslepiony ~b~flashbangiem~w~. Twoja widocznosc bedzie ograniczona przez kilka sekund.)
								TextDrawShowForPlayer(i, Text:TextDrawMainInfo(i))

								PlayerCache(i)(pShowInfoText) = 5
							)
						)
						DeleteItem(ItemInfo(itemid)(iUID))
						TextDrawSetString(Text:TextDrawMainInfo(playerid), Powodzenie! Twoj ~b~flashbang~w~ zostal wrzucony poprawnie do srodka.)
						TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
						PlayerCache(playerid)(pShowInfoText) = 3
						return 1
					)
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znajdujesz siÍ przy wejúciu øadnych drzwi., OK, )
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_FLASHLIGHT)
	(
		if(!ItemInfo(itemid)(iUsed))
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_FLASHLIGHT))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ tego przedmiotu w tym momencie., OK, )
				return 1
			)
			
			ItemInfo(itemid)(iUsed) = 1
			PlayerCache(playerid)(pManageItem) = 0

			RemovePlayerAttachedObject(playerid, SLOT_FLASHLIGHT)
			RemovePlayerAttachedObject(playerid, SLOT_FLASHLIGHT_BEAM)
			
			mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
			
			data(256), access_model, access_bone,
			Float:access_posx, Float:access_posy, Float:access_posz,
			Float:access_rotx, Float:access_roty, Float:access_rotz,
			Float:access_scalex, Float:access_scaley, Float:access_scalez

			mysql_query_format(SELECT access_model, access_bone, access_posx, access_posy, access_posz, access_rotx, access_roty, access_rotz, access_scalex, access_scaley, access_scalez FROM hrp_items, hrp_access WHERE item_place = %d AND item_owner = %d AND item_type = %d AND item_used = 1 AND access_uid = 6804, PLACE_PLAYER, PlayerCache(playerid)(pUID), ITEM_FLASHLIGHT)

			mysql_store_result()
			if(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)ddfffffffff, access_model, access_bone, access_posx, access_posy, access_posz, access_rotx, access_roty, access_rotz, access_scalex, access_scaley, access_scalez)

				if(!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_FLASHLIGHT) && !IsPlayerAttachedObjectSlotUsed(playerid, SLOT_FLASHLIGHT_BEAM))
				(
					SetPlayerAttachedObject(playerid, SLOT_FLASHLIGHT, access_model, access_bone, access_posx, access_posy, access_posz, access_rotx, access_roty, access_rotz, access_scalex, access_scaley, access_scalez)
					SetPlayerAttachedObject(playerid, SLOT_FLASHLIGHT_BEAM, 18656, access_bone, access_posx - 0.004, access_posy + 0.022, access_posz - 0.01, access_rotx - 90.0, access_roty - 180.0, access_rotz + 180.0, access_scalex - 0.97, access_scaley - 0.95, access_scalez - 0.97)
				)
			)
			ApplyAnimation(playerid, COLT45, colt45_reload, 6.0, 0, 1, 1, 1, 1, 1)
			
			mysql_free_result()
			return 1
		)
		else
		(
			ItemInfo(itemid)(iUsed) = 0
			
			RemovePlayerAttachedObject(playerid, SLOT_FLASHLIGHT)
			RemovePlayerAttachedObject(playerid, SLOT_FLASHLIGHT_BEAM)
			ApplyAnimation(playerid, PED, IDLE_STANCE, 6.0, 0, 1, 1, 1, 1, 1)
			ClearAnimations(playerid)
			
			mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
			LoadPlayerAccess(playerid)
		)
		return 1
	)
	/*if(ItemInfo(itemid)(iType) == ITEM_WEAPON_AT)
	(
		if(!ItemInfo(itemid)(iUsed))
		(
			format(string, sizeof(string), )
			foreach(Items, i)
			(
				if(ItemInfo(i)(iUID))
				(
					if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(ItemInfo(i)(iType) == ITEM_WEAPON)
						(
							format(string, sizeof(string), %s%d\t%s\n, string, ItemInfo(i)(iUID), ItemInfo(i)(iName))
						)
					)
				)
			)
			if(strlen(string))
			(
				MainPlayerTable(playerid) = itemid
				ShowPlayerDialog(playerid, D_WA_LIST, DIALOG_STYLE_LIST, Wybierz broÒ do zamontowania czÍúci, string, OK, Anuluj)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie masz øadnej broni, do ktÛrej moønaby zamontowaÊ tÍ czÍúÊ., OK, )
			)
			return 1
		)
		else
		(
			ItemInfo(itemid)(iUsed) = 0
			mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		)
		return 1
	)*/

	// ITEM_BLADE usuniety w tym miejscu
	
	if(ItemInfo(itemid)(iType) == ITEM_AQUALUNG)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Ten przedmiot zosta≥ wycofany z gry., OK, )
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_TIRE)
	(
		if(PlayerCache(playerid)(pTireVeh) != INVALID_VEHICLE_ID || PlayerCache(playerid)(pPumpVeh) != INVALID_VEHICLE_ID || PlayerCache(playerid)(pOPumpItem) != 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Obecnie jesteú juø w trakcie wymieniania lub pompowania jakiejú opony., OK, )
			return 1
		)
		
		if(ItemInfo(itemid)(iValue1) == 0)
		(		
			vehid = GetClosestVehicle(playerid)
			if(GetDistanceToVehicle(playerid, vehid) ) 3.0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Musisz staÊ przy pojeüdzie aby wymieniÊ w nim ko≥o., OK, )
				return 1
			)
			if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
			(
				if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie jesteú cz≥onkiem grupy, ktÛra jest w≥aúcicielem tego pojazdu., OK, )
					return 1
				)
			)
			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
			(
				if(CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie jesteú w≥aúcicielem tego pojazdu., OK, )
					return 1
				)
			)

			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iValue1) = 1
			format(string, sizeof(string), Przebita Opona)
			strmid(ItemInfo(itemid)(iName), string, 0, strlen(string), 32)
			
			mysql_query_format(UPDATE hrp_items SET item_name = %s, item_used = 0, item_value1 = 1 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID))
			
			PlayerCache(playerid)(pTireVeh) = vehid
			PlayerCache(playerid)(pTireTime) = 70
		)
		else
		(
			object_id = GetClosestObject(playerid)
			if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_AIR_PUMP)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie znaleziono øadnego kompresora w pobliøu.\nStaÒ przy pojeüdzie w celu wymienienia w nim opony., OK, )
				return 1
			)
			
			player_vw = GetPlayerVirtualWorld(playerid), doorid = GetDoorID(player_vw)
			if(doorid != INVALID_DOOR_ID)
			(
				if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
				(
					group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
					if(group_id_fix != INVALID_GROUP_ID)
					(
						if(GroupData(group_id_fix)(gType) == GROUP_WORKSHOP || GroupData(group_id_fix)(gType) == GROUP_GASSTATION)
						(
							if(PlayerCache(playerid)(pCash) ) 10)
							(
								hrp_GivePlayerMoney(playerid, -10)
								GroupData(group_id_fix)(gCash) += 10
								SaveGroup(group_id_fix)
							)
							else
							(
								ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie masz przy sobie $10 potrzebnych do uruchomienia kompresora., OK, )	
								return 1
							)
						)
					)
				)
			)
						
			PlayerCache(playerid)(pOPumpItem) =  itemid
			PlayerCache(playerid)(pOPumpTime) = 70
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_NUTRIENT)
	(
		if(PlayerCache(playerid)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ tego úrodka w podczas BW., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pWounded))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz uøyÊ tego úrodka w trakcie os≥abienia organizmu., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pGymNutrient) ) 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Jesteú juø pod wp≥ywem odøywki lub sterydu., OK, )	
			return 1
		)
		if(ItemInfo(itemid)(iValue1) (= 0 || ItemInfo(itemid)(iValue2) (= 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz teraz uøyÊ tego przedmiotu., OK, )	
			return 1
		)
		if(PlayerCache(playerid)(pDrugLevel))
		(
			// Wbijanie BW do zakodzneia
		)

		time = ItemInfo(itemid)(iValue2)
		PlayerCache(playerid)(pGymFactor) = ItemInfo(itemid)(iValue1)
		PlayerCache(playerid)(pGymNutrient) = ItemInfo(itemid)(iValue2)
		DeleteItem(ItemInfo(itemid)(iUID))
		
		if(time ) 60)
		(
			minutes, seconds
			minutes = floatround(time / 60)
			seconds = floatround(time - (minutes * 60))
			format(string, sizeof(string), Uøy≥eú %s. Efekty bÍdπ dzia≥aÊ przez nastÍpne %d minut i %d sekund., ItemInfo(itemid)(iName), minutes, seconds)
		)
		else
		(
			format(string, sizeof(string), Uøy≥eú %s. Efekty bÍdπ dzia≥aÊ przez nastÍpne %d sekund., ItemInfo(itemid)(iName), time)
		)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Sukces, string, OK, )	
		return 1
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_TAGGER)
	(
		if(!IsPlayerInGroupType(playerid, GROUP_CRIMINAL) && !IsPlayerInGroupType(playerid, GROUP_POLICE))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd!, Nie jesteú cz≥onkiem grupy przestÍpczej.\nNie moøesz uøyÊ tego przedmiotu., OK, )	
			return 1
		)
		if(PlayerCache(playerid)(pAJ))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd!, Nie moøesz uøyÊ tego przedmiotu bÍdπc w AJ., OK, )	
			return 1
		)
		if(PlayerCache(playerid)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd!, Nie moøesz uøyÊ tego przedmiotu majπc BW., OK, )	
			return 1
		)
		if(GetPlayerInterior(playerid) != 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd!, Nie moøesz uøyÊ tego przedmiotu bÍdπc w budynku., OK, )	
			return 1
		)
		if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) && !PlayerCache(playerid)(pTagging))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd!, Nie moøesz uøyÊ tego przedmiotu majπc wyjÍtπ broÒ., OK, )	
			return 1
		)
		
		if(ItemInfo(itemid)(iValue1) ) 0 || ItemInfo(itemid)(iValue2) ) 0 || PlayerCache(playerid)(pTagging))
		(
			object_id = PlayerCache(playerid)(pTagging)
			CancelEdit(playerid)
			hrp_DeleteObject(object_id)		
		
			ItemInfo(itemid)(iUsed) = 0
			
			mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		
			SetPlayerAmmo(playerid, WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID), 0)
		
			WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) = 0
			WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) = 0
			WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo) = 0
			WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = 0
			
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_FUNC))
			(
				RemovePlayerAttachedObject(playerid, SLOT_WEAPON_FUNC)
			)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd!, Postanowi≥eú anulowaÊ edycjÍ obiektu. Tag nie zostanie namalowany., OK, )	
		)
		else
		(
			if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd!, Nie moøesz zaczaÊ tagowaÊ kiedy masz wyjetπ broÒ dodatkowπ., OK, )	
				return 1
			)
			else
			(
				MainPlayerTable(playerid) = itemid
				ShowPlayerDialog(playerid, D_SPRAY_FONT, DIALOG_STYLE_LIST, Tworzenie tagu, 0 - Beckett 2\n1 - Amprior\n2 - Kredit\n3 - Tahoma\n4 - Times New Roman\n5 - Arial\n6 - Diploma\n7 - Street Soul\n8 - BAUHAUS 93\n9 - Broodway\n10 - cooper blACK\n11 - Impact\n12 - OLD ENGLISH TEXT MT\n13 - playbill\n14 - ravie\n15 - showcard gothic\n16 - SNAP ITC \n17 - wide latin \n18 - goudy stout\n19 - FORTE, Maluj, Anuluj)
			)
		)
		return 1
	)

	/*
	if(ItemInfo(itemid)(iType) == ITEM_DECKOFCARDS)
	(
		if(!ItemInfo(itemid)(iUsed))
		(
			BJCreateGame(playerid)
			ItemInfo(itemid)(iUsed) = 1
		)
		else
		(
			if(PlayerCache(playerid)(pCasinoGameID) != -1)
				BJDestroyGame(PlayerCache(playerid)(pCasinoGameID))
			ItemInfo(itemid)(iUsed) = 0
		)

		mysql_query_format(UPDATE hrp_items SET item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		return 1
	)*/
	if(ItemInfo(itemid)(iType) == ITEM_LSPAD)
	(
		PlayerCache(playerid)(pLSPadItemID) = itemid
		LSPad(playerid, 1, true)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_ELOCK)
	(
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		(
			foreach(Doors, doorid)
			(
	 	   		if(DoorData(doorid)(dUID))
		  	  	(
	  		 		if(IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)) && GetPlayerVirtualWorld(playerid) == DoorData(doorid)(dEnterVW))
					(
						bool:git = false
						foreach(Player, i)
						(
							if(IsPlayerInRangeOfPoint(i, 2.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)) && GetPlayerVirtualWorld(i) == DoorData(doorid)(dEnterVW))
							(
								if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) == PlayerCache(i)(pUID))
								(
									git = true
								)
								break
							)
						)

						if(git)
						(
							if(DoorData(doorid)(dElock))
							(
								ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Te drzwi maj± juø elektroniczny zamek., OK, )
								return 1
							)
							else 
							(
								DoorData(doorid)(dElock) = 1
								SaveDoor(doorid, SAVE_DOOR_THINGS)

								ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Elektroniczny zamek zosta≥ za≥oøony.\nPamiÍtaj aby odegraÊ odpowiedni± akcjÍ (min. 5 minut)., OK, )
								ApplyAnimation(playerid, INT_HOUSE, wash_up, 7.1, 0, 0, 0, 0, 0, 1)

								DeleteItem(ItemInfo(itemid)(iUID))
								return 1
							)
						)
						else
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, W≥a∂ciciel drzwi musi byÊ obecny przy zak≥adaniu zamka., OK, )
							return 1
						)
	  			  	)
				)
			)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Musisz staÊ przy prywatnych drzwiach aby uøyÊ tego przedmiotu., OK, )
			return 1
		)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_PAGER)
	(
		ShowPlayerItemInfo(playerid, itemid)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_ROPE)
	(
		ShowPlayerItemInfo(playerid, itemid)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_HEADBAG)
	(
		ShowPlayerItemInfo(playerid, itemid)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_GAG)
	(
		ShowPlayerItemInfo(playerid, itemid)
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_HOMEPHONESET)
	(
		doorid = GetPlayerDoorID(playerid)
		
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerItemInfo(playerid, itemid)
			return 1
		)
   		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie jesteú w≥aúcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie jesteú w≥aúcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie jesteú w≥aúcicielem tego budynku., OK, )
				return 1
			)
		)
		
		if(IsDoorAddonMounted(doorid,ITEM_HOMEPHONESET))
		(
			GuiMsg(playerid,W tym pomieszczeniu jest juø zamontowany telefon stacjonarny.,1)
			return 1
		)
		
		MainPlayerTable(playerid) = itemid
		
		ShowPlayerDialog(playerid,D_DOOR_ADDON_MOUNT,DIALOG_STYLE_MSGBOX,Drzwi ª montuj,Czy chcesz zamontowaÊ telefon stacjonarny w tym pomieszczeniu?,Tak,Nie)	
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_TUNEPART)
	(
		//ShowPlayerItemInfo(playerid, itemid)
		GuiMsg(playerid, Ten przedmiot zosta≥ wycofany z uøytku, moøesz oddaÊ go administratorowi.\nW kaødym razie na nic Ci siÍ juø nie przyda., 1)
		return 1
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_NEWSPAPER)
	(
		//wczytaj gazete
		if(PlayerCache(playerid)(pBW) || PlayerCache(playerid)(pAJ))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz teraz uøyÊ gazety., OK, )
			return 1
		)
		
		if(PlayerCache(playerid)(pCuffed) != INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystπpi≥ b≥πd, Nie moøesz teraz uøyÊ gazety., OK, )
			return 1
		)
		
		//ShowPlayerNewspaper(playerid,itemid)
		testingShowPlayerNewspaper(playerid,itemid)
		PlayerCache(playerid)(pRead) = true
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_CARRY )
		
		SetPlayerAttachedObject(playerid, SLOT_PHONE, 2894,5,0,0.046999,0.107998,-88.4,-10.4,-72.2, 1, 1, 1)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_ROULETTE)
	(
		ShowPlayerItemInfo(playerid, itemid)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_PUTABLE)
	(
		if(GetPlayerVirtualWorld(playerid) != 0)
		(
			GuiMsg(playerid,Nie znajdujesz siÍ na úwiecie zerowym.,1)
			return 1
		)
		if(IsValidDynamicObject(PutableObject(playerid)(pObjID)))
		(
			//usun dotychczasowy, zmien used na 0 & wyczyúÊ tablice
			ItemInfo(itemid)(iUsed) = 0
			DestroyDynamicObject(PutableObject(playerid)(pObjID))
			PutableObject(playerid)(pObjID) = INVALID_OBJECT_ID
			PutableObject(playerid)(pObjUID) = EOS
			PutableObject(playerid)(pObjVW) = EOS
			PutableObject(playerid)(pObjOwner) = EOS 	
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~usunales ~y~obiekt, 3000, 3)			
		)
		else
		(
			ItemInfo(itemid)(iUsed) = 1
			Float:PosX, Float:PosY, Float:PosZ, Float:PosA
			GetXYInFrontOfPlayer(playerid, PosX, PosY, 5.0)
			GetPlayerFacingAngle(playerid, PosA)
			GetPlayerPos(playerid, PosX, PosY, PosZ)	
			PlayerCache(playerid)(pPut) = true
			

			object_id = CreateDynamicObject(ItemInfo(itemid)(iValue1), PosX, PosY, PosZ - 0.5, 0.0, 0.0, PosA, 0, 0, -1, 100.0)
			PutableObject(playerid)(pObjID) = object_id
			Streamer_Update(playerid)
			PlayerCache(playerid)(pMoveObject) = object_id
			SetTimerEx(WaitForPositeObject, 1000, 0, dd, playerid, object_id)
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~postawiles ~y~obiekt, 3000, 3)
		)

	)
	
	if(ItemInfo(itemid)(iType) == ITEM_FAKEPAPERS)
	(
		if(IsPlayerInGroupType(playerid, GROUP_FBI) || IsPlayerInGroupType(playerid, GROUP_POLICE))
		(
			ShowPlayerDialog(playerid,D_FBI_FAKEPAPERS,DIALOG_STYLE_INPUT,Zmiana nicku,Wpisz swoje nowe personalia.,Gotowe,Anuluj)
		)
		else
		(
			GuiMsg(playerid,Brak uprawnieÒ do uøycia tego przedmiotu.,1)
		)
	)

	if(ItemInfo(itemid)(iType) == ITEM_SEEDS)
	(
		object_id = GetClosestObject(playerid)
		if(object_id != INVALID_OBJECT_ID) (
			model = GetObjectModel(object_id)

			if(model == 2203 || model == 2242 || model == 743 || model == 742 || model == 741)
			(
				Float:PosX, Float:PosY, Float:PosZ, interior = GetPlayerInterior(playerid), world = GetPlayerVirtualWorld(playerid)
				GetDynamicObjectPos(object_id, PosX, PosY, PosZ)
				CreatePlant(PLANT_WEED, Marihuana, PosX, PosY, PosZ, interior, world)
				DeleteItem(ItemInfo(itemid)(iUID))

				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja ro∂linka zosta≥a zasadzona. PamiÍtaj aby o ni± dbaÊ., OK, )
				return 1
			) else (
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Musisz staÊ przy doniczce aby zasadziÊ krzak marihuany.\nDostÍpne modele: 2203, 2242, 743, 742, 741, OK, )
				return 1
			)
		) else (
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Musisz staÊ przy doniczce aby zasadziÊ krzak marihuany.\nDostÍpne modele: 2203, 2242, 743, 742, 741, OK, )
			return 1
		)
	)

	if(ItemInfo(itemid)(iType) == ITEM_CARD)
	(
		if(ItemInfo(itemid)(iValue1) == 0)
		(
			MainPlayerTable(playerid) = itemid
			ShowPlayerDialog(playerid, D_CREATE_CARD, DIALOG_STYLE_INPUT, Tworzenie karty, Wpisz maksymalny limit tygodniowy na karcie., OK, Anuluj)
			return 1
		)

		if(ItemInfo(itemid)(iValue1) )= 0)
		(
			cardid = GetCardID(ItemInfo(itemid)(iValue1))
			if(Cards(cardid)(cardBalance) ) 0)
			(
				if(IsPlayerInGroup(playerid, Cards(cardid)(cardGroup)))
				(
					group_id_fix = Cards(cardid)(cardGroup)

					if(PlayerCache(playerid)(pBusinessCard) (= 0)
					(
						PlayerCache(playerid)(pBusinessCard) = ItemInfo(itemid)(iValue1)

						format(string, sizeof(string), %s\nBalans: $%d | Limit: $%d\n\nNastÍpna oferta naprawy, wymiany czÍúci, mandat lub tankowanie zostanie pokryta z konta grupy.\nJeøeli chcesz anulowaÊ to dzia≥anie uøyj karty ponownie., GroupData(group_id_fix)(gName), Cards(cardid)(cardBalance), Cards(cardid)(cardLimit))
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
					)
					else
					(
						PlayerCache(playerid)(pBusinessCard) = -1
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przesta≥eú p≥aciÊ kartπ firmowπ., OK, )
					)
					return 1
				)
			) else (
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Ta karta przekroczy≥a juø balans na ten tydzieÒ., OK, )
			)
		)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_OXYGEN)
	(
		if(PlayerCache(playerid)(pDive))
		(
			ItemInfo(itemid)(iUsed) = 0
			PlayerCache(playerid)(pDive) = false
			RemovePlayerAttachedObject(playerid,SLOT_TRYING)
			
			StopDive(playerid)
			//ClearAnimations(playerid)
			SetTimerEx(StopPlayerDivingAnim,100,false,i,playerid)
		)
		else
		(
			Float:Pos(3)
			GetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))
			
			if(Pos(2) ) -0.5)
			(
				GuiMsg(playerid,Jesteú za p≥ytko by uøyÊ tego przedmiotu.,1)
				return 1
			)
			
			ItemInfo(itemid)(iUsed) = 1
			PlayerCache(playerid)(pDive) = true
			SetPlayerAttachedObject(playerid, SLOT_TRYING, 19580, 1, -0.170998, 0.014, -0.019997, -174.7, 94.5, 177, 1.0, 1.0, 1.0)
			
			StartDive(playerid)
			GuiMsg(playerid,(CCCCCC)Za≥oøy≥eú na siebie aparaturÍ tlenowπ.\n\nUøyj (C4B100)PPM (CCCCCC)aby zejúÊ pod wodÍ, (C4B100)LPM(CCCCCC) by pop≥ynπÊ do gÛry.\n(C4B100)WSAD(CCCCCC) - by p≥ynπÊ.,0)
		)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_SURFBOARD)
	(
		if(ItemInfo(itemid)(iUsed) == 1)
		(
			ItemInfo(itemid)(iUsed) = 0
			surf_DestroySurfboard(PlayerCache(playerid)(pSurfID))
			ClearAnimations(playerid)
		)
		else
		(
			Float:Pos(3)
			GetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))
			
			if(Pos(2) ) -0.5)
			(
				GuiMsg(playerid,Jesteú za p≥ytko by umieúciÊ deskÍ.,1)
				return 1
			)
			
			ItemInfo(itemid)(iUsed) = 1
			
			surfboard = surf_CreateBoard(2404, Pos(0),Pos(1)+2.1,0.09, 270.0,0,180.0)
			//Surfboard(surfboard)(surfPlayerID) = playerid
			PlayerCache(playerid)(pSurfID) = surfboard
			GuiMsg(playerid,(CCCCCC)Aby rozpoczπÊ surfing wejdü na deskÍ i wpisz komendÍ (C4B100)/surfuj,0)
		)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_BOMB)
	(
		if(ItemInfo(itemid)(iUsed))
		(
			GuiMsg(playerid, Ta bomba jest juø w uøyciu., 1)
			return 1
		)
		
		if(!IsPlayerInAnyVehicle(playerid))
		(
			GuiMsg(playerid, Musisz siedzieÊ w pojeüdzie by rozpoczπÊ montowanie bomby., 1)
			return 1
		)
		
		vehicleid = GetPlayerVehicleID(playerid)
		
		if(CarInfo(vehicleid)(cEngineTogged))
		(
			GuiMsg(playerid, Silnik w pojeüdzie musi byÊ zgaszony, by mÛc zamontowaÊ bombÍ., 1)
			return 1
		)
		
		PlayerCache(playerid)(pBombTime) = 120
		PlayerCache(playerid)(pBombID) = ItemInfo(itemid)(iUID)
		PlayerCache(playerid)(pBombPhase) = BOMB_TYPE_ARM
		GuiMsg(playerid, Zaczπ≥eú proces montowania bomby, odczekaj do koÒca wyznaczonego czasu by jπ uzbroiÊ., 1)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_SILENCER)
	(
		ishaveglock = 0, gunlist(128)
		foreach(Items, i)
		(
			if(ItemInfo(i)(iUID))
			(
				if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
				(
					if(ItemInfo(i)(iType) == ITEM_WEAPON)
					(
						if(ItemInfo(i)(iValue1) == 22)
						(
							format(gunlist, sizeof(gunlist), %d. %s, ItemInfo(i)(iUID), ItemInfo(i)(iName))
							ishaveglock = 1
						)
					)
				)
			)
		)
		
		if(ishaveglock != 0)
		(
			// Dialog
			ShowPlayerDialog(playerid, D_WEAPON_SILENCER_SELECT, DIALOG_STYLE_LIST, T≥umik ª za≥Ûø, gunlist, Wybierz, Anuluj)
		)
		else
		(
			GuiMsg(playerid, Nie posiadasz øadnej pasujπcej broni do tego t≥umika., 1)
		)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_WORM)
	(
		bool:candoit = false
		foreach(Items, i)
		(
			if(ItemInfo(i)(iUID))
			(
				if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
				(
					if(ItemInfo(i)(iType) == ITEM_FISHING)
					(
						candoit = true
						break
					)
				)
			)
		)
		
		if(!candoit)
		(
			GuiMsg(playerid, Nie posiadasz øadnej wÍdki!, 1)
			return 1
		)
		
		PlayerCache(playerid)(pWormed) = true
		GuiMsg(playerid, Na haczyk na≥oøy≥eú robaka, teraz moøesz zaczπÊ ≥owiÊ., 0)
		
		if(ItemInfo(itemid)(iValue1) == 1)
		(
			DeleteItem(ItemInfo(itemid)(iUID))
		)
		else
		(
			temp(64)
			format(temp, sizeof(temp), Robaki (%d szt.), ItemInfo(itemid)(iValue1) - 1)
			ItemInfo(itemid)(iValue1) = ItemInfo(itemid)(iValue1) - 1
			format(ItemInfo(itemid)(iName), 32, %s, temp)
		)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_BANDAGE)
	(
		/*if(Logged(playerid))
		(
			GuiMsg(playerid, Ten przedmiot nie jest skoÒczony., 1)
			return 1
		)*/
		
		if(PlayerCache(playerid)(pBandageTime) ) 0)
		(
			GuiMsg(playerid, Jesteú w trakcie opatrywania kogoú., 1)
			return 1
		)
		
		// DodaÊ timer do leczenia, dodaÊ leczenie innych osÛb itp.
		
		MainPlayerTable(playerid) = itemid
		ShowPlayerDialog(playerid, D_BANDAGE, DIALOG_STYLE_LIST, Wybierz opcjÍ, 1. Opatrz siebie\n2. Opatrz innego gracza, Wybierz, Anuluj)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_PLANT)
	(
		if(PlayerCache(playerid)(pGroupDuty))
		(
			group_id_fix = GetPlayerDutyGroupID(playerid)
			if(GroupData(group_id_fix)(gType) != GROUP_FARM)
			(
				GuiMsg(playerid, Musisz byÊ na s≥uøbie grupy o typie farmerskim by mÛc zasadziÊ nasiona., 1)
				return 1
			)
			
			// stworz
			Float:Pos(3)
			GetPlayerPos(playerid, Pos(0), Pos(1), Pos(2))
			CreateSeed(playerid, Pos(0), Pos(1), Pos(2), ItemInfo(itemid)(iValue1))
			ApplyAnimation(playerid,BOMBER,BOM_Plant,4.1,0,0,0,0,0,1)
			Streamer_Update(playerid)
		)
		else
		(
			GuiMsg(playerid, Musisz byÊ na s≥uøbie grupy o typie farmerskim by mÛc zasadziÊ nasiona., 1)
			return 1
		)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_SPECIAL)
	(
		switch(ItemInfo(itemid)(iValue1))
		(
			case SPECIAL_TYPE_OBJECT:
			(
				if(GetPlayerVirtualWorld(playerid) == 0)
				(
					GuiMsg(playerid, Aby uøyÊ tego obiektu, musisz znajdowaÊ siÍ w budynku., 1)
					return 1
				)
				
				doorid = GetPlayerDoorID(playerid), owner = DoorData(doorid)(dOwner)
				if(DoorData(doorid)(dUID) ) 0)
				(
					switch(DoorData(doorid)(dOwnerType))
					(
						case OWNER_GROUP:
						(
							if(!IsPlayerInGroup(playerid, owner))
							(
								GuiMsg(playerid, Nie jesteú w≥aúcicielem tego budynku., 1)
								return 1
							)
							
							// dodaj obiekty
							addSpecialObjects(playerid, ItemInfo(itemid)(iUID), doorid, ItemInfo(itemid)(iValue2))
						)
						case OWNER_PLAYER:
						(
							if(PlayerCache(playerid)(pUID) != owner)
							(
								GuiMsg(playerid, Nie jesteú w≥aúcicielem tego budynku., 1)
								return 1
							)
							
							// dodaj obiekty
							addSpecialObjects(playerid, ItemInfo(itemid)(iUID), doorid, ItemInfo(itemid)(iValue2))
						)
					)
				)
				else
				(
					GuiMsg(playerid, Aby uøyÊ tego obiektu, musisz znajdowaÊ siÍ w budynku., 1)
					return 1
				)
			)
		)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_PRESENT)
	(
		if(ItemInfo(itemid)(iValue1) == PlayerCache(playerid)(pGID))
		(
			GuiMsg(playerid, Nie wypada kupowaÊ sobie samemu prezentÛw!\nPodaruj go komuú!, 0)
			return 1
		)
		
		mysql_query_format(SELECT * FROM hrp_presents WHERE present_gid = %d AND present_action = %d, PlayerCache(playerid)(pGID), 2)
		mysql_store_result()
		if(mysql_num_rows() ) 4)
		(
			mysql_free_result()
			GuiMsg(playerid, Wyczerpa≥eú limit moøliwych do otwarcia prezentÛw!, 1)
			return 1
		)
		mysql_free_result()
		
		// OtwÛrz prezent
		mysql_query_format(INSERT INTO hrp_presents VALUES(NULL, %d, %d), PlayerCache(playerid)(pGID), 2)
		DeleteItem(ItemInfo(itemid)(iUID))
		
		present = 1 + random(8)
		switch(present)
		(
			case 1:
			(
				CreatePlayerItem(playerid, iPhone 6, ITEM_PHONE, 0, 8)
			)
			case 2:
			(
				CreatePlayerItem(playerid, Ubranie, ITEM_CLOTH, 1+random(298), 0)
			)
			case 3:
			(
				CreatePlayerItem(playerid, LSPad, ITEM_LSPAD, 0, 0)
			)
			case 4:
			(
				CreatePlayerItem(playerid, Rolex, ITEM_WATCH, 0, 0)
			)
			case 5:
			(
				CreatePlayerItem(playerid, MP4, ITEM_PLAYER, 0, 0)
			)
			case 6:
			(
				CreatePlayerItem(playerid, Zestaw do nurkowania, ITEM_OXYGEN, 0, 0)
			)
			case 7:
			(
				CreatePlayerItem(playerid, Rolki, ITEM_ROLL, 0, 0)
			)
			default:
			(
				CreatePlayerItem(playerid, Ubranie, ITEM_CLOTH, 1+random(298), 0)
			)
		)
		
		GuiMsg(playerid, Otworzy≥eú prezent!\nW Twoim ekwipunku powinna pojawiÊ siÍ zawartoúÊ pude≥ka, podziÍkuj osobie, ktÛra go podarowa≥a., 0)
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_COOK_INGREDIENT)
	(
		GuiMsg(playerid, Tego przedmiotu nie moøna uøyÊ. Moøesz go wykorzystaÊ w procesie tworzenia narkotykÛw., 1)
		return 1
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_COOK_OBJECT)
	(
		if(GetPlayerVirtualWorld(playerid) == 0)
		(
			GuiMsg(playerid, Nie moøesz postawiÊ tego obiektu na úwiecie 0. Aby to zrobiÊ, poproú administratora., 1)
			return 1
		)
		
		GuiMsg(playerid, Pomyúlnie postawi≥eú obiekt.\nTeraz moøesz go ustawiÊ w odpowiednim miejscu., 0)
		
		Float:PosX, Float:PosY, Float:PosZ,
		interior_id = GetPlayerInterior(playerid), world_id = GetPlayerVirtualWorld(playerid)
		
		GetPlayerPos(playerid, PosX, PosY, PosZ)
		GetXYInFrontOfPlayer(playerid, PosX, PosY, 2.0)

		object_id = hrp_AddObject(OBJECT_COOK, PosX, PosY, PosZ, 0.0, 0.0, 0.0, interior_id, world_id)
		Streamer_Update(playerid)
		
		fakeOnPlayerSelectObject(playerid, object_id, OBJECT_COOK, PosX, PosY, PosZ)
		PlayerCache(playerid)(pMoveObject) = object_id
		
		DeleteItem(ItemInfo(itemid)(iUID))
		return 1
	)
	
	if(ItemInfo(itemid)(iType) == ITEM_KEYS)
	(
		// Val 1 = UID auta do ktorego jest dany klucz
		car_id = GetVehicleID(ItemInfo(itemid)(iValue1))
		if(car_id == INVALID_VEHICLE_ID)
		(
			GuiMsg(playerid, Pojazd jest poza zasiÍgiem., 1)
			return 1
		)
		
		if(GetVehicleVirtualWorld(car_id) != GetPlayerVirtualWorld(playerid))
		(
			GuiMsg(playerid, Pojazd jest poza zasiÍgiem., 1)
			return 1
		)
		
		if(PlayerCache(playerid)(pBW))
		(
			GuiMsg(playerid, Nie moøesz teraz uøyÊ tego przedmiotu., 1)
			return 1
		)
		
		if(GetDistanceToVehicle(playerid, car_id) ) 100)
		(
			GuiMsg(playerid, Pojazd jest poza zasiÍgiem., 1)
			return 1
		)
		
		if(CarInfo(car_id)(cLocked))
		(
			GameTextForPlayer(playerid, ~w~Pojazd ~g~otwarty, 4000, 6)
			CarInfo(car_id)(cPilotTick) = true
			CarInfo(car_id)(cLocked) = false
			SetVehicleLock(car_id, false)
		)
		else
		(
			GameTextForPlayer(playerid, ~w~Pojazd ~r~zamkniety, 4000, 6)
			CarInfo(car_id)(cPilotTick) = true
			CarInfo(car_id)(cLocked) = true
			SetVehicleLock(car_id, true)
		)
		
		// TrochÍ wizualnego
		ApplyAnimation(playerid, HEIST9, Use_SwipeCard, 4.1, 0, 0, 0, 0, 0, 1)
		ChangeVehicleLightsStatus(car_id, true)
		PlayerPlaySound(playerid, 1147, 0, 0, 0)
	)
	
	/*if(ItemInfo(itemid)(iType) == ITEM_SKATEBOARD)
	(
		if(PlayerCache(playerid)(pAdmin) == 0)
		(
			GuiMsg(playerid, Ten przedmiot jeszcze nie zosta≥ ukoÒczony., 1)
			return 1
		)
		
		if(ItemInfo(itemid)(iUsed) == 1)
		(
			// usun jπ
			ItemInfo(itemid)(iUsed) = 0
			skateboard = PlayerCache(playerid)(pSkateboardID)
			destroySkateboard(skateboard)
			
			PlayerCache(playerid)(pSkateboardID) = -1
			sendClientPoop(playerid, ª Schowa≥eú deskÍ do ekwipunku.)
		)
		else
		(
			// dodaj jπ
			Float:Pos(3)
			GetPlayerPos(playerid, Pos(0), Pos(1), Pos(2))
			
			ItemInfo(itemid)(iUsed) = 1
			//MapAndreas_FindZ_For2DCoord(Pos(0), Pos(1), Pos(2))
			skateboard = createSkateboard(15225, Pos(0),Pos(1)+2.1,Pos(2)+0.10, 90.0 ,0.0, 0.0)
			PlayerCache(playerid)(pSkateboardID) = skateboard
			
			sendClientPoop(playerid, ª Postawi≥eú deskÍ, stoi teraz ona obok Ciebie.)
		)
	)*/

	if(ItemInfo(itemid)(iType) == ITEM_SAFE)
	(
		bool:checkbug = false
		if(gettime() - LogTime(playerid) ) 60)
			checkbug = true
		
		if(!checkbug)
		(
			GuiMsg(playerid, Musisz chwilÍ odczekaÊ nim uøyjesz tej komendy., 0)
			return 1
		)


		if(ItemInfo(itemid)(iValue1) == 0)
		(
			// Nowy sejf
			MainPlayerTable(playerid) = itemid
			ShowPlayerDialog(playerid, D_NEW_SAFE_PASSWORD, DIALOG_STYLE_INPUT, Sejf, Wpisz nowe haslo dla tego sejfu., OK, Anuluj)
			return 1
		) else (
			// Odblokowanie
			MainPlayerTable(playerid) = itemid
			ShowPlayerDialog(playerid, D_SAFE_AUTH, DIALOG_STYLE_INPUT, Sejf, Wpisz haslo dla tego sejfu., OK, Anuluj)
			return 1
		)
	)
	
	return 1
)

