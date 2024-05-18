#include "CHttpUrl.h"
#include <map>
#include <regex>
#include <string>

namespace
{

const std::map<Protocol, unsigned short> PORT_FROM_PROTOCOL{
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 }
};
const std::map<Protocol, std::string> PROTOCOL_TO_STRING{
	{ Protocol::HTTP, "http" },
	{ Protocol::HTTPS, "https" }
};
const std::map<std::string, Protocol> STRING_TO_PROTOCOL{
	{ "http", Protocol::HTTP },
	{ "https", Protocol::HTTPS }
};
const unsigned short MAX_PORT_VALUE = 65535;
const unsigned short MIN_PORT_VALUE = 1;

const std::string PROTOCOL_REGEX_STR = "(https?)://";
const std::string DOMAIN_REGEX_STR = "([\\w-.,]+)";
const std::string PORT_REGEX_STR = "(?:\\:(\\d{1,5}))?";
const std::string DOCUMENT_REGEX_STR = "(\\S*)";

const std::regex URL_REGEX = std::regex("^" + PROTOCOL_REGEX_STR + DOMAIN_REGEX_STR + PORT_REGEX_STR + "(?:/" + DOCUMENT_REGEX_STR + ")?"
		+ "$",
	std::regex_constants::icase);
const std::regex DOMAIN_REGEX = std::regex("^" + DOMAIN_REGEX_STR + "$");
const std::regex DOCUMENT_REGEX = std::regex("^" + DOCUMENT_REGEX_STR + "$");

const std::string INVALID_URL = "Invalid Url.";
const std::string INVALID_DOMAIN = "Invalid domain. Domain can has letters and symbols: '-', '.', ','";
const std::string INVALID_PROTOCOL = "Invalid Protocol. Protocal must be http or https";
const std::string INVALID_PORT = "Invalid Port. Port must be between 1 and 65535";
const std::string INVALID_DOCUMENT = "Invalid document. Document can not has spaces";
} // namespace

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::smatch match;
	if (!std::regex_match(url, match, URL_REGEX))
	{
		throw CUrlParsingError(INVALID_URL);
	}

	m_protocol = GetProtocolByString(match[1]);
	m_domain = match[2];
	m_port = ParsePort(match[3]);
	m_document = "/";
	m_document += match[4];
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, PORT_FROM_PROTOCOL.at(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_protocol{ protocol }
{
	if (!IsDomainValid(domain))
	{
		throw std::invalid_argument(INVALID_DOMAIN);
	}
	m_domain = domain;
	if (!IsDocumentValid(document))
	{
		throw std::invalid_argument(INVALID_DOCUMENT);
	}
	if (document[0] != '/')
	{
		m_document = '/' + document;
	}
	else
	{
		m_document = document;
	}
	if (port < MIN_PORT_VALUE || port > MAX_PORT_VALUE)
	{
		throw std::invalid_argument(INVALID_PORT);
	}
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	std::string port = (m_port == PORT_FROM_PROTOCOL.at(m_protocol)) ? "" : ":" + std::to_string(m_port);
	return PROTOCOL_TO_STRING.at(m_protocol) + "://" + m_domain + port + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

bool CHttpUrl::IsDomainValid(const std::string& domain)
{
	std::smatch match;
	return (std::regex_match(domain, match, DOMAIN_REGEX));
}

bool CHttpUrl::IsDocumentValid(const std::string& document)
{
	std::smatch match;
	return (std::regex_match(document, match, DOCUMENT_REGEX)) || (document.empty());
}

Protocol CHttpUrl::GetProtocolByString(const std::string& str)
{
	std::string protocolStr = StrToLowerCase(str);
	if (STRING_TO_PROTOCOL.find(protocolStr) != STRING_TO_PROTOCOL.end())
	{
		return STRING_TO_PROTOCOL.at(protocolStr);
	}

	throw CUrlParsingError(INVALID_PROTOCOL);
}

unsigned short CHttpUrl::ParsePort(const std::string& portStr)
{
	if (portStr.empty())
	{
		return PORT_FROM_PROTOCOL.at(m_protocol);
	}
	int portValue;
	try
	{
		portValue = std::stoi(portStr);
	}
	catch (...)
	{
		throw CUrlParsingError(INVALID_PORT);
	}
	if (portValue > MAX_PORT_VALUE || portValue < MIN_PORT_VALUE)
	{
		throw CUrlParsingError(INVALID_PORT);
	}

	return portValue;
}

std::string CHttpUrl::StrToLowerCase(const std::string& str)
{
	std::string result;

	for (int i = 0; i < str.length(); i++)
	{
		result += tolower(str[i]);
	}

	return result;
}

std::ostream& operator<<(std::ostream& out, Protocol protocol)
{
	out << PROTOCOL_TO_STRING.at(protocol);
	return out;
}
