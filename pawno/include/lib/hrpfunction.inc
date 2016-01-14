stock hrp_Tip(playerid, givenString())
(
	string(256)
	format(string, sizeof(string), U¿ycie: %s, givenString)

	SendClientMessage(playerid, COLOR_GREY, string)
	return 1
)

stock hrp_SetPlayerHealth(playerid, Float:health)
(
	PlayerCache(playerid)(pHealth) = health
	SetPlayerHealth(playerid, health)
	return 1
)

stock hrp_SetPlayerArmour(playerid, Float:armour)
(
	PlayerCache(playerid)(pArmour) = armour
	SetPlayerArmour(playerid, armour)
	return 1
)

stock hrp_SetPlayerSkin(playerid, skinid)
(
	PlayerCache(playerid)(pSkin) = skinid
	SetPlayerSkin(playerid, skinid)
	return 1
)

stock hrp_GivePlayerMoney(playerid, money)
(
	PlayerCache(playerid)(pCash) += money
	SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
	GivePlayerMoney(playerid, money)
	return 1
)

stock hrp_TogglePlayerControllable(playerid, toggle)
(
	if(toggle == 1)
	(
		PlayerCache(playerid)(pFreeze) = 0
	)
	else
	(
		PlayerCache(playerid)(pFreeze) = 1
	)
	TogglePlayerControllable(playerid, toggle)
	GetPlayerPos(playerid, PlayerCache(playerid)(pFreezePosX), PlayerCache(playerid)(pFreezePosY), PlayerCache(playerid)(pFreezePosZ))
	return 1
)

stock hrp_SetPlayerPos(playerid, Float:PosX, Float:PosY, Float:PosZ)
(
	if(SetPlayerPos(playerid, PosX, PosY, PosZ))
	(
		PlayerCache(playerid)(pGotAirBrkPos) = 0

		PlayerCache(playerid)(pCheatPosX) = PosX
		PlayerCache(playerid)(pCheatPosY) = PosY
		PlayerCache(playerid)(pCheatPosZ) = PosZ

		SetPlayerPos(playerid, PosX, PosY, PosZ)
	)
	return 1
)

stock hrp_SetPlayerPosFindZ(playerid, Float:PosX, Float:PosY, Float:PosZ)
(
	if(SetPlayerPosFindZ(playerid, PosX, PosY, PosZ))
	(
		PlayerCache(playerid)(pGotAirBrkPos) = 0

		PlayerCache(playerid)(pCheatPosX) = PosX
		PlayerCache(playerid)(pCheatPosY) = PosY
		PlayerCache(playerid)(pCheatPosZ) = PosZ

		SetPlayerPosFindZ(playerid, PosX, PosY, 1000)
	)
	return 1
)

stock hrp_AddVehicleComponent(vehicleid, componentid)
(
	slot = GetVehicleComponentType(componentid)
	if(slot != -1)
	(
		AddVehicleComponent(vehicleid, componentid)
		CarInfo(vehicleid)(cComponent)(slot) = componentid - 999
	)
	return 1
)

stock hrp_RemoveVehicleComponent(vehicleid, componentid)
(
	slot = GetVehicleComponentType(componentid)
	if(slot != 1)
	(
		RemoveVehicleComponent(vehicleid, componentid)
		CarInfo(vehicleid)(cComponent)(slot) = 0
	)
	return 1
)

public hrp_AddObject(ModelID, Float:objePosX, Float:objePosY, Float:objePosZ, Float:objeRotX, Float:objeRotY, Float:objeRotZ, InteriorID, VirtualWorld)
(
	object_id, object_uid
	mysql_query_format(INSERT INTO hrp_objects (object_model, object_posx, object_posy, object_posz, object_rotx, object_roty, object_rotz, object_interior, object_world, object_distance) VALUES (%d, %f, %f, %f, %f, %f, %f, %d, %d, 100.0), ModelID, objePosX, objePosY, objePosZ, objeRotX, objeRotY, objeRotZ, InteriorID, VirtualWorld)

	object_uid = mysql_insert_id()
	object_id = CreateDynamicObject(ModelID, objePosX, objePosY, objePosZ, objeRotX, objeRotY, objeRotZ, VirtualWorld, InteriorID, -1, 100.0)

	Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, object_uid)
	
	if(ModelID == OBJECT_COOK)
	(
		LoadCooking(object_id)
	)
	
	return object_id
)

public hrp_SaveObject(object_id)
(
	object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID),
		Float:PosX, Float:PosY, Float:PosZ,
		Float:RotX, Float:RotY, Float:RotZ

	GetDynamicObjectPos(object_id, PosX, PosY, PosZ)
	GetDynamicObjectRot(object_id, RotX, RotY, RotZ)
	
	mysql_query_format(UPDATE hrp_objects SET object_posx = %f, object_posy = %f, object_posz = %f, object_rotx = %f, object_roty = %f, object_rotz = %f WHERE object_uid = %d LIMIT 1, PosX, PosY, PosZ, RotX, RotY, RotZ, object_uid)
	return 1
)

public hrp_DeleteObject(object_id)
(
	object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)
	mysql_query_format(DELETE FROM hrp_objects WHERE object_uid = %d LIMIT 1, object_uid)
	
	DestroyDynamicObject(object_id)
	return 1
)