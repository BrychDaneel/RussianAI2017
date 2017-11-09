#pragma once
#ifndef _MY_GROUP_MANAGER_HPP_
#define _MY_GROUP_MANAGER_HPP_


#include <map>
#include <set>
#include <string>
#include "ActionManager.hpp"
#include "Enviroment.hpp"
#include "model/VehicleType.h"


namespace my{
    class GroupManager{
        private:
            std::map<std::string, int> groups;
            std::map<int, std::string> names;
            std::set<int> freeIndexes;
            int maxId;
            ActionManager & actionManager;
            Enviroment & env;
        public:
            GroupManager(ActionManager & actionManager, Enviroment & env);
            void setup();

            const int bind();
            const int bind(std::string name);

            void describe(int id, std::string name);
            const int getId(std::string name);
            const std::string getName(int id);

            void free(int id);
            void free(std::string name);

            void select(std::string name);
            void select(int id);
            const int getMaxId();
    };
}


#endif
