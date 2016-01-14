// Poker
#define MAX_POKERGAMES 					200
#define INVALID_POKER_GAME_ID 			(-1)
#define INVALID_POKER_SLOT_ID			(-1)
#define POKER_NEEDED_PLAYERS			2 // Zmieniæ na 3
#define POKER_MAX_PLAYERS				6

// Stó³ do pokera
#define OBJECT_POKER_TABLE				2188

// Typy ticków
#define POKER_TICK_RAISE				1			// podbicie
#define POKER_TICK_BED					2			// sprawdzenie
#define POKER_TICK_FOLD					3			// pas
#define POKER_TICK_MAKE					4			// tworzenie gry

// Dialogi
#define D_POKER_INVITE 					231

// Tablica gier
enum pokerPars
(
	bool:pkActive,
	pkPhase,				// Status gry
	
	pkCard1,
	pkCard2,
	pkCard3,
	pkCard4,
	pkCard5,
	
	pkRound,	
	
	Float:pkPosX,
	Float:pkPosY,
	Float:pkPosZ,
	
	pkSlot(6),
	
	pkBlind,				// Aktualne stawki
	pkNeed,					// Ile kasy trzeba wrzuciæ by kontynuowaæ
	pkActivePlayers,		// Iloœæ aktywnych graczy
	pkTimer,				// Czas akcji gracza
	pkMoney,				// Kasa w stole
	
	pkActivePlayerSlot,		// Aktualny gracz

	
	pkTicks,				// Iloœæ ruchów
)
PokerGames(MAX_POKERGAMES)(pokerPars)


// Tablica na karty
enum cPars
(
	cdName(32),
	cdHumanName(32),
)
CardInfo(53)(cPars) = 
(
	(LD_CARD:cdback,Tyl karty),	//0
	
	(LD_CARD:cd13c,Krol krzyz),
	(LD_CARD:cd13d,Krol karo),
	(LD_CARD:cd13h,Krol serce),
	(LD_CARD:cd13s,Krol pik),
	
	(LD_CARD:cd12c,Dama krzyz),
	(LD_CARD:cd12d,Dama karo),
	(LD_CARD:cd12h,Dama serce),
	(LD_CARD:cd12s,Dama pik),	//8
	
	(LD_CARD:cd11c,Jopek krzyz),
	(LD_CARD:cd11d,Jopek karo),
	(LD_CARD:cd11h,Jopek serce),
	(LD_CARD:cd11s,Jopek pik),
	
	(LD_CARD:cd10c,Dziesiatka krzyz),
	(LD_CARD:cd10d,Dziesiatka karo),
	(LD_CARD:cd10h,Dziesiatka serce),
	(LD_CARD:cd10s,Dziesiatka pik),	//16
	
	(LD_CARD:cd9c,Dziewiatka krzyz),
	(LD_CARD:cd9d,Dziewiatka karo),
	(LD_CARD:cd9h,Dziewiatka serce),
	(LD_CARD:cd9s,Dziewiatka pik),
	
	(LD_CARD:cd8c,Osemka krzyz),
	(LD_CARD:cd8d,Osemka karo),
	(LD_CARD:cd8h,Osemka serce),
	(LD_CARD:cd8s,Osemka pik),		//24
	
	(LD_CARD:cd7c,Siodemka krzyz),
	(LD_CARD:cd7d,Siodemka karo),
	(LD_CARD:cd7h,Siodemka serce),
	(LD_CARD:cd7s,Siodemka pik),
	
	(LD_CARD:cd6c,Szostka krzyz),
	(LD_CARD:cd6d,Szostka karo),
	(LD_CARD:cd6h,Szostka serce),
	(LD_CARD:cd6s,Szostka pik),		//32
	
	(LD_CARD:cd5c,Piatka krzyz),
	(LD_CARD:cd5d,Piatka karo),
	(LD_CARD:cd5h,Piatka serce),
	(LD_CARD:cd5s,Piatka pik),
	
	(LD_CARD:cd4c,Czworka krzyz),
	(LD_CARD:cd4d,Czworka karo),
	(LD_CARD:cd4h,Czworka serce),
	(LD_CARD:cd4s,Czworka pik),	//40
	
	(LD_CARD:cd3c,Trojka krzyz),
	(LD_CARD:cd3d,Trojka karo),
	(LD_CARD:cd3h,Trojka serce),
	(LD_CARD:cd3s,Trojka pik),
	
	(LD_CARD:cd2c,Dwojka krzyz),
	(LD_CARD:cd2d,Dwojka karo),
	(LD_CARD:cd2h,Dwojka serce),
	(LD_CARD:cd2s,Dwojka pik),	//48
	
	(LD_CARD:cd1c,As krzyz),	//49
	(LD_CARD:cd1d,As karo),	//50
	(LD_CARD:cd1h,As serce),	//51
	(LD_CARD:cd1s,As pik)		//52
)

CMD:pkshow(playerid,params())
(
	poker_DebugPokerShow(playerid)
	return 1
)

CMD:pkhide(playerid,params())
(
	poker_DebugPokerHide(playerid)
	return 1
)

stock poker_DebugPokerShow(playerid)
(
	PlayerTextDrawShow(playerid,TextDrawTableMSG1(playerid) )
	PlayerTextDrawShow(playerid,TextDrawActionWindow(playerid))
	PlayerTextDrawShow(playerid,TextDrawTableCardOne(playerid))
	PlayerTextDrawShow(playerid,TextDrawTableCardTwo(playerid))
	PlayerTextDrawShow(playerid,TextDrawTableCardThree(playerid))
	PlayerTextDrawShow(playerid,TextDrawTableCardFour(playerid))
	PlayerTextDrawShow(playerid,TextDrawTableCardFive(playerid))
	
	PlayerTextDrawShow(playerid,TextDrawTableMSG2(playerid) )
	PlayerTextDrawShow(playerid,TextDrawPlayerCardOne(playerid))
	PlayerTextDrawShow(playerid,TextDrawPlayerCardTwo(playerid))
	
	PlayerTextDrawShow(playerid,TextDrawTableCash(playerid))
	PlayerTextDrawShow(playerid,TextDrawActionCheck(playerid))
	PlayerTextDrawShow(playerid,TextDrawActionBed(playerid))
	PlayerTextDrawShow(playerid,TextDrawActionFold(playerid))
	
	SelectTextDraw(playerid, 0x00FF00FF) 
	return 1
)

stock poker_DebugPokerHide(playerid)
(
	PlayerTextDrawHide(playerid,TextDrawTableMSG1(playerid) )
	PlayerTextDrawHide(playerid,TextDrawActionWindow(playerid))
	PlayerTextDrawHide(playerid,TextDrawTableCardOne(playerid))
	PlayerTextDrawHide(playerid,TextDrawTableCardTwo(playerid))
	PlayerTextDrawHide(playerid,TextDrawTableCardThree(playerid))
	PlayerTextDrawHide(playerid,TextDrawTableCardFour(playerid))
	PlayerTextDrawHide(playerid,TextDrawTableCardFive(playerid))
	
	PlayerTextDrawHide(playerid,TextDrawTableMSG2(playerid) )
	PlayerTextDrawHide(playerid,TextDrawPlayerCardOne(playerid))
	PlayerTextDrawHide(playerid,TextDrawPlayerCardTwo(playerid))
	
	PlayerTextDrawHide(playerid,TextDrawTableCash(playerid))
	PlayerTextDrawHide(playerid,TextDrawActionCheck(playerid))
	PlayerTextDrawHide(playerid,TextDrawActionBed(playerid))
	PlayerTextDrawHide(playerid,TextDrawActionFold(playerid))
	
	CancelSelectTextDraw(playerid)
	return 1
)

/*
	koniec testowych
*/


hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext())
(
	if(dialogid == D_POKER_INVITE)
	(
		string(256)
		if(response)
		(
			gameid = PlayerCache(playerid)(pPokerID)
			PokerGames(gameid)(pkActivePlayers)++
			PokerGames(gameid)(pkSlot)(GetFreeSlotInPoker(gameid)) = playerid
			format(string, sizeof(string), %s zaakceptowa³ zaproszenie. (S: %d), PlayerName(playerid), GetFreeSlotInPoker(gameid))
			pkMessageToAll(PlayerCache(playerid)(pPokerID), string)
		)
		else
		(
			format(string, sizeof(string), %s odrzuci³ zaproszenie., PlayerName(playerid))
			pkMessageToAll(PlayerCache(playerid)(pPokerID), string)
			PlayerCache(playerid)(pPokerID) = INVALID_POKER_GAME_ID
		)
	)
)

CMD:poker(playerid,params())
(
	if(PlayerCache(playerid)(pAdmin) == 0)
	(
		return 1
	)
	
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /poker (zaloz | zapros | opusc | zakoncz | start))
	 	return 1
	)
	
	if(!strcmp(type, zaloz, true))
	(
		objectid = GetClosestObject(playerid), string(256)
		if(objectid == INVALID_OBJECT_ID || GetObjectModel(objectid) != OBJECT_POKER_TABLE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono sto³u do pokera w pobli¿u., OK, )
			return 1
		)
		if(PlayerCache(playerid)(pPokerID) != INVALID_POKER_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie posiadasz ju¿ za³o¿ony stó³ do gry., OK, )
			format(string, sizeof(string), ID sto³u: %d, PlayerCache(playerid)(pPokerID))
			pkMessage(playerid, string)
			return 1
		)
		gameid = GetFreePokerID()
		if(gameid == INVALID_POKER_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿na utworzyæ gry., OK, )
			return 1
		)
		PokerGames(gameid)(pkActive) = true
		PokerGames(gameid)(pkPhase) = POKER_TICK_MAKE
		PokerGames(gameid)(pkActivePlayers)++
		PokerGames(gameid)(pkSlot)(0) = playerid
		PlayerCache(playerid)(pPokerID) = gameid
		format(string, sizeof(string), Utworzono stó³. ID: %d, gameid)
		pkMessage(playerid, string)
		return 1
	)
	
	if(!strcmp(type, zakoncz, true))
	(
		
	)
	
	if(!strcmp(type, zapros, true))
	(
		targetid
		if(sscanf(varchar, d, targetid))
		(
			hrp_Tip(playerid, /poker zapros (ID gracza))
			return 1
		)
		if(PlayerCache(playerid)(pPokerID) == INVALID_POKER_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem sto³u.\nAby za³o¿yæ, u¿yj /poker zaloz., OK, )
			return 1
		)
		if(targetid == INVALID_PLAYER_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wprowadzono b³êdne ID gracza., OK, )
			return 1
		)
		if(!Logged(targetid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Gracz o podanym ID nie jest zalogowany., OK, )
			return 1
		)
		if(targetid == playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaprosiæ siebie samego do gry w pokera., OK, )
			return 1
		)
		if(PlayerCache(targetid)(pPokerID) != INVALID_POKER_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wybrany gracz jest ju¿ zapisany do sto³u., OK, )
			return 1
		)
		gameid = PlayerCache(playerid)(pPokerID), slotid = GetFreeSlotInPoker(gameid)
		if(slotid == INVALID_POKER_SLOT_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaprosiæ ju¿ wiêcej graczy do sto³u., OK, )
			return 1
		)
		if(!PlayerToPlayer(5.0, playerid, targetid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie jest blisko Ciebie., OK, )
			return 1
		)
		PlayerCache(targetid)(pPokerID) = gameid
		ShowPlayerDialog(targetid, D_POKER_INVITE, DIALOG_STYLE_MSGBOX, Poker, Czy akceptujesz zaproszenie gracza do sto³u pokerowego?, Tak, Nie)
		pkMessage(playerid, Zaprosi³eœ gracza.)
		return 1
	)
	
	if(!strcmp(type, opusc, true))
	(
		if(PlayerCache(playerid)(pPokerID) == INVALID_POKER_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ zaproszony do ¿adnego sto³u., OK, )
			return 1
		)
		gameid = PlayerCache(playerid)(pPokerID), slotid = GetPlayerSlotInPoker(gameid, playerid), string(256)
		format(string, sizeof(string), %s opuœci³ stó³. (S: %d), PlayerName(playerid), slotid)
		pkMessageToAll(PlayerCache(playerid)(pPokerID), string)
		PokerGames(gameid)(pkActivePlayers)--
		PokerGames(gameid)(pkSlot)(slotid) = INVALID_PLAYER_ID
		PlayerCache(playerid)(pPokerID) = INVALID_POKER_GAME_ID
		pkMessage(playerid, Opuœci³eœ stó³.)
		return 1
	)
	
	if(!strcmp(type, start, true))
	(
		gameid = PlayerCache(playerid)(pPokerID), string(256)
		if(gameid == INVALID_POKER_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem sto³u.\nAby za³o¿yæ, u¿yj /poker zaloz., OK, )
			return 1
		)
		if(PokerGames(gameid)(pkActivePlayers) ( POKER_NEEDED_PLAYERS || PokerGames(gameid)(pkActivePlayers) ) POKER_MAX_PLAYERS)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby wystartowaæ grê, przy stole musi usi¹œæ przynajmniej 3 graczy., OK, )
			return 1
		)
		format(string, sizeof(string), %s rozpocz¹³ grê., PlayerName(playerid))
		pkMessageToAll(PlayerCache(playerid)(pPokerID), string)
		StartPoker(gameid)
		return 1
	)
)


/*
	Ogólne funkcje
*/

// Komunikaty pokerowe
stock pkMessage(playerid, givenString())
(
	string(256)
	format(string, sizeof(string), (0000FF)POKER(FFFFFF): %s, givenString)

	SendClientMessage(playerid, COLOR_WHITE, string)
	return 1
)

// Komunikat pokerowy dla ka¿dego przy stole
stock pkMessageToAll(gameid, givenString())
(
	string(256)
	format(string, sizeof(string), (0000FF)POKER(FFFFFF): %s, givenString)
	for(i = 0  i ( 5 i++)
	(
		if(PokerGames(gameid)(pkSlot)(i) != INVALID_PLAYER_ID)
		(
			SendClientMessage(i, COLOR_WHITE, string)
		)
	)
	return 1
)

// Szukanie wolnego ID dla gry
stock GetFreePokerID()
(
	for(i = 0 i ( MAX_POKERGAMES i++)
	(
		if(!PokerGames(i)(pkActive))
		(
			return i
		)
	)
	return INVALID_POKER_GAME_ID
)

// Szukanie wolnego slota gracza w stole
stock GetFreeSlotInPoker(gameid)
(
	for(i = 0  i ( 5 i++)
	(
		if(PokerGames(gameid)(pkSlot)(i) == INVALID_PLAYER_ID)
		(
			return i
		)
	)
	return INVALID_POKER_SLOT_ID
)

// Szukanie obecnego slota gracza w stole
stock GetPlayerSlotInPoker(gameid, playerid)
(
	for(i = 0  i ( 5 i++)
	(
		if(PokerGames(gameid)(pkSlot)(i) == playerid)
		(
			return i
		)
	)
	return INVALID_POKER_SLOT_ID
)

// Rozpoczêcie gry
stock StartPoker(gameid)
(
	for(i = 0  i ( 5 i++)
	(
		if(PokerGames(gameid)(pkSlot)(i) != INVALID_PLAYER_ID)
		(
			poker_DebugPokerShow(PokerGames(gameid)(pkSlot)(i))
		)
	)
	return 1
)

stock SetPokerTick(playerid, ticktype)
(
	gameid = PlayerCache(playerid)(pPokerID)
	switch(ticktype)
	(
		case POKER_TICK_MAKE:
		(
			
		)
	)
	
	return 1
)

stock poker_ShowPlayerTable(playerid)
(
	gameid = PlayerCache(playerid)(pPoker)
	string(128)
	PlayerTextDrawShow(playerid,TextDrawTableMSG1(playerid) )
	PlayerTextDrawShow(playerid,TextDrawActionWindow(playerid))
	
	PlayerTextDrawSetString(playerid,TextDrawTableCardOne(playerid), CardInfo(PokerGames(gameid)(pkCard1))(cdName))
	PlayerTextDrawShow(playerid,TextDrawTableCardOne(playerid))
	
	PlayerTextDrawSetString(playerid,TextDrawTableCardTwo(playerid), CardInfo(PokerGames(gameid)(pkCard2))(cdName))
	PlayerTextDrawShow(playerid,TextDrawTableCardTwo(playerid))
	
	PlayerTextDrawSetString(playerid,TextDrawTableCardThree(playerid), CardInfo(PokerGames(gameid)(pkCard3))(cdName))
	PlayerTextDrawShow(playerid,TextDrawTableCardThree(playerid))
	
	PlayerTextDrawSetString(playerid,TextDrawTableCardFour(playerid), CardInfo(PokerGames(gameid)(pkCard4))(cdName))
	PlayerTextDrawShow(playerid,TextDrawTableCardFour(playerid))
	
	PlayerTextDrawSetString(playerid,TextDrawTableCardFive(playerid), CardInfo(PokerGames(gameid)(pkCard5))(cdName))
	PlayerTextDrawShow(playerid,TextDrawTableCardFive(playerid))
	
	PlayerTextDrawShow(playerid,TextDrawTableMSG2(playerid) )
	
	PlayerTextDrawSetString(playerid,TextDrawPlayerCardOne(playerid), CardInfo(PlayerCache(playerid)(pcOne))(cdName))
	PlayerTextDrawShow(playerid,TextDrawPlayerCardOne(playerid))
	
	PlayerTextDrawSetString(playerid,TextDrawPlayerCardTwo(playerid), CardInfo(PlayerCache(playerid)(pcTwo))(cdName))
	PlayerTextDrawShow(playerid,TextDrawPlayerCardTwo(playerid))
	
	format(string,sizeof(string),Kasa: ~b~~h~$%i,PokerGames(gameid)(pkMoney))
	PlayerTextDrawSetString(playerid,TextDrawTableCash(playerid), string)
	PlayerTextDrawShow(playerid,TextDrawTableCash(playerid))

	PlayerTextDrawShow(playerid,TextDrawActionCheck(playerid))
	PlayerTextDrawShow(playerid,TextDrawActionBed(playerid))
	PlayerTextDrawShow(playerid,TextDrawActionFold(playerid))
	return 1
)

stock poker_LoadTextDraws(playerid)
(
	//tx welcome
	TextDrawTableMSG1(playerid) = CreatePlayerTextDraw(playerid,249.000000, 116.000000, Karty na stole)
	PlayerTextDrawBackgroundColor(playerid,TextDrawTableMSG1(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawTableMSG1(playerid), 2)
	PlayerTextDrawLetterSize(playerid,TextDrawTableMSG1(playerid), 0.449999, 1.899999)
	PlayerTextDrawColor(playerid,TextDrawTableMSG1(playerid), -16776961)
	PlayerTextDrawSetOutline(playerid,TextDrawTableMSG1(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawTableMSG1(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawTableMSG1(playerid), 1)
	
	//background dla okna akcji
	TextDrawActionWindow(playerid) = CreatePlayerTextDraw(playerid,598.000000, 133.000000, ~n~~n~~n~~n~~n~~n~)
	PlayerTextDrawBackgroundColor(playerid,TextDrawActionWindow(playerid) , 255)
	PlayerTextDrawFont(playerid,TextDrawActionWindow(playerid) , 1)
	PlayerTextDrawLetterSize(playerid,TextDrawActionWindow(playerid) , 0.500000, 1.000000)
	PlayerTextDrawColor(playerid,TextDrawActionWindow(playerid) , -1)
	PlayerTextDrawSetOutline(playerid,TextDrawActionWindow(playerid) , 0)
	PlayerTextDrawSetProportional(playerid,TextDrawActionWindow(playerid) , 1)
	PlayerTextDrawSetShadow(playerid,TextDrawActionWindow(playerid) , 1)
	PlayerTextDrawUseBox(playerid,TextDrawActionWindow(playerid) , 1)
	PlayerTextDrawBoxColor(playerid,TextDrawActionWindow(playerid) , 100)
	PlayerTextDrawTextSize(playerid,TextDrawActionWindow(playerid) , 437.000000, 0.000000)
	
	//karta 1 w stole
	TextDrawTableCardOne(playerid) = CreatePlayerTextDraw(playerid,259.000000, 140.000000, ld_card:cdback)
	PlayerTextDrawBackgroundColor(playerid,TextDrawTableCardOne(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawTableCardOne(playerid), 4)
	PlayerTextDrawLetterSize(playerid,TextDrawTableCardOne(playerid), 0.430000, 0.199999)
	PlayerTextDrawColor(playerid,TextDrawTableCardOne(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawTableCardOne(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawTableCardOne(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawTableCardOne(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawTableCardOne(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawTableCardOne(playerid), 255)
	PlayerTextDrawTextSize(playerid,TextDrawTableCardOne(playerid), 36.000000, 43.000000)
	
	//karta 2 w stole
	TextDrawTableCardTwo(playerid) = CreatePlayerTextDraw(playerid,302.000000, 140.000000, ld_card:cdback)
	PlayerTextDrawBackgroundColor(playerid,TextDrawTableCardTwo(playerid) , 255)
	PlayerTextDrawFont(playerid,TextDrawTableCardTwo(playerid) , 4)
	PlayerTextDrawLetterSize(playerid,TextDrawTableCardTwo(playerid) , 0.430000, 0.199999)
	PlayerTextDrawColor(playerid,TextDrawTableCardTwo(playerid) , -1)
	PlayerTextDrawSetOutline(playerid,TextDrawTableCardTwo(playerid) , 0)
	PlayerTextDrawSetProportional(playerid,TextDrawTableCardTwo(playerid) , 1)
	PlayerTextDrawSetShadow(playerid,TextDrawTableCardTwo(playerid) , 1)
	PlayerTextDrawUseBox(playerid,TextDrawTableCardTwo(playerid) , 1)
	PlayerTextDrawBoxColor(playerid,TextDrawTableCardTwo(playerid) , 255)
	PlayerTextDrawTextSize(playerid,TextDrawTableCardTwo(playerid) , 36.000000, 43.000000)
	
	//karta 3 w stole
	TextDrawTableCardThree(playerid) = CreatePlayerTextDraw(playerid,345.000000, 140.000000, ld_card:cdback)
	PlayerTextDrawBackgroundColor(playerid,TextDrawTableCardThree(playerid) , 255)
	PlayerTextDrawFont(playerid,TextDrawTableCardThree(playerid) , 4)
	PlayerTextDrawLetterSize(playerid,TextDrawTableCardThree(playerid) , 0.430000, 0.199999)
	PlayerTextDrawColor(playerid,TextDrawTableCardThree(playerid) , -1)
	PlayerTextDrawSetOutline(playerid,TextDrawTableCardThree(playerid) , 0)
	PlayerTextDrawSetProportional(playerid,TextDrawTableCardThree(playerid) , 1)
	PlayerTextDrawSetShadow(playerid,TextDrawTableCardThree(playerid) , 1)
	PlayerTextDrawUseBox(playerid,TextDrawTableCardThree(playerid) , 1)
	PlayerTextDrawBoxColor(playerid,TextDrawTableCardThree(playerid) , 255)
	PlayerTextDrawTextSize(playerid,TextDrawTableCardThree(playerid) , 36.000000, 43.000000)
	
	//karta 4 w stole
	TextDrawTableCardFour(playerid) = CreatePlayerTextDraw(playerid,388.000000, 140.000000, ld_card:cdback)
	PlayerTextDrawBackgroundColor(playerid,TextDrawTableCardFour(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawTableCardFour(playerid), 4)
	PlayerTextDrawLetterSize(playerid,TextDrawTableCardFour(playerid), 0.430000, 0.199999)
	PlayerTextDrawColor(playerid,TextDrawTableCardFour(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawTableCardFour(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawTableCardFour(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawTableCardFour(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawTableCardFour(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawTableCardFour(playerid), 255)
	PlayerTextDrawTextSize(playerid,TextDrawTableCardFour(playerid), 36.000000, 43.000000)
	
	//karta 5 w stole
	TextDrawTableCardFive(playerid) = CreatePlayerTextDraw(playerid,216.000000, 140.000000, ld_card:cdback)
	PlayerTextDrawBackgroundColor(playerid,TextDrawTableCardFive(playerid) , 255)
	PlayerTextDrawFont(playerid,TextDrawTableCardFive(playerid) , 4)
	PlayerTextDrawLetterSize(playerid,TextDrawTableCardFive(playerid) , 0.430000, 0.199999)
	PlayerTextDrawColor(playerid,TextDrawTableCardFive(playerid) , -1)
	PlayerTextDrawSetOutline(playerid,TextDrawTableCardFive(playerid) , 0)
	PlayerTextDrawSetProportional(playerid,TextDrawTableCardFive(playerid) , 1)
	PlayerTextDrawSetShadow(playerid,TextDrawTableCardFive(playerid) , 1)
	PlayerTextDrawUseBox(playerid,TextDrawTableCardFive(playerid) , 1)
	PlayerTextDrawBoxColor(playerid,TextDrawTableCardFive(playerid) , 255)
	PlayerTextDrawTextSize(playerid,TextDrawTableCardFive(playerid) , 36.000000, 43.000000)
	
	//msg 2 - twoje kart
	TextDrawTableMSG2(playerid) = CreatePlayerTextDraw(playerid,248.000000, 193.000000, Twoje karty)
	PlayerTextDrawBackgroundColor(playerid,TextDrawTableMSG2(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawTableMSG2(playerid), 2)
	PlayerTextDrawLetterSize(playerid,TextDrawTableMSG2(playerid), 0.449999, 1.899999)
	PlayerTextDrawColor(playerid,TextDrawTableMSG2(playerid), -16776961)
	PlayerTextDrawSetOutline(playerid,TextDrawTableMSG2(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawTableMSG2(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawTableMSG2(playerid), 1)
	
	//player card 1
	TextDrawPlayerCardOne(playerid) = CreatePlayerTextDraw(playerid,274.000000, 215.000000, ld_card:cdback)
	PlayerTextDrawBackgroundColor(playerid,TextDrawPlayerCardOne(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawPlayerCardOne(playerid), 4)
	PlayerTextDrawLetterSize(playerid,TextDrawPlayerCardOne(playerid), 0.430000, 0.199999)
	PlayerTextDrawColor(playerid,TextDrawPlayerCardOne(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawPlayerCardOne(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawPlayerCardOne(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawPlayerCardOne(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawPlayerCardOne(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawPlayerCardOne(playerid), 255)
	PlayerTextDrawTextSize(playerid,TextDrawPlayerCardOne(playerid), 36.000000, 43.000000)
	
	//player card 2
	TextDrawPlayerCardTwo(playerid) = CreatePlayerTextDraw(playerid,323.000000, 215.000000, ld_card:cdback)
	PlayerTextDrawBackgroundColor(playerid,TextDrawPlayerCardTwo(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawPlayerCardTwo(playerid), 4)
	PlayerTextDrawLetterSize(playerid,TextDrawPlayerCardTwo(playerid), 0.430000, 0.199999)
	PlayerTextDrawColor(playerid,TextDrawPlayerCardTwo(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawPlayerCardTwo(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawPlayerCardTwo(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawPlayerCardTwo(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawPlayerCardTwo(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawPlayerCardTwo(playerid), 255)
	PlayerTextDrawTextSize(playerid,TextDrawPlayerCardTwo(playerid), 36.000000, 43.000000)
	
	//kasa w stole
	TextDrawTableCash(playerid) = CreatePlayerTextDraw(playerid,460.000000, 136.000000, Kasa: ~b~~h~$0)
	PlayerTextDrawBackgroundColor(playerid,TextDrawTableCash(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawTableCash(playerid), 3)
	PlayerTextDrawLetterSize(playerid,TextDrawTableCash(playerid), 0.539999, 1.899999)
	PlayerTextDrawColor(playerid,TextDrawTableCash(playerid), 16711935)
	PlayerTextDrawSetOutline(playerid,TextDrawTableCash(playerid), 0)
	PlayerTextDrawSetProportional(playerid,TextDrawTableCash(playerid), 1)
	PlayerTextDrawSetShadow(playerid,TextDrawTableCash(playerid), 1)
	
	//akcja - sprawdŸ
	TextDrawActionCheck(playerid) = CreatePlayerTextDraw(playerid,470.000000, 174.000000, Sprawdz)
	PlayerTextDrawAlignment(playerid,TextDrawActionCheck(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,TextDrawActionCheck(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawActionCheck(playerid), 1)
	PlayerTextDrawLetterSize(playerid,TextDrawActionCheck(playerid), 0.230000, 0.899999)
	PlayerTextDrawColor(playerid,TextDrawActionCheck(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawActionCheck(playerid), 1)
	PlayerTextDrawSetProportional(playerid,TextDrawActionCheck(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawActionCheck(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawActionCheck(playerid), 1316040)
	PlayerTextDrawTextSize(playerid,TextDrawActionCheck(playerid), 264.000000, 36.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawActionCheck(playerid),1)
	
	//akcja - podbij
	TextDrawActionBed(playerid) = CreatePlayerTextDraw(playerid,517.000000, 174.000000, Podbij)
	PlayerTextDrawAlignment(playerid,TextDrawActionBed(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,TextDrawActionBed(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawActionBed(playerid), 1)
	PlayerTextDrawLetterSize(playerid,TextDrawActionBed(playerid), 0.230000, 0.899999)
	PlayerTextDrawColor(playerid,TextDrawActionBed(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawActionBed(playerid), 1)
	PlayerTextDrawSetProportional(playerid,TextDrawActionBed(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawActionBed(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawActionBed(playerid), 1316040)
	PlayerTextDrawTextSize(playerid,TextDrawActionBed(playerid), 264.000000, 36.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawActionBed(playerid),1)
	
	//akcja - pasuj
	TextDrawActionFold(playerid) = CreatePlayerTextDraw(playerid,564.000000, 174.000000, Pasuj)
	PlayerTextDrawAlignment(playerid,TextDrawActionFold(playerid), 2)
	PlayerTextDrawBackgroundColor(playerid,TextDrawActionFold(playerid), 255)
	PlayerTextDrawFont(playerid,TextDrawActionFold(playerid), 1)
	PlayerTextDrawLetterSize(playerid,TextDrawActionFold(playerid), 0.230000, 0.899999)
	PlayerTextDrawColor(playerid,TextDrawActionFold(playerid), -1)
	PlayerTextDrawSetOutline(playerid,TextDrawActionFold(playerid), 1)
	PlayerTextDrawSetProportional(playerid,TextDrawActionFold(playerid), 1)
	PlayerTextDrawUseBox(playerid,TextDrawActionFold(playerid), 1)
	PlayerTextDrawBoxColor(playerid,TextDrawActionFold(playerid), 1316040)
	PlayerTextDrawTextSize(playerid,TextDrawActionFold(playerid), 264.000000, 36.000000)
	PlayerTextDrawSetSelectable(playerid,TextDrawActionFold(playerid),1)
	
	return 1
)

