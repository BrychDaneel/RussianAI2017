#pragma once
#ifndef _MY_ASYNC_ROTATE_TASK_HPP_
#define _MY_ASYNC_ROTATE_TASK_HPP_


#include "Task.hpp"
#include <string>


namespace my{
    class AsyncRotateTask : public Task{
        private:
            double x;
            double y;
            double angle;
            double maxSpeed;
            double maxAngularSpeed;
            bool firtRun = true;
            ActionManager* actionManager;
            const VehicleManager* vehicleManager;

            enum class RotateType{Point, Center} rotateType;
        public:
            AsyncRotateTask(double angle, double maxSpeed, double maxAngularSpeed);
            AsyncRotateTask(double x, double y, double angle, double maxSpeed, double maxAngularSpeed);
            virtual bool action();
            virtual void setup(Enviroment& env, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif


