CMD:loadtime(playerid,params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid,Brak uprawnieñ do wykonania tej komendy.,1)
		return 1
	)
	
	reps
	if(sscanf(params,d,reps))
	(
		hrp_Tip(playerid,/loadtime (ilosc sekund))
		return 1
	)
	
	PlayerCache(playerid)(pPackingTime) = reps
	
	return 1
)

CMD:zlecenie(playerid,params())
(
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /zlecenie (rozpocznij | zakoncz))
	 	return 1
	)
	
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		GuiMsg(playerid,Musisz byæ na s³u¿bie grupy przewozowej.,1)
		return 1
	)
	
	group_id_fix = GetPlayerDutyGroupID(playerid)
	if(GroupData(group_id_fix)(gType) != GROUP_TRUCKERS)
	(
		GuiMsg(playerid,Musisz byæ na s³u¿bie grupy przewozowej.,1)
		return 1
	)
	
	if(!IsPlayerInAnyVehicle(playerid))
	(
		GuiMsg(playerid,Musisz siedzieæ w pojeŸdzie by aktywowaæ jakiekolwiek ze zleceñ.,1)
		return 1
	)
	
	if(GetPlayerVehicleSeat(playerid) != 0)
	(
		GuiMsg(playerid,Musisz byæ kierowc¹ tego pojazdu by móc u¿yæ tej komendy.,1)
		return 1
	)
	
	vehicleid = GetPlayerVehicleID(playerid)
	model = GetVehicleModel(vehicleid)
	//if(model != 403 && model != 514 && model != 515) 413
	if(model != 403 && model != 514 && model != 515 && model != 413 && model != 440 && model != 456 && model != 482 && model != 498 && model != 499)
	(
		GuiMsg(playerid,Tej komendy mo¿esz u¿ywaæ tylko w pojazdach ciê¿arowych.,1)
		return 1
	)
	
	if(!strcmp(type, rozpocznij, true))
	(
		if(PlayerCache(playerid)(pTrucking))
		(
			GuiMsg(playerid,Jedno zlecenie jest ju¿ aktywne.,1)
			return 1
		)
		
		CreatePlayerTrack(playerid)
		
	)
	
	if(!strcmp(type, zakoncz, true))
	(
		if(!PlayerCache(playerid)(pTrucking))
		(
			GuiMsg(playerid,Nie jesteœ w trakcie realizacji ¿adnego zlecenia.,1)
			return 1
		)
		
		DestroyPlayerTrack(playerid)
		GuiMsg(playerid,Anulowa³eœ zlecenie.,1)
	)
	
	return 1
)

CMD:wyladuj(playerid,params())
(
	if(!PlayerCache(playerid)(pTrucking))
	(
		GuiMsg(playerid,Nie jesteœ w trakcie realizacji ¿adnego zlecenia.,1)
		return 1
	)
	
	if(PlayerCache(playerid)(pPackingPhase) != TRUCK_PHASE_LOADED)
	(
		GuiMsg(playerid,Nie mo¿esz jeszcze wy³adowaæ ¿adnego ³adunku.,1)
		return 1
	)
	
	if(PlayerCache(playerid)(pPackingTime) ) 0)
	(
		return 1
	)
	
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	
	orderid = PlayerCache(playerid)(pTrackID), buffer(256),  Float:Pos(3)
	
	format(buffer,sizeof(buffer),SELECT to FROM hrp_truck_route WHERE uid=%i,orderid)
	mysql_query(buffer)
	mysql_store_result()
	to = mysql_fetch_int()
	mysql_free_result()
	
	format(buffer,sizeof(buffer),SELECT posx,posy,posz FROM hrp_truck_target WHERE uid=%i,to)
	mysql_query(buffer)
	mysql_store_result()
	
	while(mysql_fetch_row(buffer, |))
	(
		sscanf(buffer,p(|)fff,Pos(0),Pos(1),Pos(2))
	)
	
	format(PlayerCache(playerid)(pUnloadPos),32,%f|%f|%f,Pos(0),Pos(1),Pos(2))
	
	mysql_free_result()
	
	if(!IsPlayerInRangeOfPoint(playerid,8.0,Pos(0),Pos(1),Pos(2)))
	(
		GuiMsg(playerid,Musisz byæ w pobli¿u magazynu by móc pobraæ towar.,1)
		return 1
	)
	
	PlayerCache(playerid)(pPackingTime) = 120
	PlayerCache(playerid)(pPackingPhase) = TRUCK_PHASE_UNLOAD
	
	
	return 1
)

CMD:zaladuj(playerid,params())
(
	if(!PlayerCache(playerid)(pTrucking))
	(
		GuiMsg(playerid,Nie jesteœ w trakcie realizacji ¿adnego zlecenia.,1)
		return 1
	)
	
	if(PlayerCache(playerid)(pPackingPhase) != TRUCK_PHASE_RIDE)
	(
		return 1
	)
	
	if(PlayerCache(playerid)(pPackingTime) ) 0)
	(
		return 1
	)
	
	if(!PlayerCache(playerid)(pGroupDuty))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby skorzystaæ z tej komendy, musisz byæ na s³u¿bie grupy., OK, )
		return 1
	)
	
	orderid = PlayerCache(playerid)(pTrackID), buffer(256),  Float:Pos(3)
	
	format(buffer,sizeof(buffer),SELECT from FROM hrp_truck_route WHERE uid=%i,orderid)
	mysql_query(buffer)
	mysql_store_result()
	from = mysql_fetch_int()
	mysql_free_result()
	
	format(buffer,sizeof(buffer),SELECT posx,posy,posz FROM hrp_truck_target WHERE uid=%i,from)
	mysql_query(buffer)
	mysql_store_result()
	
	while(mysql_fetch_row(buffer, |))
	(
		sscanf(buffer,p(|)fff,Pos(0),Pos(1),Pos(2))
	)
	
	mysql_free_result()
	
	if(!IsPlayerInRangeOfPoint(playerid,8.0,Pos(0),Pos(1),Pos(2)))
	(
		GuiMsg(playerid,Musisz byæ w pobli¿u magazynu by móc pobraæ towar.,1)
		return 1
	)
	
	PlayerCache(playerid)(pPackingTime) = 120
	PlayerCache(playerid)(pPackingPhase) = TRUCK_PHASE_LOAD
	
	return 1
)

stock CreatePlayerTrack(playerid)
(
	vehicleid = GetPlayerVehicleID(playerid), model = GetVehicleModel(GetPlayerVehicleID(playerid))
	if(!IsTrailerAttachedToVehicle(vehicleid) && model != 413 && model != 440 && model != 456 && model != 482 && model != 498 && model != 499)
	(
		GuiMsg(playerid,Nie posiadasz naczepy, wiêc nie mo¿esz pobraæ ¿adnego zlecenia.,1)
		return 1
	)
	
	trailer = -1, record = -1
	if(IsTrailerAttachedToVehicle(vehicleid))
	(
		// TIR
		trailer = GetVehicleTrailer(vehicleid)
		record = GetRandomTrack(GetVehicleModel(trailer))
	)
	else
	(
		// NIE TIR
		record = GetVanTrack(GetVehicleModel(vehicleid))
	)
	
	//printf(trailerid: %i | trailer model: %i,trailer,GetVehicleModel(trailer))
	
	//record = uid trasowania
	PlayerCache(playerid)(pTrackID) = record
	PlayerCache(playerid)(pTrailerID) = trailer
	PlayerCache(playerid)(pPackingPhase) = TRUCK_PHASE_RIDE
	PlayerCache(playerid)(pTrucking) = true
	
	buffer(256)
	format(buffer,sizeof(buffer),SELECT from FROM hrp_truck_route WHERE uid=%i,record)
	mysql_query(buffer)
	mysql_store_result()
	from = mysql_fetch_int()
	mysql_free_result()
	
	format(buffer,sizeof(buffer),SELECT posx,posy,posz,company,town FROM hrp_truck_target WHERE uid=%i,from)
	mysql_query(buffer)
	mysql_store_result()
	Float:Pos(3), company(32), town(32)
	
	while(mysql_fetch_row(buffer, |))
	(
		sscanf(buffer,p(|)fffs(32)s(32),Pos(0),Pos(1),Pos(2),company,town)
	)
	
	mysql_free_result()
	
	string(256)
	format(string,sizeof(string),(CCCCCC)Przyj¹³eœ zlecenie od firmy (C4B100)%s\n(CCCCCC)Miejsce docelowe: (C4B100)%s\n\n(CCCCCC)Powodzenia! Musisz udaæ siê we wskazane miejsce by za³adowaæ towar.,
	company,town)
	GuiMsg(playerid,string,0)
	
	SetPlayerCheckpoint(playerid, Pos(0),Pos(1),Pos(2), 7.0)
	Checkpoint(playerid) = 0
	
	return 1
)

stock DestroyPlayerTrack(playerid)
(
	PlayerCache(playerid)(pTrackID) = 0
	PlayerCache(playerid)(pTrailerID) = 0
	PlayerCache(playerid)(pPackingPhase) = 0
	PlayerCache(playerid)(pTrucking) = false
	PlayerCache(playerid)(pPackingTime) = 0
	
	DisablePlayerCheckpoint(playerid)
	return 1
)

stock GetVanTrack(model)
(
	buffer(256)
	format(buffer,sizeof(buffer),SELECT uid FROM hrp_truck_route WHERE trailer=%i ORDER BY RAND() LIMIT 1, model)
	
	mysql_query(buffer)
	mysql_store_result()
	sql = mysql_fetch_int()
	mysql_free_result()
	
	return sql
)

stock GetRandomTrack(trailer)
(
	buffer(256)
	switch(trailer)
	(
		case TRAILER_TYPE_FOOD:
		(
			format(buffer,sizeof(buffer),SELECT uid FROM hrp_truck_route WHERE trailer=%i ORDER BY RAND() LIMIT 1,TRAILER_TYPE_FOOD)
		)
		case TRAILER_TYPE_MATERIALS:
		(
			format(buffer,sizeof(buffer),SELECT uid FROM hrp_truck_route WHERE trailer=%i ORDER BY RAND() LIMIT 1,TRAILER_TYPE_MATERIALS)
		)
		case TRAILER_TYPE_OIL:
		(
			format(buffer,sizeof(buffer),SELECT uid FROM hrp_truck_route WHERE trailer=%i ORDER BY RAND() LIMIT 1,TRAILER_TYPE_OIL)
		)
		case TRAILER_TYPE_TOOLS:
		(
			format(buffer,sizeof(buffer),SELECT uid FROM hrp_truck_route WHERE trailer=%i ORDER BY RAND() LIMIT 1,TRAILER_TYPE_TOOLS)
		)
	)
	
	mysql_query(buffer)
	mysql_store_result()
	sql = mysql_fetch_int()
	mysql_free_result()
	
	return sql
)