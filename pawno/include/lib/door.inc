public CreateDoor(Float:EnterX, Float:EnterY, Float:EnterZ, Float:EnterA, EnterInt, EnterVW, DoorName())
(
	door_name(128)
	
	mysql_real_escape_string(DoorName, door_name)
	mysql_query_format(INSERT INTO hrp_doors (door_name, door_enterx, door_entery, door_enterz, door_entera, door_enterint, door_entervw) VALUES (%s, %f, %f, %f, %f, %d, %d), door_name, EnterX, EnterY, EnterZ, EnterA, EnterInt, EnterVW)
	
	uid = mysql_insert_id(), gameid = CreatePickup(1318, 2, EnterX, EnterY, EnterZ, EnterVW)
	LoadDoor(gameid, uid)
	
	Itter_Add(Doors, gameid)
	return gameid
)

public LoadDoor(gameid, uid)
(
	data(512), null(32)
	mysql_query_format(SELECT * FROM hrp_doors WHERE door_uid = %d, uid)
	
 	print((load) Rozpoczynam proces wczytywania statystyk drzwi...)

	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ddds(32)ffffddffffdddds(128)dddds(32)dddddddd,
		DoorData(gameid)(dUID),
		
		DoorData(gameid)(dOwner),
		DoorData(gameid)(dOwnerType),
		
		DoorData(gameid)(dName),
		
		DoorData(gameid)(dEnterX),
		DoorData(gameid)(dEnterY),
		DoorData(gameid)(dEnterZ),
		DoorData(gameid)(dEnterAng),
		DoorData(gameid)(dEnterInt),
		DoorData(gameid)(dEnterVW),
		
		DoorData(gameid)(dExitX),
		DoorData(gameid)(dExitY),
		DoorData(gameid)(dExitZ),
		DoorData(gameid)(dExitAng),
		DoorData(gameid)(dExitInt),
		DoorData(gameid)(dExitVW),
		
		DoorData(gameid)(dPickupID),
		DoorData(gameid)(dLocked),
		
		DoorData(gameid)(dAudioURL),
		
		DoorData(gameid)(dEnterPay),
		DoorData(gameid)(dGarage),
		
		DoorData(gameid)(dAccess),
		DoorData(gameid)(dBurnTime),
		
		null,
		
		DoorData(gameid)(dWood),
		DoorData(gameid)(dRock),
		DoorData(gameid)(dElock),
		DoorData(gameid)(dTime),
		DoorData(gameid)(dBlocked),
		DoorData(gameid)(dLimit),
		DoorData(gameid)(dCost),
		DoorData(gameid)(dPaintball))
		
		DoorData(gameid)(dBell) = false
		DoorData(gameid)(dDoorEdited) = 0
	)
	mysql_free_result()

	printf((load) Wczytano statystyki drzwi %s (SampID: %d, UID: %d) pomyœlnie., DoorData(gameid)(dName), gameid, DoorData(gameid)(dUID))
	return 1
)

public SaveDoor(gameid, what)
(
 	query(256), main_query(512)
 	format(main_query, sizeof(main_query), UPDATE hrp_doors SET)
	if(what & SAVE_DOOR_ENTER)
	(
		// Pozycja wejœcia
		format(query, sizeof(query),  door_enterx = %f, door_entery = %f, door_enterz = %f, door_entera = %f, door_enterint = %d, door_entervw = %d,
		DoorData(gameid)(dEnterX),
		DoorData(gameid)(dEnterY),
		DoorData(gameid)(dEnterZ),
		DoorData(gameid)(dEnterAng),
		DoorData(gameid)(dEnterInt),
		DoorData(gameid)(dEnterVW))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_DOOR_EXIT)
	(
		// Pozycja wyjœcia
		format(query, sizeof(query),  door_exitx = %f, door_exity = %f, door_exitz = %f, door_exita = %f, door_exitint = %d, door_exitvw = %d,
		DoorData(gameid)(dExitX),
		DoorData(gameid)(dExitY),
		DoorData(gameid)(dExitZ),
		DoorData(gameid)(dExitAng),
		DoorData(gameid)(dExitInt),
		DoorData(gameid)(dExitVW))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_DOOR_THINGS)
	(
		// Pozosta³e (nazwa, w³aœciciel, model pickupa, koszt wstêpu, gara¿, akcesoria, czas p³oniêcia)
		format(query, sizeof(query),  door_name = %s, door_owner = %d, door_ownertype = %d, door_pickup = %d, door_enterpay = %d, door_garage = %d, door_access = %d, door_burntime = %d, door_wood = %d, door_rock = %d, door_elock = %d, door_cost = %d,
		DoorData(gameid)(dName),
		DoorData(gameid)(dOwner),
		DoorData(gameid)(dOwnerType),
		DoorData(gameid)(dPickupID),
		DoorData(gameid)(dEnterPay),
		DoorData(gameid)(dGarage),
		DoorData(gameid)(dAccess),
		DoorData(gameid)(dBurnTime),
		DoorData(gameid)(dWood),
		DoorData(gameid)(dRock),
		DoorData(gameid)(dElock),
		DoorData(gameid)(dCost))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_DOOR_PAINTBALL)
	(
		//ustalenie drzwi na paintball
		format(query, sizeof(query),  door_paintball = %d ,
		DoorData(gameid)(dPaintball))
		
		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_DOOR_AUDIO)
	(
		// Link do muzyki spoza gry
		format(query, sizeof(query),  door_audiourl = %s,
		DoorData(gameid)(dAudioURL))
		
   		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_DOOR_LOCK)
	(
		// Zamkniêcie drzwi
		format(query, sizeof(query),  door_lock = %d,
		DoorData(gameid)(dLocked))
		
		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_DOOR_LIMITS)
	(
		//zapisz blokadê tworzenia obiektów
		format(query, sizeof(query),  door_blocked = %d, door_limit=%d ,
		DoorData(gameid)(dBlocked), DoorData(gameid)(dLimit))
		
		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	format(query, sizeof(query),  WHERE door_uid = %d LIMIT 1, DoorData(gameid)(dUID))
	strcat(main_query, query, sizeof(main_query))
	
	mysql_query(main_query)
	return 1
)

public DeleteDoor(gameid)
(
	object_counts = MAX_OBJECTS, label_counts = CountDynamic3DTextLabels()
	mysql_query_format(DELETE FROM hrp_doors WHERE door_uid = %d, DoorData(gameid)(dUID))

	// Usuñ stare obiekty z tego VW (jeœli s¹)
	mysql_query_format(DELETE FROM hrp_objects WHERE object_world = %d, DoorData(gameid)(dUID))

	for (object_id = 0 object_id (= object_counts object_id++)
	(
 		if(IsValidDynamicObject(object_id))
   		(
			if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID, DoorData(gameid)(dUID)))
			(
				DestroyDynamicObject(object_id)
	  		)
		)
	)
	
	// Usuñ 3d teksty z tych drzwi
	mysql_query_format(DELETE FROM hrp_3dlabels WHERE label_world = %d, DoorData(gameid)(dUID))
	
	// usun defaultsy
	mysql_query_format(DELETE FROM hrp_door_defaults WHERE default_dooruid = %d, DoorData(gameid)(dUID))
	
	for (label_id = 0 label_id (= label_counts label_id++)
	(
		if(IsValidDynamic3DTextLabel(Text3D:label_id))
		(
			if(Streamer_IsInArrayData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_WORLD_ID, DoorData(gameid)(dUID)))
			(
				DestroyDynamic3DTextLabel(Text3D:label_id)
	  		)
		)
	)
	
	
	// Wyczyœæ magazyn drzwi
	mysql_query_format(DELETE FROM hrp_products WHERE product_dooruid = %d, DoorData(gameid)(dUID))
	
	foreach(Products, product_id)
	(
		if(ProductInfo(product_id)(pUID))
		(
			if(ProductInfo(product_id)(pDoorUID) == DoorData(gameid)(dUID))
			(
				ProductInfo(product_id)(pUID) = 0
				ProductInfo(product_id)(pType) = 0

				ProductInfo(product_id)(pValue1) = 0
				ProductInfo(product_id)(pValue2) = 0

				ProductInfo(product_id)(pPrice) = 0
				ProductInfo(product_id)(pNumber) = 0

				ProductInfo(product_id)(pDoorUID) = 0
			)
		)
	)
	
	// Usuñ zamówienia do tych drzwi
	mysql_query_format(DELETE FROM hrp_packages WHERE package_dooruid = %d, DoorData(gameid)(dUID))
	
	foreach(Packages, package_id)
	(
		if(PackageInfo(package_id)(pUID))
		(
			if(PackageInfo(package_id)(pDoorUID) == DoorData(gameid)(dUID))
			(
				PackageInfo(package_id)(pUID) = 0
				PackageInfo(package_id)(pDoorUID) = 0

				PackageInfo(package_id)(pItemType) = 0

				PackageInfo(package_id)(pItemValue1) = 0
				PackageInfo(package_id)(pItemValue2) = 0

				PackageInfo(package_id)(pItemNumber) = 0
				PackageInfo(package_id)(pItemPrice) = 0
				
				Itter_Remove(Packages, package_id)
			)
		)
	)
	
	if(DoorData(gameid)(dOwnerType) == OWNER_PLAYER)
	(
		foreach(Player, i)
		(
  			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pHouse) == DoorData(gameid)(dUID))
				(
					PlayerCache(i)(pHouse) = 0
				)
			)
		)

		mysql_query_format(UPDATE hrp_characters SET char_house = 0 WHERE char_house = %d, DoorData(gameid)(dUID))
	)
	else if(DoorData(gameid)(dOwnerType) == OWNER_GROUP)
	(
		group_id_fix = GetGroupID(DoorData(gameid)(dOwner))
		if(GroupData(group_id_fix)(gType) == GROUP_HOTEL)
		(
			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					if(PlayerCache(i)(pHotel) == DoorData(gameid)(dUID))
					(
						PlayerCache(i)(pHotel) = 0
					)
				)
			)
			
			mysql_query_format(UPDATE hrp_characters SET char_hotel = 0 WHERE char_hotel = %d, DoorData(gameid)(dUID))
		)
	)
	
	// Jeœli p³onie, usuñ dodatki
	if(DoorData(gameid)(dBurnTime) != 0)
	(
		DestroyDynamicObject(DoorData(gameid)(dFireObject))
		Delete3DTextLabel(Text3D:DoorData(gameid)(dFireLabels))
	)
	DoorData(gameid)(dUID) = 0
	
	DoorData(gameid)(dOwner) = 0
	DoorData(gameid)(dOwnerType) = 0
	
	DoorData(gameid)(dEnterX) = 0.0
	DoorData(gameid)(dEnterY) = 0.0
	DoorData(gameid)(dEnterZ) = 0.0
	DoorData(gameid)(dEnterAng) = 0.0
	DoorData(gameid)(dEnterInt) = 0
	DoorData(gameid)(dEnterVW) = 0
	
	DoorData(gameid)(dExitX) = 0.0
	DoorData(gameid)(dExitY) = 0.0
	DoorData(gameid)(dExitZ) = 0.0
	DoorData(gameid)(dExitAng) = 0.0
	DoorData(gameid)(dExitInt) = 0
	DoorData(gameid)(dExitVW) = 0
	
	DoorData(gameid)(dPickupID) = 0
	DoorData(gameid)(dLocked) = 0
	
	DoorData(gameid)(dEnterPay) = 0
	DoorData(gameid)(dGarage) = false
	
	DoorData(gameid)(dAccess) = 0
	DoorData(gameid)(dBurnTime) = 0
	
	DoorData(gameid)(dWood) = 0
	DoorData(gameid)(dRock) = 0
	DoorData(gameid)(dElock) = 0
	DoorData(gameid)(dRobbed) = false
	
	DoorData(gameid)(dBell) = false
	
	DoorData(gameid)(dPaintball) = false
	
	DestroyPickup(gameid)
	
	Itter_Remove(Doors, gameid)
	return 1
)

public LoadDoors()
(
	gameid, data(512), null(32)
	mysql_query(SELECT * FROM hrp_doors ORDER BY door_uid)
	
 	print((load) Rozpoczynam proces wczytywania drzwi z bazy danych...)

	DoorCache(sDoorCache)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ddds(32)ffffddffffdddds(128)dddds(32)dddddddd,
		DoorCache(dUID),
		
		DoorCache(dOwner),
		DoorCache(dOwnerType),
		
		DoorCache(dName),
		
		DoorCache(dEnterX),
		DoorCache(dEnterY),
		DoorCache(dEnterZ),
		DoorCache(dEnterAng),
		DoorCache(dEnterInt),
		DoorCache(dEnterVW),
		
		DoorCache(dExitX),
		DoorCache(dExitY),
		DoorCache(dExitZ),
		DoorCache(dExitAng),
		DoorCache(dExitInt),
		DoorCache(dExitVW),
		
		DoorCache(dPickupID),
		DoorCache(dLocked),
		
		DoorCache(dAudioURL),
		
		DoorCache(dEnterPay),
		DoorCache(dGarage),

		DoorCache(dAccess),
		DoorCache(dBurnTime),

		null,
		DoorCache(dWood),
		DoorCache(dRock),
		DoorCache(dElock),
		DoorCache(dTime),
		DoorCache(dBlocked),
		DoorCache(dLimit),
		DoorCache(dCost),
		DoorCache(dPaintball))
		
		// -------------------------------------------------------------------------------------------------------------
		
		gameid = CreatePickup(DoorCache(dPickupID), 2, DoorCache(dEnterX), DoorCache(dEnterY), DoorCache(dEnterZ), DoorCache(dEnterVW))

		// -------------------------------------------------------------------------------------------------------------

		DoorData(gameid)(dUID) = DoorCache(dUID)
		DoorData(gameid)(dOwner) = DoorCache(dOwner)
		DoorData(gameid)(dOwnerType) = DoorCache(dOwnerType)
		
		format(DoorData(gameid)(dName), 32, %s, DoorCache(dName))

		DoorData(gameid)(dEnterX) = DoorCache(dEnterX)
		DoorData(gameid)(dEnterY) = DoorCache(dEnterY)
		DoorData(gameid)(dEnterZ) = DoorCache(dEnterZ)
		DoorData(gameid)(dEnterAng) = DoorCache(dEnterAng)
		DoorData(gameid)(dEnterInt) = DoorCache(dEnterInt)
		DoorData(gameid)(dEnterVW) = DoorCache(dEnterVW)
		DoorData(gameid)(dExitX) = DoorCache(dExitX)
		DoorData(gameid)(dExitY) = DoorCache(dExitY)
		DoorData(gameid)(dExitZ) = DoorCache(dExitZ)
		DoorData(gameid)(dExitAng) = DoorCache(dExitAng)
		DoorData(gameid)(dExitInt) = DoorCache(dExitInt)
		DoorData(gameid)(dExitVW) = DoorCache(dExitVW)
		DoorData(gameid)(dPickupID) = DoorCache(dPickupID)
		DoorData(gameid)(dLocked) = DoorCache(dLocked)
		DoorData(gameid)(dTime) = DoorCache(dTime)
		
		format(DoorData(gameid)(dAudioURL), 128, %s, DoorCache(dAudioURL))

		DoorData(gameid)(dEnterPay) = DoorCache(dEnterPay)
		DoorData(gameid)(dGarage) = DoorCache(dGarage)
		DoorData(gameid)(dAccess) = DoorCache(dAccess)
		DoorData(gameid)(dBurnTime) = DoorCache(dBurnTime)
		DoorData(gameid)(dWood) = DoorCache(dWood)
		DoorData(gameid)(dRock) = DoorCache(dRock)
		DoorData(gameid)(dElock) = DoorCache(dElock)
		DoorData(gameid)(dBell) = false
		DoorData(gameid)(dDoorEdited) = 0
		
		DoorData(gameid)(dBlocked) = DoorCache(dBlocked)
		DoorData(gameid)(dLimit) = DoorCache(dLimit)
		DoorData(gameid)(dCost) = DoorCache(dCost)
		DoorData(gameid)(dPaintball) = DoorCache(dPaintball)

		// Jeœli p³onie
		if(DoorData(gameid)(dBurnTime))
		(
			string(128), Float:percent = (float(DoorData(gameid)(dBurnTime)) / 15.0) * 100
			
			format(string, sizeof(string), Ten budynek stan¹³ w p³omieniach!\nProcent zniszczeñ: %d%, floatround(percent))
			DoorData(gameid)(dFireObject) = CreateDynamicObject(18690, DoorData(gameid)(dEnterX), DoorData(gameid)(dEnterY), DoorData(gameid)(dEnterZ) - 2.0, 0.0, 0.0, 0.0, DoorData(gameid)(dEnterVW), DoorData(gameid)(dEnterInt), -1, 100.0)

			if(percent ( 30)
			(
				DoorData(gameid)(dFireLabels) = CreateDynamic3DTextLabel(string, 0x33AA33FF, DoorData(gameid)(dEnterX), DoorData(gameid)(dEnterY), DoorData(gameid)(dEnterZ) + 0.3, 10.0)
			)
			else if(percent )= 30 && percent ( 70)
			(
				DoorData(gameid)(dFireLabels) = CreateDynamic3DTextLabel(string, 0xFF9900FF, DoorData(gameid)(dEnterX), DoorData(gameid)(dEnterY), DoorData(gameid)(dEnterZ) + 0.3, 10.0)
			)
			else
			(
				DoorData(gameid)(dFireLabels) = CreateDynamic3DTextLabel(string, 0xAA3333FF, DoorData(gameid)(dEnterX), DoorData(gameid)(dEnterY), DoorData(gameid)(dEnterZ) + 0.3, 10.0)
			)
		)
		
		Itter_Add(Doors, gameid)
	)
	mysql_free_result()

	printf((load) Wczytano %d drzwi z bazy danych., gameid)
	return 1
)

public ShowPlayerDoorInfo(playerid, gameid)
(
	list_stats(256), string(128)
	format(list_stats, sizeof(list_stats), PickupID:\t\t%d, DoorData(gameid)(dPickupID))
	if(DoorData(gameid)(dLocked))
	(
		format(list_stats, sizeof(list_stats), %s\nDrzwi:\t\t\t(FB5006)Zamkniête(FFFFFF)\n, list_stats)
	)
	else
	(
		format(list_stats, sizeof(list_stats), %s\nDrzwi:\t\t\tOtwarte\n, list_stats)
	)
	if(DoorData(gameid)(dElock))
	(
		format(list_stats, sizeof(list_stats), %s\nZamek elektroniczny:\t\tTak\n, list_stats)
	)
	else
	(
		format(list_stats, sizeof(list_stats), %s\nZamek elektroniczny:\t\tNie\n, list_stats)
	)
	if(DoorData(gameid)(dOwnerType) == OWNER_NONE)
	(
 		format(list_stats, sizeof(list_stats), %s\nTyp w³aœciciela:\t\tBrak\n, list_stats)
	)
	if(DoorData(gameid)(dOwnerType) == OWNER_PLAYER)
	(
		format(list_stats, sizeof(list_stats), %s\nTyp w³aœciciela:\t\tGracz\n, list_stats)
		format(list_stats, sizeof(list_stats), %s\nUID gracza:\t\t%d\n, list_stats, DoorData(gameid)(dOwner))
	)
	if(DoorData(gameid)(dOwnerType) == OWNER_GROUP)
	(
		format(list_stats, sizeof(list_stats), %s\nTyp w³aœciciela:\t\tGrupa\n, list_stats)
		format(list_stats, sizeof(list_stats), %s\nUID grupy:\t\t%d\n, list_stats, DoorData(gameid)(dOwner))
	)
	if(DoorData(gameid)(dPaintball))
	(
		format(list_stats, sizeof(list_stats), %s\nHala do Paintballa:\tTak\n, list_stats)
	)
	if(DoorData(gameid)(dBlocked))
	(
		format(list_stats, sizeof(list_stats), %s\nBlokada obiektów:\t\t(FB5006) aktywna(FFFFFF), list_stats)
	)
	else
	(
		format(list_stats, sizeof(list_stats), %s\nBlokada obiektów: \t\tbrak, list_stats)
	)
	format(list_stats,sizeof(list_stats),%s\nLimit obiektów: \t\t%d/%d,list_stats,GetDoorObjectsAmount(gameid),DoorData(gameid)(dLimit))
	
	format(string, sizeof(string), %s (SampID: %d, UID: %d) » Informacje, DoorData(gameid)(dName), gameid, DoorData(gameid)(dUID))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, string, list_stats, Zamknij, )
	return 1
)

public OnPlayerEnterDoor(playerid, doorid)
(
	if(PlayerCache(playerid)(pBW))
 	(
  		return 1
  	)
  	if(PlayerCache(playerid)(pMoveObject) != INVALID_OBJECT_ID)
  	(
  		return 1
  	)
	if(DoorData(doorid)(dCost) ) 0 && !PlayerCache(playerid)(pAdmin))
	(
		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~r~Aby wejsc kup ta nieruchomosc, 4000, 3)
		return 1
	)
   	if(DoorData(doorid)(dLocked) && PlayerCache(playerid)(pAdmin) != 1)
	(
		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~r~Drzwi sa zamkniete, 4000, 3)
	 	return 1
	)
	if(PlayerCache(playerid)(pCash) ( DoorData(doorid)(dEnterPay))
	(
		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~r~Brak gotowki na wstep, 4000, 3)
		return 1
	)
	if(DoorData(doorid)(dWood) ) 0 || DoorData(doorid)(dRock) ) 0)
	(
		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~w~Budynek jest w trakcie ~p~~h~budowy, 4000, 3)
		ProxDetector(15.0, playerid, * W okolicy widaæ narzêdzia, ciê¿kie maszyny oraz budowlañców. *, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
	 	return 1
	)
	if(!DoorData(doorid)(dExitX))
	(
		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~w~Wnetrze jest w trakcie ~p~~h~remontu, 4000, 3)
	 	return 1
	)
   	if(PlayerCache(playerid)(pRoll))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie mo¿esz wejœæ do budynku maj¹c rolki na nogach., OK, )
		return 1
	)
	if(DoorData(doorid)(dPaintball) && !PlayerCache(playerid)(pPaintballTime))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie mo¿esz wejœæ na halê do paintballu., OK, )
		return 1
	)
	if(DoorData(doorid)(dPaintball) && PlayerCache(playerid)(pPaintballTime))
	(
		ResetPlayerWeapons(playerid)
		if(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
		(
			itemid = GetItemID(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
			
			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo)
			
			mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		)
		
		WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID) = 0
		WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID) = 0
		WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo) = 0
		WeaponCache(playerid)(WEAPON_MAIN)(pLastAmmo) = 0
		WeaponCache(playerid)(WEAPON_MAIN)(pShot) = false
		
		if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_MAIN))
		(
			RemovePlayerAttachedObject(playerid, SLOT_WEAPON_MAIN)
		)
		
		if(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
		(
			itemid = GetItemID(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
			
			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo)
			
			mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		)
		
		WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID) = 0
		WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID) = 0
		WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo) = 0
		WeaponCache(playerid)(WEAPON_SIDE)(pLastAmmo) = 0
		WeaponCache(playerid)(WEAPON_SIDE)(pShot) = false
		
		if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_SIDE))
		(
			RemovePlayerAttachedObject(playerid, SLOT_WEAPON_SIDE)
		)
		
		if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
		(
			itemid = GetItemID(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
			
			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo)
			
			mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		)
		
		WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) = 0
		WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) = 0
		WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo) = 0
		WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = 0
		WeaponCache(playerid)(WEAPON_FUNC)(pShot) = false
		
		if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_FUNC))
		(
			RemovePlayerAttachedObject(playerid, SLOT_WEAPON_FUNC)
		)
		
		ResetPlayerWeapons(playerid)
	)
	if(DoorData(doorid)(dBurnTime))
	(
		if(!IsPlayerInGroupType(playerid, GROUP_FIREDEPT))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Ten budynek p³onie!\n\nZadzwoñ po s³u¿by porz¹dkowe, w przeciwnym wypadku\nbudynek ulegnie ca³kowitemu zniszczeniu!, OK, )
			return 1
		)
		TextDrawSetString(Text:TextDrawMainInfo(playerid), Wszedles do ~r~palacego ~w~sie budynku. Uzywaj ~y~gasnicy ~w~by gasic pozar.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
		
		PlayerCache(playerid)(pShowInfoText) = 5
	)
   	if(strlen(DoorData(doorid)(dAudioURL)) != 0)
	(
		if(PlayerCache(playerid)(pAudioHandle))
		(
			//Audio_Stop(playerid, PlayerCache(playerid)(pAudioHandle))
			PlayerCache(playerid)(pAudioHandle) = 0
			StopAudioStreamForPlayer(playerid)
			
			if(PlayerCache(playerid)(pMusicPlayerUID))
			(
				itemid = GetItemID(PlayerCache(playerid)(pMusicPlayerUID))
				ItemInfo(itemid)(iUsed) = 0
			)
		)

		//PlayerCache(playerid)(pAudioHandle) = Audio_PlayStreamed(playerid, DoorData(doorid)(dAudioURL))
		PlayAudioStreamForPlayer(playerid, DoorData(doorid)(dAudioURL))
	)
	
	if(!IsPlayerInAnyVehicle(playerid))
	(
		hrp_SetPlayerPos(playerid, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ))
		SetPlayerFacingAngle(playerid, DoorData(doorid)(dExitAng))

		Streamer_Update(playerid)

		SetPlayerInterior(playerid, DoorData(doorid)(dExitInt))
		SetPlayerVirtualWorld(playerid, DoorData(doorid)(dExitVW))
	)
	else
	(
		vehid = GetPlayerVehicleID(playerid)
		
   		PlayerCache(playerid)(pGotAirBrkPos) = 0

		PlayerCache(playerid)(pCheatPosX) = DoorData(doorid)(dExitX)
		PlayerCache(playerid)(pCheatPosY) = DoorData(doorid)(dExitY)
		PlayerCache(playerid)(pCheatPosZ) = DoorData(doorid)(dExitZ)
		
		SetVehicleVirtualWorld(vehid, DoorData(doorid)(dExitVW))
		SetVehiclePos(vehid, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ))

		Streamer_Update(playerid)

		SetVehicleZAngle(vehid, DoorData(doorid)(dExitAng))
		LinkVehicleToInterior(vehid, DoorData(doorid)(dExitInt))
		
		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
	  			if(GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid))
				(
					SetPlayerVirtualWorld(i, DoorData(doorid)(dExitVW))
					SetPlayerInterior(i, DoorData(doorid)(dExitInt))
				)
			)
		)
	)
	
	TogglePlayerControllable(playerid, false)
	PlayerCache(playerid)(pDoorFreeze) = 3

	SetCameraBehindPlayer(playerid)
	PlayerTextDrawHide(playerid, TextDrawDoorInfo(playerid))
	
	// Zabierz graczowi kasê za wstêp i przelej j¹ na konto w³aœciciela
 	if(DoorData(doorid)(dEnterPay))
	(
		bool:checkbug = false
		if(gettime() - LogTime(playerid) ) 60)
			checkbug= true
	
		if(PlayerCache(playerid)(pHours) ) 5 && DoorData(doorid)(dEnterPay) ( 60 && checkbug)
		(
			hrp_MoneyActionLog(%s (UID: %d) stracil $%d przez wejscie w drzwi %s (UID: %d), PlayerName(playerid), PlayerCache(playerid)(pUID), DoorData(doorid)(dEnterPay), DoorData(doorid)(dName), DoorData(doorid)(dUID))
			hrp_GivePlayerMoney(playerid, -DoorData(doorid)(dEnterPay))
			if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
			(
				owner_id = GetPlayerID(DoorData(doorid)(dOwner))

				if(owner_id != INVALID_PLAYER_ID && Logged(owner_id) && Spawned(owner_id))
				(
					PlayerCache(owner_id)(pBankCash) += DoorData(doorid)(dEnterPay)
					SavePlayerStats(owner_id, SAVE_PLAYER_BASIC)
				)
				else
				(
					mysql_query_format(UPDATE hrp_characters SET char_bankcash = char_bankcash + %d WHERE char_uid = %d LIMIT 1, DoorData(doorid)(dEnterPay), DoorData(doorid)(dOwner))
					mysql_query_format(UPDATE hrp_characters SET char_color = (((((char_cash + char_bankcash) + 31) * 3) + char_uid) + 3) WHERE char_uid = %d LIMIT 1, DoorData(doorid)(dOwner))
				)
			)
			if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
			(
				group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
				
				GroupData(group_id_fix)(gCash) += DoorData(doorid)(dEnterPay)
				GroupData(group_id_fix)(gActionTime) = gettime()
				SaveGroup(group_id_fix)
			)
		)
	)
	
	if(DoorData(doorid)(dExitVW) != 0 && !PlayerCache(playerid)(pRage))
		SetPlayerWeather(playerid, 10)
	
	if(DoorData(doorid)(dExitVW) == 0)
	(
		new_time_h, new_time_m
		gettime(new_time_h, new_time_m)
		SetPlayerTime(playerid, new_time_h, new_time_m)
	)
	else
	(
		SetPlayerTime(playerid, DoorData(doorid)(dTime), 0)
	)

	SyncCamera(playerid)
	return 1
)

public OnPlayerExitDoor(playerid, doorid)
(
	CancelEdit(playerid)
	if(PlayerCache(playerid)(pBW))
 	(
  		return 1
  	)
  	if(PlayerCache(playerid)(pMoveObject) != INVALID_OBJECT_ID)
  	(
  		return 1
  	)
	if(DoorData(doorid)(dLocked) && PlayerCache(playerid)(pAdmin) != 1)
 	(
		if(!DoorData(doorid)(dPaintball))
		(
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~r~Drzwi sa zamkniete., 4000, 3)
			return 1
		)
 	)
 	if(strlen(DoorData(doorid)(dAudioURL)) != 0)
 	(
		//if(PlayerCache(playerid)(pAudioHandle))
		//(
			PlayerCache(playerid)(pAudioHandle) = 0
			StopAudioStreamForPlayer(playerid)
		//)
	)
	if(PlayerCache(playerid)(pTrainTime))
  	(
  		OnPlayerGymTrainStopped(playerid)
  		
		itemid = PlayerCache(playerid)(pGymPass)

		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue1) = PlayerCache(playerid)(pTrainTime) / 60

		mysql_query_format(UPDATE hrp_items SET item_used = %d, item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))

		PlayerCache(playerid)(pGymPass) = 0
  		PlayerCache(playerid)(pTrainTime) = 0
  	)
	
	if(PlayerCache(playerid)(pPaintballTime))
  	(
  		ResetPlayerWeapons(playerid)
		
		if(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
		(
			itemid = GetItemID(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
			
			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo)
			
			mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		)
		
		WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID) = 0
		WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID) = 0
		WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo) = 0
		WeaponCache(playerid)(WEAPON_MAIN)(pLastAmmo) = 0
		WeaponCache(playerid)(WEAPON_MAIN)(pShot) = false
		
		if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_MAIN))
		(
			RemovePlayerAttachedObject(playerid, SLOT_WEAPON_MAIN)
		)
		
		if(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
		(
			itemid = GetItemID(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
			
			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo)
			
			mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		)
		
		WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID) = 0
		WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID) = 0
		WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo) = 0
		WeaponCache(playerid)(WEAPON_SIDE)(pLastAmmo) = 0
		WeaponCache(playerid)(WEAPON_SIDE)(pShot) = false
					
		if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_SIDE))
		(
			RemovePlayerAttachedObject(playerid, SLOT_WEAPON_SIDE)
		)
					
		if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
		(
			itemid = GetItemID(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
		
			ItemInfo(itemid)(iUsed) = 0
			ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo)
			
			mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
		)
		
		WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) = 0
		WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) = 0
		WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo) = 0
		WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = 0
		WeaponCache(playerid)(WEAPON_FUNC)(pShot) = false
		
		if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_FUNC))
		(
			RemovePlayerAttachedObject(playerid, SLOT_WEAPON_FUNC)
		)
		
		ResetPlayerWeapons(playerid)
		
		itemid = PlayerCache(playerid)(pPaintballPass)

		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue1) = PlayerCache(playerid)(pPaintballTime) / 60

		mysql_query_format(UPDATE hrp_items SET item_used = %d, item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))

		PlayerCache(playerid)(pPaintballPass) = 0
  		PlayerCache(playerid)(pPaintballTime) = 0
  	)
  		
  	if(!IsPlayerInAnyVehicle(playerid))
  	(
		hrp_SetPlayerPos(playerid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ))
	  	SetPlayerFacingAngle(playerid, DoorData(doorid)(dEnterAng))

		Streamer_Update(playerid)

		SetPlayerInterior(playerid, DoorData(doorid)(dEnterInt))
	 	SetPlayerVirtualWorld(playerid, DoorData(doorid)(dEnterVW))
	)
	else
	(
		vehid = GetPlayerVehicleID(playerid)
		
		PlayerCache(playerid)(pGotAirBrkPos) = 0

		PlayerCache(playerid)(pCheatPosX) = DoorData(doorid)(dEnterX)
		PlayerCache(playerid)(pCheatPosY) = DoorData(doorid)(dEnterY)
		PlayerCache(playerid)(pCheatPosZ) = DoorData(doorid)(dEnterZ)
		
		SetVehicleVirtualWorld(vehid, DoorData(doorid)(dEnterVW))
		SetVehiclePos(vehid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ))

		Streamer_Update(playerid)

		SetVehicleZAngle(vehid, DoorData(doorid)(dEnterAng))
		LinkVehicleToInterior(vehid, DoorData(doorid)(dEnterInt))
		
		PlayerCache(playerid)(pVehCollisions) = 5
		DisableRemoteVehicleCollisions(playerid, 1)
		
		foreach(Player, i)
		(
  			if(GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid))
			(
				// Reszta osób w pojeŸdzie - im te¿ duty trzeba pozabieraæ
				group_id_fix = GetPlayerDutyGroupID(i), bool:check = false, bool:check2 = false, bool:check3 = false
				if(group_id_fix != -1)
				(
					if(GroupData(group_id_fix)(gType) != GROUP_CORONER && GroupData(group_id_fix)(gType) != GROUP_DOC && GroupData(group_id_fix)(gType) != GROUP_FARM && GroupData(group_id_fix)(gType) != GROUP_RADIO && GroupData(group_id_fix)(gType) != GROUP_GASSTATION)
						check = true
					if(GroupData(group_id_fix)(gType) != GROUP_TAXI && GroupData(group_id_fix)(gType) != GROUP_DRIVING && GroupData(group_id_fix)(gType) != GROUP_TRANSPORT && GroupData(group_id_fix)(gType) != GROUP_SECURITY && GroupData(group_id_fix)(gType) != GROUP_POLICE)
						check2 = true
					if(GroupData(group_id_fix)(gType) != GROUP_TIMBER && GroupData(group_id_fix)(gType) != GROUP_MEDICAL && GroupData(group_id_fix)(gType) != GROUP_FBI && GroupData(group_id_fix)(gType) != GROUP_RACERS)
						check3 = true

					if(check && check2 && check3 && GroupData(group_id_fix)(gType) != GROUP_TRUCKERS && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT && GroupData(group_id_fix)(gType) != GROUP_NEWS && GroupData(group_id_fix)(gType) != GROUP_ARMY && GroupData(group_id_fix)(gType) != GROUP_AUTOSALE)
					(
						cmd_duty(i, grupa skip)
					)
				)
				
				SetPlayerVirtualWorld(i, DoorData(doorid)(dEnterVW))
				SetPlayerInterior(i, DoorData(doorid)(dEnterInt))
			)
		)
	)
	if(DoorData(doorid)(dEnterVW) == 0 && !PlayerCache(playerid)(pRage)) SetPlayerWeather(playerid, weather)
 	
	TogglePlayerControllable(playerid, false)
	PlayerCache(playerid)(pDoorFreeze) = 3

	SetCameraBehindPlayer(playerid)
	
	group_id_fix = GetPlayerDutyGroupID(playerid), bool:check = false, bool:check2 = false, bool:check3 = false
	if(group_id_fix != -1)
	(
		if(GroupData(group_id_fix)(gType) != GROUP_DOC && GroupData(group_id_fix)(gType) != GROUP_FARM && GroupData(group_id_fix)(gType) != GROUP_RADIO && GroupData(group_id_fix)(gType) != GROUP_GASSTATION && GroupData(group_id_fix)(gType) != GROUP_TAXI)
			check = true
		if(GroupData(group_id_fix)(gType) != GROUP_DRIVING && GroupData(group_id_fix)(gType) != GROUP_TRANSPORT && GroupData(group_id_fix)(gType) != GROUP_SECURITY && GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_MEDICAL && GroupData(group_id_fix)(gType) != GROUP_FBI)
			check2 = true
		if(GroupData(group_id_fix)(gType) != GROUP_SAWMILL && GroupData(group_id_fix)(gType) != GROUP_QUARRY && GroupData(group_id_fix)(gType) != GROUP_TIMBER)
			check3 = true

		if(check && check2 && check3 && GroupData(group_id_fix)(gType) != GROUP_TRUCKERS && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT && GroupData(group_id_fix)(gType) != GROUP_NEWS && GroupData(group_id_fix)(gType) != GROUP_ARMY && GroupData(group_id_fix)(gType) != GROUP_AUTOSALE)
		(
			cmd_duty(playerid, grupa skip)
		)
	)
		
	if(DoorData(doorid)(dEnterVW) == 0)
	(
		new_time_h, new_time_m
		gettime(new_time_h, new_time_m)
		SetPlayerTime(playerid, new_time_h, new_time_m)
	)
	else
	(
		SetPlayerTime(playerid, DoorData(doorid)(dTime), 0)
	)

	SyncCamera(playerid)
	return 1
)

public ShowPlayerDoorAddons(playerid, gameid)
(
	buffer(256),list(128)
	format(buffer,sizeof(buffer),SELECT * FROM hrp_doors_addons WHERE addon_dooruid=%i,DoorData(gameid)(dUID))
	
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		while(mysql_fetch_row(buffer,|))
		(
			addUID,addDoor,addType
			sscanf(buffer,p(|)ddd,addUID,addDoor,addType)
			if(addType == ITEM_HOMEPHONESET)
			(
				dooruid = DoorData(GetPlayerDoorID(playerid))(dUID), number = 1000 + dooruid
				format(list,sizeof(list),%s\n%i.\t\t%s (NR: %i),list,addUID,ItemTypeInfo(addType)(iTypeName),number)
			)
			else
			(
				format(list,sizeof(list),%s\n%i.\t\t%s,list,addUID,ItemTypeInfo(addType)(iTypeName))
			)
		)
		
		mysql_free_result()
		
		ShowPlayerDialog(playerid,D_DOOR_ADDON_LIST,DIALOG_STYLE_LIST,Drzwi » dodatki,list,Wybierz,Anuluj)
	)
	else
	(
		mysql_free_result()
		GuiMsg(playerid,Brak dodatków dla tego budynku.,0)
	)
	return 1
)

stock GetDoorObjectsAmount(doorid)
(
	world = DoorData(doorid)(dExitVW)
	buffer(256)
	format(buffer,sizeof(buffer),SELECT * FROM hrp_objects WHERE object_world=%d,world)
	mysql_query(buffer)
	mysql_store_result()
	amount = mysql_num_rows()
	mysql_free_result()
	return amount
)

stock IsDoorAddonMounted(doorid,addonType)
(
	buffer(256)
	format(buffer,sizeof(buffer),SELECT * FROM hrp_doors_addons WHERE addon_dooruid=%i AND addon_type=%i,DoorData(doorid)(dUID),addonType)
	
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		mysql_free_result()
		return true
	)
	else
	(
		mysql_free_result()
		return false
	)
)

stock GetClosestDoor(playerid, Float:distance = 5.0)
(
	// dEnterX
	doorid = INVALID_DOOR_ID, Float:PosX, Float:PosY, Float:PosZ, Float:closest
	GetPlayerPos(playerid, PosX, PosY, PosZ)
	
	for(i = 0  i ( MAX_DOORS i++)
	(
		if(GetPlayerVirtualWorld(playerid) != DoorData(i)(dEnterVW))
			continue
			
		if(!IsPlayerInRangeOfPoint(playerid, distance, DoorData(i)(dEnterX), DoorData(i)(dEnterY), DoorData(i)(dEnterZ)))
			continue
		
		if(GetPlayerDistanceFromPoint(playerid, DoorData(i)(dEnterX), DoorData(i)(dEnterY), DoorData(i)(dEnterZ)) ( closest || closest == 0.0)
		(
			closest = GetPlayerDistanceFromPoint(playerid, DoorData(i)(dEnterX), DoorData(i)(dEnterY), DoorData(i)(dEnterZ))
			doorid = i
		)
	)
	
	return doorid
)

stock addSpecialObjects(playerid, item_uid, doorid, amount)
(
	// dodajemy limit
	buffer(256)
	DoorData(doorid)(dLimit) += amount
	format(buffer, sizeof(buffer), UPDATE hrp_doors SET door_limit = door_limit + %d WHERE door_uid=%d, amount, DoorData(doorid)(dUID))
	mysql_query(buffer)
	
	// informujemy gracza
	GuiMsg(playerid, Pomyœlnie zwiêkszono limit obiektów w tych drzwiach!, 0)
	DeleteItem(item_uid)
	return 1
)

stock checkDoorsActivity()
(
	buffer(256), cleared = 0
	for(i = 0  i ( MAX_DOORS i++)
	(
		if(DoorData(i)(dUID))
		(
			if(DoorData(i)(dOwnerType) == OWNER_PLAYER)
			(
				// Te drzwi mog¹ nie byæ w tabeli
				format(buffer, sizeof(buffer), SELECT * FROM hrp_door_defaults WHERE default_dooruid = %d, DoorData(i)(dUID))
				mysql_query(buffer)
				mysql_store_result()
				if(mysql_num_rows() (= 0)
				(
					mysql_free_result()
					continue
				)
				
				global_time = 0			// do wyci¹gania zmiennej
				
				door_cost, door_name(64), door_time
				format(buffer, sizeof(buffer), SELECT default_doorcost, default_doorname, default_checktime FROM hrp_door_defaults WHERE default_dooruid = %d, DoorData(i)(dUID))
				mysql_query(buffer)
				mysql_store_result()
				while(mysql_fetch_row(buffer, |))
				(
					sscanf(buffer, p(|)ds(64)d, door_cost, door_name, door_time)
					global_time = door_time
					if(gettime() ) door_time)
					(
						DoorData(i)(dPickupID) = 19471
						DoorData(i)(dCost) = door_cost
						DoorData(i)(dOwnerType) = OWNER_NONE
						DoorData(i)(dOwner) = 0
						
						printf((SYSTEM-SOLD) Drzwi %s (UID: %d) zostaly zwolnione z powodu nieaktynosci gracza, DoorData(i)(dName), DoorData(i)(dUID))
						cleared++
						
						DestroyPickup(i)
						CreatePickup(DoorData(i)(dPickupID), 2, DoorData(i)(dEnterX), DoorData(i)(dEnterY), DoorData(i)(dEnterZ), DoorData(i)(dEnterVW))
					)
				)
				
				mysql_free_result()
				if(gettime() ) global_time)
				(
					mysql_query_format(UPDATE hrp_characters SET char_house = 0 WHERE char_house = %d, DoorData(i)(dUID))
					SaveDoor(i, SAVE_DOOR_THINGS)
				)
			)
		)
	)
	
	printf((SYSTEM-SOLD) Wyczyszczono %d drzwi, cleared)
	return 1
)

stock setDoorActivity(playerid)
(
	buffer(256)
	for(i = 0  i ( MAX_DOORS i++)
	(
		if(DoorData(i)(dUID) && DoorData(i)(dOwnerType) == OWNER_PLAYER && DoorData(i)(dOwner) == PlayerCache(playerid)(pUID))
		(
			format(buffer, sizeof(buffer), SELECT * FROM hrp_door_defaults WHERE default_dooruid = %d, DoorData(i)(dUID))
			mysql_query(buffer)
			mysql_store_result()
			if(mysql_num_rows() ) 0)
			(
				// Zwiêkszamy czas o miesi¹c
				mysql_free_result()
				mysql_query_format(UPDATE hrp_door_defaults SET default_checktime = %d WHERE default_dooruid = %d, gettime() + 2592000, DoorData(i)(dUID))
			)
			else
			(
				mysql_free_result()
			)
		)
	)
	return 1
)















