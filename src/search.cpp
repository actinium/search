#include <cstdio>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "filefinder.h"
#include "options.h"
#include "query_string.h"
#include "terminal.h"


std::vector<node> files;

void print_result(const terminal& term, query_string qstr, int selected){
  term.restore_cursor_pos();
  for(int i=0; i < options.number_of_result_lines; ++i){
    fprintf(stderr,"\n");
    term.erase_line();
  }
  term.restore_cursor_pos();
  std::string str(qstr.get_str());
  if( str != ""){
    int count = 1;
    for(std::size_t i=0; i < files.size() && count <=options.number_of_result_lines; ++i){
      if(files[i].filename.find(qstr.get_str()) != std::string::npos){
        fprintf(stderr,"\n");
        if(count-1==selected) fprintf(stderr,"\033[7m");
        fprintf(stderr,"%d: %s%s",count,files[i].location.c_str(), files[i].filename.c_str());
        if(count-1==selected) fprintf(stderr,"\033[0m");
        count++;
      }
    }
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
          if(selected < 0){
            selected = 0;
          }
          print_result(term, qstr, selected);
          term.restore_cursor_pos();
          term.cursor_right(qstr.get_pos()+1);
        }else if(c == 'B'){ // down
          selected++;
          if(selected > options.number_of_result_lines-1){
            // TODO: should be number of results.
            selected = options.number_of_result_lines-1;
          }
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
      fprintf(stderr,"\n");
      return 0;
    }else if(c == 127){ //backspace
      qstr.remove();
      term.print_search_line(qstr.get_str(),qstr.get_pos());
      print_result(term, qstr, selected);
      term.restore_cursor_pos();
      term.cursor_right(qstr.get_pos()+1);
    }else{
      qstr.add(c);
      term.print_search_line(qstr.get_str(),qstr.get_pos());
      print_result(term, qstr, selected);
      term.restore_cursor_pos();
      term.cursor_right(qstr.get_pos()+1);
    }
  }
}
