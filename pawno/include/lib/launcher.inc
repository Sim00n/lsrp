stock LogPlayerByLauncher(playerid)
(
	IP(16)
	GetPlayerIp(playerid, IP, sizeof(IP))
	
	CheckBans(playerid)
	
	buffer(256), time, gid
	format(buffer, sizeof(buffer), SELECT auth_time, auth_gid FROM hrp_auth WHERE auth_ip = %s, IP)
	mysql_query(buffer)
	
	mysql_store_result()
	if(mysql_fetch_row(buffer, |))
	(
		sscanf(buffer, p(|)dd, time, gid)
	)
	mysql_free_result()
	
	format(buffer, sizeof(buffer), SELECT char_uid, char_name FROM hrp_characters WHERE char_gid = %d, gid)
	mysql_query(buffer)
	mysql_store_result()
	char_list(1024), char_name(32), char_uid
	while(mysql_fetch_row(buffer, |))
	(
		sscanf(buffer, p(|)ds(32), char_uid, char_name)
		
		format(char_list, sizeof(char_list), %s\n%s, char_list, char_name)
	)
	mysql_free_result()
	
	// Poka¿ postacie mo¿liwe do zalogowania
	ShowPlayerDialog(playerid, D_LAUNCH_SELECT_CHAR, DIALOG_STYLE_LIST, Wybierz postaæ, char_list, Wybierz, Anuluj)
	PlayerCache(playerid)(pLauncherLogged) = true
	
	// Reszta
	TogglePlayerSpectating(playerid, true)
	mysql_query_format(DELETE FROM hrp_auth WHERE auth_ip = %s, IP)
	initializePlayerTextDraws(playerid)	
	InitLSPadTDForPlayer(playerid)
	SetThirdPerson(playerid, 1)
	return 1
)

stock IsLauncherLog(playerid)
(
	IP(16)
	GetPlayerIp(playerid, IP, sizeof(IP))
	
	buffer(256)
	format(buffer, sizeof(buffer), SELECT auth_time, auth_gid FROM hrp_auth WHERE auth_ip = %s AND auth_time ) %d, IP, gettime())
	mysql_query(buffer)
	
	mysql_store_result()
	if(mysql_num_rows() ) 0)
	(
		mysql_free_result()
		return 1
	)
	else
	(
		mysql_free_result()
		return 0
	)
)