#include "MiniDictionary.h"

void ArgumentsCountCheck(int argc)
{
	if (argc > 2)
	{
		std::cout << "Usage: MiniDictionary.exe <Dictionary file>" << std::endl
			<< "\t<Dictionary file> - <optional> file path to dictionary." << std::endl;

		throw std::invalid_argument("Invalid arguments count.");
	}
}

std::string GetDictionaryFilePathFromArgv(int argc, char* argv[])
{
	ArgumentsCountCheck(argc);

	return (argc == 1) ? "DefaultDictionary.txt" : argv[1];
}

Dictionary ReadDictionaryFromFile(std::string const& filePath)
{
	Dictionary result;

	std::ifstream dictionaryFile(filePath);
	std::string key;
	std::string value;

	while (dictionaryFile >> key)
	{
		dictionaryFile >> value;
		result.insert(std::pair<std::string, std::string>(key, value));
	}

	return result;
}

bool StartDialogWithUser(Dictionary& dictionary)
{
	std::string userString;
	std::string userTranslation;
	bool isDictionaryChanged = false;

	std::cout << "������� ����� ��� ��������. ��� ������ �������: '...'" << std::endl;

	std::getline(std::cin, userString);
	boost::algorithm::to_lower(userString);

	while (userString!= EXIT)
	{
		FindWordInDictionary(dictionary, userString, userTranslation, isDictionaryChanged);
		std::getline(std::cin, userString);
		boost::algorithm::to_lower(userString);
	}

	if (isDictionaryChanged)
	{
		std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
	}

	return isDictionaryChanged;
}

void FindWordInDictionary(
	Dictionary& dictionary, 
	std::string const& userString, 
	std::string& userTranslation, 
	bool& isDictionaryChanged
)
{
	std::pair<Dictionary::iterator, Dictionary::iterator> rangeOfElements;
	rangeOfElements = dictionary.equal_range(userString);

	if (dictionary.find(userString) == dictionary.end())
	{
		std::cout << "����������� ����� '" << userString << "'. ������� ������� ��� ������ ������ ��� ������." << std::endl;
		std::getline(std::cin, userTranslation);
		isDictionaryChanged = CheckUserTranslation(dictionary, userString, userTranslation);
	}
	else
	{
		for (auto& it = rangeOfElements.first; it != rangeOfElements.second; ++it)
		{
			std::cout << it->second << ' ';
		}
		std::cout << std::endl;
	}
}

bool CheckUserTranslation(Dictionary& dictionary, std::string const& userString, std::string const& userTranslation)
{
	bool isDictionaryChanged = false;

	if (!userTranslation.empty())
	{
		dictionary.insert(std::pair<std::string, std::string>(userString, userTranslation));
		std::cout << "����� '" << userString << "' ��������� � ������� ��� '" << userTranslation << "'." << std::endl;
		isDictionaryChanged = true;
	}
	else
	{
		std::cout << "����� '" << userString << "' ���������������." << std::endl;
	}

	return isDictionaryChanged;
}

void CheckForSavingChanges(Dictionary& dictionary, std::string const& dictionaryFileName, std::string& userString)
{
	boost::algorithm::to_lower(userString);
	if (userString == "y")
	{
		OverwriteDictionaryFile(dictionaryFileName, dictionary);
		std::cout << "��������� ���������. �� ��������.";
	}
	else
	{
		std::cout << "��������� �� ���� ���������. �� ��������.";
	}
}

void OverwriteDictionaryFile(std::string const& fileName, Dictionary const& dictionary)
{
	std::ofstream dictionaryFile(fileName);

	for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		dictionaryFile << (*it).first << std::endl;
		dictionaryFile << (*it).second << std::endl;
	}
}