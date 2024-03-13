#pragma once
#include <iostream>
#include <map>
#include <optional>

using Dictionary = std::map<std::string, std::string>;

Dictionary LoadDictionaryFromFile(const std::string& fileName);

std::optional<std::string> TranslateWord(const Dictionary& dictionary, const std::string& word);

void SaveWordToDictionary(Dictionary& dictionary, const std::string& word, const std::string& translate);

void SaveDictionaryToFile(const Dictionary& dictionary, const std::string& fileName);
