CXX=clang++
CFLAGS=-I$(INCDIR) --std=c++11 -Wall -Wextra -DSEARCHVERSION=\"$(VERSION)\"

VERSION = 0.1

INCDIR=include
SRCDIR=src
GENDIR=gen
OBJDIR=obj

DIR_GUARD=@mkdir -p $(@D)

_INCLUDES=options.h filefinder.h query_string.h terminal.h
INCLUDES=$(patsubst %,$(INCDIR)/%,$(_INCLUDES))

_OBJECTS=search.o options.o filefinder.o
OBJECTS=$(patsubst %,$(OBJDIR)/%,$(_OBJECTS))

all: init_search searcher

init_search: $(GENDIR)/gen_search_init.sh
	$(GENDIR)/gen_search_init.sh

searcher: $(OBJECTS)
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	$(DIR_GUARD)
	$(CXX) -c -o $@ $< $(CFLAGS)

.PHONY: install
install: searcher
	@echo "Installing search."
	mkdir -p /usr/local/bin/search
	cp searcher /usr/local/bin/search/searcher
	./gen/gen_search_init.sh /usr/local/bin/search

.PHONY: uninstall
uninstall:
	@echo "Uninstalling search."
	rm -f /usr/local/bin/search/init_search
	rm -f /usr/local/bin/search/searcher
	rm -df /usr/local/bin/search

.PHONY:clean
clean:
	rm -rf $(OBJDIR) init_search searcher
