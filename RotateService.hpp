#pragma once
#ifndef _MY_ROTATE_SERVICE_HPP_
#define _MY_ROTATE_SERVICE_HPP_


#include "Service.hpp"
#include "VehicleManager.hpp"


namespace my{
    class RotateService : public Service{
        private:
            Enviroment* env;
            TaskManager * taskManager;
            const int RATE = 120;
            double minRotateAngle;
            double minRotateDistance;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif


