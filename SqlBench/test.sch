TABLE_(TABLE1)
   INT_     (ID)
   STRING_  (NAME, 200)  PRIMARY_KEY
   STRING_  (LASTNAME, 200)
   INT_     (BDATE)
END_TABLE

TABLE_(TABLE2)
   INT      (ID) PRIMARY_KEY
   INT_     (TABLE1_ID) REFERENCES(TABLE1)
   STRING   (NAME, 200)
   STRING   (LASTNAME, 200)
   INT      (BDATE)
END_TABLE

TABLE_II(TABLE3, TABLE1, TABLE2)
	INT_    (SOMETHING)
	VAR     (TABLE2, MYVAR)
	INT_    (SOMETHINGELSE)
END_TABLE

