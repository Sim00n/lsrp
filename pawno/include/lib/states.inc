public OnPlayerStateChange(playerid, newstate, oldstate)
(
	string(256)
	
	// Spectate
 	foreach(Player, i)
  	(
   		if(Logged(i) && Spawned(i))
	 	(
	  		if(PlayerCache(i)(pSpectate) == playerid)
	  		(
				switch(newstate)
		  		(
	 				case 0, 1, 7, 8:
					(
						PlayerSpectatePlayer(i, playerid)
						SetPlayerInterior(i, GetPlayerInterior(playerid))
					)
					case 2, 3:
					(
						PlayerSpectateVehicle(i , GetPlayerVehicleID(playerid))
					)
		   			case 9:
					(
						TogglePlayerSpectating(i, 0)
						
	   					hrp_SetPlayerPos(i, PlayerCache(i)(pPosX), PlayerCache(i)(pPosY), PlayerCache(i)(pPosZ))

						SetPlayerVirtualWorld(i, PlayerCache(i)(pVW))
						SetPlayerInterior(i, PlayerCache(i)(pInt))
						
						SetCameraBehindPlayer(i)
					)
				)
		  	)
		)
   	)
	
	if(newstate == PLAYER_STATE_SPAWNED)
	(
		if(!Spawned(playerid))
		(
			Spawned(playerid) = true
		)
	)
	
	// wsiadl do wozu
	
	if(newstate == PLAYER_STATE_DRIVER)
	(
		vehid = GetPlayerVehicleID(playerid), model = GetVehicleModel(vehid)
		if(model == 509 || model == 510 || model == 481)
		(
			return 1
		)
  		if(!CarInfo(vehid)(cEngineTogged))
  		(
			TextDrawSetString(Text:TextDrawMainInfo(playerid), Wcisnij ~r~~k~~VEHICLE_HANDBRAKE~ + ~k~~VEHICLE_FIREWEAPON~~w~ jednoczesnie, aby uruchomic silnik. Klawisz ~g~~k~~VEHICLE_FIREWEAPON_ALT~~w~ kontroluje swiatla w pojezdzie.)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

			PlayerCache(playerid)(pShowInfoText) = 5
		)
  		ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))
		
		if(model == 574)
		(
			if(PlayerCache(playerid)(pJob) == JOB_SWEEPER)
			(
				if(PlayerCache(playerid)(pDailyIncome) )= MAX_DAILY_INCOME)
				(
					GuiMsg(playerid, Wyczerpa³eœ dzisiejszy limit dochodu z prac dorywczych.\nWróæ jutro., 1)
					RemovePlayerFromVehicle(playerid)
					return 1
				)
				
				
				ShowPlayerDialog(playerid, D_SWEEP_ACCEPT, DIALOG_STYLE_MSGBOX, Praca sprz¹tacza ulic, Wsiad³eœ do pojazdu Sweeper. Urz¹d miasta udostêpnia Ci go do wykonania Twojej pracy czyszczenia ulic. Czy akceptujesz pracê sprz¹tacza?, Akceptuj, Odrzuæ)
			)
			else
			(
				RemovePlayerFromVehicle(playerid)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ sprz¹taczem ulic. Aby zmieniæ swoj¹ pracê dorywcz¹ udaj siê do urzêdu., OK, )
			)
		)
		
		//no prêdkoœæ trzeba przecie¿ ustawiæ, sama sie nie ustawi
		//POTEM DODAJ WYJ¥TKI DLA HELIKOPTERÓW I SAMOLOTÓ
		
		/*if(model != 462 && 
		model != 461 &&
		model != 463 &&
		model != 468 &&
		model != 471 &&
		model != 521 &&
		model != 522 &&
		model != 523 &&
		model != 581 &&
		model != 586 &&
		model != 417 && 
		model != 425 && 
		model != 447 && 
		model != 446 && 
		model != 452 && 
		model != 453 && 
		model != 454 && 
		model != 460 && 
		model != 469 && 
		model != 472 && 
		model != 473 && 
		model != 476 && 
		model != 484 && 
		model != 487 && 
		model != 488 && 
		model != 493 && 
		model != 497 && 
		model != 511 && 
		model != 512 && 
		model != 513 && 
		model != 519 && 
		model != 520 && 
		model != 548 && 
		model != 553 && 
		model != 563 && 
		model != 577 && 
		model != 593 && 
		model != 592 && 
		model != 595)
		(
			Float:boost = CarInfo(vehid)(cBoost)
			Float:maxCap = (float(GetVehicleMaxSpeed(vehid)) / 160.0)
			
			if(boost )= 35.0)
			(
				DisablePlayerSpeedCap( playerid )
			)
			else
			(
				Float:cap = (maxCap * (65.0 + boost)) / 100.0
				SetPlayerSpeedCap( playerid, Float:cap )
			)
		)
		else
		(
			DisablePlayerSpeedCap( playerid )
		)*/
		
		GetVehiclePos(vehid, OldVehiclePosition(vehid)(0), OldVehiclePosition(vehid)(1), OldVehiclePosition(vehid)(2))
		
		// wycofujemy skrypt silników
		DisablePlayerSpeedCap(playerid)
		
		// Dodaj checkpoint jeœli Course
		if(PlayerCache(playerid)(pCourse))
		(
			if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
			(
				group_id_fix = GetGroupID(CarInfo(vehid)(cOwner))
				if(GroupData(group_id_fix)(gType) == GROUP_DRIVING)
				(
					SetPlayerRaceCheckpoint(playerid, 0, 1090.8137,-1745.6072,13.4456, 1170.5844,-1742.2474,13.3984, 5.0)
					PlayerCache(playerid)(pCourseCP) = 1
					PlayerCache(playerid)(pCourseVeh) = vehid
					PlayerCache(playerid)(pCourseMS) = 0.0
					//PlayerCache(playerid)(pCourseHP) = CarInfo(vehid)(cHealth)
					
					ChangeVehicleEngineStatus(vehid, 1)
					CarInfo(vehid)(cEngineTogged) = true
					
					GuiMsg(playerid, Rozpocz¹³eœ egzamin, pod¹¿aj za punktami.\nPoruszaj siê zgodnie z zasadami ruchu drogowego!, 0)
				)
			)
		)
	)
	if(newstate == PLAYER_STATE_ONFOOT)
	(
		// Schowaj info o szybie
		TextDrawHideForPlayer(playerid, Text:TextDrawWindow(playerid))
		
		
		if(oldstate == PLAYER_STATE_PASSENGER || oldstate == PLAYER_STATE_DRIVER)
		(
			vehid = PlayerCache(playerid)(pLastVeh)
			
			// Anti Car TP
			GetVehiclePos(vehid, OldVehiclePosition(vehid)(0), OldVehiclePosition(vehid)(1), OldVehiclePosition(vehid)(2))
			
			// Przyciemniony szyby
			if(CarInfo(vehid)(cAccess) & VEH_ACCESS_DIM)
			(
				if(!PlayerCache(playerid)(pMaskUID))
				(
					if(!PlayerCache(playerid)(pAdminDuty))
					(
						name(32)
						GetPlayerName(playerid, name, sizeof(name))
						strmid(PlayerCache(playerid)(pName), name, 0, strlen(name), 32)

						format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
						Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
					)
				)
			)
			
			if(GetVehicleModel(vehid) == 574)
			(
				if(PlayerCache(playerid)(pSweep))
				(
					PlayerCache(playerid)(pSweep) = false
					PlayerCache(playerid)(pSweepStep) = 0
					PlayerCache(playerid)(pSweepSteps) = 0
					PlayerCache(playerid)(pSweepRoute) = 0
								
					TextDrawSetString(Text:TextDrawMainInfo(playerid), Wysiadles ze Sweepera dlatego Twoja praca zostala ~r~anulowana.)
					TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
					PlayerCache(playerid)(pShowInfoText) = 7
				)
				
				DisablePlayerRaceCheckpoint(playerid)
				
				UpdateVehicleDamageStatus(vehid, 0, 0, 0, 0)
				GetVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))

				CarInfo(vehid)(cHealth) = 1000.0
				SetVehicleHealth(vehid, 1000.0)

				SaveVehicle(vehid, SAVE_VEH_COUNT)
				SaveVehicle(vehid, SAVE_VEH_ACCESS)
				
				SetVehicleToRespawn(vehid)
			)
		)
	)
	if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)
	(
		if(PlayerCache(playerid)(pDrunkLevel) ( 500)
		(
			SetPlayerDrunkLevel(playerid, 0)
		)
		if(PlayerCache(playerid)(pAudioHandle) && PlayerCache(playerid)(pMusicPlayerUID) == 0)
		(
			StopAudioStreamForPlayer(playerid)
			PlayerCache(playerid)(pAudioHandle) = 0
		)

			//Audio_Stop(playerid, PlayerCache(playerid)(pAudioHandle))
		
		// Jeœli kierowca taksówki wysi¹dzie
		if(PlayerCache(playerid)(pTaxiPassenger) != INVALID_PLAYER_ID)
		(
			passenger_id = PlayerCache(playerid)(pTaxiPassenger), price = PlayerCache(passenger_id)(pTaxiPay)

			if(price ) 0)
			(
				price = price ) PlayerCache(playerid)(pCash) ? PlayerCache(playerid)(pCash) : price
			
	  			group_cash = floatround(0.50 * price),
					playercash = floatround(0.50 * price)
					
				hrp_GivePlayerMoney(passenger_id, -price)
				
				// zabezpieczenie przed bugowaniem - seler
				if(PlayerCache(playerid)(pGroupDuty))
				(
					hrp_GivePlayerMoney(playerid, playercash)

					group_id_fix = GetPlayerDutyGroupID(playerid)
					
					GroupData(group_id_fix)(gCash) += group_cash
					SaveGroup(group_id_fix)
					
					format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
					
					AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(playerid)(pUID), PlayerCache(passenger_id)(pUID), price, group_cash, Taxi)
				)
				else
				(
					printf((taxi-bug) Gracz %s (UID: %d) prawdopodobnie chcial teraz zbugowac nasz system bez duty z graczem %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), PlayerName(passenger_id), PlayerCache(passenger_id)(pUID))
					format(string,sizeof(string),Nie jesteœ na s³u¿bie grupy, nie otrzymasz gotówki za przewóz klienta.)
					GuiMsg(playerid,string,0)
				)
				
	   			format(string, sizeof(string), Zap³aci³eœ $%d za przejazd taksówk¹., price)
				ShowPlayerDialog(passenger_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			)

			PlayerCache(playerid)(pTaxiPassenger) = INVALID_PLAYER_ID

			PlayerCache(passenger_id)(pTaxiVeh) = INVALID_VEHICLE_ID
			PlayerCache(passenger_id)(pTaxiPay) = 0
			PlayerCache(passenger_id)(pTaxiPrice) = 0
		)
		
		// Jeœli bierze udzia³ w wyœcigu
		if(PlayerCache(playerid)(pRacePhase))
		(
			if(PlayerCache(playerid)(pRacePhase) == 3)
			(
				TextDrawSetString(Text:TextDrawMainInfo(playerid), Nie mozesz ~y~wysiadac ~w~z pojazdu podczas trwania ~g~wyscigu~w~.~n~~n~Zostales ~r~zdyskwalifikowany~w~.)
			)
			else
			(
				TextDrawSetString(Text:TextDrawMainInfo(playerid), Proces tworzenia wyscigu zostal ~r~przerwany~w~.)
			)
  			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			PlayerCache(playerid)(pShowInfoText) = 5
			
			DisablePlayerRaceCheckpoint(playerid)
			
   			PlayerCache(playerid)(pRacePhase) = 0
	  		PlayerCache(playerid)(pRacePoint) = 0

			PlayerCache(playerid)(pRaceCheckpoints) = 0
		)
		
		vehid = PlayerCache(playerid)(pLastVeh)
		
		// Jeœli w³¹czony GPS
		if(CarInfo(vehid)(cGPS))
		(
			if(IsPlayerInGroupType(playerid, GROUP_POLICE))
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
		
		// Odepnij pasy
		if(PlayerCache(playerid)(pBelts))	PlayerCache(playerid)(pBelts) = false
	)
	if(oldstate == PLAYER_STATE_PASSENGER && newstate == PLAYER_STATE_ONFOOT)
	(
		// Jeœli pasa¿er taksówki wysi¹dzie
 		if(PlayerCache(playerid)(pTaxiVeh) != INVALID_VEHICLE_ID)
		(
			driverid = GetVehicleDriver(PlayerCache(playerid)(pTaxiVeh)), price = PlayerCache(playerid)(pTaxiPay)

			if(price ) 0)
			(
				price = price ) PlayerCache(playerid)(pCash) ? PlayerCache(playerid)(pCash) : price
			
	  			group_cash = floatround(0.50 * price),
					playercash = floatround(0.50 * price)
					
				hrp_GivePlayerMoney(playerid, -price)

				// zabezpieczenie przed bugowaniem - seler
				if(PlayerCache(driverid)(pGroupDuty))
				(
					hrp_GivePlayerMoney(driverid, playercash)

					group_id_fix = GetPlayerDutyGroupID(driverid)
					
					GroupData(group_id_fix)(gCash) += group_cash
					SaveGroup(group_id_fix)
					
					format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
					ShowPlayerDialog(driverid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
					
					AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(driverid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Taxi)
				)
				else
				(
					printf((taxi-bug) Gracz %s (UID: %d) prawdopodobnie chcial teraz zbugowac nasz system bez duty z graczem %s (UID: %d)., PlayerName(driverid), PlayerCache(driverid)(pUID), PlayerName(playerid), PlayerCache(playerid)(pUID))
					format(string,sizeof(string),Nie jesteœ na s³u¿bie grupy, nie otrzymasz gotówki za przewóz klienta.)
					GuiMsg(driverid,string,0)
				)
				
	   			format(string, sizeof(string), Zap³aci³eœ $%d za przejazd taksówk¹., price)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			)
						
			PlayerCache(driverid)(pTaxiPassenger) = INVALID_PLAYER_ID
			
			PlayerCache(playerid)(pTaxiVeh) = INVALID_VEHICLE_ID
			PlayerCache(playerid)(pTaxiPay) = 0
			PlayerCache(playerid)(pTaxiPrice) = 0
		)
		
		// Odepnij pasy
		if(PlayerCache(playerid)(pBelts))	PlayerCache(playerid)(pBelts) = false
	)
	
	if(oldstate == PLAYER_STATE_ONFOOT && (newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER))
	(	
		vehid = GetPlayerVehicleID(playerid)
		if(strlen(CarInfo(vehid)(cAudioURL)))
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
			//Audio_StopRadio(playerid)
	  		//PlayerCache(playerid)(pAudioHandle) = Audio_PlayStreamed(playerid, CarInfo(vehid)(cAudioURL))
			
			PlayerCache(playerid)(pAudioHandle) = 1
			PlayAudioStreamForPlayer(playerid, CarInfo(vehid)(cAudioURL))
			
		)
		/*
		if(HasWindow(vehid))
		(
			if(GetPlayerWindowStatus(vehid, playerid))
			(
				TextDrawSetString(Text:TextDrawWindow(playerid), Szyba otwarta)
				TextDrawShowForPlayer(playerid, Text:TextDrawWindow(playerid))
			)
			else
			(
				TextDrawSetString(Text:TextDrawWindow(playerid), Szyba zamknieta)
				TextDrawShowForPlayer(playerid, Text:TextDrawWindow(playerid))
			)
		)
		*/
	)
	
	
	// wysiad³ z wozu
	if((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) && newstate == PLAYER_STATE_ONFOOT)
	(
		if(PlayerCache(playerid)(pAudioHandle) && !PlayerCache(playerid)(pMusicPlayerUID))
		(
			StopAudioStreamForPlayer(playerid)
			PlayerCache(playerid)(pAudioHandle) = 0
			
		)
			
		//if(PlayerCache(playerid)(pCourse))
			//PlayerCache(playerid)(pCourseVeh) = INVALID_VEHICLE_ID
	)
	
	SyncCamera(playerid)
	return 1
)

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
(
	if(newkeys & KEY_CROUCH)
	(
		if(IsPlayerInAnyVehicle(playerid))
		(
			if(PlayerCache(playerid)(pFlood) (= 0)
			(
				cmd_brama(playerid, skrypt)
				PlayerCache(playerid)(pFlood) = 2
			)
		)
	)
	
	if(PlayerCache(playerid)(pFueling))
	(
		if(newkeys & KEY_SPRINT)
		(
				price = floatround(RefuelData(playerid)(rPrice)), value = RefuelData(playerid)(rLiters), vehid = RefuelData(playerid)(rVeh), string(128)
				if(PlayerCache(playerid)(pCash) ( price) // brak³o kaski, jakiœ jebany buger
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz takiej iloœci gotówki., OK, )
					PlayerCache(playerid)(pFueling) = false
					RefuelData(playerid)(rType) = 0
					RefuelData(playerid)(rLiters) = 0
					RefuelData(playerid)(rPrice) = 0.00
					RefuelData(playerid)(rPricePerL) = 0.00
					RefuelData(playerid)(rVeh) = 0
				)
				else // ma kaske, nie buguje, dobry gracz
				(
					hrp_GivePlayerMoney(playerid, -price)
					SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
					CarInfo(vehid)(cFuel) = floatadd(CarInfo(vehid)(cFuel), value)
					SaveVehicle(vehid, SAVE_VEH_COUNT)
					PlayerCache(playerid)(pFueling) = false
					RefuelData(playerid)(rType) = 0
					RefuelData(playerid)(rLiters) = 0
					RefuelData(playerid)(rPrice) = 0.00
					RefuelData(playerid)(rPricePerL) = 0.00
					RefuelData(playerid)(rVeh) = 0
					format(string, sizeof(string), Zap³aci³eœ $%d za %d litrów paliwa., price, value)
					SendClientMessage(playerid, COLOR_LIGHTBLUE, string)
					format(string, sizeof(string), * Pojazd %s zosta³ pomyœlnie zatankowany (( %s )), CarInfo(vehid)(cName), PlayerName(playerid))
					ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
					PlayerTextDrawHide(playerid, TextDrawFuelContent(playerid))
					TextDrawHideForPlayer(playerid, Text:TextDrawFuelBack)					
				)
		)
	)
	
	if(newkeys & KEY_SUBMISSION)
	(
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		(
			if(GetPlayerTargetPlayer(playerid) != INVALID_PLAYER_ID && PlayerCache(playerid)(pClicked) == INVALID_VEHICLE_ID)
			(
				PlayerCache(playerid)(pClicked) = GetPlayerTargetPlayer(playerid)
				ShowDashboardPlayer(playerid, DASHBOARD_PLAYER)
			)
		)
	)
	if(newkeys & KEY_NO)
	(
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		(
			if(GetPlayerVehicleID(playerid) != INVALID_VEHICLE_ID && PlayerCache(playerid)(pClicked) == INVALID_PLAYER_ID)
			(
				PlayerCache(playerid)(pClicked) = GetPlayerVehicleID(playerid)
				ShowDashboardPlayer(playerid, DASHBOARD_VEHICLE)
			)
		)
	)
	
	if(newkeys & KEY_CTRL_BACK)	// H, prace w wiêzieniu
	(
		if(PlayerCache(playerid)(pWorkingNow) == WORK_LAUNDRY)
		(
			if(PlayerCache(playerid)(pWorkingPhase) == LAUNDRY_UNLOADED)
			(
				if(PlayerCache(playerid)(pWorkRepeat) )= 10)
				(
					GuiMsg(playerid, Wyczerpa³eœ dzienny limit pracy, odpocznij., 0)
					StopPlayerPrisonWork(playerid)
				)
				else
				(
					for(cell_id = 0 cell_id ( sizeof(PoliceCell) cell_id++)
					(
						if(IsPlayerInRangeOfPoint(playerid, 2.0, PoliceCell(cell_id)(pCellX), PoliceCell(cell_id)(pCellY), PoliceCell(cell_id)(pCellZ)) && GetPlayerVirtualWorld(playerid) == PoliceCell(cell_id)(pCellVW))
						(
							if(PoliceCell(cell_id)(pCellCleaned) == 0)
							(
								PlayerCache(playerid)(pWorkingPhase) = LAUNDRY_LOADED
								SetPlayerLaundryAnimations(playerid)
								PoliceCell(cell_id)(pCellCleaned) = 1
								GuiMsg(playerid, Zebra³eœ brudn¹ odzie¿ z tej celi. Udaj siê teraz ponownie do pralni.\nBêd¹c na miejscu aby wrzuciæ rzeczy do kosza u¿yj klawisza H (klakson)., 0)
							)
							else
							(
								GuiMsg(playerid, Niestety w tej celi nie znalaz³eœ ¿adnej brudnej odzie¿y.\nUdaj siê do kolejnej i u¿yj klawisza H (klakson)., 0)
							)
							break
						)
					)
				)
			)
			else if(PlayerCache(playerid)(pWorkingPhase) == LAUNDRY_LOADED)
			(
				if(IsPlayerInRangeOfPoint(playerid, 3.0, 1782.0901, -1548.1317, 40.8159) && GetPlayerVirtualWorld(playerid) == PrisonWorld)
				(					
					StopPlayerAnimations(playerid)
					PlayerCache(playerid)(pWorkingPhase) = LAUNDRY_UNLOADED
					
					rand = random(20)
					
					if(rand == 5)
					(
						GuiMsg(playerid, Gratulacje! Za Twoj¹ dobr¹ pracê na rzecz placówki naczelnik skróci³ Twój wyrok o godzinê.\nUdaj siê po kolejne ciuchy, b¹dŸ zakoñcz pracê komend¹ /praca., 0)
						PlayerCache(playerid)(pArrestTime) = PlayerCache(playerid)(pArrestTime) - 3600	// godzina
					)
					else
					(
						GuiMsg(playerid, Brawo! Odda³eœ rzeczy do kosza na brudn¹ odzie¿ i otrzyma³eœ dwa dolary za pracê na rzecz placówki.\nUdaj siê po kolejne ciuchy, b¹dŸ zakoñcz pracê komend¹ /praca., 0)
						hrp_GivePlayerMoney(playerid, 2)
					)
					
					PlayerCache(playerid)(pWorkRepeat)++
					SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
				)
				else
				(
					GuiMsg(playerid, Nie znajdujesz siê w pralni., 0)
				)
			)
		)
		if(PlayerCache(playerid)(pWorkingNow) == WORK_WORKSHOP)
		(
			if(PlayerCache(playerid)(pWorkingPhase) == WORKSHOP_WAITING)
			(
				if(IsPlayerInRangeOfPoint(playerid, 3.0, 1764.4370, -1534.9044, 39.9441) && GetPlayerVirtualWorld(playerid) == PrisonWorld)
				(
					if(PlayerCache(playerid)(pWorkRepeat) )= 10)
					(
						GuiMsg(playerid, Wyczerpa³eœ dzienny limit pracy, odpocznij., 0)
						StopPlayerPrisonWork(playerid)
					)
					else
					(
						SetPlayerWorkshopAnimations(playerid)
						PlayerCache(playerid)(pWorkingPhase) = WORKSHOP_SAWING
						PlayerCache(playerid)(pWorkingTimeLeft) = 40
					)
				)
				else
				(
					GuiMsg(playerid, Nie znajdujesz siê w warsztacie., 0)
				)
			)
			else if(PlayerCache(playerid)(pWorkingPhase) == WORKSHOP_SAWING)
			(
				GuiMsg(playerid, Przerwa³eœ pracê, aby zacz¹æ od nowa u¿yj klawisza H., 0)
				PlayerCache(playerid)(pWorkingRepeat) = 0
				PlayerCache(playerid)(pWorkingPhase) = WORKSHOP_WAITING
				StopPlayerAnimations(playerid)
			)
		)
	)	
		
 	// Blokada bicia
 	if(PlayerCache(playerid)(pBlock) & BLOCK_RUN)
 	(
 		if(!GetPlayerWeapon(playerid) && GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_ENTER_VEHICLE && GetPlayerState(playerid) != PLAYER_STATE_DRIVER && GetPlayerState(playerid) != PLAYER_STATE_PASSENGER)
 		(
 			if((newkeys & KEY_FIRE) || (newkeys & 144))
 			(
 				ClearAnimations(playerid, true)
 			)
 		)
 	)
	
	if(newkeys & KEY_FIRE)
	(
		if(PlayerCache(playerid)(pCarryBox) != BOX_NONE)
		(
			cmd_port(playerid, )
		)
		
		if(PlayerCache(playerid)(pFish) && PlayerCache(playerid)(pFishTaking))
		(
			random_value = random(60), string(64)
			switch(random_value)
			(
				case 21:
				(
					GameTextForPlayer(playerid, ~w~Zylka zostala ~r~zerwana, 5000, 3)
					PlayerCache(playerid)(pFishTaking) = false
				)
				case 14:
				(
					if(PlayerCache(playerid)(pWormed))
					(
						fish_id = random(sizeof(FishInfo))
						
						format(string, sizeof(string), ~w~Zlowiles rybe ~p~\%s\, FishInfo(fish_id)(fName))
						GameTextForPlayer(playerid, string, 5000, 3)
						
						PlayerCache(playerid)(pFishTaking) = false
						CreatePlayerItem(playerid, FishInfo(fish_id)(fName), ITEM_FOOD, FishInfo(fish_id)(fValue1), 0)
						
						PlayerCache(playerid)(pWormed) = false
					)
					else
					(
						PlayerCache(playerid)(pFishTaking) = false
						
						format(string, sizeof(string), ~w~Ryba uciekla, zapomniales nabic ~r~robaka ~w~na haczyk)
						GameTextForPlayer(playerid, string, 5000, 3)
					)
				)
			)
			ApplyAnimation(playerid, CAMERA, picstnd_out, 4.1, 0, 0, 0, 1, 0, 1)
		)
		
		if(PlayerCache(playerid)(pWorkingPhase) == WORKSHOP_SAWING)
		(
			// mo¿na dodaæ szansê na jak¹œ nag³¹ przerwê w pracy, stêpienie pi³y
			
			PlayerCache(playerid)(pWorkingRepeat)++
		)
		
		
		// AC - Sprawdzanie czy nie buguj¹ amunicji - liczymy pestki po naciœniêciu LPM. Nie banowaæ przy braku zmian bo mog¹ byæ przy œcianie.

		if((WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID) || WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID) || WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID)) && !PlayerCache(playerid)(pTagging))
		(
			if(!IsPlayerAFK(playerid))
			(
				weapon = GetPlayerWeapon(playerid)
				
				if(GetPlayerVirtualWorld(playerid) == 0)
				(
					if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
					(
						//if(weapon == WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID) || weapon == WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID) || weapon == WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
						//(
							// Informacje o strzelaninach dla PD
							if(weapon != 23 && weapon )= 22 && weapon (= 34)
							(							
								/*Float:shortest_distance = 0, index = 0, Float:x, Float:y, Float:z
								GetPlayerPos(playerid, x, y, z)
								for(i = 0 i ( sizeof(GunRegionInfo) i++)
								(
									Float:distance = floatsqroot(floatpower(floatabs(floatsub(x, GunRegionInfo(i)(grPosX))), 2)+floatpower(floatabs(floatsub(y, GunRegionInfo(i)(grPosY))),2)+floatpower(floatabs(floatsub(z, GunRegionInfo(i)(grPosZ))),2))
									if(distance ( shortest_distance || shortest_distance == 0)
									(
										shortest_distance = distance
										index = i
									)
								)
								ShootsFired(index)++*/
								Float:shortest_distance = 0.0, Float:x, Float:y, Float:z, currentIndex = 0
								GetPlayerPos(playerid, x, y, z)
								for(i = 0 i ( sizeof(GunRegionInfo) i++)
								(
									Float:distance = GetPlayerDistanceFromPoint(playerid, GunRegionInfo(i)(grPosX), GunRegionInfo(i)(grPosY), GunRegionInfo(i)(grPosZ))
									if(distance ( shortest_distance || shortest_distance == 0.0)
									(
										shortest_distance = distance
										currentIndex = i
									)
								)
								
								ShootsFired(currentIndex)++
							)
						//)
					)
				)
			)
		)
	)
	if((newkeys == KEY_WALK + KEY_SPRINT) || newkeys == (KEY_SUBMISSION + KEY_HANDBRAKE))
	(
		Float:pvX = 0.0, Float:pvY = 0.0, Float:pvZ = 0.0, vehid = GetPlayerVehicleID(playerid)
		if(vehid != INVALID_VEHICLE_ID)
		(
			GetVehicleVelocity(vehid, pvX, pvY, pvZ)
		)

		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT || (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && floatabs(pvX) ( 0.1 && floatabs(pvY) ( 0.1))
		(
			if(PlayerCache(playerid)(pDoorFreeze))
			(
				return 1
			)
			foreach(Doors, doorid)
			(
	 	   		if(DoorData(doorid)(dUID))
		  	  	(
	  		 		if(IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)) && GetPlayerVirtualWorld(playerid) == DoorData(doorid)(dEnterVW))
					(
						OnPlayerEnterDoor(playerid, doorid)
						if(PlayerCache(playerid)(pMoveObject) != INVALID_OBJECT_ID)
						(
							CancelEdit(playerid)
						)
	  					break
	  			  	)
		 		   	else if(IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ)) && GetPlayerVirtualWorld(playerid) == DoorData(doorid)(dExitVW))
		   		 	(
						OnPlayerExitDoor(playerid, doorid)
						if(PlayerCache(playerid)(pMoveObject) != INVALID_OBJECT_ID)
						(
							CancelEdit(playerid)
						)
	  					break
		 		   	)
				)
			)
		)
	)
	if(newkeys & KEY_SPRINT)
	(
		if(PlayerCache(playerid)(pSlots))
		(
			slotid = PlayerCache(playerid)(pSlotID)
			if(PlayerCache(playerid)(pSlotTicks) (= 0)
			(
				if(PlayerCache(playerid)(pCash) ) 10)
				(
					hrp_GivePlayerMoney(playerid, -10)
					SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
					ApplyAnimation(playerid, DEALER, shop_pay, 4.1, 0, 0, 0, 0, 0, 1)
					PlayerCache(playerid)(pSlotTicks)  = 4
					//SetTimerEx(slots_RollMachine, 100, 0, d, playerid)
					SlotMachine(slotid)(mMoney) += 10
					slots_RandIcons(playerid)
				)
				else
				(
					//nie stac go
					GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~r~za malo pieniedzy, 5000, 3)
				)
			)
		)
		if(PlayerCache(playerid)(pRoll))
		(
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
			(
				if(GetPlayerSpeed(playerid, true) ) 5)
				(
					ApplyAnimation(playerid, SKATE, skate_run, 3.0, 1, 1, 1, 1, 1, 1)
					PlayerCache(playerid)(pPlayAnim) = true
					return 1
				)
			)
		)
	)
	if(newkeys == KEY_JUMP)
	(
		if(PlayerCache(playerid)(pClothChanging))
		(
			hrp_TogglePlayerControllable(playerid, true)
			PlayerCache(playerid)(pClothChanging) = false

			GameTextForPlayer(playerid, _, 0, 6)
			TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			
			SetCameraBehindPlayer(playerid)
			SetPlayerSkin(playerid, PlayerCache(playerid)(pSkin))
			return 1
		)
		if(PlayerCache(playerid)(pAccessChanging))
		(
			SetCameraBehindPlayer(playerid)
			RemovePlayerAttachedObject(playerid, SLOT_TRYING)
		
			hrp_TogglePlayerControllable(playerid, true)
			PlayerCache(playerid)(pAccessChanging) = false

			GameTextForPlayer(playerid, _, 0, 6)
			TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			return 1
		)
		/*
		if(PlayerCache(playerid)(pAccessEditing))
		(
			SetCameraBehindPlayer(playerid)
			RemovePlayerAttachedObject(playerid, SLOT_TRYING)
		
			PlayerCache(playerid)(pAccessEditing) = false
			hrp_TogglePlayerControllable(playerid, true)
			
			TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			return 1
		)
		*/
	)
	if(newkeys == KEY_SECONDARY_ATTACK)
	(
		if(PlayerCache(playerid)(pClothChanging))
		(
			skin_id = PlayerCache(playerid)(pClothID)
			if(PlayerCache(playerid)(pCash) ( SkinInfo(skin_id)(sPrice))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie staæ Ciê na zakup tego ubrania., OK, )
				return 1
			)
			hrp_GivePlayerMoney(playerid, -SkinInfo(skin_id)(sPrice))
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			CreatePlayerItem(playerid, SkinInfo(skin_id)(sName), ITEM_CLOTH, SkinInfo(skin_id)(sModel), 0)

			SetCameraBehindPlayer(playerid)
			SetPlayerSkin(playerid, PlayerCache(playerid)(pSkin))
			
			hrp_TogglePlayerControllable(playerid, true)
			PlayerCache(playerid)(pClothChanging) = false
			
			GameTextForPlayer(playerid, _, 0, 6)
			TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			
			doorid = GetPlayerDoorID(playerid), group_id_fix = GetGroupID(DoorData(doorid)(dOwner))

			GroupData(group_id_fix)(gCash) += SkinInfo(skin_id)(sPrice)
			SaveGroup(group_id_fix)
			
			SendClientMessage(playerid, COLOR_INFO, Wybrane ubranie zosta³o zakupione. Kupiony przedmiot znajdziesz w swoim ekwipunku.)
			return 1
		)
		if(PlayerCache(playerid)(pAccessChanging))
		(
			access_id = PlayerCache(playerid)(pAccessID)
			if(AccessInfo(access_id)(aOwnerType))
			(
				if(AccessInfo(access_id)(aOwnerType) == OWNER_GROUP)
				(
					if(!IsPlayerInGroupType(playerid, AccessInfo(access_id)(aOwner)))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do kupna tego akcesoria., OK, )
						return 1
					)
				)
			)
			
			if(PlayerCache(playerid)(pCash) ( AccessInfo(access_id)(aPrice))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie staæ Ciê na zakup tego akcesoria., OK, )
				return 1
			)
			hrp_GivePlayerMoney(playerid, -AccessInfo(access_id)(aPrice))
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			SetCameraBehindPlayer(playerid)
			RemovePlayerAttachedObject(playerid, SLOT_TRYING)

			hrp_TogglePlayerControllable(playerid, true)
			PlayerCache(playerid)(pAccessChanging) = false

			GameTextForPlayer(playerid, _, 0, 6)
			TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))

			doorid = GetPlayerDoorID(playerid), group_id_fix = GetGroupID(DoorData(doorid)(dOwner))

			GroupData(group_id_fix)(gCash) += AccessInfo(access_id)(aPrice)
			SaveGroup(group_id_fix)
			
			mysql_query_format(INSERT INTO hrp_access VALUES (, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f), PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
			access_uid = mysql_insert_id()
			
			CreatePlayerItem(playerid, AccessInfo(access_id)(aName), ITEM_ATTACH, access_uid, 0)
			SendClientMessage(playerid, COLOR_INFO, Wybrane akcesorie zosta³o zakupione. Kupiony przedmiot znajdziesz w swoim ekwipunku.)
			return 1
		)
		if(PlayerCache(playerid)(pAccessEditing))
		(
	 		SetCameraBehindPlayer(playerid)
			RemovePlayerAttachedObject(playerid, SLOT_TRYING)

			PlayerCache(playerid)(pAccessEditing) = false
			hrp_TogglePlayerControllable(playerid, true)
			
			TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			mysql_query_format(UPDATE hrp_access SET access_posx = %f, access_posy = %f, access_posz = %f, access_rotx = %f, access_roty = %f, access_rotz = %f, access_scalex = %f, access_scaley = %f, access_scalez = %f WHERE access_uid = %d LIMIT 1,

			PlayerAttach(playerid)(aPosX),
			PlayerAttach(playerid)(aPosY),
			PlayerAttach(playerid)(aPosZ),

			PlayerAttach(playerid)(aRotX),
			PlayerAttach(playerid)(aRotY),
			PlayerAttach(playerid)(aRotZ),

			PlayerAttach(playerid)(aScaleX),
			PlayerAttach(playerid)(aScaleY),
			PlayerAttach(playerid)(aScaleZ),

			PlayerAttach(playerid)(aUID))

			SendClientMessage(playerid, COLOR_INFO, Akcesorie zosta³o zedytowane pomyœlnie. Aby za³o¿yæ, u¿yj go ponownie.)
			return 1
		)
	)
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	(
		vehid = GetPlayerVehicleID(playerid)
		if(newkeys == KEY_HANDBRAKE + KEY_FIRE)
		(
			if(!CarInfo(vehid)(cEngineTogged))
			(
			 	cmd_silnik(playerid, )
				return 1
			)
		)
		// Zapalanie œwiate³ & odczepianie pojazdu
		if(newkeys & 1)
		(
  			if(GetVehicleLightsStatus(vehid) == 1)
	 		(
				ChangeVehicleLightsStatus(vehid, false)
	   		)
			else
			(
				ChangeVehicleLightsStatus(vehid, true)
			)
			
			if(IsPlayerInAnyVehicle(playerid))
			(
				if(PlayerCache(playerid)(pGroupDuty))
				(
					group_id_fix = GetPlayerDutyGroupID(playerid)
					if(GroupData(group_id_fix)(gType) == GROUP_POLICE || GroupData(group_id_fix)(gType) == GROUP_FIREDEPT || GroupData(group_id_fix)(gType) == GROUP_MEDICAL || GroupData(group_id_fix)(gType) == GROUP_FBI)
					(
						if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == GroupData(group_id_fix)(gUID))
						(
							if(CarInfo(vehid)(cStrobe))
							(
								CarInfo(vehid)(cStrobe) = false
							)
							else
							(
								CarInfo(vehid)(cStrobe) = true
							)
						)
					)
				)
				
			)

			if(CarInfo(vehid)(cTowedVeh) != INVALID_VEHICLE_ID)
			(
				if(GetVehicleTrailer(vehid))
				(
					DetachTrailerFromVehicle(vehid)
					CarInfo(vehid)(cTowedVeh) = INVALID_VEHICLE_ID

					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pojazd zosta³ odczepiony pomyœlnie., OK, )
				)
			)
		)
		
		if(PlayerCache(playerid)(pRacePhase) == 1)
		(
			if(newkeys & 4)
			(
  				if(PlayerCache(playerid)(pRacePoint) ( MAX_RACE_CP - 1)
				(
					checkpoint = PlayerCache(playerid)(pRacePoint), string(256)
					GetVehiclePos(vehid, RaceCheckpoint(checkpoint)(0), RaceCheckpoint(checkpoint)(1), RaceCheckpoint(checkpoint)(2))

					GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~w~Checkpoint ~g~dodany, 3000, 3)
					PlayerCache(playerid)(pRacePoint) ++
					
  					format(string, sizeof(string), Rozpoczales ~r~proces ~w~tworzenia wyscigu, zwroc uwage na ~g~legende~w~:~n~~n~~y~~k~~VEHICLE_FIREWEAPON~ ~w~- stawia checkpoint~n~~y~~k~~VEHICLE_FIREWEAPON_ALT~ ~w~- ustala linie mety~n~~n~Checkpointy: ~y~%d/%d, PlayerCache(playerid)(pRacePoint), MAX_RACE_CP)

					TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
	 				TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
				)
				else
				(
					GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Limit checkpointow przekroczony! Ustal linie mety!, 3000, 3)
				)
			)
			
			if(newkeys & 1)
			(
 				if(PlayerCache(playerid)(pRacePoint) (= 2)
				(
					GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Musza byc conajmniej 3 checkpointy!, 3000, 3)
					return 1
				)
				checkpoint = PlayerCache(playerid)(pRacePoint)
				GetVehiclePos(vehid, RaceCheckpoint(checkpoint)(0), RaceCheckpoint(checkpoint)(1), RaceCheckpoint(checkpoint)(2))
				
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~w~Linia mety ~y~ustawiona, 3000, 3)
				PlayerCache(playerid)(pRacePhase) = 2
				
				PlayerCache(playerid)(pRaceCheckpoints) = PlayerCache(playerid)(pRacePoint)
				
				TextDrawSetString(Text:TextDrawMainInfo(playerid), Postawiles ~y~linie mety~w~. Teraz mozesz zaprosic rywali do wyscigu komenda ~r~/wyscig zapros~w~.~n~~n~~y~/wyscig start ~w~rozpoczyna wyscig.)
				TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
				
				PlayerCache(playerid)(pShowInfoText) = 10
			)
		)
	)
	// Blokowanie skakania na rowerku
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	(
		vehid = GetPlayerVehicleID(playerid), model = GetVehicleModel(vehid)
		if(model == 509 || model == 510 || model == 481)
  		(
  			if(!IsPlayerInRangeOfPoint(playerid, 80.0, 1907.7548, -1402.8784, 13.1844) && !IsPlayerInGroupType(playerid, GROUP_SKATE))
  			(
				if(newkeys & 1)
				(
					ClearAnimations(playerid)
					
					TextDrawSetString(Text:TextDrawMainInfo(playerid), ~r~Skakanie ~w~na rowerze poza skate parkiem nie jest ~y~dozwolone~w~.)
					TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
					
					PlayerCache(playerid)(pShowInfoText) = 5
				)
			)
		)
	)
	if(newkeys & 128) // PPM
	(
		if(PlayerCache(playerid)(pPlayAnim))
		(
			PlayerCache(playerid)(pPlayAnim) = false
			ApplyAnimation(playerid, CARRY, crry_prtial, 4.1, 0, 0, 0, 0, 0)
		)
	)
	
	if(PlayerCache(playerid)(pWalkAnim))
	(
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		(
			if(newkeys & KEY_WALK)
			(
				anim_id = GetAnimationID(PlayerCache(playerid)(pWalkAnim))
				ApplyAnimation(playerid, AnimInfo(anim_id)(aLib), AnimInfo(anim_id)(aName), AnimInfo(anim_id)(aSpeed), AnimInfo(anim_id)(aOpt1), AnimInfo(anim_id)(aOpt2), AnimInfo(anim_id)(aOpt3), AnimInfo(anim_id)(aOpt4), AnimInfo(anim_id)(aOpt5), 1)

				PlayerCache(playerid)(pPlayAnim) = true
			)
			else if(oldkeys & KEY_WALK)
			(
				ApplyAnimation(playerid, CARRY, crry_prtial, 4.1, 0, 0, 0, 0, 0)
			)
		)
	)
	if(newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP) && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED)	ApplyAnimation(playerid, GYMNASIUM, gym_jog_falloff,4.1, 0, 1, 1, 0, 0, 1)
	
	if(newkeys & KEY_YES)
	(
		if(PlayerCache(playerid)(pAdminMode) != -1)
		(
			if(PlayerCache(playerid)(pAdminMode) + 1 ( sizeof(Penalties))
			(
				PlayerCache(playerid)(pAdminMode) ++
				TextDrawSetString(TextDrawAdminMode(playerid), Penalties(PlayerCache(playerid)(pAdminMode)))
			) else (
				PlayerCache(playerid)(pAdminMode) = 0
			)
		) else (
			cmd_lspd(playerid, )
		)
	)
	if(newkeys & KEY_NO)
	(
		if(PlayerCache(playerid)(pAdminMode) != -1)
		(
			if(PlayerCache(playerid)(pAdminMode) - 1 (= 0)
			(
				PlayerCache(playerid)(pAdminMode) --
				TextDrawSetString(TextDrawAdminMode(playerid), Penalties(PlayerCache(playerid)(pAdminMode)))
			) else (
				PlayerCache(playerid)(pAdminMode) = sizeof(Penalties) - 1
			)
		)
		else
		(
			if(PlayerCache(playerid)(pCarryBox) != BOX_NONE)
			(
				StopPlayerCarryPort(playerid)
			)
		)
	)
	
	if(newkeys & KEY_SUBMISSION)
	(	
		if(IsPlayerInAnyVehicle(playerid))
		(
			if(PlayerCache(playerid)(pGroupDuty))
			(
				Float:PosX, Float:PosY, Float:PosZ, string(128), group_id_fix = GetPlayerDutyGroupID(playerid)
				GetPlayerPos(playerid, PosX, PosY, PosZ)
				if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
				(
					vehid = GetPlayerVehicleID(playerid)
					if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == GroupData(group_id_fix)(gUID))
					(
						foreach(Player, i)
						(
							if(IsPlayerInRangeOfPoint(i, 60.0, PosX, PosY, PosZ))
							(
								//audio = Audio_Play(i, AUDIO_SIREN)
								//Audio_Set3DPosition(i, audio, PosX, PosY, PosZ, 60.0)
								PlayAudioStreamForPlayer(i, http://pliki.ls-rp.net/sounds/police.mp3)
								format(string, sizeof(string), %s (megafon): Tu Los Santos Police Department. ZjedŸ na pobocze i zgaœ silnik. Pozostañ w pojeŸdzie., PlayerName(playerid))
							)
						)
						ProxDetector(40.0, playerid, string, GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), true)
					)
				)
				else if(GroupData(group_id_fix)(gType) == GROUP_MEDICAL)
				(
					vehid = GetPlayerVehicleID(playerid)
					if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == GroupData(group_id_fix)(gUID))
					(
						foreach(Player, i)
						(
							if(IsPlayerInRangeOfPoint(i, 60.0, PosX, PosY, PosZ))
							(
								//audio = Audio_Play(i, AUDIO_FDSIREN)
								//Audio_Set3DPosition(i, audio, PosX, PosY, PosZ, 60.0)
								format(string, sizeof(string), %s (megafon): Tu Los Santos Emergency Medical Services. Ust¹p piewrszeñstwa pojazdowi uprzywilejowanemu., PlayerName(playerid))
							)
						)
						ProxDetector(40.0, playerid, string, GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), true)
					)
				)
				else if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
				(
					vehid = GetPlayerVehicleID(playerid)
					if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == GroupData(group_id_fix)(gUID))
					(
						foreach(Player, i)
						(
							if(IsPlayerInRangeOfPoint(i, 60.0, PosX, PosY, PosZ))
							(
								//audio = Audio_Play(i, AUDIO_FDSIREN)
								//Audio_Set3DPosition(i, audio, PosX, PosY, PosZ, 60.0)
								PlayAudioStreamForPlayer(i, http://pliki.ls-rp.net/sounds/firehorn.mp3)
								format(string, sizeof(string), %s (megafon): Tu Los Santos Fire Department. Ust¹p pierwszeñstwa pojazdowi uprzywilejowanemu., PlayerName(playerid))
							)
						)
						ProxDetector(40.0, playerid, string, GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), GroupData(group_id_fix)(gColor), true)
					)
				)
			)
		)
		else
		(
			if(PlayerCache(playerid)(pTrainTime))
			(
				if(PlayerCache(playerid)(pGymType) == TRAIN_NONE)
				(
					object_id = GetClosestObject(playerid)
					if(object_id != INVALID_OBJECT_ID)
					(
						if(GetObjectModel(object_id) == OBJECT_BENCH)
						(
							cmd_trenuj(playerid, laweczka)
						)
						else if(GetObjectModel(object_id) == OBJECT_BENCH)
						(
							cmd_trenuj(playerid, hantle)
						)
						else if(GetObjectModel(object_id) == OBJECT_PUNCH_BAG)
						(
							cmd_trenuj(playerid, worek)
						)
						else if(GetObjectModel(object_id) == OBJECT_TRACK)
						(
							cmd_trenuj(playerid, bieznia)
						)
					)
				)
				else
				(
					OnPlayerGymTrainStopped(playerid)
				)
			)
		)
	)
		
	return 1
)

public OnPlayerUpdate(playerid)
(	
	inHand = GetPlayerWeapon(playerid)

	// Broñ g³ówna
	if(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
	(
		if(inHand != WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID))
		(
			type = WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID),
				itemid = GetItemID(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
			
			if(!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_MAIN))
			(
				if(!strfind(ItemInfo(itemid)(iName), (F), true))
				(
					SetPlayerAttachedObject(playerid, SLOT_WEAPON_MAIN, WeaponModel(type), 16, 0.16, -0.15, 0.21, 83.0, 330.0, 70.0) 
				)
				else if(!strfind(ItemInfo(itemid)(iName), (W), true))
				(
					SetPlayerAttachedObject(playerid, SLOT_WEAPON_MAIN, WeaponModel(type), 16, 0.16, -0.15, 0.21, 83.0, 330.0, 70.0) 
				)
				else
				(
					SetPlayerAttachedObject(playerid, SLOT_WEAPON_MAIN, WeaponModel(type), 1, 0.2, -0.125, -0.1, 0.0, 25.0, 180.0)
				)
			)
		)
		else
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_MAIN))
			(
				RemovePlayerAttachedObject(playerid, SLOT_WEAPON_MAIN)
			)
		)
	)
	
	// Broñ poboczna
	if(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
	(
		if(inHand != WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID))
		(
			type = WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID),
				itemid = GetItemID(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
			
			if(!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_SIDE))
			(
				if(!strfind(ItemInfo(itemid)(iName), (D), true))
				(
					RemovePlayerAttachedObject(playerid, SLOT_WEAPON_SIDE)	// usuwamy broñ przyczepialn¹, bo flaga (D) = broñ schowana, czyli dla detektywów
				)
				else
				(
					if(!strfind(ItemInfo(itemid)(iName), (F), true))
					(
						SetPlayerAttachedObject(playerid, SLOT_WEAPON_SIDE, WeaponModel(type), 8, 0.0, -0.1, 0.15, -100.0, 0.0, 0.0)
					)
					else
					(
						SetPlayerAttachedObject(playerid, SLOT_WEAPON_SIDE, WeaponModel(type), 1, -0.19, -0.1, -0.09, 180.0, 180.0, 0.0)
					)
				)
			)
		)
		else
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_SIDE))
			(
				RemovePlayerAttachedObject(playerid, SLOT_WEAPON_SIDE)
			)
		)
	)
	
	// Broñ funkcjonalna
	if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
	(
		if(inHand != WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID))
		(
			type = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID)
			
			if(!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_FUNC))
			(
				SetPlayerAttachedObject(playerid, SLOT_WEAPON_FUNC, WeaponModel(type), 7, 0.0, 0.0, -0.18, 100.0, 45.0, 0.0)
			)
		)
		else
		(
			if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_FUNC))
			(
				RemovePlayerAttachedObject(playerid, SLOT_WEAPON_FUNC)
			)
		)
	)	
	
	if(PlayerCache(playerid)(pSlots))
	(
		keysa, uda, lra
		GetPlayerKeys(playerid, keysa, uda, lra)
		
		if(keysa & KEY_WALK)
		(
			slots_EndGame(playerid,PlayerCache(playerid)(pSlotID))
		)
	)
	
	if(PlayerCache(playerid)(pCurrentGUI) != GUI_TYPE_NONE)
	(
		keysa, uda, lra
		GetPlayerKeys(playerid, keysa, uda, lra)
		
		if(keysa & KEY_WALK)
		(
			switch(PlayerCache(playerid)(pCurrentGUI))
			(
				case GUI_TYPE_DOCUMENT_DRIVING:
				(
					doc_gInterfaceHide(playerid)
				)
			)
		)
	)

	// Pakernia
	if(PlayerCache(playerid)(pGymType) != TRAIN_NONE)
	(
		keysa, uda, lra
		GetPlayerKeys(playerid, keysa, uda, lra)

		// Wyciskanie na ³awce
		if(PlayerCache(playerid)(pGymType) == TRAIN_BENCH_PRESS)
		(
			if(uda ( 0)
			(
				if(PlayerCache(playerid)(pGymPhase) == 1)
				(
					PlayerCache(playerid)(pGymPhase) = 3

					ApplyAnimation(playerid, BENCHPRESS, gym_bp_up_A, 4.0, 0, 0, 0, 1, 0, 1)
					SetTimerEx(OnPlayerTrainRep, 2500, 0, d, playerid)
				)
			)
			else if(uda ) 0)
			(
				if(PlayerCache(playerid)(pGymPhase) == 2)
				(
					PlayerCache(playerid)(pGymPhase) = 4

					ApplyAnimation(playerid, BENCHPRESS, gym_bp_down, 4.0, 0, 0, 0, 1, 0, 1)
					SetTimerEx(OnPlayerTrainRep, 1000, 0, d, playerid)
				)
			)
			else if(keysa & KEY_SECONDARY_ATTACK)
			(
				PlayerCache(playerid)(pGymPhase) = 0

				ApplyAnimation(playerid, BENCHPRESS, gym_bp_getoff, 4.0, 0, 0, 0, 0, 0, 1)

				SetTimerEx(OnPlayerGymTrainStopped, 3000, 0, d, playerid)
			)
		)
		// Wyciskanie na dwóch ciê¿arkach
		if(PlayerCache(playerid)(pGymType) == TRAIN_BARBELL)
		(
			if(keysa & KEY_SPRINT)
			(
				if(PlayerCache(playerid)(pGymPhase) == 1)
				(
					PlayerCache(playerid)(pGymPhase) = 2

					ApplyAnimation(playerid, FREEWEIGHTS, gym_free_A, 4.0, 0, 0, 0, 1, 0, 1)
					SetTimerEx(OnPlayerTrainRep, 2000, 0, d, playerid)
				)
			)
			if(keysa & KEY_SECONDARY_ATTACK)
			(
				PlayerCache(playerid)(pGymPhase) = 0

				ApplyAnimation(playerid, FREEWEIGHTS, gym_free_putdown, 4.0, 0, 0, 0, 0, 0, 1)
				SetTimerEx(OnPlayerGymTrainStopped, 1000, 0, d, playerid)
			)
		)
	)
	// Pozycja 3D Tekstu
	if(PlayerCache(playerid)(pMove3DText) != INVALID_3DTEXT_ID)
	(
		keysa, uda, lra, label_id = PlayerCache(playerid)(pMove3DText),
			Float:PosX, Float:PosY, Float:PosZ,
			Float:Multiplier = 0.5, string(256)
			
		GetPlayerKeys(playerid, keysa, uda, lra)
		
		Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_X, PosX)
		Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Y, PosY)
		Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Z, PosZ)
		
		if((keysa & KEY_WALK))
		(
			Multiplier = 0.1
		)
		else if((keysa & KEY_SPRINT))
		(
			Multiplier = 1.0
		)

		if(!(keysa & KEY_JUMP))
		(
			if(uda ( 0)
			(
				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Y, PosY - Multiplier)
			)
			else if(uda ) 0)
			(
				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Y, PosY + Multiplier)
			)
			else if(lra ( 0)
			(
				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_X, PosX + Multiplier)
			)
			else if(lra ) 0)
			(
				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_X, PosX - Multiplier)
			)
		)

		if((keysa & KEY_JUMP))
		(
			if(uda ( 0)
			(
				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Z, PosZ + Multiplier)
			)
			else if(uda ) 0)
			(
				Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Z, PosZ - Multiplier)
			)
		)
		Streamer_Update(playerid)
		
		SetPlayerCameraPos(playerid, PosX + 3, PosY + 4, PosZ + 4)
		SetPlayerCameraLookAt(playerid, PosX, PosY, PosZ)
		
		format(string, sizeof(string), ~b~Identyfikator: ~w~%d~n~~n~~n~~r~PosX: ~w~%.4f ~r~PosY: ~w~%.4f ~r~PosZ: ~w~%.4f, GetLabelUID(label_id), PosX, PosY, PosZ)
		TextDrawSetString(Text:TextDrawEditorTitle(playerid), string)
	)
 	
	// Wybiera³ka skinów w ciucholandzie
	if(PlayerCache(playerid)(pClothChanging))
	(		
		keysa, uda, lra, string(64)
		GetPlayerKeys(playerid, keysa, uda, lra)

		if(lra ( 0) // Strza³ka w prawo
		(
			PlayerCache(playerid)(pClothID) ++

			skin_id = PlayerCache(playerid)(pClothID)
			if(PlayerCache(playerid)(pClothID) )= sizeof(SkinInfo))
			(
				skin_id = 0

				PlayerCache(playerid)(pClothID) = 0
				SetPlayerSkin(playerid, SkinInfo(skin_id)(sModel))
			)
			else
			(
				SetPlayerSkin(playerid, SkinInfo(skin_id)(sModel))
			)

			format(string, sizeof(string), $~g~%d, SkinInfo(skin_id)(sPrice))
			GameTextForPlayer(playerid, string, 10000, 6)
		)
		else if(lra ) 0) // Strza³ka w lewo
		(
			PlayerCache(playerid)(pClothID) --

			skin_id = PlayerCache(playerid)(pClothID)
			if(PlayerCache(playerid)(pClothID) (= 0)
			(
				skin_id = sizeof(SkinInfo)

				PlayerCache(playerid)(pClothID) = sizeof(SkinInfo)
				SetPlayerSkin(playerid, SkinInfo(skin_id)(sModel))
			)
			else
			(
				SetPlayerSkin(playerid, SkinInfo(skin_id)(sModel))
			)

			format(string, sizeof(string), $~g~%d, SkinInfo(skin_id)(sPrice))
			GameTextForPlayer(playerid, string, 10000, 6)
		)
	)
	// Wybiera³ka akcesorii
	if(PlayerCache(playerid)(pAccessChanging))
	(
		keysa, uda, lra, string(12), counter = 0
		GetPlayerKeys(playerid, keysa, uda, lra)
		
		if(!(keysa & KEY_WALK) && !(keysa & KEY_SPRINT) && lra ( 0) // Strza³ka w prawo
		(
			
			PlayerCache(playerid)(pAccessID) ++
			if(PlayerCache(playerid)(pAccessID) )= sizeof(AccessInfo))
			(
				PlayerCache(playerid)(pAccessID) = 0
			)
			while(AccessInfo(PlayerCache(playerid)(pAccessID))(aType) != PlayerCache(playerid)(pAccessShop))
			(
				PlayerCache(playerid)(pAccessID) ++
				if(PlayerCache(playerid)(pAccessID) )= sizeof(AccessInfo))
				(
					PlayerCache(playerid)(pAccessID) = 0
				)
				counter++
				if(counter ) 500)
				(
					counter = 0
					break
				)
			)

			access_id = PlayerCache(playerid)(pAccessID)
  			if(PlayerCache(playerid)(pAccessID) )= sizeof(AccessInfo))
			(
				access_id = 0

	 			PlayerCache(playerid)(pAccessID) = 0
 				SetPlayerAttachedObject(playerid, SLOT_TRYING, AccessInfo(access_id)(aModel), AccessInfo(access_id)(aBone), AccessInfo(access_id)(aPosX), AccessInfo(access_id)(aPosY), AccessInfo(access_id)(aPosZ), AccessInfo(access_id)(aRotX), AccessInfo(access_id)(aRotY), AccessInfo(access_id)(aRotZ))
			)
			else
			(
 				SetPlayerAttachedObject(playerid, SLOT_TRYING, AccessInfo(access_id)(aModel), AccessInfo(access_id)(aBone), AccessInfo(access_id)(aPosX), AccessInfo(access_id)(aPosY), AccessInfo(access_id)(aPosZ), AccessInfo(access_id)(aRotX), AccessInfo(access_id)(aRotY), AccessInfo(access_id)(aRotZ))
			)

			format(string, sizeof(string), $~g~%d, AccessInfo(access_id)(aPrice))
			GameTextForPlayer(playerid, string, 10000, 6)

			// Tablice dla gracza
			PlayerAttach(playerid)(aModel) = AccessInfo(access_id)(aModel)
			PlayerAttach(playerid)(aBone) = AccessInfo(access_id)(aBone)

			PlayerAttach(playerid)(aPosX) = AccessInfo(access_id)(aPosX)
			PlayerAttach(playerid)(aPosY) = AccessInfo(access_id)(aPosY)
			PlayerAttach(playerid)(aPosZ) = AccessInfo(access_id)(aPosZ)

			PlayerAttach(playerid)(aRotX) = AccessInfo(access_id)(aRotX)
			PlayerAttach(playerid)(aRotY) = AccessInfo(access_id)(aRotY)
			PlayerAttach(playerid)(aRotZ) = AccessInfo(access_id)(aRotZ)

			PlayerAttach(playerid)(aScaleX) = 1.0
			PlayerAttach(playerid)(aScaleY) = 1.0
			PlayerAttach(playerid)(aScaleZ) = 1.0
		)
		else if(!(keysa & KEY_WALK) && !(keysa & KEY_SPRINT) && lra ) 0) // Strza³ka w lewo
		(
		
			PlayerCache(playerid)(pAccessID) --
			if(PlayerCache(playerid)(pAccessID) (= 0)
			(
				PlayerCache(playerid)(pAccessID) = sizeof(AccessInfo)
			)
			while(AccessInfo(PlayerCache(playerid)(pAccessID))(aType) != PlayerCache(playerid)(pAccessShop))
			(
				if(PlayerCache(playerid)(pAccessID) (= 0)
				(
					PlayerCache(playerid)(pAccessID) = sizeof(AccessInfo)
				)
				PlayerCache(playerid)(pAccessID) ++
				counter++
				if(counter ) 500)
				(
					counter = 0
					return 1
				)
			)
		
			access_id = PlayerCache(playerid)(pAccessID)
			if(PlayerCache(playerid)(pAccessID) (= 0)
			(
				access_id = sizeof(AccessInfo)

				PlayerCache(playerid)(pAccessID) = sizeof(AccessInfo)
				SetPlayerAttachedObject(playerid, SLOT_TRYING, AccessInfo(access_id)(aModel), AccessInfo(access_id)(aBone), AccessInfo(access_id)(aPosX), AccessInfo(access_id)(aPosY), AccessInfo(access_id)(aPosZ), AccessInfo(access_id)(aRotX), AccessInfo(access_id)(aRotY), AccessInfo(access_id)(aRotZ))
			)
			else
			(
 				SetPlayerAttachedObject(playerid, SLOT_TRYING, AccessInfo(access_id)(aModel), AccessInfo(access_id)(aBone), AccessInfo(access_id)(aPosX), AccessInfo(access_id)(aPosY), AccessInfo(access_id)(aPosZ), AccessInfo(access_id)(aRotX), AccessInfo(access_id)(aRotY), AccessInfo(access_id)(aRotZ))
			)

			format(string, sizeof(string), $~g~%d, AccessInfo(access_id)(aPrice))
			GameTextForPlayer(playerid, string, 10000, 6)

			// Tablice dla gracza
			PlayerAttach(playerid)(aModel) = AccessInfo(access_id)(aModel)
			PlayerAttach(playerid)(aBone) = AccessInfo(access_id)(aBone)

			PlayerAttach(playerid)(aPosX) = AccessInfo(access_id)(aPosX)
			PlayerAttach(playerid)(aPosY) = AccessInfo(access_id)(aPosY)
			PlayerAttach(playerid)(aPosZ) = AccessInfo(access_id)(aPosZ)

			PlayerAttach(playerid)(aRotX) = AccessInfo(access_id)(aRotX)
			PlayerAttach(playerid)(aRotY) = AccessInfo(access_id)(aRotY)
			PlayerAttach(playerid)(aRotZ) = AccessInfo(access_id)(aRotZ)

			PlayerAttach(playerid)(aScaleX) = 1.0
			PlayerAttach(playerid)(aScaleY) = 1.0
			PlayerAttach(playerid)(aScaleZ) = 1.0
		)
 	)
	// Pozycjonowanie & skalowanie
	if(PlayerCache(playerid)(pAccessChanging))// || PlayerCache(playerid)(pAccessEditing))
	(
		keysa, uda, lra
		GetPlayerKeys(playerid, keysa, uda, lra)

		if((keysa & KEY_WALK))
		(
			if(lra ( 0)
			(
				if(PlayerAttach(playerid)(aPosY) ( 0.1)
				(
					PlayerAttach(playerid)(aPosY) += 0.01
					SetPlayerAttachedObject(playerid, SLOT_TRYING, PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
				)
			)
			else if(lra ) 0)
			(
				if(PlayerAttach(playerid)(aPosY) ) -0.1)
				(
					PlayerAttach(playerid)(aPosY) -= 0.01
					SetPlayerAttachedObject(playerid, SLOT_TRYING, PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
				)
			)
			else if(uda ( 0)
			(
	  			if(PlayerAttach(playerid)(aPosX) ( 0.2)
	  			(
					PlayerAttach(playerid)(aPosX) += 0.01
					SetPlayerAttachedObject(playerid, SLOT_TRYING, PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
				)
			)
			else if(uda ) 0)
			(
	  			if(PlayerAttach(playerid)(aPosX) ) -0.1)
	  			(
					PlayerAttach(playerid)(aPosX) -= 0.01
					SetPlayerAttachedObject(playerid, SLOT_TRYING, PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
				)
			)
		)

		if((keysa & KEY_SPRINT))
		(
			if(lra ( 0)
			(
				if(PlayerAttach(playerid)(aScaleY) ( 1.5)
				(
					PlayerAttach(playerid)(aScaleY) += 0.1
					SetPlayerAttachedObject(playerid, SLOT_TRYING, PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
				)
			)
			else if(lra ) 0)
			(
				if(PlayerAttach(playerid)(aScaleY) ) 1.0)
				(
					PlayerAttach(playerid)(aScaleY) -= 0.1
					SetPlayerAttachedObject(playerid, SLOT_TRYING, PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
				)
			)
			else if(uda ( 0)
			(
				if(PlayerAttach(playerid)(aScaleX) ( 1.5)
				(
					PlayerAttach(playerid)(aScaleX) += 0.1
					SetPlayerAttachedObject(playerid, SLOT_TRYING, PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
				)
			)
			else if(uda ) 0)
			(
				if(PlayerAttach(playerid)(aScaleX) ) 1.0)
				(
					PlayerAttach(playerid)(aScaleX) -= 0.1
					SetPlayerAttachedObject(playerid, SLOT_TRYING, PlayerAttach(playerid)(aModel), PlayerAttach(playerid)(aBone), PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ), PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ))
				)
			)
		)
	)
	// Zmiana speca dla admina/suppa
	if(PlayerCache(playerid)(pSpectateChange) + 1 ( gettime())
	(
		if(PlayerCache(playerid)(pSpectate) != INVALID_PLAYER_ID)
		(
			if(IsPlayerConnected(PlayerCache(playerid)(pSpectate)))
			(
				keysa, uda, lra, passes = 0, current = PlayerCache(playerid)(pSpectate)
				GetPlayerKeys(playerid, keysa, uda, lra)


				if(lra ) 0) // Strza³ka w lewo
				(

					current--
					if(current (= 0)
					(
						current = MAX_PLAYERS
					)
					while(!IsPlayerConnected(current) || !Logged(current) || !Spawned(current) || current == playerid || GetPlayerState(current) == 	PLAYER_STATE_SPECTATING)
					(
						passes++
						current--
						if(current (= 0)
						(
							current = MAX_PLAYERS
						)
						if(passes ) MAX_PLAYERS)
						(
							current = INVALID_PLAYER_ID
							break
						)
					)
					

					PlayerCache(playerid)(pSpectateChange) = gettime()
					s(4)
					format(s, sizeof(s), %d, current)
					cmd_spec(playerid, s)
				)

				if(lra ( 0) // Strza³ka w prawo
				(
					current++
					if(current )= MAX_PLAYERS)
					(
						current = 0
					)
					while(!IsPlayerConnected(current) || !Logged(current) || !Spawned(current) || current == playerid || GetPlayerState(current) == 	PLAYER_STATE_SPECTATING)
					(
						passes++
						current++
						if(current )= MAX_PLAYERS)
						(
							current = 0
						)
						if(passes ) MAX_PLAYERS)
						(
							current = INVALID_PLAYER_ID
							break
						)
					)

					PlayerCache(playerid)(pSpectateChange) = gettime()
					s(4)
					format(s, sizeof(s), %d, current)
					cmd_spec(playerid, s)
				)
			)
		)
	)
	PlayerCache(playerid)(pAFK) = 5
	return 1
)

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid)
(/*
	if(PlayerCache(damagedid)(pAdminDuty))
	(
		return 0
	)
	if(GlobalGod)
	(
		return 0
	)
	if(!Logged(damagedid) || !Spawned(damagedid))
	(
		return 0
	)
	if(PlayerCache(damagedid)(pBW) ) 0)
	(
		hrp_SetPlayerHealth(damagedid, 20)
		return 0
	)
	if(PlayerCache(playerid)(pRoped) != INVALID_PLAYER_ID)
	(
		return 0
	)
	if(PlayerCache(playerid)(pGamePoints) ( 50)
	(
		if(weaponid != 0 && weaponid != WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID) && weaponid != WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID) && weaponid != WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID))
		(
			weap_name(24), string(64)
			GetWeaponName(weaponid, weap_name, 24)

			ResetPlayerWeapons(playerid)
			
			format(string, sizeof(string), WeaponHack (WeapID: %d, WeapName: %s)., weaponid, weap_name)
			hrp_Kick(playerid, -1, string)
			return 0
		)
	)
	if(PlayerCache(playerid)(pGamePoints) ( 100 && PlayerCache(playerid)(pPremiumTime) ( gettime())
	(
		if(weaponid != 0 && !PlayerCache(playerid)(pTagging))
		(
			weap_name(24), string(64)
			GetWeaponName(weaponid, weap_name, 24)

			ResetPlayerWeapons(playerid)
			
			format(string, sizeof(string), WeaponHack (WeapID: %d, WeapName: %s)., weaponid, weap_name)
			hrp_Ban(playerid, -1, string, 0)
			return 0
		)
	)
	if(PlayerCache(playerid)(pAdminMode) != -1)
	(
		string(64)		
		if(PlayerCache(playerid)(pAdminMode) == 0)
		(
			format(string, sizeof(string), run %d 7 Sprint/bh (7), damagedid)
			cmd_block(playerid, string)
		) else if(PlayerCache(playerid)(pAdminMode) == 1) (
			format(string, sizeof(string), veh %d 7 Niepoprawna jazda pojazdem (7), damagedid)
			cmd_block(playerid, string)
		) else if(PlayerCache(playerid)(pAdminMode) == 2) (
			format(string, sizeof(string), %d 60 Odwalanie, damagedid)
			cmd_aj(playerid, string)
		) else if(PlayerCache(playerid)(pAdminMode) == 3) (
			format(string, sizeof(string), %d 0 Cheat, damagedid)
			cmd_ban(playerid, string)
		) else if(PlayerCache(playerid)(pAdminMode) == 4) (
			format(string, sizeof(string), %d, damagedid)
			cmd_res(playerid, string)
		) else if(PlayerCache(playerid)(pAdminMode) == 5) (
			format(string, sizeof(string), %d, damagedid)
			cmd_spec(playerid, string)
		) else if(PlayerCache(playerid)(pAdminMode) == 6) (
			format(string, sizeof(string), %d, damagedid)
			cmd_goto(playerid, string)
		) else if(PlayerCache(playerid)(pAdminMode) == 7) (
			format(string, sizeof(string), %d, damagedid)
			cmd_gethere(playerid, string)
		) else if(PlayerCache(playerid)(pAdminMode) == 8) (
			format(string, sizeof(string), %d, damagedid)
			cmd_freeze(playerid, string)
		)
		return 0
	)
	if(playerid != INVALID_PLAYER_ID)
	(
		//class = GetWeaponClass(weaponid)
		//Wszystkie bronie bia³e i do strzelania
		if((weaponid )= 0 && weaponid (= 5) || (weaponid ) 15 && weaponid ( 39) || (weaponid )= 10 && weaponid (= 15))
		(
			bool:czy_dostal_wpierdol = false
			
			//Reszta else to bronie bia³e
			if(weaponid == 0)
			(
				Float:health, Float:attack = floatround( PlayerCache(playerid)(pStrength) / 20 )
				if(PlayerCache(playerid)(pStrength) ) 20)
				(
					GetPlayerHealth(damagedid, health)
					hrp_SetPlayerHealth(damagedid, health - (attack + amount))
				)
				
				czy_dostal_wpierdol = true
			)
			else if(weaponid == 1)
			(
				Float:health, drunk_level, Float:attack = floatround(PlayerCache(playerid)(pStrength) / 20) * 2
				if(PlayerCache(playerid)(pStrength) ) 20)
				(
					GetPlayerHealth(damagedid, health)
					hrp_SetPlayerHealth(damagedid, health - (attack + amount))
				)
				
				drunk_level = GetPlayerDrunkLevel(damagedid)
				if(drunk_level ( 6000)
				(
					SetPlayerDrunkLevel(damagedid, drunk_level + 700)
				)
				czy_dostal_wpierdol = true
			)
			else if(weaponid == 3 || weaponid == 5 || weaponid == 10 || weaponid == 11)
			(
				Float:health, drunk_level, Float:attack = floatround(PlayerCache(playerid)(pStrength) / 20) * 3
				if(PlayerCache(playerid)(pStrength) ) 20)
				(
					GetPlayerHealth(damagedid, health)
					hrp_SetPlayerHealth(damagedid, health - (attack + amount))
				)
				
				drunk_level = GetPlayerDrunkLevel(damagedid)
				if(drunk_level ( 6000)
				(
					SetPlayerDrunkLevel(damagedid, drunk_level + 700)
				)
				czy_dostal_wpierdol = true
				
				// Propozycja Gutka
				group_id_fix = GetPlayerDutyGroupID(playerid)
				if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
				(
					ApplyPlayerWound(damagedid, 6, true)
				)
			)
			else if(weaponid == 4 || weaponid == 13)
			(
				Float:health, drunk_level, Float:attack = floatround(PlayerCache(playerid)(pStrength) / 20) * 4
				if(PlayerCache(playerid)(pStrength) ) 20)
				(
					GetPlayerHealth(damagedid, health)
					hrp_SetPlayerHealth(damagedid, health - (attack + amount))
				)
				PlayerCache(damagedid)(pBleeding) = 300
				
				drunk_level = GetPlayerDrunkLevel(damagedid)
				if(drunk_level ( 6000)
				(
					SetPlayerDrunkLevel(damagedid, drunk_level + 1000)
				)
				czy_dostal_wpierdol = true
			)
			else if(weaponid == 12 || weaponid == 15)
			(
				Float:health, drunk_level, Float:attack = floatround(PlayerCache(playerid)(pStrength) / 20) * 6
				if(PlayerCache(playerid)(pStrength) ) 20)
				(
					GetPlayerHealth(damagedid, health)
					hrp_SetPlayerHealth(damagedid, health - (attack + amount))
				)
				PlayerCache(damagedid)(pBleeding) = 300
				
				drunk_level = GetPlayerDrunkLevel(damagedid)
				if(drunk_level ( 6000)
				(
					SetPlayerDrunkLevel(damagedid, drunk_level + 1000)
				)
				czy_dostal_wpierdol = true
			)
			//Ca³a reszta oprócz bia³ych i wiatrówki, paralizatorów.
			else
			(
				if(amount ) 7.0)
				(
					if((WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID) || WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID) || WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID)) && !PlayerCache(playerid)(pTagging))
					(
						if(weaponid == WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID))
						(
							//ammo = GetPlayerWeaponAmmo(playerid, WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID))
							
							//WeaponCache(playerid)(WEAPON_MAIN)(pLastAmmo) = ammo
							WeaponCache(playerid)(WEAPON_MAIN)(pShot) = true
						)
						if(weaponid == WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID))
						(
							//ammo = GetPlayerWeaponAmmo(playerid, WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID))
							
							//WeaponCache(playerid)(WEAPON_SIDE)(pLastAmmo) = ammo
							WeaponCache(playerid)(WEAPON_SIDE)(pShot) = true
						)
						if(weaponid == WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID))
						(
							//ammo = GetPlayerWeaponAmmo(playerid, WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID))
							
							//WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = ammo
							WeaponCache(playerid)(WEAPON_FUNC)(pShot) = true
						)
					)
				)
				if(!PlayerCache(damagedid)(pArmour))
				(
					if(!PlayerCache(damagedid)(pWoundAnim))
					(
						if(!IsPlayerInAnyVehicle(damagedid))
						(
							// Arczir - znowu wydupcanie ale po postrzale
							Float:chance = 0.6 * 30
							rand = random(100)
							
							if(rand )= chance)
								ApplyPlayerWound(damagedid, 6, true)
						)
						
						if(!PlayerCache(damagedid)(pBleeding)) (
							string(64)
							format(string, sizeof(string), ** %s zaczyna krwawic., PlayerName(damagedid))
							ProxDetector(10.0, damagedid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
						)
						PlayerCache(damagedid)(pBleeding) = 300
					)
					else
					(
						PlayerCache(damagedid)(pWoundedTime) += 6
					)
				)
				else
				(
					// Kamizelki
					GetPlayerArmour(damagedid, PlayerCache(damagedid)(pArmour))
					if(!PlayerCache(damagedid)(pArmorDisplay) && PlayerCache(damagedid)(pArmour) ( 100.0)
					(
						PlayerCache(damagedid)(pArmorDisplay) = true
					)
					
					// ma kamizelke i niech dostanie okres
					randBleed = random(100)
					if(randBleed ( 15)
					(
						PlayerCache(damagedid)(pBleeding) = 300
					)
					
					// Wydupcanie z kamizelk¹
					Float:chance = 0.6 * 30 + 60
					rand = random(100)
					if(rand )= floatround(chance))
						ApplyPlayerWound(damagedid, 6, true)
				)
			)
			
			if(!czy_dostal_wpierdol)
			(
				Float:health = 0.0
				GetPlayerHealth(damagedid, health)
				hrp_SetPlayerHealth(damagedid, health - amount)
			)
		)
	)
	
	// Dodaj logi DMG
	printf((dmg) Gracz %s (uid: %d) zadal obrazenia graczowi %s (uid: %d) weap: %d, dmg: %f, PlayerName(playerid), PlayerCache(playerid)(pUID), PlayerName(damagedid), PlayerCache(damagedid)(pUID), weaponid, amount)
	
	//Czerwony nick przy zadawaniu jakiegokolwiek damagea.
	string(128)
	if(!PlayerCache(damagedid)(pMaskUID))
	(
		format(string, sizeof(string), %s (%d)%s, PlayerName(damagedid), damagedid, GetPlayerStatusInfo(damagedid))
	)
	else
	(
		format(string, sizeof(string), %s%s, PlayerName(damagedid), GetPlayerStatusInfo(damagedid))
	)
	Update3DTextLabelText(Text3D:PlayerCache(damagedid)(pNameTag), 0xFF040088, string)
	SetTimerEx(SetPlayerNormalColor, 500, false, d, damagedid)*/
	return 1
)

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
( // seler - probujemy wprowadzic hitboxy
	/*
	issuerid - napastnik
	playerid - ofiara
	*/
	if(PlayerCache(playerid)(pAdminDuty))
	(
		return 0
	)
	if(GlobalGod)
	(
		Float:health = 0.0
		GetPlayerHealth(playerid, health)
		hrp_SetPlayerHealth(playerid, health)
		return 0
	)
	if(!Logged(playerid) || !Spawned(playerid))
	(
		Float:health = 0.0
		GetPlayerHealth(playerid, health)
		hrp_SetPlayerHealth(playerid, health)
		return 0
	)
	if(PlayerCache(playerid)(pBW) ) 0)
	(
		hrp_SetPlayerHealth(playerid, 20)
		return 0
	)
	if(issuerid != INVALID_PLAYER_ID) // If not self-inflicted
    (
		if(PlayerCache(issuerid)(pRoped) != INVALID_PLAYER_ID)
		(
			Float:health = 0.0
			GetPlayerHealth(playerid, health)
			hrp_SetPlayerHealth(playerid, health)
			return 0
		)
		if(PlayerCache(issuerid)(pGamePoints) ( 50)
		(
			if(weaponid != 0 && weaponid ( 47 && weaponid != WeaponCache(issuerid)(WEAPON_MAIN)(pWeaponID) && weaponid != WeaponCache(issuerid)(WEAPON_SIDE)(pWeaponID) && weaponid != WeaponCache(issuerid)(WEAPON_FUNC)(pWeaponID))
			(
				weap_name(24), string(64)
				GetWeaponName(weaponid, weap_name, 24)

				ResetPlayerWeapons(issuerid)
				
				format(string, sizeof(string), WeaponHack (WeapID: %d, WeapName: %s)., weaponid, weap_name)
				hrp_Kick(issuerid, -1, string)
				return 0
			)
		)
		if(PlayerCache(issuerid)(pGamePoints) ( 100 && PlayerCache(issuerid)(pPremiumTime) ( gettime())
		(
			if(weaponid != 0 && weaponid ( 47 && !PlayerCache(issuerid)(pTagging))
			(
				weap_name(24), string(64)
				GetWeaponName(weaponid, weap_name, 24)

				ResetPlayerWeapons(issuerid)
				
				format(string, sizeof(string), WeaponHack (WeapID: %d, WeapName: %s)., weaponid, weap_name)
				hrp_Ban(issuerid, -1, string, 0)
				return 0
			)
		)
	
		// wszystkie bronie
        if((weaponid )= 0 && weaponid (= 5) || (weaponid ) 15 && weaponid ( 39) || (weaponid )= 10 && weaponid (= 15))
		(
			bool:coldsteel_dmg = false // DMG z broni bia³ej
			bool:kevlar_shoot = false // strza³ w kamizelkê
			Float:attack // DMG z ataku
			Float:targetHP = 0.0
			GetPlayerHealth(playerid, targetHP)
			
			if(weaponid == 0) // piêœci
			(
				Float:health attack = floatround(PlayerCache(issuerid)(pStrength) / 20)
				if(PlayerCache(issuerid)(pStrength) ) 20)
				(
					GetPlayerHealth(playerid, health)
					hrp_SetPlayerHealth(playerid, health - (attack + amount))
				)
				
				coldsteel_dmg = true
			)
			else if(weaponid == 1) // kastet
			(
				Float:health attack = floatround(PlayerCache(issuerid)(pStrength) / 20) * 2
				if(PlayerCache(issuerid)(pStrength) ) 20)
				(
					GetPlayerHealth(playerid, health)
					hrp_SetPlayerHealth(playerid, health - (attack + amount))
				)
				
				coldsteel_dmg = true
			)
			else if(weaponid == 3 || weaponid == 5 || weaponid == 10 || weaponid == 11) // pa³ka policyjna, baseball, dildo(teleskop), dildo(metalowa rurka)
			(
				Float:health attack = floatround(PlayerCache(issuerid)(pStrength) / 20) * 3
				if(PlayerCache(issuerid)(pStrength) ) 20)
				(
					GetPlayerHealth(playerid, health)
					hrp_SetPlayerHealth(playerid, health - (attack + amount))
				)
				
				group_id_fix = GetPlayerDutyGroupID(issuerid)
				if(GroupData(group_id_fix)(gType) == GROUP_POLICE || GroupData(group_id_fix)(gType) == GROUP_DOC)
				(
					ApplyPlayerWound(playerid, 6, true)
				)
				
				coldsteel_dmg = true
			)
			else if(weaponid == 4 || weaponid == 13) // nó¿, wibrator2(nó¿)
			(
				Float:health attack = floatround(PlayerCache(issuerid)(pStrength) / 20) * 4
				if(PlayerCache(issuerid)(pStrength) ) 20)
				(
					GetPlayerHealth(playerid, health)
					hrp_SetPlayerHealth(playerid, health - (attack + amount))
				)
				PlayerCache(playerid)(pBleeding) = 30
				
				coldsteel_dmg = true
			)
			else if(weaponid == 12 || weaponid == 15) // wibrator(maczeta), laska(siekiera)
			(
				Float:health attack = floatround(PlayerCache(issuerid)(pStrength) / 20) * 6
				if(PlayerCache(issuerid)(pStrength) ) 20)
				(
					GetPlayerHealth(playerid, health)
					hrp_SetPlayerHealth(playerid, health - (attack + amount))
				)
				PlayerCache(playerid)(pBleeding) = 30
				
				coldsteel_dmg = true
			)
			else 
			(
				PlayerDamageCache(playerid)(bodypart) = true
				if(amount ) 7.0)
				(
					if((WeaponCache(issuerid)(WEAPON_MAIN)(pWeaponUID) || WeaponCache(issuerid)(WEAPON_SIDE)(pWeaponUID) || WeaponCache(issuerid)(WEAPON_FUNC)(pWeaponUID)) && !PlayerCache(issuerid)(pTagging))
					(
						if(weaponid == WeaponCache(issuerid)(WEAPON_MAIN)(pWeaponID))
						(
							WeaponCache(issuerid)(WEAPON_MAIN)(pShot) = true
						)
						if(weaponid == WeaponCache(issuerid)(WEAPON_SIDE)(pWeaponID))
						(
							WeaponCache(issuerid)(WEAPON_SIDE)(pShot) = true
						)
						if(weaponid == WeaponCache(issuerid)(WEAPON_FUNC)(pWeaponID))
						(
							WeaponCache(issuerid)(WEAPON_FUNC)(pShot) = true
						)
					)
				)

				if(bodypart == 9) // g³owa
				(
					attack = floatround(amount)
				)
				else if(bodypart == 8 || bodypart == 7 || bodypart == 4) // prawa noga, lewa noga, jajca i penis
				(
					if(!PlayerCache(playerid)(pWoundAnim) && targetHP ( 25.0)
					(
						if(!IsPlayerInAnyVehicle(playerid))
						(
							ApplyPlayerWound(playerid, 3, true)
						)
					)
					else
					(
						PlayerCache(playerid)(pWoundedTime) += 3
					)
				)
				else if(bodypart == 6 || bodypart == 5) // prawa rêka, lewa rêka
				(
					if(targetHP ( 25.0) (
						PlayerCache(playerid)(pBlockShooting) = 5
					)
				)
				else if(bodypart == 3) // brzuch i klatka piersiowa
				(
					if(!PlayerCache(playerid)(pArmour))
					(
						
					)
					else
					(
						hrp_SetPlayerHealth(playerid, targetHP)
						kevlar_shoot = true
					)
				)
				
			)
			if(!coldsteel_dmg && !kevlar_shoot)
			(
				hrp_SetPlayerHealth(playerid, targetHP - (attack + amount))
			)
			if(!kevlar_shoot)
			(
				Float:armour = 0.0
				GetPlayerArmour(playerid, armour)
				hrp_SetPlayerArmour(playerid, armour)
			)
		)
		// Dodaj logi DMG
		printf((dmg) Gracz %s (uid: %d) zadal obrazenia graczowi %s (uid: %d) weap: %d, dmg: %f, bodypart: %d, PlayerName(issuerid), PlayerCache(issuerid)(pUID), PlayerName(playerid), PlayerCache(playerid)(pUID), weaponid, amount, bodypart)
	
		//Czerwony nick przy zadawaniu jakiegokolwiek damagea.
		string(128)
		if(!PlayerCache(playerid)(pMaskUID))
		(
			format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
		)
		else
		(
			format(string, sizeof(string), %s%s, PlayerName(playerid), GetPlayerStatusInfo(playerid))
		)
		Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), 0xFF040088, string)
		SetTimerEx(SetPlayerNormalColor, 500, false, d, playerid)
    )
	return 1
)


/*
		0.3z Callback - mo¿e wyst¹piæ warning przy kompilacji, nie patrzcie na to
		return 1 - pozwala zadaæ DMG
		return 0 - nie zabierze HP
		
		(( przynajmniej wiki tak mówi, mo¿na zaufaæ ))
		* póki co tylko warningi dodam, bo banowanie systemowe czêsto zawodzi
*/

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
(
	if(hittype != BULLET_HIT_TYPE_NONE) //0.3.7 Aim Crash
	(
		if((fX (= -1000.0 || fX )= 1000.0) || (fY (= -1000.0 || fY )= 1000.0) || (fZ (= -1000.0 || fZ )= 1000.0) || ((hittype != BULLET_HIT_TYPE_PLAYER) && (hittype != BULLET_HIT_TYPE_VEHICLE) && (hittype != BULLET_HIT_TYPE_OBJECT) && (hittype != BULLET_HIT_TYPE_PLAYER_OBJECT)))
		(
			hrp_Kick(playerid, -1, Aim-crash) //wywal chuja
			return 0 // Desync pocisku
		)
		if(!(-1000.0 (= fX (= 1000.0) || !(-1000.0 (= fY (= 1000.0) || !(-1000.0 (= fZ (= 1000.0)) // 0.3z Bullet Crash
		(
			hrp_Kick(playerid, -1, Aim-crash) //wywal chuja
			return 0 // Desync pocisku
		)
	)
	
	if( hittype == BULLET_HIT_TYPE_PLAYER ) // Tylko gdy do gracza strzeli to mo¿na wywaliæ - fix z 0.3z
    (
        if( !( -20.0 (= fX (= 20.0 ) || !( -20.0 (= fY (= 20.0 ) || !( -20.0 (= fZ (= 20.0 ) ) 
        (
            //                Kick dla cheatera
			hrp_Kick(playerid, -1, Cheater WC)
            return 0 // desynchronizujemy strza³
        )
    )
	
	class = GetWeaponClass(weaponid), ammo = GetPlayerWeaponAmmo(playerid, WeaponCache(playerid)(class)(pWeaponID))
	if(ammo ) WeaponCache(playerid)(class)(pLastAmmo) && WeaponCache(playerid)(class)(pShot))
	(
		ShowAdminLog(~r~(TESTOWE) ~w~Gracz %s byc moze uzywa ammohack, lecz nie sugeruj sie tym jeszcze, PlayerName(playerid))
	)
	
	return 1
)