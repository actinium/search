CXX=clang++
CFLAGS=-I$(INCDIR) --std=c++11 -Wall -Wextra -DSEARCHVERSION=\"$(VERSION)\"

VERSION = 0.1

INCDIR=include
SRCDIR=src
OBJDIR=obj

DIR_GUARD=@mkdir -p $(@D)

_INCLUDES=options.h filefinder.h query_string.h
INCLUDES=$(patsubst %,$(INCDIR)/%,$(_INCLUDES))

_OBJECTS=search.o options.o filefinder.o
OBJECTS=$(patsubst %,$(OBJDIR)/%,$(_OBJECTS))

all: search_init search_searcher

search_init: $(SRCDIR)/search.sh
	cp $(SRCDIR)/search.sh search_init && chmod +x search_init

search_searcher: $(OBJECTS)
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	$(DIR_GUARD)
	$(CXX) -c -o $@ $< $(CFLAGS)

.PHONY:clean
clean:
	rm -rf $(OBJDIR) search_init search_searcher
