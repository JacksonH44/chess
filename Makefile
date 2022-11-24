CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS =  game/game.o piece/bishop.o piece/board.o piece/king.o piece/knight.o piece/pawn.o piece/piece.o piece/queen.o piece/rook.o player/cpu1.o player/cpu2.o player/cpu3.o player/cpu4.o player/humanPlayer.o player/player.o player/playerFactory.o view/graphicsView.o view/textView.o view/view.o pos.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
