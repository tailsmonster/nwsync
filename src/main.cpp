#include "../include/hex_reader.hpp"
#include "../include/files_utils.hpp"
#include <iostream>
#include <vector>
#include <string>

using std::string;

int main() {
  string path = "data/TSTMPTBL.DAT";

  if (!fileExists(path)) {
      std::cerr << "File not found: " << path << '\n';
      return 1;
  }

  auto data = readRawBin(path);
  if (!data.empty()) {
      std::cout << "Hex dump of: " << path << "\n";
      printHex(data);
  }

  return 0;
}