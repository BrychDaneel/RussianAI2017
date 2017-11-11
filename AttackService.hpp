#pragma once
#ifndef _MY_ATTACK_SERVICE_HPP_
#define _MY_ATTACK_SERVICE_HPP_


#include "Service.hpp"
#include "VehicleManager.hpp"


namespace my{
    class AttackService : public Service{
        private:
            Enviroment* env;
            TaskManager * taskManager;
            const int RATE = 60;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif
