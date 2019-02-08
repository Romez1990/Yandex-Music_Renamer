#include "compilation.hpp"

void compilation()
{
	compilation(fs::current_path());
}

void compilation(const char* path)
{
	compilation(fs::path(path));
}

void compilation(const string& path)
{
	compilation(fs::path(path));
}

void compilation(const fs::path& path)
{
	for (auto& entry : fs::directory_iterator(path))
	{
		const fs::path& entry_path = entry.path();
		if (!is_directory(entry_path)) continue;

		band(entry_path);
	}
}
