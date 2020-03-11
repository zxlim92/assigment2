CC=g++
LFLAGS=
CFLAGS=-c -Wall -O2
OBJS= dijkstra.o sever.o digraph.o
PROGS=server

all: $(PROGS)

dijkstra.o: dijkstra.cpp
	$(CC) dijkstra.cpp -o dijkstra.o $(CFLAGS)

digraph.o:digraph.cpp
	$(CC) digraph.cpp -o digraph.o $(LFLAGS)
sever.o: server.cpp
	$(CC) server.cpp -o server.o $(LFLAGS)

clean:
	@rm -f $(PROGS) $(OBJS)