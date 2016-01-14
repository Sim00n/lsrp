public SavePlayerStats(playerid, what)
(
	if(!Logged(playerid))	return 1
	if(StatsProtection(playerid) + 20 ) gettime()) return 1
	
	query(1024), main_query(1024), Float:health = (PlayerCache(playerid)(pHealth) ) 100.0)? 100.0 : PlayerCache(playerid)(pHealth)
	
	PlayerCache(playerid)(pChecksum) = (PlayerCache(playerid)(pBlockChecksum))? 0 : PlayerCache(playerid)(pCash) + PlayerCache(playerid)(pBankCash)
	
	format(main_query, sizeof(main_query), UPDATE hrp_characters SET)
	if(what & SAVE_PLAYER_BASIC)
	(
 		// Podstawowe (czas gry, skin, ¿ycie, pieni¹dze, warny, bw, hotel, pkt karne, dowód, prawko)
   		format(query, sizeof(query),  char_hours = %d, char_minutes = %d, char_skin = %d, char_health = %f, char_cash = %d, char_bankcash = %d, char_banknumb = %d, char_warns = %d, char_bw = %d, char_crash = %d, char_hoteluid = %d, char_pdp = %d, char_documents = %d, char_lastpay = %d, char_job = %d, char_arrest = %d, char_arresttime = %d, char_spawnplace = %d, char_house = %d, char_fightstyle = %d, char_fed = %d, char_knownstyles = %d, char_dailyreps = %d,
		PlayerCache(playerid)(pHours),
		PlayerCache(playerid)(pMinutes),
			
		PlayerCache(playerid)(pSkin),
		health,

		PlayerCache(playerid)(pCash),
		PlayerCache(playerid)(pBankCash),
		PlayerCache(playerid)(pBankNumber),
			
		PlayerCache(playerid)(pWarns),
			
		PlayerCache(playerid)(pBW),
			
		PlayerCache(playerid)(pCrash),
			
		PlayerCache(playerid)(pHotel),
			
		PlayerCache(playerid)(pPDP),
			
		PlayerCache(playerid)(pDocuments),
			
		PlayerCache(playerid)(pLastPay),
		PlayerCache(playerid)(pJob),

		PlayerCache(playerid)(pArrest),
		PlayerCache(playerid)(pArrestTime),
			
		PlayerCache(playerid)(pSpawnPlace),
		PlayerCache(playerid)(pHouse),

		PlayerCache(playerid)(pFightingStyle),
		PlayerCache(playerid)(pFed),
		PlayerCache(playerid)(pKnownStyles),
		PlayerCache(playerid)(pDailyReps))
		
		// Continuation of the previous format.

		
		// Za d³ugia linia - dodawaæ tu -  dodawaæ tu -  dodawaæ tu -  dodawaæ tu -  dodawaæ tu -  dodawaæ tu -  dodawaæ tu -  dodawaæ tu -  dodawaæ tu -  dodawaæ tu - 
		format(query, sizeof(query), %s, char_wounded = %d, char_color = %d, char_arrestday = %d, char_bleeding = %d, char_insurancecount = %d, char_familyhouse = %d, char_workrepeat = %d, 
			query, 
			PlayerCache(playerid)(pWounded), 
			((((PlayerCache(playerid)(pChecksum) + 31) * 3) + PlayerCache(playerid)(pUID)) + 3),
			PlayerCache(playerid)(pArrestDay),
			PlayerCache(playerid)(pBleeding),
			PlayerCache(playerid)(pInsuranceCount),
			PlayerCache(playerid)(pFamilyHouse),
			PlayerCache(playerid)(pWorkRepeat))

		if(strlen(main_query) ) 32)
		(
  			strcat(main_query, ,, sizeof(main_query))
		)
		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_PLAYER_POS)
	(
 		// Pozycja (interior, virtual world, posx, posy, posz)
   		format(query, sizeof(query),  char_int = %d, char_vw = %d, char_posx = %f, char_posy = %f, char_posz = %f,
		PlayerCache(playerid)(pInt),
		PlayerCache(playerid)(pVW),
		PlayerCache(playerid)(pPosX),
  		PlayerCache(playerid)(pPosY),
  		PlayerCache(playerid)(pPosZ))

		if(strlen(main_query) ) 32)
		(
  			strcat(main_query, ,, sizeof(main_query))
		)
		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_PLAYER_SKILLS)
	(
		// ¯eby nie zapisa³o chujowi statów na dragach.
		Float:strength = (PlayerCache(playerid)(pRage))? PlayerCache(playerid)(pRageStrength) : PlayerCache(playerid)(pStrength)
	
 		// Umiejêtnoœci postaci (je¿d¿enie, kondycja, strzelanie, ³owienie, si³a, uzale¿enienie)
   		format(query, sizeof(query),  char_fishing = %f, char_strength = %f, char_dependence = %f,
		PlayerCache(playerid)(pFishing),
		strength,
		PlayerCache(playerid)(pDependence))
			
		if(strlen(main_query) ) 32)
		(
  			strcat(main_query, ,, sizeof(main_query))
		)
		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_PLAYER_OPTIONS)
	(
		format(query, sizeof(query),  char_walkanim = %d,
		PlayerCache(playerid)(pWalkAnim))
	
		if(strlen(main_query) ) 32)
		(
  			strcat(main_query, ,, sizeof(main_query))
		)
		strcat(main_query, query, sizeof(main_query))
	)
	format(query, sizeof(query),  WHERE char_uid = %d LIMIT 1, PlayerCache(playerid)(pUID))
	strcat(main_query, query, sizeof(main_query))

	mysql_query(main_query)
	return 1
)

public ShowPlayerStats(playerid, giveplayer_id)
(
	list_stats(1024), string(128), IP(16)
	GetPlayerIp(giveplayer_id, IP, sizeof(IP))
	
	format(list_stats, sizeof(list_stats), Konto globalne:\t%s\n, PlayerCache(giveplayer_id)(pGlobalName))
	format(list_stats, sizeof(list_stats), %sCzas gry:\t\t%dh %dm\n, list_stats, PlayerCache(giveplayer_id)(pHours), PlayerCache(giveplayer_id)(pMinutes))
	if(PlayerCache(giveplayer_id)(pHealth) (= 40)
	(
		format(list_stats, sizeof(list_stats), %sZdrowie:\t\t(FB5006)%.2f(FFFFFF) HP\n, list_stats, PlayerCache(giveplayer_id)(pHealth))
	)
	else
	(
		format(list_stats, sizeof(list_stats), %sZdrowie:\t\t%.2f HP\n, list_stats, PlayerCache(giveplayer_id)(pHealth))
	)
	format(list_stats, sizeof(list_stats), %sGotówka:\t\t$%d\n, list_stats, PlayerCache(giveplayer_id)(pCash))

	format(list_stats, sizeof(list_stats), %sStan konta:\t\t$%d\n, list_stats, PlayerCache(giveplayer_id)(pBankCash))
	format(list_stats, sizeof(list_stats), %sNumer konta:\t\t%d\n, list_stats, PlayerCache(giveplayer_id)(pBankNumber))
	
	format(list_stats, sizeof(list_stats), %sSkin:\t\t\t%d\n, list_stats, PlayerCache(giveplayer_id)(pSkin))
	
	format(list_stats, sizeof(list_stats), %s-----\n, list_stats)
	
	format(list_stats, sizeof(list_stats), %s£owienie:\t\t%.2f%%\n, list_stats, PlayerCache(giveplayer_id)(pFishing))
	format(list_stats, sizeof(list_stats), %sSi³a:\t\t\t%.2f%%\n, list_stats, PlayerCache(giveplayer_id)(pStrength))
	
	format(list_stats, sizeof(list_stats), %s-----\n, list_stats)

	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerGroup(giveplayer_id)(slot)(gUID))
		(
  			group_id_fix = PlayerGroup(giveplayer_id)(slot)(gID)
			format(list_stats, sizeof(list_stats), %s%s (UID: %d)  -  %s\n, list_stats, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID) ,PlayerGroup(giveplayer_id)(slot)(gTitle))
		)
	)

	format(list_stats, sizeof(list_stats), %s-----\n, list_stats)

	// Animacja chodzenia
	if(PlayerCache(giveplayer_id)(pWalkAnim))
	(
		anim_id = GetAnimationID(PlayerCache(giveplayer_id)(pWalkAnim))
		format(list_stats, sizeof(list_stats), %s1\tStyl chodzenia:\t\t%s\n, list_stats, AnimInfo(anim_id)(aCommand))
	)
	else
	(
		format(list_stats, sizeof(list_stats), %s1\tStyl chodzenia:\t\tBrak\n, list_stats)
	)
	
	//dodaj duty
	if(PlayerCache(giveplayer_id)(pGroupDuty))
	(
		duty_time = (gettime() - PlayerCache(giveplayer_id)(pGroupDutyTime)) / 60
		format(list_stats, sizeof(list_stats), %s2\tSesja s³u¿by:\t\t(FB5006)%i (FFFFFF)min\n, list_stats,duty_time)
	)

	//areszt
	if(PlayerCache(giveplayer_id)(pArrest))
	(
		arrest_time_h = (PlayerCache(giveplayer_id)(pArrestTime) / (60*60))
		arrest_time_m = ((PlayerCache(giveplayer_id)(pArrestTime) - (arrest_time_h * 60*60)) / 60)
		arrest_time_s = (PlayerCache(giveplayer_id)(pArrestTime) - (arrest_time_h * 60*60) - (arrest_time_m * 60))
		format(list_stats, sizeof(list_stats), %s2\tCzas aresztu:\t\t(FB5006)%i:%i:%i (FFFFFF)\n, list_stats, arrest_time_h, arrest_time_m, arrest_time_s)
	)
	
	if(PlayerCache(playerid)(pAdmin) != 0)
	(
		if(PlayerCache(giveplayer_id)(pFCK) ) gettime())
		(
			fckleft = PlayerCache(giveplayer_id)(pFCK) - gettime()
			fcksec, fckmin, fckhr, fckday
			while(fckleft ) 0) (
				if(fckleft ) (60*60*24)) (
					fckday++
					fckleft -= 60*60*24
					continue
				)
				if(fckleft ) (60*60)) (
					fckhr++
					fckleft -= 60*60
					continue
				)
				if(fckleft ) 60) (
					fckmin++
					fckleft -= 60
					continue
				)
				fcksec += fckleft
				fckleft = 0
			)
			format(list_stats, sizeof(list_stats), %s2\tFCK:\t\t\t(9106FB)%id %ih %im %is (FFFFFF)\n, list_stats, fckday, fckhr, fckmin, fcksec)	
		)
	)

	if(GetViewMode(playerid) == MODE_FIRSTPERSON)
	(
		format(list_stats, sizeof(list_stats), %s3\tTryb kamery:\t\t1 os\n, list_stats)
	)
	else
	(
		format(list_stats, sizeof(list_stats), %s3\tTryb kamery:\t\t3 os\n, list_stats)
	)

	
	format(string, sizeof(string), %s (ID: %d | GID: %d | UID: %d) (%s), PlayerOriginalName(giveplayer_id), giveplayer_id, PlayerCache(giveplayer_id)(pGID), PlayerCache(giveplayer_id)(pUID), IP)
	ShowPlayerDialog(playerid, D_PLAYER_STATS, DIALOG_STYLE_LIST, string, list_stats, OK, Anuluj)
	return 1
)

public OnPlayerDutyStart(playerid, DutyType, DutyTypeUID)
(
	duty_start = gettime() + (2*(60*60)) //+2 GMT
	mysql_query_format(INSERT INTO hrp_duties (duty_type, duty_typeuid, duty_owner, duty_start) VALUES (%d, %d, %d, %d), DutyType, DutyTypeUID, PlayerCache(playerid)(pUID), duty_start)

	PlayerCache(playerid)(pDutyUID) = mysql_insert_id()
	return 1
)

public OnPlayerDutyStop(playerid)
(
	duty_end = gettime() + (2*(60*60)) //+2 GMT
	mysql_query_format(UPDATE hrp_duties SET duty_end = %d WHERE duty_uid = %d LIMIT 1, duty_end, PlayerCache(playerid)(pDutyUID))
	
	PlayerCache(playerid)(pDutyUID) = 0
	return 1
)

public UpdatePlayerStatus(playerid)
(
	// Status AFK
	if(PlayerCache(playerid)(pAFK) (= 0 && !(PlayerCache(playerid)(pStatus) & STATUS_AFK))					PlayerCache(playerid)(pStatus) += STATUS_AFK
	else if(PlayerCache(playerid)(pAFK) ) 0 && (PlayerCache(playerid)(pStatus) & STATUS_AFK))				PlayerCache(playerid)(pStatus) -= STATUS_AFK
	
	// Status nieprzytomny
	if(PlayerCache(playerid)(pBW) && !(PlayerCache(playerid)(pStatus) & STATUS_UNCON))						PlayerCache(playerid)(pStatus) += STATUS_UNCON
	else if(!PlayerCache(playerid)(pBW) && (PlayerCache(playerid)(pStatus) & STATUS_UNCON))					PlayerCache(playerid)(pStatus) -= STATUS_UNCON
	
	// Status naæpany
	if(PlayerCache(playerid)(pRage) && (PlayerCache(playerid)(pRageDrug) != DRUG_MARIHUANA) && !(PlayerCache(playerid)(pStatus) & STATUS_STONED))					PlayerCache(playerid)(pStatus) += STATUS_STONED
	else if(!PlayerCache(playerid)(pRage) && (PlayerCache(playerid)(pStatus) & STATUS_STONED))				PlayerCache(playerid)(pStatus) -= STATUS_STONED
	
	// Status muskularny
	if(PlayerCache(playerid)(pStrength) ) 85.0 && !(PlayerCache(playerid)(pStatus) & STATUS_MUSCULAR))  	PlayerCache(playerid)(pStatus) += STATUS_MUSCULAR
	else if(PlayerCache(playerid)(pStrength) ( 85.0 && (PlayerCache(playerid)(pStatus) & STATUS_MUSCULAR))  PlayerCache(playerid)(pStatus) -= STATUS_MUSCULAR

	// Status pijany
	if(PlayerCache(playerid)(pDrunkLevel) )= 10000 && !(PlayerCache(playerid)(pRageDrug) & DRUG_MARIHUANA) && PlayerCache(playerid)(pBagged) == INVALID_PLAYER_ID && !(PlayerCache(playerid)(pStatus) & STATUS_DRUNK))	 	PlayerCache(playerid)(pStatus) += STATUS_DRUNK
	else if(PlayerCache(playerid)(pDrunkLevel) ( 10000 && (PlayerCache(playerid)(pStatus) & STATUS_DRUNK))  PlayerCache(playerid)(pStatus) -= STATUS_DRUNK
	
	// Status zjarany
	if(PlayerCache(playerid)(pRage) && (PlayerCache(playerid)(pRageDrug) == DRUG_MARIHUANA) && !(PlayerCache(playerid)(pStatus) & STATUS_BAKED))					PlayerCache(playerid)(pStatus) += STATUS_BAKED
	else if(!PlayerCache(playerid)(pRage) && (PlayerCache(playerid)(pStatus) & STATUS_BAKED))
	
	// Status s³uchawki
	if(PlayerCache(playerid)(pMusicPlayerUID) && !(PlayerCache(playerid)(pStatus) & STATUS_EARPIECE))	 	PlayerCache(playerid)(pStatus) += STATUS_EARPIECE
	else if(!PlayerCache(playerid)(pMusicPlayerUID) && (PlayerCache(playerid)(pStatus) & STATUS_EARPIECE))  PlayerCache(playerid)(pStatus) -= STATUS_EARPIECE
	
	// Status pasy
	if(PlayerCache(playerid)(pBelts) && !(PlayerCache(playerid)(pStatus) & STATUS_BELTS))	 				PlayerCache(playerid)(pStatus) += STATUS_BELTS
	else if(!PlayerCache(playerid)(pBelts) && (PlayerCache(playerid)(pStatus) & STATUS_BELTS))				PlayerCache(playerid)(pStatus) -= STATUS_BELTS
	
	// Status zamaskowany
	if(PlayerCache(playerid)(pMaskUID) && !(PlayerCache(playerid)(pStatus) & STATUS_MASKED))				PlayerCache(playerid)(pStatus) += STATUS_MASKED
	else if(!PlayerCache(playerid)(pMaskUID) && (PlayerCache(playerid)(pStatus) & STATUS_MASKED))			PlayerCache(playerid)(pStatus) -= STATUS_MASKED
	
	// Status rêkawiczki
	if(PlayerCache(playerid)(pGloves) && !(PlayerCache(playerid)(pStatus) & STATUS_GLOVES))				 	PlayerCache(playerid)(pStatus) += STATUS_GLOVES
	else if(!PlayerCache(playerid)(pGloves) && (PlayerCache(playerid)(pStatus) & STATUS_GLOVES))		 	PlayerCache(playerid)(pStatus) -= STATUS_GLOVES
	
	// Status kamizelka
	/*if(PlayerCache(playerid)(pArmour) && !(PlayerCache(playerid)(pStatus) & STATUS_ARMOUR))					PlayerCache(playerid)(pStatus) += STATUS_ARMOUR
	else if(!PlayerCache(playerid)(pArmour) && (PlayerCache(playerid)(pStatus) & STATUS_ARMOUR))			PlayerCache(playerid)(pStatus) -= STATUS_ARMOUR*/
	
	// Nowy status kamizelka
	if(PlayerCache(playerid)(pArmorDisplay))
	(
		if(PlayerCache(playerid)(pArmour) && !(PlayerCache(playerid)(pStatus) & STATUS_ARMOUR))					PlayerCache(playerid)(pStatus) += STATUS_ARMOUR
		else if(!PlayerCache(playerid)(pArmour) && (PlayerCache(playerid)(pStatus) & STATUS_ARMOUR))			PlayerCache(playerid)(pStatus) -= STATUS_ARMOUR
	)
	else
	(
		if(PlayerCache(playerid)(pArmour) && (PlayerCache(playerid)(pStatus) & STATUS_ARMOUR)) 		PlayerCache(playerid)(pStatus) -= STATUS_ARMOUR
		else if(!PlayerCache(playerid)(pArmour) && (PlayerCache(playerid)(pStatus) & STATUS_ARMOUR)) 		PlayerCache(playerid)(pStatus) -= STATUS_ARMOUR
	)
	
	// Status rolki
	if(PlayerCache(playerid)(pRoll) && !(PlayerCache(playerid)(pStatus) & STATUS_ROLL))						PlayerCache(playerid)(pStatus) += STATUS_ROLL
	else if(!PlayerCache(playerid)(pRoll) && (PlayerCache(playerid)(pStatus) & STATUS_ROLL))				PlayerCache(playerid)(pStatus) -= STATUS_ROLL
	
	// Status nowa postaæ
	if((PlayerCache(playerid)(pHours) ( 5 && PlayerCache(playerid)(pGamePoints) )= 100) && !(PlayerCache(playerid)(pStatus) & STATUS_NEWCHAR))			 PlayerCache(playerid)(pStatus) += STATUS_NEWCHAR
	else if((PlayerCache(playerid)(pHours) )= 5 && PlayerCache(playerid)(pGamePoints) )= 100) && (PlayerCache(playerid)(pStatus) & STATUS_NEWCHAR))		 PlayerCache(playerid)(pStatus) -= STATUS_NEWCHAR

	// Status nowy gracz
	if(PlayerCache(playerid)(pGamePoints) ( 100 && !(PlayerCache(playerid)(pStatus) & STATUS_NEWPLAYER))	PlayerCache(playerid)(pStatus) += STATUS_NEWPLAYER
	else if(PlayerCache(playerid)(pGamePoints) )= 100 && (PlayerCache(playerid)(pStatus) & STATUS_NEWPLAYER)) PlayerCache(playerid)(pStatus) -= STATUS_NEWPLAYER

	//	Status zwi¹zany
	if(PlayerCache(playerid)(pRoped) != INVALID_PLAYER_ID && !(PlayerCache(playerid)(pStatus) & STATUS_TIED))						PlayerCache(playerid)(pStatus) += STATUS_TIED
	else if(PlayerCache(playerid)(pRoped) == INVALID_PLAYER_ID && (PlayerCache(playerid)(pStatus) & STATUS_TIED))				PlayerCache(playerid)(pStatus) -= STATUS_TIED
	
	//	Status zakneblowany
	if(PlayerCache(playerid)(pGagged) != INVALID_PLAYER_ID && !(PlayerCache(playerid)(pStatus) & STATUS_GAGGED))						PlayerCache(playerid)(pStatus) += STATUS_GAGGED
	else if(PlayerCache(playerid)(pGagged) == INVALID_PLAYER_ID && (PlayerCache(playerid)(pStatus) & STATUS_GAGGED))				PlayerCache(playerid)(pStatus) -= STATUS_GAGGED
	
	// Status worek na g³owie
	if(PlayerCache(playerid)(pBagged) != INVALID_PLAYER_ID && !(PlayerCache(playerid)(pStatus) & STATUS_HEADBAG))						PlayerCache(playerid)(pStatus) += STATUS_HEADBAG
	else if(PlayerCache(playerid)(pBagged) == INVALID_PLAYER_ID && (PlayerCache(playerid)(pStatus) & STATUS_HEADBAG))				PlayerCache(playerid)(pStatus) -= STATUS_HEADBAG
	
	// Status czyta gazete
	if(PlayerCache(playerid)(pRead) == true && !(PlayerCache(playerid)(pStatus) & STATUS_READ)) 			PlayerCache(playerid)(pStatus) += STATUS_READ
	else if(PlayerCache(playerid)(pRead) == false && (PlayerCache(playerid)(pStatus) & STATUS_READ))		PlayerCache(playerid)(pStatus) -= STATUS_READ

	// Status krwawi
	if(PlayerCache(playerid)(pBleeding) ) 0 && !(PlayerCache(playerid)(pStatus) & STATUS_BLEEDING)) 	PlayerCache(playerid)(pStatus) += STATUS_BLEEDING
	else if(PlayerCache(playerid)(pBleeding) == 0 && (PlayerCache(playerid)(pStatus) & STATUS_BLEEDING)) PlayerCache(playerid)(pStatus) -= STATUS_BLEEDING
	
	// Status znany
	if(PlayerCache(playerid)(pCeleb) && !(PlayerCache(playerid)(pStatus) & STATUS_CELEBRITY)) 	PlayerCache(playerid)(pStatus) += STATUS_CELEBRITY
	else if(!PlayerCache(playerid)(pCeleb) && (PlayerCache(playerid)(pStatus) & STATUS_CELEBRITY))  PlayerCache(playerid)(pStatus) -= STATUS_CELEBRITY
	
	// Status narkoman/narkomanka
	if(PlayerCache(playerid)(pDependence) ) 400.0 && !(PlayerCache(playerid)(pStatus) & STATUS_DRUGGY)) PlayerCache(playerid)(pStatus) += STATUS_DRUGGY
	else if(PlayerCache(playerid)(pDependence) ( 400.0 && (PlayerCache(playerid)(pStatus) & STATUS_DRUGGY)) PlayerCache(playerid)(pStatus) -= STATUS_DRUGGY
	
	return 1
)

public LoadPlayerAccess(playerid)
(
	data(256), access_model, access_bone,
 		Float:access_posx, Float:access_posy, Float:access_posz,
  		Float:access_rotx, Float:access_roty, Float:access_rotz,
   		Float:access_scalex, Float:access_scaley, Float:access_scalez

	mysql_query_format(SELECT access_model, access_bone, access_posx, access_posy, access_posz, access_rotx, access_roty, access_rotz, access_scalex, access_scaley, access_scalez FROM hrp_items, hrp_access WHERE item_place = %d AND item_owner = %d AND item_type = %d AND item_used = 1 AND access_uid = item_value1, PLACE_PLAYER, PlayerCache(playerid)(pUID), ITEM_ATTACH)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ddfffffffff, access_model, access_bone, access_posx, access_posy, access_posz, access_rotx, access_roty, access_rotz, access_scalex, access_scaley, access_scalez)

		if(!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_ONE))
		(
			SetPlayerAttachedObject(playerid, SLOT_ACCESS_ONE, access_model, access_bone, access_posx, access_posy, access_posz, access_rotx, access_roty, access_rotz, access_scalex, access_scaley, access_scalez)
		)
		else if(!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_TWO))
		(
  			SetPlayerAttachedObject(playerid, SLOT_ACCESS_TWO, access_model, access_bone, access_posx, access_posy, access_posz, access_rotx, access_roty, access_rotz, access_scalex, access_scaley, access_scalez)
		)
		else if(PlayerCache(playerid)(pPremium) && !IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_THREE))
		(
  			SetPlayerAttachedObject(playerid, SLOT_ACCESS_THREE, access_model, access_bone, access_posx, access_posy, access_posz, access_rotx, access_roty, access_rotz, access_scalex, access_scaley, access_scalez)
		)
		else if(PlayerCache(playerid)(pAASlot) && !IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ACCESS_FOUR))
		(
			SetPlayerAttachedObject(playerid, SLOT_ACCESS_FOUR, access_model, access_bone, access_posx, access_posy, access_posz, access_rotx, access_roty, access_rotz, access_scalex, access_scaley, access_scalez)
		)
	)
	mysql_free_result()
	return 1
)

public UpdatePlayerUnitPositions(playerid)
(
	vehid, group_id_fix,
		Float:PosX, Float:PosY, Float:PosZ
		
	// Usuñ pozycjê pozosta³ych
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

	// Pobierz now¹ pozycjê
	foreach(Player, i)
	(
		if(playerid != i)
		(
			if(Logged(i) && Spawned(i))
			(
	  			if(PlayerCache(i)(pGroupDuty))
	  			(
					group_id_fix = GetPlayerDutyGroupID(i)
					if(group_id_fix != -1)
					(
						if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
						(
							if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
							(
								vehid = GetPlayerVehicleID(i)
								if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == PlayerCache(i)(pGroupDuty))
								(
									GetPlayerPos(i, PosX, PosY, PosZ)
									CreateDynamicMapIcon(PosX, PosY, PosZ, 30, 0, 0, 0, playerid, 200.0)
								)
							)
						)
					)
				)
			)
		)
	)
	
	Streamer_Update(playerid)
	return 1
)

public CreatePlayerCorpse(playerid, killer_uid, weapon_uid)
(
	new	Float:PosX, Float:PosY, Float:PosZ, Float:PosA, VirtualWorldID
		//date = getdate(), corpse_uid

	GetPlayerPos(playerid, PosX, PosY, PosZ)
	GetPlayerFacingAngle(playerid, PosA)

	VirtualWorldID = GetPlayerVirtualWorld(playerid)
	
	//mysql_query_format(INSERT INTO hrp_corpses (corpse_owner, corpse_killer, corpse_weapon, corpse_date) VALUES (%d, %d, %d, %d), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pKiller), PlayerCache(playerid)(pKillerWeapon), date)
	//corpse_uid = mysql_insert_id()

	item_uid, object_id
	mysql_query_format(INSERT INTO hrp_items (item_name, item_type, item_value1, item_value2, item_place, item_owner, item_posx, item_posy, item_posz, item_world, item_weight) VALUES (Zwloki %s, %d, %d, %d, %d, 0, %f, %f, %f, %d, 10.0), PlayerRealName(playerid), ITEM_CORPSE, killer_uid, weapon_uid, PLACE_NONE, PosX, PosY, PosZ, VirtualWorldID)

	item_uid = mysql_insert_id()
	object_id = CreateDynamicObject(ItemTypeInfo(ITEM_CORPSE)(iTypeObjModel), PosX, PosY, PosZ - 1.0, ItemTypeInfo(ITEM_CORPSE)(iTypeObjRotX), ItemTypeInfo(ITEM_CORPSE)(iTypeObjRotY), -PosA, VirtualWorldID, -1, -1, 80.0)

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, item_uid * -1)
	return item_uid
)

public OnPlayerSkillUp(playerid, skill_type)
(
	string(256), skill_type_name(24), Float: skill_percent

	if(skill_type == SKILL_FISH)
	(
		skill_type_name = Lowienie:
		skill_percent = PlayerCache(playerid)(pFishing)
	)
	else if(skill_type == SKILL_STRENGTH)
	(
		skill_type_name = Sila:
		skill_percent = PlayerCache(playerid)(pStrength)
	)
	format(string, sizeof(string), ~b~Poziom ~w~danej umiejetnosci Twojej postaci ulegl ~g~zmianie~w~. ~n~~n~%s: ~y~%.0f%, skill_type_name, skill_percent)
	
   	TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
	TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

	PlayerCache(playerid)(pShowInfoText) = 5
	return 1
)


public PayDay(playerid)
(
	final_pay, g_payed, g_taken
	for(slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerGroup(playerid)(slot)(gUID))
		(
			if(PlayerGroup(playerid)(slot)(gLastPayment) + PAYDAYDAY (= gettime())
			(
				if(PlayerGroup(playerid)(slot)(gTodayDuty) ) 2700)
				(
					group_id_fix = GetGroupID(PlayerGroup(playerid)(slot)(gUID)),
						payment = PlayerGroup(playerid)(slot)(gPayment),
						group_expense = payment - GroupData(group_id_fix)(gDotation)
				//		group_gain = GroupData(group_id_fix)(gDotation) - payment
						
						
					if(GroupData(group_id_fix)(gType) == GROUP_FAMILY)
					(
						continue
					)
					if(GroupData(group_id_fix)(gDotation) (= payment)
					(
						if(GroupData(group_id_fix)(gCash) )= group_expense)
						(
							GroupData(group_id_fix)(gCash) -= group_expense
							SaveGroup(group_id_fix)
						)
						else
						(
							continue
						)
					)
					else
					(
						// @edit: Ktoœ niemi³y bugowa³ to zakomentowaliœmy
						//GroupData(group_id_fix)(gCash) += group_gain
					)
					payment += PAYDAY_CONSTANT * 45
					PlayerCache(playerid)(pBankCash) += payment
					final_pay += payment
					
					PlayerGroup(playerid)(slot)(gTodayDuty) = 0
					
					g_payed = PlayerGroup(playerid)(slot)(gUID)	// zaraz sie przyda
					g_taken = group_expense		// to tez
					
					PlayerGroup(playerid)(slot)(gLastPayment) = gettime()
					mysql_query_format(UPDATE hrp_char_groups SET group_lastpayment = %d WHERE group_uid = %d AND char_uid = %d, gettime(), PlayerGroup(playerid)(slot)(gUID), PlayerCache(playerid)(pUID))
				)
			)
		)
	)
		
	if(final_pay ) 0)
	(
		// i for slot
	//	first = true
		for(i = 0 i ( MAX_GROUP_SLOTS i++)
		(
			if(PlayerGroup(playerid)(i)(gUID))
			(
				if(PlayerGroup(playerid)(i)(gLastPayment) + PAYDAYDAY )= gettime())
				(
			//		first = false
					break
				)
			)
		)
		
		
		// Poka¿ informacjê o wyp³acie
		string(128)
		format(string, sizeof(string), Na Twoje ~y~konto bankowe ~w~wplynela wyplata w wysokosci ~g~$%d, final_pay)
		hrp_GroupActionLog((payday) Gracz %s (UID: %d) pobral wyplate z grupy %s (UID: %d) w wysokosci: $%d, z konta grupy pobrano $%d, PlayerName(playerid), PlayerCache(playerid)(pUID), GroupData(GetGroupID(g_payed))(gName), GroupData(GetGroupID(g_payed))(gUID), final_pay, g_taken)

		TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		PlayerCache(playerid)(pShowInfoText) = 10
		SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
	)
	return 1
)

public AddPlayerReasonToDirectory(playerid, reason())
(
	real_reason(32)
	
	mysql_real_escape_string(reason, real_reason)
	mysql_query_format(INSERT INTO hrp_directory (directory_owner, directory_reason, directory_date) VALUES (%d, %s, NOW()), PlayerCache(playerid)(pUID), real_reason)
	return 1
)

public ShowPlayerDirectoryForPlayer(playerid, giveplayer_id)
(
	string(64), data(64), list_items(256)
	mysql_query_format(SELECT directory_uid, directory_date, directory_reason FROM hrp_directory WHERE directory_owner = %d, PlayerCache(giveplayer_id)(pUID))
	
	new	directory_uid, directory_date(24), directory_reason(32)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ds(24)s(32), directory_uid, directory_date, directory_reason)
		format(list_items, sizeof(list_items), %s\n%d\t%s\t%s, list_items, directory_uid, directory_date, directory_reason)
	)
	mysql_free_result()
	if(strlen(list_items) ) 0)
	(
		format(string, sizeof(string), Kartoteka - %s. Punkty karne: %d, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pPDP))
		ShowPlayerDialog(playerid, D_DIRECTORY_INFO, DIALOG_STYLE_LIST, string, list_items, Szczegó³y, Anuluj)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych wpisów w kartotece., OK, )
	)
	return 1
)

stock ShowPlayerUidDirectoryForPlayer(playerid, uid)
(
	string(64), data(64), list_items(256)
	mysql_query_format(SELECT directory_uid, directory_date, directory_reason FROM hrp_directory WHERE directory_owner = %d, uid)
	
	new	directory_uid, directory_date(24), directory_reason(32)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ds(24)s(32), directory_uid, directory_date, directory_reason)
		format(list_items, sizeof(list_items), %s\n%d\t%s\t%s, list_items, directory_uid, directory_date, directory_reason)
	)
	mysql_free_result()
	if(strlen(list_items) ) 0)
	(
		format(string, sizeof(string), Kartoteka)
		ShowPlayerDialog(playerid, D_DIRECTORY_INFO, DIALOG_STYLE_LIST, string, list_items, Szczegó³y, Anuluj)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych wpisów w kartotece., OK, )
	)
	return 1
)

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
(
	if(PlayerCache(playerid)(pAdmin) != 0)
	(
		hrp_SetPlayerPosFindZ(playerid, fX, fY, fZ)
	)
	return 1
)

public OnPlayerStreamIn(playerid, forplayerid)
(
	SetPlayerFightingStyle(playerid, GetPlayerFightingStyle(playerid))
	SetPlayerFightingStyle(forplayerid, GetPlayerFightingStyle(forplayerid))
	return 1
)

/*
stock SendPlayerMe(playerid, text(128), time=20)
(
	UpdateDynamic3DTextLabelText(Text3D:PlayerCache(playerid)(pMeTag), COLOR_PURPLE, DescWrap(text))
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, Text3D:PlayerCache(playerid)(pMeTag), E_STREAMER_ATTACHED_PLAYER, playerid)
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, Text3D:PlayerCache(playerid)(pMeTag), E_STREAMER_Z, 0.05)
	PlayerCache(playerid)(pMeTime) = time
	return 1
)
*/

stock ApplyPlayerWound(playerid, time, bool:first)
(
	if(!first) return 1

	rand_anim = random(5)
	PlayerCache(playerid)(pWoundedTime) = time
	if(!IsPlayerInAnyVehicle(playerid))
	(
	//	hrp_TogglePlayerControllable(playerid, 0)
	)
	switch(rand_anim)
	(
		case 0:
				ApplyAnimation(playerid, PED, KO_shot_face, 4.1, 0, 1, 1, 1, 0, 1)
		case 1:
				ApplyAnimation(playerid, PED, KO_shot_front, 4.1, 0, 1, 1, 1, 0, 1)
		case 2:
				ApplyAnimation(playerid, PED, KO_shot_stom, 6.1, 0, 1, 1, 1, 0, 1)
		case 3:
				ApplyAnimation(playerid, PED, KO_skid_back, 4.1, 0, 1, 1, 1, 0, 1)
		case 4:
				ApplyAnimation(playerid, PED, KO_skid_front, 4.1, 0, 1, 1, 1, 0, 1)
	)
	
	PlayerCache(playerid)(pWoundAnim) = true
	return 1
)

stock PlayerGlobalName(playerid, color = COLOR_GREY)
(
	name(MAX_PLAYER_NAME + 20)

	c(10)
	format(c, sizeof(c), %06x, color ))) 8)

	format(name, sizeof(name), (%s)%s(%s), AL(PlayerCache(playerid)(pUserColor))(lColor), PlayerCache(playerid)(pGlobalName), c)
	return name
)

stock PlayerName(playerid)
(
	pos, name(MAX_PLAYER_NAME)
	strmid(name, PlayerCache(playerid)(pName), 0, strlen(PlayerCache(playerid)(pName)), 24)
	
	pos = strfind(name, _, true)
	while(pos != -1)
	(
		name(pos) =  
		pos = strfind(name, _, true)
	)
	return name
)

stock PlayerRealName(playerid)
(
	pos, name(MAX_PLAYER_NAME)
	GetPlayerName(playerid, name, sizeof(name))

	pos = strfind(name, _, true)
	while(pos != -1)
	(
		name(pos) =  
		pos = strfind(name, _, true)
	)
	return name
)

stock PlayerOriginalName(playerid)
(
	name(MAX_PLAYER_NAME)
	GetPlayerName(playerid, name, sizeof(name))
	return name
)

stock SetPlayerMoney(playerid, money)
(
	ResetPlayerMoney(playerid)
	GivePlayerMoney(playerid, money)
	return 1
)

stock GetPlayerID(playeruid)
(
	playerid = INVALID_PLAYER_ID
	foreach(Player, i)
	(
		if(PlayerCache(i)(pUID) == playeruid)
		(
			playerid = i
			break
		)
	)
	return playerid
)

stock IsGlobalLogged(player_gid)
(
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pGID) == player_gid)
			(
				return true
			)
		)
	)
	return false
)

stock PlayerToPlayer(Float:radi, playerid, targetid)
(
	if(GetPlayerState(targetid) == PLAYER_STATE_SPECTATING)
	(
		return 0
	)
	
	Float:posx, Float:posy, Float:posz,
		Float:oldposx, Float:oldposy, Float:oldposz,
		Float:tempposx, Float:tempposy, Float:tempposz

	GetPlayerPos(playerid, oldposx, oldposy, oldposz)

	GetPlayerPos(targetid, posx, posy, posz)
	tempposx = (oldposx -posx)
	tempposy = (oldposy -posy)
	tempposz = (oldposz -posz)

 	if (((tempposx ( radi) && (tempposx ) -radi)) && ((tempposy ( radi) && (tempposy ) -radi)) && ((tempposz ( radi) && (tempposz ) -radi)))
	(
		return 1
	)
	return 0
)

stock ClearChat(playerid)
(
	for(i = 1 i ( 40 i++)
	(
		SendClientMessage(playerid, COLOR_WHITE,  )
	)
	return 1
)

stock GetPlayerDoorID(playerid)
(
	doorid = INVALID_DOOR_ID
	for(d=0d ( MAX_DOORS d++)
	(
		if(DoorData(d)(dUID))
		(
			if(GetPlayerVirtualWorld(playerid) != 0 && GetPlayerVirtualWorld(playerid) == DoorData(d)(dExitVW))
			(
				doorid = d
				break
			)
		)
	)
	return doorid
)
/*
	ta, wiem, ¿e to jest szybsze ale widocznie coœ siê zjeba³o i zrobiê po swoiemu, wolniej
*/
/*stock GetPlayerDoorID(playerid)
(
	doorid = INVALID_DOOR_ID
	foreach(Doors, d)
	(
		if(DoorData(d)(dUID))
		(
			if(GetPlayerVirtualWorld(playerid) != 0 && GetPlayerVirtualWorld(playerid) == DoorData(d)(dExitVW))
			(
				doorid = d
				break
			)
		)
	)
	return doorid
)*/

stock GetPlayerStatusInfo(playerid)
(
	status(24), main_status(128)

	format(main_status, sizeof(main_status), )
	if(PlayerCache(playerid)(pStatus) & STATUS_DRUNK)
	(
		if(PlayerCache(playerid)(pSex) == 1)	format(status, sizeof(status), pijany)
		else									format(status, sizeof(status), pijana)

   		if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)

	if(PlayerCache(playerid)(pStatus) & STATUS_BAKED)
	(
		if(PlayerCache(playerid)(pSex) == 1)	format(status, sizeof(status), zjarany)
		else									format(status, sizeof(status), zjarana)

   		if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_STONED)
	(
 		if(PlayerCache(playerid)(pSex) == 1)	format(status, sizeof(status), naæpany)
 		else									format(status, sizeof(status), naæpana)

		if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)

	if(PlayerCache(playerid)(pStatus) & STATUS_AFK)
	(
		hour, minute
		gettime(hour, minute)
		
		format(status, sizeof(status), AFK od %02d:%02d, hour, minute)

   		if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_MUSCULAR)
	(
		if(PlayerCache(playerid)(pSex) == 1)	format(status, sizeof(status), muskularny)
		else									format(status, sizeof(status), umiêœniona)
	
		if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_UNCON)
	(
		if(PlayerCache(playerid)(pSex) == 1)	format(status, sizeof(status), nieprzytomny)
		else									format(status, sizeof(status), nieprzytomna)

	   	if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_EARPIECE)
	(
 		format(status, sizeof(status), s³ucha muzyki)

	   	if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_BELTS)
	(
 		format(status, sizeof(status), pasy)

	   	if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_MASKED)
	(
 		if(PlayerCache(playerid)(pSex) == 1)	format(status, sizeof(status), zamaskowany)
		else									format(status, sizeof(status), zamaskowana)

	   	if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_GLOVES)
	(
		format(status, sizeof(status), rêkawiczki)

	   	if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_ARMOUR)
	(
		format(status, sizeof(status), kamizelka)

	   	if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_ROLL)
	(
		format(status, sizeof(status), rolki)

	   	if(strlen(main_status) ) 0)
		(
  			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_NEWCHAR)
	(
		format(status, sizeof(status), nowa postaæ)
		
		if(strlen(main_status) ) 0)
		(
			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_NEWPLAYER)
	(
		format(status, sizeof(status), nowy gracz)
		
		if(strlen(main_status) ) 0)
		(
			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_GAGGED)
	(
		format(status, sizeof(status), knebel)
		
		if(strlen(main_status) ) 0)
		(
			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_TIED)
	(
		if(PlayerCache(playerid)(pSex) == 1)	format(status, sizeof(status), zwi¹zany)
		else									format(status, sizeof(status), zwi¹zana)
		
		if(strlen(main_status) ) 0)
		(
			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_HEADBAG)
	(
		format(status, sizeof(status), worek na g³owie)
		
		if(strlen(main_status) ) 0)
		(
			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_READ)
	(
		format(status, sizeof(status), czyta gazetê)
		
		if(strlen(main_status) ) 0)
		(
			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)

	if(PlayerCache(playerid)(pStatus) & STATUS_BLEEDING)
	(
		format(status, sizeof(status), krwawi)

		if(strlen(main_status) ) 0)
		(
			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_CELEBRITY)
	(
		if(PlayerCache(playerid)(pSex) == 1)	format(status, sizeof(status), znany)
		else									format(status, sizeof(status), znana)

		if(strlen(main_status) ) 0)
		(
			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(PlayerCache(playerid)(pStatus) & STATUS_DRUGGY)
	(
		if(PlayerCache(playerid)(pSex) == 1)	format(status, sizeof(status), narkoman)
		else									format(status, sizeof(status), narkomanka)

		if(strlen(main_status) ) 0)
		(
			strcat(main_status, , , sizeof(main_status))
		)
		strcat(main_status, status, sizeof(main_status))
	)
	
	if(strlen(main_status))	format(main_status, sizeof(main_status), \n(%s), main_status)

	return main_status
)

stock GetPlayerSpeed(playerid, get3d)
(
	Float: x, Float: y, Float: z
	if (IsPlayerInAnyVehicle (playerid)) GetVehicleVelocity(GetPlayerVehicleID(playerid), x, y, z)
	else GetPlayerVelocity (playerid, x, y, z)
	return Speed(x, y, z, 100.0, get3d)
)

stock GetVehicleMaxSpeed(vehicleid)
(
	modelid = GetVehicleModel (vehicleid) - 400
	if(modelid )= 0 && modelid ( sizeof (VehicleData))
	(
		return VehicleData(modelid)(vMaxSpeed)
	)
	return 9999
)

stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance) //by Y_Less
(
 	Float:a
 	GetPlayerPos(playerid, x, y, a)
 	GetPlayerFacingAngle(playerid, a)
 	
 	x += (distance * floatsin(-a, degrees))
 	y += (distance * floatcos(-a, degrees))
)

stock GetXYInFrontOfPoint(&Float:x, &Float:y, Float:angle, Float:distance)
(
        x += (distance * floatsin(-angle, degrees))
        y += (distance * floatcos(-angle, degrees))
)

stock GetXYInFrontOfObject(object_id, &Float:x, &Float:y, Float:distance)
(
 	Float:z,
 		Float:rotx, Float:roty, Float:rotz

 	GetDynamicObjectPos(object_id, x, y, z)
	GetDynamicObjectRot(object_id, rotx, roty, rotz)

 	x -= (distance * floatsin(-rotz, degrees))
 	y -= (distance * floatcos(-rotz, degrees))
)

stock GetXYBehindOfObject(object_id, &Float:x, &Float:y, Float:distance)
(
 	Float:z,
 		Float:rotx, Float:roty, Float:rotz

 	GetDynamicObjectPos(object_id, x, y, z)
	GetDynamicObjectRot(object_id, rotx, roty, rotz)

 	x += (distance * floatsin(-rotz, degrees))
 	y += (distance * floatcos(-rotz, degrees))
)

stock IsPlayerFacingVehicle(playerid, vehicleid)
(
	Float:plPosX, Float:plPosZ, Float:plPosY, Float:vePosX, Float:vePosY, Float:vePosZ, Float:MainAngle

	GetVehiclePos(vehicleid, vePosX, vePosY, vePosZ)
	GetPlayerPos(playerid, plPosX, plPosY, plPosZ)

	if( vePosY ) plPosY ) MainAngle = (-acos((vePosX - plPosX) / floatsqroot((vePosX - plPosX) * (vePosX - plPosX) + (vePosY - plPosY) * (vePosY - plPosY))) - 90.0)
	else if( vePosY ( plPosY && vePosX ( plPosX ) MainAngle = (acos((vePosX - plPosX) / floatsqroot((vePosX - plPosX) * (vePosX - plPosX) + (vePosY - plPosY) * (vePosY - plPosY))) - 450.0)
	else if( vePosY ( plPosY ) MainAngle = (acos((vePosX - plPosX) / floatsqroot((vePosX - plPosX) * (vePosX - plPosX) + (vePosY - plPosY) * (vePosY - plPosY))) - 90.0)

	if(vePosX ) plPosX) MainAngle = (floatabs(floatabs(MainAngle) + 180.0))
	else MainAngle = (floatabs(MainAngle) - 180.0)

	Float:plAngle
	GetPlayerFacingAngle(playerid, plAngle)
	
	if(MainAngle - plAngle ( -130 || MainAngle - plAngle ) 130)
	(
		return 0
	)
	return 1
)

stock IsPlayerFacingObject(playerid, object_id)
(
	Float:plPosX, Float:plPosZ, Float:plPosY, Float:obPosX, Float:obPosY, Float:obPosZ, Float:MainAngle

	GetDynamicObjectPos(object_id, obPosX, obPosY, obPosZ)
	GetPlayerPos(playerid, plPosX, plPosY, plPosZ)

	if( obPosY ) plPosY ) MainAngle = (-acos((obPosX - plPosX) / floatsqroot((obPosX - plPosX) * (obPosX - plPosX) + (obPosY - plPosY) * (obPosY - plPosY))) - 90.0)
	else if( obPosY ( plPosY && obPosX ( plPosX ) MainAngle = (acos((obPosX - plPosX) / floatsqroot((obPosX - plPosX) * (obPosX - plPosX) + (obPosY - plPosY) * (obPosY - plPosY))) - 450.0)
	else if( obPosY ( plPosY ) MainAngle = (acos((obPosX - plPosX) / floatsqroot((obPosX - plPosX) * (obPosX - plPosX) + (obPosY - plPosY) * (obPosY - plPosY))) - 90.0)

	if(obPosX ) plPosX) MainAngle = (floatabs(floatabs(MainAngle) + 180.0))
	else MainAngle = (floatabs(MainAngle) - 180.0)

	Float:plAngle
	GetPlayerFacingAngle(playerid, plAngle)

	if(MainAngle - plAngle ( -130 || MainAngle - plAngle ) 130)
	(
		return 0
	)
	return 1
)

stock IsPlayerAFK(playerid)
(
	if(PlayerCache(playerid)(pAFK) ( 0)
	(
		return 1
	)
	return 0
)

stock IsPlayerInArea(playerid, Float:max_x, Float:min_x, Float:max_y, Float:min_y)
(
	Float:X, Float:Y, Float:Z
 	GetPlayerPos(playerid, X, Y, Z)
  	if(X (= max_x && X )= min_x && Y (= max_y && Y )= min_y) return 1
   	return 0
)

stock IsPlayerInSquare(playerid, Float:MinX, Float:MinY, Float:MaxX, Float:MaxY)
(
    Float:X, Float:Y, Float:Z

    GetPlayerPos(playerid, X, Y, Z)
    if(X )= MinX && X (= MaxX && Y )= MinY && Y (= MaxY) (
        return 1
    )
    return 0
)

stock IsPlayerInWater(playerid)
(
	Float:x,Float:y,Float:z
	GetPlayerPos(playerid, x, y, z)
	
	if (
	(IsPlayerInArea(playerid, 2032.1371, 1841.2656, 1703.1653, 1467.1099) && z (= 9.0484) //lv piratenschiff
	|| (IsPlayerInArea(playerid, 2109.0725, 2065.8232, 1962.5355, 10.8547) && z (= 10.0792) //lv visage
	|| (IsPlayerInArea(playerid, -492.5810, -1424.7122, 2836.8284, 2001.8235) && z (= 41.06) //lv staucamm
	|| (IsPlayerInArea(playerid, -2675.1492, -2762.1792, -413.3973, -514.3894) && z (= 4.24) //sf südwesten kleiner teich
	|| (IsPlayerInArea(playerid, -453.9256, -825.7167, -1869.9600, -2072.8215) && z (= 5.72) //sf gammel teich
	|| (IsPlayerInArea(playerid, 1281.0251, 1202.2368, -2346.7451, -2414.4492) && z (= 9.3145) //ls neben dem airport
	|| (IsPlayerInArea(playerid, 2012.6154, 1928.9028, -1178.6207, -1221.4043) && z (= 18.45) //ls mitte teich
	|| (IsPlayerInArea(playerid, 2326.4858, 2295.7471, -1400.2797, -1431.1266) && z (= 22.615) //ls weiter südöstlich
	|| (IsPlayerInArea(playerid, 2550.0454, 2513.7588, 1583.3751, 1553.0753) && z (= 9.4171) //lv pool östlich
	|| (IsPlayerInArea(playerid, 1102.3634, 1087.3705, -663.1653, -682.5446) && z (= 112.45) //ls pool nordwestlich
	|| (IsPlayerInArea(playerid, 1287.7906, 1270.4369, -801.3882, -810.0527) && z (= 87.123) //pool bei maddogs haus oben
	)
	(
		return 1
	)
	return 0
)

stock BagPlayerHead(playerid)
(
	TextDrawShowForPlayer(playerid,TextDrawHeadbag(playerid))
	SetPlayerCameraPos(playerid, 0, 0, 0)
	SetPlayerCameraLookAt(playerid,0,0,-50)
	SetPlayerDrunkLevel(playerid,50000)
	return 1
)

stock UnbagPlayerHead(playerid)
(
	TextDrawHideForPlayer(playerid,TextDrawHeadbag(playerid))
	SetCameraBehindPlayer(playerid)
	SetPlayerDrunkLevel(playerid,0)
	return 1
)

// Wiadomoœci Offline
stock AddPlayerOfflineMessage(playeruid, text())
(
	// Tworzenie wiadomoœci dla goœcia, którego nie ma teraz w grze.
	mysql_query_format(INSERT INTO hrp_messages VALUES(NULL, %d, %s), playeruid, text)
	return 1
)

stock PrintPlayerOfflineMessages(playerid)
(
	buffer(256)
	format(buffer, sizeof(buffer), SELECT msg_owner, msg_content FROM hrp_messages WHERE msg_owner = %d, PlayerCache(playerid)(pUID))
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		msg_owner, msg_content(256), msg_count = 1
		while(mysql_fetch_row(buffer, |))
		(
			sscanf(buffer, p(|)ds(256), msg_owner, msg_content)
			format(msg_content, sizeof(msg_content), Informacja %d: (DDDDDD)%s, msg_count, msg_content)
			SendClientMessage(playerid, 0x2989D8FF, msg_content) 
			msg_count += 1
		)
	)
	mysql_free_result()
	
	mysql_query_format(DELETE FROM hrp_messages WHERE msg_owner = %d, PlayerCache(playerid)(pUID))
	return 1
)

// Weryfikacja
forward GoogleVerifyResponse(playerid, response_code, data())
public GoogleVerifyResponse(playerid, response_code, data())
(
	if(response_code == 200)
	(
		page_response = strval(data)
		if( page_response ) 0 )
		(
			sendClientPoop(playerid, » Weryfikacja dwuetapowa przebieg³a pomyœlnie.)
			PlayerCache(playerid)(pVerificated) = true
		)
		else
		(
			sendClientPoop(playerid, » Zly kod.)
			ShowPlayerDialog(playerid, D_VERIFICATE, DIALOG_STYLE_INPUT, Weryfikacja dwuetapowa, Wypisz poni¿ej kod wygenerowany przez aplikacjê Google Authenticator., Gotowe, Anuluj)
		)
	)
	else if( response_code == 3 )
	(
		//nothing
	)
	else
	(
		Kick(playerid)
	)
)

stock GetPlayerFameStatus(playerid)
(
	mysql_query_format(SELECT * FROM hrp_celebs WHERE cb_char = %d, PlayerCache(playerid)(pUID))
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		// Jest celebryt¹
		mysql_free_result()
		
		PlayerCache(playerid)(pCeleb) = true
	)
	else
	(
		// Nie jest celebryt¹
		mysql_free_result()
		
		PlayerCache(playerid)(pCeleb) = false
	)
	return 1
)