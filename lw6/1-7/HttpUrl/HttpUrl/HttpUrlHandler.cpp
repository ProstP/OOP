#include "HttpUrlHandler.h"
#include <string>
#include "CHttpUrl.h"

const std::string EXIT_COMM = "...";

void HttpUrlHandler::Handle(std::istream& in, std::ostream& out)
{
	std::string line;
	while (std::getline(in, line))
	{
		if (line == EXIT_COMM)
		{
			break;
		}
		try
		{
			CHttpUrl url(line);
			out << "Url: " << url.GetURL() << "\n"
				<< "Protocol: " << url.GetProtocol() << "\n"
				<< "Domain: " << url.GetDomain() << "\n"
				<< "Port: " << url.GetPort() << "\n"
				<< "Document: " << url.GetDocument() << "\n\n";
		}
		catch (const std::exception& e)
		{
			out << e.what() << "\n\n";
		}
	}
}
