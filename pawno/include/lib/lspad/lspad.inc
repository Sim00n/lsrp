#include (lib\lspad\lspad_draws.inc)

stock LSPad(playerid, action, require_password=false) (
	if(action) (

		itemid = PlayerCache(playerid)(pLSPadItemID),
			bgiindex = ItemInfo(itemid)(iValue1)

		if(require_password) (
			if(ItemInfo(itemid)(iValue2) != 0) (
				ShowPlayerDialog(playerid, D_LSPAD_PASSWORD, DIALOG_STYLE_PASSWORD, ItemInfo(itemid)(iName), Wpisz kod do odblokowania urzadzenia., Odblokuj, WyjdzŸ)
				return 1
			)
		)

		PlayerCache(playerid)(pUsingTablet) = true
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY)
		SetPlayerAttachedObject(playerid, SLOT_PHONE, 15204, 6, 0.0, -0.009998, -0.175998, -109.2, -5.0, -101.3, 1.32, 1.12, 1.0)

		for(i = 0 i ( 14 i++) (
			TextDrawShowForPlayer(playerid, LSPad_Frame(i))
		)

		TextDrawSetString(LSPad_BG(playerid), LSPadBackgrounds(bgiindex))
		TextDrawShowForPlayer(playerid, LSPad_BG(playerid))

		for(i = 15 i ( 22 i++) (
			TextDrawShowForPlayer(playerid, LSPad_Frame(i))
		)

		for(i = 0 i ( 5 i++) (
			PlayerTextDrawShow(playerid, LSPad_Calendar(i))
		)

		TextDrawShowForPlayer(playerid, LSPad_Weather)

		SelectTextDraw(playerid, 0x32A1F0AA)

	) else (
		PlayerCache(playerid)(pUsingTablet) = false
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE)
		RemovePlayerAttachedObject(playerid, SLOT_PHONE)
		

		for(i = 0 i ( 22 i++) (
			TextDrawHideForPlayer(playerid, LSPad_Frame(i))
		)

		for(i = 0 i ( 5 i++) (
			PlayerTextDrawHide(playerid, LSPad_Calendar(i))
		)

		TextDrawHideForPlayer(playerid, LSPad_BG(playerid))
		TextDrawHideForPlayer(playerid, LSPad_Weather)

		LSPad_CloseAllExcept(playerid, lspad)

		CancelSelectTextDraw(playerid)
	)

	return 1
)

stock LSPad_Menu(playerid, action) (
	if(action) (
		
		for(i = 0 i ( 10 i++) (
			if(i == 5 || i == 6 || i == 7) continue // Chwilowo nie potrzebujemy ostatniego pola w menu
			PlayerTextDrawShow(playerid, LSPad_MenuTDClickable(i))
		)
		for(i = 0 i ( 12 i++) (
			if(i == 7 || i == 8 || i == 9) continue // Chwilowo nie potrzebujemy ostatniego pola w menu
			TextDrawShowForPlayer(playerid, LSPad_MenuTD(i))
		)

		LSPad_ReopenAnn(playerid) = 0

		LSPad_AnnFix(playerid, 0)
		LSPad_SettFix(playerid, 0)
	) else (
		for(i = 0 i ( 12 i++) (
			TextDrawHideForPlayer(playerid, LSPad_MenuTD(i))
		)
		for(i = 0 i ( 10 i++) (
			PlayerTextDrawHide(playerid, LSPad_MenuTDClickable(i))
		)

		if(LSPad_ReopenAnn(playerid) == 1) (
			LSPad_AnnFix(playerid, 1)
		)
		if(LSPad_ReopenSett(playerid) == 1) (
			LSPad_SettFix(playerid, 1)
		)

		LSPad_ReopenAnn(playerid) = 1
	)
)

stock LSPad_Music(playerid, action) (
	if(action) (

		for(i = 0 i ( 12 i++) (
			TextDrawShowForPlayer(playerid, LSPad_MusicFrame(i))
		)

		TextDrawShowForPlayer(playerid, LSPad_Exit)

		if(!PlayerCache(playerid)(pAudioHandle)) (
			PlayerTextDrawSetString(playerid, LSPad_MusicTitle, Wybierz stacje radiowa z listy.)
		)

		string(64)
		format(string, sizeof(string), Volume: ~r~%d%, PlayerCache(playerid)(pAudioVolume))
		PlayerTextDrawSetString(playerid, LSPad_MusicVolume, string)

		PlayerTextDrawShow(playerid, LSPad_MusicTitle)
		PlayerTextDrawShow(playerid, LSPad_MusicVolume)

		LSPad_CloseAllExcept(playerid, music)
		LSPad_ReopenAnn(playerid) = 0

		for(i = 0 i ( 20 i++) (
			TextDrawShowForPlayer(playerid, LSPad_MusicList(i))
		)

		TextDrawShowForPlayer(playerid, LSPad_Exit)

	) else (
		for(i = 0 i ( 12 i++) (
			TextDrawHideForPlayer(playerid, LSPad_MusicFrame(i))
		)

		for(i = 0 i ( 20 i++) (
			TextDrawHideForPlayer(playerid, LSPad_MusicList(i))
		)

		TextDrawHideForPlayer(playerid, LSPad_Exit)

		PlayerTextDrawHide(playerid, LSPad_MusicTitle)
		PlayerTextDrawHide(playerid, LSPad_MusicVolume)

		LSPad_ReopenAnn(playerid) = 1
	)
)

stock LSPad_Settings(playerid, action) (

	if(action) (

		for(i = 0 i ( 3 i++) (
			TextDrawShowForPlayer(playerid, LSPad_SettingsTD(i))
		)

		for(i = 0 i ( 24 i++) (
			TextDrawShowForPlayer(playerid, LSPad_SettingsWP(i))
		)

		itemid = PlayerCache(playerid)(pLSPadItemID),
			string(8)

		if(ItemInfo(itemid)(iValue2) == 0)
			format(string, sizeof(string), Brak)
		else
			format(string, sizeof(string), %d, ItemInfo(itemid)(iValue2))

		PlayerTextDrawSetString(playerid, LSPad_SettingsCode, string)
		PlayerTextDrawShow(playerid, LSPad_SettingsCode)

		LSPad_CloseAllExcept(playerid, settings)
		LSPad_ReopenAnn(playerid) = 0

		TextDrawShowForPlayer(playerid, LSPad_Exit)

	) else (

		for(i = 0 i ( 3 i++) (
			TextDrawHideForPlayer(playerid, LSPad_SettingsTD(i))
		)

		for(i = 0 i ( 24 i++) (
			TextDrawHideForPlayer(playerid, LSPad_SettingsWP(i))
		)

		TextDrawHideForPlayer(playerid, LSPad_Exit)
		PlayerTextDrawHide(playerid, LSPad_SettingsCode)

		LSPad_ReopenAnn(playerid) = 1

	)

	return 1
)

stock LSPad_Map(playerid, action) (

	if(action) (
		TextDrawShowForPlayer(playerid, LSPad_MapTD)
		
		LSPad_CloseAllExcept(playerid, map)
		LSPad_ReopenAnn(playerid) = 0

		TextDrawShowForPlayer(playerid, LSPad_Exit)
	) else (
		TextDrawHideForPlayer(playerid, LSPad_MapTD)
		TextDrawHideForPlayer(playerid, LSPad_Exit)

		LSPad_ReopenAnn(playerid) = 1
	)
	return 1
)

stock LSPad_Doors(playerid, action) (

	if(action) (
		LSPad_CloseAllExcept(playerid, doors)
		LSPad_CarDoorCleanUp(playerid)

		TextDrawShowForPlayer(playerid, LSPad_LocksTD(0))
		TextDrawShowForPlayer(playerid, LSPad_LocksTD(1))

		iindex = 0, string(128)

		foreach(Doors, doorid) (
			if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER && DoorData(doorid)(dOwner) == PlayerCache(playerid)(pUID)) (
				if(DoorData(doorid)(dElock)) (
					format(string, sizeof(string), %s, DoorData(doorid)(dName))
					PlayerTextDrawSetString(playerid, LSPad_LocksNames(iindex), string)

					if(DoorData(doorid)(dLocked)) (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(iindex), 428150271)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(iindex), 153)
					) else (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(iindex), 153)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(iindex), -2062742017)
					)

					PlayerTextDrawShow(playerid, LSPad_LocksNames(iindex))
					PlayerTextDrawShow(playerid, LSPad_LocksUnlock(iindex))
					PlayerTextDrawShow(playerid, LSPad_LocksLock(iindex))

					LSPad_DoorIDs(playerid)(iindex) = doorid

					iindex++
					if(iindex == 7)
						break
				)
			)
		)

		if(iindex == 0) (
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie posiadasz ¿adnych drzwi z zamkiem elektronicznym., OK, )
		)

		LSPad_ReopenAnn(playerid) = 0

		TextDrawShowForPlayer(playerid, LSPad_Exit)

	) else (

		TextDrawHideForPlayer(playerid, LSPad_Exit)

		TextDrawHideForPlayer(playerid, LSPad_LocksTD(0))
		TextDrawHideForPlayer(playerid, LSPad_LocksTD(1))

		for(i = 0 i ( 8 i++) (
			PlayerTextDrawHide(playerid, LSPad_LocksNames(i))
			PlayerTextDrawHide(playerid, LSPad_LocksUnlock(i))
			PlayerTextDrawHide(playerid, LSPad_LocksLock(i))

			LSPad_DoorIDs(playerid)(i) = INVALID_DOOR_ID
		)

		LSPad_ReopenAnn(playerid) = 1
	)
)

stock LSPad_Cars(playerid, action) (

	if(action) (
		LSPad_CloseAllExcept(playerid, cars)
		LSPad_CarDoorCleanUp(playerid)

		TextDrawShowForPlayer(playerid, LSPad_LocksTD(0))
		TextDrawShowForPlayer(playerid, LSPad_LocksTD(1))

		iindex = 0, string(128)

		foreach(Vehicles, vehid) (
			if(CarInfo(vehid)(cOwnerType) == OWNER_PLAYER && CarInfo(vehid)(cOwner) == PlayerCache(playerid)(pUID)) (
				if(CarInfo(vehid)(cAccess) & VEH_ACCESS_ALARM) (
					format(string, sizeof(string), %s, CarInfo(vehid)(cName))
					PlayerTextDrawSetString(playerid, LSPad_LocksNames(iindex), string)

					if(CarInfo(vehid)(cLocked)) (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(iindex), 428150271)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(iindex), 153)
					) else (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(iindex), 153)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(iindex), -2062742017)
					)

					PlayerTextDrawShow(playerid, LSPad_LocksNames(iindex))
					PlayerTextDrawShow(playerid, LSPad_LocksUnlock(iindex))
					PlayerTextDrawShow(playerid, LSPad_LocksLock(iindex))

					LSPad_CarIDs(playerid)(iindex) = CarInfo(vehid)(cUID)

					iindex++
					if(iindex == 7)
						break
				)
			)
		)

		if(iindex == 0) (
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Nie posiadasz ¿adnych pojazdów z zamkiem elektronicznym (lub nie s± zespawnowane)., OK, )
		)

		LSPad_ReopenAnn(playerid) = 0

		TextDrawShowForPlayer(playerid, LSPad_Exit)

	) else (

		TextDrawHideForPlayer(playerid, LSPad_Exit)

		TextDrawHideForPlayer(playerid, LSPad_LocksTD(0))
		TextDrawHideForPlayer(playerid, LSPad_LocksTD(1))

		for(i = 0 i ( 8 i++) (
			PlayerTextDrawHide(playerid, LSPad_LocksNames(i))
			PlayerTextDrawHide(playerid, LSPad_LocksUnlock(i))
			PlayerTextDrawHide(playerid, LSPad_LocksLock(i))

			LSPad_CarIDs(playerid)(i) = INVALID_VEHICLE_ID
		)

		LSPad_ReopenAnn(playerid) = 1
	)
)

stock LSPad_Bank(playerid, action) (

	if(action) (
		for(i = 0 i ( 4 i++) (
			TextDrawShowForPlayer(playerid, LSPad_BankFrame(i))
		)

		string(256), iindex = 1 // starts at 1 b/c 0 is used for main player cash in LSPad_BankInfo
		
		format(string, sizeof(string), ~b~Stan konta: ~g~$%d, PlayerCache(playerid)(pBankCash))
		PlayerTextDrawSetString(playerid, LSPad_BankInfo(0), string)
		PlayerTextDrawShow(playerid, LSPad_BankInfo(0))

		for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
		(
			if(PlayerGroup(playerid)(slot)(gUID))
			(
				group_id_fix = PlayerGroup(playerid)(slot)(gID)

				format(string, sizeof(string), ~b~%s: ~g~$~r~%d, GroupData(group_id_fix)(gName), GroupData(group_id_fix)(gCash))
				PlayerTextDrawSetString(playerid, LSPad_BankInfo(iindex), string)
				PlayerTextDrawShow(playerid, LSPad_BankInfo(iindex))

				iindex++
			)
		)
		
		LSPad_CloseAllExcept(playerid, bank)
		LSPad_ReopenAnn(playerid) = 0

		TextDrawShowForPlayer(playerid, LSPad_Exit)
	) else (

		for(i = 0 i ( 4 i++) (
			TextDrawHideForPlayer(playerid, LSPad_BankFrame(i))
		)
		for(i = 0 i ( 6 i++) (
			PlayerTextDrawHide(playerid, LSPad_BankInfo(i))
		)

		TextDrawHideForPlayer(playerid, LSPad_Exit)
		LSPad_ReopenAnn(playerid) = 1
	)
	return 1
)

// ======================================================================================================================
// ======================================================================================================================
// ======================================================================================================================

forward LSPad_PlayerTDListener(playerid, PlayerText:playertextid)
forward LSPad_TDListener(playerid, Text:clickedid)

public LSPad_TDListener(playerid, Text:clickedid) (
	
	if(clickedid == LSPad_Frame(17)) (
		// Start button
		if(!LSPad_MenuBool(playerid)) (
			// Show menu
			LSPad_Menu(playerid, 1)
			LSPad_MenuBool(playerid) = true
		) else (
			// Hide menu
			LSPad_Menu(playerid, 0)
			LSPad_MenuBool(playerid) = false
		)
	) else if(clickedid == LSPad_MusicFrame(7)) (
		// Music right
		if(LSPad_MusicStation(playerid) )= 0) (
			LSPad_MusicStation(playerid)++
			if(LSPad_MusicStation(playerid) ) 20) (
				LSPad_MusicStation(playerid) = 0
			)

			LSPad_PlayStation(playerid)
		)
	) else if(clickedid == LSPad_MusicFrame(8)) (
		// Music left
		if(LSPad_MusicStation(playerid) )= 0) (
			LSPad_MusicStation(playerid)--
			if(LSPad_MusicStation(playerid) ( 0) (
				LSPad_MusicStation(playerid) = 19
			)

			LSPad_PlayStation(playerid)
		)
	) else if(clickedid == LSPad_MusicFrame(9)) (
		// Music stop
		LSPad_StopStation(playerid)
	) else if(clickedid == LSPad_MusicFrame(10)) (
		// Music volume up
		LSPad_VolumeUp(playerid)
	) else if(clickedid == LSPad_MusicFrame(11)) (
		// Music volume down
		LSPad_VolumeDown(playerid)
	) else if(clickedid == LSPad_Frame(14)) (
		// Home button (turns off)
		LSPad(playerid, 0)
	) else if(clickedid == LSPad_Exit) (
		// Programm Exit Button
		LSPad_CloseAllExcept(playerid, lspad)
		LSPad_Desktop(playerid, 1)
	) else if(clickedid == LSPad_BankFrame(3)) (
		if(PlayerCache(playerid)(pHours) ) 5)
			ShowPlayerDialog(playerid, D_TRANSFER_NUMBER, DIALOG_STYLE_INPUT, Konto bankowe » Dokonaj przelewu, WprowadŸ numer konta bankowego, na który chcesz przelaæ gotówkê., Dalej, Anuluj)
	) else (

		for(i = 0 i ( 20 i++) (
			if(clickedid == LSPad_MusicList(i)) (
				LSPad_MusicStation(playerid) = i
				LSPad_PlayStation(playerid)
				break
			)
		)

		for(i = 0 i ( 24 i++) ( 
			if(clickedid == LSPad_SettingsWP(i)) (
				
				itemid = PlayerCache(playerid)(pLSPadItemID)
				ItemInfo(itemid)(iValue1) = i
				mysql_query_format(UPDATE hrp_items SET item_value1 = %d WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iValue1), ItemInfo(itemid)(iUID))

				LSPad(playerid, 0)
				LSPad(playerid, 1)
				LSPad_Settings(playerid, 1)
				
				break
			)
		)
	)

	return 0
)

public LSPad_PlayerTDListener(playerid, PlayerText:playertextid) (

	if(playertextid == LSPad_MenuTDClickable(2)) (
		LSPad_Music(playerid, 1)
	) else if(playertextid == LSPad_MenuTDClickable(9)) (
		LSPad(playerid, 0)
	) else if(playertextid == LSPad_MenuTDClickable(8)) (
		LSPad_Settings(playerid, 1)
	) else if(playertextid == LSPad_MenuTDClickable(4)) (
		LSPad_Map(playerid, 1)
	) else if(playertextid == LSPad_MenuTDClickable(0)) (
		LSPad_Doors(playerid, 1)
	) else if(playertextid == LSPad_MenuTDClickable(1)) (
		LSPad_Cars(playerid, 1)
	) else if(playertextid == LSPad_MenuTDClickable(3)) (
		LSPad_Bank(playerid, 1)
	) else if(playertextid == LSPad_SettingsCode) (
		itemid = PlayerCache(playerid)(pLSPadItemID)
		ShowPlayerDialog(playerid, D_LSPAD_NEWPASSWORD, DIALOG_STYLE_INPUT, ItemInfo(itemid)(iName), Wpisz nowe 4-cyfrowe has³o lub 0 aby usunaæ has³o z urz±dzenia., Ustaw, WyjdzŸ)
	) else (

		for(i = 0 i ( 8 i++) (
			if(LSPad_DoorIDs(playerid)(i) != INVALID_DOOR_ID)
			(
				if(playertextid == LSPad_LocksUnlock(i)) (
					doorid = LSPad_DoorIDs(playerid)(i)
					DoorData(doorid)(dLocked) = false
					SaveDoor(doorid, SAVE_DOOR_LOCK)

					if(DoorData(doorid)(dLocked)) (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(i), 428150271)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(i), 153)
					) else (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(i), 153)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(i), -2062742017)
					)

					PlayerTextDrawShow(playerid, LSPad_LocksUnlock(i))
					PlayerTextDrawShow(playerid, LSPad_LocksLock(i))

					break
				)
				if(playertextid == LSPad_LocksLock(i)) (
					doorid = LSPad_DoorIDs(playerid)(i)
					DoorData(doorid)(dLocked) = true
					SaveDoor(doorid, SAVE_DOOR_LOCK)

					if(DoorData(doorid)(dLocked)) (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(i), 428150271)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(i), 153)
					) else (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(i), 153)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(i), -2062742017)
					)

					PlayerTextDrawShow(playerid, LSPad_LocksUnlock(i))
					PlayerTextDrawShow(playerid, LSPad_LocksLock(i))

					break
				)
			)

			if(LSPad_CarIDs(playerid)(i) != INVALID_VEHICLE_ID)
			(
				if(playertextid == LSPad_LocksUnlock(i)) (
					vehuid = LSPad_CarIDs(playerid)(i),
						vehid = GetVehicleID(vehuid)

					CarInfo(vehid)(cLocked) = false
					SetVehicleLock(vehid, false)
					SaveVehicle(vehid, SAVE_VEH_LOCK)

					if(CarInfo(vehid)(cLocked)) (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(i), 428150271)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(i), 153)
					) else (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(i), 153)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(i), -2062742017)
					)

					PlayerTextDrawShow(playerid, LSPad_LocksUnlock(i))
					PlayerTextDrawShow(playerid, LSPad_LocksLock(i))


					Float:VehX, Float:VehY, Float:VehZ
					GetVehiclePos(vehid, VehX, VehY, VehZ)
			
					foreach(Player, pi)
					(
						if(Logged(pi) && Spawned(pi))
						(
							if(IsPlayerInRangeOfPoint(pi, 10.0, VehX, VehY, VehZ))
							(
								//audio = Audio_Play(pi, AUDIO_ALARM)
								//Audio_Set3DPosition(pi, audio, VehX, VehY, VehZ, 10.0)
							)
						)
					)

					break
				)
				if(playertextid == LSPad_LocksLock(i)) (
					vehuid = LSPad_CarIDs(playerid)(i),
						vehid = GetVehicleID(vehuid)

					CarInfo(vehid)(cLocked) = true
					SetVehicleLock(vehid, true)
					SaveVehicle(vehid, SAVE_VEH_LOCK)

					if(CarInfo(vehid)(cLocked)) (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(i), 428150271)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(i), 153)
					) else (
						PlayerTextDrawBoxColor(playerid, LSPad_LocksUnlock(i), 153)
						PlayerTextDrawBoxColor(playerid, LSPad_LocksLock(i), -2062742017)
					)

					PlayerTextDrawShow(playerid, LSPad_LocksUnlock(i))
					PlayerTextDrawShow(playerid, LSPad_LocksLock(i))

					Float:VehX, Float:VehY, Float:VehZ
					GetVehiclePos(vehid, VehX, VehY, VehZ)
			
					foreach(Player, pi)
					(
						if(Logged(pi) && Spawned(pi))
						(
							if(IsPlayerInRangeOfPoint(pi, 10.0, VehX, VehY, VehZ))
							(
								//audio = Audio_Play(pi, AUDIO_ALARM)
								//Audio_Set3DPosition(pi, audio, VehX, VehY, VehZ, 10.0)
							)
						)
					)

					break
				)
			)
		)

	)
	return 0
)

// ======================================================================================================================
// ======================================================================================================================
// ======================================================================================================================

stock LSPad_PlayStation(playerid) (

	if(PlayerCache(playerid)(pAudioHandle))
	(
		PlayerCache(playerid)(pAudioHandle) = 0
		StopAudioStreamForPlayer(playerid)
	)
	
	PlayerCache(playerid)(pMusicPlayerUID) = PlayerCache(playerid)(pLSPadItemID)
	PlayerCache(playerid)(pAudioHandle) = 1
	PlayAudioStreamForPlayer(playerid, LSPad_AudioURLs(LSPad_MusicStation(playerid)))
	

	/*if(PlayerCache(playerid)(pAudioVolume) (= 0 || PlayerCache(playerid)(pAudioVolume) ) 100) (
		Audio_SetVolume(playerid, PlayerCache(playerid)(pAudioHandle), 50)
		PlayerTextDrawSetString(playerid, LSPad_MusicVolume, Volume: ~r~50%)
	)*/

	string(256)
	format(string, sizeof(string), Now Playing: %s, LSPad_AudioURLNames(LSPad_MusicStation(playerid)))

	PlayerTextDrawSetString(playerid, LSPad_MusicTitle, string)
	return 1
)

stock LSPad_StopStation(playerid) (

	PlayerCache(playerid)(pMusicPlayerUID) = 0
	PlayerCache(playerid)(pAudioHandle) = 0

	PlayerCache(playerid)(pAudioHandle) = 0
	StopAudioStreamForPlayer(playerid)
	return 1
)

stock LSPad_VolumeUp(playerid) (
	PlayerCache(playerid)(pAudioVolume) += 5
	if(PlayerCache(playerid)(pAudioVolume) ) 100)
		PlayerCache(playerid)(pAudioVolume) = 100

	//Audio_SetVolume(playerid, PlayerCache(playerid)(pAudioHandle), PlayerCache(playerid)(pAudioVolume))

	string(64)
	format(string, sizeof(string), Volume: ~r~%d%, PlayerCache(playerid)(pAudioVolume))
	PlayerTextDrawSetString(playerid, LSPad_MusicVolume, string)
	return 1
)

stock LSPad_VolumeDown(playerid) (
	PlayerCache(playerid)(pAudioVolume) -= 5

	if(PlayerCache(playerid)(pAudioVolume) ( 0)
		PlayerCache(playerid)(pAudioVolume) = 0

	//Audio_SetVolume(playerid, PlayerCache(playerid)(pAudioHandle), PlayerCache(playerid)(pAudioVolume))

	string(64)
	format(string, sizeof(string), Volume: ~r~%d%, PlayerCache(playerid)(pAudioVolume))
	PlayerTextDrawSetString(playerid, LSPad_MusicVolume, string)
	return 1
)

// ======================================================================================================================

stock LSPad_Desktop(playerid, action) (
	if(action) (
		TextDrawShowForPlayer(playerid, LSPad_Frame(19))
		TextDrawShowForPlayer(playerid, LSPad_Frame(20))
		TextDrawShowForPlayer(playerid, LSPad_Frame(21))

		for(i = 0 i ( 5 i++) (
			PlayerTextDrawShow(playerid, LSPad_Calendar(i))
		)

		TextDrawShowForPlayer(playerid, LSPad_Weather)
	) else (
		TextDrawHideForPlayer(playerid, LSPad_Frame(19))
		TextDrawHideForPlayer(playerid, LSPad_Frame(20))
		TextDrawHideForPlayer(playerid, LSPad_Frame(21))

		for(i = 0 i ( 5 i++) (
			PlayerTextDrawHide(playerid, LSPad_Calendar(i))
		)

		TextDrawHideForPlayer(playerid, LSPad_Weather)
	)
	return 1
)

stock LSPad_AnnFix(playerid, action) (
	if(action) (
		for(i = 0 i ( 5 i++) (
			PlayerTextDrawShow(playerid, LSPad_Calendar(i))
		)		
	) else (
		for(i = 0 i ( 5 i++) (
			PlayerTextDrawHide(playerid, LSPad_Calendar(i))
		)
	)
	return 1
)

stock LSPad_SettFix(playerid, action) (
	if(action) (
		TextDrawShowForPlayer(playerid, LSPad_SettingsTD(2))
		PlayerTextDrawShow(playerid, LSPad_SettingsCode)
	) else (
		TextDrawHideForPlayer(playerid, LSPad_SettingsTD(2))
		PlayerTextDrawHide(playerid, LSPad_SettingsCode)
	)
	return 1	
)

stock LSPad_CloseAllExcept(playerid, t_name(32)) (

	//if(strcmp(t_name, lspad, true))
	if(strcmp(t_name, music, true))
		LSPad_Music(playerid, 0)
	if(strcmp(t_name, settings, true))
		LSPad_Settings(playerid, 0)
	if(strcmp(t_name, map, true))
		LSPad_Map(playerid, 0)
	if(strcmp(t_name, doors, true))
		LSPad_Doors(playerid, 0)
	if(strcmp(t_name, cars, true))
		LSPad_Cars(playerid, 0)
	if(strcmp(t_name, bank, true))
		LSPad_Bank(playerid, 0)

	if(strcmp(t_name, menu, true)) (
		LSPad_Menu(playerid, 0)
		LSPad_MenuBool(playerid) = false
	)

	LSPad_Desktop(playerid, 0)
	
	return 1
)

stock LSPad_OnLoad() (
	string(128)
	for(i = 0 i ( 20 i++) (
		format(string, sizeof(string), %s, LSPad_AudioURLNames(i))
		TextDrawSetString(LSPad_MusicList(i), string)
	)
	return 1
)

stock LSPad_CarDoorCleanUp(playerid) (
	for(i = 0 i ( 8 i++) (
		PlayerTextDrawHide(playerid, LSPad_LocksNames(i))
		PlayerTextDrawHide(playerid, LSPad_LocksUnlock(i))
		PlayerTextDrawHide(playerid, LSPad_LocksLock(i))
	)
	return 1
)
