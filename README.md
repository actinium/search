# SEARCH

Interactive command-line file searching.

## Installation
##### 1. Clone the repository:
```shell
git clone https://github.com/actinium/search.git
```

##### 2. Build and install with:
``` shell
make install
```
This will move `searcher` and `init_search` to `/usr/local/bin/`.

##### 3. Add search function to your shell configuration file:
``` 
# Add this line to your shell rc-file
source /usr/local/bin/init_search
```

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
