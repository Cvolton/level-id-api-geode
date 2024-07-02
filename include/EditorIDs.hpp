#pragma once

#include <Geode/binding/GJGameLevel.hpp>
#include <Geode/binding/GJLevelList.hpp>

#ifdef GEODE_IS_WINDOWS
    #ifdef CVOLTON_EDITORIDS_EXPORTING
        #define EDITORIDS_DLL __declspec(dllexport)
    #else
        #define EDITORIDS_DLL __declspec(dllimport)
    #endif
#else
    #define EDITORIDS_DLL __attribute__((visibility("default")))
#endif

namespace EditorIDs {
    EDITORIDS_DLL int getID(GJGameLevel* level);
    EDITORIDS_DLL int getID(GJLevelList* level);

    EDITORIDS_DLL int getID(GJGameLevel* level, bool autoAssign);
    EDITORIDS_DLL int getID(GJLevelList* level, bool autoAssign);

    EDITORIDS_DLL GJGameLevel* getLevelByID(int id);
    EDITORIDS_DLL GJLevelList* getListByID(int id);
}