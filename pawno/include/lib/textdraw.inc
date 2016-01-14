// Nowe info textdrawy
stock ShowPlayerTextDrawInfo(playerid, content())
(
	output(512)
	format(output, sizeof(output), ~n~%s, content)
	PlayerTextDrawSetString(playerid, TextDrawInfoNewContent(playerid), output)
	
	TextDrawShowForPlayer(playerid, TextDrawInfoNew)
	PlayerTextDrawShow(playerid, TextDrawInfoNewContent(playerid))
	return 1
)

stock HidePlayerTextDrawInfo(playerid)
(
	TextDrawHideForPlayer(playerid, TextDrawInfoNew)
	PlayerTextDrawHide(playerid, TextDrawInfoNewContent(playerid))
	return 1
)

public OnPlayerClickTextDraw(playerid, Text:clickedid)
(	
	if(PlayerCache(playerid)(pClicked) != INVALID_PLAYER_ID)
	(
		target = PlayerCache(playerid)(pClicked), string(64)
		
		if(clickedid == Text:DashboardOption(0))	// sparing
		(
			format(string, sizeof(string), %d, target)
			cmd_sparing(playerid, string)
		)
		else if(clickedid == Text:DashboardOption(1))	// powitanie
		(
			PlayerCache(playerid)(pPlayerIDOffer) = target
			ShowPlayerDialog(playerid, D_DASHBOARD_YO, DIALOG_STYLE_LIST, Wybierz animacjê powitania, 1\n2\n3\n4\n5\n6, Oferuj, Anuluj)
		)
		else if(clickedid == Text:DashboardOption(2))	// poca³unek
		(
			PlayerCache(playerid)(pPlayerIDOffer) = target
			ShowPlayerDialog(playerid, D_DASHBOARD_KISS, DIALOG_STYLE_LIST, Wybierz animacjê poca³unku, 1\n2\n3, Oferuj, Anuluj)
		)
		else if(clickedid == Text:DashboardOption(3))	// przedmiot
		(
			PlayerCache(playerid)(pPlayerIDOffer) = target
			ListPlayerItems(playerid, MANAGE_TYPE_DASHBOARD_OFFER)
		)
		else if(clickedid == Text:DashboardOption(4))	// vcard
		(
			format(string, sizeof(string), vcard %d, target)
			cmd_oferuj(playerid, string)
		)
		else if(clickedid == Text:DashboardOption(5))	// gotówka
		(
			PlayerCache(playerid)(pPlayerIDOffer) = target
			ShowPlayerDialog(playerid, D_DASHBOARD_PAY, DIALOG_STYLE_INPUT, Zap³aæ gotówkê, WprowadŸ w poni¿sze pole kwotê, któr¹ chcesz podarowaæ drugiej osobie., P³aæ, Anuluj)
		)
		else if(clickedid == Text:DashboardOption(6))	// hamulec rêczny
		(
			cmd_reczny(playerid, )
		)
		else if(clickedid == Text:DashboardOption(7))	// szyba
		(
			cmd_okno(playerid, )
		)
		else if(clickedid == Text:DashboardOption(8))	// CB radio
		(
			if(!(CarInfo(target)(cAccess) & VEH_ACCESS_RADIO))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, W tym pojeŸdzie nie zosta³o zamontowane CB radio., OK, )
			)
			else
			(
				ShowPlayerDialog(playerid, D_RADIO_OPTIONS, DIALOG_STYLE_LIST, CB radio, 1. Ustaw kana³\n2. Wykup kana³ na w³asnoœæ\n3. Ustaw has³o dla kana³u\n4. Definitywnie usuñ kana³\n5. Przypisz kana³ pod grupê, Wybierz, Anuluj)
			)
		)
		else if(clickedid == Text:DashboardOption(9))	// baga¿nik
		(
			cmd_bagaznik(playerid, _)
		)
		else if(clickedid == Text:DashboardOption(10))	// maska
		(
			cmd_maska(playerid, )
		)
		else if(clickedid == Text:DashboardOption(11))	// silnik
		(
			cmd_silnik(playerid, )
		)
		
		HideDashboardPlayer(playerid)
	) else (
		LSPad_TDListener(playerid, clickedid)
	)
/*
	if(clicked != INVALID_PLAYER_ID)
	(
		if(clickedid == Text:TextDrawAKill)
		(
			format(string, sizeof(string), %d %d, clicked, 0)
			cmd_sethp(playerid, string)
		)
		else if(clickedid == Text:TextDrawAKick)
		(
			format(string, sizeof(string), %d Relog, clicked)
			cmd_kick(playerid, string)
		)
		else if(clickedid == Text:TextDrawABan)
		(
			format(string, sizeof(string), %d 0 Cheater, clicked)
			cmd_ban(playerid, string)
		)
		else if(clickedid == Text:TextDrawARun)
		(
			format(string, sizeof(string), run %d 7 Sprint (7 dni), clicked)
			cmd_block(playerid, string)
		)
		else if(clickedid == Text:TextDrawAVeh)
		(
			format(string, sizeof(string), veh %d 7 Odwalanie pojazdem (7 dni), clicked)
			cmd_block(playerid, string)
		)
		else if(clickedid == Text:TextDrawAFreeze)
		(
			format(string, sizeof(string), %d, clicked)
			cmd_freeze(playerid, string)
		)
		else if(clickedid == Text:TextDrawAGethere)
		(
			format(string, sizeof(string), %d, clicked)
			cmd_gethere(playerid, string)
		)
		else if(clickedid == Text:TextDrawAGoto)
		(
			format(string, sizeof(string), %d, clicked)
			cmd_goto(playerid, string)
		)
		else if(clickedid == Text:TextDrawASlap)
		(
			format(string, sizeof(string), %d, clicked)
			cmd_slap(playerid, string)
		)
		else if(clickedid == Text:TextDrawARespawn)
		(
			format(string, sizeof(string), %d, clicked)
			cmd_res(playerid, string)
		)
		else if(clickedid == Text:TextDrawABW)
		(
			format(string, sizeof(string), zdejmij %d, clicked)
			cmd_bw(playerid, string)
			format(string, sizeof(string), %d 100, clicked)
			cmd_sethp(playerid, string)
		)
		else if(clickedid == Text:TextDrawAChill)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Ta opcja nie jest aktywna., OK, )
			//format(string, sizeof(string), %d Odpocznij sobie, clicked)
			//cmd_chill(playerid, string)
		)
		else if(clickedid == Text:TextDrawASpec)
		(
			format(string, sizeof(string), %d, clicked)
			cmd_spec(playerid, string)
		)
		else if(clickedid == Text:TextDrawAUlti)
		(
			Float:x, Float:y, Float:z
			GetPlayerPos(clicked, x, y, z)
			CreateExplosion(x, y, z, 7, 5.0)
			
			format(string, sizeof(string), %d 0, clicked)
			cmd_sethp(playerid, string)
		)
		else if(clickedid == Text:TextDrawAExit)
		(
			
		)
		HideAdminMenu(playerid)
	)
*/	
	return 1
)

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
(
	/*
		u¿ywanie przedmiotów
	*/
	if(!LSPad_PlayerTDListener(playerid, playertextid))
	(
		// telefon
		if(playertextid == TextPhoneButton(playerid))
		(
			PlayerTextDrawSetString(playerid, TextPhoneBtnCall(playerid), Zadzwon)
			PlayerTextDrawSetString(playerid, TextPhoneBtnSms(playerid), SMS)
			PlayerTextDrawSetString(playerid, TextPhoneBtnContacts(playerid), Kontakty)
			phone_hideTexts(playerid)
			return 1
		)
		
		if(playertextid == TextPhoneBtnSett(playerid))
		(
			PlayerCache(playerid)(pPhoneAction) = PHONE_ACTION_SETTINGS
			PlayerTextDrawSetString(playerid, TextPhoneBtnCall(playerid), Haslo)
			PlayerTextDrawSetString(playerid, TextPhoneBtnSms(playerid), Tapeta)
			PlayerTextDrawSetString(playerid, TextPhoneBtnContacts(playerid), Dzwonek)
			PlayerTextDrawHide(playerid, TextPhoneBtnAdd(playerid))
			PlayerTextDrawHide(playerid, TextPhoneBtnCard(playerid))
			PlayerTextDrawHide(playerid, TextPhoneBtnSett(playerid))
			
			return 1
		)
		
		if(playertextid == TextPhoneBtnCard(playerid))
		(
			list_players(256)
			foreach(Player, i)
			(
				if(IsPlayerConnected(i))
				(
					if(Logged(i) && Spawned(i))
					(
						if(i != playerid)
						(
							if(PlayerToPlayer(5.0, playerid, i))
							(
								format(list_players, sizeof(list_players), %s\n%d\t%s, list_players, i, PlayerName(i))
							)
						)
					)
				)
			)
			if(!strlen(list_players))
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych graczy w pobli¿u., OK, )
			)
			ShowPlayerDialog(playerid, D_SEND_VCARD, DIALOG_STYLE_LIST, Wyœlij vCard do:, list_players, Wybierz, Anuluj)
			
			phone_hideTexts(playerid)
			return 1
		)
		
		if(playertextid == TextPhoneBtnCall(playerid))
		(
			if(PlayerCache(playerid)(pPhoneAction) == PHONE_ACTION_SETTINGS)
			(
				// Haslo
				if(getPhoneSettings(playerid, GET_PHONE_PASSWORD) ) 0)
				(
					ShowPlayerDialog(playerid, D_PHONE_PASS_CHANGE, DIALOG_STYLE_LIST, Ustawienia has³a, 1. Zmieñ has³o\n2. Usuñ has³o, OK, Anuluj)
					phone_hideTexts(playerid)
				)
				else
				(
					ShowPlayerDialog(playerid, D_PHONE_PASS_CHANGE, DIALOG_STYLE_LIST, Ustawienia has³a, 1. Zmieñ has³o, OK, Anuluj)
					phone_hideTexts(playerid)
				)
				
				PlayerTextDrawSetString(playerid, TextPhoneBtnCall(playerid), Zadzwon)
				PlayerTextDrawSetString(playerid, TextPhoneBtnSms(playerid), SMS)
				return 1
			)
			
			ShowPlayerDialog(playerid, D_INSERT_NUMBER_CALL, DIALOG_STYLE_INPUT, Zadzwoñ, WprowadŸ numer telefonu komórkowego, na który chcesz zadzwoniæ., Po³¹cz, Anuluj)
			phone_hideTexts(playerid)
			return 1
		)
		
		if(playertextid == TextPhoneBtnSms(playerid))
		(
			if(PlayerCache(playerid)(pPhoneAction) == PHONE_ACTION_SETTINGS)
			(
				// Tapeta
				ShowPlayerDialog(playerid, D_PHONE_SELECT_WALLPAPER, DIALOG_STYLE_LIST, Wybierz now¹ tapetê, 1. Brunetka\n2. Ciemna tapeta\n3. Blondynka\n4. Gangster\n5. Savanna, OK, Anuluj)
				phone_hideTexts(playerid)
				
				PlayerTextDrawSetString(playerid, TextPhoneBtnCall(playerid), Zadzwon)
				PlayerTextDrawSetString(playerid, TextPhoneBtnSms(playerid), SMS)
				return 1
			)
			
			ShowPlayerDialog(playerid, D_INSERT_NUMBER_SMS, DIALOG_STYLE_INPUT, Wyœlij SMS, WprowadŸ numer telefonu, na który chcesz wys³aæ wiadomoœæ SMS., Dalej, Anuluj)
			phone_hideTexts(playerid)
			return 1
		)
		
		if(playertextid == TextPhoneBtnContacts(playerid))
		(
			if(PlayerCache(playerid)(pPhoneAction) == PHONE_ACTION_SETTINGS)
			(
				// Dzwonek w telefonie
				if(PlayerCache(playerid)(pPhoneMuted))
				(
					PlayerCache(playerid)(pPhoneMuted) = false
					GameTextForPlayer(playerid, ~w~Telefon ~g~odciszony, 4000, 6)
				)
				else
				(
					PlayerCache(playerid)(pPhoneMuted) = true
					GameTextForPlayer(playerid, ~w~Telefon ~r~wyciszony, 4000, 6)
				)

				phone_hideTexts(playerid)
				
				PlayerTextDrawSetString(playerid, TextPhoneBtnCall(playerid), Zadzwon)
				PlayerTextDrawSetString(playerid, TextPhoneBtnSms(playerid), SMS)
				return 1
			)

			data(128), list_contacts(1024),
				contact_number, contact_name(24)

			mysql_query_format(SELECT contact_number, contact_name FROM hrp_contacts WHERE contact_ownernumb = %d, PlayerCache(playerid)(pPhoneNumber))

			format(list_contacts, sizeof(list_contacts), 911\t\tNumer alarmowy\n333\t\tHurtownia\n777\t\tTaxi\n444\t\tLos Santos News\n-----)

			mysql_store_result()
			while(mysql_fetch_row(data, |))
			(
				sscanf(data, p(|)ds(24), contact_number, contact_name)

				format(list_contacts, sizeof(list_contacts), %s\n%d\t\t%s, list_contacts, contact_number, contact_name)
			)
			mysql_free_result()
			if(strlen(list_contacts) ) 0)
			(
				ShowPlayerDialog(playerid, D_LIST_CONTACTS, DIALOG_STYLE_LIST, Kontakty w telefonie, list_contacts, Wybierz, Anuluj)
			)
			else
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych kontaktów w telefonie., OK, )
			)
					
			phone_hideTexts(playerid)
			return 1
		)
		
		if(playertextid == TextPhoneBtnAdd(playerid))
		(
			ShowPlayerDialog(playerid, D_TEL_ADDNUM, DIALOG_STYLE_INPUT, Zapisz numer, WprowadŸ numer, który chcesz dodaæ do kontaktów., Dodaj, Anuluj)
			phone_hideTexts(playerid)
			return 1
		)
		
		if(playertextid == TextPhoneBtnExit(playerid))
		(
			itemid = PlayerCache(playerid)(pManageItem)

			ItemInfo(itemid)(iUsed) = 0

			PlayerCache(playerid)(pPhoneNumber) = 0
			GameTextForPlayer(playerid, ~w~Telefon ~r~wylaczony, 4000, 6)

			mysql_query_format(UPDATE hrp_items SET item_used = 0 WHERE item_uid = %d LIMIT 1, ItemInfo(itemid)(iUID))
			phone_hideTexts(playerid)
			return 1
		)
		// koniec telefonów
		
		if(playertextid == TextDrawItem(playerid)(0))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			foreach(Items, itemid)
			(
				
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
				
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
			
		)
		if(playertextid == TextDrawItem(playerid)(1))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			skip = 1, loops = 0 // do wybierania
			foreach(Items, itemid)
			(
				
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
						
						if(skip ) loops)		
						(
							loops++
							continue
						)
						
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
		)
		if(playertextid == TextDrawItem(playerid)(2))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			skip = 2, loops = 0 // do wybierania
			foreach(Items, itemid)
			(
				
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
						
						if(skip ) loops)		
						(
							loops++
							continue
						)
						
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
		)
		if(playertextid == TextDrawItem(playerid)(3))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			skip = 3, loops = 0 // do wybierania
			foreach(Items, itemid)
			(
				
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
						
						if(skip ) loops)		
						(
							loops++
							continue
						)
						
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
		)
		if(playertextid == TextDrawItem(playerid)(4))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			skip = 4, loops = 0 // do wybierania
			foreach(Items, itemid)
			(
				
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
						
						if(skip ) loops)		
						(
							loops++
							continue
						)
						
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
		)
		if(playertextid == TextDrawItem(playerid)(5))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			skip = 5, loops = 0 // do wybierania
			foreach(Items, itemid)
			(
				
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
						
						if(skip ) loops)		
						(
							loops++
							continue
						)
						
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
		)
		if(playertextid == TextDrawItem(playerid)(6))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			skip = 6, loops = 0 // do wybierania
			foreach(Items, itemid)
			(
				
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
						
						if(skip ) loops)		
						(
							loops++
							continue
						)
						
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
		)
		if(playertextid == TextDrawItem(playerid)(7))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			skip = 7, loops = 0 // do wybierania
			foreach(Items, itemid)
			(
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
						
						if(skip ) loops)		
						(
							loops++
							continue
						)
						
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
		)
		if(playertextid == TextDrawItem(playerid)(8))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			skip = 8, loops = 0 // do wybierania
			foreach(Items, itemid)
			(
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
						
						if(skip ) loops)		
						(
							loops++
							continue
						)
						
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
		)
		if(playertextid == TextDrawItem(playerid)(9))
		(
			CancelSelectTextDraw(playerid)
			
			pageid = PlayerCache(playerid)(pItemPage)
			pageid = pageid * 10		//dla pewnoœci
			itemSel = 0
			
			helped = 0		//taka tam pomocniczna
			skip = 9, loops = 0 // do wybierania
			foreach(Items, itemid)
			(
				
				if(ItemInfo(itemid)(iUID))
				(
					if(ItemInfo(itemid)(iPlace) == PLACE_PLAYER && ItemInfo(itemid)(iOwner) == PlayerCache(playerid)(pUID))
					(
						if(pageid ) helped)
						(
							//do kolejnych stron, chyba
							helped++
							continue
						)
						
						if(skip ) loops)		
						(
							loops++
							continue
						)
						
						itemSel = itemid
						break
					)
				)
			)
			
			title(64), list_manage(256)
			PlayerCache(playerid)(pSelectItem) = itemSel
			PlayerCache(playerid)(pManageItem) = itemSel
			format(title, sizeof(title), Zarz¹dzaj przedmiotem » %s (UID: %d), ItemInfo(itemSel)(iName), ItemInfo(itemSel)(iUID))

			if(ItemInfo(itemSel)(iUsed))
			(
				format(list_manage, sizeof(list_manage), 1. Przestañ u¿ywaæ tego przedmiotu\n2. (FF3D3D)Od³ó¿ przedmiot w pobli¿u(FFFFFF)\n3. (FF3D3D)Sprzedaj innemu graczowi(93A818)\n4. Poka¿ informacje(FFFFFF)\n5. (FF3D3D)W³ó¿ do innego przedmiotu(FFFFFF)\n6. (FF3D3D)WsadŸ przedmiot do schowka(FFFFFF)\n7. (FF3D3D)Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)
			else
			(
				format(list_manage, sizeof(list_manage), (FFFFFF)1. U¿yj tego przedmiotu\n2. Od³ó¿ przedmiot w pobli¿u\n3. Sprzedaj innemu graczowi\n(93A818)4. Poka¿ informacje(FFFFFF)\n5. W³ó¿ do innego przedmiotu\n6. WsadŸ przedmiot do schowka\n7. Rozbij przedmiot\n8. Zmieñ opis przedmiotu\n9. Poka¿ przedmiot graczowi)
			)

			ShowPlayerDialog(playerid, D_MANAGE_ITEM, DIALOG_STYLE_LIST, title, list_manage, Wybierz, Wróæ)
		)
		/*
			koniec u¿ywania przedmiotów
		*/
		if(playertextid == TextDrawItemNext(playerid))
		(
			if(bGUI_ListPlayerItems(playerid,PlayerCache(playerid)(pItemPage)+1) (= 0)
			(
				GuiMsg(playerid,Nie posiadasz wiêcej przedmiotów.,1)
			)
			else
			(
				PlayerCache(playerid)(pItemPage)++
				bGUI_ListPlayerItems(playerid,PlayerCache(playerid)(pItemPage))
			)
		)
		if(playertextid == TextDrawItemPrev(playerid))
		(
			if(bGUI_ListPlayerItems(playerid,PlayerCache(playerid)(pItemPage)-1) (= 0)
			(
				return 1
			)
			else
			(
				PlayerCache(playerid)(pItemPage)--
				if(PlayerCache(playerid)(pItemPage) ( 0)
					PlayerCache(playerid)(pItemPage) = 0
				
				bGUI_ListPlayerItems(playerid,PlayerCache(playerid)(pItemPage))
			)
		)
		if(playertextid == TextDrawItemCancel(playerid))
		(
			bGUI_Hide(playerid)
			PlayerCache(playerid)(pItemPage) = 0
		)
		/*if(playertextid == TextDrawActionCheck(playerid))
		(
			//sprawdz
			gameid = PlayerCache(playerid)(pPoker)
			if(PokerGames(gameid)(pkActivePlayerSlot) != poker_GetPlayerPokerSlot(playerid))
			(
				GuiMsg(playerid,Aktualnie inny gracz wykonuje ruch, poczekaj na swoj¹ kolej!,1)
				return 1
			)
			
			if(PlayerCache(playerid)(pCash) )= PokerGames(gameid)(pkNeed))
			(
				PlayerCache(playerid)(pPokerPhase) = PLAYER_PKPHASE_CHECK
				poker_RoundLoop(gameid)
			)
			else
			(
				//koniec gry dla tego pana
				PlayerCache(playerid)(pPokerPhase) = PLAYER_PKPHASE_FOLD
				poker_RoundLoop(gameid)
			)
		)
		if(playertextid == TextDrawActionBed(playerid))
		(
			//podbij
			gameid = PlayerCache(playerid)(pPoker)
			if(PokerGames(gameid)(pkActivePlayerSlot) != poker_GetPlayerPokerSlot(playerid))
			(
				GuiMsg(playerid,Aktualnie inny gracz wykonuje ruch, poczekaj na swoj¹ kolej!,1)
				return 1
			)
			
			if(PlayerCache(playerid)(pCash) ) PokerGames(gameid)(pkNeed))
			(
				PlayerCache(playerid)(pPokerPhase) = PLAYER_PKPHASE_BED
				poker_RoundLoop(gameid)
			)
			else
			(
				GuiMsg(playerid,Nie masz wystarczaj¹co pieniêdzy, by podbiæ stawkê.,1)
				return 1
			)
			
		)
		if(playertextid == TextDrawActionFold(playerid))
		(
			//pasuj
			gameid = PlayerCache(playerid)(pPoker)
			if(PokerGames(gameid)(pkActivePlayerSlot) != poker_GetPlayerPokerSlot(playerid))
			(
				GuiMsg(playerid,Aktualnie inny gracz wykonuje ruch, poczekaj na swoj¹ kolej!,1)
				return 1
			)
			
			PlayerCache(playerid)(pPokerPhase) = PLAYER_PKPHASE_FOLD
			
			poker_RoundLoop(gameid)
		)*/
		if(playertextid == PDT_2(playerid))
		(
			if(PlayerCache(playerid)(pPDMenu) == PDM_START)
			(
				PD_ShowPersonalSearch(playerid)
				return 1
			)
		)
		else if(playertextid == PDT_3(playerid))
		(
			if(PlayerCache(playerid)(pPDMenu) == PDM_START)
			(
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Ta opcja nie jest aktywna., OK, )
			)
		)
		else if(playertextid == PDT_4(playerid))
		(
			if(PlayerCache(playerid)(pPDMenu) == PDM_START)
			(
				PD_ShowCarSearch(playerid)
				PlayerCache(playerid)(pPDMenu) = PDM_CAR
				return 1
			)
		)
		else if(playertextid == PDT_5(playerid))
		(
			if(PlayerCache(playerid)(pPDMenu) == PDM_START)
			(
				ShowPlayerDialog(playerid,D_MANDAT_PD_INPUT_NAME,DIALOG_STYLE_INPUT,LSPD ) informacje o mandatach,WprowadŸ imiê i nazwisko osoby, której listê mandatów chcesz sprawdziæ.\n\n (( Imie_Nazwisko)),Gotowe,Anuluj)
			)
		)
		else if(playertextid == PDT_6(playerid))
		(
			if(PlayerCache(playerid)(pPDMenu) == PDM_START)
			(
				cmd_gps(playerid, )
				PD_Hide(playerid)
			)
		)
		else if(playertextid == PDT_7(playerid))
		(
			if(PlayerCache(playerid)(pPDMenu) == PDM_START)
			(
				if(IsPlayerInAnyVehicle(playerid))
				(
					if(PlayerCache(playerid)(pGroupDuty))
					(
						group_id_fix = GetPlayerDutyGroupID(playerid), vehid = GetPlayerVehicleID(playerid)
						if(GroupData(group_id_fix)(gType) == GROUP_POLICE || GroupData(group_id_fix)(gType) == GROUP_FBI)
						(
							if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == GroupData(group_id_fix)(gUID))
							(
								/*if(CarInfo(vehid)(cStrobe))
								(
									CarInfo(vehid)(cStrobe) = false
								)
								else
								(
									CarInfo(vehid)(cStrobe) = true
								)*/
								
								if(CarInfo(vehid)(cFlashed))
								(
									if(IsValidObject(CarInfo(vehid)(cPoliceGrill)))
										DestroyObject(CarInfo(vehid)(cPoliceGrill))
									
									panelsx,doorsx,lightsx,tiresx
									GetVehicleDamageStatus(vehid,panelsx,doorsx,lightsx,tiresx)
	                                UpdateVehicleDamageStatus(vehid, panelsx, doorsx, 0, tiresx)
									
									CarInfo(vehid)(cFlashed) = false
									
									TextDrawSetString(Text:TextDrawMainInfo(playerid), Stroboskopy ~r~wylaczone)
									TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

									PlayerCache(playerid)(pShowInfoText) = 5
								)
								else
								(
									CarInfo(vehid)(cFlashed) = true
									
									CarInfo(vehid)(cPoliceGrill) = CreateObject(19419, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 200.0)
									AttachObjectToVehicle(CarInfo(vehid)(cPoliceGrill), vehid, 0.0, 2.1, -0.15, 0.0, 0.00, 0.0)
									
									TextDrawSetString(Text:TextDrawMainInfo(playerid), Stroboskopy ~g~wlaczone)
									TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))

									PlayerCache(playerid)(pShowInfoText) = 5
								)
								PD_Hide(playerid, true)
							)
						)
					)
				)
			)
		)
		else if(playertextid == PDT_8(playerid))
		(
			if(PlayerCache(playerid)(pPDMenu) == PDM_PERSON)
			(
				PD_ShowPersonalOffenses(playerid)
			)
		)
		else if(playertextid == PDT_9(playerid)) ()
		else if(playertextid == PDT_Back(playerid))
		(
			if(PlayerCache(playerid)(pPDMenu) == PDM_START)
			(
				PD_Hide(playerid, true)
				PlayerCache(playerid)(pPDMenu) = 0
				return 1
			)
			else if(PlayerCache(playerid)(pPDMenu) == PDM_PERSON || PlayerCache(playerid)(pPDMenu) == PDM_CAR)
			(
				PD_Show(playerid)
				PlayerCache(playerid)(pPDMenu) = PDM_START
				return 1
			)
		)
	)
	
	// craftowanie narkotyków cooking.inc
	if(playertextid == ActionClose(playerid))
	(
		ClearCooking(playerid)
		PlayerCache(playerid)(pCookID) = -1
		return 1
	)
	else if(playertextid == ActionAdd(playerid))
	(
		data(64), list_items(256), item_uid, item_name(32), item_value1
		
		mysql_query_format(SELECT item_uid, item_name, item_value1 FROM hrp_items WHERE item_place = %d AND item_owner = %d AND (item_type = %d OR item_type = %d AND item_value1 = %d AND item_value2 = 1), PLACE_PLAYER, PlayerCache(playerid)(pUID), ITEM_COOK_INGREDIENT, ITEM_DRUG, DRUG_COCAINE)
		mysql_store_result()
		while(mysql_fetch_row(data, |))
		(
			sscanf(data, p(|)ds(32)d, item_uid, item_name, item_value1)
			format(list_items, sizeof(list_items), %s\n%d\t%s, list_items, item_uid, item_name)
		)
		mysql_free_result()
		
		if(strlen(list_items))
		(
			ShowPlayerDialog(playerid, D_COOK_ADD, DIALOG_STYLE_LIST, Dostêpne sk³adniki, list_items, Dodaj, Anuluj)
		)
		else
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz ¿adnego sk³adnika, którego mo¿esz u¿yæ w procesie gotowania., OK, )
		)
		return 1
	)
	else if(playertextid == ActionCook(playerid))
	(
		cookid = PlayerCache(playerid)(pCookID)
		
		if(CookData(cookid)(cIngredients) ( 2)
		(
			GuiMsg(playerid, Aby gotowaæ musisz u¿yæ przynajmniej 2 sk³adników., 1)
			return 1
		)
		
		CookData(cookid)(cStatus) = COOK_STATUS_COOKING
		CookData(cookid)(cTime) = gettime()+RecipesData(CookData(cookid)(cDrug))(rTime)
		
		timeleft = (RecipesData(CookData(cookid)(cDrug))(rTime) / 60), string(256)
		format(string, sizeof(string), Sukces! Teraz rozpocznie siê proces tworzenia.\nWywar bêdzie gotowy do odebrania za: %d minut/y., timeleft)
		GuiMsg(playerid, string, 0)
		
		CloseCookingBox(playerid)
		PlayerCache(playerid)(pCookID) = -1
		
		/*ingredients(MAX_INGREDIENTS)
		sscanf(RecipesData(CookData(cookid)(cDrug))(rRecipe), a(d)(18), ingredients)
		string(256)
		for(i = 0 i ( sizeof(ingredients) i++)
		(
			format(string, sizeof(string), %s, IngredientsData(ingredients(i))(ingName))
			SendClientMessage(playerid, COLOR_WHITE, string)
		)*/
		return 1
	)
	
	return 1
)

stock ShowDashboardPlayer(playerid, what)
(
	for(i = 0 i ( 4 i++)
	(
		TextDrawShowForPlayer(playerid, Text:DashboardBG(i))
	)
	if(what & DASHBOARD_PLAYER)
	(
		for(i = 0 i ( 6 i++)
		(
			TextDrawShowForPlayer(playerid, Text:DashboardOption(i))
		)
	)
	if(what & DASHBOARD_VEHICLE)
	(
		for(i = 6 i ( 12 i++)
		(
			TextDrawShowForPlayer(playerid, Text:DashboardOption(i))
		)
	)
	
	SelectTextDraw(playerid, 0x14A2ECFF)
	return 1
)

stock HideDashboardPlayer(playerid)
(
	PlayerCache(playerid)(pClicked) = INVALID_PLAYER_ID
	CancelSelectTextDraw(playerid)
	
	for(i = 0 i ( 4 i++)
	(
		TextDrawHideForPlayer(playerid, Text:DashboardBG(i))
	)
	for(i = 0 i ( 12 i++)
	(
		TextDrawHideForPlayer(playerid, Text:DashboardOption(i))
	)
	
	return 1
)

/*
stock ShowAdminMenu(playerid)
(
	TextDrawShowForPlayer(playerid, Text:TextDrawAKill)
	TextDrawShowForPlayer(playerid, Text:TextDrawAKick)
	TextDrawShowForPlayer(playerid, Text:TextDrawABan)
	TextDrawShowForPlayer(playerid, Text:TextDrawARun)
	TextDrawShowForPlayer(playerid, Text:TextDrawAVeh)
	TextDrawShowForPlayer(playerid, Text:TextDrawAFreeze)
	TextDrawShowForPlayer(playerid, Text:TextDrawAGethere)
	TextDrawShowForPlayer(playerid, Text:TextDrawAGoto)
	TextDrawShowForPlayer(playerid, Text:TextDrawASlap)
	TextDrawShowForPlayer(playerid, Text:TextDrawARespawn)
	TextDrawShowForPlayer(playerid, Text:TextDrawABW)
	TextDrawShowForPlayer(playerid, Text:TextDrawAChill)
	TextDrawShowForPlayer(playerid, Text:TextDrawASpec)
	TextDrawShowForPlayer(playerid, Text:TextDrawAUlti)
	TextDrawShowForPlayer(playerid, Text:TextDrawAExit)
	
	SelectTextDraw(playerid, 0x32CD32FF)
	return 1
)

stock HideAdminMenu(playerid)
(
	PlayerCache(playerid)(pAdminClicked) = INVALID_PLAYER_ID
	CancelSelectTextDraw(playerid)

	TextDrawHideForPlayer(playerid, Text:TextDrawAKill)
	TextDrawHideForPlayer(playerid, Text:TextDrawAKick)
	TextDrawHideForPlayer(playerid, Text:TextDrawABan)
	TextDrawHideForPlayer(playerid, Text:TextDrawARun)
	TextDrawHideForPlayer(playerid, Text:TextDrawAVeh)
	TextDrawHideForPlayer(playerid, Text:TextDrawAFreeze)
	TextDrawHideForPlayer(playerid, Text:TextDrawAGethere)
	TextDrawHideForPlayer(playerid, Text:TextDrawAGoto)
	TextDrawHideForPlayer(playerid, Text:TextDrawASlap)
	TextDrawHideForPlayer(playerid, Text:TextDrawARespawn)
	TextDrawHideForPlayer(playerid, Text:TextDrawABW)
	TextDrawHideForPlayer(playerid, Text:TextDrawAChill)
	TextDrawHideForPlayer(playerid, Text:TextDrawASpec)
	TextDrawHideForPlayer(playerid, Text:TextDrawAUlti)
	TextDrawHideForPlayer(playerid, Text:TextDrawAExit)
	return 1
)
*/

stock PD_Show(playerid)
(
	PD_Hide(playerid)
	bool:flag = false
	
	PlayerTextDrawSetString(playerid, PDT_2(playerid), LSPD ) Kartoteka osobowa)
	PlayerTextDrawSetString(playerid, PDT_3(playerid), LSPD ) Lista poszukiwanych pojazdow)
	PlayerTextDrawSetString(playerid, PDT_4(playerid), DMV ) Znajdz pojazd)
	//PlayerTextDrawSetString(playerid, PDT_5(playerid), DMV ) Anuluj prawo jazdy)
	PlayerTextDrawSetString(playerid, PDT_5(playerid), LSPD ) Baza mandatow)
	if(IsPlayerInAnyVehicle(playerid))
	(
		if(PlayerCache(playerid)(pGroupDuty))
		(
			group_id_fix = GetPlayerDutyGroupID(playerid)
			if(GroupData(group_id_fix)(gType) == GROUP_POLICE || GroupData(group_id_fix)(gType) == GROUP_FBI)
			(
				vehid = GetPlayerVehicleID(playerid)
				if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP && CarInfo(vehid)(cOwner) == GroupData(group_id_fix)(gUID))
				(
					if(CarInfo(vehid)(cGPS))
					(
						flag = true
						PlayerTextDrawSetString(playerid, PDT_6(playerid), LSDPCAR ) Wylacz GPS)
					)
					else
					(
						flag = true
						PlayerTextDrawSetString(playerid, PDT_6(playerid), LSDPCAR ) Wlacz GPS)
					)
					
					if(CarInfo(vehid)(cStrobe))
					(
						flag = true
						PlayerTextDrawSetString(playerid, PDT_7(playerid), LSDPCAR ) Wylacz stroboskopy)
					)
					else
					(
						flag = true
						PlayerTextDrawSetString(playerid, PDT_7(playerid), LSDPCAR ) Wlacz stroboskopy)
					)
				)
			)
		)
	)
	
	if(!flag)
	(
		PlayerTextDrawSetString(playerid, PDT_6(playerid), _)
		PlayerTextDrawSetString(playerid, PDT_7(playerid), _)
	)
	
	PlayerTextDrawSetString(playerid, PDT_8(playerid), _)
	PlayerTextDrawSetString(playerid, PDT_9(playerid), _)
	PlayerTextDrawSetString(playerid, PDT_Back(playerid), Wyjdz)
	
	PlayerTextDrawShow(playerid, PDT_BG(playerid))
	PlayerTextDrawShow(playerid, PDT_1(playerid))
	PlayerTextDrawShow(playerid, PDT_2(playerid))
	PlayerTextDrawShow(playerid, PDT_3(playerid))
	PlayerTextDrawShow(playerid, PDT_4(playerid))
	PlayerTextDrawShow(playerid, PDT_5(playerid))
	PlayerTextDrawShow(playerid, PDT_Back(playerid))
	
	if(flag)
	(
		PlayerTextDrawShow(playerid, PDT_6(playerid))
		PlayerTextDrawShow(playerid, PDT_7(playerid))
	)
	return 1
)

stock PD_Hide(playerid, bool:fully = false)
(
	PlayerTextDrawHide(playerid, PDT_BG(playerid))
	PlayerTextDrawHide(playerid, PDT_1(playerid))
	PlayerTextDrawHide(playerid, PDT_2(playerid))
	PlayerTextDrawHide(playerid, PDT_3(playerid))
	PlayerTextDrawHide(playerid, PDT_4(playerid))
	PlayerTextDrawHide(playerid, PDT_5(playerid))
	PlayerTextDrawHide(playerid, PDT_6(playerid))
	PlayerTextDrawHide(playerid, PDT_7(playerid))
	PlayerTextDrawHide(playerid, PDT_8(playerid))
	PlayerTextDrawHide(playerid, PDT_9(playerid))
	PlayerTextDrawHide(playerid, PDT_Back(playerid))
	
	if(fully)
		CancelSelectTextDraw(playerid)
	return 1
)

stock PD_ShowPersonalSearch(playerid)
(
	ShowPlayerDialog(playerid, D_PD_NAME_INPUT, DIALOG_STYLE_INPUT, LSPD )) Szukaj, Wpisz \Imie_Nazwisko\ szukanej osoby.\n\nMo¿esz tak¿e u¿yæ polecenie \dodaj\ aby dodaæ nowy wpis., Szukaj, Anuluj)
	return 1
)

stock PD_ShowPersonalRecord(playerid, name(24), age, sex, points, bool:license, city)
(
	string(128)
	PD_Hide(playerid)
	
	format(string, sizeof(string), %s, name)
	PlayerTextDrawSetString(playerid, PDT_2(playerid), string)
	
	format(string, sizeof(string), Wiek: %d, age)
	PlayerTextDrawSetString(playerid, PDT_3(playerid), string)
	
	if(sex == 1)
		format(string, sizeof(string), Plec: Mezczyzna)
	else
		format(string, sizeof(string), Plec: Kobieta)
	PlayerTextDrawSetString(playerid, PDT_4(playerid), string)
	
	format(string, sizeof(string), Punkty kartne: %d, points)
	PlayerTextDrawSetString(playerid, PDT_5(playerid), string)
	
	if(license)
		format(string, sizeof(string), Prawo jazdy: Tak)
	else
		format(string, sizeof(string), Prawo jazdy: Nie)
	PlayerTextDrawSetString(playerid, PDT_6(playerid), string)
	
	if(city == 1) ( format(string, sizeof(string), Zameldowanie: Los Santos - Centrum) )
	else if(city == 2) ( format(string, sizeof(string), Zameldowanie: Los Santos - South Central) )
	else if(city == 3) ( format(string, sizeof(string), Zameldowanie: Los Santos - Obrzeza miasta) )
	else ( format(string, sizeof(string), Zameldowanie: Brak Danych) )
	PlayerTextDrawSetString(playerid, PDT_7(playerid), string)
	
	format(string, sizeof(string),  )) Pokaz kartoteke)
	PlayerTextDrawSetString(playerid, PDT_8(playerid), string)
	
	PlayerTextDrawSetString(playerid, PDT_Back(playerid), Powrot)
	
	PlayerTextDrawShow(playerid, PDT_BG(playerid))
	PlayerTextDrawShow(playerid, PDT_1(playerid))
	PlayerTextDrawShow(playerid, PDT_2(playerid))
	PlayerTextDrawShow(playerid, PDT_3(playerid))
	PlayerTextDrawShow(playerid, PDT_4(playerid))
	PlayerTextDrawShow(playerid, PDT_5(playerid))
	PlayerTextDrawShow(playerid, PDT_6(playerid))
	PlayerTextDrawShow(playerid, PDT_7(playerid))
	PlayerTextDrawShow(playerid, PDT_8(playerid))
	PlayerTextDrawShow(playerid, PDT_Back(playerid))
	
	PlayerCache(playerid)(pPDMenu) = PDM_PERSON
	return 1
)

stock PD_ShowPersonalOffenses(playerid)
(
	cmd_kartotekauid(playerid, PlayerCache(playerid)(pPDSuspect))
	return 1
)

stock PD_ShowCarSearch(playerid)
(
	ShowPlayerDialog(playerid, D_PD_CAR_NAME_INPUT, DIALOG_STYLE_INPUT, LSPD )) Szukaj, Wpisz rejestracjê szukanego pojazdu., Szukaj, Anuluj)
	return 1
)

stock PD_ShowCarRecord(playerid, name(24), plate(8), owner(64), model, fuel_type)
(
	string(128)
	PD_Hide(playerid)
	
	format(string, sizeof(string), %s, name)
	PlayerTextDrawSetString(playerid, PDT_2(playerid), string)
	
	format(string, sizeof(string), Rejestracja: %s, plate)
	PlayerTextDrawSetString(playerid, PDT_3(playerid), string)
	
	format(string, sizeof(string), Wlasciciel: %s, owner)
	PlayerTextDrawSetString(playerid, PDT_4(playerid), string)
	
	format(string, sizeof(string), Model: %s, VehicleData(model - 400)(vName))
	PlayerTextDrawSetString(playerid, PDT_5(playerid), string)
	
	format(string, sizeof(string), Typ paliwa: %s, GetVehicleFuelTypeName(fuel_type))
	PlayerTextDrawSetString(playerid, PDT_6(playerid), string)
	
	PlayerTextDrawSetString(playerid, PDT_Back(playerid), Powrot)
	
	PlayerTextDrawShow(playerid, PDT_BG(playerid))
	PlayerTextDrawShow(playerid, PDT_1(playerid))
	PlayerTextDrawShow(playerid, PDT_2(playerid))
	PlayerTextDrawShow(playerid, PDT_3(playerid))
	PlayerTextDrawShow(playerid, PDT_4(playerid))
	PlayerTextDrawShow(playerid, PDT_5(playerid))
	PlayerTextDrawShow(playerid, PDT_6(playerid))
	PlayerTextDrawShow(playerid, PDT_Back(playerid))
	
	PlayerCache(playerid)(pPDMenu) = PDM_CAR
	return 1
)