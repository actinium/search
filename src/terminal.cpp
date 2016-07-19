#include "terminal.h"

#include <termios.h>
#include <unistd.h>

#include "filefinder.h"
#include "options.h"

terminal::terminal(){
  // save and copy terminal settings
  tcgetattr( STDIN_FILENO, &oldt);
  newt = oldt;

  // set new terminal settings
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);

  // print as many newlines as number_of_result_lines to
  // enable moving the cursor up and down.
  for(int i=0; i < options.number_of_result_lines; ++i){
    fprintf(stderr,"\n");
  }
  cursor_up(options.number_of_result_lines);
  save_cursor_pos();
  restore_cursor_pos();
}

terminal::~terminal(){
  // restore terminal settings
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

void terminal::save_cursor_pos() const{
  fprintf(stderr,"\033[s");
}

void terminal::restore_cursor_pos() const{
  fprintf(stderr,"\033[u");
}

void terminal::erase_line() const{
  fprintf(stderr,"\033[K");
}

void terminal::cursor_left(int n) const{
  fprintf(stderr,"\033[%dD",n);
}

void terminal::cursor_right(int n) const{
  fprintf(stderr,"\033[%dC",n);
}

void terminal::cursor_up(int n) const{
  fprintf(stderr,"\033[%dA",n);
}

void terminal::cursor_down(int n) const{
  fprintf(stderr,"\033[%dB",n);
}

void terminal::print_search_line(std::string str, int pos) const{
  restore_cursor_pos();
  erase_line();
  fprintf(stderr,">%s", str.c_str());
  restore_cursor_pos();
  cursor_right(1+pos);
}


void terminal::print_result(const std::vector<node>& result, std::size_t selected) const{
  restore_cursor_pos();
  for(int i=0; i < options.number_of_result_lines; ++i){
    fprintf(stderr,"\n");
    erase_line();
  }
  restore_cursor_pos();

  for(std::size_t i=1; i <= result.size(); ++i){
    fprintf(stderr,"\n");
    if(i-1==selected) fprintf(stderr,"\033[7m");
    fprintf(stderr,"%lu: %s%s",(unsigned long)i,result[i-1].location.c_str(), result[i-1].filename.c_str());
    if(i-1==selected) fprintf(stderr,"\033[0m");
  }
}
