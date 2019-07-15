#pragma once
#include "main.hpp"
#include "album.hpp"

namespace ren
{
	auto find_albums(const fs::path& dir, const regex& check) -> vector<string>;
	auto rename_albums(const fs::path& dir, const vector<string>& albums, const regex& check, const string& replace) -> void;
	auto band(const fs::path& dir) -> void;
}
