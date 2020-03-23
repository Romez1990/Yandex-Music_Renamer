#include "band.hpp"

auto ren::find_albums(
	const fs::path& dir,
	const std::regex& check
) -> std::vector<std::string>
{
	std::vector<std::string> dirnames;
	for (const auto& entry : fs::directory_iterator(dir))
	{
		const fs::path& entry_path = entry.path();
		if (!is_directory(entry_path)) continue;

		const std::string dirname = entry_path.filename().string();
		album(entry_path, false);
		if (regex_match(dirname, check))
			dirnames.push_back(dirname);
	}
	return dirnames;
}

auto ren::rename_albums(
	const fs::path& dir,
	const std::vector<std::string>& albums,
	const std::regex& check,
	const std::string& replace
) -> void
{
	for (size_t i = 0; i < albums.size(); ++i)
	{
		const int number_length = std::to_string(albums.size()).length();
		std::ostringstream album_number_stream;
		album_number_stream << std::setw(number_length) << std::setfill(L'0') << i + 1;
		const std::string album_number = album_number_stream.str();
		const std::string new_name = album_number + std::regex_replace(albums[i], check, replace);
		rename(dir / albums[i], dir / new_name);
	}
}

auto ren::band(const fs::path& dir) -> void
{
	const std::regex check(R"(((?:20|19)\d{2}) - (.+) - (.+))");
	const std::string replace = " $3 ($1)";

	const std::vector<std::string> albums = find_albums(dir, check);
	rename_albums(dir, albums, check, replace);
}
