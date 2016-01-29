#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  if(argc < 1){
    return 1;
  }
  int pipe_fd = open(argv[1],O_WRONLY);
  if(pipe_fd == -1){
    return 1;
  }
  write(pipe_fd,"test",5);
  std::cout << "Hello Searcher" << std::endl;
}
