#!/bin/sh

SEARCHDIR=${1-pwd};

echo "function search {" > $SEARCHDIR/init_search;
echo "  $SEARCHDIR/searcher \$@;" >> $SEARCHDIR/init_search;
echo "}" >> $SEARCHDIR/init_search;


exit 0;
