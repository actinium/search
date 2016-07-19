#ifndef SEARCH_TERMINAL_H
#define SEARCH_TERMINAL_H

#include <termios.h>
#include <unistd.h>

#include "filefinder.h"

class terminal{
 public:
  terminal();
  ~terminal();

  void save_cursor_pos() const;
  void restore_cursor_pos() const;

  void erase_line() const;
  void cursor_left(int n = 1) const;
  void cursor_right(int n = 1) const;
  void cursor_up(int n = 1) const;
  void cursor_down(int n = 1) const;

  void print_search_line(std::string str, int pos) const;
  void print_result(const std::vector<node>& result, std::size_t selected) const;

 private:
  struct termios oldt;
  struct termios newt;
};

#endif
