// JE¯ELI KTOŒ TEGO KIEDYŒ U¯YWA TO PRZYSTOSOWAÆ POD NOWY SYSTEM BRONI !!!! //

/*GenerateWeaponForItem(itemid)
(
	mysql_query(INSERT INTO hrp_weapons (w_ammo) VALUES(5))
	new_id = mysql_insert_id()
	mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, new_id, ItemInfo(itemid)(iUID))
	ItemInfo(itemid)(iValue2) = new_id
	
	wid = Itter_Free(Weapons)
	mysql_query_format(SELECT * FROM hrp_weapons WHERE w_uid = %d LIMIT 1, new_id)
	mysql_store_result()
	
	data(256)
	
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ddddddd,
		WeaponInfo(wid)(wUID),
		WeaponInfo(wid)(wScope),
		WeaponInfo(wid)(wLight),
		WeaponInfo(wid)(wHandle),
		WeaponInfo(wid)(wMag),
		WeaponInfo(wid)(wSilent),
		WeaponInfo(wid)(wAmmo))
		
		Itter_Add(Weapons, wid)
	)
	mysql_free_result()	
	return 1
)

GetWeapon(wid)
(
	foreach(Weapons, i)
	(
		if(WeaponInfo(i)(wUID) == wid)
		(
			return i
		)
	)
	
	nwid = Itter_Free(Weapons), data(64)
	mysql_query_format(SELECT * FROM hrp_weapons WHERE w_uid = %d LIMIT 1, wid)
	mysql_store_result()
	
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ddddddd,
		WeaponInfo(nwid)(wUID),
		WeaponInfo(nwid)(wScope),
		WeaponInfo(nwid)(wLight),
		WeaponInfo(nwid)(wHandle),
		WeaponInfo(nwid)(wMag),
		WeaponInfo(nwid)(wSilent),
		WeaponInfo(nwid)(wAmmo))
		
		Itter_Add(Weapons, nwid)
	)
	mysql_free_result()
	
	if(nwid)
	(
		return nwid
	)
	
	return -1
)

SaveWeapon(w)
(
	mysql_query_format(UPDATE hrp_weapons SET w_scope = %d, w_light = %d, w_handle = %d, w_mag = %d, w_silent = %d, w_ammo = %d WHERE w_uid = %d, WeaponInfo(w)(wScope), WeaponInfo(w)(wLight), WeaponInfo(w)(wHandle), WeaponInfo(w)(wMag), WeaponInfo(w)(wSilent), WeaponInfo(w)(wAmmo), WeaponInfo(w)(wUID))
)

HandlePlayerWeaponSwap(playerid, bool:hide)
(
	player_weapon = PlayerCache(playerid)(pWeaponUID), itemid = GetItemID(player_weapon), wid = GetWeapon(ItemInfo(itemid)(iValue2))
	if(WeaponInfo(wid)(wUID))
	(
		if(hide)
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_SCOPE))
			(
				RemovePlayerAttachedObject(playerid, SLOT_SCOPE)
			)
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT))
			(
				RemovePlayerAttachedObject(playerid, SLOT_LIGHT)
			)
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT_BEAM))
			(
				RemovePlayerAttachedObject(playerid, SLOT_LIGHT_BEAM)
			)
		)
		else
		(
			if(WeaponInfo(wid)(wScope) == 1)
			(
				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_SCOPE))
				(
					RemovePlayerAttachedObject(playerid, SLOT_SCOPE)
				)
				if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
				(
					if(ItemInfo(itemid)(iValue1) )= 22 && ItemInfo(itemid)(iValue1) (= 24)
					(
						SetPlayerAttachedObject(playerid, SLOT_SCOPE, 18643, 6, 0.108249, 0.030232, 0.118051, 1.468254, 349.862579, 364.784240, 1.0, 1.0, 1.0)
					)
					else
					(
						SetPlayerAttachedObject(playerid, SLOT_SCOPE, 18643, 6, 0.528249, -0.020266, 0.068052, -1.621746, 356.202667, 355.084289, 1.0, 1.0, 1.0)
					)
				)
				else
				(
					if(ItemInfo(itemid)(iValue1) )= 22 && ItemInfo(itemid)(iValue1) (= 24)
					(
						SetPlayerAttachedObject(playerid, SLOT_SCOPE, 18643, 6, 0.108249, 0.030232, 0.118051, 1.468254, 350.512573, 364.284240, 1.0, 1.0, 1.0)
					)
					else
					(
						SetPlayerAttachedObject(playerid, SLOT_SCOPE, 18643, 6, 0.528249, -0.020266, 0.068052, -6.621746, 352.552642, 355.084289, 1.0, 1.0, 1.0)
					)
				)
			)
			else if(WeaponInfo(wid)(wScope) == 2)
			(
				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_SCOPE))
				(
					RemovePlayerAttachedObject(playerid, SLOT_SCOPE)
				)
			)
			
			if(WeaponInfo(wid)(wLight) == 1)
			(
				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT))
				(
					RemovePlayerAttachedObject(playerid, SLOT_LIGHT)
				)
				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT_BEAM))
				(
					RemovePlayerAttachedObject(playerid, SLOT_LIGHT_BEAM)
				)
				if(ItemInfo(itemid)(iValue1) )= 22 && ItemInfo(itemid)(iValue1) (= 24)
				(
					SetPlayerAttachedObject(playerid, SLOT_LIGHT, 18641, 6, 0.26, 0.019, 0.035, 0.0, 270.0, 0.0, 0.5, 0.5, 0.25)
					SetPlayerAttachedObject(playerid, SLOT_LIGHT_BEAM, 18656, 6, 0.22, 0.03, 0.035, 90.0, 0.0, 270.0, 0.015, 0.05, 0.015)
				)
				else
				(
					SetPlayerAttachedObject(playerid, SLOT_LIGHT, 18641, 6, 0.485, -0.045, 0.085, 40.0, 270.0, 40.0, 0.65, 0.65, 0.45)
					SetPlayerAttachedObject(playerid, SLOT_LIGHT_BEAM, 18656, 6, 0.415, -0.0245, 0.080, 90.0, -3.0, 274.0, 0.022, 0.09, 0.022)
				)
			)
			else if(WeaponInfo(wid)(wLight) == 2)
			(
				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT))
				(
					RemovePlayerAttachedObject(playerid, SLOT_LIGHT)
				)
				if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT_BEAM))
				(
					RemovePlayerAttachedObject(playerid, SLOT_LIGHT_BEAM)
				)
			)
		)
	)
)

ReloadPlayerWeapon(playerid)
(
	// Koordynaty laserownika celowanego : http://forum.sa-mp.com/showthread.php?t=207732
	player_weapon = PlayerCache(playerid)(pWeaponUID), itemid = GetItemID(player_weapon), wid = GetWeapon(ItemInfo(itemid)(iValue2))
	if(WeaponInfo(wid)(wUID))
	(
		if(WeaponInfo(wid)(wScope) == 1)
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_SCOPE))
			(
				RemovePlayerAttachedObject(playerid, SLOT_SCOPE)
			)
			if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
			(
				if(ItemInfo(itemid)(iValue1) )= 22 && ItemInfo(itemid)(iValue1) (= 24)
				(
					SetPlayerAttachedObject(playerid, SLOT_SCOPE, 18643, 6, 0.108249, 0.030232, 0.118051, 1.468254, 349.862579, 364.784240, 1.0, 1.0, 1.0)
				)
				else
				(
					SetPlayerAttachedObject(playerid, SLOT_SCOPE, 18643, 6, 0.528249, -0.020266, 0.068052, -1.621746, 356.202667, 355.084289, 1.0, 1.0, 1.0)
				)
			)
			else
			(
				if(ItemInfo(itemid)(iValue1) )= 22 && ItemInfo(itemid)(iValue1) (= 24)
				(
					SetPlayerAttachedObject(playerid, SLOT_SCOPE, 18643, 6, 0.108249, 0.030232, 0.118051, 1.468254, 350.512573, 364.284240, 1.0, 1.0, 1.0)
				)
				else
				(
					SetPlayerAttachedObject(playerid, SLOT_SCOPE, 18643, 6, 0.528249, -0.020266, 0.068052, -6.621746, 352.552642, 355.084289, 1.0, 1.0, 1.0)
				)
			)
		)
		else if(WeaponInfo(wid)(wScope) == 2)
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_SCOPE))
			(
				RemovePlayerAttachedObject(playerid, SLOT_SCOPE)
			)
		)
		
		if(WeaponInfo(wid)(wLight) == 1)
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT))
			(
				RemovePlayerAttachedObject(playerid, SLOT_LIGHT)
			)
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT_BEAM))
			(
				RemovePlayerAttachedObject(playerid, SLOT_LIGHT_BEAM)
			)
			if(ItemInfo(itemid)(iValue1) )= 22 && ItemInfo(itemid)(iValue1) (= 24)
			(
				SetPlayerAttachedObject(playerid, SLOT_LIGHT, 18641, 6, 0.26, 0.019, 0.035, 0.0, 270.0, 0.0, 0.5, 0.5, 0.25)
				SetPlayerAttachedObject(playerid, SLOT_LIGHT_BEAM, 18656, 6, 0.22, 0.03, 0.035, 90.0, 0.0, 270.0, 0.015, 0.05, 0.015)
			)
			else
			(
				SetPlayerAttachedObject(playerid, SLOT_LIGHT, 18641, 6, 0.485, -0.045, 0.085, 40.0, 270.0, 40.0, 0.65, 0.65, 0.45)
				SetPlayerAttachedObject(playerid, SLOT_LIGHT_BEAM, 18656, 6, 0.415, -0.0245, 0.080, 90.0, -3.0, 274.0, 0.022, 0.09, 0.022)
			)
		)
		else if(WeaponInfo(wid)(wLight) == 2)
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT))
			(
				RemovePlayerAttachedObject(playerid, SLOT_LIGHT)
			)
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LIGHT_BEAM))
			(
				RemovePlayerAttachedObject(playerid, SLOT_LIGHT_BEAM)
			)
		)
	)
	SaveWeapon(wid)
	return 1
)
*/

stock UpdateNativeWeaponSkills(playerid)
(
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 800)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 1000)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 1000)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 1000)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 800)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 1000)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 800)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 1000)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 1000)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 1000)
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 1000)
	return 1
)

stock GetPlayerWeaponAmmo(playerid, weaponid)
(
	ammo, weapons(13)(2)
	for (i = 0 i ( 13 i++)
	(
		GetPlayerWeaponData(playerid, i, weapons(i)(0), weapons(i)(1))
		if(weapons(i)(0) == weaponid)
		(
			ammo = weapons(i)(1)
		)
	)
	return ammo
)

stock GetPlayerWeaponSlot(playerid, weaponid)
(
	slotid, weapons(13)(2)
	for (i = 0 i ( 13 i++)
	(
		GetPlayerWeaponData(playerid, i, weapons(i)(0), weapons(i)(1))
		if(weapons(i)(0) == weaponid)
		(
			slotid = i
		)
	)
	return slotid
)

stock GetWeaponMaxMag(weaponid, bool:extended=false)
(
	if(extended)
	(
		switch(weaponid)
		(
			case 22, 23:
				return 70		// 9mm, Slienced 9mm
			case 24:
				return 55 		// Desert Eagle
			case 25..27, 33:
				return 35		// Shotgun, Spawnoof, Combat, Country Rifle
			case 28, 29, 32:
				return 140		// SMG, MP5
			case 30, 31:
				return 200		// AK-47, M4
			case 34:
				return 20		// Sniper Rifle
			case 35, 36, 39, 40:
				return 5		// RPG, HS Rocket
			case 37, 41..43:
				return 1000	// Flamerthrower, Spraycan, Fire Extinguisher
			case 38, 44..46:
				return 1		// Minigun
		)
	)
	else
	(
		switch(weaponid)
		(
			case 22, 23:
				return 40		// 9mm, Slienced 9mm
			case 24:
				return 30		// Desert Eagle
			case 25..27, 33:
				return 15		// Shotgun, Spawnoof, Combat, Country Rifle
			case 28, 29, 32:
				return 65		// SMG, MP5
			case 30, 31:
				return 90		// AK-47, M4
			case 34:
				return 5		// Sniper Rifle
			case 35, 36, 39, 40:
				return 2		// RPG, HS Rocket
			case 37, 41..43:
				return 500		// Flamerthrower, Spraycan, Fire Extinguisher
			case 38, 44..46:
				return 1		// Minigun
		)
	)
	
	return 5
)

stock GetWeaponType(weaponid)
(
	switch(weaponid)
	(
		case 22, 23, 24, 26, 28, 32:
			return WEAPON_TYPE_LIGHT

		case 3, 4, 16, 17, 18, 39, 10, 11, 12, 13, 14, 40, 41:
			return WEAPON_TYPE_MELEE

		case 2, 6, 7, 8, 9, 25, 27, 29, 30, 31, 33, 34, 35, 36, 37, 38:
			return WEAPON_TYPE_HEAVY
	)
	return WEAPON_TYPE_NONE
)

stock GetPlayerUsingArmourID(playerid)
(
	itemid
	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID))
		(
			if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
			(
				if(ItemInfo(i)(iType) == ITEM_ARMOUR && ItemInfo(i)(iUsed))
				(
					itemid = i
					break
				)
			)
		)
	)
	return itemid
)

stock GetWeaponClass(weaponid)
(
	// 0 main, 1 side, 2 func
	if((weaponid ) 0 && weaponid ( 19) || weaponid ) 38)
		return 2
	else if((weaponid )= 22 && weaponid (= 24) || weaponid == 28 || weaponid == 32)
		return 1
	else
		return 0
)

stock GetWeaponModel(weapid)
(
	switch(weapid)
	(
		case 1:
			return 331
		case 2:
			return 333
		case 3:
			return 334
		case 4:
			return 335
		case 5:
			return 336
		case 6:
			return 337
		case 7:
			return 338
		case 8:
			return 339
		case 9:
			return 341
		case 10:
			return 321
		case 11:
			return 322
		case 12:
			return 323
		case 13:
			return 324
		case 14:
			return 325
		case 15:
			return 326
		case 16:
			return 342
		case 17:
			return 343
		case 18:
			return 344
		case 22:
			return 346
		case 23:
			return 347
		case 24:
			return 348
		case 25:
			return 349
		case 26:
			return 350
		case 27:
			return 351
		case 28:
			return 352
		case 29:
			return 253
		case 30:
			return 355
		case 31:
			return 356
		case 32:
			return 372
		case 33:
			return 357
		case 34:
			return 358
		case 35:
			return 359
		case 36: 
			return 360
		case 37:
			return 361
		case 38:
			return 362
		case 39:
			return 363
		case 40:
			return 364
		case 41:
			return 365
		case 42:
			return 366
		case 43:
			return 367
	)
	
	return 328
)