#include "SearchEngine.h"


/**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/


/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> relativeFreq;
    int responsesLimit = config.GetResponsesLimit();

    for (const auto &word: queries_input) {
        //Поиск уникальных слов в запросе
        std::vector<std::pair<std::string, int>> unique_queries;
        bool unique_found = true;
        std::string tempString;
        std::istringstream iss(word);

        do {
            iss >> tempString;
            if (!unique_queries.empty()) {
                for (const auto& it: unique_queries) {
                    if (tempString == it.first) {
                        unique_found = false;
                        break;
                    }
                }
            }

            //Количество совпадений в документах
            if (unique_found) {
                int temp = 0;
                if (_index.freq_dictionary.find(tempString) != _index.freq_dictionary.end()) {
                    for (auto it: _index.freq_dictionary[tempString]) {
                        temp += it.count;
                    }
                }
                unique_queries.push_back(std::make_pair(tempString, temp));
            }

        } while (!iss.eof());

        //Сортировка слов в запросе от самых редких до частых
        for (int i = 0; i < unique_queries.size(); i++) {
            for (int j = 0; j < unique_queries.size() - 1 - j; j++) {
                if (unique_queries[j].second > unique_queries[j + 1].second) {
                    auto temp = unique_queries[j + 1];
                    unique_queries[j + 1] = unique_queries[j];
                    unique_queries[j] = temp;
                }
            }
        }

        int absoluteFreq = 0; //Максимальное число совпадений

        std::vector<RelativeIndex> pushbackVector; //Временная переменнаая, содержащая индексы запроса
        for (int docNum = 0; docNum < _index.GetDocsSize(); docNum++) {
            int temp = 0;
            for (const auto &wordUnique: unique_queries) {
                for (auto it: _index.freq_dictionary[wordUnique.first]) {
                    if (it.doc_id == docNum)
                        temp += it.count;
                }
            }

            if (temp > absoluteFreq)
                absoluteFreq = temp;

            //Добавление только тех резульатов, в которых было совпадение
            if (temp != 0) {
                RelativeIndex tempPushback(docNum, temp);
                pushbackVector.push_back(tempPushback);
            }


        }

        relativeFreq.push_back(pushbackVector);

        //Перевод результатов в десятичный вид
        if (absoluteFreq) {
            for (int i = 0; i < relativeFreq.back().size(); i++) {
                relativeFreq.back()[i].rank /= absoluteFreq;
            }

            //Сортировка индекса встречаемости по возврастанию
            for (int i = 0; i < relativeFreq.back().size(); i++) {
                for (int j = 0; j < relativeFreq.back().size() - 1 - i; j++) {
                    if (relativeFreq.back()[j].rank < relativeFreq.back()[j + 1].rank) {
                        auto temp = relativeFreq.back()[j + 1];
                        relativeFreq.back()[j + 1] = relativeFreq.back()[j];
                        relativeFreq.back()[j] = temp;
                    }
                }
            }
            //Обрезка результатов по максимальному число ответов из config.json
            if (relativeFreq.back().size() > responsesLimit) {
                for (; responsesLimit < relativeFreq.back().size();) {
                    relativeFreq.back().pop_back();
                }
            }
        }

    }
    stringResult.clear();
    for (const auto &x: relativeFreq) {
        for (auto y: x) {
            stringResult = stringResult + "DocId: " + std::to_string(y.doc_id) + " Rank: " + std::to_string(y.rank) + "\n";
           // std::cout << stringResult;
           // std::cout << "DocId: " <<  y.doc_id << " Rank: " << y.rank << std::endl;
        }
    }
    return relativeFreq;
};

