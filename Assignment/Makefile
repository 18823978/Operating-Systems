# Makefile Variables
CC		 = gcc -pthread
EXEC	 = cq
CFLAGS = -Wall -ansi -pedantic -g 
OBJ 	 = main.o fileIO.o services.o customerQueue.o timers.o

ifdef DEBUG
CFLAGS += -D DEBUG
DEBUG : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c fileIO.h customerQueue.h services.h timers.h
	$(CC) $(CFLAGS) main.c -c 

fileIO.o : fileIO.c fileIO.h
	$(CC) $(CFLAGS) fileIO.c -c

services.o : services.c services.h
	$(CC) $(CFLAGS) services.c -c

customerQueue.o : customerQueue.c customerQueue.h
	$(CC) $(CFLAGS) customerQueue.c -c

timers.o : timers.c timers.h
	$(CC) $(CFLAGS) timers.c -c

clean:
	rm -f $(EXEC) $(OBJ)