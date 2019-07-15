#pragma once
#include "main.hpp"

namespace ren
{
	void rename_album(const fs::path& path);
	void rename_track(const fs::path& dir, const fs::path& track, const regex& check, const string& replace);
	void album(const fs::path& dir, const bool main);
}
