#include "album.hpp"

void album(const fs::path& path, const bool main)
{
	if (main)
	{
		const regex check(R"(((?:20|19)\d{2}) - (.+) - (.+))");
		const string dirname(path.filename().string());
		if (regex_match(dirname, check))
		{
			const string replace("$3 ($1)");
			rename(path, path / ".." / regex_replace(dirname, check, replace));
		}
	}

	const regex check(R"((\d{1,2})\. (.+\.mp3))");
	const string replace("$1 $2");

	for (const auto& entry : fs::directory_iterator(path))
	{
		const fs::path& entry_path = entry.path();

		if (is_directory(entry_path)) continue;

		const string filename = entry_path.filename().string();
		if (regex_match(filename, check))
		{
			const string new_name = regex_replace(filename, check, replace);
			rename(path / filename, path / new_name);
		}
	}
}
