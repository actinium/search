#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include "filefinder.h"
#include "options.h"
#include "query_string.h"

int main(int argc, char* argv[]){
  if(!get_options(argc, argv)){
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
  
  std::vector<node> files;
  find_files(files);
  
  printf(">");
  char input[100];
  scanf("%s",input);
  query_string qstr(input);
  qstr.add('2');
  qstr.cursor_left();
  qstr.add('1');
  qstr.cursor_left();
  qstr.remove();
  printf("%s\n",qstr.get_str());
  
}
