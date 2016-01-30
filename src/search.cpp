#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include "options.h"

int main(int argc, char* argv[]){
  if(argc < 1){
    return 1;
  }
  int pipe_fd = open(argv[1],O_WRONLY);
  if(pipe_fd == -1){
    return 1;
  }
  printf("Hello Searcher");
  
  std::printf ("all files        = %d\n"
               "directories only = %d\n"
               "files only       = %d\n"
               "show help        = %d\n"
               "number of lines  = %d\n"
               "show version     = %d\n",
          options.include_hidden_files, options.directories_only, options.files_only,
          options.show_help, options.number_of_result_lines, options.show_version);
  write(pipe_fd,"test",5);
}
