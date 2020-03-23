#include "compilation.hpp"

auto main(const int argc, const char* argv[]) -> int
{
	if (argc == 1)
	{
		std::cout << "I'll help you... Soon..." << std::endl;
	}
	else if (argc == 2)
	{
		const fs::path dir = fs::current_path();
		if (std::string(argv[1]) == "--album" || std::string(argv[1]) == "-a")
			ren::album(dir, true);
		else if (std::string(argv[1]) == "--band" || std::string(argv[1]) == "-b")
			ren::band(dir);
		else if (std::string(argv[1]) == "--compilation" || std::string(argv[1]) == "-c")
			ren::compilation(dir);
		else
			std::cout << "Wrong parameter" << std::endl;
	}
	else if (argc == 3)
	{
		const fs::path dir = fs::current_path() / fs::path(argv[2]);
		if (!exists(dir))
		{
			std::cout << "Folder does not exist" << std::endl;
			return 1;
		}

		if (std::string(argv[1]) == "--album" || std::string(argv[1]) == "-a")
			ren::album(dir, true);
		else if (std::string(argv[1]) == "--band" || std::string(argv[1]) == "-b")
			ren::band(dir);
		else if (std::string(argv[1]) == "--compilation" || std::string(argv[1]) == "-c")
			ren::compilation(dir);
	}
	else
	{
		std::cout << "Wrong parameters" << std::endl;
	}

	return 0;
}
