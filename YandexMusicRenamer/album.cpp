#include "album.hpp"

auto ren::rename_album(const fs::path& dir_path) -> void
{
	const std::wregex check(LR"(((?:20|19)\d{2}) - .+ - (.+))");
	const std::wstring dirname = dir_path.filename().wstring();
	if (regex_match(dirname, check))
	{
		const std::wstring replace = L"$2 ($1)";
		const std::wstring new_dirname = regex_replace(dirname, check, replace);
		const fs::path new_dir_path = dir_path / ".." / new_dirname;
		rename(dir_path, new_dir_path);
	}
}

auto ren::rename_track(
	const fs::path& dir,
	const fs::path& track,
	const std::wregex& check,
	const std::wstring& replace
) -> void
{
	const std::wstring filename = track.filename().wstring();
	if (regex_match(filename, check))
	{
		const std::wstring new_name = regex_replace(filename, check, replace);
		rename(dir / filename, dir / new_name);
	}
}

auto ren::album(const fs::path& dir, const bool main) -> void
{
	const std::wregex check(LR"((\d{1,2})\. (.+\.mp3))");
	const std::wstring replace = L"$1 $2";

	for (const auto& entry : fs::directory_iterator(dir))
	{
		const fs::path& track = entry.path();
		if (is_directory(track)) continue;

		rename_track(dir, track, check, replace);
	}

	if (main) rename_album(dir);
}
