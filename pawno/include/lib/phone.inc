/*
	Customowe modele telefonów
	19856 - Blackberry
	19855 - Samsung
	19854 - HTC One
	19853 - Nokia
	19852 - Sony
	19851 - Galaxy Samsung
	19850 - Iphone
*/

public LoadPhones()
(
	data(64), phone_id
	mysql_query(SELECT * FROM hrp_phones)
	
	print((load) Rozpoczynam proces wczytywania wszystkich budek telefonicznych z bazy...)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		phone_id++
	
		sscanf(data, p(|)ddfffdd,
		Phones(phone_id)(phoneUID),
		Phones(phone_id)(phoneNumber),
		
		Phones(phone_id)(phonePosX),
		Phones(phone_id)(phonePosY),
		Phones(phone_id)(phonePosZ),
		
		Phones(phone_id)(phoneWorld),
		Phones(phone_id)(phoneInterior))
		
		Phones(phone_id)(phoneBusy) = false
		Phones(phone_id)(phoneConvo) = INVALID_PLAYER_ID
		
		Itter_Add(Phones, phone_id)
	)
	mysql_free_result()
	
	printf((load) Wczytano %d budek telefonicznych., phone_id)
	
	print((load) Tworze 3DTexty dla budek telefonicznych)
	count = Create3DTextsForPhones()
	printf((load) Stworzono %d 3DTextow dla budek telefonicznych, count)
	return 1
)

stock ReloadPhones()
(
	for(i = 0  i ( MAX_PHONES i++)
	(
		Phones(i)(phoneUID) = EOS
		Phones(i)(phoneNumber) = EOS
		Phones(i)(phonePosX) = EOS
		Phones(i)(phonePosY) = EOS
		Phones(i)(phonePosZ) = EOS
		Phones(i)(phoneWorld) = EOS
		Phones(i)(phoneInterior) = EOS
		Phones(i)(phoneBusy) = false
		Phones(i)(phoneConvo) = INVALID_PLAYER_ID
	)
	
	LoadPhones()
	
	print((reload) Przeladowano budki telefoniczne)
	
	return 1
)

stock Create3DTextsForPhones()
(
	count = 0, string(128)
	foreach(Phones, phone)
	(
		format(string, sizeof(string), Budka telefoniczna (%d)\n(3E9E0E)Numer: (E85405)%d(FFFFFF), Phones(phone)(phoneUID), Phones(phone)(phoneNumber))
		Text3D:label_id = CreateDynamic3DTextLabel(string, COLOR_DESC, Phones(phone)(phonePosX), Phones(phone)(phonePosY), Phones(phone)(phonePosZ), 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, Phones(phone)(phoneWorld), Phones(phone)(phoneInterior), -1, 10.0)
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID, Phones(phone)(phoneUID))
		count++
	)
	return count
)

stock CanPlayerHearPhone(playerid, phoneid)
(
	return (IsPlayerInRangeOfPoint(playerid, 20.0, Phones(phoneid)(phonePosX), Phones(phoneid)(phonePosY), Phones(phoneid)(phonePosZ)))? true : false
)

stock IsPlayerNearPhone(playerid, phoneid)
(
	return (IsPlayerInRangeOfPoint(playerid, 3.0, Phones(phoneid)(phonePosX), Phones(phoneid)(phonePosY), Phones(phoneid)(phonePosZ)))? true : false
)

stock GetPhoneNearPlayer(playerid, Float:range)
(
	foreach(Phones, phone)
	(
		if(GetPlayerVirtualWorld(playerid) == Phones(phone)(phoneWorld) && GetPlayerInterior(playerid) == Phones(phone)(phoneInterior))
		(
			if(IsPlayerInRangeOfPoint(playerid, range, Phones(phone)(phonePosX), Phones(phone)(phonePosY), Phones(phone)(phonePosZ)))
			(
				return phone
			)
		)
	)
	return -1
)

/*
		domowe
*/

public LoadHomephones()
(
	gameid = 0
	for(i = 0  i ( MAX_DOORSi++)
	(
		if(!IsDoorAddonMounted(i,ITEM_HOMEPHONESET))
		(
			continue
		)
		else
		(
			if(gameid ) MAX_HOMEPHONES)
			(
				for(error = 0  error ( 50 error++)
				(
					print((error) tablica przepelniona, trzeba zwiekszyc limit (MAX_HOMEPHONES))
				)
				
				break
			)
			HomePhones(gameid)(hPhoneNumber) = 1000 + DoorData(i)(dUID)
			HomePhones(gameid)(hphoneBusy) = false
			HomePhones(gameid)(hDoorUID) = DoorData(i)(dUID)
			HomePhones(gameid)(hWorld) = DoorData(i)(dExitVW)
			
			gameid++
		)
	)
	
	return 1
)

stock ReloadHomephones()
(
	for(i = 0  i ( MAX_HOMEPHONES i++)
	(
		HomePhones(i)(hPhoneNumber) = 0
		HomePhones(i)(hphoneBusy) = false
		HomePhones(i)(hDoorUID) = 0
		HomePhones(i)(hWorld) = 0
	)
	
	LoadHomephones()
	
	print((reload) telefony stacjonarne prze³adowane)
	
	return 1
)

stock CanPlayerHearHomephone(playerid,phoneid)
(	
	if(GetPlayerVirtualWorld(playerid) == HomePhones(phoneid)(hWorld))
	(
		return true
	)
	else
	(
		return false
	)
)

stock getPlayerOfflineMessages(playerid)
(
	buffer(256), number, text(256), conname(128), count = 0
	format(buffer, sizeof(buffer), SELECT sms_number, sms_text, sms_conname FROM hrp_offlinesms WHERE sms_target = %d, PlayerCache(playerid)(pPhoneNumber))
	mysql_query(buffer)
	mysql_store_result()
	while(mysql_fetch_row(buffer, |))
	(
		count++
		sscanf(buffer, p(|)ds(256)s(128), number, text, conname)
		
		format(text, sizeof(text), (SMS) (%d) %s: %s, number, conname, text)
		SendClientMessage(playerid, COLOR_YELLOW, text)
	)
	mysql_free_result()
	
	if(!count)
		return 0

	if(PlayerCache(playerid)(pSex) == 1) 
		format(buffer, sizeof(buffer), * %s otrzyma³ SMS-a., PlayerName(playerid))
	else
		format(buffer, sizeof(buffer), * %s otrzyma³a SMS-a., PlayerName(playerid))
		
	ProxDetector(10.0, playerid, buffer, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
	mysql_query_format(DELETE FROM hrp_offlinesms WHERE sms_target = %d, PlayerCache(playerid)(pPhoneNumber))
	return 1
)

/*stock getPlayerOfflineMessages(playerid)
(
	buffer(256), number, text(256), count = 0
	format(buffer, sizeof(buffer), SELECT sms_number, sms_text FROM hrp_offlinesms WHERE sms_target = %d, PlayerCache(playerid)(pPhoneNumber))
	mysql_query(buffer)
	mysql_store_result()
	while(mysql_fetch_row(buffer, |))
	(
		count++
		sscanf(buffer, p(|)ds(256), number, text)
		
		format(text, sizeof(text), (SMS) %d: %s, number, text)
		SendClientMessage(playerid, COLOR_YELLOW, text)
	)
	mysql_free_result()
	
	if(!count)
		return 1

	if(PlayerCache(playerid)(pSex) == 1) 
		format(buffer, sizeof(buffer), * %s otrzyma³ SMS-a., PlayerName(playerid))
	else
		format(buffer, sizeof(buffer), * %s otrzyma³a SMS-a., PlayerName(playerid))
		
	ProxDetector(10.0, playerid, buffer, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
	mysql_query_format(DELETE FROM hrp_offlinesms WHERE sms_target = %d, PlayerCache(playerid)(pPhoneNumber))
	return 1
)*/

// Nowe telefony
stock attachPlayerPhone(playerid)
(
	phoneType = 0
	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID))
		(
			if(ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID) && ItemInfo(i)(iPlace) == PLACE_PLAYER)
			(
				if(ItemInfo(i)(iType) == ITEM_PHONE && ItemInfo(i)(iUsed))
				(
					phoneType = ItemInfo(i)(iValue2)
					break
				)
			)
		)
	)
	
	switch(phoneType)
	(
		case PHONE_TYPE_OLD:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
			
		case PHONE_TYPE_BLACKBERRY:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 19856, 6, 0.064999, 0.043999, 0.004999, -112.0, 0.0, -178.9)
			
		case PHONE_TYPE_SAMSUNG:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 19855, 6, 0.064999, 0.043999, 0.004999, -112.0, 0.0, -178.9)
			
		case PHONE_TYPE_HTC:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 19854, 6, 0.064999, 0.043999, 0.004999, -112.0, 0.0, -178.9)
			
		case PHONE_TYPE_NOKIA:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 19853, 6, 0.064999, 0.043999, 0.004999, -112.0, 0.0, -178.9)
			
		case PHONE_TYPE_SONY:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 19852, 6, 0.064999, 0.043999, 0.004999, -112.0, 0.0, -178.9)
			
		case PHONE_TYPE_GALAXY:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 19851, 6, 0.064999, 0.043999, 0.004999, -112.0, 0.0, -178.9)
			
		case PHONE_TYPE_IPHONE:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 19850, 6, 0.064999, 0.043999, 0.004999, -112.0, 0.0, -178.9)
			
		case PHONE_TYPE_IPHONE_WHITE:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 15203, 6, -0.032002, 0.031998, 0.001999, -170.5, 175.8, 173.5)
			
		default:
			SetPlayerAttachedObject(playerid, SLOT_PHONE, 330, 6)
	)
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE)
	return 1
)

// Nowe GUI telefonów
/*
	1. dodaæ pobieranie godziny
	2. dodaæ pobieranie daty
	3. ustawienia rozwin¹æ
*/
stock setPhoneWallpaper(playerid, wallpaper)
(
	switch(wallpaper)
	(
		case 0:
			PlayerTextDrawSetString(playerid, TextPhoneWallpaper(playerid), loadsc6:loadsc6)		// babka
		case 1:
			PlayerTextDrawSetString(playerid, TextPhoneWallpaper(playerid), loadsc0:loadsc0)		// kolarz
		case 2:
			PlayerTextDrawSetString(playerid, TextPhoneWallpaper(playerid), loadsc8:loadsc8)		// blondyna
		case 3:
			PlayerTextDrawSetString(playerid, TextPhoneWallpaper(playerid), loadsc12:loadsc12)		// gangster
		case 4:
			PlayerTextDrawSetString(playerid, TextPhoneWallpaper(playerid), loadsc2:loadsc2)		// savanna
		default:
			PlayerTextDrawSetString(playerid, TextPhoneWallpaper(playerid), loadsc6:loadsc6)
	)
	return 1
)

stock getPhoneSettings(playerid, setting)
(
	value = -1, buffer(256)
	
	// sprawdzanie czy ma ustawienia
	format(buffer, sizeof(buffer), SELECT * FROM hrp_phoneset WHERE set_phone = %d, PlayerCache(playerid)(pPhoneNumber))
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() (= 0)
	(
		mysql_free_result()
		mysql_query_format(INSERT INTO hrp_phoneset VALUES(NULL, %d, 0, 0), PlayerCache(playerid)(pPhoneNumber))
	)
	else
		mysql_free_result()
	
	if(setting & GET_PHONE_PASSWORD)
	(
		format(buffer, sizeof(buffer), SELECT set_password FROM hrp_phoneset WHERE set_phone = %d, PlayerCache(playerid)(pPhoneNumber))
		mysql_query(buffer)
		mysql_store_result()
		value = mysql_fetch_int()
		mysql_free_result()
	)
	
	if(setting & GET_PHONE_WALLPAPER)
	(
		format(buffer, sizeof(buffer), SELECT set_wallpaper FROM hrp_phoneset WHERE set_phone = %d, PlayerCache(playerid)(pPhoneNumber))
		mysql_query(buffer)
		mysql_store_result()
		value = mysql_fetch_int()
		mysql_free_result()
	)
	
	if(setting & GET_PHONE_COLOR)
	(
		// brak
	)
	
	return value
)

stock isPhoneNewType(playerid)
(
	// 0 = klasyczny, 1 = modyfikowany
	type = 0
	foreach(Items, i)
	(
		if(ItemInfo(i)(iUID))
		(
			if(ItemInfo(i)(iOwner) == PlayerCache(playerid)(pUID) && ItemInfo(i)(iPlace) == PLACE_PLAYER)
			(
				if(ItemInfo(i)(iType) == ITEM_PHONE && ItemInfo(i)(iUsed))
				(
					type = ItemInfo(i)(iValue2)
					break
				)
			)
		)
	)
	
	if(type ) 0)
		type = 1
	
	return type
)

stock phone_showTexts(playerid)
(
	string(128)
	phone_hideTexts(playerid)
	PlayerCache(playerid)(pUseGUI) = true
	SelectTextDraw(playerid, 0x8C8C8CFF)
	
	// co by ³adniej wygl¹da³o
	attachPlayerPhone(playerid)
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE)
	ApplyAnimation(playerid, CARRY, crry_prtial, 4.1, 0, 0, 0, 0, 0)
	
	// ustaw godzine
	hour, minute, second
	gettime(hour, minute, second)
	format(string, sizeof(string), %02d:%02d, hour, minute)
	PlayerTextDrawSetString(playerid, TextPhoneTime(playerid), string)
	
	// ustaw date
	year, month, day
	getdate(year, month, day)
	format(string, sizeof(string), %02d/%02d/%d, year, month, day)
	PlayerTextDrawSetString(playerid, TextPhoneDate(playerid), string)
	
	PlayerTextDrawShow(playerid, TextPhoneCorner1(playerid))
	PlayerTextDrawShow(playerid, TextPhoneCorner2(playerid))
	PlayerTextDrawShow(playerid, TextPhoneCorner3(playerid))
	PlayerTextDrawShow(playerid, TextPhoneCorner4(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBackground(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBorder1(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBorder2(playerid))
	PlayerTextDrawShow(playerid, TextPhoneWallpaper(playerid))
	PlayerTextDrawShow(playerid, TextPhoneButton(playerid))
	PlayerTextDrawShow(playerid, TextPhoneHeading(playerid))
	PlayerTextDrawShow(playerid, TextPhoneName(playerid))
	PlayerTextDrawShow(playerid, TextPhoneHeadset(playerid))
	PlayerTextDrawShow(playerid, TextPhoneTime(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBattery1(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBattery2(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBtnCard(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBtnCall(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBtnSms(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBtnContacts(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBtnAdd(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBtnExit(playerid))
	PlayerTextDrawShow(playerid, TextPhoneDate(playerid))
	PlayerTextDrawShow(playerid, TextPhoneBtnSett(playerid))
	
	return 1
)

stock phone_hideTexts(playerid)
(
	PlayerTextDrawHide(playerid, TextPhoneCorner1(playerid))
	PlayerTextDrawHide(playerid, TextPhoneCorner2(playerid))
	PlayerTextDrawHide(playerid, TextPhoneCorner3(playerid))
	PlayerTextDrawHide(playerid, TextPhoneCorner4(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBackground(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBorder1(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBorder2(playerid))
	PlayerTextDrawHide(playerid, TextPhoneWallpaper(playerid))
	PlayerTextDrawHide(playerid, TextPhoneButton(playerid))
	PlayerTextDrawHide(playerid, TextPhoneHeading(playerid))
	PlayerTextDrawHide(playerid, TextPhoneName(playerid))
	PlayerTextDrawHide(playerid, TextPhoneHeadset(playerid))
	PlayerTextDrawHide(playerid, TextPhoneTime(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBattery1(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBattery2(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBtnCard(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBtnCall(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBtnSms(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBtnContacts(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBtnAdd(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBtnExit(playerid))
	PlayerTextDrawHide(playerid, TextPhoneDate(playerid))
	PlayerTextDrawHide(playerid, TextPhoneBtnSett(playerid))
	
	RemovePlayerAttachedObject(playerid, SLOT_PHONE)
	PlayerCache(playerid)(pPhoneAction) = PHONE_ACTION_HOME
	PlayerCache(playerid)(pUseGUI) = false
	CancelSelectTextDraw(playerid)
	
	return 1
)

stock phone_loadTextdraws(playerid)
(
	TextPhoneCorner1(playerid) = CreatePlayerTextDraw(playerid, 20.000000, 130.000000, ld_pool:ball)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneCorner1(playerid), 255)
	PlayerTextDrawFont(playerid, TextPhoneCorner1(playerid), 4)
	PlayerTextDrawLetterSize(playerid, TextPhoneCorner1(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneCorner1(playerid), 255)
	PlayerTextDrawSetOutline(playerid, TextPhoneCorner1(playerid), 0)
	PlayerTextDrawSetProportional(playerid, TextPhoneCorner1(playerid), 1)
	PlayerTextDrawSetShadow(playerid, TextPhoneCorner1(playerid), 1)
	PlayerTextDrawUseBox(playerid, TextPhoneCorner1(playerid), 1)
	PlayerTextDrawBoxColor(playerid, TextPhoneCorner1(playerid), 255)
	PlayerTextDrawTextSize(playerid, TextPhoneCorner1(playerid), 36.000000, 30.000000)

	TextPhoneCorner2(playerid)= CreatePlayerTextDraw(playerid, 127.000000, 130.000000, ld_pool:ball)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneCorner2(playerid), 255)
	PlayerTextDrawFont(playerid, TextPhoneCorner2(playerid), 4)
	PlayerTextDrawLetterSize(playerid, TextPhoneCorner2(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneCorner2(playerid), 255)
	PlayerTextDrawSetOutline(playerid, TextPhoneCorner2(playerid), 0)
	PlayerTextDrawSetProportional(playerid, TextPhoneCorner2(playerid), 1)
	PlayerTextDrawSetShadow(playerid, TextPhoneCorner2(playerid), 1)
	PlayerTextDrawUseBox(playerid, TextPhoneCorner2(playerid), 1)
	PlayerTextDrawBoxColor(playerid, TextPhoneCorner2(playerid), 255)
	PlayerTextDrawTextSize(playerid, TextPhoneCorner2(playerid), 36.000000, 30.000000)

	TextPhoneCorner3(playerid)= CreatePlayerTextDraw(playerid, 127.000000, 295.000000, ld_pool:ball)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneCorner3(playerid), 255)
	PlayerTextDrawFont(playerid, TextPhoneCorner3(playerid), 4)
	PlayerTextDrawLetterSize(playerid, TextPhoneCorner3(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneCorner3(playerid), 255)
	PlayerTextDrawSetOutline(playerid, TextPhoneCorner3(playerid), 0)
	PlayerTextDrawSetProportional(playerid, TextPhoneCorner3(playerid), 1)
	PlayerTextDrawSetShadow(playerid, TextPhoneCorner3(playerid), 1)
	PlayerTextDrawUseBox(playerid, TextPhoneCorner3(playerid), 1)
	PlayerTextDrawBoxColor(playerid, TextPhoneCorner3(playerid), 255)
	PlayerTextDrawTextSize(playerid, TextPhoneCorner3(playerid), 36.000000, 30.000000)

	TextPhoneCorner4(playerid) = CreatePlayerTextDraw(playerid, 20.000000, 295.000000, ld_pool:ball)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneCorner4(playerid), 255)
	PlayerTextDrawFont(playerid, TextPhoneCorner4(playerid), 4)
	PlayerTextDrawLetterSize(playerid, TextPhoneCorner4(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneCorner4(playerid), 255)
	PlayerTextDrawSetOutline(playerid, TextPhoneCorner4(playerid), 0)
	PlayerTextDrawSetProportional(playerid, TextPhoneCorner4(playerid), 1)
	PlayerTextDrawSetShadow(playerid, TextPhoneCorner4(playerid), 1)
	PlayerTextDrawUseBox(playerid, TextPhoneCorner4(playerid), 1)
	PlayerTextDrawBoxColor(playerid, TextPhoneCorner4(playerid), 255)
	PlayerTextDrawTextSize(playerid, TextPhoneCorner4(playerid), 36.000000, 30.000000)

	TextPhoneBackground(playerid)= CreatePlayerTextDraw(playerid, 92.000000, 146.000000, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~)
	PlayerTextDrawAlignment(playerid, TextPhoneBackground(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBackground(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBackground(playerid),  1)
	PlayerTextDrawLetterSize(playerid, TextPhoneBackground(playerid),  0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneBackground(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBackground(playerid),  0)
	PlayerTextDrawSetProportional(playerid, TextPhoneBackground(playerid),  1)
	PlayerTextDrawSetShadow(playerid, TextPhoneBackground(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBackground(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBackground(playerid),  255)
	PlayerTextDrawTextSize(playerid, TextPhoneBackground(playerid),  0.000000, -148.000000)

	TextPhoneBorder1(playerid)= CreatePlayerTextDraw(playerid, 90.000000, 133.000000, _)
	PlayerTextDrawAlignment(playerid, TextPhoneBorder1(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBorder1(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBorder1(playerid),  1)
	PlayerTextDrawLetterSize(playerid, TextPhoneBorder1(playerid),  0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneBorder1(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBorder1(playerid),  0)
	PlayerTextDrawSetProportional(playerid, TextPhoneBorder1(playerid),  1)
	PlayerTextDrawSetShadow(playerid, TextPhoneBorder1(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBorder1(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBorder1(playerid),  255)
	PlayerTextDrawTextSize(playerid, TextPhoneBorder1(playerid),  0.000000, -112.000000)

	TextPhoneBorder2(playerid) = CreatePlayerTextDraw(playerid, 90.000000, 305.000000, ~n~~n~)
	PlayerTextDrawAlignment(playerid, TextPhoneBorder2(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBorder2(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBorder2(playerid),  1)
	PlayerTextDrawLetterSize(playerid, TextPhoneBorder2(playerid),  0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneBorder2(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBorder2(playerid),  0)
	PlayerTextDrawSetProportional(playerid, TextPhoneBorder2(playerid),  1)
	PlayerTextDrawSetShadow(playerid, TextPhoneBorder2(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBorder2(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBorder2(playerid),  255)
	PlayerTextDrawTextSize(playerid, TextPhoneBorder2(playerid),  0.000000, -112.000000)

	TextPhoneWallpaper(playerid) = CreatePlayerTextDraw(playerid, 28.000000, 143.000000, loadsc6:loadsc6)
	PlayerTextDrawAlignment(playerid, TextPhoneWallpaper(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneWallpaper(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneWallpaper(playerid),  4)
	PlayerTextDrawLetterSize(playerid, TextPhoneWallpaper(playerid),  0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneWallpaper(playerid),  1684301055)
	PlayerTextDrawSetOutline(playerid, TextPhoneWallpaper(playerid),  0)
	PlayerTextDrawSetProportional(playerid, TextPhoneWallpaper(playerid),  1)
	PlayerTextDrawSetShadow(playerid, TextPhoneWallpaper(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneWallpaper(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneWallpaper(playerid),  1684301055)
	PlayerTextDrawTextSize(playerid, TextPhoneWallpaper(playerid),  126.000000, 166.000000)

	TextPhoneButton(playerid) = CreatePlayerTextDraw(playerid, 85.000000, 311.000000, ld_pool:ball)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneButton(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneButton(playerid),  4)
	PlayerTextDrawLetterSize(playerid, TextPhoneButton(playerid),  0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneButton(playerid),  -1768515841)
	PlayerTextDrawSetOutline(playerid, TextPhoneButton(playerid),  0)
	PlayerTextDrawSetProportional(playerid, TextPhoneButton(playerid),  1)
	PlayerTextDrawSetShadow(playerid, TextPhoneButton(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneButton(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneButton(playerid),  -1)
	PlayerTextDrawTextSize(playerid, TextPhoneButton(playerid),  13.000000, 12.000000)
	PlayerTextDrawSetSelectable(playerid, TextPhoneButton(playerid), 1)

	TextPhoneHeading(playerid) = CreatePlayerTextDraw(playerid, 92.000000, 137.000000, _)
	PlayerTextDrawAlignment(playerid, TextPhoneHeading(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneHeading(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneHeading(playerid),  1)
	PlayerTextDrawLetterSize(playerid, TextPhoneHeading(playerid),  0.500000, -0.100000)
	PlayerTextDrawColor(playerid, TextPhoneHeading(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneHeading(playerid),  0)
	PlayerTextDrawSetProportional(playerid, TextPhoneHeading(playerid),  1)
	PlayerTextDrawSetShadow(playerid, TextPhoneHeading(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneHeading(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneHeading(playerid),  1010580735)
	PlayerTextDrawTextSize(playerid, TextPhoneHeading(playerid),  0.000000, 17.000000)

	TextPhoneName(playerid) = CreatePlayerTextDraw(playerid, 35.000000, 134.000000, LSPhone)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneName(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneName(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneName(playerid),  0.159999, 0.599999)
	PlayerTextDrawColor(playerid, TextPhoneName(playerid),  65535)
	PlayerTextDrawSetOutline(playerid, TextPhoneName(playerid),  0)
	PlayerTextDrawSetProportional(playerid, TextPhoneName(playerid),  1)
	PlayerTextDrawSetShadow(playerid, TextPhoneName(playerid),  0)

	TextPhoneHeadset(playerid) = CreatePlayerTextDraw(playerid, 91.000000, 145.000000, _)
	PlayerTextDrawAlignment(playerid, TextPhoneHeadset(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneHeadset(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneHeadset(playerid),  1)
	PlayerTextDrawLetterSize(playerid, TextPhoneHeadset(playerid),  0.500000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneHeadset(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneHeadset(playerid),  0)
	PlayerTextDrawSetProportional(playerid, TextPhoneHeadset(playerid),  1)
	PlayerTextDrawSetShadow(playerid, TextPhoneHeadset(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneHeadset(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneHeadset(playerid),  673720420)
	PlayerTextDrawTextSize(playerid, TextPhoneHeadset(playerid),  0.000000, -132.000000)

	TextPhoneTime(playerid) = CreatePlayerTextDraw(playerid, 128.000000, 144.000000, 21:37)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneTime(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneTime(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneTime(playerid),  0.200000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneTime(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneTime(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneTime(playerid),  1)

	TextPhoneBattery1(playerid) = CreatePlayerTextDraw(playerid, 30.000000, 141.000000, I)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBattery1(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBattery1(playerid),  1)
	PlayerTextDrawLetterSize(playerid, TextPhoneBattery1(playerid),  0.829999, 1.600000)
	PlayerTextDrawColor(playerid, TextPhoneBattery1(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBattery1(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneBattery1(playerid),  1)

	TextPhoneBattery2(playerid) = CreatePlayerTextDraw(playerid, 30.000000, 146.000000, I)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBattery2(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBattery2(playerid),  1)
	PlayerTextDrawLetterSize(playerid, TextPhoneBattery2(playerid),  0.829999, 0.899999)
	PlayerTextDrawColor(playerid, TextPhoneBattery2(playerid),  16711935)
	PlayerTextDrawSetOutline(playerid, TextPhoneBattery2(playerid),  0)
	PlayerTextDrawSetProportional(playerid, TextPhoneBattery2(playerid),  1)
	PlayerTextDrawSetShadow(playerid, TextPhoneBattery2(playerid),  0)

	// Ma³a edycja guzików
	TextPhoneBtnCall(playerid) = CreatePlayerTextDraw(playerid, 91.000000, 166.000000, Zadzwon)
	PlayerTextDrawAlignment(playerid, TextPhoneBtnCall(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBtnCall(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBtnCall(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneBtnCall(playerid),  0.380000, 1.600000)
	PlayerTextDrawColor(playerid, TextPhoneBtnCall(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBtnCall(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneBtnCall(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBtnCall(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBtnCall(playerid),  1352020660)
	PlayerTextDrawTextSize(playerid, TextPhoneBtnCall(playerid),  15.000000, 121.000000)
	PlayerTextDrawSetSelectable(playerid, TextPhoneBtnCall(playerid), 1)

	TextPhoneBtnSms(playerid) = CreatePlayerTextDraw(playerid, 91.000000, 188.000000, SMS)
	PlayerTextDrawAlignment(playerid, TextPhoneBtnSms(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBtnSms(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBtnSms(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneBtnSms(playerid),  0.380000, 1.600000)
	PlayerTextDrawColor(playerid, TextPhoneBtnSms(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBtnSms(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneBtnSms(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBtnSms(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBtnSms(playerid),  1352020660)
	PlayerTextDrawTextSize(playerid, TextPhoneBtnSms(playerid),  15.000000, 121.000000)
	PlayerTextDrawSetSelectable(playerid, TextPhoneBtnSms(playerid) , 1)

	TextPhoneBtnContacts(playerid) = CreatePlayerTextDraw(playerid, 91.000000, 210.000000, Kontakty)
	PlayerTextDrawAlignment(playerid, TextPhoneBtnContacts(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBtnContacts(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBtnContacts(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneBtnContacts(playerid),  0.380000, 1.600000)
	PlayerTextDrawColor(playerid, TextPhoneBtnContacts(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBtnContacts(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneBtnContacts(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBtnContacts(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBtnContacts(playerid),  1352020660)
	PlayerTextDrawTextSize(playerid, TextPhoneBtnContacts(playerid),  15.000000, 121.000000)
	PlayerTextDrawSetSelectable(playerid, TextPhoneBtnContacts(playerid), 1)

	TextPhoneBtnAdd(playerid) = CreatePlayerTextDraw(playerid, 91.000000, 232.000000, Dodaj)
	PlayerTextDrawAlignment(playerid, TextPhoneBtnAdd(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBtnAdd(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBtnAdd(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneBtnAdd(playerid),  0.380000, 1.600000)
	PlayerTextDrawColor(playerid, TextPhoneBtnAdd(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBtnAdd(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneBtnAdd(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBtnAdd(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBtnAdd(playerid),  1352020660)
	PlayerTextDrawTextSize(playerid, TextPhoneBtnAdd(playerid),  15.000000, 121.000000)
	PlayerTextDrawSetSelectable(playerid, TextPhoneBtnAdd(playerid), 1)

	TextPhoneBtnCard(playerid) = CreatePlayerTextDraw(playerid, 91.000000, 254.000000, vCARD)
	PlayerTextDrawAlignment(playerid, TextPhoneBtnCard(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBtnCard(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBtnCard(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneBtnCard(playerid),  0.380000, 1.600000)
	PlayerTextDrawColor(playerid, TextPhoneBtnCard(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBtnCard(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneBtnCard(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBtnCard(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBtnCard(playerid),  1352020660)
	PlayerTextDrawTextSize(playerid, TextPhoneBtnCard(playerid),  15.000000, 121.000000)
	PlayerTextDrawSetSelectable(playerid, TextPhoneBtnCard(playerid), 1)

	TextPhoneBtnExit(playerid) = CreatePlayerTextDraw(playerid, 57.000000, 279.000000, Wylacz)
	PlayerTextDrawAlignment(playerid, TextPhoneBtnExit(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBtnExit(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBtnExit(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneBtnExit(playerid),  0.180000, 0.799999)
	PlayerTextDrawColor(playerid, TextPhoneBtnExit(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBtnExit(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneBtnExit(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBtnExit(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBtnExit(playerid),  1352020660)
	PlayerTextDrawTextSize(playerid, TextPhoneBtnExit(playerid),  15.000000, 48.000000)
	PlayerTextDrawSetSelectable(playerid, TextPhoneBtnExit(playerid), 1)

	TextPhoneBtnSett(playerid) = CreatePlayerTextDraw(playerid, 57.000000, 294.000000, Ustawienia)
	PlayerTextDrawAlignment(playerid, TextPhoneBtnSett(playerid),  2)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneBtnSett(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneBtnSett(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneBtnSett(playerid),  0.180000, 0.799999)
	PlayerTextDrawColor(playerid, TextPhoneBtnSett(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneBtnSett(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneBtnSett(playerid),  1)
	PlayerTextDrawUseBox(playerid, TextPhoneBtnSett(playerid),  1)
	PlayerTextDrawBoxColor(playerid, TextPhoneBtnSett(playerid),  1352020660)
	PlayerTextDrawTextSize(playerid, TextPhoneBtnSett(playerid),  15.000000, 48.000000)
	PlayerTextDrawSetSelectable(playerid, TextPhoneBtnSett(playerid), 1)

	TextPhoneDate(playerid) = CreatePlayerTextDraw(playerid, 43.000000, 144.000000, 31.10.2014)
	PlayerTextDrawBackgroundColor(playerid, TextPhoneDate(playerid),  255)
	PlayerTextDrawFont(playerid, TextPhoneDate(playerid),  2)
	PlayerTextDrawLetterSize(playerid, TextPhoneDate(playerid),  0.200000, 1.000000)
	PlayerTextDrawColor(playerid, TextPhoneDate(playerid),  -1)
	PlayerTextDrawSetOutline(playerid, TextPhoneDate(playerid),  1)
	PlayerTextDrawSetProportional(playerid, TextPhoneDate(playerid),  1)
	
	return 1
)