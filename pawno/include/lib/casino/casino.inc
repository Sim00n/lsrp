#define GAME_BLACKJACK		0
#define GAME_POKER			1
#define GAME_SLOTS			2
#define GAME_DARTS			3

#include (lib\casino\blackjack)

forward CasinoLoop()

public CasinoLoop() (
	BJLoop()
)