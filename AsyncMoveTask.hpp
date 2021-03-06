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
            double x;
            double y;
            double maxSpeed;
            bool firtRun = true;
            ActionManager* actionManager;
            const VehicleManager* vehicleManager;
        public:
            AsyncMoveTask(double x, double y, double maxSpeed = 0.0);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif

