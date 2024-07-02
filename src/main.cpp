#include <Geode/Geode.hpp>
#include <EditorIDsManagement.hpp>

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

#include <Geode/modify/GJLevelList.hpp>
class $modify(GJLevelList) {

	void dataLoaded(DS_Dictionary* dict) {
		GJLevelList::dataLoaded(dict);

		EditorIDs::ListManagement::verifyIDAssignmentDelayed(this);
	}

	bool hasMatchingLevels(GJLevelList* source) {
		if(!GJLevelList::hasMatchingLevels(source)) return false;

        //log::info("Matched list {} with list {}", source->m_listName, m_listName);

		if(m_listType == GJLevelType::Editor) EditorIDs::ListManagement::tryTransferID(this, source);

        return true;
	}
};

#include <Geode/modify/LocalLevelManager.hpp>
class $modify(LocalLevelManager) {
	void dataLoaded(DS_Dictionary* dict) {
		LocalLevelManager::dataLoaded(dict);

		Loader::get()->queueInMainThread([this] {
			EditorIDs::Management::handleLevelDupes(m_localLevels);
			EditorIDs::ListManagement::handleListDupes(m_localLists);
		});
	}

	void firstLoad() {
		LocalLevelManager::firstLoad();

		EditorIDs::Management::reset();
		EditorIDs::ListManagement::reset();
	}
};

#include <Geode/modify/GameManager.hpp>
class $modify(GameManager) {
    void dataLoaded(DS_Dictionary* dict) {
        GameManager::dataLoaded(dict);

        EditorIDs::Management::tryRaiseMaxID(getIntGameVariable("editor_id_max"_spr));
        EditorIDs::ListManagement::tryRaiseMaxID(getIntGameVariable("editor_list_id_max"_spr));
    }

    void encodeDataTo(DS_Dictionary* dict) {
        setIntGameVariable("editor_id_max"_spr, EditorIDs::Management::getMaxID());
        setIntGameVariable("editor_list_id_max"_spr, EditorIDs::ListManagement::getMaxID());

        GameManager::encodeDataTo(dict);
    }
};

#include <Geode/modify/LevelCell.hpp>
class $modify(LevelCell) {
    void loadLocalLevelCell() {
        LevelCell::loadLocalLevelCell();

        if(Mod::get()->getSettingValue<bool>("show-ids")) {
            auto idTextNode = CCLabelBMFont::create(fmt::format("#{}", EditorIDs::getID(m_level)).c_str(), "chatFont.fnt");
            idTextNode->setPosition({346,m_height - 1});
            if(m_level->m_dailyID == 0 && Loader::get()->isModLoaded("n.level-pronouns")) {
                if(m_compactView) idTextNode->setPositionX(idTextNode->getPositionX() - 23.f);
                else idTextNode->setPositionY(idTextNode->getPositionY() - 6.f);
            }
            idTextNode->setAnchorPoint({1,1});
            idTextNode->setScale(m_compactView ? 0.45f : 0.6f);
            idTextNode->setColor({51,51,51});
            idTextNode->setOpacity(152);
            idTextNode->setID("level-id-label"_spr);
            m_mainLayer->addChild(idTextNode);
        }
    }
};

#include <Geode/modify/LevelListCell.hpp>
class $modify(LevelListCell) {
    void loadFromList(GJLevelList* list) {
        LevelListCell::loadFromList(list);

        if(Mod::get()->getSettingValue<bool>("show-ids")) {
            auto idTextNode = CCLabelBMFont::create(fmt::format("#{}", EditorIDs::getID(list)).c_str(), "chatFont.fnt");
            idTextNode->setPosition({346,m_height - 1});
            idTextNode->setAnchorPoint({1,1});
            idTextNode->setScale(0.6f);
            idTextNode->setColor({51,51,51});
            idTextNode->setOpacity(152);
            idTextNode->setID("level-id-label"_spr);
            m_mainLayer->addChild(idTextNode);
        }
    }
};