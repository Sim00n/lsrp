public Add3DTextLabel(LabelDesc(128), LabelColor, Float:LabelPosX, Float:LabelPosY, Float:LabelPosZ, Float:LabelDrawDistance, LabelWorld, LabelInteriorID)
(
	Text3D:label_id, label_uid, label_desc(256)
	mysql_real_escape_string(LabelDesc, label_desc)
	
	mysql_query_format(INSERT INTO hrp_3dlabels (label_desc, label_color, label_posx, label_posy, label_posz, label_drawdist, label_world, label_interior) VALUES (%s, %d, %f, %f, %f, %f, %d, %d), label_desc, LabelColor, LabelPosX, LabelPosY, LabelPosZ, LabelDrawDistance, LabelWorld, LabelInteriorID)

	label_uid = mysql_insert_id()

	label_id = CreateDynamic3DTextLabel(LabelWrap(LabelDesc), LabelColor, LabelPosX, LabelPosY, LabelPosZ, LabelDrawDistance, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, LabelWorld, LabelInteriorID, -1, 80.0)
	Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID, label_uid)

	return 1
	//test
)

public Load3DTextLabels()
(
	data(512), labels
	mysql_query(SELECT * FROM hrp_3dlabels)

	Text3D:label_id, label_uid, label_desc(128), label_color,
		Float:label_posx, Float:label_posy, Float:label_posz,
		Float:label_drawdist, label_interior, label_world

	print((load) Rozpoczynam proces wczytywania wszystkich 3DTexts z bazy...)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ds(128)dffffdd, label_uid, label_desc, label_color, label_posx, label_posy, label_posz, label_drawdist, label_world, label_interior)
  		label_id = CreateDynamic3DTextLabel(LabelWrap(label_desc), label_color, label_posx, label_posy, label_posz, label_drawdist, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, label_world, label_interior, -1, 100.0)

		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID, label_uid)
		
		labels++
	)
	mysql_free_result()
	
	printf((load) Wczytano %d 3D teksty/ów., labels)
	return 1
)

public Destroy3DTextLabel(label_id)
(
	label_uid = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID)
	mysql_query_format(DELETE FROM hrp_3dlabels WHERE label_uid = %d LIMIT 1, label_uid)

	DestroyDynamic3DTextLabel(Text3D:label_id)
	return 1
)

public Save3DTextLabel(label_id)
(
	label_uid = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID),
		Float:PosX, Float:PosY, Float:PosZ

	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_X, PosX)
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Y, PosY)
	Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_Z, PosZ)

	mysql_query_format(UPDATE hrp_3dlabels SET label_posx = %f, label_posy = %f, label_posz = %f WHERE label_uid = %d LIMIT 1, PosX, PosY, PosZ, label_uid)
	return 1
)