all: main clean

main: main.cpp Buffer.o UI.o
	g++ -std=c++17 main.cpp Buffer.o UI.o -o filebrowser

Buffer.o: Buffer.cpp Buffer.h
	g++ -std=c++17 -c Buffer.cpp -o Buffer.o

UI.o: UI.cpp UI.h
	g++ -std=c++17 -c UI.cpp -o UI.o

clean:
	rm Buffer.o
	rm UI.o