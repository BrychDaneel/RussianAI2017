#pragma once
#ifndef _MY_SAVE_SERVICE_HPP_
#define _MY_SAVE_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class SaveService : public Service{
        private:
            Enviroment* env;
            TaskManager* taskManager;
            const VehicleManager* vehicleManager;
            const int RATE = 60;
            bool first = true;
            double width, height;
            double sX, sY;

            void firstRun();
        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif
