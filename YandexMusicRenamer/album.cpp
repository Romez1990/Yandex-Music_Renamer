#include "album.hpp"

auto ren::rename_album(const fs::path& path) -> void
{
	const std::regex check(R"(((?:20|19)\d{2}) - .+ - (.+))");
	const std::string dirname(path.filename().string());
	if (regex_match(dirname, check))
	{
		const std::string replace("$2 ($1)");
		rename(path, path / ".." / regex_replace(dirname, check, replace));
	}
}

auto ren::rename_track(
	const fs::path& dir,
	const fs::path& track,
	const std::regex& check,
	const std::string& replace
) -> void
{
	const std::string filename = track.filename().string();
	if (regex_match(filename, check))
	{
		const std::string new_name = regex_replace(filename, check, replace);
		rename(dir / filename, dir / new_name);
	}
}

auto ren::album(const fs::path& dir, const bool main) -> void
{
	const std::regex check(R"((\d{1,2})\. (.+\.mp3))");
	const std::string replace("$1 $2");

	for (const auto& entry : fs::directory_iterator(dir))
	{
		const fs::path& track = entry.path();
		if (is_directory(track)) continue;

		rename_track(dir, track, check, replace);
	}

	if (main)
		rename_album(dir);
}
