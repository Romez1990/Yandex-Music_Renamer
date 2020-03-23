#pragma once
#include "main.hpp"

namespace ren
{
	auto rename_album(const fs::path& dir_path) -> void;
	auto rename_track(
		const fs::path& dir,
		const fs::path& track,
		const std::regex& check,
		const std::string& replace
	) -> void;
	auto album(const fs::path& dir, const bool main) -> void;
}
