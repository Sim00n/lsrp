public LoadPlayerPunish(playerid)
(
	date = gettime(), data(128), punish_type, punish_value, punish_reason(64), string(128)
	mysql_query_format(SELECT punish_type, punish_value, punish_reason FROM hrp_punishlogs WHERE punish_owneruid = %d AND (punish_end ) %d OR punish_end = 0), PlayerCache(playerid)(pUID), date)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)dds(64), punish_type, punish_value, punish_reason)
		
		switch(punish_type)
		(
			case PUNISH_WARN:
			(
				PlayerCache(playerid)(pWarns) ++
			)
			case PUNISH_BLOCK_CHAR:
			(
				format(string, sizeof(string), Ta postaæ zosta³a zablokowana z powodem: %s\n\nZa³ó¿ now¹ lub ubiegaj siê o odblokowanie poprzedniej., punish_reason)
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
			
				Kick(playerid)
				break
			)
			case PUNISH_BLOCK_VEH:
			(
				PlayerCache(playerid)(pBlock) += BLOCK_VEH
			)
			case PUNISH_BLOCK_RUN:
			(
				PlayerCache(playerid)(pBlock) += BLOCK_RUN
			)
			case PUNISH_BLOCK_OOC:
			(
				PlayerCache(playerid)(pBlock) += BLOCK_OOC
			)
			case PUNISH_BLOCK_OBJ:
			(
				PlayerCache(playerid)(pBlock) += BLOCK_OBJ
			)
			case PUNISH_AJ:
			(
				if(punish_value ) 0)
				(
					PlayerCache(playerid)(pAJ) += punish_value
				)
			)
		)
	)
	mysql_free_result()
	return 1
)

public AddPlayerPunishLog(playerid, giveplayer_id, punish_type, reason(), days)
(
	giverid = -1
	if(giveplayer_id != -1)
	(
		giverid = PlayerCache(giveplayer_id)(pUID)
	)

	if(punish_type == PUNISH_AJ)
	(
 		mysql_query_format(INSERT INTO hrp_punishlogs (punish_giveruid, punish_owneruid, punish_type, punish_reason, punish_datetime, punish_value) VALUES (%d, %d, %d, %s, NOW(), %d), giverid, PlayerCache(playerid)(pUID), punish_type, reason, days*60)
	)
	else
	(
		end_time = 0
		if(days ) 0)
		(
			end_time = gettime() + ((60 * 60 * 24) * days)
		)
		if(giveplayer_id == -1)
	 	(
	 	   	mysql_query_format(INSERT INTO hrp_punishlogs (punish_giveruid, punish_owneruid, punish_type, punish_reason, punish_datetime, punish_end) VALUES (-1, %d, %d, %s, NOW(), %d), PlayerCache(playerid)(pUID), punish_type, reason, end_time)
		)
		else
		(
			mysql_query_format(INSERT INTO hrp_punishlogs (punish_giveruid, punish_owneruid, punish_type, punish_reason, punish_datetime, punish_end) VALUES (%d, %d, %d, %s, NOW(), %d), giverid, PlayerCache(playerid)(pUID), punish_type, reason, end_time)
		)
		if(punish_type == PUNISH_BAN)
		(
			mysql_query_format(INSERT INTO hrp_punishlogs (punish_giveruid, punish_owneruid, punish_type, punish_reason, punish_datetime, punish_end) VALUES (%d, %d, %d, %s, NOW(), %d), giverid, PlayerCache(playerid)(pUID), PUNISH_BLOCK_CHAR, Blokada postaci po banie, end_time)
	 		return 1
		)
	)
	return 1
)

// Punishes
hrp_Kick(playerid, giveplayer_id, reason(), log_skip = false)
(
	string(256), giver_name(24)
	if(giveplayer_id == -1) strmid(giver_name, System, 0, 6, 24)
	else					strmid(giver_name, PlayerName(giveplayer_id), 0, strlen(PlayerName(giveplayer_id)), 24)
	
	EscapePL(reason)

	PlayerCache(playerid)(pQuit) = QUIT_KICK
	
	if(!log_skip)
	(
		AddPlayerPunishLog(playerid, giveplayer_id, PUNISH_KICK, reason, 0)
	)
	
	format(string, sizeof(string), ~r~~h~Kick~n~~w~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, PlayerName(playerid), giver_name, reason)
	TextDrawSetString(Text:TextDrawPunishInfo, string)
	
	TextDrawShowForAll(Text:TextDrawPunishInfo)

	Kick(playerid)
	
	PunishTime = 15
	
	if(!log_skip)
	(
		if(giveplayer_id != -1)
			hrp_AdminActionLog(%s (UID: %d) wyrzucil %s (UID: %d) z gry. Powod: %s, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), reason)
	)
	return 1
)

hrp_Warn(playerid, giveplayer_id, reason(), days)
(
	string(256), giver_name(24)
	if(giveplayer_id == -1) strmid(giver_name, System, 0, 6, 24)
	else					strmid(giver_name, PlayerName(giveplayer_id), 0, strlen(PlayerName(giveplayer_id)), 24)
	
	EscapePL(reason)
	
	PlayerCache(playerid)(pWarns) ++
	if(PlayerCache(playerid)(pWarns) ( 5)
	(
		AddPlayerPunishLog(playerid, giveplayer_id, PUNISH_WARN, reason, days)
		
		format(string, sizeof(string), ~r~~h~Warn ~w~(warns: %d/5)~n~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, PlayerCache(playerid)(pWarns), PlayerName(playerid), giver_name, reason)
		TextDrawSetString(Text:TextDrawPunishInfo, string)
		
 		TextDrawShowForAll(Text:TextDrawPunishInfo)
 		
		PunishTime = 15
		
		hrp_AdminActionLog(%s (UID: %d) nadal ostrzezenie %s (UID: %d). Powod: %s, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), reason)
	)
	else
	(
		format(string, sizeof(string), %s (warns: 5/5), reason)
		hrp_Ban(playerid, giveplayer_id, string, 0)
	)
	return 1
)

hrp_Block(playerid, giveplayer_id, reason(), block_type, days, raw=false)
(
	string(256), giver_name(24)
	if(giveplayer_id == -1) strmid(giver_name, System, 0, 6, 24)
	else					strmid(giver_name, PlayerName(giveplayer_id), 0, strlen(PlayerName(giveplayer_id)), 24)

	EscapePL(reason)
	
	switch(block_type)
	(
		case BLOCK_CHAR:
		(
			if(!raw)
			(
		 		format(string, sizeof(string), ~r~~h~Blokada postaci~n~~w~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, PlayerName(playerid), giver_name, reason)
				hrp_AdminActionLog(%s (UID: %d) nalozyl blokade na postac %s (UID: %d). Powod: %s, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), reason)
			)

			AddPlayerPunishLog(playerid, giveplayer_id, PUNISH_BLOCK_CHAR, reason, days)
		)
		case BLOCK_VEH:
		(
  			if(!raw)
  			(
				format(string, sizeof(string), ~r~~h~Blokada prowadzenia pojazdow~n~~w~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, PlayerName(playerid), giver_name, reason)
				hrp_AdminActionLog(%s (UID: %d) nalozyl blokade prowadzenia pojazdow dla %s (UID: %d). Powod: %s, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), reason)
			)
			
			AddPlayerPunishLog(playerid, giveplayer_id, PUNISH_BLOCK_VEH, reason, days)
		)
		case BLOCK_RUN:
		(
			if(!raw)
			(
				format(string, sizeof(string), ~r~~h~Blokada biegania i bicia~n~~w~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, PlayerName(playerid), giver_name, reason)
				hrp_AdminActionLog(%s (UID: %d) nalozyl blokade biegania i bicia dla %s (UID: %d). Powod: %s, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), reason)
			)
			
			AddPlayerPunishLog(playerid, giveplayer_id, PUNISH_BLOCK_RUN, reason, days)
		)
		case BLOCK_OOC:
		(
			if(!raw)
			(
	  			format(string, sizeof(string), ~r~~h~Blokada czatu OOC~n~~w~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, PlayerName(playerid), giver_name, reason)
				hrp_AdminActionLog(%s (UID: %d) nalozyl blokade czatu OOC dla %s (UID: %d). Powod: %s, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), reason)
			)
			
			AddPlayerPunishLog(playerid, giveplayer_id, PUNISH_BLOCK_OOC, reason, days)
		)
		case BLOCK_OBJ:
		(
			if(!raw)
			(
	  			format(string, sizeof(string), ~r~~h~Blokada edycji obiektow~n~~w~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, PlayerName(playerid), giver_name, reason)
				hrp_AdminActionLog(%s (UID: %d) nalozyl blokade edycji obiektow dla %s (UID: %d). Powod: %s, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), reason)
			)
			
			AddPlayerPunishLog(playerid, giveplayer_id, PUNISH_BLOCK_OBJ, reason, days)
		)
	)

	if(!raw)
	(
		TextDrawSetString(Text:TextDrawPunishInfo, string)
		TextDrawShowForAll(Text:TextDrawPunishInfo)
	)
	
	PlayerCache(playerid)(pBlock) += block_type
	SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
	
	if(block_type == BLOCK_CHAR) Kick(playerid)
	
	PunishTime = 15
	return 1
)

hrp_Ban(playerid, giveplayer_id, reason(), days)
(
	string(256), giver_name(24), IP(16)
	if(giveplayer_id == -1) strmid(giver_name, System, 0, 6, 24)
	else					strmid(giver_name, PlayerName(giveplayer_id), 0, strlen(PlayerName(giveplayer_id)), 24)
	
	EscapePL(reason)
	
	if(giveplayer_id != 1 && IsPlayerConnected(giveplayer_id))
	(
		PlayerCache(giveplayer_id)(pQuit) = QUIT_BAN
	)
	AddPlayerPunishLog(playerid, giveplayer_id, PUNISH_BAN, reason, days)
	
	format(string, sizeof(string), ~r~~h~Ban~n~~w~Gracz:	%s~n~Nadajacy: %s~n~~y~~h~%s, PlayerName(playerid), giver_name, reason)
	TextDrawSetString(Text:TextDrawPunishInfo, string)

	TextDrawShowForAll(Text:TextDrawPunishInfo)
	// Jeœli jest w pojeŸdzie
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	(
		vehid = GetPlayerVehicleID(playerid)
		SetVehicleToRespawn(vehid)
		
		CarInfo(vehid)(cEngineTogged) = false
		CarInfo(vehid)(cLocked) = true
		
		ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))
		SetVehicleLock(vehid, CarInfo(vehid)(cLocked))
		
		SaveVehicle(vehid, SAVE_VEH_COUNT)
	)
	
	mysql_query_format(UPDATE members SET member_group_id = 5 WHERE member_gid = %d LIMIT 1, PlayerCache(playerid)(pGID))
	
	PlayerCache(playerid)(pBlock) += BLOCK_CHAR
	
	ban_time = 0
	if(days ) 0)
	(
		ban_time = gettime() + ((60*60*24) * days)
	)

	GetPlayerIp(playerid, IP, sizeof(IP))
	mysql_query_format(INSERT INTO hrp_bans (ban_type, ban_ip, ban_ownergid, ban_ownerchar, ban_reason, ban_time) VALUES(1, %s, %d, %d, %s, %d), IP, PlayerCache(playerid)(pGID), PlayerCache(playerid)(pUID), reason, ban_time)

	PunishTime = 15

	Kick(playerid)
	return 1
)

hrp_AdminJail(playerid, giveplayer_id, reason(), time)
(
	string(256), giver_name(24)
	if(giveplayer_id == -1) strmid(giver_name, System, 0, 6, 24)
	else					strmid(giver_name, PlayerName(giveplayer_id), 0, strlen(PlayerName(giveplayer_id)), 24)
	
	EscapePL(reason)
	
	AddPlayerPunishLog(playerid, giveplayer_id, PUNISH_AJ, reason, time)

	format(string, sizeof(string), ~r~~h~AdminJail~n~~w~Gracz:	 %s~n~Nadajacy: %s~n~~y~~h~%s, PlayerName(playerid), giver_name, reason)
	TextDrawSetString(Text:TextDrawPunishInfo, string)

	TextDrawShowForAll(Text:TextDrawPunishInfo)

	hrp_SetPlayerPos(playerid, 154.1221, -1951.9156, 47.8750)
	SetPlayerInterior(playerid, 0)
	SetPlayerVirtualWorld(playerid, playerid + 1000)

	// Jeœli jest w pojeŸdzie
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	(
		vehid = GetPlayerVehicleID(playerid)
		SetVehicleToRespawn(vehid)

		CarInfo(vehid)(cEngineTogged) = false
		CarInfo(vehid)(cLocked) = true

		ChangeVehicleEngineStatus(vehid, CarInfo(vehid)(cEngineTogged))
		SetVehicleLock(vehid, CarInfo(vehid)(cLocked))

		SaveVehicle(vehid, SAVE_VEH_COUNT)
	)
	PlayerCache(playerid)(pAJ) = time * 60
	
	PunishTime = 15
	
	hrp_AdminActionLog(%s (UID: %d) uwiezil %s (UID: %d) w AdminJail. Czas AJ: %d min. Powod: %s, PlayerName(giveplayer_id), PlayerCache(giveplayer_id)(pUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), time * 60, reason)
	return 1
)

stock hrp_HardwareBan(playerid, target_id, gpci(100))
(
	mysql_query_format(INSERT INTO hrp_hardbans VALUES(NULL, %s, %d), gpci, PlayerCache(target_id)(pGID))
	hrp_AdminActionLog(%s (UID: %d) nadal hardware bana graczowi %s (UID: %d), PlayerName(playerid), PlayerCache(playerid)(pUID), PlayerRealName(target_id), PlayerCache(target_id)(pUID))
	return 1
)

stock getPlayerSerial(playerid)
(
	serial(100)
	gpci(playerid, serial, sizeof(serial))
	return serial
)

/*stock isPlayerHardBanned(playerid)
(
	buffer(256), serial(100)
	gpci(playerid, serial, sizeof(serial))
	format(buffer, sizeof(buffer), SELECT * FROM hrp_hardbans WHERE ban_serial = %s, serial)
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		mysql_free_result()
		return true
	)
	else
	(
		mysql_free_result()
		return false
	)
)

stock isPlayerHardPassed(playerid)
(
	buffer(256), serial(100)
	gpci(playerid, serial, sizeof(serial))
	format(buffer, sizeof(buffer), SELECT * FROM hrp_hardfilter WHERE filter_gid = %d, PlayerCache(playerid)(pGID))
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		mysql_free_result()
		return true
	)
	else
	(
		mysql_free_result()
		return false
	)
)*/