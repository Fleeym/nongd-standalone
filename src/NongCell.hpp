#pragma once

#include "types/SongInfo.hpp"
#include "NongdPopup.hpp"

class NongdPopup;

class NongListCell : public CCLayer, public gd::FLAlertLayerProtocol {
protected:
    float m_width;
    float m_height;
    CCLayer* m_layer;

    bool init(CCLayer* layer, CCSize const& size);
    void draw() override;
};

class NongCell : public NongListCell {
protected:
    SongInfo m_songInfo;
    CCLabelBMFont* m_songNameLabel;
    CCLabelBMFont* m_authorNameLabel;
    CCLayer* m_songInfoLayer;

    NongdPopup* m_parentPopup;

    bool init(SongInfo info, NongdPopup* parentPopup, CCSize const& size, bool selected, bool isDefault);

    virtual void FLAlert_Clicked(gd::FLAlertLayer*, bool btn2);
public:
    static NongCell* create(SongInfo info, NongdPopup* parentPopup, CCSize const& size, bool selected, bool isDefault);
    void onSet(CCObject*);
    void deleteSong(CCObject*);
};