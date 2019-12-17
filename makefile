IDIR = ./include
ODIR = ./obj
SRCDIR = ./src

CC = g++
FLAGS = -std=c++11 -I$(IDIR)
EXE = gallery
_OBJECTS = main.o polygon.o graph.o artgallery.o
_DEPS = polygon.h graph.h artgallery.h


OBJECTS = $(patsubst %,$(ODIR)/%,$(_OBJECTS))
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(EXE): $(OBJECTS) $(DEPS)
	$(CC) -o $@ $(OBJECTS) $(FLAGS)

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

.PHONY: clean

clean:
	rm $(OBJECTS) $(EXE)
