#include "../include/hex_reader.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <string>

using std::vector;
using std::string;

vector<uint8_t> readRawBin(const string& path) {
  std::ifstream file(path, std::ios::binary);
  return vector<uint8_t>((std::istreambuf_iterator<char>(file)),
                          std::istreambuf_iterator<char>());
};

void printHex(const vector<uint8_t>& data) {
  for (size_t i = 0; i < data.size(); ++i) {
    if (i % 16 == 0) std::cout << std::endl;
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
  }
  std::cout << std::dec << std::endl;
};