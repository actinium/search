CXX=clang++
CFLAGS=-Wall

SRCDIR=src
BINDIR=bin

dir_guard=@mkdir -p $(@D)

search: $(BINDIR)/search.o
	$(CXX) $(CFLAGS) -o search $(BINDIR)/search.o

$(BINDIR)/search.o: $(SRCDIR)/search.cpp
	$(dir_guard)
	$(CXX) $(CFLAGS) -c -o $(BINDIR)/search.o $(SRCDIR)/search.cpp

.PHONY:clean
clean:
	rm -rf $(BINDIR)
	rm -f  search
