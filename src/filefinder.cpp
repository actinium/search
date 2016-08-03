#include "filefinder.h"

#if ! defined(_XOPEN_SOURCE) || _XOPEN_SOURCE < 600
#define _XOPEN_SOURCE 600       /* Get nftw() and S_IFSOCK declarations */
#endif
#include <ftw.h>

#include <string>

#include "options.h"

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
    if( (options.files_only && type != FTW_D) ||
       (options.directories_only && type == FTW_D) ||
       (!options.files_only && !options.directories_only) ){
      nodes->emplace_back(filename,location,ftwb->level, type == FTW_D);
    }
    return 0;
  }else if(type != FTW_D){
    return 0;
  }else{
    return FTW_SKIP_SUBTREE;
  }
}

}

std::vector<node> files = std::vector<node>{};

void find_files(std::vector<node>& ns){
  nodes = &ns;
  int flags = FTW_ACTIONRETVAL;
  if(nftw(options.search_dir.c_str(),dirTree,10,flags)== -1){
    // TODO
  }
}

std::vector<node> search(const query_string& qstr){
  std::vector<node> result;

  if( !qstr.is_empty() ){
    int count = 1;
    for(std::size_t i=0; i < files.size() && count <=options.number_of_result_lines; ++i){
      if(qstr.is_part_of(files[i].lowercase_filename)){
        result.push_back(files[i]);
        count++;
      }
    }
  }

  return result;
}
