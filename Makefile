CXX=clang++
CFLAGS=-I$(INCDIR) -Wall

SRCDIR=src
INCDIR=inc
BINDIR=bin

DIR_GUARD=@mkdir -p $(@D)

_INCLUDES=flags.h
INCLUDES=$(patsubst %,$(INCDIR)/%,$(_INCLUDES))

_OBJECTS=search.o flags.o
OBJECTS=$(patsubst %,$(BINDIR)/%,$(_OBJECTS))

search: $(OBJECTS)
	$(CXX) -o $@ $^ $(CFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	$(DIR_GUARD)
	$(CXX) -c -o $@ $< $(CFLAGS)

.PHONY:clean
clean:
	rm -rf $(BINDIR) search
