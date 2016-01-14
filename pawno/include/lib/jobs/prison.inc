stock SetPlayerLaundryAnimations(playerid)
(
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY)
	SetPlayerAttachedObject(playerid, SLOT_TRYING, 1576, 6, 0.10, -0.030999, -0.155, -112.5, -5.89993, 88.1001, 1.0, 1.0, 1.0, 0xFFFF8C2C)
	return 1
)

stock SetPlayerWorkshopAnimations(playerid)
(
	hrp_TogglePlayerControllable(playerid, false)
	ApplyAnimation(playerid, SWORD, sword_IDLE, 4.1, 0, 0, 0, 1, 0, 1)
	return 1
)

stock StopPlayerAnimations(playerid)
(
	hrp_TogglePlayerControllable(playerid, true)
	ClearAnimations(playerid)
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE)
	RemovePlayerAttachedObject(playerid, SLOT_TRYING)
	return 1
)

stock StopPlayerPrisonWork(playerid)
(
	StopPlayerAnimations(playerid)
	
	PlayerCache(playerid)(pWorkingNow) = 0
	PlayerCache(playerid)(pWorkingPhase) = 0
)

CMD:praca(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		GuiMsg(playerid, Nie mo¿esz tego zrobiæ bêd¹c nieprzytomnym., 1)
		return 1
	)
	if(!PlayerCache(playerid)(pArrest))
	(
		GuiMsg(playerid, Tej komendy mo¿esz u¿yæ do pracy tylko bêd¹c w areszcie., 1)
		return 1
	)
	
	if(PlayerCache(playerid)(pWorkingNow))
	(
		GuiMsg(playerid, Pracowa³eœ, obecnie przerwa³eœ pracê w wiêzieniu., 0)
		StopPlayerPrisonWork(playerid)
		return 1
	)
	
	if(PlayerCache(playerid)(pWorkRepeat) )= 10)
	(
		GuiMsg(playerid, Wyczerpa³eœ dzienny limit pracy, odpocznij., 0)
		return 1
	)
	
	type(32)
	if(sscanf(params, s(32), type))
	(
		hrp_Tip(playerid, /praca (pralnia | warsztat))
		return 1
	)
	
	// sprawdzanie limitu prac dziennych
	
	if(!strcmp(type, pralnia, true))
	(
		if(PlayerCache(playerid)(pWorkingNow))
		(
			GuiMsg(playerid, Obecnie pracujesz.\nAby przerwaæ pracê u¿yj komendy /praca., 1)
			return 1
		)
		if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1782.0901, -1548.1317, 40.8159))
		(
			GuiMsg(playerid, Aby rozpocz¹æ pracê w pralni musisz siê tam znajdowaæ., 1)
			return 1
		)
		PlayerCache(playerid)(pWorkingNow) = WORK_LAUNDRY
		PlayerCache(playerid)(pWorkingPhase) = LAUNDRY_UNLOADED
		GuiMsg(playerid, Rozpocz¹³eœ pracê jako pomocnik w pralni!\nTeraz musisz udaæ siê do poszczególnych cel aby zebraæ brudn¹ odzie¿ wiêŸniów oraz przeœcierad³a z powrotem do pralni.\nBêd¹c w celi aby podnieœæ rzeczy u¿yj klawisza H (klakson)., 0)
	)
	else if(!strcmp(type, warsztat, true))
	(
		if(PlayerCache(playerid)(pWorkingNow))
		(
			GuiMsg(playerid, Obecnie pracujesz.\nAby przerwaæ pracê u¿yj komendy /praca., 1)
			return 1
		)
		if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1764.4370, -1534.9044, 39.9441))
		(
			GuiMsg(playerid, Aby rozpocz¹æ pracê w warsztacie musisz znajdowaæ siê przy stanowisku., 1)
			return 1
		)
		PlayerCache(playerid)(pWorkingNow) = WORK_WORKSHOP
		PlayerCache(playerid)(pWorkingPhase) = WORKSHOP_WAITING
		PlayerCache(playerid)(pWorkingRepeat) = 0
		GuiMsg(playerid, Rozpocz¹³eœ pracê jako cieœla w warsztacie!\nAby rozpocz¹æ pracê u¿yj klawisza H (klakson). Je¿eli chcesz przerwaæ pracê ponownie u¿yj klawisza H.\nPo rozpoczêciu pracy musisz w okreœlonym czasie wcisn¹æ wystarczaj¹c¹ du¿¹ iloœæ LPM (lewy przycisk myszki), stra¿nikowi zale¿y na czasie., 0)
	)
	else
	(
		hrp_Tip(playerid, /praca (pralnia | warsztat))
	)
	
	return 1
)