#!/bin/bash

tmppipe=$(mktemp -u "/tmp/search.pipe.XXXXXX")

if mkfifo -m 600 "$tmppipe"; then
  trap 'rm -rf "$tmppipe"' EXIT INT TERM HUP
  ./search_searcher $@ $tmppipe &
  read resp < $tmppipe
  if [[ "$resp" != '' ]]; then
    echo $resp
  fi
else
  echo "Error: Could not create fifo."
fi

exit 0
