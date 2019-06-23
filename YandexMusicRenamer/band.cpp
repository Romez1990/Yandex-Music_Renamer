#include "band.hpp"

vector<string> find_albums(const fs::path& dir, const regex& check)
{
	vector<string> dirnames;
	for (const auto& entry : fs::directory_iterator(dir))
	{
		const fs::path& entry_path = entry.path();
		if (!is_directory(entry_path)) continue;

		const string dirname = entry_path.filename().string();
		album(entry_path, false);
		if (regex_match(dirname, check))
			dirnames.push_back(dirname);
	}
	return dirnames;
}

void rename_albums(const fs::path& dir, const vector<string>& albums, const regex& check, const string& replace)
{
	const bool list_greater_than_10 = albums.size() >= 10;
	for (size_t i = 0; i < albums.size(); ++i)
	{
		string album_number = to_string(i + 1);
		if (list_greater_than_10 && i + 1 < 10)
			album_number.insert(0, "0");

		const string new_name = album_number + regex_replace(albums[i], check, replace);
		rename(dir / albums[i], dir / new_name);
	}
}

void band(const fs::path& dir)
{
	const regex check(R"(((?:20|19)\d{2}) - (.+) - (.+))");
	const string replace(" $3 ($1)");

	const vector<string> albums = find_albums(dir, check);
	rename_albums(dir, albums, check, replace);
}
