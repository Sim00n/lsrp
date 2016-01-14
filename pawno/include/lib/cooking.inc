/*
	Gotowanie narkotyków,
	seler.

*/

CMD:gotuj(playerid, params())
(
	if(!strcmp(params, zakoncz, true))
	(
		if(PlayerCache(playerid)(pCookID) != -1)
		(
			ClearCooking(playerid)
			PlayerCache(playerid)(pCookID) = -1
		)
		return 1
	)
	
	if(PlayerCache(playerid)(pCookID) != -1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie jesteœ w trakcie gotowania., OK, )
		return 1
	)
	
	objectid = GetClosestObject(playerid)
	cookid = GetCookingID(objectid)
	
	if(objectid == INVALID_OBJECT_ID || cookid == -1)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono kuchenki do gotowania w pobli¿u., OK, )
		return 1
	)
	if(CookData(cookid)(cIsOccupied))
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie ktoœ korzysta z tej kuchenki., OK, )
		return 1
	)
	if(CookData(cookid)(cStatus) == COOK_STATUS_COOKING)
	(
		if(gettime() ( CookData(cookid)(cTime))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Obecnie w tej kuchence coœ siê gotuje, spróbuj póŸniej., OK, )
			return 1
		)
		
		if(gettime() ) CookData(cookid)(cTime)+300)	// ma mo¿liwe 5 minut spóŸnienia (300s)
		(
			printf((cooking) Gracz %s (UID: %d) spoznil sie po odebranie wywaru., PlayerRealName(playerid), PlayerCache(playerid)(pUID))
			PlayerCache(playerid)(pCookID) = cookid
			ClearCookingData(playerid)
			PlayerCache(playerid)(pCookID) = -1
			CookData(cookid)(cStatus) = COOK_STATUS_FREE
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Produkt zbyt d³ugo czeka³ na Ciebie.\nSpróbuj ponownie u¿ywaj¹c komendy /gotuj, tylko wyrób siê w wyznaczonym czasie!, OK, )
			return 1
		)
		PlayerCache(playerid)(pCookID) = cookid
		GetCookingProduct(playerid)
		ClearCookingData(playerid)
		PlayerCache(playerid)(pCookID) = -1
		CookData(cookid)(cStatus) = COOK_STATUS_FREE
		return 1
	)
	
	list_drugs(256)
	
	strcat(list_drugs, Crack\n)
	strcat(list_drugs, Ecstasy\n)
	strcat(list_drugs, LSD\n)
	strcat(list_drugs, Metamfetamina\n)
	strcat(list_drugs, Amfetamina\n)
	strcat(list_drugs, Szarlotka)
	
	CookData(cookid)(cIsOccupied) = true
	PlayerCache(playerid)(pCookID) = cookid
	
 	ShowPlayerDialog(playerid, D_COOK_SELECT, DIALOG_STYLE_LIST, Wybierz produkt do gotowania, list_drugs, Gotuj, Anuluj)
	initializeCookTextDraws(playerid)
	
	return 1
)

stock GetCookingProduct(playerid)
(
	cookid = PlayerCache(playerid)(pCookID), ingredient_list(MAX_INGREDIENTS), points = 0
	
	sscanf(RecipesData(CookData(cookid)(cDrug))(rRecipe), a(d)(18), ingredient_list)
	for(i = 0 i ( sizeof(ingredient_list) i++)
	(
		if(ingredient_list(i) != 0)
		(
			for(j = 0 j ( MAX_INGREDIENTS j++)
			(
				if(CookData(cookid)(cIngredient)(j) == IngredientsData(ingredient_list(i))(ingValue))
				(
					points +=  IngredientsData(ingredient_list(i))(ingPoints)
					ingredient_list(i) = 0 // tutaj blokada, ¿e je¿eli powtórzy siê ten sam sk³adnik to ju¿ go nie zaliczy
				)
			)
		)
	)
	
	if(points (= floatround(0.50 * RecipesData(CookData(cookid)(cDrug))(rMaxPoints)))	// ma mniej ni¿ po³owa maksymalnych punktów
	(
		GuiMsg(playerid, Ooops!\nTwój produkt niestety nie powsta³ prawid³owo. Doda³eœ zbyt ma³o sk³adników, b¹dŸ posiadasz b³êdn¹ recepturê.\nSpróbuj ponownie u¿ywaj¹c komendy /gotuj, jednak¿e popraw swój przepis., 0)
		return 1
	)
	
	string(128), grams
	if(RecipesData(CookData(cookid)(cDrug))(rMaxGrams) (= 5)
	(
		grams = RecipesData(CookData(cookid)(cDrug))(rMaxGrams)
	)
	else
	(
		Float:percent = points / RecipesData(CookData(cookid)(cDrug))(rMaxPoints)
		grams = floatround(percent * RecipesData(CookData(cookid)(cDrug))(rMaxGrams))	// (Punkty/maxPunkty)*maxGramy
		symbol = random(2), bonus = random(6)
		
		switch (symbol)
		(
			case 0:	// odejmuje mu bonus
				grams = grams - bonus
			case 1:	// dodaje mu bonus
				grams = grams + bonus
		)
	)
	
	if(RecipesData(CookData(cookid)(cDrug))(rItemType) == ITEM_DRUG)
	(
		format(string, sizeof(string), %s %dg., RecipesData(CookData(cookid)(cDrug))(rName), grams)
		CreatePlayerItem(playerid, string, RecipesData(CookData(cookid)(cDrug))(rItemType), RecipesData(CookData(cookid)(cDrug))(rDrugValue), grams)
		
		format(string, sizeof(string), Sukces!\nUda³o Ci siê ugotowaæ swój produkt. Uzyska³eœ go %d gram., grams)
	)
	else
	(
		format(string, sizeof(string), %s, RecipesData(CookData(cookid)(cDrug))(rName))
		CreatePlayerItem(playerid, string, RecipesData(CookData(cookid)(cDrug))(rItemType), RecipesData(CookData(cookid)(cDrug))(rDrugValue), grams)
		
		format(string, sizeof(string), Sukces!\nUda³o Ci siê ugotowaæ swój produkt.)
	)
	
	GuiMsg(playerid, string, 0)
	
	printf((cooking) Gracz %s (UID: %d) wyprodukowal %s w ilosci %d gram., PlayerRealName(playerid), PlayerCache(playerid)(pUID), RecipesData(CookData(cookid)(cDrug))(rName), grams)
	
	return 1
)

stock ClearCooking(playerid)
(
	CloseCookingBox(playerid)
	ClearCookingData(playerid)
	
	return 1
)

stock ClearCookingData(playerid)
(
	cookid = PlayerCache(playerid)(pCookID)
	
	CookData(cookid)(cIngredients) = 0
	CookData(cookid)(cTime) = 0
	CookData(cookid)(cDrug) = 0
	
	for(i = 0 i ( MAX_INGREDIENTS i++)
	(
		CookData(cookid)(cIngredient)(i) = 0
	)
	
	return 1
)

stock CloseCookingBox(playerid)
(
	cookid = PlayerCache(playerid)(pCookID)
	CookData(cookid)(cIsOccupied) = false
	
	PlayerTextDrawDestroy(playerid, CookBG(playerid))
	PlayerTextDrawDestroy(playerid, ActionCook(playerid))
	PlayerTextDrawDestroy(playerid, ActionAdd(playerid))
	PlayerTextDrawDestroy(playerid, ActionClose(playerid))
	PlayerTextDrawDestroy(playerid, CookInfo(playerid))
	PlayerTextDrawDestroy(playerid, CookThing(playerid))
	PlayerTextDrawDestroy(playerid, CookIngredients(playerid))
	for(i = 0 i ( MAX_INGREDIENTS i++)
	(
		PlayerTextDrawDestroy(playerid, CookIngredient(i)(playerid))	
	)

	CancelSelectTextDraw(playerid)
	
	hrp_TogglePlayerControllable(playerid, true)
	
	return 1
)

stock LoadCooking(objectid)
(
	gameid = GetFreeCookingID()
	
	if(gameid ( 0)
	(
		return 1
	)
	
	CookData(gameid)(cObjectID) = objectid
	CookData(gameid)(cIsOccupied) = false
	CookData(gameid)(cStatus) = COOK_STATUS_FREE

	return 1
)

stock GetFreeCookingID()
(
	freeid = -1
	for(i = 0  i ( MAX_COOK i++)
	(
		if(CookData(i)(cStatus) == COOK_STATUS_ZERO)
		(
			freeid = i
			break
		)
		else
		(
			continue
		)
	)
	
	return freeid
)

stock GetCookingID(objectid)
(
	gameid = -1
	for(i = 0  i ( MAX_COOK i++)
	(
		if(CookData(i)(cObjectID) == objectid)
		(
			gameid = i
			break
		)
		else
		(
			continue
		)
	)
	
	return gameid
)

stock initializeCookTextDraws(playerid)
(
	CookBG(playerid) = CreatePlayerTextDraw(playerid,280.000000, 105.000000, _)
	PlayerTextDrawAlignment(playerid,CookBG(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,CookBG(playerid), 65535)
	PlayerTextDrawFont(playerid,CookBG(playerid), 0)
	PlayerTextDrawLetterSize(playerid,CookBG(playerid), 0.000000, 30.000019)
	PlayerTextDrawColor(playerid,CookBG(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookBG(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookBG(playerid), 1)
	PlayerTextDrawUseBox(playerid,CookBG(playerid), 1)
	PlayerTextDrawBoxColor(playerid,CookBG(playerid), 150)
	PlayerTextDrawTextSize(playerid,CookBG(playerid), 0.000000, 427.000000)
	PlayerTextDrawSetSelectable(playerid,CookBG(playerid), 0)

	ActionCook(playerid) = CreatePlayerTextDraw(playerid,492.000000, 110.000000, GOTUJ)
	PlayerTextDrawAlignment(playerid,ActionCook(playerid), 3)
	PlayerTextDrawBackgroundColor(playerid,ActionCook(playerid), 255)
	PlayerTextDrawFont(playerid,ActionCook(playerid), 2)
	PlayerTextDrawLetterSize(playerid,ActionCook(playerid), 0.600000, 2.500000)
	PlayerTextDrawColor(playerid,ActionCook(playerid), 0xFFD6D6D6)
	PlayerTextDrawSetOutline(playerid,ActionCook(playerid), 1)
	PlayerTextDrawSetProportional(playerid,ActionCook(playerid), 1)
	PlayerTextDrawTextSize(playerid,ActionCook(playerid), 576.000000, 20.000000)
	PlayerTextDrawUseBox(playerid,ActionCook(playerid), 1)
	PlayerTextDrawBoxColor(playerid,ActionCook(playerid), 0x00000000)
	PlayerTextDrawSetSelectable(playerid,ActionCook(playerid), 1)

	ActionAdd(playerid) = CreatePlayerTextDraw(playerid,492.000000, 140.000000, DODAJ)
	PlayerTextDrawAlignment(playerid,ActionAdd(playerid), 3)
	PlayerTextDrawBackgroundColor(playerid,ActionAdd(playerid), 255)
	PlayerTextDrawFont(playerid,ActionAdd(playerid), 2)
	PlayerTextDrawLetterSize(playerid,ActionAdd(playerid), 0.600000, 2.500000)
	PlayerTextDrawColor(playerid,ActionAdd(playerid), 0xFFD6D6D6)
	PlayerTextDrawSetOutline(playerid,ActionAdd(playerid), 1)
	PlayerTextDrawSetProportional(playerid,ActionAdd(playerid), 1)
	PlayerTextDrawTextSize(playerid,ActionAdd(playerid), 578.000000, 20.000000)
	PlayerTextDrawUseBox(playerid,ActionAdd(playerid), 1)
	PlayerTextDrawBoxColor(playerid,ActionAdd(playerid), 0x00000000)
	PlayerTextDrawSetSelectable(playerid,ActionAdd(playerid), 1)
	
	ActionClose(playerid) = CreatePlayerTextDraw(playerid,492.000000, 350.000000, ANULUJ)
	PlayerTextDrawAlignment(playerid,ActionClose(playerid), 3)
	PlayerTextDrawBackgroundColor(playerid,ActionClose(playerid), 255)
	PlayerTextDrawFont(playerid,ActionClose(playerid), 2)
	PlayerTextDrawLetterSize(playerid,ActionClose(playerid), 0.600000, 2.500000)
	PlayerTextDrawColor(playerid,ActionClose(playerid), 0xFFD6D6D6)
	PlayerTextDrawSetOutline(playerid,ActionClose(playerid), 1)
	PlayerTextDrawSetProportional(playerid,ActionClose(playerid), 1)
	PlayerTextDrawTextSize(playerid,ActionClose(playerid), 585.000000, 20.000000)
	PlayerTextDrawUseBox(playerid,ActionClose(playerid), 1)
	PlayerTextDrawBoxColor(playerid,ActionClose(playerid), 0x00000000)
	PlayerTextDrawSetSelectable(playerid,ActionClose(playerid), 1)

	CookInfo(playerid) = CreatePlayerTextDraw(playerid,80.000000, 110.000000, GOTUJESZ:)
	PlayerTextDrawAlignment(playerid,CookInfo(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookInfo(playerid), 255)
	PlayerTextDrawFont(playerid,CookInfo(playerid), 2)
	PlayerTextDrawLetterSize(playerid,CookInfo(playerid), 0.600000, 2.500000)
	PlayerTextDrawColor(playerid,CookInfo(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookInfo(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookInfo(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookInfo(playerid), 0)
	
	CookThing(playerid) = CreatePlayerTextDraw(playerid,80.000000, 125.000000, _)
	PlayerTextDrawAlignment(playerid,CookThing(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookThing(playerid), 255)
	PlayerTextDrawFont(playerid,CookThing(playerid), 2)
	PlayerTextDrawLetterSize(playerid,CookThing(playerid), 0.600000, 2.500000)
	PlayerTextDrawColor(playerid,CookThing(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookThing(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookThing(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookThing(playerid), 0)

	CookIngredients(playerid) = CreatePlayerTextDraw(playerid,80.000000, 167.000000, SKLADNIKI:)
	PlayerTextDrawAlignment(playerid,CookIngredients(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredients(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredients(playerid), 2)
	PlayerTextDrawLetterSize(playerid,CookIngredients(playerid), 0.419999, 2.599999)
	PlayerTextDrawColor(playerid,CookIngredients(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredients(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredients(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredients(playerid), 0)

	CookIngredient(0)(playerid) = CreatePlayerTextDraw(playerid,80.000000, 192.000000, _)	// 1 sk³adnik
	PlayerTextDrawAlignment(playerid,CookIngredient(0)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(0)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(0)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(0)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(0)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(0)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(0)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(0)(playerid), 0)

	CookIngredient(1)(playerid) = CreatePlayerTextDraw(playerid,80.000000, 211.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(1)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(1)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(1)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(1)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(1)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(1)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(1)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(1)(playerid), 0)
	
	CookIngredient(2)(playerid) = CreatePlayerTextDraw(playerid,80.000000, 230.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(2)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(2)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(2)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(2)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(2)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(2)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(2)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(2)(playerid), 0)

	CookIngredient(3)(playerid) = CreatePlayerTextDraw(playerid,80.000000, 249.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(3)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(3)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(3)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(3)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(3)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(3)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(3)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(3)(playerid), 0)
	
	CookIngredient(4)(playerid) = CreatePlayerTextDraw(playerid,80.000000, 268.000000, _) // 5 sk³adnik
	PlayerTextDrawAlignment(playerid,CookIngredient(4)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(4)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(4)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(4)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(4)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(4)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(4)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(4)(playerid), 0)

	CookIngredient(5)(playerid) = CreatePlayerTextDraw(playerid,80.000000, 287.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(5)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(5)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(5)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(5)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(5)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(5)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(5)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(5)(playerid), 0)
	
	CookIngredient(6)(playerid) = CreatePlayerTextDraw(playerid,80.000000, 306.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(6)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(6)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(6)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(6)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(6)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(6)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(6)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(6)(playerid), 0)
	
	CookIngredient(7)(playerid) = CreatePlayerTextDraw(playerid,80.000000, 325.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(7)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(7)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(7)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(7)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(7)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(7)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(7)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(7)(playerid), 0)
	
	CookIngredient(8)(playerid) = CreatePlayerTextDraw(playerid,80.000000, 344.000000, _)	// 9 sk³adnik
	PlayerTextDrawAlignment(playerid,CookIngredient(8)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(8)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(8)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(8)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(8)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(8)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(8)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(8)(playerid), 0)
	
	CookIngredient(9)(playerid) = CreatePlayerTextDraw(playerid,240.000000, 192.000000, _)	// 10 sk³adnik
	PlayerTextDrawAlignment(playerid,CookIngredient(9)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(9)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(9)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(9)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(9)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(9)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(9)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(9)(playerid), 0)
	
	CookIngredient(10)(playerid) = CreatePlayerTextDraw(playerid,240.000000, 211.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(10)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(10)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(10)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(10)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(10)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(10)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(10)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(10)(playerid), 0)
	
	CookIngredient(11)(playerid) = CreatePlayerTextDraw(playerid,240.000000, 230.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(11)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(11)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(11)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(11)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(11)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(11)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(11)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(11)(playerid), 0)
	
	CookIngredient(12)(playerid) = CreatePlayerTextDraw(playerid,240.000000, 249.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(12)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(12)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(12)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(12)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(12)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(12)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(12)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(12)(playerid), 0)
	
	CookIngredient(13)(playerid) = CreatePlayerTextDraw(playerid,240.000000, 268.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(13)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(13)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(13)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(13)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(13)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(13)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(13)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(13)(playerid), 0)
	
	CookIngredient(14)(playerid) = CreatePlayerTextDraw(playerid,240.000000, 287.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(14)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(14)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(14)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(14)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(14)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(14)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(14)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(14)(playerid), 0)
	
	CookIngredient(15)(playerid) = CreatePlayerTextDraw(playerid,240.000000, 306.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(15)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(15)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(15)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(15)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(15)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(15)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(15)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(15)(playerid), 0)
	
	CookIngredient(16)(playerid) = CreatePlayerTextDraw(playerid,240.000000, 325.000000, _)
	PlayerTextDrawAlignment(playerid,CookIngredient(16)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(16)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(16)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(16)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(16)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(16)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(16)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(16)(playerid), 0)
	
	CookIngredient(17)(playerid) = CreatePlayerTextDraw(playerid,240.000000, 344.000000, _)	// 18 sk³adnik
	PlayerTextDrawAlignment(playerid,CookIngredient(17)(playerid), 1)
	PlayerTextDrawBackgroundColor(playerid,CookIngredient(17)(playerid), 255)
	PlayerTextDrawFont(playerid,CookIngredient(17)(playerid), 1)
	PlayerTextDrawLetterSize(playerid,CookIngredient(17)(playerid), 0.350000, 2.500000)
	PlayerTextDrawColor(playerid,CookIngredient(17)(playerid), -1)
	PlayerTextDrawSetOutline(playerid,CookIngredient(17)(playerid), 1)
	PlayerTextDrawSetProportional(playerid,CookIngredient(17)(playerid), 1)
	PlayerTextDrawSetSelectable(playerid,CookIngredient(17)(playerid), 0)	
	
	return 1
)