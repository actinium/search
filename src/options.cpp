#include "options.h"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <string>
#include <getopt.h>


program_options options = {".",false,false,false,false,false,8 };

bool get_options(int argc, char* argv[]){
  int c;
  while (1){
    static struct option long_options[] = {
      {"help",       no_argument,       0, 'h'},
      {"version",    no_argument,       0, 'v'},
      {"all",        no_argument,       0, 'a'},
      {"lines",      required_argument, 0, 'l'},
      {"dirs-only",  no_argument,       0, 'd'},
      {"files-only", no_argument,       0, 'f'},
      {0, 0, 0, 0}
    };
    int option_index = 0;

    c = getopt_long (argc, argv, "hval:df",
                     long_options, &option_index);

    if (c == -1){
      break;
    }

    int l_arg;
    switch (c){
      case 'h':
        options.show_help = true;
        break;
      case 'v':
        options.show_version = true;
        break;
      case 'a':
        options.include_hidden = true;
        break;
      case 'l':
        l_arg = std::atoi(optarg);
        if(l_arg > 0){
          options.number_of_result_lines = l_arg;
        }else{
          fprintf(stderr,"Invalid argument to option -l/--lines\n");
          return false;
        }
        break;
      case 'd':
        options.directories_only = true;
        break;
      case 'f':
        options.files_only = true;
        break;
      case '?':
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
  fprintf(stderr,"  -h    --help       show this help message and exit.\n");
  fprintf(stderr,"  -v    --version    show version info and exit.\n");
  fprintf(stderr,"  -a    --all        do not ignore entries starting with '.'.\n");
  fprintf(stderr,"  -d    --dirs-only  search only for directories. ignore files.\n");
  fprintf(stderr,"  -f    --files-only search only for files. ignore directories.\n");
  fprintf(stderr,"  -l N  --lines=N    use N number of lines to show result.\n");
}
