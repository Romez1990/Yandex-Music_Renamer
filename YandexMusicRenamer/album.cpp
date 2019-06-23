#include "album.hpp"

void rename_album(const fs::path& path)
{
	const regex check(R"(((?:20|19)\d{2}) - .+ - (.+))");
	const string dirname(path.filename().string());
	if (regex_match(dirname, check))
	{
		const string replace("$2 ($1)");
		rename(path, path / ".." / regex_replace(dirname, check, replace));
	}
}

void rename_track(const fs::path& dir, const fs::path& track, const regex& check, const string& replace)
{
	const string filename = track.filename().string();
	if (regex_match(filename, check))
	{
		const string new_name = regex_replace(filename, check, replace);
		rename(dir / filename, dir / new_name);
	}
}

void album(const fs::path& dir, const bool main)
{
	const regex check(R"((\d{1,2})\. (.+\.mp3))");
	const string replace("$1 $2");

	for (const auto& entry : fs::directory_iterator(dir))
	{
		const fs::path& track = entry.path();
		if (is_directory(track)) continue;

		rename_track(dir, track, check, replace);
	}

	if (main)
		rename_album(dir);
}
