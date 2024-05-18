#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../HttpUrl/CHttpUrl.h"

TEST_CASE("Creating CHttpUrl by Protocol, domain, port and document")
{
	WHEN("All fields ok")
	{
		CHttpUrl url("domain", "/some-document", Protocol::HTTP, 8000);
		THEN("Will create class and fields will true")
		{
			CHECK(url.GetURL() == "http://domain:8000/some-document");
			CHECK(url.GetDomain() == "domain");
			CHECK(url.GetDocument() == "/some-document");
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetPort() == 8000);
		}
	}

	WHEN("Document without /")
	{
		CHttpUrl url("domain", "some-document", Protocol::HTTP, 8000);
		THEN("Will create class and fields will true")
		{
			CHECK(url.GetURL() == "http://domain:8000/some-document");
			CHECK(url.GetDocument() == "/some-document");
		}
	}

	WHEN("Document empty")
	{
		CHttpUrl url("domain", "", Protocol::HTTP, 8000);
		THEN("Will create class and fields will true")
		{
			CHECK(url.GetURL() == "http://domain:8000/");
			CHECK(url.GetDocument() == "/");
		}
	}

	WHEN("Port = default port of protocol")
	{
		CHttpUrl url("domain", "some-document", Protocol::HTTP, 80);
		THEN("Url without port")
		{
			CHECK(url.GetURL() == "http://domain/some-document");
			CHECK(url.GetPort() == 80);
		}
	}

	WHEN("Port < min port value")
	{
		THEN("Will trow invalid_argument exception")
		{
			CHECK_THROWS_AS(CHttpUrl("dom", "/doc", Protocol::HTTP, 0), std::invalid_argument);
		}
	}

	WHEN("Document has space")
	{
		THEN("Will trow invalid_argument exception")
		{
			CHECK_THROWS_AS(CHttpUrl("dom", "/do c", Protocol::HTTP, 15), std::invalid_argument);
		}
	}
}

TEST_CASE("Creating CHttpUrl by Protocol, domain and document")
{
	WHEN("Protocol Https")
	{
		CHttpUrl url("domain", "/document", Protocol::HTTPS);
		THEN("Port == 443")
		{
			CHECK(url.GetURL() == "https://domain/document");
			CHECK(url.GetPort() == 443);
		}
	}

	WHEN("Protocol Http")
	{
		CHttpUrl url("domain", "/document", Protocol::HTTP);
		THEN("Port == 80")
		{
			CHECK(url.GetURL() == "http://domain/document");
			CHECK(url.GetPort() == 80);
		}
	}
}

TEST_CASE("Create CHttpUrl by url")
{
	WHEN("Url full with http protocol")
	{
		CHttpUrl url("http://domain:8000/some-document");
		THEN("Fields be right")
		{
			CHECK(url.GetURL() == "http://domain:8000/some-document");
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetDomain() == "domain");
			CHECK(url.GetPort() == 8000);
			CHECK(url.GetDocument() == "/some-document");
		}
	}

	WHEN("Url full with https protocol")
	{
		CHttpUrl url("https://domain:8000/some-document");
		THEN("Fields be right")
		{
			CHECK(url.GetURL() == "https://domain:8000/some-document");
			CHECK(url.GetProtocol() == Protocol::HTTPS);
			CHECK(url.GetDomain() == "domain");
			CHECK(url.GetPort() == 8000);
			CHECK(url.GetDocument() == "/some-document");
		}
	}

	WHEN("Url full with https protocol in upper case")
	{
		CHttpUrl url("HTTPS://domain:8000/some-document");
		THEN("Fields be right")
		{
			CHECK(url.GetURL() == "https://domain:8000/some-document");
			CHECK(url.GetProtocol() == Protocol::HTTPS);
		}
	}

	WHEN("Url full with http protocol in upper case")
	{
		CHttpUrl url("HTTP://domain:8000/some-document");
		THEN("Fields be right")
		{
			CHECK(url.GetURL() == "http://domain:8000/some-document");
			CHECK(url.GetProtocol() == Protocol::HTTP);
		}
	}

	WHEN("Url full without port")
	{
		CHttpUrl url("https://domain/some-document");
		THEN("Fields be right, port will get by protocol")
		{
			CHECK(url.GetURL() == "https://domain/some-document");
			CHECK(url.GetProtocol() == Protocol::HTTPS);
			CHECK(url.GetDomain() == "domain");
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDocument() == "/some-document");
		}
	}

	WHEN("Url full without document")
	{
		CHttpUrl url("https://domain:8000");
		THEN("Fields be right, document = /")
		{
			CHECK(url.GetURL() == "https://domain:8000/");
			CHECK(url.GetProtocol() == Protocol::HTTPS);
			CHECK(url.GetDomain() == "domain");
			CHECK(url.GetPort() == 8000);
			CHECK(url.GetDocument() == "/");
		}
	}

	WHEN("Url full without document and port")
	{
		CHttpUrl url("https://domain");
		THEN("Fields be right, port will get by protocol, document = /")
		{
			CHECK(url.GetURL() == "https://domain/");
			CHECK(url.GetProtocol() == Protocol::HTTPS);
			CHECK(url.GetDomain() == "domain");
			CHECK(url.GetPort() == 443);
			CHECK(url.GetDocument() == "/");
		}
	}

	WHEN("String not url")
	{
		THEN("Will be trow exception CUtlParsingError type")
		{
			CHECK_THROWS_AS(CHttpUrl("It is not url"), CUrlParsingError);
		}
	}

	WHEN("Url has invalid symbols between protocol and domain")
	{
		THEN("Will be trow exception CUtlParsingError type")
		{
			CHECK_THROWS_AS(CHttpUrl("http:/dfsdf/domain:8000/some-document"), CUrlParsingError);
		}
	}

	WHEN("Protocol is invalid")
	{
		THEN("Will be trow exception CUtlParsingError type")
		{
			CHECK_THROWS_AS(CHttpUrl("protocol://domain:8000/some-document"), CUrlParsingError);
		}
	}

	WHEN("Domain is invalid")
	{
		THEN("Will be trow exception CUtlParsingError type")
		{
			CHECK_THROWS_AS(CHttpUrl("http://dom:ain:8000/some-document"), CUrlParsingError);
		}
	}

	WHEN("Port length > length of max port value")
	{
		THEN("Will be trow exception CUtlParsingError type")
		{
			CHECK_THROWS_AS(CHttpUrl("http://domain:800000/some-document"), CUrlParsingError);
		}
	}

	WHEN("Port length = length of max port value, port value > max port value")
	{
		THEN("Will be trow exception CUtlParsingError type")
		{
			CHECK_THROWS_AS(CHttpUrl("http://domain:80000/some-document"), CUrlParsingError);
		}
	}

	WHEN("Document has space")
	{
		THEN("Will be trow exception CUtlParsingError type")
		{
			CHECK_THROWS_AS(CHttpUrl("http://domain:8000/some document"), CUrlParsingError);
		}
	}
}
