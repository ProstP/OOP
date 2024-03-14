#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Translator/Dictionary.h"

SCENARIO("Load dictionary form file")
{
	WHEN("Filename is empty")
	{
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(LoadDictionaryFromFile(""), "Filename can not be empty");
		}
	}

	WHEN("Dictionary file not found")
	{
		THEN("Without exception, dictionary will be empty")
		{
			Dictionary dictionary = LoadDictionaryFromFile("Missing.txt");
			CHECK(dictionary.empty());
		}
	}

	WHEN("Dictionary file is empty")
	{
		THEN("Without exception, dictionary will be empty")
		{
			Dictionary dictionary = LoadDictionaryFromFile("Empty.txt");
			CHECK(dictionary.empty());
		}
	}

	WHEN("Dictionaty was found")
	{
		THEN("Dectionary will has values")
		{
			Dictionary dictionary = LoadDictionaryFromFile("Dictionary.txt");
			CHECK(dictionary.size() == 3);
		}
	}
}

SCENARIO("Translate word")
{
	Dictionary dictionary = LoadDictionaryFromFile("Dictionary.txt");
	WHEN("Word is empty")
	{
		THEN("We get null optional")
		{
			auto translate = TranslateWord(dictionary, "");
			CHECK(translate == std::nullopt);
		}
	}

	WHEN("Word exist in dictionary")
	{
		THEN("We get translate")
		{
			auto translate = TranslateWord(dictionary, "dog");
			CHECK(translate.value() == "собака");
		}
	}

	WHEN("Word not exists in dictionary")
	{
		THEN("We get null optional")
		{
			auto translate = TranslateWord(dictionary, "eeeeeeeeeee");
			CHECK(translate == std::nullopt);
		}
	}
}

SCENARIO("Save new word to dictionary")
{
	Dictionary dictionary = LoadDictionaryFromFile("Dictionary.txt");
	WHEN("Word is empty")
	{
		THEN("Size of dictionary not change")
		{
			SaveWordToDictionary(dictionary, "", "translate");
			CHECK(dictionary.size() == 3);
		}
	}

	WHEN("Translate is empty")
	{
		THEN("Size of dictionary not change")
		{
			SaveWordToDictionary(dictionary, "word", "");
			CHECK(dictionary.size() == 3);
		}
	}

	WHEN("Word and translate not empty")
	{
		THEN("Size of dictionary will increase by 1")
		{
			SaveWordToDictionary(dictionary, "word", "слово");
			CHECK(dictionary.size() == 4);
		}
	}
}

SCENARIO("Save dictionary to file")
{
	Dictionary dictionary = LoadDictionaryFromFile("Dictionary.txt");
	WHEN("Filename is empty")
	{
		THEN("Will be throw exception")
		{
			CHECK_THROWS_WITH(SaveDictionaryToFile(dictionary, ""), "File name can not be empty");
		}
	}

	WHEN("Save dictionary to file")
	{
		THEN("Save dictionary in file will be equal to load dictionary")
		{
			SaveDictionaryToFile(dictionary, "NewDictionary.txt");
			Dictionary newDictionary = LoadDictionaryFromFile("NewDictionary.txt");
			CHECK(dictionary == newDictionary);
		}
	}
}
