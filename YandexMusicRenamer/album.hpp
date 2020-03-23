#pragma once
#include "main.hpp"

namespace ren
{
	auto rename_album(const fs::path& path) -> void;
	auto rename_track(
		const fs::path& dir,
		const fs::path& track,
		const regex& check,
		const string& replace
	) -> void;
	auto album(const fs::path& dir, const bool main) -> void;
}
