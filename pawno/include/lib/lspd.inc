stock showDataFor(playerid, _record_id)
(
	data(128), string(512), counter = 0, num
	mysql_query_format(SELECT * FROM lspd_record WHERE record = %d, _record_id)

	mysql_store_result()
	num = mysql_num_rows()
	if(num != 0)
	(
		while(mysql_fetch_row(data, |))
		(
			record_id, record_record, record_name(32), record_data(255)
			sscanf(data, p(|)dds(32)s(255), record_id, record_record, record_name, record_data)
			if(counter + 1 == num)
			(
				format(string, sizeof(string), %s%d - %s, string, record_id, record_name)
			)
			else
			(
				format(string, sizeof(string), %s%d - %s\n, string, record_id, record_name)
			)
			counter++
		)
	)
	mysql_free_result()
	
	format(string, sizeof(string), %s\n0 - Dodaj nowy, string)
	ShowPlayerDialog(playerid, D_PD_C_LIST, DIALOG_STYLE_LIST, LSPD )) Kartoteka, string, OK, Anuluj)
	return 1
)

stock showDataForRecord(playerid, _record_id)
(
	data(128), string(512), record_id, record_record, record_name(32), record_data(255)
	mysql_query_format(SELECT * FROM lspd_record WHERE id = %d LIMIT 1, _record_id)

	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)dds(32)s(255), record_id, record_record, record_name, record_data)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, LSPD )) Kartoteka, Nie znaleziono takiego wpisu., OK, )
	)
	mysql_free_result()
	
	format(string, sizeof(string), %s\n-----------------------------------------------------------\n%s, record_name, record_data)
	ShowPlayerDialog(playerid, D_PD_C_RECORD, DIALOG_STYLE_MSGBOX, LSPD )) Kartoteka, string, OK, )
	return 1
)

stock ShowPlayerMansions(playerid, giveplayer_id)
(
	return 1
)

stock ShowPlayerVehiclesList(playerid, giveplayer_id)
(
	buffer(256)
	format(buffer, sizeof(buffer), SELECT car_uid, car_name, car_color1, car_color2 FROM hrp_cars WHERE car_owner = %d AND car_register = 1, PlayerCache(playerid)(pUID))
	mysql_query(buffer)
	mysql_store_result()
	
	uid, name(64), c1, c2, clist(512)
	while(mysql_fetch_row(buffer, |))
	(
		sscanf(buffer, p(|)ds(64)dd, uid, name, c1, c2)
		format(clist, sizeof(clist), %s\n%s - LS%d (%d/%d), clist, name, uid, c1, c2)
	)
	mysql_free_result()
	
	if(!strlen(clist))
	(
		GuiMsg(giveplayer_id, Nie znaleziono żadnych pojazdów zarejestrowanych w urzędzie miasta., 1)
		return 1
	)
	
	ShowPlayerDialog(giveplayer_id, D_INFO, DIALOG_STYLE_LIST, Lista zarejestrowanych pojazdów, clist, OK, )
	return 1
)