CC = g++
FLAGS = -std=c++11 
COMPILE_FLAGS = $(FLAGS) -c 
ALL_FILES= main.o Comment.o Filter.o Hotel.o Inputs.o Reserve.o Room.o Score.o User.o UTRIP.o Exceptions.o

all: utrip.out

utrip.out: ${ALL_FILES}
	${CC} ${ALL_FILES} ${FLAGS} -o utrip.out

main.o: main.cpp UTRIP.h
	${CC} ${COMPILE_FLAGS} main.cpp 

UTRIP.o: UTRIP.cpp UTRIP.h Reserve.h Comment.h User.h Inputs.h Hotel.h Exceptions.h
	${CC} ${COMPILE_FLAGS} UTRIP.cpp

User.o: User.cpp User.h Exceptions.h Hotel.h Reserve.h Filter.h
	${CC} ${COMPILE_FLAGS} User.cpp

Score.o: Score.cpp Score.h 
	${CC} ${COMPILE_FLAGS} Score.cpp

Room.o: Room.cpp Room.h
	${CC} ${COMPILE_FLAGS} Room.cpp

Reserve.o: Reserve.cpp Reserve.h Room.h Hotel.h
	${CC} ${COMPILE_FLAGS} Reserve.cpp

Inputs.o: Inputs.cpp Inputs.h Hotel.h
	${CC} ${COMPILE_FLAGS} Inputs.cpp

Exceptions.o: Exceptions.h Exceptions.cpp
	${CC} ${COMPILE_FLAGS} Exceptions.cpp
	
Hotel.o: Hotel.cpp Hotel.h Exceptions.h Room.h Comment.h Score.h 
	${CC} ${COMPILE_FLAGS} Hotel.cpp

Filter.o: Filter.cpp Filter.h Hotel.h Exceptions.h
	${CC} ${COMPILE_FLAGS} Filter.cpp

Comment.o: Comment.cpp Comment.h Hotel.h
	${CC} ${COMPILE_FLAGS} Comment.cpp

.PHONY: clean
clean:
	rm -r *.o *.out