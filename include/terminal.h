#ifndef SEARCH_TERMINAL_H
#define SEARCH_TERMINAL_H

class term{
  static void save_cursor_pos(){
    printf("\033[s");
  }

  static void restore_cursor_pos(){
    printf("\033[u");
  }

  static void erase_line(){
    printf("\033[K");
  }

  static void cursor_left(int n = 1){
    printf("\033[%dD",n);
  }

  static void cursor_right(int n = 1){
    printf("\033[%dC",n);
  }

  static void cursor_up(int n = 1){
    printf("\033[%dA",n);
  }

  static void cursor_down(int n = 1){
    printf("\033[%dB",n);
  }

  static void print_search_line(const char* s, int pos){
    restore_cursor_pos();
    erase_line();
    printf(">%s",s);
    restore_cursor_pos();
    cursor_right(1+pos);
  }
};

#endif
