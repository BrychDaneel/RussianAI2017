#pragma once
#ifndef _MY_RUSH_DETECTOR_SERVICE_HPP_
#define _MY_RUSH_DETECTOR_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class RushDetectorService : public Service{
        private:
            Enviroment* env;
            const VehicleManager * vehicleManager;
            TaskManager* taskManager;
            const int RATE = 60;
            double rushCof;
            int minRushTick;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif



