#ifndef SEARCH_QUERY_STRING_H
#define SEARCH_QUERY_STRING_H

#include <string>

class query_string{
 public:
  query_string(const char* s):str(s){}
  const char* get_str(){
    return str.c_str();
  }
 private:
  std::string str;
};

#endif
