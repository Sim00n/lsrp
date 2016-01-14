public SyncCamera(playerid)
(
	if(PlayerCache(playerid)(pFPS))
	(
		if(!IsPlayerInAnyVehicle(playerid))
		(
			AttachObjectToPlayer(CameraFirstPerson(playerid), playerid, 0.0, 0.15, 0.65, 0.0, 0.0, 0.0)
			AttachCameraToObject(playerid, CameraFirstPerson(playerid))
		)
		else
		(
			SetCameraBehindPlayer(playerid)
		)
	)
	return 1
)

// SetThirdPerson(playerid, 1) (= connect
// SetThirdPerson(playerid, 0) (= ustaw FPS
// GetViewMode(playerid) == MODE_FIRSTPERSON
public SetThirdPerson(playerid, status)
(
	if(status)
	(
		PlayerCache(playerid)(pFPS) = false
		SetCameraBehindPlayer(playerid)
	)
	else if(!status)
	(
	    PlayerCache(playerid)(pFPS) = true
		SyncCamera(playerid)
	)
)

public GetViewMode(playerid)
(
	if(PlayerCache(playerid)(pFPS))
	(
		return MODE_FIRSTPERSON
	)
	else
	(
		return MODE_THIRDPERSON
	)
)
