#pragma once
#ifndef _MY_FAR_NUCLEAR_SERVICE_HPP_
#define _MY_FAR_NUCLEAR_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class FarNuclearService : public Service{
        private:
            const model::Game * game;
            const VehicleManager * vehicleManager;
            Enviroment * env;
            TaskManager * taskManager;
            GroupManager * groupManager;
            int RATE = 400;

            int farNuclearCount;
            double minFarRange;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif


