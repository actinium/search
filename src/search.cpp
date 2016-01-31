#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include "options.h"

int main(int argc, char* argv[]){
  if(argc < 1){
    return 1;
  }
  int pipe_fd = open(argv[argc-1],O_WRONLY);
  if(pipe_fd == -1){
    return 1;
  }
  if(!get_options(argc-1, argv)){
    return 1;
  }
  if(options.show_help){
    print_help();
    return 0;
  }
  if(options.show_version){
    print_version();
    return 0;
  }
  printf(">\n"); 
  write(pipe_fd,"test",5);
}
