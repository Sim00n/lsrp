public AddGangZone(Float:MinX, Float:MinY, Float:MaxX, Float:MaxY)
(
	gangzone_uid, gangzone_id
	mysql_query_format(INSERT INTO hrp_gangzones (gangzone_minx, gangzone_miny, gangzone_maxx, gangzone_maxy) VALUES (%f, %f, %f, %f), MinX, MinY, MaxX, MaxY)

	gangzone_uid = mysql_insert_id()
	gangzone_id = GangZoneCreate(MinX, MinY, MaxX, MaxY)

	GangZoneInfo(gangzone_id)(gUID) = gangzone_uid

	GangZoneInfo(gangzone_id)(gMinX) = MinX
	GangZoneInfo(gangzone_id)(gMinY) = MinY
	GangZoneInfo(gangzone_id)(gMaxX) = MaxX
	GangZoneInfo(gangzone_id)(gMaxY) = MaxY
	
	GangZoneInfo(gangzone_id)(gOwner) = 0
	GangZoneInfo(gangzone_id)(gMarihuana) = 0
	GangZoneInfo(gangzone_id)(gAmp) = 0
	GangZoneInfo(gangzone_id)(gMetaamp) = 0
	GangZoneInfo(gangzone_id)(gProfit) = 0
	GangZoneInfo(gangzone_id)(gRobberies) = 0
	GangZoneInfo(gangzone_id)(gAttack) = 0
	
	Itter_Add(GangZones, gangzone_id)
	
	// Poka¿ tylko dla org przestêpczych
	/*foreach(Player, i)
	(
 		if(Logged(i) && Spawned(i))
   		(
			GangZoneShowForPlayer(i, gangzone_id, 0xFFFFFF66)
		)
	)*/
	return gangzone_id
)

public LoadGangZones()
(
	data(128), gangzone_id = 0
	mysql_query(SELECT * FROM hrp_gangzones)

	print((load) Rozpoczynam proces wczytywania wszystkich GangZone z bazy...)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)dffffddddddd,
		GangZoneInfo(gangzone_id)(gUID),

		GangZoneInfo(gangzone_id)(gMinX),
		GangZoneInfo(gangzone_id)(gMinY),
		GangZoneInfo(gangzone_id)(gMaxX),
		GangZoneInfo(gangzone_id)(gMaxY),
		
		GangZoneInfo(gangzone_id)(gOwner),
		GangZoneInfo(gangzone_id)(gMarihuana),
		GangZoneInfo(gangzone_id)(gAmp),
		GangZoneInfo(gangzone_id)(gMetaamp),
		GangZoneInfo(gangzone_id)(gProfit),
		GangZoneInfo(gangzone_id)(gRobberies),
		GangZoneInfo(gangzone_id)(gAttack))
		
		GangZoneCreate(GangZoneInfo(gangzone_id)(gMinX), GangZoneInfo(gangzone_id)(gMinY), GangZoneInfo(gangzone_id)(gMaxX), GangZoneInfo(gangzone_id)(gMaxY))
		Itter_Add(GangZones, gangzone_id)

		gangzone_id ++
	)
	mysql_free_result()

	printf((load) Wczytano %d GangZone z bazy danych., gangzone_id)
	return 1
)

public SaveGangZone(gangzone_id, what)
(
	query(256), main_query(512)
	format(main_query, sizeof(main_query), UPDATE hrp_gangzones SET)

	if(what & SAVE_GZ_POS)
	(
		format(query, sizeof(query),  gangzone_minx = %f, gangzone_miny = %f, gangzone_maxx = %f, gangzone_maxy = %f,
		GangZoneInfo(gangzone_id)(gMinX),
		GangZoneInfo(gangzone_id)(gMinY),
		GangZoneInfo(gangzone_id)(gMaxX),
		GangZoneInfo(gangzone_id)(gMaxY))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_GZ_OWNER)
	(
		format(query, sizeof(query),  gangzone_owner = %d, GangZoneInfo(gangzone_id)(gOwner))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_GZ_THINGS)
	(
		format(query, sizeof(query),  gangzone_marihuana = %d, gangzone_amp = %d, gangzone_metaamp = %d, gangzone_profit = %d, gangzone_robberies = %d, gangzone_attack = %d,
		GangZoneInfo(gangzone_id)(gMarihuana),
		GangZoneInfo(gangzone_id)(gAmp),
		GangZoneInfo(gangzone_id)(gMetaamp),
		GangZoneInfo(gangzone_id)(gProfit),
		GangZoneInfo(gangzone_id)(gRobberies),
		GangZoneInfo(gangzone_id)(gAttack))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
		strcat(main_query, query, sizeof(main_query))
	)

	format(query, sizeof(query),  WHERE gangzone_uid = %d LIMIT 1, GangZoneInfo(gangzone_id)(gUID))
	strcat(main_query, query, sizeof(main_query))
	
	print(main_query)

	if(mysql_query(main_query))
	(
		print(success)
	) else (
		print(error)
		test(256)
		mysql_error(test)
		print(test)
	)
	return 1
)

public DeleteGangZone(gangzone_id)
(
	mysql_query_format(DELETE FROM hrp_gangzones WHERE gangzone_uid = %d LIMIT 1, GangZoneInfo(gangzone_id)(gUID))

	GangZoneInfo(gangzone_id)(gUID) = 0
	
	GangZoneInfo(gangzone_id)(gMinX) = 0.0
	GangZoneInfo(gangzone_id)(gMinY) = 0.0
	GangZoneInfo(gangzone_id)(gMaxX) = 0.0
	GangZoneInfo(gangzone_id)(gMaxY) = 0.0
	
	GangZoneInfo(gangzone_id)(gOwner) = 0
	GangZoneInfo(gangzone_id)(gMarihuana) = 0
	GangZoneInfo(gangzone_id)(gAmp) = 0
	GangZoneInfo(gangzone_id)(gMetaamp) = 0
	GangZoneInfo(gangzone_id)(gProfit) = 0
	GangZoneInfo(gangzone_id)(gRobberies) = 0
	GangZoneInfo(gangzone_id)(gAttack) = 0
	
	GangZoneDestroy(gangzone_id)
	
	Itter_Remove(GangZones, gangzone_id)
	return 1
)

stock IsPlayerInGangZone(playerid, gangzone_id)
(
	if(IsPlayerInArea(playerid, GangZoneInfo(gangzone_id)(gMaxX), GangZoneInfo(gangzone_id)(gMinX), GangZoneInfo(gangzone_id)(gMaxY), GangZoneInfo(gangzone_id)(gMinY)))
		return true
	
	return false
)

stock GetCurrentPlayerGangZone(playerid) (
	foreach(GangZones, gangzone_id)
	(
		if(GangZoneInfo(gangzone_id)(gUID))
		(
			if(IsPlayerInArea(playerid, GangZoneInfo(gangzone_id)(gMaxX), GangZoneInfo(gangzone_id)(gMinX), GangZoneInfo(gangzone_id)(gMaxY), GangZoneInfo(gangzone_id)(gMinY)))
			(
				return gangzone_id
			)
		)
	)
	return -1
)

stock GetGangZoneAt(Float:gPosX, Float:gPosY)
(
	foreach(GangZones, gangzone_id)
	(
		Float:minX = GangZoneInfo(gangzone_id)(gMinX),
			Float:minY = GangZoneInfo(gangzone_id)(gMinY),
			Float:maxX = GangZoneInfo(gangzone_id)(gMaxX),
			Float:maxY = GangZoneInfo(gangzone_id)(gMaxY)

		if((gPosX )= minX && gPosX (= maxX) && (gPosY )= minY && gPosY (= maxY))
		(
			return gangzone_id
		)
	)

	return -1
)

stock GangZoneShow(playerid, gangzone_id)
(
	GangZoneHideForPlayer(playerid, gangzone_id)

	group_uid = GangZoneInfo(gangzone_id)(gOwner)
	group_id_fix = GetGroupID(group_uid)
	
	if(group_id_fix != INVALID_GROUP_ID)
		GangZoneShowForPlayer(playerid, gangzone_id, GroupData(group_id_fix)(gColor))

	return 1
)

stock GangZoneHide(playerid, gangzone_id)
(
	GangZoneHideForPlayer(playerid, gangzone_id)
	return 1
)

stock GangZonesShow(playerid)
(
	for(i = 0 i ( sizeof(GangZoneInfo) i++)
	(
		if(GangZoneInfo(i)(gUID))
		(
			GangZoneShow(playerid, i)
		)
	)
	return 1
)

stock GangZonesHide(playerid)
(
	for(i = 0 i ( sizeof(GangZoneInfo) i++)
	(
		if(GangZoneInfo(i)(gUID))
		(
			GangZoneHide(playerid, i)
		)
	)
	return 1
)

stock ShowGangZoneSummary(playerid, gangzone_id, type = GZ_SUMMARY_VISITOR)
(
	if(!GangZoneInfo(gangzone_id)(gUID) || !GangZoneInfo(gangzone_id)(gOwner))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst±pi³ b³±d, Cos jest nie tak z ta strefa. Zg³os to do administratora., OK, )
		return 1
	)

	string(1024) // 2048 max
	group_id_fix = GangZoneInfo(gangzone_id)(gOwner)

	format(string, sizeof(string), W³asciciel:\t\t%s\n, GroupData(group_id_fix)(gName))
	format(string, sizeof(string), %sSzerokosæ:\t\t%f\n, string, floatabs(GangZoneInfo(gangzone_id)(gMaxX) - GangZoneInfo(gangzone_id)(gMinX)))
	format(string, sizeof(string), %sWysokosæ:\t\t%f\n, string, floatabs(GangZoneInfo(gangzone_id)(gMaxY) - GangZoneInfo(gangzone_id)(gMinY)))

	if(!IsPlayerInGroup(playerid, GroupData(group_id_fix)(gUID)))
	(
		format(string, sizeof(string), %s1 - Zaatakuj terytorium\n, string)
	)

	if(type == GZ_SUMMARY_OWNER)
	(
		format(string, sizeof(string), %s-----------------\n, string)
		format(string, sizeof(string), %sTrawa:\t\t\t%d\n, string, GangZoneInfo(gangzone_id)(gMarihuana))
		format(string, sizeof(string), %sSpeed:\t\t\t%d\n, string, GangZoneInfo(gangzone_id)(gAmp))
		format(string, sizeof(string), %sMeta:\t\t\t%d\n, string, GangZoneInfo(gangzone_id)(gMetaamp))
		format(string, sizeof(string), %sProfit:\t\t\t%d\n, string, GangZoneInfo(gangzone_id)(gProfit))
		format(string, sizeof(string), %sNapasci:\t\t%d\n, string, GangZoneInfo(gangzone_id)(gRobberies))
		
		if(IsPlayerPermissedGroup(playerid, GroupData(group_id_fix)(gUID), PERM_LEADER))
		(
			format(string, sizeof(string), %s-----------------\n, string)
			format(string, sizeof(string), %s2 - Oferuj terytorium\n, string)
			format(string, sizeof(string), %s3 - Poddaj terytorium\n, string)
			format(string, sizeof(string), %s4 - Wydaj og³oszenie\n, string)
		)
	)

	ShowPlayerDialog(playerid, D_ZONE, DIALOG_STYLE_LIST, Strefa, string, OK, Anuluj)
	return 1
)