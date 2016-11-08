#Todo

- add long options support
- add option to only search for specific file-type
- exit search with escape (Needs new way to handle input)

##### terminal:

- make sure output is shorter than terminal width
- print newline before exiting when Ctrl-C is pressed

##### utf-8:

- utf-8 support (Maybe use [ICU](http://site.icu-project.org/))
- make search case insensitive

##### threads:

- index files in a background thread and immediately enable input

##### portability(Maybe):

- make filefinder work on systems without `FTW_ACTIONRETVAL` and `FTW_SKIP_SUBTREE`
