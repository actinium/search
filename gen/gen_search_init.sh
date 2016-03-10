#!/bin/sh

SEARCHDIR=$(pwd);

echo "function search {" > init_search;
echo "  $SEARCHDIR/searcher \$@;" >> init_search;
echo "}" >> init_search;


exit 0;
