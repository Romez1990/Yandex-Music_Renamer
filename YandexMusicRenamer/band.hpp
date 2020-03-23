#pragma once
#include "main.hpp"
#include "album.hpp"

namespace ren
{
	auto find_albums(
		const fs::path& dir,
		const std::wregex& check
	) -> std::vector<std::wstring>;
	auto rename_albums(
		const fs::path& dir,
		const std::vector<std::wstring>& albums,
		const std::wregex& check
	) -> void;
	auto band(const fs::path& dir) -> void;
}
