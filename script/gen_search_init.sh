#!/bin/sh

SEARCHDIR=${1-$(pwd)};

echo "function search {"                       >  $SEARCHDIR/init_search;
# Don't prefix searcher with pwd when installing to /usr/local/bin
if [ "$SEARCHDIR" = "/usr/local/bin" ]; then
  echo "  OUTPUT=\$(searcher \$@);"            >> $SEARCHDIR/init_search;
else
  echo "  OUTPUT=\$($SEARCHDIR/searcher \$@);" >> $SEARCHDIR/init_search;
fi
echo "  if [ -n \"\$OUTPUT\" ]; then"          >> $SEARCHDIR/init_search;
echo "    cd \${OUTPUT};"                      >> $SEARCHDIR/init_search;
echo "  fi"                                    >> $SEARCHDIR/init_search;
echo "}"                                       >> $SEARCHDIR/init_search;


exit 0;
