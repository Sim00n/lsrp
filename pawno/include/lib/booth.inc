public CreateBooth(Float:PosX, Float:PosY, Float:PosZ, Float:Radius)
(
	gameid, uid
	mysql_query_format(INSERT INTO hrp_booths (booth_owner, booth_posx, booth_posy, booth_posz, booth_radius, booth_dooruid) VALUES(0, %f, %f, %f, %f, 0), PosX, PosY, PosZ, Radius)
	
	uid = mysql_insert_id()
	gameid = Itter_Free(Booths)
	
	BoothData(gameid)(bUID) = uid
	BoothData(gameid)(bOwner) = 0
	BoothData(gameid)(bPosX) = PosX
	BoothData(gameid)(bPosY) = PosY
	BoothData(gameid)(bPosZ) = PosZ
	BoothData(gameid)(bRadius) = Radius
	BoothData(gameid)(bDoorUID) = 0
	
	Itter_Add(Booths, gameid)
	return gameid
)

public DeleteBooth(gameid)
(
	mysql_query_format(DELETE FROM hrp_booths WHERE booth_uid = %d, BoothData(gameid)(bUID))
	
	BoothData(gameid)(bUID) = 0
	BoothData(gameid)(bOwner) = 0
	BoothData(gameid)(bPosX) = 0.0
	BoothData(gameid)(bPosY) = 0.0
	BoothData(gameid)(bPosZ) = 0.0
	BoothData(gameid)(bRadius) = 0.0
	BoothData(gameid)(bDoorUID) = 0
	
	Itter_Remove(Booths, gameid)
	return 1
)

public SaveBooth(gameid)
(
	mysql_query_format(UPDATE hrp_booths SET booth_owner = %d, booth_posx = %f, booth_posy = %f, booth_posz = %f, booth_radius = %f, booth_dooruid = %d WHERE booth_uid = %d,
		BoothData(gameid)(bOwner),
		BoothData(gameid)(bPosX),
		BoothData(gameid)(bPosY),
		BoothData(gameid)(bPosZ),
		BoothData(gameid)(bRadius),
		BoothData(gameid)(bDoorUID),
		BoothData(gameid)(bUID))
		
	return 1
)

public LoadBooths()
(
	booth_id, data(128)
	mysql_query(SELECT * FROM hrp_booths)

 	print((load) Rozpoczynam proces wczytywania bazarow z bazy danych...)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		booth_id = Itter_Free(Booths)
		
		sscanf(data, p(|)ddffffd,
		BoothData(booth_id)(bUID),
		BoothData(booth_id)(bOwner),

		BoothData(booth_id)(bPosX),
		BoothData(booth_id)(bPosY),
		BoothData(booth_id)(bPosZ),
		BoothData(booth_id)(bRadius),

		BoothData(booth_id)(bDoorUID))

		Itter_Add(Booths, booth_id)
	)
	mysql_free_result()

	printf((load) Wczytano %d budek z bazy danych., booth_id)
	return 1
)

