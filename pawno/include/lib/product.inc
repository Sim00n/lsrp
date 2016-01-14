public AddDoorProduct(ProductName(), ProductType, ProductValue1, ProductValue2, ProductPrice, ProductNumber, ProductDoorUID)
(
	product_id
	
	// Sumuj produkt z innymi
	foreach(Products, i)
	(
		if(ProductInfo(i)(pUID))
		(
			if(ProductInfo(i)(pDoorUID) == ProductDoorUID)
			(
				if(ProductInfo(i)(pType) == ProductType && ProductInfo(i)(pPrice) == ProductPrice)
				(
					if(!strcmp(ProductInfo(i)(pName), ProductName, true))
					(
						ProductInfo(i)(pNumber) += ProductNumber

						SaveProduct(i, SAVE_PRODUCT_VALUES)
						return 1
					)
				)
			)
		)
	)
	
	mysql_query_format(INSERT INTO hrp_products (product_name, product_type, product_value1, product_value2, product_price, product_number, product_dooruid) VALUES (%s, %d, %d, %d, %d, %d, %d), ProductName, ProductType, ProductValue1, ProductValue2, ProductPrice, ProductNumber, ProductDoorUID)

	product_id = Itter_Free(Products)
	
	ProductInfo(product_id)(pUID) = mysql_insert_id()
	strmid(ProductInfo(product_id)(pName), ProductName, 0, strlen(ProductName), 32)
	
	ProductInfo(product_id)(pType) = ProductType
	
	ProductInfo(product_id)(pValue1) = ProductValue1
	ProductInfo(product_id)(pValue2) = ProductValue2
	
	ProductInfo(product_id)(pPrice) = ProductPrice
	
	ProductInfo(product_id)(pNumber) = ProductNumber
	ProductInfo(product_id)(pDoorUID) = ProductDoorUID
	
	Itter_Add(Products, product_id)
	return 1
)

public LoadAllProducts()
(
	data(128), product_id
	mysql_query(SELECT * FROM hrp_products)
	
	print((load) Rozpoczynam proces wczytywania wszystkich produktów...)

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(

		sscanf(data, p(|)ds(32)dddddd,
		ProductInfo(product_id)(pUID),
		ProductInfo(product_id)(pName),
		ProductInfo(product_id)(pType),
		ProductInfo(product_id)(pValue1),
		ProductInfo(product_id)(pValue2),
		ProductInfo(product_id)(pPrice),
		ProductInfo(product_id)(pNumber),
		ProductInfo(product_id)(pDoorUID))
		
		Itter_Add(Products, product_id)
		
		product_id ++
	)
	mysql_free_result()

	printf((load) Wczytano %d produkty/ów., product_id)
	return 1
)

public SaveProduct(product_id, what)
(
	query(256), main_query(256)
	format(main_query, sizeof(main_query), UPDATE hrp_products SET)
	if(what & SAVE_PRODUCT_THINGS)
	(
		// Pozosta³e (nazwa, itemtype, wartoœæ 1, wartoœæ 2, UID drzwi)
		format(query, sizeof(query),  product_name = %s, product_itemtype = %d, product_value1 = %d, product_value2 = %d, product_dooruid = %d,
		ProductInfo(product_id)(pName),
		ProductInfo(product_id)(pType),
		ProductInfo(product_id)(pValue1),
		ProductInfo(product_id)(pValue2),
		ProductInfo(product_id)(pDoorUID))

		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	if(what & SAVE_PRODUCT_VALUES)
	(
		// Wartoœci (koszt produktu, iloœæ w magazynie)
		format(query, sizeof(query),  product_price = %d, product_number = %d,
		ProductInfo(product_id)(pPrice),
		ProductInfo(product_id)(pNumber))
		
		if(strlen(main_query) ) 32)
		(
			strcat(main_query, ,, sizeof(main_query))
		)
  		strcat(main_query, query, sizeof(main_query))
	)
	format(query, sizeof(query),  WHERE product_uid = %d LIMIT 1, ProductInfo(product_id)(pUID))
	strcat(main_query, query, sizeof(main_query))
	
	mysql_query(main_query)
	return 1
)

public DeleteProduct(product_id)
(
	mysql_query_format(DELETE FROM hrp_products WHERE product_uid = %d LIMIT 1, ProductInfo(product_id)(pUID))
	
	ProductInfo(product_id)(pUID) = 0
	ProductInfo(product_id)(pType) = 0
	
	ProductInfo(product_id)(pValue1) = 0
	ProductInfo(product_id)(pValue2) = 0
	
	ProductInfo(product_id)(pPrice) = 0
	ProductInfo(product_id)(pNumber) = 0
	
	ProductInfo(product_id)(pDoorUID) = 0
	
	Itter_Remove(Products, product_id)
	return 1
)

public CreatePackage(PackageDoorUID, PackageItemName(32), PackageItemType, PackageItemValue1, PackageItemValue2, PackageItemNumber, PackageItemPrice, PackageSecured)
(
	package_id, package_uid
	mysql_query_format(INSERT INTO hrp_packages (package_dooruid, package_itemname, package_itemtype, package_itemvalue1, package_itemvalue2, package_itemnumber, package_itemprice, package_secured) VALUES (%d, %s, %d, %d, %d, %d, %d, %d), PackageDoorUID, PackageItemName, PackageItemType, PackageItemValue1, PackageItemValue2, PackageItemNumber, PackageItemPrice, PackageSecured)
	
	package_uid = mysql_insert_id()
	package_id = Itter_Free(Packages)
	
	PackageInfo(package_id)(pUID) = package_uid
	PackageInfo(package_id)(pDoorUID) = PackageDoorUID

	strmid(PackageInfo(package_id)(pItemName), PackageItemName, 0, strlen(PackageItemName), 32)
	PackageInfo(package_id)(pItemType) = PackageItemType

	PackageInfo(package_id)(pItemValue1) = PackageItemValue1
	PackageInfo(package_id)(pItemValue2) = PackageItemValue2

	PackageInfo(package_id)(pItemNumber) = PackageItemNumber
	PackageInfo(package_id)(pItemPrice) = PackageItemPrice
	
	PackageInfo(package_id)(pSecured) = PackageSecured
	PackageInfo(package_id)(pTransportTime) = 5
	
	Itter_Add(Packages, package_id)
	return package_id
)

public CreateLimitedPackage(PackageDoorUID, playerid, playeruid, PackageItemName(32), PackageItemType, PackageItemValue1, PackageItemValue2, PackageItemNumber, PackageItemPrice, PackageSecured)
(
	limitedpackage_id, package_uid
	Float:DeliveryPoint()(4) =
	(
		(1.0, -392.4167,2221.2620,42.4297),
		(2.0, 267.7657,2887.7651,10.8491),
		(3.0, -2217.9829,641.0096,49.4491),
		(4.0, -579.7222,-177.1168,78.8631),
		(5.0, 2798.0588,-2436.3267,13.6312)
	)
	rand = random(sizeof(DeliveryPoint))
	Checkpoint(playerid) = 1
	PackagePoint = floatround(DeliveryPoint(rand)(0))	
	SetPlayerCheckpoint(playerid, DeliveryPoint(rand)(1), DeliveryPoint(rand)(2),DeliveryPoint(rand)(3), 5.0)
	mysql_query_format(INSERT INTO hrp_limitedpackages (package_playeruid, package_dooruid, package_itemname, package_itemtype, package_itemvalue1, package_itemvalue2, package_itemnumber, package_itemprice, package_secured, package_point) VALUES (%d, %d, %s, %d, %d, %d, %d, %d, %d, %d), playeruid, PackageDoorUID, PackageItemName, PackageItemType, PackageItemValue1, PackageItemValue2, PackageItemNumber, PackageItemPrice, PackageSecured, PackagePoint)
	package_uid = mysql_insert_id()
	limitedpackage_id = Itter_Free(LimitedPackages)
	
	LimitedPackageInfo(limitedpackage_id)(pUID) = package_uid
	LimitedPackageInfo(limitedpackage_id)(pDoorUID) = PackageDoorUID
	LimitedPackageInfo(limitedpackage_id)(pPlayerUID) = playeruid

	strmid(LimitedPackageInfo(limitedpackage_id)(pItemName), PackageItemName, 0, strlen(PackageItemName), 32)
	LimitedPackageInfo(limitedpackage_id)(pItemType) = PackageItemType

	LimitedPackageInfo(limitedpackage_id)(pItemValue1) = PackageItemValue1
	LimitedPackageInfo(limitedpackage_id)(pItemValue2) = PackageItemValue2

	LimitedPackageInfo(limitedpackage_id)(pItemNumber) = PackageItemNumber
	LimitedPackageInfo(limitedpackage_id)(pItemPrice) = PackageItemPrice
	
	LimitedPackageInfo(limitedpackage_id)(pSecured) = PackageSecured
	LimitedPackageInfo(limitedpackage_id)(pPoint) = floatround(DeliveryPoint(rand)(0)) // seler POZYCJA
	
	Itter_Add(LimitedPackages, limitedpackage_id)
	return limitedpackage_id
)

public LoadLimitedPackages()
(
	data(128), limitedpackage_id
	mysql_query(SELECT * FROM hrp_limitedpackages)
	
	print((load) Rozpoczynam proces wczytywania olimitowanych paczek z bazy...)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		limitedpackage_id ++
	
		sscanf(data, p(|)ddds(32)ddddddd,
		LimitedPackageInfo(limitedpackage_id)(pUID),
		LimitedPackageInfo(limitedpackage_id)(pDoorUID),
		LimitedPackageInfo(limitedpackage_id)(pPlayerUID),
		
		LimitedPackageInfo(limitedpackage_id)(pItemName),
		LimitedPackageInfo(limitedpackage_id)(pItemType),
		
		LimitedPackageInfo(limitedpackage_id)(pItemValue1),
		LimitedPackageInfo(limitedpackage_id)(pItemValue2),
		
		LimitedPackageInfo(limitedpackage_id)(pItemNumber),
		LimitedPackageInfo(limitedpackage_id)(pItemPrice),
		
		LimitedPackageInfo(limitedpackage_id)(pSecured),
		LimitedPackageInfo(limitedpackage_id)(pPoint))
		
		Itter_Add(LimitedPackages, limitedpackage_id)
	)
	mysql_free_result()

	printf((load) Wczytano %d olimitowanych/e paczki/e., limitedpackage_id)
	return 1

)

public DeleteLimitedPackage(limitedpackage_id)
(
	mysql_query_format(DELETE FROM hrp_limitedpackages WHERE package_uid = %d LIMIT 1, LimitedPackageInfo(limitedpackage_id)(pUID))
	
	LimitedPackageInfo(limitedpackage_id)(pUID) = 0
	LimitedPackageInfo(limitedpackage_id)(pDoorUID) = 0
	LimitedPackageInfo(limitedpackage_id)(pPlayerUID) = 0

	LimitedPackageInfo(limitedpackage_id)(pItemType) = 0

	LimitedPackageInfo(limitedpackage_id)(pItemValue1) = 0
	LimitedPackageInfo(limitedpackage_id)(pItemValue2) = 0

	LimitedPackageInfo(limitedpackage_id)(pItemNumber) = 0
	LimitedPackageInfo(limitedpackage_id)(pItemPrice) = 0

	LimitedPackageInfo(limitedpackage_id)(pPoint) = 0
	
	Itter_Remove(LimitedPackages, limitedpackage_id)
	return limitedpackage_id
)

public LoadPackages()
(
	data(64), package_id
	mysql_query(SELECT * FROM hrp_packages)
	
	print((load) Rozpoczynam proces wczytywania wszystkich paczek z bazy...)
	
	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		package_id ++
	
		sscanf(data, p(|)dds(32)dddddd,
		PackageInfo(package_id)(pUID),
		PackageInfo(package_id)(pDoorUID),
		
		PackageInfo(package_id)(pItemName),
		PackageInfo(package_id)(pItemType),
		
		PackageInfo(package_id)(pItemValue1),
		PackageInfo(package_id)(pItemValue2),
		
		PackageInfo(package_id)(pItemNumber),
		PackageInfo(package_id)(pItemPrice),
		
		PackageInfo(package_id)(pSecured))
		
		PackageInfo(package_id)(pTransportTime) = 5
		Itter_Add(Packages, package_id)
	)
	mysql_free_result()
	
	printf((load) Wczytano %d paczki/e., package_id)
	return 1
)

public DeletePackage(package_id)
(
	mysql_query_format(DELETE FROM hrp_packages WHERE package_uid = %d LIMIT 1, PackageInfo(package_id)(pUID))
	
	PackageInfo(package_id)(pUID) = 0
	PackageInfo(package_id)(pDoorUID) = 0

	PackageInfo(package_id)(pItemType) = 0

	PackageInfo(package_id)(pItemValue1) = 0
	PackageInfo(package_id)(pItemValue2) = 0

	PackageInfo(package_id)(pItemNumber) = 0
	PackageInfo(package_id)(pItemPrice) = 0
	
	Itter_Remove(Packages, package_id)
	return package_id
)

public ListPlayerDoorProducts(playerid, doorid)
(
	data(64), list_items(1024)
	mysql_query_format(SELECT product_uid, product_number, product_price, product_name FROM hrp_products WHERE product_dooruid = %d, DoorData(doorid)(dUID))
	new	product_uid, product_name(32), product_number, product_price

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ddds(32), product_uid, product_number, product_price, product_name)

		format(list_items, sizeof(list_items), %s\n%d\tx%d\t$%d\t%s, list_items, product_uid, product_number, product_price, product_name)
	)
	mysql_free_result()
	if(strlen(list_items) ) 0)
	(
		ShowPlayerDialog(playerid, D_OFFER_PRODUCT, DIALOG_STYLE_LIST, Produkty w magazynie, list_items, Oferuj, Anuluj)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych produktów w magazynie., OK, )
	)
	return 1
)

stock LoadProductsList(playerid)
(
	doorid = GetPlayerDoorID(playerid), data(64), list_items(1024)
	if(doorid == INVALID_DOOR_ID)
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znajdujesz siê w budynku., OK, )
		return 1
	)
	mysql_query_format(SELECT product_uid, product_number, product_price, product_name FROM hrp_products WHERE product_dooruid = %d, DoorData(doorid)(dUID))

	new	product_uid, product_name(32), product_number, product_price

	mysql_store_result()
	while(mysql_fetch_row(data, |))
	(
		sscanf(data, p(|)ddds(32), product_uid, product_number, product_price, product_name)
		format(list_items, sizeof(list_items), %s\n%d\tx%d\t$%d\t%s, list_items, product_uid, product_number, product_price, product_name)
	)
	mysql_free_result()
	if(strlen(list_items) ) 0)
	(
		ShowPlayerDialog(playerid, D_PRODUCT_SELECT, DIALOG_STYLE_LIST, Produkty w magazynie, list_items, Wybierz, Anuluj)
	)
	else
	(
		ShowPlayerDialog(playerid, D_INFO, DIALOG_STYLE_MSGBOX, Wyst¹pi³ b³¹d, Nie znaleziono ¿adnych produktów w magazynie., OK, )
	)
	return 1
)