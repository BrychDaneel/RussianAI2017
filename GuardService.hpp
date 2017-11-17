#pragma once
#ifndef _MY_GUARD_SERVICE_HPP_
#define _MY_GUARD_SERVICE_HPP_


#include "Service.hpp"
#include "model/Game.h"

namespace my{
    class GuardService : public Service{
        private:
            const VehicleManager * vehicleManager;
            Enviroment * env;
            TaskManager * taskManager;
            GroupManager * groupManager;
            int RATE = 60;

            int guardInteresCount;
            double guardInteresRadius;
            double guardMinArmyDist;
            double guardMaxDist;
            double guardZoneRadius;
            const char * groupName = "Guard";

            bool first = true;

            void firsRun();
        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif


