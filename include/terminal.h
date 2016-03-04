#ifndef SEARCH_TERMINAL_H
#define SEARCH_TERMINAL_H

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
      printf("\n");
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
    printf("\033[s");
  }

  void restore_cursor_pos() const{
    printf("\033[u");
  }

  void erase_line() const{
    printf("\033[K");
  }

  void cursor_left(int n = 1) const{
    printf("\033[%dD",n);
  }

  void cursor_right(int n = 1) const{
    printf("\033[%dC",n);
  }

  void cursor_up(int n = 1) const{
    printf("\033[%dA",n);
  }

  void cursor_down(int n = 1) const{
    printf("\033[%dB",n);
  }

  void print_search_line(std::string str, int pos) const{
    restore_cursor_pos();
    erase_line();
    printf(">%s", str.c_str());
    restore_cursor_pos();
    cursor_right(1+pos);
  }
 private:
  struct termios oldt;
  struct termios newt;
};

#endif
