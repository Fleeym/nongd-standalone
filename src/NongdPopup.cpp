#include "NongdPopup.hpp"

bool NongdPopup::setup(int songID, gd::CustomSongWidget* customSongWidget) {
    m_customSongWidget = customSongWidget;
    m_songID = songID;

    this->setSongs();
    this->createList();
    this->createAddButton();

    return true;
}

void NongdPopup::setSongs() {
    auto nongd = Nongd::sharedInstance();
    m_songs = nongd->getNongs(m_songID);
}

void NongdPopup::createList() {
    auto cells = this->createNongCells();
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto listSize = this->getListSize();

    m_listLayer = CCLayer::create();
    m_list = gd::CustomListView::create(
        cells,
        gd::BoomListType::kBoomListTypeDefault,
        listSize.width,
        listSize.height
    );

    m_list->setupList();

    auto sideLeft = CCSprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    sideLeft->setAnchorPoint(ccp(0, 0));
    sideLeft->setScaleY(5.45f);
    sideLeft->setScaleX(1.2f);
    sideLeft->setPositionX(-3.f);
    sideLeft->setZOrder(9);

    auto sideTop = CCSprite::createWithSpriteFrameName("GJ_commentTop_001.png");
    sideTop->setAnchorPoint(ccp(0, 0));
    sideTop->setScaleX(1.15f);
    sideTop->setPosition(ccp(-3.f, 163.f));
    sideTop->setZOrder(9);

    auto sideBottom = CCSprite::createWithSpriteFrameName("GJ_commentTop_001.png");
    sideBottom->setFlipY(true);
    sideBottom->setAnchorPoint(ccp(0, 0));
    sideBottom->setPosition(ccp(-3.f, -15.f));
    sideBottom->setScaleX(1.15f);
    sideBottom->setZOrder(9);

    auto sideRight = CCSprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    sideRight->setFlipX(true);
    sideRight->setScaleY(5.45f);
    sideRight->setScaleX(1.2f);
    sideRight->setAnchorPoint(ccp(0, 0));
    sideRight->setPositionX(396.f);
    sideRight->setZOrder(9);

    this->m_listLayer->addChild(sideLeft);
    this->m_listLayer->addChild(sideTop);
    this->m_listLayer->addChild(sideBottom);
    this->m_listLayer->addChild(sideRight);
    this->m_listLayer->addChild(this->m_list);
    this->m_listLayer->ignoreAnchorPointForPosition(false);
    this->m_listLayer->setPosition(winSize / 2 + ccp(83.f, 62.f));
    this->m_mainLayer->addChild(m_listLayer);
}

void NongdPopup::createAddButton() {
    this->m_addButtonMenu = CCMenu::create();
    auto addButton = gd::CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png"),
        this,
        nullptr
    );
    
    this->m_addButtonMenu->addChild(addButton);
    this->m_addButtonMenu->setPosition(ccp(524.5f, 29.f));
    this->m_mainLayer->addChild(m_addButtonMenu);
}

CCSize NongdPopup::getCellSize() const {
    return {
        this->getListSize().width,
        60.f
    };
}

CCSize NongdPopup::getListSize() const {
    return { 400.f, 190.f };
}

CCArray* NongdPopup::createNongCells() {
    auto songs = CCArray::create();
    auto activeSong = this->getActiveSong();

    songs->addObject(NongCell::create(activeSong, this, this->getCellSize(), true, activeSong.path == this->m_songs.defaultPath));

    for (auto song : m_songs.songs) {
        if (m_songs.active == song.path) {
            continue;
        }
        songs->addObject(NongCell::create(song, this, this->getCellSize(), false, song.path == this->m_songs.defaultPath));
    }

    return songs;
}

SongInfo NongdPopup::getActiveSong() {
    for (auto song : m_songs.songs) {
        if (song.path == m_songs.active) {
            return song;
        }
    }

    auto nongd = Nongd::sharedInstance();
    m_songs.active = m_songs.defaultPath;
    nongd->saveNongs(m_songs, this->m_songID);
    for (auto song : m_songs.songs) {
        if (song.path == m_songs.active) {
            return song;
        }
    }

    throw std::runtime_error("If you somehow reached this, good job.");
}

void NongdPopup::setActiveSong(SongInfo const& song) {

}

void NongdPopup::deleteSong(SongInfo const& song) {
    // auto nongd = Nongd::sharedInstance();
    // nongd->deleteNong(song, this->m_songID);
    // this->updateParentWidget(nong::getActiveNong(this->m_songID));
    // FLAlertLayer::create("Success", "The song was deleted!", "Ok")->show();
    // this->m_listLayer->removeAllChildrenWithCleanup(true);
    // this->removeChild(m_listLayer);
    // this->m_listLayer = nullptr;
    // this->setSongs();
    // this->createList();
}