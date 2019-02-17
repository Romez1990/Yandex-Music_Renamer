#include "band.hpp"

void band()
{
	band(fs::current_path());
}

void band(const char* path)
{
	band(fs::path(path));
}

void band(const string& path)
{
	band(fs::path(path));
}

struct band_dir
{
	string old_name;
	string new_name;
};

void band(const fs::path& path)
{
	vector<band_dir> band_dirs;

	const regex check(R"(((?:20|19)\d{2}) - (.+) - (.+))");
	const string replace(" $3 ($1)");

	for (const auto& entry : fs::directory_iterator(path))
	{
		const fs::path& entry_path = entry.path();
		if (!is_directory(entry_path)) continue;

		const string dirname = entry_path.filename().string();
		if (regex_match(dirname.c_str(), check))
		{
			band_dir band_dir;
			band_dir.old_name = dirname;
			band_dir.new_name = regex_replace(dirname, check, replace);
			band_dirs.push_back(band_dir);
		}
	}

	const bool need_add_0 = band_dirs.size() >= 10;
	for (int i = 0; i < band_dirs.size(); ++i)
	{
		string album_number;
		if (need_add_0)
			album_number = i < 10 ? "0" + to_string(i + 1) : to_string(i + 1);
		else
			album_number = to_string(i + 1);

		const string new_name = album_number + band_dirs[i].new_name;
		const fs::path new_path = path / new_name.c_str();
		fs::rename(path / band_dirs[i].old_name.c_str(), new_path);
		album(new_path);
	}
}
