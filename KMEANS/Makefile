CC = g++
CFLAGS = -g3 -Wall
LDFLAGS = -lm

ODIR = build
IDIR = headers
SDIR = src

EXECUTABLE = cluster

_DEPS = input.h LSH.h HashTable.h HashFunctions.h kMeans.h list.h RedBlack.h cube.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o input.o LSH.o HashTable.o HashFunctions.o kMeans.o list.o RedBlack.o cube.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cc $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -O3

clean:
	rm -f $(ODIR)/*.o
	rm -f $(EXECUTABLE)

all: $(EXECUTABLE)

valgrind:
	# valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --leak-check=full ./run
	valgrind --track-origins=yes --trace-children=yes --leak-check=full ./run

exe:
	# ./cluster -d t10k-images.idx3-ubyte -i input_file_newspace -n classes_from_NN_as_clusters_file.txt -c configuration_file.conf -o output_file
	./cluster -d t10k-images.idx3-ubyte -i query_file_newspace -n classes_from_NN_as_clusters_file.txt -c configuration_file.conf -o output_file