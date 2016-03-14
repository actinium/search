#ifndef SEARCH_TERMINAL_H
#define SEARCH_TERMINAL_H

#include "filefinder.h"

class terminal{
 public:
  terminal(){
    // save and copy terminal settings
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;

    // set new terminal settings
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    //
    for(int i=0; i < options.number_of_result_lines; ++i){
      fprintf(stderr,"\n");
    }
    cursor_up(options.number_of_result_lines);
    save_cursor_pos();
    restore_cursor_pos();
  }

  ~terminal(){
    // restore terminal settings
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  }

  void save_cursor_pos() const{
    fprintf(stderr,"\033[s");
  }

  void restore_cursor_pos() const{
    fprintf(stderr,"\033[u");
  }

  void erase_line() const{
    fprintf(stderr,"\033[K");
  }

  void cursor_left(int n = 1) const{
    fprintf(stderr,"\033[%dD",n);
  }

  void cursor_right(int n = 1) const{
    fprintf(stderr,"\033[%dC",n);
  }

  void cursor_up(int n = 1) const{
    fprintf(stderr,"\033[%dA",n);
  }

  void cursor_down(int n = 1) const{
    fprintf(stderr,"\033[%dB",n);
  }

  void print_search_line(std::string str, int pos) const{
    restore_cursor_pos();
    erase_line();
    fprintf(stderr,">%s", str.c_str());
    restore_cursor_pos();
    cursor_right(1+pos);
  }

  void print_result(const terminal& term,const std::vector<node>& result, std::size_t selected){
    term.restore_cursor_pos();
    for(int i=0; i < options.number_of_result_lines; ++i){
      fprintf(stderr,"\n");
      term.erase_line();
    }
    term.restore_cursor_pos();

    for(std::size_t i=1; i <= result.size(); ++i){
      fprintf(stderr,"\n");
      if(i-1==selected) fprintf(stderr,"\033[7m");
      fprintf(stderr,"%lu: %s%s",i,result[i-1].location.c_str(), result[i-1].filename.c_str());
      if(i-1==selected) fprintf(stderr,"\033[0m");
    }
  }
 private:
  struct termios oldt;
  struct termios newt;
};

#endif
