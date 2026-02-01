#define GEODE_DEFINE_EVENT_EXPORTS
#include <EditorIDs.hpp>
#include <EditorIDsInternal.hpp>

int EditorIDs::getID(GJGameLevel* level, bool autoAssign) {
    return EditorIDs::Internal::getID(level, autoAssign);
}

int EditorIDs::getID(GJGameLevel* level) {
    return EditorIDs::Internal::getID(level);
}

GJGameLevel* EditorIDs::getLevelByID(int id) {
    return EditorIDs::Internal::getLevelByID(id);
}

int EditorIDs::getID(GJLevelList* list) {
    return EditorIDs::Internal::getID(list);
}

int EditorIDs::getID(GJLevelList* list, bool autoAssign) {
    return EditorIDs::Internal::getID(list, autoAssign);
}

GJLevelList* EditorIDs::getListByID(int id) {
    return EditorIDs::Internal::getListByID(id);
}