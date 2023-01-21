#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {

    std::vector<std::pair<std::future<std::vector<Entry>>, std::string>> vectorThread;

    for (const auto &text: input_docs) {
        docs.push_back(text);
    }

    for (const auto &text: input_docs) {
        std::istringstream iss(text);
        //Поиск уникальных слов
        do {
            std::string word;
            iss >> word;
            if (freq_dictionary.find(word) == freq_dictionary.end()) {
                //Создание потоков для обновления частотного словаря
                vectorThread.push_back(std::make_pair(std::async(&InvertedIndex::GetWordCount, this, word), word));
            }

        } while (iss);
    }
    for (auto &it: vectorThread) {
        freq_dictionary[it.second] = it.first.get();
    }
}


/** Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {

    std::vector<Entry> wordCount;
    int docNum = 0;

    for (const auto &text: docs) {
        std::string inWord;
        std::istringstream iss(text);
        bool wordFound = false;

        while (!iss.eof()) {
            iss >> inWord;

            //Обрезние ненужных символов
            while ((inWord.back() >= 32 && inWord.back() < 48) || (inWord.back() > 58 && inWord.back() < 64)) {
                inWord.pop_back();
            }

            //Подсчет количества заданного слова в документе
            if (inWord == word) {
                if (!wordFound) {
                    Entry tempEntry;
                    tempEntry.doc_id = docNum;
                    tempEntry.count += 1;
                    wordFound = true;
                    wordCount.push_back(tempEntry);
                } else {
                    wordCount.back().count++;
                }
            }
        }
        docNum++;

    }
    return wordCount;
};

int InvertedIndex::GetDocsSize() {
    return docs.size();
};


