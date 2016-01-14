public OnDynamicObjectMoved(objectid)
(
	/*
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(PlayerCache(i)(pBasketBall) != INVALID_OBJECT_ID)
			(
				if(PlayerCache(i)(pHavingBall))
				(
					ball = ObjectInfo(PlayerCache(i)(pBasketBall))(objSID),
						Float:objX, Float:objY, Float:objZ,
						Float:PosX, Float:PosY, Float:PosZ,
						Float:Speed, Float:Distance, Float:Angle

	   				keysa, uda, lra
			   		GetPlayerKeys(i, keysa, uda, lra)
			   		if(keysa & KEY_SPRINT)
			   		(
			   			Speed = 15.0
			   			Distance = 2.0

						ApplyAnimation(i, BSKTBALL, BBALL_run, 4.1, 1, 1, 1, 1, 1, 1)
			   		)
			   		else
			   		(
			   			Speed = 12.0
			   			Distance = 1.2

			   			ApplyAnimation(i, BSKTBALL, BBALL_walk, 4.1, 1, 1, 1, 1, 1, 1)
			   		)

			   		GetPlayerPos(i, PosX, PosY, PosZ)
			   		GetPlayerFacingAngle(i, Angle)

					GetXYInFrontOfPlayer(i, PosX, PosY, Distance)
					GetDynamicObjectPos(ball, objX, objY, objZ)

					if(PlayerCache(i)(pBallPhase) == 1)
		 			(
   						MoveDynamicObject(ball, PosX, PosY, PosZ, Speed)
						PlayerCache(i)(pBallPhase) = 2
	   				)
					else if(PlayerCache(i)(pBallPhase) == 2)
					(
		   				MoveDynamicObject(ball, PosX, PosY, PosZ - 1.0, Speed)
						PlayerCache(i)(pBallPhase) = 1
	   				)
				)
			)
		)
	)
	*/
	return 1
)

public OnPlayerObjectMoved(playerid, objectid)
(
	return 1
)


public OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ)
(
	new	string(256),
		Float:ObjPosX, Float:ObjPosY, Float:ObjPosZ,
		Float:ObjRotX, Float:ObjRotY, Float:ObjRotZ, counter

	if(GetPlayerVirtualWorld(playerid) == 0)
	(
		if(PlayerCache(playerid)(pAdmin) ( 1 && PlayerCache(playerid)(pAdmin) ) -3)
		(
			group_id_fix = GetPlayerDutyGroupID(playerid)
			if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
			(
				flag = false
				for(i = 0 i ( sizeof(PoliceLadder) i++)
				(
					if(modelid == OBJECT_POLICE_LADDER || modelid == OBJECT_FIRE_WRECK)
					(
						flag = true
					)
				)
				if(!flag)
				(
					return 1
				)
			)
			else
			(
				if(PutableObject(playerid)(pObjID) != INVALID_OBJECT_ID)
				(
					//edytuj
					obj_owner = Streamer_GetIntData(STREAMER_TYPE_OBJECT , objectid , E_STREAMER_EXTRA_ID)
					if(PlayerCache(playerid)(pUID) != obj_owner)
					(
						return 1
					)
					else
					(
						//SendClientMessage(playerid,COLOR_RED,spassiba)
					)
				)
				else
				(
					return 1
				)
			)
		)
	)
	
	for (object_id = 0 object_id (= MAX_OBJECTS object_id++)
	(
		counter++
 		if(Streamer_IsItemVisible(playerid, STREAMER_TYPE_OBJECT, object_id))
		(
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_MODEL_ID) == modelid)
			(
				GetDynamicObjectPos(object_id, ObjPosX, ObjPosY, ObjPosZ)
				GetDynamicObjectRot(object_id, ObjRotX, ObjRotY, ObjRotZ)

				// Porównaj pozycjê do siebie, upewnij siê, ¿e to ten obiekt
				if(!floatcmp(ObjPosX, fX) && !floatcmp(ObjPosY, fY) && !floatcmp(ObjPosZ, fZ))
				(
					PlayerCache(playerid)(pMoveObject) = object_id

				   	format(string, sizeof(string), ~b~Model: ~w~%d		  ~b~Identyfikator: ~w~%d~n~~n~~n~~r~PosX: ~w~%.4f ~r~PosY: ~w~%.4f ~r~PosZ: ~w~%.4f ~n~~n~~n~~y~RotX: ~w~%.4f ~y~RotY: ~w~%.4f ~y~RotZ: ~w~%.4f, GetObjectModel(object_id), GetObjectUID(object_id), ObjPosX, ObjPosY, ObjPosZ, ObjRotX, ObjRotY, ObjRotZ)
					TextDrawSetString(Text:TextDrawEditorTitle(playerid), string)

					TextDrawShowForPlayer(playerid, Text:TextDrawEditorBack)
					TextDrawShowForPlayer(playerid, Text:TextDrawEditorTitle(playerid))
					break
				)
			)
		)
	)
	EditPlayerObject(playerid, objectid)

	TextDrawSetString(Text:TextDrawMainInfo(playerid), Rozpoczales ~b~edycje ~w~obiektu. Aby anulowac, wcisnij klawisz ~r~ESC~w~.~n~~n~Aby ~y~zapisac ~w~pozycje obiektu, kliknij na ~g~dyskietke~w~.~n~~n~Klawisz ~r~~k~~PED_SPRINT~ ~w~pozwala na swobodne poruszanie kamera.~n~~n~~y~/odel ~w~- usun obiekt~n~~y~/ogate ~w~- pozycja bramy otwartej)
	TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
	return 1
)

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
(
	itemid = PlayerCache(playerid)(pManageItem)
		
	switch(response)
	(
		case EDIT_RESPONSE_CANCEL:
		(
			RemovePlayerAttachedObject(playerid, SLOT_TRYING)			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Anulowa³eœ edycjê obiektu - powróci³ on do poprzedniego stanu. Mo¿esz go za³o¿yæ u¿ywaj¹c przedmiot., OK, )
		)
		case EDIT_RESPONSE_FINAL:
		(						
			PlayerAttach(playerid)(aPosX) = fOffsetX
			PlayerAttach(playerid)(aPosY) = fOffsetY
			PlayerAttach(playerid)(aPosZ) = fOffsetZ
			PlayerAttach(playerid)(aRotX) = fRotX
			PlayerAttach(playerid)(aRotY) = fRotY
			PlayerAttach(playerid)(aRotZ) = fRotZ
			PlayerAttach(playerid)(aScaleX) = fScaleX
			PlayerAttach(playerid)(aScaleY) = fScaleY
			PlayerAttach(playerid)(aScaleZ) = fScaleZ
				
			RemovePlayerAttachedObject(playerid, SLOT_TRYING)
			
			string(512)
			format(string, sizeof(string), UPDATE hrp_access SET access_posx = %f, access_posy = %f, access_posz = %f, access_rotx = %f, access_roty = %f, access_rotz = %f,, PlayerAttach(playerid)(aPosX), PlayerAttach(playerid)(aPosY), PlayerAttach(playerid)(aPosZ), PlayerAttach(playerid)(aRotX), PlayerAttach(playerid)(aRotY), PlayerAttach(playerid)(aRotZ))
			format(string, sizeof(string), %s access_scalex = %f, access_scaley = %f, access_scalez = %f WHERE access_uid = %d LIMIT 1, string, PlayerAttach(playerid)(aScaleX), PlayerAttach(playerid)(aScaleY), PlayerAttach(playerid)(aScaleZ), ItemInfo(itemid)(iValue1))
			mysql_query(string)
			
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Sukces, Obiekt zosta³ poprawnie zapisany. Mo¿esz go teraz za³o¿yæ u¿ywaj¹c przedmiot., OK, )
		)
	)
	ItemInfo(itemid)(iUsed) = 0
	mysql_query_format(UPDATE hrp_items SET item_used = 0 WHERE item_uid = %d, ItemInfo(itemid)(iUID))
	return 1
)

public OnPlayerEditObject(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ)
(
	object_id = PlayerCache(playerid)(pMoveObject), string(256),
 		Float:ObjPosX, Float:ObjPosY, Float:ObjPosZ,
   		Float:ObjRotX, Float:ObjRotY, Float:ObjRotZ

	switch(response)
	(
		case EDIT_RESPONSE_CANCEL:
		(
			GetDynamicObjectPos(object_id, ObjPosX, ObjPosY, ObjPosZ)
			GetDynamicObjectRot(object_id, ObjRotX, ObjRotY, ObjRotZ)

			SetDynamicObjectPos(object_id, ObjPosX, ObjPosY, ObjPosZ)
			SetDynamicObjectRot(object_id, ObjRotX, ObjRotY, ObjRotZ)

			PlayerCache(playerid)(pMoveObject) = INVALID_OBJECT_ID

  			TextDrawHideForPlayer(playerid, Text:TextDrawEditorBack)
			TextDrawHideForPlayer(playerid, Text:TextDrawEditorTitle(playerid))

			TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Edycja obiektu zosta³a anulowana.\nObiekt powróci³ na swoje miejsce., OK, )
		)
		case EDIT_RESPONSE_FINAL:
		(
			SetDynamicObjectPos(object_id, fX, fY, fZ)
			SetDynamicObjectRot(object_id, fRotX, fRotY, fRotZ)

			hrp_SaveObject(object_id)
			PlayerCache(playerid)(pMoveObject) = INVALID_OBJECT_ID

			TextDrawHideForPlayer(playerid, Text:TextDrawEditorBack)
			TextDrawHideForPlayer(playerid, Text:TextDrawEditorTitle(playerid))

			TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pozycja obiektu zosta³a pomyœlnie zapisana., OK, )
		)
		case EDIT_RESPONSE_UPDATE:
		(
			format(string, sizeof(string), ~b~Model: ~w~%d		  ~b~Identyfikator: ~w~%d~n~~n~~n~~r~PosX: ~w~%.4f ~r~PosY: ~w~%.4f ~r~PosZ: ~w~%.4f ~n~~n~~n~~y~RotX: ~w~%.4f ~y~RotY: ~w~%.4f ~y~RotZ: ~w~%.4f, GetObjectModel(object_id), GetObjectUID(object_id), fX, fY, fZ, fRotX, fRotY, fRotZ)
			TextDrawSetString(Text:TextDrawEditorTitle(playerid), string)
		)
	)
	
	//a moze nie ?
	if(PlayerCache(playerid)(pPut))
	(
		PlayerCache(playerid)(pPut) = false
	)
	
	return 1
)

public LoadCorpseObjects()
(
	data(256), item_uid, Float:item_posx, Float:item_posy, Float:item_posz, item_world, object_id, count = 0
	
	mysql_query_format(SELECT item_uid, item_posx, item_posy, item_posz, item_world FROM hrp_items WHERE item_type = %d AND item_place = %d, ITEM_CORPSE, PLACE_NONE)
	
	print((load) Rozpoczynam proces wczytywania wszystkich cia³ z bazy...)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)dfffd, item_uid, item_posx, item_posy, item_posz, item_world)
		
		object_id = CreateDynamicObject(ItemTypeInfo(ITEM_CORPSE)(iTypeObjModel), item_posx, item_posy, item_posz - 1.0, ItemTypeInfo(ITEM_CORPSE)(iTypeObjRotX), ItemTypeInfo(ITEM_CORPSE)(iTypeObjRotY), 0, item_world, -1, -1, 80.0)
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, (item_uid * -1))
		count++
	)
	mysql_free_result()
	
	printf((load) Wczytano %d cia³., count)
	return 1
)

public LoadSafeObjects()
(
	data(256), item_uid, Float:item_posx, Float:item_posy, Float:item_posz, item_world, object_id, count = 0
	
	mysql_query_format(SELECT item_uid, item_posx, item_posy, item_posz, item_world FROM hrp_items WHERE item_type = %d AND item_place = %d, ITEM_SAFE, PLACE_NONE)
	
	print((load) Rozpoczynam proces wczytywania wszystkich sejfow z bazy...)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)dfffd, item_uid, item_posx, item_posy, item_posz, item_world)
		
		object_id = CreateDynamicObject(ItemTypeInfo(ITEM_SAFE)(iTypeObjModel), item_posx, item_posy, item_posz - 1.0 + 0.46, ItemTypeInfo(ITEM_SAFE)(iTypeObjRotX), ItemTypeInfo(ITEM_SAFE)(iTypeObjRotY), 0, item_world, -1, -1, 80.0)
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, (item_uid * -1))
		count++
	)
	mysql_free_result()
	
	printf((load) Wczytano %d sejfow., count)
	return 1
)

public LoadAllObjects()
(
	data(256), object_id
	mysql_query(SELECT * FROM hrp_objects)

 	object_uid, object_model,
		Float:object_posx, Float:object_posy, Float:object_posz,
		Float:object_rotx, Float:object_roty, Float:object_rotz,
		object_world, object_interior, Float:object_distance

	print((load) Rozpoczynam proces wczytywania wszystkich obiektów z bazy...)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
	 	sscanf(data, p(|)ddffffffddf, object_uid, object_model, object_posx, object_posy, object_posz, object_rotx, object_roty, object_rotz, object_world, object_interior, object_distance)
		object_id = CreateDynamicObject(object_model, object_posx, object_posy, object_posz, object_rotx, object_roty, object_rotz, object_world, object_interior, -1, object_distance)

		if(object_model == OBJECT_COOK)
		(
			LoadCooking(object_id)
		)
		
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID, object_uid)
	)
  	mysql_free_result()

	printf((load) Wczytano %d obiekty/ów., object_id)
	
	printf((load) Rozpoczynam proces wczytywania tagów dla obiektów)
	
	if(!DEBUG_MODE)
		LoadObjectTags()
	printf((load) Wczytano tagi.)
	
	LoadObjectMaterials()
	LoadObjectsText()
	
	return 1
)

// Szymon - tego nie zrozumiesz - ³adowanie ok. 1:30-2:00 minut
stock LoadObjectTags(world = 0)
(
	data(512), tag_objectuid, tag_size, tag_font, tag_text(256)
	mysql_query(SELECT tag_objectuid, tag_text, tag_size, tag_font FROM hrp_tags WHERE tag_objectuid != 0)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
	 	sscanf(data, p(|)ds(256)dd, tag_objectuid, tag_text, tag_size, tag_font)
				
		for (object_id = 0 object_id ( MAX_OBJECTS object_id++)
		(
			if(IsValidDynamicObject(object_id))
			(
				if(Streamer_IsInArrayData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_WORLD_ID, world))
				(
					object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)
					if(object_uid == tag_objectuid)
					(
						SetDynamicObjectMaterialText(object_id, 0, tag_text, OBJECT_MATERIAL_SIZE_256x128, Fonts(tag_font), FontSizes(tag_size), 1, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER)
					)
				)
			)
		)
	)
  	mysql_free_result()
	return 1
)

stock fakeOnPlayerSelectObject(playerid, objectid, modelid, Float:fX, Float:fY, Float:fZ)
(
	new	string(256),
		Float:ObjPosX, Float:ObjPosY, Float:ObjPosZ,
		Float:ObjRotX, Float:ObjRotY, Float:ObjRotZ, counter

	if(GetPlayerVirtualWorld(playerid) == 0)
	(
		//if(PlayerCache(playerid)(pAdmin) != 1 && !PlayerCache(playerid)(pTagging) && !PlayerCache(playerid)(pPut))
		if(PlayerCache(playerid)(pAdmin) ( 1 && PlayerCache(playerid)(pAdmin) ) -3 && !PlayerCache(playerid)(pTagging) && !PlayerCache(playerid)(pPut))
		(
			group_id_fix = GetPlayerDutyGroupID(playerid)
			if(GroupData(group_id_fix)(gType) == GROUP_FIREDEPT)
			(
				flag = false
				for(i = 0 i ( sizeof(PoliceLadder) i++)
				(
					if(modelid == OBJECT_POLICE_LADDER)
					(
						flag = true
					)
				)
				if(!flag)
				(
					return 1
				)
			)
			else
			(
				return 1
			)
		)
	)
	
	for (object_id = 0 object_id (= MAX_OBJECTS object_id++)
	(
		counter++
 		if(Streamer_IsItemVisible(playerid, STREAMER_TYPE_OBJECT, object_id))
		(
			if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_MODEL_ID) == modelid)
			(
				GetDynamicObjectPos(object_id, ObjPosX, ObjPosY, ObjPosZ)
				GetDynamicObjectRot(object_id, ObjRotX, ObjRotY, ObjRotZ)

				// Porównaj pozycjê do siebie, upewnij siê, ¿e to ten obiekt
				if(!floatcmp(ObjPosX, fX) && !floatcmp(ObjPosY, fY) && !floatcmp(ObjPosZ, fZ))
				(
					PlayerCache(playerid)(pMoveObject) = object_id

				   	format(string, sizeof(string), ~b~Model: ~w~%d		  ~b~Identyfikator: ~w~%d~n~~n~~n~~r~PosX: ~w~%.4f ~r~PosY: ~w~%.4f ~r~PosZ: ~w~%.4f ~n~~n~~n~~y~RotX: ~w~%.4f ~y~RotY: ~w~%.4f ~y~RotZ: ~w~%.4f, GetObjectModel(object_id), GetObjectUID(object_id), ObjPosX, ObjPosY, ObjPosZ, ObjRotX, ObjRotY, ObjRotZ)
					TextDrawSetString(Text:TextDrawEditorTitle(playerid), string)

					TextDrawShowForPlayer(playerid, Text:TextDrawEditorBack)
					TextDrawShowForPlayer(playerid, Text:TextDrawEditorTitle(playerid))
					break
				)
			)
		)
	)
	EditDynamicObject(playerid, objectid)
	//EditPlayerObject(playerid, objectid)
	

	TextDrawSetString(Text:TextDrawMainInfo(playerid), Rozpoczales ~b~edycje ~w~obiektu. Aby anulowac, wcisnij klawisz ~r~ESC~w~.~n~~n~Aby ~y~zapisac ~w~pozycje obiektu, kliknij na ~g~dyskietke~w~.~n~~n~Klawisz ~r~~k~~PED_SPRINT~ ~w~pozwala na swobodne poruszanie kamera.~n~~n~~y~/odel ~w~- usun obiekt~n~~y~/ogate ~w~- pozycja bramy otwartej)
	TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
	return 1
)

stock LoadObjectMaterials()
(
	buffer(256), txd(32), tx(32), model, color, index, count = 0
	for(i = 0  i ( MAX_OBJECTS i++)
	(
		if(IsValidDynamicObject(i))
		(
			object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, i, E_STREAMER_EXTRA_ID)
			format(buffer, sizeof(buffer), SELECT mat_model, mat_txd, mat_tx, mat_color, mat_index FROM hrp_materials WHERE mat_object = %d, object_uid)
			mysql_query(buffer)
			mysql_store_result()
			
			if(mysql_num_rows() ) 0)
			(
				while(mysql_fetch_row(buffer, |))
				(
					sscanf(buffer, p(|)ds(32)s(32)hd, model, txd, tx, color, index)
					color |= 0xFF (( 24
					SetDynamicObjectMaterial(i, index, model, txd, tx, color)
					count++
				)
			)
			
			mysql_free_result()
		)
	)
	
	printf((load) Wczytano wszystkie tekstury obiektow (%i), count)
	
	return 1
)

stock LoadObjectMaterial(object_id)
(
	// To jest funkcja tylko dla jednego obiektu, mo¿e siê przydaæ
	buffer(256), txd(32), tx(32), model, color, index
	if(IsValidDynamicObject(object_id))
	(
		object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)
		format(buffer, sizeof(buffer), SELECT mat_model, mat_txd, mat_tx, mat_color, mat_index FROM hrp_materials WHERE mat_object = %d, object_uid)
		
		mysql_query(buffer)
		mysql_store_result()
		if(mysql_num_rows() ) 0)
		(
			while(mysql_fetch_row(buffer, |))
			(
				sscanf(buffer, p(|)ds(32)s(32)hd, model, txd, tx, color, index)
				color |= 0xFF (( 24
				SetDynamicObjectMaterial(object_id, index, model, txd, tx, color)
			)
		)
			
		mysql_free_result()
	)
	
	return 1
)

stock LoadObjectsText()
(
	buffer(256), count = 0, matsize, font(32), fontsize, text(128), bold
	for(i = 0  i ( MAX_OBJECTS i++)
	(
		if(IsValidDynamicObject(i))
		(
			object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, i, E_STREAMER_EXTRA_ID)
			format(buffer, sizeof(buffer), SELECT text_matsize, text_font, text_fontsize, text_text, text_bold FROM hrp_materialtexts WHERE text_object = %d, object_uid)
			mysql_query(buffer)
			mysql_store_result()
			
			if(mysql_num_rows() ) 0)
			(
				while(mysql_fetch_row(buffer, |))
				(
					sscanf(buffer, p(|)ds(32)ds(128)d, matsize, font, fontsize, text, bold)
					SetDynamicObjectMaterialText(i, 0, text, matsize, font, fontsize, bold, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER)
					count++
				)
			)
			
			mysql_free_result()
		)
	)
	
	printf((load) Wczytano wszystkie teksty na obiektach (%i), count)
	return 1
)

stock LoadObjectText(object_id)
(
	buffer(256), matsize, font(32), fontsize, text(128), bold
	
	if(IsValidDynamicObject(object_id))
	(
		object_uid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, object_id, E_STREAMER_EXTRA_ID)
		format(buffer, sizeof(buffer), SELECT text_matsize, text_font, text_fontsize, text_text, text_bold FROM hrp_materialtexts WHERE text_object = %d, object_uid)
		
		mysql_query(buffer)
		mysql_store_result()
		
		if(mysql_num_rows() ) 0)
		(
			while(mysql_fetch_row(buffer, |))
			(
				sscanf(buffer, p(|)ds(32)ds(128)d, matsize, font, fontsize, text, bold)
				SetDynamicObjectMaterialText(object_id, 0, text, matsize, font, fontsize, bold, 0xFFFFFFFF, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER)
			)
		)
		
		mysql_free_result()
	)
	return 1
)

stock ClearMaterialsForObject(object_uid)
(	
	mysql_query_format(DELETE FROM hrp_materials WHERE mat_object = %d, object_uid)
	mysql_query_format(DELETE FROM hrp_materialtexts WHERE text_object= %d, object_uid)
	return 1
)


