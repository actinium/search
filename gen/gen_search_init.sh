#!/bin/sh

SEARCHDIR=$(pwd);

echo "function search {" > search_init.sh;
echo "  $SEARCHDIR/search_searcher \$@;" >> search_init.sh;
echo "}" >> search_init.sh;


exit 0;
