stock Float:GetPlayerCapacity(playerid)
(	
	return 29 + (PlayerCache(playerid)(pStrength) * 0.10)
)

stock Float:GetPlayerEqWeight(playerid)
(
	Float:weight

	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID) != 0)
		(
			if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
			(
				weight += ItemInfo(i)(iWeight)
			)
		)
	)
	
	return weight
)

stock Float:GetPlayerEqSpace(playerid)
(
	return GetPlayerCapacity(playerid) - GetPlayerEqWeight(playerid)
)

stock Float:GetItemWeightByUID(itemuid)
(
	data(32), item_uid, Float:item_weight
	mysql_query_format(SELECT item_uid, item_weight FROM hrp_items WHERE item_uid = %d LIMIT 1, itemuid)
	
	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)df, item_uid, item_weight)
	)
	mysql_free_result()
	
	return item_weight
)

stock Float:GetBagEqWeight(item_uid)
(
	desc(8), Float:total_weight = 0.0

	mysql_query_format(SELECT sum(item_weight) FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_BAG, item_uid)
	mysql_store_result()
	if(mysql_fetch_row(desc, |))
	(
		sscanf(desc, p(|)f, total_weight)
	)
	mysql_free_result()

	return total_weight
)

stock Float:GetBagCapacity(itemid)
(
	return float(ItemInfo(itemid)(iValue1))
)

stock Float:GetBagEqSpace(itemid)
(
	return GetBagCapacity(itemid) - GetBagEqWeight(ItemInfo(itemid)(iUID))
)

stock Float:GetWeaponWeight(type) (
	if(type == 1) // brass knuclkes
		return 1.0
	else if(type == 2) // golf club
		return 5.0
	else if(type == 3) // palka policyjna
		return 3.0
	else if(type == 4) // noz
		return 1.0
	else if(type == 5) // kij
		return 5.0
	else if(type == 6) // lopata
		return 6.0
	else if(type == 7) // bilard
		return 6.0
	else if(type == 8) // katana
		return 6.0
	else if(type == 9) // pila
		return 6.0
	else if(type == 10) // teleskopowa
		return 1.0
	else if(type == 11) // rurka
		return 1.5
	else if(type == 12) // maczeta
		return 5.0
	else if(type == 13) // noz (z modpacka)
		return 1.0
	else if(type == 14) // kwiaty
		return 2.0
	else if(type == 15) // siekiera
		return 6.0
	else if(type == 16) // granat
		return 2.0
	else if(type == 17) // tear gas
		return 2.0
	else if(type == 18) // koktalj
		return 2.0
	else if(type == 22) // 9mm
		return 3.0
	else if(type == 23) // z tlumikiem
		return 4.0
	else if(type == 24) // deagle
		return 3.0
	else if(type == 25) // shogun
		return 6.0
	else if(type == 26) // spawnoff
		return 4.0
	else if(type == 27) // combat
		return 6.0
	else if(type == 28) // uzi
		return 4.0
	else if(type == 29) // mp5
		return 5.0
	else if(type == 30) // ak
		return 6.0
	else if(type == 31) // m4
		return 6.0
	else if(type == 32) // tec
		return 4.0
	else if(type == 33) // country rifle
		return 6.0
	else if(type == 34) // sniper
		return 7.0
	else if(type == 35) // rpg
		return 8.0
	else if(type == 36) // hs rocket
		return 8.0
	else if(type == 37) // flame thrower (oriox)
		return 0.0
	else if(type == 38) // minigun
		return 0.0
	else if(type == 39) // momba
		return 4.0
	else if(type == 40) // detonator
		return 1.0
	else if(type == 41) // spraycan
		return 1.0
	else if(type == 42) // gasnica
		return 1.0
	else if(type == 43) // aparat 
		return 1.0
	else if(type == 44) // night vision
		return 1.0
	else if(type == 45) // thermal
		return 1.0
	else if(type == 46) // spadochron
		return 1.0
	else
		return 0.0
)

stock Float:GetItemTypeWeight(type)
(
	if(type == ITEM_WATCH)
		return 0.25
	else if(type == ITEM_FOOD)
		return 1.0
	else if(type == ITEM_CIGGY)
		return 0.5
	else if(type == ITEM_CUBE)
		return 0.25
	else if(type == ITEM_CLOTH)
		return 3.0
	else if(type == ITEM_WEAPON)
		return 4.5
	else if(type == ITEM_AMMO)
		return 1.5
	else if(type == ITEM_PHONE)
		return 1.0
	else if(type == ITEM_CANISTER)
		return 6.0
	else if(type == ITEM_MASK)
		return 1.0
	else if(type == ITEM_INHIBITOR)
		return 2.0
	else if(type == ITEM_PAINT)
		return 1.0
	else if(type == ITEM_HANDCUFFS)
		return 0.25
	else if(type == ITEM_MEGAPHONE)
		return 0.5
	else if(type == ITEM_LINE)
		return 1.0
	else if(type == ITEM_BEDBUG)
		return 1.0
	else if(type == ITEM_NOTEBOOK)
		return 1.0
	else if(type == ITEM_CHIT)
		return 0.25
	else if(type == ITEM_TUNING)
		return 7.0
	else if(type == ITEM_CHECKBOOK)
		return 0.5
	else if(type == ITEM_CHECK)
		return 0.25
	else if(type == ITEM_FISHING)
		return 2.5
	else if(type == ITEM_BAG)
		return 6.0
	else if(type == ITEM_DRINK)
		return 1.0
	else if(type == ITEM_DRUG)
		return 1.0
	else if(type == ITEM_JOINT)
		return 0.5
	else if(type == ITEM_BLET)
		return 0.25
	else if(type == ITEM_BONGOS)
		return 1.0
	else if(type == ITEM_BARREL)
		return 0.5
	else if(type == ITEM_ATTACH)
		return 1.0
	else if(type == ITEM_ACCESS)
		return 3.0
	else if(type == ITEM_PLATE)
		return 0.5
	else if(type == ITEM_PLAYER)
		return 1.0
	else if(type == ITEM_KEYS)
		return 0.25
	else if(type == ITEM_ARMOUR)
		return 3.0
	else if(type == ITEM_GLOVES)
		return 1.0
	else if(type == ITEM_CORPSE)
		return 10.0
	else if(type == ITEM_WINDGUN)
		return 4.0
	else if(type == ITEM_ROLL)
		return 2.0
	else if(type == ITEM_PASS)
		return 0.25
	else if(type == ITEM_MOLOTOV)
		return 2.0
	else if(type == ITEM_PICKLOCK)
		return 1.0
	else if(type == ITEM_OPTIWAND)
		return 1.0
	else if(type == ITEM_CRAFT)
		return 1.0
	else if(type == ITEM_FLASHBANG)
		return 0.5
	else if(type == ITEM_FLASHLIGHT)
		return 0.5
	else if(type == ITEM_WEAPON_AT)
		return 0.25
	else if(type == ITEM_BLADE)
		return 0.5
	else if(type == ITEM_AQUALUNG)
		return 1.0
	else if(type == ITEM_TIRE)
		return 7.0
	else if(type == ITEM_NUTRIENT)
		return 1.0
	else if(type == ITEM_TAGGER)
		return 1.0
	else if(type == ITEM_DECKOFCARDS)
		return 0.25
	else if(type == ITEM_LSPAD)
		return 1.5
	else if(type == ITEM_ELOCK)
		return 1.5
	else if(type == ITEM_PAGER)
		return 0.25
	else if(type == ITEM_ROPE)
		return 0.5
	else if(type == ITEM_HEADBAG)
		return 0.25
	else if(type == ITEM_GAG)
		return 0.25
	else if(type == ITEM_HOMEPHONESET)
		return 2.0
	else if(type == ITEM_TUNEPART)
		return 8.0
	else if(type == ITEM_NEWSPAPER)
		return 0.25
	else if(type == ITEM_ROULETTE)
		return 2.0
	else if(type == ITEM_PUTABLE)
		return 0.5
	else if(type == ITEM_FAKEPAPERS)
		return 0.25
	else if(type == ITEM_SEEDS)
		return 0.25
	else if(type == ITEM_OXYGEN)
		return 2.50
	else if(type == ITEM_SURFBOARD)
		return 5.00
	else if(type == ITEM_BOMB)
		return 4.00
	else if(type == ITEM_SILENCER)
		return 1.50
	else if(type == ITEM_WORM)
		return 0.25
	else if(type == ITEM_BANDAGE)
		return 0.25
	else if(type == ITEM_PLANT)
		return 0.25
	else if(type == ITEM_PRESENT)
		return 3.0
	else if(type == ITEM_SAFE)
		return 10.0
	else
		return 1.0
)