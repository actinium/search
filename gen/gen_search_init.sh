#!/bin/sh

SEARCHDIR=${1-$(pwd)};

echo "function search {"                     >  $SEARCHDIR/init_search;
echo "  OUTPUT=\$($SEARCHDIR/searcher \$@);" >> $SEARCHDIR/init_search;
echo "  if [ -n \"\$OUTPUT\" ]; then"        >> $SEARCHDIR/init_search;
echo "    cd \${OUTPUT};"                    >> $SEARCHDIR/init_search;
echo "  fi"                                  >> $SEARCHDIR/init_search;
echo "}"                                     >> $SEARCHDIR/init_search;


exit 0;
