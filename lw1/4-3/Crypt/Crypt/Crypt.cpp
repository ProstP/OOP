#include <iostream>
#include <string>
#include <fstream>

const int MAX_KEY_VALUE = 255;
const int MIN_KEY_VALUE = 0;

enum class Mode
{
	Crypt,
	Decrypt
};

struct Args
{
	Mode mode;
	std::string inFileName;
	std::string outFileName;
	int key;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument("Invalid argument count\nUsage: crypt.exe <mode> <input file> <output file> <key>");
	}

	Args args;
	std::string mode = argv[1];
	if (mode == "crypt")
	{
		args.mode = Mode::Crypt;
	}
	else if (mode == "decrypt")
	{
		args.mode = Mode::Decrypt;
	}
	else
	{
		throw std::invalid_argument("Unknown mode: " + mode);
	}
	args.inFileName = argv[2];
	args.outFileName = argv[3];
	args.key = std::stoi(argv[4]);
	if (args.key < MIN_KEY_VALUE || args.key > MAX_KEY_VALUE)
	{
		throw std::invalid_argument("Invalid key value");
	}

	return args;
}

unsigned char MixBits(char byte)
{
	unsigned char result = 0;

	result |= (byte & 0b00000111) << 2;
	result |= (byte & 0b00011000) << 3;
	result |= (byte & 0b01100000) >> 5;
	result |= (byte & 0b10000000) >> 2;

	return result;
}

void Crypt(std::ifstream& inFile, std::ofstream& outFile, int key)
{
	char byte;
	while (inFile.read(&byte, sizeof(byte)))
	{
		byte ^= key;
		outFile.put(MixBits(byte));
	}
}

unsigned char UnMixBits(char byte)
{
	unsigned char result = 0;

	result |= (byte & 0b00000011) << 5;
	result |= (byte & 0b00011100) >> 2;
	result |= (byte & 0b00100000) << 2;
	result |= (byte & 0b11000000) >> 3;

	return result;
}

void Decrypt(std::ifstream& inFile, std::ostream& outFile, int key)
{
	char byte;
	while (inFile.read(&byte, sizeof(byte)))
	{
		byte = UnMixBits(byte);
		outFile.put(byte ^ key);
	}
}

void CryptOrDecryptFile(const Mode& mode, const std::string& inFileName, const std::string& outFileName, int key)
{
	std::ifstream inFile(inFileName, std::ios::binary | std::ios::in);
	if (!inFile.is_open())
	{
		throw std::runtime_error("Failed to open: " + inFileName + " to read");
	}
	std::ofstream outFile(outFileName, std::ios::binary | std::ios::out);
	if (!outFile.is_open())
	{
		throw std::runtime_error("Falied to open: " + outFileName + " to write");
	}

	if (mode == Mode::Crypt)
	{
		Crypt(inFile, outFile, key);
	}
	if (mode == Mode::Decrypt)
	{
		Decrypt(inFile, outFile, key);
	}

	if (!inFile.eof())
	{
		throw std::runtime_error("Failed to read data from " + inFileName);
	}
	if (!outFile.flush())
	{
		throw std::runtime_error("Failed to write data to " + outFileName);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		CryptOrDecryptFile(args.mode, args.inFileName, args.outFileName, args.key);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		return 1;
	}

	return 0;
}
