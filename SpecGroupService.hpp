#pragma once
#ifndef _MY_SPEC_GROUP_SERVICE_HPP_
#define _MY_SPEC_GROUP_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class SpecGroupService : public Service{
        private:
            Enviroment* env;
            TaskManager* taskManager;
            const VehicleManager * vehicleManager;
            const int RATE = 0;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif
