public OnPlayerEnterCheckpoint(playerid)
(
	if(Checkpoint(playerid))
	(
		DisablePlayerCheckpoint(playerid)

		Checkpoint(playerid) = 0
	)
	
	return 1
)

public OnPlayerLeaveCheckpoint(playerid)
(
	return 1
)

public OnPlayerEnterRaceCheckpoint(playerid)
(
	if(PlayerCache(playerid)(pCourse))
	(
		switch(PlayerCache(playerid)(pCourseCP))
		(
			case 1:
				SetPlayerRaceCheckpoint(playerid, 0,1170.5844,-1742.2474,13.3984,1174.4644,-1850.6838,13.3984, 5.0)
			case 2:
				SetPlayerRaceCheckpoint(playerid, 0,1174.4644,-1850.6838,13.3984,1312.0121,-1853.1628,13.3828, 5.0)
			case 3:
				SetPlayerRaceCheckpoint(playerid, 0,1312.0121,-1853.1628,13.3828, 1312.9114,-1733.6487,13.3828, 5.0)
			case 4:
				SetPlayerRaceCheckpoint(playerid, 0, 1312.9114,-1733.6487,13.3828, 1447.9456,-1733.6399,13.3828, 5.0)
			case 5:
				SetPlayerRaceCheckpoint(playerid, 0, 1447.9456,-1733.6399,13.3828, 1566.7976,-1732.2648,13.3828, 5.0)
			case 6:
				SetPlayerRaceCheckpoint(playerid, 0, 1566.7976,-1732.2648,13.3828, 1569.2767,-1871.5590,13.3906, 5.0)
			case 7:
				SetPlayerRaceCheckpoint(playerid, 0, 1569.2767,-1871.5590,13.3906, 1668.7550,-1873.0698,13.3828, 5.0)
			case 8:
				SetPlayerRaceCheckpoint(playerid, 0, 1668.7550,-1873.0698,13.3828, 1692.0956,-1774.9159,13.3828, 5.0)
			case 9:
				SetPlayerRaceCheckpoint(playerid, 0, 1692.0956,-1774.9159,13.3828, 1692.5432,-1634.3065,13.3828, 5.0)
			case 10:
				SetPlayerRaceCheckpoint(playerid, 0, 1692.5432,-1634.3065,13.3828, 1689.0814,-1593.4497,13.3796, 5.0)
			case 11:
				SetPlayerRaceCheckpoint(playerid, 0, 1689.0814,-1593.4497,13.3796, 1512.0747,-1589.4910,13.3828, 5.0)
			case 12:
				SetPlayerRaceCheckpoint(playerid, 0, 1512.0747,-1589.4910,13.3828, 1431.2655,-1591.4486,13.3906, 5.0)
			case 13:
				SetPlayerRaceCheckpoint(playerid, 0, 1431.2655,-1591.4486,13.3906, 1454.9132,-1442.3110,13.3906, 5.0)
			case 14:
				SetPlayerRaceCheckpoint(playerid, 0, 1454.9132,-1442.3110,13.3906, 1374.6648,-1392.6779,13.4694, 5.0)
			case 15:
				SetPlayerRaceCheckpoint(playerid, 0, 1374.6648,-1392.6779,13.4694, 1238.4919,-1392.7229,13.1495, 5.0)
			case 16:
				SetPlayerRaceCheckpoint(playerid, 0, 1238.4919,-1392.7229,13.1495, 1064.8376,-1398.3898,13.5001, 5.0)
			case 17:
				SetPlayerRaceCheckpoint(playerid, 0, 1064.8376,-1398.3898,13.5001, 1037.6478,-1571.3474,13.3828, 5.0)
			case 18:
				SetPlayerRaceCheckpoint(playerid, 0, 1037.6478,-1571.3474,13.3828, 1037.0060,-1709.6580,13.3906, 5.0)
			case 19:
				SetPlayerRaceCheckpoint(playerid, 0, 1037.0060,-1709.6580,13.3906,1091.1659,-1750.0553,13.3828, 5.0)
			case 20:
				SetPlayerRaceCheckpoint(playerid, 1,1091.1659,-1750.0553,13.3828,0.0, 0.0,0.0, 5.0)
		)
		
		if(PlayerCache(playerid)(pCourseCP) == 21)
		(
			bool:failed = false
			if(GetPlayerVehicleID(playerid) != PlayerCache(playerid)(pCourseVeh))
			(
				GuiMsg(playerid, Nie dojecha³eœ tym samym pojazdem, którym rozpocz¹³eœ kurs., 1)
				PlayerCache(playerid)(pCourse) = false
				DisablePlayerRaceCheckpoint(playerid)
				PlayerCache(playerid)(pCourseVeh) = INVALID_VEHICLE_ID
				return 1
			)
			
			if(PlayerCache(playerid)(pCourseMS) ) 40.0)
			(
				GuiMsg(playerid, Podczas kursu przekroczy³eœ maksymaln¹ dozwolon¹ prêdkoœæ.\nKurs niezaliczony., 0)
				failed = true
			)
			
			Float:vHealth
			GetVehicleHealth(PlayerCache(playerid)(pCourseVeh), vHealth)
			if(vHealth ( 1000.0)
			(
				GuiMsg(playerid, Uderzy³eœ autem podczas egzaminu, niestety nie zdane!, 0)
				failed = true
			)
			
			if(!failed)
			(
				GuiMsg(playerid, Brawo! Zaliczy³eœ egzamin na prawo jazdy, dokument zosta³ dodany do Twojej postaci.\nSzerokiej drogi!, 0)
				
				PlayerCache(playerid)(pDocuments) += DOC_DRIVER
			)
			
			RemovePlayerFromVehicle(playerid)
			PlayerCache(playerid)(pCourse) = false
			DisablePlayerRaceCheckpoint(playerid)
			ChangeVehicleEngineStatus(PlayerCache(playerid)(pCourseVeh), 0)
			
			CarInfo(PlayerCache(playerid)(pCourseVeh))(cHealth) = 1000.0
			SetVehicleHealth(PlayerCache(playerid)(pCourseVeh), CarInfo(PlayerCache(playerid)(pCourseVeh))(cHealth))
				
			SetVehicleToRespawn(PlayerCache(playerid)(pCourseVeh))
			UpdateVehicleDamageStatus(PlayerCache(playerid)(pCourseVeh), CarInfo(PlayerCache(playerid)(pCourseVeh))(cVisual)(0), CarInfo(PlayerCache(playerid)(pCourseVeh))(cVisual)(1), CarInfo(PlayerCache(playerid)(pCourseVeh))(cVisual)(2), CarInfo(PlayerCache(playerid)(pCourseVeh))(cVisual)(3))
			
			PlayerCache(playerid)(pCourseVeh) = INVALID_VEHICLE_ID
			
		)
		
		PlayerCache(playerid)(pCourseCP)++
		
		return 1
	)
	
	if(PlayerCache(playerid)(pSweep))
	(
		data(256), Float:rX(2), Float:rY(2), Float:rZ(2), rPointName(2)(64), i
		if(PlayerCache(playerid)(pSweepStep) + 1 == PlayerCache(playerid)(pSweepSteps))
		(
			mysql_query_format(SELECT p_name, p_price FROM hrp_sweep_points WHERE p_rid = %d ORDER BY p_id DESC LIMIT 1, PlayerCache(playerid)(pSweepRoute))
			mysql_store_result()

			mysql_fetch_row(data, |)
			sscanf(data, p(|)s(64)d, rPointName(0), i)
			
			mysql_free_result()
			
			format(data, sizeof(data), Ukonczyles trasê ~r~%s. ~w~Na Twoje konto wplynela kwota ~g~$%d., rPointName(0), i)
			TextDrawSetString(Text:TextDrawMainInfo(playerid), data)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			PlayerCache(playerid)(pShowInfoText) = 7
			
			PlayerCache(playerid)(pBankCash) += i
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			DisablePlayerRaceCheckpoint(playerid)

			PlayerCache(playerid)(pSweep) = false
			PlayerCache(playerid)(pSweepStep) = 0
			PlayerCache(playerid)(pSweepSteps) = 0
			PlayerCache(playerid)(pSweepRoute) = 0
			PlayerCache(playerid)(pSweepTime) = 0
		)
		else
		(
			if(PlayerCache(playerid)(pSweepStep) + 2 == PlayerCache(playerid)(pSweepSteps))
			(
				mysql_query_format(SELECT p_name, p_posx, p_posy, p_posz FROM hrp_sweep_points WHERE p_rid = %d ORDER BY p_id DESC LIMIT 2, PlayerCache(playerid)(pSweepRoute))
				mysql_store_result()

				while(mysql_fetch_row(data, |))
				(
					sscanf(data, p(|)s(64)fff, rPointName(i), rX(i), rY(i), rZ(i))
					i++
				)
				
				mysql_free_result()
				
				SetPlayerRaceCheckpoint(playerid, 1, rX(0), rY(0), rZ(0), 0.0, 0.0, 0.0, 5.0)
				
				format(data, sizeof(data), Udaj sie do punktu ~r~%s ~w~aby zakonczyc prace. Niech ulice beda z Toba., rPointName(0))
				TextDrawSetString(Text:TextDrawMainInfo(playerid), data)
				TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
				PlayerCache(playerid)(pShowInfoText) = 7
			)
			else
			(
				mysql_query_format(SELECT p_name, p_posx, p_posy, p_posz FROM hrp_sweep_points WHERE p_rid = %d ORDER BY p_id ASC LIMIT %d, 2, PlayerCache(playerid)(pSweepRoute), PlayerCache(playerid)(pSweepStep) + 1)
				mysql_store_result()

				while(mysql_fetch_row(data, |))
				(
					sscanf(data, p(|)s(64)fff, rPointName(i), rX(i), rY(i), rZ(i))
					i++
				)
				
				mysql_free_result()
				
				SetPlayerRaceCheckpoint(playerid, 0, rX(0), rY(0), rZ(0), rX(1), rY(1), rZ(1), 5.0)
				
				format(data, sizeof(data), Udaj sie do punktu ~r~%s ~w~i postepuj wedlug instrukcji. Niech ulice beda z Toba., rPointName(0))
				TextDrawSetString(Text:TextDrawMainInfo(playerid), data)
				TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
				PlayerCache(playerid)(pShowInfoText) = 7
			)
			
			PlayerCache(playerid)(pSweepStep)++
			PlayerCache(playerid)(pSweepTime) = gettime()
		)
		return 1
	)
	
	PlayerCache(playerid)(pRacePoint) ++
	checkpoint = PlayerCache(playerid)(pRacePoint)
	
	if(checkpoint ( PlayerCache(playerid)(pRaceCheckpoints))
	(
		SetPlayerRaceCheckpoint(playerid, 0, RaceCheckpoint(checkpoint)(0), RaceCheckpoint(checkpoint)(1), RaceCheckpoint(checkpoint)(2), RaceCheckpoint(checkpoint + 1)(0), RaceCheckpoint(checkpoint + 1)(1), RaceCheckpoint(checkpoint + 1)(2), 10.0)
	)
	else
	(
		SetPlayerRaceCheckpoint(playerid, 1, RaceCheckpoint(checkpoint)(0), RaceCheckpoint(checkpoint)(1), RaceCheckpoint(checkpoint)(2), 0.0, 0.0, 0.0, 10.0)
	)
	
	if(checkpoint ) PlayerCache(playerid)(pRaceCheckpoints))
	(
		string(128)
		format(string, sizeof(string), ~w~Wyscig dobiegl konca!~n~~y~Zwyciezca jest ~g~%s, PlayerName(playerid))

		foreach (Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pRacePhase) == 3)
				(
					GameTextForPlayer(i, string, 5000, 3)
					DisablePlayerRaceCheckpoint(i)
					
					PlayerCache(i)(pRacePhase) = 0
					PlayerCache(i)(pRacePoint) = 0
					
					PlayerCache(i)(pRaceCheckpoints) = 0
				)
			)
		)
	)	
	return 1
)

public OnPlayerLeaveRaceCheckpoint(playerid)
(
	return 1
)

public OnPlayerPickUpPickup(playerid, pickupid)
(
	if(pickupid == PressPickup)
	(
		if(PlayerCache(playerid)(pJob) == JOB_PRESSER)
		(
			ShowPlayerDialog(playerid, D_PRESS_JOB, DIALOG_STYLE_MSGBOX, Roznoszenie gazet, Czy chcesz rozpocz¹æ roznoszenie gazet?, Tak, Nie)
		)
		else
		(
			GuiMsg(playerid,Nie posiadasz odpowiedniej pracy dorywczej.,1)
		)
		
		return 1
	)
	if(pickupid == JobPickup)
	(
		ShowPlayerDialog(playerid, D_SELECT_JOB, DIALOG_STYLE_LIST, Dostêpne prace dorywcze:, 1 - Kurier\n2 - Rybak\n3 - Sprz¹tacz ulic, Wybierz, Anuluj)
		return 1
	)
	if(pickupid == MarihuanaGangPickup)
	(
		gangzone_id = GetCurrentPlayerGangZone(playerid)
		if(gangzone_id == -1)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst±pi³ b³±d, Ten pickup niedzia³a tak jak powinien. Zg³o¶ to Administracji., OK, )
			return 1
		)

		group_id_fix = GetGroupID(GangZoneInfo(gangzone_id)(gOwner))
		if(!GroupData(group_id_fix)(gUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst±pi³ b³±d, Ten pickup niedzia³a tak jak powinien. Zg³o¶ to Administracji., OK, )
			return 1
		)

		if(!IsPlayerPermissedGroup(playerid, GangZoneInfo(gangzone_id)(gOwner), PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
			return 1
		)

		string(128)
		format(string, sizeof(string), Aktualnie w magazynie znajduje siê %d marihuany.\nKolejna dostawa pojawi siê w poniedzia³ek.\nBierz ile potrzeba ale u¿ywaj z g³ow±.\n\nWpisz ilo¶æ do pobrania, GangZoneInfo(gangzone_id)(gMarihuana))
		ShowPlayerDialog(playerid, D_GETZONE_MARIHUANA, DIALOG_STYLE_INPUT, Magazyn marihuany, string, OK, Anuluj)
		return 1
	)
	if(pickupid == AmpGangPickup)
	(
		gangzone_id = GetCurrentPlayerGangZone(playerid)
		if(gangzone_id == -1)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst±pi³ b³±d, Ten pickup niedzia³a tak jak powinien. Zg³o¶ to Administracji., OK, )
			return 1
		)

		group_id_fix = GetGroupID(GangZoneInfo(gangzone_id)(gOwner))
		if(!GroupData(group_id_fix)(gUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst±pi³ b³±d, Ten pickup niedzia³a tak jak powinien. Zg³o¶ to Administracji., OK, )
			return 1
		)

		if(!IsPlayerPermissedGroup(playerid, GangZoneInfo(gangzone_id)(gOwner), PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
			return 1
		)

		string(128)
		format(string, sizeof(string), Aktualnie w magazynie znajduje siê %d amfetaminy.\nKolejna dostawa pojawi siê w poniedzia³ek.\nBierz ile potrzeba ale u¿ywaj z g³ow±.\n\nWpisz ilo¶æ do pobrania, GangZoneInfo(gangzone_id)(gAmp))
		ShowPlayerDialog(playerid, D_GETZONE_AMP, DIALOG_STYLE_INPUT, Magazyn Fety, string, OK, Anuluj)
		return 1
	)
	if(pickupid == MetaampGangPickup)
	(
		gangzone_id = GetCurrentPlayerGangZone(playerid)
		if(gangzone_id == -1)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst±pi³ b³±d, Ten pickup niedzia³a tak jak powinien. Zg³o¶ to Administracji., OK, )
			return 1
		)

		group_id_fix = GetGroupID(GangZoneInfo(gangzone_id)(gOwner))
		if(!GroupData(group_id_fix)(gUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst±pi³ b³±d, Ten pickup niedzia³a tak jak powinien. Zg³o¶ to Administracji., OK, )
			return 1
		)

		if(!IsPlayerPermissedGroup(playerid, GangZoneInfo(gangzone_id)(gOwner), PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
			return 1
		)

		string(128)
		format(string, sizeof(string), Aktualnie w magazynie znajduje siê %d metaamfetaminy.\nKolejna dostawa pojawi siê w poniedzia³ek.\nBierz ile potrzeba ale u¿ywaj z g³ow±.\n\nWpisz ilo¶æ do pobrania, GangZoneInfo(gangzone_id)(gMetaamp))
		ShowPlayerDialog(playerid, D_GETZONE_METAAMP, DIALOG_STYLE_INPUT, Magazyn Mety, string, OK, Anuluj)
		return 1
	)
	if(pickupid == WeaponPointPickup)
	(
		string(128), data(128), package_uid, package_itemname(32), package_itemtype, package_itemvalue1, package_itemvalue2, package_itemnumber
		mysql_query_format(SELECT package_uid, package_itemname, package_itemtype, package_itemvalue1, package_itemvalue2, package_itemnumber FROM hrp_limitedpackages WHERE package_playeruid = %d, PlayerCache(playerid)(pUID))
		mysql_store_result()
		if(mysql_num_rows() ) 0)
		(
			while(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)ds(64)dddd, package_uid, package_itemname, package_itemtype, package_itemvalue1, package_itemvalue2, package_itemnumber)
			)
			// seler - tutaj musi skryptowo dac bronie dla playerid
			format(string, sizeof(string), ** Nieznajomy mê¿czyzna k³adzie skrzynkê z broni¹ na ziemiê i odchodzi.)
			ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			
			for(i = 0 i ( package_itemnumber i++)
			(
				CreatePlayerItem(playerid, package_itemname, package_itemtype, package_itemvalue1, package_itemvalue2)
			)
			limitedpackage_id = GetLimitedPackageID(package_uid)
			DeleteLimitedPackage(limitedpackage_id)
			DestroyActor(WeaponPointActor)
			DestroyPickup(WeaponPointPickup)
			WeaponPointPickup = -1
			mysql_free_result()
			return 1
		)
		else
		(
			format(string, sizeof(string), Nieznajomy mê¿czyzna mówi: Zmykaj st¹d szybko, nie na Ciebie czekam.)
			ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
			mysql_free_result()
			return 1
		)
	)


	string(256), lock_text(128), enter_pay(32), doorid = pickupid
	
	if(DoorData(doorid)(dCost) ) 0)
	(
		if(PlayerCache(playerid)(pAdmin))
		(
			format(string, sizeof(string), %s (%d)~n~~y~Nieruchomosc bez wlasciciela~n~~n~Cena: ~g~$%d, DoorData(doorid)(dName), doorid, DoorData(doorid)(dCost))
		)
		else
		(
			format(string, sizeof(string), %s ~n~~y~Nieruchomosc bez wlasciciela~n~~n~Cena: ~g~$%d~n~, DoorData(doorid)(dName), DoorData(doorid)(dCost))
		)
		
		PlayerTextDrawSetString(playerid, TextDrawDoorInfo(playerid), string)
		PlayerTextDrawShow(playerid, TextDrawDoorInfo(playerid))
		PlayerCache(playerid)(pShowDoorText) = 5
		
		TextDrawSetString(Text:TextDrawMainInfo(playerid), ~y~Aby kupic nieruchomosc wpisz~n~~g~/zamieszkaj)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))	
		PlayerCache(playerid)(pShowInfoText) = 5
		
		return 1
	)
 	if(DoorData(doorid)(dEnterPay))
  	(
   		format(enter_pay, sizeof(enter_pay), ~w~~n~Koszt wstepu: ~g~$%d~n~, DoorData(doorid)(dEnterPay))
   	)
	else
	(
		format(enter_pay, sizeof(enter_pay), _)
	)
	if(DoorData(doorid)(dLocked))
	(
		format(lock_text, sizeof(lock_text), ~r~Drzwi sa zamkniete)
	)
	else
	(
   		if(!DoorData(doorid)(dExitX))
	 	(
	  		format(lock_text, sizeof(lock_text), ~w~W trakcie remontu)
		)
		else
		(
  			format(lock_text, sizeof(lock_text), ~y~Aby wejsc, wcisnij jednoczesnie~n~~w~(~b~~h~~h~~k~~SNEAK_ABOUT~ + ~k~~PED_SPRINT~~w~))
		)
  	)
   	if(PlayerCache(playerid)(pAdmin))
   	(
   		format(string, sizeof(string), %s (%d)~n~%s~n~%s, DoorData(doorid)(dName), doorid, enter_pay, lock_text)
   	)
 	else
   	(
  		format(string, sizeof(string), %s~n~%s~n~%s, DoorData(doorid)(dName), enter_pay, lock_text)
	)
	PlayerTextDrawSetString(playerid, TextDrawDoorInfo(playerid), string)
			
	PlayerTextDrawShow(playerid, TextDrawDoorInfo(playerid))
 	PlayerCache(playerid)(pShowDoorText) = 5
	return 1
)