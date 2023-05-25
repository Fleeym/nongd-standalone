#include "NongCell.hpp"

bool NongListCell::init(CCLayer* layer, CCSize const& size) {
    m_width = size.width;
    m_height = size.height;
    m_layer = layer;
    this->setContentSize(size);
    return true;
}

void NongListCell::draw() {
    reinterpret_cast<gd::StatsCell*>(this)->StatsCell::draw();
}

bool NongCell::init(SongInfo info, NongdPopup* parentPopup, CCSize const& size, bool selected, bool isDefault) {
    if (!NongListCell::init(parentPopup, size)) return false;

    this->m_songInfo = info;
    this->m_parentPopup = parentPopup;

    gd::CCMenuItemSpriteExtra* button;

    if (selected) {
        auto sprite = gd::ButtonSprite::create("Set", 0, false, "goldFont.fnt", "GJ_button_02.png", 0, 1.f);
        // sprite->setColor(ccc3(0, 204, 255));
        button = gd::CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(NongCell::onSet)
        );
    } else {
        button = gd::CCMenuItemSpriteExtra::create(
            gd::ButtonSprite::create("Set", 0, false, "goldFont.fnt", "GJ_button_02.png", 0, 1.f),
            this,
            menu_selector(NongCell::onSet)
        );
    }
    button->setAnchorPoint(ccp(0.5f, 0.5f));

    auto menu = CCMenu::create();
    menu->addChild(button);

    if (!isDefault) {
        auto deleteButton = gd::CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png"),
            this,
            menu_selector(NongCell::deleteSong)
        );
        menu->addChild(deleteButton);
        deleteButton->setPositionX(53.f);
    }

    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(320.f, 29.f));
    this->addChild(menu);

    this->m_songInfoLayer = CCLayer::create();

    this->m_songNameLabel = CCLabelBMFont::create(m_songInfo.songName.c_str(), "bigFont.fnt");
    this->m_songNameLabel->limitLabelWidth(240.f, 0.8f, 0.1f);

    if (selected) {
        this->m_songNameLabel->setColor(ccc3(188, 254, 206));
    }

    this->m_authorNameLabel = CCLabelBMFont::create(m_songInfo.authorName.c_str(), "goldFont.fnt");
    this->m_authorNameLabel->limitLabelWidth(240.f, 0.7f, 0.1f);

    this->m_songInfoLayer->addChild(this->m_authorNameLabel);
    this->m_songInfoLayer->addChild(this->m_songNameLabel);
    this->m_songInfoLayer->setContentSize(ccp(240.f, this->getContentSize().height - 6.f));
    this->m_songInfoLayer->setAnchorPoint(ccp(0.f, 0.f));
    this->m_songInfoLayer->setPosition(ccp(12.f, 1.5f));

    this->addChild(m_songInfoLayer);
    return true;
}

void NongCell::onSet(CCObject* target) {
    this->m_parentPopup->setActiveSong(this->m_songInfo);
}

void NongCell::deleteSong(CCObject* target) {
    gd::FLAlertLayer::create(this, "Are you sure?", "No", "Yes", "Are you sure you want to delete <cy>" + this->m_songInfo.songName + "</c> from your NONGs?")->show();
}

void NongCell::FLAlert_Clicked(gd::FLAlertLayer* layer, bool btn2) {
    if (btn2) {
        this->m_parentPopup->deleteSong(this->m_songInfo);
    }
}

NongCell* NongCell::create(SongInfo info, NongdPopup* parentPopup, CCSize const& size, bool selected, bool isDefault) {
    auto ret = new NongCell();
    if (ret && ret->init(info, parentPopup, size, selected, isDefault)) {
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
