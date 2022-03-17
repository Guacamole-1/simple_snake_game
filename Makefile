all: compile link open
build: compile_final link
link_final:
compile:
	g++ -I src/include -c main.cpp 
link:
	g++ main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system 
link_final:
	g++ main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -mwindows
open:
	./main.exe