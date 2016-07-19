CXX=clang++
CFLAGS=-I$(INCDIR) --std=c++11 -Wall -Wextra -DSEARCHVERSION=\"$(VERSION)\"
LINKFLAGS=-licuuc

VERSION = 0.1

INCDIR=src
SRCDIR=src
SCRIPTDIR=script
OBJDIR=obj

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
	$(CXX) -o $@ $^ $(CFLAGS) $(LINKFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	@echo "\033[1m\033[95m[Compiling $<]\033[0m"
	$(DIR_GUARD)
	$(CXX) -c -o $@ $< $(CFLAGS)

.PHONY: install
install: searcher
	@echo "\033[1m\033[95m[Installing search]\033[0m"
	@id_check=`id -u`; \
	if test $$id_check != 0; \
	then \
		echo "\033[1m\033[91mError: \033[21m\033[39mInstalling search requires root privileges!\033[0m"; \
		return 1; \
	else \
		return 0; \
	fi
	cp searcher /usr/local/bin/searcher
	$(SCRIPTDIR)/gen_search_init.sh /usr/local/bin

.PHONY: uninstall
uninstall:
	@echo "\033[1m\033[95m[Uninstalling search]\033[0m"
	@id_check=`id -u`; \
	if test $$id_check != 0; \
	then \
		echo "\033[1m\033[91mError: \033[21m\033[39mUninstalling search requires root privileges!\033[0m"; \
		return 1; \
	else \
		return 0; \
	fi
	rm -f /usr/local/bin/init_search
	rm -f /usr/local/bin/searcher

.PHONY:clean
clean:
	@echo "\033[1m\033[95m[Cleaning up]\033[0m"
	rm -rf $(OBJDIR) init_search searcher

