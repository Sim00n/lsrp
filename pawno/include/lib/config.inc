// test
native gpci (playerid, serial (), len) // takie tam dziadostwo

bool:IS_PRIMA_APRILIS = false

#undef MAX_PLAYERS
#undef MAX_VEHICLES
#undef MAX_GANG_ZONES
#undef MAX_OBJECTS

#define MAX_RADIO		5

#define INVALID_SLOT_ID	 (-1)
#define INVALID_DOOR_ID	 (-1)
#define INVALID_GROUP_ID	(-1)
#define INVALID_POKER_GAME_ID (-1)
#define INVALID_SURFBOARD_ID (-1)
#define INVALID_ZONE_ID (-1)

#define KEY_AIM KEY_HANDBRAKE

#pragma tabsize 0
#pragma dynamic 8196

// Main Config
#define SERVER_NAME		Los Santos Role Play
#define LAST_UPDATE		06.12.2015 00:25 GMT +2
#define WEB_URL			www.ls-rp.net
//#define VERSION			LSRP_PB_25092014
#define VERSION 		LSRP_PB_061215
#define GAMEMODE		LS-RP
	DEBUG_MODE	=	false		// false in stable
new		SKIP_OBJECTS = 	false		// false in stable

// Limitations
#define MAX_PLAYERS		 500
#define MAX_VEHICLES		1000
#define MAX_DOORS		   2500		// 1500
#define MAX_ITEM_CACHE	  6400
//#define MAX_ITEM_WA_CACHE	  1000
#define MAX_PHONES			100 // Maksymalna liczba budek telefonicznych.
#define MAX_PLANTS			500 // Maksymalna liczba krzaków.
#define MAX_CALLS			100 // Maksymalna liczba jednoczesnych konwersacji przez telefon/budke na serwerze.
#define MAX_GANGBANGS		20  // Maksymalna liczba jednoczesnych wojen pomiêdzy gagnami. (more than enough)
#define MAX_HOMEPHONES 1600// Maksymalna liczba telefonów stacjonarnych (ERROR)
#define MAX_PRODUCTS		6000
#define MAX_ANIMATIONS	  500
#define MAX_PACKAGES		200
#define MAX_LIMITEDPACKAGES		200
#define MAX_BUS_STOPS	   100
#define MAX_PHOTO_RADARS	10
#define MAX_GANG_ZONES	  50
#define MAX_RACE_CP		 128
#define MAX_OBJECTS		 150000
#define MAX_DAILY_REPS		250
#define MAX_PRESSBOX	150
#define MAX_SLOTS	200
#define MAX_CARDS		10000
#define MAX_SEEDS 1000

#define MAX_ZONES 150
#define MAX_CORNERS	42

#define MAX_GROUPS		  1000
#define MAX_BOOTHS		  50
#define MAX_PETROLS		  50
#define MAX_GROUP_SLOTS	 5

#define MAX_SURFBOARDS 500
#define MAX_SURFBOARD_SPEED (8.5)

#define MAX_DAILY_INCOME 	235 

#define MAX_COOK			500	// maksymalna ilosc piecykow do gotowania narko³yków
#define MAX_INGREDIENTS	18		// maksymalna ilosc skladnikow w tworzeniu

#define PAYDAYDAY		72000 // Liczba sekund co ile gracz mo¿e dostaæ paydaya. 72000s = 20h.
#define PAYDAY_CONSTANT 4 // Liczba dolarów które dodaje siê graczowi za ka¿d¹ minutê na duty.

#define PREMIUM_VEHICLES	3
#define STANDARD_VEHICLES   1

// Anty Cheat Car TP
#define MAX_CARS_NEED_TO_BAN 		3		// ile aut ma do siebie przeteleportowaæ, ¿eby zyskaæ bana
#define AC_PASS_NUMBER					5		// co ile minut resetowaæ limit

// Teams
#define TEAM_DEFAULT			0

// Bodyparts
#define BODY_PART_TORSO 		3
#define BODY_PART_CHEST			4
#define BODY_PART_LEFT_ARM 		5
#define BODY_PART_RIGHT_ARM 	6
#define BODY_PART_LEFT_LEG 		7
#define BODY_PART_RIGHT_LEG 	8
#define BODY_PART_HEAD 			9

// Zapis gracza
#define SAVE_PLAYER_BASIC   	1
#define SAVE_PLAYER_POS	  	2
#define SAVE_PLAYER_SKILLS	  4
#define SAVE_PLAYER_OPTIONS	 8

// Zapis pojazdu
#define SAVE_VEH_POS			1
#define SAVE_VEH_ACCESS   		2
#define SAVE_VEH_COUNT  		4
#define SAVE_VEH_THINGS 		8
#define SAVE_VEH_LOCK   		16

// Zapisywanie krzaków
#define SAVE_PLANT_POS			1
#define SAVE_PLANT_THINGS		2
#define SAVE_PLANT_IDENTITY		4

// Zapis drzwi
#define SAVE_DOOR_ENTER			1
#define SAVE_DOOR_EXIT			2
#define SAVE_DOOR_THINGS		4
#define SAVE_DOOR_AUDIO	 	8
#define SAVE_DOOR_LOCK	  	16
#define SAVE_DOOR_LIMITS	32
#define SAVE_DOOR_PAINTBALL	64

// Wczytanie ustawieñ telefonu
#define GET_PHONE_PASSWORD 	1
#define GET_PHONE_WALLPAPER 	2
#define GET_PHONE_COLOR			4

// Zapis Gangzones
#define SAVE_GZ_POS				1
#define SAVE_GZ_OWNER			2
#define SAVE_GZ_THINGS			4

// Zapis produktu
#define SAVE_PRODUCT_THINGS 	1
#define SAVE_PRODUCT_VALUES 	2
#define SAVE_PRODUCT_OWNERS 	4

// Dashboardy na scrollu
#define DASHBOARD_PLAYER	1
#define DASHBOARD_VEHICLE	2

// Owners
#define OWNER_NONE				0
#define OWNER_PLAYER  			1
#define OWNER_GROUP			 5

// Typy interfejsów przedmiotów
#define INTERFACE_TYPE_TEXT 1
#define INTERFACE_TYPE_GRAPHIC 2

// Typy paliw
#define TYPE_BENS	   			0
#define TYPE_GAS				1
#define TYPE_DIESEL	 			2
#define TYPE_AIRFUEL	 		3

// Ceny paliw
#define BENS_PRICE	   			3.5
#define GAS_PRICE	   			1
#define DIESEL_PRICE	   		2
#define AIRFUEL_PRICE	   		8

// Typy napadów
#define ROBBING_NONE			0
#define ROBBING_GANG			1
#define ROBBING_LSPD			2
#define ROBBING_BOTH			3

// Typy grup
#define GROUP_NONE		  	0
#define GROUP_GASSTATION	1
#define GROUP_GASTRONOMY	2
#define GROUP_BAR		   	3
#define GROUP_HOTEL		 	4
#define GROUP_TAXI		  	5
#define GROUP_WORKSHOP	  	6
#define GROUP_CARDEALER	 	7
#define GROUP_TIMBER		8
#define GROUP_BANK		  	9
#define GROUP_DRIVING	   	10
#define GROUP_CLOTHES	   	11
#define GROUP_GYM		   	12
#define GROUP_RANGE		 	13
#define GROUP_TRANSPORT	 	14
#define GROUP_RACERS		15
#define GROUP_SECURITY	  	16
#define GROUP_COURT		 	17
#define GROUP_CRIMINAL	  	18
#define GROUP_MAFIA		 	19
#define GROUP_CARTEL		20
#define GROUP_DEALERS	   	21
#define GROUP_POLICE		22
#define GROUP_MEDICAL	   	23
#define GROUP_FBI		   	24
#define GROUP_FIREDEPT	  	25
#define GROUP_NEWS		  	26
#define GROUP_GOV		   	27
#define GROUP_ARMY		  	28
#define GROUP_PRISON		29
#define GROUP_AUTOSALE		30
#define GROUP_DRUGSTORE		31
#define GROUP_AIRPORT		32
#define GROUP_SAWMILL		33
#define GROUP_QUARRY		34
#define GROUP_FAMILY		35
#define GROUP_FISHING		36
#define GROUP_TRUCKERS	37
#define GROUP_HARDCORE	38
#define GROUP_HIRE 39	// wypo¿yczalnia wózków
#define GROUP_SKATE 40	// grupa skateów, coœ jak freelancer
#define GROUP_RADIO 41		// radia (pewnie i tak nikt nie skorzysta)
#define GROUP_FARM	42	// Farmerzy
#define GROUP_DOC		43	// Wiêzienie, w sensie grupa policjantów
#define GROUP_SPORT 			44	// sklep sportowy
#define GROUP_CORONER 	45		// Wiadomix.
#define GROUP_INSURANCE 	46	// Ubezpieczenia
#define GROUP_PAINTBALL 	47	// Paintball

// Typy sklepów
#define SHOP_SHADES			1
#define SHOP_HATS			2
#define SHOP_MASKS			3
#define SHOP_UTILITY		4
#define SHOP_ELECTRONIC		5
#define SHOP_LSPD			6
#define SHOP_FD				7
#define SHOP_FULLCAP		8
#define SHOP_JEWELLRY		9
#define SHOP_EMS			10
#define SHOP_DSE		11
#define SHOP_HAIRCUT	12			// no nie wiem?
#define SHOP_PAINTJOB	13		// jak grupa ma takie val 2 to moze oferowac paintjob

// Miejsce przedmiotów
#define PLACE_NONE		  0
#define PLACE_PLAYER		1   // Przedmiot gracza
#define PLACE_VEHICLE	   2   // Przedmiot w pojeŸdzie
#define PLACE_BAG		   3   // Przedmiot w torbie
#define PLACE_SAFE		  4   // Przedmiot w schowku
#define PLACE_MACHINE 5		// W automacie

// Sloty broni
#define WEAPON_MAIN		0	// G³ówna broñ typu M4
#define WEAPON_SIDE		1	// Broñ poboczna typu Deagle
#define WEAPON_FUNC		2	// Broñ funkcjonalno-taktyczna typu nó¿

// Typy przedmiotów
#define TYPE_NONE		   0   // Brak
#define ITEM_WATCH		  1   // Zegarek
#define ITEM_FOOD		   2   // Jedzenie (value1 = iloœæ hp)
#define ITEM_CIGGY		  3   // Papierosy (value1 = iloœæ sztuk)
#define ITEM_CUBE		   4   // Kostka do gry
#define ITEM_CLOTH		  5   // Ubranie (value1 = id skinu)
#define ITEM_WEAPON		 6   // Broñ (value1 = model broni, value2 = amunicja)
#define ITEM_AMMO		   7   // Amunicja (value1 = model broni, value2 = iloœæ amunicji)
#define ITEM_PHONE		  8   // Telefon (value1 = numer telefonu)
#define ITEM_CANISTER	   9   // Karnister (value1 = iloœæ paliwa, value2 = typ paliwa)
#define ITEM_MASK		   10  // Maska
#define ITEM_INHIBITOR	  11  // Paralizator (value2 = iloœæ naboi)
#define ITEM_PAINT		  12  // Lakier (value2 = iloœæ naboi)
#define ITEM_HANDCUFFS	  13  // Kajdanki
#define ITEM_MEGAPHONE	  14  // Megafon
#define ITEM_LINE		   15  // Lina holownicza
#define ITEM_BEDBUG		 16  // Pluskwa
#define ITEM_NOTEBOOK	   17  // Notes (value1 = iloœæ karteczek)
#define ITEM_CHIT		   18  // Karteczka (value1 = uid wpisu w bazie)
#define ITEM_TUNING		 19  // Czêœæ tuningu (value1 = id komponentu)
#define ITEM_CHECKBOOK	  20  // Ksia¿eczka czekowa (value1 = iloœæ czeków)
#define ITEM_CHECK		  21  // Czek (value1 = iloœæ pieniêdzy)
#define ITEM_FISHING		22  // Wêdka (value1 = rodzaj wêdki)
#define ITEM_BAG			23  // Torba
#define ITEM_DRINK		  24  // Napój (value1 = special_action (20 - piwo, 22 - wino, 23 - sprunk))
#define ITEM_DRUG		   25  // Narkotyk (value1 = typ narkotyku, value2 = pozosta³e)
#define ITEM_JOINT		  26  // Joincik

#define ITEM_BLET		   27  // Bletka (wymagana do skrêcenia jointa)
#define ITEM_BONGOS		 28  // Bongos (lepsze dzia³anie pal¹cej siê w nim marihuany)
#define ITEM_BARREL		 29  // Lufka (niezbêdna do kokainy, morfiny etc.)

#define ITEM_ATTACH		 30  // Obiekt przyczepialny (value1 = uid wpisu w bazie)
#define ITEM_ACCESS		 31  // Akcesoria do pojazdu (value1 = typ akcesoria)
#define ITEM_PLATE		  32  // P³yta (value1 = UID wpisu w bazie)
#define ITEM_PLAYER			33  // Odwtarzacz CD (value1 = UID wpisu na p³ycie)
#define ITEM_KEYS		   34  // Kluczyki do pojazdu (value1 = UID pojazdu)
#define ITEM_ARMOUR		 35  // Kamizelka kuloodporna (value1 = iloœæ kamizelki)
#define ITEM_GLOVES		 36  // Rêkawiczki
#define ITEM_CORPSE		 37  // Zw³oki (value1 = UID zabójcy, value2 = typ zabójstwa)
#define ITEM_WINDGUN		38  // Wiatrówka
#define ITEM_ROLL		   39  // Rolki
#define ITEM_PASS		   40  // Karnet
#define ITEM_MOLOTOV		41  // Koktajl mo³otowa (podpalanie budynków)
#define ITEM_PICKLOCK	   42  // Wytrych (value1 = procent powodzenia)
#define ITEM_OPTIWAND	   43  // Optiwand
#define ITEM_CRAFT		  44  // Crafting
#define ITEM_FLASHBANG	  45  // Flashbang
#define ITEM_FLASHLIGHT		46	// Latarka
#define ITEM_WEAPON_AT		47	// Dodatek do broni
#define ITEM_BLADE			48	// Przedmiot z którego mo¿na craftowaæ broñ
#define ITEM_AQUALUNG		49	// Akwalung Arczira
#define ITEM_TIRE			50	// Zapasowa opona.
#define ITEM_NUTRIENT		51  // Od¿ywka na pakierni
#define ITEM_TAGGER			52  // Spray do tagowania dzielnicy
//#define ITEM_WOOD			53	// Drewno do skryptu tartaka
//#define ITEM_ROCK			54	// Kamieñ do skryptu kopalni
//#define ITEM_BOX			55  // Przedmiot do transportu materia³ów.
#define ITEM_DECKOFCARDS	56  // Karty
#define ITEM_LSPAD			57  // LSPad
#define ITEM_ELOCK			58  // Elektroniczny zamek do drzwi
#define ITEM_PAGER			59  // Pager .. gimby nie znajo.
#define ITEM_ROPE		60	//lina do wi¹zania
#define ITEM_HEADBAG	61		// worek na g³owê
#define ITEM_GAG	62		// knebel
#define ITEM_HOMEPHONESET	63		// stacjonarny 
#define ITEM_TUNEPART	64	// (val 1 = ile % ma przyspieszaæ dany pojazd val2 = typ dodatku)
#define ITEM_NEWSPAPER	65	// (val 1 = ID wpisu w bazie wbc_press)
#define ITEM_ROULETTE	66		// na proœbê gracza Czeœæ (- ruletka (- coœ na zasadzie kostki z 36 œciankami
#define ITEM_PUTABLE	67	// obiekt odk³adalny, mo¿liwoœæ oselacji i te sprawy (- (val 1 = ID modelu)
#define ITEM_FAKEPAPERS	68	// ¿ó³te papiery dla FBI
#define ITEM_SEEDS		69	// Nasiona dla plantowania zio³a
#define ITEM_CARD 		70 	// Biznesowa karta p³atnicza
#define ITEM_OXYGEN	71	// butla z tlenem
#define ITEM_SURFBOARD 72 	//deska surfingowa
#define ITEM_BOMB 73
#define ITEM_SILENCER 74		// t³umik
#define ITEM_WORM 75 // robak do wêdki
#define ITEM_BANDAGE 76 // banda¿e
#define ITEM_PLANT	77	// te nowe do sadzenia
#define ITEM_SPECIAL 78		// Baloon shop, limity itp.
#define ITEM_PRESENT	79		// prezent
#define ITEM_SAFE 		80	// Sejfy
#define ITEM_PBENTRY		81 // wejsciowki na paintball
#define ITEM_COOK_INGREDIENT	82 // elementy do gotowania narkotykow
#define ITEM_COOK_OBJECT			83 // obiekt kuchenki do gotowania narkotyków

// Typy kamer
#define	MODE_THIRDPERSON	1
#define	MODE_FIRSTPERSON	2


//////////// NIE ZAPOMNIJ DODAÆ OPISU W ShowPlayerItemInfo W ITEM.INC ORAZ NAZWY I OBIEKTU NA DOLE FRAJERZE ////////////

#define ITEM_COUNT		  83

// Typy dodatków do broni
#define WA_SCOPE	1	// Celownik laserowy
#define WA_LIGHT	2	// Latarka
#define WA_HANDLE	3	// Uchwy
#define WA_MAG		4	// Dodatkowy magazynek
#define WA_SILENT	5	// T³umik

// Okna w menu PD
#define PDM_START 	1 	// Okno startowe
#define PDM_PERSON	2	// Przeglad osoby
#define PDM_CAR		3	// Przeglad osoby

// Typy ofert
#define OFFER_NONE					0   // Nieokreœlony
#define OFFER_ITEM					1   // Przedmiot
#define OFFER_VEHICLE				2   // Pojazd
#define OFFER_PRODUCT				3   // Produkt
#define OFFER_VCARD					4	  // vCard
#define OFFER_PASSAGE				5   // Przejazd Taxi
#define OFFER_REFUEL				6   // Tankowanie pojazdu
#define OFFER_PAINT					7   // Lakierowanie pojazdu
#define OFFER_REPAIR				8   // Naprawa pojazdu
#define OFFER_DOOR					9   // Nieruchomoœæ
#define OFFER_MANDATE				10  // Mandat
#define OFFER_TOWING				11  // Holowanie
#define OFFER_HEAL					12  // Leczenie
#define OFFER_AD					13  // Reklama
#define OFFER_MONTAGE				14  // Monta¿ czêœci
#define OFFER_PAINTJOB				15  // PaintJob
#define OFFER_DOCUMENT				16  // Dokument
#define OFFER_SALON					17  // Pojazd z salonu
#define OFFER_LESSON				18  // Lekcja jazdy
#define OFFER_UNBLOCK				19  // Zdjêcie blokady na kole
#define OFFER_TRAIN					20  // Trening w si³owni
#define OFFER_TAX					21  // Podatek
//#define OFFER_SHOOTING				22  // Strzelanie
#define OFFER_KEYS					23  // Kluczyki do pojazdu
#define OFFER_INTERIOR				24  // Wnêtrze
#define OFFER_PREVIEW				25  // Podgl¹d wnêtrza
#define OFFER_WELCOME				26  // Powitanie
#define OFFER_AREA					27  // Teren gangu
#define OFFER_REGISTER				28  // Rejestracja pojazdu
#define OFFER_FEE					29  // Op³ata
#define OFFER_SEX					30  // Op³ata
#define OFFER_HOTDOG				31  // Sprzeda¿ hotdoga
//#define OFFER_LOAD					32  // Za³adowania pojazdu z materia³ami.
//#define OFFER_UNLOAD				33  // Roz³adowanie pojazdu z materia³ami.
#define OFFER_REPAIR_ENGINE			34  // Naprawa silnika
#define OFFER_REPAIR_BODY			35	// Naprawa karoserii
#define OFFER_REPAIR_FLUIDS			36	// Wymiana p³ynów
#define OFFER_REPAIR_FILTER			37	// Wymiana filtra
#define OFFER_REPAIR_COOLER			38	// Wymiana ch³odnicy
#define OFFER_HIRE_CAR	39
#define OFFER_LIFE					40 // ubezpieczenie na zycie
#define OFFER_PAINTBALL				41 // wejœciówka na paintball

// Typy napraw
#define REPAIR_STANDARD			1	// Normalna naprawa
#define REPAIR_ENGINE			2	// Wymiana silnika
#define REPAIR_BODY				3	// Naprawa karoserii
#define REPAIR_FLUIDS			4	// Wymiana p³ynów
#define REPAIR_FILTER			5	// Wymiana filtra
#define REPAIR_COOLER			6	// Wymiana ch³odnicy

// Typy broni do craftowania pawlika
#define BLADE_KNIFE		1 // Nó¿
#define BLADE_BAT		2 // Pa³ka
#define BLADE_KNUCKLE	3 // Kastet

// Typy sexu
#define SEX_NORMAL	1	// Sex na misjonarza
#define SEX_ORAL	2	// Sex oralny
#define SEX_ANAL	3	// Sex analny
#define SEX_DOGGY	4	// Sex na pieska

// Typy dni do pogody
#define DAY_FREEZING	1  // Mro¼nie zimno (poni¿ej 0 *C)
#define DAY_COLD		2  // Zimno (0 - 15 *C)
#define DAY_WARM		3  // Ciep³o (16 - 25 *C)
#define DAY_HOT			4  // Gor±co (26 - 36 *C)
#define DAY_HELL		5  // Piekielnie gor±co (36+ *C)

// Typy dni ogólnie, w tygodniu
#define DAY_SATURDAY 0
#define DAY_SUNDAY 1
#define DAY_MONDAY 2
#define DAY_TUESDAY 3
#define DAY_WEDNESDAY 4
#define DAY_THURSDAY 5
#define DAY_FRIDAY 6

// Typy stref
#define ZONE_TYPE_NONE 0
#define ZONE_TYPE_MONEY 1
#define ZONE_TYPE_GUN 2
#define ZONE_TYPE_DRUG 3
#define ZONE_TYPE_MAIN 4 

// Limity na bronie?
/*
	no jeszcze nie u¿ywane bo Nejman siê nie okreœli³ jakie te limity maj¹ byæ
*/

// Typy limitów w strefach (nieu¿ywane jeszcze)
#define LIMIT_ZONE_NEUTRALS	0
#define LIMIT_ZONE_ATTACK		1

// Typy informacji o strefach
#define GZ_SUMMARY_VISITOR				1
#define GZ_SUMMARY_OWNER				2

// Sloty przyczepionego obiektu
#define SLOT_WEAPON_MAIN				0
#define SLOT_WEAPON_SIDE				1
#define SLOT_WEAPON_FUNC				2

#define SLOT_TRAIN_ITEM			3
#define SLOT_FISHING_ROD		3
#define SLOT_PHONE				3
#define SLOT_TRYING				3
#define SLOT_ACCESS_ONE			4
#define SLOT_ACCESS_TWO			5
#define SLOT_ACCESS_THREE		6

#define SLOT_FLASHLIGHT			7
#define SLOT_FLASHLIGHT_BEAM	8
#define SLOT_ACCESS_FOUR		9

// Style walk
#define FIGHT_NORMAL		1
#define FIGHT_BOX			2
#define FIGHT_KUNGFU		4
#define FIGHT_KICKBOX		8
#define FIGHT_ULTI			16

// Typy kar
#define PUNISH_WARN		 	1
#define PUNISH_KICK		 	2
#define PUNISH_BAN		  	3
#define PUNISH_GLOB_BAN	 	4
#define PUNISH_BLOCK_CHAR   5
#define PUNISH_BLOCK_VEH 	6
#define PUNISH_BLOCK_RUN	7
#define PUNISH_BLOCK_OOC	8
#define PUNISH_AJ		   	9
#define PUNISH_BLOCK_OBJ	10

// Typy banów
#define BANTYPE_BAN		 	1
#define BANTYPE_FILTER	  	2

// Typy treningów w si³owni
#define TRAIN_NONE		  	0
#define TRAIN_BENCH_PRESS   1
#define TRAIN_BARBELL	   	2
#define TRAIN_PUNCH_BAG	 	3

// Typy umiejêtnoœci
#define SKILL_SHOOT		 	1
#define SKILL_CONDITION	  	2
#define SKILL_DRIVE			3
#define SKILL_FISH			4
#define SKILL_STRENGTH		5

// Typy prac dorywczych
#define JOB_NONE			0
#define JOB_COURIER		 	1
#define JOB_FISHER		  	2
#define JOB_MECHANIC		3
#define JOB_SWEEPER			4
#define JOB_HOTDOG			5
#define JOB_PRESSER	6
#define JOB_SCOURER	7		// ten co tagi czyœci

// Typy pojazdów w salonie
#define VEH_ONESEAT			1   //  Jednoœlady
#define VEH_THREEDOORS		2	//  Trzydrzwiówki
#define VEH_FIFTHDOORS		3   //  Piêciodrzwiówki
#define VEH_HEAVY		  	4   //  Furgonetki i ciê¿arówki
#define VEH_OTHERS		  	5   //  Pozosta³e

// Uprawnienia
#define PERM_OFFER		  	1   // Oferowanie (/o)
#define PERM_CARS		   	2   // Pojazdy
#define PERM_DOORS		  	4   // Drzwi
#define PERM_ORDER		  	8   // Zamawianie produktów
#define PERM_CHAT		   	16  // Korzystanie z czatu OOC
#define PERM_LEADER		 	32  // Lider
#define PERM_GATE		   	64  // Dostêp do /brama

#define PERM_LIMIT		  	127  // Mo¿e wszystko

// Dokumenty posiadane
#define DOC_NONE			0
#define DOC_PROOF		   	1
#define DOC_DRIVER		  	2
#define DOC_SEND			4
#define DOC_SANITY		  	8

// Rodzaje p³atnoœci
#define PAYTYPE_NONE		0
#define PAYTYPE_CASH		1
#define PAYTYPE_CARD		2
#define PAYTYPE_BCARD		3

// U¿ywalne obiekty
#define OBJECT_ATM				2942
#define OBJECT_BENCH			2629
#define OBJECT_BARBELL			2915
#define OBJECT_PUNCH_BAG		1985
#define OBJECT_TRACK			2627
#define OBJECT_FUELING			3465
#define OBJECT_BUSSTOP			1257
#define OBJECT_POOL_TABLE   	2964
#define OBJECT_TELEPHONE		1216
#define OBJECT_TELEPHONE_ALT	1346
#define OBJECT_POLICE_POLE		1238
#define OBJECT_POLICE_DETOUR	1425
#define OBJECT_POLICE_FLARE		18728
#define OBJECT_POLICE_JUMP		14449
#define OBJECT_POLICE_LADDER	1437
#define OBJECT_POLICE_LINE		19527
#define OBJECT_POLICE_CRIME		19528
#define OBJECT_POLICE_CAUTION	19529
#define OBJECT_POLICE_FIRELINE	19526
#define OBJECT_POLICE_HESCO		14080
#define OBJECT_AIR_PUMP 		19570
#define OBJECT_HOTDOG			1340
#define OBJECT_HOMEPHONE		330	//do zmiany
#define OBJECT_BASKETBALL 		1946
#define OBJECT_BASKETBOARD		946
#define OBJECT_FIRE_WRECK 		15221
#define OBJECT_MICROPHONE		14020
#define OBJECT_COOK					2144	//	2170

// Typy narkotyków
#define DRUG_MARIHUANA		1
#define DRUG_COCAINE		2
#define DRUG_HEROIN			3
#define DRUG_AMPHETAMINE	4
#define DRUG_MEDICINE	   	5
#define DRUG_CRACK		  	6
#define DRUG_LSD			7
#define DRUG_SHROOMS		8
#define DRUG_MDMA			9
#define DRUG_METAAMP		10

// Prace w wiêzieniu
#define WORK_LAUNDRY		1
#define WORK_WORKSHOP	2

// Etapy pracy
#define LAUNDRY_UNLOADED		1
#define LAUNDRY_LOADED			2
#define WORKSHOP_WAITING	3
#define WORKSHOP_SAWING		4


// Typy krzakó
#define PLANT_WEED			1

// Typy telefonów
#define DEVICE_CELL			1
#define DEVICE_BOX			2
#define DEVICE_HOME			3
/*
    100 (= x (= 999			Numery alarmowe / Taxi / WN
   1000 (= x (= 9999		Numery stacjonarne
  10000 (= x (= 99999		Pagery
 100000 (= x (= 999999		Numery komórkowe
1000000 (= x (= ...			Budki telefoniczne
*/


// Typy /q
#define QUIT_TIMEOUT		1
#define QUIT_KICK			2
#define QUIT_BAN			3
#define QUIT_QS				4
#define QUIT_Q				5
#define QUIT_SWITCHING		6

// Korporacja
#define CORP_TYPE_NONE 		0
#define CORP_TYPE_MATH			1
#define CORP_TYPE_TEXT			2

// Typy u¿ycia
#define DRUG_USE_SMOKE		1
#define DRUG_USE_SNORT		2
#define DRUG_USE_INJECT		3
#define DRUG_USE_GUMS		4

// Crafting
#define CRAFT_BLET		  	1
#define CRAFT_BONGOS		2

// Typy BW
#define BW_STANDARD			1
#define BW_SHOT				2
#define BW_EMS				3

// Przedmiot po craftingu
#define ITEM_CRAFT_JOINT	1
#define ITEM_CRAFT_BONGOS   2

// Typy broni
#define WEAPON_TYPE_NONE	0
#define WEAPON_TYPE_HEAVY   1
#define WEAPON_TYPE_LIGHT   2
#define WEAPON_TYPE_MELEE   3

// Typy spawnów
#define SPAWN_NONE		  	0
#define SPAWN_HOUSE		 	1
#define SPAWN_HOTEL		 	2
#define SPAWN_GROUP		 	3
#define SPAWN_FAMILYHOUSE	4

//Fazy truckerskie
#define TRUCK_PHASE_LOAD 1
#define TRUCK_PHASE_UNLOAD 2
#define TRUCK_PHASE_RIDE 3
#define TRUCK_PHASE_LOADED 4

//typy naczep
#define TRAILER_TYPE_FOOD 435
#define TRAILER_TYPE_MATERIALS 450
#define TRAILER_TYPE_OIL 584
#define TRAILER_TYPE_TOOLS 591

//Typy towarów
#define CARGO_TYPE_OIL 1		//paliwo
#define CARGO_TYPE_FOOD 2	//zarelkko
#define CARGO_TYPE_TOOLS 3	//narzedzia
#define CARGO_TYPE_MATERIALS 4	//materialy budowlane

// Fazy koszykówki
#define BALL_START 1		//rozpocz¹³ gre
#define BALL_TAKE 2			//podniós³ pi³kê
#define BALL_THROW 3 		//rzuci³
#define BALL_PICKUP 4			// podniós³ by przenosiæ

// Typy blokad
#define BLOCK_NONE		0
#define BLOCK_CHAR		1
#define BLOCK_VEH		2
#define BLOCK_RUN		4
#define BLOCK_OOC		8
#define BLOCK_OBJ		16

// Typy gui
#define GUI_TYPE_NONE 0
#define GUI_TYPE_DOCUMENT_DRIVING 1
#define GUI_TYPE_EQUIPMENT 2

// Akcesoria w pojeŸdzie
#define VEH_ACCESS_NONE		 	0
#define VEH_ACCESS_ALARM		1
#define VEH_ACCESS_IMMO		 	2
#define VEH_ACCESS_AUDIO		4
#define VEH_ACCESS_RADIO		8
#define VEH_ACCESS_DIM			16

// Akcesoria w budynku
#define DOOR_ACCESS_NONE		0
#define DOOR_ACCESS_SPRINKLERS  1
#define DOOR_ACCESS_BURGLARY	2

// Typy audio
#define AUDIO_NONE			0
#define AUDIO_ALARM			1
#define AUDIO_MESSAGE		2
#define AUDIO_CALLING		3
#define AUDIO_WN_START		4
#define AUDIO_FLASHBANG		5
#define AUDIO_SIREN			6
#define AUDIO_FDSIREN		7
#define AUDIO_HUMILIATION	9

// Rodzaje /duty
#define DUTY_NONE		   	0
#define DUTY_ADMIN		  	1
#define DUTY_GROUP		  	5

//bomby
#define BOMB_TYPE_ARM 1
#define BOMB_TYPE_SEARCH 2
#define BOMB_TYPE_DEFUSE 3

// Typy specjalnych
#define SPECIAL_TYPE_OBJECT 1

// Statusy pod nickiem
#define STATUS_NONE		 	0
#define STATUS_DRUNK		1
#define STATUS_STONED		2
#define STATUS_AFK		 	4
#define STATUS_MUSCULAR	 	8
#define STATUS_UNCON		16
#define STATUS_EARPIECE	 	32
#define STATUS_BELTS		64
#define STATUS_MASKED		128
#define STATUS_GLOVES		256
#define STATUS_ARMOUR		512
#define STATUS_ROLL		 	1024
#define STATUS_NEWCHAR	 	2048
#define STATUS_NEWPLAYER	4096
//#define STATUS_FIT			8192	(-- Skrypty usuniete - mozna zagospodarowac na cos innego
#define STATUS_GAGGED		16384
#define STATUS_TIED			32768
#define STATUS_HEADBAG		65536
#define STATUS_READ			131072
#define STATUS_BLEEDING		262144
#define STATUS_CELEBRITY		524288
#define STATUS_DRUGGY			1048576
#define STATUS_BAKED			2097152

// Stany zmieniania postaci
#define STAGE_NONE			0
#define STAGE_CAM01			1
#define STAGE_CAM02			2
#define STAGE_CAM03			3
#define STAGE_REAJUST_TILT	4
#define STAGE_CAM11			5
#define STAGE_CAM12			6
#define STAGE_CAM13			7
#define STAGE_CAM14			8
#define STAGE_SPAWN			9

// Typy zarz¹dzania
#define MANAGE_TYPE_ALL	 		1
#define MANAGE_TYPE_USE	 		2
#define MANAGE_TYPE_DROP   		3
#define MANAGE_TYPE_DASHBOARD_OFFER		4


//typy dodatków do pojazdów
#define VEH_ADD_TURBOCHARGER 1	//turbosprê¿arka
#define VEH_ADD_CHARGER 2	//sprê¿arka
#define VEH_ADD_GEARBOX 3	//skrzynia biegów
#define VEH_ADD_SUSPENSION 4	// zawieszenie
#define VEH_ADD_INTERCOOLER 5		//intercooler

//Typy telefonów - marki
#define PHONE_TYPE_OLD 					0
#define PHONE_TYPE_BLACKBERRY 	1
#define PHONE_TYPE_SAMSUNG 		2
#define PHONE_TYPE_HTC 					3
#define PHONE_TYPE_NOKIA 				4
#define PHONE_TYPE_SONY 				5
#define PHONE_TYPE_GALAXY 			6
#define PHONE_TYPE_IPHONE 			7
#define PHONE_TYPE_IPHONE_WHITE	8

// Co w telefonie robiæ mo¿na?
#define PHONE_ACTION_HOME 0
#define PHONE_ACTION_SETTINGS 1

// Typy paczek noszonych w porcie
#define BOX_NONE 				0
#define BOX_LIGHT 				1
#define BOX_MEDIUM			2
#define BOX_HUGE				3

// Fazy noszenia paczki
#define BOX_PHASE_NONE			0
#define BOX_PHASE_START		1
#define BOX_PHASE_CARRY		2
#define BOX_PHASE_GONEW		3

// Statusy craftowania narkotyków
#define COOK_STATUS_ZERO				0
#define COOK_STATUS_FREE				1
#define COOK_STATUS_COOKING			2

// Dialogs
#define D_INFO					1
#define D_LOGIN					2

#define D_LIST_PLAYER_CARS		3
#define D_LIST_SPAWNED_CARS	 	4

#define D_CHANGE_PICKUP		 	5

#define D_SELECT_INTERIOR	   	6

#define D_DOOR_OPTIONS		  	7
#define D_CHANGE_DOOR_NAME	  	8
#define D_CHANGE_ENTER_PRICE	9
#define D_CHANGE_DOOR_AUDIO	 	10
#define D_ASSIGN_DOOR		   	11
#define D_ASSIGN_DOOR_ACCEPT	12

#define D_RAISE_ITEM			13

#define D_OFFER				 	14
#define D_OFFER_PAYTYPE		 	15
#define D_OFFER_LIST			16

#define D_ITEM_USE_AMMO		 	17

#define D_OFFER_PRODUCT			18
#define D_BUY_PRODUCT		   	19

#define D_LIST_CONTACTS		 	20
#define D_OPTION_CONTACT		21
#define D_DELETE_CONTACT		22
#define D_SEND_VCARD			23

#define D_CHANGE_ROOM_PRICE	 	24

#define D_TEL_OPTIONS		   	25
#define D_INSERT_NUMBER_CALL	26
#define D_INSERT_NUMBER_SMS	 	27
#define D_INSERT_TEXT_SMS	   	28

#define D_SELECT_WEIGHT_BENCH   29
#define D_SELECT_WEIGHT_BARBELL 30
#define D_SELECT_FIGHTING_STYLE 31

#define D_ADD_CHIT			  	32

#define D_UNMOUNT_TUNING		33

#define D_CREATE_BANK_ACCOUNT   34
#define D_SELECT_BANK_OPTION   	35

#define D_DEPOSIT_CASH		  	36
#define D_WITHDRAW_CASH		 	37
#define D_TRANSFER_NUMBER	   	38
#define D_TRANSFER_CASH		 	39

#define D_WRITE_A_CHECK		 	40

#define D_PRODUCT_TYPE		  	41
#define D_SELECT_PRODUCT		42
#define D_PRODUCT_NUMBER		43
#define D_PRODUCT_PRICE		 	44

#define D_HELP				  	45

#define D_SEND_PW			   	46

#define D_PLAY_ANIM			 	47

#define D_GET_PACKAGE		   	48

#define D_SELECT_JOB			49
#define D_SELECT_COURIER		50
#define D_SELECT_FISHER		 	51
#define D_SELECT_MECHANIC	   	52

#define D_REMOVE_ITEM_BAG	  	53
#define D_PUT_ITEM_BAG		  	54

#define D_MANAGE_VEH			55

#define D_ALARM_NUMBER		  	56
#define D_ALARM_CALL			57

#define D_SALON_OFFER_CAT	   	58
#define D_SALON_OFFER_VEH	   	59

#define D_BLOCK_WHEEL		   	60

#define D_TAXI_CALL			 	61
#define D_SN_CALL			   	62

#define D_PRODUCT_COSTS		 	63
#define D_PRODUCT_SELECT		64
#define D_PRODUCT_OPTION		65
#define D_PRODUCT_DELETE		66

#define D_SELECT_SKILL		  	67

#define D_SELECT_BUSSTOP		68
#define D_ACCEPT_TRAVEL		 	69

#define D_SALON_PRICE_LIST	  	70

#define D_INTRODUCTION		  	71

#define D_ACTION_CRAFT		  	72

#define D_SELECT_DRUG_USE	   	73
#define D_TYPE_COCAINE_USE	  	74

#define D_ASSIGN_VEH			75
#define D_ASSIGN_VEH_ACCEPT	 	76

#define D_LIST_PLAYERS		  	77

#define D_SELECT_SPAWN		  	78

#define D_RECORD_DISC		   	79
#define D_RECORD_DISC_NAME	  	80

#define D_INSERT_DISC		   	81

#define D_REMOVE_ITEM_SAFE	  	82

#define D_DIRECTORY_INFO		83

#define D_EDIT_REGISTER		 	84
#define D_SELECT_CLOTH_OPTION   85

#define D_ACCESS_APPLY		  	86

#define D_RADIO_OPTIONS			87
#define D_RADIO_SET_CANAL	  	88
#define D_RADIO_PASSWORD		89
#define D_RADIO_BUY_CANAL	   	90
#define D_RADIO_ACCEPT_CANAL	91
#define D_RADIO_CANAL_PASSWORD  92
#define D_RADIO_SET_PASSWORD	93
#define D_RADIO_DELETE_CANAL	94
#define D_RADIO_DELETE_ACCEPT   95
#define D_RADIO_ASSIGN_CANAL	96
#define D_RADIO_ASSIGN_ACCEPT   97

#define D_SELECT_TAXI_CORP	 	98

#define D_PLAYER_STATS		  	99
#define D_SELECT_WALK_ANIM	  	100

#define D_LIST_ITEMS		  	101
#define D_MANAGE_ITEM		   	102
#define D_OFFER_ITEM_PLAYER	 	103
#define D_OFFER_ITEM_PRICE	  	104
#define D_CHECK_ITEM			105

#define D_LIST_ITEMS_USE		106
#define D_LIST_ITEMS_DROP	   	107

#define D_CHANGE_GROUP_TYPE	 	108

#define D_MANAGE_GROUPS		 	109
#define D_GROUP_OPTIONS		 	110

#define D_LEAVE_GROUP		   	111
#define D_ADD_SUBGROUP		  	112
#define D_SUBGROUP_LIST		 	113

#define D_BOOTH_NUMBER		  	114
#define D_TEL_ADDNUM			115
#define D_TEL_ADDNAME		   	116

#define D_DESC_OPTIONS			117
#define D_DESC_ACTIONS		  	118
#define D_DESC_LIST			 	119
#define D_DESC_ADD			  	120
#define D_DESC_ADDNAME		  	121
#define D_DESC_SHOW			 	122

#define D_PRODUCT_GETNUM		123

#define D_PICK_STYLE			124

#define D_SWEEP_ACCEPT			125
#define D_SELECT_SWEEPER		126

#define D_DIVIDE_ITEM			127
#define D_DIVIDE_ITEM_FINAL		128

#define D_ADD_GROUP_ANN			129

#define D_TYPE_AMPHETAMINE_USE	130
#define D_TYPE_LSD_USE			131
#define D_TYPE_METAAMP_USE		132
#define D_TYPE_HEROIN_USE		133

#define D_SELECT_HOTDOG			134

#define D_SPRAY					135
#define D_SPRAY_FONT_SIZE		136
#define D_SPRAY_FONT			137

#define D_PD_NAME_INPUT			138
#define D_PD_CAR_NAME_INPUT		139

#define D_FCK_CONFIRM			141

#define D_DESTROY_CAR			142

#define D_PD_C_ADD_NEW			143
#define D_PD_C_LIST				144
#define D_PD_C_ADD_FIELD		145
#define D_PD_C_ADD_DATA			146
#define D_PD_C_RECORD			147
#define D_PD_C_SEARCH_RESULT	148

#define D_BW_LIST				149

#define D_FCK_REASON			150
#define D_FCK_REASON_P			151

#define D_ADD_ITEM_DESC			152
#define D_SHOW_ITEM_INFO_TO		153

//#define D_BLACKJACK_INVITE		154
//#define D_BLACKJACK_CONFIRM		155

#define D_LSPAD_PASSWORD		156
#define D_LSPAD_NEWPASSWORD		157
//#define D_SELECT_CHAR			158

#define D_GETZONE_MARIHUANA		159
#define D_GETZONE_AMP			160
#define D_GETZONE_METAAMP		161
#define D_ZONE					162
#define D_GZ_OFFER				163
#define D_GZ_SURRENDER			164
#define D_GZ_MSG				165

#define D_DOOR_ADDON_LIST	166
#define D_DOOR_ADDON_MOUNT	167

#define D_DOOR_PHONE_MENU	168

#define D_VEH_ADDONS	169
#define D_VEH_ADDON_DISMOUNT	170

#define D_WBC_PRESS	171
#define D_WBC_CREATE	172
#define D_WBC_WRITE	173
#define D_WBC_TITLE 174

#define D_PRESS_BUY 175
#define D_PRESS_JOB	176

#define D_SELECT_PRESSER 177

#define D_FBI_FAKEPAPERS 179

#define D_DOOR_SET_TIME 180

#define D_CREATE_CARD	181

#define D_SELECT_CHAR	182

#define D_MANDAT_PD_INPUT_NAME 183

#define D_INTERFACE_SELECT 184
#define D_GRAPHIC_SELECT	185

#define D_ZONE_MENU 186
#define D_ZONE_OFFER 187
#define D_ZONE_GIVE 188

#define D_WEAPON_SILENCER_SELECT 189
#define D_WEAPON_SILENCER_UNMOUNT	190

#define D_TEXT_MATSIZE 191
#define D_TEXT_FONTFACE 192
#define D_TEXT_BOLD 193
#define D_TEXT_FONTSIZE 194
#define D_TEXT_TEXT	195

#define D_FISH_INFO 196
#define D_FISH_MARKET 197

#define D_SELECT_SCOURER 198

#define D_HALL 		199
#define D_HALL_START_RIDE			200
#define D_HALL_REGISTER 201

#define D_BUY_HOUSE 202

#define D_BANDAGE 203
#define D_BANDAGE_SOMEONE 204

#define D_SELECT_RADIOSTATION 205

#define D_CAPTCHA 206

#define D_USED_LIST 207
#define D_USED_CONFIRM 208

#define D_DRUG_DEALING_START 209
#define D_DRUG_DEALING_CONTINUE 210
#define D_DRUG_SELL 211

#define D_NEAR_OBJECTS 212

#define D_SPARING_INVITE 213

#define D_OBJECTS_DELETE 214

#define D_PHONE_PASS 215
#define D_PHONE_PASS_CHANGE 216
#define D_PHONE_PASS_INPUT 217
#define D_PHONE_SELECT_WALLPAPER 218

// Dialogi Launchera
#define D_LAUNCH_SELECT_CHAR 220

// Dialogi paczek
#define D_BOX_SELECT_WEIGHT 		221

// Weryfikacja dwuetapowa
#define D_VERIFICATE 222

// Korporacja
#define D_CORPO 223

#define D_JOIN_BOWLING 224

#define D_NEW_SAFE_PASSWORD		226
#define D_SAFE_AUTH				227
#define D_SAFE_OP 				228
#define D_SAFE_IN_VALUE			229
#define D_SAFE_OUT_VALUE		230

// 231-xxx DIALOGI BLACKJACKOWE

#define D_COOK_SELECT		233
#define D_COOK_ADD			234

#define D_DASHBOARD_ITEM	235
#define D_DASHBOARD_ITEM_PRICE	236
#define D_DASHBOARD_PAY		237
#define D_DASHBOARD_KISS		238
#define D_DASHBOARD_YO		239

#define D_BUY_PAYTYPE			240

#define D_FCK_DECISION		241

// Colors
#define COLOR_WHITE			0xFFFFFFFF
#define COLOR_BLACK		 	0x000000FF
#define COLOR_BROWN 		0x8F4747FF
#define COLOR_KREM 			0xFF8080FF
#define COLOR_SAY 			0x2986CEFF
#define COLOR_GREY 			0xAFAFAFAA
#define COLOR_SYSGREY 		0xC6BEBDFF
#define COLOR_GREEN 		0x33AA33AA
#define COLOR_RED 			0xAA3333AA
#define COLOR_LIGHTRED	  	0xFF6347AA
#define COLOR_YELLOW 		0xFFFF00AA
#define COLOR_BLUE 			0x0000BBAA
#define COLOR_LIGHTBLUE 	0x33CCFFFF
#define COLOR_ORANGE 		0xFF9900AA
#define COLOR_DARKRED 		0xAA993333
#define COLOR_GREEN 		0x33AA33AA
#define COLOR_RED 			0xAA3333AA
#define COLOR_YELLOW 		0xFFFF00AA
#define COLOR_PINK 			0xFF66FFAA
#define COLOR_BLUE 			0x0000BBAA
#define COLOR_ORANGE 		0xFF9900AA
#define COLOR_VIOLET 		0x8000FFFF
#define COLOR_BROWN 		0x8F4747FF
#define COLOR_DARKGREY 		0x808080FF
#define COLOR_BLACK 		0x000000FF
#define COLOR_DARKGREEN 	0x0D731FFF
#define COLOR_DARKBLUE 		0x2010E0FF
#define COLOR_DARKBROWN 	0x530000FF
#define COLOR_DARKVIOLET 	0x400040FF
#define COLOR_DARKYELLOW 	0x808000FF
#define COLOR_DARKPINK 		0x400040FF
#define COLOR_KREM 			0xFF8080FF
#define COLOR_LIGHTGREEN 	0x00FF00FF
#define COLOR_LIGHTPINK 	0xFF80FFFF
#define COLOR_PURPLE	 	0xC2A2DAFF
#define COLOR_PURPLE2		0xE0EA64FF

#define COLOR_DO	   		0x9A9CCDFF
#define COLOR_INFO			0xD7A064FF

#define COLOR_FADE1   		0xE6E6E6E6
#define COLOR_FADE2   		0xC8C8C8C8
#define COLOR_FADE3   		0xAAAAAAAA
#define COLOR_FADE4   		0x8C8C8C8C
#define COLOR_FADE5   		0x6E6E6E6E

#define COLOR_GRAD1   		0xB4B5B7FF
#define COLOR_GRAD2   		0xBFC0C2FF
#define COLOR_GRAD3   		0xCBCCCEFF
#define COLOR_GRAD4   		0xD8D8D8FF
#define COLOR_GRAD5   		0xE3E3E3FF
#define COLOR_GRAD6	  		0xF0F0F0FF

#define COLOR_BUSINESS	  	0x8A614DFF
#define COLOR_ORG  			0x70B8B8FF
#define COLOR_FACTION	   	0x8A8AFFFF
#define COLOR_DEPARTMENT	0x3DF5FFFF // 3DFF9E

#define COLOR_RADIO		 	0x0077FFFF

#define COLOR_ADMIN		 	0xEEE8AAFF
#define COLOR_SUPPORT	   	0x44D6FFFF

#define COLOR_SEND_PW   	0xFFC973FF
#define COLOR_GOT_PW  		0xFDAE33FF

#define COLOR_DESC		  	0xC2A2DAFF

#define COLOR_CB_RADIO	  	0xEFF291FF

#define PIN_SPREAD_ANGLE	35.0
#define ARROW_DIST 			4.0
#define ARROW_SPREAD 		2.0
#define ARROW_SPREAD_SQ		4.0
#define PED_DISPLACEMENT	-2.0	


_str(256)

#define AbS(%1) \
		(((%1) ( 0) ? (-(%1)) : ((%1)))

#define chrtoupper(%1) \
		(((%1) ) 0x60 && (%1) (= 0x7A) ? ((%1) ^ 0x20) : (%1))
		
#define chrtolower(%1) \
		(((%1) ) 0x40 && (%1) (= 0x5A) ? ((%1) | 0x20) : (%1))

#define isnull(%1) \
		((!(%1(0))) || (((%1(0)) == \1) && (!(%1(1)))))
		
#define Speed(%0,%1,%2,%3,%4) \
		floatround(floatsqroot((%4)?(%0*%0+%1*%1+%2*%2):(%0*%0+%1*%1))*%3*1.6)

#define SendClientFormatMessage(%0,%1,%2,%3) \
do \
( \
	if(strlen(%2) ) 0) \
	( \
		format(_str, sizeof(_str), %2, %3) \
		SendClientMessage(%0, %1, _str) \
	) \
) \
while(FALSE)

#define ShowAdminLog(%0,%1) \
do \
( \
	if(strlen(%0) ) 0) \
	( \
		format(_str, sizeof(_str), %0, %1) \
		TextDrawSetString(Text:TextDrawAdminLog, _str) \
		AdminLogTime = 20 \
	) \
) \
while(FALSE)

#define PRESSED(%0) \
		(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
	
#define HOLDING(%0) \
		((newkeys & (%0)) == (%0))
		
#define GetObjectUID(%0) \
		Streamer_GetIntData(STREAMER_TYPE_OBJECT, %0, E_STREAMER_EXTRA_ID)

#define GetObjectModel(%0) \
		Streamer_GetIntData(STREAMER_TYPE_OBJECT, %0, E_STREAMER_MODEL_ID)
		
#define GetLabelUID(%0) \
		Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, %0, E_STREAMER_EXTRA_ID)
		
// Forwards

forward LoadSettings()

forward OnPlayerLogin(playerid)
forward SetPlayerSpawn(playerid)
forward SavePlayerStats(playerid, what)
forward ShowPlayerStats(playerid, giveplayer_id)

forward CreateBooth(Float:PosX, Float:PosY, Float:PosZ, Float:Radius)
forward DeleteBooth(gameid)
forward SaveBooth(gameid)

forward CreatePetrol(Float:PosX, Float:PosY, Float:PosZ, Float:Radius)
forward DeletePetrol(gameid)
forward SavePetrol(gameid)

forward CreateCar(modelid, Float:PosX, Float:PosY, Float:PosZ, Float:PosA, color1, color2, respawn_delay)
forward LoadVehicle(gameid, uid)
forward SaveVehicle(gameid, what)
forward DeleteVehicle(gameid)
forward LoadVehicles()
forward ShowPlayerVehicleInfo(playerid, gameid)

forward CreateDoor(Float:EnterX, Float:EnterY, Float:EnterZ, Float:EnterA, EnterInt, EnterVW, DoorName())
forward LoadDoor(gameid, uid)
forward SaveDoor(gameid, what)
forward DeleteDoor(gameid)
forward LoadDoors()
forward ShowPlayerDoorInfo(playerid, gameid)
forward ShowPlayerDoorAddons(playerid, gameid)

forward OnPlayerEnterDoor(playerid, doorid)
forward OnPlayerExitDoor(playerid, doorid)

forward CreatePlayerItem(playerid, ItemName(), ItemType, ItemValue1, ItemValue2)
forward CreateVehicleItem(vehid, ItemName(), ItemType, ItemValue1, ItemValue2)
forward DeleteItem(itemuid)
forward OnPlayerRaiseItem(playerid, itemuid)

forward OnPlayerUseItem(playerid, itemid)
forward OnPlayerDropItem(playerid, itemid, bool:skip_anim)

forward ShowPlayerItemInfo(playerid, itemid)

forward LoadItem(itemuid)
forward LoadPlayerItems(playerid)
forward UnloadPlayerItems(playerid)

forward ListPlayerItems(playerid, manage_type)
forward ListPlayerNearItems(playerid)
forward ListPlayerCheckedItems(playerid)

forward ListPlayerItemsForPlayer(playerid, giveplayer_id)
forward ListVehicleItemsForPlayer(playerid, vehicleid)

forward AddDoorProduct(ProductName(), ProductType, ProductValue1, ProductValue2, ProductPrice, ProductNumber, ProductDoorUID)
forward LoadAllProducts()
forward DeleteProduct(product_id)
forward SaveProduct(product_id, what)
forward ListPlayerDoorProducts(playerid, doorid)

forward LoadSafeObjects()
forward LoadAllObjects()
forward LoadCorpseObjects()

forward Add3DTextLabel(LabelDesc(128), LabelColor, Float:LabelPosX, Float:LabelPosY, Float:LabelPosZ, Float:LabelDrawDistance, LabelWorld, LabelInteriorID)
forward Load3DTextLabels()
forward Destroy3DTextLabel(label_id)
forward Save3DTextLabel(label_id)

forward LoadAnims()

forward CreatePackage(PackageDoorUID, PackageItemName(32), PackageItemType, PackageItemValue1, PackageItemValue2, PackageItemNumber, PackageItemPrice, PackageSecured)
forward LoadPackages()
forward DeletePackage(package_id)

forward CreateLimitedPackage(PackageDoorUID, playerid, playeruid, PackageItemName(32), PackageItemType, PackageItemValue1, PackageItemValue2, PackageItemNumber, PackageItemPrice, PackageSecured)
forward LoadLimitedPackages()
forward DeleteLimitedPackage(limitedpackage_id)

forward AddSalonVehicle(VehModel, VehType, VehPrice)
forward LoadSalonVehicles()
forward DeleteSalonVehicle()

forward OnPlayerSendOffer(playerid, customerid, type, offer_name(), value, price)
forward OnPlayerAcceptOffer(playerid, offererid)
forward OnPlayerRejectOffer(playerid, offererid)

forward KillAnimation(playerid)
forward ProxDetector(Float:radi, playerid, string(), col1, col2, col3, col4, col5, bool:skip_windows)

forward OnVehicleEngineStarted(vehicleid)

forward AddPlayerReasonToDirectory(playerid, reason())
forward ShowPlayerDirectoryForPlayer(playerid, giveplayer_id)

forward AddPlayerPunishLog(playerid, giveplayer_id, punish_type, reason(), days)
forward AddPlayerLoginLog(playerid, bool: success)

forward OnPlayerGymTrainStarted(playerid)
forward OnPlayerGymTrainStopped(playerid)
forward OnPlayerTrainRep(playerid)

forward PayDay(playerid)

forward OnPlayerSkillUp(playerid, skill_type)
forward OnPlayerSkillDown(playerid)

forward hrp_AddObject(ModelID, Float:objePosX, Float:objePosY, Float:objePosZ, Float:objeRotX, Float:objeRotY, Float:objeRotZ, InteriorID, VirtualWorld)
forward hrp_SaveObject(object_id)
forward hrp_DeleteObject(object_id)

forward CreateBusStop(BusName(32), Float:BusPosX, Float:BusPosY, Float:BusPosZ)
forward LoadBusStops()
forward SaveBusStop(busstop_id)
forward DeleteBusStop(busstop_id)

forward AddPhotoRadar(Float:PosX, Float:PosY, Float:PosZ, Float:MaxSpeed)
forward LoadPhotoRadars()
forward SavePhotoRadar(photoradar_id)
forward DeletePhotoRadar(photoradar_id)

forward AddGangZone(Float:MinX, Float:MinY, Float:MaxX, Float:MaxY)
forward LoadGangZones()
forward SaveGangZone(gangzone_id, what)
forward DeleteGangZone(gangzone_id)

forward OnPlayerDutyStart(playerid, DutyType, DutyTypeUID)
forward OnPlayerDutyStop(playerid)

forward SetPlayerNormalColor(playerid)
forward UpdatePlayerStatus(playerid)

forward OnBasketBallFallingDown(objectid, Float:FallTargetX, Float:FallTargetY, Float:FallTargetZ)

forward LoadPlayerAccess(playerid)
forward UpdatePlayerUnitPositions(playerid)

forward CreateGroup(GroupName())
forward SaveGroup(group__id)
forward DeleteGroup(group__id)
forward LoadGroups()
forward LoadBooths()
forward LoadPetrols()
forward LoadPhones()
forward LoadHomephones()
forward ReloadGroup(group__id)
forward ShowPlayerGroupInfo(playerid, group__id)

forward LoadPlayerGroups(playerid)
forward LoadPlayerPunish(playerid)

forward CreatePlayerCorpse(playerid, killer_uid, weapon_uid)

forward CreateAnn(group_uid, author_uid, content())

forward OnPlayerClickTextDraw(playerid, Text:clickedid)

forward UnloadWood(playerid, vehid, group__id, item_count)
forward UnloadRocks(playerid, vehid, group__id, item_count)

forward OnPlayerPickChar(playerid)
forward OnPlayerSwitch(playerid, charuid)
forward DisconnectChar(playerid, reason)
forward ChangeSwitchingCamera(playerid, stage)

CameraFirstPerson(MAX_PLAYERS)
forward SyncCamera(playerid)
forward CheckCameraPosition(playerid)
forward ToggleThirdPerson(playerid)
forward SetThirdPerson(playerid, status)
forward GetViewMode(playerid)

forward setupBots()


// News
weather = 10

TruckersTicks = 0

Logged(MAX_PLAYERS)
Spawned(MAX_PLAYERS)
Uid(60000)
LoginTime(MAX_PLAYERS)(3)
StatsProtection(MAX_PLAYERS)
LogTime(MAX_PLAYERS)
SpawnTime(MAX_PLAYERS)

Preloaded(MAX_PLAYERS)
MainPlayerTable(MAX_PLAYERS)   // G³ówna tablica, s³u¿y do przypisywania w wiêkszoœci dzia³aniach ró¿nych wartoœci
SecondPlayerTable(MAX_PLAYERS)   // Tablica dodatkowa, s³u¿y do przypisywania w wiêkszoœci dzia³aniach ró¿nych wartoœci
MainPlayerStringTable(MAX_PLAYERS)(128)   // G³ówna tablica, s³u¿y do przypisywania w wiêkszoœci dzia³aniach ró¿nych wartoœci STRING

PlayerHelpStep(MAX_PLAYERS)

Checkpoint(MAX_PLAYERS)
ChangePickup(MAX_PLAYERS)

ChangingRank(MAX_PLAYERS)

WBCpress(1280)

playerIP(MAX_PLAYERS)(32)		//tabela na reconnecty

OrderProductUID(MAX_PLAYERS)
OrderProductName(MAX_PLAYERS)(32)
OrderProductPrice(MAX_PLAYERS)
OrderProductNumber(MAX_PLAYERS)

CommandTickCount(MAX_PLAYERS)

OnVehicleSave(MAX_VEHICLES)
Float:VehiclePos(MAX_VEHICLES)(3)

Float:RaceCheckpoint(MAX_RACE_CP)(3)
OnPlayerSave(MAX_PLAYERS)

DSEBlockade(10)
PoliceBlockade(20)
PolicePole(30)
PoliceSpikes(5)
PoliceDetour(10)
PoliceFlare(20)
PoliceJump(5)
PoliceLadder(10)
PoliceLine(20)
TruckLine(20)
PoliceCaution(40)
PoliceFireLine(20)
PoliceHesco(10)
FBIBlockade(20)

// Dla FD
FDWreck(5)
FDFire(5)

/*
UsingRadio = 0
AdvertiseTime = 0
*/

AdminLogTime = 0
PunishTime = 0

bool:GlobalGod = false
bool:CheckSumCheck = true

JobPickup = -1
MarihuanaGangPickup = -1
AmpGangPickup = -1
MetaampGangPickup = -1
PressPickup = -1
WeaponPointPickup = -1

// aktorzy
WeaponPointActor = -1

// aktualna pogoda
CurrentWeather
WeatherTicks = 59
WeatherDayType = 0
WeatherTemperature = 0
QuakeTimer = 0

// Text Draws
Text:TextDrawServerLogo

// Timery
/*tMinute = -1
tSecond = -1
tHalf = -1
tQuarter = -1*/

// Gotowanie narkotyków
PlayerText:ActionCook(MAX_PLAYERS)
PlayerText:ActionAdd(MAX_PLAYERS)
PlayerText:ActionClose(MAX_PLAYERS)
PlayerText:CookBG(MAX_PLAYERS)
PlayerText:CookInfo(MAX_PLAYERS)
PlayerText:CookThing(MAX_PLAYERS)
PlayerText:CookIngredients(MAX_PLAYERS)
PlayerText:CookIngredient(MAX_INGREDIENTS)(MAX_PLAYERS)

// Nowy infobox
PlayerText:TextDrawInfoNewContent(MAX_PLAYERS)
Text:TextDrawInfoNew

// Posiad³oœæ kupiona!
PlayerText:TextDrawPropertyFade1(MAX_PLAYERS)
PlayerText:TextDrawPropertyFade2(MAX_PLAYERS)
PlayerText:TextDrawPropertyMSG(MAX_PLAYERS)

//karty + stó³

Text:TextDrawAdmin
Text:TextDrawAdminMode(MAX_PLAYERS)

Text:TextDrawMainInfo(MAX_PLAYERS)

Text:TextDrawOfferBack
Text:TextDrawOfferTitle(MAX_PLAYERS)

PlayerText:TextDrawDoorInfo(MAX_PLAYERS)
Text:TextDrawWindow(MAX_PLAYERS)
Text:TextDrawHeadbag(MAX_PLAYERS)
Text:TextDrawHitscreen(MAX_PLAYERS)

Text:TextDrawFuelBack
PlayerText:TextDrawFuelContent(MAX_PLAYERS)

Text:TextDrawTemperature
Text:TextDrawPremium
Text:TextDrawSanNews
Text:TextDrawRadio(MAX_RADIO)

Text:TextDrawAudioError

Text:TextDrawAdminLog
Text:TextDrawPunishInfo

Text:TextDrawEditorBack
Text:TextDrawEditorTitle(MAX_PLAYERS)

Text:TextDrawDamage(MAX_PLAYERS)

Text:TextDrawFlashbang(MAX_PLAYERS)

Text:TextDrawSwitching

/*
Text:TextDrawAKill
Text:TextDrawAKick
Text:TextDrawABan
Text:TextDrawARun
Text:TextDrawAVeh
Text:TextDrawAFreeze
Text:TextDrawAGethere
Text:TextDrawAGoto
Text:TextDrawASlap
Text:TextDrawARespawn
Text:TextDrawABW
Text:TextDrawAChill
Text:TextDrawASpec
Text:TextDrawAUlti
Text:TextDrawAExit
*/

Text:DashboardBG(4)
Text:DashboardOption(12)

PlayerText:PDT_BG(MAX_PLAYERS)
PlayerText:PDT_1(MAX_PLAYERS)
PlayerText:PDT_2(MAX_PLAYERS)
PlayerText:PDT_3(MAX_PLAYERS)
PlayerText:PDT_4(MAX_PLAYERS)
PlayerText:PDT_5(MAX_PLAYERS)
PlayerText:PDT_6(MAX_PLAYERS)
PlayerText:PDT_7(MAX_PLAYERS)
PlayerText:PDT_8(MAX_PLAYERS)
PlayerText:PDT_9(MAX_PLAYERS)
PlayerText:PDT_Back(MAX_PLAYERS)


PlayerText:TextDrawCardWelcome(MAX_PLAYERS)
PlayerText:TextDrawCardTable(MAX_PLAYERS)
/* poker
PlayerText:TextDrawTableMSG1(MAX_PLAYERS)
PlayerText:TextDrawActionWindow(MAX_PLAYERS)
PlayerText:TextDrawTableCardOne(MAX_PLAYERS)
PlayerText:TextDrawTableCardTwo(MAX_PLAYERS)
PlayerText:TextDrawTableCardThree(MAX_PLAYERS)
PlayerText:TextDrawTableCardFour(MAX_PLAYERS)
PlayerText:TextDrawTableCardFive(MAX_PLAYERS)
PlayerText:TextDrawTableMSG2(MAX_PLAYERS)
PlayerText:TextDrawPlayerCardOne(MAX_PLAYERS)
PlayerText:TextDrawPlayerCardTwo(MAX_PLAYERS)
PlayerText:TextDrawTableCash(MAX_PLAYERS)
PlayerText:TextDrawActionCheck(MAX_PLAYERS)
PlayerText:TextDrawActionBed(MAX_PLAYERS)
PlayerText:TextDrawActionFold(MAX_PLAYERS)
*/
// nowy interfejs
PlayerText:TextDrawMainItems(MAX_PLAYERS)
PlayerText:TextDrawItem(MAX_PLAYERS)(10)
PlayerText:TextDrawItemTitle(MAX_PLAYERS)
PlayerText:TextDrawItemNext(MAX_PLAYERS)
PlayerText:TextDrawItemPrev(MAX_PLAYERS)
PlayerText:TextDrawItemCancel(MAX_PLAYERS)

// nowe telefony
PlayerText:TextPhoneCorner1(MAX_PLAYERS)
PlayerText:TextPhoneCorner2(MAX_PLAYERS)
PlayerText:TextPhoneCorner3(MAX_PLAYERS)
PlayerText:TextPhoneCorner4(MAX_PLAYERS)
PlayerText:TextPhoneBackground(MAX_PLAYERS)
PlayerText:TextPhoneBorder1(MAX_PLAYERS)
PlayerText:TextPhoneBorder2(MAX_PLAYERS)
PlayerText:TextPhoneWallpaper(MAX_PLAYERS)
PlayerText:TextPhoneButton(MAX_PLAYERS)
PlayerText:TextPhoneHeading(MAX_PLAYERS)
PlayerText:TextPhoneName(MAX_PLAYERS)
PlayerText:TextPhoneHeadset(MAX_PLAYERS)
PlayerText:TextPhoneTime(MAX_PLAYERS)
PlayerText:TextPhoneBattery1(MAX_PLAYERS)
PlayerText:TextPhoneBattery2(MAX_PLAYERS)
/*PlayerText:TextPhoneTile1(MAX_PLAYERS)
PlayerText:TextPhoneTile2(MAX_PLAYERS)
PlayerText:TextPhoneTile3(MAX_PLAYERS)
PlayerText:TextPhoneTile4(MAX_PLAYERS)
PlayerText:TextPhoneTile5(MAX_PLAYERS)
PlayerText:TextPhoneTile6(MAX_PLAYERS)*/
PlayerText:TextPhoneBtnCard(MAX_PLAYERS)
PlayerText:TextPhoneBtnCall(MAX_PLAYERS)
PlayerText:TextPhoneBtnSms(MAX_PLAYERS)
PlayerText:TextPhoneBtnContacts(MAX_PLAYERS)
PlayerText:TextPhoneBtnAdd(MAX_PLAYERS)
PlayerText:TextPhoneBtnExit(MAX_PLAYERS)
PlayerText:TextPhoneBtnSett(MAX_PLAYERS)
PlayerText:TextPhoneDate(MAX_PLAYERS)

//slots
PlayerText:TextDrawSlotsFirst(MAX_PLAYERS)
PlayerText:TextDrawSlotsSecond(MAX_PLAYERS)
PlayerText:TextDrawSlotsThird(MAX_PLAYERS)

PlayerText:AdminSpecInfo(MAX_PLAYERS)
PlayerText:AdminSpecStats(MAX_PLAYERS)

// Nowy interfejs prawa jazdy - hehe, zajebisty
PlayerText:pLicenseBall1(MAX_PLAYERS)
PlayerText:pLicenseBall2(MAX_PLAYERS)
PlayerText:pLicenseBall3(MAX_PLAYERS)
PlayerText:pLicenseBall4(MAX_PLAYERS)
PlayerText:pLicenseBack(MAX_PLAYERS)
PlayerText:pLicenseBorder1(MAX_PLAYERS)
PlayerText:pLicenseBorder2(MAX_PLAYERS)
PlayerText:pLicenseBorder3(MAX_PLAYERS)
PlayerText:pLicenseBorder4(MAX_PLAYERS)
PlayerText:pLicenseStar(MAX_PLAYERS)
PlayerText:pLicenseHeading1(MAX_PLAYERS)
PlayerText:pLicenseHeading2(MAX_PLAYERS)
PlayerText:pLicenseInfo(MAX_PLAYERS)
PlayerText:pLicenseLine(MAX_PLAYERS)
//PlayerText:pLicenseButton(MAX_PLAYERS)

// Radio
//PlayerText:TextDrawRadio(MAX_PLAYERS)

Text:LSPad_Frame(22)
Text:LSPad_MenuTD(12)
Text:LSPad_BG(MAX_PLAYERS) // (N) - U¿ywany w stary sposób bo kolejno¶ci siê pierdol±.
PlayerText:LSPad_MenuTDClickable(10)
PlayerText:LSPad_Taskbar(9)
PlayerText:LSPad_Calendar(5)
Text:LSPad_Weather
Text:LSPad_Exit

LSPad_MenuBool(MAX_PLAYERS)
LSPad_MusicStation(MAX_PLAYERS)
LSPad_ReopenAnn(MAX_PLAYERS)
LSPad_ReopenSett(MAX_PLAYERS)
LSPad_DoorIDs(MAX_PLAYERS)(8)
LSPad_CarIDs(MAX_PLAYERS)(8)

Text:LSPad_MusicFrame(12)
Text:LSPad_MusicList(20)
PlayerText:LSPad_MusicTitle
PlayerText:LSPad_MusicVolume

Text:LSPad_MapTD
PlayerText:LSPad_MapMarker

Text:LSPad_SettingsTD(3)
PlayerText:LSPad_SettingsCode
Text:LSPad_SettingsWP(24)

Text:LSPad_LocksTD(2)
PlayerText:LSPad_LocksNames(8)
PlayerText:LSPad_LocksUnlock(8)
PlayerText:LSPad_LocksLock(8)

Text:LSPad_BankFrame(4)
PlayerText:LSPad_BankInfo(6)

// Itterators
Iterator:Vehicles(MAX_VEHICLES)
Iterator:Doors(MAX_DOORS)

Iterator:Items(MAX_ITEM_CACHE)
Iterator:Products(MAX_PRODUCTS)

Iterator:GangZones(MAX_GANG_ZONES)

Iterator:Groups(MAX_GROUPS)
Iterator:Packages(MAX_PACKAGES)
Iterator:LimitedPackages(MAX_PACKAGES)
Iterator:Booths(MAX_BOOTHS)
Iterator:Petrols(MAX_BOOTHS)

Iterator:Quiters(MAX_PLAYERS)
Iterator:Phones(MAX_PHONES)
Iterator:Plants(MAX_PLANTS)
Iterator:Cards(MAX_CARDS)
Iterator:Calls(MAX_CALLS)

Iterator:Gangbang(MAX_GANGBANGS)
// BlackJack iterator in lib\caisno\blackjack

Tick(MAX_VEHICLES)

LastUpdatedVehicle(MAX_PLAYERS)
Float:OldVehiclePosition(MAX_VEHICLES)(3)

//pName - charname
//pGlobalName - oocname

// Enums
enum sPlayer
(
	pUID,
	pGID,

	bool:pSwitching,
	Float:pSwitchingX,
	Float:pSwitchingY,
	Float:pSwitchingZ,
	Float:pSwitchingDX,
	Float:pSwitchingDY,
	Float:pSwitchingDZ,
	pSwitchingStage,
	pLastSwitch,

	pIGDBID,
	pIGTimeIn,
	
 	pName(MAX_PLAYER_NAME),
 	pGlobalName(64),
 	
 	pNickColor,
 	
 	pPremium,
	pPremiumTime,

	pAASlot,
 	
 	pAdmin,
 	bool: pAdminDuty,
	bool: pAdminToken,
	pUserColor,
	pClicked,
 	
 	pHours,
 	pMinutes,
 	
 	pSkin,
	Float:pHealth,
	Float:pArmour,
	pArmourDelay,
	
	pSex,
	pBirth,
	
	pCash,
	pBankCash,
	pChecksum,
	
	pBlockChecksum,
	
	pBankNumber,
	pBankLastTransaction,
	
	pWarns,
	
	pInt,
	pVW,
	
	pBW,
	pBleeding,
	pWounded,
	pInsurance,
	pInsuranceCompany,
	pInsuranceCount,
	pHospitalization,
	pHospitalCharge,
	pHospitalBed,
	pAJ,
	
	pBlock,
	
	Float:pPosX,
	Float:pPosY,
	Float:pPosZ,

	pRegion,
	
	pHotel,
	
	pGroupDuty,
	pGroupDutyTime,
	pMainGroupSlot,
	
	pDutyUID,
	
	pDocuments,
	
	pPDP,
	
	pPhoneNumber,
	
	pArrest,
	pArrestTime,
	pArrestDay,

	pSpawnPlace,
	pHouse,
	pFamilyHouse,
	
	pFightingStyle,
	pGamePoints,
	
	pLogTries,
	
	pCarSpawned,
	
	pLastVeh,
	
	pTaxiVeh,
	pTaxiPay,
	pTaxiPrice,
	pTaxiPassenger,
	
	pWalkAnim,

	pShowItems,
	pTrackingNumber,
	
	pKiller,
	pKillerWeapon,
	
	// Maska
	pMaskUID,
	
	// Kamizelka
	pArmorUID,

	// Naprawia pojazd
	pRepairVeh,
	pRepairType,
	pRepairTime,
	
	// Wymiana opony
	pTireVeh,
	pTireTime,
	
	// Pompowanie pojazdu
	pPumpVeh,
	pPumpTime,
	
	// Pompowanie opony z przedmiotu
	pOPumpItem,
	pOPumpTime,
	
	// Lakieruje pojazd
	pSprayType,
	pSprayVeh,
	pSprayTime,
	pSprayColor(2),
	
	// Montuje czêœæ
	pMontageVeh,
	pMontageTime,
	pMontageItem,
	
	pCuffed,
	pCuffedStill,
	
	pRoped,		//zwi¹zany
	
	pBagged,		// czy ma worek na glowie
	
	pGagged,		//czy knebel w gêbie ma
	
	pSearches,
	pSearchTime,
	
	pHealing,
	
	bool: pTogW,
	bool: pTogBo,
	bool: pTogRo,
	
	pLastW,
	pLastWTo,
	
	pAFK,
	
	bool: pPlayAnim,
	bool:pWoundAnim,
	
	pSpectate,
	pSpectateChange,
	
	pCall,
	pAlarmCall,
	pSerivceNumberAs,
	bool:pUsingBooth,
	
	// AntyUnFreeze
	pFreeze,
	
	Float:pFreezePosX,
	Float:pFreezePosY,
	Float:pFreezePosZ,
	
	pWoundedTime,
	
	pShowDoorText,
	pShowInfoText,
	
	pAudioHandle,
	pAudioVolume,
	pRingToneHandle,
	
	// Anty AirBreak
	pAirBrkWarns,
	pGotAirBrkPos,
	
	// Anty WallRide
	pWallRideWarns,
	
	pGymPass,
	pPaintballPass,
	pGymObject,
	pGymType,
	pGymPhase,
	pGymValue1,
	pGymValue2,
	
	pGymNutrient,
	pGymFactor,
	
	pTrainTime,
	pPaintballTime,
	
	pPreviewTime,
	
	pLive,
	pInterview,
	
	pLastPay,
	pLastReport,
	
	bool: pRaising,
	
	pJob,
	pFed,
	
	pDrivingLesson,
	pDoorFreeze,
	
	bool: pBelts,
	bool: pGloves,
	bool: pRoll,
	
	pDrunkLevel,
	
	pCrash,
	pQSing,
	pStatus,
	
	pManageItem,
	pPlayerIDOffer,
	
	bool: pAiming,
	
	// Kurier
	bool: pPackage,
	pPackageUID,
	pWholeSale,
	
	// Sweeper
	bool: pSweep,
	pSweepRoute,
	pSweepSteps,
	pSweepStep,
	pSweepTime,
	
	// Rybak
	bool: pFish,
	pFishingRodUID,
	bool: pFishTaking,
	
	// Bus
	bool: pBusRide,
	pBusStart,
	pBusPrice,
	pBusTravel,
	pBusTime,
	
	// Wybór skina
	bool: pClothChanging,
	pClothID,
	
	// Wybór akcesorii
	bool: pAccessChanging,
	pAccessID,
	pAccessShop,
	
	bool: pAccessEditing,

	// Wyœcigi
	pRacePhase,
	pRacePoint,
	pRaceCheckpoints,
	
	// Umiejêtnoœci postaci
	Float:pDriving,
	Float:pCondition,
	Float:pShooting,
	Float:pFishing,
	Float:pStrength,
	
	// Nauczone style
	pKnownStyles,
	pDailyReps,
	
	Float:pDependence,
	pSkillShowed,
	
	// Koszykówka
	pBasketBall,
	pBasketID,
	bool: pHavingBall,
	bool:pPlayBasket,
	pBallTicks,
	pBallThrowPhase,
	
	pBallPhase,
	pBasketTeam,
	
	bool: pSmokeJoint,
	pSmokeReps,
	pSmokeLevel,
	
	pDrugLevel,
	pMusicPlayerUID,
	
	Float:pCheatPosX,
	Float:pCheatPosY,
	Float:pCheatPosZ,
	
	pMove3DText,
	pMove3DTextPhase,
	
	pMoveObject,
	pMoveObjectPhase,
 	
	Text3D:pNameTag,
	pDescTagText(128),
	
	pPlayerIgnored(MAX_PLAYERS),
	bool: pUsingOptiwand,
	
	// Admin stuff
	bool: pAdminChat,
	bool: pChangeName,
	
	// BLOCK_RUN bypass
	pEnteringVeh,
	
	// Timer textdrawa z flashbangiem
	pFlashed,
	
	// Sex
	bool:pHavingSex,
	pSexType,
	pSexReps,
	pSexTime,
	
	// Tankowanie
	pFueling,
	
	pVehCollisions,
	
	// Nowe efekty dragów
	bool:pRage,
	pRageTime,
	pRageDrug,
	pRageDrunkLevel,
	pRageDrugUse,
	Float:pRageStrength,
	
	// Nowe/me nad g³ow¹
	//Text3D:pMeTag,
	//pMeTime,
	
	// Czas od ostatniego /osel (model)
	pOselLimit,

	// Gangzone pokazane?
	bool:pGangZoneShowing,
	
	// Id samochodu z którego s³ucha muzyki
	pCarMusic,
	
	// Typ quita
	pQuit,
	
	// Czy gracz taguje ?
	pTagging,
	pTaggingFont,
	pTaggingSize,
	
	// U¿ywane dla PD do nawigacji po menu
	pPDMenu,
	pPDSuspect,
	
	pLogTime,
	
	pFlood,
	
	pDialog,
	
	pAdminMode,
	
	pLastWoodHit,
	
	pKillCount,
	
	pWeaponWarning,
	bool:pWeaponCheckFreeze,
	pAmmoWarning,
	
	pWiretap,

	pCasinoGameType,
	pCasinoGameID,

	pLSPadItemID,
	bool:pUsingTablet,

	bool:pShowingZones,
	
	bool:pTogOOC,
	
	bool:pRead,
	pPressStage,

	bool:pSpread,		//czy gazety roznosi
	pSpreadTime,		//ilosc sekund 
	
	bool:pPut,
	
	bool:pSlots,		//czy w slotsy gra
	pSlotID,		//id maszyny na ktorej gra
	pSlotTicks,
	
	pCallTicks,
	
	pTrackID,		//uid trasy z bazy
	bool:pTrucking,		//czy aktualnie ma zlecenie jakieœ
	pPackingTime,		//czas za³adunku lub wyladunku
	pPackingPhase,
	pTrailerID,
	
	pUnloadPos(32),		//pozycja wyladowywania
	pBusinessCard,
	
	pSurfID,		//
	
	bool:pDive,
	
	pLoginEx,		//¿eby za czêsto nie prze³adowywali )
	bool:pReconnect,
	
	pItemPage,	//ID strony z przedmiotami
	pInterface,		//typ interfejsu
	bool:pUseGUI,		//czy uzywa gui
	pSelectItem,		//u¿yty item
	
	pHireTime,
	pHireGroup,
	
	pBombTime,  //czas pozostaly do konca montowania bomby
	pBombID, // id przedmiotu
	pBombPhase,	//typ brojenia/rozbrojenia
	pBombFound, 		//czy bombê znalaz³
	
	pCurrentZone, 
	pLastZone,
	pZoneTicks,
	
	pEMatSize,		// edycja tekstów - matsize
	pEMatFont(32),	//edycja tekstów - fontface
	pEMatBold,		// edycja tekstów - pogrubienie
	pEMatFontSize, 		// edycja tekstów - rozmiar czcionki
	
	pJourneyID, 		// ID wozu w którym gracz teraz siedzi
	
	pScouredID,		// ID obiektu, który w³aœnie usuwa
	bool:pScouring,		// czy usuwa teraz tag
	
	pCurrentGUI, 
	
	bool:pWormed,
	pPicking, 							// czas kopania
	
	bool:pCourse,			//czy jest w trakcie DMV
	pCourseCP,			//aktualny checkpoint
	pCourseVeh, 			// ID wozu którym kursuje
	Float:pCourseMS,			//max speed
	Float:pCourseHP,		//hp wozu
	
	pDailyIncome,			// kaska ile sobie dziennie moze przepracowa
	
	pViewDoorID,
	pViewTime,
	pBuyCount,	
	
	pBandaged,			// ID banda¿owanego gracza
	pBandageTime,		// Czas banda¿owania
	
	pStation,		
	pStationLive,			// czy nadaje live dla swojej stacji
	
	pCaptcha(16),						// Captcha
	pSendingCaptcha(128),			// Tresc wiadomosci
	
	pOfferedUID,					// dodatkowe zabezpieczenie
	bool:pGod,
	
	pCorner,			// ID cornera
	bool:pDrugDealing,
	bool:pSelling,
	
	pSearching,		// szuka FBI kogos
	pSearchingTime,	// czas do konca szukania
	
	bool:pFPS,			// czy 1-osobowy
	
	pDailyDrugs,			// sprzedane narkotyki bierz¹cego dnia
	
	pSparing,			// Id gracza z którym siê klepiemy
	
	pPhoneAction,		// co robi w telefonie
	
	pTalkedNPC,		// z którym NPC gada
	pTalkedPhase,	// faza rozmowy
	
	pCarsTP,			// AC do pojazdów
	
	bool:pBusinessShow,			// Czy biznesy widzi na minimapie
	
	pFocusedID,				// ID Gracza, który jest teraz focusowany
	
	bool:pLauncherLogged,
	
	bool:pPhoneMuted,		// Czy telefon wyciszony
	
	pCarryBox,
	pCarryTries,
	pCarryBoxPhase,
	pCarryPoint,
	
	bool:pVerificated,
	
	bool:pArmorDisplay,
	
	pCorpID,
	pCorpType,
	pCorpAnswer(24),
	
	bool:pCeleb,		// czy gracz jest celebryt¹
	
	pBlackJackID,
	
	pBlockShooting, // czy dosta³ postrza³ w rêkê
	
	pCookID,		// ID kuchenki na której gotuje (-1 default)
	
	pPrisonWork,
	pWorkingNow,
	pWorkingPhase,
	pWorkingRepeat,
	pWorkingTimeLeft,
	pWorkRepeat,
	
	pInterviewSlot,

	pFCK
)
PlayerCache(MAX_PLAYERS)(sPlayer)

PlayerDamageCache(MAX_PLAYERS)(10)

enum sCards
(
	cardUID,
	cardGroup,
	cardLimit,
	cardBalance
)

Cards(MAX_CARDS)(sCards)

// ARKHIR
enum sPlayerWeapon 
(
	// Broñ w rêku
	bool: pEquipped,
	bool: pShot,
	
	pWeaponUID,
	pWeaponID,
	pWeaponAmmo,
	pLastAmmo
)
WeaponCache(MAX_PLAYERS)(3)(sPlayerWeapon)

enum sCarInfo
(
	cUID,
	cModel,

	cName(32),

	Float:cPosX,
	Float:cPosY,
	Float:cPosZ,
	Float:cPosA,
	
	// Pozycje do rêcznego.
	Float:cEPosX,
	Float:cEPosY,
	Float:cEPosZ,
	Float:cEPosA,
	
	cInteriorID,
	cWorldID,

	cColor1,
	cColor2,

	cOwner,
	cOwnerType,

	Float:cHealth,
	cVisual(4),

	Float:cFuel,
	Float:cMileage,
	cFuelType,
	
	cWheelBlock,

	bool: cEngineTogged,
	
	bool: cLocked,
	bool: cSpawned,
	
	cTowedVeh,
	
	cPaintJob,
	cAccess,
	
	cComponent(14),
	cAudioURL(64),
	
	cPoliceSiren,
	
	bool: cRegister,
	bool: cWindowOpen,
	
	cDriverWindowOpen,
	cPassengerWindowOpen,
	cLeftWindowOpen,
	cRightWindowOpen,
	
	cRadioCanal,
	bool: cGPS,
	
	bool:cBlocked,
	
	cOwnerExitTime,
	bool:cStrobe,
	
	Float:cCarfax,
	bool:cEBreak,
	
	bool:cTop,			//czy dach ma za³o¿ony czy nie
	
	Float:cBoost,
	bool:cArmed,		//czy bombe ma
	
	cPoliceGrill, 	// stroboskop na grillu
	bool:cFlashed,		//czy stroboskopy w œwietle w³¹czone
	cFlashPhase,
	
	bool:cPilotTick,	// czy w³aœnie ktoœ go mykn¹³ pilotem
)
CarInfo(MAX_VEHICLES)(sCarInfo)

enum sDoorCache
(
	dUID,

	dOwnerType,
	dOwner,

	Float:dEnterX,
	Float:dEnterY,
	Float:dEnterZ,
	Float:dEnterAng,
	dEnterInt,
	dEnterVW,

	Float:dExitX,
	Float:dExitY,
	Float:dExitZ,
	Float:dExitAng,
	dExitInt,
	dExitVW,

	dLocked,
	dPickupID,
	dName(32),
	
	dAudioURL(128),

	dEnterPay,
	bool: dGarage,
	
	dAccess,
	dBurnTime,
	bool:dBell,
	
	dFireObject,
	Text3D:dFireLabels,
	
	dWood,
	dRock,
	dElock,
	dTime,
	
	bool:dBlocked,
	dLimit,
	
	dCost,		// koszt drzwi
	
	bool:dPaintball, // hala na paintball
	
	dDoorEdited
)

// Pamiêtaj ¿eby te¿ zmieniæ sDoorCache i LoadDoors !!!
enum sDoorData
(
	dUID,

	dOwnerType,
	dOwner,

	Float:dEnterX,
	Float:dEnterY,
	Float:dEnterZ,
	Float:dEnterAng,
	dEnterInt,
	dEnterVW,

	Float:dExitX,
	Float:dExitY,
	Float:dExitZ,
	Float:dExitAng,
	dExitInt,
	dExitVW,

	dLocked,
	dPickupID,
	dName(32),
	
	dAudioURL(128),

	dEnterPay,
	bool: dGarage,
	
	dAccess,
	dBurnTime,
	bool:dBell,
	
	dFireObject,
	Text3D:dFireLabels,
	
	dWood,
	dRock,
	dElock,
	bool:dRobbed,
	
	dTime,
	
	bool:dBlocked,
	dLimit,
	
	dCost,		// koszt drzwi
	
	bool:dPaintball, // hala na paintball
	
	dDoorEdited
)
DoorData(MAX_DOORS)(sDoorData)

enum sPhone
(
	phoneUID,
	phoneNumber,
	Float:phonePosX,
	Float:phonePosY,
	Float:phonePosZ,
	phoneWorld,
	phoneInterior,

	bool:phoneBusy,
	phoneConvo
)
Phones(MAX_PHONES)(sPhone)

enum sPlants
(
	plantUID,
	plantName(64),
	plantType,
	plantTicks,
	plantGrowth,
	plantSun,
	plantWater,
	plantQuality,
	Float:plantPosX,
	Float:plantPosY,
	Float:plantPosZ,
	plantInt,
	plantVW,
	Text3D:plantLabel
)
Plants(MAX_PLANTS)(sPlants)

enum hPhone
(
	hPhoneNumber,
	hDoorUID,
	hWorld,

	bool:hphoneBusy,
	hphoneConvo
)
HomePhones(MAX_HOMEPHONES)(hPhone)

enum sCalls
(
	caller,
	called,
	callerNumber,
	calledNumber,
	callerDevice,
	calledDevice,
	callerDevID,
	calledDevID,
	bool:convo,
	callTime
)
Call(MAX_CALLS)(sCalls)

enum sItemData
(
	iUID,
	iName(32),
	
	iValue1,
	iValue2,
	iType,
	Float:iWeight,
	
	iPlace,
	iOwner,
	
	iUsed,
	bool: iChecked
)
ItemInfo(MAX_ITEM_CACHE)(sItemData)

enum sQuitInfo
(
	Text3D:qLLabelID,
	qLTime
)

QuitInfo(MAX_PLAYERS)(sQuitInfo)

enum sRegionInfo
(
	rName(16),
	Float:rPosX,
	Float:rPosY,
	Float:rPosZ,
	Float:rPosA
)
RegionInfo(3)(sRegionInfo) =
(
	/* nazwa		  |	posX	|	posY   |  posZ  |  rotA */
	//(Centrum,			837.9846,  -1341.8937, 7.1719,  167.8357),
	//(Centrum,			1085.9253,-1370.5439,13.7813),
	//(Centrum, 1003.1159,-1345.3027,13.5341),
	(Centrum, 1460.5184, -1548.9999, 13.5668, 90.1884), // Pershing Square seler
	(South-Central,	1743.0443, -1863.2510, 13.5753, 355.9145),
 	(Obrze¿a miasta,	660.8438,  -573.0786,  16.3359, 177.3012)
)

enum sGunRegionInfo
(
	grName(32),
	Float:grPosX,
	Float:grPosY,
	Float:grPosZ,
	grTolerance,
)

GunRegionInfo(45)(sGunRegionInfo) =
(
	/* 		nazwa		 |	posX   |	 posY   | posZ | tolerancja */
	(stacja Idlewood, 1938.1045, -1772.2850, 13.0075, 2),
	(centrum Ganton, 2483.9131, -1669.7698, 12.9647, 5),
	(niebieskie bloki Ganton, 2298.8291, -1782.8435,13.1773 , 5),
	(boiska ko³o Grape Street, 2308.7378, -1526.4301,24.9686, 5),
	(Grape Street, 2210.5266, -1442.5980, 23.4431, 5),
	(13th street, 2373.7241, -1302.0630, 23.4570, 5),
	(Los Flores, 2624.1797,-1254.0232,48.8235, 5),
	(East Beach, 2883.2344, -1418.7383, 10.6617, 5),
	(LS Forum, 2686.2759, -1690.3483, 9.0659, 2),
	(Seville, 2715.5984, -1993.4844, 13.0289, 5),
	(Ocean Docks, 2438.6418, -2470.9712, 13.2580, 10),
	(Willowfield, 2266.9832, -1892.3342, 12.9896, 5),
	(LS Airport, 1732.3317, -2394.5027, 13.1797, 1),
	(El Corona, 1820.8923, -2112.3960, 13.0076, 5),
	(Unity Station, 1813.7850, -1861.8033, 13.1566, 2),
	(Alhambra, 1827.5405 ,-1687.4658, 13.1290, 2),
	(pizzeria na Idlewood, 2097.4480, -1765.0869, 13.1902, 3),
	(Glen Park, 1972.4663, -1186.9182, 25.4339, 5),
	(Las Collinas, 2163.5503, -1004.5039, 62.4200, 5),
	(Jefferson, 2212.3911, -1219.5061, 23.4412, 5),
	(Downtown, 1473.6417, -1098.4784, 23.4529, 2),
	(Central Ave., 1453.4650, -1490.1060, 12.9952, 2),
	(Pershing Square, 1482.8035, -1675.2338, 13.6823, 1),
	(Legal Club, 1316.3212, -1707.2937, 13.0049, 1),
	(centrum handlowe, 1112.1998, -1391.4575, 13.0747, 1),
	(szpital, 1198.2156, -1326.9536, 13.0233, 1),
	(siedziba WBC, 922.0455, -1440.7124, 13.0608, 1),
	(Market Station, 808.1282, -1334.9757, 13.1698, 1),
	(Cmentarz, 915.9384, -1102.9211, 23.9218, 3),
	(Aleja Gwiazd wschód, 1254.7454, -1142.9219, 23.2811, 1),
	(Aleja Gwiazd zachód, 1006.1722, -1146.5288, 23.3894, 1),
	(Rodeo wschód, 623.6810, -1527.9463, 14.6209, 3),
	(Rodeo zachód, 337.1937, -1551.2986, 32.7207, 3),
	(Verona Beach, 366.9433, -1818.7592, 7.2837, 3),
	(Santa Maria Beach, 627.7790, -1867.5392, 4.4293, 3),
	(Marina, 746.2892, -1646.1876, 5.0964, 3),
	(Conference Center, 1173.4907, -1759.6736, 13.0279, 2),
	(Ammu-Nation, 1364.7225, -1283.8179, 13.1716, 2),
	(Stacja Mullholand, 1011.6169, -941.4313, 41.7679, 2),
	(Vinewood, 1253.1919, -728.3937, 94.0441, 2),
	(Richman wschód, 680.4056, -1044.7137, 49.8149, 2),
	(Richman zachód, 301.9560, -1292.2285, 53.7326, 2),
	(Verdant Bluffs, 1258.1860, -2039.9333, 59.0953, 3),
	(Temple, 1213.9253, -1037.8287, 31.3591, 3),
	(Dillimore, 657.5687,-562.9366,22.1478, 3)
)

ShootsFired(sizeof(GunRegionInfo))
ShootsCountdown(sizeof(GunRegionInfo))
bool:ShootsFiredInfo(sizeof(GunRegionInfo))

enum sGbang
(
	gbAttackingGroup,
	gbDefendingGroup,
	gbAttackingDeaths,
	gbDefendingDeaths,
	gbZone,
	gbStartTime
)
Gangbang(MAX_GANGBANGS)(sGbang)

enum sItemTypeInfo
(
	iTypeName(32),
	Float:iTypeWeight,
	
	iTypeObjModel,
	
	Float:iTypeObjRotX,
	Float:iTypeObjRotY,
	
	iTypeValueName1(24),
	iTypeValueName2(24)
)
ItemTypeInfo(ITEM_COUNT + 1)(sItemTypeInfo) =
(
	/* nazwa | waga | model | rotx | roty   */
	(Nieokreœlony, 	0.0, 328, 90.0, 95.0),
	(Zegarek, 		0.0, 2710, 0.0,  0.0),
	(Jedzenie, 		0.0, 2769, 0.0,	 0.0),
	(Papierosy, 		0.0, 1485, 0.0,  0.0),
	(Kostka do gry, 	0.0, 328, 90.0, 95.0),
	(Ubranie, 		0.0, 2843, 0.0,  0.0),
	(Broñ, 			0.0, 328, 90.0, 95.0),
	(Amunicja, 		0.0, 328, 90.0, 95.0),
	(Telefon, 		0.0, 330, 90.0,  0.0),
	(Kanister, 		0.0, 1650, 90.0, 0.0),
	(Maska, 			0.0, 328, 90.0, 95.0),
	(Paralizator, 	0.0, 328, 90.0, 95.0),
	(Lakier, 			0.0, 328, 90.0, 95.0),
	(Kajdanki, 		0.0, 328, 90.0, 95.0),
	(Megafon, 		0.0, 328, 90.0, 95.0),
	(Lina, 			0.0, 328, 90.0, 95.0),
	(Pluskwa, 		0.0, 328, 90.0, 95.0),
	(Notes,		   0.0, 2894, 0.0,  0.0),
	(Karteczka,	   0.0, 328, 90.0, 95.0),
	(Tuning,		  0.0, 328, 90.0, 95.0),
	(Ks. Czekowa, 	0.0, 2894, 0.0,  0.0),
	(Czek,			0.0, 328, 90.0, 95.0),
	(Wêdka,		   0.0, 18632, 90.0, 90.0),
	(Torba,		   0.0, 2663, 90.0,  0.0),
	(Napój,		   0.0, 328, 90.0, 95.0),
	(U¿ywka,	   		0.0, 19997, 0.0, 0.0),
	(Joint, 			0.0, 1485, 0.0,  0.0),
	
	(Bletka,		  0.0, 328, 90.0, 95.0),
	(Bongos,		  0.0, 328, 90.0, 95.0),
	(Lufka,		   0.0, 328, 90.0, 95.0),
	
	(Przyczepialny,   0.0, 328, 90.0, 95.0),
	(Akcesoria,	   0.0, 328, 90.0, 95.0),
	(P³yta,		   0.0, 1961, 90.0, 180.0),
	(Odtwarzacz,	  0.0, 328, 90.0, 95.0),
	(Kluczyki,		0.0, 328, 90.0, 95.0),
	(Kamizelka,	   0.0, 328, 90.0, 95.0),
	(Rêkawiczki,	  0.0, 328, 90.0, 95.0),
	(Zw³oki,		  0.0, 19830, 0.0, 0.0),
	(Wiatrówka,	   0.0, 328,  0.0, 0.0),
	(Rolki,		   0.0, 328, 90.0, 95.0),
	(Karnet,		  0.0, 2894, 0.0,  0.0),
	(Mo³otowa,		0.0, 344, 90.0,  0.0),
	(Wytrych,		 0.0, 328, 90.0, 95.0),
	(Optiwand,		0.0, 328, 90.0, 95.0),
	(Craft,		   0.0, 328, 90.0, 95.0),
	(Flashbang,	   0.0, 343, 90.0, 95.0),
	(Latarka,	   0.0, 18641, 90.0, 95.0),
	(Dodatek do broni,	0.0, 328, 90.0, 95.0),
	(Kontrabanda,			0.0, 328, 90.0, 95.0),
	(Akwalung,			0.0, 328, 90.0, 95.0),
	(Opona,				0.0, 328, 90.0, 95.0),
	(Od¿ywka,				0.0, 2709, 0.0, 0.0),
	(Puszka farby,		0.0, 365, 0.0, 0.0),
	(K³oda drewna,		0.0, 18566, 0.0, 0.0),
	(Kamieñ,				0.0, 1303, 0.0, 0.0),
	(Box,					0.0, 328, 0.0, 0.0),
	(Karty,				1.0, 1877, 0.0, 0.0),
	(LSPad,				1.0, 19864, 0.0, 0.0),
	(Zamek Elektroniczny, 1.0, 2922, 0.0, 0.0),
	(Pager,				0.25, 18875, 0.0, 0.0),
	(Lina,				1.50, 328, 90.0, 95.0),
	(Worek,				1.0, 328, 90.0, 95.0),
	(Knebel,				1.0, 328, 90.0, 95.0),
	(Telefon domowy,				1.0, 19629, 0.0,0.0),
	(Czêœæ tuningowa,				4.0, 328, 90.0, 95.0),
	(Gazeta,				1.0, 2894, 0.0,  0.0),
	(Ruletka,				1.0, 328, 90.0, 95.0),
	(Przedmiot odk³adalny,				1.0, 328, 90.0, 95.0),
	(¯ó³te papiery,				1.0, 328, 90.0, 95.0),
	(Nasiona,				0.25, 701, 0.0, 0.0),
	(Karta biznesowa,		0.25, 1581, 0.0, 0.0),
	(Butla z tlenem, 0.25,19580 ,0.0,0.0),
	(Deska surfingowa, 0.25, 2404,0.0,0.0),
	(Bomba, 4.0, 328, 90.0, 95.0),
	(T³umik, 1.5, 328, 90.0, 95.0),
	(Robak, 0.25, 328, 90.0, 95.0),
	(Banda¿, 0.25, 328, 90.0, 95.0),
	(Nasiono, 0.25, 328, 90.0, 95.0),
	(Specjalny, 0.25, 328, 90.0, 95.0),
	(Prezent, 0.25, 328, 90.0, 95.0),
	(Sejf, 10.0, 2332, 0.0, 0.0),
	(Wejsciowka Paintball, 0.25, 2894, 0.0, 0.0),
	(Sk³adnik, 0.25, 19997, 0.0, 0.0),
	(Kuchenka, 10.0, 1271, 0.0, 0.0)
)

enum sOfferTypeInfo
(
	oTypeName(32)
)
OfferTypeInfo(42)(sOfferTypeInfo) =
(
	(Nieokreslona),
	(Przedmiot),
	(Pojazd),
	(Produkt),
	(vCard),
	(Przejazd taxi),
	(Tankowanie),
	(Lakierowanie),
	(Naprawa),
	(Nieruchomosc),
	(Mandat),
	(Holowanie),
	(Leczenie),
	(Reklama),
	(Montaz czesci),
	(PaintJob),
	(Kredyt),
	(Dokument),
	(Nowy pojazd),
	(Biznes),
	(Lekcja jazdy),
	(Zdjecie blokady),
	(Trening),
	(Podatek),
	(Strzelanie),
	(Kluczyki),
	(Wnetrze),
	(Podglad wnetrza),
	(Powitanie),
	(Teren gangu),
	(Rejestracja),
	(Oplata),
	(Sprzedaz hotdoga),
	(Zaladunek),
	(Rozladunek),
	(Naprawa silnika),
	(Naprawa karoserii),
	(Wymiana plynow),
	(Wymiana filtra),
	(Wymiana chlodnicy),
	(Wypozyczenie),
	(Ubezpieczenie)
)

enum sProductData
(
	pUID,
	
	pName(32),
	pType,
	
	pValue1,
	pValue2,
	
	pPrice,
	pNumber,
	
	pDoorUID
)
ProductInfo(MAX_PRODUCTS)(sProductData)

//budki z pras¹
enum pressBoxPars
(
	bUID,
	Float:bPosX,
	Float:bPosY,
	Float:bPosZ,
	bVW,
	bAmount,
	
	Text3D:bText,
)
PressBox(MAX_PRESSBOX)(pressBoxPars)

enum sSettings
(
	Float:MainSpawnPos(4),
	MainSpawnInt,
	MainSpawnVW,
	
	Float:HotelPos(4),
	HotelInt
)
SettingData(sSettings)

enum sGroupTypeInfo
(
	gTypeName(24),
	gMaxDotation,
	
	bool: gChatIC,
	gTypePrice,
	bool: gBell,
)
GroupTypeInfo()(sGroupTypeInfo) =
(
	(Nieokreœlony,			0,		false,	2000,	false),
	(Stacja benzynowa,		0,		false,	30000,	false),
	(Gastronomia,				0,		true,	10000,	false),
	(Bar,						0,		false,	15000,	false),
	(Hotel,					0,		false,	7000,	true),
	(Firma taksówkarska,		0,		false,	25000,	false),
	(Warsztat samochodowy,	0,		false,	18000,	true),
	(Salon samochodowy,		0,		false,	25000,	true),
	(Firma budowlana,			0,		false,	50000,	true),
	(Bank,					0,		false,	70000,	true),
	(Szko³a jazdy,			450,	false,	0,		true),
	(Ciucholand,				0,		false,	8000,	false),
	(Si³ownia,				0,		false,	10000,	false),
	(Strzelnica,				0,		false,	14000,	false),
	(Firma transportowa,		0,		false,	16500,	false),
	(Œciganci,				0,		false,	0,		false),
	(Firma Ochroniarska,		0,		true,	0,		true),
	(S¹d,						450,	false,	0,		false),
	(Grupa przestêpcza,		0,		false,	0,		false),
	(Mafia,					0,		false,	0,		false),
	(Kartel,					0,		false,	0,		false),
	(Dilerzy Narkotyków,		0,		false,	0,		false),
	(Police Departament,		1100,	true,	0,		true),
	(Medical Center,			600,	true,	0,		true),
	(FBI,						800,	true,	0,		false),
	(Fire Departament,		800,	true,	0,		true),
	(San News,				500,	true,	0,		true),
	(Government,				450,	true,	0,		true),
	(National Army,			1000,	true,	0,		false),
	(Gang wiêzienny,			0,		false,	0,		false),
	(Komis aut,				0,		false,	45000,	false),
	(Sklep z koksami,			0,		false,	15000,	true),
	(Lotnisko,				0,		true,	100000,	false),
	(Tartak,					0,		false,	0,		true),
	(Kopalnia,				0, 		false,	0,		true),
	(Rodzina,					0, 		false,	1000,	true),
	(Rybolowstwo,				0,		false,	8000,	false),
	(Firma ciê¿arowa,	400,	true,	0,	false),
	(Typ hardcore,0,	false,	0,	false),
	(Wypo¿yczalnia,	200,	false,	0,	false),
	(Skate,	0,false,	0,	false),
	(Radio, 300, true, 0, false),
	(Gospodarstwo rolne, 300, false, 0, false),
	(Wiezienie, 500, true, 0 ,true),
	(Sklep sportowy, 200, false, 0, false),
	(Coroner, 200, false, 0, false),
	(Ubezpieczalnia,	500,	false,	0,	false),
	(Paintball,	500,	false,	0,	false)
)

enum sGroupInfo
(
	gUID,
	gName(32),

	gCash,

	gType,
	gOwner,

	gValue1,
	gValue2,

	gDotation,
	gColor,

	gTag(5),
	gActivity,
	
	bool: gToggleChat,
	gActionTime
)
GroupData(MAX_GROUPS)(sGroupInfo)

enum sPlayerGroup
(
	gUID,
	gID,

	gPerm,
	gTitle(32),

	gPayment,
	gSkin,
	gLastPayment,
	gTodayDuty
)
PlayerGroup(MAX_PLAYERS)(MAX_GROUP_SLOTS)(sPlayerGroup)

enum sPetrolInfo
(
	bUID,
	bOwner,
	Float:bPosX,
	Float:bPosY,
	Float:bPosZ,
	Float:bRadius
)
PetrolData(MAX_PETROLS)(sPetrolInfo)

enum sRefuelInfo
(
	rType,
	rVeh,
	rLiters,
	Float:rPricePerL,
	Float:rPrice
)
RefuelData(MAX_PLAYERS)(sRefuelInfo)

enum sBoothInfo
(
	bUID,
	bOwner,
	Float:bPosX,
	Float:bPosY,
	Float:bPosZ,
	Float:bRadius,
	bDoorUID
)
BoothData(MAX_BOOTHS)(sBoothInfo)

enum sAnimData
(
	aUID,
	
	aCommand(12),
	aLib(16),
	aName(24),
	
	Float:aSpeed,
	
	aOpt1,
	aOpt2,
	aOpt3,
	aOpt4,
	aOpt5,
	
	aAction
)
AnimInfo(MAX_ANIMATIONS)(sAnimData)

enum sPackageData
(
	pUID,
	pDoorUID,
	
	pItemName(32),
	pItemType,

	pItemValue1,
	pItemValue2,
	
	pItemNumber,
	pItemPrice,
	
	pSecured,
	pTransportTime
)
PackageInfo(MAX_PACKAGES)(sPackageData)

enum sLimitedPackageData
(
	pUID,
	pDoorUID,
	pPlayerUID,
	
	pItemName(32),
	pItemType,

	pItemValue1,
	pItemValue2,
	
	pItemNumber,
	pItemPrice,
	
	pSecured,
	pPoint
)
LimitedPackageInfo(MAX_LIMITEDPACKAGES)(sLimitedPackageData)

enum sOffer
(
	oCustomerID,
	oType,
	
	oName(32),
	oValue,
	oPrice,
	
	oPayType
)
Offer(MAX_PLAYERS)(sOffer)

enum sBuyProduct
(
	pProductUID,
	pProductPrice,
)
BuyProduct(MAX_PLAYERS)(sBuyProduct)

enum eBusStops
(
	bUID,
	bName(32),
	
	Float:bPosX,
	Float:bPosY,
	Float:bPosZ,

	Text3D:bNameTag
)
BusStopData(MAX_BUS_STOPS)(eBusStops)

enum sPhotoRadars
(
	pUID,
	
	Float:pPosX,
	Float:pPosY,
	Float:pPosZ,
	
	Float:pMaxSpeed
)
PhotoRadarInfo(MAX_PHOTO_RADARS)(sPhotoRadars)

enum sGangZones
(
	gUID,
	
	Float:gMinX,
	Float:gMinY,
	
	Float:gMaxX,
	Float:gMaxY,
	
	gOwner,
	gMarihuana,
	gAmp,
	gMetaamp,
	gProfit,
	gRobberies,
	gAttack
)
GangZoneInfo(MAX_GANG_ZONES)(sGangZones)

enum sFishData
(
	fName(32),
	
	fValue1,
	fValue2
)
FishInfo(5)(sFishData) =
(
	(Sledz, 	45, 0),
	(Sardynka, 	25, 0),
	(Tunczyk, 	30, 0),
	(Szczupak, 50, 0),
	(Karas, 	30, 0)
)

enum sVehicleData
(
	vName(32),
	vMaxSpeed
)
VehicleData(212)(sVehicleData) =
(
	(Landstalker, 	140),
	(Bravura, 		131),
	(Buffalo, 		166),
	(Linerunner, 		98),
	(Pereniel, 		118),
	(Sentinel, 		146),
	(Dumper, 			98),
	(Firetruck, 		132),
	(Trashmaster, 	89),
	(Stretch, 		140),
	(Manana, 			115),
	(Infernus, 		197),
	(Voodoo, 			150),
	(Pony, 			98),
	(Mule, 			94),
	(Cheetah, 		171),
	(Ambulance, 		137),
	(Leviathan, 		399),
	(Moonbeam, 		103),
	(Esperanto, 		133),
	(Taxi, 			129),
	(Washington, 		137),
	(Bobcat, 			124),
	(Mr Whoopee, 		88),
	(BF Injection, 	120),
	(Hunter, 			399),
	(Premier, 		154),
	(Enforcer, 		147),
	(Securicar, 		139),
	(Banshee, 		179),
	(Predator, 		399),
	(Bus, 			116),
	(Rhino, 			84),
	(Barracks, 		98),
	(Hotknife, 		148),
	(Firanka Trailer, 		0),
	(Previon, 		133),
	(Coach, 			140),
	(Cabbie, 			127),
	(Stallion, 		150),
	(Rumpo, 			121),
	(RC Bandit, 		67),
	(Romero, 			124),
	(Packer, 			112),
	(Monster Truck A, 98),
	(Admiral, 		146),
	(Squalo, 			399),
	(Seasparrow, 		399),
	(Pizzaboy,		162),
	(Tram, 			399),
	(Wywrotka, 		399),
	(Turismo, 		172),
	(Speeder, 		399),
	(Reefer, 			399),
	(Tropic, 			399),
	(Flatbed, 		140),
	(Yankee, 			94),
	(Caddy, 			84),
	(Solair, 			140),
	(Berkleys RC Van,121),
	(Skimmer, 		399),
	(PCJ-600, 		180),
	(Faggio, 			155),
	(Freeway, 		180),
	(RC Baron, 		399),
	(RC Raider, 		399),
	(Glendale, 		131),
	(Oceanic, 		125),
	(Sanchez, 		164),
	(Sparrow, 		399),
	(Patriot, 		139),
	(Quad, 			98),
	(Coastguard, 		399),
	(Dinghy, 			399),
	(Hermes, 			133),
	(Sabre, 			154),
	(Rustler, 		399),
	(ZR-350, 			166),
	(Walton, 			105),
	(Regina, 			124),
	(Comet, 			164),
	(BMX, 			86),
	(Burrito, 		139),
	(Camper, 			109),
	(Marquis, 		399),
	(Baggage, 		88),
	(Dozer, 			56),
	(Maverick, 		399),
	(News Chopper, 	399),
	(Rancher, 		124),
	(FBI Rancher, 	139),
	(Virgo, 			132),
	(Greenwood, 		125),
	(Jetmax, 			399),
	(Hotring, 		191),
	(Sandking, 		157),
	(Blista Compact, 	145),
	(Police Maverick, 399),
	(Boxville, 		96),
	(Benson, 			109),
	(Mesa, 			125),
	(RC Goblin, 		399),
	(Hotring Racer, 	191),
	(Hotring Racer, 	191),
	(Bloodring Banger,154),
	(Rancher, 		124),
	(Super GT, 		159),
	(Elegant, 		148),
	(Journey, 		96),
	(Bike, 			93),
	(Mountain Bike, 	117),
	(Beagle, 			399),
	(Cropdust, 		399),
	(Stunt, 			399),
	(Tanker, 			107),
	(RoadTrain, 		126),
	(Nebula, 			140),
	(Majestic, 		140),
	(Buccaneer, 		146),
	(Shamal, 			399),
	(Hydra, 			399),
	(FCR-900, 		190),
	(NRG-500, 		200),
	(HPV1000, 		172),
	(Cement Truck, 	116),
	(Tow Truck, 		143),
	(Fortune, 		140),
	(Cadrona, 		133),
	(FBI Truck, 		157),
	(Willard, 		133),
	(Forklift, 		54),
	(Tractor, 		62),
	(Combine, 		98),
	(Feltzer, 		148),
	(Remington, 		150),
	(Slamvan, 		140),
	(Blade, 			154),
	(Freight, 		399),
	(Streak, 			399),
	(Vortex, 			89),
	(Vincent, 		136),
	(Bullet, 			180),
	(Clover, 			146),
	(Sadler, 			134),
	(Firetruck, 		132),
	(Hustler, 		131),
	(Intruder, 		133),
	(Primo, 			127),
	(Cargobob, 		399),
	(Tampa, 			136),
	(Sunrise, 		128),
	(Merit, 			140),
	(Utility, 		108),
	(Nevada, 			399),
	(Yosemite, 		128),
	(Windsor, 		141),
	(Monster Truck B, 98),
	(Monster Truck C, 98),
	(Uranus, 			139),
	(Jester, 			158),
	(Sultan, 			150),
	(Stratum, 		137),
	(Elegy, 			158),
	(Raindance, 		399),
	(RC Tiger, 		79),
	(Flash, 			146),
	(Tahoma,			142),
	(Savanna, 		154),
	(Bandito, 		130),
	(Freight, 		399),
	(Trailer, 		399),
	(Kart, 			83),
	(Mower, 			54),
	(Duneride, 		98),
	(Sweeper, 		53),
	(Broadway, 		140),
	(Tornado, 		140),
	(AT-400, 			399),
	(DFT-30, 			116),
	(Huntley, 		140),
	(Stafford, 		136),
	(BF-400, 			170),
	(Newsvan, 		121),
	(Tug, 			76),
	(Cysterna, 		399),
	(Emperor, 		136),
	(Wayfarer, 		175),
	(Euros, 			147),
	(Hotdog,			96),
	(Club, 			145),
	(Trailer, 		399),
	(Chlodnia, 		399),
	(Andromada, 		399),
	(Dodo, 			399),
	(RC Cam, 			54),
	(Launch,			399),
	(Police Car,		156),
	(Police Car, 		156),
	(Police Car, 		156),
	(Police Ranger, 	140),
	(Picador, 		134),
	(S.W.A.T. Van, 	98),
	(Alpha, 			150),
	(Phoenix, 		152),
	(Glendale, 		131),
	(Sadler, 			134),
	(Luggage Trailer, 399),
	(Luggage Trailer, 399),
	(Stair Trailer, 	399),
	(Boxville, 		96),
	(Farm Plow, 		399),
	(Utility Trailer, 399)
)

PickupIDs(13) = (1239, 1274, 1273, 1272, 1240, 1247, 1277, 1275, 1318, 19471, 19523, 19524, 19525)

WeaponModel(47) = (0, 331, 333, 334, 335, 336, 337, 338, 339, 341, 321, 322, 323, 324, 325, 326, 342, 343, 344, 0, 0, 0, 346, 347, 348, 349, 350, 351, 352, 353, 355, 356, 372, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 371)

enum INTERIOR_INFO
(
	INTERIOR_ID,
	Float:INTERIOR_X,
	Float:INTERIOR_Y,
	Float:INTERIOR_Z,
	Float:INTERIOR_A,
	INTERIOR_NAME(32),
	INTERIOR_PRICE
)

// 21 max. track


/*
Interiors()(INTERIOR_INFO) = (
 	(5, 772.3852,-5.0267,1000.7289,0.6510,			Ganton Gym, 						8000),
  	(3, 975.1497,-8.8785,1001.1484,92.6761, 		Brothel, 							9500),
   	(3, 966.9457,-53.1448,1001.1246,91.2287,		Brothel2, 						12500),
	(3, 834.2611,7.3429,1004.1870,88.4086, 			Inside Track Betting, 			8000),
	(3, 1038.1899,-3.8097,1001.2845,359.7343, 		Blastin Fools Records, 			7500),
	(3, 1212.2024,-26.0924,1000.9531,181.7593,		The Big Spread Ranch, 			11000),
	(18, 1291.9290,3.7353,1001.0112,180.8917, 		Warehouse 1, 						35000),
	(1, 1403.9896,4.1124,1000.9089,180.0966, 		Warehouse 2, 						40000),
	(3, 1525.9994,-10.8667,1002.0971,275.7367, 		B Dups Apartment, 				3000),
	(2, 1521.0021,-48.0825,1002.1310,269.8558, 		B Dups Crack Palace, 			3000),
	(3, 612.2191,-123.9028,997.9922,266.5704, 		Wheel Arch Angels, 				8000),
	(3, 520.3263,-9.0747,1001.5653,90.2650, 		OG Locs House,					6000),
	(3, 418.7094,-84.0039,1001.8047,0.9642, 		Barber Shop, 						7500),
	(3, 390.1465,173.8574,1008.3828,87.4451, 		Planning Department, 				35000),
	(3, 288.7931,167.4812,1007.1719,357.5410, 		Las Venturas Police Department, 	30000),
	(3, 207.1015,-140.0236,1003.5078,356.9143, 		Pro-Laps, 						14500),
	(3, -100.4219,-24.6163,1000.7188,356.9143, 		Sex Shop, 						19000),
	(3, -204.5397,-43.9880,1002.2734,356.9143, 		Las Venturas Tattoo parlor, 		6500),
	(17, -204.2623,-8.3931,1002.2734,0.0477, 		Lost San Fierro Tattoo parlor, 	22000),
	(17, -25.7220,-187.8216,1003.5469,5.0760, 		24/7 (version 1), 				13000),
	(5, 372.4557,-133.3936,1001.4922,1.6144, 		Pizza Stack, 						25500),
	(17, 377.2173,-193.1430,1000.6401,0.0477, 		Rusty Browns Donuts, 			15000),
	(7, 315.9149,-143.4442,999.6016,1.6144, 		Ammu-nation, 						19500),
	(5, 227.0982,-8.0044,1002.2109,90.9151, 		Victim, 							7000),
	(2, 612.6995,-75.5179,997.9922,273.3493, 		Loco Low Co, 						16000),
	(10, 246.3100,107.7927,1003.2188,2.7954, 		San Fierro Police Department, 	90000),
	(10, 6.2462,-31.1101,1003.5494,0.0478, 			24/7 (version 2 - large), 		25000),
	(7, 773.8416,-78.5067,1000.6623,0.0478, 		Below The Belt Gymr, 				15000),
	(1, 608.0074,-10.7054,1000.9174,272.1453, 		Transfenders, 					26000),
	(1, 285.4489,-41.1734,1001.5156,355.6142, 		Ammu-nation (version 2), 			21000),
	(1, 203.9385,-50.1884,1001.8047,355.6142,		SubUrban, 						18500),
	(1, 244.1629,304.8900,999.1484,268.8201, 		Denises Bedroom, 				5000),
	(3, 293.0890,309.9762,999.1484,86.1683, 		Helenas Barn, 					7500),
	(5, 322.1865,302.7020,999.1484,358.1208, 		Barbaras Love nest, 				40000),
	(2, 1204.9052,-13.4438,1000.9219,2.5557, 		The Pig Pen (strip club 2), 		29000),
	(10, 2018.6531,1017.8937,996.8750,87.1330, 		Four Dragons, 					45000),
	(2, 2455.7131,-1706.5864,1013.5078,357.7831,	Ryders house,					14000),
	(1, 2524.6389,-1679.3669,1015.4986,270.1214, 	Sweets House, 					13000),
	(3, 2496.0498,-1692.4344,1014.7422,181.4706, 	The Johnson House, 				32000),
	(10, 362.9743,-74.9267,1001.5078,317.1219, 		Burger shot, 						15000),
	(1, 2234.0559,1714.0764,1012.3347,180.8439, 	Caligulas Casino, 				60000),
	(2, 266.8239,304.9771,999.1484,272.9415, 		Katies Lovenest,		 			6000),
	(2, 411.5980,-22.9821,1001.8047,358.7722, 		Barber Shop 2 (Reeces), 			6500),
	(2, 1.1853,-3.2387,999.4284,87.5718, 			Angel \Pine Trailer\, 			8000),
	(18, -31.1142,-91.6357,1003.5469,356.8922, 		24/7 (version 3), 				20000),
	(18, 161.3073,-96.5507,1001.8047,356.8922, 		Zip, 								6500),
	(3, -2636.7996,1402.7880,906.4609,356.8922, 	The Pleasure Domes, 				59000),
	(5, 1261.0970,-785.3736,1091.9063,269.3989, 	Madd Doggs Mansion, 				220000),
	(2, 2570.7341,-1301.9620,1044.1250,84.9398, 	Big Smokes Crack Palace, 		140000),
	(5, 2352.3013,-1180.8904,1027.9766,89.6399, 	Burning Desire Building, 			2500),
	(1, -2158.6418,642.7681,1052.3750,186.1475, 	Wu-Zi Mus, 						28000),
	(10, 422.2926,2536.6521,10.0000,91.8332, 		Abandoned AC tower, 				7000),
	(14, 254.3687,-41.7188,1002.0308,269.8082, 		Wardrobe/Changing room, 			1500),
	(14, 204.3125,-168.7386,1000.5234,358.7724, 	Didier Sachs, 					12000),
	(12, 1133.0537,-15.3457,1000.6797,357.5191, 	Casino (Redsands West), 			27000),
	(17, 493.5156,-24.7910,1000.6797,357.5191, 		Club, 							34500),
	(18, 1726.9481,-1638.5168,20.2233,176.4107, 	Atrium, 							36000),
	(16, -204.2385,-27.0951,1002.2734,359.6890, 	Los Santos Tattoo Parlor, 		6500),
	(5, 2233.6138,-1115.0178,1050.8828,359.6890,	Safe House group 1, 				6500),
	(9, 2317.9077,-1026.6240,1050.2178,3.1357, 		Safe House group 3, 				43000),
	(10, 2259.6904,-1135.9205,1050.6328,266.9415, 	Safe House group 4, 				9000),
	(15, 2214.9121,-1150.3807,1025.7969,268.5082, 	Jefferson Motel, 					39500),
	(1, 2.1403,23.2410,1199.5938,93.0399, 			Jet Interior, 					20000),
 	(1, 681.6216,-451.8933,-25.6172,166.1660, 		The Welcome Pump, 				29000),
 	(3, 235.2854,1186.7764,1080.2578,359.9790, 		Burglary House X1,				0),
  	(2, 225.5707,1240.0643,1082.1406,96.2852, 		Burglary House X2, 				15000),
   	(1, 223.0885,1287.1864,1082.1406,356.2190, 		Burglary House X3, 				50000),
	(5, 226.9825,1114.3130,1080.9965,270.0515, 		Burglary House X4, 				0),
 	(15, 207.5804,-110.9442,1005.1328,358.4124, 	Binco, 							27500),
  	(15, 295.1391,1473.3719,1080.2578,352.9526, 	4 Burglary houses, 				6000),
	(12, 446.7587,506.6798,1001.4195,357.4724, 		Budget Inn Motel Room, 			4500),
	(0, 2305.1001,-16.2089,26.7422,269.7382, 		Palamino Bank, 					5500),
	(0, 663.0487,-573.6597,16.3359,266.0015, 		Dillimore Gas Station, 			6800),
	(18, -228.8965,1401.3147,27.7656,266.0015, 		Lil Probe Inn, 					13000),
	(2, 446.9469,1397.5585,1084.3047,359.3991, 		Pair of Burglary Houses, 			25000),
	(5, 226.6049,1114.2588,1080.9945,266.3383, 		Burglary House X11, 				26000),
	(4, 260.8826,1284.4226,1080.2578,356.8690, 		Burglary House X12, 				28000),
	(4, 285.7398,-86.2111,1001.5229,0.9424, 		Ammu-nation (version 3), 			23000),
	(4, 460.0900,-88.7736,999.5547,88.6766, 		Jays Diner, 						13000),
	(4, 300.2214,308.9092,1003.3047,267.5913, 		Michelles Love Nest*, 			6000),
	(10, 24.0752,1340.4037,1084.3750,357.5913,	 	Burglary House X14, 				47500),
	(1, 964.8690,2160.1362,1011.0303,87.4463, 		Sindacco Abatoir, 				15000),
	(4, 221.7042,1140.5739,1082.6094,355.0121, 		Burglary House X13, 				12000),
	(12, 2324.4485,-1149.3555,1050.7101,355.0121, 	Unused Safe House, 				115000),
	(6, 344.0542,305.0782,999.1484,270.3390, 		Millies Bedroom, 				4500),
	(12, 412.0997,-54.1158,1001.8984,357.5189, 		Barber Shop, 						6500),
	(6, 774.1306,-50.3132,1000.5859,356.5555, 		Cobra Gym, 						29000),
	(6, 246.7376,62.6765,1003.6406,359.6888, 		Los Santos Police Department, 	80000),
	(4, -260.6812,1456.6299,1084.3672,84.9163, 		Burglary House X15, 				31000),
	(5, 22.7006,1403.4539,1084.4370,0.0022, 		Burglary House X16, 				34000),
	(5, 140.4259,1366.3585,1083.8594,354.6754, 		Burglary House X17, 				105000),
	(3, 1494.4634,1303.9586,1093.2891,358.1221, 	Bike School, 						15000),
	(6, 234.1510,1064.0935,1084.2117,358.1221, 		Burglary House X18, 				55000),
	(6, -68.7717,1351.2863,1080.2109,358.1221, 		Burglary House X19, 				0),
	(6, -2240.6143,137.1421,1035.4141,268.8213, 	Zeros RC Shop, 					16000),
	(6, 296.8614,-111.8426,1001.5156,355.3021, 		Ammu-nation (version 4), 			18500),
	(6, 316.2793,-169.7145,999.6010,355.3021, 		Ammu-nation (version 5), 			22000),
	(15, -283.5468,1471.0049,1084.3750,89.3029, 	Burglary House X20, 				28000),
	(6, 744.3742,1436.4757,1102.7031,356.9153, 		Fanny Batters Whore House, 		0),
	(8, 2807.4829,-1174.5416,1025.5703,356.9153, 	Colonel Furhbergers, 			37000),
	(9, 364.8955,-11.1229,1001.8516,356.9153, 		Cluckin Bell, 					5500),
	(1, 2218.2136,-1076.3907,1050.4844,89.0129, 	The Camels Toe Safehouse, 		6500),
	(1, 2266.2695,1647.5325,1084.2344,265.7112, 	Caligulas Roof, 					20000),
	(2, 2237.5891,-1081.4121,1049.0234,357.1820, 	Old Venturas Strip Casino,		40000),
	(3, -2029.7666,-119.0861,1035.1719,357.1820, 	Driving School, 					8000),
	(8, 2365.3745,-1135.1105,1050.8750,357.8087, 	Verdant Bluffs Safehouse, 		25000),
	(10, 1893.7197,1018.2451,31.8828,96.3156, 		Four Dragons Janitors Office, 	40000),
	(11, 502.0814,-68.0179,998.7578,179.9763, 		Bar, 								30000),
	(8, -42.5038,1405.9224,1084.4297,356.6021, 		Burglary House X21, 				27500),
	(9, 83.0910,1322.5833,1083.8662,1.6155, 		Burglary House X22, 				36000),
	(9, 260.7572,1237.4823,1084.2578,1.6155, 		Burglary House X23, 				30000)
)
*/

Interiors()(INTERIOR_INFO) = (
 	(5, 772.3852,-5.0267,1000.7289,0.6510,			Ganton Gym, 						0),
  	(3, 975.1497,-8.8785,1001.1484,92.6761, 		Brothel, 							0),
   	(3, 966.9457,-53.1448,1001.1246,91.2287,		Brothel2, 						0),
	(3, 834.2611,7.3429,1004.1870,88.4086, 			Inside Track Betting, 			0),
	(3, 1038.1899,-3.8097,1001.2845,359.7343, 		Blastin Fools Records, 			0),
	(3, 1212.2024,-26.0924,1000.9531,181.7593,		The Big Spread Ranch, 			0),
	(18, 1291.9290,3.7353,1001.0112,180.8917, 		Warehouse 1, 						0),
	(1, 1403.9896,4.1124,1000.9089,180.0966, 		Warehouse 2, 						0),
	(3, 1525.9994,-10.8667,1002.0971,275.7367, 		B Dups Apartment, 				0),
	(2, 1521.0021,-48.0825,1002.1310,269.8558, 		B Dups Crack Palace, 			0),
	(3, 612.2191,-123.9028,997.9922,266.5704, 		Wheel Arch Angels, 				0),
	(3, 520.3263,-9.0747,1001.5653,90.2650, 		OG Locs House,					0),
	(3, 418.7094,-84.0039,1001.8047,0.9642, 		Barber Shop, 						0),
	(3, 390.1465,173.8574,1008.3828,87.4451, 		Planning Department, 				0),
	(3, 288.7931,167.4812,1007.1719,357.5410, 		Las Venturas Police Department, 	0),
	(3, 207.1015,-140.0236,1003.5078,356.9143, 		Pro-Laps, 						0),
	(3, -100.4219,-24.6163,1000.7188,356.9143, 		Sex Shop, 						0),
	(3, -204.5397,-43.9880,1002.2734,356.9143, 		Las Venturas Tattoo parlor, 		0),
	(17, -204.2623,-8.3931,1002.2734,0.0477, 		Lost San Fierro Tattoo parlor, 	0),
	(17, -25.7220,-187.8216,1003.5469,5.0760, 		24/7 (version 1), 				0),
	(5, 372.4557,-133.3936,1001.4922,1.6144, 		Pizza Stack, 						0),
	(17, 377.2173,-193.1430,1000.6401,0.0477, 		Rusty Browns Donuts, 			0),
	(7, 315.9149,-143.4442,999.6016,1.6144, 		Ammu-nation, 						0),
	(5, 227.0982,-8.0044,1002.2109,90.9151, 		Victim, 							0),
	(2, 612.6995,-75.5179,997.9922,273.3493, 		Loco Low Co, 						0),
	(10, 246.3100,107.7927,1003.2188,2.7954, 		San Fierro Police Department, 	0),
	(10, 6.2462,-31.1101,1003.5494,0.0478, 			24/7 (version 2 - large), 		0),
	(7, 773.8416,-78.5067,1000.6623,0.0478, 		Below The Belt Gymr, 				0),
	(1, 608.0074,-10.7054,1000.9174,272.1453, 		Transfenders, 					0),
	(1, 285.4489,-41.1734,1001.5156,355.6142, 		Ammu-nation (version 2), 			0),
	(1, 203.9385,-50.1884,1001.8047,355.6142,		SubUrban, 						0),
	(1, 244.1629,304.8900,999.1484,268.8201, 		Denises Bedroom, 				0),
	(3, 293.0890,309.9762,999.1484,86.1683, 		Helenas Barn, 					0),
	(5, 322.1865,302.7020,999.1484,358.1208, 		Barbaras Love nest, 				0),
	(2, 1204.9052,-13.4438,1000.9219,2.5557, 		The Pig Pen (strip club 2), 		0),
	(10, 2018.6531,1017.8937,996.8750,87.1330, 		Four Dragons, 					0),
	(2, 2455.7131,-1706.5864,1013.5078,357.7831,	Ryders house,					0),
	(1, 2524.6389,-1679.3669,1015.4986,270.1214, 	Sweets House, 					0),
	(3, 2496.0498,-1692.4344,1014.7422,181.4706, 	The Johnson House, 				0),
	(10, 362.9743,-74.9267,1001.5078,317.1219, 		Burger shot, 						0),
	(1, 2234.0559,1714.0764,1012.3347,180.8439, 	Caligulas Casino, 				0),
	(2, 266.8239,304.9771,999.1484,272.9415, 		Katies Lovenest,		 			0),
	(2, 411.5980,-22.9821,1001.8047,358.7722, 		Barber Shop 2 (Reeces), 			0),
	(2, 1.1853,-3.2387,999.4284,87.5718, 			Angel \Pine Trailer\, 			0),
	(18, -31.1142,-91.6357,1003.5469,356.8922, 		24/7 (version 3), 				0),
	(18, 161.3073,-96.5507,1001.8047,356.8922, 		Zip, 								0),
	(3, -2636.7996,1402.7880,906.4609,356.8922, 	The Pleasure Domes, 				0),
	(5, 1261.0970,-785.3736,1091.9063,269.3989, 	Madd Doggs Mansion, 				0),
	(2, 2570.7341,-1301.9620,1044.1250,84.9398, 	Big Smokes Crack Palace, 		0),
	(5, 2352.3013,-1180.8904,1027.9766,89.6399, 	Burning Desire Building, 			0),
	(1, -2158.6418,642.7681,1052.3750,186.1475, 	Wu-Zi Mus, 						0),
	(10, 422.2926,2536.6521,10.0000,91.8332, 		Abandoned AC tower, 				0),
	(14, 254.3687,-41.7188,1002.0308,269.8082, 		Wardrobe/Changing room, 			0),
	(14, 204.3125,-168.7386,1000.5234,358.7724, 	Didier Sachs, 					0),
	(12, 1133.0537,-15.3457,1000.6797,357.5191, 	Casino (Redsands West), 			0),
	(17, 493.5156,-24.7910,1000.6797,357.5191, 		Club, 							0),
	(18, 1726.9481,-1638.5168,20.2233,176.4107, 	Atrium, 							0),
	(16, -204.2385,-27.0951,1002.2734,359.6890, 	Los Santos Tattoo Parlor, 		0),
	(5, 2233.6138,-1115.0178,1050.8828,359.6890,	Safe House group 1, 				0),
	(9, 2317.9077,-1026.6240,1050.2178,3.1357, 		Safe House group 3, 				0),
	(10, 2259.6904,-1135.9205,1050.6328,266.9415, 	Safe House group 4, 				0),
	(15, 2214.9121,-1150.3807,1025.7969,268.5082, 	Jefferson Motel, 					0),
	(1, 2.1403,23.2410,1199.5938,93.0399, 			Jet Interior, 					0),
 	(1, 681.6216,-451.8933,-25.6172,166.1660, 		The Welcome Pump, 				0),
 	(3, 235.2854,1186.7764,1080.2578,359.9790, 		Burglary House X1,				0),
  	(2, 225.5707,1240.0643,1082.1406,96.2852, 		Burglary House X2, 				0),
   	(1, 223.0885,1287.1864,1082.1406,356.2190, 		Burglary House X3, 				0),
	(5, 226.9825,1114.3130,1080.9965,270.0515, 		Burglary House X4, 				0),
 	(15, 207.5804,-110.9442,1005.1328,358.4124, 	Binco, 							0),
  	(15, 295.1391,1473.3719,1080.2578,352.9526, 	4 Burglary houses, 				0),
	(12, 446.7587,506.6798,1001.4195,357.4724, 		Budget Inn Motel Room, 			0),
	(0, 2305.1001,-16.2089,26.7422,269.7382, 		Palamino Bank, 					0),
	(0, 663.0487,-573.6597,16.3359,266.0015, 		Dillimore Gas Station, 			0),
	(18, -228.8965,1401.3147,27.7656,266.0015, 		Lil Probe Inn, 					0),
	(2, 446.9469,1397.5585,1084.3047,359.3991, 		Pair of Burglary Houses, 			0),
	(5, 226.6049,1114.2588,1080.9945,266.3383, 		Burglary House X11, 				0),
	(4, 260.8826,1284.4226,1080.2578,356.8690, 		Burglary House X12, 				0),
	(4, 285.7398,-86.2111,1001.5229,0.9424, 		Ammu-nation (version 3), 			0),
	(4, 460.0900,-88.7736,999.5547,88.6766, 		Jays Diner, 						0),
	(4, 300.2214,308.9092,1003.3047,267.5913, 		Michelles Love Nest*, 			0),
	(10, 24.0752,1340.4037,1084.3750,357.5913,	 	Burglary House X14, 				0),
	(1, 964.8690,2160.1362,1011.0303,87.4463, 		Sindacco Abatoir, 				0),
	(4, 221.7042,1140.5739,1082.6094,355.0121, 		Burglary House X13, 				0),
	(12, 2324.4485,-1149.3555,1050.7101,355.0121, 	Unused Safe House, 				0),
	(6, 344.0542,305.0782,999.1484,270.3390, 		Millies Bedroom, 				0),
	(12, 412.0997,-54.1158,1001.8984,357.5189, 		Barber Shop, 						0),
	(6, 774.1306,-50.3132,1000.5859,356.5555, 		Cobra Gym, 						0),
	(6, 246.7376,62.6765,1003.6406,359.6888, 		Los Santos Police Department, 	0),
	(4, -260.6812,1456.6299,1084.3672,84.9163, 		Burglary House X15, 				0),
	(5, 22.7006,1403.4539,1084.4370,0.0022, 		Burglary House X16, 				0),
	(5, 140.4259,1366.3585,1083.8594,354.6754, 		Burglary House X17, 				0),
	(3, 1494.4634,1303.9586,1093.2891,358.1221, 	Bike School, 						0),
	(6, 234.1510,1064.0935,1084.2117,358.1221, 		Burglary House X18, 				0),
	(6, -68.7717,1351.2863,1080.2109,358.1221, 		Burglary House X19, 				0),
	(6, -2240.6143,137.1421,1035.4141,268.8213, 	Zeros RC Shop, 					0),
	(6, 296.8614,-111.8426,1001.5156,355.3021, 		Ammu-nation (version 4), 			0),
	(6, 316.2793,-169.7145,999.6010,355.3021, 		Ammu-nation (version 5), 			0),
	(15, -283.5468,1471.0049,1084.3750,89.3029, 	Burglary House X20, 				0),
	(6, 744.3742,1436.4757,1102.7031,356.9153, 		Fanny Batters Whore House, 		0),
	(8, 2807.4829,-1174.5416,1025.5703,356.9153, 	Colonel Furhbergers, 			0),
	(9, 364.8955,-11.1229,1001.8516,356.9153, 		Cluckin Bell, 					0),
	(1, 2218.2136,-1076.3907,1050.4844,89.0129, 	The Camels Toe Safehouse, 		0),
	(1, 2266.2695,1647.5325,1084.2344,265.7112, 	Caligulas Roof, 					0),
	(2, 2237.5891,-1081.4121,1049.0234,357.1820, 	Old Venturas Strip Casino,		0),
	(3, -2029.7666,-119.0861,1035.1719,357.1820, 	Driving School, 					0),
	(8, 2365.3745,-1135.1105,1050.8750,357.8087, 	Verdant Bluffs Safehouse, 		0),
	(10, 1893.7197,1018.2451,31.8828,96.3156, 		Four Dragons Janitors Office, 	0),
	(11, 502.0814,-68.0179,998.7578,179.9763, 		Bar, 								0),
	(8, -42.5038,1405.9224,1084.4297,356.6021, 		Burglary House X21, 				0),
	(9, 83.0910,1322.5833,1083.8662,1.6155, 		Burglary House X22, 				0),
	(9, 260.7572,1237.4823,1084.2578,1.6155, 		Burglary House X23, 				0)
)

//slots
enum mchPars
(
	mUID,
	Float:mPosX,
	Float:mPosY,
	Float:mPosZ,
	mVW,
	mMoney,
	mOwner,
	bool:mBusy,
)
SlotMachine(MAX_SLOTS)(mchPars)

enum slotsPars
(
	slName(32),
	humanName(32),
)
SlotInfo(6)(slotsPars) = 
(
	(LD_SLOT:bar1_o,Sztabka zlota),
	(LD_SLOT:bar2_o,Sztabki zlota),
	(LD_SLOT:bell,Dzwonki),
	(LD_SLOT:cherry,Wisnia),
	(LD_SLOT:grapes,Winogrono),
	(LD_SLOT:r_69,Liczba 69)
)


/*enum cPars
(
	cdName(32),
	cdHumanName(32),
)
CardInfo(53)(cPars) = 
(
	(LD_CARD:cdback,Tyl karty),
	
	(LD_CARD:cd13c,Krol krzyz),
	(LD_CARD:cd13d,Krol karo),
	(LD_CARD:cd13h,Krol serce),
	(LD_CARD:cd13s,Krol pik),
	
	(LD_CARD:cd12c,Dama krzyz),
	(LD_CARD:cd12d,Dama karo),
	(LD_CARD:cd12h,Dama serce),
	(LD_CARD:cd12s,Dama pik),
	
	(LD_CARD:cd11c,Jopek krzyz),
	(LD_CARD:cd11d,Jopek karo),
	(LD_CARD:cd11h,Jopek serce),
	(LD_CARD:cd11s,Jopek pik),
	
	(LD_CARD:cd10c,Dziesiatka krzyz),
	(LD_CARD:cd10d,Dziesiatka karo),
	(LD_CARD:cd10h,Dziesiatka serce),
	(LD_CARD:cd10s,Dziesiatka pik),
	
	(LD_CARD:cd9c,Dziewiatka krzyz),
	(LD_CARD:cd9d,Dziewiatka karo),
	(LD_CARD:cd9h,Dziewiatka serce),
	(LD_CARD:cd9s,Dziewiatka pik),
	
	(LD_CARD:cd8c,Osemka krzyz),
	(LD_CARD:cd8d,Osemka karo),
	(LD_CARD:cd8h,Osemka serce),
	(LD_CARD:cd8s,Osemka pik),
	
	(LD_CARD:cd7c,Siodemka krzyz),
	(LD_CARD:cd7d,Siodemka karo),
	(LD_CARD:cd7h,Siodemka serce),
	(LD_CARD:cd7s,Siodemka pik),
	
	(LD_CARD:cd6c,Szostka krzyz),
	(LD_CARD:cd6d,Szostka karo),
	(LD_CARD:cd6h,Szostka serce),
	(LD_CARD:cd6s,Szostka pik),
	
	(LD_CARD:cd5c,Piatka krzyz),
	(LD_CARD:cd5d,Piatka karo),
	(LD_CARD:cd5h,Piatka serce),
	(LD_CARD:cd5s,Piatka pik),
	
	(LD_CARD:cd4c,Czworka krzyz),
	(LD_CARD:cd4d,Czworka karo),
	(LD_CARD:cd4h,Czworka serce),
	(LD_CARD:cd4s,Czworka pik),
	
	(LD_CARD:cd3c,Trojka krzyz),
	(LD_CARD:cd3d,Trojka karo),
	(LD_CARD:cd3h,Trojka serce),
	(LD_CARD:cd3s,Trojka pik),
	
	(LD_CARD:cd2c,Dwojka krzyz),
	(LD_CARD:cd2d,Dwojka karo),
	(LD_CARD:cd2h,Dwojka serce),
	(LD_CARD:cd2s,Dwojka pik),
	
	(LD_CARD:cd1c,As krzyz),
	(LD_CARD:cd1d,As karo),
	(LD_CARD:cd1h,As serce),
	(LD_CARD:cd1s,As pik)
)*/



enum sSkinData
(
	sModel,
	sPrice,
	sName(24)
)

SkinInfo()(sSkinData) =
(
	(1, 40, Flanelowa koszula),
	(2, 60, Bluza z kapeluszem),
	(3, 95, Firmowa marynarka),
	(4, 30, Brazowa koszulka),
	(5, 35, Brazowa koszulka xxl),
	(7, 68, Kurtka jensowa),
	(8, 70, Stroj mechanika 1),
	(10, 50, Sweterek),
	(11, 95, Stroj elegancki),
	(12, 110, Czarna sukienka),
	(13, 50, Ciemny luzny stroj),
	(15, 35, Koszula w krate),
	(16, 50, Kamizelka odblaskowa),
	(17, 200, Czarny garnitur),
	(18, 10, Kapielowki),
	(19, 55, Czerwone spodnie),
	(20, 50, Zolta bluza),
	(21, 60, Granatowa koszula),
	(22, 65, Pomaranczowa bluza),
	(23, 45, Stroj skate),
	(24, 50, Granatowa bluza),
	(25, 60, Komplet Luz),
	(27, 50, Stroj roboczy),
	(28, 70, Firmowa podkoszulka),
	(29, 95, Bluza z kapturem),
	(30, 30, Szara podkoszulka),
	(31, 70, Kowbojki),
	(32, 25, Jensowa kurtka),
	(33, 60, Czarny p³aszcz),
	(34, 75, Stroj kowboja),
	(35, 35, Rozowa koszula),
	(36, 25, Biala koszulka),
	(37, 30, Stroj Golf),
	(38, 40, Koszulka golfowa),
	(39, 25, Stroj babciny),
	(40, 105, Czerwona sukienka),
	(41, 80, Blekitny dres),
	(42, 60, Stroj mechanika 2),
	(43, 20, Fioletowa koszulka),
	(45, 20, Zielone bokserki),
	(46, 110, Elegancka koszula),
	(47, 60, Siwa koszula),
	(48, 40, Koszula w paski),
	(49, 50, Komplet Snake),
	(50, 50, Stroj mechanika 3),
	(51, 70, Stroj do rolek 1),
	(52, 70, Stroj do rolek 2),
	(53, 35, Tandetna koszulka),
	(54, 40, Swterek babuni),
	(55, 75, Sukienka i okulary),
	(56, 65, Komplet nastolatki),
	(57, 150, Elegancki garnitur 1),
	(58, 30, Bordowa koszula),
	(59, 75, Elegancka koszula),
	(60, 55, Komplet codzienny),
	(62, 30, Pidzama nocna),
	(63, 170, Komplet prostytutki 1),
	(64, 190, Komplet prostytutki 2),
	(65, 40, Ubranie LUZ),
	(66, 50, Stroj codzienny),
	(67, 70, Bluza z chusta),
	(68, 50, Stroj ksiedza),
	(69, 40, Niebieski komplet),
	(72, 55, Ubranie tradycyjne),
	(73, 65, Spodnie moro),
	(75, 40, Stroj wywloki),
	(76, 55, Zakiet granatowy),
	(77, 25, Rozdarta spodniczka),
	(78, 10, Komplet bezdomny 1),
	(79, 10, Komplet bezdomny 2),
	(80, 90, Komplet bokserski),
	(81, 90, Komplet bokserski),
	(82, 80, Stroj Elvisa 1),
	(83, 70, Stroj Elvisa 2),
	(84, 70, Stroj Elvisa 3),
	(85, 120, Komplet prostytutki 5),
	(87, 90, Komplet striptiz),
	(88, 40, Czerwona koszulka),
	(89, 50, Babcina sukienka),
	(90, 50, Komplet Dres),
	(91, 110, Biala suknia),
	(92, 40, Rolki w bikini),
	(93, 70, Stroj codzienny),
	(94, 20, Stroj dziadkowy),
	(95, 30, Jasna koszula),
	(96, 55, Stroj sportowy),
	(97, 30, Czerwone bokserki),
	(98, 100, Elegancki stroj),
	(99, 50, Stroj rolkarza),
	(100, 80, Stroj Harley),
	(101, 60, Zielona koszulka),
	(111, 150, Komplet BLACK),
	(112, 140, Kurtka skorzana),
	(113, 200, Garnitur),
	(117, 100, Czarny garnitur),
	(118, 100, Czarny garnitur),
	(119, 90, Jasne spodnie),
	(120, 120, Czarna marynarka),
	(121, 60, Komplet Army),
	(122, 70, Koszulka z chusta),
	(123, 90, Chinska koszula),
	(124, 100, Komplet LUZIO),
	(125, 80, Bluza ortalionowa),
	(126, 90, Elegancka koszula),
	(127, 80, Skorzana kurtka),
	(128, 90, Komplet HIPIS),
	(129, 50, Dluga spodnica),
	(130, 30, Komplet babuszki),
	(131, 50, Stroj damski),
	(132, 40, Stroj farmera),
	(133, 55, Komplet DENO),
	(134, 10, Komplet bezdomnych),
	(135, 20, Stara czerwona koszula),
	(136, 20, Zwykla koszula),
	(137, 5, Stroj z kartonem),
	(138, 15, Komplet i okulary),
	(139, 10, Komplet),
	(140, 10, Komplet2),
	(141, 90, Stroj sluzbowy),
	(143, 85, Blekitna bluza),
	(144, 50, Szeroka koszulka),
	(145, 40, Maseczka),
	(146, 40, Maseczka),
	(147, 110, Garnitur wyjsciowy),
	(148, 90, Zakiet zielony),
	(150, 100, Krotka sukienka),
	(151, 70, Sukienka jansowa),
	(152, 200, Stroj SEX),
	(153, 100, Garnitur z kaskiem),
	(154, 5, Galoty granatowe),
	(155, 155, Komplet PIZZA),
	(156, 50, Koszuleczka niebieska),
	(157, 40, Stroj FARM),
	(158, 50, Komplet FARM),
	(159, 40, Komplet FARMI),
	(160, 20, Komplet BIDA),
	(161, 80, Komplet KOWBOY),
	(162, 5, Spodnie JENS),
	(165, 220, Czarny garnitur N),
	(166, 220, Czarny garnitur),
	(167, 10, Kogut),
	(168, 30, Fartuch),
	(169, 95, Czarna sukienka CHI),
	(170, 80, Komplet PIR),
	(171, 100, Komplet CES M),
	(172, 90, Komplet CES),
	(176, 60, Komplet BLUE),
	(177, 60, Komplet BLUE2),
	(178, 300, LATEX),
	(179, 50, Komplet MOR),
	(180, 60, Dluga koszulka),
	(181, 70, Komplet PUNK),
	(183, 70, Ciemna krata),
	(184, 60, Ubranie LIZ),
	(185, 80, Koszula w pasy),
	(186, 220, Brazowy garnitur),
	(187, 200, Garnitur z krawatem),
	(188, 50, Zielona koszulka),
	(189, 80, Czerwona kamizelka),
	(190, 40, Getry i koszuleczka),
	(191, 50, Stroj zielony),
	(192, 70, Komplet GE),
	(193, 60, Dres i koszulka),
	(194, 95, Elegancja),
	(195, 40, Biale spodnie dresowe),
	(196, 35, Spodnica w krate),
	(197, 20, Bluzeczka na ramiaczka),
	(198, 80, Dam kowboy),
	(199, 65, Rozowa sukienka),
	(200, 5, Ogrodniczki),
	(201, 20, Komplet Fam-dam),
	(202, 40, Koszulka z czapka),
	(203, 60, Stroj Kimono),
	(204, 60, Stroj Kimono2),
	(205, 30, Czapka hamburger damska),
	(206, 40, Komplet Cab),
	(207, 60, Komplet Gre),
	(208, 100, Ubranie Black),
	(299, 50, Czarna kurtka ze skory),
	(298, 25, Bluzka na ramiaczkach),
	(297, 70, Komplet Madd-Dogg),
	(296, 90, Fioletowy Garnitur),
	(295, 100, Elegancki Garnitur),
	(294, 120, Stylowy garnitur),
	(293, 20, Brazowe Jeansy),
	(292, 30, Bialy podkoszulek),
	(291, 40, Jeansowa kamizelka),
	(290, 50, Czarna marynarka),
	(289, 35, Zielona koszula),
	(273, 25, T-Shirt w paski),
	(272, 40, Brazowa kurtka),
	(268, 60, Ubranie robocze),
	(264, 50, Kostium klauna),
	(263, 90, Obcisla sukienka),
	(262, 50, Zielony sweterek),
	(261, 60, Koszula w krate),
	(260, 50, Kamizelka odblaskowa),
	(259, 60, Niebieska koszula XXL),
	(258, 60, Szara koszula w krate),
	(257, 80, Komplet Nocne igraszki),
	(256, 80, Czarno-czerwona Mini),
	(255, 90, Garnitur dla szofera),
	(254, 70, Kamizelka ze skory),
	(252, 15, Bokserki na plaze),
	(251, 20, Stroj kapielowy),
	(250, 35, Bluzka z rekawami),
	(249, 85, Dlugi plaszcz ze skory),
	(248, 90, Komplet ze skory),
	(247, 70, Skorzana kamizelka),
	(246, 50, Wyuzdana policjantka),
	(245, 25, Bluzko-biustonosz),
	(244, 40, Obiekt porzadania),
	(243, 40, Czerwona bluzka),
	(242, 20, Bialy podkoszulek XXL),
	(241, 25, Czarny T-shirt zapinany),
	(240, 75, Czarny bezrekawnik),
	(239, 15, Zaniedbana koszula),
	(238, 70, Obcisla sukienka),
	(237, 40, Bluzeczka Panterka),
	(236, 25, Koszula z T-Shirtem),
	(235, 30, Koszula z wzorkiem),
	(234, 25, Obcisly T-Shirt),
	(233, 40, Bialy sweterek),
	(232, 20, Bordowy kangurek),
	(231, 20, Jablkowy T-Shirt),
	(230, 15, Bluza z kapturem),
	(229, 25, Bialy T-shirt),
	(228, 90, Zwykly garnitur),
	(227, 110, Firmowy garnitur),
	(226, 55, Liliowa bluzka),
	(225, 45, Obcisla bluzka),
	(224, 55, Obcisly T-Shirt),
	(223, 65, Rozowa koszula),
	(222, 30, Luzna koszula),
	(221, 25, Biala koszulka Polo),
	(220, 40, Arabski T-Shirt),
	(219, 95, Damska marynarka),
	(218, 30, Rozowy sweter),
	(217, 35, Zwykly ciemny T-shirt),
	(216, 75, Biala sukienka),
	(215, 65, Zolta kurteczka),
	(214, 125, Komplet Afrodyta),
	(213, 15, Rock n Rollowiec),
	(212, 15, Uzywana koszulka),
	(210, 45, Kamizelka rybacka),
	(209, 35, Pracownik Fast-Food)
)

enum sAccessData
(
	aModel,
	aPrice,
	
	aName(24),
	aBone,
	
	Float:aPosX,
	Float:aPosY,
	Float:aPosZ,
	
	Float:aRotX,
	Float:aRotY,
	Float:aRotZ,
	
	aOwnerType,
	aOwner,
	aType
)

AccessInfo()(sAccessData) =
(
	/* Cennik zrobiony przez ABESa, wszelkie prawa zastrze¿one. :D */
	
	/* Komentujemy dla lagtestu */
	
	// Fryzury - SHOP_HAIRCUT
	(15108, 100, Fryzura 1, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15109, 100, Fryzura 2, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15110, 100, Fryzura 3, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15111, 100, Fryzura 4, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15112, 100, Fryzura 5, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15113, 100, Fryzura 6, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15114, 100, Fryzura 7, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15115, 100, Fryzura 8, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15116, 100, Fryzura 9, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15117, 100, Fryzura 10, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15118, 100, Fryzura 11, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15119, 100, Fryzura 12, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15120, 100, Fryzura 12, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15121, 100, Fryzura 13, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15122, 100, Fryzura 14, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15123, 100, Fryzura 15, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15124, 100, Fryzura 16, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(18640, 100, Fryzura 17, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(19518, 100, Fryzura 18, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	
	/*(15125, 100, Fryzura 17, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15126, 100, Fryzura 18, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15127, 100, Fryzura 19, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15128, 100, Fryzura 20, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15129, 100, Fryzura 21, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15130, 100, Fryzura 22, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15131, 100, Fryzura 23, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15132, 100, Fryzura 24, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15133, 100, Fryzura 25, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15134, 100, Fryzura 26, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15135, 100, Fryzura 27, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15136, 100, Fryzura 28, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15137, 100, Fryzura 29, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15138, 100, Fryzura 30, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15139, 100, Fryzura 31, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15140, 100, Fryzura 32, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15141, 100, Fryzura 33, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15142, 100, Fryzura 34, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15143, 100, Fryzura 35, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15144, 100, Fryzura 36, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15145, 100, Fryzura 37, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15146, 100, Fryzura 38, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15147, 100, Fryzura 39, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15148, 100, Fryzura 40, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15149, 100, Fryzura 41, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15150, 100, Fryzura 42, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15151, 100, Fryzura 43, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15152, 100, Fryzura 44, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15153, 100, Fryzura 45, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15154, 100, Fryzura 46, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15155, 100, Fryzura 47, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15156, 100, Fryzura 48, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15157, 100, Fryzura 49, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15158, 100, Fryzura 50, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15159, 100, Fryzura 51, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15160, 100, Fryzura 52, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15161, 100, Fryzura 53, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15162, 100, Fryzura 54, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15163, 100, Fryzura 55, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15164, 100, Fryzura 56, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15165, 100, Fryzura 57, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15166, 100, Fryzura 58, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15167, 100, Fryzura 59, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15168, 100, Fryzura 60, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15169, 100, Fryzura 61, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15170, 100, Fryzura 62, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15171, 100, Fryzura 63, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15172, 100, Fryzura 64, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15173, 100, Fryzura 65, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15174, 100, Fryzura 66, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15175, 100, Fryzura 67, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15176, 100, Fryzura 68, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15177, 100, Fryzura 69, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15178, 100, Fryzura 70, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15179, 100, Fryzura 71, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),
	(15180, 100, Fryzura 72, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_HAIRCUT),*/
	
	// Pierdo³y Custom 4.1
	(15067, 1800, Kolczyki 01, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
 	(15068, 400, Rozowy zegarek, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15069, 1200, Zlote bransoletki, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15070, 2400, Zloty zegarek, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15071, 600, Bia³y kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15072, 600, Szary kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15073, 600, Bialy kolczyk 2, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15074, 600, Zielony kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15075, 600, Niebieski kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15076, 600, Czerwony kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15077, 600, Czerwony kolczyk 2, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15078, 600, Czerwony kolczyk 3, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15079, 600, Zielony kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15080, 600, Niebieski kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15081, 600, Fioletowy kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15082, 50, Frotka 1, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15083, 50, Frotka 2, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15084, 50, Frotka 3, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15085, 1900, Srebrny kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15093, 1600, Czarny zegarek, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15095, 1900, Zloty naszyjnik, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
 	(15096, 900, Brazowy Zegarek, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15097, 900, Bezowy Zegarek, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15098, 2400, Zloty damski kolczyk, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15099, 600, Sluchawka BT, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15100, 1400, Klasyczyny zegarek, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15101, 1900, Zlota bransoleta, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15102, 1200, Klasyczny zegarek 2, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15103, 3000, Zloty CASIO, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
  	(15104, 1500, Czarny zegarek, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(15202, 12000, Louis Vuitton BLING, 17, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	
	
	
	// Sklepy z okularami
	(19006, 75,  Red glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19007, 75,  Victim glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19008, 75,  Green glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19009, 75,  Blue glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19010, 75,  Violet glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19011, 100, Psyho glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19012, 100, Elegant glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19013, 100, Binco glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19014, 150, Race glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19015, 100, Angel glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19016, 75,  R and B glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19017, 75,  Wayfarer yellow, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19018, 75,  Wayfarer orange, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19019, 75,  Wayfarer red, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19020, 75,  Wayfarer blue, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19021, 75,  Wayfarer green, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19022, 200, West black, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19023, 200, West blue, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19024, 200, West violet, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19025, 200, West pink, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19026, 200, West red, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19027, 200, West X, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
   	(19027, 200, West Yellow, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19028, 200, West green, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19029, 150, Vatsim glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19030, 150, Vatsim yellow, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19031, 150, Vatsim red, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19032, 200, Black glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19033, 200, Elev glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19034, 200, Future glass, 2, 0.08, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19968, 200, Czarne okulary, 2, 0.05149, 0.083879, 0.0, 4.72361, -4.5127, -2.5, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19967, 200, Kwadratowe okulary, 2, 0.05149, 0.071878, 0.0, 4.72361, -4.5127, -2.5, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19964, 150, Sportowe okulary 01, 2, 0.081998, 0.079999, 0.002999, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19963, 150, Sportowe okulary 02, 2, 0.081998, 0.079999, 0.002999, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19962, 220, Eleganckie okulary 01, 2, 0.081997, 0.015999, 0.002999, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19961, 220, Eleganckie okulary 02, 2, 0.081997, 0.015999, 0.002999, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	(19960, 300, Eleganckie okulary 03, 2, 0.083996, 0.019999, 0.002999, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_SHADES),
	
	// Czapki, kapelusze, berety itd
	(14169, 300, Durag1, 2, -0.699113, -0.017448, -0.062999, 167.304, 95.194, -176.845, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(14170, 300, Durag2, 2, -0.676002, 0.037001, 0.005006, -83.0, 93.6001, 76.9, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(14171, 300, Durag3, 2, -0.672113, -0.023448, -0.062999, 167.304, 95.194, -176.845, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18926, 150, Insestion cap, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18927, 150, Invation cap, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18928, 160, Binco adventure, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18929, 120, Binco X, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18930, 120, Binco red, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18931, 120, Future blue, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18932, 150, Future orange, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18932, 120, Future yellow, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18933, 120, El red, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18934, 120, El yellow, 2, 0.145899, -0.005373, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18638, 90,  Build Kask, 2, 0.164888, 0.028553, 0.000000, 176.004180, 178.093902, 186.354782, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18639, 180, Cowboy Hat, 2, 0.164888, 0.028553, 0.000000, 176.004180, 178.093902, 186.354782, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18944, 130, Elegant red, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18945, 120, Elegant x, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
 	(18945, 250, Elegant Victim, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
 	(18945, 255, Elegant Black, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18946, 175, Cape blue, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18946, 175, Cape green, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18947, 150, Cape red, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18948, 150, Cape yellow, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18949, 100, Howk black, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18950, 175, Howk best, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18951, 140, Howk X, 2, 0.143349, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18962, 180, Cowboy Hat 2, 2, 0.156087, -0.003380, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18964, 160, Black shoe, 2, 0.142538, -0.005465, 0.0, 40.929325, 91.085235, 56.034988, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18966, 145, Color shoe, 2, 0.142538, -0.005465, 0.0, 40.929325, 91.085235, 56.034988, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18967, 150, Class brown, 2, 0.140852, 0.013641, 0.0, 112.626106, 95.035888, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18968, 150, Class blue, 2, 0.140852, 0.013641, 0.0, 112.626106, 95.035888, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18969, 155, Class yellow, 2, 0.140852, 0.013641, 0.0, 112.626106, 95.035888, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18970, 150, Cape elegant, 2, 0.123022, 0.030276, 0.0, 82.742706, 95.204544, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
   	(18971, 150, Cape elegant 2, 2, 0.123022, 0.030276, 0.0, 82.742706, 95.204544, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18972, 200, Cape elegant 3, 2, 0.123022, 0.030276, 0.0, 82.742706, 95.204544, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18973, 260, Cape elegant 4, 2, 0.123022, 0.030276, 0.0, 82.742706, 95.204544, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18941, 85,  Czarna bejsbolowka, 2, 0.143999, -0.019, 0.006, -179.6, 0.0, 21.9, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18942, 85,  Niebieska bejsbolowka, 2, 0.143999, -0.019, 0.006, -179.6, 0.0, 21.9, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18943, 85,  Zielona bejsbolowka, 2, 0.143999, -0.019, 0.006, -179.6, 0.0, 21.9, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18921, 110, Black Beret, 2, 0.162611, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18922, 110, Brown Beret, 2, 0.162611, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18923, 110, Blue Beret, 2, 0.162611, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18924, 110, Moro Beret, 2, 0.162611, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(18925, 165, France Beret, 2, 0.162611, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19532, 400, Cylinder Czarny, 2, 0.093998, -0.013, 0.0, 107.1, 66.8, 162.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19487, 400, Cylinder Bialy, 2, 0.093998, -0.013, 0.0, 107.1, 66.8, 162.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19069, 100, Czapka, 2, 0.092608, 0.016999, 0.002, -56.6, 73.4, 145.0, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19815, 155, Kapelusz1, 2, 0.167998, -0.001999, -0.016995, -83.0, 93.6001, 171.9, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19814, 155, Kapelusz2, 2, 0.167998, -0.001999, -0.016995, -83.0, 93.6001, 171.9, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19812, 155, Kapelusz4, 2, 0.167998, -0.001999, -0.016995, -83.0, 93.6001, 171.9, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19811, 155, Kapelusz5, 2, 0.167998, -0.001999, -0.016995, -83.0, 93.6001, 171.9, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19810, 155, Kapelusz6, 2, 0.167998, -0.001999, -0.016995, -83.0, 93.6001, 171.9, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19808, 155, Czapka zimowa1, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19807, 155, Czapka zimowa2, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19806, 155, Czapka zimowa3, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19805, 155, Czapka zimowa4, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19804, 155, Czapka zimowa5, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19803, 155, Czapka zimowa6, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19802, 155, Czapka zimowa7, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(19801, 155, Czapka zimowa8, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	// CIMG 4.0
	(14049, 70, Czapka PR, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	(14048, 70, Czapka FR, 2, 0.130997, -0.037999, 0.006004, 174.3, -179.5, -161.6, OWNER_NONE, TYPE_NONE, SHOP_HATS),
	
	// Fullcapy
	(19985, 155, Fullcap1, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19984, 155, Fullcap2, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19983, 155, Fullcap3, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19982, 155, Fullcap4, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19980, 155, Fullcap6, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19979, 155, Fullcap7, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19978, 155, Fullcap8, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19977, 155, Fullcap9, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19976, 155, Fullcap10, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19975, 155, Fullcap11, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19974, 155, Fullcap12, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19973, 155, Fullcap13, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19972, 155, Fullcap14, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19969, 155, Fullcap17, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19826, 155, Fullcap18, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19818, 155, Fullcap19, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	(19817, 155, Fullcap21, 2, 0.094997, 0.009001, 0.006004, 161.5, 93.5, 13.8, OWNER_NONE, TYPE_NONE, SHOP_FULLCAP),
	
	// Kaski
	(18976, 400, HJC R-RHA, 2, 0.079383, 0.025340, 0.0, 95.945587, 85.987258, 0.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(18977, 200, Sooni MC10, 2, 0.079383, 0.025340, 0.0, 95.945587, 85.987258, 0.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(18978, 200, Throttle, 2, 0.079383, 0.025340, 0.0, 95.945587, 85.987258, 0.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(18979, 205, MCS-R1, 2, 0.079383, 0.025340, 0.0, 95.945587, 85.987258, 0.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	
	// Telefony
	(18866, 70, Phone orange, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18865, 70, Phone blue, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18866, 70, Phone self, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18867, 70, Phone black, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18868, 70, Phone pink, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18869, 70, Phone red, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18870, 90, Phone green, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18871, 85, Phone blue, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18872, 70, Phone yellow, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18873, 65, Phone white, 7, -0.002878, 0.105640, 0.024853, 274.914367, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19856, 520, BlackBerry, 7, -0.002878, 0.10564, 0.024853, 274.914, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19855, 410, Samsung Galaxy, 7, -0.002878, 0.10564, 0.024853, 274.914, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19854, 600, HTC, 7, -0.002878, 0.10564, 0.024853, 274.914, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19853, 350, Nokia, 7, -0.002878, 0.10564, 0.024853, 274.914, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19852, 470, SONY, Xperia Neo V, 7, -0.002878, 0.10564, 0.024853, 274.914, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19851, 370, Samsung, 7, -0.002878, 0.10564, 0.024853, 274.914, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19850, 650, IPhone, 7, -0.002878, 0.10564, 0.024853, 274.914, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	
	// Bandany
	(14031, 500, (B) Kominiara 3, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(14030, 500, (B) Kominiara 2, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(14029, 500, (B) Kominiara 1, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(18912, 480, (B) Black Bandana, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(18913, 450, (B) Green Bandana, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(18914, 480, (B) Moro Bandana, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(18915, 450, (B) Pink Bandana, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(18916, 445, (B) Yellow Bandana, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(18917, 380, (B) Psyho Bandana, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(18918, 380, (B) Angel Bandana, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(18919, 380, (B) Fun Bandana, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(18920, 380, (B) Experial Bandana, 2, 0.070531, 0.023475, 0.0, 89.837280, 174.963546, 91.600776, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(19824, 155, Bandana Purpurowa czolo, 2, 0.089997, -0.049999, -0.015999, 105.3, -34.8999, -85.1999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19823, 155, Bandana Zielona czolo, 2, 0.089997, -0.049999, -0.015999, 105.3, -34.8999, -85.1999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19821, 155, Bandana Czarna czolo , 2, 0.089997, -0.049999, -0.015999, 105.3, -34.8999, -85.1999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19820, 155, Bandana Szara czolo , 2, 0.089997, -0.049999, -0.015999, 105.3, -34.8999, -85.1999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19959, 155, Bandana Hawajska twarz, 2, -0.046002, 0.053, -0.009996, -6.70001, -10.7999, -21.6999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19958, 155, Bandana Czerwona twarz , 2, -0.046002, 0.053, -0.009996, -6.70001, -10.7999, -21.6999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19957, 155, Bandana Purp twarz , 2, -0.046002, 0.053, -0.009996, -6.70001, -10.7999, -21.6999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19956, 155, Bandana Zielona twarz , 2, -0.046002, 0.053, -0.009996, -6.70001, -10.7999, -21.6999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19955, 155, Bandana Nieb twarz , 2, -0.046002, 0.053, -0.009996, -6.70001, -10.7999, -21.6999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19954, 155, Bandana Czarna twarz , 2, -0.046002, 0.053, -0.009996, -6.70001, -10.7999, -21.6999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19953, 155, Bandana Wloska twarz , 2, -0.046002, 0.053, -0.009996, -6.70001, -10.7999, -21.6999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(19952, 155, Bandana Czacha twarz , 2, -0.046002, 0.053, -0.009996, -6.70001, -10.7999, -21.6999, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	
	// Chusty na g³owê
	(18891, 65, Blue Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18892, 65, Red Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18893, 65, Red & White Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18894, 65, Brown Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18895, 65, Experial Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18896, 65, Black Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18897, 65, H-Blue Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18898, 65, Night Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18899, 65, Pink Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18900, 65, Colour Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18901, 65, Moro Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18902, 65, Gold Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18903, 65, L-Blue Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18904, 65, Psyho Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18905, 65, Cline Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18906, 65, Gringe Up-Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18907, 65, Ungre Up-Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18908, 65, Psyho Up-Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18909, 65, L-Blue Up-Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	(18910, 65, Exotic Up-Shawl, 2, 0.129967, -0.003380, 0.0, 267.881774, 354.832885, 272.176177, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	
	// Maski
	(19036, 325, (B) White Mask, 2, 0.093492, 0.027876, 0.0, 85.123649, 88.987266, 0.0, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(19037, 325, (B) Red Mask, 2, 0.093492, 0.027876, 0.0, 85.123649, 88.987266, 0.0, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(19038, 325, (B) Green Mask, 2, 0.093492, 0.027876, 0.0, 85.123649, 88.987266, 0.0, OWNER_GROUP, GROUP_CRIMINAL, SHOP_MASKS),
	(19951, 425, Maska psychopaty, 2, 0.101, 0.025, 0.001, -3.018, -2.767, 3.576, OWNER_NONE, TYPE_NONE, SHOP_MASKS),
	
	// Reszta - elektroniczny
	(1210, 200,  Teczka, 6, 0.266997, -0.002999, 0.032999, 8.3, -100.5, 175.9, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(3026, 85,   Plecak, 1, -0.118998, 0.024001, 0.025, 170.0, 177.8, 176.2, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19348, 350, Elegancka Laska, 8, 0.079999, 0.043, 0.0, 100.0, 90.0, -10.0, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(18875, 80,  Pager, 1, -0.248391, 0.225994, 0.056, -72.0998, 94.0, -99.6, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19421, 130, Sluchawki Biel, 2, 0.054967, -0.003378, 0.0, 267.882, 354.833, 272.176, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19422, 130, Sluchawki Czern, 2, 0.054967, -0.003378, 0.0, 267.882, 354.833, 272.176, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19423, 130, Sluchawki Czerwone, 2, 0.054967, -0.003378, 0.0, 267.882, 354.833, 272.176, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19424, 130, Sluchawki Niebieskie, 2, 0.054967, -0.003378, 0.0, 267.882, 354.833, 272.176, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19918, 155, Mikrofon, 6, 0.023, 0.018, 0.076999, -176.3, -141.3, -151.9, OWNER_GROUP, GROUP_NEWS, SHOP_ELECTRONIC),
	(19874, 155, Sluchawki SONY, 2, 0.1, -0.000999, 0.002998, -176.4, 102.694, 94.00001, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19873, 155, Sluchawki Czarne, 2, 0.081999, -0.000999, -0.002002, -176.4, 8.00008, 23.2001, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	(19871, 155, Sluchawki Nb-Szare, 2, 0.081999, -0.000999, -0.002002, -176.4, 8.00008, 23.2001, OWNER_NONE, TYPE_NONE, SHOP_ELECTRONIC),
	
	// Sklep z narzedziami
	(18633, 115, Klucz do kol, 6, 0.095897, 0.046626, 0.061999, 96.4, -101.3, 0.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(18644, 85, Srubokret, 5, 0.114897, 0.032627, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(18635, 95, Mlotek, 6, 0.023609, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(18634, 125, Lom, 6, 0.044966, 0.030622, 0.017999, 5.68194, -101.067, -91.724, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(19472, 150, Maska do lakierowania, 2, -0.033999, 0.131998, -0.000999, 100.0, 99.9, -10.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	
	// Los Santos Police Department
	(18636, 90,  Czapka LSPD, 2, 0.132608, 0.034999, -0.002001, 67.7, 83.0, 17.6, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(19200, 350,  Helm LSPD, 2, 0.132608, 0.034999, -0.002001, 67.7, 83.0, 17.6, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD), // SELER
	(19775, 100,  Odznaka LSPD, 1, -0.232002, 0.198999, 0.038999, 102.6, 166.5, -95.0001, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD), // SELER
	(19141 , 300,  Helm, 2, 0.132608, 0.034999, -0.002001, 67.7, 83.0, 17.6, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD), // SELER
	(19142, 350,  Helm LSPD, 1, 0.013999, 0.040998, -0.002001, 67.7, 83.0, 17.6, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD), // SELER
	(19142, 400,  Skorzana kabura, 8, 0.103939, -0.004001, -0.055999, -94.7, -93.2, -165.5, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD), // SELER
	(19515, 350, Kevlar SWAT, 1, 0.013999, 0.040998, -0.002001, 67.7, 83.0, 17.6, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(19100, 110, Braz. Kap. PD, 2, 0.172607, -0.031999, -0.007, 0.0, -1.6, -26.6, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(19099, 110, Czern. Kap. PD, 2, 0.172607, -0.031999, -0.007, 0.0, -1.6, -26.6, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(18637, 275, Tarcza LSPD, 13, 0.403121, -0.04936, -0.010147, -12.386, 0.0, 162.2, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(19515, 350, Kevlar DEVGRU, 1, 0.013999, 0.040998, -0.002001, 67.7, 83.0, 17.6, OWNER_GROUP, GROUP_ARMY, SHOP_LSPD),
	(14004, 175, Czapka Policyjna, 2, 0.130999, 0.003999, 0.001999, 2.0, 4.50001, -11.9, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(14003, 50,  Odznaka, 1, -0.232002, 0.198999, 0.038999, 102.6, 166.5, -95.0001, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(14002, 125, Kevlar, 1, 0.114999, 0.047, 0.0, -2.10003, 0.000006, 0.199997, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(19565, 100, Krotkofalowka, 4, 0.103939, -0.004001, -0.055999, -94.7, -93.2, -165.5, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(19559, 155, Maska przeciwgazowa, 2, 0.521999, 0.036, -0.101, -176.3, -178.2, -161.7, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(19966, 200, Okulary Crossbow X2, 2, 0.04449, 0.022878, -0.002999, 4.32361, 82.8873, -2.5, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(19600, 70, Atrapa, 4, 0.103939, -0.004001, -0.055999, -94.7, -93.2, -165.5, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	// CIMG 4.0
	(14027, 350, Kevlar FBI, 1, 0.013999, 0.040998, -0.002001, 67.7, 83.0, 17.6, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	(14028, 350, Kevlar DOC, 1, 0.013999, 0.040998, -0.002001, 67.7, 83.0, 17.6, OWNER_GROUP, GROUP_POLICE, SHOP_LSPD),
	
	// Fire Department	
	(19330, 150, Helm FD, 2, 0.16261, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),
	(19559, 155, SCBA Mask, 2, 0.521999, 0.036, -0.101, -176.3, -178.2, -161.7, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),
	(19581, 155, Czapka FD, 2, -0.643999, -0.104999, -0.031, -176.3, -178.2, -172.1, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),
	(19580, 155, SCBA, 1, -0.169998, 0.014001, -0.034998, -174.7, 94.5, 177.0, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),
	(19536, 260, Foam extinguisher, 5, 0.715606, 0.039999, 0.079999, -16.9, -99.4, 0.0, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),
	(19913, 230, Defibrylator, 6, 0.201602, 0.053998, 0.000999, -110.5, 170.1, -82.7999, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),
	(19584, 160, Helm, 2, -0.67351, 0.063877, 0.009, -1.67641, 0.987298, -3.2, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),
    (14178, 200, Siekiera LSFD, 6, -0.086063, 0.031002, 0.336001, -92.7, -179.5, -61.8001, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),
    (14179, 100, Torba medyczna, 6, 0.180937, -0.057997, 0.044, -96.6, -85.2, -93.9001, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),
	(19610, 350, Nozyco-rozpierak, 6, -0.086063, 0.031002, 0.336001, -92.7, -179.5, -61.8001, OWNER_GROUP, GROUP_FIREDEPT, SHOP_FD),

    // EMS	
    (19913, 230, Defibrylator, 6, 0.201602, 0.053998, 0.000999, -110.5, 170.1, -82.7999, OWNER_GROUP, GROUP_MEDICAL, SHOP_EMS),
    (14179, 100, Torba medyczna, 6, 0.180937, -0.057997, 0.044, -96.6, -85.2, -93.9001, OWNER_GROUP, GROUP_MEDICAL, SHOP_EMS),
    (19565, 160, Krotkofalowka, 6, 0.075599, 0.027, 0.031998, 22.0, -20.8, 178.1, OWNER_GROUP, GROUP_MEDICAL, SHOP_EMS),
	(19602, 100, Maseczka, 2, 0.16261, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_GROUP, GROUP_MEDICAL, SHOP_EMS),
	(19627, 60, Stetoskop, 2, 0.16261, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_GROUP, GROUP_MEDICAL, SHOP_EMS),
	(19603, 50, Czepek, 2, 0.16261, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_GROUP, GROUP_MEDICAL, SHOP_EMS),
	(14035, 50, Maska EMS, 2, 0.16261, 0.0, 0.0, 0.0, 0.0, 0.0, OWNER_GROUP, GROUP_MEDICAL, SHOP_EMS),
	
	// DSE - Department of Sanitation & Electrocity
	(2712, 50, Miotla, 6, 0.201602, 0.053998, 0.000999, -110.5, 170.1, -82.7999, OWNER_GROUP, GROUP_MEDICAL, SHOP_DSE),
	(910, 85,  Szlaban, 1, -0.084003, 0.024995, 0.028999, 4.89997, 2.29998, -10.0, OWNER_NONE, TYPE_NONE, SHOP_DSE),
	(1430, 45,  Kosz, 1, -0.084003, 0.024995, 0.028999, 4.89997, 2.29998, -10.0, OWNER_NONE, TYPE_NONE, SHOP_DSE),
	(19574, 50, Narzedzia, 6, 0.201602, 0.053998, 0.000999, -110.5, 170.1, -82.7999, OWNER_NONE, TYPE_NONE, SHOP_DSE),

	// Torby
	(19988, 150,  Torebka niebieska, 15, -0.152003, 0.024996, -0.441, 4.89997, 2.29998, -10.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(19987, 150,  Torebka czerwona, 15, -0.152003, 0.024996, -0.441, 4.89997, 2.29998, -10.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(19986, 150,  Torebka czarna, 15, -0.152003, 0.024996, -0.441, 4.89997, 2.29998, -10.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(19989, 120,  Czarny plecak, 1, -0.084003, 0.024995, 0.028999, 4.89997, 2.29998, -10.0, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(19992, 180,  Torba do reki, 6, 0.209996, -0.010005, 0.028999, -74.2001, 3.89999, 96.4999, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(19991, 140,  Mala szara torba, 6, 0.152995, 0.005995, -0.019001, -162.2, 93.5001, 106.3, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(19990, 120,  Torebka na ramie, 15, -0.026004, 0.004994, -0.244, -158.0, -97.5999, 124.2, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	(325, 100,  Kwiatki, 6, 0.045936, -0.053997, 0.029, -174.0, -135.1, -98.9001, OWNER_NONE, TYPE_NONE, SHOP_UTILITY),
	//(14183, 200, Pies, 6, 0.017937, -0.203999, -0.274999, -110.7, -90.3001, -117.5, OWNER_NONE, TYPE_NONE, SHOP_UTILITY), // FRESHER STAHP
	
	// Bi¿uteria - 17 to szyja
	(19611, 5, Frotka, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19760, 1200, Zegarek 01, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19761, 1460, Zegarek 02, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19567, 1200, Zegarek 03, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19568, 2300, Zegarek 04, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19879, 1800, Zegarek 05, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19883, 1080, Zegarek 06, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19884, 550, Lancuszek 01, 17, 0.033123, 0.046639, 0.005851, 178.714, 0.0, -65.1, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19885, 650, Lancuszek 02, 17, 0.033123, 0.046639, 0.005851, 178.714, 0.0, -65.1, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19886, 350, Lancuszek 03, 17, 0.033123, 0.046639, 0.005851, 178.714, 0.0, -65.1, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19887, 450, Lancuszek 04, 17, 0.033123, 0.046639, 0.005851, 178.714, 0.0, -65.1, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19905, 450, Lancuszek 05, 17, 0.033123, 0.046639, 0.005851, 178.714, 0.0, -65.1, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19904, 650, Lancuszek 06, 17, 0.033123, 0.046639, 0.005851, 178.714, 0.0, -65.1, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19903, 290, Lancuszek 07, 17, 0.033123, 0.046639, 0.005851, 178.714, 0.0, -65.1, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19902, 600, Lancuszek 08, 17, 0.033123, 0.046639, 0.005851, 178.714, 0.0, -65.1, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),	
	(19910, 250,  Bransoleta 01, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19909, 250,  Bransoleta 02, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19908, 250, Sygnet 05, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19907, 550, Sygnet 06, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19906, 350, Sygnet 07, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(14041, 2150, Zegarek Gucci, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(13997, 750, Lancuszek 09, 17, 0.033123, 0.046639, 0.005851, 178.714, 0.0, -65.1, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),	
	
	
//    (19889, 250, Sygnet 01, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
//    (19890, 350, Sygnet 02, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
//    (19898, 400, Sygnet 03, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
//    (19899, 250, Sygnet 04, 6, 0.101122, 0.029638, 0.020851, -178.286, -170.2, 47.5, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19040, 250,  Zegarek Srebro, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19039, 350,  Zegarek Zloto, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19043, 250,  Zegarek Dam. Srebro, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19042, 350,  Zegarek Dam. Zloto, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19567, 2000, Zegarek Rolex, 5, 0.007999, 0.011011, -0.001001, 172.0, -11.6999, -68.2999, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19041, 175,  Zegarek Ecru, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19044, 100,  Zegarek Purpura, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19045, 100,  Zegarek Czerwien, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19046, 100,  Zegarek Zielen, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY),
	(19047, 100,  Zegarek Fiolet, 6, -0.032099, -0.015371, 0.009, -108.3, -114.4, 88.3, OWNER_NONE, TYPE_NONE, SHOP_JEWELLRY)
)

Fonts(20)(32) =
(
	Beckett,
	Amprior,
	Kredit,
	Tahoma,
	Times New Roman,
	Arial,
	Diploma,
	Street Soul,
	BAUHAUS 93,
	Broodway,
	cooper blACK,
	Impact,
	OLD ENGLISH TEXT MT,
	playbill,
	ravie,
	showcard gothic,
	SNAP ITC,
	wide latin,
	goudy stout,
	FORTE
)

FontSizes(21) = 
(
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30
)

enum sAttachData
(
	aUID,
	
	aModel,
	aBone,

	Float:aPosX,
	Float:aPosY,
	Float:aPosZ,

	Float:aRotX,
	Float:aRotY,
	Float:aRotZ,

	Float:aScaleX,
	Float:aScaleY,
	Float:aScaleZ
)
PlayerAttach(MAX_PLAYERS)(sAttachData)

Float:SalonVehSpawnPos(5)(4) =
(
	(901.3408, -1208.8365, 16.8620, 178.8416),
	(866.7073, -1209.3844, 16.8687, 176.9288),
	(830.8945, -1208.5759, 16.8481, 177.3645),
	(729.4213, -1533.5233, 2.78910, 335.1115), // £odzie
	(1968.5499, -2324.6646, 13.5469, 103.8927) // Samoloty
)

// Pozycje hurtowni
Float:WholeSalePos(3)(3) =
(
	(-189.2011, -278.2386, 1.1548),
	(580.0261, 1219.6764, 11.4348),
	(-535.4456, -543.3052, 25.5234)
)

Penalties(9)(128) =
(
	Blokada biegania i bicia 7 dni,
	Blokada prowadzenia pojazdów 7 dni,
	AJ na 60 minut za odwalanie,
	Ban permamentny za cheatowanie,
	Reset na spawn,
	Spec,
	Goto,
	Gethere,
	Freeze
)

// Cele policyjne
enum sPoliceCell
(
	Float:pCellX,
	Float:pCellY,
	Float:pCellZ,
	pCellVW,
	pCellCleaned
)

PoliceCell(24)(sPoliceCell) =					// areszto-wiêzienie selera
(	
	(1787.4008,-1551.0262,39.9252,6299,0),
	(1790.7017,-1551.3041,39.9252,6299,0),
	(1793.7810,-1551.0729,39.9252,6299,0),
	(1796.9584,-1551.2307,39.9252,6299,0),	// 5
	(1799.7145,-1551.2115,39.9252,6299,0),
	(1803.0217,-1551.8059,39.9252,6299,0),
	(1806.2188,-1551.4471,39.9252,6299,0),
	(1806.4120,-1535.5288,39.9252,6299,0),
	(1803.1946,-1535.4772,39.9252,6299,0),	// 10
	(1800.1265,-1535.9099,39.9252,6299,0),
	(1796.4945,-1535.8882,39.9252,6299,0),
	(1793.4153,-1535.3231,39.9252,6299,0),
	(1790.3156,-1535.5457,39.9252,6299,0),
	(1787.1870,-1535.2327,39.9252,6299,0),	// 15
	(1787.3840,-1551.5543,43.4453,6299,0),
	(1792.3951,-1551.6124,43.4453,6299,0),
	(1796.9711,-1551.7529,43.4453,6299,0),
	(1801.5944,-1551.9043,43.4453,6299,0),
	(1806.4132,-1552.1539,43.4453,6299,0),	// 20
	(1806.3759,-1535.3701,43.4253,6299,0),
	(1801.9672,-1535.2087,43.4253,6299,0),
	(1796.7880,-1534.7025,43.4253,6299,0),
	(1792.2379,-1535.2263,43.4253,6299,0),
	(1787.3933,-1535.1246,43.4253,6299,0)		// 24
)

/*
PoliceCell(12)(sPoliceCell) =
(	
	(1951.3180,-2363.4856,13.6128, 4171),
	(1948.2635,-2364.1211,13.6128, 4171),
	(1944.9576,-2363.6975,13.6128, 4171),
	(1942.0406,-2364.1833,13.6128, 4171),
	(1938.6552,-2363.9849,13.6128, 4171),		// 5
	
	(1977.7693,-2334.2451,13.5628, 4709),
	(1977.8047,-2328.9304,13.5628, 4709),
	(1977.2230,-2323.8835,13.5628, 4709),
	(1977.2106,-2318.9895,13.5628, 4709),
	(1977.8752,-2313.8030,13.5628, 4709),
	(1977.7727,-2308.5188,13.5628, 4709),
	(1977.6841,-2303.2739,13.5628, 4709)
)
*/

enum surfPars
(
	surfModelID,
	surfObjectID,
	Float:surfSpeed,
	Float:surfPos(7),
	surfPlayerID,	//id akutalnego gracza
	
	Float:surfPosTo(3),		//do jakich coordów ma siê move
)
Surfboard(MAX_SURFBOARDS)(surfPars)

// Skateboardy
/*enum skatePars
(
	skateModelID,
	skateObjectID,
	Float:skateSpeed,
	Float:skatePos(7),
	skatePlayerID,
	
	Float:skatePosTo(3),
)
Skateboard(MAX_SURFBOARDS)(skatePars)*/

/*
PoliceCell(45)(sPoliceCell) =
(
	(-1018.1803,-951.9262,129.2491,1734),
	(-1022.9058,-951.5172,129.2491,1734),
	(-1028.1917,-948.5831,129.2491,1734),		// A A A A A A A A A A A A A A A A A A A A A     1734 1734 1734 1734 1734
	(-1027.2816,-942.9751,129.2491,1734),		// Total: 5 (0-4)
	(-1027.9224,-938.1151,129.2491,1734),
	
	(-995.3753,-896.1301,139.5081,1551),
	(-991.1744,-895.8486,139.5081,1551),
	(-987.2761,-895.7124,139.5081,1551),
	(-983.4036,-895.6171,139.5081,1551),
	(-978.9529,-896.4439,139.5081,1551),
	(-974.4930,-891.9888,139.5081,1551),
	(-974.9788,-886.8780,139.5081,1551),			// B B B B B B B B B B B B B B B B B B B B B	1551 1551 1551 1551 1551
	(-975.0005,-883.3315,139.5081,1551),			// Total: 14 (5-19)
	(-974.5132,-877.9459,139.5081,1551),
	(-979.2076,-874.1951,139.5081,1551),
	(-983.4185,-874.3359,139.5081,1551),
	(-987.3472,-875.0139,139.5081,1551),
	(-991.5054,-874.7267,139.5081,1551),
	(-995.2129,-874.5716,139.5081,1551),
	
	(1656.4911,-1100.1270,-18.8440,1363),
	(1660.6179,-1099.7604,-18.8440,1363),
	(1664.8678,-1100.0033,-18.8440,1363),
	(1668.6906,-1099.4979,-18.8440,1363),
	(1672.7830,-1099.6467,-18.8440,1363),
	(1676.8540,-1099.6622,-18.8440,1363),
	(1680.8275,-1099.2784,-18.8440,1363),
	(1680.5704,-1099.6112,-14.7459,1363),
	(1676.5593,-1099.4967,-14.7459,1363), 		// C C C C C C C C C C C C C C C C C C C C C C		1363 1363 1363 1363 1363
	(1672.4681,-1099.4150,-14.7514,1363),		// Total: 21 (20-41)
	(1668.3085,-1099.5050,-14.7514,1363),
	(1664.6855,-1099.1993,-14.7526,1363),
	(1660.7916,-1099.1760,-14.7526,1363),
	(1656.0975,-1099.2374,-14.7668,1363),
	(1656.7898,-1099.0344,-10.7331,1363),
	(1660.9839,-1099.9437,-10.7331,1363),
	(1665.1639,-1100.5343,-10.7277,1363),
	(1669.3406,-1100.9869,-10.7242,1363),
	(1672.9146,-1099.4435,-10.7242,1363),
	(1676.8774,-1099.6989,-10.7245,1363),
	(1680.6217,-1099.7023,-10.7245,1363),
	
	(-1655.5168,-257.2651,14.6625,1112),
	(-1655.4396,-263.0520,14.7599,1112),
	(-1655.3329,-268.3017,14.7599,1112),		// Izolatki Izolatki Izolatki Izolatki Izolatki 1112 1112 1112 1112 1112 1112
	(-1655.5941,-274.0429,14.7599,1112),		// Total: 5 (42-47)
	(-1655.7947,-280.7654,14.1809,1112)
)
*/

//Admini
enum sAdminLevels
(
	lColor(8),
	lTag(32)
)
AL(7)(sAdminLevels) = 
(
	(FFFFFF, Gracz),
	(FF574F, Administrator),
	//(8B0000, Moderator),
	(FF9900, Administrator),
	(6CC417, Gamemaster),
	(6698FF, Supporter),
	(6600CC, Nauczyciel),
	(FF1CD2, Engineer)
)

//£ó¿ka
enum sHospitalBeds
(
	Float:bPosX,
	Float:bPosY,
	Float:bPosZ,
	bVW,
	bINT
)

HospitalBed(9)(sHospitalBeds) =
(
	//(1171.7206,-1331.2103,16.2083,518,0),
	//(1171.7753,-1333.5444,16.2083,518,0),
	//(1171.6532,-1339.8821,16.2083,518,0),
	//(1171.7124,-1337.5037,16.2083,518,0),
	(1159.6685, -1303.8372, 16.1133, 2825, 0),
	(1159.3569, -1301.4889, 16.1233, 2825, 0),
	(1159.4043, -1299.0885, 16.1333, 2825, 0),
	(1165.1311, -1320.0677, 20.2075, 2825, 0),
	(1165.0632, -1322.7327, 20.2074, 2825, 0),
	(1165.2289, -1329.1542, 20.2174, 2825, 0),
	(1165.3750, -1326.3289, 20.2174, 2825, 0),		// 7
	(1766.3138, -1546.8505, 40.6820, 6299, 0),		// wiezienie
	(1766.0090, -1550.0028, 40.6720, 6299, 0)			// wiezienie
)

//Obiekty odk³adalne
enum pPutablePars
(
	pObjUID,
	pObjVW,
	pObjID,
	pObjOwner,
)
PutableObject(MAX_PLAYERS)(pPutablePars)

Captcha(36)(2) =
(
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	w,
	v,
	x,
	y,
	z,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	0
)

Letters(26)(2) =
(
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	w,
	v,
	x,
	y,
	z
)
// WTF i sie dziwisz potem ze bugi
//#define true false
Colors(6)(2) = 
(
	w,
	r,
	g,
	y,
	p,
	b
)

LSPad_AudioURLs(20)(128) =
(
	http://radiozetmp3-07.eurozet.pl:8400/listen.pls,
	http://www.radioparty.pl/all.m3u,
	http://www.polskastacja.pl/play/reggae.pls,
	http://www.polskastacja.pl/play/aac_ibizahits.pls,
	http://www.polskastacja.pl/play/hiphop.pls,
	http://www.radiosfera.pl/reggae.m3u,
	http://polskastacja.pl/play/aac_discopolo.pls,
	http://www.miastomuzyki.pl/n/rmfhiphop.pls,
	http://www.polskastacja.pl/play/drumbass.pls,
	http://www.polskastacja.pl/play/aac_mocne.pls,
	http://polskastacja.pl/play/clubhits.pls,
	http://files.kusmierz.be/rmf/rmfdance.mp3,
	http://www.miastomuzyki.pl/n/rmfchillout.pls,
	http://magnatune.com/genres/m3u/metal.m3u,
	http://www.radioparty.pl/play/energy2000.m3u,
	http://files.kusmierz.be/rmf/top5dance-1.mp3,
	http://listen.radionomy.com/a2r-rap-us.m3u,
	http://www.miastomuzyki.pl/n/rmfmaxxx.pls,
	http://www.di.fm/mp3/electro.pls,
	http://www.bassdrive.com/v2/streams/BassDrive.pls
)

LSPad_AudioURLNames(20)(128) =
(
	Radio Zet,
	Radio Party,
	Polska Stacja Reggae,
	Ibiza Hits,
	Polska Stacja Hip-Hop,
	Radio Strefa Reggae,
	Polska Stacja Discopolo,
	Miasto Muzyki Hip-Hop,
	Stacja Drumbass,
	Mocny ROCK,
	Polska Stacja ClubHits,
	RMF Dance,
	Miasto Muzyki Chillout,
	Magnatune - Metal,
	Energy2000 Club,
	Radiowe Hity,
	Radionomy Rap,
	RMF MAXXX,
	Electro,
	Bass Drive
)

enum zonePars
(
	zUID,
	Float:zMinX,
	Float:zMinY,
	Float:zMaxX,
	Float:zMaxY,
	zOwner,
	zType,
	zSID, // gangzone id
	bool:zBlocked,		//czy atakowana dzis juz byla, jak true to sie nie da znow
	zPackage,		//czy pobra³ bonus ze strefy
)
ZoneInfo(MAX_ZONES)(zonePars)


// moze potem
/*enum exZoneBiz
(
	gUID,
	Float:gRange,
	Float:gPosX,
	Float:gPosY,
	Float:gPosZ,
	gGroup,
)
GroupZone(100)(exZoneBiz)*/

enum seedPars
(
	sUID,
	Float:sPosX,
	Float:sPosY,
	Float:sPosZ,
	sType,
	sValue,
	sPlantTime,
	sWeed,			// czy nawo¿one by³o, ewentualnie ile razy
	sOwner,
	sObject,			// Id obiektu ktory trzyma konkretny seedPars
	Text3D:sLabel,				// Wiadomo
	bool:isSplashed,				// czy spryskano t¹ roœlinê
	Float:sWater,					// poziom podlania
)
SeedInfo(MAX_SEEDS)(seedPars)


// Tablica na u¿ywane wozy mo¿liwe do kupna
enum usedPars
(
	uModel,
	uName(64),
	uCost
)
UsedCars()(usedPars) =
(
	(439, Uzywany Stallion, 8000),
	(445, Uzywany Admiral, 13000),
	(467, Uzywany Oceanic, 3000),
	(479, Uzywana Regina, 4200),
	(517, Uzywany Majestic, 6300),
	(527, Uzywana Cadrona, 7250)
)

// Tablica przechowuj¹ca Cornery
enum corPars
(
	Float:cPosX,
	Float:cPosY,
	Float:cPosZ,
	bool:isUsed,
	cRisk,			// wspó³czynnik przypa³u
	cOwner,
)
CornerInfo(MAX_CORNERS)(corPars) = 
(
	(2594.6860,-1059.2239,69.5762,false,7,0),
	(2442.0339,-1247.5411,23.8869,false,7,0),
	(2507.9468,-1245.8607,35.2158,false,7,0),
	(2080.9189,-1291.8046,23.9772,false,7,0),
	(1983.3112,-1235.5494,20.0469,false,7,0),
	(2175.4453,-1309.4824,23.9844,false,7,0),
	(2331.1482,-1423.7247,24.0000,false,7,0),
	(2171.1257,-1394.7711,23.9917,false,7,0),
	(2331.9634,-1494.6522,24.0837,false,7,0),
	(2397.9326,-1668.4370,13.5469,false,7,0),
	(2304.5540,-1648.4424,14.5310,false,7,0),
	(2057.7959,-1780.2201,13.5469,false,7,0),
	(2128.7788,-1741.6637,13.5666,false,7,0),
	(2264.5339,-1759.6631,13.5469,false,7,0),
	(2070.9827,-1898.0067,13.5538,false,7,0),
	(1855.1886,-1722.0898,13.5369,false,7,0),
	(1932.1215,-1809.7803,13.5469,false,7,0),
	(2037.1779,-1661.6519,13.5469,false,7,0),
	(2173.8750,-1724.1127,13.5377,false,7,0),
	(2072.0784,-1681.8990,13.5391,false,7,0),
	(2459.8298,-1435.6251,23.8794,false,7,0),
	(2580.2451,-1265.7621,46.1498,false,7,0),
	(2175.7947,-1291.6384,23.9766,false,7,0),
	(2166.6926,-1212.5024,23.9610,false,7,0),
	(2209.8889,-1148.1661,25.7564,false,7,0),
	(2249.3721,-1032.8508,55.2877,false,7,0),
	(2136.2163,-1205.9661,23.9739,false,7,0),
	(2312.6108,-1162.2029,26.9749,false,7,0),
	(2181.6375,-1258.2410,23.9770,false,7,0),
	(1811.6478,-2101.4124,13.5469,false,7,0),
	(1944.2704,-2120.8513,13.5519,false,7,0),
	(1937.3500,-2029.4950,13.5547,false,7,0),
	(1952.5253,-1940.0790,13.5469,false,7,0),
	(1971.3254,-1969.2551,13.5526,false,7,0),
	(2208.9465,-1904.0974,13.5469,false,7,0),
	(2304.0295,-1904.3667,13.6172,false,7,0),
	(2366.3425,-1931.2426,13.3973,false,7,0),
	(2422.9966,-2000.3527,13.5469,false,7,0),
	(2423.8918,-1883.9250,13.5469,false,7,0),
	(2760.1340,-1982.2906,13.5484,false,7,0),
	(2723.3562,-2058.3369,13.5469,false,7,0),
	(2645.1873,-1993.5856,13.5554,false,7,0)
)

// Œrednia wartoœc narkotyku
DrugCost(11) = 
(
0, 		// nie wa¿ne
20,		 // marycha - U
130,			// kokaina - U
60,			// heroina - U
70,			//amfetamina - U
40,			// medicine ?
80,			// crack -- 6
100, 		// LSD
80, 		// grzybki
90,			// Kolejnie nie wazne MDMA?
90			// Metaamfetamina - U
)

// --- Scena muzyczna ---
Float:scenePosX = 0.0
Float:scenePosY = 0.0
Float:scenePosZ = 1000.0
sceneWorld = 0
Float:sceneRadius = 0.0
bool:sceneWorks = false
sceneDJ = INVALID_PLAYER_ID
sceneStream(256)
isScened(MAX_PLAYERS)		// no nie wiem, tak dziwnie nazwane chodzi o to czy akurat koleœ teraz s³ucha

// Wiêzienie - seler
PrisonWorld = 6299

//15188, 15108
HairIDs() = 
(
	15108,
	15109,
	15110,
	15111,
	15112,
	15113,
	15114,
	15115,
	15116,
	15117,
	15118,
	15119,
	15120,
	15121,
	15122,
	15123,
	15124,
	15125,
	15126,
	15127,
	15128,
	15129,
	15130,
	15131,
	15132,
	15133,
	15134,
	15135,
	15136,
	15137,
	15138,
	15139,
	15140,
	15141,
	15142,
	15143,
	15144,
	15145,
	15146,
	15147,
	15148,
	15149,
	15150,
	15151,
	15152,
	15153,
	15154,
	15155,
	15156,
	15157,
	15158,
	15159,
	15160,
	15161,
	15162,
	15163,
	15164,
	15165,
	15166,
	15167,
	15168,
	15169,
	15170,
	15171,
	15172,
	15173,
	15174,
	15175,
	15176,
	15177,
	15178,
	15179,
	15180,
	15181,
	15182,
	15183,
	15184,
	15185,
	15186,
	15187,
	15188
)

public LoadSettings()
(
	data(256)
	mysql_query(SELECT * FROM hrp_settings LIMIT 1)
	
 	print((load) Rozpoczynam proces wczytywania ustawieñ g³ównych...)

	mysql_store_result()
	if(mysql_fetch_row(data, |))
	(
	 	sscanf(data, p(|)ffffddffffd,
		SettingData(MainSpawnPos)(0),
		SettingData(MainSpawnPos)(1),
		SettingData(MainSpawnPos)(2),
		SettingData(MainSpawnPos)(3),
		SettingData(MainSpawnInt),
		SettingData(MainSpawnVW),
		SettingData(HotelPos)(0),
		SettingData(HotelPos)(1),
		SettingData(HotelPos)(2),
		SettingData(HotelPos)(3),
		SettingData(HotelInt))

		print((load) Proces wczytywania g³ównych ustawieñ przebieg³ bezproblemowo.)
	)
   	else
   	(
		print((load) Wyst¹pi³ b³¹d podczas procesu wczytywania ustawieñ. Prawdopodobnie nie odnaleziono tabeli hrp_settings w bazie danych.)
	)
	mysql_free_result()
	return 1
)

stock hrp_ShowPlayerDialog(playerid, dialogid, style, caption(), infoo(), button1(), button2())
(
	PlayerCache(playerid)(pDialog) = dialogid
	return ShowPlayerDialog(playerid, dialogid, style, caption, infoo, button1, button2)
)

#define ShowPlayerDialog hrp_ShowPlayerDialog

// Redefine CreateDynamicObject - nie ma wszystkich argumentów, to tylko test
stock lsrp_CreateDynamicObject(modelid, Float:PosX = 0.0, Float:PosY = 0.0, Float:PosZ = 0.0, Float:RotX = 0.0, Float:RotY = 0.0, Float:RotZ = 0.0, interior_id = 0, world_id = 0, playerid = -1, Float:streamdistance = 200.0, Float:drawdistance = 200.0)
(
	first_id = -1, second_id = -1
	first_id = CreateDynamicObject(modelid, PosX, PosY, PosZ, RotX, RotY, RotZ, interior_id, world_id, playerid, streamdistance, drawdistance)
	if(first_id == 65545 || first_id == 65535)
	(
		second_id = CreateDynamicObject(modelid, PosX, PosY, PosZ, RotX, RotY, RotZ, interior_id, world_id, playerid, streamdistance, drawdistance)
		DestroyDynamicObject(first_id)
		return second_id
	)
	else
	(
		return first_id
	)
)

#define CreateDynamicObject lsrp_CreateDynamicObject

// News
Weather(4) = (30, 60, 12, 4)
WeatherTypes(5)(32) =
(
	Deszczowy,
	Sniezny,
	Wietrzny,
	Pochmurny,
	Sloneczny
)

LSPadBackgrounds(24)(32) =
(
	ld_shtr:bstars,
	ld_spac:duality,
	ld_spac:backgnd,
	loadsc1:loadsc1,
	loadsc10:loadsc10,
	loadsc11:loadsc11,
	loadsc12:loadsc12,
	loadsc13:loadsc13,
	loadsc14:loadsc14,
	loadsc2:loadsc2,
	loadsc3:loadsc3,
	loadsc4:loadsc4,
	loadsc5:loadsc5,
	loadsc6:loadsc6,
	loadsc7:loadsc7,
	loadsc8:loadsc8,
	loadsc9:loadsc9,
	splash2:splash2,
	splash1:splash1,
	ld_plan:tvbase,
	ld_plan:airlogo,
	ld_grav:bumble,
	ld_bum:bum1,
	ld_bum:bum2
)

enum pBoxPoints
(
	Float:bPosX,
	Float:bPosY,
	Float:bPosZ,
)
BoxPositions(4)(pBoxPoints) = 
(
	(2785.0874,-2464.4580,13.6343),
	(2782.6523,-2487.8835,13.6565),
	(2782.5071,-2409.4216,13.6350),
	(2794.4661,-2373.4319,13.6320)
)

enum corpPars
(
	Float:corPosX,
	Float:corPosY,
	Float:corPosZ,
	Float:corAngle,
)
CorPositions()(corpPars) = 
(
	(362.0674,171.4521,1025.7891,179.2456),
	(364.1038,152.6415,1025.7964,359.7039),
	(356.3162,152.7944,1025.7891,356.8838),
	(353.6549,171.4550,1025.7964,180.1621)
)

enum sCookData
(
	cID,
	
	cObjectID,
	
	bool:cIsOccupied,
	cStatus,

	cDrug,
	cIngredient(MAX_INGREDIENTS),
	cIngredients,
	
	cTime
)
CookData(MAX_COOK)(sCookData)

enum sIngredientsData
(
	ingValue,
	ingName(32),
	ingPoints
)
IngredientsData()(sIngredientsData) =
(
	(0, _, 0),
	(1, wodorotlenek potasu, 6), 
	(2, winian ergotaminy, 2),
	(3, kwas siarkowy, 1),
	(4, 15 proc. amoniak, 2),
	(5, 1 proc. r-r amoniaku, 4),
	(6, dietyloamina, 2),
	(7, chloroform, 4),
	(8, trichlorek fosforylu, 1),
	(9, woda amoniakalna, 2),
	(10, siarczan magnezu, 5),
	(11, metanol, 4),
	(12, suchy kwas d-winowy, 4),
	(13, eter dietylowy, 1),
	(14, paski litu, 3),
	(15, azotan amonu, 3),
	(16, wodorotlenek sodu, 2),
	(17, eter dietylowy, 1),
	(18, ksylen, 4),
	(19, pseudoefedryna, 3),
	(20, kwas solny, 5),
	(21, alkohol izopropylowy, 3),
	(22, woda destylowana, 4),
	(23, proszek do pieczenia, 4),
	(24, proszek kokainowy, 4),			// ITEM_DRUG DRUG_COCAINE
	(25, fenyloaceton, 4),
	(26, hydroksyamina, 3),
	(27, wodor, 1),
	(28, nikiel, 4),
	(29, safrol, 3),
	(30, dimetyloformamid, 1),
	(31, benzochinon, 1),
	(32, chlorek palladu, 2),
	(33, chlorek metylenu, 2),
	(34, chlorek rteci, 6),
	(35, alkohol izopropylowy, 3),
	(36, folia aluminiowa, 1),
	(37, chlorek amonowy, 1),
	(38, paraformaldehyd, 1),
	(39, olej z orzeszków ziemnych, 6),
	(40, aceton, 1),
	(41, maka, 2),
	(42, maslo, 6),
	(43, jajka, 5),
	(44, cukier, 3),
	(45, cynamon, 1),
	(46, jablka, 2)
)

enum sRecipesData
(
	rName(32),
	rRecipe(64),
	Float:rMaxPoints,
	rMaxGrams,
	rTime,
	rItemType,
	rDrugValue,
)
// przy dodawaniu nowej trzeba te¿ dodaæ w cooking.inc -) CMD:gotuj
RecipesData()(sRecipesData) =
(
	(CRACK, 23 24, 8.0, 2, 120, ITEM_DRUG, DRUG_CRACK),
	(ECSTASY, 10 16 18 20 29 30 31 32 33 34 35 36 37 38 39 40, 43.0, 43, 2400, ITEM_DRUG, DRUG_MDMA),
	(LSD, 1 2 3 4 5 6 7 8 9 10 11 12 13 22, 42.0, 42, 2400, ITEM_DRUG, DRUG_LSD),
	(METAMFETAMINA, 14 15 16 17 18 19 20 21 22, 28.0, 28, 1800, ITEM_DRUG, DRUG_METAAMP),
	(AMFETAMINA, 25 26 27 28, 12.0, 10, 1200, ITEM_DRUG, DRUG_AMPHETAMINE),
	(SZARLOTKA, 41 42 43 44 45 46, 19.0, 1, 240, ITEM_FOOD, 10)
)

enum sRadioData
(
	gUID,
	gTag(32),
	bool:IsUsingRadio,
	AdvertTime
)
RadioData(MAX_RADIO)(sRadioData)

// Prezenty
/*enum pPars
(
	presentType,
	presentName(32),
)
PresentInfo()(pPars) = 
(
	(ITEM_PHONE, iPhone),
	(ITEM_CLOTH, Ubranie),
	(ITEM_LSPAD, LSPad),
	(ITEM_WATCH, Rolex),
	(ITEM_PLAYER, Odtwarzacz MP3),
	(ITEM_OXYGEN, Zestaw do nurkowania), 
	(ITEM_ROLL, Rolki)
)*/