#pragma once
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <sstream>

using namespace std;

struct Entry{
    size_t doc_id, count = 0;
// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

class InvertedIndex {
private:
    // частотный словарь
    std::map<std::string, std::vector<Entry>> freq_dictionary;
public:
    InvertedIndex() = default;
    // список содержимого документов
    std::vector<std::string> docs;
    void UpdateDocumentBase(std::vector<std::string> input_docs);
    std::vector<Entry> GetWordCount(const std::string& word);
    int GetDocsSize();
    friend class SearchServer;
};


