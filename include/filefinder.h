#ifndef FILEFINDER_H
#define FILEFINDER_H

#include <vector>
#include <string>

struct node{
  node(const std::string& fil, const std::string&  loc,int lev, bool id):
      filename(fil),location(loc),level(lev),is_dir(id){}
  std::string filename;
  std::string location;
  int level;
  bool is_dir;
};

void find_files(std::vector<node>&);

#endif
