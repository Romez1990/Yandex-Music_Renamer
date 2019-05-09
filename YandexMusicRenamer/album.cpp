#include "album.hpp"

void album(const fs::path& path)
{
	const regex check(R"((\d{1,2})\. (.+\.mp3))");
	const string replace("$1 $2");

	for (const auto& entry : fs::directory_iterator(path))
	{
		const fs::path& entry_path = entry.path();
		if (is_directory(entry_path)) continue;

		const string filename = entry_path.filename().string();
		if (regex_match(filename.c_str(), check))
		{
			const string new_name = regex_replace(filename, check, replace);
			fs::rename(path / filename.c_str(), path / new_name.c_str());
		}
	}
}
