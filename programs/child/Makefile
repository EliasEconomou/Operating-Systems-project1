
INCLUDE = ../../include
SRC = ../../src

CC = g++
CFLAGS = -Wall -g -Werror -I$(INCLUDE)
LDFLAGS = -lm

OBJS = Child.o $(SRC)/semaphores.o $(SRC)/sharedmemory.o
EXEC = Child


$(EXEC): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)