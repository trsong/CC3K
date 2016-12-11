a5: cc3k.o Cell.o CharacterSystem.o InventorySystem.o Grid.o MapDisplay.o randomNum.o
	g++ cc3k.o Cell.o CharacterSystem.o InventorySystem.o Grid.o MapDisplay.o randomNum.o -o a5
	
cc3k.o: cc3k.cpp Grid.h
	g++ -g -Wall -c cc3k.cpp 

Cell.o: Cell.cpp Cell.h CharacterSystem.h InventorySystem.h randomNum.h MapDisplay.h
	g++ -g -Wall -c Cell.cpp
	
CharacterSystem.o: CharacterSystem.cpp CharacterSystem.h randomNum.h MapDisplay.h
	g++ -g -Wall -c CharacterSystem.cpp
	
Grid.o: Grid.cpp Grid.h Cell.h CharacterSystem.h InventorySystem.h randomNum.h MapDisplay.h
	g++ -g -Wall -c Grid.cpp
	
InventorySystem.o: InventorySystem.cpp InventorySystem.h CharacterSystem.h MapDisplay.h
	g++ -g -Wall -c InventorySystem.cpp
	
MapDisplay.o: MapDisplay.cpp MapDisplay.h
	g++ -g -Wall -c MapDisplay.cpp

randomNum.o: randomNum.cpp randomNum.h
	g++ -g -Wall -c randomNum.cpp

clean:
	rm -f *.o
