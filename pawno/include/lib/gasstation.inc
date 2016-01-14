public CreatePetrol(Float:PosX, Float:PosY, Float:PosZ, Float:Radius)
(
	gameid, uid
	mysql_query_format(INSERT INTO hrp_petrols (petrol_owner, petrol_posx, petrol_posy, petrol_posz, petrol_radius) VALUES(0, %f, %f, %f, %f), PosX, PosY, PosZ, Radius)
	
	uid = mysql_insert_id()
	gameid = Itter_Free(Petrols)
	
	PetrolData(gameid)(bUID) = uid
	PetrolData(gameid)(bOwner) = 0
	PetrolData(gameid)(bPosX) = PosX
	PetrolData(gameid)(bPosY) = PosY
	PetrolData(gameid)(bPosZ) = PosZ
	PetrolData(gameid)(bRadius) = Radius
	
	Itter_Add(Petrols, gameid)
	return gameid
)

public DeletePetrol(gameid)
(
	mysql_query_format(DELETE FROM hrp_petrols WHERE booth_uid = %d, PetrolData(gameid)(bUID))
	
	PetrolData(gameid)(bUID) = 0
	PetrolData(gameid)(bOwner) = 0
	PetrolData(gameid)(bPosX) = 0.0
	PetrolData(gameid)(bPosY) = 0.0
	PetrolData(gameid)(bPosZ) = 0.0
	PetrolData(gameid)(bRadius) = 0.0
	
	Itter_Remove(Petrols, gameid)
	return 1
)

public SavePetrol(gameid)
(
	mysql_query_format(UPDATE hrp_petrols SET petrol_owner = %d, petrol_posx = %f, petrol_posy = %f, petrol_posz = %f, petrol_radius = %f WHERE petrol_uid = %d,
		PetrolData(gameid)(bOwner),
		PetrolData(gameid)(bPosX),
		PetrolData(gameid)(bPosY),
		PetrolData(gameid)(bPosZ),
		PetrolData(gameid)(bRadius),
		PetrolData(gameid)(bUID))
		
	return 1
)

public LoadPetrols()
(
	gameid, data(128)
	mysql_query(SELECT * FROM hrp_petrols)

 	print((load) Rozpoczynam proces wczytywania cpnow z bazy danych...)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		gameid = Itter_Free(Petrols)
		
		sscanf(data, p(|)ddffff,
		PetrolData(gameid)(bUID),
		PetrolData(gameid)(bOwner),

		PetrolData(gameid)(bPosX),
		PetrolData(gameid)(bPosY),
		PetrolData(gameid)(bPosZ),
		PetrolData(gameid)(bRadius))

		Itter_Add(Petrols, gameid)
	)
	mysql_free_result()

	printf((load) Wczytano %d cpnow z bazy danych., gameid)
	return 1
)

