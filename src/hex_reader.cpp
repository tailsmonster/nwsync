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

void debugEntryBlock(const vector<uint8_t>& data, size_t start, size_t length) {
  std::cout << "Block at offset " << start << ":" << std::endl;

  for (size_t i = 0; i < length; ++i) {
      if (i % 16 == 0) std::cout << std::endl;

      // Print hex
      std::cout << std::hex << std::setw(2) << std::setfill('0')
                << static_cast<int>(data[start + i]) << " ";
  }

  std::cout << "\n\nASCII:" << std::endl;

  for (size_t i = 0; i < length; ++i) {
      char c = static_cast<char>(data[start + i]);
      if (std::isprint(c)) std::cout << c;
      else std::cout << '.';
  }

  std::cout << "\n\n" << std::dec;
}

void extractEntries(const vector<uint8_t>& data, size_t entryLength) {
  string currentString;

  for (size_t i = 0; i < data.size(); ++i) {
    uint8_t byte = data[i];

    if (byte == 0x00) {
      if (!currentString.empty()) {
        if (currentString.rfind("A:\\OMGAUDIO\\", 0) == 0 && currentString.find(".DAT") != string::npos)
          std::cout << "Extracted file path: " << currentString << std::endl;
        currentString.clear();
      }
    } else {
      currentString += static_cast<char>(byte);
    }
  }

  // Catch any leftover string at the end
  if (!currentString.empty()) {
      if (currentString.rfind("A:\\OMGAUDIO\\", 0) == 0 && currentString.find(".DAT") != string::npos) {
          std::cout << "Extracted file path: " << currentString << std::endl;
      }
  }
}

