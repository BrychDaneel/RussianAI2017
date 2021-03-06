#pragma once
#ifndef _MY_NUCLEAR_SERVICE_HPP_
#define _MY_NUCLEAR_SERVICE_HPP_


#include "Service.hpp"
#include "model/Game.h"

namespace my{
    class NuclearService : public Service{
        private:
            const model::Game * game;
            const VehicleManager * vehicleManager;
            Enviroment * env;
            TaskManager * taskManager;
            GroupManager * groupManager;
            int RATE = 120;

            double nuclearDist;
            double minNuclearDistPercent;
            double maxNuclearDistPercent;
            double minVisionCof;
            double nuclearCancelRadius;
            double maxNuclearDist;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif

