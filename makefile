CC=gcc
FLAGS = -Wall

all: graph

graph: main.o algo.o nodes.o edges.o
	$(CC) $(FLAGS) main.o algo.o nodes.o edges.o -o graph

main.o: main.c algo.h graph.h nodes.h edges.h
	$(CC) $(FLAGS) -c -g main.c

algo.o: algo.c algo.h graph.h nodes.h edges.h
	$(CC) $(FLAGS) -c -g algo.c

nodes.o: nodes.c algo.h graph.h nodes.h edges.h
	$(CC) $(FLAGS) -c -g nodes.c

edges.o: edges.c algo.h graph.h nodes.h edges.h
	$(CC) $(FLAGS) -c -g edges.c


.PHONY: clean all

clean:
	rm -f *.o graph