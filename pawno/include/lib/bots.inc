#define BOT_CHAT_COLOR 0xFFCC66FF

public setupBots()
(
	for(i = 0  i ( MAX_PLAYERS i++)
	(
		if(IsPlayerNPC(i))
		(
			npcname(MAX_PLAYER_NAME), string(128)
			GetPlayerName(i, npcname, sizeof(npcname))
			
			// Willard_Fry
			if(!strcmp(npcname, Willard_Fry, true))
			(
				SetPlayerSkin(i, 29)
				format(string, sizeof(string), %s (%d), Willard Fry, i)
				Update3DTextLabelText(Text3D:PlayerCache(i)(pNameTag), PlayerCache(i)(pNickColor), string)
				Attach3DTextLabelToPlayer(Text3D:PlayerCache(i)(pNameTag), i, 0.0, 0.0, 0.2)
				SetPlayerPos(i, 1013.3431,-1369.6055,13.5341)
				SetPlayerFacingAngle(i, 359.2388)
			)
			
			// Michael_Brooks
			if(!strcmp(npcname, Michael_Brooks, true))
			(
				SetPlayerSkin(i, 259)
				format(string, sizeof(string), %s (%d), Michael Brooks, i)
				Update3DTextLabelText(Text3D:PlayerCache(i)(pNameTag), PlayerCache(i)(pNickColor), string)
				Attach3DTextLabelToPlayer(Text3D:PlayerCache(i)(pNameTag), i, 0.0, 0.0, 0.2)
				
				// Czapka
				SetPlayerAttachedObject(i, 1, 19065, 2, 0.100998, 0.018998, 0.015999, 18.1, 83.2, 74.0, 1.211, 1.28, 1.43)
				
				// Prezent do rêki
				//SetPlayerAttachedObject(i, 2, 19054, 5, 0.0, 0.149999, 0.181999, -83.9, -11.3, -86.8, 0.3, 0.278, 0.247999)
			)
			
			// Sasha_Grey
			if(!strcmp(npcname, Sasha_Grey, true))
			(
				SetPlayerSkin(i, 12)
				format(string, sizeof(string), %s (%d), Sasha Grey, i)
				Update3DTextLabelText(Text3D:PlayerCache(i)(pNameTag), PlayerCache(i)(pNickColor), string)
				Attach3DTextLabelToPlayer(Text3D:PlayerCache(i)(pNameTag), i, 0.0, 0.0, 0.2)
			)
			
			// maszynista
			if(!strcmp(npcname, George_Black, true))
			(
				SetPlayerSkin(i, 8)
				format(string, sizeof(string), %s (%d), George Black, i)
				Update3DTextLabelText(Text3D:PlayerCache(i)(pNameTag), PlayerCache(i)(pNickColor), string)
				Attach3DTextLabelToPlayer(Text3D:PlayerCache(i)(pNameTag), i, 0.0, 0.0, 0.2)
			)
			
			// Maverick
			if(!strcmp(npcname, George_Brown, true))
			(
				SetPlayerSkin(i, 284)
				format(string, sizeof(string), %s (%d), George Brown, i)
				Update3DTextLabelText(Text3D:PlayerCache(i)(pNameTag), PlayerCache(i)(pNickColor), string)
				Attach3DTextLabelToPlayer(Text3D:PlayerCache(i)(pNameTag), i, 0.0, 0.0, 0.2)
			)
			
			// Dodo
			if(!strcmp(npcname, George_White, true))
			(
				SetPlayerSkin(i, 61)
				format(string, sizeof(string), %s (%d), George White, i)
				Update3DTextLabelText(Text3D:PlayerCache(i)(pNameTag), PlayerCache(i)(pNickColor), string)
				Attach3DTextLabelToPlayer(Text3D:PlayerCache(i)(pNameTag), i, 0.0, 0.0, 0.2)
			)
		)
	)
	
	return 1
)

// ==========================================
stock botTextHandler(playerid, text())
(
	talked_id = INVALID_PLAYER_ID, Float:distance, current = -1, Float:Pos(3)
	for(i = 0  i ( MAX_PLAYERS i++)
	(
		if(IsPlayerNPC(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
		(
			GetPlayerPos(i, Pos(0), Pos(1), Pos(2))
			if(GetPlayerDistanceFromPoint(playerid, Pos(0), Pos(1), Pos(2)) ( distance || distance == 0.0)
			(
				distance = GetPlayerDistanceFromPoint(playerid, Pos(0), Pos(1), Pos(2))
				current = i
			)
		)
	)
	
	if(current != -1 && distance ( 11.0)
	(
		talked_id = current
	)
	else
	(
		if(PlayerCache(playerid)(pTalkedNPC) != INVALID_PLAYER_ID)
		(
			PlayerCache(playerid)(pTalkedNPC) = INVALID_PLAYER_ID
			PlayerCache(playerid)(pTalkedPhase) = 0
		)
			
		return 1
	)
	
	npcname(MAX_PLAYER_NAME)
	GetPlayerName(talked_id, npcname, sizeof(npcname))
	
	PlayerCache(playerid)(pTalkedNPC) = talked_id
		
	// -------------------------------------------------------------
	if(!strcmp(npcname, Sasha_Grey, true))
	(
		// Angle
		Float:Angle
		GetPlayerFacingAngle(playerid, Angle)
		SetPlayerFacingAngle(talked_id, Angle+180.0)
		
		if (strfind(text, witam, true) != -1 || 
		strfind(text, czesc, true) != -1 || 
		strfind(text, czeœæ, true) != -1 || 
		strfind(text, hej, true) != -1 || 
		strfind(text, siema, true) != -1 || 
		strfind(text, witaj, true) != -1)
		(
			SendClientMessage(playerid, BOT_CHAT_COLOR, Sasha Grey mówi: Czeœæ, chcia³byœ bym da³a Ci dupy?)
			PlayerCache(playerid)(pTalkedPhase) = 1
		)
		
		if (strfind(text, tak, true) != -1 || 
		strfind(text, no, true) != -1 || 
		strfind(text, okej, true) != -1 || 
		strfind(text, pewnie, true) != -1)
		(
			if(PlayerCache(playerid)(pTalkedPhase) == 1)
				SendClientMessage(playerid, BOT_CHAT_COLOR, Sasha Grey mówi: Okej!)
		)
	)
	// -------------------------------------------------------------
	if(!strcmp(npcname, Michael_Brooks, true))
	(
		// Angle
		Float:Angle
		GetPlayerFacingAngle(playerid, Angle)
		SetPlayerFacingAngle(talked_id, Angle+180.0)
		
		if (strfind(text, witam, true) != -1 || 
		strfind(text, czesc, true) != -1 || 
		strfind(text, czeœæ, true) != -1 || 
		strfind(text, hej, true) != -1 || 
		strfind(text, siema, true) != -1 || 
		strfind(text, witaj, true) != -1)
		(
			SendClientMessage(playerid, BOT_CHAT_COLOR, Michael Brooks mówi: Witaj w moim sklepie, jak widzisz *wskazuje na asortyment* znajdziesz u nas odpowiedni)
			SendClientMessage(playerid, BOT_CHAT_COLOR, (...)pomys³ na prezent dla kogoœ znajomego, zapakowaæ jeden?)
			PlayerCache(playerid)(pTalkedPhase) = 1
		)
		
		if(PlayerCache(playerid)(pTalkedPhase) == 1)
		(
			// OpowiedŸ czy by³, czy nie.
			if (strfind(text, tak, true) != -1 || 
			strfind(text, pewnie, true) != -1 || 
			strfind(text, no, true) != -1 || 
			strfind(text, oczywiœcie, true) != -1 || 
			strfind(text, jasne, true) != -1)
			(
				PlayerCache(playerid)(pTalkedPhase) = 2
				SendClientMessage(playerid, BOT_CHAT_COLOR, Michael Brooks mówi: Jeden pakunek kosztuje $500, jesteœ pewien, ¿e chcesz go kupiæ?)
			)
			else if(strfind(text, nie, true) != -1 || 
			strfind(text, raczej, true) != -1 || 
			strfind(text, hmm, true) != -1 )
			(
				SendClientMessage(playerid, BOT_CHAT_COLOR, Michael Brooks mówi: W porz¹dku, wróæ jak zmienisz zdanie.)
			)
		)
		
		if(PlayerCache(playerid)(pTalkedPhase) == 2)
		(
			if (strfind(text, tak, true) != -1 || 
			strfind(text, pewnie, true) != -1 || 
			strfind(text, no, true) != -1 || 
			strfind(text, okej, true) != -1 || 
			strfind(text, oczywiœcie, true) != -1 || 
			strfind(text, jasne, true) != -1)
			(
				if(PlayerCache(playerid)(pCash) ( 500)
				(
					SendClientMessage(playerid, BOT_CHAT_COLOR, Michael Brooks mówi: Przecie¿ nie masz przy sobie tyle pieniêdzy.)
				)
				else
				(
					mysql_query_format(SELECT * FROM hrp_presents WHERE present_gid = %d AND present_action = %d, PlayerCache(playerid)(pGID), 1)
					mysql_store_result()
					if(mysql_num_rows() ) 9)
					(
						mysql_free_result()
						SendClientMessage(playerid, BOT_CHAT_COLOR, Michael Brooks mówi: Och! W³aœnie zabrak³o mi towaru, wróæ póŸniej.)
						return 1
					)
					mysql_free_result()
					
					PlayerCache(playerid)(pTalkedPhase) = 3
					SendClientMessage(playerid, BOT_CHAT_COLOR, Michael Brooks mówi: Proszê bardzo!)
					cmd_me(talked_id, k³adzie zapakowane pude³ko przed klientem.)
					
					hrp_GivePlayerMoney(playerid, -500)
					SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
					
					mysql_query_format(INSERT INTO hrp_presents VALUES(NULL, %d, %d), PlayerCache(playerid)(pGID), 1)
					CreatePlayerItem(playerid, Prezent, ITEM_PRESENT, PlayerCache(playerid)(pGID), 0)
					cmd_me(playerid, podaje pieni¹dze pracownikowi i zgarnia pude³ko ze stolika.)
				)
			)
		)
	)
	// -------------------------------------------------------------
	/*if(!strcmp(npcname, Willard_Fry, true))
	(
		// Angle
		Float:Angle
		GetPlayerFacingAngle(playerid, Angle)
		SetPlayerFacingAngle(talked_id, Angle+180.0)
		
		if (strfind(text, witam, true) != -1 || 
		strfind(text, czesc, true) != -1 || 
		strfind(text, czeœæ, true) != -1 || 
		strfind(text, hej, true) != -1 || 
		strfind(text, siema, true) != -1 || 
		strfind(text, witaj, true) != -1)
		(
			SendClientMessage(playerid, BOT_CHAT_COLOR, Willard Fry mówi: Taa.. Dzieñ dobry, mo¿e chcesz kupiæ los na loteriê?)
			PlayerCache(playerid)(pTalkedPhase) = 1
		)
		
		if(PlayerCache(playerid)(pTalkedPhase) == 1)
		(
			if (strfind(text, tak, true) != -1 || 
			strfind(text, pewnie, true) != -1 || 
			strfind(text, no, true) != -1 || 
			strfind(text, oczywiœcie, true) != -1 || 
			strfind(text, jasne, true) != -1)
			(
				PlayerCache(playerid)(pTalkedPhase) = 2
				SendClientMessage(playerid, BOT_CHAT_COLOR, Willard Fry mówi: Los jest za dziesiêæ dolarów, to jak?)
			)
			else if(strfind(text, nie, true) != -1 || 
			strfind(text, raczej, true) != -1 || 
			strfind(text, hmm, true) != -1 )
			(
				SendClientMessage(playerid, BOT_CHAT_COLOR, Willard Fry mówi: No dobra, to wróæ jak zmienisz zdanie, nie?)
			)
		)
		
		if(PlayerCache(playerid)(pTalkedPhase) == 2)
		(
			if (strfind(text, tak, true) != -1 || 
			strfind(text, pewnie, true) != -1 || 
			strfind(text, no, true) != -1 || 
			strfind(text, biore, true) != -1 || 
			strfind(text, wezmê, true) != -1 || 
			strfind(text, wezme, true) != -1 || 
			strfind(text, chcê, true) != -1 || 
			strfind(text, chce, true) != -1 || 
			strfind(text, oczywiœcie, true) != -1 || 
			strfind(text, jasne, true) != -1)
			(
				if(PlayerCache(playerid)(pCash) ( 10)
				(
					PlayerCache(playerid)(pTalkedPhase) = 3
					SendClientMessage(playerid, BOT_CHAT_COLOR, Willard Fry mówi: Nawet nie masz tyle pieniêdzy, wróæ jak bêdziesz mia³ coœ w portfelu.)
				)
				else
				(
					PlayerCache(playerid)(pTalkedPhase) = 3
					SendClientMessage(playerid, BOT_CHAT_COLOR, Willard Fry mówi: ¯yczê wygranej.)
					
					// Zabierz kasê, dodaj los.
					cmd_me(talked_id, drukuje los, podaje go klientowi.)
					
					hrp_GivePlayerMoney(playerid, -10)
					SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
					
					CreatePlayerItem(playerid, Los na loterie, ITEM_LOSS, 0, 0)
					mysql_query_format(INSERT INTO hrp_lottery VALUES(NULL, %d), PlayerCache(playerid)(pUID))
				)
			)
			else if(strfind(text, nie, true) != -1 || 
			strfind(text, raczej, true) != -1 || 
			strfind(text, hmm, true) != -1 )
			(
				SendClientMessage(playerid, BOT_CHAT_COLOR, Willard Fry mówi: No dobra, to wróæ jak zmienisz zdanie, nie?)
			)
		)
	)*/
	
	return 1
)

// Komendy adminów
// -------------------------------------------------
CMD:spawnbot(playerid, params())
(
	if(PlayerCache(playerid)(pAdmin) != 1)
	(
		GuiMsg(playerid, Brak uprawnieñ do u¿ycia tej komendy., 1)
		return 1
	)
	
	bot_name(32), bot_script(32)
	if(sscanf(params, s(32)s(32), bot_name, bot_script))
	(
		hrp_Tip(playerid, /spawn (Sasha_Grey) (gun))
		return 1
	)
	
	ConnectNPC(bot_name, bot_script)
	sendClientPoop(playerid, » Zespawnowa³eœ bota.)
	
	SetTimer(setupBots, 10000, false)
	return 1
)