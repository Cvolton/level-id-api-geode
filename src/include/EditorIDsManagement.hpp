#pragma once

#include "EditorIDs.hpp"

namespace EditorIDs {
    namespace Management {
        EDITORIDS_DLL void assignNewID(GJGameLevel* level);
        EDITORIDS_DLL void verifyIDAssignment(GJGameLevel* level);
        EDITORIDS_DLL void verifyIDAssignmentDelayed(GJGameLevel* level);
        EDITORIDS_DLL void queueCheck();
        EDITORIDS_DLL void tryTransferID(GJGameLevel* source, GJGameLevel* dest);

        EDITORIDS_DLL void handleLevelDupes(cocos2d::CCArray* array);

        EDITORIDS_DLL void reset();
    }

    namespace ListManagement {
        EDITORIDS_DLL void assignNewID(GJLevelList* level);
        EDITORIDS_DLL void verifyIDAssignment(GJLevelList* level);
        EDITORIDS_DLL void verifyIDAssignmentDelayed(GJLevelList* level);
        EDITORIDS_DLL void queueCheck();
        EDITORIDS_DLL void tryTransferID(GJLevelList* source, GJLevelList* dest);

        EDITORIDS_DLL void handleListDupes(cocos2d::CCArray* array);

        EDITORIDS_DLL void reset();
    }
}