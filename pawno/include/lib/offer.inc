public OnPlayerSendOffer(playerid, customerid, type, offer_name(), value, price)
(
	// Zobaczymy czy to pomo¿e.
	PlayerCache(playerid)(pOfferedUID) = PlayerCache(customerid)(pUID)
	
	if(IsPlayerNPC(playerid) || IsPlayerNPC(customerid))
	(
		GuiMsg(playerid, Nie mo¿esz handlowaæ z botem., 1)
		return 1
	)
	
	if(Offer(playerid)(oCustomerID) != INVALID_PLAYER_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz wys³aæ kilku ofert jednoczeœnie., OK, )
		return 1
	)
	
	bool:checkbug = false
	if(gettime() - LogTime(playerid) ) 60 && gettime() - LogTime(customerid) ) 60)
		checkbug= true
		
	if(!checkbug)
	(
		GuiMsg(playerid, Musisz chwilê odczekaæ nim wyœlesz ofertê do tego gracza., 0)
		return 1
	)
	
	if(type != OFFER_PRODUCT && type != OFFER_VCARD && type != OFFER_PASSAGE && type != OFFER_REFUEL && type != OFFER_REPAIR && type != OFFER_REPAIR_ENGINE && type != OFFER_REPAIR_BODY && type != OFFER_REPAIR_FLUIDS && type != OFFER_REPAIR_FILTER && type != OFFER_REPAIR_COOLER && type != OFFER_MANDATE && type != OFFER_HEAL && type != OFFER_AD && type != OFFER_DOCUMENT && type != OFFER_REGISTER && type != OFFER_TRAIN && type != OFFER_LIFE && type != OFFER_WELCOME)
	(
		if(PlayerCache(customerid)(pGamePoints) ( 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz nic oferowaæ temu graczowi, dopóki ten nie zdobedzie 100GS., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pGamePoints) ( 100)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz nic oferowaæ, dopóki nie zdobedziesz 100GS., OK, )
			return 1
		)
	)
	
	string(256)
	hrp_OfferActionLog(Gracz %s (UID: %d) wyslal oferte dla %s (UID: %d). Typ oferty: %s, nazwa: %s, wartosc: %d, cena: $%d, PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerRealName(customerid), PlayerCache(customerid)(pUID), OfferTypeInfo(type)(oTypeName), offer_name, value, price)

	if(type == OFFER_HIRE_CAR)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Wypozyczenie~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)
		
		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)
		
		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)
		
   		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
	)
	if(type == OFFER_ITEM)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Przedmiot~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)
		
		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)
		
		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)
		
   		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		//Offer(playerid)(oPayType) = PAYTYPE_NONE
		Offer(playerid)(oPayType) = PAYTYPE_CASH
		
		return 1
	)
	if(type == OFFER_VEHICLE)
	(
 		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Pojazd~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

   		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_PRODUCT)
	(
		product_id = GetProductID(value)
		Float:weight = GetItemTypeWeight(ProductInfo(product_id)(pType))
		
		if(weight ) GetPlayerEqSpace(customerid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz, któremu wysy³asz ofertê nie ma wystarczaj¹co miejsca w swoim ekwipunku., OK, )
			return 0
		)
	
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Produkt~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)
	
		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_VCARD)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Nowy kontakt~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_PASSAGE)
	(
		if(price ) 10)
		(
			GuiMsg(playerid, Wprowadzono nieprawid³ow¹ kwotê., 1)
			return 0
		)
		
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$/100m~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_CASH
		return 1
	)
	if(type == OFFER_REFUEL)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_PAINT)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_REPAIR)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_REPAIR_ENGINE)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_REPAIR_BODY)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_REPAIR_FLUIDS)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_REPAIR_FILTER)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_REPAIR_COOLER)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_DOOR)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Nieruchomosc~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
	 	return 1
	)
	if(type == OFFER_MANDATE)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Mandat~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~PKT. Karne: ~p~~h~%d~n~Powod: ~y~~h~%s, PlayerName(playerid), price, value, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_TOWING)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_HEAL)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_AD)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s~n~Czas: ~p~~h~%d min, PlayerName(playerid), price, offer_name, value)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_MONTAGE)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_PAINTJOB)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s (PaintJobID: %d), PlayerName(playerid), price, offer_name, value)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_DOCUMENT)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Dokument~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_SALON)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Nowy pojazd~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_LESSON)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_LIFE)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Ubezpieczenie~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Czas: ~y~~h~%s na tydzieñ, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)
		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_TRAIN)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_PAINTBALL)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_UNBLOCK)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price
		
		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_TAX)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Podatek~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_KEYS)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Przedmiot~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_INTERIOR)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Wnetrze~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_PREVIEW)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Podglad~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_WELCOME)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Powitanie~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_AREA)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Teren~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_REGISTER)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_FEE)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Usluga~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_SEX)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Stosunek plciowy~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Jestem za mlody)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	if(type == OFFER_HOTDOG)
	(
		format(string, sizeof(string), ~b~~h~Oferta ~)~ ~w~Cieply Hotdog~n~~n~Oferujacy: ~r~~h~%s~n~Koszt: ~g~~h~%d$~n~Nazwa: ~y~~h~%s, PlayerName(playerid), price, offer_name)
  		TextDrawSetString(Text:TextDrawOfferTitle(customerid), string)

		TextDrawShowForPlayer(customerid, Text:TextDrawOfferBack)
  		TextDrawShowForPlayer(customerid, Text:TextDrawOfferTitle(customerid))
		ShowPlayerDialog(customerid, D_OFFER, DIALOG_STYLE_MSGBOX, Oferta, Czy akceptujesz ofertê tego gracza?, Tak, Nie)

		SendClientMessage(playerid, COLOR_INFO, Oferta zosta³a wys³ana. Odczekaj chwilê, by przekonaæ siê, czy gracz zaakceptuje Twoj¹ ofertê.)

		Offer(playerid)(oCustomerID) = customerid
		Offer(playerid)(oType) = type
		strmid(Offer(playerid)(oName), offer_name, 0, strlen(offer_name), 32)
		Offer(playerid)(oValue) = value
		Offer(playerid)(oPrice) = price

		Offer(playerid)(oPayType) = PAYTYPE_NONE
		return 1
	)
	return 1
)

public OnPlayerAcceptOffer(playerid, offererid)
(
	string(256)
	TextDrawHideForPlayer(playerid, Text:TextDrawOfferBack)
	TextDrawHideForPlayer(playerid, Text:TextDrawOfferTitle(playerid))
	
	sender_uid = PlayerCache(offererid)(pUID)
	player_uid = PlayerCache(playerid)(pUID)
	
	if(!PlayerToPlayer(5.0, playerid, offererid))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz znajduje siê zbyt daleko od Ciebie., OK, )
		OnPlayerRejectOffer(playerid, offererid)
		return 1
	)
	
	if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
	(
		if(Offer(offererid)(oPrice) ) PlayerCache(playerid)(pCash))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiedniej iloœci gotówki., OK, )
		 	OnPlayerRejectOffer(playerid, offererid)
			return 1
		)
	)
	
	if(Offer(offererid)(oPayType) == PAYTYPE_CARD)
	(
		if(Offer(offererid)(oPrice) ) PlayerCache(playerid)(pBankCash))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiedniej iloœci pieniêdzy na karcie., OK, )
		 	OnPlayerRejectOffer(playerid, offererid)
			return 1
		)
	)

	if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
	(
		cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
		if(!IsCardValid(cardid, Offer(offererid)(oPrice)))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie posiadasz odpowiedniej iloœci piniêdzy na firmowej karcie., OK, )
		 	OnPlayerRejectOffer(playerid, offererid)
			return 1
		)	
	)
	
	if(Offer(offererid)(oType) == OFFER_HIRE_CAR)
	(
		price = Offer(offererid)(oPrice)
		group_id_fix = GetPlayerDutyGroupID(offererid)
		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)

			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Wypozyczenie)
		)
		
		
		lesson_time = Offer(offererid)(oValue)
		PlayerCache(playerid)(pHireTime) = lesson_time * 60
		
		PlayerCache(playerid)(pHireGroup) = group_id_fix
	)
	
	if(Offer(offererid)(oType) == OFFER_ITEM)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, price)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += price
			)
		)
		itemid = GetItemID(Offer(offererid)(oValue))

		if(ItemInfo(itemid)(iType) == ITEM_WEAPON && ItemInfo(itemid)(iUsed))
		(
			OnPlayerUseItem(playerid, itemid)
		)
		
		format(string, sizeof(string), UPDATE hrp_items SET item_owner = %d WHERE item_uid = %d LIMIT 1, PlayerCache(playerid)(pUID), ItemInfo(itemid)(iUID))
		mysql_query(string)
		
		ItemInfo(itemid)(iOwner) = PlayerCache(playerid)(pUID)
		
		format(string, sizeof(string), * %s podaje przedmiot %s., PlayerName(offererid), PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)

		hrp_ItemActionLog(%s (UID: %d) podal przedmiot %s (UID: %d) dla %s (UID: %d) za kwote $%d., PlayerRealName(offererid), PlayerCache(offererid)(pUID), ItemInfo(itemid)(iName), ItemInfo(itemid)(iUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), price)
	)
	if(Offer(offererid)(oType) == OFFER_VEHICLE)
	(
		vehid = Offer(offererid)(oValue),
			price = Offer(offererid)(oPrice)
	
		if(price)
		(
			if(CarInfo(vehid)(cOwnerType) == OWNER_GROUP)
			(
				group_uid = CarInfo(vehid)(cOwner),
					group_id_fix = GetGroupID(group_uid)
					
				GroupData(group_id_fix)(gCash) += price
				SaveGroup(group_id_fix)
				
				if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
				(
					hrp_GivePlayerMoney(playerid, -price)
				)
				else
				(
					PlayerCache(playerid)(pBankCash) -= price
				)
			)
			else
			(
				if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
				(
					hrp_GivePlayerMoney(playerid, -price)
					hrp_GivePlayerMoney(offererid, price)
				)
				else
				(
					PlayerCache(playerid)(pBankCash) -= price
					PlayerCache(offererid)(pBankCash) += price
				)
			)
		)
		
		CarInfo(vehid)(cOwnerType) = OWNER_PLAYER
		CarInfo(vehid)(cOwner) = PlayerCache(playerid)(pUID)
		
		PlayerCache(offererid)(pCarSpawned) --
		
		SaveVehicle(vehid, SAVE_VEH_THINGS)
		if(!PlayerCache(playerid)(pPremium))
		(
			if(PlayerCache(playerid)(pCarSpawned) )= STANDARD_VEHICLES)
			(
				UnspawnVehicle(CarInfo(vehid)(cUID))
			)
			else
			(
	  			PlayerCache(playerid)(pCarSpawned) ++
			)
		)
		else
		(
			if(PlayerCache(playerid)(pCarSpawned) )= PREMIUM_VEHICLES)
			(
				UnspawnVehicle(CarInfo(vehid)(cUID))
			)
			else
			(
	  			PlayerCache(playerid)(pCarSpawned) ++
			)
		)
		format(string, sizeof(string), Pojazd %s (SampID: %d, UID: %d) kupiony.\nU¿yj komendy /pomoc aby poznaæ szczegó³y dotycz¹ce pojazdów., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		hrp_VehicleActionLog(Wlasciciel pojazdu %s (UID: %d) zmienil sie. Stary wlasciciel %s (UID: %d). Nowy wlasciciel %s (UID: %d). Kwota sprzedazy: $%d, CarInfo(vehid)(cName), CarInfo(vehid)(cUID), PlayerRealName(offererid), PlayerCache(offererid)(pUID), PlayerRealName(playerid), PlayerCache(playerid)(pUID), price)
	)
	if(Offer(offererid)(oType) == OFFER_PRODUCT)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += playercash
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)
			
			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Sprzedaz produktu)
		)
		
		product_id = GetProductID(Offer(offererid)(oValue))
		CreatePlayerItem(playerid, ProductInfo(product_id)(pName), ProductInfo(product_id)(pType), ProductInfo(product_id)(pValue1), ProductInfo(product_id)(pValue2))

		ProductInfo(product_id)(pNumber) --
		if(ProductInfo(product_id)(pNumber) ( 1)
		(
			DeleteProduct(product_id)
		)
		else
		(
			SaveProduct(product_id, SAVE_PRODUCT_VALUES)
		)
		
		format(string, sizeof(string), * %s podaje przedmiot %s., PlayerName(offererid), PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)

		MainPlayerTable(offererid) = 0
	)
	if(Offer(offererid)(oType) == OFFER_VCARD)
	(
		format(string, sizeof(string), * %s wysy³a wizytówkê %s., PlayerName(offererid), PlayerName(playerid))
		FlashMe(playerid, string) //ProxDetector(10.0, offererid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, false)

		MainPlayerTable(playerid) = Offer(offererid)(oValue)
		ShowPlayerDialog(playerid, D_TEL_ADDNAME, DIALOG_STYLE_INPUT, Dodawanie kontaktu, Wpisz nazwê kontaktu, który dodajesz., OK, Anuluj)
	)
	if(Offer(offererid)(oType) == OFFER_PASSAGE)
	(
		PlayerCache(offererid)(pTaxiPassenger) = playerid
		
		PlayerCache(playerid)(pTaxiVeh) = Offer(offererid)(oValue)
		PlayerCache(playerid)(pTaxiPrice) = Offer(offererid)(oPrice)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Od teraz skrypt naliczy ka¿de przejechane 100 metrów.\nSkrypt automatycznie zabierze Ci pieni¹dze po opuszczeniu pojazdu., OK, )
	)
	if(Offer(offererid)(oType) == OFFER_PAINT)
	(
	
 		price = Offer(offererid)(oPrice)

		if(price)
		(
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, price)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += price
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += price
			)
		)
		color1 = PlayerCache(playerid)(pSprayColor)(0),
			color2 = PlayerCache(playerid)(pSprayColor)(1)

		group_id_fix = GetPlayerDutyGroupID(offererid)

		PlayerCache(offererid)(pSprayVeh) = GetPlayerVehicleID(playerid)
		PlayerCache(offererid)(pSprayTime) = 120

		PlayerCache(offererid)(pSprayColor)(0) = color1
		PlayerCache(offererid)(pSprayColor)(1) = color2
		
		PlayerCache(offererid)(pSprayType) = 1

		if (group_id_fix != INVALID_GROUP_ID)(
			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, 0, Lakierowanie pojazdu)
		)

		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Zaakceptowa³eœ us³ugê lakierowania pojazdu.\nTeraz odczekaj a¿ mechanik skoñczy lakierowaæ pojazd., OK, )


	)
	if(Offer(offererid)(oType) == OFFER_REPAIR)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
  			group_cash = floatround(0.20 * price),
				playercash = floatround(0.30 * price)
				
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += playercash
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			
			if(PlayerCache(offererid)(pGroupDuty))
			(
				group_id_fix = GetPlayerDutyGroupID(offererid)
				if(GroupData(group_id_fix)(gType) == GROUP_WORKSHOP || GroupData(group_id_fix)(gType) == GROUP_GASSTATION)
				(
					GroupData(group_id_fix)(gCash) += group_cash
					SaveGroup(group_id_fix)
					
	   				format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
					ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

					AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Naprawa silnika)
				)
			)
		)
		vehid = Offer(offererid)(oValue)
		
		PlayerCache(offererid)(pRepairVeh) = vehid
		PlayerCache(offererid)(pRepairType) = REPAIR_STANDARD
		PlayerCache(offererid)(pRepairTime) = 180
	)
	if(Offer(offererid)(oType) == OFFER_REPAIR_ENGINE)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
  			group_cash = floatround(0.035 * price),
				playercash = floatround(0.050 * price)
				
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += playercash
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			
			if(PlayerCache(offererid)(pGroupDuty))
			(
				group_id_fix = GetPlayerDutyGroupID(offererid)
				if(GroupData(group_id_fix)(gType) == GROUP_WORKSHOP || GroupData(group_id_fix)(gType) == GROUP_GASSTATION)
				(
					GroupData(group_id_fix)(gCash) += group_cash
					SaveGroup(group_id_fix)
					
	   				format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
					ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

					AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Rekonstrukcja silnika)
				)
			)
		)
		vehid = Offer(offererid)(oValue)
		
		PlayerCache(offererid)(pRepairVeh) = vehid
		PlayerCache(offererid)(pRepairType) = REPAIR_ENGINE
		PlayerCache(offererid)(pRepairTime) = 900
	)
	if(Offer(offererid)(oType) == OFFER_REPAIR_BODY)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
  			group_cash = floatround(0.20 * price),
				playercash = floatround(0.30 * price)
				
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += playercash
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			
			if(PlayerCache(offererid)(pGroupDuty))
			(
				group_id_fix = GetPlayerDutyGroupID(offererid)
				if(GroupData(group_id_fix)(gType) == GROUP_WORKSHOP || GroupData(group_id_fix)(gType) == GROUP_GASSTATION)
				(
					GroupData(group_id_fix)(gCash) += group_cash
					SaveGroup(group_id_fix)
					
	   				format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
					ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

					AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Naprawa karoserii)
				)
			)
		)
		vehid = Offer(offererid)(oValue)
		
		PlayerCache(offererid)(pRepairVeh) = vehid
		PlayerCache(offererid)(pRepairType) = REPAIR_BODY
		PlayerCache(offererid)(pRepairTime) = 600
	)
	if(Offer(offererid)(oType) == OFFER_REPAIR_FLUIDS)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
  			group_cash = floatround(0.20 * price),
				playercash = floatround(0.30 * price)
				
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += playercash
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			
			if(PlayerCache(offererid)(pGroupDuty))
			(
				group_id_fix = GetPlayerDutyGroupID(offererid)
				if(GroupData(group_id_fix)(gType) == GROUP_WORKSHOP || GroupData(group_id_fix)(gType) == GROUP_GASSTATION)
				(
					GroupData(group_id_fix)(gCash) += group_cash
					SaveGroup(group_id_fix)
					
	   				format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
					ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

					AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Wymiana plynow w wozie)
				)
			)
		)
		vehid = Offer(offererid)(oValue)
		
		PlayerCache(offererid)(pRepairVeh) = vehid
		PlayerCache(offererid)(pRepairType) = REPAIR_FLUIDS
		PlayerCache(offererid)(pRepairTime) = 120
	)
	if(Offer(offererid)(oType) == OFFER_REPAIR_FILTER)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
  			group_cash = floatround(0.20 * price),
				playercash = floatround(0.30 * price)
				
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += playercash
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			
			if(PlayerCache(offererid)(pGroupDuty))
			(
				group_id_fix = GetPlayerDutyGroupID(offererid)
				if(GroupData(group_id_fix)(gType) == GROUP_WORKSHOP || GroupData(group_id_fix)(gType) == GROUP_GASSTATION)
				(
					GroupData(group_id_fix)(gCash) += group_cash
					SaveGroup(group_id_fix)
					
	   				format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
					ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

					AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Wymiana filtra w wozie)
				)
			)
		)
		vehid = Offer(offererid)(oValue)
		
		PlayerCache(offererid)(pRepairVeh) = vehid
		PlayerCache(offererid)(pRepairType) = REPAIR_FILTER
		PlayerCache(offererid)(pRepairTime) = 180
	)
	if(Offer(offererid)(oType) == OFFER_REPAIR_COOLER)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
  			group_cash = floatround(0.20 * price),
				playercash = floatround(0.30 * price)
				
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += playercash
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			
			if(PlayerCache(offererid)(pGroupDuty))
			(
				group_id_fix = GetPlayerDutyGroupID(offererid)
				if(GroupData(group_id_fix)(gType) == GROUP_WORKSHOP || GroupData(group_id_fix)(gType) == GROUP_GASSTATION)
				(
					GroupData(group_id_fix)(gCash) += group_cash
					SaveGroup(group_id_fix)
					
	   				format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
					ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

					AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Wymiana chlodnicy)
				)
			)
		)
		vehid = Offer(offererid)(oValue)
		
		PlayerCache(offererid)(pRepairVeh) = vehid
		PlayerCache(offererid)(pRepairType) = REPAIR_COOLER
		PlayerCache(offererid)(pRepairTime) = 360
	)
	if(Offer(offererid)(oType) == OFFER_DOOR)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, price)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += price
			)
		)
		doorid = Offer(offererid)(oValue)
		
		if(DoorData(doorid)(dOwnerType) == OWNER_PLAYER)
		(
			foreach(Player, i)
			(
   				if(Logged(i) && Spawned(i))
				(
					if(PlayerCache(i)(pHouse) == DoorData(doorid)(dUID))
					(
						PlayerCache(i)(pHouse) = 0
					)
				)
			)

			mysql_query_format(UPDATE hrp_characters SET char_house = 0 WHERE char_house = %d, DoorData(doorid)(dUID))
		)
		
		DoorData(doorid)(dOwnerType) = OWNER_PLAYER
		DoorData(doorid)(dOwner) = PlayerCache(playerid)(pUID)
		
		SaveDoor(doorid, SAVE_DOOR_THINGS)
		
		format(string, sizeof(string), Gratulacje, zakupi³eœ now¹ nieruchomoœæ %s (SampID: %d, UID: %d).\nNieruchomoœci¹ mo¿esz zarz¹dzaæ poprzez komendê /drzwi., DoorData(doorid)(dName), doorid, DoorData(doorid)(dUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	)
	if(Offer(offererid)(oType) == OFFER_MANDATE)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)
		
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += playercash
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Mandat)
			
			//dodanie do kartoteki
			/*buffer(256)
			format(buffer,sizeof(buffer),INSERT INTO lspd_mandats VALUES(NULL,%s,%s,%i,%i,%s,%s,%s),
			PlayerName(playerid),PlayerName(offererid),price,Offer(playerid)(oValue),Offer(playerid)(oName),null,null)
			mysql_query(buffer)*/
			
		)
		PlayerCache(playerid)(pPDP) += Offer(offererid)(oValue)
		
		AddPlayerReasonToDirectory(playerid, Offer(offererid)(oName))
		SaveTicket(PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), Offer(offererid)(oName), price)
	)
	if(Offer(offererid)(oType) == OFFER_TOWING)
	(
		if(!IsPlayerInAnyVehicle(offererid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz, który zaoferowa³ Ci holowanie, musi siedzieæ w pojeŸdzie., OK, )
			OnPlayerRejectOffer(playerid, offererid)
			return 1
		)
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, price)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += price
			)
		)
		
		vehid = GetPlayerVehicleID(offererid)
		AttachTrailerToVehicle(Offer(offererid)(oValue), vehid)

		CarInfo(vehid)(cTowedVeh) = Offer(offererid)(oValue)

		TextDrawSetString(Text:TextDrawMainInfo(offererid), Pojazd zostal ~r~podczepiony~w~, aby go odczepic wcisnij klawisz ~g~~k~~VEHICLE_FIREWEAPON_ALT~~w~.)
		TextDrawShowForPlayer(offererid, Text:TextDrawMainInfo(offererid))

		PlayerCache(offererid)(pShowInfoText) = 5
	)
	if(Offer(offererid)(oType) == OFFER_HEAL)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Leczenie)
		)
		PlayerCache(playerid)(pWounded) = 0
		PlayerCache(playerid)(pBleeding) = 0
		PlayerCache(offererid)(pHealing) = playerid
		
		format(string, sizeof(string), Postanowi³eœ uleczyæ gracza %s.\nProces leczenia potrwa chwile, nie oddalaj siê od pacjenta., PlayerName(playerid))
		ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

		format(string, sizeof(string), Gracz %s postanowi³ Ciê uleczyæ.\nProces leczenia potrwa chwile, nie oddalaj siê od medyka., PlayerName(offererid))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	)
	if(Offer(offererid)(oType) == OFFER_AD)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)
				
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Reklama WN)
		)
	)
	if(Offer(offererid)(oType) == OFFER_MONTAGE)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, price)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += price
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += price
			)
		)
		itemid = Offer(offererid)(oValue)
		ItemInfo(itemid)(iUsed) = 1
		
		PlayerCache(offererid)(pMontageItem) = itemid
		
  		PlayerCache(offererid)(pMontageVeh) = GetPlayerVehicleID(playerid)
		PlayerCache(offererid)(pMontageTime) = 120
	)
	if(Offer(offererid)(oType) == OFFER_PAINTJOB)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, price)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += price
			)
		)
  		PlayerCache(offererid)(pSprayVeh) = GetPlayerVehicleID(playerid)
		PlayerCache(offererid)(pSprayTime) = 600

		PlayerCache(offererid)(pSprayColor)(0) = Offer(offererid)(oValue)
		PlayerCache(offererid)(pSprayType) = 2

		group_id_fix = GetPlayerDutyGroupID(offererid)

		if (group_id_fix != INVALID_GROUP_ID)(
			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, 0, Paintjob)
		)
	)
	if(Offer(offererid)(oType) == OFFER_DOCUMENT)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Dokument w urzedzie)
		)
		PlayerCache(playerid)(pDocuments) += Offer(offererid)(oValue)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Zakupi³eœ nowy dokument.\nU¿yj komendy /pokaz, aby zarz¹dzaæ dokumentami., OK, )
	)
	if(Offer(offererid)(oType) == OFFER_REFUEL)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
   			group_cash = floatround(0.80 * price),
				playercash = floatround(0.20 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else if(Offer(offererid)(oPayType) == PAYTYPE_BCARD)
			(
				cardid = GetCardID(PlayerCache(playerid)(pBusinessCard))
				ChargeCard(cardid, price)
				PlayerCache(playerid)(pBusinessCard) = -1
				SaveCard(cardid)

				PlayerCache(offererid)(pBankCash) += playercash
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)

			if(PlayerCache(offererid)(pGroupDuty))
			(
				group_id_fix = GetPlayerDutyGroupID(offererid)
				if(GroupData(group_id_fix)(gType) == GROUP_GASSTATION)
				(
					GroupData(group_id_fix)(gCash) += group_cash
					SaveGroup(group_id_fix)
					
					format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
					ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
				)
			)
		)
		vehid = GetPlayerVehicleID(playerid), value = Offer(offererid)(oValue)

		CarInfo(vehid)(cFuel) = floatadd(CarInfo(vehid)(cFuel), value)
		SaveVehicle(vehid, SAVE_VEH_COUNT)

		format(string, sizeof(string), Zap³aci³eœ $%d za %d litrów paliwa., price, value)
		SendClientMessage(playerid, COLOR_LIGHTBLUE, string)

		ApplyAnimation(offererid, INT_HOUSE, wash_up,4.1, 0, 0, 0, 0, 0, 1)

		format(string, sizeof(string), * %s wk³ada w¹¿ do baku., PlayerName(offererid))
		FlashMe(playerid, string) //ProxDetector(10.0, offererid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, true)

		format(string, sizeof(string), * Pojazd %s zosta³ pomyœlnie zatankowany (( %s )), CarInfo(vehid)(cName), PlayerName(offererid))
  		ProxDetector(10.0, offererid, string, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, COLOR_DO, true)
	)
	if(Offer(offererid)(oType) == OFFER_SALON)
	(
		price = Offer(offererid)(oPrice)
		
		if(price)
		(
  			group_cash = floatround(0.1 * price)
			//playercash = floatround(0.001 * price)
				
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				//hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				//PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Sprzedaz pojazdu)

			//format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			//ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		)		
		salonveh_model = Offer(offererid)(oValue), spawn_point, vehid
		
		
		if(salonveh_model == 472 || salonveh_model == 473 || salonveh_model == 493 || salonveh_model == 595 || salonveh_model == 484 || salonveh_model == 430 || salonveh_model == 453 || salonveh_model == 452 || salonveh_model == 446 || salonveh_model == 454)
		(
			// Lodzie
			spawn_point = 3
		)
		else if(salonveh_model == 417 || salonveh_model == 425 || salonveh_model == 447 || salonveh_model == 460 || salonveh_model == 469 || salonveh_model == 476 || salonveh_model == 487 || salonveh_model == 488 || salonveh_model == 497 || salonveh_model == 511 || salonveh_model == 512 || salonveh_model == 5133 || salonveh_model == 519 || salonveh_model == 520 || salonveh_model == 548 || salonveh_model == 553 || salonveh_model == 563 || salonveh_model == 577 || salonveh_model == 592 || salonveh_model == 593)
		(
			// Samoloty
			spawn_point = 4
		)
		else
		(
			spawn_point = random(sizeof(SalonVehSpawnPos)-2)
		)
		
		vehid = CreateCar(salonveh_model, SalonVehSpawnPos(spawn_point)(0), SalonVehSpawnPos(spawn_point)(1), SalonVehSpawnPos(spawn_point)(2), SalonVehSpawnPos(spawn_point)(3), 92, 111, 6000000)
		
		CarInfo(vehid)(cOwnerType) = OWNER_PLAYER
		CarInfo(vehid)(cOwner) = PlayerCache(playerid)(pUID)
		SaveVehicle(vehid, SAVE_VEH_THINGS)
		
		mysql_query_format(UPDATE hrp_cars SET car_timeleft = %d WHERE car_uid = %d, gettime() + 3600, CarInfo(vehid)(cUID))
		UnspawnVehicle(CarInfo(vehid)(cUID))
		
		GuiMsg(playerid, Gratulacje! Zakupi³eœ nowy pojazd.\nMusisz poczekaæ kilka dni a¿ zostanie on dostarczony do miasta., 0)
		
		/*if(!PlayerCache(playerid)(pPremium))
		(
			if(PlayerCache(playerid)(pCarSpawned) )= STANDARD_VEHICLES)
			(
				UnspawnVehicle(CarInfo(vehid)(cUID))
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Gratulacje, zakupi³eœ nowy pojazd.\n\nMasz ju¿ pe³ne prawa dotycz¹ce pojazdu.\n\nPoniewa¿ masz ju¿ zespawnowan¹ maksymaln¹ liczbê pojazdów, pojazd zosta³ odspawnowany.\nU¿yj /v lista, by zespawnowaæ pojazd., OK, )
			)
			else
			(
	  			PlayerCache(playerid)(pCarSpawned) ++

				SetPlayerCheckpoint(playerid, SalonVehSpawnPos(spawn_point)(0), SalonVehSpawnPos(spawn_point)(1), SalonVehSpawnPos(spawn_point)(2), 5.0)
				Checkpoint(playerid) = 1

	  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Gratulacje, zakupi³eœ nowy pojazd.\n\nTwój pojazd pojawi³ siê w hurtowni, mo¿esz go stamt¹d odebraæ.\nMasz ju¿ pe³ne prawa dotycz¹ce pojazdu.\n\nMarker na mapie wska¿e Ci drogê., OK, )
			)
		)
		else
		(
			if(PlayerCache(playerid)(pCarSpawned) )= PREMIUM_VEHICLES)
			(
				UnspawnVehicle(CarInfo(vehid)(cUID))
				ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Gratulacje, zakupi³eœ nowy pojazd.\n\nMasz ju¿ pe³ne prawa dotycz¹ce pojazdu.\n\nPoniewa¿ masz ju¿ zespawnowan¹ maksymaln¹ liczbê pojazdów, pojazd zosta³ odspawnowany.\nU¿yj /v lista, by zespawnowaæ pojazd., OK, )
			)
			else
			(
	  			PlayerCache(playerid)(pCarSpawned) ++

				SetPlayerCheckpoint(playerid, SalonVehSpawnPos(spawn_point)(0), SalonVehSpawnPos(spawn_point)(1), SalonVehSpawnPos(spawn_point)(2), 5.0)
				Checkpoint(playerid) = 1

	  			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Gratulacje, zakupi³eœ nowy pojazd.\n\nTwój pojazd pojawi³ siê w hurtowni, mo¿esz go stamt¹d odebraæ.\nMasz ju¿ pe³ne prawa dotycz¹ce pojazdu.\n\nMarker na mapie wska¿e Ci drogê., OK, )
			)
		)*/
	)
	if(Offer(offererid)(oType) == OFFER_LESSON)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)

			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Lekcja)
		)
		lesson_time = Offer(offererid)(oValue)
		PlayerCache(playerid)(pDrivingLesson) = lesson_time * 60
	)
	if(Offer(offererid)(oType) == OFFER_LIFE)
	(
		price = Offer(offererid)(oPrice)
		group_id_fix

		if(price)
		(
   			group_cash = floatround(0.95 * price),
				playercash = floatround(0.05 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)

			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)
		
			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		)
		format(string, sizeof(string), UPDATE hrp_characters SET char_insurance = %d, char_insurancecomp = %d, char_insurancecount = 0 WHERE char_uid = %d LIMIT 1, gettime() + 604800, GroupData(group_id_fix)(gUID), PlayerCache(playerid)(pUID))
		mysql_query(string)
		PlayerCache(playerid)(pInsurance) = gettime() + 604800
		PlayerCache(playerid)(pInsuranceCompany) = GroupData(group_id_fix)(gUID)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Zakupi³eœ ubezpieczenie. Bêdzie ono aktywne przez równy tydzieñ., OK, )

	)
	if(Offer(offererid)(oType) == OFFER_TRAIN)
	(
		price = Offer(offererid)(oPrice)
		group_id_fix

		if(price)
		(
   			group_cash = floatround(0.50 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)

			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Karnet)
		)
		train_time = Offer(offererid)(oValue)
		
		name(64)
		format(name, sizeof(name), Kartnet - %s, GroupData(group_id_fix)(gName))
		CreatePlayerItem(playerid, name, ITEM_PASS, train_time, PlayerCache(offererid)(pGroupDuty))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Zakupi³eœ karnet. Przedmiot znajdziesz w swoim ekwipunku.\nAby u¿yæ przedmiotu skorzystaj z komendy /u., OK, )

	)
	if(Offer(offererid)(oType) == OFFER_PAINTBALL)
	(
		price = Offer(offererid)(oPrice)
		group_id_fix

		if(price)
		(
   			group_cash = floatround(0.50 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)

			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Wejsciowka Paintball)
		)
		paintball_time = Offer(offererid)(oValue)
		
		name(64)
		format(name, sizeof(name), Wejœciówka Paintball - %s, GroupData(group_id_fix)(gName))
		CreatePlayerItem(playerid, name, ITEM_PBENTRY, paintball_time, PlayerCache(offererid)(pGroupDuty))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Zakupi³eœ wejœciówka. Przedmiot znajdziesz w swoim ekwipunku.\nAby u¿yæ przedmiotu skorzystaj z komendy /u., OK, )

	)
	if(Offer(offererid)(oType) == OFFER_UNBLOCK)
	(
		price = Offer(offererid)(oPrice)
		
   		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Odblokowanie pojazdu)
		)
		vehid = Offer(offererid)(oValue)
		
		CarInfo(vehid)(cWheelBlock) = 0
		SaveVehicle(vehid, SAVE_VEH_ACCESS)
		
		format(string, sizeof(string), Blokada zosta³a zdjêta z ko³a %s (SampID: %d, UID: %d).\nNastêpnym razem uwa¿aj gdzie parkujesz., CarInfo(vehid)(cName), vehid, CarInfo(vehid)(cUID))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	)
	if(Offer(offererid)(oType) == OFFER_KEYS)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Kluczyki)
		)
		vehid = Offer(offererid)(oValue)
		
		format(string, sizeof(string), Kluczyki do %s, CarInfo(vehid)(cName))
		CreatePlayerItem(playerid, string, ITEM_KEYS, CarInfo(vehid)(cUID), 0)

		format(string, sizeof(string), Kluczyki do pojazdu %s zosta³y pomyœlnie wyrobione.\nPrzedmiot pojawi³ siê w Twoim ekwipunku., CarInfo(vehid)(cName))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	)
	if(Offer(offererid)(oType) == OFFER_INTERIOR)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
   			group_cash = floatround(0.30 * price),
				playercash = floatround(0.05 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Interior)
		)
		doorid = Offer(offererid)(oValue), interior_id = MainPlayerTable(offererid)
		
		DoorData(doorid)(dExitX) = Interiors(interior_id)(INTERIOR_X)
		DoorData(doorid)(dExitY) = Interiors(interior_id)(INTERIOR_Y)
		DoorData(doorid)(dExitZ) = Interiors(interior_id)(INTERIOR_Z)
		DoorData(doorid)(dExitAng) = Interiors(interior_id)(INTERIOR_A)
		
		DoorData(doorid)(dExitInt) = Interiors(interior_id)(INTERIOR_ID)
		DoorData(doorid)(dExitVW) = DoorData(doorid)(dUID)
		
		SaveDoor(doorid, SAVE_DOOR_EXIT)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Gratulacje, zakupi³eœ wnêtrze do swojego budynku!\nOd teraz po wejœciu do œrodka ujrzysz swoje nowo zakupione wnêtrze., OK, )
	)
	if(Offer(offererid)(oType) == OFFER_PREVIEW)
	(
		interior_id = Offer(offererid)(oValue)
		
		GetPlayerPos(offererid, PlayerCache(offererid)(pPosX), PlayerCache(offererid)(pPosY), PlayerCache(offererid)(pPosZ))
		PlayerCache(offererid)(pInt) = GetPlayerInterior(offererid)
		PlayerCache(offererid)(pVW) = GetPlayerVirtualWorld(offererid)
		
		GetPlayerPos(playerid, PlayerCache(playerid)(pPosX), PlayerCache(playerid)(pPosY), PlayerCache(playerid)(pPosZ))
		PlayerCache(playerid)(pInt) = GetPlayerInterior(playerid)
		PlayerCache(playerid)(pVW) = GetPlayerVirtualWorld(playerid)

		hrp_SetPlayerPos(offererid, Interiors(interior_id)(INTERIOR_X), Interiors(interior_id)(INTERIOR_Y), Interiors(interior_id)(INTERIOR_Z))
		SetPlayerInterior(offererid, Interiors(interior_id)(INTERIOR_ID))
		
		hrp_SetPlayerPos(playerid, Interiors(interior_id)(INTERIOR_X), Interiors(interior_id)(INTERIOR_Y), Interiors(interior_id)(INTERIOR_Z))
		SetPlayerInterior(playerid, Interiors(interior_id)(INTERIOR_ID))
		
		PlayerCache(offererid)(pPreviewTime) = 30
		PlayerCache(playerid)(pPreviewTime) = 30
	)
	if(Offer(offererid)(oType) == OFFER_WELCOME)
	(
		welcome_type = Offer(offererid)(oValue),
			Float:PosX, Float:PosY, Float:PosZ, Float:PosA

		GetPlayerPos(offererid, PosX, PosY, PosZ)
		
		if(welcome_type (= 6)
		(
			GetXYInFrontOfPlayer(offererid, PosX, PosY, 1.0)
		)
		else
		(
			GetXYInFrontOfPlayer(offererid, PosX, PosY, 0.5)
		)
		
		GetPlayerFacingAngle(offererid, PosA)

		if(!IsPlayerInGroupType(playerid, GROUP_PRISON) && !IsPlayerInGroupType(offererid, GROUP_PRISON))
		(
			SetPlayerPos(playerid, PosX, PosY, PosZ)
		)
		SetPlayerFacingAngle(playerid, (floatabs(PosA) - 180.0))
		
		switch(welcome_type)
		(
			case 1:
			(
  				ApplyAnimation(offererid, GANGS, hndshkfa, 4.1, 0, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, GANGS, hndshkfa, 4.1, 0, 0, 0, 0, 0, 1)
			)
			case 2:
			(
  				ApplyAnimation(offererid, GANGS, hndshkba, 4.1, 0, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, GANGS, hndshkba, 4.1, 0, 0, 0, 0, 0, 1)
			)
			case 3:
			(
				ApplyAnimation(offererid, GANGS, hndshkaa, 4.1, 0, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, GANGS, hndshkaa, 4.1, 0, 0, 0, 0, 0, 1)
			)
			case 4:
			(
  				ApplyAnimation(offererid, GANGS, hndshkda, 4.1, 0, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, GANGS, hndshkda, 4.1, 0, 0, 0, 0, 0, 1)
			)
			case 5:
			(
  				ApplyAnimation(offererid, GANGS, hndshkca, 4.1, 0, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, GANGS, hndshkca, 4.1, 0, 0, 0, 0, 0, 1)
			)
			case 6:
			(
  				ApplyAnimation(offererid, GANGS, hndshkcb, 4.1, 0, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, GANGS, hndshkcb, 4.1, 0, 0, 0, 0, 0, 1)
			)
			case 7:
			(
				ApplyAnimation(offererid, KISSING, Playa_Kiss_01, 4.1, 0, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, KISSING, Playa_Kiss_01, 4.1, 0, 0, 0, 0, 0, 1)
			)
			case 8:
			(
				ApplyAnimation(offererid, KISSING, Playa_Kiss_02, 4.1, 0, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, KISSING, Playa_Kiss_02, 4.1, 0, 0, 0, 0, 0, 1)
			)
			case 9:
			(
				ApplyAnimation(offererid, KISSING, Playa_Kiss_03, 4.1, 0, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, KISSING, Playa_Kiss_03, 4.1, 0, 0, 0, 0, 0, 1)
			)
		)
	)
	if(Offer(offererid)(oType) == OFFER_AREA)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, price)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += price
			)
		)
		gangzone_id = Offer(offererid)(oValue), group_id_fix = GetPlayerDutyGroupID(playerid)
		
		GangZoneInfo(gangzone_id)(gOwner) = GroupData(group_id_fix)(gUID)
		SaveGangZone(gangzone_id, SAVE_GZ_OWNER)
		
		// Zmieñ kolorek dla wszystkich
		foreach(Player, i)
		(
			if(Logged(i) && Spawned(i))
			(
				if(IsPlayerInGroupType(i, GROUP_CRIMINAL))
				(
	   				GangZoneHideForPlayer(i, gangzone_id)
	   				GangZoneShowForPlayer(i, gangzone_id, GroupData(group_id_fix)(gColor))
				)
			)
		)
		
		format(string, sizeof(string), Teren, na którym siê znajdujesz nale¿y teraz do %s., GroupData(group_id_fix)(gName))
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
	)
	if(Offer(offererid)(oType) == OFFER_REGISTER)
	(
		price = Offer(offererid)(oPrice)

		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )

			AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, Rejestracja pojazdu)
		)
		vehid = Offer(offererid)(oValue)
		
		CarInfo(vehid)(cRegister) = true
		SaveVehicle(vehid, SAVE_VEH_THINGS)
		
		format(string, sizeof(string), LS%d, CarInfo(vehid)(cUID))
		SetVehicleNumberPlate(vehid, string)
		
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Pojazd zosta³ pomyœlnie zarejestrowany.\nTablice rejestracyjne zmieni³y siê automatycznie., OK, )
	)
	if(Offer(offererid)(oType) == OFFER_FEE)
	(
		price = Offer(offererid)(oPrice)
	
		if(price)
		(
   			group_cash = floatround(0.90 * price),
				playercash = floatround(0.10 * price)

			if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
			(
				hrp_GivePlayerMoney(playerid, -price)
				hrp_GivePlayerMoney(offererid, playercash)
			)
			else
			(
				PlayerCache(playerid)(pBankCash) -= price
				PlayerCache(offererid)(pBankCash) += playercash
			)
			group_id_fix = GetPlayerDutyGroupID(offererid)
			
			GroupData(group_id_fix)(gCash) += group_cash
			SaveGroup(group_id_fix)

			format(string, sizeof(string), Otrzyma³eœ premiê w wysokoœci $%d!\nNa konto grupy dodano: $%d, playercash, group_cash)
			ShowPlayerDialog(offererid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, string, OK, )
		)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Zaakceptowa³eœ ofertê, op³ata zosta³a pobrana., OK, )
	)
	if(Offer(offererid)(oType) == OFFER_SEX)
	(
		sex_type = Offer(offererid)(oValue),
			Float:PosX, Float:PosY, Float:PosZ, Float:PosA

		GetPlayerPos(offererid, PosX, PosY, PosZ)
		GetPlayerFacingAngle(offererid, PosA)
		
		switch(sex_type)
		(
			case SEX_NORMAL:
			(
  				ApplyAnimation(offererid, sex, SEX_1_P, 4.1, 1, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, sex, SEX_1_W, 4.1, 1, 0, 0, 0, 0, 1)
				GetXYInFrontOfPlayer(offererid, PosX, PosY, 0.3)
				SetPlayerPos(playerid, PosX, PosY, PosZ)
				SetPlayerFacingAngle(playerid, (floatabs(PosA) - 180.0))
			)
			case SEX_ORAL:
			(
  				ApplyAnimation(offererid, BLOWJOBZ, BJ_Stand_Loop_W, 4.1, 1, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, BLOWJOBZ, BJ_Stand_Loop_P, 4.1, 1, 0, 0, 0, 0, 1)
				GetXYInFrontOfPlayer(offererid, PosX, PosY, 0.5)
				SetPlayerPos(playerid, PosX, PosY, PosZ)
				SetPlayerFacingAngle(playerid, (floatabs(PosA) - 180.0))
			)
			case SEX_ANAL:
			(
				ApplyAnimation(offererid, sex, SEX_2_P, 4.1, 1, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, sex, SEX_2_W, 4.1, 1, 0, 0, 0, 0, 1)
				GetXYInFrontOfPlayer(offererid, PosX, PosY, 0.2)
				SetPlayerPos(playerid, PosX, PosY, PosZ)
				SetPlayerFacingAngle(playerid, (floatabs(PosA) - 180.0))
			)
			case SEX_DOGGY:
			(
  				//ApplyAnimation(offererid, SEX, SEX_3_P, 4.1, 1, 0, 0, 0, 0, 1)
				//ApplyAnimation(playerid, SEX, SEX_3_W, 4.1, 1, 0, 0, 0, 0, 1)
				ApplyAnimation(offererid, snm, SpankingW, 4.1, 1, 0, 0, 0, 0, 1)
				ApplyAnimation(playerid, snm, SpankingP, 4.1, 1, 0, 0, 0, 0, 1)
				GetXYInFrontOfPlayer(offererid, PosX, PosY, 0.1)
				SetPlayerPos(playerid, PosX, PosY, PosZ)
				SetPlayerFacingAngle(playerid, PosA)
			)
		)
	)
	if(Offer(offererid)(oType) == OFFER_HOTDOG)
	(
		customer = Offer(offererid)(oCustomerID)
			
		CreatePlayerItem(customer, Hotdog, ITEM_FOOD, 60, 0)
		
		hrp_GivePlayerMoney(offererid, 10)
		
		if(Offer(offererid)(oPayType) == PAYTYPE_CASH)
		(
			hrp_GivePlayerMoney(customer, -10)
		)
		else
		(
			PlayerCache(customer)(pBankCash) -= 10
		)
		//AddGroupEvent(GroupData(group_id_fix)(gUID), PlayerCache(offererid)(pUID), PlayerCache(playerid)(pUID), price, group_cash, hotdog)
	)
	
	format(string, sizeof(string), ~w~Oferta gracza ~p~%s ~w~zostala ~g~zaakceptowana~w~., PlayerName(offererid))
	TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
	
	TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
 	PlayerCache(playerid)(pShowInfoText) = 5

	format(string, sizeof(string), ~w~Gracz ~p~%s ~w~zaakceptowal Twoja oferte., PlayerName(playerid))
	TextDrawSetString(Text:TextDrawMainInfo(offererid), string)
	
	TextDrawShowForPlayer(offererid, Text:TextDrawMainInfo(offererid))
	PlayerCache(offererid)(pShowInfoText) = 5
	
	hrp_OfferActionLog(Gracz %s (UID: %d) zaakceptowal oferte gracza %s (UID: %d). Typ oferty: %s, wartosc: %d, cena: %d, PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerRealName(offererid), PlayerCache(offererid)(pUID), OfferTypeInfo(Offer(offererid)(oType))(oTypeName), Offer(offererid)(oValue), Offer(offererid)(oPrice))

	SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
	SavePlayerStats(offererid, SAVE_PLAYER_BASIC)
	
	blint_SaveCash(player_uid, playerid)
	blint_SaveCash(sender_uid, offererid)

	Offer(offererid)(oCustomerID)	= INVALID_PLAYER_ID
	Offer(offererid)(oType) 		= 0
	Offer(offererid)(oValue) 		= 0
	
	Offer(offererid)(oPrice) 		= 0
	Offer(offererid)(oPayType) 		= PAYTYPE_NONE
	return 1
)

public OnPlayerRejectOffer(playerid, offererid)
(
	string(128)
	TextDrawHideForPlayer(playerid, Text:TextDrawOfferBack)
	TextDrawHideForPlayer(playerid, Text:TextDrawOfferTitle(playerid))
	
	format(string, sizeof(string), ~w~Oferta gracza ~p~%s zostala ~r~odrzucona~w~., PlayerName(offererid))
	GameTextForPlayer(playerid, string, 4000, 3)

	format(string, sizeof(string), ~w~Gracz ~p~%s ~r~odrzucil ~w~Twoja oferte., PlayerName(playerid))
	GameTextForPlayer(offererid, string, 4000, 3)
	
	hrp_OfferActionLog(Gracz %s (UID: %d) odrzucil oferte gracza %s (UID: %d). Typ oferty: %s, wartosc: %d, cena: %d, PlayerRealName(playerid), PlayerCache(playerid)(pUID), PlayerRealName(offererid), PlayerCache(offererid)(pUID), OfferTypeInfo(Offer(offererid)(oType))(oTypeName), Offer(offererid)(oValue), Offer(offererid)(oPrice))

	Offer(offererid)(oCustomerID)	= INVALID_PLAYER_ID
	Offer(offererid)(oType)  		= 0
	Offer(offererid)(oValue) 		= 0
	
	Offer(offererid)(oPrice) 		= 0
	Offer(offererid)(oPayType) 		= PAYTYPE_NONE
	return 1
)

stock ClearOffer(offererid)
(
	Offer(offererid)(oCustomerID)	= INVALID_PLAYER_ID
	Offer(offererid)(oType) 		= 0
	Offer(offererid)(oValue) 		= 0
	
	Offer(offererid)(oPrice) 		= 0
	Offer(offererid)(oPayType) 		= PAYTYPE_NONE
	return 1
)