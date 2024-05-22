main.exe: main.o overworld.o
	g++ overworld.o main.o -o main.exe

main.o: main.cpp
	g++ -c main.cpp
	
task-manager.o: overworld.cpp overworld.h
	g++ -c overworld.cpp
	
clean:
	rm -f *.exe *.o