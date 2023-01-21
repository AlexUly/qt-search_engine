#include "ConverterJSON.h"


/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
std::vector<std::string> ConverterJSON::GetTextDocuments(std::string path) {
    std::vector<std::string> textDocuments;
    nlohmann::json config;

    std::ifstream fileConfig(path);

    try{
        fileConfig >> config;
    } catch(std::exception &x){
        std::cerr << "Error opening config.json" << x.what() << std::endl;
    }

    if(config["files"].empty()){
        std::cerr <<"JSON files name syntax error" <<  std::endl;
    }

    if(config["config"]["name"].empty()){
        std::cerr << "JSON engine name syntax error" << std::endl;
    }

    if(config["config"]["version"].empty()) {
        std::cerr << "JSON version syntax error" << std::endl;
    }

    std::cout << "Engine name: ";
    std::cout << config["config"]["name"] << std::endl;
    std::cout  << "Version: ";
    std::cout << config["config"]["name"] << std::endl;

            for (auto it = config["files"].begin(); it != config["files"].end(); it++) {
                if (!it.value().empty()) {
                    std::string tempPath = to_string(it.value());

                    if (tempPath.length() > 3) {
                        tempPath = tempPath.substr(1, tempPath.size() - 2);
                        tempPath = "files/" + tempPath;
                    }

                    std::ifstream fileText(tempPath);
                    if (fileText.is_open()) {
                        if (fileText.is_open()) {
                            std::ostringstream ss;
                            std::string temp;
                            ss << fileText.rdbuf();
                            temp = ss.str();
                            textDocuments.push_back(temp);
                            fileText.close();
                        }
                    } else {
                        std::cerr << "Error opening " << tempPath << std::endl;
                    }
                }
            }

        //Вывод версии, названия и количество максимальных запросов в консоль
        if (!config["config"]["max_responses"].empty()) {
            responseLimit = config["config"]["max_responses"];
        } else {
            std::perror("JSON max responses syntax error, setting default value");
        }


    fileConfig.close();
    return textDocuments;
}

/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/

int ConverterJSON::GetResponsesLimit() const {
    return responseLimit;
}

/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
std::vector<std::string> ConverterJSON::GetRequests(std::string path) {
    std::vector<std::string> requests;
    std::ifstream requestsJson;
    nlohmann::json config;
    requestsJson.open(path);

    try{
        requestsJson >> config;
    } catch (std::exception &x){
        std::cerr <<"Error opening requests.json" << x.what() << std::endl;
    }

    if(config["requests"].empty()){
        std::cerr << "JSON requests syntax error" << std::endl;
    }

        for (const auto& it: config["requests"]) {
                requests.push_back(it);
            }

    requestsJson.close();
    return requests;
}

/**
* Положить в файл answers.json результаты поисковых запросов
*/
void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers) {
    std::ofstream answersPath("json/answers.json");

    if(!answersPath.is_open()){
        std::cerr << "Error opening answers.json" << std::endl;
    }

        nlohmann::json answersJson;
        int i = 1;
        for (const auto& it: answers) {
            if (it.size() < 1) {
                answersJson["answers"]["request" + std::to_string(i)]["result"].push_back(true);
                int rankNum = 0;
                for (auto ij: answers[rankNum]) {
                    answersJson["answers"]["request" + std::to_string(i)]["relevance"]["docId" + std::to_string(
                            rankNum)].push_back(ij.doc_id);
                    answersJson["answers"]["request" + std::to_string(i)]["relevance"]["rank" +
                                                                                       std::to_string(
                                                                                               rankNum)].push_back(
                            ij.rank);
                    rankNum++;
                }
            } else {
                answersJson["answers"]["request" + std::to_string(i)]["result"].push_back(false);
                answersPath << std::endl;
            }
            i++;
        }
        answersPath << std::setw(4) << answersJson << std::endl;

    answersPath.close();
}

