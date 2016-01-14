public OnPlayerGymTrainStarted(playerid)
(
	string(256)
	if(PlayerCache(playerid)(pGymType) == TRAIN_BENCH_PRESS)
	(
		SetPlayerAttachedObject(playerid, SLOT_TRAIN_ITEM, 2913, 6, 0.0, 0.0, -0.2)
		
		PlayerCache(playerid)(pGymPhase) = 1

		format(string, sizeof(string), Wcisnij ~up~ aby ~r~uniesc ~y~sztange~n~~n~~w~Ciezar: ~y~~h~%d kg~n~~w~Powtorzenia: ~b~~h~%d~n~~n~~w~., PlayerCache(playerid)(pGymValue1), PlayerCache(playerid)(pGymValue2))
		TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
		
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
		return 1
	)
	if(PlayerCache(playerid)(pGymType) == TRAIN_BARBELL)
	(
	 	SetPlayerAttachedObject(playerid, SLOT_TRAIN_ITEM, 2915, 6, 0.0, 0.0, -0.45, 0.0, 90.0, 0.0)
		PlayerCache(playerid)(pGymPhase) = 1
		
   		format(string, sizeof(string), ~b~Klawisz sprintu~w~, aby wyciskac~n~~n~Ciezar: ~y~~h~%d kg~n~~w~Powtorzenia: ~b~~h~%d~n~~n~~w~., PlayerCache(playerid)(pGymValue1), PlayerCache(playerid)(pGymValue2))
		TextDrawSetString(Text:TextDrawMainInfo(playerid), string)

		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
		return 1
	)
	if(PlayerCache(playerid)(pGymType) == TRAIN_PUNCH_BAG)
	(
		format(string, sizeof(string), Uderzaj w ~r~worek ~b~(~y~PPM ~w~+ ~y~ENTER~b~)~w~.~n~~n~Trafienia: ~g~~h~%d/%d~n~~n~~w~Po osiagnieciu ~g~celu~w~, Twoja postac nauczy sie nowego ~y~stylu ~w~walki., PlayerCache(playerid)(pGymValue1), PlayerCache(playerid)(pGymValue2))
		TextDrawSetString(Text:TextDrawMainInfo(playerid), string)

		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
		return 1
	)
	return 1
)

public OnPlayerGymTrainStopped(playerid)
(
	if(PlayerCache(playerid)(pGymType) != TRAIN_NONE)
	(
		if(PlayerCache(playerid)(pGymType) == TRAIN_PUNCH_BAG)
		(
			if(PlayerCache(playerid)(pGymValue1) )= PlayerCache(playerid)(pGymValue2))
			(
				PlayerCache(playerid)(pFightingStyle) = GetPlayerFightingStyle(playerid)
			)
			else
			(
				SetPlayerFightingStyle(playerid, PlayerCache(playerid)(pFightingStyle))
			)
		)
	)
	SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
 	PlayerCache(playerid)(pGymObject) = INVALID_OBJECT_ID

	PlayerCache(playerid)(pGymValue1) = 0
 	PlayerCache(playerid)(pGymValue2) = 0
	PlayerCache(playerid)(pGymType) = TRAIN_NONE

	RemovePlayerAttachedObject(playerid, SLOT_TRAIN_ITEM)
	ClearAnimations(playerid)
	
	if(GetPlayerVirtualWorld(playerid) == 0)
	(
		// na pewno?
		PlayerCache(playerid)(pTrainTime) = 0
	)

	TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
	return 1
)

public OnPlayerTrainRep(playerid)
(
	Float:factor = 1
	if(PlayerCache(playerid)(pGymNutrient))
	(
		factor += (PlayerCache(playerid)(pGymFactor) / 50)
		if(factor ( 1) factor = 1
		if(factor ) 2) factor = 2
	)

	string(256)
	if(PlayerCache(playerid)(pGymType) == TRAIN_BENCH_PRESS)
	(
		if(PlayerCache(playerid)(pGymPhase) == 3)
		(
  			PlayerCache(playerid)(pGymPhase) = 2

			format(string, sizeof(string), Wcisnij ~down~ aby ~g~opuscic ~y~sztange ~n~~n~~w~Ciezar: ~y~~h~%d kg~n~~w~Powtorzenia: ~b~~h~%d~n~~n~Sila: ~y~%.3f~w~., PlayerCache(playerid)(pGymValue1), PlayerCache(playerid)(pGymValue2), PlayerCache(playerid)(pStrength))
			TextDrawSetString(Text:TextDrawMainInfo(playerid), string)

			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			PlayerCache(playerid)(pGymValue2) ++
			
			// Dodaj pkt si³y
			if(PlayerCache(playerid)(pStrength) ( 100)
			(
				Float:last_strength = PlayerCache(playerid)(pStrength)

				PlayerCache(playerid)(pStrength) += (0.00005 * PlayerCache(playerid)(pGymValue1)) * factor
				if(floatround(PlayerCache(playerid)(pStrength), floatround_floor) ) floatround(last_strength, floatround_floor))
	 			(
					OnPlayerSkillUp(playerid, SKILL_STRENGTH)
				)
			)
		)
		else if(PlayerCache(playerid)(pGymPhase) == 4)
		(
			PlayerCache(playerid)(pGymPhase) = 1

			format(string, sizeof(string), Wcisnij ~up~ aby ~r~uniesc ~y~sztange ~n~~n~~w~Ciezar: ~y~~h~%d kg~n~~w~Powtorzenia: ~b~~h~%d~n~~n~Sila: ~y~%.3f~w~., PlayerCache(playerid)(pGymValue1), PlayerCache(playerid)(pGymValue2), PlayerCache(playerid)(pStrength))
			TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
			
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
		)
		
		PlayerCache(playerid)(pDailyReps) ++
		if(PlayerCache(playerid)(pDailyReps) ) MAX_DAILY_REPS)
		(
			OnPlayerGymTrainStopped(playerid)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postaæ jest zbyt zmêczona ¿eby pakowaæ tak d³ugi czas., OK, )
		)		
		return 1
	)
	if(PlayerCache(playerid)(pGymType) == TRAIN_BARBELL)
	(
		if(PlayerCache(playerid)(pGymPhase) == 2)
		(
			PlayerCache(playerid)(pGymPhase) = 1

			format(string, sizeof(string), ~b~Klawisz sprintu~w~, aby wyciskac~n~~n~Ciezar: ~y~~h~%d kg~n~~w~Powtorzenia: ~b~~h~%d~n~~n~Sila: ~y~%.3f~w~., PlayerCache(playerid)(pGymValue1), PlayerCache(playerid)(pGymValue2), PlayerCache(playerid)(pStrength))
   			TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
   			
   			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			ApplyAnimation(playerid, FREEWEIGHTS, gym_free_down, 4.0, 0, 0, 0, 1, 0, 1)
			
			PlayerCache(playerid)(pGymValue2) ++
			
			// Dodaj pkt si³y
			if(PlayerCache(playerid)(pStrength) ( 100)
			(
				Float:last_strength = PlayerCache(playerid)(pStrength)

				PlayerCache(playerid)(pStrength) += (0.000026 * PlayerCache(playerid)(pGymValue1)) * factor
				if(floatround(PlayerCache(playerid)(pStrength), floatround_floor) ) floatround(last_strength, floatround_floor))
	 			(
					OnPlayerSkillUp(playerid, SKILL_STRENGTH)
				)
			)
		)
		
		PlayerCache(playerid)(pDailyReps) ++
		if(PlayerCache(playerid)(pDailyReps) ) MAX_DAILY_REPS)
		(
			OnPlayerGymTrainStopped(playerid)
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Informacja, Twoja postaæ jest zbyt zmêczona ¿eby pakowaæ tak d³ugi czas., OK, )
		)		
		return 1
	)
	if(PlayerCache(playerid)(pGymType) == TRAIN_PUNCH_BAG)
	(
		PlayerCache(playerid)(pGymValue1) ++
		
		format(string, sizeof(string), Uderzaj w ~r~worek ~b~(~y~PPM ~w~+ ~y~ENTER~b~)~w~.~n~~n~Trafienia: ~g~~h~%d/%d~n~~n~~w~Po osiagnieciu ~g~celu~w~, Twoja postac nauczy sie nowego ~y~stylu ~w~walki., PlayerCache(playerid)(pGymValue1), PlayerCache(playerid)(pGymValue2))
		TextDrawSetString(Text:TextDrawMainInfo(playerid), string)
		
		TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
		
		if(PlayerCache(playerid)(pGymValue1) )= PlayerCache(playerid)(pGymValue2))
		(
			OnPlayerGymTrainStopped(playerid)

		   	TextDrawSetString(Text:TextDrawMainInfo(playerid), ~b~Trening ~w~dobiegl konca. Odblokowano ~y~nowy ~w~styl walki.)
			TextDrawShowForPlayer(playerid, Text:TextDrawMainInfo(playerid))
			
			PlayerCache(playerid)(pShowInfoText) = 5
			
			fstyle = GetPlayerFightingStyle(playerid)
			if(fstyle == FIGHT_STYLE_NORMAL)
			(
				if(!(PlayerCache(playerid)(pKnownStyles) & 1))
				(
					PlayerCache(playerid)(pKnownStyles) += 1
				)
			)
			else if(fstyle == FIGHT_STYLE_BOXING)
			(
				if(!(PlayerCache(playerid)(pKnownStyles) & 2))
				(
					PlayerCache(playerid)(pKnownStyles) += 2
				)
			)
			else if(fstyle == FIGHT_STYLE_KUNGFU)
			(
				if(!(PlayerCache(playerid)(pKnownStyles) & 4))
				(
					PlayerCache(playerid)(pKnownStyles) += 4
				)
			)
			else if(fstyle == FIGHT_STYLE_KNEEHEAD)
			(
				if(!(PlayerCache(playerid)(pKnownStyles) & 8))
				(
					PlayerCache(playerid)(pKnownStyles) += 8
				)
			)
			else if(fstyle == FIGHT_STYLE_GRABKICK)
			(
				if(!(PlayerCache(playerid)(pKnownStyles) & 16))
				(
					PlayerCache(playerid)(pKnownStyles) += 16
				)
			)
			PlayerCache(playerid)(pFightingStyle) = fstyle
			SavePlayerStats(playerid, SAVE_PLAYER_BASIC)
		)
	)
	return 1
)