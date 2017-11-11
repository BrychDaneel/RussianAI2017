#pragma once
#ifndef _MY_ENEMY_SEARCH_SERVICE_HPP_
#define _MY_ENEMY_SEARCH_SERVICE_HPP_


#include "Service.hpp"
#include "VehicleManager.hpp"


namespace my{
    class EnemySearchService : public Service{
        private:
            Enviroment* env;
            const VehicleManager * vehicleManager;
            const int RATE = 120;
            double enemyX;
            double enemyY;
            double myX;
            double myY;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif



