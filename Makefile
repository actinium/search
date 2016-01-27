CXX=clang++
CFLAGS=-I$(INCDIR) -Wall

INCDIR=include
SRCDIR=src
BINDIR=bin

DIR_GUARD=@mkdir -p $(@D)

_INCLUDES=options.h
INCLUDES=$(patsubst %,$(INCDIR)/%,$(_INCLUDES))

_OBJECTS=search.o options.o
OBJECTS=$(patsubst %,$(BINDIR)/%,$(_OBJECTS))

search: $(OBJECTS)
	$(CXX) -o $@ $^ $(CFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	$(DIR_GUARD)
	$(CXX) -c -o $@ $< $(CFLAGS)

.PHONY:clean
clean:
	rm -rf $(BINDIR) search
