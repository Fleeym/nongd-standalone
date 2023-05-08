#include "Nongd.hpp"

Nongd* instance = nullptr;

Nongd* Nongd::sharedInstance() {
    if (!instance) {
        instance = new Nongd();
    }

    return instance;
}

fs::path Nongd::getNongDataPath() {
    auto path = fs::path(CCFileUtils::sharedFileUtils()->getWritablePath()).append("nongd").append("nong_data");
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

    // auto data = getNongs(songID);

    // if (data.songs.size() == 1) return false;
    return true;
}

// NongData Nongd::getNongs(int songID) {
//     auto path = this->getJsonPath(songID);
// }