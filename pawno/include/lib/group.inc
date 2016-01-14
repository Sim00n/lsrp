public CreateGroup(GroupName())
(
	group_id_fix, group_uid, group_name(32)
	
	mysql_real_escape_string(GroupName, group_name)
	mysql_query_format(INSERT INTO hrp_groups (group_name) VALUES (%s), group_name)

	group_uid = mysql_insert_id()
	group_id_fix = Itter_Free(Groups)

	GroupData(group_id_fix)(gUID) = group_uid
	strmid(GroupData(group_id_fix)(gName), group_name, 0, strlen(group_name), 32)

	GroupData(group_id_fix)(gCash) = 0

	GroupData(group_id_fix)(gType) = TYPE_NONE
	GroupData(group_id_fix)(gOwner) = OWNER_NONE

	GroupData(group_id_fix)(gValue1) = 0
	GroupData(group_id_fix)(gValue2) = 0

	GroupData(group_id_fix)(gDotation) = 0
	GroupData(group_id_fix)(gColor) = COLOR_WHITE

	strmid(GroupData(group_id_fix)(gTag), NONE, 0, 4, 5)
	GroupData(group_id_fix)(gActivity) = 0
	
	GroupData(group_id_fix)(gToggleChat) = false
	GroupData(group_id_fix)(gActionTime) = 0
	Itter_Add(Groups, group_id_fix)
	
	return group_id_fix
)

public SaveGroup(group__id)
(
	mysql_query_format(UPDATE hrp_groups SET group_name = %s, group_cash = %d, group_type = %d, group_owner = %d, group_value1 = %d, group_value2 = %d, group_dotation = %d, group_activity = %d WHERE group_uid = %d LIMIT 1,
	GroupData(group__id)(gName),

	GroupData(group__id)(gCash),

	GroupData(group__id)(gType),
	GroupData(group__id)(gOwner),

	GroupData(group__id)(gValue1),
	GroupData(group__id)(gValue2),

	GroupData(group__id)(gDotation),
	
	GroupData(group__id)(gActivity),
	GroupData(group__id)(gUID))
	return 1
)

public DeleteGroup(group__id)
(
	mysql_query_format(DELETE FROM hrp_groups WHERE group_uid = %d, GroupData(group__id)(gUID))

	// Zwolnij cz³onków
	mysql_query_format(DELETE FROM hrp_char_groups WHERE group_uid = %d, GroupData(group__id)(gUID))

	group_slot
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(IsPlayerInGroup(i, GroupData(group__id)(gUID)))
			(
				group_slot = GetPlayerGroupSlot(i, GroupData(group__id)(gUID))

				PlayerGroup(i)(group_slot)(gUID) = 0
				PlayerGroup(i)(group_slot)(gID) = 0

				PlayerGroup(i)(group_slot)(gPerm) = 0
				strmid(PlayerGroup(i)(group_slot)(gTitle), Brak, 0, 4, 32)

				PlayerGroup(i)(group_slot)(gPayment) = 0
			)
		)
	)

	// Usuñ pojazdy
	for(vehid = 1 vehid ( MAX_VEHICLES vehid++)
	(
		if(CarInfo(vehid)(cUID) && CarInfo(vehid)(cSpawned))
		(
			if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == GroupData(group__id)(gUID))
			(
				DeleteVehicle(vehid)
			)
		)
	)

	// Usuñ drzwi
	for(doorid = 1 doorid ( MAX_DOORS doorid++)
	(
		if(DoorData(doorid)(dUID))
		(
			if(DoorData(doorid)(dOwnerType) == OWNER_GROUP && DoorData(doorid)(dOwner) == GroupData(group__id)(gUID))
			(
				DeleteDoor(doorid)
			)
		)
	)
	
	// jeœli radiostacja
	if(GroupData(group__id)(gType) == GROUP_RADIO)
	(
		mysql_query_format(UPDATE hrp_characters SET char_station = 0 WHERE char_station = %d, GroupData(group__id)(gUID)) 
	)
	
	// jesli przestepcza to zony jeszcze zneutralizujmy
	if(GroupData(group__id)(gType) == GROUP_CRIMINAL)
	(
		for(i = 0  i ( MAX_ZONES i++)
		(
			if(ZoneInfo(i)(zOwner) == GroupData(group__id)(gUID))
			(
				ZoneInfo(i)(zOwner) = 0
				ZoneInfo(i)(zType) = 0
				ReloadZones()
			)
		)
	)
	
	// Usuñ podgrupy
	if(!GroupData(group__id)(gOwner))
	(
		for(g = 1 g ( MAX_GROUPS g++)
		(
			if(GroupData(g)(gUID))
			(
				if(GroupData(g)(gOwner) == GroupData(group__id)(gUID))
				(
					DeleteGroup(g)
				)
			)
		)
	)
	GroupData(group__id)(gUID) = 0
	GroupData(group__id)(gCash) = 0

	GroupData(group__id)(gType) = GROUP_NONE
	GroupData(group__id)(gOwner) = OWNER_NONE

	GroupData(group__id)(gValue1) = 0
	GroupData(group__id)(gValue2) = 0

	GroupData(group__id)(gDotation) = 0
	GroupData(group__id)(gColor) = 0
	
	GroupData(group__id)(gActivity) = 0
	Itter_Remove(Groups, group__id)
	return 1
)

public LoadGroups()
(
	group_id_fix, radio_id, data(128)
	mysql_query(SELECT * FROM hrp_groups)

 	print((load) Rozpoczynam proces wczytywania grup z bazy danych...)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		group_id_fix ++

		sscanf(data, p(|)ds(32)ddddddds(5)d,
		GroupData(group_id_fix)(gUID),
		GroupData(group_id_fix)(gName),

		GroupData(group_id_fix)(gCash),

		GroupData(group_id_fix)(gType),
		GroupData(group_id_fix)(gOwner),

		GroupData(group_id_fix)(gValue1),
		GroupData(group_id_fix)(gValue2),

		GroupData(group_id_fix)(gDotation),
		GroupData(group_id_fix)(gColor),
		
		GroupData(group_id_fix)(gTag),
		GroupData(group_id_fix)(gActivity))
		GroupData(group_id_fix)(gActionTime) = 0
		GroupData(group_id_fix)(gToggleChat) = true
		
		Itter_Add(Groups, group_id_fix)
		
		if(GroupData(group_id_fix)(gType) == GROUP_NEWS)
		(
			string(256)
			radio_id++
			
			RadioData(radio_id)(gUID) = GroupData(group_id_fix)(gUID)
			strmid(RadioData(radio_id)(gTag), GroupData(group_id_fix)(gTag), 0, strlen(GroupData(group_id_fix)(gTag)), 32)
			
			format(string, sizeof(string), %s ~)~ W radiu leci standardowy blok muzyczny., GroupData(group_id_fix)(gTag))
			TextDrawRadio(radio_id) = TextDrawCreate(2.000000, 438.000000, string)
			TextDrawBackgroundColor(TextDrawRadio(radio_id), 255)
			TextDrawFont(TextDrawRadio(radio_id), 1)
			TextDrawLetterSize(TextDrawRadio(radio_id), 0.250000, 0.899999)
			TextDrawColor(TextDrawRadio(radio_id), -1)
			TextDrawSetOutline(TextDrawRadio(radio_id), 1)
			TextDrawSetProportional(TextDrawRadio(radio_id), 1)
			TextDrawUseBox(TextDrawRadio(radio_id), 1)
			TextDrawBoxColor(TextDrawRadio(radio_id), 68)
			TextDrawTextSize(TextDrawRadio(radio_id), 640.000000, 600.000000)
		)
		
	)
	mysql_free_result()

	printf((load) Wczytano %d grup z bazy danych., group_id_fix)
	return 1
)

public ReloadGroup(group__id)
(
	data(128)
	mysql_query_format(SELECT * FROM hrp_groups WHERE group_uid = %d LIMIT 1, GroupData(group__id)(gUID))
	
	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ds(32)ddddddds(5)d,
		GroupData(group__id)(gUID),
		GroupData(group__id)(gName),
		
		GroupData(group__id)(gCash),

		GroupData(group__id)(gType),
		GroupData(group__id)(gOwner),
		
		GroupData(group__id)(gValue1),
		GroupData(group__id)(gValue2),
		
		GroupData(group__id)(gDotation),
		GroupData(group__id)(gColor),
		
		GroupData(group__id)(gTag),
		GroupData(group__id)(gActivity))
	)
	mysql_free_result()
	return 1
)

public ShowPlayerGroupInfo(playerid, group__id)
(
	list_stats(512), string(128)
	format(list_stats, sizeof(list_stats), Typ grupy:\t%s, GroupTypeInfo(GroupData(group__id)(gType))(gTypeName))
	format(list_stats, sizeof(list_stats), %s\nBud¿et:\t\t$%d\n, list_stats, GroupData(group__id)(gCash))

	format(list_stats, sizeof(list_stats), %s\nDotacja:\t$%d\n, list_stats, GroupData(group__id)(gDotation))

	if(GroupData(group__id)(gOwner))
	(
		group_owner_id = GetGroupID(GroupData(group__id)(gOwner))
		format(list_stats, sizeof(list_stats), %s\nNadrzêdna:\t%s (UID: %d)\n, list_stats, GroupData(group_owner_id)(gName), GroupData(group_owner_id)(gUID))
	)
	
	format(list_stats, sizeof(list_stats), %s\nTag:\t\t%s, list_stats, GroupData(group__id)(gTag))
	
	if(GroupData(group__id)(gType) == GROUP_SAWMILL || GroupData(group__id)(gType) == GROUP_QUARRY || GroupData(group__id)(gType) == GROUP_TIMBER)
	(
		format(list_stats, sizeof(list_stats), %s\nOpcja 1:\t\t%.1f ton, list_stats, (GroupData(group__id)(gValue1) * 0.1))
	)
	else
	(
		format(list_stats, sizeof(list_stats), %s\nOpcja 1:\t\t%d, list_stats, GroupData(group__id)(gValue1))
	)
	format(list_stats, sizeof(list_stats), %s\nOpcja 2:\t\t%.1f, list_stats, (GroupData(group__id)(gValue2) * 0.1))

	format(string, sizeof(string), %s (UID: %d) » Informacje, GroupData(group__id)(gName), GroupData(group__id)(gUID))
	ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, string, list_stats, Zamknij, )
	return 1
)

public LoadPlayerGroups(playerid)
(
	data(128), group_slot
	mysql_query_format(SELECT group_uid, group_perm, group_title, group_payment, group_skin, group_lastpayment FROM hrp_char_groups WHERE char_uid = %d LIMIT %d, PlayerCache(playerid)(pUID), MAX_GROUP_SLOTS)

	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)dds(32)ddd,
			PlayerGroup(playerid)(group_slot)(gUID),

			PlayerGroup(playerid)(group_slot)(gPerm),
			PlayerGroup(playerid)(group_slot)(gTitle),

			PlayerGroup(playerid)(group_slot)(gPayment),
			PlayerGroup(playerid)(group_slot)(gSkin),
			PlayerGroup(playerid)(group_slot)(gLastPayment))

			PlayerGroup(playerid)(group_slot)(gID) = GetGroupID(PlayerGroup(playerid)(group_slot)(gUID))
			group_slot ++
		)
	)
	mysql_free_result()
	LoadDutyTimes(playerid)
	return 1
)

stock LoadDutyTimes(playerid)
(
	data(128), day, month, year
	getdate(year, month, day)
	
	for(slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerGroup(playerid)(slot)(gUID))
		(
			start, end, time = 0
			
			mysql_query_format(SELECT duty_start, duty_end FROM hrp_duties WHERE duty_start )= UNIX_TIMESTAMP(%d-%d-%d) AND duty_owner = %d AND duty_typeuid = %d AND duty_end != 0, year, month, day, PlayerCache(playerid)(pUID), PlayerGroup(playerid)(slot)(gUID))
			mysql_store_result()
			if(mysql_num_rows() ) 0)
			(
				while(mysql_fetch_row(data, |))
				(
					sscanf(data, p(|)dd, start, end)
					time += end - start
					PlayerGroup(playerid)(slot)(gTodayDuty) += time
				)
			)
			mysql_free_result()
		)
	)
	return 1
)


stock GetGroupID(group_uid)
(
	group_id_fix = INVALID_GROUP_ID
	foreach(Groups, i)
	(
		if(GroupData(i)(gUID) == group_uid)
		(
			group_id_fix = i
			break
		)
	)
	return group_id_fix
)

stock IsPlayerInGroup(playerid, group_uid)
(
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerGroup(playerid)(slot)(gUID) == group_uid)
		(
			return true
		)
	)
	return false
)

stock GetPlayerGroupSlot(playerid, group_uid)
(
	group_slot = INVALID_SLOT_ID
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerGroup(playerid)(slot)(gUID))
		(
			if(PlayerGroup(playerid)(slot)(gUID) == group_uid)
			(
		 		group_slot = slot
		 		break
			)
		)
	)
	return group_slot
)

stock GetPlayerFreeGroupSlot(playerid)
(
	group_slot = INVALID_SLOT_ID
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(!PlayerGroup(playerid)(slot)(gUID))
		(
	 		group_slot = slot
	 		break
		)
	)
	return group_slot
)

stock GetPlayerDutyGroupID(playerid)
(
	group_id_fix = INVALID_GROUP_ID
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerCache(playerid)(pGroupDuty))
		(
			if(PlayerGroup(playerid)(slot)(gUID) == PlayerCache(playerid)(pGroupDuty))
			(
		 		group_id_fix = PlayerGroup(playerid)(slot)(gID)
		 		break
			)
		)
	)
	return group_id_fix
)

stock IsPlayerInGroupType(playerid, type)
(
	group_id_fix
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerGroup(playerid)(slot)(gUID))
		(
			group_id_fix = PlayerGroup(playerid)(slot)(gID)
			if(GroupData(group_id_fix)(gType) == type)
			(
				return true
			)
		)
	)
	return false
)

stock IsPlayerInAnyGroup(playerid)
(
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerGroup(playerid)(slot)(gUID))
		(
			return true
		)
	)
	return false
)

stock IsPlayerPermissedGroup(playerid, group_uid, permission)
(
	group_id_fix
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if((PlayerGroup(playerid)(slot)(gPerm) & permission))
		(
			if(PlayerGroup(playerid)(slot)(gUID) == group_uid)
			(
				return true
			)
			else
			(
				group_id_fix = GetGroupID(group_uid)
				if(GroupData(group_id_fix)(gOwner) == PlayerGroup(playerid)(slot)(gUID))
				(
					return true
				)
			)
		)
	)
	return false
)

stock AddGroupEvent(group_uid, seller, buyer, cash, gcash, desc())
(
	mysql_query_format(INSERT INTO hrp_roffers (offer_uid, offer_group, offer_seller, offer_buyer, offer_cash, offer_gcash, offer_desc) VALUES(NULL, %d, %d, %d, %d, %d, %s), group_uid, seller, buyer, cash, gcash, desc)
	return 1
)

stock AddGroupLog(playerid, group_id_fix, desc(), va_args())
(
	qdesc(256)
	va_format(qdesc, sizeof(qdesc), desc, va_start(3))

	mysql_query_format(INSERT INTO hrp_group_logs (log_uid, log_group_uid, log_char_uid, log_char_gid, log_time, log_desc) VALUES(NULL, %d, %d, %d, unix_timestamp(now()), %s), GroupData(group_id_fix)(gUID), PlayerCache(playerid)(pUID), PlayerCache(playerid)(pGID), qdesc)
	return 1
)

// ------------------------------

stock CreateCard(group_uid, limit)
(
	mysql_query_format(INSERT INTO hrp_cards VALUES (NULL, %d, %d, %d), group_uid, limit, limit)

	card_uid = mysql_insert_id()
	LoadCard(card_uid)
	return card_uid
)

stock SaveCard(cardid)
(
	mysql_query_format(UPDATE hrp_cards SET card_group = %d, card_limit = %d, card_balance = %d WHERE card_uid = %d LIMIT 1,
	Cards(cardid)(cardGroup),
	Cards(cardid)(cardLimit),
	Cards(cardid)(cardBalance),
	Cards(cardid)(cardUID))
	return 1
)

stock LoadCard(card_uid)
(
	data(128), cardid = Itter_Free(Cards)
	mysql_query_format(SELECT * FROM hrp_cards WHERE card_uid = %d LIMIT 1, card_uid)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)dddd,
		Cards(cardid)(cardUID),
		Cards(cardid)(cardGroup),
		Cards(cardid)(cardLimit),
		Cards(cardid)(cardBalance))
		
		Itter_Add(Cards, cardid)
	)
	mysql_free_result()
	return 1
)

stock GetCardID(card_uid)
(
	foreach(Cards, cardid)
	(
		printf(%d, %d, cardid, Cards(cardid)(cardUID))
		if(Cards(cardid)(cardUID) == card_uid)
		(
			return cardid
		)
	)

	return -1
)

stock IsCardValid(cardid, price)
(
	group_id_fix = GetGroupID(Cards(cardid)(cardGroup))
	if(GroupData(group_id_fix)(gCash) )= price && Cards(cardid)(cardBalance) )= price)
		return true
	else
		return false
)

stock ChargeCard(cardid, price)
(
	group_id_fix = Cards(cardid)(cardGroup)
	GroupData(group_id_fix)(gCash) -= price
	SaveGroup(group_id_fix)
	
	Cards(cardid)(cardBalance) -= price
	SaveCard(cardid)
	return 1
)

stock IsPlayerGroupLimited(playerid, group_id_fix)
(
	// true, gdy jest limit, false gdy limitu nie ma
	bool:limited = false
	mysql_query_format(SELECT * FROM hrp_groups_limit WHERE limit_char = %d AND limit_group = %d, PlayerCache(playerid)(pUID), GroupData(group_id_fix)(gUID))
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		limited = true
		mysql_free_result()
	)
	else
	(
		limited = false
		mysql_free_result()
	)
	return limited
)

stock AddPlayerGroupLimit(playerid, group_id_fix)
(
	mysql_query_format(INSERT INTO hrp_groups_limit VALUES(NULL, %d, %d), PlayerCache(playerid)(pUID), GroupData(group_id_fix)(gUID))
	return 1
)

/* -------------------------------------------------------
  Trzeba dodaæ strefy dla biznesów do bicia duty
  ------------------------------------------------------- */
  
