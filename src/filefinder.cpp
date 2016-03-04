#include "filefinder.h"
#include "options.h"

#if ! defined(_XOPEN_SOURCE) || _XOPEN_SOURCE < 600
#define _XOPEN_SOURCE 600       /* Get nftw() and S_IFSOCK declarations */
#endif
#include <ftw.h>

namespace{

std::vector<node> *nodes;

int dirTree(const char *pathname, const struct stat *, int type,
        struct FTW *ftwb){
  std::string filename(&pathname[ftwb->base]);
  if(filename == "."){
    return 0;
  }
  if(filename[0] != '.' || options.include_hidden){
    std::string location(pathname);
    location = location.substr(0,location.size()-filename.size());
    nodes->emplace_back(filename,location,ftwb->level, type == FTW_D);
    return 0;
  }else if(type != FTW_D){
    return 0;
  }else{
    return FTW_SKIP_SUBTREE;
  }
}

}

void find_files(std::vector<node>& ns){
  nodes = &ns;
  int flags = 0;
  if(nftw(".",dirTree,10,flags)== -1){
  }
}
