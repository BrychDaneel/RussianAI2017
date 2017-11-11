#pragma once
#ifndef _MY_FIGHT_DETECTOR_SERVICE_HPP_
#define _MY_FIGHT_DETECTOR_SERVICE_HPP_


#include "Service.hpp"
#include "DamageManager.hpp"


namespace my{
    class FightDetectorService : public Service{
        private:
            Enviroment* env;
            const DamageManager * damageManager;
            TaskManager* taskManager;
            const int RATE = 30;
            int minFightDamage;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif


