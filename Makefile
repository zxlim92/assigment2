CC=g++
LFLAGS=
CFLAGS=-c -Wall -O2
OBJS= dijkstra.o server.o digraph.o
PROGS=server
header = wdigraph.h digraph.h dijkstra.h
all: $(PROGS)
server: server.o
	$(CC) server.o -o server $(LFLAGS)
# dijkstra.o: dijkstra.cpp
# 	$(CC) dijkstra.cpp -o dijkstra.o $(CFLAGS)

# digraph.o:digraph.cpp
# 	$(CC) digraph.cpp -o digraph.o $(CFLAGS)
server.o: server.cpp wdigraph.h digraph.h
	$(CC) server.cpp -o server.o $(CFLAGS)


clean:
	@rm -f $(PROGS) $(OBJS)
