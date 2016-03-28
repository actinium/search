# SEARCH

Interactive command-line file searching.

## Installation
###Step 1.
Run:

```
make install
```

This will move `searcher` and `init_search` to `/usr/local/bin/`.

###Step 2.
Add:

```
source /usr/local/bin/init_search
```

to your shell rc-file.

## Usage

```
  Usage: search [OPTION]... DIRECTORY

  Options:
    -h    show this help message and exit.
    -v    show version info and exit.
    -a    do not ignore entries starting with '.'.
    -l L  use L number of lines to show result.
    -f    search only for files. ignore directories.
    -d    search only for directories. ignore files.
```

## License
This project is licensed under the MIT License. See the full license text in
[`LICENSE`](LICENSE).
