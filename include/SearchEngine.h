#pragma once
#include "InvertedIndex.h"
#include "ConverterJSON.h"
#include <vector>
#include <string>
#include <thread>
#include <sstream>
#include <iostream>

using namespace std;

class SearchServer {
private:
    InvertedIndex _index;
public:
    SearchServer(InvertedIndex& idx) : _index(idx){ };
    SearchServer() = default;
    ConverterJSON config;
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);
};



