#include "NongdLayer.hpp"

void NongdLayer::updateSongNameLabel(std::string const& title, int songID) {
    if (!this->m_songNameMenu) {
        this->addSongNameLabel(title, songID);
        return;
    }

    m_songNameMenuItem->setTag(songID);
    m_songNameLabel->setString(title.c_str());
    m_songNameLabel->limitLabelWidth(220.f, 0.8f, 0.1f);
    auto labelScale = m_songNameLabel->getScale();
    m_songNameMenuItem->setContentSize({ 220.f, labelScale * 30 });
}

void NongdLayer::addSongNameLabel(std::string const& title, int songID) {
    auto menu = CCMenu::create();

    auto label = CCLabelBMFont::create(title.c_str(), "bigFont.fnt");
    label->limitLabelWidth(220.f, 0.8f, 0.1f);
    label->setColor(ccc3(255, 208, 208));
    auto songNameMenuLabel = gd::CCMenuItemSpriteExtra::create(
        label,
        this,
        menu_selector(NongdLayer::openNongdPopup)
    );
    songNameMenuLabel->setTag(songID);
    auto labelScale = label->getScale();
    songNameMenuLabel->setPosition(ccp(0.f, 0.f));
    songNameMenuLabel->setAnchorPoint(ccp(0.f, 0.5f));
    menu->addChild(songNameMenuLabel);
    menu->setContentSize(ccp(220.f, 25.f));
    menu->setPosition(ccp(-140.f, 27.5f));
    songNameMenuLabel->setContentSize({ 220.f, labelScale * 30 });

    this->m_songNameMenuItem = songNameMenuLabel;
    this->m_songNameMenu = menu;
    this->m_songNameLabel = label;

    this->addChild(menu);
}

void NongdLayer::openNongdPopup(CCObject* target) {
    NongdPopup::create(target->getTag(), this->m_customSongWidget)->show();
}

void NongdLayer::updateIDAndSizeLabel(SongInfo const& song, int songID) {
    auto defaultPath = m_nongData.defaultPath;

    if (!fs::exists(song.path) && song.path == defaultPath) {
        m_idAndSizeLabel->setVisible(false);
        m_idAndSizeLabel_O->setVisible(true);
    } else if (m_idAndSizeLabel_O && m_idAndSizeLabel_O->isVisible()) { 
        m_idAndSizeLabel_O->setVisible(false);
        m_idAndSizeLabel->setVisible(true);
    }

    auto nongd = Nongd::sharedInstance();

    auto sizeText = nongd->getFormattedSize(song);
    std::string labelText;
    if (songID != 0) {
        labelText = "SongID: " + std::to_string(songID) + "  Size: " + sizeText;
    } else {
        labelText = "SongID: NONG  Size: " + sizeText;
    }

    if (m_idAndSizeLabel) {
        m_idAndSizeLabel->setString(labelText.c_str());
    }
}