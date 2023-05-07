#include "CustomSongWidget.hpp"

bool __fastcall CustomSongWidget_initH(
        gd::CustomSongWidget* self, 
        uintptr_t,
        bool b1,
        bool b2,
        bool b3,
        bool b4,
        bool hideBackground,
        gd::SongInfoObject* song,
        gd::LevelSettingsObject* settings
    ) {
    if (!CustomSongWidget_initO(self, b1, b2, b3, b4, hideBackground, song, settings)) {
        return false;
    }

    return true;
}

void __fastcall CustomSongWidget_updateSongObjectH(gd::CustomSongWidget* self, uintptr_t, gd::SongInfoObject* song) {
    CustomSongWidget_updateSongObjectO(self, song);
}