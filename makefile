pong.out: display.o move.o main.o
	gcc -o pong.out display.o move.o main.o -lSDL2

main.o: main.c display.h structs.h move.h
	gcc -c -o main.o main.c -lSDL2

display.o: display.c display.h structs.h
	gcc -c -o display.o display.c -lSDL2

move.o: move.c move.h structs.h
	gcc -c -o move.o move.c -lSDL2

clean:
	rm -f *.out *.o


