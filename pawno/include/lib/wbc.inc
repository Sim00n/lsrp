/*
	funkcje wczytywania wszystkiego w Init
*/

stock LoadNewsboxes()
(
	buffer(256)
	format(buffer,sizeof(buffer),SELECT * FROM wbc_newsboxes)
	mysql_query(buffer)
	mysql_store_result()
	
	gameid = 0
	while(mysql_fetch_row(buffer,|))
	(
		sscanf(buffer,p(|)ifffii,PressBox(gameid)(bUID),PressBox(gameid)(bPosX),PressBox(gameid)(bPosY),PressBox(gameid)(bPosZ),PressBox(gameid)(bVW),PressBox(gameid)(bAmount))
		gameid++
	)
	
	mysql_free_result()
	
	
	count = LoadNewsLabels()
	printf((load) wczytano %i 3d textow dla skrzynek z gazetami,count)
	return 1
)

stock LoadNewsLabels()
(
	count = 0, string(128)
	for(i = 0  i ( MAX_PRESSBOX i++)
	(
		if(PressBox(i)(bUID) != 0)
		(
			format(string, sizeof(string), Budka z gazetami (%d)\n(E85405)(( aby kupiæ gazetê u¿yj komendy /kup ))(FFFFFF), PressBox(i)(bUID))
			PressBox(i)(bText) = CreateDynamic3DTextLabel(string, COLOR_DESC, PressBox(i)(bPosX),PressBox(i)(bPosY),PressBox(i)(bPosZ), 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, PressBox(i)(bVW), 0, -1, 10.0)
			//Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, label_id, E_STREAMER_EXTRA_ID, PressBox(i)(bUID))
			count++
		)
	)
	
	return count
)

stock ReloadNewsboxes()
(
	for(i = 0  i ( MAX_PRESSBOX i++)
	(
		if(IsValidDynamic3DTextLabel(PressBox(i)(bText)))
		(
			DestroyDynamic3DTextLabel(PressBox(i)(bText))
		)
	)
	
	//czyszczenie tablic
	for(i = 0  i ( MAX_PRESSBOX i++)
	(
		PressBox(i)(bUID) = EOS
		PressBox(i)(bPosX) = 0.0
		PressBox(i)(bPosY) = 0.0
		PressBox(i)(bPosZ) = 0.0
		PressBox(i)(bVW) = 0
		PressBox(i)(bAmount) = 0
	)
	
	//force load
	LoadNewsboxes()
	print((reload) przeladowano wszystkie budki z prasa)

	
	return 1
)


/*
	funkcje dotycz¹ce WBC i dodanych dla nich gazet
*/

stock ShowPlayerNewspaper(playerid,itemid)
(
	newsid = ItemInfo(itemid)(iValue1)
	
	buffer(256)
	format(buffer,sizeof(buffer),SELECT news_author, news_title,news_text FROM wbc_press WHERE news_id=%i,newsid)
	mysql_query(buffer)
	mysql_store_result()
	
	if(mysql_num_rows() (= 0 )
	(
		mysql_free_result()
		GuiMsg(playerid,Nie znaleziono takiego wpisu w bazie danych.,1)
		return 1
	)
	else
	(
		while(mysql_fetch_row(buffer,|))
		(
			author(32),title(64),text(2048)
			sscanf(buffer,p(|)s(32)s(64)s(1024),author,title,text)
			format(text,sizeof(text),** Nag³ówek Los Santos Times ** \n\nAutor: %s\nTytu³: %s\n\n%s,author,title,StringFormatForDialog(text))
			
			ShowPlayerDialog(playerid,D_WBC_PRESS,DIALOG_STYLE_MSGBOX,** Egzemplarz gazety Los Santos Times **,text,Schowaj,)
		)
		
		mysql_free_result()
		return 1
	)
)

stock testingShowPlayerNewspaper(playerid,itemid)
(
	newsid = ItemInfo(itemid)(iValue1)
	
	text(2048)
	format(text,sizeof(text),** Nag³ówek Los Santos Times **\n\nAutor: %s\nTytu³: %s \n\n%s,GetNewsAuthor(newsid),GetNewsTitle(newsid),StringFormatForDialog(GetNewsText(newsid)))
	
	
	ShowPlayerDialog(playerid,D_WBC_PRESS,DIALOG_STYLE_MSGBOX,** Egzemplarz gazety Los Santos Times **,text,Schowaj,)
	
	return 1
)

stock InsertNews(playerid,title())
(
	//zapis newsa do bazy
	toSQL(1280)
	mysql_real_escape_string(WBCpress, toSQL)
	
	/*print(toSQL)
	print(WBCpress)
	print(title)*/
	
	buffer(256)
	format(buffer,sizeof(buffer),INSERT INTO wbc_press VALUES (NULL,%s,%i,%s,%s),PlayerName(playerid),gettime(),title,toSQL)
	mysql_query(buffer)
	return 1
)

/*
	podstawowe pobieranie kawa³ków newsa
*/

stock GetLastNewsID()
(
	mysql_query(SELECT MAX(news_id) FROM wbc_press)
	mysql_store_result()
	newsid = mysql_fetch_int()
	mysql_free_result()
	
	return newsid
)

stock GetNewsText(newsid)
(
	buffer(256), text(1024)
	format(buffer,sizeof(buffer),SELECT news_text FROM wbc_press WHERE news_id=%i,newsid)
	mysql_query(buffer)
	mysql_store_result()
	if(mysql_num_rows() (= 0)
	(
		mysql_free_result()
		format(text,sizeof(text),GUWNO)
		return text
	)
	mysql_fetch_string(text)
	mysql_free_result()
	
	return text
)

stock GetNewsTitle(newsid)
(
	buffer(256),text(64)
	format(buffer,sizeof(buffer),SELECT news_title FROM wbc_press WHERE news_id=%i,newsid)
	mysql_query(buffer)
	mysql_store_result()
	
	if(mysql_num_rows() (= 0)
	(
		mysql_free_result()
		format(text,sizeof(text),GUWNO)
		return text
	)
	
	mysql_fetch_string(text)
	mysql_free_result()
	
	return text
)

stock GetNewsAuthor(newsid)
(
	buffer(256),text(32)
	format(buffer,sizeof(buffer),SELECT news_author FROM wbc_press WHERE news_id=%i,newsid)
	mysql_query(buffer)
	mysql_store_result()
	
	if(mysql_num_rows() (= 0)
	(
		mysql_free_result()
		format(text,sizeof(text),GUWNO)
		return text
	)
	
	mysql_fetch_string(text)
	mysql_free_result()
	
	return text
)

stock GetNewsDate(newsid)
(
	buffer(256),stamp
	format(buffer,sizeof(buffer),SELECT news_date FROM wbc_press WHERE news_id=%i,newsid)
	mysql_query(buffer)
	mysql_store_result()
	
	if(mysql_num_rows() (= 0)
	(
		mysql_free_result()
		return 0
	)
	
	stamp = mysql_fetch_int()
	mysql_free_result()
	
	return stamp
)

/*
	funkcje radia
*/