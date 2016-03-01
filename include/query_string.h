#ifndef SEARCH_QUERY_STRING_H
#define SEARCH_QUERY_STRING_H

#include <string>

class query_string{
 public:
  query_string():str(""),pos(0){}
  query_string(const char* s):str(s),pos(0){}
  const char* get_str(){
    return str.c_str();
  }
  void add(char c){
    // add c at pos
  }
  void remove(){
    // remove char before pos
  }
  void cursor_left(){
    // pos left
  }
  void cursor_right(){
    // pos right
  }
 private:
  std::string str;
  std::size_t pos;
};

#endif
