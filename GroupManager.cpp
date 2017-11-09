#include "GroupManager.hpp"


#include "Repos.hpp"


namespace my{
    GroupManager::GroupManager(ActionManager & actionManager, Enviroment & env) :
        actionManager(actionManager),
        env(env)
    {
    }

    void GroupManager::setup(){
        for (int i=1; i<=getMaxId(); i++)
            freeIndexes.insert(i);
    }

    const int GroupManager::bind(){
        int id = *freeIndexes.begin();
        freeIndexes.erase(id);
        actionManager.assign(id);
        return id;
    }

    const int GroupManager::bind(std::string name){
        int id = bind();
        describe(id, name);
        return id;
    }

    void GroupManager::describe(int id, std::string name){
        groups[name] = id;
        names[id] = name;
    }

    const int GroupManager::getId(std::string name){
        return groups[name];
    }

    const std::string GroupManager::getName(int id){
        return names[id];
    }

    void GroupManager::free(int id){
        freeIndexes.insert(id);
        groups.erase(names[id]);
        names.erase(id);
    }

    void GroupManager::free(std::string name){
        free(groups[name]);
    }

    void GroupManager::select(std::string name){
        select(groups[name]);
    }

    void GroupManager::select(int id){
        actionManager.select(id);
    }

    const int GroupManager::getMaxId(){
        return env.getGame()->getMaxUnitGroup();
    }

}
