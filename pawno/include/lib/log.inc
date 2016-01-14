public AddPlayerLoginLog(playerid, bool: success)
(
	ip(16)
	GetPlayerIp(playerid, ip, sizeof(ip))
	
	mysql_query_format(INSERT INTO hrp_loginlogs (loginlog_ownergid, loginlog_charname, loginlog_ip, loginlog_success, loginlog_date, loginlog_charuid) VALUES (%d, %s, %s, %d, NOW(), %d), PlayerCache(playerid)(pGID), PlayerRealName(playerid), ip, success, PlayerCache(playerid)(pUID))
	return 1
)

stock hrp_DebugLog(logString(), va_args())
(
	entry(256), hour, minute, second
	gettime(hour, minute, second)
	
	va_format(entry, sizeof(entry), logString, va_start(1))
	format(entry, sizeof(entry), (%02d:%02d:%02d) %s\n, hour, minute, second, entry)
	
	year, month, day, file_name(64)
	getdate(year, month, day)
	
	format(file_name, sizeof(file_name), logs/debug_log_(%d-%d-%d).txt, day, month, year)
	File:hFile = fopen(file_name, io_append)
	
	fwrite(File:hFile, entry)
	fclose(File:hFile)
	return 1
)

stock hrp_DialogLog(logString(), va_args())
(
	entry(256), hour, minute, second
	gettime(hour, minute, second)
	
	va_format(entry, sizeof(entry), logString, va_start(1))
	format(entry, sizeof(entry), (%02d:%02d:%02d) %s\n, hour, minute, second, entry)
	
	year, month, day, file_name(64)
	getdate(year, month, day)
	
	format(file_name, sizeof(file_name), logs/dialog_log_(%d-%d-%d).txt, day, month, year)
	File:hFile = fopen(file_name, io_append)
	
	fwrite(File:hFile, entry)
	fclose(File:hFile)
	return 1
)

stock hrp_MoneyActionLog(logString(), va_args())
(
	entry(256), hour, minute, second
	gettime(hour, minute, second)

	va_format(entry, sizeof(entry), logString, va_start(1))
	format(entry, sizeof(entry), (%02d:%02d:%02d) %s\n, hour, minute, second, entry)

	year, month, day, file_name(64)
	getdate(year, month, day)

	format(file_name, sizeof(file_name), logs/money_log_(%d-%d-%d).txt, day, month, year)
	File:hFile = fopen(file_name, io_append)

	fwrite(File:hFile, entry)
	fclose(File:hFile)
	return 1
)

stock hrp_ItemActionLog(logString(), va_args())
(
	entry(256), hour, minute, second
	gettime(hour, minute, second)

	va_format(entry, sizeof(entry), logString, va_start(1))
	format(entry, sizeof(entry), (%02d:%02d:%02d) %s\n, hour, minute, second, entry)

	year, month, day, file_name(64)
	getdate(year, month, day)

	format(file_name, sizeof(file_name), logs/item_log_(%d-%d-%d).txt, day, month, year)
	File:hFile = fopen(file_name, io_append)

	fwrite(File:hFile, entry)
	fclose(File:hFile)
	return 1
)

stock hrp_VehicleActionLog(logString(), va_args())
(
	entry(256), hour, minute, second
	gettime(hour, minute, second)

	va_format(entry, sizeof(entry), logString, va_start(1))
	format(entry, sizeof(entry), (%02d:%02d:%02d) %s\n, hour, minute, second, entry)

	year, month, day, file_name(64)
	getdate(year, month, day)

	format(file_name, sizeof(file_name), logs/vehicle_log_(%d-%d-%d).txt, day, month, year)
	File:hFile = fopen(file_name, io_append)

	fwrite(File:hFile, entry)
	fclose(File:hFile)
	return 1
)

stock hrp_AdminActionLog(logString(), va_args())
(
	entry(256), hour, minute, second
	gettime(hour, minute, second)

	va_format(entry, sizeof(entry), logString, va_start(1))
	format(entry, sizeof(entry), (%02d:%02d:%02d) %s\n, hour, minute, second, entry)

	year, month, day, file_name(64)
	getdate(year, month, day)

	format(file_name, sizeof(file_name), logs/admin_log_(%d-%d-%d).txt, day, month, year)
	File:hFile = fopen(file_name, io_append)

	fwrite(File:hFile, entry)
	fclose(File:hFile)
	return 1
)

stock hrp_OfferActionLog(logString(), va_args())
(
	entry(256), hour, minute, second
	gettime(hour, minute, second)

	va_format(entry, sizeof(entry), logString, va_start(1))
	format(entry, sizeof(entry), (%02d:%02d:%02d) %s\n, hour, minute, second, entry)

	year, month, day, file_name(64)
	getdate(year, month, day)

	format(file_name, sizeof(file_name), logs/offer_log_(%d-%d-%d).txt, day, month, year)
	File:hFile = fopen(file_name, io_append)

	fwrite(File:hFile, entry)
	fclose(File:hFile)
	return 1
)

stock hrp_GroupActionLog(logString(), va_args())
(
	entry(256), hour, minute, second
	gettime(hour, minute, second)

	va_format(entry, sizeof(entry), logString, va_start(1))
	format(entry, sizeof(entry), (%02d:%02d:%02d) %s\n, hour, minute, second, entry)

	year, month, day, file_name(64)
	getdate(year, month, day)

	format(file_name, sizeof(file_name), logs/group_log_(%d-%d-%d).txt, day, month, year)
	File:hFile = fopen(file_name, io_append)

	fwrite(File:hFile, entry)
	fclose(File:hFile)
	return 1
)

stock hrp_SerialLog(logString(), va_args())
(
	entry(256), hour, minute, second
	gettime(hour, minute, second)

	va_format(entry, sizeof(entry), logString, va_start(1))
	format(entry, sizeof(entry), (%02d:%02d:%02d) %s\n, hour, minute, second, entry)

	year, month, day, file_name(64)
	getdate(year, month, day)

	format(file_name, sizeof(file_name), logs/serial_log_(%d-%d-%d).txt, day, month, year)
	File:hFile = fopen(file_name, io_append)

	fwrite(File:hFile, entry)
	fclose(File:hFile)
	return 1
)