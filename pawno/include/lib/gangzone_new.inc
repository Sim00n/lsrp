#define COLOR_ZONE_NEUTRAL 0xA6A6A6AA
#define ZONE_TICKS_NEUTRAL	 380 //minimalny próg przejêcia neutralnej strefy
#define ZONE_MAX_NEUTRALS 	3		//maksymalna liczba neutralnych w tygodniu

DenyAttack(MAX_GROUPS)
DebugZones = 0

/*
	callbacks
*/

stock OnPlayerEnterZone(playerid, zoneid)
(
	PlayerCache(playerid)(pCurrentZone) = zoneid
	
	if(DebugZones)
	(
		message(128)
		format(message, sizeof(message), (debug) wszedles do strefy (SID: %i) (UID: %i), PlayerCache(playerid)(pCurrentZone), ZoneInfo(PlayerCache(playerid)(pCurrentZone))(zUID))
		SendClientMessage(playerid, 0xFFFFFFAA, message)
	)
	
	if(PlayerCache(playerid)(pLastZone) != zoneid)
	(
		// czyœæ tick jeœli zmieni³ strefê
		PlayerCache(playerid)(pZoneTicks) = 0
	)
	
	
	
	return 1
)

stock OnPlayerExitZone(playerid, zoneid)
(
	PlayerCache(playerid)(pCurrentZone) = -1
	PlayerCache(playerid)(pLastZone) = zoneid
	
	if(DebugZones)
	(
		message(128)
		format(message, sizeof(message), (debug) wyszedles ze strefy)
		SendClientMessage(playerid, 0xFFFFFFAA, message)
	)
	
	
	
	return 1
)

/*
	przejmowanie i te sprawy
*/

stock GetZoneTicks(zone_uid, group_uid)
(
	ticks = 0
	mysql_query_format(SELECT * FROM hrp_zoneticks WHERE tick_zone = %d AND tick_group = %d, zone_uid, group_uid)
	mysql_store_result()
	ticks = mysql_num_rows()
	mysql_free_result()
	return ticks
)

stock AddZoneTick(playerid)
(
	buffer(256)
	PlayerCache(playerid)(pZoneTicks) = 0
	
	group_id_fix, gSlot
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerGroup(playerid)(slot)(gUID))
		(
			group_id_fix = PlayerGroup(playerid)(slot)(gID)
			if(GroupData(group_id_fix)(gType) == GROUP_CRIMINAL)
			(
				gSlot = slot
				break
			)
		)
	)
	
	format(buffer, sizeof(buffer), INSERT INTO hrp_zoneticks VALUES(NULL, %d, %d, %d), ZoneInfo(GetPlayerZoneID(playerid))(zUID), PlayerGroup(playerid)(gSlot)(gUID), 1)
	mysql_query(buffer)
	
	return 1
)

stock ZoneCalculateTicks()
(
	for(i = 0  i ( MAX_ZONES i++)
	(
		if(ZoneInfo(i)(zUID) ) 0)
		(
			buffer(256)
			
			leader = -1, maxscore = 0
			for(IDGroup = 0 IDGroup ( MAX_GROUPS IDGroup++)
			(
				if(GroupData(IDGroup)(gType) == GROUP_CRIMINAL)
				(
					// moze do wywalenia, zobaczymy
					if(!IsGroupCanTakeArea(GroupData(IDGroup)(gUID)))
						continue
					
					format(buffer, sizeof(buffer), SELECT * FROM hrp_zoneticks WHERE tick_zone = %d AND tick_group = %d, ZoneInfo(i)(zUID), GroupData(IDGroup)(gUID))
					mysql_query(buffer)
					mysql_store_result()
					if(maxscore == 0 || mysql_num_rows() ) maxscore)
					(
						maxscore = mysql_num_rows()
						leader = IDGroup
					)
					mysql_free_result()
				)
			)
			
			printf(leader: %i, score: %i, leader, maxscore)
			if(leader == -1)
				continue
			
			type = random(3) + 1
			
			if(maxscore )= ZONE_TICKS_NEUTRAL)
			(
				printf((STEP 2) leader: %i, score: %i, leader, maxscore)
				if(!IsZoneTakeAgree(GroupData(leader)(gUID), i))
					continue
					
				AddGroupLimit(GroupData(leader)(gUID))
				
				ZoneInfo(i)(zOwner) = GroupData(leader)(gUID)
				ZoneInfo(i)(zType) = type
			)
		)
	)
	
	
	ReloadZones()
	mysql_query(TRUNCATE hrp_zoneticks)
	return 1
)


/*
	loadfunc
*/

stock ZoneClearAttacks()
(
	for(i = 0  i ( MAX_GROUPS i++)
	(
		DenyAttack(i) = 0
	)
	
	return 1
)

stock IsGroupDenyAttack(group_uid)
(
	// zwraca TRUE jak grupa juz nie moze dzis atakowac lub FALSE jak moze
	groupid = GetGroupID(group_uid)
	if(DenyAttack(groupid))
		return true
	else
		return false
)

stock LoadZones()
(
	buffer(256)
	format(buffer, sizeof(buffer), SELECT * FROM hrp_zones)
	
	mysql_query(buffer)
	mysql_store_result()
	gameid = 0
	while(mysql_fetch_row(buffer,|))
	(
		sscanf(buffer, p(|)dffffddd,
		ZoneInfo(gameid)(zUID),
		ZoneInfo(gameid)(zMinX),
		ZoneInfo(gameid)(zMinY),
		ZoneInfo(gameid)(zMaxX),
		ZoneInfo(gameid)(zMaxY),
		ZoneInfo(gameid)(zOwner),
		ZoneInfo(gameid)(zType),
		ZoneInfo(gameid)(zPackage))
		
		ZoneInfo(gameid)(zSID) = GangZoneCreate(ZoneInfo(gameid)(zMinX), ZoneInfo(gameid)(zMinY), ZoneInfo(gameid)(zMaxX), ZoneInfo(gameid)(zMaxY))
		
		gameid++
	)
	printf((load) zaladowano %i stref, gameid)
	mysql_free_result()
	return 1
)

stock UnloadZones()
(
	for(gameid = 0  gameid ( MAX_ZONES gameid++)
	(
		ZoneInfo(gameid)(zUID) = 0
		ZoneInfo(gameid)(zMinX) = 0
		ZoneInfo(gameid)(zMinY) = 0
		ZoneInfo(gameid)(zMaxX) = 0
		ZoneInfo(gameid)(zMaxY) = 0 
		ZoneInfo(gameid)(zOwner) = 0 
		ZoneInfo(gameid)(zType) = 0 
		
		GangZoneHideForAll(ZoneInfo(gameid)(zSID))
		GangZoneDestroy(ZoneInfo(gameid)(zSID))
	)
	
	for(i = 0  i ( 100 i++)
	(
		// tak zapobiegawczo
		GangZoneDestroy(i)
	)
	
	printf((unload) wyladowano wszystkie strefy)
	
	return 1
)

stock ReloadZones()
(
	SaveZones()
	UnloadZones()
	LoadZones()
	
	for(i = 0  i ( MAX_PLAYERS i++)
	(
		if(IsPlayerInGroupType(i, GROUP_CRIMINAL))
		(
			ShowPlayerAllZones(i)
		)
	)
	
	printf((reload) przeladowalem strefy)
	return 1
)

stock SaveZones()
(
	buffer(256)
	for(i = 0  i ( MAX_ZONES i++)
	(
		if(ZoneInfo(i)(zUID) ) 0)
		(	
			format(buffer, sizeof(buffer), UPDATE hrp_zones SET zone_owner = %d, zone_type = %d, zone_package = %d WHERE zone_uid = %d, ZoneInfo(i)(zOwner), ZoneInfo(i)(zType), ZoneInfo(i)(zPackage), ZoneInfo(i)(zUID))
			mysql_query(buffer)
		)
	)
	
	return 1
)

/*
	other func
*/

stock IsZoneTakeAgree(group_uid, zoneid)
(
	for(i = 0  i ( MAX_ZONES i++)
	(
		if(zoneid == i)
			continue
			
		if(ZoneInfo(i)(zOwner) != group_uid)
			continue
					
		if(ZoneInfo(i)(zUID) ) 0)
		(
			if(IsPointInRangeOfPoint(ZoneInfo(zoneid)(zMaxX), ZoneInfo(zoneid)(zMaxY), 10.0, ZoneInfo(i)(zMaxX), ZoneInfo(i)(zMaxY), 10.0, 100.0) (= 100)
			(
				return true
			)
			
			if(IsPointInRangeOfPoint(ZoneInfo(zoneid)(zMaxX), ZoneInfo(zoneid)(zMaxY), 10.0, ZoneInfo(i)(zMinX), ZoneInfo(i)(zMinY), 10.0, 100.0) (= 100)
			(
				return true
			)
			
			if(IsPointInRangeOfPoint(ZoneInfo(zoneid)(zMinX), ZoneInfo(zoneid)(zMinY), 10.0, ZoneInfo(i)(zMaxX), ZoneInfo(i)(zMaxY), 10.0, 100.0) (= 100)
			(
				return true
			)
			
			if(IsPointInRangeOfPoint(ZoneInfo(zoneid)(zMinX), ZoneInfo(zoneid)(zMinY), 10.0, ZoneInfo(i)(zMinX), ZoneInfo(i)(zMinY), 10.0, 100.0) (= 100)
			(
				return true
			)
		)
	)
	
	return false
)

stock GetZoneInfo(playerid, zoneid)
(
	zInfo(256)
	format(zInfo, sizeof(zInfo), ID strefy:\t\t%i, zoneid)
	format(zInfo, sizeof(zInfo), %s\nUID strefy:\t\t%i, zInfo, ZoneInfo(zoneid)(zUID))
	
	if(!ZoneInfo(zoneid)(zOwner))
	(
		format(zInfo, sizeof(zInfo), %s\nW³aœciciel strefy:\t\t brak, zInfo)
	)
	else
	(
		format(zInfo, sizeof(zInfo), %s\nW³aœciciel strefy:\t\t%i, zInfo, ZoneInfo(zoneid)(zOwner))
	)
	
	if(ZoneInfo(zoneid)(zType) == ZONE_TYPE_NONE)
	(
		format(zInfo, sizeof(zInfo), %s\nTyp strefy:\t\t neutralna, zInfo)
	)
	if(ZoneInfo(zoneid)(zType) == ZONE_TYPE_MONEY)
	(
		format(zInfo, sizeof(zInfo), %s\nTyp strefy:\t\t kasa, zInfo)
	)
	if(ZoneInfo(zoneid)(zType) == ZONE_TYPE_GUN)
	(
		format(zInfo, sizeof(zInfo), %s\nTyp strefy:\t\t broñ, zInfo)
	)
	if(ZoneInfo(zoneid)(zType) == ZONE_TYPE_MAIN)
	(
		format(zInfo, sizeof(zInfo), %s\nTyp strefy:\t\t serce gangu, zInfo)
	)
	if(ZoneInfo(zoneid)(zType) == ZONE_TYPE_DRUG)
	(
		format(zInfo, sizeof(zInfo), %s\nTyp strefy:\t\t narkotyki, zInfo)
	)
	
	if(ZoneInfo(zoneid)(zPackage))
	(
		format(zInfo, sizeof(zInfo), %s\nBonus:\t\t nie odebrany, zInfo)
	)
	else
	(
		format(zInfo, sizeof(zInfo), %s\nBonus:\t\t brak, zInfo)
	)
	
	if(ZoneInfo(zoneid)(zBlocked))
	(
		format(zInfo, sizeof(zInfo), %s\nAtak:\t\t nie mo¿liwy, zInfo)
	)
	else
	(
		format(zInfo, sizeof(zInfo), %s\nAtak:\t\t mo¿liwy, zInfo)
	)
	
	
	if(!strlen(zInfo))
	(
		return GuiMsg(playerid, Wyst¹pi³ b³¹d podczas ³adowania informacji o strefie., 1)
	)
	else
	(
		return ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Informacje o strefie, zInfo, OK, )
	)
)

stock GetPlayerZoneID(playerid)
(
	zoneid = INVALID_ZONE_ID
	for(i = 0  i ( MAX_ZONES i++)
	(
		if(ZoneInfo(i)(zUID) ) 0)
		(
			if(IsPlayerInArea(playerid, ZoneInfo(i)(zMaxX), ZoneInfo(i)(zMinX), ZoneInfo(i)(zMaxY), ZoneInfo(i)(zMinY)))
			//if(IsPlayerInSquare(playerid, ZoneInfo(i)(zMinX), ZoneInfo(i)(zMinY), ZoneInfo(i)(zMaxX), ZoneInfo(i)(zMaxY)))
			(
				zoneid = i
				break
			)
		)
	)
	
	return zoneid
)

stock GetPointZoneID(Float:zX, Float:zY)
(
	zoneid = INVALID_ZONE_ID
	for(i = 0  i ( MAX_ZONES i++)
	(
		if(ZoneInfo(i)(zUID) ) 0)
		(
			if(zX ( ZoneInfo(i)(zMaxX) && zX ) ZoneInfo(i)(zMinX) && zY ( ZoneInfo(i)(zMaxY) && zY ) ZoneInfo(i)(zMinY))
			(
				zoneid = i
				break
			)
		)
	)
	
	return zoneid
)

stock ShowPlayerAllZones(playerid)
(
	for(i = 0  i ( MAX_ZONES i++)
	(
		if(ZoneInfo(i)(zUID) ) 0)
		(
			if(ZoneInfo(i)(zOwner) ) 0)
			(
				GangZoneShowForPlayer(playerid, i, ColorFade(GroupData(GetGroupID(ZoneInfo(i)(zOwner)))(gColor), 200, 200 ))
			)
			else
			(
				GangZoneShowForPlayer(playerid, i, COLOR_ZONE_NEUTRAL)
			)
		)
	)
	
	return 1
)

stock HidePlayerAllZones(playerid)
(
	for(i = 0  i ( MAX_ZONES i++)
	(
		if(ZoneInfo(i)(zUID) ) 0)
		(
			if(ZoneInfo(i)(zOwner) ) 0)
			(
				GangZoneHideForPlayer(playerid, i)
			)
			else
			(
				GangZoneHideForPlayer(playerid, i)
			)
		)
	)
	return 1
)

stock GetZoneMembersOnline(zoneid)
(
	members = 0, owner = ZoneInfo(zoneid)(zOwner)
	for(i = 0  i ( MAX_PLAYERS i++)
	(
		if(IsPlayerInGroup(i, owner))
		(
			members++
		)
	)
	return members
)

stock IsGroupCanTakeArea(group_uid)
(
	buffer(256)
	format(buffer, sizeof(buffer), SELECT * FROM hrp_zone_limits WHERE limit_group = %d, group_uid)
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() )= ZONE_MAX_NEUTRALS)
	(
		mysql_free_result()
		return false
	)
	else
	(
		mysql_free_result()
		return true
	)
)

stock AddGroupLimit(group_uid)
(
	buffer(256)
	format(buffer, sizeof(buffer), INSERT INTO hrp_zone_limits VALUES(NULL, %d, NULL), group_uid)
	if(mysql_query(buffer))
	(
		return 1
	)
	else
	(
		return 0
	)
)

/*
	komendy
*/

CMD:ztest(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Brak odpowiednich uprawnieñ., 1)
		return 1
	)
	
	buffer(256)
	PlayerCache(playerid)(pZoneTicks) = 0
	
	group_id_fix, gSlot
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		if(PlayerGroup(playerid)(slot)(gUID))
		(
			group_id_fix = PlayerGroup(playerid)(slot)(gID)
			if(GroupData(group_id_fix)(gType) == GROUP_CRIMINAL)
			(
				gSlot = slot
				break
			)
		)
	)
	
	format(buffer, sizeof(buffer), INSERT INTO hrp_zoneticks VALUES(NULL, %d, %d, %d), ZoneInfo(GetPlayerZoneID(playerid))(zUID), PlayerGroup(playerid)(gSlot)(gUID), 1)
	
	for(i = 0  i ( 400 i++)
	(
		mysql_query(buffer)
	)
	
	return 1
)

CMD:azone(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Brak odpowiednich uprawnieñ., 1)
		return 1
	)
	
	type(32), varchar(64)
	if(sscanf(params, s(32)S()(64), type, varchar))
	(
		hrp_Tip(playerid, /azone (przeladuj | przypisz | lista | sampid | goto | zneutralizuj | pokaz | ukryj))
		return 1
	)
	
	if(!strcmp(type, ukryj, true))
	(
		HidePlayerAllZones(playerid)
		GuiMsg(playerid, Ukryles strefy., 1)
		return 1
	)

	if(!strcmp(type, pokaz, true))
	(
		ShowPlayerAllZones(playerid)
		GuiMsg(playerid, Pokazales strefy., 1)
		return 1
	)

	if(!strcmp(type, zneutralizuj, true))
	(
		zoneid
		if(sscanf(varchar, d, zoneid))
		(
			hrp_Tip(playerid, /azone zneutralizuj (ID strefy))
			return 1
		)
		
		if(ZoneInfo(zoneid)(zUID) (= 0)
		(
			GuiMsg(playerid, Nie znaleziono takiej strefy., 1)
			return 1
		)
		
		ZoneInfo(zoneid)(zOwner) = 0
		ZoneInfo(zoneid)(zType) = 0
		
		GuiMsg(playerid, Zneutralizowa³eœ wskazan¹ strefê., 1)
		
		ReloadZones() // na koniec
	)
	
	if(!strcmp(type, przypisz, true))
	(
		zoneid, group, zoType
		if(sscanf(varchar, ddd, zoneid, group, zoType))
		(
			hrp_Tip(playerid, /azone przypisz (ID strefy) (UID grupy) (Typ strefy))
			return 1
		)
		
		if(ZoneInfo(zoneid)(zUID) (= 0)
		(
			GuiMsg(playerid, Nie znaleziono takiej strefy., 1)
			return 1
		)
		
		if(GetGroupID(group) == INVALID_GROUP_ID)
		(
			GuiMsg(playerid, Nie znaleziono takiej grupy., 1)
			return 1
		)
		
		if(zoType ( 0 || zoType ) 4)
		(
			GuiMsg(playerid, Podano z³y typ grupy, dopuszczalne (1-4), 1)
			return 1
		)
		
		if(GroupData(GetGroupID(group))(gType) != GROUP_CRIMINAL)
		(
			GuiMsg(playerid, Strefê mo¿esz podpisaæ tylko pod grupê przestêpcz¹., 1)
			return 1
		)
		
		ZoneInfo(zoneid)(zOwner) = group
		ZoneInfo(zoneid)(zType) = zoType
		
		message(256)
		format(message, sizeof(message), Przypisano strefê (ID: %i) (UID: %i) pod grupê \n %s, 
		zoneid, 
		ZoneInfo(zoneid)(zUID),
		GroupData(GetGroupID(group))(gName))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, message, OK, )
		
		ReloadZones() // na koniec
		
	)
	
	if(!strcmp(type, przeladuj, true))
	(
		GuiMsg(playerid, Prze³adowano wszystkie strefy., 1)
		
		/*
			inne prze³adowanie bo poprzednie siê sypa³o tak konkretnie
			zwiêkszamy MAX_ZONES, bo coœ siê spieroli³o
		*/
		
		for(gameid = 0  gameid ( MAX_ZONES gameid++)
		(
			ZoneInfo(gameid)(zUID) = 0
			ZoneInfo(gameid)(zMinX) = 0
			ZoneInfo(gameid)(zMinY) = 0
			ZoneInfo(gameid)(zMaxX) = 0
			ZoneInfo(gameid)(zMaxY) = 0 
			ZoneInfo(gameid)(zOwner) = 0 
			ZoneInfo(gameid)(zType) = 0 
			
			GangZoneHideForAll(ZoneInfo(gameid)(zSID))
			GangZoneDestroy(ZoneInfo(gameid)(zSID))
		)
		
		for(i = 0  i ( 100 i++)
		(
			// tak zapobiegawczo
			GangZoneDestroy(i)
		)
		
		buffer(256)
		format(buffer, sizeof(buffer), SELECT * FROM hrp_zones)
		
		mysql_query(buffer)
		mysql_store_result()
		gameid = 0
		while(mysql_fetch_row(buffer,|))
		(
			sscanf(buffer, p(|)dffffddd,
			ZoneInfo(gameid)(zUID),
			ZoneInfo(gameid)(zMinX),
			ZoneInfo(gameid)(zMinY),
			ZoneInfo(gameid)(zMaxX),
			ZoneInfo(gameid)(zMaxY),
			ZoneInfo(gameid)(zOwner),
			ZoneInfo(gameid)(zType),
			ZoneInfo(gameid)(zPackage))
			
			ZoneInfo(gameid)(zSID) = GangZoneCreate(ZoneInfo(gameid)(zMinX), ZoneInfo(gameid)(zMinY), ZoneInfo(gameid)(zMaxX), ZoneInfo(gameid)(zMaxY))
			
			gameid++
		)
		printf((load) zaladowano %i stref, gameid)
		mysql_free_result()
		
		for(i = 0  i ( MAX_PLAYERS i++)
		(
			if(IsPlayerInGroupType(i, GROUP_CRIMINAL))
			(
				ShowPlayerAllZones(i)
			)
		)
		
	)
	
	if(!strcmp(type, sampid, true))
	(
		if(GetPlayerZoneID(playerid) != INVALID_ZONE_ID)
		(
			message(128)
			format(message, sizeof(message), Aktualna strefa to (SID: %i), GetPlayerZoneID(playerid))
			
			hrp_Tip(playerid, message)
		)
		else
		(
			hrp_Tip(playerid, nie jesteœ w ¿adnej strefie)
		)
	)
	
	if(!strcmp(type, goto, true))
	(
		zoneid
		if(sscanf(varchar, d, zoneid))
		(
			hrp_Tip(playerid, /azone goto (ID strefy))
			return 1
		)
		
		if(ZoneInfo(zoneid)(zUID) (= 0)
		(
			GuiMsg(playerid, Nie ma takiej strefy., 1)
			return 1
		)
		
		SetPlayerPosFindZ(playerid, ZoneInfo(zoneid)(zMaxX), ZoneInfo(zoneid)(zMaxY), 0.0)
	)
	
	if(!strcmp(type, debug, true))
	(
		PlayerCache(playerid)(pCurrentZone)  = -1
		GuiMsg(playerid, Wyczyœci³eœ aktualn¹ strefê.,1)
	)
	
	if(!strcmp(type, info, true))
	(
		sampid
		if(sscanf(varchar, d, sampid))
		(
			hrp_Tip(playerid, /azone info (ID strefy))
			return 1
		)
		
		GetZoneInfo(playerid, sampid)
	)
	
	if(!strcmp(type, lista, true))
	(
		glist(512)
		count = 0
		for(i = 0  i ( MAX_ZONES i++)
		(
			if(ZoneInfo(i)(zUID) ) 0)
			(
				count++
				format(glist, sizeof(glist), %s\n%i. Strefa (ID: %i) (UID: %i), glist, count, i, ZoneInfo(i)(zUID))
			)
		)
		
		if(!strlen(glist))
		(
			GuiMsg(playerid, Nie znaleziono ¿adnej strefy., 1)
			return 1
		)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Lista stref, glist, OK, )
	)
	
	return 1
)