#pragma once
#ifndef _MY_PERFECT_BREAK_SERVICE_HPP_
#define _MY_PERFECT_BREAK_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class PerfectBreakService : public Service{
        private:
            Enviroment* env;
            const VehicleManager * vehicleManager;
            int RATE = 300;
            double perfectBreak;
            int startSize;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}

#endif
