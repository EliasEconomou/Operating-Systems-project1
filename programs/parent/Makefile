
INCLUDE = ../../include
SRC = ../../src

CC = g++
CFLAGS = -Wall -g -Werror -I$(INCLUDE)
LDFLAGS = -lm

OBJS = Parent.o $(SRC)/semaphores.o $(SRC)/sharedmemory.o
EXEC = Parent


# Arguments for make run / make valgrind
ARGS = ../../file.txt 10 100

$(EXEC): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./$(EXEC) $(ARGS)
