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
            int tick = 0;
            bool interrupt;

            enum class SelectType{All, GID, Name, Rect, TypeAndRect, Type} selectType;
        public:
            SelectTask(bool interrupt=true);
            SelectTask(int groupId, bool interrupt=true);
            SelectTask(const char * groupName, bool interrupt=true);
            SelectTask(double left, double top, double right, double bottom, bool interrupt=true);
            SelectTask(double left, double top, double right, double bottom, model::VehicleType type, bool interrupt=true);
            SelectTask(model::VehicleType type, bool interrupt=true);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
            virtual bool canInterrupt();
    };
}
#endif


