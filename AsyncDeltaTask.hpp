#pragma once
#ifndef _MY_ASYNC_DELTA_TASK_HPP_
#define _MY_ASYNC_DELTA_TASK_HPP_


#include "Service.hpp"


namespace my{
    class AsyncDeltaTask : public Task{
        private:
            double dx;
            double dy;
            double maxSpeed;
            bool firtRun = true;
            ActionManager* actionManager;
            const VehicleManager* vehicleManager;
        public:
            AsyncDeltaTask(double dx, double dy, double maxSpeed=0.0);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif
