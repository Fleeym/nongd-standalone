#include "CustomSongWidget.hpp"

namespace nongd {
    bool firstRun = false;
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

    nongd::firstRun = false;
    return true;
}

void __fastcall CustomSongWidget_updateSongObjectH(gd::CustomSongWidget* self, uintptr_t, gd::SongInfoObject* song) {
    CustomSongWidget_updateSongObjectO(self, song);
}