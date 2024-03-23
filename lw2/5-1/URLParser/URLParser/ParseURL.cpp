#include "ParseURL.h"
#include <regex>
#include <map>

const std::map<std::string, Protocol> STRING_TO_PROTOCOL
{
	{"http", Protocol::HTTP},
	{"https", Protocol::HTTPS},
	{"ftp", Protocol::FTP}
};

const std::map<Protocol, int> DEFAULT_PORT
{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443},
	{Protocol::FTP, 21}
};

bool CheckUrl(const std::string& url)
{
	const std::regex pattern("^([hH][tT][tT][pP][sS]?|[fF][tT][pP])://[\\w-.,]+(:\\d{1,5})?(/[\\w-.,/]+)?/?$");

	if (!std::regex_match(url, pattern))
	{
		return false;
	}

	return true;
}

void StringToLower(std::string& str)
{
	for (char& c : str)
	{
		c = tolower(c);
	}
}

void GetProtocol(const std::string& url, Protocol& protocol)
{
	const std::regex pattern("^([hH][tT][tT][pP][sS]?|[fF][tT][pP])");
	std::smatch match;

	std::regex_search(url, match, pattern);

	std::string protocolStr = match[0].str();
	StringToLower(protocolStr);
	protocol = STRING_TO_PROTOCOL.at(protocolStr);
}

bool GetPort(const std::string& url, int& port)
{
	const std::regex portPattern(":\\d+");
	std::smatch portMatch;
	if (!std::regex_search(url, portMatch, portPattern))
	{
		return false;
	}
	std::string	portStr = portMatch[0].str();
	std::string digitsStr = portStr.substr(1, portStr.length() - 1);

	port = std::stoi(digitsStr);
	return true;
}

std::string GetHost(const std::string& url)
{	
	const std::regex hostPattern("://[\\w-.,]+");
	std::smatch hostMatch;
	std::regex_search(url, hostMatch, hostPattern);
	std::string partWithHost = hostMatch[0].str();
	return partWithHost.substr(3, partWithHost.length() - 3);
}

std::string GetDocument(const std::string& url)
{
	const std::regex documentPattern("[\\w-.,]/[\\w-.,/]+");
	std::smatch documentMatch;
	if (!std::regex_search(url, documentMatch, documentPattern))
	{
		return "";
	}
	std::string document = documentMatch[0].str();
	return document.substr(2, document.length() - 2);
}

void ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	if (!CheckUrl(url))
	{
		throw std::runtime_error("Received string is not url");
	}
	
	GetProtocol(url, protocol);
	if (!GetPort(url, port))
	{
		port = DEFAULT_PORT.at(protocol);
	}
	const int maxPortValue = 65535;
	if (port > maxPortValue)
	{
		throw std::runtime_error("Port more then max acceptable port value");
	}

	host = GetHost(url);
	document = GetDocument(url);
}
