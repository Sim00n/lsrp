stock CreatePlant(type, name(), Float:PosX, Float:PosY, Float:PosZ, interior, world)
(
	mysql_query_format(INSERT INTO hrp_plants (plant_name, plant_type, plant_posx, plant_posy, plant_posz, plant_int, plant_vw) VALUES (%s, %d, %f, %f, %f, %d, %d), name, type, PosX, PosY, PosZ, interior, world)
	plant_uid = mysql_insert_id()

	LoadPlant(plant_uid)
	return 1
)

stock LoadPlants()
(
	data(256), plantid
	mysql_query(SELECT * FROM hrp_plants)
	
	print((load) Rozpoczynam proces wczytywania wszystkich krzakow z bazy...)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		plantid++
	
		sscanf(data, p(|)ds(64)ddddddfffdd,
		
		Plants(plantid)(plantUID),
		Plants(plantid)(plantName),
		Plants(plantid)(plantType),
		Plants(plantid)(plantTicks),
		Plants(plantid)(plantGrowth),
		Plants(plantid)(plantSun),
		Plants(plantid)(plantWater),
		Plants(plantid)(plantQuality),
		Plants(plantid)(plantPosX),
		Plants(plantid)(plantPosY),
		Plants(plantid)(plantPosZ),
		Plants(plantid)(plantInt),
		Plants(plantid)(plantVW))
		
		Itter_Add(Plants, plantid)
	)
	mysql_free_result()
	printf((load) Wczytano %d krzakow., plantid)

	printf((load) Rozpoczynam proces towrzenia 3DTextow dla krzakow)
	label_count = Create3DTextsAOForPlants()
	printf((load) Wczytano %d 3DTextow dla krzakow., label_count)	
	return 1
)

stock LoadPlant(plant_uid)
(
	printf((load) Wczytuje krzak %d., plant_uid)

	data(256), plantid = Itter_Free(Plants)
	mysql_query_format(SELECT * FROM hrp_plants WHERE plant_uid = %d, plant_uid)
		
	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(	
		sscanf(data, p(|)ds(64)ddddddfffdd,
		
		Plants(plantid)(plantUID),
		Plants(plantid)(plantName),
		Plants(plantid)(plantType),
		Plants(plantid)(plantTicks),
		Plants(plantid)(plantGrowth),
		Plants(plantid)(plantSun),
		Plants(plantid)(plantWater),
		Plants(plantid)(plantQuality),
		Plants(plantid)(plantPosX),
		Plants(plantid)(plantPosY),
		Plants(plantid)(plantPosZ),
		Plants(plantid)(plantInt),
		Plants(plantid)(plantVW))

		Plants(plantid)(plantLabel) = Text3D:EOS
		
		Itter_Add(Plants, plantid)
	)
	mysql_free_result()

	printf((load) Wczytano krzak %d., plant_uid)
	printf((load) Rozpoczynam proces towrzenia 3DTextow dla krzaka)	
	Create3DTextAOForPlant(plantid)
	return 1
)

stock ReloadPlants()
(
	for(i = 0  i ( MAX_PLANTS i++)
	(
		Plants(i)(plantUID) = EOS
		Plants(i)(plantName) = EOS
		Plants(i)(plantType) = EOS
		Plants(i)(plantTicks) = EOS
		Plants(i)(plantGrowth) = EOS
		Plants(i)(plantSun) = EOS
		Plants(i)(plantWater) = EOS
		Plants(i)(plantQuality) = EOS
		Plants(i)(plantPosX) = EOS
		Plants(i)(plantPosY) = EOS
		Plants(i)(plantPosZ) = EOS
		Plants(i)(plantInt) = EOS
		Plants(i)(plantVW) = EOS
		Plants(i)(plantLabel) = EOS
	)
	
	LoadPlants()
	
	print((reload) Przeladowano krzaki.)
	
	return 1
)


stock SavePlant(gameid, what)
(
	main_query(512), query(256)
	format(main_query, sizeof(main_query), UPDATE hrp_plants SET)
	if(what & SAVE_PLANT_POS)
	(
		// Pozycja krzaka
		format(query, sizeof(query),  plant_posx = %f, plant_posy = %f, plant_posz = %f, plant_int = %d, plant_vw = %d,
		Plants(gameid)(plantPosX),
		Plants(gameid)(plantPosY),
		Plants(gameid)(plantPosZ),
		Plants(gameid)(plantInt),
		Plants(gameid)(plantVW))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_PLANT_THINGS)
	(
		// Reszta smieci
		format(query, sizeof(query),  plant_ticks = %d, plant_growth = %d, plant_sun = %d, plant_water = %d, plant_quality = %d,
		Plants(gameid)(plantTicks),
		Plants(gameid)(plantGrowth),
		Plants(gameid)(plantSun),
		Plants(gameid)(plantWater),
		Plants(gameid)(plantQuality))
		
		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_PLANT_IDENTITY)
	(
		// Nazwa i typ
		format(query, sizeof(query),  plant_name = %s, plant_type = %d,
		Plants(gameid)(plantName),
		Plants(gameid)(plantType))
		
		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	format(query, sizeof(query),  WHERE plant_uid = %d LIMIT 1, Plants(gameid)(plantUID))
	strcat(main_query, query, sizeof(main_query))
	
	mysql_query(main_query)
	return 1
)

stock DeletePlant(plantid)
(
	Delete3DTextForPlant(plantid)
	mysql_query_format(DELETE FROM hrp_plants WHERE plant_uid = %d, Plants(plantid)(plantUID))

	Plants(plantid)(plantUID) = EOS
	Plants(plantid)(plantName) = EOS
	Plants(plantid)(plantType) = EOS
	Plants(plantid)(plantTicks) = EOS
	Plants(plantid)(plantGrowth) = EOS
	Plants(plantid)(plantSun) = EOS
	Plants(plantid)(plantWater) = EOS
	Plants(plantid)(plantQuality) = EOS
	Plants(plantid)(plantPosX) = EOS
	Plants(plantid)(plantPosY) = EOS
	Plants(plantid)(plantPosZ) = EOS
	Plants(plantid)(plantInt) = EOS
	Plants(plantid)(plantVW) = EOS
	Plants(plantid)(plantLabel) = Text3D:EOS

	Itter_Remove(Plants, plantid)
	return 1
)

stock Create3DTextsAOForPlants()
(
	count = 0, string(128)
	foreach(Plants, plant)
	(
		format(string, sizeof(string), Krzak (%s)\nNawodnienie: (E85405)%d(FFFFFF)\nNaœwietlenie: (E85405)%d(FFFFFF)\nJakoœæ: (E85405)%d(FFFFFF), Plants(plant)(plantName), Plants(plant)(plantWater), Plants(plant)(plantSun), Plants(plant)(plantQuality))
		Text3D:label_id = CreateDynamic3DTextLabel(string, COLOR_DESC, Plants(plant)(plantPosX), Plants(plant)(plantPosY), Plants(plant)(plantPosZ), 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Plants(plant)(plantVW), Plants(plant)(plantInt), -1, 10.0)
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID, Plants(plant)(plantUID))
		Plants(plant)(plantLabel) = label_id
		
		object_id = CreateDynamicObject(19473, Plants(plant)(plantPosX), Plants(plant)(plantPosY), Plants(plant)(plantPosZ), 0, 0, 0, Plants(plant)(plantVW), -1, -1, 100.0)
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, (Plants(plant)(plantUID) * -1))

		count++
	)
	return count
)

stock Create3DTextAOForPlant(plant)
(
	string(128)
	format(string, sizeof(string), Krzak (%s)\nNawodnienie: (E85405)%d(FFFFFF)\nNaœwietlenie: (E85405)%d(FFFFFF)\nJakoœæ: (E85405)%d(FFFFFF), Plants(plant)(plantName), Plants(plant)(plantWater), Plants(plant)(plantSun), Plants(plant)(plantQuality))
	Text3D:label_id = CreateDynamic3DTextLabel(string, COLOR_DESC, Plants(plant)(plantPosX), Plants(plant)(plantPosY), Plants(plant)(plantPosZ), 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Plants(plant)(plantVW), Plants(plant)(plantInt), -1, 10.0)
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID, Plants(plant)(plantUID))
	Plants(plant)(plantLabel) = label_id
	
	object_id = CreateDynamicObject(19473, Plants(plant)(plantPosX), Plants(plant)(plantPosY), Plants(plant)(plantPosZ), 0, 0, 0, Plants(plant)(plantVW), -1, -1, 100.0)
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, (Plants(plant)(plantUID) * -1))

	return 1
)

stock Delete3DTextForPlant(plant)
(
	for (label_id = 0 label_id (= CountDynamic3DTextLabels() label_id++)
	(
 		if(IsValidDynamic3DTextLabel(Text3D:label_id))
		(
	 		if(Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID) == Plants(plant)(plantUID))
			(
				if(Text3D:label_id == Plants(plant)(plantLabel))
				(
					Destroy3DTextLabel(label_id)
				)
			)
		)
	)

	return 1
)

stock Update3DTextForPlant(plant)
(
	string(128)
	format(string, sizeof(string), Krzak (%s)\nNawodnienie: (E85405)%d(FFFFFF)\nNaœwietlenie: (E85405)%d(FFFFFF)\nJakoœæ: (E85405)%d(FFFFFF), Plants(plant)(plantName), Plants(plant)(plantWater), Plants(plant)(plantSun), Plants(plant)(plantQuality))

	for (label_id = 0 label_id (= CountDynamic3DTextLabels() label_id++)
	(
 		if(IsValidDynamic3DTextLabel(Text3D:label_id))
		(
	 		if(Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID) == Plants(plant)(plantUID))
			(
				if(Text3D:label_id == Plants(plant)(plantLabel)) (
					UpdateDynamic3DTextLabelText(Text3D:label_id, COLOR_DESC, string)
					break
				)
			)
		)
	)

	return 1
)

stock GetNearestPlant(playerid)
(
	index = -1
	for(i = 0 i ( MAX_PLANTS i++)
	(
		if(Plants(i)(plantUID))
		(
			if(Plants(i)(plantVW) == GetPlayerVirtualWorld(playerid) && Plants(i)(plantInt) == GetPlayerInterior(playerid))
			(
				if(IsPlayerInRangeOfPoint(playerid, 2.0, Plants(i)(plantPosX), Plants(i)(plantPosY), Plants(i)(plantPosZ)))
				(
					index = i
					break
				)
			)
		)
	)

	return index
)

stock WaterPlant(playerid, plantid)
(
	Plants(plantid)(plantWater)++
	Plants(plantid)(plantGrowth)++

	if(Plants(plantid)(plantTicks) ) 24*7)
	(
		Plants(plantid)(plantQuality)--

		if(Plants(plantid)(plantWater) ) 150)
		(
			SendClientMessage(playerid, COLOR_DO, Zala³eœ swój krzak zbyt du¿¹ iloœci¹ wody w efekciego czego zgni³.)
			DeletePlant(plantid)
			return 1
		)
	)
	else if(Plants(plantid)(plantTicks) ) 24*3)
	(
		if(Plants(plantid)(plantQuality) ) 80)
			Plants(plantid)(plantQuality) -= 5
		else
			Plants(plantid)(plantQuality)++

		if(Plants(plantid)(plantWater) ) 100)
		(
			SendClientMessage(playerid, COLOR_DO, Zala³eœ swój krzak zbyt du¿¹ iloœci¹ wody w efekciego czego zgni³.)
			DeletePlant(plantid)
			return 1
		)
	)
	else if(Plants(plantid)(plantTicks) ) 24*2)
	(
		if(Plants(plantid)(plantQuality) ) 50)
			Plants(plantid)(plantQuality) -= 20
		else
			Plants(plantid)(plantQuality)++

		if(Plants(plantid)(plantWater) ) 70)
		(
			SendClientMessage(playerid, COLOR_DO, Zala³eœ swój krzak zbyt du¿¹ iloœci¹ wody w efekciego czego zgni³.)
			DeletePlant(plantid)
			return 1
		)
	)
	else if(Plants(plantid)(plantTicks) ) 24*1)
	(
		if(Plants(plantid)(plantQuality) ) 20)
			Plants(plantid)(plantQuality) -= 20
		else
			Plants(plantid)(plantQuality)++

		if(Plants(plantid)(plantWater) ) 30)
		(
			SendClientMessage(playerid, COLOR_DO, Zala³eœ swój krzak zbyt du¿¹ iloœci¹ wody w efekciego czego zgni³.)
			DeletePlant(plantid)
			return 1
		)
	) else (
		if(Plants(plantid)(plantQuality) )= 0)
			Plants(plantid)(plantQuality) = 0

		if(Plants(plantid)(plantWater) ) 10)
		(
			SendClientMessage(playerid, COLOR_DO, Zala³eœ swój krzak zbyt du¿¹ iloœci¹ wody w efekciego czego zgni³.)
			DeletePlant(plantid)
			return 1
		)
	)

	Update3DTextForPlant(plantid)

	SendClientMessage(playerid, COLOR_DO, Krzak zosta³ podlany.)
	string(64)
	format(string, sizeof(string), ** %s podla³ krzak marihuany. **, PlayerName(playerid))
	
	ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, false)
	return 1
)

stock CollectPlant(playerid, plantid)
(
	// Aktualnie plantujemy tylko zio³o wiêc nie bawie siê w sprawdzanie typu do zbioru, etc.

	if(Plants(plantid)(plantUID))
	(
		string(128), grams = 0

		if(Plants(plantid)(plantTicks) ) 24 * 10)
		(
			SendClientMessage(playerid, COLOR_DO, Twoja roœlinka jest kompletnie bezu¿yteczna. Zbyt d³ugo trzyma³eœ j¹ w ziemi.)
			DeletePlant(plantid)
			return 1
		)
		else if(Plants(plantid)(plantTicks) ) 24 * 7)
		(
			grams = Plants(plantid)(plantGrowth) / 2
			grams += Plants(plantid)(plantQuality) / 10
		)
		else if(Plants(plantid)(plantTicks) ) 24 * 4)
		(
			grams = Plants(plantid)(plantGrowth) / 3
			grams += Plants(plantid)(plantQuality) / 20
		)
		else
		(
			SendClientMessage(playerid, COLOR_DO, Twoja roœlinka jest kompletnie bezu¿yteczna. Zbyt d³ugo trzyma³eœ j¹ w ziemi.)
			DeletePlant(plantid)
			return 1	
		)

		grams = floatround(grams/2)
		
		format(string, sizeof(string), Marihuana (%d g.), grams)
		CreatePlayerItem(playerid, string, ITEM_DRUG, DRUG_MARIHUANA, grams)

		format(string, sizeof(string), Po zebraniu i obrobieniu liœci uda³o Ci siê odzyskaæ %d gram marihuany, grams)
		SendClientMessage(playerid, COLOR_DO, string)

		DeletePlant(plantid)
	)

	return 1
)