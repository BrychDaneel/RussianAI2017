#pragma once
#ifndef _MY_FRONT_MOVE_SERVICE_HPP_
#define _MY_FRONT_MOVE_SERVICE_HPP_


#include "Service.hpp"


namespace my{
    class FrontMoveService : public Service{
        private:
            Enviroment* env;
            TaskManager * taskManager;
            const int RATE = 60;
            double moveSpeed;

        public:
            virtual bool action();
            virtual int getRate();
            virtual void setup(Enviroment& env, TaskManager& taskManager, ActionManager& actionManager, GroupManager& groupManager);
    };
}
#endif
