public CreateAnn(group_uid, author_uid, content())
(
	mysql_query_format(INSERT INTO hrp_ann (ann_group, ann_author, ann_content) VALUES (%d, %d, %s), group_uid, author_uid, content)

	uid = mysql_insert_id()
	return uid
)

stock getLastAnn(group_uid, skip_author = false)
(
	data(512), a_content(256), a_author_name(32)
	mysql_query_format(SELECT c.char_name, a.ann_content FROM hrp_ann as a LEFT JOIN hrp_characters as c ON a.ann_author = c.char_uid WHERE a.ann_group = %d ORDER BY a.ann_uid DESC LIMIT 1, group_uid)
	
	mysql_store_result()
	num = mysql_num_rows()
	if(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)s(32)s(255), a_author_name, a_content)
	)
	mysql_free_result()
	
	format(data, sizeof(data), )
	
	if(num != 0)
	(
		if(!skip_author)
		(
			format(data, sizeof(data), %s \nAutor: %s, a_content, a_author_name)
		)
		else
		(
			format(data, sizeof(data), %s, a_content)	
		)
	)
	return data
)

stock GetPlayerAnns(playerid)
(
	if(IsPlayerInAnyGroup(playerid))
	(
		for(i = 0  i ( MAX_GROUP_SLOTS i++)
		(
			if(PlayerGroup(playerid)(i)(gUID))
			(
				msg(256)
				if(strlen(getLastAnn(PlayerGroup(playerid)(i)(gUID), true)) ) 1)
				(
					format(msg,sizeof(msg),#%i Aktualne og³oszenie w grupie %s,i+1,GroupData(GetGroupID(PlayerGroup(playerid)(i)(gUID)))(gName))
					SendClientMessage(playerid,COLOR_RED,msg)
					
					format(msg,sizeof(msg),Treœæ: %s,getLastAnn(PlayerGroup(playerid)(i)(gUID), false))
					SendClientMessage(playerid,COLOR_ORANGE,msg)

					group_id_fix = PlayerGroup(playerid)(i)(gID)
					format(msg, sizeof(msg), (%s): %s, GroupData(group_id_fix)(gTag), getLastAnn(GroupData(group_id_fix)(gUID), true))
				) else (
					group_id_fix = PlayerGroup(playerid)(i)(gID)
					format(msg, sizeof(msg), (%s): Brak ogloszen, GroupData(group_id_fix)(gTag))
				)

				EscapePL(msg)
				PlayerTextDrawSetString(playerid, LSPad_Calendar(i), msg)
			) else (
				msg(4)
				format(msg, sizeof(msg),  )
				PlayerTextDrawSetString(playerid, LSPad_Calendar(i), msg)
			)
		)
	)
	for(i = 0  i ( MAX_GROUP_SLOTS i++)
	(
		if(PlayerGroup(playerid)(i)(gUID))
		(
			if(IsPlayerPermissedGroup(playerid, PlayerGroup(playerid)(i)(gUID), PERM_LEADER))
			(
				group_id_fix = GetGroupID(PlayerGroup(playerid)(i)(gUID))
				if(GroupData(group_id_fix)(gType) == GROUP_CRIMINAL)
				(
					buffer(256), data(512), msg(256), message(128)
					mysql_query_format(SELECT message FROM hrp_groups_messages WHERE group_uid = %d OR group_uid = 0, PlayerGroup(playerid)(i)(gUID))
					mysql_store_result()
					while(mysql_fetch_row(data, |))
					(
						sscanf(data, p(|)s(128), message)
						format(msg, sizeof(msg), (SMS) 504227: %s, message)
						SendClientMessage(playerid, COLOR_YELLOW, msg)
						if(PlayerCache(playerid)(pSex) == 1) 
							format(buffer, sizeof(buffer), * %s otrzyma³ SMS-a., PlayerName(playerid))
						else
							format(buffer, sizeof(buffer), * %s otrzyma³a SMS-a., PlayerName(playerid))
						ProxDetector(10.0, playerid, buffer, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
					)
					mysql_free_result()
				)
			)
		)
	)
	return 1
)