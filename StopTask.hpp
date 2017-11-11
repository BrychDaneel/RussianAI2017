#pragma once
#ifndef _MY_STOP_TASK_HPP_
#define _MY_STOP_TASK_HPP_


#include "Task.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"
#include <string>


namespace my{
    class StopTask : public Task{
        private:
            bool selected = false;
            int gid = -1;
            int taskTick = 0;
            ActionManager* actionManager;
            GroupManager* groupManager;
            const VehicleManager* vehicleManager;
            std::string name = "";
            double width;
            double height;
        public:
            StopTask();
            StopTask(int groupId);
            StopTask(const std::string & groupName);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif

