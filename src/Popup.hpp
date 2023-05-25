#pragma once

#include "includes.hpp"

using namespace cocos2d::extension;

/**
 * I stole this from Geode, thanks guys!
 * 
 * 
*/

template<typename... Args>
class Popup : public CCLayerColor {
protected:
    CCLayer* m_mainLayer = nullptr;
    CCMenu* m_buttonMenu;
    CCSize m_size;
    CCScale9Sprite* m_bgSprite;
    CCLabelBMFont* m_title;
    gd::CCMenuItemSpriteExtra* m_closeButton;

    bool init(float width, float height, Args... args, char const* bgSprite = "GJ_square01.png", CCRect bgRect = { 0, 0, 80, 80 }) {
        if (!this->initWithColor(ccc4(0, 0, 0, 106))) {
            return false;
        }
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        m_size = CCSize{ width, height };
        m_mainLayer = CCLayer::create();
        this->addChild(m_mainLayer);
        
        m_bgSprite = CCScale9Sprite::create(bgSprite, bgRect);
        m_bgSprite->setContentSize(m_size);
        m_bgSprite->setPosition(winSize.width / 2, winSize.height / 2);
        m_mainLayer->addChild(m_bgSprite);

        m_buttonMenu = CCMenu::create();
        m_buttonMenu->setZOrder(100);
        m_mainLayer->addChild(m_buttonMenu);

        CCDirector::sharedDirector()->getTouchDispatcher()->incrementForcePrio(2);
        this->registerWithTouchDispatcher();

        auto closeSpr = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        closeSpr->setScale(.8f);

        m_closeButton = gd::CCMenuItemSpriteExtra::create(
            closeSpr, 
            this, 
            menu_selector(Popup::onClose)
        );
        m_closeButton->setPosition(-m_size.width / 2 + 3.f, m_size.height / 2 - 3.f);
        m_buttonMenu->addChild(m_closeButton);

        if (!this->setup(std::forward<Args>(args)...)) {
            return false;
        }

        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);
        this->setTouchPriority(10);

        return true;
    }
    virtual bool setup(Args... args) = 0;

    void registerWithTouchDispatcher() {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MAX, true);
    }

    void keyDown(enumKeyCodes key) {
        if (key == enumKeyCodes::KEY_Escape) return this->onClose(nullptr);
        return;
    }

    void keyBackClicked() {
	    this->onClose(nullptr);
    }

    virtual void onClose(cocos2d::CCObject*) {
        this->setKeyboardEnabled(false);
        this->removeFromParentAndCleanup(true);
    }

    void setTitle(std::string const& title, const char* font = "goldFont.fnt", float scale = .7f, float offset = 20.f) {
        if (m_title) {
            m_title->setString(title.c_str());
        } else {
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            m_title = CCLabelBMFont::create(title.c_str(), font);
            m_title->setPosition(winSize.width / 2, winSize.height / 2 + m_size.height / 2 - offset);
            m_mainLayer->addChild(m_title, 2);
        }
        m_title->limitLabelWidth(m_size.width - 20.f, scale, .1f);
    }
public:
    void show() {
        this->m_mainLayer->setScale(0.1f);
        m_mainLayer->runAction(CCEaseElasticOut::create(CCScaleTo::create(.5f, 1.0f), 0.6f));
        this->runAction(CCFadeTo::create(0.14f, 100));

        if (!this->getParent()) {
            auto scene = CCDirector::sharedDirector()->getRunningScene();
            scene->addChild(this);
        }
    }
};