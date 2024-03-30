#include "HTMLDecode.h"
#include <optional>
#include <map>

const std::map<std::string, char> CODING_PAIRS
{
	{"quot;", '"'},
	{"apos;", '\''},
	{"lt;", '<'},
	{"gt;", '>'},
	{"amp;", '&'}
};

std::string HtmlDecode(const std::string& html)
{
	std::string decoded;

	for (size_t i = 0; i < html.size(); i++)
	{
		if (html[i] == '&')
		{
			bool founded = false;
			for (const auto& [str, symbol] : CODING_PAIRS)
			{
				if (html.compare(i + 1, str.length(), str) == 0)
				{
					decoded += symbol;
					i += str.length();
					founded = true;
					break;
				}
			}
			if (founded)
			{
				continue;
			}
		}

		decoded += html[i];
	}

	return decoded;
}
