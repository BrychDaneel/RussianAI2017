#pragma once
#ifndef _MY_SMART_START_GROUP_SERVICE_HPP_
#define _MY_SMART_START_GROUP_SERVICE_HPP_


#include "Service.hpp"
#include "model/VehicleType.h"


namespace my{
    class SmartStartGroupService : public Service{
        private:
            Enviroment* env;
            TaskManager * taskManager;
            const VehicleManager * vehicleManager;
            const int RATE = 0;

            model::VehicleType convert(int a);

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif


