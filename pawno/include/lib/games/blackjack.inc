/* BlackJack
Skrypt gry w blacjkacja wydaje siê dzia³aæ dobrze,
by³ testowany kilkukrotnie przez wiele osób.

Podpisano: Mateusz.
*/

#define MAX_BLACKJACKGAMES 					200
#define INVALID_BLACKJACK_GAME_ID 			(-1)
#define INVALID_BLACKJACK_SLOT_ID			(-1)
#define BLACKJACK_NEEDED_PLAYERS			2
#define BLACKJACK_MAX_PLAYERS				4
#define BLACKJACK_MAX_PLAYER_CARDS			6

// StÃ³Å‚ do blackjacka
#define OBJECT_BLACKJACK_TABLE				2188

// Etapy
#define BLACKJACK_PHASE_MAKE				1
#define BLACKJACK_PHASE_GAME				2

// Dialogi
#define D_BLACKJACK_INVITE 					231

// TextDrawy
PlayerText:TextDrawTitleP1(MAX_BLACKJACKGAMES)
PlayerText:TextDrawTitleP2(MAX_BLACKJACKGAMES)
PlayerText:TextDrawTitleP3(MAX_BLACKJACKGAMES)
PlayerText:TextDrawTitleP4(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP1CardOne(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP1CardTwo(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP1CardThree(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP1CardFour(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP1CardFive(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP1CardSix(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP2CardOne(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP2CardTwo(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP2CardThree(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP2CardFour(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP2CardFive(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP2CardSix(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP3CardOne(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP3CardTwo(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP3CardThree(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP3CardFour(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP3CardFive(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP3CardSix(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP4CardOne(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP4CardTwo(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP4CardThree(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP4CardFour(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP4CardFive(MAX_BLACKJACKGAMES)
PlayerText:TextDrawP4CardSix(MAX_BLACKJACKGAMES)
PlayerText:TextDrawActionCash(MAX_BLACKJACKGAMES)
	
// Tablica gier
enum sBlackJack
(
	bjID,
	bjOwner,
	
	bool:bjActive,
	bjPhase,				// Status gry

	bjSlot(4),
	
	bool:BjCard(52),		// Karta na stole (true/false)
	
	bjActivePlayers,		// Iloœæ aktywnych graczy
	bjTimer,				// Czas akcji gracza
	bjMoney,				// Kasa w stole
	
	bjActivePlayerSlot		// Aktualny gracz
)
BlackJack(MAX_BLACKJACKGAMES)(sBlackJack)

// Tablica graczy
enum sBlackjackPlayer
(
	bjID,
	bjpSeat,
	bjpPoints,
	bool:bjpFold,
	bjpCards(BLACKJACK_MAX_PLAYER_CARDS)
)

BlackjackPlayer(MAX_PLAYERS)(sBlackjackPlayer)

// Tablica na karty
enum cPars
(
	cdName(32),
	cdHumanName(32),
	cdValue,
)
CardInfo(53)(cPars) = 
(
	(LD_CARD:cdback,Pusta,0),

	(LD_CARD:cd13c,Krol krzyz,10),
	(LD_CARD:cd13d,Krol karo,10),
	(LD_CARD:cd13h,Krol serce,10),
	(LD_CARD:cd13s,Krol pik,10),

	(LD_CARD:cd12c,Dama krzyz,10),
	(LD_CARD:cd12d,Dama karo,10),
	(LD_CARD:cd12h,Dama serce,10),
	(LD_CARD:cd12s,Dama pik,10),		//8

	(LD_CARD:cd11c,Jopek krzyz,10),
	(LD_CARD:cd11d,Jopek karo,10),
	(LD_CARD:cd11h,Jopek serce,10),
	(LD_CARD:cd11s,Jopek pik,10),

	(LD_CARD:cd10c,Dziesiatka krzyz,10),
	(LD_CARD:cd10d,Dziesiatka karo,10),
	(LD_CARD:cd10h,Dziesiatka serce,10),
	(LD_CARD:cd10s,Dziesiatka pik,10),	//16

	(LD_CARD:cd9c,Dziewiatka krzyz,9),
	(LD_CARD:cd9d,Dziewiatka karo,9),
	(LD_CARD:cd9h,Dziewiatka serce,9),
	(LD_CARD:cd9s,Dziewiatka pik,9),

	(LD_CARD:cd8c,Osemka krzyz,8),
	(LD_CARD:cd8d,Osemka karo,8),
	(LD_CARD:cd8h,Osemka serce,8),
	(LD_CARD:cd8s,Osemka pik,8),		//24

	(LD_CARD:cd7c,Siodemka krzyz,7),
	(LD_CARD:cd7d,Siodemka karo,7),
	(LD_CARD:cd7h,Siodemka serce,7),
	(LD_CARD:cd7s,Siodemka pik,7),

	(LD_CARD:cd6c,Szostka krzyz,6),
	(LD_CARD:cd6d,Szostka karo,6),
	(LD_CARD:cd6h,Szostka serce,6),
	(LD_CARD:cd6s,Szostka pik,6),		//32

	(LD_CARD:cd5c,Piatka krzyz,5),
	(LD_CARD:cd5d,Piatka karo,5),
	(LD_CARD:cd5h,Piatka serce,5),
	(LD_CARD:cd5s,Piatka pik,5),

	(LD_CARD:cd4c,Czworka krzyz,4),
	(LD_CARD:cd4d,Czworka karo,4),
	(LD_CARD:cd4h,Czworka serce,4),
	(LD_CARD:cd4s,Czworka pik,4),		//40

	(LD_CARD:cd3c,Trojka krzyz,3),
	(LD_CARD:cd3d,Trojka karo,3),
	(LD_CARD:cd3h,Trojka serce,3),
	(LD_CARD:cd3s,Trojka pik,3),

	(LD_CARD:cd2c,Dwojka krzyz,2),
	(LD_CARD:cd2d,Dwojka karo,2),
	(LD_CARD:cd2h,Dwojka serce,2),
	(LD_CARD:cd2s,Dwojka pik,2),		//48

	(LD_CARD:cd1c,As krzyz,11),			//49
	(LD_CARD:cd1d,As karo,11),			//50
	(LD_CARD:cd1h,As serce,11),			//51
	(LD_CARD:cd1s,As pik,11)			//52
)

hook OnGameModeInit()
(
	for(gameid = 0 gameid ( MAX_BLACKJACKGAMES gameid++)
	(
		ClearBlackjack(gameid)
		
	)
	for(i = 0 i ( MAX_PLAYERS i++)
	(
		BlackjackPlayer(i)(bjID) = INVALID_BLACKJACK_GAME_ID
		BlackjackPlayer(i)(bjpFold) = false
	)
)

hook OnPlayerDisconnect(playerid)
(
	if(BlackjackPlayer(playerid)(bjID) != INVALID_BLACKJACK_GAME_ID)
	(
		gameid = BlackjackPlayer(playerid)(bjID), slotid = BlackjackPlayer(playerid)(bjpSeat), string(256)
		format(string, sizeof(string), %s opuœci³ stó³ (S: %d), PlayerName(playerid), slotid)
		bjMessageToAll(gameid, string)
		BlackJack(gameid)(bjActivePlayers)--
		BlackJack(gameid)(bjSlot)(slotid) = INVALID_PLAYER_ID
		BlackjackPlayer(playerid)(bjID) = INVALID_BLACKJACK_GAME_ID
		BlackjackHideTable(playerid)
	)
)

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext())
(
	if(dialogid == D_BLACKJACK_INVITE)
	(
		string(256)
		if(response)
		(
			gameid = BlackjackPlayer(playerid)(bjID)
			BlackJack(gameid)(bjActivePlayers)++
			slot = GetFreeSlotInBlackjack(gameid)
			BlackJack(gameid)(bjSlot)(slot) = playerid
			BlackjackPlayer(playerid)(bjpSeat) = slot
			format(string, sizeof(string), %s zaakceptowa³ zaproszenie. (S: %d), PlayerName(playerid), slot)
			bjMessageToAll(gameid, string)
		)
		else
		(
			gameid = BlackjackPlayer(playerid)(bjID)
			format(string, sizeof(string), %s odrzuci³ zaproszenie., PlayerName(playerid))
			bjMessageToAll(gameid, string)
			BlackjackPlayer(playerid)(bjID) = INVALID_BLACKJACK_GAME_ID
		)
	)
)

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
(
	if(BlackjackPlayer(playerid)(bjID) != INVALID_BLACKJACK_GAME_ID)
	(
		gameid = BlackjackPlayer(playerid)(bjID)
		if(BlackJack(gameid)(bjPhase) == BLACKJACK_PHASE_GAME)
		(
			if(newkeys & KEY_FIRE)
			(
				if(GetPlayerPoints(playerid) )= 21)
				(
					GuiMsg(playerid, Posiadasz wiêcej b¹dŸ 21 punktów w swoich kartach., 1)
					return 1
				)
				if(BlackjackPlayer(playerid)(bjpFold))
				(
					GuiMsg(playerid, U¿y³eœ opcji pasowania, poczekaj na kolejn¹ rundê., 1)
					return 1
				)
				if(BlackJack(gameid)(bjActivePlayerSlot) != GetPlayerSlotInBlackjack(playerid))
				(
					GuiMsg(playerid, Obecnie jest ruch innego gracza, odczekaj na swoj¹ kolejkê., 1)
					return 1
				)
				else
				(
					RandomCard(playerid)
					CheckGameStatus(gameid)
					BlackjackRefreshTable(gameid)
				)
				return 1
			)
			if(newkeys & KEY_HANDBRAKE)
			(
				if(GetPlayerPoints(playerid) )= 21)
				(
					GuiMsg(playerid, Posiadasz wiêcej b¹dŸ 21 punktów w swoich kartach., 1)
					return 1
				)
				if(BlackjackPlayer(playerid)(bjpFold))
				(
					GuiMsg(playerid, U¿y³eœ opcji pasowania, poczekaj na kolejn¹ rundê., 1)
					return 1			
				)
				if(BlackJack(gameid)(bjActivePlayerSlot) != GetPlayerSlotInBlackjack(playerid))
				(
					GuiMsg(playerid, Obecnie jest ruch innego gracza, odczekaj na swoj¹ kolejkê., 1)
				)
				else
				(
					GuiMsg(playerid, Pasujesz. Od tej pory nie bêdziesz móg³ dobraæ kart w tej rundzie., 1)
					BlackjackPlayer(playerid)(bjpFold) = true
					CheckGameStatus(gameid)
				)
				return 1
			)
		)
	)
	
	return 1
)

CMD:blackjack(playerid,params())
(
	type(32), varchar(32)
	if(sscanf(params, s(32)S()(32), type, varchar))
	(
		hrp_Tip(playerid, /blackjack (zaloz | zapros | opusc | zakoncz | start | pomoc))
	 	return 1
	)
	
	if(!strcmp(type, zaloz, true))
	(
		string(256)
		/*
		Usunieto wymog stolu w aktualizacji z 17/18 pazdziernika.
		objectid = GetClosestObject(playerid)
		if(objectid == INVALID_OBJECT_ID || GetObjectModel(objectid) != OBJECT_BLACKJACK_TABLE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono sto³u do blackjacka w pobli¿u., OK, )
			return 1
		)*/
		if(BlackjackPlayer(playerid)(bjID) != INVALID_BLACKJACK_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Obecnie posiadasz ju¿ za³o¿ony stó³ do gry., OK, )
			format(string, sizeof(string), ID sto³u: %d, BlackjackPlayer(playerid)(bjID))
			bjMessage(playerid, string)
			return 1
		)
		gameid = GetFreeBlackjackID()
		if(gameid == INVALID_BLACKJACK_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿na utworzyæ gry., OK, )
			return 1
		)
		BlackJack(gameid)(bjActive) = true
		BlackJack(gameid)(bjPhase) = BLACKJACK_PHASE_MAKE
		BlackJack(gameid)(bjActivePlayers) = 1
		slot = GetFreeSlotInBlackjack(gameid)
		BlackJack(gameid)(bjSlot)(slot) = playerid
		BlackJack(gameid)(bjOwner) = playerid
		BlackjackPlayer(playerid)(bjID) = gameid
		BlackjackPlayer(playerid)(bjpSeat) = slot
		format(string, sizeof(string), Utworzono stó³. ID: %d (S: %d)., gameid, slot)
		bjMessage(playerid, string)
		return 1
	)
	
	if(!strcmp(type, zakoncz, true))
	(
		gameid = BlackjackPlayer(playerid)(bjID)
		if(BlackJack(gameid)(bjOwner) != playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem sto³u.\nAby za³o¿yæ, u¿yj /blackjack zaloz., OK, )
			return 1
		)
		if(BlackJack(gameid)(bjPhase) != BLACKJACK_PHASE_MAKE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zakoñczyæ gry w trakcie rozgrywki.\nPoczekaj na koniec rundy., OK, )
			return 1
		)
		for(i = 0 i ( 4 i++)
		(
			if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
			(
				hrp_TogglePlayerControllable(BlackJack(gameid)(bjSlot)(i), true)
				BlackJack(gameid)(bjSlot)(i) = INVALID_PLAYER_ID
				BlackjackPlayer(BlackJack(gameid)(bjSlot)(i))(bjID) = INVALID_BLACKJACK_SLOT_ID
			)
		)
		string(256)
		format(string, sizeof(string), %s zamkn¹³ stó³. (ID: %d), PlayerName(playerid), gameid)
		bjMessageToAll(gameid, string)
		ClearBlackjack(gameid)
		return 1
	)
	
	if(!strcmp(type, zapros, true))
	(
		targetid, gameid = BlackjackPlayer(playerid)(bjID)
		if(sscanf(varchar, d, targetid))
		(
			hrp_Tip(playerid, /blackjack zapros (ID gracza))
			return 1
		)
		if(BlackJack(gameid)(bjOwner) != playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem sto³u.\nAby za³o¿yæ, u¿yj /blackjack zaloz., OK, )
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
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaprosiæ siebie samego do gry w blackjacka., OK, )
			return 1
		)
		if(BlackjackPlayer(targetid)(bjID) != INVALID_BLACKJACK_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Wybrany gracz jest ju¿ zapisany do sto³u., OK, )
			return 1
		)
		if(BlackJack(gameid)(bjActivePlayers) )= 4)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie mo¿esz zaprosiæ ju¿ wiêcej graczy do tego sto³u., OK, )
			return 1
		)
		if(!PlayerToPlayer(5.0, playerid, targetid))
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Ten gracz nie jest blisko Ciebie., OK, )
			return 1
		)
		BlackjackPlayer(targetid)(bjID) = gameid
		ShowPlayerDialog(targetid, D_BLACKJACK_INVITE, DIALOG_STYLE_MSGBOX, BlackJack, Czy akceptujesz zaproszenie gracza do sto³u blackjackowego?, Tak, Nie)
		bjMessage(playerid, Zaprosi³eœ gracza.)
		return 1
	)
	
	if(!strcmp(type, opusc, true))
	(
		if(BlackjackPlayer(playerid)(bjID) == INVALID_BLACKJACK_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ zaproszony do ¿adnego sto³u., OK, )
			return 1
		)
		gameid = BlackjackPlayer(playerid)(bjID), slotid = BlackjackPlayer(playerid)(bjpSeat), string(256)
		format(string, sizeof(string), %s opuœci³ stó³ (S: %d), PlayerName(playerid), slotid)
		bjMessageToAll(gameid, string)
		BlackJack(gameid)(bjActivePlayers)--
		if(BlackJack(gameid)(bjActivePlayers) == 0)
		(
			ClearBlackjack(gameid)
		)
		BlackjackHideAll(playerid)
		BlackJack(gameid)(bjSlot)(slotid) = INVALID_PLAYER_ID
		BlackjackPlayer(playerid)(bjID) = INVALID_BLACKJACK_GAME_ID
		hrp_TogglePlayerControllable(playerid, true)
		bjMessage(playerid, Opuœci³eœ stó³.)
		return 1
	)
	
	if(!strcmp(type, start, true))
	(
		gameid = BlackjackPlayer(playerid)(bjID), string(256)
		if(gameid == INVALID_BLACKJACK_GAME_ID)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem sto³u.\nAby za³o¿yæ, u¿yj /blackjack zaloz., OK, )
			return 1
		)
		if(BlackJack(gameid)(bjOwner) != playerid)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie jesteœ w³aœcicielem tego sto³u., OK, )
			return 1
		)
		if(BlackJack(gameid)(bjActivePlayers) ( BLACKJACK_NEEDED_PLAYERS || BlackJack(gameid)(bjActivePlayers) ) BLACKJACK_MAX_PLAYERS)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aby wystartowaæ grê przy stole musi usi¹œæ przynajmniej 2 graczy., OK, )
			return 1
		)
		if(BlackJack(gameid)(bjPhase) != BLACKJACK_PHASE_MAKE)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Aktualnie prowadzisz rozgrywkê., OK, )
			return 1
		)
		money
		if(sscanf(varchar, d, money))
		(
			hrp_Tip(playerid, /blackjack start (Stawka))
			return 1
		)
		if(money ( 1 || money ) 10000)
		(
			ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Kwota nie mo¿e byæ mniejsza ni¿ $1, ani wiêksza ni¿ $10000., OK, )
			return 1
		)
		for(i = 0  i ( 4 i++)
		(
			if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
			(
				if(PlayerCache(BlackJack(gameid)(bjSlot)(i))(pCash) ( money)
				(
					format(string, sizeof(string), Gracz %s nie posiada wystarczaj¹cej gotówki ($%d)., PlayerName(BlackJack(gameid)(bjSlot)(i)), money)
					bjMessageToAll(gameid, string)
					return 1
				)
			)
		)
		BlackJack(gameid)(bjMoney) = money
		for(i = 0  i ( 4 i++)
		(
			if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
			(
				hrp_GivePlayerMoney(BlackJack(gameid)(bjSlot)(i), -money)
			)
		)
		format(string, sizeof(string), %s rozpocz¹³ grê., PlayerName(playerid))
		bjMessageToAll(gameid, string)
		StartBlackjack(gameid)
		return 1
	)
	if(!strcmp(type, pomoc, true))
	(
		string(512)
		format(string, sizeof(string), Instrukcja do gry w BlackJacka na LS-RP.net!\nAby dobraæ kartê, naciœnij (6e9aff)LEWY PRZYCISK MYSZKI(a4c0ff). Aby pasowaæ, wciœnij (6e9aff)PRAWY PRZYCISK MYSZKI(a4c0ff).\nMusisz uzyskaæ iloœæ punktów, która jest najbli¿ej 21 pkt.\nKa¿da karta od 2 do 9 ma wartoœæ równ¹ wartoœci karty.\nAs ma wartoœæ równ¹ 11.\nW Blackjacku u¿ywa siê kilku talii z³o¿onych z 52 kart z których u¿ywa siê od jednej a¿ do szeœciu.\nIm mniej, tym lepiej dla gracza.\nPowodzenia!)
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, BlackJack: Instrukcja, string, OK, )
		return 1
	)
	return 0
)


/*
	Ogólne funkcje
*/

// Czyszczenie tablic
stock ClearBlackjack(gameid)
(
	for(i = 0 i ( 4 i++)
	(
		BlackJack(gameid)(bjSlot)(i) = INVALID_PLAYER_ID
	)
	BlackJack(gameid)(bjActive) = false
	BlackJack(gameid)(bjOwner) = INVALID_PLAYER_ID
	BlackJack(gameid)(bjActivePlayers) = 0
	BlackJack(gameid)(bjPhase) = 0
)

// Komunikaty blackjackowe
stock bjMessage(playerid, givenString())
(
	string(256)
	format(string, sizeof(string), (6e9aff)BlackJack(a4c0ff): %s, givenString)

	SendClientMessage(playerid, COLOR_WHITE, string)
	return 1
)

// Komunikat blackjackowy dla ka¿dego przy stole
stock bjMessageToAll(gameid, givenString())
(
	string(256)
	format(string, sizeof(string), (6e9aff)BlackJack(a4c0ff): %s, givenString)
	for(i = 0  i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
		(
			SendClientMessage(BlackJack(gameid)(bjSlot)(i), COLOR_WHITE, string)
		)
	)
	return 1
)

// Szukanie wolnego ID dla gry
stock GetFreeBlackjackID()
(
	for(i = 0 i ( MAX_BLACKJACKGAMES i++)
	(
		if(!BlackJack(i)(bjActive))
		(
			return i
		)
	)
	return INVALID_BLACKJACK_GAME_ID
)

// Szukanie wolnego slota gracza w stole
stock GetFreeSlotInBlackjack(gameid)
(
	for(i = 0 i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) == INVALID_PLAYER_ID)
		(
			return i
		)
	)
	return INVALID_BLACKJACK_SLOT_ID
)

// Szukanie obecnego slota gracza w stole
stock GetPlayerSlotInBlackjack(playerid)
(
	gameid = BlackjackPlayer(playerid)(bjID)
	for(i = 0 i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) == playerid)
		(
			return i
		)
	)
	return INVALID_BLACKJACK_SLOT_ID
)

// Wybieranie nastêpnego aktywnego gracza
stock SelectNextPlayer(gameid)
(
	if(BlackJack(gameid)(bjActivePlayerSlot) )= BlackJack(gameid)(bjActivePlayers)-1)
	(
		BlackJack(gameid)(bjActivePlayerSlot) = 0
	)
	else
	(
		BlackJack(gameid)(bjActivePlayerSlot)++
	)
	gamerid = BlackJack(gameid)(bjSlot)(BlackJack(gameid)(bjActivePlayerSlot))
	if(GetPlayerPoints(gamerid) )= 21 || BlackjackPlayer(gamerid)(bjpFold))
	(
		SelectNextPlayer(gameid)
	)
	return 1
)

// Czyszczenie gry dla gracza
stock ClearPlayerCache(playerid)
(
	BlackjackPlayer(playerid)(bjpFold) = false
	BlackjackPlayer(playerid)(bjpPoints) = 0
	for(i = 0 i ( BLACKJACK_MAX_PLAYER_CARDS i++)
	(
		BlackjackPlayer(playerid)(bjpCards)(i) = 0
	)
	hrp_TogglePlayerControllable(playerid, true)
)

// Koñczenie gry
stock EndGame(gameid)
(
	string(256)
	maxp = 21
	points(4) = 0
	winpoints = 0
	for(i = 0 i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
		(
			points(i) = BlackjackPlayer(BlackJack(gameid)(bjSlot)(i))(bjpPoints)
		)
	)
	
	while(maxp ) 1 || winpoints == 0)
	(
		if(points(0) == maxp || points(1) == maxp || points(2) == maxp || points(3) == maxp)
		(
			winpoints = maxp
			goto payment
		)
		maxp--
	)
	
	payment:
	if(winpoints == 0)
	(
		for(i = 0 i ( 4 i++)
		(
			if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
			(
				hrp_GivePlayerMoney(BlackJack(gameid)(bjSlot)(i), BlackJack(gameid)(bjMoney))
			)
		)
		format(string, sizeof(string), (6e9aff)BlackJack(a4c0ff): Brak zwyciêzcy, zwrot gotówki dla ka¿dego.)
		bjMessageToAll(gameid, string)
	)
	else
	(
		count = 0
		bool:winner(4) = false
		for(i = 0 i ( 4 i++)
		(
			if(points(i) == winpoints)
			(
				count++
				winner(i) = true
			)
		)
		
		money_in_game = BlackJack(gameid)(bjActivePlayers)*BlackJack(gameid)(bjMoney)
		prize = 0		
		if(count == 1) // jeden zwyciêzca
		(
			prize = money_in_game
		)
		else if(count == 2)
		(
			prize = money_in_game / 2
		)
		else if(count == 3)
		(
			prize = money_in_game / 3
		)
		else if(count == 4)
		(
			prize = money_in_game / 4
		)
		
		if(winner(0))
		(
			hrp_GivePlayerMoney(BlackJack(gameid)(bjSlot)(0), prize)
		)
		if(winner(1))
		(
			hrp_GivePlayerMoney(BlackJack(gameid)(bjSlot)(1), prize)
		)
		if(winner(2))
		(
			hrp_GivePlayerMoney(BlackJack(gameid)(bjSlot)(2), prize)
		)
		if(winner(3))
		(
			hrp_GivePlayerMoney(BlackJack(gameid)(bjSlot)(3), prize)
		)
		format(string, sizeof(string), (6e9aff)BlackJack(a4c0ff): Koniec rozgrywki, gratulacje dla zwyciêzcy/ów!)
		bjMessageToAll(gameid, string)
	)
	
	for(i = 0 i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
		(
			ClearPlayerCache(BlackJack(gameid)(bjSlot)(i))
		)
	)
	
	BlackJack(gameid)(bjPhase) = BLACKJACK_PHASE_MAKE
	BlackJack(gameid)(bjMoney) = 0
	for(i = 0 i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
		(
			blackjack_DestroyTextDraws(BlackJack(gameid)(bjSlot)(i))
		/*	PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawActionCash(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawTitleP1(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawTitleP2(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawTitleP3(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawTitleP4(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP1CardOne(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP1CardTwo(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP1CardThree(gameid))		
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP1CardFour(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP1CardFive(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP1CardSix(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP2CardOne(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP2CardTwo(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP2CardThree(gameid))	
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP2CardFour(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP2CardFive(gameid))	
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP2CardSix(gameid))	
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP3CardOne(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP3CardTwo(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP3CardThree(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP3CardFour(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP3CardFive(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP3CardSix(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP4CardOne(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP4CardTwo(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP4CardThree(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP4CardFour(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP4CardFive(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawP4CardSix(gameid))
			PlayerTextDrawHide(BlackJack(gameid)(bjSlot)(i),TextDrawActionCash(gameid))*/
		)
	)
	return 1
)

// Sprawdzanie statusu gry
stock CheckGameStatus(gameid)
(
	bool:play(4) = false
	for(i = 0 i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
		(
			if(!BlackjackPlayer(BlackJack(gameid)(bjSlot)(i))(bjpFold))
			(
				play(i) = true
			)
		)
	)
	
	if(!play(0) && !play(1) && !play(2) && !play(3))
	(
		EndGame(gameid)
		return 1
	)
	else
	(
		SelectNextPlayer(gameid)
		return 1
	)
)

// Sprawdzanie punktów gracza
stock GetPlayerPoints(playerid)
(
	gameid = BlackjackPlayer(playerid)(bjID)
	for(i = 0 i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) == playerid)
		(
			points = BlackjackPlayer(playerid)(bjpPoints)
			return points
		)
	)
	return 0
)

// Losowanie karty
stock RandomCard(playerid)
(
	rand = random(53)
	new	gameid = BlackjackPlayer(playerid)(bjID)
	
	if(!BlackJack(gameid)(BjCard)(rand) && rand != 0)
	(
		for(i = 0 i ( BLACKJACK_MAX_PLAYER_CARDS i++)
		(
			if(BlackjackPlayer(playerid)(bjpCards)(i) == 0)
			(
				BlackJack(gameid)(BjCard)(rand) = true
				BlackjackPlayer(playerid)(bjpCards)(i) = rand
				BlackjackPlayer(playerid)(bjpPoints) += CardInfo(BlackjackPlayer(playerid)(bjpCards)(i))(cdValue)
				if(BlackjackPlayer(playerid)(bjpPoints) )= 21)
				(
					BlackjackPlayer(playerid)(bjpFold) = true
				)
				return 1
			)
		)
	)
	else
	(
		RandomCard(playerid)
	)
	return 1
)

// Rozpoczêcie gry
stock StartBlackjack(gameid)
(
	BlackJack(gameid)(bjActivePlayerSlot) = 0
	BlackJack(gameid)(bjPhase) = BLACKJACK_PHASE_GAME
	for(i = 0 i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
		(
			RandomCard(BlackJack(gameid)(bjSlot)(i))
			RandomCard(BlackJack(gameid)(bjSlot)(i))
		)
	)
	for(i = 0 i ( 4 i++)
	(
		if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
		(
			hrp_TogglePlayerControllable(BlackJack(gameid)(bjSlot)(i), false)
			blackjack_LoadTextDraws(BlackJack(gameid)(bjSlot)(i))
			BlackjackShowTable(BlackJack(gameid)(bjSlot)(i))
		)
	)
	return 1
)

// Odœwie¿anie tabelki
stock BlackjackRefreshTable(gameid)
(
	for(i = 0 i ( 4)
	(
		if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
		(
			BlackjackHideTable(BlackJack(gameid)(bjSlot)(i))
			BlackjackShowTable(BlackJack(gameid)(bjSlot)(i))
		)
		i++
	)
	return 1
)

// Chowanie tabelki
stock BlackjackGameHideTable(gameid)
(
	for(i = 0 i ( 4)
	(
		if(BlackJack(gameid)(bjSlot)(i) != INVALID_PLAYER_ID)
		(
			BlackjackHideAll(BlackJack(gameid)(bjSlot)(i))
		)
		i++
	)
	return 1
)

stock BlackjackHideAll(playerid)
(
	gameid = BlackjackPlayer(playerid)(bjID)	

	PlayerTextDrawHide(playerid,TextDrawTitleP1(gameid))
	PlayerTextDrawHide(playerid,TextDrawTitleP2(gameid))
	PlayerTextDrawHide(playerid,TextDrawTitleP3(gameid))
	PlayerTextDrawHide(playerid,TextDrawTitleP4(gameid))
	PlayerTextDrawHide(playerid,TextDrawP1CardOne(gameid))
	PlayerTextDrawHide(playerid,TextDrawP1CardTwo(gameid))
	PlayerTextDrawHide(playerid,TextDrawP1CardThree(gameid))		
	PlayerTextDrawHide(playerid,TextDrawP1CardFour(gameid))
	PlayerTextDrawHide(playerid,TextDrawP1CardFive(gameid))
	PlayerTextDrawHide(playerid,TextDrawP1CardSix(gameid))
	PlayerTextDrawHide(playerid,TextDrawP2CardOne(gameid))
	PlayerTextDrawHide(playerid,TextDrawP2CardTwo(gameid))
	PlayerTextDrawHide(playerid,TextDrawP2CardThree(gameid))	
	PlayerTextDrawHide(playerid,TextDrawP2CardFour(gameid))
	PlayerTextDrawHide(playerid,TextDrawP2CardFive(gameid))	
	PlayerTextDrawHide(playerid,TextDrawP2CardSix(gameid))	
	PlayerTextDrawHide(playerid,TextDrawP3CardOne(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardTwo(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardThree(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardFour(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardFive(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardSix(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardOne(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardTwo(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardThree(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardFour(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardFive(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardSix(gameid))
	PlayerTextDrawHide(playerid,TextDrawActionCash(gameid))
)

stock BlackjackHideTable(playerid)
(
	gameid = BlackjackPlayer(playerid)(bjID)	

	PlayerTextDrawHide(playerid,TextDrawP1CardOne(gameid))
	PlayerTextDrawHide(playerid,TextDrawP1CardTwo(gameid))
	PlayerTextDrawHide(playerid,TextDrawP1CardThree(gameid))		
	PlayerTextDrawHide(playerid,TextDrawP1CardFour(gameid))
	PlayerTextDrawHide(playerid,TextDrawP1CardFive(gameid))
	PlayerTextDrawHide(playerid,TextDrawP1CardSix(gameid))
	PlayerTextDrawHide(playerid,TextDrawP2CardOne(gameid))
	PlayerTextDrawHide(playerid,TextDrawP2CardTwo(gameid))
	PlayerTextDrawHide(playerid,TextDrawP2CardThree(gameid))	
	PlayerTextDrawHide(playerid,TextDrawP2CardFour(gameid))
	PlayerTextDrawHide(playerid,TextDrawP2CardFive(gameid))	
	PlayerTextDrawHide(playerid,TextDrawP2CardSix(gameid))	
	PlayerTextDrawHide(playerid,TextDrawP3CardOne(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardTwo(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardThree(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardFour(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardFive(gameid))
	PlayerTextDrawHide(playerid,TextDrawP3CardSix(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardOne(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardTwo(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardThree(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardFour(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardFive(gameid))
	PlayerTextDrawHide(playerid,TextDrawP4CardSix(gameid))
)

stock BlackjackShowTable(playerid)
(
	string(128)
	
	gameid = BlackjackPlayer(playerid)(bjID)	

	PlayerTextDrawSetString(playerid,TextDrawTitleP1(gameid),PlayerName(BlackJack(gameid)(bjSlot)(0)))
	PlayerTextDrawShow(playerid,TextDrawTitleP1(gameid))
	
	PlayerTextDrawSetString(playerid,TextDrawP1CardOne(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(0))(cdName))
	PlayerTextDrawShow(playerid,TextDrawP1CardOne(gameid))
	
	PlayerTextDrawSetString(playerid,TextDrawP1CardTwo(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(1))(cdName))
	PlayerTextDrawShow(playerid,TextDrawP1CardTwo(gameid))
	if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(2) != 0)
	(
		PlayerTextDrawSetString(playerid,TextDrawP1CardThree(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(2))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP1CardThree(gameid))		
	)
	if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(3) != 0)
	(
		PlayerTextDrawSetString(playerid,TextDrawP1CardFour(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(3))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP1CardFour(gameid))
	)
	if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(4) != 0)
	(
		PlayerTextDrawSetString(playerid,TextDrawP1CardFive(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(4))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP1CardFive(gameid))
	)
	if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(5) != 0)
	(
		PlayerTextDrawSetString(playerid,TextDrawP1CardSix(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(0))(bjpCards)(5))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP1CardSix(gameid))
	)
	PlayerTextDrawSetString(playerid,TextDrawTitleP2(gameid), PlayerName(BlackJack(gameid)(bjSlot)(1)))
	PlayerTextDrawShow(playerid,TextDrawTitleP2(gameid))
	
	PlayerTextDrawSetString(playerid,TextDrawP2CardOne(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(0))(cdName))
	PlayerTextDrawShow(playerid,TextDrawP2CardOne(gameid))
	
	PlayerTextDrawSetString(playerid,TextDrawP2CardTwo(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(1))(cdName))
	PlayerTextDrawShow(playerid,TextDrawP2CardTwo(gameid))
	if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(2) != 0)
	(
		PlayerTextDrawSetString(playerid,TextDrawP2CardThree(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(2))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP2CardThree(gameid))	
	)
	if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(3) != 0)
	(
		PlayerTextDrawSetString(playerid,TextDrawP2CardFour(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(3))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP2CardFour(gameid))	
	)
	if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(4) != 0)
	(
		PlayerTextDrawSetString(playerid,TextDrawP2CardFive(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(4))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP2CardFive(gameid))	
	)
	if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(5) != 0)
	(
		PlayerTextDrawSetString(playerid,TextDrawP2CardSix(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(1))(bjpCards)(5))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP2CardSix(gameid))	
	)
	

	if(BlackJack(gameid)(bjActivePlayers) )= 3)
	(
		PlayerTextDrawSetString(playerid,TextDrawTitleP3(gameid), PlayerName(BlackJack(gameid)(bjSlot)(2)))
		PlayerTextDrawShow(playerid,TextDrawTitleP3(gameid))
		
		PlayerTextDrawSetString(playerid,TextDrawP3CardOne(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(0))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP3CardOne(gameid))
		
		PlayerTextDrawSetString(playerid,TextDrawP3CardTwo(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(1))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP3CardTwo(gameid))
		if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(2) != 0)
		(
		PlayerTextDrawSetString(playerid,TextDrawP3CardThree(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(2))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP3CardThree(gameid))
		)
		if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(3) != 0)
		(
		PlayerTextDrawSetString(playerid,TextDrawP3CardFour(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(3))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP3CardFour(gameid))
		)
		if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(4) != 0)
		(
		PlayerTextDrawSetString(playerid,TextDrawP3CardFive(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(4))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP3CardFive(gameid))
		)
		if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(5) != 0)
		(
		PlayerTextDrawSetString(playerid,TextDrawP3CardSix(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(2))(bjpCards)(5))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP3CardSix(gameid))
		)
	)
	if(BlackJack(gameid)(bjActivePlayers) == 4)
	(
		PlayerTextDrawSetString(playerid,TextDrawTitleP4(gameid), PlayerName(BlackJack(gameid)(bjSlot)(3)))
		PlayerTextDrawShow(playerid,TextDrawTitleP4(gameid))
		
		PlayerTextDrawSetString(playerid,TextDrawP4CardOne(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(0))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP4CardOne(gameid))
		
		PlayerTextDrawSetString(playerid,TextDrawP4CardTwo(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(1))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP4CardTwo(gameid))
		if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(2) != 0)
		(
		PlayerTextDrawSetString(playerid,TextDrawP4CardThree(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(2))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP4CardThree(gameid))
		)
		if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(3) != 0)
		(
		PlayerTextDrawSetString(playerid,TextDrawP4CardFour(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(3))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP4CardFour(gameid))
		)
		if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(4) != 0)
		(
		PlayerTextDrawSetString(playerid,TextDrawP4CardFive(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(4))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP4CardFive(gameid))
		)
		if(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(5) != 0)
		(
		PlayerTextDrawSetString(playerid,TextDrawP4CardSix(gameid), CardInfo(BlackjackPlayer(BlackJack(gameid)(bjSlot)(3))(bjpCards)(5))(cdName))
		PlayerTextDrawShow(playerid,TextDrawP4CardSix(gameid))
		)
	)
	
	format(string,sizeof(string),Stawka: ~b~~h~$%d, BlackJack(gameid)(bjMoney))
	PlayerTextDrawSetString(playerid,TextDrawActionCash(gameid), string)
	PlayerTextDrawShow(playerid,TextDrawActionCash(gameid))
	return 1
)
stock blackjack_LoadTextDraws(playerid)
(
		gameid = BlackjackPlayer(playerid)(bjID)
	
		//P1
		TextDrawTitleP1(gameid) = CreatePlayerTextDraw(playerid,216.000000, 116.000000, Gracz 1)
		PlayerTextDrawBackgroundColor(playerid,TextDrawTitleP1(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawTitleP1(gameid), 2)
		PlayerTextDrawLetterSize(playerid,TextDrawTitleP1(gameid), 0.449999, 1.899999)
		PlayerTextDrawColor(playerid,TextDrawTitleP1(gameid), -16776961)
		PlayerTextDrawSetOutline(playerid,TextDrawTitleP1(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawTitleP1(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawTitleP1(gameid), 1)
		
		//P2
		TextDrawTitleP2(gameid) = CreatePlayerTextDraw(playerid,216.000000, 193.000000, Gracz 2)
		PlayerTextDrawBackgroundColor(playerid,TextDrawTitleP2(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawTitleP2(gameid), 2)
		PlayerTextDrawLetterSize(playerid,TextDrawTitleP2(gameid), 0.449999, 1.899999)
		PlayerTextDrawColor(playerid,TextDrawTitleP2(gameid), -16776961)
		PlayerTextDrawSetOutline(playerid,TextDrawTitleP2(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawTitleP2(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawTitleP2(gameid), 1)
		
		//P3
		TextDrawTitleP3(gameid) = CreatePlayerTextDraw(playerid,216.000000, 270.000000, Gracz 3)
		PlayerTextDrawBackgroundColor(playerid,TextDrawTitleP3(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawTitleP3(gameid), 2)
		PlayerTextDrawLetterSize(playerid,TextDrawTitleP3(gameid), 0.449999, 1.899999)
		PlayerTextDrawColor(playerid,TextDrawTitleP3(gameid), -16776961)
		PlayerTextDrawSetOutline(playerid,TextDrawTitleP3(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawTitleP3(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawTitleP3(gameid), 1)
		
		//P4
		TextDrawTitleP4(gameid) = CreatePlayerTextDraw(playerid,216.000000, 347.000000, Gracz 4)
		PlayerTextDrawBackgroundColor(playerid,TextDrawTitleP4(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawTitleP4(gameid), 2)
		PlayerTextDrawLetterSize(playerid,TextDrawTitleP4(gameid), 0.449999, 1.899999)
		PlayerTextDrawColor(playerid,TextDrawTitleP4(gameid), -16776961)
		PlayerTextDrawSetOutline(playerid,TextDrawTitleP4(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawTitleP4(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawTitleP4(gameid), 1)
		
		//P1 - karta 1
		TextDrawP1CardOne(gameid) = CreatePlayerTextDraw(playerid,216.000000, 140.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP1CardOne(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP1CardOne(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP1CardOne(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP1CardOne(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP1CardOne(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP1CardOne(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP1CardOne(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP1CardOne(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP1CardOne(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP1CardOne(gameid), 36.000000, 43.000000)
		
		//P1 - karta 2
		TextDrawP1CardTwo(gameid) = CreatePlayerTextDraw(playerid,259.000000, 140.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP1CardTwo(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP1CardTwo(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP1CardTwo(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP1CardTwo(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP1CardTwo(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP1CardTwo(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP1CardTwo(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP1CardTwo(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP1CardTwo(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP1CardTwo(gameid), 36.000000, 43.000000)
		
		//P1 - karta 3
		TextDrawP1CardThree(gameid) = CreatePlayerTextDraw(playerid,302.000000, 140.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP1CardThree(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP1CardThree(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP1CardThree(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP1CardThree(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP1CardThree(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP1CardThree(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP1CardThree(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP1CardThree(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP1CardThree(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP1CardThree(gameid) , 36.000000, 43.000000)
		
		//P1 - karta 4
		TextDrawP1CardFour(gameid) = CreatePlayerTextDraw(playerid,345.000000, 140.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP1CardFour(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP1CardFour(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP1CardFour(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP1CardFour(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP1CardFour(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP1CardFour(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP1CardFour(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP1CardFour(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP1CardFour(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP1CardFour(gameid) , 36.000000, 43.000000)
		
		//P1 - karta 5
		TextDrawP1CardFive(gameid) = CreatePlayerTextDraw(playerid,388.000000, 140.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP1CardFive(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP1CardFive(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP1CardFive(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP1CardFive(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP1CardFive(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP1CardFive(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP1CardFive(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP1CardFive(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP1CardFive(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP1CardFive(gameid), 36.000000, 43.000000)
		
		//P1 - karta 6
		TextDrawP1CardSix(gameid) = CreatePlayerTextDraw(playerid,431.000000, 140.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP1CardSix(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP1CardSix(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP1CardSix(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP1CardSix(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP1CardSix(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP1CardSix(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP1CardSix(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP1CardSix(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP1CardSix(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP1CardSix(gameid) , 36.000000, 43.000000)
		
		//P2 - karta 1
		TextDrawP2CardOne(gameid) = CreatePlayerTextDraw(playerid,216.000000, 215.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP2CardOne(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP2CardOne(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP2CardOne(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP2CardOne(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP2CardOne(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP2CardOne(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP2CardOne(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP2CardOne(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP2CardOne(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP2CardOne(gameid), 36.000000, 43.000000)
		
		//P2 - karta 2
		TextDrawP2CardTwo(gameid) = CreatePlayerTextDraw(playerid,259.000000, 215.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP2CardTwo(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP2CardTwo(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP2CardTwo(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP2CardTwo(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP2CardTwo(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP2CardTwo(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP2CardTwo(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP2CardTwo(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP2CardTwo(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP2CardTwo(gameid), 36.000000, 43.000000)
		
		//P2 - karta 3
		TextDrawP2CardThree(gameid) = CreatePlayerTextDraw(playerid,302.000000, 215.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP2CardThree(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP2CardThree(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP2CardThree(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP2CardThree(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP2CardThree(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP2CardThree(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP2CardThree(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP2CardThree(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP2CardThree(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP2CardThree(gameid), 36.000000, 43.000000)
		
		//P2 - karta 4
		TextDrawP2CardFour(gameid) = CreatePlayerTextDraw(playerid,345.000000, 215.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP2CardFour(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP2CardFour(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP2CardFour(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP2CardFour(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP2CardFour(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP2CardFour(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP2CardFour(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP2CardFour(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP2CardFour(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP2CardFour(gameid) , 36.000000, 43.000000)
		
		//P2 - karta 5
		TextDrawP2CardFive(gameid) = CreatePlayerTextDraw(playerid,388.000000, 215.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP2CardFive(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP2CardFive(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP2CardFive(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP2CardFive(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP2CardFive(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP2CardFive(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP2CardFive(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP2CardFive(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP2CardFive(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP2CardFive(gameid), 36.000000, 43.000000)
		
		//P2 - karta 6
		TextDrawP2CardSix(gameid) = CreatePlayerTextDraw(playerid,431.000000, 215.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP2CardSix(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP2CardSix(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP2CardSix(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP2CardSix(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP2CardSix(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP2CardSix(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP2CardSix(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP2CardSix(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP2CardSix(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP2CardSix(gameid) , 36.000000, 43.000000)
		
		//P3 - karta 1
		TextDrawP3CardOne(gameid) = CreatePlayerTextDraw(playerid,216.000000, 294.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP3CardOne(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP3CardOne(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP3CardOne(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP3CardOne(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP3CardOne(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP3CardOne(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP3CardOne(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP3CardOne(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP3CardOne(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP3CardOne(gameid), 36.000000, 43.000000)
		
		//P3 - karta 2
		TextDrawP3CardTwo(gameid) = CreatePlayerTextDraw(playerid,259.000000, 294.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP3CardTwo(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP3CardTwo(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP3CardTwo(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP3CardTwo(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP3CardTwo(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP3CardTwo(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP3CardTwo(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP3CardTwo(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP3CardTwo(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP3CardTwo(gameid), 36.000000, 43.000000)
		
		//P3 - karta 3
		TextDrawP3CardThree(gameid) = CreatePlayerTextDraw(playerid,302.000000, 294.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP3CardThree(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP3CardThree(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP3CardThree(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP3CardThree(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP3CardThree(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP3CardThree(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP3CardThree(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP3CardThree(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP3CardThree(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP3CardThree(gameid) , 36.000000, 43.000000)
		
		//P3 - karta 4
		TextDrawP3CardFour(gameid) = CreatePlayerTextDraw(playerid,345.000000, 294.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP3CardFour(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP3CardFour(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP3CardFour(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP3CardFour(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP3CardFour(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP3CardFour(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP3CardFour(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP3CardFour(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP3CardFour(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP3CardFour(gameid) , 36.000000, 43.000000)
		
		//P3 - karta 5
		TextDrawP3CardFive(gameid) = CreatePlayerTextDraw(playerid,388.000000, 294.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP3CardFive(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP3CardFive(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP3CardFive(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP3CardFive(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP3CardFive(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP3CardFive(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP3CardFive(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP3CardFive(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP3CardFive(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP3CardFive(gameid), 36.000000, 43.000000)
		
		//P3 - karta 6
		TextDrawP3CardSix(gameid) = CreatePlayerTextDraw(playerid,431.000000, 294.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP3CardSix(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP3CardSix(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP3CardSix(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP3CardSix(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP3CardSix(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP3CardSix(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP3CardSix(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP3CardSix(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP3CardSix(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP3CardSix(gameid) , 36.000000, 43.000000)
		
		//P4 - karta 1
		TextDrawP4CardOne(gameid) = CreatePlayerTextDraw(playerid,216.000000, 371.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP4CardOne(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP4CardOne(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP4CardOne(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP4CardOne(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP4CardOne(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP4CardOne(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP4CardOne(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP4CardOne(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP4CardOne(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP4CardOne(gameid), 36.000000, 43.000000)
		
		//P4 - karta 2
		TextDrawP4CardTwo(gameid) = CreatePlayerTextDraw(playerid,259.000000, 371.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP4CardTwo(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP4CardTwo(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP4CardTwo(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP4CardTwo(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP4CardTwo(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP4CardTwo(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP4CardTwo(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP4CardTwo(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP4CardTwo(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP4CardTwo(gameid), 36.000000, 43.000000)
		
		//P4 - karta 3
		TextDrawP4CardThree(gameid) = CreatePlayerTextDraw(playerid,302.000000, 371.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP4CardThree(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP4CardThree(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP4CardThree(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP4CardThree(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP4CardThree(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP4CardThree(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP4CardThree(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP4CardThree(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP4CardThree(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP4CardThree(gameid) , 36.000000, 43.000000)
		
		//P4 - karta 4
		TextDrawP4CardFour(gameid) = CreatePlayerTextDraw(playerid,345.000000, 371.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP4CardFour(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP4CardFour(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP4CardFour(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP4CardFour(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP4CardFour(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP4CardFour(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP4CardFour(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP4CardFour(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP4CardFour(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP4CardFour(gameid) , 36.000000, 43.000000)
		
		//P4 - karta 5
		TextDrawP4CardFive(gameid) = CreatePlayerTextDraw(playerid,388.000000, 371.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP4CardFive(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawP4CardFive(gameid), 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP4CardFive(gameid), 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP4CardFive(gameid), -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP4CardFive(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP4CardFive(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP4CardFive(gameid), 1)
		PlayerTextDrawUseBox(playerid,TextDrawP4CardFive(gameid), 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP4CardFive(gameid), 255)
		PlayerTextDrawTextSize(playerid,TextDrawP4CardFive(gameid), 36.000000, 43.000000)
		
		//P4 - karta 6
		TextDrawP4CardSix(gameid) = CreatePlayerTextDraw(playerid,431.000000, 371.000000, ld_card:cdback)
		PlayerTextDrawBackgroundColor(playerid,TextDrawP4CardSix(gameid) , 255)
		PlayerTextDrawFont(playerid,TextDrawP4CardSix(gameid) , 4)
		PlayerTextDrawLetterSize(playerid,TextDrawP4CardSix(gameid) , 0.430000, 0.199999)
		PlayerTextDrawColor(playerid,TextDrawP4CardSix(gameid) , -1)
		PlayerTextDrawSetOutline(playerid,TextDrawP4CardSix(gameid) , 0)
		PlayerTextDrawSetProportional(playerid,TextDrawP4CardSix(gameid) , 1)
		PlayerTextDrawSetShadow(playerid,TextDrawP4CardSix(gameid) , 1)
		PlayerTextDrawUseBox(playerid,TextDrawP4CardSix(gameid) , 1)
		PlayerTextDrawBoxColor(playerid,TextDrawP4CardSix(gameid) , 255)
		PlayerTextDrawTextSize(playerid,TextDrawP4CardSix(gameid) , 36.000000, 43.000000)
		
		//Stawka na stole
		TextDrawActionCash(gameid) = CreatePlayerTextDraw(playerid,80.000000, 136.000000, Stawka: ~b~~h~$0)
		PlayerTextDrawBackgroundColor(playerid,TextDrawActionCash(gameid), 255)
		PlayerTextDrawFont(playerid,TextDrawActionCash(gameid), 3)
		PlayerTextDrawLetterSize(playerid,TextDrawActionCash(gameid), 0.539999, 1.899999)
		PlayerTextDrawColor(playerid,TextDrawActionCash(gameid), 16711935)
		PlayerTextDrawSetOutline(playerid,TextDrawActionCash(gameid), 0)
		PlayerTextDrawSetProportional(playerid,TextDrawActionCash(gameid), 1)
		PlayerTextDrawSetShadow(playerid,TextDrawActionCash(gameid), 1)

)

stock blackjack_DestroyTextDraws(playerid)
(
	gameid = BlackjackPlayer(playerid)(bjID)
	
	PlayerTextDrawDestroy(playerid,TextDrawTitleP1(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawTitleP2(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawTitleP3(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawTitleP4(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP1CardOne(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP1CardTwo(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP1CardThree(gameid))		
	PlayerTextDrawDestroy(playerid,TextDrawP1CardFour(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP1CardFive(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP1CardSix(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP2CardOne(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP2CardTwo(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP2CardThree(gameid))	
	PlayerTextDrawDestroy(playerid,TextDrawP2CardFour(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP2CardFive(gameid))	
	PlayerTextDrawDestroy(playerid,TextDrawP2CardSix(gameid))	
	PlayerTextDrawDestroy(playerid,TextDrawP3CardOne(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP3CardTwo(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP3CardThree(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP3CardFour(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP3CardFive(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP3CardSix(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP4CardOne(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP4CardTwo(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP4CardThree(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP4CardFour(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP4CardFive(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawP4CardSix(gameid))
	PlayerTextDrawDestroy(playerid,TextDrawActionCash(gameid))
)