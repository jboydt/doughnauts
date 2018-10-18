FLAGS = -std=c++11 -Wall -Wextra -Werror
CC = g++

doughnauts.exe: doughnauts.cpp fight_history.o
	$(CC) $(FLAGS) doughnauts.cpp fight_history.o -o doughnauts.exe

fight_history.o: fight_history.h fight_history.cpp
	$(CC) $(FLAGS) -c fight_history.cpp -o fight_history.o

clean:
	del *.o

cleanall: clean
	del *.exe
