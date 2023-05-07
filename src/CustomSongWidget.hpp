#pragma once

#include "includes.hpp"

inline bool(__thiscall* CustomSongWidget_initO)(
    gd::CustomSongWidget*,
    gd::SongInfoObject*,
    gd::LevelSettingsObject*,
    bool,
    bool,
    bool,
    bool,
    bool
);
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
);

inline void (__thiscall* CustomSongWidget_updateSongObjectO)(gd::CustomSongWidget* self, gd::SongInfoObject* song);
void __fastcall CustomSongWidget_updateSongObjectH(gd::CustomSongWidget* self, uintptr_t, gd::SongInfoObject* song);