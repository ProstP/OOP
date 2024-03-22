#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../URLParser/ParseURL.h"

SCENARIO("Parse url")
{
	std::string dummyHost;
	std::string dummyDocument;
	int dummyPort = 0;
	Protocol dummyProtocol = Protocol::HTTP;

	WHEN("Url is invalid")
	{
		THEN("False")
		{
			CHECK(!ParseURL("fsfsd", dummyProtocol, dummyPort, dummyHost, dummyDocument));
		}
	}

	WHEN("Host is empty")
	{
		THEN("False")
		{
			CHECK(!ParseURL("https://:9000/smt", dummyProtocol, dummyPort, dummyHost, dummyDocument));
		}
	}

	WHEN("Url is valid")
	{
		THEN("Valid host and empty document")
		{
			std::string host;
			std::string document;
			ParseURL("https://www.youtube.com", dummyProtocol, dummyPort, host, document);
			CHECK(host == "www.youtube.com");
			CHECK(document.empty());
		}
	}

	WHEN("Port length more then acceptable value length")
	{
		THEN("False")
		{
			CHECK(!ParseURL("https://localhost:65536/", dummyProtocol, dummyPort, dummyHost, dummyDocument));
		}
	}

	WHEN("Port more then acceptable value")
	{
		THEN("False")
		{
			CHECK(!ParseURL("https://localhost:65536/", dummyProtocol, dummyPort, dummyHost, dummyDocument));
		}
	}

	WHEN("Url with port")
	{
		THEN("Valid port")
		{
			int port;
			ParseURL("https://localhost:8000/", dummyProtocol, port, dummyHost, dummyDocument);
			CHECK(port == 8000);
		}
	}

	WHEN("Url with document")
	{
		THEN("Valid document")
		{
			std::string document;
			ParseURL("https://vk.com/feed", dummyProtocol, dummyPort, dummyHost, document);
			CHECK(document == "feed");
		}
	}

	WHEN("Url with port and document")
	{
		THEN("Valid parts")
		{
			int port;
			std::string host;
			std::string document;
			ParseURL("https://localhost:3301/post/1", dummyProtocol, port, host, document);
			CHECK(port == 3301);
			CHECK(host == "localhost");
			CHECK(document == "post/1");
		}
	}

	WHEN("Invalid protocol")
	{
		THEN("False")
		{
			CHECK(!ParseURL("protocol://www.youtube.com", dummyProtocol, dummyPort, dummyHost, dummyDocument));
		}
	}

	WHEN("Https protocol")
	{
		THEN("Valid protocol and port")
		{
			Protocol protocol;
			int port;
			ParseURL("https://www.youtube.com", protocol, port, dummyHost, dummyDocument);
			CHECK(protocol == Protocol::HTTPS);
			CHECK(port == 443);
		}
	}

	WHEN("Http protocol")
	{
		THEN("Valid protocol and port")
		{
			Protocol protocol;
			int port;
			ParseURL("http://www.youtube.com", protocol, port, dummyHost, dummyDocument);
			CHECK(protocol == Protocol::HTTP);
			CHECK(port == 80);
		}
	}

	WHEN("Ftp protocol")
	{
		THEN("Valid protocol and port")
		{
			Protocol protocol;
			int port;
			ParseURL("ftp://www.youtube.com", protocol, port, dummyHost, dummyDocument);
			CHECK(protocol == Protocol::FTP);
			CHECK(port == 21);
		}
	}

	WHEN("Https protocol in different register")
	{
		THEN("Valid protocol and port")
		{
			Protocol protocol;
			int port;
			ParseURL("HtTpS://www.youtube.com", protocol, port, dummyHost, dummyDocument);
			CHECK(protocol == Protocol::HTTPS);
			CHECK(port == 443);
		}
	}

	WHEN("Http protocol in different register")
	{
		THEN("Valid protocol and port")
		{
			Protocol protocol;
			int port;
			ParseURL("HtTP://www.youtube.com", protocol, port, dummyHost, dummyDocument);
			CHECK(protocol == Protocol::HTTP);
			CHECK(port == 80);
		}
	}

	WHEN("Ftp protocol in different register")
	{
		THEN("Valid protocol and port")
		{
			Protocol protocol;
			int port;
			ParseURL("FtP://www.youtube.com", protocol, port, dummyHost, dummyDocument);
			CHECK(protocol == Protocol::FTP);
			CHECK(port == 21);
		}
	}
}