CC=g++
LFLAGS=
CFLAGS=-c -Wall -O2
OBJS= dijkstra.o server.o digraph.o
PROGS=server
header = wdigraph.h digraph.h dijkstra.h
build = ./build
all: $(PROGS)
server: server.o digraph.o
	$(CC) server.o digraph.o -o $(build)/server $(LFLAGS)
# dijkstra.o: dijkstra.cpp
# 	$(CC) dijkstra.cpp -o dijkstra.o $(CFLAGS)

digraph.o: digraph.cpp
	$(CC) digraph.cpp -o digraph.o $(CFLAGS)
server.o: server.cpp $(header)
	$(CC) server.cpp -o server.o $(CFLAGS)

clean:
	@rm -f $(PROGS) $(OBJS)
