CXX=clang++
CFLAGS=-I$(INCDIR) --std=c++11 -Wall -Wextra -DSEARCHVERSION=\"$(VERSION)\"
LINKFLAGS=-licuuc
DIR_GUARD=@mkdir -p $(@D)

VERSION = 0.1

################################################################################
#	Directories
################################################################################
INCDIR=src
SRCDIR=src
SCRIPTDIR=script
OBJDIR=obj
INSTALLDIR?=/usr/local/bin

################################################################################
# Files
################################################################################
_INCLUDES=options.h filefinder.h query_string.h string_util.h terminal.h
INCLUDES=$(patsubst %,$(INCDIR)/%,$(_INCLUDES))

_OBJECTS=search.o options.o filefinder.o string_util.o terminal.o
OBJECTS=$(patsubst %,$(OBJDIR)/%,$(_OBJECTS))

################################################################################
# Build Targets
################################################################################
all: init_search searcher

init_search: $(SCRIPTDIR)/gen_search_init.sh
	@echo "\033[1m\033[95m[Generating init script]\033[0m"
	$(SCRIPTDIR)/gen_search_init.sh

searcher: $(OBJECTS)
	@echo "\033[1m\033[95m[Building $@]\033[0m"
	$(CXX) -o $@ $^ $(CFLAGS) $(LINKFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	@echo "\033[1m\033[95m[Compiling $<]\033[0m"
	$(DIR_GUARD)
	$(CXX) -c -o $@ $< $(CFLAGS)

################################################################################
# Install
################################################################################
.PHONY: install
install: searcher
	@echo "\033[1m\033[95m[Installing search in $(INSTALLDIR)]\033[0m"
	cp searcher $(INSTALLDIR)/searcher
	$(SCRIPTDIR)/gen_search_init.sh $(INSTALLDIR)

################################################################################
# Uninstall
################################################################################
.PHONY: uninstall
uninstall:
	@echo "\033[1m\033[95m[Uninstalling search from $(INSTALLDIR)]\033[0m"
	rm -f $(INSTALLDIR)/init_search
	rm -f $(INSTALLDIR)/searcher

################################################################################
# Clean
################################################################################
.PHONY:clean
clean:
	@echo "\033[1m\033[95m[Cleaning up]\033[0m"
	rm -rf $(OBJDIR) init_search searcher

################################################################################
# Help
################################################################################
.PHONY:help
help:
	@echo "Makefile for search"
	@echo ""
	@echo "Targets:"
	@echo "  all                      - build init_search and searcher."
	@echo "  init_search              - build init_search."
	@echo "  searcher                 - build searcher."
	@echo "  install   [INSTALLDIR=?] - install search in INSTALLDIR (deafult is /usr/local/bin)"
	@echo "  uninstall [INSTALLDIR=?] - remove search from INSTALLDIR (deafult is /usr/local/bin)"
	@echo "  clean                    - remove compiled files."
	@echo "  help                     - show this message."

