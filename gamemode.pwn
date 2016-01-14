/*
	Autorem zawartości tego pliku jest Mario.	
	Wszelkie prawa zastrzeżone.
	
	Czas prac nad skryptem waha się między 26 maja 2011 roku a 6 lipca 2012.
	Za optymalizację kodu oraz jego ułożenia w całości odpowiedzialny jest autor skryptu.
	
	Gamemode był tworzony z myślą o projekcie HarvestGames (www.harvestgames.pl).
	Pomysłodawcami dla poszczególnych części skryptu były przypadkowe osoby oraz sam autor.
	
	Autor zastrzeża sobie prawo do rozpowszechniania zawartości oraz samego pliku.
	Od dnia 2 lutego 2012 roku skrypt był medyfikowany na potrzeby serwera Los Santos Role Play (www.ls-rp.net).
*/

#include (a_samp)
#include (a_actor)
#include (mysql)
#include (sscanf2)		
#include (zcmd)
#include (md5)
#include (streamer)
#include (foreach)
#include (YSI\y_va)
#include (YSI\y_timers)
#include (speedcap)		 
#include (fly)			
#include (dive)
#include (crashdetect)


#include (lib\DB)				// Konfiguracja DB - NIE OTWIERAĆ NA STRUMIENIU !!!!!
#include (lib\config)			// Definicje, makra, zmienne, enumy, tablice, etc.
#include (lib\traffic)			// Główne funkcje zwi±zane z graczem (OnPlayerConnect/Disconnect etc.)
#include (lib\ducktape)			// Ducktape z kolejnością funkcji zwracających Float - nie wiem - nie pytaj - nie znam pawn
#include (lib\states)			// Funkcje związane z różnymi stanami jak OnPlayerStateChange, OnPlayerKeyStateChange, OnPlayerTakeDamage, etc.
#include (lib\vehicle)			// Funcke związane z pojazdami
#include (lib\games\surf)		// funkcje surferów
#include (lib\tasks)			// Timery
#include (lib\chat)				// Funkcje związane z odpowiednim przekierowaniem czatu
#include (lib\admincmd)			// Komendy adminów/supporterów
#include (lib\chatcmd)			// Komendy chatowe typu /k, /c, /l, etc.
#include (lib\cmd)				// Zwykłe komendy graczy
#include (lib\penalties)		// Funkcje związane z karami
#include (lib\hrpfunction)		// Funkcje hrp_* - funkcje zastępujące natywne ze względu na np. antycheat
#include (lib\player)			// Funkcje związane z graczem typu zgarnianie koordów, etc.
#include (lib\weapon)			// Funkcje broni
#include (lib\group)			// Funkcje grup
#include (lib\item)				// Funkcje przedmiotów
#include (lib\item_use)			// OnPlayerUseItem   (osobno od przedmiotów ponieważ dłuuuuuuuuuga funkcja)
#include (lib\log)				// Funkcje logów
#include (lib\utils)			// Funkcje dodatkowe, małe pierdoły - nie pasujące nigdzie indziej
#include (lib\object)			// Funkcje obiektów
#include (lib\dialog)			// OnDialogResponse
#include (lib\gangzone)			// Funkcje GangZone
#include (lib\photoradar)		// Funkcje fotoradarów
#include (lib\busstop)			// Funkcje przystanków autobusowych
#include (lib\gym)				// Funkcje pakierni
#include (lib\booth)			// Funkcje bazarów (oferowanie na 0)
#include (lib\gasstation)		// Funkcje stacji benzynowych (dosłownie kod bazarów)
#include (lib\offer)			// Funkcje oferowania (OnPlayer(Send/Accept)Offcer, etc.)
#include (lib\checkpoint)		// Funkcje checkpointów (zwykłych i wyścigowych)
#include (lib\door)				// Funkcje drzwi
#include (lib\product)			// Funkcje produktów i ))paczek((
#include (lib\3dtext)			// Funkcje 3dtextów
#include (lib\textdraw)			// Funkcje textdrawów (klik na niego)
#include (lib\group_ann)		// Funkcje do informacji grupowych
#include (lib\lspd)				// Funkcje dla szukajki LSPD
#include (lib\phone)			// Funkcje dla budek telefonicznych
#include (lib\wbc)				// Funkcje dla WBC
#include (lib\games\basket)		// Funkcje dla koszykówki
#include (lib\games\slots)		//jednoreki bandyta
#include (lib\plants)			// Krzaki
#include (lib\jobs\truckers)	//funkcje trackersów
#include (lib\jobs\airport)		//funkcje portu lotniczego
#include (lib\item_interface_new)		//nowe gui sys. przedmiotów - do wyjebania później, niewątpliwie
#include (lib\gangzone_new)		// nowe strefy
#include (lib\farming.inc)			// Farmienie, rośliny i inne pierdoły
#include (lib\fps.inc)				// pierwsza osoba
#include (lib\bots.inc)					// Boty
#include (lib\lspad\lspad)		// Funkcje LSPada*/
#include (lib\launcher)					// Funkcje launchera LS-RP
#include (lib\jobs\port)					// Praca dorywcza w porcie
#include (lib\jobs\prison)				// Praca dorywcza w areszcie/wiezieniu
//#include (lib\games\poker)			// poker
#include (lib\games\blackjack)	// blackjack
//#include (modelsizes)				// model sizes samp
//#include (lib\games\billiard)		// bilard
#include (lib\cooking)				// gotowanie narkotyków

main()
(
	print(Oprogramowanie SERVER_NAME zostało załadowane pomyślnie.\n\n----------\nAutorem oprogramowania jest Mario, wszelkie prawa zastrzeżone\n----------)
)

public OnGameModeInit()
(
	year, month, day, hour, minute, second

	getdate(year, month, day)
	gettime(hour, minute, second)

	if ( fexist(debug-true.txt) )
	(
		DEBUG_MODE	=	true
		SKIP_OBJECTS = 	true
	)

 	mysql_init(LOG_ALL)
	print((mysql) Trwa łączenie z bazą danych...)
	if(mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB))
	(
	 	print((mysql) Połączenie z bazą danych powiodło się.)
		
		mysql_query(UPDATE hrp_zones SET zone_package = 1)

	  	SetGameModeText(VERSION)

	 	// Wczytywanie
	 	LoadSettings()

		LoadGroups()
		LoadBooths()
		LoadPetrols()
	 	LoadVehicles()
	 	LoadPickups()
	 	LoadDoors()

	 	LoadAllProducts()
		if(!SKIP_OBJECTS)
		(
			LoadAllObjects()
			LoadCorpseObjects()
	 		Load3DTextLabels()
		)

	 	LoadAnims()
		LoadLimitedPackages()
	 	LoadPackages()
	 	LoadBusStops()
		LoadGangZones()
		
		LoadPhones()
		
		LoadHomephones()	
		LoadNewsboxes()	
		LoadSlotsAutomats()
		LoadPlants()
		
		LoadZones()		
		LoadSeeds()
		
		checkDoorsActivity()
		
		checkVehiclesActivity()
	)
	else
	(
	 	print((mysql) Połączenie z bazą nie było możliwe - sprawdź konfigurację mySQL.)
	 	SetGameModeText(GAMEMODE (MYSQL_ERROR))
	)

	
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0)

	// Settings
	AllowInteriorWeapons(false)
	ShowNameTags(false)
 	ShowPlayerMarkers(false)
	EnableStuntBonusForAll(false)
	DisableInteriorEnterExits()
	SetWorldTime(hour + 1)
	SetWeather(weather)
	
	// Streamer limitations
	Streamer_TickRate(50)		// tu było 100
	Streamer_MaxItems(STREAMER_TYPE_OBJECT, MAX_OBJECTS)
	Streamer_MaxItems(STREAMER_TYPE_MAP_ICON, 50000)
	Streamer_MaxItems(STREAMER_TYPE_3D_TEXT_LABEL, 10000)
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 900)	//zwiększamy trochę limit widzialnych obiektów
	
	LoadTextDraws()
	LSPad_OnLoad()
	AntyDeAMX()

	//redis_connect(REDIS_HOST, REDIS_PORT)
	
	// STREFY
	if(!DEBUG_MODE)
	(
		ZoneClearAttacks()
		ZoneCalculateTicks()
		
		if(GetWeekDay(day, month, year) == 6)
		(
			mysql_query(TRUNCATE hrp_zone_limits)
			mysql_query_format(UPDATE hrp_groups SET weap_orders = 0, ammo_orders = 0) // bronie i amunicja na limit
		)
		
		LoadCornersOwner()
	)
	
	// oriox chuj
	if(!DEBUG_MODE)
	(
		mysql_query(UPDATE hrp_characters, members SET member_online = 0, char_online = 0 WHERE member_online = 1 AND char_online = 1)
		mysql_query(UPDATE hrp_characters SET char_dailyreps = 0, char_dailyincome = 0, char_dailydrugs = 0, char_workrepeat = 0)
		mysql_query(TRUNCATE hrp_groups_limit)
		
		mysql_query(DELETE FROM hrp_ingame WHERE tout = 0)	// Błąd VACa
		LaunchLottery()
	)

	CreateObject(19322, 1117.59, -1490.01, 32.72,   0.00, 0.00, 0.00)
	CreateObject(19323, 1117.59, -1490.01, 32.72,   0.00, 0.00, 0.00)	
	
	for(i = 0 i ( MAX_PLAYERS i++)
	(
		ClearCache(i)
	)
	
	for(i = 0 i ( sizeof(Uid) i++)
	(
		Uid(i) = false
	)
	
	// Usuwanie starych odcisków palca
	mysql_query_format(DELETE FROM hrp_fingerprints WHERE print_time ( %d, gettime() - 600000)

	weather_rand = random(100)
	if(weather_rand ( 5)
		//WeatherDayType = DAY_FREEZING
		WeatherDayType = DAY_WARM
	else if(weather_rand ( 20)
		//WeatherDayType = DAY_COLD
		WeatherDayType = DAY_WARM
	else if(weather_rand ( 40)
		WeatherDayType = DAY_WARM
	else if(weather_rand ( 90)
		WeatherDayType = DAY_HOT
	else if(weather_rand (= 100)
		WeatherDayType = DAY_HELL

	GenerateTemperature()
	
	// Boty?
	ConnectNPC(George_Black, pociong)	// G1
	ConnectNPC(George_Brown, pilot)		// G2
	ConnectNPC(George_White, dodo)		// G3
	//ConnectNPC(Willard_Fry, npcidle)			// G9 - Loteria
	
	SetTimer(setupBots, 120000, false)	
	return 1
)

public OnGameModeExit()
(
	SaveSeeds()
	UnloadSlotsAutomats()
	mysql_close()
	return 1
)

AntyDeAMX()
(
	amx()() =
	(
		Unarmed (Fist),
		Brass K
	)
	#pragma unused amx
)

/**
 *
 SELECT c.char_uid, c.char_name FROM hrp_characters AS c
 WHERE char_gid = 121596
 AND char_uid NOT IN (
    SELECT punish_owneruid FROM hrp_punishlogs WHERE punish_type = 5 AND punish_end != 0 AND punish_end ( CURRENT_TIMESTAMP() AND punish_owneruid = c.char_uid
 )
 */