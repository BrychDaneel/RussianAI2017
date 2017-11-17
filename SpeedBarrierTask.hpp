#pragma once
#ifndef _MY_SPEED_BARRIER_TASK_HPP_
#define _MY_SPEED_BARRIER_TASK_HPP_


#include "Task.hpp"
#include "Enviroment.hpp"
#include "ActionManager.hpp"
#include "GroupManager.hpp"
#include "SpeedManager.hpp"


namespace my{
    class SpeedBarrierTask : public Task{
        private:
            const SpeedManager * speedManager;
            double maxSpeed;
            GroupManager * groupManager;
            bool interrupt;
            std::string groupName;
            bool useGroup;
            const VehicleManager * vehicleManager;
        public:
            SpeedBarrierTask(double maxSpeed, bool interrupt=true);
            SpeedBarrierTask(const char * groupName, double maxSpeed, bool interrupt=true);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
            virtual bool canInterrupt();
    };
}
#endif


