public SetPlayerNormalColor(playerid)
(
	string(128)
	if(!PlayerCache(playerid)(pMaskUID))
	(
		format(string, sizeof(string), %s (%d)%s, PlayerName(playerid), playerid, GetPlayerStatusInfo(playerid))
	)
	else
	(
		format(string, sizeof(string), %s%s, PlayerName(playerid), GetPlayerStatusInfo(playerid))
	)
	Update3DTextLabelText(Text3D:PlayerCache(playerid)(pNameTag), PlayerCache(playerid)(pNickColor), string)
	return 1
)

forward SetPlayerNormalScreenAfterHit(playerid)
public SetPlayerNormalScreenAfterHit(playerid)
(
	TextDrawHideForPlayer(playerid, Text:TextDrawHitscreen(playerid))
	return 1
)

public OnBasketBallFallingDown(objectid, Float:FallTargetX, Float:FallTargetY, Float:FallTargetZ)
(
	MoveDynamicObject(objectid, FallTargetX, FallTargetY, FallTargetZ - 0.8, 8.0 + random(3))
	return 1
)

/*
public OnQueryFinish(query(), resultid, extraid, connectionHandle)
(
	return 1
)

public OnQueryError(errorid, error(), resultid, extraid, callback(), query(), connectionHandle)
(
	printf((mysql)(error) %s (errorid: %d), error, errorid)
	return 1
)
*/

public OnMysqlError(error(), errorid, MySQL:handle)
(
	printf((mysql)(error) %s (errorid: %d), error, errorid)
	return 1
)

/*public Audio_OnTransferFile(playerid, file(), current, total, result)
(
	if(!result)
	(
		TextDrawShowForPlayer(playerid, Text:TextDrawAudioError)
		return 1
	)

	string(64)
	
	format(string, sizeof(string), ~b~Audio plugin: ~w~%d/%d, current, total)
	GameTextForPlayer(playerid, string, 3000, 3)
	
	if(current == total) GameTextForPlayer(playerid, ~w~Audio plugin ~g~zaladowany, 3000, 3)
	return 1
)*/

public LoadAnims()
(
	data(128), anim_id
	mysql_query(SELECT * FROM hrp_anim)
	
	print((load) Rozpoczynam proces wczytywania wszystkich animacji z bazy...)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		anim_id ++
		
		sscanf(data, p(|)ds(12)s(16)s(24)fdddddd,
		AnimInfo(anim_id)(aUID),
		AnimInfo(anim_id)(aCommand),
		AnimInfo(anim_id)(aLib),
		AnimInfo(anim_id)(aName),
		AnimInfo(anim_id)(aSpeed),
		AnimInfo(anim_id)(aOpt1),
		AnimInfo(anim_id)(aOpt2),
		AnimInfo(anim_id)(aOpt3),
		AnimInfo(anim_id)(aOpt4),
		AnimInfo(anim_id)(aOpt5),
		AnimInfo(anim_id)(aAction))
	)
	mysql_free_result()
	
	printf((load) Wczytano %d animacji/e., anim_id)
	return 1
)

public KillAnimation(playerid)
(
	ApplyAnimation(playerid, CARRY, crry_prtial, 4.0, 0, 0, 0, 0, 0, 1)
	return 1
)

stock GetDoorID(door_uid)
(
	doorid = -1
	foreach(Doors, d)
	(
		if(DoorData(d)(dUID) == door_uid)
		(
			doorid = d
			break
		)
	)
	return doorid
)

stock GetProductID(product_uid)
(
	product_id
	for (i = 1 i ( MAX_PRODUCTS i++)
	(
		if(ProductInfo(i)(pUID) == product_uid)
		(
			product_id = i
			break
		)
	)
	return product_id
)

stock GetFreeOrderID()
(
	order_id
	for (o = 1 o ( MAX_ORDERS o++)
	(
		if(!OrderInfo(o)(oUID))
		(
			order_id = o
			break
		)
	)
	return order_id
)

stock GetOrderID(order_uid)
(
	order_id
	for (o = 1 o ( MAX_ORDERS o++)
	(
		if(OrderInfo(o)(oUID) == order_uid)
		(
			order_id = o
			break
		)
	)
	return order_id
)

stock GetOffererID(playerid)
(
	customerid
	foreach(Player, i)
	(
		if(Offer(i)(oCustomerID) == playerid)
		(
			customerid = i
			break
		)
	)
	return customerid
)

stock GetAnimationID(uid)
(
	anim_id
	for (a = 1 a ( MAX_ANIMATIONS a++)
	(
		if(AnimInfo(a)(aUID) == uid)
		(
			anim_id = a
			break
		)
	)
	return anim_id
)

stock GetPackageID(uid)
(
	package_id
	foreach(Packages, p)
	(
		if(PackageInfo(p)(pUID) == uid)
		(
			package_id = p
			break
		)
	)
	return package_id
)

stock GetLimitedPackageID(uid)
(
	limitedpackage_id
	foreach(LimitedPackages, p)
	(
		if(LimitedPackageInfo(p)(pUID) == uid)
		(
			limitedpackage_id = p
			break
		)
	)
	return limitedpackage_id
)

stock GetFreeBusStopID()
(
	busstop_id
	for(b = 1 b ( MAX_BUS_STOPS b++)
	(
		if(BusStopData(b)(bUID) == 0)
		(
			busstop_id = b
			break
		)
	)
	return busstop_id
)

stock GetFreePhotoRadarID()
(
	photoradar_id
	for(p = 1 p ( MAX_PHOTO_RADARS p++)
	(
		if(PhotoRadarInfo(p)(pUID) == 0)
		(
			photoradar_id = p
			break
		)
	)
	return photoradar_id
)

stock IsParkingPlaceFree(vehid)
(
	Float:posx, Float:posy, Float:posz, world, free = 1
 	GetVehiclePos(vehid, posx, posy, posz)
 	
 	world = GetVehicleVirtualWorld(vehid)

  	mysql_query_format(SELECT car_uid FROM hrp_cars WHERE car_posx ( %f + 4 AND car_posx ) %f - 4 AND car_posy ( %f + 4 AND car_posy ) %f - 4 AND car_posz ( %f + 4 AND car_posz ) %f - 4 AND car_world = %d LIMIT 1, posx, posx, posy, posy, posz, posz, world)
   	
	mysql_store_result()
	if(mysql_num_rows())
	(
		free = 0
	)
	mysql_free_result()
	
	return free
)

stock PreloadAnimLib(playerid, animlib())
(
	ApplyAnimation(playerid, animlib, null, 0.0, 0, 0, 0, 0, 0)
	return 1
)

stock CharCode(playerid)
(

	data(256), mask(32)

	mysql_query_format(SELECT mask_value FROM hrp_mask WHERE char_uid = %d LIMIT 1, PlayerCache(playerid)(pUID))
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)s(32), mask)
		)
	)
	else
	(
		text(32), char1(5), char2(5), char3(5), char4(4), charcode2(5)
	
		format(text, sizeof(text), %d, PlayerCache(playerid)(pUID))
		
		strmid(charcode2, MD5_Hash(text), 0, strlen(MD5_Hash(text)), 5)
		strmid(char1, charcode2(0), 0, 1, 5)
		strmid(char2, charcode2(1), 0, 1, 5)
		strmid(char3, charcode2(2), 0, 1, 5)
		strmid(char4, charcode2(3), 0, 1, 5)
		
		format(mask, sizeof(mask), %s%s%s%s, char1, char2, char3, char4)
	)
	mysql_free_result()

	return mask
)

stock DescWrap(givenString(128)) // /opis
(
	editingString(128), spaceCounter = 0
	memcpy(editingString, givenString, 0, 128 * 4)

	for (i = 0 editingString(i) != 0 i++)
	(
		if(editingString(i) == , || editingString(i) == .)
		(
			if(editingString(i+1) !=  ) strins(editingString,  , i + 1)
		)

		if(editingString(i) ==   && editingString(i+1) !=  ) spaceCounter++

		if(spaceCounter )= 5)
		(
			editingString(i) = \n
			spaceCounter = 0
	 	)
		
		if(editingString(i) == \) editingString(i) =  
		else if(editingString(i) == \) editingString(i) =  
		else if(editingString(i) == \\) editingString(i) =  
	)
	return editingString
)

stock StringFormatForDialog(givenString()) // poprawki 
(
	editingString(1024), spaceCounter = 0
	memcpy(editingString, givenString, 0, 128 * 8)

	for (i = 0 editingString(i) != 0 i++)
	(
		if(editingString(i) == , || editingString(i) == .)
		(
			if(editingString(i+1) !=  ) strins(editingString,  , i + 1)
		)

		if(editingString(i) ==   && editingString(i+1) !=  ) spaceCounter++

		if(spaceCounter )= 10)
		(
			editingString(i) = \n
			spaceCounter = 0
	 	)
		
		if(editingString(i) == \) editingString(i) =  
		else if(editingString(i) == \) editingString(i) =  
		else if(editingString(i) == \\) editingString(i) =  
	)
	return editingString
)

stock DialogWrap(givenString())
(
	editingString(1024), wordCount = 0
	format(editingString,sizeof(editingString),%s,givenString)
	for(i = 0 editingString(i) != 0 i++)
	(
		if(editingString(i) ==  )
		(
			wordCount++
		)
		if(wordCount ) 8)
		(
			editingString(i) = \n
			wordCount = 0
		)
	)
	
	return editingString
)

stock LabelWrap(givenString(128)) // Etykiety 3D
(
	editingString(128)
 	memcpy(editingString, givenString, 0, 128 * 4)

	for (i = 0 editingString(i) != 0 i++)
	(
		if(editingString(i) == ( && editingString(i + 7) == ))
		(
			editingString(i) = (
			editingString(i + 7) = )
		)

		if(editingString(i) == , || editingString(i) == .)
		(
			if(editingString(i+1) !=  ) strins(editingString,  , i + 1)
		)

		if(editingString(i) == |)
		(
			editingString(i) = \n
	 	)
	)
	return editingString
)

stock GetClosestObjectByModel(playerid,object_model,Float:range = 5.0)
(
	Float:Pos(3),Float:dist
	GetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))
	
	objectID = INVALID_OBJECT_ID
	
	for(object_id = 0  object_id (= MAX_OBJECTS object_id++)
	(
		if(IsValidDynamicObject(object_id))
		(
			if(Streamer_IsItemVisible(playerid, STREAMER_TYPE_OBJECT, object_id))
			(
				Streamer_GetDistanceToItem(Pos(0),Pos(1),Pos(2), STREAMER_TYPE_OBJECT, object_id, dist)
				
				if(dist (= range)
				(

					model = GetObjectModel(object_id)
					
					if(model == object_model)
					(
						objectID = object_id
						break
					)
				)
			)
		)
	)
	
	return objectID
)

stock GetClosestObject(playerid, Float:range = 5.0)
(
	Float:prevdist = range, ObjectID = INVALID_OBJECT_ID,
		visible_items,  Float:PosX, Float:PosY, Float:PosZ, Float:dist
		
	GetPlayerPos(playerid, PosX, PosY, PosZ)

	for (object_id = 0 object_id (= MAX_OBJECTS object_id++)
	(
 		if(IsValidDynamicObject(object_id))
		(
	 		if(Streamer_IsItemVisible(playerid, STREAMER_TYPE_OBJECT, object_id))
			(
				visible_items ++
				Streamer_GetDistanceToItem(PosX, PosY, PosZ, STREAMER_TYPE_OBJECT, object_id, dist)

				if((dist ( prevdist))
				(
	   				prevdist = dist
					ObjectID = object_id
				)

	   			if(visible_items )= Streamer_CountVisibleItems(playerid, STREAMER_TYPE_OBJECT))
				(
					break
				)
			)
		)
	)
	return ObjectID
)

stock GetObjectID(object_uid)
(
	for (object_id = 0 object_id (= MAX_OBJECTS object_id++)
	(
		if(IsValidDynamicObject(object_id))
		(
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID) == object_uid)
			(
				return object_id
			)
		)
	)
	return INVALID_OBJECT_ID
)

stock CreateAltQuitLabel(playerid)
(
	string(128), reason = PlayerCache(playerid)(pQuit)
	if(reason == QUIT_TIMEOUT)
	(
		format(string, sizeof(string), (( %s - timeout )), PlayerName(playerid))
	)
	else if(reason == QUIT_Q)
	(
		format(string, sizeof(string), (( %s - /q )), PlayerName(playerid))
	)
	else if(reason == QUIT_QS)
	(
		format(string, sizeof(string), (( %s - /qs )), PlayerName(playerid))
	)
	else if(reason == QUIT_KICK)
	(
		format(string, sizeof(string), (( %s - kick )), PlayerName(playerid))
	)
	else if(reason == QUIT_BAN)
	(
		format(string, sizeof(string), (( %s - ban )), PlayerName(playerid))
	)
	else if(reason == QUIT_SWITCHING)
	(
		format(string, sizeof(string), (( %s - zmiana postaci )), PlayerName(playerid))
	)
	else
	(
		format(string, sizeof(string), (( %s - powÛd nieznany )), PlayerName(playerid))
	)

	if(reason == QUIT_SWITCHING)
	(
		ProxDetectorDucktape(50, playerid, string)
	)
	else
	(
		if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
			ProxDetector(50, playerid, string, COLOR_GREY, COLOR_GREY, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true)
	)
	return 1
)

stock CreateQuitLabel(playerid)
(
	Text3D:label_id, string(128), Float:PosX, Float:PosY, Float:PosZ, world = GetPlayerVirtualWorld(playerid), interior = GetPlayerInterior(playerid), reason = PlayerCache(playerid)(pQuit)
	GetPlayerPos(playerid, PosX, PosY, PosZ)
	if(reason == QUIT_TIMEOUT)
	(
		format(string, sizeof(string), (( %s - timeout )), PlayerName(playerid))
	)
	else if(reason == QUIT_Q)
	(
		format(string, sizeof(string), (( %s - /q )), PlayerName(playerid))
	)
	else if(reason == QUIT_QS)
	(
		format(string, sizeof(string), (( %s - /qs )), PlayerName(playerid))
	)
	else if(reason == QUIT_KICK)
	(
		format(string, sizeof(string), (( %s - kick )), PlayerName(playerid))
	)
	else if(reason == QUIT_BAN)
	(
		format(string, sizeof(string), (( %s - ban )), PlayerName(playerid))
	)
	else
	(
		format(string, sizeof(string), (( %s - powÛd nieznany )), PlayerName(playerid))
	)
	
	label_id = CreateDynamic3DTextLabel(LabelWrap(string), COLOR_GREY, PosX, PosY, PosZ, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, world, interior, -1, 80.0)
	
	i = Itter_Free(Quiters)
	QuitInfo(i)(qLLabelID) = label_id
	QuitInfo(i)(qLTime) = gettime()
	Itter_Add(Quiters, i)
	
	return 1
)

stock GetClosestLabel(playerid)
(
	Float:prevdist = 5.0, LabelID = INVALID_3DTEXT_ID,
		visible_items

	for (label_id = 0 label_id (= CountDynamic3DTextLabels() label_id++)
	(
 		if(IsValidDynamic3DTextLabel(Text3D:label_id))
		(
	 		if(Streamer_IsItemVisible(playerid, STREAMER_TYPE_3D_TEXT_LABEL, label_id))
			(
				visible_items ++
				Float:dist = GetDistanceToLabel(playerid, label_id)
				if((dist ( prevdist))
				(
	   				prevdist = dist
					LabelID = label_id
				)

	   			if(visible_items )= Streamer_CountVisibleItems(playerid, STREAMER_TYPE_3D_TEXT_LABEL))
				(
					break
				)
			)
		)
	)
	return LabelID
)

stock GetDistanceToLabel(playerid, label_id)
(
	Float:x1, Float:y1, Float:z1,
		Float:x2, Float:y2, Float:z2, Float:dis

	GetPlayerPos(playerid, x1, y1, z1)
	
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_X, x2)
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Y, y2)
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Z, z2)

	dis = floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2))
	return floatround(dis)
)





stock mysql_query_format(format_query(), va_args())
(
	query(512)

	va_format(query, sizeof(query), format_query, va_start(1))
	mysql_query(query)

	return 1
)

stock FormatTextDrawColors(givenString())
(
	pos, editingString(128)
	memcpy(editingString, givenString, 0, 128 * 4)

	pos = strfind(editingString, ~, true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 1)
		pos = strfind(editingString, ~, true, pos + 1)
	)
	
	pos = strfind(editingString, (w), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, ~w~, pos)

		pos = strfind(editingString, (w), true, pos + 3)
	)
	
	pos = strfind(editingString, (b), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, ~b~, pos)

		pos = strfind(editingString, (b), true, pos + 3)
	)
	
	pos = strfind(editingString, (g), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, ~g~, pos)

		pos = strfind(editingString, (g), true, pos + 3)
	)
	
	pos = strfind(editingString, (r), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, ~r~, pos)
		
		pos = strfind(editingString, (r), true, pos + 3)
	)
	
	pos = strfind(editingString, (p), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, ~p~, pos)

		pos = strfind(editingString, (p), true, pos + 3)
	)
	
	pos = strfind(editingString, (y), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, ~y~, pos)

		pos = strfind(editingString, (y), true, pos + 3)
	)
	
	pos = strfind(editingString, (h), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, ~h~, pos)

		pos = strfind(editingString, (h), true, pos + 3)
	)
	return editingString
)

stock FormatLabelColors(givenString())
(
	pos, editingString(128)
	memcpy(editingString, givenString, 0, 128 * 4)

	pos = strfind(editingString, (w), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, (FFFFFF), pos)

		pos = strfind(editingString, (w), true, pos + 8)
	)

	pos = strfind(editingString, (b), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, (0000BB), pos)

		pos = strfind(editingString, (b), true, pos + 8)
	)

	pos = strfind(editingString, (g), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, (33AA33), pos)

		pos = strfind(editingString, (g), true, pos + 8)
	)

	pos = strfind(editingString, (r), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, (AA3333), pos)

		pos = strfind(editingString, (r), true, pos + 8)
	)

	pos = strfind(editingString, (p), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, (C2A2DA), pos)

		pos = strfind(editingString, (p), true, pos + 8)
	)

	pos = strfind(editingString, (y), true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 3)
		strins(editingString, (FFFF00), pos)

		pos = strfind(editingString, (y), true, pos + 8)
	)
	return editingString
)

stock ColorFade (color, value, maxvalue)
(
	if (0 (= value (= maxvalue)
	(
		new
			Float: ratio = float (value) / float (maxvalue)
		new
			r = max (0, min (255, floatround (float ((color )) 24) & 0xFF) * ratio))),
			g = max (0, min (255, floatround (float ((color )) 16) & 0xFF) * ratio))),
			b = max (0, min (255, floatround (float ((color )) 8) & 0xFF) * ratio)))
		return (r (( 24) | (g (( 16) | (b (( 8) | (value & 0xFF)
	)
	return 0
)

stock EscapeTildes(givenString())
(
	pos, editingString(64)
	memcpy(editingString, givenString, 0, 64 * 4)

	pos = strfind(editingString, ~, true)
	while(pos != -1)
	(
		strdel(editingString, pos, pos + 1)
		pos = strfind(editingString, ~, true, pos + 1)
	)
	return editingString
)

stock EscapePL(name())
(
	for(i = 0 name(i) != 0 i++)
	(
		if(name(i) == ú) name(i) = s
		else if(name(i) == Í) name(i) = e
		else if(name(i) == Û) name(i) = o
		else if(name(i) == π) name(i) = a
		else if(name(i) == ≥) name(i) = l
		else if(name(i) == ø) name(i) = z
		else if(name(i) == ü) name(i) = z
		else if(name(i) == Ê) name(i) = c
		else if(name(i) == Ò) name(i) = n
		else if(name(i) == å) name(i) = S
		else if(name(i) ==  ) name(i) = E
		else if(name(i) == ”) name(i) = O
		else if(name(i) == •) name(i) = A
		else if(name(i) == £) name(i) = L
		else if(name(i) == Ø) name(i) = Z
		else if(name(i) == è) name(i) = Z
		else if(name(i) == ∆) name(i) = C
		else if(name(i) == —) name(i) = N
		else if(name(i) ==  ) name(i) = _
	)
)

stock MagicQuotes(name())
(
	for(i = 0 name(i) != 0 i++)
	(
		if(name(i) == \) name(i) =  
		else if(name(i) == \) name(i) =  
	)
)

stock crossp(Float:v1x, Float:v1y, Float:v1z, Float:v2x, Float:v2y, Float:v2z, &Float:output)
(
		new	Float:c1 = (v1y * v2z) - (v1z * v2y),
	  		Float:c2 = (v1z * v2x) - (v1x * v2z),
			Float:c3 = (v1x * v2y) - (v1y * v2x)
			
		output = floatsqroot ((c1 * c1) + (c2 * c2) + (c3 * c3))
		return 0
)

stock GetDistanceFromPointToLine(&Float:distance, Float:line_vector_x, Float:line_vector_y, Float:line_vector_z, Float:line_x, Float:line_y, Float:line_z, Float:point_x, Float:point_y, Float:point_z)
(
		static Float:output
		crossp(line_vector_x, line_vector_y, line_vector_z, point_x - line_x, point_y - line_y, point_z - line_z, output)
		distance = output / floatsqroot ((line_vector_x * line_vector_x) + (line_vector_y * line_vector_y) + (line_vector_z * line_vector_z))
		return 0
)

stock GetRadioSlot(group_id)
(
	for(i = 1 i ( sizeof(RadioData) i++)
	(
		if(RadioData(i)(gUID) == GroupData(group_id)(gUID))
		(
			return i
		)
	)
		
	return false
)

stock ConvertNonNormaQuatToEuler(Float: qw, Float: qx, Float: qy, Float: qz, &Float: heading, &Float: attitude, &Float: bank)
(
	new
		Float: sqw = qw * qw,
		Float: sqx = qx * qx,
		Float: sqy = qy * qy,
		Float: sqz = qz * qz,
		Float: unit = sqx + sqy + sqz + sqw,
		Float: test = qx * qy + qz * qw
	/*
	if (test ) 0.499 * unit)
	(
		heading = 2 * atan2 (qx, qw)
		attitude = 3.141592653 / 2
		bank = 0
		return 1
	)
	if (test ( -0.499 * unit)
	(
		heading = -2 * atan2 (qx, qw)
		attitude = -3.141592653 / 2
		bank = 0
		return 1
	)
	*/
	heading = atan2 (2 * qy * qw - 2 * qx * qz, sqx - sqy - sqz + sqw)
	attitude = asin (2 * test / unit)
	
	bank = atan2(2 * qx * qw - 2 * qy * qz, -sqx + sqy - sqz + sqw)
	return 1
)

ClearCache(playerid, switching = false)
(
	// Zeruj cache
	LoginTime(playerid)(0) = 0
	LoginTime(playerid)(1) = 0
	LoginTime(playerid)(2) = 0

	PlayerCache(playerid)(pUID) 			= 0
	if(!switching)
	(
		PlayerCache(playerid)(pGID) 			= 0
		PlayerCache(playerid)(pSwitching)		= false
		PlayerCache(playerid)(pSwitchingX)		= 0.0
		PlayerCache(playerid)(pSwitchingY)		= 0.0
		PlayerCache(playerid)(pSwitchingZ)		= 0.0
		PlayerCache(playerid)(pSwitchingDX)		= 0.0
		PlayerCache(playerid)(pSwitchingDY)		= 0.0
		PlayerCache(playerid)(pSwitchingDZ)		= 0.0
		PlayerCache(playerid)(pSwitchingStage)	= STAGE_NONE
		PlayerCache(playerid)(pNickColor)	   = 0xFFFFFF88

		PlayerCache(playerid)(pAdmin) 			= 0
		PlayerCache(playerid)(pAdminDuty)	   = false
		PlayerCache(playerid)(pUserColor)	   = 0

		PlayerCache(playerid)(pLastSwitch)		= 0

		PlayerCache(playerid)(pShowDoorText)	= 0
		PlayerCache(playerid)(pShowInfoText)	= 0

		PlayerCache(playerid)(pLastVeh) 		= INVALID_VEHICLE_ID
	)

	PlayerCache(playerid)(pClicked)	= INVALID_PLAYER_ID

	PlayerCache(playerid)(pArmour)		  = 0.0
	PlayerCache(playerid)(pArmourDelay)		= 0

	PlayerCache(playerid)(pHours)		   = 0
	PlayerCache(playerid)(pMinutes)		 = 0

	PlayerCache(playerid)(pSkin) 			= 0
	PlayerCache(playerid)(pCash) 			= 0
	PlayerCache(playerid)(pChecksum)		= 0
	
	PlayerCache(playerid)(pIGDBID) 			= 0
	PlayerCache(playerid)(pIGTimeIn)		= 0
	
	PlayerCache(playerid)(pBlockChecksum)	= 0

	PlayerCache(playerid)(pAASlot) = 0

	PlayerCache(playerid)(pBankCash)		= 0
	PlayerCache(playerid)(pBankNumber)	  = 0
	PlayerCache(playerid)(pBankLastTransaction) = 0

	PlayerCache(playerid)(pWarns)		   = 0

	PlayerCache(playerid)(pInt)			 = 0
	PlayerCache(playerid)(pVW)			  = 0

	PlayerCache(playerid)(pBW)			  = 0
	PlayerCache(playerid)(pBleeding)		= 0
	PlayerCache(playerid)(pInsurance) = 0
	PlayerCache(playerid)(pInsuranceCompany) = 0
	PlayerCache(playerid)(pInsuranceCount) = 0
	PlayerCache(playerid)(pWounded)		  = 0
	PlayerCache(playerid)(pHospitalization) = 0
	PlayerCache(playerid)(pHospitalCharge)	= 0
	PlayerCache(playerid)(pHospitalBed)		= 0
	PlayerCache(playerid)(pAJ)			  = 0
	
	PlayerCache(playerid)(pPressStage) = 0

	PlayerCache(playerid)(pBlock)		   = 0

	PlayerCache(playerid)(pHotel)			= 0

	PlayerCache(playerid)(pRegion)			= 0

	PlayerCache(playerid)(pGroupDuty)	   = 0
	PlayerCache(playerid)(pGroupDutyTime)   = 0
	PlayerCache(playerid)(pMainGroupSlot)   = INVALID_SLOT_ID

	PlayerCache(playerid)(pDutyUID)		 = 0

	PlayerCache(playerid)(pDocuments)	   = 0

	PlayerCache(playerid)(pPDP)			 = 0

	PlayerCache(playerid)(pPhoneNumber)	 = 0
	PlayerCache(playerid)(pCallTicks) = 0

	PlayerCache(playerid)(pArrest)		  = 0
	PlayerCache(playerid)(pArrestTime)	  = 0
	PlayerCache(playerid)(pArrestDay)	  = 0

	PlayerCache(playerid)(pSpawnPlace)	  = 0
	PlayerCache(playerid)(pHouse)		   = 0
	PlayerCache(playerid)(pFamilyHouse) 	= 0

	PlayerCache(playerid)(pFightingStyle)   = 0

	PlayerCache(playerid)(pLogTries) 		= 3

	PlayerCache(playerid)(pCarSpawned)		= 0


	PlayerCache(playerid)(pTaxiVeh) 		= INVALID_VEHICLE_ID
	PlayerCache(playerid)(pTaxiPay) 		= 0
	PlayerCache(playerid)(pTaxiPrice) 		= 0
	PlayerCache(playerid)(pTaxiPassenger) 	= INVALID_PLAYER_ID

	PlayerCache(playerid)(pWalkAnim)		= 0

	PlayerCache(playerid)(pShowItems) 		= 0

	PlayerCache(playerid)(pKiller)	   = 0
	PlayerCache(playerid)(pKillerWeapon)	= 0

	PlayerCache(playerid)(pMaskUID) 		= 0

	PlayerCache(playerid)(pRepairVeh)	   = INVALID_VEHICLE_ID
	PlayerCache(playerid)(pRepairType)		= 0
	PlayerCache(playerid)(pRepairTime)	  = 0
	
	PlayerCache(playerid)(pTireVeh)	 	  = INVALID_VEHICLE_ID
	PlayerCache(playerid)(pTireTime)	   = 0

	PlayerCache(playerid)(pSprayType)		= 0
	PlayerCache(playerid)(pSprayVeh)		= INVALID_VEHICLE_ID
	PlayerCache(playerid)(pSprayTime)	   = 0
	PlayerCache(playerid)(pSprayColor)(0)   = -1
	PlayerCache(playerid)(pSprayColor)(1)   = -1

	PlayerCache(playerid)(pMontageVeh)	  = INVALID_VEHICLE_ID
	PlayerCache(playerid)(pMontageTime)	 = 0
	PlayerCache(playerid)(pMontageItem)	 = 0

	PlayerCache(playerid)(pCuffed)		  = INVALID_PLAYER_ID
	PlayerCache(playerid)(pCuffedStill)	  = INVALID_PLAYER_ID
	
	PlayerCache(playerid)(pRoped)		  = INVALID_PLAYER_ID
	
	PlayerCache(playerid)(pBagged)		  = INVALID_PLAYER_ID
	
	PlayerCache(playerid)(pGagged)		  = INVALID_PLAYER_ID

	PlayerCache(playerid)(pSearches)		= INVALID_PLAYER_ID
	PlayerCache(playerid)(pSearchTime)	  = 0

	PlayerCache(playerid)(pHealing)		 = INVALID_PLAYER_ID

	PlayerCache(playerid)(pTogW)			= false
	PlayerCache(playerid)(pTogBo)		   = false
	PlayerCache(playerid)(pTogRo)		   = false
	
	PlayerCache(playerid)(pVehCollisions) = 0
	
	PlayerCache(playerid)(pSlots) = false
	PlayerCache(playerid)(pSpread)		   = false
	PlayerCache(playerid)(pPlayBasket)		   = false
	PlayerCache(playerid)(pBasketID) = INVALID_OBJECT_ID
	PlayerCache(playerid)(pPut) = false
	PlayerCache(playerid)(pSpreadTime) = 0

	PlayerCache(playerid)(pLastW)		   = INVALID_PLAYER_ID
	PlayerCache(playerid)(pLastWTo)		   = INVALID_PLAYER_ID

	PlayerCache(playerid)(pAFK)			 = 5

	PlayerCache(playerid)(pPlayAnim)		= false

	PlayerCache(playerid)(pSpectate)		= INVALID_PLAYER_ID
	PlayerCache(playerid)(pSpectateChange)	= 0

	PlayerCache(playerid)(pCall)		   = -1
	PlayerCache(playerid)(pAlarmCall)	= -1
	PlayerCache(playerid)(pSerivceNumberAs) = 0
	PlayerCache(playerid)(pUsingBooth)	  = false

	PlayerCache(playerid)(pFreeze)		  = 0

	PlayerCache(playerid)(pWoundedTime)	 = 0
	PlayerCache(playerid)(pWoundAnim)	= false

 	PlayerCache(playerid)(pAudioHandle)	 = 0
 	PlayerCache(playerid)(pAudioVolume)		= 0
 	PlayerCache(playerid)(pRingToneHandle)  = 0

	PlayerCache(playerid)(pAirBrkWarns)	 = 0
	PlayerCache(playerid)(pGotAirBrkPos)	= 0

	PlayerCache(playerid)(pWallRideWarns)   = 0

	PlayerCache(playerid)(pGymPass)		 = 0
	PlayerCache(playerid)(pPaintballPass) 	= 0
	PlayerCache(playerid)(pGymObject)  		= INVALID_OBJECT_ID
	PlayerCache(playerid)(pGymType)			= TRAIN_NONE
	PlayerCache(playerid)(pGymPhase)   		= 0
	PlayerCache(playerid)(pGymValue1)  		= 0
	PlayerCache(playerid)(pGymValue2)  		= 0

	PlayerCache(playerid)(pGymNutrient)		= 0
	PlayerCache(playerid)(pGymFactor)		= 0
	
	PlayerCache(playerid)(pTrainTime)	   = 0
	PlayerCache(playerid)(pPaintballTime)	 = 0

	PlayerCache(playerid)(pPreviewTime)	 = 0

	PlayerCache(playerid)(pLive)			= 0
	PlayerCache(playerid)(pInterview)	   = INVALID_PLAYER_ID
	PlayerCache(playerid)(pInterviewSlot)	   = INVALID_PLAYER_ID

	PlayerCache(playerid)(pLastPay)		 = 0
	PlayerCache(playerid)(pLastReport)	  = 0

	PlayerCache(playerid)(pRaising)		 = false

	PlayerCache(playerid)(pJob)			 = 0
	PlayerCache(playerid)(pFed)			 = 0

	PlayerCache(playerid)(pDrivingLesson)   = 0
	PlayerCache(playerid)(pDoorFreeze) 		= 0

	PlayerCache(playerid)(pBelts)		   = false
	PlayerCache(playerid)(pGloves)		  = false
	PlayerCache(playerid)(pRoll)			= false

	PlayerCache(playerid)(pDrunkLevel)	  = 0

	PlayerCache(playerid)(pCrash)		   = 0
	PlayerCache(playerid)(pQSing)			= 0
	PlayerCache(playerid)(pStatus)		  = 0

	PlayerCache(playerid)(pAiming)		  = false

	PlayerCache(playerid)(pPackage)		 = false
	PlayerCache(playerid)(pPackageUID)	  = 0
	PlayerCache(playerid)(pWholeSale)	   = -1
	
	PlayerCache(playerid)(pSweep)		= false
	PlayerCache(playerid)(pSweepRoute)		= 0
	PlayerCache(playerid)(pSweepSteps)		= 0
	PlayerCache(playerid)(pSweepStep)		= 0
	PlayerCache(playerid)(pSweepTime)		= 0
	

	PlayerCache(playerid)(pFish)			= false
	PlayerCache(playerid)(pFishingRodUID)   = 0
	PlayerCache(playerid)(pFishTaking)	  = false

	PlayerCache(playerid)(pBusRide)		 = false
	PlayerCache(playerid)(pBusStart)		= 0
	PlayerCache(playerid)(pBusPrice)		= 0
	PlayerCache(playerid)(pBusTravel)	   = 0
	PlayerCache(playerid)(pBusTime)		 = 0

	PlayerCache(playerid)(pClothChanging)   = false
	PlayerCache(playerid)(pClothID)		 = 0

	PlayerCache(playerid)(pAccessChanging)  = false
	PlayerCache(playerid)(pAccessID)		= 0
	PlayerCache(playerid)(pAccessShop)		= 0

	PlayerCache(playerid)(pAccessEditing)   = false

	PlayerCache(playerid)(pRacePhase)	   = 0
	PlayerCache(playerid)(pRacePoint)	   = 0
	PlayerCache(playerid)(pRaceCheckpoints) = 0

	PlayerCache(playerid)(pDriving)		 = 0.0
	PlayerCache(playerid)(pCondition)		= 0.0
	PlayerCache(playerid)(pShooting)		= 0.0
	PlayerCache(playerid)(pFishing)		 = 0.0
	PlayerCache(playerid)(pStrength)		= 0.0
		
	PlayerCache(playerid)(pKnownStyles)	=	0
	PlayerCache(playerid)(pDailyReps) = 0

	PlayerCache(playerid)(pDependence)	  = 0.0
	PlayerCache(playerid)(pSkillShowed)	 = 0

	PlayerCache(playerid)(pBasketBall)	  = INVALID_OBJECT_ID
	PlayerCache(playerid)(pHavingBall)	  = false
	PlayerCache(playerid)(pBallPhase)	   = 0

	PlayerCache(playerid)(pSmokeJoint)	  = false
	PlayerCache(playerid)(pSmokeReps)	   = 0
	PlayerCache(playerid)(pSmokeLevel)	  = 0

	PlayerCache(playerid)(pDrugLevel)	   = 0
	PlayerCache(playerid)(pMusicPlayerUID)  = 0

	PlayerCache(playerid)(pMove3DText)	  = INVALID_3DTEXT_ID
	PlayerCache(playerid)(pMoveObject)	  = INVALID_OBJECT_ID

	PlayerCache(playerid)(pUsingOptiwand)   = false
	
	PlayerCache(playerid)(pTogOOC)   = false
	
	PlayerCache(playerid)(pRead)   = false

	//Admin stuff
	PlayerCache(playerid)(pAdminChat)		= true
	PlayerCache(playerid)(pChangeName)	  = false

	// Bypass blokady biegania i bicia
	PlayerCache(playerid)(pEnteringVeh)	 = 0

	// Flash
	PlayerCache(playerid)(pFlashed) 		= 0
	
	// Sex
	PlayerCache(playerid)(pHavingSex)		= false
	PlayerCache(playerid)(pSexType)			= 0
	PlayerCache(playerid)(pSexReps)			= 0
	PlayerCache(playerid)(pSexTime)			= 0
		
	// Nowe efekty dragÛw
	PlayerCache(playerid)(pRage)				= false
	PlayerCache(playerid)(pRageTime)			= 0
	PlayerCache(playerid)(pRageDrug)			= 0
	PlayerCache(playerid)(pRageDrunkLevel)		= 0
	PlayerCache(playerid)(pRageDrugUse)			= 0
	PlayerCache(playerid)(pRageStrength)		= 0
	
	// Wymiana opon
	PlayerCache(playerid)(pTireVeh)			= INVALID_VEHICLE_ID
	PlayerCache(playerid)(pTireTime)		= 0
	
	// Pompowanie opon
	PlayerCache(playerid)(pPumpVeh)			= INVALID_VEHICLE_ID
	PlayerCache(playerid)(pPumpTime)		= 0
	
	// Pompowanie opony z itemu
	PlayerCache(playerid)(pOPumpItem)		= 0
	PlayerCache(playerid)(pOPumpTime)		= 0
	
	// Nowe/me nad g≥owπ
	//PlayerCache(playerid)(pMeTime)			= 0
	
	PlayerCache(playerid)(pOselLimit)		= 0

	PlayerCache(playerid)(pGangZoneShowing) = false
	
	PlayerCache(playerid)(pCarMusic)		= 0
	
	PlayerCache(playerid)(pTagging)			= 0
	PlayerCache(playerid)(pTaggingFont)		= 0
	PlayerCache(playerid)(pTaggingSize)		= 0
	
	PlayerCache(playerid)(pPDMenu)			= 0
	PlayerCache(playerid)(pPDSuspect)		= 0
	
	PlayerCache(playerid)(pLogTime)			= 0
	
	PlayerCache(playerid)(pFlood)			= 0
	
	PlayerCache(playerid)(pDialog)			= -1
	
	PlayerCache(playerid)(pAdminMode)		= -1
	
	PlayerCache(playerid)(pLastWoodHit)		= 0
	
	PlayerCache(playerid)(pKillCount)		= 0
	
	PlayerCache(playerid)(pWeaponWarning)	= 0
	PlayerCache(playerid)(pWeaponCheckFreeze)	= false
	
	PlayerCache(playerid)(pAmmoWarning)		= 0
	
	PlayerCache(playerid)(pWiretap)			= 0

	PlayerCache(playerid)(pCasinoGameType)	= -1
	PlayerCache(playerid)(pCasinoGameID)	= -1

	PlayerCache(playerid)(pLSPadItemID)		= -1

	PlayerCache(playerid)(pShowingZones)	= false
	
	LSPad_MenuBool(playerid) = false
	LSPad_MusicStation(playerid) = -1
	LSPad_ReopenAnn(playerid) = 0
	LSPad_ReopenSett(playerid) = 0
	
	PlayerCache(playerid)(pTrucking) = false
	PlayerCache(playerid)(pTrackID) = -1
	PlayerCache(playerid)(pPackingPhase) = 0
	PlayerCache(playerid)(pPackingTime) = 0
	
	PlayerCache(playerid)(pSurfID) = -1
	PlayerCache(playerid)(pDive) = false

	PlayerCache(playerid)(pBusinessCard) = -1
	
	PlayerCache(playerid)(pLoginEx) = 10
	PlayerCache(playerid)(pReconnect) = false
	
	PlayerCache(playerid)(pItemPage) = 0
	PlayerCache(playerid)(pInterface) = 0
	PlayerCache(playerid)(pUseGUI) = false
	
	PlayerCache(playerid)(pHireTime)   = 0
	PlayerCache(playerid)(pHireGroup)   = INVALID_GROUP_ID
	
	PlayerCache(playerid)(pBombTime) = 0
	PlayerCache(playerid)(pBombID) = -1
	PlayerCache(playerid)(pBombFound) = 0
	
	PlayerCache(playerid)(pCurrentZone) = -1
	PlayerCache(playerid)(pZoneTicks) = 0
	
	PlayerCache(playerid)(pJourneyID) = INVALID_VEHICLE_ID
	
	PlayerCache(playerid)(pScouredID) = INVALID_OBJECT_ID
	PlayerCache(playerid)(pScouring) = false
	
	PlayerCache(playerid)(pCurrentGUI) = GUI_TYPE_NONE
		
	PlayerCache(playerid)(pWormed) = false
	PlayerCache(playerid)(pPicking) = 0
		
	PlayerCache(playerid)(pCourse) = false
	PlayerCache(playerid)(pCourseCP) = 0
	PlayerCache(playerid)(pCourseVeh) = INVALID_VEHICLE_ID
	PlayerCache(playerid)(pCourseMS) = 0.0
	
	PlayerCache(playerid)(pViewDoorID) = INVALID_DOOR_ID
	PlayerCache(playerid)(pViewTime) = 0
	PlayerCache(playerid)(pBuyCount) = 0
	
	PlayerCache(playerid)(pBandaged) = INVALID_PLAYER_ID
	PlayerCache(playerid)(pBandageTime) = 0
	
	PlayerCache(playerid)(pStation) = 0
	PlayerCache(playerid)(pStationLive) = false
	
	strdel(PlayerCache(playerid)(pCaptcha), 0, 16)
	strdel(PlayerCache(playerid)(pSendingCaptcha), 0, 128)
	
	PlayerCache(playerid)(pOfferedUID) = 0
	PlayerCache(playerid)(pGod) = false
	
	PlayerCache(playerid)(pDrugDealing) = false
	PlayerCache(playerid)(pCorner) = -1
	PlayerCache(playerid)(pSelling) = false
	
	// Namierzanie telefonu
	PlayerCache(playerid)(pSearching) = -1
	PlayerCache(playerid)(pSearchTime) = 0
	
	PlayerCache(playerid)(pFPS) = false
	
	PlayerCache(playerid)(pDailyDrugs) = 0
	
	PlayerCache(playerid)(pSparing) = INVALID_PLAYER_ID
	
	PlayerCache(playerid)(pPhoneAction) = 0
	
	PlayerCache(playerid)(pTalkedNPC) = INVALID_PLAYER_ID
	PlayerCache(playerid)(pTalkedPhase) = 0
	
	PlayerCache(playerid)(pCarsTP) = 0
	
	PlayerCache(playerid)(pBusinessShow) = false
	
	PlayerCache(playerid)(pFocusedID) = INVALID_PLAYER_ID
	
	PlayerCache(playerid)(pLauncherLogged) = false
	
	PlayerCache(playerid)(pPhoneMuted) = false
	
	PlayerCache(playerid)(pCarryBox) = BOX_NONE
	PlayerCache(playerid)(pCarryTries) = 0
	PlayerCache(playerid)(pCarryBoxPhase) = BOX_PHASE_NONE
	
	PlayerCache(playerid)(pVerificated) = false
	
	PlayerCache(playerid)(pArmorDisplay) = false
	
	PlayerCache(playerid)(pCorpID) = -1
	PlayerCache(playerid)(pCorpType) = CORP_TYPE_NONE
	
	PlayerCache(playerid)(pCeleb) = false
		
	PlayerCache(playerid)(pFueling) = false
	
	PlayerCache(playerid)(pCookID) = -1
	
	PlayerCache(playerid)(pPrisonWork) = 0
	PlayerCache(playerid)(pWorkingNow) = 0
	PlayerCache(playerid)(pWorkingPhase) = 0
	PlayerCache(playerid)(pWorkingRepeat) = 0
	PlayerCache(playerid)(pWorkingTimeLeft) = 0
	PlayerCache(playerid)(pWorkRepeat) = 0

	for(i = 0 i ( 10 i++)
	(
		PlayerDamageCache(playerid)(i) = false
	)
	
	// Chowanie ikonek dla potomnych
	for (i = 0 i (= CountDynamicMapIcons() i++)
 	(
 		if(IsValidDynamicMapIcon(i))
 		(
	  		if(Streamer_IsInArrayData(STREAMER_TYPE_MAP_ICON, i, E_STREAMER_PLAYER_ID, playerid))
			(
				DestroyDynamicMapIcon(i)
	   		)
		)
	)

	for(i = 0 i ( 3 i++) (	
		WeaponCache(playerid)(i)(pEquipped) = false
		WeaponCache(playerid)(i)(pShot) = false
		
		WeaponCache(playerid)(i)(pWeaponUID) = 0
		WeaponCache(playerid)(i)(pWeaponID) = 0
		WeaponCache(playerid)(i)(pWeaponAmmo) = 0
		WeaponCache(playerid)(i)(pLastAmmo) = 0
		WeaponCache(playerid)(i)(pShot) = false
	)
	
	// WyczyúÊ sloty grup
	for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
	(
		PlayerGroup(playerid)(slot)(gUID) 			= 0
		PlayerGroup(playerid)(slot)(gID) 			= 0

		PlayerGroup(playerid)(slot)(gPerm)			= 0

		PlayerGroup(playerid)(slot)(gPayment)		= 0
		PlayerGroup(playerid)(slot)(gSkin)			= 0
		PlayerGroup(playerid)(slot)(gLastPayment)	= 0
		PlayerGroup(playerid)(slot)(gTodayDuty) 	= 0
		
	)

	Offer(playerid)(oCustomerID) 			= INVALID_PLAYER_ID
	Offer(playerid)(oType) 					= 0
	Offer(playerid)(oValue) 				= 0

	Offer(playerid)(oPrice) 				= 0
	Offer(playerid)(oPayType)			   = PAYTYPE_NONE
	
	BuyProduct(playerid)(pProductUID) = 		0
	BuyProduct(playerid)(pProductPrice) =		0
	
	if(!switching) (
		Logged(playerid) 						= false
		Spawned(playerid) 						= false

		Preloaded(playerid)					 = 0
	)

	OnPlayerSave(playerid)				  = 0

	MainPlayerTable(playerid) 				= 0
	SecondPlayerTable(playerid) 			= 0
	strdel(MainPlayerStringTable(playerid), 0, 512)

	PlayerHelpStep(playerid)				= 0

	Checkpoint(playerid) 					= 0
	ChangePickup(playerid) 					= -1

	PlayerCache(playerid)(pManageItem) 		= 0
	PlayerCache(playerid)(pPlayerIDOffer)		= INVALID_PLAYER_ID

	ChangingRank(playerid) 					= 0

	ResetPlayerWeapons(playerid)
	SetPlayerColor(playerid, COLOR_BLACK)

	for (i = 0 i ( MAX_PLAYERS i++)	PlayerCache(playerid)(pPlayerIgnored)(i) = false
)

CheckBans(playerid)
(
	data(256), IP(16), bool:banned = false,
		ban_type, ban_reason(64), ban_ownergid, ban_time

	GetPlayerIp(playerid, IP, sizeof(IP))

	mysql_query_format(SELECT ban_type, ban_reason, ban_ownergid, ban_time FROM hrp_bans WHERE ban_ip = %s ORDER BY hrp_bans.ban_type DESC, IP)
	mysql_store_result()

	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ds(64)dd, ban_type, ban_reason, ban_ownergid, ban_time)

		if(ban_type == 1)
		(
			if(ban_time != 0 && ban_time ( gettime()) continue
			banned = true
		)
		else if(ban_type == 2 && ban_ownergid == PlayerCache(playerid)(pGID))
		(
			banned = false
			break
		)
	)

	mysql_free_result()

	if (banned == false)
	(
		mysql_query_format(SELECT punish_type, punish_reason, punish_owneruid, punish_end, char_gid FROM hrp_punishlogs punish INNER JOIN hrp_characters chars ON (punish.punish_owneruid = chars.char_uid) WHERE punish_type IN (3, 4) AND char_gid = %d, PlayerCache(playerid)(pGID))
		mysql_store_result()

		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)ds(64)dd, ban_type, ban_reason, ban_ownergid, ban_time)

			if(ban_time == 0 || ban_time ) gettime())
			(
				banned = true
				//printf((banCRT) Wykryto bana GID %d, czas %d (obecnie: %d), IP: %s, PlayerCache(playerid)(pGID), ban_time, gettime(), IP)
				break
			)
		)

		mysql_free_result()
	)

	if(banned)
	(
		string(128)
		format(string, sizeof(string), Zosta≥es zbanowany.\nTwÛj adres IP: %s\nPowÛd: %s\nApeluj na: %s, IP, ban_reason, WEB_URL)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		Kick(playerid)
		return 1
	)
	return 1
)

stock getGroupDutyCount(group_type)
(
	duty_count
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pGroupDuty))
			(
				group_id = GetPlayerDutyGroupID(i)
				if(GroupData(group_id)(gType) == group_type)
				(
					duty_count ++
				)
			)
		)
	)
	return duty_count
)

stock isNumeric(string1())
(
	length=strlen(string1)
	if (length==0) return false
	for (i = 0 i ( length i++)
	(
		if ((string1(i) ) 9 || string1(i) ( 0 && string1(i)!=- && string1(i)!=+) // Not a number,+ or -
             || (string1(i)==- && i!=0)                                             // A - but not at first.
             || (string1(i)==+ && i!=0)                                             // A + but not at first.
         ) return false
    )
	if (length==1 && (string1(0)==- || string1(0)==+)) return false
	return true
)

public ChangeSwitchingCamera(playerid, stage)
(
	if(stage == STAGE_CAM01)
	(
		TogglePlayerControllable(playerid, 0)

		TextDrawShowForPlayer(playerid, TextDrawSwitching)
		PlayerCache(playerid)(pSwitchingStage) = STAGE_CAM02
		//SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ), CAMERA_MOVE)
		InterpolateCameraPos(playerid, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ), PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ) + 10, 1000, CAMERA_MOVE)
		InterpolateCameraLookAt(playerid, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ), PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ), 1000, CAMERA_MOVE)
		PlayerPlaySound(playerid, 1132, 0.0, 0.0, 0.0)
		printf(cam01 1: %f, 2: %f, 3: %f, 4: %f, 5: %f, 6: %f, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ), PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ) + 10)
		//SetPlayerDrunkLevel(playerid, 2100)
		SetTimerEx(ChangeSwitchingCamera, 1200, 0, dd, playerid, STAGE_CAM02)
		return 1
	)
	if(stage == STAGE_CAM02)
	(
		SetPlayerVirtualWorld(playerid, 0)
		SetPlayerInterior(playerid, 0)

		Float:CamPosX, Float:CamPosY, Float:CamPosZ
		//GetPlayerCameraPos(playerid, CamPosX, CamPosY, CamPosZ)
		CamPosX = PlayerCache(playerid)(pSwitchingX)
		CamPosY = PlayerCache(playerid)(pSwitchingY)
		CamPosZ = PlayerCache(playerid)(pSwitchingZ) + 10

		//SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ), CAMERA_MOVE)
		InterpolateCameraPos(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ) + 40, 1000, CAMERA_MOVE)
		InterpolateCameraLookAt(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ), 1000, CAMERA_MOVE)
		PlayerPlaySound(playerid, 1132, 0.0, 0.0, 0.0)
		printf(cam02 1: %f, 2: %f, 3: %f, 4: %f, 5: %f, 6: %f, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ) + 40)
		//SetPlayerDrunkLevel(playerid, 2100)
		SetTimerEx(ChangeSwitchingCamera, 1200, 0, dd, playerid, STAGE_CAM03)
		return 1
	)
	if(stage == STAGE_CAM03)
	(
		//TogglePlayerSpectating(playerid, 1)
		Float:CamPosX, Float:CamPosY, Float:CamPosZ
		//GetPlayerCameraPos(playerid, CamPosX, CamPosY, CamPosZ)
		CamPosX = PlayerCache(playerid)(pSwitchingX)
		CamPosY = PlayerCache(playerid)(pSwitchingY)
		CamPosZ = PlayerCache(playerid)(pSwitchingZ) + 50

		//SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ), CAMERA_MOVE)
		InterpolateCameraPos(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ) + 150, 1000, CAMERA_MOVE)
		InterpolateCameraLookAt(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ), 1000, CAMERA_MOVE)
		PlayerPlaySound(playerid, 1132, 0.0, 0.0, 0.0)
		//SetTimerEx(ChangeSwitchingCamera, 1300, 0, dd, playerid, STAGE_CAM11)
		charuid = MainPlayerTable(playerid)
		printf(cam03 1: %f, 2: %f, 3: %f, 4: %f, 5: %f, 6: %f, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingX), PlayerCache(playerid)(pSwitchingY), PlayerCache(playerid)(pSwitchingZ) + 150)
		//SetPlayerDrunkLevel(playerid, 2100)
		SetTimerEx(OnPlayerSwitch, 1200, 0, dd, playerid, charuid)
		return 1
	)
	if(stage == STAGE_REAJUST_TILT)
	(
		//SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ) + 200, 100, CAMERA_MOVE)
		SetTimerEx(ChangeSwitchingCamera, 2000, 0, dd, playerid, STAGE_CAM11)
	)
	if(stage == STAGE_CAM11)
	(
		//TogglePlayerSpectating(playerid, 1)
		Float:CamPosX, Float:CamPosY, Float:CamPosZ
		//GetPlayerCameraPos(playerid, CamPosX, CamPosY, CamPosZ)
		CamPosX = PlayerCache(playerid)(pSwitchingX)
		CamPosY = PlayerCache(playerid)(pSwitchingY)
		CamPosZ = PlayerCache(playerid)(pSwitchingZ) + 150

		//SetPlayerCameraPos(playerid, CamPosX, CamPosY, CamPosZ)
		//SetPlayerCameraLookAt(playerid, CamPosX, CamPosY, CamPosZ - 200)

		InterpolateCameraPos(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ) + 150, 5000, CAMERA_MOVE)
		InterpolateCameraLookAt(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ), 5000, CAMERA_MOVE)
		printf(cam11 1: %f, 2: %f, 3: %f, 4: %f, 5: %f, 6: %f, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ) + 150)
		//SetPlayerDrunkLevel(playerid, 2100)
		SetTimerEx(ChangeSwitchingCamera, 5200, 0, dd, playerid, STAGE_CAM12)
		return 1
	)
	if(stage == STAGE_CAM12)
	(
		//TogglePlayerSpectating(playerid, 1)
		Float:CamPosX, Float:CamPosY, Float:CamPosZ
		//GetPlayerCameraPos(playerid, CamPosX, CamPosY, CamPosZ)
		CamPosX = PlayerCache(playerid)(pSwitchingDX)
		CamPosY = PlayerCache(playerid)(pSwitchingDY)
		CamPosZ = PlayerCache(playerid)(pSwitchingDZ) + 150

		//SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ), CAMERA_MOVE)
		InterpolateCameraPos(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ) + 80, 1000, CAMERA_MOVE)
		InterpolateCameraLookAt(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ), 1000, CAMERA_MOVE)
		PlayerPlaySound(playerid, 1132, 0.0, 0.0, 0.0)
		printf(cam12 1: %f, 2: %f, 3: %f, 4: %f, 5: %f, 6: %f, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ) + 80)
		//SetPlayerDrunkLevel(playerid, 2100)
		SetTimerEx(ChangeSwitchingCamera, 1200, 0, dd, playerid, STAGE_CAM13)
		return 1
	)
	if(stage == STAGE_CAM13)
	(
		Float:CamPosX, Float:CamPosY, Float:CamPosZ
		//GetPlayerCameraPos(playerid, CamPosX, CamPosY, CamPosZ)
		CamPosX = PlayerCache(playerid)(pSwitchingDX)
		CamPosY = PlayerCache(playerid)(pSwitchingDY)
		CamPosZ = PlayerCache(playerid)(pSwitchingDZ) + 80

		//SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ), CAMERA_MOVE)
		InterpolateCameraPos(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ) + 25, 1000, CAMERA_MOVE)
		InterpolateCameraLookAt(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ), 1000, CAMERA_MOVE)
		PlayerPlaySound(playerid, 1132, 0.0, 0.0, 0.0)
		printf(cam13 1: %f, 2: %f, 3: %f, 4: %f, 5: %f, 6: %f, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ) + 25)
		//SetPlayerDrunkLevel(playerid, 2100)
		SetTimerEx(ChangeSwitchingCamera, 1200, 0, dd, playerid, STAGE_CAM14)
		return 1
	)
	if(stage == STAGE_CAM14)
	(
		Float:CamPosX, Float:CamPosY, Float:CamPosZ
		//GetPlayerCameraPos(playerid, CamPosX, CamPosY, CamPosZ)
		CamPosX = PlayerCache(playerid)(pSwitchingDX)
		CamPosY = PlayerCache(playerid)(pSwitchingDY)
		CamPosZ = PlayerCache(playerid)(pSwitchingDZ) + 25

		//SetPlayerCameraLookAt(playerid, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ), CAMERA_MOVE)
		InterpolateCameraPos(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ) + 5, 1000, CAMERA_MOVE)
		InterpolateCameraLookAt(playerid, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ), 1000, CAMERA_MOVE)
		PlayerPlaySound(playerid, 1132, 0.0, 0.0, 0.0)
		printf(cam14 1: %f, 2: %f, 3: %f, 4: %f, 5: %f, 6: %f, CamPosX, CamPosY, CamPosZ, PlayerCache(playerid)(pSwitchingDX), PlayerCache(playerid)(pSwitchingDY), PlayerCache(playerid)(pSwitchingDZ) + 5)
		//SetPlayerDrunkLevel(playerid, 2100)
		SetTimerEx(ChangeSwitchingCamera, 1200, 0, dd, playerid, STAGE_SPAWN)
		return 1
	)
	if(stage == STAGE_SPAWN)
	(
		TextDrawHideForPlayer(playerid, TextDrawSwitching)
		TogglePlayerSpectating(playerid, 0)
		//SetPlayerDrunkLevel(playerid, 0)
		MainPlayerTable(playerid) = 0
		PlayerCache(playerid)(pSwitching) = false
		SpawnPlayer(playerid)

		//SetPlayerSpawn(playerid)
		return 1
	)
	
	return 1
)
	

stock LoadPickups()
(
	JobPickup = CreatePickup(1239, 2, 1465.7085, -1748.9308, 15.4453, 0)
	//PressPickup = CreatePickup(1239, 2, 1677.1243,-1624.3998,14.2227, 0)
	//MarihuanaGangPickup = CreatePickup(1279, 2, 2178.4683,-998.0547,62.9517, 0)
	//AmpGangPickup = CreatePickup(1279, 2, 2172.8367,-998.4705,62.9683, 0)
	//MetaampGangPickup = CreatePickup(1279, 2, 2167.3904,-997.6728,62.9643, 0)
	

	return 1
)

stock EndCall(callid)
(
	eccaller = Call(callid)(caller)
	eccalled = Call(callid)(called)

	if(eccaller != INVALID_PLAYER_ID && IsPlayerConnected(eccaller))
	(
		if(GetPlayerSpecialAction(eccaller) == SPECIAL_ACTION_USECELLPHONE)
		(
			SetPlayerSpecialAction(eccaller, SPECIAL_ACTION_STOPUSECELLPHONE)
		)
		if(IsPlayerAttachedObjectSlotUsed(eccaller, SLOT_PHONE))
		(
			RemovePlayerAttachedObject(eccaller, SLOT_PHONE)
		)

		if(PlayerCache(eccalled)(pCall) != callid)
			SendClientMessage(eccaller, COLOR_YELLOW, Po≥πczenie zosta≥o przerwane.)
		else
			SendClientMessage(eccaller, COLOR_YELLOW, Rozmowa zosta≥a zakoÒczona.)
	)
	if(eccalled != INVALID_PLAYER_ID && IsPlayerConnected(eccalled))
	(
		if(GetPlayerSpecialAction(eccalled) == SPECIAL_ACTION_USECELLPHONE)
		(
			SetPlayerSpecialAction(eccalled, SPECIAL_ACTION_STOPUSECELLPHONE)
		)
		if(IsPlayerAttachedObjectSlotUsed(eccalled, SLOT_PHONE))
		(
			RemovePlayerAttachedObject(eccalled, SLOT_PHONE)
		)

		if(PlayerCache(eccalled)(pCall) != callid)
			SendClientMessage(eccalled, COLOR_YELLOW, Po≥πczenie zosta≥o przerwane.)
		else
			SendClientMessage(eccalled, COLOR_YELLOW, Rozmowa zosta≥a zakoÒczona.)
	)

	if(Call(callid)(callerDevice) == DEVICE_BOX)
		if(Call(callid)(callerDevID) != 0)
			Phones(Call(callid)(callerDevID))(phoneBusy) = false

	if(Call(callid)(calledDevice) == DEVICE_BOX)
		if(Call(callid)(calledDevID) != 0)
			Phones(Call(callid)(calledDevID))(phoneBusy) = false
			
	if(Call(callid)(callerDevice) == DEVICE_HOME)
		if(Call(callid)(callerDevID) != 0)
			HomePhones(Call(callid)(callerDevID))(hphoneBusy) = false
			
	if(Call(callid)(calledDevice) == DEVICE_HOME)
		if(Call(callid)(calledDevID) != 0)
			HomePhones(Call(callid)(calledDevID))(hphoneBusy) = false
			
			
	PlayerCache(eccaller)(pCall) = -1
	PlayerCache(eccalled)(pCall) = -1

	Call(callid)(caller) = INVALID_PLAYER_ID
	Call(callid)(called) = INVALID_PLAYER_ID
	Call(callid)(callerNumber) = 0
	Call(callid)(calledNumber) = 0
	Call(callid)(callerDevice) = 0
	Call(callid)(calledDevice) = 0
	Call(callid)(callerDevID) = 0
	Call(callid)(calledDevID) = 0
	Call(callid)(convo) = false			//blint kurwa 2 tu false bylo
	Call(callid)(callTime) = 0

	Itter_Remove(Calls, callid)
	return 1
)


stock LoadTextDraws()
(
	year, month, day, hour, minute, second, string(256)

	getdate(year, month, day)
	gettime(hour, minute, second)
	format(string, sizeof(string), ~b~~h~LS-RP ~w~: ~g~~h~%02d.%02d.%02d, day, month, year)	
	
	TextDrawServerLogo = TextDrawCreate(469.000000, 2.000000, string)
	TextDrawBackgroundColor(TextDrawServerLogo, 255)
	TextDrawFont(TextDrawServerLogo, 3)
	TextDrawLetterSize(TextDrawServerLogo, 0.470000, 1.100000)
	TextDrawColor(TextDrawServerLogo, -1)
	TextDrawSetOutline(TextDrawServerLogo, 1)
	TextDrawSetProportional(TextDrawServerLogo, 1)
	
	TextDrawAdmin = TextDrawCreate(143.000000, 369.000000, ADMIN ON)
	TextDrawBackgroundColor(TextDrawAdmin, 255)
	TextDrawFont(TextDrawAdmin, 1)
	TextDrawLetterSize(TextDrawAdmin, 0.500000, 1.000000)
	TextDrawColor(TextDrawAdmin, -16776961)
	TextDrawSetOutline(TextDrawAdmin, 0)
	TextDrawSetProportional(TextDrawAdmin, 1)
	TextDrawSetShadow(TextDrawAdmin, 1)
	TextDrawUseBox(TextDrawAdmin, 1)
	TextDrawBoxColor(TextDrawAdmin, 572662218)
	TextDrawTextSize(TextDrawAdmin, 232.000000, 0.000000)
	
	TextDrawOfferBack = TextDrawCreate(489.000000, 319.000000, _)
	TextDrawBackgroundColor(TextDrawOfferBack, 255)
	TextDrawFont(TextDrawOfferBack, 1)
	TextDrawLetterSize(TextDrawOfferBack, 5.199995, 11.000000)
	TextDrawColor(TextDrawOfferBack, -1)
	TextDrawSetOutline(TextDrawOfferBack, 0)
	TextDrawSetProportional(TextDrawOfferBack, 1)
	TextDrawSetShadow(TextDrawOfferBack, 1)
	TextDrawUseBox(TextDrawOfferBack, 1)
	TextDrawBoxColor(TextDrawOfferBack, 68)
	TextDrawTextSize(TextDrawOfferBack, 177.000000, 200.000000)
	
	TextDrawFuelBack = TextDrawCreate(489.000000, 319.000000, _)
	TextDrawBackgroundColor(TextDrawFuelBack, 255)
	TextDrawFont(TextDrawFuelBack, 1)
	TextDrawLetterSize(TextDrawFuelBack, 5.199995, 11.000000)
	TextDrawColor(TextDrawFuelBack, -1)
	TextDrawSetOutline(TextDrawFuelBack, 0)
	TextDrawSetProportional(TextDrawFuelBack, 1)
	TextDrawSetShadow(TextDrawFuelBack, 1)
	TextDrawUseBox(TextDrawFuelBack, 1)
	TextDrawBoxColor(TextDrawFuelBack, 68)
	TextDrawTextSize(TextDrawFuelBack, 177.000000, 200.000000)
	
	TextDrawAudioError = TextDrawCreate(520.000000, 423.500000, Brak klienta audio)
	TextDrawBackgroundColor(TextDrawAudioError, -16776961)
	TextDrawFont(TextDrawAudioError, 3)
	TextDrawLetterSize(TextDrawAudioError, 0.350000, 0.850000)
	TextDrawColor(TextDrawAudioError, -1)
	TextDrawSetOutline(TextDrawAudioError, 1)
	TextDrawSetProportional(TextDrawAudioError, 1)
	
	TextDrawTemperature = TextDrawCreate(5.000000, 408.500000, 0 *C)
	TextDrawBackgroundColor(TextDrawTemperature, 866792362)
	TextDrawFont(TextDrawTemperature, 3)
	TextDrawLetterSize(TextDrawTemperature, 0.350000, 0.850000)
	TextDrawColor(TextDrawTemperature, -1)
	TextDrawSetOutline(TextDrawTemperature, 1)
	TextDrawSetProportional(TextDrawTemperature, 1)
	TextDrawSetSelectable(TextDrawTemperature, 1)

	TextDrawPremium = TextDrawCreate(5.000000, 423.500000, Gracz premium)
	TextDrawBackgroundColor(TextDrawPremium, 866792362)
	TextDrawFont(TextDrawPremium, 3)
	TextDrawLetterSize(TextDrawPremium, 0.350000, 0.850000)
	TextDrawColor(TextDrawPremium, -1)
	TextDrawSetOutline(TextDrawPremium, 1)
	TextDrawSetProportional(TextDrawPremium, 1)
	TextDrawSetSelectable(TextDrawPremium, 1)
	
	TextDrawAdminLog = TextDrawCreate(108.000000, 423.000000, _)
	TextDrawBackgroundColor(TextDrawAdminLog, 255)
	TextDrawFont(TextDrawAdminLog, 1)
	TextDrawLetterSize(TextDrawAdminLog, 0.200000, 0.899999)
	TextDrawColor(TextDrawAdminLog, -1)
	TextDrawSetOutline(TextDrawAdminLog, 1)
	TextDrawSetProportional(TextDrawAdminLog, 1)
	
	TextDrawPunishInfo = TextDrawCreate(14.000000, 286.000000, _)
 	TextDrawBackgroundColor(TextDrawPunishInfo, 255)
 	TextDrawFont(TextDrawPunishInfo, 1)
 	TextDrawLetterSize(TextDrawPunishInfo, 0.300000, 1.200000)
 	TextDrawColor(TextDrawPunishInfo, -1)
 	TextDrawSetOutline(TextDrawPunishInfo, 1)
 	TextDrawSetProportional(TextDrawPunishInfo, 1)
 	
	TextDrawEditorBack = TextDrawCreate(650.000000, 310.000000, _)
	TextDrawBackgroundColor(TextDrawEditorBack, 255)
	TextDrawFont(TextDrawEditorBack, 1)
	TextDrawLetterSize(TextDrawEditorBack, 0.000000, 15.000000)
	TextDrawColor(TextDrawEditorBack, -1)
	TextDrawSetOutline(TextDrawEditorBack, 0)
	TextDrawSetProportional(TextDrawEditorBack, 1)
	TextDrawSetShadow(TextDrawEditorBack, 1)
	TextDrawUseBox(TextDrawEditorBack, 1)
	TextDrawBoxColor(TextDrawEditorBack, 68)
	TextDrawTextSize(TextDrawEditorBack, -11.000000, 0.000000)
	
/*	
	TextDrawAKill = TextDrawCreate(506.000000, 116.000000, Zabij!)
	TextDrawBackgroundColor(TextDrawAKill, 255)
	TextDrawFont(TextDrawAKill, 1)
	TextDrawLetterSize(TextDrawAKill, 0.370000, 1.000000)
	TextDrawColor(TextDrawAKill, -65281)
	TextDrawSetOutline(TextDrawAKill, 0)
	TextDrawSetProportional(TextDrawAKill, 1)
	TextDrawSetShadow(TextDrawAKill, 1)
	TextDrawUseBox(TextDrawAKill, 1)
	TextDrawBoxColor(TextDrawAKill, 1032256767)
	//TextDrawTextSize(TextDrawAKill, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawAKill, 1)

	TextDrawAKick = TextDrawCreate(506.000000, 132.000000, Kick - Relog) // git
	TextDrawBackgroundColor(TextDrawAKick, 255) // git
	TextDrawFont(TextDrawAKick, 1) // git
	TextDrawLetterSize(TextDrawAKick, 0.360000, 1.000000) // git
	TextDrawColor(TextDrawAKick, -65281) // git
	TextDrawSetOutline(TextDrawAKick, 0) // git
	TextDrawSetProportional(TextDrawAKick, 1) // git
	TextDrawSetShadow(TextDrawAKick, 1) // git
	TextDrawUseBox(TextDrawAKick, 1) // git
	TextDrawBoxColor(TextDrawAKick, 1032256767) // git
	//TextDrawTextSize(TextDrawAKick, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawAKick, 1) // git

	TextDrawABan = TextDrawCreate(506.000000, 148.000000, Ban - Cheat)
	TextDrawBackgroundColor(TextDrawABan, 255)
	TextDrawFont(TextDrawABan, 1)
	TextDrawLetterSize(TextDrawABan, 0.360000, 1.000000)
	TextDrawColor(TextDrawABan, -16776961)
	TextDrawSetOutline(TextDrawABan, 1)
	TextDrawSetProportional(TextDrawABan, 1)
	TextDrawUseBox(TextDrawABan, 1)
	TextDrawBoxColor(TextDrawABan, 1032256767)
	//TextDrawTextSize(TextDrawABan, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawABan, 1)

	TextDrawARun = TextDrawCreate(506.000000, 164.000000, Blokada biegania)
	TextDrawBackgroundColor(TextDrawARun, 255)
	TextDrawFont(TextDrawARun, 1)
	TextDrawLetterSize(TextDrawARun, 0.330000, 1.000000)
	TextDrawColor(TextDrawARun, -65281)
	TextDrawSetOutline(TextDrawARun, 0)
	TextDrawSetProportional(TextDrawARun, 1)
	TextDrawSetShadow(TextDrawARun, 1)
	TextDrawUseBox(TextDrawARun, 1)
	TextDrawBoxColor(TextDrawARun, 1032256767)
	//TextDrawTextSize(TextDrawARun, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawARun, 1)

	TextDrawAVeh = TextDrawCreate(506.000000, 180.000000, Blokada prowadzenia)
	TextDrawBackgroundColor(TextDrawAVeh, 255)
	TextDrawFont(TextDrawAVeh, 1)
	TextDrawLetterSize(TextDrawAVeh, 0.270000, 1.000000)
	TextDrawColor(TextDrawAVeh, -65281)
	TextDrawSetOutline(TextDrawAVeh, 0)
	TextDrawSetProportional(TextDrawAVeh, 1)
	TextDrawSetShadow(TextDrawAVeh, 1)
	TextDrawUseBox(TextDrawAVeh, 1)
	TextDrawBoxColor(TextDrawAVeh, 1032256767)
	//TextDrawTextSize(TextDrawAVeh, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawAVeh, 1)

	TextDrawAFreeze = TextDrawCreate(506.000000, 196.000000, Freeze)
	TextDrawBackgroundColor(TextDrawAFreeze, 255)
	TextDrawFont(TextDrawAFreeze, 1)
	TextDrawLetterSize(TextDrawAFreeze, 0.370000, 1.000000)
	TextDrawColor(TextDrawAFreeze, -65281)
	TextDrawSetOutline(TextDrawAFreeze, 0)
	TextDrawSetProportional(TextDrawAFreeze, 1)
	TextDrawSetShadow(TextDrawAFreeze, 1)
	TextDrawUseBox(TextDrawAFreeze, 1)
	TextDrawBoxColor(TextDrawAFreeze, 1032256767)
	//TextDrawTextSize(TextDrawAFreeze, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawAFreeze, 1)

	TextDrawAGethere = TextDrawCreate(506.000000, 212.000000, Gethere)
	TextDrawBackgroundColor(TextDrawAGethere, 255)
	TextDrawFont(TextDrawAGethere, 1)
	TextDrawLetterSize(TextDrawAGethere, 0.370000, 1.000000)
	TextDrawColor(TextDrawAGethere, -65281)
	TextDrawSetOutline(TextDrawAGethere, 0)
	TextDrawSetProportional(TextDrawAGethere, 1)
	TextDrawSetShadow(TextDrawAGethere, 1)
	TextDrawUseBox(TextDrawAGethere, 1)
	TextDrawBoxColor(TextDrawAGethere, 1032256767)
	//TextDrawTextSize(TextDrawAGethere, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawAGethere, 1)

	TextDrawAGoto = TextDrawCreate(506.000000, 228.000000, Goto)
	TextDrawBackgroundColor(TextDrawAGoto, 255)
	TextDrawFont(TextDrawAGoto, 1)
	TextDrawLetterSize(TextDrawAGoto, 0.370000, 1.000000)
	TextDrawColor(TextDrawAGoto, -65281)
	TextDrawSetOutline(TextDrawAGoto, 0)
	TextDrawSetProportional(TextDrawAGoto, 1)
	TextDrawSetShadow(TextDrawAGoto, 1)
	TextDrawUseBox(TextDrawAGoto, 1)
	TextDrawBoxColor(TextDrawAGoto, 1032256767)
	//TextDrawTextSize(TextDrawAGoto, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawAGoto, 1)

	TextDrawASlap = TextDrawCreate(506.000000, 244.000000, Slap)
	TextDrawBackgroundColor(TextDrawASlap, 255)
	TextDrawFont(TextDrawASlap, 1)
	TextDrawLetterSize(TextDrawASlap, 0.370000, 1.000000)
	TextDrawColor(TextDrawASlap, -65281)
	TextDrawSetOutline(TextDrawASlap, 0)
	TextDrawSetProportional(TextDrawASlap, 1)
	TextDrawSetShadow(TextDrawASlap, 1)
	TextDrawUseBox(TextDrawASlap, 1)
	TextDrawBoxColor(TextDrawASlap, 1032256767)
	//TextDrawTextSize(TextDrawASlap, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawASlap, 1)

	TextDrawARespawn = TextDrawCreate(506.000000, 260.000000, Respawn)
	TextDrawBackgroundColor(TextDrawARespawn, 255)
	TextDrawFont(TextDrawARespawn, 1)
	TextDrawLetterSize(TextDrawARespawn, 0.370000, 1.000000)
	TextDrawColor(TextDrawARespawn, -65281)
	TextDrawSetOutline(TextDrawARespawn, 0)
	TextDrawSetProportional(TextDrawARespawn, 1)
	TextDrawSetShadow(TextDrawARespawn, 1)
	TextDrawUseBox(TextDrawARespawn, 1)
	TextDrawBoxColor(TextDrawARespawn, 1032256767)
	//TextDrawTextSize(TextDrawARespawn, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawARespawn, 1)

	TextDrawABW = TextDrawCreate(506.000000, 276.000000, Zdejmij BW + Heal)
	TextDrawBackgroundColor(TextDrawABW, 255)
	TextDrawFont(TextDrawABW, 1)
	TextDrawLetterSize(TextDrawABW, 0.310000, 1.000000)
	TextDrawColor(TextDrawABW, -65281)
	TextDrawSetOutline(TextDrawABW, 0)
	TextDrawSetProportional(TextDrawABW, 1)
	TextDrawSetShadow(TextDrawABW, 1)
	TextDrawUseBox(TextDrawABW, 1)
	TextDrawBoxColor(TextDrawABW, 1032256767)
	//TextDrawTextSize(TextDrawABW, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawABW, 1)

	TextDrawAChill = TextDrawCreate(506.000000, 292.000000, Chilluj gnoja)
	TextDrawBackgroundColor(TextDrawAChill, 255)
	TextDrawFont(TextDrawAChill, 1)
	TextDrawLetterSize(TextDrawAChill, 0.340000, 1.000000)
	TextDrawColor(TextDrawAChill, -65281)
	TextDrawSetOutline(TextDrawAChill, 0)
	TextDrawSetProportional(TextDrawAChill, 1)
	TextDrawSetShadow(TextDrawAChill, 1)
	TextDrawUseBox(TextDrawAChill, 1)
	TextDrawBoxColor(TextDrawAChill, 1032256767)
	//TextDrawTextSize(TextDrawAChill, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawAChill, 1)

	TextDrawASpec = TextDrawCreate(506.000000, 308.000000, Specuj)
	TextDrawBackgroundColor(TextDrawASpec, 255)
	TextDrawFont(TextDrawASpec, 1)
	TextDrawLetterSize(TextDrawASpec, 0.340000, 1.000000)
	TextDrawColor(TextDrawASpec, -65281)
	TextDrawSetOutline(TextDrawASpec, 0)
	TextDrawSetProportional(TextDrawASpec, 1)
	TextDrawSetShadow(TextDrawASpec, 1)
	TextDrawUseBox(TextDrawASpec, 1)
	TextDrawBoxColor(TextDrawASpec, 1032256767)
	//TextDrawTextSize(TextDrawASpec, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawASpec, 1)

	TextDrawAUlti = TextDrawCreate(506.000000, 324.000000, Ultimate)
	TextDrawBackgroundColor(TextDrawAUlti, 255)
	TextDrawFont(TextDrawAUlti, 1)
	TextDrawLetterSize(TextDrawAUlti, 0.340000, 1.000000)
	TextDrawColor(TextDrawAUlti, -65281)
	TextDrawSetOutline(TextDrawAUlti, 0)
	TextDrawSetProportional(TextDrawAUlti, 1)
	TextDrawSetShadow(TextDrawAUlti, 1)
	TextDrawUseBox(TextDrawAUlti, 1)
	TextDrawBoxColor(TextDrawAUlti, 1032256767)
	//TextDrawTextSize(TextDrawAUlti, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawAUlti, 1)

	TextDrawAExit = TextDrawCreate(506.000000, 339.000000, EXIT)
	TextDrawBackgroundColor(TextDrawAExit, 255)
	TextDrawFont(TextDrawAExit, 2)
	TextDrawLetterSize(TextDrawAExit, 0.400000, 1.000000)
	TextDrawColor(TextDrawAExit, -1)
	TextDrawSetOutline(TextDrawAExit, 1)
	TextDrawSetProportional(TextDrawAExit, 1)
	TextDrawUseBox(TextDrawAExit, 1)
	TextDrawBoxColor(TextDrawAExit, 1032256767)
	//TextDrawTextSize(TextDrawAExit, 601.000000, 0.000000)
	TextDrawSetSelectable(TextDrawAExit, 1)
*/

	DashboardBG(0) = TextDrawCreate(239.082873, 123.666664, hud:radardisc) // gÛra lewo
	TextDrawLetterSize(DashboardBG(0), 0.000000, 0.000000)
	TextDrawTextSize(DashboardBG(0), 79.180084, 97.416824)
	TextDrawAlignment(DashboardBG(0), 1)
	TextDrawColor(DashboardBG(0), -156)
	TextDrawSetShadow(DashboardBG(0), 0)
	TextDrawSetOutline(DashboardBG(0), 0)
	TextDrawFont(DashboardBG(0), 4)
	TextDrawSetProportional(DashboardBG(0), 1)

	DashboardBG(1) = TextDrawCreate(239.382873, 319.033221, hud:radardisc) // dÛ≥ lewo
	TextDrawLetterSize(DashboardBG(1), 0.000000, 0.000000)
	TextDrawTextSize(DashboardBG(1), 77.774520, -97.999885)
	TextDrawAlignment(DashboardBG(1), 1)
	TextDrawColor(DashboardBG(1), -156)
	TextDrawSetShadow(DashboardBG(1), 0)
	TextDrawSetOutline(DashboardBG(1), 0)
	TextDrawFont(DashboardBG(1), 4)

	DashboardBG(2) = TextDrawCreate(392.541339, 318.166847, hud:radardisc) // dÛ≥ prawo
	TextDrawLetterSize(DashboardBG(2), 0.000000, 0.000000)
	TextDrawTextSize(DashboardBG(2), -78.243026, -97.999839)
	TextDrawAlignment(DashboardBG(2), 1)
	TextDrawColor(DashboardBG(2), -156)
	TextDrawSetShadow(DashboardBG(2), 0)
	TextDrawSetOutline(DashboardBG(2), 0)
	TextDrawFont(DashboardBG(2), 4)

	DashboardBG(3) = TextDrawCreate(392.341339, 123.949847, hud:radardisc) // gÛra prawo
	TextDrawLetterSize(DashboardBG(3), 0.000000, 0.000000)
	TextDrawTextSize(DashboardBG(3), -74.026344, 96.250259)
	TextDrawAlignment(DashboardBG(3), 1)
	TextDrawColor(DashboardBG(3), -156)
	TextDrawSetShadow(DashboardBG(3), 0)
	TextDrawSetOutline(DashboardBG(3), 0)
	TextDrawFont(DashboardBG(3), 4)
	
	DashboardOption(0) = TextDrawCreate(317.809570, 296.666564, SPARING)
	TextDrawLetterSize(DashboardOption(0), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(0), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(0), 2)
	TextDrawColor(DashboardOption(0), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(0), 53)
	TextDrawSetOutline(DashboardOption(0), 1)
	TextDrawBackgroundColor(DashboardOption(0), 255)
	TextDrawFont(DashboardOption(0), 3)
	TextDrawSetProportional(DashboardOption(0), 1)
	TextDrawSetShadow(DashboardOption(0), 53)
	TextDrawSetSelectable(DashboardOption(0), 1)

	DashboardOption(1) = TextDrawCreate(252.285797, 249.733276, POWITANIE)
	TextDrawLetterSize(DashboardOption(1), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(1), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(1), 2)
	TextDrawColor(DashboardOption(1), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(1), 53)
	TextDrawSetOutline(DashboardOption(1), 1)
	TextDrawBackgroundColor(DashboardOption(1), 255)
	TextDrawFont(DashboardOption(1), 3)
	TextDrawSetProportional(DashboardOption(1), 1)
	TextDrawSetShadow(DashboardOption(1), 53)
	TextDrawSetSelectable(DashboardOption(1), 1)

	DashboardOption(2) = TextDrawCreate(379.142883, 250.159942, POCALUNEK)
	TextDrawLetterSize(DashboardOption(2), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(2), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(2), 2)
	TextDrawColor(DashboardOption(2), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(2), 53)
	TextDrawSetOutline(DashboardOption(2), 1)
	TextDrawBackgroundColor(DashboardOption(2), 255)
	TextDrawFont(DashboardOption(2), 3)
	TextDrawSetProportional(DashboardOption(2), 1)
	TextDrawSetShadow(DashboardOption(2), 53)
	TextDrawSetSelectable(DashboardOption(2), 1)

	DashboardOption(3) = TextDrawCreate(251.142913, 175.066650, PRZEDMIOT)
	TextDrawLetterSize(DashboardOption(3), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(3), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(3), 2)
	TextDrawColor(DashboardOption(3), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(3), 53)
	TextDrawSetOutline(DashboardOption(3), 1)
	TextDrawBackgroundColor(DashboardOption(3), 255)
	TextDrawFont(DashboardOption(3), 3)
	TextDrawSetProportional(DashboardOption(3), 1)
	TextDrawSetShadow(DashboardOption(3), 53)
	TextDrawSetSelectable(DashboardOption(3), 1)

	DashboardOption(4) = TextDrawCreate(383.714324, 175.493316, VCARD)
	TextDrawLetterSize(DashboardOption(4), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(4), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(4), 2)
	TextDrawColor(DashboardOption(4), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(4), 53)
	TextDrawSetOutline(DashboardOption(4), 1)
	TextDrawBackgroundColor(DashboardOption(4), 255)
	TextDrawFont(DashboardOption(4), 3)
	TextDrawSetProportional(DashboardOption(4), 1)
	TextDrawSetShadow(DashboardOption(4), 53)
	TextDrawSetSelectable(DashboardOption(4), 1)

	DashboardOption(5) = TextDrawCreate(318.571502, 118.320037, GOTOWKA)
	TextDrawLetterSize(DashboardOption(5), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(5), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(5), 2)
	TextDrawColor(DashboardOption(5), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(5), 53)
	TextDrawSetOutline(DashboardOption(5), 1)
	TextDrawBackgroundColor(DashboardOption(5), 255)
	TextDrawFont(DashboardOption(5), 3)
	TextDrawSetProportional(DashboardOption(5), 1)
	TextDrawSetShadow(DashboardOption(5), 53)
	TextDrawSetSelectable(DashboardOption(5), 1)
	
	DashboardOption(6) = TextDrawCreate(315.809570, 296.666564, HAMULEC RECZNY)
	TextDrawLetterSize(DashboardOption(6), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(6), 48.00000, 91.142906)
	TextDrawAlignment(DashboardOption(6), 2)
	TextDrawColor(DashboardOption(6), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(6), 53)
	TextDrawSetOutline(DashboardOption(6), 1)
	TextDrawBackgroundColor(DashboardOption(6), 255)
	TextDrawFont(DashboardOption(6), 3)
	TextDrawSetProportional(DashboardOption(6), 1)
	TextDrawSetShadow(DashboardOption(6), 53)
	TextDrawSetSelectable(DashboardOption(6), 1)

	DashboardOption(7) = TextDrawCreate(252.285797, 249.733276, SZYBA)
	TextDrawLetterSize(DashboardOption(7), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(7), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(7), 2)
	TextDrawColor(DashboardOption(7), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(7), 53)
	TextDrawSetOutline(DashboardOption(7), 1)
	TextDrawBackgroundColor(DashboardOption(7), 255)
	TextDrawFont(DashboardOption(7), 3)
	TextDrawSetProportional(DashboardOption(7), 1)
	TextDrawSetShadow(DashboardOption(7), 53)
	TextDrawSetSelectable(DashboardOption(7), 1)

	DashboardOption(8) = TextDrawCreate(379.142883, 250.159942, CB RADIO)
	TextDrawLetterSize(DashboardOption(8), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(8), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(8), 2)
	TextDrawColor(DashboardOption(8), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(8), 53)
	TextDrawSetOutline(DashboardOption(8), 1)
	TextDrawBackgroundColor(DashboardOption(8), 255)
	TextDrawFont(DashboardOption(8), 3)
	TextDrawSetProportional(DashboardOption(8), 1)
	TextDrawSetShadow(DashboardOption(8), 53)
	TextDrawSetSelectable(DashboardOption(8), 1)

	DashboardOption(9) = TextDrawCreate(251.142913, 175.066650, BAGAZNIK)
	TextDrawLetterSize(DashboardOption(9), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(9), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(9), 2)
	TextDrawColor(DashboardOption(9), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(9), 53)
	TextDrawSetOutline(DashboardOption(9), 1)
	TextDrawBackgroundColor(DashboardOption(9), 255)
	TextDrawFont(DashboardOption(9), 3)
	TextDrawSetProportional(DashboardOption(9), 1)
	TextDrawSetShadow(DashboardOption(9), 53)
	TextDrawSetSelectable(DashboardOption(9), 1)

	DashboardOption(10) = TextDrawCreate(383.714324, 175.493316, MASKA)
	TextDrawLetterSize(DashboardOption(10), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(10), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(10), 2)
	TextDrawColor(DashboardOption(10), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(10), 53)
	TextDrawSetOutline(DashboardOption(10), 1)
	TextDrawBackgroundColor(DashboardOption(10), 255)
	TextDrawFont(DashboardOption(10), 3)
	TextDrawSetProportional(DashboardOption(10), 1)
	TextDrawSetShadow(DashboardOption(10), 53)
	TextDrawSetSelectable(DashboardOption(10), 1)

	DashboardOption(11) = TextDrawCreate(318.571502, 118.320037, SILNIK)
	TextDrawLetterSize(DashboardOption(11), 0.573333, 2.568533)
	TextDrawTextSize(DashboardOption(11), 25.00000, 91.142906)
	TextDrawAlignment(DashboardOption(11), 2)
	TextDrawColor(DashboardOption(11), 0x8CC5E3FF)
	TextDrawSetShadow(DashboardOption(11), 53)
	TextDrawSetOutline(DashboardOption(11), 1)
	TextDrawBackgroundColor(DashboardOption(11), 255)
	TextDrawFont(DashboardOption(11), 3)
	TextDrawSetProportional(DashboardOption(11), 1)
	TextDrawSetShadow(DashboardOption(11), 53)
	TextDrawSetSelectable(DashboardOption(11), 1)
	
	TextDrawSwitching = TextDrawCreate(322.000000, 2.000000, _)
	TextDrawAlignment(TextDrawSwitching, 2)
	TextDrawBackgroundColor(TextDrawSwitching, 255)
	TextDrawFont(TextDrawSwitching, 1)
	TextDrawLetterSize(TextDrawSwitching, 0.500000, 50.000000)
	TextDrawColor(TextDrawSwitching, -1)
	TextDrawSetOutline(TextDrawSwitching, 0)
	TextDrawSetProportional(TextDrawSwitching, 1)
	TextDrawSetShadow(TextDrawSwitching, 1)
	TextDrawUseBox(TextDrawSwitching, 1)
	TextDrawBoxColor(TextDrawSwitching, 660350242)
	TextDrawTextSize(TextDrawSwitching, 0.000000, 649.000000)
	
	// Nowy info box
	TextDrawInfoNew = TextDrawCreate(521.000000, 331.000000, Informacja)
	TextDrawAlignment(TextDrawInfoNew, 2)
	TextDrawBackgroundColor(TextDrawInfoNew, 255)
	TextDrawFont(TextDrawInfoNew, 1)
	TextDrawLetterSize(TextDrawInfoNew, 0.280000, 1.099999)
	TextDrawColor(TextDrawInfoNew, -1)
	TextDrawSetOutline(TextDrawInfoNew, 1)
	TextDrawSetProportional(TextDrawInfoNew, 1)
	TextDrawUseBox(TextDrawInfoNew, 1)
	TextDrawBoxColor(TextDrawInfoNew, 100)
	TextDrawTextSize(TextDrawInfoNew, 0.000000, 197.000000)

	TextDrawSanNews = TextDrawCreate(2.000000, 438.000000, Radio ~)~ Aby wybrac stacje radiowa uzyj komendy /stacja.)
	TextDrawBackgroundColor(TextDrawSanNews, 255)
	TextDrawFont(TextDrawSanNews, 1)
	TextDrawLetterSize(TextDrawSanNews, 0.250000, 0.899999)
	TextDrawColor(TextDrawSanNews, -1)
	TextDrawSetOutline(TextDrawSanNews, 1)
	TextDrawSetProportional(TextDrawSanNews, 1)
	TextDrawUseBox(TextDrawSanNews, 1)
	TextDrawBoxColor(TextDrawSanNews, 68)
	TextDrawTextSize(TextDrawSanNews, 640.000000, 600.000000)
	
	InitializeLSPadTextDraws()

	// Gracze (pÍtla)
	for (i = 0 i ( MAX_PLAYERS i++)
 	(
		/*
		TextDrawCardWelcome(i) = TextDrawCreate(241.000000, 116.000000, Aktualne rozdanie)
		TextDrawBackgroundColor(TextDrawCardWelcome(i), 255)
		TextDrawFont(TextDrawCardWelcome(i), 3)
		TextDrawLetterSize(TextDrawCardWelcome(i), 0.539999, 1.899999)
		TextDrawColor(TextDrawCardWelcome(i), 16711935)
		TextDrawSetOutline(TextDrawCardWelcome(i), 0)
		TextDrawSetProportional(TextDrawCardWelcome(i), 1)
		TextDrawSetShadow(TextDrawCardWelcome(i), 1)

		TextDrawTableCardOne(i) = TextDrawCreate(259.000000, 140.000000, ld_card:cdback)
		TextDrawBackgroundColor(TextDrawTableCardOne(i), 255)
		TextDrawFont(TextDrawTableCardOne(i), 4)
		TextDrawLetterSize(TextDrawTableCardOne(i), 0.430000, 0.199999)
		TextDrawColor(TextDrawTableCardOne(i), -1)
		TextDrawSetOutline(TextDrawTableCardOne(i), 0)
		TextDrawSetProportional(TextDrawTableCardOne(i), 1)
		TextDrawSetShadow(TextDrawTableCardOne(i), 1)
		TextDrawUseBox(TextDrawTableCardOne(i), 1)
		TextDrawBoxColor(TextDrawTableCardOne(i), 255)
		TextDrawTextSize(TextDrawTableCardOne(i), 36.000000, 43.000000)

		TextDrawTableCardTwo(i) = TextDrawCreate(302.000000, 140.000000, ld_card:cdback)
		TextDrawBackgroundColor(TextDrawTableCardTwo(i), 255)
		TextDrawFont(TextDrawTableCardTwo(i), 4)
		TextDrawLetterSize(TextDrawTableCardTwo(i), 0.430000, 0.199999)
		TextDrawColor(TextDrawTableCardTwo(i), -1)
		TextDrawSetOutline(TextDrawTableCardTwo(i), 0)
		TextDrawSetProportional(TextDrawTableCardTwo(i), 1)
		TextDrawSetShadow(TextDrawTableCardTwo(i), 1)
		TextDrawUseBox(TextDrawTableCardTwo(i), 1)
		TextDrawBoxColor(TextDrawTableCardTwo(i), 255)
		TextDrawTextSize(TextDrawTableCardTwo(i), 36.000000, 43.000000)

		TextDrawTableCardThree(i) = TextDrawCreate(345.000000, 140.000000, ld_card:cdback)
		TextDrawBackgroundColor(TextDrawTableCardThree(i), 255)
		TextDrawFont(TextDrawTableCardThree(i), 4)
		TextDrawLetterSize(TextDrawTableCardThree(i), 0.430000, 0.199999)
		TextDrawColor(TextDrawTableCardThree(i), -1)
		TextDrawSetOutline(TextDrawTableCardThree(i), 0)
		TextDrawSetProportional(TextDrawTableCardThree(i), 1)
		TextDrawSetShadow(TextDrawTableCardThree(i), 1)
		TextDrawUseBox(TextDrawTableCardThree(i), 1)
		TextDrawBoxColor(TextDrawTableCardThree(i), 255)
		TextDrawTextSize(TextDrawTableCardThree(i), 36.000000, 43.000000)

		TextDrawTableCardFour(i) = TextDrawCreate(388.000000, 140.000000, ld_card:cdback)
		TextDrawBackgroundColor(TextDrawTableCardFour(i), 255)
		TextDrawFont(TextDrawTableCardFour(i), 4)
		TextDrawLetterSize(TextDrawTableCardFour(i), 0.430000, 0.199999)
		TextDrawColor(TextDrawTableCardFour(i), -1)
		TextDrawSetOutline(TextDrawTableCardFour(i), 0)
		TextDrawSetProportional(TextDrawTableCardFour(i), 1)
		TextDrawSetShadow(TextDrawTableCardFour(i), 1)
		TextDrawUseBox(TextDrawTableCardFour(i), 1)
		TextDrawBoxColor(TextDrawTableCardFour(i), 255)
		TextDrawTextSize(TextDrawTableCardFour(i), 36.000000, 43.000000)

		TextDrawTableCardFive(i) = TextDrawCreate(216.000000, 140.000000, ld_card:cdback)
		TextDrawBackgroundColor(TextDrawTableCardFive(i), 255)
		TextDrawFont(TextDrawTableCardFive(i), 4)
		TextDrawLetterSize(TextDrawTableCardFive(i), 0.430000, 0.199999)
		TextDrawColor(TextDrawTableCardFive(i), -1)
		TextDrawSetOutline(TextDrawTableCardFive(i), 0)
		TextDrawSetProportional(TextDrawTableCardFive(i), 1)
		TextDrawSetShadow(TextDrawTableCardFive(i), 1)
		TextDrawUseBox(TextDrawTableCardFive(i), 1)
		TextDrawBoxColor(TextDrawTableCardFive(i), 255)
		TextDrawTextSize(TextDrawTableCardFive(i), 36.000000, 43.000000)

		TextDrawCardSelf(i) = TextDrawCreate(251.000000, 191.000000, Twoje karty)
		TextDrawBackgroundColor(TextDrawCardSelf(i), 255)
		TextDrawFont(TextDrawCardSelf(i), 3)
		TextDrawLetterSize(TextDrawCardSelf(i), 0.539999, 1.899999)
		TextDrawColor(TextDrawCardSelf(i), 16711935)
		TextDrawSetOutline(TextDrawCardSelf(i), 0)
		TextDrawSetProportional(TextDrawCardSelf(i), 1)
		TextDrawSetShadow(TextDrawCardSelf(i), 1)

		TextDrawTableCardSelfFirst(i) = TextDrawCreate(274.000000, 215.000000, ld_card:cdback)
		TextDrawBackgroundColor(TextDrawTableCardSelfFirst(i), 255)
		TextDrawFont(TextDrawTableCardSelfFirst(i), 4)
		TextDrawLetterSize(TextDrawTableCardSelfFirst(i), 0.430000, 0.199999)
		TextDrawColor(TextDrawTableCardSelfFirst(i), -1)
		TextDrawSetOutline(TextDrawTableCardSelfFirst(i), 0)
		TextDrawSetProportional(TextDrawTableCardSelfFirst(i), 1)
		TextDrawSetShadow(TextDrawTableCardSelfFirst(i), 1)
		TextDrawUseBox(TextDrawTableCardSelfFirst(i), 1)
		TextDrawBoxColor(TextDrawTableCardSelfFirst(i), 255)
		TextDrawTextSize(TextDrawTableCardSelfFirst(i), 36.000000, 43.000000)

		TextDrawTableCardSelfSecond(i) = TextDrawCreate(323.000000, 215.000000, ld_card:cdback)
		TextDrawBackgroundColor(TextDrawTableCardSelfSecond(i), 255)
		TextDrawFont(TextDrawTableCardSelfSecond(i), 4)
		TextDrawLetterSize(TextDrawTableCardSelfSecond(i), 0.430000, 0.199999)
		TextDrawColor(TextDrawTableCardSelfSecond(i), -1)
		TextDrawSetOutline(TextDrawTableCardSelfSecond(i), 0)
		TextDrawSetProportional(TextDrawTableCardSelfSecond(i), 1)
		TextDrawSetShadow(TextDrawTableCardSelfSecond(i), 1)
		TextDrawUseBox(TextDrawTableCardSelfSecond(i), 1)
		TextDrawBoxColor(TextDrawTableCardSelfSecond(i), 255)
		TextDrawTextSize(TextDrawTableCardSelfSecond(i), 36.000000, 43.000000)

		TextDrawTableMoney(i) = TextDrawCreate(130.000000, 270.000000, Kasa w stole: $4515)
		TextDrawBackgroundColor(TextDrawTableMoney(i), 255)
		TextDrawFont(TextDrawTableMoney(i), 3)
		TextDrawLetterSize(TextDrawTableMoney(i), 0.539999, 1.899999)
		TextDrawColor(TextDrawTableMoney(i), -65281)
		TextDrawSetOutline(TextDrawTableMoney(i), 0)
		TextDrawSetProportional(TextDrawTableMoney(i), 1)
		TextDrawSetShadow(TextDrawTableMoney(i), 1)
		
		
			karty stop
		*/
		
		
		//czerwony ekran po uderzeniu w pojeüdzie
		TextDrawHitscreen(i) = TextDrawCreate(-20.000000,2.000000,|)
        TextDrawUseBox(TextDrawHitscreen(i) ,1)
        TextDrawBoxColor(TextDrawHitscreen(i) ,0xFF0000aa)
        TextDrawTextSize(TextDrawHitscreen(i) ,660.000000,22.000000)
        TextDrawAlignment(TextDrawHitscreen(i) ,0)
        TextDrawBackgroundColor(TextDrawHitscreen(i) ,0xFF0000aa)
        TextDrawFont(TextDrawHitscreen(i) ,3)
        TextDrawLetterSize(TextDrawHitscreen(i) ,1.000000,52.200000)
        TextDrawColor(TextDrawHitscreen(i) ,0xFF0000aa)
        TextDrawSetOutline(TextDrawHitscreen(i) ,1)
        TextDrawSetProportional(TextDrawHitscreen(i) ,1)
        TextDrawSetShadow(TextDrawHitscreen(i) ,1)
		
		//worek na g≥owie, ktÛry bÍdzie zas≥ania≥ leb
		TextDrawHeadbag(i) = TextDrawCreate(-20.000000,2.000000,|)
        TextDrawUseBox(TextDrawHeadbag(i) ,1)
        TextDrawBoxColor(TextDrawHeadbag(i) ,0x000000f)
        TextDrawTextSize(TextDrawHeadbag(i) ,660.000000,22.000000)
        TextDrawAlignment(TextDrawHeadbag(i) ,0)
        TextDrawBackgroundColor(TextDrawHeadbag(i) ,0x000000ff)
        TextDrawFont(TextDrawHeadbag(i) ,3)
        TextDrawLetterSize(TextDrawHeadbag(i) ,1.000000,52.200000)
        TextDrawColor(TextDrawHeadbag(i) ,0x000000f)
        TextDrawSetOutline(TextDrawHeadbag(i) ,1)
        TextDrawSetProportional(TextDrawHeadbag(i) ,1)
        TextDrawSetShadow(TextDrawHeadbag(i) ,1)
		
		// TextDraw z g≥Ûwnym info dla gracza
		//TextDrawMainInfo(i) = TextDrawCreate(430.000000, 113.000000, _)
		TextDrawMainInfo(i) = TextDrawCreate(430.000000, 145.000000, _)
		TextDrawBackgroundColor(TextDrawMainInfo(i), 255)
		TextDrawFont(TextDrawMainInfo(i), 1)
		TextDrawLetterSize(TextDrawMainInfo(i), 0.290000, 1.200000)
		TextDrawColor(TextDrawMainInfo(i), -1)
		TextDrawSetOutline(TextDrawMainInfo(i), 1)
		TextDrawSetProportional(TextDrawMainInfo(i), 1)
		TextDrawUseBox(TextDrawMainInfo(i), 1)
		TextDrawBoxColor(TextDrawMainInfo(i), 68)
		TextDrawTextSize(TextDrawMainInfo(i), 608.000000, 10.000000)

		// TextDraw z ofertπ
		TextDrawOfferTitle(i) = TextDrawCreate(191.000000, 324.000000, _)
		TextDrawBackgroundColor(TextDrawOfferTitle(i), 255)
		TextDrawFont(TextDrawOfferTitle(i), 1)
		TextDrawLetterSize(TextDrawOfferTitle(i), 0.480000, 1.400000)
		TextDrawColor(TextDrawOfferTitle(i), -1)
		TextDrawSetOutline(TextDrawOfferTitle(i), 1)
		TextDrawSetProportional(TextDrawOfferTitle(i), 1)
		
		// TextDraw z tankowaniem seler
		TextDrawFuelContent(i) = CreatePlayerTextDraw(i, 191.000000, 324.000000, _)
		PlayerTextDrawBackgroundColor(i, TextDrawFuelContent(i), 255)
		PlayerTextDrawFont(i, TextDrawFuelContent(i), 1)
		PlayerTextDrawLetterSize(i, TextDrawFuelContent(i), 0.480000, 1.400000)
		PlayerTextDrawColor(i, TextDrawFuelContent(i), -1)
		PlayerTextDrawSetOutline(i, TextDrawFuelContent(i), 1)
		PlayerTextDrawSetProportional(i, TextDrawFuelContent(i), 1)
		
  		// TextDraw z informacjπ o drzwiach
		/*TextDrawDoorInfo(i) = TextDrawCreate(326.000000, 330.000000, _)
		TextDrawAlignment(TextDrawDoorInfo(i), 2)
		TextDrawBackgroundColor(TextDrawDoorInfo(i), 255)
		TextDrawFont(TextDrawDoorInfo(i), 1)
		TextDrawLetterSize(TextDrawDoorInfo(i), 0.379999, 1.299999)
		TextDrawColor(TextDrawDoorInfo(i), -1)
		TextDrawSetOutline(TextDrawDoorInfo(i), 1)
		TextDrawSetProportional(TextDrawDoorInfo(i), 1)
		TextDrawUseBox(TextDrawDoorInfo(i), 1)
		TextDrawBoxColor(TextDrawDoorInfo(i), 68)
		TextDrawTextSize(TextDrawDoorInfo(i), 490.000000, 221.000000)*/

		// TextDraw edytora
		TextDrawEditorTitle(i) = TextDrawCreate(160.000000, 330.000000, _)
		TextDrawBackgroundColor(TextDrawEditorTitle(i), 255)
		TextDrawFont(TextDrawEditorTitle(i), 1)
		TextDrawLetterSize(TextDrawEditorTitle(i), 0.429999, 1.300000)
		TextDrawColor(TextDrawEditorTitle(i), -1)
		TextDrawSetOutline(TextDrawEditorTitle(i), 1)
		TextDrawSetProportional(TextDrawEditorTitle(i), 1)

		// TextDraw czerwonego hp
		TextDrawDamage(i) = TextDrawCreate(0.0, 20.0, _)
		TextDrawAlignment(TextDrawDamage(i), 1)
		TextDrawFont(TextDrawDamage(i) , 3)
		TextDrawLetterSize(TextDrawDamage(i), 10, 65)
		TextDrawBoxColor(TextDrawDamage(i) , 0xFF000022)
		TextDrawSetOutline(TextDrawDamage(i), false)
		TextDrawUseBox(TextDrawDamage(i), 1)
		TextDrawTextSize(TextDrawDamage(i), 840, 680)
		
  		TextDrawFlashbang(i) = TextDrawCreate(0.0, 0.0, _)
		TextDrawAlignment(TextDrawFlashbang(i), 1)
		TextDrawFont(TextDrawFlashbang(i) , 3)
		TextDrawLetterSize(TextDrawFlashbang(i), 10, 65)
		TextDrawBoxColor(TextDrawFlashbang(i) , 0xFFFFFFEE)
		TextDrawSetOutline(TextDrawFlashbang(i), false)
		TextDrawUseBox(TextDrawFlashbang(i), 1)
		TextDrawTextSize(TextDrawFlashbang(i), 840, 680)
		
		TextDrawWindow(i) = TextDrawCreate(499.000000, 13.000000, Szyba zamknieta)
		TextDrawBackgroundColor(TextDrawWindow(i), 866792362)
		TextDrawFont(TextDrawWindow(i), 3)
		TextDrawLetterSize(TextDrawWindow(i), 0.350000, 0.850000)
		TextDrawColor(TextDrawWindow(i), -1)
		TextDrawSetOutline(TextDrawWindow(i), 1)
		TextDrawSetProportional(TextDrawWindow(i), 1)
				
		TextDrawAdminMode(i) = TextDrawCreate(143.000000, 387.000000, -)
		TextDrawBackgroundColor(TextDrawAdminMode(i), 255)
		TextDrawFont(TextDrawAdminMode(i), 1)
		TextDrawLetterSize(TextDrawAdminMode(i), 0.159999, 0.900000)
		TextDrawColor(TextDrawAdminMode(i), -1)
		TextDrawSetOutline(TextDrawAdminMode(i), 0)
		TextDrawSetProportional(TextDrawAdminMode(i), 1)
		TextDrawSetShadow(TextDrawAdminMode(i), 1)
		TextDrawUseBox(TextDrawAdminMode(i), 1)
		TextDrawBoxColor(TextDrawAdminMode(i), 572662218)
		TextDrawTextSize(TextDrawAdminMode(i), 232.000000, 0.000000)

		// 3DTexts
		PlayerCache(i)(pNameTag) = Create3DTextLabel( , COLOR_WHITE, 0.0, 0.0, 0.0, 15.0, 0, 1)
		//PlayerCache(i)(pMeTag) = CreateDynamic3DTextLabel( , COLOR_PURPLE, 0.0, 0.0, 0.05, 10.0)
		format(PlayerCache(i)(pDescTagText), 128,  )
	)

	return 1
)

stock RandWeather()
(
	loss = random(10)
	
	switch(loss)
	(
		case 1..3:
		(
			//slonecznie
			return 0
		)
		case 4..6:
		(
			//pochmurnie
			return 4
		)
		case 7..9:
		(
			//troche mniej slonecznie
			return 5
		)
		case 10:
		(
			//deszcz
			return 8
		)
	)
	
	return 0
)

forward WaitForPositeObject(playerid,object_id)
public WaitForPositeObject(playerid,object_id)
(
	EditDynamicObject(playerid, object_id)
	return 1
)

forward StopPlayerDivingAnim(playerid)
public StopPlayerDivingAnim(playerid)
(	
	ClearAnimations(playerid, 1)
	return 1
)

stock randomEx(min, max)
(    
    //Credits to y_less    
    rand = random(max-min)+min    
    return rand
)

forward SetPlayerToChangeChar(playerid)
public SetPlayerToChangeChar(playerid)
(
	PlayerCache(playerid)(pReconnect) = true
	
	ip(32)
	GetPlayerIp(playerid, ip, sizeof(ip))
	format(playerIP(playerid),32,%s,ip)
	
	string(128)
	format(string, sizeof(string), banip %s, ip)
	SendRconCommand(string)
	
	printf((reconnect) Gracz %s (UID: %i) o ip %s wlasnie przelogowywuje sie,PlayerName(playerid),PlayerCache(playerid)(pUID),ip)
	return 1
)

stock RemoveAttachedShit(playerid)	// usuwanie wszystkich przyczepionych itemÛw
(
	for(i = 0  i ( 9  i ++)
	(
		RemovePlayerAttachedObject(playerid, i)
	)
	
	return 1
)

stock GenerateTemperature()
(
	if(WeatherDayType == DAY_FREEZING)
		WeatherTemperature = -5 + random(11)
	else if(WeatherDayType == DAY_COLD)
		WeatherTemperature = 3 + random(16)
	else if(WeatherDayType == DAY_WARM)
		WeatherTemperature = 16 + random(10)
	else if(WeatherDayType == DAY_HOT)
		WeatherTemperature = 20 + random(10)
	else if(WeatherDayType == DAY_HELL)
		WeatherTemperature = 30 + random(7)
	else
		WeatherTemperature = 20

	temp_s(8)
	format(temp_s, sizeof(temp_s), %d C, WeatherTemperature)
	TextDrawSetString(Text:TextDrawTemperature, temp_s)
	
	foreach(Player, i)
	(
		TextDrawShowForPlayer(i, Text:TextDrawTemperature)
	)

	return 1
)

stock GetWeekDay(day=0, month=0, year=0)
(
  if (!day)
    getdate(year, month, day)

  new
    j,
    e
  

  if (month (= 2)
  (
    month += 12
    --year
  )

  j = year % 100
  e = year / 100

  retDay = 0
  
  switch ((day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7)
  (
    case 0: retDay = DAY_SATURDAY
    case 1: retDay = DAY_SUNDAY
    case 2: retDay = DAY_MONDAY
    case 3: retDay = DAY_TUESDAY
    case 4: retDay = DAY_WEDNESDAY
    case 5: retDay = DAY_THURSDAY
    case 6: retDay = DAY_FRIDAY
  )

  return retDay
)

stock GetDistanceFromPointToPoint( Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2 )
(
    return floatround( floatsqroot( ( ( x1 - x2 ) * ( x1 - x2 ) ) + ( ( y1 - y2 ) * ( y1 - y2 ) ) + ( ( z1 - z2 ) * ( z1 - z2 ) ) ) )
)

stock IsPointInRangeOfPoint(Float:x, Float:y, Float:z, Float:x2, Float:y2, Float:z2, Float:range)
(
    x2 -= x
    y2 -= y
    z2 -= z

    return ((x2 * x2) + (y2 * y2) + (z2 * z2)) ( (range * range)
)

stock blint_SaveCash(safetyUID, playerid)
(
	// dodajmy, tak na przysz≥oúÊ
	buffer(256)
	format(buffer,sizeof(buffer),UPDATE hrp_characters SET char_cash = %i WHERE char_uid = %i, PlayerCache(playerid)(pCash), safetyUID)
	mysql_query(buffer)
	
	return 1
)

stock SaveTicket(giveruid, owneruid, reason(), cash)
(
	real_reason(32)

	mysql_real_escape_string(reason, real_reason)
	mysql_query_format(INSERT INTO hrp_pd_ticket (ticket_giver, ticker_owner, ticket_desc, ticket_cash) VALUES (%d, %d, %s, %d), giveruid, owneruid, real_reason, cash)
	return 1
)

stock SaveArrest(giveruid, owneruid, day)
(
	mysql_query_format(INSERT INTO hrp_pd_arrest (arrest_giver, arrest_owner, arrest_day) VALUES (%d, %d, %d), giveruid, owneruid, day)
	return 1
)

// encode
encode_doors(bonnet, boot, driver_door, passenger_door, behind_driver_door, behind_passenger_door)
(
    #pragma unused behind_driver_door
    #pragma unused behind_passenger_door
    return bonnet | (boot (( 8) | (driver_door (( 16) | (passenger_door (( 24)
)

stock getPlayerRegion(playerid)
(
	region = -1
	Float:distance = 0.0
	for(i = 0  i ( sizeof(GunRegionInfo) i++)
	(
		if(GetPlayerDistanceFromPoint(playerid, GunRegionInfo(i)(grPosX), GunRegionInfo(i)(grPosY), GunRegionInfo(i)(grPosZ)) ( distance || distance == 0.0)
		(
			distance = GetPlayerDistanceFromPoint(playerid, GunRegionInfo(i)(grPosX), GunRegionInfo(i)(grPosY), GunRegionInfo(i)(grPosZ))
			region = i
		)
	)
	
	return region
)

stock countCornerDealers(corner_id)
(
	count = 0
	for(i = 0  i ( MAX_PLAYERS i++)
	(
		if(PlayerCache(i)(pCorner) == corner_id)
			count++
	)
	
	return count
)

// Losowanie corneru dla gracza, seler
stock SelectRandomCorner(playerid)
(
	playerzone = GetPlayerZoneID(playerid)
	cornerid = random(MAX_CORNERS)
	if(CornerInfo(cornerid)(cOwner) != ZoneInfo(playerzone)(zOwner))
	(
		SelectRandomCorner(playerid)
	)
	else
	(
		PlayerCache(playerid)(pCorner) = cornerid
		return cornerid
	)
	
	return 0
)

// Przypisywanie w≥aúciciela (UID grupy) dla corneru, seler
stock LoadCornersOwner()
(
	count = 0
	for(i = 0 i ( MAX_CORNERS i++)
	(
		zone = GetPointZoneID(CornerInfo(i)(cPosX), CornerInfo(i)(cPosY))
		if(ZoneInfo(zone)(zOwner) != 0)
		(
			CornerInfo(i)(cOwner) = ZoneInfo(zone)(zOwner)
			count++
		)
	)
	printf((load) Wczytano wszystkich wlascicieli cornerow (%i), count)
	return 1
)


// Takie tam.
stock sendClientPoop(playerid, text())
(
	SendClientMessage(playerid, COLOR_INFO, text)
	return 1
)

stock stopSparing(playerid)
(
	if(PlayerCache(playerid)(pSparing) == INVALID_PLAYER_ID)
	(
		return 0
	)
	
	enemy = PlayerCache(playerid)(pSparing)
	
	PlayerCache(playerid)(pSparing) = INVALID_PLAYER_ID
	PlayerCache(enemy)(pSparing) = INVALID_PLAYER_ID
	
	SendClientMessage(enemy, COLOR_INFO, ) Sparing zosta≥ przerwany.)
	SendClientMessage(playerid, COLOR_INFO, ) Sparing zosta≥ przerwany.)
	
	return 1
)

// Loteria
stock LaunchLottery()
(
	buffer(256)
	format(buffer, sizeof(buffer), SELECT * FROM hrp_lottery)
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() ) 99)
	(
		id, owner, current = 0
		rows = mysql_num_rows()
		
		winchoose:
		winner = random(rows - 1)
		if(winner ( 0)
			goto winchoose
			
		while(mysql_fetch_row(buffer, |))
		(
			current++
			sscanf(buffer, p(|)dd, id, owner)
			if(current == winner)
			(
				mysql_query_format(UPDATE hrp_characters SET char_bankcash = char_bankcash + %d WHERE char_uid = %d, rows * 10, owner)
				
				message(128)
				format(message, sizeof(message), wygra≥eú na loterii $%d!, rows * 10)
				AddPlayerOfflineMessage(owner, message)
				break
			)
		)
		
		mysql_free_result()
		printf((LOTTERY) Uruchomiono loterie, bo znaleziono %d losow, rows)
	)
	else
	(
		mysql_free_result()
		printf((LOTTERY) Nie uruchomiono loterii, bo jest za malo losow)
	)
	
	//mysql_query_format(DELETE FROM hrp_items WHERE item_type = 80)
	mysql_query(TRUNCATE TABLE hrp_lottery)
	return 1
)

stock blint_CashBugFixer(playerid)
(
	bool:checkbug = false
	if(gettime() - LogTime(playerid) ) 60)
		checkbug= true
	
	if(!checkbug)
	(
		GuiMsg(playerid, Musisz chwilÍ odczekaÊ nim uøyjesz tej komendy., 0)
		return 1
	)
	
	return 1
)

stock IsPlayerFacingPoint(playerid, Float:PointX, Float:PointY, Float:Range = 10.0)
(
	Float:FacingAngle
	GetPlayerFacingAngle(playerid, FacingAngle)
	
	Float:Angle
	Float:X, Float:Y, Float:Z
	GetPlayerPos(playerid, X, Y, Z)
	if(X ) PointX && Y ) PointY) Angle = floatabs(atan2(floatsub(PointX, X), floatsub(PointY, Y)))
	if(X ) PointX && Y (= PointY) Angle = floatadd(floatabs(atan2(floatsub(Y, PointY), floatsub(PointX, X))), 270.0)
	if(X (= PointX && Y ) PointY) Angle = floatadd(floatabs(atan2(floatsub(PointY, Y), floatsub(X, PointX))), 90.0)
	if(X (= PointX && Y (= PointY) Angle = floatadd(floatabs(atan2(floatsub(X, PointX), floatsub(Y, PointY))), 180.0)
	Range /= 2.0
	return floatabs(floatsub(FacingAngle, Angle)) (= floatabs(Range) || floatabs(floatsub(floatadd(FacingAngle, 360.0), Angle)) (= floatabs(Range)
)
