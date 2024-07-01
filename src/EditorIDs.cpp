#include <EditorIDsManagement.hpp>

#include <Geode/Geode.hpp>
#include <queue>

using namespace geode::prelude;

static std::queue<Ref<GJGameLevel>> s_needsAssignment;
static int s_maxID = 0;
static std::atomic_bool s_checkQueued = false;
static std::unordered_map<int, Ref<GJGameLevel>> s_idMap;

$on_mod(DataLoaded) {
    s_maxID = std::max(Mod::get()->getSavedValue("editor_id_max", 0), s_maxID);
}

$on_mod(DataSaved) {
    Mod::get()->setSavedValue("editor_id_max", s_maxID);
}

int EditorIDs::getID(GJGameLevel* level, bool autoAssign) {
    if(level->m_levelType != GJLevelType::Editor) return level->m_levelID;

    if(autoAssign) Management::verifyIDAssignment(level);
    return level->m_downloads == level->m_featured ? level->m_downloads : 0;
}

GJGameLevel* EditorIDs::getLevelByID(int id) {
    return s_idMap.contains(id) ? s_idMap[id] : nullptr;
}

void EditorIDs::Management::assignNewID(GJGameLevel *level) {
    if(level->m_levelType != GJLevelType::Editor) return;

    level->m_downloads = ++s_maxID;
    level->m_featured = level->m_downloads;

    log::info("Assigned custom ID {} to editor level {}", level->m_downloads, level->m_levelName);
}

void EditorIDs::Management::verifyIDAssignment(GJGameLevel *level) {
    if(level->m_levelType != GJLevelType::Editor) return;

    if(level->m_downloads == 0 || level->m_featured == 0 || level->m_downloads != level->m_featured || (s_idMap.contains(level->m_downloads) && s_idMap[level->m_downloads] != level)) {
        assignNewID(level);
    } else {
        s_maxID = std::max(s_maxID, level->m_downloads);

        log::info("Verified custom ID {} for editor level {}", level->m_downloads, level->m_levelName);
    }

    s_idMap[level->m_downloads] = level;
}

void EditorIDs::Management::verifyIDAssignmentDelayed(GJGameLevel *level) {
    s_needsAssignment.emplace(level);

    if(level->m_levelType == GJLevelType::Editor) s_maxID = std::max(s_maxID, level->m_downloads);

    queueCheck();
}

void EditorIDs::Management::queueCheck() {
    if(!s_checkQueued) {
        s_checkQueued = true;
        Loader::get()->queueInMainThread([] {
            while(!s_needsAssignment.empty()) {
                auto level = s_needsAssignment.front();
                s_needsAssignment.pop();

                verifyIDAssignment(level);
            }

            s_checkQueued = false;
        });
    }
}

void EditorIDs::Management::tryTransferID(GJGameLevel *source, GJGameLevel *dest) {
    log::info("Trying to transfer ID from {} to {}", source->m_levelName, dest->m_levelName);

    if(source->m_levelType != GJLevelType::Editor || dest->m_levelType != GJLevelType::Editor) return;

    log::info("Source: {} ({}), Dest: {} ({})", source->m_downloads, source->m_featured, dest->m_downloads, dest->m_featured);

    if(dest->m_downloads == 0 || dest->m_featured == 0 || dest->m_downloads != dest->m_featured || (dest->m_downloads == source->m_downloads && dest->m_featured == source->m_featured)) {
        dest->m_downloads = source->m_downloads;
        dest->m_featured = source->m_featured;

        s_idMap[dest->m_downloads] = dest;

        log::info("Assigned custom ID {} to editor level {} in tryTransferID", dest->m_downloads, dest->m_levelName);
    }
}

void EditorIDs::Management::handleLevelDupes(cocos2d::CCArray* array) {
    if(!array) return;

    std::unordered_set<int> ids;
    for(auto level : CCArrayExt<GJGameLevel*>(array)) {
        auto id = EditorIDs::getID(level);

        if(ids.contains(id)) {
            log::warn("Found duplicate ID {} in local levels, assigning new ID", id);
            assignNewID(level);
        } else {
            ids.insert(id);
        }
    }

    log::info("Handled level dupes in local levels");
}

void EditorIDs::Management::reset() {
    s_needsAssignment = {};
    s_maxID = 0;
    s_checkQueued = false;
    s_idMap.clear();
}