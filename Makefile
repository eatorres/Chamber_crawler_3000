CXX = g++
CXXFLAGS = -g
EXEC = cc3k 
OBJECTS = testing.o map.o character.o cell.o treasure.o potion.o  human.o orc.o elf.o dwarf.o dev.o vampire.o werewolf.o phoenix.o troll.o goblin.o merchant.o dragon.o asciiArt.o normal.o woundatk.o boostatk.o restore.o wounddef.o boostdef.o small.o poison.o dragonHoard.o merchantHoard.o

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
