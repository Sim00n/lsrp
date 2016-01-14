public CreatePlayerItem(playerid, ItemName(), ItemType, ItemValue1, ItemValue2)
(
	item_uid, itemid
	
	if(ItemType == ITEM_PHONE)			ItemValue1 = 100000 + random(899999)
	if(ItemType == ITEM_PAINT)			ItemValue1 = 41
	if(ItemType == ITEM_FLASHLIGHT)		ItemValue1 = 6804
	if(ItemType == ITEM_PAGER)			ItemValue1 = 10000 + random(89999)
	
	Float:weight = 1.0
	if(ItemType == ITEM_WEAPON)
	(
		weight = GetWeaponWeight(ItemValue1)
	)
	else
	(
		weight = GetItemTypeWeight(ItemType)
	)
	
	mysql_query_format(INSERT INTO hrp_items (item_name, item_type, item_value1, item_value2, item_place, item_owner, item_weight) VALUES (%s, %d, %d, %d, %d, %d, %f), ItemName, ItemType, ItemValue1, ItemValue2, PLACE_PLAYER, PlayerCache(playerid)(pUID), weight)
	
	itemid = Itter_Free(Items)
	item_uid = mysql_insert_id()
	
	ItemInfo(itemid)(iUID) = item_uid
	strmid(ItemInfo(itemid)(iName), ItemName, 0, strlen(ItemName), 32)
	
	ItemInfo(itemid)(iValue1) = ItemValue1
	ItemInfo(itemid)(iValue2) = ItemValue2
	
	ItemInfo(itemid)(iType) = ItemType
	ItemInfo(itemid)(iWeight) = weight
	
	ItemInfo(itemid)(iPlace) = PLACE_PLAYER
	ItemInfo(itemid)(iOwner) = PlayerCache(playerid)(pUID)

	Itter_Add(Items, itemid)
	
	hrp_ItemActionLog(Przedmiot %s (UID: %d) zostal dodany do ekwipunku gracza %s (UID: %d)., ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID))
	
	return item_uid
)

public CreateVehicleItem(vehid, ItemName(), ItemType, ItemValue1, ItemValue2)
(	
	if(ItemType == ITEM_PHONE)			ItemValue1 = 100000 + random(899999)
	if(ItemType == ITEM_PAINT)			ItemValue1 = 41
	if(ItemType == ITEM_FLASHLIGHT)		ItemValue1 = 6804
	
	Float:weight = 1.0
	if(ItemType == ITEM_WEAPON)
	(
		weight = GetWeaponWeight(ItemValue1)
	)
	else
	(
		weight = GetItemTypeWeight(ItemType)
	)
	
	mysql_query_format(INSERT INTO hrp_items (item_name, item_type, item_value1, item_value2, item_place, item_owner, item_weight) VALUES (%s, %d, %d, %d, %d, %d, %f), ItemName, ItemType, ItemValue1, ItemValue2, PLACE_VEHICLE, CarInfo(vehid)(cUID), weight)	
	return 1
)

public DeleteItem(itemuid)
(
	itemid = GetItemID(itemuid)
	mysql_query_format(DELETE FROM hrp_items WHERE item_uid = %d LIMIT 1, itemuid)
	
	ItemInfo(itemid)(iUID) = 0
	
	ItemInfo(itemid)(iValue1) = 0
	ItemInfo(itemid)(iValue2) = 0
	
	ItemInfo(itemid)(iType) = 0
	ItemInfo(itemid)(iWeight) = 0
	
	ItemInfo(itemid)(iPlace) = 0
	ItemInfo(itemid)(iOwner) = 0
	
	ItemInfo(itemid)(iUsed) = 0
	ItemInfo(itemid)(iChecked) = false
	
	Itter_Remove(Items, itemid)
	return 1
)

public LoadItem(itemuid)
(
	data(128), itemid = Itter_Free(Items)
	mysql_query_format(SELECT item_uid, item_name, item_value1, item_value2, item_type, item_place, item_owner, item_weight FROM hrp_items WHERE item_uid = %d LIMIT 1, itemuid)
	
 	print((load) Rozpoczynam proces wczytywania statystyk przedmiotu...)

	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ds(32)dddddf,
		ItemInfo(itemid)(iUID),
		ItemInfo(itemid)(iName),
		ItemInfo(itemid)(iValue1),
		ItemInfo(itemid)(iValue2),
		ItemInfo(itemid)(iType),
		ItemInfo(itemid)(iPlace),
		ItemInfo(itemid)(iOwner),
		ItemInfo(itemid)(iWeight))
		
		Itter_Add(Items, itemid)

		if(ItemInfo(itemid)(iType) == ITEM_CARD && ItemInfo(itemid)(iValue1) != 0)
		(
			LoadCard(ItemInfo(itemid)(iValue1))
		)
	)
	mysql_free_result()
	
	printf((load) Wczytano statystyki przedmiotu %s (SampID: %d, UID: %d) pomyœlnie., ItemInfo(itemid)(iName), itemid, ItemInfo(itemid)(iUID))
	return 1
)

public LoadPlayerItems(playerid)
(
	data(128), itemid, item, tick_count = GetTickCount()
	mysql_query_format(SELECT item_uid, item_name, item_value1, item_value2, item_type, item_place, item_owner, item_used, item_weight FROM hrp_items WHERE item_place = %d AND item_owner = %d , PLACE_PLAYER, PlayerCache(playerid)(pUID))
	
 	printf((load) Rozpoczynam proces wczytywania przedmiotów gracza %s (ID: %d, UID %d)..., PlayerName(playerid), playerid, PlayerCache(playerid)(pUID))

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
  		item++
  		
		itemid = Itter_Free(Items)

		sscanf(data, p(|)ds(32)ddddddf,
		ItemInfo(itemid)(iUID),
		ItemInfo(itemid)(iName),
		ItemInfo(itemid)(iValue1),
		ItemInfo(itemid)(iValue2),
		ItemInfo(itemid)(iType),
		ItemInfo(itemid)(iPlace),
		ItemInfo(itemid)(iOwner),
		ItemInfo(itemid)(iUsed),
		ItemInfo(itemid)(iWeight))

		// Telefon
		if(ItemInfo(itemid)(iType) == ITEM_PHONE && ItemInfo(itemid)(iUsed))
		(
   			PlayerCache(playerid)(pPhoneNumber) = ItemInfo(itemid)(iValue1)
		)
		
		// Rêkawiczki
		if(ItemInfo(itemid)(iType) == ITEM_GLOVES && ItemInfo(itemid)(iUsed))
		(
			PlayerCache(playerid)(pGloves) = true
		)
		
		// Rolki
		if(ItemInfo(itemid)(iType) == ITEM_ROLL && ItemInfo(itemid)(iUsed))
		(
			PlayerCache(playerid)(pRoll) = true
		)
		
		if(ItemInfo(itemid)(iType) == ITEM_CARD && ItemInfo(itemid)(iValue1) != 0)
		(
			LoadCard(ItemInfo(itemid)(iValue1))
		)

		Itter_Add(Items, itemid)
	)
	mysql_free_result()

	printf((load) Wczytano %d przedmioty/ów (czas trwania: %d ms)., item, GetTickCount() - tick_count)
	return 1
)

public UnloadPlayerItems(playerid)
(
	item, item_next
	printf((load) Rozpoczynam proces od³adowywania przedmiotów gacza %s (ID: %d, UID:%d)..., PlayerName(playerid), playerid, PlayerCache(playerid)(pUID))

	foreach(Items, itemid)
	(
		if(ItemInfo(itemid)(iUID))
		(
			if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
			(
				ItemInfo(itemid)(iUID) = 0

				ItemInfo(itemid)(iValue1) = 0
				ItemInfo(itemid)(iValue2) = 0
				ItemInfo(itemid)(iType) = 0

				ItemInfo(itemid)(iPlace) = 0
				ItemInfo(itemid)(iOwner) = 0

				ItemInfo(itemid)(iUsed) = 0
				ItemInfo(itemid)(iWeight) = 0
				ItemInfo(itemid)(iChecked) = false
				
				Itter_SafeRemove(Items, itemid, item_next)
				item++

				itemid = item_next
			)
		)
	)

	printf((load) Od³adowano %d przedmioty/ów., item)
	return 1
)

public ListPlayerItems(playerid, manage_type)
(
	list_items(2048), item_count
	if(manage_type != MANAGE_TYPE_DASHBOARD_OFFER)
	(
		format(list_items, sizeof(list_items), Poka¿ pobliskie przedmioty\nFunkcja zaznaczania przedmiotów\n----------\t\t----------)
	)

	foreach(Items, itemid)
	(
		if(ItemInfo(itemid)(iUID))
		(
			if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
			(
				if(ItemInfo(itemid)(iUsed))
				(
					if(manage_type != MANAGE_TYPE_DASHBOARD_OFFER)
					(
						format(list_items, sizeof(list_items), %s\n(68B6FF)%d\t%.2f\t%s, list_items, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iWeight), ItemInfo(itemid)(iName))
					)
				)
				else
				(
					if(manage_type == MANAGE_TYPE_DASHBOARD_OFFER)
					(
						if(item_count == 0)
						(
							format(list_items, sizeof(list_items), %s(C0C0C0)%d\t%s, list_items, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iName))
						)
						else
						(
							format(list_items, sizeof(list_items), %s\n(C0C0C0)%d\t%s, list_items, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iName))
						)
					)
					else
					(
						format(list_items, sizeof(list_items), %s\n(C0C0C0)%d\t%.2f\t%s, list_items, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iWeight), ItemInfo(itemid)(iName))
					)
				)
				item_count ++
			)
		)
	)
	if(!item_count)
	(
		format(list_items, sizeof(list_items), %s\n(FF3D3D)#\t\tBrak przedmiotów, list_items)
	)
	
	switch(manage_type)
	(
		case MANAGE_TYPE_ALL:
		(
			title(64)
			format(title, sizeof(title), Znaleziono przedmioty » UdŸwig: %.2f/%.2f, GetPlayerEqWeight(playerid), GetPlayerCapacity(playerid))
  			ShowPlayerDialog(playerid, D_LIST_ITEMS, DIALOG_STYLE_LIST, title, list_items, Wybierz, Zamknij)
		)
		case MANAGE_TYPE_USE:
		(
			title(64)
			format(title, sizeof(title), Szybkie u¿ywanie przedmiotu » UdŸwig: %.2f/%.2f, GetPlayerEqWeight(playerid), GetPlayerCapacity(playerid))
			ShowPlayerDialog(playerid, D_LIST_ITEMS_USE, DIALOG_STYLE_LIST, title, list_items, U¿yj, Zamknij)
		)
		case MANAGE_TYPE_DROP:
		(
			ShowPlayerDialog(playerid, D_LIST_ITEMS_DROP, DIALOG_STYLE_LIST, Od³ó¿ przedmiot, list_items, Od³ó¿, Zamknij)
		)
		case MANAGE_TYPE_DASHBOARD_OFFER:
		(
			title(64)
			format(title, sizeof(title), Oferuj przedmiot » %s, GetPlayerEqWeight(playerid), PlayerName(PlayerCache(playerid)(pPlayerIDOffer)))
			ShowPlayerDialog(playerid, D_DASHBOARD_ITEM, DIALOG_STYLE_LIST, title, list_items, Dalej, Anuluj)
		)
	)
	return 1
)

public ListPlayerNearItems(playerid)
(
	if(!PlayerCache(playerid)(pRaising))	return 1
	
	data(64), list_items(512)
	
	PlayerCache(playerid)(pRaising) = false
	TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
	
	if(!IsPlayerInAnyVehicle(playerid))
	(
		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)

		mysql_query_format(SELECT item_uid, item_name, item_weight FROM hrp_items WHERE item_posx ( %f + 2 AND item_posx ) %f - 2 AND item_posy ( %f + 2 AND item_posy ) %f - 2 AND item_posz ( %f + 2 AND item_posz ) %f - 2 AND item_place = %d AND item_world = %d, PosX, PosX, PosY, PosY, PosZ, PosZ, PLACE_NONE, GetPlayerVirtualWorld(playerid))
	)
	else
	(
		vehid = GetPlayerVehicleID(playerid), bool:error = true
		if(IsPlayerInGroupType(playerid, GROUP_POLICE) || IsPlayerInGroupType(playerid, GROUP_FBI) || IsPlayerInGroupType(playerid, GROUP_ARMY))
		(
			error = false
		)
		
		if(error)
		(
			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz podnosiæ przedmiotów z tego pojazdu., OK, )
				return 1
			)
			if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
			(
				if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz podnosiæ przedmiotów z tego pojazdu., OK, )
					return 1
				)
			)
		)
		
		mysql_query_format(SELECT item_uid, item_name, item_weight FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_VEHICLE, CarInfo(vehid)(cUID))
	)
	
	new	item_uid, item_name(32), Float:item_weight

	mysql_store_result()
   	while(mysql_fetch_row(data, |))
   	(
	 	sscanf(data, p(|)ds(32)f, item_uid, item_name, item_weight)
	 	format(list_items, sizeof(list_items), %s\n%d\t%.2f\t%s, list_items, item_uid, item_weight, item_name)
	)
  	mysql_free_result()
  	if(!strlen(list_items))
  	(
	 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych przedmiotów w pobli¿u., OK, )
	 	return 1
	)
	if(IsPlayerInAnyVehicle(playerid))
	(
		vehid = GetPlayerVehicleID(playerid)
		title(64)
		format(title, sizeof(title), Pobliskie przedmioty » %.2f/%.2f, GetVehicleEqWeight(CarInfo(vehid)(cUID)), GetVehicleCapacity(GetVehicleModel(vehid)))
		ShowPlayerDialog(playerid, D_RAISE_ITEM, DIALOG_STYLE_LIST, title, list_items, Podnieœ, Anuluj)
	)
	else
	(
		ShowPlayerDialog(playerid, D_RAISE_ITEM, DIALOG_STYLE_LIST, Pobliskie przedmioty, list_items, Podnieœ, Anuluj)
	)
	PlayerCache(playerid)(pFlood) = 5
	return 1
)

public ListPlayerCheckedItems(playerid)
(
	list_items(2048), item_count
	format(list_items, sizeof(list_items), Od³ó¿ przedmioty w pobli¿u\nSchowaj zaznaczone do schowka\n----------\t\t----------)
	
	foreach(Items, itemid)
	(
		if(ItemInfo(itemid)(iUID))
		(
			if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
			(
				if(!ItemInfo(itemid)(iUsed))
				(
					if(ItemInfo(itemid)(iChecked))
					(
						format(list_items, sizeof(list_items), %s\n(C0C0C0)%d\t%.2f\t(X)\t%s, list_items, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iWeight), ItemInfo(itemid)(iName))
					)
					else
					(
						format(list_items, sizeof(list_items), %s\n(C0C0C0)%d\t%.2f\t( )\t%s, list_items, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iWeight), ItemInfo(itemid)(iName))
					)
					item_count ++
				)
			)
		)
	)
	if(!item_count)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych przedmiotów, które móg³byœ zaznaczyæ., OK, )
		return 1
	)
	ShowPlayerDialog(playerid, D_CHECK_ITEM, DIALOG_STYLE_LIST, Funkcja zaznaczania przedmiotów, list_items, Zaznacz, Wróæ)
	return 1
)

public ListPlayerItemsForPlayer(playerid, giveplayer_id)
(
	list_items(2048), item_count

	foreach(Items, itemid)
	(
		if(ItemInfo(itemid)(iUID))
		(
			if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(giveplayer_id)(pUID))
			(
		 		format(list_items, sizeof(list_items), %s\n(C0C0C0)%d\t%.2f\t%s, list_items, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iWeight), ItemInfo(itemid)(iName))

				item_count ++
			)
		)
	)
	if(!item_count)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych przedmiotów w ekwipunku., OK, )
	)
	
	title(64)
	format(title, sizeof(title), Znaleziono przedmioty » UdŸwig: %.2f/%.2f, GetPlayerEqWeight(giveplayer_id), GetPlayerCapacity(giveplayer_id))
	
  	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, title, list_items, Zamknij, )
	return 1
)

public ListVehicleItemsForPlayer(playerid, vehicleid)
(
	mysql_query_format(SELECT item_uid, item_name, item_weight FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_VEHICLE, CarInfo(vehicleid)(cUID))

	new	item_uid, item_name(32), Float:item_weight, data(64),
		list_items(1024)

	mysql_store_result()
   	while(mysql_fetch_row(data, |))
   	(
	 	sscanf(data, p(|)ds(32)f, item_uid, item_name, item_weight)
	 	format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, item_uid, item_name)
	)
  	mysql_free_result()
  	if(!strlen(list_items))
  	(
	 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych przedmiotów w pobli¿u., OK, )
	 	return 1
	)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Przedmioty znajduj¹ce siê w pojeŸdzie, list_items, Zamknij, )
	return 1
)

public OnPlayerDropItem(playerid, itemid, bool:skip_anim)
(
	if(Offer(playerid)(oType) == OFFER_ITEM)
	(
		if(Offer(playerid)(oValue) == itemid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz od³o¿yæ przedmiotu, który oferujesz., OK, )
			return 0
		)
	)

	string(128)
	
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	(
		Float:PosX, Float:PosY, Float:PosZ, Float:PosA, virtual_world = GetPlayerVirtualWorld(playerid)

		GetPlayerPos(playerid, PosX, PosY, PosZ)
		GetPlayerFacingAngle(playerid, PosA)

		if(!skip_anim)
		(
			ApplyAnimation(playerid,BOMBER,BOM_Plant,4.1,0,0,0,0,0,1)
			format(string, sizeof(string), * %s coœ odk³ada., PlayerName(playerid))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		)
		
		mysql_query_format(UPDATE hrp_items SET item_posx = %f, item_posy = %f, item_posz = %f, item_place = %d, item_world = %d WHERE item_uid = %d LIMIT 1, PosX, PosY, PosZ, PLACE_NONE, virtual_world, ItemInfo(itemid)(iUID))

		object_id
		if(ItemInfo(itemid)(iType) == ITEM_WEAPON || ItemInfo(itemid)(iType) == ITEM_PAINT)
		(
			object_id = CreateDynamicObject(WeaponModel(ItemInfo(itemid)(iValue1)), PosX, PosY, PosZ - 1.0, 80.0, 0.0, -PosA, virtual_world, -1, -1, 80.0)
			
		)
		else if(ItemInfo(itemid)(iType) == ITEM_TUNING)
		(
			object_id = CreateDynamicObject(ItemInfo(itemid)(iValue1), PosX, PosY, PosZ - 0.5, 0.0, 0.0, -PosA, virtual_world, -1, -1, 80.0)
		) else if(ItemInfo(itemid)(iType) == ITEM_SAFE)
		(
			object_id = CreateDynamicObject(ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjModel), PosX, PosY, PosZ - 1.0 + 0.46, ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjRotX), ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjRotY), -PosA, virtual_world, -1, -1, 80.0)	
		)
		else
		(
			object_id = CreateDynamicObject(ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjModel), PosX, PosY, PosZ - 1.0, ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjRotX), ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjRotY), -PosA, virtual_world, -1, -1, 80.0)
		)
		
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, (ItemInfo(itemid)(iUID) * -1))
		Streamer_Update(playerid)

		hrp_ItemActionLog(%s (UID: %d) odlozyl przedmiot %s (UID: %d) na ziemie (PosX: %.3f, PosY: %.3f, PosZ: %.3f)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), PosX, PosY, PosZ)
	)
	else if(IsPlayerInAnyVehicle(playerid))
	(
		flag = true, vehid = GetPlayerVehicleID(playerid)
		
		// Logi z propozycji
		hrp_VehicleActionLog(%s (UID: %d) odlozyl przedmiot %s do pojazdu %s (UID: %d), PlayerRealName(playerid), PlayerCache(playerid)(pUID), ItemInfo(itemid)(iName), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		
		if(ItemInfo(itemid)(iType) == ITEM_TIRE)
		(
			item_type, data(16)

			mysql_query_format(SELECT item_type FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_VEHICLE, CarInfo(vehid)(cUID))
			mysql_store_result()
			while(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)d, item_type)
				if(item_type == ITEM_TIRE)
				(
					flag = false
					break
				)
			)
			mysql_free_result()
		)
		
		if(flag)
		(
			if(GetVehicleEqSpace(vehid) ( ItemInfo(itemid)(iWeight))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W tym pojeŸdzie jest ju¿ za du¿o przedmiotów., OK, )
				return 1
			)
		
			format(string, sizeof(string), * %s odk³ada coœ w pojeŸdzie., PlayerName(playerid))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)

			ApplyAnimation(playerid,BOMBER,BOM_Plant,4.1,0,0,0,0,0,1)
			
			mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d WHERE item_uid = %d LIMIT 1, PLACE_VEHICLE, CarInfo(vehid)(cUID), ItemInfo(itemid)(iUID))

			hrp_ItemActionLog(%s (UID: %d) odlozyl przedmiot %s (UID: %d) w pojezdzie %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W tym pojeŸdzie znajduje siê ju¿ jedna opona., OK, )
			return 1
		)
	)
	// Zwolnij miejsce dla czegoœ, co mo¿e byæ u¿yte
	ItemInfo(itemid)(iUID) = 0
	ItemInfo(itemid)(iValue1) = 0
	ItemInfo(itemid)(iValue2) = 0
	ItemInfo(itemid)(iType) = 0

	ItemInfo(itemid)(iPlace) = 0
	ItemInfo(itemid)(iOwner) = 0
	
	ItemInfo(itemid)(iUsed) = 0
	ItemInfo(itemid)(iChecked) = false
	
	Itter_Remove(Items, itemid)
	return 1
)

public OnPlayerRaiseItem(playerid, itemuid)
(
	string(128), data(64),
		ItemName(32), ItemPlace, ItemType, Float:ItemWeight
	
	mysql_query_format(SELECT item_name, item_place, item_type, item_weight FROM hrp_items WHERE item_uid = %d LIMIT 1, itemuid)

	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)s(32)ddf, ItemName, ItemPlace, ItemType, ItemWeight)
	)
	mysql_free_result()
	
	// Dialog Bug Fix by seler
	if(ItemPlace == PLACE_VEHICLE && IsPlayerInAnyVehicle(playerid))
	(
		vehid = GetPlayerVehicleID(playerid), bool:error = true
		
		if(IsPlayerInGroupType(playerid, GROUP_POLICE) || IsPlayerInGroupType(playerid, GROUP_FBI) || IsPlayerInGroupType(playerid, GROUP_ARMY))
		(
			error = false
		)
		
		if(error)
		(
			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
			(
				hrp_Kick(playerid, -1, GrabCheat)
				return 1
			)
			if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
			(
				if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
				(
					hrp_Kick(playerid, -1, GrabCheat)
					return 1
				)
			)
		)
	
		// Logi z propozycji
		hrp_VehicleActionLog(%s (UID: %d) podniosl przedmiot %s z pojazdu %s (UID: %d), PlayerRealName(playerid), PlayerCache(playerid)(pUID), ItemName, CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
	)
	
	if(ItemPlace != PLACE_NONE && ItemPlace != PLACE_VEHICLE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Tego przedmiotu nie ma w pobli¿u., OK, )
		return 1
	)
	if(GetPlayerEqSpace(playerid) ( ItemWeight)
	(
		infostring(256)
		format(infostring, sizeof(infostring), Masz zbyt du¿o przedmiotów w swoim inwentarzu.\n\nDostêpne miejsce: %.2f/%.2f\nWaga przedmiotu: %.2f, GetPlayerEqWeight(playerid), GetPlayerCapacity(playerid), ItemWeight)
	
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, infostring, OK, )
		return 1
	)
	
	format(string, sizeof(string), * %s podnosi przedmiot %s., PlayerName(playerid), ItemName)
	ProxDetector(10.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE, true)

	ApplyAnimation(playerid,BOMBER,BOM_Plant,4.1,0,0,0,0,0,1)

	mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d WHERE item_uid = %d LIMIT 1, PLACE_PLAYER, PlayerCache(playerid)(pUID), itemuid)
	
	if(ItemPlace != PLACE_VEHICLE)
	(
		object_extra_id = (itemuid * -1)
		for (object_id = 0 object_id (= MAX_OBJECTS object_id++)
		(
			if(IsValidDynamicObject(object_id))
			(
				if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID) == object_extra_id)
				(
					DestroyDynamicObject(object_id)
					break
				)
			)
		)
	)
	
	LoadItem(itemuid)
	
	hrp_ItemActionLog(%s (UID: %d) podniosl przedmiot %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), ItemName, itemuid)
	return 1
)

public ShowPlayerItemInfo(playerid, itemid)
(
	/*list_info(512), title(64)
	format(list_info, sizeof(list_info), Identyfikator:\t\t%d\n, ItemInfo(itemid)(iUID))

	format(list_info, sizeof(list_info), %sTyp przedmiotu:\t%s\n, list_info, ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeName))

	if(ItemInfo(itemid)(iUsed))
	(
		format(list_info, sizeof(list_info), %sStatus:\t\t\tW u¿yciu\n\n, list_info)
	)
	else
	(
		format(list_info, sizeof(list_info), %sStatus:\t\t\tNieaktywny\n\n, list_info)
	)

	format(list_info, sizeof(list_info), %sWartoœæ 1:\t\t%d\n, list_info, ItemInfo(itemid)(iValue1))
	format(list_info, sizeof(list_info), %sWartoœæ 2:\t\t%d\n, list_info, ItemInfo(itemid)(iValue2))

	format(title, sizeof(title), Informacje » %s, ItemInfo(itemid)(iName))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, title, list_info, OK, Zamknij)
	return 1
	*/
	
	v1 = ItemInfo(itemid)(iValue1),
		v2 = ItemInfo(itemid)(iValue2),
		fdesc(512),
		desc(128)
		
		
	format(desc, sizeof(desc), Brak opisu)
		
	mysql_query_format(SELECT item_desc FROM hrp_items WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUID))
	mysql_store_result()
	if(mysql_fetch_row(desc, |))
	(
		sscanf(desc, p(|)s(128), desc)
	)
	mysql_free_result()
	
	switch(ItemInfo(itemid)(iType))
	(
		case ITEM_WATCH:
			format(fdesc, sizeof(fdesc), Zwyczajny zegarek dla twojej postaci.\nU¿yj go, by sprawdziæ która godzina.\nMo¿esz równie¿ wykorzystaæ z komendy /time lub /czas.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_FOOD:
			format(fdesc, sizeof(fdesc), Potrawa, któr¹ mo¿e spo¿yæ twoja postaæ.\nU¿yj jej, by to zrobiæ.\nJedzenie sprawia, ¿e twoja postaæ nie jest g³odna,\nprzez co jej HP ulega regeneracji.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_CIGGY:
			format(fdesc, sizeof(fdesc), Paczka fajek.\nU¿yj jej by sprawiæ, ¿e twoja postaæ odpali papierosa.\nPalenie nieznacznie obni¿a kondycjê postaci.\n\nIloœæ papierosów: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_CUBE:
			format(fdesc, sizeof(fdesc), Szeœcioœcienna kostka do gry.\nU¿yj jej, by wylosowaæ liczbê od 1 do 6.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_CLOTH:
			format(fdesc, sizeof(fdesc), Komplet ubrañ dla twojej postaci.\nU¿yj go, by zmieniæ skin. Pamiêtaj o stosownej akcji RP.\n\nSkin: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_WEAPON:
			format(fdesc, sizeof(fdesc), Broñ, której mo¿e u¿ywaæ twoja postaæ.\nU¿yj tego przedmiotu, by jej dobyæ. Mo¿esz równie¿ skorzystaæ z komendy w formie:\n/u (id broni) (sk¹d wyci¹ga)\n\nModel broni: %d\nIloœæ amunicji: %d\n\nOpis przedmiotu:\n\t %s, v1, v2, desc)
		case ITEM_AMMO:
			format(fdesc, sizeof(fdesc), Amunicja, któr¹ mo¿na prze³adowaæ broñ.\nU¿yj tego przedmiotu, by to zrobiæ. Pamiêtaj o tym, ¿e broñ nie mo¿e byæ w u¿yciu.\n\nPasuj¹cy model broni: %d\nIloœæ amunicji: %d\n\nOpis przedmiotu:\n\t %s, v1, v2, desc)
		case ITEM_PHONE:
			format(fdesc, sizeof(fdesc), Zwyczajny telefon.\nU¿yj go, by otworzyæ intuicyjne menu kontekstowe telefonu.\n\nNumer tego aparatu: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_CANISTER:
			format(fdesc, sizeof(fdesc), Kanister, s³u¿¹cy do przenoszenia paliwa i tankowania pojazdu.\nDoda paliwo do pojazdu, w którym go u¿yjesz.\n\nIloœæ paliwa: %d litrów\nTyp paliwa: %d\n\nOpis przedmiotu:\n\t %s, v1, v2, desc)
		case ITEM_MASK:
			format(fdesc, sizeof(fdesc), Maska, która ukryje to¿samoœæ twojej postaci.\nU¿yj jej, by j¹ za³o¿yæ lub zdj¹æ.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_INHIBITOR:
			format(fdesc, sizeof(fdesc), Ten przedmiot zosta³ usuniêty.\nZg³oœ siê do moderacji serwera po nagrodê.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_PAINT:
			format(fdesc, sizeof(fdesc), Lakier samochodowy zwyczajnej jakoœci.\nPo u¿yciu mo¿na go wykorzystaæ do lakierowania, komend¹ //o lakierowanie.\n\nIloœæ lakieru: %d ml.\n\nOpis przedmiotu:\n\t %s, v2, desc)
		case ITEM_HANDCUFFS:
			format(fdesc, sizeof(fdesc), Kajdanki, niezbêdne podczas aresztowañ.\nKomenda /skuj sprawia, ¿e prowadzisz podejrzanego za sob¹. Komenda /zakuj unieruchamia podejrzanego.\nAby kogoœ rozkuæ, wpisz /rozkuj.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_MEGAPHONE:
			format(fdesc, sizeof(fdesc), Megafon wykorzystywany g³ównie przez s³u¿by porz¹dkowe i organizatorów imprez.\nUmo¿liwia korzystanie z czatu //m o du¿ym zasiêgu.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_LINE:
			format(fdesc, sizeof(fdesc), Linka holownicza dla twojego auta.\nUmo¿liwia korzystanie z komendy (TUTAJ TY NAPISZ JA NIE WIEM)\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_BEDBUG:
			format(fdesc, sizeof(fdesc), Pluskwa, która nie dzia³a. Pewnie jakiœ robak, zamieszkuj¹cy wszelkiej maœci Hydraulikê.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_NOTEBOOK:
			format(fdesc, sizeof(fdesc), Zwyczajny notes.\nPo u¿yciu utworzy kartkê, na której bêdziesz móg³ zanotowaæ co tylko chcesz.\n\nIloœæ stron: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_CHIT:
			format(fdesc, sizeof(fdesc), Karteczka, na której prawdopodobnie coœ zanotowano.\nU¿yj jej aby odczytaæ zapiski.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_TUNING:
			format(fdesc, sizeof(fdesc), Komponent, którego mo¿esz u¿yæ, ¿eby odpicowaæ swoj¹ brykê.\nPracownicy warsztatów mog¹ je montowaæ, u¿ywaj¹c komendy /o montaz.\n\nSampID komponentu: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_CHECKBOOK:
			format(fdesc, sizeof(fdesc), Ksi¹¿eczka czekowa, dziêki której mo¿na utworzyæ papiery wartoœciowe.\nPo u¿yciu utworzysz czek na okreœlon¹ sumê.\n\nIloœæ czeków: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_CHECK:
			format(fdesc, sizeof(fdesc), Czek, wypisany przez pewn¹ osobê na sumê %d dolarów.\nUdaj siê do banku i go u¿yj, aby zrealizowaæ p³atnoœæ.\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_FISHING:
			format(fdesc, sizeof(fdesc), Zwyczajna wêdka wykonana z tworzyw sztucznych i zaawansowanych technologicznie w³ókien.\nPo jej u¿yciu mo¿esz ³owiæ ryby.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_BAG:
			format(fdesc, sizeof(fdesc), Pojemnik, umo¿liwiaj¹cy posiadanie wiêkszej iloœci przedmiotów.\nU¿yj go, by coœ z niego wyci¹gn¹æ, lub skorzystaj z\nopcji odk³adania w torbie, by coœ do niego schowaæ.\n\nRozmiar: %d slotów\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_DRINK:
			format(fdesc, sizeof(fdesc), Napój niekoniecznie bezalkoholowy.\nPo u¿yciu twoja postaæ zacznie spo¿ywaæ zawartoœæ, ulegaj¹c upojeniu.\nSprunk pomaga odnowiæ wytrzyma³oœæ.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_DRUG:
			format(fdesc, sizeof(fdesc), Substancja o dzia³aniu narkotycznym.\nPo u¿yciu tego przedmiotu twoja postaæ za¿yje %d gram narkotyku zawartych w torebce.\nBy zmniejszyæ dzia³kê u¿yj funkcji rozdzielania przedmiotów.\nPamiêtaj, ¿e u¿ycie niektórych substancji doprowadza do uzale¿nienia.\n\nTyp: %d\n\nOpis przedmiotu:\n\t %s, v2, v1, desc)
		case ITEM_JOINT:
			format(fdesc, sizeof(fdesc), Ciasno skrêcony blunt, pachn¹cy marihuan¹.\nPo u¿yciu twoja postaæ odpali skrêta.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_BLET:
			format(fdesc, sizeof(fdesc), Bletki, niezbêdne przy skrêcaniu blantów.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_BONGOS:
			format(fdesc, sizeof(fdesc), Bongo, którego mo¿na u¿yæ do palenia marihuany.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_BARREL:
			format(fdesc, sizeof(fdesc), Szklana lufka, dziêki której mo¿na wypaliæ marihuanê.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_ATTACH:
			format(fdesc, sizeof(fdesc), Obiekt, który mo¿na przyczepiæ do modelu postaci.\nPo u¿yciu mo¿na wybraæ edycjê lub za³o¿enie obiektu w oknie dialogowym.\n\nUID wpisu: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_ACCESS:
			format(fdesc, sizeof(fdesc), Akcesorium, które mo¿na zamontowaæ do pojazdu.\nPracownicy warsztatów maj¹ mo¿liwoœæ zamontowania tej czêœci w twoim aucie.\nTyp akcesorium: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_PLATE:
			format(fdesc, sizeof(fdesc), P³yta CD, której mo¿na u¿yæ w odtwarzaczach wszelkiego typu.\nPo u¿yciu w pojeŸdzie zostanie uruchomiona w CarAudio.\nBy u¿yæ jej w ekwipunku potrzeba odtwarzacza.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_PLAYER:
			format(fdesc, sizeof(fdesc), Odtwarzacz CD.\nU¿yj go, aby w³¹czyæ muzykê. Pamiêtaj, ¿e przed uruchomieniem nale¿y umieœciæ w nim p³ytê.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_KEYS:
			format(fdesc, sizeof(fdesc), Kluczyki do samochodu zarejestrowanego na tablicê LS%d.\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_ARMOUR:
			format(fdesc, sizeof(fdesc), Kamizelka kuloodporna sprawna w %d/%.\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_GLOVES:
			format(fdesc, sizeof(fdesc), Rêkawiczki, ukrywaj¹ce odciski palców twojej postaci.\nU¿yj ich, by je za³o¿yæ.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_CORPSE:
			format(fdesc, sizeof(fdesc), Zw³oki.\n\nOpis œmierci: %s, desc)
		case ITEM_WINDGUN:
			format(fdesc, sizeof(fdesc), Przedmiot nie jest u¿ywany. Zg³oœ siê do moderacji po ciastko.)
		case ITEM_ROLL:
			format(fdesc, sizeof(fdesc), Rolki. U¿ycie przedmiotu w³¹czy animacjê jazdy na rolkach.\nPamiêtaj o adekwatnym skinie i stosownym odegraniu akcji.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_PASS:
			format(fdesc, sizeof(fdesc), Karnet na si³owniê, wygasaj¹cy za %d minut.\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_PBENTRY:
			format(fdesc, sizeof(fdesc), Wejœciówka na paintball, wygasaj¹ca za %d minut.\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_MOLOTOV:
			format(fdesc, sizeof(fdesc), Przedmiot, którego mo¿na u¿yæ do podpalenia budynku.\nPo wejœciu do interiora i u¿yciu przedmiotu wybuchnie w nim po¿ar.\nDo odegrania tego typu akcji wymagana jest odpowiednia iloœæ stra¿aków na duty.\nPamiêtaj, aby odegraæ odpowiedni¹ akcjê RP przed jego u¿yciem.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_PICKLOCK:
			format(fdesc, sizeof(fdesc), Paczka wytrychów, którym przy odrobinie szczêœcia otworzysz drzwi.\nSzansa na otwarcie drzwi: %d/%\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_OPTIWAND:
			format(fdesc, sizeof(fdesc), Kamera, której s³u¿by specjalne u¿ywaj¹ do sprawdzania naro¿ników oraz szczelin.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_CRAFT:
			format(fdesc, sizeof(fdesc), Przedmiot nie jest u¿ywany. Zg³oœ siê do moderacji po ciastko.)
		case ITEM_FLASHBANG:
			format(fdesc, sizeof(fdesc), Granat hukowo-b³yskowy.\nPo u¿yciu w pickupie interiora wytworzy og³uszaj¹cy i oœlepiaj¹cy napastników efekt eksplozji.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_FLASHLIGHT:
			format(fdesc, sizeof(fdesc), Latarka typowych rozmiarów, u¿ywana najczêœciej przez s³u¿by porz¹dkowe.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_WEAPON_AT:
			format(fdesc, sizeof(fdesc), Przedmiot nie jest u¿ywany. Zg³oœ siê do moderacji po ciastko.)
		case ITEM_BLADE:
			format(fdesc, sizeof(fdesc), Przedmiot nie jest u¿ywany. Zg³oœ siê do moderacji po ciastko.)
		case ITEM_AQUALUNG:
			format(fdesc, sizeof(fdesc), Przedmiot nie jest u¿ywany. Zg³oœ siê do moderacji po ciastko.)
		case ITEM_TIRE:
			format(fdesc, sizeof(fdesc), Opona, któr¹ zawsze warto mieæ w baga¿niku.\nPo u¿yciu w pojeŸdzie mo¿na wymieniæ flaka, je¿eli siê go z³apa³o.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_NUTRIENT:
			format(fdesc, sizeof(fdesc), Od¿ywki lub sterydy, u³atwiaj¹ce trening twojej postaci i przyspieszaj¹ce stopieñ, w jakim zdobywa siê si³ê.\nWystarcza na %d minut(y) treningu.\n\nOpis przedmiotu:\n\t %s, v2, desc)
		case ITEM_TAGGER:
			format(fdesc, sizeof(fdesc), Farba w sprayu u¿ywana do malowania wrzut na œcianach.\nIloœæ farby w puszce: %d ml.\n\nOpis przedmiotu:\n\t %s, v2, desc)
		case ITEM_DECKOFCARDS:
			format(fdesc, sizeof(fdesc), Karty do grania.\nPo u¿yciu bêdziesz móg³ zagraæ w Blackjacka z osobami wokó³ Ciebie.\nPodczas u¿ywania kart nie mo¿esz byæ w trakcie oferowania/przyjmowania oferty, hospitalizacji, malowania pojazdu, etc.\n\nOpis przedmiotu: %s, desc)
		case ITEM_LSPAD:
			format(fdesc, sizeof(fdesc), Urz±dzenie elektroniczne posiadaj±ce wiele funkcji, od pogody i kalendarza do zarz±dzania elektronicznymi zamkami i sprawdzania stanu konta bankowego.\nTapeta: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_ELOCK:
			format(fdesc, sizeof(fdesc), Zamek Elektroniczny. Pozawala na zdalne kontrolowanie drzwi\npoprzez LSPad.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_PAGER:
			format(fdesc, sizeof(fdesc), Pager. Pozwala na odebranie wiadomo¶ci o chêci kontaktu z Tob± bez p³acenia za drogie po³aczenie telefoniczne.\nNumer: %d\n\nOpis przedmiotu:\n\t %s, v1, desc)
		case ITEM_ROPE:
			format(fdesc, sizeof(fdesc), Zwyczajny zwój liny pozwalaj¹cy na unieruchomienie innej osoby, lub wykonanie prymitywnego stryczka.\n/lina (ID Gracza) \n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_HEADBAG:
			format(fdesc, sizeof(fdesc), Worek przypomiaj¹cy te do przechowywania zbo¿a - mo¿esz go za³o¿yæ na czyj¹œ g³owê. \n/worek (ID gracza)\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_GAG:
			format(fdesc, sizeof(fdesc), Knebel, który mo¿esz w³o¿yæ komuœ do ust - mo¿esz go za³o¿yæ na czyj¹œ g³owê. \n/knebel (ID gracza)\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_HOMEPHONESET:
			format(fdesc, sizeof(fdesc), Nowy telefon stacjonarny, mo¿esz go u¿yæ we w³asnym domu aby móc dzwoniæ na inne telefony.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_TUNEPART:
			format(fdesc, sizeof(fdesc), Czêœæ tuningowa do pojazdu, która po zamontowaniu zwiêkszy nieco osi¹gi maszyny.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_ROULETTE:
			format(fdesc, sizeof(fdesc), Ruletka która losuje liczbê z przedzia³u 0-36 (( /ruletka )).\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_PUTABLE:
			format(fdesc, sizeof(fdesc), Przedmiot, który po u¿yciu tworzy obiekt na œwiecie 0 mo¿liwy do edycji poprzez komendê \n/osel.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_FAKEPAPERS:
			format(fdesc, sizeof(fdesc), Przedmiot po u¿yciu którego zmieniaj¹ siê Twoje dane personalne.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_SEEDS:
			format(fdesc, sizeof(fdesc), Nasiona umo¿liwiaj¹ce zasadzenie krzaka marihuany.\nAby zasadziæ krzak u¿yj go przy obiekcie doniczki.\n\nOpis przedmiotu:\n\t %s, desc)
		case ITEM_CARD:
			format(fdesc, sizeof(fdesc), Karta p³atnicza z balansem firmowym.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_OXYGEN:
			format(fdesc, sizeof(fdesc), Butla tlenowa s³u¿¹ca do nurkowania.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_SURFBOARD:
			format(fdesc, sizeof(fdesc), Deska surfingowa, u¿yj by postawiæ j¹ na wodzie.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_BOMB:
			format(fdesc, sizeof(fdesc), Bomba, któr¹ mo¿na zamontowaæ w pojeŸdzie, po odpaleniu silnika eksploduje.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_SILENCER:
			format(fdesc, sizeof(fdesc), T³umik, który mo¿esz za³o¿yæ na dowoln¹ broñ kalibru 9mm.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_WORM:
			format(fdesc, sizeof(fdesc), Robak, którego mo¿esz za³o¿yæ na wêdkê, by rozpocz¹æ ³owienie.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_BANDAGE:
			format(fdesc, sizeof(fdesc), Banda¿, który po u¿yciu zatamuje krwawienie Twojej postaci.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_PLANT:
			format(fdesc, sizeof(fdesc), Nasiono, które po u¿yciu pozwoli Ci zasadziæ w swoim pobli¿u jak¹œ roœlinê\nTyp roœliny: %d.\n\nOpis przedmiotu:\n\t%s, v1, desc)
		case ITEM_SPECIAL:
			format(fdesc, sizeof(fdesc), Przedmiot OOC, który dodaje pewne korzyœci.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_PRESENT:
			format(fdesc, sizeof(fdesc), Upominek zapakowany w kolorowy papier.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_SAFE:
			format(fdesc, sizeof(fdesc), Bezpieczony schowek na pieniadze chroniony 5-cyfrowym kodem.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_COOK_INGREDIENT:
			format(fdesc, sizeof(fdesc), Sk³adnik do tworzenia narkotyków.\n\nOpis przedmiotu:\n\t%s, desc)
		case ITEM_COOK_OBJECT:
			format(fdesc, sizeof(fdesc), Kuchenka gazowa przeznaczona do gotowania narkotyków.\n\nOpis przedmiotu:\n\t%s, desc)
 	
	)
	
	mtitle(64)
	format(mtitle, sizeof(mtitle), Informacje » %s, ItemInfo(itemid)(iName))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, mtitle, fdesc, OK, )
	return 1
)

stock SetItemDesc(item_uid, desc())
(
	printf(desc: %d, %s, item_uid, desc)
	mysql_query_format(UPDATE hrp_items SET item_desc = %s WHERE item_uid = %d, desc, item_uid)
	return 1
)

DropAllPlayerItems(playerid)
(
	foreach(Items, itemid)
	(
		prevIter
		if(ItemInfo(itemid)(iUID))
		(
			if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
			(
				if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
				(
					Float:PosX, Float:PosY, Float:PosZ, Float:PosA, virtual_world = GetPlayerVirtualWorld(playerid)

					GetPlayerPos(playerid, PosX, PosY, PosZ)
					GetPlayerFacingAngle(playerid, PosA)

					mysql_query_format(UPDATE hrp_items SET item_posx = %f, item_posy = %f, item_posz = %f, item_place = %d, item_world = %d WHERE item_uid = %d LIMIT 1, PosX, PosY, PosZ, PLACE_NONE, virtual_world, ItemInfo(itemid)(iUID))

					object_id
					if(ItemInfo(itemid)(iType) == ITEM_WEAPON || ItemInfo(itemid)(iType) == ITEM_PAINT)
					(
						object_id = CreateDynamicObject(WeaponModel(ItemInfo(itemid)(iValue1)), PosX, PosY, PosZ - 1.0, 80.0, 0.0, -PosA, virtual_world, -1, -1, 80.0)

					)
					else if(ItemInfo(itemid)(iType) == ITEM_TUNING)
					(
						object_id = CreateDynamicObject(ItemInfo(itemid)(iValue1), PosX, PosY, PosZ - 0.5, 0.0, 0.0, -PosA, virtual_world, -1, -1, 80.0)
					)
					else
					(
						object_id = CreateDynamicObject(ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjModel), PosX, PosY, PosZ - 1.0, ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjRotX), ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeObjRotY), -PosA, virtual_world, -1, -1, 80.0)
					)

					Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, (ItemInfo(itemid)(iUID) * -1))
					Streamer_Update(playerid)
				)
				else if(IsPlayerInAnyVehicle(playerid))
				(
					vehid = GetPlayerVehicleID(playerid)
					mysql_query_format(UPDATE hrp_items SET item_place = %d, item_owner = %d WHERE item_uid = %d LIMIT 1, PLACE_VEHICLE, CarInfo(vehid)(cUID), ItemInfo(itemid)(iUID))
				)
				// Zwolnij miejsce dla czegoœ, co mo¿e byæ u¿yte
				ItemInfo(itemid)(iUID) = 0
				ItemInfo(itemid)(iValue1) = 0
				ItemInfo(itemid)(iValue2) = 0
				ItemInfo(itemid)(iType) = 0

				ItemInfo(itemid)(iPlace) = 0
				ItemInfo(itemid)(iOwner) = 0

				ItemInfo(itemid)(iUsed) = 0
				ItemInfo(itemid)(iChecked) = false

				// Itter_Remove(Items, itemid)
				// U¿yæ SafeRemove ¿eby usun¹æ iteracje w œrodku pêtli z t¹ iteracj¹.
				Iter_SafeRemove(Items, itemid, prevIter)
				itemid = prevIter
			)
		)
	)
	return 1
)

stock ListPlayerTrunkItems(playerid, vehid)
(
	if(!PlayerCache(playerid)(pRaising))	return 1
	
	data(64), list_items(512)
	
	PlayerCache(playerid)(pRaising) = false
	TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
	
	if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz podnosiæ przedmiotów z tego pojazdu., OK, )
		return 1
	)
	if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
	(
		if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz podnosiæ przedmiotów z tego pojazdu., OK, )
			return 1
		)
	)
	
	mysql_query_format(SELECT item_uid, item_name, item_weight FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_VEHICLE, CarInfo(vehid)(cUID))
	
	new	item_uid, item_name(32), Float:item_weight

	mysql_store_result()
   	while(mysql_fetch_row(data, |))
   	(
	 	sscanf(data, p(|)ds(32)f, item_uid, item_name, item_weight)
	 	format(list_items, sizeof(list_items), %s\n%d\t%.2f\t%s, list_items, item_uid, item_weight, item_name)
	)
  	mysql_free_result()
  	if(!strlen(list_items))
  	(
	 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych przedmiotów w baga¿niku., OK, )
	 	return 1
	)
	ShowPlayerDialog(playerid, D_RAISE_ITEM, DIALOG_STYLE_LIST, Przedmioty w baga¿niku, list_items, Podnieœ, Anuluj)
	return 1
)

stock TrackPhone(playerid, number)
(
	Float:x, Float:y, Float:z
	
	foreach(Items, itemid)
	(
		if(ItemInfo(itemid)(iUID))
		(
			if(ItemInfo(itemid)(iType) == ITEM_PHONE && ItemInfo(itemid)(iValue1) == number && ItemInfo(itemid)(iUsed))
			(
				if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER)
				(
					GetPlayerPos(playerid, x, y, z)
					PlayerCache(playerid)(pTrackingNumber) = ItemInfo(itemid)(iValue2)
					SetPlayerCheckpoint(playerid, x, y, z, 5.0)
					return 1
				)
				else if(ItemInfo(itemid)(iPlace) == PLACE_VEHICLE)
				(
					vehid = GetVehicleID(ItemInfo(itemid)(iOwner))
					if(vehid == INVALID_VEHICLE_ID)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pojazd, w którym znajduje siê telefon jest aktualnie odspawnowany.\nNamierzanie bêdzie mo¿liwe kiedy pojazd pojawi siê na mapie., OK, )
						PlayerCache(playerid)(pTrackingNumber) = 0
						Checkpoint(playerid) = 0
						DisablePlayerCheckpoint(playerid)
						return 0
					)
					GetVehiclePos(vehid, x, y, z)
					PlayerCache(playerid)(pTrackingNumber) = ItemInfo(itemid)(iValue2)
					SetPlayerCheckpoint(playerid, x, y, z, 5.0)
					return 1
				)
			)
		)
	)
	return 0
)

stock PlayerHaveItem(playerid, item_type)
(
	have = false
	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID) != 0)
		(
			if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
			(
				if(ItemInfo(i)(iType) == item_type)
				(
					have = true
					break
				)
			)
		)
	)
	return have
)

stock GetPlayerItemTypeCount(playerid, item_type)
(
	count = 0
	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID) != 0)
		(
			if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
			(
				if(ItemInfo(i)(iType) == item_type)
				(
					count++
				)
			)
		)
	)
	return count
)

stock GetPlayerItemByType(playerid, item_type)
(
	itemid = 0
	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID) != 0)
		(
			if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
			(
				if(ItemInfo(i)(iType) == item_type)
				(
					itemid = i
				)
			)
		)
	)
	return itemid
)

stock GetItemID(itemuid)
(
	itemid
  	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID) == itemuid)
		(
			itemid = i
			break
		)
	)
	return itemid
)

stock GenerateDrugNameByItemid(itemid)
(
	name(32), portion = ItemInfo(itemid)(iValue2)
	if(ItemInfo(itemid)(iValue1) == DRUG_MARIHUANA)
	(
		format(name, sizeof(name), Marihuana %d g., portion)
	)
	else if(ItemInfo(itemid)(iValue1) == DRUG_COCAINE)
	(
		format(name, sizeof(name), Kokaina %d g., portion)
	)
	else if(ItemInfo(itemid)(iValue1) == DRUG_HEROIN)
	(
		format(name, sizeof(name), Heroina %d g., portion)
	)
	else if(ItemInfo(itemid)(iValue1) == DRUG_AMPHETAMINE)
	(
		format(name, sizeof(name), Amfetamina %d g., portion)
	)
	else if(ItemInfo(itemid)(iValue1) == DRUG_CRACK)
	(
		format(name, sizeof(name), Crack %d g., portion)
	)
	else if(ItemInfo(itemid)(iValue1) == DRUG_LSD)
	(
		format(name, sizeof(name), LSD %d g., portion)
	)
	else if(ItemInfo(itemid)(iValue1) == DRUG_SHROOMS)
	(
		format(name, sizeof(name), Grzybki %d g., portion)
	)
	else if(ItemInfo(itemid)(iValue1) == DRUG_MDMA)
	(
		format(name, sizeof(name), Extasy %d g., portion)
	)
	else if(ItemInfo(itemid)(iValue1) == DRUG_METAAMP)
	(
		format(name, sizeof(name), Metamfetamina %d g., portion)
	)
	else
	(
		format(name, sizeof(name), %s, ItemInfo(itemid)(iName))
	)

	format(ItemInfo(itemid)(iName), 32, %s, name)
	mysql_query_format(UPDATE hrp_items SET item_name = %s WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID))
	return 1
)

stock items_LoadTextdraws(playerid)
(
	/*
		Nowy interfejs przedmiotów, lepiej tutaj to upakowaæ, ni¿ zajebaæ póŸniej po³owê trafficu.
	*/
	
	pLicenseBall1(playerid) = CreatePlayerTextDraw(playerid,144.000000, 133.000000, ld_pool:ball)
	PlayerTextDrawBackgroundColor(playerid,pLicenseBall1(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseBall1(playerid), 4)
	PlayerTextDrawLetterSize(playerid,pLicenseBall1(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseBall1(playerid), -523930881)
	PlayerTextDrawSetOutline(playerid,pLicenseBall1(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseBall1(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseBall1(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseBall1(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseBall1(playerid), -523930881)
	PlayerTextDrawTextSize(playerid,pLicenseBall1(playerid), 40.000000, 35.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseBall1(playerid), 0)

	pLicenseBall2(playerid) = CreatePlayerTextDraw(playerid,442.000000, 133.000000, ld_pool:ball)
	PlayerTextDrawBackgroundColor(playerid,pLicenseBall2(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseBall2(playerid), 4)
	PlayerTextDrawLetterSize(playerid,pLicenseBall2(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseBall2(playerid), -523930881)
	PlayerTextDrawSetOutline(playerid,pLicenseBall2(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseBall2(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseBall2(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseBall2(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseBall2(playerid), -523930881)
	PlayerTextDrawTextSize(playerid,pLicenseBall2(playerid), 40.000000, 35.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseBall2(playerid), 0)

	pLicenseBall3(playerid) = CreatePlayerTextDraw(playerid,442.000000, 306.000000, ld_pool:ball)
	PlayerTextDrawBackgroundColor(playerid,pLicenseBall3(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseBall3(playerid), 4)
	PlayerTextDrawLetterSize(playerid,pLicenseBall3(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseBall3(playerid), -523930881)
	PlayerTextDrawSetOutline(playerid,pLicenseBall3(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseBall3(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseBall3(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseBall3(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseBall3(playerid), -523930881)
	PlayerTextDrawTextSize(playerid,pLicenseBall3(playerid), 40.000000, -34.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseBall3(playerid), 0)

	pLicenseBall4(playerid) = CreatePlayerTextDraw(playerid,144.000000, 305.000000, ld_pool:ball)
	PlayerTextDrawBackgroundColor(playerid,pLicenseBall4(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseBall4(playerid), 4)
	PlayerTextDrawLetterSize(playerid,pLicenseBall4(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseBall4(playerid), -523930881)
	PlayerTextDrawSetOutline(playerid,pLicenseBall4(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseBall4(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseBall4(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseBall4(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseBall4(playerid), -523930881)
	PlayerTextDrawTextSize(playerid,pLicenseBall4(playerid), 40.000000, -35.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseBall4(playerid), 0)

	pLicenseBack(playerid) = CreatePlayerTextDraw(playerid,313.000000, 152.000000, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~)
	PlayerTextDrawAlignment(playerid,pLicenseBack(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,pLicenseBack(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseBack(playerid), 1)
	PlayerTextDrawLetterSize(playerid,pLicenseBack(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseBack(playerid), -1)
	PlayerTextDrawSetOutline(playerid,pLicenseBack(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseBack(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseBack(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseBack(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseBack(playerid), -523930881)
	PlayerTextDrawTextSize(playerid,pLicenseBack(playerid), 0.000000, 295.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseBack(playerid), 0)

	pLicenseBorder1(playerid) = CreatePlayerTextDraw(playerid,313.000000, 135.000000, ~n~~n~)
	PlayerTextDrawAlignment(playerid,pLicenseBorder1(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,pLicenseBorder1(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseBorder1(playerid), 1)
	PlayerTextDrawLetterSize(playerid,pLicenseBorder1(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseBorder1(playerid), -1)
	PlayerTextDrawSetOutline(playerid,pLicenseBorder1(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseBorder1(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseBorder1(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseBorder1(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseBorder1(playerid), -523930881)
	PlayerTextDrawTextSize(playerid,pLicenseBorder1(playerid), 0.000000, -306.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseBorder1(playerid), 0)

	pLicenseBorder2(playerid) = CreatePlayerTextDraw(playerid,313.000000, 285.000000, ~n~~n~)
	PlayerTextDrawAlignment(playerid,pLicenseBorder2(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,pLicenseBorder2(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseBorder2(playerid), 1)
	PlayerTextDrawLetterSize(playerid,pLicenseBorder2(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseBorder2(playerid), -1)
	PlayerTextDrawSetOutline(playerid,pLicenseBorder2(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseBorder2(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseBorder2(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseBorder2(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseBorder2(playerid), -523930881)
	PlayerTextDrawTextSize(playerid,pLicenseBorder2(playerid), 0.000000, -306.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseBorder2(playerid), 0)

	pLicenseBorder3(playerid) = CreatePlayerTextDraw(playerid,162.000000, 152.000000, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~)
	PlayerTextDrawAlignment(playerid,pLicenseBorder3(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,pLicenseBorder3(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseBorder3(playerid), 1)
	PlayerTextDrawLetterSize(playerid,pLicenseBorder3(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseBorder3(playerid), -1)
	PlayerTextDrawSetOutline(playerid,pLicenseBorder3(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseBorder3(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseBorder3(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseBorder3(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseBorder3(playerid), -523930881)
	PlayerTextDrawTextSize(playerid,pLicenseBorder3(playerid), 0.000000, 29.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseBorder3(playerid), 0)

	pLicenseBorder4(playerid) = CreatePlayerTextDraw(playerid,464.000000, 152.000000, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~)
	PlayerTextDrawAlignment(playerid,pLicenseBorder4(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,pLicenseBorder4(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseBorder4(playerid), 1)
	PlayerTextDrawLetterSize(playerid,pLicenseBorder4(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseBorder4(playerid), -1)
	PlayerTextDrawSetOutline(playerid,pLicenseBorder4(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseBorder4(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseBorder4(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseBorder4(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseBorder4(playerid), -523930881)
	PlayerTextDrawTextSize(playerid,pLicenseBorder4(playerid), 0.000000, 29.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseBorder4(playerid), 0)

	pLicenseStar(playerid) = CreatePlayerTextDraw(playerid,233.000000, 170.000000, ld_drv:silver)
	PlayerTextDrawBackgroundColor(playerid,pLicenseStar(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseStar(playerid), 4)
	PlayerTextDrawLetterSize(playerid,pLicenseStar(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseStar(playerid), -156)
	PlayerTextDrawSetOutline(playerid,pLicenseStar(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseStar(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseStar(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseStar(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseStar(playerid), -1)
	PlayerTextDrawTextSize(playerid,pLicenseStar(playerid), 152.000000, 127.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseStar(playerid), 0)

	pLicenseHeading1(playerid) = CreatePlayerTextDraw(playerid,166.000000, 136.000000, Los Santos)
	PlayerTextDrawBackgroundColor(playerid,pLicenseHeading1(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseHeading1(playerid), 1)
	PlayerTextDrawLetterSize(playerid,pLicenseHeading1(playerid), 0.500000, 2.100001)
	PlayerTextDrawColor(playerid,pLicenseHeading1(playerid), 255)
	PlayerTextDrawSetOutline(playerid,pLicenseHeading1(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseHeading1(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseHeading1(playerid), 0)
	PlayerTextDrawSetSelectable(playerid,pLicenseHeading1(playerid), 0)

	/*
		przyklad do tego ponizej - na przyszlosc, potem ten komentarz wyjebiemy
		
		~l~NM: ~b~Cassie Barnes~n~
		~l~ID: ~b~012 345 678~n~
		~l~Class ~b~D
	*/

	pLicenseInfo(playerid) = CreatePlayerTextDraw(playerid,301.000000, 197.000000, _)
	PlayerTextDrawAlignment(playerid,pLicenseInfo(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,pLicenseInfo(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseInfo(playerid), 1)
	PlayerTextDrawLetterSize(playerid,pLicenseInfo(playerid), 0.519999, 1.399999)
	PlayerTextDrawColor(playerid,pLicenseInfo(playerid), -1)
	PlayerTextDrawSetOutline(playerid,pLicenseInfo(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseInfo(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseInfo(playerid), 0)
	PlayerTextDrawSetSelectable(playerid,pLicenseInfo(playerid), 0)

	pLicenseHeading2(playerid) = CreatePlayerTextDraw(playerid,406.000000, 137.000000, Enhanced Driver License)
	PlayerTextDrawAlignment(playerid,pLicenseHeading2(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,pLicenseHeading2(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseHeading2(playerid), 1)
	PlayerTextDrawLetterSize(playerid,pLicenseHeading2(playerid), 0.519999, 1.500000)
	PlayerTextDrawColor(playerid,pLicenseHeading2(playerid), 255)
	PlayerTextDrawSetOutline(playerid,pLicenseHeading2(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseHeading2(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseHeading2(playerid), 0)
	PlayerTextDrawUseBox(playerid,pLicenseHeading2(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseHeading2(playerid), 0)
	PlayerTextDrawTextSize(playerid,pLicenseHeading2(playerid), 0.000000, 138.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseHeading2(playerid), 0)

	pLicenseLine(playerid) = CreatePlayerTextDraw(playerid,159.000000, 165.000000, ld_otb2:butna)
	PlayerTextDrawBackgroundColor(playerid,pLicenseLine(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseLine(playerid), 4)
	PlayerTextDrawLetterSize(playerid,pLicenseLine(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,pLicenseLine(playerid), -1)
	PlayerTextDrawSetOutline(playerid,pLicenseLine(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseLine(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseLine(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseLine(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseLine(playerid), 255)
	PlayerTextDrawTextSize(playerid,pLicenseLine(playerid), 310.000000, 3.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseLine(playerid), 0)
	
	/*pLicenseButton(playerid) = CreatePlayerTextDraw(playerid,310.000000, 323.000000, Okej)
	PlayerTextDrawAlignment(playerid,pLicenseButton(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,pLicenseButton(playerid), 255)
	PlayerTextDrawFont(playerid,pLicenseButton(playerid), 1)
	PlayerTextDrawLetterSize(playerid,pLicenseButton(playerid), 0.549998, 1.600000)
	PlayerTextDrawColor(playerid,pLicenseButton(playerid), -1)
	PlayerTextDrawSetOutline(playerid,pLicenseButton(playerid), 0)
	PlayerTextDrawSetProportional(playerid,pLicenseButton(playerid), 1)
	PlayerTextDrawSetShadow(playerid,pLicenseButton(playerid), 1)
	PlayerTextDrawUseBox(playerid,pLicenseButton(playerid), 1)
	PlayerTextDrawBoxColor(playerid,pLicenseButton(playerid), 150)
	PlayerTextDrawTextSize(playerid,pLicenseButton(playerid), 0.000000, 78.000000)
	PlayerTextDrawSetSelectable(playerid,pLicenseButton(playerid), 1)*/
	
	return 1
)

stock doc_gInterfaceShow(playerid, forplayerid)
(
	// Dodaj formatowanie poszczególnych textdrawów
	
	PlayerTextDrawShow(forplayerid, pLicenseLine(forplayerid))
	//
	string(256)
	format(string, sizeof(string), ~l~NM: ~b~%s~n~~l~ID: ~b~012 345 678~n~ ~l~Class ~b~D, PlayerName(playerid))
	PlayerTextDrawShow(forplayerid, pLicenseInfo(forplayerid))
	PlayerTextDrawSetString(forplayerid, pLicenseInfo(forplayerid), string)
	//
	PlayerTextDrawShow(forplayerid, pLicenseHeading2(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseHeading1(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseStar(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseBorder4(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseBorder3(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseBorder2(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseBorder1(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseBack(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseBall4(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseBall3(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseBall2(forplayerid))
	PlayerTextDrawShow(forplayerid, pLicenseBall1(forplayerid))
	//PlayerTextDrawShow(forplayerid, pLicenseButton(forplayerid))
	
	//PlayerCache(forplayerid)(pUseGUI) = true
	PlayerCache(forplayerid)(pCurrentGUI) = GUI_TYPE_DOCUMENT_DRIVING
	SetTimerEx(doc_AutoClose, 7000, 0, d, forplayerid)
	//SelectTextDraw(forplayerid, 0x00FF00FF)
	
	return 1
)

stock doc_gInterfaceHide(playerid)
(
	//PlayerTextDrawHide(playerid, pLicenseButton(playerid))
	PlayerTextDrawHide(playerid, pLicenseLine(playerid))
	PlayerTextDrawHide(playerid, pLicenseInfo(playerid))
	PlayerTextDrawHide(playerid, pLicenseHeading2(playerid))
	PlayerTextDrawHide(playerid, pLicenseHeading1(playerid))
	PlayerTextDrawHide(playerid, pLicenseStar(playerid))
	PlayerTextDrawHide(playerid, pLicenseBorder4(playerid))
	PlayerTextDrawHide(playerid, pLicenseBorder3(playerid))
	PlayerTextDrawHide(playerid, pLicenseBorder2(playerid))
	PlayerTextDrawHide(playerid, pLicenseBorder1(playerid))
	PlayerTextDrawHide(playerid, pLicenseBack(playerid))
	PlayerTextDrawHide(playerid, pLicenseBall4(playerid))
	PlayerTextDrawHide(playerid, pLicenseBall3(playerid))
	PlayerTextDrawHide(playerid, pLicenseBall2(playerid))
	PlayerTextDrawHide(playerid, pLicenseBall1(playerid))
	
	//PlayerCache(playerid)(pUseGUI) = false
	PlayerCache(playerid)(pCurrentGUI) = GUI_TYPE_NONE
	//CancelSelectTextDraw(playerid)
	
	return 1
)

forward doc_AutoClose(playerid)
public doc_AutoClose(playerid)
(
	if(PlayerCache(playerid)(pCurrentGUI) != GUI_TYPE_NONE)
		doc_gInterfaceHide(playerid)
	return 1
)

stock isItemIsHaircut(item_id)
(
	// Spradzamy czy przedmiot jest w³osami ?
	bool:isHaircut = false, buffer(256)
	format(buffer, sizeof(buffer), SELECT access_model FROM hrp_access WHERE access_uid = %d, ItemInfo(item_id)(iValue1))
	mysql_query(buffer)
	mysql_store_result()
	model_id = mysql_fetch_int()
	mysql_free_result()
	
	for(hair_id = 0 hair_id ( sizeof(HairIDs) hair_id++)
	(
		if(model_id == HairIDs(hair_id))
		(
			isHaircut = true
			break
		)
	)
	
	return isHaircut
)

stock getSafeHash(code) (
	c1 = (code / 10000)											// 1st digit
	c2 = (code / 1000)	- c1*10									// 2nd digit
	c3 = (code / 100)	- c1*100  - c2*10						// 3rd digit
	c4 = (code / 10)	- c1*1000 - c2*100 - c3*10				// 4th digit
	c5 = (code)			- c1*10000- c2*1000- c3*100 - c4*10		// 5th digit

	return getHashValue(c1) * getHashValue(c2) + getHashValue(c3) + getHashValue(c4) - getHashValue(c5) 
)

stock getHashValue(digit) (
	switch(digit)
	(
		case 0: return 61
		case 1: return 100
		case 2: return 51
		case 3: return 26
		case 4: return 40
		case 5: return 95
		case 6: return 79
		case 7: return 87
		case 8: return 88
		case 9: return 34
		default: return 0
	)
	return 0
)