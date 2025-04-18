#include "../include/hex_reader.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <cctype>

using std::vector;
using std::string;

vector<uint8_t> readRawBin(const string& path) {
  std::ifstream file(path, std::ios::binary);
  return vector<uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
};

void printHex(const vector<uint8_t>& data) {
  for (size_t i = 0; i < data.size(); ++i) {
    if (i % 16 == 0) 
      std::cout << std::endl;
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
  }
  std::cout << std::dec << std::endl;
};

void printStrings(const vector<uint8_t>& data) {
  string current;

  for (uint8_t byte : data) {
    if (byte == 0x00) {
      // Wen reach end of string, and not empty
      if (!current.empty()) {
        // Only prints printable strings
        bool printable = true;
        for (char c : current) {
          if (!std::isprint(c)) {
            printable = false;
            break;
          }
        }
        if (printable)
          std::cout << current << std::endl;
        current.clear();
      }
    } else {
      current += static_cast<char>(byte);
    }
  }
  // Handle remaining text
  if (!current.empty()) 
    std::cout << current << std::endl;
};
