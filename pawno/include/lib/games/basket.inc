stock IsPlayerInRangeOfBasket(playerid)
(
	object = GetClosestObjectByModel(playerid,946, 5.0)
	if(object != INVALID_OBJECT_ID)
	(
		return true
	)
	else
	(
		return false
	)
)

stock PlayBasketEnd(playerid)
(
	GameTextForPlayer(playerid, ~n~~n~~n~~n~~n~~n~~n~~r~Anulowales gre!, 3000, 3)
	TextDrawHideForPlayer(playerid, Text:TextDrawMainInfo(playerid))
	PlayerCache(playerid)(pPlayBasket) = false
	SetCameraBehindPlayer(playerid)
			
	ball = PlayerCache(playerid)(pBasketBall)
	if(IsValidDynamicObject(ball))
	(
		DestroyDynamicObject(ball)
		PlayerCache(playerid)(pBasketBall) = INVALID_OBJECT_ID
		ClearAnimations(playerid, true)
	)
	
	if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_PHONE))
	(
		RemovePlayerAttachedObject(playerid,SLOT_PHONE)
	)
	
	return 1
)

//forward BasketBallThrow(playerid)
stock BasketBallThrow(playerid)
(
	ball = PlayerCache(playerid)(pBasketBall)
	basket = PlayerCache(playerid)(pBasketID)
	
	Float:Pos(3)
	GetDynamicObjectPos(ball,Pos(0),Pos(1),Pos(2))
	SetDynamicObjectPos(ball,Pos(0),Pos(1),Pos(2)+2.0)
	GetDynamicObjectPos(basket,Pos(0),Pos(1),Pos(2))
	
	MoveDynamicObject(ball, Pos(0),Pos(1),Pos(2)+1.0, 10.0 + random(4), float(random(180)),float(random(180)))
	
	return 1
)

forward ChangeAnimToBasketLoop(playerid)
public ChangeAnimToBasketLoop(playerid)
(
	ApplyAnimation(playerid,BSKTBALL,BBALL_idleloop,4.1,1,1,1,1,1)
	
	ball = PlayerCache(playerid)(pBasketBall)
	basket = PlayerCache(playerid)(pBasketID)
	
	
	Float:Pos(3)
	GetPlayerPos(playerid,Pos(0),Pos(1),Pos(2))
	SetDynamicObjectPos(ball,Pos(0),Pos(1),Pos(2) - 1.5)
	
	SetPlayerCameraPos(playerid,Pos(0),Pos(1),Pos(2)+1.0)
	GetDynamicObjectPos(basket,Pos(0),Pos(1),Pos(2))
	SetPlayerCameraLookAt(playerid, Pos(0),Pos(1),Pos(2)+2.0)
	
	//PlayerCache(playerid)(pBallTicks) = 1
	//PlayerCache(playerid)(pBallPhase) = BALL_START
	
	return 1
)

forward Basket_ChangeAnimToNormal(playerid)
public Basket_ChangeAnimToNormal(playerid)
(
	ClearAnimations(playerid, true)
	SetCameraBehindPlayer(playerid)
	
	ball = PlayerCache(playerid)(pBasketBall)
	basket = PlayerCache(playerid)(pBasketID)
	
	Float:Pos(3)
	GetDynamicObjectPos(basket,Pos(0),Pos(1),Pos(2))
	SetDynamicObjectPos(ball,Pos(0)+random(2),Pos(1)+random(2),Pos(2)-2.0)
	
	PlayerCache(playerid)(pBallTicks) = 1
	PlayerCache(playerid)(pBallPhase) = BALL_START
	return 1
)