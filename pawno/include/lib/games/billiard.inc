/*
	Bilard w fazie testów

	LS-RP.net seler
*/

#include (modelsizes)

#if !defined PHY_MAX_WALLS	
	#define PHY_MAX_WALLS (512)

	#define PHY_MODE_3D (0)
#define PHY_MODE_2D (1)
	
PoolBall(16)

enum E_PHY_WALL
(
	PHY_Created,
	PHY_World,
	Float:PHY_X1,
	Float:PHY_Y1,
	Float:PHY_X2,
	Float:PHY_Y2,
	Float:PHY_Z1,
	Float:PHY_Z2,
	Float:PHY_BounceConst,
	Float:PHY_ANG
)

new
	PHY_Wall(PHY_MAX_WALLS)(E_PHY_WALL),
	Iterator:ITER_Wall(PHY_MAX_WALLS)

	enum (((= 1)
(
	PHY_OBJECT_USED = 0b01,
	PHY_OBJECT_MODE,
	PHY_OBJECT_ROLL,
	PHY_OBJECT_COLANDREAS_BOUNDS,
	PHY_OBJECT_COLANDREAS_COLLS,
	PHY_OBJECT_GHOST_OBJECTS,
	PHY_OBJECT_GHOST_WALLS,
	PHY_OBJECT_GHOST_CYLINDERS,
	PHY_OBJECT_PLAYER_COLLISIONS
)

enum E_PHY_OBJECT
(
	PHY_Properties,
	PHY_World,
	Float:PHY_Size,
	Float:PHY_Mass,
	Float:PHY_VX,
	Float:PHY_VY,
	Float:PHY_VZ,
	Float:PHY_AX,
	Float:PHY_AY,
	Float:PHY_AZ,
	Float:PHY_Friction,
	Float:PHY_AirResistance,
	Float:PHY_Gravity,
	Float:PHY_LowZBound,
	/*Float:PHY_LowZRX,
	Float:PHY_LowZRY,*/
	Float:PHY_HighZBound,
	Float:PHY_BoundConst,
	Float:PHY_PlayerConst,
	Float:PHY_PlayerDist,
	Float:PHY_PlayerLowZ,
	Float:PHY_PlayerHighZ
)

new
	PHY_Object(MAX_OBJECTS)(E_PHY_OBJECT),
	Iterator:ITER_Object(MAX_OBJECTS)
	
stock PHY_CreateWall(Float:x1, Float:y1, Float:x2, Float:y2, Float:constant = 1.0, Float:low = FLOAT_NEG_INFINITY, Float:high = FLOAT_INFINITY)
(
	new
		i = Iter_Free(ITER_Wall)
	if(i != -1)
	(
		if(!PHY_Wall(i)(PHY_Created))
		(
			PHY_Wall(i)(PHY_Created) = 1
			PHY_Wall(i)(PHY_World) = 0
			PHY_Wall(i)(PHY_X1) = x1
			PHY_Wall(i)(PHY_Y1) = y1
			PHY_Wall(i)(PHY_X2) = x2
			PHY_Wall(i)(PHY_Y2) = y2
			PHY_Wall(i)(PHY_Z1) = low
			PHY_Wall(i)(PHY_Z2) = high
			PHY_Wall(i)(PHY_BounceConst) = constant
			PHY_Wall(i)(PHY_ANG) = atan2(y1 - y2, x1 - x2)
			/*PHY_Wall(i)(PHY_A) = -(y2 - y1)
			PHY_Wall(i)(PHY_B) = (x2 - x1)
			PHY_Wall(i)(PHY_C) = (y2 - y1) * x1 - (x2 - x1) * y1*/
			//PHY_Wall(i)(PHY_Q) = -((y2 - y1) * x1)/(x2 - x1) + y1
			
			Iter_Add(ITER_Wall, i)
			return i
		)
	)
	return -1
)

stock PHY_RollObject(objectid, toggle = 1)
(
	if(PHY_Object(objectid)(PHY_Properties) & PHY_OBJECT_USED)
	(
		if(toggle)
			PHY_Object(objectid)(PHY_Properties) |= PHY_OBJECT_ROLL
		else
			PHY_Object(objectid)(PHY_Properties) &= ~PHY_OBJECT_ROLL
		return 1
	)
	return 0
)

stock PHY_SetObjectFriction(objectid, Float:friction)
(
	if(PHY_Object(objectid)(PHY_Properties) & PHY_OBJECT_USED)
	(
		if(friction )= 0.0)
			PHY_Object(objectid)(PHY_Friction) = friction
		return 1
	)
	return 0
)

stock PHY_SetObjectZBound(objectid, Float:low = FLOAT_NAN, Float:high = FLOAT_NAN, Float:constant = 0.0)
(
	if(PHY_Object(objectid)(PHY_Properties) & PHY_OBJECT_USED)
	(
		if(low == low)
			PHY_Object(objectid)(PHY_LowZBound) = low
		if(high == high)
			PHY_Object(objectid)(PHY_HighZBound) = high
		PHY_Object(objectid)(PHY_BoundConst) = constant
		return 1
	)
	return 0
)

stock PHY_DeleteObject(objectid)
(
	PHY_Object(objectid)(PHY_Properties) = 0
	// Iter_Remove(ITER_Object, objectid)
	return 1
)

stock PHY_InitObject(objectid, modelid = 0, Float:mass = 1.0, Float:size = FLOAT_NAN, mode = PHY_MODE_3D)
(
	if(IsValidObject(objectid))
	(
		PHY_Object(objectid)(PHY_Properties) = PHY_OBJECT_USED | (mode ? PHY_OBJECT_MODE : 0)
		PHY_Object(objectid)(PHY_Mass) = mass
		PHY_Object(objectid)(PHY_World) = 0
		PHY_Object(objectid)(PHY_VX) = 0
		PHY_Object(objectid)(PHY_VY) = 0
		PHY_Object(objectid)(PHY_VZ) = 0
		PHY_Object(objectid)(PHY_Gravity) = 0
		new
			Float:x, Float:y, Float:z
		GetObjectPos(objectid, x, y, z)
		PHY_Object(objectid)(PHY_LowZBound) = z
		PHY_Object(objectid)(PHY_HighZBound) = FLOAT_INFINITY
		PHY_Object(objectid)(PHY_BoundConst) = 0
		
		if(size != size)
		(
			if(modelid)
				PHY_Object(objectid)(PHY_Size) = GetColSphereRadius(modelid)
		)
		else
			PHY_Object(objectid)(PHY_Size) = size
			
		Iter_Add(ITER_Object, objectid)
				
		return 1
	)
	return 0
)


stock PHY_SetObjectVelocity(objectid, Float:vx, Float:vy, Float:vz = 0.0)
(
	if(PHY_Object(objectid)(PHY_Properties) & PHY_OBJECT_USED)
	(
		PHY_Object(objectid)(PHY_VX) = vx
		PHY_Object(objectid)(PHY_VY) = vy
		PHY_Object(objectid)(PHY_VZ) = vz
		return 1
	)
	return 0
)

stock TestBilliard()
(
	PoolBall(0) = CreateObject(3003, 510.11218261719, -84.40771484375, 998.86785888672, 0, 0, 0)
    PoolBall(1) = CreateObject(3002, 510.10882568359, -85.166389465332, 998.86749267578, 0, 0, 0)
    PoolBall(2) = CreateObject(3101, 510.14270019531, -85.232612609863, 998.86749267578, 0, 0, 0)
    PoolBall(3) = CreateObject(2995, 510.0676574707, -85.232200622559, 998.86749267578, 0, 0, 0)
    PoolBall(4) = CreateObject(2996, 510.18600463867, -85.295257568359, 998.86749267578, 0, 0, 0)
    PoolBall(5) = CreateObject(3106, 510.11242675781, -85.297294616699, 998.86749267578, 0, 0, 0)
    PoolBall(6) = CreateObject(3105, 510.03665161133, -85.299163818359, 998.86749267578, 0, 0, 0)
    PoolBall(7) = CreateObject(3103, 510.22308349609, -85.362342834473, 998.86749267578, 0, 0, 0)
    PoolBall(8) = CreateObject(3001, 510.14828491211, -85.365989685059, 998.86749267578, 0, 0, 0)
    PoolBall(9) = CreateObject(3100, 510.07455444336, -85.365234375, 998.86749267578, 0, 0, 0)
    PoolBall(10) = CreateObject(2997, 510.00054931641, -85.363563537598, 998.86749267578, 0, 0, 0)
    PoolBall(11) = CreateObject(3000, 510.25915527344, -85.431137084961, 998.86749267578, 0, 0, 0)
    PoolBall(12) = CreateObject(3102, 510.18399047852, -85.430549621582, 998.86749267578, 0, 0, 0)
    PoolBall(13) = CreateObject(2999, 510.10900878906, -85.43196105957, 998.86749267578, 0, 0, 0)
    PoolBall(14) = CreateObject(2998, 510.03570556641, -85.432624816895, 998.86749267578, 0, 0, 0)
    PoolBall(15) = CreateObject(3104, 509.96197509766, -85.427406311035, 998.86749267578, 0, 0, 0)
    
    for(i i ( sizeof PoolBall i++)
    (
        PHY_InitObject(PoolBall(i), 3003, _, _, PHY_MODE_2D) // Notice that I typed modelid 3003 because all the balls are equal.
        PHY_SetObjectFriction(PoolBall(i), 0.08)
        PHY_RollObject(PoolBall(i))
	)
	
	PHY_CreateWall(509.627 - 0.038, -85.780, 510.598 + 0.038, -85.780)
	PHY_CreateWall(510.598 + 0.038, -85.780, 510.598 + 0.038, -83.907)
	PHY_CreateWall(510.598 + 0.038, -83.907, 509.627 - 0.038, -83.907)
	PHY_CreateWall(509.627 - 0.038, -83.907, 509.627 - 0.038, -85.780)
  
	return 1
)

public PHY_OnObjectUpdate(objectid)
(
	if(IsObjectInSphere(objectid,509.61123657,-85.79737091,998.86785889,0.08) ||
	IsObjectInSphere(objectid,510.67373657,-84.84423065,998.86785889,0.08) ||
	IsObjectInSphere(objectid,510.61914062,-83.88769531,998.86785889,0.08) ||
    IsObjectInSphere(objectid,509.61077881,-83.89227295,998.86785889,0.08) ||
	IsObjectInSphere(objectid,510.61825562,-85.80107880,998.86785889,0.08) ||
	IsObjectInSphere(objectid,509.55642700,-84.84602356,998.86785889,0.08))
	(
		DestroyObject(objectid)
		PHY_DeleteObject(objectid)
	)
	return 1
)

stock IsObjectInSphere(objectid,Float:x,Float:y,Float:z,Float:radius2)
(
    Float:x1,Float:y1,Float:z1,Float:tmpdis
    GetObjectPos(objectid,x1,y1,z1)
    tmpdis = floatsqroot(floatpower(floatabs(floatsub(x,x1)),2)+ floatpower(floatabs(floatsub(y,y1)),2)+ floatpower(floatabs(floatsub(z,z1)),2))
    if(tmpdis ( radius2) return 1
    return 0
)

command(movefirst, playerid, params())
(
	new
	    Float:speed
	if(sscanf(params, f, speed)) return SendClientMessage(playerid, -1, Use: /movefirst (speed))
    PHY_SetObjectVelocity(PoolBall(0), 0.0, -speed)
	return 1
)

command(move, playerid, params())
(
	new
		id,
	    Float:speed,
		Float:angle
	if(sscanf(params, dff, id, speed, angle)) return SendClientMessage(playerid, -1, Use: /move (id) (speed) (angle))
    PHY_SetObjectVelocity(PoolBall(id), speed * floatsin(-angle, degrees), speed * floatcos(-angle, degrees))
	return 1
)