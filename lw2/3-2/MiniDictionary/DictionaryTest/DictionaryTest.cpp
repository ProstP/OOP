#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../Translator/Dictionary.h"

SCENARIO("Load dictionary form file")
{
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

}
