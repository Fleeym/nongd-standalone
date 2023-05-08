#pragma once

#include "includes.hpp"
#include "types/SongInfo.hpp"
#include "Nongd.hpp"

class NongdLayer : public CCLayer {
public:
    bool m_firstRun = false;
    gd::CustomSongWidget* m_customSongWidget = nullptr;
    CCLabelBMFont* m_songNameLabel_O = nullptr;
    CCLabelBMFont* m_idAndSizeLabel_O = nullptr;

    CCMenu* m_songNameMenu = nullptr;
    gd::CCMenuItemSpriteExtra* m_songNameMenuItem = nullptr;
    CCLabelBMFont* m_songNameLabel = nullptr;
    CCLabelBMFont* m_idAndSizeLabel = nullptr;

    NongData m_nongData;

    void updateSongNameLabel(std::string const& title, int songID);
    void updateIDAndSizeLabel(SongInfo const& song, int songID = 0);

    static NongdLayer* create() {
        auto layer = new NongdLayer();
        if (layer && layer->init()) {
            layer->autorelease();
            return layer;
        }
        CC_SAFE_DELETE(layer);
        return nullptr;
    }
private:
    void addSongNameLabel(std::string const& title, int songID);
    void openNongdPopup(CCObject* target);
};