CMD:pojazd(playerid, params())
(
	if(PlayerCache(playerid)(pGamePoints) ( 50)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie przegra³eœ jeszcze 5 godzin na serwerze i dlatego nie pozwalamy Ci u¿ywaæ pojazdów. Nie martw siê, Twój pojazd profilowy dalej nale¿y do Ciebie i bêdziesz go móg³ u¿ywaæ po przegraniu 5 godzin., OK, )
		return 1
	)
	type(32), varchar(128)
	if(sscanf(params, s(32)S()(128), type, varchar))
	(
		if(IsPlayerInAnyVehicle(playerid))
		(
			vehid = GetPlayerVehicleID(playerid)
			if(GetVehicleModel(vehid) == 574)
			(
				return 1
			)
	   		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
				return 1
			)
			if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
			(
				if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
					return 1
				)
			)
   			list_manage(128)
   			if(GetVehicleBonnetStatus(vehid) == 1)	strcat(list_manage, 1 - Zamknij maskê\n)
			else									strcat(list_manage, 1 - Otwórz maskê\n)

			if(GetVehicleBootStatus(vehid) == 1)	strcat(list_manage, 2 - Zamknij baga¿nik\n)
			else									strcat(list_manage, 2 - Otwórz baga¿nik\n)

			if(GetVehicleLightsStatus(vehid) == 1)	strcat(list_manage, 3 - Wy³¹cz œwiat³a\n)
			else									strcat(list_manage, 3 - W³¹cz œwiat³a\n)

			strcat(list_manage, 4 - W³asna rejestracja\n)
   			strcat(list_manage, 5 - Opcje CB radio)

 			ShowPlayerDialog(playerid, D_MANAGE_VEH, DIALOG_STYLE_LIST, Zarz¹dzanie pojazdem, list_manage, Wybierz, Anuluj)
	   		return 1
		)
		hrp_Tip(playerid, /pojazd (lista | namierz | zaparkuj | tuning | przypisz | zamknij | info | dodatki))
		return 1
	)
	/*if(!strcmp(type, dodatki, true))
	(
		if(!IsPlayerInAnyVehicle(playerid))
		(
			GuiMsg(playerid,Musisz byæ w pojeŸdzie by u¿yæ tej komendy.,1)
			return 1
		)

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie jako kierowca, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(playerid)
		if(GetVehicleModel(vehid) == 574)
		(
			return 1
		)
   		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
				return 1
			)
		)

		if(!IsVehicleTuned(vehid))
		(
			GuiMsg(playerid,Ten pojazd nie posiada ¿adnych dodatków.,0)
			return 1
		)

		GetVehicleTune(playerid,vehid)
		return 1
	)*/
	if(!strcmp(type, lista, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			ShowVehicleList(playerid)
			return 1
		)
   		if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
		(
   			ShowVehicleList(playerid)
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
		ShowVehicleListForPlayer(playerid, giveplayer_id)
		return 1
	)
	if(!strcmp(type, namierz, true))
	(
		if(Checkpoint(playerid))
		(
			DisablePlayerCheckpoint(playerid)

			Checkpoint(playerid) = 0

   			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Namierzanie zosta³o wy³¹czone., OK, )
			return 1
		)
		list_veh(256)
		foreach(Vehicles, vehid)
		(
			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) == PlayerCache(playerid)(pUID) && CarInfo(vehid)(cSpawned))
			(
				format(list_veh, sizeof(list_veh), %s\n%d\t\t%s, list_veh, vehid, CarInfo(vehid)(cName))
			)
		)
		if(strlen(list_veh) != 0)
		(
			ShowPlayerDialog(playerid, D_LIST_SPAWNED_CARS, DIALOG_STYLE_LIST, Pojazdy zespawnowane:, list_veh, Namierz, Zamknij)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz ¿adnych pojazdów zespawnowanych w tym momencie., OK, )
		)
		return 1
	)
	if(!strcmp(type, zaparkuj, true))
	(
 		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie jako kierowca, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(playerid)
		if(GetVehicleModel(vehid) == 574)
		(
			return 1
		)
   		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
				return 1
			)
		)
		if(!IsParkingPlaceFree(vehid))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, To miejsce parkingowe jest ju¿ zajête., OK, )
			return 1
		)
		vehuid = CarInfo(vehid)(cUID)

		GetVehiclePos(vehid, CarInfo(vehid)(cPosX), CarInfo(vehid)(cPosY), CarInfo(vehid)(cPosZ))
		GetVehiclePos(vehid, CarInfo(vehid)(cEPosX), CarInfo(vehid)(cEPosY), CarInfo(vehid)(cEPosZ))
		GetVehicleZAngle(vehid, CarInfo(vehid)(cPosA))

		CarInfo(vehid)(cInteriorID) = GetPlayerInterior(playerid)
		CarInfo(vehid)(cWorldID) = GetPlayerVirtualWorld(playerid)

		SaveVehicle(vehid, SAVE_VEH_POS)

		seatid = GetPlayerVehicleSeat(playerid)

		UnspawnVehicle(vehuid)
		vehid = SpawnVehicle(vehuid)

		ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))
		PlayerCache(playerid)(pLastVeh) = vehid

		PutPlayerInVehicle(playerid, vehid, seatid)
		OnVehicleSpawn(vehid)

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Pojazd zosta³ zaparkowany pomyœlnie., OK, )
		return 1
	)
	if(!strcmp(type, zamknij, true) || !strcmp(type, z, true))
	(
	 	vehid = GetClosestVehicle(playerid)
		if(vehid ) 0 && vehid ( MAX_VEHICLES)
		(
			if(CarInfo(vehid)(cOwnerType) == OWNER_NONE && !PlayerCache(playerid)(pAdmin))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczyków do tego pojazdu., OK, )
				return 1
			)
			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
			(
				if(CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID) && !HavePlayerVehicleKeys(playerid, vehid))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczyków do tego pojazdu., OK, )
					return 1
				)
			)
			if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
			(
				if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczyków do tego pojazdu., OK, )
					return 1
				)
			)
			Float:VehX, Float:VehY, Float:VehZ
			GetVehiclePos(vehid, VehX, VehY, VehZ)

			if(CarInfo(vehid)(cLocked))
			(
				GameTextForPlayer(playerid, ~w~Pojazd ~g~otwarty, 4000, 6)

				if(CarInfo(vehid)(cAccess) & VEH_ACCESS_ALARM)
				(
					ApplyAnimation(playerid, HEIST9, Use_SwipeCard, 4.1, 0, 0, 0, 0, 0, 1)

					// Audio alarmu
					foreach(Player, i)
					(
						if(Logged(i) && Spawned(i))
						(
							if(IsPlayerInRangeOfPoint(i, 10.0, VehX, VehY, VehZ))
							(
								// Miejsce na audio alarmu
								//audio = Audio_Play(i, AUDIO_ALARM)
								//Audio_Set3DPosition(i, audio, VehX, VehY, VehZ, 10.0)
							)
						)
					)
				)
				else
				(
					ApplyAnimation(playerid,INT_HOUSE, wash_up, 4.1, 0, 0, 0, 0, 0, 1)
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0)
				)

				CarInfo(vehid)(cLocked) = false
				SetVehicleLock(vehid, false)
			)
			else
			(
				GameTextForPlayer(playerid, ~w~Pojazd ~r~zamkniety, 4000, 6)

				if(CarInfo(vehid)(cAccess) & VEH_ACCESS_ALARM)
				(
					ApplyAnimation(playerid, HEIST9, Use_SwipeCard, 4.1, 0, 0, 0, 0, 0, 1)

					// Audio alarmu
					foreach(Player, i)
					(
						if(Logged(i) && Spawned(i))
						(
							if(IsPlayerInRangeOfPoint(i, 10.0, VehX, VehY, VehZ))
							(
								// Miejsce na audio alarmu
								//audio = Audio_Play(i, AUDIO_ALARM)
								//Audio_Set3DPosition(i, audio, VehX, VehY, VehZ, 10.0)
							)
						)
					)
				)
				else
				(
					ApplyAnimation(playerid,INT_HOUSE, wash_up, 4.1, 0, 0, 0, 0, 0, 1)
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0)
				)

				CarInfo(vehid)(cLocked) = true
				SetVehicleLock(vehid, true)
			)
			SaveVehicle(vehid, SAVE_VEH_LOCK)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wyst¹pi³ problem z Twoim pojazdem. Spróbuj go odspawnowaæ i zespawnowaæ ponownie.\nJe¿eli problem bêdzie dalej wystêpowa³, skontaktuj siê z Administratorem., OK, )
		)
		return 1
	)
	if(!strcmp(type, info, true))
	(
		if(!IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(playerid)
   		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ wymaganych do tej czynnoœci., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ wymaganych do tej czynnoœci., OK, )
				return 1
			)
		)
		ShowPlayerVehicleInfo(playerid, vehid)
		return 1
	)
	if(!strcmp(type, tuning, true))
	(
 		if(!IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(playerid)
		if(GetVehicleModel(vehid) == 574)
		(
			return 1
		)
   		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ wymaganych do tej czynnoœci., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ wymaganych do tej czynnoœci., OK, )
				return 1
			)
		)
		data(64), list_tuning_items(256),
			item_uid, item_value1, item_name(32)

		mysql_query_format(SELECT item_uid, item_value1, item_name FROM hrp_items WHERE item_vehuid = %d, CarInfo(vehid)(cUID))

		mysql_store_result()
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)dds(32), item_uid, item_value1, item_name)
			format(list_tuning_items, sizeof(list_tuning_items), %s\n%d\t%d\t%s, list_tuning_items, item_uid, item_value1, item_name)
		)
		mysql_free_result()
		if(strlen(list_tuning_items))
		(
			ShowPlayerDialog(playerid, D_UNMOUNT_TUNING, DIALOG_STYLE_LIST, Zamontowane czêœci:, list_tuning_items, Odmontuj, Zamknij)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych zamontowanych czêœci., OK, )
		)
		return 1
	)
	if(!strcmp(type, przypisz, true))
	(
		if(!IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(playerid)
		if(GetVehicleModel(vehid) == 574)
		(
			return 1
		)
   		if(CarInfo(vehid)(cOwnerType) != OWNER_PLAYER || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ wymaganych do tej czynnoœci., OK, )
			return 1
		)
		if(CarInfo(vehid)(cBlocked))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz przypisaæ tego pojazdu pod grupê., OK, )
			return 1
		)
		list_groups(256), group_id_fix
		format(list_groups, sizeof(list_groups), (C0C0C0)Slot\tNazwa oraz UID grupy(FFFFFF))

		for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
		(
			if(PlayerGroup(playerid)(slot)(gUID))
  			(
  				group_id_fix = PlayerGroup(playerid)(slot)(gID)
				format(list_groups, sizeof(list_groups), %s\n%d\t%s (%d), list_groups, slot + 1, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
 			)
		)
		ShowPlayerDialog(playerid, D_ASSIGN_VEH, DIALOG_STYLE_LIST, Pojazd » Przypisz pod grupê, list_groups, Wybierz, Anuluj)
		return 1
	)
	if(!strcmp(type, opis, true))
	(
		if(!IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(playerid)
		if(GetVehicleModel(vehid) == 574)
		(
			return 1
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
				return 1
			)
		)
		desc(128)
		if(sscanf(varchar, s(128), desc))
		(
			hrp_Tip(playerid, /v opis (Treœæ opisu) | Aby usun¹æ opis, u¿yj komendy /opis usun.)
			return 1
		)
		
		format(PlayerCache(playerid)(pDescTagText), 128, %s, DescWrap(desc))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Ustalono nowy opis pojazdu:, DescWrap(desc), OK, )
		return 1
	)
	return 1
)

CMD:reczny(playerid, params())
(
	if(!IsPlayerInAnyVehicle(playerid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie, aby móc u¿yæ tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pBW) || PlayerCache(playerid)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skorzystaæ teraz z tej komendy., OK, )
		return 1
	)

	vehid = GetPlayerVehicleID(playerid)

	if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
		return 1
	)
	if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
	(
		if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
			return 1
		)
	)
	if(CarInfo(vehid)(cHealth) ( 600.0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Hamulec rêczny w tym pojeŸdzie nie funkcjonuje prawid³owo., OK, )
		return 1
	)
	if(GetVehicleEngineStatus(vehid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz zgasiæ pojazd aby zaci¹gn¹æ hamulec rêczny., OK, )
		return 1
	)

	GetVehiclePos(vehid, CarInfo(vehid)(cEPosX), CarInfo(vehid)(cEPosY), CarInfo(vehid)(cEPosZ))
	if(CarInfo(vehid)(cEBreak))
	(
		CarInfo(vehid)(cEBreak) = false
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Hamulec rêczny zosta³ opuszczony., OK, )
	)
	else
	(
		CarInfo(vehid)(cEBreak) = true
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Hamulec rêczny zosta³ zaci¹gniêty., OK, )
	)
	return 1
)

CMD:radio(playerid, params())
(
	if(IsPlayerInAnyVehicle(playerid))
	(
		vehid = GetPlayerVehicleID(playerid)
		if(!PlayerCache(playerid)(pMusicPlayerUID))
		(
			strmid(CarInfo(vehid)(cAudioURL), , 0, 0, 0)
			foreach(Player, i)
			(
				if(IsPlayerInAnyVehicle(i))
				(
					if(GetPlayerVehicleID(i) == vehid)
					(
						if(!PlayerCache(i)(pMusicPlayerUID))
						(
							//Audio_Stop(i, PlayerCache(i)(pAudioHandle))
							//Audio_StopRadio(i)
							StopAudioStreamForPlayer(i)
						)
					)
				)
			)
		)
	)
	return 1
)

CMD:v(playerid, params()) return cmd_pojazd(playerid, params)
CMD:auto(playerid, params()) return cmd_pojazd(playerid, params)

CMD:magazyn(playerid, params())
(
	doorid = GetPlayerDoorID(playerid)
	if(doorid == INVALID_DOOR_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy., OK, )
		return 1
	)
	if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
		return 1
	)
	if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
		return 1
	)
	if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
	(
		if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
	)

	LoadProductsList(playerid)
	return 1
)

CMD:drzwi(playerid, params())
(
	type(32), varchar(32), string(128), doorid = GetPlayerDoorID(playerid)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /drzwi (zamknij | info | schowek | opcje | dodatki | wyjscie))
	 	return 1
	)
	
	if(!strcmp(type, wyjscie, true))
	(
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
   		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
				return 1
			)
		)
		if(DoorData(doorid)(dDoorEdited) )= 1)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Te drzwi wykorzysta³y ju¿ dzienny limit zmiany pozycji wyjœcia, spróbuj jutro., OK, )
			return 1
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Sukces, zmieniles pozycje wyjscia z budynku., OK, )
		
		GetPlayerPos(playerid, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ))
		GetPlayerFacingAngle(playerid, DoorData(doorid)(dExitAng))
		
		DoorData(doorid)(dExitInt) = GetPlayerInterior(playerid)
		SaveDoor(doorid, SAVE_DOOR_EXIT)
		
		printf((door) Gracz %s (uid: %d) zmienil pozycje wyjscia w drzwiach (uid: %d)., PlayerName(playerid), PlayerCache(playerid)(pUID), DoorData(doorid)(dUID))
		return 1
	)
	if(!strcmp(type, dodatki, true))
	(
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
   		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
				return 1
			)
		)

		ShowPlayerDoorAddons(playerid, doorid)
		return 1
	)
	if(!strcmp(type, info, true))
	(
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
   		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
				return 1
			)
		)
		ShowPlayerDoorInfo(playerid, doorid)
		return 1
	)
	if(!strcmp(type, zamknij, true) || !strcmp(type, z, true))
	(
		foreach(Doors, d)
		(
			if(DoorData(d)(dUID))
			(
				if((IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(d)(dEnterX), DoorData(d)(dEnterY), DoorData(d)(dEnterZ)) && GetPlayerVirtualWorld(playerid) == DoorData(d)(dEnterVW)) || (IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(d)(dExitX), DoorData(d)(dExitY), DoorData(d)(dExitZ)) && GetPlayerVirtualWorld(playerid) == DoorData(d)(dExitVW)))
				(
					if(DoorData(d)(dOwnerType) == OWNER_NONE)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczy do tego budynku., OK, )
						return 1
					)
					if(DoorData(d)(dOwnerType) == OWNER_PLAYER && DoorData(d)(dOwner) != PlayerCache(playerid)(pUID) && DoorData(d)(dUID) != PlayerCache(playerid)(pHouse))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczy do tego budynku., OK, )
						return 1
					)
					if(DoorData(d)(dOwnerType) == OWNER_GROUP)
					(
						if(!IsPlayerPermissedGroup(playerid, DoorData(d)(dOwner), PERM_DOORS))
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczy do tego budynku., OK, )
							return 1
						)
					)
					if(DoorData(d)(dLocked))
					(
						GameTextForPlayer(playerid, ~w~Drzwi ~g~otwarte, 4000, 6)

						ApplyAnimation(playerid,INT_HOUSE, wash_up, 4.1, 0, 0, 0, 0, 0, 1)
						PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0)

						DoorData(d)(dLocked) = 0

						SaveDoor(d, SAVE_DOOR_LOCK)
					)
					else
					(
						GameTextForPlayer(playerid, ~w~Drzwi ~r~zamkniete, 4000, 6)

						ApplyAnimation(playerid,INT_HOUSE, wash_up, 4.1, 0, 0, 0, 0, 0, 1)
						PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0)

						DoorData(d)(dLocked) = 1

						SaveDoor(d, SAVE_DOOR_LOCK)
					)
					break
				)
			)
		)
		return 1
	)
	if(!strcmp(type, schowek, true))
	(
 		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
   		if(DoorData(doorid)(dOwnerType) == OWNER_NONE && PlayerCache(playerid)(pAdmin) != 1)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID) && PlayerCache(playerid)(pAdmin) != 1)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP && PlayerCache(playerid)(pAdmin) != 1)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
				return 1
			)
		)
		data(64), list_items(512),
			item_uid, item_name(32)

		mysql_query_format(SELECT item_uid, item_name FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_SAFE, DoorData(doorid)(dUID))

		mysql_store_result()
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)ds(32), item_uid, item_name)
			format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, item_uid, item_name)
		)
		mysql_free_result()
		if(strlen(list_items))
		(
			format(string, sizeof(string), %s (SampID: %d, UID: %d) » Schowek, DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
			ShowPlayerDialog(playerid, D_REMOVE_ITEM_SAFE, DIALOG_STYLE_LIST, string, list_items, Wyjmij, Anuluj)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych przedmiotów w schowku., OK, )
		)
		return 1
	)
	if(!strcmp(type, opcje, true))
	(
		temp_doorid
		if(!sscanf(params, d, temp_doorid))
		(
			doorid = temp_doorid
		)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy., OK, )
			return 1
		)
   		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
				return 1
			)
		)
		format(string, sizeof(string), %s (SampID: %d, UID: %d) » Opcje, DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		ShowPlayerDialog(playerid, D_DOOR_OPTIONS, DIALOG_STYLE_LIST, string, 1. Zmieñ nazwê drzwi\n2. Ustal koszt wstêpu\n3. Przypisz drzwi\n4. Muzyka spoza gry\n5. Wczytaj obiekty\n6. Poka¿ magazyn\n7. Mo¿liwoœæ przejazdu\n8. Dzwonek do drzwi\n9. Czas w interiorze\n10. Usuñ obiekty, Wybierz, Anuluj)
		return 1
	)
	return 1
)

CMD:dzwonek(playerid, params())
(
	doorid = GetDoorID(GetPlayerVirtualWorld(playerid)), string(128), send_counter = 0

	if(doorid == INVALID_DOOR_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy., OK, )
		return 1
	)
	if(!DoorData(doorid)(dBell))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Te drzwi nie maj¹ dzwonka., OK, )
		return 1
	)

	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pGroupDuty))
			(
				group_id_fix = GetPlayerDutyGroupID(i)
				if(DoorData(doorid)(dOwner) == GroupData(group_id_fix)(gUID))
				(
					format(string, sizeof(string), ** W %s mo¿na us³yszeæ rozbrzmiewaj¹cy dŸwiêk dzwonka. **, DoorData(doorid)(dName))
					SendClientMessage(i, COLOR_DO, string)
					send_counter ++
				)
			)
		)
	)

	format(string, sizeof(string), ** Dzwiêk Twojego dzwonka us³ysza³o %d osób. **, send_counter)
	SendClientMessage(playerid, COLOR_INFO, string)

	return 1
)

CMD:d(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_DOC && GroupData(group_id_fix)(gType) != GROUP_ARMY && GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_MEDICAL && GroupData(group_id_fix)(gType) != GROUP_FBI && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skorzystaæ teraz z tej komendy., OK, )
		return 1
	)
	text(128), string(256)
	if(sscanf(params, s(128), text))
	(
		hrp_Tip(playerid, /d (Tekst))
		return 1
	)
	text(0) = chrtoupper(text(0))
	format(string, sizeof(string), ** (%s) %s: %s **, GroupData(group_id_fix)(gTag), PlayerName(playerid), text)

	other_group_id_fix
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pGroupDuty))
			(
				other_group_id_fix = GetPlayerDutyGroupID(i)
				if(GroupData(other_group_id_fix)(gType) == GROUP_DOC || GroupData(other_group_id_fix)(gType) == GROUP_ARMY || GroupData(other_group_id_fix)(gType) == GROUP_MEDICAL || GroupData(other_group_id_fix)(gType) == GROUP_POLICE || GroupData(other_group_id_fix)(gType) == GROUP_FIREDEPT || GroupData(other_group_id_fix)(gType) == GROUP_FBI)
		   		(
					SendClientMessage(i, COLOR_KREM, string)
				)
			)
		)
	)
	format(string, sizeof(string), %s mówi (radio): %s, PlayerName(playerid), text)
	ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
	return 1
)

CMD:u(playerid, params())
(
	if(PlayerCache(playerid)(pCuffed) != INVALID_PLAYER_ID && PlayerCache(playerid)(pCuffedStill) != INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿ywaæ ekwipunku podczas gdy jesteœ skuty., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGymType) != TRAIN_NONE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz korzystaæ z ekwipunku podczas treningu., OK, )
		return 1
	)
	item_uid, varchar(64)
	if(sscanf(params, dS()(24), item_uid, varchar))
	(
		ListPlayerItems(playerid, MANAGE_TYPE_USE)
		return 1
	)
	itemid = GetItemID(item_uid), string(256)
	if(!ItemInfo(itemid)(iUID) || ItemInfo(itemid)(iPlace) != PLACE_PLAYER || ItemInfo(itemid)(iOwner) != PlayerCache(playerid)(pUID))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Wprowadzono nieprawid³owe UID przedmiotu., OK, )
		return 1
	)
	if(ItemInfo(itemid)(iType) == ITEM_WEAPON || ItemInfo(itemid)(iType) == ITEM_PAINT)
	(
		sub(24)
		if(sscanf(varchar, s(24), sub))
		(
			if(!ItemInfo(itemid)(iUsed))
  			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Pomoc, /u (UID przedmiotu) (Dodatkowy parametr)\n\nW miejsce dodatkowego parametru nale¿y wpisaæ sk¹d broñ zostanie wyjêta.\nPrzyk³ad: /u 1998 z kabury\n\nGdzie \z kabury\ jest dodatkowym parametrem.\nPo u¿yciu tego parametru skrypt sam u³o¿y treœæ /me., OK, )
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Pomoc, /u (UID przedmiotu) (Dodatkowy parametr)\n\nW miejsce dodatkowego parametru nale¿y wpisaæ gdzie broñ zostanie schowana.\nPrzyk³ad: /u 1998 do kabury\n\nGdzie \do kabury\ jest dodatkowym parametrem.\nPo u¿yciu tego parametru skrypt sam u³o¿y treœæ /me., OK, )
			)
			return 1
		)
  		if(strfind(sub, ., true, strlen(sub) - 1) == -1) strcat(sub, ., sizeof(sub))

  		if(OnPlayerUseItem(playerid, itemid))
  		(
			if(ItemInfo(itemid)(iUsed))
			(
				format(string, sizeof(string), * %s wyjmuje %s %s, PlayerName(playerid), ItemInfo(itemid)(iName), sub)
				FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			)
			else
			(
				format(string, sizeof(string), * %s chowa %s %s, PlayerName(playerid), ItemInfo(itemid)(iName), sub)
	 			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			)
		)
	)
	else
	(
 		OnPlayerUseItem(playerid, itemid)
	)
	return 1
)

CMD:p(playerid, params())
(
	type(24), varchar(24), string(128)
	if(sscanf(params, s(24)S()(24), type, varchar))
	(
		switch(PlayerCache(playerid)(pInterface))
		(
			case INTERFACE_TYPE_TEXT:
			(
				ListPlayerItems(playerid, MANAGE_TYPE_ALL)
			)
			case INTERFACE_TYPE_GRAPHIC:
			(
				PlayerCache(playerid)(pItemPage) = 0
				bGUI_ListPlayerItems(playerid,0)
			)
		)
		return 1
	)
	if(!strcmp(type, podnies, true))
	(
		if(PlayerCache(playerid)(pFlood) ) 0) (
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿yæ tej komendy tak szybko., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pRaising))	return 1

		PlayerCache(playerid)(pRaising) = true
 		SetTimerEx(ListPlayerNearItems, 3000, 0, d, playerid)

		format(string, sizeof(string), * %s rozgl¹da siê., PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE, true)

		ApplyAnimation(playerid, PED, XPRESSscratch, 4.1, 0, 0, 0, 0, 0, 1)

		TextDrawSetString(Text:TextDrawMainInfo(playerid), Twoja postac ~y~rozglada sie ~w~w celu ~g~odnalezienia ~w~przedmiotow w poblizu. Odczekaj 3. sekundy.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
		return 1
	)
	if(!strcmp(type, pokaz, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /p pokaz (ID gracza))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
		   	return 1
		)
		ListPlayerItemsForPlayer(giveplayer_id, playerid)

 		format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~n~~n~~n~~y~Gotowka gracza ~r~%s~y~: ~g~$%d~y~., PlayerName(playerid), PlayerCache(playerid)(pCash))
		GameTextForPlayer(giveplayer_id, string, 6000, 3)

		format(string, sizeof(string), Pokaza³eœ swoje przedmioty dla gracza %s., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		hrp_ItemActionLog(%s (UID: %d) pokaza³ swoje przedmioty %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerRealName(giveplayer_id), PlayerCache(giveplayer_id)(pUID))
		return 1
	)
	if(!strcmp(type, lista, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			ListPlayerItems(playerid, MANAGE_TYPE_ALL)
			return 1
		)
   		if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
		(
   			ListPlayerItems(playerid, MANAGE_TYPE_ALL)
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
		ListPlayerItemsForPlayer(playerid, giveplayer_id)
		return 1
	)
	return 1
)

CMD:przedmiot(playerid, params()) return cmd_p(playerid, params)

CMD:odloz(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿ywaæ niczego oferowaæ podczas stanu nieprzytomnoœci., OK, )
		return 1
	)
	item_uid
	if(sscanf(params, d, item_uid))
	(
		SendClientMessage(playerid, COLOR_INFO, )) Musisz podaæ poprawne uid przedmiotu.)
		return 1	
	)

	itemid = GetItemID(item_uid)
	if(ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID) && ItemInfo(itemid)(iPlace) == PLACE_PLAYER)
	(
		OnPlayerDropItem(playerid, itemid, true)
		
		string(64)
		format(string, sizeof(string), ** %s rzuca coœ pod nogi. **, PlayerName(playerid))
		FlashMe(playerid, string)
		
		SendClientMessage(playerid, COLOR_INFO, )) Przedmiot zostal wyrzucony.)
		return 1
	)
	else
	(
		SendClientMessage(playerid, COLOR_INFO, )) Musisz podaæ poprawne uid przedmiotu.)
		return 1		
	)
)

CMD:oferuj(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿ywaæ niczego oferowaæ podczas stanu nieprzytomnoœci., OK, )
		return 1
	)
	type(32), varchar(64), string(256)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		format(string, sizeof(string), » pojazd)

		strcat(string, \n» przedmiot, sizeof(string))
	 	strcat(string, \n» drzwi, sizeof(string))
	 	strcat(string, \n» holowanie, sizeof(string))
	 	strcat(string, \n» vcard, sizeof(string))
	 	strcat(string, \n» produkt, sizeof(string))

	 	if(IsPlayerInGroupType(playerid, GROUP_TAXI))
	 	(
	 		strcat(string, \n» przejazd, sizeof(string))
	 	)
	 	if(IsPlayerInGroupType(playerid, GROUP_DRIVING))
	 	(
	 		strcat(string, \n» lekcja, sizeof(string))
	 	)
	 	if(IsPlayerInGroupType(playerid, GROUP_GYM))
	 	(
	 		strcat(string, \n» trening, sizeof(string))
	 	)
	 	if(IsPlayerInGroupType(playerid, GROUP_TIMBER))
	 	(
	  		strcat(string, \n» wnêtrze, sizeof(string))
			strcat(string, \n» podgl¹d, sizeof(string))
	 	)
	 	if(IsPlayerInGroupType(playerid, GROUP_POLICE))
	 	(
	  		strcat(string, \n» mandat, sizeof(string))
			strcat(string, \n» odblokowanie, sizeof(string))
	 	)
	 	if(IsPlayerInGroupType(playerid, GROUP_MEDICAL) || IsPlayerInGroupType(playerid, GROUP_FIREDEPT))
	 	(
	 		strcat(string, \n» leczenie, sizeof(string))
	 	)
	 	if(IsPlayerInGroupType(playerid, GROUP_GOV))
	 	(
			strcat(string, \n» dokument, sizeof(string))
			strcat(string, \n» biznes, sizeof(string))

			strcat(string, \n» rejestracje, sizeof(string))
			strcat(string, \n» oplata, sizeof(string))
	 	)
	 	if(IsPlayerInGroupType(playerid, GROUP_INSURANCE))
	 	(
	 		strcat(string, \n» ubezpieczenie, sizeof(string))
	 	)
		if(IsPlayerInGroupType(playerid, GROUP_PAINTBALL))
	 	(
	 		strcat(string, \n» paintball, sizeof(string))
	 	)
		if(IsPlayerInGroupType(playerid, GROUP_TAXI))
	 	(
	 		strcat(string, \n» przejazd, sizeof(string))
	 	)
		if(IsPlayerInGroupType(playerid, GROUP_WORKSHOP))
		(
	 		strcat(string, \n» tankowanie, sizeof(string))
	   		strcat(string, \n» naprawe, sizeof(string))
			strcat(string, \n» wymiane, sizeof(string))

		 	strcat(string, \n» lakierowanie, sizeof(string))
		  	strcat(string, \n» montaz, sizeof(string))
		)
		if(IsPlayerInGroupType(playerid, GROUP_SAWMILL) || IsPlayerInGroupType(playerid, GROUP_QUARRY))
		(
			strcat(string, \n» zaladowanie, sizeof(string))
		)
		if(IsPlayerInGroupType(playerid, GROUP_TIMBER))
		(
			strcat(string, \n» rozladowanie, sizeof(string))
		)
		if(PlayerCache(playerid)(pJob) == JOB_HOTDOG)
		(
	 		strcat(string, \n» hotdog, sizeof(string))
		)
		if(IsPlayerInGroupType(playerid, GROUP_HIRE))
		(
			strcat(string, \n» wypozyczenie, sizeof(string))
		)

		ShowPlayerDialog(playerid, D_OFFER_LIST, DIALOG_STYLE_LIST, Dostêpne typy ofert:, string, Wybierz, Anuluj)
		return 1
	)
	if(!strcmp(type, wypozyczenie, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)

		group_id_fix = GetPlayerDutyGroupID(playerid)

		if(!IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			GuiMsg(playerid,Nie masz odpowiednich uprawnieñ do wykonania tej komendy.,1)
			return 1
		)

		if(GroupData(group_id_fix)(gType) != GROUP_HIRE)
		(
			GuiMsg(playerid,Musisz byæ na s³u¿bie grupy, która ma uprawnienia do wypo¿yczania pojazdów.,1)
			return 1
		)

		giveplayer_id, time,  price
		if(sscanf(varchar, ddd, giveplayer_id,time,  price))
		(
			hrp_Tip(playerid, /oferuj wypozyczenie (ID gracza) (Czas (w minutach)) (Cena))
			return 1
		)
		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)

		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_HIRE_CAR, Wypozyczenie pojazdu, time, price)
	)
	if(!strcmp(type, pojazd, true))
	(
		giveplayer_id, price
		if(sscanf(varchar, dd, giveplayer_id, price))
		(
			hrp_Tip(playerid, /oferuj pojazd (ID gracza) (Cena))
			return 1
		)
		if(!IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie który chcesz sprzedaæ., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(playerid)
		if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
		(
			group_uid = CarInfo(vehid)(cOwner),
				group_id_fix = GetGroupID(group_uid)

			if(!IsPlayerPermissedGroup(playerid, group_uid, PERM_OFFER))
			(
				format(string, sizeof(string), Nie jesteœ w³aœcicielem grupy %s., GroupData(group_id_fix)(gName))
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
				return 1
			)
			if(GroupData(group_id_fix)(gType) != GROUP_AUTOSALE)
			(
				format(string, sizeof(string), %s nie jest komisem pojazdów przez co nie mo¿esz sprzedaæ tego pojazdu., GroupData(group_id_fix)(gName))
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
				return 1
			)
		)
		else
		(
			if(CarInfo(vehid)(cOwnerType) != OWNER_PLAYER || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd nie nale¿y do Ciebie., OK, )
				return 1
			)
		)
  		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
	   		return 1
		)
		if(CarInfo(vehid)(cBlocked))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz sprzedaæ tego pojazdu., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pFreeze))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz oferowaæ pojazdu, gdy Twoja postaæ jest zamro¿ona., OK, )
			return 1
		)
		if(price ( 0)
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdn¹ kwotê., OK, )
  			return 1
		)

		salonveh_premium = 0, data(8)
		mysql_query_format(SELECT salonveh_premium FROM hrp_salonveh WHERE salonveh_model = %d, CarInfo(vehid)(cModel))

		mysql_store_result()
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)d, salonveh_premium)
		)
		mysql_free_result()

		if(salonveh_premium == 1 && !PlayerCache(giveplayer_id)(pPremium))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie posiada konta premium wymaganego dla tego pojazdu., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_VEHICLE, CarInfo(vehid)(cName), vehid, price)
		return 1
	)
	if(!strcmp(type, przedmiot, true))
	(
		giveplayer_id, price, item_uid
		if(sscanf(varchar, ddd, giveplayer_id, item_uid, price))
		(
			hrp_Tip(playerid, /oferuj przedmiot (ID gracza) (UID przedmiotu) (Cena))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		itemid = GetItemID(item_uid)
		if(ItemInfo(itemid)(iPlace) != PLACE_PLAYER || ItemInfo(itemid)(iOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID przedmiotu., OK, )
			return 1
		)
		if(ItemInfo(itemid)(iUsed))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten przedmiot jest aktualnie w u¿yciu., OK, )
			return 1
		)
		if(ItemInfo(itemid)(iWeight) ) GetPlayerEqSpace(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie ma wystarczaj¹co miejsca w swoim ekwipunku., OK, )
			return 1
		)
		if(price ( 0)
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdn¹ kwotê., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_ITEM, ItemInfo(itemid)(iName), item_uid, price)
		return 1
	)
	if(!strcmp(type, produkt, true))
	(
   		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /oferuj produkt (ID gracza))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		if(GetPlayerVirtualWorld(playerid) == 0)
		(
 			foreach(Booths, boothid)
			(
				printf(Bodka id: %d| radius: %f| owner: %d| door: %d, boothid, BoothData(boothid)(bRadius), BoothData(boothid)(bOwner), BoothData(boothid)(bDoorUID))
				if(IsPlayerInRangeOfPoint(playerid, BoothData(boothid)(bRadius), BoothData(boothid)(bPosX), BoothData(boothid)(bPosY), BoothData(boothid)(bPosZ)))
				(
					dooruid = BoothData(boothid)(bDoorUID), doorid

					foreach(Doors, door)
					(
						if(DoorData(door)(dUID) == dooruid)
						(
							doorid = door
						)
					)

					if(doorid == INVALID_DOOR_ID)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wyst¹pi³ problem z magazynem Twojej budki. Zg³oœ siê do Administracji w celu naprawienia problemu., OK, )
						return 1
					)
					if(!IsPlayerPermissedGroup(playerid, BoothData(boothid)(bOwner), PERM_OFFER))
					(
			 			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, do oferowania przedmiotów z magazynu., OK, )
						return 1
					)
		   			MainPlayerTable(playerid) = giveplayer_id
					ListPlayerDoorProducts(playerid, doorid)
					return 1
				)
			)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku lub budce grupy, aby móc oferowaæ produkty z magazynu., OK, )
		)
		else
		(
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, aby móc oferowaæ produkty z magazynu., OK, )
				return 1
			)
			if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, aby móc oferowaæ produkty z magazynu., OK, )
				return 1
			)
	  		if(!IsPlayerPermissedGroup(playerid, PlayerCache(playerid)(pGroupDuty), PERM_OFFER))
			(
	 			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, do oferowania przedmiotów z magazynu., OK, )
				return 1
			)
			MainPlayerTable(playerid) = giveplayer_id
			ListPlayerDoorProducts(playerid, doorid)
		)
		return 1
	)
	if(!strcmp(type, przejazd, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_TAXI || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id, price
		if(sscanf(varchar, dd, giveplayer_id, price))
		(
			hrp_Tip(playerid, /oferuj przejazd (ID gracza) (Koszt za 100 metrów))
			return 1
		)
		if(PlayerCache(playerid)(pTaxiPassenger) != INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ przeja¿d¿ki drugiej osobie., OK, )
			return 1
		)
		if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie taksówkarskim jako kierowca, aby móc zaoferowaæ przejazd., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(playerid)
		if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie taksówkarskim jako kierowca, aby móc zaoferowaæ przejazd., OK, )
			return 1
		)
		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		if(GetPlayerState(giveplayer_id) != PLAYER_STATE_PASSENGER || GetPlayerVehicleID(giveplayer_id) != vehid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w taksówce jako pasa¿er., OK, )
			return 1
		)
		if(price ) 20)
		(
			GuiMsg(playerid, Podana kwota jest zbyt wysoka!, 1)
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_PASSAGE, Kurs Taxi, vehid, price)
		return 1
	)
	if(!strcmp(type, tankowanie, true))
	(
		/*
		if(!IsPlayerInGroupType(playerid, GROUP_WORKSHOP))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ pracownikiem ¿adnego warsztatu., OK, )
			return 1
		)
		object_id = GetClosestObject(playerid)
		if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_FUELING)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnego dystrybutora w pobli¿u., OK, )
	   		return 1
		)
		giveplayer_id, bens_type, value
		if(sscanf(varchar, udd, giveplayer_id, bens_type, value))
		(
			hrp_Tip(playerid, /oferuj tankowanie (ID gracza) (Rodzaj paliwa) (Iloœæ litrów))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		if(!IsPlayerInAnyVehicle(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w pojeŸdzie, który zamierzasz zatankowaæ., OK, )
			return 1
		)
		if(bens_type ( 0 || bens_type ) 3)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wybrano nieprawid³owy rodzaj paliwa., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(giveplayer_id)
		if((bens_type - 1) != CarInfo(vehid)(cFuelType))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wybrany rodzaj paliwa nie pasuje do tego pojazdu., OK, )
			return 1
		)
		if(value ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ iloœæ litrów., OK, )
			return 1
		)
		if(value + CarInfo(vehid)(cFuel) ) GetVehicleMaxFuel(CarInfo(vehid)(cModel)))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W baku nie zmieœci siê tyle paliwa., OK, )
			return 1
		)
		price

		if(bens_type == TYPE_BENS) 			price = floatround(value * 3.5)
		else if(bens_type == TYPE_GAS) 		price = floatround(value * 1.0)
		else if(bens_type == TYPE_DIESEL) 	price = floatround(value * 2.0)
		else if(bens_type == TYPE_AIRFUEL)  price = floatround(value * 8.0)

		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_REFUEL, Tankowanie, value, price)
		return 1
		*/

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ta funkcja nie jest ju¿ dostêpna. U¿yj komendy /tankuj, OK, )
		return 1
	)
	if(!strcmp(type, lakierowanie, true))
	(
		if(!IsPlayerInGroupType(playerid, GROUP_WORKSHOP))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ pracownikiem ¿adnego warsztatu., OK, )
			return 1
		)
		giveplayer_id, color1, color2, price
		if(sscanf(varchar, dddd, giveplayer_id, color1, color2, price))
		(
			hrp_Tip(playerid, /oferuj lakierowanie (ID gracza) (Kolor 1) (Kolor 2) (Robocizna))
			return 1
		)
		if(PlayerCache(playerid)(pSprayVeh) != INVALID_VEHICLE_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie jesteœ ju¿ w trakcie lakierowania innego pojazdu., OK, )
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		if(!IsPlayerInAnyVehicle(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w pojeŸdzie, który zamierzasz przelakierowaæ., OK, )
			return 1
		)
 		if(color1 ( 0 || color1 ) 255 || color2 ( 0 || color2 ) 255)
		(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, ID koloru nie mo¿e byæ mniejsze ni¿ 0 a tak¿e wiêksze ni¿ 255., OK, )
		 	return 1
	   	)
		if(price ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê., OK, )
			return 1
		)
		if(!WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz mieæ lakier w u¿yciu., OK, )
			return 1
		)
		itemid = GetItemID(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
		if(ItemInfo(itemid)(iType) != ITEM_PAINT)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz mieæ lakier w u¿yciu., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pSprayColor)(0) = color1
		PlayerCache(giveplayer_id)(pSprayColor)(1) = color2

		format(string, sizeof(string), Lakierowanie (%d/%d), color1, color2)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_PAINT, string, 0, price)
		return 1
	)
	if(!strcmp(type, naprawe, true))
	(
		if(!IsPlayerInGroupType(playerid, GROUP_WORKSHOP))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ pracownikiem ¿adnego warsztatu., OK, )
			return 1
		)
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /oferuj naprawe (ID gracza))
			return 1
		)
		if(PlayerCache(playerid)(pRepairVeh) != INVALID_VEHICLE_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie jesteœ ju¿ w trakcie naprawiania innego pojazdu., OK, )
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(!IsPlayerInAnyVehicle(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w pojeŸdzie, który zamierzasz naprawiaæ., OK, )
			return 1
		)
		if(GetPlayerVehicleSeat(giveplayer_id) != 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi byæ kierowc¹ pojazdu, który zamierzasz naprawiaæ., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)

		vehid = GetPlayerVehicleID(giveplayer_id), data(64)
		veh_price = -1

		mysql_query_format(SELECT salonveh_price FROM hrp_salonveh WHERE salonveh_model = %d, GetVehicleModel(vehid))
		mysql_store_result()
		mysql_fetch_row(data, |)
		sscanf(data, p(|)d, veh_price)
		mysql_free_result()

		if(veh_price == -1 || veh_price == 0)
		(
			veh_price = 23500
		)

		price, Float:var_x, Float:percent

		var_x = (CarInfo(vehid)(cMileage) * 2) + (CarInfo(vehid)(cCarfax) * 2)
		percent = varX(var_x)

		if(percent == -1)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd jest w zbyt kiepskim stanie aby go naprawiæ.\nNie mo¿emy znaleŸæ tak starych czêœci. Musisz go odrestaurowaæ., OK, )
			return 1
		)

		price = floatround(((percent * (1000-CarInfo(vehid)(cHealth)))/100) * veh_price)

		//price = 1000 - floatround(CarInfo(vehid)(cHealth), floatround_ceil)

 		if(price (= 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd jest w pe³ni sprawny., OK, )
			return 1
		)

		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_REPAIR, Naprawa, vehid, price)
		return 1
	)
	if(!strcmp(type, wymiane, true))
	(
		if(!IsPlayerInGroupType(playerid, GROUP_WORKSHOP))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ pracownikiem ¿adnego warsztatu., OK, )
			return 1
		)
		fix_type(24), giveplayer_id
		if(sscanf(varchar, s(24)d, fix_type, giveplayer_id))
		(
			hrp_Tip(playerid, /oferuj wymiane (silnika/karoserii/plynow/filtra/chlodnicy) (ID gracza))
			return 1
		)
		if(PlayerCache(playerid)(pRepairVeh) != INVALID_VEHICLE_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie jesteœ ju¿ w trakcie naprawiania innego pojazdu., OK, )
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(!IsPlayerInAnyVehicle(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w pojeŸdzie, który zamierzasz naprawiaæ., OK, )
			return 1
		)
		if(GetPlayerVehicleSeat(giveplayer_id) != 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi byæ kierowc¹ pojazdu, który zamierzasz naprawiaæ., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)

		vehid = GetPlayerVehicleID(giveplayer_id), data(64), price
		veh_price = -1

		mysql_query_format(SELECT salonveh_price FROM hrp_salonveh WHERE salonveh_model = %d, GetVehicleModel(vehid))
		mysql_store_result()
		mysql_fetch_row(data, |)
		sscanf(data, p(|)d, veh_price)
		mysql_free_result()

		if(veh_price (= 0)
		(
			veh_price = 23500
		)

		if(!strcmp(fix_type, silnika, true))
		(
			price = floatround(veh_price * 0.40)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_REPAIR_ENGINE, Wymiana silnika, vehid, price)
			return 1
		)
		if(!strcmp(fix_type, karoserii, true))
		(
			price = floatround(veh_price * 0.08)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_REPAIR_BODY, Naprawa karoserii, vehid, price)
			return 1
		)
		if(!strcmp(fix_type, plynow, true))
		(
			price = floatround(veh_price * 0.0025)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_REPAIR_FLUIDS, Wymiana plynow, vehid, price)
			return 1
		)
		if(!strcmp(fix_type, filtra, true))
		(
			price = floatround(veh_price * 0.0030)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_REPAIR_FILTER, Wymiana filtra, vehid, price)
			return 1
		)
		if(!strcmp(fix_type, chlodnicy, true))
		(
			price = floatround(veh_price * 0.0050)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_REPAIR_COOLER, Naprawa chlodnicy, vehid, price)
			return 1
		)

		hrp_Tip(playerid, /oferuj wymiane (silnika/karoserii/plynow/filtra/chlodnicy) (ID gracza))
		return 1
	)
	if(!strcmp(type, montaz, true))
	(
		if(!IsPlayerInGroupType(playerid, GROUP_WORKSHOP))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ pracownikiem ¿adnego warsztatu., OK, )
			return 1
		)
		item_uid, giveplayer_id, price
		if(sscanf(varchar, ddd, item_uid, giveplayer_id, price))
		(
			hrp_Tip(playerid, /oferuj montaz (UID przedmiotu) (ID gracza) (Robocizna))
			return 1
		)
   		itemid = GetItemID(item_uid)
		if(ItemInfo(itemid)(iPlace) != PLACE_PLAYER || ItemInfo(itemid)(iOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID przedmiotu., OK, )
			return 1
		)
		if(ItemInfo(itemid)(iType) != ITEM_TUNING && ItemInfo(itemid)(iType) != ITEM_ACCESS && ItemInfo(itemid)(iType) != ITEM_TUNEPART)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zamontowaæ tego przedmiotu., OK, )
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		if(!IsPlayerInAnyVehicle(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w pojeŸdzie, w którym zamierzasz coœ zamontowaæ., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(giveplayer_id)
		if(ItemInfo(itemid)(iType) == ITEM_TUNING)
		(
			slot = GetVehicleComponentType(ItemInfo(itemid)(iValue1))
			if(CarInfo(vehid)(cComponent)(slot) != 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Jakiœ komponent tego typu jest ju¿ zamontowany.\nMusi zostaæ on odmontowany., OK, )
				return 1
			)
		)

		//sprawdz modele
		if(ItemInfo(itemid)(iType) == ITEM_TUNING)
		(
			model = GetVehicleModel(vehid)
			if(model == 417 || model == 425 || model == 430 || model == 446 || model == 447 || model == 448 || model == 452 || model == 453 || model == 454 || model == 460 || model == 461 || model == 462 || model == 463 || model == 468 || model == 471 || model == 472 || model == 476 || model == 481 || model == 484 || model == 487 )
			(
				GuiMsg(playerid,Ten pojazd nie jest poddawany tuningowi mechanicznemu.,1)
				return 1
			)
			else if (model == 488 || model == 493 || model == 497 || model == 509 || model == 510 || model == 511 || model == 512 || model == 513 || model == 519 || model == 520 || model == 521 || model == 522 || model == 523 || model == 548 || model == 553 || model == 563 || model == 577 || model == 581 || model == 586 || model == 593 || model == 595)
			(
				GuiMsg(playerid,Ten pojazd nie jest poddawany tuningowi mechanicznemu.,1)
				return 1
			)
		)

		if(ItemInfo(itemid)(iType) == ITEM_TUNEPART)
		(
			if(IsVehicleHasTune(vehid,ItemInfo(itemid)(iValue2)))
			(
				//tuning mechaniczny
				GuiMsg(playerid,Wskazany komponent jest ju¿ zainstalowany w tym pojeŸdzie.,1)
				return 1
			)
		)
		if(ItemInfo(itemid)(iType) == ITEM_ACCESS)
		(
			if(CarInfo(vehid)(cAccess) & ItemInfo(itemid)(iValue1))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W tym pojeŸdzie jest ju¿ zamontowane te akcesorie., OK, )
				return 1
			)
		)
		if(price ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdn¹ kwotê., OK, )
  			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_MONTAGE, Montaz czesci, itemid, price)
		return 1
	)
	if(!strcmp(type, paintjob, true))
	(
		if(!IsPlayerInGroupType(playerid, GROUP_WORKSHOP))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ pracownikiem ¿adnego warsztatu., OK, )
			return 1
		)
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		/*if(GroupData(group_id_fix)(gType) != GROUP_RACERS || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)*/
		if(GroupData(group_id_fix)(gValue2) != SHOP_PAINTJOB || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Twoja grupa nie mo¿e oferowaæ malowania paintjobów., OK, )
			return 1
		)
		giveplayer_id, paintjob_id, price
		if(sscanf(varchar, ddd, giveplayer_id, paintjob_id, price))
		(
			hrp_Tip(playerid, /oferuj paintjob (ID gracza) (Paintjob ID) (Robocizna))
			return 1
		)
		if(PlayerCache(playerid)(pSprayVeh) != INVALID_VEHICLE_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie jesteœ ju¿ w trakcie lakierowania innego pojazdu., OK, )
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		if(!IsPlayerInAnyVehicle(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w pojeŸdzie, który zamierzasz przelakierowaæ., OK, )
			return 1
		)
		if(paintjob_id ( 0 || paintjob_id ) 4)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID paintjoba., OK, )
			return 1
		)
		if(price ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê., OK, )
			return 1
		)
		if(!WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz mieæ lakier w u¿yciu., OK, )
			return 1
		)
		itemid = GetItemID(WeaponCache(playerid)(WEAPON_FUNC)(pWeaponUID))
		if(ItemInfo(itemid)(iType) != ITEM_PAINT)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz mieæ lakier w u¿yciu., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_PAINTJOB, PaintJob, paintjob_id, price)
		return 1
	)
	if(!strcmp(type, drzwi, true))
	(
		giveplayer_id, price, doorid = GetPlayerDoorID(playerid)
		if(sscanf(varchar, dd, giveplayer_id, price))
		(
			hrp_Tip(playerid, /oferuj drzwi (ID gracza) (Cena))
			return 1
		)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, który zamierzasz sprzedaæ., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego budynku., OK, )
				return 1
			)
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		if(price ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_DOOR, DoorData(doorid)(dName), doorid, price)
		return 1
	)
	if(!strcmp(type, mandat, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_POLICE || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id, points, price, reason(32)
		if(sscanf(varchar, ddds(32), giveplayer_id, points, price, reason))
		(
			hrp_Tip(playerid, /oferuj mandat (ID gracza) (PKT. Karne) (Cena) (Powód))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		if(points ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ iloœæ punktów karnych., OK, )
			return 1
		)
		if(price ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê za mandat., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_MANDATE, reason, points, price)
		return 1
	)
	if(!strcmp(type, odblokowanie, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_POLICE || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id, veh_uid
		if(sscanf(varchar, dd, giveplayer_id, veh_uid))
		(
			hrp_Tip(playerid, /oferuj odblokowanie (ID gracza) (UID pojazdu))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		vehid = GetVehicleID(veh_uid)
		if(vehid == INVALID_VEHICLE_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne UID pojazdu., OK, )
			return 1
		)
		if(!CarInfo(vehid)(cWheelBlock))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd nie ma za³o¿onej blokady na ko³o., OK, )
			return 1
		)
		format(string, sizeof(string), Zdjecie blokady (UID: %d), CarInfo(vehid)(cWheelBlock))
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_UNBLOCK, string, vehid, CarInfo(vehid)(cWheelBlock))
		return 1
	)
	if(!strcmp(type, holowanie, true))
	(
		giveplayer_id, price
		if(sscanf(varchar, dd, giveplayer_id, price))
		(
			hrp_Tip(playerid, /oferuj holowanie (ID gracza) (Cena))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(20.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(!IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie, by móc zaoferowaæ holowanie., OK, )
			return 1
		)
		if(!IsPlayerInAnyVehicle(giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w pojeŸdzie, by móc zaoferowaæ holowanie., OK, )
			return 1
		)
		if(GetPlayerState(giveplayer_id) != PLAYER_STATE_PASSENGER)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w pojeŸdzie jako pasa¿er., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma BW., OK, )
			return 1
		)
		vehid = GetPlayerVehicleID(giveplayer_id)
		if(CarInfo(vehid)(cTowedVeh) != INVALID_VEHICLE_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd jest ju¿ w trakcie holowania innego pojazdu., OK, )
			return 1
		)
		if(price ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wpisana kwota naprawy jest niepoprawna., OK, )
			return 1
		)
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 525 || PlayerHaveItem(playerid, ITEM_LINE))
		(
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_TOWING, Holowanie, vehid, price)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz posiadaæ linê holownicz¹, b¹dŸ siedzieæ w holowniku., OK, )
		)
		return 1
	)
	if(!strcmp(type, vcard, true))
	(
		if(!PlayerCache(playerid)(pPhoneNumber))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby móc wys³aæ vCard musisz mieæ w³¹czony telefon., OK, )
			return 1
		)
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /oferuj vcard (ID gracza))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
  		if(!PlayerCache(giveplayer_id)(pPhoneNumber))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie posiada telefonu w u¿yciu., OK, )
	   		return 1
		)
	 	OnPlayerSendOffer(playerid, giveplayer_id, OFFER_VCARD, vCard, PlayerCache(playerid)(pPhoneNumber), 0)
		return 1
	)
	if(!strcmp(type, leczenie, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_MEDICAL && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id, price
		if(sscanf(varchar, dd, giveplayer_id, price))
		(
			hrp_Tip(playerid, /oferuj leczenie (ID gracza) (Cena))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pHealth) )= 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz jest zdrowy., OK, )
			return 1
		)
		if(price ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê za leczenie., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_HEAL, Leczenie, 0, price)
		return 1
	)
	if(!strcmp(type, reklame, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_NEWS || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id, time, price
		if(sscanf(varchar, ddd, giveplayer_id, time, price))
		(
			hrp_Tip(playerid, /oferuj reklame (ID gracza) (Czas (min)) (Cena))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(price ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Cena nie mo¿e byæ mniejsza ni¿ 0$!, OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_AD, Nadanie reklamy, time, price)
		return 1
	)
	if(!strcmp(type, lekcja, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_DRIVING || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
	  	doorid = GetPlayerDoorID(playerid)
	  	if(doorid == INVALID_DOOR_ID)
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
	  	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
		giveplayer_id, lesson_time, price
		if(sscanf(varchar, ddd, giveplayer_id, lesson_time, price))
		(
			hrp_Tip(playerid, /oferuj lekcja (ID gracza) (Czas (min)) (Cena))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(price ( 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Cena nie mo¿e byæ mniejsza ni¿ 100$!, OK, )
			return 1
		)
		if(lesson_time ( 0 || lesson_time ) 10)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy czas lekcji.\nNie mo¿e byæ wiêkszy ni¿ 10 min., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_LESSON, Lekcja jazdy, lesson_time, price)
		return 1
	)
	if(!strcmp(type, ubezpieczenie, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_INSURANCE || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
	  	doorid = GetPlayerDoorID(playerid)
	  	if(doorid == INVALID_DOOR_ID)
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
	  	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
		giveplayer_id, price
		price = 500
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /oferuj ubezpieczenie (ID gracza))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_LIFE, Ubezpieczenie, 0, price)
		return 1
	)
	if(!strcmp(type, trening, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_GYM || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
	  	doorid = GetPlayerDoorID(playerid)
	  	if(doorid == INVALID_DOOR_ID)
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
	  	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
		giveplayer_id, train_time, price
		if(sscanf(varchar, ddd, giveplayer_id, train_time, price))
		(
			hrp_Tip(playerid, /oferuj trening (ID gracza) (Czas (min)) (Cena))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(price (= 30)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Cena nie mo¿e byæ mniejsza ni¿ 30$!, OK, )
			return 1
		)
		if(train_time ( 0 || train_time ) 10)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy czas treningu.\nNie mo¿e byæ wiêkszy ni¿ 20 min., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_TRAIN, Trening, train_time, price)
		return 1
	)
	if(!strcmp(type, paintball, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_PAINTBALL || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
	  	doorid = GetPlayerDoorID(playerid)
	  	if(doorid == INVALID_DOOR_ID)
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
	  	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
		giveplayer_id, paintball_time, price
		if(sscanf(varchar, ddd, giveplayer_id, paintball_time, price))
		(
			hrp_Tip(playerid, /oferuj paintball (ID gracza) (Czas (min)) (Cena))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(price (= 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Cena nie mo¿e byæ mniejsza ni¿ 100$!, OK, )
			return 1
		)
		if(paintball_time ( 0 || paintball_time ) 10)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy czas treningu.\nNie mo¿e byæ wiêkszy ni¿ 10 min., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_PAINTBALL, Paintball, paintball_time, price)
		return 1
	)
	if(!strcmp(type, wnetrze, true) || !strcmp(type, wnêtrze, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_TIMBER || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id, interior_id, price
		if(sscanf(varchar, ddd, giveplayer_id, interior_id, price))
		(
			hrp_Tip(playerid, /oferuj wnetrze (ID gracza) (ID wnêtrza) (Cena))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(interior_id ( 0 || interior_id ) 111)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID wnêtrza., OK, )
			return 1
		)
		if(price ( Interiors(interior_id)(INTERIOR_PRICE))
		(
			format(string, sizeof(string), Cena za to wnêtrze nie mo¿e byæ mniejsza od $%d., Interiors(interior_id)(INTERIOR_PRICE))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
			return 1
		)

		foreach(Doors, doorid)
		(
			if(DoorData(doorid)(dUID))
			(
				if(IsPlayerInRangeOfPoint(giveplayer_id, 3.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)))
				(
					if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) == PlayerCache(giveplayer_id)(pUID))
					(
						MainPlayerTable(playerid) = interior_id
						OnPlayerSendOffer(playerid, giveplayer_id, OFFER_INTERIOR, Interiors(interior_id)(INTERIOR_NAME), doorid, price)
						return 1
					)
					if(DoorData(doorid)(dOwnerType) == OWNER_GROUP && DoorData(doorid)(dOwner) == GroupData(group_id_fix)(gUID))
					(
						MainPlayerTable(playerid) = interior_id
						OnPlayerSendOffer(playerid, giveplayer_id, OFFER_INTERIOR, Interiors(interior_id)(INTERIOR_NAME), doorid, price)
						return 1
					)
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Klient musi znajdowaæ siê w otoczeniu wejœcia do drzwi., OK, )
		return 1
	)
	if(!strcmp(type, podgl¹d, true) || !strcmp(type, podglad, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_TIMBER || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id, interior_id
		if(sscanf(varchar, dd, giveplayer_id, interior_id))
		(
			hrp_Tip(playerid, /oferuj podglad (ID gracza) (ID wnêtrza))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(interior_id ( 0 || interior_id ) 111)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID wnêtrza., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pPreviewTime))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz aktualnie przegl¹da ju¿ jakieœ wnêtrze, zaczekaj chwilê., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_PREVIEW, Interiors(interior_id)(INTERIOR_NAME), interior_id, 0)
		return 1
	)
	if(!strcmp(type, dokument, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
  	 	doorid = GetPlayerDoorID(playerid)
	  	if(doorid == INVALID_DOOR_ID)
	  	(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
	  	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
	  	(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
		document_type(12), giveplayer_id
		if(sscanf(varchar, ds(12), giveplayer_id, document_type))
		(
			hrp_Tip(playerid, /oferuj dokument (ID gracza) (Typ dokumentu (dowod, prawko, metryczka, poczytalnosc)))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(!strcmp(document_type, dowod, true))
		(
			if(GroupData(group_id_fix)(gType) != GROUP_GOV || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, do wyrobienia tego dokumentu., OK, )
				return 1
			)
			if(PlayerCache(giveplayer_id)(pDocuments) & DOC_PROOF)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz posiada ju¿ dowód osobisty., OK, )
				return 1
			)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_DOCUMENT, Dowod osobisty, DOC_PROOF, 50)
			return 1
		)
		if(!strcmp(document_type, prawko, true))
		(
			if(GroupData(group_id_fix)(gType) != GROUP_DRIVING || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, do wyrobienia tego dokumentu.\nPrawo jazdy wyrabia departament komunikacji z siedzib¹ na Verona Beach., OK, )
				return 1
			)
  			if(PlayerCache(giveplayer_id)(pDocuments) & DOC_DRIVER)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz posiada ju¿ prawo jazdy., OK, )
				return 1
			)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_DOCUMENT, Prawo jazdy, DOC_DRIVER, 100)
			return 1
		)
		if(!strcmp(document_type, metryczka, true))
		(
			if(GroupData(group_id_fix)(gType) != GROUP_MEDICAL || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, do wyrobienia tego dokumentu., OK, )
				return 1
			)
   			if(PlayerCache(giveplayer_id)(pDocuments) & DOC_SEND)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz posiada ju¿ metryczkê zdrowia., OK, )
				return 1
			)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_DOCUMENT, Metryczka zdrowia, DOC_SEND, 250)
			return 1
		)
		if(!strcmp(document_type, poczytalnosc, true))
		(
			if(GroupData(group_id_fix)(gType) != GROUP_MEDICAL || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, do wyrobienia tego dokumentu., OK, )
				return 1
			)
   			if(PlayerCache(giveplayer_id)(pDocuments) & DOC_SANITY)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz posiada ju¿ zaœwiadczenie o poczytalnoœci., OK, )
				return 1
			)
			OnPlayerSendOffer(playerid, giveplayer_id, OFFER_DOCUMENT, Zaswiadczenie - poczytalnosc, DOC_SANITY, 250)
			return 1
		)
		return 1
	)
	if(!strcmp(type, rejestracje, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_DRIVING || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy.\nPojazdy rejestruje departament komunikacji z siedzib¹ na Verona Beach., OK, )
			return 1
		)
  	 	doorid = GetPlayerDoorID(playerid)
	  	if(doorid == INVALID_DOOR_ID)
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
	  	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
		giveplayer_id, veh_uid
		if(sscanf(varchar, dd, giveplayer_id, veh_uid))
		(
			hrp_Tip(playerid, /oferuj rejestracje (ID gracza) (UID pojazdu))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		vehid = GetVehicleID(veh_uid)
		if(vehid == INVALID_VEHICLE_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne UID pojazdu., OK, )
			return 1
		)
		if(CarInfo(vehid)(cRegister))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd jest ju¿ zarejestrowany., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_REGISTER, Rejestracja pojazdu, vehid, 150)
		return 1
	)
	if(!strcmp(type, oplata, true))
	(
 		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_GOV || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
	  	doorid = GetPlayerDoorID(playerid)
	  	if(doorid == INVALID_DOOR_ID)
	  	(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
	  	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
	  	(
	  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku grupy, by móc oferowaæ., OK, )
	  		return 1
	  	)
	  	giveplayer_id, price
		if(sscanf(varchar, dd, giveplayer_id, price))
		(
			hrp_Tip(playerid, /oferuj oplata (ID gracza) (Kwota))
			return 1
		)
  		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(price ( 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_FEE, Oplata, 0, price)
	  	return 1
	)
	if(!strcmp(type, teren, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
			return 1
		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
 		if(!IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id, price
		if(sscanf(varchar, dd, giveplayer_id, price))
		(
			hrp_Tip(playerid, /oferuj teren (ID gracza) (Cena))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(!PlayerCache(giveplayer_id)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Drugi gracz musi byæ na s³u¿bie grupy, któr¹ chce przej¹æ teren., OK, )
			return 1
		)
		give_group_id_fix = GetPlayerDutyGroupID(giveplayer_id)
		if(GroupData(give_group_id_fix)(gType) != GROUP_CRIMINAL)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ terenu temu graczowi, nie jest on na s³u¿bie grupy gangu., OK, )
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ
		GetPlayerPos(playerid, PosX, PosY, PosZ)

		foreach(GangZones, gangzone_id)
		(
			if(GangZoneInfo(gangzone_id)(gUID))
			(
				if(GangZoneInfo(gangzone_id)(gOwner) == PlayerCache(playerid)(pGroupDuty))
				(
					if(IsPlayerInArea(playerid, GangZoneInfo(gangzone_id)(gMaxX), GangZoneInfo(gangzone_id)(gMinX), GangZoneInfo(gangzone_id)(gMaxY), GangZoneInfo(gangzone_id)(gMinY)))
					(
						OnPlayerSendOffer(playerid, giveplayer_id, OFFER_AREA, Teren, gangzone_id, price)
						return 1
					)
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê na terenie nale¿¹cym do Twojego gangu., OK, )
		return 1
	)
	if(!strcmp(type, hotdog, true))
	(
		if(PlayerCache(playerid)(pJob) != JOB_HOTDOG)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ sprzedawc¹ hotdogów. Aby zmieniæ swoj¹ pracê dorywcz¹ udaj siê do urzêdu., OK, )
			return 1
		)
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz stan¹æ przy budce aby sprzedawaæ hotdogi., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿ywaæ budki podczas stanu nieprzytomnoœci., OK, )
			return 1
		)
		object_id = GetClosestObject(playerid)
		if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_HOTDOG)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê przy budce z hotdogami., OK, )
			return 1
		)
		giveplayer_id
		if(sscanf(varchar, dd, giveplayer_id))
		(
			hrp_Tip(playerid, /oferuj hotdog (ID gracza))
			return 1
		)
   		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)

		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_HOTDOG, Hotdog z budki, 10, 10)

		return 1
	)
	return 1
)

CMD:o(playerid, params()) return cmd_oferuj(playerid, params)

CMD:login(playerid, params())
(
	if(!Logged(playerid))
	(
		OnPlayerLogin(playerid)
		return 1
	)
	return 1
)

CMD:hazard(playerid, params())
(
	SendClientMessage(playerid, COLOR_RED, http://gry.wp.pl)
	return 1
)

CMD:tel(playerid, params())
(
 	if(!PlayerCache(playerid)(pPhoneNumber))
  	(
   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz ¿adnego telefonu w u¿yciu.\nSkorzystaj z komendy /u, by w³¹czyæ telefon., OK, )
   		return 1
   	)
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿ywaæ telefonu podczas stanu nieprzytomnoœci., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGymType) != TRAIN_NONE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz korzystaæ z telefonu podczas treningu., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pArrest))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Twój telefon podczas pobytu w areszcie jest schowany do depozytu., OK, )
		return 1
	)
	number, string(256)
	if(sscanf(params, d, number))
	(
		itemid, hour, minute
		gettime(hour, minute)

		foreach(Items, i)
		(
	 		if(ItemInfo(i)(iUID))
	   		(
	   			if(ItemInfo(i)(iType) == ITEM_PHONE && ItemInfo(i)(iUsed))
	   			(
	   				if(ItemInfo(i)(iValue1) == PlayerCache(playerid)(pPhoneNumber))
	   				(
				 		itemid = i
				   		break
					)
				)
			)
		)
		PlayerCache(playerid)(pManageItem) = itemid
		
		if(isPhoneNewType(playerid))
		(
			PlayerCache(playerid)(pPhoneAction) = PHONE_ACTION_HOME
			
			setPhoneWallpaper(playerid, getPhoneSettings(playerid, GET_PHONE_WALLPAPER))	// tapetka
			if(getPhoneSettings(playerid, GET_PHONE_PASSWORD) ) 0)
			(
				ShowPlayerDialog(playerid, D_PHONE_PASS, DIALOG_STYLE_PASSWORD, Has³o, To urz¹dzenie jest zablokowane has³em, wprowadŸ kod by odblokowaæ menu., OK, Anuluj)
				return 1
			)
			
			phone_showTexts(playerid)
			return 1
		)

		format(string, sizeof(string), %s (Nr. %d | %02d:%02d), ItemInfo(itemid)(iName), PlayerCache(playerid)(pPhoneNumber), hour, minute)
		ShowPlayerDialog(playerid, D_TEL_OPTIONS, DIALOG_STYLE_LIST, string, 1. Zadzwoñ\n2. Napisz SMS\n3. Wyœlij vCard\n4. Lista kontaktów\n5. Dodaj numer\n6. Dzwonek w telefonie\n7. Wy³¹cz telefon, Wybierz, Zamknij)
		//ShowPlayerDialog(playerid, D_TEL_OPTIONS, DIALOG_STYLE_LIST, string, 1. Zadzwoñ\n2. Wyœlij vCard\n3. Lista kontaktów\n4. Dodaj numer\n5. Wy³¹cz telefon, Wybierz, Zamknij)
		return 1
	)
	if(number == 0)
	(
		SendClientMessage(playerid, COLOR_DO, * S³ychaæ sygna³ zajêtoœci... *)
		return 1
	)
	if(PlayerCache(playerid)(pPhoneNumber) == number)
	(
		SendClientMessage(playerid, COLOR_DO, * S³ychaæ sygna³ zajêtoœci... *)
		return 1
	)
	if(PlayerCache(playerid)(pCall) != -1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie prowadzisz ju¿ jak¹œ rozmowê telefoniczn¹.\nU¿yj komendy /zakoncz, aby zakoñczyæ obecn¹ rozmowê., OK, )
		return 1
	)
	if(number == 27103) // LimitedPackages (- paczki z broniami na limit
	(
		data(2), package_point
		mysql_query_format(SELECT package_point FROM hrp_limitedpackages WHERE package_playeruid = %d, PlayerCache(playerid)(pUID))
		mysql_store_result()
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)d, package_point)
		)
		mysql_free_result()
		if(IsPlayerInRangeOfPoint(playerid, 3.0, -392.4167,2221.2620,42.4297) && package_point == 1) // dolina miedzy gorami LV
		(
			if(!IsPlayerInAnyVehicle(playerid))
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Dla bezpieczeñstwa wsi¹dŸ do samochodu.)
				return 1
			)
			gangsters = 0
			for(i = 0  i ( MAX_PLAYERS i++)
			(
				if(IsPlayerInRangeOfPoint(i, 5.0, -392.4167,2221.2620,42.4297))
				(
					gangsters++
				)
				if(gangsters == 3)
				(
					continue
				)
			)
			if(gangsters (= 2)
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Mówi³em, przyjedŸ z obstaw¹...)
				return 1
			)
			WeaponPointActor = CreateActor(125, -385.4510,2217.6567,42.4297, 0.0)
			WeaponPointPickup = CreatePickup(1239,2,-385.4510,2217.6567,42.4297,0)
			SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Czekam za rogiem.)
			return 1
		)
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 267.7657,2887.7651,10.8491) && package_point == 2) // opuszczona wioska obok LV
		(
			if(!IsPlayerInAnyVehicle(playerid))
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Dla bezpieczeñstwa wsi¹dŸ do samochodu.)
				return 1
			)
			gangsters = 0
			for(i = 0  i ( MAX_PLAYERS i++)
			(
				if(IsPlayerInRangeOfPoint(i, 5.0, 267.7657,2887.7651,10.8491))
				(
					gangsters++
				)
				if(gangsters == 3)
				(
					continue
				)
			)
			if(gangsters (= 2)
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Mówi³em, przyjedŸ z obstaw¹...)
				return 1
			)
			WeaponPointActor = CreateActor(58, 262.3114,2895.6213,10.4067, 0.0)
			WeaponPointPickup = CreatePickup(1239,2,262.3114,2895.6213,10.4067,0)
			SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Czekam na Ciebie za domkiem.)
			return 1
		)
		if(IsPlayerInRangeOfPoint(playerid, 3.0, -2217.9829,641.0096,49.4491) && package_point == 3) // chinatown SF
		(
			if(!IsPlayerInAnyVehicle(playerid))
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Dla bezpieczeñstwa wsi¹dŸ do samochodu.)
				return 1
			)
			gangsters = 0
			for(i = 0  i ( MAX_PLAYERS i++)
			(
				if(IsPlayerInRangeOfPoint(i, 5.0, -2217.9829,641.0096,49.4491))
				(
					gangsters++
				)
				if(gangsters == 3)
				(
					continue
				)
			)
			if(gangsters (= 2)
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Mówi³em, przyjedŸ z obstaw¹...)
				return 1
			)
			WeaponPointActor = CreateActor(118, -2207.6836,690.3974,50.7107, 0.0)
			WeaponPointPickup = CreatePickup(1239,2,-2207.6836,690.3974,50.7107,0)
			SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Jestem w uliczce po lewej stronie.)
			return 1
		)
		if(IsPlayerInRangeOfPoint(playerid, 3.0, -579.7222,-177.1168,78.8631) && package_point == 4) // opuszczony tartak
		(
			if(!IsPlayerInAnyVehicle(playerid))
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Dla bezpieczeñstwa wsi¹dŸ do samochodu.)
				return 1
			)
			gangsters = 0
			for(i = 0  i ( MAX_PLAYERS i++)
			(
				if(IsPlayerInRangeOfPoint(i, 5.0, -579.7222,-177.1168,78.8631))
				(
					gangsters++
				)
				if(gangsters == 3)
				(
					continue
				)
			)
			if(gangsters (= 2)
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Mówi³em, przyjedŸ z obstaw¹...)
				return 1
			)
			WeaponPointActor = CreateActor(128, -563.7750,-182.4900,78.4063, 0.0)
			WeaponPointPickup = CreatePickup(1239,2,-563.7750,-182.4900,78.4063,0)
			SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Zapraszam Was do wewn¹trz szopy.)
			return 1
		)
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 2798.0588,-2436.3267,13.6312) && package_point == 5) // doki LS
		(
			if(!IsPlayerInAnyVehicle(playerid))
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Dla bezpieczeñstwa wsi¹dŸ do samochodu.)
				return 1
			)
			gangsters = 0
			for(i = 0  i ( MAX_PLAYERS i++)
			(
				if(IsPlayerInRangeOfPoint(i, 5.0, 2798.0588,-2436.3267,13.6312))
				(
					gangsters++
				)
				if(gangsters == 3)
				(
					continue
				)
			)
			if(gangsters (= 2)
			(
				SendClientMessage(playerid, COLOR_YELLOW, Rozmowa zosta³a zakoñczona.)
				SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Mówi³em, przyjedŸ z obstaw¹...)
				return 1
			)
			WeaponPointActor = CreateActor(112, 2830.3140,-2445.6169,19.9220, 0.0)
			WeaponPointPickup = CreatePickup(1239,2,2830.3140,-2445.6169,19.9220,0)
			SendClientMessage(playerid, COLOR_YELLOW, (SMS) 27103: Jestem na górze statku.)
			return 1
		)
		SendClientMessage(playerid, COLOR_DO, * Nie mo¿na po³¹czyæ siê z wybranym numerem...)
	)
	if(number ( 999999)
	(
		PlayerCache(playerid)(pSerivceNumberAs) = PlayerCache(playerid)(pPhoneNumber)
		// Dzownienie na s³uzby/sklepy/kom.
		if(number == 333)
		(
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skontaktowaæ siê z hurtowni¹, musisz znajdowaæ siê w budynku., OK, )
				return 1
			)
			if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ wlaœcicielem tego budynku., OK, )
				return 1
			)
			if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
			(
				if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_ORDER))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zamawiania produktów., OK, )
					return 1
				)
			)
			MainPlayerTable(playerid) = doorid
			attachPlayerPhone(playerid)

			// Kolejne bugowanie
			bool:checkbug = false
			if(gettime() - LogTime(playerid) ) 60)
				checkbug= true
				
			if(!checkbug)
			(
				GuiMsg(playerid, Musisz chwilê odczekaæ nim u¿yjesz tej funkcji., 0)
				return 1
			)


			data(48), list_cat(512),
				cat_uid, cat_name(32)

			mysql_query(SELECT * FROM hrp_orders_cat)

			mysql_store_result()
			while(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)ds(32), cat_uid, cat_name)
				format(list_cat, sizeof(list_cat), %s\n%d\t%s, list_cat, cat_uid, cat_name)
			)
			mysql_free_result()
			if(strlen(list_cat))
			(
				ShowPlayerDialog(playerid, D_PRODUCT_TYPE, DIALOG_STYLE_LIST, Wybierz kategoriê Ci odpowiadaj¹c¹:, list_cat, Wybierz, Anuluj)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych kategorii., OK, )
			)
			
			return 1
		)
		if(number == 777)
		(
			list_taxi_corp(1024)
			foreach(Groups, group_id_fix)
			(
				if(GroupData(group_id_fix)(gUID))
				(
					if(GroupData(group_id_fix)(gType) == GROUP_TAXI)
					(
						workers = 0
						foreach(Player, i)
						(
							if(Logged(i) && Spawned(i))
							(
								if(PlayerCache(i)(pGroupDuty) == GroupData(group_id_fix)(gUID))
								(
				 					workers ++
								)
							)
						)
						if(workers)
						(
							format(list_taxi_corp, sizeof(list_taxi_corp), %s\n%d\t(na s³u¿bie %d)\t%s, list_taxi_corp, group_id_fix, workers, GroupData(group_id_fix)(gName))
						)
					)
				)
			)
			if(strlen(list_taxi_corp))
			(
	  			//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
				//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
				attachPlayerPhone(playerid)

				ShowPlayerDialog(playerid, D_SELECT_TAXI_CORP, DIALOG_STYLE_LIST, Korporacje taksówkarskie, list_taxi_corp, Dalej, Anuluj)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W chwili obecnej nie ma ¿adnej taksówki na s³u¿bie., OK, )
			)
			return 1
		)
		if(number == 911)
		(
			//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
			//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
			attachPlayerPhone(playerid)

			SendClientMessage(playerid, COLOR_YELLOW, Sekretarka: Witaj, po³¹czy³eœ siê z numerem alarmowym centrali Los Santos, z kim po³¹czyæ?)
			ShowPlayerDialog(playerid, D_ALARM_NUMBER, DIALOG_STYLE_LIST, Z kim chcesz siê po³¹czyæ?, Los Santos Police Department\nLos Santos Medical Center\nLos Santos Fire Department\nDepartment of Sanitation Electricity\nFederal Bureau of Investigation, Wybierz, Anuluj)
			return 1
		)
		if(number == 444)
		(
			//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
			//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
			attachPlayerPhone(playerid)

			ShowPlayerDialog(playerid, D_SN_CALL, DIALOG_STYLE_INPUT, Los Santos News, Dodzwoni³eœ siê do radiostacji w Los Santos.\nPowiedz nam po krótce w czym rzecz., Dalej, Anuluj)
			return 1
		)
		if(number ) 9999 && number ( 99999)
		(
			// pagery
			foreach(Items, itemid)
			(
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iType) == ITEM_PAGER && ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iValue1) == number)
					(
						foreach(Player, i)
						(
							if(ItemInfo(itemid)(iOwner) == PlayerCache(i)(pUID))
							(
								format(string, sizeof(string), ** Twój pager pokaza³ na ekranie numer %d. **, PlayerCache(playerid)(pPhoneNumber))
								SendClientMessage(i, COLOR_LIGHTRED, string)

								SendClientMessage(playerid, COLOR_DO, ** W s³uchawce s³ychaæ dŸwiêk potwierdzenia po³Â±czenia. **)
								return 1
							)
						)
						return 1
					)
				)
			)
			return 1
		)
		else if(number ) 999 && number ( 9999)
		(
			//stacjonarny
			// Dzwoni na stacjonarny
			for(i = 0  i ( MAX_HOMEPHONES i++)
			(
				if(HomePhones(i)(hPhoneNumber) == number)
				(
					callid = Itter_Free(Calls)
					Call(callid)(caller) = playerid
					Call(callid)(callerNumber) = PlayerCache(playerid)(pPhoneNumber)
					Call(callid)(callerDevice) = DEVICE_CELL
					PlayerCache(playerid)(pCall) = callid

					Call(callid)(called) = INVALID_PLAYER_ID
					Call(callid)(calledNumber) = number
					Call(callid)(calledDevice) = DEVICE_HOME
					Call(callid)(calledDevID) = i

					Call(callid)(callTime) = gettime()

					Itter_Add(Calls, callid)

					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)

					SendClientMessage(playerid, COLOR_DO, ** S³ychaæ sygna³ próby po³¹czenia siê... **)

					foreach(Player, pid)
					(
						if(CanPlayerHearHomephone(pid, i))
						(
							// dzwonienie dla gracza
							SendClientMessage(pid, COLOR_DO, ** S³ychaæ dŸwiêk telefonu domowego. **)
							PlayerPlaySound(pid, 20600, 0.0, 0.0, 0.0)
						)
					)

					return 1
				)
			)
			return 1
		)
		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pPhoneNumber) == number)
				(
					if(PlayerCache(i)(pCall) != -1)
					(
						SendClientMessage(playerid, COLOR_DO, ** S³ychaæ sygna³ zajêtoœci... **)
						return 1
					)

					callid = Itter_Free(Calls)
					Call(callid)(caller) = playerid
					Call(callid)(callerNumber) = PlayerCache(playerid)(pPhoneNumber)
					Call(callid)(callerDevice) = DEVICE_CELL
					PlayerCache(playerid)(pCall) = callid

					Call(callid)(called) = i
					Call(callid)(calledNumber) = number
					Call(callid)(calledDevice) = DEVICE_CELL

					Call(callid)(callTime) = gettime()

					Itter_Add(Calls, callid)

					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)

					// Wyciasznie telefonu
					if(!PlayerCache(i)(pArrest))
					(
						if(!PlayerCache(i)(pPhoneMuted))
						(
							format(string, sizeof(string), * S³ychaæ dŸwiêk dzwoni¹cego telefonu. (( %s )), PlayerName(i))
							ProxDetector(10.0, i, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, false)
						)
						else
						(
							SendClientMessage(i, COLOR_DO, * Czujesz w kieszeni jak¹œ wibracjê.)
						)

						SendClientMessage(playerid, COLOR_DO, * S³ychaæ sygna³ próby po³¹czenia siê... *)
					)

					//contact_number	contact_name	contact_ownernumb

					data(32), name(24)

					mysql_query_format(SELECT contact_name FROM hrp_contacts WHERE contact_ownernumb = %d AND contact_number = %d LIMIT 1, PlayerCache(i)(pPhoneNumber), PlayerCache(playerid)(pPhoneNumber))
					mysql_store_result()
					if(mysql_fetch_row(data, |))
					(
						sscanf(data, p(|)s(24), name)
					)
					mysql_free_result()

					if(strlen(name) ) 0)
					(
						format(string, sizeof(string), Po³¹czenie przychodz¹ce od %s, u¿yj /odbierz, by odebraæ rozmowê., name)
					)
					else
					(
						format(string, sizeof(string), Po³¹czenie przychodz¹ce od %d, u¿yj /odbierz, by odebraæ rozmowê., PlayerCache(playerid)(pPhoneNumber))
					)

					if(!PlayerCache(i)(pArrest))
					(
						SendClientMessage(i, COLOR_YELLOW, string)
					)

					// Audio dzwonka
					Float:PosX, Float:PosY, Float:PosZ
					GetPlayerPos(i, PosX, PosY, PosZ)

	  				foreach(Player, player)
					(
						if(Logged(player) && Spawned(player))
						(
							if(IsPlayerInRangeOfPoint(player, 10.0, PosX, PosY, PosZ))
							(
								// Miejsce na audio dzwonka
								//audio = Audio_Play(player, AUDIO_CALLING)
								//Audio_Set3DPosition(player, audio, PosX, PosY, PosZ, 10.0)
							)
						)
					)
					return 1
				)
			)
		)
	)
	else
	(
		foreach(Phones, phone)
		(
			if(Phones(phone)(phoneUID))
			(
				if(Phones(phone)(phoneNumber) == number)
				(
					callid = Itter_Free(Calls)
					Call(callid)(caller) = playerid
					Call(callid)(callerNumber) = PlayerCache(playerid)(pPhoneNumber)
					Call(callid)(callerDevice) = DEVICE_CELL
					PlayerCache(playerid)(pCall) = callid

					Call(callid)(called) = INVALID_PLAYER_ID
					Call(callid)(calledNumber) = number
					Call(callid)(calledDevice) = DEVICE_BOX
					Call(callid)(calledDevID) = phone

					Call(callid)(callTime) = gettime()

					Itter_Add(Calls, callid)

					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)

					SendClientMessage(playerid, COLOR_DO, ** S³ychaæ sygna³ próby po³¹czenia siê... **)

					foreach(Player, i)
					(
						if(CanPlayerHearPhone(i, phone))
						(
							// dzwonienie dla gracza
							SendClientMessage(i, COLOR_DO, ** S³yszysz dŸwiêk telefonu w pobli¿u. Brzmi jak budka telefoniczna. **)
							PlayerPlaySound(i, 20600, 0.0, 0.0, 0.0)
						)
					)

					return 1
				)
			)
		)
	)

	SendClientMessage(playerid, COLOR_DO, * Nie mo¿na po³¹czyæ siê z wybranym numerem...)
	return 1
)

CMD:telefon(playerid, params()) return cmd_tel(playerid, params)
CMD:call(playerid, params()) return cmd_tel(playerid, params)

CMD:odbierz(playerid, params())
(
	// Odbieranie zwyk³ego telefonu

	if(PlayerCache(playerid)(pCall) != -1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie rozmawiasz ju¿ z kimœ przez telefon., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz odebraæ telefonu podczas stanu nieprzytomnoœci., OK, )
		return 1
	)

	foreach(Calls, callid)
	(
		if(Call(callid)(called) == playerid && !Call(callid)(convo))
		(
			Call(callid)(convo) = true
			PlayerCache(playerid)(pCall) = callid

			PlayerPlaySound(Call(callid)(caller), 1147, 0.0, 0.0, 0.0)

			//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
			//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
			attachPlayerPhone(playerid)

			SendClientMessage(playerid, COLOR_YELLOW, Odebrano telefon. Aby zakoñczyæ rozmowê u¿yj komendy /zakoncz.)
			SendClientMessage(Call(callid)(caller), COLOR_YELLOW, Odebrano telefon. Aby zakoñczyæ rozmowê u¿yj komendy /zakoncz.)

			return 1
		)
	)

	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nikt w danej chwili nie próbuje siê z Tob¹ po³¹czyæ., OK, )
	return 1
)

CMD:od(playerid, params()) return cmd_odbierz(playerid, params)

CMD:zakoncz(playerid, params())
(
	// W poni¿szym kodzie zak³adamy ¿e koñczÂ±cy rozmowê to dzwoniÂ±cy a nie odbireajÂ±cy nawet je¿eli to nie prawda.
	// Logia siê zgadza przez ustalenie kto jest tym drugim i operowaniem na zasadzie zminnej other (drugi).

	callid = PlayerCache(playerid)(pCall)

	if(callid != -1)
	(
		EndCall(callid)
		return 1
	)
	else
	(
		foreach(Calls, callidd)
		(
			if(Call(callidd)(caller) == playerid || Call(callidd)(called) == playerid)
			(
				EndCall(callidd)
				return 1
			)
		)
	)

	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie nikt nie próbuje siê z Tob¹ po³¹czyæ., OK, )
	return 1
)

CMD:z(playerid, params()) return cmd_zakoncz(playerid, params)


// JE¿ELI TO ODKOMENTOWUJESZ TO PRZYSTOSUJ POD NOWE TELEFONY!!!
// OKOIKOKOKOKOKK
CMD:sms(playerid, params())
(
	if(!PlayerCache(playerid)(pPhoneNumber))
  	(
   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz ¿adnego telefonu w u¿yciu.\nSkorzystaj z komendy /u, by w³¹czyæ telefon., OK, )
   		return 1
   	)
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿ywaæ telefonu podczas stanu nieprzytomnoœci., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pArrest))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Twój telefon podczas pobytu w areszcie jest schowany do depozytu., OK, )
		return 1
	)
	number, text(128), string(256)
	if(sscanf(params, ds(128), number, text))
	(
		hrp_Tip(playerid, /sms (Nr. tel) (Treœæ))
		return 1
	)
	if(number ) 999999 || number ( 100000)
	(
		GuiMsg(playerid, Wiadomoœci tekstowe mo¿esz wysy³aæ wy³¹cznie na telefony komórkowe.\nSprawdŸ czy wpisa³eœ dobry numer., 1)
		return 1
	)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pPhoneNumber) == number)
			(
				//contact_number	contact_name	contact_ownernumb

				data(32), name(24)

				mysql_query_format(SELECT contact_name FROM hrp_contacts WHERE contact_ownernumb = %d AND contact_number = %d LIMIT 1, PlayerCache(i)(pPhoneNumber), PlayerCache(playerid)(pPhoneNumber))
				mysql_store_result()
				if(mysql_fetch_row(data, |))
				(
					sscanf(data, p(|)s(24), name)
				)
				mysql_free_result()

				if(strlen(name) ) 0)
				(
					format(string, sizeof(string), (SMS) %s: %s, name, text)
				)
				else
				(
					format(string, sizeof(string), (SMS) %d: %s, PlayerCache(playerid)(pPhoneNumber), text)
				)
				if(!PlayerCache(i)(pArrest))
				(
					SendClientMessage(i, COLOR_YELLOW, string)
				)

				format(string, sizeof(string), Wys³ano » (SMS) %d: %s, number, text)
				SendClientMessage(playerid, COLOR_YELLOW, string)

				format(string, sizeof(string), * %s wysy³a SMS-a., PlayerName(playerid))
				FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
				if(!PlayerCache(playerid)(pArrest))
				(
					if(!PlayerCache(i)(pPhoneMuted))
					(
						if(PlayerCache(i)(pSex) == 1) 		format(string, sizeof(string), * %s otrzyma³ SMS-a., PlayerName(i))
						else if(PlayerCache(i)(pSex) == 2) 	format(string, sizeof(string), * %s otrzyma³a SMS-a., PlayerName(i))
						
						ProxDetector(10.0, i, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
					)
					else
					(
						SendClientMessage(i, COLOR_DO, * W kieszeni czujesz krótk¹ wibracjê SMS-a.)
					)
				)

				//ProxDetector(10.0, i, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)

				// Audio smsa
				Float:PosX, Float:PosY, Float:PosZ
				GetPlayerPos(i, PosX, PosY, PosZ)

  				foreach(Player, player)
				(
					if(Logged(player) && Spawned(player))
					(
						if(IsPlayerInRangeOfPoint(player, 10.0, PosX, PosY, PosZ))
						(
							//audio = Audio_Play(player, 2)
		  					//Audio_Set3DPosition(player, audio, PosX, PosY, PosZ, 10.0)
							//PlayAudioStreamForPlayer(player, http://pliki.ls-rp.net/sounds/sms.mp3)
						)
					)
				)

				return 1
			)
		)
	)
	
	// SMS Offline - poni¿ej co ma siê staæ, jeœli koleœ offline a telefon w³¹czony
	buffer(256), name(64)
	format(buffer, sizeof(buffer), SELECT * FROM hrp_items WHERE item_value1 = %d AND item_used = 1, number)
	mysql_query(buffer)
	mysql_store_result()
	
	if(mysql_num_rows() ) 0)
	(
		mysql_free_result()
		sendClientPoop(playerid, » Telefon poza zasiêgiem, SMS zostanie odczytany gdy abonent go w³¹czy.)
		format(string, sizeof(string), Wys³ano » (SMS) %d: %s, number, text)
		SendClientMessage(playerid, COLOR_YELLOW, string)
		
		mysql_query_format(SELECT contact_name FROM hrp_contacts WHERE contact_ownernumb = %d AND contact_number = %d LIMIT 1, number, PlayerCache(playerid)(pPhoneNumber))
		mysql_store_result()
		if(mysql_fetch_row(buffer, |))
		(
			sscanf(buffer, p(|)s(24), name)
		)
		mysql_free_result()
		
		if(!strlen(name))
		(
			format(name, sizeof(name), nieznany)
		)
		
		format(buffer, sizeof(buffer), INSERT INTO hrp_offlinesms VALUES(NULL, %d, %d, %s, %s), PlayerCache(playerid)(pPhoneNumber), number, text, name)
		mysql_query(buffer)
		
		return 1
	)
	else
	(
		mysql_free_result()
	)
	
	SendClientMessage(playerid, COLOR_DO, * Wiadomoœæ SMS nie zosta³a dostarczona...)
	return 1
)

/*
CMD:namierz(playerid, params())
(
	number
	if(sscanf(params, d, number))
	(
		if(Checkpoint(playerid))
		(
			DisablePlayerCheckpoint(playerid)

			Checkpoint(playerid) = 0

			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Namierzanie zosta³o wy³¹czone., OK, )
			return 1
		)
		else
		(
			hrp_Tip(playerid, /namierz (Numer telefonu))
			return 1
		)
	)

	string(128)

	if(!IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI) && !IsPlayerInGroupType(playerid, GROUP_ARMY))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie masz uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)

	if(TrackPhone(playerid, number))
	(
		Checkpoint(playerid) = 1

		format(string, sizeof(string), Namierzony zosta³ telefon %d.\nAby anulowaæ namierzanie, wpisz komendê /namierz., number)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )
	)
	return 1
)*/

CMD:sprobuj(playerid, params())
(
	if(isnull(params))
	(
		hrp_Tip(playerid, /sprobuj (Akcja np. podnieœæ ciê¿arek))
		return 1
	)
	string(256), loss = random(100)

	switch(loss)
	(
		case 0..50:
		(
  			if(PlayerCache(playerid)(pSex) == 1)
			(
				format(string, sizeof(string), *** %s zawiód³ próbuj¹c %s, PlayerName(playerid), params)
				ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			)
			else
			(
				format(string, sizeof(string), *** %s zawiod³a próbuj¹c %s, PlayerName(playerid), params)
				ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			)
		)
		case 51..99:
		(
  			if(PlayerCache(playerid)(pSex) == 1)
			(
				format(string, sizeof(string), *** %s odniós³ sukces próbuj¹c %s, PlayerName(playerid), params)
				ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			)
			else
			(
				format(string, sizeof(string), *** %s odnios³a sukces próbuj¹c %s, PlayerName(playerid), params)
				ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			)
		)
	)
	return 1
)

CMD:tog(playerid, params())
(
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /tog (w | grupa | glod ))
		return 1
	)

	if(!strcmp(type, token, true))
	(
		if(PlayerCache(playerid)(pAdmin) == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		else
		(
			if(PlayerCache(playerid)(pAdminToken))
			(
				PlayerCache(playerid)(pAdminToken) = false
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~y~Token zostal ~g~wylaczony, 3000, 3)
			)
			else
			(
				PlayerCache(playerid)(pAdminToken) = true
				GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~y~Token zostal ~r~wlaczony, 3000, 3)
			)
		)
	)
	
	if(!strcmp(type, w, true))
	(
		if(PlayerCache(playerid)(pTogW))
		(
			PlayerCache(playerid)(pTogW) = false
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~y~Otrzymywanie wiadomosci ~g~wlaczone, 3000, 3)
		)
		else
		(
			PlayerCache(playerid)(pTogW) = true
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~y~Otrzymywanie wiadomosci ~r~wylaczone, 3000, 3)
		)
	)

	if(!strcmp(type, grupa, true))
	(
		if(PlayerCache(playerid)(pTogOOC))
		(
			PlayerCache(playerid)(pTogOOC) = false
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~y~Czaty grupowe ~g~wlaczone, 3000, 3)
		)
		else
		(
			PlayerCache(playerid)(pTogOOC) = true
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~y~Czaty grupowe ~r~wylaczone, 3000, 3)
		)
	)

	return 1
)

CMD:ignoruj(playerid, params())
(
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /ignoruj (ID gracza))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz ignorowaæ swoich wiadomoœci., OK, )
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
	if(PlayerCache(playerid)(pPlayerIgnored)(giveplayer_id))
	(
		PlayerCache(playerid)(pPlayerIgnored)(giveplayer_id) = false

		format(string, sizeof(string), Wiadomoœci przychodz¹ce od gracza %s nie bêd¹ ju¿ ignorowane., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	)
	else
	(
		PlayerCache(playerid)(pPlayerIgnored)(giveplayer_id) = true

		format(string, sizeof(string), Wiadomoœci przychodz¹ce od gracza %s bêd¹ od teraz ignorowane., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	)
	return 1
)

CMD:stats(playerid, params())
(
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		ShowPlayerStats(playerid, playerid)
		return 1
	)
	//if(PlayerCache(playerid)(pAdmin) == 0)
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerStats(playerid, playerid)
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
	ShowPlayerStats(playerid, giveplayer_id)
	return 1
)

CMD:admins(playerid, params())
(
	list_admins(2048)
	
	format(list_admins, sizeof(list_admins), Pamiêtaj, ¿e cz³onek ekipy na s³u¿bie dostaje bardzo du¿o wiadomosci od wszystkich graczy.\n)
	format(list_admins, sizeof(list_admins), %sPisz¹c wiadomosæ zawrzyj tylko najwa¿niejsze informacje. Powitania zachowaj na inn¹ okazje.\n, list_admins)
	format(list_admins, sizeof(list_admins), %sPamiêtaj te¿ aby o mniejsze sprawy prosiæ (6698FF)supporterów(FFFFFF).\n, list_admins)
	format(list_admins, sizeof(list_admins), %sAktualnie na s³u¿bie:\n, list_admins)

	count = strlen(list_admins)

	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
	   	  	if(PlayerCache(i)(pAdminDuty))
	   	  	(
				if(PlayerCache(i)(pAdmin) ( -1)
				(
					format(list_admins, sizeof(list_admins), %s\n%d\t(%s)%s(FFFFFF)\t%d\t\t%s, list_admins, i, AL(PlayerCache(i)(pUserColor))(lColor), AL(PlayerCache(i)(pUserColor))(lTag), (PlayerCache(i)(pAdmin) * -1), PlayerName(i))
				)
				if(PlayerCache(i)(pAdmin) ) 0 || PlayerCache(i)(pAdmin) == -1)
				(
					format(list_admins, sizeof(list_admins), %s\n%d\t(%s)%s(FFFFFF)\t\t\t%s, list_admins, i, AL(PlayerCache(i)(pUserColor))(lColor), AL(PlayerCache(i)(pUserColor))(lTag), PlayerName(i))
				)
			)
		)
	)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
	   	  	if(!PlayerCache(i)(pAdminDuty) && PlayerCache(playerid)(pAdmin) != 0)
			(
				if(PlayerCache(i)(pAdmin) ( -1)
				(
					format(list_admins, sizeof(list_admins), %s\n%d\t(%s)%s(FFFFFF)\t%d\t\t%s - Poza s³u¿b¹, list_admins, i, AL(PlayerCache(i)(pUserColor))(lColor), AL(PlayerCache(i)(pUserColor))(lTag), (PlayerCache(i)(pAdmin) * -1), PlayerName(i))
				)
				if(PlayerCache(i)(pAdmin) ) 0 || PlayerCache(i)(pAdmin) == -1)
				(
					format(list_admins, sizeof(list_admins), %s\n%d\t(%s)%s(FFFFFF)\t\t\t%s - Poza s³u¿b¹, list_admins, i, AL(PlayerCache(i)(pUserColor))(lColor), AL(PlayerCache(i)(pUserColor))(lTag), PlayerName(i))
				)
			)
		)
	)
	if(strlen(list_admins) ) count)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Administratorzy on-line:, list_admins, OK, )
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie znaleziono ¿adnych administratorów on-line., OK, )
	)
	return 1
)

CMD:a(playerid, params()) return cmd_admins(playerid, params)

CMD:odblokuj(playerid, params())
(
	if(!IsPlayerInAnyVehicle(playerid))
	(
		GuiMsg(playerid, Aby odblokowaæ pojazd musisz pierw w jakimœ byæ., 1)
		return 1
	)
	
	// Antybug jak zwykle
	bool:checkbug = false
	if(gettime() - LogTime(playerid) ) 60)
		checkbug= true
	
	if(!checkbug)
	(
		GuiMsg(playerid, Musisz chwilê odczekaæ nim u¿yjesz tej komendy., 0)
		return 1
	)
	
	veh_id = GetPlayerVehicleID(playerid)
	if(!CarInfo(veh_id)(cWheelBlock))
	(
		GuiMsg(playerid, Ten pojazd nie ma za³o¿onej blokady., 1)
		return 1
	)
	
	if(CarInfo(veh_id)(cOwnerType) != OWNER_PLAYER || CarInfo(veh_id)(cOwner) != PlayerCache(playerid)(pUID))
	(
		GuiMsg(playerid, Nie jesteœ w³aœcicielem tego pojazdu., 1)
		return 1
	)
	
	if(CarInfo(veh_id)(cAccess) & VEH_ACCESS_DIM)
	(
		GuiMsg(playerid, Nie mo¿esz odblokowaæ pojazdu gdy ten ma zamontowane przyciemniane szyby., 1)
		return 1
	)

	if(!(PlayerCache(playerid)(pDocuments) & DOC_DRIVER))
	(
		GuiMsg(playerid, Musisz posiadaæ prawo jazdy by odebraæ pojazd., 1)
		return 1
	)
	
	if(!CarInfo(veh_id)(cRegister))
	(
		GuiMsg(playerid, Ten pojazd musi byæ zarejestrowany by móc go odblokowaæ., 1)
		return 1
	)
	
	price = CarInfo(veh_id)(cWheelBlock)
	if(PlayerCache(playerid)(pCash) ( price)
	(
		GuiMsg(playerid, Nie masz wystarczaj¹co pieniêdzy by odblokowaæ ten pojazd., 1)
		return 1
	)
	
	CarInfo(veh_id)(cWheelBlock) = 0
	SaveVehicle(veh_id, SAVE_VEH_ACCESS)
	Float:x, Float:y, Float:z
	GetVehiclePos(veh_id, x, y, z)
	
	hrp_VehicleActionLog(%s (UID: %d) odblokowa³ pojazd %s (UID: %d) (Cena: %d, X: %f, Y: %f, Z: %f), PlayerRealName(playerid), PlayerCache(playerid)(pUID), CarInfo(veh_id)(cName), CarInfo(veh_id)(cUID), price, x, y, z)
	hrp_GivePlayerMoney(playerid, -price)
	GuiMsg(playerid, Blokada zosta³a zdjêta., 0)
	return 1
)

CMD:silnik(playerid, params())
(
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	(
		vehid = GetPlayerVehicleID(playerid), model = GetVehicleModel(vehid)
		if(CarInfo(vehid)(cWheelBlock))
		(
			string(256)
			format(string, sizeof(string), Na ko³o tego pojazdu zosta³a na³o¿ona blokada.\nJe¿eli jesteœ w³aœcicielem tego pojazdu, musisz zg³oœiæ siê na\nkomisariat policji w celu zdjêcia blokady za podan¹ poni¿ej kwotê pieniê¿n¹.\n\nIdentyfikator pojazdu: %d\nKoszt zdjêcia blokady wynosi: $%d, CarInfo(vehid)(cUID), CarInfo(vehid)(cWheelBlock))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			
			sendClientPoop(playerid, » Mo¿esz odblokowaæ ten pojazd wpisuj¹c /odblokuj.)
			return 1
		)
  		if(model == 509 || model == 510 || model == 481)
		(
			return 1
		)
		if(PlayerCache(playerid)(pGamePoints) ( 50)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz prowadziæ pojazdów nie maj¹c 50 GameScore., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_NONE)
		(
			if(model != 574)
			(
				if(!PlayerCache(playerid)(pAdmin))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczyków do tego pojazdu., OK, )
					return 1
				)
			)
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
		(
			if(CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID) && !HavePlayerVehicleKeys(playerid, vehid))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczyków do tego pojazdu., OK, )
				return 1
			)
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
		(
			if(PlayerCache(playerid)(pHireGroup) != INVALID_GROUP_ID && PlayerCache(playerid)(pHireTime) ) 0)
			(
				group_id_fix = GetGroupID(CarInfo(vehid)(cOwner))
				if(GroupData(group_id_fix)(gType) != GROUP_HIRE)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczyków do tego pojazdu., OK, )
					return 1
				)
			)
			else
			(
				if(!PlayerCache(playerid)(pDrivingLesson))
				(
					if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczyków do tego pojazdu., OK, )
						return 1
					)
				)
				else
				(
					group_id_fix = GetGroupID(CarInfo(vehid)(cOwner))
					if(GroupData(group_id_fix)(gType) != GROUP_DRIVING)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kluczyków do tego pojazdu., OK, )
						return 1
					)
				)
			)
		)
		if(CarInfo(vehid)(cHealth) ( 360)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Silnik w tym pojeŸdzie jest ca³kowicie zniszczony., OK, )
			return 1
		)
		if(CarInfo(vehid)(cEngineTogged))
		(
			CarInfo(vehid)(cEngineTogged) = false
			ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))

			hrp_VehicleActionLog(%s (UID: %d) zgasil silnik pojazdu %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), CarInfo(vehid)(cName), CarInfo(vehid)(cUID))
		)
		else
		(
			string(256)
			format(string, sizeof(string), ** %s przekrêca kluczyk w stacyjce., PlayerName(playerid))
			FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Trwa uruchamianie silnika..., 3500, 3)
			SetTimerEx(OnVehicleEngineStarted, 2000, 0, d, vehid)
		)
	)
	return 1
)

CMD:dach(playerid,params())
(
	if(!IsPlayerInAnyVehicle(playerid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie, by móc zmieniæ stan dachu., OK, )
		return 1
	)
	else
	(
		vehicleid = GetPlayerVehicleID(playerid)
		if(GetVehicleModel(vehicleid) == 567)
		(
			seat = GetPlayerVehicleSeat(playerid)
			if(seat != 0)
			(
				GuiMsg(playerid,Tylko kierowca mo¿e u¿ywaæ tej komendy.,1)
				return 1
			)

			slot = GetVehicleComponentType(1131)
			dach = CarInfo(vehicleid)(cComponent)(slot)+999
			if(dach == 1131)
			(
				if(!CarInfo(vehicleid)(cTop))
				(
					//zaloz
					CarInfo(vehicleid)(cTop) = true
					AddVehicleComponent(vehicleid, 1131)
					GameTextForPlayer(playerid, ~w~dach ~g~wysuniety, 3000, 6)
				)
				else
				(
					//sciagnij
					CarInfo(vehicleid)(cTop) = false
					RemoveVehicleComponent(vehicleid, 1131)
					GameTextForPlayer(playerid, ~w~dach ~r~schowany, 3000, 6)
				)
			)
			else
			(
				GuiMsg(playerid,Ten pojazd nie posiada wymaganego komponentu.,1)
			)
		)
		else
		(
			GuiMsg(playerid,Ten pojazd nie ma mo¿liwoœci œci¹gania dachu.,1)
		)
	)

	return 1
)

CMD:pasy(playerid, params())
(
	if(!IsPlayerInAnyVehicle(playerid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie, by móc zapi¹æ pasy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pBelts))
	(
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0)
		GameTextForPlayer(playerid, ~w~pasy ~g~odpiete, 3000, 6)

		PlayerCache(playerid)(pBelts) = false
	)
	else
	(
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0)
		GameTextForPlayer(playerid, ~w~pasy ~r~zapiete, 3000, 6)

		PlayerCache(playerid)(pBelts) = true
	)
	return 1
)

CMD:okno(playerid, params())
(
	/*
	CarInfo(gameid)(cDriverWindowOpen) = 1
	CarInfo(gameid)(cPassengerWindowOpen) = 1
	CarInfo(gameid)(cLeftWindowOpen) = 1
	CarInfo(gameid)(cRightWindowOpen) = 1
	*/
	if(!IsPlayerInAnyVehicle(playerid))
	(
		string(64), vehid = GetClosestVehicle(playerid)
		if(CarInfo(vehid)(cWindowOpen))
		(
			format(string, sizeof(string), ** Szyby pojazdu %s s¹ otwarte. **, CarInfo(vehid)(cName))
		)
		else
		(
			format(string, sizeof(string), ** Szyby pojazdu %s s¹ zamkniête. **, CarInfo(vehid)(cName))
		)
		ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, false)
		return 1
	)

	vehid = GetPlayerVehicleID(playerid)
	if(!HasWindow(vehid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd nie ma okien., OK, )
		return 1
	)
	vehmodel = GetVehicleModel(vehid)
	seat = GetPlayerVehicleSeat(playerid)
	if((vehmodel == 596 || vehmodel == 597 || vehmodel == 598 || vehmodel == 490) && (seat == 2 || seat == 3))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W radiowozie z tylu nie mozna otwierac okien., OK, )
		return 1
	)
	foreach(Player, i)
	(
		if(IsPlayerInAnyVehicle(i))
		(
			if(GetPlayerVehicleID(i) == vehid)
			(
				if(GetPlayerWindowStatus(vehid, playerid))
				(
					PlayerPlaySound(i, 34601, 0.0, 0.0, 0.0)
				)
				else
				(
					PlayerPlaySound(i, 34601, 0.0, 0.0, 0.0)
				)
			)
		)
	)
	/*if(CarInfo(vehid)(cWindowOpen))
	(
		CarInfo(vehid)(cWindowOpen) = false
	)
	else
	(
		CarInfo(vehid)(cWindowOpen) = true
	)*/
	ChangeWindowStatus(vehid, playerid)
	return 1
)
CMD:szyba(playerid, params()) return cmd_okno(playerid, params)

CMD:okna(playerid, params())
(
	/*
	CarInfo(gameid)(cDriverWindowOpen) = 1
	CarInfo(gameid)(cPassengerWindowOpen) = 1
	CarInfo(gameid)(cLeftWindowOpen) = 1
	CarInfo(gameid)(cRightWindowOpen) = 1
	*/
	if(!IsPlayerInAnyVehicle(playerid))
	(
		string(64), vehid = GetClosestVehicle(playerid)
		if(CarInfo(vehid)(cWindowOpen))
		(
			format(string, sizeof(string), ** Szyby pojazdu %s s¹ otwarte. **, CarInfo(vehid)(cName))
		)
		else
		(
			format(string, sizeof(string), ** Szyby pojazdu %s s¹ zamkniête. **, CarInfo(vehid)(cName))
		)
		ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, false)
		return 1
	)

	vehid = GetPlayerVehicleID(playerid)
	if(!HasWindow(vehid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd nie ma okien., OK, )
		return 1
	)
	seat = GetPlayerVehicleSeat(playerid)
	if(seat != 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, To funkcja tylko dla kierowcy., OK, )
		return 1
	)
	window(64)
	if(sscanf(params, s(64), window))
	(
		hrp_Tip(playerid, /okna (otworz | zamknij))
		return 1
	)
	foreach(Player, i)
	(
		if(IsPlayerInAnyVehicle(i))
		(
			if(GetPlayerVehicleID(i) == vehid)
			(
				PlayerPlaySound(i, 34601, 0.0, 0.0, 0.0)
			)
		)
	)
	
	if(!strcmp(window, otworz, true))
	(
		ChangeSelectedWindowStatus(vehid, 0)
	)
	else if(!strcmp(window, zamknij, true))
	(
		ChangeSelectedWindowStatus(vehid, 1)
	)
	return 1
)
CMD:szyby(playerid, params()) return cmd_okna(playerid, params)

CMD:bw(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) ) -2 && PlayerCache(playerid)(pAdmin) ( 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32), string(128)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /bw (naloz | zdejmij | lista))
		return 1
	)
	if(!strcmp(type, naloz, true))
	(
		giveplayer_id, time
		if(sscanf(varchar, ud, giveplayer_id, time))
		(
			hrp_Tip(playerid, /bw naloz (ID gracza) (Czas BW (min)))
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
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma ju¿ BW.\nU¿yj /bw zdejmij, aby zdj¹æ BW., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pBW) = time * 60
		GetPlayerPos(giveplayer_id, PlayerCache(giveplayer_id)(pPosX), PlayerCache(giveplayer_id)(pPosY), PlayerCache(giveplayer_id)(pPosZ))

		PlayerCache(giveplayer_id)(pInt) = GetPlayerInterior(playerid)
		PlayerCache(giveplayer_id)(pVW) = GetPlayerVirtualWorld(playerid)

		SetPlayerCameraPos(giveplayer_id, PlayerCache(giveplayer_id)(pPosX) + 3, PlayerCache(giveplayer_id)(pPosY) + 4, PlayerCache(giveplayer_id)(pPosZ) + 7)
		SetPlayerCameraLookAt(giveplayer_id, PlayerCache(giveplayer_id)(pPosX), PlayerCache(giveplayer_id)(pPosY), PlayerCache(giveplayer_id)(pPosZ))

		hrp_TogglePlayerControllable(giveplayer_id, 0)

		SavePlayerStats(giveplayer_id, SAVE_PLAYER_POS)

		format(string, sizeof(string), Administrator %s na³o¿y³ Ci BW. Czas: %d min, PlayerName(playerid), time)
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Pomyœlnie na³o¿ono BW graczowi %s (ID: %d, UID: %d). Czas: %d min., PlayerName(giveplayer_id), giveplayer_id, PlayerCache(giveplayer_id)(pUID), time)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, zdejmij, true))
	(
 		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /bw zdejmij (ID gracza))
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
		if(!PlayerCache(giveplayer_id)(pBW))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie ma BW., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pBW) = 0
		PlayerCache(giveplayer_id)(pWounded) = 0

		PlayerCache(playerid)(pKiller) = 0
		PlayerCache(playerid)(pKillerWeapon) = 0

		ApplyAnimation(giveplayer_id, Attractors, Stepsit_out, 4.0, 0, 0, 0, 0, 0, 1)
		hrp_TogglePlayerControllable(giveplayer_id, 1)

		SetCameraBehindPlayer(giveplayer_id)
		hrp_SetPlayerHealth(giveplayer_id, 20)

		PlayerCache(giveplayer_id)(pWoundAnim) = false
		PlayerCache(giveplayer_id)(pWoundedTime) = 0
		PlayerCache(giveplayer_id)(pBleeding) = 0

		format(string, sizeof(string), Administrator %s zdj¹³ Ci BW, PlayerName(playerid))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Pomyœlnie zdjêto BW graczowi %s (ID: %d, UID: %d)., PlayerName(giveplayer_id), giveplayer_id, PlayerCache(giveplayer_id)(pUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, lista, true))
	(
		list_players(256)
		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pBW))
				(
					format(list_players, sizeof(list_players), %s\n%d\t%d min\t%s, list_players, i, PlayerCache(i)(pBW) / 60, PlayerName(i))
				)
			)
		)
		if(!strlen(list_players))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie znaleziono ¿adnych graczy maj¹cych BW., OK, )
		)
		ShowPlayerDialog(playerid, D_BW_LIST, DIALOG_STYLE_LIST, Znaleziono graczy maj¹cych BW:, list_players, Sciag, Zamknij)
		return 1
	)
	return 1
)

CMD:wound(playerid, params())
(
	string(16)
	format(string, sizeof(string), Wound: %d, PlayerCache(playerid)(pWounded))
	SendClientMessage(playerid, COLOR_WHITE, string)
	return 1
)

CMD:bagaznik(playerid, params())
(
	vehid
	if(IsPlayerInAnyVehicle(playerid))
	(
		vehid = GetPlayerVehicleID(playerid)
	)
	else
	(
		vehid = GetClosestVehicle(playerid)
	)

	if(!strcmp(params, wyjmij, true) || !strcmp(params, wez, true) || !strcmp(params, podnies, true))
	(
		if(IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wyj¹æ przedmiotu z baga¿nika bêd¹c w pojeŸdzie., OK, )
			return 1
		)
		if(GetVehicleBootStatus(vehid) == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Otwórz baga¿nik w celu wyjêcia przedmiotu. (/bagaznik), OK, )
			return 1
		)
		PlayerCache(playerid)(pRaising) = true
		ListPlayerTrunkItems(playerid, vehid)
		return 1
	)

	if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
		return 1
	)
	if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
	(
		if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
			return 1
		)
	)

	if(GetVehicleBootStatus(vehid) == 1)
	(
		ChangeVehicleBootStatus(vehid, false)
		GameTextForPlayer(playerid, ~w~Bagaznik ~r~zamkniety, 5000, 3)
	)
	else
	(
		ChangeVehicleBootStatus(vehid, true)
		GameTextForPlayer(playerid, ~w~Bagaznik ~g~otwarty, 5000, 3)
	)
	return 1
)

CMD:maska(playerid, params())
(
	vehid
	if(IsPlayerInAnyVehicle(playerid))
	(
		vehid = GetPlayerVehicleID(playerid)
	)
	else
	(
		vehid = GetClosestVehicle(playerid)
	)

	if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
		return 1
	)
	if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
	(
		if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
			return 1
		)
	)

	if(GetVehicleBonnetStatus(vehid) == 1)
	(
		ChangeVehicleBonnetStatus(vehid, false)
		GameTextForPlayer(playerid, ~w~Maska ~r~zamknieta, 5000, 3)
	)
	else
	(
		ChangeVehicleBonnetStatus(vehid, true)
		GameTextForPlayer(playerid, ~w~Maska ~g~otwarta, 5000, 3)
	)
	return 1
)

CMD:odwyk(playerid, params())
(
	charge = 350

	if(PlayerCache(playerid)(pHospitalization))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Jesteœ w trakcie hospitalizacji, powinieneœ le¿eæ w swojej sali., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz poddaæ siê odwykowi w trakcie kary OOC., OK, )
		return 1
	)
	if(!IsPlayerInRangeOfPoint(playerid, 15.0, 1167.7534,-1324.5004,15.3936))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w izbie przyjêæ szpitala., OK, )
		return 1
	)
	if(GetPlayerVirtualWorld(playerid) != 2825 && GetPlayerVirtualWorld(playerid) != 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w izbie przyjêæ szpitala., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pBankCash) ( charge)
	(
		string(128)
		format(string, sizeof(string), Nie masz wystarczaj¹cych œrodków na koncie aby poddaæ siê odwykowi.\nAktualny koszt to: $%d., charge)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
		return 1
	)

	rand = random(sizeof(HospitalBed))

	PlayerCache(playerid)(pHospitalization) = 10 * 60
	PlayerCache(playerid)(pHospitalCharge) = charge
	PlayerCache(playerid)(pHospitalBed) = rand
	
	PlayerCache(playerid)(pDependence) -= 50.0
	if(PlayerCache(playerid)(pDependence) ( 0.0)
		PlayerCache(playerid)(pDependence) = 0.0

	SetPlayerPos(playerid, HospitalBed(rand)(bPosX), HospitalBed(rand)(bPosY), HospitalBed(rand)(bPosZ))
	SetPlayerInterior(playerid, HospitalBed(rand)(bINT))
	SetPlayerVirtualWorld(playerid, HospitalBed(rand)(bVW))

	ApplyAnimation(playerid, BEACH, bather, 4.0, 1, 0, 0, 0, 0, 0)
	return 1
)

CMD:szpital(playerid, params())
(
	string(128)
	medics = 0
	insuranceUID = PlayerCache(playerid)(pInsuranceCompany)
	insuranceID = GetGroupID(insuranceUID)
	foreach(Player, i)
	(
		if(IsPlayerInGroupType(playerid, GROUP_MEDICAL))
		(
			group_id_fix = GetPlayerDutyGroupID(playerid)
			if(group_id_fix != INVALID_GROUP_ID)
			(
				if(GroupData(group_id_fix)(gType) == GROUP_MEDICAL)
				(
					medics++
				)
			)
		)
	)

	if(medics )= 3)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie wiêcej ni¿ 2 medyków jest na s³u¿bie, dlatego hospitalizacja jest niedostêpna., OK, )
		return 1
	)

	Float:health, charge = floatround((100 - floatround(health)) * 1.5)
	GetPlayerHealth(playerid, health)

	if(IsPlayerInAnyVehicle(playerid))
	(
		vehicle_id = GetPlayerVehicleID(playerid)
		if(GetVehicleModel(vehicle_id) == 416)
		(
			foreach(Player, i)
			(
				if(IsPlayerInAnyVehicle(i))
				(
					if(GetPlayerVehicleID(i) == vehicle_id)
					(
						if(IsPlayerInGroupType(i, GROUP_FIREDEPT) || IsPlayerInGroupType(i, GROUP_MEDICAL))
						(
							charge = floatround(charge / 3)
						)
					)
				)
			)
		)
	)

	if(PlayerCache(playerid)(pHospitalization))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, JesteœÂ¶ w trakcie hospitalizacji, powinieneœ le¿eæ w swojej sali., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz poddaæ siê hospitalizacji w trakcie kary OOC., OK, )
		return 1
	)
	if(!IsPlayerInRangeOfPoint(playerid, 15.0, 1167.7534,-1324.5004,15.3936))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w izbie przyjêæ szpitala., OK, )
		return 1
	)
	if(GetPlayerVirtualWorld(playerid) != 2825 && GetPlayerVirtualWorld(playerid) != 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w izbie przyjêæ szpitala., OK, )
		return 1
	)
	
	if(PlayerCache(playerid)(pInsurance) )= gettime()) // ma ubezpieczenie
	(
		if(GroupData(insuranceID)(gCash) )= 45 && PlayerCache(playerid)(pInsuranceCount) (= 14) // grupa ma kasÄ™ i nie wykorzystaÅ‚ limitu
		(
			charge = 0
		)
	)
	if(PlayerCache(playerid)(pBankCash) ( charge)
	(
		format(string, sizeof(string), Nie masz wystarczaj¹cych œrodków na koncie aby poddaæ siê hospitalizacji.\nAktualny koszt to: $%d., charge)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
		return 1
	)

	rand = random(7)

	if(PlayerCache(playerid)(pInsurance) ( gettime()) // nie ma ubezpieczenia
	(
		PlayerCache(playerid)(pHospitalization) = 10 * 60
		PlayerCache(playerid)(pHospitalCharge) = charge
		PlayerCache(playerid)(pHospitalBed) = rand
		PlayerCache(playerid)(pBleeding) = 12 * 60
	)
	else // ma ubezpieczenie
	(
		if(PlayerCache(playerid)(pInsuranceCount) (= 14) // nie wykorzystal limitu
		(
			if(GroupData(insuranceID)(gCash) )= 45) // firma ma wiÄ™cej niÅ¼ 45 dolce
			(
				GroupData(insuranceID)(gCash) -= 45
				SaveGroup(insuranceID)
				hrp_GroupActionLog(%s (UID: %d) korzysta z hospitalizacji firmy %s (UID: %d). Stan konta wynosi: $%d., PlayerRealName(playerid), PlayerCache(playerid)(pUID), GroupData(insuranceID)(gName), GroupData(insuranceID)(gUID), GroupData(insuranceID)(gCash))
				AddGroupLog(playerid, insuranceID, %s korzysta z hospitalizacji., PlayerName(playerid))
				PlayerCache(playerid)(pInsuranceCount)++
				SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
				PlayerCache(playerid)(pHospitalization) = 5 * 60
				PlayerCache(playerid)(pHospitalCharge) = charge
				PlayerCache(playerid)(pHospitalBed) = rand
				PlayerCache(playerid)(pBleeding) = 6 * 60
				format(string, sizeof(string), Jestes w trakcie hospitalizacji.\nCalosc oplat zostala pobrana z Twojego ubezpieczenia.)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Hospitalizacja, string, OK, )
			)
			else
			(
				PlayerCache(playerid)(pHospitalization) = 10 * 60
				PlayerCache(playerid)(pHospitalCharge) = charge
				PlayerCache(playerid)(pHospitalBed) = rand
				PlayerCache(playerid)(pBleeding) = 12 * 60
				format(string, sizeof(string), Konto twojego ubezpieczyciela jest puste.\nZostajesz oddany na platne leczenie.)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Hospitalizacja, string, OK, )
			)
		)
		else
		(
			PlayerCache(playerid)(pHospitalization) = 10 * 60
			PlayerCache(playerid)(pHospitalCharge) = charge
			PlayerCache(playerid)(pHospitalBed) = rand
			PlayerCache(playerid)(pBleeding) = 12 * 60
			format(string, sizeof(string), Wykorzystales juz limit 15 hospitalizacji z ubezpieczenia.\nZostajesz oddany na platne leczenie.)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Hospitalizacja, string, OK, )
		)
	)

	SetPlayerPos(playerid, HospitalBed(rand)(bPosX), HospitalBed(rand)(bPosY), HospitalBed(rand)(bPosZ))
	SetPlayerInterior(playerid, HospitalBed(rand)(bINT))
	SetPlayerVirtualWorld(playerid, HospitalBed(rand)(bVW))

	ApplyAnimation(playerid, BEACH, bather, 4.0, 1, 0, 0, 0, 0, 0)
	return 1
)

CMD:leczenie(playerid, params())
(
	if(!PlayerCache(playerid)(pArrest))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie nie siedzisz w areszcie., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pHospitalization))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Jesteœ w trakcie leczenia, powinieneœ le¿eæ na swoim ³ó¿ku., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz poddaæ siê hospitalizacji w trakcie kary OOC., OK, )
		return 1
	)
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, 1764.1101,-1549.7306,39.9341))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w punkcie medycznym placówki., OK, )
		return 1
	)
	if(GetPlayerVirtualWorld(playerid) != PrisonWorld)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w punkcie medycznym placówki., OK, )
		return 1
	)
	
	PrisonersHospi = 0
	foreach(Player, i)
	(
		if(PlayerCache(i)(pHospitalBed) == 7 || PlayerCache(i)(pHospitalBed) == 8)
		(
			PrisonersHospi++
		)
	)
	if(PrisonersHospi )= 2)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie nie mo¿esz poddaæ siê leczeniu, zbyt du¿o wiêŸniów przebywa w punkcie medycznym.\nPrzyjdŸ póŸniej., OK, )
		return 1
	)
	rand = random(2)
	bed = rand+7
	
	PlayerCache(playerid)(pHospitalization) = 10 * 60
	PlayerCache(playerid)(pHospitalCharge) = 0
	PlayerCache(playerid)(pHospitalBed) = bed
	PlayerCache(playerid)(pBleeding) = 12 * 60
	
	SetPlayerPos(playerid, HospitalBed(bed)(bPosX), HospitalBed(bed)(bPosY), HospitalBed(bed)(bPosZ))
	SetPlayerInterior(playerid, HospitalBed(bed)(bINT))
	SetPlayerVirtualWorld(playerid, HospitalBed(bed)(bVW))

	ApplyAnimation(playerid, BEACH, bather, 4.0, 1, 0, 0, 0, 0, 0)
	return 1
)

CMD:akceptujsmierc(playerid, params())
(
	if(!PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, U¿ywanie tej komendy dostêpne jest tylko podczas stanu nieprzytomnoœci., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pPremium)) (
		if(PlayerCache(playerid)(pHours) ( 3)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz uœmierciæ postaci, na której przegra³eœ mniej ni¿ 3 godzin., OK, )
			return 1
		)
	)
	else
	(
		if(PlayerCache(playerid)(pHours) ( 10)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz uœmierciæ postaci, na której przegra³eœ mniej ni¿ 10 godzin., OK, )
			return 1
		)
	)

	ShowPlayerDialog(playerid, D_FCK_REASON_P, DIALOG_STYLE_INPUT, Zaakceptuj œmieræ, Opisz okolicznoœci swojej œmierci, OK, Anuluj)
	return 1
)

CMD:kup(playerid, params())
(
	blint_CashBugFixer(playerid)
	
	for(i = 0  i ( MAX_PRESSBOX i++)
	(
		if(IsPlayerInRangeOfPoint(playerid,2.0,PressBox(i)(bPosX),PressBox(i)(bPosY),PressBox(i)(bPosZ)))
		(
			if(GetPlayerVirtualWorld(playerid) == PressBox(i)(bVW))
			(
				if(PressBox(i)(bAmount) ) 0)
				(
					//kup
					ShowPlayerDialog(playerid,D_PRESS_BUY,DIALOG_STYLE_MSGBOX,Budka z gazetami,(9E9E9E)Czy chcesz kupiæ gazetê za (00CE00)$3(9E9E9E)?,Tak,Nie)
					return 1
				)
				else
				(
					GuiMsg(playerid,Niestety skoñczy³y siê gazety w tym pojemniku.,0)
					return 1
				)
			)
		)
	)

	doorid

	if(GetPlayerVirtualWorld(playerid) == 0)
	(
		foreach(Booths, boothid)
		(
			if(IsPlayerInRangeOfPoint(playerid, BoothData(boothid)(bRadius), BoothData(boothid)(bPosX), BoothData(boothid)(bPosY), BoothData(boothid)(bPosZ)))
			(
				dooruid = BoothData(boothid)(bDoorUID)

				foreach(Doors, door)
				(
					if(DoorData(door)(dUID) == dooruid)
					(
						doorid = door
					)
				)
				break
			)
		)
	)
	else
	(
		doorid = GetPlayerDoorID(playerid)
	)

	if(doorid == INVALID_DOOR_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wyst¹pi³ problem z magazynem Tej budki. Zg³oœ siê do Administracji w celu naprawienia problemu., OK, )
		return 1
	)
	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku lub budce biznesu gastronomicznego., OK, )
		return 1
	)
	group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
	if(GroupData(group_id_fix)(gType) != GROUP_GASTRONOMY)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku lub budce biznesu gastronomicznego., OK, )
		return 1
	)

	MainPlayerTable(playerid) = doorid
	mysql_query_format(SELECT product_uid, product_number, product_price, product_name FROM hrp_products WHERE product_dooruid = %d, DoorData(doorid)(dUID))

	data(128), list_items(1024),
 		product_uid, product_name(32), product_number, product_price

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ddds(32), product_uid, product_number, product_price, product_name)
		format(list_items, sizeof(list_items), %s\n%d\tx%d\t$%d\t%s, list_items, product_uid, product_number, product_price, product_name)
	)
	mysql_free_result()
	if(strlen(list_items) ) 0)
	(
		ShowPlayerDialog(playerid, D_BUY_PRODUCT, DIALOG_STYLE_LIST, Zakup produktu, list_items, Zakup, Anuluj)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych produktów w magazynie., OK, )
	)
	return 1
)

CMD:ubranie(playerid, params())
(
	doorid = GetPlayerDoorID(playerid)
	if(doorid == INVALID_DOOR_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku sklepu z odzie¿¹., OK, )
		return 1
	)
	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku sklepu z odzie¿¹., OK, )
		return 1
	)
	group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
	if(GroupData(group_id_fix)(gType) != GROUP_CLOTHES)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku sklepu z odzie¿¹., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pClothChanging) || PlayerCache(playerid)(pAccessChanging))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie korzystasz ju¿ z edytora., OK, )
		return 1
	)

	ShowPlayerDialog(playerid, D_SELECT_CLOTH_OPTION, DIALOG_STYLE_LIST, Wybierz rodzaj:, 1 - Ubranie\n2 - Akcesoria, Wybierz, Anuluj)
	return 1
)

CMD:pokoj(playerid, params())
(
	type(32), varchar(32), string(256), doorid = GetPlayerDoorID(playerid)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /pokoj (zamelduj | wymelduj | wejdz | wyjdz | koszt))
		return 1
	)
	if(!strcmp(type, zamelduj, true))
	(
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
		if(GroupData(group_id_fix)(gType) != GROUP_HOTEL)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pHotel))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Jesteœ zameldowany ju¿ w jakimœ hotelu., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pBankCash) ( GroupData(group_id_fix)(gValue1))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie masz wystarczaj¹co du¿o poeniêdzy na koncie., OK, )
			return 1
		)

		PlayerCache(playerid)(pHotel) = DoorData(doorid)(dUID)
		PlayerCache(playerid)(pSpawnPlace) = SPAWN_HOTEL

		format(string, sizeof(string), Wynaj¹³eœ pokój w hotelu \%s\.\nOp³ata bêdzie pobierana przy ka¿dej wyp³acie.\n\nTwój numer pokoju to: %d, DoorData(doorid)(dName), PlayerCache(playerid)(pUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, wymelduj, true))
	(
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
		if(GroupData(group_id_fix)(gType) != GROUP_HOTEL)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
 		if(!PlayerCache(playerid)(pHotel))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ zameldowany w ¿adnym z hoteli., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pHotel) != DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu, którym jesteœ zameldowany., OK, )
			return 1
		)
		PlayerCache(playerid)(pHotel) = 0

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Skoñczy³eœ wynajmowanie pokoju w tym hotelu.\nOp³ata za wynajm nie bêdzie ju¿ pobierana., OK, )
		return 1
	)
	if(!strcmp(type, wejdz, true))
	(
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
		if(GroupData(group_id_fix)(gType) != GROUP_HOTEL)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		room
		if(sscanf(varchar, d, room))
		(
			hrp_Tip(playerid, /pokoj wejdz (Numer pokoju))
			return 1
		)
		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pHotel) == DoorData(doorid)(dUID))
				(
					if(PlayerCache(i)(pUID) == room)
					(
						val2 = GroupData(group_id_fix)(gValue2)

						hrp_SetPlayerPos(playerid, Interiors(val2)(INTERIOR_X), Interiors(val2)(INTERIOR_Y), Interiors(val2)(INTERIOR_Z))
						SetPlayerFacingAngle(playerid, Interiors(val2)(INTERIOR_A))

						SetPlayerInterior(playerid, Interiors(val2)(INTERIOR_ID))
						SetPlayerVirtualWorld(playerid, room)

						SetCameraBehindPlayer(playerid)

						GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~w~Aby wyjsc z pokoju uzyj komendy ~r~/pokoj wyjdz, 4000, 3)
						return 1
					)
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Drzwi od tego pokoju s¹ zamkniête., OK, )
		return 1
	)
	if(!strcmp(type, wyjdz, true))
	(
		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pHotel))
				(
		  			if(PlayerCache(i)(pUID) == GetPlayerVirtualWorld(playerid))
		  			(
				  		hotel = GetDoorID(PlayerCache(i)(pHotel)),
							group_id_fix = GetGroupID(DoorData(hotel)(dOwner))

						if(GroupData(group_id_fix)(gType) != GROUP_HOTEL)
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w pokoju hotelowym., OK, )
							return 1
						)
						hrp_SetPlayerPos(playerid, DoorData(hotel)(dExitX), DoorData(hotel)(dExitY), DoorData(hotel)(dExitZ))
						SetPlayerFacingAngle(playerid, DoorData(hotel)(dExitAng))

						SetPlayerInterior(playerid, DoorData(hotel)(dExitInt))
						SetPlayerVirtualWorld(playerid, DoorData(hotel)(dExitVW))

						TogglePlayerControllable(playerid, false)
						PlayerCache(playerid)(pDoorFreeze) = 3
						return 1
		  			)
				)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Drzwi od tego pokoju s¹ zamkniête., OK, )
		return 1
	)
	/*
	if(!strcmp(type, koszt, true))
	(
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
		if(GroupData(group_id_fix)(gType) != GROUP_HOTEL)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w hotelu., OK, )
			return 1
		)
		if(IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
		(
  			format(string, sizeof(string), WprowadŸ kwotê, jak¹ chcesz pobieraæ za wynajem pokoju.\nObecny koszt wynajmu pokoju wynosi $%d.\n\nOp³ata za pokój pobierana jest raz dziennie, razem z wydaniem wyp³at., GroupData(group_id_fix)(gValue1))
			ShowPlayerDialog(playerid, D_CHANGE_ROOM_PRICE, DIALOG_STYLE_INPUT, Zmieñ koszt wynajmu, string, Zmieñ, Anuluj)
		)
		else
		(
  			format(string, sizeof(string), Koszt wynajmu pokoju wynosi $%d.\nOp³ata za pokój pobierana jest raz dziennie, razem z wydaniem wyp³at., GroupData(group_id_fix)(gValue1))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		)
		return 1
	)
	*/
	return 1
)

CMD:hotel(playerid, params()) return cmd_pokoj(playerid, params)
CMD:motel(playerid, params()) return cmd_pokoj(playerid, params)

CMD:pozycja(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /pozycja (spawn | hotel | aj))
		return 1
	)
	if(!strcmp(type, spawn, true))
	(
		GetPlayerPos(playerid, SettingData(MainSpawnPos)(0), SettingData(MainSpawnPos)(1), SettingData(MainSpawnPos)(2))
		GetPlayerFacingAngle(playerid, SettingData(MainSpawnPos)(3))

		SettingData(MainSpawnInt) = GetPlayerInterior(playerid)
		SettingData(MainSpawnVW) = GetPlayerVirtualWorld(playerid)

		mysql_query_format(UPDATE hrp_settings SET setting_mainspawnx = %f, setting_mainspawny = %f, setting_mainspawnz = %f, setting_mainspawna = %f, setting_mainspawnint = %d, setting_mainspawnvw = %d LIMIT 1, SettingData(MainSpawnPos)(0), SettingData(MainSpawnPos)(1), SettingData(MainSpawnPos)(2), SettingData(MainSpawnPos)(3), SettingData(MainSpawnInt), SettingData(MainSpawnVW))

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Pozycja g³ównego spawnu zosta³a pomyœlnie zmieniona.\nPozycja zosta³a zapisana w bazie danych., OK, )
		return 1
	)
	if(!strcmp(type, hotel, true))
	(
 		GetPlayerPos(playerid, SettingData(HotelPos)(0), SettingData(HotelPos)(1), SettingData(HotelPos)(2))
		GetPlayerFacingAngle(playerid, SettingData(MainSpawnPos)(3))

		SettingData(HotelInt) = GetPlayerInterior(playerid)

		mysql_query_format(UPDATE hrp_settings SET setting_hotelspawnx = %f, setting_hotelspawny = %f, setting_hotelspawnz = %f, setting_hotelspawna = %f, setting_hotelspawnint = %d LIMIT 1, SettingData(HotelPos)(0), SettingData(HotelPos)(1), SettingData(HotelPos)(2), SettingData(HotelPos)(3), SettingData(HotelInt))

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Pozycja pokoju hotelowego zosta³a pomyœlnie zmieniona.\nPozycja zosta³a zapisana w bazie danych., OK, )
		return 1
	)
	return 1
)

CMD:zakuj(playerid, params())
(
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /zakuj (ID gracza))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zakuæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(!PlayerHaveItem(playerid, ITEM_HANDCUFFS))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiedniego przedmiotu w swoim ekwipunku., OK, )
		return 1
	)

	PlayerCache(giveplayer_id)(pCuffedStill) = playerid
	SetPlayerSpecialAction(giveplayer_id, SPECIAL_ACTION_CUFFED)

	ApplyAnimation(giveplayer_id, CRACK, crckdeth3, 4.1, 0, 0, 0, 1, 0, 1)
	hrp_TogglePlayerControllable(giveplayer_id, 0)
	ApplyAnimation(giveplayer_id, CRACK, crckdeth3, 4.1, 0, 0, 0, 1, 0, 1)

	format(string, sizeof(string), Zaku³eœ gracza %s, aby rozkuæ, u¿yj komendy /rozkuj., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:skuj(playerid, params())
(
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /skuj (ID gracza))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skuæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(!PlayerHaveItem(playerid, ITEM_HANDCUFFS))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiedniego przedmiotu w swoim ekwipunku., OK, )
		return 1
	)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pCuffed) == playerid)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skuæ wiêcej osób., OK, )
				return 1
			)
		)
	)
	PlayerCache(giveplayer_id)(pCuffed) = playerid
	SetPlayerSpecialAction(giveplayer_id, SPECIAL_ACTION_CUFFED)

	format(string, sizeof(string), Sku³eœ gracza %s, aby rozkuæ, u¿yj komendy /rozkuj., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:rozkuj(playerid, params())
(
	giveplayer_id, string(64)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /rozkuj (ID gracza))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skuæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(PlayerCache(giveplayer_id)(pCuffed) != playerid && PlayerCache(giveplayer_id)(pCuffedStill) != playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyt¹pi³ b³¹d, Ten gracz nie jest skuty przez Ciebie., OK, )
		return 1
	)
	PlayerCache(giveplayer_id)(pCuffed) = INVALID_PLAYER_ID
	PlayerCache(giveplayer_id)(pCuffedStill) = INVALID_PLAYER_ID
	SetPlayerSpecialAction(giveplayer_id, SPECIAL_ACTION_NONE)

	hrp_TogglePlayerControllable(giveplayer_id, 1)

	format(string, sizeof(string), Gracz %s zosta³ rozkuty., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:lspd(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FBI)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(IsPlayerInAnyVehicle(playerid))
	(
		vehid = GetPlayerVehicleID(playerid)
		if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
			return 1
		)
	)
	else
	(
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
			return 1
		)
	)
	PlayerCache(playerid)(pPDMenu) = PDM_START
	PD_Show(playerid)
	SelectTextDraw(playerid, 0xFFFF66FF)
	return 1
)

CMD:kartoteka(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FBI)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /kartoteka (ID gracza))
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
	if(IsPlayerInAnyVehicle(playerid))
	(
		vehid = GetPlayerVehicleID(playerid)
		if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
			return 1
		)
	)
	else
	(
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
			return 1
		)
	)
	ShowPlayerDirectoryForPlayer(playerid, giveplayer_id)
	return 1
)

CMD:kartotekauid(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FBI)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(strval(params) )= 0 && strval(params) ( 65565)
	(
		ShowPlayerUidDirectoryForPlayer(playerid, strval(params))
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wyst¹pi³ niespodziewany b³¹d. Komputer nie odnalaz³ ¿adnych wyników., OK, )
	)
	return 1
)

CMD:przeszukaj(playerid, params())
(
	if(!IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI) && !IsPlayerInGroupType(playerid, GROUP_ARMY) && !IsPlayerInGroupType(playerid, GROUP_CRIMINAL) && !IsPlayerInGroupType(playerid, GROUP_MAFIA) && PlayerCache(playerid)(pAdmin) == 0 && !IsPlayerInGroupType(playerid, GROUP_SECURITY) && !IsPlayerInGroupType(playerid, GROUP_DOC) && !IsPlayerInGroupType(playerid, GROUP_HARDCORE))
	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
  		return 1
  	)
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		if(!IsPlayerInAnyVehicle(playerid))
		(
			doorid = GetPlayerDoorID(playerid)
			if(doorid != INVALID_DOOR_ID)
			(
				data(128), list_items(512),
					item_uid, item_name(32)

				mysql_query_format(SELECT item_uid, item_name FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_SAFE, DoorData(doorid)(dUID))

				mysql_store_result()
				while(mysql_fetch_row(data, |))
				(
					sscanf(data, p(|)ds(32), item_uid, item_name)
					format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, item_uid, item_name)
				)
				mysql_free_result()
				if(strlen(list_items))
				(
					format(data, sizeof(data), %s (SampID: %d, UID: %d) » Schowek, DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, data, list_items, OK, Anuluj)
					return 1
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych przedmiotów w schowku., OK, )
					return 1
				)
			)
			else
			(
				hrp_Tip(playerid, /przeszukaj (ID gracza))
			)
		)
		else
		(
			vehid = GetPlayerVehicleID(playerid)
			ListVehicleItemsForPlayer(playerid, vehid)
		)
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz przeszukiwaæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(PlayerCache(playerid)(pSearches) != INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie przeszukujesz ju¿ jakiegoœ gracza, odczekaj chwilê., OK, )
		return 1
	)
	PlayerCache(playerid)(pSearches) = giveplayer_id
	PlayerCache(playerid)(pSearchTime) = 15

	string(128)
	format(string, sizeof(string), Grasz %s rozpocz¹³ przeszukiwanie Twojego cia³a.\nPrzeszukiwanie dobiegnie koñca za kilka sekund., PlayerName(playerid))

	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przeszukiwanie gracza w toku.\nOdczekaj kilka sekund, a¿ przeszukiwanie dobiegnie koñca., OK, )
	ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:blokuj(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	vehid = GetClosestVehicle(playerid), string(256)
  	if(vehid == INVALID_VEHICLE_ID)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnego pojazdu w pobli¿u., OK, )
  		return 1
  	)
  	MainPlayerTable(playerid) = vehid

  	format(string, sizeof(string), WprowadŸ cenê zdjêcia blokady dla pojazdu %s (SampID: %d, UID: %d).\nW³aœciciel pojazdu bêdzie musia³ zg³osiæ siê na komisariat, by zdj¹æ blokadê za podan¹ kwotê pieniêdzy., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
  	ShowPlayerDialog(playerid, D_BLOCK_WHEEL, DIALOG_STYLE_INPUT, Blokada ko³a, string, Blokuj, Anuluj)
	return 1
)

CMD:blokada(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /blokada (id | sprawdz))
		return 1
	)
	if(!strcmp(type, id, true))
	(
		blockade_id
		if(sscanf(varchar, d, blockade_id))
		(
			hrp_Tip(playerid, /blokada id (ID blokady(1, 2, 3, ...)))
			return 1
		)
		if(blockade_id (= 0 || blockade_id ) 10)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID blokady., OK, )
			return 1
		)
		if(IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania blokady., OK, )
			return 1
		)

		if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
		(
			blockade_id -= 1
		)
		else if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
		(
			blockade_id = (blockade_id + 10) - 1
		)

		if(IsValidDynamicObject(PoliceBlockade(blockade_id)) && PoliceBlockade(blockade_id) != INVALID_OBJECT_ID)
		(
			DestroyDynamicObject(PoliceBlockade(blockade_id))
			PoliceBlockade(blockade_id) = INVALID_OBJECT_ID
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~blokade, 3000, 3)
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ, Float:PosA

		GetPlayerPos(playerid, PosX, PosY, PosZ)
		GetPlayerFacingAngle(playerid, PosA)

		GetXYInFrontOfPlayer(playerid, PosX, PosY, 5.0)
		PoliceBlockade(blockade_id) = CreateDynamicObject(3578, PosX, PosY, PosZ - 0.5, 0.0, 0.0, PosA)

		Streamer_Update(playerid)

		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~blokade, 3000, 3)
		return 1
	)
	if(!strcmp(type, sprawdz, true))
	(
		string(128)
 		if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
		(
			for(blockade_id = 0 blockade_id ( 10 blockade_id++)
			(
				Float:Pos(3)
				GetDynamicObjectPos(PoliceBlockade(blockade_id), Pos(0), Pos(1), Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid, 5.0, Pos(0), Pos(1), Pos(2)))
				(
					format(string, sizeof(string), Blokada w poblizu to ID: %d, blockade_id+1)
					SendClientMessage(playerid, COLOR_GREY, string)
				)
			)
		)
		else if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
		(
			for(blockade_id = 10 blockade_id ( 20 blockade_id++)
			(
				Float:Pos(3)
				GetDynamicObjectPos(PoliceBlockade(blockade_id), Pos(0), Pos(1), Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid, 5.0, Pos(0), Pos(1), Pos(2)))
				(
					format(string, sizeof(string), Blokada w poblizu to ID: %d, blockade_id-9)
					SendClientMessage(playerid, COLOR_GREY, string)
				)
			)
		)
		return 1
	)
	return 1
)

CMD:pacholek(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /pacholek (id | sprawdz))
		return 1
	)
	if(!strcmp(type, id, true))
	(
		blockade_id
		if(sscanf(varchar, d, blockade_id))
		(
			hrp_Tip(playerid, /pacholek id (ID pacholka(1, 2, 3, ...)))
			return 1
		)
		if(blockade_id (= 0 || blockade_id ) 15)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID pacholka., OK, )
			return 1
		)
		if(IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania pacholka., OK, )
			return 1
		)

		if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
		(
			blockade_id -= 1
		)
		else if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
		(
			blockade_id = (blockade_id + 15) - 1
		)

		if(IsValidDynamicObject(PolicePole(blockade_id)) && PolicePole(blockade_id) != INVALID_OBJECT_ID)
		(
			DestroyDynamicObject(PolicePole(blockade_id))
			PolicePole(blockade_id) = INVALID_OBJECT_ID
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~pacholek, 3000, 3)
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ, Float:PosA

		GetPlayerPos(playerid, PosX, PosY, PosZ)
		GetPlayerFacingAngle(playerid, PosA)

		GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
		PolicePole(blockade_id) = CreateDynamicObject(OBJECT_POLICE_POLE, PosX, PosY, PosZ - 0.69, 0.0, 0.0, PosA)

		Streamer_Update(playerid)

		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~pacholek, 3000, 3)
		return 1
	)
	if(!strcmp(type, sprawdz, true))
	(
		string(128)
 		if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
		(
			for(blockade_id = 0 blockade_id ( 15 blockade_id++)
			(
				Float:Pos(3)
				GetDynamicObjectPos(PolicePole(blockade_id), Pos(0), Pos(1), Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid, 5.0, Pos(0), Pos(1), Pos(2)))
				(
					format(string, sizeof(string), Pacholek w poblizu to ID: %d, blockade_id+1)
					SendClientMessage(playerid, COLOR_GREY, string)
				)
			)
		)
		else if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
		(
			for(blockade_id = 16 blockade_id ( 30 blockade_id++)
			(
				Float:Pos(3)
				GetDynamicObjectPos(PolicePole(blockade_id), Pos(0), Pos(1), Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid, 5.0, Pos(0), Pos(1), Pos(2)))
				(
					format(string, sizeof(string), Pacholek w poblizu to ID: %d, blockade_id-15)
					SendClientMessage(playerid, COLOR_GREY, string)
				)
			)
		)
		return 1
	)
	return 1
)

CMD:objazd(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /objazd (ID objazd(1, 2, 3, 4, 5)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 5)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID objazdu., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania objazdów., OK, )
  		return 1
  	)

  	if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
  	(
  		blockade_id -= 1
	)
	else if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
	(
  		blockade_id = (blockade_id + 5) - 1
	)

  	if(IsValidDynamicObject(PoliceDetour(blockade_id)) && PoliceDetour(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(PoliceDetour(blockade_id))
		PoliceDetour(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~znak objazdu, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	PoliceDetour(blockade_id) = CreateDynamicObject(OBJECT_POLICE_DETOUR, PosX, PosY, PosZ - 0.69, 0.0, 0.0, PosA)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~znak objazdu, 3000, 3)
	return 1
)

CMD:skokochron(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) !=  GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
		hrp_Tip(playerid, /skokochron (ID skokochronu(1, 2, 3, 4, 5)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 5)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID skokochronu., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania skokochronu., OK, )
  		return 1
  	)

  	if(IsValidDynamicObject(PoliceJump(blockade_id)) && PoliceJump(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(PoliceJump(blockade_id))
		PoliceJump(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~skokochron, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	PoliceJump(blockade_id) = CreateDynamicObject(OBJECT_POLICE_JUMP, PosX - 2.8504, PosY, PosZ - 0.69, 0.0, 0.0, PosA + 450)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~skokochron, 3000, 3)
	return 1
)

CMD:drabina(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) !=  GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
		hrp_Tip(playerid, /drabina (ID drabiny(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 10)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID drabiny., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania drabiny., OK, )
  		return 1
  	)

  	if(IsValidDynamicObject(PoliceLadder(blockade_id)) && PoliceLadder(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(PoliceLadder(blockade_id))
		PoliceLadder(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~drabine, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	PoliceLadder(blockade_id) = CreateDynamicObject(OBJECT_POLICE_LADDER, PosX, PosY, PosZ - 0.69, 0.0, 0.0, PosA)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~drabine, 3000, 3)
	return 1
)

CMD:flara(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT && GroupData(group_id_fix)(gType) != GROUP_ARMY)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /flara (ID flary(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 10)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID flary., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania flary., OK, )
  		return 1
  	)

  	if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
  	(
  		blockade_id -= 1
	)
	else if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
	(
  		blockade_id = (blockade_id + 10) - 1
	)

  	if(IsValidDynamicObject(PoliceFlare(blockade_id)) && PoliceFlare(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(PoliceFlare(blockade_id))
		PoliceFlare(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~flare, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	PoliceFlare(blockade_id) = CreateDynamicObject(OBJECT_POLICE_FLARE, PosX, PosY, PosZ - 3.00, 0.0, 0.0, PosA, -1, -1, -1, 300.0)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~flare, 3000, 3)
	return 1
)

CMD:kolczatka(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /kolczatka (ID kolczatki(1, 2, 3, 4, 5)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 5)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID kolczatki., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania kolczatki., OK, )
  		return 1
  	)

	blockade_id -= 1

  	if(IsValidDynamicObject(PoliceSpikes(blockade_id)) && PoliceSpikes(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(PoliceSpikes(blockade_id))
		PoliceSpikes(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~kolczatke, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 5.0)
	PoliceSpikes(blockade_id) = CreateDynamicObject(2899, PosX, PosY, PosZ - 0.9, 0.0, 0.0, PosA)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~kolczatke, 3000, 3)
	return 1
)

CMD:trucktasma(playerid,params())
(
	/*
		blokady dla truckerów
	*/
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_TRUCKERS)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /trucktasma (ID tasmy(1-20)))
  		return 1
  	)

	if(blockade_id (= 0 || blockade_id ) 20)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID taœmy., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania taœmy., OK, )
  		return 1
  	)

	blockade_id -= 1
	if(IsValidDynamicObject(TruckLine(blockade_id)) && TruckLine(blockade_id) != INVALID_OBJECT_ID)
	(
		DestroyDynamicObject(TruckLine(blockade_id))
		TruckLine(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~tasme, 3000, 3)
  		return 1
	)

	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	TruckLine(blockade_id) = CreateDynamicObject(OBJECT_POLICE_LINE, PosX, PosY, PosZ - 0.17, 0.0, 0.0, PosA, -1, -1, -1, 300.0)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~tasme, 3000, 3)

	return 1
)

CMD:dseblokada(playerid,params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_MEDICAL)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)

	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /dseblokada (ID blokady(1-10)))
  		return 1
  	)

	if(blockade_id (= 0 || blockade_id ) 10)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID blokady., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania blokady., OK, )
  		return 1
  	)

	blockade_id -= 1

	if(IsValidDynamicObject(DSEBlockade(blockade_id)) && DSEBlockade(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(DSEBlockade(blockade_id))
		DSEBlockade(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~blokade, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	DSEBlockade(blockade_id) = CreateDynamicObject(3578, PosX, PosY, PosZ - 0.5, 0.0, 0.0, PosA)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~blokade, 3000, 3)

	return 1
)

CMD:pdtasma(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /pdtasma (ID tasmy(1-20)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 20)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID taœmy., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania taœmy., OK, )
  		return 1
  	)

	blockade_id -= 1

  	if(IsValidDynamicObject(PoliceLine(blockade_id)) && PoliceLine(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(PoliceLine(blockade_id))
		PoliceLine(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~tasme, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	PoliceLine(blockade_id) = CreateDynamicObject(OBJECT_POLICE_LINE, PosX, PosY, PosZ - 0.17, 0.0, 0.0, PosA, -1, -1, -1, 300.0)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~tasme, 3000, 3)
	return 1
)

CMD:fbitasma(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_FBI)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /fbitasma (ID tasmy(1-20)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 20)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID taœmy., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania taœmy., OK, )
  		return 1
  	)

	blockade_id -= 1

  	if(IsValidDynamicObject(FBIBlockade(blockade_id)) && FBIBlockade(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(FBIBlockade(blockade_id))
		FBIBlockade(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~tasme, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	FBIBlockade(blockade_id) = CreateDynamicObject(OBJECT_POLICE_LINE, PosX, PosY, PosZ - 0.17, 0.0, 0.0, PosA, -1, -1, -1, 300.0)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~tasme, 3000, 3)
	return 1
)

CMD:ludzie(playerid, params())
(
	string(256)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerToPlayer(15.0, playerid, i))
			(
				format(string, sizeof(string), ** %s: %s. **, PlayerName(i), PlayerCache(i)(pDescTagText))
				SendClientMessage(playerid, COLOR_DO, string)
			)
		)
	)
	return 1	
)

CMD:fire(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /fire (ID wraku(1-5)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 5)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID p³omienia., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania p³omienia., OK, )
  		return 1
  	)

	blockade_id -= 1

  	if(IsValidDynamicObject(FDFire(blockade_id)) && FDFire(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(FDFire(blockade_id))
		FDFire(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~plomien, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	FDFire(blockade_id) = CreateDynamicObject(18688+random(3), PosX, PosY, PosZ - 1.80, 0.0, 0.0, PosA, -1, -1, -1, 300.0)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~plomien, 3000, 3)
	return 1
)

CMD:wrak(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /wrak (ID wraku(1-5)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 5)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID wraku., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania wraku., OK, )
  		return 1
  	)

	blockade_id -= 1

  	if(IsValidDynamicObject(FDWreck(blockade_id)) && FDWreck(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(FDWreck(blockade_id))
		FDWreck(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~wrak, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	FDWreck(blockade_id) = CreateDynamicObject(15221, PosX, PosY, PosZ - 0.17, 0.0, 0.0, PosA, -1, -1, -1, 300.0)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~wrak, 3000, 3)
	return 1
)

CMD:fdtasma(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /fdtasma (ID fdtasmy(1-20)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 20)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID taœmy., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania taœmy., OK, )
  		return 1
  	)

	blockade_id -= 1

  	if(IsValidDynamicObject(PoliceFireLine(blockade_id)) && PoliceFireLine(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(PoliceFireLine(blockade_id))
		PoliceFireLine(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~tasme, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	PoliceFireLine(blockade_id) = CreateDynamicObject(OBJECT_POLICE_FIRELINE, PosX, PosY, PosZ - 0.17, 0.0, 0.0, PosA, -1, -1, -1, 300.0)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~tasme, 3000, 3)
	return 1
)

CMD:hesco(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_ARMY)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	blockade_id
  	if(sscanf(params, d, blockade_id))
  	(
  		hrp_Tip(playerid, /hesco (ID blokady(1-10)))
  		return 1
  	)
  	if(blockade_id (= 0 || blockade_id ) 10)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID blokady., OK, )
  		return 1
  	)
  	if(IsPlayerInAnyVehicle(playerid))
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania blokady., OK, )
  		return 1
  	)

	blockade_id -= 1

  	if(IsValidDynamicObject(PoliceHesco(blockade_id)) && PoliceHesco(blockade_id) != INVALID_OBJECT_ID)
  	(
  		DestroyDynamicObject(PoliceHesco(blockade_id))
		PoliceHesco(blockade_id) = INVALID_OBJECT_ID
  		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~blokade, 3000, 3)
  		return 1
  	)
  	Float:PosX, Float:PosY, Float:PosZ, Float:PosA

  	GetPlayerPos(playerid, PosX, PosY, PosZ)
  	GetPlayerFacingAngle(playerid, PosA)

  	GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
	PoliceHesco(blockade_id) = CreateDynamicObject(OBJECT_POLICE_HESCO, PosX, PosY, PosZ - 1.04, 0.0, 0.0, PosA, -1, -1, -1, 300.0)

	Streamer_Update(playerid)

	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~blokade, 3000, 3)
	return 1
)

CMD:tasma(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /tasma (id | sprawdz))
		return 1
	)
	if(!strcmp(type, id, true))
	(
		blockade_id
		if(sscanf(varchar, d, blockade_id))
		(
			hrp_Tip(playerid, /tasma id (ID tasmy(1, 2, 3, ...)))
			return 1
		)
		if(blockade_id (= 0 || blockade_id ) 20)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nieprawid³owe ID tasmy., OK, )
			return 1
		)
		if(IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siedzieæ w pojeŸdzie podczas stawiania tasmy., OK, )
			return 1
		)

		if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
		(
			blockade_id -= 1
		)
		else if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
		(
			blockade_id = (blockade_id + 20) - 1
		)

		if(IsValidDynamicObject(PoliceCaution(blockade_id)) && PoliceCaution(blockade_id) != INVALID_OBJECT_ID)
		(
			DestroyDynamicObject(PoliceCaution(blockade_id))
			PoliceCaution(blockade_id) = INVALID_OBJECT_ID
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Usunieto ~y~tasme, 3000, 3)
			return 1
		)
		Float:PosX, Float:PosY, Float:PosZ, Float:PosA

		GetPlayerPos(playerid, PosX, PosY, PosZ)
		GetPlayerFacingAngle(playerid, PosA)

		GetXYInFrontOfPlayer(playerid, PosX, PosY, 1.0)
		PoliceCaution(blockade_id) = CreateDynamicObject(OBJECT_POLICE_CAUTION, PosX, PosY, PosZ - 0.17, 0.0, 0.0, PosA, -1, -1, -1, 300.0)

		Streamer_Update(playerid)

		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~g~Postawiono ~y~tasme, 3000, 3)
		return 1
	)
	if(!strcmp(type, sprawdz, true))
	(
		string(128)
 		if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
		(
			for(blockade_id = 0 blockade_id ( 20 blockade_id++)
			(
				Float:Pos(3)
				GetDynamicObjectPos(PoliceCaution(blockade_id), Pos(0), Pos(1), Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid, 5.0, Pos(0), Pos(1), Pos(2)))
				(
					format(string, sizeof(string), Tasma w poblizu to ID: %d, blockade_id+1)
					SendClientMessage(playerid, COLOR_GREY, string)
				)
			)
		)
		else if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
		(
			for(blockade_id = 20 blockade_id ( 40 blockade_id++)
			(
				Float:Pos(3)
				GetDynamicObjectPos(PoliceCaution(blockade_id), Pos(0), Pos(1), Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid, 5.0, Pos(0), Pos(1), Pos(2)))
				(
					format(string, sizeof(string), Tasma w poblizu to ID: %d, blockade_id-19)
					SendClientMessage(playerid, COLOR_GREY, string)
				)
			)
		)
		return 1
	)
	return 1
)

CMD:rejestracja(playerid, params())
(
	string(64)
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FBI)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	vehid = GetClosestVehicle(playerid)
	if(!CarInfo(vehid)(cRegister))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Pojazd ten nie zosta³ zarejestrowany w urzêdzie miasta., OK, )
		return 1
	)
	format(string, sizeof(string), Rejestracja: ** LS%d **, CarInfo(vehid)(cUID))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Rejestracja pojazdu, string, OK, )
	return 1
)

CMD:zabierz(playerid, params())
(
	type(32), varchar(32), string(128)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /zabierz (dowod | prawko | przedmiot))
		return 1
	)
	if(!strcmp(type, przedmiot, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
			return 1
		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_POLICE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id, item_uid
		if(sscanf(varchar, ud, giveplayer_id, item_uid))
		(
			hrp_Tip(playerid, /zabierz przedmiot (ID gracza) (UID przedmiotu))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
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
		if(ItemInfo(itemid)(iWeight) ) GetPlayerEqSpace(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie masz wystarczaj¹co miejsca w swoim ekwipunku aby zabraæ ten przedmiot., OK, )
			return 1
		)
		ItemInfo(itemid)(iOwner) = PlayerCache(playerid)(pUID)
		mysql_query_format(UPDATE hrp_items SET item_owner = %d WHERE item_uid = %d LIMIT 1, PlayerCache(playerid)(pUID), ItemInfo(itemid)(iUID))

		format(string, sizeof(string), Zabra³eœ przedmiot %s (SampID: %d, UID: %d) graczu %s.\nPrzedmiot pojawi³ siê w Twoim ekwipunku., ItemInfo(itemid)(iName), itemid, ItemInfo(itemid)(iUID), PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Gracz %s zabra³ Ci przedmiot %s (SampID: %d, UID: %d)., PlayerName(playerid), ItemInfo(itemid)(iName), itemid, ItemInfo(itemid)(iUID))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, prawko, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
			return 1
		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_POLICE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
 		giveplayer_id
		if(sscanf(varchar, ud, giveplayer_id))
		(
			hrp_Tip(playerid, /zabierz prawko (ID gracza))
			return 1
		)
 		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zabraæ dokumentu sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		if(!(PlayerCache(giveplayer_id)(pDocuments) & DOC_DRIVER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie posiada prawa jazdy., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pPDP) ( 21)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi mieæ przyznanych conajmniej 21 pkt karnych., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pDocuments) -= DOC_DRIVER
		PlayerCache(giveplayer_id)(pPDP) = 0

		format(string, sizeof(string), Zabra³eœ prawo jazdy gracza %s., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Gracz %s zabra³ Ci prawo jazdy., PlayerName(playerid))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	return 1
)

CMD:reanimuj(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_MEDICAL && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /reanimuj (ID gracza))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz reanimowaæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
		return 1
	)
	if(!PlayerCache(giveplayer_id)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie ma BW., OK, )
		return 1
	)
	PlayerCache(giveplayer_id)(pBW) = 0

	ApplyAnimation(giveplayer_id, Attractors, Stepsit_out, 4.0, 0, 0, 0, 0, 0, 1)
	hrp_TogglePlayerControllable(giveplayer_id, 1)

	SetCameraBehindPlayer(giveplayer_id)
	hrp_SetPlayerHealth(giveplayer_id, 20)
	return 1
)

CMD:reklama(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_NEWS)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(24), varchar(256)
	if(sscanf(params, s(24)S()(256), type, varchar))
	(
 		hrp_Tip(playerid, /reklama (transmituj | anuluj))
   		return 1
	)
	string(256), radioslot = GetRadioSlot(group_id_fix)
	if(!strcmp(type, transmituj, true))
	(
		time, text(128)
		if(sscanf(varchar, ds(128), time, text))
		(
			hrp_Tip(playerid, /reklama transmituj (Czas (min)) (Treœæ))
			return 1
		)
   		if(time (= 0 || time ) 5)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Reklama nie mo¿e byæ wyœwietalana d³u¿ej ni¿ 5 minut, a tak¿e mniej ni¿ 0., OK, )
  			return 1
		)
		if(RadioData(radioslot)(AdvertTime))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie jest ju¿ nadawana jakaœ reklama, u¿yj /reklama anuluj., OK, )
			return 1
		)
		
		
		if(RadioData(radioslot)(IsUsingRadio))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie w radiu jest coœ nadawane., OK, )
			return 1
		)
		if(IsPlayerInAnyVehicle(playerid))
		(
			vehid = GetPlayerVehicleID(playerid)
			if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pGroupDuty))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
				return 1
			)
		)
		else
		(
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
				return 1
			)
			if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
				return 1
			)
		)
		EscapePL(text)
		
		format(string, sizeof(string), %s ~)~ ~g~~h~Reklama: ~w~%s, GroupData(group_id_fix)(gTag), FormatTextDrawColors(text))
		TextDrawSetString(Text:TextDrawRadio(radioslot), string)

		streams = 0
		for(i = 1 i ( sizeof(RadioData) i++)
		(
			if(RadioData(i)(IsUsingRadio))
			(
				streams++
			)
		)
		if(streams == 0)
		(
			for(i = 0 i ( MAX_PLAYERS i++)
			(
				playerslot = PlayerCache(i)(pStation)
				TextDrawHideForPlayer(i, Text:TextDrawRadio(playerslot))
				TextDrawHideForPlayer(i, Text:TextDrawSanNews)
				TextDrawShowForPlayer(i, Text:TextDrawRadio(radioslot))
				PlayerCache(i)(pStation) = radioslot
			)
		)
		
		RadioData(radioslot)(AdvertTime) = time
		RadioData(radioslot)(IsUsingRadio) = true
		return 1
	)
	if(!strcmp(type, anuluj, true))
	(
		if(RadioData(radioslot)(AdvertTime) == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, ¯adna reklama nie jest obecnie nadawana w radiu., OK, )
			return 1
		)
		if(IsPlayerInAnyVehicle(playerid))
		(
			vehid = GetPlayerVehicleID(playerid)
			if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pGroupDuty))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
				return 1
			)
		)
		else
		(
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
				return 1
			)
			if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie lub budynku nale¿¹cym do grupy., OK, )
				return 1
			)
		)
		format(string, sizeof(string), %s ~)~ W radiu leci standardowy blok muzyczny., GroupData(group_id_fix)(gTag))
		TextDrawSetString(Text:TextDrawRadio(radioslot), string)

		RadioData(radioslot)(AdvertTime) = 0
		RadioData(radioslot)(IsUsingRadio) = false
		return 1
	)
	return 1
)

CMD:live(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_NEWS)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(24), varchar(24), radioslot = GetRadioSlot(group_id_fix), string(256)
	if(sscanf(params, s(24)S()(24), type, varchar))
	(
		hrp_Tip(playerid, /live (rozpocznij | zakoncz))
		return 1
	)
	if(!strcmp(type, rozpocznij, true))
	(
		if(PlayerCache(playerid)(pLive))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie prowadzisz ju¿ jak¹œ transmisjê na ¿ywo., OK, )
			return 1
		)

		PlayerCache(playerid)(pLive) = 1
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Transmisja na ¿ywo zosta³a rozpoczêta.\nU¿ywaj g³ównego czatu w celu nadawania w radiu., OK, )

		if(!RadioData(radioslot)(IsUsingRadio))
		(
			format(string, sizeof(string), %s ~)~ Aktualnie prowadzona jest transmisja na zywo., GroupData(group_id_fix)(gTag))
			TextDrawSetString(Text:TextDrawRadio(radioslot), string)
			/*foreach(Player, i)
			(
				Float:PosX, Float:PosY, Float:PosZ
				GetPlayerPos(i, PosX, PosY, PosZ)
				audio = Audio_Play(i, AUDIO_WN_START)
				Audio_Set3DPosition(i, audio, PosX, PosY, PosZ, 10.0)
			)*/
		)
		
		streams = 0
		for(i = 1 i ( sizeof(RadioData) i++)
		(
			if(RadioData(i)(IsUsingRadio))
			(
				streams++
			)
		)
		if(streams == 0)
		(
			for(i = 0 i ( MAX_PLAYERS i++)
			(
				playerslot = PlayerCache(i)(pStation)
				TextDrawHideForPlayer(i, Text:TextDrawRadio(playerslot))
				TextDrawHideForPlayer(i, Text:TextDrawSanNews)
				TextDrawShowForPlayer(i, Text:TextDrawRadio(radioslot))
				PlayerCache(i)(pStation) = radioslot
			)
		)
		
		RadioData(radioslot)(IsUsingRadio) = true

		return 1
	)
	if(!strcmp(type, zakoncz, true))
	(
		if(!PlayerCache(playerid)(pLive))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie prowadzisz ¿adnej transmisji na ¿ywo., OK, )
			return 1
		)

		PlayerCache(playerid)(pLive) = 0
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Transmisja na ¿ywo zosta³a zakoñczona pomyœlnie., OK, )

		counter = 0
		foreach(Player, i)
		(
			if(PlayerCache(i)(pLive)) counter++
		)
		if(counter == 0)
		(
			format(string, sizeof(string), %s ~)~ W radiu leci standardowy blok muzyczny., GroupData(group_id_fix)(gTag))
			TextDrawSetString(Text:TextDrawRadio(radioslot), string)
			RadioData(radioslot)(IsUsingRadio) = false
		)
		return 1
	)
	return 1
)

CMD:wywiad(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_NEWS)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	type(32), varchar(32), radioslot = GetRadioSlot(group_id_fix), string(256)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /wywiad (rozpocznij | zakoncz))
		return 1
	)
	if(!strcmp(type, rozpocznij, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /wywiad rozpocznij (ID gracza))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz prowadziæ wywiadu ze sob¹., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		if(RadioData(radioslot)(IsUsingRadio))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie w radiu jest coœ nadawane., OK, )
			return 1
		)
		
		streams = 0
		for(i = 1 i ( sizeof(RadioData) i++)
		(
			if(RadioData(i)(IsUsingRadio))
			(
				streams++
			)
		)
		if(streams == 0)
		(
			for(i = 0 i ( MAX_PLAYERS i++)
			(
				playerslot = PlayerCache(playerid)(pStation)
				TextDrawHideForPlayer(i, Text:TextDrawRadio(playerslot))
				TextDrawHideForPlayer(i, Text:TextDrawSanNews)
				TextDrawShowForPlayer(i, Text:TextDrawRadio(radioslot))
				PlayerCache(i)(pStation) = radioslot
			)
		)
		
		RadioData(radioslot)(IsUsingRadio) = true

		PlayerCache(playerid)(pInterview) = giveplayer_id
		PlayerCache(giveplayer_id)(pInterview) = playerid
		PlayerCache(playerid)(pInterviewSlot) = radioslot
		PlayerCache(giveplayer_id)(pInterviewSlot) = radioslot

		format(string, sizeof(string), Roczpocz¹³eœ wywiad z %s.\nPos³uguj siê g³ównym czatem, aby nadawaæ na antenie., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), %s rozpocz¹³ z Tob¹ wywiad.\nPos³uguj siê g³ównym czatem, aby nadawaæ na antenie., PlayerName(playerid))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, zakoncz, true))
	(
		if(PlayerCache(playerid)(pInterview) == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie nie prowadzisz ¿adnego wywiadu., OK, )
			return 1
		)
		interviewer_id = PlayerCache(playerid)(pInterview)

		PlayerCache(playerid)(pInterview) = INVALID_PLAYER_ID
		PlayerCache(interviewer_id)(pInterview) = INVALID_PLAYER_ID
		PlayerCache(playerid)(pInterviewSlot) = 0
		PlayerCache(interviewer_id)(pInterviewSlot) = 0

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wywiad zosta³ zakoñczony., OK, )
		ShowPlayerDialog(interviewer_id, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wywiad zosta³ zakoñczony., OK, )

		format(string, sizeof(string), %s ~)~ Ostatni wywiad z %s przeprowadzil %s, dziekujemy!, GroupData(group_id_fix)(gTag), PlayerName(interviewer_id), PlayerName(playerid))
		TextDrawSetString(Text:TextDrawRadio(radioslot), string)

		RadioData(radioslot)(IsUsingRadio) = false
		return 1
	)
	return 1
)

CMD:opis(playerid, params())
(
	desc(128)
	if(sscanf(params, s(128), desc))
	(
		ShowPlayerDialog(playerid, D_DESC_OPTIONS, DIALOG_STYLE_LIST, System opisów, 1. Lista Twoich opisów\n2. Dodaj opis\n3. Poka¿ aktualny opis\n4. Usuñ aktualny opis, Wybierz, Zamknij)
		return 1
	)
	if(!strcmp(desc, usun, true))
	(
		format(PlayerCache(playerid)(pDescTagText), 128,  )
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Opis zosta³ pomyœlnie usuniêty., OK, )
		return 1
	)
	format(PlayerCache(playerid)(pDescTagText), 128, %s, DescWrap(desc))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Ustalono nowy opis:, DescWrap(desc), OK, )
	return 1
)

CMD:styl(playerid, params())
(
	string(256)

	format(string, sizeof(string), %s\nStyl normalny, string)
	format(string, sizeof(string), %s\nStyl bokserski, string)
	format(string, sizeof(string), %s\nStyl Kung Fu, string)
	format(string, sizeof(string), %s\nStyl Kickboxingu, string)
	format(string, sizeof(string), %s\nStyl uliczny, string)

	ShowPlayerDialog(playerid, D_PICK_STYLE, DIALOG_STYLE_LIST, Wybierz swój styl walki, string, OK, Anuluj)
	return 1
)

CMD:stop(playerid, params())
(
	OnPlayerGymTrainStopped(playerid)
)

CMD:trenuj(playerid, params())
(
	type(12)
	if(PlayerCache(playerid)(pWounded))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz trenowaæ w trakcie os³abienia organizmu., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pRage))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz trenowaæ pod wp³ywem narkotyków. U¿yj od¿ywek., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pDailyReps) ) MAX_DAILY_REPS)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Twoja postaæ jest zbyt zmêczona ¿eby pakowaæ tak d³ugi czas., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGymType) != TRAIN_NONE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz najpierw zakoñczyæ obecny trening., OK, )
		return 1
	)
	if(GetPlayerVirtualWorld(playerid) != 0)
	(
		if(!PlayerCache(playerid)(pTrainTime))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz wykupiæ pozwolenie na u¿ywanie obiektów u pracownika., OK, )
			return 1
		)
	)
	if(sscanf(params, s(12), type))
	(
		hrp_Tip(playerid, /trenuj (laweczka | hantle | worek | bieznia))
		return 1
	)
	if(!strcmp(type, laweczka, true))
	(
		object_id = GetClosestObject(playerid)
		if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_BENCH)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê przy ³awce wyciskanej., OK, )
			return 1
		)
		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pGymType) == TRAIN_BENCH_PRESS)
				(
					if(PlayerCache(i)(pGymObject) == object_id)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ktoœ aktualnie korzysta z tego obiektu., OK, )
						return 1
					)
				)
			)
		)
		PlayerCache(playerid)(pGymObject) = object_id
		ShowPlayerDialog(playerid, D_SELECT_WEIGHT_BENCH, DIALOG_STYLE_LIST, Wybierz ciê¿ar sztangi:, 40 kg\n60 kg\n80 kg\n100 kg\n120 kg\n140 kg\n160 kg\n180 kg\n200 kg\n220 kg, Wybierz, Anuluj)
		return 1
	)
	if(!strcmp(type, hantle, true))
	(
   		object_id = GetClosestObject(playerid)
		if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_BARBELL)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnej hantli w pobli¿u., OK, )
			return 1
		)
  		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pGymType) == TRAIN_BARBELL)
				(
					if(PlayerCache(i)(pGymObject) == object_id)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ktoœ aktualnie korzysta z tego obiektu., OK, )
						return 1
					)
				)
			)
		)
		PlayerCache(playerid)(pGymObject) = object_id
		ShowPlayerDialog(playerid, D_SELECT_WEIGHT_BARBELL, DIALOG_STYLE_LIST, Wybierz ciê¿ar sztangi:, 40 kg\n60 kg\n80 kg\n100 kg\n120 kg\n140 kg, Wybierz, Anuluj)
		return 1
	)
	if(!strcmp(type, worek, true))
	(
		object_id = GetClosestObject(playerid)
		if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_PUNCH_BAG)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnego worka w pobli¿u., OK, )
			return 1
		)
  		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pGymType) == TRAIN_PUNCH_BAG)
				(
					if(PlayerCache(i)(pGymObject) == object_id)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ktoœ aktualnie korzysta z tego obiektu., OK, )
						return 1
					)
				)
			)
		)

		string(256)
		format(string, sizeof(string), %s\nStyl bokserski, string)
		format(string, sizeof(string), %s\nStyl Kung Fu, string)
		format(string, sizeof(string), %s\nStyl uliczny, string)

		PlayerCache(playerid)(pGymObject) = object_id

		ShowPlayerDialog(playerid, D_SELECT_FIGHTING_STYLE, DIALOG_STYLE_LIST, Wybierz styl trenowanej walki, string, Wybierz, Anuluj)
		return 1
	)
	return 1
)

CMD:bank(playerid, params())
(
	doorid = GetPlayerDoorID(playerid)
	if(doorid == INVALID_DOOR_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w banku., OK, )
		return 1
	)
 	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
  	(
   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w banku., OK, )
   		return 1
   	)
   	group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
   	if(GroupData(group_id_fix)(gType) != GROUP_BANK)
   	(
   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w banku., OK, )
   		return 1
   	)
   	if(!PlayerCache(playerid)(pBankNumber))
   	(
		ShowPlayerDialog(playerid, D_CREATE_BANK_ACCOUNT, DIALOG_STYLE_MSGBOX, Informacja, Aby w pe³ni korzystaæ z funkcji banku musisz za³o¿yæ konto bankowe,\ndo którego bêdzie przypisany odpowiedni numer bankowy.\n\nNumer bankowy bêdzie wykorzystywany do wszystkich akcji zwi¹zanych z pieniêdzmi w banku.\nCzy chcesz za³o¿yæ konto bankowe?, Tak, Nie)
   	)
   	else
   	(
		PlayerCache(playerid)(pBankLastTransaction) = 0
   		ShowPlayerDialog(playerid, D_SELECT_BANK_OPTION, DIALOG_STYLE_LIST, Wybierz opcjê, 1. Stan konta\n2. Wyp³aæ gotówkê\n2. Wp³aæ gotówkê\n4. Lista moich kredytów\n5. Dokonaj przelewu, Wybierz, Anuluj)
   	)
	return 1
)

CMD:crime(playerid, params())
(
	suspect, crime
	if(sscanf(params, ud, suspect, crime))
	(
		hrp_Tip(playerid, /crime (suspect) (crime (3-22)))
		return 1
	)
	if(crime ( 3 || crime ) 22)
	(
		hrp_Tip(playerid, /crime (suspect) (crime (3-22)))
		return 1
	)
	foreach(Player, i)
	(
		PlayCrimeReportForPlayer(i, suspect, crime)
	)
	return 1
)

CMD:budka(playerid, params())
(
	object_id = GetClosestObject(playerid)
	if(object_id == INVALID_OBJECT_ID || (GetObjectModel(object_id) != OBJECT_TELEPHONE && GetObjectModel(object_id) != OBJECT_TELEPHONE_ALT))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê przy budce telefonicznej., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿ywaæ budki podczas stanu nieprzytomnoœci., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGymType) != TRAIN_NONE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz korzystaæ z budki podczas treningu., OK, )
		return 1
	)

	phoneid = GetPhoneNearPlayer(playerid, 5.0)
	if(phoneid == -1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê przy budce telefonicznej., OK, )
		return 1
	)

	cmd(8)
	if(sscanf(params, s(8), cmd))
	(
		foreach(Calls, callid)
		(
			if(Call(callid)(calledDevice) == DEVICE_BOX)
			(
				if(Call(callid)(calledNumber) == Phones(phoneid)(phoneNumber))
				(
					cmd_budka(playerid, odbierz)
					return 1
				)
			)
		)

		if(Phones(phoneid)(phoneBusy))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ktoœ u¿ywa tej budki. Poczekaj na swoj¹ kolej!, OK, )
			return 1
		)

		MainPlayerTable(playerid) = phoneid
		ShowPlayerDialog(playerid, D_BOOTH_NUMBER, DIALOG_STYLE_INPUT, Budka telefoniczna, WprowadŸ numer, na który chcesz zadzwoniæ., Zadzwoñ, Anuluj)
		return 1
	)

	if(!strcmp(cmd, odbierz, true))
	(
		// Odbieranie budki.
		foreach(Calls, callid)
		(
			if(Call(callid)(calledDevice) == DEVICE_BOX)
			(
				if(Call(callid)(calledNumber) == Phones(phoneid)(phoneNumber))
				(
					Call(callid)(called) = playerid
					Call(callid)(convo) = true

					PlayerCache(playerid)(pUsingBooth) = true
					PlayerCache(playerid)(pCall) = callid

					Phones(phoneid)(phoneBusy) = true

					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)

					SendClientMessage(playerid, COLOR_YELLOW, Odebrano telefon. Aby zakoñczyæ rozmowê u¿yj komendy /zakoncz.)
					SendClientMessage(Call(callid)(caller), COLOR_YELLOW, Odebrano telefon. Aby zakoñczyæ rozmowê u¿yj komendy /zakoncz.)
					break
				)
			)
		)
	)

	return 1
)

CMD:bankomat(playerid, params())
(
	bool:checkbug = false
	if(gettime() - LogTime(playerid) ) 60)
		checkbug= true
	
	if(!checkbug)
	(
		GuiMsg(playerid, Musisz chwilê odczekaæ nim u¿yjesz tej komendy., 0)
		return 1
	)
	
	object_id = GetClosestObject(playerid)
	if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_ATM)
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê przy bankomacie., OK, )
   		return 1
	)
	if(!PlayerCache(playerid)(pBankNumber))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby móc korzystaæ z bankomatu, musisz posiadaæ konto bankowe., OK, )
		return 1
	)
	ShowPlayerDialog(playerid, D_SELECT_BANK_OPTION, DIALOG_STYLE_LIST, Bankomat, 1. Stan konta\n2. Wyp³aæ gotówkê, Wybierz, Anuluj)
	return 1
)

CMD:pomoc(playerid, params())
(
	list_commands(256)

	strcat(list_commands, » Wprowadzenie\n, sizeof(list_commands))

	strcat(list_commands, » Komendy g³ówne\n, sizeof(list_commands))
	strcat(list_commands, » Pojazd\n, sizeof(list_commands))

	strcat(list_commands, » Przedmioty\n, sizeof(list_commands))
	strcat(list_commands, » Praca\n, sizeof(list_commands))

	if(IsPlayerInAnyGroup(playerid))
	(
		strcat(list_commands, » Grupy\n, sizeof(list_commands))
	)

	if(PlayerCache(playerid)(pAdmin) == 1)
	(
		strcat(list_commands, » Administracja\n, sizeof(list_commands))
	)
	if(PlayerCache(playerid)(pAdmin) == -1)
	(
		strcat(list_commands, » Support\n, sizeof(list_commands))
	)

 	strcat(list_commands, » Animacje, sizeof(list_commands))

	ShowPlayerDialog(playerid, D_HELP, DIALOG_STYLE_LIST, Pomoc ogólna, list_commands, Wybierz, Anuluj)
	return 1
)

CMD:help(playerid, params()) return cmd_pomoc(playerid, params)

CMD:id(playerid, params())
(
	nick(24), list_players(256)
	if(sscanf(params, s(24), nick))
	(
		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerToPlayer(10.0, playerid, i))
				(
					format(list_players, sizeof(list_players), %s\n%d\t%s, list_players, i, PlayerName(i))
				)
			)
		)
		if(strlen(list_players))
		(
			ShowPlayerDialog(playerid, D_LIST_PLAYERS, DIALOG_STYLE_LIST, Gracze znajduj¹cy siê w pobli¿u:, list_players, PW, Zamknij)
		)
		else
		(
			hrp_Tip(playerid, /id (Czêœæ nicku))
		)
		return 1
	)
	if(isNumeric(nick))
	(
		id = strval(nick)
		format(list_players, sizeof(list_players), %s\n%d\t%s, list_players, id, PlayerName(id))
	)
	else
	(
		if(strlen(nick) ( 3)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz podaæ przynajmniej 3 znaki., OK, )
			return 1
		)
		foreach(Player, i)
		(
			name(24)
			GetPlayerName(i, name, sizeof(name))
			if(strfind(name, nick, true) )= 0)
			(
				format(list_players, sizeof(list_players), %s\n%d\t%s, list_players, i, PlayerName(i))
			)
		)
	)

	if(strlen(list_players))
	(
		ShowPlayerDialog(playerid, D_LIST_PLAYERS, DIALOG_STYLE_LIST, Znaleziono graczy:, list_players, PW, Zamknij)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych graczy spe³niaj¹cych dane kryteria., OK, )
	)
	return 1
)

CMD:duty(playerid, params())
(
	duty_type(12), varchar(24), string(128)
	if(sscanf(params, s(12)S()(24), duty_type, varchar))
	(
		hrp_Tip(playerid, /duty (grupa | admin | support | nauczyciel))
		return 1
	)
	if(!strcmp(duty_type, grupa, true))
	(
		if(PlayerCache(playerid)(pFlood) ) 0 && strcmp(varchar, skip, true)) (
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿yæ tej komendy tak szybko., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pGroupDuty))
		(
  			group_id_fix = GetPlayerDutyGroupID(playerid)
			duty_time = (gettime() - PlayerCache(playerid)(pGroupDutyTime)) / 60

			PlayerCache(playerid)(pGroupDuty) = 0
			PlayerCache(playerid)(pGroupDutyTime) = 0

			PlayerCache(playerid)(pNickColor) = 0xFFFFFF88

  			format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
			Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)

			format(string, sizeof(string), » Zszed³eœ ze s³u¿by grupy %s (UID: %d). Czas trwania sesji: %d min., GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID), duty_time)
			SendClientMessage(playerid, GroupData(group_id_fix)(gColor), string)

			OnPlayerDutyStop(playerid)

			GroupData(group_id_fix)(gActivity) += duty_time
			SaveGroup(group_id_fix)

			LoadDutyTimes(playerid)
			
			// Wracamy do starego systemu.
			PayDay(playerid)
			
			PlayerCache(playerid)(pFlood) = 10
			return 1
		)
		group_slot
		if(sscanf(varchar, d, group_slot))
		(
			hrp_Tip(playerid, /duty grupa (Slot grupy))
			return 1
		)
		group_slot -= 1
		if(group_slot ( 0 || group_slot ) 5)
		(
			GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
			return 1
		)
		if(!PlayerGroup(playerid)(group_slot)(gUID))
		(
			GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
  			return 1
		)
		if(Offer(playerid)(oCustomerID) != INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿yæ tej komendy zaraz po wys³aniu oferty., OK, )
			return 1
		)
		group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
		door_id = GetDoorID(GetPlayerVirtualWorld(playerid))
		bool:check = false, bool:check2 = false, bool:check3 = false

		if(GroupData(group_id_fix)(gType) != GROUP_DOC && GroupData(group_id_fix)(gType) != GROUP_FARM && GroupData(group_id_fix)(gType) != GROUP_RADIO && GroupData(group_id_fix)(gType) != GROUP_GASSTATION && GroupData(group_id_fix)(gType) != GROUP_TAXI)
			check = true
		if(GroupData(group_id_fix)(gType) != GROUP_DRIVING && GroupData(group_id_fix)(gType) != GROUP_TRANSPORT && GroupData(group_id_fix)(gType) != GROUP_SECURITY && GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_MEDICAL && GroupData(group_id_fix)(gType) != GROUP_FBI)
			check2 = true
		if(GroupData(group_id_fix)(gType) != GROUP_AUTOSALE && GroupData(group_id_fix)(gType) != GROUP_TIMBER && GroupData(group_id_fix)(gType) != GROUP_CRIMINAL && GroupData(group_id_fix)(gType) != GROUP_RACERS)
			check3 = true

		if(check && check2 && check3 && GroupData(group_id_fix)(gType) != GROUP_CORONER && GroupData(group_id_fix)(gType) != GROUP_TRUCKERS && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT && GroupData(group_id_fix)(gType) != GROUP_NEWS && GroupData(group_id_fix)(gType) != GROUP_ARMY)
		(
			if(GetPlayerVirtualWorld(playerid) == 0)
			(
				check = false
				foreach(Booths, boothid)
				(
					if(IsPlayerInRangeOfPoint(playerid, BoothData(boothid)(bRadius), BoothData(boothid)(bPosX), BoothData(boothid)(bPosY), BoothData(boothid)(bPosZ)))
					(
						if(BoothData(boothid)(bOwner) == GroupData(group_id_fix)(gUID))
						(
							check = true
						)
						break
					)
				)
				if(!check)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ w budynku grupy aby wejœæ na s³u¿bê., OK, )
					return 1
				)
			)
			else if(door_id != INVALID_DOOR_ID)
			(
				if(DoorData(door_id)(dUID))
				(
					if(DoorData(door_id)(dOwnerType) != OWNER_GROUP || DoorData(door_id)(dOwner) != GroupData(group_id_fix)(gUID))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ w budynku grupy aby wejœæ na s³u¿bê., OK, )
						return 1
					)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ w budynku grupy aby wejœæ na s³u¿bê., OK, )
					return 1
				)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ w budynku grupy aby wejœæ na s³u¿bê., OK, )
				return 1
			)
		)

  		PlayerCache(playerid)(pGroupDuty) = PlayerGroup(playerid)(group_slot)(gUID)
		PlayerCache(playerid)(pGroupDutyTime) = gettime()

		if(GroupData(group_id_fix)(gType) == GROUP_DOC || GroupData(group_id_fix)(gType) == GROUP_POLICE || GroupData(group_id_fix)(gType) == GROUP_MEDICAL || GroupData(group_id_fix)(gType) == GROUP_FBI || GroupData(group_id_fix)(gType) == GROUP_FIREDEPT || GroupData(group_id_fix)(gType) == GROUP_NEWS || GroupData(group_id_fix)(gType) == GROUP_GOV || GroupData(group_id_fix)(gType) == GROUP_ARMY)
		(
			if(GroupData(group_id_fix)(gColor) != -1)
			(
				format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
				Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), GroupData(group_id_fix)(gColor), string)

				PlayerCache(playerid)(pNickColor) = GroupData(group_id_fix)(gColor)
			)
		)

  		format(string, sizeof(string), » Wszed³eœ na s³u¿bê grupy %s (UID: %d). Aby zejœæ ze s³u¿by wpisz /duty grupa., GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
		SendClientMessage(playerid, GroupData(group_id_fix)(gColor), string)

		OnPlayerDutyStart(playerid, DUTY_GROUP, GroupData(group_id_fix)(gUID))

	 	PlayerCache(playerid)(pMainGroupSlot) = group_slot + 1
		PlayerCache(playerid)(pFlood) = 10
		return 1
	)
	if(!strcmp(duty_type, admin, true) || !strcmp(duty_type, support, true) || !strcmp(duty_type, nauczyciel, true))
	(
		if(PlayerCache(playerid)(pAdmin) == 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		name(32)
		if(!PlayerCache(playerid)(pAdminDuty))
		(
			PlayerCache(playerid)(pAdminDuty) = true
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Wszed³eœ na s³u¿bê administratora., OK, )

			if(PlayerCache(playerid)(pAdmin) != -1)
			(
				format(name, sizeof(name), %s, PlayerCache(playerid)(pGlobalName), playerid)
				strmid(PlayerCache(playerid)(pName), name, 0, strlen(name), 32)

				format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
				Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
			)

			OnPlayerDutyStart(playerid, DUTY_ADMIN, 0)
		)
		else
		(
			PlayerCache(playerid)(pAdminDuty) = false
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Zszed³eœ ze s³u¿by administratora., OK, )

			GetPlayerName(playerid, name, sizeof(name))
			strmid(PlayerCache(playerid)(pName), name, 0, strlen(name), 32)

			format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
			Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)

			OnPlayerDutyStop(playerid)

			if(IsPlayerInAnyVehicle(playerid))
			(
				vehid = GetPlayerVehicleID(playerid)
				if(CarInfo(vehid)(cAccess) & VEH_ACCESS_DIM)
				(
					format(name, sizeof(name), Nieznajomy_%s, CharCode(playerid))
					strmid(PlayerCache(playerid)(pName), name, 0, strlen(name), 32)

					format(string, sizeof(string), %s%s, PlayerName(playerid), GetPlayerStatusInfo(playerid))
					Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
				)
			)
		)
		return 1
	)
	return 1
)

CMD:sluzba(playerid, params()) return cmd_duty(playerid, params)

CMD:pokaz(playerid, params())
(
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /pokaz (dowod | prawko | metryczke | poczytalnosc | id | cennik | przedmiot | rejestracje))
		return 1
	)
	if(!strcmp(type, dowod, true))
	(
		if(!(PlayerCache(playerid)(pDocuments) & DOC_PROOF))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz tego dokumentu., OK, )
			return 1
		)
		giveplayer_id, string(256)
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /pokaz dowod (ID gracza))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		format(string, sizeof(string), Imiê, nazwisko:\t%s\nRok urodzenia:\t%d, PlayerRealName(playerid), PlayerCache(playerid)(pBirth))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, ** Dowód osobisty **, string, OK, )

		format(string, sizeof(string), * %s pokaza³ dowód osobisty %s., PlayerName(playerid), PlayerName(giveplayer_id))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 1
	)
	if(!strcmp(type, prawko, true))
	(
		if(!(PlayerCache(playerid)(pDocuments) & DOC_DRIVER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz tego dokumentu., OK, )
			return 1
		)
		giveplayer_id, string(256)
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /pokaz prawko (ID gracza))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		//format(string, sizeof(string), Imiê, nazwisko:\t%s\nRok urodzenia:\t%d, PlayerName(playerid), PlayerCache(playerid)(pBirth))
		//ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, ** Prawo jazdy **, string, OK, )

		doc_gInterfaceShow(playerid, giveplayer_id)

		TextDrawSetString(Text:TextDrawMainInfo(giveplayer_id), ~y~Okienko zamknie sie automatycznie za kilka sekund.)
		TextDrawShowForPlayer(giveplayer_id, Text:TextDrawMainInfo(giveplayer_id))

		PlayerCache(giveplayer_id)(pShowInfoText) = 5

		format(string, sizeof(string), * %s pokaza³ prawo jazdy %s., PlayerName(playerid), PlayerName(giveplayer_id))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 1
	)
	if(!strcmp(type, metryczke, true))
	(
		if(!(PlayerCache(playerid)(pDocuments) & DOC_SEND))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz tego dokumentu., OK, )
			return 1
		)
		giveplayer_id, string(256)
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /pokaz metryczke (ID gracza))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		format(string, sizeof(string), Imiê, nazwisko:\t%s\nRok urodzenia:\t%d\n\nStan zdrowia:\tNienaganny, PlayerRealName(playerid), PlayerCache(playerid)(pBirth))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, ** Metryczka zdrowia **, string, OK, )

		format(string, sizeof(string), * %s pokaza³ metryczkê zdrowia %s., PlayerName(playerid), PlayerName(giveplayer_id))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 1
	)
	if(!strcmp(type, poczytalnosc, true))
	(
		if(!(PlayerCache(playerid)(pDocuments) & DOC_SANITY))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz tego dokumentu., OK, )
			return 1
		)
		giveplayer_id, string(256)
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /pokaz poczytalnosc (ID gracza))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		format(string, sizeof(string), Imiê, nazwisko:\t%s\nRok urodzenia:\t%d, PlayerRealName(playerid), PlayerCache(playerid)(pBirth))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, ** Zaœwiadczenie o poczytalnoœci **, string, OK, )

		format(string, sizeof(string), * %s pokaza³ zaœwiadczenie o poczytalnoœci %s., PlayerName(playerid), PlayerName(giveplayer_id))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 1
	)
	if(!strcmp(type, id, true))
	(
		if(!PlayerCache(playerid)(pGroupDuty))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
			return 1
		)
		giveplayer_id, title(64), string(256)
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /pokaz id (ID gracza))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		group_id_fix = GetPlayerDutyGroupID(playerid), group_slot = GetPlayerGroupSlot(playerid, GroupData(group_id_fix)(gUID))
		format(title, sizeof(title), ** %s **, GroupData(group_id_fix)(gName))

		format(string, sizeof(string), Imiê, nazwisko:\t%s\nRok urodzenia:\t%d\nRanga:\t\t%s, PlayerRealName(playerid), PlayerCache(playerid)(pBirth), PlayerGroup(playerid)(group_slot)(gTitle))
		ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, title, string, OK, )

		format(string, sizeof(string), * %s pokaza³ identyfikator %s., PlayerName(playerid), PlayerName(giveplayer_id))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 1
	)
	if(!strcmp(type, cennik, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /pokaz cennik (ID gracza))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)

		data(64), list_items(1024), product_name(32), product_price

		if(GetPlayerVirtualWorld(playerid) == 0)
		(
 			foreach(Booths, boothid)
			(
				if(IsPlayerInRangeOfPoint(playerid, BoothData(boothid)(bRadius), BoothData(boothid)(bPosX), BoothData(boothid)(bPosY), BoothData(boothid)(bPosZ)))
				(
					dooruid = BoothData(boothid)(bDoorUID), doorid

					foreach(Doors, door)
					(
						if(DoorData(door)(dUID) == dooruid)
						(
							doorid = door
						)
					)
					if(doorid == INVALID_DOOR_ID)
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wyst¹pi³ problem z magazynem Twojej budki. Zg³oœ siê do Administracji w celu naprawienia problemu., OK, )
						return 1
					)

					mysql_query_format(SELECT product_price, product_name FROM hrp_products WHERE product_dooruid = %d, DoorData(doorid)(dUID))

					mysql_store_result()
					while(mysql_fetch_row(data, |))
					(
						sscanf(data, p(|)ds(32), product_price, product_name)
						format(list_items, sizeof(list_items), %s\n$%d\t%s, list_items, product_price, product_name)
					)
					mysql_free_result()
					if(strlen(list_items) ) 0)
					(
						ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_LIST, Cennik, list_items, OK, )
					)
					else
					(
						ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych produktów w magazynie., OK, )
					)
					return 1
				)
			)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku lub budce grupy, aby móc oferowaæ produkty z magazynu., OK, )
			return 1
		)
		else
		(
			doorid = GetPlayerDoorID(playerid)
			mysql_query_format(SELECT product_price, product_name FROM hrp_products WHERE product_dooruid = %d, DoorData(doorid)(dUID))
			mysql_store_result()
			while(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)ds(32), product_price, product_name)
				format(list_items, sizeof(list_items), %s\n$%d\t%s, list_items, product_price, product_name)
			)
			mysql_free_result()
			if(strlen(list_items) ) 0)
			(
				ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_LIST, Cennik, list_items, OK, )
			)
			else
			(
				ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych produktów w magazynie., OK, )
			)
			return 1
		)
	)
	if(!strcmp(type, przedmiot, true))
	(
		item_uid, giveplayer_id
		if(sscanf(varchar, du, item_uid, giveplayer_id))
		(
			hrp_Tip(playerid, /pokaz przedmiot (UID przedmiotu) (ID gracza))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		itemid = GetItemID(item_uid)
		if(itemid == 0 || !ItemInfo(itemid)(iUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Przedmiot o podanym UID nie istnieje., OK, )
	 		return 1
		)
		ShowPlayerItemInfo(giveplayer_id, itemid)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Przedmiot zosta³ pokazany., OK, )
		return 1
	)
	if(!strcmp(type, rejestracje, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /pokaz rejestracje (ID gracza))
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		if(!IsPlayerInAnyVehicle(playerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ w pojeŸdzie aby pokazaæ rejestracjê., OK, )
	 		return 1
		)
		vehid = GetPlayerVehicleID(playerid)
		if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
		(
			if(CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz dokumentów tego pojazdu., OK, )
				return 1
			)
		)
		if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz dokumentów tego pojazdu., OK, )
				return 1
			)
		)

		ShowPlayerVehicleInfo(giveplayer_id, vehid)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Rejestracja zosta³a pokazana., OK, )
		return 1
	)
	return 1
)

CMD:pay(playerid, params())
(
	/*if(PlayerCache(playerid)(pAdmin) == 0)
	(
		GuiMsg(playerid,Funkcja tymczasowo zablokowana.,1)
		return 1
	)*/
	
	// Kolejne bugowanie
	bool:checkbug = false
	if(gettime() - LogTime(playerid) ) 60)
		checkbug= true
	
	if(!checkbug)
	(
		GuiMsg(playerid, Musisz chwilê odczekaæ nim u¿yjesz tej komendy., 0)
		return 1
	)

	giveplayer_id, price, string(128)
	if(sscanf(params, dd, giveplayer_id, price))
	(
		hrp_Tip(playerid, /pay (ID gracza) (Kwota))
		return 1
	)
	if(IsPlayerNPC(giveplayer_id))
	(
		GuiMsg(playerid, Nie mo¿esz wysy³aæ oferty do bota., 1)
		return 1
	)
	if(PlayerCache(playerid)(pGamePoints) ( 100)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz mieæ conajmniej 100GS, by móc u¿yæ tej komendy., OK, )
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz podaæ pieniedzy sobie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
		return 1
	)
	if(price (= 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pCash) ( price)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz takiej iloœci gotówki., OK, )
		return 1
	)

	printf((blint kasa) Gracz %s (UID: %i) ma $%i przed przelewem.,PlayerName(playerid),PlayerCache(playerid)(pUID),PlayerCache(playerid)(pCash))
	safetyUID = PlayerCache(playerid)(pUID)	// pobierz tak dla pewnoœci

	hrp_GivePlayerMoney(playerid, -price)
	hrp_GivePlayerMoney(giveplayer_id, price)

	// dodatkowe zabezpieczenie (?)
	buffer(256)
	format(buffer,sizeof(buffer),UPDATE hrp_characters SET char_cash = %i WHERE char_uid = %i, PlayerCache(playerid)(pCash), safetyUID)
	mysql_query(buffer)

	SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
	SavePlayerStats(giveplayer_id, SAVE_PLAYER_BASIC)

	ApplyAnimation(playerid, DEALER, shop_pay, 4.1, 0, 0, 0, 0, 0, 1)

	format(string, sizeof(string), * %s podaje trochê gotówki %s., PlayerName(playerid), PlayerName(giveplayer_id))
	FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)

	format(string, sizeof(string), Poda³eœ $%d dla gracza %s., price, PlayerName(giveplayer_id))
	SendClientMessage(playerid, COLOR_LIGHTBLUE, string)

	format(string, sizeof(string), Otrzyma³eœ $%d od gracza %s., price, PlayerName(playerid))
	SendClientMessage(giveplayer_id, COLOR_LIGHTBLUE, string)

	hrp_MoneyActionLog(%s (UID: %d) podal $%d dla %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), price, PlayerRealName(giveplayer_id), PlayerCache(giveplayer_id)(pUID))

	printf((blint kasa) Gracz %s (UID: %i) ma $%i po przelewie.,PlayerName(playerid),PlayerCache(playerid)(pUID),PlayerCache(playerid)(pCash))

	PlayerCache(playerid)(pFlood) = 2
	return 1
)

CMD:plac(playerid, params()) return cmd_pay(playerid, params)

CMD:anim(playerid, params())
(
	list_anims(2048)
	for (anim_id = 1 anim_id ( MAX_ANIMATIONS anim_id++)
	(
		format(list_anims, sizeof(list_anims), %s\n%s, list_anims, AnimInfo(anim_id)(aCommand))
	)
	if(strlen(list_anims))
	(
		ShowPlayerDialog(playerid, D_PLAY_ANIM, DIALOG_STYLE_LIST, Lista animacji:, list_anims, Start, Zamknij)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych animacji., OK, )
	)
	return 1
)

CMD:animacje(playerid, params()) return cmd_anim(playerid, params)

CMD:sprzatacz(playerid, params())
(
	if(PlayerCache(playerid)(pJob) != JOB_SWEEPER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ sprz¹taczem ulic. Aby zmieniæ swoj¹ pracê dorywcz¹ udaj siê do urzêdu., OK, )
		return 1
	)
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ kierowc¹ pojazdu Sweeper aby zacz¹æ tê pracê., OK, )
		return 1
	)
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 574)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ kierowc¹ pojazdu Sweeper aby zacz¹æ tê pracê., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pSweep))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wyst¹pi³ b³¹d. Pracujesz aktualnie jako sprz¹tacz ulic., OK, )
		return 1
	)

	ShowPlayerDialog(playerid, D_SWEEP_ACCEPT, DIALOG_STYLE_MSGBOX, Praca sprz¹tacza ulic, Wsiad³eœ do pojazdu Sweeper. Urz¹d miasta udostêpnia Ci go do wykonania Twojej pracy czyszczenia ulic. Czy akceptujesz pracê sprz¹tacza?, Akceptuj, Odrzuæ)
	return 1
)


CMD:paczka(playerid, params())
(
	if(PlayerCache(playerid)(pJob) != JOB_COURIER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz pracy kuriera, jako dorywczej., OK, )
		return 1
	)
	type(12)
	if(sscanf(params, s(12), type))
	(
		if(PlayerCache(playerid)(pWholeSale) == -1)
  		(
			PlayerCache(playerid)(pWholeSale) = random(3)
		)
		wholesale = PlayerCache(playerid)(pWholeSale)

		if(!PlayerCache(playerid)(pPackage))
		(
			PlayerCache(playerid)(pPackage) = true

			SetPlayerCheckpoint(playerid, WholeSalePos(wholesale)(0), WholeSalePos(wholesale)(1), WholeSalePos(wholesale)(2), 10.0)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Rozwo¿enie paczek rozpoczête, udaj siê w wyznaczone miejsce aby odebraæ paczkê., OK, )
		)
		else
		(
			if(!PlayerCache(playerid)(pPackageUID))
			(
				if(!IsPlayerInRangeOfPoint(playerid, 10.0, WholeSalePos(wholesale)(0), WholeSalePos(wholesale)(1), WholeSalePos(wholesale)(2)))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Aby odebraæ paczkê, musisz znajdowaæ siê pod magazynem.\nAby anulowaæ rozwo¿enie paczek, wpisz /paczka anuluj., OK, )
					return 1
				)
				doorid, list_packages(1024)
				foreach(Packages, package_id)
				(
					if(PackageInfo(package_id)(pUID))
					(
						if(!PackageInfo(package_id)(pSecured))
						(
							doorid = GetDoorID(PackageInfo(package_id)(pDoorUID))
							format(list_packages, sizeof(list_packages), %s\n%d\t%s, list_packages, PackageInfo(package_id)(pUID), DoorData(doorid)(dName))
						)
					)
				)
				if(strlen(list_packages))
				(
					ShowPlayerDialog(playerid, D_GET_PACKAGE, DIALOG_STYLE_LIST, Paczki w magazynie:, list_packages, Dostarcz, Anuluj)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych paczek w magazynie., OK, )
				)
			)
			else
			(
				package_id = GetPackageID(PlayerCache(playerid)(pPackageUID)), doorid = GetDoorID(PackageInfo(package_id)(pDoorUID))
				if(!IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Udaj siê na miejsce zaznaczone na mapie, a nastêpnie u¿yj /paczka aby od³o¿yæ paczkê., OK, )
					return 1
				)
				AddDoorProduct(PackageInfo(package_id)(pItemName), PackageInfo(package_id)(pItemType), PackageInfo(package_id)(pItemValue1), PackageInfo(package_id)(pItemValue2), PackageInfo(package_id)(pItemPrice), PackageInfo(package_id)(pItemNumber), PackageInfo(package_id)(pDoorUID))
				DeletePackage(package_id)

				PlayerCache(playerid)(pPackage) = false
				PlayerCache(playerid)(pPackageUID) = 0

				DisablePlayerCheckpoint(playerid)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Paczka zosta³a dostarczona pomyœlnie., OK, )

				if(PlayerCache(playerid)(pGroupDuty))
				(
					group_id_fix = GetPlayerDutyGroupID(playerid)
					if(GroupData(group_id_fix)(gType) == GROUP_TRANSPORT)
					(
						GroupData(group_id_fix)(gCash) += 45
						SaveGroup(group_id_fix)

						//hrp_GivePlayerMoney(playerid, 10)
						return 1
					)
				)
				hrp_GivePlayerMoney(playerid, 35)
			)
		)
		return 1
	)
	if(!strcmp(type, anuluj, true))
	(
		if(!PlayerCache(playerid)(pPackage))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie nie rozwozisz paczek., OK, )
			return 1
		)
		PlayerCache(playerid)(pPackage) = false
		PlayerCache(playerid)(pPackageUID) = 0

		DisablePlayerCheckpoint(playerid)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Rozwo¿enie paczek zosta³o anulowane., OK, )
		return 1
	)
	return 1
)

CMD:wyrzuc(playerid, params())
(
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /wyrzuc (ID gracza))
		return 1
	)
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie jako kierowca., OK, )
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wyrzuciæ siebie., OK, )
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
	if(!IsPlayerInAnyVehicle(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w pojeŸdzie., OK, )
		return 1
	)
	if(GetPlayerVehicleID(playerid) != GetPlayerVehicleID(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz musi siedzieæ w tym samym pojeŸdzie., OK, )
		return 1
	)
	format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~w~Gracz ~p~%s ~w~wyrzuca Cie z pojazdu, PlayerName(playerid))
	GameTextForPlayer(giveplayer_id, string, 5000, 3)

	format(string, sizeof(string), ~n~~n~~n~~n~~n~~n~~w~Wyrzucasz gracza ~p~%s ~w~z pojazdu, PlayerName(giveplayer_id))
	GameTextForPlayer(playerid, string, 5000, 3)

	RemovePlayerFromVehicle(giveplayer_id)
	return 1
)

CMD:dotacja(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_GOV)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	group_uid, price, string(256)
  	if(sscanf(params, dd, group_uid, price))
  	(
  		hrp_Tip(playerid, /dotacja (UID grupy) (Kwota))
  		return 1
  	)
  	group_id_fix = GetGroupID(group_uid)
  	if(group_id_fix == INVALID_GROUP_ID)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne UID grupy., OK, )
  		return 1
  	)
  	if(price ( 0)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê., OK, )
  		return 1
  	)
  	/*max_dotation = GroupTypeInfo(GroupData(group_id_fix)(gType))(gMaxDotation)
  	if(price (= max_dotation)
  	(
		GroupData(group_id_fix)(gDotation) = price
		SaveGroup(group_id_fix)

		format(string, sizeof(string), Pomyœlnie ustalono wyokoœæ dotacji na pracownika dla grupy.\n\nGrupa: %s (UID: %d)\nWysokoœæ dotacji: $%d, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID), GroupData(group_id_fix)(gDotation))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
  	)
  	else
  	(
 		format(string, sizeof(string), Dla tego typu grupy maksymalna dotacja mo¿e wynieœæ $%d., max_dotation)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
  	)*/
	if(price (= 2000)
	(
		GroupData(group_id_fix)(gDotation) = price
		SaveGroup(group_id_fix)

		format(string, sizeof(string), Pomyœlnie ustalono wyokoœæ dotacji na pracownika dla grupy.\n\nGrupa: %s (UID: %d)\nWysokoœæ dotacji: $%d, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID), GroupData(group_id_fix)(gDotation))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	)
  	else
  	(
 		format(string, sizeof(string), Maksymalna dotacja mo¿e wynieœæ $2000.)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, string, OK, )
  	)
	return 1
)

CMD:report(playerid, params())
(
	giveplayer_id, text(128), string(256)
	if(sscanf(params, us(128), giveplayer_id, text))
	(
		hrp_Tip(playerid, /report (ID gracza) (Treœæ))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wys³aæ raportu na siebie., OK, )
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
	if(PlayerCache(playerid)(pLastReport))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Zamierzasz wys³aæ raport zaraz po poprzednim, odczekaj chwilê., OK, )
		return 1
	)
	format(string, sizeof(string), (Raport) %s (%d): %s (%s (%d)), PlayerName(playerid), playerid, text, PlayerName(giveplayer_id), giveplayer_id)
	SendClientMessage(playerid, COLOR_RED, string)

	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pAdmin) != 0 && PlayerCache(i)(pAdminDuty))
			(
				SendClientMessage(i, COLOR_LIGHTRED, string)
			)
		)
	)
	PlayerCache(playerid)(pLastReport) = 20
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Za co mo¿esz zostaæ ukarany?\n\n1. Za kilkukrotne wysy³anie powtarzaj¹cych siê raportów.\n2. Za pytania odnosz¹ce siê do administracji na /raport.\n3. Wyzwiska oraz obrazê w stosunku do administracji., OK, )
	return 1
)

CMD:raport(playerid, params()) return cmd_report(playerid, params)

CMD:kompresor(playerid, params())
(
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby u¿yæ kompresora musisz znajdowaæ siê poza pojazdem., OK, )
		return 1
	)

	object_id = GetClosestObject(playerid)
	if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_AIR_PUMP)
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnego kompresora w pobli¿u., OK, )
   		return 1
	)

	vehid = GetClosestVehicle(playerid)
	if(vehid == INVALID_VEHICLE_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz staæ przy pojeŸdzie aby napompowaæ w nim ko³o., OK, )
		return 1
	)
	if(GetDistanceToVehicle(playerid, vehid) ) 4.0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz staæ przy pojeŸdzie aby napompowaæ w nim ko³o., OK, )
		return 1
	)
	if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
	(
		if(!IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ cz³onkiem grupy, która jest w³aœcicielem tego pojazdu., OK, )
			return 1
		)
	)
	if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
	(
		if(CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego pojazdu., OK, )
			return 1
		)
	)

	player_vw = GetPlayerVirtualWorld(playerid), doorid = GetDoorID(player_vw)
	if(doorid != INVALID_DOOR_ID)
	(
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
			if(group_id_fix != INVALID_GROUP_ID)
			(
				if(GroupData(group_id_fix)(gType) == GROUP_WORKSHOP || GroupData(group_id_fix)(gType) == GROUP_GASSTATION)
				(
					if(PlayerCache(playerid)(pCash) ) 10)
					(
						hrp_GivePlayerMoney(playerid, -10)
						GroupData(group_id_fix)(gCash) += 10
						SaveGroup(group_id_fix)
					)
					else
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie masz przy sobie $10 potrzebnych do uruchomienia kompresora., OK, )
						return 1
					)
				)
			)
		)
	)

	PlayerCache(playerid)(pPumpVeh) = vehid
	PlayerCache(playerid)(pPumpTime) = 70
	return 1
)

CMD:pompka(playerid, params()) return cmd_kompresor(playerid, params)
CMD:pompa(playerid, params()) return cmd_kompresor(playerid, params)

CMD:tankuj(playerid, params())
(
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby zatankowaæ pojazd musisz znajdowaæ siê obok niego., OK, )
		return 1
	)
	object_id = GetClosestObject(playerid)
	if((object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_FUELING) && GetVehicleModel(GetClosestVehicle(playerid)) != 584)
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnego dystrybutora w pobli¿u., OK, )
   		return 1
	)
	bens_type, string(128)
	if(sscanf(params, d, bens_type))
	(
		hrp_Tip(playerid, /tankuj (Rodzaj paliwa) | Rodzaje paliwa: 0 - Benzyna, 1 - Gaz, 2 - Ropa, 3 - Nafta lotnicza)
		return 1
	)
	vehid = GetClosestVehicle(playerid)
	if(vehid == INVALID_VEHICLE_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnego pojazdu w pobli¿u., OK, )
		return 1
	)
	if(bens_type ( 0 || bens_type ) 3)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wybrano nieprawid³owy rodzaj paliwa., OK, )
		return 1
	)
	if(bens_type != CarInfo(vehid)(cFuelType))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wybrany rodzaj paliwa nie pasuje tego pojazdu., OK, )
		return 1
	)
	if(CarInfo(vehid)(cFuel) )= GetVehicleMaxFuel(CarInfo(vehid)(cModel)))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W baku nie zmiesci siê wiêcej paliwa., OK, )
		return 1
	)
	
	RefuelData(playerid)(rVeh) = vehid
	RefuelData(playerid)(rLiters) = 0
	RefuelData(playerid)(rPrice) = 0.00
	PlayerCache(playerid)(pFueling) = true	
	if(bens_type == TYPE_BENS) 			RefuelData(playerid)(rType) = TYPE_BENS, RefuelData(playerid)(rPricePerL) = BENS_PRICE
	else if(bens_type == TYPE_GAS) 		RefuelData(playerid)(rType) = TYPE_GAS, RefuelData(playerid)(rPricePerL) = GAS_PRICE
	else if(bens_type == TYPE_DIESEL) 	RefuelData(playerid)(rType) = TYPE_DIESEL, RefuelData(playerid)(rPricePerL) = DIESEL_PRICE
	else if(bens_type == TYPE_AIRFUEL) RefuelData(playerid)(rType) = TYPE_AIRFUEL, RefuelData(playerid)(rPricePerL) = AIRFUEL_PRICE
	
	if(PlayerCache(playerid)(pCash) ( floatround(RefuelData(playerid)(rPricePerL)))
	(
		PlayerCache(playerid)(pFueling) = false
		RefuelData(playerid)(rType) = 0
		RefuelData(playerid)(rPricePerL) = 0.00
		RefuelData(playerid)(rVeh) = 0
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz tyle pieniêdzy., OK, )
		return 1
	)
	
	format(string, sizeof(string), Aby zakonczyc proces tankowania nacisnij klawisz ~k~~PED_SPRINT~.)
	SendClientMessage(playerid, COLOR_GREY, string)
	return 1
)

CMD:zatankuj(playerid, params()) return cmd_tankuj(playerid, params)

CMD:salon(playerid, params())
(
  	type(32), varchar(32)
  	if(sscanf(params, s(32)S()(32), type, varchar))
  	(
  		hrp_Tip(playerid, /salon (oferuj | cennik | kluczyki))
  		return 1
  	)
  	if(!strcmp(type, oferuj, true))
  	(
  		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_CARDEALER) 
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		if(!IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /salon oferuj (ID gracza))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
  		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w salonie samochodowym., OK, )
	   		return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w salonie samochodowym., OK, )
	   		return 1
		)
		MainPlayerTable(playerid) = giveplayer_id
		ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategoriê, 1. Jednoœlady\n2. Trzydrzwiowe\n3. Piêciodrzwiowe\n4. Furgonetki i ciê¿arówki\n5.Sportowe\n6. Lowridery \n7  Pickupy\n8  Lataj¹ce\n9  P³ywaj¹ce\n10  Pozosta³e , Wybierz, Anuluj)
		//ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategoriê, 1. Jednoœlady\n2. Trzydrzwiowe\n3. Piêciodrzwiowe\n4. Furgonetki i ciê¿arówki\n5. Pozosta³e, Wybierz, Anuluj)
		return 1
  	)
  	if(!strcmp(type, cennik, true))
  	(
  		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w salonie samochodowym., OK, )
	   		return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w salonie samochodowym., OK, )
	   		return 1
		)
		group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
		if(GroupData(group_id_fix)(gType) != GROUP_CARDEALER)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w salonie samochodowym., OK, )
			return 1
		)
		ShowPlayerDialog(playerid, D_SALON_PRICE_LIST, DIALOG_STYLE_LIST, Wybierz kategoriê, 1. Jednoœlady\n2. Trzydrzwiowe\n3. Piêciodrzwiowe\n4. Furgonetki i ciê¿arówki\n5.Sportowe\n6. Lowridery \n7  Pickupy\n8  Lataj¹ce\n9  P³ywaj¹ce\n10  Pozosta³e , Wybierz, Anuluj)
		//ShowPlayerDialog(playerid, D_SALON_PRICE_LIST, DIALOG_STYLE_LIST, Wybierz kategoriê, 1. Jednoœlady\n2. Trzydrzwiowe\n3. Piêciodrzwiowe\n4. Furgonetki i ciê¿arówki\n5. Pozosta³e, Wybierz, Anuluj)
  		return 1
  	)
  	if(!strcmp(type, kluczyki, true))
  	(
  		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_CARDEALER || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
  		giveplayer_id, veh_uid
		if(sscanf(varchar, ud, giveplayer_id, veh_uid))
		(
			hrp_Tip(playerid, /salon kluczyki (ID gracza) (UID pojazdu))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
  		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w salonie samochodowym., OK, )
	   		return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w salonie samochodowym., OK, )
	   		return 1
		)
		vehid = GetVehicleID(veh_uid)
		if(vehid == INVALID_VEHICLE_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Pojazd musi byæ zespawnowany., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwnerType) != OWNER_PLAYER)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz nie jest w³aœcicielem tego pojazdu., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwner) != PlayerCache(giveplayer_id)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz nie jest w³aœcicielem tego pojazdu., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_KEYS, Kluczyki, vehid, 80)
  		return 1
  	)
	return 1
)

CMD:qs(playerid, params())
(
	if(PlayerCache(playerid)(pFlood) ) 0)
	(
		GuiMsg(playerid,Wyst¹pi³ b³¹d, musisz chwilê odczekaæ zanim u¿yjesz tej komendy.,0)
		return 1
	)
	string(64),
		Float:PosX, Float:PosY, Float:PosZ,
		VirtualWorld, InteriorID

	GetPlayerPos(playerid, PosX, PosY, PosZ)

	VirtualWorld = GetPlayerVirtualWorld(playerid)
	InteriorID = GetPlayerInterior(playerid)

 	format(string, sizeof(string), (( %s - /qs )), PlayerRealName(playerid))

	PlayerCache(playerid)(pPosX) = PosX
	PlayerCache(playerid)(pPosY) = PosY
	PlayerCache(playerid)(pPosZ) = PosZ

	PlayerCache(playerid)(pVW) = VirtualWorld
	PlayerCache(playerid)(pInt) = InteriorID

	PlayerCache(playerid)(pCrash) = 1
	PlayerCache(playerid)(pQSing) = 1
	SavePlayerStats(playerid, SAVE_PLAYER_POS)

	PlayerCache(playerid)(pQuit) = QUIT_QS

	Kick(playerid)
	return 1
)

CMD:szrot(playerid, params())
(
	if(PlayerCache(playerid)(pHours) ( 5)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zdezelowaæ auta przed przegraniem 5 godzin., OK, )
		return 1
	)
	if(IsPlayerInRangeOfPoint(playerid, 10.0, -1850.3809, -1677.8109, 21.4613))
	(
		if(IsPlayerInAnyVehicle(playerid))
		(
			vehid = GetPlayerVehicleID(playerid),
				veh_price, sell_price, string(128), data(32)

			mysql_query_format(SELECT salonveh_price FROM hrp_salonveh WHERE salonveh_model = %d, GetVehicleModel(vehid))
			mysql_store_result()
			mysql_fetch_row(data, |)
			sscanf(data, p(|)d, veh_price)
			mysql_free_result()

			if(!veh_price)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d., Tego pojazdu nie da siê zdezelowaæ., OK, )
				return 1
			)

			sell_price = floatround(veh_price * 0.15)

			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER)
			(
				if(CarInfo(vehid)(cOwner) == PlayerCache(playerid)(pUID))
				(
					MainPlayerTable(playerid) = vehid
					SecondPlayerTable(playerid) = sell_price

					//PlayerCache(playerid)(pCash) += sell_price
					//DeleteVehicle(vehid)

					format(string, sizeof(string), Pojazd zostanie zdezelowany.\n\nWartoœæ pojazdu:\t%d\nKwota sprzeda¿y:\t%d\n\nCzy jesteœ pewny?, veh_price, sell_price)
					ShowPlayerDialog(playerid, D_DESTROY_CAR, DIALOG_STYLE_MSGBOX, PotwierdŸ transakcjê, string, Tak, Nie)
					return 1
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nie jesteœ w³aœcicielem tego pojazdu. Nie mo¿esz go zdezelowaæ., OK, )
					return 1
				)
			)
			else if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
			(
				if(IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_LEADER))
				(
					MainPlayerTable(playerid) = vehid
					SecondPlayerTable(playerid) = sell_price

					//PlayerCache(playerid)(pCash) += sell_price
					//DeleteVehicle(vehid)

					format(string, sizeof(string), Pojazd zostanie zdezelowany.\n\nWartoœæ pojazdu:\t%d\nKwota sprzeda¿y:\t%d\n\nCzy jesteœ pewny?, veh_price, sell_price)
					ShowPlayerDialog(playerid, D_DESTROY_CAR, DIALOG_STYLE_MSGBOX, PotwierdŸ transakcjê, string, Tak, Nie)
					return 1
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nie masz uprawnieñ do zdezelowania tego pojazdu., OK, )
					return 1
				)
			)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie, który chcesz zdezelowaæ., OK, )
			return 1
		)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Musisz znajdowaæ siê na San Fierro Scrapyard aby zdezelowaæ pojazd., OK, )
		return 1
	)
	return 1
)

CMD:bus(playerid, params())
(
	if(PlayerCache(playerid)(pBW) != 0 || PlayerCache(playerid)(pBusRide))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Nie mo¿esz teraz u¿yæ tej komendy., OK, )
		return 1
	)
	object_id = GetClosestObject(playerid)
	if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_BUSSTOP)
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê na ¿adnym z przystanków., OK, )
   		return 1
	)

	for(i = 0  i ( MAX_PLAYERS i++)
	(
		if(PlayerCache(i)(pGroupDuty))
		(
			group_id_fix = GetPlayerDutyGroupID(i)
			if(GroupData(group_id_fix)(gType) == GROUP_TAXI)
			(
				if(PlayerCache(i)(pTaxiPassenger) == INVALID_PLAYER_ID)
				(
					if(!IsPlayerInAnyVehicle(i))
						continue
					
					vehicle_id = GetPlayerVehicleID(i)
					if(CarInfo(vehicle_id)(cOwnerType) == OWNER_GROUP)
					(
						owner_group = CarInfo(vehicle_id)(cOwner)
						if(GroupData(GetGroupID(owner_group))(gType) == GROUP_TAXI)
						(
							GuiMsg(playerid,Przynajmniej jeden z taksówkarzy jest aktualnie na s³u¿bie i nie posiada ¿adnego zlecenia.\n\nU¿yj telefonu lub pobliskiej budki by wezwaæ taksówkê zadzwoñ pod numer (FF0000)777,1)
							return 1
						)
					)
				)
			)
		)
	)

	list_busstops(1024)
	for(b = 1 b ( MAX_BUS_STOPS b++)
	(
		if(BusStopData(b)(bUID) != 0)
		(
			if(IsPlayerInRangeOfPoint(playerid, 5.0, BusStopData(b)(bPosX), BusStopData(b)(bPosY), BusStopData(b)(bPosZ)))
			(
				for(bs = 1 bs ( MAX_BUS_STOPS bs++)
				(
					if(BusStopData(bs)(bUID) != 0 && bs != b)
					(
						format(list_busstops, sizeof(list_busstops), %s\n%d\t%s, list_busstops, bs, BusStopData(bs)(bName))
			  		)
				)
				if(strlen(list_busstops) (= 0)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie ma ¿adnych utworzonych przystanków., OK, )
					return 1
				)

				PlayerCache(playerid)(pBusStart) = b

				ShowPlayerDialog(playerid, D_SELECT_BUSSTOP, DIALOG_STYLE_LIST, Wybierz, dok¹d chcesz siê udaæ:, list_busstops, JedŸ, Zamknij)
				return 1
			)
		)
	)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê na przystanku autobusowym., OK, )
	return 1
)


CMD:przejazd(playerid, params())
(
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie., OK, )
		return 1
	)
	foreach(Doors, doorid)
	(
		if(DoorData(doorid)(dGarage))
		(
	 		if(IsPlayerInRangeOfPoint(playerid, 5.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)) && GetPlayerVirtualWorld(playerid) == DoorData(doorid)(dEnterVW))
	   		(
	   			OnPlayerEnterDoor(playerid, doorid)
	   			if(PlayerCache(playerid)(pMoveObject) != INVALID_OBJECT_ID)
				(
					CancelEdit(playerid)
				)
	   			break
	   		)
		 	else if(IsPlayerInRangeOfPoint(playerid, 5.0, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ)) && GetPlayerVirtualWorld(playerid) == DoorData(doorid)(dExitVW))
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
	return 1
)

CMD:aresztuj(playerid, params())
(
	if(!IsPlayerInGroupType(playerid, GROUP_DOC) && !IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, time
	if(sscanf(params, ud, giveplayer_id, time))
	(
		hrp_Tip(playerid, /aresztuj (ID gracza) (liczba godzin))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz aresztowaæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(PlayerCache(giveplayer_id)(pArrest))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz zosta³ ju¿ aresztowany.\nU¿yj komendy /wypusc, by zwolniæ go z aresztu., OK, )
		return 1
	)
	if(time (= 0 || time ) 120)(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿na aresztowaæ na tak¹ iloœæ godzin., OK, )
		return 1
	)

	for (cell_id = 0 cell_id ( sizeof(PoliceCell) cell_id++)
	(
		if(IsPlayerInRangeOfPoint(playerid, 3.0, PoliceCell(cell_id)(pCellX), PoliceCell(cell_id)(pCellY), PoliceCell(cell_id)(pCellZ)))
		(
			if(GetPlayerVirtualWorld(playerid) == PoliceCell(cell_id)(pCellVW))
			(
				string(128)
				
				PlayerCache(giveplayer_id)(pArrestTime) = time * 60 * 60	// w sekundach
				PlayerCache(giveplayer_id)(pArrest) = cell_id + 1

				hrp_SetPlayerPos(giveplayer_id, PoliceCell(cell_id)(pCellX), PoliceCell(cell_id)(pCellY), PoliceCell(cell_id)(pCellZ))
				SetPlayerInterior(giveplayer_id, 0)
				SetPlayerVirtualWorld(giveplayer_id, PoliceCell(cell_id)(pCellVW))

				SavePlayerStats(giveplayer_id, SAVE_PLAYER_BASIC)

				SaveArrest(PlayerCache(playerid)(pUID), PlayerCache(giveplayer_id)(pUID), time)
				
				format(string, sizeof(string), ** Twój telefon, pager oraz sprzêt elektroniczny zosta³ schowany do depozytu. **)
				SendClientMessage(giveplayer_id, COLOR_DO, string)
				
				return 1
			)
		)
	)
 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê blisko celi., OK, )
	return 1
)

CMD:wypusc(playerid, params())
(
	if(!IsPlayerInGroupType(playerid, GROUP_DOC) && !IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /wypusc (ID gracza))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wypuœciæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(!PlayerCache(giveplayer_id)(pArrest))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie siedzi w areszcie., OK, )
		return 1
	)
	PlayerCache(giveplayer_id)(pArrest) = 0
  	PlayerCache(giveplayer_id)(pArrestTime) = 0
	PlayerCache(giveplayer_id)(pWorkingNow) = 0
	PlayerCache(giveplayer_id)(pWorkingPhase) = 0
	
	
	hrp_SetPlayerPos(giveplayer_id, 1800.5225,-1577.0044,14.0625) // Kordy przed wiezieniem
	SetPlayerInterior(giveplayer_id, 0)
	SetPlayerVirtualWorld(giveplayer_id, 0)
	SetCameraBehindPlayer(giveplayer_id)
	hrp_TogglePlayerControllable(giveplayer_id, 1)

	format(string, sizeof(string), Gracz %s zosta³ zwolniony z aresztu., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:opusc(playerid, params())
(
	if(!PlayerCache(playerid)(pArrest))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie nie siedzisz w areszcie., OK, )
		return 1
	)
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, 1823.0023, -1547.0116, 39.9212))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê przy bramie wyjœciowej z aresztu., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pArrestTime) ) 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz opuœciæ aresztu, czas odsiadki nie dobieg³ koñca.\nAby sprawdziæ pozosta³y wyrok u¿yj komendy /areszt., OK, )
		return 1	
	)
	
	PlayerCache(playerid)(pArrest) = 0
  	PlayerCache(playerid)(pArrestTime) = 0
	PlayerCache(playerid)(pWorkingNow) = 0
	PlayerCache(playerid)(pWorkingPhase) = 0
	
	hrp_SetPlayerPos(playerid, 1800.5225,-1577.0044,14.0625) // Kordy przed wiezieniem
	SetPlayerInterior(playerid, 0)
	SetPlayerVirtualWorld(playerid, 0)
	SetCameraBehindPlayer(playerid)
	hrp_TogglePlayerControllable(playerid, 1)

	string(128)
	format(string, sizeof(string), Zosta³eœ zwolniony z aresztu.)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:areszt(playerid, params())
(
	if(!PlayerCache(playerid)(pArrest))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie nie siedzisz w areszcie., OK, )
		return 1
	)
	
	string(256)

	if(PlayerCache(playerid)(pArrestTime) ) 3600)
	(
		format(string, sizeof(string), ~w~Wyrok:~w~ ~y~%02d godzin/y, floatround(PlayerCache(playerid)(pArrestTime) / 3600))
		GameTextForPlayer(playerid, string, 5000, 1)
		return 1
	)
	if(PlayerCache(playerid)(pArrestTime) ) 60)
	(
		format(string, sizeof(string), ~w~Wyrok:~w~ ~y~%02d minut, floatround(PlayerCache(playerid)(pArrestTime) / 60))
		GameTextForPlayer(playerid, string, 5000, 1)
		return 1
	)
	format(string, sizeof(string), ~w~Wyrok:~w~ ~y~%02d sekund, PlayerCache(playerid)(pArrestTime))
	GameTextForPlayer(playerid, string, 5000, 1)
	return 1
)

CMD:spawn(playerid, params())
(
	list_spawns(128)
	strcat(list_spawns, Cywil\n, sizeof(list_spawns))

	if(PlayerCache(playerid)(pHotel))
	(
		strcat(list_spawns, Hotel\n, sizeof(list_spawns))
	)

	if(PlayerCache(playerid)(pHouse))
	(
		strcat(list_spawns, Mieszkanie\n, sizeof(list_spawns))
	)

	if(PlayerCache(playerid)(pFamilyHouse))
	(
		strcat(list_spawns, Dom rodzinny\n, sizeof(list_spawns))
	)
	
	ShowPlayerDialog(playerid, D_SELECT_SPAWN, DIALOG_STYLE_LIST, Dostêpne miejsca spawnu:, list_spawns, Wybierz, Anuluj)
	return 1
)

CMD:dom(playerid, params())
(
	doorid = GetPlayerDoorID(playerid)
	if(doorid == INVALID_DOOR_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, przypisanym pod Ciebie., OK, )
		return 1
	)
	if(DoorData(doorid)(dOwnerType) != OWNER_PLAYER || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, przypisanym pod Ciebie., OK, )
		return 1
	)
	type(32), varchar(64), string(128)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /dom (zapros | wypros | spawn | kup))
		return 1
	)
	if(!strcmp(type, zapros, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /dom zapros (ID gracza))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaproœiæ siebie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
	 		return 1
		)
		PlayerCache(giveplayer_id)(pHouse) = DoorData(doorid)(dUID)
		SavePlayerStats(giveplayer_id, SAVE_PLAYER_BASIC)

		format(string, sizeof(string), %s zaprosi³ Ciê do swojego domu., PlayerName(playerid))
		SendClientMessage(giveplayer_id, COLOR_LIGHTBLUE, string)

		format(string, sizeof(string), Zaprosi³eœ gracza %s do swojego domu., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, wypros, true))
	(
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /dom wypros (ID gracza))
			return 1
		)
 		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaproœiæ siebie., OK, )
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
		if(!PlayerCache(playerid)(pHouse))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie masz ustanowionego spawnu w domu, u¿yj komendy /dom spawn., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pHouse) != DoorData(doorid)(dUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie jest zameldowany w Twoim domu., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pHouse) = 0
		SavePlayerStats(giveplayer_id, SAVE_PLAYER_BASIC)

		format(string, sizeof(string), %s wyprosi³ Ciê ze swojego domu., PlayerName(playerid))
		SendClientMessage(giveplayer_id, COLOR_LIGHTBLUE, string)

		format(string, sizeof(string), Wyprosi³eœ gracza %s ze swojego domu., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, spawn, true))
	(
		PlayerCache(playerid)(pHouse) = DoorData(doorid)(dUID)
		SavePlayerStats(playerid, SAVE_PLAYER_BASIC)

		format(string, sizeof(string), Ustali³eœ spawn w drzwiach %s (UID: %d).\nOd tej pory, spawnowaæ bêdziesz siê w nich., DoorData(doorid)(dName), DoorData(doorid)(dUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	return 1
)

CMD:kogut2(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FBI && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT && GroupData(group_id_fix)(gType) != GROUP_MEDICAL)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie jako kierowca, by móc u¿yæ tej komendy., OK, )
		return 1
	)
	vehid = GetPlayerVehicleID(playerid)
	if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie nale¿¹cym do grupy., OK, )
		return 1
	)

	if(GetVehicleModel(vehid) != 405 && GetVehicleModel(vehid) != 554 && GetVehicleModel(vehid) != 478 && GetVehicleModel(vehid) != 421 && GetVehicleModel(vehid) != 480 && GetVehicleModel(vehid) != 415 && GetVehicleModel(vehid) != 560 && GetVehicleModel(vehid) != 445)
	(
		GuiMsg(playerid, Musisz siedzieæ w oskryptowanym pojeŸdzie by u¿yæ tej komendy., 1)
		return 1
	)

	if(CarInfo(vehid)(cPoliceSiren) == INVALID_OBJECT_ID)
	(
		CarInfo(vehid)(cPoliceSiren) = CreateObject(18646, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 200.0)

		if(CarInfo(vehid)(cModel) == 554)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, -0.50, 0.85, 0.55, -2.30, 0.00, 4.00)
		)
		else if(CarInfo(vehid)(cModel) == 478)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, 0.0, -2.00, 0.5, -2.30, 0.00, 90.00)
		)
		else if(CarInfo(vehid)(cModel) == 480)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, 0.45, 0.35, 0.30, -2.30, 0.00, 4.00)
		)
		else if(CarInfo(vehid)(cModel) == 415)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, 0.00, 0.55, 0.20, -2.30, 0.00, 4.00)
		)
		else if(CarInfo(vehid)(cModel) == 560)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, 0.45, 0.75, 0.40, -2.30, 0.00, 4.00)
		)
		else if(CarInfo(vehid)(cModel) == 445)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, 0.45, 0.65, 0.30, -2.30, 0.00, 4.00)
		)
		else if(CarInfo(vehid)(cModel) == 421)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, 0.45, 0.85, 0.15, -2.30, 0.00, 4.00)
		)
		else if(CarInfo(vehid)(cModel) == 405)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, 0.5, 0.55, 0.2, 0.0, 0.0, 0.0)
		)

		TextDrawSetString(Text:TextDrawMainInfo(playerid), Syrena ~b~policyjna ~w~zostala ~g~wyjeta~w~.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		PlayerCache(playerid)(pShowInfoText) = 5
	)
	else
	(
		DestroyObject(CarInfo(vehid)(cPoliceSiren))

   		TextDrawSetString(Text:TextDrawMainInfo(playerid), Syrena ~b~policyjna ~w~zostala ~r~schowana~w~.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		PlayerCache(playerid)(pShowInfoText) = 5
		CarInfo(vehid)(cPoliceSiren) = INVALID_OBJECT_ID
	)

	return 1
)

CMD:kogut(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FBI && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT && GroupData(group_id_fix)(gType) != GROUP_MEDICAL)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie jako kierowca, by móc u¿yæ tej komendy., OK, )
		return 1
	)
	vehid = GetPlayerVehicleID(playerid)
	if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w pojeŸdzie nale¿¹cym do grupy., OK, )
		return 1
	)
	if(CarInfo(vehid)(cModel) != 415 && CarInfo(vehid)(cModel) != 544 && CarInfo(vehid)(cModel) != 560 && CarInfo(vehid)(cModel) != 426 && CarInfo(vehid)(cModel) != 482 && CarInfo(vehid)(cModel) != 525)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz umieœciæ syreny na tym pojeŸdzie., OK, )
		return 1
	)
	if(CarInfo(vehid)(cPoliceSiren) == INVALID_OBJECT_ID)
	(
		CarInfo(vehid)(cPoliceSiren) = CreateObject(18646, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 200.0)

		if(CarInfo(vehid)(cModel) == 560 || CarInfo(vehid)(cModel) == 426)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, -0.34, -0.20, 0.90, -2.00, 0.00, 4.00)
		)
		else if(CarInfo(vehid)(cModel) == 482)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, -0.34, -0.20, 1.10, -2.00, 0.00, 4.00)
		)
		else if(CarInfo(vehid)(cModel) == 415)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, -0.34, -0.17, 0.64, -2.00, 0.00, 4.00)
		)
		else if(CarInfo(vehid)(cModel) == 525)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, 0.0, 0, 1.4, 0.0, 0.0, 0.0)
		)
		else if(CarInfo(vehid)(cModel) == 544)
		(
			AttachObjectToVehicle(CarInfo(vehid)(cPoliceSiren), vehid, 0.0, 2.3, 1.50, 0.0, 0.0, 0.0)
		)

		TextDrawSetString(Text:TextDrawMainInfo(playerid), Syrena ~b~policyjna ~w~zostala ~g~wyjeta~w~.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		PlayerCache(playerid)(pShowInfoText) = 5
	)
	else
	(
		DestroyObject(CarInfo(vehid)(cPoliceSiren))

   		TextDrawSetString(Text:TextDrawMainInfo(playerid), Syrena ~b~policyjna ~w~zostala ~r~schowana~w~.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		PlayerCache(playerid)(pShowInfoText) = 5
		CarInfo(vehid)(cPoliceSiren) = INVALID_OBJECT_ID
	)
	return 1
)

CMD:syrena(playerid, params()) return cmd_kogut(playerid, params)

CMD:yo(playerid, params())
(
	giveplayer_id, type
	if(sscanf(params, ud, giveplayer_id, type))
	(
		hrp_Tip(playerid, /yo (ID gracza) (1-6))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz przywitaæ siê ze sob¹., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(type ( 1 || type ) 6)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy typ powitania (1-6)., OK, )
		return 1
	)
	OnPlayerSendOffer(playerid, giveplayer_id, OFFER_WELCOME, Powitanie, type, 0)
	return 1
)

/*CMD:sex(playerid, params())
(
	giveplayer_id, type(16)
	if(sscanf(params, us(16), giveplayer_id, type))
	(
		hrp_Tip(playerid, /sex (ID gracza) (misjonarz, oral, anal, doggy))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, ZnajdŸ j¹kieœ zaciszne miejsce je¿eli chcesz to robiæ samemu. ZnajdŸ dziewczynê/bielaxa! (.walekonia), OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(!strcmp(type, misjonarz, true))
	(
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_SEX, Sex na misjonarza, SEX_NORMAL, 0)
		return 1
	)
	if(!strcmp(type, oral, true))
	(
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_SEX, Sex oralny, SEX_ORAL, 0)
		return 1
	)
	if(!strcmp(type, anal, true))
	(
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_SEX, Sex analny, SEX_ANAL, 0)
		return 1
	)
	if(!strcmp(type, doggy, true))
	(
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_SEX, Sex na pieska, SEX_DOGGY, 0)
		return 1
	)

	hrp_Tip(playerid, /sex (ID gracza) (misjonarz, oral, anal, doggy))
	return 1
)
*/

CMD:sex(playerid, params())
(
	SendClientMessage(playerid, 0xFFAAAA, Ups.. Coœ posz³o nie tak, u¿yj musztardy by naprawiæ problem.)
	return 1
)

CMD:kiss(playerid, params())
(
	giveplayer_id, type
	if(sscanf(params, ud, giveplayer_id, type))
	(
		hrp_Tip(playerid, /kiss (ID gracza) (1-3))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz poca³owaæ siê ze sob¹., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(type ( 1 || type ) 3)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy typ poca³unku (1-3)., OK, )
		return 1
	)
	OnPlayerSendOffer(playerid, giveplayer_id, OFFER_WELCOME, Pocalunek, type + 6, 0)
	return 1
)

CMD:wyscig(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_RACERS && !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_LEADER))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Tej komendy mog¹ u¿yæ tylko liderzy organizacji œcigantów., OK, )
		return 1
	)
	type(32), varchar(32), string(256)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /wyscig (stworz | zapros | wypros | zakoncz))
		return 1
	)
	if(!strcmp(type, stworz, true))
	(
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie jako kierowca, aby móc stworzyæ wyœcig., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pRacePhase))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie jesteœ w trakcie tworzenia jakiegoœ wyœcigu., OK, )
			return 1
		)

		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pRacePhase))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie trwa jakiœ inny wyœcig., OK, )
					return 1
				)
			)
		)
		
		/*format(string, sizeof(string), Rozpoczales ~r~proces ~w~tworzenia wyscigu, zwroc uwage na ~g~legende~w~:~n~~n~~y~~k~~VEHICLE_FIREWEN~ ~w~- stawia checkpoint~n~~y~~k~~VEHICLE_FIREWEAPON_ALT~ ~w~- ustala linie mety~n~~n~Checkpointy: ~y~%d/%d, PlayerCache(playerid)(pRacePoint), MAX_RACE_CP)
		TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))*/
		
		sendClientPoop(playerid, » Rozpocz¹³eœ proces tworzenia wyœcigu, poni¿ej klawiszologia.)
		sendClientPoop(playerid, » ~k~~VEHICLE_FIREWEAPON~  by ustawiæ checkpoint i ~k~~VEHICLE_FIREWEAPON_ALT~ by ustawiæ liniê mety.)
		
		format(string, sizeof(string), » Checkpointy: %d/%d, PlayerCache(playerid)(pRacePoint), MAX_RACE_CP)
		sendClientPoop(playerid, string)

		PlayerCache(playerid)(pRacePhase) = 1
		PlayerCache(playerid)(pRacePoint) = 0

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Rozpoczêto proces tworzenia wyœcigu., OK, )
		return 1
	)
	if(!strcmp(type, zapros, true))
	(
		if(PlayerCache(playerid)(pRacePhase) != 2)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz teraz zapraszaæ rywali., OK, )
			return 1
		)
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /wyscig zapros (ID gracza))
			return 1
		)
  		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaprosiæ do wyœcigu siebie., OK, )
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
		if(!PlayerToPlayer(10.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(PlayerCache(giveplayer_id)(pRacePhase))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ju¿ bierze udzia³ w jakimœ wyœcigu., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pRacePhase) = 2
		PlayerCache(giveplayer_id)(pRacePoint) = 0

		PlayerCache(giveplayer_id)(pRaceCheckpoints) = PlayerCache(playerid)(pRaceCheckpoints)

		format(string, sizeof(string), Gracz %s zosta³ zaproszony do wyœcigu., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Gracz %s zaprosi³ Ciê do wyœcigu., PlayerName(playerid))
		SendClientMessage(giveplayer_id, COLOR_INFO, string)
		return 1
	)
	if(!strcmp(type, wypros, true))
	(
 		if(PlayerCache(playerid)(pRacePhase) != 2)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz teraz wypraszaæ rywali., OK, )
			return 1
		)
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /wyscig wypros (ID gracza))
			return 1
		)
  		if(giveplayer_id == playerid)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaprosiæ do wyœcigu siebie., OK, )
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
		if(!PlayerToPlayer(10.0, playerid, giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
		if(!PlayerCache(giveplayer_id)(pRacePhase))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie bierze udzia³u w ¿adnym wyœcigu., OK, )
			return 1
		)
		PlayerCache(giveplayer_id)(pRacePhase) = 0
		PlayerCache(giveplayer_id)(pRacePoint) = 0

		PlayerCache(giveplayer_id)(pRaceCheckpoints) = 0

		format(string, sizeof(string), Gracz %s zosta³ wyproszony z wyœcigu., PlayerName(giveplayer_id))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Gracz %s wyprosi³ Ciê z wyœcigu., PlayerName(playerid))
		SendClientMessage(giveplayer_id, COLOR_INFO, string)
		return 1
	)
	if(!strcmp(type, start, true))
	(
		if(PlayerCache(playerid)(pRacePhase) != 2)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz teraz rozpocz¹æ wyœcigu., OK, )
			return 1
		)

		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(PlayerCache(i)(pRacePhase) == 2)
				(
					PlayerCache(i)(pRacePhase) = 3
					PlayerCache(i)(pRacePoint) = 0

					GameTextForPlayer(i, ~w~Wyscig ~g~rozpoczety!, 5000, 3)
 					SetPlayerRaceCheckpoint(i, 0, RaceCheckpoint(0)(0), RaceCheckpoint(0)(1), RaceCheckpoint(0)(2), RaceCheckpoint(1)(0), RaceCheckpoint(1)(1), RaceCheckpoint(1)(2), 10.0)
				)
			)
		)
		return 1
	)
	return 1
)

CMD:hak(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w holowniku., OK, )
  		return 1
  	)
	vehid = GetPlayerVehicleID(playerid)
	if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wystapi³ b³¹d, Pojazd musi byæ przypisany pod grupê., OK, )
	 	return 1
	)
	if(GetVehicleModel(vehid) != 525)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w holowniku., OK, )
		return 1
	)
	Float:vPosX, Float:vPosY, Float:vPosZ

	foreach(Vehicles, carid)
	(
		if(carid != vehid)
		(
			if(CarInfo(carid)(cUID))
			(
				GetVehiclePos(carid, vPosX, vPosY, vPosZ)
				if(IsPlayerInRangeOfPoint(playerid, 10.0, vPosX, vPosY, vPosZ))
				(
					AttachTrailerToVehicle(carid, vehid)
					CarInfo(vehid)(cTowedVeh) = carid

					TextDrawSetString(Text:TextDrawMainInfo(playerid), Pojazd zostal ~r~podczepiony~w~, aby go odczepic wcisnij klawisz ~g~~k~~VEHICLE_FIREWEAPON_ALT~~w~.)
					TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

					PlayerCache(playerid)(pShowInfoText) = 5
					return 1
				)
			)
		)
	)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnego pojazdu w pobli¿u., OK, )
	return 1
)

CMD:wejdz(playerid, params())
(
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
 	(
 		return 1
 	)
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
		)
  	)
	return 1
)

CMD:wyjdz(playerid, params())
(
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
 	(
 		return 1
 	)
  	if(PlayerCache(playerid)(pDoorFreeze))
   	(
		return 1
	)
	foreach(Doors, doorid)
	(
		if(DoorData(doorid)(dUID))
	 	(
	  		if(IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ)) && GetPlayerVirtualWorld(playerid) == DoorData(doorid)(dExitVW))
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
	return 1
)

CMD:getranditem(playerid, params())
(
	itemid = Iter_Random(Items)
	SendClientFormatMessage(playerid, COLOR_YELLOW, Wylosowano przedmiot %s (UID: %d)., ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID))
	return 1
)

CMD:cb(playerid, params())
(
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby korzystaæ z CB radio musisz siedzieæ w pojeŸdzie., OK, )
		return 1
	)
	vehid = GetPlayerVehicleID(playerid)
	if(!(CarInfo(vehid)(cAccess) & VEH_ACCESS_RADIO))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W tym pojeŸdzie nie ma zamontowanego CB radio., OK, )
		return 1
	)
	if(!CarInfo(vehid)(cRadioCanal))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie ustawi³eœ ¿adnego kana³u!, OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /cb (Tekst))
		return 1
	)
	string(256), radio_canal = CarInfo(vehid)(cRadioCanal)
	params(0) = chrtoupper(params(0))

	format(string, sizeof(string), (K:%d) %s: %s, radio_canal, PlayerName(playerid), params)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(IsPlayerInAnyVehicle(i))
			(
				vehid = GetPlayerVehicleID(i)
				if(CarInfo(vehid)(cAccess) & VEH_ACCESS_RADIO)
				(
					if(CarInfo(vehid)(cRadioCanal) == radio_canal)
					(
						SendClientMessage(i, COLOR_CB_RADIO, string)
					)
				)
			)
		)
	)
	return 1
)

CMD:gps(playerid, params())
(
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
  	(
  		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie jako kierowca, by móc w³¹czyæ GPS., OK, )
		return 1
  	)
	vehid = GetPlayerVehicleID(playerid)
	if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie nale¿¹cym do grupy., OK, )
		return 1
	)
	if(!CarInfo(vehid)(cGPS))
	(
		CarInfo(vehid)(cGPS) = true

		TextDrawSetString(Text:TextDrawMainInfo(playerid), Nadajnik ~b~GPS ~w~zostal ~g~uruchomiony~w~.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		PlayerCache(playerid)(pShowInfoText) = 5
	)
	else
	(
		CarInfo(vehid)(cGPS) = false

   		TextDrawSetString(Text:TextDrawMainInfo(playerid), Nadajnik ~b~GPS ~w~zostal ~r~wylaczony~w~.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		PlayerCache(playerid)(pShowInfoText) = 5

		// Ukryj ikonki
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
	return 1
)

CMD:oc(playerid, params())
(
	modelid, world = GetPlayerVirtualWorld(playerid)
	if(sscanf(params, d, modelid))
	(
		hrp_Tip(playerid, /oc (Model))
		return 1
	)
	if(PlayerCache(playerid)(pMoveObject) != INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz tworzyæ nowych obiektów podczas edycji., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAdmin) != 1 && world != 0 && Streamer_CountVisibleItems(playerid, STREAMER_TYPE_OBJECT) ) 800)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W tym pomieszczeniu znajduje siê ju¿ 600 obiektów.\nUsuñ jeden z istniej¹cych obiektów aby dodaæ nowy., OK, )
		return 1
	)
	if((modelid )= 384 && modelid (= 393) || modelid == 1573)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Te obiekty powoduja crashe., OK, )
		return 1
	)
	/*
	if(world == 0)
	(
		if(PlayerCache(playerid)(pAdmin) != 1)
		(
			gangzone_id = GetCurrentPlayerGangZone(playerid)
			if(gangzone_id == -1)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby móc stworzyæ obiekt w œwiecie 0, musisz znajdowaæ siê w strefie, do której masz prawa., OK, )
				return 1
			)
			group_uid = GangZoneInfo(gangzone_id)(gOwner)
			group_id_fix = GetGroupID(group_uid)
			if(GroupData(group_id_fix)(gUID))
			(
				if(IsPlayerPermissedGroup(playerid, group_uid, PERM_LEADER))
				(
					count = 0
					for(object_id = 0 object_id (= MAX_OBJECTS object_id++)
					(
						if(GroupData(group_id_fix)(gType) == GROUP_CRIMINAL || GroupData(group_id_fix)(gType) == GROUP_MAFIA || GroupData(group_id_fix)(gType) == GROUP_CARTEL)
							if(count ) 200)
								break
						else
							if(count ) 15)
								break

						if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID) == 0)
						(
							Float:x, Float:y, Float:z
							GetDynamicObjectPos(object_id, x, y, z)
							if(x )= GangZoneInfo(gangzone_id)(gMinX) && x (= GangZoneInfo(gangzone_id)(gMaxX) && y )= GangZoneInfo(gangzone_id)(gMinY) && y (= GangZoneInfo(gangzone_id)(gMaxY))
							(
								count++
							)
						)
					)
					if(GroupData(group_id_fix)(gType) == GROUP_CRIMINAL || GroupData(group_id_fix)(gType) == GROUP_MAFIA || GroupData(group_id_fix)(gType) == GROUP_CARTEL)
					(
						if(count ) 200)
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Dla tej grupy obowi¹zuje maximum 200 obiektów., OK, )
							return 1
						)
					)
					else
					(
						if(count ) 15)
						(
							ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Dla tej grupy obowi¹zuje maximum 15 obiektów., OK, )
							return 1
						)
					)
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby móc stworzyæ obiekt w œwiecie 0, musisz znajdowaæ siê w strefie, do której masz prawa., OK, )
					return 1
				)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby móc stworzyæ obiekt w œwiecie 0, musisz znajdowaæ siê w strefie, do której masz prawa., OK, )
				return 1
			)
		)
	)
	else
	(	*/
		if(PlayerCache(playerid)(pAdmin) ) -3 && PlayerCache(playerid)(pAdmin) ( 1)
		(
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby móc stworzyæ obiekt, musisz znajdowaæ siê w budynku., OK, )
				return 1
			)
			if(DoorData(doorid)(dExitVW) == 0)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby móc stworzyæ obiekt, musisz znajdowaæ siê w budynku., OK, )
				return 1
			)
			if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten budynek nie nale¿y do Ciebie., OK, )
				return 1
			)
			if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
			(
				if(DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten budynek nie nale¿y do Ciebie., OK, )
					return 1
				)
			)
			if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
			(
				if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten budynek nie nale¿y do Ciebie., OK, )
					return 1
				)
			)
		)
	//)

	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		if(GetPlayerVirtualWorld(playerid) ) 0)
		(
			doorid = GetPlayerDoorID(playerid)
			if(DoorData(doorid)(dBlocked))
			(
				GuiMsg(playerid,Te drzwi s¹ maj¹ na³o¿on¹ blokadê tworzenia obiektów.,1)
				return 1
			)

			if(DoorData(doorid)(dLimit) (= GetDoorObjectsAmount(doorid))
			(
				GuiMsg(playerid,Wyczerpa³es limit mo¿liwych obiektów w tych drzwiach.,1)
				return 1
			)
		)
	)



	if(modelid (= 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³owy model obiektu., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		if((modelid == OBJECT_ATM || modelid == OBJECT_FUELING || modelid == OBJECT_BUSSTOP || modelid == OBJECT_TELEPHONE || modelid == OBJECT_TELEPHONE_ALT || modelid == OBJECT_AIR_PUMP || modelid == OBJECT_HOTDOG) || modelid == OBJECT_COOK)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Model tego obiektu jest zarezerwowany dla wewnêtrznych systemów., OK, )
			return 1
		)
	)
	Float:PosX, Float:PosY, Float:PosZ, string(256),
		interior_id = GetPlayerInterior(playerid), world_id = GetPlayerVirtualWorld(playerid)

	GetPlayerPos(playerid, PosX, PosY, PosZ)
	GetXYInFrontOfPlayer(playerid, PosX, PosY, 2.0)

	object_id = hrp_AddObject(modelid, PosX, PosY, PosZ, 0.0, 0.0, 0.0, interior_id, world_id)
	Streamer_Update(playerid)

	format(string, sizeof(string), Obiekt zosta³ stworzony pomyœlnie, pownien pojawiæ siê tu¿ przed Tob¹.\nAby zarz¹dzaæ stworzonym obiektem u¿yj komendy /osel w pobli¿u niego.\n\nModel obiektu: %d\nIdentyfikator: %d, modelid, object_id)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:osel(playerid, params())
(
	if(PlayerCache(playerid)(pMoveObject) != INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie edytujesz ju¿ jakiœ obiekt., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(group_id_fix == INVALID_GROUP_ID) group_id_fix = 0
	if((PlayerCache(playerid)(pAdmin) ) -3 && PlayerCache(playerid)(pAdmin) ( 1) && GroupData(group_id_fix)(gType) != GROUP_FIREDEPT)
	(
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Edytowaæ obiekty mo¿esz tylko bêd¹c w budynku, którego w³aœcicielem jesteœ., OK, )
	   		return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Edytowaæ obiekty mo¿esz tylko bêd¹c w budynku, którego w³aœcicielem jesteœ., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
		(
	 		if(DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
	   		(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Edytowaæ obiekty mo¿esz tylko bêd¹c w budynku, którego w³aœcicielem jesteœ., OK, )
	   			return 1
			)
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Edytowaæ obiekty mo¿esz tylko bêd¹c w budynku, którego w³aœcicielem jesteœ., OK, )
				return 1
			)
		)
	)

	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		if(GetPlayerVirtualWorld(playerid) ) 0)
		(
			doorid = GetPlayerDoorID(playerid)
			if(DoorData(doorid)(dBlocked))
			(
				GuiMsg(playerid,Te drzwi posiadaj¹ aktywn¹ blokadê edycji obiektów.,1)
				return 1
			)
		)
	)

	modelid
	if(!sscanf(params, d, modelid))
	(
		if(PlayerCache(playerid)(pOselLimit) ) 0)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wyszukiwanie obiektów poprzez model zabiera trochê czasu.\nMusisz poczekaæ 10 sekund od ostatniego u¿ycia.\nPamiêtaj, ¿e standardowe wybieranie obiektów dalej dzia³a., OK, )
			return 1
		)

		closestID, Float:closest_distance, Float:x, Float:y, Float:z

		for (object_id = 0 object_id (= MAX_OBJECTS object_id++)
		(
			if(Streamer_IsItemVisible(playerid, STREAMER_TYPE_OBJECT, object_id))
			(
				if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_MODEL_ID) == modelid)
				(
					GetDynamicObjectPos(object_id, x, y, z)
					Float:distance = GetPlayerDistanceFromPoint(playerid, x, y, z)

					if(distance ( closest_distance || closest_distance == 0)
					(
						closestID = object_id
						closest_distance = distance
					)
				)
			)
		)

		if(IsValidDynamicObject(closestID))
		(
			// Simii
			//EditDynamicObject(playerid, closestID)
			modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, closestID, E_STREAMER_MODEL_ID)
			Float:fX, Float:fY, Float:fZ

			GetDynamicObjectPos(closestID, fX, fY, fZ)

			fakeOnPlayerSelectObject(playerid, closestID, modelid, fX, fY, fZ)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych obiektów o tym modelu w pobli¿u., OK, )
			return 1
		)

		PlayerCache(playerid)(pOselLimit) = 2
	)
	else
	(
		SelectObject(playerid)
		TextDrawSetString(Text:TextDrawMainInfo(playerid), Wybierz ~b~obiekt ~w~ktory pragniesz edytowac (kliknij na niego ~r~LPM~w~).)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
	)

	return 1
)

CMD:odel(playerid, params())
(
	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject)
	CancelEdit(playerid)

	object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)
	ClearMaterialsForObject(object_uid)

	hrp_DeleteObject(object_id)
	PlayerCache(playerid)(pMoveObject) = INVALID_OBJECT_ID

	TextDrawHideForPlayer(playerid, Text:TextDrawEditorBack)
	TextDrawHideForPlayer(playerid, Text:TextDrawEditorTitle(playerid))

	TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))

	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Obiekt zosta³ ca³kowicie usuniêty., OK, )
	return 1
)

CMD:ogate(playerid, params())
(
	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject),
		Float:GateX, Float:GateY, Float:GateZ,
		Float:GateRotX, Float:GateRotY, Float:GateRotZ,
		distance = 6
	
	if(GetPlayerVirtualWorld(playerid) != 0)
	(
		if(sscanf(params,d,distance))
		(
			hrp_Tip(playerid,/ogate (dystans (1-6)))
			return 1
		)
		if(distance ) 6 || distance ( 1)
		(
			hrp_Tip(playerid,/ogate (dystans (1-6)))
			return 1
		)
	)
	
	object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)

	GetDynamicObjectPos(object_id, GateX, GateY, GateZ)
	GetDynamicObjectRot(object_id, GateRotX, GateRotY, GateRotZ)

	mysql_query_format(UPDATE hrp_objects SET object_gatex = %f, object_gatey = %f, object_gatez = %f, object_gaterotx = %f, object_gateroty = %f, object_gaterotz = %f, object_gate = 1 , object_dist = %d WHERE object_uid = %d LIMIT 1, GateX, GateY, GateZ, GateRotX, GateRotY, GateRotZ, distance, object_uid)

 	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Ustalono pozycjê bramy otwartej.\nWróæ teraz na pozycjê bramy zamkniêtej i zapisz jej pozycjê., OK, )
	return 1
)

CMD:ocopy(playerid, params())
(
	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	/*if(Streamer_CountVisibleItems(playerid, STREAMER_TYPE_OBJECT) ) 600)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W tym pomieszczeniu znajduje siê ju¿ 400 obiektów.\nUsuñ jeden z istniej¹cych obiektów aby dodaæ nowy., OK, )
		return 1
	)*/
	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		if(GetPlayerVirtualWorld(playerid) ) 0)
		(
			doorid = GetPlayerDoorID(playerid)
			if(DoorData(doorid)(dLimit) (= GetDoorObjectsAmount(doorid))
			(
				GuiMsg(playerid,Wyczerpa³es limit mo¿liwych obiektów w tych drzwiach.,1)
				return 1
			)
		)
	)
	object_id = PlayerCache(playerid)(pMoveObject), interior_id = GetPlayerInterior(playerid), world_id = GetPlayerVirtualWorld(playerid), model = GetObjectModel(object_id), string(256),
		Float:PosX, Float:PosY, Float:PosZ,
		Float:RotX, Float:RotY, Float:RotZ

	if(model == OBJECT_COOK)
	(
		GuiMsg(playerid,Nie mo¿na kopiowaæ obiektu kuchenki!,1)
		return 1
	)
		
	GetDynamicObjectPos(object_id, PosX, PosY, PosZ)
	GetDynamicObjectRot(object_id, RotX, RotY, RotZ)

	new_object_id = hrp_AddObject(model, PosX, PosY, PosZ, RotX, RotY, RotZ, interior_id, world_id)
	Streamer_Update(playerid)

	format(string, sizeof(string), Obiekt zosta³ skopiowany pomyœlnie i pownien pojawiæ siê w miejscu aktualnie edytowanego.\nAby zarz¹dzaæ stworzonym obiektem u¿yj komendy /osel w pobli¿u niego.\n\nModel obiektu: %d\nIdentyfikator: %d, model, new_object_id)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:okopia(playerid, params()) return cmd_ocopy(playerid, params)
CMD:okopiuj(playerid, params()) return cmd_ocopy(playerid, params)

CMD:px(playerid, params())
(
	Float:oPosX
	if(sscanf(params,f,oPosX))
	(
		hrp_Tip(playerid,/px (pozycja))
		return 1
	)

	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject)

	Float:Pos(3)
	CancelEdit(playerid)
	GetDynamicObjectPos(object_id, Pos(0), Pos(1), Pos(2))
	SetDynamicObjectPos(object_id, oPosX, Pos(1), Pos(2))

	hrp_SaveObject(object_id)
	PlayerCache(playerid)(pMoveObject) = INVALID_OBJECT_ID


	return 1
)

CMD:py(playerid, params())
(
	Float:oPosY
	if(sscanf(params,f,oPosY))
	(
		hrp_Tip(playerid,/py (pozycja))
		return 1
	)

	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject)

	Float:Pos(3)
	CancelEdit(playerid)
	GetDynamicObjectPos(object_id, Pos(0), Pos(1), Pos(2))
	SetDynamicObjectPos(object_id, Pos(0), oPosY, Pos(2))

	hrp_SaveObject(object_id)
	PlayerCache(playerid)(pMoveObject) = INVALID_OBJECT_ID


	return 1
)

CMD:pz(playerid, params())
(
	Float:oPosZ
	if(sscanf(params,f,oPosZ))
	(
		hrp_Tip(playerid,/pz (pozycja))
		return 1
	)

	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject)

	Float:Pos(3)
	CancelEdit(playerid)
	GetDynamicObjectPos(object_id, Pos(0), Pos(1), Pos(2))
	SetDynamicObjectPos(object_id, Pos(0), Pos(1), oPosZ)

	hrp_SaveObject(object_id)
	PlayerCache(playerid)(pMoveObject) = INVALID_OBJECT_ID


	return 1
)

CMD:rx(playerid, params())
(
	Float:oRotX
	if(sscanf(params,f,oRotX))
	(
		hrp_Tip(playerid,/rx (rotacja))
		return 1
	)

	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject)

	Float:Rot(3)
	CancelEdit(playerid)
	GetDynamicObjectRot(object_id,Rot(0),Rot(1),Rot(2))
	SetDynamicObjectRot(object_id,oRotX,Rot(1),Rot(2))

	hrp_SaveObject(object_id)
	PlayerCache(playerid)(pMoveObject) = INVALID_OBJECT_ID


	return 1
)

CMD:ry(playerid, params())
(
	Float:oRotY
	if(sscanf(params,f,oRotY))
	(
		hrp_Tip(playerid,/ry (rotacja))
		return 1
	)

	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject)

	Float:Rot(3)
	CancelEdit(playerid)
	GetDynamicObjectRot(object_id,Rot(0),Rot(1),Rot(2))
	SetDynamicObjectRot(object_id,Rot(0),oRotY,Rot(2))

	hrp_SaveObject(object_id)
	PlayerCache(playerid)(pMoveObject) = INVALID_OBJECT_ID


	return 1
)

CMD:rz(playerid, params())
(
	Float:oRotZ
	if(sscanf(params,f,oRotZ))
	(
		hrp_Tip(playerid,/rz (rotacja))
		return 1
	)

	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)
	object_id = PlayerCache(playerid)(pMoveObject)

	Float:Rot(3)
	CancelEdit(playerid)
	GetDynamicObjectRot(object_id,Rot(0),Rot(1),Rot(2))
	SetDynamicObjectRot(object_id,Rot(0),Rot(1),oRotZ)

	hrp_SaveObject(object_id)
	PlayerCache(playerid)(pMoveObject) = INVALID_OBJECT_ID


	return 1
)

CMD:brama(playerid, params())
(
	virtual_world = GetPlayerVirtualWorld(playerid),
		interior_id = GetPlayerInterior(playerid)

	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		if(virtual_world != 0)
		(
			doorid = GetPlayerDoorID(playerid)
			if(doorid == INVALID_DOOR_ID)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz do tego odpowiednich uprawnieñ., OK, )
				return 1
			)
			
			if(virtual_world == PrisonWorld)
			(
				if(!IsPlayerInGroupType(playerid, GROUP_POLICE) && !IsPlayerInGroupType(playerid, GROUP_FBI) && !IsPlayerInGroupType(playerid, GROUP_DOC))
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie nale¿ysz do s³u¿b porz¹dkowych lub wiêziennych., OK, )
					return 1
				)
			)
			else
			(
				if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz do tego odpowiednich uprawnieñ., OK, )
					return 1
				)
				if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
				(
					if(DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID) && PlayerCache(playerid)(pHouse) != DoorData(doorid)(dUID))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz do tego odpowiednich uprawnieñ., OK, )
						return 1
					)
				)
				if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
				(
					if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_GATE))
					(
						ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz do tego odpowiednich uprawnieñ., OK, )
						return 1
					)
				)
			)
		)
	)
	data(256)

	object_uid, object_id, distance
	//distance = (virtual_world == 0)? 6:3
	distance = 6

	Float:PosX, Float:PosY, Float:PosZ, object_owner,
		Float:object_posx, Float:object_posy, Float:object_posz,
		Float:object_rotx, Float:object_roty, Float:object_rotz,
		Float:object_gatex, Float:object_gatey, Float:object_gatez,
		Float:object_gaterotx, Float:object_gateroty, Float:object_gaterotz,
		object_dist,
		Float:ObjPosX, Float:ObjPosY, Float:ObjPosZ

	GetPlayerPos(playerid, PosX, PosY, PosZ)

	string(2048)
	format(string, sizeof(string), SELECT object_uid, object_posx, object_posy, object_posz, object_rotx, object_roty, object_rotz, object_gatex, object_gatey, object_gatez, object_gaterotx, object_gateroty, object_gaterotz, object_dist, object_owner)
	format(string, sizeof(string), %s FROM hrp_objects WHERE ((object_posx ( %f + %d AND object_posx ) %f - %d AND object_posy ( %f + %d AND object_posy ) %f - %d AND object_posz ( %f + %d AND object_posz ) %f - %d), string, PosX, distance, PosX, distance, PosY, distance, PosY, distance, PosZ, distance, PosZ, distance)
	format(string, sizeof(string), %s OR (object_gatex ( %f + %d AND object_gatex ) %f - %d AND object_gatey ( %f + %d AND object_gatey ) %f - %d AND object_gatez ( %f + %d AND object_gatez ) %f - %d)) AND object_world = %d AND object_interior = %d AND object_gate = 1 LIMIT 5, string, PosX, distance, PosX, distance, PosY, distance, PosY, distance, PosZ, distance, PosZ, distance, virtual_world, interior_id)
	mysql_query(string)

	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)dffffffffffffdd, object_uid, object_posx, object_posy, object_posz, object_rotx, object_roty, object_rotz, object_gatex, object_gatey, object_gatez, object_gaterotx, object_gateroty, object_gaterotz, object_dist, object_owner)

			object_id = GetObjectID(object_uid)
			GetDynamicObjectPos(object_id, ObjPosX, ObjPosY, ObjPosZ)
			
			if(floatround(GetPlayerDistanceFromPoint(playerid, object_posx, object_posy, object_posz)) (= object_dist)
			(
				flag = false
				if(virtual_world == 0)
				(
					if(object_owner ) 0)
					(
						if(IsPlayerPermissedGroup(playerid, object_owner, PERM_GATE))
						(
							flag = true
						)
						
						// Bramy na gracza
						if(object_owner == PlayerCache(playerid)(pUID))
						(
							flag = true
						)
					)
				)
				else
				(
					flag = true
				)
				if(PlayerCache(playerid)(pAdmin) == 1)
				(
					flag = true
				)

				if(flag)
				(
					if(!floatcmp(ObjPosX, object_posx) && !floatcmp(ObjPosY, object_posy) && !floatcmp(ObjPosZ, object_posz))
					(
						MoveDynamicObject(object_id, object_gatex, object_gatey, object_gatez, 4.0, object_gaterotx, object_gateroty, object_gaterotz)
						GameTextForPlayer(playerid, ~w~Brama ~g~otwarta, 4000, 6)
					)
					else
					(
						MoveDynamicObject(object_id, object_posx, object_posy, object_posz, 4.0, object_rotx, object_roty, object_rotz)
						GameTextForPlayer(playerid, ~w~Brama ~r~zamknieta, 4000, 6)
					)
				)
			)
		)
	)
	else
	(
		if(!strcmp(params, skrypt, true))
		(
			// nic nie zwracaj bo skryptem wywo³ane
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych bram w pobli¿u., OK, )
		)
	)
	mysql_free_result()
	return 1
)

CMD:ec(playerid, params())
(
	Float:distance, desc(128)
	if(sscanf(params, fs(128), distance, desc))
	(
		hrp_Tip(playerid, /ec (Odleg³oœæ) (Treœæ))
		return 1
	)
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby móc stworzyæ obiekt, musisz znajdowaæ siê w budynku., OK, )
	   		return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten budynek nie nale¿y do Ciebie., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
		(
	 		if(DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
	   		(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten budynek nie nale¿y do Ciebie., OK, )
	   			return 1
			)
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten budynek nie nale¿y do Ciebie., OK, )
				return 1
			)
		)
	)
	Float:PosX, Float:PosY, Float:PosZ,
		interior_id = GetPlayerInterior(playerid), world_id = GetPlayerVirtualWorld(playerid)

	GetPlayerPos(playerid, PosX, PosY, PosZ)
	GetXYInFrontOfPlayer(playerid, PosX, PosY, 2.0)

	Add3DTextLabel(LabelWrap(desc), COLOR_WHITE, PosX, PosY, PosZ, distance, world_id, interior_id)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Etykieta 3D zosta³a pomyœlnie stworzona, powinna pojawiæ siê tu¿ przed Tob¹.\nAby zarz¹dzaæ stworzon¹ etykiet¹ u¿yj komendy /esel w pobli¿u jej., OK, )
	return 1
)

CMD:esel(playerid, params())
(
	if(PlayerCache(playerid)(pMove3DText) != INVALID_3DTEXT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie edytujesz ju¿ jak¹œ etykietê., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Edytowaæ etykiety mo¿esz tylko bêd¹c w budynku, którego w³aœcicielem jesteœ., OK, )
	   		return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_NONE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Edytowaæ etykiety mo¿esz tylko bêd¹c w budynku, którego w³aœcicielem jesteœ., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
		(
	 		if(DoorData(doorid)(dOwner) != PlayerCache(playerid)(pUID))
	   		(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Edytowaæ etykiety mo¿esz tylko bêd¹c w budynku, którego w³aœcicielem jesteœ., OK, )
	   			return 1
			)
		)
		if(DoorData(doorid)(dOwnerType) == OWNER_GROUP)
		(
			if(!IsPlayerPermissedGroup(playerid, DoorData(doorid)(dOwner), PERM_LEADER))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Edytowaæ etykiety mo¿esz tylko bêd¹c w budynku, którego w³aœcicielem jesteœ., OK, )
				return 1
			)
		)
	)
	label_id = GetClosestLabel(playerid)
	if(label_id == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnej etykiety w pobli¿u., OK, )
		return 1
	)
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pMove3DText) == label_id)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ktoœ aktualnie edytuje tê etykietê., OK, )
				return 1
			)
		)
	)
	Float:PosX, Float:PosY, Float:PosZ,
		string(256)

	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_X, PosX)
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Y, PosY)
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Z, PosZ)

	//SetPlayerCameraPos(playerid, PosX + 3, PosY + 4, PosZ + 4)
	SetPlayerCameraLookAt(playerid, PosX, PosY, PosZ)

	hrp_TogglePlayerControllable(playerid, false)

	PlayerCache(playerid)(pMove3DText) = label_id

	format(string, sizeof(string), ~b~Identyfikator: ~w~%d~n~~n~~n~~r~PosX: ~w~%.4f ~r~PosY: ~w~%.4f ~r~PosZ: ~w~%.4f, GetLabelUID(label_id), PosX, PosY, PosZ)
	TextDrawSetString(Text:TextDrawEditorTitle(playerid), string)

	TextDrawShowForPlayer(playerid, Text:TextDrawEditorBack)
	TextDrawShowForPlayer(playerid, Text:TextDrawEditorTitle(playerid))

	TextDrawSetString(Text:TextDrawMainInfo(playerid), Edytor etykiety ~g~aktywny~w~.~n~~n~~y~/esave ~w~- zapisz pozycje etykiety~n~~y~/edel ~w~- usun etykiete)
	TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
	return 1
)

CMD:esave(playerid, params())
(
	if(PlayerCache(playerid)(pMove3DText) == INVALID_3DTEXT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnej etykiety., OK, )
		return 1
	)
	label_id = PlayerCache(playerid)(pMove3DText)

	hrp_TogglePlayerControllable(playerid, true)
	SetCameraBehindPlayer(playerid)

	Save3DTextLabel(label_id)
	PlayerCache(playerid)(pMove3DText) = INVALID_3DTEXT_ID

	TextDrawHideForPlayer(playerid, Text:TextDrawEditorBack)
	TextDrawHideForPlayer(playerid, Text:TextDrawEditorTitle(playerid))

	TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))

	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pozycja etykiety zosta³a pomyœlnie zapisana., OK, )
	return 1
)

CMD:edel(playerid, params())
(
	if(PlayerCache(playerid)(pMove3DText) == INVALID_3DTEXT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnej etykiety., OK, )
		return 1
	)
	label_id = PlayerCache(playerid)(pMove3DText)

	hrp_TogglePlayerControllable(playerid, true)
	SetCameraBehindPlayer(playerid)

	Destroy3DTextLabel(label_id)
	PlayerCache(playerid)(pMove3DText) = INVALID_3DTEXT_ID

	TextDrawHideForPlayer(playerid, Text:TextDrawEditorBack)
	TextDrawHideForPlayer(playerid, Text:TextDrawEditorTitle(playerid))

	TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))

	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Etykieta zosta³a ca³kowicie usuniêta., OK, )
	return 1
)

CMD:getvw(playerid, params())
(
	SendClientFormatMessage(playerid, COLOR_GREY, VirtualWorld w którym siê obecnie znajdujesz to %d., GetPlayerVirtualWorld(playerid))
	return 1
)

CMD:jailtime(playerid, params())
(
	if (PlayerCache(playerid)(pArrestDay) ) 0)
	(
		string(64)
		format(string, sizeof(string), ~r~Areszt~w~: ~g~%d ~w~dni., PlayerCache(playerid)(pArrestDay))
		GameTextForPlayer(playerid, string, 1000, 1)
	)
	else if(PlayerCache(playerid)(pArrest))
	(
		string(64)
		if(PlayerCache(playerid)(pArrestTime) ) 1*60)
		(
			format(string, sizeof(string), ~r~Areszt~w~: ~g~%d ~w~min., PlayerCache(playerid)(pArrestTime)/60)
			GameTextForPlayer(playerid, string, 1000, 1)
		)
		else
		(
			format(string, sizeof(string), ~r~Areszt~w~: ~g~%d ~w~sek., PlayerCache(playerid)(pArrestTime))
			GameTextForPlayer(playerid, string, 1000, 1)
		)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ aktualnie w areszcie., OK, )
		return 1
	)
	return 1
)

CMD:panic(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)

	string(64)
	if(GlobalGod == true)
	(
		GlobalGod = false
		format(string, sizeof(string), (PANIC BUTTON) %s wy³¹czy³ globalny godmode., PlayerName(playerid))
	)
	else
	(
		GlobalGod = true
		format(string, sizeof(string), (PANIC BUTTON) %s w³¹czy³ globalny godmode., PlayerName(playerid))
	)

	foreach(Player, i)
	(
		if(PlayerCache(i)(pAdmin) != 0)
		(
			SendClientMessage(i, COLOR_RED, string)
		)
	)

	return 1
)

CMD:banpanic(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)

	string(64)
	if(CheckSumCheck == true)
	(
		CheckSumCheck = false
		format(string, sizeof(string), (PANIC BUTTON) %s wy³¹czy³ sprawdzanie bugowania kasy., PlayerName(playerid))
	)
	else
	(
		CheckSumCheck = true
		format(string, sizeof(string), (PANIC BUTTON) %s w³¹czy³ sprawdzanie bugowania kasy., PlayerName(playerid))
	)

	foreach(Player, i)
	(
		if(PlayerCache(i)(pAdmin) != 0)
		(
			SendClientMessage(i, COLOR_RED, string)
		)
	)

	return 1
)

CMD:time(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz tego zrobiæ bêd¹c nieprzytomnym., OK, )
		return 1
	)
	if(!PlayerHaveItem(playerid, ITEM_WATCH))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz zegarka w swoim ekwipunku., OK, )
		return 1
	)
	hour, minute, second, string(128)
	gettime(hour, minute, second)

	format(string, sizeof(string), ~w~Godzina:~w~ ~y~%02d:%02d:%02d~y~~w~., hour, minute, second)
	GameTextForPlayer(playerid, string, 5000, 1)

	format(string, sizeof(string), * %s spogl¹da na zegarek., PlayerName(playerid))
	FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)

	ApplyAnimation(playerid,COP_AMBIENT, Coplook_watch, 4.1, 0, 0, 0, 0, 0, 1)
	return 1
)

CMD:czas(playerid, params()) return cmd_time(playerid, params)
CMD:zegarek(playerid, params()) return cmd_time(playerid, params)

CMD:kostka(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz tego zrobiæ bêd¹c nieprzytomnym., OK, )
		return 1
	)
	if(!PlayerHaveItem(playerid, ITEM_CUBE))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz kostki do gry w swoim ekwipunku., OK, )
		return 1
	)
	rand = 1 + random(6), string(128)

	format(string, sizeof(string), * %s wyrzuci³ %d oczek na 6., PlayerName(playerid), rand)
	ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
	return 1
)

CMD:wepchnij(playerid, params())
(
	giveplayer_id
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /wepchnij (ID gracza))
		return 1
	)
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz siedzieæ w pojeŸdzie jako kierowca., OK, )
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wepchn¹æ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(!PlayerCache(giveplayer_id)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz, którego chcesz wepchn¹æ musi byæ nieprzytomny., OK, )
		return 1
	)
 	vehid = GetPlayerVehicleID(playerid)
	if(IsSeatFree(vehid, 2))
	(
 		PlayerCache(giveplayer_id)(pLastVeh) = vehid
		PutPlayerInVehicle(giveplayer_id, vehid, 2)

		SetCameraBehindPlayer(giveplayer_id)
	)
	else if(IsSeatFree(vehid, 3))
	(
 		PlayerCache(giveplayer_id)(pLastVeh) = vehid
		PutPlayerInVehicle(giveplayer_id, vehid, 3)

  		SetCameraBehindPlayer(giveplayer_id)
	)
	else
	(
		GameTextForPlayer(playerid, ~r~Brak wolnego miejsca w pojezdzie., 4000, 3)
	)
	return 1
)

CMD:zapukaj(playerid, params())
(
	string(128)
	foreach(Doors, d)
	(
 		if(DoorData(d)(dUID))
   		(
			if(IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(d)(dEnterX), DoorData(d)(dEnterY), DoorData(d)(dEnterZ)) || IsPlayerInRangeOfPoint(playerid, 2.0, DoorData(d)(dExitX), DoorData(d)(dExitY), DoorData(d)(dExitZ)) && GetPlayerVirtualWorld(playerid) == DoorData(d)(dExitVW))
			(
				foreach(Player, i)
				(
					if(i != playerid)
					(
						if(GetPlayerDoorID(i) == d)
						(
							SendClientMessage(i, COLOR_DO, ** S³ychaæ dŸwiêk pukania dobiegaj¹cy od drzwi wejœciowych. **)
						)
					)
				)
				ApplyAnimation(playerid, HEIST9, Use_SwipeCard, 4.1, 0, 0, 0, 0, 0, 1)

				format(string, sizeof(string), * %s puka do drzwi., PlayerName(playerid))
				ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
				break
			)
		)
	)
	return 1
)

/*CMD:pogoda(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	weather_id, string(128)
	if(sscanf(params, d, weather_id))
	(
		hrp_Tip(playerid, /pogoda (ID pogody))
		return 1
	)
	SetWeather(weather_id)

	format(string, sizeof(string), Pogoda zosta³a pomyœlnie zmieniona. ID pogody: %d., weather_id)
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)*/

CMD:g(playerid, params())
(
	group_slot = INVALID_SLOT_ID, type(32), varchar(64), string(128)
	// if(isnull(params))	SendClientMessage(playerid, COLOR_GREY, Je¿eli jesteœ na s³u¿bie jednej z grup, nie musisz podawaæ jej slotu - skrypt automatycznie go wyszuka.)

	if(sscanf(params, ds(32)S()(64), group_slot, type, varchar))
	(
		format(string, sizeof(string), /g (slot (1-%d)) (zapros | wypros | info | pojazdy | respawn | online | wyplac | wplac | czat | wczytaj | ogloszenia | spawn), MAX_GROUP_SLOTS)
		hrp_Tip(playerid, string)

		list_groups(256), group_id_fix
		format(list_groups, sizeof(list_groups), (C0C0C0)Slot\tNazwa oraz UID grupy(FFFFFF))

		for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
		(
  			if(PlayerGroup(playerid)(slot)(gUID))
			(
	  			group_id_fix = PlayerGroup(playerid)(slot)(gID)
				format(list_groups, sizeof(list_groups), %s\n%d\t%s (%d), list_groups, slot + 1, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			)
		)
		ShowPlayerDialog(playerid, D_MANAGE_GROUPS, DIALOG_STYLE_LIST, Grupy, do których nale¿ysz, list_groups, Wybierz, Anuluj)
		return 1
	)
	group_slot -= 1
	if(group_slot ( 0 || group_slot ) MAX_GROUP_SLOTS)
	(
		GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
		return 1
	)
	if(!PlayerGroup(playerid)(group_slot)(gUID))
	(
		GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
		return 1
	)
	if(!strcmp(type, zapros, true))
	(
		if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, aby u¿yæ tej komendy., OK, )
			return 1
		)
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			format(string, sizeof(string), /g (slot (1-%d)) zapros (ID gracza), MAX_GROUP_SLOTS)
			hrp_Tip(playerid, string)
			return 1
		)
		if(giveplayer_id == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
   			return 1
		)
		if(IsPlayerNPC(giveplayer_id))
		(
			GuiMsg(playerid, Nie mo¿esz zatrudniæ bota., 1)
			return 1
		)
		if(!Logged(giveplayer_id))
		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zatrudniæ samego siebie., OK, )
			return 1
		)
		group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
		if(GroupData(group_id_fix)(gType) == GROUP_FAMILY)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaprosiæ nikogo do rodziny., OK, )
			return 1
		)
		if(IsPlayerInGroup(giveplayer_id, GroupData(group_id_fix)(gUID)))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nale¿y ju¿ do tej grupy., OK, )
			return 1
		)
		giveplayer_group_slot = GetPlayerFreeGroupSlot(giveplayer_id)
		if(giveplayer_group_slot == INVALID_SLOT_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie posiada ¿adnego wolnego slotu dla grupy., OK, )
			return 1
		)
		
		// Sprawdzenie czy dzisiaj go ju¿ nie dodano, pieprzeni bugerzy PDM_START
		if(IsPlayerGroupLimited(giveplayer_id, group_id_fix) && PlayerCache(playerid)(pAdmin) == 0)
		(
			GuiMsg(playerid, Ten gracz zosta³ dzisiaj raz dodany do tej grupy.\nPoczekaj do jutra, by zrobiæ to ponownie., 1)
			return 1
		)
		
		PlayerGroup(giveplayer_id)(giveplayer_group_slot)(gUID) = GroupData(group_id_fix)(gUID)
		PlayerGroup(giveplayer_id)(giveplayer_group_slot)(gID) = group_id_fix

		mysql_query_format(INSERT INTO hrp_char_groups (char_uid, group_uid) VALUES (%d, %d), PlayerCache(giveplayer_id)(pUID), GroupData(group_id_fix)(gUID))

		format(string, sizeof(string), Gracz %s zaprosi³ Ciê do grupy %s., PlayerName(playerid), GroupData(group_id_fix)(gName))
		SendClientMessage(giveplayer_id, COLOR_BUSINESS, string)

		format(string, sizeof(string), Zaprosi³eœ gracza %s do grupy %s., PlayerName(giveplayer_id), GroupData(group_id_fix)(gName))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_GroupActionLog(%s (UID: %d) zaprosil gracza %s (UID: %d) do grupy %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerRealName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
		AddGroupLog(playerid, group_id_fix, %s zaprosil gracza %s do grupy., PlayerName(playerid), PlayerName(giveplayer_id))
		
		AddPlayerGroupLimit(playerid, group_id_fix)
		return 1
	)
	if(!strcmp(type, wypros, true))
	(
		if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, aby u¿yæ tej komendy., OK, )
			return 1
		)
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			format(string, sizeof(string), /g (slot (1-%d)) wypros (ID gracza), MAX_GROUP_SLOTS)
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
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wyprosiæ samego siebie., OK, )
			return 1
		)
		group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
		if(GroupData(group_id_fix)(gType) == GROUP_FAMILY)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wyprosiæ nikogo z rodziny., OK, )
			return 1
		)
		if(!IsPlayerInGroup(giveplayer_id, GroupData(group_id_fix)(gUID)))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie jest cz³onkiem Twojej grupy., OK, )
			return 1
		)
		giveplayer_group_slot = GetPlayerGroupSlot(giveplayer_id, GroupData(group_id_fix)(gUID))

  		PlayerGroup(giveplayer_id)(giveplayer_group_slot)(gUID) = 0
		PlayerGroup(giveplayer_id)(giveplayer_group_slot)(gID) = 0

		PlayerGroup(giveplayer_id)(giveplayer_group_slot)(gPerm) = 0
  		strmid(PlayerGroup(giveplayer_id)(giveplayer_group_slot)(gTitle), Brak, 0, 4, 32)

		PlayerGroup(giveplayer_id)(giveplayer_group_slot)(gPayment) = 0
		mysql_query_format(DELETE FROM hrp_char_groups WHERE char_uid = %d AND group_uid = %d, PlayerCache(giveplayer_id)(pUID), GroupData(group_id_fix)(gUID))

		format(string, sizeof(string), Gracz %s wyprosi³ Ciê z grupy %s., PlayerName(playerid), GroupData(group_id_fix)(gName))
		SendClientMessage(giveplayer_id, COLOR_BUSINESS, string)

		format(string, sizeof(string), Wyprosi³eœ gracza %s z grupy %s., PlayerName(giveplayer_id), GroupData(group_id_fix)(gName))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, string, OK, )

		hrp_GroupActionLog(%s (UID: %d) wyprosil gracza %s (UID: %d) z grupy %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerRealName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
		AddGroupLog(playerid, group_id_fix, %s wyprosil gracza %s z grupy., PlayerName(playerid), PlayerName(giveplayer_id))
		return 1
	)
	if(!strcmp(type, spawn, true))
	(
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku., OK, )
			return 1
		)
		group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
		if(GroupData(group_id_fix)(gType) != GROUP_FAMILY)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Spawn ustawic mozna tylko w grupie rodziny., OK, )
			return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != GroupData(group_id_fix)(gUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, przypisanym pod ta grupe., OK, )
			return 1
		)
		
		PlayerCache(playerid)(pFamilyHouse) = DoorData(doorid)(dUID)
		PlayerCache(playerid)(pSpawnPlace) = SPAWN_FAMILYHOUSE
		SavePlayerStats(playerid, SAVE_PLAYER_BASIC)

		format(string, sizeof(string), Ustali³eœ spawn w drzwiach %s (UID: %d).\nOd tej pory, spawnowaæ bêdziesz siê w nich., DoorData(doorid)(dName), DoorData(doorid)(dUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		return 1
	)
	if(!strcmp(type, info, true))
	(
		if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, aby u¿yæ tej komendy., OK, )
			return 1
		)
		group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
		ShowPlayerGroupInfo(playerid, group_id_fix)
		return 1
	)
	if(!strcmp(type, pojazdy, true))
	(
		if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_CARS))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, aby u¿yæ tej komendy., OK, )
			return 1
		)
		list_vehicles(1024)
		foreach(Vehicles, vehid)
		(
			if(CarInfo(vehid)(cUID))
			(
				if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == PlayerGroup(playerid)(group_slot)(gUID))
				(
					format(list_vehicles, sizeof(list_vehicles), %s\n%d\t\t%s, list_vehicles, vehid, CarInfo(vehid)(cName))
				)
			)
		)
		if(strlen(list_vehicles))
		(
			ShowPlayerDialog(playerid, D_LIST_SPAWNED_CARS, DIALOG_STYLE_LIST, Pojazdy nale¿¹ce do grupy, list_vehicles, Namierz, Anuluj)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych pojazdów przypisanych pod grupê., OK, )
		)
		return 1
	)
	if(!strcmp(type, respawn, true))
	(
		if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, aby u¿yæ tej komendy., OK, )
			return 1
		)
	 	foreach(Vehicles, vehid)
	  	(
	   		if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == PlayerGroup(playerid)(group_slot)(gUID))
		 	(
		  		if(!IsAnyPlayerInVehicle(vehid))
		  		(
					SetVehicleToRespawn(vehid)
					UpdateVehicleDamageStatus(vehid, CarInfo(vehid)(cVisual)(0), CarInfo(vehid)(cVisual)(1), CarInfo(vehid)(cVisual)(2), CarInfo(vehid)(cVisual)(3))
	 			)
			)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Powodzenie, Wszystkie nieu¿ywane pojazdy grupowe zosta³y przywrócone na miejsce spawnu., OK, )
		return 1
	)
	if(!strcmp(type, online, true))
	(
  		list_workers(1024)
		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
	   			if(IsPlayerInGroup(i, PlayerGroup(playerid)(group_slot)(gUID)))
				(
					if(PlayerCache(i)(pGroupDuty) == PlayerGroup(playerid)(group_slot)(gUID))
					(
						format(list_workers, sizeof(list_workers), %s\n%d\t\t(008000)%s(FFFFFF), list_workers, i, PlayerName(i))
					)
					else
					(
						format(list_workers, sizeof(list_workers), %s\n%d\t\t%s, list_workers, i, PlayerName(i))
					)
				)
			)
		)
		if(strlen(list_workers) ) 0)
		(
  			ShowPlayerDialog(playerid, D_LIST_PLAYERS, DIALOG_STYLE_LIST, Cz³onkowie online:, list_workers, PW, Zamknij)
		)
		return 1
	)
	if(!strcmp(type, wyplac, true))
	(
		// Antybugowanie
		bool:checkbug = false
		if(gettime() - LogTime(playerid) ) 60)
			checkbug= true
			
		if(!checkbug)
		(
			GuiMsg(playerid, Musisz chwilê odczekaæ nim u¿yjesz tej komendy., 0)
			return 1
		)
				
		if(PlayerCache(playerid)(pGamePoints) ( 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz dokonaæ przelewu pieniêdzy nie majac 100GS., OK, )
			return 1
		)
		if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, aby u¿yæ tej komendy., OK, )
			return 1
		)
	   	price
	   	if(sscanf(varchar, d, price))
	   	(
	   		format(string, sizeof(string), /g (slot (1-%d)) wyplac (Kwota), MAX_GROUP_SLOTS)
	   		hrp_Tip(playerid, string)
	   		return 1
	   	)
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w banku., OK, )
			return 1
		)
	 	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
	  	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w banku., OK, )
	   		return 1
	   	)
	   	at_group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
	   	if(GroupData(at_group_id_fix)(gType) != GROUP_BANK)
	   	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w banku., OK, )
	   		return 1
	   	)
	   	if(price (= 0)
	   	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê., OK, )
	   		return 1
	   	)
	   	group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
	   	if(price ) GroupData(group_id_fix)(gCash))
	   	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz takiej iloœci gotówki na koncie biznesu., OK, )
	   		return 1
	   	)
	   	hrp_GivePlayerMoney(playerid, price)
	   	SavePlayerStats(playerid, SAVE_PLAYER_BASIC)

	   	GroupData(group_id_fix)(gCash) -= price
	   	SaveGroup(group_id_fix)

	   	format(string, sizeof(string), Wyp³aci³eœ pieni¹dze z konta grupy.\n\nZ konta grupy zosta³o wyp³acone: $%d\nPozosta³e œrodki na koncie: $%d, price, GroupData(group_id_fix)(gCash))
	   	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		hrp_GroupActionLog(%s (UID: %d) wyplacil $%d z konta grupy %s (UID: %d). Stan konta wynosi: $%d., PlayerRealName(playerid), PlayerCache(playerid)(pUID), price, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID), GroupData(group_id_fix)(gCash))
		AddGroupLog(playerid, group_id_fix, %s wyplacil $%d z grupy., PlayerName(playerid), price)
		return 1
	)
	if(!strcmp(type, wplac, true))
	(
		// Antybugowanie
		bool:checkbug = false
		if(gettime() - LogTime(playerid) ) 60)
			checkbug= true
			
		if(!checkbug)
		(
			GuiMsg(playerid, Musisz chwilê odczekaæ nim u¿yjesz tej komendy., 0)
			return 1
		)
				
		if(PlayerCache(playerid)(pGamePoints) ( 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz dokonaæ przelewu pieniêdzy nie majac 100GS., OK, )
			return 1
		)
		if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, aby u¿yæ tej komendy., OK, )
			return 1
		)
	   	price
	   	if(sscanf(varchar, d, price))
	   	(
	   		format(string, sizeof(string), /g (slot (1-%d)) wplac (Kwota), MAX_GROUP_SLOTS)
	   		hrp_Tip(playerid, string)
	   		return 1
	   	)
		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w banku., OK, )
			return 1
		)
	 	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
	  	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w banku., OK, )
	   		return 1
	   	)
	   	at_group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
	   	if(GroupData(at_group_id_fix)(gType) != GROUP_BANK)
	   	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w banku., OK, )
	   		return 1
	   	)
	   	if(price (= 0)
	   	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê., OK, )
	   		return 1
	   	)
	   	if(price ) PlayerCache(playerid)(pCash))
	   	(
	   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono nieprawid³ow¹ kwotê., OK, )
	   		return 1
	   	)
	   	group_id_fix = PlayerGroup(playerid)(group_slot)(gID)

	   	hrp_GivePlayerMoney(playerid, -price)
	   	SavePlayerStats(playerid, SAVE_PLAYER_BASIC)

	   	GroupData(group_id_fix)(gCash) += price
		GroupData(group_id_fix)(gActionTime) = gettime()
	   	SaveGroup(group_id_fix)

	   	format(string, sizeof(string), Wp³aci³eœ pieni¹dze na konto grupy.\n\nNa konto grupy zosta³o wp³acone: $%d\nNowy stan konta grupy: $%d, price, GroupData(group_id_fix)(gCash))
	   	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		hrp_GroupActionLog(%s (UID: %d) wplacil $%d na konto grupy %s (UID: %d). Stan konta wynosi: $%d., PlayerRealName(playerid), PlayerCache(playerid)(pUID), price, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID), GroupData(group_id_fix)(gCash))
		AddGroupLog(playerid, group_id_fix, %s wplacil %d na konto grupy., PlayerName(playerid), price)
		return 1
	)
	if(!strcmp(type, czat, true))
	(
		if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, aby u¿yæ tej komendy., OK, )
			return 1
		)

		group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
		if(GroupData(group_id_fix)(gType) == GROUP_FAMILY)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Rodzina nie posiada czatu OOC., OK, )
			return 1
		)
		if(GroupData(group_id_fix)(gToggleChat))
		(
			GroupData(group_id_fix)(gToggleChat) = false

			format(string, sizeof(string), Czat OOC grupy %s (UID: %d) zosta³ w³¹czony., GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			SendClientMessage(playerid, GroupData(group_id_fix)(gColor), string)
		)
		else
		(
  			GroupData(group_id_fix)(gToggleChat) = true

			format(string, sizeof(string), Czat OOC grupy %s (UID: %d) zosta³ wy³¹czony., GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
			SendClientMessage(playerid, GroupData(group_id_fix)(gColor), string)
		)
		return 1
	)
	if(!strcmp(type, wczytaj, true))
	(
		if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_LEADER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ, aby u¿yæ tej komendy., OK, )
			return 1
		)
		group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
		if(GroupData(group_id_fix)(gActionTime) + 5 ) gettime())
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz teraz u¿yæ tej komendy., OK, )
			return 1
		)
		ReloadGroup(group_id_fix)

		format(string, sizeof(string), Dane na temat grupy %s (UID: %d) zosta³y pomyœlnie wczytane., GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		hrp_GroupActionLog(%s (UID: %d) wczytal statystyki grupy %s (UID: %d)., PlayerRealName(playerid), PlayerCache(playerid)(pUID), GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gUID))
		return 1
	)
	if(!strcmp(type, ogloszenia, true))
	(
  		ann(300), group_id_fix = PlayerGroup(playerid)(group_slot)(gID), name(128)

		format(ann, sizeof(ann), %s, getLastAnn(GroupData(group_id_fix)(gUID)))
		format(name, sizeof(name), ** Og³oszenia %s ***, GroupData(group_id_fix)(gName))

		if(strlen(ann) == 0)
		(
			format(ann, sizeof(ann), **Brak og³oszeñ dla tej grupy.**)
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, name, ann, OK, )
		return 1
	)
	return 1
)

CMD:przebierz(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		return 1
	)
	SetPlayerSkin(playerid, PlayerCache(playerid)(pSkin))
	return 1
)

CMD:tartak(playerid, params())
(
	if(IsPlayerInAnyVehicle(playerid))
	(
		vehid = GetPlayerVehicleID(playerid), group_id_fix = GetPlayerDutyGroupID(playerid)
		if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != GroupData(group_id_fix)(gUID) || !IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
			return 1
		)
		if(GroupData(group_id_fix)(gType) != GROUP_SAWMILL)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd nie nale¿y do tartaka., OK, )
			return 1
		)
		if(!IsPlayerInRangeOfPoint(playerid, 15.0, -1989.5765,-2382.0974,30.3322) && !IsPlayerInRangeOfPoint(playerid, 15.0, -1946.2982,-2442.2690,30.3304) && !IsPlayerInRangeOfPoint(playerid, 15.0, -2015.8252,-2405.4202,30.3307))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ na miejscu przeznaczonym do roz³adunku drewna., OK, )
			return 1
		)

		mysql_query_format(SELECT count(item_uid) as item_count FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_VEHICLE, CarInfo(vehid)(cUID))

		new	item_count, data(128)

		mysql_store_result()
		mysql_fetch_row(data, |)
		sscanf(data, p(|)d, item_count)
		mysql_free_result()

		if(item_count ) 0)
		(
			time = (floatround(item_count / 4) == 0)? 1 : floatround(item_count / 4)

			SetTimerEx(UnloadWood, time * 1000, 0, dddd, playerid, vehid, group_id_fix, item_count) //(player, vehid, group_id_fix, item_count)

			format(data, sizeof(data), Roz³adowywanie drewna potrwa %d sekund ..., time)
			GameTextForPlayer(playerid, data, time * 1000, 6)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W tym pojeŸdzie nie ma ¿adnych k³ód., OK, )
			return 1
		)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ w pojeŸdzie aby go roz³adowaæ., OK, )
	)
	return 1
)

CMD:kopalnia(playerid, params())
(
	if(IsPlayerInAnyVehicle(playerid))
	(
		vehid = GetPlayerVehicleID(playerid), group_id_fix = GetPlayerDutyGroupID(playerid)
		if(CarInfo(vehid)(cOwnerType) != OWNER_GROUP || CarInfo(vehid)(cOwner) != GroupData(group_id_fix)(gUID) || !IsPlayerPermissedGroup(playerid, CarInfo(vehid)(cOwner), PERM_CARS))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do zarz¹dzania tym pojazdem., OK, )
			return 1
		)
		if(GroupData(group_id_fix)(gType) != GROUP_QUARRY)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten pojazd nie nale¿y do kopalni., OK, )
			return 1
		)

		if(!IsPlayerInRangeOfPoint(playerid, 15.0, 695.2902,843.4327,-27.4401) && !IsPlayerInRangeOfPoint(playerid, 15.0, 682.4719,822.9739,-27.2756) && !IsPlayerInRangeOfPoint(playerid, 15.0, 531.3472,830.8685,-27.7690) && !IsPlayerInRangeOfPoint(playerid, 15.0, 536.7856,882.4314,-36.6261))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ na miejscu przeznaczonym do roz³adunku kamienia., OK, )
			return 1
		)

		mysql_query_format(SELECT count(item_uid) as item_count FROM hrp_items WHERE item_place = %d AND item_owner = %d, PLACE_VEHICLE, CarInfo(vehid)(cUID))

		new	item_count, data(128)

		mysql_store_result()
		mysql_fetch_row(data, |)
		sscanf(data, p(|)d, item_count)
		mysql_free_result()

		if(item_count ) 0)
		(
			time = (floatround(item_count / 4) == 0)? 1 : floatround(item_count / 4)

			SetTimerEx(UnloadRocks, time * 1000, 0, dddd, playerid, vehid, group_id_fix, item_count) //(player, vehid, group_id_fix, item_count)

			format(data, sizeof(data), Roz³adowywanie kamieni potrwa %d sekund ..., time)
			GameTextForPlayer(playerid, data, time * 1000, 6)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W tym pojeŸdzie nie ma ¿adnych kamieni., OK, )
			return 1
		)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ w pojeŸdzie aby go roz³adowaæ., OK, )
		return 1
	)
	return 1
)

CMD:strefy(playerid, params())
(
	if(!strcmp(params, show, true))
	(
		GangZonesHide(playerid)
		GangZonesShow(playerid)
		PlayerCache(playerid)(pGangZoneShowing) = true
		return 1
	)
	if(!strcmp(params, hide, true))
	(
		GangZonesHide(playerid)
		PlayerCache(playerid)(pGangZoneShowing) = false
		return 1
	)

	if(PlayerCache(playerid)(pGangZoneShowing))
	(	GangZonesHide(playerid)
		PlayerCache(playerid)(pGangZoneShowing) = false
	)
	else
	(
		GangZonesShow(playerid)
		PlayerCache(playerid)(pGangZoneShowing) = true
	)

	return 1
)

/*CMD:strefa(playerid, params())
(
	return 1
	gangzone_id = GetCurrentPlayerGangZone(playerid)
	if(gangzone_id == -1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ aktualnie na terenie ¿adnego gangu., OK, )
		return 1
	)

	if(IsPlayerPermissedGroup(playerid, GangZoneInfo(gangzone_id)(gOwner), PERM_LEADER))
	(
		ShowGangZoneSummary(playerid, gangzone_id, GZ_SUMMARY_OWNER)
		return 1
	)

	ShowGangZoneSummary(playerid, gangzone_id, GZ_SUMMARY_VISITOR)
	return 1
)*/

CMD:knebel(playerid, params())
(
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /knebel (ID gracza))
		return 1
	)
	if(PlayerCache(giveplayer_id)(pGagged) != INVALID_PLAYER_ID)
	(
		if(PlayerCache(giveplayer_id)(pGagged) == playerid)
		(
			PlayerCache(giveplayer_id)(pGagged) = INVALID_PLAYER_ID
			GuiMsg(playerid,Å’ci¹gn¹³eœ knebel.,0)
			GuiMsg(giveplayer_id,Å’ci¹gniêto Ci knebel z ust.,0)
			return 1
		)

		GuiMsg(playerid,Ten gracz ma ju¿ knebel w ustach.,1)
		//tu mu go zdejmij
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz kneblowaæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(!PlayerHaveItem(playerid, ITEM_GAG))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiedniego przedmiotu w swoim ekwipunku., OK, )
		return 1
	)

	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pGagged) == playerid)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zakneblowaæ wiêcej osób., OK, )
				return 1
			)
		)
	)

	PlayerCache(giveplayer_id)(pGagged) = playerid

	GuiMsg(giveplayer_id,Za³o¿ono Ci knebel na usta, od tej pory nie bêdziesz móg³ nic powiedzieæ.,0)

	format(string, sizeof(string), Zakneblowa³eœ %s, aby wyci¹gn¹æ knebel u¿yj komendy raz jeszcze ( /knebel (ID) ), PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

	return 1
)

//co by mo¿na by³o wi¹zaæ ludzi
CMD:lina(playerid, params())
(
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /lina (ID gracza))
		return 1
	)
	if(PlayerCache(giveplayer_id)(pRoped) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid,Ten gracz jest ju¿ zwi¹zany.,1)
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zwi¹zaæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(!PlayerHaveItem(playerid, ITEM_ROPE))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiedniego przedmiotu w swoim ekwipunku., OK, )
		return 1
	)

	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pRoped) == playerid)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zwi¹zaæ wiêcej osób., OK, )
				return 1
			)
		)
	)

	PlayerCache(giveplayer_id)(pRoped) = playerid
	SetPlayerSpecialAction(giveplayer_id, SPECIAL_ACTION_CUFFED)

	format(string, sizeof(string), Zwi¹za³eœ gracza %s, aby rozwi¹zaæ, u¿yj komendy /rozwiarz., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

	return 1
)

CMD:rozwiaz(playerid, params())
(
	giveplayer_id, string(64)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /rozwiaz (ID gracza))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz rozwi¹zaæ siebie., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(PlayerCache(giveplayer_id)(pRoped) != playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyt¹pi³ b³¹d, Ten gracz nie jest zwi¹zany przez Ciebie., OK, )
		return 1
	)
	PlayerCache(giveplayer_id)(pRoped) = INVALID_PLAYER_ID
	SetPlayerSpecialAction(giveplayer_id, SPECIAL_ACTION_NONE)

	hrp_TogglePlayerControllable(giveplayer_id, 1)

	format(string, sizeof(string), Gracz %s zosta³ rozwi¹zany., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	return 1
)

CMD:worek(playerid, params())
(
	giveplayer_id, string(128)
	if(sscanf(params, d, giveplayer_id))
	(
		hrp_Tip(playerid, /worek (ID gracza))
		return 1
	)
	if(PlayerCache(giveplayer_id)(pBagged) != INVALID_PLAYER_ID)
	(
		if(PlayerCache(giveplayer_id)(pBagged) == playerid)
		(
			//zdejmij
			PlayerCache(giveplayer_id)(pBagged) = INVALID_PLAYER_ID
			UnbagPlayerHead(giveplayer_id)

			GuiMsg(playerid,Å’ci¹gn¹³eœ worek z g³owy swojej ofiary.,0)
			GuiMsg(giveplayer_id,Z Twojej g³owy œci¹gniêto worek, znów widzisz wszystko dooko³a.,0)
			return 1
		)

		GuiMsg(playerid,Ten gracz ma ju¿ worek na g³owie.,1)
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Sam sobie nie mo¿esz takiego worka za³o¿yæ., OK, )
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
	if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
 		return 1
	)
	if(!PlayerHaveItem(playerid, ITEM_HEADBAG))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiedniego przedmiotu w swoim ekwipunku., OK, )
		return 1
	)

	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pBagged) == playerid)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Za³o¿y³eœ ju¿ komuœ worek na g³owê., OK, )
				return 1
			)
		)
	)

	PlayerCache(giveplayer_id)(pBagged) = playerid
	//SetPlayerSpecialAction(giveplayer_id, SPECIAL_ACTION_CUFFED)
	BagPlayerHead(giveplayer_id)
	GuiMsg(playerid,Za³o¿y³eœ worek na g³owê gracza, od teraz z pewnoœci¹ nic nie widzi.,0)
	GuiMsg(giveplayer_id,Za³o¿ono worek na Twoj¹ g³owê, nie bêdziesz nic widzia³ tak d³ugo a¿ ktoœ go zdejmie.,0)

	format(string, sizeof(string), Za³o¿y³eœ worek na g³owê %s, aby zdj¹æ u¿yj komendy raz jeszcze., PlayerName(giveplayer_id))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

	return 1
)

CMD:domowy(playerid, params())
(
	doorid = GetPlayerDoorID(playerid)
	object_id = GetClosestObject(playerid)

	if(!IsDoorAddonMounted(doorid,ITEM_HOMEPHONESET))
	(
		GuiMsg(playerid,W tym budynku nie ma telefonu stacjonarnego.,1)
		return 1
	)

	if(doorid == INVALID_DOOR_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w budynku, aby móc u¿yæ tej komendy., OK, )
		return 1
	)
	if(object_id == INVALID_OBJECT_ID || (GetObjectModel(object_id) != 19630 && GetObjectModel(object_id) != 19629))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê przy ¿adnym telefonie stacjonarnym., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿ywaæ telefonu podczas stanu nieprzytomnoœci., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGymType) != TRAIN_NONE)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz korzystaæ z telefonu podczas treningu., OK, )
		return 1
	)

	phoneid = -1

	for(i = 0  i ( MAX_HOMEPHONES i++)
	(
		if(HomePhones(i)(hDoorUID) == DoorData(doorid)(dUID))
		(
			phoneid = i
			break
		)
		else
		(
			continue
		)
	)

	if(phoneid == -1)
	(
		GuiMsg(playerid,Skrypt wykry³ b³¹d w module telefonów stacjonarnych, powiadom jednego z administratorów lub moderatorów o tym zajœciu.,1)
		return 1
	)

	//instr
	if(HomePhones(phoneid)(hphoneBusy))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten telefon jest ju¿ w u¿yciu., OK, )
		return 1
	)

	//MainPlayerTable(playerid) = phoneid

	//ShowPlayerDialog(playerid,D_DOOR_PHONE_MENU,DIALOG_STYLE_INPUT,Telefon stacjonarny,Wpisz numer telefonu, na który chcesz zadzwoniæ.,Gotowe,Anuluj)

	cmd(8)
	if(sscanf(params, s(8), cmd))
	(
		MainPlayerTable(playerid) = phoneid
		title(64)
		format(title,sizeof(title),Telefon stacjonarny (%i),HomePhones(phoneid)(hPhoneNumber))
		ShowPlayerDialog(playerid,D_DOOR_PHONE_MENU,DIALOG_STYLE_INPUT,title,Wpisz numer telefonu, na który chcesz zadzwoniæ.,Gotowe,Anuluj)
		return 1
	)

	if(!strcmp(cmd, odbierz, true))
	(
		foreach(Calls, callid)
		(
			if(Call(callid)(calledDevice) == DEVICE_HOME)
			(
				if(Call(callid)(calledNumber) == HomePhones(phoneid)(hPhoneNumber))
				(
					Call(callid)(called) = playerid
					Call(callid)(convo) = true

					PlayerCache(playerid)(pUsingBooth) = true
					PlayerCache(playerid)(pCall) = callid

					HomePhones(phoneid)(hphoneBusy) = true

					//SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
					attachPlayerPhone(playerid)

					SendClientMessage(playerid, COLOR_YELLOW, Odebrano telefon. Aby zakoñczyæ rozmowê u¿yj komendy /zakoncz.)
					SendClientMessage(Call(callid)(caller), COLOR_YELLOW, Odebrano telefon. Aby zakoñczyæ rozmowê u¿yj komendy /zakoncz.)
					return 1
				)
			)
		)
	)

	return 1
)

CMD:gazety(playerid, params())
(
	if(PlayerCache(playerid)(pJob) != JOB_PRESSER)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz pracy roznosiciela gazet, jako dorywczej., OK, )
		return 1
	)

	if(!PlayerCache(playerid)(pSpread))
	(
		GuiMsg(playerid,Musisz posiadaæ aktywne zlecenie by u¿yæ tej komendy.,1)
		return 1
	)

	if(IsPlayerInCheckpoint(playerid))
	(
		PlayerCache(playerid)(pSpread) = false
		DisablePlayerCheckpoint(playerid)
		buffer(256)

		box = -1

		for(box_id = 0 box_id ( MAX_PRESSBOX box_id++)
		(
			if(IsPlayerInRangeOfPoint(playerid,3.0,PressBox(box_id)(bPosX),PressBox(box_id)(bPosY),PressBox(box_id)(bPosZ)))
			(
				box = box_id
				break
			)
		)

		boxUID = PressBox(box)(bUID)
		format(buffer,sizeof(buffer),UPDATE wbc_newsboxes SET box_amount = box_amount + 10 WHERE box_id=%i,boxUID)
		mysql_query(buffer)

		PressBox(box)(bAmount) = PressBox(box)(bAmount) + 10

		hrp_GivePlayerMoney(playerid, 15)
		SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
	)
	else
	(
		// nie jest w CP to anuluj t¹ pierdo³ê
		PlayerCache(playerid)(pSpread) = false
		DisablePlayerCheckpoint(playerid)
		GuiMsg(playerid,Anulowa³eœ zlecenie.,0)
	)
	return 1
)

CMD:ruletka(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz tego zrobiæ bêd¹c nieprzytomnym., OK, )
		return 1
	)
	if(!PlayerHaveItem(playerid, ITEM_ROULETTE))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz ruletki w swoim ekwipunku., OK, )
		return 1
	)
	rand = random(36), string(128)

	format(string, sizeof(string), * %s wyrzuci³ %d oczek na 36., PlayerName(playerid), rand)
	ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
	return 1
)

//moj

CMD:kosz(playerid, params())
(
	if(GetPlayerVirtualWorld(playerid) != 0)
	(
		GuiMsg(playerid,Nie mo¿esz graæ w kosza poza worldem zerowym.,1)
		return 1
	)

	if(!PlayerCache(playerid)(pPlayBasket))
	(
		if(!IsPlayerInRangeOfBasket(playerid))
		(
			GuiMsg(playerid,W Twoim pobli¿u nie ma ¿adnego kosza.,1)
			return 1
		)

		TextDrawSetString(Text:TextDrawMainInfo(playerid), Rozpoczales ~b~gre ~w~w koszykowke. Aby anulowac, wcisnij klawisz ~r~ALT~w~.~n~~n~Aby ~y~podniesc ~w~pilke, kliknij na ~r~~k~~PED_SPRINT~~n~~w~Przenoszenie pilki za pomoca ~r~~k~~PED_LOCK_TARGET~)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		object = GetClosestObjectByModel(playerid,946, 5.0)	//obiekt kosza

		PlayerCache(playerid)(pBasketID) = object
		PlayerCache(playerid)(pBallThrowPhase) = 0

		PlayerCache(playerid)(pPlayBasket) = true
		PlayerCache(playerid)(pBallPhase) = BALL_START

		//stworz pilke
		Float:Pos(3)
		GetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))

		Float:PosA
		GetPlayerFacingAngle(playerid,PosA)

		Float:pX = float(random(20000)/10000)
		Float:pY = float(random(20000)/10000)

		object_id = CreateDynamicObject(1946, Pos(0)+ pX, Pos(1) + pY, Pos(2) - 0.7, 0.0, 0.0, PosA, 0, 0, -1, 100.0)
		PlayerCache(playerid)(pBasketBall) = object_id

		// odœwiezenie streamera ¿eby pi³eczki sie pojawiali
		foreach(Player, i)
		(
			if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
			(
				if(IsPlayerInRangeOfPoint(i,50,Pos(0),Pos(1),Pos(2)))
				(
					Streamer_Update(playerid)
				)
			)
		)

	)
	else
	(
		PlayBasketEnd(playerid)
	)


	return 1
)

CMD:slots(playerid, params())
(
	if(!PlayerCache(playerid)(pSlots))
	(
		machineID = slots_GetNerbyID(playerid)
		if(machineID (= 0)
		(
			GuiMsg(playerid,W Twoim pobli¿u nie ma ¿adnej maszyny.,1)
			return 1
		)

		if(SlotMachine(machineID)(mBusy))
		(
			GuiMsg(playerid,Ta maszyna jest ju¿ zajêta przez innego gracza.,0)
			return 1
		)

		PlayerCache(playerid)(pSlotID) = machineID
		slots_StartGame(playerid,machineID)
	)
	else
	(
		slots_EndGame(playerid,PlayerCache(playerid)(pSlotID))
	)

	return 1
)

CMD:zbierz(playerid, params())
(
	plantid = GetNearestPlant(playerid)
	if(plantid != -1)
	(
		if(Plants(plantid)(plantUID))
		(
			CollectPlant(playerid, plantid)
			return 1
		)
	) else (
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Musisz staæ przy doniczce aby zebraæ krzak marihuany., OK, )
		return 1
	)
	return 1
)

CMD:podlej(playerid, params())
(
	plantid = GetNearestPlant(playerid)
	if(plantid != -1)
	(
		if(Plants(plantid)(plantUID))
		(
			WaterPlant(playerid, plantid)
			return 1
		)
	) else (
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Musisz staæ przy doniczce aby podlaæ krzak marihuany., OK, )
		return 1
	)
	return 1
)

CMD:settickforplant(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
	plant, tick
	if(sscanf(params, dd, plant, tick))
	(
		hrp_Tip(playerid, /settickforplant plant tick)
		return 1
	)

	Plants(plant)(plantTicks) = tick
	SendClientMessage(playerid, COLOR_DESC, Ustawiono plant tick.)
	return 1
)

CMD:odczep(playerid,params())
(
	if(!IsPlayerInAnyVehicle(playerid))
	(
		GuiMsg(playerid,Musisz siedzieæ w pojeŸdzie by móc u¿yæ tej komendy.,1)
		return 1
	)

	vehicleid = GetPlayerVehicleID(playerid)
	seat = GetPlayerVehicleSeat(playerid)
	if(seat != 0)
	(
		GuiMsg(playerid,Aby odczepiæ naczepê musisz byæ kierowc¹ tego pojazdu.,1)
		return 1
	)

	Float:Pos(3)
	trailer = GetVehicleTrailer(vehicleid)
	GetVehiclePos(trailer,Pos(0),Pos(1),Pos(2))

	DetachTrailerFromVehicle(vehicleid)
	SetVehiclePos(trailer,Pos(0),Pos(1),Pos(2)-0.25)

	return 1
)

CMD:relog(playerid,params())
(
	if(PlayerCache(playerid)(pLoginEx) ) 0)
	(
		msg(128)
		format(msg,sizeof(msg),Nie mo¿esz tak szybko zmieniæ postaci!\nMusisz odczekaæ %i sekund.,PlayerCache(playerid)(pLoginEx))
		GuiMsg(playerid,msg,1)
		return 1
	)

	buffer(256),charlist(512)
	format(buffer,sizeof(buffer),SELECT char_uid, char_name FROM hrp_characters WHERE char_gid=%i,PlayerCache(playerid)(pGID))
	mysql_query(buffer)
	mysql_store_result()

	while(mysql_fetch_row(buffer,|))
	(
		charUID,charName(32)
		sscanf(buffer,p(|)ds(32),charUID,charName)
		if(!strcmp(charName, PlayerCache(playerid)(pName), true))
		(
			format(charlist,sizeof(charlist),%s\n%i\t\t(CC0000)%s(FFFFFF),charlist,charUID,charName)
		)
		else
		(
			format(charlist,sizeof(charlist),%s\n%i\t\t%s(FFFFFF),charlist,charUID,charName)
		)
	)

	mysql_free_result()
	ShowPlayerDialog(playerid,D_SELECT_CHAR,DIALOG_STYLE_LIST,Twoje postacie,charlist,Wybierz,Anuluj)

	return 1
)

CMD:szukaj(playerid, params())
(
	type(32), varchar(64)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /szukaj (bomby))
		return 1
	)

	if(!strcmp(type, bomby, true))
	(
		if(!IsPlayerInAnyVehicle(playerid))
		(
			GuiMsg(playerid, Musisz siedzieæ w pojeŸdzie by u¿yæ tej komendy., 1)
			return 1
		)

		PlayerCache(playerid)(pBombTime) = 120
		PlayerCache(playerid)(pBombPhase) = BOMB_TYPE_SEARCH
	)

	return 1
)

CMD:rozbroj(playerid, params())
(
	if(!IsPlayerInAnyVehicle(playerid))
	(
		GuiMsg(playerid, Musisz siedzieæ w pojeŸdzie by u¿yæ tej komendy., 1)
		return 1
	)

	if(!PlayerCache(playerid)(pBombFound))
	(
		GuiMsg(playerid, Nie znalaz³eœ ¿adnej bomby w tym pojeŸdzie., 1)
		return 1
	)

	PlayerCache(playerid)(pBombTime) = 45
	PlayerCache(playerid)(pBombPhase) = BOMB_TYPE_DEFUSE

	return 1
)

CMD:strefa(playerid, params())
(
	zone = GetPlayerZoneID(playerid)
	if(GetPlayerZoneID(playerid) == INVALID_ZONE_ID)
	(
		GuiMsg(playerid, Nie jesteœ na terenie ¿adnej ze stref., 1)
		return 1
	)

	if(ZoneInfo(zone)(zOwner) (= 0 && IsPlayerInGroupType(playerid, GROUP_CRIMINAL))
	(
		group_id_fix, string(256)
		for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
		(
			if(PlayerGroup(playerid)(slot)(gUID))
			(
				group_id_fix = PlayerGroup(playerid)(slot)(gID)
				if(GroupData(group_id_fix)(gType) == GROUP_CRIMINAL)
				(
					break
				)
			)
		)
		
		format(string, sizeof(string), » Nabijasz punkty aktywnoœci dla grupy: %s, GroupData(group_id_fix)(gName))
		sendClientPoop(playerid, string)
		
		format(string, sizeof(string), » Iloœæ punktów dzisiaj: %d/380, GetZoneTicks(ZoneInfo(zone)(zUID), GroupData(group_id_fix)(gUID)))
		sendClientPoop(playerid, string)
		
		return 1
	)
	
	if(ZoneInfo(zone)(zOwner) (= 0 && !IsPlayerInGroupType(playerid, GROUP_CRIMINAL))
	(
		GuiMsg(playerid, Nikt nie jest w³aœcicielem tej strefy., 1)
		return 1
	)

	if(!IsPlayerInGroup(playerid, ZoneInfo(zone)(zOwner)))
	(
		GuiMsg(playerid, Nie jesteœ cz³onkiem organizacji, do której nale¿y ten teren., 1)
		return 1
	)

	if(!IsPlayerPermissedGroup(playerid, ZoneInfo(zone)(zOwner), PERM_LEADER))
	(
		GuiMsg(playerid, Musisz posiadaæ uprawnienia lidera, by móc zarz¹dzaæ terenem., 1)
		return 1
	)

	if(ZoneInfo(zone)(zType) == ZONE_TYPE_MAIN)
	(
		GuiMsg(playerid, Nie mo¿esz zarz¹dzaæ stref¹, która jest sercem Twojej organizacji., 1)
		return 1
	)

	// Jezeli przywracasz stary kod to pamietaj o zmianie numeracji w D_ZONE_MENU
	//ShowPlayerDialog(playerid, D_ZONE_MENU, DIALOG_STYLE_LIST, Zarz¹dzanie terenem, 1. Poka¿ informacje\n2. Oddaj teren\n3. Opuœæ teren\n4. SprawdŸ bonus, Wybierz, Anuluj)
	ShowPlayerDialog(playerid, D_ZONE_MENU, DIALOG_STYLE_LIST, Zarz¹dzanie terenem, 1. Poka¿ informacje\n2. Oddaj teren\n3. SprawdŸ bonus, Wybierz, Anuluj)

	return 1
)

CMD:omat(playerid, params())
(
	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)

	object_id = PlayerCache(playerid)(pMoveObject)

	index, color, mat_color, model, txdname(32), txname(32), colorstr(12)
	if(sscanf(params, dhds(32)s(32), index, color, model, txdname, txname))
	(
		hrp_Tip(playerid, /omat (Indeks) (Kolor) (Model) (Rodzina tekstur) (Nazwa tekstury))
		return 1
	)
	if(color != 0)
	(
		mat_color = color
		mat_color |= 0xFF (( 24
		format(colorstr,sizeof(colorstr),%h, color)
	)
	else
	(
		format(colorstr,sizeof(colorstr),FFFFFF)
	)
	if(index )= 10)
	(
		return 1
	)
	SetDynamicObjectMaterial(object_id, index, model, txdname, txname, mat_color)
	buffer(256)
	format(buffer, sizeof(buffer),SELECT * FROM hrp_materials WHERE mat_object = %d AND mat_index = %d, Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID), index)
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	( 
		//update
		mysql_free_result()

		format(buffer, sizeof(buffer), UPDATE hrp_materials SET mat_color = %s, mat_txd = %s, mat_tx = %s, mat_model = %d WHERE mat_object = %d AND mat_index = %d, colorstr, txdname, txname, model, Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID), index)
		mysql_query(buffer)
	)
	else
	(
		//insert
		mysql_free_result()
		
		format(buffer, sizeof(buffer), INSERT INTO hrp_materials (mat_model, mat_txd, mat_tx, mat_color, mat_object, mat_index) VALUES(%d, %s, %s, %s, %d, %d), model, txdname, txname, colorstr, Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID), index)
		mysql_query(buffer)
	)

	return 1
)

CMD:otext(playerid, params())
(
	if(!PlayerCache(playerid)(pPremium))
	(
		GuiMsg(playerid, Aby u¿yæ tej komendy musisz posiadaæ konto premium!, 1)
		return 1
	)

	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)

	//object_id = PlayerCache(playerid)(pMoveObject)
	ShowPlayerDialog(playerid, D_TEXT_MATSIZE, DIALOG_STYLE_LIST, Rozmiar powierzchni, 1. 32x32\n2. 64x32\n3. 64x64\n4. 128x32\n5. 128x64\n6. 128x128\n7. 256x32\n8. 256x64\n8. 256x128\n9. 256x256\n10. 512x64\n11. 512x128\n12. 512x256\n13. 512x512, Wybierz, Anuluj)

	return 1
)

CMD:simon(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid,Nie masz odpowiednich uprawnieñ do wykonania tej komendy.,1)
		return 1
	)

	if(PlayerCache(playerid)(pMoveObject) == INVALID_OBJECT_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie edytujesz aktualnie ¿adnego obiektu., OK, )
		return 1
	)

	object_id = PlayerCache(playerid)(pMoveObject)

	size, color, font(32), text(128)
	if(sscanf(params, dhs(32)s(128), size, color, font, text))
	(
		hrp_Tip(playerid, /simon (size) (color hex) (font) (text))
		hrp_Tip(playerid, Ex: /simon 8 0xFF60C700 LCD Bradstreet Gym)
		return 1
	)

	SetDynamicObjectMaterialText(object_id, 0, text, OBJECT_MATERIAL_SIZE_256x128, font, size, 0, color, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER)
	SendClientMessage(playerid, COLOR_LIGHTRED, Udalo sie!)
	return 1
)

CMD:tlumik(playerid, params())
(
	gunlist(256)

	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID))
		(
			if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID))
			(
				if(ItemInfo(i)(iType) == ITEM_WEAPON)
				(
					if(ItemInfo(i)(iValue1) == 23)
					(
						format(gunlist, sizeof(gunlist), %d. %s, ItemInfo(i)(iUID), ItemInfo(i)(iName))
					)
				)
			)
		)
	)

	if(!strlen(gunlist))
	(
		GuiMsg(playerid, Nie posiadasz ¿adnej broni z za³o¿onym t³umikiem., 1)
		return 1
	)
	else
		ShowPlayerDialog(playerid, D_WEAPON_SILENCER_UNMOUNT, DIALOG_STYLE_LIST, T³umik » zdejmij, gunlist, Wybierz, Anuluj)

	return 1
)

CMD:camper(playerid, params())
(
	if(PlayerCache(playerid)(pJourneyID) != INVALID_VEHICLE_ID)
	(
		// wyjdz
		currentVeh = PlayerCache(playerid)(pJourneyID), Float:Pos(3)
		GetVehiclePos(currentVeh, Pos(0), Pos(1), Pos(2))
		if(CarInfo(currentVeh)(cLocked) == true)
		(
			GuiMsg(playerid, Ten Camper jest zamkniety., 1)
			return 1
		)
		SetPlayerPos(playerid, Pos(0)+2, Pos(1)+2, Pos(2)+3.0)
		SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(currentVeh))
		PlayerCache(playerid)(pJourneyID) = INVALID_VEHICLE_ID
		return 1
	)

	vehid = GetClosestVehicle(playerid, 5.0)
	if(vehid == INVALID_VEHICLE_ID)
	(
		GuiMsg(playerid, W pobli?u nie ma ?adnego wozu kempingowego., 1)
		return 1
	)

	if(GetVehicleModel(vehid) != 508)
	(
		GuiMsg(playerid, W pobli?u nie ma ?adnego Campera., 1)
		return 1
	)
	if(CarInfo(vehid)(cLocked) == true)
	(
		GuiMsg(playerid, Najbli?szy Camper jest zamkniety., 1)
		return 1
	)
	TogglePlayerControllable(playerid, false)
	PlayerCache(playerid)(pDoorFreeze) = 3
	SetPlayerPos(playerid, -1502.1378,-2501.2856,-30.5667) // pozycja na Journey

	SetPlayerVirtualWorld(playerid, CarInfo(vehid)(cUID)+9999)
	PlayerCache(playerid)(pJourneyID) = vehid

	return 1
)

CMD:boat(playerid, params())
(
	if(PlayerCache(playerid)(pJourneyID) != INVALID_VEHICLE_ID)
	(
		// wyjdz
		currentVeh = PlayerCache(playerid)(pJourneyID), Float:Pos(3)
		GetVehiclePos(currentVeh, Pos(0), Pos(1), Pos(2))
		if(CarInfo(currentVeh)(cLocked) == true)
		(
			GuiMsg(playerid, Ta 3ódÅº jest zamkniety., 1)
			return 1
		)
		SetPlayerPos(playerid, Pos(0), Pos(1), Pos(2)+5.0)
		SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(currentVeh))
		PlayerCache(playerid)(pJourneyID) = INVALID_VEHICLE_ID
		return 1
	)

	vehid = GetClosestVehicle(playerid, 5.0)
	if(vehid == INVALID_VEHICLE_ID)
	(
		GuiMsg(playerid, W pobli?u nie ma ?adnej 3odzi., 1)
		return 1
	)

	if(GetVehicleModel(vehid) != 484 && GetVehicleModel(vehid) != 454)
	(
		GuiMsg(playerid, W pobli?u nie ma ?adnej 3odzi., 1)
		return 1
	)
	if(CarInfo(vehid)(cLocked) == true)
	(
		GuiMsg(playerid, Najbli?sza 3ódÅº jest zamknieta., 1)
		return 1
	)
	TogglePlayerControllable(playerid, false)
	PlayerCache(playerid)(pDoorFreeze) = 3
	if(GetVehicleModel(vehid) == 484)
	(
		SetPlayerPos(playerid, -28.2790,-376.6924,-30.8827) // pozycja na Marquis
	)
	if(GetVehicleModel(vehid) == 454)
	(
		SetPlayerPos(playerid, -68.8693,-448.0288,-31.0008) // pozycja na Tropic
	)

	SetPlayerVirtualWorld(playerid, CarInfo(vehid)(cUID)+9999)
	PlayerCache(playerid)(pJourneyID) = vehid

	return 1
)

CMD:sprzedaj(playerid, params())
(
	// Ryby
	if(IsPlayerInRangeOfPoint(playerid, 5.0, 621.6731, -1854.5099, 5.4538))
	(
		if(PlayerCache(playerid)(pDailyIncome) )= MAX_DAILY_INCOME && !IsPlayerInGroupType(playerid, GROUP_FISHING))
		(
			GuiMsg(playerid, Wyczerpa³eœ dzisiejszy limit dochodu z prac dorywczych.\nWróæ jutro., 1)
			return 1
		)

		ShowPlayerDialog(playerid, D_FISH_INFO, DIALOG_STYLE_MSGBOX, Handlarz, Mê¿czyzna, do którego nale¿y to stoisko skupuje ryby.\nCzy chcesz rozpocz¹æ z nim handel?, Tak, Nie)
	)

	// Roœlinki - jeszcze nie dodane
	return 1
)

CMD:czysc(playerid, params())
(
	/*if(IsPlayerInRangeOfPoint(playerid, 550.0, 2487.8108,-1666.8884,13.3438))
	(
		GuiMsg(playerid, Nie mo¿esz tutaj usuwaæ tagów., 1)
		return 1
	)*/
	
	zoneid = GetPlayerZoneID(playerid)
	if(ZoneInfo(zoneid)(zOwner) ) 0)
	(
		GuiMsg(playerid, Nie mo¿esz tutaj usuwaæ tagów., 1)
		return 1
	)

	hasWeapon = 0
	for(i = 0 i ( 3 i++) (
		if(WeaponCache(playerid)(i)(pWeaponID) ) 0)
			hasWeapon = 1
	)

	if(hasWeapon ) 0)
	(
		GuiMsg(playerid, Nie mo¿esz mieæ ¿adnej broni w u¿yciu!, 1)
		return 1
	)

	if(PlayerCache(playerid)(pDailyIncome) )= MAX_DAILY_INCOME)
	(
		GuiMsg(playerid, Wyczerpa³eœ dzisiejszy limit dochodu z prac dorywczych.\nWróæ jutro., 1)
		return 1
	)

	if(PlayerCache(playerid)(pScouring))
	(
		GuiMsg(playerid, Jesteœ w trakcie usuwania innego taga!, 1)
		return 1
	)

	if(PlayerCache(playerid)(pJob) != JOB_SCOURER)
	(
		GuiMsg(playerid, Nie posiadasz pracy dorywczej czyœciciela tagów., 1)
		return 1
	)

	objectid = GetClosestObject(playerid, 5.0)
	modelid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID)

	if(modelid != 18661)
	(
		GuiMsg(playerid, W pobli¿u nie znaleziono ¿adnego taga., 1)
		return 1
	)
	else
	(
		for(i = 0  i ( MAX_PLAYERS i++)
		(
			if(playerid == i)
				continue

			if(PlayerCache(i)(pScouredID) == objectid)
			(
				GuiMsg(playerid, Ktoœ usuwa ju¿ tego taga., 1)
				return 1
			)
		)

		PlayerCache(playerid)(pScouredID) = objectid
		PlayerCache(playerid)(pScouring) = true
		GuiMsg(playerid, Rozpocz¹³eœ w³aœnie usuwanie taga.\nPsikaj sprayem w stronê taga by go usun¹æ., 0)

		GivePlayerWeapon(playerid, 41, 1000)
	)



	return 1
)

/*
CMD:bilard(playerid, params())
(
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz tera zacz¹æ gry w bilard., OK, )
		return 1
	)
	object_id = GetClosestObject(playerid)
	if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_POOL_TABLE)
	(
 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnego sto³u bilardowego w pobli¿u., OK, )
   		return 1
	)
	Float:ObjectPosX, Float:ObjectPosY, Float:ObjectPosZ,
		Float:ObjectRotX, Float:ObjectRotY, Float:ObjectRotZ

	GetDynamicObjectPos(object_id, ObjectPosX, ObjectPosY, ObjectPosZ)
	GetDynamicObjectRot(object_id, ObjectRotX, ObjectRotY, ObjectRotZ)

	Float:Distance

	Distance = floatsqroot(floatpower(ObjectPosX + 0.3 - ObjectPosX, 2) + floatpower(ObjectPosY - ObjectPosY, 2))

	ObjectPosX += ((Distance * floatsin(90 - ObjectRotZ, degrees) / floatsin(90, degrees)))
	ObjectPosY += ((Distance * floatsin(ObjectRotZ, degrees) / floatsin(90, degrees)))

	CreateObject(2995, ObjectPosX, ObjectPosY, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)

	for(i = 0 i ( 2 i++)
	(
 		GetObjectPos(object_id, ObjectPosX, ObjectPosY, ObjectPosZ)

		object_id = CreateObject(2996 + i, ObjectPosX + 0.05, ObjectPosY + 0.05, ObjectPosZ, 0, 0, 0, 50.0)
		object_id = CreateObject(2998 + i, ObjectPosX + 0.05, ObjectPosY - 0.05, ObjectPosZ, 0, 0, 0, 50.0)
		object_id = CreateObject(3000 + i, ObjectPosX + 0.05, ObjectPosY + 0.05, ObjectPosZ, 0, 0, 0, 50.0)
	)

	for(i = 0 i ( 2 i++)
	(
		GetObjectPos(object_id, ObjectPosX, ObjectPosY, ObjectPosZ)

		object_id = CreateObject(3100 + i, ObjectPosX + 0.05, ObjectPosY + 0.05, ObjectPosZ, 0, 0, 0, 50.0)
		object_id = CreateObject(3102 + i, ObjectPosX + 0.05, ObjectPosY - 0.05, ObjectPosZ, 0, 0, 0, 50.0)
		object_id = CreateObject(3104 + i, ObjectPosX + 0.05, ObjectPosY + 0.05, ObjectPosZ, 0, 0, 0, 50.0)

	)

	for(i = 0 i ( 14 i++)
	(
		GetObjectPos(object_id, ObjectPosX, ObjectPosY, ObjectPosZ)

		if(i == 0)
		(
			object_id = CreateObject(2996 + i, ObjectPosX + 0.05, ObjectPosY + 0.05, ObjectPosZ, 0, 0, 0, 50.0)
		)

		if(i ) 0 && i ( 2)
		(
			object_id = CreateObject(2996 + i, ObjectPosX + 0.05, ObjectPosY + 0.05, ObjectPosZ, 0, 0, 0, 50.0)
			object_id = CreateObject(3100 + i, ObjectPosX + 0.05, ObjectPosY - 0.05, ObjectPosZ, 0, 0, 0, 50.0)
		)

		if(i ) 2 && i ( 5)
		(
			object_id = CreateObject(2996 + i, ObjectPosX + 0.05, ObjectPosY + 0.05, ObjectPosZ, 0, 0, 0, 50.0)
			object_id = CreateObject(3100 + i, ObjectPosX + 0.05, ObjectPosY - 0.05, ObjectPosZ, 0, 0, 0, 50.0)
		)
	)

	CreateObject(3100, ObjectPosX + 0.3, ObjectPosY, ObjectPosZ + 0.95, 0, 0, 0, 50.0)

	CreateObject(3101, ObjectPosX + 0.35, ObjectPosY + 0.05, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(3102, ObjectPosX + 0.35, ObjectPosY - 0.05, ObjectPosZ + 0.95, 0, 0, 0, 50.0)

	CreateObject(3103, ObjectPosX + 0.40, ObjectPosY + 0.10, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(3104, ObjectPosX + 0.40, ObjectPosY - 0.10, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(3105, ObjectPosX + 0.40, ObjectPosY, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)

	CreateObject(2995, ObjectPosX + 0.45, ObjectPosY + 0.15, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(2996, ObjectPosX + 0.45, ObjectPosY - 0.15, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(2997, ObjectPosX + 0.45, ObjectPosY + 0.05, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(2998, ObjectPosX + 0.45, ObjectPosY - 0.05, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)

	CreateObject(2999, ObjectPosX + 0.50, ObjectPosY + 0.20, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(3000, ObjectPosX + 0.50, ObjectPosY - 0.20, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(3001, ObjectPosX + 0.50, ObjectPosY + 0.10, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(3002, ObjectPosX + 0.50, ObjectPosY - 0.10, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)
	CreateObject(3106, ObjectPosX + 0.50, ObjectPosY, ObjectPosZ + 0.95, 0, 0, ObjectRotZ, 50.0)

	return 1
)*/

CMD:kop(playerid, params())
(
	if(!IsPlayerInRangeOfPoint(playerid, 50.0, 549.2377, -564.3649, 22.4066))
	(
		GuiMsg(playerid, Musisz udaæ siê na miejsce, w którym mo¿na wykopaæ jakieœ robaki., 1)
		return 1
	)

	PlayerCache(playerid)(pPicking) = 135
	GuiMsg(playerid, Rozpocz¹³eœ w³aœnie kopaæ w poszukiwaniu robaków.\nPoczekaj do koñca czasu, by wyci¹gn¹æ kilka z nich., 0)

	return 1
)

CMD:urzad(playerid, params())
(
	if(PlayerCache(playerid)(pCourse))
	(
		GuiMsg(playerid, Jesteœ w trakcie kursu, zakoñcz go by u¿yæ tej komendy., 1)
		return 1
	)

	if(PlayerCache(playerid)(pBW))
	(
		GuiMsg(playerid, Nie mo¿esz u¿yæ tej komendy bêd¹c nieprzytomnym., 1)
		return 1
	)

	doorid = GetPlayerDoorID(playerid)
	if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
	(
		GuiMsg(playerid, Musisz znajdowaæ siê w urzêdzie by u¿yæ tej komendy., 1)
		return 1
	)

	group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
	if(GroupData(group_id_fix)(gType) != GROUP_DRIVING)
	(
		GuiMsg(playerid, Musisz znajdowaæ siê w urzêdzie by u¿yæ tej komendy., 1)
		return 1
	)

	if(PlayerCache(playerid)(pGamePoints) ( 50)
	(
		GuiMsg(playerid, Nie mo¿esz u¿yæ teraz tej komendy, wróæ gdy przegrasz minimum 5H., 1)
		return 1
	)

	ShowPlayerDialog(playerid, D_HALL, DIALOG_STYLE_LIST, Urz¹d miasta, 1. PodejdŸ do egzaminu\n2. Wyrób dokument, Wybierz, Anuluj)

	return 1
)

CMD:zamieszkaj(playerid, params())
(
	count = 0
	for(i = 0  i ( MAX_DOORS i++)
	(
		if(DoorData(i)(dUID) != 0)
		(
			if(DoorData(i)(dOwnerType) == OWNER_PLAYER && DoorData(i)(dOwner) == PlayerCache(playerid)(pUID))
				count++
		)
	)

	if(count ) 1)
	(
		GuiMsg(playerid, Posiadasz zbyt wiele nieruchomoœci, jeœli chcesz mieæ wiêcej - skontaktuj siê z administratorem., 1)
		return 1
	)

	if(GetClosestDoor(playerid, 5.0) == INVALID_DOOR_ID)
	(
		GuiMsg(playerid, Nie znaleziono ¿adnych drzwi w pobli¿u!, 1)
		return 1
	)

	doorid = GetClosestDoor(playerid, 5.0)
	if(DoorData(doorid)(dCost) (= 0)
	(
		GuiMsg(playerid, Ten budynek nie jest na sprzeda¿., 1)
		return 1
	)

	if(DoorData(doorid)(dOwnerType) != OWNER_NONE || DoorData(doorid)(dOwner) != 0)
	(
		GuiMsg(playerid, Ten budynek nie jest na sprzeda¿., 1)
		return 1
	)

	if(PlayerCache(playerid)(pCash) ( DoorData(doorid)(dCost))
	(
		GuiMsg(playerid, Nie posiadasz tyle gotówki!, 1)
		return 1
	)

	string(256)
	format(string, sizeof(string), Czy na pewno chcesz kupiæ nieruchomoœæ %s za $%d?, DoorData(doorid)(dName), DoorData(doorid)(dCost))
	ShowPlayerDialog(playerid, D_BUY_HOUSE, DIALOG_STYLE_MSGBOX, Zakup budynku, string, Akceptuj, Odrzuæ)
	MainPlayerTable(playerid) = doorid

	return 1
)

CMD:podglad(playerid, params())
(
	if(PlayerCache(playerid)(pViewDoorID) != INVALID_DOOR_ID)
	(
		GuiMsg(playerid, Jesteœ w trakcie podgl¹du drzwi, poczekaj do koñca!, 0)
		return 1
	)

	if(GetClosestDoor(playerid, 5.0) == INVALID_DOOR_ID)
	(
		GuiMsg(playerid, W pobli¿u nie ma ¿adnych drzwi., 1)
		return 1
	)

	doorid = GetClosestDoor(playerid, 5.0)
	if(DoorData(doorid)(dCost) (= 0)
	(
		GuiMsg(playerid, Te drzwi nie posiadaj¹ dostêpnego podgl¹du., 1)
		return 1
	)

	PlayerCache(playerid)(pViewDoorID) = doorid
	PlayerCache(playerid)(pViewTime) = 15

	SetPlayerPos(playerid, DoorData(doorid)(dExitX), DoorData(doorid)(dExitY), DoorData(doorid)(dExitZ))
	SetPlayerInterior(playerid, DoorData(doorid)(dExitInt))
	SetPlayerVirtualWorld(playerid, 50000 + PlayerCache(playerid)(pUID) + random(500))

	return 1
)

CMD:wizjer(playerid, params())
(
	doorid = GetPlayerDoorID(playerid)
	if(doorid == INVALID_DOOR_ID)
	(
		GuiMsg(playerid, Musisz byæ w budynku by u¿yæ tej komendy., 1)
		return 1
	)

	perList(512)
	for(i = 0 i ( MAX_PLAYERS i++)
	(
		if(DoorData(doorid)(dEnterVW) != GetPlayerVirtualWorld(i))
			continue

		if(!IsPlayerInRangeOfPoint(i, 5.0, DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ)))
			continue

		format(perList, sizeof(perList), %d. %s, i, PlayerName(i))
	)

	if(!strlen(perList))
	(
		GuiMsg(playerid, Nie ma nikogo w pobli¿u drzwi., 1)
		return 1
	)

	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Widoczne osoby, perList, OK, )

	return 1
)

CMD:stacja(playerid, params())
(
	if(PlayerCache(playerid)(pStation) ) 0)
	(
		TextDrawHideForPlayer(playerid, Text:TextDrawRadio(PlayerCache(playerid)(pStation)))
		TextDrawShowForPlayer(playerid, Text:TextDrawSanNews)
		GuiMsg(playerid, Wy³¹czy³eœ stacjê radiow¹., 0)
		PlayerCache(playerid)(pStation) = 0
		return 1
	)
	else
	(
		stationList(512)

		for(i = 1 i ( sizeof(RadioData) i++)
		(
			if(RadioData(i)(gUID))
			(
				format(stationList, sizeof(stationList), %s\n%d. %s (%d), stationList, i, RadioData(i)(gTag), RadioData(i)(gUID))
			)
		)

		if(!strlen(stationList))
		(
			GuiMsg(playerid, Nie znaleziono ¿adnych stacji radiowych., 1)
			return 1
		)

		ShowPlayerDialog(playerid, D_SELECT_RADIOSTATION, DIALOG_STYLE_LIST, Radiostacje, stationList, Wybierz, Anuluj)
	)

	return 1
)
/*
CMD:nadaj(playerid, params())
(
	if(!IsPlayerInGroupType(playerid, GROUP_RADIO))
	(
		GuiMsg(playerid, Nie mo¿esz u¿ywaæ tej komendy., 1)
		return 1
	)

	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_RADIO)
	(
		GuiMsg(playerid, Musisz byæ na s³u¿bie radia by u¿ywaæ tej komendy., 1)
		return 1
	)

	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /nadaj (reklame | live | wywiad))
	 	return 1
	)

	if(!strcmp(type, live, true))
	(
		if(PlayerCache(playerid)(pStationLive))
		(
			PlayerCache(playerid)(pStationLive) = false
			GuiMsg(playerid, Zakoñczy³eœ nadawanie live., 0)

			string(128)
			format(string, sizeof(string), %s ~)~ w radio leci standardowy blok muzyczny, GroupData(group_id_fix)(gTag))

			for(i = 0  i ( MAX_PLAYERS i++)
			(
				if(PlayerCache(i)(pStation) == GroupData(group_id_fix)(gUID))
				(
					PlayerTextDrawSetString(i, TextDrawRadio(i), string)
				)
			)

			return 1
		)

		for(i = 0  i ( MAX_PLAYERS i++)
		(
			if(PlayerCache(i)(pStationLive) && GroupData(GetPlayerDutyGroupID(i))(gType) == GROUP_RADIO && GetPlayerDutyGroupID(i) == group_id_fix)
			(
				GuiMsg(playerid, Ktoœ inny z Twojej stacji teraz nadaje., 1)
				return 1
			)
		)

		string(128)
		format(string, sizeof(string), %s ~)~ trwa transmisja na zywo, GroupData(group_id_fix)(gTag))
		PlayerCache(playerid)(pStationLive) = true

		for(i = 0  i ( MAX_PLAYERS i++)
		(
			if(PlayerCache(i)(pStation) == GroupData(group_id_fix)(gUID))
			(
				PlayerTextDrawSetString(i, TextDrawRadio(i), string)
			)
		)
	)

	return 1
)
*/
/*
	*	Komis skryptowy, wycofany ze wzglêdu na wprowadzenie tych
	* 	kontrolowanych przez fizyczne osoby.
*/
/*CMD:komis(playerid, params())
(
	bool:checkbug = false
	if(gettime() - LogTime(playerid) ) 60)
		checkbug= true
		
	if(!checkbug)
	(
		GuiMsg(playerid, Nie mo¿esz tak szybko u¿yæ tej komendy., 0)
		return 1
	)
	
	if(!IsPlayerInRangeOfPoint(playerid, 15.0, 2131.8691,-1150.8456,24.1132) || GetPlayerVirtualWorld(playerid) != 0)
	(
		GuiMsg(playerid, Nie znajdujesz siê na terenie komisu., 1)
		return 1
	)
	
	list(512)
	for(i = 0  i ( sizeof(UsedCars) i++)
	(
		format(list, sizeof(list), %s\n%d. %s ($%d), list, i, UsedCars(i)(uName), UsedCars(i)(uCost))
	)
	
	ShowPlayerDialog(playerid, D_USED_LIST, DIALOG_STYLE_LIST, Komis aut, list, Wybierz, Zamknij)
	return 1
)*/

// handluj z tym
CMD:handel(playerid, params())
(
	if(PlayerCache(playerid)(pCorner) != -1)
	(
		PlayerCache(playerid)(pDrugDealing) = false
		PlayerCache(playerid)(pSelling) = false
		PlayerCache(playerid)(pCorner) = -1
		DisablePlayerCheckpoint(playerid)
		ApplyAnimation(playerid, CARRY, crry_prtial, 4.1, 0, 0, 0, 0, 0)
		
		GuiMsg(playerid, Przerwa³eœ proces sprzeda¿y narkotyków., 0)
		return 1
	)
/*
	if(PlayerCache(playerid)(pDailyDrugs) ) 14)
	(
		GuiMsg(playerid, Wyczerpa³eœ limit dziennej sprzeda¿y narkotyków.\nWróæ nastêpnego dnia., 1)
		return 1
	)
*/	
	count = 0
	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID))
		(
			if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID) && ItemInfo(i)(iType) == ITEM_DRUG)
			(
				count++
			)
		)
	)
	
	if(!count)
	(
		GuiMsg(playerid, Nie posiadasz przy sobie ¿adnego narkotyku.\nNie mo¿esz rozpocz¹æ sprzeda¿y., 1)
		return 1
	)
	
	// Je¿eli nie ma nikogo z LSPD w grze to nie mo¿na akceptowaæ
	count = 0
	foreach(Player, i)
	(
		if(PlayerCache(i)(pUID))
		(
			if(PlayerCache(i)(pGroupDuty))
			(
				group_id_fix = GetGroupID(PlayerCache(i)(pGroupDuty))
				if(GroupData(group_id_fix)(gType) == GROUP_POLICE)
				(
					count += 1
				)
			)
		)
	)
	
	if(!count)
	(
		GuiMsg(playerid, Nie mo¿esz teraz zacz¹æ handlowaæ., 1)
		return 1
	)
	
	playerzone = GetPlayerZoneID(playerid)
	if(playerzone == INVALID_ZONE_ID || ZoneInfo(playerzone)(zOwner) (= 0)
	(
		GuiMsg(playerid, Aby rozpoczac handel musisz stac na jednej ze stref gangowych., 1)
		return 1
	)
	
	occupied = false
	for(i = 0 i ( MAX_CORNERS i++)
	(
		if(CornerInfo(i)(cOwner) == ZoneInfo(playerzone)(zOwner))
		(
			if(countCornerDealers(i) )= 1)
			(
				occupied = true // ktoÅ› handluje na cornerze na strefie tego gangu
			)
		)
	)
	
	if(occupied)
	(
		GuiMsg(playerid, Obecnie ktos handluje na strefach tego gangu., 1)
		return 1
	)
	
	SelectRandomCorner(playerid)
	
	cornerid = PlayerCache(playerid)(pCorner)
	
	zoneowner = CornerInfo(cornerid)(cOwner)
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
	if(PlayerCache(playerid)(pDailyDrugs) ) DailyDrugsLimit)
	(
		GuiMsg(playerid, Wyczerpa³eœ limit dziennej sprzeda¿y narkotyków.\nWróæ nastêpnego dnia., 1)
		PlayerCache(playerid)(pCorner) = -1
		return 1
	)
	SetPlayerCheckpoint(playerid, CornerInfo(cornerid)(cPosX), CornerInfo(cornerid)(cPosY), CornerInfo(cornerid)(cPosZ), 2.0)
	PlayerCache(playerid)(pDrugDealing) = true
	
	GuiMsg(playerid, Udaj siê we wskazane na mapie miejsce, by rozpocz¹æ proces sprzeda¿y narkotyku.\nWystarczy stan¹æ w miejscu, reszty dowiesz siê bêd¹c tam!, 0)
	return 1
)

CMD:namierz(playerid, params())
(
	if(!IsPlayerInGroupType(playerid, GROUP_FBI))
	(
		GuiMsg(playerid, Brak uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	if(!IsPlayerInAnyVehicle(playerid))
	(
		GuiMsg(playerid, Musisz znajdowaæ siê w pojeŸdzie by u¿yæ tej komendy., 1)
		return 1
	)
	
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_FBI)
	(
		GuiMsg(playerid, Musisz byæ na s³u¿bie grupy, by u¿yæ tej komendy., 1)
		return 1
	)
	
	vehicle_id = GetPlayerVehicleID(playerid)
	if(CarInfo(vehicle_id)(cOwnerType) == OWNER_GROUP && CarInfo(vehicle_id)(cOwner) == GroupData(group_id_fix)(gUID))
	(
		phone_number
		if(sscanf(params, d, phone_number))
		(
			hrp_Tip(playerid, /namierz (Numer telefonu))
			return 1
		)
		
		owner_id = INVALID_PLAYER_ID
		foreach(Items, i)
		(
			if(ItemInfo(i)(iUID))
			(
				if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iUsed) == 1 && ItemInfo(i)(iType) == ITEM_PHONE)
				(
					if(ItemInfo(i)(iValue1) == phone_number)
					(
						owner_id = GetPlayerID(ItemInfo(i)(iOwner))
						break
					)
				)
			)
		)
		
		if(owner_id == INVALID_PLAYER_ID)
		(
			GuiMsg(playerid, Nie znaleziono takiego telefonu w sieci.\nByæ mo¿e telefon jest wy³¹czony, lub nie ma takiego numeru., 1)
			return 1
		)
		
		if(GetPlayerVirtualWorld(owner_id) != 0)
		(
			GuiMsg(playerid, Nie znaleziono takiego telefonu w sieci.\nByæ mo¿e telefon jest wy³¹czony, lub nie ma takiego numeru., 1)
			return 1
		)
		
		PlayerCache(playerid)(pSearchingTime) = 10 + random(30)
		PlayerCache(playerid)(pSearching) = PlayerCache(owner_id)(pUID)
		GuiMsg(playerid, Rozpoczêto proces namierzania telefonu.\nGdy up³ynie czas oczekiwania na mapie pojawi siê znacznik., 0)
	)
	else
	(
		GuiMsg(playerid, Musisz znajdowaæ siê w pojeŸdzie podpisanym pod grupê., 1)
		return 1
	)
	
	return 1
)

// Near Objects -) 
// /obiektywpoblizu 
// /nob 15 -)
CMD:ob(playerid, params())
(
	Float:radius, object_list(1024)
	if(sscanf(params, f, radius))
	(
		hrp_Tip(playerid, /ob (Metry))
		return 1
	)
	
	if(GetPlayerVirtualWorld(playerid) != 0)
	(
		doorid = GetPlayerDoorID(playerid)
		if(doorid != INVALID_DOOR_ID)
		(
			owner_type = DoorData(doorid)(dOwnerType)
			if(owner_type == OWNER_NONE)
			(
				GuiMsg(playerid, Te drzwi nie nale¿¹ do Ciebie., 1)
				return 1
			)
			else if(owner_type == OWNER_GROUP)
			(
				group_uid = DoorData(doorid)(dOwner)
				if(!IsPlayerInGroup(playerid, group_uid))
				(
					GuiMsg(playerid, Te drzwi nie nale¿¹ do Twojej grupy., 1)
					return 1
				)		
			)
			else if(owner_type == OWNER_PLAYER)
			(
				if(PlayerCache(playerid)(pUID) != DoorData(doorid)(dOwner))
				(
					GuiMsg(playerid, Te drzwi nie nale¿¹ do Ciebie., 1)
					return 1
				)
			)
			
			for(object_id = 0  object_id ( MAX_OBJECTS object_id++)
			(
				// obiekt jest na tym samym œwiecie co gracz, który wpisa³ komendê
				if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID) == GetPlayerVirtualWorld(playerid))
				(
					Float:Pos(3)
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_X, Pos(0))
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_Y, Pos(1))
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_Z, Pos(2))
					
					if(IsPlayerInRangeOfPoint(playerid, radius, Pos(0), Pos(1), Pos(2)))
					(
						format(object_list, sizeof(object_list), %s\n#%d. %d, object_list, object_id, Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_MODEL_ID))
					)
				)
			)
			
			// dialog
			if(!strlen(object_list))
			(
				GuiMsg(playerid, W Twoim pobli¿u nie ma ¿adnych obiektów., 0)
				return 1
			)
			
			ShowPlayerDialog(playerid, D_NEAR_OBJECTS, DIALOG_STYLE_LIST, Obiekty w Twoim pobli¿u, object_list, Wybierz, Zamknij)
		)
		else
		(
			GuiMsg(playerid, Nie znajdujesz siê w budynku., 1)
			return 1
		)
	)
	else
	(
		// jest na dworzu
		// 1 = administrator
		if(PlayerCache(playerid)(pAdmin) != 1)
		(
			GuiMsg(playerid, Nie masz uprawnieñ do u¿ycia tej komendy na dworzu., 1)
			return 1
		)
		
		for(object_id = 0  object_id ( MAX_OBJECTS object_id++)
		(
			// obiekt jest na tym samym œwiecie co gracz, który wpisa³ komendê
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID) == GetPlayerVirtualWorld(playerid))
			(
				Float:Pos(3)
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_X, Pos(0))
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_Y, Pos(1))
				Streamer_GetFloatData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_Z, Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid, radius, Pos(0), Pos(1), Pos(2)))
				(
					format(object_list, sizeof(object_list), %s\n#%d. $d, object_list, object_id, Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_MODEL_ID))
				)
			)
		)
	)
	
	if(!strlen(object_list))
	(
		GuiMsg(playerid, W Twoim pobli¿u nie ma ¿adnych obiektów., 0)
		return 1
	)
	
	ShowPlayerDialog(playerid, D_NEAR_OBJECTS, DIALOG_STYLE_LIST, Obiekty w Twoim pobli¿u, object_list, Wybierz, Zamknij)
	return 1
)

CMD:sparing(playerid, params())
(
/*	if(!IsPlayerInGroupType(playerid, GROUP_CRIMINAL))
	(
		GuiMsg(playerid, Aby zaprosiæ kogoœ do sparingu, musisz nale¿eæ do grupy przestêpczej., 1)
		return 1
	) */
	
	target_id	// gracz którego zapraszamy do sparingu
	if(sscanf(params, d, target_id))
	(
		hrp_Tip(playerid, /sparing (ID gracza) - zaprasza gracza do sparingu)
		return 1
	)
	
	if(!Logged(target_id))
	(
		GuiMsg(playerid, Podano b³êdne ID Gracza., 1)
		return 1
	)
	
	if(target_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz sparowaæ ze soba., OK, )
		return 1
	)
	
	if(PlayerCache(playerid)(pSparing) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid, Nie mo¿esz zaprosiæ nikogo do sparingu podczas trwania innego., 1)
		return 1
	)
	
	if(PlayerCache(target_id)(pSparing) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid, Ten gracz jest ju¿ podczas sparingu, poczekaj a¿ skoñczy., 1)
		return 1
	)
	
	if(GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(target_id))
	(
		GuiMsg(playerid, Osoba, któr¹ zapraszasz jest zbyt daleko od Ciebie., 1)
		return 1
	)
	
	Float:Pos(3)
	GetPlayerPos(target_id, Pos(0), Pos(1), Pos(2))
	
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, Pos(0), Pos(1), Pos(2)))
	(
		GuiMsg(playerid, Osoba, któr¹ zapraszasz jest zbyt daleko od Ciebie., 1)
		return 1
	)
	
	message(128)
	format(message, sizeof(message), Gracz %s zaprosi³ Cie do sparingu, czy chcesz akceptowaæ jego ofertê?, PlayerName(playerid))
	ShowPlayerDialog(target_id, D_SPARING_INVITE, DIALOG_STYLE_MSGBOX, Sparing » zaproszenie, message, Akceptuj, Odrzuæ)
	MainPlayerTable(target_id) = playerid
	
	format(message, sizeof(message), Oferta zosta³a wys³ana do %s. Poczekaj na jego odpowiedŸ., PlayerName(target_id))
	SendClientMessage(playerid, COLOR_INFO, message)
	
	return 1
)

CMD:biznesy(playerid, params())
(
	if(!strcmp(params, ukryj, true))
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
		
		PlayerCache(playerid)(pBusinessShow) = false
		GuiMsg(playerid, Ukry³eœ ikonki biznesów., 0)
		return 1
	)
	
	
	if(PlayerCache(playerid)(pFlood) ) 0)
	(
		GuiMsg(playerid,Wyst¹pi³ b³¹d, musisz chwilê odczekaæ zanim u¿yjesz tej komendy.,0)
		return 1
	)
	
	if(!strcmp(params, skrypt, true))
	(
		PlayerCache(playerid)(pFlood) = 0
		PlayerCache(playerid)(pBusinessShow) = true	
	)
	else
	(
		hrp_Tip(playerid, /biznesy (ukryj))
	)
	
	PlayerCache(playerid)(pBusinessShow) = true
	
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
	
	count = 0
	
	foreach(Player, i)
	(
		if(PlayerCache(i)(pGroupDuty))
		(
			group_id_fix = GetPlayerDutyGroupID(i)
			foreach(Doors, doorid)
			(
				if(DoorData(doorid)(dUID) && DoorData(doorid)(dEnterVW) == 0)
				(
					if(DoorData(doorid)(dOwnerType) == OWNER_GROUP && GetGroupID(DoorData(doorid)(dOwner)) == group_id_fix)
					(
						group_type = GroupData(group_id_fix)(gType)
						if(group_type != GROUP_FBI && group_type != GROUP_CRIMINAL && group_type != GROUP_MAFIA && group_type != GROUP_CARTEL && group_type != GROUP_POLICE && group_type != GROUP_FIREDEPT)
						(
							count += 1
							switch(group_type)
							(
								case GROUP_NEWS:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 52, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
								case GROUP_FIREDEPT:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 20, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
								case GROUP_GYM:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 54, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
								case GROUP_CARDEALER:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 55, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
								case GROUP_WORKSHOP:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 27, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
								case GROUP_BAR:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 17, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
								case GROUP_POLICE:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 30, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
								case GROUP_AUTOSALE:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 55, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
								case GROUP_PAINTBALL:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 18, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
								default:
									CreateDynamicMapIcon(DoorData(doorid)(dEnterX), DoorData(doorid)(dEnterY), DoorData(doorid)(dEnterZ), 31, 0, -1, -1, playerid, 400.0, MAPICON_GLOBAL)
							)
						)
					)
				)
			)
		)
	)
	
	if(count == 0)
	(
		GuiMsg(playerid, Nie znaleziono ¿adnego biznesu z aktywnym pracownikiem na s³u¿bie., 1)
		return 1
	)
	
	PlayerCache(playerid)(pFlood) += 10
	Streamer_Update(playerid)
	return 1
)

CMD:wycisz(playerid, params())
(
	if(PlayerCache(playerid)(pCuffed) != INVALID_PLAYER_ID && PlayerCache(playerid)(pCuffedStill) != INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz u¿ywaæ ekwipunku podczas gdy jesteœ skuty., OK, )
		return 1
	)
	
	if(PlayerCache(playerid)(pBW) || PlayerCache(playerid)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skorzystaæ teraz z tej komendy., OK, )
		return 1
	)
	
	if(!PlayerCache(playerid)(pPhoneNumber))
  	(
   		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz ¿adnego telefonu w u¿yciu.\nSkorzystaj z komendy /u, by w³¹czyæ telefon., OK, )
   		return 1
   	)
	
	if(PlayerCache(playerid)(pPhoneMuted))
	(
		PlayerCache(playerid)(pPhoneMuted) = false
		GameTextForPlayer(playerid, ~w~Telefon ~g~odciszony, 4000, 6)
	)
	else
	(
		PlayerCache(playerid)(pPhoneMuted) = true
		GameTextForPlayer(playerid, ~w~Telefon ~r~wyciszony, 4000, 6)
	)
	
	return 1
)

CMD:komis(playerid, params())
(
  	type(32), varchar(32)
  	if(sscanf(params, s(32)S()(32), type, varchar))
  	(
  		hrp_Tip(playerid, /komis (oferuj | cennik))
  		return 1
  	)
  	if(!strcmp(type, oferuj, true))
  	(
  		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_AUTOSALE) 
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		if(!IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
		giveplayer_id
		if(sscanf(varchar, d, giveplayer_id))
		(
			hrp_Tip(playerid, /komis oferuj (ID gracza))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
  		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w komisie samochodowym., OK, )
	   		return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w komisie samochodowym., OK, )
	   		return 1
		)
		MainPlayerTable(playerid) = giveplayer_id
		ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategoriê, 1. Jednoœlady\n2. Trzydrzwiowe\n3. Piêciodrzwiowe\n4. Furgonetki i ciê¿arówki\n5.Sportowe\n6. Lowridery \n7  Pickupy\n8  Lataj¹ce\n9  P³ywaj¹ce\n10  Pozosta³e , Wybierz, Anuluj)
		//ShowPlayerDialog(playerid, D_SALON_OFFER_CAT, DIALOG_STYLE_LIST, Wybierz kategoriê, 1. Jednoœlady\n2. Trzydrzwiowe\n3. Piêciodrzwiowe\n4. Furgonetki i ciê¿arówki\n5. Pozosta³e, Wybierz, Anuluj)
		return 1
  	)
  	if(!strcmp(type, cennik, true))
  	(
  		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w komisie samochodowym., OK, )
	   		return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w komisie samochodowym., OK, )
	   		return 1
		)
		group_id_fix = GetGroupID(DoorData(doorid)(dOwner))
		if(GroupData(group_id_fix)(gType) != GROUP_AUTOSALE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w komisie samochodowym., OK, )
			return 1
		)
		ShowPlayerDialog(playerid, D_SALON_PRICE_LIST, DIALOG_STYLE_LIST, Wybierz kategoriê, 1. Jednoœlady\n2. Trzydrzwiowe\n3. Piêciodrzwiowe\n4. Furgonetki i ciê¿arówki\n5.Sportowe\n6. Lowridery \n7  Pickupy\n8  Lataj¹ce\n9  P³ywaj¹ce\n10  Pozosta³e , Wybierz, Anuluj)
		//ShowPlayerDialog(playerid, D_SALON_PRICE_LIST, DIALOG_STYLE_LIST, Wybierz kategoriê, 1. Jednoœlady\n2. Trzydrzwiowe\n3. Piêciodrzwiowe\n4. Furgonetki i ciê¿arówki\n5. Pozosta³e, Wybierz, Anuluj)
  		return 1
  	)
  	if(!strcmp(type, kluczyki, true))
  	(
  		if(!PlayerCache(playerid)(pGroupDuty))
  		(
  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz byæ na s³u¿bie grupy, by móc coœ oferowaæ., OK, )
  			return 1
  		)
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) != GROUP_AUTOSALE || !IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_OFFER))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
			return 1
		)
  		giveplayer_id, veh_uid
		if(sscanf(varchar, ud, giveplayer_id, veh_uid))
		(
			hrp_Tip(playerid, /komis kluczyki (ID gracza) (UID pojazdu))
			return 1
		)
		if(giveplayer_id == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaoferowaæ czegoœ sobie., OK, )
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
		if(!PlayerToPlayer(5.0, playerid, giveplayer_id))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID znajduje siê zbyt daleko od Ciebie., OK, )
			return 1
		)
  		doorid = GetPlayerDoorID(playerid)
		if(doorid == INVALID_DOOR_ID)
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w komisie samochodowym., OK, )
	   		return 1
		)
		if(DoorData(doorid)(dOwnerType) != OWNER_GROUP || DoorData(doorid)(dOwner) != PlayerCache(playerid)(pGroupDuty))
		(
	 		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Musisz znajdowaæ siê w komisie samochodowym., OK, )
	   		return 1
		)
		vehid = GetVehicleID(veh_uid)
		if(vehid == INVALID_VEHICLE_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Pojazd musi byæ zespawnowany., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwnerType) != OWNER_PLAYER)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz nie jest w³aœcicielem tego pojazdu., OK, )
			return 1
		)
		if(CarInfo(vehid)(cOwner) != PlayerCache(giveplayer_id)(pUID))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz nie jest w³aœcicielem tego pojazdu., OK, )
			return 1
		)
		OnPlayerSendOffer(playerid, giveplayer_id, OFFER_KEYS, Kluczyki, vehid, 80)
  		return 1
  	)
	return 1
)

CMD:korporacja(playerid, params())
(
	if(PlayerCache(playerid)(pCorpID) != -1)
	(
		// anuluj
		PlayerCache(playerid)(pCorpID) = -1
		PlayerCache(playerid)(pCorpType) = CORP_TYPE_NONE
		PlayerCache(playerid)(pCorpAnswer) = -1
		HidePlayerTextDrawInfo(playerid)
		return 1
	)
	
	if(PlayerCache(playerid)(pCarryTries) ) 0)
	(
		GuiMsg(playerid, Poczekaj chwilê zanim znowu podejmiesz pracê., 1)
		return 1
	)
	
	if(GetPlayerVirtualWorld(playerid) != 4499)
	(
		GuiMsg(playerid, Nie jesteœ w biurowcu., 1)
		return 1
	)
	
	freecorpo = -1
	
	for(i = 0  i ( sizeof(CorPositions) i++)
	(
		if(IsPlayerInRangeOfPoint(playerid, 3.0, CorPositions(i)(corPosX), CorPositions(i)(corPosY), CorPositions(i)(corPosZ)))
		(
			now_corpo = i
			for(worker = 0 worker ( MAX_PLAYERS worker++)
			(
				if(PlayerCache(worker)(pCorpID) == i)
				(
					now_corpo = -1
					freecorpo = -1
					break
				)
			)
			
			freecorpo = now_corpo
		)
	)
	
	if(freecorpo == -1)
	(
		GuiMsg(playerid, Nie ma wolnego miejsca pracy, spróbuj przy innym biurku., 1)
		return 1
	)
	
	PlayerCache(playerid)(pCorpID) = freecorpo
	PlayerCache(playerid)(pCorpType) = CORP_TYPE_TEXT
	SetPlayerPos(playerid, CorPositions(freecorpo)(corPosX), CorPositions(freecorpo)(corPosY), CorPositions(freecorpo)(corPosZ))
	SetPlayerFacingAngle(playerid, CorPositions(freecorpo)(corAngle))
	ShowPlayerTextDrawInfo(playerid, ~w~Rozpoczales prace w korporacji, rozwiazuj zagadki aby uzyskac kilka dolarow wyplaty.~n~Kliknij ~r~anuluj~w~ aby przerwac prace.)
	
	// Losowanie zadania.
	originalstring(24)
	answer = random(10)
	switch(answer)
	(
		case 0:
			format(originalstring, sizeof(originalstring), kasa)
		case 1:
			format(originalstring, sizeof(originalstring), biuro)
		case 2:
			format(originalstring, sizeof(originalstring), wiezowiec)
		case 3:
			format(originalstring, sizeof(originalstring), biurko)
		case 4:
			format(originalstring, sizeof(originalstring), papiery)
		case 5:
			format(originalstring, sizeof(originalstring), okno)
		case 6:
			format(originalstring, sizeof(originalstring), auto)
		case 7:
			format(originalstring, sizeof(originalstring), inwestycja)
		case 8:
			format(originalstring, sizeof(originalstring), kwit)
		case 9:
			format(originalstring, sizeof(originalstring), zysk)
	)
	
	// Dodaj dla gracza
	format(PlayerCache(playerid)(pCorpAnswer), 24, originalstring)
	
	scrambledstring(24) // this will contain the scrambled string
	rand
	for(i = 0, j = strlen(originalstring) i != j i++)
	(
	  do
	  (
		rand = random(j)
	  )
	  while(scrambledstring(rand) != 0)
	  scrambledstring(rand) = originalstring(i)
	)
	
	//GuiMsg(playerid, scrambledstring, 1)
	message(256)
	format(message, sizeof(message), U³ó¿ s³owo z podanych liter: %s, scrambledstring)
	ShowPlayerDialog(playerid, D_CORPO, DIALOG_STYLE_INPUT, Korporacja, message, Spróbuj, Anuluj)
	return 1
)

CMD:odciski(playerid, params())
(
	type(32), varchar(32), string(256)
  	if(sscanf(params, s(32)S()(32), type, varchar))
  	(
  		hrp_Tip(playerid, /odciski ( bron ))
  		return 1
  	)
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_POLICE && GroupData(group_id_fix)(gType) != GROUP_FBI)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiednich uprawnieñ do u¿ycia tej komendy., OK, )
		return 1
	)
  	if(!strcmp(type, bron, true))
	(
		weapon_uid, printlist(512), bool:error = true
		if(sscanf(varchar, d, weapon_uid))
		(
			hrp_Tip(playerid, /odciski bron (UID przedmiotu))
			return 1
		)
		
		foreach(Items, i)
		(
			if(ItemInfo(i)(iUID))
			(
				if(ItemInfo(i)(iPlace) == PLACE_PLAYER && ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID) && ItemInfo(i)(iType) == ITEM_WEAPON)
				(
					error = false
				)
			)
		)
		
		if(error)
		(
			GuiMsg(playerid, Nie posiadasz tej broni przy sobie., 1)
			return 1
		)
		
		mysql_query_format(SELECT print_id, char_name FROM hrp_fingerprints INNER JOIN hrp_characters ON char_uid = print_person WHERE print_weapon = %d GROUP BY print_person, weapon_uid)
		mysql_store_result()
		p_id, p_name(64)
		while(mysql_fetch_row(string, |))
		(
			sscanf(string, p(|)ds(64), p_id, p_name)
			
			pos = strfind(p_name, _, true)
			if(pos != -1)	p_name(pos) =  
			
			format(printlist, sizeof(printlist), %s\n#%d\t\t%s, printlist, p_id, p_name)
		)
		mysql_free_result()
		
		if(!strlen(printlist))
		(
			GuiMsg(playerid, Brak odcisków palców., 1)
			return 1
		)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Odciski palców na tej broni, printlist, OK, )
	)
	
	return 1
)

CMD:obrazenia(playerid, params())
(
	string(128)
	format(string, sizeof(string), Twoje obrazenia: )

	if(PlayerDamageCache(playerid)(BODY_PART_LEFT_ARM))
		format(string, sizeof(string), %slewe ramie, , string)

	if(PlayerDamageCache(playerid)(BODY_PART_LEFT_LEG))
		format(string, sizeof(string), %slewa noga, , string)

	if(PlayerDamageCache(playerid)(BODY_PART_TORSO))
		format(string, sizeof(string), %storso, , string)

	if(PlayerDamageCache(playerid)(BODY_PART_CHEST))
		format(string, sizeof(string), %sklatka, , string)

	if(PlayerDamageCache(playerid)(BODY_PART_HEAD))
		format(string, sizeof(string), %sglowa, , string)

	if(PlayerDamageCache(playerid)(BODY_PART_RIGHT_ARM))
		format(string, sizeof(string), %sprawe ramie, , string)

	if(PlayerDamageCache(playerid)(BODY_PART_RIGHT_LEG))
		format(string, sizeof(string), %sprawa noga, , string)

	SendClientMessage(playerid, COLOR_DO, string)
	return 1
)