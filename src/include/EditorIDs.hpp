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
    int EDITORIDS_DLL getID(GJGameLevel* level, bool autoAssign = true);
    int EDITORIDS_DLL getID(GJLevelList* level, bool autoAssign = true);

    namespace Management {
        void EDITORIDS_DLL assignNewID(GJGameLevel* level);
        void EDITORIDS_DLL verifyIDAssignment(GJGameLevel* level);
        void EDITORIDS_DLL verifyIDAssignmentDelayed(GJGameLevel* level);
        void EDITORIDS_DLL queueCheck();
        void EDITORIDS_DLL tryTransferID(GJGameLevel* source, GJGameLevel* dest);

        void EDITORIDS_DLL handleLevelDupes(cocos2d::CCArray* array);

        void EDITORIDS_DLL reset();
    }

    namespace ListManagement {
        void EDITORIDS_DLL assignNewID(GJLevelList* level);
        void EDITORIDS_DLL verifyIDAssignment(GJLevelList* level);
        void EDITORIDS_DLL verifyIDAssignmentDelayed(GJLevelList* level);
        void EDITORIDS_DLL queueCheck();
        void EDITORIDS_DLL tryTransferID(GJLevelList* source, GJLevelList* dest);

        void EDITORIDS_DLL handleListDupes(cocos2d::CCArray* array);

        void EDITORIDS_DLL reset();
    }
}