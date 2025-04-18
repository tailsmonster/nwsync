#include "../include/files_utils.hpp"
#include <iostream>
#include <string>
#include <filesystem>

using std::string;

bool fileExists(const string& path) {
  return std::filesystem::exists(path);
};