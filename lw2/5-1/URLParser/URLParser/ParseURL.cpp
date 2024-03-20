#include "ParseURL.h"
#include <regex>
#include <map>

const std::map<Protocol, int> DEFAULT_PORT
{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443},
	{Protocol::FTP, 21}
};

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	const std::regex pattern("^(http|https|ftp):\/\/\[^\s]+(:[1-65535])*(\/[^\s])*");

	std::smatch substr;

	if (std::regex_match(url, pattern))
	{
		host = substr[0].str();
		return true;
	}

	return false;
}
