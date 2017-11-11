#pragma once
#ifndef _MY_FRONT_DETECTOR_SERVICE_HPP_
#define _MY_FRONT_DETECTOR_SERVICE_HPP_


#include "Service.hpp"
#include "DamageManager.hpp"
#include "VehicleManager.hpp"


namespace my{
    class FrontDetectorService : public Service{
        private:
            Enviroment* env;
            const DamageManager * damageManager;
            const VehicleManager * vehicleManager;
            const int RATE = 60;
            double frontX, frontY;
            double myX, myY;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif



