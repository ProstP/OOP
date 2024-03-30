#include <fstream>
#include <iostream>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::runtime_error("Invalid aruments count\nUsage: Replace.exe <input file name> <output file name> <search string> <replace string>\n");
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

std::string ReplaceStringsInLine(const std::string& line, const std::string& search, const std::string& replace)
{
	if (line.empty() || search.empty())
	{
		return line;
	}

	std::string replacedLine;
	size_t pos = 0;
	while (pos < line.length())
	{
		size_t foundPos = line.find(search, pos);
		replacedLine.append(line, pos, foundPos - pos);
		if (foundPos == std::string::npos)
		{
			break;
		}
		replacedLine.append(replace);
		pos = foundPos + search.length();
	}

	return replacedLine;
}

void CopyAndReplaceStringsInStreams(std::ifstream& inFile, std::ofstream& outFile, const std::string& search, const std::string& replace)
{
	std::string inputLine;
	while (std::getline(inFile, inputLine))
	{
		std::string replacedLine = ReplaceStringsInLine(inputLine, search, replace);
		outFile << replacedLine << "\n";
	}
}

void CopyAndReplaceStringsInFiles(
	const std::string& inputFileName,
	const std::string& outputFileName,
	const std::string& search,
	const std::string& replace)
{
	std::ifstream inFile;
	inFile.open(inputFileName);
	if (!inFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFileName + " for reading\n");
	}
	std::ofstream outFile;
	outFile.open(outputFileName);
	if (!outFile.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFileName + " for writing\n");
	}

	CopyAndReplaceStringsInStreams(inFile, outFile, search, replace);

	if (inFile.bad())
	{
		throw std::runtime_error("Failed to read data from " + inputFileName + "\n");
	}
	if (!outFile.flush())
	{
		throw std::runtime_error("Failed to write data to " + outputFileName + "\n");
	}
}

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArgs(argc, argv);
		CopyAndReplaceStringsInFiles(args.inputFileName, args.outputFileName, args.searchString, args.replaceString);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}

	return 0;
}
