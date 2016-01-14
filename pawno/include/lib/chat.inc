public OnPlayerText(playerid, text())
(
	if(!Logged(playerid) || !Spawned(playerid))
	(
		return 0
	)
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podczas stanu nieprzytomnoœci nie mo¿esz siê odzywaæ., OK, )
		return 0
	)
	if(PlayerCache(playerid)(pAJ))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz siê tutaj odezwaæ., OK, )
		return 0
	)
	if(isnull(text))
	(
		return 0
	)
	string(256)
	
	// Grupy - czat OOC
	
	if(text(0) == @)
	(
		group_slot = INVALID_SLOT_ID, chat_title(128)
		pos = strfind(text,  , true) + 1
		
		if(text(1) == @)
		(
			strmid(chat_title, text, pos, strlen(text))
			strdel(text, pos, strlen(text))

			if(isnull(chat_title))
			(
				SendClientMessage(playerid, COLOR_GREY, Aby pos³ugiwaæ siê czatem OOC podgrupy, poprzedŸ numer slotu znakami @@ a nastêpnie wpisz treœæ wiadomoœci.)
				SendClientMessage(playerid, COLOR_GREY, Przyk³ad: @@1 Witam! Skrypt automatycznie pobiera slot ostatnio u¿ywanego czatu, wiêc dalej nie musisz go definiowaæ.)
				return 0
			)

			if(text(2) !=  )	group_slot = strval(text(2)) - 1
			else	group_slot = PlayerCache(playerid)(pMainGroupSlot) - 1

			if(group_slot ( 0 || group_slot )= MAX_GROUP_SLOTS)
			(
				GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
	   			return 0
			)
			if(!PlayerGroup(playerid)(group_slot)(gUID))
			(
	  			GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
				return 0
			)
			if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_CHAT))
			(
				GameTextForPlayer(playerid, ~r~Brak uprawnien do pisania na czacie., 3000, 3)
				return 0
			)
			group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
			if(GroupData(group_id_fix)(gType) == GROUP_FAMILY)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ta grupa nie ma dostêpu do czatu OOC., OK, )
				return 1
			)
			if(GroupData(group_id_fix)(gToggleChat))
			(
				GameTextForPlayer(playerid, ~r~Czat ~w~OOC ~r~grupy zostal wylaczony., 3000, 3)
				return 0
			)
			chat_title(0) = chrtoupper(chat_title(0))
			
			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					
					if(IsPlayerInGroup(i, GroupData(group_id_fix)(gUID)))
					(
 						PlayerCache(i)(pMainGroupSlot) = GetPlayerGroupSlot(i, GroupData(group_id_fix)(gUID)) + 1

						format(string, sizeof(string), (@@%d %s): (( %s (%d): %s )), PlayerCache(i)(pMainGroupSlot), GroupData(group_id_fix)(gTag), PlayerRealName(playerid), playerid, chat_title)
						SendClientMessage(i, ColorFade(GroupData(group_id_fix)(gColor), 7, 10), string)
					)
					else if(GroupData(group_id_fix)(gOwner) && IsPlayerInGroup(i, GroupData(group_id_fix)(gOwner)))
					(
						PlayerCache(i)(pMainGroupSlot) = GetPlayerGroupSlot(i, GroupData(group_id_fix)(gOwner)) + 1
					
						format(string, sizeof(string), (@@%d %s): (( %s (%d): %s )), PlayerCache(i)(pMainGroupSlot), GroupData(group_id_fix)(gTag), PlayerRealName(playerid), playerid, chat_title)
						SendClientMessage(i, ColorFade(GroupData(group_id_fix)(gColor), 7, 10), string)
					)
					else
					(
						for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
						(
							if(PlayerGroup(i)(slot)(gUID))
							(
								if(GroupData(PlayerGroup(i)(slot)(gID))(gOwner) == GroupData(group_id_fix)(gUID))
								(
	 								PlayerCache(i)(pMainGroupSlot) = slot + 1

									format(string, sizeof(string), (@@%d %s): (( %s (%d): %s )), PlayerCache(i)(pMainGroupSlot), GroupData(group_id_fix)(gTag), PlayerRealName(playerid), playerid, chat_title)
									SendClientMessage(i, ColorFade(GroupData(group_id_fix)(gColor), 7, 10), string)
									break
								)
							)
						)
					)
				)
			)
		)
		else
		(
  			strmid(chat_title, text, pos, strlen(text))
			strdel(text, pos, strlen(text))

			if(isnull(chat_title))
			(
				SendClientMessage(playerid, COLOR_GREY, Aby pos³ugiwaæ siê czatem OOC grupy, poprzedŸ numer slotu znakiem @ a nastêpnie wpisz treœæ wiadomoœci.)
				SendClientMessage(playerid, COLOR_GREY, Przyk³ad: @1 Witam! Skrypt automatycznie pobiera slot ostatnio u¿ywanego czatu, wiêc dalej nie musisz go definiowaæ.)
				return 0
			)

			if(text(1) !=  )	group_slot = strval(text(1)) - 1
			else	group_slot = PlayerCache(playerid)(pMainGroupSlot) - 1
			
			if(group_slot ( 0 || group_slot )= MAX_GROUP_SLOTS)
			(
				GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
	   			return 0
			)
			if(!PlayerGroup(playerid)(group_slot)(gUID))
			(
	  			GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
				return 0
			)
			if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_CHAT))
			(
				GameTextForPlayer(playerid, ~r~Brak uprawnien do pisania na czacie., 3000, 3)
				return 0
			)
			group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
			if(GroupData(group_id_fix)(gToggleChat))
			(
				GameTextForPlayer(playerid, ~r~Czat ~w~OOC ~r~grupy zostal wylaczony., 3000, 3)
				return 0
			)
			chat_title(0) = chrtoupper(chat_title(0))

			foreach(Player, i)
			(
				if(PlayerCache(i)(pTogOOC))
				(
					continue
				)
				if(Logged(i) && Spawned(i))
				(
					if(IsPlayerInGroup(i, GroupData(group_id_fix)(gUID)))
					(
	 					PlayerCache(i)(pMainGroupSlot) = GetPlayerGroupSlot(i, GroupData(group_id_fix)(gUID)) + 1

						format(string, sizeof(string), (@%d %s): (( %s (%d): %s )), PlayerCache(i)(pMainGroupSlot), GroupData(group_id_fix)(gTag), PlayerRealName(playerid), playerid, chat_title)
						SendClientMessage(i, ColorFade(GroupData(group_id_fix)(gColor), 7, 10), string)
					)
				)
			)
		)
		return 0
	)

	// Grupy - czat IC
	if(text(0) == !)
	(
 		group_slot = INVALID_SLOT_ID, chat_title(128)
 		pos = strfind(text,  , true) + 1
 		
		if(text(1) == !)
		(
  			strmid(chat_title, text, pos, strlen(text))
			strdel(text, pos, strlen(text))

			if(isnull(chat_title))
			(
				SendClientMessage(playerid, COLOR_GREY, Aby pos³ugiwaæ siê czatem IC podgrupy, poprzedŸ numer slotu znakami !! a nastêpnie wpisz treœæ wiadomoœci.)
				SendClientMessage(playerid, COLOR_GREY, Przyk³ad: !!1 Zg³aszam siê. Skrypt automatycznie pobiera slot ostatnio u¿ywanego czatu, wiêc dalej nie musisz go definiowaæ.)
				return 0
			)

			if(text(2) !=  )	group_slot = strval(text(2)) - 1
			else	group_slot = PlayerCache(playerid)(pMainGroupSlot) - 1

			if(group_slot ( 0 || group_slot )= MAX_GROUP_SLOTS)
			(
				GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
	   			return 0
			)
			if(!PlayerGroup(playerid)(group_slot)(gUID))
			(
	  			GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
				return 0
			)
			if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_CHAT))
			(
				GameTextForPlayer(playerid, ~r~Brak uprawnien do pisania na czacie., 3000, 3)
				return 0
			)
			group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
			if(!GroupTypeInfo(GroupData(group_id_fix)(gType))(gChatIC))
			(
				GameTextForPlayer(playerid, ~r~Ten typ grupy nie ma dostepu do czatu IC., 3000, 3)
				return 0
			)
			chat_title(0) = chrtoupper(chat_title(0))

			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					if(IsPlayerInGroup(i, GroupData(group_id_fix)(gUID)))
					(
 						PlayerCache(i)(pMainGroupSlot) = GetPlayerGroupSlot(i, GroupData(group_id_fix)(gUID)) + 1

						format(string, sizeof(string), !!%d ** (%s): %s: %s **, PlayerCache(i)(pMainGroupSlot), GroupData(group_id_fix)(gTag), PlayerName(playerid), chat_title)
						SendClientMessage(i, GroupData(group_id_fix)(gColor), string)
					)
					else if(GroupData(group_id_fix)(gOwner) && IsPlayerInGroup(i, GroupData(group_id_fix)(gOwner)))
					(
						PlayerCache(i)(pMainGroupSlot) = GetPlayerGroupSlot(i, GroupData(group_id_fix)(gOwner)) + 1

						format(string, sizeof(string), !!%d ** (%s): %s: %s **, PlayerCache(i)(pMainGroupSlot), GroupData(group_id_fix)(gTag), PlayerName(playerid), chat_title)
						SendClientMessage(i, GroupData(group_id_fix)(gColor), string)
					)
					else
					(
						for (slot = 0 slot ( MAX_GROUP_SLOTS slot++)
						(
							if(PlayerGroup(i)(slot)(gUID))
							(
								if(GroupData(PlayerGroup(i)(slot)(gID))(gOwner) == GroupData(group_id_fix)(gUID))
								(
	 								PlayerCache(i)(pMainGroupSlot) = slot + 1

									format(string, sizeof(string), !!%d ** (%s): %s: %s **, PlayerCache(i)(pMainGroupSlot), GroupData(group_id_fix)(gTag), PlayerName(playerid), chat_title)
									SendClientMessage(i, GroupData(group_id_fix)(gColor), string)
									break
								)
							)
						)
					)
				)
			)
			format(string, sizeof(string), %s mówi (radio): %s, PlayerName(playerid), chat_title)
			ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
		)
		else
		(
  			strmid(chat_title, text, pos, strlen(text))
			strdel(text, pos, strlen(text))

			if(isnull(chat_title))
			(
				SendClientMessage(playerid, COLOR_GREY, Aby pos³ugiwaæ siê czatem IC grupy, poprzedŸ numer slotu znakiem ! a nastêpnie wpisz treœæ wiadomoœci.)
				SendClientMessage(playerid, COLOR_GREY, Przyk³ad: !1 Zg³aszam siê. Skrypt automatycznie pobiera slot ostatnio u¿ywanego czatu, wiêc dalej nie musisz go definiowaæ.)
				return 0
			)

			if(text(1) !=  )	group_slot = strval(text(1)) - 1
			else	group_slot = PlayerCache(playerid)(pMainGroupSlot) - 1

			if(group_slot ( 0 || group_slot )= MAX_GROUP_SLOTS)
			(
				GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
	   			return 0
			)
			if(!PlayerGroup(playerid)(group_slot)(gUID))
			(
	  			GameTextForPlayer(playerid, ~r~Nieprawidlowy slot grupy., 3000, 3)
				return 0
			)
			if(!(PlayerGroup(playerid)(group_slot)(gPerm) & PERM_CHAT))
			(
				GameTextForPlayer(playerid, ~r~Brak uprawnien do pisania na czacie., 3000, 3)
				return 0
			)
			group_id_fix = PlayerGroup(playerid)(group_slot)(gID)
			if(!GroupTypeInfo(GroupData(group_id_fix)(gType))(gChatIC))
			(
				GameTextForPlayer(playerid, ~r~Ten typ grupy nie ma dostepu do czatu IC., 3000, 3)
				return 0
			)
			chat_title(0) = chrtoupper(chat_title(0))

			Float:Pos(3)
			GetPlayerPos(playerid, Pos(0), Pos(1), Pos(2))
			
			foreach(Player, i)
			(
				if(Logged(i) && Spawned(i))
				(
					if(IsPlayerInGroup(i, GroupData(group_id_fix)(gUID)))
					(
	 					PlayerCache(i)(pMainGroupSlot) = GetPlayerGroupSlot(i, GroupData(group_id_fix)(gUID)) + 1

						format(string, sizeof(string), !%d ** (%s): %s: %s **, PlayerCache(i)(pMainGroupSlot), GroupData(group_id_fix)(gTag), PlayerName(playerid), chat_title)
						SendClientMessage(i, GroupData(group_id_fix)(gColor), string)
						PlayCrimeReportForPlayer(playerid, 0, 3)
					)
					else if (IsPlayerInRangeOfPoint(i, 10.0, Pos(0), Pos(1), Pos(2)) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
					(
						PlayCrimeReportForPlayer(playerid, 0, 3)
					)
				)
			)
			format(string, sizeof(string), %s mówi (radio): %s, PlayerName(playerid), chat_title)
			ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
		)
		return 0
	)
	
	if(text(0) == )
	(
		cmd_adminmode(playerid, )
		return 0
	)
	
	if(text(0) == .)
	(
		if(PlayerCache(playerid)(pWoundedTime) ) 0)
		(
			GameTextForPlayer(playerid, Nie buguj frajerze!, 3000, 1)
			return 0
		)
		bool: found = false
		for(anim_id = 1 anim_id ( MAX_ANIMATIONS anim_id++)
		(
			if(!isnull(AnimInfo(anim_id)(aCommand)))
			(
				if(!strcmp(text, AnimInfo(anim_id)(aCommand), true))
				(
					if(AnimInfo(anim_id)(aAction) == 0)
					(
						ApplyAnimation(playerid, AnimInfo(anim_id)(aLib), AnimInfo(anim_id)(aName), AnimInfo(anim_id)(aSpeed), AnimInfo(anim_id)(aOpt1), AnimInfo(anim_id)(aOpt2), AnimInfo(anim_id)(aOpt3), AnimInfo(anim_id)(aOpt4), AnimInfo(anim_id)(aOpt5), 1)
					)
					else
					(
						SetPlayerSpecialAction(playerid, AnimInfo(anim_id)(aAction))
					)
					PlayerCache(playerid)(pPlayAnim) = true
					found = true
				)
			)
		)
		if(!found) PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0)
		return 0
	)
	text(0) = chrtoupper(text(0))
	
	if(PlayerCache(playerid)(pCall) != -1)
	(
		callid = PlayerCache(playerid)(pCall)

		if(Call(callid)(caller) == INVALID_PLAYER_ID || Call(callid)(called) == INVALID_PLAYER_ID)
		(
			if(Call(callid)(calledNumber) == 991 || Call(callid)(calledNumber) == 333 || Call(callid)(calledNumber) == 777 || Call(callid)(calledNumber) == 444)
			(
				EndCall(callid)
				return 0
			)
		)
		else
		(
			if(Call(callid)(convo))
			(
				otherid = (Call(callid)(caller) == playerid)? Call(callid)(called) : Call(callid)(caller)
				
				if(PlayerCache(playerid)(pSex) == 2)
				(
					// Przez telefon mówi kobieta
					format(string, sizeof(string), (Telefon) (G³os damski): %s, text)
				)
				else
				(
					// Przez telefon mówi facet
					format(string, sizeof(string), (Telefon) (G³os mêski): %s, text)
				)
				SendClientMessage(otherid, COLOR_YELLOW, string)
				
		   		format(string, sizeof(string), %s (telefon): %s, PlayerName(playerid), text)
		  		ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
		  		return 0
			)
		)
	)
	
	if(PlayerCache(playerid)(pGagged) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid,Nie mo¿esz nic mówiæ maj¹c knebel w ustach.,1)
		if(PlayerCache(playerid)(pSex) == 1)
		(
			format(string, sizeof(string), * %s próbuje coœ wykrztusiæ przez knebel wciœniêty w jego usta., PlayerName(playerid))
		)
		else
		(
			format(string, sizeof(string), * %s próbuje coœ wykrztusiæ przez knebel wciœniêty w jej usta., PlayerName(playerid))
		)
		
		ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)
		
		return 0
	)
	
	if(PlayerCache(playerid)(pLive))
	(
		sub(128), group_id_fix = GetPlayerDutyGroupID(playerid), radioslot = GetRadioSlot(group_id_fix)
		memcpy(sub, text, 0, 128 * 4)
		
		/*
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) == GROUP_NEWS)
		(
			GroupData(group_id_fix)(gCash) += strlen(text)
		)
		*/
		
		EscapePL(sub)
		
		format(string, sizeof(string), %s ~)~ ~p~~h~Na zywo - %s: ~w~%s, GroupData(group_id_fix)(gTag), PlayerName(playerid), FormatTextDrawColors(sub))
		TextDrawSetString(Text:TextDrawRadio(radioslot), string)
		return 0
	)
	
	if(PlayerCache(playerid)(pStationLive))
	(
		sub(128), group_id_fix = GetPlayerDutyGroupID(playerid)
		memcpy(sub, text, 0, 128 * 4)	
		EscapePL(sub)
		format(string, sizeof(string), %s ~)~ ~p~~h~Na zywo - %s: ~w~%s, GroupData(group_id_fix)(gTag), PlayerName(playerid), FormatTextDrawColors(sub))
			
		for(i = 0  i ( MAX_PLAYERS i++)
		(
			if(PlayerCache(i)(pStation) == GroupData(group_id_fix)(gUID))
			(
		//		TextDrawSetString(i, TextDrawRadio(i), string)
			)
		)
		return 0
	)
	
	if(PlayerCache(playerid)(pInterview) != INVALID_PLAYER_ID)
	(
		sub(128), radioslot = PlayerCache(playerid)(pInterviewSlot)
		memcpy(sub, text, 0, 128 * 4)
		
		/*
		group_id_fix = GetPlayerDutyGroupID(playerid)
		if(GroupData(group_id_fix)(gType) == GROUP_NEWS)
		(
			GroupData(group_id_fix)(gCash) += strlen(text)
		)
		*/
		
		group_id_fix = GetGroupID(RadioData(radioslot)(gUID))
		
		EscapePL(sub)
		
		format(string, sizeof(string), %s ~)~ ~r~~h~Wywiad - %s: ~w~%s, GroupData(group_id_fix)(gTag), PlayerName(playerid), FormatTextDrawColors(sub))
		TextDrawSetString(Text:TextDrawRadio(radioslot), string)
		return 0
	)
	
	if(!strcmp(text, :D, true) || !strcmp(text,  :D, true) || !strcmp(text, :D , true))
	(
		format(string, sizeof(string), * %s œmieje siê., PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 0
	)
	if(!strcmp(text, :), true) || !strcmp(text,  :), true) || !strcmp(text, :) , true))
	(
		format(string, sizeof(string), * %s uœmiecha siê., PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 0
	)
	if(!strcmp(text, :/, true) || !strcmp(text,  :/, true) || !strcmp(text, :/ , true))
	(
		format(string, sizeof(string), * %s krzywi siê., PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 0
	)
	if(!strcmp(text, :O, true) || !strcmp(text,  :O, true) || !strcmp(text, :O , true))
	(
		format(string, sizeof(string), * %s robi zdziwion¹ minê., PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 0
	)
	if(!strcmp(text, :(, true) || !strcmp(text,  :(, true) || !strcmp(text, :( , true))
	(
		format(string, sizeof(string), * %s robi smutn¹ minê., PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 0
	)
	if(!strcmp(text, :P, true) || !strcmp(text,  :P, true) || !strcmp(text, :P , true))
	(
		format(string, sizeof(string), * %s wystawia jêzyk., PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 0
	)
	if(!strcmp(text, ), true) || !strcmp(text,  ), true) || !strcmp(text, ) , true))
	(
		format(string, sizeof(string), * %s puszcza oczko., PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		return 0
	)
	
	if(strlen(text) ( 78)
	(
		
		//format(string, sizeof(string), %s mówi: %s, PlayerName(playerid), text)
		
		format(string, sizeof(string), %s mówi: %s, PlayerName(playerid), text)
		ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
 	)
	else
	(
		pos = strfind(text,  , true, strlen(text) / 2)
		if(pos != -1)
		(
  			text2(64)

  			strmid(text2, text, pos + 1, strlen(text))
			strdel(text, pos, strlen(text))

			format(string, sizeof(string), %s mówi: %s..., PlayerName(playerid), text)
	  		ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)

			format(string, sizeof(string), ...%s, text2)
			ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
		)
	)
	
	// Tutaj boty mo¿na dodaæ.
	botTextHandler(playerid, text)
	
	if(PlayerCache(playerid)(pGymType) || PlayerCache(playerid)(pFish) || PlayerCache(playerid)(pPlayAnim))
	(
		return 0
	)
	
	if(PlayerCache(playerid)(pWoundedTime) == 0)
	(
		ApplyAnimation(playerid, PED, IDLE_CHAT, 4.1, 0, 1, 1, 1, 1, 1)
	)
  	SetTimerEx(KillAnimation, 60 * strlen(text), 0, d, playerid)
	return 0
)

public OnPlayerCommandText(playerid, cmdtext())
(
	if(isnull(cmdtext))
	(
		hrp_Ban(playerid, -1, BugAbusing., 0)
		return 0
	)
	return 0
)

public OnPlayerCommandPerformed(playerid, cmdtext(), success)
(
	printf((cmd) %s: %s (czas wykonania: %d ms), PlayerCache(playerid)(pName), cmdtext, GetTickCount() - CommandTickCount(playerid))
	if(success == 0)
	(
		return PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0)
	)
	else
	(
		return 1
	)
)

public OnPlayerCommandReceived(playerid, cmdtext())
(
	CommandTickCount(playerid) = GetTickCount()
	if(!Logged(playerid) || !Spawned(playerid))
	(
		return 0
	)
	if(!strcmp(cmdtext, /w, true) && !strcmp(cmdtext, /report, true))
	(
		if(PlayerCache(playerid)(pAJ) && PlayerCache(playerid)(pAdmin) == 0)
		(
			return 0
		)
	)
	
	
	return 1
)

stock ProxDetectorDucktape(Float:radi, playerid, string())
(
	foreach(Player, i)
	(
		if(Logged(i) && Spawned(i))
		(
			if(IsPlayerInRangeOfPoint(i, radi, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ)))
			(
				SendClientMessage(i, COLOR_GREY, string)
			)
		)
	)
	return 1
)

public ProxDetector(Float:radi, playerid, string(), col1, col2, col3, col4, col5, bool:skip_windows)
(
	new	Float:PosX, Float:PosY, Float:PosZ,
		WorldID, WorldID2
		
	WorldID = GetPlayerVirtualWorld(playerid)
	GetPlayerPos(playerid, PosX, PosY, PosZ)
	
	SendClientMessage(playerid, col1, string)
		
	foreach(Player, i)
	(
		bool:flag = false
		if(i != playerid)
		(
			if(Logged(i) && Spawned(i))
			(
				if(radi ) 20.0 || skip_windows)
				(
					flag = true
				)
				else
				(
					if(IsPlayerInAnyVehicle(playerid))
					(
						if(IsPlayerInAnyVehicle(i))
						(
							// player - freeway | i - sabre
							playervehid = GetPlayerVehicleID(playerid), ivehid = GetPlayerVehicleID(i)
							if(HasWindow(ivehid))
							(
								if(GetPlayerVehicleID(playerid) == GetPlayerVehicleID(i))
								(
									flag = true
								)
								else
								(
									if(CarInfo(playervehid)(cUID) && CarInfo(ivehid)(cUID))
									(
										if(HasWindow(playervehid))
										(	
											if(CarInfo(playervehid)(cWindowOpen) && CarInfo(ivehid)(cWindowOpen))
											(
												flag = true
											)
										)
										else
										(
											if(CarInfo(ivehid)(cWindowOpen))
											(
												flag = true
											)
										)
									)
								)
							)
							else
							(
								flag = true
							)
						)
						else
						(
							// Specowanie
							if(GetPlayerState(i) == PLAYER_STATE_SPECTATING)
							(
								flag = true
							)
							
							playervehid = GetPlayerVehicleID(playerid)
							if(HasWindow(playervehid))
							(
								if(CarInfo(playervehid)(cUID))
								(
									if(CarInfo(playervehid)(cWindowOpen))
									(
										flag = true
									)
								)
							)
							else
							(
								flag = true
							)
						)
					)
					else
					(
						if(IsPlayerInAnyVehicle(i))
						(
							ivehid = GetPlayerVehicleID(i)
							if(HasWindow(ivehid))
							(
								if(CarInfo(ivehid)(cUID))
								(
									if(CarInfo(ivehid)(cWindowOpen))
									(
										flag = true
									)
								)
							)
							else
							(
								flag = true
							)
						)
						else
						(
							flag = true
						)
					)
				)
				
				if(flag)
				(
					WorldID2 = GetPlayerVirtualWorld(i)

					if(WorldID != WorldID2) continue

					if(IsPlayerInRangeOfPoint(i, radi/16, PosX, PosY, PosZ))
					(
						SendClientMessage(i, col1, string)
					)
					else if(IsPlayerInRangeOfPoint(i, radi/8, PosX, PosY, PosZ))
					(
						SendClientMessage(i, col2, string)
					)
					else if(IsPlayerInRangeOfPoint(i, radi/4, PosX, PosY, PosZ))
					(
						SendClientMessage(i, col3, string)
					)
					else if(IsPlayerInRangeOfPoint(i, radi/2, PosX, PosY, PosZ))
					(
						SendClientMessage(i, col4, string)
					)
					else if(IsPlayerInRangeOfPoint(i, radi, PosX, PosY, PosZ))
					(
						SendClientMessage(i, col5, string)
					)
					flag = false
				)
			)
		)
	)
	return 1
)

forward ProxDetectorAlt(Float:radi, playerid, string(), col1, col2, col3, col4, col5, bool:skip_windows)
public ProxDetectorAlt(Float:radi, playerid, string(), col1, col2, col3, col4, col5, bool:skip_windows)
(
	new	Float:PosX, Float:PosY, Float:PosZ,
		WorldID, WorldID2
		
	WorldID = GetPlayerVirtualWorld(playerid)
	GetPlayerPos(playerid, PosX, PosY, PosZ)
	
	//SendClientMessage(playerid, col1, string)
	toggle = 1
		
	foreach(Player, i)
	(
		bool:flag = false
	//	if(i != playerid)
		if(toggle == 1)
		(
			if(Logged(i) && Spawned(i))
			(
				if(radi ) 20.0 || skip_windows)
				(
					flag = true
				)
				else
				(
					if(IsPlayerInAnyVehicle(playerid))
					(
						if(IsPlayerInAnyVehicle(i))
						(
							// player - freeway | i - sabre
							playervehid = GetPlayerVehicleID(playerid), ivehid = GetPlayerVehicleID(i)
							if(HasWindow(ivehid))
							(
								if(GetPlayerVehicleID(playerid) == GetPlayerVehicleID(i))
								(
									flag = true
								)
								else
								(
									if(CarInfo(playervehid)(cUID) && CarInfo(ivehid)(cUID))
									(
										if(HasWindow(playervehid))
										(	
											if(CarInfo(playervehid)(cWindowOpen) && CarInfo(ivehid)(cWindowOpen))
											(
												flag = true
											)
										)
										else
										(
											if(CarInfo(ivehid)(cWindowOpen))
											(
												flag = true
											)
										)
									)
								)
							)
							else
							(
								flag = true
							)
						)
						else
						(
							playervehid = GetPlayerVehicleID(playerid)
							if(HasWindow(playervehid))
							(
								if(CarInfo(playervehid)(cUID))
								(
									if(CarInfo(playervehid)(cWindowOpen))
									(
										flag = true
									)
								)
							)
							else
							(
								flag = true
							)
						)
					)
					else
					(
						if(IsPlayerInAnyVehicle(i))
						(
							ivehid = GetPlayerVehicleID(i)
							if(HasWindow(ivehid))
							(
								if(CarInfo(ivehid)(cUID))
								(
									if(CarInfo(ivehid)(cWindowOpen))
									(
										flag = true
									)
								)
							)
							else
							(
								flag = true
							)
						)
						else
						(
							flag = true
						)
					)
				)
				
				if(flag)
				(
					WorldID2 = GetPlayerVirtualWorld(i)

					if(WorldID != WorldID2) continue

					if(IsPlayerInRangeOfPoint(i, radi/16, PosX, PosY, PosZ))
					(
						//MakeTextColorMe(string, 0)
						SendClientMessage(i, col1, string)
					)
					else if(IsPlayerInRangeOfPoint(i, radi/8, PosX, PosY, PosZ))
					(
						//MakeTextColorMe(string, 1)
						SendClientMessage(i, col2, string)
					)
					else if(IsPlayerInRangeOfPoint(i, radi/4, PosX, PosY, PosZ))
					(
						//MakeTextColorMe(string, 2)
						SendClientMessage(i, col3, string)
					)
					else if(IsPlayerInRangeOfPoint(i, radi/2, PosX, PosY, PosZ))
					(
						//MakeTextColorMe(string, 3)
						SendClientMessage(i, col4, string)
					)
					else if(IsPlayerInRangeOfPoint(i, radi, PosX, PosY, PosZ))
					(
						//MakeTextColorMe(string, 4)
						SendClientMessage(i, col5, string)
					)
					flag = false
				)
			)
		)
	)
	return 1
)

stock MakeTextColorMe(text(), fade)		//test
(
	applyMe = 0, skip = 0
	for(i = 0  i ( strlen(text) i++)
	(
		if(skip ) 0)
		(
			skip--
			continue
		)
		
		if(text(i) == *)
		(
			if(applyMe == 0)
			(
				strins(text, (C2A2DA), i)
				applyMe = 1
				skip = 9
			)
			else
			(
				switch(fade)
				(
					case 0:
						strins(text, (E6E6E6), i+1)
					case 1:
						strins(text, (C8C8C8), i+1)
					case 2:
						strins(text, (AAAAAA), i+1)
					case 3:
						strins(text, (8C8C8C), i+1)
					case 4:
						strins(text, (6E6E6E), i+1)
				)
				applyMe = 0
			)
		)
	)
)