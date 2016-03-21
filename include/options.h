#ifndef SEARCH_OPTIONS_H
#define SEARCH_OPTIONS_H

#include <string>

struct program_options{
  std::string search_dir;
  bool show_help;
  bool show_version;
  bool include_hidden;
  bool files_only;
  bool directories_only;
  int  number_of_result_lines;
};

extern program_options options;

bool get_options(int argc, char* argv[]);

void print_version();

void print_help();

#endif
