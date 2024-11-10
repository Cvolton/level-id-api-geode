#include <EditorIDsManagement.hpp>

#include <Geode/Geode.hpp>
#include <queue>

using namespace geode::prelude;

static std::queue<Ref<GJLevelList>> s_needsAssignment;
static int s_maxListID = 0;
static bool s_debugPrint = false;
static std::atomic_bool s_checkQueued = false;
static std::unordered_map<int, Ref<GJLevelList>> s_idMap;

$on_mod(Loaded) {
    listenForSettingChanges("debug-print", +[](bool value) {
        s_debugPrint = value;
    });
}

$on_mod(DataLoaded) {
    s_maxListID = std::max(Mod::get()->getSavedValue("editor_list_id_max", 0), s_maxListID);
    s_debugPrint = Mod::get()->getSettingValue<bool>("debug-print");
}

$on_mod(DataSaved) {
    Mod::get()->setSavedValue("editor_list_id_max", s_maxListID);
}

int EditorIDs::getID(GJLevelList* list) {
    return getID(list, true);
}

int EditorIDs::getID(GJLevelList* list, bool autoAssign) {
    if(list->m_listType != GJLevelType::Editor) return list->m_listID;

    if(autoAssign) ListManagement::verifyIDAssignment(list);
    return list->m_downloads == list->m_levelsToClaim ? list->m_downloads : 0;
}

GJLevelList* EditorIDs::getListByID(int id) {
    return s_idMap.contains(id) ? s_idMap[id] : nullptr;
}

void EditorIDs::ListManagement::assignNewID(GJLevelList *list) {
    if(list->m_listType != GJLevelType::Editor) return;

    list->m_downloads = ++s_maxListID;
    list->m_levelsToClaim = list->m_downloads;

    if(s_debugPrint) log::info("Assigned custom ID {} to editor list {}", list->m_downloads, list->m_listName);
}

void EditorIDs::ListManagement::verifyIDAssignment(GJLevelList *list) {
    if(list->m_listType != GJLevelType::Editor) return;

    if(list->m_downloads == 0 || list->m_levelsToClaim == 0 || list->m_downloads != list->m_levelsToClaim || (s_idMap.contains(list->m_downloads) && s_idMap[list->m_downloads] != list)) {
        assignNewID(list);
    } else {
        s_maxListID = std::max(s_maxListID, list->m_downloads);

        if(s_debugPrint) log::info("Verified custom ID {} for editor list {}", list->m_downloads, list->m_listName);
    }

    s_idMap[list->m_downloads] = list;
}

void EditorIDs::ListManagement::verifyIDAssignmentDelayed(GJLevelList *list) {
    s_needsAssignment.emplace(list);

    if(list->m_listType == GJLevelType::Editor) s_maxListID = std::max(s_maxListID, list->m_downloads);

    queueCheck();
}

void EditorIDs::ListManagement::queueCheck() {
    if(!s_checkQueued) {
        s_checkQueued = true;
        Loader::get()->queueInMainThread([] {
            while(!s_needsAssignment.empty()) {
                auto list = s_needsAssignment.front();
                s_needsAssignment.pop();

                verifyIDAssignment(list);
            }

            s_checkQueued = false;
        });
    }
}

void EditorIDs::ListManagement::tryTransferID(GJLevelList *source, GJLevelList *dest) {
    if(s_debugPrint) log::info("Trying to transfer ID from {} to {}", source->m_listName, dest->m_listName);

    if(source->m_listType != GJLevelType::Editor || dest->m_listType != GJLevelType::Editor) return;

    if(s_debugPrint) log::info("Source: {} ({}), Dest: {} ({})", source->m_downloads, source->m_levelsToClaim, dest->m_downloads, dest->m_levelsToClaim);

    if(dest->m_downloads == 0 || dest->m_levelsToClaim == 0 || dest->m_downloads != dest->m_levelsToClaim || (dest->m_downloads == source->m_downloads && dest->m_levelsToClaim == source->m_levelsToClaim)) {
        dest->m_downloads = source->m_downloads;
        dest->m_levelsToClaim = source->m_levelsToClaim;

        s_idMap[dest->m_downloads] = dest;

        if(s_debugPrint) log::info("Assigned custom ID {} to editor list {} in tryTransferID", dest->m_downloads, dest->m_listName);
    }
}

void EditorIDs::ListManagement::listIsDeleting(GJLevelList *list) {
    if(list->m_listType != GJLevelType::Editor) return;

    auto id = EditorIDs::getID(list);

    if(s_idMap.contains(id) && s_idMap[id] == list) {
        s_idMap.erase(list->m_downloads);

        if(s_debugPrint) log::info("Removed custom ID {} from editor list {}", list->m_downloads, list->m_listName);
    }
}

void EditorIDs::ListManagement::handleListDupes(cocos2d::CCArray* array) {
    if(!array) return;

    std::unordered_set<int> ids;
    for(auto list : CCArrayExt<GJLevelList*>(array)) {
        auto id = EditorIDs::getID(list);

        if(ids.contains(id)) {
            if(s_debugPrint) log::warn("Found duplicate ID {} in local lists, assigning new ID", id);
            assignNewID(list);
        } else {
            ids.insert(id);
        }
    }

    if(s_debugPrint) log::info("Handled list dupes in local lists");
}

void EditorIDs::ListManagement::reset() {
    s_needsAssignment = {};
    s_maxListID = 0;
    s_checkQueued = false;
    s_idMap.clear();
}

void EditorIDs::ListManagement::tryRaiseMaxID(int id) {
    if(id > s_maxListID) {
        s_maxListID = id;

        if(s_debugPrint) log::info("Raised max list ID to {}", s_maxListID);
    }
}

int EditorIDs::ListManagement::getMaxID() {
    return s_maxListID;
}