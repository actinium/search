#include "options.h"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <string>

// Global struct which stores command line options.
// As default all flags are false, the search directory is the current
// directory and 8 lines are used to print results.
program_options options = {".",false,false,false,false,false,8 };

bool get_options(int argc, char* argv[]){
  int c;
  opterr = 0;
  while ((c = getopt (argc, argv, "adfhl:v")) != -1){
    switch (c){
      case 'a':
        options.include_hidden = true;
        break;
      case 'd':
        options.directories_only = true;
        break;
      case 'f':
        options.files_only = true;
        break;
      case 'h':
        options.show_help = true;
        break;
      case 'l':
        options.number_of_result_lines = std::atoi(optarg);
        break;
      case 'v':
        options.show_version = true;
        break;
      case '?':
        if (optopt == 'l')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option '-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character '\\x%x'.\n",
                   optopt);
        return false;
      default:
        abort ();
      }
  }
  if(optind < argc){
    options.search_dir = std::string(argv[optind]);
  }
  return true;
}

void print_version(){
  fprintf(stderr,"search version %s\n",SEARCHVERSION);
}

void print_help(){
  fprintf(stderr,"Usage: search [OPTION]... DIRECTORY\n");
  fprintf(stderr,"\n");
  fprintf(stderr,"Options:\n");
  fprintf(stderr,"  -h    show this help message and exit.\n");
  fprintf(stderr,"  -v    show version info and exit.\n");
  fprintf(stderr,"  -a    do not ignore entries starting with '.'.\n");
  fprintf(stderr,"  -l L  use L number of lines to show result.\n");
  fprintf(stderr,"  -f    search only for files. ignore directories.\n");
  fprintf(stderr,"  -d    search only for directories. ignore files.\n");
}
