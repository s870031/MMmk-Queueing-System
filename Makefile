CC = /usr/bin/g++
CFLAGS = 
LIBS = -lm

sim: main.o rv.o event.o qsystem.o
	$(CC) $(CFLAGS) -o sim main.o rv.o event.o qsystem.o

main.o: rv.h event.h qsystem.h main.cpp
	$(CC) $(CFLAGS) -c main.cpp

rv.o: rv.h rv.cpp
	$(CC) $(CFLAGS) -c rv.cpp

event.o: event.h event.cpp
	$(CC) $(CFLAGS) -c event.cpp

qsystem.o: qsystem.h qsystem.cpp
	$(CC) $(CFLAGS) -c qsystem.cpp

clean: 
	rm -f *.o sim
