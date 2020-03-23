#pragma once
#include "main.hpp"
#include "album.hpp"

namespace ren
{
	auto find_albums(
		const fs::path& dir,
		const std::regex& check
	) -> std::vector<std::string>;
	auto rename_albums(
		const fs::path& dir,
		const std::vector<std::string>& albums,
		const std::regex& check,
		const std::string& replace
	) -> void;
	auto band(const fs::path& dir) -> void;
}
