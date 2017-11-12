#pragma once
#ifndef _MY_REGROUP_SERVICE_HPP_
#define _MY_REGROUP_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class RegroupService : public Service{
        private:
            Enviroment* env;
            TaskManager * taskManager;
            const int RATE = 300;
            double maxSquarCof;
            double maxFightSquarCof;
            const VehicleManager * vehicleManager;

            void getAirBox(double & minX, double & maxX, double & minY, double & maxY);
            void getGroundBox(double & minX, double & maxX, double & minY, double & maxY);

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif
