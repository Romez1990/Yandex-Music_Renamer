#include "compilation.hpp"

auto ren::compilation(const fs::path& dir) -> void
{
	for (const auto& entry : fs::directory_iterator(dir))
	{
		const fs::path& band_ = entry.path();
		if (!is_directory(band_)) continue;

		band(band_);
	}
}
