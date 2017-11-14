#pragma once
#ifndef _MY_LOSE_DETECTOR_SERVICE_HPP_
#define _MY_LOSE_DETECTOR_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class LoseDetectorService : public Service{
        private:
            Enviroment* env;
            const VehicleManager * vehicleManager;
            TaskManager* taskManager;
            const int RATE = 60;
            double loseCof;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif



