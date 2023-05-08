#include "CustomSongWidget.hpp"

namespace nong {
    bool firstRun = false;
    CCLabelBMFont* songNameLabel_O = nullptr;
    CCLabelBMFont* idAndSizeLabel_O = nullptr;
    CCLabelBMFont* idAndSizeLabel = nullptr;
    std::string invalidSongList = "";
}

void addMenuItemLabel(gd::CustomSongWidget* parent, std::string const& text, int songID) {
    auto menu = CCMenu::create();

    auto label = CCLabelBMFont::create(text.c_str(), "bigFont.fnt");
    label->limitLabelWidth(220.f, 0.8f, 0.1f);
    auto info = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    auto songNameMenuLabel = gd::CCMenuItemSpriteExtra::create(
        label,
        parent,
        // menu_selector(MyCustomSongWidget::addNongLayer)
        nullptr
    );
    songNameMenuLabel->setTag(songID);
    // I am not even gonna try and understand why this works, but this places the label perfectly in the menu
    auto labelScale = label->getScale();
    songNameMenuLabel->setPosition(ccp(0.f, 0.f));
    songNameMenuLabel->setAnchorPoint(ccp(0.f, 0.5f));
    menu->addChild(songNameMenuLabel);
    menu->setContentSize(ccp(220.f, 25.f));
    menu->setPosition(ccp(-140.f, 27.5f));
    songNameMenuLabel->setContentSize({ 220.f, labelScale * 30 });

    parent->addChild(menu);
}

bool __fastcall CustomSongWidget_initH(
        gd::CustomSongWidget* self, 
        uintptr_t,
        gd::SongInfoObject* song,
        gd::LevelSettingsObject* settings,
        bool b1,
        bool b2,
        bool b3,
        bool b4,
        bool hideBackground
    ) {
    if (!CustomSongWidget_initO(self, song, settings, b1, b2, b3, b4, hideBackground)) {
        return false;
    }

    std::cout << "b1: " << b1 << ", b2: " << b2 << ", b3: " << b3 << ", b4: " << b4 << ", hideBG: " << hideBackground << ", settings: " << settings << ", song: " << song << std::endl;

    if (!song) {
        return true;
    }

    auto nongdLayer = NongdLayer::create();
    self->addChild(nongdLayer);
    nongdLayer->m_customSongWidget = self;

    auto *songNameLabel = static_cast<CCLabelBMFont*>(self->getChildren()->objectAtIndex(2));
    songNameLabel->setVisible(false);
    nongdLayer->m_songNameLabel_O = songNameLabel;

    auto idAndSizeLabel = static_cast<CCLabelBMFont*>(self->getChildren()->objectAtIndex(4));
    idAndSizeLabel->setVisible(false);
    nongdLayer->m_idAndSizeLabel_O = idAndSizeLabel;

    auto newLabel = CCLabelBMFont::create("new", "bigFont.fnt");
    newLabel->setPosition(ccp(0.f, -32.f));
    newLabel->setScale(0.4f);
    nongdLayer->addChild(newLabel);
    nongdLayer->m_idAndSizeLabel = newLabel;

    auto nongd = Nongd::sharedInstance();

    if (!nongd->checkIfNongsExist(song->m_nSongID)) {
        auto strPath = std::string(gd::MusicDownloadManager::sharedState()->pathForSong(song->m_nSongID));

        SongInfo defaultSong = {
            .path = fs::path(strPath),
            .songName = song->m_sSongName,
            .authorName = song->m_sArtistName,
            .songUrl = song->m_sSongLink,
        };

        nongd->createDefaultSongIfNull(defaultSong, song->m_nSongID);
    }

    auto invalidSongs = nongd->validateNongs(song->m_nSongID);
    auto nongdata = nongd->getNongs(song->m_nSongID);
    nongdLayer->m_nongData = nongdata;
    SongInfo nong;
    for (auto song : nongdata.songs) {
        if (song.path == nongdata.active) {
            nong = song;
        }
    }

    song->m_sArtistName = nong.authorName;
    song->m_sSongName = nong.songName;
    self->updateSongObject(song);

    nongdLayer->updateSongNameLabel(song->m_sSongName, song->m_nSongID);

    if (nong.path == nongdata.defaultPath) {
        nongdLayer->updateIDAndSizeLabel(nong, song->m_nSongID);
    } else {
        nongdLayer->updateIDAndSizeLabel(nong);
    }

    return true;
}


void __fastcall CustomSongWidget_updateSongObjectH(gd::CustomSongWidget* self, uintptr_t, gd::SongInfoObject* song) {
    CustomSongWidget_updateSongObjectO(self, song);
}