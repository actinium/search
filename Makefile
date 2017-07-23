CXX=clang++
CFLAGS=-I$(INCDIR) --std=c++11 -Wall -Wextra -DSEARCHVERSION=\"$(VERSION)\"

VERSION = 0.1

INCDIR=src
SRCDIR=src
SCRIPTDIR=script
OBJDIR=obj
INSTALLDIR?=/usr/local/bin

DIR_GUARD=@mkdir -p $(@D)

_INCLUDES=options.h filefinder.h query_string.h string_util.h terminal.h
INCLUDES=$(patsubst %,$(INCDIR)/%,$(_INCLUDES))

_OBJECTS=search.o options.o filefinder.o string_util.o terminal.o
OBJECTS=$(patsubst %,$(OBJDIR)/%,$(_OBJECTS))

all: init_search searcher

init_search: $(SCRIPTDIR)/gen_search_init.sh
	@echo "\033[1m\033[95m[Generating init script]\033[0m"
	$(SCRIPTDIR)/gen_search_init.sh

searcher: $(OBJECTS)
	@echo "\033[1m\033[95m[Building $@]\033[0m"
	$(CXX) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	@echo "\033[1m\033[95m[Compiling $<]\033[0m"
	$(DIR_GUARD)
	$(CXX) -c -o $@ $< $(CFLAGS)

.PHONY: install
install: searcher
	@echo "\033[1m\033[95m[Installing search]\033[0m"
	cp searcher $(INSTALLDIR)/searcher
	$(SCRIPTDIR)/gen_search_init.sh $(INSTALLDIR)

.PHONY: uninstall
uninstall:
	@echo "\033[1m\033[95m[Uninstalling search]\033[0m"
	rm -f $(INSTALLDIR)/init_search
	rm -f $(INSTALLDIR)/searcher

.PHONY:clean
clean:
	@echo "\033[1m\033[95m[Cleaning up]\033[0m"
	rm -rf $(OBJDIR) init_search searcher

.PHONY:help
help:
	@echo "Makefile for search"
	@echo ""
	@echo "Targets:"
	@echo "  all                      - build init_search and searcher."
	@echo "  init_search              - build init_search."
	@echo "  searcher                 - build searcher."
	@echo "  install   [INSTALLDIR=?] - install search to INSTALLDIR (deafult is /usr/local/dir)"
	@echo "  uninstall [INSTALLDIR=?] - remove search from INSTALLDIR (deafult is /usr/local/dir)"
	@echo "  clean                    - remove compiled files."
	@echo "  help                     - show this message."

