#include "compilation.hpp"

int main(const int argc, const char* argv[])
{
	if (argc == 1)
	{
		cout << "I'll help you... Soon..." << endl;
	}
	else if (argc == 2)
	{
		const fs::path path = fs::current_path();
		if (string(argv[1]) == "--album" || string(argv[1]) == "-a")
			album(path);
		else if (string(argv[1]) == "--band" || string(argv[1]) == "-b")
			band(path);
		else if (string(argv[1]) == "--compilation" || string(argv[1]) == "-c")
			compilation(path);
		else
			cout << "Wrong parameter" << endl;
	}
	else if (argc == 3)
	{
		const fs::path path = fs::current_path() / fs::path(argv[2]);

		if (!exists(path))
		{
			cout << "Folder does not exist" << endl;
			return 1;
		}

		if (string(argv[1]) == "--album" || string(argv[1]) == "-a")
			album(path);
		else if (string(argv[1]) == "--band" || string(argv[1]) == "-b")
			band(path);
		else if (string(argv[1]) == "--compilation" || string(argv[1]) == "-c")
			compilation(path);
	}
	else
	{
		cout << "Wrong parameters" << endl;
	}

	return 0;
}
