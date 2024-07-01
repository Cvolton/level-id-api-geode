# Editor Level ID API
Assigns Level IDs to Editor levels that other mods can use to refer to them.

Reuses `m_downloads` and `m_featured` on `GJGameLevel` and `m_downloads` and `m_levelsToComplete` on `GJLevelList` for editor levels/lists to store unique ID numbers for them.

<img src="logo.png" width="150" alt="the mod's logo" />

## How does this work?

Every level stores the same piece of information regardless of type. Since some information (download counts, featured state) is not actually used for editor levels, this mod repurposes these fields to store a unique ID value (per save file). This means that these IDs do not disappear if you uninstall the mod or if you load your save file in a copy of the game that does not have Geode installed - your levels will get their assigned IDs back after reinstalling the mod.

## Usage
You can use Editor Level ID API as a dependency by declaring it in your `mod.json`:

```json
{
    "dependencies": [
        {
            "id": "cvolton.editor-ids",
            "version": "v1.0.0",
            "importance": "required"
        }
    ]
}
```

All editor levels should already have IDs assigned by default on mod load. Getting the ID assigned to the level can be done as follows:
```cpp
int levelId = EditorIDs::getID(level);
```
This also assigns a new ID to the level if it does not have one already. If you do not wish to modify the level object to assign an ID, you can pass a false argument `EditorIDs::getID(level, false);` to skip the auto-assign behavior. This might be desirable while accessing editor IDs during something like `LocalLevelManager::dataLoaded` as a lot of the de-duplication checks are delayed by 1 frame. (This probably does not matter to you if you are not accessing the IDs during a specific frame while loading the game though).

Similarly you can utilize a different overload of the same function to get the ID of a GJLevelList.
```cpp
int listId = EditorIDs::getID(myGJLevelList);
```

Namespaces `EditorIDs::Management` and `EditorIDs::ListManagement` are also exported, however they should be treated as danger zone and using functions within them should only be considered last resort.

Alternatively it is also possible to fetch and check the fields used to store the IDs directly, however this is heavily discouraged, as the exact fields used are considered an implementation detail and subject to change in the future.