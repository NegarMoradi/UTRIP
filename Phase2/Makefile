CC = g++
FLAGS = -std=c++11 
COMPILE_FLAGS = $(FLAGS) -c 
ALL_FILES= main.o Comment.o Filter.o Hotel.o Inputs.o Reserve.o Room.o Weight.o Score.o User.o UTRIP.o Exceptions.o

all: utrip.out

utrip.out: ${ALL_FILES}
	${CC} ${ALL_FILES} ${FLAGS} -o utrip.out

main.o: main.cpp UTRIP.hpp
	${CC} ${COMPILE_FLAGS} main.cpp 

UTRIP.o: UTRIP.cpp UTRIP.hpp Reserve.hpp Comment.hpp User.hpp Inputs.hpp Hotel.hpp Exceptions.hpp
	${CC} ${COMPILE_FLAGS} UTRIP.cpp

User.o: User.cpp User.hpp Exceptions.hpp Hotel.hpp Reserve.hpp Filter.hpp Weight.hpp
	${CC} ${COMPILE_FLAGS} User.cpp

Score.o: Score.cpp Score.hpp 
	${CC} ${COMPILE_FLAGS} Score.cpp

Room.o: Room.cpp Room.hpp
	${CC} ${COMPILE_FLAGS} Room.cpp

Reserve.o: Reserve.cpp Reserve.hpp Room.hpp Hotel.hpp
	${CC} ${COMPILE_FLAGS} Reserve.cpp

Inputs.o: Inputs.cpp Inputs.hpp Hotel.hpp
	${CC} ${COMPILE_FLAGS} Inputs.cpp

Exceptions.o: Exceptions.hpp Exceptions.cpp
	${CC} ${COMPILE_FLAGS} Exceptions.cpp
	
Hotel.o: Hotel.cpp Hotel.hpp Exceptions.hpp Room.hpp Comment.hpp Score.hpp Weight.hpp
	${CC} ${COMPILE_FLAGS} Hotel.cpp

Filter.o: Filter.cpp Filter.hpp Hotel.hpp Exceptions.hpp
	${CC} ${COMPILE_FLAGS} Filter.cpp

Comment.o: Comment.cpp Comment.hpp Hotel.hpp
	${CC} ${COMPILE_FLAGS} Comment.cpp

Weight.o: Weight.cpp Weight.hpp 
	${CC} ${COMPILE_FLAGS} Weight.cpp

.PHONY: clean
clean:
	rm -r *.o *.out