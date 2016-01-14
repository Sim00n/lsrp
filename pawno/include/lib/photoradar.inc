public AddPhotoRadar(Float:PosX, Float:PosY, Float:PosZ, Float:MaxSpeed)
(
	mysql_query_format(INSERT INTO hrp_photoradars (photoradar_posx, photoradar_posy, photoradar_posz, photoradar_maxspeed) VALUES (%f, %f, %f, %f), PosX, PosY, PosZ, MaxSpeed)

	photoradar_uid = mysql_insert_id()
	photoradar_id = GetFreePhotoRadarID()

	PhotoRadarInfo(photoradar_id)(pUID) = photoradar_uid
	
	PhotoRadarInfo(photoradar_id)(pPosX) = PosX
	PhotoRadarInfo(photoradar_id)(pPosY) = PosY
	PhotoRadarInfo(photoradar_id)(pPosZ) = PosZ
	
	PhotoRadarInfo(photoradar_id)(pMaxSpeed) = MaxSpeed

	return photoradar_id
)

public LoadPhotoRadars()
(
	data(128), photoradar_id = 0
	mysql_query(SELECT * FROM hrp_photoradars)

	print((load) Rozpoczynam proces wczytywania wszystkich fotoradarów z bazy...)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		photoradar_id++

		sscanf(data, p(|)dffff,
		PhotoRadarInfo(photoradar_id)(pUID),
		
		PhotoRadarInfo(photoradar_id)(pPosX),
		PhotoRadarInfo(photoradar_id)(pPosY),
		PhotoRadarInfo(photoradar_id)(pPosZ),
		
		PhotoRadarInfo(photoradar_id)(pMaxSpeed))
	)
	mysql_free_result()

	printf((load) Wczytano %d fotoradary/ów z bazy danych., photoradar_id)
	return 1
)

public SavePhotoRadar(photoradar_id)
(
	mysql_query_format(UPDATE hrp_photoradars SET photoradar_posx = %f, photoradar_posy = %f, photoradar_posz = %f, photoradar_maxspeed = %f WHERE photoradar_uid = %d LIMIT 1,
	PhotoRadarInfo(photoradar_id)(pPosX),
	PhotoRadarInfo(photoradar_id)(pPosY),
	PhotoRadarInfo(photoradar_id)(pPosZ),

	PhotoRadarInfo(photoradar_id)(pMaxSpeed),
	PhotoRadarInfo(photoradar_id)(pUID))
	return 1
)

public DeletePhotoRadar(photoradar_id)
(
	mysql_query_format(DELETE FROM hrp_photoradars WHERE photoradar_uid = %d LIMIT 1, PhotoRadarInfo(photoradar_id)(pUID))

	PhotoRadarInfo(photoradar_id)(pUID) = 0

	PhotoRadarInfo(photoradar_id)(pPosX) = 0
	PhotoRadarInfo(photoradar_id)(pPosY) = 0
	PhotoRadarInfo(photoradar_id)(pPosZ) = 0
	return 1
)