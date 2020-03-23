#include "band.hpp"

auto ren::find_albums(
	const fs::path& dir,
	const std::wregex& check
) -> std::vector<std::wstring>
{
	std::vector<std::wstring> dirnames;
	for (const auto& entry : fs::directory_iterator(dir))
	{
		const fs::path& entry_path = entry.path();
		if (!is_directory(entry_path)) continue;

		const std::wstring dirname = entry_path.filename().wstring();
		album(entry_path, false);
		if (regex_match(dirname, check))
			dirnames.push_back(dirname);
	}
	return dirnames;
}

auto ren::rename_albums(
	const fs::path& dir,
	const std::vector<std::wstring>& albums,
	const std::wregex& check,
	const std::wstring& replace
) -> void
{
	for (size_t i = 0; i < albums.size(); ++i)
	{
		const int number_length = std::to_string(albums.size()).length();
		std::wostringstream album_number_stream;
		album_number_stream << std::setw(number_length) << std::setfill(L'0') << i + 1;
		const std::wstring album_number = album_number_stream.str();
		const std::wstring new_name = album_number + regex_replace(albums[i], check, replace);
		rename(dir / albums[i], dir / new_name);
	}
}

auto ren::band(const fs::path& dir) -> void
{
	const std::wregex check(LR"(((?:20|19)\d{2}) - (.+) - (.+))");
	const std::wstring replace = L" $3 ($1)";

	const std::vector<std::wstring> albums = find_albums(dir, check);
	rename_albums(dir, albums, check, replace);
}
