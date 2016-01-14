public CreateCar(modelid, Float:PosX, Float:PosY, Float:PosZ, Float:PosA, color1, color2, respawn_delay)
(
	gameid, uid
	mysql_query_format(INSERT INTO hrp_cars (car_model, car_name, car_posx, car_posy, car_posz, car_posa, car_color1, car_color2, car_fuel, car_fueltype, car_lastactivity, car_activity) VALUES (%d, %s, %f, %f, %f, %f, %d, %d, %d, %d, %d, 1), modelid, VehicleData(modelid-400)(vName), PosX, PosY, PosZ, PosA, color1, color2, GetVehicleMaxFuel(modelid), GetVehicleFuelType(modelid), gettime())

	uid = mysql_insert_id()
	gameid = CreateVehicle(modelid, PosX, PosY, PosZ, PosA, color1, color2, respawn_delay)
		
	LoadVehicle(gameid, uid)
	Itter_Add(Vehicles, gameid)
	return gameid
)

public LoadVehicle(gameid, uid)
(
	data(256), visual(32), empty = 0
	mysql_query_format(SELECT * FROM hrp_cars WHERE car_uid = %d , uid)
	
 	print((load) Rozpoczynam proces wczytywania statystyk pojazdu...)

	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)dds(24)ffffddddddfs(32)fdfddddddfddd,
		CarInfo(gameid)(cUID),
		CarInfo(gameid)(cModel),
		CarInfo(gameid)(cName),
		CarInfo(gameid)(cPosX),
		CarInfo(gameid)(cPosY),
		CarInfo(gameid)(cPosZ),
		CarInfo(gameid)(cPosA),
		CarInfo(gameid)(cInteriorID),
		CarInfo(gameid)(cWorldID),
		CarInfo(gameid)(cColor1),
		CarInfo(gameid)(cColor2),
		CarInfo(gameid)(cOwner),
		CarInfo(gameid)(cOwnerType),
		CarInfo(gameid)(cHealth),
		visual,
		CarInfo(gameid)(cFuel),
		CarInfo(gameid)(cFuelType),
		CarInfo(gameid)(cMileage),
		CarInfo(gameid)(cLocked),
		CarInfo(gameid)(cPaintJob),
		CarInfo(gameid)(cWheelBlock),
		CarInfo(gameid)(cAccess),
		CarInfo(gameid)(cRegister),
		CarInfo(gameid)(cBlocked),
		CarInfo(gameid)(cCarfax),
		CarInfo(gameid)(cEBreak),
		empty)
		
		
		CarInfo(gameid)(cOwnerExitTime) = 0
		CarInfo(gameid)(cWindowOpen) = false
		CarInfo(gameid)(cDriverWindowOpen) = 1
		CarInfo(gameid)(cPassengerWindowOpen) = 1
		CarInfo(gameid)(cLeftWindowOpen) = 1
		CarInfo(gameid)(cRightWindowOpen) = 1
		CarInfo(gameid)(cStrobe) = false
		CarInfo(gameid)(cTop) = false
		CarInfo(gameid)(cFlashed) = false
		CarInfo(gameid)(cPilotTick) = false
		
		sscanf(visual, p(,)dddd, CarInfo(gameid)(cVisual)(0), CarInfo(gameid)(cVisual)(1), CarInfo(gameid)(cVisual)(2), CarInfo(gameid)(cVisual)(3))

		if(CarInfo(gameid)(cHealth) ( 350)	CarInfo(gameid)(cHealth) = 350
		
		SetVehicleHealth(gameid, CarInfo(gameid)(cHealth))
		UpdateVehicleDamageStatus(gameid, CarInfo(gameid)(cVisual)(0), CarInfo(gameid)(cVisual)(1), CarInfo(gameid)(cVisual)(2), CarInfo(gameid)(cVisual)(3))

		SetVehicleVirtualWorld(gameid, CarInfo(gameid)(cWorldID))
		LinkVehicleToInterior(gameid, CarInfo(gameid)(cInteriorID))

		SetVehicleLock(gameid, CarInfo(gameid)(cLocked))
		ChangeVehiclePaintjob(gameid, CarInfo(gameid)(cPaintJob))
	)
	mysql_free_result()
	
	// Wczytaj komponenty pojazdu
 	componentid
	mysql_query_format(SELECT item_value1 FROM hrp_items WHERE item_vehuid = %d, CarInfo(gameid)(cUID))

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		if(componentid == 1131)
		(
			// savanna ma chowany dach
			CarInfo(gameid)(cTop) = true
		)
		
		sscanf(data, p(|)d, componentid)
		hrp_AddVehicleComponent(gameid, componentid)
	)
	mysql_free_result()
	ChangeVehiclePaintjob(gameid, CarInfo(gameid)(cPaintJob))
	
	// Wyzeruj informacje
	CarInfo(gameid)(cEngineTogged) = false
	
	CarInfo(gameid)(cBoost) = 0.0

	CarInfo(gameid)(cSpawned) = true
	CarInfo(gameid)(cTowedVeh) = INVALID_VEHICLE_ID
	
	CarInfo(gameid)(cRadioCanal) = 0
	CarInfo(gameid)(cGPS) = false
	
	CarInfo(gameid)(cArmed) = false

	strmid(CarInfo(gameid)(cAudioURL), , 0, 0, 0)

	if(CarInfo(gameid)(cRegister))
	(
		string(32)

		format(string, sizeof(string), LS%d, CarInfo(gameid)(cUID))
		SetVehicleNumberPlate(gameid, string)
	)
	else
	(
		SetVehicleNumberPlate(gameid, _)
	)

	Itter_Add(Vehicles, gameid)
	
	LoadVehicleTune(gameid)	//pobieramy tuning

	GetVehiclePos(gameid, CarInfo(gameid)(cEPosX), CarInfo(gameid)(cEPosY), CarInfo(gameid)(cEPosZ))
	
	getVehicleRemoves(gameid)
	
	GetVehiclePos(gameid, OldVehiclePosition(gameid)(0), OldVehiclePosition(gameid)(1), OldVehiclePosition(gameid)(2))
	
	printf((load) Wczytano statystyki pojazdu %s (SampID: %d, UID: %d) pomyœlnie., CarInfo(gameid)(cName), gameid, CarInfo(gameid)(cUID))
	return uid
)

public SaveVehicle(gameid, what)
(
	main_query(512), query(256)
	format(main_query, sizeof(main_query), UPDATE hrp_cars SET)
	if(what & SAVE_VEH_POS)
	(
		// Pozycja pojazdu
		format(query, sizeof(query),  car_posx = %f, car_posy = %f, car_posz = %f, car_posa = %f, car_interior = %d, car_world = %d,
		CarInfo(gameid)(cPosX),
		CarInfo(gameid)(cPosY),
		CarInfo(gameid)(cPosZ),
		CarInfo(gameid)(cPosA),
		CarInfo(gameid)(cInteriorID),
		CarInfo(gameid)(cWorldID))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_VEH_ACCESS)
	(
		// Akcesoria pojazdu (kolory, rodzaj paliwa, paintjob, blokada na ko³o, akcesoria)
		format(query, sizeof(query),  car_color1 = %d, car_color2 = %d, car_fueltype = %d, car_paintjob = %d, car_blockwheel = %d, car_access = %d, car_ebreak = %d,
		CarInfo(gameid)(cColor1),
		CarInfo(gameid)(cColor2),
		CarInfo(gameid)(cFuelType),
		CarInfo(gameid)(cPaintJob),
		CarInfo(gameid)(cWheelBlock),
		CarInfo(gameid)(cAccess),
		CarInfo(gameid)(cEBreak))
		
		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_VEH_COUNT)
	(
		// Liczniki (paliwo, przebieg, uszkodzenie techniczne, uszkodzenie wizualne)
		format(query, sizeof(query),  car_health = %f, car_fuel = %f, car_mileage = %f, car_visual = %d,%d,%d,%d, car_carfax = %f,
		CarInfo(gameid)(cHealth),
		CarInfo(gameid)(cFuel),
		CarInfo(gameid)(cMileage),
		CarInfo(gameid)(cVisual)(0),
		CarInfo(gameid)(cVisual)(1),
		CarInfo(gameid)(cVisual)(2),
		CarInfo(gameid)(cVisual)(3),
		CarInfo(gameid)(cCarfax))
		
		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_VEH_THINGS)
	(
		// Pozosta³e (w³a¶ciciel, model, nazwa, last activity)
		format(query, sizeof(query),  car_owner = %d, car_ownertype = %d, car_model = %d, car_name = %s, car_register = %d,
		CarInfo(gameid)(cOwner),
		CarInfo(gameid)(cOwnerType),
		CarInfo(gameid)(cModel),
		CarInfo(gameid)(cName),
		CarInfo(gameid)(cRegister))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_VEH_LOCK)
	(
		// Zamkniêcie pojazdu
		format(query, sizeof(query),  car_lock = %d,
		CarInfo(gameid)(cLocked))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	format(query, sizeof(query),  WHERE car_uid = %d LIMIT 1, CarInfo(gameid)(cUID))
	strcat(main_query, query, sizeof(main_query))
	
	mysql_query(main_query)
	
	OnVehicleSave(gameid) = 0
	return 1
)

public DeleteVehicle(gameid)
(
	mysql_query_format(DELETE FROM hrp_cars WHERE car_uid = %d, CarInfo(gameid)(cUID))
	
	if(CarInfo(gameid)(cOwnerType) == OWNER_PLAYER)
	(
		giveplayer_id = GetPlayerID(CarInfo(gameid)(cOwner))
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			return 1
		)
		PlayerCache(giveplayer_id)(pCarSpawned) --
	)
	
	CarInfo(gameid)(cUID) = 0
	CarInfo(gameid)(cModel) = 0

	CarInfo(gameid)(cPosX) = 0.0
	CarInfo(gameid)(cPosY) = 0.0
	CarInfo(gameid)(cPosZ) = 0.0
	CarInfo(gameid)(cPosA) = 0.0
	
	CarInfo(gameid)(cInteriorID) = 0
	CarInfo(gameid)(cWorldID) = 0

	CarInfo(gameid)(cColor1) = 0
	CarInfo(gameid)(cColor2) = 0

	CarInfo(gameid)(cOwner) = 0
	CarInfo(gameid)(cOwnerType) = 0

	CarInfo(gameid)(cHealth) = 0.0
	
	CarInfo(gameid)(cVisual)(0) = 0
	CarInfo(gameid)(cVisual)(1) = 0
	CarInfo(gameid)(cVisual)(2) = 0
	CarInfo(gameid)(cVisual)(3) = 0

	CarInfo(gameid)(cFuel) = 0.0
	CarInfo(gameid)(cMileage) = 0.0

	CarInfo(gameid)(cFuelType) = 0

	CarInfo(gameid)(cWheelBlock) = 0

	CarInfo(gameid)(cEngineTogged) = false

	CarInfo(gameid)(cLocked) = false
	CarInfo(gameid)(cSpawned) = false

	CarInfo(gameid)(cTowedVeh) = INVALID_VEHICLE_ID

	CarInfo(gameid)(cPaintJob) = 0
	CarInfo(gameid)(cAccess) = 0
	
	strmid(CarInfo(gameid)(cAudioURL), , 0, 0, 0)
	
	CarInfo(gameid)(cRadioCanal) = 0
	CarInfo(gameid)(cGPS) = false
	
	CarInfo(gameid)(cOwnerExitTime) = 0
	CarInfo(gameid)(cWindowOpen) = false
	
	CarInfo(gameid)(cDriverWindowOpen) = 1
	CarInfo(gameid)(cPassengerWindowOpen) = 1
	CarInfo(gameid)(cLeftWindowOpen) = 1
	CarInfo(gameid)(cRightWindowOpen) = 1
	
	CarInfo(gameid)(cStrobe) = false
	
	CarInfo(gameid)(cCarfax) = 0.0
	
	DestroyVehicle(gameid)
	
	Itter_Remove(Vehicles, gameid)
	return 1
)

public LoadVehicles()
(
	gameid, data(256), visual(32), empty = 0
	mysql_query(SELECT * FROM hrp_cars WHERE car_ownertype () 1)
	
	print((load) Rozpoczynam proces wczytywania pojazdów z bazy danych...)

	// Wczytaj do tablic
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		gameid++

		sscanf(data, p(|)dds(24)ffffddddddfs(32)fdfdddddfdd,
		CarInfo(gameid)(cUID),
		CarInfo(gameid)(cModel),
		CarInfo(gameid)(cName),
		CarInfo(gameid)(cPosX),
		CarInfo(gameid)(cPosY),
		CarInfo(gameid)(cPosZ),
		CarInfo(gameid)(cPosA),
		CarInfo(gameid)(cInteriorID),
		CarInfo(gameid)(cWorldID),
		CarInfo(gameid)(cColor1),
		CarInfo(gameid)(cColor2),
		CarInfo(gameid)(cOwner),
		CarInfo(gameid)(cOwnerType),
		CarInfo(gameid)(cHealth),
		visual,
		CarInfo(gameid)(cFuel),
		CarInfo(gameid)(cFuelType),
		CarInfo(gameid)(cMileage),
		CarInfo(gameid)(cLocked),
		CarInfo(gameid)(cPaintJob),
		CarInfo(gameid)(cWheelBlock),
		CarInfo(gameid)(cAccess),
		CarInfo(gameid)(cRegister),
		CarInfo(gameid)(cCarfax),
		CarInfo(gameid)(cEBreak),
		empty)
		
		
		CarInfo(gameid)(cOwnerExitTime) = 0
		CarInfo(gameid)(cWindowOpen) = false
		CarInfo(gameid)(cDriverWindowOpen) = 1
		CarInfo(gameid)(cPassengerWindowOpen) = 1
		CarInfo(gameid)(cLeftWindowOpen) = 1
		CarInfo(gameid)(cRightWindowOpen) = 1
		CarInfo(gameid)(cArmed) = false
		CarInfo(gameid)(cFlashed) = false
		CarInfo(gameid)(cPilotTick) = false
		
  		sscanf(visual, p(,)dddd, CarInfo(gameid)(cVisual)(0), CarInfo(gameid)(cVisual)(1), CarInfo(gameid)(cVisual)(2), CarInfo(gameid)(cVisual)(3))

		if(CarInfo(gameid)(cModel) == 544)
		(
			CreateVehicle(CarInfo(gameid)(cModel), CarInfo(gameid)(cPosX), CarInfo(gameid)(cPosY), CarInfo(gameid)(cPosZ), CarInfo(gameid)(cPosA), CarInfo(gameid)(cColor1), CarInfo(gameid)(cColor2), 7200, 1)
		)
		else
		(
			CreateVehicle(CarInfo(gameid)(cModel), CarInfo(gameid)(cPosX), CarInfo(gameid)(cPosY), CarInfo(gameid)(cPosZ), CarInfo(gameid)(cPosA), CarInfo(gameid)(cColor1), CarInfo(gameid)(cColor2), 7200)
		)

		if(CarInfo(gameid)(cHealth) ( 350)	CarInfo(gameid)(cHealth) = 350
		
		SetVehicleHealth(gameid, CarInfo(gameid)(cHealth))
		UpdateVehicleDamageStatus(gameid, CarInfo(gameid)(cVisual)(0), CarInfo(gameid)(cVisual)(1), CarInfo(gameid)(cVisual)(2), CarInfo(gameid)(cVisual)(3))

		SetVehicleVirtualWorld(gameid, CarInfo(gameid)(cWorldID))
		LinkVehicleToInterior(gameid, CarInfo(gameid)(cInteriorID))
		
		SetVehicleLock(gameid, CarInfo(gameid)(cLocked))
		ChangeVehiclePaintjob(gameid, CarInfo(gameid)(cPaintJob))
		
		CarInfo(gameid)(cSpawned) = true
		CarInfo(gameid)(cTowedVeh) = INVALID_VEHICLE_ID
		
		CarInfo(gameid)(cBoost) = 0.0
		
		GetVehiclePos(gameid, OldVehiclePosition(gameid)(0), OldVehiclePosition(gameid)(1), OldVehiclePosition(gameid)(2))

		strmid(CarInfo(gameid)(cAudioURL), , 0, 0, 0)
		CarInfo(gameid)(cPoliceSiren) = INVALID_OBJECT_ID
		
		if(CarInfo(gameid)(cRegister))
		(
			string(32)

			format(string, sizeof(string), LS%d, CarInfo(gameid)(cUID))
			SetVehicleNumberPlate(gameid, string)
		)
		else
		(
			SetVehicleNumberPlate(gameid, _)
		)
		Itter_Add(Vehicles, gameid)
		
		GetVehiclePos(gameid, CarInfo(gameid)(cEPosX), CarInfo(gameid)(cEPosY), CarInfo(gameid)(cEPosZ))
	)
	mysql_free_result()
	
	// Wczytaj komponenty dla wszystkich pojazdów
	
	veh_uid, componentid
	mysql_query(SELECT item_vehuid, item_value1 FROM hrp_items WHERE item_vehuid != 0)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)dd, veh_uid, componentid)
		
		gameid = GetSpawnedVehicleID(veh_uid)
		if(gameid != INVALID_VEHICLE_ID)
		(
			hrp_AddVehicleComponent(gameid, componentid)
		)
	)
	mysql_free_result()
	
	//wczytaj tuning mechaniczny
	format(data,sizeof(data),SELECT item_vehuid, item_value1 FROM hrp_items WHERE item_vehuid != 0 AND item_type=%i,ITEM_TUNEPART)
	mysql_query(data)
	mysql_store_result()
	while(mysql_fetch_row(data,|))
	(
		sscanf(data, p(|)dd, veh_uid, componentid)
		gameid = GetSpawnedVehicleID(veh_uid)
		if(gameid != INVALID_VEHICLE_ID)
		(
			CarInfo(gameid)(cBoost) = CarInfo(gameid)(cBoost) + float(componentid)
		)
	)
	mysql_free_result()
	
	printf((load) Wczytano %d pojazdy/ów z bazy danych., gameid)
	return 1
)

public ShowPlayerVehicleInfo(playerid, gameid)
(
	list_stats(512), string(128)
	format(list_stats, sizeof(list_stats), Model:\t\t\t%d, CarInfo(gameid)(cModel))
	format(list_stats, sizeof(list_stats), %s\nKolory:\t\t\t%d/%d\n, list_stats, CarInfo(gameid)(cColor1), CarInfo(gameid)(cColor2))
	if(CarInfo(gameid)(cOwnerType) == OWNER_NONE)
	(
 		format(list_stats, sizeof(list_stats), %s\nTyp w³aœciciela:\t\tBrak\n, list_stats)
	)
	if(CarInfo(gameid)(cOwnerType) == OWNER_PLAYER)
	(
		format(list_stats, sizeof(list_stats), %s\nTyp w³aœciciela:\t\tGracz\n, list_stats)
		format(list_stats, sizeof(list_stats), %s\nUID gracza:\t\t%d\n, list_stats, CarInfo(gameid)(cOwner))
	)
	if(CarInfo(gameid)(cOwnerType) == OWNER_GROUP)
	(
		format(list_stats, sizeof(list_stats), %s\nTyp w³aœciciela:\t\tGrupa\n, list_stats)
   		format(list_stats, sizeof(list_stats), %s\nUID grupy:\t\t%d\n, list_stats, CarInfo(gameid)(cOwner))
	)
	
	if(CarInfo(gameid)(cHealth) (= 650)
	(
		format(list_stats, sizeof(list_stats), %s\nStan techniczny:\t(FB5006)%.1f(FFFFFF) HP\n, list_stats, CarInfo(gameid)(cHealth))
	)
	else
	(
 		format(list_stats, sizeof(list_stats), %s\nStan techniczny:\t%.1f HP\n, list_stats, CarInfo(gameid)(cHealth))
	)
	format(list_stats, sizeof(list_stats), %s\nPaliwo:\t\t\t%d/%d L\n, list_stats, floatround(CarInfo(gameid)(cFuel)), GetVehicleMaxFuel(CarInfo(gameid)(cModel)))
	format(list_stats, sizeof(list_stats), %s\nRodzaj paliwa:\t\t%s\n, list_stats, GetVehicleFuelTypeName(CarInfo(gameid)(cFuelType)))

	format(list_stats, sizeof(list_stats), %s\nPrzebieg:\t\t%.0f km\n, list_stats, CarInfo(gameid)(cMileage))
	format(list_stats, sizeof(list_stats), %s\nHistoria serwisu:\t\t%.0f HP\n, list_stats, CarInfo(gameid)(cCarfax))

	if(CarInfo(gameid)(cRegister))
	(
		format(list_stats, sizeof(list_stats), %s\nRejestracja:\t\tTak\n, list_stats)
	)
	else
	(
		format(list_stats, sizeof(list_stats), %s\nRejestracja:\t\t(FB5006)Nie(FFFFFF)\n, list_stats)
	)

	format(string, sizeof(string), %s (SampID: %d, UID: %d) » Informacje, CarInfo(gameid)(cName), gameid, CarInfo(gameid)(cUID))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, string, list_stats, Zamknij, )
	return 1
)

stock ShowVehicleListForPlayer(playerid, giveplayer_id)
(
	uid, vehname(32), strx(256), data(256), list
	mysql_query_format(SELECT car_uid, car_name FROM hrp_cars WHERE car_ownertype = 1 AND car_owner = %d, PlayerCache(playerid)(pUID))

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		list ++
		sscanf(data, p(|)ds(32), uid, vehname)
		format(strx, sizeof strx, %s\n%d\t\t%s, strx, uid, vehname)
	)
	mysql_free_result()
	if(strlen(strx) != 0)
	(
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_LIST, Lista pojazdów:, strx, Zamknij, )
	)
	else
	(
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz nie posiada ¿adnych pojazdów., OK, )
	)
	return 1
)

stock ShowVehicleList(playerid)
(
	uid, vehname(32), strx(256), data(256), list
	mysql_query_format(SELECT car_uid, car_name FROM hrp_cars WHERE car_ownertype = 1 AND car_owner = %d, PlayerCache(playerid)(pUID))

	printf((load) Listujê pojazdy gracza %s (UID: %d, GID: %d)..., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		list ++
		sscanf(data, p(|)ds(32), uid, vehname)
		format(strx, sizeof strx, %s\n%d\t\t%s, strx, uid, vehname)
	)
	mysql_free_result()
	if(strlen(strx) != 0)
	(
		ShowPlayerDialog(playerid, D_LIST_PLAYER_CARS, DIALOG_STYLE_LIST, Lista posiadanych pojazdów:, strx, (Un)spawn, Zamknij)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz ¿adnych pojazdów., OK, )
	)

	printf((load) Wylistowa³em pojazdy gracza %s (UID: %d, GID: %d). Znaleziono %d pojazdy/ów w bazie, PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID), list)
	return 1
)

public OnVehicleSpawn(vehicleid)
(
	for(i = 0 i ( 14 i++)
	(
 		if(CarInfo(vehicleid)(cComponent)(i) != 0)
   		(
			AddVehicleComponent(vehicleid, CarInfo(vehicleid)(cComponent)(i) + 999)
   		)
	)
	ChangeVehiclePaintjob(vehicleid, CarInfo(vehicleid)(cPaintJob))
	
	LinkVehicleToInterior(vehicleid, CarInfo(vehicleid)(cInteriorID))
	SetVehicleVirtualWorld(vehicleid, CarInfo(vehicleid)(cWorldID))
	
	SetVehicleHealth(vehicleid, CarInfo(vehicleid)(cHealth))
	UpdateVehicleDamageStatus(vehicleid, CarInfo(vehicleid)(cVisual)(0), CarInfo(vehicleid)(cVisual)(1), CarInfo(vehicleid)(cVisual)(2), CarInfo(vehicleid)(cVisual)(3))
	
	ChangeVehicleColor(vehicleid, CarInfo(vehicleid)(cColor1), CarInfo(vehicleid)(cColor2))
	
	if(CarInfo(vehicleid)(cArmed))
	(
		CarInfo(vehicleid)(cArmed) = false
	)
	
	if(CarInfo(vehicleid)(cRegister))
	(
		string(32)

		format(string, sizeof(string), LS%d, CarInfo(vehicleid)(cUID))
		SetVehicleNumberPlate(vehicleid, string)
	)
	else
	(
		SetVehicleNumberPlate(vehicleid, _)
	)
	return 1
)

public OnVehicleDeath(vehicleid, killerid)
(

	CarInfo(vehicleid)(cHealth) = 350
	SaveVehicle(vehicleid, SAVE_VEH_COUNT)
	
	if(killerid != INVALID_PLAYER_ID)
	(
		if(GetPlayerVehicleSeat(killerid) != 0)
		(
			if(PlayerCache(killerid)(pGamePoints) ( 50)
			(
				bool:check = false
				foreach(Player, i)
				(
					if(IsPlayerInAnyVehicle(i))
					(
						vehid = GetPlayerVehicleID(i)
						if(vehid == vehicleid)
						(
							if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
							(
								if(CarInfo(vehid)(cOwner) == PlayerCache(i)(pUID))
								(
									check = true
								)
							)
							else if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
							(
								if(IsPlayerPermissedGroup(i, CarInfo(vehid)(cOwner), PERM_CARS))
								(
									check = true
								)
							)
						)
					)
				)
				if(!check)
				(
					hrp_Kick(killerid, -1, Cheater - psucie pojazdow.)
					CarInfo(vehicleid)(cHealth) = 1000
					SaveVehicle(vehicleid, SAVE_VEH_COUNT)
				)
			)
		)
		else
		(
			if(CarInfo(vehicleid)(cOwnerType) == OWNER_PLAYER)
			(
				if(CarInfo(vehicleid)(cOwner) != PlayerCache(killerid)(pUID))
				(
					hrp_Kick(killerid, -1, Cheater - psucie pojazdow.)
					CarInfo(vehicleid)(cHealth) = 1000
					SaveVehicle(vehicleid, SAVE_VEH_COUNT)
				)
			)
			else if(CarInfo(vehicleid)(cOwnerType) == OWNER_GROUP)
			(
				if(!IsPlayerPermissedGroup(killerid, CarInfo(vehicleid)(cOwner), PERM_CARS))
				(
					hrp_Kick(killerid, -1, Cheater - psucie pojazdow.)
					CarInfo(vehicleid)(cHealth) = 1000
					SaveVehicle(vehicleid, SAVE_VEH_COUNT)
				)
			)
		)
	
		hrp_VehicleActionLog(Pojazd %s (UID: %d) zostal calkowicie zniszczony przez %s (UID: %d)., CarInfo(vehicleid)(cName), CarInfo(vehicleid)(cUID), PlayerRealName(killerid), PlayerCache(killerid)(pUID))
	)
	else
	(
		hrp_VehicleActionLog(Pojazd %s (UID: %d) zostal calkowicie zniszczony., CarInfo(vehicleid)(cName), CarInfo(vehicleid)(cUID))
	)
	return 1
)

/*public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat)
(
	return 1
)*/

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
(	
	Float:PosX, Float:PosY, Float:PosZ
 	GetPlayerPos(playerid, PosX, PosY, PosZ)
	
	Float:health GetVehicleHealth(vehicleid, health)
	CarInfo(vehicleid)(cHealth) = health
	
	/*if(CarInfo(vehicleid)(cWheelBlock))
	(
		hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
	
 		string(256)
 		format(string, sizeof(string), Na ko³o tego pojazdu zosta³a na³o¿ona blokada.\nJe¿eli jesteœ w³aœcicielem tego pojazdu, musisz zg³oœiæ siê na\nkomisariat policji w celu zdjêcia blokady za podan¹ poni¿ej kwotê pieniê¿n¹.\n\nIdentyfikator pojazdu: %d\nKoszt zdjêcia blokady wynosi: $%d, CarInfo(vehicleid)(cUID), CarInfo(vehicleid)(cWheelBlock))
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)*/
	if(CarInfo(vehicleid)(cLocked))
	(
		hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~r~Ten pojazd jest zamkniety, 4000, 3)
		return 1
	)
	if(PlayerCache(playerid)(pRoll))
	(
		hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie mo¿esz wsi¹œæ do pojazdu maj¹c rolki na nogach., OK, )
		return 1
	)
	if(!ispassenger)
	(
		if(PlayerCache(playerid)(pGamePoints) ( 50)
		(
			hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie przegra³eœ jeszcze 5 godzin na serwerze i dlatego nie pozwalamy Ci u¿ywaæ pojazdów.\nNie martw siê, Twój pojazd profilowy dalej nale¿y do Ciebie i bêdziesz go móg³ u¿ywaæ po przegraniu 5 godzin., OK, )
			return 1
		)
		if(CarInfo(vehicleid)(cOwnerType) == OWNER_GROUP)
		(
			if(PlayerCache(playerid)(pHireGroup) != INVALID_GROUP_ID && PlayerCache(playerid)(pHireTime) ) 0)
			(
				group_id_fix = GetGroupID(CarInfo(vehicleid)(cOwner))
				if(GroupData(group_id_fix)(gType) != GROUP_HIRE)
				(
					hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz prowadziæ tego pojazdu., OK, )
					return 1
				)
			)
			else
			(
				if(!PlayerCache(playerid)(pDrivingLesson) && !PlayerCache(playerid)(pCourse))
				(
					if(!IsPlayerPermissedGroup(playerid, CarInfo(vehicleid)(cOwner), PERM_CARS))
					(
						hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz prowadziæ tego pojazdu., OK, )
						return 1
					)
				)
				else
				(
					group_id_fix = GetGroupID(CarInfo(vehicleid)(cOwner))
					if(GroupData(group_id_fix)(gType) != GROUP_DRIVING)
					(
						hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz prowadziæ tego pojazdu., OK, )
						return 1
					)
				)
			)
		)
		if((PlayerCache(playerid)(pBlock) & BLOCK_VEH))
		(
			hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Na Twoj¹ potaæ zosta³a na³o¿ona blokada prowadzenia pojazdów,\njeœli minie okres zarzucony przez nadaj¹cego karê, mo¿esz\nnapisaæ apelacjê, by kara ta zosta³a Ci zdjêta., OK, )
			return 1
		)
	)
 	PlayerCache(playerid)(pLastVeh) = vehicleid
 	PlayerCache(playerid)(pEnteringVeh) = gettime()
 	
	if(CarInfo(vehicleid)(cAccess) & VEH_ACCESS_DIM)
	(
		if(!PlayerCache(playerid)(pMaskUID))
		(
			if(!PlayerCache(playerid)(pAdminDuty))
			(
				name(32), string(1024)
				format(name, sizeof(name), Nieznajomy_%s, CharCode(playerid))
				strmid(PlayerCache(playerid)(pName), name, 0, strlen(name), 32)
				
				format(string, sizeof(string), %s%s, PlayerName(playerid), GetPlayerStatusInfo(playerid))
				Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
			)
		)
	)
	
 	if(!ispassenger)
 	(
 		hrp_VehicleActionLog(%s (UID: %d) wsiadl do pojazdu %s (UID: %d) jako kierowca., PlayerRealName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehicleid)(cName), CarInfo(vehicleid)(cUID))
	)
	else
	(
		hrp_VehicleActionLog(%s (UID: %d) wsiadl do pojazdu %s (UID: %d) jako pasazer., PlayerRealName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehicleid)(cName), CarInfo(vehicleid)(cUID))
	)
	
	return 1
)

/*
		eksperymentujemy
*/
public OnVehicleDamageStatusUpdate(vehicleid, playerid)
(
	panels,doors,lights,tires
	GetVehicleDamageStatus(vehicleid,panels,doors,lights,tires)
	
	CarInfo(vehicleid)(cVisual)(3) = tires
	
	Float:afterCrash GetVehicleHealth(vehicleid,afterCrash)
	Float:hitValue = CarInfo(vehicleid)(cHealth) - afterCrash
	
	if(hitValue )= 350)
	(
		/*
			jak pierdoln¹³ wiêcej ni¿ 350HP to zwróæ HP
		*/
		SetVehicleHealth(vehicleid,CarInfo(vehicleid)(cHealth))
		return 1
	)
	
	if(hitValue )= 50 && afterCrash ) hitValue)
	(
		//jesli waln¹³ wiêcej ni¿ 50 HP to trzeba zakolorowaæ nick gracza na chwilê
		for(i = 0  i ( MAX_PLAYERS i++)
		(
			if(IsPlayerInVehicle(i,vehicleid))
			(
				string(128)
				if(!PlayerCache(i)(pMaskUID))
				(
					format(string, sizeof(string), %s (%d)%s, PlayerName(i), i, GetPlayerStatusInfo(i))
				)
				else
				(
					format(string, sizeof(string), %s%s, PlayerName(i), GetPlayerStatusInfo(i))
				)
				
				TextDrawShowForPlayer(playerid, Text:TextDrawHitscreen(playerid))
				//SetPlayerNormalScreenAfterHit
				SetTimerEx(SetPlayerNormalScreenAfterHit, 1000, false, d, i)
				Update3DTextLabelText(Text3D:PlayerCache(i)(pNameTag), 0xFF040088, string)
				SetTimerEx(SetPlayerNormalColor, 1000, false, d, i)
			)
		)
	)
	
	//je¿eli wózek ma wiêcej ni¿ 900HP to
	if(afterCrash )= 900)
	(
		CarInfo(vehicleid)(cVisual)(0) = 0
		CarInfo(vehicleid)(cVisual)(1) = 0
		CarInfo(vehicleid)(cVisual)(2) = 0
		UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, CarInfo(vehicleid)(cVisual)(3))
	)
	
	getVehicleRemoves(vehicleid)
	
	return 1
)

public OnPlayerExitVehicle(playerid, vehicleid)
(	
	Float:health GetVehicleHealth(vehicleid, health)
	if(health ( 350)
		health = 350
	CarInfo(vehicleid)(cHealth) = health
	return 1
)

public OnVehicleEngineStarted(vehicleid)
(
	playerid = GetVehicleDriver(vehicleid)
	if(playerid == INVALID_PLAYER_ID)
	(
		return 1
	)
	if(CarInfo(vehicleid)(cEngineTogged))
	(
		return 1
	)
	if(CarInfo(vehicleid)(cFuel) (= 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, W tym pojeŸdzie nie ma paliwa.\nZatankuj pojazd, aby móc odpaliæ silnik., OK, )
		return 1
	)
	CarInfo(vehicleid)(cEngineTogged) = true
	ChangeVehicleEngineStatus(vehicleid, CarInfo(vehicleid)(cEngineTogged))
	
	if(CarInfo(vehicleid)(cArmed))
	(
		Float:x, Float:y, Float:z
		GetPlayerPos(playerid, x, y, z)
		CreateExplosion(x, y, z, 0, 15.0)
		CarInfo(vehicleid)(cArmed) = false
	)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~w~Aby zgasic pojazd uzyj ~r~/silnik, 3000, 3)

	hrp_VehicleActionLog(%s (UID: %d) odpalil silnik pojazdu %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehicleid)(cName), CarInfo(vehicleid)(cUID))
	return 1
)

public OnVehicleRespray(playerid, vehicleid, color1, color2)
(

)

stock GetClosestVehicle(playerid, Float:odis = 5.000)
(
	Float:prevdist = odis, prevcar = INVALID_VEHICLE_ID
	for(carid = 0 carid ( MAX_VEHICLES carid++)
	(
		if(GetVehicleVirtualWorld(carid) == GetPlayerVirtualWorld(playerid))
		(
			Float:dist = GetDistanceToVehicle(playerid, carid)
			if ((dist ( prevdist))
			(
				prevdist = dist
				prevcar = carid
			)
		)
	)
	return prevcar
)

stock GetDistanceToVehicle(playerid,carid)
(
	Float:x1, Float:y1, Float:z1,
		Float:x2, Float:y2, Float:z2, Float:dis

	GetPlayerPos(playerid, x1, y1, z1)
	GetVehiclePos(carid, x2, y2, z2)

	dis = floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2))
	return floatround(dis)
)

stock PlayerToVehicle(Float:radi, playerid, vehicleid)
(
	Float:posx, Float:posy, Float:posz,
		Float:oldposx, Float:oldposy, Float:oldposz,
		Float:tempposx, Float:tempposy, Float:tempposz

	GetPlayerPos(playerid, oldposx, oldposy, oldposz)

	GetVehiclePos(vehicleid, posx, posy, posz)
	tempposx = (oldposx -posx)
	tempposy = (oldposy -posy)
	tempposz = (oldposz -posz)

	if (((tempposx ( radi) && (tempposx ) -radi)) && ((tempposy ( radi) && (tempposy ) -radi)) && ((tempposz ( radi) && (tempposz ) -radi)))
	(
		return 1
	)
	return 0
)

stock GetVehicleID(vehuid)
(
	vehid = INVALID_VEHICLE_ID
	foreach(Vehicles, h)
	(
		if(CarInfo(h)(cUID) == vehuid)
		(
			vehid = h
			break
		)
	)
	return vehid
)

stock SpawnVehicle(uid)
(
	mysql_query_format(SELECT car_model, car_posx, car_posy, car_posz, car_posa, car_color1, car_color2 FROM hrp_cars WHERE car_uid = %d LIMIT 1, uid)
	
	data(256)
	modelid, Float:posx, Float:posy, Float:posz, Float:posa, color1, color2

	print((load) Wczytujê dane pojazdu wymagane do spawnu...)

	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)dffffdd, modelid, posx, posy, posz, posa, color1, color2)
	)
	mysql_free_result()
	// gameid = CreateVehicle(modelid, posx, posy, posz, posa, color1, color2, 7200)
	// Ma³a modyfikacja prima
	gameid = INVALID_VEHICLE_ID
	if(IS_PRIMA_APRILIS)
		gameid = CreateVehicle(542, posx, posy, posz, posa, color1, color2, 7200)
	else
		if(modelid == 544)
		(
			gameid = CreateVehicle(modelid, posx, posy, posz, posa, color1, color2, 7200, 1)
		)
		else
		(
			gameid = CreateVehicle(modelid, posx, posy, posz, posa, color1, color2, 7200)
		)
		
	// Koniec prima moda

	
	print((load) Dane wymagane do spawnu pojazdu zosta³y pomyœlnie wczytane.)

	LoadVehicle(gameid, uid)
	return gameid
)

stock UnspawnVehicle(uid)
(
	vehid = GetVehicleID(uid), Float:health
	GetVehicleHealth(vehid, health)
	
	if(IsValidObject(CarInfo(vehid)(cPoliceGrill)))
	(
		DestroyObject(CarInfo(vehid)(cPoliceGrill))
	)
	
	if(CarInfo(vehid)(cFlashed))
		CarInfo(vehid)(cFlashed) = false
	
	GetVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))
	
	if(health ) CarInfo(vehid)(cHealth))
	(
		printf((VEHICLE_WARNING) Odspawnowuje fure %d ktora ma %f hp wedlug gry a %f wedlug zmiennej. Sprawdzic gnoja., CarInfo(vehid)(cUID), health, CarInfo(vehid)(cHealth))
	) else (
		GetVehicleHealth(vehid, CarInfo(vehid)(cHealth))
	)

	SaveVehicle(vehid, SAVE_VEH_COUNT)
	DestroyVehicle(vehid)
	
	for (i = 0 i ( 14 i++)
	(
		if(CarInfo(vehid)(cComponent)(i) != 0)
		(
			hrp_RemoveVehicleComponent(vehid, CarInfo(vehid)(cComponent)(i) + 999)
		)
	)
	Itter_Remove(Vehicles, vehid)
	return vehid
)

stock GetVehicleSpeed(vehid)
(
	Float:vaX, Float:vaY, Float:vaZ
	GetVehicleVelocity(vehid, vaX, vaY, vaZ)
	return floatround(floatsqroot(vaX*vaX + vaY*vaY + vaZ*vaZ))
)

stock IsAnyPlayerInVehicle(vehicleid)
(
	if(vehicleid)
	(
		foreach(Player, i)
		(
			if(GetPlayerVehicleID(i) == vehicleid)
			(
				return true
			)
		)
	)
	return false
)

stock GetVehicleDriver(vehicleid)
(
	foreach(Player, i)
	(
		if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
		(
			if(GetPlayerVehicleID(i) == vehicleid)
			(
				return i
			)
		)
	)
	return INVALID_PLAYER_ID
)

stock GetSpawnedVehicleID(veh_uid)
(
	foreach(Vehicles, vehid)
	(
		if(CarInfo(vehid)(cUID) == veh_uid)
		(
			return vehid
		)
	)
	return INVALID_VEHICLE_ID
)

stock IsSeatFree(vehid, seatid)
(
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(GetPlayerVehicleID(i) == vehid)
			(
				if(GetPlayerVehicleSeat(i) == seatid)
				(
					return false
				)
			)
		)
	)
	return true
)

stock HavePlayerVehicleKeys(playerid, vehid)
(
	have = false
 	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID) != 0)
		(
			if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
			(
				if(ItemInfo(i)(iType) == ITEM_KEYS)
				(
					if(ItemInfo(i)(iValue1) == CarInfo(vehid)(cUID))
					(
						have = true
						break
					)
				)
			)
		)
	)
	return have
)

stock GetVehicleFuelTypeName(fuel_type)
(
	fuel_type_name(12)
	if(fuel_type == TYPE_BENS) 		fuel_type_name = Benzyna
	if(fuel_type == TYPE_GAS) 		fuel_type_name = Gaz
	if(fuel_type == TYPE_DIESEL) 	fuel_type_name = Ropa
	if(fuel_type == TYPE_AIRFUEL) 	fuel_type_name = Nafta
	return fuel_type_name
)

stock ChangeSelectedWindowStatus(vehicleid, window)
(
	if(window == 0) // otwiera
	(

		CarInfo(vehicleid)(cDriverWindowOpen) = 0
		CarInfo(vehicleid)(cPassengerWindowOpen) = 0
		CarInfo(vehicleid)(cLeftWindowOpen) = 0
		CarInfo(vehicleid)(cRightWindowOpen) = 0
		CarInfo(vehicleid)(cWindowOpen) = true
	)
	else if(window == 1) // zamyka
	(
		CarInfo(vehicleid)(cDriverWindowOpen) = 1
		CarInfo(vehicleid)(cPassengerWindowOpen) = 1
		CarInfo(vehicleid)(cLeftWindowOpen) = 1
		CarInfo(vehicleid)(cRightWindowOpen) = 1
		CarInfo(vehicleid)(cWindowOpen) = false
	)
	else
	(
		return false
	)
	SetVehicleParamsCarWindows(vehicleid, CarInfo(vehicleid)(cDriverWindowOpen), CarInfo(vehicleid)(cPassengerWindowOpen), CarInfo(vehicleid)(cLeftWindowOpen), CarInfo(vehicleid)(cRightWindowOpen))
	return 1
)

stock ChangeWindowStatus(vehicleid, playerid)
(
	driver, passenger, backleft, backright
	GetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, backright)
	if(GetPlayerVehicleSeat(playerid) == 0) // kierowca
	(
		if(driver == 0) // otwarte
		(
			CarInfo(vehicleid)(cDriverWindowOpen) = 1
		)
		else
		(
			CarInfo(vehicleid)(cDriverWindowOpen) = 0
		)
	)
	else if(GetPlayerVehicleSeat(playerid) == 1) // pasazer
	(
		if(passenger == 0) // otwarte
		(
			CarInfo(vehicleid)(cPassengerWindowOpen) = 1
		)
		else
		(
			CarInfo(vehicleid)(cPassengerWindowOpen) = 0
		)
	)
	else if(GetPlayerVehicleSeat(playerid) == 2) // tyl lewo
	(
		if(backleft == 0) // otwarte
		(
			CarInfo(vehicleid)(cLeftWindowOpen) = 1
		)
		else
		(
			CarInfo(vehicleid)(cLeftWindowOpen) = 0
		)
	)
	else if(GetPlayerVehicleSeat(playerid) == 3) // tyl prawo
	(
		if(backright == 0) // otwarte
		(
			CarInfo(vehicleid)(cRightWindowOpen) = 1
		)
		else
		(
			CarInfo(vehicleid)(cRightWindowOpen) = 0
		)
	)
	else
	(
		return false
	)
	SetVehicleParamsCarWindows(vehicleid, CarInfo(vehicleid)(cDriverWindowOpen), CarInfo(vehicleid)(cPassengerWindowOpen), CarInfo(vehicleid)(cLeftWindowOpen), CarInfo(vehicleid)(cRightWindowOpen))
	if(CarInfo(vehicleid)(cDriverWindowOpen) == 0 || CarInfo(vehicleid)(cPassengerWindowOpen) == 0 || CarInfo(vehicleid)(cLeftWindowOpen) == 0 || CarInfo(vehicleid)(cRightWindowOpen) == 0)
	(
		CarInfo(vehicleid)(cWindowOpen) = true
	)
	if(CarInfo(vehicleid)(cDriverWindowOpen) == 1 && CarInfo(vehicleid)(cPassengerWindowOpen) == 1 && CarInfo(vehicleid)(cLeftWindowOpen) == 1 && CarInfo(vehicleid)(cRightWindowOpen) == 1)
	(
		CarInfo(vehicleid)(cWindowOpen) = false
	)
	return 1
)

stock GetPlayerWindowStatus(vehicleid, playerid)
(
	if(GetPlayerVehicleSeat(playerid) == 0) //kierowca
	(
		if(CarInfo(vehicleid)(cDriverWindowOpen) == 0) // otwarte
		(
			return true
		)
		else
		(
			return false
		)
	)
	if(GetPlayerVehicleSeat(playerid) == 1) //pasazer
	(
		if(CarInfo(vehicleid)(cPassengerWindowOpen) == 0) // otwarte
		(
			return true
		)
		else
		(
			return false
		)
	)
	if(GetPlayerVehicleSeat(playerid) == 2) //tyl lewo
	(
		if(CarInfo(vehicleid)(cLeftWindowOpen) == 0) // otwarte
		(
			return true
		)
		else
		(
			return false
		)
	)
	if(GetPlayerVehicleSeat(playerid) == 3) //tyl prawo
	(
		if(CarInfo(vehicleid)(cRightWindowOpen) == 0) // otwarte
		(
			return true
		)
		else
		(
			return false
		)
	)
	return false
)

stock ChangeVehicleEngineStatus(vehicleid, toggle)
(
	engine, lights, alarm, doors, bonnet, boot, objective

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
	SetVehicleParamsEx(vehicleid, toggle, lights, alarm, doors, bonnet, boot, objective)
	
	if(toggle == 1)
	(
		CarInfo(vehicleid)(cEBreak) = false
	)
	
	return toggle
)

stock GetVehicleEngineStatus(vehicleid)
(
	engine, lights, alarm, doors, bonnet, boot, objective
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
	return engine
)

stock SetVehicleLock(vehicleid, toggle)
(
	engine, lights, alarm, doors, bonnet, boot, objective

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, toggle, bonnet, boot, objective)
	return toggle
)

stock ChangeVehicleLightsStatus(vehicleid, toggle)
(
	engine, lights, alarm, doors, bonnet, boot, objective

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
	SetVehicleParamsEx(vehicleid, engine, toggle, alarm, doors, bonnet, boot, objective)
	return toggle
)

stock GetVehicleLightsStatus(vehicleid)
(
	engine, lights, alarm, doors, bonnet, boot, objective
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
	return lights
)

stock ChangeVehicleBonnetStatus(vehicleid, toggle)
(
	engine, lights, alarm, doors, bonnet, boot, objective

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, toggle, boot, objective)
	return toggle
)

stock GetVehicleBonnetStatus(vehicleid)
(
	engine, lights, alarm, doors, bonnet, boot, objective
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
	return bonnet
)

stock ChangeVehicleBootStatus(vehicleid, toggle)
(
	engine, lights, alarm, doors, bonnet, boot, objective

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
	SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, toggle, objective)
	return toggle
)

stock GetVehicleBootStatus(vehicleid)
(
	engine, lights, alarm, doors, bonnet, boot, objective
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective)
	return boot
)

stock GetVehicleRotation(vehicleid, &Float: heading,  &Float: attitude,  &Float: bank)
(
	new
		Float: quat_w,
		Float: quat_x,
		Float: quat_y,
		Float: quat_z

	GetVehicleRotationQuat(vehicleid, quat_w, quat_x, quat_y, quat_z)
	ConvertNonNormaQuatToEuler(quat_w, quat_x, quat_z, quat_y,  heading,  attitude,  bank)

	bank = -1 * bank
	return 1
)

stock IsVehicleInRange(vehid, Float:pX, Float:pY, Float:pZ, range)
(
	if(CarInfo(vehid)(cUID))
	(
		Float:cX, Float:cY, Float:cZ, Float:distance
		GetVehiclePos(vehid, cX, cY, cZ)
		distance = floatsqroot(floatpower(floatabs(floatsub(cX,pX)),2) + floatpower(floatabs(floatsub(cY,pY)),2) + floatpower(floatabs(floatsub(cZ,pZ)),2))
		return (distance (= range)? 1 : 0
	)
	return 0
)

stock GetVehicleModelByName(veh_name(32))
(
	for (veh = 0 veh ( sizeof(VehicleData) veh++)
	(
		if(!strcmp(veh_name, VehicleData(veh)(vName), true))
		(
			return veh + 400
		)
	)
	return 1
)

stock GetItemsCountInVehicle(vehid, item_type)
(
	mysql_query_format(SELECT count(item_uid) as item_count FROM hrp_items WHERE item_place = %d AND item_owner = %d AND item_type = %d, PLACE_VEHICLE, CarInfo(vehid)(cUID), item_type)
	new	item_count, data(128)
	mysql_store_result()
	mysql_fetch_row(data, |)
	sscanf(data, p(|)d, item_count)
	mysql_free_result()
	
	return item_count
)

stock DeleteVehicleItemsByType(vehid, type, count)
(
	mysql_query_format(DELETE FROM hrp_items WHERE item_place = %d AND item_owner = %d AND item_type = %d LIMIT %d, PLACE_VEHICLE, CarInfo(vehid)(cUID), type, count)
	return mysql_affected_rows()
)

stock IsGroundVehicle(model)
(
	if(model == 592) return false
	else if(model == 577) return false
	else if(model == 511) return false
	else if(model == 512) return false
	else if(model == 593) return false
	else if(model == 520) return false
	else if(model == 553) return false
	else if(model == 476) return false
	else if(model == 519) return false
	else if(model == 460) return false
	else if(model == 513) return false
	else if(model == 548) return false
	else if(model == 425) return false
	else if(model == 417) return false
	else if(model == 487) return false
	else if(model == 488) return false
	else if(model == 497) return false
	else if(model == 563) return false
	else if(model == 447) return false
	else if(model == 469) return false
	else if(model == 472) return false
	else if(model == 473) return false
	else if(model == 493) return false
	else if(model == 595) return false
	else if(model == 484) return false
	else if(model == 430) return false
	else if(model == 453) return false
	else if(model == 452) return false
	else if(model == 446) return false
	else if(model == 454) return false
	else if(model == 464) return false
	else if(model == 465) return false
	else if(model == 501) return false
	else if(model == 539) return false
   
	return true
)

stock HasWindow(vehid)
(
	model = GetVehicleModel(vehid)
	if(model == 509) return false
	else if(model == 481) return false
	else if(model == 510) return false
	else if(model == 462) return false
	else if(model == 448) return false
	else if(model == 581) return false
	else if(model == 522) return false
	else if(model == 461) return false
	else if(model == 521) return false
	else if(model == 523) return false
	else if(model == 463) return false
	else if(model == 586) return false
	else if(model == 468) return false
	else if(model == 471) return false
	else if(model == 472) return false
	else if(model == 473) return false
	else if(model == 493) return false
	else if(model == 595) return false
	else if(model == 484) return false
	else if(model == 430) return false
	else if(model == 453) return false
	else if(model == 452) return false
	else if(model == 446) return false
	else if(model == 454) return false
	else if(model == 441) return false
	else if(model == 457) return false
	else if(model == 464) return false
	else if(model == 465) return false
	else if(model == 485) return false
	else if(model == 486) return false
	else if(model == 501) return false
	else if(model == 530) return false
	else if(model == 539) return false
	else if(model == 564) return false
	else if(model == 571) return false
	else if(model == 572) return false
	else if(model == 594) return false
	else if(model == 571) return false
	else if(model == 571) return false
	else if(model == 504) return false
	else if(model == 568) return false

	return true
)

stock GetVehicleMaxFuel(model)
(
	if(model == 400) return 70
	else if(model == 401) return 52
	else if(model == 402) return 60
	else if(model == 403) return 400
	else if(model == 404) return 50
	else if(model == 405) return 52
	else if(model == 406) return 150
	else if(model == 407) return 250
	else if(model == 408) return 150
	else if(model == 409) return 110
	else if(model == 410) return 66
	else if(model == 411) return 66
	else if(model == 412) return 52
	else if(model == 413) return 80
	else if(model == 414) return 120
	else if(model == 415) return 76
	else if(model == 416) return 120
	else if(model == 417) return 408
	else if(model == 418) return 80
	else if(model == 419) return 72
	else if(model == 420) return 80
	else if(model == 421) return 82
	else if(model == 422) return 80
	else if(model == 423) return 90
	else if(model == 424) return 30
	else if(model == 425) return 500
	else if(model == 426) return 70
	else if(model == 427) return 120
	else if(model == 428) return 120
	else if(model == 429) return 68
	else if(model == 430) return 220
	else if(model == 431) return 315
	else if(model == 432) return 1020
	else if(model == 433) return 430
	else if(model == 434) return 30
	else if(model == 435) return 0
	else if(model == 436) return 60
	else if(model == 437) return 310
	else if(model == 438) return 80
	else if(model == 439) return 72
	else if(model == 440) return 80
	else if(model == 441) return 5
	else if(model == 442) return 61
	else if(model == 443) return 180
	else if(model == 444) return 162
	else if(model == 445) return 56
	else if(model == 446) return 101
	else if(model == 447) return 140
	else if(model == 448) return 7
	else if(model == 449) return 0
	else if(model == 450) return 0 
	else if(model == 451) return 78
	else if(model == 452) return 111
	else if(model == 453) return 201
	else if(model == 454) return 221
	else if(model == 455) return 198
	else if(model == 456) return 101
	else if(model == 457) return 15
	else if(model == 458) return 70
	else if(model == 459) return 84
	else if(model == 460) return 30
	else if(model == 461) return 25
	else if(model == 462) return 7
	else if(model == 463) return 30
	else if(model == 464) return 5
	else if(model == 465) return 5
	else if(model == 466) return 71
	else if(model == 467) return 61
	else if(model == 468) return 27
	else if(model == 469) return 50
	else if(model == 470) return 110
	else if(model == 471) return 35
	else if(model == 472) return 110
	else if(model == 473) return 69
	else if(model == 474) return 70
	else if(model == 475) return 71 
	else if(model == 476) return 68
	else if(model == 477) return 69
	else if(model == 478) return 45
	else if(model == 479) return 61
	else if(model == 480) return 67
	else if(model == 481) return 0
	else if(model == 482) return 96
	else if(model == 483) return 75
	else if(model == 484) return 87
	else if(model == 485) return 40
	else if(model == 486) return 141
	else if(model == 487) return 123
	else if(model == 488) return 121
	else if(model == 489) return 91
	else if(model == 490) return 101
	else if(model == 491) return 81
	else if(model == 492) return 62
	else if(model == 493) return 130
	else if(model == 494) return 99
	else if(model == 495) return 81
	else if(model == 496) return 61
	else if(model == 497) return 140
	else if(model == 498) return 121
	else if(model == 499) return 104
	else if(model == 500) return 71
	else if(model == 501) return 5
	else if(model == 502) return 96
	else if(model == 503) return 97
	else if(model == 504) return 91
	else if(model == 505) return 84
	else if(model == 506) return 67
	else if(model == 507) return 81
	else if(model == 508) return 133
	else if(model == 509) return 0
	else if(model == 510) return 0
	else if(model == 511) return 210
	else if(model == 512) return 130
	else if(model == 513) return 54
	else if(model == 514) return 300
	else if(model == 515) return 300
	else if(model == 516) return 63
	else if(model == 517) return 64
	else if(model == 518) return 67
	else if(model == 519) return 300
	else if(model == 520) return 290
	else if(model == 521) return 35
	else if(model == 522) return 35
	else if(model == 523) return 121
	else if(model == 524) return 91
	else if(model == 525) return 65
	else if(model == 526) return 63
	else if(model == 527) return 71
	else if(model == 528) return 71
	else if(model == 529) return 67
	else if(model == 530) return 12
	else if(model == 531) return 21
	else if(model == 532) return 36
	else if(model == 533) return 61
	else if(model == 534) return 71
	else if(model == 535) return 85
	else if(model == 536) return 69
	else if(model == 537) return 0
	else if(model == 538) return 0
	else if(model == 539) return 33
	else if(model == 540) return 60
	else if(model == 541) return 71
	else if(model == 542) return 69
	else if(model == 543) return 60
	else if(model == 544) return 120
	else if(model == 545) return 74
	else if(model == 546) return 64
	else if(model == 547) return 67
	else if(model == 548) return 210
	else if(model == 549) return 71
	else if(model == 550) return 64
	else if(model == 551) return 64
	else if(model == 552) return 68
	else if(model == 553) return 330
	else if(model == 554) return 81
	else if(model == 555) return 61
	else if(model == 556) return 123
	else if(model == 557) return 124
	else if(model == 558) return 61
	else if(model == 559) return 63
	else if(model == 560) return 71
	else if(model == 561) return 74
	else if(model == 562) return 66
	else if(model == 563) return 210
	else if(model == 564) return 0
	else if(model == 565) return 57
	else if(model == 566) return 65
	else if(model == 567) return 66
	else if(model == 568) return 45
	else if(model == 569) return 0
	else if(model == 570) return 0
	else if(model == 571) return 10
	else if(model == 572) return 10
	else if(model == 573) return 121
	else if(model == 574) return 21
	else if(model == 575) return 71
	else if(model == 576) return 75
	else if(model == 577) return 900
	else if(model == 578) return 210
	else if(model == 579) return 85
	else if(model == 580) return 80
	else if(model == 581) return 31
	else if(model == 582) return 81
	else if(model == 583) return 20
	else if(model == 584) return 0
	else if(model == 585) return 64
	else if(model == 586) return 30
	else if(model == 587) return 66
	else if(model == 588) return 79
	else if(model == 589) return 59
	else if(model == 590) return 0
	else if(model == 591) return 0
	else if(model == 592) return 0
	else if(model == 593) return 110
	else if(model == 594) return 0
	else if(model == 595) return 151
	else if(model == 596) return 89
	else if(model == 597) return 89
	else if(model == 598) return 89
	else if(model == 599) return 94
	else if(model == 600) return 61
	else if(model == 601) return 120
	else if(model == 602) return 61
	else if(model == 603) return 59
	else if(model == 604) return 91
	else if(model == 605) return 64
	else if(model == 606) return 0
	else if(model == 607) return 0
	else if(model == 608) return 0
	else if(model == 609) return 99
	else if(model == 610) return 0
	else if(model == 611) return 0
	else return 0
)

stock GetVehicleFuelType(model)
(
	if(model == 400) return TYPE_DIESEL
	else if(model == 401) return TYPE_BENS
	else if(model == 402) return TYPE_BENS
	else if(model == 403) return TYPE_DIESEL
	else if(model == 404) return TYPE_BENS
	else if(model == 405) return TYPE_BENS
	else if(model == 406) return TYPE_BENS
	else if(model == 407) return TYPE_DIESEL
	else if(model == 408) return TYPE_DIESEL
	else if(model == 409) return TYPE_BENS
	else if(model == 410) return TYPE_BENS
	else if(model == 411) return TYPE_BENS
	else if(model == 412) return TYPE_BENS
	else if(model == 413) return TYPE_DIESEL
	else if(model == 414) return TYPE_DIESEL
	else if(model == 415) return TYPE_BENS
	else if(model == 416) return TYPE_DIESEL
	else if(model == 417) return TYPE_AIRFUEL
	else if(model == 418) return TYPE_DIESEL
	else if(model == 419) return TYPE_BENS
	else if(model == 420) return TYPE_BENS
	else if(model == 421) return TYPE_BENS
	else if(model == 422) return TYPE_DIESEL
	else if(model == 423) return TYPE_DIESEL
	else if(model == 424) return TYPE_DIESEL
	else if(model == 425) return TYPE_AIRFUEL
	else if(model == 426) return TYPE_BENS
	else if(model == 427) return TYPE_DIESEL
	else if(model == 428) return TYPE_DIESEL
	else if(model == 429) return TYPE_BENS
	else if(model == 430) return TYPE_BENS
	else if(model == 431) return TYPE_DIESEL
	else if(model == 432) return TYPE_DIESEL
	else if(model == 433) return TYPE_DIESEL
	else if(model == 434) return TYPE_BENS
	else if(model == 435) return TYPE_BENS
	else if(model == 436) return TYPE_BENS
	else if(model == 437) return TYPE_DIESEL
	else if(model == 438) return TYPE_BENS
	else if(model == 439) return TYPE_BENS
	else if(model == 440) return TYPE_DIESEL
	else if(model == 441) return TYPE_BENS
	else if(model == 442) return TYPE_BENS
	else if(model == 443) return TYPE_DIESEL
	else if(model == 444) return TYPE_DIESEL
	else if(model == 445) return TYPE_BENS
	else if(model == 446) return TYPE_BENS
	else if(model == 447) return TYPE_AIRFUEL
	else if(model == 448) return TYPE_BENS
	else if(model == 449) return TYPE_BENS
	else if(model == 450) return TYPE_BENS 
	else if(model == 451) return TYPE_BENS
	else if(model == 452) return TYPE_BENS
	else if(model == 453) return TYPE_BENS
	else if(model == 454) return TYPE_BENS
	else if(model == 455) return TYPE_DIESEL
	else if(model == 456) return TYPE_DIESEL
	else if(model == 457) return TYPE_BENS
	else if(model == 458) return TYPE_DIESEL
	else if(model == 459) return TYPE_DIESEL
	else if(model == 460) return TYPE_AIRFUEL
	else if(model == 461) return TYPE_BENS
	else if(model == 462) return TYPE_BENS
	else if(model == 463) return TYPE_BENS
	else if(model == 464) return TYPE_AIRFUEL
	else if(model == 465) return TYPE_AIRFUEL
	else if(model == 466) return TYPE_BENS
	else if(model == 467) return TYPE_DIESEL
	else if(model == 468) return TYPE_BENS
	else if(model == 469) return TYPE_AIRFUEL
	else if(model == 470) return TYPE_DIESEL
	else if(model == 471) return TYPE_BENS
	else if(model == 472) return TYPE_BENS
	else if(model == 473) return TYPE_BENS
	else if(model == 474) return TYPE_BENS
	else if(model == 475) return TYPE_BENS
	else if(model == 476) return TYPE_AIRFUEL
	else if(model == 477) return TYPE_BENS
	else if(model == 478) return TYPE_DIESEL
	else if(model == 479) return TYPE_DIESEL
	else if(model == 480) return TYPE_BENS
	else if(model == 481) return TYPE_BENS
	else if(model == 482) return TYPE_DIESEL
	else if(model == 483) return TYPE_DIESEL
	else if(model == 484) return TYPE_BENS
	else if(model == 485) return TYPE_BENS
	else if(model == 486) return TYPE_DIESEL
	else if(model == 487) return TYPE_AIRFUEL
	else if(model == 488) return TYPE_AIRFUEL
	else if(model == 489) return TYPE_DIESEL
	else if(model == 490) return TYPE_DIESEL
	else if(model == 491) return TYPE_BENS
	else if(model == 492) return TYPE_BENS
	else if(model == 493) return TYPE_BENS
	else if(model == 494) return TYPE_BENS
	else if(model == 495) return TYPE_BENS
	else if(model == 496) return TYPE_BENS
	else if(model == 497) return TYPE_AIRFUEL
	else if(model == 498) return TYPE_DIESEL
	else if(model == 499) return TYPE_DIESEL
	else if(model == 500) return TYPE_BENS
	else if(model == 501) return TYPE_AIRFUEL
	else if(model == 502) return TYPE_BENS
	else if(model == 503) return TYPE_BENS
	else if(model == 504) return TYPE_BENS
	else if(model == 505) return TYPE_DIESEL
	else if(model == 506) return TYPE_BENS
	else if(model == 507) return TYPE_BENS
	else if(model == 508) return TYPE_DIESEL
	else if(model == 509) return TYPE_BENS
	else if(model == 510) return TYPE_BENS
	else if(model == 511) return TYPE_AIRFUEL
	else if(model == 512) return TYPE_AIRFUEL
	else if(model == 513) return TYPE_AIRFUEL
	else if(model == 514) return TYPE_DIESEL
	else if(model == 515) return TYPE_DIESEL
	else if(model == 516) return TYPE_BENS
	else if(model == 517) return TYPE_BENS
	else if(model == 518) return TYPE_BENS
	else if(model == 519) return TYPE_AIRFUEL
	else if(model == 520) return TYPE_AIRFUEL
	else if(model == 521) return TYPE_BENS
	else if(model == 522) return TYPE_BENS
	else if(model == 523) return TYPE_BENS
	else if(model == 524) return TYPE_DIESEL
	else if(model == 525) return TYPE_DIESEL
	else if(model == 526) return TYPE_BENS
	else if(model == 527) return TYPE_BENS
	else if(model == 528) return TYPE_DIESEL
	else if(model == 529) return TYPE_BENS
	else if(model == 530) return TYPE_BENS
	else if(model == 531) return TYPE_DIESEL
	else if(model == 532) return TYPE_DIESEL
	else if(model == 533) return TYPE_BENS
	else if(model == 534) return TYPE_BENS
	else if(model == 535) return TYPE_BENS
	else if(model == 536) return TYPE_BENS
	else if(model == 537) return TYPE_BENS
	else if(model == 538) return TYPE_BENS
	else if(model == 539) return TYPE_BENS
	else if(model == 540) return TYPE_BENS
	else if(model == 541) return TYPE_BENS
	else if(model == 542) return TYPE_BENS
	else if(model == 543) return TYPE_DIESEL
	else if(model == 544) return TYPE_DIESEL
	else if(model == 545) return TYPE_BENS
	else if(model == 546) return TYPE_BENS
	else if(model == 547) return TYPE_BENS
	else if(model == 548) return TYPE_AIRFUEL
	else if(model == 549) return TYPE_BENS
	else if(model == 550) return TYPE_BENS
	else if(model == 551) return TYPE_BENS
	else if(model == 552) return TYPE_DIESEL
	else if(model == 553) return TYPE_AIRFUEL
	else if(model == 554) return TYPE_DIESEL
	else if(model == 555) return TYPE_BENS
	else if(model == 556) return TYPE_BENS
	else if(model == 557) return TYPE_BENS
	else if(model == 558) return TYPE_BENS
	else if(model == 559) return TYPE_BENS
	else if(model == 560) return TYPE_BENS
	else if(model == 561) return TYPE_DIESEL
	else if(model == 562) return TYPE_BENS
	else if(model == 563) return TYPE_AIRFUEL
	else if(model == 564) return TYPE_BENS
	else if(model == 565) return TYPE_BENS
	else if(model == 566) return TYPE_BENS
	else if(model == 567) return TYPE_BENS
	else if(model == 568) return TYPE_BENS
	else if(model == 569) return TYPE_BENS
	else if(model == 570) return TYPE_BENS
	else if(model == 571) return TYPE_BENS
	else if(model == 572) return TYPE_BENS
	else if(model == 573) return TYPE_DIESEL
	else if(model == 574) return TYPE_BENS
	else if(model == 575) return TYPE_BENS
	else if(model == 576) return TYPE_BENS
	else if(model == 577) return TYPE_AIRFUEL
	else if(model == 578) return TYPE_DIESEL
	else if(model == 579) return TYPE_DIESEL
	else if(model == 580) return TYPE_DIESEL
	else if(model == 581) return TYPE_BENS
	else if(model == 582) return TYPE_BENS
	else if(model == 583) return TYPE_BENS
	else if(model == 584) return TYPE_BENS
	else if(model == 585) return TYPE_BENS
	else if(model == 586) return TYPE_BENS
	else if(model == 587) return TYPE_BENS
	else if(model == 588) return TYPE_DIESEL
	else if(model == 589) return TYPE_BENS
	else if(model == 590) return TYPE_BENS
	else if(model == 591) return TYPE_BENS
	else if(model == 592) return TYPE_AIRFUEL
	else if(model == 593) return TYPE_AIRFUEL
	else if(model == 594) return TYPE_BENS
	else if(model == 595) return TYPE_BENS
	else if(model == 596) return TYPE_BENS
	else if(model == 597) return TYPE_BENS
	else if(model == 598) return TYPE_BENS
	else if(model == 599) return TYPE_DIESEL
	else if(model == 600) return TYPE_BENS
	else if(model == 601) return TYPE_DIESEL
	else if(model == 602) return TYPE_BENS
	else if(model == 603) return TYPE_BENS
	else if(model == 604) return TYPE_BENS
	else if(model == 605) return TYPE_DIESEL
	else if(model == 606) return TYPE_BENS
	else if(model == 607) return TYPE_BENS
	else if(model == 608) return TYPE_BENS
	else if(model == 609) return TYPE_DIESEL
	else if(model == 610) return TYPE_BENS
	else if(model == 611) return TYPE_BENS
	else return 0
)

stock Float:GetVehicleEqWeight(veh_uid)
(
	desc(8), Float:total_weight = 0.0

	mysql_query_format(SELECT sum(item_weight) FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_VEHICLE, veh_uid)
	mysql_store_result()
	if(mysql_fetch_row(desc, |))
	(
		sscanf(desc, p(|)f, total_weight)
	)
	mysql_free_result()

	return total_weight
)

stock Float:GetVehicleCapacity(model)
(
	if(model == 400) return 73.0 // landstalker
	else if(model == 401) return 52.0 // bravura
	else if(model == 402) return 46.0 // buffalo
	else if(model == 403) return 400.0 // linerunner
	else if(model == 404) return 70.0 // perenial
	else if(model == 405) return 53.0 // sentinel
	else if(model == 406) return 150.0 // dumper
	else if(model == 407) return 80.0 // firetruck
	else if(model == 408) return 150.0 // trashmaster
	else if(model == 409) return 53.0 // stretch
	else if(model == 410) return 35.0 // manana
	else if(model == 411) return 25.0 // infernus
	else if(model == 412) return 52.0 // voodoo
	else if(model == 413) return 110.0 // pony
	else if(model == 414) return 120.0 // muke
	else if(model == 415) return 20.0 // cheetah
	else if(model == 416) return 120.0 // ambulance
	else if(model == 417) return 400.0 // leviathan
	else if(model == 418) return 80.0 // moonbeam
	else if(model == 419) return 48.0 // esperanto
	else if(model == 420) return 54.0 // taxi
	else if(model == 421) return 52.0 // washington
	else if(model == 422) return 80.0 // bobcat
	else if(model == 423) return 90.0 // mr whoopee
	else if(model == 424) return 10.0 // bf injection
	else if(model == 425) return 500.0 // hunter
	else if(model == 426) return 51.0 // premier
	else if(model == 427) return 9999.0 // enforcer
	else if(model == 428) return 500.0 // securicar
	else if(model == 429) return 22.0 // banshe
	else if(model == 430) return 220.0 // predator
	else if(model == 431) return 315.0 // bus
	else if(model == 432) return 1020.0 // rhino
	else if(model == 433) return 850.0 // barracks
	else if(model == 434) return 28.0 // hotkinfe
	else if(model == 435) return 0.0 // article trailer
	else if(model == 436) return 43.0 // previon
	else if(model == 437) return 310.0 // coach
	else if(model == 438) return 51.0 // cabbie
	else if(model == 439) return 38.0 // stallion
	else if(model == 440) return 150.0 // rumpo
	else if(model == 441) return 5.0 // rc bandit
	else if(model == 442) return 80.0 // romero
	else if(model == 443) return 50.0 // packer
	else if(model == 444) return 50.0 // monster
	else if(model == 445) return 56.0 // admiral
	else if(model == 446) return 101.0 // squallo
	else if(model == 447) return 0.0 // seasparrow
	else if(model == 448) return 5.0 // pizzaboy
	else if(model == 449) return 0.0 // tram
	else if(model == 450) return 0.0 // article trailer 2 
	else if(model == 451) return 23.0 // turismo
	else if(model == 452) return 111.0 // speeder
	else if(model == 453) return 201.0 // reefer
	else if(model == 454) return 221.0 // tropic
	else if(model == 455) return 450.0 // flatbed
	else if(model == 456) return 250.0 // yankee
	else if(model == 457) return 10.0 // caddy
	else if(model == 458) return 73.0 // solair 
	else if(model == 459) return 116.0 // topfun van
	else if(model == 460) return 30.0 // skimmer
	else if(model == 461) return 5.0 // pcj600
	else if(model == 462) return 5.0 // faggio
	else if(model == 463) return 15.0 // freway
	else if(model == 464) return 5.0 // rc baron
	else if(model == 465) return 5.0 // rc raider
	else if(model == 466) return 44.0 // glendale
	else if(model == 467) return 48.0 // oceanic
	else if(model == 468) return 5.0 // sanchez
	else if(model == 469) return 50.0 // sparrow
	else if(model == 470) return 80.0 // patriot
	else if(model == 471) return 10.0 // quad
	else if(model == 472) return 110.0
	else if(model == 473) return 55.0
	else if(model == 474) return 49.0
	else if(model == 475) return 38.0
	else if(model == 476) return 68.0
	else if(model == 477) return 25.0
	else if(model == 478) return 65.0
	else if(model == 479) return 60.0
	else if(model == 480) return 23.0
	else if(model == 481) return 0.0
	else if(model == 482) return 118.0
	else if(model == 483) return 95.0
	else if(model == 484) return 95.0
	else if(model == 485) return 0.0
	else if(model == 486) return 35.0
	else if(model == 487) return 25.0
	else if(model == 488) return 20.0
	else if(model == 489) return 83.0
	else if(model == 490) return 103.0
	else if(model == 491) return 46.0
	else if(model == 492) return 44.0
	else if(model == 493) return 47.0
	else if(model == 494) return 15.0
	else if(model == 495) return 51.0
	else if(model == 496) return 23.0
	else if(model == 497) return 85.0
	else if(model == 498) return 153.0
	else if(model == 499) return 171.0
	else if(model == 500) return 38.0
	else if(model == 501) return 0.0
	else if(model == 502) return 15.0
	else if(model == 503) return 15.0
	else if(model == 504) return 15.0
	else if(model == 505) return 78.0
	else if(model == 506) return 21.0
	else if(model == 507) return 53.0
	else if(model == 508) return 94.0
	else if(model == 509) return 0.0
	else if(model == 510) return 0.0
	else if(model == 511) return 118.0
	else if(model == 512) return 36.0
	else if(model == 513) return 10.0
	else if(model == 514) return 418.0
	else if(model == 515) return 432.0
	else if(model == 516) return 52.0
	else if(model == 517) return 48.0
	else if(model == 518) return 43.0
	else if(model == 519) return 300.0
	else if(model == 520) return 25.0
	else if(model == 521) return 5.0
	else if(model == 522) return 5.0
	else if(model == 523) return 15.0
	else if(model == 524) return 280.0
	else if(model == 525) return 80.0
	else if(model == 526) return 47.0
	else if(model == 527) return 44.0
	else if(model == 528) return 150.0
	else if(model == 529) return 37.0
	else if(model == 530) return 5.0
	else if(model == 531) return 10.0
	else if(model == 532) return 0.0
	else if(model == 533) return 34.0
	else if(model == 534) return 39.0
	else if(model == 535) return 72.0
	else if(model == 536) return 41.0
	else if(model == 537) return 0.0
	else if(model == 538) return 0.0
	else if(model == 539) return 0.0
	else if(model == 540) return 51.0
	else if(model == 541) return 28.0
	else if(model == 542) return 38.0
	else if(model == 543) return 67.0
	else if(model == 544) return 120.0
	else if(model == 545) return 41.0
	else if(model == 546) return 44.0
	else if(model == 547) return 48.0
	else if(model == 548) return 450.0
	else if(model == 549) return 32.0
	else if(model == 550) return 46.0
	else if(model == 551) return 48.0
	else if(model == 552) return 135.0
	else if(model == 553) return 950.0
	else if(model == 554) return 85.0
	else if(model == 555) return 28.0
	else if(model == 556) return 50.0
	else if(model == 557) return 50.0
	else if(model == 558) return 33.0
	else if(model == 559) return 35.0
	else if(model == 560) return 42.0
	else if(model == 561) return 76.0
	else if(model == 562) return 31.0
	else if(model == 563) return 250.0
	else if(model == 564) return 0.0
	else if(model == 565) return 55.0
	else if(model == 566) return 48.0
	else if(model == 567) return 45.0
	else if(model == 568) return 5.0
	else if(model == 569) return 0.0
	else if(model == 570) return 0.0
	else if(model == 571) return 5.0
	else if(model == 572) return 5.0
	else if(model == 573) return 250.0
	else if(model == 574) return 5.0
	else if(model == 575) return 43.0
	else if(model == 576) return 48.0
	else if(model == 577) return 900.0
	else if(model == 578) return 350.0
	else if(model == 579) return 85.0
	else if(model == 580) return 61.0
	else if(model == 581) return 5.0
	else if(model == 582) return 81.0
	else if(model == 583) return 5.0
	else if(model == 584) return 0.0
	else if(model == 585) return 51.0
	else if(model == 586) return 20.0
	else if(model == 587) return 22.0
	else if(model == 588) return 89.0
	else if(model == 589) return 59.0
	else if(model == 590) return 0.0
	else if(model == 591) return 0.0
	else if(model == 592) return 9999.0
	else if(model == 593) return 55.0
	else if(model == 594) return 0.0
	else if(model == 595) return 150.0
	else if(model == 596) return 89.0
	else if(model == 597) return 89.0
	else if(model == 598) return 89.0
	else if(model == 599) return 105.0
	else if(model == 600) return 82.0
	else if(model == 601) return 150.0
	else if(model == 602) return 33.0
	else if(model == 603) return 39.0
	else if(model == 604) return 41.0
	else if(model == 605) return 84.0
	else if(model == 606) return 0.0
	else if(model == 607) return 0.0
	else if(model == 608) return 0.0
	else if(model == 609) return 350.0
	else if(model == 610) return 0.0
	else if(model == 611) return 0.0
	else return 0.0
)

stock Float:GetVehicleEqSpace(vehid)
(
	Float:ret = GetVehicleCapacity(GetVehicleModel(vehid)) - GetVehicleEqWeight(CarInfo(vehid)(cUID))
	printf(GetVehicleEqSpace: %f, ret)
	return ret
)

stock LoadVehicleTune(vehicleid)
(
	buffer(256)
	format(buffer,sizeof(buffer),SELECT item_name,item_value1 FROM hrp_items WHERE item_vehuid=%i AND item_type=%i,CarInfo(vehicleid)(cUID),ITEM_TUNEPART)
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() (= 0)
	(
		//nie ma dodatkow
		mysql_free_result()
		return 1
	)
	else
	(
		while(mysql_fetch_row(buffer,|))
		(
			name(32),value
			sscanf(buffer,p(|)s(32)d,name,value)
			CarInfo(vehicleid)(cBoost) = CarInfo(vehicleid)(cBoost) + float(value)
		)
		
		mysql_free_result()
	)
	return 1
)

stock IsVehicleTuned(vehicleid)
(
	buffer(256)
	format(buffer,sizeof(buffer),SELECT item_name,item_value1 FROM hrp_items WHERE item_vehuid=%i AND item_type=%i,CarInfo(vehicleid)(cUID),ITEM_TUNEPART)
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() (= 0)
	(
		mysql_free_result()
		return false
	)
	else
	(
		mysql_free_result()
		return true
	)
)

stock IsVehicleHasTune(vehicleid,partid)	//do sprawdzania czy ma ju¿ tuning danego typu
(
	buffer(256)
	format(buffer,sizeof(buffer),SELECT item_name,item_value1 FROM hrp_items WHERE item_vehuid=%i AND item_type=%i AND item_value2=%i,CarInfo(vehicleid)(cUID),ITEM_TUNEPART,partid)
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() (= 0)
	(
		mysql_free_result()
		return false
	)
	else
	(
		mysql_free_result()
		return true
	)
)

stock GetVehicleTune(playerid,vehicleid)
(
	buffer(256), list(256)
	format(buffer,sizeof(buffer),SELECT item_name,item_value1 FROM hrp_items WHERE item_vehuid=%i AND item_type=%i,CarInfo(vehicleid)(cUID),ITEM_TUNEPART)
	mysql_query(buffer)
	mysql_store_result()
	while(mysql_fetch_row(buffer,|))
	(
		name(32), value
		sscanf(buffer,p(|)s(32)d,name,value)
		
		format(list,sizeof(list),%s\n%s (+%i procent),list,name,value)
	)
	mysql_free_result()
	
	ShowPlayerDialog(playerid,D_VEH_ADDONS,DIALOG_STYLE_LIST,Lista dodatków,list,Wybierz,Anuluj)
	
	return 1
)


stock Float:varX(Float:x) 
(
	Float:retVal
	tactical_x = floatround(x)
	switch(tactical_x)
	(
		case 0..1500:
			retVal = 0.0025
		case 1501..3500:
			retVal = 0.0040
		case 3501..6000:
			retVal = 0.0050
		case 6001..9000:
			retVal = 0.0060
		case 9001..13500:
			retVal = 0.0070
		case 13501..17000:
			retVal = 0.0080
		case 17001..20000:
			retVal = 0.0090
		default:
			retVal = -1
	)
	
	return retVal
)

// Pobierz permanentne uszkodzenia wozu, to taka szybka regu³a i gitara
stock getVehicleRemoves(vehicle_id)
(
	buffer(256)
	format(buffer, sizeof(buffer), SELECT remove_bonnet, remove_boot, remove_driverdoor, remove_passdoor, remove_maxhp FROM hrp_removes WHERE remove_car = %d, CarInfo(vehicle_id)(cUID))
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		rem_bonnet, rem_boot, rem_ddoor, rem_pdoor, Float:rem_maxhp
		while(mysql_fetch_row(buffer, |))
		(
			sscanf(buffer, p(|)ddddf, rem_bonnet, rem_boot, rem_ddoor, rem_pdoor, rem_maxhp)
		)
		
		panels, doors, lights, tires	
		GetVehicleDamageStatus(vehicle_id, panels, doors, lights, tires)
		
		door = encode_doors(rem_bonnet, rem_boot, rem_ddoor, rem_pdoor, 0, 0)
		UpdateVehicleDamageStatus(vehicle_id, panels, door, lights, tires)
		GetVehicleDamageStatus(vehicle_id, CarInfo(vehicle_id)(cVisual)(0), CarInfo(vehicle_id)(cVisual)(1), CarInfo(vehicle_id)(cVisual)(2), CarInfo(vehicle_id)(cVisual)(3))
		
		// HP
		if(CarInfo(vehicle_id)(cHealth) ) rem_maxhp)
		(
			CarInfo(vehicle_id)(cHealth) = rem_maxhp
			SetVehicleHealth(vehicle_id, rem_maxhp)
		)

	   	SaveVehicle(vehicle_id, SAVE_VEH_COUNT)
		SaveVehicle(vehicle_id, SAVE_VEH_ACCESS)
		
		mysql_free_result()
		return 1
	)
	else
	(
		mysql_free_result()
		return 0
	)
)

stock getCarValue(model, Float:maxhp, ddoors, pdoors, bonnet, boot)
(
	// To bêdzie funkcja do obliczania wartoœciu pojazdu w skryptowym komisie.
	cost = 0
	
	return cost
)

// Takie tam, mo¿e siê przyda
stock IsVehicleBoat(vehicleid)
(
	isboat = false
	model = GetVehicleModel(vehicleid)
	
	if(model == 473 || model == 472 || model == 493 || model == 595 || model == 484 || model == 430 || model == 453 || model == 452 || model == 446 || model == 454)
	(
		isboat = true
	)
	
	return isboat
)

stock checkVehiclesActivity()
(
	data(256), cleared = 0
	
	format(data, sizeof(data), SELECT MAX(car_uid) FROM hrp_cars)
	mysql_query(data)
	mysql_store_result()
	MAX_VEH_UID = mysql_fetch_int()
	mysql_free_result()
	
	for(i = 0 i ( MAX_VEH_UID i ++)
	(
		format(data, sizeof(data), SELECT * FROM hrp_cars WHERE car_ownertype = 1 AND car_lastactivity ( %d AND car_uid = %d AND car_activity = 1, gettime()-2629743, i)
		mysql_query(data)
		mysql_store_result()
		if(mysql_num_rows() (= 0)
		(
			mysql_free_result()
			continue
		)
		mysql_free_result()
		
		mysql_query_format(UPDATE hrp_cars SET car_activity = 0, car_posx = 1649.6169, car_posy = -1084.6721, car_posz = 23.9063, car_posa = 270.3151, car_interior = 0, car_world = 0 WHERE car_uid = %d, i)
		printf((SYSTEM-PARKING) Pojazd UID: %d zostal przeparkowany z powodu nieaktynosci gracza, i)
		cleared++
	)

	printf((SYSTEM-PARKING) Wyczyszczono %d miejsc parkingowych, cleared)
	return 1
)

stock setVehiclesActivity(playerid)
(
	buffer(256), car_uid
	format(buffer, sizeof(buffer), SELECT car_uid FROM hrp_cars WHERE car_ownertype = 1 AND car_owner = %d, PlayerCache(playerid)(pUID))
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() (= 0)
	(
		mysql_free_result()
	)
	else
	(
		while(mysql_fetch_row(buffer, |))
		(
			sscanf(buffer, p(|)d, car_uid)

			mysql_query_format(UPDATE hrp_cars SET car_lastactivity = %d, car_activity = 1 WHERE car_ownertype = 1 AND car_owner = %d, gettime(), PlayerCache(playerid)(pUID))

		)	
		mysql_free_result()
	)
	return 1
)

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat)
(
	// Anti Cheat
	//if(PlayerCache(playerid)(pHours) ( 2 && PlayerCache(playerid)(pGamePoints) ( 30 && PlayerCache(playerid)(pAdmin) == 0)
	if(PlayerCache(playerid)(pHours) ( 2 && PlayerCache(playerid)(pGamePoints) ( 30)
	(
		if(LastUpdatedVehicle(playerid) != vehicleid)
		(
			LastUpdatedVehicle(playerid) = vehicleid
		)
		else
		(
			return 1
		)
		
		if(IsPlayerInAnyVehicle(playerid))
			return 1
		
		Float:new_x, Float:new_y, Float:new_z
		GetVehiclePos(vehicleid, new_x, new_y, new_z)
		
		if(GetVehicleDistanceFromPoint(vehicleid, OldVehiclePosition(vehicleid)(0), OldVehiclePosition(vehicleid)(1), OldVehiclePosition(vehicleid)(2)) ( 5.0)
			return 1
		
		if(GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehicleid))
		(
			if(IsPlayerInRangeOfPoint(playerid, 4.0, new_x, new_y, new_z))
			(
				PlayerCache(playerid)(pCarsTP) += 1
				
				if(PlayerCache(playerid)(pCarsTP) ) MAX_CARS_NEED_TO_BAN)
				(
					// Banuj gnoja
					hrp_Ban(playerid, -1, Teleportowanie pojazdow, 0)
				)
			)
		)
	)
	
	return 1
)