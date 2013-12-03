TABLE_(DATES)
	INT_   (ID) PRIMARY_KEY
	DATE_  (DT)
END_TABLE

TABLE_(GROUPS)
	INT     (ID) PRIMARY_KEY
	STRING_ (NAME, 500)
END_TABLE

TABLE_(CATEGORIES)
	INT 	(ID) PRIMARY_KEY
	INT_    (GR_ID)
	STRING  (NAME, 500)
	DOUBLE_ (DEFVALUE)
	INT_    (PM)
	INT_    (INNEWMONTH)
END_TABLE

TABLE_(MONEY)
	INT  (ID) PRIMARY_KEY
	INT_ (DT_ID)
	INT_ (CAT_ID)
	INT  (PM)
	DOUBLE_ (VALUE)
	DATE (DT)
	STRING_ (DESC, 1024)
END_TABLE