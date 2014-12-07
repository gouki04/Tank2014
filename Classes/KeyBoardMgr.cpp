#include "KeyBoardMgr.h"
#include <Windows.h>

namespace gouki {
    static KeyBoardMgr *pSharedKeyBoardMgr = NULL;

    KeyBoardMgr * KeyBoardMgr::sharedKeyBoardMgr() {
        if (! pSharedKeyBoardMgr) {
            pSharedKeyBoardMgr = new KeyBoardMgr();
            //pSharedKeyBoardMgr->init();
        }

        return pSharedKeyBoardMgr;
    }

    void KeyBoardMgr::purgeSharedKeyBoardMgr() {
        CC_SAFE_RELEASE_NULL(pSharedKeyBoardMgr);
    }

    KeyBoardMgr::KeyBoardMgr() {

    }

    KeyBoardMgr::~KeyBoardMgr() {

    }

    bool KeyBoardMgr::isKeyDown( int virKey ) {
        return GetKeyState(virKey) < 0;
    }

    bool KeyBoardMgr::isKeyUp( int virKey ) {
        return GetKeyState(virKey) > 0;
    }
}
