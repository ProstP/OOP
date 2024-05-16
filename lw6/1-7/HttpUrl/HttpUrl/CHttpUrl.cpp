#include "CHttpUrl.h"
#include <map>
#include <string>
#include <regex>

const std::map<Protocol, unsigned short> PORT_FROM_PROTOCOL
{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443}
};
const std::map<Protocol, std::string> PROTOCOL_TO_STRING
{
	{Protocol::HTTP, "http"},
	{Protocol::HTTPS, "https"}
};
const unsigned short MAX_PORT_VALUE = 65535;
const unsigned short MIN_PORT_VALUE = 1;

const std::string DOMAIN_REGEX_STR = "[\\w-.,]";
const std::string DOCUMENT_REGEX_STR = "\\.*";
const std::regex DOMAIN_REGEX = std::regex(DOMAIN_REGEX_STR);
const std::regex DOCUMENT_REGEX = std::regex(DOCUMENT_REGEX_STR);

CHttpUrl::CHttpUrl(std::string const& url)
{
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
		throw std::invalid_argument("Invalid domain. Domain must contain only english letters, digits, '-', ',', '.'");
	}
	m_domain = domain;
	if (!IsDocumentValid(document))
	{
		throw std::invalid_argument("Invalid document. Document can not has space");
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
		throw std::invalid_argument("Port has invalid value, port must be >= 1 and <= 65535");
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
	return !(std::regex_match(domain, match, DOMAIN_REGEX));
}

bool CHttpUrl::IsDocumentValid(const std::string& document)
{
	std::smatch match;
	return !(std::regex_match(document, match, DOCUMENT_REGEX)) || (document.empty());
}

Protocol CHttpUrl::GetProtocolByString(const std::string& str)
{
	if (str == "https")
	{
		return Protocol::HTTPS;
	}

	if (str == "http")
	{
		return Protocol::HTTP;
	}

	throw CUrlParsingError::InvalidProtocol();
}
