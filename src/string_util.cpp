#include "string_util.h"

#include <unicode/unistr.h>
#include <unicode/ustream.h>
#include <unicode/locid.h>

std::string to_lowercase(std::string str){
  icu::UnicodeString someUString(str.c_str());
  std::string return_string;
  someUString.toLower().toUTF8String(return_string);
  return return_string;
}
