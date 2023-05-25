#pragma once

#include "Popup.hpp"
#include "Nongd.hpp"
#include "NongCell.hpp"

class NongdPopup : public Popup<int, gd::CustomSongWidget*> {
protected:
    int m_songID;
    gd::CustomSongWidget* m_customSongWidget;
    CCMenu* m_addButtonMenu;
    CCMenu* m_fetchSongHubMenu;
    CCLayer* m_listLayer;
    gd::CustomListView* m_list;

    NongData m_songs;

    CCSize getPopupSize() const {
        return { 500.f, 280.f };
    }

    bool setup(int songID, gd::CustomSongWidget* customSongWidget) override;
    void setSongs();
    SongInfo getActiveSong();
    void createList();
    void createAddButton();
    CCArray* createNongCells();

    CCSize getCellSize() const;
    CCSize getListSize() const;

public:
    void setActiveSong(SongInfo const& song);
    void deleteSong(SongInfo const& song);

    static NongdPopup* create(int songID, gd::CustomSongWidget* parent) {
        auto ref = new NongdPopup();
        auto size = ref->getPopupSize();
        if (ref && ref->init(size.width, size.height, songID, parent)) {
            ref->autorelease();
            ref->setTitle("Nongs for ID " + std::to_string(songID));
            return ref;
        }

        CC_SAFE_DELETE(ref);
        return nullptr;
    }
};