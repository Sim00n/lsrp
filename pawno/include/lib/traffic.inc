
// Nie forwardowaæ, to nowa funkcja 0.3z - wiêc jak siê ma stary kompilator to wyrzuci b³¹d o braku forwarda - ZIGNOROWAÆ
public OnIncomingConnection(playerid, ip_address(), port)
(
	SendRconCommand(reloadbans)
	return 1
)

public OnPlayerRequestClass(playerid, classid)
(
	if(Logged(playerid))
	(
		SpawnPlayer(playerid)
		return 1
	)
	return 1
)

public OnPlayerConnect(playerid)
(
	printf(OnPlayerConnect, %d, playerid)
	ClearCache(playerid)
	SetPlayerVirtualWorld(playerid, 54321)
	PlayerCache(playerid)(pLogTime) = gettime()
	gettime(LoginTime(playerid)(0), LoginTime(playerid)(1), LoginTime(playerid)(2))
	
	// BOTY!!
	if(IsPlayerNPC(playerid))
	(
		ip(64)
		GetPlayerIp(playerid, ip, sizeof(ip))
		if(strcmp(127.0.0.1, ip) != 0)
		(
			// Jakiœ bot spoza LS-RP
			Kick(playerid)
			return 1
		)
		
		npcname(MAX_PLAYER_NAME)
		GetPlayerName(playerid, npcname, sizeof(npcname))
		
		format(PlayerCache(playerid)(pName), 24, %s, npcname)
		printf((bot) do gry podlaczono bota (ID: %d), playerid)
		PlayerCache(playerid)(pGamePoints) = 100
		SetPlayerScore(playerid, PlayerCache(playerid)(pGamePoints))
		LogTime(playerid) = gettime() - 20
		Spawned(playerid) = true
		Logged(playerid) = true
		return 1
	)
	// KONIEC BOTÓW W £¥CZENIU
	
	InitFly(playerid) 
	InitDive(playerid)
	RemoveAttachedShit(playerid)
	
	SetPlayerCameraPos(playerid, 1129.1959,-1489.5917,25.7690)
	SetPlayerCameraLookAt(playerid, 1128.8148,-1446.8660,15.7981)
	CameraFirstPerson(playerid) = CreateObject(19300, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)

	
	test(64)
    GetPlayerVersion(playerid, test, sizeof(test))
    format(test, sizeof(test), V: %s, test)
	for(i = strlen(test)i)=0i--) if(test(i) == %) test(i) = #
    SendClientMessage(playerid, 0xFFFFFFFF, test)
	
	TextDrawHideForPlayer(playerid, Text:TextDrawHitscreen(playerid))
	
	// Launcher
	if(IsLauncherLog(playerid))
	(
		LogPlayerByLauncher(playerid)
		return 1
	)
	
	
	// Sprawd?, czy konto istnieje w bazie
	data(32)
	mysql_query_format(SELECT char_uid, char_gid FROM hrp_characters WHERE BINARY char_name LIKE %s LIMIT 1, PlayerOriginalName(playerid))
	
	printf((mysql) Zaczynam sprawdzaæ gracza %s w bazie danych..., PlayerRealName(playerid))

	mysql_store_result()
	if(mysql_fetch_row(data, |))
 	(
  		sscanf(data, p(|)dd, PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))
		ClearChat(playerid)
	)
 	else
  	(
   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystšpi³ b³šd, Nie posiadasz u nas konta, za³ó¿ je na WEB_URL., OK, )

		printf((mysql) Gracz %s nie zosta³ odnaleziony w bazie danych - zostaje wyrzucony z serwera., PlayerRealName(playerid))
		Kick(playerid)
	)
	mysql_free_result()
	
	string(64)
	format(string, sizeof(string), RPUSH lsrp_connect_queue %d, PlayerCache(playerid)(pGID))
	//redis_command(string)
	CheckBans(playerid)
	
	// To miejsce dla odbanowanych za czity, ¿eby mogli wchodziæ wy³¹cznie przez launcher na serwer.
/*	if(PlayerCache(playerid)(pGID) == 000000)
	(
		printf((kick)(cheater) wyrzucono GID: %d bo jest na blackliscie, PlayerCache(playerid)(pGID))
		Kick(playerid)
	)
*/
	if(!IsGlobalLogged(PlayerCache(playerid)(pGID)))
	(
		TogglePlayerSpectating(playerid, true)	
		printf((mysql) Gracz %s (UID: %d, GID: %d) zosta³ odnaleziony w bazie danych - przechodzê do logowania., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))

		passIP(16), bool:done
		GetPlayerIp(playerid, passIP, sizeof(passIP))
		
		mysql_query_format(SELECT user_login, user_admin, user_premium, user_premium_time, user_gamepoints, user_color FROM live_users WHERE user_id = %d AND user_loginpass ) %d AND user_loginip = %s LIMIT 1, PlayerCache(playerid)(pGID), gettime(), passIP)
		mysql_store_result()
		if(mysql_fetch_row(data, |))
		(
			printf((log) Logowanie gracza %s (UID: %d, GID: %d) przebieg³o pomy?lnie., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))

			sscanf(data, p(|)s(64)ddddd, PlayerCache(playerid)(pGlobalName), PlayerCache(playerid)(pAdmin), PlayerCache(playerid)(pPremium), PlayerCache(playerid)(pPremiumTime), PlayerCache(playerid)(pGamePoints), PlayerCache(playerid)(pUserColor))
			AddPlayerLoginLog(playerid, true)
			
			done = true
			Logged(playerid) = true
		)
		else
		(
			done = false
		)
		mysql_free_result()
		
		if(done) OnPlayerLogin(playerid)
		else ShowPlayerDialog(playerid, D_LOGIN, DIALOG_STYLE_PASSWORD, Panel logowania, Witaj na serwerze SERVER_NAME.\nWprowadz haslo do konta, aby moc rozpoczac gre., Zaloguj, WyjdŸ)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystšpi³ b³šd, Obecnie na serwerze zalogowana jest ju¿ jaka? postaæ z tego konta globalnego., OK, )
		Kick(playerid)
	)
	
	initializePlayerTextDraws(playerid)	
	InitLSPadTDForPlayer(playerid)
	SetThirdPerson(playerid, 1)
	
	return 1
)

public OnPlayerLogin(playerid)
(
	if(!Logged(playerid)) (
		printf(Kicking %d bo przeszedl do OnPlayerLogin bez zalogowania., playerid)
		Kick(playerid)
	)

	printf(OnPlayerLogin, %d, playerid)
	StatsProtection(playerid) = gettime()
	
	if(Uid(PlayerCache(playerid)(pUID)) + 20 ) gettime())
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystšpi³ b³šd, Nie czaruj mi tu ..., OK, )
		SendClientMessage(playerid, COLOR_WHITE, Nie czaruj mi tu ...)
		Kick(playerid)
		return 0
	)
	
	Uid(PlayerCache(playerid)(pUID)) = true
	LogTime(playerid) = gettime()
	
	string(256), data(1024), tick_count = GetTickCount(), nulled, nulleds(32)
	mysql_query_format(SELECT * FROM hrp_characters WHERE char_uid = %d LIMIT 1, PlayerCache(playerid)(pUID))
	
 	printf((load) Rozpoczynam proces wczytywania statystyk gracza %s (UID: %d, GID: %d)..., PlayerName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID))

	mysql_store_result()
 	if(mysql_fetch_row(data, |))
  	(
		sscanf(data, p(|)dds(24)dddfddddddddddddfffdddffffffddddddddddddddds(32)ddddddfddddddddddddd,
		PlayerCache(playerid)(pUID),
		PlayerCache(playerid)(pGID),

		PlayerCache(playerid)(pName),

		PlayerCache(playerid)(pHours),
		PlayerCache(playerid)(pMinutes),

		PlayerCache(playerid)(pSkin),
		PlayerCache(playerid)(pHealth),

		PlayerCache(playerid)(pSex),
		PlayerCache(playerid)(pBirth),

		PlayerCache(playerid)(pCash),
		PlayerCache(playerid)(pBankCash),
		PlayerCache(playerid)(pBankNumber),
		
		nulled,

		PlayerCache(playerid)(pInt),
		PlayerCache(playerid)(pVW),
		PlayerCache(playerid)(pBW),
		
		nulled,

		PlayerCache(playerid)(pCrash),

		nulled,

		PlayerCache(playerid)(pPosX),
		PlayerCache(playerid)(pPosY),
		PlayerCache(playerid)(pPosZ),
		PlayerCache(playerid)(pHotel),

		PlayerCache(playerid)(pPDP),
		PlayerCache(playerid)(pDocuments),

		PlayerCache(playerid)(pDriving),
		PlayerCache(playerid)(pCondition),
		PlayerCache(playerid)(pShooting),
		PlayerCache(playerid)(pFishing),
		PlayerCache(playerid)(pStrength),
		
		PlayerCache(playerid)(pDependence),

		PlayerCache(playerid)(pLastPay),
		PlayerCache(playerid)(pJob),

		PlayerCache(playerid)(pArrest),
		PlayerCache(playerid)(pArrestTime),
		
		PlayerCache(playerid)(pSpawnPlace),
		PlayerCache(playerid)(pHouse),

		PlayerCache(playerid)(pFightingStyle),

		PlayerCache(playerid)(pWalkAnim),
		PlayerCache(playerid)(pFed),
		nulled,
		nulled,
		nulled,
		PlayerCache(playerid)(pRegion),
		PlayerCache(playerid)(pKnownStyles),
		PlayerCache(playerid)(pDailyReps),
		nulleds,
		PlayerCache(playerid)(pWounded),
		PlayerCache(playerid)(pChecksum),
		nulled,
		nulled,
		PlayerCache(playerid)(pWiretap),
		PlayerCache(playerid)(pInterface),
		nulled,
		nulled,
		PlayerCache(playerid)(pDailyIncome),
		PlayerCache(playerid)(pStation), 
		PlayerCache(playerid)(pArrestDay),
		PlayerCache(playerid)(pDailyDrugs),
		PlayerCache(playerid)(pAASlot),
		PlayerCache(playerid)(pBleeding),
		PlayerCache(playerid)(pInsurance),
		PlayerCache(playerid)(pInsuranceCompany),
		PlayerCache(playerid)(pInsuranceCount),
		PlayerCache(playerid)(pFamilyHouse),
		PlayerCache(playerid)(pWorkRepeat),
		PlayerCache(playerid)(pFCK))
	)
 	mysql_free_result()
	
	
	PlayerCache(playerid)(pAdminToken) = false
	PlayerCache(playerid)(pVehCollisions) = 0
	PlayerCache(playerid)(pFueling) = false
	PlayerCache(playerid)(pBlockShooting) = 0
	PlayerCache(playerid)(pCookID) = -1
	PlayerCache(playerid)(pStation) = 0
	
	LoadPlayerPunish(playerid)

	printf((load) Proces wczytywania statystyk gracza %s (UID: %d, GID: %d) zosta³ zakoñczony (czas trwania: %d ms)., PlayerName(playerid), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID), GetTickCount() - tick_count)
	mysql_query_format(UPDATE hrp_characters, members SET member_online = 1, char_online = 1 WHERE member_gid = %d AND char_uid = %d, PlayerCache(playerid)(pGID), PlayerCache(playerid)(pUID))

	mysql_query_format(INSERT INTO hrp_ingame (uid, gid, tin) VALUES(%d, %d, %d), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pUID), gettime())
	PlayerCache(playerid)(pIGDBID) = mysql_insert_id()
	
	// Czas spêdzony w grze
	mysql_query_format(INSERT INTO hrp_ingame VALUES(NULL, %d, %d, %d, 0, 0), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID), gettime())
	result_id = mysql_insert_id()
	PlayerCache(playerid)(pIGDBID) = result_id

	PlayerCache(playerid)(pIGTimeIn) = gettime()

	format(string, sizeof(string), %s (%d), PlayerName(playerid), playerid)
	Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
	Attach3DTextLabelToPlayer(Text3D:PlayerCache(playerid)(pNameTag), playerid, 0.0, 0.0, 0.2)

	if(PlayerCache(playerid)(pPremium))
	(
		if(gettime() ) PlayerCache(playerid)(pPremiumTime))
		(
			PlayerCache(playerid)(pPremium) = 0
			mysql_query_format(UPDATE live_users SET user_premium_time = 0 AND user_premium = 0 WHERE user_id = %d LIMIT 1, PlayerCache(playerid)(pGID))

			SetPlayerColor(playerid, COLOR_GREY)
		)
		else
		(
			SetPlayerColor(playerid, COLOR_WHITE)
			
			// Usuwamy na czas dodawania specjalnych guwien, radia
			//TextDrawShowForPlayer(playerid, Text:TextDrawPremium)
		)
	)
	else
	(
		SetPlayerColor(playerid, COLOR_GREY)
	)
	
	Float:health
	GetPlayerHealth(playerid, health)
	if(health ( 0)
	(
		hrp_SetPlayerHealth(playerid, 20)
	)
	
	// Je?li zablokowane konto
	if(PlayerCache(playerid)(pBlock) & BLOCK_CHAR)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postaæ zosta³a zablokowana, powód znajdziesz w panelu na stronie.\nZa³ó¿ nowš lub ubiegaj siê o odblokowanie poprzedniej., OK, )
		Kick(playerid)
		return 1
	)
	
	// Nalicz zespawnowane pojazdy gracza i przypisz pod niego
	foreach(Vehicles, vehid)
	(
		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) == PlayerCache(playerid)(pUID) && CarInfo(vehid)(cSpawned))
		(
			CarInfo(vehid)(cOwnerExitTime) = 0
			PlayerCache(playerid)(pCarSpawned) ++
			if(!PlayerCache(playerid)(pPremium))
			(
				if(PlayerCache(playerid)(pCarSpawned) )= STANDARD_VEHICLES)
				(
					break
				)
			)
			else
			(
				if(PlayerCache(playerid)(pCarSpawned) )= PREMIUM_VEHICLES)
				(
					break
				)
			)
		)
	)
	
	GangZonesShow(playerid)
	PlayerCache(playerid)(pGangZoneShowing) = true
   	//for(w = 0 w ( 10 w++) ( SetPlayerSkillLevel(playerid, w, 1000) )
   	
	UpdateNativeWeaponSkills(playerid)
	
	SetPlayerVirtualWorld(playerid, 0)
	
	SetPlayerFightingStyle(playerid, PlayerCache(playerid)(pFightingStyle))
	SetPlayerScore(playerid, PlayerCache(playerid)(pGamePoints))

	LoadPlayerItems(playerid)
	LoadPlayerGroups(playerid)
	
	TextDrawShowForPlayer(playerid, Text:TextDrawTemperature)
	TextDrawShowForPlayer(playerid, Text:TextDrawSanNews)
	TextDrawShowForPlayer(playerid, Text:TextDrawServerLogo)
	
	TogglePlayerSpectating(playerid, false)
	SpawnPlayer(playerid)
	
	Logged(playerid) = true
	
	SetSpawnInfo(playerid, TEAM_DEFAULT, PlayerCache(playerid)(pSkin), SettingData(MainSpawnPos)(0), SettingData(MainSpawnPos)(1), SettingData(MainSpawnPos)(2), SettingData(MainSpawnPos)(3), 0, 0, 0, 0, 0, 0)
	SendClientFormatMessage(playerid, 0xF5DEB3FF, Witaj, (FFFFFF)%s(F5DEB3). Zalogowaleœ siê na postaæ (FFFFFF)%s(F5DEB3). Milej gry!, PlayerCache(playerid)(pGlobalName), PlayerName(playerid))

	if(PlayerCache(playerid)(pAdmin) ) 0)
	(
		GameTextForPlayer(playerid, ~w~~n~~n~~n~Zalogowany jako ~g~admin, 5000, 4)
	)
	else if(PlayerCache(playerid)(pAdmin) ( 0)
	(
		GameTextForPlayer(playerid, ~w~~n~~n~~n~Zalogowany jako ~b~support, 5000, 4)
	)
	
	if(PlayerCache(playerid)(pAdmin) != 0)
	(
		TextDrawShowForPlayer(playerid, Text:TextDrawAdminLog)
	)
		
	GetPlayerAnns(playerid)
	
	getPlayerOfflineMessages(playerid)
	
	setDoorActivity(playerid)

	setVehiclesActivity(playerid)
	
	RemoveBuildings(playerid)
	
	hrp_SerialLog(Gracz %s (UID: %d) zalogowal sie z GPCI: %s, PlayerName(playerid), PlayerCache(playerid)(pUID), getPlayerSerial(playerid))
	
	PrintPlayerOfflineMessages(playerid)		// wiadomoœci offline
	
	GetPlayerFameStatus(playerid)
	
	// Sprawdzanie przekrêtów z kasš
	if(CheckSumCheck)
	(
		if(PlayerCache(playerid)(pChecksum) != (((((PlayerCache(playerid)(pCash) + PlayerCache(playerid)(pBankCash)) + 31) * 3) + PlayerCache(playerid)(pUID)) + 3))
		(
			/*info(256)
			format(info, sizeof(info), Zostajesz zabnowany poniewa¿ istnieje powa¿ne prawdopodobnieñstwo pozasystemowej manipulacji\nstatystykami Twojej postaci. Zrób zrzut ekranu z tej informacji i za³šcz do apelacji.\n\n#aod: %d\n#dle: %d\n#oem: %d, (((PlayerCache(playerid)(pCash) + 6) * 6) * 4), (((PlayerCache(playerid)(pBankCash) + 3) * 2) * 5), (((PlayerCache(playerid)(pChecksum) + 133) * -3) * 3))
		
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, info, OK, )
			hrp_Ban(playerid, -1, Pozasystemowa manipulacja statystykami., 0)*/
			
			info(256)
			format(info, sizeof(info), (ARCZIRPEDAL) Gracz %s ma %d przy sobie, %d w banku, i checksume: %d. Sprawdzenie gnoja pokazuje ze cheatuje., PlayerName(playerid), PlayerCache(playerid)(pCash), PlayerCache(playerid)(pBankCash), PlayerCache(playerid)(pChecksum))
			//print(info)
			PlayerCache(playerid)(pBlockChecksum) = 1
			return 1
		)
	)
	
	return 1
)

public OnPlayerDisconnect(playerid, reason)
(
	SavePlayerStats(playerid, SAVE_PLAYER_BASIC | SAVE_PLAYER_SKILLS)
	printf(Zapisuje %d po hotfixie LSRP_PR_020314, PlayerCache(playerid)(pUID))
	
	DestroyObject(CameraFirstPerson(playerid))
	
	if(PlayerCache(playerid)(pCourseVeh) != INVALID_VEHICLE_ID)
	(
		courseveh = PlayerCache(playerid)(pCourseVeh)
		ChangeVehicleEngineStatus(courseveh, 0)
		CarInfo(courseveh)(cEngineTogged) = false
		SetVehicleToRespawn(courseveh)
		UpdateVehicleDamageStatus(courseveh, CarInfo(courseveh)(cVisual)(0), CarInfo(courseveh)(cVisual)(1), CarInfo(courseveh)(cVisual)(2), CarInfo(courseveh)(cVisual)(3))
		CarInfo(courseveh)(cHealth) = 1000.0
		SetVehicleHealth(courseveh, CarInfo(courseveh)(cHealth))
	)
	
	// Zamknij okno speca, jeœli ktoœ go specuje
	for(i = 0  i ( MAX_PLAYERS i++)
	(
		if(PlayerCache(i)(pSpectate) == playerid)
		(
			PlayerTextDrawHide(PlayerCache(i)(pSpectate), AdminSpecInfo(PlayerCache(i)(pSpectate)))
			PlayerTextDrawHide(PlayerCache(i)(pSpectate), AdminSpecStats(PlayerCache(i)(pSpectate)))
			break
		)
	)
	
	// dodaj tutaj zapis g³odu i dailyincome i dailydrugs
	mysql_query_format(UPDATE hrp_characters SET char_dailyincome = %d, char_dailydrugs = %d WHERE char_uid = %d, PlayerCache(playerid)(pDailyIncome), PlayerCache(playerid)(pDailyDrugs), PlayerCache(playerid)(pUID))
	
	Uid(PlayerCache(playerid)(pUID)) = gettime()
	LogTime(playerid) = 0
	SpawnTime(playerid) = 0
	
	if(PlayerCache(playerid)(pReconnect))
	(
		string(128)
		format(string,sizeof(string),unbanip %s, playerIP(playerid))
		SendRconCommand(string)
		
		SendRconCommand(reloadbans)
	)
	
	if(IsValidDynamicObject(PutableObject(playerid)(pObjID)))
	(
		DestroyDynamicObject(PutableObject(playerid)(pObjID))
		PutableObject(playerid)(pObjID) = INVALID_OBJECT_ID
		PutableObject(playerid)(pObjUID) = EOS
		PutableObject(playerid)(pObjVW) = EOS
		PutableObject(playerid)(pObjOwner) = EOS 		
	)
	
	if(PlayerCache(playerid)(pSlots))
	(
		slots_EndGame(playerid,PlayerCache(playerid)(pSlotID))
	)
	
	for(i = 0  i ( MAX_SURFBOARDS i++)
	(
		if(PlayerCache(playerid)(pSurfID) != INVALID_SURFBOARD_ID)
		(
			surf_DestroySurfboard(PlayerCache(playerid)(pSurfID))
			break
		)
	)
	
	if(IsValidDynamicObject(PlayerCache(playerid)(pBasketBall)))
	(
		DestroyDynamicObject(PlayerCache(playerid)(pBasketBall))
	)

	string(128)
	format(string, sizeof(string), RPUSH lsrp_disconnect_queue %d, PlayerCache(playerid)(pGID))
	//redis_command(string)

	PlayerCache(playerid)(pLogTime) = 0
	
 	Float:PosX, Float:PosY, Float:PosZ,
 		VirtualWorld, InteriorID

	GetPlayerPos(playerid, PosX, PosY, PosZ)

	VirtualWorld = GetPlayerVirtualWorld(playerid)
 	InteriorID = GetPlayerInterior(playerid)
	
	
	PlayerCache(playerid)(pCrash) = (PlayerCache(playerid)(pQSing))? 1 : 0
	
	if(reason == 0)
	(
		//format(string, sizeof(string), (( %s - timeout )), PlayerRealName(playerid))
	
		PlayerCache(playerid)(pPosX) = PosX
		PlayerCache(playerid)(pPosY) = PosY
		PlayerCache(playerid)(pPosZ) = PosZ
		
		PlayerCache(playerid)(pVW) = VirtualWorld
		PlayerCache(playerid)(pInt) = InteriorID
		
		PlayerCache(playerid)(pQSing) = 1
		PlayerCache(playerid)(pCrash) = 1
		SavePlayerStats(playerid, SAVE_PLAYER_POS)
		
		PlayerCache(playerid)(pQuit) = QUIT_TIMEOUT
	)
	else if(reason == 1)
	(
		//format(string, sizeof(string), (( %s - /q )), PlayerRealName(playerid))
		PlayerCache(playerid)(pQuit) = QUIT_Q
	)
	else if(reason == 2)
	(
		PlayerCache(playerid)(pQuit) = QUIT_KICK
	)
	
	// BALOLOL
	//CreateQuitLabel(playerid)
	CreateAltQuitLabel(playerid)

	foreach(Vehicles, vehid)
	(
		if(CarInfo(vehid)(cUID))
		(
			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) == PlayerCache(playerid)(pUID))
			(
				driver_id = GetVehicleDriver(vehid)
				if(driver_id == playerid || driver_id == INVALID_PLAYER_ID)
				(
	   				CarInfo(vehid)(cLocked) = true
		  			SetVehicleLock(vehid, CarInfo(vehid)(cLocked))

					if(CarInfo(vehid)(cEngineTogged))
					(
						CarInfo(vehid)(cEngineTogged) = false
						ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))
					)

					SaveVehicle(vehid, SAVE_VEH_COUNT | SAVE_VEH_LOCK)
				)
				CarInfo(vehid)(cOwnerExitTime) = gettime()
			)
		)
	)
	
	foreach (Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			// Oferta
			if(Offer(i)(oCustomerID) == playerid)
			(
				format(string, sizeof(string), ~w~Gracz ~p~%s ~r~odrzucil ~w~Twoja oferte., PlayerName(playerid))
				GameTextForPlayer(i, string, 4000, 3)

				hrp_OfferActionLog(Gracz %s (UID: %d) odrzucil oferte gracza %s (UID: %d). Typ oferty: %s, wartosc: %d, cena: %d, PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerRealName(i), PlayerCache(i)(pUID), OfferTypeInfo(Offer(i)(oType))(oTypeName), Offer(i)(oValue), Offer(i)(oPrice))

				Offer(i)(oCustomerID)	= INVALID_PLAYER_ID
				Offer(i)(oType)  		= 0
				Offer(i)(oValue) 		= 0

				Offer(i)(oPrice) 		= 0
				Offer(i)(oPayType) 		= PAYTYPE_NONE
			)
		
			// Skuty
			if(PlayerCache(i)(pCuffed) == playerid)
			(
				PlayerCache(i)(pCuffed) = INVALID_PLAYER_ID
			)
			
			// Zakuty
			if(PlayerCache(i)(pCuffedStill) == playerid)
			(
				PlayerCache(i)(pCuffedStill) = INVALID_PLAYER_ID
			)
			
			// Przeszukuje
			if(PlayerCache(i)(pSearches) == playerid)
			(
				PlayerCache(i)(pSearches) = INVALID_PLAYER_ID
				PlayerCache(i)(pSearchTime) = 0
			)
			
			// Leczy
			if(PlayerCache(i)(pHealing) == playerid)
			(
				PlayerCache(i)(pHealing) = INVALID_PLAYER_ID
			)
			
			PlayerCache(i)(pPlayerIgnored)(playerid) = false
		)
	)
	
	// Je?li na s³u¿bie grupy
	if(PlayerCache(playerid)(pGroupDuty))
	(
		group_id_fix = GetPlayerDutyGroupID(playerid),
	 		duty_time = (gettime() - PlayerCache(playerid)(pGroupDutyTime)) / 60

		if(group_id_fix != -1)
		(
			if(GroupData(group_id_fix)(gUID))
			(
				GroupData(group_id_fix)(gActivity) += duty_time
				SaveGroup(group_id_fix)
				
				OnPlayerDutyStop(playerid)
			)
		)
	)
	
	// czy aby na pewno? :D
	if(PlayerCache(playerid)(pAdminDuty))
	(
		OnPlayerDutyStop(playerid)
	)

	// Je?li by³ w poje?dzie
	if(PlayerCache(playerid)(pLastVeh) != INVALID_VEHICLE_ID)
	(
		vehid = PlayerCache(playerid)(pLastVeh)

		// W³šczony GPS
		if(CarInfo(vehid)(cGPS))
		(
  			for (i = 0 i (= CountDynamicMapIcons() i++)
		 	(
				if(IsValidDynamicMapIcon(i))
 				(
				 	if(Streamer_IsInArrayData(STREAMER_TYPE_MAP_ICON, i, E_STREAMER_PLAYER_ID, playerid))
				  	(
				  		DestroyDynamicMapIcon(i)
				   	)
				)
			)
		)
	)
	
	
	if(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
	(
		itemid = GetItemID(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo)
		
		mysql_query_format(UPDATE hrp_items SET item_used = 0, item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
	)
	
	if(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
	(
		itemid = GetItemID(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo)
		
		mysql_query_format(UPDATE hrp_items SET item_used = 0, item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
	)
	
	if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
	(
		itemid = GetItemID(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo)
		
		mysql_query_format(UPDATE hrp_items SET item_used = 0, item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
	)
	
	// Je?li ma kamizelkê w u¿yciu
	if(PlayerCache(playerid)(pArmour))
	(
		itemid = GetPlayerUsingArmourID(playerid)
  		mysql_query_format(UPDATE hrp_items SET item_value1 = %d, item_used = 0 WHERE item_uid = %d LIMIT 1, floatround(PlayerCache(playerid)(pArmour)), ItemInfo(itemid)(iUID))
	)
	
	// Je?li u¿ywa karnetu
	if(PlayerCache(playerid)(pGymPass))
	(
 		itemid = PlayerCache(playerid)(pGymPass)

		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue1) = PlayerCache(playerid)(pTrainTime) / 60

		mysql_query_format(UPDATE hrp_items SET item_used = %d, item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
	)
	
	// Je?li u¿ywa wejsciowki na paintball
	if(PlayerCache(playerid)(pPaintballPass))
	(
 		itemid = PlayerCache(playerid)(pPaintballPass)

		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue1) = PlayerCache(playerid)(pPaintballTime) / 60

		mysql_query_format(UPDATE hrp_items SET item_used = %d, item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUsed), ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))
	)
	
	mysql_query_format(UPDATE hrp_characters, members SET member_online = 0, char_online = 0 WHERE member_gid = %d AND char_uid = %d, PlayerCache(playerid)(pGID), PlayerCache(playerid)(pUID))
	
	// Zabierz kasê za przejechany kurs taksówkš
	if(PlayerCache(playerid)(pTaxiVeh) != INVALID_VEHICLE_ID)
 	(
  		driverid = GetVehicleDriver(PlayerCache(playerid)(pTaxiVeh)), price = PlayerCache(playerid)(pTaxiPay)

		if(price ) 0)
  		(
			price = price ) PlayerCache(playerid)(pCash) ? PlayerCache(playerid)(pCash) : price
  		
  			group_cash = floatround(0.50 * price),
				playercash = floatround(0.50 * price)
		
			hrp_GivePlayerMoney(playerid, -price)
	  		hrp_GivePlayerMoney(driverid, playercash)

			group_id_fix = GetPlayerDutyGroupID(driverid)
			
   			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)
			
			format(string, sizeof(string), Otrzyma³e? premiê w wysoko?ci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(driverid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		)
		PlayerCache(driverid)(pTaxiPassenger) = INVALID_PLAYER_ID
	)
	
	// Zakoñcz transmisje na ¿ywo
	if(PlayerCache(playerid)(pLive))
	(
		group_id_fix = GetPlayerDutyGroupID(playerid), radioslot = GetRadioSlot(group_id_fix)
 		format(string, sizeof(string), %s ~)~ W radiu leci standardowy blok muzyczny., GroupData(group_id_fix)(gTag))
		TextDrawSetString(Text:TextDrawRadio(radioslot), string)
		RadioData(radioslot)(IsUsingRadio) = false
	)
	
	// Zakoñcz wywiad
	if(PlayerCache(playerid)(pInterview) != INVALID_PLAYER_ID)
	(
		interviewer_id = PlayerCache(playerid)(pInterview), radioslot = PlayerCache(playerid)(pInterviewSlot)
		PlayerCache(interviewer_id)(pInterview) = INVALID_PLAYER_ID
		PlayerCache(interviewer_id)(pInterviewSlot) = 0
		
  		format(string, sizeof(string), RADIO ~)~ Ostatni wywiad z %s przeprowadzil %s., PlayerName(interviewer_id), PlayerName(playerid))
		TextDrawSetString(Text:TextDrawRadio(radioslot), string)
		RadioData(radioslot)(IsUsingRadio) = false
		ShowPlayerDialog(interviewer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wywiad zosta³ zakoñczony., OK, )
	)
	
	// Je¿eli by³ w AJ
	if(PlayerCache(playerid)(pAJ))
	(
		mysql_query_format(UPDATE hrp_punishlogs SET punish_value = %d WHERE punish_owneruid = %d AND punish_type = %d, PlayerCache(playerid)(pAJ), PlayerCache(playerid)(pUID), PUNISH_AJ)
	)
	
	isScened(playerid) = 0
	if(sceneDJ == playerid)
		sceneDJ = INVALID_PLAYER_ID

	if(PlayerCache(playerid)(pCall) != -1)
		EndCall(PlayerCache(playerid)(pCall))


	verbose(10)
	v_sum = gettime() - PlayerCache(playerid)(pIGTimeIn)
	v_h =  floatround(v_sum / (60*60), floatround_floor)
	v_m = floatround((v_sum - (v_h*60*60)) / 60, floatround_floor)
	v_s = floatround(v_sum - (v_h*60*60) - (v_m*60))
	format(verbose, sizeof(verbose), %dh%dm%ds, v_h, v_m, v_s)
	//mysql_query_format(UPDATE hrp_ingame SET (tout, verbose) VALUES(%d, %s) WHERE id = %d, gettime(), verbose, PlayerCache(playerid)(pIGDBID))
	//mysql_query_format(UPDATE hrp_ingame SET out = %d, verbose = %s WHERE id = %d, gettime(), verbose, PlayerCache(playerid)(pIGDBID))
	mysql_query_format(UPDATE hrp_ingame SET tout = %d, verbose = %s WHERE id = %d, gettime(), verbose, PlayerCache(playerid)(pIGDBID))
	
	format(PlayerCache(playerid)(pDescTagText), 128,  )
	
	SavePlayerStats(playerid, SAVE_PLAYER_BASIC | SAVE_PLAYER_SKILLS)
	UnloadPlayerItems(playerid)
	
	Spawned(playerid) = false
	Logged(playerid) = false
	ClearCache(playerid)
	return 1
)

public OnPlayerSpawn(playerid)
(
	printf(OnPlayerSpawn, %d, playerid)
	SpawnTime(playerid) = gettime()
	
	if(!Logged(playerid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystšpi³ b³šd, Aby móc rozpoczšæ grê, musisz siê zalogowaæ.\nZostajesz wyrzucony z serwera., OK, )
		Kick(playerid)
		return 1
	)
	if(!Preloaded(playerid))
	(
   		PreloadAnimLib(playerid, BOMBER)
   		PreloadAnimLib(playerid, RAPPING)
		PreloadAnimLib(playerid, SHOP)
   		PreloadAnimLib(playerid, BEACH)
   		PreloadAnimLib(playerid, SMOKING)
		PreloadAnimLib(playerid, FOOD)
		PreloadAnimLib(playerid, ON_LOOKERS)
		PreloadAnimLib(playerid, DEALER)
		PreloadAnimLib(playerid, CRACK)
		PreloadAnimLib(playerid, CARRY)
		PreloadAnimLib(playerid, COP_AMBIENT)
		PreloadAnimLib(playerid, PARK)
		PreloadAnimLib(playerid, INT_HOUSE)
		PreloadAnimLib(playerid, INT_OFFICE)
		PreloadAnimLib(playerid, FOOD)
		PreloadAnimLib(playerid, PED)
		PreloadAnimLib(playerid, POLICE)
		PreloadAnimLib(playerid, CAR)
		PreloadAnimLib(playerid, CAR_CHAT)
		PreloadAnimLib(playerid, MEDIC)
		PreloadAnimLib(playerid, GANGS)
		PreloadAnimLib(playerid, BENCHPRESS)
		PreloadAnimLib(playerid, HEIST9)
		PreloadAnimLib(playerid, MISC)
		PreloadAnimLib(playerid, OTB)
		PreloadAnimLib(playerid, PAULNMAC)
		PreloadAnimLib(playerid, SWEET)
		PreloadAnimLib(playerid, GRAFFITI)
		PreloadAnimLib(playerid, FIGHT_C)
		PreloadAnimLib(playerid, FIGHT_B)
		PreloadAnimLib(playerid, FIGHT_D)
		PreloadAnimLib(playerid, WAYFARER)
		PreloadAnimLib(playerid, BASEBALL)
		PreloadAnimLib(playerid, GRENADE)
		PreloadAnimLib(playerid, BSKTBALL)
		PreloadAnimLib(playerid, RIOT)

		Preloaded(playerid) = 1
	)
	SetPlayerSpawn(playerid)
	LoadPlayerAccess(playerid)
	PlayerCache(playerid)(pWoundAnim) = false
	PlayerCache(playerid)(pWoundedTime) = 0
	SyncCamera(playerid)
	
	if(IsPlayerInGroupType(playerid, GROUP_CRIMINAL))
	(
		// no niech odœwie¿y wygl¹d minimapki
		HidePlayerAllZones(playerid)
		ShowPlayerAllZones(playerid)
	)
	
	if(IsPlayerNPC(playerid))
	(
		npcname(MAX_PLAYER_NAME)
		GetPlayerName(playerid, npcname, sizeof(npcname))
		
		// Maszynista
		if(!strcmp(npcname, George_Black, true))
		(
			george_tram = INVALID_VEHICLE_ID
			for(i = 0  i ( MAX_VEHICLES i++)
			(
				if(CarInfo(i)(cOwnerType) == OWNER_GROUP && CarInfo(i)(cOwner) == 154)
				(
					if(CarInfo(i)(cModel) == 449)
					(
						george_tram = i
						break
					)
				)
			)
			
			CarInfo(george_tram)(cEngineTogged) = true
			ChangeVehicleEngineStatus(george_tram, CarInfo(george_tram)(cEngineTogged))
			PutPlayerInVehicle(playerid, george_tram, 0)
		)
		
		// Police Maverick
		if(!strcmp(npcname, George_Brown, true))
		(
			george_tram = INVALID_VEHICLE_ID
			for(i = 0  i ( MAX_VEHICLES i++)
			(
				if(CarInfo(i)(cOwnerType) == OWNER_GROUP && CarInfo(i)(cOwner) == 154)
				(
					if(CarInfo(i)(cModel) == 497)
					(
						george_tram = i
						break
					)
				)
			)
			
			CarInfo(george_tram)(cEngineTogged) = true
			ChangeVehicleEngineStatus(george_tram, CarInfo(george_tram)(cEngineTogged))
			PutPlayerInVehicle(playerid, george_tram, 0)
		)
		
		// Dodo
		if(!strcmp(npcname, George_White, true))
		(
			george_tram = INVALID_VEHICLE_ID
			for(i = 0  i ( MAX_VEHICLES i++)
			(
				if(CarInfo(i)(cOwnerType) == OWNER_GROUP && CarInfo(i)(cOwner) == 154)
				(
					if(CarInfo(i)(cModel) == 593)
					(
						george_tram = i
						break
					)
				)
			)
			
			CarInfo(george_tram)(cEngineTogged) = true
			ChangeVehicleEngineStatus(george_tram, CarInfo(george_tram)(cEngineTogged))
			PutPlayerInVehicle(playerid, george_tram, 0)
		)
	)
	
	if(PlayerCache(playerid)(pAdmin) != 0 && !PlayerCache(playerid)(pVerificated) && !DEBUG_MODE)
	(
		//Wy³¹czona autoryzacja g-auth, seler
		//ShowPlayerDialog(playerid, D_VERIFICATE, DIALOG_STYLE_INPUT, Weryfikacja dwuetapowa, Wypisz poni¿ej kod wygenerowany przez aplikacjê Google Authenticator., Gotowe, Anuluj)
	)
	
	return 1
)

public SetPlayerSpawn(playerid)
(
	printf(SetPlayerSpawn, %d, playerid)
	SetPlayerMoney(playerid, PlayerCache(playerid)(pCash))
	SetPlayerSkin(playerid, PlayerCache(playerid)(pSkin))
	
	if(PlayerCache(playerid)(pSpectate) != INVALID_PLAYER_ID)
	(
		hrp_SetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))
		//hrp_SetPlayerPos(playerid, RegionInfo(PlayerCache(playerid)(pRegion))(rPosX), RegionInfo(PlayerCache(playerid)(pRegion))(rPosY), RegionInfo(PlayerCache(playerid)(pRegion))(rPosZ))

		SetPlayerVirtualWorld(playerid, PlayerCache(playerid)(pVW))
		SetPlayerInterior(playerid, PlayerCache(playerid)(pInt))

		PlayerCache(playerid)(pSpectate) = INVALID_PLAYER_ID
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Podglšdanie gracza zosta³o przerwane., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAJ))
	(
		hrp_SetPlayerPos(playerid, 154.1221, -1951.9156, 47.8750)
		
		SetPlayerInterior(playerid, 0)
		SetPlayerVirtualWorld(playerid, playerid + 1000)
		return 1
	)
	if(PlayerCache(playerid)(pBW))
	(
		hrp_SetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))
		
		SetPlayerInterior(playerid, PlayerCache(playerid)(pInt))
		SetPlayerVirtualWorld(playerid, PlayerCache(playerid)(pVW))
		
		SetPlayerCameraPos(playerid, PlayerCache(playerid)(pPosX) + 3, PlayerCache(playerid)(pPosY) + 4, PlayerCache(playerid)(pPosZ) + 7)
		SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

		hrp_TogglePlayerControllable(playerid, 0)
		hrp_SetPlayerHealth(playerid, 20)
		return 1
	)
	if(PlayerCache(playerid)(pArrest))
	(
		cell_id = PlayerCache(playerid)(pArrest) - 1
		
		SetPlayerVirtualWorld(playerid, PoliceCell(cell_id)(pCellVW))
		SetPlayerInterior(playerid, 0)
		hrp_SetPlayerPos(playerid, PoliceCell(cell_id)(pCellX), PoliceCell(cell_id)(pCellY), PoliceCell(cell_id)(pCellZ))
		SetCameraBehindPlayer(playerid)
		
		if(PlayerCache(playerid)(pBW))
		(
			SetPlayerCameraPos(playerid, PlayerCache(playerid)(pPosX) + 3, PlayerCache(playerid)(pPosY) + 4, PlayerCache(playerid)(pPosZ) + 7)
			SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

			hrp_TogglePlayerControllable(playerid, 0)
		)
		else
		(
			TogglePlayerControllable(playerid, false)
			PlayerCache(playerid)(pDoorFreeze) = 5
		)
		
		if(PlayerCache(playerid)(pArrestTime) (= 1)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twój wyrok dobieg³ koñca.\nTeraz mo¿esz opuœciæ areszt podchodz¹c do wyjœcia i u¿ywaj¹c komendy /opusc, b¹dŸ pozostaæ i graæ dalej tutaj.\nMi³ej gry!, OK, )
		)
		
		return 1
	)
	if(PlayerCache(playerid)(pPaintballPass))
	(
		doorid = GetPlayerDoorID(playerid)
		hrp_SetPlayerPos(playerid, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ))
		
		SetPlayerInterior(playerid, PlayerCache(playerid)(pInt))
		SetPlayerVirtualWorld(playerid, PlayerCache(playerid)(pVW))
		
		hrp_SetPlayerHealth(playerid, 100)
		return 1
	)
	if(PlayerCache(playerid)(pCrash))
	(
 		hrp_SetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

		SetPlayerInterior(playerid, PlayerCache(playerid)(pInt))
		SetPlayerVirtualWorld(playerid, PlayerCache(playerid)(pVW))
		
		SetCameraBehindPlayer(playerid)
		
		PlayerCache(playerid)(pCrash) = 0
		
		TogglePlayerControllable(playerid, false)
		PlayerCache(playerid)(pDoorFreeze) = 3
		return 1
	)
	if(PlayerCache(playerid)(pSpawnPlace) == SPAWN_HOUSE)
	(
		if(PlayerCache(playerid)(pHouse))
		(
			house_id = GetDoorID(PlayerCache(playerid)(pHouse))
			
			hrp_SetPlayerPos(playerid, DoorData(house_id)(dExitX), DoorData(house_id)(dExitY), DoorData(house_id)(dExitZ))
			SetPlayerFacingAngle(playerid, DoorData(house_id)(dExitAng))

			SetPlayerInterior(playerid, DoorData(house_id)(dExitInt))
			SetPlayerVirtualWorld(playerid, DoorData(house_id)(dExitVW))

			SetCameraBehindPlayer(playerid)

			TogglePlayerControllable(playerid, false)
			PlayerCache(playerid)(pDoorFreeze) = 3
		)
		else
		(
 			hrp_SetPlayerPos(playerid, SettingData(MainSpawnPos)(0), SettingData(MainSpawnPos)(1), SettingData(MainSpawnPos)(2))
			SetPlayerFacingAngle(playerid, SettingData(MainSpawnPos)(3))

			SetPlayerInterior(playerid, SettingData(MainSpawnInt))
			SetPlayerVirtualWorld(playerid, SettingData(MainSpawnVW))

			SetCameraBehindPlayer(playerid)
		)
		return 1
	)
	if(PlayerCache(playerid)(pSpawnPlace) == SPAWN_FAMILYHOUSE)
	(
		if(PlayerCache(playerid)(pFamilyHouse))
		(
			familyhouse_id = GetDoorID(PlayerCache(playerid)(pFamilyHouse))
			
			hrp_SetPlayerPos(playerid, DoorData(familyhouse_id)(dExitX), DoorData(familyhouse_id)(dExitY), DoorData(familyhouse_id)(dExitZ))
			SetPlayerFacingAngle(playerid, DoorData(familyhouse_id)(dExitAng))

			SetPlayerInterior(playerid, DoorData(familyhouse_id)(dExitInt))
			SetPlayerVirtualWorld(playerid, DoorData(familyhouse_id)(dExitVW))

			SetCameraBehindPlayer(playerid)

			TogglePlayerControllable(playerid, false)
			PlayerCache(playerid)(pDoorFreeze) = 3
		)
		else
		(
 			hrp_SetPlayerPos(playerid, SettingData(MainSpawnPos)(0), SettingData(MainSpawnPos)(1), SettingData(MainSpawnPos)(2))
			SetPlayerFacingAngle(playerid, SettingData(MainSpawnPos)(3))

			SetPlayerInterior(playerid, SettingData(MainSpawnInt))
			SetPlayerVirtualWorld(playerid, SettingData(MainSpawnVW))

			SetCameraBehindPlayer(playerid)
		)
		return 1
	)
	if(PlayerCache(playerid)(pSpawnPlace) == SPAWN_HOTEL)
	(
		if(PlayerCache(playerid)(pHotel))
		(
			hotel_door_id = GetDoorID(PlayerCache(playerid)(pHotel))
			if(hotel_door_id != -1)
			(
				group_id_fix = GetGroupID(DoorData(hotel_door_id)(dOwner)),
					val2 = GroupData(group_id_fix)(gValue2)
					
				hrp_SetPlayerPos(playerid, Interiors(val2)(INTERIOR_X), Interiors(val2)(INTERIOR_Y), Interiors(val2)(INTERIOR_Z))
				SetPlayerFacingAngle(playerid, Interiors(val2)(INTERIOR_A))

				SetPlayerInterior(playerid, Interiors(val2)(INTERIOR_ID))
				SetPlayerVirtualWorld(playerid, PlayerCache(playerid)(pUID))
				
				SetCameraBehindPlayer(playerid)

				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~w~Aby wyjsc z pokoju uzyj komendy ~r~/pokoj wyjdz, 4000, 3)
				return 1			
			)
		)
	)

 	hrp_SetPlayerPos(playerid, RegionInfo(PlayerCache(playerid)(pRegion))(rPosX), RegionInfo(PlayerCache(playerid)(pRegion))(rPosY), RegionInfo(PlayerCache(playerid)(pRegion))(rPosZ))
	SetPlayerFacingAngle(playerid, SettingData(MainSpawnPos)(3))

	SetPlayerInterior(playerid, SettingData(MainSpawnInt))
	SetPlayerVirtualWorld(playerid, SettingData(MainSpawnVW))
	
	SetCameraBehindPlayer(playerid)
	
	if(PlayerCache(playerid)(pHours) ( 1)	ShowPlayerDialog(playerid, D_INTRODUCTION, DIALOG_STYLE_MSGBOX, Wprowadzenie (1/2), Witaj na serwerze SERVER_NAME.\n\nPojawi³eœ siê w metrze Los Santos, na mieœcie znajdziesz wiele ró¿nego rodzaju\ninstytucji, dziêki którym bêdziesz móg³ przyj¹æ siê do pracy\na tak¿e skorzystaæ z ich us³ug np. kupiæ telefon, b¹dŸ zjeœæ obiad.\n\nNa pierwszy etat udaj siê do urzêdu miasta, by wyrobiæ dokumenty niezbêdne do gry., Dalej, Zamknij)
	return 1
)

public OnPlayerDeath(playerid, killerid, reason)
(
	// paintball
	if(PlayerCache(playerid)(pPaintballPass))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Zosta³eœ trafiony podczas gry w paintball.\nWróci³eœ siê na miejsce rozpoczêcia gry., OK, )
		hrp_SetPlayerHealth(playerid, 100)
		hrp_SetPlayerHealth(playerid, 100)
		
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
		
		GetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))
		
		PlayerCache(playerid)(pInt) = GetPlayerInterior(playerid)
		PlayerCache(playerid)(pVW) = GetPlayerVirtualWorld(playerid)
		
		SavePlayerStats(playerid, SAVE_PLAYER_POS)
		return 1
	)
	printf(playerid %d, killer %d, reason %d, playerid, killerid, reason)
	if(killerid != INVALID_PLAYER_ID)
	(
		print(1)
		if(PlayerCache(playerid)(pBW) (= 0)
		(
			print(2)
			if(PlayerCache(killerid)(pHours) )= 10)
			(
				if(PlayerCache(playerid)(pArrest))
				(
					PlayerCache(playerid)(pBW) = 5 * 60
				) else (
					PlayerCache(playerid)(pBW) = 10 * 60
				)

				if(PlayerCache(playerid)(pFCK) ) gettime() && !PlayerCache(playerid)(pSparing))
				(
					string(768)
					format(string, sizeof(string), Na skutek otrzymanych obra¿eñ, straci³eœ przytomnoœæ.\n\n)
					format(string, sizeof(string), %sGamemaster zaakceptowal podanie o CK na glowe Twojej postaci.\n, string)
					format(string, sizeof(string), %sPonizej zdecyduj czy ta smierc byla wynikiem buga czy tez prawidlowym zabojstwem.\n, string)
					format(string, sizeof(string), %sJezeli ta smierc wynika z buga typu skakanie przez plotki czy budowanie interiorow, kliknij \anuluj\.\n, string)
					format(string, sizeof(string), %sW przeciwnym wypadku zaakcpetuj smierc postac.\n, string)
					format(string, sizeof(string), %sPS \noby zrobily db\ nie kwalifikuje sie jako powod do anulowania. To zglos na forum po smierci.\n, string)
					format(string, sizeof(string), %s(ff0000)UWAGA: Jezeli klikniesz \anuluj\, sprawa zainteresuje sie administrator.\n, string)
					format(string, sizeof(string), %s\nKLAMSTWO PRZY WYBORZE SKONCZY SIE AUTOMATYCZNA, PERMAMENTNA BANICJA\n\n, string)
					format(string, sizeof(string), %s(ffffff)Czy zabic Twoja postac?, string)

					ShowPlayerDialog(playerid, D_FCK_DECISION, DIALOG_STYLE_MSGBOX, Śmierć postaci, string, Zabij, Anuluj)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Na skutek otrzymanych obra¿eñ, straci³eœ przytomnoœæ.\nPoczekaj do czasu gdy siê ockniesz, lub przyjedzie karetka., OK, )
				)
			)
			else
			(
				if(PlayerCache(playerid)(pArrest))
				(
					PlayerCache(playerid)(pBW) = 3 * 60
				) else (
					PlayerCache(playerid)(pBW) = 5 * 60
				)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Na skutek otrzymanych obra¿eñ, straci³eœ przytomnoœæ.\nPoczekaj do czasu gdy siê ockniesz, lub przyjedzie karetka.\nZosta³eœ zabity przez gracza maj¹cego na koncie mniej ni¿ 10 godzin gry, BW zosta³o skrócone do 5 min., OK, )
			)
			
			if(!PlayerCache(killerid)(pGloves))
			(
				PlayerCache(playerid)(pKiller) = PlayerCache(killerid)(pUID)
				printf(k: %d, PlayerCache(killerid)(pUID))
			)
			else
			(
				PlayerCache(playerid)(pKiller) = 0
			)
			weaponid = GetPlayerWeapon(killerid),
				weapon_class = GetWeaponClass(weaponid)
				
			PlayerCache(playerid)(pKillerWeapon) = WeaponCache(killerid)(weapon_class)(pWeaponUID)
			printf(w: %d, PlayerCache(playerid)(pKillerWeapon))
			
			if(PlayerCache(playerid)(pSparing) != INVALID_PLAYER_ID)
			(
				stopSparing(playerid)
				PlayerCache(playerid)(pHealth) = 20.0
				PlayerCache(playerid)(pBW) = 1 * 60
			)
		)
	)
	else
	(
		if(PlayerCache(playerid)(pBW) (= 0)
		(
			if(PlayerCache(playerid)(pArrest))
			(
				PlayerCache(playerid)(pBW) = 5 * 60
			) else (
				PlayerCache(playerid)(pBW) = 10 * 60
			)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Na skutek otrzymanych obra¿eñ, straci³eœ przytomnoœæ.\nPoczekaj do czasu gdy siê ockniesz, lub przyjedzie karetka., OK, )

			PlayerCache(playerid)(pKiller) = 0
			PlayerCache(playerid)(pKillerWeapon) = 0
		)
		
		if(IsPlayerConnected(killerid))
		(
			PlayerCache(killerid)(pKillCount) ++
		)
	)
	
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

	GetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

	PlayerCache(playerid)(pInt) = GetPlayerInterior(playerid)
	PlayerCache(playerid)(pVW) = GetPlayerVirtualWorld(playerid)

	hrp_SetPlayerHealth(playerid, 20)
	hrp_SetPlayerHealth(playerid, 20)
	
	SavePlayerStats(playerid, SAVE_PLAYER_POS)
	
	if(killerid != INVALID_PLAYER_ID)
	(
		ShowAdminLog(~r~(death) ~w~Gracz %s (ID: %d, Godzin: %d) zabil gracza %s (ID: %d, Godzin: %d)., PlayerName(killerid), killerid, PlayerCache(killerid)(pHours), PlayerName(playerid), playerid, PlayerCache(playerid)(pHours))
	)
	else
	(
		ShowAdminLog(~r~(death) ~w~Gracz %s (ID: %d, Godzin: %d) zginal (prawdopodobne samobojstwo)., PlayerName(playerid), playerid, PlayerCache(playerid)(pHours))
	)
	return 1
)

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
(
	// Spectate
 	foreach(Player, i)
  	(
   		if(Logged(i) && Spawned(i))
	 	(
	  		if(PlayerCache(i)(pSpectate) == playerid)
			(
		 		SetPlayerInterior(i, newinteriorid)
		 		SetPlayerVirtualWorld(i, GetPlayerVirtualWorld(playerid))
		 	)
		)
   	)
	return 1
)

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
(
	if(!Logged(playerid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wysy³aæ prywatnych wiadomoœci bêd¹c niezalogowanym., OK, )
		return 1
	)
	if(clickedplayerid == playerid || !Logged(clickedplayerid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wys³aæ prywatnej wiadomoœci do tego gracza., OK, )
		return 1
	)
	if((PlayerCache(playerid)(pBlock) & BLOCK_OOC) && PlayerCache(clickedplayerid)(pAdmin) == 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Twoja postaæ ma na³o¿on¹ blokadê czatu OOC., OK, )
		return 1
	)
	if(PlayerCache(clickedplayerid)(pTogW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma wy³¹czone otrzymywanie prywatnych wiadomoœci., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pBW) && !PlayerToPlayer(25.0, playerid, clickedplayerid) && PlayerCache(clickedplayerid)(pAdmin) == 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podczas stanu nieprzytomnoœci, wiadomoœci prywatne mo¿esz wysy³aæ na okreœlon¹ odleg³oœæ., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wysy³aæ prywatnych wiadomoœci w chwili obecnej., OK, )
		return 1
	)
	string(128)
	MainPlayerTable(playerid) = clickedplayerid
	
	format(string, sizeof(string), WprowadŸ treœæ prywatnej wiadomoœci, która zostanie wys³ana do gracza %s., PlayerName(clickedplayerid))
	ShowPlayerDialog(playerid, D_SEND_PW, DIALOG_STYLE_INPUT, Wysy³anie prywatnej wiadomoœci, string, Wyœlij, Anuluj)
	return 1
)

stock initializePlayerTextDraws(playerid)
(
	// Drzwi
	TextDrawDoorInfo(playerid) = CreatePlayerTextDraw(playerid, 326.000000, 330.000000, _)
	PlayerTextDrawAlignment(playerid, TextDrawDoorInfo(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid, TextDrawDoorInfo(playerid), 255)
	PlayerTextDrawFont(playerid, TextDrawDoorInfo(playerid), 1)
	PlayerTextDrawLetterSize(playerid, TextDrawDoorInfo(playerid), 0.379999, 1.299999)
	PlayerTextDrawColor(playerid, TextDrawDoorInfo(playerid), -1)
	PlayerTextDrawSetOutline(playerid, TextDrawDoorInfo(playerid), 1)
	PlayerTextDrawSetProportional(playerid, TextDrawDoorInfo(playerid), 1)
	PlayerTextDrawUseBox(playerid, TextDrawDoorInfo(playerid), 1)
	PlayerTextDrawBoxColor(playerid, TextDrawDoorInfo(playerid), 68)
	PlayerTextDrawTextSize(playerid, TextDrawDoorInfo(playerid), 490.000000, 221.000000)
	
	TextDrawPropertyFade1(playerid) = CreatePlayerTextDraw(playerid,0.000000, -1.000000, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~)
	PlayerTextDrawBackgroundColor(playerid,TextDrawPropertyFade1(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawPropertyFade1(playerid), 1)
	PlayerTextDrawLetterSize(playerid,TextDrawPropertyFade1(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawPropertyFade1(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawPropertyFade1(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawPropertyFade1(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawPropertyFade1(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawPropertyFade1(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawPropertyFade1(playerid), 255)
	PlayerTextDrawTextSize(playerid,TextDrawPropertyFade1(playerid), 653.000000, -2.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawPropertyFade1(playerid), 0)

	TextDrawPropertyFade2(playerid) = CreatePlayerTextDraw(playerid,0.000000, 342.000000, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~)
	PlayerTextDrawBackgroundColor(playerid,TextDrawPropertyFade2(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawPropertyFade2(playerid), 1)
	PlayerTextDrawLetterSize(playerid,TextDrawPropertyFade2(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawPropertyFade2(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawPropertyFade2(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawPropertyFade2(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawPropertyFade2(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawPropertyFade2(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawPropertyFade2(playerid), 255)
	PlayerTextDrawTextSize(playerid,TextDrawPropertyFade2(playerid), 653.000000, -2.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawPropertyFade2(playerid), 0)

	TextDrawPropertyMSG(playerid) = CreatePlayerTextDraw(playerid,302.000000, 283.000000, Posiadlosc kupiona)
	PlayerTextDrawBackgroundColor(playerid,TextDrawPropertyMSG(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawPropertyMSG(playerid), 3)
	PlayerTextDrawLetterSize(playerid,TextDrawPropertyMSG(playerid), 0.970000, 3.199999)
	PlayerTextDrawColor(playerid,TextDrawPropertyMSG(playerid), -6749953)
	PlayerTextDrawSetOutline(playerid,TextDrawPropertyMSG(playerid), 1)
	PlayerTextDrawSetProportional(playerid,TextDrawPropertyMSG(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,TextDrawPropertyMSG(playerid), 0)
	
	/*TextDrawCardTable(playerid) = CreatePlayerTextDraw(playerid,522.000000, 112.000000, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~)
	PlayerTextDrawBackgroundColor(playerid,TextDrawCardTable(playerid) , 255)
	PlayerTextDrawFont(playerid,TextDrawCardTable(playerid) , 1)
	PlayerTextDrawLetterSize(playerid,TextDrawCardTable(playerid) , 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawCardTable(playerid) , -1)
	PlayerTextDrawSetOutline(playerid,TextDrawCardTable(playerid) , 0)
	PlayerTextDrawSetProportional(playerid,TextDrawCardTable(playerid) , 1)
	PlayerTextDrawSetShadow(playerid,TextDrawCardTable(playerid) , 1)
	PlayerTextDrawUseBox(playerid,TextDrawCardTable(playerid) , 1)
	PlayerTextDrawBoxColor(playerid,TextDrawCardTable(playerid) , 150)
	PlayerTextDrawTextSize(playerid,TextDrawCardTable(playerid) , 113.000000, 151.000000)
	
	TextDrawCardWelcome(playerid) = CreatePlayerTextDraw(playerid,241.000000, 116.000000, Aktualne rozdanie)
	PlayerTextDrawBackgroundColor(playerid,TextDrawCardWelcome(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawCardWelcome(playerid), 3)
	PlayerTextDrawLetterSize(playerid,TextDrawCardWelcome(playerid), 0.539999, 1.899999)
	PlayerTextDrawColor(playerid,TextDrawCardWelcome(playerid), 16711935)
	PlayerTextDrawSetOutline(playerid,TextDrawCardWelcome(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawCardWelcome(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawCardWelcome(playerid), 1)*/
	

	TextDrawSlotsFirst(playerid) = CreatePlayerTextDraw(playerid,172.000000, 142.000000, LD_SLOT:bar1_o)
	PlayerTextDrawBackgroundColor(playerid,TextDrawSlotsFirst(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawSlotsFirst(playerid), 4)
	PlayerTextDrawLetterSize(playerid,TextDrawSlotsFirst(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawSlotsFirst(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawSlotsFirst(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawSlotsFirst(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawSlotsFirst(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawSlotsFirst(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawSlotsFirst(playerid), 255)
	PlayerTextDrawTextSize(playerid,TextDrawSlotsFirst(playerid), 90.000000, 76.000000)

	TextDrawSlotsSecond(playerid) = CreatePlayerTextDraw(playerid,375.000000, 142.000000, LD_SLOT:bar1_o)
	PlayerTextDrawBackgroundColor(playerid,TextDrawSlotsSecond(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawSlotsSecond(playerid), 4)
	PlayerTextDrawLetterSize(playerid,TextDrawSlotsSecond(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawSlotsSecond(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawSlotsSecond(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawSlotsSecond(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawSlotsSecond(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawSlotsSecond(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawSlotsSecond(playerid), 255)
	PlayerTextDrawTextSize(playerid,TextDrawSlotsSecond(playerid), 90.000000, 76.000000)

	TextDrawSlotsThird(playerid) = CreatePlayerTextDraw(playerid,273.000000, 142.000000, LD_SLOT:bar1_o)
	PlayerTextDrawBackgroundColor(playerid,TextDrawSlotsThird(playerid) , 255)
	PlayerTextDrawFont(playerid,TextDrawSlotsThird(playerid) , 4)
	PlayerTextDrawLetterSize(playerid,TextDrawSlotsThird(playerid) , 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawSlotsThird(playerid) , -1)
	PlayerTextDrawSetOutline(playerid,TextDrawSlotsThird(playerid) , 0)
	PlayerTextDrawSetProportional(playerid,TextDrawSlotsThird(playerid) , 1)
	PlayerTextDrawSetShadow(playerid,TextDrawSlotsThird(playerid) , 1)
	PlayerTextDrawUseBox(playerid,TextDrawSlotsThird(playerid) , 1)
	PlayerTextDrawBoxColor(playerid,TextDrawSlotsThird(playerid) , 255)
	PlayerTextDrawTextSize(playerid,TextDrawSlotsThird(playerid) , 90.000000, 76.000000)

	PDT_BG(playerid) = CreatePlayerTextDraw(playerid, 449.000000, 113.000000, _)
	PlayerTextDrawBackgroundColor(playerid, PDT_BG(playerid), -16776961)
	PlayerTextDrawFont(playerid, PDT_BG(playerid), 3)
	PlayerTextDrawLetterSize(playerid, PDT_BG(playerid), 0.439999, 27.500001)
	PlayerTextDrawColor(playerid, PDT_BG(playerid), -1)
	PlayerTextDrawSetOutline(playerid, PDT_BG(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_BG(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_BG(playerid), 5)
	PlayerTextDrawUseBox(playerid, PDT_BG(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_BG(playerid), 572661589)
	PlayerTextDrawTextSize(playerid, PDT_BG(playerid), 180.000000, 8.000000)

	PDT_1(playerid) = CreatePlayerTextDraw(playerid, 193.000000, 117.000000, LSPD)
	PlayerTextDrawBackgroundColor(playerid, PDT_1(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_1(playerid), 2)
	PlayerTextDrawLetterSize(playerid, PDT_1(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid, PDT_1(playerid), -1)
	PlayerTextDrawSetOutline(playerid, PDT_1(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_1(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_1(playerid), 1)

	PDT_2(playerid) = CreatePlayerTextDraw(playerid, 193.000000, 141.000000, Kartoteka osobowa)
	PlayerTextDrawBackgroundColor(playerid, PDT_2(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_2(playerid), 1)
	PlayerTextDrawLetterSize(playerid, PDT_2(playerid), 0.319999, 1.500000)
	PlayerTextDrawColor(playerid, PDT_2(playerid), 0xFFFFFFFF)
	PlayerTextDrawSetOutline(playerid, PDT_2(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_2(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_2(playerid), 1)
	PlayerTextDrawUseBox(playerid, PDT_2(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_2(playerid), 572662218)
	PlayerTextDrawTextSize(playerid, PDT_2(playerid), 435.000000, 15.000000)
	PlayerTextDrawSetSelectable(playerid, PDT_2(playerid), 1)

	PDT_3(playerid) = CreatePlayerTextDraw(playerid, 193.000000, 165.000000, Lista poszukiwanych pojazdow)
	PlayerTextDrawBackgroundColor(playerid, PDT_3(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_3(playerid), 1)
	PlayerTextDrawLetterSize(playerid, PDT_3(playerid), 0.319999, 1.500000)
	PlayerTextDrawColor(playerid, PDT_3(playerid), 0xFFFFFFFF)
	PlayerTextDrawSetOutline(playerid, PDT_3(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_3(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_3(playerid), 1)
	PlayerTextDrawUseBox(playerid, PDT_3(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_3(playerid), 572662218)
	PlayerTextDrawTextSize(playerid, PDT_3(playerid), 435.000000, 15.000000)
	PlayerTextDrawSetSelectable(playerid, PDT_3(playerid), 1)

	PDT_4(playerid) = CreatePlayerTextDraw(playerid, 193.000000, 189.000000, DMV ) Znajdz pojazd)
	PlayerTextDrawBackgroundColor(playerid, PDT_4(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_4(playerid), 1)
	PlayerTextDrawLetterSize(playerid, PDT_4(playerid), 0.319999, 1.500000)
	PlayerTextDrawColor(playerid, PDT_4(playerid), 0xFFFFFFFF)
	PlayerTextDrawSetOutline(playerid, PDT_4(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_4(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_4(playerid), 1)
	PlayerTextDrawUseBox(playerid, PDT_4(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_4(playerid), 572662218)
	PlayerTextDrawTextSize(playerid, PDT_4(playerid), 435.000000, 15.000000)
	PlayerTextDrawSetSelectable(playerid, PDT_4(playerid), 1)

	PDT_5(playerid) = CreatePlayerTextDraw(playerid, 193.000000, 213.000000, DMV ) Anuluj prawo jazdy)
	PlayerTextDrawBackgroundColor(playerid, PDT_5(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_5(playerid), 1)
	PlayerTextDrawLetterSize(playerid, PDT_5(playerid), 0.319999, 1.500000)
	PlayerTextDrawColor(playerid, PDT_5(playerid), 0xFFFFFFFF)
	PlayerTextDrawSetOutline(playerid, PDT_5(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_5(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_5(playerid), 1)
	PlayerTextDrawUseBox(playerid, PDT_5(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_5(playerid), 572662218)
	PlayerTextDrawTextSize(playerid, PDT_5(playerid), 435.000000, 15.000000)
	PlayerTextDrawSetSelectable(playerid, PDT_5(playerid), 1)

	PDT_6(playerid) = CreatePlayerTextDraw(playerid, 193.000000, 238.000000, _)
	PlayerTextDrawBackgroundColor(playerid, PDT_6(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_6(playerid), 1)
	PlayerTextDrawLetterSize(playerid, PDT_6(playerid), 0.319999, 1.500000)
	PlayerTextDrawColor(playerid, PDT_6(playerid), 0xFFFFFFFF)
	PlayerTextDrawSetOutline(playerid, PDT_6(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_6(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_6(playerid), 1)
	PlayerTextDrawUseBox(playerid, PDT_6(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_6(playerid), 572662218)
	PlayerTextDrawTextSize(playerid, PDT_6(playerid), 435.000000, 15.000000)
	PlayerTextDrawSetSelectable(playerid, PDT_6(playerid), 1)

	PDT_7(playerid) = CreatePlayerTextDraw(playerid, 193.000000, 263.000000, _)
	PlayerTextDrawBackgroundColor(playerid, PDT_7(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_7(playerid), 1)
	PlayerTextDrawLetterSize(playerid, PDT_7(playerid), 0.319999, 1.500000)
	PlayerTextDrawColor(playerid, PDT_7(playerid), 0xFFFFFFFF)
	PlayerTextDrawSetOutline(playerid, PDT_7(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_7(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_7(playerid), 1)
	PlayerTextDrawUseBox(playerid, PDT_7(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_7(playerid), 572662218)
	PlayerTextDrawTextSize(playerid, PDT_7(playerid), 435.000000, 15.000000)
	PlayerTextDrawSetSelectable(playerid, PDT_7(playerid), 1)

	PDT_8(playerid) = CreatePlayerTextDraw(playerid, 193.000000, 288.000000, _)
	PlayerTextDrawBackgroundColor(playerid, PDT_8(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_8(playerid), 1)
	PlayerTextDrawLetterSize(playerid, PDT_8(playerid), 0.319999, 1.500000)
	PlayerTextDrawColor(playerid, PDT_8(playerid), 0xFFFFFFFF)
	PlayerTextDrawSetOutline(playerid, PDT_8(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_8(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_8(playerid), 1)
	PlayerTextDrawUseBox(playerid, PDT_8(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_8(playerid), 572662218)
	PlayerTextDrawTextSize(playerid, PDT_8(playerid), 435.000000, 15.000000)
	PlayerTextDrawSetSelectable(playerid, PDT_8(playerid), 1)

	PDT_9(playerid) = CreatePlayerTextDraw(playerid, 193.000000, 314.000000, _)
	PlayerTextDrawBackgroundColor(playerid, PDT_9(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_9(playerid), 1)
	PlayerTextDrawLetterSize(playerid, PDT_9(playerid), 0.319999, 1.500000)
	PlayerTextDrawColor(playerid, PDT_9(playerid), 0xFFFFFFFF)
	PlayerTextDrawSetOutline(playerid, PDT_9(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_9(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_9(playerid), 1)
	PlayerTextDrawUseBox(playerid, PDT_9(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_9(playerid), 572662218)
	PlayerTextDrawTextSize(playerid, PDT_9(playerid), 435.000000, -13.000000)
	PlayerTextDrawSetSelectable(playerid, PDT_9(playerid), 1)

	PDT_Back(playerid) = CreatePlayerTextDraw(playerid, 383.000000, 338.000000, Wyjdz)
	PlayerTextDrawBackgroundColor(playerid, PDT_Back(playerid), 255)
	PlayerTextDrawFont(playerid, PDT_Back(playerid), 1)
	PlayerTextDrawLetterSize(playerid, PDT_Back(playerid), 0.319999, 1.500000)
	PlayerTextDrawColor(playerid, PDT_Back(playerid), 0xFFFFFFFF)
	PlayerTextDrawSetOutline(playerid, PDT_Back(playerid), 0)
	PlayerTextDrawSetProportional(playerid, PDT_Back(playerid), 1)
	PlayerTextDrawSetShadow(playerid, PDT_Back(playerid), 1)
	PlayerTextDrawUseBox(playerid, PDT_Back(playerid), 1)
	PlayerTextDrawBoxColor(playerid, PDT_Back(playerid), 572662218)
	PlayerTextDrawTextSize(playerid, PDT_Back(playerid), 435.000000, 15.000000)
	PlayerTextDrawSetSelectable(playerid, PDT_Back(playerid), 1)


	AdminSpecInfo(playerid) = CreatePlayerTextDraw(playerid, 14.000000, 211.000000, ~r~Simon Sarno  ~w~(Sim00n)~n~~y~Zalogowany o 21:33:12~n~~w~UID: 5235  GID: 615~n~Portfel: ~g~$5215~w~  Bank: ~g~$52000)
	PlayerTextDrawBackgroundColor(playerid, AdminSpecInfo(playerid), 255)
	PlayerTextDrawFont(playerid, AdminSpecInfo(playerid), 1)
	PlayerTextDrawLetterSize(playerid, AdminSpecInfo(playerid), 0.230000, 0.799999)
	PlayerTextDrawColor(playerid, AdminSpecInfo(playerid), -1)
	PlayerTextDrawSetOutline(playerid, AdminSpecInfo(playerid), 0)
	PlayerTextDrawSetProportional(playerid, AdminSpecInfo(playerid), 1)
	PlayerTextDrawSetShadow(playerid, AdminSpecInfo(playerid), 1)

	AdminSpecStats(playerid) = CreatePlayerTextDraw(playerid, 13.000000, 251.000000, ~b~Sila: ~w~35%~n~~b~Kondycja: ~w~59%~n~~w~~b~Lowienie: ~w~12%~n~~b~Strzelanie: ~w~0%~n~~b~Prowadzenie: ~w~30%)
	PlayerTextDrawBackgroundColor(playerid, AdminSpecStats(playerid), 255)
	PlayerTextDrawFont(playerid, AdminSpecStats(playerid), 1)
	PlayerTextDrawLetterSize(playerid, AdminSpecStats(playerid), 0.230000, 0.799999)
	PlayerTextDrawColor(playerid, AdminSpecStats(playerid), -1)
	PlayerTextDrawSetOutline(playerid, AdminSpecStats(playerid), 0)
	PlayerTextDrawSetProportional(playerid, AdminSpecStats(playerid), 1)
	PlayerTextDrawSetShadow(playerid, AdminSpecStats(playerid), 1)
	
	// TextDrawInfoNew
	TextDrawInfoNewContent(playerid) = CreatePlayerTextDraw(playerid, 521.000000, 331.000000, _)
	PlayerTextDrawAlignment(playerid, TextDrawInfoNewContent(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid, TextDrawInfoNewContent(playerid), 255)
	PlayerTextDrawFont(playerid, TextDrawInfoNewContent(playerid), 1)
	PlayerTextDrawLetterSize(playerid, TextDrawInfoNewContent(playerid), 0.280000, 1.300000)
	PlayerTextDrawColor(playerid, TextDrawInfoNewContent(playerid), -1)
	PlayerTextDrawSetOutline(playerid, TextDrawInfoNewContent(playerid), 1)
	PlayerTextDrawSetProportional(playerid, TextDrawInfoNewContent(playerid), 1)
	PlayerTextDrawUseBox(playerid, TextDrawInfoNewContent(playerid), 1)
	PlayerTextDrawBoxColor(playerid, TextDrawInfoNewContent(playerid), 150995044)
	PlayerTextDrawTextSize(playerid, TextDrawInfoNewContent(playerid), 0.000000, 198.000000)
	
	// nowe itemkowe textdrawy
	items_LoadTextdraws(playerid)
	
	bGUI_LoadTextdraws(playerid)
	
	phone_loadTextdraws(playerid)

	//BJTextDrawInitiateForPlayer(playerid)
)

stock RemoveBuildings(playerid)
(
	// Dystrybutory (zmieniamy na nasze niewybuchaj¹ce)
	RemoveBuildingForPlayer(playerid, 1676, 1941.6563, -1778.4531, 14.1406, 0.25)
 	RemoveBuildingForPlayer(playerid, 1676, 1941.6563, -1774.3125, 14.1406, 0.25)
 	RemoveBuildingForPlayer(playerid, 1676, 1941.6563, -1771.3438, 14.1406, 0.25)
 	RemoveBuildingForPlayer(playerid, 1676, 1941.6563, -1767.2891, 14.1406, 0.25)

	//Sygnalizacja na ca³ej mapie (1283, 1315, 1315, 1350)
 	RemoveBuildingForPlayer(playerid, 1283, 0.0, 0.0, 0.0, 6000.0)
 	RemoveBuildingForPlayer(playerid, 1284, 0.0, 0.0, 0.0, 6000.0)
 	RemoveBuildingForPlayer(playerid, 1315, 0.0, 0.0, 0.0, 6000.0)
 	RemoveBuildingForPlayer(playerid, 1350, 0.0, 0.0, 0.0, 6000.0)
	
	//Usuniêcie jednej latarni dla FD
	RemoveBuildingForPlayer(playerid, 1294, 1735.0076, -1155.6365, 23.2838, 20.0)
	
	//Nowe centrum na Pershing Square, Akro
	RemoveBuildingForPlayer(playerid, 4026, 1497.7969, -1543.7109, 17.5547, 0.25)
	RemoveBuildingForPlayer(playerid, 4054, 1402.5000, -1682.0234, 25.5469, 0.25)
	RemoveBuildingForPlayer(playerid, 4055, 1394.3594, -1620.6641, 32.1484, 0.25)
	RemoveBuildingForPlayer(playerid, 4218, 1497.7031, -1546.6172, 43.9922, 0.25)
	RemoveBuildingForPlayer(playerid, 4220, 1370.6406, -1643.4453, 33.1797, 0.25)
	RemoveBuildingForPlayer(playerid, 4005, 1402.5000, -1682.0234, 25.5469, 0.25)
	RemoveBuildingForPlayer(playerid, 4006, 1394.3594, -1620.6641, 32.1484, 0.25)
	RemoveBuildingForPlayer(playerid, 4016, 1497.7969, -1543.7109, 17.5547, 0.25)
	RemoveBuildingForPlayer(playerid, 713, 1457.9375, -1620.6953, 13.4531, 0.25)
	RemoveBuildingForPlayer(playerid, 673, 1501.2813, -1624.5781, 12.3984, 0.25)
	RemoveBuildingForPlayer(playerid, 673, 1498.3594, -1616.9688, 12.3984, 0.25)
	
	//Alahambra pod nowe osiedla
	RemoveBuildingForPlayer(playerid, 5408, 1837, -1664, 14, 100)
	RemoveBuildingForPlayer(playerid, 5544, 1837, -1664, 14, 100)
	RemoveBuildingForPlayer(playerid, 5408, 1873.74219 , -1682.47656, 34.79688, 5.0)
	RemoveBuildingForPlayer(playerid, 1533, 1837.38989, -1678.82776, 13.31242, 5.0)
	RemoveBuildingForPlayer(playerid, 1537, 1837.4375, -1680.95312, 12.29688, 5.0)
	RemoveBuildingForPlayer(playerid, 1533, 1837.38989, -1685.3064, 12.54757, 5.0)
	RemoveBuildingForPlayer(playerid, 1537, 1837.4375, -1686.98437, 12.3125, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1832.89844, -1670.76562, 9.71875, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1832.38281, -1694.3125, 9.71875, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1855.71875, -1623.28125, 10.80469, 5.0)
	RemoveBuildingForPlayer(playerid, 1308, 1891.96875, -1622, 12.78125, 5.0)
	RemoveBuildingForPlayer(playerid, 712, 1929.57813, -1627.625, 21.39063, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1908.21875, -1622.98437, 10.80469, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1931.03906, -1637.89844, 10.80469, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1931.03906, -1667.03125, 10.80469, 5.0)
	RemoveBuildingForPlayer(playerid, 712, 1929.57813, -1702.28906, 21.39063, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1931.03906, -1702.28906, 10.80469, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1931.03906, -1726.32812, 10.80469, 5.0)
	RemoveBuildingForPlayer(playerid, 712, 1929.57813, -1736.90625, 21.39063, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1908.21875, -1741.48437, 10.80469, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1879.50781, -1741.48437, 10.80469, 5.0)
	RemoveBuildingForPlayer(playerid, 620, 1855.71875, -1741.53906, 10.80469, 5.0)
	RemoveBuildingForPlayer(playerid, 740, 1863.3125,  -1568.64844, 11.77344, 5.0)
	RemoveBuildingForPlayer(playerid,  645, 1976.17188, -1600.17969, 12.19531, 5.0)
	RemoveBuildingForPlayer(playerid, 1308, 1832.82031, -1622, 12.78125, 5.0)
	
	//Jakaœ lampa na wjeÂ?dzie - proœba gracza
	//RemoveBuildingForPlayer(playerid, 1223, 2832.1045, -1593.5623, 10.9219, 50.0)

	//Jakieœ p³otki - proœba gracza
	/*RemoveBuildingForPlayer(playerid, 1411, 444.577820, -1340.351563, 15.815981, 20.0)
	RemoveBuildingForPlayer(playerid, 1411, 440.196350, -1343.254883, 15.777159, 20.0)
	RemoveBuildingForPlayer(playerid, 1411, 431.381439, -1348.973389, 15.705402, 20.0)
	RemoveBuildingForPlayer(playerid, 1411, 425.242462, -1360.366455, 15.483902, 20.0)*/
	
	//Brama Jackala
	//RemoveBuildingForPlayer(playerid, 3036, -2176.7783, 660.6580, 49.4375, 20.0)
	
	//Jakieœ gówna Arczira (devgru)
	/*RemoveBuildingForPlayer(playerid, 10829, -1522.0662, 481.6288, 7.1875, 20.0)
	RemoveBuildingForPlayer(playerid, 968, -1526.1235, 480.7867, 7.1875, 20.0)
	RemoveBuildingForPlayer(playerid, 3115, -1456.9875, 502.2328, 18.2662, 20.0)
	RemoveBuildingForPlayer(playerid, 3114, -1415.6456, 515.5402, 18.2427, 20.0)*/
	
	// Jakieœ domki Sebka - postawi³ nowe na miejsce starych // http://www.ls-rp.net/index.php?app=samp&module=admin&section=ticket&id=7677
	/*RemoveBuildingForPlayer(playerid, 3582, 2246, -1434, 26, 40)
	RemoveBuildingForPlayer(playerid, 3562, 2246, -1434, 26, 40)
	RemoveBuildingForPlayer(playerid, 620, 2268, -1469, 25, 10)
	RemoveBuildingForPlayer(playerid, 0, 2268, -1469, 25, 10)
	RemoveBuildingForPlayer(playerid, 645, 2238, -1394, 24, 10)
	RemoveBuildingForPlayer(playerid, 0, 2238, -1394, 24, 10)*/
	
	// Jakieœ obiekty w Polomino Creek - aaGruby - http://www.ls-rp.net/index.php?app=samp&module=admin&section=ticket&id=25004
	//RemoveBuildingForPlayer(playerid, 12842, 2330.7031, 1.3203, 25.9531, 0.25)
	
	// Jakieœ obiekty dzielnicy na Sevilli - Pawe³_Franciszek - http://www.ls-rp.net/index.php?app=samp&module=admin&section=ticket&id=26167
	/*RemoveBuildingForPlayer(playerid, 3638, 2687.125, -1955.70312, 15.73438, 15.0)
	RemoveBuildingForPlayer(playerid, 3638, 2666.4375, 1955.70312, 15.73438, 15.0)
	RemoveBuildingForPlayer(playerid, 3638, 2644.61719, -1955.70312, 15.73438, 15.0)
	RemoveBuildingForPlayer(playerid, 3244, 2758.42969, -2124.85937, 10.61719, 15.0)
	RemoveBuildingForPlayer(playerid, 3244, 2632.39063, -1954.82031, 12.75781, 15.0)
	RemoveBuildingForPlayer(playerid, 1226, 2709.10913, -1967.297, 12.90205, 15.0)
	RemoveBuildingForPlayer(playerid, 3636, 2794.80469, -2074.51562, 17.75781, 15.0)
	RemoveBuildingForPlayer(playerid, 3636, 2739.98438, -2119.78906, 17.78906, 15.0)
	RemoveBuildingForPlayer(playerid, 3636, 2739.98438, -2089.05469, 18.5, 15.0)
	RemoveBuildingForPlayer(playerid, 3636, 2768.04688, -2104.48437, 17.78906, 15.0)
	RemoveBuildingForPlayer(playerid, 3636, 2766.52344, -2074.51562, 18.5, 15.0)
	RemoveBuildingForPlayer(playerid, 3244, 2758.42969, -2124.85937, 10.61719, 15.0)
	RemoveBuildingForPlayer(playerid, 1460, 2640.30469, -1987.29504, 14.02198, 15.0)
	RemoveBuildingForPlayer(playerid, 1460, 2642.77246, -1979.46069, 13.72291, 15.0)
	RemoveBuildingForPlayer(playerid, 708, 2639.27344, -1976.32812, 12.63281, 15.0)
	RemoveBuildingForPlayer(playerid, 1483, 2644.2998, -1982.39941, 14.5, 15.0)
	RemoveBuildingForPlayer(playerid, 1447, 2796.13794, -2108.54712, 11.34391, 15.0)
	RemoveBuildingForPlayer(playerid, 1447, 2812.67285, -2063.41455, 11.22549, 15.0)
	RemoveBuildingForPlayer(playerid, 3683, 2739.9844, -2089.0547, 18.5000, 0.25)
	RemoveBuildingForPlayer(playerid, 3683, 2739.9844, -2119.7891, 17.7891, 0.25)
	RemoveBuildingForPlayer(playerid, 3683, 2768.0469, -2104.4844, 17.7891, 0.25)
	RemoveBuildingForPlayer(playerid, 3683, 2794.8047, -2074.5156, 17.7578, 0.25)
	RemoveBuildingForPlayer(playerid, 3683, 2766.5234, -2074.5156, 18.5000, 0.25)
	RemoveBuildingForPlayer(playerid, 3638, 2644.6172, -1955.7031, 15.7344, 0.25)
	RemoveBuildingForPlayer(playerid, 3638, 2666.4375, -1955.7031, 15.7344, 0.25)
	RemoveBuildingForPlayer(playerid, 3638, 2687.1250, -1955.7031, 15.7344, 0.25)
	RemoveBuildingForPlayer(playerid, 3636, 2739.9844, -2119.7891, 17.7891, 0.25)
	RemoveBuildingForPlayer(playerid, 3636, 2739.9844, -2089.0547, 18.5000, 0.25)
	RemoveBuildingForPlayer(playerid, 3636, 2766.5234, -2074.5156, 18.5000, 0.25)
	RemoveBuildingForPlayer(playerid, 3636, 2768.0469, -2104.4844, 17.7891, 0.25)
	RemoveBuildingForPlayer(playerid, 3636, 2794.8047, -2074.5156, 17.7578, 0.25)*/


	// Xmas passage
	/*RemoveBuildingForPlayer(playerid, 1294, 1387.0999755859, -1235.5, 17.89999961853, 10.0)
	RemoveBuildingForPlayer(playerid, 1294, 1405.8000488281, -1246.4000244141, 17.10000038147, 10.0)
	RemoveBuildingForPlayer(playerid, 1294, 1426.5, -1235.1999511719, 17.10000038147, 10.0)
	RemoveBuildingForPlayer(playerid, 1286, 1440, -1246.3000488281, 13.199999809265, 10.0)
	RemoveBuildingForPlayer(playerid, 1285, 1439.0999755859, -1246.3000488281, 13.10000038147, 10.0)
	RemoveBuildingForPlayer(playerid, 1287, 1440.9000244141, -1246.5999755859, 13.10000038147, 10.0)
	RemoveBuildingForPlayer(playerid, 1289, 1442.8000488281, -1246.3000488281, 13.10000038147, 10.0)
	RemoveBuildingForPlayer(playerid, 1288, 1442, -1246.3000488281, 13.199999809265, 10.0)
	RemoveBuildingForPlayer(playerid, 1256, 1379.0999755859, -1228.5999755859, 13.199999809265, 10.0)
	RemoveBuildingForPlayer(playerid, 1256, 1390.4000244141, -1228.5999755859, 13.199999809265, 10.0)
	RemoveBuildingForPlayer(playerid, 1256, 1422.9000244141, -1228.5, 13.39999961853, 10.0)
	RemoveBuildingForPlayer(playerid, 1256, 1430.5, -1229.0999755859, 13.199999809265, 10.0)*/

	// Miko³aj || Nexsus - jakiÅ? event
	/*RemoveBuildingForPlayer(playerid, 671, 2535.71875, -1919.67187, 12.88281, 25.0)
	RemoveBuildingForPlayer(playerid, 708, 2535.00781, -1911.19531, 12.55469, 25.0)
	RemoveBuildingForPlayer(playerid, 671, 2530.11719, -1899.09375, 12.88281, 25.0)
	RemoveBuildingForPlayer(playerid, 1226, 2521.76855, -1910.71509, 13.19456, 25.0)*/

	// Drzewa - http://www.ls-rp.net/index.php?app=samp&module=admin&section=ticket&id=26867
	RemoveBuildingForPlayer(playerid, 717, 1703.3817,-1150.1799,24.0607, 5.0)
	RemoveBuildingForPlayer(playerid, 717, 1720.6276,-1150.1229,24.0607, 5.0)
	RemoveBuildingForPlayer(playerid, 717, 1738.1738,-1150.1156,24.0607, 5.0)

	// Blacky || Willofield - kana³y || Southern Crew
	RemoveBuildingForPlayer(playerid, 3594, 2450.4609, -1890.7813, 13.1641, 25.0)
	RemoveBuildingForPlayer(playerid, 1447, 2461.8828, -1879.7031, 13.8203, 25.0)
	RemoveBuildingForPlayer(playerid, 1447, 2444.8281, -1879.8750, 13.8203, 25.0)
	RemoveBuildingForPlayer(playerid, 1447, 2434.2734, -1879.7031, 13.8203, 25.0)
	RemoveBuildingForPlayer(playerid, 1413, 2452.3047, -1879.7109, 13.8203, 25.0)
	RemoveBuildingForPlayer(playerid, 1413, 2439.5469, -1879.9219, 13.8203, 25.0)


	// Centrum sultana
	RemoveBuildingForPlayer(playerid, 1440, 1148.694580, -1385.164551, 13.248435, 25.0)
	RemoveBuildingForPlayer(playerid, 1440, 1141.995117, -1346.068359, 13.257936, 25.0)
	RemoveBuildingForPlayer(playerid, 1440, 1085.695801, -1361.049316, 13.268291, 25.0)
	RemoveBuildingForPlayer(playerid, 5737, 1120.170166, -1303.445801, 18.580647, 25.0)
	RemoveBuildingForPlayer(playerid, 5935, 1120.170166, -1303.445801, 18.580647, 25.0)

	return 1
)
