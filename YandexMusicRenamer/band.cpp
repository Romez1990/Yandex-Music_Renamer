#include "band.hpp"

void band(const fs::path& path)
{
	const regex check(R"(((?:20|19)\d{2}) - (.+) - (.+))");
	const string replace(" $3 ($1)");

	vector<string> old_dirnames;

	for (const auto& entry : fs::directory_iterator(path))
	{
		const fs::path& entry_path = entry.path();
		if (!is_directory(entry_path)) continue;

		const string dirname = entry_path.filename().string();
		album(entry_path, false);
		if (regex_match(dirname, check))
			old_dirnames.push_back(dirname);
	}

	const bool list_greater_than_10 = old_dirnames.size() >= 10;
	for (int i = 0; i < old_dirnames.size(); ++i)
	{
		string album_number = to_string(i + 1);
		if (list_greater_than_10 && i + 1 < 10)
			album_number.insert(0, "0");

		const string new_name = album_number + regex_replace(old_dirnames[i], check, replace);
		rename(path / old_dirnames[i], path / new_name);
	}
}
