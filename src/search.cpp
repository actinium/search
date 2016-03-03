#include <cstdio>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "filefinder.h"
#include "options.h"
#include "query_string.h"
#include "terminal.h"


void print_result(const terminal& term, query_string qstr, int selected){
  term.restore_cursor_pos();
  for(int i=1; i<= 5; ++i){
    printf("\n");
    term.erase_line();
    if(i-1==selected) printf("\033[7m");
    printf("%d: %s",i,qstr.get_str());
    if(i-1==selected) printf("\033[0m");
  }
}

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
  
  query_string qstr;

  terminal term;
  int c;

  int selected = 0;
  term.print_search_line(qstr.get_str(),qstr.get_pos());
  while(1){
    c = getchar();
    if(c == 27){ // esc
      c=getchar();
      if(c == '['){
        c=getchar();
        if(c == 'A'){ // up
          selected--;
          print_result(term, qstr, selected);
          term.restore_cursor_pos();
          term.cursor_right(qstr.get_pos()+1);
        }else if(c == 'B'){ // down
          selected++;
          print_result(term, qstr, selected);
          term.restore_cursor_pos();
          term.cursor_right(qstr.get_pos()+1);
        }else if(c == 'C'){ // right
          term.cursor_right();
          qstr.cursor_right();
        }else if(c == 'D'){ // left
          term.cursor_left();
          qstr.cursor_left();
        }
      }
    }else if(c == 9){
      // tab
    }else if(c == 10){ // enter
      print_result(term, qstr, selected);
      term.restore_cursor_pos();
      term.cursor_right(qstr.get_pos()+1);
    }else if(c == 127){ //backspace
      qstr.remove();
      term.print_search_line(qstr.get_str(),qstr.get_pos());
    }else{
      qstr.add(c);
      term.print_search_line(qstr.get_str(),qstr.get_pos());
    }
  }
}
