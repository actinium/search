#!/bin/bash

tmppipe=$(mktemp -u "/tmp/search.pipe.XXXXXX")

if mkfifo -m 600 "$tmppipe"; then
  trap 'rm -rf "$tmppipe"' EXIT INT TERM HUP
  if ./search_searcher $tmppipe $@; then
    cat $tmppipe
  fi
else
  echo "Error: Could not create fifo."
fi

exit 0
