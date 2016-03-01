#ifndef SEARCH_QUERY_STRING_H
#define SEARCH_QUERY_STRING_H

#include <string>

class query_string{
 public:
  query_string():str(""),pos(0){}
  query_string(const char* s):str(s),pos(0){}
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
  const char* get_str(){
    return str.c_str();
  }
  std::size_t get_pos(){
    //calculate pos
    return 0;
  }
 private:
  std::string str;
  std::size_t pos;
};

#endif
