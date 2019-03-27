CC=g++
CFLAGS=
LINK=-lncurses -lm
hiddenmessage: main.o screen.o
	$(CC) $(CFLAGS) -o hiddenmessage main.o screen.o $(LINK)
main.o: main.cpp screen.h
	$(CC) $(CFLAGS) -c main.cpp
screen.o: screen.cpp screen.h
	$(CC) $(CFLAGS) -c screen.cpp
clean:
	rm *.o hiddenmessage
