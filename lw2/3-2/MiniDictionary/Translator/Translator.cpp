﻿#include "Dictionary.h"
#include <Windows.h>
#include <iostream>
#include <string>

std::string ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::runtime_error("Invalid arguments count\nUsage: Translator.exe <dictionary file name>\n");
	}

	return argv[1];
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const std::string exitWord = "...";

	try
	{
		bool isChanged = false;
		std::string dictionaryFileName = ParseArgs(argc, argv);
		Dictionary dictionary = LoadDictionaryFromFile(dictionaryFileName);

		std::string word;
		while (std::getline(std::cin, word))
		{
			if (word == exitWord)
			{
				if (isChanged)
				{
					std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
					std::getline(std::cin, word);
					if (word == "Y" || word == "y")
					{
						SaveDictionaryToFile(dictionary, dictionaryFileName);
						std::cout << "Изменения сохранены.\n";
					}
					else
					{
						std::cout << "Изменения не были сохранены.\n";
					}
				}
				std::cout << "До свидания.\n";
				break;
			}

			auto translate = TranslateWord(dictionary, word);
			if (!translate)
			{
				std::cout << "Неизвестное слово \"" + word + "\". Введите перевод или пустую строку для отказа.\n";
				std::string translate;
				std::getline(std::cin, translate);
				if (!translate.empty())
				{
					SaveWordToDictionary(dictionary, word, translate);
					isChanged = true;
					std::cout << "Слово \'" << word << "\" сохранено как \"" << translate << "\"\n";
				}
				else
				{
					std::cout << "Слово " + word + " проигноринованно\n";
				}
			}
			else
			{
				std::cout << translate.value() << "\n";
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}

	return 0;
}
