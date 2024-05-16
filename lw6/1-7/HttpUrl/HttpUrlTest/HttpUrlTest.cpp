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
			CHECK_THROWS_AS(CHttpUrl("dom", "/do c", Protocol::HTTP, 0), std::invalid_argument);
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
