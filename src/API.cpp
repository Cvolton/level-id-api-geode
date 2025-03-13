#include <EditorIDs.hpp>

template <class>
struct ToFilterImpl;

template <class... Args>
struct ToFilterImpl<geode::DispatchEvent<Args...>>
{
    using type = geode::DispatchFilter<Args...>;
};

template <class T>
using ToFilter = typename ToFilterImpl<T>::type;

$execute
{
    new geode::EventListener(+[](int* ret, GJGameLevel* level) {
        *ret = EditorIDs::getID(level);
        return geode::ListenerResult::Stop;
    }, ToFilter<EditorIDs::event::GetLevelID>("v1/get-level-id"_spr));

    new geode::EventListener(+[](int* ret, GJLevelList* list) {
        *ret = EditorIDs::getID(list);
        return geode::ListenerResult::Stop;
    }, ToFilter<EditorIDs::event::GetListID>("v1/get-list-id"_spr));

    new geode::EventListener(+[](int* ret, GJGameLevel* level, bool autoAssign) {
        *ret = EditorIDs::getID(level, autoAssign);
        return geode::ListenerResult::Stop;
    }, ToFilter<EditorIDs::event::GetLevelID2>("v1/get-level-id-2"_spr));

    new geode::EventListener(+[](int* ret, GJLevelList* list, bool autoAssign) {
        *ret = EditorIDs::getID(list, autoAssign);
        return geode::ListenerResult::Stop;
    }, ToFilter<EditorIDs::event::GetListID2>("v1/get-list-id-2"_spr));

    new geode::EventListener(+[](GJGameLevel* level, int id) {
        level = EditorIDs::getLevelByID(id);
        return geode::ListenerResult::Stop;
    }, ToFilter<EditorIDs::event::GetLevelByID>("v1/get-level-by-id"_spr));

    new geode::EventListener(+[](GJLevelList* list, int id) {
        list = EditorIDs::getListByID(id);
        return geode::ListenerResult::Stop;
    }, ToFilter<EditorIDs::event::GetListByID>("v1/get-list-by-id"_spr));
}
