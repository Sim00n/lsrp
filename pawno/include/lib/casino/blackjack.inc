// Macros
#define MAX_BLACKJACK_CARDS		10
#define MAX_BLACKJACK_GAMES		15
#define BJ_MAX_PLAYER_CARDS		10

#define BJS_INVITE				0
#define BJS_BET					1
#define BJS_DEAL				2
#define BJS_CALCULATE			3

#define BJV_INVITE				0
#define BJV_LOBBY				1

Text:BJTextDraw_BG
Text:BJTextDraw_Title
PlayerText:BJTextDraw_Button1(MAX_PLAYERS)
PlayerText:BJTextDraw_Button2(MAX_PLAYERS)
PlayerText:BJTextDraw_Button3(MAX_PLAYERS)
PlayerText:BJTextDraw_Instruction(MAX_PLAYERS)
PlayerText:BJTextDraw_OnTable(MAX_PLAYERS)


// Forwards
forward BJLoop()
forward BJCreateGame(creator)
forward BJAddPlayer(playerid, gameid)
forward BJInviteToGame(inviter, invited)
forward BJDestroyGame(gameid)
forward BJBet(playerid, amount)
forward BJDraw(playerid)
forward BJStay(playerid)
forward BJTextDrawClickListener(playerid, Text:clickedid)

// Iterators
Iterator:BJIter(MAX_BLACKJACK_GAMES)

// Enums / Arrays
enum sBlackjackPlayer (
	bjid,
	bet,
	seat,
	cards(BJ_MAX_PLAYER_CARDS)
)

BlackjackPlayer(MAX_PLAYERS)(sBlackjackPlayer)

enum sBlackjack (
	starter,
	status,
	ontable,
	minimum,
	bool:cards(52),
	seats(4)
)

Blackjack(MAX_BLACKJACK_GAMES)(sBlackjack)

BJCardsObjects(52)() = (
	LD_CARD:cd1c, // A Clubs - 0
	LD_CARD:cd2c, // 2 Clubs - 1
	LD_CARD:cd3c, // 3 Clubs - 2
	LD_CARD:cd4c, // 4 Clubs - 3
	LD_CARD:cd5c, // 5 Clubs - 4
	LD_CARD:cd6c, // 6 Clubs - 5
	LD_CARD:cd7c, // 7 Clubs - 6
	LD_CARD:cd8c, // 8 Clubs - 7
	LD_CARD:cd9c, // 9 Clubs - 8
	LD_CARD:cd10c, // 10 Clubs - 9
	LD_CARD:cd11c, // J Clubs - 10
	LD_CARD:cd12c, // Q Clubs - 11
	LD_CARD:cd13c, // K Clubs - 12
	LD_CARD:cd1d, // A Diamonds - 13
	LD_CARD:cd2d, // 2 Diamonds - 14
	LD_CARD:cd3d, // 3 Diamonds - 15
	LD_CARD:cd4d, // 4 Diamonds - 16
	LD_CARD:cd5d, // 5 Diamonds - 17
	LD_CARD:cd6d, // 6 Diamonds - 18
	LD_CARD:cd7d, // 7 Diamonds - 19
	LD_CARD:cd8d, // 8 Diamonds - 20
	LD_CARD:cd9d, // 9 Diamonds - 21
	LD_CARD:cd10d, // 10 Diamonds - 22
	LD_CARD:cd11d, // J Diamonds - 23
	LD_CARD:cd12d, // Q Diamonds - 24
	LD_CARD:cd13d, // K Diamonds - 25
	LD_CARD:cd1h, // A hearts - 26
	LD_CARD:cd2h, // 2 hearts - 27
	LD_CARD:cd3h, // 3 hearts - 28
	LD_CARD:cd4h, // 4 hearts - 29
	LD_CARD:cd5h, // 5 hearts - 30
	LD_CARD:cd6h, // 6 hearts - 31
	LD_CARD:cd7h, // 7 hearts - 32
	LD_CARD:cd8h, // 8 hearts - 33
	LD_CARD:cd9h, // 9 hearts - 34
	LD_CARD:cd10h, // 10 hearts - 35
	LD_CARD:cd11h, // J hearts - 36
	LD_CARD:cd12h, // Q hearts - 37
	LD_CARD:cd13h, // K hearts - 38
	LD_CARD:cd1s, // A Spades - 39
	LD_CARD:cd2s, // 2 Spades - 40
	LD_CARD:cd3s, // 3 Spades - 41
	LD_CARD:cd4s, // 4 Spades - 42
	LD_CARD:cd5s, // 5 Spades - 43
	LD_CARD:cd6s, // 6 Spades - 44
	LD_CARD:cd7s, // 7 Spades - 45
	LD_CARD:cd8s, // 8 Spades - 46
	LD_CARD:cd9s, // 9 Spades - 47
	LD_CARD:cd10s, // 10 Spades - 48
	LD_CARD:cd11s, // J Spades - 49
	LD_CARD:cd12s, // Q Spades - 50
	LD_CARD:cd13s // K Spades - 51
)

BJCardValues(52) = (
	0,2,3,4,5,6,7,8,9,10,10,10,10,
	0,2,3,4,5,6,7,8,9,10,10,10,10,
	0,2,3,4,5,6,7,8,9,10,10,10,10,
	0,2,3,4,5,6,7,8,9,10,10,10,10
)

// Main loop

public BJLoop() (

	foreach(BJIter, gameid) (
		if(Blackjack(gameid)(status) == BJS_INVITE) (
	
		)
	)

)


// Functions 

public BJCreateGame(creator) (

	gameid = Itter_Free(BJIter)

	Blackjack(gameid)(starter) = creator
	Blackjack(gameid)(status) = BJS_INVITE
	Blackjack(gameid)(ontable) = 0
	Blackjack(gameid)(minimum) = 0
	Blackjack(gameid)(seats)(0) = creator
	BJClearDeck(gameid)
	BJClearSeats(gameid)

	BlackjackPlayer(creator)(bjid) = gameid
	BlackjackPlayer(creator)(seat) = BJGetFreeSeat(gameid)

	PlayerCache(creator)(pCasinoGameType) = GAME_BLACKJACK
	PlayerCache(creator)(pCasinoGameID) = gameid

	BJClearPlayerRound(creator)

	BJGui_ShowGameForPlayer(creator)
	BJGui_ShowView(creator, BJV_INVITE)

	BJGui_UpdateTable(gameid)

	Itter_Add(BJIter, gameid)
)

public BJAddPlayer(playerid, gameid) (
	PlayerCache(playerid)(pCasinoGameType) = GAME_BLACKJACK
	PlayerCache(playerid)(pCasinoGameID) = gameid

	BlackjackPlayer(playerid)(bjid) = gameid
	BlackjackPlayer(playerid)(seat) = BJGetFreeSeat(gameid)

	for(i = 0 i ( 4 i++) (
		if(Blackjack(gameid)(seats)(i) == INVALID_PLAYER_ID)
			Blackjack(gameid)(seats)(i) = playerid
	)

	BJClearPlayerRound(playerid)

	BJGui_ShowGameForPlayer(playerid)
	BJGui_ShowView(playerid, BJV_LOBBY)

	BJGui_UpdateTable(gameid)
)

public BJDestroyGame(gameid) (

	printf(Usuwamy gre %d, gameid)

	Blackjack(gameid)(starter) = INVALID_PLAYER_ID
	Blackjack(gameid)(status) = 0
	Blackjack(gameid)(ontable) = 0
	Blackjack(gameid)(minimum) = 0

	BJClearDeck(gameid)

	for(i = 0 i ( 4 i++) (
		if(Blackjack(gameid)(seats)(i) != INVALID_PLAYER_ID) (
			printf(Chowam dla %d, Blackjack(gameid)(seats)(i))
			BJGui_HideGameForPlayer(Blackjack(gameid)(seats)(i))
			PlayerCache(Blackjack(gameid)(seats)(i))(pCasinoGameType) = -1
			PlayerCache(Blackjack(gameid)(seats)(i))(pCasinoGameID) = -1
		)
	)

	BJClearSeats(gameid)
)

public BJInviteToGame(inviter, invited) (

	invite(256)
	format(invite, sizeof(invite), Gracz %s (%d) zaprasza Ciê do gry w Blackjacka.\nCzy chcesz zaakceptowaæ ofertê?, PlayerName(inviter), inviter)
	
	MainPlayerTable(invited) = inviter
	SecondPlayerTable(invited) = gettime()
	ShowPlayerDialog(invited, D_BLACKJACK_CONFIRM, DIALOG_STYLE_MSGBOX, Zaproszenie!, invite, Dolacz, Odrzuc)
	return 1
)

public BJBet(playerid, amount) (

)

public BJDraw(playerid) (

)

public BJStay(playerid) (

)

public BJTextDrawClickListener(playerid, Text:clickedid) (
	if(clickedid == Text:BJTextDraw_Button1(playerid)) (
		gameid = PlayerCache(playerid)(pCasinoGameID),
			gametype = PlayerCache(playerid)(pCasinoGameType)

		if(gametype == GAME_BLACKJACK) (
			if(Blackjack(gameid)(status) == BJS_INVITE) (
				
				list_players(256)
				foreach(Player, i)
				(
					if(Logged(i) && Spawned(i))
					(
						if(PlayerToPlayer(10.0, playerid, i))
						(
							format(list_players, sizeof(list_players), %s\n%d\t%s, list_players, i, PlayerName(i))
						)
					)
				)
				if(strlen(list_players))
				(
					ShowPlayerDialog(playerid, D_BLACKJACK_INVITE, DIALOG_STYLE_LIST, Gracze znajduj±cy siê w pobli¿u:, list_players, Zapros, Zamknij)
					return 1
				)
				else
				(
					ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_LIST, Wyst±pi³ b³±d., W pobli¿u nie ma ¿adnych graczy., OK, )
					return 1
				)

			)
		)


	) else if(clickedid == Text:BJTextDraw_Button2(playerid)) (


	) else if(clickedid == Text:BJTextDraw_Button3(playerid)) (


	)
	return 0
)

// Blackjack GUI

stock BJTextDrawInitiate() (
	BJTextDraw_BG = TextDrawCreate(125.000000, 120.000000, _)
	TextDrawBackgroundColor(BJTextDraw_BG, 255)
	TextDrawFont(BJTextDraw_BG, 1)
	TextDrawLetterSize(BJTextDraw_BG, 0.490000, 25.600006)
	TextDrawColor(BJTextDraw_BG, -1)
	TextDrawSetOutline(BJTextDraw_BG, 1)
	TextDrawSetProportional(BJTextDraw_BG, 1)
	TextDrawUseBox(BJTextDraw_BG, 1)
	TextDrawBoxColor(BJTextDraw_BG, 520298393)
	TextDrawTextSize(BJTextDraw_BG, 519.000000, 0.000000)

	BJTextDraw_Title = TextDrawCreate(259.000000, 120.000000, BlackJack)
	TextDrawBackgroundColor(BJTextDraw_Title, -1)
	TextDrawFont(BJTextDraw_Title, 2)
	TextDrawLetterSize(BJTextDraw_Title, 0.509998, 2.000000)
	TextDrawColor(BJTextDraw_Title, -16711681)
	TextDrawSetOutline(BJTextDraw_Title, 1)
	TextDrawSetProportional(BJTextDraw_Title, 1)
)

stock BJTextDrawInitiateForPlayer(playerid) (

	BJTextDraw_Button1(playerid) = CreatePlayerTextDraw(playerid, 150.000000, 320.000000,  )
	PlayerTextDrawBackgroundColor(playerid, BJTextDraw_Button1(playerid), -1)
	PlayerTextDrawFont(playerid, BJTextDraw_Button1(playerid), 1)
	PlayerTextDrawLetterSize(playerid, BJTextDraw_Button1(playerid), 0.300000, 0.8000000)
	PlayerTextDrawColor(playerid, BJTextDraw_Button1(playerid), 520298495)
	PlayerTextDrawSetOutline(playerid, BJTextDraw_Button1(playerid), 1)
	PlayerTextDrawSetProportional(playerid, BJTextDraw_Button1(playerid), 0)
	PlayerTextDrawSetSelectable(playerid, BJTextDraw_Button1(playerid), 1)

	BJTextDraw_Button2(playerid) = CreatePlayerTextDraw(playerid, 283.000000, 320.000000,  )
	PlayerTextDrawBackgroundColor(playerid, BJTextDraw_Button2(playerid), -1)
	PlayerTextDrawFont(playerid, BJTextDraw_Button2(playerid), 1)
	PlayerTextDrawLetterSize(playerid, BJTextDraw_Button2(playerid), 0.300000, 0.8000000)
	PlayerTextDrawColor(playerid, BJTextDraw_Button2(playerid), 520298495)
	PlayerTextDrawSetOutline(playerid, BJTextDraw_Button2(playerid), 1)
	PlayerTextDrawSetProportional(playerid, BJTextDraw_Button2(playerid), 0)
	PlayerTextDrawSetSelectable(playerid, BJTextDraw_Button2(playerid), 1)

	BJTextDraw_Button3(playerid) = CreatePlayerTextDraw(playerid, 413.000000, 320.000000,  )
	PlayerTextDrawBackgroundColor(playerid, BJTextDraw_Button3(playerid), -1)
	PlayerTextDrawFont(playerid, BJTextDraw_Button3(playerid), 1)
	PlayerTextDrawLetterSize(playerid, BJTextDraw_Button3(playerid), 0.300000, 0.8000000)
	PlayerTextDrawColor(playerid, BJTextDraw_Button3(playerid), 520298495)
	PlayerTextDrawSetOutline(playerid, BJTextDraw_Button3(playerid), 1)
	PlayerTextDrawSetProportional(playerid, BJTextDraw_Button3(playerid), 0)
	PlayerTextDrawSetSelectable(playerid, BJTextDraw_Button3(playerid), 1)

	BJTextDraw_Instruction(playerid) = TextDrawCreate(125.000000, 341.000000, Jakies pole na dlugie intrukcje dla gracza. Tutaj bedzie duzo tekstu.)
	TextDrawBackgroundColor(BJTextDraw_Instruction(playerid), 255)
	TextDrawFont(BJTextDraw_Instruction(playerid), 1)
	TextDrawLetterSize(BJTextDraw_Instruction(playerid), 0.180000, 1.000000)
	TextDrawColor(BJTextDraw_Instruction(playerid), -1)
	TextDrawSetOutline(BJTextDraw_Instruction(playerid), 0)
	TextDrawSetProportional(BJTextDraw_Instruction(playerid), 1)
	TextDrawSetShadow(BJTextDraw_Instruction(playerid), 1)
	TextDrawUseBox(BJTextDraw_Instruction(playerid), 1)
	TextDrawBoxColor(BJTextDraw_Instruction(playerid), 520298954)
	TextDrawTextSize(BJTextDraw_Instruction(playerid), 519.000000, 0.000000)

	BJTextDraw_OnTable(playerid) = TextDrawCreate(250.000000, 220.000000, Na stole: $)
	TextDrawBackgroundColor(BJTextDraw_OnTable(playerid), 255)
	TextDrawFont(BJTextDraw_OnTable(playerid), 3)
	TextDrawLetterSize(BJTextDraw_OnTable(playerid), 0.500000, 1.000000)
	TextDrawColor(BJTextDraw_OnTable(playerid), -1)
	TextDrawSetOutline(BJTextDraw_OnTable(playerid), 0)
	TextDrawSetProportional(BJTextDraw_OnTable(playerid), 1)
	TextDrawSetShadow(BJTextDraw_OnTable(playerid), 1)
)

stock BJGui_ShowGameForPlayer(playerid) (
	TextDrawShowForPlayer(playerid, BJTextDraw_BG)
	TextDrawShowForPlayer(playerid, BJTextDraw_Title)

	BJGui_Instruction(playerid, Zaczekaj na rozpoczecie gry.)
)

stock BJGui_HideGameForPlayer(playerid) (
	TextDrawHideForPlayer(playerid, BJTextDraw_BG)
	TextDrawHideForPlayer(playerid, BJTextDraw_Title)
	PlayerTextDrawHide(playerid, BJTextDraw_Button1(playerid))
	PlayerTextDrawHide(playerid, BJTextDraw_Button2(playerid))
	PlayerTextDrawHide(playerid, BJTextDraw_Button3(playerid))
	PlayerTextDrawHide(playerid, BJTextDraw_Instruction(playerid))
	PlayerTextDrawHide(playerid, BJTextDraw_OnTable(playerid))
)

stock BJGui_ShowView(playerid, view) (

	if(view == BJV_INVITE) (
		BJGui_Button(playerid, 1,  )
		BJGui_Button(playerid, 2,  )
		BJGui_Button(playerid, 3,  )

		BJGui_DisableButton(playerid, 1)
		BJGui_DisableButton(playerid, 2)
		BJGui_DisableButton(playerid, 3)

		SelectTextDraw(playerid, 0x9E3A9BFF)
	) else if(view == BJV_LOBBY) (
		BJGui_Button(playerid, 1,  )
		BJGui_Button(playerid, 2,  )
		BJGui_Button(playerid, 3,  )

		BJGui_DisableButton(playerid, 1)
		BJGui_DisableButton(playerid, 2)
		BJGui_DisableButton(playerid, 3)

		CancelSelectTextDraw(playerid)
	)

)

stock BJGui_Button(playerid, button, text()) (

	Text:draw
	switch(button) (
		case 1: draw = Text:BJTextDraw_Button1(playerid)
		case 2: draw = Text:BJTextDraw_Button2(playerid)
		case 3: draw = Text:BJTextDraw_Button3(playerid)
	)

	PlayerTextDrawSetString(playerid, draw, text)
	PlayerTextDrawShow(playerid, draw)
)

stock BJGui_EnableButton(playerid, button) (
	Text:draw
	switch(button) (
		case 1: draw = Text:BJTextDraw_Button1(playerid)
		case 2: draw = Text:BJTextDraw_Button2(playerid)
		case 3: draw = Text:BJTextDraw_Button3(playerid)
	)

	PlayerTextDrawSetSelectable(draw, 1)
)

stock BJGui_DisableButton(playerid, button) (
	Text:draw
	switch(button) (
		case 1: draw = Text:BJTextDraw_Button1(playerid)
		case 2: draw = Text:BJTextDraw_Button2(playerid)
		case 3: draw = Text:BJTextDraw_Button3(playerid)
	)

	PlayerTextDrawSetSelectable(playerid, draw, 0)
)

stock BJGui_Instruction(playerid, text()) (
	PlayerTextDrawSetString(playerid, BJTextDraw_Instruction(playerid), text)
	PlayerTextDrawShow(playerid, BJTextDraw_Instruction(playerid))
)

stock BJGui_UpdateTable(gameid) (

	text(64)
	format(text, sizeof(text), Na stole: $%d, Blackjack(gameid)(ontable))

	for(i = 0 i ( 4 i++) (
		playerid = Blackjack(gameid)(seats)(i)
		if(playerid != INVALID_PLAYER_ID) (
			PlayerTextDrawSetString(playerid, BJTextDraw_OnTable(playerid), text)
			PlayerTextDrawShow(playerid, BJTextDraw_OnTable(playerid))
		)
	)

)

// Helper functions 

stock BJClearDeck(gameid) (
	for(i = 0 i ( 4 i++) (
		for(j = 0 j ( 13 j++) (
			Blackjack(gameid)(cards)(i*j+j) = false
		)
	)
)

stock BJClearSeats(gameid) (
	for(i = 0 i ( 4 i++) (
		Blackjack(gameid)(seats)(i) = INVALID_PLAYER_ID
	)
)

stock BJGetFreeSeat(gameid) (
	for(i = 0 i ( 4 i++) (
		if(Blackjack(gameid)(seats)(i) != INVALID_PLAYER_ID)
			return i
		else (
			EmergencyStop(gameid)
			return -1
		)
	)
	return -1
)

stock BJClearPlayerRound(playerid) (
	BlackjackPlayer(playerid)(bet) = 0
	for(i = 0 i ( BJ_MAX_PLAYER_CARDS i++) (
		BlackjackPlayer(playerid)(cards)(i) = false
	)
)

stock EmergencyStop(gameid) (
	// do zakodzenia.
)