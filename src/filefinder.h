#ifndef FILEFINDER_H
#define FILEFINDER_H

#include <string>
#include <vector>

#include "string_util.h"

struct node{
  node(const std::string& fil, const std::string&  loc,int lev, bool id):
      filename(fil),lowercase_filename(fil),location(loc),level(lev),is_dir(id){
    lowercase_filename = to_lowercase(filename);
  }
  std::string filename;
  std::string lowercase_filename;
  std::string location;
  int level;
  bool is_dir;
};

void find_files(std::vector<node>&);

#endif
