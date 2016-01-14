/*
	---------------------------------------------------------------------------------
	Tutaj doklejamy skrypt roœlinek do hodowania itp.
	
	Przedmiot - nasionko:
		1. value1 = typ nasionka (co sadzi)
		
	Przedmiot - nawóz:
		1. value1 = typ nawozu
		
	Przedmiot - produkt (taki rolny):
		1. value1 = typ produktu
	
	Zasadzona roslinka: (hrp_seeds)
		1. seed_id
		2. seed_x, seed_y, seed_z
		3. seed_type
		4. seed_planttime
		5. seed_value = jakoœæ roœlinki
		5. seed_owner = uid grupy ktora zarzadza tym szajsem
		
	Jakoœæ:
		1. roœlina musi byæ dziennie podlana minimum dwa razy
		2. nawóz trzeba minimum raz
		
	531 - tractor
	610 - p³ug, czy co to
	532 - kombajn
	
	86400 - jedna doba, wed³ug unixtime
	value - 1690 = dojrzala roslina
	
	AI 1: Jeœli sadzi to sprawdŸ czy na duty grupy farmerów
	AI 2: Zbieranie powinno sie odbywac przy pomocy kombajna
	---------------------------------------------------------------------------------
*/
// Ogolne
//#define MAX_SEEDS 1000
#define INVALID_SEED_ID (-1)

// Mo¿liwe typy aktualnego wyposa¿enia
#define FARMING_SET_NONE 0
#define FARMING_SET_TRACTOR 2
#define FARMING_SET_COMBINE 4		// kombajn
#define FARMING_SET_TRAILER	8			// naczepka do traktora

// Typy seedsow
#define SEED_TYPE_NONE 0		// blad
#define SEED_TYPE_WHEAT 1			// Pszenica
#define SEED_TYPE_BEET 2		// Buraki
#define SEED_TYPE_CARROT 3	// Marchew

// -----------------------------------------------------------

/*enum sSellPars
(
	sType,
	sPrice
)
SeedSellInfo()(sSellPars) = 
(
	(SEED_TYPE_WHEAT, 30),
	(SEED_TYPE_BEET, 20),
	(SEED_TYPE_CARROT, 25)
)*/

stock CreateSeed(playerid, Float:posx, Float:posy, Float:posz, type)
(
	seed_id = seed_GetFreeID()
	if(seed_id == INVALID_SEED_ID)
	(
		GuiMsg(playerid, Wyst¹pi³ problem podczas tworzenia roœliny.\nPowiadom administratora o problemie z limitami., 1)
		return 0
	)
	
	SeedInfo(seed_id)(sPlantTime) = gettime()
	SeedInfo(seed_id)(sPosX) = posx
	SeedInfo(seed_id)(sPosY) = posy
	SeedInfo(seed_id)(sPosZ) = posz
	SeedInfo(seed_id)(sType) = type
	SeedInfo(seed_id)(sWeed) = 0
	SeedInfo(seed_id)(sValue) = 0
	SeedInfo(seed_id)(isSplashed) = false
	SeedInfo(seed_id)(sWater) = 0.0
	
	switch(type)
	(
		case SEED_TYPE_NONE:
			SeedInfo(seed_id)(sObject) = CreateDynamicObject(862, posx, posy, posz - 0.90, 0.0, 0.0, 0.0)
		case SEED_TYPE_WHEAT:
			SeedInfo(seed_id)(sObject) = CreateDynamicObject(862, posx, posy, posz - 0.90, 0.0, 0.0, 0.0)
		case SEED_TYPE_BEET:
			SeedInfo(seed_id)(sObject) = CreateDynamicObject(2011, posx, posy, posz - 2.3, 0.0, 0.0, 0.0)
		case SEED_TYPE_CARROT:
			SeedInfo(seed_id)(sObject) = CreateDynamicObject(3409, posx, posy, posz - 2.0, 0.0, 0.0, 0.0)
	)
	//format(string, sizeof(string), (ffffff)Roœlina (0066FF)(ID: %d)\n(ffffff)Wartoœæ: (0066FF)%d, seed_id, SeedInfo(seed_id)(sValue))
	//SeedInfo(seed_id)(sLabel) = CreateDynamic3DTextLabel(string, COLOR_WHITE, posx, posy, posz, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 80.0)
	
	owner_id = GroupData(GetPlayerDutyGroupID(playerid))(gUID)
	mysql_query_format(INSERT INTO hrp_seeds VALUES(NULL, %f, %f, %f, %d, %d, %d, %d), posx, posy, posz, type, gettime(), 0, owner_id)
	seed_uid = mysql_insert_id()
	
	SeedInfo(seed_id)(sOwner) = owner_id
	SeedInfo(seed_id)(sUID) = seed_uid
	
	Create3DTextForSeed(seed_id)
	return 1
)

stock DestroySeed(seed_id)
(
	if(SeedInfo(seed_id)(sUID) (= 0)
	(
		return 0
	)
	
	DestroyDynamicObject(SeedInfo(seed_id)(sObject))
	DestroyDynamic3DTextLabel(SeedInfo(seed_id)(sLabel))
	
	SeedInfo(seed_id)(sPlantTime) = 0
	SeedInfo(seed_id)(sPosX) = 0
	SeedInfo(seed_id)(sPosY) = 0
	SeedInfo(seed_id)(sPosZ) = 0
	SeedInfo(seed_id)(sType) = 0
	SeedInfo(seed_id)(sWeed) = 0
	SeedInfo(seed_id)(sValue) = 0
	SeedInfo(seed_id)(sOwner) = 0
	
	mysql_query_format(DELETE FROM hrp_seeds WHERE seed_id = %d, SeedInfo(seed_id)(sUID))
	SeedInfo(seed_id)(sUID) = 0
	return 1
)

stock LoadSeeds()
(
	// £adowanie wszystkich seedsów na starcie serwera
	buffer(256), gameid = 0
	format(buffer, sizeof(buffer), SELECT * FROM hrp_seeds)
	mysql_query(buffer)
	mysql_store_result()
	while(mysql_fetch_row(buffer, |))
	(
		sscanf(buffer, p(|)dfffdddd,
		SeedInfo(gameid)(sUID),
		SeedInfo(gameid)(sPosX),
		SeedInfo(gameid)(sPosY),
		SeedInfo(gameid)(sPosZ),
		SeedInfo(gameid)(sType),
		SeedInfo(gameid)(sPlantTime),
		SeedInfo(gameid)(sValue),
		SeedInfo(gameid)(sOwner))
		SeedInfo(gameid)(isSplashed) = false
		SeedInfo(gameid)(sWater) = 100.0
		
		switch(SeedInfo(gameid)(sType))
		(
			case SEED_TYPE_NONE:
				SeedInfo(gameid)(sObject) = CreateDynamicObject(862, SeedInfo(gameid)(sPosX), SeedInfo(gameid)(sPosY), SeedInfo(gameid)(sPosZ) - 0.90, 0.0, 0.0, 0.0)
			case SEED_TYPE_WHEAT:
				SeedInfo(gameid)(sObject) = CreateDynamicObject(862, SeedInfo(gameid)(sPosX), SeedInfo(gameid)(sPosY), SeedInfo(gameid)(sPosZ) - 0.90, 0.0, 0.0, 0.0)
			case SEED_TYPE_BEET:
				SeedInfo(gameid)(sObject) = CreateDynamicObject(2011, SeedInfo(gameid)(sPosX), SeedInfo(gameid)(sPosY), SeedInfo(gameid)(sPosZ) - 2.3, 0.0, 0.0, 0.0)
			case SEED_TYPE_CARROT:
				SeedInfo(gameid)(sObject) = CreateDynamicObject(3409, SeedInfo(gameid)(sPosX), SeedInfo(gameid)(sPosY), SeedInfo(gameid)(sPosZ) - 2.0, 0.0, 0.0, 0.0)
		)
		
		//SeedInfo(gameid)(sObject) = CreateDynamicObject(862, SeedInfo(gameid)(sPosX), SeedInfo(gameid)(sPosY), SeedInfo(gameid)(sPosZ) - 0.90, 0.0, 0.0, 0.0)
		//format(string, sizeof(string), (ffffff)Roœlina (0066FF)(ID: %d)\n(ffffff)Wartoœæ: (0066FF)%d, gameid, SeedInfo(gameid)(sValue))
		//SeedInfo(gameid)(sLabel) = CreateDynamic3DTextLabel(string, COLOR_WHITE, SeedInfo(gameid)(sPosX), SeedInfo(gameid)(sPosY), SeedInfo(gameid)(sPosZ), 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 80.0)
		
		gameid++
	)
	mysql_free_result()
	
	Create3DTextForSeeds()
	printf((load) zaladowano %d roslin farmerskich, gameid)
	return 1
)

stock SaveSeeds()
(
	saved = 0
	for(plant_id = 0  plant_id ( MAX_SEEDS plant_id++)
	(
		if(SeedInfo(plant_id)(sUID) ) 0)
		(
			mysql_query_format(UPDATE hrp_seeds SET seed_value = %d WHERE seed_id = %d, SeedInfo(plant_id)(sValue), SeedInfo(plant_id)(sUID))
			saved++
		)
	)
	
	printf((unload) zapisano %d roslin farmerskich, saved)
	return 1
)

stock seed_GetFreeID()
(
	free_id = INVALID_SEED_ID
	for(i = 0  i ( MAX_SEEDS i++)
	(
		if(SeedInfo(i)(sUID) ) 0)
			continue
			
		free_id = i
		break
	)
	
	return free_id
)

stock GetPlayerFarmingSet(playerid)
(
	// Ta piêkna funkcja zwróci to jaki set ma gracz aktualnie, w teorii
	farming_set = FARMING_SET_NONE
	
	if(IsPlayerInAnyVehicle(playerid))
	(
		vehicle_id = GetPlayerVehicleID(playerid)
		if(GetVehicleModel(vehicle_id) == 531)
		(
			farming_set += FARMING_SET_TRACTOR
			if(GetVehicleTrailer(vehicle_id) ) 0)
			(
				trailer_id = GetVehicleTrailer(vehicle_id)
				if(GetVehicleModel(trailer_id) == 610)
				(
					farming_set += FARMING_SET_TRAILER
				)
			)
		)
		if(GetVehicleModel(vehicle_id) == 532)
		(
			farming_set += FARMING_SET_COMBINE
		)
	)
	
	return farming_set
)

stock seed_GetNearestSeed(playerid, Float:ddistance = 5.0)
(
	seed_id = INVALID_SEED_ID, Float:distance = 0.0
	
	for(i = 0 i ( MAX_SEEDS i++)
	(
		if(!IsPlayerInRangeOfPoint(playerid, ddistance, SeedInfo(i)(sPosX), SeedInfo(i)(sPosY), SeedInfo(i)(sPosZ)))
			continue
			
		if(GetPlayerDistanceFromPoint(playerid, SeedInfo(i)(sPosX), SeedInfo(i)(sPosY), SeedInfo(i)(sPosZ)) ( distance || distance == 0.0)
		(
			seed_id = i
			distance = GetPlayerDistanceFromPoint(playerid, SeedInfo(i)(sPosX), SeedInfo(i)(sPosY), SeedInfo(i)(sPosZ))
		)
	)
	
	return seed_id
)

stock Create3DTextForSeed(seed_id)
(
	string(128)
	format(string, sizeof(string), (ffffff)Roœlina (0066FF)(ID: %d)\n(ffffff)Wartoœæ: (0066FF)%d, seed_id, SeedInfo(seed_id)(sValue))
	Text3D:label_id = CreateDynamic3DTextLabel(string, COLOR_WHITE, SeedInfo(seed_id)(sPosX), SeedInfo(seed_id)(sPosY), SeedInfo(seed_id)(sPosZ), 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 10.0)
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID, SeedInfo(seed_id)(sUID))
	SeedInfo(seed_id)(sLabel) = label_id

	return 1
)

stock Create3DTextForSeeds()
(
	string(128)
	for(i = 0 i ( MAX_SEEDS i++)
	(
		if(SeedInfo(i)(sUID) ) 0)
		(
			format(string, sizeof(string), (ffffff)Roœlina (0066FF)(ID: %d)\n(ffffff)Wartoœæ: (0066FF)%d, i, SeedInfo(i)(sValue))
			Text3D:label_id = CreateDynamic3DTextLabel(string, COLOR_WHITE, SeedInfo(i)(sPosX), SeedInfo(i)(sPosY), SeedInfo(i)(sPosZ), 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 10.0)
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID, SeedInfo(i)(sUID))
			SeedInfo(i)(sLabel) = label_id
		)
	)
	return 1
)

stock Update3DTextForSeed(seed_id)
(
	string(256)
	switch(SeedInfo(seed_id)(sType))
	(
		case SEED_TYPE_NONE:
		(
			format(string, sizeof(string), (ffffff)Roœlina (0066FF)(ID: %d)\n(ffffff)Gatunek: (0066FF)brak\n(ffffff)Wartoœæ: (0066FF)%d, seed_id, SeedInfo(seed_id)(sValue))
		)
		case SEED_TYPE_WHEAT:
		(
			format(string, sizeof(string), (ffffff)Roœlina (0066FF)(ID: %d)\n(ffffff)Gatunek: (0066FF)pszenica\n(ffffff)Wartoœæ: (0066FF)%d, seed_id, SeedInfo(seed_id)(sValue))
		)
		case SEED_TYPE_BEET:
		(
			format(string, sizeof(string), (ffffff)Roœlina (0066FF)(ID: %d)\n(ffffff)Gatunek: (0066FF)burak\n(ffffff)Wartoœæ: (0066FF)%d, seed_id, SeedInfo(seed_id)(sValue))
		)
		case SEED_TYPE_CARROT:
		(
			format(string, sizeof(string), (ffffff)Roœlina (0066FF)(ID: %d)\n(ffffff)Gatunek: (0066FF)marchew\n(ffffff)Wartoœæ: (0066FF)%d, seed_id, SeedInfo(seed_id)(sValue))
		)
	)
	
	if(gettime() - SeedInfo(seed_id)(sPlantTime) ) 86400)
	(
		format(string, sizeof(string), (66FF00)(Roœlina wydaje sie byæ dojrza³a)\n%s, string)
	)
	
	if(!SeedInfo(seed_id)(isSplashed))
	(
		format(string, sizeof(string), (990000)(Roœlina nie jest spryskana)\n%s, string)
	)
	
	if(SeedInfo(seed_id)(sWater) ( 30.0)
	(
		format(string, sizeof(string), (990000)(Roœlina nie jest podlana)\n%s, string)
	)
	
	for (label_id = 0 label_id (= CountDynamic3DTextLabels() label_id++)
	(
 		if(IsValidDynamic3DTextLabel(Text3D:label_id))
		(
	 		if(Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID) == SeedInfo(seed_id)(sUID))
			(
				if(Text3D:label_id == SeedInfo(seed_id)(sLabel)) (
					UpdateDynamic3DTextLabelText(Text3D:label_id, COLOR_WHITE, string)
					break
				)
			)
		)
	)
	return 1
)

/*stock Destroy3DTextForSeed(seed_id)
(
	for (label_id = 0 label_id (= CountDynamic3DTextLabels() label_id++)
	(
 		if(IsValidDynamic3DTextLabel(Text3D:label_id))
		(
	 		if(Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID) == SeedInfo(seed_id)(sLabel))
			(
				if(label_id == SeedInfo(seed_id)(sLabel))
				(
					Destroy3DTextLabel(label_id)
				)
			)
		)
	)
	
	return 1
)*/

// Komendy admina
// ----------------------------------------------------------------

CMD:aplant(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Nie mo¿esz u¿yæ tej komendy., 1)
		return 1
	)
	
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /aplant (usun | wymaksuj | info))
	 	return 1
	)
	
	if(!strcmp(type, info, true))
	(
		plant_id
		if(sscanf(varchar, d, plant_id))
		(
			hrp_Tip(playerid, /aplant info (ID roœliny))
			return 1
		)
		
		if(SeedInfo(plant_id)(sUID) (= 0)
		(
			GuiMsg(playerid, Nie ma takiej roœliny., 1)
			return 1
		)
		
		string(256), title(64)
		format(string, sizeof(string), ID roœliny: \t%d\nTyp roœliny: \t%d\nWartoœæ: \t%d\nW³aœciciel: \t%d, plant_id, SeedInfo(plant_id)(sType), SeedInfo(plant_id)(sValue), SeedInfo(plant_id)(sOwner))
		format(title, sizeof(title), UID: %d || Time: %d, SeedInfo(plant_id)(sUID), SeedInfo(plant_id)(sPlantTime))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, title, string, OK, )
	)
	
	if(!strcmp(type, usun, true))
	(
		plant_id
		if(sscanf(varchar, d, plant_id))
		(
			hrp_Tip(playerid, /aplant usun (ID roœliny))
			return 1
		)
		
		if(SeedInfo(plant_id)(sUID) (= 0)
		(
			GuiMsg(playerid, Nie ma takiej roœliny., 1)
			return 1
		)
		
		DestroySeed(plant_id)
		GuiMsg(playerid, Usun¹³eœ wskazan¹ roœlinê., 1)
	)
	
	if(!strcmp(type, wymaksuj, true))
	(
		plant_id
		if(sscanf(varchar, d, plant_id))
		(
			hrp_Tip(playerid, /aplant wymaksuj (ID roœliny))
			return 1
		)
		
		if(SeedInfo(plant_id)(sUID) (= 0)
		(
			GuiMsg(playerid, Nie ma takiej roœliny., 1)
			return 1
		)
		
		SeedInfo(plant_id)(sPlantTime) = gettime() - 86400
		SeedInfo(plant_id)(sValue) = 1440 + 250
		Update3DTextForSeed(plant_id)
		
		GuiMsg(playerid, Wskazana roœlina jest teraz gotowa do zebrania., 0)
	)
	
	return 1
)

// Komenda gracza
// -----------------------------------------------------

CMD:farma(playerid, params())
(
	if(PlayerCache(playerid)(pGroupDuty))
	(
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_FARM)
		(
			GuiMsg(playerid, Musisz byæ na s³u¿bie grupy o typie farmerskim by móc zebraæ nasiona., 1)
			return 1
		)
		
		type(32), varchar(32)
		if(sscanf(params, s(32)S()(32), type, varchar))
		(
			hrp_Tip(playerid, /farma (zbierz | podlej | nawiez | sprzedaj))
			return 1
		)
		
		if(!strcmp(type, sprzedaj, true))
		(
			if(!IsPlayerInRangeOfPoint(playerid, 10.0, -62.8525, 116.9715, 3.1172) || GetPlayerVirtualWorld(playerid) != 0)
			(
				GuiMsg(playerid, Udaj siê na punkt skupu by sprzedaæ trochê produktów., 0)
				SetPlayerCheckpoint(playerid, -62.8525, 116.9715, 3.1172, 5.0)
				Checkpoint(playerid) = 0
			)
			else
			(
				// ShowPlayerDialog
				DisablePlayerCheckpoint(playerid)
			)
		)
		
		if(!strcmp(type, nawiez, true))
		(
			seed_id = seed_GetNearestSeed(playerid, 5.0)
			if(seed_id == INVALID_SEED_ID || SeedInfo(seed_id)(sOwner) != GroupData(group_id_fix)(gUID))
			(
				GuiMsg(playerid, W pobli¿u nie ma ¿adnej roœliny nale¿¹cej do Twojej farmy., 1)
				return 1
			)
			
			string(128)
			format(string, sizeof(string), ** %s nawozi roœlinê., PlayerName(playerid))
			ApplyAnimation(playerid, ROB_BANK, CAT_Safe_Rob, 4.0, 0, 0, 0, 0, 0, 1)
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			
			SeedInfo(seed_id)(isSplashed) = true
			Update3DTextForSeed(seed_id)
		)
		
		if(!strcmp(type, podlej, true))
		(
			seed_id = seed_GetNearestSeed(playerid, 5.0)
			if(seed_id == INVALID_SEED_ID || SeedInfo(seed_id)(sOwner) != GroupData(group_id_fix)(gUID))
			(
				GuiMsg(playerid, W pobli¿u nie ma ¿adnej roœliny nale¿¹cej do Twojej farmy., 1)
				return 1
			)
			
			string(128)
			format(string, sizeof(string), ** %s podlewa roœlinê., PlayerName(playerid))
			ApplyAnimation(playerid, ROB_BANK, CAT_Safe_Rob, 4.0, 0, 0, 0, 0, 0, 1)
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			
			SeedInfo(seed_id)(sWater) += 10.0
			Update3DTextForSeed(seed_id)
		)
		
		if(!strcmp(type, zbierz, true))
		(
			seed_id = seed_GetNearestSeed(playerid, 5.0)
			if(seed_id == INVALID_SEED_ID || SeedInfo(seed_id)(sOwner) != GroupData(group_id_fix)(gUID))
			(
				GuiMsg(playerid, W pobli¿u nie ma ¿adnej roœliny nale¿¹cej do Twojej farmy., 1)
				return 1
			)
			
			if(gettime() - SeedInfo(seed_id)(sPlantTime) ( 80000 || SeedInfo(seed_id)(sValue) ( 1500)
			(
				// Daj GUI do usuniecia roœliny bez ¿adnych korzyœci
				DestroySeed(seed_id)
				GuiMsg(playerid, Zebra³eœ roœlinê, która nie nadawa³a siê do u¿ytku.\nNiestety nie dosta³eœ nic., 0)
				return 1
			)
			
			if(SeedInfo(seed_id)(sValue) )= 1690)
			(
				// CreatePlayerItem
				// 
				//
				
				
				
				
				GuiMsg(playerid, Zebra³eœ roœlinkê, która okaza³a siê dojrza³a.\nDo ekwipunku dodano odpowiedni produkt., 0)
				DestroySeed(seed_id)
				return 1
			)
			
			
			
			
		)
		
	)
	else
	(
		GuiMsg(playerid, Musisz byæ na s³u¿bie grupy o typie farmerskim by móc zasadziæ nasiona., 1)
		return 1
	)
	
	
	return 1
)
