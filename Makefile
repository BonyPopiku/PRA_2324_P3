testTableEntry:	testTableEntry.cpp	TableEntry.h
	mkdir	-p	bin	
	g++	-o	testTableEntry	testTableEntry.cpp

clean:
	rm	-rf	*.o	*.gch	bin
	
bin/testHashTable:	testHashTable.cpp	HashTable.h	Dict.h	TableEntry.h
	mkdir	-p	bin
	g++	-o	testHashTable	testHashTable.cpp	HashTable.h	Dict.h	TableEntry.h

