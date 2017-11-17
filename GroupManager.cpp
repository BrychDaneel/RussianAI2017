#include "GroupManager.hpp"


#include "Repos.hpp"
#include <vector>


namespace my{
    GroupManager::GroupManager(ActionManager & actionManager, Enviroment & env) :
        actionManager(actionManager),
        env(env)
    {
    }

    void GroupManager::setup(){
        for (int i=1; i<=getMaxId(); i++)
            freeIndexes.insert(i);
        vehicleManager = env.getVehicleManager();
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

    const int GroupManager::getId(std::string name) const{
        return (*groups.find(name)).second;
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

    const bool GroupManager::exist(std::string name) const{
        return groups.find(name) != groups.end();
    }

    const std::vector<model::Vehicle> GroupManager::getVehicles(const int id)const{
        std::vector<model::Vehicle> result;
        for (auto pair : vehicleManager->getMy()){
            model::Vehicle vehicle = pair.second;
            for (int unitGroup : vehicle.getGroups())
                if (id == unitGroup)
                    result.push_back(vehicle);
            }
        return result;
    }

    const std::vector<model::Vehicle> GroupManager::getVehicles(const std::string name)const{
        return getVehicles(getId(name));
    }
}
