#pragma once
#ifndef _MY_HEAL_ANGLE_DETECCTOR_SERVICE_HPP_
#define _MY_HEAL_ANGLE_DETECCTOR_SERVICE_HPP_


#include "Service.hpp"
#include "VehicleManager.hpp"


namespace my{
    class HealAngleDetectorService : public Service{
        private:
            Enviroment* env;
            const VehicleManager * vehicleManager;
            const int RATE = 120;
            double angleX;
            double angleY;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif

