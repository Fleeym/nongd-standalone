#include "Nongd.hpp"

Nongd* instance = nullptr;

Nongd* Nongd::sharedInstance() {
    if (!instance) {
        instance = new Nongd();
    }

    return instance;
}

fs::path Nongd::getNongDataPath() {
    auto path = fs::path(CCFileUtils::sharedFileUtils()->getWritablePath()).append("nongd");
    if (!fs::exists(path)) {
        std::cout << "hey!" << std::endl;
        fs::create_directory(path);
    }

    path.append("nong_data");
    if (!fs::exists(path)) {
        fs::create_directory(path);
    }

    return path;
}

fs::path Nongd::getJsonPath(int songID) {
    return this->getNongDataPath().append(std::to_string(songID) + ".json");
}

bool Nongd::checkIfNongsExist(int songID) {
    auto nongData = this->getNongDataPath();
    if (!fs::exists(nongData)) {
        fs::create_directory(nongData);
    }
    auto path = this->getJsonPath(songID);
    if (!fs::exists(path)) return false;

    auto data = getNongs(songID);

    if (data.songs.size() == 1) return false;
    return true;
}

NongData Nongd::getNongs(int songID) {
    auto path = this->getJsonPath(songID);

    std::ifstream input(path.string());
    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    auto json = json::parse(std::string_view(buffer.str()));
    return json::Serialize<NongData>::from_json(json);
}

void Nongd::createDefaultSongIfNull(SongInfo const& song, int songID) {
    if (!this->checkIfNongsExist(songID)) {
        std::vector<SongInfo> songs = { song };
        NongData nongData = {
            .active = song.path,
            .defaultPath = song.path,
            .songs = songs
        };
        this->saveNongs(nongData, songID);
    }
}

void Nongd::saveNongs(NongData const& data, int songID) {
    auto path = getJsonPath(songID);
    auto json = json::Serialize<NongData>::to_json(data);
    std::ofstream output(path.string());
    output << json.dump();
    output.close();
}

std::vector<SongInfo> Nongd::validateNongs(int songID) {
    auto currentData = getNongs(songID);
    // Validate nong paths and delete those that don't exist anymore
    std::vector<SongInfo> invalidSongs;
    std::vector<SongInfo> validSongs;

    for (auto &song : currentData.songs) {
        if (!fs::exists(song.path) && currentData.defaultPath != song.path && song.songUrl == "local") {
            invalidSongs.push_back(song);
            if (song.path == currentData.active) {
                currentData.active = currentData.defaultPath;
            }
        } else {
            validSongs.push_back(song);
        }
    }

    if (invalidSongs.size() > 0) {
        NongData newData = {
            .active = currentData.active,
            .defaultPath = currentData.defaultPath,
            .songs = validSongs
        };

        this->saveNongs(newData, songID);
    }

    return invalidSongs;
}

std::string Nongd::getFormattedSize(SongInfo const& song) {
    try {
        auto size = fs::file_size(song.path);
        double toMegabytes = size / 1024.f / 1024.f;
        std::stringstream ss;
        ss << std::setprecision(3) << toMegabytes << "MB";
        return ss.str();
    } catch (fs::filesystem_error) {
        return "0.00MB";
    }
}