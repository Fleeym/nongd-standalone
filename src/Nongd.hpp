#pragma once

#include "includes.hpp"
#include "types/SongInfo.hpp"

class Nongd {
public:
    static Nongd* sharedInstance();

    /**
     * Checks if any NONGS exist for a songID
     * 
     * @param songID the id of the song
     * @return true if the json exists, false otherwise
    */
    bool checkIfNongsExist(int songID);

    /**
     * Returns the path for writing nong data
     * 
     * @return %LOCALAPPDATA%/GeometryDash/nongd/nong_data
    */
    fs::path getNongDataPath();

    /**
     * Returns the path for the JSON of a songID
     * 
     * @param songID the ID of the song
     * 
     * @return the path of the JSON of the song
    */
    fs::path getJsonPath(int songID);

    /**
     * Fetches all NONG data from the songID JSON
     * 
     * @param songID the id of the song
     * @return the data from the JSON
    */
    NongData getNongs(int songID);

    void createDefaultSongIfNull(SongInfo const& song, int songID);

    void saveNongs(NongData const& data, int songID);

    std::vector<SongInfo> validateNongs(int songID);

    std::string getFormattedSize(SongInfo const& song);
};
    