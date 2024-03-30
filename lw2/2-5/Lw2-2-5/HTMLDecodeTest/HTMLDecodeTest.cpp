#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../../../catch.hpp"
#include "../HTMLDecoder/HTMLDecode.h"

SCENARIO("Decode html string")
{
	WHEN("Html is empty")
	{
		std::string html = "";

		THEN("Decoded string is empty")
		{
			std::string decodedString = HtmlDecode(html);
			CHECK(decodedString.empty());
		}
	}

	WHEN("Html don't has special substr")
	{
		std::string html = "It is html string without special substr";

		THEN("Decoded string equal html")
		{
			std::string decoded = HtmlDecode(html);
			CHECK(decoded == html);
		}
	}

	WHEN("Html has specail substr")
	{
		std::string html = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		THEN("Specail substr will be decoded to symbols")
		{
			std::string decoded = HtmlDecode(html);
			CHECK(decoded == "Cat <says> \"Meow\". M&M's");
		}
	}

	WHEN("Specail substr not full")
	{
		std::string html = "Cat &ltsays&gt &quotMeow&quot. M&ampM&aposs";
		THEN("Specail substr will not decoded to symbols")
		{
			std::string decoded = HtmlDecode(html);
			CHECK(decoded == "Cat &ltsays&gt &quotMeow&quot. M&ampM&aposs");
		}
	}
}
