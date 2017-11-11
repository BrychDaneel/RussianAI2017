#pragma once
#ifndef _MY_ASYNC_MOVE_TASK_HPP_
#define _MY_ASYNC_MOVE_TASK_HPP_


#include "Task.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"
#include <string>


namespace my{
    class AsyncMoveTask : public Task{
        private:
            int gid = -1;
            double x;
            double y;
            int taskTick = 0;
            ActionManager* actionManager;
            GroupManager* groupManager;
            const VehicleManager* vehicleManager;
            std::string name = "";
            double width;
            double height;
            double maxSpeed;
        public:
            AsyncMoveTask(double x, double y, double maxSpeed = 0.0);
            AsyncMoveTask(int groupId, double x, double y, double maxSpeed = 0.0);
            AsyncMoveTask(const std::string & groupName, double x, double y, double maxSpeed = 0.0);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif

