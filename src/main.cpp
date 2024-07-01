#include <Geode/Geode.hpp>
#include "include/EditorIDs.hpp"

using namespace geode::prelude;

#include <Geode/modify/GJGameLevel.hpp>
class $modify(GJGameLevel) {

	void dataLoaded(DS_Dictionary* dict) {
		GJGameLevel::dataLoaded(dict);

		EditorIDs::Management::verifyIDAssignmentDelayed(this);
	}

	void handleStatsConflict(GJGameLevel* source) {
		GJGameLevel::handleStatsConflict(source);

		if(m_levelType != GJLevelType::Editor) return;

		EditorIDs::Management::tryTransferID(source, this);
	}
};

#include <Geode/modify/LocalLevelManager.hpp>
class $modify(LocalLevelManager) {
	void dataLoaded(DS_Dictionary* dict) {
		LocalLevelManager::dataLoaded(dict);

		Loader::get()->queueInMainThread([this] {
			EditorIDs::Management::handleLevelDupes(m_localLevels);
		});
	}
};

#include <Geode/modify/LevelCell.hpp>
class $modify(LevelCell) {
    void loadLocalLevelCell() {
        LevelCell::loadLocalLevelCell();

        //this->getScheduler()->scheduleSelector(schedule_selector(BILevelCell::checkHover), this, 0.1f, false);

        //TODO: layout for ID node in Node ID mod

        auto idTextNode = CCLabelBMFont::create(fmt::format("#{}", EditorIDs::getID(m_level)).c_str(), "chatFont.fnt");
        //idTextNode->setPosition({346,79 - (m_level->m_dailyID == 0 && Loader::get()->isModLoaded("n.level_pronouns") ? 9.f : 0.f)});
        idTextNode->setPosition({346,m_height - 1});
        if(m_level->m_dailyID == 0 && Loader::get()->isModLoaded("n.level_pronouns")) {
            if(m_compactView) idTextNode->setPositionX(idTextNode->getPositionX() - 23.f);
            else idTextNode->setPositionY(idTextNode->getPositionY() - 9.f);
        }
        idTextNode->setAnchorPoint({1,1});
        idTextNode->setScale(m_compactView ? 0.45f : 0.6f);
        idTextNode->setColor({51,51,51});
        idTextNode->setOpacity(152);
        idTextNode->setID("level-id-label"_spr);
        m_mainLayer->addChild(idTextNode);
    }
};