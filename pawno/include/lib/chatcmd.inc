CMD:sz(playerid, params())
(
	giveplayer_id, text(128), string(256)
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podczas stanu nieprzytomnoœci nie mo¿esz szeptaæ., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGagged) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid,Nie mo¿esz mówiæ bêd¹c zakneblowanym.,1)
		return 1
	)
	if(sscanf(params, ds(128), giveplayer_id, text))
	(
		hrp_Tip(playerid, /sz (ID gracza) (Szept))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz szeptaæ do siebie., OK, )
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
 		return 1
	)
	
	text(0) = chrtoupper(text(0))

	if(!PlayerToPlayer(0.8, playerid, giveplayer_id) || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(giveplayer_id))
	(
		GuiMsg(playerid, Szept mo¿esz wysy³aæ tylko na okreœlon¹ odleg³oœæ.\nOsoba, do której chcesz szeptaæ nie jest obok Ciebie., 1)
		return 1
	)
	
	format(string, sizeof(string), * %s szepcze coœ na ucho do %s., PlayerName(playerid), PlayerName(giveplayer_id))
	FlashMe(playerid, string)
	
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), Szepczesz do %s: %s, PlayerName(giveplayer_id), text)
		SendClientMessage(playerid, COLOR_FADE1, string)
		
		format(string, sizeof(string), %s szepcze do ciebie: %s, PlayerName(playerid), text)
		SendClientMessage(giveplayer_id, COLOR_FADE1, string)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
			text2(64)

			strmid(text2, text, pos, strlen(text))
			strdel(text, pos, strlen(text))

			format(string, sizeof(string), Szepczesz do %s: %s..., PlayerName(giveplayer_id), text)
			SendClientMessage(playerid, COLOR_FADE1, string)
			
			format(string, sizeof(string), ...%s, text)
			SendClientMessage(playerid, COLOR_FADE1, string)
			
			
			format(string, sizeof(string), %s szepcze do ciebie: %s..., PlayerName(playerid), text)
			SendClientMessage(giveplayer_id, COLOR_FADE1, string)

			format(string, sizeof(string), ...%s, text)
			SendClientMessage(giveplayer_id, COLOR_FADE1, string)
		)
	)
	
	return 1
)

CMD:szept(playerid, params()) return cmd_sz(playerid, params)

CMD:c(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skorzystaæ teraz z tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGagged) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid,Nie mo¿esz mówiæ bêd¹c zakneblowanym.,1)
		return 1
	)
	if(isnull(params))
	(
	   	hrp_Tip(playerid, /c (Tekst))
		return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))
	
	/*
	// Szukanie gwiazdek do me nad g³ow¹
	firstAstr, secondAstr, mestr(128), newstr1(128), newstr2(128)
	firstAstr = strfind(params, *, false, 0)
	if(firstAstr != -1)
	(
		secondAstr = strfind(params, *, false, firstAstr + 1)
		if(secondAstr != -1)
		(
			// Testowy *string* do testowania.
			// Testowy * do testowania.
		
			strmid(mestr, params, firstAstr+1, secondAstr, sizeof(mestr))
			strmid(newstr1, params, 0, firstAstr, sizeof(newstr1) - 1)
			strmid(newstr2, params, secondAstr+1, strlen(params), sizeof(newstr2))
			format(params, 144, %s%s, newstr1, newstr2)
			if(strlen(mestr) ) 1)
			(
				mestr(0) = chrtoupper(mestr(0))
				strcat(mestr, ., sizeof(mestr))
				SendPlayerMe(playerid, mestr)
			)
		)
	)
	*/
	
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), %s szepcze: %s, PlayerName(playerid), params)
		ProxDetector(5.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), %s szepcze: %s..., PlayerName(playerid), params)
			ProxDetector(5.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)

			format(string, sizeof(string), ...%s, text)
			ProxDetector(5.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
		)
	)
	return 1
)

CMD:k(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skorzystaæ teraz z tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGagged) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid,Nie mo¿esz mówiæ bêd¹c zakneblowanym.,1)
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /k (Tekst))
		return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))
	
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), %s krzyczy: %s!!, PlayerName(playerid), params)
		ProxDetector(25.0, playerid, string, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2, false)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), %s krzyczy: %s..., PlayerName(playerid), params)
			ProxDetector(25.0, playerid, string, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2, false)

			format(string, sizeof(string), ...%s!, text)
			ProxDetector(25.0, playerid, string, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2, false)
		)
	)
	return 1
)

CMD:s(playerid, params()) return cmd_k(playerid, params)
CMD:krzycz(playerid, params()) return cmd_k(playerid, params)

CMD:dk(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skorzystaæ teraz z tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGagged) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid,Nie mo¿esz mówiæ bêd¹c zakneblowanym.,1)
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /dk (Tekst))
		return 1
	)

	string(256)
	params(0) = chrtoupper(params(0))

	foreach(Doors, d)
	(
 		if(DoorData(d)(dUID))
   		(
			if((IsPlayerInRangeOfPoint(playerid, 5.0, DoorData(d)(dEnterX), DoorData(d)(dEnterY), DoorData(d)(dEnterZ)) && GetPlayerVirtualWorld(playerid) == DoorData(d)(dEnterVW)) || (IsPlayerInRangeOfPoint(playerid, 5.0, DoorData(d)(dExitX), DoorData(d)(dExitY), DoorData(d)(dExitZ)) && GetPlayerVirtualWorld(playerid) == DoorData(d)(dExitVW)))
			(
				if(strlen(params) ( 78)
				(
					format(string, sizeof(string), %s krzyczy: %s!!, PlayerName(playerid), params)
					foreach(Player, i)
					(
						if((IsPlayerInRangeOfPoint(i, 20.0, DoorData(d)(dEnterX), DoorData(d)(dEnterY), DoorData(d)(dEnterZ)) && GetPlayerVirtualWorld(i) == DoorData(d)(dEnterVW)) || (IsPlayerInRangeOfPoint(i, 20.0, DoorData(d)(dExitX), DoorData(d)(dExitY), DoorData(d)(dExitZ)) && GetPlayerVirtualWorld(i) == DoorData(d)(dExitVW)))
						(
							SendClientMessage(i, COLOR_WHITE, string)
						)
					)
				)
				else
				(
					pos = strfind(params,  , true, strlen(params) / 2)
					if(pos != -1)
					(
			  			text(64), string2(256)

			  			strmid(text, params, pos + 1, strlen(params))
						strdel(params, pos, strlen(params))

						format(string, sizeof(string), %s krzyczy: %s..., PlayerName(playerid), params)
						format(string2, sizeof(string2), ...%s!!, text)
						
						foreach(Player, i)
						(
							if((IsPlayerInRangeOfPoint(i, 20.0, DoorData(d)(dEnterX), DoorData(d)(dEnterY), DoorData(d)(dEnterZ)) && GetPlayerVirtualWorld(i) == DoorData(d)(dEnterVW)) || (IsPlayerInRangeOfPoint(i, 20.0, DoorData(d)(dExitX), DoorData(d)(dExitY), DoorData(d)(dExitZ)) && GetPlayerVirtualWorld(i) == DoorData(d)(dExitVW)))
							(
								SendClientMessage(i, COLOR_WHITE, string)
								SendClientMessage(i, COLOR_WHITE, string2)
							)
						)
					)
				)
			)
		)
	)
	
	return 1
)

CMD:l(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skorzystaæ teraz z tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGagged) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid,Nie mo¿esz mówiæ bêd¹c zakneblowanym.,1)
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /l (Tekst))
		return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))
	
	/*
	// Szukanie gwiazdek do me nad g³ow¹
	firstAstr, secondAstr, mestr(128), newstr1(128), newstr2(128)
	firstAstr = strfind(params, *, false, 0)
	if(firstAstr != -1)
	(
		secondAstr = strfind(params, *, false, firstAstr + 1)
		if(secondAstr != -1)
		(
			// Testowy *string* do testowania.
			// Testowy * do testowania.
		
			strmid(mestr, params, firstAstr+1, secondAstr, sizeof(mestr))
			strmid(newstr1, params, 0, firstAstr, sizeof(newstr1) - 1)
			strmid(newstr2, params, secondAstr+2, strlen(params), sizeof(newstr2))
			format(params, 144, %s%s, newstr1, newstr2)
			if(strlen(mestr) ) 1)
			(
				mestr(0) = chrtoupper(mestr(0))
				strcat(mestr, ., sizeof(mestr))
				SendPlayerMe(playerid, mestr)
			)
		)
	)
	*/
	
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), %s mówi: %s, PlayerName(playerid), params)
		ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)
  			
  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), %s mówi: %s..., PlayerName(playerid), params)
			ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)

			format(string, sizeof(string), ...%s, text)
			ProxDetector(10.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, false)
		)
	)
	return 1
)

CMD:b(playerid, params())
(
	if(PlayerCache(playerid)(pBlock) & BLOCK_OOC)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Twoja postaæ ma na³o¿on¹ blokadê czatu OOC., OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /b (Tekst))
		return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))
	
	if(strlen(params) ( 78)
	(
		if(!PlayerCache(playerid)(pMaskUID))
		(
			format(string, sizeof(string), (( (%d) %s: %s )), playerid, PlayerGlobalName(playerid, COLOR_GREY), params)
		)
		else
		(
			format(string, sizeof(string), (( %s: %s )), PlayerGlobalName(playerid, COLOR_GREY), params)
		)
		ProxDetector(10.0, playerid, string, COLOR_GREY, COLOR_GREY, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			if(!PlayerCache(playerid)(pMaskUID))
			(
				format(string, sizeof(string), (( (%d) %s: %s..., playerid, PlayerGlobalName(playerid, COLOR_GREY), params)
			)
			else
			(
				format(string, sizeof(string), (( %s: %s..., PlayerGlobalName(playerid, COLOR_GREY), params)
			)
			ProxDetector(10.0, playerid, string, COLOR_GREY, COLOR_GREY, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true)

			format(string, sizeof(string), ...%s )), text)
			ProxDetector(10.0, playerid, string, COLOR_GREY, COLOR_GREY, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true)
		)
	)
	return 1
)

CMD:me(playerid, params())
(
	if(isnull(params))
	(
		hrp_Tip(playerid, /me (Akcja))
		return 1
	)
	string(256)
	params(0) = chrtolower(params(0))
	
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), ** %s %s, PlayerName(playerid), params)
		ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), ** %s %s..., PlayerName(playerid), params)
			ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			
			format(string, sizeof(string), ...%s, text)
			ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		)
	)
	return 1
)

CMD:cme(playerid, params())
(
	if(isnull(params))
	(
		hrp_Tip(playerid, /cme (Akcja))
		return 1
	)
	string(256)
	params(0) = chrtolower(params(0))
	
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), ** %s %s, PlayerName(playerid), params)
		ProxDetector(2.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), ** %s %s..., PlayerName(playerid), params)
			ProxDetector(2.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
			
			format(string, sizeof(string), ...%s, text)
			ProxDetector(2.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)
		)
	)
	return 1
)

CMD:ja(playerid, params()) return cmd_me(playerid, params)

CMD:do(playerid, params())
(
	if(isnull(params))
	(
		hrp_Tip(playerid, /do (Sytuacja))
		return 1
	)
	string(256)
	params(0) = chrtoupper(params(0))

	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), ** %s (( %s )), params, PlayerName(playerid))
		ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), ** %s..., params)
			ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)

			format(string, sizeof(string), ...%s (( %s )), text, PlayerName(playerid))
			ProxDetector(10.0, playerid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
		)
	)
	return 1
)

CMD:w(playerid, params())
(
	giveplayer_id, text(128), string(256)
	if(sscanf(params, ds(128), giveplayer_id, text))
	(
		hrp_Tip(playerid, /w (ID gracza) (Tekst))
		return 1
	)
	if(giveplayer_id == playerid)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wysy³aæ prywatnej wiadomoœci do siebie., OK, )
		return 1
	)
	if(giveplayer_id == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podano b³êdne ID gracza., OK, )
		return 1
	)
	if(!Logged(giveplayer_id))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
 		return 1
	)
	if((PlayerCache(playerid)(pBlock) & BLOCK_OOC) && PlayerCache(giveplayer_id)(pAdmin) == 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Twoja postaæ ma na³o¿on¹ blokadê czatu OOC., OK, )
		return 1
	)
	if(PlayerCache(giveplayer_id)(pTogW) && PlayerCache(playerid)(pAdmin) == 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ma wy³¹czone otrzymywanie prywatnych wiadomoœci., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pBW) && !PlayerToPlayer(25.0, playerid, giveplayer_id) && PlayerCache(giveplayer_id)(pAdmin) == 0)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Podczas stanu nieprzytomnoœci, wiadomoœci prywatne mo¿esz wysy³aæ na okreœlon¹ odleg³oœæ., OK, )
		return 1
	)
	if(PlayerCache(giveplayer_id)(pPlayerIgnored)(playerid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz ignoruje wiadomoœci przychodz¹ce od Ciebie., OK, )
		return 1
	)
	text(0) = chrtoupper(text(0))
	
	/*if(PlayerCache(playerid)(pMaskUID))
	(
		format(string, sizeof(string), (( %s: %s )), PlayerName(playerid), text)
	)
	else
	(
		format(string, sizeof(string), (( %s (%d): %s )), PlayerName(playerid), playerid, text)
	)*/
	
	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		if(PlayerCache(giveplayer_id)(pAdmin) != 0 && PlayerCache(giveplayer_id)(pFocusedID) != INVALID_PLAYER_ID && PlayerCache(giveplayer_id)(pFocusedID) != playerid)
		(
			GuiMsg(playerid, Ten administrator pomaga w³aœnie innemu graczowi\nnapisz do niego za chwilê., 1)
			return 1
		)
	)
	
	if(PlayerCache(giveplayer_id)(pAdminToken) && PlayerCache(playerid)(pAdmin) == 0)
	(
		if(PlayerCache(giveplayer_id)(pAdmin) ) 0 || PlayerCache(giveplayer_id)(pAdmin) ( 0)
		(
			// tego warunku nie by³o
			if(PlayerCache(giveplayer_id)(pAdmin) != -1)
			(
				cap1 = random(sizeof(Captcha)),
				cap2 = random(sizeof(Captcha)),
				cap3 = random(sizeof(Captcha)),
				cap4 = random(sizeof(Captcha)),
				cap5 = random(sizeof(Captcha)),
				cap6 = random(sizeof(Captcha)),
				cap7 = random(sizeof(Captcha)),
				cap8 = random(sizeof(Captcha)),
				cap9 = random(sizeof(Captcha)),
				cap10 = random(sizeof(Captcha))
				
				format(PlayerCache(playerid)(pCaptcha), 16, %s%s%s%s%s%s%s%s%s%s, Captcha(cap1), Captcha(cap2), Captcha(cap3), Captcha(cap4), Captcha(cap5), Captcha(cap6), Captcha(cap7), Captcha(cap8), Captcha(cap9), Captcha(cap10))
				format(PlayerCache(playerid)(pSendingCaptcha), 128, %s, text)
				MainPlayerTable(playerid) = giveplayer_id
				
				msg(512)
				format(msg, sizeof(msg), Przepisz poni¿szy kod by wys³aæ wiadomoœæ do administratora.\nTo ograniczenie zosta³o stworzone po to by administratorzy mogli nad¹¿aæ za proœbami graczy.\n\nKod: (00FF00)%s, PlayerCache(playerid)(pCaptcha))
				ShowPlayerDialog(playerid, D_CAPTCHA, DIALOG_STYLE_INPUT, Captcha, msg, Gotowe, Anuluj)
				
				return 1
			)
		)
	)

	PlayerCache(giveplayer_id)(pLastW) = playerid
	PlayerCache(playerid)(pLastW) = giveplayer_id
	PlayerCache(playerid)(pLastWTo) = giveplayer_id
		
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), (( » %s (%d): %s )), PlayerGlobalName(giveplayer_id, COLOR_SEND_PW), giveplayer_id, text)
		SendClientMessage(playerid, COLOR_SEND_PW, string)
		
		format(string, sizeof(string), (( %s (%d): %s )), PlayerGlobalName(playerid, COLOR_GOT_PW), playerid, text)
		SendClientMessage(giveplayer_id, COLOR_GOT_PW, string)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
			text2(64)

			strmid(text2, text, pos, strlen(text))
			strdel(text, pos, strlen(text))

			format(string, sizeof(string), (( » %s (%d): %s )), PlayerGlobalName(giveplayer_id, COLOR_SEND_PW), giveplayer_id, text)
			SendClientMessage(playerid, COLOR_SEND_PW, string)
			
			format(string, sizeof(string), (( %s (%d): %s )), PlayerGlobalName(playerid, COLOR_GOT_PW), playerid, text)
			SendClientMessage(giveplayer_id, COLOR_GOT_PW, string)
			
			
			format(string, sizeof(string), (( » %s (%d): %s )), PlayerGlobalName(giveplayer_id, COLOR_SEND_PW), giveplayer_id, text2)
			SendClientMessage(playerid, COLOR_SEND_PW, string)
			
			format(string, sizeof(string), (( %s (%d): %s )), PlayerGlobalName(playerid, COLOR_GOT_PW), playerid, text2)
			SendClientMessage(giveplayer_id, COLOR_GOT_PW, string)
		)
	)
	
	if(PlayerCache(playerid)(pTogW))
	(
		TextDrawSetString(Text:TextDrawMainInfo(playerid), Pamietaj, ze masz ~r~wylaczona ~w~mozliwosc otrzymywania prywatnych ~y~wiadomosci~w~.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		PlayerCache(playerid)(pShowInfoText) = 5
		return 1
	)
	
	if(IsPlayerAFK(giveplayer_id))
	(
		TextDrawSetString(Text:TextDrawMainInfo(playerid), Gracz, do ktorego ~g~wyslano ~w~ta ~y~wiadomosc ~w~jest teraz AFK.)
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

		PlayerCache(playerid)(pShowInfoText) = 5
		return 1
	)
	return 1
)

CMD:pm(playerid, params()) return cmd_w(playerid, params)
CMD:wiadomosc(playerid, params()) return cmd_w(playerid, params)

CMD:re(playerid, params())
(
	if(PlayerCache(playerid)(pLastW) == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Z nikim nie pisa³eœ przez ostatni czas., OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /re (Tekst))
		return 1
	)
	string(256)
	
	format(string, sizeof(string), %d %s, PlayerCache(playerid)(pLastW), params)
	cmd_w(playerid, string)
	return 1
)

CMD:wr(playerid, params())
(
	if(PlayerCache(playerid)(pLastWTo) == INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Z nikim nie pisa³eœ przez ostatni czas., OK, )
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /wr (Tekst))
		return 1
	)
	string(256)
	
	format(string, sizeof(string), %d %s, PlayerCache(playerid)(pLastWTo), params)
	cmd_w(playerid, string)
	return 1
)

CMD:mic(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skorzystaæ teraz z tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGagged) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid,Nie mo¿esz mówiæ bêd¹c zakneblowanym.,1)
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /mic (Tekst))
		return 1
	)
	object_id = GetClosestObject(playerid)
	if(object_id == INVALID_OBJECT_ID || GetObjectModel(object_id) != OBJECT_MICROPHONE)
	(
		GuiMsg(playerid,W pobli¿u nie ma ¿adnego mikrofonu.,1)
		return 1
	)
	string(256)
 	params(0) = chrtoupper(params(0))
 	
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), %s (mikrofon): %s, PlayerName(playerid), params)
		ProxDetector(40.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, false)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), %s (mikrofon): %s..., PlayerName(playerid), params)
			ProxDetector(40.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, false)

			format(string, sizeof(string), ...%s, text)
			ProxDetector(40.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, false)
		)
	)
	return 1
)

CMD:m(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz skorzystaæ teraz z tej komendy., OK, )
		return 1
	)
	if(PlayerCache(playerid)(pGagged) != INVALID_PLAYER_ID)
	(
		GuiMsg(playerid,Nie mo¿esz mówiæ bêd¹c zakneblowanym.,1)
		return 1
	)
	if(isnull(params))
	(
		hrp_Tip(playerid, /m (Tekst))
		return 1
	)
	if(!PlayerHaveItem(playerid, ITEM_MEGAPHONE))
	(
		 ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiedniego przedmiotu w swoim ekwipunku., OK, )
		 return 1
	)
	string(256)
 	params(0) = chrtoupper(params(0))
 	
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), %s (megafon): %s, PlayerName(playerid), params)
		ProxDetector(40.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, false)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), %s (megafon): %s..., PlayerName(playerid), params)
			ProxDetector(40.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, false)

			format(string, sizeof(string), ...%s, text)
			ProxDetector(40.0, playerid, string, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, false)
		)
	)
	return 1
)

CMD:ame(playerid, params())
(
	if(isnull(params))
	(
		hrp_Tip(playerid, /ame (Akcja))
		return 1
	)
	
	// Dla reszty graczy
	string(256)
	params(0) = chrtolower(params(0))
	
	format(string, sizeof(string), ** %s %s, PlayerName(playerid), params)
	SetPlayerChatBubble(playerid, string, COLOR_PURPLE, 30.0, 8000)
	
	// Komunikat dla gracza
	if(strlen(params) ( 78)
	(
		format(string, sizeof(string), ** %s %s, PlayerName(playerid), params)
		SendClientMessage(playerid, COLOR_PURPLE, string)
	)
	else
	(
		pos = strfind(params,  , true, strlen(params) / 2)
		if(pos != -1)
		(
  			text(64)

  			strmid(text, params, pos + 1, strlen(params))
			strdel(params, pos, strlen(params))

			format(string, sizeof(string), ** %s %s..., PlayerName(playerid), params)
			SendClientMessage(playerid, COLOR_PURPLE, string)
			
			format(string, sizeof(string), ...%s **, text)
			SendClientMessage(playerid, COLOR_PURPLE, string)
		)
	)
	return 1
)

stock FlashMe(playerid, message())
(
	SetPlayerChatBubble(playerid, message, COLOR_PURPLE, 30.0, 8000)
	SendClientMessage(playerid, COLOR_PURPLE, message)
	return 1
)