bool:printTimers = false

/*forward OnMinuteTimer()
public OnMinuteTimer()*/
task OnMinuteTimer(60000)()
(
	// coœ zjebane jest
	if(DEBUG_MODE || printTimers)
	(
		SendClientMessageToAll(0x00AA00FF, (DEBUG) Timer 1 min tick passed.)
	)
	
	hour, minute, second
	gettime(hour, minute, second)
	year, month, day
	getdate(year, month, day)
	lspad_string(128)
	
	// Godzina
	static LastHour = 25
	
	format(lspad_string, sizeof(lspad_string), %02d:%02d~n~%02d-%02d-%04d, hour, minute, month, day, year)
	TextDrawSetString(LSPad_Frame(18), lspad_string)

	farenheit = floatround(WeatherTemperature * 1.8 + 32)
	Weather(1) = (WeatherTemperature ) 25)?	random(50) : random(50) + 50
	Weather(2) = random(20)
	format(lspad_string, sizeof(lspad_string), Temperatura: ~r~%dF / %dC~w~~n~Wilgotnosc: ~b~%d%~w~~n~Wiatr: ~y~%dmph~n~~w~Dzien: ~g~%s, farenheit, WeatherTemperature, Weather(1), Weather(2), WeatherTypes(Weather(3)))
	TextDrawSetString(LSPad_Weather, lspad_string)
	
	//pogoda
	WeatherTicks++
	if(CurrentWeather == 8)
	(
		if(WeatherTicks ) 20)
		(
			CurrentWeather = RandWeather()
			WeatherTicks = 0
		)
	)
	else
	(
		if(WeatherTicks ) 60)
		(
			CurrentWeather = RandWeather()
			WeatherTicks = 0

			GenerateTemperature()
		)
	)
	
	for(i = 0  i ( MAX_PLAYERS  i++)
	(
		PlayerCache(i)(pCarryTries) = 0
		
		if(!PlayerCache(i)(pRage))
		(
			if(GetPlayerVirtualWorld(i) ) 0)
			(
				SetPlayerWeather(i,0)
			)
			else
			(
				SetPlayerWeather(i,CurrentWeather)
			)
		)
	)
	
	for(i = 0  i ( MAX_SEEDS i++)
	(
		if(SeedInfo(i)(sUID) ) 0)
		(
			if(SeedInfo(i)(sWater) ) 150.0)
				DestroySeed(i)
			
			if(!SeedInfo(i)(isSplashed))
			(
				loss = random(100)
				if(loss == 50 || loss == 70 || loss == 10)
				(
					SeedInfo(i)(sValue) -= 60
					if(SeedInfo(i)(sValue) ( 0)
						SeedInfo(i)(sValue) = 0
				)
			)
			
			if(SeedInfo(i)(sWater) ) 30.0)
				SeedInfo(i)(sValue) += 1
			
			SeedInfo(i)(sWater) -= 0.2
			Update3DTextForSeed(i)
		)
	)
	
	NewHour
	gettime(NewHour)

	if(NewHour ) LastHour)
	(		
		string(128)
		if(NewHour == 24)
		(
			format(string, sizeof(string), ~b~~h~LS-RP ~w~: ~g~~h~%02d.%02d.%02d, day, month, year)
			TextDrawSetString(Text:TextDrawServerLogo, string)
		)


		// Krzaki
		foreach(Plants, plantid)
		(
			if(Plants(plantid)(plantUID))
			(
				if(Plants(plantid)(plantWater) ) 10)
				(
					if(Plants(plantid)(plantSun) ) 12) (
						if(random(4) == 1)
							Plants(plantid)(plantGrowth) ++
					) else (
						if(random(6) == 1)
							Plants(plantid)(plantGrowth) ++
					)
				)

				// £atka na obecn± chwile - system o¶wietlenia do zmiany.
				if(Plants(plantid)(plantVW) == 0)
					Plants(plantid)(plantSun) += 4
				else
					Plants(plantid)(plantSun)++

				Plants(plantid)(plantTicks)++

				if(Plants(plantid)(plantWater) )= 0)
					Plants(plantid)(plantWater)--


				Update3DTextForPlant(plantid)

				SavePlant(plantid, SAVE_PLANT_THINGS)
			)
		)

		if(NewHour % 19 == 0 && minute == 30) //Nie trzeba sprawdzaæ sekundy bo to timer minutowy
		(
			if(random(50) == 34)
			(
				foreach(Player, i)
				(
					scale = 4500 + random(15) * 100
					SetPlayerDrunkLevel(i, scale)
				)
				QuakeTimer = 20
				SendClientMessageToAll(COLOR_DO, ** W calym miescie czuc trzesienie ziemi. Ludzie wychodza z domow, slychac alarmy w samochodach. **)
			)
		)


		if(NewHour == 4)
		(
			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Serwer zostanie zrestartowany o godzinie 4:00. Przez ten czas prosimy Ciê o opuszczenie serwera., OK, )
				)
				Kick(i)
			)
			
			foreach(Player, i)
			(
				SendClientMessage(i, COLOR_RED, Serwer przechodzi przez nocny restart. Zapraszamy wkrótce.)
				Kick(i)
			)
			
			SendRconCommand(gmx)
		)
		SetWorldTime(NewHour + 1)
	)
	LastHour = NewHour
	
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i) && !PlayerCache(i)(pSwitching))
		(
			if(PlayerCache(i)(pMinutes) % AC_PASS_NUMBER == 0)
			(
				PlayerCache(i)(pCarsTP) = 0
			)
			
			if(!IsPlayerAFK(i))
			(
				PlayerCache(i)(pMinutes) ++
				if(PlayerCache(i)(pMinutes) ) 59)
				(
					PlayerCache(i)(pMinutes) = 0
					PlayerCache(i)(pHours) ++
					
					if(PlayerCache(i)(pPremium))	PlayerCache(i)(pGamePoints) += 15
					else							PlayerCache(i)(pGamePoints) += 10
					
					SetPlayerScore(i, PlayerCache(i)(pGamePoints))
					mysql_query_format(UPDATE live_users SET user_gamepoints = %d WHERE user_id = %d LIMIT 1, PlayerCache(i)(pGamePoints), PlayerCache(i)(pGID))
				)
			)
			
			if(PlayerCache(i)(pKillCount) ) 0)
			(
				PlayerCache(i)(pKillCount) = 0
			)
			
			if(PlayerCache(i)(pBusinessShow))
			(
				cmd_biznesy(i, skrypt)
			)
			
			if(PlayerCache(i)(pAJ))
			(
				// Dodatkowa kara w AJ
				PlayAudioStreamForPlayer(i, http://pliki.ls-rp.net/sounds/aj.mp3)
			)
			
			if(PlayerCache(i)(pFocusedID) != INVALID_PLAYER_ID)
			(
				TextDrawSetString(Text:TextDrawMainInfo(i), Skupiasz sie na graczu, pamietaj by wylaczyc to gdy skonczysz~n~~g~/focus)
				TextDrawShowForPlayer(i, Text:TextDrawMainInfo(i))

				PlayerCache(i)(pShowInfoText) = 5
			)
			
			if(PlayerCache(i)(pBleeding) ) 0)
			(
				Float:current = PlayerCache(i)(pHealth)
				current = current - 10
				PlayerCache(i)(pHealth) = current
				SetPlayerHealth(i, current)
			)
			
			
			PlayerCache(i)(pCurrentZone) = GetPlayerZoneID(i)
			if(PlayerCache(i)(pCurrentZone) != INVALID_ZONE_ID)
			(
				AddZoneTick(i)
			)
			
			/*if(PlayerCache(i)(pCurrentZone) ) -1)
			(
				AddZoneTick(i)		// bêdzie dobrze?
				zone = PlayerCache(i)(pCurrentZone)
				if(!IsPlayerInArea(i, ZoneInfo(zone)(zMaxX), ZoneInfo(zone)(zMinX), ZoneInfo(zone)(zMaxY), ZoneInfo(zone)(zMinY)))
				(
					OnPlayerExitZone(i, zone)
				)	
			)
			
			if(PlayerCache(i)(pCurrentZone) == INVALID_ZONE_ID)
			(
				zone = GetPlayerZoneID(i)
				if(zone != PlayerCache(i)(pCurrentZone))
				(
					OnPlayerEnterZone(i, zone)
				)
			)*/
			
			/*
				koniec testowych stref
			*/
			
			
			// Animacja BW
			if(PlayerCache(i)(pBW))
			(
				ApplyAnimation(i, CRACK, crckdeth3, 4.1, 0, 0, 0, 1, 0, 1)
			)
			if(PlayerCache(i)(pCuffedStill) != INVALID_PLAYER_ID)
			(
				ApplyAnimation(i, CRACK, crckdeth3, 4.1, 0, 0, 0, 1, 0, 1)
			)
			
			if(PlayerCache(i)(pAirBrkWarns) != 0)
			(
				PlayerCache(i)(pAirBrkWarns) --
			)
			
			// Jest najedzony
			if(PlayerCache(i)(pFed))
			(
				PlayerCache(i)(pFed) -= 2
				if(PlayerCache(i)(pHealth) ( 100.0)
				(
					Float:factor = 1
					if(PlayerCache(i)(pGymNutrient))
					(
						factor += (PlayerCache(i)(pGymFactor) / 50)
					)
					if(factor ( 1) factor = 1
					if(factor ) 2) factor = 2
					
					// Je¿eli naæpany, HP szybciej roœnie
					if(PlayerCache(i)(pSmokeLevel) )= 780)
					(
						if(PlayerCache(i)(pWounded))
						(
							hrp_SetPlayerHealth(i, PlayerCache(i)(pHealth) + 2.0)
						)
						else
						(
							hrp_SetPlayerHealth(i, PlayerCache(i)(pHealth) + (10.0 * factor))
						)
					)
					else
					(
						if(PlayerCache(i)(pWounded))
						(
							// Brak pasywnego regenu hp dla ludzi z obra¿eniami bez dragów.
							//hrp_SetPlayerHealth(i, PlayerCache(i)(pHealth) + 1.0)
						)
						else
						(
							hrp_SetPlayerHealth(i, PlayerCache(i)(pHealth) + (3.0 * factor))
						)
					)
				)

				if(PlayerCache(i)(pFed) (= 0)
				(
					PlayerCache(i)(pFed) = 0

					TextDrawSetString(Text:TextDrawMainInfo(i), Twoja postac odczuwa ~b~glod~w~, pasek stanu zdrowia ~r~nie bedzie ~w~sie wiecej regenerowal.)
					TextDrawShowForPlayer(i, Text:TextDrawMainInfo(i))

					PlayerCache(i)(pShowInfoText) = 5
				)
			)
			
			if(hour % 5 == 0)
			(
				if(IsPlayerInAnyVehicle(i))
				(
					vehid = GetPlayerVehicleID(i), Float:vSX, Float:vSY, Float:vSZ
					vmodel = GetVehicleModel(vehid)

					if(IsGroundVehicle(vmodel))
					(
						GetVehicleVelocity(vehid, vSX, vSY, vSZ)
						if(vSX ) 0 || vSY ) 0 || vSZ ) 0)
						(
							if(random(500) == 32)
							(
								if(GetVehicleComponentInSlot(vehid, 7) != 1025) //Sprawdzanie czy ma felgi offroad - je¿eli tak to nie przebija.
								(
									CarInfo(vehid)(cVisual)(3) = 2 ^ random(4) // 1, 2, 4, 8, 
									UpdateVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))
									
									foreach(Player, j)
									(
										if(IsPlayerInAnyVehicle(j))
										(
											if(GetPlayerVehicleID(j) == vehid)
											(
												TextDrawSetString(Text:TextDrawMainInfo(j), Opona w Twoim pojezdzie ~r~zostala przebita ~w~przez lezacy na drodze gwozdz~w~. Udaj sie do ~g~mechanika ~w~w celu wymiany.)
												TextDrawShowForPlayer(j, Text:TextDrawMainInfo(j))

												PlayerCache(j)(pShowInfoText) = 8
											)
										)
									)
								)
							)
						)
					)
				)
			)
			
			if(PlayerCache(i)(pArrest))
			(
				if(!PlayerCache(i)(pAJ))
				(
					if(GetPlayerVirtualWorld(i) != PrisonWorld && !IsPlayerInRangeOfPoint(i, 20.0, 1762.3607, -1537.6106, 9.3697))
					(
						ShowAdminLog(~r~(prison) ~w~Gracz %s (ID: %d, Godzin: %d) prawdopodobnie uciekl bugiem ze spacerniaka., PlayerName(i), i, PlayerCache(i)(pHours))
					)
				)
			)
			
			OnPlayerSave(i) ++
			if(OnPlayerSave(i) )= 10)
			(
				SavePlayerStats(i, SAVE_PLAYER_BASIC | SAVE_PLAYER_SKILLS)
				OnPlayerSave(i) = 0
			)
		)
	)
	// Czas reklamy nadawanej
/*	if(AdvertiseTime != 0)
	(
		AdvertiseTime --
		
		if(AdvertiseTime (= 0)
		(
			TextDrawSetString(Text:TextDrawSanNews, B96 FM ~)~ W radiu leci standardowy blok muzyczny.)

			UsingRadio = false
			AdvertiseTime = 0
		)
	)
*/	
	// Czas reklamy, nowy system selera
	for(i = 1 i ( sizeof(RadioData) i++)
	(
		if(RadioData(i)(AdvertTime) != 0)
		(		
			if(RadioData(i)(AdvertTime) == 1)
			(
				string(256), group_id_fix = GetGroupID(RadioData(i)(gUID))
				format(string, sizeof(string), %s ~)~ W radiu leci standardowy blok muzyczny., GroupData(group_id_fix)(gTag))
				TextDrawSetString(Text:TextDrawRadio(i), string)

				RadioData(i)(IsUsingRadio) = false
				RadioData(i)(AdvertTime) = 0
			)
			RadioData(i)(AdvertTime)--
		)
	)
	
	// Paczki czasowe
	foreach(Packages, package_id)
	(
		if(PackageInfo(package_id)(pUID))
		(
			if(PackageInfo(package_id)(pSecured))
			(
				PackageInfo(package_id)(pTransportTime) --

				if(PackageInfo(package_id)(pTransportTime) (= 0)
				(
					package_next
					
					// Dodaj paczkê do magazynu drzwi, jeœli istniej¹
					if(GetDoorID(PackageInfo(package_id)(pDoorUID)))
					(
			 			AddDoorProduct(PackageInfo(package_id)(pItemName), PackageInfo(package_id)(pItemType), PackageInfo(package_id)(pItemValue1), PackageInfo(package_id)(pItemValue2), PackageInfo(package_id)(pItemPrice), PackageInfo(package_id)(pItemNumber), PackageInfo(package_id)(pDoorUID))
					)
					mysql_query_format(DELETE FROM hrp_packages WHERE package_uid = %d LIMIT 1, PackageInfo(package_id)(pUID))

					PackageInfo(package_id)(pUID) = 0
					PackageInfo(package_id)(pDoorUID) = 0

					PackageInfo(package_id)(pItemType) = 0

					PackageInfo(package_id)(pItemValue1) = 0
					PackageInfo(package_id)(pItemValue2) = 0

					PackageInfo(package_id)(pItemNumber) = 0
					PackageInfo(package_id)(pItemPrice) = 0

					Itter_SafeRemove(Packages, package_id, package_next)
					package_id = package_next
				)
			)
		)
	)
	
	// Pêtla na drzwi
	foreach(Doors, doorid)
	(
		if(DoorData(doorid)(dUID))
		(
			// Jeœli jakiœ budynek p³onie
			if(DoorData(doorid)(dBurnTime))
			(
				string(128), Float:percent, group_id_fix
				DoorData(doorid)(dBurnTime) ++
				
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pGroupDuty))
						(
							group_id_fix = GetPlayerDutyGroupID(i)
							if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
							(
								if(GetPlayerDoorID(i) == doorid)
								(
									DoorData(doorid)(dBurnTime) --
								)
							)
						)
					)
				)
				percent = (float(DoorData(doorid)(dBurnTime)) / 15.0) * 100
				format(string, sizeof(string), Ten budynek stan¹³ w p³omieniach!\nProcent zniszczeñ: %d%, floatround(percent))

				if(DoorData(doorid)(dBurnTime) ( 5)
				(
					UpdateDynamic3DTextLabelText(Text3D:DoorData(doorid)(dFireLabels), 0x33AA33FF, string)
				)
				else if(DoorData(doorid)(dBurnTime) )= 5 && DoorData(doorid)(dBurnTime) ( 10)
				(
					UpdateDynamic3DTextLabelText(Text3D:DoorData(doorid)(dFireLabels), 0xFF9900FF, string)
					CreateExplosion(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 9, 5.0)
				)
				else
				(
					UpdateDynamic3DTextLabelText(Text3D:DoorData(doorid)(dFireLabels), 0xAA3333FF, string)
					CreateExplosion(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 2, 10.0)
				)
				
				if(percent )= 100)
				(
					for (object_id = 0 object_id (= MAX_OBJECTS object_id++)
					(
						if(IsValidDynamicObject(object_id))
						(
							if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID, DoorData(doorid)(dExitVW)))
							(
								if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_MODEL_ID) == 18694)
								(
									DestroyDynamicObject(object_id)
								)
							)
						)
					)
				
					DoorData(doorid)(dExitX) = 0.0
					DoorData(doorid)(dExitY) = 0.0
					DoorData(doorid)(dExitZ) = 0.0
					
					DoorData(doorid)(dExitAng) = 0.0
					DoorData(doorid)(dExitInt) = 0
					DoorData(doorid)(dExitVW) = 0
				
					DestroyDynamicObject(DoorData(doorid)(dFireObject))
					DestroyDynamic3DTextLabel(Text3D:DoorData(doorid)(dFireLabels))
					
					DoorData(doorid)(dBurnTime) = 0
					CreateExplosion(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 6, 10.0)
				)
				else if(percent (= 0)
				(
					for (object_id = 0 object_id (= MAX_OBJECTS object_id++)
					(
						if(IsValidDynamicObject(object_id))
						(
							if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID, DoorData(doorid)(dExitVW)))
							(
								if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_MODEL_ID) == 18694)
								(
									DestroyDynamicObject(object_id)
								)
							)
						)
					)
				
					DestroyDynamicObject(DoorData(doorid)(dFireObject))
					DestroyDynamic3DTextLabel(Text3D:DoorData(doorid)(dFireLabels))
					
					DoorData(doorid)(dBurnTime) = 0
				)
				SaveDoor(doorid, SAVE_DOOR_THINGS | SAVE_DOOR_EXIT)
			)
		)
	)
	
	/*
	// SprawdŸ, czy jest po³¹czenie z mySQL
	if(!mysql_ping())
	(
		mysql_reconnect()
		print((mysql) £¹czê siê z mySQL ponownie... Próba: 1/3)
		
		if(!mysql_ping())
		(
			mysql_reconnect()
			print((mysql) £¹czê siê z mySQL ponownie... Próba: 2/3)
			
			if(!mysql_ping())
			(
				mysql_reconnect()
				print((mysql) £¹czê siê z mySQL ponownie... Próba: 3/3)
				
				if(!mysql_ping())
				(
					print((mysql) Po³¹czenie z baz¹ danych nie by³o mo¿liwe.)
				)
			)
		)
	)
	*/
	
	
	// Sprawdzenie redisa
	
/*	if(!redis_check_connection())
	(
		print((redis) Lacze sie z serwerem redisa ponownie ... Proba: 1/3)
		redis_connect(REDIS_HOST, REDIS_PORT)
		if(!redis_check_connection())
		(
			print((redis) Lacze sie z serwerem redisa ponownie ... Proba: 2/3)
			redis_connect(REDIS_HOST, REDIS_PORT)
			if(!redis_check_connection())
			(
				print((redis) Lacze sie z serwerem redisa ponownie ... Proba: 3/3)
				redis_connect(REDIS_HOST, REDIS_PORT)
				if(!redis_check_connection())
				(
					print((redis) Polaczenie z serwerem redisa nie bylo mozliwe.)
				)
			)
		)
	)*/
	
	
	
	// Resetowanie strzelanin co 10 minut
	if(minute % 10 == 0)
	(
		for(i = 0 i ( sizeof(GunRegionInfo) i++)
		(
			ShootsFired(i) = 0
			ShootsFiredInfo(i) = false
		)
	)
	
	foreach(Vehicles, vehid)
	(
		if(vehid + 1 ) MAX_VEHICLES)
		(
			break
		)
		if(CarInfo(vehid)(cUID))
		(
			if(CarInfo(vehid)(cOwnerExitTime) != 0 && CarInfo(vehid)(cOwnerExitTime) + (60*5) ( gettime())
			(
				Float:VehX, Float:VehY, Float:VehZ
				GetVehiclePos(vehid, VehX, VehY, VehZ)

				string(128)
				format(string, sizeof(string), (( Pojazd %s (%s) zostaje odspawnowany poniewa¿ jego w³a¶ciciel wyszed³ z gry ponad 5 minut temu. )), CarInfo(vehid)(cName), VehicleData(CarInfo(vehid)(cModel) - 400)(vName))
				
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(IsPlayerInRangeOfPoint(i, 20.0, VehX, VehY, VehZ))
						(
							SendClientMessage(i, COLOR_GREY, string)
						)
					)
				)

				CarInfo(vehid)(cOwnerExitTime) = 0
				UnspawnVehicle(CarInfo(vehid)(cUID))
			)
		)		
	)
	
	return 1
)

/*forward OnSecondTimer()
public OnSecondTimer()*/
task OnSecondTimer(1000)()
(
	string(256)
	
	if(AdminLogTime)
	(
		AdminLogTime --
		
		if(AdminLogTime (= 0)
		(
			TextDrawSetString(Text:TextDrawAdminLog, _)
		)
	)
	
	if(PunishTime)
	(
		PunishTime --
		if(PunishTime (= 0)
		(
			TextDrawHideForAll(Text:TextDrawPunishInfo)
		)
	)
	
	// Gun Region Info
	for(j = 0 j ( sizeof(GunRegionInfo) j++)
	(
		if(ShootsCountdown(j) ) 0)
		(
			ShootsCountdown(j)--
			
			if(ShootsCountdown(j) == 0)
			(
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pGroupDuty))
						(
							group_id_fix = GetPlayerDutyGroupID(i)
							if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
							(
		 						PlayerCache(i)(pMainGroupSlot) = GetPlayerGroupSlot(i, GroupData(group_id_fix)(gUID)) + 1
								format(string, sizeof(string), !!%d ** (%s): Centrala dla wszystkich jednostek, dostaliœmy informacje o strzelaninie w pobli¿u %s, odbiór.  **, PlayerCache(i)(pMainGroupSlot), GroupData(group_id_fix)(gTag), GunRegionInfo(j)(grName))
								SendClientMessage(i, GroupData(group_id_fix)(gColor), string)
								ShootsFiredInfo(j) = true
							)
						)
					)
				)
			)
		)
	)
	
	if(QuakeTimer ) 0)
	(
		QuakeTimer--
		if(QuakeTimer == 0)
		(
			foreach(Player, i)
			(
				SetPlayerDrunkLevel(i, 0)
			)
		)
	)
	
	foreach(Player, i)
	(
		if(SpawnTime(i) (= 0)
		(
			if(LogTime(i) ) 0)
			(
				if(LogTime(i) + 15 ( gettime())
				(
					SendClientMessage(i, COLOR_RED, Nie cheatuj ...)
					Kick(i)
				)
			)
		)
		if(Logged(i) && Spawned(i) && !PlayerCache(i)(pSwitching))
		(
			anim_id = GetPlayerAnimationIndex(i),
				Float:PosX, Float:PosY, Float:PosZ,
				Float:hp, status = PlayerCache(i)(pStatus),
				loop_player_weapon = GetPlayerWeapon(i),
				loop_player_speed = GetPlayerSpeed(i, true),
				loop_player_vehid = GetPlayerVehicleID(i)
			
			// FBI namierzanie kamer¹ ludzi, ciekawe czy bêdzie lagowaæ
			if(loop_player_weapon == 43)
			(
				if(IsPlayerInGroupType(i, GROUP_FBI))
				(
					Float:agentPos(3)
					GetPlayerPos(i, agentPos(0), agentPos(1), agentPos(2))
					
					for(target = 0  target ( MAX_PLAYERS target++)
					(
						if(IsPlayerConnected(target))
						(
							// Warunek, ¿eby nie by³o mo¿na zobaczyæ kto kogo specuje i samego siebie
							if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(target) && PlayerCache(target)(pSpectate) == INVALID_PLAYER_ID && target != i)
							(
								Float:targetPos(3)
								GetPlayerPos(target, targetPos(0), targetPos(1), targetPos(2))
								
								if(IsPlayerFacingPoint(i, targetPos(0), targetPos(1), 2.5) && IsPlayerInRangeOfPoint(target, 100.0, agentPos(0), agentPos(1), agentPos(2)))
								(
									output(128)
									format(output, sizeof(output), ~n~~n~~n~~n~~n~~n~Widzisz: ~g~%s, PlayerName(target))
									GameTextForPlayer(i, output, 5000, 4)
								)
							)
						)
					)
				)
			)
			
			// Kolizja po /przejazd
			if(PlayerCache(i)(pVehCollisions) != 0)
			(
				PlayerCache(i)(pVehCollisions)--
			)
			if(PlayerCache(i)(pVehCollisions) == 0)
			(
				DisableRemoteVehicleCollisions(i, 0)
			)

			if(PlayerCache(i)(pSparing) != INVALID_PLAYER_ID)
			(
				enemy = PlayerCache(i)(pSparing), Float:Pos(3)
				GetPlayerPos(enemy, Pos(0), Pos(1), Pos(2))
				
				if(GetPlayerVirtualWorld(enemy) != GetPlayerVirtualWorld(i))
				(
					stopSparing(i)
				)
				
				if(!IsPlayerInRangeOfPoint(i, 20.0, Pos(0), Pos(1), Pos(2)))
				(
					stopSparing(i)
				)
			)
			
			// SCENY
			if(!isScened(i))
			(
				if(sceneWorks)
				(
					if(GetPlayerVirtualWorld(i) == sceneWorld)
					(
						if(IsPlayerInRangeOfPoint(i, sceneRadius, scenePosX, scenePosY, scenePosZ))
						(
							isScened(i) = 1
							PlayAudioStreamForPlayer(i, sceneStream)
						)
					)
				)
			)
			else
			(
				if(!IsPlayerInRangeOfPoint(i, sceneRadius, scenePosX, scenePosY, scenePosZ))
				(
					isScened(i) = 0
					StopAudioStreamForPlayer(i)
				)
			)
			
			if(PlayerCache(i)(pSearchingTime) ) 0)
			(
				searching_id = GetPlayerID(PlayerCache(i)(pSearching))
				GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~g~trwa szukanie..., 1000, 3)
				PlayerCache(i)(pSearchingTime) -= 1
				
				if(searching_id == INVALID_PLAYER_ID)
				(
					GuiMsg(i, Wybrany numer nagle znikn¹³ z sieci., 1)
					PlayerCache(i)(pSearchingTime) = 0
					PlayerCache(i)(pSearching) = -1
				)
				
				if(PlayerCache(i)(pSearchingTime) == 0 && searching_id != INVALID_PLAYER_ID)
				(
					Float:x, Float:y, Float:z
					GetPlayerPos(searching_id, x ,y ,z)
					
					PlayerCache(i)(pSearchingTime) = 0
					PlayerCache(i)(pSearching) = -1
					
					if(searching_id != INVALID_PLAYER_ID && GetPlayerVirtualWorld(searching_id) == 0)
					(
						Checkpoint(i) = 1
						SetPlayerCheckpoint(i, x, y, z, 4.0)
					)
					else
					(
						GuiMsg(i, Wyst¹pi³ b³¹d w sieci.\nSpróbuj jeszcze raz., 1)
					)
				)
			)
			
			if(PlayerCache(i)(pDrugDealing))
			(	
				zoneid = GetPlayerZoneID(i)
				zoneowner = ZoneInfo(zoneid)(zOwner)
				ownerzones = 0
				for(zone = 0 zone ( MAX_ZONES zone++)
				(
					if(ZoneInfo(zone)(zUID) ) 0)
					(
						if(ZoneInfo(zone)(zOwner) == zoneowner)
						(
							ownerzones++
						)
					)
				)
				DailyDrugsLimit = 3*ownerzones
				if(PlayerCache(i)(pDailyDrugs) ) DailyDrugsLimit)
				(
					// przerwij
					PlayerCache(i)(pDrugDealing) = false
					PlayerCache(i)(pSelling) = false
					PlayerCache(i)(pCorner) = -1
					DisablePlayerCheckpoint(i)
					ApplyAnimation(i, CARRY, crry_prtial, 4.1, 0, 0, 0, 0, 0)
					
					GuiMsg(i, Przerwa³eœ proces sprzeda¿y narkotyków., 0)
				)
				
				if(IsPlayerInAnyVehicle(i))
				(
					// przerwij
					PlayerCache(i)(pDrugDealing) = false
					PlayerCache(i)(pSelling) = false
					PlayerCache(i)(pCorner) = -1
					DisablePlayerCheckpoint(i)
					ApplyAnimation(i, CARRY, crry_prtial, 4.1, 0, 0, 0, 0, 0)
					
					GuiMsg(i, Przerwa³eœ proces sprzeda¿y narkotyków., 0)
				)
				
				occupied = false
				for(j = 0 j ( MAX_CORNERS j++)
				(
					if(CornerInfo(j)(cOwner) == ZoneInfo(zoneid)(zOwner))
					(
						if(countCornerDealers(j) )= 2)
						(
							occupied = true // ktoœ handluje na cornerze na strefie tego gangu
						)
					)
				)
				
				if(occupied)
				(
					GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~r~za duzo dilerow!, 1000, 3)
				)
				
				corner_id = PlayerCache(i)(pCorner)
				if(!PlayerCache(i)(pSelling) && IsPlayerInRangeOfPoint(i, 4.0, CornerInfo(corner_id)(cPosX), CornerInfo(corner_id)(cPosY), CornerInfo(corner_id)(cPosZ)) && GetPlayerVirtualWorld(i) == 0 && countCornerDealers(corner_id) ( 2)
				(
					ApplyAnimation(i, DEALER, DEALER_DEAL, 4.0, 0, 1, 1, 1, 1, 0)
					GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~g~trwa proces sprzedazy..., 1000, 3)
					gratis = random(3)
					chance = random(100)
					
					if(float(chance) ( (CornerInfo(PlayerCache(i)(pCorner))(cRisk) / 10) + gratis )
					(
						// Otwórz GUI sprzeda¿y.
						PlayerCache(i)(pSelling) = true
						
						stringg(256), msg = random(3)
						switch(msg)
						(
							case 0:
								format(stringg, sizeof(stringg), ** Do %s podszed³ zakapturzony, wychudzony facet., PlayerName(i))
							case 1:
								format(stringg, sizeof(stringg), ** %s zacz¹³ rozmawiaæ z nisk¹ kobiet¹, która w³aœnie do niego podesz³a., PlayerName(i))
							case 2:
								format(stringg, sizeof(stringg), ** M³ody skate podbija do %s i zaczyna z nim rozmawiaæ, rozgl¹daj¹c siê na boki., PlayerName(i))
						)
						
						ProxDetector(10.0, i, stringg, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
						ShowPlayerDialog(i, D_DRUG_DEALING_START, DIALOG_STYLE_LIST, Klient » akcja, 1. OdpêdŸ klienta\n2. Rozpocznij handel, Wybierz, Anuluj)
						
						// Mo¿liwoœæ poinformowania LSPD
						if(CornerInfo(corner_id)(cRisk) ) 10)
						(
							pd_alert = random(100)
							if(pd_alert ( 50)
							(
								foreach(Player, plr)
								(
									if(Logged(plr) && Spawned(plr))
									(
										if(PlayerCache(plr)(pGroupDuty))
										(
											group_id_fix = GetPlayerDutyGroupID(plr)
											if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
											(
												PlayerCache(plr)(pMainGroupSlot) = GetPlayerGroupSlot(plr, GroupData(group_id_fix)(gUID)) + 1
												format(string, sizeof(string), !!%d ** (%s): Centrala dla wszystkich jednostek, dostaliœmy informacje o dilerze w pobli¿u %s, odbiór.  **, PlayerCache(plr)(pMainGroupSlot), GroupData(group_id_fix)(gTag), GunRegionInfo(getPlayerRegion(i))(grName))
												SendClientMessage(plr, GroupData(group_id_fix)(gColor), string)
											)
										)	
									)
								)
							)
						)
						else if(CornerInfo(corner_id)(cRisk) ( 10)
						(
							pd_alert = random(100)
							if(pd_alert ( 25)
							(
								foreach(Player, plr)
								(
									if(Logged(plr) && Spawned(plr))
									(
										if(PlayerCache(plr)(pGroupDuty))
										(
											group_id_fix = GetPlayerDutyGroupID(plr)
											if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
											(
												PlayerCache(plr)(pMainGroupSlot) = GetPlayerGroupSlot(plr, GroupData(group_id_fix)(gUID)) + 1
												format(string, sizeof(string), !!%d ** (%s): Centrala dla wszystkich jednostek, dostaliœmy informacje o dilerze w pobli¿u %s, odbiór.  **, PlayerCache(plr)(pMainGroupSlot), GroupData(group_id_fix)(gTag), GunRegionInfo(getPlayerRegion(i))(grName))
												SendClientMessage(plr, GroupData(group_id_fix)(gColor), string)
											)
										)	
									)
								)
							)
						)
					)
				)
			)
			
			if(PlayerCache(i)(pBuyCount) ) 0)
			(
				PlayerCache(i)(pBuyCount)--
				
				if(PlayerCache(i)(pBuyCount) == 0)
				(
					hrp_TogglePlayerControllable(i, 1)
					PlayerTextDrawHide(i, TextDrawPropertyFade1(i))
					PlayerTextDrawHide(i, TextDrawPropertyFade2(i))
					PlayerTextDrawHide(i, TextDrawPropertyMSG(i))
					SetCameraBehindPlayer(i)
					
					StopAudioStreamForPlayer(i)
					PlayerPlaySound(i, 30800, 0.0, 0.0, 0.0)
				)
			)
			
			if(PlayerCache(i)(pViewDoorID) != INVALID_DOOR_ID)
			(
				if(PlayerCache(i)(pViewTime) ) 0)
					PlayerCache(i)(pViewTime)--
					
				viewMsg(128)
				format(viewMsg, sizeof(viewMsg), ~n~~n~~n~~n~~n~~n~~n~~y~czas podgladu: ~g~%d ~y~sekund, PlayerCache(i)(pViewTime))
				GameTextForPlayer(i, viewMsg, 1000, 3)
					
				if(PlayerCache(i)(pViewTime) == 0)
				(
					// koniec podgl¹du
					doorid = PlayerCache(i)(pViewDoorID)
					PlayerCache(i)(pViewDoorID) = INVALID_DOOR_ID
					
					SetPlayerInterior(i, DoorData(doorid)(dEnterInt))
					SetPlayerVirtualWorld(i, DoorData(doorid)(dEnterVW))
					SetPlayerPos(i, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ))
					
					GuiMsg(i, Podgl¹d drzwi dobieg³ koñca., 0)
				)
			)
			
			if(PlayerCache(i)(pCourse))
			(
				if(IsPlayerInAnyVehicle(i))
				(
					if(PlayerCache(i)(pCourseMS) ( GetVehicleSpeed(loop_player_vehid))
						PlayerCache(i)(pCourseMS) = GetVehicleSpeed(loop_player_vehid)
				)
			)
			
			if(PlayerCache(i)(pBombTime) ) 0)
			(
				if(PlayerCache(i)(pBombPhase) == BOMB_TYPE_ARM)
				(
					if(!IsPlayerInAnyVehicle(i))
					(
						PlayerCache(i)(pBombTime) = 0
						GuiMsg(i, Wysiad³eœ z pojazdu, proces uzbrajania bomby zosta³ przerwany., 1)
					)
					
					if(PlayerCache(i)(pBombTime) == 1)
					(
						PlayerCache(i)(pBombTime) = 0
						
						armveh = loop_player_vehid
						CarInfo(armveh)(cArmed) = true
						
						GuiMsg(i, Zamontowa³eœ bombê w tym pojeŸdzie, odpalenie silnika spowoduje ekspolzjê, uciekaj!, 1)
						
						DeleteItem(PlayerCache(i)(pBombID))
					)
					
					PlayerCache(i)(pBombTime)-- 
					
					message(128)
					format(message, sizeof(message), ~y~pozostaly czas bomby: ~g~%i sek, PlayerCache(i)(pBombTime))
					GameTextForPlayer(i, message, 1000, 3)
				)
				
				if(PlayerCache(i)(pBombPhase) == BOMB_TYPE_SEARCH)
				(
					if(!IsPlayerInAnyVehicle(i))
					(
						PlayerCache(i)(pBombTime) = 0
						GuiMsg(i, Wysiad³eœ z pojazdu, proces szukania bomby zosta³ przerwany., 1)
					)
					
					if(PlayerCache(i)(pBombTime) == 1)
					(
						PlayerCache(i)(pBombTime) = 0
						armveh = loop_player_vehid
						
						if(!CarInfo(armveh)(cArmed))
						(
							GuiMsg(i, Nie znaleziono bomby w tym pojeŸdzie., 1)
					//		return 1 // seler test, wyjebalem returna
						)
						else
						(
							rand = random(10)
							switch(rand)
							(
								case 0..8:
								(
									GuiMsg(i, Znalaz³eœ bombê, nie odpalaj pojazdu, poniewa¿ wybuchnie., 1)
									PlayerCache(i)(pBombFound) = 1
								)
								case 9:
								(
									GuiMsg(i, Nie znaleziono bomby w tym pojeŸdzie., 1)
									PlayerCache(i)(pBombFound) = 0
								)
							)
						)
					)
					
					PlayerCache(i)(pBombTime)-- 
					
					message(128)
					format(message, sizeof(message), ~y~pozostaly czas szukania bomby: ~g~%i sek, PlayerCache(i)(pBombTime))
					GameTextForPlayer(i, message, 1000, 3)
				)
				
				if(PlayerCache(i)(pBombPhase) == BOMB_TYPE_DEFUSE)
				(
					if(!IsPlayerInAnyVehicle(i))
					(
						PlayerCache(i)(pBombTime) = 0
						GuiMsg(i, Wysiad³eœ z pojazdu, proces rozbrajania bomby zosta³ przerwany., 1)
					)
					
					if(PlayerCache(i)(pBombTime) == 1)
					(
						PlayerCache(i)(pBombTime) = 0
						armveh = loop_player_vehid
						
						CarInfo(armveh)(cArmed) = false
						GuiMsg(i, Rozbroi³eœ bombê w tym pojeŸdzie., 1)
					)
					
					PlayerCache(i)(pBombTime)-- 
					
					message(128)
					format(message, sizeof(message), ~y~pozostaly czas rozbrajania bomby: ~g~%i sek, PlayerCache(i)(pBombTime))
					GameTextForPlayer(i, message, 1000, 3)
				)
			)
			
			if(PlayerCache(i)(pLoginEx) ) 0)
			(
				// anti flood - niby ¿aden ale zawsze
				PlayerCache(i)(pLoginEx)--
			)
			
			if(PlayerCache(i)(pUseGUI))
			(
				SelectTextDraw(i, 0x8C8C8CFF)
			)
			
			if(PlayerCache(i)(pSurfID) != INVALID_SURFBOARD_ID && Surfboard(PlayerCache(i)(pSurfID))(surfPlayerID) == i)
			(
				surfid = PlayerCache(i)(pSurfID)
				objectid = Surfboard(surfid)(surfObjectID)
				Float:Pos(3)
				GetObjectPos(objectid,Pos(0),Pos(1),Pos(2))
				if(!IsPlayerInRangeOfPoint(i,3.0,Pos(0),Pos(1),Pos(2)))
				(
					surf_StopSurfing(i)
					surf_StopBoard(surfid)
				)
			)

			//telefon
			if(PlayerCache(i)(pCallTicks) ) 0)
			(
				if(PlayerCache(i)(pCallTicks) == 1)
				(
					//przerwij gadanie
					callid = PlayerCache(i)(pCall)

					if(callid != -1)
					(
						EndCall(callid)
						//return 1
					)
					else
					(
						foreach(Calls, callidd)
						(
							if(Call(callidd)(caller) == i || Call(callidd)(called) == i)
							(
								EndCall(callidd)
								//return 1
							)
						)
					)
				)
				
				PlayerCache(i)(pCallTicks)--
			)
			
			if(PlayerCache(i)(pPackingTime) ) 0)
			(
				trailerid = PlayerCache(i)(pTrailerID), Float:Pos(3)
				GetVehiclePos(trailerid,Pos(0),Pos(1),Pos(2))
				switch(PlayerCache(i)(pPackingPhase))
				(
					case TRUCK_PHASE_LOAD:
					(
						if(!IsPlayerInRangeOfPoint(i,15.0,Pos(0),Pos(1),Pos(2)) && trailerid != -1)
						(
							GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~n~~r~zbyt daleko od naczepy, 1000, 3)
						)
						else
						(
							if(PlayerCache(i)(pPackingTime) == 1)
							(
								//zakoncz zaladunek
								trackid = PlayerCache(i)(pTrackID), buffer(256)
								format(buffer,sizeof(buffer),SELECT to, packagetype,company FROM hrp_truck_route WHERE uid=%i,trackid)
								mysql_query(buffer)
								mysql_store_result()
								point, packagetype,company(32)
								while(mysql_fetch_row(buffer,|))
								(
									sscanf(buffer,p(|)iis(32),point, packagetype,company)
								)
								mysql_free_result()
								
								format(buffer,sizeof(buffer),SELECT posx, posy, posz, town FROM hrp_truck_target WHERE uid=%i,point)
								mysql_query(buffer)
								mysql_store_result()
								town(32)
								while(mysql_fetch_row(buffer,|))
								(
									sscanf(buffer,p(|)fffs(32),Pos(0),Pos(1),Pos(2),town)
								)
								
								PlayerCache(i)(pPackingPhase) = TRUCK_PHASE_LOADED
								DisablePlayerCheckpoint(i)
								SetPlayerCheckpoint(i, Pos(0),Pos(1),Pos(2), 7.0)
								
								format(buffer,sizeof(buffer),(CCCCCC)Do naczepy za³adowano towar, teraz musisz udaæ siê do punktu zrzutu.\nMiejsce docelowe: (C4B100)%s\n(CCCCCC),town)
								switch(packagetype)
								(
									case CARGO_TYPE_OIL:
									(
										format(buffer,sizeof(buffer),%s\n(CCCCCC)Typ ³adunku: (C4B100)paliwo(CCCCCC),buffer)
									)
									case CARGO_TYPE_FOOD:
									(
										format(buffer,sizeof(buffer),%s\n(CCCCCC)Typ ³adunku: (C4B100)artyku³y spo¿ywcze(CCCCCC),buffer)
									)
									case CARGO_TYPE_TOOLS:
									(
										format(buffer,sizeof(buffer),%s\n(CCCCCC)Typ ³adunku: (C4B100)narzêdzia(CCCCCC),buffer)
									)
									case CARGO_TYPE_MATERIALS:
									(
										format(buffer,sizeof(buffer),%s\n(CCCCCC)Typ ³adunku: (C4B100)materia³y budowlane(CCCCCC),buffer)
									)
								)
								format(buffer,sizeof(buffer),%s\nNazwa zleceniodawcy: (C4B100)%s\n\nPowodzenia!,buffer,company)
								GuiMsg(i,buffer,0)
								
							)
							msg(128)
							format(msg,sizeof(msg),~n~~n~~n~~n~~n~~n~~n~~n~~y~pozostaly czas zaladunku: ~g~%i ~y~sekund,PlayerCache(i)(pPackingTime))
							GameTextForPlayer(i, msg, 1000, 3)
							PlayerCache(i)(pPackingTime)--
						)
					)
					case TRUCK_PHASE_UNLOAD:
					(
						if(!IsPlayerInRangeOfPoint(i,15.0,Pos(0),Pos(1),Pos(2)) && trailerid != -1)
						(
							GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~n~~r~zbyt daleko od naczepy, 1000, 3)
						)
						else
						(
							sscanf(PlayerCache(i)(pUnloadPos),p(|)fff,Pos(0),Pos(1),Pos(2))
							if(!IsPlayerInRangeOfPoint(i,15.0,Pos(0),Pos(1),Pos(2)))
							(
								GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~n~~r~zbyt daleko od punktu rozladunku, 1000, 3)
							)
							else
							(
								if(PlayerCache(i)(pPackingTime) == 1)
								(
									//zakoncz wyladunek
									orderid = PlayerCache(i)(pTrackID), buffer(256)
									
									format(buffer,sizeof(buffer),SELECT cash FROM hrp_truck_route WHERE uid=%i,orderid)
									mysql_query(buffer)
									mysql_store_result()
									cash = mysql_fetch_int()
									mysql_free_result()
									
									msg(128)									
									if(!PlayerCache(i)(pGroupDuty))
									(
										printf((truck-bug) Gracz %s (UID: %d) prawdopodobnie chcial teraz zbugowac nasz system bez duty., PlayerName(i), PlayerCache(i)(pUID))
										format(msg,sizeof(msg),(CCCCCC)Nie jesteœ na s³u¿bie grupy, nie otrzymasz gotówki za przewóz towaru.)
										GuiMsg(i,msg,0)
									)
									else
									(
										group_id_fix = GetPlayerDutyGroupID(i)
										
										group_cash = floatround(0.75 * cash),
											player_cash = floatround(0.25 * cash)
											
										hrp_GivePlayerMoney(i, player_cash)
										GroupData(group_id_fix)(gCash) += group_cash
										SaveGroup(group_id_fix)
										
										AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(i)(pUID), 0, 0, cash, Przewoz towaru(truckers))
										
										AddGroupLog(i, group_id_fix, %s wykona³ kurs za %d., PlayerName(i), cash)
										
										format(msg,sizeof(msg),(CCCCCC)Zakoñczy³eœ trasê, otrzyma³eœ premiê w wysokoœci (C4B100)$%i(CCCCCC)!\nNa konto grupy dodano: (C4B100)$%i, player_cash, group_cash)
										
										GuiMsg(i,msg,0)
									)
									DestroyPlayerTrack(i)
									TruckersTicks++
								)
								msg(128)
								format(msg,sizeof(msg),~n~~n~~n~~n~~n~~n~~n~~n~~y~pozostaly czas wyladunku: ~g~%i ~y~sekund,PlayerCache(i)(pPackingTime))
								GameTextForPlayer(i, msg, 1000, 3)
								PlayerCache(i)(pPackingTime)--
							)
						)
					)
				)
			)
			
			//slots			
			if(PlayerCache(i)(pSlots))
			(
				if(PlayerCache(i)(pSlotTicks) ) 1)
				(
					PlayerCache(i)(pSlotTicks)--
					slots_RandIcons(i)
				)
				else if(PlayerCache(i)(pSlotTicks) == 1)
				(
					//last rand
					PlayerCache(i)(pSlotTicks) = 0
					one = random(6)
					PlayerTextDrawSetString(i,TextDrawSlotsFirst(i), SlotInfo(one)(slName))
					PlayerTextDrawShow(i,TextDrawSlotsFirst(i))
					
					two = random(6)
					PlayerTextDrawSetString(i,TextDrawSlotsSecond(i), SlotInfo(two)(slName))
					PlayerTextDrawShow(i,TextDrawSlotsSecond(i))
					
					three = random(6)
					PlayerTextDrawSetString(i,TextDrawSlotsThird(i), SlotInfo(three)(slName))
					PlayerTextDrawShow(i,TextDrawSlotsThird(i))
					
					if(one == two && two == three)
					(
						// Wygrana w jednorêkiego bandytê
						chance = random(3)
						if(chance == 2)
						(
							// Poprawka po nerfie, inne losowanie puli
							all_cash = slots_GetCashCount()
							Float:win_cash = (all_cash * 0.50) * (0.50 + float(random(1000) / (random(2000)+1)))
							
							//slotid = PlayerCache(i)(pSlotID)
							//hrp_GivePlayerMoney(i, SlotMachine(slotid)(mMoney))
							//SavePlayerStats(i, SAVE_PLAYER_BASIC)
							//SlotMachine(slotid)(mMoney) = 0
							
							if(floatround(win_cash) ) 10000)
								win_cash = 10000.0
							
							hrp_GivePlayerMoney(i, floatround(win_cash))
							slots_TakeCash( floatround(win_cash) )
							GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~n~~g~zgarniasz jackpota, 5000, 3)
						)
						else
						(
							one = random(6)
							PlayerTextDrawSetString(i,TextDrawSlotsFirst(i), SlotInfo(one)(slName))
							PlayerTextDrawShow(i,TextDrawSlotsFirst(i))
							
							two = random(6)
							PlayerTextDrawSetString(i,TextDrawSlotsSecond(i), SlotInfo(two)(slName))
							PlayerTextDrawShow(i,TextDrawSlotsSecond(i))
							
							three = random(6)
							PlayerTextDrawSetString(i,TextDrawSlotsThird(i), SlotInfo(three)(slName))
							PlayerTextDrawShow(i,TextDrawSlotsThird(i))
						)
					)
					else
					(
						GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~n~~r~sprobuj jeszcze raz, 5000, 3)
					)
				)
			)
			
			GetPlayerPos(i, PosX, PosY, PosZ)
			
			if(loop_player_weapon != 0)
			(
				if(!IsPlayerInAnyVehicle(i))
				(
					weapon = loop_player_weapon, found = false
					if(weapon != 0)
					(
						for(j = 0 j ( 3 j++)
						(
							if(WeaponCache(i)(j)(pWeaponID) == weapon)
							(
								found = true
							)
						)
						
						// dodajmy wyj¹tek dla tych co usuwaj¹ taga
						if(!found)
						(
							if(weapon == 41 && PlayerCache(i)(pScouring) == true)
							(
								found = true
							)
						)
						
						if(!found)
						(
							if(PlayerCache(i)(pWeaponWarning) ) 2)
							(
								format(string, sizeof(string), Wklej ca³y, nieedytowany screenshot tej linijki do apelacji (%s, %d), PlayerName(i), PlayerCache(i)(pUID))
								SendClientMessage(i, COLOR_RED, string)
								
								PlayerCache(i)(pWeaponWarning) = 0
								weap_name(24)
								GetWeaponName(weapon, weap_name, 24)
								
								ResetPlayerWeapons(i)
								
								//baninfo(64)
								//format(baninfo, sizeof(baninfo), WeaponHack (WeapID: %d, WeapName: %s)., weapon, weap_name)
								//hrp_Ban(i, -1, baninfo, 0)
								
								ShowAdminLog(~r~(cheat) ~w~Gracz %s (ID: %d, Godzin: %d) prawdopodobnie uzywa weapon hacka (WeapID: %d, WeapName: %s)., PlayerName(i), i, PlayerCache(i)(pHours), weapon, weap_name)
								
								if(PlayerCache(i)(pHours) ( 2)
								(
									hrp_Ban(i, -1, Cheater, 0)
								)
							)
							else
							(
								PlayerCache(i)(pWeaponWarning)++
								
								ResetPlayerWeapons(i)
		
								WeaponCache(i)(WEAPON_MAIN)(pWeaponUID) = 0
								WeaponCache(i)(WEAPON_MAIN)(pWeaponID) = 0
								WeaponCache(i)(WEAPON_MAIN)(pWeaponAmmo) = 0
								WeaponCache(i)(WEAPON_MAIN)(pLastAmmo) = 0
								WeaponCache(i)(WEAPON_MAIN)(pShot) = false
								
								WeaponCache(i)(WEAPON_SIDE)(pWeaponUID) = 0
								WeaponCache(i)(WEAPON_SIDE)(pWeaponID) = 0
								WeaponCache(i)(WEAPON_SIDE)(pWeaponAmmo) = 0
								WeaponCache(i)(WEAPON_SIDE)(pLastAmmo) = 0
								WeaponCache(i)(WEAPON_SIDE)(pShot) = false
								
								WeaponCache(i)(WEAPON_FUNC)(pWeaponUID) = 0
								WeaponCache(i)(WEAPON_FUNC)(pWeaponID) = 0
								WeaponCache(i)(WEAPON_FUNC)(pWeaponAmmo) = 0
								WeaponCache(i)(WEAPON_FUNC)(pLastAmmo) = 0
								WeaponCache(i)(WEAPON_FUNC)(pShot) = false
								
								ResetPlayerWeapons(i)
							)
						)
					)
				)
			)
			
			cammode = GetPlayerCameraMode(i)			
			if(cammode == 55)
			(
				if(PlayerCache(i)(pHours) ( 5)
				(
					hrp_Kick(i, -1, Drive-By, 0)
				)
			)
			
			if(PlayerCache(i)(pSpreadTime) ) 0)
			(
				PlayerCache(i)(pSpreadTime)--
			)
			
			if(PlayerCache(i)(pBallTicks) ) 0)
			(
				PlayerCache(i)(pBallTicks)--
			)
			
			// Sprawdzanie czy gracz nie doda³ sobie hp
			GetPlayerHealth(i, hp)
			if(hp ( PlayerCache(i)(pHealth))
			(
		 		GetPlayerHealth(i, PlayerCache(i)(pHealth))
			)
			else if(hp ) PlayerCache(i)(pHealth))
			(
		 		SetPlayerHealth(i, PlayerCache(i)(pHealth))
			)
			
			// Sprawdzanie czy kasa sampowa siê zgadza
			if(GetPlayerMoney(i) ) PlayerCache(i)(pCash))
			(
				ResetPlayerMoney(i)
				GivePlayerMoney(i, PlayerCache(i)(pCash))
			)
			
			// Zmniejszanie limitu na /osel model
			if(PlayerCache(i)(pOselLimit) ) 0)
			(
				PlayerCache(i)(pOselLimit) --
			)
			
			if(PlayerCache(i)(pFlood) ) 0) (
				PlayerCache(i)(pFlood) --
			)

			if(IsPlayerAFK(i))
			(
				if(PlayerCache(i)(pAFK) ( -1 * 60 * 3)
				(
					if(PlayerCache(i)(pDutyUID) != 0 && !PlayerCache(i)(pAdminDuty))
					(
						hrp_Kick(i, -1, AFK podczas duty biznesu.)	
					)
				)
			)
			
			// Sprawdzanie czy ktoœ nie robi rampageu.
			if(PlayerCache(i)(pKillCount) ) 3 && PlayerCache(i)(pAdmin) == 0)
			(
				if(IsPlayerInGroupType(i, GROUP_POLICE) || IsPlayerInGroupType(i, GROUP_CRIMINAL) || IsPlayerInGroupType(i, GROUP_PRISON))
				(
					if(PlayerCache(i)(pKillCount) ) 7)
					(
						hrp_Ban(i, -1, Prawdopodobny DM - zapraszam na forum., 0)
					)
				)
				else
				(
					hrp_Ban(i, -1, Prawdopodobny DM - zapraszam na forum., 0)
				)
			)
			
			// Drunk level
			if(!PlayerCache(i)(pAiming) && GetPlayerDrunkLevel(i) ) 0)
			(
				PlayerCache(i)(pDrunkLevel) = GetPlayerDrunkLevel(i)
			)
			else if(GetPlayerDrunkLevel(i) (= 0 && PlayerCache(i)(pDrunkLevel))
			(
				PlayerCache(i)(pDrunkLevel) = 0
			)

			if(PlayerCache(i)(pArmourDelay) ) 0)
			(
				PlayerCache(i)(pArmourDelay)--
			)
			if(PlayerCache(i)(pArmourDelay) ( 0)
			(
				PlayerCache(i)(pArmourDelay) = 0
			)
			
			// Jeœli ma kamizelkê
			if(PlayerCache(i)(pArmour))
			(
				if(PlayerCache(i)(pArmourDelay) (= 0)
				(
					Float:armour
					GetPlayerArmour(i, armour)
					
					if(armour (= PlayerCache(i)(pArmour))
					(
						GetPlayerArmour(i, PlayerCache(i)(pArmour))
					)
					if(armour ) PlayerCache(i)(pArmour))
					(
						SetPlayerArmour(i, PlayerCache(i)(pArmour))
					)
					
					if(armour (= 0)
					(
						itemid = GetPlayerUsingArmourID(i)

						PlayerCache(i)(pArmour) = 0.0
						
						DeleteItem(ItemInfo(itemid)(iUID))
						SetPlayerArmour(i, 0)
					)
				)
  	 		)
			
			PlayerCache(i)(pAFK) --
			
			// G³ówna informacja
			if(PlayerCache(i)(pShowInfoText))
			(
				PlayerCache(i)(pShowInfoText) --

				if(PlayerCache(i)(pShowInfoText) (= 0)
				(
					TextDrawHideForPlayer(i, Text:TextDrawMainInfo(i))
				)
			)
			
			// Informacja o drzwiach
			if(PlayerCache(i)(pShowDoorText))
			(
				PlayerCache(i)(pShowDoorText) --

				if(PlayerCache(i)(pShowDoorText) (= 0)
				(
					PlayerTextDrawHide(i, TextDrawDoorInfo(i))
				)
			)

			// Postrzelony
			if(PlayerCache(i)(pWoundedTime))
			(
				PlayerCache(i)(pWoundedTime) --

				if(PlayerCache(i)(pBW))
				(
					PlayerCache(i)(pWoundedTime) = 0
					PlayerCache(i)(pWoundAnim) = false
				)
				else
				(
					if(!PlayerCache(i)(pWoundAnim))
					(
						ApplyPlayerWound(i, PlayerCache(i)(pWoundedTime), !PlayerCache(i)(pWoundAnim))
					)
					
					if(PlayerCache(i)(pWoundedTime) (= 0)
					(
						hrp_TogglePlayerControllable(i, 1)
						ApplyAnimation(i, PED, getup, 2.0, 0, 1, 1, 0, 0, 1)
						PlayerCache(i)(pWoundedTime) = 0
						PlayerCache(i)(pWoundAnim) = false
					)
				)
			)
			
			// Freeze przy wejœciu
			if(PlayerCache(i)(pDoorFreeze))
			(
				PlayerCache(i)(pDoorFreeze) --
				if(PlayerCache(i)(pDoorFreeze) (= 0)
				(
					PlayerCache(i)(pDoorFreeze) = 0
					TogglePlayerControllable(i, true)
				)
			)
			
			// Czas od ostatniego raportu
			if(PlayerCache(i)(pLastReport))
			(
				PlayerCache(i)(pLastReport) --
				if(PlayerCache(i)(pLastReport) (= 0)
				(
					PlayerCache(i)(pLastReport) = 0
				)
			)

			// Krwawienie
			if(PlayerCache(i)(pBleeding) ) 0)
			(
				PlayerCache(i)(pBleeding)--
				
				// Arczir - wydupcanie
				player_speed = loop_player_speed
				if(player_speed ) 10 && !IsPlayerInAnyVehicle(i))
				(
					GetPlayerHealth(i, PlayerCache(i)(pHealth))
					Float:czy_sie_wyjebie = (-0.09)*PlayerCache(i)(pHealth) + 10
					chance = random(100)
					if(chance (= floatround(czy_sie_wyjebie))
						ApplyAnimation(i, GYMNASIUM, gym_jog_falloff, 4.1, 0, 0, 0, 0, 0)
				)
			)
			
			// Hospitalizacja
			if(PlayerCache(i)(pHospitalization))
			(
				PlayerCache(i)(pHospitalization) --
				
				if(PlayerCache(i)(pBleeding) ) 0)
				(
					PlayerCache(i)(pBleeding) = 0
				)
				
				if(PlayerCache(i)(pHospitalization) ) 60)
				(
					time = floatround(PlayerCache(i)(pHospitalization) / 60)
					format(string, sizeof(string), ~g~Hospitalizacja: ~r~%d m., time)
				)
				else
				(
					format(string, sizeof(string), ~g~Hospitalizacja: ~r~%d s., PlayerCache(i)(pHospitalization))
				)
				GameTextForPlayer(i, string, 1, 1)
				
				bed = PlayerCache(i)(pHospitalBed)
				
				Float:hospitaldistance = 20.0
				if(GetPlayerVirtualWorld(i) == PrisonWorld)
				(
					hospitaldistance = 4.0
				)
				
				if(!IsPlayerInRangeOfPoint(i, hospitaldistance, HospitalBed(bed)(bPosX), HospitalBed(bed)(bPosY), HospitalBed(bed)(bPosZ)))
				(
					SetPlayerPos(i, HospitalBed(bed)(bPosX), HospitalBed(bed)(bPosY), HospitalBed(bed)(bPosZ))
				)
				if(GetPlayerInterior(i) != HospitalBed(bed)(bINT))
				(
					SetPlayerInterior(i, HospitalBed(bed)(bINT))
				)
				if(GetPlayerVirtualWorld(i) != HospitalBed(bed)(bVW))
				(
					SetPlayerVirtualWorld(i, HospitalBed(bed)(bVW))
				)
				
				if(PlayerCache(i)(pHospitalization) (= 0)
				(
					if(PlayerCache(i)(pHospitalCharge) (= PlayerCache(i)(pBankCash))
					(
						PlayerCache(i)(pBankCash) -= PlayerCache(i)(pHospitalCharge)
						PlayerCache(i)(pWounded) = 0
						PlayerCache(i)(pBleeding) = 0
						PlayerCache(i)(pBW) = 0
						hrp_SetPlayerHealth(i, 100.0)

						for(j = 0 j ( 10 j++)
						(
							PlayerDamageCache(i)(j) = false
						)
					)
					else
					(
						ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Na Twoim koncie bankowym nie znajduje siê wystarczaj¹ca iloœæ\nœrodków aby kontynuowaæ hospitalizacjê., OK, )
					)
					
					PlayerCache(i)(pHospitalBed) = 0
					PlayerCache(i)(pHospitalization) = 0
					PlayerCache(i)(pHospitalCharge) = 0
					
					if(GetPlayerVirtualWorld(i) != PrisonWorld)
					(
						hrp_SetPlayerPos(i, 1167.0933,-1324.3550,15.4303)					
						SetPlayerFacingAngle(i, 178.6870)
					)
					else
					(
						hrp_SetPlayerPos(i, 1764.6735,-1544.9320,39.9281)					
						SetPlayerFacingAngle(i, 1.8753)
					)
					SetPlayerInterior(i, 0)
					//SetPlayerVirtualWorld(i, 0)
					SetCameraBehindPlayer(i)
				)
			)
			
			// Sterydy
			if(PlayerCache(i)(pGymNutrient))
			(
				PlayerCache(i)(pGymNutrient) --
				if(PlayerCache(i)(pGymNutrient) == 0)
				(
					PlayerCache(i)(pGymNutrient) = 0
					PlayerCache(i)(pGymFactor) = 0
					SendClientMessage(i, COLOR_DO, ** oddzia³ywanie od¿ywki lub sterydu przesta³o wystêpowaæ w Twoim ciele.**)
				)
			)
			
			// Przegl¹da wnêtrze
			if(PlayerCache(i)(pPreviewTime))
			(
				PlayerCache(i)(pPreviewTime) --
				
				format(string, sizeof(string), ~y~Pozostalo: ~g~%d ~y~sek, PlayerCache(i)(pPreviewTime))
				GameTextForPlayer(i, string, 1000, 3)
				
				if(PlayerCache(i)(pPreviewTime) (= 0)
				(
					hrp_SetPlayerPos(i, PlayerCache(i)(pPosX), PlayerCache(i)(pPosY), PlayerCache(i)(pPosZ))

					SetPlayerInterior(i, PlayerCache(i)(pInt))
					SetPlayerVirtualWorld(i, PlayerCache(i)(pVW))
					
					PlayerCache(i)(pPreviewTime) = 0
				)
			)
			
			// Kopanie robaków
			if(PlayerCache(i)(pPicking) ) 0)
			(
				skip = false
				if(!IsPlayerInRangeOfPoint(i, 50.0, 549.2377, -564.3649, 22.4066))
				(
					skip = true
					PlayerCache(i)(pPicking) = 1
				)
				
				if(anim_id != 368)
				(
					ApplyAnimation(i, COP_AMBIENT, Copbrowse_loop, 4.0, 1, 0, 0, 0, 0, 0)
				)
				
				PlayerCache(i)(pPicking)--
				if(PlayerCache(i)(pPicking) == 0)
				(
					if((GetPlayerEqWeight(i) + ItemTypeInfo(ITEM_WORM)(iTypeWeight)) )= GetPlayerCapacity(i))
					(
						GuiMsg(i, Zabrak³o miejsca w Twoim ekwipunku., 1)
					)
					else
					(
						if(!skip)
						(
							lossworm:
							wormcount = random(10)
							if(wormcount (= 0)
								goto lossworm
							
							GuiMsg(i, Wykopa³eœ kilka robaków, dodano je do Twojego ekwipunku., 0)
							temp(64)
							format(temp, sizeof(temp), Robaki (%d szt.), wormcount)
							CreatePlayerItem(i, temp, ITEM_WORM, wormcount, 0)
							
							ApplyAnimation(i, CARRY, crry_prtial, 4.1, 0, 0, 0, 0, 0)
						)
						else
						(
							GuiMsg(i, Wyszed³eœ poza teren zbierania robaczków, akcja zosta³a anulowana., 0)
						)
						
					)
				)
				
				timeleft(64)
				format(timeleft, sizeof(timeleft), ~y~Pozostaly czas: ~g~%d sek, PlayerCache(i)(pPicking))
				GameTextForPlayer(i, timeleft, 1000, 3)
			)
			
			// £owi rybki
			if(PlayerCache(i)(pFish))
			(
				bool:cancel = false, bool:canUse = false
				cvehID = GetClosestVehicle(i, 10.0)
				if(IsVehicleBoat(cvehID))
					canUse = true
				
				// blint kurwa tutaj
				if(canUse || IsPlayerInRangeOfPoint(i, 15.0, 380.1618, -2096.8606, 7.8359) || IsPlayerInRangeOfPoint(i, 15.0, 526.4686,-1938.0804,2.4405) || IsPlayerInRangeOfPoint(i, 15.0, 561.6442,-1936.8746,2.4405) || IsPlayerInRangeOfPoint(i, 15.0, 544.5582,-1948.4175,3.2605))
				(
	   				// Dodaj punkty za ³owienie
  					if(PlayerCache(i)(pFishing) ( 100)
					(
						Float:last_fishing = PlayerCache(i)(pFishing)
						PlayerCache(i)(pFishing) += 0.0005

						if(floatround(PlayerCache(i)(pFishing), floatround_floor) ) floatround(last_fishing, floatround_floor))
						(
							OnPlayerSkillUp(i, SKILL_FISH)
						)
					)

					if(anim_id != 257)
					(
						ApplyAnimation(i, CAMERA, camstnd_lkabt, 4.1, 0, 0, 0, 1, 0, 1)
					)

					if(!PlayerCache(i)(pFishTaking))
					(
						if(random(85) == 35)
						(
							PlayerCache(i)(pFishTaking) = true
						)
						TextDrawSetString(Text:TextDrawMainInfo(i), Proces polowu ~b~~h~ryb ~w~w toku.~n~Odczekaj kilka chwil na zdobycz.)
						TextDrawHideForPlayer(i, Text:TextDrawMainInfo(i))
					)
					else
					(
						if(random(15) == 5)
						(
							GameTextForPlayer(i, ~w~Ryba ~r~uciekla, 5000, 3)
							PlayerCache(i)(pFishTaking) = false
						)
				   		TextDrawSetString(Text:TextDrawMainInfo(i), ~p~Splawik ~w~sie poruszyl, masz branie.~n~Wciskaj ~g~~k~~PED_FIREWEAPON~~w~, aby ~b~~h~zlowic ~w~zdobycz.)
						TextDrawShowForPlayer(i, Text:TextDrawMainInfo(i))
					)
				)
				else
				(
					gangzone_id = GetCurrentPlayerGangZone(i),
						group_id_fix = GetGroupID(GangZoneInfo(gangzone_id)(gOwner))
					if(GroupData(group_id_fix)(gUID))
					(
						if(GroupData(group_id_fix)(gType) == GROUP_FISHING)
						(
							vehid = GetClosestVehicle(i),
								Float:x, Float:y, Float:z
							GetVehiclePos(vehid, x, y, z)
							
							if(IsPlayerInRangeOfPoint(i, 20, x, y, z))
							(
								model = GetVehicleModel(vehid)
								if(model == 472 || model == 473 || model == 493 || model == 595 || model == 484 || model == 430 || model == 453 || model == 452 || model == 446 || model == 454)
								(
									//git
								) else (
									cancel = true
								)
							)					
							else
							(
								cancel = true
							)
						)
						else
						(
							cancel = true
						)
					)
					else
					(
						cancel = true
					)
				)
				
				if(cancel)
				(
					itemid = GetItemID(PlayerCache(i)(pFishingRodUID))
					
					ItemInfo(itemid)(iUsed) = 0
					PlayerCache(i)(pFishingRodUID) = 0

					PlayerCache(i)(pFish) = false

		   			if(IsPlayerAttachedObjectSlotUsed(i, SLOT_FISHING_ROD))
					(
						RemovePlayerAttachedObject(i, SLOT_FISHING_ROD)
					)
					ApplyAnimation(i, CARRY, crry_prtial, 4.1, 0, 0, 0, 0, 0)
					TextDrawHideForPlayer(i, Text:TextDrawMainInfo(i))
				)
			)
			
			// Blokada biegania i bicia
			if(PlayerCache(i)(pBlock) & BLOCK_RUN || PlayerCache(i)(pCarryBox) != BOX_NONE)
			(
				if(GetPlayerState(i) == PLAYER_STATE_ONFOOT)
				(
					keysa, uda, lra
					GetPlayerKeys(i, keysa, uda, lra)

					if(loop_player_speed ) 1)
					(
						if(!(keysa & KEY_WALK))
						(
							ClearAnimations(i, true)
						)
					)
				)
			)
			
			if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
			(
				vehid = loop_player_vehid
								
	 			// Nieautoryzowane wejœcie do pojazdu
		   		if(PlayerCache(i)(pLastVeh) != vehid)
				(
	 				hrp_Kick(i, -1, Nieautoryzowane wejscie do pojazdu.)
				)
				
				if(CarInfo(vehid)(cGPS))
				(
					if(IsPlayerInGroupType(i, GROUP_POLICE))
					(
		   				UpdatePlayerUnitPositions(i)
					)
				)
				
				Float: health
				GetVehicleHealth(vehid, health)
				
				if(CarInfo(vehid)(cEngineTogged))
				(
					// Odejmij paliwo
	  				speed = loop_player_speed,
					  	Float:last_fuel = CarInfo(vehid)(cFuel)
	  				
					if(speed ( 1)
					(
	   					CarInfo(vehid)(cFuel) -= (CarInfo(vehid)(cFuelType) != TYPE_DIESEL) ? 0.001 : 0.002
					)
					else if(speed )= 1 && speed (= 40)
					(
						CarInfo(vehid)(cFuel) -= (CarInfo(vehid)(cFuelType) != TYPE_DIESEL) ? 0.005 : 0.007
					)
					else if(speed )= 41 && speed (= 80)
					(
						CarInfo(vehid)(cFuel) -= (CarInfo(vehid)(cFuelType) != TYPE_DIESEL) ? 0.008 : 0.010
					)
					else if(speed )= 81 && speed (= 120)
				   	(
						CarInfo(vehid)(cFuel) -= (CarInfo(vehid)(cFuelType) != TYPE_DIESEL) ? 0.010 : 0.015
					)
					else if(speed )= 121 && speed (= 150)
					(
						CarInfo(vehid)(cFuel) -= (CarInfo(vehid)(cFuelType) != TYPE_DIESEL) ? 0.015 : 0.020
					)
					else
					(
						CarInfo(vehid)(cFuel) -= (CarInfo(vehid)(cFuelType) != TYPE_DIESEL) ? 0.022 : 0.026
					)
					
					// Jeœli paliwo spadnie o 1 litr, poka¿ info
	 				if(floatround(CarInfo(vehid)(cFuel), floatround_floor) ( floatround(last_fuel, floatround_floor))
					(
						format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~g~Paliwo: ~y~%.0f/%d L, CarInfo(vehid)(cFuel), GetVehicleMaxFuel(CarInfo(vehid)(cModel)))
						GameTextForPlayer(i, string, 10000, 3)
					)

					// Pobierz pozycje
					Float:x, Float:y, Float:z
					GetVehiclePos(vehid, x, y, z)

					Float:distance = floatsqroot(floatpower(floatabs(floatsub(x, VehiclePos(vehid)(0))), 2)+floatpower(floatabs(floatsub(y,VehiclePos(vehid)(1))),2)+floatpower(floatabs(floatsub(z, VehiclePos(vehid)(2))),2))
					Tick(vehid) += floatround(distance)

					// Pobierz i sprawdŸ dane na temat uszkodzeñ technicznych
					if(health ( CarInfo(vehid)(cHealth))
					(
						hrp_VehicleActionLog(Stan HP pojazdu %s (UID: %d) ulegl zmianie. Kierowca: %s (UID: %d). Stary stan HP: %.0f, nowy stan HP: %.0f, CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(i), PlayerCache(i)(pUID), CarInfo(vehid)(cHealth), health)
					
	 					GetVehicleHealth(vehid, CarInfo(vehid)(cHealth))
	 					OnVehicleSave(vehid) ++
					)

					// Pobierz i sprawdŸ dane na temat uszkodzeñ wizualnych
					panels, doors, lights, tires
					GetVehicleDamageStatus(vehid, panels, doors, lights, tires)
					if(panels ( CarInfo(vehid)(cVisual)(0) || lights ( CarInfo(vehid)(cVisual)(2) || tires ( CarInfo(vehid)(cVisual)(3))
					(
						UpdateVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))
					)
					GetVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))

					// Nalicz przebieg pojazdu
					if(Tick(vehid) )= 110)
					(
						// Jeœli ma pasa¿era w taksówce
						if(PlayerCache(i)(pTaxiPassenger) != INVALID_PLAYER_ID)
						(
							passenger_id = PlayerCache(i)(pTaxiPassenger)
	 						if(PlayerCache(passenger_id)(pCash) ) PlayerCache(passenger_id)(pTaxiPay))
	 						(
	 							PlayerCache(passenger_id)(pTaxiPay) += PlayerCache(passenger_id)(pTaxiPrice)

								format(string, sizeof(string), ~w~Koszt: ~g~$%d, PlayerCache(passenger_id)(pTaxiPay))

								GameTextForPlayer(i, string, 5000, 6)
								GameTextForPlayer(passenger_id, string, 5000, 6)
							)
							else
							(
								GameTextForPlayer(i, ~r~Pasazer nie posiada tyle gotowki, 5000, 6)
								GameTextForPlayer(passenger_id, ~r~Nie posiadasz tyle gotowki, 5000, 6)
							)
						)
	 					Tick(vehid) = false
	 					CarInfo(vehid)(cMileage) += 0.1
	 					
						OnVehicleSave(vehid) ++
					)

					VehiclePos(vehid)(0) = x
					VehiclePos(vehid)(1) = y
					VehiclePos(vehid)(2) = z
 					
					if(CarInfo(vehid)(cHealth) (= 360 || CarInfo(vehid)(cHealth) ( 700 && random(150) == 25)
					(
  						CarInfo(vehid)(cEngineTogged) = false
						ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))

						GameTextForPlayer(i, ~r~Silnik w pojezdzie zgasl ze wzgledu na uszkodzenia techniczne., 5000, 3)
						OnVehicleSave(vehid) += 10
					)
					
					if(CarInfo(vehid)(cFuel) (= 0)
					(
						CarInfo(vehid)(cEngineTogged) = false
						ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))

						GameTextForPlayer(i, ~r~Silnik w pojezdzie zgasl ze wzgledu na brak paliwa., 5000, 3)
						OnVehicleSave(vehid) += 10
					)
 					
 					if(CarInfo(vehid)(cTowedVeh) != INVALID_VEHICLE_ID)
 					(
					 	if(!IsTrailerAttachedToVehicle(vehid))
 						(
							CarInfo(vehid)(cTowedVeh) = INVALID_VEHICLE_ID
						)
 					)
 					
 					// Anty SpeedHack
 					if(speed )= GetVehicleMaxSpeed(vehid) + 60)
 					(
 						format(string, sizeof(string), SpeedHack (speed: %d km/h, pojazd: %s)., loop_player_speed, CarInfo(vehid)(cName))
						hrp_Kick(i, -1, string)
						continue
 					)
 					
 					// Anty tuning
					for (j = 0 j ( 14 ++j)
			   		(
						componentid = GetVehicleComponentInSlot(vehid, j)
			  			if (componentid != 0 && componentid != (CarInfo(vehid)(cComponent)(j) + 999))
						(
							hrp_Ban(i, -1, Proba stuningowania pojazdu., 0)
							SetVehicleToRespawn(vehid)
							continue
						)
					)
					
					if(OnVehicleSave(vehid) )= 30)
					(
						SaveVehicle(vehid, SAVE_VEH_COUNT)
					)
					
					// Jeœli ma lekcjê jazdy
					if(PlayerCache(i)(pDrivingLesson))
					(
						if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
						(
							// SprawdŸ czy siedzi w pojeŸdzie grupowym
							group_id_fix = GetGroupID(CarInfo(vehid)(cOwner))
							if(GroupData(group_id_fix)(gType) == GROUP_DRIVING)
							(
								PlayerCache(i)(pDrivingLesson) --
								if(PlayerCache(i)(pDrivingLesson) ) 60)
								(
		 							format(string, sizeof(string), ~w~Pozostaly czas: ~y~%d ~w~min, PlayerCache(i)(pDrivingLesson)/60)
									GameTextForPlayer(i, string, 1000, 6)
				  				)
								else
								(
									format(string, sizeof(string), ~w~Pozostaly czas: ~y~%d ~w~sec, PlayerCache(i)(pDrivingLesson))
									GameTextForPlayer(i, string, 1000, 6)
								)

								if(PlayerCache(i)(pDrivingLesson) (= 0)
								(
									PlayerCache(i)(pDrivingLesson) = 0
								)
							)
						)
					)
				)
				else
				(
					if(health ( CarInfo(vehid)(cHealth))
					(
						if(CarInfo(vehid)(cHealth) ( 350)
						(
							CarInfo(vehid)(cHealth) = 350.0
						)
						SetVehicleHealth(vehid, CarInfo(vehid)(cHealth))
					)
				)
			)
			
			// Dbanie o amunicjê spraya
			
			if(PlayerCache(i)(pScouring))
			(
				objectid = GetClosestObject(i, 5.0)
				modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID)
				
				if(modelid != 18661)
				(
					ResetPlayerWeapons(i)
					PlayerCache(i)(pScouring) = false
					PlayerCache(i)(pScouredID) = INVALID_OBJECT_ID
					GuiMsg(i, Za bardzo oddali³eœ siê od taga!\nPraca zosta³a przerwana., 0)
				)
				
				weapid, ammo
				GetPlayerWeaponData(i, 9, weapid, ammo)
				if(weapid != 41)
				(
					ResetPlayerWeapons(i)
					PlayerCache(i)(pScouring) = false
					PlayerCache(i)(pScouredID) = INVALID_OBJECT_ID
					GuiMsg(i, Coœ kombinujesz, musisz mieæ spray w rêku!\nPraca zosta³a przerwana., 0)
				)
				
				if(ammo ( 5)
				(
					deletingID = PlayerCache(i)(pScouredID)
					PlayerCache(i)(pScouring) = false
					ResetPlayerWeapons(i)
					
					hrp_DeleteObject(deletingID)
					
					money = random(5) + 1
					
					hrp_GivePlayerMoney(i, money)
					saveUID = PlayerCache(i)(pUID)
					
					PlayerCache(i)(pScouredID) = INVALID_OBJECT_ID
					
					blint_SaveCash(saveUID, i)
					msg(128)
					format(msg, sizeof(msg),Usun¹³eœ tag!\nNa Twoje konto dodano $%d!, money)
					GuiMsg(i, msg, 0)
					
					PlayerCache(i)(pDailyIncome) += money
				)
			)
			
			if(PlayerCache(i)(pTagging))
			(
				object_id = PlayerCache(i)(pTagging), object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)
				if(WeaponCache(i)(WEAPON_FUNC)(pWeaponUID))
				(
					if(WeaponCache(i)(WEAPON_FUNC)(pWeaponID) == 41)
					(
						GetDynamicObjectPos(object_id, PosX, PosY, PosZ)
						ammo = GetPlayerWeaponAmmo(i, WeaponCache(i)(WEAPON_FUNC)(pWeaponID))
						
						data(512), tag_text(256)
						mysql_query_format(SELECT tag_text FROM hrp_tags WHERE tag_objectuid = %d, object_uid)
						
						mysql_store_result()
						if(mysql_fetch_row(data, |))
						(
							sscanf(data, p(|)s(255), tag_text)
						)
						mysql_free_result()
						
						if(strlen(tag_text) ) 0)
						(
							visible = floatround((1000 - ammo) / (1000 / strlen(tag_text)))
							format(string, sizeof(string), )
							strmid(string, tag_text, 0, visible, sizeof(string))
							
							SetDynamicObjectMaterialText(object_id, 0, string, OBJECT_MATERIAL_SIZE_256x128, Fonts(PlayerCache(i)(pTaggingFont)), FontSizes(PlayerCache(i)(pTaggingSize)), 1, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER)
							
							if(ammo ( 5)
							(
								fakeOnPlayerSelectObject(i, object_id, 18661, PosX, PosY, PosZ)
			
								TextDrawSetString(Text:TextDrawMainInfo(i), Ustaw tag w odpowiednim miejscu.~n~Pamietaj ze masz tylko jedna szanse na ustawienie pozycji.)
								TextDrawShowForPlayer(i, Text:TextDrawMainInfo(i))
								PlayerCache(i)(pShowInfoText) = 8
								
								itemid = GetItemID(WeaponCache(i)(WEAPON_FUNC)(pWeaponUID))
								DeleteItem(ItemInfo(itemid)(iUID))
							
								//SetPlayerAmmo(i, WeaponCache(i)(WEAPON_FUNC)(pWeaponID), 0)
								ResetPlayerWeapons(i)
								GivePlayerWeapon(i, WeaponCache(i)(WEAPON_MAIN)(pWeaponID), WeaponCache(i)(WEAPON_MAIN)(pLastAmmo)) 
								GivePlayerWeapon(i, WeaponCache(i)(WEAPON_SIDE)(pWeaponID), WeaponCache(i)(WEAPON_SIDE)(pLastAmmo))
		
								WeaponCache(i)(WEAPON_FUNC)(pWeaponUID) = 0
								WeaponCache(i)(WEAPON_FUNC)(pWeaponID) = 0
								WeaponCache(i)(WEAPON_FUNC)(pWeaponAmmo) = 0
								WeaponCache(i)(WEAPON_FUNC)(pLastAmmo) = 0
								WeaponCache(i)(WEAPON_FUNC)(pShot) = false
								
								if(IsPlayerAttachedObjectSlotUsed(i, SLOT_WEAPON_FUNC))
								(
									RemovePlayerAttachedObject(i, SLOT_WEAPON_FUNC)
								)
								
								PlayerCache(i)(pTagging) = 0
								PlayerCache(i)(pTaggingFont) = 0
								PlayerCache(i)(pTaggingSize) = 0
							)
						)
					)
				)
			)
			
			
			// Zapis amunicji i chowanie broni po wyczerpaniu.
			
			if(loop_player_weapon ) 0 && !PlayerCache(i)(pTagging))
			(
				wid = loop_player_weapon,
					j = GetWeaponClass(wid) //class
				if(WeaponCache(i)(j)(pWeaponUID))
				(
					if(WeaponCache(i)(j)(pWeaponID) ) 15 && WeaponCache(i)(j)(pWeaponID) ( 44)
					(
						ammo = GetPlayerWeaponAmmo(i, WeaponCache(i)(j)(pWeaponID))
						if(ammo ( WeaponCache(i)(j)(pWeaponAmmo))
						(
							WeaponCache(i)(j)(pWeaponAmmo) = ammo
						)
						
						if(ammo (= 0)
						(
							WeaponCache(i)(j)(pEquipped) = false
							
							itemid = GetItemID(WeaponCache(i)(j)(pWeaponUID))
							format(string, sizeof(string), UPDATE hrp_items SET item_used = 0, item_value2 = 0 WHERE item_uid = %d LIMIT 1, WeaponCache(i)(j)(pWeaponUID))
							mysql_query(string)

							SetPlayerAmmo(i, WeaponCache(i)(j)(pWeaponID), 0)

							ItemInfo(itemid)(iUsed) = 0
							ItemInfo(itemid)(iValue2) = 0
							
							WeaponCache(i)(j)(pWeaponUID) = 0
							WeaponCache(i)(j)(pWeaponID) = 0
							WeaponCache(i)(j)(pWeaponAmmo) = 0
							WeaponCache(i)(j)(pLastAmmo) = 0
							WeaponCache(i)(j)(pShot) = false
							
							slot = -1
							if(j == 0) slot = SLOT_WEAPON_MAIN
							if(j == 1) slot = SLOT_WEAPON_SIDE
							if(j == 2) slot = SLOT_WEAPON_FUNC
							
							if(IsPlayerAttachedObjectSlotUsed(i, slot))
							(
								RemovePlayerAttachedObject(i, slot)
							)
						)
					)
				)
			)

			// Brutally Wounded (bw)
			if(PlayerCache(i)(pBW))
			(
				Float:temp_h = 0.0
				GetPlayerHealth(i, temp_h)
				if(temp_h ( 5.0)
				(
					hrp_SetPlayerHealth(i, 20.0)
				)
				PlayerCache(i)(pBW) --
				if(PlayerCache(i)(pBW) ) 1*60)
				(
					format(string, sizeof(string), ~w~Koniec ~r~BW~w~: ~g~%d ~w~min., PlayerCache(i)(pBW)/60)
					GameTextForPlayer(i, string, 1000, 1)
				)
				else
				(
					format(string, sizeof(string), ~w~Koniec ~r~BW~w~: ~g~%d ~w~sek., PlayerCache(i)(pBW))
					GameTextForPlayer(i, string, 1000, 1)
				)
				if(PlayerCache(i)(pBW) (= 0)
				(
					PlayerCache(i)(pBW) = 0
					PlayerCache(i)(pWounded) = 1

					PlayerCache(i)(pKiller) = 0
	   			 	PlayerCache(i)(pKillerWeapon) = 0

					ApplyAnimation(i, Attractors, Stepsit_out, 4.0, 0, 0, 0, 0, 0, 1)
 					hrp_TogglePlayerControllable(i, 1)

					SetCameraBehindPlayer(i)
					hrp_SetPlayerHealth(i, 20)

					ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Ockn¹³eœ siê, jednak nie jesteœ wystarczaj¹co na si³ach.\nTwój stan zdrowia nie jest idealny - mo¿e udaj siê do szpitala?, OK, )

					SetPlayerDrunkLevel(i, 5000)
				)
			)
			
			// AdminJail (aj)
			if(PlayerCache(i)(pAJ))
			(
				if(!IsPlayerInRangeOfPoint(i, 5.0, 154.1221, -1951.9156, 47.8750))
				(
					hrp_SetPlayerPos(i, 154.1221, -1951.9156, 47.8750)
				   	SetPlayerInterior(i, 0)
					SetPlayerVirtualWorld(i, i + 1000)
				)
				
				PlayerCache(i)(pAJ) --
				if(PlayerCache(i)(pAJ) ) 60)
				(
					format(string, sizeof(string), ~w~Koniec ~r~AJ~w~: ~g~%d ~w~min., PlayerCache(i)(pAJ)/60)
					GameTextForPlayer(i, string, 1000, 1)
				)
				else
				(
					format(string, sizeof(string), ~w~Koniec ~r~AJ~w~: ~g~%d ~w~sek., PlayerCache(i)(pAJ))
					GameTextForPlayer(i, string, 1000, 1)
				)
				if(PlayerCache(i)(pAJ) (= 0)
				(
					PlayerCache(i)(pAJ) = 0
					SetPlayerSpawn(i)
					mysql_query_format(UPDATE hrp_punishlogs SET punish_end = %d WHERE punish_owneruid = %d AND punish_type = %d, gettime(), PlayerCache(i)(pUID), PUNISH_AJ)
				)
			)
			
			
			//Areszt
			if(PlayerCache(i)(pArrest))
			(
				if(PlayerCache(i)(pArrestTime) ) 0)
				(
					if(PlayerCache(i)(pArrestTime) == 1)
					(
						ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twój wyrok dobieg³ koñca.\nTeraz mo¿esz opuœciæ areszt podchodz¹c do wyjœcia i u¿ywaj¹c komendy /opusc, b¹dŸ pozostaæ i graæ dalej tutaj.\nMi³ej gry!, OK, )
					)
					PlayerCache(i)(pArrestTime) --
				)
			)
			
			// Lakierowanie pojazdu
			if(PlayerCache(i)(pSprayVeh) != INVALID_VEHICLE_ID)
			(
				keysa, uda, lra, vehid = PlayerCache(i)(pSprayVeh), weapon = loop_player_weapon
				GetPlayerKeys(i, keysa, uda, lra)
				if(keysa & KEY_FIRE && weapon == 41 && GetPlayerState(i) == PLAYER_STATE_ONFOOT)
				(
					Float:VehX, Float:VehY, Float:VehZ
					GetVehiclePos(vehid, VehX, VehY, VehZ)
					
					if(IsPlayerInRangeOfPoint(i, 4.0, VehX, VehY, VehZ))
					(
						if(IsPlayerFacingVehicle(i, vehid))
						(
							if(anim_id == 1167 || anim_id == 640 || anim_id == 1161 || anim_id == 1162 || anim_id == 1163 || anim_id == 1160)
							(
		  						PlayerCache(i)(pSprayTime) --

								format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~g~Pozostalo: ~w~%d sekund., PlayerCache(i)(pSprayTime))
		   						GameTextForPlayer(i, string, 1000, 3)

								if(PlayerCache(i)(pSprayTime) (= 0)
				 				(
									if(PlayerCache(i)(pSprayType) == 1)
				 					(
			  							color1 = PlayerCache(i)(pSprayColor)(0), color2 = PlayerCache(i)(pSprayColor)(1)
										ChangeVehicleColor(vehid, color1, color2)

										CarInfo(vehid)(cColor1) = color1
			  							CarInfo(vehid)(cColor2) = color2
							  			SaveVehicle(vehid, SAVE_VEH_ACCESS)

										ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pojazd zosta³ pomyœlnie przemalowany., OK, )
										hrp_VehicleActionLog(Kolory pojazdu %s (UID: %d) zmienily sie. Nowe kolory: %d/%d., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), color1, color2)
									)
									else if(PlayerCache(i)(pSprayType) == 2)
									(
										paintjob_id = PlayerCache(i)(pSprayColor)(0)
										ChangeVehiclePaintjob(vehid, paintjob_id)

										CarInfo(vehid)(cPaintJob) = paintjob_id
										SaveVehicle(vehid, SAVE_VEH_ACCESS)

										ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pojazd zosta³ pomyœlnie przemalowany., OK, )
										hrp_VehicleActionLog(PaintJob pojazdu %s (UID: %d) zmienil sie. Nowy PaintJob: %d., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), paintjob_id)
									)
									PlayerCache(i)(pSprayVeh) = INVALID_VEHICLE_ID

									PlayerCache(i)(pSprayColor)(0) = -1
									PlayerCache(i)(pSprayColor)(1) = -1

									PlayerCache(i)(pSprayTime) = 0
									PlayerCache(i)(pSprayType) = 0
								)
							)
						)
						else
						(
							GameTextForPlayer(i, ~r~Psikaj w strone pojazdu., 1000, 3)
						)
					)
					else
					(
						GameTextForPlayer(i, ~r~Jestes zbyt daleko od pojazdu., 1000, 3)
					)
				)
			)
						
			// Wymiana opony
			if(PlayerCache(i)(pTireVeh) != INVALID_VEHICLE_ID)
			(
				vehid = PlayerCache(i)(pTireVeh), Float:VehX, Float:VehY, Float:VehZ
				GetVehiclePos(vehid, VehX, VehY, VehZ)
				if(IsPlayerInRangeOfPoint(i, 4.0, VehX, VehY, VehZ))
				(
					if(!CarInfo(vehid)(cEngineTogged))
					(
						PlayerCache(i)(pTireTime) --
						
						format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~g~Pozostalo: ~w~%d sekund., PlayerCache(i)(pTireTime))
						GameTextForPlayer(i, string, 1000, 3)
						
						if(PlayerCache(i)(pTireTime) (= 0)
						(
							CarInfo(vehid)(cVisual)(3) = 0
							UpdateVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))
							
							SaveVehicle(vehid, SAVE_VEH_COUNT)
	  						ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wymiana opony dobieg³a koñca., OK, )

							PlayerCache(i)(pTireVeh) = INVALID_VEHICLE_ID
							PlayerCache(i)(pTireTime) = 0
							
							hrp_VehicleActionLog(Pojazd %s (UID: %d) mial wymieniona opone przez gracza %s (UID: %d)., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(i), PlayerCache(i)(pUID))
						)
					)
					else
					(
						GameTextForPlayer(i, ~r~Silnik pojazdu musi byc zgaszony!, 1000, 3)
					)
				)				
				else
				(
					GameTextForPlayer(i, ~r~Jestes zbyt daleko od pojazdu., 1000, 3)
				)
			)
			
			// Pompowanie opon
			if(PlayerCache(i)(pOPumpItem))
			(
				itemid = PlayerCache(i)(pOPumpItem)
				if(ItemInfo(itemid)(iUID))
				(
				
					object_id = GetClosestObject(i)
					if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_AIR_PUMP)
					(
						GameTextForPlayer(i, ~r~Musisz staæ przy kompresorze aby pompowaæ oponê!, 1000, 3)
					)
					else
					(
						PlayerCache(i)(pOPumpTime) --
							
						format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~g~Pozostalo: ~w~%d sekund., PlayerCache(i)(pOPumpTime))
						GameTextForPlayer(i, string, 1000, 3)
						
						if(PlayerCache(i)(pOPumpTime) (= 0)
						(
							ItemInfo(itemid)(iUsed) = 0
							ItemInfo(itemid)(iValue1) = 0
							format(string, sizeof(string), Kolo zapasowe)
							strmid(ItemInfo(itemid)(iName), string, 0, strlen(string), 32)
							
							mysql_query_format(UPDATE hrp_items SET item_name = %s, item_used = 0, item_value1 = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID))
									
							ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pompowanie opon dobieg³o koñca., OK, )

							PlayerCache(i)(pOPumpItem) = 0
							PlayerCache(i)(pOPumpTime) = 0
						)
					)
				)
			)
			
			// Pompowanie opon
			if(PlayerCache(i)(pPumpVeh) != INVALID_VEHICLE_ID)
			(
				vehid = PlayerCache(i)(pPumpVeh), Float:VehX, Float:VehY, Float:VehZ
				GetVehiclePos(vehid, VehX, VehY, VehZ)
				if(IsPlayerInRangeOfPoint(i, 4.0, VehX, VehY, VehZ))
				(
					if(!CarInfo(vehid)(cEngineTogged))
					(
						PlayerCache(i)(pPumpTime) --
						
						format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~g~Pozostalo: ~w~%d sekund., PlayerCache(i)(pPumpTime))
						GameTextForPlayer(i, string, 1000, 3)
						
						if(PlayerCache(i)(pPumpTime) (= 0)
						(
							CarInfo(vehid)(cVisual)(3) = 0
							UpdateVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))
							
							SaveVehicle(vehid, SAVE_VEH_COUNT)
	  						ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pompowanie opon dobieg³o koñca., OK, )

							PlayerCache(i)(pPumpVeh) = INVALID_VEHICLE_ID
							PlayerCache(i)(pPumpTime) = 0
						)
					)
					else
					(
						GameTextForPlayer(i, ~r~Silnik pojazdu musi byc zgaszony!, 1000, 3)
					)
				)				
				else
				(
					GameTextForPlayer(i, ~r~Jestes zbyt daleko od pojazdu., 1000, 3)
				)
			)
			
			// Naprawa pojazdu
			if(PlayerCache(i)(pRepairVeh) != INVALID_VEHICLE_ID)
			(
   				vehid = PlayerCache(i)(pRepairVeh), type = PlayerCache(i)(pRepairType), Float:VehX, Float:VehY, Float:VehZ, Float:current_health
				
				GetVehicleHealth(vehid, current_health)
				GetVehiclePos(vehid, VehX, VehY, VehZ)
				
				if(IsPlayerInRangeOfPoint(i, 4.0, VehX, VehY, VehZ))
				(
					if(!CarInfo(vehid)(cEngineTogged))
					(
						PlayerCache(i)(pRepairTime) --

						format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~g~Pozostalo: ~w~%d sekund., PlayerCache(i)(pRepairTime))
	  					GameTextForPlayer(i, string, 1000, 3)

	  					if(PlayerCache(i)(pRepairTime) (= 0)
	  					(
							if(type == REPAIR_STANDARD)
							(
								CarInfo(vehid)(cVisual)(0) = 0
								CarInfo(vehid)(cVisual)(1) = 0
								CarInfo(vehid)(cVisual)(2) = 0
								
								CarInfo(vehid)(cCarfax) += 1000 - current_health

								CarInfo(vehid)(cHealth) = 1000

								//RepairVehicle(vehid)
								UpdateVehicleDamageStatus(vehid, 0, 0, 0, CarInfo(vehid)(cVisual)(3))
								
								SetVehicleHealth(vehid, 1000)

								SaveVehicle(vehid, SAVE_VEH_COUNT)
								ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Naprawa pojazdu dobieg³a koñca., OK, )

								PlayerCache(i)(pRepairVeh) = INVALID_VEHICLE_ID
								PlayerCache(i)(pRepairTime) = 0
								
								getVehicleRemoves(vehid)
								
								hrp_VehicleActionLog(Pojazd %s (UID: %d) zostal naprawiony przez gracza %s (UID: %d)., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(i), PlayerCache(i)(pUID))
							)
							if(type == REPAIR_ENGINE)
							(
								CarInfo(vehid)(cMileage) = 0
								CarInfo(vehid)(cCarfax) = (CarInfo(vehid)(cCarfax) - 7500.0 ( 0)? 0.0 : (CarInfo(vehid)(cCarfax) - 7500.0)
								
								CarInfo(vehid)(cVisual)(0) = 0
								CarInfo(vehid)(cVisual)(1) = 0
								CarInfo(vehid)(cVisual)(2) = 0
								CarInfo(vehid)(cHealth) = 1000

								UpdateVehicleDamageStatus(vehid, 0, 0, 0, CarInfo(vehid)(cVisual)(3))								
								SetVehicleHealth(vehid, 1000)

								SaveVehicle(vehid, SAVE_VEH_COUNT)
								ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wymiana silnika dobieg³a koñca., OK, )

								PlayerCache(i)(pRepairVeh) = INVALID_VEHICLE_ID
								PlayerCache(i)(pRepairType) = 0
								PlayerCache(i)(pRepairTime) = 0
								
								hrp_VehicleActionLog(Pojazd %s (UID: %d) zostal naprawiony przez gracza %s (UID: %d) (Wymiana silnika)., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(i), PlayerCache(i)(pUID))
							)
							if(type == REPAIR_BODY)
							(
								CarInfo(vehid)(cCarfax) = (CarInfo(vehid)(cCarfax) - 10000.0 ( 0)? 0.0: (CarInfo(vehid)(cCarfax) - 10000)
								
								CarInfo(vehid)(cVisual)(0) = 0
								CarInfo(vehid)(cVisual)(1) = 0
								CarInfo(vehid)(cVisual)(2) = 0

								UpdateVehicleDamageStatus(vehid, 0, 0, 0, CarInfo(vehid)(cVisual)(3))

								SaveVehicle(vehid, SAVE_VEH_COUNT)
								ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Naprawa karoserii dobieg³a koñca., OK, )

								PlayerCache(i)(pRepairVeh) = INVALID_VEHICLE_ID
								PlayerCache(i)(pRepairType) = 0
								PlayerCache(i)(pRepairTime) = 0
								
								hrp_VehicleActionLog(Pojazd %s (UID: %d) zostal naprawiony przez gracza %s (UID: %d) (Naprawa karoserii)., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(i), PlayerCache(i)(pUID))
							)
							if(type == REPAIR_FLUIDS)
							(
								CarInfo(vehid)(cCarfax) = (CarInfo(vehid)(cCarfax) - 150.0 ( 0)? 0.0 : (CarInfo(vehid)(cCarfax) - 150)
								
								SaveVehicle(vehid, SAVE_VEH_COUNT)
								ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wymiana p³ynów dobieg³a koñca., OK, )

								PlayerCache(i)(pRepairVeh) = INVALID_VEHICLE_ID
								PlayerCache(i)(pRepairType) = 0
								PlayerCache(i)(pRepairTime) = 0
								
								hrp_VehicleActionLog(Pojazd %s (UID: %d) zostal naprawiony przez gracza %s (UID: %d) (Wymiana plynow)., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(i), PlayerCache(i)(pUID))
							)
							if(type == REPAIR_FILTER)
							(
								CarInfo(vehid)(cCarfax) = (CarInfo(vehid)(cCarfax) - 160.0 ( 0)? 0.0 : (CarInfo(vehid)(cCarfax) - 160)

								SaveVehicle(vehid, SAVE_VEH_COUNT)
								ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wymiana filtra dobieg³a koñca., OK, )

								PlayerCache(i)(pRepairVeh) = INVALID_VEHICLE_ID
								PlayerCache(i)(pRepairType) = 0
								PlayerCache(i)(pRepairTime) = 0
								
								hrp_VehicleActionLog(Pojazd %s (UID: %d) zostal naprawiony przez gracza %s (UID: %d) (Wymiana filtra)., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(i), PlayerCache(i)(pUID))
							)
							if(type == REPAIR_COOLER)
							(
								CarInfo(vehid)(cCarfax) = (CarInfo(vehid)(cCarfax) - 400.0 ( 0)? 0.0 : (CarInfo(vehid)(cCarfax) - 400)
								
								SaveVehicle(vehid, SAVE_VEH_COUNT)
								ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wymiana ch³odnicy dobieg³a koñca., OK, )

								PlayerCache(i)(pRepairVeh) = INVALID_VEHICLE_ID
								PlayerCache(i)(pRepairType) = 0
								PlayerCache(i)(pRepairTime) = 0
								
								hrp_VehicleActionLog(Pojazd %s (UID: %d) zostal naprawiony przez gracza %s (UID: %d) (Wymiana chlodnicy)., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(i), PlayerCache(i)(pUID))
							)
						)
					)
					else
					(
						GameTextForPlayer(i, ~r~Silnik pojazdu musi byc zgaszony!, 1000, 3)
					)
				)
			)
			
			// Montowanie czêœci
			if(PlayerCache(i)(pMontageVeh) != INVALID_VEHICLE_ID)
			(
				vehid = PlayerCache(i)(pMontageVeh), Float:VehX, Float:VehY, Float:VehZ
				GetVehiclePos(vehid, VehX, VehY, VehZ)
				if(IsPlayerInRangeOfPoint(i, 4.0, VehX, VehY, VehZ))
				(
					PlayerCache(i)(pMontageTime) --
					
   					format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~g~Pozostalo: ~w~%d sekund., PlayerCache(i)(pMontageTime))
  					GameTextForPlayer(i, string, 1000, 3)
  					
  					if(PlayerCache(i)(pMontageTime) (= 0)
  					(
  						itemid = PlayerCache(i)(pMontageItem)
  						
  						// Komponent tuningu
  						if(ItemInfo(itemid)(iType) == ITEM_TUNING)
  						(
	  						format(string, sizeof(string), UPDATE hrp_items SET item_place = -1, item_owner = 0, item_vehuid = %d WHERE item_uid = %d LIMIT 1, CarInfo(vehid)(cUID), ItemInfo(itemid)(iUID))
	  						mysql_query(string)

	  						hrp_AddVehicleComponent(vehid, ItemInfo(itemid)(iValue1))

							hrp_VehicleActionLog(W pojezdzie %s (UID: %d) zamontowano komponent %s (UID: %d)., CarInfo(vehid)(cName), CarInfo(vehid)(cUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID))

							ItemInfo(itemid)(iUID) = 0

							ItemInfo(itemid)(iValue1) = 0
							ItemInfo(itemid)(iValue2) = 0
							ItemInfo(itemid)(iType) = 0

							ItemInfo(itemid)(iPlace) = 0
							ItemInfo(itemid)(iOwner) = 0

							ItemInfo(itemid)(iUsed) = 0
							ItemInfo(itemid)(iChecked) = false
							
							Itter_Remove(Items, itemid)
						)
						
						// tuning mechaniczny
						if(ItemInfo(itemid)(iType) == ITEM_TUNEPART)
						(
							format(string, sizeof(string), UPDATE hrp_items SET item_place = %i, item_owner = 0, item_vehuid = %d WHERE item_uid = %d LIMIT 1,PLACE_VEHICLE, CarInfo(vehid)(cUID), ItemInfo(itemid)(iUID))
	  						mysql_query(string)
							
							ItemInfo(itemid)(iUID) = 0

							ItemInfo(itemid)(iValue1) = 0
							ItemInfo(itemid)(iValue2) = 0
							ItemInfo(itemid)(iType) = 0

							ItemInfo(itemid)(iPlace) = 0
							ItemInfo(itemid)(iOwner) = 0

							ItemInfo(itemid)(iUsed) = 0
							ItemInfo(itemid)(iChecked) = false
							
							Itter_Remove(Items, itemid)
							
							LoadVehicleTune(vehid)		//przeladuj tuning pojazdu
						)
						
						// Akcesoria (alarm, immobiliser, sprzêt audio)
						if(ItemInfo(itemid)(iType) == ITEM_ACCESS)
						(
							CarInfo(vehid)(cAccess) += ItemInfo(itemid)(iValue1)
							SaveVehicle(vehid, SAVE_VEH_ACCESS)
							
							DeleteItem(ItemInfo(itemid)(iUID))
						)
						
   						ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Monta¿ nowej czêœci dobieg³ koñca., OK, )

						PlayerCache(i)(pMontageVeh) = INVALID_VEHICLE_ID
						PlayerCache(i)(pMontageTime) = 0

						PlayerCache(i)(pMontageItem) = 0
  					)
				)
			)
			
			// zwi¹zany
			if(PlayerCache(i)(pRoped) != INVALID_PLAYER_ID)
			(
				cuffed_to = PlayerCache(i)(pRoped)
				
				Float:x, Float:y, Float:z,
					interior = GetPlayerInterior(cuffed_to), virtual_world = GetPlayerVirtualWorld(cuffed_to)
				
				GetPlayerPos(cuffed_to, x, y, z)
				
				if(!IsPlayerInRangeOfPoint(i, 5.0, x, y, z))
				(
					if(IsPlayerInAnyVehicle(i))
					(
						RemovePlayerFromVehicle(i)
						hrp_TogglePlayerControllable(i, 1)
					)
					hrp_SetPlayerPos(i, x + 1, y, z)
					
					SetPlayerInterior(i, interior)
					SetPlayerVirtualWorld(i, virtual_world)
				)
				else if(GetPlayerState(cuffed_to) == PLAYER_STATE_DRIVER)
				(
					vehid = GetPlayerVehicleID(cuffed_to)
					if(IsSeatFree(vehid, 2))
					(
						PlayerCache(i)(pLastVeh) = vehid
						
						PutPlayerInVehicle(i, vehid, 2)
						hrp_TogglePlayerControllable(i, 0)
					)
					else if(IsSeatFree(vehid, 3))
					(
						PlayerCache(i)(pLastVeh) = vehid
						
						PutPlayerInVehicle(i, vehid, 3)
						hrp_TogglePlayerControllable(i, 0)
					)
					else
					(
						GameTextForPlayer(cuffed_to, ~r~Brak wolnego miejsca w pojezdzie., 4000, 3)
					)
				)
			)
			
			if(PlayerCache(i)(pCuffed) != INVALID_PLAYER_ID)
			(
				cuffed_to = PlayerCache(i)(pCuffed)
				
				Float:x, Float:y, Float:z,
					interior = GetPlayerInterior(cuffed_to), virtual_world = GetPlayerVirtualWorld(cuffed_to)
					
				GetPlayerPos(cuffed_to, x, y, z)
				
				if(!IsPlayerInRangeOfPoint(i, 5.0, x, y, z))
				(
					if(IsPlayerInAnyVehicle(i))
					(
						RemovePlayerFromVehicle(i)
						hrp_TogglePlayerControllable(i, 1)
					)
					hrp_SetPlayerPos(i, x + 1, y, z)
					
					SetPlayerInterior(i, interior)
					SetPlayerVirtualWorld(i, virtual_world)
				)
				else if(GetPlayerState(cuffed_to) == PLAYER_STATE_DRIVER)
				(
					vehid = GetPlayerVehicleID(cuffed_to)
					if(IsSeatFree(vehid, 2))
					(
						PlayerCache(i)(pLastVeh) = vehid
						
						PutPlayerInVehicle(i, vehid, 2)
						hrp_TogglePlayerControllable(i, 0)
					)
					else if(IsSeatFree(vehid, 3))
					(
						PlayerCache(i)(pLastVeh) = vehid
						
						PutPlayerInVehicle(i, vehid, 3)
						hrp_TogglePlayerControllable(i, 0)
					)
					else
					(
						GameTextForPlayer(cuffed_to, ~r~Brak wolnego miejsca w pojezdzie., 4000, 3)
					)
				)
			)
			
			// Zakuty gracz
			if(PlayerCache(i)(pCuffedStill) != INVALID_PLAYER_ID)
			(
				hrp_TogglePlayerControllable(i, 0)
			)
			
			// Przeszukiwanie gracza
			if(PlayerCache(i)(pSearches) != INVALID_PLAYER_ID)
			(
				searched_player = PlayerCache(i)(pSearches)
				if(PlayerToPlayer(5.0, i, searched_player))
				(
					PlayerCache(i)(pSearchTime) --

					GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~g~Trwa przeszukiwanie..., 1000, 3)
					if(PlayerCache(i)(pSearchTime) (= 0)
					(
						ListPlayerItemsForPlayer(i, searched_player)

						format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~n~~n~~y~Gotowka gracza ~r~%s~y~: ~g~$%d~y~., PlayerName(searched_player), PlayerCache(searched_player)(pCash))
						GameTextForPlayer(i, string, 6000, 3)

						PlayerCache(i)(pSearches) = INVALID_PLAYER_ID
						PlayerCache(i)(pSearchTime) = 0
					)
				)
				else
				(
					PlayerCache(i)(pSearches) = INVALID_PLAYER_ID
					PlayerCache(i)(pSearchTime) = 0
					
					ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Przeszukiwanie gracza zosta³o anulowane.\nPowód: Gracz znajduje siê zbyt daleko od Ciebie., OK, )

					GameTextForPlayer(searched_player, ~r~~h~Przeszukiwanie zostalo przerwane., 4500, 3)
				)
			)
			
			// Anty AirBreak
			if(PlayerCache(i)(pGotAirBrkPos))
			(
				if(PlayerCache(i)(pAdmin) == 0)
				(
					if(GetPlayerSurfingVehicleID(i) == INVALID_VEHICLE_ID && PlayerCache(i)(pSpectate) == INVALID_PLAYER_ID && PlayerCache(i)(pBusRide) == false)
					(
						distance = floatround(GetPlayerDistanceFromPoint(i, PlayerCache(i)(pCheatPosX), PlayerCache(i)(pCheatPosY), PlayerCache(i)(pCheatPosZ)))
						if(distance )= 35 && distance ( 250 && loop_player_speed ( 30)
						(
							PlayerCache(i)(pAirBrkWarns) ++
							if(PlayerCache(i)(pAirBrkWarns) )= 2)
							(
		 						ShowAdminLog(~r~(cheat) ~w~Gracz %s (ID: %d, Godzin: %d) prawdopodobnie uzywa AirBreaka (Hght: %.2f, Diff: ok. %d m/s)., PlayerName(i), i, PlayerCache(i)(pHours), PosZ, distance)
			 				)

							if(PlayerCache(i)(pAirBrkWarns) )= 3)
							(
								hrp_Kick(i, -1, AirBreak)
							)
						)
					)
				)
			)

			// Anty FlyHack (przy wskakiwaniu do basenu w willi Madd Dogga)
			if(PosZ ) 120.0 && (anim_id == 1543 || anim_id == 1538 || anim_id == 1539))
			(
				ShowAdminLog(~r~(cheat) ~w~Gracz %s (ID: %d, Godzin: %d) prawdopodobnie uzywa FlyHacka (hgt: %.2f)., PlayerName(i), i, PlayerCache(i)(pHours), PosZ)
				continue
			)
			
			// Anty UnFreeze
			if(PlayerCache(i)(pFreeze))
			(
				if(GetPlayerState(i) != PLAYER_STATE_PASSENGER)
				(
					if(!IsPlayerInRangeOfPoint(i, 3.0, PlayerCache(i)(pFreezePosX), PlayerCache(i)(pFreezePosY), PlayerCache(i)(pFreezePosZ)))
					(
						if(loop_player_speed )= 5)
						(
							hrp_Kick(i, -1, UnFreeze)
							continue
						)
						else
						(
							GetPlayerPos(i, PlayerCache(i)(pFreezePosX), PlayerCache(i)(pFreezePosY), PlayerCache(i)(pFreezePosZ))
						)
					)
				)
			)

			// Anty JetPack
			if(GetPlayerSpecialAction(i) == SPECIAL_ACTION_USEJETPACK)
			(
				hrp_Ban(i, -1, JetPack, 0)
				continue
			)
			
			// Anty SpectateHack
			if(GetPlayerState(i) == PLAYER_STATE_SPECTATING && PlayerCache(i)(pSpectate) == INVALID_PLAYER_ID && PlayerCache(i)(pAdmin) == 0)
			(
				hrp_Kick(i, -1, SpectateHack)
				continue
			)

			// SprawdŸ czy æwiczy, a jak æwiczy a nie ma do tego odpowiedniej animki to zastopuj æwiczenie
			if(PlayerCache(i)(pGymType) != TRAIN_NONE && PlayerCache(i)(pGymPhase) != 0)
			(
				
				if(PlayerCache(i)(pGymType) == TRAIN_BENCH_PRESS)
				(
					if(anim_id ( 47 || anim_id ) 50)
					(
						OnPlayerGymTrainStopped(i)
					)
				)
				if(PlayerCache(i)(pGymType) == TRAIN_BARBELL)
				(
					if(anim_id != 576 && anim_id != 575 && anim_id != 573 && anim_id != 570)
					(
						OnPlayerGymTrainStopped(i)
					)
				)
			)

			// Jeœli trenuje
   			if(PlayerCache(i)(pTrainTime))
			(
				PlayerCache(i)(pTrainTime) --

				if(PlayerCache(i)(pTrainTime) ) 60)
				(
					format(string, sizeof(string), ~w~Pozostaly czas: ~y~%d ~w~min, PlayerCache(i)(pTrainTime)/60)
					GameTextForPlayer(i, string, 1000, 6)
  				)
				else
				(
					format(string, sizeof(string), ~w~Pozostaly czas: ~y~%d ~w~sec, PlayerCache(i)(pTrainTime))
   					GameTextForPlayer(i, string, 1000, 6)
				)
				

				if(PlayerCache(i)(pTrainTime) (= 0)
				(
					PlayerCache(i)(pTrainTime) = 0
					if(PlayerCache(i)(pGymType) != TRAIN_NONE)
					(
						OnPlayerGymTrainStopped(i)
						GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~w~Trening dobiegl ~r~konca, 5000, 3)
					)
					
					itemid = PlayerCache(i)(pGymPass)

					ItemInfo(itemid)(iUsed) = 0
					ItemInfo(itemid)(iValue1) = PlayerCache(i)(pTrainTime) / 60

					if(ItemInfo(itemid)(iValue1))
					(
						mysql_query_format(UPDATE hrp_items SET item_used = %d, item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
					)
					else
					(
						DeleteItem(ItemInfo(itemid)(iUID))
					)
					PlayerCache(i)(pGymPass) = 0
				)
			)
			
			// Jeœli jest podczas paintballa
   			if(PlayerCache(i)(pPaintballTime))
			(
				PlayerCache(i)(pPaintballTime) --

				if(PlayerCache(i)(pPaintballTime) ) 60)
				(
					format(string, sizeof(string), ~w~Pozostaly czas: ~y~%d ~w~min, PlayerCache(i)(pPaintballTime)/60)
					GameTextForPlayer(i, string, 1000, 6)
  				)
				else
				(
					format(string, sizeof(string), ~w~Pozostaly czas: ~y~%d ~w~sec, PlayerCache(i)(pPaintballTime))
   					GameTextForPlayer(i, string, 1000, 6)
				)
				

				if(PlayerCache(i)(pPaintballTime) (= 0)
				(
					PlayerCache(i)(pPaintballTime) = 0
					GameTextForPlayer(i, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~w~Czas wejsciowki dobiegl ~r~konca, 5000, 3)
					
					doorid = GetPlayerDoorID(i)
					OnPlayerExitDoor(i, doorid) // seler do sprawdzenia
					
					ResetPlayerWeapons(i)
		
					if(WeaponCache(i)(WEAPON_MAIN)(pWeaponUID))
					(
						itemid = GetItemID(WeaponCache(i)(WEAPON_MAIN)(pWeaponUID))
						
						ItemInfo(itemid)(iUsed) = 0
						ItemInfo(itemid)(iValue2) = WeaponCache(i)(WEAPON_MAIN)(pWeaponAmmo)
						
						mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
					)
					
					WeaponCache(i)(WEAPON_MAIN)(pWeaponUID) = 0
					WeaponCache(i)(WEAPON_MAIN)(pWeaponID) = 0
					WeaponCache(i)(WEAPON_MAIN)(pWeaponAmmo) = 0
					WeaponCache(i)(WEAPON_MAIN)(pLastAmmo) = 0
					WeaponCache(i)(WEAPON_MAIN)(pShot) = false
					
					if(IsPlayerAttachedObjectSlotUsed(i, SLOT_WEAPON_MAIN))
					(
						RemovePlayerAttachedObject(i, SLOT_WEAPON_MAIN)
					)
					
					if(WeaponCache(i)(WEAPON_SIDE)(pWeaponUID))
					(
						itemid = GetItemID(WeaponCache(i)(WEAPON_SIDE)(pWeaponUID))
						
						ItemInfo(itemid)(iUsed) = 0
						ItemInfo(itemid)(iValue2) = WeaponCache(i)(WEAPON_SIDE)(pWeaponAmmo)
						
						mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
					)
					
					WeaponCache(i)(WEAPON_SIDE)(pWeaponUID) = 0
					WeaponCache(i)(WEAPON_SIDE)(pWeaponID) = 0
					WeaponCache(i)(WEAPON_SIDE)(pWeaponAmmo) = 0
					WeaponCache(i)(WEAPON_SIDE)(pLastAmmo) = 0
					WeaponCache(i)(WEAPON_SIDE)(pShot) = false
					
					if(IsPlayerAttachedObjectSlotUsed(i, SLOT_WEAPON_SIDE))
					(
						RemovePlayerAttachedObject(i, SLOT_WEAPON_SIDE)
					)
					
					if(WeaponCache(i)(WEAPON_FUNC)(pWeaponUID))
					(
						itemid = GetItemID(WeaponCache(i)(WEAPON_FUNC)(pWeaponUID))
						
						ItemInfo(itemid)(iUsed) = 0
						ItemInfo(itemid)(iValue2) = WeaponCache(i)(WEAPON_FUNC)(pWeaponAmmo)
						
						mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iUID))
					)
					
					WeaponCache(i)(WEAPON_FUNC)(pWeaponUID) = 0
					WeaponCache(i)(WEAPON_FUNC)(pWeaponID) = 0
					WeaponCache(i)(WEAPON_FUNC)(pWeaponAmmo) = 0
					WeaponCache(i)(WEAPON_FUNC)(pLastAmmo) = 0
					WeaponCache(i)(WEAPON_FUNC)(pShot) = false
					
					if(IsPlayerAttachedObjectSlotUsed(i, SLOT_WEAPON_FUNC))
					(
						RemovePlayerAttachedObject(i, SLOT_WEAPON_FUNC)
					)
					
					ResetPlayerWeapons(i)
					
					itemid = PlayerCache(i)(pPaintballPass)

					ItemInfo(itemid)(iUsed) = 0
					ItemInfo(itemid)(iValue1) = PlayerCache(i)(pPaintballTime) / 60

					if(ItemInfo(itemid)(iValue1))
					(
						mysql_query_format(UPDATE hrp_items SET item_used = %d, item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
					)
					else
					(
						DeleteItem(ItemInfo(itemid)(iUID))
					)
					PlayerCache(i)(pPaintballPass) = 0
				)
			)
			
			// Sprawdzanie czy nie cheatuje
			if((WeaponCache(i)(WEAPON_MAIN)(pWeaponUID) || WeaponCache(i)(WEAPON_SIDE)(pWeaponUID) || WeaponCache(i)(WEAPON_FUNC)(pWeaponUID)))
			(
				if(!IsPlayerInAnyVehicle(i))
				(
					weapon = loop_player_weapon
					if(weapon && weapon != 43 && weapon != 41 && weapon ) 15 && weapon ( 44)
					(
						if(weapon == WeaponCache(i)(WEAPON_MAIN)(pWeaponID))
						(
							ammo = GetPlayerWeaponAmmo(i, WeaponCache(i)(WEAPON_MAIN)(pWeaponID))
							if(ammo ) WeaponCache(i)(WEAPON_MAIN)(pLastAmmo) || (ammo )= WeaponCache(i)(WEAPON_MAIN)(pLastAmmo) && WeaponCache(i)(WEAPON_MAIN)(pShot)))
							(
								if(PlayerCache(i)(pAmmoWarning) ) 4)
								(
									PlayerCache(i)(pAmmoWarning) = 0
									hrp_Ban(i, -1, Ammo hack, 0)
								)
								else
								(
									PlayerCache(i)(pAmmoWarning) ++
									ShowAdminLog(~r~(cheat) ~w~Gracz %s (ID: %d, Godzin: %d) prawdopodobnie uzywa ammo hacka. Ammo: %d, Ostrzezenie: %s)., PlayerName(i), i, PlayerCache(i)(pHours), ammo, PlayerCache(i)(pAmmoWarning))
								)
							)
							
							WeaponCache(i)(WEAPON_MAIN)(pLastAmmo) = ammo
							WeaponCache(i)(WEAPON_MAIN)(pShot) = false
						)
						if(weapon == WeaponCache(i)(WEAPON_SIDE)(pWeaponID))
						(
							ammo = GetPlayerWeaponAmmo(i, WeaponCache(i)(WEAPON_SIDE)(pWeaponID))
							if(ammo ) WeaponCache(i)(WEAPON_SIDE)(pLastAmmo) || (ammo )= WeaponCache(i)(WEAPON_SIDE)(pLastAmmo) && WeaponCache(i)(WEAPON_SIDE)(pShot)))
							(
								if(PlayerCache(i)(pAmmoWarning) ) 4)
								(
									PlayerCache(i)(pAmmoWarning) = 0
									hrp_Ban(i, -1, Ammo hack, 0)
								)
								else
								(
									PlayerCache(i)(pAmmoWarning) ++
									ShowAdminLog(~r~(cheat) ~w~Gracz %s (ID: %d, Godzin: %d) prawdopodobnie uzywa ammo hacka. Ammo: %d, Ostrzezenie: %s)., PlayerName(i), i, PlayerCache(i)(pHours), ammo, PlayerCache(i)(pAmmoWarning))
								)
							)
							
							WeaponCache(i)(WEAPON_SIDE)(pLastAmmo) = ammo
							WeaponCache(i)(WEAPON_SIDE)(pShot) = false
						)
						if(weapon == WeaponCache(i)(WEAPON_FUNC)(pWeaponID))
						(
							ammo = GetPlayerWeaponAmmo(i, WeaponCache(i)(WEAPON_FUNC)(pWeaponID))
							if(ammo ) WeaponCache(i)(WEAPON_FUNC)(pLastAmmo) || (ammo )= WeaponCache(i)(WEAPON_FUNC)(pLastAmmo) && WeaponCache(i)(WEAPON_FUNC)(pShot)))
							(
								if(PlayerCache(i)(pAmmoWarning) ) 4)
								(
									PlayerCache(i)(pAmmoWarning) = 0
									hrp_Ban(i, -1, Ammo hack, 0)
								)
								else
								(
									PlayerCache(i)(pAmmoWarning) ++
									ShowAdminLog(~r~(cheat) ~w~Gracz %s (ID: %d, Godzin: %d) prawdopodobnie uzywa ammo hacka. Ammo: %d, Ostrzezenie: %d)., PlayerName(i), i, PlayerCache(i)(pHours), ammo, PlayerCache(i)(pAmmoWarning))
								)
							)
							
							WeaponCache(i)(WEAPON_FUNC)(pLastAmmo) = ammo
							WeaponCache(i)(WEAPON_FUNC)(pShot) = false
						)
					)
				)
			)
			
			// Worek treningowy
			if(PlayerCache(i)(pGymType) == TRAIN_PUNCH_BAG)
			(
				object_id = PlayerCache(i)(pGymObject),
					Float:obPosX, Float:obPosY, Float:obPosZ
				
				GetDynamicObjectPos(object_id, obPosX, obPosY, obPosZ)
				if(IsPlayerInRangeOfPoint(i, 3.0, obPosX, obPosY, obPosZ))
				(
	   				if(IsPlayerFacingObject(i, object_id))
		   			(
						keysa, uda, lra
						GetPlayerKeys(i, keysa, uda, lra)
						if(keysa == 144)
						(
							fighting_style = GetPlayerFightingStyle(i)
							if(fighting_style == FIGHT_STYLE_BOXING)
							(
								if(anim_id == 473 || anim_id == 474)
								(
									OnPlayerTrainRep(i)
								)
							)
							
							if(fighting_style == FIGHT_STYLE_KUNGFU)
							(
								if(anim_id == 483 || anim_id == 484)
								(
									OnPlayerTrainRep(i)
								)
							)
							
							if(fighting_style == FIGHT_STYLE_KNEEHEAD)
							(
								if(anim_id == 495)
								(
									OnPlayerTrainRep(i)
								)
							)
							
							if(fighting_style == FIGHT_STYLE_GRABKICK)
							(
								if(anim_id == 504 || anim_id == 505)
								(
									OnPlayerTrainRep(i)
								)
							)
						)
					)
				)
				else
				(
					OnPlayerGymTrainStopped(i)
				)
			)
			
			// Leczenie gracza przez medyka
			if(PlayerCache(i)(pHealing) != INVALID_PLAYER_ID)
			(
				patient_id = PlayerCache(i)(pHealing)
				if(PlayerToPlayer(5.0, i, patient_id))
				(
					if(PlayerCache(patient_id)(pHealth) + 5.0 ( 100.0)
					(
						hrp_SetPlayerHealth(patient_id, PlayerCache(patient_id)(pHealth) + 5.0)
						
						GameTextForPlayer(i, ~n~~n~~n~~n~~n~~g~~h~Proces leczenia trwa..., 3000, 3)
						GameTextForPlayer(patient_id, ~n~~n~~n~~n~~n~~g~~h~Proces leczenia trwa..., 3000, 3)
					)
					else
					(
						PlayerCache(i)(pHealing) = INVALID_PLAYER_ID
						
						hrp_SetPlayerHealth(patient_id, 100.0)
						
						ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Proces leczenia zosta³ zakoñczony pomyœlnie., OK, )
						ShowPlayerDialog(patient_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Proces leczenia zosta³ zakoñczony pomyœlnie., OK, )
					)
				)
				else
				(
					PlayerCache(i)(pHealing) = INVALID_PLAYER_ID
				
					ShowPlayerDialog(i, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Proces leczenia gracza zosta³o anulowane.\nPowód: Gracz znajduje siê zbyt daleko od Ciebie., OK, )
					GameTextForPlayer(patient_id, ~r~~h~Leczenie zostalo przerwane., 4500, 3)
				)
			)
			
			// W busie
			if(PlayerCache(i)(pBusRide))
			(
   				PlayerCache(i)(pBusTime) --
   				
				Float:busPosX, Float:busPosY, Float:busPosZ
				GetPlayerCameraPos(i, busPosX, busPosY, busPosZ)
				hrp_SetPlayerPos(i, busPosX, busPosY, busPosZ)
   				
				if(PlayerCache(i)(pBusTime) (= 0)
				(
					hrp_SetPlayerPos(i, BusStopData(PlayerCache(i)(pBusTravel))(bPosX), BusStopData(PlayerCache(i)(pBusTravel))(bPosY), BusStopData(PlayerCache(i)(pBusTravel))(bPosZ))
					PlayerCache(i)(pBusStart) = 0
					PlayerCache(i)(pBusTravel) = 0
						
					PlayerCache(i)(pBusTime) = 0
					PlayerCache(i)(pBusPrice) = 0
					PlayerCache(i)(pBusRide) = false

					TogglePlayerControllable(i, 1)

					SetPlayerInterior(i, 0)
					SetPlayerVirtualWorld(i, 0)

					SetCameraBehindPlayer(i)

					PlayerPlaySound(i, 1098, 0.0, 0.0, 0.0)
					PlayerPlaySound(i, 1147, 0.0, 0.0, 0.0)
				)
			)
			
			// Pali Jointa
			if(PlayerCache(i)(pSmokeJoint))
			(
				if(GetPlayerSpecialAction(i) == SPECIAL_ACTION_SMOKE_CIGGY)
				(
					if(anim_id == 609)
					(
						SetPlayerDrunkLevel(i, GetPlayerDrunkLevel(i) + 710)
						
						PlayerCache(i)(pSmokeLevel) += 50
						if(PlayerCache(i)(pSmokeLevel) )= 780 && PlayerCache(i)(pSmokeLevel) ( 910)
						(
							SetPlayerWeather(i, 62)
						)
						else if(PlayerCache(i)(pSmokeLevel) )= 910)
						(
							SetPlayerWeather(i, -66)
						)
						else
						(
							SetPlayerWeather(i, 1)
						)
						
						PlayerCache(i)(pSmokeReps) --
						if(PlayerCache(i)(pSmokeReps) (= 0)
						(
							SetPlayerSpecialAction(i, SPECIAL_ACTION_NONE)
							PlayerCache(i)(pSmokeJoint) = false
							
							PlayerCache(i)(pSmokeReps) = 0
						)
					)
				)
				else
				(
					PlayerCache(i)(pSmokeJoint) = false
					PlayerCache(i)(pSmokeReps) = 0
				)
			)
			
			if(PlayerCache(i)(pSmokeLevel))
			(
				PlayerCache(i)(pSmokeLevel) -= 5
				
				if(PlayerCache(i)(pSmokeLevel) ) 780 && PlayerCache(i)(pSmokeLevel) (= 910)
				(
					SetPlayerWeather(i, 62)
				)
				else if(PlayerCache(i)(pSmokeLevel) (= 0)
				(
					SetPlayerDrunkLevel(i, 0)
					SetPlayerWeather(i, weather)
					
					PlayerCache(i)(pSmokeLevel) = 0
				)
			)
			
			// Uzale¿nienie
			if(PlayerCache(i)(pDependence) )= 400)
			(
				if(random(300) == 60)
				(
						rand = random(5)
				   	if(rand == 1)
					(
							format(string, sizeof(string), * %s zaczyna mocno kaszleæ., PlayerName(i))
						FlashMe(i, string) //ProxDetector(10.0, i, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
					)
					else if(rand == 2)
					(
  						SendClientMessage(i, COLOR_DO, ** Odczuwasz lekkie dusznoœci **)
					)
					else if(rand == 3)
					(
						SendClientMessage(i, COLOR_DO, ** Od kilku minut odnosisz wra¿enie, ¿e ktoœ Ciê œledzi. **)
					)
					else if(rand == 4)
					(
						SendClientMessage(i, COLOR_DO, ** S³yszysz dziwne g³osy, zdaj¹ce siê mówiæ do Ciebie. **)
					)
					else if(rand == 5)
					(
						SendClientMessage(i, COLOR_DO, ** Masz wra¿enie, jakby ktoœ trzyma³ Ciê za rêkê. **)
					)
				)
			)
			
			if(PlayerCache(i)(pDrugLevel))
			(
				PlayerCache(i)(pDrugLevel) --
				if(PlayerCache(i)(pDrugLevel) (= 0)
				(
					PlayerCache(i)(pDrugLevel) = 0
				)
			)
			
			// Pobierz pozycje dla AntyCheata
			PlayerCache(i)(pCheatPosX) = PosX
			PlayerCache(i)(pCheatPosY) = PosY
			PlayerCache(i)(pCheatPosZ) = PosZ
			
			PlayerCache(i)(pGotAirBrkPos) = 1
			
			// Zaktualizuj status
			UpdatePlayerStatus(i)
			
			// Odœwie¿ nick, jeœli status jest inny
			if(PlayerCache(i)(pStatus) != status || PlayerCache(i)(pChangeName))
			(
				if(!PlayerCache(i)(pMaskUID))
				(
	  				format(string, sizeof(string), %s (%d)%s, PlayerName(i), i, GetPlayerStatusInfo(i))
				)
				else
				(
	   				format(string, sizeof(string), %s%s, PlayerName(i), GetPlayerStatusInfo(i))
				)
				Update3DTextLabelText(Text3D:PlayerCache(i)(pNameTag), PlayerCache(i)(pNickColor), string)

				if(PlayerCache(i)(pChangeName)) PlayerCache(i)(pChangeName) = false
			)

			// Sprawdzanie czy gracz nie spierdoli³ spod budki przy rozmowie
			if(PlayerCache(i)(pUsingBooth))
			(
				object_id = GetClosestObject(i, 3.0)				
				if(object_id == INVALID_OBJECT_ID || (GetObjectModel(object_id) != OBJECT_TELEPHONE && GetObjectModel(object_id) != OBJECT_TELEPHONE_ALT))
				(
					foreach(Calls, callid)
					(
						if(callid ) MAX_CALLS || callid == 0) break
						if((Call(callid)(caller) == i || Call(callid)(called) == i) && Call(callid)(callerDevice) == DEVICE_BOX || Call(callid)(calledDevice) == DEVICE_BOX)
						(
							EndCall(callid)
						)
					)

					PlayerCache(i)(pUsingBooth) = false
				)
			)
			
			// Sygna³ po³¹czenia	- blint kurwa 1
			h, m, s
			gettime(h, m, s)
			if(s % 7)
			(
				if(PlayerCache(i)(pCall) != -1)
				(
					if(!Call(PlayerCache(i)(pCall))(convo))
					(
						PlayerPlaySound(i, 16001, 0.0, 0.0, 0.0)
					)
				)
			)
			
			// Chowanie Flashbanga
			if(PlayerCache(i)(pFlashed) ) 0)
			(
				if(PlayerCache(i)(pFlashed) + 15 ( gettime())
				(
					TextDrawHideForPlayer(i, Text:TextDrawFlashbang(i))
					PlayerCache(i)(pFlashed) = 0
				)
			)
			
			// Sprawdzanie sprz¹taczy
			if(PlayerCache(i)(pSweep))
			(
				if(PlayerCache(i)(pSweepTime) + 45 ( gettime())
				(
					if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
					(
						vehicleid = loop_player_vehid
						PlayerCache(i)(pSweep) = false
						PlayerCache(i)(pSweepStep) = 0
						PlayerCache(i)(pSweepSteps) = 0
						PlayerCache(i)(pSweepRoute) = 0
									
						TextDrawSetString(Text:TextDrawMainInfo(i), Wysiadles ze Sweepera dlatego Twoja praca zostala anulowana.)
						TextDrawShowForPlayer(i, Text:TextDrawMainInfo(i))
						PlayerCache(i)(pShowInfoText) = 7
						
						DisablePlayerRaceCheckpoint(i)
						
						if(GetVehicleModel(vehicleid == 574))
						(
							UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, 0)
							GetVehicleDamageStatus(vehicleid, CarInfo(vehicleid)(cVisual)(0), CarInfo(vehicleid)(cVisual)(1), CarInfo(vehicleid)(cVisual)(2), CarInfo(vehicleid)(cVisual)(3))

							CarInfo(vehicleid)(cHealth) = 1000.0
							SetVehicleHealth(vehicleid, 1000.0)

							SaveVehicle(vehicleid, SAVE_VEH_COUNT)
							SaveVehicle(vehicleid, SAVE_VEH_ACCESS)
							
							SetVehicleToRespawn(vehicleid)
						)
					)
				)
			)

			// Rage (narkotyki)
			if(PlayerCache(i)(pRage))
			(
				bool:rage_camera = false,
					bool:rage_gametext = false,
					bool:rage_text = false
				
				hour, minute, second
					gettime(hour, minute, second)
				
				if(PlayerCache(i)(pRageDrug) == DRUG_LSD || PlayerCache(i)(pRageDrug) == DRUG_METAAMP || PlayerCache(i)(pRageDrug) == DRUG_SHROOMS || PlayerCache(i)(pRageDrug) == DRUG_MARIHUANA)
				(
					SetPlayerTime(i, 17, 0)
				)
				
				PlayerCache(i)(pRageTime) --
				//PlayerCache(i)(pRageTime) -= 100 // Testowy wartoœæ do testowania efektów - zmniejsza z 15 minut do 15 sekund.
				
				switch(PlayerCache(i)(pRageDrug))
				(
					case DRUG_MARIHUANA:
					(
						// nic
					)
					case DRUG_HEROIN:
					(
						if(minute % 5 == 0 && second == 1)
						(
							rand = random(3) + 1
							switch(PlayerCache(i)(pRageDrugUse))
							(
								case DRUG_USE_SNORT:
								(
									switch(rand)
									(
										case 1: ( format(string, sizeof(string), ** Twoja postaæ czuje siê intensywnie odprê¿ona. **) rage_text = true )
										case 2: ( format(string, sizeof(string), ** Twoja postaæ czuje siê b³ogo. **) rage_text = true )
										case 3: ( format(string, sizeof(string), ** Twoja postaæ czuje ulgê. **) rage_text = true )
									)
								)
								case DRUG_USE_SMOKE:
								(
									switch(rand)
									(
										case 1: ( format(string, sizeof(string), ** Wszelkie troski ustêpuj¹. **) rage_text = true )
										case 2: ( format(string, sizeof(string), ** Nie masz siê czym martwiæ. **) rage_text = true )
										case 3: ( format(string, sizeof(string), ** Jesteœ œpi¹cy. **) rage_text = true )
									)
								)
								case DRUG_USE_INJECT:
								(
									switch(rand)
									(
										case 1:( format(string, sizeof(string), ** Jesteœ bardzo œpi¹cy. **) rage_text = true )
										case 2: ( format(string, sizeof(string), ** Czujesz, ¿e odp³ywasz. **) rage_text = true )
										case 3: ( format(string, sizeof(string), ** Widzisz siebie z góry. **) rage_text = true )
									)
								)
							)
						)
						rage_camera = true
						rage_gametext = true
					)
					case DRUG_AMPHETAMINE:
					(
						if(minute % 5 == 0 && second == 1)
						(
							rand = random(3)
							switch(PlayerCache(i)(pRageDrugUse))
							(
								case DRUG_USE_SNORT:
								(
									if(PlayerCache(i)(pDependence) ( 200)
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Nikt Ciê nie pokona! **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Serce wali ci jak m³ot. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Ale faza ja pierdolê! **) rage_text = true )
										)
									)
									else
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Ktoœ za tob¹ chodzi od d³u¿szego czasu. **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Spójrz za siebie. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Oni Ciê widz¹... **) rage_text = true )
										)
									)
								)
								case DRUG_USE_SMOKE:
								(
									if(PlayerCache(i)(pDependence) ( 200)
									(	
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Twoje cia³o odp³ywa... **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Nie czujesz siê za dobrze. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Chyba zaraz odlecisz... **) rage_text = true )
										)
									)
									else
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Obejrzyj siê za siebie. **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Chyba jesteœ na pods³uchu. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Czujesz siê œledzony. **) rage_text = true )
										)
									)
								)
								case DRUG_USE_INJECT:
								(
									if(PlayerCache(i)(pDependence) ( 200)
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Czujesz mocne pobudzenie. **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Chyba nie przeœpisz tej nocy. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Twoje serce wali jak dzwon. **) rage_text = true )
										)
									)
									else
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Czujesz siê œledzony. **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Czujesz siê obserwowany. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Nie patrz za siebie... **) rage_text = true )
										)
									)
									rage_camera = true
								)
							)
						)
					)
					case DRUG_CRACK:
					(
						rage_camera = true
					)
					case DRUG_LSD, DRUG_SHROOMS:
					(
						if(minute % 5 == 0 && second == 1)
						(
							rand = random(3)
							if(PlayerCache(i)(pDependence) ( 200)
							(
								switch(rand)
								(
									case 1: ( format(string, sizeof(string), ** Kolorowe wizualizacje wzbogacaj¹ tw¹ wizjê. **) rage_text = true )
									case 2: ( format(string, sizeof(string), ** Twarze dziwnie siê wyginaj¹, wszystko siê rusza. **) rage_text = true )
									case 3: ( format(string, sizeof(string), ** Wszystko dooko³a jest zwielokrotnione. **) rage_text = true )
								)
							)
							else
							(
								switch(rand)
								(
									case 1: ( format(string, sizeof(string), ** Nigdy nie mia³eœ tak z³ej podró¿y! **) rage_text = true )
									case 2: ( format(string, sizeof(string), ** Czujesz siê jak ostatnie gówno. **) rage_text = true )
									case 3: ( format(string, sizeof(string), ** Masz krzyw¹ fazê, widzisz popieprzone rzeczy. **) rage_text = true )
								)
							)
						)
					)
					case DRUG_MDMA:
					(
						if(minute % 5 == 0 && second == 1)
						(
							rand = random(3)
							if(PlayerCache(i)(pDependence) ( 200)
							(
								switch(rand)
								(
									case 1: ( format(string, sizeof(string), ** Chce ci siê tañczyæ, a ka¿demu ruchowi towarzyszy euforia! **) rage_text = true )
									case 2: ( format(string, sizeof(string), ** Nie mo¿esz ustaæ na miejscu. **) rage_text = true )
									case 3: ( format(string, sizeof(string), ** Gor¹co Ci! **) rage_text = true )
								)
							)
							else
							(
								switch(rand)
								(
									case 1: ( format(string, sizeof(string), ** Zaraz siê zrzygasz... **) rage_text = true )
									case 2: ( format(string, sizeof(string), ** Twój organizm chyba wiêcej nie wytrzyma, czujesz, ¿e masz gor¹czkê. **) rage_text = true )
									case 3: ( format(string, sizeof(string), ** Twoja g³owa zaraz eksploduje, wszystko wydaje siê zbyt g³oœne. **) rage_text = true )
								)
							)
						)
					)
					case DRUG_METAAMP:
					(
						if(minute % 5 == 0 && second == 1)
						(
							rand = random(3)
							switch(PlayerCache(i)(pRageDrugUse))
							(
								case DRUG_USE_SNORT:
								(
									if(PlayerCache(i)(pDependence) ( 200)
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Nikt Ciê nie pokona! **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Serce wali ci jak m³ot. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Ale faza ja pierdolê! **) rage_text = true )
										)
									)
									else
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Ktoœ za tob¹ chodzi od d³u¿szego czasu. **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Spójrz za siebie. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Oni Ciê widz¹... **) rage_text = true )
										)
									)
								)
								case DRUG_USE_SMOKE:
								(
									if(PlayerCache(i)(pDependence) ( 200)
									(	
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Twoje cia³o odp³ywa... **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Nie czujesz siê za dobrze. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Chyba zaraz odlecisz... **) rage_text = true )
										)
									)
									else
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Obejrzyj siê za siebie. **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Chyba jesteœ na pods³uchu. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Czujesz siê œledzony. **) rage_text = true )
										)
									)
								)
								case DRUG_USE_INJECT:
								(
									if(PlayerCache(i)(pDependence) ( 200)
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Czujesz mocne pobudzenie. **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Chyba nie przeœpisz tej nocy. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Twoje serce wali jak dzwon. **) rage_text = true )
										)
									)
									else
									(
										switch(rand)
										(
											case 1: ( format(string, sizeof(string), ** Czujesz siê œledzony. **) rage_text = true )
											case 2: ( format(string, sizeof(string), ** Czujesz siê obserwowany. **) rage_text = true )
											case 3: ( format(string, sizeof(string), ** Nie patrz za siebie... **) rage_text = true )
										)
									)
									rage_camera = true
									rage_gametext = true
								)
							)
						)
					)
					default:()
				)
				
				if(rage_camera)
				(
					if(PlayerCache(i)(pRageTime) % 3 == 0)
					(
						Float:x, Float:y, Float:z
						GetPlayerPos(i, x, y, z)
						InterpolateCameraPos(i, x, y, z, x + (random(10) - 5), y + (random(10) - 5), z + 1, 3 * 1000, CAMERA_MOVE)
					)
				)
				
				if(rage_gametext)
				(
					rage(128)
					format(rage, sizeof(rage), )
					for(j = 0 j ( 30 j++)
					(
						format(rage, sizeof(rage), %s~%s~%s, rage, Colors(random(6)), Letters(random(25)))
					)
					GameTextForPlayer(i, rage, 1000, 3)
				)
				
				if(rage_text)
				(
					SendClientMessage(i, COLOR_DO, string)
					rage_text = false
				)
				
				if(PlayerCache(i)(pRageDrunkLevel) != 0)
				(
					SetPlayerDrunkLevel(i, PlayerCache(i)(pRageDrunkLevel))
				)
				
				if(PlayerCache(i)(pRageTime) (= 1)
				(
					PlayerCache(i)(pStrength) = PlayerCache(i)(pRageStrength)
				
					PlayerCache(i)(pRage) = false
					PlayerCache(i)(pRageTime) = 0
					PlayerCache(i)(pRageDrug) = 0
					PlayerCache(i)(pRageDrugUse) = 0
					PlayerCache(i)(pRageDrunkLevel) = 0

					PlayerCache(i)(pRageStrength) = 0.0
					
					//hrp_SetPlayerPos(i, PlayerCache(i)(pPosX), PlayerCache(i)(pPosY), PlayerCache(i)(pPosZ))
					SetPlayerDrunkLevel(i, 0)
					SetPlayerInterior(i, GetPlayerInterior(i))
					SetPlayerVirtualWorld(i, GetPlayerVirtualWorld(i))
					SetPlayerWeather(i, 1)
					SetCameraBehindPlayer(i)
					
					new_time_h, new_time_m
					gettime(new_time_h, new_time_m)
					SetPlayerTime(i, new_time_h, new_time_m)
				)
			)
			
			// OPTYMALIZACYJNY KOMENTARZ
			
			/*car_music = false,
				stop_car_music = false
			if(PlayerCache(i)(pCarMusic))
			(
				vehid = PlayerCache(i)(pCarMusic)
				if(GetDistanceToVehicle(i, vehid) ) 15.0)
				(
					stop_car_music = true
				)
				else
				(
					if(strlen(CarInfo(vehid)(cAudioURL)) (= 0) stop_car_music = true
					if(GetVehicleBootStatus(vehid) != 1) stop_car_music = true
					if(!CarInfo(vehid)(cEngineTogged)) stop_car_music = true
				)
			)
			else
			(
				car_music = true
			)
			
			if(stop_car_music)
			(
				if(!PlayerCache(i)(pMusicPlayerUID))
				(
					//Audio_Stop(i, PlayerCache(i)(pAudioHandle))
					//Audio_StopRadio(i)
					PlayerCache(i)(pAudioHandle) = 0
					StopAudioStreamForPlayer(i)
				)
				PlayerCache(i)(pCarMusic) = 0
				car_music = true
			)
			
			if(car_music)
			(
				if(!IsPlayerInAnyVehicle(i))
				(
					Float:vX, Float:vY, Float:vZ
					GetVehiclePos(GetClosestVehicle(i, 16.000), vX, vY, vZ)
					if(IsPlayerInRangeOfPoint(i, 20.0, vX, vY, vZ))
					(
						foreach(Vehicles, vehid)
						(
							if(strlen(CarInfo(vehid)(cAudioURL)))
							(
								if(GetVehicleBootStatus(vehid) == 1)
								(
									if(CarInfo(vehid)(cEngineTogged))
									(
										if(GetDistanceToVehicle(i, vehid) ( 15.0)
										(
											if(PlayerCache(i)(pAudioHandle))
											(
												//Audio_Stop(i, PlayerCache(i)(pAudioHandle))
												PlayerCache(i)(pAudioHandle) = 0
												StopAudioStreamForPlayer(i)
												
												if(PlayerCache(i)(pMusicPlayerUID))
												(
													itemid = GetItemID(PlayerCache(i)(pMusicPlayerUID))
													ItemInfo(itemid)(iUsed) = 0
												)
											)
											//Audio_StopRadio(i)
											//PlayerCache(i)(pAudioHandle) = Audio_PlayStreamed(i, CarInfo(vehid)(cAudioURL))
											
											PlayerCache(i)(pAudioHandle) = 1
											PlayAudioStreamForPlayer(i, CarInfo(vehid)(cAudioURL))
											PlayerCache(i)(pCarMusic) = vehid
											break
										)
									)
								)
							)
						)
					)
				)
			)*/
			
			// po postrzale w rêkê
			if(PlayerCache(i)(pBlockShooting) ) 0)
			(
				PlayerCache(i)(pBlockShooting) --
				SetPlayerArmedWeapon(i,0)
			)
			
			// tankowanie
			if(PlayerCache(i)(pFueling))
			(
				vehid = RefuelData(i)(rVeh), fuel_name(16)
				if(RefuelData(i)(rType) == TYPE_BENS)
				(
					fuel_name = Benzyna
				)
				else if(RefuelData(i)(rType) == TYPE_GAS)
				(
					fuel_name = GAZ
				)
				else if(RefuelData(i)(rType) == TYPE_DIESEL)
				(
					fuel_name = ROPA
				)
				else if(RefuelData(i)(rType) == TYPE_AIRFUEL)
				(
					fuel_name = NAFTA LOTNICZA
				)

				RefuelData(i)(rLiters)++
				RefuelData(i)(rPrice) = floatmul(RefuelData(i)(rLiters), RefuelData(i)(rPricePerL))
				PlayerTextDrawHide(i, TextDrawFuelContent(i))
				format(string, sizeof(string), ~b~~h~Tankowanie ~)~ %s~w~~n~~n~CENA: ~r~~h~$%.2f~n~ILOSC: ~g~~h~%d~n~$/LITR: ~y~~h~$%.2f, fuel_name, RefuelData(i)(rPrice), RefuelData(i)(rLiters), RefuelData(i)(rPricePerL))
				TextDrawShowForPlayer(i, Text:TextDrawFuelBack)
				PlayerTextDrawSetString(i, TextDrawFuelContent(i), string)
				PlayerTextDrawShow(i, TextDrawFuelContent(i))
			
				if(PlayerCache(i)(pCash) ( floatadd(RefuelData(i)(rPrice), RefuelData(i)(rPricePerL)) || CarInfo(vehid)(cFuel) + RefuelData(i)(rLiters) )= GetVehicleMaxFuel(CarInfo(vehid)(cModel))) // brak³o kaski || bak jest pe³ny
				(
					price = floatround(RefuelData(i)(rPrice)), value = RefuelData(i)(rLiters), fuelstring(128)
					hrp_GivePlayerMoney(i, -price)
					SavePlayerStats(i, SAVE_PLAYER_BASIC)
					CarInfo(vehid)(cFuel) = floatadd(CarInfo(vehid)(cFuel), value)
					SaveVehicle(vehid, SAVE_VEH_COUNT)
					PlayerCache(i)(pFueling) = false
					RefuelData(i)(rType) = 0
					RefuelData(i)(rLiters) = 0
					RefuelData(i)(rPrice) = 0.00
					RefuelData(i)(rPricePerL) = 0.00
					RefuelData(i)(rVeh) = 0
					format(fuelstring, sizeof(fuelstring), Zap³aci³eœ $%d za %d litrów paliwa., price, value)
					SendClientMessage(i, COLOR_LIGHTBLUE, fuelstring)
					format(fuelstring, sizeof(fuelstring), * Pojazd %s zosta³ pomyœlnie zatankowany (( %s )), CarInfo(vehid)(cName), PlayerName(i))
					ProxDetector(10.0, i, fuelstring, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)	
					PlayerTextDrawHide(i, TextDrawFuelContent(i))
					TextDrawHideForPlayer(i, Text:TextDrawFuelBack)
				) 
			)
			
			if(PlayerCache(i)(pWorkingPhase) == WORKSHOP_SAWING)
			(
				format(string, sizeof(string), ~w~Pozostalo ~r~%d ~w~sekund, PlayerCache(i)(pWorkingTimeLeft))
				GameTextForPlayer(i, string, 1000, 4)
				
				if(PlayerCache(i)(pWorkingTimeLeft) == 1)
				(
					if(PlayerCache(i)(pWorkingRepeat) )= 240)
					(
						rand = random(10)
					
						if(rand == 5)
						(
							GuiMsg(i, Gratulacje! Za Twoj¹ dobr¹ pracê na rzecz placówki naczelnik skróci³ Twój wyrok o godzinê.\nAby ponownie zacz¹æ pracê u¿yj klawisza H (klakson) b¹dŸ zakoñcz pracê komend¹ /praca., 0)
							PlayerCache(i)(pArrestTime) = PlayerCache(i)(pArrestTime) - 3600	// godzina
						)
						else
						(
							GuiMsg(i, Czas dobieg³ koñca. Uda³o Ci siê, stra¿nik jest z Ciebie zadowolony dlatego otrzyma³eœ od niego kilka dolarów.\nAby ponownie zacz¹æ pracê u¿yj klawisza H (klakson) b¹dŸ zakoñcz pracê komend¹ /praca., 0)
							hrp_GivePlayerMoney(i, 6)
						)
					)
					else
					(
						GuiMsg(i, Czas dobieg³ koñca. Niestety nie uda³o siê tym razem, mo¿esz spróbowaæ ponownie.\nAby ponownie zacz¹æ pracê u¿yj klawisza H (klakson) b¹dŸ zakoñcz pracê komend¹ /praca., 0)
					)
					
					PlayerCache(i)(pWorkRepeat)++
					SavePlayerStats(i, SAVE_PLAYER_BASIC)
					
					StopPlayerAnimations(i)
					PlayerCache(i)(pWorkingRepeat) = 0
					PlayerCache(i)(pWorkingPhase) = WORKSHOP_WAITING
				)
				
				PlayerCache(i)(pWorkingTimeLeft)--
			)

			// Przeniesione z OnPlayerUpdate
			if(PlayerCache(i)(pGod))
			(
				hrp_SetPlayerHealth(i, 100.0)
			)

			// Przeniesione z OnPlayerUpdate
			if(GetPlayerVirtualWorld(i) != 0 && !PlayerCache(i)(pRage))
			(
				SetPlayerWeather(i,0)
			)
			else if(!PlayerCache(i)(pRage))
			(
				SetPlayerWeather(i,CurrentWeather)
			)

			// Przeniesione z OnPlayerUpdate // Surfing
			if(PlayerCache(i)(pSurfID) != INVALID_SURFBOARD_ID)
			(
				if(Surfboard(PlayerCache(i)(pSurfID))(surfPlayerID) == i)
				(
					surfid_c = PlayerCache(i)(pSurfID)
					keys(3), Float:floatVal(4)
					GetPlayerPos(i, floatVal(0), floatVal(1), floatVal(2))
					floatVal(3) = Surfboard(surfid_c)(surfSpeed)
					GetPlayerKeys(i, keys(0), keys(1), keys(2))
					
					GetXYInFrontOfPlayerOnSB(i, floatVal(0), floatVal(1), 50.0)
					Surfboard(surfid_c)(surfPosTo)(0) = floatVal(0)
					Surfboard(surfid_c)(surfPosTo)(1) = floatVal(1)
					Surfboard(surfid_c)(surfPosTo)(2) = Surfboard(surfid_c)(surfPos)(2)
					
					if(keys(0) == KEY_WALK)
					(
						surf_StopSurfing(i)
					)
					
					if(keys(1) == KEY_UP)
					(
						if(floatVal(3) )= 0.0 && floatVal(3) ( MAX_SURFBOARD_SPEED) Surfboard(surfid_c)(surfSpeed) += 0.05
						if(floatVal(3) )= MAX_SURFBOARD_SPEED) Surfboard(surfid_c)(surfSpeed) = MAX_SURFBOARD_SPEED
						//
						//SetDynamicObjectRot(Surfboard(surfid_c)(surfObjectID), Surfboard(surfid_c)(surfPos)(3), Surfboard(surfid_c)(surfPos)(4), Surfboard(surfid_c)(surfPos)(5))
					)
					else if(keys(1) == KEY_DOWN)
					(
						if(floatVal(3) )= 0.0 && floatVal(3) ( MAX_SURFBOARD_SPEED) Surfboard(surfid_c)(surfSpeed) -= 0.05
						if(floatVal(3) )= MAX_SURFBOARD_SPEED) Surfboard(surfid_c)(surfSpeed) = MAX_SURFBOARD_SPEED
						//
						//SetDynamicObjectRot(Surfboard(surfid_c)(surfObjectID), Surfboard(surfid_c)(surfPos)(3), Surfboard(surfid_c)(surfPos)(4), Surfboard(surfid_c)(surfPos)(5))
					)
					
					if(keys(2) == KEY_LEFT)
					(
						Surfboard(surfid_c)(surfSpeed) -= 0.01
						Surfboard(surfid_c)(surfPos)(5) += 1.5
						SetObjectRot(Surfboard(surfid_c)(surfObjectID), Surfboard(surfid_c)(surfPos)(3), Surfboard(surfid_c)(surfPos)(4), Surfboard(surfid_c)(surfPos)(5))
						SetPlayerFacingAngle(i, Surfboard(surfid_c)(surfPos)(5) + 270.0)
						Surfboard(surfid_c)(surfPosTo)(0) = floatVal(0)
						Surfboard(surfid_c)(surfPosTo)(1) = floatVal(1)
						Surfboard(surfid_c)(surfPosTo)(2) = Surfboard(surfid_c)(surfPos)(2)
					)
					else if(keys(2) == KEY_RIGHT)
					(
						Surfboard(surfid_c)(surfSpeed) -= 0.01
						Surfboard(surfid_c)(surfPos)(5) -= 1.5
						SetObjectRot(Surfboard(surfid_c)(surfObjectID), Surfboard(surfid_c)(surfPos)(3), Surfboard(surfid_c)(surfPos)(4), Surfboard(surfid_c)(surfPos)(5))
						SetPlayerFacingAngle(i, Surfboard(surfid_c)(surfPos)(5) + 270.0)
						Surfboard(surfid_c)(surfPosTo)(0) = floatVal(0)
						Surfboard(surfid_c)(surfPosTo)(1) = floatVal(1)
						Surfboard(surfid_c)(surfPosTo)(2) = Surfboard(surfid_c)(surfPos)(2)
					)
					
					if(Surfboard(surfid_c)(surfSpeed) ) 0.005)
					(
						Surfboard(surfid_c)(surfSpeed) -= 0.005
						MoveObject(Surfboard(surfid_c)(surfObjectID), Surfboard(surfid_c)(surfPosTo)(0), Surfboard(surfid_c)(surfPosTo)(1), Surfboard(surfid_c)(surfPosTo)(2), Surfboard(surfid_c)(surfSpeed) )
					)
					else surf_StopBoard(surfid_c)
				)
			)
		)
		//Koniec if Logged && Spawned
	)
	// Koniec foreach Players
	
	foreach(Gangbang, gbid)
	(
		if(Gangbang(gbid)(gbZone))
		(
			a_count = 0, d_count = 0
			
			gbstring(64)
			format(gbstring, sizeof(gbstring), ~w~Pozostalo ~r~%d ~w~sekund, (Gangbang(gbid)(gbStartTime) + 60*10) - gettime())
			
			foreach(Player, i)
			(
				if(IsPlayerInGroup(i, GroupData(Gangbang(gbid)(gbAttackingGroup))(gUID)))
				(
					a_count++
					GameTextForPlayer(i, gbstring, 1000, 4)
					continue
				)
				if(IsPlayerInGroup(i, GroupData(Gangbang(gbid)(gbDefendingGroup))(gUID)))
				(
					d_count++
					GameTextForPlayer(i, gbstring, 1000, 4)
					continue
				)
			)

			if(floatround(Gangbang(gbid)(gbAttackingDeaths) / 2.0) ) a_count)
			(
				// Wygrana broni±cych
				// lock terenu
			)

			if(floatround(Gangbang(gbid)(gbDefendingDeaths) / 2.0) ) d_count)
			(
				// Wygrana atakuj±cych
				// przekazanie terenu
			)

			if(Gangbang(gbid)(gbStartTime) + 60*10 ( gettime())
			(
				// koniec i wygrywaj± broni±cy
			)
		)
	)

	// Sprawdzanie czy gdzies nie ma za duzo strzelania
	for(j = 0 j ( sizeof(GunRegionInfo) j++)
	(
		if(ShootsFired(j) ) GunRegionInfo(j)(grTolerance))
		(
			if(!ShootsFiredInfo(j))
			(
				// od 10 do 120
				countdown = 10 + random(110)
				ShootsCountdown(j) = countdown
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pGroupDuty))
						(
							group_id_fix = GetPlayerDutyGroupID(i)
							if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
							(
								ShootsFiredInfo(j) = true
							)
						)
					)
				)
			)
			ShootsFired(j) = 0
		)
	)
	
	foreach(Vehicles, vehid)
	(
		if(CarInfo(vehid)(cEBreak))
		(
			if(!GetVehicleEngineStatus(vehid))
			(
				if(CarInfo(vehid)(cHealth) ) 600.0)
				(
					Float: tX, Float:tY, Float:tZ, Float:tA
					GetVehiclePos(vehid, tX, tY, tZ)
					GetVehicleZAngle(vehid, tA)
					
					if(tX ) CarInfo(vehid)(cEPosX) + 5 || tX ( CarInfo(vehid)(cEPosX) - 5 || tY ) CarInfo(vehid)(cEPosY) + 5 || tY ( CarInfo(vehid)(cEPosY) - 5 || tZ ) CarInfo(vehid)(cEPosZ) + 5 || tZ ( CarInfo(vehid)(cEPosX) - 5)
					(
						SetVehiclePos(vehid, CarInfo(vehid)(cEPosX), CarInfo(vehid)(cEPosY), CarInfo(vehid)(cEPosZ))
					)
				)
			)
		)
	)

	return 1
)

// Przebijanie opon na kolczatkach
/*forward OnOneHalfTimer()
public OnOneHalfTimer()*/

/*
task OnOneHalfTimer(500)()
(
	for(s = 0 s ( sizeof(PoliceSpikes) s++)
	(
		object_id = PoliceSpikes(s)
		if(IsValidDynamicObject(object_id))
		(
			foreach(Player, i)
			(
				if(IsPlayerInAnyVehicle(i))
				(
					Float:obPosX, Float:obPosY, Float:obPosZ, vehid = GetPlayerVehicleID(i)
					GetDynamicObjectPos(object_id, obPosX, obPosY, obPosZ)
					if(IsPlayerInRangeOfPoint(i, 4.0, obPosX, obPosY, obPosZ))
					(
						if(GetVehicleComponentInSlot(vehid, 7) != 1025) //Sprawdzanie czy ma felgi offroad - je¿eli tak to nie przebija.
						(
							CarInfo(vehid)(cVisual)(3) = random(15) + 1
							UpdateVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))
						)
					)
				)
			)
		)
	)
	
	
	// Miganie œwiate³ dla pd, fd, mc, fbi, etc.
	foreach(Vehicles, vehid)
	(	
		Float:health = 0.0
		GetVehicleHealth(vehid, health)
		
		// tutaj stroboskopy dodajmy
		if(CarInfo(vehid)(cFlashed))
		(
			panelsx, doorsx, lightsx, tiresx
			switch(CarInfo(vehid)(cFlashPhase))
			(
				case 0:
				(
					CarInfo(vehid)(cFlashPhase) = 1
					GetVehicleDamageStatus(vehid,panelsx,doorsx,lightsx,tiresx)
                    UpdateVehicleDamageStatus(vehid, panelsx, doorsx, 4, tiresx)
				)
				case 1:
				(
					CarInfo(vehid)(cFlashPhase) = 0
					GetVehicleDamageStatus(vehid,panelsx,doorsx,lightsx,tiresx)
                    UpdateVehicleDamageStatus(vehid, panelsx, doorsx, 1, tiresx)
				)
			)
		)
		
		if(CarInfo(vehid)(cPilotTick))
		(
			CarInfo(vehid)(cPilotTick) = false
			ChangeVehicleLightsStatus(vehid, false)
		)
	
		Float:sx, Float:sy, Float:sz
		GetVehicleVelocity(vehid, sx, sy, sz)
		if(sx ) 0.05 || sy ) 0.05 || sz ) 0.05)
		(
			panels, doors, lights, tires
			GetVehicleDamageStatus(vehid, panels, doors, lights, tires)
			if(tires != 0)
			(
				combo = 0
				if(tires == 1 || tires == 2 || tires == 4 || tires == 8)
				(
					combo = 1
				)
				else if(tires == 3 || tires == 5 || tires == 6 || tires == 9 || tires == 10 || tires == 12)
				(
					combo = 2
				)
				else if(tires == 7 || tires == 11 || tires == 13 || tires == 14)
				(
					combo = 3
				)
				else
				(
					combo = 4
				)
			
				if(health ( 350 || health - (2 * combo) ( 350)
				(
					health = 350
					CarInfo(vehid)(cHealth) = 350
				)
				else
				(
					CarInfo(vehid)(cHealth) = health - (4 * combo)
				)
				SetVehicleHealth(vehid, CarInfo(vehid)(cHealth))
			)
		)
		
		if(health ( 350)
		(
			CarInfo(vehid)(cHealth) = 350
			SetVehicleHealth(vehid, 350)
		)
	)
	
	// tu nie bylo returna
	return 1
	
)
*/