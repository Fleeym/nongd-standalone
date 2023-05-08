#include "JsonManager.hpp"

JsonManager* instance = nullptr;

JsonManager* JsonManager::sharedInstance() {
    if (!instance) {
        instance = new JsonManager();
    }

    return instance;
}