#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

struct RelativeIndex{
    size_t doc_id;
    float rank;
    RelativeIndex(int docN, float rel){
        doc_id = docN;
        rank = rel;
    }
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class ConverterJSON {
public:
    int responseLimit = 5;
    std::string engineName;
    std::string engineVersion;
    ConverterJSON() = default;
    std::vector<std::string> GetTextDocuments(std::string path);
    int GetResponsesLimit() const;
    static std::vector<std::string> GetRequests(std::string path);
    std::vector<std::string> GetRequestsFromGUI(std::string);
    void putAnswers(std::vector<std::vector<RelativeIndex>> answers);
};

