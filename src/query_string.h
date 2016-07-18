#ifndef SEARCH_QUERY_STRING_H
#define SEARCH_QUERY_STRING_H

#include <cstring>
#include <string>

class query_string{
 public:
  query_string():str(""),pos(0){}
  query_string(const char* s):str(s),pos(strlen(s)){}
  void add(char c){
    str.insert(pos, 1, c);
    pos++;
  }
  void remove(){
    // TODO: remove multibyte utf8 character
    if(pos > 0){
      str.erase(pos-1,1);
      pos--;
    }
  }
  bool cursor_left(){
    // TODO: move to next utf8 character
    if(pos > 0){
      pos--;
      return true;
    }
    return false;
  }
  bool cursor_right(){
    // TODO: move to next utf8 character
    if(pos < str.length()){
      pos++;
      return true;
    }
    return false;
  }
  bool is_part_of(std::string lowercase_filename){
    std::string lowercase_str = str;
    return lowercase_filename.find(lowercase_str) != std::string::npos;
  }
  const char* get_str(){
    return str.c_str();
  }
  std::size_t get_pos(){
    // TODO: calculate ut8 pos
    return pos;
  }
 private:
  std::string str;
  std::size_t pos;
};

#endif