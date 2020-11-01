CC = g++
CFLAGS = -g3 -Wall
LDFLAGS = -lm

ODIR = build
IDIR = headers
SDIR = src

EXECUTABLE = run

_DEPS = input.h LSH.h HashTable.h HashFunctions.h kMeans.h list.h RedBlack.h cube.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = cubemain.o input.o LSH.o HashTable.o HashFunctions.o kMeans.o list.o RedBlack.o cube.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cc $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(ODIR)/*.o
	rm -f $(EXECUTABLE)

all: $(EXECUTABLE)

valgrind:
	valgrind --track-origins=yes --trace-children=yes --leak-check=full ./run

exe:
	./run
