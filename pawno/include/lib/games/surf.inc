stock surf_LoadSurfboards()
(
	//dodaj kilka surfboardów
	surf_CreateBoard(2404,331.2454,-1905.8453,0.0911,270.0,0,180.0)
	surf_CreateBoard(2404,296.2121,-1903.0786,0.0911,270.0,0,180.0)
	return 1
)

stock GetXYInFrontOfPlayerOnSB(playerid, &Float:x, &Float:y, Float:distance)
(
	new
			Float:angle
	GetPlayerPos(playerid, x, y, angle)
	GetPlayerFacingAngle(playerid, angle)
	x += (distance * floatsin(-angle + 270.0, degrees))
	y += (distance * floatcos(-angle + 270.0, degrees))
)

stock surf_DestroySurfboard(surfid)
(
	DestroyObject(Surfboard(surfid)(surfObjectID))
	Surfboard(surfid)(surfPlayerID) = INVALID_PLAYER_ID
	return 1
)

stock surf_GetFreeID()
(
	freeid = 0
	for(i = 0  i ( MAX_SURFBOARDS i++)
	(
		if(IsValidObject(Surfboard(i)(surfObjectID)))
		(
			continue
		)
		else
		(
			freeid = i
			break
		)
	)
	
	return freeid
)

stock surf_CreateBoard(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz = 0.0)
(
	gameid = surf_GetFreeID()
	Surfboard(gameid)(surfPlayerID) = INVALID_PLAYER_ID
	Surfboard(gameid)(surfSpeed) = 0.0
	Surfboard(gameid)(surfObjectID) = CreateObject(modelid, x, y, z, rx, ry, rz)
	Surfboard(gameid)(surfPos)(0) = x
	Surfboard(gameid)(surfPos)(1) = y
	Surfboard(gameid)(surfPos)(2) = z
	Surfboard(gameid)(surfPos)(3) = rx
	Surfboard(gameid)(surfPos)(4) = ry
	Surfboard(gameid)(surfPos)(5) = rz
	Surfboard(gameid)(surfPos)(6) = rz // angle
	
	Surfboard(gameid)(surfPosTo)(0) = x
	Surfboard(gameid)(surfPosTo)(1) = y
	Surfboard(gameid)(surfPosTo)(2) = z
	
	return gameid
)

stock surf_RespawnBoard(gameid)
(
	if(IsValidObject(Surfboard(gameid)(surfObjectID)))
	(
		SetObjectPos(Surfboard(gameid)(surfObjectID),
		Surfboard(gameid)(surfPos)(0), //x
		Surfboard(gameid)(surfPos)(1), 	//y
		Surfboard(gameid)(surfPos)(2))		//z
		
		SetObjectRot(Surfboard(gameid)(surfObjectID),
		Surfboard(gameid)(surfPos)(3),	//rx
		Surfboard(gameid)(surfPos)(4),	//ry
		Surfboard(gameid)(surfPos)(5))		//rz
		
		Surfboard(gameid)(surfPlayerID) = INVALID_PLAYER_ID
		Surfboard(gameid)(surfSpeed) = 0.0
		return 1
	)
	else
	(
		return 0
	)
)

stock surf_StopSurfing(playerid)
(
	surfid = PlayerCache(playerid)(pSurfID)
	if(!IsPlayerInRangeOfPoint(playerid,2.0,Surfboard(surfid)(surfPosTo)(0),Surfboard(surfid)(surfPosTo)(1),Surfboard(surfid)(surfPosTo)(2)))
	(
		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~spadles z deski!, 3000, 3)
		ClearAnimations(playerid)
	)
	
	Surfboard(surfid)(surfPlayerID) = INVALID_PLAYER_ID
	
	return 1
)

stock surf_StopBoard(gameid)
(
	if(IsValidObject(Surfboard(gameid)(surfObjectID)))
	(
		/*playerid = Surfboard(gameid)(surfPlayerID)
		
		if(playerid != INVALID_PLAYER_ID)
		(
			Float:Pos(3)
			GetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))
			//SetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))
			SetObjectPos(Surfboard(gameid)(surfObjectID),Pos(0),Pos(1)+1,0.9)
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~spadles z deski!, 3000, 3)
		)*/
		
		//Surfboard(gameid)(surfPlayerID) = INVALID_PLAYER_ID
		Surfboard(gameid)(surfSpeed) = 0.0
		StopObject(Surfboard(gameid)(surfObjectID))
		return true
	)
	else
	(
		return false
	)
)

/*CMD:skate(playerid, params())
(
	if(PlayerCache(playerid)(pSkateboardID) != -1 && Skateboard(PlayerCache(playerid)(pSkateboardID))(skatePlayerID) == playerid)
	(
		GuiMsg(playerid,Jesteœ ju¿ na jakieœ desce.,1)
		return 1
	)
	else
	(
		skateid = -1
		for(i = 0  i ( MAX_SURFBOARDS i++)
		(
			if(GetPlayerVirtualWorld(playerid) == 0)
			(
				object = Skateboard(i)(skateObjectID)
				Float:Pos(3)
				GetObjectPos(object, Pos(0), Pos(1), Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid, 2.0, Pos(0), Pos(1), Pos(2)))
				(
					if(Skateboard(i)(skatePlayerID) == INVALID_PLAYER_ID)
					(
						skateid = i
						break
					)
				)
			)
			else
			(
				GuiMsg(playerid,Nie mo¿esz jeŸdziæ wewn¹trz budynku.,1)
				return 1
			)
		)
		
		if(skateid == INVALID_SURFBOARD_ID)
		(
			GuiMsg(playerid,Nie jesteœ w pobli¿u ¿adnej z desek.,1)
			return 1
		)
		
		Skateboard(skateid)(skatePlayerID) = playerid
		SetPlayerFacingAngle(playerid, Skateboard(skateid)(skatePos)(5) + 0.0)
		object = Skateboard(skateid)(skateObjectID), Float:Pos(3)
		
		GetObjectPos(object,Pos(0),Pos(1),Pos(2))
		//MapAndreas_FindZ_For2DCoord(Pos(0), Pos(1), Pos(2))
		SetPlayerPos(playerid,Pos(0),Pos(1),Pos(2)+1.0)
		ApplyAnimation(playerid, BSKTBALL, BBALL_def_loop, 4.0, 1, 0, 0, 0, 0)
	)
	return 1
)*/

CMD:surfuj(playerid,params())
(
	if(PlayerCache(playerid)(pSurfID) != INVALID_SURFBOARD_ID && Surfboard(PlayerCache(playerid)(pSurfID))(surfPlayerID) == playerid)
	(
		GuiMsg(playerid,Jesteœ ju¿ na jakieœ desce.,1)
		return 1
	)
	else
	(
		surfid = INVALID_SURFBOARD_ID
		for(i = 0  i ( MAX_SURFBOARDS i++)
		(
			// Ten drugi to AquaPark
			if(GetPlayerVirtualWorld(playerid) == 0 || GetPlayerVirtualWorld(playerid) == 3722)
			(
				object = Surfboard(i)(surfObjectID)
				Float:Pos(3)
				GetObjectPos(object,Pos(0),Pos(1),Pos(2))
				
				if(IsPlayerInRangeOfPoint(playerid,2.0,Pos(0),Pos(1),Pos(2)))
				(
					if(Surfboard(i)(surfPlayerID) == INVALID_PLAYER_ID)
					(
						surfid = i
						break
					)
				)
			)
			else
			(
				GuiMsg(playerid,Nie mo¿esz surfowaæ wewn¹trz budynku.,1)
				return 1
			)
		)
		
		if(surfid == INVALID_SURFBOARD_ID)
		(
			GuiMsg(playerid,Nie jesteœ w pobli¿u ¿adnej z desek.,1)
			return 1
		)
		
		Surfboard(surfid)(surfPlayerID) = playerid
		SetPlayerFacingAngle(playerid, Surfboard(surfid)(surfPos)(5) + 270.0)
		object = Surfboard(surfid)(surfObjectID), Float:Pos(3)
		GetObjectPos(object,Pos(0),Pos(1),Pos(2))
		SetPlayerPos(playerid,Pos(0),Pos(1),Pos(2)+1.0)
		ApplyAnimation(playerid, BSKTBALL, BBALL_def_loop, 4.0, 1, 0, 0, 0, 0)
		
	)
	
	return 1
)