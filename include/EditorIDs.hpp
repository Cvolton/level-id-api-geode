#pragma once

#include <Geode/loader/Dispatch.hpp>

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
    namespace Event {
        using GetLevelID = geode::DispatchEvent<int*, GJGameLevel*>;
        using GetListID = geode::DispatchEvent<int*, GJLevelList*>;
        using GetLevelID2 = geode::DispatchEvent<int*, GJGameLevel*, bool>;
        using GetListID2 = geode::DispatchEvent<int*, GJLevelList*, bool>;

        using GetLevelByID = geode::DispatchEvent<GJGameLevel*, int>;
        using GetListByID = geode::DispatchEvent<GJLevelList*, int>;
    }

#ifndef EDITOR_IDS_USE_EVENTS_API

    /**
     * @brief Get the editor ID of a level or list.
     *
     * @param level The level to get the ID of.
     *
     * @return The ID of the level, or m_levelID if the level is not editor.
     */
    EDITORIDS_DLL int getID(GJGameLevel* level);

    /**
     * @brief Get the editor ID of a level or list.
     *
     * @param list The list to get the ID of.
     *
     * @return The ID of the level, or m_levelID if the level is not editor.
     */
    EDITORIDS_DLL int getID(GJLevelList* level);

    /**
     * @brief Get the editor ID of a level or list.
     *
     * @param level The level to get the ID of.
     * @param autoAssign Whether to assign an ID if it has not been assigned automatically
     *
     * @return The ID of the level, or m_levelID if the level is not editor.
     */
    EDITORIDS_DLL int getID(GJGameLevel* level, bool autoAssign);

    /**
     * @brief Get the editor ID of a level or list.
     *
     * @param level The level to get the ID of.
     * @param autoAssign Whether to assign an ID if it has not been assigned automatically
     *
     * @return The ID of the level, or m_levelID if the level is not editor.
     */
    EDITORIDS_DLL int getID(GJLevelList* level, bool autoAssign);

    /**
     * @brief Get a level by its editor ID.
     * 
     * @param id The editor ID of the level.
     *
     * @return The level with the given ID, or nullptr if no level has that ID.
     */
    EDITORIDS_DLL GJGameLevel* getLevelByID(int id);

    /**
     * @brief Get a list by its editor ID.
     * 
     * @param id The editor ID of the list.
     *
     * @return The list with the given ID, or nullptr if no list has that ID.
     */
    EDITORIDS_DLL GJLevelList* getListByID(int id);

#endif // !EDITOR_IDS_USE_EVENTS_API
}