#pragma once

#include <Geode/loader/Dispatch.hpp>
#define MY_MOD_ID "cvolton.level-id-api"

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
    /**
     * @brief Get the editor ID of a level or list.
     *
     * @param level The level to get the ID of.
     *
     * @return The ID of the level, or m_levelID if the level is not editor.
     */
    inline int getID(GJGameLevel* level) GEODE_EVENT_EXPORT_ID_NORES(&getID, (level), MY_MOD_ID "/getID-level");

    /**
     * @brief Get the editor ID of a level or list.
     *
     * @param list The list to get the ID of.
     *
     * @return The ID of the level, or m_levelID if the level is not editor.
     */
    inline int getID(GJLevelList* list) GEODE_EVENT_EXPORT_ID_NORES(static_cast<int(*)(GJLevelList*)>(&getID), (list), MY_MOD_ID "/getID-list");

    /**
     * @brief Get the editor ID of a level or list.
     *
     * @param level The level to get the ID of.
     * @param autoAssign Whether to assign an ID if it has not been assigned automatically
     *
     * @return The ID of the level, or m_levelID if the level is not editor.
     */
    inline int getID(GJGameLevel* level, bool autoAssign) GEODE_EVENT_EXPORT_ID_NORES(static_cast<int(*)(GJGameLevel*, bool)>(&getID), (level, autoAssign), MY_MOD_ID "/getID-level-autoAssign");

    /**
     * @brief Get the editor ID of a level or list.
     *
     * @param list The list to get the ID of.
     * @param autoAssign Whether to assign an ID if it has not been assigned automatically
     *
     * @return The ID of the level, or m_levelID if the level is not editor.
     */
    inline int getID(GJLevelList* list, bool autoAssign) GEODE_EVENT_EXPORT_ID_NORES(static_cast<int(*)(GJLevelList*, bool)>(&getID), (list, autoAssign), MY_MOD_ID "/getID-list-autoAssign");

    /**
     * @brief Get a level by its editor ID.
     * 
     * @param id The editor ID of the level.
     *
     * @return The level with the given ID, or nullptr if no level has that ID.
     */
    inline GJGameLevel* getLevelByID(int id) GEODE_EVENT_EXPORT_NORES(&getLevelByID, (id));

    /**
     * @brief Get a list by its editor ID.
     * 
     * @param id The editor ID of the list.
     *
     * @return The list with the given ID, or nullptr if no list has that ID.
     */
    inline GJLevelList* getListByID(int id) GEODE_EVENT_EXPORT_NORES(&getListByID, (id));
}

//#undef MY_MOD_ID