#include "compilation.hpp"

void compilation(const fs::path& path)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		const fs::path& entry_path = entry.path();
		if (!is_directory(entry_path)) continue;

		band(entry_path);
	}
}
