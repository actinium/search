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

program_options get_options(int argc, char* argv[]);

#endif
