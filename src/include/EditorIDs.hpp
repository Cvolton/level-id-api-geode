#pragma once

#include <Geode/binding/GJGameLevel.hpp>

namespace EditorIDs {
    int getID(GJGameLevel* level, bool autoAssign = true);

    namespace Management {
        void assignNewID(GJGameLevel* level);
        void verifyIDAssignment(GJGameLevel* level);
        void verifyIDAssignmentDelayed(GJGameLevel* level);
        void queueCheck();
        void tryTransferID(GJGameLevel* source, GJGameLevel* dest);

        void handleLevelDupes(cocos2d::CCArray* array);
    }
}