#include "compilation.hpp"

void absolute_or_relative(const string path, void (*absolute)(const string& path1), void (*relative)(const fs::path& path2))
{
	if (path[1] == ':' || path[0] == '/')
		// Absolute path
		absolute(path);
	else
		// Relative path
		relative(fs::current_path() / path);
}

int main(const int argc, const char* argv[])
{
	if (argc == 1)
	{
		cout << "I'll help you..." << endl;
	}
	else if (argc == 2)
	{
		if (string(argv[1]) == "--album" || string(argv[1]) == "-a")
			album();
		else if (string(argv[1]) == "--band" || string(argv[1]) == "-b")
			band(fs::current_path().string());
		else if (string(argv[1]) == "--compilation" || string(argv[1]) == "-c")
			compilation(fs::current_path());
	}
	else if (argc == 3)
	{
		if (string(argv[1]) == "--album" || string(argv[1]) == "-a")
			absolute_or_relative(string(argv[2]), album, album);
		else if (string(argv[1]) == "--band" || string(argv[1]) == "-b")
			absolute_or_relative(string(argv[2]), band, band);
		else if (string(argv[1]) == "--compilation" || string(argv[1]) == "-c")
			absolute_or_relative(string(argv[2]), compilation, compilation);
	}
	else
	{
		cout << "Wrong parameters" << endl;
	}

	return 0;
}
