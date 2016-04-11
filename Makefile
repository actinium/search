CXX=clang++
CFLAGS=-I$(INCDIR) --std=c++11 -Wall -Wextra -DSEARCHVERSION=\"$(VERSION)\"

VERSION = 0.1

INCDIR=include
SRCDIR=src
SCRIPTDIR=script
OBJDIR=obj

DIR_GUARD=@mkdir -p $(@D)

_INCLUDES=options.h filefinder.h query_string.h terminal.h
INCLUDES=$(patsubst %,$(INCDIR)/%,$(_INCLUDES))

_OBJECTS=search.o options.o filefinder.o terminal.o
OBJECTS=$(patsubst %,$(OBJDIR)/%,$(_OBJECTS))

all: init_search searcher

init_search: $(SCRIPTDIR)/gen_search_init.sh
	$(SCRIPTDIR)/gen_search_init.sh

searcher: $(OBJECTS)
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	$(DIR_GUARD)
	$(CXX) -c -o $@ $< $(CFLAGS)

.PHONY: install
install: searcher
	@echo "Installing search."
	cp searcher /usr/local/bin/searcher
	$(SCRIPTDIR)/gen_search_init.sh /usr/local/bin

.PHONY: uninstall
uninstall:
	@echo "Uninstalling search."
	rm -f /usr/local/bin/init_search
	rm -f /usr/local/bin/searcher

.PHONY:clean
clean:
	rm -rf $(OBJDIR) init_search searcher
