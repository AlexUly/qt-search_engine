#include "ConverterJSON.h"
#include "gtest/gtest.h"

TEST(ConverterJSON, readConfig) {
    ConverterJSON config;
    std::vector<std::string> expected = {"milk milk milk milk water water water",
                                         "milk water water",
                                         "milk milk milk milk milk water water water water water",
                                         "americano cappuccino"};
    std::vector<std::string> result = config.GetTextDocuments("config.json");
    ASSERT_EQ(result, expected);
}

TEST(ConverterJSON, readRequests) {
    ConverterJSON config;
    std::vector<std::string> expected = {"milk water",
                                         "sugar"};
    std::vector<std::string> result = config.GetRequests("requests.json");
    ASSERT_EQ(result, expected);
}

