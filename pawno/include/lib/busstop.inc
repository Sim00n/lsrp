public CreateBusStop(BusName(32), Float:BusPosX, Float:BusPosY, Float:BusPosZ)
(
	string(64)
	mysql_query_format(INSERT INTO hrp_busstops (busstop_name, busstop_posx, busstop_posy, busstop_posz) VALUES (%s, %f, %f, %f), BusName, BusPosX, BusPosY, BusPosZ)

	busstop_uid = mysql_insert_id()
	busstop_id = GetFreeBusStopID()

	BusStopData(busstop_id)(bUID) = busstop_uid
	strmid(BusStopData(busstop_id)(bName), BusName, 0, strlen(BusName), 32)
	BusStopData(busstop_id)(bPosX) = BusPosX
	BusStopData(busstop_id)(bPosY) = BusPosY
	BusStopData(busstop_id)(bPosZ) = BusPosZ

	format(string, sizeof(string), Przystanek nr %d:\n%s., busstop_id, BusName)
	BusStopData(busstop_id)(bNameTag) = CreateDynamic3DTextLabel(string, COLOR_LIGHTBLUE, BusPosX, BusPosY, BusPosZ, 15.0)

	return busstop_id
)

public LoadBusStops()
(
	data(128), string(64), busstop_id = 0
	mysql_query(SELECT * FROM hrp_busstops)
	
	print((load) Rozpoczynam proces wczytywania wszystkich przystanków z bazy...)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		busstop_id++

		sscanf(data, p(|)ds(32)fff,
		BusStopData(busstop_id)(bUID),
		BusStopData(busstop_id)(bName),
		
		BusStopData(busstop_id)(bPosX),
		BusStopData(busstop_id)(bPosY),
		BusStopData(busstop_id)(bPosZ))

		format(string, sizeof(string), Przystanek nr %d:\n%s., busstop_id, BusStopData(busstop_id)(bName))
		BusStopData(busstop_id)(bNameTag) = CreateDynamic3DTextLabel(string, COLOR_LIGHTBLUE, BusStopData(busstop_id)(bPosX), BusStopData(busstop_id)(bPosY), BusStopData(busstop_id)(bPosZ), 15.0)
	)
	mysql_free_result()
	
	printf((load) Wczytano %d przystanki/ów z bazy danych., busstop_id)
	return 1
)

public SaveBusStop(busstop_id)
(
	mysql_query_format(UPDATE hrp_busstops SET busstop_name = %s, busstop_posx = %f, busstop_posy = %f, busstop_posz = %f WHERE busstop_uid = %d LIMIT 1,
	BusStopData(busstop_id)(bName),
	
	BusStopData(busstop_id)(bPosX),
	BusStopData(busstop_id)(bPosY),
	BusStopData(busstop_id)(bPosZ),
	
	BusStopData(busstop_id)(bUID))
	return 1
)

public DeleteBusStop(busstop_id)
(
	mysql_query_format(DELETE FROM hrp_busstops WHERE busstop_uid = %d LIMIT 1, BusStopData(busstop_id)(bUID))

	BusStopData(busstop_id)(bUID) = 0
	BusStopData(busstop_id)(bPosX) = 0
	BusStopData(busstop_id)(bPosY) = 0
	BusStopData(busstop_id)(bPosZ) = 0

	DestroyDynamic3DTextLabel(Text3D:BusStopData(busstop_id)(bNameTag))
	return 1
)