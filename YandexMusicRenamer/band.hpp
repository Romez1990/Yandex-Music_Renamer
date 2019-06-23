#pragma once
#include "main.hpp"
#include "album.hpp"

vector<string> find_albums(const fs::path& dir, const regex& check);
void rename_albums(const fs::path& dir, const vector<string>& albums, const regex& check, const string& replace);
void band(const fs::path& dir);
