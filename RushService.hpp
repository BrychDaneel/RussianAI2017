#pragma once
#ifndef _MY_RUSH_SERVICE_HPP_
#define _MY_RUSH_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class RushService : public Service{
        private:
            Enviroment* env;
            TaskManager* taskManager;
            const VehicleManager* vehicleManager;
            const int RATE = 60;
            double sX, sY, width, height;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif

