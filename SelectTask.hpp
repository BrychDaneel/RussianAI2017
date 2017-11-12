#pragma once
#ifndef _MY_SELECT_TASK_HPP_
#define _MY_SELECT_TASK_HPP_


#include "Task.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"
#include <string>
#include "model/VehicleType.h"


namespace my{
    class SelectTask : public Task{
        private:
            ActionManager* actionManager;
            GroupManager* groupManager;
            int gid;
            std::string name;
            double width;
            double height;
            double left, top, right, bottom;
            model::VehicleType type;
            bool firstRun = true;

            enum class SelectType{All, GID, Name, Rect, TypeAndRect, Type} selectType;
        public:
            SelectTask();
            SelectTask(int groupId);
            SelectTask(const std::string & groupName);
            SelectTask(double left, double top, double right, double bottom);
            SelectTask(double left, double top, double right, double bottom, model::VehicleType type);
            SelectTask(model::VehicleType type);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif


