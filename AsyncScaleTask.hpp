#pragma once
#ifndef _MY_ASYNC_SCALE_TASK_HPP_
#define _MY_ASYNC_SCALE_TASK_HPP_


#include "Task.hpp"
#include <string>


namespace my{
    class AsyncScaleTask : public Task{
        private:
            double x;
            double y;
            double factor;
            double maxSpeed;
            bool firtRun = true;
            ActionManager* actionManager;
            const VehicleManager* vehicleManager;

            enum class ScaleType{Point, Center} scaleType;
        public:
            AsyncScaleTask(double factor, double maxSpeed = 0.0);
            AsyncScaleTask(double x, double y, double factor, double maxSpeed = 0.0);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif
