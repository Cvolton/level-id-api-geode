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
}