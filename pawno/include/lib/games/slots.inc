stock LoadSlotsAutomats()
(
	buffer(256)
	format(buffer,sizeof(buffer),SELECT * FROM hrp_slots)
	mysql_query(buffer)
	mysql_store_result()
	
	gameid = 0
	while(mysql_fetch_row(buffer,|))
	(
		if(gameid ) MAX_SLOTS)
		(
			break
		)
		
		sscanf(buffer,p(|)ifffiii,
		SlotMachine(gameid)(mUID),
		SlotMachine(gameid)(mPosX) ,
		SlotMachine(gameid)(mPosY) ,
		SlotMachine(gameid)(mPosZ) ,
		SlotMachine(gameid)(mVW),
		SlotMachine(gameid)(mMoney) ,
		SlotMachine(gameid)(mOwner) 		)	
		
		SlotMachine(gameid)(mBusy) = false
		
		gameid++
	)
	
	printf((load) zaladowano %i maszyn typu slots,gameid)
	
	mysql_free_result()
	return 1
)

stock UnloadSlotsAutomat(slotid)
(
	buffer(256)
	format(buffer,sizeof(buffer),UPDATE hrp_slots SET money=%i WHERE uid=%i,SlotMachine(slotid)(mMoney),SlotMachine(slotid)(mUID))
	mysql_query(buffer)
	
	SlotMachine(slotid)(mUID) = 0
	SlotMachine(slotid)(mPosX) = 0.0  
	SlotMachine(slotid)(mPosY) = 0.0  
	SlotMachine(slotid)(mPosZ) = 0.0  
	SlotMachine(slotid)(mVW) = 0
	SlotMachine(slotid)(mMoney) = 0
	SlotMachine(slotid)(mOwner) = 0
	SlotMachine(slotid)(mBusy) = false
	
	return 1
)

stock UnloadSlotsAutomats()
(
	for(i = 0  i ( MAX_SLOTS i++)
	(	
		if(SlotMachine(i)(mUID) ) 0)
		(
			UnloadSlotsAutomat(i)
		)
	)
	
	return 1
)

stock ReloadSlotsAutomats()
(
	for(i = 0  i ( MAX_SLOTS i++)
	(
		UnloadSlotsAutomat(i)
	)
	
	LoadSlotsAutomats()
	print((slots) reload wszystkich automatow do jednorekiego bandyty...)
	
	return 1
)

stock slots_GetFreeID()
(
	freeid = -1
	for(i = 0  i ( MAX_SLOTS i++)
	(
		if(SlotMachine(i)(mUID) != 0)
		(
			continue
		)
		else
		(
			freeid = i
			break
		)
	)
	
	return freeid
)

stock slots_RandIcons(playerid)
(
	icon = random(6)
	PlayerTextDrawSetString(playerid,TextDrawSlotsFirst(playerid), SlotInfo(icon)(slName))
	PlayerTextDrawShow(playerid,TextDrawSlotsFirst(playerid))
	
	icon = random(6)
	PlayerTextDrawSetString(playerid,TextDrawSlotsSecond(playerid), SlotInfo(icon)(slName))
	PlayerTextDrawShow(playerid,TextDrawSlotsSecond(playerid))
	
	icon = random(6)
	PlayerTextDrawSetString(playerid,TextDrawSlotsThird(playerid), SlotInfo(icon)(slName))
	PlayerTextDrawShow(playerid,TextDrawSlotsThird(playerid))
	return 1
)

/*forward slots_RollMachine(playerid)
public slots_RollMachine(playerid)
(
	slotid = PlayerCache(playerid)(pSlotID) 
	if(PlayerCache(playerid)(pSlotTicks) ) 20)
	(
		slots_RandIcons(playerid)
		PlayerCache(playerid)(pSlotTicks)  =PlayerCache(playerid)(pSlotTicks) - 1
		SetTimerEx(slots_RollMachine, 100, 0, d, playerid)
	)
	else if(PlayerCache(playerid)(pSlotTicks)  ( 20 && PlayerCache(playerid)(pSlotTicks)  ) 1)
	(
		slots_RandIcons(playerid)
		PlayerCache(playerid)(pSlotTicks)  =PlayerCache(playerid)(pSlotTicks) - 1
		SetTimerEx(slots_RollMachine, 400, 0, d, playerid)
	)
	else if(PlayerCache(playerid)(pSlotTicks)(= 1)
	(
		PlayerCache(playerid)(pSlotTicks) = 0
		//last loss
		one = random(6)
		PlayerTextDrawSetString(playerid,TextDrawSlotsFirst(playerid), SlotInfo(one)(slName))
		PlayerTextDrawShow(playerid,TextDrawSlotsFirst(playerid))
		
		two = random(6)
		PlayerTextDrawSetString(playerid,TextDrawSlotsSecond(playerid), SlotInfo(two)(slName))
		PlayerTextDrawShow(playerid,TextDrawSlotsSecond(playerid))
		
		three = random(6)
		PlayerTextDrawSetString(playerid,TextDrawSlotsThird(playerid), SlotInfo(three)(slName))
		PlayerTextDrawShow(playerid,TextDrawSlotsThird(playerid))
		
		if(one == two && two == three)
		(
			//wygral
			//wyplac caly hajs z maszyny
			hrp_GivePlayerMoney(playerid, SlotMachine(slotid)(mMoney))
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
			
			SlotMachine(slotid)(mMoney) = 0
			
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~r~zgarniasz jackpota, 5000, 3)
		)
		else
		(
			GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~r~sprobuj jeszcze raz, 5000, 3)
		)
	)
	
	SendClientMessageToAll(COLOR_WHITE,PlayerCache(playerid)(pSlotTicks))
	print(PlayerCache(playerid)(pSlotTicks))
	
	return 1
)*/

stock slots_GetNerbyID(playerid)
(
	gameid = -1
	for(i = 0  i ( MAX_SLOTS i++)
	(
		if(GetPlayerVirtualWorld(playerid) == SlotMachine(i)(mVW))
		(
			if(IsPlayerInRangeOfPoint(playerid,1.5,SlotMachine(i)(mPosX),SlotMachine(i)(mPosY),SlotMachine(i)(mPosZ)))
			(
				gameid = i
				break
			)
		)
	)
	
	return gameid
)

stock slots_StartGame(playerid,gameid)
(
	SlotMachine(gameid)(mBusy) = true
	
	PlayerTextDrawSetString(playerid,TextDrawCardWelcome(playerid), ~g~Jednoreki bandyta)
	PlayerTextDrawShow(playerid,TextDrawCardWelcome(playerid))
	
	// Coś się zbugował ten textdraw, to trudno, komentuję
	//PlayerTextDrawSetString(playerid,TextDrawCardTable(playerid),~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~)
	//PlayerTextDrawShow(playerid,TextDrawCardTable(playerid))
	
	icon = random(6)
	PlayerTextDrawSetString(playerid,TextDrawSlotsFirst(playerid), SlotInfo(icon)(slName))
	PlayerTextDrawShow(playerid,TextDrawSlotsFirst(playerid))
	
	icon = random(6)
	PlayerTextDrawSetString(playerid,TextDrawSlotsSecond(playerid), SlotInfo(icon)(slName))
	PlayerTextDrawShow(playerid,TextDrawSlotsSecond(playerid))
	
	icon = random(6)
	PlayerTextDrawSetString(playerid,TextDrawSlotsThird(playerid), SlotInfo(icon)(slName))
	PlayerTextDrawShow(playerid,TextDrawSlotsThird(playerid))
	
	PlayerCache(playerid)(pSlots) = true
	PlayerCache(playerid)(pSlotTicks) = 0
	
	hrp_TogglePlayerControllable(playerid, false)
	
	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~n~~y~uzyj klawisza ~g~~k~~PED_SPRINT~ ~y~aby zakrecic maszyna~n~lub ~r~~k~~SNEAK_ABOUT~ ~y~aby zakonczyc, 5000, 3)
	
	return 1
)

stock slots_EndGame(playerid,gameid)
(
	PlayerTextDrawHide(playerid,TextDrawCardWelcome(playerid))
	PlayerTextDrawHide(playerid,TextDrawCardTable(playerid))
	PlayerTextDrawHide(playerid,TextDrawSlotsFirst(playerid))
	PlayerTextDrawHide(playerid,TextDrawSlotsSecond(playerid))
	PlayerTextDrawHide(playerid,TextDrawSlotsThird(playerid))
	
	SlotMachine(gameid)(mBusy) = false
	PlayerCache(playerid)(pSlots) = false
	
	hrp_TogglePlayerControllable(playerid, true)
	return 1
)

stock slots_GetCashCount()
(
	cash = 0
	for(i = 0  i ( MAX_SLOTS i++)
	(
		if(SlotMachine(i)(mUID) != 0)
		(
			cash += SlotMachine(i)(mMoney)
		)
	)
	return cash
)

stock slots_TakeCash( amount )
(
	for(i = 0 i ( MAX_SLOTS i++)
	(
		if(amount (= 0)
			break
		
		if(SlotMachine(i)(mUID) != 0)
		(
			if(amount ) 0 && SlotMachine(i)(mMoney) ) 0)
			(
				amount -= SlotMachine(i)(mMoney)
				SlotMachine(i)(mMoney) = 0
			)
		)
	)
	
	return 1
)


