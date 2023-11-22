all: Akinator

Akinator: main.o tree.o akinator.o Stack_Func.o
	g++ -g -o myprog.exe main.o tree.o akinator.o Stack_Func.o -o Akinator

main.o: main.cpp
	g++ -g -DDUMP -c main.cpp

tree.o: tree.cpp
	g++ -g -DDUMP -c tree.cpp

akinator.o: akinator.cpp
	g++ -g -DDUMP -c akinator.cpp

Stack_Func.o: Stack_Func.cpp
	g++ -g -DDUMP -c Stack_Func.cpp

clean:
	rm *.o akinator.exe