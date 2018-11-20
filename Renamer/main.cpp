#include <iostream>
#include <string>
#include <filesystem>
#include <list>

std::string GetFileExtension(std::string File)
{
	for (int i = File.length() - 1; i >= 0; i--)
	{
		if (File[i] == '.')
		{
			return File.substr(i + 1);
		}
	}

	return "";
}

std::list<std::string> ReadFolder(std::string PathToRead)
{
	auto Files = std::experimental::filesystem::directory_iterator(PathToRead);
	std::list<std::string> mp3Files = {};
	for (const auto &File : Files)
	{
		if (GetFileExtension(File.path().string()) == "mp3")
		{
			mp3Files.push_back(File.path().string());
		}
	}

	return mp3Files;
}

int StartName(std::string mp3File)
{
	for (int i = mp3File.length() - 1; i >= 0; i--)
	{
		if (mp3File[i] == '\\')
		{
			return i + 1;
		}
	}

	return -1;
}

void Album(std::string PathToRead)
{
	std::list<std::string> mp3Files = ReadFolder(PathToRead);

	for (std::string mp3File : mp3Files)
	{
		if (mp3File[StartName(mp3File) + 2] != '.') continue;

		std::string NewName = mp3File;
		NewName.erase(StartName(NewName) + 2, 1);

		rename(mp3File.c_str(), NewName.c_str());
	}
}

void Band(std::string PathToRead)
{
	auto Folders = std::experimental::filesystem::directory_iterator(PathToRead);

	for (const auto& Folder : Folders)
	{
		if (!is_directory(Folder)) continue;

		std::string FolderName = Folder.path().string().substr(StartName(Folder.path().string()));
		std::string NewFolderName;

		std::string Year = FolderName.substr(0, 4);

		NewFolderName += " (" + Year + ")";

		std::cout << NewFolderName << std::endl;

		//Album(PathToRead + '\\' + NewFolderName);
	}
}

int main(int argc, char* argv[])
{
	Band(R"(C:\Users\User\source\repos\I See Stars)");

	/*
	if (argc == 1)
	{
		std::cout << "I'll help you..." << std::endl;
	}
	else if (argc == 2)
	{
		if (argv[1] == std::string("--album") || argv[1] == std::string("-a"))
		{
			Album(R"(C:\Users\User\source\repos\I See Stars\2013 - I See Stars - New Demons)");
			//Album(std::experimental::filesystem::current_path().string());
		}
		else if (argv[1] == std::string("--band") || argv[1] == std::string("-b"))
		{
			Band(R"(C:\Users\User\source\repos\I See Stars)");
			//Band(std::experimental::filesystem::current_path().string());
		}
	}
	//*/

	return 0;
}
