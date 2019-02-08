#include "album.hpp"

void album()
{
	album(fs::current_path());
}

void album(const char* path)
{
	album(fs::path(path));
}

void album(const string& path)
{
	album(fs::path(path));
}

void album(const fs::path& path)
{
	const regex regex(R"((\d{1,2})\.( .+\.mp3))");
	for (auto& entry : fs::directory_iterator(path))
	{
		const fs::path& entry_path = entry.path();
		if (is_directory(entry_path)) continue;

		const string filename = entry_path.filename().string();
		cmatch res;
		if (regex_match(filename.c_str(), res, regex))
		{
			const string new_name = res[1].str() + res[2].str();
			fs::rename(path / filename.c_str(), path / new_name.c_str());
		}
	}
}
