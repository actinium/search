#ifndef SEARCH_OPTIONS_H
#define SEARCH_OPTIONS_H

struct program_options{
  bool show_help;
  bool show_version;
  bool include_hidden_files;
  bool files_only;
  bool directories_only;
  int  number_of_result_lines;
};

extern program_options options;

void get_options(int argc, char* argv[]);

#endif
