/*
	bGUI = blint GUI, taka sobie robocza nazwa :3
*/

stock bGUI_LoadTextdraws(playerid)
(
	// kafelki mia³y ID 1 fontu
	TextDrawMainItems(playerid) = CreatePlayerTextDraw(playerid,549.000000, 108.000000, ~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~)
	PlayerTextDrawBackgroundColor(playerid,TextDrawMainItems(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawMainItems(playerid), 1)
	PlayerTextDrawLetterSize(playerid,TextDrawMainItems(playerid), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawMainItems(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawMainItems(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawMainItems(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawMainItems(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawMainItems(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawMainItems(playerid), -1768515946)
	PlayerTextDrawTextSize(playerid,TextDrawMainItems(playerid), 78.000000, 0.000000)

	TextDrawItemTitle(playerid) = CreatePlayerTextDraw(playerid,90.000000, 107.000000, posiadany ekwipunek)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItemTitle(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawItemTitle(playerid), 3)
	PlayerTextDrawLetterSize(playerid,TextDrawItemTitle(playerid), 0.490000, 2.000000)
	PlayerTextDrawColor(playerid,TextDrawItemTitle(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItemTitle(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItemTitle(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItemTitle(playerid), 0)

	TextDrawItem(playerid)(0) = CreatePlayerTextDraw(playerid,90.000000, 128.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(0), 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(0), 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(0), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(0), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(0), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(0), 0)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(0), 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(0), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(0), 65535)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(0), 74.000000, 61.000000)
	PlayerTextDrawSetPreviewModel(playerid, TextDrawItem(playerid)(0), 1216)
	PlayerTextDrawSetPreviewRot(playerid, TextDrawItem(playerid)(0), -16.000000, 0.000000, -55.000000, 1.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(0), 1)

	TextDrawItem(playerid)(1) = CreatePlayerTextDraw(playerid,179.000000, 128.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(1), 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(1), 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(1), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(1), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(1), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(1), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(1), 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(1), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(1), 255)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(1), 74.000000, 61.000000)
	PlayerTextDrawSetPreviewModel(playerid, TextDrawItem(playerid)(1), 19450)
	PlayerTextDrawSetPreviewRot(playerid, TextDrawItem(playerid)(1), -16.000000, 0.000000, -55.000000, 1.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(1), 1)

	TextDrawItem(playerid)(2) = CreatePlayerTextDraw(playerid,271.000000, 128.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(2), 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(2), 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(2), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(2), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(2), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(2), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(2), 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(2), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(2), 255)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(2), 76.000000, 60.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(2), 1)

	TextDrawItem(playerid)(3)  = CreatePlayerTextDraw(playerid,365.000000, 128.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(3) , 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(3) , 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(3) , 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(3) , -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(3) , 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(3) , 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(3) , 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(3) , 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(3) , 255)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(3) , 74.000000, 60.000000)
	PlayerTextDrawSetPreviewModel(playerid, TextDrawItem(playerid)(3) , 450)
	PlayerTextDrawSetPreviewRot(playerid, TextDrawItem(playerid)(3) , -16.000000, 0.000000, -55.000000, 1.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(3) , 1)

	TextDrawItem(playerid)(4) = CreatePlayerTextDraw(playerid,457.000000, 128.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(4), 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(4), 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(4), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(4), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(4), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(4), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(4), 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(4), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(4), 255)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(4), 75.000000, 61.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(4), 1)


	TextDrawItem(playerid)(5) = CreatePlayerTextDraw(playerid,90.000000, 204.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(5), 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(5), 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(5), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(5), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(5), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(5), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(5), 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(5), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(5), 255)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(5), 74.000000, 58.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(5), 1)

	TextDrawItem(playerid)(6) = CreatePlayerTextDraw(playerid,179.000000, 204.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(6), 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(6), 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(6), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(6), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(6), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(6), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(6), 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(6), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(6), 255)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(6), 75.000000, 58.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(6), 1)

	TextDrawItem(playerid)(7) = CreatePlayerTextDraw(playerid,271.000000, 204.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(7), 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(7), 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(7), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(7), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(7), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(7), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(7), 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(7), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(7), 255)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(7), 76.000000, 58.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(7), 1)

	TextDrawItem(playerid)(8) = CreatePlayerTextDraw(playerid,365.000000, 204.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(8), 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(8), 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(8), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(8), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(8), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(8), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(8), 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(8), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(8), 255)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(8), 75.000000, 59.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(8), 1)

	TextDrawItem(playerid)(9) = CreatePlayerTextDraw(playerid,458.000000, 204.000000, New Textdraw)
	PlayerTextDrawBackgroundColor(playerid,TextDrawItem(playerid)(9), 255)
	PlayerTextDrawFont(playerid,TextDrawItem(playerid)(9), 5)
	PlayerTextDrawLetterSize(playerid,TextDrawItem(playerid)(9), 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawItem(playerid)(9), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawItem(playerid)(9), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawItem(playerid)(9), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawItem(playerid)(9), 1)
	PlayerTextDrawUseBox(playerid,TextDrawItem(playerid)(9), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawItem(playerid)(9), 255)
	PlayerTextDrawTextSize(playerid,TextDrawItem(playerid)(9), 75.000000, 59.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItem(playerid)(9), 1)

	TextDrawItemCancel(playerid) = CreatePlayerTextDraw(playerid, 307.000000, 305.000000, Anuluj)
	PlayerTextDrawAlignment(playerid, TextDrawItemCancel(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemCancel(playerid), 255)
	PlayerTextDrawFont(playerid, TextDrawItemCancel(playerid), 3)
	PlayerTextDrawLetterSize(playerid, TextDrawItemCancel(playerid), 0.559998, 1.899999)
	PlayerTextDrawColor(playerid, TextDrawItemCancel(playerid), -1)
	PlayerTextDrawSetOutline(playerid, TextDrawItemCancel(playerid), 0)
	PlayerTextDrawSetProportional(playerid, TextDrawItemCancel(playerid), 1)
	PlayerTextDrawSetShadow(playerid, TextDrawItemCancel(playerid), 0)
	PlayerTextDrawUseBox(playerid, TextDrawItemCancel(playerid), 1)
	PlayerTextDrawBoxColor(playerid, TextDrawItemCancel(playerid), 160)
	PlayerTextDrawTextSize(playerid, TextDrawItemCancel(playerid), 244.000000, 91.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItemCancel(playerid), 1)

	TextDrawItemPrev(playerid) = CreatePlayerTextDraw(playerid, 197.000000, 305.000000, ((()
	PlayerTextDrawAlignment(playerid, TextDrawItemPrev(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemPrev(playerid), 255)
	PlayerTextDrawFont(playerid, TextDrawItemPrev(playerid), 3)
	PlayerTextDrawLetterSize(playerid, TextDrawItemPrev(playerid), 0.559997, 1.899999)
	PlayerTextDrawColor(playerid, TextDrawItemPrev(playerid), -1)
	PlayerTextDrawSetOutline(playerid, TextDrawItemPrev(playerid), 0)
	PlayerTextDrawSetProportional(playerid, TextDrawItemPrev(playerid), 1)
	PlayerTextDrawSetShadow(playerid, TextDrawItemPrev(playerid), 0)
	PlayerTextDrawUseBox(playerid, TextDrawItemPrev(playerid), 1)
	PlayerTextDrawBoxColor(playerid, TextDrawItemPrev(playerid), 160)
	PlayerTextDrawTextSize(playerid, TextDrawItemPrev(playerid), 244.000000, 91.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItemPrev(playerid), 1)

	TextDrawItemNext(playerid) = CreatePlayerTextDraw(playerid, 416.000000, 304.000000, ))))
	PlayerTextDrawAlignment(playerid, TextDrawItemNext(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid, TextDrawItemNext(playerid), 255)
	PlayerTextDrawFont(playerid, TextDrawItemNext(playerid), 3)
	PlayerTextDrawLetterSize(playerid, TextDrawItemNext(playerid), 0.559997, 1.899999)
	PlayerTextDrawColor(playerid, TextDrawItemNext(playerid), -1)
	PlayerTextDrawSetOutline(playerid, TextDrawItemNext(playerid), 0)
	PlayerTextDrawSetProportional(playerid, TextDrawItemNext(playerid), 1)
	PlayerTextDrawSetShadow(playerid, TextDrawItemNext(playerid), 0)
	PlayerTextDrawUseBox(playerid, TextDrawItemNext(playerid), 1)
	PlayerTextDrawBoxColor(playerid, TextDrawItemNext(playerid), 160)
	PlayerTextDrawTextSize(playerid, TextDrawItemNext(playerid), 244.000000, 91.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawItemNext(playerid), 1)
	
	return 1
)

// miejsce

stock bGUI_Testing(playerid)
(
	return 1
)

stock bGUI_Hide(playerid)
(
	PlayerCache(playerid)(pUseGUI) = false
	
	PlayerTextDrawHide(playerid, TextDrawMainItems(playerid))
	PlayerTextDrawHide(playerid, TextDrawItemTitle(playerid))
	PlayerTextDrawHide(playerid, TextDrawItemNext(playerid))
	PlayerTextDrawHide(playerid, TextDrawItemPrev(playerid))
	PlayerTextDrawHide(playerid, TextDrawItemCancel(playerid))
	
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(0))
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(1))
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(2))
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(3))
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(4))
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(5))
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(6))
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(7))
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(8))
	PlayerTextDrawHide(playerid, TextDrawItem(playerid)(9))
	
	CancelSelectTextDraw(playerid)

	return 1
)

stock bGUI_ShowItem(playerid,slot,itemid)
(
	modelid = 328
	if(ItemInfo(itemid)(iType) == TYPE_NONE)
	(
		modelid = 328
	)
	else if(ItemInfo(itemid)(iType) == ITEM_WATCH)
	(
		modelid = 2710
	)
	else if(ItemInfo(itemid)(iType) == ITEM_FOOD)
	(
		modelid = 2769
	)
	else if(ItemInfo(itemid)(iType) == ITEM_CIGGY)
	(
		modelid = 1485
	)
	else if(ItemInfo(itemid)(iType) == ITEM_CUBE)
	(
		modelid = 328
	)
	else if(ItemInfo(itemid)(iType) == ITEM_CLOTH)
	(
		modelid = ItemInfo(itemid)(iValue1)
	)
	else if(ItemInfo(itemid)(iType) == ITEM_WEAPON)
	(
		modelid = GetWeaponModel(ItemInfo(itemid)(iValue1))
	)
	else if(ItemInfo(itemid)(iType) == ITEM_AMMO)
	(
		modelid = 3016
	)
	else if(ItemInfo(itemid)(iType) == ITEM_PHONE)
	(
		modelid = 330
	)
	else if(ItemInfo(itemid)(iType) == ITEM_CANISTER)
	(
		modelid = 1650
	)
	else if(ItemInfo(itemid)(iType) == ITEM_MASK)
	(
		modelid = 18912
	)
	else if(ItemInfo(itemid)(iType) == ITEM_PAINT)
	(
		modelid = 365
	)
	else if(ItemInfo(itemid)(iType) == ITEM_HANDCUFFS)
	(
		modelid = 19418
	)
	else if(ItemInfo(itemid)(iType) == ITEM_MEGAPHONE)
	(
		modelid = 328
	)
	else if(ItemInfo(itemid)(iType) == ITEM_LINE)
	(
		modelid = 19087
	)
	else if(ItemInfo(itemid)(iType) == ITEM_NOTEBOOK)
	(
		modelid = 2894
	)
	else if(ItemInfo(itemid)(iType) == ITEM_CHIT)
	(
		modelid = 2953
	)
	else if(ItemInfo(itemid)(iType) == ITEM_TUNING)
	(
		modelid = ItemInfo(itemid)(iValue1)
	)
	else if(ItemInfo(itemid)(iType) == ITEM_FISHING)
	(
		modelid = 18632
	)
	else if(ItemInfo(itemid)(iType) == ITEM_BAG)
	(
		modelid = 1550
	)
	else if(ItemInfo(itemid)(iType) == ITEM_DRINK)
	(
		modelid = 1484
	)
	else if(ItemInfo(itemid)(iType) == ITEM_DRUG)
	(
		modelid = 1575
	)
	else if(ItemInfo(itemid)(iType) == ITEM_ATTACH)
	(
		buffer(256)
		format(buffer,sizeof(buffer),SELECT access_model FROM hrp_access WHERE access_uid = %i,ItemInfo(itemid)(iValue1))
		mysql_query(buffer)
		mysql_store_result()
		modelid = mysql_fetch_int()
		mysql_free_result()
	)
	else if(ItemInfo(itemid)(iType) == ITEM_ACCESS)
	(
		modelid = 1025
	)
	else if(ItemInfo(itemid)(iType) == ITEM_PLATE)
	(
		modelid = 1961
	)
	else if(ItemInfo(itemid)(iType) == ITEM_ARMOUR)
	(
		modelid = 373
	)
	else if(ItemInfo(itemid)(iType) == ITEM_CORPSE)
	(
		modelid = 19830
	)
	else if(ItemInfo(itemid)(iType) == ITEM_PASS)
	(
		modelid = 2894
	)
	else if(ItemInfo(itemid)(iType) == ITEM_MOLOTOV)
	(
		modelid = 344
	)
	else if(ItemInfo(itemid)(iType) == ITEM_FLASHLIGHT)
	(
		modelid = 18641
	)
	else if(ItemInfo(itemid)(iType) == ITEM_TAGGER)
	(
		modelid = 365
	)
	else if(ItemInfo(itemid)(iType) == ITEM_PAGER)
	(
		modelid = 18875
	)
	else if(ItemInfo(itemid)(iType) == ITEM_ROPE)
	(
		modelid = 19087
	)
	else if(ItemInfo(itemid)(iType) == ITEM_HEADBAG)
	(
		modelid = 2663
	)
	else if(ItemInfo(itemid)(iType) == ITEM_HOMEPHONESET)
	(
		modelid = 19630
	)
	else if(ItemInfo(itemid)(iType) == ITEM_NEWSPAPER)
	(
		modelid = 2894
	)
	else if(ItemInfo(itemid)(iType) == ITEM_PUTABLE)
	(
		modelid = ItemInfo(itemid)(iValue1)
	)
	else if(ItemInfo(itemid)(iType) == ITEM_CARD)
	(
		modelid = 1581
	)
	else if(ItemInfo(itemid)(iType) == ITEM_OXYGEN)
	(
		modelid = 19580
	)
	else if(ItemInfo(itemid)(iType) == ITEM_SURFBOARD)
	(
		modelid = 2410
	)
	else
	(
		modelid = 328
	)

	
	PlayerTextDrawSetPreviewModel(playerid, TextDrawItem(playerid)(slot), modelid)
	PlayerTextDrawShow(playerid,TextDrawItem(playerid)(slot))

	return 1
)

stock bGUI_ListPlayerItems(playerid,pageid)
(
	//pierw schowaj
	bGUI_Hide(playerid)
	PlayerCache(playerid)(pUseGUI) = true
	
	//msg(128)
	//format(msg,sizeof(msg),pageid: %i,pageid)
	//SendClientMessage(playerid,0xFFFFFFAA,msg)
	
	
	// poka¿ textdrawa
	PlayerTextDrawShow(playerid, TextDrawMainItems(playerid))
	PlayerTextDrawShow(playerid, TextDrawItemTitle(playerid))
	PlayerTextDrawShow(playerid, TextDrawItemNext(playerid))
	PlayerTextDrawShow(playerid, TextDrawItemPrev(playerid))
	PlayerTextDrawShow(playerid, TextDrawItemCancel(playerid))
	
	pageid = pageid*10	//do itemek
	currentSlot = 0
	
	helped = 0		//taka tam pomocniczna
	foreach(Items, itemid)
	(
		/*if(pageid ) helped)
		(
			//do kolejnych stron, chyba
			helped++
			continue
		)
		if(currentSlot ) 9)
		(
			break
		)*/
		
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
				if(currentSlot ) 9)
				(
					break
				)
				
				bGUI_ShowItem(playerid,currentSlot,itemid)
				currentSlot++
			)
		)
	)
	
	SelectTextDraw(playerid, 0x8C8C8CFF)
	
	return currentSlot
)