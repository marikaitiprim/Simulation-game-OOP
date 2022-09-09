ex :Heroes.o Items.o LivingBeings.o Monsters.o Objects.o Spells.o Blocks.o newmain.o
	g++ -std=c++11 Heroes.o Items.o LivingBeings.o Monsters.o Objects.o Spells.o Blocks.o  newmain.o -o ex

ex.exe :Heroes.o Items.o LivingBeings.o Monsters.o Objects.o Spells.o Blocks.o newmain.o
	g++ -std=c++11 Heroes.o Items.o LivingBeings.o Monsters.o Objects.o Spells.o Blocks.o  newmain.o -o ex.exe


Heroes.o :Heroes.cpp header.h
	g++ -std=c++11 -c Heroes.cpp

Items.o :Items.cpp header.h
	g++ -std=c++11 -c Items.cpp

LivingBeings.o :LivingBeings.cpp header.h
	g++ -std=c++11 -c LivingBeings.cpp

Monsters.o :Monsters.cpp header.h
	g++ -std=c++11 -c Monsters.cpp

Objects.o :Objects.cpp header.h
	g++ -std=c++11 -c Objects.cpp

Spells.o :Spells.cpp header.h
	g++ -std=c++11 -c Spells.cpp

Blocks.o :Blocks.cpp header.h
	g++ -std=c++11 -c Blocks.cpp

newmain.o :newmain.cpp header.h
	g++ -std=c++11 -c newmain.cpp

clean:
	rm ex ex.exe Blocks.o Heroes.o Items.o LivingBeings.o Monsters.o Objects.o Spells.o newmain.o 
