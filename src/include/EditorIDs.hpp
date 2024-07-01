#pragma once

#include <Geode/binding/GJGameLevel.hpp>
#include <Geode/binding/GJLevelList.hpp>

namespace EditorIDs {
    int getID(GJGameLevel* level, bool autoAssign = true);
    int getID(GJLevelList* level, bool autoAssign = true);

    namespace Management {
        void assignNewID(GJGameLevel* level);
        void verifyIDAssignment(GJGameLevel* level);
        void verifyIDAssignmentDelayed(GJGameLevel* level);
        void queueCheck();
        void tryTransferID(GJGameLevel* source, GJGameLevel* dest);

        void handleLevelDupes(cocos2d::CCArray* array);

        void reset();
    }

    namespace ListManagement {
        void assignNewID(GJLevelList* level);
        void verifyIDAssignment(GJLevelList* level);
        void verifyIDAssignmentDelayed(GJLevelList* level);
        void queueCheck();
        void tryTransferID(GJLevelList* source, GJLevelList* dest);

        void handleListDupes(cocos2d::CCArray* array);

        void reset();
    }
}