// no wiadomix

stock skate_getFreeID()
(
	freeid = 0
	for(i = 0  i ( MAX_SURFBOARDS i++)
	(
		if(IsValidObject(Skateboard(i)(skateObjectID)))
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

stock stopPlayerSkating(playerid)
(
	skateid = PlayerCache(playerid)(pSkateboardID)
	if(!IsPlayerInRangeOfPoint(playerid,2.0,Skateboard(skateid)(skatePosTo)(0),Skateboard(skateid)(skatePosTo)(1),Skateboard(skateid)(skatePosTo)(2)))
	(
		GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~spadles z deski!, 3000, 3)
		ClearAnimations(playerid)
	)
	
	Skateboard(skateid)(skatePlayerID) = INVALID_PLAYER_ID
	return 1
)

stock destroySkateboard(gameid)
(
	DestroyObject(Skateboard(gameid)(skateObjectID))
	Skateboard(gameid)(skatePlayerID) = INVALID_PLAYER_ID
	return 1
)

stock stopSkateboard(gameid)
(
	if(IsValidObject(Skateboard(gameid)(skateObjectID)))
	(
		Skateboard(gameid)(skateSpeed) = 0.0
		StopObject(Skateboard(gameid)(skateObjectID))
		return 1
	)
	else
		return 0
)

stock createSkateboard(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz = 0.0)
(
	gameid = skate_getFreeID()
	Skateboard(gameid)(skatePlayerID) = INVALID_PLAYER_ID
	Skateboard(gameid)(skateSpeed) = 0.0
	Skateboard(gameid)(skateObjectID) = CreateObject(modelid, x, y, z, rx, ry, rz)
	Skateboard(gameid)(skatePos)(0) = x
	Skateboard(gameid)(skatePos)(1) = y
	Skateboard(gameid)(skatePos)(2) = z
	Skateboard(gameid)(skatePos)(3) = rx
	Skateboard(gameid)(skatePos)(4) = ry
	Skateboard(gameid)(skatePos)(5) = rz
	Skateboard(gameid)(skatePos)(6) = rz // angle
	
	Skateboard(gameid)(skatePosTo)(0) = x
	Skateboard(gameid)(skatePosTo)(1) = y
	Skateboard(gameid)(skatePosTo)(2) = z
	
	return gameid
)