#pragma once

#include "../includes.hpp"

struct SongInfo {
    fs::path path;
    std::string songName;
    std::string authorName;
    std::string songUrl;
};

struct NongData {
    fs::path active;
    fs::path defaultPath;
    std::vector<SongInfo> songs;
};