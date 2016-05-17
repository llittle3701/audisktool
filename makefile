CFLAGS = -c
CC = g++
OBJ = Tool.o CommandLine.o Report.o Config.o main.o

main : ${OBJ}
	${CC} ${OBJ} -o main

main.o : main.cpp
	${CC} ${CFLAGS} main.cpp

Tool.o : Tool.cpp Tool.h 
	${CC} ${CFLAGS} Tool.cpp

CommandLine.o : CommandLine.cpp CommandLine.h
	${CC} ${CFLAGS} CommandLine.cpp

Report.o : Report.cpp Report.h
	${CC} ${CFLAGS} Report.cpp

Config.o : Config.cpp Config.h
	${CC} ${CFLAGS} Config.cpp

clean:
	rm *.o main
