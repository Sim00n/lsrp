CMD:komunikat(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	buffer(512), type(32), varchar(32), string(64)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /komunikat (uid | global))
		return 1
	)
	if(!strcmp(type, uid, true))
	(
		groupuid
		if(sscanf(varchar, ds(64), groupuid, string))
		(
			hrp_Tip(playerid, /komunikat uid (UID grupy) (KOMUNIKAT))
			return 1
		)
		mysql_query_format(SELECT * FROM hrp_groups_messages WHERE group_uid = %d, groupuid)
		mysql_store_result()
		if(mysql_num_rows() ) 0)
		(
			mysql_free_result()
			mysql_query_format(UPDATE hrp_groups_messages SET message = %s, message_owner = %d, message_create = %d WHERE group_uid = %d, string, PlayerCache(playerid)(pUID), gettime(), groupuid)		
			ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil komunikat dla grupy (UID: %d)., PlayerName(playerid), groupuid)
		)
		else
		(
			mysql_free_result()
			format(buffer,sizeof(buffer),INSERT INTO hrp_groups_messages (message, group_uid, message_owner, message_create) VALUES(%s, %d, %d, %d), string, groupuid, PlayerCache(playerid)(pUID), gettime())
			mysql_query(buffer)
			ShowAdminLog(~r~(create) ~w~Administrator %s utworzyl komunikat dla grupy (UID: %d)., PlayerName(playerid), groupuid)
		)
	)
	if(!strcmp(type, global, true))
	(
		if(sscanf(varchar, s(64), string))
		(
			hrp_Tip(playerid, /komunikat global (KOMUNIKAT))
			return 1
		)
		mysql_query_format(SELECT * FROM hrp_groups_messages WHERE group_uid = 0)
		mysql_store_result()
		if(mysql_num_rows() ) 0)
		(
			mysql_free_result()
			mysql_query_format(UPDATE hrp_groups_messages SET message = %s, message_owner = %d, message_create = %d WHERE group_uid = 0, string, PlayerCache(playerid)(pUID), gettime())
			ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil komunikat globalny dla grup., PlayerName(playerid))
		)
		else
		(
			mysql_free_result()
			format(buffer,sizeof(buffer),INSERT INTO hrp_groups_messages (message, group_uid, message_owner, message_create) VALUES(%s, 0, %d, %d), string, PlayerCache(playerid)(pUID), gettime())
			mysql_query(buffer)
			ShowAdminLog(~r~(create) ~w~Administrator %s utworzyl komunikat globalny dla grup., PlayerName(playerid))
		)
	)
	return 1
)

CMD:spojazd(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 )
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32), string(256)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /spojazd (hp | zaparkuj | zamknij | res | visual | gethere | fix))
		return 1
	)
	if(!strcmp(type, hp, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		vehid, Float:health
 		if(sscanf(varchar, df, vehid, health))
		(
			hrp_Tip(playerid, /spojazd hp (ID pojazdu) (HP))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(health ( 350 || health ) 1000)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, HP pojazdu nie mo¿e byæ mniejsze ni¿ 350 oraz wiêksze od 1000., OK, )
			return 1
		)
	 	CarInfo(vehid)(cHealth) = health
	  	SetVehicleHealth(vehid, health)

	   	SaveVehicle(vehid, SAVE_VEH_COUNT)

		ShowAdminLog(~r~(edit) ~w~Supporter %s zmienil ilosc HP pojazdu %s (SampID: %d, UID: %d). Nowy stan HP: %.0f., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), CarInfo(vehid)(cHealth))

		format(string, sizeof(string), Stan techniczny pojazdu zosta³ zmieniony.\nHP pojazdu wynosi teraz: %.0f HP., CarInfo(vehid)(cHealth))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil hp pojazdu %s (UID: %d). Nowy stan HP: %.0f., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), CarInfo(vehid)(cHealth))
		return 1
	)
	if(!strcmp(type, zaparkuj, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /spojazd zaparkuj (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		vehuid = CarInfo(vehid)(cUID)

		GetVehiclePos(vehid, CarInfo(vehid)(cPosX), CarInfo(vehid)(cPosY), CarInfo(vehid)(cPosZ))
		GetVehiclePos(vehid, CarInfo(vehid)(cEPosX), CarInfo(vehid)(cEPosY), CarInfo(vehid)(cEPosZ))
		GetVehicleZAngle(vehid, CarInfo(vehid)(cPosA))

		CarInfo(vehid)(cInteriorID) = GetPlayerInterior(playerid)
		CarInfo(vehid)(cWorldID) = GetPlayerVirtualWorld(playerid)

		SaveVehicle(vehid, SAVE_VEH_POS)

		ShowAdminLog(~r~(edit) ~w~Supporter %s przeparkowal pojazd %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))

		UnspawnVehicle(vehuid)
		SpawnVehicle(vehuid)

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Pojazd zosta³ zaparkowany w miejscu, na którym w³aœnie stoi., OK, )

		hrp_AdminActionLog(%s (UID: %d) przeparkowal pojazd %s (UID: %d) (PosX: %.3f, PosY: %.3f, PosZ: %.3f)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), CarInfo(vehid)(cPosX), CarInfo(vehid)(cPosY), CarInfo(vehid)(cPosZ))
		return 1
	)
	if(!strcmp(type, zamknij, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		
 		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /spojazd zamknij (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(CarInfo(vehid)(cLocked))
		(
	 		format(string, sizeof(string), Pojazd %s (SampID: %d, UID: %d) zosta³ otwarty., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

  			CarInfo(vehid)(cLocked) = false
			SetVehicleLock(vehid, false)
		)
		else
		(
			format(string, sizeof(string), Pojazd %s (SampID: %d, UID: %d) zosta³ zamkniêty., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

  			CarInfo(vehid)(cLocked) = true
			SetVehicleLock(vehid, true)
		)
		SaveVehicle(vehid, SAVE_VEH_LOCK)
		return 1
	)
	if(!strcmp(type, res, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /spojazd res (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
	 	SetVehicleToRespawn(vehid)

		ShowAdminLog(~r~(edit) ~w~Supporter %s przywrocil pojazd %s (SampID: %d, UID: %d) na miejsce spawnu., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))

	  	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie,Pojazd zosta³ przywrócony na miejsce spawnu., OK, )

		hrp_AdminActionLog(%s (UID: %d) przywrocil pojazd %s (UID: %d) na miejsce spawnu., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, visual, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /spojazd visual (ID pojazdu))
			return 1
		)
   		if(CarInfo(vehid)(cUID) == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		UpdateVehicleDamageStatus(vehid, 0, 0, 0, 0)
		GetVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))

		ShowAdminLog(~r~(edit) ~w~Supporter %s naprawil wyglad wizualny pojazdu %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))

		SaveVehicle(vehid, SAVE_VEH_ACCESS)

		hrp_AdminActionLog(%s (UID: %d) naprawil wyglad wizualny pojazdu %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, gethere, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /spojazd gethere (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ,
			interior_id, virtual_world

		GetPlayerPos(playerid, PosX, PosY, PosZ)

		interior_id = GetPlayerInterior(playerid)
		virtual_world = GetPlayerVirtualWorld(playerid)

		SetVehiclePos(vehid, PosX + 3.0, PosY, PosZ)

		LinkVehicleToInterior(vehid, interior_id)
		SetVehicleVirtualWorld(vehid, virtual_world)
		return 1
	)
	if(!strcmp(type, fix, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /spojazd fix (ID pojazdu))
			return 1
		)
   		if(CarInfo(vehid)(cUID) == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		UpdateVehicleDamageStatus(vehid, 0, 0, 0, 0)
		GetVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))

	 	CarInfo(vehid)(cHealth) = 1000.0
	  	SetVehicleHealth(vehid, 1000.0)

	   	SaveVehicle(vehid, SAVE_VEH_COUNT)
		SaveVehicle(vehid, SAVE_VEH_ACCESS)

		format(string, sizeof(string), Pojazd %s (UID: %d) zosta³ ca³kowicie naprawiony., CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(edit) ~w~Supporter %s naprawil calkowicie pojazd %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		hrp_AdminActionLog(%s (UID: %d) naprawil calkowicie pojazd %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, kolor1, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		
		vehid, color1
		if(sscanf(varchar, dd, vehid, color1))
		(
			hrp_Tip(playerid, /spojazd kolor1 (ID pojazdu) (Kolor 1))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(color1 ( 0 || color1 ) 255)
	  	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, ID koloru nie mo¿e byæ mniejsze ni¿ 0 a tak¿e wiêksze ni¿ 255., OK, )
		 	return 1
	   	)
		CarInfo(vehid)(cColor1) = color1
		ChangeVehicleColor(vehid, CarInfo(vehid)(cColor1), CarInfo(vehid)(cColor2))
		
		SaveVehicle(vehid, SAVE_VEH_ACCESS)
		
		ShowAdminLog(~r~(edit) ~w~Supporter %s zmienil kolor pojazdu %s (SampID: %d, UID: %d). Nowy kolor: %d., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), CarInfo(vehid)(cColor1))
		
		format(string, sizeof(string), Kolor pojazdu zosta³ zmieniony. Nowy kolor: %d, color1)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil kolor pojazdu %s (UID: %d). Nowy kolor: %d., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), CarInfo(vehid)(cColor1))
		return 1
	)
	if(!strcmp(type, kolor2, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		
		vehid, color2
		if(sscanf(varchar, dd, vehid, color2))
		(
			hrp_Tip(playerid, /spojazd kolor1 (ID pojazdu) (Kolor 2))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(color2 ( 0 || color2 ) 255)
	  	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, ID koloru nie mo¿e byæ mniejsze ni¿ 0 a tak¿e wiêksze ni¿ 255., OK, )
		 	return 1
	   	)
		CarInfo(vehid)(cColor2) = color2
		ChangeVehicleColor(vehid, CarInfo(vehid)(cColor1), CarInfo(vehid)(cColor2))

		SaveVehicle(vehid, SAVE_VEH_ACCESS)

		ShowAdminLog(~r~(edit) ~w~Supporter %s zmienil kolor pojazdu %s (SampID: %d, UID: %d). Nowy kolor: %d., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), CarInfo(vehid)(cColor2))

		format(string, sizeof(string), Kolor pojazdu zosta³ zmieniony. Nowy kolor: %d, color2)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil kolor pojazdu %s (UID: %d). Nowy kolor: %d., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), CarInfo(vehid)(cColor2))
		return 1
	)
	if(!strcmp(type, spawn, true))
	(
		if(PlayerCache(playerid)(pAdmin) ) -3 )
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		
		
		vehuid
		if(sscanf(varchar, d, vehuid))
		(
			hrp_Tip(playerid, /spojazd spawn (UID pojazdu))
			return 1
		)
		vehid = GetVehicleID(vehuid)
		if(vehid != INVALID_VEHICLE_ID)
		(
			format(string, sizeof(string), Ten pojazd jest ju¿ zespawnowany (SampID: %d, UID: %d)., vehid, vehuid)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
			return 1
		)
		SpawnVehicle(vehuid)
		
		vehid = GetVehicleID(vehuid)
		
		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
		(
			giveplayer_id = GetPlayerID(CarInfo(vehid)(cOwner))
			if(giveplayer_id == INVALID_PLAYER_ID)
			(
				return 1
			)
			if(!Logged(giveplayer_id))
			(
				return 1
			)
			PlayerCache(giveplayer_id)(pCarSpawned) ++
		)
		
	 	format(string, sizeof(string), Pojazd (UID: %d) zosta³ zespawnowany pomyœlnie., vehuid)
	 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(edit) ~w~Supporter %s zespawnowal pojazd %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		hrp_AdminActionLog(%s (UID: %d) zespawnowal pojazd %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, info, true))
	(
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /spojazd info (ID pojazdu))
			return 1
		)
		
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		ShowPlayerVehicleInfo(playerid, vehid)
	)
	return 1
)

CMD:kolor(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	
	if(PlayerCache(playerid)(pUserColor) == 7)
	(
		PlayerCache(playerid)(pUserColor) = 0
	)
	else
	(
		PlayerCache(playerid)(pUserColor) ++
	)
	return 1
)

CMD:sv(playerid, params()) return cmd_spojazd(playerid, params)

CMD:fly(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /fly (up | down | xp | xm | yp | ym))
		hrp_TogglePlayerControllable(playerid, true)
		return 1
	)

	Float:PosX, Float:PosY, Float:PosZ
	GetPlayerPos(playerid, PosX, PosY, PosZ)

	if(!strcmp(type, up, true))
	(
		SetPlayerPos(playerid, PosX, PosY, PosZ + 1)
		hrp_TogglePlayerControllable(playerid, false)
		return 1
	)
	if(!strcmp(type, down, true))
	(
		SetPlayerPos(playerid, PosX, PosY, PosZ - 1)
		hrp_TogglePlayerControllable(playerid, false)
  		return 1
	)
	if(!strcmp(type, xp, true))
	(
		SetPlayerPos(playerid, PosX + 2.5, PosY, PosZ)
		hrp_TogglePlayerControllable(playerid, false)
		return 1
	)
	if(!strcmp(type, xm, true))
	(
		SetPlayerPos(playerid, PosX - 2.5, PosY, PosZ)
		hrp_TogglePlayerControllable(playerid, false)
		return 1
	)
	if(!strcmp(type, yp, true))
	(
		SetPlayerPos(playerid, PosX, PosY + 2.5, PosZ)
		hrp_TogglePlayerControllable(playerid, false)
		return 1
	)
	if(!strcmp(type, ym, true))
	(
		SetPlayerPos(playerid, PosX, PosY - 2.5, PosZ)
		hrp_TogglePlayerControllable(playerid, false)
		return 1
	)
	return 1
)

CMD:abudka(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(64), string(256), gameid
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /abudka (stworz | usun | id | lista | grupa | drzwi | goto))
		return 1
	)
	if(!strcmp(type, stworz, true))
	(
		Float:PosX, Float:PosY, Float:PosZ, Float:Radius
		if(sscanf(varchar, f, Radius))
		(
			hrp_Tip(playerid, /abudka stworz (zasieg))
			return 1
		)
		GetPlayerPos(playerid, PosX, PosY, PosZ)
		gameid = CreateBooth(PosX, PosY, PosZ, Radius)
		SaveBooth(gameid)
		
		ShowAdminLog(~r~(create) ~w~Administrator %s stworzyl budke (SampID: %d, UID: %d)., PlayerName(playerid), gameid, BoothData(gameid)(bUID))
		hrp_AdminActionLog(%s (UID: %d) stworzyl budke (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), BoothData(gameid)(bUID))
		
		format(string, sizeof(string), Budka zostala utworzona.\nSampid: %d\nUID: %d, gameid, BoothData(gameid)(bUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, usun, true))
	(
		if(sscanf(varchar, d, gameid))
		(
			hrp_Tip(playerid, /abudka usun (sampid))
			return 1
		)
		if(BoothData(gameid)(bUID))
		(
			ShowAdminLog(~r~(create) ~w~Administrator %s usunal budke (SampID: %d, UID: %d)., PlayerName(playerid), gameid, BoothData(gameid)(bUID))
			hrp_AdminActionLog(%s (UID: %d) usunal budke (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), BoothData(gameid)(bUID))

			DeleteBooth(gameid)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Budka zostala usunieta., OK, )
			return 1
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano nieprawidlowe sampid budki. Sprobuj /abudka lista, OK, )
		return 1
	)
	if(!strcmp(type, id, true))
	(
		foreach(Booths, boothid)
		(
			if(IsPlayerInRangeOfPoint(playerid, BoothData(boothid)(bRadius), BoothData(boothid)(bPosX), BoothData(boothid)(bPosY), BoothData(boothid)(bPosZ)))
			(
				format(string, sizeof(string), Sampid budki: %d\nUid budki: %d\nPosX: %f|PosY: %f|PosZ: %f\nW³aœciciel: %s (Uid: %d)\nUid drzwi: %d, boothid, BoothData(boothid)(bUID), BoothData(boothid)(bPosX), BoothData(boothid)(bPosY), BoothData(boothid)(bPosZ), GroupData(GetGroupID(BoothData(boothid)(bOwner)))(gName), BoothData(boothid)(bOwner), BoothData(boothid)(bDoorUID))
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacje na temat budki, string, OK, )
				return 1
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê aktualnie w pobli¿u ¿adnej budki., OK, )
		return 1
	)
	if(!strcmp(type, lista, true))
	(
		list_items(1024)
		format(list_items, sizeof(list_items), SampID\tNazwa grupy)
		foreach(Booths, boothid)
		(
			if(BoothData(boothid)(bUID))
			(
				booth_owner = GetGroupID(BoothData(boothid)(bOwner))
				if(GroupData(booth_owner)(gUID))
				(
					format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, boothid, GroupData(booth_owner)(gName))
				)
				else
				(
					format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, boothid, Brak w³aœcicela)
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Lista budek, list_items, OK, Anuluj)
		return 1
	)
	if(!strcmp(type, grupa, true))
	(
		group_uid
		if(sscanf(varchar, dd, gameid, group_uid))
		(
			hrp_Tip(playerid, /abudka grupa (sampid budki) (uid grupy))
			return 1
		)
		if(!BoothData(gameid)(bUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne sampid budki., OK, )
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)

		ShowAdminLog(~r~(create) ~w~Administrator %s przypisal budke (SampID: %d, UID: %d) pod grupe %s (SampID: %d, UID: %d)., PlayerName(playerid), gameid, BoothData(gameid)(bUID), GroupData(group_id_fix)(gName), group_id_fix, group_uid)
		hrp_AdminActionLog(%s (UID: %d) przypisal budke (UID: %d) pod grupe %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), BoothData(gameid)(bUID), GroupData(group_id_fix)(gName), group_uid)

		BoothData(gameid)(bOwner) = group_uid
		SaveBooth(gameid)

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Budka zosta³a przypisana pod grupê., OK, )

		return 1
	)
	if(!strcmp(type, drzwi, true))
	(
		door_id
		if(sscanf(varchar, dd, gameid, door_id))
		(
			hrp_Tip(playerid, /abudka drzwi (sampid budki) (sampid drzwi))
			return 1
		)
		if(!BoothData(gameid)(bUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne sampid budki., OK, )
			return 1
		)
		if(door_id == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne sampid drzwi., OK, )
			return 1
		)
		
   		ShowAdminLog(~r~(create) ~w~Administrator %s przypisal budke (SampID: %d, UID: %d) pod drzwi %s (SampID: %d, UID: %d)., PlayerName(playerid), gameid, BoothData(gameid)(bUID), DoorData(door_id)(dName), door_id, DoorData(door_id)(dUID))
		hrp_AdminActionLog(%s (UID: %d) przypisal budke (UID: %d) pod drzwi %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), BoothData(gameid)(bUID), DoorData(door_id)(dName), DoorData(door_id)(dUID))

		BoothData(gameid)(bDoorUID) = DoorData(door_id)(dUID)
		SaveBooth(gameid)

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Drzwi zosta³y przypisane do budki., OK, )

		return 1
	)
	if(!strcmp(type, goto, true))
	(
		if(sscanf(varchar, d, gameid))
		(
			hrp_Tip(playerid, /abudka goto (sampid budki))
			return 1
		)
		if(!BoothData(gameid)(bUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne sampid budki., OK, )
			return 1
		)
		hrp_SetPlayerPos(playerid, BoothData(gameid)(bPosX), BoothData(gameid)(bPosY), BoothData(gameid)(bPosZ))
   		ShowAdminLog(~r~(create) ~w~Administrator %s przeteleportowal sie do budki (SampID: %d, UID: %d)., PlayerName(playerid), gameid, BoothData(gameid)(bUID))
   		return 1
	)
	return 1
)
CMD:ab(playerid, params()) return cmd_abudka(playerid, params)

CMD:apetrol(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(64), string(256), gameid
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /apetrol (stworz | usun | id | lista | grupa | drzwi | goto))
		return 1
	)
	if(!strcmp(type, stworz, true))
	(
		Float:PosX, Float:PosY, Float:PosZ, Float:Radius
		if(sscanf(varchar, f, Radius))
		(
			hrp_Tip(playerid, /apetrol stworz (zasieg))
			return 1
		)
		GetPlayerPos(playerid, PosX, PosY, PosZ)
		gameid = CreatePetrol(PosX, PosY, PosZ, Radius)
		SavePetrol(gameid)
		
		ShowAdminLog(~r~(create) ~w~Administrator %s stworzyl cpn (SampID: %d, UID: %d)., PlayerName(playerid), gameid, PetrolData(gameid)(bUID))
		hrp_AdminActionLog(%s (UID: %d) stworzyl cpn (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), PetrolData(gameid)(bUID))
		
		format(string, sizeof(string), CPN zostal utworzony.\nSampid: %d\nUID: %d, gameid, PetrolData(gameid)(bUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, usun, true))
	(
		if(sscanf(varchar, d, gameid))
		(
			hrp_Tip(playerid, /apetrol usun (sampid))
			return 1
		)
		if(PetrolData(gameid)(bUID))
		(
			ShowAdminLog(~r~(create) ~w~Administrator %s usunal cpn (SampID: %d, UID: %d)., PlayerName(playerid), gameid, PetrolData(gameid)(bUID))
			hrp_AdminActionLog(%s (UID: %d) usunal cpn (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), PetrolData(gameid)(bUID))

			DeletePetrol(gameid)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, CPN zostala usunieta., OK, )
			return 1
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano nieprawidlowe sampid CPNu. Sprobuj /apetrol lista, OK, )
		return 1
	)
	if(!strcmp(type, id, true))
	(
		foreach(Petrols, boothid)
		(
			if(IsPlayerInRangeOfPoint(playerid, PetrolData(boothid)(bRadius), PetrolData(boothid)(bPosX), PetrolData(boothid)(bPosY), PetrolData(boothid)(bPosZ)))
			(
				format(string, sizeof(string), Sampid CPNu: %d\nUid CPNu: %d\nPosX: %f|PosY: %f|PosZ: %f\nW³aœciciel: %s (Uid: %d), boothid, PetrolData(boothid)(bUID), PetrolData(boothid)(bPosX), PetrolData(boothid)(bPosY), PetrolData(boothid)(bPosZ), GroupData(GetGroupID(PetrolData(boothid)(bOwner)))(gName), PetrolData(boothid)(bOwner))
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacje na temat budki, string, OK, )
				return 1
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê aktualnie w pobli¿u ¿adnego CPNu., OK, )
		return 1
	)
	if(!strcmp(type, lista, true))
	(
		list_items(1024)
		format(list_items, sizeof(list_items), SampID\tNazwa grupy)
		foreach(Petrols, boothid)
		(
			if(PetrolData(boothid)(bUID))
			(
				booth_owner = GetGroupID(PetrolData(boothid)(bOwner))
				if(GroupData(booth_owner)(gUID))
				(
					format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, boothid, GroupData(booth_owner)(gName))
				)
				else
				(
					format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, boothid, Brak w³aœcicela)
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Lista budek, list_items, OK, Anuluj)
		return 1
	)
	if(!strcmp(type, grupa, true))
	(
		group_uid
		if(sscanf(varchar, dd, gameid, group_uid))
		(
			hrp_Tip(playerid, /apetrol grupa (sampid cpnu) (uid grupy))
			return 1
		)
		if(!PetrolData(gameid)(bUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne sampid CPNu., OK, )
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)

		ShowAdminLog(~r~(create) ~w~Administrator %s przypisal CPN (SampID: %d, UID: %d) pod grupe %s (SampID: %d, UID: %d)., PlayerName(playerid), gameid, PetrolData(gameid)(bUID), GroupData(group_id_fix)(gName), group_id_fix, group_uid)
		hrp_AdminActionLog(%s (UID: %d) przypisal CPN (UID: %d) pod grupe %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), PetrolData(gameid)(bUID), GroupData(group_id_fix)(gName), group_uid)

		PetrolData(gameid)(bOwner) = group_uid
		SavePetrol(gameid)

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, CPN zosta³a przypisana pod grupê., OK, )

		return 1
	)
	if(!strcmp(type, goto, true))
	(
		if(sscanf(varchar, d, gameid))
		(
			hrp_Tip(playerid, /apetrol goto (sampid cpnu))
			return 1
		)
		if(!PetrolData(gameid)(bUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne sampid cpnu., OK, )
			return 1
		)
		hrp_SetPlayerPos(playerid, PetrolData(gameid)(bPosX), PetrolData(gameid)(bPosY), PetrolData(gameid)(bPosZ))
   		ShowAdminLog(~r~(create) ~w~Administrator %s przeteleportowal sie do CPNu (SampID: %d, UID: %d)., PlayerName(playerid), gameid, PetrolData(gameid)(bUID))
   		return 1
	)
	return 1
)

CMD:addsweep(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	group, price, name(64), Float:swPosX, Float:swPosY, Float:swPosZ
	if(sscanf(params, dds(64), group, price, name))
	(
		hrp_Tip(playerid, /addsweep (grupa) (wyp³ata) (nazwa))
		return 1
	)
	
	GetPlayerPos(playerid, swPosX, swPosY, swPosZ)
	
	mysql_query_format(INSERT INTO hrp_sweep_points (p_rid, p_name, p_posx, p_posy, p_posz, p_price) VALUES(%d, %s, %f, %f, %f, %d), group, name, swPosX, swPosY, swPosZ, price)

	string(64)
	format(string, sizeof(string), Punkt ~g~%s ~w~w grupie ~g~%d ~w~na koordach ~r~%f~w~, ~r~%f~w~, ~r~%f ~w~o cenie ~g~$%d ~w~zostal prawidlowo dodany., name, group, swPosX, swPosY, swPosZ, price)
	TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
	TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
	PlayerCache(playerid)(pShowInfoText) = 7
	
	return 1
)

CMD:apojazd(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32), string(256)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /apojazd (stworz | model | kolor1 | kolor2 | paliwo | hp | zaparkuj | zamknij | res | fix | goto))
		hrp_Tip(playerid, /apojazd (przebieg | info | usun | visual | id | przypisz | unspawn | spawn | resall | resrange | silnik))
		return 1
	)
	if(!strcmp(type, stworz, true))
	(
		modelid, color1, color2
		if(sscanf(varchar, ddd, modelid, color1, color2))
		(
			hrp_Tip(playerid, /apojazd stworz (Model) (Kolor1) (Kolor2))
			return 1
		)
		if(modelid ( 400 || modelid ) 611)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Model pojazdu nie mo¿e byæ mniejszy ni¿ 400 oraz wiêkszy ni¿ 611., OK, )
			return 1
		)
	 	if(color1 ( 0 || color1 ) 255 || color2 ( 0 || color2 ) 255)
	  	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, ID koloru nie mo¿e byæ mniejsze ni¿ 0 a tak¿e wiêksze ni¿ 255., OK, )
		 	return 1
	   	)
		Float:x, Float:y, Float:z, gameid
		GetPlayerPos(playerid, x, y, z)
		gameid = CreateCar(modelid, x+2, y, z, 0.0, color1, color2, 6000000)

		format(string, sizeof(string), Pojazd zosta³ stworzony pomyœlnie (SampID: %d)., gameid)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		
		ShowAdminLog(~r~(create) ~w~Administrator %s stworzyl pojazd %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(gameid)(cName), gameid, CarInfo(gameid)(cUID))

		hrp_AdminActionLog(%s (UID: %d) stworzyl pojazd %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(gameid)(cName), CarInfo(gameid)(cUID))
		return 1
	)
	if(!strcmp(type, model, true))
	(
		vehid, modelid
		if(sscanf(varchar, dd, vehid, modelid))
		(
			hrp_Tip(playerid, /apojazd model (ID pojazdu) (Model))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(modelid ( 400 || modelid ) 611)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Model pojazdu nie mo¿e byæ mniejszy ni¿ 400 oraz wiêkszy ni¿ 611., OK, )
			return 1
		)
	 	Float:x, Float:y, Float:z, Float:a
	  	GetVehiclePos(vehid, x, y, z)
	   	GetVehicleZAngle(vehid, a)
	   	
	   	vehuid = CarInfo(vehid)(cUID)
	   	
		CarInfo(vehid)(cModel) = modelid
		CarInfo(vehid)(cFuel) = GetVehicleMaxFuel(modelid)
	   	
		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil model pojazdu %s (SampID: %d, UID: %d). Nowy model: %d., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), CarInfo(vehid)(cModel))
		hrp_AdminActionLog(%s (UID: %d) zmienil model pojazdu %s (UID: %d). Nowy model: %d., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), modelid)

		strmid(CarInfo(vehid)(cName), VehicleData(modelid - 400)(vName), 0, strlen(VehicleData(modelid - 400)(vName)), 64)
		SaveVehicle(vehid, SAVE_VEH_THINGS)
	   	
		UnspawnVehicle(vehuid)
		SpawnVehicle(vehuid)
		
		format(string, sizeof(string), Model pojazdu zosta³ zmieniony. Nowy model: %d, modelid)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		return 1
	)
	if(!strcmp(type, kolor1, true))
	(
		vehid, color1
		if(sscanf(varchar, dd, vehid, color1))
		(
			hrp_Tip(playerid, /apojazd kolor1 (ID pojazdu) (Kolor 1))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(color1 ( 0 || color1 ) 255)
	  	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, ID koloru nie mo¿e byæ mniejsze ni¿ 0 a tak¿e wiêksze ni¿ 255., OK, )
		 	return 1
	   	)
		CarInfo(vehid)(cColor1) = color1
		ChangeVehicleColor(vehid, CarInfo(vehid)(cColor1), CarInfo(vehid)(cColor2))
		
		SaveVehicle(vehid, SAVE_VEH_ACCESS)
		
		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil kolor pojazdu %s (SampID: %d, UID: %d). Nowy kolor: %d., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), CarInfo(vehid)(cColor1))
		
		format(string, sizeof(string), Kolor pojazdu zosta³ zmieniony. Nowy kolor: %d, color1)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil kolor pojazdu %s (UID: %d). Nowy kolor: %d., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), CarInfo(vehid)(cColor1))
		return 1
	)
	if(!strcmp(type, kolor2, true))
	(
		vehid, color2
		if(sscanf(varchar, dd, vehid, color2))
		(
			hrp_Tip(playerid, /apojazd kolor1 (ID pojazdu) (Kolor 2))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(color2 ( 0 || color2 ) 255)
	  	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, ID koloru nie mo¿e byæ mniejsze ni¿ 0 a tak¿e wiêksze ni¿ 255., OK, )
		 	return 1
	   	)
		CarInfo(vehid)(cColor2) = color2
		ChangeVehicleColor(vehid, CarInfo(vehid)(cColor1), CarInfo(vehid)(cColor2))

		SaveVehicle(vehid, SAVE_VEH_ACCESS)

		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil kolor pojazdu %s (SampID: %d, UID: %d). Nowy kolor: %d., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), CarInfo(vehid)(cColor2))

		format(string, sizeof(string), Kolor pojazdu zosta³ zmieniony. Nowy kolor: %d, color2)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil kolor pojazdu %s (UID: %d). Nowy kolor: %d., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), CarInfo(vehid)(cColor2))
		return 1
	)
	if(!strcmp(type, paliwo, true))
	(
		vehid, Float:fuel
		if(sscanf(varchar, df, vehid, fuel))
		(
		 	hrp_Tip(playerid, /apojazd paliwo (ID pojazdu) (Litry))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(fuel ) GetVehicleMaxFuel(CarInfo(vehid)(cModel)))
		(
			format(string, sizeof(string), Nie mo¿esz ustaliæ wiêcej paliwa ni¿ zmieœci siê w baku.\nPojemnoœæ baku wynosi: %d litry/ów., GetVehicleMaxFuel(CarInfo(vehid)(cModel)))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
			return 1
		)
		CarInfo(vehid)(cFuel) = fuel
		SaveVehicle(vehid, SAVE_VEH_COUNT)
		
		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil ilosc paliwa pojazdu %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		
		format(string, sizeof(string), Ustalono %.0f litry/ów paliwa w pojeŸdzie %s., fuel, CarInfo(vehid)(cName))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil ilosc paliwa w pojezdzie %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, hp, true))
	(
		vehid, Float:health
 		if(sscanf(varchar, df, vehid, health))
		(
			hrp_Tip(playerid, /apojazd hp (ID pojazdu) (HP))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(health ( 0 || health ) 1000)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, HP pojazdu nie mo¿e byæ mniejsze ni¿ 0 oraz wiêksze od 1000., OK, )
			return 1
		)
	 	CarInfo(vehid)(cHealth) = health
	  	SetVehicleHealth(vehid, health)
	  	
	   	SaveVehicle(vehid, SAVE_VEH_COUNT)
	   	
		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil ilosc HP pojazdu %s (SampID: %d, UID: %d). Nowy stan HP: %.0f., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), CarInfo(vehid)(cHealth))
	   	
		format(string, sizeof(string), Stan techniczny pojazdu zosta³ zmieniony.\nHP pojazdu wynosi teraz: %.0f HP., CarInfo(vehid)(cHealth))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil hp pojazdu %s (UID: %d). Nowy stan HP: %.0f., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), CarInfo(vehid)(cHealth))
		return 1
	)
	if(!strcmp(type, zaparkuj, true))
	(
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd zaparkuj (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		vehuid = CarInfo(vehid)(cUID)
		
		GetVehiclePos(vehid, CarInfo(vehid)(cPosX), CarInfo(vehid)(cPosY), CarInfo(vehid)(cPosZ))
		GetVehiclePos(vehid, CarInfo(vehid)(cEPosX), CarInfo(vehid)(cEPosY), CarInfo(vehid)(cEPosZ))
		GetVehicleZAngle(vehid, CarInfo(vehid)(cPosA))
		
		CarInfo(vehid)(cInteriorID) = GetPlayerInterior(playerid)
		CarInfo(vehid)(cWorldID) = GetPlayerVirtualWorld(playerid)
		
		SaveVehicle(vehid, SAVE_VEH_POS)

		ShowAdminLog(~r~(edit) ~w~Administrator %s przeparkowal pojazd %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))

		UnspawnVehicle(vehuid)
		SpawnVehicle(vehuid)

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Pojazd zosta³ zaparkowany w miejscu, na którym w³aœnie stoi., OK, )

		hrp_AdminActionLog(%s (UID: %d) przeparkowal pojazd %s (UID: %d) (PosX: %.3f, PosY: %.3f, PosZ: %.3f)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), CarInfo(vehid)(cPosX), CarInfo(vehid)(cPosY), CarInfo(vehid)(cPosZ))
		return 1
	)
	if(!strcmp(type, zamknij, true))
	(
 		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd zamknij (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(CarInfo(vehid)(cLocked))
		(
	 		format(string, sizeof(string), Pojazd %s (SampID: %d, UID: %d) zosta³ otwarty., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		
  			CarInfo(vehid)(cLocked) = false
			SetVehicleLock(vehid, false)
		)
		else
		(
			format(string, sizeof(string), Pojazd %s (SampID: %d, UID: %d) zosta³ zamkniêty., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		
  			CarInfo(vehid)(cLocked) = true
			SetVehicleLock(vehid, true)
		)
		SaveVehicle(vehid, SAVE_VEH_LOCK)
		return 1
	)
	if(!strcmp(type, res, true))
	(
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd res (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
	 	SetVehicleToRespawn(vehid)
	 	
		ShowAdminLog(~r~(edit) ~w~Administrator %s przywrocil pojazd %s (SampID: %d, UID: %d) na miejsce spawnu., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
	 	
	  	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie,Pojazd zosta³ przywrócony na miejsce spawnu., OK, )

		hrp_AdminActionLog(%s (UID: %d) przywrocil pojazd %s (UID: %d) na miejsce spawnu., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, przebieg, true))
	(
		vehid, Float:mileage
		if(sscanf(varchar, df, vehid, mileage))
		(
			hrp_Tip(playerid, /apojazd przebieg (ID pojazdu) (Przebieg))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		CarInfo(vehid)(cMileage) = mileage
		SaveVehicle(vehid, SAVE_VEH_COUNT)
		
   		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil przebieg pojazdu %s (SampID: %d, UID: %d). Nowy przebieg: %.0f., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), CarInfo(vehid)(cMileage))
		
		format(string, sizeof(string), Zmieniono przebieg pojazdu %s (SampID: %d, UID: %d).\nUstalono przebieg: %.0f km, CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), mileage)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil przebieg pojazdu %s (UID: %d). Nowy przebieg: %.0f., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), CarInfo(vehid)(cMileage))
		return 1
	)
	if(!strcmp(type, usun, true))
	(
		vehid
 		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd usun (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
   		ShowAdminLog(~r~(delete) ~w~Administrator %s usunal pojazd %s (SampID: %d, UID: %d) z bazy., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		hrp_AdminActionLog(%s (UID: %d) usunal pojazd %s (UID: %d) z bazy danych., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		
	 	DeleteVehicle(vehid)
		
	  	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Pojazd zosta³ pomyœlnie usuniêty z bazy danych., OK, )
		return 1
	)
	if(!strcmp(type, visual, true))
	(
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd visual (ID pojazdu))
			return 1
		)
   		if(CarInfo(vehid)(cUID) == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		UpdateVehicleDamageStatus(vehid, 0, 0, 0, 0)
		GetVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))

		ShowAdminLog(~r~(edit) ~w~Administrator %s naprawil wyglad wizualny pojazdu %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))

		SaveVehicle(vehid, SAVE_VEH_ACCESS)
		
		hrp_AdminActionLog(%s (UID: %d) naprawil wyglad wizualny pojazdu %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, id, true))
	(
		vehid = GetClosestVehicle(playerid)
   		if(!vehid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnego pojazdu w pobli¿u., OK, )
			return 1
		)
		format(string, sizeof(string), Najbli¿szy pojazd to \%s\ (SampID: %d)., CarInfo(vehid)(cName), vehid)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, przypisz, true))
	(
		vehid, owner_type(24), varchar2(24)
		if(sscanf(varchar, ds(24)S()(24), vehid, owner_type, varchar2))
		(
			hrp_Tip(playerid, /apojazd przypisz (ID pojazdu) (Typ (gracz, grupa, uid)))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(CarInfo(vehid)(cBlocked))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd jest pojazdem profilowym - nie mo¿esz go przypisaæ., OK, )
			return 1
		)
		if(!strcmp(owner_type, gracz, true))
		(
			giveplayer_id
			if(sscanf(varchar2, d, giveplayer_id))
			(
				format(string, sizeof(string), /apojazd przypisz %d gracz (ID gracza), vehid)
				hrp_Tip(playerid, string)
				return 1
			)
			if(giveplayer_id == INVALID_PLAYER_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
				return 1
			)
			if(!Logged(giveplayer_id))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
				return 1
			)
			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
			(
				getplayerid = GetPlayerID(CarInfo(vehid)(cOwner))
				if(getplayerid != INVALID_PLAYER_ID && Logged(getplayerid))
				(
					PlayerCache(getplayerid)(pCarSpawned) --
				)
			)
			CarInfo(vehid)(cOwnerType) = OWNER_PLAYER
			CarInfo(vehid)(cOwner) = PlayerCache(giveplayer_id)(pUID)

			SaveVehicle(vehid, SAVE_VEH_THINGS)
			
			if(!PlayerCache(giveplayer_id)(pPremium))
			(
				if(PlayerCache(giveplayer_id)(pCarSpawned) )= 1)
				(
					UnspawnVehicle(CarInfo(vehid)(cUID))
				)
				else
				(
					PlayerCache(giveplayer_id)(pCarSpawned) ++
				)
			)
			else
			(
				if(PlayerCache(giveplayer_id)(pCarSpawned) )= 3)
				(
					UnspawnVehicle(CarInfo(vehid)(cUID))
				)
				else
				(
					PlayerCache(giveplayer_id)(pCarSpawned) ++
				)
			)
			format(string, sizeof(string), Pojazd %s (SampID: %d, UID: %d) zosta³ przypisany pomyœlnie.\n\nTyp w³aœciciela: gracz\nW³aœciciel: %s (ID: %d, UID: %d), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), PlayerName(giveplayer_id), giveplayer_id, PlayerCache(giveplayer_id)(pUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

			ShowAdminLog(~r~(edit) ~w~Administrator %s przypisal pojazd %s (SampID: %d, UID: %d) pod gracza., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
			hrp_AdminActionLog(%s (UID: %d) przypisal pojazd %s (UID: %d) pod gracza %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(giveplayer_id), PlayerCache(giveplayer_id)(pUID))
			return 1
		)
		if(!strcmp(owner_type, grupa, true))
		(
			group_uid
			if(sscanf(varchar2, d, group_uid))
			(
				format(string, sizeof(string), /apojazd przypisz %d grupa (UID grupy), vehid)
				hrp_Tip(playerid, string)
				return 1
			)
			group_id_fix = GetGroupID(group_uid)
 			if(group_id_fix == INVALID_GROUP_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
				return 1
			)
   			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
			(
				getplayerid = GetPlayerID(CarInfo(vehid)(cOwner))
				if(getplayerid != INVALID_PLAYER_ID && Logged(getplayerid))
				(
					PlayerCache(getplayerid)(pCarSpawned) --
				)
			)
			CarInfo(vehid)(cOwnerType) = OWNER_GROUP
			CarInfo(vehid)(cOwner) = GroupData(group_id_fix)(gUID)
			
			SaveVehicle(vehid, SAVE_VEH_THINGS)
			
			format(string, sizeof(string), Pojazd %s (SampID: %d, UID: %d) zosta³ przypisany pomyœlnie.\n\nTyp w³aœciciela: grupa\nW³aœciciel: %s (UID: %d), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

			ShowAdminLog(~r~(edit) ~w~Administrator %s przypisal pojazd %s (SampID: %d, UID: %d) pod grupe., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
			hrp_AdminActionLog(%s (UID: %d) przypisal pojazd %s (UID: %d) pod grupe %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			return 1
		)
		if(!strcmp(owner_type, uid, true))
		(
			p_uid
			if(sscanf(varchar2, d, p_uid))
			(
				format(string, sizeof(string), /apojazd przypisz %d uid (UID gracza), vehid)
				hrp_Tip(playerid, string)
				return 1
			)
   			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
			(
				getplayerid = GetPlayerID(CarInfo(vehid)(cOwner))
				if(getplayerid != INVALID_PLAYER_ID && Logged(getplayerid))
				(
					PlayerCache(getplayerid)(pCarSpawned) --
				)
			)
			CarInfo(vehid)(cOwnerType) = OWNER_PLAYER
			CarInfo(vehid)(cOwner) = p_uid

			SaveVehicle(vehid, SAVE_VEH_THINGS)

			format(string, sizeof(string), Pojazd %s (SampID: %d, UID: %d) zosta³ przypisany pomyœlnie.\n\nTyp w³aœciciela: gracz\nW³aœciciel: UID %d, CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID), p_uid)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

			ShowAdminLog(~r~(edit) ~w~Administrator %s przypisal pojazd %s (SampID: %d, UID: %d) pod gracza., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
			hrp_AdminActionLog(%s (UID: %d) przypisal pojazd %s (UID: %d) pod gracza UID: %d., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID), p_uid)
			return 1
		)
		return 1
	)
	if(!strcmp(type, info, true))
	(
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd info (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		ShowPlayerVehicleInfo(playerid, vehid)
		return 1
	)
	if(!strcmp(type, unspawn, true))
	(
 		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd unspawn (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
   		ShowAdminLog(~r~(edit) ~w~Administrator %s odspawnowal pojazd %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		hrp_AdminActionLog(%s (UID: %d) odspawnowal pojazd %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		
		UnspawnVehicle(CarInfo(vehid)(cUID))
		
		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
		(
			giveplayer_id = GetPlayerID(CarInfo(vehid)(cOwner))
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
		
	 	format(string, sizeof(string), Pojazd %s (UID: %d) zosta³ odspawnowany pomyœlnie., CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
	 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		return 1
	)
	if(!strcmp(type, spawn, true))
	(
		vehuid
		if(sscanf(varchar, d, vehuid))
		(
			hrp_Tip(playerid, /apojazd spawn (UID pojazdu))
			return 1
		)
		vehid = GetVehicleID(vehuid)
		if(vehid != INVALID_VEHICLE_ID)
		(
			format(string, sizeof(string), Ten pojazd jest ju¿ zespawnowany (SampID: %d, UID: %d)., vehid, vehuid)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
			return 1
		)
		SpawnVehicle(vehuid)
		
		vehid = GetVehicleID(vehuid)
		
		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
		(
			giveplayer_id = GetPlayerID(CarInfo(vehid)(cOwner))
			if(giveplayer_id == INVALID_PLAYER_ID)
			(
				return 1
			)
			if(!Logged(giveplayer_id))
			(
				return 1
			)
			PlayerCache(giveplayer_id)(pCarSpawned) ++
		)
		
	 	format(string, sizeof(string), Pojazd (UID: %d) zosta³ zespawnowany pomyœlnie., vehuid)
	 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(edit) ~w~Administrator %s zespawnowal pojazd %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		hrp_AdminActionLog(%s (UID: %d) zespawnowal pojazd %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, resall, true))
	(
		foreach(Vehicles, vehid)
		(
			if(!IsAnyPlayerInVehicle(vehid))
			(
				SetVehicleToRespawn(vehid)
				UpdateVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Wszystkie nieu¿ywane pojazdy zosta³y przywrócone na miejsce spawnu., OK, )

		ShowAdminLog(~r~(edit) ~w~Administrator %s przywrocil wszystkie nieuzywane pojazdy na miejsce spawnu., PlayerName(playerid))
		hrp_AdminActionLog(%s (UID: %d) przywrocil wszystkie nieuzywane pojazdy na miejsce spawnu., PlayerName(playerid), PlayerCache(playerid)(pUID))
		return 1
	)
	if(!strcmp(type, goto, true))
	(
 		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd goto (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby móc przeteleportowaæ siê do pojazdu, nie mo¿esz siedzieæ w innym., OK, )
			return 1
		)
		virtual_world = GetVehicleVirtualWorld(vehid)
		
		PutPlayerInVehicle(playerid, vehid, 0)
		SetPlayerVirtualWorld(playerid, virtual_world)
		
		SetPlayerInterior(playerid, CarInfo(vehid)(cInteriorID))
		PlayerCache(playerid)(pLastVeh) = vehid
		
		format(string, sizeof(string), Zosta³eœ przeteleportowany do pojazdu %s (SampID: %d, UID: %d)., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(teleport) ~w~Administrator %s przeteleportowal sie do pojazdu %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		hrp_AdminActionLog(%s (UID: %d) przeteleportowal sie do pojazdu %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, gethere, true))
	(
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd gethere (ID pojazdu))
			return 1
		)
		if(!CarInfo(vehid)(cSpawned))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ,
			interior_id, virtual_world
			
		GetPlayerPos(playerid, PosX, PosY, PosZ)
		
		interior_id = GetPlayerInterior(playerid)
		virtual_world = GetPlayerVirtualWorld(playerid)
		
		SetVehiclePos(vehid, PosX + 3.0, PosY, PosZ)
		
		LinkVehicleToInterior(vehid, interior_id)
		SetVehicleVirtualWorld(vehid, virtual_world)
		return 1
	)
	if(!strcmp(type, fix, true))
	(
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd fix (ID pojazdu))
			return 1
		)
   		if(CarInfo(vehid)(cUID) == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		UpdateVehicleDamageStatus(vehid, 0, 0, 0, 0)
		GetVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))

	 	CarInfo(vehid)(cHealth) = 1000.0
	  	SetVehicleHealth(vehid, 1000.0)

	   	SaveVehicle(vehid, SAVE_VEH_COUNT)
		SaveVehicle(vehid, SAVE_VEH_ACCESS)

		format(string, sizeof(string), Pojazd %s (UID: %d) zosta³ ca³kowicie naprawiony., CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(edit) ~w~Administrator %s naprawil calkowicie pojazd %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		hrp_AdminActionLog(%s (UID: %d) naprawil calkowicie pojazd %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	if(!strcmp(type, resrange, true))
	(
		Float:PosX, Float:PosY, Float:PosZ, radius
		if(sscanf(varchar, d, radius))
		(
			hrp_Tip(playerid, /apojazd resrange (odleg³oœæ))
			return 1
		)
		
		GetPlayerPos(playerid, PosX, PosY, PosZ)
		
		foreach(Vehicles, vehid)
		(
			if(IsVehicleInRange(vehid, PosX, PosY, PosZ, radius))
			(
				if(!IsAnyPlayerInVehicle(vehid))
				(
	  				SetVehicleToRespawn(vehid)
			 		UpdateVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))
				)
			)
		)
		format(string, sizeof(string), Pojazdy w obrêbie %d metrów zosta³y przywrócone na miejsce spawnu., radius)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(edit) ~w~Administrator %s przywrocil pojazdy w obrebie %d metrow na miejsce spawnu., PlayerName(playerid), radius)
		hrp_AdminActionLog(%s (UID: %d) przywrocil pojazdy w obrebie %d metrow na miejsce spawnu., PlayerName(playerid), PlayerCache(playerid)(pUID), radius)
		return 1
	)
	if(!strcmp(type, silnik, true))
	(
		vehid
		if(sscanf(varchar, d, vehid))
		(
			hrp_Tip(playerid, /apojazd silnik (ID pojazdu))
			return 1
		)
   		if(CarInfo(vehid)(cUID) == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID pojazdu.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		
		if(CarInfo(vehid)(cEngineTogged))
		(
			CarInfo(vehid)(cEngineTogged) = false
			ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))

			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~w~Silnik wylaczony., 3000, 3)
		)
		else
		(
			CarInfo(vehid)(cEngineTogged) = true
			ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))

			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~w~Jazda!, 3000, 3)
		)
		
		ShowAdminLog(~r~(edit) ~w~Administrator %s odpalil pojazd %s (SampID: %d, UID: %d)., PlayerName(playerid), CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		hrp_AdminActionLog(%s (UID: %d) odpalil pojazd %s (UID: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		return 1
	)
	return 1
)

CMD:av(playerid, params()) return cmd_apojazd(playerid, params)

CMD:adrzwi(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(64), string(128)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /adrzwi (stworz | wyjscie | wejscie | entervw | exitvw | pickup | usun | unrob))
		hrp_Tip(playerid, /adrzwi (nazwa | przypisz | zamknij | interior | goto | lista | sampid | info))
		hrp_Tip(playerid, /adrzwi (block | limit | sprzedaz | przejazd | paintball))
		return 1
	)
	if(!strcmp(type, paintball, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi paintball (ID Drzwi))
			return 1
		)
		
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Te drzwi nie sa przypisane pod typ grupy.\n, OK, )
			return 1
		)
		group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
		if(GroupData(group_id_fix)(gType) != GROUP_PAINTBALL)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Te drzwi nie sa przypisane na grupe PAINTBALL., OK, )
			return 1
		)
		if(!DoorData(doorid)(dPaintball))
		(
			DoorData(doorid)(dPaintball) = true
			SaveDoor(doorid, SAVE_DOOR_PAINTBALL)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Opcje drzwi » Paintball, Te drzwi zostaly ustalone jako hala do gry w paintball., OK, )
		)
		else
		(
			DoorData(doorid)(dPaintball) = false
			SaveDoor(doorid, SAVE_DOOR_PAINTBALL)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Opcje drzwi » Paintball, Te drzwi nie sa juz hala do gry w paintballa., OK, )
		)
	)
	if(!strcmp(type, przejazd, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi przejazd (ID Drzwi))
			return 1
		)
		
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		
		if(!DoorData(doorid)(dGarage))
		(
			DoorData(doorid)(dGarage) = true
			SaveDoor(doorid, SAVE_DOOR_THINGS)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Opcje drzwi » Mozlioœæ przejazdu, Mo¿liwoœæ przejazdu samochodem przez drzwi zosta³a w³¹czona.\n\nOd tej pory bêdziesz móg³ wjechaæ dowolnym pojazdem do budynku.\nAby wjechaæ pojazdem do budynku skorzystaj z komendy /przejazd., OK, )
		)
		else
		(
			DoorData(doorid)(dGarage) = false
			SaveDoor(doorid, SAVE_DOOR_THINGS)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Opcje drzwi » Mozlioœæ przejazdu, Mo¿liwoœæ przejazdu samochodem przez drzwi zosta³a wy³¹czona., OK, )
		)
	)
	if(!strcmp(type, sprzedaz, true))
	(
		doorid, cost
		if(sscanf(varchar, dd, doorid, cost))
		(
			hrp_Tip(playerid, /adrzwi sprzedaz (ID Drzwi) (Cena))
			return 1
		)
		
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		
		if(cost (= 0)
		(
			GuiMsg(playerid, Cena nie mo¿e byæ mniejsza ani równa zeru., 0)
			return 1
		)
		
		DoorData(doorid)(dCost) = cost
		DoorData(doorid)(dOwnerType) = OWNER_NONE
		DoorData(doorid)(dOwner) = 0
		
		SaveDoor(doorid, SAVE_DOOR_THINGS)
		
		msg(256)
		format(msg, sizeof(msg), Ustali³eœ cenê drzwi %s na $%d!, DoorData(doorid)(dName), DoorData(doorid)(dCost))
		GuiMsg(playerid, msg, 0)
		
		// Dodaæ do defaults
		format(msg, sizeof(msg), SELECT * FROM hrp_door_defaults WHERE default_dooruid = %d, DoorData(doorid)(dUID))
		mysql_query(msg)
		mysql_store_result()
		if(mysql_num_rows() ) 0)
		(
			mysql_free_result()
			mysql_query_format(UPDATE hrp_door_defaults SET default_doorcost = %d WHERE default_dooruid = %d, cost, DoorData(doorid)(dUID))
		)
		else
		(
			mysql_free_result()
			mysql_query_format(INSERT INTO hrp_door_defaults VALUES(NULL, %d, %d, %s, %d), DoorData(doorid)(dUID), cost, DoorData(doorid)(dName), gettime() + 2592000)
		)
	)
	if(!strcmp(type, limit, true))
	(
		doorid,limit
		if(sscanf(varchar,dd,doorid,limit))
		(
			hrp_Tip(playerid,/adrzwi limit (ID drzwi) (Limit obiektow))
			return 1
		)
		
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		
		if(limit ( 0)
		(
			GuiMsg(playerid,Wprowadzono nieprawid³ow¹ liczbê.,1)
			return 1
		)
		
		DoorData(doorid)(dLimit) = limit
		SaveDoor(doorid, SAVE_DOOR_LIMITS)
		
		msg(256)
		format(msg,sizeof(msg),Zmieni³eœ limit obiektów dla drzwi %s (UID: %d)\nNowy limit wynosi: %d obiektów.,DoorData(doorid)(dName),DoorData(doorid)(dUID),limit)
		GuiMsg(playerid,msg,0)
		
		ShowAdminLog(~r~(create) ~w~Administrator %s ustawil limit obiektow drzwi %s (SampID: %d, UID: %d) Limit: %d., PlayerName(playerid),DoorData(doorid)(dName),doorid,DoorData(doorid)(dUID),limit)
	)
	if(!strcmp(type, block, true))
	(
		doorid
		if(sscanf(varchar,d,doorid))
		(
			hrp_Tip(playerid,/adrzwi block (ID drzwi))
			return 1
		)
		
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		
		doorMsg(256)
		if(DoorData(doorid)(dBlocked))
		(
			DoorData(doorid)(dBlocked) = false
			format(doorMsg,sizeof(doorMsg),Odblokowa³eœ mo¿liwoœæ tworzenia obiektów dla drzwi %s (UID:%i),DoorData(doorid)(dName),DoorData(doorid)(dUID))
			
			ShowAdminLog(~r~(create) ~w~Administrator %s odblokowal drzwi %s (SampID: %d, UID: %d)., PlayerName(playerid),DoorData(doorid)(dName),doorid,DoorData(doorid)(dUID))
		)
		else
		(
			DoorData(doorid)(dBlocked) = true
			format(doorMsg,sizeof(doorMsg),Zablokowa³eœ mo¿liwoœæ tworzenia obiektów dla drzwi %s (UID:%i),DoorData(doorid)(dName),DoorData(doorid)(dUID))
			
			ShowAdminLog(~r~(create) ~w~Administrator %s zablokowal drzwi %s (SampID: %d, UID: %d)., PlayerName(playerid),DoorData(doorid)(dName),doorid,DoorData(doorid)(dUID))
		)
		
		GuiMsg(playerid,doorMsg,0)
		SaveDoor(doorid, SAVE_DOOR_LIMITS)
	)
	if(!strcmp(type, stworz, true))
	(
		door_name(32)
		if(sscanf(varchar, s(32), door_name))
		(
			hrp_Tip(playerid, /adrzwi stworz (Nazwa drzwi))
			return 1
		)
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby stworzyæ drzwi, musisz byæ w pozycji stoj¹cej., OK, )
			return 1
		)
   		Float:EnterX, Float:EnterY, Float:EnterZ, Float:EnterA
   		
		GetPlayerPos(playerid, EnterX, EnterY, EnterZ)
		GetPlayerFacingAngle(playerid, EnterA)
		
		interior = GetPlayerInterior(playerid), virtual_world = GetPlayerVirtualWorld(playerid)
		
		gameid = CreateDoor(EnterX, EnterY, EnterZ, EnterA, interior, virtual_world, door_name)
		
		format(string, sizeof(string), Drzwi zosta³y stworzone pomyœlnie %s (SampID: %d)., door_name, gameid)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		
		// Ustawianie automatycznie exitVW
		DoorData(gameid)(dExitVW) = DoorData(gameid)(dUID)
		SaveDoor(gameid, SAVE_DOOR_EXIT)

		ShowAdminLog(~r~(create) ~w~Administrator %s stworzyl drzwi %s (SampID: %d, UID: %d)., PlayerName(playerid), door_name, gameid, DoorData(gameid)(dName))
		return 1
	)
	if(!strcmp(type, wyjscie, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi wyjscie (ID drzwi))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		GetPlayerPos(playerid, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ))
		GetPlayerFacingAngle(playerid, DoorData(doorid)(dExitAng))
		
		DoorData(doorid)(dExitInt) = GetPlayerInterior(playerid)
		SaveDoor(doorid, SAVE_DOOR_EXIT)
		
		format(string, sizeof(string), Pozycja wyjœcia dla drzwi %s (SampID: %d, UID: %d) zosta³a ustalona., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil pozycje wyjscia z drzwi %s (SampID: %d, UID: %d)., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		return 1
	)
	if(!strcmp(type, wejscie, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi wejscie (ID drzwi))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		GetPlayerPos(playerid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ))
		GetPlayerFacingAngle(playerid, DoorData(doorid)(dEnterAng))

		DoorData(doorid)(dEnterInt) = GetPlayerInterior(playerid)
		SaveDoor(doorid, SAVE_DOOR_ENTER)
		
		DestroyPickup(doorid)
		CreatePickup(DoorData(doorid)(dPickupID), 2, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), DoorData(doorid)(dEnterVW))

		format(string, sizeof(string), Pozycja wejœcia dla drzwi %s (SampID: %d, UID: %d) zosta³a ustalona., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil pozycje wejscia do drzwi %s (SampID: %d, UID: %d)., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		return 1
	)
	if(!strcmp(type, exitvw, true))
	(
		doorid, exitvw
		if(sscanf(varchar, dd, doorid, exitvw))
		(
			hrp_Tip(playerid, /adrzwi exitvw (ID drzwi) (VirtualWorld))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		DoorData(doorid)(dExitVW) = exitvw
		SaveDoor(doorid, SAVE_DOOR_EXIT)
		
		format(string, sizeof(string), VirtualWorld wyjœcia dla drzwi %s (SampID: %d, UID: %d) zosta³ ustalony (VW: %d)., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), exitvw)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil virtual world wyjsciowy w drzwiach %s (SampID: %d, UID: %d)., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		return 1
	)
	if(!strcmp(type, entervw, true))
	(
		doorid, entervw
		if(sscanf(varchar, dd, doorid, entervw))
		(
			hrp_Tip(playerid, /adrzwi entervw (ID drzwi) (VirtualWorld))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		DoorData(doorid)(dEnterVW) = entervw
		SaveDoor(doorid, SAVE_DOOR_ENTER)

		format(string, sizeof(string), VirtualWorld wyjœcia dla drzwi %s (SampID: %d, UID: %d) zosta³ ustalony (VW: %d)., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), entervw)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil virtual world wejsciowy w drzwiach %s (SampID: %d, UID: %d)., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		return 1
	)
	if(!strcmp(type, pickup, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi pickup (ID drzwi))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		ChangePickup(playerid) = doorid
		
		format(string, sizeof(string), %s (SampID: %d, UID: %d) » Pickup, DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		ShowPlayerDialog(playerid, D_CHANGE_PICKUP, DIALOG_STYLE_LIST, string, 1. Informacja\n2. Banknot\n3. Zielony domek\n4. Niebieski domek\n5. Serduszko\n6. Gwiazdka\n7. Dyskietka\n8. Koszulka\n9. Bia³a strza³ka\n10. Tabliczka FOR SALE\n11. Czerwony domek\n12. Pomarañczowy domek\n13. ¯ó³ty domek, Wybierz, Anuluj)
		return 1
	)
	if(!strcmp(type, usun, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi usun (ID drzwi))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		ShowAdminLog(~r~(edit) ~w~Administrator %s usunal drzwi %s (SampID: %d, UID: %d) z bazy., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		
		DeleteDoor(doorid)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Drzwi zosta³y pomyœlnie usuniête z bazy danych., OK, )
		return 1
	)
	if(!strcmp(type, nazwa, true))
	(
		doorid, door_name(32)
		if(sscanf(varchar, ds(32), doorid, door_name))
		(
			hrp_Tip(playerid, /adrzwi nazwa (ID drzwi) (Nowa nazwa))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		format(string, sizeof(string), Nazwa dla drzwi %s (SampID: %d, UID: %d) zosta³a zmieniona pomyœlnie.\nNowa nazwa: %s., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), door_name)
		ShowAdminLog(~r~(edit) ~w~Administrator %s zmienil nazwe drzwi %s (SampID: %d, UID: %d). Nowa nazwa: %s., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), door_name)

		strmid(DoorData(doorid)(dName), door_name, 0, strlen(door_name), 32)
		
		SaveDoor(doorid, SAVE_DOOR_THINGS)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		return 1
	)
	if(!strcmp(type, przypisz, true))
	(
		doorid, owner_type(24), varchar2(24)
		if(sscanf(varchar, ds(24)S()(24), doorid, owner_type, varchar2))
		(
			hrp_Tip(playerid, /adrzwi przypisz (ID drzwi) (Typ (gracz, grupa, uid)))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		if(!strcmp(owner_type, gracz, true))
		(
			giveplayer_id
			if(sscanf(varchar2, d, giveplayer_id))
			(
				format(string, sizeof(string), /adrzwi przypisz %d gracz (ID gracza), doorid)
				hrp_Tip(playerid, string)
				return 1
			)
			if(giveplayer_id == INVALID_PLAYER_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
				return 1
			)
			if(!Logged(giveplayer_id))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
				return 1
			)

			if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
			(
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pHouse) == DoorData(doorid)(dUID))
						(
							PlayerCache(i)(pHouse) = 0
						)
					)
				)
				
				mysql_query_format(UPDATE hrp_characters SET char_house = 0 WHERE char_house = %d, DoorData(doorid)(dUID))
			)
			
			PlayerCache(giveplayer_id)(pHouse) = DoorData(doorid)(dUID)
			
			DoorData(doorid)(dCost) = 0
			DoorData(doorid)(dOwnerType) = OWNER_PLAYER
			DoorData(doorid)(dOwner) = PlayerCache(giveplayer_id)(pUID)
			
			SaveDoor(doorid, SAVE_DOOR_THINGS)
			
			format(string, sizeof(string), Drzwi %s (SampID: %d, UID: %d) zosta³y przypisane pomyœlnie.\n\nTyp w³aœciciela: gracz\nW³aœciciel: %s (ID: %d, UID: %d), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), PlayerName(giveplayer_id), giveplayer_id, PlayerCache(giveplayer_id)(pUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

			ShowAdminLog(~r~(edit) ~w~Administrator %s przypisal drzwi %s (SampID: %d, UID: %d) pod gracza., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
			return 1
		)
		if(!strcmp(owner_type, grupa, true))
		(
			group_uid
			if(sscanf(varchar2, d, group_uid))
			(
				format(string, sizeof(string), /adrzwi przypisz %d grupa (UID grupy), doorid)
				hrp_Tip(playerid, string)
				return 1
			)
			group_id_fix = GetGroupID(group_uid)
  			if(group_id_fix == INVALID_GROUP_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
				return 1
			)
			
   			if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
			(
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pHouse) == DoorData(doorid)(dUID))
						(
							PlayerCache(i)(pHouse) = 0
						)
					)
				)

				mysql_query_format(UPDATE hrp_characters SET char_house = 0 WHERE char_house = %d, DoorData(doorid)(dUID))
			)
			
			DoorData(doorid)(dCost) = 0
			DoorData(doorid)(dOwnerType) = OWNER_GROUP
			DoorData(doorid)(dOwner) = GroupData(group_id_fix)(gUID)
			
			SaveDoor(doorid, SAVE_DOOR_THINGS)
			
   			format(string, sizeof(string), Drzwi %s (SampID: %d, UID: %d) zosta³y przypisane pomyœlnie.\n\nTyp w³aœciciela: grupa\nW³aœciciel: %s (UID: %d), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

			ShowAdminLog(~r~(edit) ~w~Administrator %s przypisal drzwi %s (SampID: %d, UID: %d) pod grupa., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
			return 1
		)
		if(!strcmp(owner_type, uid, true))
		(
			p_uid
			if(sscanf(varchar2, d, p_uid))
			(
				format(string, sizeof(string), /adrzwi przypisz %d uid (UID gracza), doorid)
				hrp_Tip(playerid, string)
				return 1
			)
			
   			if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
			(
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerCache(i)(pHouse) == DoorData(doorid)(dUID))
						(
							PlayerCache(i)(pHouse) = 0
						)
					)
				)

				mysql_query_format(UPDATE hrp_characters SET char_house = 0 WHERE char_house = %d, DoorData(doorid)(dUID))
			)

			DoorData(doorid)(dCost) = 0
			DoorData(doorid)(dOwnerType) = OWNER_PLAYER
			DoorData(doorid)(dOwner) = p_uid

			SaveDoor(doorid, SAVE_DOOR_THINGS)

   			format(string, sizeof(string), Drzwi %s (SampID: %d, UID: %d) zosta³y przypisane pomyœlnie.\n\nTyp w³aœciciela: gracz\nW³aœciciel: UID %d, DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID), p_uid)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

			ShowAdminLog(~r~(edit) ~w~Administrator %s przypisal drzwi %s (SampID: %d, UID: %d) pod gracza., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
			return 1
		)
		return 1
	)
	if(!strcmp(type, otworz, true))
	(
		foreach(Doors, d)
		(
			if(DoorData(d)(dUID))
			(
				if((IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(d)(dEnterX), DoorData(d)(dEnterY), DoorData(d)(dEnterZ)) && GetPlayerVirtualWorld(playerid) == DoorData(d)(dEnterVW)) || (IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(d)(dExitX), DoorData(d)(dExitY), DoorData(d)(dExitZ)) && GetPlayerVirtualWorld(playerid) == DoorData(d)(dExitVW)))
				(
		   			DoorData(d)(dLocked) = 0
					format(string, sizeof(string), Drzwi %s (SampID: %d, UID: %d) zosta³y otwarte., DoorData(d)(dName), d, DoorData(d)(dUID))

					SaveDoor(d, SAVE_DOOR_LOCK)
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
			 		return 1
				)
			)
		)
		return 1
	)
	if(!strcmp(type, zamknij, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi zamknij (ID drzwi))
			return 1
		)
  		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		
		if(DoorData(doorid)(dLocked))
		(
			DoorData(doorid)(dLocked) = 0
			format(string, sizeof(string), Drzwi %s (SampID: %d, UID: %d) zosta³y otwarte., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		)
		else
		(
			DoorData(doorid)(dLocked) = 1
			format(string, sizeof(string), Drzwi %s (SampID: %d, UID: %d) zosta³y zamkniête., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		)
		SaveDoor(doorid, SAVE_DOOR_LOCK)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
 		return 1
	)
	if(!strcmp(type, interior, true))
	(
		interiorid
		if(sscanf(varchar, d, interiorid))
		(
			strx(3064)
			for (int = 0 int ( sizeof(Interiors) int++)
			(
				format(strx, sizeof(strx), %s\n%d\t%s, strx, int, Interiors(int)(INTERIOR_NAME))
			)
			ShowPlayerDialog(playerid, D_SELECT_INTERIOR, DIALOG_STYLE_LIST, Dostêpne interiory, strx, Wybierz, Zamknij)
			return 1
		)
		if(interiorid ) 145 || interiorid ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, B³êdne ID interioru, nie mo¿e wynieœæ wiêcej ni¿ 145 ani mniej ni¿ 0., OK, )
			return 1
		)
	 	hrp_SetPlayerPos(playerid, Interiors(interiorid)(INTERIOR_X), Interiors(interiorid)(INTERIOR_Y), Interiors(interiorid)(INTERIOR_Z))
	 	SetPlayerInterior(playerid, Interiors(interiorid)(INTERIOR_ID))
	 	
	 	SetPlayerFacingAngle(playerid, Interiors(interiorid)(INTERIOR_A))
	 	
	 	format(string, sizeof(string), Zosta³eœ pomyœlnie przeteleportowany do interioru %s (InteriorID: %d)., Interiors(interiorid)(INTERIOR_NAME), Interiors(interiorid)(INTERIOR_ID))
	  	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		return 1
	)
	if(!strcmp(type, goto, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi goto (ID drzwi))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		hrp_SetPlayerPos(playerid, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ))
		SetPlayerInterior(playerid, DoorData(doorid)(dEnterInt))
		
		SetPlayerVirtualWorld(playerid, DoorData(doorid)(dEnterVW))
		
		format(string, sizeof(string), Zosta³eœ przeteleportowany do drzwi %s (SampID: %d, UID: %d)., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		ShowAdminLog(~r~(teleport) ~w~Administrator %s przeteleportowal sie do drzwi %s (SampID: %d, UID: %d)., PlayerName(playerid), DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		return 1
	)
	if(!strcmp(type, lista, true))
	(
 		list_door(1024)
		foreach(Doors, doorid)
		(
			if(DoorData(doorid)(dUID) != 0)
			(
				format(list_door, sizeof(list_door), %s\n%d\t%s, list_door, doorid, DoorData(doorid)(dName))
			)
		)
		if(strlen(list_door) != 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Lista drzwi, list_door, OK, )
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych drzwi., OK, )
		)
		return 1
	)
	if(!strcmp(type, sampid, true))
	(
 		door_uid
		if(sscanf(varchar, d, door_uid))
		(
			hrp_Tip(playerid, /adrzwi sampid (UID drzwi))
			return 1
		)
		doorid = GetDoorID(door_uid)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID drzwi., OK, )
			return 1
		)
		format(string, sizeof(string), Znaleziono drzwi %s (SampID: %d, UID: %d)., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, info, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi info (ID drzwi))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		ShowPlayerDoorInfo(playerid, doorid)
		return 1
	)
	if(!strcmp(type, unrob, true))
	(
		doorid
		if(sscanf(varchar, d, doorid))
		(
			hrp_Tip(playerid, /adrzwi unrob (ID drzwi))
			return 1
		)
		if(!DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID drzwi.\nPodaj identyfikator ten z gry, nie z bazy danych., OK, )
			return 1
		)
		DoorData(doorid)(dRobbed) = false
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Sukces, Te drzwi mozna ponownie napadac., OK, )
		return 1
	)
	return 1
)

CMD:ad(playerid, params()) return cmd_adrzwi(playerid, params)

CMD:aprzedmiot(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(64), string(128)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /aprzedmiot (stworz | typ | nazwa | value1 | value2 | zabierz))
		return 1
	)
	if(!strcmp(type, zabierz, true))
	(
		giveplayer_id, item_uid
		if(sscanf(varchar, ud, giveplayer_id, item_uid))
		(
			hrp_Tip(playerid, /ap zabierz (ID gracza) (UID przedmiotu))
			return 1
		)
 		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zabraæ przedmiotu sobie., OK, )
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)

		itemid = GetItemID(item_uid)
		if(!ItemInfo(itemid)(iUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owe UID przedmiotu., OK, )
			return 1
		)
		if(ItemInfo(itemid)(iPlace) != PLACE_PLAYER || ItemInfo(itemid)(iOwner) != PlayerCache(giveplayer_id)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten przedmiot nie nale¿y do tego gracza., OK, )
			return 1
		)
		if(ItemInfo(itemid)(iUsed))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zabraæ tego przedmiotu, poniewa¿ jest on w u¿ytku., OK, )
			return 1
		)

		ItemInfo(itemid)(iOwner) = PlayerCache(playerid)(pUID)
		mysql_query_format(UPDATE hrp_items SET item_owner = %d WHERE item_uid = %d LIMIT 1, PlayerCache(playerid)(pUID), ItemInfo(itemid)(iUID))

		format(string, sizeof(string), Zabra³eœ przedmiot %s (SampID: %d, UID: %d) graczu %s.\nPrzedmiot pojawi³ siê w Twoim ekwipunku., ItemInfo(itemid)(iName), itemid, ItemInfo(itemid)(iUID), PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Admin %s zabra³ Ci przedmiot %s (SampID: %d, UID: %d)., PlayerName(playerid), ItemInfo(itemid)(iName), itemid, ItemInfo(itemid)(iUID))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, stworz, true))
	(
		item_name(32), item_type, item_value1, item_value2
		if(sscanf(varchar, S(32)ddd, item_name, item_type, item_value1, item_value2))
		(
			hrp_Tip(playerid, /aprzedmiot stworz (Nazwa przedmiotu) (Typ) (Value1) (Value2))
			return 1
		)
		if(item_type == ITEM_INHIBITOR || item_type == ITEM_WINDGUN)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten typ przedmiotu nie jest ju¿ u¿ywany., OK, )
			return 1
		)
		if(item_type == ITEM_CHECK)
		(
			info(64)
			format(info, sizeof(info), %s what are you doing? %s! Stahp!, PlayerName(playerid), PlayerName(playerid))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, info, OK, )
			return 1
		)
		if(item_type ( 0 || item_type ) ITEM_COUNT)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy typ przedmiotu., OK, )
			return 1
		)
		item_uid = CreatePlayerItem(playerid, item_name, item_type, item_value1, item_value2)
		
		format(string, sizeof(string), Przedmiot %s (UID: %d) zosta³ stworzony pomyœlnie.\nTyp przedmiotu: %s\n\nPrzedmiot znajdziesz w swoim ekwipunku., item_name, item_uid, ItemTypeInfo(item_type)(iTypeName))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) stworzyl przedmiot %s (UID: %d, Value1: %d, Value2: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), item_name, item_uid, item_value1, item_value2)
		return 1
	)
	if(!strcmp(type, utworz, true))
	(
		item_name(32), item_type, item_value1, item_value2
		if(sscanf(varchar, S(32)ddd, item_name, item_type, item_value1, item_value2))
		(
			hrp_Tip(playerid, /aprzedmiot utworz (Nazwa przedmiotu) (Typ) (Value1) (Value2))
			return 1
		)
		if(item_type ( 0 || item_type ) ITEM_COUNT)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy typ przedmiotu., OK, )
			return 1
		)
		item_uid = CreatePlayerItem(playerid, item_name, item_type, item_value1, item_value2)
		
		format(string, sizeof(string), Przedmiot %s (UID: %d) zosta³ stworzony pomyœlnie.\nTyp przedmiotu: %s\n\nPrzedmiot znajdziesz w swoim ekwipunku., item_name, item_uid, ItemTypeInfo(item_type)(iTypeName))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) stworzyl przedmiot %s (UID: %d, Value1: %d, Value2: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), item_name, item_uid, item_value1, item_value2)
		
		itemid = GetItemID(item_uid)
		OnPlayerDropItem(playerid, itemid, false)
		return 1
	)
	if(!strcmp(type, typ, true))
	(
		item_uid, item_type
		if(sscanf(varchar, dd, item_uid, item_type))
		(
			hrp_Tip(playerid, /aprzedmiot typ (UID przedmiotu) (Typ))
			return 1
		)
		itemid = GetItemID(item_uid)
		if(!ItemInfo(itemid)(iUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza., OK, )
			return 1
		)
		
		if(item_type == ITEM_INHIBITOR || item_type == ITEM_WINDGUN)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten typ przedmiotu nie jest ju¿ u¿ywany., OK, )
			return 1
		)

		ItemInfo(itemid)(iType) = item_type
		
		Float:weight = 1.0
		if(item_type == ITEM_WEAPON)
		(
			weight = GetWeaponWeight(ItemInfo(itemid)(iValue1))
		)
		else
		(
			weight = GetItemTypeWeight(item_type)
		)

		ItemInfo(itemid)(iWeight) = weight
		mysql_query_format(UPDATE hrp_items SET item_type = %d, item_weight = %f WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iType), ItemInfo(itemid)(iWeight), ItemInfo(itemid)(iUID))
		
		format(string, sizeof(string), Typ przedmiotu %s (SampID: %d, UID: %d) zosta³ pomyœlnie zmieniony.\nNowy typ przedmiotu: %s., ItemInfo(itemid)(iName), itemid, ItemInfo(itemid)(iUID), ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeName))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil typ przedmiotu %s (UID: %d). Nowy typ: %s, PlayerName(playerid), PlayerCache(playerid)(pUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), ItemTypeInfo(ItemInfo(itemid)(iType))(iTypeName))
		return 1
	)
	if(!strcmp(type, nazwa, true))
	(
 		item_uid, item_name(32)
		if(sscanf(varchar, ds(32), item_uid, item_name))
		(
			hrp_Tip(playerid, /aprzedmiot nazwa (UID przedmiotu) (Nazwa))
			return 1
		)
		itemid = GetItemID(item_uid)
		if(!ItemInfo(itemid)(iUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza., OK, )
			return 1
		)
		format(string, sizeof(string), Nazwa przedmiotu %s (SampID: %d, UID: %d) zosta³a pomyœlnie zmieniona.\nNowa nazwa przedmiotu: %s., ItemInfo(itemid)(iName), itemid, ItemInfo(itemid)(iUID), item_name)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil nazwe przedmiotu %s (UID: %d). Nowa nazwa: %s., PlayerName(playerid), PlayerCache(playerid)(pUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), item_name)

		strmid(ItemInfo(itemid)(iName), item_name, 0, strlen(item_name), 32)
		mysql_query_format(UPDATE hrp_items SET item_name = %s WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID))
		return 1
	)
	if(!strcmp(type, value1, true))
	(
 		item_uid, item_value1
		if(sscanf(varchar, dd, item_uid, item_value1))
		(
			hrp_Tip(playerid, /aprzedmiot value1 (UID przedmiotu) (Value 1))
			return 1
		)
		itemid = GetItemID(item_uid)
		if(!ItemInfo(itemid)(iUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza., OK, )
			return 1
		)
		ItemInfo(itemid)(iValue1) = item_value1
		mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))

		format(string, sizeof(string), Wartoœæ nr. 1 przedmiotu %s (SampID: %d, UID: %d) zosta³a pomyœlnie zmieniona.\nNowa wartoœæ nr. 1 przedmiotu: %d., ItemInfo(itemid)(iName), itemid, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iValue1))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil wartosc 1 przedmiotu %s (UID: %d). Nowa wartosc: %d., PlayerName(playerid), PlayerCache(playerid)(pUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), ItemInfo(itemid)(iValue1))
		return 1
	)
	if(!strcmp(type, value2, true))
	(
 		item_uid, item_value2
		if(sscanf(varchar, dd, item_uid, item_value2))
		(
			hrp_Tip(playerid, /aprzedmiot value2 (UID przedmiotu) (Value 2))
			return 1
		)
		itemid = GetItemID(item_uid)
		if(!ItemInfo(itemid)(iUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza., OK, )
			return 1
		)
		ItemInfo(itemid)(iValue2) = item_value2
		mysql_query_format(UPDATE hrp_items SET item_value2 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))

		format(string, sizeof(string), Wartoœæ nr. 2 przedmiotu %s (SampID: %d, UID: %d) zosta³a pomyœlnie zmieniona.\nNowa wartoœæ nr. 2 przedmiotu: %d., ItemInfo(itemid)(iName), itemid, ItemInfo(itemid)(iUID), ItemInfo(itemid)(iValue2))
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_AdminActionLog(%s (UID: %d) zmienil wartosc 2 przedmiotu %s (UID: %d). Nowa wartosc: %d., PlayerName(playerid), PlayerCache(playerid)(pUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), ItemInfo(itemid)(iValue2))
		return 1
	)
	if(!strcmp(type, info, true))
	(
		item_uid
		if(sscanf(varchar, d, item_uid))
		(
			hrp_Tip(playerid, /aprzedmiot info (UID przedmiotu))
			return 1
		)
		itemid = GetItemID(item_uid)
		if(!ItemInfo(itemid)(iUID) || itemid == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID przedmiotu.\nPamiêtaj, ¿e przedmiot musi byæ w posiadaniu gracza., OK, )
			return 1
		)
		ShowPlayerItemInfo(playerid, itemid)
		return 1
	)
	return 1
)

CMD:ap(playerid, params()) return cmd_aprzedmiot(playerid, params)

CMD:sdo(playerid, params()) 
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(	
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie masz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	range, string(256), endstring(256)
	if(sscanf(params, ds(128), range, string))
	(
		hrp_Tip(playerid, /sdo (odleg³oœæ) (Sytuacja))
		return 1
	)
	string(0) = chrtoupper(string(0))
	
	if(strlen(string) ( 78)
	(
		format(endstring, sizeof(endstring), ** %s (( %s )), string, PlayerName(playerid))
		ProxDetector(range, playerid, endstring, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
	)
	else
	(
		pos = strfind(string,  , true, strlen(string) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, string, pos + 1, strlen(string))
			strdel(string, pos, strlen(string))

			format(endstring, sizeof(endstring), ** %s..., string)
			ProxDetector(range, playerid, endstring, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)

			format(endstring, sizeof(endstring), ...%s (( %s )), text, PlayerName(playerid))
			ProxDetector(range, playerid, endstring, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
		)
	)
	return 1
)

CMD:propsuj(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	
	giveplayer_id, gamescore, reason(128), string(256)
	if(sscanf(params, uds(128), giveplayer_id, gamescore, reason))
	(
		hrp_Tip(playerid, /propsuj (ID gracza) (Iloœæ GS) (Powód))
		return 1
	)	
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(IsPlayerNPC(giveplayer_id))
	(
		GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	
	EscapePL(reason)

	mysql_query_format(INSERT INTO hrp_ribbons (rib_char, rib_admin, rib_gs, rib_time, rib_caption) VALUES(%d, %d, %d, %d, %s), PlayerCache(giveplayer_id)(pUID), PlayerCache(playerid)(pGID), gamescore, gettime(), reason)
	PlayerCache(giveplayer_id)(pGamePoints) += gamescore
	
	SetPlayerScore(giveplayer_id, PlayerCache(giveplayer_id)(pGamePoints))
	mysql_query_format(UPDATE live_users SET user_gamepoints = %d WHERE user_id = %d LIMIT 1, PlayerCache(giveplayer_id)(pGamePoints), PlayerCache(giveplayer_id)(pGID))
	
	hrp_AdminActionLog(%s (UID: %d) nadal osiagniecie (%d GS) graczowi %s (UID: %d). Powod: %s, PlayerName(playerid), PlayerCache(playerid)(pUID), gamescore, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), reason)
	
	if(gamescore ) 0)
	(
		format(string, sizeof(string), ~g~~h~Osiagniecie +%d GS ~n~~w~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, gamescore, PlayerName(giveplayer_id), PlayerName(playerid), reason)
	)
	else
	(
		format(string, sizeof(string), ~r~~h~Osiagniecie %d GS ~n~~w~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, gamescore, PlayerName(giveplayer_id), PlayerName(playerid), reason)
		
		/*foreach(Player, i)
		(
			Float:PosX, Float:PosY, Float:PosZ
			GetPlayerPos(i, PosX, PosY, PosZ)
			audio = Audio_Play(i, AUDIO_HUMILIATION)
		  	Audio_Set3DPosition(i, audio, PosX, PosY, PosZ, 10.0)
		)*/
	)
	TextDrawSetString(Text:TextDrawPunishInfo, string)
	TextDrawShowForAll(Text:TextDrawPunishInfo)
	PunishTime = 15
	
	return 1	
)

CMD:i(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /i (Tekst))
	  	return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))
	
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), (( %s: %s )), PlayerGlobalName(playerid, COLOR_WHITE), params)
		SendClientMessageToAll(COLOR_WHITE, string)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), (( %s: %s... )), PlayerGlobalName(playerid, COLOR_WHITE), params)
			SendClientMessageToAll(COLOR_WHITE, string)

			format(string, sizeof(string), (( ...%s )), text)
			SendClientMessageToAll(COLOR_WHITE, string)
		)
	)
	return 1
)

CMD:aj(playerid, params())
(
   	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, time, reason(128)
	if(sscanf(params, dds(128), giveplayer_id, time, reason))
	(
		hrp_Tip(playerid, /aj (ID gracza) (Czas (min)) (Powód))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(IsPlayerNPC(giveplayer_id))
	(
		GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	if(PlayerCache(giveplayer_id)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz jest ju¿ uwiêziony w AdminJail., OK, )
		return 1
	)
	if(PlayerCache(giveplayer_id)(pBW))
	(
		PlayerCache(giveplayer_id)(pBW) = 0
		PlayerCache(giveplayer_id)(pKiller) = 0
		PlayerCache(giveplayer_id)(pKillerWeapon) = 0

		hrp_TogglePlayerControllable(giveplayer_id, 1)
		SetCameraBehindPlayer(giveplayer_id)
		hrp_SetPlayerHealth(giveplayer_id, 20)
		return 1
	)
	reason(0) = chrtoupper(reason(0))
	hrp_AdminJail(giveplayer_id, playerid, reason, time)
	return 1
)

CMD:jail(playerid, params()) return cmd_aj(playerid, params)

CMD:unaj(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /unaj (ID gracza))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	if(!PlayerCache(giveplayer_id)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie jest uwiêziony w AdminJail., OK, )
		return 1
	)
	
	mysql_query_format(UPDATE hrp_punishlogs SET punish_end = %d WHERE punish_owneruid = %d AND punish_type = %d, gettime(), PlayerCache(giveplayer_id)(pUID), PUNISH_AJ)
	
	PlayerCache(giveplayer_id)(pAJ) = 0
	SetPlayerSpawn(giveplayer_id)
	
	format(string, sizeof(string), Gracz %s zosta³ zwolniony z kary AdminJaila., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:kick(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, reason(128)
	if(sscanf(params, ds(128), giveplayer_id, reason))
	(
		hrp_Tip(playerid, /kick (ID gracza) (Powód))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(IsPlayerNPC(giveplayer_id))
	(
		GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	reason(0) = chrtoupper(reason(0))
	hrp_Kick(giveplayer_id, playerid, reason)
	return 1
)

CMD:warn(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, days, reason(128)
	if(sscanf(params, dds(128), giveplayer_id, days, reason))
	(
		hrp_Tip(playerid, /warn (ID gracza) (Czas w dniach) (Powód))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(IsPlayerNPC(giveplayer_id))
	(
		GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	reason(0) = chrtoupper(reason(0))
	hrp_Warn(giveplayer_id, playerid, reason, days)
	return 1
)

CMD:unwarn(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /unwarn (ID gracza))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(IsPlayerNPC(giveplayer_id))
	(
		GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	if(PlayerCache(giveplayer_id)(pWarns) (= 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie ma na swoim koncie ¿adnych warnów., OK, )
		return 1
	)
	PlayerCache(giveplayer_id)(pWarns) -= 1
	mysql_query_format(UPDATE hrp_punishlogs SET punish_end = %d WHERE punish_owneruid = %d AND punish_type = %d ORDER BY punish_uid DESC LIMIT 1, gettime(), PlayerCache(giveplayer_id)(pUID), PUNISH_WARN, gettime())
	
	format(string, sizeof(string), %s zdj¹³ Ci warna. Obecny stan ostrze¿eñ: %d, PlayerName(playerid), PlayerCache(giveplayer_id)(pWarns))
	ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	
	format(string, sizeof(string), Zdj¹³eœ warna dla %s. Obecny stan ostrze¿eñ: %d, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pWarns))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:fck(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /fck (ID gracza))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	
	MainPlayerTable(playerid) = giveplayer_id
	string(128)
	format(string, sizeof(string), PotwierdŸ FCK dla gracza %s (uid: %d) (id: %d), PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), giveplayer_id)
	ShowPlayerDialog(playerid, D_FCK_CONFIRM, DIALOG_STYLE_MSGBOX, Force Character Kill, string, Tak, Nie)
	return 1
)

CMD:block(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(12), varchar(256)
	if(sscanf(params, s(12)S()(256), type, varchar))
	(
		hrp_Tip(playerid, /block (char | veh | run | ooc | obj))
		return 1
	)
	if(!strcmp(type, char, true))
	(
	   	giveplayer_id, days, reason(128)
		if(sscanf(varchar, dds(128), giveplayer_id, days, reason))
		(
			hrp_Tip(playerid, /block char (ID gracza) (Czas w dniach) (Powód))
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(IsPlayerNPC(giveplayer_id))
		(
			GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBlock) & BLOCK_CHAR)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz zosta³ ju¿ zablokowany!, OK, )
			return 1
		)
		reason(0) = chrtoupper(reason(0))
  		hrp_Block(giveplayer_id, playerid, reason, BLOCK_CHAR, days)
		return 1
	)
	if(!strcmp(type, veh, true))
	(
		giveplayer_id, days, reason(128)
		if(sscanf(varchar, dds(128), giveplayer_id, days, reason))
		(
			hrp_Tip(playerid, /block veh (ID gracza) (Czas w dniach) (Powód))
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(IsPlayerNPC(giveplayer_id))
		(
			GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBlock) & BLOCK_VEH)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma ju¿ na³o¿on¹ blokadê prowadzenia pojazdów., OK, )
			return 1
		)
		reason(0) = chrtoupper(reason(0))
		hrp_Block(giveplayer_id, playerid, reason, BLOCK_VEH, days)
		return 1
	)
	if(!strcmp(type, run, true))
	(
		giveplayer_id, days, reason(128)
		if(sscanf(varchar, dds(128), giveplayer_id, days, reason))
		(
			hrp_Tip(playerid, /block run (ID gracza) (Czas w dniach) (Powód))
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(IsPlayerNPC(giveplayer_id))
		(
			GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBlock) & BLOCK_RUN)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma ju¿ na³o¿on¹ blokadê biegania., OK, )
			return 1
		)
  		reason(0) = chrtoupper(reason(0))
		hrp_Block(giveplayer_id, playerid, reason, BLOCK_RUN, days)
		return 1
	)
	if(!strcmp(type, ooc, true))
	(
		giveplayer_id, days, reason(128)
		if(sscanf(varchar, dds(128), giveplayer_id, days, reason))
		(
			hrp_Tip(playerid, /block ooc (ID gracza) (Czas w dniach) (Powód))
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(IsPlayerNPC(giveplayer_id))
		(
			GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBlock) & BLOCK_OOC)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma ju¿ na³o¿on¹ blokadê pisania na czacie OOC., OK, )
			return 1
		)
  		reason(0) = chrtoupper(reason(0))
		hrp_Block(giveplayer_id, playerid, reason, BLOCK_OOC, days)
		return 1
	)
	if(!strcmp(type, obj, true))
	(
		giveplayer_id, days, reason(128)
		if(sscanf(varchar, dds(128), giveplayer_id, days, reason))
		(
			hrp_Tip(playerid, /block obj (ID gracza) (Czas w dniach) (Powód))
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(IsPlayerNPC(giveplayer_id))
		(
			GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBlock) & BLOCK_OBJ)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma ju¿ na³o¿on¹ blokadê edycji obiektów przyczepialnych., OK, )
			return 1
		)
  		reason(0) = chrtoupper(reason(0))
		hrp_Block(giveplayer_id, playerid, reason, BLOCK_OBJ, days)
		return 1
	)
	return 1
)

CMD:unblock(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(12), varchar(32), string(128)
	if(sscanf(params, s(12)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /unblock (veh | run | ooc | obj))
		return 1
	)
	if(!strcmp(type, veh, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /unblock veh (ID gracza))
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(!(PlayerCache(giveplayer_id)(pBlock) & BLOCK_VEH))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie ma na³o¿onej blokady prowadzenia pojazdów., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pBlock) -= BLOCK_VEH

		mysql_query_format(UPDATE hrp_punishlogs SET punish_end = %d WHERE punish_owneruid = %d AND punish_type = %d, gettime(), PlayerCache(giveplayer_id)(pUID), PUNISH_BLOCK_VEH)
		
		format(string, sizeof(string), %s zdj¹³ Ci blokadê prowadzenia pojazdów., PlayerName(playerid))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Zdj¹³eœ %s blokadê prowadzenia pojazdów., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, run, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /unblock run (ID gracza))
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(!(PlayerCache(giveplayer_id)(pBlock) & BLOCK_RUN))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie ma na³o¿onej blokady biegania i bicia., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pBlock) -= BLOCK_RUN

		mysql_query_format(UPDATE hrp_punishlogs SET punish_end = %d WHERE punish_owneruid = %d AND punish_type = %d, gettime(), PlayerCache(giveplayer_id)(pUID), PUNISH_BLOCK_RUN)
		
		format(string, sizeof(string), %s zdj¹³ Ci blokadê biegania i bicia., PlayerName(playerid))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Zdj¹³eœ %s blokadê biegania i bicia., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, ooc, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /unblock ooc (ID gracza))
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(!(PlayerCache(giveplayer_id)(pBlock) & BLOCK_OOC))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie ma na³o¿onej blokady czatu OOC., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pBlock) -= BLOCK_OOC

		mysql_query_format(UPDATE hrp_punishlogs SET punish_end = %d WHERE punish_owneruid = %d AND punish_type = %d, gettime(), PlayerCache(giveplayer_id)(pUID), PUNISH_BLOCK_OOC)

		format(string, sizeof(string), %s zdj¹³ Ci blokadê czatu OOC., PlayerName(playerid))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Zdj¹³eœ %s blokadê czatu OOC., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, obj, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /unblock obj (ID gracza))
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(!(PlayerCache(giveplayer_id)(pBlock) & BLOCK_OBJ))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie ma na³o¿onej blokady edycji obiektów., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pBlock) -= BLOCK_OBJ

		mysql_query_format(UPDATE hrp_punishlogs SET punish_end = %d WHERE punish_owneruid = %d AND punish_type = %d, gettime(), PlayerCache(giveplayer_id)(pUID), PUNISH_BLOCK_OBJ)

		format(string, sizeof(string), %s zdj¹³ Ci blokadê edycji obiektów., PlayerName(playerid))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Zdj¹³eœ %s blokadê edycji obiektów., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	return 1
)

CMD:ban(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -3 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, days, reason(128)
	if(sscanf(params, dds(128), giveplayer_id, days, reason))
	(
		hrp_Tip(playerid, /ban (ID gracza) (Czas w dniach) (Powód))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(IsPlayerNPC(giveplayer_id))
	(
		GuiMsg(playerid, Nie mo¿esz karaæ bota., 1)
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	reason(0) = chrtoupper(reason(0))
	hrp_Ban(giveplayer_id, playerid, reason, days)
	return 1
)

CMD:unban(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -3 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	IP(16), string(128)
	if(sscanf(params, s(16), IP))
	(
		hrp_Tip(playerid, /unban (Adres IP))
		return 1
	)
	
	format(string, sizeof(string), UPDATE hrp_punishlogs SET punish_end = %d WHERE punish_value = %s, getdate(), IP)
	mysql_query(string)
	
	mysql_query_format(DELETE FROM hrp_bans WHERE ban_ip = %s AND ban_type == 1, IP)

	format(string, sizeof(string), Adres IP %s zosta³ pomyœlnie odbanowany., IP)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:tp(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	Float:PosX, Float:PosY, Float:PosZ, INT, VW
	if(sscanf(params, fffdd, PosX, PosY, PosZ, INT, VW))
	(
		hrp_Tip(playerid, /tp (PosX) (PosY) (PosZ) (Int) (Vw))
		return 1
	)
	hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
	
	SetPlayerInterior(playerid, INT)
	SetPlayerVirtualWorld(playerid, VW)
	return 1
)

CMD:teleport(playerid, params()) return cmd_tp(playerid, params)

CMD:respawn(playerid, params())
(
	//if(PlayerCache(playerid)(pAdmin) == 0)
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /respawn (ID gracza))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	if(PlayerCache(giveplayer_id)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
		return 1
	)
	if(PlayerCache(giveplayer_id)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz jest uwiêziony w AdminJail., OK, )
		return 1
	)

	hrp_TogglePlayerControllable(playerid, 1)

	SetPlayerSpawn(giveplayer_id)
	SpawnPlayer(giveplayer_id)

	format(string, sizeof(string), Gracz %s (ID: %d) zosta³ pomyœlnie zrespawnowany., PlayerCache(giveplayer_id)(pName), giveplayer_id)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:res(playerid, params()) return cmd_respawn(playerid, params)

CMD:ptp(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	getplayer_id, giveplayer_id, string(128)
	if(sscanf(params, dd, getplayer_id, giveplayer_id))
	(
		hrp_Tip(playerid, /ptp (ID gracza (1)) (ID gracza (2)))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	Float:PosX, Float:PosY, Float:PosZ,
		interior_id, virtual_world
		
	GetPlayerPos(giveplayer_id, PosX, PosY, PosZ)

	interior_id = GetPlayerInterior(giveplayer_id)
	virtual_world = GetPlayerVirtualWorld(giveplayer_id)
	
	hrp_SetPlayerPos(getplayer_id, PosX, PosY, PosZ)
	
	SetPlayerInterior(getplayer_id, interior_id)
	SetPlayerVirtualWorld(getplayer_id, virtual_world)
	
	format(string, sizeof(string), Gracz %s zosta³ przeteleportowany do gracza %s pomyœlnie., PlayerName(getplayer_id), PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:burton(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	time1, time2
	if(sscanf(params, dd, time1, time2))
	(
		hrp_Tip(playerid, /burton godzina1 godzina2)
		return 1
	)
	
	SetPlayerTime(playerid, time1, time2)
	return 1
)

CMD:goto(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	//if(PlayerCache(playerid)(pAdmin) == 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /goto (ID gracza))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	Float:PosX, Float:PosY, Float:PosZ, Float:PosA
	GetPlayerPos(giveplayer_id, PosX, PosY, PosZ)
	
	interior = GetPlayerInterior(giveplayer_id)
	virtual_world = GetPlayerVirtualWorld(giveplayer_id)
	
	GetXYInFrontOfPlayer(giveplayer_id, PosX, PosY, 1.0)
	GetPlayerFacingAngle(giveplayer_id, PosA)
	hrp_SetPlayerPos(playerid, PosX, PosY, PosZ)
	SetPlayerFacingAngle(playerid, -PosA)
	
	SetPlayerInterior(playerid, interior)
	SetPlayerVirtualWorld(playerid, virtual_world)
	return 1
)

CMD:gethere(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /gethere (ID gracza))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	Float:PosX, Float:PosY, Float:PosZ, Float:PosA
	GetPlayerPos(playerid, PosX, PosY, PosZ)

	interior = GetPlayerInterior(playerid)
	virtual_world = GetPlayerVirtualWorld(playerid)

	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	GetPlayerFacingAngle(playerid, PosA)
	hrp_SetPlayerPos(giveplayer_id, PosX, PosY, PosZ)
	SetPlayerFacingAngle(giveplayer_id, -PosA)
	

	SetPlayerInterior(giveplayer_id, interior)
	SetPlayerVirtualWorld(giveplayer_id, virtual_world)
	return 1
)

CMD:spec(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		if(PlayerCache(playerid)(pSpectate) != INVALID_PLAYER_ID)
		(
			TogglePlayerSpectating(playerid, false)
			PlayerTextDrawHide(playerid, AdminSpecInfo(playerid))
			PlayerTextDrawHide(playerid, AdminSpecStats(playerid))
			return 1
		)
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz podgl¹daæ siebie., OK, )
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	if(PlayerCache(giveplayer_id)(pSpectate) != INVALID_PLAYER_ID)
	(
		giveplayer_id = PlayerCache(giveplayer_id)(pSpectate)
		//ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz podgl¹da innego gracza., OK, )
	)
	if(PlayerCache(playerid)(pSpectate) == INVALID_PLAYER_ID)
	(
		GetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))

		PlayerCache(playerid)(pVW) = GetPlayerVirtualWorld(playerid)
		PlayerCache(playerid)(pInt) = GetPlayerInterior(playerid)
	)
	
	if(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID))
	(
		itemid = GetItemID(WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID))
		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo)
		
		mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
	)
	
	if(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID))
	(
		itemid = GetItemID(WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID))
		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo)
		
		mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
	)
	
	if(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID))
	(
		itemid = GetItemID(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
		ItemInfo(itemid)(iUsed) = 0
		ItemInfo(itemid)(iValue2) = WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo)
		
		mysql_query_format(UPDATE hrp_items SET item_value2 = %d, item_used = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue2), ItemInfo(itemid)(iUID))
	)
	
	WeaponCache(playerid)(WEAPON_MAIN)(pWeaponUID) = 0
	WeaponCache(playerid)(WEAPON_MAIN)(pWeaponID) = 0
	WeaponCache(playerid)(WEAPON_MAIN)(pWeaponAmmo) = 0
	WeaponCache(playerid)(WEAPON_MAIN)(pLastAmmo) = 0
	WeaponCache(playerid)(WEAPON_MAIN)(pShot) = false
	
	WeaponCache(playerid)(WEAPON_SIDE)(pWeaponUID) = 0
	WeaponCache(playerid)(WEAPON_SIDE)(pWeaponID) = 0
	WeaponCache(playerid)(WEAPON_SIDE)(pWeaponAmmo) = 0
	WeaponCache(playerid)(WEAPON_SIDE)(pLastAmmo) = 0
	WeaponCache(playerid)(WEAPON_SIDE)(pShot) = false
	
	WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID) = 0
	WeaponCache(playerid)(WEAPON_FUNC)(pWeaponID) = 0
	WeaponCache(playerid)(WEAPON_FUNC)(pWeaponAmmo) = 0
	WeaponCache(playerid)(WEAPON_FUNC)(pLastAmmo) = 0
	WeaponCache(playerid)(WEAPON_FUNC)(pShot) = false
	
	ResetPlayerWeapons(playerid)
	
	if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_MAIN)) RemovePlayerAttachedObject(playerid, SLOT_WEAPON_MAIN)
	if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_SIDE)) RemovePlayerAttachedObject(playerid, SLOT_WEAPON_SIDE)
	if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_WEAPON_FUNC)) RemovePlayerAttachedObject(playerid, SLOT_WEAPON_FUNC)
	
	PlayerCache(playerid)(pSpectate) = giveplayer_id
	player_state = GetPlayerState(giveplayer_id)
	
	SetPlayerInterior(playerid, GetPlayerInterior(giveplayer_id))
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(giveplayer_id))
	
	info(256)

	format(info, sizeof(info), ~r~%s(%d)  ~w~(%s)~n~~y~Zalogowany o %d:%d:%d~n~~w~UID: %d  GID: %d~n~Portfel: ~g~$%d~w~  Bank: ~g~$%d, PlayerName(giveplayer_id), giveplayer_id, PlayerCache(giveplayer_id)(pGlobalName), LoginTime(giveplayer_id)(0), LoginTime(giveplayer_id)(1), LoginTime(giveplayer_id)(2), PlayerCache(giveplayer_id)(pUID), PlayerCache(giveplayer_id)(pGID), PlayerCache(giveplayer_id)(pCash), PlayerCache(giveplayer_id)(pBankCash))
	PlayerTextDrawSetString(playerid, AdminSpecInfo(playerid), info)

	format(info, sizeof(info), ~b~Sila: ~w~%.2f~n~~w~~b~Lowienie: ~w~%.2f, PlayerCache(giveplayer_id)(pStrength), PlayerCache(giveplayer_id)(pFishing))
	PlayerTextDrawSetString(playerid, AdminSpecStats(playerid), info)

	PlayerTextDrawShow(playerid, AdminSpecInfo(playerid))
	PlayerTextDrawShow(playerid, AdminSpecStats(playerid))

	switch(player_state)
	(
		case 2, 3:
		(
			TogglePlayerSpectating(playerid, true)
			PlayerSpectateVehicle(playerid, GetPlayerVehicleID(giveplayer_id))
		)
		case 0, 1, 4, 7, 8:
		(
			TogglePlayerSpectating(playerid, true)
			PlayerSpectatePlayer(playerid, giveplayer_id)
		)
	)
	return 1
)

CMD:setint(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, interior_id, string(128)
	if(sscanf(params, dd, giveplayer_id, interior_id))
	(
		hrp_Tip(playerid, /setint (ID gracza) (Interior))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	SetPlayerInterior(giveplayer_id, interior_id)
	
	format(string, sizeof(string), InteriorID gracza %s zosta³ zmieniony pomyœlnie.\nNowy interior: %d, PlayerName(giveplayer_id), interior_id)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:setvw(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, virtual_world, string(128)
	if(sscanf(params, dd, giveplayer_id, virtual_world))
	(
		hrp_Tip(playerid, /setvw (ID gracza) (VirtualWorld))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	SetPlayerVirtualWorld(giveplayer_id, virtual_world)

	format(string, sizeof(string), VirualWorld gracza %s zosta³ zmieniony pomyœlnie.\nNowy VirtualWorld: %d, PlayerName(giveplayer_id), virtual_world)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:sethp(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, Float:health, string(128)
	if(sscanf(params, df, giveplayer_id, health))
	(
		hrp_Tip(playerid, /sethp (ID gracza) (Iloœæ HP))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)

	PlayerCache(giveplayer_id)(pBleeding) = 0

	hrp_SetPlayerHealth(giveplayer_id, health)
	hrp_SetPlayerHealth(giveplayer_id, health)
	hrp_SetPlayerHealth(giveplayer_id, health)
	hrp_SetPlayerHealth(giveplayer_id, health)
	
	for(i = 0 i ( 10 i++)
	(
		PlayerDamageCache(giveplayer_id)(i) = false
	)

	format(string, sizeof(string), HP gracza %s zosta³o pomyœlnie zmienione. Nowy stan HP: %.1f, PlayerName(giveplayer_id), health)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:setskin(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		 ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, skin_id, string(128)
	if(sscanf(params, dd, giveplayer_id, skin_id))
	(
		hrp_Tip(playerid, /setskin (ID gracza) (ID skina))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	if(skin_id ( 0 || skin_id ) 311)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owe ID skina., OK, )
		return 1
	)
	if(skin_id == 300)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Skin ID 300 cos kurwa buguje., OK, )
		return 1
	)
	hrp_SetPlayerSkin(giveplayer_id, skin_id)

	format(string, sizeof(string), Skin gracza %s zosta³ pomyœlnie zmieniony. Nowy skin: %d, PlayerName(giveplayer_id), skin_id)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:setskill(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pUserColor) != 1 && PlayerCache(playerid)(pUserColor) != 3)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Sorry ale na polecenie gamemasterów tylko oni maj¹ dostêp do tej komendy :(., OK, )
		return 1
	)
	giveplayer_id, skill_name(12), skill_lvl, string(128)
	if(sscanf(params, s(12)udf, skill_name, giveplayer_id, skill_lvl))
	(
		hrp_Tip(playerid, /setskill (Nazwa skilla) (ID gracza) (Poziom)\n\nDostêpne nazwy:\n - lowienie\n - plywanie\n - sila)
		return 1
	)
	if(!strcmp(skill_name, lowienie, true))
	(
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(skill_lvl ( 0 || skill_lvl ) 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy poziom umiejêtnoœci., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pFishing) = skill_lvl
		
		format(string, sizeof(string), Umiejetnoœæ ³owienia dla gracza %s zmieniona: %f, PlayerName(giveplayer_id), skill_lvl)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(skill_name, sila, true))
	(
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
		)
		if(!Logged(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(skill_lvl ( 0 || skill_lvl ) 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy poziom umiejêtnoœci., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pStrength) = skill_lvl
		
		format(string, sizeof(string), Si³a dla gracza %s zmieniona: %f, PlayerName(giveplayer_id), skill_lvl)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	return 1
)

CMD:settime(playerid, params())
(
   	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		 ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, time_type(12), time
	if(sscanf(params, ds(12)d, giveplayer_id, time_type, time))
	(
		hrp_Tip(playerid, /settime (ID gracza) (Typ czasu (godzina, minuta)) (Wartoœæ))
		return 1
	)
   	if(giveplayer_id == INVALID_PLAYER_ID)
	(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
 		return 1
	)
	if(!strcmp(time_type, godzina, true))
	(
		if(time ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nieprawid³owy czas., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pHours) = time
		return 1
	)
	if(!strcmp(time_type, minuta, true))
	(
		if(time ( 0 || time ) 60)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³ad, Nieprawid³owy czas., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pMinutes) = time
		return 1
	)
	return 1
)

CMD:freeze(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, string(64)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /freeze (ID gracza))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	hrp_TogglePlayerControllable(giveplayer_id, false)
	
	format(string, sizeof(string), Gracz %s zosta³ zamro¿ony., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:unfreeze(playerid, params())
(
	//if(PlayerCache(playerid)(pAdmin) == 0)
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, string(64)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /unfreeze (ID gracza))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	hrp_TogglePlayerControllable(giveplayer_id, true)

	format(string, sizeof(string), Gracz %s zosta³ odmro¿ony., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:ac(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAdminChat) == false)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz pisaæ na czacie administratorskim poniewa¿ go wy³¹czy³es (/togac)., OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /ac (Tekst))
		return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))
	
	format(string, sizeof(string), (( (AC) %s: %s )), PlayerGlobalName(playerid, COLOR_ADMIN), params)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pAdmin) == 1)
			(
				if(PlayerCache(i)(pAdminChat) == true)
				(
					SendClientMessage(i, COLOR_ADMIN, string)
				)
			)
		)
	)
	return 1
)

CMD:togac(playerid, params())
(
	string(128)
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAdminChat) == true)
	(
		PlayerCache(playerid)(pAdminChat) = false
		format(string, sizeof(string), Czat Administratorów zosta³ dla Ciebie wy³¹czony.)
	)
	else
	(
		PlayerCache(playerid)(pAdminChat) = true
		format(string, sizeof(string), Czat Administratoruf zosta³ dla Ciebie w³¹czony.)
	)

	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

	#pragma unused params
	return 1
)

CMD:sc(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) )= 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /sc (Tekst))
		return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))

	format(string, sizeof(string), (( (SC) %s: %s )), PlayerGlobalName(playerid, COLOR_SUPPORT), params)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pAdmin) ( 0)
			(
				SendClientMessage(i, COLOR_SUPPORT, string)
			)
		)
	)
	return 1
)

CMD:gc(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /gc (Tekst))
		return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))

	format(string, sizeof(string), (( (GC) %s: %s )), PlayerGlobalName(playerid, COLOR_DEPARTMENT), params)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pAdmin) != 0)
			(
				SendClientMessage(i, COLOR_DEPARTMENT, string)
			)
		)
	)
	return 1
)

CMD:gtx(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /gtx (Tekst))
		return 1
	)
	string(256)
	
	format(string, sizeof(string), %s: %s, PlayerName(playerid), params)
	GameTextForAll(string, 15000, 3)
	return 1
)

CMD:ado(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /ado (Sytuacja))
		return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))

	format(string, sizeof(string), ** %s **, params)
	SendClientMessageToAll(COLOR_DO, string)
	return 1
)

CMD:slap(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /slap (ID gracza))
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
		return 1
	)
	Float:PosX, Float:PosY, Float:PosZ
	GetPlayerPos(giveplayer_id, PosX, PosY, PosZ)
	
	hrp_SetPlayerPos(giveplayer_id, PosX, PosY, PosZ + 5.0)
	
	GameTextForPlayer(giveplayer_id, ~n~~n~~n~~r~SLAP!, 3000, 3)
	GameTextForPlayer(playerid, ~n~~n~~n~~r~SLAP!, 3000, 3)
	return 1
)

CMD:playername(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)

	giveplayer_id, new_name(24), string(128)
	if(sscanf(params, ds(24), giveplayer_id, new_name))
	(
		hrp_Tip(playerid, /playername (ID gracza) (Nowy nick (max.24)))
		return 1
	)
   	if(giveplayer_id == INVALID_PLAYER_ID)
	(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
			return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
 		return 1
	)

	format(string, sizeof(string), Nick gracza %s (UID: %d) zosta³ zmieniony.\nNowy nick: %s., PlayerCache(giveplayer_id)(pName), giveplayer_id, new_name)
	strmid(PlayerCache(giveplayer_id)(pName), new_name, 0, strlen(new_name), MAX_PLAYER_NAME)
	PlayerCache(giveplayer_id)(pChangeName) = true

	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:abus(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
 		return 1
	)
	type(32), varchar(32), string(128)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /abus (stworz | nazwa | pozycja | lista | usun))
		return 1
	)
	if(!strcmp(type, stworz, true))
	(
		busstop_name(32)
		if(sscanf(varchar, s(32), busstop_name))
		(
			hrp_Tip(playerid, /abus stworz (Nazwa przystanku))
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)
		
		busstop_id = CreateBusStop(busstop_name, PosX, PosY, PosZ + 0.25)
		
		format(string, sizeof(string), Stworzono nowy przystanek.\nNazwa przystanku: %s (SampID: %d, UID: %d).\n\nPrzystanek stworzony zosta³ w tym miejscu., busstop_name, busstop_id, BusStopData(busstop_id)(bUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, nazwa, true))
	(
		busstop_id, busstop_name(32)
		if(sscanf(varchar, ds(32), busstop_id, busstop_name))
		(
			hrp_Tip(playerid, /abus nazwa (NR przystanku) (Nowa nazwa))
			return 1
		)
		if(!BusStopData(busstop_id)(bUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy nr. przystanku., OK, )
			return 1
		)
   		strmid(BusStopData(busstop_id)(bName), busstop_name, 0, strlen(busstop_name), 32)

		SaveBusStop(busstop_id)

		format(string, sizeof(string), Przystanek nr %d:\n%s., busstop_id, busstop_name)
		UpdateDynamic3DTextLabelText(Text3D:BusStopData(busstop_id)(bNameTag), COLOR_LIGHTBLUE, string)

		format(string, sizeof(string), Nazwa przystanku (SampID: %d, UID: %d) zosta³a zmieniona pomyœlnie.\nNowa nazwa przystanku: %s., busstop_id, BusStopData(busstop_id)(bUID), busstop_name)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, pozycja, true))
	(
		busstop_id
		if(sscanf(varchar, d, busstop_id))
		(
			hrp_Tip(playerid, /abus pozycja (NR przystanku))
			return 1
		)
		if(!BusStopData(busstop_id)(bUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy nr. przystanku., OK, )
			return 1
		)
   		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)
		
		BusStopData(busstop_id)(bPosX) = PosX
		BusStopData(busstop_id)(bPosY) = PosY
		BusStopData(busstop_id)(bPosZ) = PosZ + 0.25
		
		SaveBusStop(busstop_id)
		
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, Text3D:BusStopData(busstop_id)(bNameTag), E_STREAMER_X, BusStopData(busstop_id)(bPosX))
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, Text3D:BusStopData(busstop_id)(bNameTag), E_STREAMER_Y, BusStopData(busstop_id)(bPosY))
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, Text3D:BusStopData(busstop_id)(bNameTag), E_STREAMER_Z, BusStopData(busstop_id)(bPosZ))

		format(string, sizeof(string), Pozycja przystanku (SampID: %d, UID: %d) zosta³a zmieniona pomyœlnie., busstop_id, BusStopData(busstop_id)(bUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, usun, true))
	(
		busstop_id
		if(sscanf(varchar, d, busstop_id))
		(
			hrp_Tip(playerid, /abus usun (NR przystanku))
			return 1
		)
		if(!BusStopData(busstop_id)(bUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy nr. przystanku., OK, )
			return 1
		)
	 	format(string, sizeof(string), Przystanek (SampID: %d, SampID: %d) zosta³ pomyœlnie usuniêty., busstop_id, BusStopData(busstop_id)(bUID))

		DeleteBusStop(busstop_id)

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, lista, true))
	(
		list_busstop(1024)
		for(b = 1 b ( MAX_BUS_STOPS b++)
		(
			if(BusStopData(b)(bUID) != 0)
			(
				format(list_busstop, sizeof(list_busstop), %s\n%d\t%s, list_busstop, b, BusStopData(b)(bName))
			)
		)
		if(strlen(list_busstop) (= 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie ma ¿adnych utworzonych przystanków., OK, )
			return 1
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Lista przystanków:, list_busstop, Zamknij, )
		return 1
	)
	return 1
)

CMD:phr(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
 		return 1
	)
	type(32), varchar(32), string(128)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /phr (stworz | nazwa | pozycja | lista | usun))
		return 1
	)
	if(!strcmp(type, stworz, true))
	(
		Float:photoradar_maxspeed
		if(sscanf(varchar, f, photoradar_maxspeed))
		(
			hrp_Tip(playerid, /phr stworz (Max. prêdkoœæ))
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)

		AddPhotoRadar(PosX, PosY, PosZ, photoradar_maxspeed)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pomyœlnie postawiono fotoradar.\nU¿yj komendy /phr lista, by ujrzeæ ich listê., OK, )
		return 1
	)
	if(!strcmp(type, pozycja, true))
	(
		photoradar_id
		if(sscanf(varchar, d, photoradar_id))
		(
			hrp_Tip(playerid, /phr pozycja (ID fotoradaru))
			return 1
		)
		if(!PhotoRadarInfo(photoradar_id)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owe ID fotoradaru., OK, )
			return 1
		)
   		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)

		PhotoRadarInfo(photoradar_id)(pPosX) = PosX
		PhotoRadarInfo(photoradar_id)(pPosY) = PosY
		PhotoRadarInfo(photoradar_id)(pPosZ) = PosZ

		SavePhotoRadar(photoradar_id)
		
		format(string, sizeof(string), Pozycja fotoradaru (SampID: %d, UID: %d) zosta³a zmieniona pomyœlnie., photoradar_id, PhotoRadarInfo(photoradar_id)(pUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, usun, true))
	(
		photoradar_id
		if(sscanf(varchar, d, photoradar_id))
		(
			hrp_Tip(playerid, /phr usun (ID fotoradaru))
			return 1
		)
		if(!PhotoRadarInfo(photoradar_id)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owe ID fotoradaru., OK, )
			return 1
		)
	 	format(string, sizeof(string), Fotoradar (SampID: %d, SampID: %d) zosta³ pomyœlnie usuniêty., photoradar_id, PhotoRadarInfo(photoradar_id)(pUID))

		DeletePhotoRadar(photoradar_id)

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, lista, true))
	(
		list_photoradars(1024)
		for(p = 1 p ( MAX_PHOTO_RADARS p++)
		(
			if(PhotoRadarInfo(p)(pUID) != 0)
			(
				format(list_photoradars, sizeof(list_photoradars), %s\n%d\tFotoradar nr %d, list_photoradars, p, p)
			)
		)
		if(strlen(list_photoradars) (= 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie ma ¿adnych utworzonych fotoradarów., OK, )
			return 1
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Lista przystanków:, list_photoradars, Zamknij, )
		return 1
	)
	return 1
)

CMD:ggate(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	group_uid
	if(sscanf(params, d, group_uid))
	(
		hrp_Tip(playerid, /ggate (ID grupy))
		return 1
	)
	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject)
		
	object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)
	
	mysql_query_format(UPDATE hrp_objects SET object_owner = %d WHERE object_uid = %d LIMIT 1, group_uid, object_uid)

	string(64), group_id_fix = GetGroupID(group_uid)
	format(string, sizeof(string), Przypisano obiekt o uid: %d pod grupê %s (Uid: %d), object_uid, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:pgate(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	player_uid
	if(sscanf(params, d, player_uid))
	(
		hrp_Tip(playerid, /pgate (UID gracza))
		return 1
	)
	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject)
		
	object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)
	
	mysql_query_format(UPDATE hrp_objects SET object_owner = %d WHERE object_uid = %d LIMIT 1, player_uid, object_uid)

	string(64)
	format(string, sizeof(string), Przypisano obiekt o uid: %d pod gracza Uid: %d, object_uid, player_uid)
 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:wczytaj(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	world_id
	if(sscanf(params, d, world_id))
	(
		hrp_Tip(playerid, /wczytaj (ID worlda))
		return 1
	)
	object_uid, object_model,
		Float:object_posx, Float:object_posy, Float:object_posz,
		Float:object_rotx, Float:object_roty, Float:object_rotz,
		object_world, object_interior, Float:object_distance

	// Usuñ stare obiekty z tego VW (jeœli s¹)
	for (object_id = 0 object_id ( MAX_OBJECTS object_id++)
	(
 		if(IsValidDynamicObject(object_id))
   		(
			if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID, world_id))
			(
				DestroyDynamicObject(object_id)
	  		)
		)
	)
	
	data(512), object_id
	mysql_query_format(SELECT * FROM hrp_objects WHERE object_world = %d, world_id)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ddffffffddf, object_uid, object_model, object_posx, object_posy, object_posz, object_rotx, object_roty, object_rotz, object_world, object_interior, object_distance)
		object_id = CreateDynamicObject(object_model, object_posx, object_posy, object_posz, object_rotx, object_roty, object_rotz, object_world, object_interior, -1, object_distance)
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, object_uid)
	)
	LoadObjectTags(world_id)
	
	
	// ³adowanie przy wczytywaniu
	for(objectid = 0  objectid ( MAX_OBJECTS objectid++)
	(
		if(IsValidDynamicObject(objectid))
		(
			if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID, world_id))
			(
				LoadObjectMaterial(objectid)
				LoadObjectText(objectid)
	  		)
		)
	)
	
	mysql_free_result()
	return 1
)

CMD:testosadminos(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		return 1
	)
	
	item_counts, time = GetTickCount()
	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID) != 0)
		(
			item_counts ++
		)
	)
	
	SendClientFormatMessage(playerid, COLOR_YELLOW, Na serwerze jest wczytanych %d (%d) przedmiotów ³¹cznie w chwili obecnej., item_counts, Itter_Count(Items))
	SendClientFormatMessage(playerid, COLOR_YELLOW, Czas wykonania siê pêtli (%d) wynosi %d milisekund., MAX_ITEM_CACHE, GetTickCount() - time)

	SendClientFormatMessage(playerid, COLOR_YELLOW, Wolny index dla przedmiotów: %d, Itter_Free(Items))
	SendClientFormatMessage(playerid, COLOR_YELLOW, Wolny index dla graczy: %d, Itter_Free(Player))
	SendClientFormatMessage(playerid, COLOR_YELLOW, Wolny index dla produktów: %d, Itter_Free(Products))

	object_counts, world_id = GetPlayerVirtualWorld(playerid), tick_count = GetTickCount()
	for (i = 0 i (= MAX_OBJECTS i++)
	(
		if(IsValidDynamicObject(i))
		(
			if(Streamer_IsItemVisible(playerid, STREAMER_TYPE_OBJECT, i))
			(
				if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, i, E_STREAMER_WORLD_ID, world_id))
				(
					object_counts ++
				)
			)
		)
	)
	SendClientFormatMessage(playerid, COLOR_RED, Iloœæ obiektów: %d/%d, object_counts, CountDynamicObjects())
	SendClientFormatMessage(playerid, COLOR_GREEN, Czas wykonania: %d ms, GetTickCount() - tick_count)


	label_id = GetClosestLabel(playerid)
	if(label_id == INVALID_3DTEXT_ID)
	(
		SendClientMessage(playerid, COLOR_RED, Nie znaleziono 3D tekstów!)
	)
	else
	(
		SendClientFormatMessage(playerid, COLOR_GREEN, Znaleziono 3D tekst: %d, label_id)
	)
	return 1
)

CMD:astrefa(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32), string(256)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /strefa (stworz | przypisz | usun | edytuj | obiekty))
		hrp_Tip(playerid, Pamiêtaj, ¿e wykonuj¹c akcje dla konkretnego terenu, musisz byæ w jego fizycznej lokacji. Strefa 10x10 jest bardzo ma³a, zacznij od 50x50.)
		return 1
	)
	if(!strcmp(type, stworz, true))
	(
		Float:gangzone_maxx, Float:gangzone_maxy
		if(sscanf(varchar, ff, gangzone_maxx, gangzone_maxy))
		(
			hrp_Tip(playerid, /strefa stworz (MaxX) (MaxY))
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)
		
		gangzone_id = AddGangZone(PosX - (gangzone_maxx/2), PosY - (gangzone_maxy/2), PosX + (gangzone_maxx/2), PosY + (gangzone_maxy/2))
		
		format(string, sizeof(string), Strefa (SampID: %d, UID: %d) zosta³a pomyœlnie stworzona.\nAby zarz¹dzaæ strefami skorzystaj z komendy /strefa., gangzone_id, GangZoneInfo(gangzone_id)(gUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, przypisz, true))
	(
		group_uid
		if(sscanf(varchar, d, group_uid))
		(
			hrp_Tip(playerid, /strefa przypisz (UID grupy))
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)

		foreach(GangZones, gangzone_id)
		(
			if(GangZoneInfo(gangzone_id)(gUID))
			(
				if(IsPlayerInArea(playerid, GangZoneInfo(gangzone_id)(gMaxX), GangZoneInfo(gangzone_id)(gMinX), GangZoneInfo(gangzone_id)(gMaxY), GangZoneInfo(gangzone_id)(gMinY)))
				(
					GangZoneInfo(gangzone_id)(gOwner) = GroupData(group_id_fix)(gUID)
					SaveGangZone(gangzone_id, SAVE_GZ_OWNER)

				   	// Zmieñ kolorek dla wszystkich
					foreach(Player, i)
					(
						if(Logged(i) && Spawned(i))
						(
							if(PlayerCache(i)(pShowingZones))
							(
		  						GangZoneShow(playerid, gangzone_id)
		  					)
						)
					)
					
					format(string, sizeof(string), Teren (SampID: %d, UID: %d) zosta³ pomyœlnie przypisany pod grupê.\nStrefa przypisana dla %s (UID: %d)., gangzone_id, GangZoneInfo(gangzone_id)(gUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
					return 1
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê na ¿adnym z terenów.\nMusisz znajdowaæ siê na danym terenie, by móc go przypisaæ., OK, )
		return 1
	)
	if(!strcmp(type, usun, true))
	(
 		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)

		foreach(GangZones, gangzone_id)
		(
			if(GangZoneInfo(gangzone_id)(gUID))
			(
				if(IsPlayerInArea(playerid, GangZoneInfo(gangzone_id)(gMaxX), GangZoneInfo(gangzone_id)(gMinX), GangZoneInfo(gangzone_id)(gMaxY), GangZoneInfo(gangzone_id)(gMinY)))
				(
					format(string, sizeof(string), Teren (SampID: %d, UID: %d) zosta³ pomyœlnie usuniêty z bazy., gangzone_id, GangZoneInfo(gangzone_id)(gUID))
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

					foreach(Player, i)
					(
						if(Logged(playerid) && Spawned(playerid))(
							GangZoneHideForPlayer(i, gangzone_id)
						)
					)
					DeleteGangZone(gangzone_id)
					return 1
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê na ¿adnym z terenów.\nMusisz znajdowaæ siê na danym terenie, by móc go usun¹æ., OK, )
		return 1
	)
	if(!strcmp(type, edytuj, true))
	(
 		Float:gangzone_maxx, Float:gangzone_maxy
		if(sscanf(varchar, ff, gangzone_maxx, gangzone_maxy))
		(
			hrp_Tip(playerid, /strefa edytuj (MaxX) (MaxY))
			return 1
		)
   		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)
		
		foreach(GangZones, gangzone_id)
		(
			if(GangZoneInfo(gangzone_id)(gUID))
			(
				if(IsPlayerInArea(playerid, GangZoneInfo(gangzone_id)(gMaxX), GangZoneInfo(gangzone_id)(gMinX), GangZoneInfo(gangzone_id)(gMaxY), GangZoneInfo(gangzone_id)(gMinY)))
				(
					Float:creationX = GangZoneInfo(gangzone_id)(gMinX) + floatabs(GangZoneInfo(gangzone_id)(gMaxX) - GangZoneInfo(gangzone_id)(gMinX))
					Float:creationY = GangZoneInfo(gangzone_id)(gMinY) + floatabs(GangZoneInfo(gangzone_id)(gMaxY) - GangZoneInfo(gangzone_id)(gMinY))
					Float:newMinX = creationX - (gangzone_maxx/2)
					Float:newMinY = creationY - (gangzone_maxy/2)
					Float:newMaxX = creationX + (gangzone_maxx/2)
					Float:newMaxY = creationX + (gangzone_maxy/2)
					
				
					GangZoneInfo(gangzone_id)(gMinX) = newMinX
					GangZoneInfo(gangzone_id)(gMinY) = newMinY 
					GangZoneInfo(gangzone_id)(gMaxX) = newMaxX
					GangZoneInfo(gangzone_id)(gMaxY) = newMaxY
					
					SaveGangZone(gangzone_id, SAVE_GZ_POS)
					
					GangZoneDestroy(gangzone_id)
					GangZoneCreate(newMinX, newMinY, newMaxX, newMaxY)

					format(string, sizeof(string), Teren (SampID: %d, UID: %d) zosta³ pomyœlnie zmodyfikowany., gangzone_id, GangZoneInfo(gangzone_id)(gUID))
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
					return 1
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê na ¿adnym z terenów.\nMusisz znajdowaæ siê na danym terenie, by móc go edytowaæ., OK, )
		return 1
	)
	return 1
)

CMD:reloadanims(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		return 1
	)
	LoadAnims()
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Animacje zosta³y pomyœlnie prze³adowane., OK, )
	return 1
)

CMD:restart(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		return 1
	)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			SavePlayerStats(i, SAVE_PLAYER_BASIC | SAVE_PLAYER_SKILLS)
		)
	)
	GameTextForAll(~g~Restart serwera..., 5000, 3)
	SendRconCommand(gmx)
	return 1
)

CMD:arhir(playerid, params())
(
	sid
	if(sscanf(params, d, sid))
	(
		PlayerPlaySound(playerid, 6001, 0.0, 0.0, 0.0)
		return 1
	)
	PlayerPlaySound(playerid, sid, 0.0, 0.0, 0.0)
	return 1
)

CMD:ag(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
 		return 1
	)
	type(32), varchar(64), string(256)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /ag (dotacja | stworz | lider | lista | nazwa | usun | info | typ | value1))
		return 1
	)
	if(!strcmp(type, dotacja, true))
	(
		group_uid, group_dotation
		if(sscanf(varchar, dd, group_uid, group_dotation))		// /ag dotacja 154 200 (- Grupa o uid 154 dostanie 200 dotacji
		(
			hrp_Tip(playerid, /ag dotacja (UID grupy) (Kwota dotacji))
			return 1
		)
		
		group_id_fix = GetGroupID(group_uid)
		if(GroupData(group_id_fix)(gUID) (= 0)
		(
			GuiMsg(playerid, Podano b³êdne UID grupy., 1)
			return 1
		)
		
		format(string, sizeof(string), Ustawi³eœ grupie %s (UID: %d) kwotê dotacji na: $%d!, GroupData(group_id_fix)(gName), group_uid, group_dotation)
		GuiMsg(playerid, string, 0)		// informacja
		GroupData(group_id_fix)(gDotation) = group_dotation
		SaveGroup(group_id_fix)
	)
	if(!strcmp(type, stworz, true))
	(
		group_name(32)
		if(sscanf(varchar, s(32), group_name))
		(
			hrp_Tip(playerid, /ag stworz (Nazwa grupy))
			return 1
		)
		group_id_fix = CreateGroup(group_name)

		format(string, sizeof(string), Grupa zosta³a stworzona pomyœlnie: %s (UID: %d)., GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		return 1
	)
	if(!strcmp(type, lider, true))
	(
		group_uid, giveplayer_id
		if(sscanf(varchar, dd, group_uid, giveplayer_id))
		(
			hrp_Tip(playerid, /ag lider (UID grupy) (ID gracza))
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		   	return 1
		)
		if(!Logged(giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(IsPlayerInGroup(giveplayer_id, GroupData(group_id_fix)(gUID)) || (GroupData(group_id_fix)(gOwner) && IsPlayerInGroup(giveplayer_id, GroupData(group_id_fix)(gOwner))))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nale¿y ju¿ do tej grupy., OK, )
			return 1
		)
		group_slot = GetPlayerFreeGroupSlot(giveplayer_id)
		if(group_slot == INVALID_SLOT_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie posiada ¿adnego wolnego slotu dla grupy., OK, )
			return 1
		)
		PlayerGroup(giveplayer_id)(group_slot)(gUID) = GroupData(group_id_fix)(gUID)
		PlayerGroup(giveplayer_id)(group_slot)(gID) = group_id_fix

		PlayerGroup(giveplayer_id)(group_slot)(gPerm) = PERM_LIMIT
		mysql_query_format(INSERT INTO hrp_char_groups (char_uid, group_uid, group_perm) VALUES (%d, %d, %d), PlayerCache(giveplayer_id)(pUID), GroupData(group_id_fix)(gUID), PERM_LIMIT)

		format(string, sizeof(string), Administrator %s przypisa³ Ci lidera grupy %s (SampID: %d, UID: %d).\nSkorzystaj z komendy /pomoc, by zapoznaæ siê z komendami lidera., PlayerName(playerid), GroupData(group_id_fix)(gName), group_id_fix, GroupData(group_id_fix)(gUID))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Gracz %s (ID: %d, UID: %d) otrzyma³ lidera grupy %s (SampID: %d, UID: %d)., PlayerName(giveplayer_id), giveplayer_id, PlayerCache(giveplayer_id)(pUID), GroupData(group_id_fix)(gName), group_id_fix, GroupData(group_id_fix)(gUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		return 1
	)
	if(!strcmp(type, nazwa, true))
	(
		group_uid, group_name(32)
		if(sscanf(varchar, ds(32), group_uid, group_name))
		(
			hrp_Tip(playerid, /ag nazwa (UID grupy) (Nowa nazwa))
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)
		format(string, sizeof(string), Nazwa grupy %s (UID: %d) zosta³a zmieniona pomyœlnie.\nNowa nazwa grupy: %s, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID), group_name)
		strmid(GroupData(group_id_fix)(gName), group_name, 0, strlen(group_name), 32)

		SaveGroup(group_id_fix)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		return 1
	)
	if(!strcmp(type, usun, true))
	(
		group_uid
		if(sscanf(varchar, d, group_uid))
		(
			hrp_Tip(playerid, /ag usun (UID grupy))
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)
		DeleteGroup(group_id_fix)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Grupa zosta³a pomyœlnie usuniêta z bazy danych., OK, )
		return 1
	)
	if(!strcmp(type, info, true))
	(
		group_uid
		if(sscanf(varchar, d, group_uid))
		(
			hrp_Tip(playerid, /ag info (UID grupy))
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)
		ShowPlayerGroupInfo(playerid, group_id_fix)
		return 1
	)
	if(!strcmp(type, typ, true))
	(
 		group_uid
		if(sscanf(varchar, d, group_uid))
		(
			hrp_Tip(playerid, /ag typ (UID grupy))
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)
		MainPlayerTable(playerid) = group_id_fix

		list_group_type(1024)
		for (i = 0 i ( sizeof(GroupTypeInfo) i++)
		(
			format(list_group_type, sizeof(list_group_type), %s\n%d\t%s, list_group_type, i + 1, GroupTypeInfo(i)(gTypeName))
		)

		format(string, sizeof(string), %s (UID: %d) » Zmiana typu, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
		ShowPlayerDialog(playerid, D_CHANGE_GROUP_TYPE, DIALOG_STYLE_LIST, string, list_group_type, Wybierz, Anuluj)
		return 1
	)
	if(!strcmp(type, value1, true))
	(
		group_uid, group_value1
		if(sscanf(varchar, dd, group_uid, group_value1))
		(
			hrp_Tip(playerid, /ag nazwa (UID grupy) (Wartoœæ 1))
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)
		format(string, sizeof(string), Wartoœæ 1 grupy %s (UID: %d) zosta³a zmieniona pomyœlnie.\nNowa wartoœæ: %d, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID), group_value1)
		
		GroupData(group_id_fix)(gValue1) = group_value1
		SaveGroup(group_id_fix)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		return 1
	)
	if(!strcmp(type, value2, true))
	(
		group_uid, group_value2
		if(sscanf(varchar, dd, group_uid, group_value2))
		(
			hrp_Tip(playerid, /ag nazwa (UID grupy) (Wartoœæ 2))
			return 1
		)
		group_id_fix = GetGroupID(group_uid)
		if(group_id_fix == INVALID_GROUP_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
			return 1
		)
		format(string, sizeof(string), Wartoœæ 2 grupy %s (UID: %d) zosta³a zmieniona pomyœlnie.\nNowa wartoœæ: %d, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID), group_value2)
		
		GroupData(group_id_fix)(gValue2) = group_value2
		SaveGroup(group_id_fix)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
		return 1
	)
	return 1
)

CMD:aphone(playerid,params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
 		return 1
	)
	type(32), varchar(64),buffer(256)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /aphone (stworz | usun))
		return 1
	)
	
	if(!strcmp(type, stworz, true))
	(
		Float:Pos(3)
		
		format(buffer,sizeof(buffer),SELECT MAX(phone_number) FROM hrp_phones)
		mysql_query(buffer)
		mysql_store_result()
		number = mysql_fetch_int()
		mysql_free_result()
		
		number = number +1
		
		GetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))
		format(buffer,sizeof(buffer),INSERT INTO hrp_phones VALUES (NULL,%i,%f,%f,%f,%i,%i),number,Pos(0),Pos(1),Pos(2),GetPlayerVirtualWorld(playerid),GetPlayerInterior(playerid))
		mysql_query(buffer)
		
		ReloadPhones()
		
		GuiMsg(playerid,Stworzy³eœ now¹ budkê, powinna pojawiæ siê w miejscu, w którym stoisz.,0)
		
	)
	
	return 1
)

CMD:adminmode(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
 		return 1
	)
	if(PlayerCache(playerid)(pAdminMode) == -1)
	(
		PlayerCache(playerid)(pAdminMode) = 0
		TextDrawSetString(TextDrawAdminMode(playerid), Penalties(0))
		TextDrawShowForPlayer(playerid, TextDrawAdmin)
		TextDrawShowForPlayer(playerid, TextDrawAdminMode(playerid))
	) else (
		PlayerCache(playerid)(pAdminMode) = -1
		TextDrawHideForPlayer(playerid, TextDrawAdmin)
		TextDrawHideForPlayer(playerid, TextDrawAdminMode(playerid))
	)
	return 1
)

CMD:apress(playerid,params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid,Brak uprawnieñ do wykonania tej komendy.,1)
 		return 1
	)
	
	type(32), varchar(64),buffer(256)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /apress (stworz | usun))
		return 1
	)
	
	if(!strcmp(type, stworz, true))
	(
		Float:Pos(3)
		GetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))
		
		format(buffer,sizeof(buffer),INSERT INTO wbc_newsboxes VALUES(NULL,%f,%f,%f,%i,0),Pos(0),Pos(1),Pos(2),GetPlayerVirtualWorld(playerid))
		mysql_query(buffer)
		
		ReloadNewsboxes()
		
		GuiMsg(playerid,Doda³eœ now¹ budkê z gazetami na aktualnej pozycji.,0)
	)
	
	if(!strcmp(type, usun, true))
	(
		for(i = 0  i ( MAX_PRESSBOX i++)
		(
			if(IsPlayerInRangeOfPoint(playerid,5,PressBox(i)(bPosX),PressBox(i)(bPosY),PressBox(i)(bPosZ)))
			(
				if(GetPlayerVirtualWorld(playerid) == PressBox(i)(bVW))
				(
					remove = PressBox(i)(bUID)
					format(buffer,sizeof(buffer),DELETE FROM wbc_newsboxes WHERE box_id=%i,remove)
					mysql_query(buffer)
					
					ReloadNewsboxes()
					
					GuiMsg(playerid,Usun¹³eœ budkê stoj¹c¹ najbli¿ej Ciebie.,0)
				)	
			)
		)
	)
	
	return 1
)

CMD:pogoda(playerid,params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid,Brak uprawnieñ do wykonania tej komendy.,1)
 		return 1
	)
	
	type(32), varchar(64)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /pogoda (deszczowa | deszczowa2 | sloneczna | pochmurna | id))
		return 1
	)
	
	if(!strcmp(type, id, true))
	(
		weather_id
		if(sscanf(varchar, d, weather_id))
		(
			hrp_Tip(playerid, /pogoda id (ID Pogody))
			return 1
		)
		
		CurrentWeather = weather_id
	)
	
	if(!strcmp(type, deszczowa, true))
	(
		CurrentWeather = 8
	)
	
	if(!strcmp(type, sloneczna, true))
	(
		CurrentWeather = 0
	)
	
	if(!strcmp(type, pochmurna, true))
	(
		CurrentWeather = 4
	)
	
	if(!strcmp(type, deszczowa2, true))
	(
		CurrentWeather = 16
	)
	
	WeatherTicks = 0
	
	return 1
)

CMD:blint(playerid,params())
(
	/*
		wybacz Szymon, musia³em 
	*/
	
	if(PlayerCache(playerid)(pGID) == 53835 || PlayerCache(playerid)(pGID) == 37572)
	(
		if(PlayerCache(playerid)(pTogW))
		(
			PlayerCache(playerid)(pTogW) = false
			GuiMsg(playerid,false,0)
		)
		else
		(
			PlayerCache(playerid)(pTogW) = true
			GuiMsg(playerid,true,0)
		)
	)
	else
	(
		return 1
	)
	
	return 1
)

CMD:aslots(playerid,params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid,Brak uprawnieñ.,1)
		return 1
	)
	
	type(32), varchar(128)
	if(sscanf(params, s(32)S()(128), type, varchar))
	(
		hrp_Tip(playerid, /aslots (stworz | usun | lista | goto | przypisz))
		return 1
	)
	
	if(!strcmp(type, stworz, true))
	(
		Float:Pos(3)
		GetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))
		
		gameid = slots_GetFreeID()
		if(gameid == -1)
		(
			GuiMsg(playerid,Zabrak³o miejsca na t¹ maszynê.,1)
			return 1
		)
		
		buffer(256)
		format(buffer,sizeof(buffer),INSERT INTO hrp_slots VALUES(NULL,%f,%f,%f,%i,0,0),Pos(0),Pos(1),Pos(2),GetPlayerVirtualWorld(playerid))
		mysql_query(buffer)
		
		uid = mysql_insert_id()
		SlotMachine(gameid)(mUID) = uid
		SlotMachine(gameid)(mPosX) = Pos(0)
		SlotMachine(gameid)(mPosY) = Pos(1)
		SlotMachine(gameid)(mPosZ) = Pos(2)
		SlotMachine(gameid)(mVW) = GetPlayerVirtualWorld(playerid)
		SlotMachine(gameid)(mMoney) = 0
		
		format(buffer,sizeof(buffer),Utworzy³eœ now¹ maszynê do jednorêkiego bandyty (ID: %i),gameid)
		GuiMsg(playerid,buffer,0)
		
	)
	
	if(!strcmp(type, usun, true))
	(
		slotid
		if(sscanf(varchar,d,slotid))
		(
			hrp_Tip(playerid,/aslots usun (ID maszyny))
			return 1
		)
		
		if(SlotMachine(slotid)(mUID) (= 0)
		(
			GuiMsg(playerid,Taki automat nie istnieje.,1)
			return 1
		)
		
		buffer(256)
		format(buffer,sizeof(buffer),DELETE FROM hrp_slots WHERE uid=%i,SlotMachine(slotid)(mUID))
		mysql_query(buffer)
		
		SlotMachine(slotid)(mUID) = 0
		SlotMachine(slotid)(mPosX) = 0.0  
		SlotMachine(slotid)(mPosY) = 0.0  
		SlotMachine(slotid)(mPosZ) = 0.0  
		SlotMachine(slotid)(mVW) = 0
		SlotMachine(slotid)(mMoney) = 0
		SlotMachine(slotid)(mOwner) = 0
	)
	
	if(!strcmp(type, goto, true))
	(
		slotid
		if(sscanf(varchar,d,slotid))
		(
			hrp_Tip(playerid,/aslots goto (ID maszyny))
			return 1
		)
		
		if(SlotMachine(slotid)(mUID) (= 0)
		(
			GuiMsg(playerid,Taki automat nie istnieje.,1)
			return 1
		)
		
		SetPlayerVirtualWorld(playerid,SlotMachine(slotid)(mVW))
		SetPlayerPos(playerid,SlotMachine(slotid)(mPosX),SlotMachine(slotid)(mPosY),SlotMachine(slotid)(mPosZ))
	)
	
	if(!strcmp(type, lista, true))
	(
		list(2048)
		for(i = 0  i ( MAX_SLOTS i++)
		(
			if(SlotMachine(i)(mUID) ) 0)
			(
				format(list,sizeof(list),%s\nID: %i \t\tKasa:$%i,list,i,SlotMachine(i)(mMoney))
			)
		)
		
		ShowPlayerDialog(playerid,D_INFO, DIALOG_STYLE_LIST,Lista maszyn typu slots,list,K,)
	)
	
	if(!strcmp(type, przypisz, true))
	(
		slotid,groupuid
		if(sscanf(varchar,dd,slotid,groupuid))
		(
			hrp_Tip(playerid,/aslots przypisz (ID maszyny) (UID grupy))
			return 1
		)
		
		if(SlotMachine(slotid)(mUID) (= 0)
		(
			GuiMsg(playerid,Taki automat nie istnieje.,1)
			return 1
		)
		
		buffer(256)
		format(buffer,sizeof(buffer),UPDATE hrp_slots SET owner=%i WHERE uid=%i,groupuid,SlotMachine(slotid)(mUID))
		mysql_query(buffer)
		
		SlotMachine(slotid)(mOwner) = groupuid
	)
	
	
	
	return 1
)

CMD:lataj(playerid,params())		// dodajê latanie dla supportu, jak bêd¹ odwalaæ to siê usunie :)
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		GuiMsg(playerid,Brak uprawnieñ do wykonania tej komendy.,1)
		return 1
	)
	
	StartFly(playerid)
	
	return 1
)

CMD:nielataj(playerid,params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		GuiMsg(playerid,Brak uprawnieñ do wykonania tej komendy.,1)
		return 1
	)
	
	StopFly(playerid)
	
	return 1
)

CMD:setmoney(playerid,params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid,Brak uprawnieñ do wykonania tej komendy.,1)
		return 1
	)
	
	type(32), varchar(128)
	if(sscanf(params, s(32)S()(128), type, varchar))
	(
		hrp_Tip(playerid, /setmoney ( bank | kieszen ))
		return 1
	)
	
	if(!strcmp(type, bank, true))
	(
		target, amount
		if(sscanf(varchar,dd,target,amount))
		(
			hrp_Tip(playerid,/setmoney bank (ID gracza) (Iloœæ))
			return 1
		)
		
		PlayerCache(target)(pBankCash) = amount
		SavePlayerStats(target, SAVE_PLAYER_BASIC)
		
		GuiMsg(playerid,Zmieni³eœ stan konta gracza.,0)
		hrp_AdminActionLog(%s (UID: %d) zmienil stan konta gracza %s (UID: %d) na $%i, PlayerName(playerid), PlayerCache(playerid)(pUID), PlayerName(target),PlayerCache(target)(pUID),amount)
		
	)
	
	if(!strcmp(type, kieszen, true))
	(
		target, amount
		if(sscanf(varchar,dd,target,amount))
		(
			hrp_Tip(playerid,/setmoney bank (ID gracza) (Iloœæ))
			return 1
		)
		
		hrp_GivePlayerMoney(target, amount)
		GuiMsg(playerid,Zmieni³eœ stan posiadanej przy sobie kasy u gracza.,0)
		hrp_AdminActionLog(%s (UID: %d) zmienil stan kasy przy sobie gracza %s (UID: %d) na $%i, PlayerName(playerid), PlayerCache(playerid)(pUID), PlayerName(target),PlayerCache(target)(pUID),amount)
	)
	
	return 1
)

CMD:quake(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) == 1)
	(
		foreach(Player, i)
		(
			scale = 4500 + random(25) * 100
			SetPlayerDrunkLevel(i, scale)
		)
		QuakeTimer = 20
		SendClientMessageToAll(COLOR_DO, ** W ca³ym miescie czuæ trzêsienie ziemi. Ludzie wychodz¹ z domów, s³ychaæ alarmy w samochodach. **)
	)

	return 1
)

CMD:temp(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Brak uprawnieñ!, 1)
		return 1
	)
	
	setTemp
	if(sscanf(params, d, setTemp))
	(
		hrp_Tip(playerid, /temp (Iloœæ stopni))
		return 1
	)
	
	temp_s(8)
	format(temp_s, sizeof(temp_s), %d C, setTemp)
	TextDrawSetString(Text:TextDrawTemperature, temp_s)
	
	message(128)
	format(message, sizeof(message), Ustali³eœ temperaturê na %d stopni Celcjusza., setTemp)
	GuiMsg(playerid, message, 0)
	
	return 1
)

/*CMD:addtune(playerid, params())
(
	// To sie mo¿e póŸniej administracji przydaæ, ale póki co nie koñczê tego
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Brak uprawnieñ do wykonania tej komendy., 1)
		return 1
	)
	
	if(!IsPlayerInAnyVehicle(playerid))
	(
		GuiMsg(playerid, Musisz siedzieæ w pojeŸdzie, do którego chcesz dorzuciæ czêœæ tuningow¹., 1)
		return 1
	)
	
	vehicleid = GetPlayerVehicleID(playerid)
	vehicle_uid = CarInfo(vehicleid)(cUID)
	
	
	
	return 1
)*/

CMD:syskick(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ( 1 && PlayerCache(playerid)(pAdmin) ) -3)
	(
		GuiMsg(playerid, Brak uprawnieñ do wykonania tej komendy., 1)
		return 1
	)
	
	target_id, reason(128)
	if(sscanf(params, ds(128), target_id, reason))
	(
		hrp_Tip(playerid, /syskick (ID Gracza) (Powód))
		return 1
	)
	
	hrp_Kick(target_id, -1, reason, false)
	
	return 1
)

CMD:zegary(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Brak uprawnieñ do wykonania tej komendy., 1)
		return 1
	)
	
	/*KillTimer(tMinute)
	KillTimer(tHalf)
	KillTimer(tQuarter)
	KillTimer(tSecond)
	
	tMinute = SetTimer(OnMinuteTimer, 60000, true)
	tHalf = SetTimer(OneOneHalfTimer, 500, true)
	tQuarter = SetTimer(OnQuarterSecondTimer, 250, true)
	tSecond = SetTimer(OnSecondTimer, 1000, true)
	
	GuiMsg(playerid, Prze³adowa³eœ wszystkie timery, zobaczymy co siê stanie!, 1)*/
	
	GuiMsg(playerid, Komendka wycofana, wyginaj st¹d!, 1)
	
	return 1
)

CMD:clearhouses(playerid, params())
(
	if(PlayerCache(playerid)(pGID) != 53835)
	(
		GuiMsg(playerid, Nie mo¿esz u¿yæ tej komendy!, 1)
		return 1
	)
	
	count = 0, string(128)
	
	for(i = 0  i ( MAX_DOORS i++)
	(
		if(DoorData(i)(dOwnerType) == OWNER_PLAYER)
		(
			DeleteDoor(i)
			count++
		)
	)
	
	format(string, sizeof(string), Wyczyszczono %d mieszkan., count)
	GuiMsg(playerid, string, 0)
	return 1
)

CMD:volounteer(playerid, params())
(	
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		return 1
	)
	
	
	target_id
	if(sscanf(params, d, target_id))
	(
		hrp_Tip(playerid, /volounteer (ID Gracza))
		return 1
	)
	
	if(!Logged(target_id))
	(
		GuiMsg(playerid, Ten gracz nie jest zalogowany., 1)
		return 1
	)
	
	GuiMsg(playerid, Wskazany gracz wszed³ w³aœnie na s³u¿bê., 0)
	
	return cmd_duty(target_id, support)
)

/*CMD:hardban(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Nie posiadasz uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	target_id
	if(sscanf(params, d, target_id))
	(
		hrp_Tip(playerid, /hardban (ID Gracza))
		return 1
	)
	
	if(!Logged(target_id))
	(
		GuiMsg(playerid, Taki gracz nie jest zalogowany., 1)
		return 1
	)
	
	serial(100)
	gpci(target_id, serial, sizeof(serial))
	hrp_HardwareBan(playerid, target_id, serial)
	hrp_Ban(target_id, playerid, Banicja HB, 0)
	
	return 1
)*/

CMD:getserial(playerid, params())
(
	// Test
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Nie posiadasz uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	target_id
	if(sscanf(params, d, target_id))
	(
		hrp_Tip(playerid, /getserial (ID Gracza))
		return 1
	)
	
	if(!Logged(target_id))
	(
		GuiMsg(playerid, Taki gracz nie jest zalogowany., 1)
		return 1
	)
	
	serial(100), output(256)
	gpci(target_id, serial, sizeof(serial))
	format(output, sizeof(output), Serial gracza %s (%d) to: %s, PlayerName(target_id), target_id, serial)
	SendClientMessage(playerid, COLOR_GREEN, output)
	return 1
)

CMD:getname(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ( 1 && PlayerCache(playerid)(pAdmin) ) -1)
	(
		GuiMsg(playerid, Nie posiadasz uprawnieñ do u¿ycia tej komendy., 0)
		return 1
	)
	
	player_uid
	if(sscanf(params, d, player_uid))
	(
		hrp_Tip(playerid, /getname (UID Gracza))
		return 1
	)
	
	buffer(256), targetName(MAX_PLAYER_NAME), bool:isConnected = false
	format(buffer, sizeof(buffer), SELECT char_name FROM hrp_characters WHERE char_uid = %d, player_uid)
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		mysql_fetch_string(targetName)
		mysql_free_result()
	)
	else
	(
		mysql_free_result()
		GuiMsg(playerid, Taki gracz nie istnieje., 1)
		return 1
	)
	
	if(!strlen(targetName))
		return 1
	
	format(buffer, sizeof(buffer), ) Istnieje gracz %s (UID: %d), targetName, player_uid)
	SendClientMessage(playerid, COLOR_ADMIN, buffer)
	
	for(i = 0  i ( MAX_PLAYERS i++)
	(
		if(PlayerCache(i)(pUID) == player_uid)
		(
			format(buffer, sizeof(buffer), ) Nawet jest ONLINE (ID: %d), i)
			SendClientMessage(playerid, COLOR_ADMIN, buffer)
			isConnected = true
			break
		)
	)
	
	if(!isConnected)
	(
		format(buffer, sizeof(buffer), ) Ale niestety nie jest pod³¹czony)
		SendClientMessage(playerid, COLOR_ADMIN, buffer)
	)
	
	return 1
)

CMD:godmode(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ( 1 && PlayerCache(playerid)(pAdmin) ) -1)
	(
		GuiMsg(playerid, Nie masz uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	if(PlayerCache(playerid)(pGod))
	(
		PlayerCache(playerid)(pGod) = false
		GuiMsg(playerid, Wy³¹czy³eœ tryb nieœmiertelnoœci., 0)
	)
	else
	(
		PlayerCache(playerid)(pGod) = true
		GuiMsg(playerid, W³¹czy³eœ tryb nieœmiertelnoœci., 0)
	)
	return 1
)

// Hamulec rêczny wœród botów
CMD:kickallbots(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ( 1 && PlayerCache(playerid)(pAdmin) ) -1)
	(
		GuiMsg(playerid, Nie masz uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	for(i = 0  i ( MAX_PLAYERS i++)
	(
		if(IsPlayerNPC(i))
		(
			Kick(i)
		)
	)
	
	GuiMsg(playerid, Wyjeba³eœ wszystkie nieludzkie stworzenia!\nMo¿esz czuæ siê jak katolik który zastopowa³ sztuczn¹ inteligencjê., 0)
	return 1
)

CMD:toveh(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Nie posiadasz uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	target_id, vehicle_id
	if(sscanf(params, dd, target_id, vehicle_id))
	(
		hrp_Tip(playerid, /toveh (ID Gracza) (ID pojazdu) - umieszcza gracza w pojezdzie)
		return 1
	)
	
	PutPlayerInVehicle(target_id, vehicle_id, 1)
	return 1
)

CMD:scena(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Brak uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	Float:radius = 0.0
	if(sscanf(params, f, radius))
	(
		hrp_Tip(playerid, /scena (Zasiêg))
		return 1
	)
	
	GuiMsg(playerid, Pomyœlnie utworzono scenê!, 0)
	GetPlayerPos(playerid, scenePosX, scenePosY, scenePosZ)
	sceneWorld = GetPlayerVirtualWorld(playerid)
	sceneRadius = radius
	sceneWorks = false
	
	return 1
)

CMD:scenalink(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1 && sceneDJ != playerid)
	(
		GuiMsg(playerid, Brak uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	link(128)
	if(sscanf(params, s(128), link))
	(
		hrp_Tip(playerid, /scenelink (Link do streama))
		return 1
	)
	
	format(sceneStream, sizeof(sceneStream), %s, link)
	GuiMsg(playerid, Zmieni³eœ aktualny stream!, 0)
	sceneWorks = true
	
	foreach(Player, i)
	(
		if(isScened(i))
		(
			PlayAudioStreamForPlayer(i, sceneStream)
		)
	)
	
	return 1
)

CMD:setdj(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Brak uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	target_id
	if(sscanf(params, d, target_id))
	(
		hrp_Tip(playerid, /setdj (ID Gracza))
		return 1
	)
	
	if(!Logged(target_id))
	(
		GuiMsg(playerid, Podano b³êdne ID Gracza!, 1)
		return 1
	)
	
	sceneDJ = target_id
	GuiMsg(playerid, Pomyœlnie ustawiono nowego DJa sceny., 0)
	return 1
)

CMD:animka(playerid, params())
(
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY)
	return 1
)

CMD:dzegary(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Brak dostêpu., 1)
		return 1
	)
	
	if(!printTimers)
	(
		printTimers = true
		GuiMsg(playerid, W³¹czy³eœ logowanie zegarów., 0)
	)
	else
	(
		printTimers = false
		GuiMsg(playerid, Wy³¹czy³eœ logowanie zegarów., 0)
	)
	
	return 1
)

CMD:blint2(playerid, params())
(
	// Taka tam niepotrzebna komenda, na czas debuga.
	if(PlayerCache(playerid)(pGID) != 53835)
	(
		return 1
	)
	
	for(i = 0  i ( 200 i ++)
	(
		mysql_query_format(INSERT INTO hrp_lottery VALUES(NULL, %d), PlayerCache(playerid)(pUID))
	)
	
	GuiMsg(playerid, Gotowe, 0)
	
	return 1
)

CMD:testosblintos(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
		return 1
		
	for(i = 0 i ( MAX_OBJECTS i++)
	(
		if(IsValidDynamicObject(i))
		(
			if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, i, E_STREAMER_WORLD_ID, GetPlayerVirtualWorld(playerid)))
			(
				Float:Pos(3)
				GetDynamicObjectPos(i, Pos(0), Pos(1), Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid, 30.0, Pos(0), Pos(1), Pos(2)))
				(
					object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, i, E_STREAMER_EXTRA_ID)
					output(256)
					format(output, sizeof(output), UID obiektu: %d, object_uid)
					SendClientMessage(playerid, COLOR_SUPPORT, output)
				)
			)
		)
	)
	return 1
)

CMD:testosobiektos(playerid, params())
(
	if(PlayerCache(playerid)(pGID) != 53835)
	(
		GuiMsg(playerid, To jest bardzo ale to bardzo testowa komenda, Ty nie powinieneœ chyba jej u¿ywaæ?, 1)
		return 1
	)
	
	how_many = strval(params)
	if(how_many ( 0 || how_many ) 70000)
	(
		GuiMsg(playerid, Wprowadzono b³êdn¹ wartoœæ., 1)
		return 1
	)
	
	if(GetPlayerDoorID(playerid) == INVALID_DOOR_ID)
	(
		GuiMsg(playerid, Koniecznie musisz byæ w interiorze, by u¿yæ tej komendy., 1)
		return 1
	)
	
	Float:Pos(3)
	GetPlayerPos(playerid, Pos(0), Pos(1), Pos(2))
	
	for(i = 0 i ( how_many i++)
	(
		CreateDynamicObject(19450, Pos(0) + 1*i, Pos(1) + 1*i, Pos(2), 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 100.0)
	)
	
	return 1
)

CMD:blint3(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Nie posiadasz uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	all_cash = slots_GetCashCount()
	Float:win_cash = (all_cash * 0.50) * (0.50 + float(random(1000) / 2000))
	
	message(128)
	format(message, sizeof(message), Symulacja: %d, floatround(win_cash))
	
	SendClientMessage(playerid, 0xFFFFFFAA, message)
	return 1
)

// Komenda, na focusowanie na s³u¿bie
CMD:focus(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		GuiMsg(playerid, Nie masz uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	if(PlayerCache(playerid)(pFocusedID) != INVALID_PLAYER_ID)
	(
		PlayerCache(playerid)(pFocusedID) = INVALID_PLAYER_ID
		GuiMsg(playerid, Przesta³eœ skupiaæ siê na graczu.\nOd teraz ka¿dy bêdzie móg³ do Ciebie napisaæ., 0)
		return 1
	)
	
	if(isnull(params))
	(
		hrp_Tip(playerid, /focus (ID Gracza))
		return 1
	)
	
	focused_id = strval(params)
	if(!IsPlayerConnected(focused_id))
	(
		GuiMsg(playerid, Podano b³êdne ID gracza., 1)
		return 1
	)
	
	if(!Logged(focused_id) || !Spawned(focused_id))
	(
		GuiMsg(playerid, Podano b³êdne ID gracza., 1)
		return 1
	)
	
	output(256)
	format(output, sizeof(output), Od teraz mo¿e do Ciebie pisaæ wy³¹cznie gracz %s (ID: %d) - wpisz komendê raz jeszcze, by to wy³¹czyæ., PlayerName(focused_id), focused_id)
	GuiMsg(playerid, output, 0)
	
	PlayerCache(playerid)(pFocusedID) = focused_id
	return 1
)

CMD:celebryta(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		GuiMsg(playerid, Nie masz uprawnieñ do wykonania tej komendy., 1)
		return 1
	)
	
	target_id
	if(sscanf(params, d, target_id))
	(
		hrp_Tip(playerid, /celebryta (ID Gracza))
		return 1
	)
	
	if(!IsPlayerConnected(target_id))
	(
		GuiMsg(playerid, Gracz o podanym ID nie jest zalogowany., 1)
		return 1
	)
	
	if(!Logged(target_id) || !Spawned(target_id))
	(
		GuiMsg(playerid, Podano b³êdne ID gracza., 1)
		return 1
	)
	
	if(PlayerCache(target_id)(pCeleb))
	(
		// Je¿eli jest celebryt¹
		mysql_query_format(DELETE FROM hrp_celebs WHERE cb_char = %d, PlayerCache(target_id)(pUID))
		GuiMsg(playerid, Odebra³eœ status celebryty graczowi!, 0)
		GuiMsg(target_id, Odebrano Ci status celebryty., 0)
		PlayerCache(target_id)(pCeleb) = false
	)
	else
	(
		// Je¿eli nie jest celebryt¹ to nadaj status
		mysql_query_format(INSERT INTO hrp_celebs VALUES(NULL, %d), PlayerCache(target_id)(pUID))
		GuiMsg(playerid, Nada³eœ status celebryty graczowi!, 0)
		GuiMsg(target_id, Nadano Ci status celebryty., 0)
		PlayerCache(target_id)(pCeleb) = true
	)
	
	GetPlayerFameStatus(target_id)
	return 1
)

CMD:adminroom(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		GuiMsg(playerid, Nie masz uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	SetPlayerVirtualWorld(playerid, 1216)
	SetPlayerPos(playerid, 1950.3243,-2364.1445,13.6028)
	SetPlayerFacingAngle(playerid, 180.0)
	GuiMsg(playerid, Przenios³eœ siê do pomieszczenia dla administratorów., 0)
	return 1
)

CMD:ar(playerid, params()) return cmd_adminroom(playerid, params)

/*
	Do usuniêcia bêdzie ta komenda
	zmienna w configu IS_PRIMA(..)
	i warunek w LoadVehicle
*/
CMD:primaaprilis(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Co?, 0)
		return 1
	)
	
	if(!IS_PRIMA_APRILIS)
	(
		IS_PRIMA_APRILIS = true
		GuiMsg(playerid, W³¹czy³eœ tryb prima aprilis., 1)
	)
	else
	(
		IS_PRIMA_APRILIS = false
		GuiMsg(playerid, Wy³¹czy³eœ tryb prima aprilis., 1)
	)
	
	return 1
)
