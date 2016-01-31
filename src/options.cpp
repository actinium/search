#include "options.h"
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>

program_options options = { false,false,false,false,false,5 };

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
  return true;
}
