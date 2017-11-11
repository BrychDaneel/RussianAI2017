#pragma once
#ifndef _MY_SPEED_BARRIER_TASK_HPP_
#define _MY_ASYNC_MOVE_TASK_HPP_


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
        public:
            SpeedBarrierTask(double maxSpeed);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif


