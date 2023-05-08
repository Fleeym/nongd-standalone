#include "CustomSongWidget.hpp"

namespace nong {
    bool firstRun = false;
    CCLabelBMFont* songNameLabel_O = nullptr;
    CCLabelBMFont* idAndSizeLabel_O = nullptr;
    CCLabelBMFont* idAndSizeLabel = nullptr;
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

    auto *songNameLabel = static_cast<CCLabelBMFont*>(self->getChildren()->objectAtIndex(2));
    songNameLabel->setVisible(false);
    nong::songNameLabel_O = songNameLabel;
    nong::firstRun = false;

    auto idAndSizeLabel = static_cast<CCLabelBMFont*>(self->getChildren()->objectAtIndex(4));
    idAndSizeLabel->setVisible(false);
    nong::idAndSizeLabel_O = idAndSizeLabel;

    auto newLabel = CCLabelBMFont::create("new", "bigFont.fnt");
    newLabel->setPosition(ccp(0.f, -32.f));
    newLabel->setScale(0.4f);
    self->addChild(newLabel);
    nong::idAndSizeLabel = newLabel;

    return true;
}

void __fastcall CustomSongWidget_updateSongObjectH(gd::CustomSongWidget* self, uintptr_t, gd::SongInfoObject* song) {
    CustomSongWidget_updateSongObjectO(self, song);
}