#!/bin/zsh

tmppipe=$(mktemp -u "/tmp/search.pipe.XXXXXX")

if mkfifo -m 600 "$tmppipe"; then
  trap 'rm -rf "$tmppipe"' EXIT INT TERM HUP
  coproc { cat $tmppipe; }
  ./search_searcher $@ $tmppipe
  read resp <&p
  if [[ "$resp" != '' ]]; then
    echo $resp
  fi
else
  echo "Error: Could not create fifo."
fi

exit 0
