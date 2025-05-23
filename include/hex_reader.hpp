#pragma once 

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdint>

using std::vector;
using std::string;

vector<uint8_t> readRawBin(const string& path);

void printHex(const vector<uint8_t>& data);

void printStrings(const vector<uint8_t>& data);

void extractEntries(const vector<uint8_t>& data, size_t entryLength = 64);